// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1007337d4 0
// ===== FUN_1007337d4 @ 1007337d4 (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007337d4(uint param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined *puVar7;
  void *aBlock;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  long unaff_x20;
  long lVar14;
  code *pcVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long *plVar19;
  long local_110;
  uint local_104;
  long local_100;
  long lStack_f8;
  long local_f0;
  long local_e8;
  long local_e0;
  long local_d8;
  long local_d0;
  long local_c8;
  code *local_c0;
  long local_b8;
  long local_b0;
  undefined *local_a0;
  undefined *local_98;
  undefined8 local_90;
  code *local_88;
  undefined *puStack_80;
  code *local_78;
  undefined *local_70;
  
  lVar2 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar13 = *(long *)(lVar2 + -8);
  lVar17 = (long)&local_110 - (*(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar14 = *(long *)(lVar3 + -8);
  lVar16 = lVar17 - (*(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  __s8Dispatch0A4TimeVMa();
  local_c0 = *(code **)(lVar4 + -8);
  uVar11 = *(long *)(local_c0 + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_c8 = lVar16 - uVar11;
  lVar12 = local_c8 - uVar11;
  lVar5 = 0;
  local_b8 = lVar12;
  local_b0 = lVar4;
  __s8Dispatch0A3QoSV0B6SClassOMa();
  lVar4 = *(long *)(lVar5 + -8);
  lVar12 = lVar12 - (*(long *)(lVar4 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar18 = *(long *)(unaff_x20 + 0x20);
  if (lVar18 == 0) {
    if ((param_1 & 1) == 0) goto LAB_100733b8c;
    lVar6 = 0;
    local_100 = lVar4;
    lStack_f8 = lVar5;
    local_f0 = lVar16;
    local_e8 = lVar14;
    local_e0 = lVar3;
    local_d8 = lVar17;
    local_d0 = lVar13;
  }
  else {
    lVar6 = lVar18;
    local_110 = lVar2;
    local_104 = param_1;
    local_100 = lVar4;
    lStack_f8 = lVar5;
    local_f0 = lVar16;
    local_e8 = lVar14;
    local_e0 = lVar3;
    local_d8 = lVar17;
    local_d0 = lVar13;
    _swift_retain_n(lVar18,2);
    FUN_10064458c();
    lVar2 = *(long *)(lVar6 + 0x10);
    if (lVar2 != 0) {
      plVar19 = (long *)(lVar6 + 0x28);
      do {
        lVar3 = plVar19[-1];
        lVar4 = *plVar19;
        lVar5 = lVar3;
        _swift_getObjectType(lVar3);
        pcVar15 = *(code **)(lVar4 + 0x90);
        _swift_unknownObjectRetain(lVar3);
        (*pcVar15)(1,lVar5,lVar4);
        _swift_unknownObjectRelease(lVar3);
        plVar19 = plVar19 + 3;
        lVar2 = lVar2 + -1;
      } while (lVar2 != 0);
    }
    _swift_release(lVar18);
    _swift_bridgeObjectRelease(lVar6);
    lVar6 = lVar18;
    lVar2 = local_110;
    if ((local_104 & 1) == 0) {
      _swift_retain(lVar18);
      FUN_100651030();
      _swift_release_n(lVar18,2);
      goto LAB_100733b8c;
    }
  }
  FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
  lVar4 = lStack_f8;
  lVar3 = local_100;
  (**(code **)(local_100 + 0x68))
            (lVar12,*(undefined4 *)PTR___s8Dispatch0A3QoSV0B6SClassO7defaultyA2EmFWC_100a1e0c0,
             lStack_f8);
  __sSo17OS_dispatch_queueC8DispatchE6global3qosAbC0D3QoSV0G6SClassO_tFZ(lVar12);
  (**(code **)(lVar3 + 8))(lVar12,lVar4);
  lVar3 = local_c8;
  __s8Dispatch0A4TimeV3nowACyFZ(local_c8);
  lVar5 = local_b8;
  __s8Dispatch1poiyAA0A4TimeVAD_SdtF(local_b8,0x3ff0000000000000,lVar3);
  local_c0 = *(code **)(local_c0 + 8);
  (*local_c0)(lVar3,local_b0);
  puVar7 = &DAT_100a610d8;
  _swift_allocObject(&DAT_100a610d8,0x18,7);
  *(long *)(puVar7 + 0x10) = lVar18;
  local_78 = FUN_100737c24;
  local_98 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_90 = 0x42000000;
  local_88 = FUN_10056b3d8;
  puStack_80 = &DAT_100a610f0;
  local_70 = puVar7;
  aBlock = __Block_copy(&local_98);
  _swift_retain_n(lVar6,2);
  lVar3 = local_f0;
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_f0);
  puVar1 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  puVar7 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_a0 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar8 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar7);
  puVar7 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar9 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar1);
  lVar4 = local_d8;
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (local_d8,&local_a0,puVar7,puVar9,lVar2,puVar8);
  __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (lVar5,lVar3,lVar4,aBlock);
  __Block_release(aBlock);
  _swift_release_n(lVar6,2);
  (**(code **)(local_d0 + 8))(lVar4,lVar2);
  (**(code **)(local_e8 + 8))(lVar3,local_e0);
  (*local_c0)(lVar5,local_b0);
  _swift_release(local_70);
LAB_100733b8c:
  uVar10 = *(undefined8 *)(unaff_x20 + 0x20);
  *(undefined8 *)(unaff_x20 + 0x20) = 0;
  _swift_release(uVar10);
  return;
}


