// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 100647514 0
// ===== FUN_100647514 @ 100647514 (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100647514(uint param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  class_t *pcVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  undefined *puVar8;
  class_t *pcVar9;
  class_t *pcVar10;
  class_rw_t *pcVar11;
  long lVar12;
  long unaff_x20;
  undefined *puVar13;
  long lVar14;
  undefined8 uVar15;
  long *plVar16;
  code *pcVar17;
  
  puVar13 = *(undefined **)(unaff_x20 + _TtC8Playback16SongChannelGroup::allChannels);
  lVar12 = *(long *)(puVar13 + 0x10);
  if (lVar12 == 0) {
    _swift_bridgeObjectRetain(puVar13);
  }
  else {
    _swift_bridgeObjectRetain_n(puVar13,2);
    plVar16 = (long *)(puVar13 + 0x28);
    do {
      lVar3 = plVar16[-1];
      lVar5 = *plVar16;
      lVar7 = lVar3;
      _swift_getObjectType();
      pcVar17 = *(code **)(lVar5 + 0x18);
      _swift_unknownObjectRetain(lVar3);
      (*pcVar17)(lVar7,lVar5);
      if (lVar7 != 0) {
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
        if ((*(byte *)(lVar7 + _TtC8Playback9SongTrack::soloState) & 1) == 0) {
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          _swift_bridgeObjectRelease_n(puVar13,2);
          _swift_unknownObjectRetain(lVar3);
          FUN_1006549a0();
          _swift_unknownObjectRelease(lVar3);
          puVar13 = puVar8;
          goto LAB_100647668;
        }
      }
      _swift_unknownObjectRelease(lVar3);
      plVar16 = plVar16 + 2;
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    _swift_bridgeObjectRelease(puVar13);
  }
LAB_100647668:
  lVar12 = *(long *)(puVar13 + 0x10);
  if (lVar12 != 0) {
    puVar8 = puVar13;
    _swift_bridgeObjectRetain();
    plVar16 = (long *)(puVar8 + 0x28);
    do {
      lVar3 = plVar16[-1];
      lVar5 = *plVar16;
      lVar7 = lVar3;
      _swift_getObjectType();
      pcVar17 = *(code **)(lVar5 + 0x18);
      _swift_unknownObjectRetain(lVar3);
      (*pcVar17)(lVar7,lVar5);
      if ((lVar7 == 0) ||
         (puVar1 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::currentFade),
         *(char *)(puVar1 + 2) == -1)) {
        _swift_unknownObjectRelease(lVar3);
      }
      else {
        uVar15 = *puVar1;
        uVar6 = puVar1[1];
        puVar2 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::fadeStartTimecode);
        *puVar2 = 0;
        *(undefined1 *)(puVar2 + 1) = 1;
        *puVar1 = 0;
        puVar1[1] = 0;
        *(undefined1 *)(puVar1 + 2) = 0xff;
        FUN_100033784(uVar15,uVar6);
        puVar1 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::currentFadeVolume);
        *puVar1 = 0;
        *(undefined1 *)(puVar1 + 1) = 1;
        lVar5 = _TtC8Playback9SongTrack::fadeWorkItem;
        lVar14 = *(long *)(lVar7 + _TtC8Playback9SongTrack::fadeWorkItem);
        uVar15 = 0;
        if (lVar14 != 0) {
          _swift_retain(lVar14);
          __s8Dispatch0A8WorkItemC6cancelyyFTj();
          _swift_release(lVar14);
          uVar15 = *(undefined8 *)(lVar7 + lVar5);
        }
        *(undefined8 *)(lVar7 + lVar5) = 0;
        _swift_unknownObjectRelease(lVar3);
        _swift_release(uVar15);
      }
      plVar16 = plVar16 + 2;
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    _swift_bridgeObjectRelease(puVar13);
    lVar12 = *(long *)(puVar13 + 0x10);
    if (lVar12 != 0) {
      plVar16 = (long *)(puVar13 + 0x28);
      do {
        pcVar4 = (class_t *)plVar16[-1];
        lVar3 = *plVar16;
        pcVar9 = pcVar4;
        _object_getClass();
        if (pcVar9 == &objc::class_t::_TtC8Playback14MIDIOutChannel && pcVar4 != (class_t *)0x0) {
          if ((param_1 & 1) != 0) {
            *(undefined1 *)(pcVar4[1].cache + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) = 1;
          }
        }
        else {
          pcVar9 = pcVar4;
          _swift_getObjectType();
          pcVar17 = *(code **)(lVar3 + 0x20);
          _swift_unknownObjectRetain(pcVar4);
          pcVar10 = pcVar9;
          (*pcVar17)(pcVar9,lVar3);
          if (((((ulong)pcVar10 & 1) == 0) &&
              (pcVar10 = pcVar9, (**(code **)(lVar3 + 0x28))(pcVar9,lVar3),
              ((ulong)pcVar10 & 1) == 0)) &&
             (pcVar10 = pcVar9, (**(code **)(lVar3 + 0x30))(pcVar9,lVar3), ((ulong)pcVar10 & 1) == 0
             )) {
            (**(code **)(lVar3 + 0x38))(pcVar9,lVar3);
            if ((((ulong)pcVar9 & 1) == 0) || ((param_1 & 1) != 0)) {
              pcVar9 = pcVar4;
              _swift_getObjectType();
              _swift_conformsToProtocol();
              if ((pcVar9 != (class_t *)0x0) && (pcVar4 != (class_t *)0x0)) {
                pcVar10 = pcVar4;
                _swift_getObjectType(pcVar4);
                pcVar11 = pcVar9[2].data;
                _swift_unknownObjectRetain(pcVar4);
                (*(code *)pcVar11)(1,pcVar10,pcVar9);
                (*(code *)pcVar9->superclass->data)(pcVar10);
                FUN_1006513dc(pcVar4,lVar3,param_1 & 1);
                _swift_unknownObjectRelease_n(pcVar4,2);
                goto LAB_1006477d0;
              }
            }
          }
          else {
            (**(code **)(lVar3 + 0x38))(pcVar9,lVar3);
          }
          _swift_unknownObjectRelease(pcVar4);
        }
LAB_1006477d0:
        plVar16 = plVar16 + 2;
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
    }
  }
  _swift_bridgeObjectRelease(puVar13);
  return;
}


