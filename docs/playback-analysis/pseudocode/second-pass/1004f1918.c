// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1004f1918 0
// ===== FUN_1004f1918 @ 1004f1918 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ulong FUN_1004f1918(double param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  undefined *puVar4;
  ID IVar5;
  ID IVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  void *aBlock;
  undefined8 *puVar10;
  undefined8 *puVar11;
  long *plVar12;
  long *plVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long unaff_x20;
  ulong uVar17;
  ulong uVar18;
  long lVar19;
  code *pcVar20;
  long lVar21;
  long *plVar22;
  ID IVar23;
  long lVar24;
  long lVar25;
  ulong uVar26;
  ID self;
  long lVar27;
  double dVar28;
  double dVar29;
  code *local_130;
  long local_128;
  long local_120;
  long local_118;
  long local_110;
  undefined *local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  code *local_a8;
  undefined8 uStack_a0;
  long local_98 [3];
  
  lVar2 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar27 = *(long *)(lVar2 + -8);
  lVar21 = (long)&local_130 - (*(long *)(lVar27 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar14 = *(long *)(lVar3 + -8);
  lVar15 = lVar21 - (*(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar4 = &DAT_100af5490;
  FUN_100021774();
  lVar25 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar16 = lVar15 - (*(long *)(*(long *)(puVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  self = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::song);
  IVar23 = *(ID *)(self + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar23 == 0) {
    IVar5 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar5 == 0) {
      return 0;
    }
    IVar6 = IVar5;
    FUN_10032ee88();
    IVar23 = IVar6;
    FUN_1005e3b94(IVar6,IVar5);
    _swift_bridgeObjectRelease(IVar6);
    if (IVar23 == 0) {
      return 0;
    }
    *(ID *)(self + lVar25) = IVar23;
  }
  lVar25 = _TtC8Playback4Song::privateSongMap;
  lVar19 = *(long *)(self + _TtC8Playback4Song::privateSongMap);
  lVar24 = lVar19;
  if (lVar19 == 0) {
    lVar19 = 0;
    FUN_100861310();
    _swift_allocObject();
    puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
    *(undefined **)(lVar19 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
    param_1 = 0.0;
    *(undefined8 *)(lVar19 + 0x28) = 0;
    *(undefined8 *)(lVar19 + 0x20) = 0;
    *(undefined8 *)(lVar19 + 0x38) = 0;
    *(undefined8 *)(lVar19 + 0x30) = 0;
    _swift_unknownObjectUnownedInit(lVar19 + 0x10,self);
    _swift_retain(puVar4);
    FUN_10085ee38();
    uVar9 = *(undefined8 *)(self + lVar25);
    *(long *)(self + lVar25) = lVar19;
    _swift_retain(lVar19);
    _swift_release(uVar9);
    lVar24 = 0;
  }
  uVar18 = *(ulong *)(lVar19 + 0x18);
  _swift_retain(lVar24);
  _swift_bridgeObjectRetain(uVar18);
  _swift_release(lVar19);
  if (uVar18 >> 0x3e == 0) {
    uVar17 = *(ulong *)((uVar18 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar17 = uVar18 & 0xffffffffffffff8;
    if ((long)uVar18 < 0) {
      uVar17 = uVar18;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  _swift_bridgeObjectRelease(uVar18);
  if (uVar17 == 0) {
    return 0;
  }
  lVar19 = *(long *)(self + lVar25);
  lVar24 = lVar19;
  if (lVar19 == 0) {
    FUN_100861310();
    _swift_allocObject();
    puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
    *(undefined **)(lVar19 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
    param_1 = 0.0;
    *(undefined8 *)(lVar19 + 0x28) = 0;
    *(undefined8 *)(lVar19 + 0x20) = 0;
    *(undefined8 *)(lVar19 + 0x38) = 0;
    *(undefined8 *)(lVar19 + 0x30) = 0;
    _swift_unknownObjectUnownedInit(lVar19 + 0x10,self);
    _swift_retain(puVar4);
    FUN_10085ee38();
    uVar9 = *(undefined8 *)(self + lVar25);
    *(long *)(self + lVar25) = lVar19;
    _swift_retain(lVar19);
    _swift_release(uVar9);
    lVar24 = 0;
  }
  uVar18 = *(ulong *)(lVar19 + 0x18);
  _swift_retain(lVar24);
  _swift_bridgeObjectRetain(uVar18);
  _swift_release(lVar19);
  if (uVar18 >> 0x3e == 0) {
    uVar17 = *(ulong *)((uVar18 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar17 = uVar18 & 0xffffffffffffff8;
    if ((long)uVar18 < 0) {
      uVar17 = uVar18;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar17 == 0) {
    _swift_bridgeObjectRelease(uVar18);
    return uVar18;
  }
  if ((uVar18 & 0xc000000000000001) == 0) {
    if (*(long *)((uVar18 & 0xfffffffffffff8) + 0x10) == 0) {
      (*pcVar20)();
    }
    lVar24 = *(long *)(uVar18 + 0x20);
    _swift_retain(lVar24);
  }
  else {
    lVar24 = 0;
    FUN_1000cc314(0,uVar18);
  }
  _swift_bridgeObjectRelease(uVar18);
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEnd) = 0;
  local_98[0] = lVar24;
  FUN_1000345bc(0);
  dVar29 = param_1;
  _objc_msgSend(IVar23,"storedStartTime");
  dVar28 = dVar29;
  IVar23 = _objc_msgSend(IVar23,"song");
  if (IVar23 == 0) {
    dVar28 = 1.0;
  }
  else {
    FUN_1003220ec();
  }
  dVar29 = dVar29 * dVar28;
  lVar19 = 0;
  __ss25FloatingPointRoundingRuleOMa();
  pcVar20 = *(code **)(*(long *)(lVar19 + -8) + 0x38);
  (*pcVar20)(lVar16,1,1,lVar19);
  thunk_FUN_100035714(3,lVar16);
  FUN_100023be4(lVar16,&DAT_100af5490);
  if (0.0 < dVar29) {
    lVar7 = *(long *)(self + lVar25);
    lVar8 = lVar7;
    local_128 = lVar19;
    local_110 = lVar21;
    if (lVar7 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar7 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar7 + 0x28) = 0;
      *(undefined8 *)(lVar7 + 0x20) = 0;
      *(undefined8 *)(lVar7 + 0x38) = 0;
      *(undefined8 *)(lVar7 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar7 + 0x10,self);
      _swift_retain(puVar4);
      FUN_10085ee38();
      lVar21 = local_110;
      uVar9 = *(undefined8 *)(self + lVar25);
      *(long *)(self + lVar25) = lVar7;
      _swift_retain(lVar7);
      _swift_release(uVar9);
      lVar8 = 0;
    }
    uVar18 = *(ulong *)(lVar7 + 0x18);
    _swift_retain(lVar8);
    _swift_bridgeObjectRetain(uVar18);
    _swift_release(lVar7);
    if (uVar18 >> 0x3e == 0) {
      uVar17 = *(ulong *)((uVar18 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar17 = uVar18 & 0xffffffffffffff8;
      if ((long)uVar18 < 0) {
        uVar17 = uVar18;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar17 == 0) {
      _swift_bridgeObjectRelease(uVar18);
    }
    else {
      local_120 = lVar25;
      lVar25 = 4;
      local_130 = pcVar20;
      local_118 = lVar27;
      do {
        lVar21 = lVar25 + -4;
        if ((uVar18 & 0xc000000000000001) == 0) {
          lVar27 = *(long *)(uVar18 + lVar25 * 8);
          _swift_retain(lVar27);
          lVar19 = _TtCC8Playback7SongMap7Element::trimTimelineStartTime;
        }
        else {
          lVar27 = lVar21;
          FUN_1000cc314(lVar21,uVar18);
          lVar19 = _TtCC8Playback7SongMap7Element::trimTimelineStartTime;
        }
        _TtCC8Playback7SongMap7Element::trimTimelineStartTime = lVar19;
        if (SCARRY8(lVar21,1)) {
          (*pcVar20)();
        }
        uVar26 = lVar25 - 3;
        if ((*(double *)(lVar27 + lVar19) <= dVar29) &&
           (dVar29 < *(double *)(lVar27 + _TtCC8Playback7SongMap7Element::trimTimelineEndTime))) {
          _swift_release(lVar24);
          _swift_bridgeObjectRelease(uVar18);
          dVar28 = *(double *)(lVar27 + lVar19);
          param_1 = dVar29 - dVar28;
          local_98[0] = lVar27;
          _swift_retain(lVar27);
          FUN_1000345bc(2);
          param_1 = param_1 + dVar28;
          (*local_130)(lVar16,1,1,local_128);
          thunk_FUN_100035714(param_1,3,lVar16);
          _swift_release(lVar27);
          FUN_100023be4(lVar16,&DAT_100af5490);
          lVar21 = local_110;
          lVar25 = local_120;
          lVar24 = lVar27;
          lVar27 = local_118;
          goto LAB_1004f2024;
        }
        _swift_release(lVar27);
        lVar25 = lVar25 + 1;
      } while (uVar26 != uVar17);
      _swift_bridgeObjectRelease(uVar18);
      lVar21 = local_110;
      lVar25 = local_120;
      lVar27 = local_118;
    }
  }
LAB_1004f2024:
  plVar13 = (long *)0x1;
  FUN_1004ff364(param_1,dVar29,lVar24);
  uVar9 = *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement);
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) = 0;
  _swift_release(uVar9);
  lVar16 = *(long *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElement);
  if (lVar16 != 0) {
    lVar19 = *(long *)(self + lVar25);
    if (lVar19 == 0) {
      lVar19 = 0;
      FUN_100861310();
      _swift_allocObject();
      puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar19 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar19 + 0x28) = 0;
      *(undefined8 *)(lVar19 + 0x20) = 0;
      *(undefined8 *)(lVar19 + 0x38) = 0;
      *(undefined8 *)(lVar19 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar19 + 0x10,self);
      _swift_retain(lVar16);
      _swift_retain(puVar4);
      FUN_10085ee38();
      uVar9 = *(undefined8 *)(self + lVar25);
      *(long *)(self + lVar25) = lVar19;
      _swift_retain(lVar19);
      _swift_release(uVar9);
      lVar25 = 0;
    }
    else {
      _swift_retain(lVar16);
      lVar25 = lVar19;
    }
    plVar22 = *(long **)(lVar19 + 0x18);
    _swift_bridgeObjectRetain(plVar22);
    _swift_retain(lVar25);
    _swift_release(lVar19);
    lVar25 = lVar16;
    plVar12 = plVar22;
    FUN_100283c1c();
    plVar13 = plVar12;
    _swift_bridgeObjectRelease(plVar22);
    if (((ulong)plVar12 & 1) == 0) {
      *(long *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElementIndex) = lVar25;
      FUN_1004fb6ac();
      _swift_release(lVar16);
      goto LAB_1004f2174;
    }
    _swift_release(lVar16);
  }
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElementIndex) = 0;
  FUN_1004fb6ac();
LAB_1004f2174:
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::rewindTime) = 0;
  lVar25 = *(long *)(unaff_x20 + _TtC8Playback9Sequencer::channelGroup);
  if ((lVar25 != 0) &&
     (lVar16 = *(long *)(lVar25 + _TtC8Playback16SongChannelGroup::midiOutChannel), lVar16 != 0)) {
    _swift_retain(lVar25);
    _swift_retain(lVar16);
    FUN_100295fe8(0);
    _swift_release(lVar25);
    _swift_release(lVar16);
  }
  if (DAT_100adef08 != -1) {
    plVar13 = (long *)0x0;
    _swift_once(&DAT_100adef08);
  }
  lVar25 = _TtC8Playback9Sequencer::uuid;
  lVar16 = *(long *)(DAT_100b75e40 + 0x20);
  if (lVar16 != 0) {
    _swift_retain(unaff_x20);
    _swift_retain(lVar16);
    uVar18 = unaff_x20 + lVar25;
    plVar13 = (long *)(lVar16 + lVar25);
    __s10Foundation4UUIDV2eeoiySbAC_ACtFZ();
    _swift_release(unaff_x20);
    _swift_release(lVar16);
    if ((uVar18 & 1) != 0) {
      FUN_10004cb08(0);
      __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
      local_a8 = FUN_1004ff5a8;
      uStack_a0 = 0;
      local_c8 = PTR___NSConcreteStackBlock_100a1d8e8;
      local_c0 = 0x42000000;
      local_b8 = FUN_10056b3d8;
      puStack_b0 = &DAT_100a4dc00;
      aBlock = __Block_copy(&local_c8);
      __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar15);
      puVar1 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
      puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
      local_c8 = PTR___swiftEmptyArrayStorage_100a1e050;
      puVar10 = &DAT_100af52a8;
      FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                    PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
      _swift_retain(puVar4);
      puVar4 = &DAT_100af52b0;
      FUN_100021774(&DAT_100af52b0);
      puVar11 = &DAT_100af52b8;
      FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar1);
      __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                (lVar21,&local_c8,puVar4,puVar11,lVar2,puVar10);
      __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
                (0,lVar15,lVar21,aBlock);
      __Block_release(aBlock);
      (**(code **)(lVar27 + 8))(lVar21,lVar2);
      (**(code **)(lVar14 + 8))(lVar15,lVar3);
      plVar12 = local_98;
      FUN_1004ff780(plVar12,unaff_x20);
      plVar13 = plVar12;
      FUN_10044d444(4,plVar12,self);
      _swift_release(plVar12);
    }
  }
  uVar9 = 0;
  FUN_100212bb0();
  _swift_release(lVar24);
  if (((ulong)plVar13 & 1) == 0) {
    *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextPreparationSequenceTime) = uVar9;
  }
  return 0;
}


