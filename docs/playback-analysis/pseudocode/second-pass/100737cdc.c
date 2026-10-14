// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 100737cdc 0
// ===== FUN_100737cdc @ 100737cdc (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x000100737e64) */

void FUN_100737cdc(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  long lVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined *puVar5;
  undefined8 uVar6;
  
  puVar1 = &DAT_100a611a0;
  _swift_allocObject(&DAT_100a611a0,0x40,7);
  *(undefined8 *)(puVar1 + 0x10) = param_5;
  *(undefined8 *)(puVar1 + 0x18) = param_6;
  *(undefined8 *)(puVar1 + 0x20) = param_7;
  *(undefined8 *)(puVar1 + 0x28) = param_8;
  *(undefined8 *)(puVar1 + 0x30) = param_1;
  *(undefined8 *)(puVar1 + 0x38) = param_2;
  lVar2 = DAT_100adef08;
  if (*(long *)(param_4 + 0x20) == 0) {
    _swift_retain(param_5);
    _swift_retain(param_6);
    _swift_retain(param_8);
    if (lVar2 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    puVar5 = *(undefined **)(DAT_100b75e40 + 0x28);
    if (puVar5 != (undefined *)0x0) {
      uVar4 = *(undefined8 *)(param_4 + 0x60);
      uVar6 = *(undefined8 *)(param_4 + 0x10);
      FUN_1006502d0();
      _swift_allocObject();
      _swift_retain_n(puVar5,2);
      FUN_10064c530(param_3,uVar4,uVar6,puVar5);
      uVar4 = *(undefined8 *)(param_4 + 0x20);
      *(undefined8 *)(param_4 + 0x20) = param_3;
      _swift_release(uVar4);
      lVar2 = *(long *)(param_4 + 0x20);
      if (lVar2 != 0) {
        _swift_retain(lVar2);
        FUN_100648190(0);
        _swift_release(lVar2);
        puVar3 = *(undefined **)(param_4 + 0x20);
        if (puVar3 != (undefined *)0x0) {
          uVar4 = *(undefined8 *)(param_4 + 0x28);
          _swift_retain(puVar3);
          FUN_100650694(uVar4,FUN_100738028,puVar1);
          _swift_release(puVar1);
          puVar1 = puVar3;
        }
      }
      _swift_release(puVar1);
      goto LAB_100737d8c;
    }
  }
  else {
    _swift_retain(param_5);
    _swift_retain(param_6);
    _swift_retain(param_8);
  }
  FUN_1002c662c(param_1,param_2,param_5,param_6,param_7,param_8);
  puVar5 = puVar1;
LAB_100737d8c:
  _swift_release(puVar5);
  return;
}


