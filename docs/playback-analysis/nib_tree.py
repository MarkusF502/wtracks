#!/usr/bin/env python3
"""Turn decoded NIBArchive JSON (scripts/decode_nib.py) into readable view trees.

Usage: nib_tree.py <decoded_dir> <out_dir>
For each archive: <out_dir>/<rel>.tree.json with the top-level objects, each view with class, geometry (bounds w/h and center in
the archive's design size), colors, fonts, texts, image names, custom class, constraint list and the outlet/action connections.
Geometry is the design-time frame; Auto Layout constraints decide the runtime layout, so both are kept.
"""
import json, os, struct, sys

ATTR = {1:'left',2:'right',3:'top',4:'bottom',5:'leading',6:'trailing',7:'width',8:'height',9:'centerX',10:'centerY',11:'baseline',12:'firstBaseline',13:'leftMargin',14:'rightMargin',15:'topMargin',16:'bottomMargin',17:'leadingMargin',18:'trailingMargin',19:'centerXWithinMargins',20:'centerYWithinMargins'}

def doubles(v):
    if isinstance(v, dict) and 'bytes' in v:
        raw = bytes.fromhex(v['bytes'])
        if raw[:1] == b'\x07' and (len(raw) - 1) % 8 == 0:
            return [round(x, 3) for x in struct.unpack('<%dd' % ((len(raw) - 1) // 8), raw[1:])]
    return None

def build(path):
    data = json.load(open(path)); O = data['objects']
    def ref(v): return O[v['ref']] if isinstance(v, dict) and 'ref' in v else None
    def text(v):
        o = ref(v)
        if o is None: return v
        if 'NS.bytes' in o['values']: return o['values']['NS.bytes']
        return None
    def color(v):
        o = ref(v)
        if not o: return None
        x = o['values']
        if 'UIRed' in x: return [x.get('UIRed'), x.get('UIGreen'), x.get('UIBlue'), x.get('UIAlpha')]
        if 'UIWhite' in x: return [x['UIWhite'], x['UIWhite'], x['UIWhite'], x.get('UIAlpha', 1)]
        if 'UISystemColorName' in x: return text(x['UISystemColorName'])
        return None
    def font(v):
        o = ref(v)
        if not o: return None
        x = o['values']; return {'name': text(x.get('UIFontName')), 'size': x.get('UIFontPointSize'), 'system': x.get('UISystemFont')}
    def array(v):
        o = ref(v)
        if not o: return []
        out = []; seen = 0
        for k, item in o['values'].items():
            if k.startswith('UINibEncoderEmptyKey') or k == 'NS.objects' or k.startswith('NS.object'): out.append(item)
        return out
    def view(o, depth=0):
        x = o['values']; node = {'id': o['id'], 'class': o['class']}
        b = doubles(x.get('UIBounds')); c = doubles(x.get('UICenter'))
        if b: node['bounds'] = b
        if c: node['center'] = c
        for key, name in (('UIBackgroundColor', 'background'), ('UITextColor', 'textColor'), ('UITintColor', 'tint')):
            if key in x: node[name] = color(x[key])
        for key, name in (('UIAlpha', 'alpha'), ('UIHidden', 'hidden'), ('UITag', 'tag'), ('UIUserInteractionDisabled', 'userInteractionDisabled'), ('UIClipsToBounds', 'clips')):
            if key in x: node[name] = x[key]
        if 'UIText' in x: node['text'] = text(x['UIText'])
        if 'UIFont' in x: node['font'] = font(x['UIFont'])
        if 'UIAccessibilityLabel' in x: node['accessibilityLabel'] = text(x['UIAccessibilityLabel'])
        if 'UIImage' in x:
            node['image'] = text((ref(x['UIImage']) or {'values': {}})['values'].get('UIResourceName')) if ref(x['UIImage']) else None
        if 'UIButtonStatefulContent' in x:
            states = {}
            sc = ref(x['UIButtonStatefulContent'])
            for k, v in (sc['values'].items() if sc else []):
                bc = ref(v)
                if bc and bc['class'] == 'UIButtonContent':
                    bx = bc['values']; states[k] = {'title': text(bx.get('UITitle')), 'titleColor': color(bx.get('UITitleColor')), 'image': text((ref(bx.get('UIImage')) or {'values': {}})['values'].get('UIResourceName')) if bx.get('UIImage') else None}
            node['buttonStates'] = states
        constraints = []
        for item in array(x.get('UIViewAutolayoutConstraints')):
            c = ref(item)
            if c and c['class'] == 'NSLayoutConstraint':
                cv = c['values']; first = ref(cv.get('NSFirstItem')); second = ref(cv.get('NSSecondItem'))
                constraints.append({'first': first['id'] if first else None, 'firstAttr': ATTR.get(cv.get('NSFirstAttribute'), cv.get('NSFirstAttribute')),
                                    'relation': cv.get('NSRelation', 0), 'second': second['id'] if second else None, 'secondAttr': ATTR.get(cv.get('NSSecondAttribute'), cv.get('NSSecondAttribute')),
                                    'multiplier': cv.get('NSMultiplier', 1.0), 'constant': cv.get('NSConstant', 0.0), 'priority': cv.get('NSPriority', 1000)})
        if constraints: node['constraints'] = constraints
        subs = [view(ref(s), depth + 1) for s in array(x.get('UISubviews')) if ref(s) and depth < 40]
        if subs: node['subviews'] = subs
        return node
    top = ref(O[0]['values'].get('UINibObjectsKey'))
    result = {'tree': [], 'connections': [], 'classSwaps': {}}
    if top:
        for item in array(O[0]['values']['UINibObjectsKey']):
            o = ref(item)
            if o and o['class'] not in ('UIProxyObject',): result['tree'].append(view(o))
    for o in O:
        if o['class'] == 'UIClassSwapper':
            x = o['values']; result['classSwaps'][str(ref(x.get('UIOriginalClassName')) and 'obj') if False else str(o['id'])] = {'custom': text(x.get('UIClassName')), 'original': text(x.get('UIOriginalClassName'))}
        elif o['class'] == 'UIRuntimeOutletConnection':
            x = o['values']; s, d = ref(x.get('UISource')), ref(x.get('UIDestination'))
            result['connections'].append({'type': 'outlet', 'label': text(x.get('UILabel')), 'source': s['id'] if s else None, 'destination': d['id'] if d else None})
        elif o['class'] == 'UIRuntimeEventConnection':
            x = o['values']; s, d = ref(x.get('UISource')), ref(x.get('UIDestination'))
            result['connections'].append({'type': 'action', 'selector': text(x.get('UILabel')), 'eventMask': x.get('UIEventMask'), 'source': s['id'] if s else None, 'target': d['id'] if d else None})
    return result

def main(src, out):
    n = 0
    for dirpath, _, files in os.walk(src):
        for f in files:
            if not f.endswith('.nib.json'): continue
            full = os.path.join(dirpath, f); rel = os.path.relpath(full, src)
            tree = build(full)
            target = os.path.join(out, rel[:-len('.nib.json')] + '.tree.json'); os.makedirs(os.path.dirname(target), exist_ok=True)
            json.dump(tree, open(target, 'w'), ensure_ascii=False, indent=None, separators=(',', ':')); n += 1
    print('trees', n)

if __name__ == '__main__': main(sys.argv[1], sys.argv[2])
