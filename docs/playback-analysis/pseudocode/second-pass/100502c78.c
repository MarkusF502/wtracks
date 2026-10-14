// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 100502c78 0
// ===== FUN_100502c78 @ 100502c78 (depth 0)

void FUN_100502c78(undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  uVar1 = DAT_100b75e40;
  uVar2 = *(undefined8 *)(param_2 + _TtC8Playback9Sequencer::preloadNextSongSequenceTime);
  uVar3 = *(undefined8 *)(param_2 + _TtC8Playback9Sequencer::songTransitionDuration);
  _swift_retain(DAT_100b75e40);
  FUN_1002c6100(uVar2,uVar3,param_1);
  _swift_release(uVar1);
  return;
}


