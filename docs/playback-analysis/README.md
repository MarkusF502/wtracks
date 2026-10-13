# Playback 8.5.3 — evidence for the reconstruction

Everything here was produced from the shipped iOS package (`Playback.app`, main executable SHA-256
`2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423`) with Ghidra 12.1.4 / REA 6.4.0 and the scripts in this folder.
Nothing was executed on iOS. This is evidence, not source: names like `FUN_100545a98` are unnamed Swift functions, and every
"inferred" statement in the other documents is marked as such. Cloud/account/purchase features are out of scope.

| Path | What it is |
|---|---|
| `playback-feature-inventory.md` | Feature list with evidence, status in WTracks and what is still missing — **start here** |
| `coredata-model-145.json` | Decoded Core Data model (39 entities, latest version 145) — the real data model of songs, sections, tempos, automation, MIDI, routing |
| `subsystem-contracts.md` / `.json` | Per-framework contracts (Click, Guide, Automation, MIDIOut, MIDIClock, Mixer, BusChannel, Timecode, Looping) with addresses, hashes and proposed tests |
| `timepitch-contract.md`, `click-songmap-findings.md` | Time/pitch (Élastique) and click-agenda findings |
| `main-ui-strings.txt` | 1472 user-visible strings of the app (feature names, settings, error texts, help texts) |
| `pseudocode/<feature>.c` | Ghidra pseudocode of every main-executable function whose body matches the feature keywords: `guides`, `automation`, `transition`, `fade`, `meters`, `songmap`, `mixer`, `midi` (a function can appear in several files; `index.json` lists addresses) |
| `pseudocode/frameworks/*.c` | All decompiled functions of the audio-unit frameworks (Click, Guide, Automation, MIDIOut, MIDIClock, Mixer, BusChannel, Timecode, Looping, BufferedFilePlayback, SineWave, TPCircularBuffer) |
| `ui/ui-index.md` | One entry per screen/cell: custom classes, visible texts, button titles, image names, actions, outlets |
| `ui/view-trees/**.tree.json` | Decoded view hierarchies of 208 compiled nib/storyboard archives: class, design bounds/center, colours, fonts, texts, button states, images, constraints, outlet/action connections |
| `ui/nib-raw/**.json` | Lossless object tables of the same archives (class + key/value per object) |
| `ui/plists/*.json` | `Info.plist` of the app and of each storyboard (scene graph / segue info) |
| `ui/assets/inventory.json` | Every rendition of `Assets.car` (184 facets, 1295 renditions): name, size, scale, pixel format, key attributes, colours |
| `ui/assets/png`, `ui/assets/data` | 55 bitmaps (palette+LZFSE) and 232 vector/data assets (SVG, PDF, JPEG) exported from `Assets.car` |

## How to read the pseudocode

1. Find the class/selector names in `main-ui-strings.txt`, `coredata-model-145.json` and the `ObjC` names that appear in the C files
   (`_TtC8Playback…::method`, `_objc_msgSend(x,"selector")`).
2. Swift functions are `FUN_<address>`; follow calls by address. `index.json` gives sizes so you can start with small functions.
3. Treat constants as observations (e.g. `0x40e5888000000000` is the double 44100.0), not as design intent.

## Limits

- Pseudocode selection is keyword based and overlapping; it is not a complete map of the app.
- Nib geometry is the design-time frame; Auto Layout constraints (kept in the trees) decide runtime layout. Pixel-exact layout is not claimed.
- `Assets.car`: 227 renditions use the tiled "deepmap" compression (ids 10/11, `KCBC`) and are listed in the inventory with an error
  but not decoded; 773 entries are size-only references. Colours (`RLOC`) are in the inventory.
- One main-executable function failed to decompile (`0x100194a54`, "Unable to find unique hash for varnode").

## Regenerating (needs the original package; the cloud environment does not have it)

```
python3 decode_momd.py "AppData.momd/AppData 145.mom" > coredata-model-145.json
python3 decode_nib.py Playback.app ui/nib-raw && python3 nib_tree.py ui/nib-raw ui/view-trees && python3 ui_index.py ui/view-trees ui/ui-index.md
pip install lzfse   # PYTHONPATH must see it
python3 decode_car.py Playback.app/Assets.car ui/assets
python3 extract_pseudocode.py <ghidra export profile dir> pseudocode
```
