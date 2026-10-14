// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 10086ba58 0
// ===== FUN_10086ba58 @ 10086ba58 (depth 0)

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10086ba58(uint param_1)

{
  ID self;
  long unaff_x20;
  long lVar1;
  
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if ((*(long *)(DAT_100b75e40 + 0x18) != 0) &&
     (lVar1 = *(long *)(*(long *)(DAT_100b75e40 + 0x18) + 0x18), lVar1 != 0)) {
    _swift_retain(lVar1);
    FUN_100647c80(param_1 & 1,0,0,0);
    _swift_release(lVar1);
  }
  self = unaff_x20 + _TtC8Playback23TransportViewController::fadeButton;
  _swift_unknownObjectWeakLoadStrong();
  if (self != 0) {
    _objc_msgSend(self,"setSelected:",(ulong)(param_1 & 1));
  }
  FUN_100867240();
  return;
}


