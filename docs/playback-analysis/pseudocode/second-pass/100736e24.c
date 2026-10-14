// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 100736e24 0
// ===== FUN_100736e24 @ 100736e24 (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100736e24(double param_1,double param_2,double param_3,double param_4)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ID self;
  undefined *puVar6;
  undefined *puVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  ulong uVar11;
  long lVar12;
  code *pcVar13;
  long unaff_x20;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  double dVar18;
  double dVar19;
  void *local_d0;
  undefined *local_c8;
  long local_c0;
  undefined *local_b8;
  undefined *local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined *puStack_98;
  code *local_90;
  undefined *local_88;
  
  lVar2 = 0;
  dVar18 = param_1;
  __s8Dispatch0A4TimeVMa();
  lVar12 = *(long *)(lVar2 + -8);
  uVar11 = *(long *)(lVar12 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar15 = (long)&local_d0 - uVar11;
  lVar14 = lVar15 - uVar11;
  lVar3 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar17 = lVar14 - (*(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar4 = lVar17 - (*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar1 = DAT_100adfba8;
  lVar16 = *(long *)(DAT_100b75e40 + 0x20);
  if ((lVar16 != 0) && (*(char *)(unaff_x20 + 0x58) == '\x01')) {
    local_c0 = lVar2;
    _swift_retain(lVar16);
    if (lVar1 != -1) {
      _swift_once(&DAT_100adfba8,FUN_100596ba8);
    }
    uVar11 = DAT_100b77538;
    uVar5 = DAT_100b77538;
    _swift_retain();
    FUN_10059671c();
    _swift_release(uVar11);
    if ((uVar5 & 1) == 0) {
      _swift_release(lVar16);
      return;
    }
    FUN_1004f240c();
    dVar19 = (dVar18 - param_3) / param_4;
    dVar18 = -(ABS(param_2 - param_1) * dVar19);
    if (param_1 <= param_2) {
      dVar18 = ABS(param_2 - param_1) * dVar19;
    }
    lVar2 = *(long *)(unaff_x20 + 0x30);
    *(double *)(lVar2 + _TtCC8Playback11AudioEngine16MasterFaderMixer::volume) = dVar18 + param_1;
    lVar2 = *(long *)(lVar2 + _TtCC8Playback11AudioEngine16MasterFaderMixer::mixerAudioUnit);
    *(float *)(lVar2 + _TtC8Playback16MixerAVAudioUnit::_volume) = (float)(dVar18 + param_1);
    self = *(ID *)(lVar2 + _TtC8Playback16MixerAVAudioUnit::volumeParameter);
    if (self != 0) {
      _objc_msgSend(self,"setValue:");
    }
    puVar6 = &DAT_100a61150;
    _swift_allocObject(&DAT_100a61150,0x18,7);
    _swift_weakInit(puVar6 + 0x10);
    puVar7 = &DAT_100a611c8;
    _swift_allocObject(&DAT_100a611c8,0x38,7);
    *(undefined **)(puVar7 + 0x10) = puVar6;
    *(double *)(puVar7 + 0x18) = param_1;
    *(double *)(puVar7 + 0x20) = param_2;
    *(double *)(puVar7 + 0x28) = param_3;
    *(double *)(puVar7 + 0x30) = param_4;
    local_90 = FUN_10073805c;
    local_b0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_a8 = 0x42000000;
    local_a0 = FUN_10056b3d8;
    puStack_98 = &DAT_100a611e0;
    local_c8 = puVar6;
    local_88 = puVar7;
    local_d0 = __Block_copy(&local_b0);
    _swift_retain(puVar6);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar4);
    puVar6 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar8 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar6);
    puVar6 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar9 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (lVar17,&local_b8,puVar6,puVar9,lVar3,puVar8);
    __s8Dispatch0A8WorkItemCMa();
    _swift_allocObject();
    __s8Dispatch0A8WorkItemC3qos5flags5blockAcA0A3QoSV_AA0abC5FlagsVyyXBtcfc(lVar4,lVar17,local_d0);
    puVar6 = local_88;
    _swift_release(local_c8);
    _swift_release(puVar6);
    uVar10 = *(undefined8 *)(unaff_x20 + 0x50);
    *(long *)(unaff_x20 + 0x50) = lVar4;
    _swift_release(uVar10);
    lVar2 = *(long *)(unaff_x20 + 0x50);
    if (lVar2 == 0) {
      _swift_release(lVar16);
    }
    else {
      FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
      _swift_retain(lVar2);
      __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
      __s8Dispatch0A4TimeV3nowACyFZ(lVar15);
      __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar14,0x3fc5c28f5c28f5c3,lVar15);
      lVar3 = local_c0;
      pcVar13 = *(code **)(lVar12 + 8);
      (*pcVar13)(lVar15,local_c0);
      __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline7executeyAC0D4TimeV_AC0D8WorkItemCtF
                (lVar14,lVar2);
      _swift_release(lVar2);
      _swift_release(lVar16);
      (*pcVar13)(lVar14,lVar3);
    }
  }
  return;
}


