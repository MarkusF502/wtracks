#!/usr/bin/env python3
"""Decode compiled Interface Builder archives ("NIBArchive") into JSON object graphs.

Usage: decode_nib.py <root> <out_dir>   (root: a .app directory or any directory containing .nib / .storyboardc)
Each archive becomes <out_dir>/<relative path>.json = {classes:[...], objects:[{id, class, values:{key:value}}], roots:[ids]}.
Object references are written as {"ref": id}. Floats/ints/bools/strings/bytes (hex) are decoded; nothing is guessed.
Format (reverse-engineered, as used by iOS 9+): header, then object / key / value / class tables; varints end on a byte
with the high bit set.
"""
import json, os, struct, sys

def varint(buf, pos):
    value = 0; shift = 0
    while True:
        b = buf[pos]; pos += 1
        value |= (b & 0x7F) << shift; shift += 7
        if b & 0x80: return value, pos

def decode(path):
    buf = open(path, 'rb').read()
    if buf[:10] != b'NIBArchive': raise ValueError('not a NIBArchive')
    v1, v2, oc, oo, kc, ko, vc, vo, cc, co = struct.unpack_from('<10I', buf, 10)
    # classes
    classes = []; pos = co
    for _ in range(cc):
        nlen, pos = varint(buf, pos); extra, pos = varint(buf, pos)
        pos += 4 * extra
        classes.append(buf[pos:pos + nlen].rstrip(b'\0').decode('utf8', 'replace')); pos += nlen
    keys = []; pos = ko
    for _ in range(kc):
        n, pos = varint(buf, pos); keys.append(buf[pos:pos + n].decode('utf8', 'replace')); pos += n
    values = []; pos = vo
    for _ in range(vc):
        k, pos = varint(buf, pos); t = buf[pos]; pos += 1
        if t == 0: val = struct.unpack_from('<b', buf, pos)[0]; pos += 1
        elif t == 1: val = struct.unpack_from('<h', buf, pos)[0]; pos += 2
        elif t == 2: val = struct.unpack_from('<i', buf, pos)[0]; pos += 4
        elif t == 3: val = struct.unpack_from('<q', buf, pos)[0]; pos += 8
        elif t == 4: val = True
        elif t == 5: val = False
        elif t == 6: val = round(struct.unpack_from('<f', buf, pos)[0], 6); pos += 4
        elif t == 7: val = struct.unpack_from('<d', buf, pos)[0]; pos += 8
        elif t == 8:
            n, pos = varint(buf, pos); raw = buf[pos:pos + n]; pos += n
            val = {'bytes': raw.hex()} if not raw or raw[0] in (0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07) or len(raw) > 4096 else _text(raw)
        elif t == 9: val = None
        elif t == 10: val = {'ref': struct.unpack_from('<I', buf, pos)[0]}; pos += 4
        else: raise ValueError(f'unknown value type {t} at {pos}')
        values.append((keys[k] if k < len(keys) else f'#{k}', val))
    objects = []; pos = oo
    for i in range(oc):
        ci, pos = varint(buf, pos); first, pos = varint(buf, pos); n, pos = varint(buf, pos)
        vals = {}
        for key, val in values[first:first + n]:
            name = key; j = 2
            while name in vals: name = f'{key}#{j}'; j += 1
            vals[name] = val
        objects.append({'id': i, 'class': classes[ci] if ci < len(classes) else f'#{ci}', 'values': vals})
    return {'version': [v1, v2], 'classes': classes, 'objects': objects}

def _text(raw):
    try:
        s = raw.decode('utf8')
        if all(c.isprintable() or c in '\n\t' for c in s): return s
    except UnicodeDecodeError: pass
    return {'bytes': raw.hex()}

def main(root, out):
    count = 0; failed = []
    for dirpath, dirs, files in os.walk(root):
        for f in files:
            if not f.endswith('.nib'): continue
            full = os.path.join(dirpath, f)
            rel = os.path.relpath(full, root)
            try: data = decode(full)
            except Exception as e: failed.append((rel, str(e))); continue
            target = os.path.join(out, rel + '.json'); os.makedirs(os.path.dirname(target), exist_ok=True)
            json.dump(data, open(target, 'w'), ensure_ascii=False, separators=(',', ':'))
            count += 1
    print(f'decoded {count} archives; failed {len(failed)}')
    for rel, e in failed[:20]: print(' ', rel, e)

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
