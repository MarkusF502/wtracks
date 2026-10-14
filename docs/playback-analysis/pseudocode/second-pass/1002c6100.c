// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1002c6100 0
// ===== FUN_1002c6100 @ 1002c6100 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001002c61f0) */

ID FUN_1002c6100(undefined8 param_1,undefined8 param_2,ID param_3)

{
  char cVar1;
  undefined *puVar2;
  uint uVar3;
  undefined8 uVar4;
  ulong uVar5;
  ID IVar6;
  ID IVar7;
  ID IVar8;
  undefined1 uVar9;
  long unaff_x20;
  long lVar10;
  long lVar11;
  long lVar12;
  
  lVar10 = _TtC8Playback4Song::timelineOnUnload;
  if (*(long *)(unaff_x20 + 0x28) != 0) {
    return param_3;
  }
  cVar1 = *(char *)(param_3 + _TtC8Playback4Song::timelineOnUnload);
  if (cVar1 != '\x03') {
    if (DAT_100adfbb8 != -1) {
      _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
    }
    lVar11 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    uVar3 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
    if ((uVar3 == 1) || (uVar3 == 2 && *(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)) {
      if (cVar1 != '\x01') goto LAB_1002c649c;
    }
    else if (cVar1 != '\x02') {
LAB_1002c649c:
      uVar5 = *(ulong *)(param_3 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (uVar5 == 0) {
        IVar6 = _objc_msgSend(param_3,"workingCopyArrangementID");
        if (IVar6 != 0) {
          IVar7 = IVar6;
          FUN_10032ee88();
          IVar8 = IVar7;
          FUN_1005e3b94(IVar7,IVar6);
          _swift_bridgeObjectRelease(IVar7);
          if (IVar8 != 0) {
            *(ID *)(param_3 + lVar11) = IVar8;
            uVar5 = 0;
            goto LAB_1002c64ac;
          }
        }
      }
      else {
LAB_1002c64ac:
        FUN_1002e272c();
        if ((uVar5 & 1) != 0) {
          lVar11 = 0;
          FUN_100861310();
          _swift_allocObject();
          puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined **)(lVar11 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined8 *)(lVar11 + 0x28) = 0;
          *(undefined8 *)(lVar11 + 0x20) = 0;
          *(undefined8 *)(lVar11 + 0x38) = 0;
          *(undefined8 *)(lVar11 + 0x30) = 0;
          _swift_unknownObjectUnownedInit(lVar11 + 0x10,param_3);
          _swift_retain(puVar2);
          FUN_10085ee38();
          uVar4 = *(undefined8 *)(param_3 + _TtC8Playback4Song::privateSongMap);
          *(long *)(param_3 + _TtC8Playback4Song::privateSongMap) = lVar11;
          _swift_release(uVar4);
          uVar3 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
          if ((uVar3 == 1) ||
             ((uVar3 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
            uVar9 = 1;
          }
          else {
            uVar9 = 2;
          }
          *(undefined1 *)(param_3 + lVar10) = uVar9;
        }
      }
    }
  }
  FUN_1004ff050();
  _swift_allocObject();
  IVar6 = param_3;
  FUN_100504280();
  uVar4 = *(undefined8 *)(unaff_x20 + 0x28);
  *(ID *)(unaff_x20 + 0x28) = IVar6;
  _swift_release(uVar4);
  uVar5 = _objc_msgSend(param_3,"contentTypeID");
  FUN_100419df0();
  uVar3 = (uint)uVar5;
  if ((uVar3 & 0xff) == 0xd) {
    uVar5 = _objc_msgSend(param_3,"setClickTimes:",0);
  }
  FUN_100324eb0();
  if ((uVar5 & 1) == 0) {
    FUN_1001bd09c(0);
  }
  else if ((uVar3 & 0xff) != 0xd) goto LAB_1002c62e4;
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar6 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar6);
LAB_1002c62e4:
  lVar10 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  if (*(long *)(param_3 + _TtC8Playback4Song::privateWorkingCopyArrangement) == 0) {
    IVar6 = _objc_msgSend(param_3,"workingCopyArrangementID");
    if (IVar6 == 0) {
      return 0;
    }
    IVar7 = IVar6;
    FUN_10032ee88();
    IVar8 = IVar7;
    FUN_1005e3b94(IVar7,IVar6);
    _swift_bridgeObjectRelease(IVar7);
    if (IVar8 == 0) {
      return 0;
    }
    *(ID *)(param_3 + lVar10) = IVar8;
    lVar10 = *(long *)(unaff_x20 + 0x20);
  }
  else {
    lVar10 = *(long *)(unaff_x20 + 0x20);
  }
  if (((lVar10 != 0) && (lVar11 = *(long *)(unaff_x20 + 0x28), lVar11 != 0)) &&
     (lVar12 = *(long *)(unaff_x20 + 0x18), lVar12 != 0)) {
    _swift_retain();
    _swift_retain(lVar12);
    _swift_retain(lVar11);
    _swift_retain(lVar10);
    FUN_100737cdc(param_1,param_2,param_3,lVar12,lVar11);
    _swift_release(lVar12);
    _swift_release(lVar10);
    _swift_release(lVar11);
    _swift_release();
  }
  return 0;
}


