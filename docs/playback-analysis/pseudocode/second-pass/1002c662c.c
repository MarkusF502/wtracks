// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1002c662c 0
// ===== FUN_1002c662c @ 1002c662c (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_1002c662c(undefined8 param_1,undefined8 param_2,long param_3,long param_4,ID param_5,
                  long param_6)

{
  code *pcVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ID IVar6;
  undefined *puVar7;
  undefined *puVar8;
  void *pvVar9;
  undefined8 *puVar10;
  undefined *puVar11;
  undefined8 *puVar12;
  ID IVar13;
  ID IVar14;
  ulong uVar15;
  ID IVar16;
  long lVar17;
  ulong uVar18;
  long lVar19;
  undefined1 *puVar20;
  uint uVar21;
  ulong uVar22;
  undefined8 uVar23;
  undefined1 auStack_f0 [8];
  long local_e8;
  ID local_e0;
  long local_d8;
  long local_d0;
  long local_c8;
  long lStack_c0;
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  code *local_98;
  undefined *local_90;
  
  lVar2 = 0;
  uVar23 = param_1;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar19 = *(long *)(lVar2 + -8);
  puVar20 = auStack_f0 + -(*(long *)(lVar19 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  local_c8 = *(long *)(lVar3 + -8);
  local_d0 = (long)puVar20 - (*(long *)(local_c8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lStack_c0 = lVar3;
  if (*(long *)(param_4 + 0x18) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined8 *)(*(long *)(param_4 + 0x18) + 0x20);
    _swift_retain();
  }
  uVar15 = *(ulong *)(param_3 + _TtC8Playback9Sequencer::channelGroup);
  *(undefined8 *)(param_3 + _TtC8Playback9Sequencer::channelGroup) = uVar4;
  _swift_release();
  FUN_1004f1918();
  FUN_1002de548();
  if (uVar15 >> 0x3e == 0) {
    uVar22 = *(ulong *)((uVar15 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar22 = uVar15 & 0xffffffffffffff8;
    if ((long)uVar15 < 0) {
      uVar22 = uVar15;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  local_e0 = param_5;
  if (uVar22 != 0) {
    if ((long)uVar22 < 1) {
      (*pcVar1)();
    }
    local_e8 = param_6;
    local_d8 = param_4;
    _swift_bridgeObjectRetain(uVar15);
    uVar18 = 0;
    do {
      if ((uVar15 & 0xc000000000000001) == 0) {
        uVar5 = *(ulong *)(uVar15 + uVar18 * 8 + 0x20);
      }
      else {
        uVar5 = uVar18;
        FUN_1000cc338(uVar18,uVar15);
      }
      uVar18 = uVar18 + 1;
      *(undefined1 *)(uVar5 + _TtC8Playback9SongTrack::soloState) = 1;
    } while (uVar22 != uVar18);
    _swift_bridgeObjectRelease(uVar15);
    param_6 = local_e8;
    param_4 = local_d8;
  }
  IVar6 = local_e0;
  _swift_bridgeObjectRelease(uVar15);
  if ((*(long *)(param_4 + 0x18) != 0) &&
     (lVar3 = *(long *)(*(long *)(param_4 + 0x18) + 0x20), lVar3 != 0)) {
    _swift_retain(lVar3);
    FUN_10064521c(IVar6,1);
    _swift_release(lVar3);
  }
  lVar3 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar16 = *(ID *)(param_6 + _TtC8Playback9Sequencer::song);
  IVar6 = *(ID *)(IVar16 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar6 == 0) {
    IVar14 = _objc_msgSend(IVar16,"workingCopyArrangementID");
    if (IVar14 == 0) goto LAB_1002c6e2c;
    IVar13 = IVar14;
    FUN_10032ee88();
    IVar6 = IVar13;
    FUN_1005e3b94(IVar13,IVar14);
    local_d8 = lVar19;
    _swift_bridgeObjectRelease(IVar13);
    if (IVar6 == 0) goto LAB_1002c6e2c;
    *(ID *)(IVar16 + lVar3) = IVar6;
    lVar19 = local_d8;
  }
  IVar6 = _objc_msgSend(IVar6,"song");
  if ((IVar6 == 0) || ((*(byte *)(IVar6 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
    uVar21 = 0;
    FUN_1002da058();
    if ((uVar21 & 0xfe) != 2) goto LAB_1002c6e2c;
  }
  else {
    uVar21 = 3;
  }
  lVar3 = *(long *)(param_4 + 0x18);
  if (lVar3 != 0) {
    lVar17 = *(long *)(lVar3 + 0x18);
    if (lVar17 != 0) {
      _swift_retain(lVar17);
      FUN_1006471c8(0);
      _swift_release(lVar17);
      lVar3 = *(long *)(param_4 + 0x18);
      if (lVar3 == 0) goto LAB_1002c68ec;
    }
    if ((*(long *)(lVar3 + 0x18) != 0) &&
       (lVar3 = *(long *)(*(long *)(lVar3 + 0x18) + _TtC8Playback16SongChannelGroup::midiOutChannel)
       , lVar3 != 0)) {
      *(undefined1 *)(lVar3 + 0x40) = 0;
      *(undefined1 *)(*(long *)(lVar3 + 0x38) + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = 0;
      _swift_retain(lVar3);
      FUN_10049ffc8();
      _swift_release(lVar3);
    }
  }
LAB_1002c68ec:
  puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_d8 = lVar19;
  if ((uVar21 & 0xff) == 3) {
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_e8 = 0;
    puVar7 = &DAT_100a3ed78;
    _swift_allocObject(&DAT_100a3ed78,0x18,7);
    _swift_weakInit(puVar7 + 0x10,param_4);
    puVar8 = &DAT_100a3ef08;
    _swift_allocObject(&DAT_100a3ef08,0x28,7);
    *(undefined **)(puVar8 + 0x10) = puVar7;
    *(undefined8 *)(puVar8 + 0x18) = param_1;
    *(undefined8 *)(puVar8 + 0x20) = param_2;
    local_98 = FUN_1002c7f08;
    local_b8 = puVar11;
    uVar23 = 0x42000000;
    local_b0 = 0x42000000;
    local_a8 = FUN_10056b3d8;
    puStack_a0 = &DAT_100a3ef20;
    local_90 = puVar8;
    pvVar9 = __Block_copy(&local_b8);
    _swift_release(local_90);
    lVar19 = local_d0;
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_d0);
    puVar7 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar10 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar11);
    puVar11 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar12 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar7);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (puVar20,&local_b8,puVar11,puVar12,lVar2,puVar10);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,lVar19,puVar20,pvVar9);
    __Block_release(pvVar9);
    (**(code **)(local_d8 + 8))(puVar20,lVar2);
    puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
    (**(code **)(local_c8 + 8))(lVar19,lStack_c0);
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar15 = DAT_100b757a8;
  FUN_100171514();
  if ((uVar15 & 1) != 0) {
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    IVar6 = *(ID *)(DAT_100b75a80 + 0x10);
    if ((IVar6 != 0) &&
       (FUN_1004a9df0(), lVar19 = _TtC8Playback4Song::privateWorkingCopyArrangement, IVar6 != 0)) {
      IVar16 = *(ID *)(IVar6 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar16 == 0) {
        IVar14 = _objc_msgSend(IVar6,"workingCopyArrangementID");
        puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        if (IVar14 != 0) {
          IVar13 = IVar14;
          FUN_10032ee88();
          IVar16 = IVar13;
          FUN_1005e3b94(IVar13,IVar14);
          _swift_bridgeObjectRelease(IVar13);
          puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
          if (IVar16 != 0) {
            *(ID *)(IVar6 + lVar19) = IVar16;
            goto LAB_1002c6b38;
          }
        }
      }
      else {
LAB_1002c6b38:
        lVar19 = *(long *)(param_4 + 0x18);
        puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        if (lVar19 != 0) {
          _swift_retain(lVar19);
          _objc_msgSend(IVar16,"masterVolumeLevel");
          uVar4 = uVar23;
          _objc_msgSend(local_e0,"masterVolumeLevel");
          *(undefined1 *)(lVar19 + 0x58) = 1;
          FUN_100736e24(uVar23,uVar4,param_1,param_2);
          _swift_release(lVar19);
          puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        }
      }
    }
  }
  FUN_1004f5388(1);
  FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  local_98 = FUN_1002c6f78;
  local_90 = (undefined *)0x0;
  local_b0 = 0x42000000;
  local_a8 = FUN_10056b3d8;
  puStack_a0 = &DAT_100a3eed0;
  local_b8 = puVar11;
  pvVar9 = __Block_copy(&local_b8);
  lVar19 = local_d0;
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_d0);
  puVar7 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar10 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar11);
  puVar11 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar12 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar7);
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (puVar20,&local_b8,puVar11,puVar12,lVar2,puVar10);
  __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (0,lVar19,puVar20,pvVar9);
  __Block_release(pvVar9);
  (**(code **)(local_d8 + 8))(puVar20,lVar2);
  (**(code **)(local_c8 + 8))(lVar19,lStack_c0);
LAB_1002c6e2c:
  FUN_1004f8088();
  return;
}


