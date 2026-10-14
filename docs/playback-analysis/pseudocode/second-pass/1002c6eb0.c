// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1002c6eb0 0
// ===== FUN_1002c6eb0 @ 1002c6eb0 (depth 0)

void FUN_1002c6eb0(undefined8 param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  long lVar2;
  undefined1 auStack_48 [24];
  
  _swift_beginAccess(param_3 + 0x10,auStack_48,0,0);
  param_3 = param_3 + 0x10;
  _swift_weakLoadStrong();
  if (param_3 == 0) {
    return;
  }
  lVar1 = *(long *)(param_3 + 0x18);
  if (lVar1 != 0) {
    lVar2 = *(long *)(lVar1 + 0x18);
    if (lVar2 != 0) {
      _swift_retain(lVar2);
      FUN_100647514(param_1,param_2,1);
      _swift_release(lVar2);
      lVar1 = *(long *)(param_3 + 0x18);
      if (lVar1 == 0) goto LAB_1002c6f60;
    }
    if (*(long *)(lVar1 + 0x20) != 0) {
      _swift_retain(*(long *)(lVar1 + 0x20));
      FUN_100647514(param_1,param_2,0);
      _swift_release(param_3);
    }
  }
LAB_1002c6f60:
  _swift_release();
  return;
}


