// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1004fbb78 0
// ===== FUN_1004fbb78 @ 1004fbb78 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined1  [16] FUN_1004fbb78(double param_1)

{
  long lVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  undefined8 uVar5;
  long unaff_x20;
  ID self;
  double dVar6;
  undefined1 auVar7 [16];
  
  lVar1 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  self = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::song);
  IVar2 = *(ID *)(self + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar2 == 0) {
    IVar3 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar3 != 0) {
      IVar4 = IVar3;
      FUN_10032ee88();
      IVar2 = IVar4;
      FUN_1005e3b94(IVar4,IVar3);
      _swift_bridgeObjectRelease(IVar4);
      if (IVar2 != 0) {
        *(ID *)(self + lVar1) = IVar2;
        goto LAB_1004fbbb4;
      }
    }
    dVar6 = 0.0;
    uVar5 = 1;
  }
  else {
LAB_1004fbbb4:
    _objc_msgSend(IVar2,"storedEndTime");
    dVar6 = param_1;
    IVar2 = _objc_msgSend(IVar2,"song");
    if (IVar2 == 0) {
      dVar6 = 1.0;
    }
    else {
      FUN_1003220ec();
    }
    uVar5 = 0;
    dVar6 = param_1 * dVar6 + -5.0;
  }
  auVar7._8_8_ = uVar5;
  auVar7._0_8_ = dVar6;
  return auVar7;
}


