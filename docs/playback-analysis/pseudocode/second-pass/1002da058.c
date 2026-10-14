// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1002da058 0
// ===== FUN_1002da058 @ 1002da058 (depth 0)

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1002da058(void)

{
  code *pcVar1;
  uint uVar2;
  ID IVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ID unaff_x20;
  
  IVar3 = _objc_msgSend(unaff_x20,"storedTransition");
  uVar2 = (uint)IVar3;
  FUN_100142b7c();
  if ((((uVar2 & 0xff) != 4) && (IVar3 = _objc_msgSend(unaff_x20,"song"), IVar3 != 0)) &&
     (uVar4 = _objc_msgSend(IVar3,"setlist"), uVar4 != 0)) {
    FUN_1004a6154();
    if (uVar4 >> 0x3e == 0) {
      uVar5 = *(ulong *)((uVar4 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar5 = uVar4 & 0xffffffffffffff8;
      if ((long)uVar4 < 0) {
        uVar5 = uVar4;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar5 == 0) {
      _swift_bridgeObjectRelease(uVar4);
    }
    else {
      uVar6 = uVar5 - 1;
      if (SBORROW8(uVar5,1)) {
        (*pcVar1)();
      }
      if ((uVar4 & 0xc000000000000001) == 0) {
        if ((long)uVar6 < 0) {
          (*pcVar1)();
        }
        if (*(ulong *)((uVar4 & 0xfffffffffffff8) + 0x10) <= uVar6) {
          (*pcVar1)();
        }
        uVar6 = *(ulong *)(uVar4 + uVar6 * 8 + 0x20);
      }
      else {
        FUN_1000cbedc(uVar6,uVar4);
      }
      _swift_bridgeObjectRelease(uVar4);
      FUN_10034293c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(IVar3,uVar6);
    }
  }
  return;
}


