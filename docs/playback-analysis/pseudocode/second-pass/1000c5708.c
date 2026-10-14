// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1000c5708 0
// ===== FUN_1000c5708 @ 1000c5708 (depth 0)

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1000c5708(void)

{
  uint uVar1;
  ID IVar2;
  ID IVar3;
  ID unaff_x20;
  
  IVar2 = _objc_msgSend(unaff_x20,"isClickOrGuide");
  IVar3 = 0;
  if (IVar2 != 0) {
    IVar2 = _objc_msgSend(IVar2,"boolValue");
    IVar3 = 0;
    if ((int)IVar2 != 0) {
      IVar2 = _objc_msgSend(unaff_x20,"partID");
      IVar3 = 0;
      if (IVar2 != 0) {
        IVar3 = _objc_msgSend(IVar2,"integerValue");
        FUN_10056fe0c();
        uVar1 = (uint)IVar3 & 0xff;
        if (uVar1 != 8 && uVar1 != 1) {
          return 1;
        }
      }
    }
  }
  FUN_1000c588c();
  return IVar3;
}


