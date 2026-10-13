#!/usr/bin/env python3
"""Read a compiled Apple asset catalog (Assets.car): inventory plus image export.

Usage: PYTHONPATH=tools/pylib decode_car.py Assets.car <out_dir>
Writes <out_dir>/inventory.json (every rendition: facet name, size, scale, pixel format, layout, compression, key attributes,
plus colors / named data where recognized) and PNG files for bitmap renditions that decode (raw, ZIP, LZFSE, LZVN not supported).
Reverse-engineered from the public BOM/CAR layout; nothing is guessed: undecodable renditions are listed with the reason.
"""
import json, os, struct, sys, zlib

try: import lzfse
except ImportError: lzfse = None
from PIL import Image

KEY_NAMES = {1:'element',2:'part',3:'size',4:'direction',5:'placeholder',6:'value',7:'appearance',8:'dimension1',9:'dimension2',10:'state',
             11:'layer',12:'scale',13:'localization',14:'presentationState',15:'idiom',16:'subtype',17:'identifier',18:'previousValue',
             19:'previousState',20:'sizeClassHorizontal',21:'sizeClassVertical',22:'memoryClass',23:'graphicsClass',24:'graphicsFallBack',
             25:'deploymentTarget',26:'glyphWeight',27:'glyphSize'}
LAYOUTS = {9:'data', 1003:'imageset-reference', 1004:'image', 1002:'color-or-stack', 10:'data', 11:'externallink', 12:'layerstack', 13:'internallink', 20:'packed', 21:'name', 23:'image', 24:'multisizeimageset',
           1000:'texture', 1001:'textureimage', 1002:'color', 1003:'multisizeimage', 1004:'legacyimage', 1007:'internallink', 1008:'gradient',
           1009:'effect', 1010:'recognitionobject'}

class Bom:
    def __init__(self, path):
        self.b = open(path, 'rb').read()
        if self.b[:8] != b'BOMStore': raise ValueError('not a BOM file')
        _, nblocks, ioff, ilen, voff, vlen = struct.unpack_from('>6I', self.b, 8)
        count = struct.unpack_from('>I', self.b, ioff)[0]
        self.blocks = [struct.unpack_from('>II', self.b, ioff + 4 + 8 * i) for i in range(count)]
        n = struct.unpack_from('>I', self.b, voff)[0]; pos = voff + 4; self.vars = {}
        for _ in range(n):
            idx, ln = struct.unpack_from('>IB', self.b, pos); pos += 5
            self.vars[self.b[pos:pos + ln].decode()] = idx; pos += ln
    def block(self, i):
        off, ln = self.blocks[i]; return self.b[off:off + ln]
    def tree(self, name):
        """Yield (key_bytes, value_bytes) of a BOM tree variable, in leaf order."""
        t = self.block(self.vars[name])
        if t[:4] != b'tree': raise ValueError('not a tree: ' + name)
        node = struct.unpack_from('>I', t, 8)[0]
        while True:  # descend to the leftmost leaf
            n = self.block(node); is_leaf, cnt, fwd, back = struct.unpack_from('>HHII', n, 0)
            if is_leaf: break
            node = struct.unpack_from('>I', n, 12)[0]
        while True:
            n = self.block(node); is_leaf, cnt, fwd, back = struct.unpack_from('>HHII', n, 0)
            for i in range(cnt):
                v, k = struct.unpack_from('>II', n, 12 + 8 * i)
                yield self.block(k), self.block(v)
            if fwd == 0: break
            node = fwd

def tlv(buf):
    pos = 0; out = {}
    while pos + 8 <= len(buf):
        tag, ln = struct.unpack_from('<II', buf, pos); pos += 8
        out[tag] = buf[pos:pos + ln]; pos += ln
    return out

def rows_to_png(width, height, pixels, fmt, path):
    if fmt == 'ARGB' or fmt == 'BGRA':
        # CAR stores premultiplied BGRA bytes as 'ARGB' little-endian words
        img = Image.frombuffer('RGBA', (width, height), pixels, 'raw', 'BGRA', 0, 1)
    elif fmt == 'GA8 ':
        img = Image.frombuffer('LA', (width, height), pixels, 'raw', 'LA', 0, 1)
    elif fmt == 'RGB5' or fmt == 'RGBA':
        img = Image.frombuffer('RGBA', (width, height), pixels, 'raw', 'RGBA', 0, 1)
    else: raise ValueError('pixel format ' + fmt)
    img.save(path)

def palette_image(d, width, height):
    """Palette image (compression 8, LZFSE): 0xCAFEF00D, version, uint16 colour count, count x 4 bytes (A,R,G,B, premultiplied),
    then width*height uint16 indices. Returns RGBA bytes (un-premultiplied)."""
    magic, version, count = struct.unpack_from('<IIH', d, 0)
    if magic != 0xCAFEF00D: raise ValueError('palette image magic %08x' % magic)
    palette = []
    for i in range(count):
        a, r, g, b = d[10 + 4 * i:14 + 4 * i]
        if a and a < 255: r, g, b = min(255, r * 255 // a), min(255, g * 255 // a), min(255, b * 255 // a)
        palette.append(bytes((r, g, b, a)))
    pos = 10 + 4 * count; idx_size = 2
    if len(d) - pos < width * height * idx_size: idx_size = 1
    if len(d) - pos < width * height * idx_size: raise ValueError(f'palette indices too short: {len(d) - pos} for {width}x{height}')
    out = bytearray()
    for i in range(width * height):
        k = int.from_bytes(d[pos + i * idx_size:pos + (i + 1) * idx_size], 'little')
        out += palette[k] if k < count else b'\0\0\0\0'
    return bytes(out)

def decode_pixels(data, width, height):
    """'MLEC' bitmap payload -> (RGBA or LA bytes, how). Layout: tag, version, compression, length, data.
    Compression ids follow CoreUI: 0 raw, 2 zip, 4 lzfse, 8 palette+lzfse; 10/11 (deepmap) are tiled and not decoded."""
    if data[:4] not in (b'MLEC', b'CELM'): raise ValueError('payload tag ' + repr(data[:4]))
    version, comp, ln = struct.unpack_from('<III', data, 4)
    body = data[16:16 + ln]
    if comp == 0: return ('bgra', body), 'raw'
    if comp == 2: return ('bgra', zlib.decompress(body)), 'zip'
    if comp == 4:
        if lzfse is None: raise ValueError('lzfse module missing')
        return ('bgra', lzfse.decompress(body)), 'lzfse'
    if comp == 8:
        if lzfse is None: raise ValueError('lzfse module missing')
        return ('rgba', palette_image(lzfse.decompress(body), width, height)), 'palette+lzfse'
    if comp in (10, 11) or body[:4] == b'KCBC': raise ValueError('deepmap/KCBC tiled bitmap (compression %d) not decoded' % comp)
    raise ValueError(f'compression {comp} unsupported')

def raw_data(payload):
    """'RAWD' payload (SVG / PDF / data assets): tag, version, length, bytes (LZFSE when it starts with bvx)."""
    if payload[:4] != b'DWAR': raise ValueError('payload tag ' + repr(payload[:4]))
    version, ln = struct.unpack_from('<II', payload, 4)
    body = payload[12:12 + ln]
    if body[:3] == b'bvx':
        if lzfse is None: raise ValueError('lzfse module missing')
        body = lzfse.decompress(body)
    return body

def main(car, out):
    os.makedirs(os.path.join(out, 'png'), exist_ok=True)
    bom = Bom(car)
    # key format: 'kfmt' tag, version, count, then identifiers
    kf = bom.block(bom.vars['KEYFORMAT'])
    ntok = struct.unpack_from('<I', kf, 8)[0]
    tokens = list(struct.unpack_from('<%dI' % ntok, kf, 12))
    facets = {}
    for k, v in bom.tree('FACETKEYS'):
        name = k.decode('utf8', 'replace')
        # value: hot spot (2 x uint16), attribute count (uint16), then (id, value) uint16 pairs
        _, _, n = struct.unpack_from('<HHH', v, 0)
        facets[name] = {KEY_NAMES.get(a, str(a)): b for a, b in (struct.unpack_from('<HH', v, 6 + 4 * i) for i in range(n))}
    ident_to_name = {f.get('identifier'): n for n, f in facets.items() if 'identifier' in f}
    items = []; ok = 0
    for k, v in bom.tree('RENDITIONS'):
        attrs = dict(zip(tokens, struct.unpack_from('<%dH' % ntok, k, 0)))
        keyd = {KEY_NAMES.get(t, str(t)): val for t, val in attrs.items() if val}
        if v[:4] != b'ISTC': items.append({'key': keyd, 'error': 'not a CSI blob'}); continue
        (_, version, flags, width, height, scale, pixfmt, cspace) = struct.unpack_from('<4sIIIIII I'.replace(' ', ''), v, 0)
        modtime, layout, _z = struct.unpack_from('<IHH', v, 32)
        name = v[40:40 + 128].split(b'\0')[0].decode('utf8', 'replace')
        tlv_len, _u, _z2, rend_len = struct.unpack_from('<IIII', v, 168)
        info = tlv(v[184:184 + tlv_len]); payload = v[184 + tlv_len:184 + tlv_len + rend_len]
        pf = pixfmt.to_bytes(4, 'little').decode('latin1') if isinstance(pixfmt, int) else str(pixfmt)
        pf = pf[::-1] if pf[::-1] in ('ARGB', 'GA8 ', 'JPEG', 'PDF ', 'RGB5', 'RGBA', 'SVG ') else pf
        item = {'name': name, 'facet': ident_to_name.get(keyd.get('identifier')), 'width': width, 'height': height, 'scale': scale / 100,
                'pixelFormat': pf, 'layout': LAYOUTS.get(layout, layout), 'key': keyd, 'payloadBytes': len(payload), 'csiFlags': flags}
        safe = (item['facet'] or name or 'item').replace('/', '_')
        if payload[:4] == b'RLOC':
            comps = struct.unpack_from('<I', payload, 8)[0]
            item['color'] = [round(x, 5) for x in struct.unpack_from('<%dd' % comps, payload, 12)]
        elif payload[:4] == b'DWAR':
            try:
                body = raw_data(payload)
                ext = 'svg' if b'<svg' in body[:400] or body[:5] == b'<?xml' else 'pdf' if body[:4] == b'%PDF' else 'jpg' if body[:2] == b'\xff\xd8' else 'bin'
                file = f"data/{safe}-{len(items)}.{ext}"; os.makedirs(os.path.join(out, 'data'), exist_ok=True)
                open(os.path.join(out, file), 'wb').write(body); item['data'] = file
            except Exception as e: item['error'] = str(e)
        elif payload[:4] in (b'MLEC', b'CELM') and width and height and pf in ('ARGB', 'GA8 ', 'BGRA'):
            try:
                (kind, px), how = decode_pixels(payload, width, height)
                file = f"png/{safe}@{int(item['scale'])}x-{keyd.get('idiom', 0)}-{len(items)}.png"
                if kind == 'rgba': Image.frombuffer('RGBA', (width, height), px, 'raw', 'RGBA', 0, 1).save(os.path.join(out, file))
                else:
                    channels = 2 if pf == 'GA8 ' else 4
                    stride = len(px) // height
                    if stride < width * channels: raise ValueError(f'bitmap too small: {len(px)} bytes for {width}x{height}x{channels}')
                    if stride != width * channels: px = b''.join(px[r * stride:r * stride + width * channels] for r in range(height))
                    rows_to_png(width, height, px, 'GA8 ' if pf == 'GA8 ' else 'ARGB', os.path.join(out, file))
                item['png'] = file; item['compression'] = how; ok += 1
            except Exception as e: item['error'] = str(e)
        elif payload[:4] == b'' and width and height: item['note'] = 'reference entry (sizes only), no bitmap in this rendition'
        elif payload[:4] == b'ISMS' or payload[:4] == b'SISM': item['note'] = 'size/slice metadata'
        items.append(item)
    json.dump({'source': os.path.basename(car), 'keyTokens': [KEY_NAMES.get(t, t) for t in tokens], 'facetCount': len(facets),
               'renditionCount': len(items), 'pngExported': ok, 'facets': facets, 'renditions': items}, open(os.path.join(out, 'inventory.json'), 'w'), indent=1, ensure_ascii=False)
    print(f'facets {len(facets)} renditions {len(items)} png {ok} errors {sum(1 for i in items if "error" in i)}')

if __name__ == '__main__': main(sys.argv[1], sys.argv[2])
