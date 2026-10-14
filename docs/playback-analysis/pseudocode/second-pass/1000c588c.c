// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1000c588c 0
// ===== FUN_1000c588c @ 1000c588c (depth 0)

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

bool FUN_1000c588c(void)

{
  uint uVar1;
  ID IVar2;
  ID unaff_x20;
  
  IVar2 = _objc_msgSend(unaff_x20,"isClickOrGuide");
  if (IVar2 == 0) {
    return false;
  }
  IVar2 = _objc_msgSend(IVar2,"boolValue");
  if ((int)IVar2 != 0) {
    IVar2 = _objc_msgSend(unaff_x20,"partID");
    if (IVar2 == 0) {
      return false;
    }
    IVar2 = _objc_msgSend(IVar2,"integerValue");
    uVar1 = (uint)IVar2;
    FUN_10056fe0c();
    uVar1 = uVar1 & 0xff;
    if (uVar1 != 0x10) {
      return uVar1 == 1 || uVar1 == 8;
    }
  }
  return false;
}


