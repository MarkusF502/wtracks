#!/usr/bin/env python3
"""Decode a compiled Core Data .mom (NSKeyedArchiver) into entities/attributes/relationships JSON."""
import plistlib, sys, json

def load(path):
    d = plistlib.load(open(path, 'rb'))
    return d['$objects'], d['$top']

def resolve(objs, v, depth=0):
    if isinstance(v, plistlib.UID): v = objs[v.data]
    if depth > 6: return '<deep>'
    if isinstance(v, dict):
        if 'NS.keys' in v:
            return {resolve(objs, k, depth+1): resolve(objs, x, depth+1) for k, x in zip(v['NS.keys'], v['NS.objects'])}
        if 'NS.objects' in v:
            return [resolve(objs, x, depth+1) for x in v['NS.objects']]
        if 'NS.string' in v: return v['NS.string']
        return {k: resolve(objs, x, depth+1) for k, x in v.items() if k != '$class'}
    if isinstance(v, list): return [resolve(objs, x, depth+1) for x in v]
    if isinstance(v, bytes): return v.hex()[:40]
    return v

def main(path):
    objs, top = load(path)
    root = resolve(objs, top['root'], 0)
    ents = root.get('NSEntities', {}) if isinstance(root, dict) else {}
    out = {}
    for name, e in ents.items():
        props = e.get('NSProperties', {}) if isinstance(e, dict) else {}
        out[name] = {'class': e.get('NSClassNameForEntity'), 'parent': e.get('NSSuperentity'), 'props': {}}
        for pn, p in props.items():
            if not isinstance(p, dict): continue
            info = {'type': p.get('NSAttributeType'), 'optional': p.get('NSIsOptional') if 'NSIsOptional' in p else None,
                    'default': p.get('NSDefaultValue'), 'dest': p.get('NSDestinationEntityName'), 'toMany': p.get('NSMaxCount'),
                    'transient': p.get('NSIsTransient')}
            out[name]['props'][pn] = {k: v for k, v in info.items() if v is not None}
    json.dump(out, sys.stdout, indent=1, default=str)

if __name__ == '__main__':
    main(sys.argv[1])
