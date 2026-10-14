// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 100647c80 0
// ===== FUN_100647c80 @ 100647c80 (depth 0)

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100647c80(ulong param_1,undefined8 param_2,ulong param_3,uint param_4)

{
  undefined8 *puVar1;
  undefined *self;
  ID self_00;
  long lVar2;
  long lVar3;
  code *pcVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  
  self = &_OBJC_CLASS___NSNotificationCenter;
  _swift_getInitializedObjCClass();
  self_00 = _objc_msgSend((ID)self,"defaultCenter");
  if (DAT_100adeae0 != -1) {
    _swift_once(&DAT_100adeae0,FUN_1001f8d2c);
  }
  _objc_msgSend(self_00,"postNotificationName:object:",DAT_100b758a8,0);
  lVar2 = 0;
  FUN_10064458c();
  lVar6 = *(long *)(lVar2 + 0x10);
  if (lVar6 != 0) {
    plVar5 = (long *)(lVar2 + 0x30);
    do {
      lVar7 = plVar5[-2];
      lVar8 = *plVar5;
      lVar3 = lVar7;
      _swift_getObjectType();
      pcVar4 = *(code **)(lVar8 + 0x18);
      _swift_unknownObjectRetain(lVar7);
      (*pcVar4)(lVar3,lVar8);
      if (lVar3 == 0) {
LAB_100647d34:
        _swift_unknownObjectRelease(lVar7);
      }
      else {
        if (DAT_100adef08 != -1) {
          _swift_once(&DAT_100adef08,FUN_1002c44b8);
        }
        if (((*(long *)(DAT_100b75e40 + 0x20) == 0) ||
            ((*(char *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::privatePlayState)
              != '\x01' || (param_3 & 0xff) != 0) || (param_1 & 1) != 0)) ||
           (*(char *)(lVar3 + _TtC8Playback9SongTrack::currentFadeVolume + 8) != '\x01')) {
          FUN_10002a5fc(param_1,param_2,param_3,param_4 & 1,0,1);
          if ((*(long *)(DAT_100b75e40 + 0x20) == 0) ||
             ((*(byte *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::privatePlayState
                        ) & 1) == 0)) {
            if ((((uint)param_3 & 0xff) != 1 && (param_3 & 0xff) != 0) || ((param_3 & 0xff) != 0))
            goto LAB_100647d34;
            _swift_unknownObjectRelease(lVar7);
            if ((param_1 & 1) == 0) {
              puVar1 = (undefined8 *)(lVar3 + _TtC8Playback9SongTrack::currentFadeVolume);
              *puVar1 = 0;
              *(undefined1 *)(puVar1 + 1) = 1;
            }
            goto LAB_100647d3c;
          }
        }
        _swift_unknownObjectRelease(lVar7);
      }
LAB_100647d3c:
      plVar5 = plVar5 + 3;
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
  }
  _swift_bridgeObjectRelease(lVar2);
  return;
}


