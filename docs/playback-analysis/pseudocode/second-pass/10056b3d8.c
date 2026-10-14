// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 10056b3d8 0
// ===== FUN_10056b3d8 @ 10056b3d8 (depth 0)

void FUN_10056b3d8(long param_1)

{
  code *pcVar1;
  undefined8 uVar2;
  
  pcVar1 = *(code **)(param_1 + 0x20);
  uVar2 = *(undefined8 *)(param_1 + 0x28);
  _swift_retain(uVar2);
  (*pcVar1)();
  _swift_release(uVar2);
  return;
}


