// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 10002c318 0
// ===== FUN_10002c318 @ 10002c318 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_10002c318(double param_1,double param_2,undefined8 param_3,undefined4 param_4,
                  double param_5,uint param_6)

{
  ulong uVar1;
  char cVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulong uVar10;
  undefined *puVar11;
  ID self;
  ulong uVar12;
  double dVar13;
  ID unaff_x20;
  long lVar14;
  code *pcVar15;
  undefined *puVar16;
  double dVar17;
  ulong uVar18;
  long lVar19;
  ulong uVar20;
  undefined1 *puVar21;
  long lVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  undefined1 auStack_f0 [8];
  double *local_e8;
  double local_e0;
  long local_d8;
  double local_d0;
  uint local_c4;
  void *local_c0;
  undefined *local_b8;
  undefined *local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined *puStack_98;
  code *local_90;
  undefined *local_88;
  
  local_c0 = (void *)CONCAT44(local_c0._4_4_,param_4);
  lVar3 = 0;
  dVar17 = param_1;
  local_d0 = param_5;
  local_c4 = param_6;
  __s8Dispatch0A4TimeVMa();
  local_d8 = *(long *)(lVar3 + -8);
  uVar12 = *(long *)(local_d8 + 0x40) + 0xfU & 0xfffffffffffffff0;
  puVar21 = auStack_f0 + -uVar12;
  lVar19 = (long)puVar21 - uVar12;
  lVar4 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar22 = lVar19 - (*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar14 = lVar22 - (*(long *)(*(long *)(lVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  FUN_1000c4f28();
  if (((lVar5 == 0) ||
      (cVar2 = *(char *)(lVar5 + _TtC8Playback9Sequencer::privatePlayState), _swift_release(),
      cVar2 != '\x01')) ||
     (local_e8 = (double *)(unaff_x20 + _TtC8Playback9SongTrack::fadeStartTimecode),
     ((ulong)local_e8[1] & 1) != 0)) {
    lVar3 = _TtC8Playback9SongTrack::fadeWorkItem;
    lVar4 = *(long *)(unaff_x20 + _TtC8Playback9SongTrack::fadeWorkItem);
    if (lVar4 == 0) {
      uVar6 = 0;
    }
    else {
      _swift_retain(lVar4);
      __s8Dispatch0A8WorkItemC6cancelyyFTj();
      _swift_release(lVar4);
      uVar6 = *(undefined8 *)(unaff_x20 + lVar3);
    }
    *(undefined8 *)(unaff_x20 + lVar3) = 0;
    _swift_release(uVar6);
    FUN_10002a5fc(param_2,param_3,(ulong)local_c0 & 0xffffffff,0,0,1);
    return;
  }
  dVar24 = *local_e8;
  FUN_1000c4f28();
  if (lVar5 == 0) {
    dVar25 = 0.0;
    dVar23 = dVar17;
  }
  else {
    FUN_1004f240c();
    dVar23 = dVar17;
    _swift_release(lVar5);
    dVar25 = dVar17;
  }
  dVar25 = dVar25 - dVar24;
  if (((uint)local_c0 & 0xff) < 2) {
    if (((ulong)param_2 & 1) != 0) {
      local_e0 = param_2;
      if (DAT_100adfbd0 != -1) {
        _swift_once(&DAT_100adfbd0,FUN_1005d0614);
      }
      uVar6 = DAT_100b77550;
      uVar7 = DAT_100b77550;
      _swift_retain(DAT_100b77550);
      FUN_1000c4f28();
      FUN_10065245c();
      _swift_release(uVar6);
      _swift_release(uVar7);
      uVar12 = (ulong)local_c0 & 0xffffffff;
      dVar17 = local_e0;
      if ((((ulong)((double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume))[1] & 1) != 0
          ) || (0.0 < *(double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume))) {
        dVar24 = dVar23 - (dVar25 / param_1) * dVar23;
        dVar23 = 0.0;
        if (0.0 < dVar24) {
          dVar23 = dVar24;
        }
        goto LAB_10002c790;
      }
      goto LAB_10002c9c4;
    }
LAB_10002c5f0:
    local_e0 = param_2;
    if (DAT_100adfbd0 != -1) {
      _swift_once(&DAT_100adfbd0,FUN_1005d0614);
    }
    uVar6 = DAT_100b77550;
    uVar7 = DAT_100b77550;
    _swift_retain(DAT_100b77550);
    FUN_1000c4f28();
    FUN_10065245c();
    _swift_release(uVar6);
    _swift_release(uVar7);
    uVar12 = (ulong)local_c0 & 0xffffffff;
    dVar17 = local_e0;
    if (((ulong)((double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume))[1] & 1) == 0) {
      if (NAN(dVar23)) {
        (*pcVar15)();
      }
      if (dVar23 <= *(double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume))
      goto LAB_10002c9c4;
    }
    dVar24 = (dVar25 / param_1) * dVar23;
    if (dVar24 <= dVar23) {
      dVar23 = dVar24;
    }
LAB_10002c790:
    FUN_10002f1d8(dVar23);
    puVar11 = &DAT_100a216b0;
    _swift_allocObject(&DAT_100a216b0,0x41,7);
    *(ID *)(puVar11 + 0x10) = unaff_x20;
    *(double *)(puVar11 + 0x18) = dVar17;
    *(undefined8 *)(puVar11 + 0x20) = param_3;
    puVar11[0x28] = (char)uVar12;
    *(double *)(puVar11 + 0x30) = param_1;
    *(double *)(puVar11 + 0x38) = local_d0;
    puVar11[0x40] = (byte)local_c4 & 1;
    local_90 = FUN_100033960;
    local_b0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_a8 = 0x42000000;
    local_a0 = FUN_10056b3d8;
    puStack_98 = &DAT_100a216c8;
    local_88 = puVar11;
    local_c0 = __Block_copy(&local_b0);
    FUN_1000337bc(dVar17,param_3,uVar12);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar14);
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar8 = &DAT_100af52a8;
    FUN_10002f670(&DAT_100af52a8,0xff,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar11);
    puVar11 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar9 = &DAT_100af52b8;
    FUN_10002f670(&DAT_100af52b8,0xff,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (lVar22,&local_b8,puVar11,puVar9,lVar4,puVar8);
    __s8Dispatch0A8WorkItemCMa();
    _swift_allocObject();
    __s8Dispatch0A8WorkItemC3qos5flags5blockAcA0A3QoSV_AA0abC5FlagsVyyXBtcfc(lVar14,lVar22,local_c0)
    ;
    _swift_release(local_88);
    lVar4 = _TtC8Playback9SongTrack::fadeWorkItem;
    uVar6 = *(undefined8 *)(unaff_x20 + _TtC8Playback9SongTrack::fadeWorkItem);
    *(long *)(unaff_x20 + _TtC8Playback9SongTrack::fadeWorkItem) = lVar14;
    _swift_release(uVar6);
    lVar4 = *(long *)(unaff_x20 + lVar4);
    if (lVar4 != 0) {
      FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
      _swift_retain(lVar4);
      __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
      __s8Dispatch0A4TimeV3nowACyFZ(puVar21);
      __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar19,param_1 / (param_1 * 30.0),puVar21);
      pcVar15 = *(code **)(local_d8 + 8);
      (*pcVar15)(puVar21,lVar3);
      __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline7executeyAC0D4TimeV_AC0D8WorkItemCtF
                (lVar19,lVar4);
      _swift_release(lVar4);
      (*pcVar15)(lVar19,lVar3);
    }
    return;
  }
  if (((uint)local_c0 & 0xff) != 2) goto LAB_10002c5f0;
  dVar17 = param_2;
  dVar24 = local_d0;
  if ((local_c4 & 1) != 0) {
    local_e0 = param_2;
    if (DAT_100adfbd0 != -1) {
      _swift_once(&DAT_100adfbd0,FUN_1005d0614);
    }
    uVar6 = DAT_100b77550;
    uVar7 = DAT_100b77550;
    _swift_retain(DAT_100b77550);
    FUN_1000c4f28();
    FUN_10065245c();
    _swift_release(uVar6);
    _swift_release(uVar7);
    dVar17 = local_e0;
    dVar24 = dVar23;
  }
  uVar12 = (ulong)(uint)local_c0;
  dVar13 = *(double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume);
  dVar23 = ((double *)(unaff_x20 + _TtC8Playback9SongTrack::currentFadeVolume))[1];
  if (dVar24 <= param_2) {
    if (((ulong)dVar23 & 1) == 0) {
      if (NAN(param_2)) {
        (*pcVar15)();
      }
      if (param_2 <= dVar13) goto LAB_10002c9c4;
    }
    dVar24 = dVar24 + (dVar25 / param_1) * (param_2 - dVar24);
    if (dVar24 <= param_2) {
      param_2 = dVar24;
    }
    dVar23 = 1.0;
    if (param_2 <= 1.0) {
      dVar23 = param_2;
    }
    goto LAB_10002c790;
  }
  if (((ulong)dVar23 & 1) != 0) {
LAB_10002c6fc:
    dVar24 = dVar24 - (dVar25 / param_1) * (dVar24 - param_2);
    if (param_2 < dVar24) {
      param_2 = dVar24;
    }
    dVar23 = 0.0;
    if (0.0 < param_2) {
      dVar23 = param_2;
    }
    goto LAB_10002c790;
  }
  if (NAN(param_2)) {
    (*pcVar15)();
  }
  if (param_2 < dVar13) goto LAB_10002c6fc;
LAB_10002c9c4:
  *local_e8 = 0.0;
  *(undefined1 *)(local_e8 + 1) = 1;
  uVar12 = _objc_msgSend(unaff_x20,"arrangement");
  if (uVar12 == 0) goto LAB_10002cbe0;
  FUN_1002f6e9c();
  _swift_bridgeObjectRetain();
  if (uVar12 >> 0x3e == 0) {
    uVar18 = *(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10);
    if (uVar18 != 0) goto LAB_10002ca1c;
LAB_10002cb50:
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    uVar18 = uVar12 & 0xffffffffffffff8;
    if ((long)uVar12 < 0) {
      uVar18 = uVar12;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (uVar18 == 0) goto LAB_10002cb50;
LAB_10002ca1c:
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    if ((long)uVar18 < 1) {
      (*pcVar15)();
    }
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    uVar20 = 0;
    do {
      if ((uVar12 & 0xc000000000000001) == 0) {
        uVar10 = *(ulong *)(uVar12 + uVar20 * 8 + 0x20);
      }
      else {
        uVar10 = uVar20;
        FUN_1000cc338(uVar20,uVar12);
      }
      if ((*(byte *)(uVar10 + _TtC8Playback9SongTrack::fadeStartTimecode + 8) & 1) == 0) {
        puVar16 = puVar11;
        _swift_isUniquelyReferenced_nonNull_native();
        local_b0 = puVar11;
        if (((ulong)puVar16 & 1) == 0) {
          FUN_1001cc4d4(0,*(long *)(puVar11 + 0x10) + 1,1);
        }
        uVar1 = *(ulong *)(local_b0 + 0x10);
        if (*(ulong *)(local_b0 + 0x18) >> 1 <= uVar1) {
          FUN_1001cc4d4(1 < *(ulong *)(local_b0 + 0x18),uVar1 + 1,1);
        }
        *(ulong *)(local_b0 + 0x10) = uVar1 + 1;
        *(ulong *)(local_b0 + uVar1 * 8 + 0x20) = uVar10;
        puVar11 = local_b0;
      }
      uVar20 = uVar20 + 1;
    } while (uVar18 != uVar20);
  }
  _swift_bridgeObjectRelease(uVar12);
  if (((long)puVar11 < 0) || (((ulong)puVar11 >> 0x3e & 1) != 0)) {
    puVar16 = puVar11;
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  else {
    puVar16 = *(undefined **)(puVar11 + 0x10);
  }
  _swift_release(puVar11);
  if (puVar16 == (undefined *)0x0) {
    puVar11 = &_OBJC_CLASS___NSNotificationCenter;
    _swift_getInitializedObjCClass();
    self = _objc_msgSend((ID)puVar11,"defaultCenter");
    if (DAT_100adeae8 != -1) {
      _swift_once(&DAT_100adeae8,FUN_1001f8d60);
    }
    _objc_msgSend(self,"postNotificationName:object:",DAT_100b758b0,0);
  }
LAB_10002cbe0:
  if (1 < ((uint)local_c0 & 0xff) - 2) {
    if (((uint)local_c0 & 0xff) == 1) {
      return;
    }
    if (((ulong)dVar17 & 1) != 0) {
      uVar6 = *(undefined8 *)(unaff_x20 + _TtC8Playback9SongTrack::fadeWorkItem);
      *(undefined8 *)(unaff_x20 + _TtC8Playback9SongTrack::fadeWorkItem) = 0;
      _swift_release(uVar6);
      return;
    }
  }
  FUN_100743430();
  return;
}


