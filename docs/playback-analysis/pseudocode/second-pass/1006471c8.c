// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1006471c8 0
// ===== FUN_1006471c8 @ 1006471c8 (depth 0)

void FUN_1006471c8(byte param_1)

{
  ulong uVar1;
  code *pcVar2;
  uint uVar3;
  class_t *pcVar4;
  class_t *pcVar5;
  class_t *pcVar6;
  long lVar7;
  undefined1 *puVar8;
  ulong uVar9;
  long lVar10;
  long unaff_x20;
  long lVar11;
  ID self;
  class_t *pcVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined4 uVar16;
  undefined1 auStack_98 [24];
  
  pcVar6 = (class_t *)PTR___swiftEmptyArrayStorage_100a1e050;
  lVar11 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::allChannels);
  lVar14 = *(long *)(lVar11 + 0x10);
  if (lVar14 == 0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    _swift_bridgeObjectRetain_n(lVar11,2);
    pcVar6 = (class_t *)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    lVar15 = 0x20;
    do {
      pcVar12 = *(class_t **)(lVar11 + lVar15);
      pcVar5 = pcVar12;
      _object_getClass();
      if (pcVar5 == &objc::class_t::_TtC8Playback12ClickChannel && pcVar12 != (class_t *)0x0) {
        _swift_unknownObjectRetain(pcVar12);
        pcVar5 = pcVar6;
        _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
        if ((((int)pcVar5 == 0) || ((long)pcVar6 < 0)) ||
           (pcVar5 = pcVar6, ((ulong)pcVar6 >> 0x3e & 1) != 0)) {
          if ((ulong)pcVar6 >> 0x3e == 0) {
            pcVar4 = *(class_t **)(((ulong)pcVar6 & 0xfffffffffffff8) + 0x10);
          }
          else {
            pcVar4 = (class_t *)((ulong)pcVar6 & 0xffffffffffffff8);
            if ((long)pcVar6 < 0) {
              pcVar4 = pcVar6;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg(pcVar4);
          }
          pcVar5 = (class_t *)0x0;
          FUN_10078f044(0,(undefined1 *)((long)&pcVar4->isa + 1),1,pcVar6);
        }
        uVar9 = (ulong)pcVar5 & 0xffffffffffffff8;
        uVar1 = *(ulong *)(uVar9 + 0x10);
        pcVar6 = pcVar5;
        if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar1) {
          pcVar6 = (class_t *)(ulong)(1 < *(ulong *)(uVar9 + 0x18));
          FUN_10078f044(pcVar6,uVar1 + 1,1,pcVar5);
          uVar9 = (ulong)pcVar6 & 0xffffffffffffff8;
        }
        *(ulong *)(uVar9 + 0x10) = uVar1 + 1;
        *(class_t **)(uVar9 + uVar1 * 8 + 0x20) = pcVar12;
      }
      lVar15 = lVar15 + 0x10;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    _swift_bridgeObjectRelease_n(lVar11,2);
  }
  if ((ulong)pcVar6 >> 0x3e == 0) {
    pcVar5 = *(class_t **)(((ulong)pcVar6 & 0xfffffffffffff8) + 0x10);
  }
  else {
    pcVar5 = (class_t *)((ulong)pcVar6 & 0xffffffffffffff8);
    if ((long)pcVar6 < 0) {
      pcVar5 = pcVar6;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (pcVar5 == (class_t *)0x0) {
    _swift_bridgeObjectRelease();
  }
  else {
    if ((long)pcVar5 < 1) {
      (*pcVar2)();
    }
    _swift_bridgeObjectRetain(pcVar6);
    lVar14 = 0x20;
    do {
      lVar13 = *(long *)((long)&pcVar6->isa + lVar14);
      *(undefined1 *)(lVar13 + 0x68) = 0;
      lVar11 = _TtC8Playback16ClickAVAudioUnit::muteState;
      lVar10 = *(long *)(lVar13 + 0x60);
      *(undefined1 *)(lVar10 + _TtC8Playback16ClickAVAudioUnit::muteState) = 0;
      lVar15 = _TtC8Playback16ClickAVAudioUnit::parameters;
      puVar8 = auStack_98;
      _swift_beginAccess(lVar10 + _TtC8Playback16ClickAVAudioUnit::parameters,puVar8,0x20,0);
      lVar15 = *(long *)(lVar10 + lVar15);
      if (*(long *)(lVar15 + 0x10) == 0) {
LAB_100647354:
        _swift_endAccess(auStack_98);
        _swift_retain(lVar13);
      }
      else {
        lVar7 = 1;
        thunk_FUN_100793c60();
        if (((ulong)puVar8 & 1) == 0) goto LAB_100647354;
        self = *(ID *)(*(long *)(lVar15 + 0x38) + lVar7 * 8);
        _swift_endAccess(auStack_98);
        uVar16 = 0;
        if (*(char *)(lVar10 + lVar11) == '\0') {
          uVar16 = 0x3f800000;
        }
        _swift_retain(lVar13);
        _objc_msgSend(self,"setValue:",uVar16);
      }
      *(byte *)(lVar13 + _TtC8Playback12ClickChannel::currentElementIsLastSongMapElementEnding) =
           param_1 & 1;
      _swift_release(lVar13);
      lVar14 = lVar14 + 8;
      pcVar5 = (class_t *)((long)&pcVar5[-1].data + 7);
    } while (pcVar5 != (class_t *)0x0);
    _swift_bridgeObjectRelease_n(pcVar6,2);
  }
  if ((param_1 & 1) == 0) {
    pcVar5 = *(class_t **)(unaff_x20 + _TtC8Playback16SongChannelGroup::dynamicGuideChannel);
    if ((pcVar5 != (class_t *)0x0) &&
       (pcVar6 = pcVar5, _object_getClass(), pcVar6 == &objc::class_t::_TtC8Playback12GuideChannel))
    {
      *(undefined1 *)&pcVar5[2].data = 0;
      _swift_unknownObjectRetain(pcVar5);
      FUN_100719fc8();
      _swift_unknownObjectRelease();
      pcVar6 = pcVar5;
    }
    FUN_10064c46c();
    if (pcVar6 != (class_t *)0x0) {
      pcVar5 = pcVar6;
      _object_getClass();
      if (pcVar5 == &objc::class_t::_TtC8Playback12TrackChannel) {
        *(undefined1 *)&pcVar6[2].vtable = 0;
        uVar3 = (uint)pcVar6->cache;
        FUN_10056fe0c();
        if ((uVar3 & 0xff) == 8) {
          FUN_1001c4398();
        }
      }
      _swift_unknownObjectRelease(pcVar6);
    }
  }
  return;
}


