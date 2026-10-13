#!/usr/bin/env python3
"""Summarise ui/view-trees into ui/ui-index.md: per screen/cell, custom classes, visible texts, button titles, images, actions."""
import glob, json, os, sys
root = sys.argv[1]; out = sys.argv[2]
lines = ['# Playback UI index (from compiled nibs/storyboards)', '',
         'Design-time data only: sizes are the archive design sizes, Auto Layout decides runtime geometry. See ui/view-trees for full trees.', '']
def walk(node, acc):
    if node.get('text'): acc['texts'].append(node['text'])
    for st in node.get('buttonStates', {}).values():
        if st.get('title'): acc['titles'].append(st['title'])
        if st.get('image'): acc['images'].append(st['image'])
    if node.get('image'): acc['images'].append(node['image'])
    acc['classes'][node['class']] = acc['classes'].get(node['class'], 0) + 1
    for s in node.get('subviews', []): walk(s, acc)
for path in sorted(glob.glob(os.path.join(root, '**', '*.tree.json'), recursive=True)):
    t = json.load(open(path)); rel = os.path.relpath(path, root)[:-len('.tree.json')]
    acc = {'texts': [], 'titles': [], 'images': [], 'classes': {}}
    for n in t['tree']: walk(n, acc)
    custom = sorted({v['custom'].split('8Playback')[-1].lstrip('0123456789') if v.get('custom') else None for v in t['classSwaps'].values()} - {None})
    actions = sorted({c['selector'] for c in t['connections'] if c['type'] == 'action' and c.get('selector')})
    outlets = sorted({c['label'] for c in t['connections'] if c['type'] == 'outlet' and c.get('label')})
    size = t['tree'][0].get('bounds', [0, 0, 0, 0])[2:] if t['tree'] else []
    lines += [f'## {rel}', f'- design size: {size}', f'- custom classes: {", ".join(custom) or "-"}', f'- texts: {" | ".join(dict.fromkeys(map(str, acc["texts"]))) or "-"}',
              f'- button titles: {" | ".join(dict.fromkeys(map(str, acc["titles"]))) or "-"}', f'- images: {", ".join(dict.fromkeys(map(str, acc["images"]))) or "-"}',
              f'- actions: {", ".join(actions) or "-"}', f'- outlets: {", ".join(outlets) or "-"}', '']
open(out, 'w').write('\n'.join(lines)); print(len(lines))
