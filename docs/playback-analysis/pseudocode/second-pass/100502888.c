// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 100502888 0
// ===== FUN_100502888 @ 100502888 (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100502888(undefined1 param_1,undefined8 param_2)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  undefined *puVar4;
  undefined *puVar5;
  void *aBlock;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined1 *puVar8;
  long lVar9;
  long lVar10;
  undefined1 auStack_a0 [8];
  long local_98;
  undefined *local_90;
  undefined8 local_88;
  code *local_80;
  undefined *puStack_78;
  code *local_70;
  undefined *local_68;
  
  lVar2 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  puVar1 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  local_98 = *(long *)(lVar2 + -8);
  puVar8 = auStack_a0 + -(*(long *)(local_98 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar10 = *(long *)(lVar3 + -8);
  lVar9 = (long)puVar8 - (*(long *)(lVar10 + 0x40) + 0xfU & 0xfffffffffffffff0);
  FUN_10004cb08(0);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  puVar4 = &DAT_100a4da08;
  _swift_allocObject(&DAT_100a4da08,0x18,7);
  _swift_weakInit(puVar4 + 0x10,param_2);
  puVar5 = &DAT_100a4dd28;
  _swift_allocObject(&DAT_100a4dd28,0x20,7);
  puVar5[0x10] = param_1;
  *(undefined **)(puVar5 + 0x18) = puVar4;
  local_70 = FUN_100504f5c;
  local_90 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_88 = 0x42000000;
  local_80 = FUN_10056b3d8;
  puStack_78 = &DAT_100a4dd40;
  local_68 = puVar5;
  aBlock = __Block_copy(&local_90);
  _swift_release(local_68);
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar9);
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_90 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar6 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,puVar1,PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8)
  ;
  _swift_retain(puVar4);
  puVar4 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar7 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar1);
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (puVar8,&local_90,puVar4,puVar7,lVar2,puVar6);
  __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (0,lVar9,puVar8,aBlock);
  __Block_release(aBlock);
  (**(code **)(local_98 + 8))(puVar8,lVar2);
  (**(code **)(lVar10 + 8))(lVar9,lVar3);
  return;
}


