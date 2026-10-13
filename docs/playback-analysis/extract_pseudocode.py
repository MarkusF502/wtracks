#!/usr/bin/env python3
"""Collect Ghidra pseudocode of the Playback main executable by feature keyword.

Input : the Ghidra export profile directory (batch-*.json) produced by scripts/export_playback.py.
Output: pseudocode/<feature>.c (one file per feature) and pseudocode/index.json.
The pseudocode is raw decompiler output (Swift/ObjC, ARM64): names like FUN_xxxx are unnamed Swift functions. Treat it as
evidence, not as source. A function may appear under several features.
"""
import glob, json, re, sys, os, collections
profile = sys.argv[1]
out = sys.argv[2]
SHA = '2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423'
feat = {
 'guides': r'Guide|guide|CountIn|countIn|countOff|CountOff|dynamicGuide',
 'automation': r'Automation|automation',
 'transition': r'Transition(?!Layout|Coordinator|Context|Style|Duration)|transitionBeats|storedTransition|cueNextSong|stayInSong|ContinuePad|continuePad',
 'fade': r'[Ff]ade(?!d?In\b)|endFade|currentFadeVolume',
 'meters': r'VUMeter|vuMeter|[Pp]eakLevel|meterLevel|MeterStart|meterStartDate|averagePower|peakPower|[Mm]etering',
 'songmap': r'SongMap|songMap|SongTempo|SongClicks|SongSection\b|presetInfiniteLoop|loopInfinite|liveLoopCount',
 'mixer': r'MixerTrackFader|MixerMasterFader|BusChannel|MixerAVAudioUnit|faderDefaultLevel|songSpecific',
 'midi': r'MIDIBank|MIDIBus|MIDIEvent|ControlMapping|MIDIOutAVAudioUnit|MIDIClockAVAudioUnit',
}
rx = {k: re.compile(v) for k, v in feat.items()}
files = {k: open(os.path.join(out, k + '.c'), 'w') for k in feat}
for k, f in files.items():
    f.write(f'// Playback main executable sha256 {SHA}\n// Ghidra 12.1.4 decompiler output, feature "{k}": functions whose pseudocode matches /{feat[k]}/\n// Addresses are image-relative VM addresses as exported (e.g. 100545a98).\n\n')
index = collections.defaultdict(list)
for path in sorted(glob.glob(os.path.join(profile, 'batch-*.json'))):
    d = json.load(open(path))
    items = d if isinstance(d, list) else d.get('functions') or d.get('results') or []
    for x in items:
        if not isinstance(x, dict): continue
        code = x.get('pseudocode') or x.get('decompiled') or ''
        if not code: continue
        for k, r in rx.items():
            if r.search(code):
                files[k].write(f"// ==== {x['address']} {x.get('name')} ====\n{code.strip()}\n\n")
                index[k].append({'address': x['address'], 'name': x.get('name'), 'bytes': len(code)})
for f in files.values(): f.close()
json.dump({'binarySha256': SHA, 'features': index}, open(os.path.join(out, 'index.json'), 'w'), indent=1)
print({k: len(v) for k, v in index.items()})
