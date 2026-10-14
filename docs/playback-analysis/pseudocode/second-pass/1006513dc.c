// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1006513dc 0
// ===== FUN_1006513dc @ 1006513dc (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1006513dc(double param_1,double param_2,double param_3,ulong param_4,long param_5,
                  byte param_6)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined *puVar8;
  undefined *puVar9;
  void *pvVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined8 uVar13;
  ulong uVar14;
  code *pcVar15;
  long unaff_x20;
  long lVar16;
  undefined1 *puVar17;
  long lVar18;
  long lVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  undefined1 auStack_110 [12];
  uint local_104;
  long local_100;
  long local_f8;
  long local_f0;
  undefined *local_d0;
  undefined *local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  code *local_a8;
  undefined *local_a0;
  
  lVar2 = 0;
  dVar20 = param_1;
  __s8Dispatch0A4TimeVMa();
  lVar18 = *(long *)(lVar2 + -8);
  uVar14 = *(long *)(lVar18 + 0x40) + 0xfU & 0xfffffffffffffff0;
  puVar17 = auStack_110 + -uVar14;
  lVar16 = (long)puVar17 - uVar14;
  lVar3 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar19 = lVar16 - (*(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar4 = lVar19 - (*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  uVar14 = param_4;
  _swift_getObjectType();
  _swift_conformsToProtocol();
  if (uVar14 == 0) {
    return;
  }
  if (param_4 == 0) {
    return;
  }
  uVar5 = param_4;
  local_f8 = lVar18;
  local_f0 = lVar2;
  _swift_getObjectType();
  pcVar15 = *(code **)(uVar14 + 0x68);
  _swift_unknownObjectRetain(param_4);
  uVar6 = uVar5;
  (*pcVar15)(uVar5,uVar14);
  if ((uVar6 & 1) == 0) {
LAB_10065156c:
    _swift_unknownObjectRelease(param_4);
    return;
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar2 = *(long *)(DAT_100b75e40 + 0x20);
  if ((lVar2 == 0) || ((*(byte *)(lVar2 + _TtC8Playback9Sequencer::privatePlayState) & 1) == 0))
  goto LAB_10065156c;
  _swift_retain();
  local_100 = lVar2;
  FUN_1004f240c();
  dVar20 = dVar20 - param_2;
  dVar23 = dVar20 / param_3;
  if ((param_6 & 1) != 0) {
    dVar20 = 0.0;
    if (0.0 < 1.0 - dVar23) {
      dVar20 = 1.0 - dVar23;
    }
    dVar23 = 1.0;
    if (dVar20 <= 1.0) {
      dVar23 = dVar20;
    }
    dVar20 = dVar23 * dVar23 * param_1;
    goto LAB_10065167c;
  }
  uVar6 = param_4;
  _swift_getObjectType();
  (**(code **)(param_5 + 0x18))();
  dVar22 = 0.0;
  if (uVar6 == 0) {
LAB_100651664:
    dVar21 = 0.0;
  }
  else {
    if (DAT_100adfbd0 != -1) {
      _swift_once(&DAT_100adfbd0,FUN_1005d0614);
    }
    uVar13 = DAT_100b77550;
    _swift_retain(DAT_100b77550);
    uVar7 = uVar6;
    FUN_1005ecd4c(uVar6,0);
    local_104 = (uint)uVar7;
    _swift_release(uVar13);
    uVar13 = DAT_100b77550;
    _swift_retain(DAT_100b77550);
    FUN_100654a7c(uVar6,0,0,FUN_100652494);
    _swift_release(uVar13);
    dVar21 = 1.0;
    dVar22 = dVar20;
    if ((local_104 & 1) != 0) goto LAB_100651664;
  }
  dVar20 = dVar23 * dVar23 * dVar22 * (1.0 - dVar21);
LAB_10065167c:
  (**(code **)(*(long *)(uVar14 + 8) + 0x28))(dVar20,uVar5);
  puVar8 = &DAT_100a572d8;
  _swift_allocObject(&DAT_100a572d8,0x18,7);
  _swift_weakInit(puVar8 + 0x10,unaff_x20);
  puVar9 = &DAT_100a57350;
  _swift_allocObject(&DAT_100a57350,0x41,7);
  *(undefined **)(puVar9 + 0x10) = puVar8;
  *(ulong *)(puVar9 + 0x18) = param_4;
  *(long *)(puVar9 + 0x20) = param_5;
  *(double *)(puVar9 + 0x28) = param_1;
  *(double *)(puVar9 + 0x30) = param_2;
  *(double *)(puVar9 + 0x38) = param_3;
  puVar9[0x40] = param_6 & 1;
  local_a8 = FUN_1006556fc;
  local_c8 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_c0 = 0x42000000;
  local_b8 = FUN_10056b3d8;
  puStack_b0 = &DAT_100a57368;
  local_a0 = puVar9;
  pvVar10 = __Block_copy(&local_c8);
  _swift_unknownObjectRetain(param_4);
  _swift_retain(puVar8);
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar4);
  puVar1 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  puVar9 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar11 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar9);
  puVar9 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar12 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar1);
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (lVar19,&local_d0,puVar9,puVar12,lVar3,puVar11);
  __s8Dispatch0A8WorkItemCMa();
  _swift_allocObject();
  __s8Dispatch0A8WorkItemC3qos5flags5blockAcA0A3QoSV_AA0abC5FlagsVyyXBtcfc(lVar4,lVar19,pvVar10);
  puVar9 = local_a0;
  _swift_release(puVar8);
  _swift_release(puVar9);
  lVar2 = _TtC8Playback16SongChannelGroup::fadeWorkItem;
  uVar13 = *(undefined8 *)(unaff_x20 + _TtC8Playback16SongChannelGroup::fadeWorkItem);
  *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::fadeWorkItem) = lVar4;
  _swift_release(uVar13);
  lVar2 = *(long *)(unaff_x20 + lVar2);
  if (lVar2 == 0) {
    _swift_unknownObjectRelease(param_4);
    _swift_release(local_100);
  }
  else {
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    _swift_retain(lVar2);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    __s8Dispatch0A4TimeV3nowACyFZ(puVar17);
    __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar16,param_3 / (param_3 * 5.0),puVar17);
    lVar3 = local_f0;
    pcVar15 = *(code **)(local_f8 + 8);
    (*pcVar15)(puVar17,local_f0);
    __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline7executeyAC0D4TimeV_AC0D8WorkItemCtF
              (lVar16,lVar2);
    _swift_unknownObjectRelease(param_4);
    _swift_release(lVar2);
    _swift_release(local_100);
    (*pcVar15)(lVar16,lVar3);
  }
  return;
}


