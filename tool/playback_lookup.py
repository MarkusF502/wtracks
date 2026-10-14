#!/usr/bin/env python3
"""Lookup over the full Ghidra export of the Playback executable.
usage: playback_lookup.py fn ADDR [depth]   -> pseudocode of ADDR and its callees up to depth (default 0)
       pb.py grep REGEX [max]  -> functions whose pseudocode matches
       pb.py callers ADDR      -> functions that call FUN_ADDR
"""
import json, os, pickle, re, sys, glob
# Export do executavel principal feito por ~/Playback/scripts/export_playback.py (Ghidra 12.1.4, lotes de 32 funcoes).
SRC = os.environ.get('PLAYBACK_EXPORT', '/home/marcos/Playback/analysis/decompiled/Playback/2a11a6f98134-2a4a38e34a84')
CACHE = os.environ.get('PLAYBACK_INDEX_CACHE', os.path.join(os.path.expanduser('~'), '.cache', 'playback_lookup.idx'))

def load():
    if os.path.exists(CACHE):
        with open(CACHE, 'rb') as f: return pickle.load(f)
    idx = {}
    for p in sorted(glob.glob(SRC + '/batch-*.json')):
        for r in json.load(open(p)):
            idx[r['address'].lower().lstrip('0')] = (r['name'], r.get('pseudocode') or '')
    os.makedirs(os.path.dirname(CACHE), exist_ok=True)
    with open(CACHE, 'wb') as f: pickle.dump(idx, f)
    return idx

def norm(a): return a.lower().replace('fun_', '').replace('0x', '').lstrip('0')

def main():
    idx = load(); cmd = sys.argv[1]
    if cmd == 'fn':
        depth = int(sys.argv[3]) if len(sys.argv) > 3 else 0
        seen = set(); frontier = [norm(sys.argv[2])]
        for d in range(depth + 1):
            nxt = []
            for a in frontier:
                if a in seen or a not in idx: continue
                seen.add(a); name, code = idx[a]
                print(f'// ===== {name} @ {a} (depth {d})\n{code}')
                nxt += [m.lower() for m in re.findall(r'FUN_([0-9a-fA-F]+)', code)]
            frontier = nxt
    elif cmd == 'grep':
        rx = re.compile(sys.argv[2]); mx = int(sys.argv[3]) if len(sys.argv) > 3 else 50; n = 0
        for a, (name, code) in idx.items():
            if rx.search(code):
                print(name, a); n += 1
                if n >= mx: break
    elif cmd == 'callers':
        t = 'FUN_' + norm(sys.argv[2])
        rx = re.compile(re.escape(t) + r'\b', re.I)
        for a, (name, code) in idx.items():
            if name.lower() != t.lower() and rx.search(code): print(name, a)

main()
