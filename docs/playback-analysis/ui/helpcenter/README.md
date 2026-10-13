# Playback user guide (MultiTracks help center) — reference catalog

Source: https://helpcenter.multitracks.com/pt-BR/articles/4944485-guia-do-usuario-do-playback (fetched 2026-10-13).
`article.txt` is the article text in reading order, with each image or video placed where it appears (signed URL query
strings stripped). The images here are downscaled copies, kept for layout reference only. `frames/` holds contact sheets
(one frame every 7 s) of the six Vimeo videos, plus 1.5 s sheets of the two GIFs. The screenshots show Playback 7.x on iPad.
They are newer than the storyboards in `../view-trees` only for some items, so where they disagree with the binary
(8.5.3), the binary wins for behaviour and these images win for appearance.

## Screens and what they show

| File | Screen |
|---|---|
| 04, 05–08 | Main screen (single window): top bar, setlist row, waveform, mixer + console + Master |
| 10, 11 | "Add a Song" popover (search; All Songs, Library, Click & Pad, Ambient Pads, Soundbeds) and song detail (Arrangement, Product, Tracks, Key, Tempo, Start Point) with "Add" |
| 12 | Setlist edit mode with one song: card with (−) and (…), (+) to its right; sections with (−) |
| 13, 14 | Setlist button popover "Setlists": New Setlist, Open Setlist, current setlist (art, date, songs, length), Save As New; setlist detail with "Load" |
| 16 | Long press on EDIT: Setlist / MIDI Cues / MIDI Mapping / Cloud Song Sections |
| 17 | Setlist edit mode: EDIT becomes DONE; cards get (−), (…) and (+) between cards; sections get (−) on the badge and (+) at the right edge |
| 18 | Transition menu from the badge between cards: Cue Next Song, Stay In Song, Continue Pad (switch), AutoLink, Overlap, Crossfade |
| 19, 20 | Song edit popover from (…): Arrangements, Content/Tracks, Key & Tempo, Duration (Start/End Point, 5 Second Fade Out), Pad Player, MIDI Out (Lyrics Bus, ProPresenter Playlist/Item) |
| 21–25 | MIDI Cues edit mode: top-left becomes ◁ ··· ▷ (previous cue, cue menu, next cue); (+) on the playhead adds a cue; orange cue flags "Note, G-1, 1" and orange triangles under the waveform; "Add MIDI Cue" (Bus, Message, Value, Velocity, Disable Loop, Description); cue menu Edit / Nudge / Delete; section badge menu Copy / Paste Section Cues |
| 26, 27 | MIDI Mapping mode: whole UI tinted blue, every mappable control highlighted; top-left buttons previous song, previous section, confirm, next section, next song |
| 28–33 | Song Sections edit mode: ◁ ··· ▷ with Edit / Move / Delete Song Section; dialog Song Section (type), Marker Location Bar / Timecode, Delete Section Marker; "the first section cannot be moved" |
| 34 | Settings, General tab: two columns of grouped switches (Auto Pan, Click Sound, Count Into Each Section, Song Section Pre-roll, Guide Cue Language, Song Specific Buses, Reference Track, Default Ambient Pad / Audio Device, Waveform Grid, Metronome Style VU, Song Specific Master Fader, Fader Default Level 80%, Power Saver, MIDI Out, Start Pad Player with Songs); tabs General, Tracks, Buses, MIDI, About; close (x) |
| 35 | About tab (logo, version, buttons) |
| 37–39 | Buses tab: list of buses with their output ("1/2", "3", "4"), "Select Output" picker (1, 2, 3, 4, 1/2, 3/4); swipe → Edit → "Edit Bus Name and Abbreviation" (GIF 38) |
| 40, 41 | MIDI tab: MIDI buses (Lyrics, Lights 1/2, Patches 1/2, Guitar, Aux 1/2) with a coloured triangle, port, channel and switch; MIDI Clock → Select Ports (Network Session / hardware ports, Select All) |
| frames/202233533 | "Get Started": library popover (Songs, Artists, Albums, Themes, Genres, Recent), Select Key, Pads list, Select Tracks (checkbox list), song popover with tempo wheel; waveform coloured blue |
| frames/503075860 | Pad Player: console toggle shows a pad pane (pad name, LINK, 12 key buttons) |

## Measured colours (screenshot 04, iPad)

Top bar / setlist / mixer background `#1E2021`; buttons `#131516` (darker than the background, 1 px `#1E2021` edge);
waveform area `#151617` (matches `#151618` in the storyboards); section fill = section colour at ~10 % over the waveform
area; waveform tinted to the section (`#A8A0A8` in a verse, `#A1A9AB` in the intro); section badge rings: Intro `#5DA4B5`,
Verse `#92278F`, Count-off `#A0A0A0`, Chorus orange (screenshot 8e0c8bcd); fader cap `#111415` with `#5CB8CF` line; fader
ticks `#494B4C`; fader slot black; PAD text `#43A86C`; fade icon `#919191`; EDIT text `#808080`; time sub-line `#AAAAAA`;
track labels white; the active song title bold white with a green outlined ▷.

## Behaviour described by the guide (relevant to WTracks)

- Top bar: tempo/meter (changes live with the tempo map); time display (tap = start/end time of the song); PAD on/off;
  Back to Start; Play/Pause; Fade (fades tracks out *and back in*; click, guide and pad keep playing); EDIT (tap = setlist
  edit, hold = mode menu); Setlists menu; More menu → settings.
- Setlist row: tap a card while stopped selects and cues it; double tap while playing crossfades into it.
- Transitions: Cue Next Song; Stay In Song; AutoLink (next song starts immediately); Overlap (last 5 s: next starts at
  full level, current ends without fading); Crossfade (last 5 s: next fades in while current fades out).
- Waveform: scrolls under a fixed playhead; Live ReOrder = double tap a section badge to jump there when the current
  section ends; loop icon on a section = single loop of that section; in setlist edit mode the loop icon toggles the preset
  infinite loop, (−)/(+) delete/add sections (arrangement editing); optional bar/beat grid ("Waveform Grid", also snapping).
- Mixer: console top button toggles Tracks / Buses / Pad Player (and Waveform on iPhone); faders change on press-and-drag;
  tap the track or bus name to mute (a muted bus mutes its tracks); hold the Click fader to expand Accent / 1/4 / 1/8 / 1/16
  faders; Master is global unless "Song Specific Master Fader".
- Console: MUTE MIDI (temporarily stops sending MIDI cues); Loop (arms a single loop of the current section, then
  disarms); Infinite Loop (loops the current section until pressed again).
- Mac keyboard: Space play/pause, P pad, F fade, L loop, I infinite loop, ←/→ browse sections, Return confirm reorder,
  number keys select (stopped) or crossfade (playing) to that song.
