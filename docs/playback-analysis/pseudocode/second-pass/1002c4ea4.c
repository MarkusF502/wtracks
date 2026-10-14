// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1002c4ea4 0
// ===== FUN_1002c4ea4 @ 1002c4ea4 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

long FUN_1002c4ea4(uint param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  long unaff_x20;
  long lVar3;
  
  lVar3 = *(long *)(unaff_x20 + 0x28);
  if (lVar3 == 0) {
    uVar1 = 0;
  }
  else {
    _swift_retain(lVar3);
    FUN_1004f5388(0);
    _swift_release(lVar3);
    uVar1 = *(undefined8 *)(unaff_x20 + 0x28);
  }
  *(undefined8 *)(unaff_x20 + 0x28) = 0;
  _swift_release(uVar1);
  lVar3 = *(long *)(unaff_x20 + 0x18);
  if (lVar3 != 0) {
    _swift_retain(lVar3);
    FUN_1007337d4(param_1 & 1);
    _swift_release(lVar3);
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar2 = DAT_100b757a8;
  FUN_100171514();
  if (((uVar2 & 1) != 0) && (lVar3 = *(long *)(unaff_x20 + 0x18), lVar3 != 0)) {
    _swift_retain(lVar3);
    FUN_100732ddc();
    _swift_release(lVar3);
    return lVar3;
  }
  return 0;
}


