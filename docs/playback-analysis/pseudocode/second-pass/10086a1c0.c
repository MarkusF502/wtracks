// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 10086a1c0 0
// ===== FUN_10086a1c0 @ 10086a1c0 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_10086a1c0(uint param_1)

{
  code *pcVar1;
  long lVar2;
  ID IVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  ID IVar7;
  long unaff_x20;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  
  if (DAT_100adeca8 != -1) {
    _swift_once(&DAT_100adeca8,FUN_100224b00);
  }
  lVar2 = *(long *)(DAT_100b75a80 + 0x10);
  if ((lVar2 != 0) && (FUN_1004a9df0(), lVar2 != 0)) {
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar8 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar8 != 0) {
      _swift_retain(lVar8);
      FUN_1004f5388(0);
      _swift_release(lVar8);
    }
    FUN_100870798();
    if (*(char *)(lVar2 + _TtC8Playback4Song::isLiveCrossfading) == '\x01') {
      *(undefined1 *)(lVar2 + _TtC8Playback4Song::isLiveCrossfading) = 0;
    }
    lVar8 = _TtC8Playback23TransportViewController::fadeButton;
    IVar3 = unaff_x20 + _TtC8Playback23TransportViewController::fadeButton;
    _swift_unknownObjectWeakLoadStrong();
    if ((IVar3 != 0) && (IVar3 = _objc_msgSend(IVar3,"isSelected"), (int)IVar3 != 0)) {
      IVar3 = unaff_x20 + lVar8;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar3 != 0) {
        _objc_msgSend(IVar3,"setSelected:",0);
      }
      FUN_100867240();
      if ((*(long *)(DAT_100b75e40 + 0x20) != 0) &&
         (lVar8 = *(long *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::channelGroup)
         , lVar8 != 0)) {
        _swift_retain(lVar8);
        FUN_100647c80(0,0,0,param_1 & 1);
        _swift_release(lVar8);
      }
    }
    lVar8 = _TtC8Playback4Song::privateSongMap;
    lVar4 = *(long *)(lVar2 + _TtC8Playback4Song::privateSongMap);
    lVar12 = lVar4;
    if (lVar4 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar4 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar4 + 0x28) = 0;
      *(undefined8 *)(lVar4 + 0x20) = 0;
      *(undefined8 *)(lVar4 + 0x38) = 0;
      *(undefined8 *)(lVar4 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar4 + 0x10,lVar2);
      _swift_retain(puVar5);
      FUN_10085ee38();
      uVar6 = *(undefined8 *)(lVar2 + lVar8);
      *(long *)(lVar2 + lVar8) = lVar4;
      _swift_retain(lVar4);
      _swift_release(uVar6);
      lVar12 = 0;
    }
    uVar9 = *(ulong *)(lVar4 + 0x18);
    _swift_retain(lVar12);
    _swift_bridgeObjectRetain(uVar9);
    _swift_release(lVar4);
    if (uVar9 >> 0x3e == 0) {
      uVar10 = *(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar10 = uVar9 & 0xffffffffffffff8;
      if ((long)uVar9 < 0) {
        uVar10 = uVar9;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar10 != 0) {
      if ((long)uVar10 < 1) {
        (*pcVar1)();
      }
      _swift_bridgeObjectRetain(uVar9);
      uVar11 = 0;
      do {
        if ((uVar9 & 0xc000000000000001) == 0) {
          uVar13 = *(ulong *)(uVar9 + uVar11 * 8 + 0x20);
          _swift_retain(uVar13);
        }
        else {
          uVar13 = uVar11;
          FUN_1000cc314(uVar11,uVar9);
        }
        uVar11 = uVar11 + 1;
        *(undefined8 *)(uVar13 + _TtCC8Playback7SongMap7Element::liveLoopCount) = 0;
        IVar3 = _objc_msgSend(*(ID *)(uVar13 + _TtCC8Playback7SongMap7Element::section),
                              "presetInfiniteLoop");
        *(char *)(uVar13 + _TtCC8Playback7SongMap7Element::privateInfiniteLoop) = (char)IVar3;
        _swift_release(uVar13);
      } while (uVar10 != uVar11);
      _swift_bridgeObjectRelease(uVar9);
    }
    _swift_bridgeObjectRelease(uVar9);
    lVar2 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar2 != 0) {
      _swift_retain(lVar2);
      FUN_1004f1918();
      _swift_release(lVar2);
    }
    lVar2 = DAT_100b75e40;
    if (*(long *)(DAT_100b75e40 + 0x28) != 0) {
      _swift_retain(DAT_100b75e40);
      FUN_1002c4ea4(1);
      _swift_release(lVar2);
    }
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar9 = DAT_100b757a8;
    FUN_100170630();
    if ((((((uVar9 & 1) != 0) &&
          (uVar9 = DAT_100b757a8, FUN_1001736c4(),
          lVar2 = _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading, (uVar9 & 1) == 0)) &&
         (*(long *)(DAT_100b75e40 + 0x18) != 0)) &&
        ((lVar8 = *(long *)(*(long *)(DAT_100b75e40 + 0x18) + 0x18), lVar8 != 0 &&
         (lVar12 = *(long *)(lVar8 + _TtC8Playback16SongChannelGroup::midiOutChannel), lVar12 != 0))
        )) && (((*(byte *)(lVar12 + 0x40) & 1) == 0 &&
               (lVar4 = *(long *)(lVar12 + 0x38),
               *(char *)(lVar4 + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) == '\x01')))) {
      *(undefined1 *)(lVar12 + 0x40) = 1;
      *(undefined1 *)(lVar4 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = 1;
      _swift_retain(lVar8);
      _swift_retain(lVar12);
      FUN_10049ffc8();
      _swift_release(lVar12);
      _swift_release(lVar8);
      *(undefined1 *)(lVar4 + lVar2) = 0;
    }
    puVar5 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar3 = _objc_msgSend((ID)puVar5,"sharedApplication");
    IVar3 = _objc_msgSend(IVar3,"delegate");
    if (IVar3 != 0) {
      uVar6 = 0;
      FUN_100842dec(0);
      IVar7 = IVar3;
      _swift_dynamicCastClass(IVar3,uVar6);
      if (((IVar7 == 0) || (*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar7 = _objc_msgSend(*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window),
                                "rootViewController"), IVar7 == 0)) {
        _swift_unknownObjectRelease(IVar3);
        return IVar3;
      }
      uVar6 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar7,uVar6);
      if (IVar7 == 0) {
        _swift_unknownObjectRelease(IVar3);
      }
      else {
        _swift_unknownObjectRelease(IVar3);
        FUN_10009cf18();
      }
    }
    return 0;
  }
  return 0;
}


