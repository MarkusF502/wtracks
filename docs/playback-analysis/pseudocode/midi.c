// Playback main executable sha256 2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423
// Ghidra 12.1.4 decompiler output, feature "midi": functions whose pseudocode matches /MIDIBank|MIDIBus|MIDIEvent|ControlMapping|MIDIOutAVAudioUnit|MIDIClockAVAudioUnit/
// Addresses are image-relative VM addresses as exported (e.g. 100545a98).

// ==== 100027f64 FUN_100027f64 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_100027f64(double param_1,double param_2,undefined8 param_3,undefined8 param_4,ID param_5,
                char param_6,ushort param_7,ushort param_8,uint param_9,undefined8 param_10,
                long param_11)

{
  undefined8 *puVar1;
  char *pcVar2;
  undefined8 uVar3;
  undefined1 uVar4;
  char cVar5;
  ID IVar6;
  ID IVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  uint uVar10;
  ID unaff_x20;
  
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar6 = _objc_msgSend(DAT_100b755c8,"viewContext");
  IVar6 = _objc_msgSend(unaff_x20,"initWithContext:",IVar6);
  _objc_msgSend(IVar6,"setId:",param_4);
  _objc_msgSend(IVar6,"setDuration:",param_3);
  _objc_msgSend(IVar6,"setBus:",param_5);
  IVar7 = _objc_msgSend(param_5,"id");
  _objc_msgSend(IVar6,"setBusID:",IVar7);
  _objc_msgSend(IVar6,"setStoredType:",(long)*(short *)(&DAT_10091dfde + (long)param_6 * 2));
  _objc_msgSend(IVar6,"setDisableLoop:",(ulong)(param_9 & 1));
  if (param_11 == 0) {
    param_10 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_10,param_11);
    _swift_bridgeObjectRelease(param_11);
  }
  _objc_msgSend(IVar6,"setEventDescription:",param_10);
  if (0.0 <= param_1) {
    _objc_msgSend(IVar6,"setSequenceTimecode:",param_1);
  }
  else {
    _objc_msgSend(IVar6,"setSequenceTimecode:",0);
    puVar1 = (undefined8 *)(IVar6 + _TtC8Playback9MIDIEvent::initializationError);
    uVar3 = *puVar1;
    uVar9 = puVar1[1];
    uVar8 = puVar1[2];
    *puVar1 = 0xd000000000000010;
    puVar1[1] = 0x80000001008d0370;
    puVar1[2] = param_1;
    uVar4 = *(undefined1 *)(puVar1 + 3);
    *(undefined1 *)(puVar1 + 3) = 2;
    FUN_100028d64(uVar3,uVar9,uVar8,uVar4);
  }
  if (0.0 <= param_2) {
    _objc_msgSend(IVar6,"setSampleTimecode:",param_2);
  }
  else {
    _objc_msgSend(IVar6,"setSampleTimecode:",0);
    pcVar2 = (char *)(IVar6 + _TtC8Playback9MIDIEvent::initializationError);
    uVar3 = *(undefined8 *)(pcVar2 + 8);
    uVar9 = *(undefined8 *)(pcVar2 + 0x10);
    pcVar2[8] = 'm';
    pcVar2[9] = 'e';
    pcVar2[10] = 'c';
    pcVar2[0xb] = 'o';
    pcVar2[0xc] = 'd';
    pcVar2[0xd] = 'e';
    pcVar2[0xe] = '\0';
    pcVar2[0xf] = -0x12;
    pcVar2[0] = 's';
    pcVar2[1] = 'a';
    pcVar2[2] = 'm';
    pcVar2[3] = 'p';
    pcVar2[4] = 'l';
    pcVar2[5] = 'e';
    pcVar2[6] = 'T';
    pcVar2[7] = 'i';
    *(double *)(pcVar2 + 0x10) = param_2;
    cVar5 = pcVar2[0x18];
    pcVar2[0x18] = '\x02';
    FUN_100028d64(*(undefined8 *)pcVar2,uVar3,uVar9,cVar5);
  }
  if (param_7 < 0x80) {
    _objc_msgSend(IVar6,"setNote:",(ulong)(uint)(int)(short)param_7);
  }
  else {
    uVar10 = 0;
    if (-1 < (short)param_7) {
      uVar10 = 0x7f;
    }
    _objc_msgSend(IVar6,"setNote:",(ulong)uVar10);
    puVar1 = (undefined8 *)(IVar6 + _TtC8Playback9MIDIEvent::initializationError);
    uVar3 = *puVar1;
    uVar9 = puVar1[1];
    uVar8 = puVar1[2];
    puVar1[1] = 0xe400000000000000;
    *puVar1 = 0x65746f4e;
    puVar1[2] = (ulong)param_7;
    uVar4 = *(undefined1 *)(puVar1 + 3);
    *(undefined1 *)(puVar1 + 3) = 0;
    FUN_100028d64(uVar3,uVar9,uVar8,uVar4);
  }
  if (param_8 < 0x80) {
    _objc_msgSend(IVar6,"setVelocity:",(ulong)(uint)(int)(short)param_8);
  }
  else {
    uVar10 = 0;
    if (-1 < (short)param_8) {
      uVar10 = 0x7f;
    }
    _objc_msgSend(IVar6,"setVelocity:",(ulong)uVar10);
    pcVar2 = (char *)(IVar6 + _TtC8Playback9MIDIEvent::initializationError);
    uVar3 = *(undefined8 *)(pcVar2 + 8);
    uVar9 = *(undefined8 *)(pcVar2 + 0x10);
    pcVar2[8] = '\0';
    pcVar2[9] = '\0';
    pcVar2[10] = '\0';
    pcVar2[0xb] = '\0';
    pcVar2[0xc] = '\0';
    pcVar2[0xd] = '\0';
    pcVar2[0xe] = '\0';
    pcVar2[0xf] = -0x18;
    pcVar2[0] = 'V';
    pcVar2[1] = 'e';
    pcVar2[2] = 'l';
    pcVar2[3] = 'o';
    pcVar2[4] = 'c';
    pcVar2[5] = 'i';
    pcVar2[6] = 't';
    pcVar2[7] = 'y';
    *(ulong *)(pcVar2 + 0x10) = (ulong)param_8;
    cVar5 = pcVar2[0x18];
    pcVar2[0x18] = '\0';
    FUN_100028d64(*(undefined8 *)pcVar2,uVar3,uVar9,cVar5);
  }
  return IVar6;
}

// ==== 10002871c _TtC8Playback9MIDIEvent::initWithEntity:insertIntoManagedObjectContext: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback9MIDIEvent::initWithEntity_insertIntoManagedObjectContext_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithEntity:insertIntoManagedObjectContext:",param_3,
                              param_4);
  return IVar2;
}

// ==== 100028770 _TtC8Playback9MIDIEvent::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback9MIDIEvent::_cxx_construct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + initializationError);
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 3) = 0xff;
  *(undefined1 *)(param_1 + isNudging) = 0;
  return;
}

// ==== 10002879c _TtC8Playback9MIDIEvent::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback9MIDIEvent::_cxx_destruct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + initializationError);
  FUN_100028d64(*puVar1,puVar1[1],puVar1[2],*(undefined1 *)(puVar1 + 3));
  return;
}

// ==== 1000287b8 FUN_1000287b8 ====
void FUN_1000287b8(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback9MIDIEvent);
  return;
}

// ==== 1000f0420 FUN_1000f0420 ====
bool FUN_1000f0420(float param_1)

{
  undefined1 *puVar1;
  long lVar2;
  ID self;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_38 [24];
  
  lVar3 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  lVar2 = *(long *)(unaff_x20 + 0x18);
  puVar1 = auStack_38;
  _swift_beginAccess(lVar2 + _TtC8Playback20MIDIClockAVAudioUnit::parameters,puVar1,0x20,0);
  lVar3 = *(long *)(lVar2 + lVar3);
  if (*(long *)(lVar3 + 0x10) != 0) {
    lVar2 = 1;
    thunk_FUN_100793c60();
    if (((ulong)puVar1 & 1) != 0) {
      self = *(ID *)(*(long *)(lVar3 + 0x38) + lVar2 * 8);
      _swift_endAccess(auStack_38);
      _objc_msgSend(self,"value");
      return param_1 != 0.0;
    }
  }
  _swift_endAccess(auStack_38);
  return false;
}

// ==== 1000f04b0 FUN_1000f04b0 ====
void FUN_1000f04b0(ulong param_1)

{
  undefined1 *puVar1;
  long unaff_x20;
  long lVar2;
  long lVar3;
  ID self;
  undefined4 uVar4;
  undefined1 auStack_48 [24];
  
  lVar3 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  lVar2 = *(long *)(unaff_x20 + 0x18);
  puVar1 = auStack_48;
  _swift_beginAccess(lVar2 + _TtC8Playback20MIDIClockAVAudioUnit::parameters,puVar1,0x20,0);
  lVar3 = *(long *)(lVar2 + lVar3);
  if (*(long *)(lVar3 + 0x10) != 0) {
    lVar2 = 1;
    thunk_FUN_100793c60();
    if (((ulong)puVar1 & 1) != 0) {
      self = *(ID *)(*(long *)(lVar3 + 0x38) + lVar2 * 8);
      _swift_endAccess(auStack_48);
      uVar4 = 0x3f800000;
      if ((param_1 & 1) == 0) {
        uVar4 = 0;
      }
      _objc_msgSend(self,"setValue:",uVar4);
      return;
    }
  }
  _swift_endAccess(auStack_48);
  return;
}

// ==== 1000f0550 FUN_1000f0550 ====
void FUN_1000f0550(double param_1)

{
  undefined1 *puVar1;
  long lVar2;
  ID self;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_48 [24];
  
  lVar3 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  lVar2 = *(long *)(unaff_x20 + 0x18);
  puVar1 = auStack_48;
  _swift_beginAccess(lVar2 + _TtC8Playback20MIDIClockAVAudioUnit::parameters,puVar1,0x20,0);
  lVar3 = *(long *)(lVar2 + lVar3);
  if (*(long *)(lVar3 + 0x10) != 0) {
    lVar2 = 2;
    thunk_FUN_100793c60();
    if (((ulong)puVar1 & 1) != 0) {
      self = *(ID *)(*(long *)(lVar3 + 0x38) + lVar2 * 8);
      _swift_endAccess(auStack_48);
      _objc_msgSend(self,"setValue:",(float)param_1);
      return;
    }
  }
  _swift_endAccess(auStack_48);
  return;
}

// ==== 1000f9f24 _TtC8Playback8MIDIBank::initWithEntity:insertIntoManagedObjectContext: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback8MIDIBank::initWithEntity_insertIntoManagedObjectContext_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithEntity:insertIntoManagedObjectContext:",param_3,
                              param_4);
  return IVar2;
}

// ==== 1000f9f78 FUN_1000f9f78 ====
void FUN_1000f9f78(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback8MIDIBank);
  return;
}

// ==== 1001fc498 FUN_1001fc498 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1001fc498(ID param_1,ID param_2)

{
  undefined1 uVar1;
  long lVar2;
  code *pcVar3;
  ID IVar4;
  ulong uVar5;
  ID IVar6;
  undefined8 uVar7;
  ulong uVar8;
  ulong uVar9;
  long unaff_x20;
  ulong uVar10;
  
  uVar10 = *(ulong *)(unaff_x20 + _TtC8Playback36MIDIPortsSelectorTableViewController::selectionMode
                     );
  if (uVar10 < 2) {
    IVar6 = param_1;
    FUN_1001f9d78();
    IVar4 = IVar6;
    __s10Foundation9IndexPathV5UIKitE7sectionSivg();
    if ((-1 < (long)IVar4) && ((long)IVar4 < *(long *)(IVar6 + 0x10))) {
      uVar1 = *(undefined1 *)(IVar6 + IVar4 + 0x20);
      _swift_bridgeObjectRelease(IVar6);
      FUN_1001f95cc(uVar10,uVar1);
      uVar5 = uVar10;
      __s10Foundation9IndexPathV5UIKitE3rowSivg();
      if (uVar10 >> 0x3e == 0) {
        uVar8 = *(ulong *)((uVar10 & 0xfffffffffffff8) + 0x10);
      }
      else {
        uVar8 = uVar10 & 0xffffffffffffff8;
        if ((long)uVar10 < 0) {
          uVar8 = uVar10;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        if ((long)uVar8 < 0) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fc818);
          (*pcVar3)();
        }
      }
      IVar6 = uVar10;
      if ((-1 < (long)uVar5) && (uVar5 < uVar8)) {
        if ((uVar10 & 0xc000000000000001) == 0) {
          if (*(ulong *)((uVar10 & 0xfffffffffffff8) + 0x10) <= uVar5) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fc850);
            (*pcVar3)();
          }
          uVar5 = *(ulong *)(uVar10 + uVar5 * 8 + 0x20);
        }
        else {
          FUN_1000ce880();
        }
        _swift_bridgeObjectRelease(uVar10);
        FUN_1001fa040();
        FUN_1005ca118(uVar5,uVar10);
        _swift_bridgeObjectRelease(uVar10);
        if ((uVar5 & 1) != 0) {
          IVar6 = _objc_msgSend(param_2,"setSelected:animated:",1,0);
          __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
          _objc_msgSend(param_1,"selectRowAtIndexPath:animated:scrollPosition:",IVar6,0,0);
          return 0;
        }
        IVar6 = _objc_msgSend(param_2,"setSelected:animated:",0,0);
        __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
        _objc_msgSend(param_1,"deselectRowAtIndexPath:animated:",IVar6,0);
        return 0;
      }
    }
    _swift_bridgeObjectRelease(IVar6);
    return IVar6;
  }
  uVar5 = uVar10;
  FUN_1001f9d78();
  uVar8 = uVar5;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if ((-1 < (long)uVar8) && ((long)uVar8 < *(long *)(uVar5 + 0x10))) {
    uVar1 = *(undefined1 *)(uVar5 + uVar8 + 0x20);
    _swift_bridgeObjectRelease(uVar5);
    uVar5 = uVar10;
    FUN_1001f95cc(uVar10,uVar1);
    uVar8 = uVar5;
    __s10Foundation9IndexPathV5UIKitE3rowSivg();
    if (uVar5 >> 0x3e == 0) {
      uVar9 = *(ulong *)((uVar5 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar9 = uVar5 & 0xffffffffffffff8;
      if ((long)uVar5 < 0) {
        uVar9 = uVar5;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if ((long)uVar9 < 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fc834);
        (*pcVar3)();
      }
    }
    if ((-1 < (long)uVar8) && (uVar8 < uVar9)) {
      if ((uVar5 & 0xc000000000000001) == 0) {
        if (*(ulong *)((uVar5 & 0xfffffffffffff8) + 0x10) <= uVar8) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fc854);
          (*pcVar3)();
        }
        uVar8 = *(ulong *)(uVar5 + uVar8 * 8 + 0x20);
      }
      else {
        FUN_1000ce880();
      }
      _swift_bridgeObjectRelease(uVar5);
      lVar2 = _TtC8Playback7MIDIBus::privateDestinationEndpoint;
      uVar5 = *(ulong *)(uVar10 + _TtC8Playback7MIDIBus::privateDestinationEndpoint);
      if (uVar5 == 0) {
        if (DAT_100adefa0 != -1) {
          _swift_once(&DAT_100adefa0,FUN_10037c47c);
        }
        uVar9 = DAT_100b75f50;
        uVar5 = DAT_100b75f50;
        _swift_retain();
        FUN_10042f27c();
        uVar5 = uVar5 & 0xffffffff | (uVar5 >> 0x20 & 1) << 0x20;
        FUN_1003824b4();
        _swift_release(uVar9);
        *(ulong *)(uVar10 + lVar2) = uVar5;
        if (uVar5 == 0) goto LAB_1001fc7d4;
      }
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar8,uVar5);
      uVar7 = 0;
      if ((uVar8 & 1) == 0) {
LAB_1001fc7d4:
        FUN_1001fea0c(uVar10);
        return 0;
      }
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF(0);
      _objc_msgSend(param_1,"selectRowAtIndexPath:animated:scrollPosition:",uVar7,1,0);
      goto LAB_1001fc8b0;
    }
  }
  _swift_bridgeObjectRelease(uVar5);
LAB_1001fc8b0:
  FUN_1001fea0c(uVar10);
  return uVar10;
}

// ==== 1001fd0b4 FUN_1001fd0b4 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ulong FUN_1001fd0b4(ID param_1)

{
  undefined1 uVar1;
  ulong uVar2;
  code *pcVar3;
  ID IVar4;
  ID IVar5;
  ulong uVar6;
  undefined *puVar7;
  long lVar8;
  ulong uVar9;
  ID unaff_x20;
  ulong uVar10;
  long lVar11;
  
  IVar4 = param_1;
  FUN_1001f9d78();
  IVar5 = IVar4;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if (((long)IVar5 < 0) || (*(long *)(IVar4 + 0x10) <= (long)IVar5)) {
LAB_1001fd3d8:
    _swift_bridgeObjectRelease(IVar4);
    return IVar4;
  }
  uVar1 = *(undefined1 *)(IVar4 + IVar5 + 0x20);
  _swift_bridgeObjectRelease(IVar4);
  uVar10 = *(ulong *)(unaff_x20 + _TtC8Playback36MIDIPortsSelectorTableViewController::selectionMode
                     );
  IVar4 = uVar10;
  FUN_1001f95cc(uVar10,uVar1);
  uVar6 = IVar4;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (IVar4 >> 0x3e == 0) {
    uVar9 = *(ulong *)((IVar4 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar9 = IVar4 & 0xffffffffffffff8;
    if ((long)IVar4 < 0) {
      uVar9 = IVar4;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if ((long)uVar9 < 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fd3a0);
      (*pcVar3)();
    }
  }
  if (((long)uVar6 < 0) || (uVar9 <= uVar6)) goto LAB_1001fd3d8;
  if ((IVar4 & 0xc000000000000001) == 0) {
    if (*(ulong *)((IVar4 & 0xfffffffffffff8) + 0x10) <= uVar6) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x1001fd3b0);
      (*pcVar3)();
    }
    uVar6 = *(ulong *)(IVar4 + uVar6 * 8 + 0x20);
  }
  else {
    FUN_1000ce880();
  }
  _swift_bridgeObjectRelease(IVar4);
  lVar11 = _TtC8Playback7MIDIBus::privateDestinationEndpoint;
  if (uVar10 < 2) {
    FUN_1001fb240(uVar6);
    return 0;
  }
  uVar9 = *(ulong *)(uVar10 + _TtC8Playback7MIDIBus::privateDestinationEndpoint);
  if (uVar9 == 0) {
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar2 = DAT_100b75f50;
    uVar9 = DAT_100b75f50;
    _swift_retain();
    FUN_10042f27c();
    uVar9 = uVar9 & 0xffffffff | (uVar9 >> 0x20 & 1) << 0x20;
    FUN_1003824b4();
    _swift_release(uVar2);
    *(ulong *)(uVar10 + lVar11) = uVar9;
    if (uVar9 != 0) goto LAB_1001fd24c;
  }
  else {
LAB_1001fd24c:
    FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar9,uVar6);
    if ((uVar9 & 1) != 0) goto LAB_1001fd2e4;
  }
  puVar7 = &_OBJC_CLASS___MIKMIDIDestinationEndpoint;
  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDIDestinationEndpoint);
  _swift_dynamicCastObjCClass(uVar6,puVar7);
LAB_1001fd2e4:
  lVar11 = unaff_x20 + _TtC8Playback36MIDIPortsSelectorTableViewController::delegate;
  lVar8 = lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar8 != 0) {
    lVar11 = *(long *)(lVar11 + 8);
    _swift_getObjectType();
    (**(code **)(lVar11 + 8))();
    _swift_unknownObjectRelease(lVar8);
  }
  _objc_msgSend(param_1,"reloadData");
  _objc_msgSend(unaff_x20,"dismissViewControllerAnimated:completion:",1,0);
  FUN_1001fea0c(uVar10);
  return uVar10;
}

// ==== 100214c58 FUN_100214c58 ====
void FUN_100214c58(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtCC8Playback7SongMap9MIDIEvent);
  return;
}

// ==== 10026e44c FUN_10026e44c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_10026e44c(uint param_1,ID param_2,uint param_3)

{
  long *plVar1;
  byte bVar2;
  undefined *puVar3;
  ID IVar4;
  undefined8 uVar5;
  ID IVar6;
  ID self;
  ID self_00;
  long lVar7;
  
  _objc_msgSend(param_2,"setSelected:",(ulong)((param_1 ^ 0xffffffff) & 1));
  puVar3 = &_OBJC_CLASS___UIApplication;
  _swift_getInitializedObjCClass();
  IVar4 = _objc_msgSend((ID)puVar3,"sharedApplication");
  IVar4 = _objc_msgSend(IVar4,"delegate");
  if (IVar4 != 0) {
    uVar5 = 0;
    FUN_100842dec(0);
    IVar6 = IVar4;
    _swift_dynamicCastClass(IVar4,uVar5);
    if (((IVar6 == 0) || (*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window) == 0)) ||
       (IVar6 = _objc_msgSend(*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window),
                              "rootViewController"), IVar6 == 0)) {
      _swift_unknownObjectRelease(IVar4);
    }
    else {
      uVar5 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar6,uVar5);
      _swift_unknownObjectRelease(IVar4);
      if (((IVar6 != 0) &&
          (*(long *)(IVar6 + _TtC8Playback18MainViewController::waveformViewController) != 0)) &&
         ((lVar7 = *(long *)(*(long *)(IVar6 + _TtC8Playback18MainViewController::
                                               waveformViewController) +
                            _TtC8Playback22WaveformViewController::selectedTimelineMarkerView),
          lVar7 != 0 &&
          (plVar1 = (long *)(lVar7 + _TtC8Playback18TimelineMarkerView::markerType),
          (char)plVar1[2] == '\0')))) {
        self = *(ID *)(*plVar1 + 0x10);
        uVar5 = *(undefined8 *)(param_2 + _TtC8Playback19MixerMuteMIDIButton::mappingID);
        IVar4 = ((undefined8 *)(param_2 + _TtC8Playback19MixerMuteMIDIButton::mappingID))[1];
        IVar6 = IVar4;
        _swift_bridgeObjectRetain();
        FUN_100822b68();
        _swift_bridgeObjectRetain(IVar4);
        self_00 = IVar6;
        FUN_100503f0c(IVar6,uVar5,IVar4);
        _swift_bridgeObjectRelease(IVar6);
        _swift_bridgeObjectRelease_n(IVar4,2);
        if (self_00 == 0) {
          FUN_1003ac3f8(0);
          _swift_bridgeObjectRetain(IVar4);
          IVar6 = _objc_msgSend(param_2,"isSelected");
          FUN_1003abe58(uVar5,IVar4,IVar6);
          _objc_msgSend(self,"addStoredItemsObject:",uVar5);
        }
        else {
          IVar4 = _objc_msgSend(param_2,"isSelected");
          uVar5 = 0x3ff0000000000000;
          if ((int)IVar4 == 0) {
            uVar5 = 0;
          }
          _objc_msgSend(self_00,"setStoredValue:",uVar5);
        }
        *(undefined1 *)(param_2 + _TtC8Playback19MixerMuteMIDIButton::automationState) = 3;
        FUN_100296c1c(0);
        FUN_1007681c8(0);
        goto LAB_10026e6f0;
      }
    }
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if (((*(long *)(DAT_100b75e40 + 0x20) == 0) ||
      (*(char *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::privatePlayState) !=
       '\x01')) ||
     (*(char *)(param_2 + _TtC8Playback19MixerMuteMIDIButton::automationState) != '\x02')) {
    if (((param_3 & 0xff) < 6) && ((1 << (ulong)(param_3 & 0x1f) & 0x25U) != 0)) goto LAB_10026e6f0;
  }
  else if ((param_3 & 0xff) < 6) {
    if ((1 << (ulong)(param_3 & 0x1f) & 0x1aU) != 0) {
      FUN_10024a098(1);
    }
    goto LAB_10026e6f0;
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar7 = DAT_100b757a8;
  IVar4 = _objc_msgSend(param_2,"isSelected");
  *(char *)(lVar7 + _TtC8Playback15DefaultsManager::___lazy_storage___midiOutMuted) = (char)IVar4;
  puVar3 = &_OBJC_CLASS___NSUserDefaults;
  _swift_getInitializedObjCClass();
  IVar6 = _objc_msgSend((ID)puVar3,"standardUserDefaults");
  IVar4 = IVar6;
  FUN_1001736c4();
  uVar5 = 0x74756f2d6964696d;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x74756f2d6964696d,0xee00646574756d2d);
  _objc_msgSend(IVar6,"setBool:forKey:",(ulong)((uint)IVar4 & 1),uVar5);
LAB_10026e6f0:
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if (((*(long *)(DAT_100b75e40 + 0x18) != 0) &&
      (lVar7 = *(long *)(*(long *)(DAT_100b75e40 + 0x18) + 0x18), lVar7 != 0)) &&
     (lVar7 = *(long *)(lVar7 + _TtC8Playback16SongChannelGroup::midiOutChannel), lVar7 != 0)) {
    _swift_retain(lVar7);
    IVar4 = _objc_msgSend(param_2,"isSelected");
    bVar2 = (byte)IVar4 ^ 1;
    *(byte *)(lVar7 + 0x40) = bVar2;
    *(byte *)(*(long *)(lVar7 + 0x38) + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = bVar2;
    FUN_10049ffc8();
    _swift_release(lVar7);
    return;
  }
  return;
}

// ==== 100279ff4 FUN_100279ff4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined1  [16] FUN_100279ff4(ulong param_1)

{
  char *pcVar1;
  bool bVar2;
  undefined *self;
  ID IVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined1 auVar6 [16];
  
  self = &_OBJC_CLASS___NSBundle;
  _swift_getInitializedObjCClass();
  IVar3 = _objc_msgSend((ID)self,"mainBundle");
  bVar2 = (param_1 & 1) == 0;
  pcVar1 = "TimelineMIDIEventCopyCell";
  if (bVar2) {
    pcVar1 = "Paste Section Cues";
  }
  uVar5 = 0xd000000000000011;
  if (!bVar2) {
    uVar5 = 0xd000000000000012;
  }
  uVar4 = (ulong)pcVar1 | 0x8000000000000000;
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (uVar5,uVar4,0,0,IVar3,0,0xe000000000000000,0,0xe000000000000000);
  auVar6._8_8_ = uVar4;
  auVar6._0_8_ = uVar5;
  return auVar6;
}

// ==== 10027a3f4 FUN_10027a3f4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_10027a3f4(ID param_1)

{
  byte bVar1;
  code *pcVar2;
  undefined8 uVar3;
  ID self;
  undefined *self_00;
  ID IVar4;
  ulong uVar5;
  long lVar6;
  char *pcVar7;
  long unaff_x20;
  ulong uVar8;
  
  uVar3 = 0xd00000000000001d;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
  self = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:",uVar3);
  if (self == 0) {
    self_00 = &_OBJC_CLASS___UITableViewCell;
    _objc_allocWithZone();
    uVar3 = 0xd00000000000001d;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
    self = _objc_msgSend((ID)self_00,"initWithStyle:reuseIdentifier:",1,uVar3);
  }
  uVar8 = 0;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (uVar8 < 2) {
    bVar1 = (&DAT_100ae87a8)[uVar8];
    uVar8 = (ulong)bVar1;
    pcVar7 = "textLabel";
    IVar4 = _objc_msgSend(self,"textLabel");
    if (IVar4 != 0) {
      uVar5 = uVar8;
      FUN_100279ff4(uVar8);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
      _swift_bridgeObjectRelease(pcVar7);
      _objc_msgSend(IVar4,"setText:",uVar5);
    }
    lVar6 = -4;
    if (bVar1 != 0) {
      lVar6 = -3;
    }
    pcVar7 = "TimelineMIDIEventPasteCell";
    if (bVar1 == 0) {
      pcVar7 = "TimelineMIDIEventCopyCell";
    }
    lVar6 = lVar6 + -0x2fffffffffffffe3;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
              (lVar6,(ulong)(pcVar7 + -0x20) | 0x8000000000000000);
    _swift_bridgeObjectRelease((ulong)(pcVar7 + -0x20) | 0x8000000000000000);
    _objc_msgSend(self,"setAccessibilityIdentifier:",lVar6);
    IVar4 = _objc_msgSend(self,"textLabel");
    if (IVar4 != 0) {
      thunk_FUN_1005ca3dc(uVar8,*(undefined8 *)
                                 (unaff_x20 +
                                 _TtC8Playback36MIDICuesCopyPasteTableViewController::optionsEnabled
                                 ));
      uVar3 = 0x3ff0000000000000;
      if ((uVar8 & 1) == 0) {
        uVar3 = 0x3fd3333333333333;
      }
      _objc_msgSend(IVar4,"setAlpha:",uVar3);
    }
    return self;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(1,0x10027a620);
  (*pcVar2)();
}

// ==== 100295fd8 FUN_100295fd8 ====
void FUN_100295fd8(void)

{
  FUN_100295ff8(&_TtC8Playback18MIDIOutAVAudioUnit::prerollOffsetTime,6);
  return;
}

// ==== 100295fe8 FUN_100295fe8 ====
void FUN_100295fe8(void)

{
  FUN_100295ff8(&_TtC8Playback18MIDIOutAVAudioUnit::rewindTime,7);
  return;
}

// ==== 100295ff8 FUN_100295ff8 ====
void FUN_100295ff8(undefined8 param_1,long *param_2,long param_3)

{
  undefined1 *puVar1;
  ID self;
  long unaff_x20;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined1 auStack_48 [24];
  
  lVar3 = *(long *)(unaff_x20 + 0x38);
  lVar4 = *param_2;
  *(undefined8 *)(lVar3 + lVar4) = param_1;
  lVar2 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  puVar1 = auStack_48;
  _swift_beginAccess(lVar3 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,puVar1,0x20,0);
  lVar2 = *(long *)(lVar3 + lVar2);
  if ((*(long *)(lVar2 + 0x10) == 0) || (thunk_FUN_100793c60(), ((ulong)puVar1 & 1) == 0)) {
    _swift_endAccess(auStack_48);
  }
  else {
    self = *(ID *)(*(long *)(lVar2 + 0x38) + param_3 * 8);
    _swift_endAccess(auStack_48);
    _objc_msgSend(self,"setValue:",(ulong)(uint)(float)*(double *)(lVar3 + lVar4));
  }
  return;
}

// ==== 10029611c FUN_10029611c ====
void FUN_10029611c(byte param_1)

{
  long unaff_x20;
  
  *(byte *)(unaff_x20 + 0x30) = param_1 & 1;
  *(byte *)(*(long *)(unaff_x20 + 0x38) + _TtC8Playback18MIDIOutAVAudioUnit::playState) =
       param_1 & 1;
  FUN_10049fe84();
  return;
}

// ==== 10029c568 _TtC8Playback31SongMenuMIDIBanksViewController::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  code *pcVar2;
  
  *(undefined8 *)(param_1 + song) = 0;
  lVar1 = param_1 + midiBankSelectionDelegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd000000000000025,0x80000001008d1460,
             "Playback/SongMenuMIDIBanksViewController.swift",0x2e,2,0x56,0);
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(1,0x10029c600);
  (*pcVar2)();
}

// ==== 10029ca3c _TtC8Playback31SongMenuMIDIBanksViewController::viewDidLoad ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback31SongMenuMIDIBanksViewController::viewDidLoad(ID param_1,SEL param_2)

{
  FUN_10029c600(param_1);
  return;
}

// ==== 10029ca64 FUN_10029ca64 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_10029ca64(void)

{
  undefined8 uVar1;
  code *pcVar2;
  ID IVar3;
  undefined8 uVar4;
  ID IVar5;
  ulong uVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  ID unaff_x20;
  undefined1 *puVar11;
  undefined1 *puVar12;
  long lVar13;
  
  IVar5 = unaff_x20;
  _swift_getObjectType();
  IVar3 = _objc_msgSend(unaff_x20,"tableView");
  if ((IVar3 == 0) || (IVar3 = _objc_msgSend(IVar3,"isEditing"), (IVar3 & 1) != 0)) {
    IVar3 = _objc_msgSend(unaff_x20,"navigationItem");
    if (DAT_100adf408 != -1) {
      _swift_once(&DAT_100adf408,FUN_10052d760);
    }
    uVar1 = DAT_100b766f8;
    uVar4 = DAT_100b766f0;
    _swift_bridgeObjectRetain(DAT_100b766f8);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar4,uVar1);
    _swift_bridgeObjectRelease(uVar1);
    if (IVar5 == 0) {
      puVar11 = (undefined1 *)0x0;
    }
    else {
      puVar11 = &stack0xffffffffffffff90;
      FUN_100023444(puVar11,IVar5);
      lVar13 = *(long *)(IVar5 - 8);
      puVar12 = &stack0xffffffffffffff90 + -(*(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0);
      (**(code **)(lVar13 + 0x10))(puVar12,puVar11,IVar5);
      puVar11 = puVar12;
      __ss27_bridgeAnythingToObjectiveCyyXlxlF(puVar12,IVar5);
      (**(code **)(lVar13 + 8))(puVar12,IVar5);
      FUN_100023468(&stack0xffffffffffffff90);
    }
    IVar5 = 0;
    FUN_1007711fc();
    _swift_getObjCClassFromMetadata();
    _objc_allocWithZone();
    IVar5 = _objc_msgSend(IVar5,"initWithTitle:style:target:action:",uVar4,0,puVar11,
                          "editBarButtonTapped:");
    _swift_unknownObjectRelease(puVar11);
    _objc_msgSend(IVar3,"setRightBarButtonItem:",IVar5);
    return 0;
  }
  IVar5 = _objc_msgSend(unaff_x20,"navigationItem");
  IVar5 = _objc_msgSend(IVar5,"rightBarButtonItem");
  if (IVar5 == 0) {
    return 0;
  }
  lVar7 = *(long *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks);
  lVar13 = *(long *)(lVar7 + 0x10);
  if (lVar13 != 0) {
    if (*(long *)(lVar7 + 0x20) != 0) {
      uVar6 = 1;
      goto LAB_10029cca4;
    }
    if (lVar13 != 1) {
      lVar9 = 1;
      plVar8 = (long *)(lVar7 + 0x50);
      do {
        lVar7 = lVar9 + 1;
        if (SCARRY8(lVar9,1)) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x10029cd08);
          (*pcVar2)();
        }
        lVar10 = *plVar8;
        uVar6 = (ulong)(lVar10 != 0);
        lVar9 = lVar9 + 1;
        plVar8 = plVar8 + 6;
      } while (lVar10 == 0 && lVar7 != lVar13);
      goto LAB_10029cca4;
    }
  }
  uVar6 = 0;
LAB_10029cca4:
  _objc_msgSend(IVar5,"setEnabled:",uVar6);
  return 0;
}

// ==== 10029cd20 _TtC8Playback31SongMenuMIDIBanksViewController::viewWillAppear: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x14 bytes */

void _TtC8Playback31SongMenuMIDIBanksViewController::viewWillAppear_
               (ID param_1,SEL param_2,bool param_3)

{
  class_t *pcVar1;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  _objc_msgSendSuper2(&local_40,"viewWillAppear:",(ulong)param_3);
  FUN_10029ca64();
  return;
}

// ==== 10029cf2c _TtC8Playback31SongMenuMIDIBanksViewController::editBarButtonTapped: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback31SongMenuMIDIBanksViewController::editBarButtonTapped_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_10029cd88(param_3);
  return;
}

// ==== 10029d3d0 FUN_10029d3d0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x00010029d5dc) */
/* WARNING: Removing unreachable block (ram,0x00010029d5e8) */
/* WARNING: Removing unreachable block (ram,0x00010029d7dc) */
/* WARNING: Removing unreachable block (ram,0x00010029d620) */
/* WARNING: Removing unreachable block (ram,0x00010029d7f4) */
/* WARNING: Removing unreachable block (ram,0x00010029d6b4) */
/* WARNING: Removing unreachable block (ram,0x00010029d778) */
/* WARNING: Removing unreachable block (ram,0x00010029d784) */

void FUN_10029d3d0(undefined8 param_1,ID param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 *param_5)

{
  int iVar1;
  ID self;
  undefined *puVar2;
  ID IVar3;
  ID self_00;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined1 auStack_e8 [80];
  undefined8 local_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  
  self = _objc_msgSend(param_2,"navigationItem");
  iVar1 = 2;
  FUN_1008c26ac(2,0xd,0,0);
  puVar2 = &_OBJC_CLASS___UIActivityIndicatorView;
  _objc_allocWithZone();
  uVar6 = 2;
  if (iVar1 != 0) {
    uVar6 = 100;
  }
  IVar3 = _objc_msgSend((ID)puVar2,"initWithActivityIndicatorStyle:",uVar6);
  _objc_msgSend(IVar3,"startAnimating");
  self_00 = 0;
  FUN_1007711fc();
  _swift_getObjCClassFromMetadata();
  _objc_allocWithZone();
  IVar3 = _objc_msgSend(self_00,"initWithCustomView:",IVar3);
  _objc_msgSend(self,"setRightBarButtonItem:",IVar3);
  puVar2 = &DAT_100a3d3a0;
  _swift_allocObject(&DAT_100a3d3a0,0x28,7);
  *(ID *)(puVar2 + 0x10) = param_2;
  *(undefined8 *)(puVar2 + 0x18) = param_3;
  *(undefined8 *)(puVar2 + 0x20) = param_4;
  uVar6 = *(undefined8 *)(param_2 + _TtC8Playback31SongMenuMIDIBanksViewController::libraryID);
  uVar7 = *param_5;
  FUN_100027524(param_3,param_4);
  FUN_100712c3c(auStack_e8,uVar6,uVar7);
  puVar4 = &DAT_100a3d3c8;
  _swift_allocObject(&DAT_100a3d3c8,0x18,7);
  _swift_unknownObjectWeakInit(puVar4 + 0x10,param_2);
  uStack_78 = param_5[2];
  uStack_80 = param_5[1];
  uStack_88 = param_5[4];
  local_90 = param_5[3];
  local_98 = param_5[5];
  puVar5 = &DAT_100a3d3f0;
  _swift_allocObject(&DAT_100a3d3f0,0x68,7);
  *(undefined **)(puVar5 + 0x10) = puVar4;
  *(undefined8 *)(puVar5 + 0x18) = param_3;
  *(undefined8 *)(puVar5 + 0x20) = param_4;
  *(code **)(puVar5 + 0x28) = FUN_10029fe20;
  *(undefined **)(puVar5 + 0x30) = puVar2;
  uVar6 = *param_5;
  uVar8 = param_5[3];
  uVar7 = param_5[2];
  *(undefined8 *)(puVar5 + 0x40) = param_5[1];
  *(undefined8 *)(puVar5 + 0x38) = uVar6;
  *(undefined8 *)(puVar5 + 0x50) = uVar8;
  *(undefined8 *)(puVar5 + 0x48) = uVar7;
  uVar6 = param_5[4];
  *(undefined8 *)(puVar5 + 0x60) = param_5[5];
  *(undefined8 *)(puVar5 + 0x58) = uVar6;
  FUN_100027524(param_3,param_4);
  _swift_retain(puVar2);
  FUN_100088c38(&uStack_80);
  FUN_100088c38(&local_90);
  FUN_10029f6a0(&local_98);
  FUN_100052dec(FUN_10029fea4,puVar5);
  _swift_release(puVar5);
  _swift_release(puVar2);
  FUN_100222238(auStack_e8);
  return;
}

// ==== 10029dab0 FUN_10029dab0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_10029dab0(undefined8 param_1,long param_2,code *param_3,undefined8 param_4,code *param_5,
                  undefined8 param_6,undefined8 *param_7)

{
  long lVar1;
  code *pcVar2;
  uint uVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 *puVar6;
  ID IVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 auStack_b0 [3];
  undefined1 local_98 [8];
  undefined8 auStack_90 [2];
  undefined1 auStack_80 [8];
  undefined1 auStack_78 [24];
  
  lVar4 = 0;
  auStack_b0[1] = param_4;
  FUN_100494e20();
  lVar4 = -(*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar10 = (undefined8 *)((long)auStack_b0 + lVar4);
  puVar5 = &DAT_100af5e50;
  FUN_100021774();
  puVar11 = (undefined8 *)
            ((long)puVar10 - (*(long *)(*(long *)(puVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0))
  ;
  _swift_beginAccess(param_2 + 0x10,auStack_78,0,0);
  IVar7 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar7 == 0) {
    if (param_3 != (code *)0x0) {
      (*param_3)(0);
    }
  }
  else {
    FUN_10029ca64();
    FUN_1000bbd6c(param_1,puVar11);
    puVar6 = puVar11;
    _swift_getEnumCaseMultiPayload(puVar11,puVar5);
    if ((int)puVar6 == 1) {
      uVar8 = *puVar11;
      _swift_getErrorValue(uVar8,auStack_80,local_98);
      uVar9 = auStack_90[1];
      FUN_1002c33f8(auStack_90[0],auStack_90[1]);
      (*param_5)();
      _swift_bridgeObjectRelease(uVar9);
      _swift_errorRelease(uVar8);
    }
    else {
      FUN_10029feb8(puVar11,puVar10);
      uVar3 = (uint)*puVar10;
      FUN_1006d2390();
      if ((uVar3 & 0xff) == 1) {
        lVar4 = IVar7 + _TtC8Playback31SongMenuMIDIBanksViewController::midiBankSelectionDelegate;
        _swift_unknownObjectWeakLoadStrong();
        uVar9 = *param_7;
        if (lVar4 != 0) {
          FUN_100528f18(uVar9);
          _swift_unknownObjectRelease(lVar4);
        }
        lVar1 = _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks;
        lVar4 = IVar7 + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks;
        FUN_10029f6c8(lVar4,uVar9);
        if (*(long *)(*(long *)(IVar7 + lVar1) + 0x10) < lVar4) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x10029dcf8);
          (*pcVar2)();
        }
        FUN_1001d7704();
        IVar7 = _objc_msgSend(IVar7,"tableView");
        if (IVar7 == 0) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x10029dcfc);
          (*pcVar2)();
        }
        _objc_msgSend(IVar7,"reloadData");
        if (param_3 != (code *)0x0) {
          (*param_3)(1);
        }
      }
      else {
        if (param_3 != (code *)0x0) {
          (*param_3)(0);
        }
        (*param_5)(*(undefined8 *)((long)auStack_90 + lVar4),
                   *(undefined8 *)(auStack_80 + lVar4 + -8));
      }
      FUN_10029fefc(puVar10);
    }
  }
  return;
}

// ==== 10029dcfc _TtC8Playback31SongMenuMIDIBanksViewController::initWithStyle: ====
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::initWithStyle_
             (ID param_1,SEL param_2,long_long param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.SongMenuMIDIBanksViewController",0x28,"init(style:)",0xc,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x10029dd28);
  (*pcVar1)();
}

// ==== 10029dd28 _TtC8Playback31SongMenuMIDIBanksViewController::initWithNibName:bundle: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::initWithNibName_bundle_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.SongMenuMIDIBanksViewController",0x28,"init(nibName:bundle:)",0x15,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x10029dd5c);
  (*pcVar1)();
}

// ==== 10029dd5c _TtC8Playback31SongMenuMIDIBanksViewController::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback31SongMenuMIDIBanksViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + availableMIDIBanks));
  FUN_100026610(param_1 + midiBankSelectionDelegate);
  return;
}

// ==== 10029dda4 FUN_10029dda4 ====
void FUN_10029dda4(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback31SongMenuMIDIBanksViewController);
  return;
}

// ==== 10029ddc4 _TtC8Playback31SongMenuMIDIBanksViewController::numberOfSectionsInTableView: ====
/* Function Stack Size: 0x18 bytes */

long_long _TtC8Playback31SongMenuMIDIBanksViewController::numberOfSectionsInTableView_
                    (ID param_1,SEL param_2,ID param_3)

{
  return 2;
}

// ==== 10029ddcc _TtC8Playback31SongMenuMIDIBanksViewController::tableView:numberOfRowsInSection: ====
/* Function Stack Size: 0x20 bytes */

long_long _TtC8Playback31SongMenuMIDIBanksViewController::tableView_numberOfRowsInSection_
                    (ID param_1,SEL param_2,ID param_3,long_long param_4)

{
  FUN_10029f8e8();
  return param_4;
}

// ==== 10029ddf0 FUN_10029ddf0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10029ddf0(ID param_1)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  code *pcVar5;
  ulong uVar6;
  undefined8 uVar7;
  ID IVar8;
  undefined *puVar9;
  ID IVar10;
  ID IVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  long lVar14;
  long unaff_x20;
  ulong uVar15;
  
  IVar8 = param_1;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if (1 < IVar8) {
                    /* WARNING: Does not return */
    pcVar5 = (code *)SoftwareBreakpoint(1,0x10029e1e4);
    (*pcVar5)();
  }
  uVar15 = *(ulong *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks
                     );
  uVar6 = uVar15;
  _swift_bridgeObjectRetain();
  FUN_10029c3d0();
  _swift_bridgeObjectRelease();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (-1 < (long)uVar15) {
    if (uVar15 < *(ulong *)(uVar6 + 0x10)) {
      lVar14 = uVar6 + uVar15 * 0x30;
      lVar1 = *(long *)(lVar14 + 0x20);
      uVar12 = *(undefined8 *)(lVar14 + 0x28);
      lVar2 = *(long *)(lVar14 + 0x30);
      uVar3 = *(undefined8 *)(lVar14 + 0x38);
      uVar13 = *(undefined8 *)(lVar14 + 0x40);
      uVar4 = *(undefined8 *)(lVar14 + 0x48);
      FUN_10029ff38(lVar1,uVar12,lVar2,uVar3,uVar13);
      _swift_bridgeObjectRelease(uVar6);
      if (lVar2 == 0) {
        uVar12 = 0xd000000000000019;
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000019,0x80000001008d0540)
        ;
        uVar13 = uVar12;
        __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
        IVar8 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar12,
                              uVar13);
        IVar10 = _objc_msgSend(IVar8,"textLabel");
        if (IVar10 != 0) {
          if (DAT_100adf650 != -1) {
            _swift_once(&DAT_100adf650,FUN_10052e688);
          }
          uVar12 = DAT_100b76b88;
          uVar13 = DAT_100b76b80;
          _swift_bridgeObjectRetain(DAT_100b76b88);
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar13,uVar12);
          _swift_bridgeObjectRelease(uVar12);
          _objc_msgSend(IVar10,"setText:",uVar13);
        }
        _objc_msgSend(IVar8,"setAccessoryType:",1);
      }
      else {
        uVar7 = 0xd00000000000001a;
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001a,0x80000001008ea420)
        ;
        IVar8 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:",uVar7);
        if (IVar8 == 0) {
          puVar9 = &_OBJC_CLASS___UITableViewCell;
          _objc_allocWithZone();
          uVar7 = 0xd00000000000001a;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                    (0xd00000000000001a,0x80000001008ea420);
          IVar8 = _objc_msgSend((ID)puVar9,"initWithStyle:reuseIdentifier:",3,uVar7);
        }
        IVar10 = _objc_msgSend(IVar8,"textLabel");
        if (IVar10 != 0) {
          uVar7 = uVar12;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar12,lVar2);
          _objc_msgSend(IVar10,"setText:",uVar7);
        }
        uVar7 = 3;
        if (lVar1 != *(long *)(unaff_x20 +
                              _TtC8Playback31SongMenuMIDIBanksViewController::selectedMIDIBankID)) {
          uVar7 = 0;
        }
        _objc_msgSend(IVar8,"setAccessoryType:",uVar7);
        _objc_msgSend(IVar8,"setEditingAccessoryType:",1);
        IVar10 = _objc_msgSend(IVar8,"detailTextLabel");
        if (IVar10 != 0) {
          uVar7 = uVar3;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar3,uVar13);
          _objc_msgSend(IVar10,"setText:",uVar7);
        }
        IVar10 = _objc_msgSend(IVar8,"detailTextLabel");
        if (IVar10 == 0) {
          FUN_10029ff74(lVar1,uVar12,lVar2,uVar3,uVar13,uVar4);
        }
        else {
          puVar9 = &_OBJC_CLASS___UIColor;
          _swift_getInitializedObjCClass();
          IVar11 = _objc_msgSend((ID)puVar9,"systemGrayColor");
          _objc_msgSend(IVar10,"setTextColor:",IVar11);
          FUN_10029ff74(lVar1,uVar12,lVar2,uVar3,uVar13,uVar4);
        }
      }
      return IVar8;
    }
                    /* WARNING: Does not return */
    pcVar5 = (code *)SoftwareBreakpoint(1,0x10029e1ec);
    (*pcVar5)();
  }
                    /* WARNING: Does not return */
  pcVar5 = (code *)SoftwareBreakpoint(1,0x10029e1e8);
  (*pcVar5)();
}

// ==== 10029e204 _TtC8Playback31SongMenuMIDIBanksViewController::tableView:cellForRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::tableView_cellForRowAtIndexPath_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined1 *puVar2;
  long lVar3;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar3 = *(long *)(lVar1 + -8);
  puVar2 = &stack0xffffffffffffffc0 + -(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar2,param_4);
  FUN_10029ddf0(param_3,puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return param_3;
}

// ==== 10029e2bc _TtC8Playback31SongMenuMIDIBanksViewController::tableView:titleForFooterInSection: ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::tableView_titleForFooterInSection_
             (ID param_1,SEL param_2,ID param_3,long_long param_4)

{
  FUN_10029f92c();
  if (param_2 == (SEL)0x0) {
    param_4 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease(param_2);
  }
  return param_4;
}

// ==== 10029e300 FUN_10029e300 ====
void FUN_10029e300(undefined8 param_1,ID param_2,undefined8 param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ID IVar5;
  long lVar6;
  undefined8 uVar7;
  code *UNRECOVERED_JUMPTABLE;
  long lVar8;
  long unaff_x20;
  long lVar9;
  
  IVar5 = param_2;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if (IVar5 < 2) {
    lVar9 = *(long *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks
                     );
    lVar6 = lVar9;
    _swift_bridgeObjectRetain();
    FUN_10029c3d0();
    _swift_bridgeObjectRelease();
    __s10Foundation9IndexPathV5UIKitE3rowSivg();
    if ((-1 < lVar9) && (lVar9 < *(long *)(lVar6 + 0x10))) {
      lVar8 = lVar6 + lVar9 * 0x30;
      uVar7 = *(undefined8 *)(lVar8 + 0x20);
      uVar2 = *(undefined8 *)(lVar8 + 0x28);
      lVar9 = *(long *)(lVar8 + 0x30);
      uVar3 = *(undefined8 *)(lVar8 + 0x38);
      uVar1 = *(undefined8 *)(lVar8 + 0x40);
      uVar4 = *(undefined8 *)(lVar8 + 0x48);
      FUN_10029ff38(uVar7,uVar2,lVar9,uVar3,uVar1,uVar4);
      _swift_bridgeObjectRelease(lVar6);
      IVar5 = _objc_msgSend(param_2,"isEditing");
      if (lVar9 == 0) {
        if ((int)IVar5 != 0) goto LAB_10029e3f8;
      }
      else {
        FUN_10029ff74(uVar7,uVar2,lVar9,uVar3,uVar1,uVar4);
      }
      lVar6 = 0;
      __s10Foundation9IndexPathVMa();
      lVar9 = *(long *)(lVar6 + -8);
      (**(code **)(lVar9 + 0x10))(param_1,param_3,lVar6);
      UNRECOVERED_JUMPTABLE = *(code **)(lVar9 + 0x38);
      uVar7 = 0;
      goto LAB_10029e418;
    }
    _swift_bridgeObjectRelease(lVar6);
  }
LAB_10029e3f8:
  lVar6 = 0;
  __s10Foundation9IndexPathVMa();
  UNRECOVERED_JUMPTABLE = *(code **)(*(long *)(lVar6 + -8) + 0x38);
  uVar7 = 1;
LAB_10029e418:
                    /* WARNING: Could not recover jumptable at 0x00010029e430. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar7,1,lVar6);
  return;
}

// ==== 10029e474 _TtC8Playback31SongMenuMIDIBanksViewController::tableView:willSelectRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::tableView_willSelectRowAtIndexPath_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  ID IVar4;
  long lVar5;
  code *pcVar6;
  undefined1 *puVar7;
  long lVar8;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar8 = *(long *)(lVar1 + -8);
  puVar7 = &stack0xffffffffffffffb0 + -(*(long *)(lVar8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar2 = &DAT_100af57b0;
  FUN_100021774();
  lVar5 = (long)puVar7 - (*(long *)(*(long *)(puVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar7,param_4);
  FUN_10029e300(lVar5,param_3,puVar7);
  pcVar6 = *(code **)(lVar8 + 8);
  (*pcVar6)(puVar7,lVar1);
  lVar3 = lVar5;
  (**(code **)(lVar8 + 0x30))(lVar5,1,lVar1);
  IVar4 = 0;
  if ((int)lVar3 != 1) {
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    (*pcVar6)(lVar5,lVar1);
  }
  return IVar4;
}

// ==== 10029e598 FUN_10029e598 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10029e598(ID param_1)

{
  long *plVar1;
  undefined8 *puVar2;
  undefined1 *puVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ID IVar8;
  class_t *pcVar9;
  long lVar10;
  ID IVar11;
  class_t *pcVar12;
  long lVar13;
  long lVar14;
  undefined8 uVar15;
  ID unaff_x20;
  long lVar16;
  ulong uVar17;
  long lVar18;
  objc_super local_80;
  objc_super local_70;
  
  IVar8 = param_1;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if (IVar8 < 2) {
    uVar17 = *(ulong *)(unaff_x20 +
                       _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks);
    uVar7 = uVar17;
    _swift_bridgeObjectRetain();
    FUN_10029c3d0();
    _swift_bridgeObjectRelease();
    __s10Foundation9IndexPathV5UIKitE3rowSivg();
    if (((long)uVar17 < 0) || (*(long *)(uVar7 + 0x10) <= (long)uVar17)) {
      _swift_bridgeObjectRelease(uVar7);
      return uVar7;
    }
    lVar14 = uVar7 + uVar17 * 0x30;
    lVar16 = *(long *)(lVar14 + 0x20);
    lVar5 = *(long *)(lVar14 + 0x28);
    lVar13 = *(long *)(lVar14 + 0x30);
    lVar6 = *(long *)(lVar14 + 0x38);
    lVar4 = *(long *)(lVar14 + 0x40);
    lVar14 = *(long *)(lVar14 + 0x48);
    FUN_10029ff38(lVar16,lVar5,lVar13,lVar6,lVar4,lVar14);
    _swift_bridgeObjectRelease(uVar7);
    IVar8 = _objc_msgSend(param_1,"isEditing");
    if (lVar13 == 0) {
      if ((IVar8 & 1) != 0) {
        return IVar8;
      }
      lVar16 = *(long *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::song);
      if (lVar16 == 0) {
        return IVar8;
      }
      uVar15 = *(undefined8 *)
                (unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::libraryID);
      pcVar9 = (class_t *)0x0;
      FUN_1007a0e0c();
      pcVar12 = pcVar9;
      _objc_allocWithZone();
      lVar13 = (long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::delegate;
      *(undefined8 *)(lVar13 + 8) = 0;
      _swift_unknownObjectWeakInit(lVar13,0);
      puVar2 = (undefined8 *)
               ((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::mode);
      puVar2[3] = 0;
      puVar2[2] = 0;
      puVar2[5] = 0;
      puVar2[4] = 0;
      puVar2[1] = 0;
      *puVar2 = 0;
      *(long *)((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::song) =
           lVar16;
      *(undefined8 *)
       ((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID) = uVar15
      ;
      *(undefined ***)(lVar13 + 8) = &PTR_PTR_100a3d230;
      _swift_unknownObjectWeakAssign();
      puVar2 = (undefined8 *)
               ((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName)
      ;
      *puVar2 = 0;
      puVar2[1] = 0xe000000000000000;
      puVar2 = (undefined8 *)
               ((long)&pcVar12->isa +
               _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription);
      *puVar2 = 0;
      puVar2[1] = 0xe000000000000000;
      local_80.receiver = (ID)pcVar12;
      local_80.super_class = pcVar9;
      IVar8 = _objc_msgSendSuper2(&local_80,"initWithStyle:",1);
      IVar11 = _objc_msgSend(unaff_x20,"navigationController");
    }
    else {
      if ((IVar8 & 1) == 0) {
        IVar8 = unaff_x20 +
                _TtC8Playback31SongMenuMIDIBanksViewController::midiBankSelectionDelegate;
        _swift_unknownObjectWeakLoadStrong();
        if (IVar8 != 0) {
          *(long *)(IVar8 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID
                   ) = lVar16;
          IVar11 = _objc_msgSend(IVar8,"tableView");
          _objc_msgSend(IVar11,"reloadData");
          IVar11 = IVar8 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::
                           midiOutUpdateDelegate;
          _swift_unknownObjectWeakLoadStrong();
          if (IVar11 != 0) {
            puVar3 = (undefined1 *)
                     (IVar11 + _TtC8Playback26SongMenuItemViewController::midiBankUpdate);
            *puVar3 = 1;
            *(long *)(puVar3 + 8) = lVar16;
            puVar3[0x10] = 0;
            _swift_unknownObjectRelease(IVar8);
            IVar8 = IVar11;
          }
          _swift_unknownObjectRelease(IVar8);
        }
        _swift_bridgeObjectRelease(lVar4);
        _swift_bridgeObjectRelease(lVar13);
        _swift_bridgeObjectRelease(lVar14);
        *(long *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::selectedMIDIBankID) =
             lVar16;
        _objc_msgSend(param_1,"reloadData");
        IVar8 = _objc_msgSend(unaff_x20,"navigationController");
        if (IVar8 != 0) {
          _objc_msgSend(IVar8,"popViewControllerAnimated:",1);
          return 0;
        }
        return 0;
      }
      lVar18 = *(long *)(unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::song);
      if ((lVar18 == 0) || (lVar16 == 0)) {
        _swift_bridgeObjectRelease(lVar4);
        _swift_bridgeObjectRelease(lVar13);
        _swift_bridgeObjectRelease(lVar14);
        __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
        _objc_msgSend(param_1,"deselectRowAtIndexPath:animated:",lVar14,0);
        return 0;
      }
      uVar15 = *(undefined8 *)
                (unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::libraryID);
      pcVar9 = (class_t *)0x0;
      FUN_1007a0e0c();
      pcVar12 = pcVar9;
      _objc_allocWithZone();
      lVar10 = (long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::delegate;
      *(undefined8 *)(lVar10 + 8) = 0;
      _swift_unknownObjectWeakInit(lVar10,0);
      plVar1 = (long *)((long)&pcVar12->isa +
                       _TtC8Playback34SongMenuMIDIBankEditViewController::mode);
      *plVar1 = lVar16;
      plVar1[1] = lVar5;
      plVar1[2] = lVar13;
      plVar1[3] = lVar6;
      plVar1[4] = lVar4;
      plVar1[5] = lVar14;
      *(long *)((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::song) =
           lVar18;
      *(undefined8 *)
       ((long)&pcVar12->isa + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID) = uVar15
      ;
      *(undefined ***)(lVar10 + 8) = &PTR_PTR_100a3d230;
      _swift_unknownObjectWeakAssign();
      plVar1 = (long *)((long)&pcVar12->isa +
                       _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName);
      *plVar1 = lVar5;
      plVar1[1] = lVar13;
      plVar1 = (long *)((long)&pcVar12->isa +
                       _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription);
      *plVar1 = lVar6;
      plVar1[1] = lVar4;
      local_70.receiver = (ID)pcVar12;
      local_70.super_class = pcVar9;
      _swift_bridgeObjectRetain(lVar13);
      _swift_bridgeObjectRetain(lVar4);
      IVar8 = _objc_msgSendSuper2(&local_70,"initWithStyle:",1);
      IVar11 = _objc_msgSend(unaff_x20,"navigationController");
    }
    if (IVar11 != 0) {
      _objc_msgSend(IVar11,"pushViewController:animated:",IVar8,1);
    }
    IVar8 = 0;
  }
  return IVar8;
}

// ==== 10029ea5c _TtC8Playback31SongMenuMIDIBanksViewController::tableView:didSelectRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void _TtC8Playback31SongMenuMIDIBanksViewController::tableView_didSelectRowAtIndexPath_
               (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined1 *puVar2;
  long lVar3;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar3 = *(long *)(lVar1 + -8);
  puVar2 = &stack0xffffffffffffffc0 + -(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar2,param_4);
  FUN_10029e598(param_3,puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return;
}

// ==== 10029eb0c FUN_10029eb0c ====
ID FUN_10029eb0c(ID param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  byte bVar6;
  ID IVar7;
  long lVar8;
  long lVar9;
  long unaff_x20;
  long lVar10;
  
  IVar7 = _objc_msgSend(param_1,"isEditing");
  if ((int)IVar7 != 0) {
    __s10Foundation9IndexPathV5UIKitE7sectionSivg();
    if (IVar7 < 2) {
      bVar6 = (&DAT_100ae8c50)[IVar7];
      lVar10 = *(long *)(unaff_x20 +
                        _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks);
      lVar8 = lVar10;
      _swift_bridgeObjectRetain();
      FUN_10029c3d0();
      _swift_bridgeObjectRelease();
      __s10Foundation9IndexPathV5UIKitE3rowSivg();
      if ((-1 < lVar10) && (lVar10 < *(long *)(lVar8 + 0x10))) {
        lVar9 = lVar8 + lVar10 * 0x30;
        lVar10 = *(long *)(lVar9 + 0x20);
        uVar3 = *(undefined8 *)(lVar9 + 0x28);
        lVar1 = *(long *)(lVar9 + 0x30);
        uVar4 = *(undefined8 *)(lVar9 + 0x38);
        uVar2 = *(undefined8 *)(lVar9 + 0x40);
        uVar5 = *(undefined8 *)(lVar9 + 0x48);
        FUN_10029ff38(lVar10,uVar3,lVar1,uVar4,uVar2,uVar5);
        _swift_bridgeObjectRelease(lVar8);
        if (lVar1 == 0) {
          return (ulong)bVar6;
        }
        FUN_10029ff74(lVar10,uVar3,lVar1,uVar4,uVar2,uVar5);
        return (ulong)(lVar10 != 0);
      }
      _swift_bridgeObjectRelease(lVar8);
    }
    IVar7 = 0;
  }
  return IVar7;
}

// ==== 10029ec28 _TtC8Playback31SongMenuMIDIBanksViewController::tableView:canEditRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

bool _TtC8Playback31SongMenuMIDIBanksViewController::tableView_canEditRowAtIndexPath_
               (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined1 *puVar2;
  long lVar3;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar3 = *(long *)(lVar1 + -8);
  puVar2 = &stack0xffffffffffffffc0 + -(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar2,param_4);
  FUN_10029eb0c(param_3,puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return (uint)param_3 & 1;
}

// ==== 10029ece0 _TtC8Playback31SongMenuMIDIBanksViewController::tableView:trailingSwipeActionsConfigurationForRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback31SongMenuMIDIBanksViewController::
   tableView_trailingSwipeActionsConfigurationForRowAtIndexPath_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  long lVar4;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar4 = *(long *)(lVar1 + -8);
  puVar3 = &stack0xffffffffffffffc0 + -(*(long *)(lVar4 + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar3,param_4);
  puVar2 = puVar3;
  FUN_10029f9f8();
  (**(code **)(lVar4 + 8))(puVar3,lVar1);
  return (ID)puVar2;
}

// ==== 10029ed94 FUN_10029ed94 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10029ed94(ID param_1,long *param_2)

{
  long lVar1;
  code *pcVar2;
  long lVar3;
  ID IVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined *puVar8;
  undefined **ppuVar9;
  long lVar10;
  ulong uVar11;
  long *plVar12;
  ID unaff_x20;
  ulong uVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_170 [8];
  undefined8 local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  undefined *local_130;
  undefined1 auStack_128 [8];
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  long local_c8;
  long local_c0;
  long lStack_b8;
  long lStack_b0;
  long lStack_a8;
  long local_98;
  long lStack_90;
  long local_88;
  long lStack_80;
  long local_78;
  long lStack_70;
  
  lVar15 = *param_2;
  local_140 = param_2[2];
  local_148 = param_2[4];
  local_138 = param_2[5];
  local_158 = param_2[1];
  local_150 = param_2[3];
  lVar3 = 0;
  __s10Foundation8IndexSetVMa();
  lVar14 = *(long *)(lVar3 + -8);
  lVar10 = *(long *)(lVar14 + 0x40);
  IVar4 = _objc_msgSend(param_1,"navigationController");
  if (IVar4 != 0) {
    _objc_msgSend(IVar4,"popViewControllerAnimated:",1);
  }
  lVar1 = _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks;
  uVar11 = *(ulong *)(*(long *)(unaff_x20 +
                               _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks) +
                     0x10);
  if (uVar11 != 0) {
    uVar13 = 0;
    plVar12 = (long *)(*(long *)(unaff_x20 +
                                _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks)
                      + 0x20);
    do {
      if (*plVar12 == lVar15) {
        puVar5 = &DAT_100afe9a0;
        FUN_100021774();
        _swift_initStaticObject();
        local_160 = lVar14;
        _swift_retain();
        uVar6 = 1;
        puVar8 = puVar5;
        thunk_FUN_100284370();
        local_168 = uVar6;
        _swift_release(puVar5);
        lStack_70 = local_138;
        if (((ulong)puVar8 & 1) != 0) {
          return;
        }
        lStack_a8 = param_2[2];
        lStack_b0 = param_2[1];
        lStack_b8 = param_2[4];
        local_c0 = param_2[3];
        local_c8 = local_138;
        FUN_100034050(auStack_128,uVar13);
        uStack_d8 = uStack_118;
        local_e0 = local_120;
        FUN_1000a26a4(&local_e0);
        uStack_e8 = uStack_108;
        local_f0 = local_110;
        FUN_1000a26a4(&local_f0);
        local_f8 = local_100;
        FUN_1001d7e54(&local_f8);
        if (uVar13 <= *(ulong *)(*(long *)(unaff_x20 + lVar1) + 0x10)) {
          lStack_90 = local_158;
          local_88 = local_140;
          lStack_80 = local_150;
          local_78 = local_148;
          local_98 = lVar15;
          FUN_100088c38(&lStack_b0);
          FUN_100088c38(&local_c0);
          FUN_10029f6a0(&local_c8);
          FUN_1001d1d08(uVar13,uVar13,&local_98);
          IVar4 = _objc_msgSend(unaff_x20,"tableView");
          if (IVar4 != 0) {
            puVar5 = &DAT_100af5398;
            FUN_100021774();
            _swift_allocObject();
            *(undefined8 *)(puVar5 + 0x18) = 2;
            *(undefined8 *)(puVar5 + 0x10) = 1;
            *(undefined8 *)(puVar5 + 0x20) = local_168;
            puVar7 = &DAT_100af7190;
            local_130 = puVar5;
            FUN_100023140(&DAT_100af7190,PTR___s10Foundation8IndexSetVMa_100a1e290,
                          PTR___s10Foundation8IndexSetVs0C7AlgebraAAMc_100a1e2a0);
            puVar5 = &DAT_100af8df8;
            FUN_100021774(&DAT_100af8df8);
            puVar8 = &DAT_100afc4e0;
            FUN_1000f634c(&DAT_100afc4e0,&DAT_100af8e08,PTR___sSiN_100a1dd88,
                          PTR___sSayxGSTsMc_100a1dd30);
            ppuVar9 = &local_130;
            __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                      (auStack_170 + -(lVar10 + 0xfU & 0xfffffffffffffff0),ppuVar9,puVar5,puVar8,
                       lVar3,puVar7);
            __s10Foundation8IndexSetV19_bridgeToObjectiveCSo07NSIndexC0CyF();
            (**(code **)(local_160 + 8))(auStack_170 + -(lVar10 + 0xfU & 0xfffffffffffffff0),lVar3);
            _objc_msgSend(IVar4,"reloadSections:withRowAnimation:",ppuVar9,100);
            return;
          }
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x10029f0f4);
          (*pcVar2)();
        }
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x10029f0f0);
        (*pcVar2)();
      }
      uVar13 = uVar13 + 1;
      plVar12 = plVar12 + 6;
    } while (uVar11 != uVar13);
  }
  return;
}

// ==== 10029f0f4 FUN_10029f0f4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_10029f0f4(ID param_1,undefined8 *param_2)

{
  long lVar1;
  long lVar2;
  ID self;
  long lVar3;
  undefined *puVar4;
  void *aBlock;
  undefined8 *puVar5;
  undefined8 *puVar6;
  ulong uVar7;
  long unaff_x20;
  undefined1 *puVar8;
  long lVar9;
  long lVar10;
  code *pcVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined1 auStack_e0 [8];
  long local_d8;
  long local_d0;
  long lStack_c8;
  long local_c0;
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  code *local_98;
  undefined *local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  lVar1 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  local_c0 = *(long *)(lVar1 + -8);
  puVar8 = auStack_e0 + -(*(long *)(local_c0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  local_d8 = lVar1;
  __s8Dispatch0A3QoSVMa();
  local_d0 = *(long *)(lVar2 + -8);
  lVar9 = (long)puVar8 - (*(long *)(local_d0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar1 = 0;
  lStack_c8 = lVar2;
  __s8Dispatch0A4TimeVMa();
  lVar10 = *(long *)(lVar1 + -8);
  uVar7 = *(long *)(lVar10 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar2 = lVar9 - uVar7;
  lVar12 = lVar2 - uVar7;
  self = _objc_msgSend(param_1,"navigationController");
  if (self != 0) {
    _objc_msgSend(self,"popViewControllerAnimated:",1);
  }
  lVar3 = unaff_x20 + _TtC8Playback31SongMenuMIDIBanksViewController::midiBankSelectionDelegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    FUN_1005291dc(param_2);
    _swift_unknownObjectRelease(lVar3);
  }
  FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  __s8Dispatch0A4TimeV3nowACyFZ(lVar2);
  __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar12,0x3fc999999999999a,lVar2);
  pcVar11 = *(code **)(lVar10 + 8);
  (*pcVar11)(lVar2,lVar1);
  uStack_68 = param_2[2];
  uStack_70 = param_2[1];
  uStack_78 = param_2[4];
  local_80 = param_2[3];
  local_88 = param_2[5];
  puVar4 = &DAT_100a3d260;
  _swift_allocObject(&DAT_100a3d260,0x48,7);
  uVar13 = *param_2;
  uVar15 = param_2[3];
  uVar14 = param_2[2];
  *(undefined8 *)(puVar4 + 0x20) = param_2[1];
  *(undefined8 *)(puVar4 + 0x18) = uVar13;
  *(long *)(puVar4 + 0x10) = unaff_x20;
  *(undefined8 *)(puVar4 + 0x30) = uVar15;
  *(undefined8 *)(puVar4 + 0x28) = uVar14;
  uVar13 = param_2[4];
  *(undefined8 *)(puVar4 + 0x40) = param_2[5];
  *(undefined8 *)(puVar4 + 0x38) = uVar13;
  local_98 = FUN_10029fca8;
  local_b8 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_b0 = 0x42000000;
  local_a8 = FUN_10056b3d8;
  puStack_a0 = &DAT_100a3d278;
  local_90 = puVar4;
  aBlock = __Block_copy(&local_b8);
  puVar4 = local_90;
  FUN_100088c38(&uStack_70);
  FUN_100088c38(&local_80);
  FUN_10029f6a0(&local_88);
  _swift_release(puVar4);
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar9);
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar5 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar4);
  puVar4 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar6 = &DAT_100af52b8;
  FUN_100023140(&DAT_100af52b8,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
  lVar2 = local_d8;
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (puVar8,&local_b8,puVar4,puVar6,local_d8,puVar5);
  __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (lVar12,lVar9,puVar8,aBlock);
  __Block_release(aBlock);
  (**(code **)(local_c0 + 8))(puVar8,lVar2);
  (**(code **)(local_d0 + 8))(lVar9,lStack_c8);
  (*pcVar11)(lVar12,lVar1);
  return;
}

// ==== 10029f418 FUN_10029f418 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_10029f418(ID param_1,undefined8 *param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  ID self;
  undefined8 *puVar6;
  undefined *puVar7;
  undefined **ppuVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined *local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  lVar2 = 0;
  __s10Foundation8IndexSetVMa();
  lVar1 = _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks;
  lVar13 = *(long *)(lVar2 + -8);
  lVar11 = (long)&local_90 - (*(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0);
  uStack_68 = param_2[2];
  uStack_70 = param_2[1];
  uStack_78 = param_2[4];
  local_80 = param_2[3];
  local_88 = param_2[5];
  uVar12 = *(ulong *)(param_1 + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks);
  FUN_100088c38(&uStack_70);
  FUN_100088c38(&local_80);
  FUN_10029f6a0(&local_88);
  uVar3 = uVar12;
  _swift_isUniquelyReferenced_nonNull_native();
  *(ulong *)(param_1 + lVar1) = uVar12;
  uVar9 = uVar12;
  if ((uVar3 & 1) == 0) {
    uVar9 = 0;
    FUN_1007915f8(0,*(long *)(uVar12 + 0x10) + 1,1,uVar12);
    *(ulong *)(param_1 + lVar1) = uVar9;
  }
  uVar3 = *(ulong *)(uVar9 + 0x10);
  uVar12 = uVar9;
  if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar3) {
    uVar12 = (ulong)(1 < *(ulong *)(uVar9 + 0x18));
    FUN_1007915f8(uVar12,uVar3 + 1,1,uVar9);
  }
  *(ulong *)(uVar12 + 0x10) = uVar3 + 1;
  lVar10 = uVar12 + uVar3 * 0x30;
  uVar14 = param_2[1];
  uVar5 = *param_2;
  uVar15 = param_2[2];
  uVar17 = param_2[5];
  uVar16 = param_2[4];
  *(undefined8 *)(lVar10 + 0x38) = param_2[3];
  *(undefined8 *)(lVar10 + 0x30) = uVar15;
  *(undefined8 *)(lVar10 + 0x48) = uVar17;
  *(undefined8 *)(lVar10 + 0x40) = uVar16;
  *(undefined8 *)(lVar10 + 0x28) = uVar14;
  *(undefined8 *)(lVar10 + 0x20) = uVar5;
  *(ulong *)(param_1 + lVar1) = uVar12;
  puVar4 = &DAT_100afe9a0;
  FUN_100021774();
  _swift_initStaticObject();
  _swift_retain();
  uVar5 = 1;
  puVar7 = puVar4;
  thunk_FUN_100284370();
  _swift_release(puVar4);
  self = _objc_msgSend(param_1,"tableView");
  if (((ulong)puVar7 & 1) == 0) {
    if (self != 0) {
      puVar4 = &DAT_100af5398;
      FUN_100021774();
      _swift_allocObject();
      *(undefined8 *)(puVar4 + 0x18) = 2;
      *(undefined8 *)(puVar4 + 0x10) = 1;
      *(undefined8 *)(puVar4 + 0x20) = uVar5;
      puVar6 = &DAT_100af7190;
      local_90 = puVar4;
      FUN_100023140(&DAT_100af7190,PTR___s10Foundation8IndexSetVMa_100a1e290,
                    PTR___s10Foundation8IndexSetVs0C7AlgebraAAMc_100a1e2a0);
      puVar4 = &DAT_100af8df8;
      FUN_100021774(&DAT_100af8df8);
      puVar7 = &DAT_100afc4e0;
      FUN_1000f634c(&DAT_100afc4e0,&DAT_100af8e08,PTR___sSiN_100a1dd88,PTR___sSayxGSTsMc_100a1dd30);
      ppuVar8 = &local_90;
      __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                (lVar11,ppuVar8,puVar4,puVar7,lVar2,puVar6);
      __s10Foundation8IndexSetV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      (**(code **)(lVar13 + 8))(lVar11,lVar2);
      _objc_msgSend(self,"reloadSections:withRowAnimation:",ppuVar8,100);
    }
  }
  else {
    _objc_msgSend(self,"reloadData");
  }
  return 0;
}

// ==== 10029f8e8 FUN_10029f8e8 ====
undefined8 FUN_10029f8e8(ulong param_1)

{
  long unaff_x20;
  
  if (1 < param_1) {
    return 0;
  }
  if ((&DAT_100ae8b60)[param_1] == '\x01') {
    return *(undefined8 *)
            (*(long *)(unaff_x20 +
                      _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks) + 0x10);
  }
  return 1;
}

// ==== 10029f9f8 FUN_10029f9f8 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10029f9f8(ulong param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  void *aBlock;
  undefined *puVar8;
  ID IVar9;
  undefined8 uVar10;
  undefined *puVar11;
  long lVar12;
  long unaff_x20;
  long lVar13;
  undefined *local_90;
  undefined8 local_88;
  code *local_80;
  undefined *puStack_78;
  code *local_70;
  undefined *local_68;
  
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if ((param_1 < 2) && ((&DAT_100ae8c80)[param_1] == '\x01')) {
    lVar13 = *(long *)(unaff_x20 +
                      _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks);
    lVar12 = lVar13;
    _swift_bridgeObjectRetain();
    __s10Foundation9IndexPathV5UIKitE3rowSivg();
    if ((-1 < lVar12) && (lVar12 < *(long *)(lVar13 + 0x10))) {
      lVar12 = lVar13 + lVar12 * 0x30;
      uVar10 = *(undefined8 *)(lVar12 + 0x20);
      uVar3 = *(undefined8 *)(lVar12 + 0x28);
      uVar1 = *(undefined8 *)(lVar12 + 0x30);
      uVar4 = *(undefined8 *)(lVar12 + 0x38);
      uVar2 = *(undefined8 *)(lVar12 + 0x40);
      uVar5 = *(undefined8 *)(lVar12 + 0x48);
      _swift_bridgeObjectRetain(uVar5);
      _swift_bridgeObjectRetain(uVar1);
      _swift_bridgeObjectRetain(uVar2);
      _swift_bridgeObjectRelease(lVar13);
      if (DAT_100adf7f0 != -1) {
        _swift_once(&DAT_100adf7f0,FUN_10052f4d8);
      }
      uVar6 = DAT_100b76ec8;
      uVar7 = DAT_100b76ec0;
      puVar8 = &DAT_100a3d2b0;
      _swift_allocObject(&DAT_100a3d2b0,0x48,7);
      *(long *)(puVar8 + 0x10) = unaff_x20;
      *(undefined8 *)(puVar8 + 0x18) = uVar10;
      *(undefined8 *)(puVar8 + 0x20) = uVar3;
      *(undefined8 *)(puVar8 + 0x28) = uVar1;
      *(undefined8 *)(puVar8 + 0x30) = uVar4;
      *(undefined8 *)(puVar8 + 0x38) = uVar2;
      *(undefined8 *)(puVar8 + 0x40) = uVar5;
      _swift_bridgeObjectRetain(uVar6);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar6);
      _swift_bridgeObjectRelease(uVar6);
      local_70 = FUN_10029fd08;
      local_90 = PTR___NSConcreteStackBlock_100a1d8e8;
      local_88 = 0x42000000;
      local_80 = FUN_10081e344;
      puStack_78 = &DAT_100a3d2c8;
      local_68 = puVar8;
      aBlock = __Block_copy(&local_90);
      puVar8 = &_OBJC_CLASS___UIContextualAction;
      _swift_getInitializedObjCClass();
      IVar9 = _objc_msgSend((ID)puVar8,"contextualActionWithStyle:title:handler:",1,uVar7,aBlock);
      __Block_release(aBlock);
      puVar8 = local_68;
      _swift_release();
      FUN_10078d28c();
      _swift_allocObject();
      *(undefined8 *)(puVar8 + 0x18) = 3;
      *(undefined8 *)(puVar8 + 0x10) = 1;
      *(ID *)(puVar8 + 0x20) = IVar9;
      uVar10 = 0;
      FUN_100023404(0,&DAT_100afe9a8,&PTR__OBJC_CLASS___UIContextualAction_100aa4130);
      puVar11 = puVar8;
      __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar8,uVar10);
      _swift_bridgeObjectRelease(puVar8);
      puVar8 = &_OBJC_CLASS___UISwipeActionsConfiguration;
      _swift_getInitializedObjCClass();
      IVar9 = _objc_msgSend((ID)puVar8,"configurationWithActions:",puVar11);
      _objc_msgSend(IVar9,"setPerformsFirstActionWithFullSwipe:",0);
      return IVar9;
    }
    _swift_bridgeObjectRelease(lVar13);
  }
  return 0;
}

// ==== 1002ac524 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + markerContainerView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac544 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setMarkerContainerView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setMarkerContainerView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + markerContainerView,param_3);
  return;
}

// ==== 1002ac558 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + titleLabel;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac578 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setTitleLabel: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setTitleLabel_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + titleLabel,param_3);
  return;
}

// ==== 1002ac58c _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + titleEditButton;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac5ac _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setTitleEditButton: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setTitleEditButton_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + titleEditButton,param_3);
  return;
}

// ==== 1002ac5c0 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + destinationButton;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac5e0 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setDestinationButton: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setDestinationButton_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + destinationButton,param_3);
  return;
}

// ==== 1002ac5f4 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + channelButton;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac614 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setChannelButton: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setChannelButton_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + channelButton,param_3);
  return;
}

// ==== 1002ac628 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + channelArrowImageView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac648 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setChannelArrowImageView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setChannelArrowImageView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + channelArrowImageView,param_3);
  return;
}

// ==== 1002ac65c _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + enabledSwitch;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1002ac67c _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setEnabledSwitch: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::setEnabledSwitch_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + enabledSwitch,param_3);
  return;
}

// ==== 1002ac690 FUN_1002ac690 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1002ac690(void)

{
  undefined *self;
  ID IVar1;
  ID IVar2;
  ID unaff_x20;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"awakeFromNib");
  self = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar1 = _objc_msgSend((ID)self,"clearColor");
  _objc_msgSend(unaff_x20,"setBackgroundColor:",IVar1);
  IVar1 = _objc_msgSend(unaff_x20,"contentView");
  IVar2 = _objc_msgSend((ID)self,"clearColor");
  _objc_msgSend(IVar1,"setBackgroundColor:",IVar2);
  IVar1 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar1 != 0) {
    _objc_msgSend(IVar1,"setHidden:",1);
  }
  return;
}

// ==== 1002ac7a4 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::awakeFromNib ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::awakeFromNib(ID param_1,SEL param_2)

{
  FUN_1002ac690(param_1);
  return;
}

// ==== 1002ac7cc FUN_1002ac7cc ====
void FUN_1002ac7cc(void)

{
  long lVar1;
  long lVar2;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_78 [32];
  undefined1 auStack_58 [24];
  
  lVar1 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  lVar2 = lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    lVar3 = *(long *)(lVar1 + 8);
    _swift_getObjectType();
    lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
    _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                       auStack_58,0,0);
    FUN_10018ed24(unaff_x20 + lVar1,auStack_78);
    (**(code **)(lVar3 + 0x18))();
    _swift_unknownObjectRelease(lVar2);
    FUN_10003d930(auStack_78);
  }
  return;
}

// ==== 1002ac880 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButtonTouchUpInside: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButtonTouchUpInside_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_1002ac7cc(param_3);
  return;
}

// ==== 1002ac8d0 FUN_1002ac8d0 ====
void FUN_1002ac8d0(void)

{
  long lVar1;
  long lVar2;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_78 [32];
  undefined1 auStack_58 [24];
  
  lVar1 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  lVar2 = lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    lVar3 = *(long *)(lVar1 + 8);
    _swift_getObjectType();
    lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
    _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                       auStack_58,0,0);
    FUN_10018ed24(unaff_x20 + lVar1,auStack_78);
    (**(code **)(lVar3 + 0x10))();
    _swift_unknownObjectRelease(lVar2);
    FUN_10003d930(auStack_78);
  }
  return;
}

// ==== 1002ac984 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButtonTouchUpInside: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButtonTouchUpInside_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_1002ac8d0(param_3);
  return;
}

// ==== 1002ac9d4 FUN_1002ac9d4 ====
void FUN_1002ac9d4(void)

{
  long lVar1;
  long lVar2;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_78 [32];
  undefined1 auStack_58 [24];
  
  lVar1 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  lVar2 = lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    lVar3 = *(long *)(lVar1 + 8);
    _swift_getObjectType();
    lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
    _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                       auStack_58,0,0);
    FUN_10018ed24(unaff_x20 + lVar1,auStack_78);
    (**(code **)(lVar3 + 8))();
    _swift_unknownObjectRelease(lVar2);
    FUN_10003d930(auStack_78);
  }
  return;
}

// ==== 1002aca88 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButtonTouchUpInside: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButtonTouchUpInside_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_1002ac9d4(param_3);
  return;
}

// ==== 1002acad8 FUN_1002acad8 ====
void FUN_1002acad8(void)

{
  long lVar1;
  long lVar2;
  long unaff_x20;
  long lVar3;
  undefined1 auStack_78 [32];
  undefined1 auStack_58 [24];
  
  lVar1 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  lVar2 = lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    lVar3 = *(long *)(lVar1 + 8);
    _swift_getObjectType();
    lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
    _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                       auStack_58,0,0);
    FUN_10018ed24(unaff_x20 + lVar1,auStack_78);
    (**(code **)(lVar3 + 0x20))();
    _swift_unknownObjectRelease(lVar2);
    FUN_10003d930(auStack_78);
  }
  return;
}

// ==== 1002acb8c _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledValueChanged: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledValueChanged_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_1002acad8(param_3);
  return;
}

// ==== 1002acbdc FUN_1002acbdc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1002acbdc(undefined8 param_1,ID param_2,undefined8 param_3)

{
  long lVar1;
  ulong uVar2;
  code *pcVar3;
  undefined *puVar4;
  ID IVar5;
  undefined8 uVar6;
  ID IVar7;
  ID IVar8;
  ID IVar9;
  undefined *self;
  undefined *puVar10;
  ID IVar11;
  ID IVar12;
  ulong uVar13;
  char *pcVar14;
  char *pcVar15;
  code *pcVar16;
  long unaff_x20;
  undefined **ppuVar17;
  undefined1 auStack_88 [24];
  
  lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
  _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                     auStack_88,0x21,0);
  FUN_1002adbb4(param_3,unaff_x20 + lVar1);
  _swift_endAccess(auStack_88);
  lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView;
  IVar12 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 != 0) {
    puVar4 = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)puVar4,"clearColor");
    _objc_msgSend(IVar12,"setBackgroundColor:",IVar5);
  }
  IVar12 = unaff_x20 + lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 != 0) {
    IVar5 = _objc_msgSend(param_2,"id");
    IVar5 = (ID)(int)IVar5;
    FUN_1004300ec();
    if (((uint)IVar5 & 0xff) != 8) {
      FUN_10042f134();
      _objc_msgSend(IVar12,"frame");
      _CGRectGetHeight();
      uVar6 = 0;
      FUN_10057bfd4(0);
      _objc_allocWithZone();
      FUN_10057b154(param_1,0,IVar5,0,2,0,0,0,0,uVar6);
      _objc_msgSend(IVar12,"addSubview:",IVar5);
      _objc_msgSend(IVar5,"setTranslatesAutoresizingMaskIntoConstraints:",0);
      IVar11 = _objc_msgSend(IVar5,"leadingAnchor");
      IVar7 = _objc_msgSend(IVar12,"leadingAnchor");
      IVar11 = _objc_msgSend(IVar11,"constraintEqualToAnchor:",IVar7);
      IVar7 = _objc_msgSend(IVar5,"topAnchor");
      IVar8 = _objc_msgSend(IVar12,"topAnchor");
      IVar7 = _objc_msgSend(IVar7,"constraintEqualToAnchor:",IVar8);
      IVar8 = _objc_msgSend(IVar5,"centerXAnchor");
      IVar9 = _objc_msgSend(IVar12,"centerXAnchor");
      IVar8 = _objc_msgSend(IVar8,"constraintEqualToAnchor:",IVar9);
      IVar5 = _objc_msgSend(IVar5,"centerYAnchor");
      IVar9 = _objc_msgSend(IVar12,"centerYAnchor");
      IVar5 = _objc_msgSend(IVar5,"constraintEqualToAnchor:",IVar9);
      self = &_OBJC_CLASS___NSLayoutConstraint;
      _swift_getInitializedObjCClass();
      puVar4 = self;
      FUN_10078bde8();
      _swift_allocObject();
      *(undefined8 *)(puVar4 + 0x18) = 9;
      *(undefined8 *)(puVar4 + 0x10) = 4;
      *(ID *)(puVar4 + 0x20) = IVar11;
      *(ID *)(puVar4 + 0x28) = IVar7;
      *(ID *)(puVar4 + 0x30) = IVar8;
      *(ID *)(puVar4 + 0x38) = IVar5;
      uVar6 = 0;
      FUN_10018cfe8(0);
      puVar10 = puVar4;
      __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar4,uVar6);
      _swift_bridgeObjectRelease(puVar4);
      _objc_msgSend((ID)self,"activateConstraints:",puVar10);
      _objc_msgSend(IVar12,"setHidden:",0);
    }
  }
  IVar12 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 == 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x1002ad508);
    (*pcVar3)();
  }
  pcVar14 = "title";
  IVar5 = _objc_msgSend(param_2,"title");
  if (IVar5 == 0) {
    IVar5 = 0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    puVar4 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar11 = _objc_msgSend((ID)puVar4,"mainBundle");
    pcVar15 = pcVar14;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (IVar5,pcVar14,0,0,IVar11,0,0xe000000000000000,0,0xe000000000000000);
    _swift_bridgeObjectRelease(pcVar14);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar5,pcVar15);
    _swift_bridgeObjectRelease(pcVar15);
  }
  _objc_msgSend(IVar12,"setText:",IVar5);
  IVar12 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 == 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x1002ad50c);
    (*pcVar3)();
  }
  IVar5 = _objc_msgSend(param_2,"enabled");
  _objc_msgSend(IVar12,"setOn:",IVar5);
  if (DAT_100adefa0 != -1) {
    _swift_once(&DAT_100adefa0,FUN_10037c47c);
  }
  uVar2 = DAT_100b75f50;
  uVar13 = DAT_100b75f50;
  _swift_retain();
  FUN_10042f27c();
  IVar12 = uVar13 & 0xffffffff | (uVar13 >> 0x20 & 1) << 0x20;
  FUN_1003824b4();
  _swift_release(uVar2);
  if (IVar12 == 0) {
LAB_1002ad1bc:
    pcVar14 = "lastConnectedPortName";
    IVar12 = _objc_msgSend(param_2,"lastConnectedPortName");
    if (IVar12 == 0) {
      if (DAT_100adf8a0 != -1) {
        pcVar3 = FUN_10052fc08;
        _swift_once(&DAT_100adf8a0,FUN_10052fc08);
        pcVar14 = (char *)pcVar3;
      }
      pcVar3 = DAT_100b77028;
      IVar12 = DAT_100b77020;
      _swift_bridgeObjectRetain(DAT_100b77028);
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      pcVar3 = (code *)pcVar14;
    }
  }
  else {
    pcVar14 = "displayName";
    IVar12 = _objc_msgSend(IVar12,"displayName");
    if (IVar12 == 0) goto LAB_1002ad1bc;
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    pcVar3 = (code *)pcVar14;
  }
  if (DAT_100adec20 != -1) {
    pcVar16 = FUN_1001fd928;
    _swift_once(&DAT_100adec20,FUN_1001fd928);
    pcVar14 = (char *)pcVar16;
  }
  if (((IVar12 == DAT_100b75a00) && (pcVar3 == DAT_100b75a08)) ||
     (IVar5 = IVar12, pcVar14 = (char *)pcVar3,
     __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
               (IVar12,pcVar3,DAT_100b75a00,DAT_100b75a08,0), (IVar5 & 1) != 0)) {
    _swift_bridgeObjectRelease(pcVar3);
    if (DAT_100adec18 != -1) {
      pcVar3 = FUN_1001fd87c;
      _swift_once(&DAT_100adec18,FUN_1001fd87c);
      pcVar14 = (char *)pcVar3;
    }
    pcVar3 = DAT_100b759f8;
    IVar12 = DAT_100b759f0;
    _swift_bridgeObjectRetain(DAT_100b759f8);
  }
  lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton;
  IVar5 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 == 0) {
    _swift_bridgeObjectRelease();
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar12,pcVar3);
    _swift_bridgeObjectRelease(pcVar3);
    pcVar14 = "setTitle:forState:";
    _objc_msgSend(IVar5,"setTitle:forState:",IVar12,0);
    pcVar3 = (code *)0x0;
  }
  FUN_10042f27c();
  uVar2 = DAT_100b75f50;
  if (((ulong)pcVar3 >> 0x20 & 1) == 0) {
    uVar13 = DAT_100b75f50;
    _swift_retain();
    FUN_10042f27c();
    uVar13 = uVar13 & 0xffffffff | (uVar13 >> 0x20 & 1) << 0x20;
    FUN_1003824b4();
    _swift_release(uVar2);
    if (uVar13 == 0) {
      ppuVar17 = &PTR_s_redColor_100aa2210;
    }
    else {
      ppuVar17 = &PTR_s_whiteColor_100aa07e8;
    }
    puVar4 = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    pcVar14 = *ppuVar17;
    IVar5 = _objc_msgSend((ID)puVar4,pcVar14);
    IVar12 = unaff_x20 + lVar1;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar12 == 0) goto LAB_1002ad3d0;
  }
  else {
    IVar12 = unaff_x20 + lVar1;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar12 == 0) goto LAB_1002ad3d0;
    puVar4 = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)puVar4,"grayColor");
  }
  pcVar14 = "setTitleColor:forState:";
  _objc_msgSend(IVar12,"setTitleColor:forState:",IVar5,0);
LAB_1002ad3d0:
  lVar1 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton;
  IVar12 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 != 0) {
    IVar5 = IVar12;
    FUN_10042f4dc();
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease(pcVar14);
    _objc_msgSend(IVar12,"setTitle:forState:",IVar5,0);
  }
  IVar12 = unaff_x20 + lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 != 0) {
    _objc_msgSend(IVar12,"setHidden:",0);
  }
  IVar12 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar12 != 0) {
    _objc_msgSend(IVar12,"setHidden:",0);
  }
  return;
}

// ==== 1002ad50c FUN_1002ad50c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_1002ad50c(long param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  long lVar2;
  ID IVar3;
  long lVar4;
  undefined *self;
  ID IVar5;
  undefined **ppuVar6;
  long unaff_x20;
  long lVar7;
  undefined8 uVar8;
  undefined1 auStack_68 [24];
  
  lVar4 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload;
  _swift_beginAccess(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload,
                     auStack_68,0x21,0);
  FUN_1002adbb4(param_2,unaff_x20 + lVar4);
  _swift_endAccess(auStack_68);
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    lVar4 = 0;
    FUN_1000af388();
    puVar1 = (undefined8 *)(param_1 + *(int *)(lVar4 + 0x14));
    uVar8 = *puVar1;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar8,puVar1[1]);
    _objc_msgSend(IVar3,"setText:",uVar8);
  }
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",0);
  }
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    lVar4 = 0;
    FUN_1000af388();
    _objc_msgSend(IVar3,"setOn:",(ulong)*(byte *)(param_1 + *(int *)(lVar4 + 0x1c)));
  }
  lVar4 = 0;
  FUN_1000af388();
  puVar1 = (undefined8 *)(param_1 + *(int *)(lVar4 + 0x18));
  lVar4 = puVar1[1];
  if (lVar4 == 0) {
    if (DAT_100adf8b0 != -1) {
      _swift_once(&DAT_100adf8b0,FUN_10052fc60);
    }
    lVar7 = DAT_100b77048;
    uVar8 = DAT_100b77040;
    _swift_bridgeObjectRetain(DAT_100b77048);
  }
  else {
    uVar8 = *puVar1;
    lVar7 = lVar4;
  }
  lVar2 = _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton;
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton;
  _swift_unknownObjectWeakLoadStrong();
  _swift_bridgeObjectRetain(lVar4);
  if (IVar3 == 0) {
    _swift_bridgeObjectRelease(lVar7);
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar8,lVar7);
    _swift_bridgeObjectRelease(lVar7);
    _objc_msgSend(IVar3,"setTitle:forState:",uVar8,0);
  }
  if (lVar4 == 0) {
    ppuVar6 = &PTR_s_grayColor_100aa1968;
  }
  else {
    ppuVar6 = &PTR_s_whiteColor_100aa07e8;
  }
  self = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar5 = _objc_msgSend((ID)self,*ppuVar6);
  IVar3 = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setTitleColor:forState:",IVar5,0);
  }
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  return 0;
}

// ==== 1002ad800 FUN_1002ad800 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1002ad800(undefined8 param_1,undefined8 param_2,long param_3)

{
  undefined8 *puVar1;
  long lVar2;
  ID IVar3;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView,0
            );
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch,0);
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  lVar2 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  *(undefined8 *)(lVar2 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar2,0);
  if (param_3 == 0) {
    param_2 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_2,param_3);
    _swift_bridgeObjectRelease(param_3);
  }
  IVar3 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,
                              "initWithStyle:reuseIdentifier:",param_1,param_2);
  return IVar3;
}

// ==== 1002ad950 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::initWithStyle:reuseIdentifier: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::initWithStyle_reuseIdentifier_
             (ID param_1,SEL param_2,long_long param_3,ID param_4)

{
  if (param_4 == 0) {
    param_2 = (SEL)0x0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(param_4);
  }
  FUN_1002ad800(param_3,param_4,param_2);
  return param_3;
}

// ==== 1002ad998 FUN_1002ad998 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1002ad998(undefined8 param_1)

{
  undefined8 *puVar1;
  long lVar2;
  ID IVar3;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::markerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::titleEditButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::destinationButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::channelArrowImageView,0
            );
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::enabledSwitch,0);
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::payload);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  lVar2 = unaff_x20 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
  *(undefined8 *)(lVar2 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar2,0);
  IVar3 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffc0,"initWithCoder:",param_1);
  return IVar3;
}

// ==== 1002adac4 _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::initWithCoder_
             (ID param_1,SEL param_2,ID param_3)

{
  FUN_1002ad998();
  return param_3;
}

// ==== 1002adaec _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_unknownObjectWeakDestroy(param_1 + markerContainerView);
  _swift_unknownObjectWeakDestroy(param_1 + titleLabel);
  _swift_unknownObjectWeakDestroy(param_1 + titleEditButton);
  _swift_unknownObjectWeakDestroy(param_1 + destinationButton);
  _swift_unknownObjectWeakDestroy(param_1 + channelButton);
  _swift_unknownObjectWeakDestroy(param_1 + channelArrowImageView);
  _swift_unknownObjectWeakDestroy(param_1 + enabledSwitch);
  FUN_10003d930(param_1 + payload);
  FUN_100026610(param_1 + delegate);
  return;
}

// ==== 1002adb94 FUN_1002adb94 ====
void FUN_1002adb94(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback35RoutingSelectorMIDIBusTableViewCell)
  ;
  return;
}

// ==== 1002c662c FUN_1002c662c ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_1002c662c(undefined8 param_1,undefined8 param_2,long param_3,long param_4,ID param_5,
                  long param_6)

{
  code *pcVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ID IVar6;
  undefined *puVar7;
  undefined *puVar8;
  void *pvVar9;
  undefined8 *puVar10;
  undefined *puVar11;
  undefined8 *puVar12;
  ID IVar13;
  ID IVar14;
  ulong uVar15;
  ID IVar16;
  long lVar17;
  ulong uVar18;
  long lVar19;
  undefined1 *puVar20;
  uint uVar21;
  ulong uVar22;
  undefined8 uVar23;
  undefined1 auStack_f0 [8];
  long local_e8;
  ID local_e0;
  long local_d8;
  long local_d0;
  long local_c8;
  long lStack_c0;
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  code *local_98;
  undefined *local_90;
  
  lVar2 = 0;
  uVar23 = param_1;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar19 = *(long *)(lVar2 + -8);
  puVar20 = auStack_f0 + -(*(long *)(lVar19 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  local_c8 = *(long *)(lVar3 + -8);
  local_d0 = (long)puVar20 - (*(long *)(local_c8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lStack_c0 = lVar3;
  if (*(long *)(param_4 + 0x18) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined8 *)(*(long *)(param_4 + 0x18) + 0x20);
    _swift_retain();
  }
  uVar15 = *(ulong *)(param_3 + _TtC8Playback9Sequencer::channelGroup);
  *(undefined8 *)(param_3 + _TtC8Playback9Sequencer::channelGroup) = uVar4;
  _swift_release();
  FUN_1004f1918();
  FUN_1002de548();
  if (uVar15 >> 0x3e == 0) {
    uVar22 = *(ulong *)((uVar15 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar22 = uVar15 & 0xffffffffffffff8;
    if ((long)uVar15 < 0) {
      uVar22 = uVar15;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  local_e0 = param_5;
  if (uVar22 != 0) {
    if ((long)uVar22 < 1) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x1002c6e80);
      (*pcVar1)();
    }
    local_e8 = param_6;
    local_d8 = param_4;
    _swift_bridgeObjectRetain(uVar15);
    uVar18 = 0;
    do {
      if ((uVar15 & 0xc000000000000001) == 0) {
        uVar5 = *(ulong *)(uVar15 + uVar18 * 8 + 0x20);
      }
      else {
        uVar5 = uVar18;
        FUN_1000cc338(uVar18,uVar15);
      }
      uVar18 = uVar18 + 1;
      *(undefined1 *)(uVar5 + _TtC8Playback9SongTrack::soloState) = 1;
    } while (uVar22 != uVar18);
    _swift_bridgeObjectRelease(uVar15);
    param_6 = local_e8;
    param_4 = local_d8;
  }
  IVar6 = local_e0;
  _swift_bridgeObjectRelease(uVar15);
  if ((*(long *)(param_4 + 0x18) != 0) &&
     (lVar3 = *(long *)(*(long *)(param_4 + 0x18) + 0x20), lVar3 != 0)) {
    _swift_retain(lVar3);
    FUN_10064521c(IVar6,1);
    _swift_release(lVar3);
  }
  lVar3 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar16 = *(ID *)(param_6 + _TtC8Playback9Sequencer::song);
  IVar6 = *(ID *)(IVar16 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar6 == 0) {
    IVar14 = _objc_msgSend(IVar16,"workingCopyArrangementID");
    if (IVar14 == 0) goto LAB_1002c6e2c;
    IVar13 = IVar14;
    FUN_10032ee88();
    IVar6 = IVar13;
    FUN_1005e3b94(IVar13,IVar14);
    local_d8 = lVar19;
    _swift_bridgeObjectRelease(IVar13);
    if (IVar6 == 0) goto LAB_1002c6e2c;
    *(ID *)(IVar16 + lVar3) = IVar6;
    lVar19 = local_d8;
  }
  IVar6 = _objc_msgSend(IVar6,"song");
  if ((IVar6 == 0) || ((*(byte *)(IVar6 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
    uVar21 = 0;
    FUN_1002da058();
    if ((uVar21 & 0xfe) != 2) goto LAB_1002c6e2c;
  }
  else {
    uVar21 = 3;
  }
  lVar3 = *(long *)(param_4 + 0x18);
  if (lVar3 != 0) {
    lVar17 = *(long *)(lVar3 + 0x18);
    if (lVar17 != 0) {
      _swift_retain(lVar17);
      FUN_1006471c8(0);
      _swift_release(lVar17);
      lVar3 = *(long *)(param_4 + 0x18);
      if (lVar3 == 0) goto LAB_1002c68ec;
    }
    if ((*(long *)(lVar3 + 0x18) != 0) &&
       (lVar3 = *(long *)(*(long *)(lVar3 + 0x18) + _TtC8Playback16SongChannelGroup::midiOutChannel)
       , lVar3 != 0)) {
      *(undefined1 *)(lVar3 + 0x40) = 0;
      *(undefined1 *)(*(long *)(lVar3 + 0x38) + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = 0;
      _swift_retain(lVar3);
      FUN_10049ffc8();
      _swift_release(lVar3);
    }
  }
LAB_1002c68ec:
  puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_d8 = lVar19;
  if ((uVar21 & 0xff) == 3) {
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_e8 = 0;
    puVar7 = &DAT_100a3ed78;
    _swift_allocObject(&DAT_100a3ed78,0x18,7);
    _swift_weakInit(puVar7 + 0x10,param_4);
    puVar8 = &DAT_100a3ef08;
    _swift_allocObject(&DAT_100a3ef08,0x28,7);
    *(undefined **)(puVar8 + 0x10) = puVar7;
    *(undefined8 *)(puVar8 + 0x18) = param_1;
    *(undefined8 *)(puVar8 + 0x20) = param_2;
    local_98 = FUN_1002c7f08;
    local_b8 = puVar11;
    uVar23 = 0x42000000;
    local_b0 = 0x42000000;
    local_a8 = FUN_10056b3d8;
    puStack_a0 = &DAT_100a3ef20;
    local_90 = puVar8;
    pvVar9 = __Block_copy(&local_b8);
    _swift_release(local_90);
    lVar19 = local_d0;
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_d0);
    puVar7 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar10 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar11);
    puVar11 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar12 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar7);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (puVar20,&local_b8,puVar11,puVar12,lVar2,puVar10);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,lVar19,puVar20,pvVar9);
    __Block_release(pvVar9);
    (**(code **)(local_d8 + 8))(puVar20,lVar2);
    puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
    (**(code **)(local_c8 + 8))(lVar19,lStack_c0);
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar15 = DAT_100b757a8;
  FUN_100171514();
  if ((uVar15 & 1) != 0) {
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    IVar6 = *(ID *)(DAT_100b75a80 + 0x10);
    if ((IVar6 != 0) &&
       (FUN_1004a9df0(), lVar19 = _TtC8Playback4Song::privateWorkingCopyArrangement, IVar6 != 0)) {
      IVar16 = *(ID *)(IVar6 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar16 == 0) {
        IVar14 = _objc_msgSend(IVar6,"workingCopyArrangementID");
        puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        if (IVar14 != 0) {
          IVar13 = IVar14;
          FUN_10032ee88();
          IVar16 = IVar13;
          FUN_1005e3b94(IVar13,IVar14);
          _swift_bridgeObjectRelease(IVar13);
          puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
          if (IVar16 != 0) {
            *(ID *)(IVar6 + lVar19) = IVar16;
            goto LAB_1002c6b38;
          }
        }
      }
      else {
LAB_1002c6b38:
        lVar19 = *(long *)(param_4 + 0x18);
        puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        if (lVar19 != 0) {
          _swift_retain(lVar19);
          _objc_msgSend(IVar16,"masterVolumeLevel");
          uVar4 = uVar23;
          _objc_msgSend(local_e0,"masterVolumeLevel");
          *(undefined1 *)(lVar19 + 0x58) = 1;
          FUN_100736e24(uVar23,uVar4,param_1,param_2);
          _swift_release(lVar19);
          puVar11 = PTR___NSConcreteStackBlock_100a1d8e8;
        }
      }
    }
  }
  FUN_1004f5388(1);
  FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  local_98 = FUN_1002c6f78;
  local_90 = (undefined *)0x0;
  local_b0 = 0x42000000;
  local_a8 = FUN_10056b3d8;
  puStack_a0 = &DAT_100a3eed0;
  local_b8 = puVar11;
  pvVar9 = __Block_copy(&local_b8);
  lVar19 = local_d0;
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_d0);
  puVar7 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar10 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar11);
  puVar11 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar12 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar7);
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (puVar20,&local_b8,puVar11,puVar12,lVar2,puVar10);
  __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (0,lVar19,puVar20,pvVar9);
  __Block_release(pvVar9);
  (**(code **)(local_d8 + 8))(puVar20,lVar2);
  (**(code **)(local_c8 + 8))(lVar19,lStack_c0);
LAB_1002c6e2c:
  FUN_1004f8088();
  return;
}

// ==== 100370d14 FUN_100370d14 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined * FUN_100370d14(undefined8 param_1,undefined *param_2)

{
  code *pcVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  ID IVar6;
  undefined8 *puVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined **ppuVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined *puVar16;
  ulong uVar17;
  long lVar18;
  long lVar19;
  long unaff_x20;
  undefined8 *puVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  undefined *puVar24;
  long lVar25;
  long lVar26;
  undefined8 auStack_e0 [2];
  undefined *apuStack_d0 [3];
  long local_b8;
  undefined1 auStack_98 [24];
  undefined *local_80;
  undefined *puStack_78;
  long local_68;
  
  lVar3 = 0;
  FUN_1000af388();
  lVar25 = (long)apuStack_d0 - (*(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0)
  ;
  puVar5 = &DAT_100afca58;
  FUN_100021774();
  lVar22 = lVar25 - (*(long *)(*(long *)(puVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  FUN_1004e18e8();
  lVar23 = *(long *)(lVar4 + -8);
  uVar17 = *(long *)(lVar23 + 0x40) + 0xfU & 0xfffffffffffffff0;
  apuStack_d0[2] = (undefined *)(lVar22 - uVar17);
  lVar26 = (long)apuStack_d0[2] - uVar17;
  lVar19 = lVar26 - uVar17;
  local_b8 = lVar19 - uVar17;
  puVar20 = (undefined8 *)(local_b8 - uVar17);
  lVar18 = (long)puVar20 - uVar17;
  lVar21 = *(long *)(unaff_x20 + _TtC8Playback29RoutingSelectorViewController::routingSources);
  lVar3 = lVar21;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  uVar14 = 1;
  if ((-1 < lVar3) && (lVar3 < *(long *)(lVar21 + 0x10))) {
    FUN_100023384(lVar21 + ((ulong)*(byte *)(lVar23 + 0x50) + 0x20 &
                           ((ulong)*(byte *)(lVar23 + 0x50) ^ 0xffffffffffffffff)) +
                  *(long *)(lVar23 + 0x48) * lVar3,lVar22,FUN_1004e18e8);
    uVar14 = 0;
  }
  (**(code **)(lVar23 + 0x38))(lVar22,uVar14,1,lVar4);
  _swift_bridgeObjectRelease(lVar21);
  lVar3 = lVar22;
  (**(code **)(lVar23 + 0x30))(lVar22,1,lVar4);
  if ((int)lVar3 == 1) {
    FUN_100023be4(lVar22,&DAT_100afca58);
    puVar5 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar6 = _objc_msgSend((ID)puVar5,"mainBundle");
    uVar14 = 0xd00000000000001c;
    *(undefined8 *)(lVar18 + -0x10) = 0xe000000000000000;
    uVar15 = 0x80000001008ef010;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd00000000000001c,0x80000001008ef010,0,0,IVar6,0,0xe000000000000000,0);
    FUN_100848d4c(param_2,uVar14,uVar15,0,0);
    _swift_bridgeObjectRelease(uVar15);
    return param_2;
  }
  FUN_100023340(lVar22,lVar18,FUN_1004e18e8);
  FUN_100023384(lVar18,puVar20,FUN_1004e18e8);
  puVar7 = puVar20;
  _swift_getEnumCaseMultiPayload(puVar20,lVar4);
  iVar2 = (int)puVar7;
  if (iVar2 < 3) {
    if ((iVar2 != 0) && (iVar2 == 1)) {
      _swift_bridgeObjectRelease(puVar20[1]);
    }
    IVar6 = unaff_x20 + _TtC8Playback29RoutingSelectorViewController::routingTableView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar6 == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x100371850);
      (*pcVar1)();
    }
    uVar15 = 0xd000000000000027;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000027,0x80000001008ef090);
    uVar14 = uVar15;
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    puVar8 = (undefined *)
             _objc_msgSend(IVar6,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar15,uVar14);
    puVar5 = (undefined *)0x0;
    FUN_1002ae804();
    puVar13 = puVar8;
    _swift_dynamicCastClass();
    if (puVar13 != (undefined *)0x0) {
      puVar24 = puVar8;
      FUN_1004e1cf8();
      puVar12 = puVar5;
      apuStack_d0[1] = puVar24;
      apuStack_d0[2] = puVar8;
      if (puVar5 == (undefined *)0x0) {
        FUN_1004e1c38();
        FUN_1004e4490();
        puVar12 = puVar5;
        _swift_bridgeObjectRetain();
        __s10Foundation9IndexPathV5UIKitE3rowSivg();
        local_80 = puVar12 + 1;
        if (SCARRY8((long)puVar12,1)) {
                    /* WARNING: Does not return */
          pcVar1 = (code *)SoftwareBreakpoint(1,0x100371760);
          (*pcVar1)();
        }
        puVar12 = PTR___sSiN_100a1dd88;
        puVar11 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
        __ss23CustomStringConvertibleP11descriptionSSvgTj(PTR___sSiN_100a1dd88);
        local_80 = puVar24;
        puStack_78 = puVar5;
        _swift_bridgeObjectRetain(puVar5);
        puVar16 = puVar11;
        __sSS6appendyySSF(puVar12);
        _swift_bridgeObjectRelease(puVar5);
        _swift_bridgeObjectRelease(puVar11);
        apuStack_d0[1] = local_80;
        puVar24 = puVar11;
        puVar5 = puVar16;
        puVar12 = puStack_78;
      }
      FUN_1004e2078();
      if (puVar5 == (undefined *)0x0) {
        if (DAT_100adf698 != -1) {
          _swift_once(&DAT_100adf698,FUN_10052e8f0);
        }
        puVar5 = DAT_100b76c18;
        puVar24 = DAT_100b76c10;
        _swift_bridgeObjectRetain(DAT_100b76c18);
      }
      lVar3 = local_b8;
      FUN_100023384(lVar18,local_b8,FUN_1004e18e8);
      lVar19 = lVar3;
      _swift_getEnumCaseMultiPayload(lVar3,lVar4);
      FUN_1000233c8(lVar3,FUN_1004e18e8);
      FUN_100373c1c(apuStack_d0[1],puVar12,puVar24,puVar5,(int)lVar19 == 0,unaff_x20,puVar13);
      _swift_bridgeObjectRelease(puVar12);
      _swift_bridgeObjectRelease(puVar5);
    }
  }
  else {
    local_68 = lVar4;
    if (iVar2 == 3) {
      uVar14 = *puVar20;
      IVar6 = unaff_x20 + _TtC8Playback29RoutingSelectorViewController::routingTableView;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar6 == 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1,0x100371854);
        (*pcVar1)();
      }
      uVar9 = 0xd000000000000023;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000023,0x80000001008ef030);
      uVar15 = uVar9;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      puVar8 = (undefined *)
               _objc_msgSend(IVar6,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar9,uVar15);
      uVar15 = 0;
      FUN_1002adb94(0);
      puVar5 = puVar8;
      _swift_dynamicCastClass(puVar8,uVar15);
      if (puVar5 != (undefined *)0x0) {
        ppuVar10 = &local_80;
        FUN_1000881c8(ppuVar10);
        FUN_100023384(lVar18,ppuVar10,FUN_1004e18e8);
        FUN_1002acbdc(uVar14,&local_80);
LAB_100371280:
        FUN_1000233c8(lVar18,FUN_1004e18e8);
        FUN_100023be4(&local_80,&DAT_100af56a0);
        puVar5 = puVar5 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate;
        *(undefined ***)(puVar5 + 8) = &PTR_PTR_100a41470;
        _swift_unknownObjectWeakAssign(puVar5,unaff_x20);
        return puVar8;
      }
    }
    else if (iVar2 == 4) {
      FUN_100023340(puVar20,lVar25,FUN_1000af388);
      IVar6 = unaff_x20 + _TtC8Playback29RoutingSelectorViewController::routingTableView;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar6 == 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1,0x100371858);
        (*pcVar1)();
      }
      uVar15 = 0xd000000000000023;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000023,0x80000001008ef030);
      uVar14 = uVar15;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      puVar8 = (undefined *)
               _objc_msgSend(IVar6,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar15,uVar14);
      uVar14 = 0;
      FUN_1002adb94(0);
      puVar5 = puVar8;
      _swift_dynamicCastClass(puVar8,uVar14);
      if (puVar5 != (undefined *)0x0) {
        ppuVar10 = &local_80;
        FUN_1000881c8(ppuVar10);
        FUN_100023384(lVar18,ppuVar10,FUN_1004e18e8);
        FUN_1002ad50c(lVar25,&local_80);
        FUN_1000233c8(lVar25,FUN_1000af388);
        goto LAB_100371280;
      }
      FUN_1000233c8(lVar25,FUN_1000af388);
    }
    else {
      IVar6 = unaff_x20 + _TtC8Playback29RoutingSelectorViewController::routingTableView;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar6 == 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1,0x10037185c);
        (*pcVar1)();
      }
      uVar14 = 0xd000000000000029;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000029,0x80000001008ef060);
      uVar15 = uVar14;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      puVar8 = (undefined *)
               _objc_msgSend(IVar6,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar14,uVar15);
      uVar14 = 0;
      FUN_1002ae288(0);
      puVar5 = puVar8;
      _swift_dynamicCastClass(puVar8,uVar14);
      if (puVar5 != (undefined *)0x0) {
        FUN_100023384(lVar18,lVar19,FUN_1004e18e8);
        lVar3 = lVar19;
        _swift_getEnumCaseMultiPayload(lVar19,lVar4);
        if ((int)lVar3 != 5) {
          FUN_1000233c8(lVar19,FUN_1004e18e8);
          FUN_1000233c8(lVar18,FUN_1004e18e8);
          return puVar8;
        }
        FUN_100023384(lVar18,lVar26,FUN_1004e18e8);
        lVar3 = lVar26;
        _swift_getEnumCaseMultiPayload(lVar26,lVar4);
        puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
        if ((int)lVar3 == 5) {
          if (DAT_100adefa0 != -1) {
            _swift_once(&DAT_100adefa0,FUN_10037c47c);
          }
          puVar13 = DAT_100b75f50;
          _swift_beginAccess(DAT_100b75f50 + 0x18,auStack_98,0,0);
          puVar24 = *(undefined **)(puVar13 + 0x18);
          if ((ulong)puVar24 >> 0x3e == 0) {
            _swift_bridgeObjectRetain_n(puVar24,2);
            __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
            FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
            _swift_bridgeObjectRelease(puVar24);
            puVar13 = puVar24;
          }
          else {
            puVar13 = (undefined *)((ulong)puVar24 & 0xffffffffffffff8);
            if ((long)puVar24 < 0) {
              puVar13 = puVar24;
            }
            uVar14 = 0;
            FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
            _swift_bridgeObjectRetain(puVar24);
            __ss17_bridgeCocoaArrayySayxGyXllF(puVar13,uVar14);
            _swift_bridgeObjectRelease(puVar24);
          }
        }
        else {
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          FUN_1000233c8(lVar26,FUN_1004e18e8);
        }
        puVar12 = apuStack_d0[2];
        FUN_100023384(lVar18,apuStack_d0[2],FUN_1004e18e8);
        puVar11 = puVar12;
        _swift_getEnumCaseMultiPayload(puVar12,lVar4);
        puVar24 = PTR___swiftEmptyArrayStorage_100a1e050;
        if ((int)puVar11 == 5) {
          if (DAT_100adefa0 != -1) {
            _swift_once(&DAT_100adefa0,FUN_10037c47c);
          }
          puVar24 = DAT_100b75f50;
          puVar12 = DAT_100b75f50;
          _swift_retain();
          FUN_10037acf0();
          _swift_release(puVar24);
          if ((ulong)puVar12 >> 0x3e == 0) {
            _swift_bridgeObjectRetain(puVar12);
            __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
            FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
            _swift_bridgeObjectRelease(puVar12);
            puVar24 = puVar12;
          }
          else {
            puVar24 = (undefined *)((ulong)puVar12 & 0xffffffffffffff8);
            if ((long)puVar12 < 0) {
              puVar24 = puVar12;
            }
            uVar14 = 0;
            FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
            _swift_bridgeObjectRetain(puVar12);
            __ss17_bridgeCocoaArrayySayxGyXllF(puVar24,uVar14);
            _swift_bridgeObjectRelease_n(puVar12,2);
          }
        }
        else {
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          FUN_1000233c8(puVar12,FUN_1004e18e8);
        }
        ppuVar10 = &local_80;
        FUN_1000881c8(ppuVar10);
        FUN_100023384(lVar18,ppuVar10,FUN_1004e18e8);
        FUN_10074b4c4(0,puVar13,puVar24,&local_80,unaff_x20,puVar5);
        _swift_bridgeObjectRelease(puVar13);
        _swift_bridgeObjectRelease(puVar24);
        FUN_1000233c8(lVar18,FUN_1004e18e8);
        FUN_100023be4(&local_80,&DAT_100af56a0);
        return puVar8;
      }
    }
  }
  FUN_1000233c8(lVar18,FUN_1004e18e8);
  return puVar8;
}

// ==== 1003762bc FUN_1003762bc ====
void FUN_1003762bc(ulong param_1)

{
  long lVar1;
  undefined1 *puVar2;
  long unaff_x20;
  long lVar3;
  ID self;
  undefined4 uVar4;
  undefined1 auStack_48 [24];
  
  lVar3 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  puVar2 = auStack_48;
  _swift_beginAccess(unaff_x20 + _TtC8Playback20MIDIClockAVAudioUnit::parameters,puVar2,0x20,0);
  lVar3 = *(long *)(unaff_x20 + lVar3);
  if (*(long *)(lVar3 + 0x10) != 0) {
    lVar1 = 0;
    thunk_FUN_100793c60();
    if (((ulong)puVar2 & 1) != 0) {
      self = *(ID *)(*(long *)(lVar3 + 0x38) + lVar1 * 8);
      _swift_endAccess(auStack_48);
      uVar4 = 0x3f800000;
      if ((param_1 & 1) == 0) {
        uVar4 = 0;
      }
      _objc_msgSend(self,"setValue:",uVar4);
      return;
    }
  }
  _swift_endAccess(auStack_48);
  return;
}

// ==== 100376358 FUN_100376358 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_100376358(void)

{
  long lVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ID self;
  ID IVar5;
  undefined8 in_x6;
  undefined8 in_x7;
  long unaff_x20;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined4 local_60;
  
  _swift_getObjectType();
  lVar1 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079d3a4();
  *(undefined **)(unaff_x20 + lVar1) = puVar2;
  *(undefined8 *)(unaff_x20 + _TtC8Playback20MIDIClockAVAudioUnit::parameterObserverToken) = 0;
  puVar2 = &_OBJC_CLASS___AUAudioUnit;
  _swift_getInitializedObjCClass();
  uVar3 = 0;
  FUN_100023404(0,&DAT_100b00438,&PTR__OBJC_CLASS___MIDIClockAudioUnit_100aa4160);
  _swift_getObjCClassFromMetadata();
  uVar4 = 0xd000000000000010;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000010,0x80000001008ef1f0);
  uVar7 = 0x24d544b53;
  uVar6 = 0x6d64636b6175676e;
  uStack_68 = 0x24d544b53;
  local_70 = 0x6d64636b6175676e;
  local_60 = 0;
  _objc_msgSend((ID)puVar2,"registerSubclass:asComponentDescription:name:version:",uVar3,&local_70,
                uVar4,0xffffffff,in_x6,in_x7,0x6d64636b6175676e,0x24d544b53);
  local_60 = 0;
  local_70 = uVar6;
  uStack_68 = uVar7;
  self = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,
                             "initWithAudioComponentDescription:",&local_70);
  IVar5 = _objc_msgSend(self,"AUAudioUnit");
  IVar5 = _objc_msgSend(IVar5,"parameterTree");
  if (IVar5 != 0) {
    FUN_1003767e8();
    lVar1 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
    _swift_beginAccess(self + _TtC8Playback20MIDIClockAVAudioUnit::parameters,&local_70,1,0);
    uVar3 = *(undefined8 *)(self + lVar1);
    *(ID *)(self + lVar1) = IVar5;
    _swift_bridgeObjectRelease(uVar3);
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar3 = DAT_100b75f50;
    uVar4 = DAT_100b75f50;
    _swift_retain(DAT_100b75f50);
    FUN_10037acf0();
    _swift_release(uVar3);
    FUN_100375fc8(uVar4);
    _swift_bridgeObjectRelease(uVar4);
  }
  return self;
}

// ==== 100376548 _TtC8Playback20MIDIClockAVAudioUnit::init ====
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback20MIDIClockAVAudioUnit::init(ID param_1,SEL param_2)

{
  FUN_100376358();
  return param_1;
}

// ==== 100376568 FUN_100376568 ====
void FUN_100376568(void)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long unaff_x20;
  undefined1 auStack_48 [24];
  
  _swift_getObjectType();
  lVar2 = _TtC8Playback20MIDIClockAVAudioUnit::parameters;
  _swift_beginAccess(unaff_x20 + _TtC8Playback20MIDIClockAVAudioUnit::parameters,auStack_48,1,0);
  puVar1 = PTR___swiftEmptyDictionarySingleton_100a1e058;
  uVar3 = *(undefined8 *)(unaff_x20 + lVar2);
  *(undefined **)(unaff_x20 + lVar2) = PTR___swiftEmptyDictionarySingleton_100a1e058;
  _swift_bridgeObjectRelease(uVar3);
  *(undefined8 *)(unaff_x20 + _TtC8Playback20MIDIClockAVAudioUnit::parameterObserverToken) = 0;
  _swift_retain(puVar1);
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa8,"dealloc");
  return;
}

// ==== 1003765f8 _TtC8Playback20MIDIClockAVAudioUnit::dealloc ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback20MIDIClockAVAudioUnit::dealloc(ID param_1,SEL param_2)

{
  undefined *puVar1;
  long lVar2;
  class_t *pcVar3;
  undefined8 uVar4;
  objc_super local_68;
  undefined1 auStack_58 [24];
  
  pcVar3 = (class_t *)param_1;
  _swift_getObjectType();
  lVar2 = parameters;
  _swift_beginAccess(param_1 + parameters,auStack_58,1,0);
  puVar1 = PTR___swiftEmptyDictionarySingleton_100a1e058;
  uVar4 = *(undefined8 *)(param_1 + lVar2);
  *(undefined **)(param_1 + lVar2) = PTR___swiftEmptyDictionarySingleton_100a1e058;
  _swift_bridgeObjectRelease(uVar4);
  *(undefined8 *)(param_1 + parameterObserverToken) = 0;
  local_68.receiver = param_1;
  local_68.super_class = pcVar3;
  _swift_retain(puVar1);
  _objc_msgSendSuper2(&local_68,"dealloc");
  return;
}

// ==== 1003766a0 _TtC8Playback20MIDIClockAVAudioUnit::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback20MIDIClockAVAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + parameters));
  return;
}

// ==== 1003766b0 _TtC8Playback20MIDIClockAVAudioUnit::initWithAudioComponentDescription: ====
/* Function Stack Size: 0x24 bytes */

ID _TtC8Playback20MIDIClockAVAudioUnit::initWithAudioComponentDescription_
             (ID param_1,SEL param_2,AudioComponentDescription param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.MIDIClockAVAudioUnit",0x1d,"init(audioComponentDescription:)",0x20,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1003766dc);
  (*pcVar1)();
}

// ==== 1003766dc FUN_1003766dc ====
void FUN_1003766dc(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback20MIDIClockAVAudioUnit);
  return;
}

// ==== 1003aeea4 FUN_1003aeea4 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined * FUN_1003aeea4(ID param_1)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  undefined *puVar8;
  class_t *pcVar9;
  ID IVar10;
  ID self;
  class_t *pcVar11;
  ID unaff_x20;
  undefined8 uVar12;
  undefined *puVar13;
  objc_super local_90;
  objc_super local_80;
  objc_super local_70;
  objc_super local_60;
  
  IVar10 = param_1;
  __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
  _objc_msgSend(param_1,"deselectRowAtIndexPath:animated:",IVar10,1);
  lVar7 = _TtC8Playback30MIDICueItemTableViewController::stagedType;
  lVar6 = _TtC8Playback30MIDICueItemTableViewController::mode;
  puVar8 = &DAT_100b00c40;
  FUN_100021774();
  _swift_initStaticObject();
  puVar13 = puVar8;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (((long)puVar13 < 0) || (*(long *)(puVar8 + 0x10) <= (long)puVar13)) {
    _swift_bridgeObjectRelease(puVar8);
    return puVar8;
  }
  bVar2 = (puVar8 + (long)puVar13)[0x20];
  _swift_bridgeObjectRelease(puVar8);
  if (bVar2 < 2) {
    if (bVar2 == 0) {
      puVar13 = *(undefined **)(unaff_x20 + lVar6);
      uVar12 = *(undefined8 *)(unaff_x20 + _TtC8Playback30MIDICueItemTableViewController::stagedBus)
      ;
      pcVar9 = (class_t *)0x0;
      FUN_1006f6410();
      pcVar11 = pcVar9;
      _objc_allocWithZone();
      puVar8 = puVar13;
      FUN_1004303d8();
      if (puVar8 == (undefined *)0x0) {
        puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain();
      }
      *(undefined **)
       ((long)&pcVar11->isa + _TtC8Playback33MIDICueItemBusTableViewController::midiBuses) = puVar8;
      lVar6 = _TtC8Playback33MIDICueItemBusTableViewController::selectedMIDIBus;
      *(undefined8 *)
       ((long)&pcVar11->isa + _TtC8Playback33MIDICueItemBusTableViewController::selectedMIDIBus) = 0
      ;
      *(undefined **)
       ((long)&pcVar11->isa + _TtC8Playback33MIDICueItemBusTableViewController::midiEvent) = puVar13
      ;
      *(undefined8 *)((long)&pcVar11->isa + lVar6) = uVar12;
      *(undefined ***)
       ((long)&pcVar11->superclass + _TtC8Playback33MIDICueItemBusTableViewController::delegate) =
           &PTR_PTR_100a42e88;
      _swift_unknownObjectUnownedInit();
      local_90.receiver = (ID)pcVar11;
      local_90.super_class = pcVar9;
      IVar10 = _objc_msgSendSuper2(&local_90,"initWithStyle:",0);
      self = _objc_msgSend(unaff_x20,"navigationController");
    }
    else {
      if (bVar2 != 1) {
        return puVar8;
      }
      uVar12 = *(undefined8 *)(unaff_x20 + lVar6);
      uVar3 = *(undefined1 *)(unaff_x20 + lVar7);
      pcVar9 = (class_t *)0x0;
      FUN_100529cc8();
      pcVar11 = pcVar9;
      _objc_allocWithZone();
      lVar6 = _TtC8Playback37MIDICueItemMessageTableViewController::selectedEventType;
      *(undefined1 *)
       ((long)&pcVar11->isa +
       _TtC8Playback37MIDICueItemMessageTableViewController::selectedEventType) = 5;
      *(undefined8 *)
       ((long)&pcVar11->isa + _TtC8Playback37MIDICueItemMessageTableViewController::midiEvent) =
           uVar12;
      *(undefined1 *)((long)&pcVar11->isa + lVar6) = uVar3;
      *(undefined ***)
       ((long)&pcVar11->superclass + _TtC8Playback37MIDICueItemMessageTableViewController::delegate)
           = &PTR_PTR_100a42e78;
      _swift_unknownObjectUnownedInit();
      local_80.receiver = (ID)pcVar11;
      local_80.super_class = pcVar9;
      IVar10 = _objc_msgSendSuper2(&local_80,"initWithStyle:",0);
      self = _objc_msgSend(unaff_x20,"navigationController");
    }
  }
  else if (bVar2 == 2) {
    uVar12 = *(undefined8 *)(unaff_x20 + lVar6);
    uVar3 = *(undefined1 *)(unaff_x20 + lVar7);
    uVar4 = *(undefined2 *)(unaff_x20 + _TtC8Playback30MIDICueItemTableViewController::stagedValue);
    pcVar9 = (class_t *)0x0;
    FUN_1001e295c();
    pcVar11 = pcVar9;
    _objc_allocWithZone();
    puVar1 = (undefined2 *)
             ((long)&pcVar11->isa +
             _TtC8Playback36MIDICueItemValuePickerViewController::selectedEventValue);
    *puVar1 = 0;
    *(undefined1 *)(puVar1 + 1) = 1;
    *(undefined8 *)
     ((long)&pcVar11->isa + _TtC8Playback36MIDICueItemValuePickerViewController::midiEvent) = uVar12
    ;
    *(undefined1 *)
     ((long)&pcVar11->isa + _TtC8Playback36MIDICueItemValuePickerViewController::eventType) = uVar3;
    *puVar1 = uVar4;
    *(undefined1 *)(puVar1 + 1) = 0;
    *(undefined ***)
     ((long)&pcVar11->superclass + _TtC8Playback36MIDICueItemValuePickerViewController::delegate) =
         &PTR_PTR_100a42e68;
    _swift_unknownObjectUnownedInit();
    local_70.receiver = (ID)pcVar11;
    local_70.super_class = pcVar9;
    IVar10 = _objc_msgSendSuper2(&local_70,"initWithNibName:bundle:",0,0);
    self = _objc_msgSend(unaff_x20,"navigationController");
  }
  else {
    if (bVar2 != 3) {
      if (bVar2 != 6) {
        return puVar8;
      }
      IVar10 = unaff_x20;
      FUN_100837390();
      if (IVar10 == 0) {
        return (undefined *)0x0;
      }
      _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar10,1,0);
      return (undefined *)0x0;
    }
    uVar12 = *(undefined8 *)(unaff_x20 + lVar6);
    uVar3 = *(undefined1 *)(unaff_x20 + lVar7);
    uVar4 = *(undefined2 *)
             (unaff_x20 + _TtC8Playback30MIDICueItemTableViewController::stagedVelocity);
    pcVar9 = (class_t *)0x0;
    FUN_10011ad30();
    pcVar11 = pcVar9;
    _objc_allocWithZone();
    puVar5 = (undefined8 *)
             ((long)&pcVar11->isa +
             _TtC8Playback39MIDICueItemVelocityPickerViewController::velocities);
    puVar5[1] = 0x7f;
    *puVar5 = 0;
    puVar1 = (undefined2 *)
             ((long)&pcVar11->isa +
             _TtC8Playback39MIDICueItemVelocityPickerViewController::selectedVelocity);
    *puVar1 = 0;
    *(undefined1 *)(puVar1 + 1) = 1;
    *(undefined8 *)
     ((long)&pcVar11->isa + _TtC8Playback39MIDICueItemVelocityPickerViewController::midiEvent) =
         uVar12;
    *(undefined1 *)
     ((long)&pcVar11->isa + _TtC8Playback39MIDICueItemVelocityPickerViewController::eventType) =
         uVar3;
    *puVar1 = uVar4;
    *(undefined1 *)(puVar1 + 1) = 0;
    *(undefined ***)
     ((long)&pcVar11->superclass + _TtC8Playback39MIDICueItemVelocityPickerViewController::delegate)
         = &PTR_PTR_100a42e58;
    _swift_unknownObjectUnownedInit();
    local_60.receiver = (ID)pcVar11;
    local_60.super_class = pcVar9;
    IVar10 = _objc_msgSendSuper2(&local_60,"initWithNibName:bundle:",0,0);
    self = _objc_msgSend(unaff_x20,"navigationController");
  }
  if (self != 0) {
    _objc_msgSend(self,"pushViewController:animated:",IVar10,1);
  }
  return (undefined *)0x0;
}

// ==== 100419fa8 FUN_100419fa8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x00010043a39c) */

undefined1  [16] FUN_100419fa8(ulong param_1)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  bool in_ZR;
  bool bVar6;
  uint uVar7;
  undefined8 *puVar8;
  class_rw_t *pcVar9;
  class_rw_t *pcVar10;
  undefined *puVar11;
  ID IVar12;
  undefined *puVar13;
  undefined *puVar14;
  ID IVar15;
  long lVar16;
  ulong uVar17;
  char *pcVar18;
  undefined8 uVar19;
  code *pcVar20;
  char *pcVar21;
  undefined8 uVar22;
  class_t *unaff_x19;
  ulong uVar23;
  class_t *unaff_x20;
  undefined **ppuVar24;
  undefined8 uVar25;
  class_t *pcVar26;
  code *unaff_x21;
  long lVar27;
  class_t *unaff_x22;
  undefined8 *unaff_x23;
  long lVar28;
  long unaff_x24;
  long unaff_x25;
  long lVar29;
  class_t *unaff_x26;
  code *pcVar30;
  ID IVar31;
  long unaff_x27;
  undefined8 *puVar32;
  class_rw_t *unaff_x28;
  long unaff_x29;
  undefined8 unaff_x30;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  undefined1 auVar79 [16];
  undefined1 auVar80 [16];
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  undefined1 auVar88 [16];
  undefined1 auVar89 [16];
  undefined1 auVar90 [16];
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined1 auVar94 [16];
  undefined1 auVar95 [16];
  undefined1 auVar96 [16];
  undefined1 auVar97 [16];
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  undefined1 auVar102 [16];
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined1 auVar107 [16];
  undefined1 auVar108 [16];
  undefined1 auVar109 [16];
  undefined1 auVar110 [16];
  undefined1 auVar111 [16];
  undefined1 auVar112 [16];
  undefined1 auVar113 [16];
  undefined1 auVar114 [16];
  undefined1 auVar115 [16];
  class_t *in_stack_00000000;
  class_t *in_stack_00000008;
  class_t *in_stack_00000010;
  code *in_stack_00000018;
  class_t *in_stack_00000020;
  class_t *in_stack_00000028;
  long in_stack_00000030;
  undefined8 in_stack_00000038;
  long in_stack_00000050;
  
  pcVar18 = (char *)0xec000000736c6f63;
  puVar8 = (undefined8 *)0x6f746f7250495041;
  pcVar21 = (char *)(param_1 & 0xff);
  ppuVar24 = (undefined **)unaff_x20;
  pcVar26 = unaff_x22;
  switch(pcVar21) {
  default:
    pcVar21 = "Playback Remote Troubleshooting";
  case (char *)0xd2:
  case (char *)0xd6:
  case (char *)0xde:
  case (char *)0xe2:
    pcVar21 = pcVar21 + 0xba0;
LAB_10041a330:
    auVar49._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar49._0_8_ = 0xd000000000000011;
    return auVar49;
  case (char *)0x1:
    goto switchD_100419fe0_caseD_1;
  case (char *)0x2:
    pcVar18 = (char *)0xea0000000000746e;
    puVar8 = (undefined8 *)0x65746e6f43495041;
  case (char *)0x92:
    auVar48._8_8_ = pcVar18;
    auVar48._0_8_ = puVar8;
    return auVar48;
  case (char *)0x3:
    auVar51._8_8_ = 0xea00000000006e6f;
    auVar51._0_8_ = 0x6973736553495041;
    return auVar51;
  case (char *)0x4:
    auVar79._8_8_ = 0xeb00000000657461;
    auVar79._0_8_ = 0x67656c6544707041;
    return auVar79;
  case (char *)0x5:
    auVar57._8_8_ = 0xeb00000000656369;
    auVar57._0_8_ = 0x7665446f69647541;
    return auVar57;
  case (char *)0x6:
    auVar78._8_8_ = 0xeb00000000656e69;
    auVar78._0_8_ = 0x676e456f69647541;
    return auVar78;
  case (char *)0x7:
    auVar60._8_8_ = 0x80000001008f4b60;
    auVar60._0_8_ = 0xd000000000000018;
    return auVar60;
  case (char *)0x8:
    pcVar21 = "AudioEngineFinalMixer";
    goto LAB_10041aa14;
  case (char *)0x9:
  case (char *)0x96:
  case (char *)0xf6:
  case (char *)0xfa:
    pcVar18 = (char *)0x80000001008f4b20;
  case (char *)0xc2:
  case (char *)0xce:
  case (char *)0xf2:
    pcVar21 = (char *)0xb;
    goto switchD_100419fe0_caseD_ba;
  case (char *)0xa:
    auVar33._8_8_ = 0xee00656361667265;
    auVar33._0_8_ = 0x746e496f69647541;
    return auVar33;
  case (char *)0xb:
    pcVar21 = (char *)0x6369;
  case (char *)0xe8:
    auVar52._8_8_ = ((ulong)pcVar21 | 0xeb00000000650000) + 0x8f9;
    auVar52._0_8_ = 0x6174616d6f747541;
    return auVar52;
  case (char *)0xc:
    pcVar21 = "BufferedFilePlaybackAVAudioUnit";
    break;
  case (char *)0xd:
    auVar80._8_8_ = 0xe300000000000000;
    auVar80._0_8_ = 0x737542;
    return auVar80;
  case (char *)0xe:
    auVar81._8_8_ = 0xea00000000006c65;
    auVar81._0_8_ = 0x6e6e616843737542;
    return auVar81;
  case (char *)0xf:
    pcVar21 = "BusChannelAVAudioUnit";
    goto LAB_10041aa14;
  case (char *)0x10:
    uVar17 = 0x43737542;
    goto LAB_10041ab00;
  case (char *)0x11:
    pcVar21 = "BusSelectorTableViewController";
    goto LAB_10041aab4;
  case (char *)0x12:
    pcVar21 = "ClickAVAudioUnit";
    goto LAB_10041a7a8;
  case (char *)0x13:
    uVar17 = 0x63696c43;
    goto LAB_10041a4c8;
  case (char *)0x14:
    pcVar21 = "ClickSoundSelectionController";
    goto LAB_10041a8d4;
  case (char *)0x15:
    pcVar21 = "CloudSongSectionOptionsViewController";
    goto LAB_10041a9b4;
  case (char *)0x16:
    pcVar21 = "CloudSongSectionSave";
    goto LAB_10041aa70;
  case (char *)0x17:
    pcVar18 = (char *)0xee00676e69707061;
    puVar8 = (undefined8 *)0x6f72746e6f43;
  case (char *)0xdb:
    puVar8 = (undefined8 *)((ulong)puVar8 & 0xffffffffffff | 0x4d6c000000000000);
switchD_100419fe0_caseD_c3:
    auVar35._8_8_ = pcVar18;
    auVar35._0_8_ = puVar8;
    return auVar35;
  case (char *)0x18:
    pcVar18 = (char *)0xed00006863746546;
    puVar8 = (undefined8 *)0x6f43;
  case (char *)0x88:
    auVar41._0_8_ = (ulong)puVar8 & 0xffff | 0x6174614465720000;
    auVar41._8_8_ = pcVar18;
    return auVar41;
  case (char *)0x19:
    pcVar21 = "CustomContentManager";
    goto LAB_10041aa70;
  case (char *)0x1a:
    uVar17 = 0x61746144;
    goto LAB_10041a16c;
  case (char *)0x1b:
    uVar25 = 0x73746c7561666544;
    goto LAB_10041a44c;
  case (char *)0x1c:
    auVar96._8_8_ = 0xef72656c646e6148;
    auVar96._0_8_ = 0x64616f6c6e776f44;
    return auVar96;
  case (char *)0x1d:
    pcVar21 = "EmbeddedClientErrorTableViewController";
    goto LAB_10041ab44;
  case (char *)0x1e:
    uVar17 = 0x656c6946;
LAB_10041a16c:
    auVar40._0_8_ = uVar17 | 0x616e614d00000000;
    auVar40._8_8_ = 0xeb00000000726567;
    return auVar40;
  case (char *)0x1f:
    pcVar21 = "GeneralSettingsView";
    goto LAB_10041ab24;
  case (char *)0x20:
    pcVar21 = "GlobalTemplatesMainTableViewController";
LAB_10041ab44:
    auVar101._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar101._0_8_ = 0xd000000000000026;
    return auVar101;
  case (char *)0x21:
    pcVar21 = "GlobalTemplatesDetailTableViewController";
    goto LAB_10041abb8;
  case (char *)0x22:
    pcVar21 = "guideAVAudioUnit";
    goto LAB_10041a7a8;
  case (char *)0x23:
    uVar17 = 0x436564697567;
    goto LAB_10041ab9c;
  case (char *)0x24:
    auVar37._8_8_ = 0x80000001008f4910;
    auVar37._0_8_ = 0xd000000000000027;
    return auVar37;
  case (char *)0x25:
    pcVar21 = "LoginViewController";
    goto LAB_10041ab24;
  case (char *)0x26:
    pcVar21 = "mainViewController";
    goto LAB_10041a66c;
  case (char *)0x27:
    pcVar21 = "mainViewController+PlaybackRemote";
    goto LAB_10041a9e8;
  case (char *)0x28:
    auVar65._8_8_ = 0xe800000000000000;
    auVar65._0_8_ = 0x656c62617070614d;
    return auVar65;
  case (char *)0x29:
  case (char *)0xea:
  case (char *)0xee:
    uVar25 = 0x4d676e697070614d;
    goto LAB_10041a238;
  case (char *)0x2a:
    uVar17 = 0x63696c43;
    goto LAB_10041ab64;
  case (char *)0x2b:
    uVar17 = 0xeb0000000079654b;
    goto LAB_10041ab7c;
  case (char *)0x2c:
    pcVar21 = "MetadataKeyGroup";
    goto LAB_10041a7a8;
  case (char *)0x2d:
    uVar17 = 0xef6e6f6974636553;
    goto LAB_10041ab7c;
  case (char *)0x2e:
    pcVar21 = "MetadataTimeSignature";
    goto LAB_10041aa14;
  case (char *)0x2f:
    uVar17 = 0x63617254;
LAB_10041ab64:
    uVar17 = uVar17 | 0xed00006b00000000;
LAB_10041ab7c:
    auVar102._8_8_ = uVar17;
    auVar102._0_8_ = 0x617461646174654d;
    return auVar102;
  case (char *)0x30:
    auVar34._8_8_ = 0xe400000000000000;
    auVar34._0_8_ = 0x4944494d;
    return auVar34;
  case (char *)0x31:
    pcVar18 = (char *)0xe700000000000000;
  case (char *)0xf3:
    auVar36._8_8_ = pcVar18;
    auVar36._0_8_ = 0x7375424944494d;
    return auVar36;
  case (char *)0x32:
    pcVar21 = "MIDIClockAVAudioUnit";
    goto LAB_10041aa70;
  case (char *)0x33:
    auVar53._8_8_ = &DAT_e900000000000074;
    auVar53._0_8_ = 0x6e6576454944494d;
    return auVar53;
  case (char *)0x34:
    pcVar21 = "MIDIOutAVAudioUnit";
    goto LAB_10041a66c;
  case (char *)0x35:
    pcVar21 = "MIDISettingsTableViewController";
  case (char *)0x8e:
    break;
  case (char *)0x36:
    auVar98._8_8_ = &DAT_e500000000000000;
    auVar98._0_8_ = 0x726578694d;
    return auVar98;
  case (char *)0x37:
    pcVar21 = "MixerAVAudioUnit";
    goto LAB_10041a7a8;
  case (char *)0x38:
    pcVar21 = "Mixer Pad Panel VC";
LAB_10041a66c:
    auVar68._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar68._0_8_ = 0xd000000000000012;
    return auVar68;
  case (char *)0x39:
    auVar46._8_8_ = 0xef72656461466b63;
    auVar46._0_8_ = 0x617254726578694d;
    return auVar46;
  case (char *)0x3a:
    pcVar21 = "MixerTrackMuteButton";
LAB_10041aa70:
    auVar95._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar95._0_8_ = 0xd000000000000014;
    return auVar95;
  case (char *)0x3b:
    pcVar21 = "MixerViewController";
    goto LAB_10041ab24;
  case (char *)0x3c:
    auVar91._8_8_ = 0xe600000000000000;
    auVar91._0_8_ = 0x72657355544d;
    return auVar91;
  case (char *)0x3d:
    auVar43._8_8_ = 0xef7463656a624f64;
    auVar43._0_8_ = 0x6567616e614d534e;
    return auVar43;
  case (char *)0x3e:
    auVar38._8_8_ = 0xed0000676e697475;
    auVar38._0_8_ = 0x6f5274757074754f;
    return auVar38;
  case (char *)0x3f:
    auVar47._8_8_ = 0xe300000000000000;
    auVar47._0_8_ = 0x646150;
    return auVar47;
  case (char *)0x40:
    uVar17 = 0x43646150;
LAB_10041ab00:
    auVar99._0_8_ = uVar17 | 0x6e6e616800000000;
    auVar99._8_8_ = 0xef70756f72476c65;
    return auVar99;
  case (char *)0x41:
    uVar25 = 0x6579616c50646150;
    goto LAB_10041a89c;
  case (char *)0x42:
    pcVar18 = (char *)0x4356726f74;
  case (char *)0xc4:
    auVar42._8_8_ = (ulong)pcVar18 & 0xffffffffffff | 0xed00000000000000;
    auVar42._0_8_ = 0x63656c6553646150;
    return auVar42;
  case (char *)0x43:
    auVar71._8_8_ = 0xe800000000000000;
    auVar71._0_8_ = 0x6b63617254646150;
    return auVar71;
  case (char *)0x44:
    uVar25 = 0xee0065746f6d6552;
    goto LAB_10041a564;
  case (char *)0x45:
    uVar25 = 0xec000000636e7953;
LAB_10041a564:
    auVar61._8_8_ = uVar25;
    auVar61._0_8_ = 0x6b63616279616c50;
    return auVar61;
  case (char *)0x46:
    auVar72._8_8_ = 0xe700000000000000;
    auVar72._0_8_ = 0x736c61746e6552;
    return auVar72;
  case (char *)0x47:
    pcVar21 = "rentalTransferItemSelectorViewController";
    goto LAB_10041abb8;
  case (char *)0x48:
    pcVar21 = "RentalTransferOverviewViewController";
    goto LAB_10041a8ec;
  case (char *)0x49:
    pcVar21 = "RoutingSelectorViewController";
    goto LAB_10041a8d4;
  case (char *)0x4a:
    pcVar18 = (char *)0xed0000726567616e;
    puVar8 = (undefined8 *)0x7972746e6553;
  case (char *)0xdc:
    auVar50._0_8_ = (ulong)puVar8 & 0xffffffffffff | 0x614d000000000000;
    auVar50._8_8_ = pcVar18;
    return auVar50;
  case (char *)0x4b:
    uVar25 = 0x65636e6575716553;
LAB_10041a89c:
    auVar83._8_8_ = 0xe900000000000072;
    auVar83._0_8_ = uVar25;
    return auVar83;
  case (char *)0x4c:
    auVar45._8_8_ = 0xe700000000000000;
    auVar45._0_8_ = 0x7473696c746553;
    return auVar45;
  case (char *)0x4d:
    pcVar21 = "SetlistsDetailTableViewController";
    goto LAB_10041a9e8;
  case (char *)0x4e:
    auVar89._8_8_ = 0xef6c6c65436d6574;
    auVar89._0_8_ = 0x497473696c746553;
    return auVar89;
  case (char *)0x4f:
    uVar25 = 0x4d7473696c746553;
LAB_10041a238:
    auVar44._8_8_ = 0xee00726567616e61;
    auVar44._0_8_ = uVar25;
    return auVar44;
  case (char *)0x50:
    pcVar21 = "SetlistViewController";
LAB_10041aa14:
    pcVar18 = (char *)((ulong)(pcVar21 + -0x20) | 0x8000000000000000);
    pcVar21 = (char *)0x5;
LAB_10041aa20:
    auVar93._0_8_ = (ulong)pcVar21 | 0xd000000000000010;
    auVar93._8_8_ = pcVar18;
    return auVar93;
  case (char *)0x51:
    pcVar21 = "SetlistBaseTableViewController";
    goto LAB_10041aab4;
  case (char *)0x52:
    pcVar21 = "SetlistMainTableViewController";
LAB_10041aab4:
    auVar97._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar97._0_8_ = 0xd00000000000001e;
    return auVar97;
  case (char *)0x53:
    auVar54._8_8_ = 0x80000001008f46d0;
    auVar54._0_8_ = 0xd000000000000023;
    return auVar54;
  case (char *)0x54:
    pcVar21 = "SetlistsOpenTableViewController";
    break;
  case (char *)0x55:
    pcVar21 = "SetlistSongDetailsTableViewCell";
    break;
  case (char *)0x56:
    auVar94._8_8_ = 0xe800000000000000;
    auVar94._0_8_ = 0x73676e6974746553;
    return auVar94;
  case (char *)0x57:
    pcVar21 = "SettingsProtocol";
    goto LAB_10041a7a8;
  case (char *)0x58:
    pcVar21 = "SineWaveAudioUnit";
    goto LAB_10041a330;
  case (char *)0x59:
    auVar39._8_8_ = 0xe400000000000000;
    auVar39._0_8_ = 0x676e6f53;
    return auVar39;
  case (char *)0x5a:
    auVar84._8_8_ = 0xef746e656d65676e;
    auVar84._0_8_ = 0x61727241676e6f53;
    return auVar84;
  case (char *)0x5b:
    pcVar21 = "SongChannelGroup";
    goto LAB_10041a7a8;
  case (char *)0x5c:
    auVar56._8_8_ = 0xeb00000000736b63;
    auVar56._0_8_ = 0x696c432b676e6f53;
    return auVar56;
  case (char *)0x5d:
    pcVar21 = "SongDownloadHandler";
LAB_10041ab24:
    auVar100._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar100._0_8_ = 0xd000000000000013;
    return auVar100;
  case (char *)0x5e:
    auVar87._8_8_ = 0xe900000000000065;
    auVar87._0_8_ = 0x726e6547676e6f53;
    return auVar87;
  case (char *)0x5f:
    pcVar21 = "SongMap.MIDIEvent";
    goto LAB_10041a330;
  case (char *)0x60:
    pcVar21 = "SongMenuProtocol";
LAB_10041a7a8:
    auVar77._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar77._0_8_ = 0xd000000000000010;
    return auVar77;
  case (char *)0x61:
    pcVar21 = "SongMenuRentalActiveViewController";
    goto LAB_10041a90c;
  case (char *)0x62:
    pcVar21 = "SongMenuAddSongViewController";
LAB_10041a8d4:
    pcVar18 = (char *)((ulong)(pcVar21 + -0x20) | 0x8000000000000000);
    pcVar21 = (char *)0xd;
    goto LAB_10041aa20;
  case (char *)0x63:
    pcVar21 = "SongMenuArrangementsViewController";
    goto LAB_10041a90c;
  case (char *)0x64:
    pcVar21 = "SongMenuClickPadDetailViewController";
    goto LAB_10041a8ec;
  case (char *)0x65:
    auVar66._8_8_ = 0x80000001008f4510;
    auVar66._0_8_ = 0xd000000000000020;
    return auVar66;
  case (char *)0x66:
    pcVar21 = "SongMenuFilterSelector";
    goto LAB_10041a774;
  case (char *)0x67:
    pcVar21 = "SongMenuItemViewController";
    goto LAB_10041a92c;
  case (char *)0x68:
    pcVar21 = "SongMenuMIDIBankEditViewController";
    goto LAB_10041a90c;
  case (char *)0x69:
    pcVar21 = "SongMenuMTCompleteListViewController";
    goto LAB_10041a8ec;
  case (char *)0x6a:
    pcVar21 = "SongMenuMultiItemViewController";
    break;
  case (char *)0x6b:
    pcVar21 = "SongMenuMyLibraryViewController";
    break;
  case (char *)0x6c:
    auVar59._8_8_ = 0x80000001008f4400;
    auVar59._0_8_ = 0xd00000000000002c;
    return auVar59;
  case (char *)0x6d:
    pcVar21 = "SongMenuProductionItemViewController";
LAB_10041a8ec:
    auVar85._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar85._0_8_ = 0xd000000000000024;
    return auVar85;
  case (char *)0x6e:
    pcVar21 = "SongMenuRentalTracksViewController";
LAB_10041a90c:
    auVar86._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar86._0_8_ = 0xd000000000000022;
    return auVar86;
  case (char *)0x6f:
    auVar73._8_8_ = 0xe900000000000049;
    auVar73._0_8_ = 0x44494d2b676e6f53;
    return auVar73;
  case (char *)0x70:
    auVar69._8_8_ = 0xeb000000006e6f69;
    auVar69._0_8_ = 0x74636553676e6f53;
    return auVar69;
  case (char *)0x71:
    pcVar21 = "StackMenuViewController";
    goto LAB_10041a874;
  case (char *)0x72:
    pcVar21 = "StackMenuCoreDataListTableViewController";
LAB_10041abb8:
    auVar104._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar104._0_8_ = 0xd000000000000028;
    return auVar104;
  case (char *)0x73:
    auVar67._8_8_ = 0xed0000736e6f6974;
    auVar67._0_8_ = 0x7069726373627553;
    return auVar67;
  case (char *)0x74:
    pcVar21 = "SupportEntryViewController";
    goto LAB_10041a92c;
  case (char *)0x75:
    pcVar21 = "TiledImageDownloadStatusTableViewCell";
LAB_10041a9b4:
    auVar90._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar90._0_8_ = 0xd000000000000025;
    return auVar90;
  case (char *)0x76:
    pcVar21 = "TimePitchProcessingManager";
LAB_10041a92c:
    pcVar18 = (char *)((ulong)(pcVar21 + -0x20) | 0x8000000000000000);
    pcVar21 = (char *)0xa;
    goto LAB_10041aa20;
  case (char *)0x77:
    pcVar21 = "TracksBusesSettingsViewController";
    goto LAB_10041a9e8;
  case (char *)0x78:
    uVar17 = 0x63617254;
LAB_10041a4c8:
    uVar17 = uVar17 | 0x436b00000000;
LAB_10041ab9c:
    auVar103._0_8_ = uVar17 | 0x6168000000000000;
    auVar103._8_8_ = 0xec0000006c656e6e;
    return auVar103;
  case (char *)0x79:
    pcVar21 = "TransportViewController";
LAB_10041a874:
    auVar82._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar82._0_8_ = 0xd000000000000017;
    return auVar82;
  case (char *)0x7a:
    pcVar21 = "LandscapeAlertController+Alerts";
    break;
  case (char *)0x7b:
    auVar58._8_8_ = 0xed00006e6f697461;
    auVar58._0_8_ = 0x63696c7070414955;
    return auVar58;
  case (char *)0x7c:
    auVar75._8_8_ = 0xe700000000000000;
    auVar75._0_8_ = 0x6567616d494955;
    return auVar75;
  case (char *)0x7d:
    auVar62._8_8_ = 0xeb00000000776569;
    auVar62._0_8_ = 0x566567616d494955;
    return auVar62;
  case (char *)0x7e:
    auVar74._8_8_ = 0xe400000000000000;
    auVar74._0_8_ = 0x72657355;
    return auVar74;
  case (char *)0x7f:
    auVar70._8_8_ = 0xec00000064697247;
    auVar70._0_8_ = 0x6d726f6665766157;
    return auVar70;
  case (char *)0x80:
    uVar25 = 0x6d726f6665766157;
LAB_10041a44c:
    auVar55._8_8_ = 0xef726567616e614d;
    auVar55._0_8_ = uVar25;
    return auVar55;
  case (char *)0x81:
    pcVar21 = "WaveformViewController";
LAB_10041a774:
    auVar76._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar76._0_8_ = 0xd000000000000016;
    return auVar76;
  case (char *)0x82:
    pcVar21 = "WaveformViewController+CueEditing";
LAB_10041a9e8:
    auVar92._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
    auVar92._0_8_ = 0xd000000000000021;
    return auVar92;
  case (char *)0x83:
    auVar63._8_8_ = 0xe800000000000000;
    auVar63._0_8_ = 0x746e65696c435357;
    return auVar63;
  case (char *)0x84:
    pcVar18 = (char *)0xe800000000000000;
    puVar8 = (undefined8 *)0x7265767265535357;
    goto switchD_100419fe0_caseD_1;
  case (char *)0x85:
    _swift_getErrorValue();
    pcVar10 = *(class_rw_t **)(unaff_x29 + -0xb0);
    pcVar26 = *(class_t **)(unaff_x29 + -0xa8);
    FUN_1002c2c2c();
    unaff_x22[1].cache = (Cache)PTR___sSSN_100a1dce0;
    pcVar9 = pcVar10;
    FUN_100026528();
    unaff_x22[1].vtable = (Implementation)pcVar9;
    unaff_x22->data = pcVar10;
    unaff_x22[1].isa = pcVar26;
    uVar25 = 0x26;
    FUN_10041ac94();
    _swift_setDeallocating();
    FUN_100023468(&unaff_x22->data);
    _swift_errorRelease();
    auVar105._8_8_ = uVar25;
    auVar105._0_8_ = unaff_x19;
    return auVar105;
  case (char *)0x86:
    goto switchD_100419fe0_caseD_86;
  case (char *)0x87:
    return ZEXT816(0xec000000736c6f63) << 0x40;
  case (char *)0x9e:
    goto switchD_100419fe0_caseD_9e;
  case (char *)0x9f:
    FUN_100435f80((uint)unaff_x19 & 1);
    _swift_bridgeObjectRelease();
    _swift_bridgeObjectRelease();
    FUN_100023468(unaff_x29 + -0xa0);
    lVar28 = unaff_x29 + -0x78;
    FUN_100023468(lVar28);
    auVar113._8_8_ = unaff_x23;
    auVar113._0_8_ = lVar28;
    return auVar113;
  case (char *)0xa0:
    return ZEXT816(0xec000000736c6f63) << 0x40;
  case (char *)0xa1:
    goto switchD_100419fe0_caseD_a1;
  case (char *)0xa6:
switchD_100419fe0_caseD_a6:
    pcVar18 = "setImage:";
    _objc_msgSend((ID)puVar8,"setImage:",0);
    goto LAB_100435d4c;
  case (char *)0xa7:
    unaff_x21 = (code *)pcVar18;
switchD_100419fe0_caseD_86:
    FUN_100023468(unaff_x29 + -0x80);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease(unaff_x21);
    _objc_msgSend((ID)unaff_x22,(SEL)unaff_x23[0x10a],unaff_x20);
    IVar15 = (long)&(unaff_x19[0x34].data)->flags + *(long *)(unaff_x29 + -0xb8);
    _swift_unknownObjectWeakLoadStrong();
    if (IVar15 != 0) {
      FUN_10003b4b4();
      lVar28 = *(long *)(unaff_x29 + -0x68);
      if (lVar28 == 0) {
        FUN_100023be4(unaff_x29 + -0x80,&DAT_100af5d38);
        lVar28 = 0;
      }
      else {
        lVar16 = *(long *)(unaff_x29 + -0x60);
        FUN_100023444(unaff_x29 + -0x80,lVar28);
        (**(code **)(lVar16 + 0x18))(lVar28);
        FUN_100023468(unaff_x29 + -0x80);
        if (lVar16 == 0) {
          lVar28 = 0;
        }
        else {
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(lVar28,lVar16);
          _swift_bridgeObjectRelease(lVar16);
        }
      }
      _objc_msgSend(IVar15,(SEL)unaff_x23[0x10a],lVar28);
    }
    FUN_10003b4b4(unaff_x26,unaff_x29 + -0x80,&DAT_100af5d38);
    lVar28 = *(long *)(unaff_x29 + -0x68);
    if (lVar28 == 0) {
LAB_100434158:
      FUN_100023be4(unaff_x29 + -0x80,&DAT_100af5d38);
    }
    else {
      lVar16 = *(long *)(unaff_x29 + -0x60);
      FUN_100023444(unaff_x29 + -0x80,lVar28);
      (**(code **)(lVar16 + 0x10))(lVar28,lVar16);
      FUN_100023468(unaff_x29 + -0x80);
      FUN_10003b4b4(unaff_x26,unaff_x29 + -0x80,&DAT_100af5d38);
      lVar27 = *(long *)(unaff_x29 + -0x68);
      if (lVar27 == 0) {
        _swift_bridgeObjectRelease(lVar16);
        goto LAB_100434158;
      }
      *(long *)(unaff_x29 + -0x120) = unaff_x25;
      *(long *)(unaff_x29 + -0x118) = unaff_x24;
      lVar29 = *(long *)(unaff_x29 + -0x60);
      FUN_100023444(unaff_x29 + -0x80,lVar27);
      (**(code **)(lVar29 + 0x18))(lVar27);
      FUN_100023468(unaff_x29 + -0x80);
      if (lVar29 != 0) {
        bVar6 = (*(ulong *)(unaff_x29 + -0xc0) & 1) == 0;
        pcVar21 = "Default Pad title";
        uVar25 = 0xd00000000000001a;
        if (bVar6) {
          pcVar21 = "SongMenuSongCellArtistLabel";
          uVar25 = 0xd000000000000024;
        }
        pcVar18 = "SongMenuSongCellTitleLabel";
        uVar22 = 0xd00000000000001b;
        if (bVar6) {
          pcVar18 = "ntItemCellTitleLabel";
          uVar22 = 0xd000000000000027;
        }
        FUN_10043641c(lVar28,lVar16,lVar27,lVar29,uVar25,(ulong)pcVar21 | 0x8000000000000000,uVar22,
                      (ulong)pcVar18 | 0x8000000000000000);
        _swift_bridgeObjectRelease(lVar16);
        _swift_bridgeObjectRelease((ulong)pcVar18 | 0x8000000000000000);
        _swift_bridgeObjectRelease((ulong)pcVar21 | 0x8000000000000000);
        lVar16 = lVar29;
      }
      _swift_bridgeObjectRelease(lVar16);
      unaff_x24 = *(long *)(unaff_x29 + -0x118);
      unaff_x25 = *(long *)(unaff_x29 + -0x120);
    }
    FUN_10003b4b4(unaff_x26,unaff_x29 + -0x80,&DAT_100af5d38);
    unaff_x26 = (class_t *)&objc::class_t::_TtC8Playback24PitchTempoProcessingView.cache;
    uVar25 = *(undefined8 *)(unaff_x29 + -200);
    if (*(long *)(unaff_x29 + -0x68) == 0) {
LAB_100434880:
      lVar28 = *(long *)(unaff_x29 + -0xb8) +
               _TtC8Playback24ContentItemTableViewCell::downloadStatusButton;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar28 != 0) {
        *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 4;
        FUN_100297e9c(4);
      }
      lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
      lVar16 = *(long *)(unaff_x29 + -0xb8);
      *(undefined8 *)(lVar16 + _TtC8Playback24ContentItemTableViewCell::artwork) = 0;
      IVar15 = lVar16 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar15 != 0) {
        lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
        if ((lVar28 == 0) && (lVar28 = DAT_100b77470, DAT_100adfb28 != -1)) {
          _swift_once(&DAT_100adfb28,FUN_100579138);
          lVar28 = DAT_100b77470;
        }
        _objc_msgSend(IVar15,"setImage:",lVar28);
      }
      goto LAB_100434bc8;
    }
    FUN_10003b4b4(unaff_x29 + -0x80,unaff_x29 + -0xa8,&DAT_100af5d38);
    puVar13 = &DAT_100af5d40;
    FUN_100021774(&DAT_100af5d40);
    pcVar10 = unaff_x28;
    _swift_dynamicCast(unaff_x28,unaff_x29 + -0xa8,puVar13,unaff_x27,0);
    if ((int)pcVar10 == 0) {
      lVar28 = unaff_x25;
      _swift_dynamicCast(unaff_x25,unaff_x29 + -0xa8,puVar13,*(undefined8 *)(unaff_x29 + -0xe0),0);
      if ((int)lVar28 == 0) {
        uVar22 = uVar25;
        _swift_dynamicCast(uVar25,unaff_x29 + -0xa8,puVar13,*(undefined8 *)(unaff_x29 + -0xe8),0);
        if ((int)uVar22 == 0) {
          uVar25 = 0;
          FUN_1001cc624(0);
          lVar28 = unaff_x29 + -0xb0;
          _swift_dynamicCast(lVar28,unaff_x29 + -0xa8,puVar13,uVar25,0);
          if ((int)lVar28 == 0) {
            uVar25 = 0;
            FUN_10034293c(0);
            lVar28 = unaff_x29 + -0xb0;
            _swift_dynamicCast(lVar28,unaff_x29 + -0xa8,puVar13,uVar25,0);
            if ((int)lVar28 == 0) {
              FUN_100023468(unaff_x29 + -0xa8);
              goto LAB_100434880;
            }
            IVar15 = *(ID *)(unaff_x29 + -0xb0);
            lVar28 = *(long *)(unaff_x29 + -0xb8) +
                     _TtC8Playback24ContentItemTableViewCell::downloadStatusButton;
            _swift_unknownObjectWeakLoadStrong();
            if (lVar28 != 0) {
              *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 4;
              FUN_100297e9c(4);
            }
            pcVar21 = "artworkData";
            IVar15 = _objc_msgSend(IVar15,"artworkData");
            if (IVar15 == 0) {
              IVar31 = 0;
            }
            else {
              __s10Foundation4DataV36_unconditionallyBridgeFromObjectiveCyACSo6NSDataCSgFZ();
              puVar13 = &_OBJC_CLASS___UIImage;
              _objc_allocWithZone();
              IVar31 = IVar15;
              __s10Foundation4DataV19_bridgeToObjectiveCSo6NSDataCyF(IVar15,pcVar21);
              IVar31 = _objc_msgSend((ID)puVar13,"initWithData:scale:",0x4000000000000000,IVar31);
              FUN_100039b24(IVar15,pcVar21);
            }
            lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
            lVar16 = *(long *)(unaff_x29 + -0xb8);
            *(ID *)(lVar16 + _TtC8Playback24ContentItemTableViewCell::artwork) = IVar31;
            IVar15 = lVar16 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
            _swift_unknownObjectWeakLoadStrong();
            if (IVar15 == 0) goto LAB_100434bc0;
            lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
            if (lVar28 == 0) {
              lVar16 = DAT_100b77470;
              if (DAT_100adfb28 != -1) {
                _swift_once(&DAT_100adfb28,FUN_100579138);
                lVar16 = DAT_100b77470;
              }
            }
            else {
LAB_100435018:
              lVar16 = lVar28;
            }
LAB_100435058:
            _objc_msgSend(IVar15,"setImage:",lVar16);
          }
          else {
            unaff_x21 = *(code **)(unaff_x29 + -0xb0);
            pcVar26 = (class_t *)_objc_msgSend((ID)unaff_x21,"padDownloadHandler");
            if (pcVar26 == (class_t *)0x0) {
              FUN_1001c5484();
              unaff_x22 = (class_t *)
                          (*(long *)(unaff_x29 + -0xb8) +
                          _TtC8Playback24ContentItemTableViewCell::downloadStatusButton);
              _swift_unknownObjectWeakLoadStrong();
              if (((ulong)pcVar26 & 1) == 0) {
                if (unaff_x22 != (class_t *)0x0) {
switchD_100419fe0_caseD_a1:
                  *(undefined1 *)
                   ((long)&unaff_x22->isa + _TtC8Playback20DownloadStatusButton::status) = 0;
                  uVar25 = 0;
                  goto LAB_100434d84;
                }
              }
              else if (unaff_x22 != (class_t *)0x0) {
                *(undefined1 *)((long)&unaff_x22->isa + _TtC8Playback20DownloadStatusButton::status)
                     = 4;
                uVar25 = 4;
LAB_100434d84:
                FUN_100297e9c(uVar25);
                goto LAB_100434d8c;
              }
            }
            else {
              unaff_x23 = (undefined8 *)_objc_msgSend((ID)pcVar26,"downloadStateID");
              FUN_100246954();
switchD_100419fe0_caseD_b1:
              lVar28 = (long)&(unaff_x26[0x35].superclass)->isa + *(long *)(unaff_x29 + -0xb8);
              _swift_unknownObjectWeakLoadStrong();
              uVar7 = (uint)unaff_x23 & 0xff;
              if (uVar7 == 7) {
                if (lVar28 != 0) {
                  *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 4;
                  uVar25 = 4;
LAB_100434cf0:
                  FUN_100297e9c(uVar25);
                }
              }
              else if (uVar7 == 5) {
                if (lVar28 != 0) {
                  *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 3;
                  FUN_100297e9c(3);
                }
                puVar8 = (undefined8 *)
                         (*(long *)(unaff_x29 + -0xb8) +
                         _TtC8Playback24ContentItemTableViewCell::downloadHandler);
                unaff_x19 = (class_t *)*puVar8;
                *puVar8 = pcVar26;
                puVar8[1] = &PTR_PTR_100a2c538;
switchD_100419fe0_caseD_ad:
                _swift_unknownObjectRelease(unaff_x19);
                FUN_1004368e8();
              }
              else if (lVar28 != 0) {
                *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 0;
                uVar25 = 0;
                goto LAB_100434cf0;
              }
LAB_100434d8c:
              unaff_x22 = (class_t *)0x0;
            }
            FUN_1001c976c();
            lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
            if (unaff_x22 == (class_t *)0x0) {
              FUN_1001c9eec();
              if (unaff_x22 == (class_t *)0x0) {
                if (DAT_100adfb28 != -1) {
                  puVar8 = &DAT_100adfb28;
                  pcVar18 = (char *)FUN_100579138;
switchD_100419fe0_caseD_b6:
                  _swift_once(puVar8,pcVar18);
                }
                lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
                lVar16 = *(long *)(unaff_x29 + -0xb8);
                *(long *)(lVar16 + _TtC8Playback24ContentItemTableViewCell::artwork) = DAT_100b77470
                ;
                IVar15 = lVar16 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
                _swift_unknownObjectWeakLoadStrong();
                if (IVar15 != 0) {
                  lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
                  lVar16 = DAT_100b77470;
                  if (lVar28 != 0) goto LAB_100435018;
                  goto LAB_100435058;
                }
              }
              else {
                puVar13 = &DAT_100a48738;
                _swift_allocObject(&DAT_100a48738,0x18,7);
                *(code **)(puVar13 + 0x10) = unaff_x21;
                lVar28 = *(long *)(unaff_x29 + -0xb8) +
                         _TtC8Playback24ContentItemTableViewCell::artworkImageView;
                _swift_unknownObjectWeakLoadStrong();
                if (lVar28 != 0) {
                  if (DAT_100adfb28 != -1) {
                    _swift_once(&DAT_100adfb28,FUN_100579138);
                  }
                  lVar28 = DAT_100b77470;
                  puVar14 = &DAT_100a48760;
                  _swift_allocObject(&DAT_100a48760,0x18,7);
                  _swift_unknownObjectWeakInit(puVar14 + 0x10,*(undefined8 *)(unaff_x29 + -0xb8));
                  puVar11 = &DAT_100a48788;
                  _swift_allocObject(&DAT_100a48788,0x28,7);
                  *(undefined **)(puVar11 + 0x10) = puVar14;
                  *(code **)(puVar11 + 0x18) = FUN_100437a8c;
                  *(undefined **)(puVar11 + 0x20) = puVar13;
                  _swift_retain(puVar14);
                  _swift_retain(puVar13);
                  FUN_1001c01d4(unaff_x22,lVar28,1,FUN_100437ae4,puVar11);
                  _swift_bridgeObjectRelease(unaff_x22);
                  _swift_release(puVar13);
                  _swift_release(puVar14);
                  _swift_release(puVar11);
                  goto LAB_100434fac;
                }
                _swift_bridgeObjectRelease(unaff_x22);
                _swift_release(puVar13);
              }
            }
            else {
              lVar16 = *(long *)(unaff_x29 + -0xb8);
              *(class_t **)(lVar16 + _TtC8Playback24ContentItemTableViewCell::artwork) = unaff_x22;
              IVar15 = lVar16 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
              _swift_unknownObjectWeakLoadStrong();
              if (IVar15 != 0) {
                lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
                if ((lVar28 == 0) && (lVar28 = DAT_100b77470, DAT_100adfb28 != -1)) {
                  _swift_once(&DAT_100adfb28,FUN_100579138);
                  lVar28 = DAT_100b77470;
                }
                _objc_msgSend(IVar15,"setImage:",lVar28);
              }
            }
          }
        }
        else {
          FUN_100023340(uVar25,unaff_x24,FUN_1004ef0e8);
          lVar28 = *(long *)(unaff_x29 + -0xb8) +
                   _TtC8Playback24ContentItemTableViewCell::downloadStatusButton;
          _swift_unknownObjectWeakLoadStrong();
          if (lVar28 != 0) {
            *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 0;
            FUN_100297e9c(0);
          }
          lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
          lVar16 = *(long *)(unaff_x24 + *(int *)(*(long *)(unaff_x29 + -0xe8) + 0x20));
          if (lVar16 != 0) {
            lVar27 = *(long *)(unaff_x29 + -0xb8);
            *(long *)(lVar27 + _TtC8Playback24ContentItemTableViewCell::artwork) = lVar16;
            unaff_x21 = (code *)(lVar27 + _TtC8Playback24ContentItemTableViewCell::artworkImageView)
            ;
            _swift_unknownObjectWeakLoadStrong();
            if (unaff_x21 != (code *)0x0) {
              lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
              if ((lVar28 == 0) && (lVar28 = DAT_100b77470, DAT_100adfb28 != -1)) {
switchD_100419fe0_caseD_9e:
                _swift_once(&DAT_100adfb28,FUN_100579138);
                lVar28 = DAT_100b77470;
              }
              _objc_msgSend((ID)unaff_x21,"setImage:",lVar28);
            }
            pcVar30 = FUN_1004ef0e8;
            goto LAB_100434bb8;
          }
          uVar19 = *(undefined8 *)(unaff_x29 + -0x110);
          FUN_10003b4b4(unaff_x24 + *(int *)(*(long *)(unaff_x29 + -0xe8) + 0x1c),uVar19,
                        &DAT_100af56b0);
          lVar28 = *(long *)(unaff_x29 + -0x100);
          uVar25 = *(undefined8 *)(unaff_x29 + -0xf8);
          uVar22 = uVar19;
          (**(code **)(lVar28 + 0x30))(uVar19,1,uVar25);
          if ((int)uVar22 == 1) {
            FUN_1000233c8(unaff_x24,FUN_1004ef0e8);
            FUN_100023be4(uVar19,&DAT_100af56b0);
            goto LAB_100434bc0;
          }
          *(long *)(unaff_x29 + -0x118) = unaff_x24;
          uVar22 = *(undefined8 *)(unaff_x29 + -0x108);
          (**(code **)(lVar28 + 0x20))(uVar22,uVar19,uVar25);
          puVar13 = &DAT_100af9eb8;
          FUN_100021774();
          puVar14 = &DAT_100af9ec0;
          FUN_100021774();
          uVar17 = (ulong)*(byte *)(*(long *)(puVar14 + -8) + 0x50);
          uVar23 = uVar17 + 0x20 & (uVar17 ^ 0xffffffffffffffff);
          _swift_allocObject(puVar13,uVar23 + *(long *)(*(long *)(puVar14 + -8) + 0x48),uVar17 | 7);
          *(undefined8 *)(puVar13 + 0x18) = 2;
          *(undefined8 *)(puVar13 + 0x10) = 1;
          puVar11 = puVar13 + uVar23;
          iVar1 = *(int *)(puVar14 + 0x30);
          *puVar11 = 1;
          (**(code **)(lVar28 + 0x10))(puVar11 + iVar1,uVar22,uVar25);
          puVar14 = puVar13;
          FUN_10079c790(puVar13);
          _swift_setDeallocating(puVar13);
          FUN_100023be4(puVar11,&DAT_100af9ec0);
          _swift_deallocClassInstance(puVar13,0x20,7);
          lVar16 = *(long *)(unaff_x29 + -0xb8) +
                   _TtC8Playback24ContentItemTableViewCell::artworkImageView;
          _swift_unknownObjectWeakLoadStrong();
          if (lVar16 == 0) {
            _swift_bridgeObjectRelease(puVar14);
          }
          else {
            if (DAT_100adfb28 != -1) {
              _swift_once(&DAT_100adfb28,FUN_100579138);
            }
            lVar28 = DAT_100b77470;
            puVar13 = &DAT_100a48760;
            _swift_allocObject(&DAT_100a48760,0x18,7);
            _swift_unknownObjectWeakInit(puVar13 + 0x10,*(undefined8 *)(unaff_x29 + -0xb8));
            puVar11 = &DAT_100a487b0;
            _swift_allocObject(&DAT_100a487b0,0x28,7);
            *(undefined8 *)(puVar11 + 0x18) = 0;
            *(undefined8 *)(puVar11 + 0x20) = 0;
            *(undefined **)(puVar11 + 0x10) = puVar13;
            _swift_retain(puVar13);
            FUN_1001c01d4(puVar14,lVar28,1,thunk_FUN_100437ae4,puVar11);
            _swift_bridgeObjectRelease(puVar14);
            _swift_release(puVar13);
            _swift_release(puVar11);
            lVar28 = *(long *)(unaff_x29 + -0x100);
            uVar25 = *(undefined8 *)(unaff_x29 + -0xf8);
          }
          (**(code **)(lVar28 + 8))(*(undefined8 *)(unaff_x29 + -0x108),uVar25);
          FUN_1000233c8(*(undefined8 *)(unaff_x29 + -0x118),FUN_1004ef0e8);
LAB_100434fac:
          unaff_x26 = (class_t *)&objc::class_t::_TtC8Playback24PitchTempoProcessingView.cache;
        }
      }
      else {
        unaff_x24 = *(long *)(unaff_x29 + -0xf0);
        FUN_100023340(unaff_x25,unaff_x24,FUN_10068e908);
        lVar28 = *(long *)(unaff_x29 + -0xb8) +
                 _TtC8Playback24ContentItemTableViewCell::downloadStatusButton;
        _swift_unknownObjectWeakLoadStrong();
        if (lVar28 != 0) {
          *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 0;
          FUN_100297e9c(0);
        }
        lVar28 = _TtC8Playback24ContentItemTableViewCell::artwork;
        lVar16 = *(long *)(unaff_x24 + *(int *)(*(long *)(unaff_x29 + -0xe0) + 0xc0));
        if (lVar16 == 0) {
          FUN_100691710();
          if (lVar16 != 0) {
            lVar28 = *(long *)(unaff_x29 + -0xb8) +
                     _TtC8Playback24ContentItemTableViewCell::artworkImageView;
            _swift_unknownObjectWeakLoadStrong();
            if (lVar28 == 0) {
              _swift_bridgeObjectRelease(lVar16);
            }
            else {
              if (DAT_100adfb28 != -1) {
                _swift_once(&DAT_100adfb28,FUN_100579138);
              }
              lVar28 = DAT_100b77470;
              puVar13 = &DAT_100a48760;
              _swift_allocObject(&DAT_100a48760,0x18,7);
              _swift_unknownObjectWeakInit(puVar13 + 0x10,*(undefined8 *)(unaff_x29 + -0xb8));
              puVar14 = &DAT_100a487d8;
              _swift_allocObject(&DAT_100a487d8,0x28,7);
              *(undefined8 *)(puVar14 + 0x18) = 0;
              *(undefined8 *)(puVar14 + 0x20) = 0;
              *(undefined **)(puVar14 + 0x10) = puVar13;
              _swift_retain(puVar13);
              FUN_1001c01d4(lVar16,lVar28,1,thunk_FUN_100437ae4,puVar14);
              _swift_bridgeObjectRelease(lVar16);
              _swift_release(puVar13);
              _swift_release(puVar14);
              unaff_x24 = *(long *)(unaff_x29 + -0xf0);
            }
          }
        }
        else {
          lVar27 = *(long *)(unaff_x29 + -0xb8);
          *(long *)(lVar27 + _TtC8Playback24ContentItemTableViewCell::artwork) = lVar16;
          IVar15 = lVar27 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
          _swift_unknownObjectWeakLoadStrong();
          if (IVar15 != 0) {
            lVar28 = *(long *)(*(long *)(unaff_x29 + -0xb8) + lVar28);
            if ((lVar28 == 0) && (lVar28 = DAT_100b77470, DAT_100adfb28 != -1)) {
              _swift_once(&DAT_100adfb28,FUN_100579138);
              lVar28 = DAT_100b77470;
            }
            _objc_msgSend(IVar15,"setImage:",lVar28);
          }
        }
        pcVar30 = FUN_10068e908;
LAB_100434bb8:
        FUN_1000233c8(unaff_x24,pcVar30);
      }
    }
    else {
      uVar25 = *(undefined8 *)(unaff_x29 + -0xd8);
      FUN_100023340(unaff_x28,uVar25,FUN_1001436fc);
      lVar28 = *(long *)(unaff_x29 + -0xb8) +
               _TtC8Playback24ContentItemTableViewCell::downloadStatusButton;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar28 != 0) {
        *(undefined1 *)(lVar28 + _TtC8Playback20DownloadStatusButton::status) = 0;
        FUN_100297e9c(0);
      }
      uVar22 = 0;
      FUN_100095dcc();
      lVar28 = *(long *)(unaff_x29 + -0xb8) +
               _TtC8Playback24ContentItemTableViewCell::artworkImageView;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar28 == 0) {
        _swift_bridgeObjectRelease(uVar22);
      }
      else {
        if (DAT_100adfb28 != -1) {
          _swift_once(&DAT_100adfb28,FUN_100579138);
        }
        lVar28 = DAT_100b77470;
        puVar13 = &DAT_100a48760;
        _swift_allocObject(&DAT_100a48760,0x18,7);
        _swift_unknownObjectWeakInit(puVar13 + 0x10,*(undefined8 *)(unaff_x29 + -0xb8));
        puVar14 = &DAT_100a48800;
        _swift_allocObject(&DAT_100a48800,0x28,7);
        *(undefined8 *)(puVar14 + 0x18) = 0;
        *(undefined8 *)(puVar14 + 0x20) = 0;
        *(undefined **)(puVar14 + 0x10) = puVar13;
        _swift_retain(puVar13);
        FUN_1001c01d4(uVar22,lVar28,1,thunk_FUN_100437ae4,puVar14);
        _swift_bridgeObjectRelease(uVar22);
        _swift_release(puVar13);
        _swift_release(puVar14);
        uVar25 = *(undefined8 *)(unaff_x29 + -0xd8);
      }
      unaff_x26 = (class_t *)&objc::class_t::_TtC8Playback24PitchTempoProcessingView.cache;
      FUN_1000233c8(uVar25,FUN_1001436fc);
    }
LAB_100434bc0:
    FUN_100023468(unaff_x29 + -0xa8);
LAB_100434bc8:
    FUN_100023be4(unaff_x29 + -0x80,&DAT_100af5d38);
    IVar15 = (long)&(unaff_x26[0x35].superclass)->isa + *(long *)(unaff_x29 + -0xb8);
    _swift_unknownObjectWeakLoadStrong();
    if (IVar15 != 0) {
      _objc_msgSend(IVar15,"setHidden:",
                    (ulong)(((uint)*(undefined8 *)(unaff_x29 + -0xc0) | *(uint *)(unaff_x29 + -0xd0)
                            ) & 1));
    }
    IVar31 = *(ID *)(unaff_x29 + -0xb8);
    IVar15 = _objc_msgSend(IVar31,"contentView");
    bVar6 = (*(uint *)(unaff_x29 + -0xcc) & 1) == 0;
    uVar25 = 0x3ff0000000000000;
    if (bVar6) {
      uVar25 = 0x3fd3333333333333;
    }
    uVar22 = 3;
    if (bVar6) {
      uVar22 = 0;
    }
    _objc_msgSend(IVar15,"setAlpha:",uVar25);
    _objc_msgSend(IVar31,"setSelectionStyle:",uVar22);
    pcVar21 = "setAccessoryType:";
    auVar108._0_8_ = _objc_msgSend(IVar31,"setAccessoryType:",*(ulong *)(unaff_x29 + -0xc0) & 1);
    auVar108._8_8_ = pcVar21;
    return auVar108;
  case (char *)0xa8:
    auVar107._8_8_ = 0xec000000736c6f63;
    auVar107._0_8_ = 0x6f746f7250495041;
    return auVar107;
  case (char *)0xa9:
switchD_100419fe0_caseD_a9:
    auVar111._8_8_ = pcVar18;
    auVar111._0_8_ = puVar8;
    return auVar111;
  case (char *)0xaa:
    puVar13 = &_OBJC_CLASS___CADisplayLink;
    _swift_getInitializedObjCClass();
    pcVar21 = "displayLinkWithTarget:selector:";
    IVar15 = _objc_msgSend((ID)puVar13,"displayLinkWithTarget:selector:");
    *(ID *)(unaff_x21 + (long)&unaff_x20->isa) = IVar15;
    unaff_x19 = *(class_t **)(unaff_x21 + (long)&unaff_x20->isa);
    if (unaff_x19 == (class_t *)0x0) {
      auVar5._8_8_ = 0;
      auVar5._0_8_ = pcVar21;
      return auVar5 << 0x40;
    }
    unaff_x20 = (class_t *)&_OBJC_CLASS___NSRunLoop;
    _swift_getInitializedObjCClass();
  case (char *)0xb7:
    IVar15 = _objc_msgSend((ID)unaff_x20,"currentRunLoop");
    pcVar21 = "addToRunLoop:forMode:";
    _objc_msgSend((ID)unaff_x19,"addToRunLoop:forMode:",IVar15,
                  *(undefined8 *)PTR__NSRunLoopCommonModes_100a1d938);
    auVar4._8_8_ = 0;
    auVar4._0_8_ = pcVar21;
    return auVar4 << 0x40;
  case (char *)0xab:
    pcVar21 = "setCornerRadius:";
    _objc_msgSend(0x6f746f7250495041,"setCornerRadius:");
    auVar2._8_8_ = 0;
    auVar2._0_8_ = pcVar21;
    return auVar2 << 0x40;
  case (char *)0xac:
    puVar13 = &DAT_100af5738;
    FUN_100021774();
    lVar28 = (long)&stack0x00000000 -
             (*(long *)(*(long *)(puVar13 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
    (*(code *)unaff_x28->instanceSize)(lVar28);
    (*(code *)unaff_x28->weakIvarLayout)(lVar28,0,1);
    __sSo8UIButtonC5UIKitE13ConfigurationV30titleTextAttributesTransformerAC015UIConfigurationefG0VSgvs
              (lVar28);
    puVar13 = &DAT_100af5730;
    FUN_100021774();
    lVar28 = (long)&stack0x00000000 -
             (*(long *)(*(long *)(puVar13 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
    (*(code *)unaff_x26->cache)(lVar28);
    (*(code *)unaff_x26[1].cache)(lVar28,0,1);
    __sSo8UIButtonC5UIKitE13configurationAbCE13ConfigurationVSgvs(lVar28);
    (*(code *)unaff_x28->instanceStart)();
    (*(code *)unaff_x26->superclass)();
    auVar106._8_8_ = unaff_x21;
    auVar106._0_8_ = unaff_x22;
    return auVar106;
  case (char *)0xad:
    goto switchD_100419fe0_caseD_ad;
  case (char *)0xae:
    _swift_bridgeObjectRetain();
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF();
    _swift_bridgeObjectRelease();
    auVar110._8_8_ = unaff_x20;
    auVar110._0_8_ = unaff_x19;
    return auVar110;
  case (char *)0xaf:
    do {
      unaff_x20 = unaff_x22;
      puVar8 = unaff_x23;
      do {
        (*(code *)unaff_x19[1].cache)();
        FUN_1000d4490();
        lVar28 = unaff_x25;
        (*(code *)unaff_x19[1].superclass)();
        if ((int)lVar28 == 1) {
          FUN_100023be4();
        }
        else {
          unaff_x28 = unaff_x19->data;
          uVar25 = *(undefined8 *)(unaff_x29 + -0x70);
          (*(code *)unaff_x28)(uVar25);
          (*(code *)unaff_x28)(*(undefined8 *)(unaff_x29 + -0x60),uVar25);
          puVar32 = puVar8;
          _swift_isUniquelyReferenced_nonNull_native();
          unaff_x23 = puVar8;
          if (((ulong)puVar32 & 1) == 0) {
            unaff_x23 = (undefined8 *)0x0;
            FUN_10078f1b8(0,puVar8[2] + 1,1,puVar8);
          }
          unaff_x22 = (class_t *)unaff_x23[2];
          pcVar21 = (char *)unaff_x23[3];
switchD_100419fe0_caseD_b4:
          puVar13 = (undefined *)((long)&unaff_x22->isa + 1);
          puVar8 = unaff_x23;
          if ((class_t *)((ulong)pcVar21 >> 1) <= unaff_x22) {
            puVar8 = (undefined8 *)(ulong)((char *)0x1 < pcVar21);
            FUN_10078f1b8(puVar8,puVar13,1,unaff_x23);
          }
          puVar8[2] = puVar13;
          (*(code *)unaff_x28)
                    ((long)puVar8 +
                     (long)unaff_x19[1].data * (long)unaff_x22 +
                     ((ulong)*(byte *)&unaff_x19[2].isa + 0x20 &
                     ((ulong)*(byte *)&unaff_x19[2].isa ^ 0xffffffffffffffff)),
                     *(undefined8 *)(unaff_x29 + -0x60));
          ppuVar24 = &PTR_s_setContentCompressionResistanceP_100aa1000;
        }
        unaff_x26 = (class_t *)((long)&unaff_x26->isa + 1);
        if (unaff_x20 == unaff_x26) {
          pcVar18 = (char *)0x2;
          _swift_bridgeObjectRelease_n(*(undefined8 *)(unaff_x29 + -0x58),2);
          FUN_100149da4(*(undefined8 *)(unaff_x29 + -0x78),puVar8);
          _swift_bridgeObjectRelease(puVar8);
          goto switchD_100419fe0_caseD_a9;
        }
        if (*(long *)(unaff_x29 + -0x68) == 0) {
          pcVar26 = *(class_t **)(*(long *)(unaff_x29 + -0x58) + (long)unaff_x26 * 8 + 0x20);
        }
        else {
          pcVar26 = unaff_x26;
          FUN_1000cbf38(unaff_x26,*(undefined8 *)(unaff_x29 + -0x58));
        }
        IVar15 = _objc_msgSend((ID)pcVar26,(SEL)((class_t *)((long)ppuVar24 + 0x8c0))->superclass);
      } while (IVar15 == 0);
      __s10Foundation4DateV36_unconditionallyBridgeFromObjectiveCyACSo6NSDateCSgFZ();
      unaff_x22 = unaff_x20;
      unaff_x23 = puVar8;
    } while( true );
  case (char *)0xb0:
    _objc_msgSend(0x6f746f7250495041,(SEL)0xec000000736c6f63);
    pcVar30 = unaff_x21 + (long)unaff_x19;
    _swift_unknownObjectWeakLoadStrong();
    if (pcVar30 != (code *)0x0) {
      _objc_msgSend((ID)pcVar30,"setHidden:",1);
    }
    uVar7 = 0;
    FUN_10012d568();
    lVar28 = _TtC8Playback24ContentItemTableViewCell::viewLabelViewBannerGroup;
    if ((uVar7 & 0xff) == 2) {
      pcVar30 = unaff_x21 + _TtC8Playback24ContentItemTableViewCell::typeIndicatorImageView;
      _swift_unknownObjectWeakLoadStrong();
      if (pcVar30 != (code *)0x0) {
        _objc_msgSend((ID)pcVar30,"setHidden:",1);
      }
      lVar28 = _TtC8Playback24ContentItemTableViewCell::viewLabelViewBannerGroup;
      _swift_beginAccess(unaff_x21 +
                         _TtC8Playback24ContentItemTableViewCell::viewLabelViewBannerGroup,
                         unaff_x29 + -0x68,0x20,0);
      uVar17 = *(ulong *)(unaff_x21 + lVar28);
      if (uVar17 == 0) {
        puVar13 = &DAT_100af56b8;
        FUN_100023be4();
        unaff_x27 = unaff_x29 + -0x68;
        _swift_endAccess(unaff_x27);
        goto LAB_10043581c;
      }
      _swift_endAccess(unaff_x29 + -0x68);
      if (uVar17 >> 0x3e == 0) {
        IVar15 = *(ID *)((uVar17 & 0xffffffffffffff8) + 0x10);
      }
      else {
        IVar15 = uVar17;
        if (-1 < (long)uVar17) {
          IVar15 = uVar17 & 0xffffffffffffff8;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      if (IVar15 != 0) {
        if ((long)IVar15 < 1) {
                    /* WARNING: Does not return */
          pcVar30 = (code *)SoftwareBreakpoint(1,0x1004358b4);
          (*pcVar30)();
        }
        _swift_bridgeObjectRetain_n(uVar17,2);
        IVar31 = 0;
        do {
          if ((uVar17 & 0xc000000000000001) == 0) {
            IVar12 = *(ID *)(uVar17 + IVar31 * 8 + 0x20);
          }
          else {
            IVar12 = IVar31;
            FUN_1000ccea8(IVar31,uVar17);
          }
          IVar31 = IVar31 + 1;
          _objc_msgSend(IVar12,"setHidden:",0);
        } while (IVar15 != IVar31);
        _swift_bridgeObjectRelease_n(uVar17,2);
      }
    }
    else if ((uVar7 & 0xff) == 3) {
      _swift_beginAccess(unaff_x21 +
                         _TtC8Playback24ContentItemTableViewCell::viewLabelViewBannerGroup,
                         unaff_x29 + -0x68,0,0);
      uVar17 = *(ulong *)(unaff_x21 + lVar28);
      if (uVar17 != 0) {
        if (uVar17 >> 0x3e == 0) {
          IVar15 = *(ID *)((uVar17 & 0xffffffffffffff8) + 0x10);
        }
        else {
          IVar15 = uVar17;
          if (-1 < (long)uVar17) {
            IVar15 = uVar17 & 0xffffffffffffff8;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
        }
        if (IVar15 != 0) {
          if ((long)IVar15 < 1) {
                    /* WARNING: Does not return */
            pcVar30 = (code *)SoftwareBreakpoint(1,0x1004358b0);
            (*pcVar30)();
          }
          _swift_bridgeObjectRetain_n(uVar17,2);
          IVar31 = 0;
          do {
            if ((uVar17 & 0xc000000000000001) == 0) {
              IVar12 = *(ID *)(uVar17 + IVar31 * 8 + 0x20);
            }
            else {
              IVar12 = IVar31;
              FUN_1000ccea8(IVar31,uVar17);
            }
            IVar31 = IVar31 + 1;
            _objc_msgSend(IVar12,"setHidden:",1);
          } while (IVar15 != IVar31);
          _swift_bridgeObjectRelease_n(uVar17,2);
        }
      }
      pcVar30 = unaff_x21 + _TtC8Playback24ContentItemTableViewCell::typeIndicatorImageView;
      _swift_unknownObjectWeakLoadStrong();
      if (pcVar30 != (code *)0x0) {
        _objc_msgSend((ID)pcVar30,"setHidden:",0);
      }
    }
    puVar13 = &DAT_100af56b8;
    FUN_100023be4();
LAB_10043581c:
    auVar109._8_8_ = puVar13;
    auVar109._0_8_ = unaff_x27;
    return auVar109;
  case (char *)0xb1:
    goto switchD_100419fe0_caseD_b1;
  case (char *)0xb2:
    uVar25 = uRam6f746f7250495dc9;
    puVar13 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
    __ss23CustomStringConvertibleP11descriptionSSvgTj();
    *(undefined8 *)(unaff_x29 + -0xb8) = uVar25;
    *(undefined **)(unaff_x29 + -0xb0) = puVar13;
    _swift_bridgeObjectRetain(puVar13);
    __sSS6appendyySSF(0x202e,0xe200000000000000);
    _swift_bridgeObjectRelease(puVar13);
    uVar25 = *(undefined8 *)(unaff_x29 + -0xb0);
    pcVar26 = unaff_x26->superclass;
    pcVar10 = (class_rw_t *)unaff_x26->cache;
    *(undefined8 *)(unaff_x29 + -0xb8) = *(undefined8 *)(unaff_x29 + -0xb8);
    *(undefined8 *)(unaff_x29 + -0xb0) = uVar25;
    _swift_bridgeObjectRetain(uVar25);
    __sSS6appendyySSF(pcVar26,pcVar10);
    _swift_bridgeObjectRelease(uVar25);
    uVar25 = *(undefined8 *)(unaff_x29 + -0xb8);
    uVar22 = *(undefined8 *)(unaff_x29 + -0xb0);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar25,uVar22);
    _swift_bridgeObjectRelease(uVar22);
    _objc_msgSend((ID)unaff_x22,"setText:",uVar25);
    lVar28 = 0x34;
    if ((*(uint *)(unaff_x29 + -0xe0) & 1) != 0) {
      lVar28 = 0x3c;
    }
    puVar8 = (undefined8 *)((long)&unaff_x26->isa + (long)*(int *)(unaff_x21 + lVar28));
    uVar25 = *puVar8;
    uVar22 = puVar8[1];
    _swift_bridgeObjectRetain(uVar22);
    IVar15 = unaff_x24 + _TtC8Playback24ContentItemTableViewCell::subtitleLabel;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar15 != 0) {
      uVar19 = uVar25;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar25,uVar22);
      _objc_msgSend(IVar15,"setText:",uVar19);
    }
    uVar19 = *(undefined8 *)(unaff_x29 + -0xc0);
    FUN_10043641c(unaff_x26->superclass,(class_rw_t *)unaff_x26->cache,uVar25,uVar22,
                  *(undefined8 *)(unaff_x29 + -0xd0));
    _swift_bridgeObjectRelease(uVar22);
    _swift_bridgeObjectRelease(uVar19);
    _swift_bridgeObjectRelease();
    lVar28 = _TtC8Playback24ContentItemTableViewCell::artworkImageView;
    IVar15 = unaff_x24 + _TtC8Playback24ContentItemTableViewCell::artworkImageView;
    _swift_unknownObjectWeakLoadStrong();
    uVar7 = *(uint *)(unaff_x29 + -0xdc);
    if (IVar15 != 0) {
      _objc_msgSend(IVar15,"setHidden:",(ulong)(uVar7 & 1));
    }
    if ((uVar7 & 1) == 0) {
      bVar6 = *(char *)((long)&unaff_x26->isa + (long)*(int *)(unaff_x21 + 0x4c)) == '\0';
      uVar25 = 0x6c615f64756f6c63;
      if (bVar6) {
        uVar25 = 0x6f777472615f6f6e;
      }
      uVar22 = 0xef7472615f6d7562;
      if (bVar6) {
        uVar22 = 0xea00000000006b72;
      }
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar25,uVar22);
      _swift_bridgeObjectRelease(uVar22);
      puVar13 = &_OBJC_CLASS___UIImage;
      _swift_getInitializedObjCClass();
      _objc_msgSend((ID)puVar13,"imageNamed:",uVar25);
      uVar25 = 0;
      FUN_100095dd8(0);
      lVar28 = unaff_x24 + lVar28;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar28 == 0) {
        _swift_bridgeObjectRelease(uVar25);
      }
      else {
        if (DAT_100adfb28 != -1) {
          _swift_once(&DAT_100adfb28,FUN_100579138);
        }
        lVar28 = DAT_100b77470;
        puVar13 = &DAT_100a48760;
        _swift_allocObject(&DAT_100a48760,0x18,7);
        _swift_unknownObjectWeakInit(puVar13 + 0x10);
        puVar14 = &DAT_100a48878;
        _swift_allocObject(&DAT_100a48878,0x28,7);
        *(undefined8 *)(puVar14 + 0x18) = 0;
        *(undefined8 *)(puVar14 + 0x20) = 0;
        *(undefined **)(puVar14 + 0x10) = puVar13;
        _swift_retain(puVar13);
        FUN_1001c01d4(uVar25,lVar28,1,thunk_FUN_100437ae4,puVar14);
        _swift_bridgeObjectRelease(uVar25);
        _swift_release(puVar13);
        _swift_release(puVar14);
      }
    }
    else {
      IVar15 = unaff_x24 + lVar28;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar15 != 0) {
        _objc_msgSend(IVar15,"setImage:",0);
      }
    }
    pcVar30 = FUN_100552058;
    FUN_1000233c8();
    FUN_100023468(unaff_x29 + -0xa8);
    lVar28 = unaff_x29 + -0x80;
    FUN_100023468(lVar28);
    auVar112._8_8_ = pcVar30;
    auVar112._0_8_ = lVar28;
    return auVar112;
  case (char *)0xb3:
    pcVar26 = unaff_x20;
    in_stack_00000010 = unaff_x22;
    in_stack_00000018 = unaff_x21;
    in_stack_00000020 = unaff_x20;
    in_stack_00000028 = unaff_x19;
    in_stack_00000030 = unaff_x29;
    in_stack_00000038 = unaff_x30;
    _swift_getObjectType();
    pcVar18 = "prepareForReuse";
    in_stack_00000000 = unaff_x20;
    in_stack_00000008 = pcVar26;
    _objc_msgSendSuper2((objc_super *)&stack0x00000000,"prepareForReuse");
    puVar8 = (undefined8 *)
             ((long)&unaff_x20->isa + _TtC8Playback24ContentItemTableViewCell::artworkImageView);
    _swift_unknownObjectWeakLoadStrong();
    if (puVar8 != (undefined8 *)0x0) goto switchD_100419fe0_caseD_a6;
LAB_100435d4c:
    puVar13 = (undefined *)
              ((long)&unaff_x20->isa + _TtC8Playback24ContentItemTableViewCell::downloadStatusButton
              );
    _swift_unknownObjectWeakLoadStrong();
    if (puVar13 != (undefined *)0x0) {
      pcVar18 = "setStrokeEnd:";
      _objc_msgSend(*(ID *)(*(long *)(puVar13 + _TtC8Playback20DownloadStatusButton::progressView) +
                           _TtCC8Playback20DownloadStatusButton12ProgressView::progressLayer),
                    "setStrokeEnd:",0);
switchD_100419fe0_caseD_b5:
    }
    puVar13 = (undefined *)
              ((long)&unaff_x20->isa + _TtC8Playback24ContentItemTableViewCell::badgeLabel);
    _swift_unknownObjectWeakLoadStrong();
    if (puVar13 != (undefined *)0x0) {
      pcVar18 = "setHidden:";
      _objc_msgSend((ID)puVar13,"setHidden:",1);
    }
    puVar8 = (undefined8 *)
             ((long)&unaff_x20->isa + _TtC8Playback24ContentItemTableViewCell::downloadHandler);
    uVar25 = *puVar8;
    *puVar8 = 0;
    puVar8[1] = 0;
    _swift_unknownObjectRelease(uVar25);
    lVar28 = _TtC8Playback24ContentItemTableViewCell::downloadProgressDisplayLink;
    IVar15 = *(ID *)((long)&unaff_x20->isa +
                    _TtC8Playback24ContentItemTableViewCell::downloadProgressDisplayLink);
    if (IVar15 != 0) {
      pcVar18 = "invalidate";
      _objc_msgSend(IVar15,"invalidate");
    }
    *(undefined8 *)((long)&unaff_x20->isa + lVar28) = 0;
    auVar3._8_8_ = 0;
    auVar3._0_8_ = pcVar18;
    return auVar3 << 0x40;
  case (char *)0xb4:
    goto switchD_100419fe0_caseD_b4;
  case (char *)0xb5:
    goto switchD_100419fe0_caseD_b5;
  case (char *)0xb6:
    goto switchD_100419fe0_caseD_b6;
  case (char *)0xba:
  case (char *)0xbe:
  case (char *)0xc6:
  case (char *)0xca:
    goto switchD_100419fe0_caseD_ba;
  case (char *)0xc3:
  case (char *)0xcf:
    goto switchD_100419fe0_caseD_c3;
  case (char *)0xd0:
  case (char *)0xf4:
    if (in_ZR) {
      if (in_stack_00000050 != 0) {
        FUN_10003b4b4(unaff_x25 + 8,&stack0x00000010,&DAT_100af56a0);
        uVar25 = 0;
        FUN_10021451c(0);
        puVar8 = &stack0x00000008;
        _swift_dynamicCast(puVar8,&stack0x00000010,PTR___sypN_100a1e038 + 8,uVar25,0);
        pcVar26 = in_stack_00000008;
        if ((int)puVar8 != 0) {
          uVar23 = *(ulong *)((long)&unaff_x20->isa +
                             _TtC8Playback22WaveformViewController::automationMarkerViews);
          _swift_retain(in_stack_00000008);
          uVar17 = uVar23;
          _swift_bridgeObjectRetain();
          FUN_100465e04();
          _swift_bridgeObjectRelease(uVar23);
          _swift_release(pcVar26);
          if (uVar17 != 0) {
            lVar28 = *(long *)((long)&unaff_x20->isa +
                              _TtC8Playback22WaveformViewController::selectedTimelineMarkerView);
            if (lVar28 != 0) {
              FUN_10057bfd4(0);
              uVar23 = uVar17;
              __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar17,lVar28);
              if ((uVar23 & 1) != 0) {
                FUN_1005f1c00(0);
                goto LAB_10045a130;
              }
            }
            FUN_1005f1fc8(uVar17,1,1);
          }
LAB_10045a130:
          _swift_release(pcVar26);
          FUN_100023468(&stack0x00000010);
          puVar13 = &DAT_100af56a0;
          puVar8 = (undefined8 *)(unaff_x25 + 8);
          goto LAB_10045a0f8;
        }
        FUN_100023468(&stack0x00000010);
      }
    }
    else {
      FUN_1000a1b5c();
    }
    puVar13 = &DAT_100b02fe8;
    puVar8 = &stack0x00000030;
LAB_10045a0f8:
    FUN_100023be4(puVar8,puVar13);
    auVar115._8_8_ = puVar13;
    auVar115._0_8_ = puVar8;
    return auVar115;
  case (char *)0xd1:
  case (char *)0xf5:
    do {
      *(class_t **)(pcVar21 + -0x100) = unaff_x26;
      __s10Foundation4DataV36_unconditionallyBridgeFromObjectiveCyACSo6NSDataCSgFZ();
      lVar16 = 0;
      FUN_100113adc();
      lVar28 = lVar16;
      _swift_allocObject();
      __s10Foundation11JSONDecoderCACycfc();
      puVar32 = *(undefined8 **)(unaff_x29 + -0x168);
      *puVar32 = FUN_100113b34;
      puVar32[1] = 0;
      pcVar30 = *(code **)(*(long *)(unaff_x29 + -0x178) + 0x68);
      (*pcVar30)(puVar32,*(undefined4 *)(unaff_x29 + -0x17c),*(undefined8 *)(unaff_x29 + -0x160));
      __s10Foundation11JSONDecoderC20dateDecodingStrategyAC04DatedE0OvsTj(puVar32);
      puVar13 = &DAT_100afd860;
      FUN_100023140(&DAT_100afd860,FUN_1000bfe90,&DAT_100921398);
      __s10Foundation11JSONDecoderC6decode_4fromxxm_AA4DataVtKSeRzlFTj
                (unaff_x27,unaff_x28,puVar8,pcVar18,unaff_x28,puVar13);
      if (unaff_x21 == (code *)0x0) {
        *(code **)(unaff_x29 + -0x1b8) = pcVar30;
        FUN_100039b24(puVar8,pcVar18);
        _swift_release(lVar28);
        pcVar30 = *(code **)(*(long *)(unaff_x29 + -0x140) + 0x38);
        (*pcVar30)(unaff_x27,0,1,unaff_x28);
        lVar28 = *(long *)(unaff_x29 + -0x1b0);
        FUN_100271c3c(unaff_x27,lVar28);
        pcVar21 = "serverVersion";
        IVar31 = *(ID *)(unaff_x29 + -0x148);
        IVar15 = _objc_msgSend(IVar31,"serverVersion");
        if ((int)IVar15 < *(int *)(lVar28 + 0xc)) {
          pcVar21 = "sourceAPISetlistData";
          IVar15 = _objc_msgSend(IVar31,"sourceAPISetlistData");
          lVar28 = *(long *)(unaff_x29 + -0x188);
          bVar6 = IVar15 == 0;
          if (!bVar6) {
            *(code **)(unaff_x29 + -0x1c8) = pcVar30;
            __s10Foundation4DataV36_unconditionallyBridgeFromObjectiveCyACSo6NSDataCSgFZ();
            _swift_allocObject(lVar16,*(undefined4 *)(lVar16 + 0x30),*(undefined2 *)(lVar16 + 0x34))
            ;
            __s10Foundation11JSONDecoderCACycfc();
            puVar8 = *(undefined8 **)(unaff_x29 + -0x168);
            *puVar8 = FUN_100113b34;
            puVar8[1] = 0;
            (**(code **)(unaff_x29 + -0x1b8))
                      (puVar8,*(undefined4 *)(unaff_x29 + -0x17c),
                       *(undefined8 *)(unaff_x29 + -0x160));
            __s10Foundation11JSONDecoderC20dateDecodingStrategyAC04DatedE0OvsTj(puVar8);
            __s10Foundation11JSONDecoderC6decode_4fromxxm_AA4DataVtKSeRzlFTj
                      (*(undefined8 *)(unaff_x29 + -0x1a8),unaff_x28,IVar15,pcVar21,unaff_x28,
                       puVar13);
            FUN_100039b24(IVar15,pcVar21);
            _swift_release(lVar16);
            pcVar30 = *(code **)(unaff_x29 + -0x1c8);
          }
          uVar25 = *(undefined8 *)(unaff_x29 + -0x1a8);
          (*pcVar30)(uVar25,bVar6,1,unaff_x28);
          (**(code **)(*(long *)(unaff_x29 + -0x140) + 0x30))(uVar25,1,unaff_x28);
          FUN_100023be4(uVar25,&DAT_100af6c68);
          pcVar21 = "declinedUpdateVersion";
          _objc_msgSend(IVar31,"declinedUpdateVersion");
          FUN_100271c80(*(undefined8 *)(unaff_x29 + -0x1b0));
          unaff_x27 = *(long *)(unaff_x29 + -0x1c0);
          goto LAB_10043a5b0;
        }
        FUN_100271c80(lVar28);
        unaff_x27 = *(long *)(unaff_x29 + -0x1c0);
        lVar28 = *(long *)(unaff_x29 + -0x188);
        goto LAB_10043a5b0;
      }
      _swift_release(lVar28);
      FUN_100039b24(puVar8,pcVar18);
      __sSo13os_log_type_ta0A0E7defaultABvgZ();
      puVar13 = &DAT_100af52c8;
      FUN_100021774();
      _swift_initStackObject();
      uVar25 = *(undefined8 *)(unaff_x29 + -0x1a0);
      *(undefined8 *)(puVar13 + 0x18) = *(undefined8 *)(unaff_x29 + -0x198);
      *(undefined8 *)(puVar13 + 0x10) = uVar25;
      _swift_getErrorValue(unaff_x21,unaff_x29 + -0xb8,unaff_x29 + -0xd0);
      uVar25 = *(undefined8 *)(unaff_x29 + -200);
      uVar19 = *(undefined8 *)(unaff_x29 + -0xc0);
      FUN_1002c2c2c();
      *(undefined **)(puVar13 + 0x38) = PTR___sSSN_100a1dce0;
      uVar22 = uVar25;
      FUN_100026528();
      *(undefined8 *)(puVar13 + 0x40) = uVar22;
      *(undefined8 *)(puVar13 + 0x20) = uVar25;
      *(undefined8 *)(puVar13 + 0x28) = uVar19;
      FUN_10041ac94(puVar8,0x4c,"Error while converting Data to APISetlist: %{public}s",0x35,2,
                    puVar13);
      _swift_setDeallocating(puVar13);
      FUN_100023468(puVar13 + 0x20);
      _swift_errorRelease(unaff_x21);
      unaff_x21 = (code *)0x0;
      lVar28 = *(long *)(unaff_x29 + -0x188);
      unaff_x26 = *(class_t **)(unaff_x29 + -0x148);
      do {
        (**(code **)(*(long *)(unaff_x29 + -0x140) + 0x38))(unaff_x27,1,1,unaff_x28);
        FUN_100023be4(unaff_x27,&DAT_100af6c68);
        pcVar21 = "title";
        uVar17 = _objc_msgSend((ID)unaff_x26,"title");
        if (uVar17 == 0) {
          uVar17 = 0;
          pcVar30 = (code *)0x0;
        }
        else {
          __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
          pcVar30 = (code *)pcVar21;
        }
        if (DAT_100adfea0 != -1) {
          pcVar20 = FUN_10077173c;
          _swift_once(&DAT_100adfea0,FUN_10077173c);
          pcVar21 = (char *)pcVar20;
        }
        if (pcVar30 == (code *)0x0) {
LAB_10043a558:
          uVar23 = *(ulong *)(unaff_x29 + -0x170);
          uVar17 = uVar23;
          _swift_isUniquelyReferenced_nonNull_native();
          *(ulong *)(unaff_x29 + -0x68) = uVar23;
          if ((uVar17 & 1) == 0) {
            pcVar21 = (char *)(*(long *)(uVar23 + 0x10) + 1);
            FUN_1001cc874(0,pcVar21,1);
            uVar23 = *(ulong *)(unaff_x29 + -0x68);
          }
          uVar17 = *(ulong *)(uVar23 + 0x10);
          pcVar30 = (code *)(uVar17 + 1);
          if (*(ulong *)(uVar23 + 0x18) >> 1 <= uVar17) {
            pcVar21 = (char *)pcVar30;
            FUN_1001cc874(1 < *(ulong *)(uVar23 + 0x18),pcVar30,1);
            uVar23 = *(ulong *)(unaff_x29 + -0x68);
          }
          *(code **)(uVar23 + 0x10) = pcVar30;
          *(ulong *)(unaff_x29 + -0x170) = uVar23;
          *(class_t **)(uVar23 + uVar17 * 8 + 0x20) = unaff_x26;
        }
        else if ((uVar17 == DAT_100b77a48) && (pcVar30 == DAT_100b77a50)) {
          _swift_bridgeObjectRelease(pcVar30);
        }
        else {
          pcVar21 = (char *)pcVar30;
          __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                    (uVar17,pcVar30,DAT_100b77a48,DAT_100b77a50,0);
          _swift_bridgeObjectRelease(pcVar30);
          if ((uVar17 & 1) == 0) goto LAB_10043a558;
        }
LAB_10043a5b0:
        pcVar26 = *(class_t **)(unaff_x29 + -0x150);
        lVar16 = *(long *)(unaff_x29 + -0x158);
        do {
          unaff_x19 = (class_t *)((long)&unaff_x19->isa + 1);
          if (pcVar26 == unaff_x19) {
            _swift_bridgeObjectRelease(lVar28);
            uVar17 = *(ulong *)(unaff_x29 + -0x170);
            if (((long)uVar17 < 0) || ((uVar17 >> 0x3e & 1) != 0)) {
              uVar23 = uVar17;
              __ss18_CocoaArrayWrapperV8endIndexSivg(uVar17);
            }
            else {
              uVar23 = *(ulong *)(uVar17 + 0x10);
            }
            _swift_release(uVar17);
            auVar114._1_7_ = 0;
            auVar114[0] = 0 < (long)uVar23;
            auVar114._8_8_ = pcVar21;
            return auVar114;
          }
          if (lVar16 == 0) {
            unaff_x26 = *(class_t **)(lVar28 + (long)unaff_x19 * 8 + 0x20);
          }
          else {
            unaff_x26 = unaff_x19;
            FUN_1000cce94(unaff_x19,lVar28);
          }
          pcVar21 = "isDemo";
          IVar15 = _objc_msgSend((ID)unaff_x26,"isDemo");
        } while ((IVar15 & 1) != 0);
        pcVar18 = "sourceAPISetlistData";
        puVar8 = (undefined8 *)_objc_msgSend((ID)unaff_x26,"sourceAPISetlistData");
      } while (puVar8 == (undefined8 *)0x0);
      pcVar21 = (char *)(unaff_x29 + -0x48);
    } while( true );
  }
  auVar88._8_8_ = (ulong)(pcVar21 + -0x20) | 0x8000000000000000;
  auVar88._0_8_ = 0xd00000000000001f;
  return auVar88;
switchD_100419fe0_caseD_ba:
  goto LAB_10041aa20;
switchD_100419fe0_caseD_1:
  auVar64._8_8_ = pcVar18;
  auVar64._0_8_ = puVar8;
  return auVar64;
}

// ==== 10042f27c FUN_10042f27c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ulong FUN_10042f27c(void)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  ID IVar4;
  undefined *self;
  char *pcVar5;
  byte bVar6;
  ID unaff_x20;
  ID IVar7;
  undefined1 auStack_60 [32];
  
  uVar2 = _objc_msgSend(unaff_x20,"storedPortID");
  FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
  uVar3 = 0;
  __sSo8NSNumberC10FoundationE14integerLiteralABSi_tcfC(0);
  if ((uVar2 != 0) && (__sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar2,uVar3), (uVar2 & 1) != 0))
  {
    _objc_msgSend(unaff_x20,"setStoredPortID:",0);
  }
  IVar4 = _objc_msgSend(unaff_x20,"storedPortID");
  if (IVar4 == 0) {
    pcVar5 = "lastConnectedPortName";
    IVar4 = _objc_msgSend(unaff_x20,"lastConnectedPortName");
    if (IVar4 != 0) {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      if (DAT_100adefa0 != -1) {
        _swift_once(&DAT_100adefa0,FUN_10037c47c);
      }
      lVar1 = DAT_100b75f50;
      _swift_beginAccess(DAT_100b75f50 + 0x18,auStack_60,0,0);
      IVar7 = *(ID *)(lVar1 + 0x18);
      _swift_bridgeObjectRetain(pcVar5);
      IVar4 = IVar7;
      _swift_bridgeObjectRetain();
      FUN_1004307d8();
      _swift_bridgeObjectRelease(IVar7);
      _swift_bridgeObjectRelease_n(pcVar5,2);
      if (IVar4 != 0) {
        IVar4 = _objc_msgSend(IVar4,"uniqueID");
        self = &_OBJC_CLASS___NSNumber;
        _objc_allocWithZone();
        IVar4 = _objc_msgSend((ID)self,"initWithInt:",IVar4);
        _objc_msgSend(unaff_x20,"setStoredPortID:",IVar4);
      }
      *(undefined8 *)(unaff_x20 + _TtC8Playback7MIDIBus::privateDestinationEndpoint) = 0;
    }
    IVar4 = _objc_msgSend(unaff_x20,"storedPortID");
    if (IVar4 == 0) {
      IVar4 = 0;
      bVar6 = 1;
      goto LAB_10042f490;
    }
  }
  IVar4 = _objc_msgSend(IVar4,"intValue");
  bVar6 = 0;
LAB_10042f490:
  return IVar4 & 0xffffffff | (ulong)bVar6 << 0x20;
}

// ==== 10042f988 FUN_10042f988 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_10042f988(ulong param_1)

{
  ulong uVar1;
  undefined *self;
  ID IVar2;
  ulong uVar3;
  ID self_00;
  char *pcVar4;
  ID unaff_x20;
  
  if ((param_1 >> 0x20 & 1) == 0) {
    self = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar2 = _objc_msgSend((ID)self,"initWithInt:",param_1);
    _objc_msgSend(unaff_x20,"setStoredPortID:",IVar2);
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar1 = DAT_100b75f50;
    uVar3 = DAT_100b75f50;
    _swift_retain();
    FUN_10042f27c();
    self_00 = uVar3 & 0xffffffff | (uVar3 >> 0x20 & 1) << 0x20;
    FUN_1003824b4();
    _swift_release(uVar1);
    IVar2 = 0;
    if (self_00 != 0) {
      pcVar4 = "displayName";
      IVar2 = _objc_msgSend(self_00,"displayName");
      if (IVar2 == 0) {
        IVar2 = 0;
      }
      else {
        __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(IVar2);
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar2,pcVar4);
        _swift_bridgeObjectRelease(pcVar4);
      }
    }
    _objc_msgSend(unaff_x20,"setLastConnectedPortName:",IVar2);
  }
  else {
    _objc_msgSend(unaff_x20,"setStoredPortID:",0);
    _objc_msgSend(unaff_x20,"setLastConnectedPortName:",0);
  }
  *(undefined8 *)(unaff_x20 + _TtC8Playback7MIDIBus::privateDestinationEndpoint) = 0;
  return 0;
}

// ==== 10042fb14 _TtC8Playback7MIDIBus::initWithEntity:insertIntoManagedObjectContext: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback7MIDIBus::initWithEntity_insertIntoManagedObjectContext_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithEntity:insertIntoManagedObjectContext:",param_3,
                              param_4);
  return IVar2;
}

// ==== 10042fb68 _TtC8Playback7MIDIBus::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback7MIDIBus::_cxx_construct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + privateDestinationEndpoint) = 0;
  return;
}

// ==== 10042fb78 _TtC8Playback7MIDIBus::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback7MIDIBus::_cxx_destruct(ID param_1,SEL param_2)

{
  return;
}

// ==== 10042fb88 FUN_10042fb88 ====
void FUN_10042fb88(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback7MIDIBus);
  return;
}

// ==== 10042fd3c FUN_10042fd3c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_10042fd3c(void)

{
  byte bVar1;
  undefined *puVar2;
  undefined8 uVar3;
  ID IVar4;
  char *pcVar5;
  char *pcVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  char *pcVar11;
  char *pcVar12;
  byte *pbVar13;
  ulong uVar14;
  long lVar15;
  undefined1 local_e0 [8];
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined1 auStack_c8 [16];
  undefined8 local_b8 [10];
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_100a1d8f0;
  puVar2 = &_OBJC_CLASS___NSFetchRequest;
  _objc_allocWithZone();
  uVar3 = 0x7375424944494d;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x7375424944494d,0xe700000000000000);
  IVar4 = _objc_msgSend((ID)puVar2,"initWithEntityName:",uVar3);
  local_b8[0] = 0;
  pcVar5 = (char *)_objc_msgSend(IVar4,"execute:",local_b8);
  if (pcVar5 == (char *)0x0) {
    uVar3 = local_b8[0];
    __s10Foundation22_convertNSErrorToErrorys0E0_pSo0C0CSgF(local_b8[0]);
    uVar7 = 0;
    _swift_willThrow(0);
    __sSo13os_log_type_ta0A0E7defaultABvgZ();
    puVar2 = &DAT_100af52c8;
    FUN_100021774();
    _swift_initStackObject();
    *(undefined8 *)(puVar2 + 0x18) = 2;
    *(undefined8 *)(puVar2 + 0x10) = 1;
    _swift_getErrorValue(uVar3,auStack_c8,local_e0);
    uVar8 = uStack_d8;
    uVar10 = local_d0;
    FUN_1002c2c2c();
    *(undefined **)(puVar2 + 0x38) = PTR___sSSN_100a1dce0;
    uVar9 = uVar8;
    FUN_100026528();
    *(undefined8 *)(puVar2 + 0x40) = uVar9;
    *(undefined8 *)(puVar2 + 0x20) = uVar8;
    *(undefined8 *)(puVar2 + 0x28) = uVar10;
    FUN_10041ac94(uVar7,0x31,"Error populating MIDI buses: %{public}s",0x27,2,puVar2);
    _swift_setDeallocating(puVar2);
    FUN_100023468(puVar2 + 0x20);
    _swift_errorRelease(uVar3);
  }
  else {
    pcVar6 = pcVar5;
    FUN_10042fb88();
    pcVar11 = pcVar6;
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(pcVar5,pcVar6);
    if ((ulong)pcVar5 >> 0x3e == 0) {
      pcVar12 = *(char **)(((ulong)pcVar5 & 0xfffffffffffff8) + 0x10);
    }
    else {
      pcVar12 = (char *)((ulong)pcVar5 & 0xffffffffffffff8);
      if ((long)pcVar5 < 0) {
        pcVar12 = pcVar5;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    _swift_bridgeObjectRelease(pcVar5);
    if ((pcVar12 == (char *)0x0) && (DAT_100aebdf8 != 0)) {
      pbVar13 = &DAT_100aebe08;
      lVar15 = DAT_100aebdf8;
      do {
        bVar1 = *pbVar13;
        uVar14 = (ulong)bVar1;
        FUN_10042f620(uVar14);
        pcVar5 = pcVar6;
        _objc_allocWithZone();
        if (DAT_100ade9d8 != -1) {
          _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
        }
        IVar4 = _objc_msgSend(DAT_100b755c8,"viewContext");
        IVar4 = _objc_msgSend((ID)pcVar5,"initWithContext:",IVar4);
        _objc_msgSend(IVar4,"setId:",(ulong)(bVar1 + 1));
        _objc_msgSend(IVar4,"setEnabled:",1);
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar14,pcVar11);
        _swift_bridgeObjectRelease(pcVar11);
        _objc_msgSend(IVar4,"setTitle:",uVar14);
        _objc_msgSend(IVar4,"setStoredPortID:",0);
        _objc_msgSend(IVar4,"setLastConnectedPortName:",0);
        *(undefined8 *)(IVar4 + _TtC8Playback7MIDIBus::privateDestinationEndpoint) = 0;
        _objc_msgSend(IVar4,"setChannel:",1);
        pcVar11 = "setAllChannels:";
        _objc_msgSend(IVar4,"setAllChannels:",0);
        lVar15 = lVar15 + -1;
        pbVar13 = pbVar13 + 1;
      } while (lVar15 != 0);
    }
  }
  if (*(long *)PTR____stack_chk_guard_100a1d8f0 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

// ==== 10049fd44 FUN_10049fd44 ====
void FUN_10049fd44(void)

{
  FUN_10049fd84(&_TtC8Playback18MIDIOutAVAudioUnit::startTime,2);
  return;
}

// ==== 10049fd54 FUN_10049fd54 ====
void FUN_10049fd54(void)

{
  FUN_10049fd84(&_TtC8Playback18MIDIOutAVAudioUnit::endTime,3);
  return;
}

// ==== 10049fd64 FUN_10049fd64 ====
void FUN_10049fd64(void)

{
  FUN_10049fd84(&_TtC8Playback18MIDIOutAVAudioUnit::enqueuedStartTime,4);
  return;
}

// ==== 10049fd74 FUN_10049fd74 ====
void FUN_10049fd74(void)

{
  FUN_10049fd84(&_TtC8Playback18MIDIOutAVAudioUnit::enqueuedEndTime,5);
  return;
}

// ==== 10049fd84 FUN_10049fd84 ====
void FUN_10049fd84(undefined8 param_1,long *param_2,long param_3)

{
  undefined1 *puVar1;
  long unaff_x20;
  long lVar2;
  ID self;
  long lVar3;
  undefined1 auStack_48 [24];
  
  lVar3 = *param_2;
  *(undefined8 *)(unaff_x20 + lVar3) = param_1;
  lVar2 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  puVar1 = auStack_48;
  _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,puVar1,0x20,0);
  lVar2 = *(long *)(unaff_x20 + lVar2);
  if ((*(long *)(lVar2 + 0x10) == 0) || (thunk_FUN_100793c60(), ((ulong)puVar1 & 1) == 0)) {
    _swift_endAccess(auStack_48);
  }
  else {
    self = *(ID *)(*(long *)(lVar2 + 0x38) + param_3 * 8);
    _swift_endAccess(auStack_48);
    _objc_msgSend(self,"setValue:",(ulong)(uint)(float)*(double *)(unaff_x20 + lVar3));
  }
  return;
}

// ==== 10049fe84 FUN_10049fe84 ====
void FUN_10049fe84(void)

{
  long lVar1;
  undefined1 *puVar2;
  ID IVar3;
  undefined8 uVar4;
  long unaff_x20;
  long lVar5;
  undefined1 auStack_48 [24];
  
  lVar5 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  puVar2 = auStack_48;
  if (*(char *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::playState) == '\x01') {
    _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,puVar2,0x20,0);
    lVar5 = *(long *)(unaff_x20 + lVar5);
    if (*(long *)(lVar5 + 0x10) != 0) {
      lVar1 = 1;
      thunk_FUN_100793c60();
      if (((ulong)puVar2 & 1) != 0) {
        IVar3 = *(ID *)(*(long *)(lVar5 + 0x38) + lVar1 * 8);
        _swift_endAccess(auStack_48);
        _objc_msgSend(IVar3,"setValue:",0x3f800000);
        return;
      }
    }
    _swift_endAccess(auStack_48);
  }
  else {
    _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,puVar2,0x20,0);
    lVar5 = *(long *)(unaff_x20 + lVar5);
    if (*(long *)(lVar5 + 0x10) == 0) {
      _swift_endAccess(auStack_48);
    }
    else {
      lVar1 = 1;
      thunk_FUN_100793c60();
      if (((ulong)puVar2 & 1) == 0) {
        _swift_endAccess(auStack_48);
      }
      else {
        IVar3 = *(ID *)(*(long *)(lVar5 + 0x38) + lVar1 * 8);
        _swift_endAccess(auStack_48);
        _objc_msgSend(IVar3,"setValue:",0);
      }
    }
    lVar5 = _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents;
    _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents,auStack_48
                       ,1,0);
    uVar4 = *(undefined8 *)(unaff_x20 + lVar5);
    *(undefined **)(unaff_x20 + lVar5) = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    _swift_bridgeObjectRelease(uVar4);
  }
  return;
}

// ==== 10049ffc8 FUN_10049ffc8 ====
void FUN_10049ffc8(void)

{
  long lVar1;
  undefined1 *puVar2;
  long unaff_x20;
  long lVar3;
  ID self;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined1 auStack_48 [24];
  
  lVar3 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  puVar2 = auStack_48;
  _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,puVar2,0x20,0);
  lVar3 = *(long *)(unaff_x20 + lVar3);
  if (*(long *)(lVar3 + 0x10) != 0) {
    lVar1 = 0;
    thunk_FUN_100793c60();
    if (((ulong)puVar2 & 1) != 0) {
      self = *(ID *)(*(long *)(lVar3 + 0x38) + lVar1 * 8);
      _swift_endAccess(auStack_48);
      uVar5 = 0x3f800000;
      if (*(char *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) == '\0') {
        uVar5 = 0;
      }
      _objc_msgSend(self,"setValue:",uVar5);
      goto LAB_1004a005c;
    }
  }
  _swift_endAccess(auStack_48);
LAB_1004a005c:
  lVar3 = _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents;
  if ((*(byte *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) & 1) == 0) {
    _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents,auStack_48
                       ,1,0);
    uVar4 = *(undefined8 *)(unaff_x20 + lVar3);
    *(undefined **)(unaff_x20 + lVar3) = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    _swift_bridgeObjectRelease(uVar4);
  }
  return;
}

// ==== 1004a00b4 FUN_1004a00b4 ====
void FUN_1004a00b4(void)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long unaff_x20;
  undefined1 auStack_48 [24];
  
  _swift_getObjectType();
  lVar2 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,auStack_48,1,0);
  puVar1 = PTR___swiftEmptyDictionarySingleton_100a1e058;
  uVar3 = *(undefined8 *)(unaff_x20 + lVar2);
  *(undefined **)(unaff_x20 + lVar2) = PTR___swiftEmptyDictionarySingleton_100a1e058;
  _swift_bridgeObjectRelease(uVar3);
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::parameterObserverToken) = 0;
  _swift_retain(puVar1);
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa8,"dealloc");
  return;
}

// ==== 1004a0144 _TtC8Playback18MIDIOutAVAudioUnit::dealloc ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback18MIDIOutAVAudioUnit::dealloc(ID param_1,SEL param_2)

{
  undefined *puVar1;
  long lVar2;
  class_t *pcVar3;
  undefined8 uVar4;
  objc_super local_68;
  undefined1 auStack_58 [24];
  
  pcVar3 = (class_t *)param_1;
  _swift_getObjectType();
  lVar2 = parameters;
  _swift_beginAccess(param_1 + parameters,auStack_58,1,0);
  puVar1 = PTR___swiftEmptyDictionarySingleton_100a1e058;
  uVar4 = *(undefined8 *)(param_1 + lVar2);
  *(undefined **)(param_1 + lVar2) = PTR___swiftEmptyDictionarySingleton_100a1e058;
  _swift_bridgeObjectRelease(uVar4);
  *(undefined8 *)(param_1 + parameterObserverToken) = 0;
  local_68.receiver = param_1;
  local_68.super_class = pcVar3;
  _swift_retain(puVar1);
  _objc_msgSendSuper2(&local_68,"dealloc");
  return;
}

// ==== 1004a01ec _TtC8Playback18MIDIOutAVAudioUnit::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback18MIDIOutAVAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + midiEvents));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + currentNoteOnEvents));
  FUN_100026610(param_1 + delegate);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + parameters));
  return;
}

// ==== 1004a0244 FUN_1004a0244 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1004a0244(void)

{
  long lVar1;
  code *pcVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined *puVar5;
  ID IVar6;
  ID unaff_x20;
  ulong uVar7;
  long *plVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  
  puVar3 = (undefined *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::delegate);
  _swift_unknownObjectWeakLoadStrong();
  if (puVar3 != (undefined *)0x0) {
    puVar5 = puVar3;
    FUN_1001b3248();
    _swift_unknownObjectRelease(puVar3);
    if (puVar5 != (undefined *)0x0) goto LAB_1004a02ac;
  }
  puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_1004a02ac:
  lVar1 = _TtC8Playback18MIDIOutAVAudioUnit::midiEvents;
  uVar4 = *(undefined8 *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
  *(undefined **)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents) = puVar5;
  _swift_bridgeObjectRelease(uVar4);
  uVar7 = *(ulong *)(unaff_x20 + lVar1);
  if (uVar7 >> 0x3e == 0) {
    uVar9 = *(ulong *)((uVar7 & 0xfffffffffffff8) + 0x10);
    puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    uVar9 = uVar7 & 0xffffffffffffff8;
    if ((long)uVar7 < 0) {
      uVar9 = uVar7;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar3;
  if (uVar9 == 0) {
    _swift_retain(puVar3);
  }
  else {
    _swift_retain();
    _swift_bridgeObjectRetain(uVar7);
    FUN_1001ccaac(0,uVar9 & ((long)uVar9 >> 0x3f ^ 0xffffffffffffffffU),0);
    if ((long)uVar9 < 0) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a0590);
      (*pcVar2)();
    }
    uVar10 = 0;
    do {
      if ((uVar7 & 0xc000000000000001) == 0) {
        uVar11 = *(ulong *)(uVar7 + uVar10 * 8 + 0x20);
        _swift_retain(uVar11);
      }
      else {
        uVar11 = uVar10;
        FUN_1000cc70c(uVar10,uVar7);
      }
      uVar4 = *(undefined8 *)(uVar11 + 0x28);
      puVar5 = &_OBJC_CLASS___NSNumber;
      _objc_allocWithZone();
      IVar6 = _objc_msgSend((ID)puVar5,"initWithDouble:",uVar4);
      _swift_release(uVar11);
      uVar11 = *(ulong *)(puVar3 + 0x10);
      if (*(ulong *)(puVar3 + 0x18) >> 1 <= uVar11) {
        FUN_1001ccaac(1 < *(ulong *)(puVar3 + 0x18),uVar11 + 1,1);
      }
      uVar10 = uVar10 + 1;
      *(ulong *)(puVar3 + 0x10) = uVar11 + 1;
      *(ID *)(puVar3 + uVar11 * 8 + 0x20) = IVar6;
    } while (uVar9 != uVar10);
    _swift_bridgeObjectRelease(uVar7);
  }
  IVar6 = _objc_msgSend(unaff_x20,"AUAudioUnit");
  puVar5 = &_OBJC_CLASS___MIDIOutAudioUnit;
  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
  _swift_dynamicCastObjCClass(IVar6,puVar5);
  if (IVar6 == 0) {
    _swift_bridgeObjectRelease(puVar3);
  }
  else {
    uVar4 = 0;
    FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
    puVar5 = puVar3;
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar3,uVar4);
    _swift_bridgeObjectRelease(puVar3);
    _objc_msgSend(IVar6,"updateEventTimes:",puVar5);
  }
  uVar7 = 0;
  FUN_1004303d8();
  if (uVar7 == 0) {
    return;
  }
  if (uVar7 >> 0x3e == 0) {
    uVar9 = *(ulong *)((uVar7 & 0xffffffffffffff8) + 0x10);
  }
  else {
    uVar9 = uVar7;
    if (-1 < (long)uVar7) {
      uVar9 = uVar7 & 0xffffffffffffff8;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar9 != 0) {
    if ((long)uVar9 < 1) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a05ac);
      (*pcVar2)();
    }
    if ((uVar7 & 0xc000000000000001) == 0) {
      _swift_bridgeObjectRetain(uVar7);
      plVar8 = (long *)(uVar7 + 0x20);
      do {
        *(undefined8 *)(*plVar8 + _TtC8Playback7MIDIBus::privateDestinationEndpoint) = 0;
        uVar9 = uVar9 - 1;
        plVar8 = plVar8 + 1;
      } while (uVar9 != 0);
    }
    else {
      _swift_bridgeObjectRetain(uVar7);
      uVar10 = 0;
      do {
        uVar11 = uVar10;
        FUN_1000cc6c0(uVar10,uVar7);
        uVar10 = uVar10 + 1;
        *(undefined8 *)(uVar11 + _TtC8Playback7MIDIBus::privateDestinationEndpoint) = 0;
        _swift_unknownObjectRelease();
      } while (uVar9 != uVar10);
    }
    _swift_bridgeObjectRelease(uVar7);
  }
  _swift_bridgeObjectRelease(uVar7);
  return;
}

// ==== 1004a0c04 _TtC8Playback18MIDIOutAVAudioUnit::initWithAudioComponentDescription: ====
/* Function Stack Size: 0x24 bytes */

ID _TtC8Playback18MIDIOutAVAudioUnit::initWithAudioComponentDescription_
             (ID param_1,SEL param_2,AudioComponentDescription param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.MIDIOutAVAudioUnit",0x1b,"init(audioComponentDescription:)",0x20,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1004a0c30);
  (*pcVar1)();
}

// ==== 1004a0c30 _TtC8Playback18MIDIOutAVAudioUnit::init ====
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback18MIDIOutAVAudioUnit::init(ID param_1,SEL param_2)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer("Playback.MIDIOutAVAudioUnit",0x1b,"init()",6,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1004a0c5c);
  (*pcVar1)();
}

// ==== 1004a0c5c FUN_1004a0c5c ====
void FUN_1004a0c5c(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback18MIDIOutAVAudioUnit);
  return;
}

// ==== 1004a0c7c _TtC8Playback18MIDIOutAVAudioUnit::midiOutAudioUnit:requestsMIDIEventOutputAtIndex:isPrerolled:isRewound: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void _TtC8Playback18MIDIOutAVAudioUnit::
     midiOutAudioUnit_requestsMIDIEventOutputAtIndex_isPrerolled_isRewound_
               (ID param_1,SEL param_2,ID param_3,long_long param_4,bool param_5,bool param_6)

{
  FUN_1004a1188(param_4,param_5,param_6);
  return;
}

// ==== 1004a1188 FUN_1004a1188 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001004a1e7c) */

void FUN_1004a1188(ulong param_1,ulong param_2,ulong param_3)

{
  char *pcVar1;
  code *pcVar2;
  uint uVar3;
  ulong uVar4;
  ID IVar5;
  ID IVar6;
  ID IVar7;
  ID IVar8;
  char *pcVar9;
  ulong uVar10;
  char *self;
  undefined *puVar11;
  undefined8 uVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  char *pcVar17;
  undefined *puVar18;
  ulong uVar19;
  long unaff_x20;
  long lVar20;
  long lVar21;
  int iVar22;
  int iVar23;
  ulong uVar24;
  long lVar25;
  char *pcVar26;
  undefined1 auStack_158 [24];
  ulong local_140 [28];
  ID IVar12;
  
  lVar21 = _TtC8Playback18MIDIOutAVAudioUnit::midiEvents;
  uVar24 = *(ulong *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
  if (uVar24 >> 0x3e == 0) {
    uVar4 = *(ulong *)((uVar24 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar4 = uVar24 & 0xffffffffffffff8;
    if ((long)uVar24 < 0) {
      uVar4 = uVar24;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if ((long)uVar4 < 0) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a1978);
      (*pcVar2)();
    }
  }
  if (uVar4 <= param_1) {
    __sSo13os_log_type_ta0A0E7defaultABvgZ();
    puVar11 = &DAT_100af52c8;
    FUN_100021774();
    _swift_initStackObject();
    *(undefined8 *)(puVar11 + 0x18) = 4;
    *(undefined8 *)(puVar11 + 0x10) = 2;
    puVar14 = PTR___sSiN_100a1dd88;
    puVar18 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
    local_140[0] = param_1;
    __ss23CustomStringConvertibleP11descriptionSSvgTj();
    puVar16 = PTR___sSSN_100a1dce0;
    *(undefined **)(puVar11 + 0x38) = PTR___sSSN_100a1dce0;
    puVar15 = puVar14;
    FUN_100026528();
    *(undefined **)(puVar11 + 0x20) = puVar14;
    *(undefined **)(puVar11 + 0x40) = puVar15;
    *(undefined **)(puVar11 + 0x28) = puVar18;
    uVar24 = *(ulong *)(unaff_x20 + lVar21);
    if (uVar24 >> 0x3e == 0) {
      uVar19 = *(ulong *)((uVar24 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar19 = uVar24 & 0xffffffffffffff8;
      if ((long)uVar24 < 0) {
        uVar19 = uVar24;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    puVar14 = PTR___sSiN_100a1dd88;
    puVar18 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
    local_140[0] = uVar19;
    __ss23CustomStringConvertibleP11descriptionSSvgTj();
    *(undefined **)(puVar11 + 0x60) = puVar16;
    *(undefined **)(puVar11 + 0x68) = puVar15;
    *(undefined **)(puVar11 + 0x48) = puVar14;
    *(undefined **)(puVar11 + 0x50) = puVar18;
    FUN_10041ac94(uVar4,0x34,
                  "Invalid MIDI Event index requested %{public}@ - MIDI Event count %{public}@",0x4b
                  ,2,puVar11);
    _swift_setDeallocating(puVar11);
    puVar16 = &DAT_100af5bc8;
    FUN_100021774(&DAT_100af5bc8);
    _swift_arrayDestroy(puVar11 + 0x20,2,puVar16);
    return;
  }
  if ((uVar24 & 0xc000000000000001) == 0) {
    if (*(ulong *)((uVar24 & 0xfffffffffffff8) + 0x10) <= param_1) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a19a8);
      (*pcVar2)();
    }
    param_1 = *(ulong *)(uVar24 + param_1 * 8 + 0x20);
    uVar24 = param_1;
    _swift_retain();
    if ((param_2 & 1) != 0) goto LAB_1004a120c;
LAB_1004a1208:
    if ((param_3 & 1) != 0) goto LAB_1004a120c;
  }
  else {
    _swift_bridgeObjectRetain(uVar24);
    FUN_1000cc70c(param_1,uVar24);
    _swift_bridgeObjectRelease();
    if ((param_2 & 1) == 0) goto LAB_1004a1208;
LAB_1004a120c:
    if (*(char *)(param_1 + 0x38) == '\x01') {
      _swift_release(param_1);
      return;
    }
  }
  lVar21 = _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents;
  if (*(char *)(param_1 + 0x18) == '\x02') {
    FUN_10021453c();
    if (uVar24 != 0) {
      puVar11 = &_OBJC_CLASS___MIKMIDINoteOffCommand;
      _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDINoteOffCommand);
      _swift_dynamicCastObjCClass(uVar24,puVar11);
      if (uVar24 != 0) {
        IVar12 = _objc_msgSend(uVar24,"note");
        IVar5 = _objc_msgSend(uVar24,"velocity");
        IVar6 = _objc_msgSend(uVar24,"channel");
        puVar11 = &_OBJC_CLASS___MIKMIDINoteOnCommand;
        _swift_getInitializedObjCClass();
        IVar12 = _objc_msgSend((ID)puVar11,"noteOnCommandWithNote:velocity:channel:timestamp:",
                               IVar12,IVar5,IVar6,0);
        lVar21 = _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents;
        if (IVar12 != 0) {
          _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents,
                             auStack_158,0,0);
          uVar24 = *(ulong *)(unaff_x20 + lVar21);
          if (uVar24 >> 0x3e == 0) {
            uVar4 = *(ulong *)((uVar24 & 0xfffffffffffff8) + 0x10);
          }
          else {
            uVar4 = uVar24 & 0xffffffffffffff8;
            if ((long)uVar24 < 0) {
              uVar4 = uVar24;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg();
          }
          if (uVar4 != 0) {
            _swift_bridgeObjectRetain_n(uVar24,2);
            lVar25 = 0;
            do {
              if ((uVar24 & 0xc000000000000001) == 0) {
                lVar20 = *(long *)(uVar24 + lVar25 * 8 + 0x20);
                _swift_retain(lVar20);
              }
              else {
                lVar20 = lVar25;
                FUN_1000cc70c(lVar25,uVar24);
              }
              uVar19 = lVar25 + 1;
              if (SCARRY8(lVar25,1)) {
                    /* WARNING: Does not return */
                pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a19ac);
                (*pcVar2)();
              }
              IVar5 = IVar12;
              FUN_10021453c();
              if (IVar5 == 0) {
                _swift_bridgeObjectRelease_n(uVar24,2);
LAB_1004a189c:
                _swift_release(lVar20);
                goto LAB_1004a1a10;
              }
              puVar11 = &_OBJC_CLASS___MIKMIDINoteOnCommand;
              _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDINoteOnCommand);
              IVar6 = IVar12;
              _swift_dynamicCastObjCClass(IVar12,puVar11);
              if (IVar6 == 0) {
LAB_1004a15b4:
                puVar11 = &_OBJC_CLASS___MIKMIDINoteOffCommand;
                _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDINoteOffCommand);
                IVar6 = IVar12;
                _swift_dynamicCastObjCClass(IVar12,puVar11);
                if (IVar6 == 0) {
LAB_1004a16b8:
                  puVar11 = &_OBJC_CLASS___MIKMIDIControlChangeCommand;
                  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDIControlChangeCommand);
                  IVar6 = IVar12;
                  _swift_dynamicCastObjCClass(IVar12,puVar11);
                  if (IVar6 != 0) {
                    puVar11 = &_OBJC_CLASS___MIKMIDIControlChangeCommand;
                    _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDIControlChangeCommand);
                    IVar7 = IVar5;
                    _swift_dynamicCastObjCClass(IVar5,puVar11);
                    if (IVar7 != 0) {
                      IVar5 = _objc_msgSend(IVar6,"controllerNumber");
                      IVar8 = _objc_msgSend(IVar7,"controllerNumber");
                      if (IVar5 == IVar8) {
                        IVar5 = _objc_msgSend(IVar6,"controllerValue");
                        IVar6 = _objc_msgSend(IVar7,"controllerValue");
                        _swift_release(lVar20);
                        if (IVar5 == IVar6) goto LAB_1004a18d0;
                        goto LAB_1004a1450;
                      }
                      goto LAB_1004a1878;
                    }
                  }
                  puVar11 = &_OBJC_CLASS___MIKMIDIProgramChangeCommand;
                  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDIProgramChangeCommand);
                  IVar6 = IVar12;
                  _swift_dynamicCastObjCClass(IVar12,puVar11);
                  if (IVar6 == 0) {
                    _swift_bridgeObjectRelease_n(uVar24,2);
                    goto LAB_1004a189c;
                  }
                  puVar11 = &_OBJC_CLASS___MIKMIDIProgramChangeCommand;
                  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDIProgramChangeCommand);
                  _swift_dynamicCastObjCClass(IVar5,puVar11);
                  if (IVar5 == 0) {
                    _swift_release(lVar20);
                    break;
                  }
                  IVar6 = _objc_msgSend(IVar6,"programNumber");
                  IVar5 = _objc_msgSend(IVar5,"programNumber");
                  _swift_release(lVar20);
                  if (IVar6 == IVar5) goto LAB_1004a18d0;
                }
                else {
                  puVar11 = &_OBJC_CLASS___MIKMIDINoteOffCommand;
                  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDINoteOffCommand);
                  IVar7 = IVar5;
                  _swift_dynamicCastObjCClass(IVar5,puVar11);
                  if (IVar7 == 0) goto LAB_1004a16b8;
                  IVar5 = _objc_msgSend(IVar6,"note");
                  IVar8 = _objc_msgSend(IVar7,"note");
                  if (IVar5 == IVar8) {
                    _objc_msgSend(IVar6,"velocity");
                    _objc_msgSend(IVar7,"velocity");
                    IVar5 = _objc_msgSend(IVar6,"channel");
                    iVar22 = (int)IVar5;
                    IVar5 = _objc_msgSend(IVar7,"channel");
                    iVar23 = (int)IVar5;
                    _swift_release(lVar20);
                    goto LAB_1004a16a8;
                  }
LAB_1004a1878:
                  _swift_release(lVar20);
                }
              }
              else {
                puVar11 = &_OBJC_CLASS___MIKMIDINoteOnCommand;
                _swift_getInitializedObjCClass(&_OBJC_CLASS___MIKMIDINoteOnCommand);
                IVar7 = IVar5;
                _swift_dynamicCastObjCClass(IVar5,puVar11);
                if (IVar7 == 0) goto LAB_1004a15b4;
                IVar5 = _objc_msgSend(IVar6,"note");
                IVar8 = _objc_msgSend(IVar7,"note");
                if (IVar5 == IVar8) {
                  _objc_msgSend(IVar6,"velocity");
                  _objc_msgSend(IVar7,"velocity");
                  IVar5 = _objc_msgSend(IVar6,"channel");
                  iVar22 = (int)IVar5;
                  IVar5 = _objc_msgSend(IVar7,"channel");
                  iVar23 = (int)IVar5;
                  _swift_release(lVar20);
LAB_1004a16a8:
                  if (iVar22 != iVar23) goto LAB_1004a1450;
LAB_1004a18d0:
                  _swift_bridgeObjectRelease_n(uVar24,2);
                  _swift_beginAccess(unaff_x20 + lVar21,local_140,0x21,0);
                  FUN_100033e6c(lVar25);
                  _swift_endAccess(local_140);
                  _swift_release(lVar25);
                  goto LAB_1004a1a10;
                }
                _swift_release(lVar20);
              }
LAB_1004a1450:
              lVar25 = lVar25 + 1;
            } while (uVar19 != uVar4);
            _swift_bridgeObjectRelease_n(uVar24,2);
          }
        }
      }
    }
  }
  else if (*(char *)(param_1 + 0x18) == '\x01') {
    _swift_beginAccess(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents,local_140,
                       0x21,0);
    _swift_retain(param_1);
    lVar25 = unaff_x20 + lVar21;
    FUN_1004a0dbc(lVar25,param_1);
    _swift_release(param_1);
    uVar24 = *(ulong *)(unaff_x20 + lVar21);
    if (uVar24 >> 0x3e == 0) {
      uVar4 = *(ulong *)((uVar24 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar4 = uVar24 & 0xffffffffffffff8;
      if ((long)uVar24 < 0) {
        uVar4 = uVar24;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if ((long)uVar4 < lVar25) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a19cc);
      (*pcVar2)();
    }
    FUN_1001d4640(lVar25);
    _swift_endAccess(local_140);
    _swift_beginAccess(unaff_x20 + lVar21,local_140,0x21,0);
    _swift_retain(param_1);
    FUN_100794d28();
    uVar4 = *(ulong *)(unaff_x20 + lVar21);
    uVar19 = uVar4 & 0xffffffffffffff8;
    uVar24 = *(ulong *)(uVar19 + 0x10);
    if (*(ulong *)(uVar19 + 0x18) >> 1 <= uVar24) {
      uVar4 = (ulong)(1 < *(ulong *)(uVar19 + 0x18));
      FUN_10078e3e0(uVar4,uVar24 + 1,1);
      uVar19 = uVar4 & 0xffffffffffffff8;
    }
    *(ulong *)(uVar19 + 0x10) = uVar24 + 1;
    *(ulong *)(uVar19 + uVar24 * 8 + 0x20) = param_1;
    *(ulong *)(unaff_x20 + lVar21) = uVar4;
    _swift_endAccess(local_140);
  }
LAB_1004a1a10:
  if (*(char *)(unaff_x20 + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) == '\x01')
  goto LAB_1004a1e70;
  uVar24 = *(ulong *)(param_1 + 0x40);
  pcVar9 = (char *)0x0;
  if (uVar24 != 0) {
    uVar4 = uVar24;
    FUN_10042f27c();
    lVar21 = _TtC8Playback7MIDIBus::privateDestinationEndpoint;
    if ((uVar4 >> 0x20 & 1) == 0) {
      pcVar9 = *(char **)(uVar24 + _TtC8Playback7MIDIBus::privateDestinationEndpoint);
      self = pcVar9;
      if (pcVar9 == (char *)0x0) {
        if (DAT_100adefa0 != -1) {
          _swift_once(&DAT_100adefa0,FUN_10037c47c);
        }
        uVar19 = DAT_100b75f50;
        uVar10 = DAT_100b75f50;
        _swift_retain();
        FUN_10042f27c();
        self = (char *)(uVar10 & 0xffffffff | (uVar10 >> 0x20 & 1) << 0x20);
        FUN_1003824b4();
        _swift_release(uVar19);
        *(char **)(uVar24 + lVar21) = self;
        uVar24 = DAT_100b75f50;
        if (self == (char *)0x0) {
          _swift_beginAccess(DAT_100b75f50 + 0x18,local_140,0,0);
          pcVar9 = *(char **)(uVar24 + 0x18);
          if ((ulong)pcVar9 >> 0x3e == 0) {
            pcVar17 = *(char **)(((ulong)pcVar9 & 0xfffffffffffff8) + 0x10);
          }
          else {
            pcVar17 = (char *)((ulong)pcVar9 & 0xffffffffffffff8);
            if ((long)pcVar9 < 0) {
              pcVar17 = pcVar9;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg();
          }
          if (pcVar17 != (char *)0x0) {
            _swift_bridgeObjectRetain_n(pcVar9,2);
            _swift_retain(uVar24);
            lVar21 = 4;
            do {
              pcVar26 = (char *)(lVar21 - 4);
              if (((ulong)pcVar9 & 0xc000000000000001) == 0) {
                self = *(char **)(pcVar9 + lVar21 * 8);
              }
              else {
                self = pcVar26;
                FUN_1000cc280(pcVar26,pcVar9);
              }
              pcVar1 = (char *)(lVar21 + -3);
              if (SCARRY8((long)pcVar26,1)) {
                    /* WARNING: Does not return */
                pcVar2 = (code *)SoftwareBreakpoint(1,0x1004a1cd8);
                (*pcVar2)();
              }
              IVar12 = _objc_msgSend((ID)self,"uniqueID");
              if ((int)IVar12 == (int)uVar4) {
                _swift_release(uVar24);
                _swift_bridgeObjectRelease_n(pcVar9,2);
                goto LAB_1004a1acc;
              }
              lVar21 = lVar21 + 1;
            } while (pcVar1 != pcVar17);
            _swift_release(uVar24);
            _swift_bridgeObjectRelease_n(pcVar9,2);
            goto LAB_1004a1de0;
          }
          goto LAB_1004a1ddc;
        }
        pcVar9 = (char *)0x0;
      }
LAB_1004a1acc:
      FUN_100214824();
      if (pcVar9 != (char *)0x0) {
        puVar11 = &_OBJC_CLASS___UIDevice;
        _swift_getInitializedObjCClass();
        IVar12 = _objc_msgSend((ID)puVar11,"currentDevice");
        uVar3 = (uint)IVar12;
        FUN_100826a8c();
        if ((uVar3 & 0xff) != 1) {
LAB_1004a1d08:
          pcVar17 = pcVar9;
          if ((ulong)pcVar9 >> 0x3e == 0) {
            _swift_bridgeObjectRetain(pcVar9);
            __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
            FUN_100023404(0,&DAT_100af7870,&PTR__OBJC_CLASS___MIKMIDICommand_100aa3fb0);
          }
          else {
            if (-1 < (long)pcVar9) {
              pcVar17 = (char *)((ulong)pcVar9 & 0xffffffffffffff8);
            }
            uVar13 = 0;
            FUN_100023404(0,&DAT_100af7870,&PTR__OBJC_CLASS___MIKMIDICommand_100aa3fb0);
            _swift_bridgeObjectRetain(pcVar9);
            __ss17_bridgeCocoaArrayySayxGyXllF(pcVar17,uVar13);
            _swift_bridgeObjectRelease(pcVar9);
          }
          _swift_bridgeObjectRelease(pcVar9);
          FUN_1004a05ac(pcVar17,self);
          _swift_release(param_1);
          _swift_bridgeObjectRelease(pcVar17);
          return;
        }
        pcVar17 = "displayName";
        uVar24 = _objc_msgSend((ID)self,"displayName");
        if (uVar24 == 0) {
          uVar24 = 0;
          pcVar17 = (char *)0x0;
        }
        else {
          __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
        }
        if (DAT_100adec20 != -1) {
          _swift_once(&DAT_100adec20,FUN_1001fd928);
        }
        if (pcVar17 == (char *)0x0) goto LAB_1004a1d08;
        if ((uVar24 == DAT_100b75a00) && (pcVar17 == DAT_100b75a08)) {
          _swift_bridgeObjectRelease(pcVar9);
          pcVar9 = pcVar17;
        }
        else {
          __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                    (uVar24,pcVar17,DAT_100b75a00,DAT_100b75a08,0);
          _swift_bridgeObjectRelease(pcVar17);
          if ((uVar24 & 1) == 0) goto LAB_1004a1d08;
        }
        _swift_bridgeObjectRelease(pcVar9);
        goto LAB_1004a1e70;
      }
    }
LAB_1004a1ddc:
    pcVar9 = (char *)0x0;
  }
LAB_1004a1de0:
  __sSo13os_log_type_ta0A0E7defaultABvgZ();
  puVar11 = &DAT_100af52c8;
  FUN_100021774();
  _swift_initStackObject();
  *(undefined8 *)(puVar11 + 0x18) = 2;
  *(undefined8 *)(puVar11 + 0x10) = 1;
  uVar19 = (ulong)*(byte *)(param_1 + 0x18);
  uVar4 = (ulong)*(ushort *)(param_1 + 0x1c);
  FUN_1000276f0();
  *(undefined **)(puVar11 + 0x38) = PTR___sSSN_100a1dce0;
  uVar24 = uVar4;
  FUN_100026528();
  *(ulong *)(puVar11 + 0x40) = uVar24;
  *(ulong *)(puVar11 + 0x20) = uVar4;
  *(ulong *)(puVar11 + 0x28) = uVar19;
  FUN_10041ac94(pcVar9,0x34,"Command could not be created for MIDI event: %{public}@",0x37,2,puVar11
               );
  _swift_setDeallocating(puVar11);
  FUN_100023468(puVar11 + 0x20);
LAB_1004a1e70:
  _swift_release(param_1);
  return;
}

// ==== 1004a2024 FUN_1004a2024 ====
void FUN_1004a2024(void)

{
  long lVar1;
  long unaff_x20;
  
  lVar1 = *(long *)(unaff_x20 + 0x10) + _TtC8Playback18MIDIOutAVAudioUnit::delegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar1 != 0) {
    _swift_unknownObjectRelease();
    return;
  }
  return;
}

// ==== 1004f5388 FUN_1004f5388 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_1004f5388(double param_1,byte param_2)

{
  ulong uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  ID IVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  void *pvVar12;
  undefined *puVar13;
  ulong uVar14;
  code *pcVar15;
  ID IVar16;
  undefined *puVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  ulong uVar20;
  ID IVar21;
  long *plVar22;
  uint uVar23;
  long lVar24;
  undefined *unaff_x20;
  long lVar25;
  ID IVar26;
  byte bVar27;
  long lVar28;
  uint uVar29;
  long lVar30;
  ID IVar31;
  long lVar32;
  code *pcVar33;
  ulong uVar34;
  long lVar35;
  double dVar36;
  double dVar37;
  double dVar38;
  undefined8 auStack_240 [2];
  long local_230;
  ID local_228;
  ID local_220;
  undefined8 local_218;
  code *local_210;
  code *local_208;
  undefined8 *local_200;
  long local_1f8;
  ID local_1f0;
  long local_1e8;
  undefined *local_1e0;
  long local_1d8;
  undefined *local_1d0;
  ID local_1c8;
  ID local_1c0;
  code *local_1b8;
  undefined8 *local_1b0;
  long local_1a8;
  long local_1a0;
  long local_198;
  ID local_190;
  long local_188;
  long local_180;
  long local_178;
  long local_170;
  ID local_168;
  undefined1 local_158 [8];
  undefined8 local_150;
  undefined8 local_148;
  undefined1 auStack_140 [80];
  undefined1 auStack_f0 [32];
  undefined *local_d0;
  undefined8 local_c8;
  code *local_c0;
  undefined *puStack_b8;
  code *local_b0;
  undefined *local_a8;
  
  lVar3 = 0;
  __s8Dispatch0A4TimeVMa();
  lVar28 = *(long *)(lVar3 + -8);
  uVar20 = *(long *)(lVar28 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar35 = (long)&local_230 - uVar20;
  lVar30 = lVar35 - uVar20;
  lVar4 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar25 = *(long *)(lVar4 + -8);
  lVar32 = lVar30 - (*(long *)(lVar25 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  __s8Dispatch0A3QoSVMa();
  puVar6 = _TtC8Playback9Sequencer::privatePlayState;
  lVar24 = *(long *)(lVar5 + -8);
  IVar21 = lVar32 - (*(long *)(lVar24 + 0x40) + 0xfU & 0xfffffffffffffff0);
  local_168 = IVar21;
  if (unaff_x20[(long)_TtC8Playback9Sequencer::privatePlayState] == (param_2 & 1)) {
    puVar13 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar21 = _objc_msgSend((ID)puVar13,"sharedApplication");
    IVar21 = _objc_msgSend(IVar21,"delegate");
    if (IVar21 == 0) {
      return 0;
    }
    uVar11 = 0;
    FUN_100842dec(0);
    IVar31 = IVar21;
    _swift_dynamicCastClass(IVar21,uVar11);
    if (((IVar31 != 0) && (*(ID *)(IVar31 + _TtC8Playback11AppDelegate::window) != 0)) &&
       (IVar31 = _objc_msgSend(*(ID *)(IVar31 + _TtC8Playback11AppDelegate::window),
                               "rootViewController"), IVar31 != 0)) {
      uVar11 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar31,uVar11);
      _swift_unknownObjectRelease();
      if (IVar31 == 0) {
        return 0;
      }
      FUN_1003f8e38();
      lVar32 = *(long *)(IVar21 + 0x10);
      if (lVar32 == 0) {
        _swift_bridgeObjectRelease();
      }
      else {
        lVar30 = IVar21 + 0x20;
        _swift_retain();
        do {
          lVar3 = *(long *)(lVar30 + 0x20);
          FUN_100023444(lVar30,*(undefined8 *)(lVar30 + 0x18));
          (**(code **)(lVar3 + 8))();
          lVar30 = lVar30 + 0x28;
          lVar32 = lVar32 + -1;
        } while (lVar32 != 0);
        _swift_bridgeObjectRelease(IVar21);
        _swift_release();
      }
      puVar13 = &_OBJC_CLASS___NSNotificationCenter;
      _swift_getInitializedObjCClass();
      IVar21 = _objc_msgSend((ID)puVar13,"defaultCenter");
      if (DAT_100adeb68 != -1) {
        _swift_once(&DAT_100adeb68,FUN_1001f90a8);
      }
      _objc_msgSend(IVar21,"postNotificationName:object:",DAT_100b75930,0);
      return 0;
    }
    goto LAB_1004f5898;
  }
  local_1a8 = lVar35;
  local_180 = lVar24;
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar24 = *(long *)(DAT_100b75e40 + 0x18);
  if ((lVar24 == 0) ||
     (IVar31 = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::channelGroup), IVar31 == 0)) {
    unaff_x20[(long)puVar6] = 0;
    puVar13 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar31 = _objc_msgSend((ID)puVar13,"mainBundle");
    *(undefined8 *)(IVar21 - 0x10) = 0xe000000000000000;
    uVar11 = 0xd00000000000007c;
    IVar26 = 0x80000001008fb640;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd00000000000007c,0x80000001008fb640,0,0,IVar31,0,0xe000000000000000,0);
    puVar13 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar21 = _objc_msgSend((ID)puVar13,"sharedApplication");
    IVar21 = _objc_msgSend(IVar21,"delegate");
    if (IVar21 != 0) {
      uVar9 = 0;
      FUN_100842dec(0);
      IVar31 = IVar21;
      _swift_dynamicCastClass(IVar21,uVar9);
      if (((IVar31 == 0) || (*(ID *)(IVar31 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar31 = _objc_msgSend(*(ID *)(IVar31 + _TtC8Playback11AppDelegate::window),
                                 "rootViewController"), IVar31 == 0)) {
        _swift_bridgeObjectRelease(IVar26);
        goto LAB_1004f5898;
      }
      uVar9 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar31,uVar9);
      if (IVar31 == 0) {
        _swift_bridgeObjectRelease(IVar26);
        _swift_unknownObjectRelease(IVar21);
        return 0;
      }
      _swift_unknownObjectRelease(IVar21);
      if (DAT_100adef18 != -1) {
        _swift_once(&DAT_100adef18,FUN_1002c7b28);
      }
      uVar18 = DAT_100b75e58;
      uVar9 = DAT_100b75e50;
      _swift_bridgeObjectRetain(DAT_100b75e58);
      FUN_1003fe990(uVar9,uVar18,uVar11,IVar26,0,1);
      _swift_bridgeObjectRelease(uVar18);
    }
    _swift_bridgeObjectRelease(IVar26);
    return IVar26;
  }
  local_1b0 = puVar6;
  pcVar33 = *(code **)(unaff_x20 + _TtC8Playback9Sequencer::song);
  local_1e0 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar26 = *(ID *)(pcVar33 + (long)_TtC8Playback4Song::privateWorkingCopyArrangement);
  local_1b8 = pcVar33;
  local_1a0 = lVar25;
  local_198 = lVar4;
  local_188 = lVar24;
  local_178 = lVar5;
  local_170 = lVar32;
  if (IVar26 == 0) {
    local_1e8 = lVar30;
    _swift_retain();
    _swift_retain(IVar31);
    IVar26 = _objc_msgSend((ID)pcVar33,"workingCopyArrangementID");
    if (IVar26 != 0) {
      IVar16 = IVar26;
      FUN_10032ee88();
      IVar8 = IVar16;
      FUN_1005e3b94(IVar16,IVar26);
      local_1c8 = 0;
      _swift_bridgeObjectRelease(IVar16);
      if (IVar8 != 0) {
        *(ID *)(pcVar33 + (long)local_1e0) = IVar8;
        lVar30 = local_1e8;
        lVar32 = local_170;
        local_190 = IVar8;
        goto LAB_1004f5528;
      }
    }
    unaff_x20[(long)local_1b0] = 0;
    puVar13 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar26 = _objc_msgSend((ID)puVar13,"mainBundle");
    *(undefined8 *)(IVar21 - 0x10) = 0xe000000000000000;
    uVar18 = 0x80000001008fb6c0;
    uVar9 = 0xd000000000000016;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd000000000000016,0x80000001008fb6c0,0,0,IVar26,0,0xe000000000000000,0);
    IVar26 = _objc_msgSend((ID)puVar13,"mainBundle");
    *(undefined8 *)(IVar21 - 0x10) = 0xe000000000000000;
    uVar11 = 0xd000000000000074;
    uVar19 = 0x80000001008fb6e0;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd000000000000074,0x80000001008fb6e0,0,0,IVar26,0,0xe000000000000000,0);
    puVar13 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar21 = _objc_msgSend((ID)puVar13,"sharedApplication");
    IVar21 = _objc_msgSend(IVar21,"delegate");
    if (IVar21 != 0) {
      uVar10 = 0;
      FUN_100842dec(0);
      IVar26 = IVar21;
      _swift_dynamicCastClass(IVar21,uVar10);
      if (((IVar26 == 0) || (*(ID *)(IVar26 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar26 = _objc_msgSend(*(ID *)(IVar26 + _TtC8Playback11AppDelegate::window),
                                 "rootViewController"), IVar26 == 0)) {
        _swift_release(local_188);
        _swift_bridgeObjectRelease(uVar19);
        _swift_bridgeObjectRelease(uVar18);
        _swift_release(IVar31);
LAB_1004f5898:
        _swift_unknownObjectRelease(IVar21);
        return IVar21;
      }
      uVar10 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar26,uVar10);
      if (IVar26 == 0) {
        _swift_release(local_188);
        _swift_bridgeObjectRelease(uVar19);
        _swift_bridgeObjectRelease(uVar18);
        _swift_release(IVar31);
        _swift_unknownObjectRelease(IVar21);
        return 0;
      }
      _swift_unknownObjectRelease(IVar21);
      FUN_1003fe990(uVar9,uVar18,uVar11,uVar19,local_1b8,1);
    }
    _swift_release(local_188);
    _swift_bridgeObjectRelease(uVar19);
    _swift_bridgeObjectRelease(uVar18);
    _swift_release(IVar31);
    return IVar31;
  }
  _swift_retain();
  _swift_retain(IVar31);
  local_1c8 = 0;
  local_190 = IVar26;
LAB_1004f5528:
  if (DAT_100adfbb8 != -1) {
    _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
  }
  puVar13 = DAT_100b77548;
  uVar20 = *(ulong *)(DAT_100b77548 + 0x10);
  local_1d0 = DAT_100b77548;
  local_1f8 = lVar28;
  local_1d8 = lVar3;
  local_1c0 = IVar31;
  if (((uVar20 >> 0x3e == 2) &&
      (uVar14 = (uVar20 & 0x3fffffffffffffff) >> 3, (uVar14 | uVar20 << 0x3d) < 8)) &&
     ((1L << (uVar14 & 0x3f) & 0x97U) != 0)) {
    _swift_retain(DAT_100b77548);
    lVar3 = local_180;
  }
  else {
    FUN_10004cb08(0);
    _swift_retain(puVar13);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_b0 = FUN_100504acc;
    local_a8 = puVar13;
    local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
    param_1 = 5.47077039858234e-315;
    local_c8 = 0x42000000;
    local_c0 = FUN_10056b3d8;
    puStack_b8 = &DAT_100a4d908;
    pvVar12 = __Block_copy(&local_d0);
    puVar17 = local_a8;
    _swift_retain(puVar13);
    _swift_release(puVar17);
    IVar21 = local_168;
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_168);
    puVar17 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar6 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar13);
    puVar13 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar7 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar17);
    lVar32 = local_170;
    lVar3 = local_198;
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (local_170,&local_d0,puVar13,puVar7,local_198,puVar6);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,IVar21,lVar32,pvVar12);
    __Block_release(pvVar12);
    (**(code **)(local_1a0 + 8))(lVar32,lVar3);
    lVar3 = local_180;
    (**(code **)(local_180 + 8))(IVar21,local_178);
  }
  IVar21 = local_190;
  local_1f0 = CONCAT44(local_1f0._4_4_,(uint)(byte)unaff_x20[(long)local_1b0]);
  unaff_x20[(long)local_1b0] = param_2 & 1;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::songToLiveCrossfadeTo) = 0;
  uVar20 = 0;
  FUN_1002da1dc();
  pcVar33 = local_1b8;
  lVar4 = _TtC8Playback4Song::privateSongMap;
  if ((uVar20 & 1) == 0) {
    lVar5 = *(long *)(local_1b8 + _TtC8Playback4Song::privateSongMap);
    lVar32 = lVar5;
    if (lVar5 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar5 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar5 + 0x28) = 0;
      *(undefined8 *)(lVar5 + 0x20) = 0;
      *(undefined8 *)(lVar5 + 0x38) = 0;
      *(undefined8 *)(lVar5 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar5 + 0x10,pcVar33);
      _swift_retain(puVar13);
      FUN_10085ee38();
      uVar11 = *(undefined8 *)(pcVar33 + lVar4);
      *(long *)(pcVar33 + lVar4) = lVar5;
      _swift_retain(lVar5);
      _swift_release(uVar11);
      lVar32 = 0;
    }
    uVar20 = *(ulong *)(lVar5 + 0x18);
    _swift_retain(lVar32);
    _swift_bridgeObjectRetain(uVar20);
    _swift_release(lVar5);
    lVar32 = local_170;
    if (uVar20 >> 0x3e == 0) {
      uVar14 = *(ulong *)((uVar20 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar14 = uVar20 & 0xffffffffffffff8;
      if ((long)uVar20 < 0) {
        uVar14 = uVar20;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar14 == 0) {
      _swift_bridgeObjectRelease(uVar20);
      dVar36 = 1.0;
    }
    else {
      uVar34 = uVar14 - 1;
      if (SBORROW8(uVar14,1)) {
                    /* WARNING: Does not return */
        pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f763c);
        (*pcVar33)();
      }
      if ((uVar20 & 0xc000000000000001) == 0) {
        if ((long)uVar34 < 0) {
                    /* WARNING: Does not return */
          pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f7650);
          (*pcVar33)();
        }
        if (*(ulong *)((uVar20 & 0xfffffffffffff8) + 0x10) <= uVar34) {
                    /* WARNING: Does not return */
          pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f7654);
          (*pcVar33)();
        }
        uVar34 = *(ulong *)(uVar20 + uVar34 * 8 + 0x20);
        _swift_retain(uVar34);
      }
      else {
        FUN_1000cc314(uVar34,uVar20);
      }
      _swift_bridgeObjectRelease(uVar20);
      uVar29 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
      if ((uVar29 == 1) ||
         ((uVar29 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
        plVar22 = &_TtCC8Playback7SongMap7Element::fullTimelineEndTime;
      }
      else {
        plVar22 = &_TtCC8Playback7SongMap7Element::trimTimelineEndTime;
      }
      dVar36 = *(double *)(uVar34 + *plVar22);
      _swift_release(uVar34);
      dVar36 = dVar36 - *(double *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionBufferOffset)
      ;
    }
  }
  else {
    _objc_msgSend(IVar21,"storedEndTime");
    dVar36 = param_1;
    IVar21 = _objc_msgSend(IVar21,"song");
    pcVar33 = local_1b8;
    if (IVar21 == 0) {
      dVar36 = 1.0;
    }
    else {
      FUN_1003220ec();
    }
    dVar36 = param_1 * dVar36 -
             *(double *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionBufferOffset);
  }
  *(double *)(unaff_x20 + _TtC8Playback9Sequencer::autoLinkStartTime) = dVar36;
  if (*(long *)(DAT_100b75e40 + 0x28) == 0) {
    uVar29 = 0;
  }
  else {
    uVar29 = (uint)*(byte *)(*(long *)(DAT_100b75e40 + 0x28) +
                            (long)_TtC8Playback9Sequencer::privatePlayState);
  }
  if (unaff_x20[(long)local_1b0] == '\x01') {
    uVar11 = 0;
    FUN_10004cb08();
    local_218 = uVar11;
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_b0 = FUN_100504b04;
    local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_c8 = 0x42000000;
    local_c0 = FUN_10056b3d8;
    puStack_b8 = &DAT_100a4d9a8;
    local_a8 = unaff_x20;
    pvVar12 = __Block_copy(&local_d0);
    _swift_retain(unaff_x20);
    _swift_release(local_a8);
    IVar21 = local_168;
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_168);
    puVar17 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar6 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar13);
    puVar13 = &DAT_100af52b0;
    FUN_100021774();
    puVar7 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar17);
    lVar4 = local_198;
    local_200 = puVar7;
    local_1e0 = puVar13;
    local_1b0 = puVar6;
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (lVar32,&local_d0,puVar13,puVar7,local_198,puVar6);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,IVar21,lVar32,pvVar12);
    __Block_release(pvVar12);
    local_208 = *(code **)(local_1a0 + 8);
    (*local_208)(lVar32,lVar4);
    local_210 = *(code **)(lVar3 + 8);
    (*local_210)(IVar21,local_178);
    lVar3 = *(long *)(local_188 + 0x38);
    puVar13 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    _swift_retain(lVar3);
    IVar21 = _objc_msgSend((ID)puVar13,"currentDevice");
    uVar23 = (uint)IVar21;
    FUN_100826a8c();
    *(bool *)(lVar3 + 0x39) = (uVar23 & 0xff) != 1;
    FUN_1001f2edc(0);
    _swift_release(lVar3);
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar20 = DAT_100b757a8;
    uVar14 = 0x1b;
    thunk_FUN_1002db810(0x1b,PTR___swiftEmptyArrayStorage_100a1e050);
    pcVar33 = local_1b8;
    IVar21 = local_1c8;
    if ((uVar14 & 1) == 0) {
      if (DAT_100ae0030 != -1) {
        _swift_once(&DAT_100ae0030,FUN_1008174c0);
      }
      uVar20 = 1;
      FUN_100819fe0();
      if ((uVar20 & 1) != 0) goto LAB_1004f646c;
LAB_1004f67f4:
      uVar20 = 0x13;
      thunk_FUN_1002db810(0x13,PTR___swiftEmptyArrayStorage_100a1e050);
      IVar31 = local_190;
      if ((uVar20 & 1) == 0) {
        if (DAT_100ae0030 != -1) {
          _swift_once(&DAT_100ae0030,FUN_1008174c0);
        }
        uVar20 = 1;
        FUN_100819fe0();
        if ((uVar20 & 1) == 0) {
          IVar26 = _objc_msgSend((ID)pcVar33,"contentTypeID");
          uVar23 = (uint)IVar26;
          FUN_100419df0();
          if ((uVar23 & 0xff) == 6) goto LAB_1004f694c;
        }
      }
      pcVar15 = pcVar33;
      FUN_10009a4d8(pcVar33,0);
      if (IVar21 != 0) {
        __sSo13os_log_type_ta0A0E7defaultABvgZ();
        puVar13 = &DAT_100af52c8;
        FUN_100021774();
        _swift_initStackObject();
        dVar36 = 4.94065645841247e-324;
        *(undefined8 *)(puVar13 + 0x18) = 2;
        *(undefined8 *)(puVar13 + 0x10) = 1;
        _swift_getErrorValue(IVar21,auStack_140,local_158);
        uVar11 = local_150;
        uVar18 = local_148;
        FUN_1002c2c2c();
        *(undefined **)(puVar13 + 0x38) = PTR___sSSN_100a1dce0;
        uVar9 = uVar11;
        FUN_100026528();
        lVar32 = local_170;
        IVar31 = local_190;
        *(undefined8 *)(puVar13 + 0x40) = uVar9;
        *(undefined8 *)(puVar13 + 0x20) = uVar11;
        *(undefined8 *)(puVar13 + 0x28) = uVar18;
        FUN_10041ac94(pcVar15,0x4b,"Could not build Guide, with error: %@",0x25,2,puVar13);
        _swift_setDeallocating(puVar13);
        pcVar33 = local_1b8;
        FUN_100023468(puVar13 + 0x20);
        _swift_errorRelease(IVar21);
        IVar21 = 0;
      }
    }
    else {
LAB_1004f646c:
      FUN_10017148c();
      if (((uVar20 & 1) == 0) ||
         (lVar3 = *(long *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElement), lVar3 == 0)
         ) goto LAB_1004f67f4;
      lVar4 = lVar3;
      _swift_retain();
      uVar23 = (uint)lVar4;
      FUN_1000344fc();
      if ((uVar23 & 0xff) == 0x19) {
LAB_1004f67ec:
        _swift_release(lVar3);
        goto LAB_1004f67f4;
      }
      FUN_1004f240c();
      uVar23 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
      if ((uVar23 == 1) ||
         ((uVar23 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
        plVar22 = &_TtCC8Playback7SongMap7Element::fullTimelineStartTime;
      }
      else {
        plVar22 = &_TtCC8Playback7SongMap7Element::trimTimelineStartTime;
      }
      if ((*(double *)(lVar3 + *plVar22) < dVar36 + -0.015) ||
         (dVar36 = dVar36 + 0.015, dVar36 <= *(double *)(lVar3 + *plVar22))) goto LAB_1004f67ec;
      FUN_1004fbcd0();
      _swift_release(lVar3);
      IVar31 = local_190;
    }
LAB_1004f694c:
    FUN_1004f240c();
    dVar37 = dVar36;
    _objc_msgSend((ID)pcVar33,"bpm");
    dVar37 = 60.0 / dVar37;
    if (dVar37 < dVar36) {
      FUN_1004f240c();
    }
    lVar3 = _TtC8Playback9Sequencer::songTransitionDuration;
    *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionDuration) =
         0x4014000000000000;
    local_1e8 = lVar30;
    _objc_msgSend(IVar31,"storedEndTime");
    dVar36 = dVar37;
    IVar31 = _objc_msgSend(IVar31,"song");
    dVar38 = 1.0;
    if (IVar31 != 0) {
      FUN_1003220ec();
      dVar38 = dVar36;
    }
    lVar30 = _TtC8Playback9Sequencer::preloadNextSongSequenceTime;
    dVar37 = dVar37 * dVar38 - *(double *)(unaff_x20 + lVar3);
    dVar36 = 1.0;
    if (1.0 <= dVar37) {
      dVar36 = dVar37;
    }
    *(double *)(unaff_x20 + _TtC8Playback9Sequencer::preloadNextSongSequenceTime) = dVar36;
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    IVar31 = *(ID *)(DAT_100b75a80 + 0x10);
    if ((IVar31 != 0) &&
       (FUN_1004b9338(), puVar13 = _TtC8Playback4Song::privateWorkingCopyArrangement, IVar31 != 0))
    {
      IVar16 = *(ID *)(_TtC8Playback4Song::privateWorkingCopyArrangement + IVar31);
      IVar26 = IVar16;
      if (IVar16 == 0) {
        IVar16 = _objc_msgSend(IVar31,"workingCopyArrangementID");
        pcVar33 = local_1b8;
        if (IVar16 != 0) {
          IVar8 = IVar16;
          FUN_10032ee88();
          IVar26 = IVar8;
          FUN_1005e3b94(IVar8,IVar16);
          _swift_bridgeObjectRelease(IVar8);
          lVar32 = local_170;
          pcVar33 = local_1b8;
          if (IVar26 != 0) {
            *(ID *)(puVar13 + IVar31) = IVar26;
            IVar16 = 0;
            goto LAB_1004f6a60;
          }
        }
      }
      else {
LAB_1004f6a60:
        FUN_1004f8c0c();
        lVar4 = _TtC8Playback4Song::privateSongMap;
        lVar32 = local_170;
        pcVar33 = local_1b8;
        if (IVar16 != 0) {
          lVar5 = *(long *)(IVar31 + _TtC8Playback4Song::privateSongMap);
          lVar32 = lVar5;
          local_220 = IVar16;
          local_1c8 = IVar31;
          if (lVar5 == 0) {
            FUN_100861310();
            _swift_allocObject();
            puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
            *(undefined **)(lVar5 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
            dVar36 = 0.0;
            *(undefined8 *)(lVar5 + 0x28) = 0;
            *(undefined8 *)(lVar5 + 0x20) = 0;
            *(undefined8 *)(lVar5 + 0x38) = 0;
            *(undefined8 *)(lVar5 + 0x30) = 0;
            _swift_unknownObjectUnownedInit(lVar5 + 0x10,local_1c8);
            _swift_retain(puVar13);
            FUN_10085ee38(local_1c8);
            uVar11 = *(undefined8 *)(local_1c8 + lVar4);
            *(long *)(local_1c8 + lVar4) = lVar5;
            _swift_retain(lVar5);
            _swift_release(uVar11);
            lVar32 = 0;
          }
          uVar20 = *(ulong *)(lVar5 + 0x18);
          _swift_retain(lVar32);
          _swift_bridgeObjectRetain(uVar20);
          _swift_release(lVar5);
          if (uVar20 >> 0x3e == 0) {
            uVar14 = *(ulong *)((uVar20 & 0xfffffffffffff8) + 0x10);
          }
          else {
            uVar14 = uVar20 & 0xffffffffffffff8;
            if ((long)uVar20 < 0) {
              uVar14 = uVar20;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg();
          }
          pcVar33 = local_1b8;
          if (uVar14 == 0) {
            _swift_release(local_220);
            _swift_bridgeObjectRelease(uVar20);
            lVar32 = local_170;
          }
          else {
            local_230 = lVar30;
            local_228 = IVar26;
            if ((uVar20 & 0xc000000000000001) == 0) {
              if (*(long *)((uVar20 & 0xfffffffffffff8) + 0x10) == 0) {
                    /* WARNING: Does not return */
                pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f7758);
                (*pcVar33)();
              }
              lVar30 = *(long *)(uVar20 + 0x20);
              _swift_retain();
            }
            else {
              lVar30 = 0;
              FUN_1000cc314(0,uVar20);
            }
            IVar26 = local_190;
            _swift_bridgeObjectRelease(uVar20);
            IVar31 = local_1c8;
            lVar24 = *(long *)(local_1c8 + lVar4);
            lVar5 = lVar24;
            if (lVar24 == 0) {
              FUN_100861310();
              _swift_allocObject();
              puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
              *(undefined **)(lVar24 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
              dVar36 = 0.0;
              *(undefined8 *)(lVar24 + 0x28) = 0;
              *(undefined8 *)(lVar24 + 0x20) = 0;
              *(undefined8 *)(lVar24 + 0x38) = 0;
              *(undefined8 *)(lVar24 + 0x30) = 0;
              _swift_unknownObjectUnownedInit(lVar24 + 0x10,IVar31);
              _swift_retain(puVar13);
              FUN_10085ee38(IVar31);
              uVar11 = *(undefined8 *)(IVar31 + lVar4);
              *(long *)(IVar31 + lVar4) = lVar24;
              _swift_retain(lVar24);
              IVar26 = local_190;
              _swift_release(uVar11);
              lVar5 = 0;
            }
            lVar32 = local_170;
            uVar20 = *(ulong *)(lVar24 + 0x18);
            _swift_retain(lVar5);
            _swift_bridgeObjectRetain(uVar20);
            _swift_release(lVar24);
            if (uVar20 >> 0x3e == 0) {
              uVar14 = *(ulong *)((uVar20 & 0xfffffffffffff8) + 0x10);
            }
            else {
              uVar14 = uVar20 & 0xffffffffffffff8;
              if ((long)uVar20 < 0) {
                uVar14 = uVar20;
              }
              __ss18_CocoaArrayWrapperV8endIndexSivg();
            }
            _swift_bridgeObjectRelease(uVar20);
            pcVar33 = local_1b8;
            if (uVar14 != 0) {
              if (uVar14 == 1) {
                FUN_1002e4834();
                dVar36 = dVar36 * 0.5 + -0.5;
                dVar37 = 5.0;
                if (dVar36 <= 5.0) {
                  dVar37 = dVar36;
                }
                FUN_1002e4834();
                dVar38 = dVar36 * 0.5 + -0.5;
                dVar36 = 5.0;
                if (dVar38 <= 5.0) {
                  dVar36 = dVar38;
                }
                if (dVar37 <= dVar36) {
                  dVar36 = dVar37;
                }
              }
              else {
                _objc_msgSend(IVar26,"storedEndTime");
                dVar37 = dVar36;
                IVar31 = _objc_msgSend(IVar26,"song");
                if (IVar31 == 0) {
                  dVar37 = 1.0;
                }
                else {
                  FUN_1003220ec();
                }
                dVar36 = dVar36 * dVar37 -
                         *(double *)
                          (local_220 + _TtCC8Playback7SongMap7Element::trimTimelineStartTime);
                dVar37 = *(double *)(lVar30 + _TtCC8Playback7SongMap7Element::trimTimelineEndTime) -
                         *(double *)(lVar30 + _TtCC8Playback7SongMap7Element::trimTimelineStartTime)
                ;
                if (dVar36 <= dVar37) {
                  dVar37 = dVar36;
                }
                dVar36 = 5.0;
                if (dVar37 <= 5.0) {
                  dVar36 = dVar37;
                }
              }
              *(double *)(unaff_x20 + lVar3) = dVar36;
            }
            _objc_msgSend(IVar26,"storedEndTime");
            dVar37 = dVar36;
            IVar31 = _objc_msgSend(IVar26,"song");
            if (IVar31 == 0) {
              _swift_release(lVar30);
              _swift_release(local_220);
              dVar37 = 1.0;
            }
            else {
              FUN_1003220ec();
              _swift_release(lVar30);
              _swift_release(local_220);
            }
            dVar36 = (dVar36 * dVar37 - *(double *)(unaff_x20 + lVar3)) -
                     *(double *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionBufferOffset);
            *(double *)(unaff_x20 + local_230) = dVar36;
            lVar30 = local_230;
          }
        }
      }
    }
    lVar3 = _TtC8Playback9Sequencer::uuid;
    if ((local_1f0 & 1) == 0) {
      lVar4 = *(long *)(DAT_100b75e40 + 0x28);
      if (lVar4 == 0) {
LAB_1004f6fc0:
        lVar4 = *(long *)(local_188 + 0x18);
        lVar3 = local_188;
        if (lVar4 != 0) {
          lVar5 = lVar4;
          _swift_retain();
          FUN_10064458c();
          _swift_release(lVar4);
          lVar3 = *(long *)(lVar5 + 0x10);
          if (lVar3 == 0) {
            _swift_bridgeObjectRelease(lVar5);
            lVar3 = local_188;
          }
          else {
            _swift_bridgeObjectRetain(lVar5);
            plVar22 = (long *)(lVar5 + 0x28);
            do {
              uVar20 = plVar22[-1];
              lVar32 = *plVar22;
              uVar14 = uVar20;
              _swift_getObjectType();
              pcVar33 = *(code **)(lVar32 + 0x68);
              _swift_unknownObjectRetain(uVar20);
              (*pcVar33)(uVar14,lVar32);
              _swift_unknownObjectRelease(uVar20);
              if ((uVar14 & 1) != 0) {
                _swift_bridgeObjectRelease_n(lVar5,2);
                lVar32 = local_170;
                lVar3 = local_188;
                pcVar33 = local_1b8;
                lVar4 = *(long *)(local_188 + 0x18);
                if (lVar4 != 0) {
                  _swift_retain(lVar4);
                  FUN_100647944();
                  _swift_release(lVar4);
                }
                goto LAB_1004f70bc;
              }
              plVar22 = plVar22 + 3;
              lVar3 = lVar3 + -1;
            } while (lVar3 != 0);
            _swift_bridgeObjectRelease_n(lVar5,2);
            lVar3 = local_188;
            lVar32 = local_170;
            pcVar33 = local_1b8;
          }
        }
LAB_1004f70bc:
        lVar4 = *(long *)(lVar3 + 0x20);
        if (lVar4 != 0) {
          lVar5 = lVar4;
          _swift_retain();
          FUN_10064458c();
          _swift_release(lVar4);
          lVar3 = *(long *)(lVar5 + 0x10);
          if (lVar3 == 0) {
            _swift_bridgeObjectRelease(lVar5);
            lVar3 = local_188;
          }
          else {
            _swift_bridgeObjectRetain(lVar5);
            plVar22 = (long *)(lVar5 + 0x28);
            do {
              uVar20 = plVar22[-1];
              lVar32 = *plVar22;
              uVar14 = uVar20;
              _swift_getObjectType();
              pcVar33 = *(code **)(lVar32 + 0x68);
              _swift_unknownObjectRetain(uVar20);
              (*pcVar33)(uVar14,lVar32);
              _swift_unknownObjectRelease(uVar20);
              if ((uVar14 & 1) != 0) {
                _swift_bridgeObjectRelease_n(lVar5,2);
                lVar32 = local_170;
                lVar3 = local_188;
                pcVar33 = local_1b8;
                lVar4 = *(long *)(local_188 + 0x20);
                if (lVar4 != 0) {
                  _swift_retain(lVar4);
                  FUN_100647944();
                  _swift_release(lVar4);
                }
                goto LAB_1004f71b0;
              }
              plVar22 = plVar22 + 3;
              lVar3 = lVar3 + -1;
            } while (lVar3 != 0);
            _swift_bridgeObjectRelease_n(lVar5,2);
            lVar3 = local_188;
            lVar32 = local_170;
            pcVar33 = local_1b8;
          }
        }
LAB_1004f71b0:
        uVar20 = DAT_100b757a8;
        FUN_100171514();
        if ((uVar20 & 1) != 0) {
          FUN_100732ddc(0);
        }
        FUN_1004f240c();
        lVar4 = *(long *)(lVar3 + 0x18);
        if (lVar4 != 0) {
          dVar37 = *(double *)(unaff_x20 + lVar30);
          _swift_retain(lVar4);
          FUN_100648190(dVar37 < dVar36);
          _swift_release(lVar4);
          lVar30 = *(long *)(lVar3 + 0x18);
          if (lVar30 != 0) {
            _swift_retain(lVar30);
            FUN_10064521c(local_190,2);
            _swift_release(lVar30);
          }
        }
      }
      else {
        _swift_retain(unaff_x20);
        _swift_retain(lVar4);
        puVar13 = unaff_x20 + lVar3;
        __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(puVar13,lVar4 + lVar3);
        _swift_release(unaff_x20);
        _swift_release(lVar4);
        if (((ulong)puVar13 & 1) == 0) goto LAB_1004f6fc0;
      }
      IVar31 = _objc_msgSend((ID)pcVar33,"midiProPresenterPlaylist");
      if ((IVar31 != 0) ||
         (IVar31 = _objc_msgSend((ID)pcVar33,"midiProPresenterPlaylistItem"), IVar31 != 0)) {
        lVar30 = _TtC8Playback9Sequencer::uuid;
        lVar3 = *(long *)(DAT_100b75e40 + 0x20);
        if (lVar3 == 0) {
LAB_1004f72e4:
          lVar30 = 0x20;
        }
        else {
          _swift_retain(unaff_x20);
          _swift_retain(lVar3);
          puVar13 = unaff_x20 + lVar30;
          __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(puVar13,lVar3 + lVar30);
          _swift_release(unaff_x20);
          _swift_release(lVar3);
          if (((ulong)puVar13 & 1) == 0) goto LAB_1004f72e4;
          lVar30 = 0x18;
        }
        lVar30 = *(long *)(local_188 + lVar30);
        if ((lVar30 != 0) &&
           (*(long *)(lVar30 + _TtC8Playback16SongChannelGroup::midiOutChannel) != 0)) {
          IVar26 = *(ID *)(*(long *)(lVar30 + _TtC8Playback16SongChannelGroup::midiOutChannel) +
                          0x38);
          _swift_retain(lVar30);
          IVar31 = _objc_msgSend(IVar26,"AUAudioUnit");
          puVar13 = &_OBJC_CLASS___MIDIOutAudioUnit;
          _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
          IVar16 = IVar31;
          _swift_dynamicCastObjCClass(IVar31,puVar13);
          if ((IVar16 != 0) && (FUN_1001b3248(), IVar16 != 0)) {
            if (IVar16 >> 0x3e == 0) {
              uVar20 = *(ulong *)((IVar16 & 0xffffffffffffff8) + 0x10);
            }
            else {
              uVar20 = IVar16;
              if (-1 < (long)IVar16) {
                uVar20 = IVar16 & 0xffffffffffffff8;
              }
              __ss18_CocoaArrayWrapperV8endIndexSivg();
            }
            if (uVar20 != 0) {
              pcVar33 = (code *)(IVar16 & 0xc000000000000001);
              if (pcVar33 == (code *)0x0) {
                lVar32 = 0;
LAB_1004f7404:
                uVar14 = lVar32 + 1;
                if (SCARRY8(lVar32,1)) {
                    /* WARNING: Does not return */
                  pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f76f8);
                  (*pcVar33)();
                }
                lVar3 = *(long *)(IVar16 + 0x20 + lVar32 * 8);
                if (*(long *)(lVar3 + 0x10) != -1) goto code_r0x0001004f741c;
                local_1b8 = pcVar33;
                _swift_retain();
                lVar32 = -1;
LAB_1004f7454:
                uVar14 = *(ulong *)(IVar26 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
                local_228 = IVar16;
                if (uVar14 >> 0x3e == 0) {
                  uVar34 = *(ulong *)((uVar14 & 0xfffffffffffff8) + 0x10);
                  if (uVar34 == 0) goto LAB_1004f77c4;
LAB_1004f747c:
                  local_230 = lVar3;
                  local_220 = IVar31;
                  local_1f0 = IVar26;
                  local_1c8 = IVar21;
                  _swift_bridgeObjectRetain(uVar14);
                  lVar3 = 0;
                  do {
                    if ((uVar14 & 0xc000000000000001) == 0) {
                      lVar4 = *(long *)(uVar14 + lVar3 * 8 + 0x20);
                      _swift_retain();
                    }
                    else {
                      lVar4 = lVar3;
                      FUN_1000cc70c(lVar3,uVar14);
                    }
                    lVar4 = *(long *)(lVar4 + 0x10);
                    _swift_release();
                    if (lVar4 == lVar32) {
                      _swift_bridgeObjectRelease(uVar14);
                      IVar26 = local_1f0;
                      if ((*(byte *)(local_1f0 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) & 1)
                          == 0) {
                        _swift_release(local_230);
                        pcVar33 = local_1b8;
                        IVar31 = local_220;
                      }
                      else {
                        FUN_1004a1188(lVar3,0,0);
                        IVar21 = _objc_msgSend(IVar26,"AUAudioUnit");
                        puVar13 = &_OBJC_CLASS___MIDIOutAudioUnit;
                        _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
                        _swift_dynamicCastObjCClass(IVar21,puVar13);
                        pcVar33 = local_1b8;
                        IVar31 = local_220;
                        _objc_msgSend(IVar21,"updateEventTimeIndex");
                        _swift_release(local_230);
                      }
                      goto LAB_1004f77d0;
                    }
                    uVar1 = lVar3 + 1;
                    if (SCARRY8(lVar3,1)) {
                    /* WARNING: Does not return */
                      pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f76fc);
                      (*pcVar33)();
                    }
                    lVar3 = lVar3 + 1;
                  } while (uVar1 != uVar34);
                  _swift_release(local_230);
                  _swift_bridgeObjectRelease(uVar14);
                  IVar26 = local_1f0;
                  pcVar33 = local_1b8;
                  IVar31 = local_220;
                }
                else {
                  uVar34 = uVar14 & 0xffffffffffffff8;
                  if ((long)uVar14 < 0) {
                    uVar34 = uVar14;
                  }
                  local_1f0 = IVar26;
                  __ss18_CocoaArrayWrapperV8endIndexSivg();
                  IVar26 = local_1f0;
                  if (uVar34 != 0) goto LAB_1004f747c;
LAB_1004f77c4:
                  _swift_release();
                  pcVar33 = local_1b8;
                }
LAB_1004f77d0:
                IVar16 = local_228;
                if (pcVar33 != (code *)0x0) goto LAB_1004f77dc;
LAB_1004f782c:
                lVar32 = 0;
                do {
                  uVar14 = lVar32 + 1;
                  if (SCARRY8(lVar32,1)) {
                    /* WARNING: Does not return */
                    pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f8048);
                    (*pcVar33)();
                  }
                  lVar3 = *(long *)(IVar16 + 0x20 + lVar32 * 8);
                  if (*(long *)(lVar3 + 0x10) == -2) {
                    _swift_retain();
                    goto LAB_1004f7ec8;
                  }
                  lVar32 = lVar32 + 1;
                } while (uVar14 != uVar20);
                goto LAB_1004f7860;
              }
              local_1b8 = pcVar33;
              _swift_bridgeObjectRetain(IVar16);
              lVar32 = 0;
              do {
                lVar3 = lVar32;
                FUN_1000cc70c(lVar32,IVar16);
                uVar14 = lVar32 + 1;
                if (SCARRY8(lVar32,1)) {
                    /* WARNING: Does not return */
                  pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f76b8);
                  (*pcVar33)();
                }
                if (*(long *)(lVar3 + 0x10) == -1) {
                  _swift_bridgeObjectRelease(IVar16);
                  lVar32 = *(long *)(lVar3 + 0x10);
                  goto LAB_1004f7454;
                }
                _swift_unknownObjectRelease();
                lVar32 = lVar32 + 1;
              } while (uVar14 != uVar20);
              _swift_bridgeObjectRelease(IVar16);
LAB_1004f77dc:
              _swift_bridgeObjectRetain(IVar16);
              lVar32 = 0;
LAB_1004f77e8:
              lVar3 = lVar32;
              FUN_1000cc70c(lVar32,IVar16);
              uVar14 = lVar32 + 1;
              if (SCARRY8(lVar32,1)) {
                    /* WARNING: Does not return */
                pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f8044);
                (*pcVar33)();
              }
              if (*(long *)(lVar3 + 0x10) != -2) goto code_r0x0001004f7808;
              _swift_bridgeObjectRelease(IVar16);
LAB_1004f7ec8:
              _swift_bridgeObjectRelease(IVar16);
              lVar32 = *(long *)(lVar3 + 0x10);
              uVar20 = *(ulong *)(IVar26 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
              if (uVar20 >> 0x3e == 0) {
                uVar14 = *(ulong *)((uVar20 & 0xfffffffffffff8) + 0x10);
                if (uVar14 == 0) goto LAB_1004f8074;
LAB_1004f7ef4:
                local_220 = IVar31;
                local_1f0 = IVar26;
                _swift_bridgeObjectRetain(uVar20);
                lVar4 = 0;
                while( true ) {
                  if ((uVar20 & 0xc000000000000001) == 0) {
                    lVar5 = *(long *)(uVar20 + lVar4 * 8 + 0x20);
                    _swift_retain();
                  }
                  else {
                    lVar5 = lVar4;
                    FUN_1000cc70c(lVar4,uVar20);
                  }
                  lVar5 = *(long *)(lVar5 + 0x10);
                  _swift_release();
                  if (lVar5 == lVar32) break;
                  uVar34 = lVar4 + 1;
                  if (SCARRY8(lVar4,1)) {
                    /* WARNING: Does not return */
                    pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f804c);
                    (*pcVar33)();
                  }
                  lVar4 = lVar4 + 1;
                  if (uVar34 == uVar14) {
                    _swift_bridgeObjectRelease(uVar20);
                    goto LAB_1004f8074;
                  }
                }
                _swift_bridgeObjectRelease(uVar20);
                IVar21 = local_1f0;
                if ((*(byte *)(local_1f0 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) & 1) == 0)
                goto LAB_1004f8074;
                FUN_1004a1188(lVar4,0,0);
                IVar21 = _objc_msgSend(IVar21,"AUAudioUnit");
                puVar13 = &_OBJC_CLASS___MIDIOutAudioUnit;
                _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
                _swift_dynamicCastObjCClass(IVar21,puVar13);
                _objc_msgSend(IVar21,"updateEventTimeIndex");
                _swift_release(lVar3);
                _swift_release(lVar30);
                lVar32 = local_170;
              }
              else {
                uVar14 = uVar20 & 0xffffffffffffff8;
                if ((long)uVar20 < 0) {
                  uVar14 = uVar20;
                }
                __ss18_CocoaArrayWrapperV8endIndexSivg();
                if (uVar14 != 0) goto LAB_1004f7ef4;
LAB_1004f8074:
                _swift_release(lVar3);
                _swift_release(lVar30);
                lVar32 = local_170;
              }
              goto LAB_1004f7880;
            }
            _swift_bridgeObjectRelease(IVar16);
            goto LAB_1004f7870;
          }
          _swift_release(lVar30);
          lVar32 = local_170;
        }
      }
    }
    goto LAB_1004f7880;
  }
  puVar13 = &DAT_100a4d940;
  _swift_allocObject(&DAT_100a4d940,0x11,7);
  puVar13[0x10] = (char)uVar29;
  FUN_10064a544(0,FUN_100504afc,puVar13);
  _swift_release(puVar13);
  puVar13 = local_1e0;
  IVar21 = *(ID *)(pcVar33 + (long)local_1e0);
  if (IVar21 == 0) {
    IVar31 = _objc_msgSend((ID)pcVar33,"workingCopyArrangementID");
    uVar23 = 0;
    if (IVar31 != 0) {
      IVar16 = IVar31;
      FUN_10032ee88();
      IVar26 = local_1c8;
      IVar21 = IVar16;
      FUN_1005e3b94(IVar16,IVar31);
      local_1c8 = IVar26;
      _swift_bridgeObjectRelease(IVar16);
      if (IVar21 != 0) {
        *(ID *)(pcVar33 + (long)puVar13) = IVar21;
        goto LAB_1004f63d8;
      }
      goto LAB_1004f65a8;
    }
  }
  else {
LAB_1004f63d8:
    IVar21 = _objc_msgSend(IVar21,"song");
    if ((IVar21 == 0) || ((*(byte *)(IVar21 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
      uVar23 = 0;
      FUN_1002da058();
      if ((uVar23 & 0xff) < 6) {
        uVar23 = 0x31 >> (ulong)(uVar23 & 0x1f);
        goto LAB_1004f65ac;
      }
    }
LAB_1004f65a8:
    uVar23 = 0;
  }
LAB_1004f65ac:
  if (*(long *)(DAT_100b75e40 + 0x28) == 0) {
    uVar20 = 0x1f;
    thunk_FUN_1002db810(0x1f,PTR___swiftEmptyArrayStorage_100a1e050);
    uVar23 = 1;
    bVar27 = 1;
    if ((uVar20 & 1) == 0) goto LAB_1004f6604;
LAB_1004f6624:
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar20 = DAT_100b75f50;
    uVar14 = DAT_100b75f50;
    _swift_retain();
    FUN_10037c328();
    _swift_release(uVar20);
    uVar20 = DAT_100b75f50;
    if ((uVar14 & 1) == 0) {
      _swift_retain(DAT_100b75f50);
      FUN_1007b6afc(0x10003);
    }
    else {
      lVar32 = *(long *)(local_188 + 0x38);
      _swift_beginAccess(lVar32 + 0x30,auStack_f0,0,0);
      uVar20 = *(ulong *)(lVar32 + 0x30);
      uVar14 = uVar20;
      _swift_bridgeObjectRetain();
      FUN_1004f16a0();
      _swift_bridgeObjectRelease(uVar20);
      if (uVar14 >> 0x3e == 0) {
        uVar20 = *(ulong *)((uVar14 & 0xfffffffffffff8) + 0x10);
      }
      else {
        uVar20 = uVar14 & 0xffffffffffffff8;
        if ((long)uVar14 < 0) {
          uVar20 = uVar14;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      if (uVar20 == 0) {
        _swift_bridgeObjectRelease(uVar14);
        lVar32 = _TtC8Playback9Sequencer::uuid;
        goto joined_r0x0001004f670c;
      }
      if ((uVar14 & 0xc000000000000001) == 0) {
        if (*(long *)((uVar14 & 0xfffffffffffff8) + 0x10) == 0) {
                    /* WARNING: Does not return */
          pcVar33 = (code *)SoftwareBreakpoint(1,0x1004f7728);
          (*pcVar33)();
        }
        uVar20 = *(ulong *)(uVar14 + 0x20);
        _swift_retain(uVar20);
      }
      else {
        uVar20 = 0;
        FUN_1000cc35c(0,uVar14);
      }
      _swift_bridgeObjectRelease(uVar14);
      FUN_1000f04b0(0);
    }
    _swift_release(uVar20);
    lVar32 = _TtC8Playback9Sequencer::uuid;
  }
  else {
    bVar27 = unaff_x20[_TtC8Playback9Sequencer::didReachSongEnd] ^ 1;
    uVar20 = 0x1f;
    thunk_FUN_1002db810(0x1f,PTR___swiftEmptyArrayStorage_100a1e050);
    if ((uVar20 & 1) == 0) {
LAB_1004f6604:
      if (DAT_100ae0030 != -1) {
        _swift_once(&DAT_100ae0030,FUN_1008174c0);
      }
      uVar2 = 0;
      FUN_100819fe0();
      uVar23 = uVar23 & uVar2;
    }
    lVar32 = _TtC8Playback9Sequencer::uuid;
    if ((uVar23 & 1) != 0) goto LAB_1004f6624;
  }
joined_r0x0001004f670c:
  _TtC8Playback9Sequencer::uuid = lVar32;
  if (((bVar27 & 1) != 0) && (lVar30 = *(long *)(DAT_100b75e40 + 0x20), lVar30 != 0)) {
    _swift_retain(unaff_x20);
    _swift_retain(lVar30);
    uVar20 = lVar30 + lVar32;
    __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar20,unaff_x20 + lVar32);
    _swift_release(lVar30);
    _swift_release(unaff_x20);
    if (((uVar20 & 1) != 0) && (lVar32 = *(long *)(local_188 + 0x48), lVar32 != 0)) {
      _swift_retain(lVar32);
      FUN_1000cfac8(0);
      _swift_release(lVar32);
    }
  }
LAB_1004f7b90:
  if ((uVar29 & 1) == 0) {
    FUN_10004cb08(0);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_b0 = thunk_FUN_100504b04;
    local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_c8 = 0x42000000;
    local_c0 = FUN_10056b3d8;
    puStack_b8 = &DAT_100a4d958;
    local_a8 = unaff_x20;
    pvVar12 = __Block_copy(&local_d0);
    puVar13 = local_a8;
    _swift_retain(unaff_x20);
    _swift_release(puVar13);
    IVar21 = local_168;
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_168);
    puVar17 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar6 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar13);
    puVar13 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar7 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar17);
    lVar30 = local_170;
    lVar32 = local_198;
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (local_170,&local_d0,puVar13,puVar7,local_198,puVar6);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,IVar21,lVar30,pvVar12);
    __Block_release(pvVar12);
    (**(code **)(local_1a0 + 8))(lVar30,lVar32);
    (**(code **)(lVar3 + 8))(IVar21,local_178);
  }
  unaff_x20[_TtC8Playback9Sequencer::fadeOutAtEndDidBegin] = 0;
  FUN_10004cb08(0);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  local_b0 = FUN_1004fe8d0;
  local_a8 = (undefined *)0x0;
  local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_c8 = 0x42000000;
  local_c0 = FUN_10056b3d8;
  puStack_b8 = &DAT_100a4d980;
  pvVar12 = __Block_copy(&local_d0);
  IVar21 = local_168;
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_168);
  puVar17 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
  puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar6 = &DAT_100af52a8;
  FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
  _swift_retain(puVar13);
  puVar13 = &DAT_100af52b0;
  FUN_100021774(&DAT_100af52b0);
  puVar7 = &DAT_100af52b8;
  FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar17);
  lVar30 = local_170;
  lVar32 = local_198;
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (local_170,&local_d0,puVar13,puVar7,local_198,puVar6);
  __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (0,IVar21,lVar30,pvVar12);
  __Block_release(pvVar12);
  _swift_release(local_188);
  _swift_release(local_1c0);
  _swift_release(local_1d0);
  (**(code **)(local_1a0 + 8))(lVar30,lVar32);
  (**(code **)(lVar3 + 8))(IVar21,local_178);
  return IVar21;
code_r0x0001004f7808:
  _swift_unknownObjectRelease();
  lVar32 = lVar32 + 1;
  if (uVar14 == uVar20) goto code_r0x0001004f7818;
  goto LAB_1004f77e8;
code_r0x0001004f7818:
  _swift_bridgeObjectRelease(IVar16);
LAB_1004f7860:
  _swift_bridgeObjectRelease(IVar16);
LAB_1004f7870:
  lVar32 = local_170;
  _swift_release(lVar30);
LAB_1004f7880:
  FUN_1004f8088();
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  local_b0 = FUN_100504b1c;
  local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_c8 = 0x42000000;
  local_c0 = FUN_10056b3d8;
  puStack_b8 = &DAT_100a4d9d0;
  local_a8 = unaff_x20;
  pvVar12 = __Block_copy(&local_d0);
  _swift_retain(unaff_x20);
  _swift_release(local_a8);
  IVar31 = local_168;
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_168);
  local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain();
  lVar4 = local_198;
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (lVar32,&local_d0,local_1e0,local_200,local_198,local_1b0);
  __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (0,IVar31,lVar32,pvVar12);
  __Block_release(pvVar12);
  (*local_208)(lVar32,lVar4);
  IVar21 = IVar31;
  (*local_210)(IVar31,local_178);
  __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
  lVar3 = local_1a8;
  local_1c8 = IVar21;
  __s8Dispatch0A4TimeV3nowACyFZ(local_1a8);
  lVar30 = local_1e8;
  __s8Dispatch1poiyAA0A4TimeVAD_SdtF(local_1e8,0x3f847ae147ae147b,lVar3);
  local_1b8 = *(code **)(local_1f8 + 8);
  (*local_1b8)(lVar3,local_1d8);
  puVar13 = &DAT_100a4da08;
  _swift_allocObject(&DAT_100a4da08,0x18,7);
  _swift_weakInit(puVar13 + 0x10,unaff_x20);
  puVar17 = &DAT_100a4da30;
  _swift_allocObject(&DAT_100a4da30,0x38,7);
  lVar3 = local_188;
  IVar21 = local_1c0;
  *(undefined **)(puVar17 + 0x10) = puVar13;
  *(long *)(puVar17 + 0x18) = local_188;
  puVar17[0x20] = (char)uVar29;
  local_1a8 = CONCAT44(local_1a8._4_4_,uVar29);
  *(ID *)(puVar17 + 0x28) = local_1c0;
  *(ID *)(puVar17 + 0x30) = local_190;
  local_b0 = FUN_100504b84;
  local_d0 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_c8 = 0x42000000;
  local_c0 = FUN_10056b3d8;
  puStack_b8 = &DAT_100a4da48;
  local_a8 = puVar17;
  pvVar12 = __Block_copy(&local_d0);
  puVar13 = local_a8;
  _swift_retain(lVar3);
  _swift_retain(IVar21);
  _swift_release(puVar13);
  __s8Dispatch0A3QoSV11unspecifiedACvgZ(IVar31);
  local_d0 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain();
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (lVar32,&local_d0,local_1e0,local_200,lVar4,local_1b0);
  __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
            (lVar30,IVar31,lVar32,pvVar12);
  __Block_release(pvVar12);
  (*local_208)(lVar32,lVar4);
  (*local_210)(IVar31,local_178);
  uVar29 = (uint)local_1a8;
  (*local_1b8)(lVar30,local_1d8);
  lVar3 = local_180;
  goto LAB_1004f7b90;
code_r0x0001004f741c:
  lVar32 = lVar32 + 1;
  if (uVar14 == uVar20) goto LAB_1004f782c;
  goto LAB_1004f7404;
}

// ==== 1005196e8 _TtC8Playback14ControlMapping::description ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback14ControlMapping::description(ID param_1,SEL param_2)

{
  FUN_100519740();
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_1,param_2);
  _swift_bridgeObjectRelease(param_2);
  return param_1;
}

// ==== 10051a280 _TtC8Playback14ControlMapping::initWithEntity:insertIntoManagedObjectContext: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback14ControlMapping::initWithEntity_insertIntoManagedObjectContext_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithEntity:insertIntoManagedObjectContext:",param_3,
                              param_4);
  return IVar2;
}

// ==== 10051a2d4 _TtC8Playback14ControlMapping::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback14ControlMapping::_cxx_construct(ID param_1,SEL param_2)

{
  return;
}

// ==== 10051a2d8 _TtC8Playback14ControlMapping::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback14ControlMapping::_cxx_destruct(ID param_1,SEL param_2)

{
  return;
}

// ==== 10051a2dc FUN_10051a2dc ====
void FUN_10051a2dc(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback14ControlMapping);
  return;
}

// ==== 10052777c _TtC8Playback37SongMenuAdvancedMIDIOutViewController::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback37SongMenuAdvancedMIDIOutViewController::initWithCoder_
             (ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  undefined *puVar2;
  code *pcVar3;
  
  lVar1 = param_1 + midiOutUpdateDelegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined8 *)(param_1 + ___lazy_storage___sections) = 0;
  *(undefined1 *)(param_1 + featureDetailsExpanded) = 0;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  *(undefined **)(param_1 + availableMIDIBanks) = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(puVar2);
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd000000000000025,0x80000001008d1460,
             "Playback/SongMenuAdvancedMIDIOutViewController.swift",0x34,2,0x49,0);
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(1,0x100527840);
  (*pcVar3)();
}

// ==== 100527bd8 _TtC8Playback37SongMenuAdvancedMIDIOutViewController::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback37SongMenuAdvancedMIDIOutViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  FUN_1001ac5c4(param_1 + contentItem);
  FUN_100026610(param_1 + midiOutUpdateDelegate);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + ___lazy_storage___sections));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + availableMIDIBanks));
  return;
}

// ==== 100527e2c FUN_100527e2c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_100527e2c(ID param_1)

{
  byte bVar1;
  undefined8 *puVar2;
  code *pcVar3;
  undefined8 uVar4;
  ID IVar5;
  undefined *self;
  ID IVar6;
  undefined8 uVar7;
  long lVar8;
  long unaff_x20;
  ulong uVar9;
  ulong *puVar10;
  undefined8 *puVar11;
  char *pcVar12;
  ulong uVar13;
  
  IVar5 = param_1;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  uVar13 = IVar5;
  FUN_100527688();
  if ((long)IVar5 < 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x100528170);
    (*pcVar3)();
  }
  if (*(ulong *)(uVar13 + 0x10) <= IVar5) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x100528174);
    (*pcVar3)();
  }
  uVar9 = (ulong)*(byte *)(uVar13 + IVar5 + 0x20);
  _swift_bridgeObjectRelease();
  FUN_100527560();
  uVar13 = uVar9;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((long)uVar13 < 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x100528178);
    (*pcVar3)();
  }
  if (*(ulong *)(uVar9 + 0x10) <= uVar13) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x10052817c);
    (*pcVar3)();
  }
  bVar1 = *(byte *)(uVar9 + uVar13 + 0x20);
  uVar13 = (ulong)bVar1;
  _swift_bridgeObjectRelease(uVar9);
  if (bVar1 == 8) {
    uVar4 = 0xd00000000000001d;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
    IVar5 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:",uVar4);
    if (IVar5 == 0) {
      self = &_OBJC_CLASS___UITableViewCell;
      _objc_allocWithZone();
      uVar4 = 0xd00000000000001d;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
      IVar5 = _objc_msgSend((ID)self,"initWithStyle:reuseIdentifier:",1,uVar4);
    }
    IVar6 = _objc_msgSend(IVar5,"textLabel");
    if (IVar6 != 0) {
      if (DAT_100adf5d8 != -1) {
        _swift_once(&DAT_100adf5d8,FUN_10052e3e0);
      }
      uVar7 = DAT_100b76a98;
      uVar4 = DAT_100b76a90;
      _swift_bridgeObjectRetain(DAT_100b76a98);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar4,uVar7);
      _swift_bridgeObjectRelease(uVar7);
      _objc_msgSend(IVar6,"setText:",uVar4);
    }
    IVar6 = _objc_msgSend(IVar5,"detailTextLabel");
    if (IVar6 == 0) goto LAB_100528140;
    lVar8 = (*(undefined8 **)
              (unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks)
            )[2];
    if (lVar8 != 0) {
      puVar2 = *(undefined8 **)
                (unaff_x20 +
                _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks);
      do {
        puVar11 = puVar2 + 6;
        if (puVar2[4] ==
            *(long *)(unaff_x20 +
                     _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID)) {
          puVar10 = puVar2 + 5;
          goto LAB_1005280f4;
        }
        lVar8 = lVar8 + -1;
        puVar2 = puVar11;
      } while (lVar8 != 0);
    }
    puVar10 = &DAT_100b765e0;
    puVar11 = &DAT_100b765e8;
    if (DAT_100adf380 != -1) {
      _swift_once(&DAT_100adf380,FUN_10052d3c4);
    }
LAB_1005280f4:
    uVar13 = *puVar10;
    pcVar12 = (char *)*puVar11;
    _swift_bridgeObjectRetain(pcVar12);
  }
  else {
    uVar7 = 0xd000000000000019;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000019,0x80000001008d0540);
    uVar4 = uVar7;
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    IVar5 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar7,uVar4);
    pcVar12 = "textLabel";
    IVar6 = _objc_msgSend(IVar5,"textLabel");
    if (IVar6 == 0) goto LAB_100528140;
    FUN_10042f620(uVar13);
  }
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
  _swift_bridgeObjectRelease(pcVar12);
  _objc_msgSend(IVar6,"setText:",uVar13);
LAB_100528140:
  _objc_msgSend(IVar5,"setAccessoryType:",1);
  return IVar5;
}

// ==== 100528f18 FUN_100528f18 ====
void FUN_100528f18(long param_1)

{
  bool bVar1;
  ulong uVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  code *pcVar14;
  long lVar15;
  undefined8 uVar16;
  ulong uVar17;
  undefined8 uVar18;
  undefined8 *puVar19;
  long lVar20;
  long *plVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  long unaff_x20;
  ulong uVar24;
  ulong uVar25;
  long lVar26;
  ulong uVar27;
  long lVar28;
  
  lVar15 = unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::midiOutUpdateDelegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar15 != 0) {
    uVar18 = *(undefined8 *)
              (unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID)
    ;
    puVar3 = (undefined1 *)(lVar15 + _TtC8Playback26SongMenuItemViewController::midiBankUpdate);
    *puVar3 = 1;
    *(undefined8 *)(puVar3 + 8) = uVar18;
    puVar3[0x10] = 0;
    _swift_unknownObjectRelease();
  }
  lVar15 = _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks;
  uVar25 = *(ulong *)(unaff_x20 +
                     _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks);
  uVar17 = *(ulong *)(uVar25 + 0x10);
  if (uVar17 == 0) {
    uVar17 = 0;
  }
  else if (*(long *)(uVar25 + 0x20) == param_1) {
    uVar24 = 0;
LAB_100528fa4:
    uVar2 = uVar24 + 1;
    if (SCARRY8(uVar24,1)) {
                    /* WARNING: Does not return */
      pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291dc);
      (*pcVar14)();
    }
    if (uVar2 != uVar17) {
      lVar26 = uVar24 * 0x30 + 0x78;
      uVar27 = uVar2;
      do {
        if ((long)uVar2 < 0) {
                    /* WARNING: Does not return */
          pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291c8);
          (*pcVar14)();
        }
        if (uVar17 <= uVar27) {
                    /* WARNING: Does not return */
          pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291cc);
          (*pcVar14)();
        }
        lVar28 = *(long *)(uVar25 + lVar26 + -0x28);
        if (lVar28 != param_1) {
          if (uVar27 != uVar24) {
            if (uVar17 <= uVar24) {
                    /* WARNING: Does not return */
              pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291d4);
              (*pcVar14)();
            }
            puVar19 = (undefined8 *)(uVar25 + 0x20 + uVar24 * 0x30);
            uVar18 = *puVar19;
            uVar9 = puVar19[1];
            uVar4 = puVar19[2];
            uVar10 = puVar19[3];
            uVar5 = puVar19[4];
            uVar11 = puVar19[5];
            puVar19 = (undefined8 *)(uVar25 + lVar26);
            uVar6 = puVar19[-4];
            uVar23 = puVar19[-3];
            uVar7 = puVar19[-2];
            uVar12 = puVar19[-1];
            uVar16 = *puVar19;
            _swift_bridgeObjectRetain();
            _swift_bridgeObjectRetain(uVar4);
            _swift_bridgeObjectRetain(uVar5);
            _swift_bridgeObjectRetain(uVar11);
            _swift_bridgeObjectRetain(uVar23);
            _swift_bridgeObjectRetain(uVar12);
            uVar17 = uVar25;
            _swift_isUniquelyReferenced_nonNull_native();
            *(ulong *)(unaff_x20 + lVar15) = uVar25;
            if ((uVar17 & 1) == 0) {
              FUN_100793864();
              *(ulong *)(unaff_x20 + lVar15) = uVar25;
            }
            lVar20 = uVar25 + uVar24 * 0x30;
            uVar22 = *(undefined8 *)(lVar20 + 0x30);
            uVar8 = *(undefined8 *)(lVar20 + 0x40);
            uVar13 = *(undefined8 *)(lVar20 + 0x48);
            *(long *)(lVar20 + 0x20) = lVar28;
            *(undefined8 *)(lVar20 + 0x28) = uVar6;
            *(undefined8 *)(lVar20 + 0x30) = uVar23;
            *(undefined8 *)(lVar20 + 0x38) = uVar7;
            *(undefined8 *)(lVar20 + 0x40) = uVar12;
            *(undefined8 *)(lVar20 + 0x48) = uVar16;
            _swift_bridgeObjectRelease(uVar8);
            _swift_bridgeObjectRelease(uVar22);
            _swift_bridgeObjectRelease(uVar13);
            *(ulong *)(unaff_x20 + lVar15) = uVar25;
            if (*(ulong *)(uVar25 + 0x10) <= uVar27) {
                    /* WARNING: Does not return */
              pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291d8);
              (*pcVar14)();
            }
            puVar19 = (undefined8 *)(uVar25 + lVar26);
            uVar23 = puVar19[-3];
            uVar6 = puVar19[-1];
            uVar7 = *puVar19;
            puVar19[-5] = uVar18;
            puVar19[-4] = uVar9;
            puVar19[-3] = uVar4;
            puVar19[-2] = uVar10;
            puVar19[-1] = uVar5;
            *puVar19 = uVar11;
            _swift_bridgeObjectRelease(uVar6);
            _swift_bridgeObjectRelease(uVar23);
            _swift_bridgeObjectRelease(uVar7);
            *(ulong *)(unaff_x20 + lVar15) = uVar25;
            uVar17 = *(ulong *)(uVar25 + 0x10);
          }
          uVar24 = uVar24 + 1;
        }
        uVar27 = uVar27 + 1;
        lVar26 = lVar26 + 0x30;
      } while (uVar27 != uVar17);
    }
    bVar1 = (long)uVar17 < (long)uVar24;
    uVar17 = uVar24;
    if (bVar1) {
                    /* WARNING: Does not return */
      pcVar14 = (code *)SoftwareBreakpoint(1,0x100528fc0);
      (*pcVar14)();
    }
  }
  else if (uVar17 == 1) {
    uVar17 = 1;
  }
  else {
    uVar24 = 1;
    plVar21 = (long *)(uVar25 + 0x50);
    do {
      if (*plVar21 == param_1) goto LAB_100528fa4;
      uVar2 = uVar24 + 1;
      if (SCARRY8(uVar24,1)) {
                    /* WARNING: Does not return */
        pcVar14 = (code *)SoftwareBreakpoint(1,0x1005291d0);
        (*pcVar14)();
      }
      uVar24 = uVar24 + 1;
      plVar21 = plVar21 + 6;
    } while (uVar2 != uVar17);
  }
  FUN_1001d7704(uVar17);
  return;
}

// ==== 1005291dc FUN_1005291dc ====
void FUN_1005291dc(undefined8 *param_1)

{
  undefined1 *puVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  long unaff_x20;
  ulong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  lVar2 = unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::midiOutUpdateDelegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    uVar5 = *(undefined8 *)
             (unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID);
    puVar1 = (undefined1 *)(lVar2 + _TtC8Playback26SongMenuItemViewController::midiBankUpdate);
    *puVar1 = 1;
    *(undefined8 *)(puVar1 + 8) = uVar5;
    puVar1[0x10] = 0;
    _swift_unknownObjectRelease();
  }
  lVar2 = _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks;
  uStack_48 = param_1[2];
  uStack_50 = param_1[1];
  uStack_58 = param_1[4];
  local_60 = param_1[3];
  local_68 = param_1[5];
  uVar7 = *(ulong *)(unaff_x20 +
                    _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks);
  FUN_100088c38(&uStack_50);
  FUN_100088c38(&local_60);
  FUN_10029f6a0(&local_68);
  uVar3 = uVar7;
  _swift_isUniquelyReferenced_nonNull_native();
  *(ulong *)(unaff_x20 + lVar2) = uVar7;
  uVar4 = uVar7;
  if ((uVar3 & 1) == 0) {
    uVar4 = 0;
    FUN_1007915f8(0,*(long *)(uVar7 + 0x10) + 1,1,uVar7);
    *(ulong *)(unaff_x20 + lVar2) = uVar4;
  }
  uVar3 = *(ulong *)(uVar4 + 0x10);
  uVar7 = uVar4;
  if (*(ulong *)(uVar4 + 0x18) >> 1 <= uVar3) {
    uVar7 = (ulong)(1 < *(ulong *)(uVar4 + 0x18));
    FUN_1007915f8(uVar7,uVar3 + 1,1,uVar4);
  }
  *(ulong *)(uVar7 + 0x10) = uVar3 + 1;
  lVar6 = uVar7 + uVar3 * 0x30;
  uVar8 = param_1[1];
  uVar5 = *param_1;
  uVar9 = param_1[2];
  uVar11 = param_1[5];
  uVar10 = param_1[4];
  *(undefined8 *)(lVar6 + 0x38) = param_1[3];
  *(undefined8 *)(lVar6 + 0x30) = uVar9;
  *(undefined8 *)(lVar6 + 0x48) = uVar11;
  *(undefined8 *)(lVar6 + 0x40) = uVar10;
  *(undefined8 *)(lVar6 + 0x28) = uVar8;
  *(undefined8 *)(lVar6 + 0x20) = uVar5;
  *(ulong *)(unaff_x20 + lVar2) = uVar7;
  return;
}

// ==== 1005293f0 FUN_1005293f0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ulong FUN_1005293f0(ulong param_1)

{
  int *piVar1;
  undefined8 *puVar2;
  byte bVar3;
  int iVar4;
  undefined *puVar5;
  class_t *pcVar6;
  ID IVar7;
  ID IVar8;
  long lVar9;
  class_t *pcVar10;
  long lVar11;
  ID unaff_x20;
  ulong uVar12;
  ulong uVar13;
  undefined8 uVar14;
  undefined *puVar15;
  undefined8 uVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  long lVar21;
  objc_super local_80;
  objc_super local_70;
  
  FUN_100527688();
  uVar13 = param_1;
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  uVar12 = param_1;
  if ((-1 < (long)uVar13) && ((long)uVar13 < *(long *)(param_1 + 0x10))) {
    uVar12 = (ulong)*(byte *)(param_1 + uVar13 + 0x20);
    _swift_bridgeObjectRelease(param_1);
    FUN_100527560();
    uVar13 = uVar12;
    __s10Foundation9IndexPathV5UIKitE3rowSivg();
    if ((-1 < (long)uVar13) && ((long)uVar13 < *(long *)(uVar12 + 0x10))) {
      bVar3 = *(byte *)(uVar12 + uVar13 + 0x20);
      uVar13 = (ulong)bVar3;
      _swift_bridgeObjectRelease(uVar12);
      if (uVar13 == 8) {
        uVar19 = *(undefined8 *)
                  (unaff_x20 +
                  _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID);
        uVar14 = *(undefined8 *)
                  (unaff_x20 +
                  _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks);
        uVar16 = *(undefined8 *)
                  (unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::song);
        uVar20 = *(undefined8 *)
                  (unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::contentItem + 8
                  );
        pcVar6 = (class_t *)0x0;
        FUN_10029dda4();
        pcVar10 = pcVar6;
        _objc_allocWithZone();
        lVar9 = _TtC8Playback31SongMenuMIDIBanksViewController::song;
        *(undefined8 *)((long)&pcVar10->isa + _TtC8Playback31SongMenuMIDIBanksViewController::song)
             = 0;
        lVar11 = (long)&pcVar10->isa +
                 _TtC8Playback31SongMenuMIDIBanksViewController::midiBankSelectionDelegate;
        *(undefined8 *)(lVar11 + 8) = 0;
        _swift_unknownObjectWeakInit(lVar11,0);
        *(undefined8 *)
         ((long)&pcVar10->isa + _TtC8Playback31SongMenuMIDIBanksViewController::selectedMIDIBankID)
             = uVar19;
        *(undefined8 *)
         ((long)&pcVar10->isa + _TtC8Playback31SongMenuMIDIBanksViewController::availableMIDIBanks)
             = uVar14;
        *(undefined8 *)((long)&pcVar10->isa + lVar9) = uVar16;
        _swift_bridgeObjectRetain(uVar14);
        *(undefined8 *)
         ((long)&pcVar10->isa + _TtC8Playback31SongMenuMIDIBanksViewController::libraryID) = uVar20;
        *(undefined ***)(lVar11 + 8) = &PTR_PTR_100a4ef78;
        _swift_unknownObjectWeakAssign(lVar11);
        local_80.receiver = (ID)pcVar10;
        local_80.super_class = pcVar6;
        IVar7 = _objc_msgSendSuper2(&local_80,"initWithStyle:",1);
        IVar8 = _objc_msgSend(unaff_x20,"navigationController");
        if (IVar8 != 0) {
          _objc_msgSend(IVar8,"pushViewController:animated:",IVar7,1);
        }
        return 0;
      }
      lVar11 = unaff_x20 + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::contentItem;
      lVar9 = 0;
      FUN_10068e908();
      puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
      puVar18 = *(undefined **)(lVar11 + *(int *)(lVar9 + 0xb0));
      puVar15 = puVar18;
      puVar17 = puVar18;
      if (puVar18 == (undefined *)0x0) {
        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        puVar15 = (undefined *)0x0;
        puVar17 = puVar5;
      }
      lVar21 = *(long *)(puVar17 + 0x10);
      _swift_bridgeObjectRetain(puVar15);
      _swift_bridgeObjectRelease(puVar17);
      puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
      if (lVar21 == 0) {
        puVar2 = (undefined8 *)(lVar11 + *(int *)(lVar9 + 0x5c));
        lVar21 = puVar2[1];
        if (lVar21 != 0) {
          uVar14 = *puVar2;
          iVar4 = *(int *)(lVar11 + 4);
          pcVar6 = (class_t *)0x0;
          FUN_10051ca14();
          pcVar10 = pcVar6;
          _objc_allocWithZone();
          puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined **)
           ((long)&pcVar10->isa +
           _TtC8Playback44SongMenuItemContentRequisitionViewController::selectedContentTypes) =
               PTR___swiftEmptyArrayStorage_100a1e050;
          lVar11 = (long)&pcVar10->isa +
                   _TtC8Playback44SongMenuItemContentRequisitionViewController::delegate;
          *(undefined8 *)(lVar11 + 8) = 0;
          _swift_unknownObjectWeakInit(lVar11,0);
          *(undefined8 *)
           ((long)&pcVar10->isa +
           _TtC8Playback44SongMenuItemContentRequisitionViewController::___lazy_storage___headerView
           ) = 0;
          *(byte *)((long)&pcVar10->isa +
                   _TtC8Playback44SongMenuItemContentRequisitionViewController::busType) = bVar3;
          *(long *)((long)&pcVar10->isa +
                   _TtC8Playback44SongMenuItemContentRequisitionViewController::contentID) =
               (long)iVar4;
          puVar2 = (undefined8 *)
                   ((long)&pcVar10->isa +
                   _TtC8Playback44SongMenuItemContentRequisitionViewController::contentTitle);
          *puVar2 = uVar14;
          puVar2[1] = lVar21;
          *(undefined ***)(lVar11 + 8) = &PTR_PTR_100a4ef68;
          _swift_unknownObjectWeakAssign();
          local_70.receiver = (ID)pcVar10;
          local_70.super_class = pcVar6;
          _swift_retain(puVar5);
          _swift_bridgeObjectRetain(lVar21);
          IVar7 = _objc_msgSendSuper2(&local_70,"initWithStyle:",1);
          IVar8 = _objc_msgSend(unaff_x20,"navigationController");
          if (IVar8 == 0) {
            return 0;
          }
          _objc_msgSend(IVar8,"pushViewController:animated:",IVar7,1);
          return 0;
        }
      }
      puVar17 = puVar15;
      if (puVar18 == (undefined *)0x0) {
        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        puVar17 = puVar5;
      }
      iVar4 = *(int *)(lVar11 + 4);
      piVar1 = (int *)(lVar11 + *(int *)(lVar9 + 0xb4));
      lVar11 = 0;
      if ((char)piVar1[1] == '\0') {
        lVar11 = (long)*piVar1;
      }
      FUN_1007f89a4();
      _objc_allocWithZone();
      _swift_bridgeObjectRetain(puVar15);
      FUN_1005b315c(uVar13,0,0,0,puVar17,(long)iVar4,lVar11);
      IVar7 = _objc_msgSend(unaff_x20,"navigationController");
      if (IVar7 != 0) {
        _objc_msgSend(IVar7,"pushViewController:animated:",uVar13,1);
      }
      return 0;
    }
  }
  _swift_bridgeObjectRelease(uVar12);
  return uVar12;
}

// ==== 1005b3a44 FUN_1005b3a44 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1005b3a44(undefined8 param_1,undefined8 param_2,undefined8 param_3,byte param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  class_t *param_9,undefined8 param_10)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  class_t *pcVar4;
  undefined *self;
  ID IVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  objc_super local_70;
  
  pcVar4 = param_9;
  _swift_getObjectType();
  puVar1 = (undefined8 *)
           ((long)&param_9->isa +
           _TtC8Playback44SongMenuProductionCuesSelectorViewController::selectedProductionCuesPack);
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  *(undefined8 *)
   ((long)&param_9->isa + _TtC8Playback44SongMenuProductionCuesSelectorViewController::midiEvents) =
       0;
  lVar2 = (long)&param_9->isa +
          _TtC8Playback44SongMenuProductionCuesSelectorViewController::delegate;
  *(undefined8 *)(lVar2 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar2,0);
  puVar3 = (undefined8 *)
           ((long)&param_9->isa +
           _TtC8Playback44SongMenuProductionCuesSelectorViewController::context);
  *(byte *)(puVar3 + 3) = param_4 & 1;
  *puVar3 = param_1;
  puVar3[1] = param_2;
  puVar3[2] = param_3;
  *(undefined8 *)
   ((long)&param_9->isa + _TtC8Playback44SongMenuProductionCuesSelectorViewController::contentID) =
       param_6;
  *(undefined8 *)
   ((long)&param_9->isa +
   _TtC8Playback44SongMenuProductionCuesSelectorViewController::demoSetlistSongID) = param_7;
  uVar6 = 0;
  uVar7 = 0;
  uVar8 = 0;
  if ((param_4 & 1) != 0) {
    _swift_bridgeObjectRetain_n(param_3,2);
    uVar6 = param_1;
    uVar7 = param_2;
    uVar8 = param_3;
  }
  uVar9 = puVar1[2];
  *puVar1 = uVar6;
  puVar1[1] = uVar7;
  puVar1[2] = uVar8;
  _swift_bridgeObjectRelease(uVar9);
  *(undefined8 *)
   ((long)&param_9->isa +
   _TtC8Playback44SongMenuProductionCuesSelectorViewController::availableMIDIEventPacks) = param_5;
  if ((param_4 & 1) != 0) {
    FUN_1005b487c(param_1,param_2,param_3,1);
    self = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)self,"mainBundle");
    uVar6 = 0x6575432072657355;
    uVar7 = 0xe900000000000073;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0x6575432072657355,0xe900000000000073,0,0,IVar5,0,0xe000000000000000,0,
               0xe000000000000000);
    FUN_1001d62e0(0,0,0xffffffffffffffff,uVar6,uVar7);
    _swift_bridgeObjectRelease(uVar7);
  }
  *(undefined8 *)(lVar2 + 8) = param_10;
  _swift_unknownObjectWeakAssign(lVar2,param_8);
  local_70.receiver = (ID)param_9;
  local_70.super_class = pcVar4;
  _objc_msgSendSuper2(&local_70,"initWithStyle:",1);
  return;
}

// ==== 1005b3c60 FUN_1005b3c60 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_1005b3c60(long param_1,ID param_2,ID param_3,ulong param_4,undefined8 param_5,
                class_t *param_6)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  class_t *pcVar4;
  long lVar5;
  undefined *puVar6;
  ID IVar7;
  ID IVar8;
  ID IVar9;
  undefined *puVar10;
  undefined8 uVar11;
  objc_super local_70;
  
  pcVar4 = param_6;
  _swift_getObjectType();
  lVar5 = (long)&param_6->isa +
          _TtC8Playback37SongMenuAdvancedMIDIOutViewController::midiOutUpdateDelegate;
  *(undefined8 *)(lVar5 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar5,0);
  *(undefined8 *)
   ((long)&param_6->isa +
   _TtC8Playback37SongMenuAdvancedMIDIOutViewController::___lazy_storage___sections) = 0;
  *(undefined1 *)
   ((long)&param_6->isa +
   _TtC8Playback37SongMenuAdvancedMIDIOutViewController::featureDetailsExpanded) = 0;
  lVar3 = _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks;
  *(undefined **)
   ((long)&param_6->isa + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::availableMIDIBanks)
       = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_100023384(param_1,(long)&param_6->isa +
                        _TtC8Playback37SongMenuAdvancedMIDIOutViewController::contentItem,
                FUN_10068e908);
  *(ID *)((long)&param_6->isa + _TtC8Playback37SongMenuAdvancedMIDIOutViewController::song) =
       param_2;
  lVar2 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  if ((param_4 & 1) == 0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    goto LAB_1005b3d8c;
  }
  IVar9 = *(ID *)(param_2 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar9 == 0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    IVar7 = _objc_msgSend(param_2,"workingCopyArrangementID");
    if (IVar7 == 0) {
      param_3 = 0;
      goto LAB_1005b3d8c;
    }
    IVar8 = IVar7;
    FUN_10032ee88();
    IVar9 = IVar8;
    FUN_1005e3b94(IVar8,IVar7);
    _swift_bridgeObjectRelease(IVar8);
    if (IVar9 == 0) {
      param_3 = 0;
      goto LAB_1005b3d8c;
    }
    *(ID *)(param_2 + lVar2) = IVar9;
  }
  else {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  param_3 = _objc_msgSend(IVar9,"midiBankID");
LAB_1005b3d8c:
  *(ID *)((long)&param_6->isa +
         _TtC8Playback37SongMenuAdvancedMIDIOutViewController::selectedMIDIBankID) = param_3;
  *(undefined ***)(lVar5 + 8) = &PTR_PTR_100a2aeb8;
  _swift_unknownObjectWeakAssign(lVar5,param_5);
  lVar5 = 0;
  FUN_10068e908();
  puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar6 = *(undefined **)(param_1 + *(int *)(lVar5 + 0xa8));
  puVar10 = puVar6;
  if (puVar6 == (undefined *)0x0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    puVar6 = (undefined *)0x0;
    puVar10 = puVar1;
  }
  uVar11 = *(undefined8 *)((long)&param_6->isa + lVar3);
  *(undefined **)((long)&param_6->isa + lVar3) = puVar10;
  _swift_bridgeObjectRetain(puVar6);
  _swift_bridgeObjectRelease(uVar11);
  local_70.receiver = (ID)param_6;
  local_70.super_class = pcVar4;
  IVar9 = _objc_msgSendSuper2(&local_70,"initWithStyle:",1);
  FUN_1000233c8(param_1,FUN_10068e908);
  return IVar9;
}

// ==== 1005f1624 FUN_1005f1624 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 * FUN_1005f1624(ID param_1)

{
  ulong uVar1;
  code *pcVar2;
  uint uVar3;
  undefined8 *puVar5;
  ID IVar6;
  undefined *puVar7;
  long lVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  char *pcVar12;
  undefined8 uVar13;
  long lVar14;
  byte bVar15;
  long unaff_x20;
  ulong uVar16;
  long lVar17;
  ID IVar18;
  ulong uVar19;
  undefined1 auStack_78 [24];
  ID IVar4;
  
  IVar4 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar4 != 0) && (FUN_1004a9df0(), IVar4 != 0)) {
    _objc_msgSend(IVar4,"setMidiCuesSaveStateValue:",1);
    IVar4 = _objc_msgSend(IVar4,"contentTypeID");
    uVar3 = (uint)IVar4;
    FUN_100419df0();
    if ((uVar3 & 0xff) < 0x18 && (1 << (ulong)(uVar3 & 0x1f) & 0x8018f6U) != 0) {
      if (DAT_100adfa98 != -1) {
        _swift_once(&DAT_100adfa98,FUN_100549fc4);
      }
      *(undefined1 *)(DAT_100b773d0 + 0x6a) = 9;
    }
  }
  puVar5 = (undefined8 *)0x1;
  FUN_1005f2f10(1,1);
  if (DAT_100adef08 != -1) {
    puVar5 = &DAT_100adef08;
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if (((*(long *)(DAT_100b75e40 + 0x18) != 0) &&
      (lVar14 = *(long *)(*(long *)(DAT_100b75e40 + 0x18) + 0x18), lVar14 != 0)) &&
     (lVar14 = *(long *)(lVar14 + _TtC8Playback16SongChannelGroup::midiOutChannel), lVar14 != 0)) {
    IVar4 = *(ID *)(lVar14 + 0x38);
    IVar6 = _objc_msgSend(IVar4,"AUAudioUnit");
    puVar7 = &_OBJC_CLASS___MIDIOutAudioUnit;
    _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
    _swift_dynamicCastObjCClass(IVar6,puVar7);
    if (IVar6 == 0) {
      return (undefined8 *)0x0;
    }
    if ((*(long *)(DAT_100b75e40 + 0x20) != 0) &&
       (*(char *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::privatePlayState) ==
        '\x01')) {
      IVar6 = _objc_msgSend(param_1,"id");
      uVar16 = *(ulong *)(IVar4 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
      if (uVar16 >> 0x3e == 0) {
        uVar19 = *(ulong *)((uVar16 & 0xfffffffffffff8) + 0x10);
      }
      else {
        uVar19 = uVar16 & 0xffffffffffffff8;
        if ((long)uVar16 < 0) {
          uVar19 = uVar16;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      if (uVar19 != 0) {
        _swift_bridgeObjectRetain(uVar16);
        lVar14 = 0;
        do {
          if ((uVar16 & 0xc000000000000001) == 0) {
            lVar17 = *(long *)(uVar16 + lVar14 * 8 + 0x20);
            _swift_retain();
          }
          else {
            lVar17 = lVar14;
            FUN_1000cc70c(lVar14,uVar16);
          }
          IVar18 = *(ID *)(lVar17 + 0x10);
          _swift_release();
          if (IVar18 == IVar6) {
            _swift_bridgeObjectRelease(uVar16);
            if ((*(byte *)(IVar4 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) & 1) != 0) {
              FUN_1004a1188(lVar14,0,0);
              IVar4 = _objc_msgSend(IVar4,"AUAudioUnit");
              puVar7 = &_OBJC_CLASS___MIDIOutAudioUnit;
              _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
              _swift_dynamicCastObjCClass(IVar4,puVar7);
              _objc_msgSend(IVar4,"updateEventTimeIndex");
            }
            goto LAB_1005f18f4;
          }
          uVar1 = lVar14 + 1;
          if (SCARRY8(lVar14,1)) {
                    /* WARNING: Does not return */
            pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f1b98);
            (*pcVar2)();
          }
          lVar14 = lVar14 + 1;
        } while (uVar1 != uVar19);
        _swift_bridgeObjectRelease(uVar16);
      }
    }
LAB_1005f18f4:
    lVar14 = _TtC8Playback22WaveformViewController::midiMarkerViews;
    uVar13 = 0;
    _swift_beginAccess(unaff_x20 + _TtC8Playback22WaveformViewController::midiMarkerViews,auStack_78
                       ,0,0);
    uVar16 = *(ulong *)(unaff_x20 + lVar14);
    if (uVar16 >> 0x3e == 0) {
      uVar19 = *(ulong *)((uVar16 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar19 = uVar16 & 0xffffffffffffff8;
      if ((long)uVar16 < 0) {
        uVar19 = uVar16;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar19 != 0) {
      _swift_bridgeObjectRetain_n(uVar16,2);
      lVar14 = 4;
      do {
        lVar17 = lVar14 + -4;
        if ((uVar16 & 0xc000000000000001) == 0) {
          lVar8 = *(long *)(uVar16 + lVar14 * 8);
        }
        else {
          lVar8 = lVar17;
          FUN_1000cd4c0(lVar17,uVar16);
        }
        uVar1 = lVar14 - 3;
        if (SCARRY8(lVar17,1)) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f1b7c);
          (*pcVar2)();
        }
        if ((char)((long *)(lVar8 + _TtC8Playback18TimelineMarkerView::markerType))[2] == '\x01') {
          uVar9 = *(long *)(lVar8 + _TtC8Playback18TimelineMarkerView::markerType) + 0x58;
          _swift_unknownObjectWeakLoadStrong();
          if (uVar9 != 0) {
            FUN_1000287b8(0);
            __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar9,param_1);
            if ((uVar9 & 1) != 0) {
              _swift_bridgeObjectRelease_n(uVar16,2);
              bVar15 = 1;
              FUN_1005f4378(1,1);
              if (*(long *)(DAT_100b75e40 + 0x20) != 0) {
                bVar15 = *(byte *)(*(long *)(DAT_100b75e40 + 0x20) +
                                  _TtC8Playback9Sequencer::privatePlayState) ^ 1;
              }
              uVar13 = 1;
              FUN_1005f1fc8(lVar8,bVar15 & 1,1);
              goto LAB_1005f1ab0;
            }
          }
        }
        lVar14 = lVar14 + 1;
      } while (uVar1 != uVar19);
      _swift_bridgeObjectRelease_n(uVar16,2);
    }
LAB_1005f1ab0:
    if (DAT_100ade9d8 != -1) {
      _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
    }
    pcVar12 = "viewContext";
    IVar4 = _objc_msgSend(DAT_100b755c8,"viewContext");
    FUN_1000f0934(IVar4);
    uVar10 = 0;
    FUN_100465288(0);
    if (pcVar12 != (char *)0x0) {
      uVar11 = 0;
      FUN_100881e0c(0);
      FUN_10087fea8(uVar10,pcVar12,uVar13,0,0,uVar11);
    }
    puVar5 = (undefined8 *)0x0;
  }
  return puVar5;
}

// ==== 1005f7ae8 FUN_1005f7ae8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1005f7ae8(double param_1,undefined8 *param_2)

{
  long *plVar1;
  ID self;
  undefined8 *puVar2;
  long unaff_x20;
  double dVar3;
  
  puVar2 = param_2;
  if ((*(long *)(unaff_x20 + _TtC8Playback22WaveformViewController::selectedTimelineMarkerView) != 0
      ) && (plVar1 = (long *)(*(long *)(unaff_x20 +
                                       _TtC8Playback22WaveformViewController::
                                       selectedTimelineMarkerView) +
                             _TtC8Playback18TimelineMarkerView::markerType),
           (char)plVar1[2] == '\x01')) {
    self = *plVar1 + 0x58;
    _swift_unknownObjectWeakLoadStrong();
    puVar2 = (undefined8 *)0x0;
    if (self != 0) {
      *(undefined1 *)(self + _TtC8Playback9MIDIEvent::isNudging) = 1;
      _objc_msgSend(self,"sequenceTimecode");
      FUN_1005f4110((uint)param_2 & 1);
      dVar3 = param_1;
      _objc_msgSend(self,"sequenceTimecode");
      _objc_msgSend(self,"setSequenceTimecode:",param_1 + dVar3);
      return;
    }
  }
  FUN_100465688();
  _swift_allocError(&DAT_100a674a0,puVar2,0,0);
  *puVar2 = 1;
  _swift_willThrow();
  return;
}

// ==== 1005f7be8 FUN_1005f7be8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1005f7be8(long param_1)

{
  undefined *puVar1;
  code *pcVar2;
  uint uVar3;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  ID IVar4;
  
  lVar11 = _TtC8Playback22WaveformViewController::currentSetlist;
  IVar4 = param_1 + _TtC8Playback22WaveformViewController::currentSetlist;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar4 != 0) && (FUN_1004a9df0(), IVar4 != 0)) {
    _objc_msgSend(IVar4,"setMidiCuesSaveStateValue:",1);
    IVar4 = _objc_msgSend(IVar4,"contentTypeID");
    uVar3 = (uint)IVar4;
    FUN_100419df0();
    if ((uVar3 & 0xff) < 0x18 && (1 << (ulong)(uVar3 & 0x1f) & 0x8018f6U) != 0) {
      if (DAT_100adfa98 != -1) {
        _swift_once(&DAT_100adfa98,FUN_100549fc4);
      }
      *(undefined1 *)(DAT_100b773d0 + 0x6a) = 9;
    }
  }
  FUN_1005f2f10(1,1);
  param_1 = param_1 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if ((param_1 != 0) && (FUN_1004a9df0(), lVar11 = _TtC8Playback4Song::privateSongMap, param_1 != 0)
     ) {
    lVar5 = *(long *)(param_1 + _TtC8Playback4Song::privateSongMap);
    lVar10 = lVar5;
    if (lVar5 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar5 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar5 + 0x28) = 0;
      *(undefined8 *)(lVar5 + 0x20) = 0;
      *(undefined8 *)(lVar5 + 0x38) = 0;
      *(undefined8 *)(lVar5 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar5 + 0x10,param_1);
      _swift_retain(puVar1);
      FUN_10085ee38();
      uVar9 = *(undefined8 *)(param_1 + lVar11);
      *(long *)(param_1 + lVar11) = lVar5;
      _swift_retain(lVar5);
      _swift_release(uVar9);
      lVar10 = 0;
    }
    _swift_retain(lVar10);
    uVar8 = 0;
    uVar6 = *(ulong *)(lVar5 + 0x30);
    uVar7 = uVar6;
    if (uVar6 == 0) {
      FUN_10085cea0();
      uVar9 = *(undefined8 *)(lVar5 + 0x30);
      *(ulong *)(lVar5 + 0x30) = uVar8;
      _swift_bridgeObjectRetain();
      _swift_bridgeObjectRelease(uVar9);
      uVar6 = 0;
      uVar7 = uVar8;
    }
    _swift_bridgeObjectRetain(uVar6);
    _swift_release(lVar5);
    if (uVar7 >> 0x3e == 0) {
      uVar8 = *(ulong *)((uVar7 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar8 = uVar7 & 0xffffffffffffff8;
      if ((long)uVar7 < 0) {
        uVar8 = uVar7;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar8 == 0) {
      _swift_bridgeObjectRelease(uVar7);
      return;
    }
    _swift_bridgeObjectRetain(uVar7);
    lVar11 = 4;
    do {
      lVar10 = lVar11 + -4;
      if ((uVar7 & 0xc000000000000001) == 0) {
        lVar5 = *(long *)(uVar7 + lVar11 * 8);
        _swift_retain(lVar5);
      }
      else {
        lVar5 = lVar10;
        FUN_1000cc70c(lVar10,uVar7);
      }
      if (SCARRY8(lVar10,1)) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f7ebc);
        (*pcVar2)();
      }
      uVar6 = lVar11 - 3;
      lVar10 = lVar5 + 0x58;
      _swift_unknownObjectWeakLoadStrong();
      if ((lVar10 != 0) && (*(char *)(lVar10 + _TtC8Playback9MIDIEvent::isNudging) == '\x01')) {
        _swift_bridgeObjectRelease_n(uVar7,2);
        FUN_1005f7f0c(lVar5);
        _swift_release(lVar5);
        return;
      }
      _swift_release(lVar5);
      lVar11 = lVar11 + 1;
    } while (uVar6 != uVar8);
    _swift_bridgeObjectRelease_n(uVar7,2);
  }
  return;
}

// ==== 1005f7f0c FUN_1005f7f0c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_1005f7f0c(long param_1)

{
  undefined *puVar1;
  code *pcVar2;
  long lVar3;
  ID IVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  uint uVar9;
  long *plVar10;
  long unaff_x20;
  undefined8 uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  undefined1 auStack_98 [24];
  
  IVar4 = param_1 + 0x58;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar4 != 0) {
    _objc_msgSend(IVar4,"setSequenceTimecode:",*(undefined8 *)(param_1 + 0x28));
    *(undefined1 *)(IVar4 + _TtC8Playback9MIDIEvent::isNudging) = 0;
  }
  lVar3 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
  _swift_unknownObjectWeakLoadStrong();
  if ((lVar3 != 0) && (FUN_1004a9df0(), lVar15 = _TtC8Playback4Song::privateSongMap, lVar3 != 0)) {
    lVar14 = *(long *)(lVar3 + _TtC8Playback4Song::privateSongMap);
    lVar8 = lVar14;
    if (lVar14 == 0) {
      lVar8 = 0;
      FUN_100861310();
      _swift_allocObject();
      puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar8 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar8 + 0x28) = 0;
      *(undefined8 *)(lVar8 + 0x20) = 0;
      *(undefined8 *)(lVar8 + 0x38) = 0;
      *(undefined8 *)(lVar8 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar8 + 0x10,lVar3);
      _swift_retain(puVar1);
      FUN_10085ee38();
      uVar11 = *(undefined8 *)(lVar3 + lVar15);
      *(long *)(lVar3 + lVar15) = lVar8;
      _swift_retain(lVar8);
      _swift_release(uVar11);
    }
    dVar18 = *(double *)(param_1 + 0x28);
    uVar12 = *(ulong *)(lVar8 + 0x18);
    if (uVar12 >> 0x3e == 0) {
      uVar13 = *(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar13 = uVar12 & 0xffffffffffffff8;
      if ((long)uVar12 < 0) {
        uVar13 = uVar12;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar13 == 0) {
      _swift_retain(lVar14);
      _swift_release(lVar8);
    }
    else {
      _swift_bridgeObjectRetain_n(uVar12,2);
      _swift_retain(lVar14);
      lVar14 = 4;
      do {
        uVar16 = lVar14 - 4;
        if ((uVar12 & 0xc000000000000001) == 0) {
          uVar5 = *(ulong *)(uVar12 + lVar14 * 8);
          _swift_retain();
        }
        else {
          uVar5 = uVar16;
          FUN_1000cc314(uVar16,uVar12);
        }
        if (SCARRY8(uVar16,1)) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f840c);
          (*pcVar2)();
        }
        uVar16 = lVar14 - 3;
        if (DAT_100adfbb8 != -1) {
          _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
        }
        lVar7 = *(long *)(DAT_100b77548 + 0x10);
        uVar6 = (uint)((ulong)lVar7 >> 0x20);
        uVar9 = uVar6 >> 0x1e;
        plVar10 = &_TtCC8Playback7SongMap7Element::fullTimelineStartTime;
        if ((uVar9 != 1) && (uVar9 != 2 || lVar7 != -0x7fffffffffffffd0)) {
          plVar10 = &_TtCC8Playback7SongMap7Element::trimTimelineStartTime;
        }
        if (*(double *)(uVar5 + *plVar10) <= dVar18) {
          uVar6 = uVar6 >> 0x1e;
          if ((uVar6 == 1) || (uVar6 == 2 && lVar7 == -0x7fffffffffffffd0)) {
            plVar10 = &_TtCC8Playback7SongMap7Element::fullTimelineEndTime;
          }
          else {
            plVar10 = &_TtCC8Playback7SongMap7Element::trimTimelineEndTime;
          }
          dVar17 = *(double *)(uVar5 + *plVar10);
          if (dVar18 < dVar17) {
            _swift_release(lVar8);
            uVar13 = 0;
            _swift_bridgeObjectRelease_n(uVar12);
            dVar18 = 0.0;
            FUN_100212bb0();
            if ((uVar13 & 1) == 0) {
              dVar19 = *(double *)(param_1 + 0x28);
              FUN_10003594c(*(undefined8 *)(uVar5 + _TtCC8Playback7SongMap7Element::section));
              dVar17 = dVar17 + dVar18;
              if (dVar19 <= dVar17) goto LAB_1005f8520;
              lVar14 = *(long *)(lVar3 + lVar15);
              lVar8 = lVar14;
              if (lVar14 == 0) {
                lVar14 = 0;
                FUN_100861310();
                _swift_allocObject();
                puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
                *(undefined **)(lVar14 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
                dVar17 = 0.0;
                *(undefined8 *)(lVar14 + 0x28) = 0;
                *(undefined8 *)(lVar14 + 0x20) = 0;
                *(undefined8 *)(lVar14 + 0x38) = 0;
                *(undefined8 *)(lVar14 + 0x30) = 0;
                _swift_unknownObjectUnownedInit(lVar14 + 0x10,lVar3);
                _swift_retain(puVar1);
                FUN_10085ee38();
                uVar11 = *(undefined8 *)(lVar3 + lVar15);
                *(long *)(lVar3 + lVar15) = lVar14;
                _swift_retain(lVar14);
                _swift_release(uVar11);
                lVar8 = 0;
              }
              uVar16 = *(ulong *)(lVar14 + 0x18);
              _swift_bridgeObjectRetain(uVar16);
              _swift_retain(lVar8);
              _swift_release(lVar14);
              uVar12 = uVar5;
              uVar13 = uVar16;
              FUN_100283c1c();
              _swift_bridgeObjectRelease(uVar16);
              if ((uVar13 & 1) != 0) goto LAB_1005f8520;
              lVar14 = *(long *)(lVar3 + lVar15);
              lVar8 = lVar14;
              if (lVar14 == 0) {
                FUN_100861310();
                _swift_allocObject();
                puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
                *(undefined **)(lVar14 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
                dVar17 = 0.0;
                *(undefined8 *)(lVar14 + 0x28) = 0;
                *(undefined8 *)(lVar14 + 0x20) = 0;
                *(undefined8 *)(lVar14 + 0x38) = 0;
                *(undefined8 *)(lVar14 + 0x30) = 0;
                _swift_unknownObjectUnownedInit(lVar14 + 0x10,lVar3);
                _swift_retain(puVar1);
                FUN_10085ee38();
                uVar11 = *(undefined8 *)(lVar3 + lVar15);
                *(long *)(lVar3 + lVar15) = lVar14;
                _swift_retain(lVar14);
                _swift_release(uVar11);
                lVar8 = 0;
              }
              uVar16 = *(ulong *)(lVar14 + 0x18);
              _swift_retain(lVar8);
              _swift_bridgeObjectRetain(uVar16);
              _swift_release(lVar14);
              uVar13 = uVar12 + 1;
              if (SCARRY8(uVar12,1)) {
                    /* WARNING: Does not return */
                pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f84dc);
                (*pcVar2)();
              }
              if (uVar16 >> 0x3e != 0) {
                uVar12 = uVar16 & 0xffffffffffffff8;
                if ((long)uVar16 < 0) {
                  uVar12 = uVar16;
                }
                __ss18_CocoaArrayWrapperV8endIndexSivg();
                if ((long)uVar12 < 0) {
                    /* WARNING: Does not return */
                  pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f84f4);
                  (*pcVar2)();
                }
                if (-1 < (long)uVar13) goto LAB_1005f8390;
LAB_1005f8518:
                _swift_bridgeObjectRelease(uVar16);
                goto LAB_1005f8520;
              }
              uVar12 = *(ulong *)((uVar16 & 0xfffffffffffff8) + 0x10);
              if ((long)uVar13 < 0) goto LAB_1005f8518;
LAB_1005f8390:
              if (uVar12 <= uVar13) goto LAB_1005f8518;
              if ((uVar16 & 0xc000000000000001) == 0) {
                if (*(ulong *)((uVar16 & 0xfffffffffffff8) + 0x10) <= uVar13) {
                    /* WARNING: Does not return */
                  pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f850c);
                  (*pcVar2)();
                }
                uVar13 = *(ulong *)(uVar16 + uVar13 * 8 + 0x20);
                _swift_retain(uVar13);
              }
              else {
                FUN_1000cc314(uVar13,uVar16);
              }
              _swift_bridgeObjectRelease(uVar16);
              uVar6 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
              if (uVar6 == 1) {
                plVar10 = &_TtCC8Playback7SongMap7Element::fullTimelineEndTime;
              }
              else if ((uVar6 == 2) && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)) {
                plVar10 = &_TtCC8Playback7SongMap7Element::fullTimelineEndTime;
              }
              else {
                plVar10 = &_TtCC8Playback7SongMap7Element::trimTimelineEndTime;
              }
              dVar18 = *(double *)(uVar5 + *plVar10);
              dVar19 = *(double *)(param_1 + 0x28);
              FUN_1000345bc(1);
              if (IVar4 != 0) {
                dVar18 = dVar18 - dVar19;
                dVar17 = dVar17 - dVar18;
                FUN_1003220ec();
                _objc_msgSend(IVar4,"setSampleTimecode:",dVar17 / dVar18);
              }
              _swift_release(uVar5);
              uVar5 = uVar13;
            }
            else {
LAB_1005f8520:
              FUN_1000345bc(0);
              uVar6 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
              if ((uVar6 == 1) ||
                 ((uVar6 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
                plVar10 = &_TtCC8Playback7SongMap7Element::fullTimelineStartTime;
              }
              else {
                plVar10 = &_TtCC8Playback7SongMap7Element::trimTimelineStartTime;
              }
              if (IVar4 != 0) {
                dVar18 = *(double *)(param_1 + 0x28) - *(double *)(uVar5 + *plVar10);
                dVar17 = dVar17 + dVar18;
                FUN_1003220ec();
                _objc_msgSend(IVar4,"setSampleTimecode:",dVar17 / dVar18);
              }
            }
            _swift_release(uVar5);
            goto LAB_1005f85e8;
          }
        }
        _swift_release();
        lVar14 = lVar14 + 1;
      } while (uVar16 != uVar13);
      _swift_release(lVar8);
      _swift_bridgeObjectRelease_n(uVar12,2);
    }
  }
LAB_1005f85e8:
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar4 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar4);
  lVar3 = _TtC8Playback22WaveformViewController::midiMarkerViews;
  _swift_beginAccess(unaff_x20 + _TtC8Playback22WaveformViewController::midiMarkerViews,auStack_98,0
                     ,0);
  uVar12 = *(ulong *)(unaff_x20 + lVar3);
  if (uVar12 >> 0x3e == 0) {
    uVar13 = *(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar13 = uVar12 & 0xffffffffffffff8;
    if ((long)uVar12 < 0) {
      uVar13 = uVar12;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar13 != 0) {
    _swift_retain(param_1);
    _swift_bridgeObjectRetain(uVar12);
    lVar15 = 4;
    do {
      uVar16 = lVar15 - 4;
      if ((uVar12 & 0xc000000000000001) == 0) {
        uVar5 = *(ulong *)(uVar12 + lVar15 * 8);
      }
      else {
        uVar5 = uVar16;
        FUN_1000cd4c0(uVar16,uVar12);
      }
      if ((((char)((long *)(uVar5 + _TtC8Playback18TimelineMarkerView::markerType))[2] == '\x01') &&
          (lVar8 = *(long *)(uVar5 + _TtC8Playback18TimelineMarkerView::markerType),
          *(long *)(lVar8 + 0x10) == *(long *)(param_1 + 0x10))) &&
         (*(double *)(lVar8 + 0x28) == *(double *)(param_1 + 0x28))) {
        _swift_bridgeObjectRelease(uVar12);
        _swift_release(param_1);
        uVar12 = *(ulong *)(unaff_x20 + lVar3);
        if (uVar12 >> 0x3e == 0) {
          uVar13 = *(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10);
        }
        else {
          uVar13 = uVar12 & 0xffffffffffffff8;
          if ((long)uVar12 < 0) {
            uVar13 = uVar12;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if ((long)uVar13 < 0) {
                    /* WARNING: Does not return */
            pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f8808);
            (*pcVar2)();
          }
        }
        if (uVar13 <= uVar16) {
          return 0;
        }
        if ((uVar12 & 0xc000000000000001) == 0) {
          if (*(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10) <= uVar16) {
                    /* WARNING: Does not return */
            pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f8830);
            (*pcVar2)();
          }
          uVar16 = *(ulong *)(uVar12 + lVar15 * 8);
        }
        else {
          _swift_bridgeObjectRetain(uVar12);
          FUN_1000cd4c0(uVar16,uVar12);
          _swift_bridgeObjectRelease(uVar12);
        }
        FUN_1005f1fc8(uVar16,1,1);
        return 0;
      }
      uVar5 = lVar15 - 3;
      if (SCARRY8(uVar16,1)) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1005f87bc);
        (*pcVar2)();
      }
      lVar15 = lVar15 + 1;
    } while (uVar5 != uVar13);
    _swift_bridgeObjectRelease(uVar12);
    _swift_release(param_1);
  }
  return 0;
}

// ==== 100647514 FUN_100647514 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100647514(uint param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  class_t *pcVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  undefined *puVar8;
  class_t *pcVar9;
  class_t *pcVar10;
  class_rw_t *pcVar11;
  long lVar12;
  long unaff_x20;
  undefined *puVar13;
  long lVar14;
  undefined8 uVar15;
  long *plVar16;
  code *pcVar17;
  
  puVar13 = *(undefined **)(unaff_x20 + _TtC8Playback16SongChannelGroup::allChannels);
  lVar12 = *(long *)(puVar13 + 0x10);
  if (lVar12 == 0) {
    _swift_bridgeObjectRetain(puVar13);
  }
  else {
    _swift_bridgeObjectRetain_n(puVar13,2);
    plVar16 = (long *)(puVar13 + 0x28);
    do {
      lVar3 = plVar16[-1];
      lVar5 = *plVar16;
      lVar7 = lVar3;
      _swift_getObjectType();
      pcVar17 = *(code **)(lVar5 + 0x18);
      _swift_unknownObjectRetain(lVar3);
      (*pcVar17)(lVar7,lVar5);
      if (lVar7 != 0) {
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
        if ((*(byte *)(lVar7 + _TtC8Playback9SongTrack::soloState) & 1) == 0) {
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          _swift_bridgeObjectRelease_n(puVar13,2);
          _swift_unknownObjectRetain(lVar3);
          FUN_1006549a0();
          _swift_unknownObjectRelease(lVar3);
          puVar13 = puVar8;
          goto LAB_100647668;
        }
      }
      _swift_unknownObjectRelease(lVar3);
      plVar16 = plVar16 + 2;
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    _swift_bridgeObjectRelease(puVar13);
  }
LAB_100647668:
  lVar12 = *(long *)(puVar13 + 0x10);
  if (lVar12 != 0) {
    puVar8 = puVar13;
    _swift_bridgeObjectRetain();
    plVar16 = (long *)(puVar8 + 0x28);
    do {
      lVar3 = plVar16[-1];
      lVar5 = *plVar16;
      lVar7 = lVar3;
      _swift_getObjectType();
      pcVar17 = *(code **)(lVar5 + 0x18);
      _swift_unknownObjectRetain(lVar3);
      (*pcVar17)(lVar7,lVar5);
      if ((lVar7 == 0) ||
         (puVar1 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::currentFade),
         *(char *)(puVar1 + 2) == -1)) {
        _swift_unknownObjectRelease(lVar3);
      }
      else {
        uVar15 = *puVar1;
        uVar6 = puVar1[1];
        puVar2 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::fadeStartTimecode);
        *puVar2 = 0;
        *(undefined1 *)(puVar2 + 1) = 1;
        *puVar1 = 0;
        puVar1[1] = 0;
        *(undefined1 *)(puVar1 + 2) = 0xff;
        FUN_100033784(uVar15,uVar6);
        puVar1 = (undefined8 *)(lVar7 + _TtC8Playback9SongTrack::currentFadeVolume);
        *puVar1 = 0;
        *(undefined1 *)(puVar1 + 1) = 1;
        lVar5 = _TtC8Playback9SongTrack::fadeWorkItem;
        lVar14 = *(long *)(lVar7 + _TtC8Playback9SongTrack::fadeWorkItem);
        uVar15 = 0;
        if (lVar14 != 0) {
          _swift_retain(lVar14);
          __s8Dispatch0A8WorkItemC6cancelyyFTj();
          _swift_release(lVar14);
          uVar15 = *(undefined8 *)(lVar7 + lVar5);
        }
        *(undefined8 *)(lVar7 + lVar5) = 0;
        _swift_unknownObjectRelease(lVar3);
        _swift_release(uVar15);
      }
      plVar16 = plVar16 + 2;
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    _swift_bridgeObjectRelease(puVar13);
    lVar12 = *(long *)(puVar13 + 0x10);
    if (lVar12 != 0) {
      plVar16 = (long *)(puVar13 + 0x28);
      do {
        pcVar4 = (class_t *)plVar16[-1];
        lVar3 = *plVar16;
        pcVar9 = pcVar4;
        _object_getClass();
        if (pcVar9 == &objc::class_t::_TtC8Playback14MIDIOutChannel && pcVar4 != (class_t *)0x0) {
          if ((param_1 & 1) != 0) {
            *(undefined1 *)(pcVar4[1].cache + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) = 1;
          }
        }
        else {
          pcVar9 = pcVar4;
          _swift_getObjectType();
          pcVar17 = *(code **)(lVar3 + 0x20);
          _swift_unknownObjectRetain(pcVar4);
          pcVar10 = pcVar9;
          (*pcVar17)(pcVar9,lVar3);
          if (((((ulong)pcVar10 & 1) == 0) &&
              (pcVar10 = pcVar9, (**(code **)(lVar3 + 0x28))(pcVar9,lVar3),
              ((ulong)pcVar10 & 1) == 0)) &&
             (pcVar10 = pcVar9, (**(code **)(lVar3 + 0x30))(pcVar9,lVar3), ((ulong)pcVar10 & 1) == 0
             )) {
            (**(code **)(lVar3 + 0x38))(pcVar9,lVar3);
            if ((((ulong)pcVar9 & 1) == 0) || ((param_1 & 1) != 0)) {
              pcVar9 = pcVar4;
              _swift_getObjectType();
              _swift_conformsToProtocol();
              if ((pcVar9 != (class_t *)0x0) && (pcVar4 != (class_t *)0x0)) {
                pcVar10 = pcVar4;
                _swift_getObjectType(pcVar4);
                pcVar11 = pcVar9[2].data;
                _swift_unknownObjectRetain(pcVar4);
                (*(code *)pcVar11)(1,pcVar10,pcVar9);
                (*(code *)pcVar9->superclass->data)(pcVar10);
                FUN_1006513dc(pcVar4,lVar3,param_1 & 1);
                _swift_unknownObjectRelease_n(pcVar4,2);
                goto LAB_1006477d0;
              }
            }
          }
          else {
            (**(code **)(lVar3 + 0x38))(pcVar9,lVar3);
          }
          _swift_unknownObjectRelease(pcVar4);
        }
LAB_1006477d0:
        plVar16 = plVar16 + 2;
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
    }
  }
  _swift_bridgeObjectRelease(puVar13);
  return;
}

// ==== 100648190 FUN_100648190 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

long FUN_100648190(double param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  class_t *pcVar3;
  char cVar4;
  float fVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  ulong uVar18;
  ulong uVar19;
  undefined8 uVar20;
  undefined8 *puVar21;
  undefined *puVar22;
  undefined1 *puVar23;
  class_t *pcVar24;
  class_rw_t **ppcVar25;
  ID IVar26;
  ID IVar27;
  TargetProtocolDescriptor *pTVar28;
  long lVar29;
  ulong uVar30;
  long lVar31;
  long lVar32;
  long lVar33;
  long lVar34;
  ID *pIVar35;
  ulong uVar36;
  long *plVar37;
  long unaff_x20;
  ID IVar38;
  long lVar39;
  long lVar40;
  undefined8 uVar41;
  code *pcVar42;
  long lVar43;
  ID IVar44;
  long lVar45;
  ulong uVar46;
  long lVar47;
  code *pcVar48;
  long lVar49;
  long lVar50;
  double dVar51;
  double dVar52;
  double dVar53;
  double dVar54;
  double dVar55;
  double dVar56;
  undefined1 auStack_260 [4];
  int local_25c;
  undefined8 local_258;
  undefined *local_250;
  int local_244;
  ID local_240;
  undefined4 local_234;
  long local_230;
  ID local_228;
  int local_21c;
  undefined8 local_218;
  int local_20c;
  ulong local_208;
  undefined8 local_200;
  int local_1f4;
  long local_1f0;
  int local_1e4;
  ulong local_1e0;
  undefined8 local_1d8;
  ulong local_1d0;
  long local_1c8;
  long local_1c0;
  long local_1b8;
  long local_1b0;
  long local_1a8;
  ulong local_1a0;
  ulong local_198;
  long local_190;
  undefined1 *local_188;
  uint local_17c;
  long local_178;
  long local_170;
  long local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_e0;
  undefined1 auStack_d0 [8];
  undefined1 auStack_c8 [16];
  undefined *local_b8;
  undefined8 local_b0;
  undefined1 auStack_a8 [40];
  
  lVar9 = 0;
  __ss25FloatingPointRoundingRuleOMa();
  lVar29 = *(long *)(lVar9 + -8);
  uVar30 = *(long *)(lVar29 + 0x40) + 0xfU & 0xfffffffffffffff0;
  puVar23 = auStack_260 + -uVar30;
  lVar39 = (long)puVar23 - uVar30;
  lVar43 = lVar39 - uVar30;
  lVar45 = lVar43 - uVar30;
  puVar16 = &DAT_100af5490;
  FUN_100021774();
  uVar30 = *(long *)(*(long *)(puVar16 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar47 = lVar45 - uVar30;
  lVar49 = lVar47 - uVar30;
  lVar50 = lVar49 - uVar30;
  lVar10 = 0;
  __sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyOMa();
  lVar31 = *(long *)(lVar10 + -8);
  lVar32 = (lVar50 - uVar30) - (*(long *)(lVar31 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar11 = 0;
  __sSo17OS_dispatch_queueC8DispatchE10AttributesVMa();
  lVar33 = lVar32 - (*(long *)(*(long *)(lVar11 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar12 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar34 = lVar33 - (*(long *)(*(long *)(lVar12 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar12 = 0;
  __s10Foundation4UUIDVMa();
  local_1b8 = *(long *)(lVar12 + -8);
  local_1c0 = lVar34 - (*(long *)(local_1b8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  local_1b0 = lVar12;
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar12 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar13 = *(long *)(DAT_100b75e40 + 0x18);
  if (lVar13 == 0) {
    return 0;
  }
  if (*(long *)(DAT_100b75e40 + 0x20) == 0) {
    return lVar13;
  }
  IVar44 = *(ID *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::song);
  IVar38 = *(ID *)(IVar44 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  local_190 = lVar43;
  local_188 = puVar23;
  local_178 = lVar50;
  local_170 = lVar47;
  local_168 = lVar45;
  local_160 = lVar39;
  if (IVar38 == 0) {
    _swift_retain(lVar13);
    IVar26 = _objc_msgSend(IVar44,"workingCopyArrangementID");
    if (IVar26 == 0) {
LAB_100649e00:
      _swift_release(lVar13);
      return 0;
    }
    IVar27 = IVar26;
    FUN_10032ee88();
    IVar38 = IVar27;
    FUN_1005e3b94(IVar27,IVar26);
    local_1d8 = 0;
    _swift_bridgeObjectRelease(IVar27);
    if (IVar38 == 0) goto LAB_100649e00;
    *(ID *)(IVar44 + lVar12) = IVar38;
  }
  else {
    _swift_retain();
    local_1d8 = 0;
  }
  IVar38 = _objc_msgSend(IVar38,"song");
  if ((IVar38 == 0) || ((*(byte *)(IVar38 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
    uVar7 = 0;
    FUN_1002da058();
  }
  else {
    uVar7 = 3;
  }
  lVar12 = _TtC8Playback16SongChannelGroup::uuid;
  lVar43 = *(long *)(lVar13 + 0x20);
  lVar39 = 0;
  if (lVar43 == 0) {
LAB_1006484ac:
    FUN_10064458c();
    lVar43 = _TtC8Playback16SongChannelGroup::subclickChannels;
    lVar12 = *(long *)(lVar39 + 0x10);
    local_1a8 = lVar39;
    if ((uVar7 & 0xff) == 3) {
      if ((param_2 & 1) == 0) {
        if (lVar12 != 0) {
          _swift_bridgeObjectRetain(lVar39);
          plVar37 = (long *)(lVar39 + 0x30);
          do {
            lVar10 = plVar37[-2];
            lVar11 = *plVar37;
            lVar9 = lVar10;
            _swift_getObjectType(lVar10);
            pcVar42 = *(code **)(lVar11 + 0x18);
            _swift_unknownObjectRetain(lVar10);
            (*pcVar42)(lVar9,lVar11);
            FUN_1006446e0();
            _swift_unknownObjectRelease(lVar10);
            lVar12 = lVar12 + -1;
            plVar37 = plVar37 + 3;
          } while (lVar12 != 0);
          _swift_release(lVar13);
LAB_100649ec0:
          _swift_bridgeObjectRelease_n(lVar39,2);
          return lVar39;
        }
      }
      else if (lVar12 != 0) {
        local_158 = _TtC8Playback16SongChannelGroup::allChannels;
        _swift_bridgeObjectRetain();
        local_230 = lVar43;
        _swift_beginAccess(unaff_x20 + lVar43,auStack_a8,0,0);
        lVar43 = 0;
        local_234 = *(undefined4 *)
                     PTR___sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyO7inherityA2EmFWC_100a1e0e8
        ;
        local_1e4 = *(int *)
                     PTR___ss25FloatingPointRoundingRuleO23toNearestOrAwayFromZeroyA2BmFWC_100a1dea0
        ;
        local_1f4 = *(int *)PTR___ss25FloatingPointRoundingRuleO15toNearestOrEvenyA2BmFWC_100a1de98;
        local_20c = *(int *)PTR___ss25FloatingPointRoundingRuleO2upyA2BmFWC_100a1dea8;
        local_21c = *(int *)PTR___ss25FloatingPointRoundingRuleO4downyA2BmFWC_100a1deb0;
        local_244 = *(int *)PTR___ss25FloatingPointRoundingRuleO10towardZeroyA2BmFWC_100a1de88;
        local_25c = *(int *)PTR___ss25FloatingPointRoundingRuleO12awayFromZeroyA2BmFWC_100a1de90;
        dVar56 = 0.0001;
        local_1c8 = lVar50 - uVar30;
        local_150 = lVar12;
LAB_1006485ec:
        pIVar35 = (ID *)(lVar39 + 0x20 + lVar43 * 0x18);
        IVar26 = *pIVar35;
        IVar44 = pIVar35[2];
        IVar38 = IVar26;
        _swift_getObjectType();
        pcVar42 = *(code **)(IVar44 + 0x18);
        _swift_unknownObjectRetain(IVar26);
        (*pcVar42)(IVar38,IVar44);
        if (IVar38 == 0) {
          _swift_unknownObjectRelease(IVar26);
        }
        else {
          lVar45 = *(long *)(unaff_x20 + local_158);
          lVar12 = *(long *)(lVar45 + 0x10);
          if (lVar12 == 0) {
            puVar16 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain();
            lVar12 = *(long *)(puVar16 + 0x10);
          }
          else {
            _swift_bridgeObjectRetain_n(lVar45,2);
            puVar16 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain();
            lVar47 = 0x20;
            do {
              lVar40 = *(long *)(lVar45 + lVar47);
              lVar50 = lVar40;
              _swift_getObjectType();
              pTVar28 = &TargetProtocolDescriptor_1009b5e94;
              lVar14 = lVar40;
              FUN_10026e150();
              if (lVar14 != 0) {
                _swift_unknownObjectRetain(lVar40);
                puVar15 = puVar16;
                _swift_isUniquelyReferenced_nonNull_native();
                puVar17 = puVar16;
                if (((ulong)puVar15 & 1) == 0) {
                  puVar17 = (undefined *)0x0;
                  FUN_10078e448(0,*(long *)(puVar16 + 0x10) + 1,1,puVar16);
                }
                uVar30 = *(ulong *)(puVar17 + 0x10);
                puVar16 = puVar17;
                if (*(ulong *)(puVar17 + 0x18) >> 1 <= uVar30) {
                  puVar16 = (undefined *)(ulong)(1 < *(ulong *)(puVar17 + 0x18));
                  FUN_10078e448(puVar16,uVar30 + 1,1,puVar17);
                }
                *(ulong *)(puVar16 + 0x10) = uVar30 + 1;
                *(long *)(puVar16 + uVar30 * 0x18 + 0x20) = lVar14;
                *(long *)(puVar16 + uVar30 * 0x18 + 0x28) = lVar50;
                *(TargetProtocolDescriptor **)(puVar16 + uVar30 * 0x18 + 0x30) = pTVar28;
              }
              lVar47 = lVar47 + 0x10;
              lVar12 = lVar12 + -1;
            } while (lVar12 != 0);
            _swift_bridgeObjectRelease_n(lVar45,2);
            lVar12 = *(long *)(puVar16 + 0x10);
          }
          if (lVar12 != 0) {
            _swift_bridgeObjectRetain(puVar16);
            plVar37 = (long *)(puVar16 + 0x30);
            do {
              uVar30 = plVar37[-2];
              lVar45 = plVar37[-1];
              lVar47 = *plVar37;
              uVar18 = uVar30;
              _swift_getObjectType();
              pcVar42 = *(code **)(lVar47 + 0x18);
              _swift_unknownObjectRetain(uVar30);
              uVar36 = uVar18;
              (*pcVar42)(uVar18,lVar47);
              if (uVar36 != 0) {
                FUN_1000cda74(0);
                __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar36,IVar38);
                if ((uVar36 & 1) != 0) {
                  _swift_bridgeObjectRelease_n(puVar16,2);
                  _objc_msgSend(IVar38,"included");
                  uVar36 = uVar18;
                  (**(code **)(lVar45 + 0x68))(uVar18,lVar45);
                  if ((uVar36 & 1) != 0) {
                    (**(code **)(lVar45 + 0x70))(0,uVar18,lVar45);
                  }
                  dVar51 = 0.0;
                  (**(code **)(*(long *)(lVar45 + 8) + 0x28))(uVar18);
                  (**(code **)(lVar47 + 0x20))(uVar18,lVar47);
                  if ((uVar18 & 1) == 0) {
                    _swift_unknownObjectRelease(IVar26);
                    _swift_unknownObjectRelease(uVar30);
                    lVar12 = local_150;
                    goto LAB_1006485e0;
                  }
                  uVar18 = _objc_msgSend(IVar38,"arrangement");
                  lVar12 = local_150;
                  if (uVar18 == 0) {
                    _swift_unknownObjectRelease(IVar26);
                  }
                  else {
                    FUN_1002db88c();
                    uVar36 = 0;
                    if ((uVar18 & 1) != 0) {
                      local_240 = IVar38;
                      FUN_1005e3cb8();
                      if (uVar36 >> 0x3e == 0) {
                        uVar18 = *(ulong *)((uVar36 & 0xfffffffffffff8) + 0x10);
                      }
                      else {
                        uVar18 = uVar36 & 0xffffffffffffff8;
                        if ((long)uVar36 < 0) {
                          uVar18 = uVar36;
                        }
                        __ss18_CocoaArrayWrapperV8endIndexSivg();
                      }
                      if (uVar18 != 0) {
                        uVar19 = uVar36 & 0xc000000000000001;
                        if (uVar19 == 0) {
                          lVar45 = *(long *)(uVar36 + 0x20);
                          _swift_bridgeObjectRetain_n(uVar36,2);
                          _swift_retain(lVar45);
                        }
                        else {
                          _swift_bridgeObjectRetain_n(uVar36,2);
                          lVar45 = 0;
                          FUN_1000cda30(0,uVar36);
                        }
                        if (*(char *)(lVar45 + 0x50) == '\x02') goto LAB_1006488f4;
                        _swift_release(lVar45);
                        if (uVar18 != 1) {
                          if (uVar19 == 0) {
                            lVar45 = *(long *)(uVar36 + 0x28);
                            _swift_retain(lVar45);
                          }
                          else {
                            lVar45 = 1;
                            FUN_1000cda30(1,uVar36);
                          }
                          if (*(char *)(lVar45 + 0x50) == '\x02') goto LAB_1006488f4;
                          _swift_release(lVar45);
                          if (uVar18 != 2) {
                            lVar47 = 6;
                            goto LAB_100649ad0;
                          }
                        }
                        _swift_bridgeObjectRelease_n(uVar36,2);
                      }
                      local_17c = 0;
                      goto LAB_100648a30;
                    }
                    _swift_unknownObjectRelease(IVar26);
                  }
                  _swift_unknownObjectRelease(uVar30);
                  goto LAB_1006485e0;
                }
              }
              _swift_unknownObjectRelease(uVar30);
              plVar37 = plVar37 + 3;
              lVar12 = lVar12 + -1;
            } while (lVar12 != 0);
            _swift_bridgeObjectRelease(puVar16);
          }
          _swift_bridgeObjectRelease(puVar16);
          _swift_unknownObjectRelease(IVar26);
          lVar12 = local_150;
        }
        goto LAB_1006485e0;
      }
      _swift_bridgeObjectRelease(lVar39);
      goto LAB_10064a480;
    }
    if (lVar12 != 0) {
      _swift_bridgeObjectRetain(lVar39);
      plVar37 = (long *)(lVar39 + 0x30);
      do {
        lVar10 = plVar37[-2];
        lVar11 = *plVar37;
        lVar9 = lVar10;
        _swift_getObjectType(lVar10);
        pcVar42 = *(code **)(lVar11 + 0x18);
        _swift_unknownObjectRetain(lVar10);
        (*pcVar42)(lVar9,lVar11);
        FUN_1006446e0();
        _swift_unknownObjectRelease(lVar10);
        lVar12 = lVar12 + -1;
        plVar37 = plVar37 + 3;
      } while (lVar12 != 0);
      _swift_bridgeObjectRelease(lVar39);
    }
    _swift_bridgeObjectRelease();
    bVar6 = (byte)lVar39;
    lVar9 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::automationChannel);
    if (lVar9 != 0) {
      uVar30 = 0;
      thunk_FUN_1002db810(0x1c,PTR___swiftEmptyArrayStorage_100a1e050);
      lVar10 = DAT_100ae0030;
      if ((uVar30 & 1) == 0) {
        _swift_retain(lVar9);
        if (lVar10 != -1) {
          _swift_once(&DAT_100ae0030,FUN_1008174c0);
        }
        bVar6 = 0;
        FUN_100819fe0();
      }
      else {
        _swift_retain(lVar9);
        bVar6 = 1;
      }
      *(byte *)(lVar9 + 0x40) = bVar6 & 1;
      FUN_100883500();
      _swift_release();
      bVar6 = (byte)lVar9;
    }
    FUN_100651194();
    lVar9 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::midiOutChannel);
    if (lVar9 == 0) goto LAB_10064a480;
    *(byte *)(lVar9 + 0x40) = bVar6 & 1;
    *(byte *)(*(long *)(lVar9 + 0x38) + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = bVar6 & 1;
    _swift_retain(lVar9);
    FUN_10049ffc8();
  }
  else {
    _swift_retain();
    _swift_retain(lVar43);
    uVar18 = unaff_x20 + lVar12;
    __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar18,lVar43 + lVar12);
    _swift_release();
    _swift_release();
    lVar39 = lVar43;
    if ((uVar18 & 1) == 0) goto LAB_1006484ac;
    lVar9 = *(long *)(DAT_100b75e40 + 0x28);
    local_e0 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::automationChannel);
    if (local_e0 == 0) {
      local_e0 = lVar9;
      _swift_retain();
    }
    else {
      uVar30 = 0;
      thunk_FUN_1002db810(0x1c,PTR___swiftEmptyArrayStorage_100a1e050);
      lVar10 = DAT_100ae0030;
      if ((uVar30 & 1) == 0) {
        _swift_retain(lVar9);
        _swift_retain(local_e0);
        if (lVar10 != -1) {
          _swift_once(&DAT_100ae0030,FUN_1008174c0);
        }
        bVar6 = 0;
        FUN_100819fe0();
      }
      else {
        _swift_retain(local_e0);
        _swift_retain(lVar9);
        bVar6 = 1;
      }
      *(byte *)(local_e0 + 0x40) = bVar6 & 1;
      FUN_100883500();
      _swift_release();
    }
    if ((uVar7 & 0xff) - 1 < 2) {
      FUN_10064458c();
      lVar10 = *(long *)(local_e0 + 0x10);
      if (lVar10 != 0) {
        plVar37 = (long *)(local_e0 + 0x30);
        do {
          IVar38 = plVar37[-2];
          lVar11 = plVar37[-1];
          lVar12 = *plVar37;
          IVar44 = IVar38;
          _swift_getObjectType();
          pcVar42 = *(code **)(lVar12 + 0x18);
          _swift_unknownObjectRetain(IVar38);
          IVar26 = IVar44;
          (*pcVar42)(IVar44,lVar12);
          if (IVar26 == 0) {
            dVar56 = 0.0;
          }
          else {
            if (DAT_100adfbd0 != -1) {
              _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            }
            uVar41 = DAT_100b77550;
            _swift_retain(DAT_100b77550);
            FUN_100654a7c(IVar26,0,lVar9,FUN_100652494);
            _swift_release(uVar41);
            dVar56 = param_1;
          }
          lVar11 = *(long *)(lVar11 + 8);
          pcVar48 = *(code **)(lVar11 + 0x28);
          param_1 = dVar56;
          (*pcVar48)(dVar56,IVar44,lVar11);
          if (DAT_100adea10 != -1) {
            _swift_once(&DAT_100adea10,FUN_1001709a4);
          }
          uVar30 = DAT_100b757a8;
          FUN_100171514();
          if ((((((uVar30 & 1) != 0) && (IVar26 = IVar44, (*pcVar42)(IVar44,lVar12), IVar26 != 0))
               && (IVar26 = _objc_msgSend(IVar26,"isClickOrGuide"), IVar26 != 0)) &&
              ((IVar26 = _objc_msgSend(IVar26,"boolValue"), (IVar26 & 1) == 0 &&
               (IVar26 = IVar44, (*pcVar42)(IVar44,lVar12), IVar26 != 0)))) &&
             (IVar26 = _objc_msgSend(IVar26,"arrangement"), IVar26 != 0)) {
            _objc_msgSend(IVar26,"masterVolumeLevel");
            param_1 = dVar56 * param_1;
            (*pcVar48)(IVar44,lVar11);
          }
          _swift_unknownObjectRelease(IVar38);
          plVar37 = plVar37 + 3;
          lVar10 = lVar10 + -1;
        } while (lVar10 != 0);
      }
    }
    else {
      if ((uVar7 & 0xff) != 3) {
        _swift_release(lVar13);
        lVar13 = lVar9;
        goto LAB_10064a480;
      }
      FUN_10064458c();
      lVar10 = *(long *)(local_e0 + 0x10);
      if (lVar10 != 0) {
        plVar37 = (long *)(local_e0 + 0x30);
        do {
          IVar38 = plVar37[-2];
          lVar11 = plVar37[-1];
          lVar12 = *plVar37;
          IVar44 = IVar38;
          _swift_getObjectType();
          pcVar42 = *(code **)(lVar12 + 0x18);
          _swift_unknownObjectRetain(IVar38);
          IVar26 = IVar44;
          (*pcVar42)(IVar44,lVar12);
          if (((IVar26 == 0) || (IVar27 = _objc_msgSend(IVar26,"isClickOrGuide"), IVar27 == 0)) ||
             ((IVar27 = _objc_msgSend(IVar27,"boolValue"), (int)IVar27 == 0 ||
              (IVar26 = _objc_msgSend(IVar26,"partID"), IVar26 == 0)))) {
LAB_10064a2c8:
            IVar26 = IVar44;
            (*pcVar42)(IVar44,lVar12);
            if (IVar26 == 0) goto LAB_10064a1e0;
            IVar27 = _objc_msgSend(IVar26,"isClickOrGuide");
            if (((IVar27 != 0) && (IVar27 = _objc_msgSend(IVar27,"boolValue"), (int)IVar27 != 0)) &&
               (IVar26 = _objc_msgSend(IVar26,"partID"), IVar26 != 0)) {
              IVar26 = _objc_msgSend(IVar26,"integerValue");
              uVar7 = (uint)IVar26;
              FUN_10056fe0c();
              if ((uVar7 & 0xff) != 8 && (uVar7 & 0xff) != 1) goto LAB_10064a370;
              goto LAB_10064a1e0;
            }
            _swift_unknownObjectRelease(IVar38);
          }
          else {
            IVar26 = _objc_msgSend(IVar26,"integerValue");
            uVar7 = (uint)IVar26;
            FUN_10056fe0c();
            if ((uVar7 & 0xff) != 1 && (uVar7 & 0xff) != 8) goto LAB_10064a2c8;
LAB_10064a370:
            IVar26 = IVar44;
            (*pcVar42)(IVar44,lVar12);
            if (IVar26 == 0) {
              param_1 = 0.0;
            }
            else {
              if (DAT_100adfbd0 != -1) {
                _swift_once(&DAT_100adfbd0,FUN_1005d0614);
              }
              uVar41 = DAT_100b77550;
              _swift_retain(DAT_100b77550);
              FUN_100654a7c(IVar26,0,lVar9,FUN_100652494);
              _swift_release(uVar41);
            }
            lVar11 = *(long *)(lVar11 + 8);
            (**(code **)(lVar11 + 0x28))(param_1,IVar44,lVar11);
            IVar26 = IVar44;
            (*pcVar42)(IVar44,lVar12);
            if (IVar26 != 0) {
              if (DAT_100adfbd0 != -1) {
                _swift_once(&DAT_100adfbd0,FUN_1005d0614);
              }
              uVar41 = DAT_100b77550;
              _swift_retain(DAT_100b77550);
              FUN_1005db378(IVar26,0,uVar41);
              _swift_release(uVar41);
              (**(code **)(lVar11 + 0x10))((uint)IVar26 & 1,IVar44,lVar11);
            }
LAB_10064a1e0:
            _swift_unknownObjectRelease(IVar38);
          }
          plVar37 = plVar37 + 3;
          lVar10 = lVar10 + -1;
        } while (lVar10 != 0);
      }
    }
    _swift_bridgeObjectRelease(local_e0);
  }
  _swift_release(lVar9);
LAB_10064a480:
  _swift_release(lVar13);
  return lVar13;
  while( true ) {
    _swift_release(lVar45);
    lVar47 = lVar47 + 1;
    if (uVar46 == uVar18) break;
LAB_100649ad0:
    lVar50 = lVar47 + -4;
    if (uVar19 == 0) {
      lVar45 = *(long *)(uVar36 + lVar47 * 8);
      _swift_retain(lVar45);
    }
    else {
      lVar45 = lVar50;
      FUN_1000cda30(lVar50,uVar36);
    }
    uVar46 = lVar47 - 3;
    if (SCARRY8(lVar50,1)) {
                    /* WARNING: Does not return */
      pcVar42 = (code *)SoftwareBreakpoint(1,0x10064a53c);
      (*pcVar42)();
    }
    if (*(char *)(lVar45 + 0x50) == '\x02') goto LAB_1006488f4;
  }
  _swift_bridgeObjectRelease_n(uVar36,2);
  local_17c = 0;
LAB_100648a30:
  uVar18 = *(ulong *)(unaff_x20 + local_230);
  if (uVar18 >> 0x3e == 0) {
    uVar36 = *(ulong *)((uVar18 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar36 = uVar18 & 0xffffffffffffff8;
    if ((long)uVar18 < 0) {
      uVar36 = uVar18;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar36 == 0) {
    _swift_unknownObjectRelease(uVar30);
  }
  else {
    if ((long)uVar36 < 1) {
                    /* WARNING: Does not return */
      pcVar42 = (code *)SoftwareBreakpoint(1,0x10064a540);
      (*pcVar42)();
    }
    local_198 = uVar18 & 0xc000000000000001;
    local_1f0 = uVar18 + 0x20;
    local_1d0 = uVar18;
    _swift_bridgeObjectRetain();
    uVar18 = 0;
    local_1a0 = uVar36;
    do {
      if (local_198 == 0) {
        uVar36 = *(ulong *)(local_1f0 + uVar18 * 8);
        _swift_retain(uVar36);
        uVar19 = *(ulong *)(uVar36 + 0x28);
        if (uVar19 != 0) goto LAB_100648b20;
LAB_100648be8:
        dVar52 = dVar51;
        dVar51 = 0.0;
      }
      else {
        uVar36 = uVar18;
        FUN_1000cdac4(uVar18,local_1d0);
        uVar19 = *(ulong *)(uVar36 + 0x28);
        if (uVar19 == 0) goto LAB_100648be8;
LAB_100648b20:
        if (((ulong)((double *)(uVar19 + _TtC8Playback9SongTrack::currentFadeVolume))[1] & 1) == 0)
        {
          dVar52 = dVar51;
          dVar51 = *(double *)(uVar19 + _TtC8Playback9SongTrack::currentFadeVolume);
        }
        else {
          if (DAT_100adfbd0 != -1) {
            _swift_once(&DAT_100adfbd0,FUN_1005d0614);
          }
          uVar41 = DAT_100b77550;
          uVar20 = 0;
          FUN_100286674();
          uVar46 = uVar19;
          _swift_dynamicCastClass(uVar19,uVar20);
          if ((uVar46 == 0) ||
             (lVar12 = *(long *)(DAT_100b75e40 + 0x18), local_1e0 = uVar19, lVar12 == 0)) {
            _swift_retain(uVar41);
            FUN_100652494(0,uVar19,0);
            dVar52 = dVar51;
            _swift_release(uVar41);
          }
          else {
            IVar38 = *(ID *)(lVar12 + 0x78);
            local_218 = uVar20;
            local_208 = uVar46;
            if (IVar38 == 0) {
              IVar38 = *(ID *)(lVar12 + 0x10);
              IVar44 = 0;
              FUN_10073f4a4();
              _swift_allocObject();
              puVar16 = &_OBJC_CLASS___AVAudioMixerNode;
              _objc_allocWithZone();
              local_200 = uVar41;
              _swift_retain(uVar41);
              _swift_retain(lVar12);
              local_228 = IVar38;
              IVar38 = _objc_msgSend((ID)puVar16,"init");
              *(ID *)(IVar44 + 0x10) = IVar38;
              _swift_unknownObjectWeakInit(IVar44 + 0x18,0);
              *(undefined1 *)(IVar44 + 0x20) = 1;
              puVar16 = &DAT_100af5be0;
              FUN_100021774();
              _swift_allocObject();
              uVar41 = 0;
              puVar21 = &DAT_100af52a0;
              local_250 = puVar16;
              FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
              lVar45 = local_1c0;
              local_b8 = (undefined *)0x755163696d6f7441;
              local_b0 = 0xec0000005f657565;
              local_258 = uVar41;
              __s10Foundation4UUIDVACycfC(local_1c0);
              __s10Foundation4UUIDV10uuidStringSSvg();
              (**(code **)(local_1b8 + 8))(lVar45,local_1b0);
              __sSS6appendyySSF(uVar41,puVar21);
              _swift_bridgeObjectRelease(puVar21);
              uVar20 = local_b0;
              puVar22 = local_b8;
              __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar34);
              puVar17 = PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVMa_100a1e0d0;
              puVar15 = PTR___swiftEmptyArrayStorage_100a1e050;
              local_b8 = PTR___swiftEmptyArrayStorage_100a1e050;
              puVar16 = &DAT_100af5be8;
              FUN_100023140(&DAT_100af5be8,
                            PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVMa_100a1e0d0,
                            PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVs10SetAlgebraACMc_100a1e0e0
                           );
              _swift_retain(puVar15);
              puVar15 = &DAT_100af5bf0;
              FUN_100021774(&DAT_100af5bf0);
              puVar21 = &DAT_100af5bf8;
              FUN_1001d598c(&DAT_100af5bf8,&DAT_100af5c00,puVar17);
              __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                        (lVar33,&local_b8,puVar15,puVar21,lVar11,puVar16);
              (**(code **)(lVar31 + 0x68))(lVar32,local_234,lVar10);
              uVar41 = local_200;
              __sSo17OS_dispatch_queueC8DispatchE5label3qos10attributes20autoreleaseFrequency6targetABSS_AC0D3QoSVAbCE10AttributesVAbCE011AutoreleaseI0OABSgtcfC
                        (puVar22,uVar20,lVar34,lVar33,lVar32,0);
              *(undefined8 *)(local_250 + 0x18) = 0;
              *(undefined8 *)(local_250 + 0x20) = 0;
              *(undefined **)(local_250 + 0x10) = puVar22;
              *(undefined **)(IVar44 + 0x28) = local_250;
              _swift_weakInit(IVar44 + 0x30,0);
              IVar38 = local_228;
              *(undefined2 *)(IVar44 + 0x38) = 0;
              puVar16 = PTR___swiftEmptyArrayStorage_100a1e050;
              *(undefined **)(IVar44 + 0x40) = PTR___swiftEmptyArrayStorage_100a1e050;
              *(undefined8 *)(IVar44 + 0x48) = 0;
              _swift_unknownObjectWeakAssign(IVar44 + 0x18,local_228);
              uVar20 = *(undefined8 *)(IVar44 + 0x10);
              _swift_retain(puVar16);
              _objc_msgSend(IVar38,"attachNode:",uVar20);
              uVar20 = *(undefined8 *)(lVar12 + 0x78);
              *(ID *)(lVar12 + 0x78) = IVar44;
              _swift_retain(IVar44);
              _swift_release(uVar20);
              IVar38 = 0;
            }
            else {
              _swift_retain(uVar41);
              _swift_retain(lVar12);
              IVar44 = IVar38;
            }
            _swift_retain(IVar38);
            _swift_release(lVar12);
            if (*(long *)(DAT_100b75e40 + 0x20) == 0) {
              if (*(byte *)(IVar44 + 0x38) != 0) {
LAB_100648f50:
                uVar19 = local_1e0;
                local_228 = IVar44;
                FUN_1005c9754();
                if (uVar19 >> 0x3e == 0) {
                  uVar46 = *(ulong *)((uVar19 & 0xfffffffffffff8) + 0x10);
                }
                else {
                  uVar46 = uVar19 & 0xffffffffffffff8;
                  if ((long)uVar19 < 0) {
                    uVar46 = uVar19;
                  }
                  __ss18_CocoaArrayWrapperV8endIndexSivg();
                }
                if (uVar46 != 0) {
                  uVar2 = uVar19 & 0xc000000000000001;
                  if (uVar2 == 0) {
                    lVar12 = *(long *)(uVar19 + 0x20);
                    _swift_bridgeObjectRetain(uVar19);
                    _swift_retain(lVar12);
                  }
                  else {
                    _swift_bridgeObjectRetain(uVar19);
                    lVar12 = 0;
                    FUN_1000cda30(0,uVar19);
                  }
                  if (*(char *)(lVar12 + 0x50) == '\x02') {
LAB_100648fa4:
                    _swift_bridgeObjectRelease_n(uVar19,2);
                    bVar6 = *(byte *)(lVar12 + 0x39);
                    _swift_release(lVar12);
                    IVar44 = local_228;
                    if (2 < bVar6 - 2) goto LAB_100649070;
                    IVar38 = _objc_msgSend(local_208,"partID");
                    uVar7 = (uint)IVar38;
                    FUN_10056fe0c();
                    lVar12 = *(long *)(DAT_100b75e40 + 0x18);
                    if ((uVar7 & 0xff) == 0xf) {
                      if (lVar12 == 0) {
                        _swift_release(local_228);
                        dVar55 = 0.0;
                      }
                      else {
                        lVar45 = *(long *)(lVar12 + 0x78);
                        if (lVar45 == 0) {
                          lVar45 = *(long *)(lVar12 + 0x10);
                          local_200 = uVar41;
                          FUN_10073f4a4(0);
                          _swift_allocObject();
                          _swift_retain(lVar12);
                          FUN_10074128c();
                          uVar41 = *(undefined8 *)(lVar12 + 0x78);
                          *(long *)(lVar12 + 0x78) = lVar45;
                          _swift_retain(lVar45);
                          _swift_release(uVar41);
                          lVar47 = 0;
                        }
                        else {
                          local_200 = uVar41;
                          _swift_retain(lVar12);
                          lVar47 = lVar45;
                        }
                        _swift_retain(lVar47);
                        _swift_release(lVar12);
                        IVar38 = *(ID *)(lVar45 + 0x10);
                        _swift_release(lVar45);
                        _objc_msgSend(IVar38,"volume");
                        fVar5 = SUB84(dVar51,0);
                        _swift_release(local_228);
                        dVar55 = (double)fVar5;
                        uVar41 = local_200;
                      }
                    }
                    else {
                      IVar38 = local_228;
                      if (lVar12 != 0) {
                        IVar38 = *(ID *)(lVar12 + 0x78);
                        if (IVar38 == 0) {
                          IVar38 = *(ID *)(lVar12 + 0x10);
                          local_200 = uVar41;
                          FUN_10073f4a4(0);
                          _swift_allocObject();
                          _swift_retain(lVar12);
                          FUN_10074128c();
                          uVar41 = *(undefined8 *)(lVar12 + 0x78);
                          *(ID *)(lVar12 + 0x78) = IVar38;
                          _swift_retain(IVar38);
                          _swift_release(uVar41);
                          IVar44 = 0;
                        }
                        else {
                          local_200 = uVar41;
                          _swift_retain(lVar12);
                          IVar44 = IVar38;
                        }
                        _swift_retain(IVar44);
                        _swift_release(lVar12);
                        _swift_beginAccess(IVar38 + 0x40,auStack_d0,0,0);
                        uVar19 = *(ulong *)(IVar38 + 0x40);
                        if (uVar19 >> 0x3e == 0) {
                          uVar46 = *(ulong *)((uVar19 & 0xfffffffffffff8) + 0x10);
                        }
                        else {
                          uVar46 = uVar19 & 0xffffffffffffff8;
                          if ((long)uVar19 < 0) {
                            uVar46 = uVar19;
                          }
                          __ss18_CocoaArrayWrapperV8endIndexSivg();
                        }
                        uVar41 = local_200;
                        if (uVar46 != 0) {
                          if ((uVar19 & 0xc000000000000001) == 0) {
                            if (*(long *)((uVar19 & 0xfffffffffffff8) + 0x10) == 0) {
                    /* WARNING: Does not return */
                              pcVar42 = (code *)SoftwareBreakpoint(1,0x10064a544);
                              (*pcVar42)();
                            }
                            lVar12 = *(long *)(uVar19 + 0x20);
                            _swift_retain(lVar12);
                            _swift_release(IVar38);
                          }
                          else {
                            _swift_bridgeObjectRetain(uVar19);
                            lVar12 = 0;
                            FUN_1000cc648(0,uVar19);
                            _swift_release(IVar38);
                            _swift_bridgeObjectRelease(uVar19);
                          }
                          puVar16 = *(undefined **)
                                     (lVar12 + _TtC8Playback15PadChannelGroup::channels);
                          _swift_bridgeObjectRetain(puVar16);
                          _swift_release(lVar12);
                          lVar12 = *(long *)(puVar16 + 0x10);
                          if (lVar12 == 0) {
                            _swift_release(local_228);
                            _swift_bridgeObjectRelease(puVar16);
                          }
                          else {
                            _swift_bridgeObjectRetain(puVar16);
                            plVar37 = (long *)(puVar16 + 0x28);
                            dVar55 = dVar51;
                            local_250 = puVar16;
                            do {
                              pcVar3 = (class_t *)plVar37[-1];
                              lVar45 = *plVar37;
                              pcVar24 = pcVar3;
                              _object_getClass();
                              if (pcVar24 == &objc::class_t::_TtC8Playback20PadPlayerFileChannel &&
                                  pcVar3 != (class_t *)0x0) {
                                ppcVar25 = &pcVar3[1].data;
                                _swift_unknownObjectWeakLoadStrong();
                                if (ppcVar25 != (class_rw_t **)0x0) {
                                  _swift_unknownObjectRetain(pcVar3);
                                  __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(ppcVar25,local_208);
                                  if (((ulong)ppcVar25 & 1) != 0) {
                                    _swift_bridgeObjectRelease_n(local_250,2);
                                    _swift_getObjectType(pcVar3);
                                    (**(code **)(lVar45 + 0x20))();
                                    dVar51 = dVar55;
                                    _swift_release(local_228);
                                    _swift_unknownObjectRelease(pcVar3);
                                    uVar41 = local_200;
                                    goto LAB_10064999c;
                                  }
                                  _swift_unknownObjectRelease(pcVar3);
                                  uVar41 = local_200;
                                }
                              }
                              plVar37 = plVar37 + 2;
                              lVar12 = lVar12 + -1;
                            } while (lVar12 != 0);
                            _swift_release(local_228);
                            _swift_bridgeObjectRelease_n(local_250,2);
                            dVar51 = dVar55;
                          }
                          dVar55 = 0.0;
                          goto LAB_10064999c;
                        }
                        _swift_release(local_228);
                      }
                      _swift_release(IVar38);
                      dVar55 = 0.0;
                    }
LAB_10064999c:
                    _swift_release(uVar41);
                    dVar52 = dVar51;
                    dVar51 = dVar55;
                    goto LAB_1006490bc;
                  }
                  local_200 = uVar41;
                  _swift_release(lVar12);
                  if (uVar46 != 1) {
                    if (uVar2 == 0) {
                      lVar12 = *(long *)(uVar19 + 0x28);
                      _swift_retain(lVar12);
                    }
                    else {
                      lVar12 = 1;
                      FUN_1000cda30(1,uVar19);
                    }
                    uVar41 = local_200;
                    if (*(char *)(lVar12 + 0x50) == '\x02') goto LAB_100648fa4;
                    _swift_release(lVar12);
                    if (uVar46 != 2) {
                      lVar45 = 6;
                      do {
                        lVar47 = lVar45 + -4;
                        if (uVar2 == 0) {
                          lVar12 = *(long *)(uVar19 + lVar45 * 8);
                          _swift_retain(lVar12);
                        }
                        else {
                          lVar12 = lVar47;
                          FUN_1000cda30(lVar47,uVar19);
                        }
                        uVar1 = lVar45 - 3;
                        if (SCARRY8(lVar47,1)) {
                    /* WARNING: Does not return */
                          pcVar42 = (code *)SoftwareBreakpoint(1,0x10064a538);
                          (*pcVar42)();
                        }
                        uVar41 = local_200;
                        if (*(char *)(lVar12 + 0x50) == '\x02') goto LAB_100648fa4;
                        _swift_release(lVar12);
                        lVar45 = lVar45 + 1;
                      } while (uVar1 != uVar46);
                    }
                  }
                  _swift_bridgeObjectRelease(uVar19);
                  uVar41 = local_200;
                }
                _swift_bridgeObjectRelease(uVar19);
                IVar44 = local_228;
              }
            }
            else if (((*(byte *)(*(long *)(DAT_100b75e40 + 0x20) +
                                _TtC8Playback9Sequencer::privatePlayState) & 1) == 0) &&
                    (((*(byte *)(IVar44 + 0x38) ^ 1) & 1) == 0)) goto LAB_100648f50;
LAB_100649070:
            FUN_100652494(0,local_1e0,0);
            dVar52 = dVar51;
            _swift_release(uVar41);
            _swift_release(IVar44);
          }
        }
      }
LAB_1006490bc:
      lVar12 = local_1c8;
      dVar55 = dVar56;
      if (local_17c == 0) {
        *(double *)(uVar36 + 0x38) = dVar51;
        dVar51 = 0.0;
        if (((*(ID *)(uVar36 + 0x28) != 0) &&
            (IVar38 = _objc_msgSend(*(ID *)(uVar36 + 0x28),"arrangement"), IVar38 != 0)) &&
           (FUN_1002dbb48(), IVar38 != 0)) {
          if (((ulong)((double *)(IVar38 + _TtC8Playback9SongTrack::currentFadeVolume))[1] & 1) == 0
             ) {
            dVar51 = *(double *)(IVar38 + _TtC8Playback9SongTrack::currentFadeVolume);
          }
          else {
            if (DAT_100adfbd0 != -1) {
              _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            }
            uVar41 = DAT_100b77550;
            _swift_retain(DAT_100b77550);
            FUN_100654a7c(IVar38,0,0,FUN_100652494);
            _swift_release(uVar41);
            dVar51 = dVar52;
          }
        }
        dVar53 = *(double *)(uVar36 + 0x38);
        dVar52 = 1.0;
        if (dVar53 <= 1.0) {
          dVar52 = dVar53;
        }
        dVar54 = dVar56;
        if (0.0001 < dVar53) {
          dVar54 = dVar52;
        }
        dVar51 = dVar51 * *(double *)(uVar36 + 0x48) * dVar54;
        dVar52 = 1.0;
        if (dVar51 <= 1.0) {
          dVar52 = dVar51;
        }
        if (0.0001 < dVar51) {
          dVar55 = dVar52;
        }
        IVar38 = *(ID *)(uVar36 + 0x60);
        (**(code **)(lVar29 + 0x38))(lVar49,1,1,lVar9);
        lVar45 = local_170;
        FUN_100214f00(lVar49,local_170);
        lVar50 = lVar45;
        (**(code **)(lVar29 + 0x30))(lVar45,1,lVar9);
        lVar47 = local_160;
        lVar12 = lVar49;
        if ((int)lVar50 != 1) {
          (**(code **)(lVar29 + 0x20))(local_160,lVar45,lVar9);
          puVar23 = local_188;
          puVar16 = (undefined *)(dVar55 * 1000.0);
          local_b8 = puVar16;
          (**(code **)(lVar29 + 0x10))(local_188,lVar47,lVar9);
          (**(code **)(lVar29 + 0x58))(puVar23,lVar9);
          iVar8 = (int)puVar23;
          if (iVar8 == local_1e4) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else if (iVar8 == local_1f4) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else if (iVar8 == local_20c) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else if (iVar8 == local_21c) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else if (iVar8 == local_244) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else if (iVar8 == local_25c) {
            puVar16 = (undefined *)(long)(double)puVar16;
          }
          else {
            __sSd14_roundSlowPathyys25FloatingPointRoundingRuleOF(local_160);
            (**(code **)(lVar29 + 8))(local_188,lVar9);
            puVar16 = local_b8;
          }
          (**(code **)(lVar29 + 8))(local_160,lVar9);
          puVar23 = &stack0xffffffffffffffc0;
          goto LAB_100649544;
        }
LAB_100648a94:
        FUN_100023be4(lVar45,&DAT_100af5490);
        puVar16 = (undefined *)(long)(dVar55 * 1000.0);
      }
      else {
        dVar52 = 1.0;
        if (dVar51 <= 1.0) {
          dVar52 = dVar51;
        }
        dVar53 = dVar56;
        if (0.0001 < dVar51) {
          dVar53 = dVar52;
        }
        dVar52 = dVar53 * *(double *)(uVar36 + 0x48) * 0.0;
        dVar51 = 1.0;
        if (dVar52 <= 1.0) {
          dVar51 = dVar52;
        }
        if (0.0001 < dVar52) {
          dVar55 = dVar51;
        }
        IVar38 = *(ID *)(uVar36 + 0x60);
        (**(code **)(lVar29 + 0x38))(local_1c8,1,1,lVar9);
        lVar45 = local_178;
        FUN_100214f00(lVar12,local_178);
        lVar50 = lVar45;
        (**(code **)(lVar29 + 0x30))(lVar45,1,lVar9);
        lVar47 = local_168;
        if ((int)lVar50 == 1) goto LAB_100648a94;
        (**(code **)(lVar29 + 0x20))(local_168,lVar45,lVar9);
        lVar12 = local_190;
        puVar16 = (undefined *)(dVar55 * 1000.0);
        local_b8 = puVar16;
        (**(code **)(lVar29 + 0x10))(local_190,lVar47,lVar9);
        (**(code **)(lVar29 + 0x58))(lVar12,lVar9);
        iVar8 = (int)lVar12;
        if (iVar8 == local_1e4) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else if (iVar8 == local_1f4) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else if (iVar8 == local_20c) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else if (iVar8 == local_21c) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else if (iVar8 == local_244) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else if (iVar8 == local_25c) {
          puVar16 = (undefined *)(long)(double)puVar16;
        }
        else {
          __sSd14_roundSlowPathyys25FloatingPointRoundingRuleOF(local_168);
          (**(code **)(lVar29 + 8))(local_190,lVar9);
          puVar16 = local_b8;
        }
        (**(code **)(lVar29 + 8))(local_168,lVar9);
        puVar23 = auStack_c8;
LAB_100649544:
        lVar12 = *(long *)(puVar23 + -0x100);
      }
      uVar18 = uVar18 + 1;
      FUN_100023be4(lVar12,&DAT_100af5490);
      dVar51 = (double)(ulong)(uint)(float)((double)puVar16 / 1000.0);
      _objc_msgSend(IVar38,"setVolume:");
      _swift_release(uVar36);
    } while (uVar18 != local_1a0);
    _swift_unknownObjectRelease(uVar30);
    _swift_bridgeObjectRelease(local_1d0);
    lVar12 = local_150;
  }
  _swift_unknownObjectRelease(IVar26);
LAB_1006485e0:
  lVar43 = lVar43 + 1;
  if (lVar43 == lVar12) goto LAB_100649eac;
  goto LAB_1006485ec;
LAB_1006488f4:
  _swift_bridgeObjectRelease_n(uVar36,2);
  cVar4 = *(char *)(lVar45 + 0x39);
  _swift_release(lVar45);
  local_17c = (uint)(cVar4 == '\x02');
  goto LAB_100648a30;
LAB_100649eac:
  _swift_release(lVar13);
  lVar39 = local_1a8;
  goto LAB_100649ec0;
}

// ==== 10064aba8 FUN_10064aba8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_10064aba8(double param_1,double param_2,ulong param_3)

{
  class_t *pcVar1;
  long lVar2;
  double dVar3;
  long lVar4;
  class_t *pcVar5;
  undefined *puVar6;
  long unaff_x20;
  ID IVar7;
  ID self;
  long *plVar8;
  undefined8 uVar9;
  long lVar10;
  undefined1 auStack_98 [24];
  
  lVar4 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::allChannels);
  lVar10 = *(long *)(lVar4 + 0x10);
  if (lVar10 != 0) {
    _swift_bridgeObjectRetain();
    plVar8 = (long *)(lVar4 + 0x28);
    do {
      pcVar1 = (class_t *)plVar8[-1];
      lVar2 = *plVar8;
      pcVar5 = pcVar1;
      _object_getClass();
      if (pcVar5 == &objc::class_t::_TtC8Playback12TrackChannel && pcVar1 != (class_t *)0x0) {
        pcVar5 = pcVar1;
        _swift_unknownObjectRetain();
        FUN_100653b84();
        if (((ulong)pcVar5 & 1) == 0) {
joined_r0x00010064ac8c:
          if ((param_3 & 1) != 0) goto LAB_10064ad70;
        }
LAB_10064ac1c:
        _swift_unknownObjectRelease(pcVar1);
      }
      else {
        if (pcVar5 == &objc::class_t::_TtC8Playback12ClickChannel && pcVar1 != (class_t *)0x0) {
          IVar7 = pcVar1[2].cache;
          _swift_unknownObjectRetain_n(pcVar1,2);
          IVar7 = _objc_msgSend(IVar7,"AUAudioUnit");
          puVar6 = &_OBJC_CLASS___ClickAudioUnit;
          _swift_getInitializedObjCClass(&_OBJC_CLASS___ClickAudioUnit);
          _swift_dynamicCastObjCClass(IVar7,puVar6);
          dVar3 = param_1;
        }
        else {
          if (pcVar5 != &objc::class_t::_TtC8Playback12GuideChannel || pcVar1 == (class_t *)0x0) {
            _swift_unknownObjectRetain(pcVar1);
            goto joined_r0x00010064ac8c;
          }
          IVar7 = pcVar1[2].cache;
          _swift_unknownObjectRetain_n(pcVar1,2);
          IVar7 = _objc_msgSend(IVar7,"AUAudioUnit");
          puVar6 = &_OBJC_CLASS___GuideAudioUnit;
          _swift_getInitializedObjCClass(&_OBJC_CLASS___GuideAudioUnit);
          _swift_dynamicCastObjCClass(IVar7,puVar6);
          dVar3 = param_2;
        }
        if (IVar7 != 0) {
          _objc_msgSend(IVar7,"prepareToPlayFromTime:",(ulong)(uint)(float)dVar3);
        }
        _swift_unknownObjectRelease(pcVar1);
        if ((param_3 & 1) == 0) goto LAB_10064ac1c;
LAB_10064ad70:
        pcVar5 = pcVar1;
        _swift_getObjectType();
        (**(code **)(lVar2 + 8))();
        _objc_msgSend((ID)pcVar5,"reset");
        _swift_unknownObjectRelease(pcVar1);
      }
      plVar8 = plVar8 + 2;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    _swift_bridgeObjectRelease(lVar4);
  }
  lVar10 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::automationChannel);
  if (lVar10 != 0) {
    IVar7 = *(ID *)(lVar10 + 0x38);
    _swift_retain(lVar10);
    IVar7 = _objc_msgSend(IVar7,"AUAudioUnit");
    puVar6 = &_OBJC_CLASS___AutomationAudioUnit;
    _swift_getInitializedObjCClass(&_OBJC_CLASS___AutomationAudioUnit);
    _swift_dynamicCastObjCClass(IVar7,puVar6);
    if (IVar7 != 0) {
      _objc_msgSend(IVar7,"prepareToPlayFromTime:",param_2);
    }
    _swift_release(lVar10);
  }
  lVar10 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::midiOutChannel);
  if (lVar10 != 0) {
    self = *(ID *)(lVar10 + 0x38);
    _swift_retain(lVar10);
    IVar7 = _objc_msgSend(self,"AUAudioUnit");
    puVar6 = &_OBJC_CLASS___MIDIOutAudioUnit;
    _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
    _swift_dynamicCastObjCClass(IVar7,puVar6);
    lVar4 = _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents;
    if (IVar7 != 0) {
      _swift_beginAccess(self + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents,auStack_98,1,
                         0);
      uVar9 = *(undefined8 *)(self + lVar4);
      *(undefined **)(self + lVar4) = PTR___swiftEmptyArrayStorage_100a1e050;
      _swift_retain();
      _swift_bridgeObjectRelease(uVar9);
      _objc_msgSend(IVar7,"prepareToPlayFromTime:",(ulong)(uint)(float)param_2);
    }
    _swift_release(lVar10);
  }
  lVar10 = *(long *)(unaff_x20 + _TtC8Playback16SongChannelGroup::masterChannel);
  if (lVar10 != 0) {
    IVar7 = *(ID *)(lVar10 + 0x60);
    _swift_retain(lVar10);
    IVar7 = _objc_msgSend(IVar7,"AUAudioUnit");
    puVar6 = &_OBJC_CLASS___BufferedFilePlaybackAudioUnit;
    _swift_getInitializedObjCClass(&_OBJC_CLASS___BufferedFilePlaybackAudioUnit);
    _swift_dynamicCastObjCClass(IVar7,puVar6);
    if (IVar7 != 0) {
      _objc_msgSend(IVar7,"prepareToPlayFromTime:",(ulong)(uint)(float)param_1);
    }
    _swift_release(lVar10);
  }
  return;
}

// ==== 100653da0 FUN_100653da0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_100653da0(undefined8 param_1,class_t *param_2)

{
  long lVar1;
  undefined1 *puVar2;
  code *pcVar3;
  class_t *pcVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ID IVar9;
  ID IVar10;
  ID IVar11;
  ID IVar12;
  undefined *puVar13;
  long lVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  undefined1 auStack_f0 [8];
  ID local_e8;
  ID IStack_e0;
  ID local_d8;
  ID IStack_d0;
  undefined1 *local_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined *local_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined4 local_90;
  objc_super local_80;
  
  pcVar4 = param_2;
  _swift_getObjectType();
  puVar5 = &DAT_100b00798;
  FUN_100021774();
  local_c8 = auStack_f0 + -(*(long *)(*(long *)(puVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(undefined1 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::playState) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::startTime) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::endTime) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::enqueuedStartTime) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::enqueuedEndTime) = 0;
  puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
  *(undefined **)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents) =
       PTR___swiftEmptyArrayStorage_100a1e050;
  *(undefined **)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::currentNoteOnEvents) =
       puVar5;
  lVar14 = (long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::delegate;
  *(undefined8 *)(lVar14 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar14,0);
  *(undefined1 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) = 0;
  lVar1 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  puVar6 = puVar5;
  FUN_10079d380();
  *(undefined **)((long)&param_2->isa + lVar1) = puVar6;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::parameterObserverToken) =
       0;
  *(undefined1 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::prerollOffsetTime) = 0;
  *(undefined8 *)((long)&param_2->isa + _TtC8Playback18MIDIOutAVAudioUnit::rewindTime) = 0;
  puVar6 = &_OBJC_CLASS___AUAudioUnit;
  _swift_getInitializedObjCClass();
  uVar7 = 0;
  FUN_100023404(0,&DAT_100b07228,&PTR__OBJC_CLASS___MIDIOutAudioUnit_100aa4200);
  _swift_getObjCClassFromMetadata();
  _swift_retain_n(puVar5,2);
  uVar8 = 0x494d203a534b544d;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x494d203a534b544d,0xee0074754f204944);
  uStack_b8 = 0x24d544b53;
  local_c0 = 0x6d646f746175676e;
  uStack_98 = 0x24d544b53;
  local_a0 = 0x6d646f746175676e;
  local_90 = 0;
  _objc_msgSend((ID)puVar6,"registerSubclass:asComponentDescription:name:version:",uVar7,&local_a0,
                uVar8,0xffffffff);
  *(undefined ***)(lVar14 + 8) = &PTR_PTR_100a35e60;
  _swift_unknownObjectWeakAssign(lVar14,param_1);
  uStack_98 = uStack_b8;
  local_a0 = local_c0;
  local_90 = 0;
  local_80.receiver = (ID)param_2;
  local_80.super_class = pcVar4;
  IVar9 = _objc_msgSendSuper2(&local_80,"initWithAudioComponentDescription:",&local_a0);
  IVar10 = _objc_msgSend(IVar9,"AUAudioUnit");
  IVar10 = _objc_msgSend(IVar10,"parameterTree");
  if (IVar10 == 0) {
    _swift_release(param_1);
    return IVar9;
  }
  IVar11 = IVar10;
  FUN_1004a206c();
  lVar14 = _TtC8Playback18MIDIOutAVAudioUnit::parameters;
  _swift_beginAccess(IVar9 + _TtC8Playback18MIDIOutAVAudioUnit::parameters,&local_a0,1,0);
  uVar7 = *(undefined8 *)(IVar9 + lVar14);
  *(ID *)(IVar9 + lVar14) = IVar11;
  _swift_bridgeObjectRelease(uVar7);
  IVar12 = _objc_msgSend(IVar9,"AUAudioUnit");
  puVar6 = &_OBJC_CLASS___MIDIOutAudioUnit;
  _swift_getInitializedObjCClass(&_OBJC_CLASS___MIDIOutAudioUnit);
  IVar11 = IVar12;
  _swift_dynamicCastObjCClass(IVar12,puVar6);
  if (IVar11 == 0) {
    _swift_release(param_1);
    return IVar9;
  }
  puVar6 = (undefined *)(IVar9 + _TtC8Playback18MIDIOutAVAudioUnit::delegate);
  _swift_unknownObjectWeakLoadStrong();
  if (puVar6 != (undefined *)0x0) {
    puVar13 = puVar6;
    FUN_1001b3248();
    _swift_unknownObjectRelease(puVar6);
    if (puVar13 != (undefined *)0x0) goto LAB_1006540cc;
  }
  puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_1006540cc:
  lVar14 = _TtC8Playback18MIDIOutAVAudioUnit::midiEvents;
  uVar7 = *(undefined8 *)(IVar9 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents);
  *(undefined **)(IVar9 + _TtC8Playback18MIDIOutAVAudioUnit::midiEvents) = puVar13;
  _swift_bridgeObjectRelease(uVar7);
  uVar17 = *(ulong *)(IVar9 + lVar14);
  if (uVar17 >> 0x3e == 0) {
    uVar18 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
    puVar6 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    uVar18 = uVar17 & 0xffffffffffffff8;
    if ((long)uVar17 < 0) {
      uVar18 = uVar17;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar6 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar6;
  if (uVar18 == 0) {
    _swift_retain(puVar6);
  }
  else {
    local_a8 = puVar5;
    local_e8 = IVar11;
    IStack_e0 = IVar12;
    local_d8 = IVar10;
    IStack_d0 = IVar9;
    local_c0 = param_1;
    _swift_retain(puVar5);
    _swift_bridgeObjectRetain(uVar17);
    FUN_1001ccaac(0,uVar18 & ((long)uVar18 >> 0x3f ^ 0xffffffffffffffffU),0);
    if ((long)uVar18 < 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x1006543e0);
      (*pcVar3)();
    }
    uVar16 = 0;
    do {
      puVar5 = local_a8;
      if ((uVar17 & 0xc000000000000001) == 0) {
        uVar15 = *(ulong *)(uVar17 + uVar16 * 8 + 0x20);
        _swift_retain(uVar15);
      }
      else {
        uVar15 = uVar16;
        FUN_1000cc70c(uVar16,uVar17);
      }
      uVar7 = *(undefined8 *)(uVar15 + 0x28);
      puVar6 = &_OBJC_CLASS___NSNumber;
      _objc_allocWithZone();
      IVar9 = _objc_msgSend((ID)puVar6,"initWithDouble:",uVar7);
      _swift_release(uVar15);
      uVar15 = *(ulong *)(puVar5 + 0x10);
      local_a8 = puVar5;
      if (*(ulong *)(puVar5 + 0x18) >> 1 <= uVar15) {
        FUN_1001ccaac(1 < *(ulong *)(puVar5 + 0x18),uVar15 + 1,1);
      }
      puVar6 = local_a8;
      uVar16 = uVar16 + 1;
      *(ulong *)(local_a8 + 0x10) = uVar15 + 1;
      *(ID *)(local_a8 + uVar15 * 8 + 0x20) = IVar9;
    } while (uVar18 != uVar16);
    _swift_bridgeObjectRelease(uVar17);
    IVar9 = IStack_d0;
    param_1 = local_c0;
    IVar11 = local_e8;
  }
  uVar7 = 0;
  FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
  puVar5 = puVar6;
  __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar6,uVar7);
  _swift_bridgeObjectRelease(puVar6);
  _objc_msgSend(IVar11,"configureDSPKernelWithEventTimes:delegate:",puVar5,IVar9);
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar7 = DAT_100b757a8;
  FUN_1001736c4();
  *(byte *)(IVar9 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = ((byte)uVar7 ^ 0xff) & 1;
  FUN_10049ffc8(0);
  if (DAT_100adefa0 != -1) {
    _swift_once(&DAT_100adefa0,FUN_10037c47c);
  }
  uVar7 = DAT_100b75f50;
  lVar14 = 0;
  __s10Foundation12NotificationVMa();
  puVar2 = local_c8;
  (**(code **)(*(long *)(lVar14 + -8) + 0x38))(local_c8,1,1,lVar14);
  _swift_retain(uVar7);
  FUN_10037e2a4(puVar2);
  _swift_release(param_1);
  _swift_release(uVar7);
  FUN_100023be4(puVar2,&DAT_100b00798);
  return IVar9;
}

// ==== 1006c2bc4 FUN_1006c2bc4 ====
void FUN_1006c2bc4(undefined8 *param_1,undefined8 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined *puVar12;
  long lVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  ulong uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  long unaff_x20;
  long lVar21;
  undefined8 uVar22;
  long lVar23;
  long lVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 local_110;
  undefined4 local_108;
  undefined4 local_104;
  long local_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined1 auStack_d0 [24];
  undefined1 auStack_b8 [24];
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long local_88;
  undefined **local_80;
  
  puVar12 = &DAT_100af7158;
  FUN_100021774();
  uVar16 = *(long *)(*(long *)(puVar12 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar21 = (long)&local_110 - uVar16;
  lVar23 = lVar21 - uVar16;
  lVar24 = unaff_x20;
  FUN_1006c2ef0();
  local_104 = param_3;
  local_100 = lVar24;
  FUN_1006c3064(lVar23);
  lVar24 = unaff_x20;
  FUN_1006c3448();
  local_108 = (undefined4)lVar24;
  FUN_10003b4b4(lVar23,lVar21,&DAT_100af7158);
  lVar13 = 0;
  FUN_1004da4ec();
  lVar24 = lVar21;
  (**(code **)(*(long *)(lVar13 + -8) + 0x30))(lVar21,1,lVar13);
  if ((int)lVar24 == 1) {
    FUN_100023be4(lVar21,&DAT_100af7158);
    uStack_98 = 0;
    local_a0 = 0;
    local_88 = 0;
    uStack_90 = 0;
    local_80 = (undefined **)0x0;
  }
  else {
    local_80 = &PTR_PTR_100a4cd48;
    puVar14 = &local_a0;
    local_88 = lVar13;
    FUN_1000881c8(puVar14);
    FUN_100023340(lVar21,puVar14,FUN_1004da4ec);
  }
  lVar24 = _TtC8Playback31SongMenuMultiItemViewController::stagedStems;
  _swift_beginAccess(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedStems,
                     auStack_b8,0,0);
  uVar22 = *(undefined8 *)(unaff_x20 + lVar24);
  _swift_bridgeObjectRetain(uVar22);
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  FUN_100023be4(lVar23,&DAT_100af7158);
  lVar24 = _TtC8Playback31SongMenuMultiItemViewController::stagedPad;
  local_110 = *(undefined8 *)
               (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedKeyID);
  uVar25 = *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedTempo);
  uVar26 = *(undefined8 *)
            (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedStartTime);
  uVar5 = *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedFadeOut)
  ;
  _swift_beginAccess(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPad,
                     auStack_d0,0,0);
  FUN_10003b4b4(unaff_x20 + lVar24,&local_f8,&DAT_100af5d38);
  uVar6 = *(undefined1 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadUseDefault);
  uVar7 = *(undefined1 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadStartWithSong);
  uVar8 = *(undefined1 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadIntroOutroOnly);
  puVar14 = (undefined8 *)
            (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedLyricCuePack);
  uVar1 = *puVar14;
  uVar2 = puVar14[1];
  lVar24 = puVar14[2];
  if (lVar24 == 0) {
    uVar17 = 0;
    uVar18 = 0;
    uVar15 = 0;
  }
  else {
    uVar15 = *(undefined8 *)
              (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrievedMIDIEvents);
    _swift_bridgeObjectRetain();
    uVar17 = uVar1;
    uVar18 = uVar2;
  }
  uVar19 = *(undefined8 *)
            (unaff_x20 +
            _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistVelocity);
  uVar3 = *(undefined1 *)
           ((undefined8 *)
            (unaff_x20 +
            _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistVelocity) + 1)
  ;
  uVar20 = *(undefined8 *)
            (unaff_x20 +
            _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistItemVelocity);
  uVar9 = *(undefined1 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEEnabled);
  uVar4 = *(undefined1 *)
           ((undefined8 *)
            (unaff_x20 +
            _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistItemVelocity)
           + 1);
  uVar10 = *(undefined1 *)
            (unaff_x20 +
            _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEFollowsDefaultArrangement);
  uVar11 = *(undefined1 *)
            (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedModularClickLength);
  param_1[1] = uStack_98;
  *param_1 = local_a0;
  param_1[3] = local_88;
  param_1[2] = uStack_90;
  param_1[4] = local_80;
  param_1[5] = uVar22;
  param_1[6] = PTR___swiftEmptyArrayStorage_100a1e050;
  param_1[7] = local_110;
  param_1[8] = uVar25;
  *(char *)(param_1 + 9) = (char)local_108;
  param_1[10] = uVar26;
  param_1[0xb] = local_100;
  *(byte *)(param_1 + 0xc) = (byte)local_104 & 1;
  *(undefined1 *)((long)param_1 + 0x61) = uVar5;
  param_1[0x11] = local_d8;
  param_1[0x10] = uStack_e0;
  param_1[0xf] = local_e8;
  param_1[0xe] = uStack_f0;
  param_1[0xd] = local_f8;
  *(undefined1 *)(param_1 + 0x12) = uVar6;
  *(undefined1 *)((long)param_1 + 0x91) = uVar7;
  *(undefined1 *)((long)param_1 + 0x92) = uVar8;
  param_1[0x13] = uVar17;
  param_1[0x14] = uVar18;
  param_1[0x15] = lVar24;
  param_1[0x16] = uVar15;
  param_1[0x17] = uVar1;
  param_1[0x18] = uVar2;
  param_1[0x19] = lVar24;
  param_1[0x1a] = uVar19;
  *(undefined1 *)(param_1 + 0x1b) = uVar3;
  param_1[0x1c] = uVar20;
  *(undefined1 *)(param_1 + 0x1d) = uVar4;
  *(undefined1 *)((long)param_1 + 0xe9) = uVar9;
  *(undefined1 *)((long)param_1 + 0xea) = uVar10;
  *(undefined1 *)((long)param_1 + 0xeb) = uVar11;
  _swift_bridgeObjectRetain_n(lVar24,2);
  return;
}

// ==== 1006c36ac FUN_1006c36ac ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001006c3a94) */

ID FUN_1006c36ac(undefined8 param_1,ulong param_2)

{
  long *plVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  ID IVar5;
  undefined8 *puVar6;
  ulong uVar7;
  long unaff_x20;
  
  _swift_getObjectType();
  puVar6 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::previewPlayerComponents);
  puVar6[1] = 0;
  *puVar6 = 0;
  puVar6[3] = 0;
  puVar6[2] = 0;
  puVar6[5] = 0;
  puVar6[4] = 0;
  puVar6[7] = 0;
  puVar6[6] = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::previewPlayerProgress)
       = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::arrangements) = 0;
  puVar6 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedArrangement);
  puVar6[1] = 0;
  *puVar6 = 0;
  puVar6[3] = 0;
  puVar6[2] = 0;
  puVar6[4] = 0;
  puVar6 = (undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::errorDataType)
  ;
  *puVar6 = 0x676e6f53;
  puVar6[1] = 0xe400000000000000;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___resources) = 0;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::cachedTableViewSections) = 0;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___selectedResource)
       = 4;
  lVar3 = _TtC8Playback31SongMenuMultiItemViewController::stagedStems;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079cd7c();
  *(undefined **)(unaff_x20 + lVar3) = puVar2;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedKeyID) = 10;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedTempo) =
       0x405e000000000000;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedStartTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedEndTime) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedFadeOut) = 0;
  plVar1 = (long *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPad);
  lVar3 = DAT_100afb908;
  lVar4 = DAT_100afb908;
  if (DAT_100afb908 == 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    lVar3 = DAT_100b757a8;
    FUN_10017103c();
    FUN_1001d3358(lVar3,0x24);
    lVar4 = lVar3;
    if (lVar3 == 0) {
      FUN_1001d3a50();
      lVar4 = DAT_100afb908;
    }
  }
  DAT_100afb908 = lVar4;
  lVar4 = 0;
  FUN_1001cc624();
  plVar1[3] = lVar4;
  plVar1[4] = (long)&PTR_PTR_100a37040;
  *plVar1 = lVar3;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadUseDefault) =
       1;
  lVar3 = _TtC8Playback31SongMenuMultiItemViewController::stagedPadStartWithSong;
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar4 = DAT_100b757a8;
  FUN_10017156c();
  *(byte *)(unaff_x20 + lVar3) = (byte)lVar4 & 1;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadIntroOutroOnly) = 0;
  puVar6 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedLyricCuePack);
  puVar6[1] = 0;
  puVar6[2] = 0;
  *puVar6 = 0;
  puVar6 = (undefined8 *)
           (unaff_x20 +
           _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistVelocity);
  *puVar6 = 0;
  *(undefined1 *)(puVar6 + 1) = 1;
  puVar6 = (undefined8 *)
           (unaff_x20 +
           _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistItemVelocity);
  *puVar6 = 0;
  *(undefined1 *)(puVar6 + 1) = 1;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEEnabled) =
       1;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEFollowsDefaultArrangement
   ) = 0;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedModularClickLength) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrievedMIDIEvents) =
       0;
  lVar3 = _TtC8Playback31SongMenuMultiItemViewController::itemExpandedStates;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079d2a4();
  *(undefined **)(unaff_x20 + lVar3) = puVar2;
  puVar2 = PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined **)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::sectionsToReload) =
       PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined **)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::displayedSectionFooterMessages) =
       puVar2;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrieveGroupDataAttempted) = 0;
  *(undefined8 *)
   (unaff_x20 +
   _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___currentIncludedOrderedGenreIDs)
       = 0;
  FUN_100023384(param_1,unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::mode,
                FUN_1003bd850);
  _swift_retain_n(puVar2,2);
  IVar5 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff88,"initWithStyle:",1);
  if (((uint)param_2 & 0xff) != 4) {
    puVar6 = &_TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___resources;
    FUN_1004456a4(&_TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___resources,
                  FUN_1006bae9c);
    uVar7 = param_2;
    thunk_FUN_1002db810(param_2,puVar6);
    _swift_bridgeObjectRelease(puVar6);
    if ((uVar7 & 1) == 0) {
      FUN_1000233c8(param_1,FUN_1003bd850);
      return IVar5;
    }
    FUN_1006b69fc();
    *(char *)(IVar5 + _TtC8Playback31SongMenuMultiItemViewController::
                      ___lazy_storage___selectedResource) = (char)param_2;
    FUN_1006bda60();
  }
  FUN_1000233c8(param_1,FUN_1003bd850);
  return IVar5;
}

// ==== 1006c9bb4 _TtC8Playback31SongMenuMultiItemViewController::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback31SongMenuMultiItemViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  FUN_100023be4(param_1 + previewPlayerComponents,&DAT_100af7178);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + arrangements));
  FUN_100023be4(param_1 + stagedArrangement,&DAT_100af5810);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + errorDataType + 8));
  FUN_1000233c8(param_1 + mode,FUN_1003bd850);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + ___lazy_storage___resources));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + cachedTableViewSections));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + stagedStems));
  FUN_100023be4(param_1 + stagedPad,&DAT_100af5d38);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + stagedLyricCuePack + 0x10));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + retrievedMIDIEvents));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + itemExpandedStates));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + sectionsToReload));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + displayedSectionFooterMessages));
  _swift_bridgeObjectRelease
            (*(undefined8 *)(param_1 + ___lazy_storage___currentIncludedOrderedGenreIDs));
  return;
}

// ==== 1006cc344 FUN_1006cc344 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001006cc680) */

void FUN_1006cc344(void)

{
  undefined8 *puVar1;
  long *plVar2;
  code *pcVar3;
  undefined *puVar4;
  long lVar5;
  long lVar6;
  long unaff_x20;
  
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::previewPlayerComponents);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[7] = 0;
  puVar1[6] = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::previewPlayerProgress)
       = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::arrangements) = 0;
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedArrangement);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[4] = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::errorDataType)
  ;
  *puVar1 = 0x676e6f53;
  puVar1[1] = 0xe400000000000000;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___resources) = 0;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::cachedTableViewSections) = 0;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___selectedResource)
       = 4;
  lVar5 = _TtC8Playback31SongMenuMultiItemViewController::stagedStems;
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079cd7c();
  *(undefined **)(unaff_x20 + lVar5) = puVar4;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedKeyID) = 10;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedTempo) =
       0x405e000000000000;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedStartTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedEndTime) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedFadeOut) = 0;
  plVar2 = (long *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPad);
  lVar5 = DAT_100afb908;
  lVar6 = DAT_100afb908;
  if (DAT_100afb908 == 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    lVar5 = DAT_100b757a8;
    FUN_10017103c();
    FUN_1001d3358(lVar5,0x24);
    lVar6 = lVar5;
    if (lVar5 == 0) {
      FUN_1001d3a50();
      lVar6 = DAT_100afb908;
    }
  }
  DAT_100afb908 = lVar6;
  lVar6 = 0;
  FUN_1001cc624();
  plVar2[3] = lVar6;
  plVar2[4] = (long)&PTR_PTR_100a37040;
  *plVar2 = lVar5;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadUseDefault) =
       1;
  lVar5 = _TtC8Playback31SongMenuMultiItemViewController::stagedPadStartWithSong;
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar6 = DAT_100b757a8;
  FUN_10017156c();
  *(byte *)(unaff_x20 + lVar5) = (byte)lVar6 & 1;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedPadIntroOutroOnly) = 0;
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedLyricCuePack);
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  puVar1 = (undefined8 *)
           (unaff_x20 +
           _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistVelocity);
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 1) = 1;
  puVar1 = (undefined8 *)
           (unaff_x20 +
           _TtC8Playback31SongMenuMultiItemViewController::stagedProPresenterPlaylistItemVelocity);
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 1) = 1;
  *(undefined1 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEEnabled) =
       1;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedSMPTEFollowsDefaultArrangement
   ) = 0;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedModularClickLength) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrievedMIDIEvents) =
       0;
  lVar5 = _TtC8Playback31SongMenuMultiItemViewController::itemExpandedStates;
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079d2a4();
  *(undefined **)(unaff_x20 + lVar5) = puVar4;
  puVar4 = PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined **)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::sectionsToReload) =
       PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined **)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::displayedSectionFooterMessages) =
       puVar4;
  *(undefined1 *)
   (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrieveGroupDataAttempted) = 0;
  *(undefined8 *)
   (unaff_x20 +
   _TtC8Playback31SongMenuMultiItemViewController::___lazy_storage___currentIncludedOrderedGenreIDs)
       = 0;
  _swift_retain_n(puVar4,2);
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd00000000000001f,0x80000001008d0650,
             "Playback/SongMenuMultiItemTableViewController.swift",0x33,2,0x1c5,0);
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(1,0x1006cc674);
  (*pcVar3)();
}

// ==== 1006e5d6c FUN_1006e5d6c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1006e5d6c(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *puVar1;
  undefined1 *puVar2;
  code *pcVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  undefined *puVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  undefined *puVar12;
  ID self;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  ulong uVar19;
  ulong uVar20;
  long lVar21;
  ID unaff_x20;
  long lVar22;
  long lVar23;
  long lVar24;
  long lVar25;
  undefined1 auStack_e0 [8];
  long local_d8;
  long local_d0;
  long local_c8;
  undefined1 *local_c0;
  
  lVar5 = 0;
  FUN_1003c2e8c();
  local_d0 = *(long *)(lVar5 + -8);
  lVar13 = *(long *)(local_d0 + 0x40);
  lVar6 = 0;
  local_c8 = lVar5;
  local_c0 = auStack_e0 + -(lVar13 + 0xfU & 0xfffffffffffffff0);
  FUN_1007ac0bc();
  uVar14 = *(long *)(*(long *)(lVar6 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar17 = (long)(auStack_e0 + -(lVar13 + 0xfU & 0xfffffffffffffff0)) - uVar14;
  uVar14 = lVar17 - uVar14;
  lVar5 = 0;
  FUN_1007accf4();
  uVar15 = *(long *)(*(long *)(lVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar18 = uVar14 - uVar15;
  lVar16 = lVar18 - uVar15;
  puVar7 = &DAT_100b01360;
  FUN_100021774();
  lVar25 = lVar16 - (*(long *)(*(long *)(puVar7 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar8 = 0;
  FUN_1003bba50();
  lVar24 = *(long *)(lVar8 + -8);
  uVar15 = *(long *)(lVar24 + 0x40) + 0xfU & 0xfffffffffffffff0;
  uVar19 = lVar25 - uVar15;
  uVar20 = uVar19 - uVar15;
  lVar5 = uVar20 - uVar15;
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::stagedLyricCuePack);
  uVar9 = puVar1[2];
  *puVar1 = param_1;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  _swift_bridgeObjectRelease(uVar9);
  uVar9 = *(undefined8 *)
           (unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrievedMIDIEvents);
  *(long *)(unaff_x20 + _TtC8Playback31SongMenuMultiItemViewController::retrievedMIDIEvents) =
       param_4;
  _swift_bridgeObjectRetain(param_3);
  _swift_bridgeObjectRelease(uVar9);
  _swift_bridgeObjectRetain();
  FUN_1006bf1d4();
  lVar6 = _TtC8Playback31SongMenuMultiItemViewController::cachedTableViewSections;
  lVar22 = *(long *)(unaff_x20 +
                    _TtC8Playback31SongMenuMultiItemViewController::cachedTableViewSections);
  lVar13 = lVar22;
  if (lVar22 == 0) {
    FUN_1006bc4dc();
    uVar9 = *(undefined8 *)(unaff_x20 + lVar6);
    *(long *)(unaff_x20 + lVar6) = param_4;
    _swift_bridgeObjectRetain();
    _swift_bridgeObjectRelease(uVar9);
    lVar13 = param_4;
  }
  _swift_storeEnumTagMultiPayload(lVar5,lVar8,7);
  lVar6 = *(long *)(lVar13 + 0x10);
  if (lVar6 == 0) {
    _swift_bridgeObjectRetain(lVar22);
  }
  else {
    lVar21 = lVar13 + ((ulong)*(byte *)(lVar24 + 0x50) + 0x20 &
                      ((ulong)*(byte *)(lVar24 + 0x50) ^ 0xffffffffffffffff));
    lVar24 = *(long *)(lVar24 + 0x48);
    _swift_bridgeObjectRetain(lVar22);
    lVar22 = 0;
    do {
      lVar11 = lVar25 + *(int *)(puVar7 + 0x30);
      FUN_100023384(lVar21,lVar25,FUN_1003bba50);
      FUN_100023384(lVar5,lVar11,FUN_1003bba50);
      lVar10 = lVar25;
      _swift_getEnumCaseMultiPayload(lVar25,lVar8);
      iVar4 = (int)lVar10;
      if (4 < iVar4) {
        if (iVar4 < 8) {
          if (iVar4 == 5) {
            _swift_getEnumCaseMultiPayload(lVar11,lVar8);
            if ((int)lVar11 != 5) goto LAB_1006e628c;
          }
          else if (iVar4 == 6) {
            _swift_getEnumCaseMultiPayload(lVar11,lVar8);
            if ((int)lVar11 != 6) goto LAB_1006e628c;
          }
          else {
            _swift_getEnumCaseMultiPayload(lVar11,lVar8);
            if ((int)lVar11 != 7) goto LAB_1006e628c;
          }
        }
        else if (iVar4 == 8) {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 8) goto LAB_1006e628c;
        }
        else if (iVar4 == 9) {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 9) goto LAB_1006e628c;
        }
        else {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 10) goto LAB_1006e628c;
        }
LAB_1006e6340:
        FUN_1000233c8(lVar25,FUN_1003bba50);
        FUN_1000233c8(lVar5,FUN_1003bba50);
        _swift_bridgeObjectRelease(lVar13);
        lVar13 = lVar22;
        FUN_1006b6688();
        puVar2 = local_c0;
        if (lVar13 == 0) {
          return;
        }
        _swift_storeEnumTagMultiPayload(local_c0,local_c8,0x13);
        lVar5 = *(long *)(lVar13 + 0x10);
        if (lVar5 != 0) {
          lVar6 = 0;
          uVar14 = lVar13 + ((ulong)*(byte *)(local_d0 + 0x50) + 0x20 &
                            ((ulong)*(byte *)(local_d0 + 0x50) ^ 0xffffffffffffffff));
          lVar8 = *(long *)(local_d0 + 0x48);
          do {
            uVar15 = uVar14;
            FUN_1003c26e4(uVar14,puVar2);
            if ((uVar15 & 1) != 0) {
              FUN_1000233c8(puVar2,FUN_1003c2e8c);
              _swift_bridgeObjectRelease(lVar13);
              self = _objc_msgSend(unaff_x20,"tableView");
              if (self != 0) {
                puVar7 = &DAT_100af7188;
                FUN_100021774();
                lVar5 = 0;
                __s10Foundation9IndexPathVMa();
                uVar14 = (ulong)*(byte *)(*(long *)(lVar5 + -8) + 0x50);
                uVar15 = uVar14 + 0x20 & (uVar14 ^ 0xffffffffffffffff);
                _swift_allocObject(puVar7,uVar15 + *(long *)(*(long *)(lVar5 + -8) + 0x48),
                                   uVar14 | 7);
                *(undefined8 *)(puVar7 + 0x18) = 2;
                *(undefined8 *)(puVar7 + 0x10) = 1;
                __s10Foundation9IndexPathV5UIKitE3row7sectionACSi_SitcfC
                          (puVar7 + uVar15,lVar6,lVar22);
                puVar12 = puVar7;
                __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar7,lVar5);
                _swift_bridgeObjectRelease(puVar7);
                _objc_msgSend(self,"reloadRowsAtIndexPaths:withRowAnimation:",puVar12,100);
                return;
              }
                    /* WARNING: Does not return */
              pcVar3 = (code *)SoftwareBreakpoint(1,0x1006e64c8);
              (*pcVar3)();
            }
            lVar6 = lVar6 + 1;
            uVar14 = uVar14 + lVar8;
          } while (lVar5 != lVar6);
        }
        FUN_1000233c8(puVar2,FUN_1003c2e8c);
        goto LAB_1006e631c;
      }
      if (1 < iVar4) {
        if (iVar4 == 2) {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 2) goto LAB_1006e628c;
        }
        else if (iVar4 == 3) {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 3) goto LAB_1006e628c;
        }
        else {
          _swift_getEnumCaseMultiPayload(lVar11,lVar8);
          if ((int)lVar11 != 4) goto LAB_1006e628c;
        }
        goto LAB_1006e6340;
      }
      if (iVar4 == 0) {
        FUN_100023384(lVar25,uVar20,FUN_1003bba50);
        lVar10 = lVar11;
        _swift_getEnumCaseMultiPayload(lVar11,lVar8);
        uVar15 = uVar20;
        if ((int)lVar10 == 0) {
          FUN_100023340(lVar11,lVar16,FUN_1007accf4);
          FUN_1007b3720(uVar20,lVar16);
          FUN_1000233c8(lVar16,FUN_1007accf4);
          FUN_1000233c8(uVar20,FUN_1007accf4);
joined_r0x0001006e6224:
          if ((uVar15 & 1) != 0) goto LAB_1006e6340;
          FUN_1000233c8(lVar25,FUN_1003bba50);
        }
        else {
LAB_1006e6278:
          FUN_1000233c8(uVar15,FUN_1007accf4);
LAB_1006e628c:
          FUN_100023be4(lVar25,&DAT_100b01360);
        }
      }
      else {
        FUN_100023384(lVar25,uVar19,FUN_1003bba50);
        puVar12 = &DAT_100af82b8;
        FUN_100021774();
        lVar23 = (long)*(int *)(puVar12 + 0x30);
        lVar10 = lVar11;
        _swift_getEnumCaseMultiPayload(lVar11,lVar8);
        if ((int)lVar10 != 1) {
          FUN_1000233c8(uVar19 + lVar23,FUN_1007ac0bc);
          uVar15 = uVar19;
          goto LAB_1006e6278;
        }
        local_d8 = lVar5;
        FUN_100023340(lVar11,lVar18,FUN_1007accf4);
        FUN_100023340(uVar19 + lVar23,uVar14,FUN_1007ac0bc);
        FUN_100023340(lVar11 + lVar23,lVar17,FUN_1007ac0bc);
        uVar15 = uVar19;
        FUN_1007b3720(uVar19,lVar18);
        FUN_1000233c8(uVar19,FUN_1007accf4);
        if ((uVar15 & 1) != 0) {
          uVar15 = uVar14;
          FUN_1007b3088(uVar14,lVar17);
          FUN_1000233c8(lVar17,FUN_1007ac0bc);
          FUN_1000233c8(uVar14,FUN_1007ac0bc);
          FUN_1000233c8(lVar18,FUN_1007accf4);
          lVar5 = local_d8;
          goto joined_r0x0001006e6224;
        }
        FUN_1000233c8(lVar17,FUN_1007ac0bc);
        FUN_1000233c8(uVar14,FUN_1007ac0bc);
        FUN_1000233c8(lVar18,FUN_1007accf4);
        FUN_1000233c8(lVar25,FUN_1003bba50);
        lVar5 = local_d8;
      }
      lVar22 = lVar22 + 1;
      lVar21 = lVar21 + lVar24;
    } while (lVar6 != lVar22);
  }
  FUN_1000233c8(lVar5,FUN_1003bba50);
LAB_1006e631c:
  _swift_bridgeObjectRelease(lVar13);
  return;
}

// ==== 1006f617c _TtC8Playback33MIDICueItemBusTableViewController::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback33MIDICueItemBusTableViewController::initWithCoder_
             (ID param_1,SEL param_2,ID param_3)

{
  code *pcVar1;
  
  FUN_1004303d8();
  if ((undefined *)param_3 == (undefined *)0x0) {
    param_3 = (ID)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
  }
  *(ID *)(param_1 + midiBuses) = param_3;
  *(undefined8 *)(param_1 + selectedMIDIBus) = 0;
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd000000000000025,0x80000001008d1460,
             "Playback/MIDICueItemBusTableViewController.swift",0x30,2,0x14,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1006f6218);
  (*pcVar1)();
}

// ==== 1006f6468 FUN_1006f6468 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1006f6468(ID param_1)

{
  code *pcVar1;
  ID IVar2;
  undefined8 uVar3;
  ID self;
  undefined *puVar4;
  ID IVar5;
  ID IVar6;
  ID IVar7;
  char *pcVar8;
  char *pcVar9;
  undefined **ppuVar10;
  ulong uVar11;
  long unaff_x20;
  
  uVar11 = *(ulong *)(unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::midiBuses);
  IVar2 = param_1;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((uVar11 & 0xc000000000000001) == 0) {
    if ((long)IVar2 < 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x1006f6704);
      (*pcVar1)();
    }
    if (*(ulong *)((uVar11 & 0xfffffffffffff8) + 0x10) <= IVar2) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x1006f6708);
      (*pcVar1)();
    }
    IVar2 = *(ID *)(uVar11 + IVar2 * 8 + 0x20);
  }
  else {
    FUN_1000cc6c0();
  }
  uVar3 = 0xd00000000000001d;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
  self = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:",uVar3);
  if (self == 0) {
    puVar4 = &_OBJC_CLASS___UITableViewCell;
    _objc_allocWithZone();
    uVar3 = 0xd00000000000001d;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001d,0x80000001008d7170);
    self = _objc_msgSend((ID)puVar4,"initWithStyle:reuseIdentifier:",1,uVar3);
  }
  IVar5 = _objc_msgSend(self,"textLabel");
  if (IVar5 != 0) {
    pcVar8 = "title";
    IVar6 = _objc_msgSend(IVar2,"title");
    if (IVar6 == 0) {
      IVar6 = 0;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      puVar4 = &_OBJC_CLASS___NSBundle;
      _swift_getInitializedObjCClass();
      IVar7 = _objc_msgSend((ID)puVar4,"mainBundle");
      pcVar9 = pcVar8;
      __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
                (IVar6,pcVar8,0,0,IVar7,0,0xe000000000000000,0,0xe000000000000000);
      _swift_bridgeObjectRelease(pcVar8);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar6,pcVar9);
      _swift_bridgeObjectRelease(pcVar9);
    }
    _objc_msgSend(IVar5,"setText:",IVar6);
  }
  IVar5 = *(ID *)(unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::selectedMIDIBus);
  if (IVar5 == 0) {
    IVar5 = *(ID *)(unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::midiEvent);
    if (IVar5 == 0) {
      return self;
    }
    ppuVar10 = &PTR_s_busID_100aa0a20;
  }
  else {
    ppuVar10 = &PTR_s_id_100aa09d8;
  }
  IVar5 = _objc_msgSend(IVar5,*ppuVar10);
  IVar2 = _objc_msgSend(IVar2,"id");
  uVar3 = 3;
  if ((int)IVar2 != (int)IVar5) {
    uVar3 = 0;
  }
  _objc_msgSend(self,"setAccessoryType:",uVar3);
  return self;
}

// ==== 1006f67c0 FUN_1006f67c0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1006f67c0(ID param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  undefined *puVar5;
  void *aBlock;
  undefined8 *puVar6;
  undefined8 *puVar7;
  ulong uVar8;
  ulong uVar9;
  long unaff_x20;
  long lVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  code *pcVar15;
  ulong local_c0;
  long local_b8;
  ID local_b0;
  long local_a8;
  long lStack_a0;
  long local_98;
  undefined *local_90;
  undefined8 local_88;
  code *local_80;
  undefined *puStack_78;
  code *local_70;
  undefined *local_68;
  
  lVar1 = 0;
  local_b0 = param_1;
  __s8Dispatch0A13WorkItemFlagsVMa();
  local_98 = *(long *)(lVar1 + -8);
  lVar10 = (long)&local_c0 - (*(long *)(local_98 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  __s8Dispatch0A3QoSVMa();
  local_a8 = *(long *)(lVar2 + -8);
  lVar12 = lVar10 - (*(long *)(local_a8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  lStack_a0 = lVar2;
  __s8Dispatch0A4TimeVMa();
  lVar14 = *(long *)(lVar3 + -8);
  uVar8 = *(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar13 = lVar12 - uVar8;
  lVar2 = lVar13 - uVar8;
  uVar11 = *(ulong *)(unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::midiBuses);
  uVar8 = uVar11;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (uVar11 >> 0x3e == 0) {
    uVar9 = *(ulong *)((uVar11 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar9 = uVar11 & 0xffffffffffffff8;
    if ((long)uVar11 < 0) {
      uVar9 = uVar11;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if ((long)uVar9 < 0) {
                    /* WARNING: Does not return */
      pcVar15 = (code *)SoftwareBreakpoint(1,0x1006f6b0c);
      (*pcVar15)();
    }
  }
  if ((-1 < (long)uVar8) && (uVar8 < uVar9)) {
    local_b8 = lVar3;
    if ((uVar11 & 0xc000000000000001) == 0) {
      if (*(ulong *)((uVar11 & 0xfffffffffffff8) + 0x10) <= uVar8) {
                    /* WARNING: Does not return */
        pcVar15 = (code *)SoftwareBreakpoint(1,0x1006f6b1c);
        (*pcVar15)();
      }
      uVar8 = *(ulong *)(uVar11 + uVar8 * 8 + 0x20);
    }
    else {
      FUN_1000cc6c0();
    }
    _swift_bridgeObjectRelease(uVar11);
    *(ulong *)(unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::selectedMIDIBus) =
         uVar8;
    local_c0 = uVar8;
    _objc_msgSend(local_b0,"reloadData");
    lVar3 = unaff_x20 + _TtC8Playback33MIDICueItemBusTableViewController::delegate;
    _swift_unknownObjectUnownedLoadStrong(lVar3);
    FUN_1003af760(uVar8);
    _swift_unknownObjectRelease(lVar3);
    uVar4 = 0;
    FUN_10004cb08();
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    local_b0 = uVar4;
    __s8Dispatch0A4TimeV3nowACyFZ(lVar13);
    __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar2,0x3fd0000000000000,lVar13);
    lVar3 = local_b8;
    pcVar15 = *(code **)(lVar14 + 8);
    (*pcVar15)(lVar13,local_b8);
    puVar5 = &DAT_100a5cf90;
    _swift_allocObject(&DAT_100a5cf90,0x18,7);
    *(long *)(puVar5 + 0x10) = unaff_x20;
    local_70 = FUN_10052a394;
    local_90 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_88 = 0x42000000;
    local_80 = FUN_10056b3d8;
    puStack_78 = &DAT_100a5cfa8;
    local_68 = puVar5;
    aBlock = __Block_copy(&local_90);
    _swift_release(local_68);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar12);
    puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_90 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar6 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar5);
    puVar5 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar7 = &DAT_100af52b8;
    FUN_100023140(&DAT_100af52b8,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (lVar10,&local_90,puVar5,puVar7,lVar1,puVar6);
    __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (lVar2,lVar12,lVar10,aBlock);
    __Block_release(aBlock);
    (**(code **)(local_98 + 8))(lVar10,lVar1);
    (**(code **)(local_a8 + 8))(lVar12,lStack_a0);
    (*pcVar15)(lVar2,lVar3);
    return;
  }
  _swift_bridgeObjectRelease(uVar11);
  return;
}

// ==== 10074a36c FUN_10074a36c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_10074a36c(ID param_1)

{
  code *pcVar1;
  ID IVar2;
  ID IVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  long unaff_x20;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong local_88 [3];
  undefined *local_70;
  undefined1 auStack_68 [24];
  
  IVar2 = param_1;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((long)IVar2 < 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x10074a764);
    (*pcVar1)();
  }
  if (*(ulong *)(*(long *)(unaff_x20 + _TtC8Playback31MIDISettingsTableViewController::options) +
                0x10) <= IVar2) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x10074a768);
    (*pcVar1)();
  }
  uVar7 = *(ulong *)(*(long *)(unaff_x20 + _TtC8Playback31MIDISettingsTableViewController::options)
                     + IVar2 * 8 + 0x20);
  local_88[0] = uVar7;
  if (1 < uVar7) {
    FUN_1001fea8c(uVar7);
    uVar5 = 0xd000000000000023;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000023,0x80000001008ef030);
    uVar4 = uVar5;
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    IVar3 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar5,uVar4);
    uVar4 = 0;
    FUN_1002adb94(0);
    IVar2 = IVar3;
    _swift_dynamicCastClass(IVar3,uVar4);
    if (IVar2 != 0) {
      local_70 = &DAT_100a621e8;
      FUN_1001fea8c(uVar7);
      FUN_1002acbdc(uVar7,local_88);
      FUN_1001fea0c(uVar7);
      FUN_1001fea0c(uVar7);
      FUN_10003d930(local_88);
      *(undefined ***)(IVar2 + _TtC8Playback35RoutingSelectorMIDIBusTableViewCell::delegate + 8) =
           &PTR_PTR_100a62230;
      _swift_unknownObjectWeakAssign();
      return IVar3;
    }
    FUN_1001fea0c(uVar7);
LAB_10074a614:
    FUN_1001fea0c(uVar7);
    return IVar3;
  }
  uVar4 = 0xd000000000000029;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000029,0x80000001008ef060);
  uVar5 = uVar4;
  __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
  IVar3 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar4,uVar5);
  uVar4 = 0;
  FUN_1002ae288(0);
  IVar2 = IVar3;
  _swift_dynamicCastClass(IVar3,uVar4);
  if (IVar2 == 0) goto LAB_10074a614;
  if (uVar7 == 0) {
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar9 = DAT_100b75f50;
    _swift_beginAccess(DAT_100b75f50 + 0x18,auStack_68,0,0);
    uVar9 = *(ulong *)(uVar9 + 0x18);
    if (uVar9 >> 0x3e == 0) {
      _swift_bridgeObjectRetain_n(uVar9,2);
      __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      uVar6 = uVar9;
    }
    else {
      uVar6 = uVar9 & 0xffffffffffffff8;
      if ((long)uVar9 < 0) {
        uVar6 = uVar9;
      }
      uVar4 = 0;
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      _swift_bridgeObjectRetain(uVar9);
      __ss17_bridgeCocoaArrayySayxGyXllF(uVar6,uVar4);
    }
    _swift_bridgeObjectRelease(uVar9);
    uVar9 = DAT_100b75f50;
    uVar8 = DAT_100b75f50;
    _swift_retain();
    FUN_10037acf0();
    _swift_release(uVar9);
    uVar9 = uVar8;
    if (uVar8 >> 0x3e != 0) {
      uVar9 = uVar8 & 0xffffffffffffff8;
      if ((long)uVar8 < 0) {
        uVar9 = uVar8;
      }
      uVar4 = 0;
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      _swift_bridgeObjectRetain(uVar8);
      __ss17_bridgeCocoaArrayySayxGyXllF(uVar9,uVar4);
      _swift_bridgeObjectRelease(uVar8);
      goto LAB_10074a6d4;
    }
  }
  else {
    if (DAT_100adefa0 != -1) {
      _swift_once(&DAT_100adefa0,FUN_10037c47c);
    }
    uVar9 = DAT_100b75f50;
    _swift_beginAccess(DAT_100b75f50 + 0x10,auStack_68,0,0);
    uVar8 = *(ulong *)(uVar9 + 0x10);
    if (uVar8 >> 0x3e == 0) {
      _swift_bridgeObjectRetain_n(uVar8,2);
      __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      uVar6 = uVar8;
    }
    else {
      uVar6 = uVar8 & 0xffffffffffffff8;
      if ((long)uVar8 < 0) {
        uVar6 = uVar8;
      }
      uVar4 = 0;
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      _swift_bridgeObjectRetain(uVar8);
      __ss17_bridgeCocoaArrayySayxGyXllF(uVar6,uVar4);
    }
    _swift_bridgeObjectRelease();
    FUN_100383e28();
    uVar9 = uVar8;
    if (uVar8 >> 0x3e != 0) {
      uVar9 = uVar8 & 0xffffffffffffff8;
      if ((long)uVar8 < 0) {
        uVar9 = uVar8;
      }
      uVar4 = 0;
      FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
      __ss17_bridgeCocoaArrayySayxGyXllF(uVar9,uVar4);
      goto LAB_10074a6d4;
    }
  }
  _swift_bridgeObjectRetain(uVar9);
  __ss28__ContiguousArrayStorageBaseC17staticElementTypeypXpvgTj();
  FUN_100023404(0,&DAT_100af78b0,&PTR__OBJC_CLASS___MIKMIDIEndpoint_100aa3fe8);
  uVar8 = uVar9;
LAB_10074a6d4:
  _swift_bridgeObjectRelease(uVar8);
  local_70 = &DAT_100a621e8;
  FUN_1001fea8c(uVar7);
  FUN_10074b4d0(uVar7,uVar6,uVar9,local_88);
  _swift_bridgeObjectRelease(uVar6);
  _swift_bridgeObjectRelease(uVar9);
  FUN_1001fea0c(uVar7);
  FUN_10003d930(local_88);
  return IVar3;
}

// ==== 10079f5dc FUN_10079f5dc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined * FUN_10079f5dc(void)

{
  ulong uVar1;
  undefined *puVar2;
  code *pcVar3;
  ID self;
  undefined *puVar4;
  undefined *puVar5;
  long unaff_x20;
  undefined *puVar6;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined1 local_58;
  
  self = _objc_msgSend(*(ID *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::song),
                       "midiEventsDefaultArrangement");
  if (self != 0) {
    puVar4 = (undefined *)_objc_msgSend(self,"array");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (puVar4,PTR___sypN_100a1e038 + 8);
    puVar5 = puVar4;
    FUN_1002d7d78();
    _swift_bridgeObjectRelease(puVar4);
    if (puVar5 != (undefined *)0x0) goto LAB_10079f688;
  }
  puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_10079f688:
  if ((ulong)puVar5 >> 0x3e == 0) {
    puVar4 = *(undefined **)(((ulong)puVar5 & 0xfffffffffffff8) + 0x10);
    puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    puVar4 = (undefined *)((ulong)puVar5 & 0xffffffffffffff8);
    if ((long)puVar5 < 0) {
      puVar4 = puVar5;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar2;
  if (puVar4 == (undefined *)0x0) {
    _swift_retain(puVar2);
  }
  else {
    _swift_retain();
    FUN_1001cda88(0,(ulong)puVar4 & ((long)puVar4 >> 0x3f ^ 0xffffffffffffffffU),0);
    if ((long)puVar4 < 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x10079f7d0);
      (*pcVar3)();
    }
    puVar6 = (undefined *)0x0;
    do {
      if (((ulong)puVar5 & 0xc000000000000001) != 0) {
        FUN_1000cc6e4(puVar6,puVar5);
      }
      FUN_100712e68(&local_98);
      uVar1 = *(ulong *)(puVar2 + 0x10);
      if (*(ulong *)(puVar2 + 0x18) >> 1 <= uVar1) {
        FUN_1001cda88(1 < *(ulong *)(puVar2 + 0x18),uVar1 + 1,1);
      }
      puVar6 = puVar6 + 1;
      *(ulong *)(puVar2 + 0x10) = uVar1 + 1;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x28) = uStack_90;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x20) = local_98;
      puVar2[uVar1 * 0x48 + 0x60] = local_58;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x48) = uStack_70;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x40) = local_78;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x58) = uStack_60;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x50) = local_68;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x38) = uStack_80;
      *(undefined8 *)(puVar2 + uVar1 * 0x48 + 0x30) = local_88;
    } while (puVar4 != puVar6);
  }
  _swift_bridgeObjectRelease(puVar5);
  return puVar2;
}

// ==== 10079f7d0 _TtC8Playback34SongMenuMIDIBankEditViewController::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback34SongMenuMIDIBankEditViewController::initWithCoder_
             (ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  code *pcVar2;
  
  lVar1 = param_1 + delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd000000000000025,0x80000001008d1460,
             "Playback/SongMenuMIDIBankEditViewController.swift",0x31,2,0x44,0);
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(1,0x10079f85c);
  (*pcVar2)();
}

// ==== 10079f85c FUN_10079f85c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_10079f85c(void)

{
  int iVar1;
  ID IVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ID IVar5;
  undefined8 uVar6;
  long lVar7;
  ID unaff_x20;
  long lVar8;
  long lVar9;
  long lVar10;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long local_68;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa0,"viewDidLoad");
  lVar7 = *(long *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::mode + 0x10);
  if (lVar7 == 0) {
    lVar7 = DAT_100b76b88;
    uVar3 = DAT_100b76b80;
    if (DAT_100adf650 != -1) {
      _swift_once(&DAT_100adf650,FUN_10052e688);
      lVar7 = DAT_100b76b88;
      uVar3 = DAT_100b76b80;
    }
  }
  else {
    uVar3 = *(undefined8 *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::mode + 8)
    ;
  }
  _swift_bridgeObjectRetain(lVar7);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar3,lVar7);
  _swift_bridgeObjectRelease(lVar7);
  _objc_msgSend(unaff_x20,"setTitle:",uVar3);
  iVar1 = 2;
  FUN_1008c26ac(2,0xe,0,0);
  IVar2 = _objc_msgSend(unaff_x20,"navigationItem");
  if (iVar1 == 0) {
    uStack_78 = 0;
    local_80 = 0;
    local_68 = 0;
    uStack_70 = 0;
    uVar3 = 0;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0,0xe000000000000000);
    lVar7 = local_68;
    if (local_68 == 0) {
      lVar8 = 0;
    }
    else {
      puVar4 = &local_80;
      FUN_100023444(puVar4,local_68);
      lVar10 = *(long *)(lVar7 + -8);
      lVar9 = (long)&local_80 - (*(long *)(lVar10 + 0x40) + 0xfU & 0xfffffffffffffff0);
      (**(code **)(lVar10 + 0x10))(lVar9,puVar4,lVar7);
      lVar8 = lVar9;
      __ss27_bridgeAnythingToObjectiveCyyXlxlF(lVar9,lVar7);
      (**(code **)(lVar10 + 8))(lVar9,lVar7);
      FUN_100023468(&local_80);
    }
    IVar5 = 0;
    FUN_1007711fc();
    _swift_getObjCClassFromMetadata();
    _objc_allocWithZone();
    IVar5 = _objc_msgSend(IVar5,"initWithTitle:style:target:action:",uVar3,0,lVar8,0);
    _swift_unknownObjectRelease(lVar8);
    _objc_msgSend(IVar2,"setBackBarButtonItem:",IVar5);
  }
  else {
    _objc_msgSend(IVar2,"setBackButtonDisplayMode:",2);
  }
  FUN_10079fbd8(0);
  IVar2 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar2 != 0) {
    if (DAT_100adfa80 != -1) {
      _swift_once(&DAT_100adfa80,FUN_1005477e4);
    }
    uVar3 = DAT_100b773c0;
    uVar6 = 0xd00000000000001b;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001b,0x80000001008e2d20);
    _objc_msgSend(IVar2,"registerNib:forCellReuseIdentifier:",uVar3,uVar6);
  }
  IVar2 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar2 != 0) {
    if (DAT_100adfc88 != -1) {
      _swift_once(&DAT_100adfc88,FUN_1006f9b98);
    }
    uVar6 = DAT_100b77808;
    uVar3 = 0xd000000000000020;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000020,0x80000001008f0c40);
    _objc_msgSend(IVar2,"registerNib:forCellReuseIdentifier:",uVar6,uVar3);
  }
  return 0;
}

// ==== 10079fbd8 FUN_10079fbd8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_10079fbd8(void)

{
  ID self;
  undefined8 uVar1;
  ID IVar2;
  ID unaff_x20;
  long lVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  undefined1 *puVar6;
  
  IVar2 = unaff_x20;
  _swift_getObjectType();
  lVar3 = *(long *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::mode + 0x10);
  self = _objc_msgSend(unaff_x20,"navigationItem");
  if (lVar3 == 0) {
    if (DAT_100adf330 != -1) {
      _swift_once(&DAT_100adf330,FUN_10052ced4);
    }
    uVar5 = DAT_100b76548;
    uVar1 = DAT_100b76540;
    _swift_bridgeObjectRetain(DAT_100b76548);
  }
  else {
    if (DAT_100adfa18 != -1) {
      _swift_once(&DAT_100adfa18,FUN_100530890);
    }
    uVar5 = DAT_100b77318;
    uVar1 = DAT_100b77310;
    _swift_bridgeObjectRetain(DAT_100b77318);
  }
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar1,uVar5);
  _swift_bridgeObjectRelease(uVar5);
  if (IVar2 == 0) {
    puVar4 = (undefined1 *)0x0;
  }
  else {
    puVar4 = &stack0xffffffffffffff90;
    FUN_100023444(puVar4,IVar2);
    lVar3 = *(long *)(IVar2 - 8);
    puVar6 = &stack0xffffffffffffff90 + -(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
    (**(code **)(lVar3 + 0x10))(puVar6,puVar4,IVar2);
    puVar4 = puVar6;
    __ss27_bridgeAnythingToObjectiveCyyXlxlF(puVar6,IVar2);
    (**(code **)(lVar3 + 8))(puVar6,IVar2);
    FUN_100023468(&stack0xffffffffffffff90);
  }
  IVar2 = 0;
  FUN_1007711fc();
  _swift_getObjCClassFromMetadata();
  _objc_allocWithZone();
  IVar2 = _objc_msgSend(IVar2,"initWithTitle:style:target:action:",uVar1,2,puVar4,
                        "addEditBarButtonTapped:");
  _swift_unknownObjectRelease(puVar4);
  _objc_msgSend(self,"setRightBarButtonItem:",IVar2);
  return 0;
}

// ==== 10079fde8 _TtC8Playback34SongMenuMIDIBankEditViewController::viewDidLoad ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback34SongMenuMIDIBankEditViewController::viewDidLoad(ID param_1,SEL param_2)

{
  FUN_10079f85c(param_1);
  return;
}

// ==== 10079fe10 FUN_10079fe10 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10079fe10(undefined8 param_1,long param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined8 *puVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  undefined8 auStack_120 [9];
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  lVar1 = 0;
  FUN_100716708();
  lVar4 = (long)auStack_120 - (*(long *)(*(long *)(lVar1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar2 = &DAT_100af64b8;
  FUN_100021774();
  puVar6 = (undefined8 *)
           (lVar4 - (*(long *)(*(long *)(puVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0));
  _swift_beginAccess(param_2 + 0x10,auStack_120,0,0);
  param_2 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (param_2 != 0) {
    FUN_10079fbd8();
    FUN_10003b4b4(param_1,puVar6,&DAT_100af64b8);
    puVar3 = puVar6;
    _swift_getEnumCaseMultiPayload(puVar6,puVar2);
    if ((int)puVar3 == 1) {
      uVar5 = *puVar6;
      FUN_1007a0028(uVar5);
      _swift_errorRelease(uVar5);
    }
    else {
      FUN_100023340(puVar6,lVar4,FUN_100716708);
      puVar6 = (undefined8 *)(lVar4 + *(int *)(lVar1 + 0x28));
      uStack_68 = puVar6[3];
      local_70 = puVar6[2];
      uStack_58 = puVar6[5];
      uStack_60 = puVar6[4];
      uStack_98 = uStack_68;
      local_a0 = local_70;
      uStack_88 = uStack_58;
      uStack_90 = uStack_60;
      uStack_a8 = puVar6[1];
      local_b0 = *puVar6;
      local_78 = uStack_a8;
      FUN_10029f6a0(&local_78);
      FUN_100088c38(&local_70);
      FUN_100088c38(&uStack_60);
      FUN_100714dbc(auStack_120 + 3,&local_b0);
      lVar1 = param_2 + _TtC8Playback34SongMenuMIDIBankEditViewController::delegate;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar1 == 0) {
        uStack_b8 = auStack_120[5];
        local_c0 = auStack_120[4];
        FUN_1000a26a4(&local_c0);
        uStack_c8 = auStack_120[7];
        local_d0 = auStack_120[6];
        FUN_1000a26a4(&local_d0);
        local_d8 = auStack_120[8];
        FUN_1001d7e54(&local_d8);
      }
      else {
        FUN_10029ed94(param_2,auStack_120 + 3);
        uStack_b8 = auStack_120[5];
        local_c0 = auStack_120[4];
        FUN_1000a26a4(&local_c0);
        uStack_c8 = auStack_120[7];
        local_d0 = auStack_120[6];
        FUN_1000a26a4(&local_d0);
        local_d8 = auStack_120[8];
        FUN_1001d7e54(&local_d8);
        _swift_unknownObjectRelease(lVar1);
      }
      FUN_1000233c8(lVar4,FUN_100716708);
    }
  }
  return;
}

// ==== 1007a0028 FUN_1007a0028 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_1007a0028(undefined8 param_1)

{
  long lVar1;
  undefined *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  void *aBlock;
  char *pcVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ID unaff_x20;
  ID IVar14;
  undefined *local_158;
  char *local_150;
  code *local_148;
  undefined *puStack_140;
  code *local_138;
  undefined *local_130;
  undefined1 local_120 [8];
  undefined8 uStack_118;
  undefined8 local_110;
  undefined1 auStack_108 [168];
  
  puVar5 = &DAT_100af5338;
  FUN_100021774();
  _swift_initStackObject();
  *(undefined8 *)(puVar5 + 0x20) = 0x444972657375;
  *(undefined8 *)(puVar5 + 0x18) = 8;
  *(undefined8 *)(puVar5 + 0x10) = 4;
  *(undefined8 *)(puVar5 + 0x28) = 0xe600000000000000;
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar1 = DAT_100b757a8;
  FUN_10016f2bc();
  if (lVar1 == 0) {
    local_158 = (undefined *)0xffffffffffffffff;
  }
  else {
    local_158 = *(undefined **)(lVar1 + _TtC8Playback7APIUser::userID);
  }
  puVar2 = PTR___sSiN_100a1dd88;
  puVar4 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
  __ss23CustomStringConvertibleP11descriptionSSvgTj();
  *(undefined **)(puVar5 + 0x30) = puVar2;
  *(undefined **)(puVar5 + 0x38) = puVar4;
  *(undefined8 *)(puVar5 + 0x40) = 0x676e6f73;
  *(undefined8 *)(puVar5 + 0x48) = 0xe400000000000000;
  IVar14 = *(ID *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::song);
  pcVar10 = "title";
  puVar2 = (undefined *)_objc_msgSend(IVar14,"title");
  if (puVar2 == (undefined *)0x0) {
    puVar2 = (undefined *)0x3e6c696e3c;
    pcVar10 = &DAT_e500000000000000;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  local_158 = puVar2;
  local_150 = pcVar10;
  _swift_bridgeObjectRetain(pcVar10);
  __sSS6appendyySSF(0x2f,0xe100000000000000);
  _swift_bridgeObjectRelease(pcVar10);
  pcVar10 = local_150;
  puVar4 = local_158;
  local_158 = (undefined *)_objc_msgSend(IVar14,"contentID");
  puVar2 = &DAT_100b0c6f0;
  FUN_100021774(&DAT_100b0c6f0);
  ppuVar3 = &local_158;
  __sSS10describingSSx_tclufC(ppuVar3,puVar2);
  local_158 = puVar4;
  local_150 = pcVar10;
  _swift_bridgeObjectRetain(pcVar10);
  __sSS6appendyySSF(ppuVar3,puVar2);
  _swift_bridgeObjectRelease(pcVar10);
  _swift_bridgeObjectRelease(puVar2);
  *(undefined **)(puVar5 + 0x50) = local_158;
  *(char **)(puVar5 + 0x58) = local_150;
  *(undefined8 *)(puVar5 + 0x60) = 0x497972617262696c;
  *(undefined1 **)(puVar5 + 0x68) = &DAT_e900000000000044;
  local_158 = *(undefined **)
               (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID);
  puVar2 = PTR___sSiN_100a1dd88;
  puVar4 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
  __ss23CustomStringConvertibleP11descriptionSSvgTj();
  *(undefined **)(puVar5 + 0x70) = puVar2;
  *(undefined **)(puVar5 + 0x78) = puVar4;
  *(undefined8 *)(puVar5 + 0x80) = 0x726f727265;
  *(undefined1 **)(puVar5 + 0x88) = &DAT_e500000000000000;
  _swift_getErrorValue(param_1,auStack_108,local_120);
  FUN_1002c2c2c();
  *(undefined8 *)(puVar5 + 0x90) = uStack_118;
  *(undefined8 *)(puVar5 + 0x98) = local_110;
  puVar4 = puVar5;
  FUN_10079bfc8();
  _swift_setDeallocating(puVar5);
  puVar2 = &DAT_100af5340;
  FUN_100021774(&DAT_100af5340);
  _swift_arrayDestroy(puVar5 + 0x20,4,puVar2);
  puVar5 = &_OBJC_CLASS___NSBundle;
  _swift_getInitializedObjCClass();
  IVar14 = _objc_msgSend((ID)puVar5,"mainBundle");
  uVar11 = 0x800000010090c260;
  uVar6 = 0xd000000000000017;
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (0xd000000000000017,0x800000010090c260,0,0,IVar14,0,0xe000000000000000,0,
             0xe000000000000000);
  IVar14 = _objc_msgSend((ID)puVar5,"mainBundle");
  uVar7 = 0xd000000000000051;
  uVar12 = 0x800000010090c280;
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (0xd000000000000051,0x800000010090c280,0,0,IVar14,0,0xe000000000000000,0,
             0xe000000000000000);
  puVar2 = puVar4;
  FUN_10079f184();
  puVar5 = &DAT_100af52f8;
  local_158 = puVar2;
  FUN_100021774(&DAT_100af52f8);
  puVar8 = &DAT_100af5300;
  FUN_1000f634c(&DAT_100af5300,&DAT_100af5308,PTR___sSSN_100a1dce0,PTR___sSayxGSKsMc_100a1dd28);
  uVar9 = 0x20;
  uVar13 = 0xe100000000000000;
  __sSKsSS7ElementRtzrlE6joined9separatorS2S_tF(0x20,0xe100000000000000,puVar5,puVar8);
  _swift_bridgeObjectRelease(puVar4);
  _swift_bridgeObjectRelease(puVar2);
  puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain_n(PTR___swiftEmptyArrayStorage_100a1e050,2);
  FUN_100831694(uVar6,uVar11,uVar7,uVar12,uVar9,uVar13,0,0,puVar5,puVar5,0);
  _swift_bridgeObjectRelease(uVar13);
  _swift_release_n(puVar5,2);
  _swift_bridgeObjectRelease(uVar12);
  _swift_bridgeObjectRelease(uVar11);
  IVar14 = _objc_msgSend(unaff_x20,"navigationController");
  if (IVar14 != 0) {
    puVar5 = &DAT_100a65710;
    _swift_allocObject(&DAT_100a65710,0x18,7);
    *(ID *)(puVar5 + 0x10) = unaff_x20;
    local_138 = thunk_FUN_1006369b4;
    local_158 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_150 = (char *)0x42000000;
    local_148 = FUN_10056b3d8;
    puStack_140 = &DAT_100a65728;
    local_130 = puVar5;
    aBlock = __Block_copy(&local_158);
    _swift_release(local_130);
    _objc_msgSend(IVar14,"presentViewController:animated:completion:",uVar6,1,aBlock);
    __Block_release(aBlock);
  }
  return 0;
}

// ==== 1007a056c FUN_1007a056c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007a056c(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 *puVar7;
  int aiStack_d0 [2];
  undefined8 local_c8;
  undefined1 auStack_c0 [24];
  undefined1 auStack_a8 [24];
  long local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined *puStack_68;
  
  lVar1 = 0;
  local_c8 = param_6;
  FUN_100715b34();
  lVar6 = (long)aiStack_d0 - (*(long *)(*(long *)(lVar1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar2 = &DAT_100af64f8;
  FUN_100021774();
  puVar7 = (undefined8 *)
           (lVar6 - (*(long *)(*(long *)(puVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0));
  _swift_beginAccess(param_2 + 0x10,auStack_a8,0,0);
  lVar3 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    FUN_10079fbd8();
  }
  FUN_10003b4b4(param_1,puVar7,&DAT_100af64f8);
  puVar4 = puVar7;
  _swift_getEnumCaseMultiPayload(puVar7,puVar2);
  if ((int)puVar4 == 1) {
    uVar5 = *puVar7;
    _swift_beginAccess(param_2 + 0x10,&local_90,0,0);
    param_2 = param_2 + 0x10;
    _swift_unknownObjectWeakLoadStrong();
    if (param_2 == 0) {
      _swift_errorRelease(uVar5);
    }
    else {
      FUN_1007a07a0(uVar5);
      _swift_errorRelease(uVar5);
    }
  }
  else {
    FUN_100023340(puVar7,lVar6,FUN_100715b34);
    _swift_beginAccess(param_2 + 0x10,auStack_c0,0,0);
    param_2 = param_2 + 0x10;
    _swift_unknownObjectWeakLoadStrong();
    uVar5 = local_c8;
    if (param_2 != 0) {
      local_90 = (long)*(int *)(lVar6 + *(int *)(lVar1 + 0x28));
      local_70 = local_c8;
      puStack_68 = PTR___swiftEmptyArrayStorage_100a1e050;
      lVar3 = param_2 + _TtC8Playback34SongMenuMIDIBankEditViewController::delegate;
      uStack_88 = param_3;
      local_80 = param_4;
      uStack_78 = param_5;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar3 != 0) {
        _swift_bridgeObjectRetain(param_4);
        _swift_bridgeObjectRetain(uVar5);
        puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        FUN_10029f0f4(param_2,&local_90);
        _swift_unknownObjectRelease(lVar3);
        _swift_release(puVar2);
        _swift_bridgeObjectRelease(uVar5);
        _swift_bridgeObjectRelease(param_4);
      }
    }
    FUN_1000233c8(lVar6,FUN_100715b34);
  }
  return;
}

// ==== 1007a07a0 FUN_1007a07a0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_1007a07a0(undefined8 param_1)

{
  long lVar1;
  undefined *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  void *aBlock;
  char *pcVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ID unaff_x20;
  ID IVar14;
  undefined *local_158;
  char *local_150;
  code *local_148;
  undefined *puStack_140;
  code *local_138;
  undefined *local_130;
  undefined1 local_120 [8];
  undefined8 uStack_118;
  undefined8 local_110;
  undefined1 auStack_108 [168];
  
  puVar5 = &DAT_100af5338;
  FUN_100021774();
  _swift_initStackObject();
  *(undefined8 *)(puVar5 + 0x20) = 0x444972657375;
  *(undefined8 *)(puVar5 + 0x18) = 8;
  *(undefined8 *)(puVar5 + 0x10) = 4;
  *(undefined8 *)(puVar5 + 0x28) = 0xe600000000000000;
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar1 = DAT_100b757a8;
  FUN_10016f2bc();
  if (lVar1 == 0) {
    local_158 = (undefined *)0xffffffffffffffff;
  }
  else {
    local_158 = *(undefined **)(lVar1 + _TtC8Playback7APIUser::userID);
  }
  puVar2 = PTR___sSiN_100a1dd88;
  puVar4 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
  __ss23CustomStringConvertibleP11descriptionSSvgTj();
  *(undefined **)(puVar5 + 0x30) = puVar2;
  *(undefined **)(puVar5 + 0x38) = puVar4;
  *(undefined8 *)(puVar5 + 0x40) = 0x676e6f73;
  *(undefined8 *)(puVar5 + 0x48) = 0xe400000000000000;
  IVar14 = *(ID *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::song);
  pcVar10 = "title";
  puVar2 = (undefined *)_objc_msgSend(IVar14,"title");
  if (puVar2 == (undefined *)0x0) {
    puVar2 = (undefined *)0x3e6c696e3c;
    pcVar10 = &DAT_e500000000000000;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  local_158 = puVar2;
  local_150 = pcVar10;
  _swift_bridgeObjectRetain(pcVar10);
  __sSS6appendyySSF(0x2f,0xe100000000000000);
  _swift_bridgeObjectRelease(pcVar10);
  pcVar10 = local_150;
  puVar4 = local_158;
  local_158 = (undefined *)_objc_msgSend(IVar14,"contentID");
  puVar2 = &DAT_100b0c6f0;
  FUN_100021774(&DAT_100b0c6f0);
  ppuVar3 = &local_158;
  __sSS10describingSSx_tclufC(ppuVar3,puVar2);
  local_158 = puVar4;
  local_150 = pcVar10;
  _swift_bridgeObjectRetain(pcVar10);
  __sSS6appendyySSF(ppuVar3,puVar2);
  _swift_bridgeObjectRelease(pcVar10);
  _swift_bridgeObjectRelease(puVar2);
  *(undefined **)(puVar5 + 0x50) = local_158;
  *(char **)(puVar5 + 0x58) = local_150;
  *(undefined8 *)(puVar5 + 0x60) = 0x497972617262696c;
  *(undefined1 **)(puVar5 + 0x68) = &DAT_e900000000000044;
  local_158 = *(undefined **)
               (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID);
  puVar2 = PTR___sSiN_100a1dd88;
  puVar4 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
  __ss23CustomStringConvertibleP11descriptionSSvgTj();
  *(undefined **)(puVar5 + 0x70) = puVar2;
  *(undefined **)(puVar5 + 0x78) = puVar4;
  *(undefined8 *)(puVar5 + 0x80) = 0x726f727265;
  *(undefined1 **)(puVar5 + 0x88) = &DAT_e500000000000000;
  _swift_getErrorValue(param_1,auStack_108,local_120);
  FUN_1002c2c2c();
  *(undefined8 *)(puVar5 + 0x90) = uStack_118;
  *(undefined8 *)(puVar5 + 0x98) = local_110;
  puVar4 = puVar5;
  FUN_10079bfc8();
  _swift_setDeallocating(puVar5);
  puVar2 = &DAT_100af5340;
  FUN_100021774(&DAT_100af5340);
  _swift_arrayDestroy(puVar5 + 0x20,4,puVar2);
  puVar5 = &_OBJC_CLASS___NSBundle;
  _swift_getInitializedObjCClass();
  IVar14 = _objc_msgSend((ID)puVar5,"mainBundle");
  uVar11 = 0x800000010090c2e0;
  uVar6 = 0xd000000000000017;
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (0xd000000000000017,0x800000010090c2e0,0,0,IVar14,0,0xe000000000000000,0,
             0xe000000000000000);
  IVar14 = _objc_msgSend((ID)puVar5,"mainBundle");
  uVar7 = 0xd000000000000052;
  uVar12 = 0x800000010090c300;
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (0xd000000000000052,0x800000010090c300,0,0,IVar14,0,0xe000000000000000,0,
             0xe000000000000000);
  puVar2 = puVar4;
  FUN_10079f184();
  puVar5 = &DAT_100af52f8;
  local_158 = puVar2;
  FUN_100021774(&DAT_100af52f8);
  puVar8 = &DAT_100af5300;
  FUN_1000f634c(&DAT_100af5300,&DAT_100af5308,PTR___sSSN_100a1dce0,PTR___sSayxGSKsMc_100a1dd28);
  uVar9 = 0x20;
  uVar13 = 0xe100000000000000;
  __sSKsSS7ElementRtzrlE6joined9separatorS2S_tF(0x20,0xe100000000000000,puVar5,puVar8);
  _swift_bridgeObjectRelease(puVar4);
  _swift_bridgeObjectRelease(puVar2);
  puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain_n(PTR___swiftEmptyArrayStorage_100a1e050,2);
  FUN_100831694(uVar6,uVar11,uVar7,uVar12,uVar9,uVar13,0,0,puVar5,puVar5,0);
  _swift_bridgeObjectRelease(uVar13);
  _swift_release_n(puVar5,2);
  _swift_bridgeObjectRelease(uVar12);
  _swift_bridgeObjectRelease(uVar11);
  IVar14 = _objc_msgSend(unaff_x20,"navigationController");
  if (IVar14 != 0) {
    puVar5 = &DAT_100a65760;
    _swift_allocObject(&DAT_100a65760,0x18,7);
    *(ID *)(puVar5 + 0x10) = unaff_x20;
    local_138 = FUN_1006369b4;
    local_158 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_150 = (char *)0x42000000;
    local_148 = FUN_10056b3d8;
    puStack_140 = &DAT_100a65778;
    local_130 = puVar5;
    aBlock = __Block_copy(&local_158);
    _swift_release(local_130);
    _objc_msgSend(IVar14,"presentViewController:animated:completion:",uVar6,1,aBlock);
    __Block_release(aBlock);
  }
  return 0;
}

// ==== 1007a0ce4 _TtC8Playback34SongMenuMIDIBankEditViewController::addEditBarButtonTapped: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34SongMenuMIDIBankEditViewController::addEditBarButtonTapped_
               (ID param_1,SEL param_2,ID param_3)

{
  FUN_1007a1368(param_1);
  return;
}

// ==== 1007a0d30 _TtC8Playback34SongMenuMIDIBankEditViewController::initWithStyle: ====
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback34SongMenuMIDIBankEditViewController::initWithStyle_
             (ID param_1,SEL param_2,long_long param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.SongMenuMIDIBankEditViewController",0x2b,"init(style:)",0xc,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1007a0d5c);
  (*pcVar1)();
}

// ==== 1007a0d5c _TtC8Playback34SongMenuMIDIBankEditViewController::initWithNibName:bundle: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback34SongMenuMIDIBankEditViewController::initWithNibName_bundle_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.SongMenuMIDIBankEditViewController",0x2b,"init(nibName:bundle:)",0x15,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1007a0d90);
  (*pcVar1)();
}

// ==== 1007a0d90 _TtC8Playback34SongMenuMIDIBankEditViewController::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback34SongMenuMIDIBankEditViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + mode);
  FUN_10029ff74(*puVar1,puVar1[1],puVar1[2],puVar1[3],puVar1[4],puVar1[5]);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + stagedName + 8));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + stagedDescription + 8));
  FUN_100026610(param_1 + delegate);
  return;
}

// ==== 1007a0e0c FUN_1007a0e0c ====
void FUN_1007a0e0c(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback34SongMenuMIDIBankEditViewController);
  return;
}

// ==== 1007a0e2c _TtC8Playback34SongMenuMIDIBankEditViewController::numberOfSectionsInTableView: ====
/* Function Stack Size: 0x18 bytes */

long_long _TtC8Playback34SongMenuMIDIBankEditViewController::numberOfSectionsInTableView_
                    (ID param_1,SEL param_2,ID param_3)

{
  return 1;
}

// ==== 1007a0e34 _TtC8Playback34SongMenuMIDIBankEditViewController::tableView:numberOfRowsInSection: ====
/* Function Stack Size: 0x20 bytes */

long_long _TtC8Playback34SongMenuMIDIBankEditViewController::tableView_numberOfRowsInSection_
                    (ID param_1,SEL param_2,ID param_3,long_long param_4)

{
  return 2;
}

// ==== 1007a0e3c FUN_1007a0e3c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_1007a0e3c(ID param_1)

{
  undefined8 uVar1;
  ID IVar2;
  ID IVar3;
  code *pcVar4;
  ulong uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long unaff_x20;
  code *pcVar10;
  ulong uVar11;
  undefined1 local_80 [24];
  undefined *local_68;
  
  IVar2 = param_1;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (IVar2 < 2) {
    if (((&DAT_100af34c8)[IVar2] & 1) == 0) {
      uVar6 = 0xd00000000000001b;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001b,0x80000001008e2d20);
      uVar7 = uVar6;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      IVar3 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar6,uVar7);
      pcVar4 = (code *)0x0;
      FUN_100547dc8(0);
      IVar2 = IVar3;
      _swift_dynamicCastClass(IVar3,pcVar4);
      if (IVar2 != 0) {
        if (DAT_100adf630 != -1) {
          pcVar4 = FUN_10052e5fc;
          _swift_once(&DAT_100adf630,FUN_10052e5fc);
        }
        uVar1 = DAT_100b76b48;
        uVar9 = DAT_100b76b40;
        _swift_bridgeObjectRetain(DAT_100b76b48);
        uVar8 = 0;
        FUN_10079f4b0(0);
        uVar7 = *(undefined8 *)
                 (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName);
        uVar6 = ((undefined8 *)
                (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName))[1];
        local_68 = &DAT_100a65820;
        local_80[0] = 0;
        _swift_bridgeObjectRetain(uVar6);
        FUN_100547658(uVar9,uVar1,uVar8,pcVar4,uVar7,uVar6,local_80);
        _swift_bridgeObjectRelease(uVar1);
        _swift_bridgeObjectRelease(pcVar4);
        _swift_bridgeObjectRelease(uVar6);
        FUN_10003d930(local_80);
      }
    }
    else {
      uVar7 = 0xd000000000000020;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000020,0x80000001008f0c40);
      uVar6 = uVar7;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      IVar3 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar7,uVar6);
      pcVar4 = (code *)0x0;
      FUN_1006fa210(0);
      IVar2 = IVar3;
      _swift_dynamicCastClass(IVar3,pcVar4);
      if (IVar2 != 0) {
        uVar11 = *(ulong *)(unaff_x20 +
                           _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription);
        pcVar10 = (code *)((ulong *)
                          (unaff_x20 +
                          _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription))[1];
        if ((uVar11 == 0 && pcVar10 == (code *)0xe000000000000000) ||
           (uVar5 = uVar11, pcVar4 = pcVar10,
           __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                     (uVar11,pcVar10,0,0xe000000000000000,0), (uVar5 & 1) != 0)) {
          uVar11 = 0;
          pcVar10 = (code *)0x0;
        }
        else {
          _swift_bridgeObjectRetain(pcVar10);
        }
        if (DAT_100adf3b8 != -1) {
          pcVar4 = FUN_10052d558;
          _swift_once(&DAT_100adf3b8,FUN_10052d558);
        }
        uVar6 = DAT_100b76658;
        uVar7 = DAT_100b76650;
        _swift_bridgeObjectRetain(DAT_100b76658);
        uVar9 = 1;
        FUN_10079f4b0(1);
        FUN_1006f99a4(uVar7,uVar6,uVar11,pcVar10,uVar9,pcVar4,0,1);
        _swift_bridgeObjectRelease(uVar6);
        _swift_bridgeObjectRelease(pcVar4);
        _swift_bridgeObjectRelease(pcVar10);
      }
    }
    return IVar3;
  }
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(1,0x1007a1144);
  (*pcVar4)();
}

// ==== 1007a1174 _TtC8Playback34SongMenuMIDIBankEditViewController::tableView:cellForRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback34SongMenuMIDIBankEditViewController::tableView_cellForRowAtIndexPath_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  undefined1 *puVar2;
  long lVar3;
  
  lVar1 = 0;
  __s10Foundation9IndexPathVMa();
  lVar3 = *(long *)(lVar1 + -8);
  puVar2 = &stack0xffffffffffffffc0 + -(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  __s10Foundation9IndexPathV36_unconditionallyBridgeFromObjectiveCyACSo07NSIndexC0CSgFZ
            (puVar2,param_4);
  FUN_1007a0e3c(param_3,puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return param_3;
}

// ==== 1007a124c FUN_1007a124c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007a124c(undefined8 param_1,ID param_2)

{
  ID *pIVar1;
  code *pcVar2;
  ID IVar3;
  ID IVar4;
  char *pcVar5;
  long unaff_x20;
  
  pcVar5 = "text";
  IVar3 = _objc_msgSend(param_2,"text");
  if (IVar3 != 0) {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    pIVar1 = (ID *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription
                   );
    IVar4 = pIVar1[1];
    *pIVar1 = IVar3;
    pIVar1[1] = (ID)pcVar5;
    _swift_bridgeObjectRelease(IVar4);
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(1,0x1007a12b8);
  (*pcVar2)();
}

// ==== 1007a12b8 FUN_1007a12b8 ====
void FUN_1007a12b8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  byte *pbVar2;
  long unaff_x20;
  undefined8 uVar3;
  byte local_51;
  undefined1 auStack_50 [24];
  long local_38;
  
  FUN_10003b4b4(param_3,auStack_50,&DAT_100af56a0);
  if (local_38 == 0) {
    FUN_10003d930(auStack_50);
  }
  else {
    pbVar2 = &local_51;
    _swift_dynamicCast(pbVar2,auStack_50,PTR___sypN_100a1e038 + 8,&DAT_100a65820,6);
    if (((int)pbVar2 != 0) && ((local_51 & 1) == 0)) {
      puVar1 = (undefined8 *)
               (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName);
      uVar3 = puVar1[1];
      *puVar1 = param_1;
      puVar1[1] = param_2;
      _swift_bridgeObjectRetain(param_2);
      _swift_bridgeObjectRelease(uVar3);
    }
  }
  return;
}

// ==== 1007a1368 FUN_1007a1368 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001007a16fc) */
/* WARNING: Removing unreachable block (ram,0x0001007a157c) */
/* WARNING: Removing unreachable block (ram,0x0001007a170c) */

void FUN_1007a1368(void)

{
  undefined8 *puVar1;
  ulong *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  undefined *puVar8;
  undefined8 uVar9;
  ID IVar10;
  undefined *puVar11;
  ID IVar12;
  ID IVar13;
  ID unaff_x20;
  ulong uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined1 auStack_d8 [120];
  
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::mode);
  uVar7 = puVar1[2];
  puVar2 = (ulong *)(unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedName);
  uVar14 = *puVar2;
  uVar5 = puVar2[1];
  if (uVar7 == 0) {
    puVar1 = (undefined8 *)
             (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription);
    uVar15 = *puVar1;
    uVar4 = puVar1[1];
    uVar16 = *(undefined8 *)
              (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID);
    _swift_bridgeObjectRetain(uVar5);
    _swift_bridgeObjectRetain(uVar4);
    puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    FUN_100714390(auStack_d8,uVar14,uVar5,uVar15,uVar4,uVar16,puVar11);
    IVar10 = _objc_msgSend(unaff_x20,"navigationItem");
    iVar6 = 2;
    FUN_1008c26ac(2,0xd,0,0);
    puVar11 = &_OBJC_CLASS___UIActivityIndicatorView;
    _objc_allocWithZone();
    uVar15 = 2;
    if (iVar6 != 0) {
      uVar15 = 100;
    }
    IVar12 = _objc_msgSend((ID)puVar11,"initWithActivityIndicatorStyle:",uVar15);
    _objc_msgSend(IVar12,"startAnimating");
    IVar13 = 0;
    FUN_1007711fc();
    _swift_getObjCClassFromMetadata();
    _objc_allocWithZone();
    IVar12 = _objc_msgSend(IVar13,"initWithCustomView:",IVar12);
    _objc_msgSend(IVar10,"setRightBarButtonItem:",IVar12);
    puVar11 = &DAT_100a656c0;
    _swift_allocObject(&DAT_100a656c0,0x18,7);
    _swift_unknownObjectWeakInit(puVar11 + 0x10);
    uVar14 = *puVar2;
    uVar5 = puVar2[1];
    uVar15 = *puVar1;
    uVar4 = puVar1[1];
    puVar8 = &DAT_100a656e8;
    _swift_allocObject(&DAT_100a656e8,0x38,7);
    *(undefined **)(puVar8 + 0x10) = puVar11;
    *(ulong *)(puVar8 + 0x18) = uVar14;
    *(ulong *)(puVar8 + 0x20) = uVar5;
    *(undefined8 *)(puVar8 + 0x28) = uVar15;
    *(undefined8 *)(puVar8 + 0x30) = uVar4;
    _swift_bridgeObjectRetain(uVar5);
    _swift_bridgeObjectRetain(uVar4);
    FUN_100056a68(FUN_1007a178c,puVar8);
    _swift_release(puVar8);
    FUN_100715050(auStack_d8);
  }
  else {
    uVar15 = *puVar1;
    uVar3 = uVar14 & 0xffffffffffff;
    if ((uVar5 & 0x2000000000000000) != 0) {
      uVar3 = uVar5 >> 0x38 & 0xf;
    }
    if (uVar3 == 0) {
      uVar14 = puVar1[1];
      _swift_bridgeObjectRetain();
    }
    else {
      _swift_bridgeObjectRetain(uVar5);
      uVar7 = uVar5;
    }
    uVar4 = *(undefined8 *)
             (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription);
    uVar16 = ((undefined8 *)
             (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::stagedDescription))[1];
    uVar17 = *(undefined8 *)
              (unaff_x20 + _TtC8Playback34SongMenuMIDIBankEditViewController::libraryID);
    uVar9 = uVar16;
    _swift_bridgeObjectRetain(uVar16);
    FUN_10079f5dc();
    FUN_1007146b0(auStack_d8,uVar14,uVar7,uVar4,uVar16,uVar17,uVar15,uVar9);
    IVar10 = _objc_msgSend(unaff_x20,"navigationItem");
    iVar6 = 2;
    FUN_1008c26ac(2,0xd,0,0);
    puVar11 = &_OBJC_CLASS___UIActivityIndicatorView;
    _objc_allocWithZone();
    uVar15 = 2;
    if (iVar6 != 0) {
      uVar15 = 100;
    }
    IVar12 = _objc_msgSend((ID)puVar11,"initWithActivityIndicatorStyle:",uVar15);
    _objc_msgSend(IVar12,"startAnimating");
    IVar13 = 0;
    FUN_1007711fc();
    _swift_getObjCClassFromMetadata();
    _objc_allocWithZone();
    IVar12 = _objc_msgSend(IVar13,"initWithCustomView:",IVar12);
    _objc_msgSend(IVar10,"setRightBarButtonItem:",IVar12);
    puVar11 = &DAT_100a656c0;
    _swift_allocObject(&DAT_100a656c0,0x18,7);
    _swift_unknownObjectWeakInit(puVar11 + 0x10);
    FUN_10005682c(FUN_1007a179c,puVar11);
    _swift_release(puVar11);
    FUN_100714fd4(auStack_d8);
  }
  return;
}

// ==== 1007f88c0 FUN_1007f88c0 ====
void FUN_1007f88c0(void)

{
  undefined8 *puVar1;
  long unaff_x20;
  
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::context);
  FUN_1005b487c(*puVar1,puVar1[1],puVar1[2],*(undefined1 *)(puVar1 + 3));
  _swift_bridgeObjectRelease
            (*(undefined8 *)
              (unaff_x20 +
              _TtC8Playback44SongMenuProductionCuesSelectorViewController::availableMIDIEventPacks))
  ;
  _swift_bridgeObjectRelease
            (*(undefined8 *)
              (unaff_x20 +
               _TtC8Playback44SongMenuProductionCuesSelectorViewController::
               selectedProductionCuesPack + 0x10));
  _swift_bridgeObjectRelease
            (*(undefined8 *)
              (unaff_x20 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::midiEvents))
  ;
  FUN_100026610(unaff_x20 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::delegate);
  return;
}

// ==== 1007f892c _TtC8Playback44SongMenuProductionCuesSelectorViewController::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback44SongMenuProductionCuesSelectorViewController::_cxx_destruct
               (ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + context);
  FUN_1005b487c(*puVar1,puVar1[1],puVar1[2],*(undefined1 *)(puVar1 + 3));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + availableMIDIEventPacks));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + selectedProductionCuesPack + 0x10));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + midiEvents));
  FUN_100026610(param_1 + delegate);
  return;
}

// ==== 1007f89cc _TtC8Playback44SongMenuProductionCuesSelectorViewController::tableView:numberOfRowsInSection: ====
/* Function Stack Size: 0x20 bytes */

long_long _TtC8Playback44SongMenuProductionCuesSelectorViewController::
          tableView_numberOfRowsInSection_(ID param_1,SEL param_2,ID param_3,long_long param_4)

{
  return *(long_long *)(*(long *)(param_1 + availableMIDIEventPacks) + 0x10);
}

// ==== 1007f89e0 FUN_1007f89e0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_1007f89e0(ID param_1)

{
  long lVar1;
  undefined8 uVar2;
  ID IVar3;
  undefined *puVar4;
  ID IVar5;
  ID IVar6;
  undefined8 uVar7;
  long lVar8;
  long unaff_x20;
  ulong uVar9;
  undefined8 uVar10;
  long lVar11;
  
  lVar11 = *(long *)(unaff_x20 +
                    _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                    availableMIDIEventPacks);
  lVar1 = lVar11;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((lVar1 < 0) || (*(long *)(lVar11 + 0x10) <= lVar1)) {
    _swift_bridgeObjectRelease(lVar11);
    puVar4 = &_OBJC_CLASS___UITableViewCell;
    _objc_allocWithZone();
    IVar3 = _objc_msgSend((ID)puVar4,"init");
    return IVar3;
  }
  lVar8 = lVar11 + lVar1 * 0x18;
  lVar1 = *(long *)(lVar8 + 0x20);
  uVar7 = *(undefined8 *)(lVar8 + 0x28);
  uVar10 = *(undefined8 *)(lVar8 + 0x30);
  _swift_bridgeObjectRetain(uVar10);
  _swift_bridgeObjectRelease(lVar11);
  uVar2 = 0xd00000000000001a;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001a,0x80000001008ea420);
  IVar3 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:",uVar2);
  if (IVar3 == 0) {
    puVar4 = &_OBJC_CLASS___UITableViewCell;
    _objc_allocWithZone();
    uVar2 = 0xd00000000000001a;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001a,0x80000001008ea420);
    IVar3 = _objc_msgSend((ID)puVar4,"initWithStyle:reuseIdentifier:",3,uVar2);
  }
  IVar5 = _objc_msgSend(IVar3,"textLabel");
  if (IVar5 != 0) {
    puVar4 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    _swift_bridgeObjectRetain(uVar10);
    IVar6 = _objc_msgSend((ID)puVar4,"mainBundle");
    uVar2 = uVar10;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (uVar7,uVar10,0,0,IVar6,0,0xe000000000000000,0,0xe000000000000000);
    _swift_bridgeObjectRelease(uVar10);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar2);
    _swift_bridgeObjectRelease(uVar2);
    _objc_msgSend(IVar5,"setText:",uVar7);
  }
  IVar5 = _objc_msgSend(IVar3,"textLabel");
  uVar9 = (ulong)(lVar1 != 3);
  if (lVar1 == 3) {
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setAlpha:",0x3fe0000000000000);
    }
    IVar5 = _objc_msgSend(IVar3,"detailTextLabel");
    if (IVar5 != 0) {
      puVar4 = &_OBJC_CLASS___NSBundle;
      _swift_getInitializedObjCClass();
      IVar6 = _objc_msgSend((ID)puVar4,"mainBundle");
      uVar7 = 0xd000000000000062;
      uVar2 = 0x80000001009102b0;
      __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
                (0xd000000000000062,0x80000001009102b0,0,0,IVar6,0,0xe000000000000000,0,
                 0xe000000000000000);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar2);
      _swift_bridgeObjectRelease(uVar2);
      _objc_msgSend(IVar5,"setText:",uVar7);
    }
    IVar5 = _objc_msgSend(IVar3,"detailTextLabel");
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setNumberOfLines:",0);
    }
    IVar5 = _objc_msgSend(IVar3,"detailTextLabel");
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setLineBreakMode:",0);
    }
    IVar5 = _objc_msgSend(IVar3,"detailTextLabel");
    if (IVar5 == 0) {
      uVar9 = 0;
    }
    else {
      _objc_msgSend(IVar5,"setAlpha:",0x3fe0000000000000);
    }
  }
  else {
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setAlpha:",0x3ff0000000000000);
    }
    IVar5 = _objc_msgSend(IVar3,"detailTextLabel");
    if (IVar5 == 0) {
      uVar9 = 1;
    }
    else {
      _objc_msgSend(IVar5,"setText:",0);
    }
  }
  _objc_msgSend(IVar3,"setUserInteractionEnabled:",uVar9);
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  lVar11 = DAT_100b757a8;
  FUN_10016f2bc();
  if ((((lVar11 == 0) ||
       ((*(uint *)(lVar11 + _TtC8Playback7APIUser::cloudProData) & 0xff0000) == 0x20000)) ||
      ((*(uint *)(lVar11 + _TtC8Playback7APIUser::cloudProData) >> 0x10 & 1) == 0)) &&
     ((lVar1 != -1 && (IVar5 = _objc_msgSend(IVar3,"textLabel"), IVar5 != 0)))) {
    _objc_msgSend(IVar5,"setAlpha:",0x3fe0000000000000);
  }
  if (((long *)(unaff_x20 +
               _TtC8Playback44SongMenuProductionCuesSelectorViewController::
               selectedProductionCuesPack))[2] == 0) {
    _swift_bridgeObjectRelease(uVar10);
  }
  else {
    lVar11 = *(long *)(unaff_x20 +
                      _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                      selectedProductionCuesPack);
    _swift_bridgeObjectRelease(uVar10);
    if (lVar11 == lVar1) {
      uVar7 = 3;
      goto LAB_1007f8f14;
    }
  }
  uVar7 = 0;
LAB_1007f8f14:
  _objc_msgSend(IVar3,"setAccessoryType:",uVar7);
  uVar7 = 0xd000000000000029;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000029,0x8000000100910280);
  _objc_msgSend(IVar3,"setAccessibilityIdentifier:",uVar7);
  return IVar3;
}

// ==== 1007f90e8 FUN_1007f90e8 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007f90e8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  long lVar2;
  long unaff_x20;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  lVar4 = *(long *)(unaff_x20 +
                   _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                   availableMIDIEventPacks);
  lVar2 = lVar4;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((lVar2 < 0) || (*(long *)(lVar4 + 0x10) <= lVar2)) {
    _swift_bridgeObjectRelease(lVar4);
LAB_1007f91b8:
    lVar2 = 0;
    __s10Foundation9IndexPathVMa();
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)(lVar2 + -8) + 0x38);
    uVar3 = 1;
  }
  else {
    lVar2 = lVar4 + lVar2 * 0x18;
    lVar5 = *(long *)(lVar2 + 0x20);
    uVar3 = *(undefined8 *)(lVar2 + 0x30);
    _swift_bridgeObjectRetain(uVar3);
    _swift_bridgeObjectRelease(lVar4);
    if (*(long *)(unaff_x20 +
                 _TtC8Playback44SongMenuProductionCuesSelectorViewController::demoSetlistSongID) < 1
       ) {
      if (DAT_100adea10 != -1) {
        _swift_once(&DAT_100adea10,FUN_1001709a4);
      }
      lVar2 = DAT_100b757a8;
      FUN_10016f2bc();
      if (lVar2 == 0) {
        _swift_bridgeObjectRelease(uVar3);
      }
      else {
        uVar1 = *(uint *)(lVar2 + _TtC8Playback7APIUser::cloudProData);
        _swift_bridgeObjectRelease(uVar3);
        if (((uVar1 & 0xff0000) != 0x20000) && ((uVar1 >> 0x10 & 1) != 0)) goto LAB_1007f9174;
      }
      if (lVar5 != -1) goto LAB_1007f91b8;
    }
    else {
      _swift_bridgeObjectRelease(uVar3);
    }
LAB_1007f9174:
    lVar2 = 0;
    __s10Foundation9IndexPathVMa();
    lVar4 = *(long *)(lVar2 + -8);
    (**(code **)(lVar4 + 0x10))(param_1,param_3,lVar2);
    UNRECOVERED_JUMPTABLE = *(code **)(lVar4 + 0x38);
    uVar3 = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x0001007f91ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar3,1,lVar2);
  return;
}

// ==== 1007f93c4 FUN_1007f93c4 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001007f96a4) */
/* WARNING: Removing unreachable block (ram,0x0001007f96a8) */
/* WARNING: Removing unreachable block (ram,0x0001007f96bc) */

long FUN_1007f93c4(ID param_1)

{
  char cVar1;
  undefined8 uVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  ID IVar6;
  undefined *puVar7;
  ID self;
  undefined *puVar8;
  long lVar9;
  undefined8 uVar10;
  ID unaff_x20;
  undefined8 uVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  long lVar14;
  undefined8 uVar15;
  
  IVar6 = param_1;
  __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
  _objc_msgSend(param_1,"deselectRowAtIndexPath:animated:",IVar6,1);
  lVar14 = *(long *)(unaff_x20 +
                    _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                    availableMIDIEventPacks);
  lVar5 = lVar14;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((lVar5 < 0) || (*(long *)(lVar14 + 0x10) <= lVar5)) {
    _swift_bridgeObjectRelease(lVar14);
    return lVar14;
  }
  lVar9 = lVar14 + lVar5 * 0x18;
  lVar5 = *(long *)(lVar9 + 0x20);
  uVar2 = *(undefined8 *)(lVar9 + 0x28);
  uVar11 = *(undefined8 *)(lVar9 + 0x30);
  _swift_bridgeObjectRetain(uVar11);
  _swift_bridgeObjectRelease(lVar14);
  uVar13 = *(undefined8 *)
            (unaff_x20 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::context);
  cVar3 = *(char *)((undefined8 *)
                    (unaff_x20 +
                    _TtC8Playback44SongMenuProductionCuesSelectorViewController::context) + 3);
  if (((long *)(unaff_x20 +
               _TtC8Playback44SongMenuProductionCuesSelectorViewController::
               selectedProductionCuesPack))[2] != 0) {
    cVar1 = '\0';
    if (lVar5 == *(long *)(unaff_x20 +
                          _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                          selectedProductionCuesPack)) {
      cVar1 = cVar3;
    }
    if (cVar1 == '\x01') {
      _swift_bridgeObjectRelease(uVar11);
      IVar6 = _objc_msgSend(unaff_x20,"navigationController");
      _objc_msgSend(IVar6,"popViewControllerAnimated:",1);
      return 0;
    }
  }
  __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
  IVar6 = _objc_msgSend(param_1,"cellForRowAtIndexPath:",lVar14);
  if (IVar6 != 0) {
    iVar4 = 2;
    FUN_1008c26ac(2,0xd,0,0);
    puVar7 = &_OBJC_CLASS___UIActivityIndicatorView;
    _objc_allocWithZone();
    uVar10 = 2;
    if (iVar4 != 0) {
      uVar10 = 100;
    }
    self = _objc_msgSend((ID)puVar7,"initWithActivityIndicatorStyle:",uVar10);
    _objc_msgSend(self,"startAnimating");
    _objc_msgSend(IVar6,"setAccessoryView:",self);
  }
  uVar10 = *(undefined8 *)
            (unaff_x20 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::contentID);
  uVar15 = *(undefined8 *)
            (unaff_x20 +
            _TtC8Playback44SongMenuProductionCuesSelectorViewController::demoSetlistSongID);
  uVar12 = 0;
  if (cVar3 == '\0') {
    uVar12 = (undefined4)uVar13;
  }
  puVar7 = &DAT_100a6af10;
  _swift_allocObject(&DAT_100a6af10,0x18,7);
  _swift_unknownObjectWeakInit(puVar7 + 0x10);
  puVar8 = &DAT_100a6af38;
  _swift_allocObject(&DAT_100a6af38,0x40,7);
  *(undefined **)(puVar8 + 0x10) = puVar7;
  *(long *)(puVar8 + 0x18) = lVar5;
  *(undefined8 *)(puVar8 + 0x20) = uVar2;
  *(undefined8 *)(puVar8 + 0x28) = uVar11;
  *(ID *)(puVar8 + 0x30) = IVar6;
  *(ID *)(puVar8 + 0x38) = param_1;
  _swift_bridgeObjectRetain(uVar11);
  _swift_retain(puVar7);
  FUN_100450684(uVar10,uVar15,uVar12,FUN_1007fa31c,puVar8,lVar5);
  _swift_release(puVar7);
  _swift_release(puVar8);
  _swift_bridgeObjectRelease(uVar11);
  return 0;
}

// ==== 1008418a8 FUN_1008418a8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1008418a8(undefined8 param_1,ulong param_2,undefined4 param_3,undefined **param_4,
                  long param_5,code *param_6,undefined8 param_7,code *param_8,undefined8 param_9,
                  ulong param_10)

{
  uint uVar1;
  char *pcVar2;
  ulong uVar3;
  short sVar4;
  code *pcVar5;
  undefined4 uVar6;
  ulong uVar7;
  long lVar8;
  undefined **ppuVar9;
  undefined **ppuVar10;
  undefined8 uVar11;
  undefined *puVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined *puVar15;
  undefined *puVar16;
  long lVar17;
  ID IVar18;
  undefined *puVar19;
  ulong uVar20;
  undefined *puVar21;
  ulong uVar22;
  undefined8 uVar23;
  undefined8 *puVar24;
  ID IVar25;
  long lVar26;
  undefined8 uVar27;
  undefined8 *puVar28;
  long lVar29;
  undefined8 local_3c0;
  undefined8 local_3b8;
  long local_3b0 [3];
  code *local_398;
  code *local_390;
  ID local_388;
  long local_380;
  ulong local_378;
  long local_370;
  ulong local_368;
  ulong local_360;
  ulong local_358;
  ulong local_350;
  undefined8 local_348;
  ulong local_340;
  undefined *local_338;
  undefined8 local_330;
  undefined8 uStack_328;
  undefined8 local_320;
  long local_318;
  uint local_30c;
  undefined8 local_308;
  ID local_300;
  ulong local_2f8;
  ulong local_2f0;
  undefined **local_2e8;
  ulong local_2e0;
  ulong local_2d8;
  undefined1 local_2d0 [8];
  undefined8 uStack_2c8;
  undefined8 local_2c0;
  undefined1 auStack_2b8 [200];
  undefined *local_1f0 [5];
  undefined **local_1c8;
  undefined *puStack_1c0;
  undefined *local_1b0;
  undefined1 local_1a0 [24];
  undefined1 auStack_188 [40];
  undefined1 local_160 [24];
  undefined *local_148;
  undefined *local_80 [2];
  
  local_2e0 = CONCAT44(local_2e0._4_4_,param_3);
  local_3b0[0] = param_9;
  puVar21 = &DAT_100af5580;
  local_3b8 = param_7;
  local_3b0[2] = param_5;
  local_398 = param_6;
  local_390 = param_8;
  FUN_100021774();
  IVar25 = (long)&local_3c0 -
           (*(long *)(*(long *)(puVar21 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  uVar7 = 0;
  local_300 = IVar25;
  FUN_10068e908();
  local_2f0 = *(ulong *)(uVar7 - 8);
  uVar20 = *(long *)(local_2f0 + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_2d8 = IVar25 - uVar20;
  lVar29 = local_2d8 - uVar20;
  lVar8 = 0;
  local_3b0[1] = lVar29 - uVar20;
  local_2f8 = uVar7;
  FUN_1002aa5c8();
  lVar26 = (lVar29 - uVar20) - (*(long *)(*(long *)(lVar8 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0)
  ;
  puVar21 = &DAT_100af5588;
  FUN_100021774();
  puVar24 = (undefined8 *)
            (lVar26 - (*(long *)(*(long *)(puVar21 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0));
  FUN_10003b4b4(param_1,puVar24,&DAT_100af5588);
  puVar28 = puVar24;
  _swift_getEnumCaseMultiPayload(puVar24,puVar21);
  local_2e8 = param_4;
  if ((int)puVar28 == 1) {
    uVar23 = 0xd000000000000010;
    local_2d8 = *puVar24;
    pcVar2 = " %{public}s. Error %{public}s";
    uVar11 = 0xd00000000000002e;
    if ((param_2 & 1) == 0) {
      pcVar2 = "rom API response: %{public}s";
      uVar11 = 0xd00000000000002a;
    }
    __sSo13os_log_type_ta0A0E4infoABvgZ();
    puVar21 = &DAT_100af52c8;
    FUN_100021774();
    _swift_initStackObject();
    *(undefined8 *)(puVar21 + 0x18) = 8;
    *(undefined8 *)(puVar21 + 0x10) = 4;
    puVar15 = PTR___sSSN_100a1dce0;
    uVar1 = (uint)local_2e0 & 0xff;
    if (uVar1 < 2) {
      if ((local_2e0 & 0xff) == 0) {
        uVar27 = 0xef64657461647055;
        uVar23 = 0x676e6f534944494d;
      }
      else {
        uVar27 = 0x80000001008cef90;
      }
    }
    else if (uVar1 == 2) {
      uVar27 = 0xe900000000000067;
      uVar23 = 0x6e696d6165727473;
    }
    else if (uVar1 == 3) {
      uVar27 = 0xee00726566736e61;
      uVar23 = 0x72546c61746e6572;
    }
    else {
      uVar27 = 0xe700000000000000;
      uVar23 = 0x7473696c746573;
    }
    *(undefined **)(puVar21 + 0x38) = PTR___sSSN_100a1dce0;
    puVar16 = puVar21;
    FUN_100026528();
    ppuVar10 = local_2e8;
    *(undefined **)(puVar21 + 0x40) = puVar16;
    *(undefined8 *)(puVar21 + 0x20) = uVar23;
    *(undefined8 *)(puVar21 + 0x28) = uVar27;
    local_1c8 = local_2e8;
    puVar12 = PTR___sSiN_100a1dd88;
    puVar19 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
    __ss23CustomStringConvertibleP11descriptionSSvgTj();
    uVar7 = local_2d8;
    *(undefined **)(puVar21 + 0x60) = puVar15;
    *(undefined **)(puVar21 + 0x68) = puVar16;
    *(undefined **)(puVar21 + 0x48) = puVar12;
    *(undefined **)(puVar21 + 0x50) = puVar19;
    *(undefined **)(puVar21 + 0x88) = puVar15;
    *(undefined **)(puVar21 + 0x90) = puVar16;
    *(undefined8 *)(puVar21 + 0x70) = uVar11;
    *(ulong *)(puVar21 + 0x78) = (ulong)pcVar2 | 0x8000000000000000;
    _swift_getErrorValue(local_2d8,auStack_2b8,local_2d0);
    FUN_1002c2c2c();
    *(undefined **)(puVar21 + 0xb0) = puVar15;
    *(undefined **)(puVar21 + 0xb8) = puVar16;
    *(undefined8 *)(puVar21 + 0x98) = uStack_2c8;
    *(undefined8 *)(puVar21 + 0xa0) = local_2c0;
    FUN_10041ac94(puVar28,4,
                  "Failed to update MIDI Events for %{public}@ with content ID %@ - %{public}s. Error %{public}s"
                  ,0x5d,2,puVar21);
    _swift_setDeallocating(puVar21);
    puVar15 = &DAT_100af5bc8;
    FUN_100021774(&DAT_100af5bc8);
    _swift_arrayDestroy(puVar21 + 0x20,4,puVar15);
    if ((param_2 & 1) != 0) {
      puVar21 = &DAT_100a6e228;
      _swift_allocObject(&DAT_100a6e228,0x18,7);
      lVar8 = local_3b0[2];
      _swift_unknownObjectWeakInit(puVar21 + 0x10,local_3b0[2]);
      puVar15 = &DAT_100a6e368;
      _swift_allocObject(&DAT_100a6e368,0x22,7);
      *(undefined ***)(puVar15 + 0x10) = ppuVar10;
      *(undefined **)(puVar15 + 0x18) = puVar21;
      puVar15[0x20] = (char)local_2e0;
      puVar15[0x21] = 0;
      puVar28 = (undefined8 *)
                (lVar8 + _TtC8Playback11AppDelegate::songMIDINeedsUpdateWhenAvailableHandler);
      uVar11 = *puVar28;
      uVar23 = puVar28[1];
      *puVar28 = thunk_FUN_100848958;
      puVar28[1] = puVar15;
      FUN_1000274b4(uVar11,uVar23);
    }
    if (local_398 != (code *)0x0) {
      (*local_398)(2);
    }
    if (local_390 != (code *)0x0) {
      (*local_390)();
    }
    _swift_errorRelease(uVar7);
  }
  else {
    FUN_100023340(puVar24,lVar26,FUN_1002aa5c8);
    ppuVar10 = (undefined **)PTR___swiftEmptyArrayStorage_100a1e050;
    local_370 = lVar26;
    lVar8 = *(long *)(lVar26 + *(int *)(lVar8 + 0x28) + 0x10);
    IVar25 = *(ID *)(lVar8 + 0x10);
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    _swift_bridgeObjectRetain(lVar8);
    uVar7 = local_2f0;
    local_2e0 = IVar25;
    if (IVar25 != 0) {
      IVar25 = 0;
      do {
        if (*(ulong *)(lVar8 + 0x10) <= IVar25) {
                    /* WARNING: Does not return */
          pcVar5 = (code *)SoftwareBreakpoint(1,0x100842bd8);
          (*pcVar5)();
        }
        uVar20 = (ulong)*(byte *)(uVar7 + 0x50) + 0x20 &
                 ((ulong)*(byte *)(uVar7 + 0x50) ^ 0xffffffffffffffff);
        lVar26 = *(long *)(uVar7 + 0x48);
        FUN_100023384(lVar8 + uVar20 + lVar26 * IVar25,lVar29,FUN_10068e908);
        if ((undefined **)(long)*(int *)(lVar29 + 4) == param_4) {
          FUN_100023340(lVar29,local_2d8,FUN_10068e908);
          ppuVar9 = ppuVar10;
          _swift_isUniquelyReferenced_nonNull_native();
          local_1c8 = ppuVar10;
          if (((ulong)ppuVar9 & 1) == 0) {
            FUN_1001cd62c(0,ppuVar10[2] + 1,1);
          }
          puVar21 = local_1c8[2];
          if ((undefined *)((ulong)local_1c8[3] >> 1) <= puVar21) {
            FUN_1001cd62c((undefined *)0x1 < local_1c8[3],puVar21 + 1,1);
          }
          ppuVar10 = local_1c8;
          local_1c8[2] = puVar21 + 1;
          FUN_100023340(local_2d8,(undefined *)((long)local_1c8 + (long)puVar21 * lVar26 + uVar20),
                        FUN_10068e908);
          uVar7 = local_2f0;
          param_4 = local_2e8;
        }
        else {
          FUN_1000233c8(lVar29,FUN_10068e908);
        }
        IVar25 = IVar25 + 1;
      } while (local_2e0 != IVar25);
    }
    _swift_bridgeObjectRelease(lVar8);
    IVar25 = local_300;
    puVar21 = ppuVar10[2];
    if (puVar21 != (undefined *)0x0) {
      FUN_100023384((undefined *)
                    ((long)ppuVar10 +
                    ((ulong)*(byte *)(uVar7 + 0x50) + 0x20 &
                    ((ulong)*(byte *)(uVar7 + 0x50) ^ 0xffffffffffffffff))),local_300,FUN_10068e908)
      ;
    }
    uVar20 = local_2f8;
    lVar8 = local_370;
    (**(code **)(uVar7 + 0x38))(IVar25,puVar21 == (undefined *)0x0,1,local_2f8);
    _swift_release(ppuVar10);
    IVar18 = IVar25;
    (**(code **)(uVar7 + 0x30))(IVar25,1,uVar20);
    if ((int)IVar18 == 1) {
      FUN_1000233c8(lVar8,FUN_1002aa5c8);
      FUN_100023be4(IVar25,&DAT_100af5580);
    }
    else {
      FUN_100023340(IVar25,local_3b0[1],FUN_10068e908);
      local_368 = param_10;
      if (param_10 >> 0x3e == 0) {
        uVar7 = *(ulong *)((param_10 & 0xfffffffffffff8) + 0x10);
      }
      else {
        uVar7 = param_10 & 0xffffffffffffff8;
        if ((long)param_10 < 0) {
          uVar7 = param_10;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      if (uVar7 != 0) {
        local_350 = local_368 & 0xc000000000000001;
        local_378 = local_368 & 0xffffffffffffff8;
        local_380 = local_368 + 0x20;
        _swift_bridgeObjectRetain();
        uVar20 = 0;
        local_320 = 0;
        local_358 = uVar7;
        do {
          if (local_350 == 0) {
            if (*(ulong *)(local_378 + 0x10) <= uVar20) {
                    /* WARNING: Does not return */
              pcVar5 = (code *)SoftwareBreakpoint(1,0x100842bec);
              (*pcVar5)();
            }
            uVar7 = *(ID *)(local_380 + uVar20 * 8);
            IVar25 = local_2e0;
          }
          else {
            uVar7 = uVar20;
            FUN_1000cbedc(uVar20,local_368);
            IVar25 = local_2e0;
          }
          local_2e0 = uVar7;
          if (SCARRY8(uVar20,1)) {
                    /* WARNING: Does not return */
            pcVar5 = (code *)SoftwareBreakpoint(1,0x100842bdc);
            local_2e0 = IVar25;
            (*pcVar5)();
          }
          uVar20 = uVar20 + 1;
          IVar25 = _objc_msgSend(local_2e0,"midiEventsDefaultArrangement");
          local_2d8 = uVar20;
          if (IVar25 == 0) {
LAB_100841ed8:
            uVar20 = local_2d8;
            puVar15 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain();
joined_r0x000100841eb8:
            if ((ulong)puVar15 >> 0x3e != 0) goto LAB_100841fb8;
LAB_100841ef0:
            puVar21 = *(undefined **)(((ulong)puVar15 & 0xfffffffffffff8) + 0x10);
            if (puVar21 == (undefined *)0x0) goto LAB_100841fd0;
LAB_100841efc:
            if ((long)puVar21 < 1) {
                    /* WARNING: Does not return */
              pcVar5 = (code *)SoftwareBreakpoint(1,0x100842be0);
              (*pcVar5)();
            }
            _swift_bridgeObjectRetain(puVar15);
            puVar16 = (undefined *)0x0;
            do {
              if (((ulong)puVar15 & 0xc000000000000001) == 0) {
                puVar12 = *(undefined **)(puVar15 + (long)puVar16 * 8 + 0x20);
              }
              else {
                puVar12 = puVar16;
                FUN_1000cc6e4(puVar16,puVar15);
              }
              if (DAT_100ade9d8 != -1) {
                _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
              }
              puVar16 = puVar16 + 1;
              IVar25 = _objc_msgSend(DAT_100b755c8,"viewContext");
              _objc_msgSend(IVar25,"deleteObject:",puVar12);
            } while (puVar21 != puVar16);
            _swift_bridgeObjectRelease_n(puVar15,2);
            uVar20 = local_2d8;
          }
          else {
            ppuVar10 = (undefined **)_objc_msgSend(IVar25,"array");
            __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                      (ppuVar10,PTR___sypN_100a1e038 + 8);
            puVar21 = ppuVar10[2];
            local_1f0[0] = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain();
            FUN_1001cc644(0,puVar21,0);
            puVar15 = local_1f0[0];
            puVar21 = ppuVar10[2];
            ppuVar9 = ppuVar10;
            if (puVar21 == (undefined *)0x0) {
              _swift_bridgeObjectRelease();
              goto joined_r0x000100841eb8;
            }
            do {
              local_2e8 = ppuVar9;
              puVar15 = local_1f0[0];
              ppuVar10 = ppuVar10 + 4;
              FUN_10003b4f8(ppuVar10,&local_1c8);
              uVar11 = 0;
              FUN_1000287b8(0);
              ppuVar9 = local_80;
              _swift_dynamicCast(ppuVar9,&local_1c8,PTR___sypN_100a1e038 + 8,uVar11,6);
              puVar16 = local_80[0];
              if ((int)ppuVar9 == 0) {
                _swift_release(puVar15);
                local_80[0] = (undefined *)0x0;
                _swift_bridgeObjectRelease(local_2e8);
                goto LAB_100841ed8;
              }
              uVar7 = *(ulong *)(puVar15 + 0x10);
              local_1f0[0] = puVar15;
              if (*(ulong *)(puVar15 + 0x18) >> 1 <= uVar7) {
                FUN_1001cc644(1 < *(ulong *)(puVar15 + 0x18),uVar7 + 1,1);
              }
              puVar15 = local_1f0[0];
              *(ulong *)(local_1f0[0] + 0x10) = uVar7 + 1;
              *(undefined **)(local_1f0[0] + uVar7 * 8 + 0x20) = puVar16;
              puVar21 = puVar21 + -1;
              ppuVar9 = local_2e8;
            } while (puVar21 != (undefined *)0x0);
            _swift_bridgeObjectRelease(local_2e8);
            uVar20 = local_2d8;
            if ((ulong)puVar15 >> 0x3e == 0) goto LAB_100841ef0;
LAB_100841fb8:
            puVar21 = (undefined *)((ulong)puVar15 & 0xffffffffffffff8);
            if ((long)puVar15 < 0) {
              puVar21 = puVar15;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg();
            if (puVar21 != (undefined *)0x0) goto LAB_100841efc;
LAB_100841fd0:
            _swift_bridgeObjectRelease(puVar15);
          }
          uVar7 = local_368;
        } while (uVar20 != local_358);
        _swift_bridgeObjectRelease(local_368);
        lVar26 = *(long *)(local_3b0[1] + *(int *)(local_2f8 + 0xac));
        lVar8 = local_370;
        if (lVar26 != 0) {
          local_388 = *(ID *)(lVar26 + 0x10);
          local_3c0 = _TtC8Playback11AppDelegate::window;
          _swift_bridgeObjectRetain(uVar7);
          uStack_328 = 6;
          local_330 = 3;
          uVar7 = 0;
          local_318 = lVar26;
          do {
            if (local_350 == 0) {
              if (*(ulong *)(local_378 + 0x10) <= uVar7) {
                    /* WARNING: Does not return */
                pcVar5 = (code *)SoftwareBreakpoint(1,0x100842bf0);
                (*pcVar5)();
              }
              uVar20 = *(ulong *)(local_380 + uVar7 * 8);
            }
            else {
              uVar20 = uVar7;
              FUN_1000cbedc(uVar7,local_368);
            }
            IVar25 = local_388;
            puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
            if (SCARRY8(uVar7,1)) {
                    /* WARNING: Does not return */
              pcVar5 = (code *)SoftwareBreakpoint(1,0x100842be4);
              (*pcVar5)();
            }
            local_360 = uVar7 + 1;
            local_340 = uVar20;
            if (local_388 == 0) {
              _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            }
            else {
              uVar11 = 0;
              FUN_1000287b8();
              local_348 = uVar11;
              _swift_retain(puVar21);
              _swift_bridgeObjectRetain(lVar26);
              uVar7 = 0;
              local_338 = puVar21;
              do {
                lVar26 = lVar26 + uVar7;
                local_300 = *(ID *)(lVar26 + 0x20);
                sVar4 = *(short *)(lVar26 + 0x28);
                lVar8 = (long)sVar4;
                local_2e8 = (undefined **)CONCAT44(local_2e8._4_4_,(uint)*(byte *)(lVar26 + 0x38));
                local_2f0 = CONCAT44(local_2f0._4_4_,(uint)*(ushort *)(lVar26 + 0x3c));
                local_2f8 = CONCAT44(local_2f8._4_4_,(uint)*(ushort *)(lVar26 + 0x3e));
                uVar11 = *(undefined8 *)(lVar26 + 0x40);
                uVar20 = *(ulong *)(lVar26 + 0x48);
                uVar23 = *(undefined8 *)(lVar26 + 0x50);
                uVar3 = *(ulong *)(lVar26 + 0x58);
                local_308 = *(undefined8 *)(lVar26 + 0x60);
                uVar27 = *(undefined8 *)(lVar26 + 0x68);
                local_30c = (uint)*(byte *)(lVar26 + 0x70);
                local_2e0 = IVar25;
                local_2d8 = uVar7;
                _swift_bridgeObjectRetain(uVar27);
                _swift_bridgeObjectRetain(uVar20);
                _swift_bridgeObjectRetain(uVar3);
                uVar13 = uVar11;
                uVar7 = uVar20;
                FUN_1006d7494(uVar11);
                if ((((uVar7 & 1) == 0) &&
                    (uVar14 = uVar23, uVar7 = uVar3, FUN_1006d7494(uVar23), (uVar7 & 1) == 0)) &&
                   (FUN_100430100(), lVar8 != 0)) {
                  _swift_bridgeObjectRetain(uVar27);
                  IVar25 = local_300;
                  FUN_100027f64(uVar13,uVar13,uVar14,local_300,lVar8,(ulong)local_2e8 & 0xffffffff,
                                local_2f0 & 0xffffffff,local_2f8 & 0xffffffff,local_30c,local_308,
                                uVar27);
                  _swift_bridgeObjectRelease(uVar27);
                  _swift_bridgeObjectRelease(uVar3);
                  _swift_bridgeObjectRelease(uVar20);
                  _objc_msgSend(IVar25,"setSong:",local_340);
                  puVar21 = local_338;
                  puVar15 = local_338;
                  _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
                  uVar7 = local_2d8;
                  uVar20 = local_2e0;
                  lVar26 = local_318;
                  if ((((int)puVar15 == 0) || ((long)puVar21 < 0)) ||
                     (((ulong)puVar21 >> 0x3e & 1) != 0)) {
                    if ((ulong)puVar21 >> 0x3e == 0) {
                      puVar15 = *(undefined **)(((ulong)puVar21 & 0xfffffffffffff8) + 0x10);
                    }
                    else {
                      puVar15 = (undefined *)((ulong)puVar21 & 0xffffffffffffff8);
                      if ((long)puVar21 < 0) {
                        puVar15 = puVar21;
                      }
                      __ss18_CocoaArrayWrapperV8endIndexSivg(puVar15);
                    }
                    puVar16 = (undefined *)0x0;
                    FUN_1007900e0(0,puVar15 + 1,1,puVar21);
                    puVar21 = puVar16;
                  }
                  uVar22 = (ulong)puVar21 & 0xffffffffffffff8;
                  uVar3 = *(ulong *)(uVar22 + 0x10);
                  local_338 = puVar21;
                  if (*(ulong *)(uVar22 + 0x18) >> 1 <= uVar3) {
                    puVar15 = (undefined *)(ulong)(1 < *(ulong *)(uVar22 + 0x18));
                    FUN_1007900e0(puVar15,uVar3 + 1,1,puVar21);
                    uVar22 = (ulong)puVar15 & 0xffffffffffffff8;
                    local_338 = puVar15;
                  }
                  *(ulong *)(uVar22 + 0x10) = uVar3 + 1;
                  *(ID *)(uVar22 + uVar3 * 8 + 0x20) = IVar25;
                }
                else {
                  puVar21 = &DAT_100af53a0;
                  FUN_100021774();
                  _swift_initStackObject();
                  *(undefined8 *)(puVar21 + 0x18) = uStack_328;
                  *(undefined8 *)(puVar21 + 0x10) = local_330;
                  puVar28 = (undefined8 *)(puVar21 + 0x20);
                  *puVar28 = 0x65646f63656d6974;
                  *(undefined8 *)(puVar21 + 0x28) = 0xe800000000000000;
                  uVar7 = uVar20;
                  FUN_1006d7494();
                  puVar15 = PTR___sSdN_100a1dd60;
                  if ((uVar7 & 1) != 0) {
                    uVar11 = 0;
                    *(undefined8 *)(puVar21 + 0x38) = 0;
                    *(undefined8 *)(puVar21 + 0x40) = 0;
                    puVar15 = (undefined *)0x0;
                  }
                  *(undefined8 *)(puVar21 + 0x30) = uVar11;
                  *(undefined **)(puVar21 + 0x48) = puVar15;
                  *(undefined8 *)(puVar21 + 0x50) = 0x6e6f697461727564;
                  *(undefined8 *)(puVar21 + 0x58) = 0xe800000000000000;
                  uVar7 = uVar3;
                  FUN_1006d7494();
                  puVar15 = PTR___sSdN_100a1dd60;
                  if ((uVar7 & 1) != 0) {
                    uVar23 = 0;
                    *(undefined8 *)(puVar21 + 0x68) = 0;
                    *(undefined8 *)(puVar21 + 0x70) = 0;
                    puVar15 = (undefined *)0x0;
                  }
                  puVar16 = PTR___sSSN_100a1dce0;
                  *(undefined8 *)(puVar21 + 0x60) = uVar23;
                  *(undefined **)(puVar21 + 0x78) = puVar15;
                  *(undefined8 *)(puVar21 + 0x80) = 0x737562;
                  *(undefined8 *)(puVar21 + 0x88) = 0xe300000000000000;
                  *(undefined **)(puVar21 + 0xa8) = PTR___ss5Int16VN_100a1def8;
                  *(short *)(puVar21 + 0x90) = sVar4;
                  _swift_bridgeObjectRelease(uVar27);
                  _swift_bridgeObjectRelease(uVar3);
                  _swift_bridgeObjectRelease(uVar20);
                  puVar15 = puVar21;
                  FUN_10079beb4();
                  _swift_setDeallocating(puVar21);
                  puVar21 = &DAT_100af53a8;
                  FUN_100021774(&DAT_100af53a8);
                  _swift_arrayDestroy(puVar28,3,puVar21);
                  FUN_100029020();
                  puVar21 = &DAT_100a21138;
                  _swift_allocError(&DAT_100a21138,puVar28,0,0);
                  puVar28[1] = 0;
                  puVar28[2] = 0;
                  *puVar28 = puVar15;
                  *(undefined1 *)(puVar28 + 3) = 1;
                  puVar15 = puVar21;
                  _swift_willThrow();
                  uVar6 = SUB84(puVar15,0);
                  __sSo13os_log_type_ta0A0E7defaultABvgZ();
                  local_2e8 = (undefined **)CONCAT44(local_2e8._4_4_,uVar6);
                  _swift_getErrorValue(puVar21,auStack_188,local_1a0);
                  FUN_1002c2c2c();
                  local_148 = puVar16;
                  FUN_100026528();
                  local_80[0] = PTR___swiftEmptyArrayStorage_100a1e050;
                  _swift_retain();
                  FUN_1001cc300(0,1,0);
                  puVar12 = local_80[0];
                  FUN_10003d87c(local_160,&local_1c8);
                  FUN_10003d87c(&local_1c8,local_1f0);
                  puVar15 = &DAT_100af5bc8;
                  FUN_100021774();
                  ppuVar10 = local_1f0;
                  __sSS10describingSSx_tclufC();
                  FUN_100023468(&local_1c8);
                  uVar7 = *(ulong *)(puVar12 + 0x10);
                  if (*(ulong *)(puVar12 + 0x18) >> 1 <= uVar7) {
                    FUN_1001cc300(1 < *(ulong *)(puVar12 + 0x18),uVar7 + 1,1);
                    puVar12 = local_80[0];
                  }
                  local_1b0 = puVar16;
                  *(ulong *)(puVar12 + 0x10) = uVar7 + 1;
                  local_1c8 = ppuVar10;
                  puStack_1c0 = puVar15;
                  FUN_1000437e8(&local_1c8,puVar12 + uVar7 * 0x28 + 0x20);
                  FUN_100023404(0,&DAT_100af5590,&PTR__OBJC_CLASS___OS_os_log_100aa3e98);
                  if (DAT_100adf080 != -1) {
                    _swift_once(&DAT_100adf080,FUN_10041abd0);
                  }
                  uVar23 = DAT_100b02448;
                  uVar11 = DAT_100b02440;
                  _swift_bridgeObjectRetain(DAT_100b02448);
                  __sSo9OS_os_logC0B0E9subsystem8categoryABSS_SStcfC
                            (uVar11,uVar23,0x67656c6544707041,0xeb00000000657461);
                  FUN_100279b9c("Failed to initialize MIDIEvent from API response: %{public}s",0x3c,
                                2,(ulong)local_2e8 & 0xffffffff,puVar12);
                  _swift_release(puVar12);
                  FUN_100023468(local_160);
                  _swift_errorRelease(puVar21);
                  local_320 = 0;
                  uVar7 = local_2d8;
                  lVar26 = local_318;
                  uVar20 = local_2e0;
                }
                uVar7 = uVar7 + 0x58;
                IVar25 = uVar20 - 1;
              } while (IVar25 != 0);
              _swift_bridgeObjectRelease(lVar26);
              puVar21 = local_338;
            }
            puVar15 = puVar21;
            FUN_1001c61b8(puVar21);
            _swift_bridgeObjectRelease(puVar21);
            puVar16 = &_OBJC_CLASS___NSMutableOrderedSet;
            _objc_allocWithZone();
            puVar21 = puVar15;
            __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar15,PTR___sypN_100a1e038 + 8);
            _swift_bridgeObjectRelease(puVar15);
            IVar25 = _objc_msgSend((ID)puVar16,"initWithArray:",puVar21);
            uVar7 = local_340;
            _objc_msgSend(local_340,"setMidiEventsDefaultArrangement:",IVar25);
            lVar8 = _TtC8Playback4Song::privateSongMap;
            lVar17 = *(long *)(uVar7 + _TtC8Playback4Song::privateSongMap);
            lVar29 = lVar17;
            if (lVar17 == 0) {
              FUN_100861310();
              _swift_allocObject();
              puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
              *(undefined **)(lVar17 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
              *(undefined8 *)(lVar17 + 0x28) = 0;
              *(undefined8 *)(lVar17 + 0x20) = 0;
              *(undefined8 *)(lVar17 + 0x38) = 0;
              *(undefined8 *)(lVar17 + 0x30) = 0;
              _swift_unknownObjectUnownedInit(lVar17 + 0x10,uVar7);
              _swift_retain(puVar21);
              FUN_10085ee38(uVar7);
              uVar11 = *(undefined8 *)(uVar7 + lVar8);
              *(long *)(uVar7 + lVar8) = lVar17;
              _swift_retain(lVar17);
              _swift_release(uVar11);
              lVar29 = 0;
            }
            lVar8 = local_370;
            uVar11 = *(undefined8 *)(lVar17 + 0x30);
            *(undefined8 *)(lVar17 + 0x30) = 0;
            _swift_retain(lVar29);
            _swift_release(lVar17);
            _swift_bridgeObjectRelease(uVar11);
            if (DAT_100adeca8 != -1) {
              _swift_once(&DAT_100adeca8,FUN_100224b00);
            }
            IVar25 = *(ID *)(DAT_100b75a80 + 0x10);
            if (IVar25 != 0) {
              IVar18 = IVar25;
              FUN_1004a6154();
              IVar25 = _objc_msgSend(IVar25,"currentSetlistIndex");
              if (IVar18 >> 0x3e == 0) {
                uVar7 = *(ulong *)((IVar18 & 0xfffffffffffff8) + 0x10);
              }
              else {
                uVar7 = IVar18 & 0xffffffffffffff8;
                if ((long)IVar18 < 0) {
                  uVar7 = IVar18;
                }
                __ss18_CocoaArrayWrapperV8endIndexSivg();
                if ((long)uVar7 < 0) {
                    /* WARNING: Does not return */
                  pcVar5 = (code *)SoftwareBreakpoint(1,0x100842be8);
                  (*pcVar5)();
                }
              }
              if (((long)IVar25 < 0) || (uVar7 <= IVar25)) {
                _swift_bridgeObjectRelease(IVar18);
              }
              else {
                if ((IVar18 & 0xc000000000000001) == 0) {
                  if (*(ulong *)((IVar18 & 0xfffffffffffff8) + 0x10) <= IVar25) {
                    /* WARNING: Does not return */
                    pcVar5 = (code *)SoftwareBreakpoint(1,0x100842bf4);
                    (*pcVar5)();
                  }
                  IVar25 = *(ID *)(IVar18 + IVar25 * 8 + 0x20);
                }
                else {
                  FUN_1000cbedc(IVar25,IVar18);
                }
                _swift_bridgeObjectRelease(IVar18);
                FUN_100023404(0,&DAT_100af6c40,&PTR__OBJC_CLASS___NSObject_100aa3f30);
                uVar7 = local_340;
                __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(local_340,IVar25);
                if (((uVar7 & 1) != 0) && (*(ID *)(local_3b0[2] + local_3c0) != 0)) {
                  IVar18 = _objc_msgSend(*(ID *)(local_3b0[2] + local_3c0),"rootViewController");
                  if (IVar18 != 0) {
                    uVar11 = 0;
                    FUN_100413a94(0);
                    _swift_dynamicCastClass(IVar18,uVar11);
                    if ((IVar18 != 0) &&
                       (*(long *)(IVar18 + _TtC8Playback18MainViewController::waveformViewController
                                 ) != 0)) {
                      FUN_1005f025c(IVar25);
                    }
                  }
                  lVar8 = local_370;
                  if ((*(ID *)(local_3b0[2] + local_3c0) != 0) &&
                     (IVar18 = _objc_msgSend(*(ID *)(local_3b0[2] + local_3c0),"rootViewController")
                     , IVar18 != 0)) {
                    uVar11 = 0;
                    FUN_100413a94(0);
                    _swift_dynamicCastClass(IVar18,uVar11);
                    if ((IVar18 != 0) &&
                       (lVar8 = local_370,
                       *(long *)(IVar18 + _TtC8Playback18MainViewController::waveformViewController)
                       != 0)) {
                      FUN_1005ef7a4(IVar25);
                      lVar8 = local_370;
                    }
                  }
                }
              }
            }
            uVar7 = local_360;
          } while (local_360 != local_358);
          _swift_bridgeObjectRelease(local_368);
        }
      }
      if (local_398 != (code *)0x0) {
        (*local_398)(0);
      }
      if (local_390 != (code *)0x0) {
        (*local_390)();
      }
      FUN_1000233c8(lVar8,FUN_1002aa5c8);
      FUN_1000233c8(local_3b0[1],FUN_10068e908);
    }
  }
  return;
}

// ==== 100859c20 FUN_100859c20 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Type propagation algorithm not settling */

void FUN_100859c20(long param_1)

{
  undefined8 uVar1;
  char cVar2;
  short sVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  ID IVar6;
  ID IVar7;
  undefined1 uVar8;
  code *pcVar9;
  long lVar10;
  ID IVar11;
  ID IVar12;
  undefined *puVar13;
  undefined *puVar14;
  ID IVar15;
  ID IVar16;
  ID *pIVar17;
  ID *pIVar18;
  undefined *puVar19;
  undefined *puVar20;
  ulong uVar21;
  undefined *puVar22;
  long lVar23;
  undefined8 uVar24;
  long lVar25;
  ID unaff_x20;
  ID IVar26;
  undefined8 uVar27;
  ulong uVar28;
  undefined8 *puVar29;
  undefined *local_290;
  long local_280;
  ID local_230;
  ID IStack_228;
  ID IStack_220;
  ID IStack_218;
  ID local_210;
  ID IStack_208;
  ID IStack_200;
  ID IStack_1f8;
  ID local_1f0;
  ID IStack_1e8;
  undefined1 local_1e0;
  ID local_e0;
  ID IStack_d8;
  ID IStack_d0;
  undefined8 local_c8;
  ID local_c0;
  ID IStack_b8;
  ID local_b0;
  ID IStack_a8;
  ID local_a0;
  ID IStack_98;
  undefined1 local_90;
  
  lVar23 = _TtC8Playback4Song::privateSongMap;
  puVar14 = PTR___swiftEmptyArrayStorage_100a1e050;
  lVar10 = *(long *)(unaff_x20 + _TtC8Playback4Song::privateSongMap);
  lVar25 = lVar10;
  if (lVar10 == 0) {
    FUN_100861310();
    _swift_allocObject();
    *(undefined **)(lVar10 + 0x18) = puVar14;
    *(undefined8 *)(lVar10 + 0x28) = 0;
    *(undefined8 *)(lVar10 + 0x20) = 0;
    *(undefined8 *)(lVar10 + 0x38) = 0;
    *(undefined8 *)(lVar10 + 0x30) = 0;
    _swift_unknownObjectUnownedInit(lVar10 + 0x10);
    _swift_retain(puVar14);
    FUN_10085ee38();
    uVar24 = *(undefined8 *)(unaff_x20 + lVar23);
    *(long *)(unaff_x20 + lVar23) = lVar10;
    _swift_retain(lVar10);
    _swift_release(uVar24);
    lVar25 = 0;
  }
  uVar24 = *(undefined8 *)(lVar10 + 0x30);
  *(undefined8 *)(lVar10 + 0x30) = 0;
  _swift_retain(lVar25);
  _swift_release(lVar10);
  _swift_bridgeObjectRelease(uVar24);
  local_280 = *(long *)(param_1 + 0x10);
  if (local_280 == 0) {
    local_290 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
  }
  else {
    FUN_1000287b8(0);
    local_290 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    _swift_bridgeObjectRetain(param_1);
    lVar23 = 0x20;
    while( true ) {
      local_280 = local_280 + -1;
      pIVar17 = (ID *)(param_1 + lVar23);
      uVar28 = pIVar17[5];
      IVar15 = pIVar17[4];
      uVar21 = pIVar17[7];
      IVar16 = pIVar17[6];
      IStack_98 = pIVar17[9];
      local_a0 = pIVar17[8];
      local_90 = (undefined1)pIVar17[10];
      IStack_d8 = pIVar17[1];
      local_e0 = *pIVar17;
      local_c8 = pIVar17[3];
      IStack_d0 = pIVar17[2];
      sVar3 = (short)IStack_d8;
      lVar25 = (long)(short)IStack_d8;
      local_c0 = IVar15;
      IStack_b8 = uVar28;
      local_b0 = IVar16;
      IStack_a8 = uVar21;
      FUN_100450b04(&local_e0);
      FUN_100450b04(&local_e0);
      IVar26 = IVar15;
      IVar11 = uVar28;
      FUN_1006d7494(IVar15);
      if ((((IVar11 & 1) == 0) &&
          (IVar11 = IVar16, IVar12 = uVar21, FUN_1006d7494(IVar16), (IVar12 & 1) == 0)) &&
         (FUN_100430100(), uVar8 = local_90, IVar7 = IStack_98, IVar6 = local_a0, IVar12 = local_e0,
         lVar25 != 0)) {
        uVar28 = local_c8 & 0xff;
        uVar4 = local_c8._4_2_;
        uVar5 = local_c8._6_2_;
        _swift_bridgeObjectRetain(IStack_98);
        FUN_100027f64(IVar26,IVar26,IVar11,IVar12,lVar25,uVar28,uVar4,uVar5,uVar8,IVar6,IVar7);
        FUN_1007141a0(&local_e0);
        FUN_1007141a0(&local_e0);
        _objc_msgSend(IVar12,"setSong:",unaff_x20);
        puVar14 = local_290;
        _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
        if ((((int)puVar14 == 0) || ((long)local_290 < 0)) ||
           (puVar14 = local_290, ((ulong)local_290 >> 0x3e & 1) != 0)) {
          if ((ulong)local_290 >> 0x3e == 0) {
            puVar13 = *(undefined **)(((ulong)local_290 & 0xfffffffffffff8) + 0x10);
          }
          else {
            puVar13 = (undefined *)((ulong)local_290 & 0xffffffffffffff8);
            if ((long)local_290 < 0) {
              puVar13 = local_290;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg(puVar13);
          }
          puVar14 = (undefined *)0x0;
          FUN_1007900e0(0,puVar13 + 1,1,local_290);
        }
        uVar21 = (ulong)puVar14 & 0xffffffffffffff8;
        uVar28 = *(ulong *)(uVar21 + 0x10);
        local_290 = puVar14;
        if (*(ulong *)(uVar21 + 0x18) >> 1 <= uVar28) {
          local_290 = (undefined *)(ulong)(1 < *(ulong *)(uVar21 + 0x18));
          FUN_1007900e0(local_290,uVar28 + 1,1);
          uVar21 = (ulong)local_290 & 0xffffffffffffff8;
        }
        *(ulong *)(uVar21 + 0x10) = uVar28 + 1;
        *(ID *)(uVar21 + uVar28 * 8 + 0x20) = IVar12;
      }
      else {
        puVar14 = &DAT_100af53a0;
        FUN_100021774();
        _swift_initStackObject();
        *(undefined8 *)(puVar14 + 0x18) = 6;
        *(undefined8 *)(puVar14 + 0x10) = 3;
        puVar29 = (undefined8 *)(puVar14 + 0x20);
        *puVar29 = 0x65646f63656d6974;
        *(undefined8 *)(puVar14 + 0x28) = 0xe800000000000000;
        FUN_1006d7494();
        puVar13 = PTR___sSdN_100a1dd60;
        if ((uVar28 & 1) != 0) {
          IVar15 = 0;
          *(undefined8 *)(puVar14 + 0x38) = 0;
          *(undefined8 *)(puVar14 + 0x40) = 0;
          puVar13 = (undefined *)0x0;
        }
        *(ID *)(puVar14 + 0x30) = IVar15;
        *(undefined **)(puVar14 + 0x48) = puVar13;
        *(undefined8 *)(puVar14 + 0x50) = 0x6e6f697461727564;
        *(undefined8 *)(puVar14 + 0x58) = 0xe800000000000000;
        FUN_1006d7494();
        puVar13 = PTR___sSdN_100a1dd60;
        if ((uVar21 & 1) != 0) {
          IVar16 = 0;
          *(undefined8 *)(puVar14 + 0x68) = 0;
          *(undefined8 *)(puVar14 + 0x70) = 0;
          puVar13 = (undefined *)0x0;
        }
        *(ID *)(puVar14 + 0x60) = IVar16;
        *(undefined **)(puVar14 + 0x78) = puVar13;
        *(undefined8 *)(puVar14 + 0x80) = 0x737562;
        *(undefined8 *)(puVar14 + 0x88) = 0xe300000000000000;
        *(undefined **)(puVar14 + 0xa8) = PTR___ss5Int16VN_100a1def8;
        *(short *)(puVar14 + 0x90) = sVar3;
        FUN_1007141a0(&local_e0);
        puVar22 = puVar14;
        FUN_10079beb4(puVar14);
        _swift_setDeallocating(puVar14);
        puVar14 = &DAT_100af53a8;
        FUN_100021774(&DAT_100af53a8);
        _swift_arrayDestroy(puVar29,3,puVar14);
        __sSo13os_log_type_ta0A0E7defaultABvgZ();
        puVar14 = &DAT_100af52c8;
        FUN_100021774();
        _swift_initStackObject();
        *(undefined8 *)(puVar14 + 0x18) = 2;
        *(undefined8 *)(puVar14 + 0x10) = 1;
        IStack_208 = IStack_b8;
        local_210 = local_c0;
        IStack_1f8 = IStack_a8;
        IStack_200 = local_b0;
        IStack_1e8 = IStack_98;
        local_1f0 = local_a0;
        local_1e0 = local_90;
        IStack_228 = IStack_d8;
        local_230 = local_e0;
        IStack_218 = local_c8;
        IStack_220 = IStack_d0;
        pIVar17 = &local_230;
        puVar13 = &DAT_100a5e690;
        __sSS10describingSSx_tclufC();
        *(undefined **)(puVar14 + 0x38) = PTR___sSSN_100a1dce0;
        pIVar18 = pIVar17;
        FUN_100026528();
        *(ID **)(puVar14 + 0x40) = pIVar18;
        *(ID **)(puVar14 + 0x20) = pIVar17;
        *(undefined **)(puVar14 + 0x28) = puVar13;
        FUN_10041ac94(puVar29,0x59,"Failed to add midiEvent %{public}@",0x22,2,puVar14);
        _swift_setDeallocating(puVar14);
        FUN_100023468(puVar14 + 0x20);
        _swift_bridgeObjectRelease(puVar22);
      }
      if (local_280 == 0) break;
      lVar23 = lVar23 + 0x58;
    }
    _swift_bridgeObjectRelease(param_1);
  }
  if ((ulong)local_290 >> 0x3e == 0) {
    puVar22 = (undefined *)((ulong)local_290 & 0xfffffffffffff8);
    puVar14 = *(undefined **)(puVar22 + 0x10);
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    puVar14 = (undefined *)((ulong)local_290 & 0xffffffffffffff8);
    if ((long)local_290 < 0) {
      puVar14 = local_290;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar22 = local_290;
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar13;
  if (puVar14 == (undefined *)0x0) {
    puVar14 = puVar13;
    _swift_retain(puVar13);
    lVar23 = *(long *)(puVar13 + 0x10);
  }
  else {
    if ((long)puVar14 < 1) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x10085a510);
      (*pcVar9)();
    }
    _swift_bridgeObjectRetain_n(puVar22);
    puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    lVar23 = 0x20;
    lVar25 = _TtC8Playback9MIDIEvent::initializationError;
    do {
      puVar29 = (undefined8 *)(*(long *)(local_290 + lVar23) + lVar25);
      cVar2 = *(char *)(puVar29 + 3);
      if (cVar2 != -1) {
        uVar24 = *puVar29;
        uVar1 = puVar29[1];
        uVar27 = puVar29[2];
        FUN_100028ab4(uVar24,uVar1,uVar27,cVar2);
        puVar22 = puVar13;
        _swift_isUniquelyReferenced_nonNull_native();
        puVar19 = puVar13;
        if (((ulong)puVar22 & 1) == 0) {
          puVar19 = (undefined *)0x0;
          FUN_10078ffd8(0,*(long *)(puVar13 + 0x10) + 1,1,puVar13);
        }
        uVar28 = *(ulong *)(puVar19 + 0x10);
        puVar13 = puVar19;
        if (*(ulong *)(puVar19 + 0x18) >> 1 <= uVar28) {
          puVar13 = (undefined *)(ulong)(1 < *(ulong *)(puVar19 + 0x18));
          FUN_10078ffd8(puVar13,uVar28 + 1,1,puVar19);
        }
        *(ulong *)(puVar13 + 0x10) = uVar28 + 1;
        *(undefined8 *)(puVar13 + uVar28 * 0x20 + 0x20) = uVar24;
        *(undefined8 *)(puVar13 + uVar28 * 0x20 + 0x28) = uVar1;
        *(undefined8 *)(puVar13 + uVar28 * 0x20 + 0x30) = uVar27;
        puVar13[uVar28 * 0x20 + 0x38] = cVar2;
        lVar25 = _TtC8Playback9MIDIEvent::initializationError;
      }
      lVar23 = lVar23 + 8;
      puVar14 = puVar14 + -1;
    } while (puVar14 != (undefined *)0x0);
    puVar14 = local_290;
    _swift_bridgeObjectRelease_n(local_290,2);
    lVar23 = *(long *)(puVar13 + 0x10);
  }
  if (lVar23 == 0) {
    _swift_bridgeObjectRelease(puVar13);
  }
  else {
    __sSo13os_log_type_ta0A0E7defaultABvgZ();
    puVar22 = &DAT_100af52c8;
    FUN_100021774();
    _swift_initStackObject();
    *(undefined8 *)(puVar22 + 0x18) = 2;
    *(undefined8 *)(puVar22 + 0x10) = 1;
    IVar26 = *(ID *)(puVar13 + 0x10);
    _swift_bridgeObjectRelease(puVar13);
    puVar13 = PTR___sSiN_100a1dd88;
    puVar20 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
    local_e0 = IVar26;
    __ss23CustomStringConvertibleP11descriptionSSvgTj();
    *(undefined **)(puVar22 + 0x38) = PTR___sSSN_100a1dce0;
    puVar19 = puVar13;
    FUN_100026528();
    *(undefined **)(puVar22 + 0x40) = puVar19;
    *(undefined **)(puVar22 + 0x20) = puVar13;
    *(undefined **)(puVar22 + 0x28) = puVar20;
    FUN_10041ac94(puVar14,0x33,
                  "MIDI Event initialization failed for %@ event(s) due to API MIDI values being out of range"
                  ,0x5a,2,puVar22);
    _swift_setDeallocating(puVar22);
    FUN_100023468(puVar22 + 0x20);
  }
  puVar14 = local_290;
  FUN_1001c61b8(local_290);
  puVar22 = &_OBJC_CLASS___NSOrderedSet;
  _objc_allocWithZone();
  puVar13 = puVar14;
  __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar14,PTR___sypN_100a1e038 + 8);
  _swift_bridgeObjectRelease(puVar14);
  IVar26 = _objc_msgSend((ID)puVar22,"initWithArray:",puVar13);
  _objc_msgSend(unaff_x20,"setMidiEventsDefaultArrangement:",IVar26);
  puVar14 = (undefined *)0x0;
  FUN_100327470();
  if ((ulong)puVar14 >> 0x3e == 0) {
    puVar13 = *(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar13 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
    if ((long)puVar14 < 0) {
      puVar13 = puVar14;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar13 != (undefined *)0x0) {
    if ((long)puVar13 < 1) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x10085a514);
      (*pcVar9)();
    }
    _swift_bridgeObjectRetain(puVar14);
    puVar22 = (undefined *)0x0;
    do {
      if (((ulong)puVar14 & 0xc000000000000001) == 0) {
        puVar19 = *(undefined **)(puVar14 + (long)puVar22 * 8 + 0x20);
      }
      else {
        puVar19 = puVar22;
        FUN_1000cbedc(puVar22,puVar14);
      }
      lVar23 = _TtC8Playback4Song::privateSongMap;
      lVar10 = *(long *)(puVar19 + _TtC8Playback4Song::privateSongMap);
      lVar25 = lVar10;
      if (lVar10 == 0) {
        FUN_100861310();
        _swift_allocObject();
        puVar20 = PTR___swiftEmptyArrayStorage_100a1e050;
        *(undefined **)(lVar10 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
        *(undefined8 *)(lVar10 + 0x28) = 0;
        *(undefined8 *)(lVar10 + 0x20) = 0;
        *(undefined8 *)(lVar10 + 0x38) = 0;
        *(undefined8 *)(lVar10 + 0x30) = 0;
        _swift_unknownObjectUnownedInit(lVar10 + 0x10,puVar19);
        _swift_retain(puVar20);
        FUN_10085ee38();
        uVar24 = *(undefined8 *)(puVar19 + lVar23);
        *(long *)(puVar19 + lVar23) = lVar10;
        _swift_retain(lVar10);
        _swift_release(uVar24);
        lVar25 = 0;
      }
      puVar22 = puVar22 + 1;
      uVar24 = *(undefined8 *)(lVar10 + 0x30);
      *(undefined8 *)(lVar10 + 0x30) = 0;
      _swift_retain(lVar25);
      _swift_release(lVar10);
      _swift_bridgeObjectRelease(uVar24);
      FUN_1008593a0(0,0);
    } while (puVar13 != puVar22);
    _swift_bridgeObjectRelease(local_290);
    local_290 = puVar14;
  }
  _swift_bridgeObjectRelease(local_290);
  _swift_bridgeObjectRelease(puVar14);
  return;
}

// ==== 10085cea0 FUN_10085cea0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x00010085dec0) */

undefined * FUN_10085cea0(double param_1)

{
  double *pdVar1;
  long lVar2;
  code *pcVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  ulong uVar11;
  ID IVar12;
  ID IVar13;
  long lVar14;
  undefined1 *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  ulong uVar18;
  long lVar19;
  ulong uVar20;
  long lVar21;
  ulong uVar22;
  double *pdVar23;
  uint uVar24;
  long lVar25;
  long lVar26;
  long unaff_x20;
  code *pcVar27;
  ulong uVar28;
  ID IVar29;
  ulong uVar30;
  long lVar31;
  double dVar32;
  double dVar33;
  double dVar34;
  double dVar35;
  double dVar36;
  double dVar37;
  undefined1 auStack_1d0 [12];
  int local_1c4;
  long local_1c0;
  ulong local_1b8;
  int local_1ac;
  long local_1a8;
  ulong local_1a0;
  ulong local_198;
  int local_18c;
  ulong local_188;
  ulong local_180;
  ulong local_178;
  int local_16c;
  long local_168;
  long local_160;
  undefined1 *local_158;
  int local_14c;
  long local_148;
  long local_140;
  long local_138;
  long local_130;
  long local_128;
  long local_120;
  int local_114;
  double *local_110;
  undefined *local_b0 [2];
  
  lVar5 = 0;
  __ss25FloatingPointRoundingRuleOMa();
  lVar26 = *(long *)(lVar5 + -8);
  uVar18 = *(long *)(lVar26 + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_158 = auStack_1d0 + -uVar18;
  local_120 = (long)local_158 - uVar18;
  local_160 = local_120 - uVar18;
  local_128 = local_160 - uVar18;
  local_168 = local_128 - uVar18;
  lVar19 = local_168 - uVar18;
  puVar16 = &DAT_100af5490;
  local_130 = lVar19;
  FUN_100021774();
  uVar20 = *(long *)(*(long *)(puVar16 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar19 = lVar19 - uVar20;
  local_138 = (lVar19 - uVar20) - uVar20;
  lVar25 = local_138 - uVar20;
  lVar21 = (lVar25 - uVar20) - uVar20;
  _swift_unknownObjectUnownedLoadStrong(unaff_x20 + 0x10);
  FUN_1003220ec();
  uVar18 = *(ulong *)(unaff_x20 + 0x18);
  dVar35 = param_1;
  if (uVar18 >> 0x3e == 0) {
    uVar30 = *(ulong *)((uVar18 & 0xfffffffffffff8) + 0x10);
    puVar16 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    uVar30 = uVar18 & 0xffffffffffffff8;
    if ((long)uVar18 < 0) {
      uVar30 = uVar18;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar16 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar16;
  if (uVar30 == 0) {
    _swift_retain(puVar16);
  }
  else {
    local_180 = uVar18 & 0xc000000000000001;
    local_1b8 = uVar18 & 0xffffffffffffff8;
    local_1c0 = uVar18 + 0x20;
    local_114 = *(int *)
                 PTR___ss25FloatingPointRoundingRuleO23toNearestOrAwayFromZeroyA2BmFWC_100a1dea0;
    local_14c = *(int *)PTR___ss25FloatingPointRoundingRuleO15toNearestOrEvenyA2BmFWC_100a1de98;
    local_16c = *(int *)PTR___ss25FloatingPointRoundingRuleO2upyA2BmFWC_100a1dea8;
    local_18c = *(int *)PTR___ss25FloatingPointRoundingRuleO4downyA2BmFWC_100a1deb0;
    local_1ac = *(int *)PTR___ss25FloatingPointRoundingRuleO10towardZeroyA2BmFWC_100a1de88;
    local_1c4 = *(int *)PTR___ss25FloatingPointRoundingRuleO12awayFromZeroyA2BmFWC_100a1de90;
    local_140 = lVar25 - uVar20;
    _swift_retain(puVar16);
    _swift_bridgeObjectRetain(uVar18);
    uVar28 = 0;
    local_1a8 = lVar19;
    local_1a0 = uVar30;
    local_198 = uVar18;
    local_148 = lVar19 - uVar20;
    do {
      if (local_180 == 0) {
        if (*(ulong *)(local_1b8 + 0x10) <= uVar28) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x10085de14);
          (*pcVar3)();
        }
        uVar20 = *(ulong *)(local_1c0 + uVar28 * 8);
        _swift_retain();
        dVar32 = dVar35;
      }
      else {
        uVar20 = uVar28;
        FUN_1000cc314(uVar28,uVar18);
        dVar32 = dVar35;
      }
      if (SCARRY8(uVar28,1)) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x10085de0c);
        (*pcVar3)();
      }
      uVar28 = uVar28 + 1;
      uVar6 = uVar20;
      FUN_10085fc88();
      lVar2 = _TtCC8Playback7SongMap7Element::section;
      FUN_1000345bc(0);
      dVar35 = dVar32;
      if (uVar6 >> 0x3e == 0) {
        uVar7 = *(ulong *)((uVar6 & 0xfffffffffffff8) + 0x10);
        if (uVar7 == 0) goto LAB_10085dd88;
LAB_10085d1e0:
        if ((long)uVar7 < 1) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x10085de10);
          (*pcVar3)();
        }
        uVar18 = 0;
        pdVar1 = (double *)(uVar20 + _TtCC8Playback7SongMap7Element::trimTimelineStartTime);
        local_110 = (double *)(uVar20 + _TtCC8Playback7SongMap7Element::fullTimelineStartTime);
        uVar30 = uVar6 & 0xc000000000000001;
        local_178 = uVar28;
        do {
          if (uVar30 == 0) {
            uVar28 = *(ulong *)(uVar6 + uVar18 * 8 + 0x20);
            _swift_retain(uVar28);
          }
          else {
            uVar28 = uVar18;
            FUN_1000cc70c(uVar18,uVar6);
          }
          lVar10 = uVar28 + 0x58;
          _swift_unknownObjectWeakLoadStrong();
          if ((lVar10 == 0) || (*(char *)(lVar10 + _TtC8Playback9MIDIEvent::isNudging) != '\x01')) {
            dVar36 = *(double *)(uVar28 + 0x20);
            dVar35 = param_1 * dVar36;
            if (dVar35 < dVar32) {
              uVar11 = uVar20;
              FUN_10085ffc8();
              if (*(long *)(uVar11 + 0x10) != 0) {
                dVar36 = *(double *)(uVar11 + 0x28);
                _swift_bridgeObjectRelease();
                if (DAT_100adfbb8 != -1) {
                  _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
                }
                uVar24 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
                if ((uVar24 == 1) ||
                   (pdVar23 = pdVar1,
                   uVar24 == 2 && *(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)) {
                  pdVar23 = local_110;
                }
                dVar35 = param_1 * dVar36 - dVar35;
                dVar36 = *pdVar23 - dVar35;
                goto LAB_10085dcb0;
              }
              _swift_bridgeObjectRelease();
            }
            IVar29 = *(ID *)(uVar20 + lVar2);
            if (DAT_100adfbb8 != -1) {
              _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
            }
            uVar24 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
            if ((uVar24 == 1) ||
               (uVar24 == 2 && *(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)) {
              _objc_msgSend(IVar29,"startTimeOriginal");
              dVar33 = dVar36;
              IVar29 = _objc_msgSend(IVar29,"arrangement");
              dVar37 = 1.0;
              if ((IVar29 != 0) && (IVar29 = _objc_msgSend(IVar29,"song"), IVar29 != 0)) {
                IVar12 = _objc_msgSend(IVar29,"contentTypeID");
                uVar24 = (uint)IVar12;
                FUN_100419df0();
                if ((((uVar24 & 0xfe) != 0x10) && (_objc_msgSend(IVar29,"bpm"), 1.0 <= dVar33)) &&
                   (_objc_msgSend(IVar29,"bpmOriginal"), 1.0 <= dVar33)) {
                  _objc_msgSend(IVar29,"bpmOriginal");
                  dVar34 = dVar33;
                  _objc_msgSend(IVar29,"bpm");
                  dVar37 = 1.0;
                  if (dVar33 / dVar34 != 0.0) {
                    dVar37 = dVar33 / dVar34;
                  }
                }
              }
              (**(code **)(lVar26 + 0x38))(lVar21,1,1,lVar5);
              lVar10 = local_140;
              FUN_100214f00(lVar21,local_140);
              lVar14 = lVar10;
              (**(code **)(lVar26 + 0x30))(lVar10,1,lVar5);
              lVar31 = local_130;
              if ((int)lVar14 == 1) {
                FUN_1000f9e50(lVar10);
                puVar9 = (undefined *)(long)(dVar36 * dVar37 * 1000.0);
              }
              else {
                (**(code **)(lVar26 + 0x20))(local_130,lVar10,lVar5);
                lVar10 = local_168;
                puVar9 = (undefined *)(dVar36 * dVar37 * 1000.0);
                local_b0[0] = puVar9;
                (**(code **)(lVar26 + 0x10))(local_168,lVar31,lVar5);
                (**(code **)(lVar26 + 0x58))(lVar10,lVar5);
                iVar4 = (int)lVar10;
                if (iVar4 == local_114) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_14c) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_16c) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_18c) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_1ac) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_1c4) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else {
                  __sSd14_roundSlowPathyys25FloatingPointRoundingRuleOF(local_130);
                  (**(code **)(lVar26 + 8))(local_168,lVar5);
                  puVar9 = local_b0[0];
                }
                (**(code **)(lVar26 + 8))(local_130,lVar5);
              }
              dVar36 = (double)puVar9 / 1000.0;
              FUN_1000f9e50(lVar21);
            }
            else {
              _objc_msgSend(IVar29,"startTimeOriginal");
              dVar33 = dVar36;
              IVar12 = _objc_msgSend(IVar29,"arrangement");
              dVar37 = 1.0;
              lVar10 = local_138;
              if ((IVar12 != 0) &&
                 (IVar12 = _objc_msgSend(IVar12,"song"), lVar10 = local_138, IVar12 != 0)) {
                IVar13 = _objc_msgSend(IVar12,"contentTypeID");
                uVar24 = (uint)IVar13;
                FUN_100419df0();
                lVar10 = local_138;
                if (((uVar24 & 0xfe) != 0x10) &&
                   ((_objc_msgSend(IVar12,"bpm"), 1.0 <= dVar33 &&
                    (_objc_msgSend(IVar12,"bpmOriginal"), 1.0 <= dVar33)))) {
                  _objc_msgSend(IVar12,"bpmOriginal");
                  dVar34 = dVar33;
                  _objc_msgSend(IVar12,"bpm");
                  dVar37 = 1.0;
                  if (dVar33 / dVar34 != 0.0) {
                    dVar37 = dVar33 / dVar34;
                  }
                }
              }
              pcVar3 = *(code **)(lVar26 + 0x38);
              (*pcVar3)(lVar25,1,1,lVar5);
              FUN_100214f00(lVar25,lVar10);
              pcVar27 = *(code **)(lVar26 + 0x30);
              lVar14 = lVar10;
              (*pcVar27)(lVar10,1,lVar5);
              lVar31 = local_128;
              if ((int)lVar14 == 1) {
                FUN_1000f9e50(lVar10);
                dVar33 = dVar36 * dVar37 * 1000.0;
                puVar9 = (undefined *)(long)dVar33;
                lVar31 = local_148;
              }
              else {
                (**(code **)(lVar26 + 0x20))(local_128,lVar10,lVar5);
                lVar10 = local_160;
                dVar33 = 1000.0;
                puVar9 = (undefined *)(dVar36 * dVar37 * 1000.0);
                local_b0[0] = puVar9;
                (**(code **)(lVar26 + 0x10))(local_160,lVar31,lVar5);
                (**(code **)(lVar26 + 0x58))(lVar10,lVar5);
                lVar31 = local_148;
                iVar4 = (int)lVar10;
                if ((((iVar4 == local_114) || (iVar4 == local_14c)) || (iVar4 == local_16c)) ||
                   (iVar4 == local_18c)) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_1ac) {
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else if (iVar4 == local_1c4) {
                  dVar33 = (double)(long)(double)puVar9;
                  puVar9 = (undefined *)(long)(double)puVar9;
                }
                else {
                  __sSd14_roundSlowPathyys25FloatingPointRoundingRuleOF(local_128);
                  (**(code **)(lVar26 + 8))(local_160,lVar5);
                  puVar9 = local_b0[0];
                }
                (**(code **)(lVar26 + 8))(local_128,lVar5);
              }
              FUN_1000f9e50(lVar25);
              _objc_msgSend(IVar29,"storedStartTimeTrimOffset");
              dVar36 = dVar33;
              IVar29 = _objc_msgSend(IVar29,"arrangement");
              dVar37 = 1.0;
              if ((IVar29 != 0) && (IVar29 = _objc_msgSend(IVar29,"song"), IVar29 != 0)) {
                IVar12 = _objc_msgSend(IVar29,"contentTypeID");
                uVar24 = (uint)IVar12;
                FUN_100419df0();
                if (((uVar24 & 0xfe) != 0x10) &&
                   ((_objc_msgSend(IVar29,"bpm"), 1.0 <= dVar36 &&
                    (local_188 = uVar6, _objc_msgSend(IVar29,"bpmOriginal"), uVar6 = local_188,
                    lVar19 = local_1a8, 1.0 <= dVar36)))) {
                  _objc_msgSend(IVar29,"bpmOriginal");
                  dVar34 = dVar36;
                  _objc_msgSend(IVar29,"bpm");
                  uVar6 = local_188;
                  lVar19 = local_1a8;
                  dVar37 = 1.0;
                  if (dVar36 / dVar34 != 0.0) {
                    dVar37 = dVar36 / dVar34;
                  }
                }
              }
              (*pcVar3)(lVar31,1,1,lVar5);
              FUN_100214f00(lVar31,lVar19);
              lVar14 = lVar19;
              (*pcVar27)(lVar19,1,lVar5);
              lVar10 = local_120;
              if ((int)lVar14 == 1) {
                FUN_1000f9e50(lVar19);
                puVar8 = (undefined *)(long)(dVar33 * dVar37 * 1000.0);
              }
              else {
                (**(code **)(lVar26 + 0x20))(local_120,lVar19,lVar5);
                puVar15 = local_158;
                puVar8 = (undefined *)(dVar33 * dVar37 * 1000.0);
                local_b0[0] = puVar8;
                (**(code **)(lVar26 + 0x10))(local_158,lVar10,lVar5);
                (**(code **)(lVar26 + 0x58))(puVar15,lVar5);
                iVar4 = (int)puVar15;
                if (iVar4 == local_114) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else if (iVar4 == local_14c) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else if (iVar4 == local_16c) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else if (iVar4 == local_18c) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else if (iVar4 == local_1ac) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else if (iVar4 == local_1c4) {
                  puVar8 = (undefined *)(long)(double)puVar8;
                }
                else {
                  __sSd14_roundSlowPathyys25FloatingPointRoundingRuleOF(local_120);
                  (**(code **)(lVar26 + 8))(local_158,lVar5);
                  puVar8 = local_b0[0];
                }
                (**(code **)(lVar26 + 8))(local_120,lVar5);
              }
              FUN_1000f9e50(lVar31);
              dVar36 = (double)puVar9 / 1000.0 + (double)puVar8 / 1000.0;
            }
            uVar24 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
            if ((uVar24 == 1) ||
               ((pdVar23 = pdVar1, uVar24 == 2 &&
                (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
              pdVar23 = local_110;
            }
            dVar35 = dVar35 - dVar36;
            dVar36 = dVar35 + *pdVar23;
          }
          else {
            dVar36 = *(double *)(uVar28 + 0x28);
          }
LAB_10085dcb0:
          if (0.0 <= dVar36) {
            dVar35 = param_1 * *(double *)(uVar28 + 0x30);
            *(double *)(uVar28 + 0x28) = dVar36;
            *(double *)(uVar28 + 0x30) = dVar35;
            IVar29 = uVar28 + 0x58;
            _swift_unknownObjectWeakLoadStrong();
            if (IVar29 != 0) {
              _objc_msgSend(IVar29,"setSequenceTimecode:");
              dVar35 = dVar36;
            }
            _swift_retain(uVar28);
            puVar9 = puVar16;
            _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
            if ((((int)puVar9 == 0) || ((long)puVar16 < 0)) ||
               (puVar9 = puVar16, ((ulong)puVar16 >> 0x3e & 1) != 0)) {
              if ((ulong)puVar16 >> 0x3e == 0) {
                puVar8 = *(undefined **)(((ulong)puVar16 & 0xfffffffffffff8) + 0x10);
              }
              else {
                puVar8 = (undefined *)((ulong)puVar16 & 0xffffffffffffff8);
                if ((long)puVar16 < 0) {
                  puVar8 = puVar16;
                }
                __ss18_CocoaArrayWrapperV8endIndexSivg(puVar8);
              }
              puVar9 = (undefined *)0x0;
              FUN_10078e3e0(0,puVar8 + 1,1,puVar16);
            }
            uVar22 = (ulong)puVar9 & 0xffffffffffffff8;
            uVar11 = *(ulong *)(uVar22 + 0x10);
            puVar16 = puVar9;
            if (*(ulong *)(uVar22 + 0x18) >> 1 <= uVar11) {
              puVar16 = (undefined *)(ulong)(1 < *(ulong *)(uVar22 + 0x18));
              FUN_10078e3e0(puVar16,uVar11 + 1,1,puVar9);
              uVar22 = (ulong)puVar16 & 0xffffffffffffff8;
            }
            *(ulong *)(uVar22 + 0x10) = uVar11 + 1;
            *(ulong *)(uVar22 + uVar11 * 8 + 0x20) = uVar28;
          }
          uVar18 = uVar18 + 1;
          _swift_release(uVar28);
        } while (uVar7 != uVar18);
        _swift_release(uVar20);
        uVar18 = local_198;
        uVar28 = local_178;
        uVar30 = local_1a0;
      }
      else {
        uVar7 = uVar6 & 0xffffffffffffff8;
        if ((long)uVar6 < 0) {
          uVar7 = uVar6;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        if (uVar7 != 0) goto LAB_10085d1e0;
LAB_10085dd88:
        _swift_release(uVar20);
      }
      _swift_bridgeObjectRelease(uVar6);
    } while (uVar28 != uVar30);
    _swift_bridgeObjectRelease(uVar18);
  }
  if ((ulong)puVar16 >> 0x3e == 0) {
    puVar8 = (undefined *)((ulong)puVar16 & 0xffffffffffffff8);
    _swift_bridgeObjectRetain_n(puVar16,2);
  }
  else {
    puVar9 = (undefined *)((ulong)puVar16 & 0xffffffffffffff8);
    if ((long)puVar16 < 0) {
      puVar9 = puVar16;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
    if (puVar9 == (undefined *)0x0) {
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      _swift_bridgeObjectRetain(puVar16);
    }
    else {
      puVar8 = puVar9;
      FUN_10078d948();
      _swift_bridgeObjectRetain_n(puVar16,3);
      puVar17 = puVar16;
      FUN_1005daf6c(puVar8 + 0x20,puVar9);
      _swift_bridgeObjectRelease();
      if (puVar17 != puVar9) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x10085dec0);
        (*pcVar3)();
      }
      _swift_bridgeObjectRelease(puVar16);
    }
  }
  local_b0[0] = puVar8;
  FUN_10085c0ac(local_b0);
  _swift_bridgeObjectRelease_n(puVar16,2);
  return local_b0[0];
}

// ==== 10086a1c0 FUN_10086a1c0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_10086a1c0(uint param_1)

{
  code *pcVar1;
  long lVar2;
  ID IVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  ID IVar7;
  long unaff_x20;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  
  if (DAT_100adeca8 != -1) {
    _swift_once(&DAT_100adeca8,FUN_100224b00);
  }
  lVar2 = *(long *)(DAT_100b75a80 + 0x10);
  if ((lVar2 != 0) && (FUN_1004a9df0(), lVar2 != 0)) {
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar8 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar8 != 0) {
      _swift_retain(lVar8);
      FUN_1004f5388(0);
      _swift_release(lVar8);
    }
    FUN_100870798();
    if (*(char *)(lVar2 + _TtC8Playback4Song::isLiveCrossfading) == '\x01') {
      *(undefined1 *)(lVar2 + _TtC8Playback4Song::isLiveCrossfading) = 0;
    }
    lVar8 = _TtC8Playback23TransportViewController::fadeButton;
    IVar3 = unaff_x20 + _TtC8Playback23TransportViewController::fadeButton;
    _swift_unknownObjectWeakLoadStrong();
    if ((IVar3 != 0) && (IVar3 = _objc_msgSend(IVar3,"isSelected"), (int)IVar3 != 0)) {
      IVar3 = unaff_x20 + lVar8;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar3 != 0) {
        _objc_msgSend(IVar3,"setSelected:",0);
      }
      FUN_100867240();
      if ((*(long *)(DAT_100b75e40 + 0x20) != 0) &&
         (lVar8 = *(long *)(*(long *)(DAT_100b75e40 + 0x20) + _TtC8Playback9Sequencer::channelGroup)
         , lVar8 != 0)) {
        _swift_retain(lVar8);
        FUN_100647c80(0,0,0,param_1 & 1);
        _swift_release(lVar8);
      }
    }
    lVar8 = _TtC8Playback4Song::privateSongMap;
    lVar4 = *(long *)(lVar2 + _TtC8Playback4Song::privateSongMap);
    lVar12 = lVar4;
    if (lVar4 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar4 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar4 + 0x28) = 0;
      *(undefined8 *)(lVar4 + 0x20) = 0;
      *(undefined8 *)(lVar4 + 0x38) = 0;
      *(undefined8 *)(lVar4 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar4 + 0x10,lVar2);
      _swift_retain(puVar5);
      FUN_10085ee38();
      uVar6 = *(undefined8 *)(lVar2 + lVar8);
      *(long *)(lVar2 + lVar8) = lVar4;
      _swift_retain(lVar4);
      _swift_release(uVar6);
      lVar12 = 0;
    }
    uVar9 = *(ulong *)(lVar4 + 0x18);
    _swift_retain(lVar12);
    _swift_bridgeObjectRetain(uVar9);
    _swift_release(lVar4);
    if (uVar9 >> 0x3e == 0) {
      uVar10 = *(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar10 = uVar9 & 0xffffffffffffff8;
      if ((long)uVar9 < 0) {
        uVar10 = uVar9;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar10 != 0) {
      if ((long)uVar10 < 1) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1,0x10086a760);
        (*pcVar1)();
      }
      _swift_bridgeObjectRetain(uVar9);
      uVar11 = 0;
      do {
        if ((uVar9 & 0xc000000000000001) == 0) {
          uVar13 = *(ulong *)(uVar9 + uVar11 * 8 + 0x20);
          _swift_retain(uVar13);
        }
        else {
          uVar13 = uVar11;
          FUN_1000cc314(uVar11,uVar9);
        }
        uVar11 = uVar11 + 1;
        *(undefined8 *)(uVar13 + _TtCC8Playback7SongMap7Element::liveLoopCount) = 0;
        IVar3 = _objc_msgSend(*(ID *)(uVar13 + _TtCC8Playback7SongMap7Element::section),
                              "presetInfiniteLoop");
        *(char *)(uVar13 + _TtCC8Playback7SongMap7Element::privateInfiniteLoop) = (char)IVar3;
        _swift_release(uVar13);
      } while (uVar10 != uVar11);
      _swift_bridgeObjectRelease(uVar9);
    }
    _swift_bridgeObjectRelease(uVar9);
    lVar2 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar2 != 0) {
      _swift_retain(lVar2);
      FUN_1004f1918();
      _swift_release(lVar2);
    }
    lVar2 = DAT_100b75e40;
    if (*(long *)(DAT_100b75e40 + 0x28) != 0) {
      _swift_retain(DAT_100b75e40);
      FUN_1002c4ea4(1);
      _swift_release(lVar2);
    }
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar9 = DAT_100b757a8;
    FUN_100170630();
    if ((((((uVar9 & 1) != 0) &&
          (uVar9 = DAT_100b757a8, FUN_1001736c4(),
          lVar2 = _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading, (uVar9 & 1) == 0)) &&
         (*(long *)(DAT_100b75e40 + 0x18) != 0)) &&
        ((lVar8 = *(long *)(*(long *)(DAT_100b75e40 + 0x18) + 0x18), lVar8 != 0 &&
         (lVar12 = *(long *)(lVar8 + _TtC8Playback16SongChannelGroup::midiOutChannel), lVar12 != 0))
        )) && (((*(byte *)(lVar12 + 0x40) & 1) == 0 &&
               (lVar4 = *(long *)(lVar12 + 0x38),
               *(char *)(lVar4 + _TtC8Playback18MIDIOutAVAudioUnit::isCrossfading) == '\x01')))) {
      *(undefined1 *)(lVar12 + 0x40) = 1;
      *(undefined1 *)(lVar4 + _TtC8Playback18MIDIOutAVAudioUnit::isEnabled) = 1;
      _swift_retain(lVar8);
      _swift_retain(lVar12);
      FUN_10049ffc8();
      _swift_release(lVar12);
      _swift_release(lVar8);
      *(undefined1 *)(lVar4 + lVar2) = 0;
    }
    puVar5 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar3 = _objc_msgSend((ID)puVar5,"sharedApplication");
    IVar3 = _objc_msgSend(IVar3,"delegate");
    if (IVar3 != 0) {
      uVar6 = 0;
      FUN_100842dec(0);
      IVar7 = IVar3;
      _swift_dynamicCastClass(IVar3,uVar6);
      if (((IVar7 == 0) || (*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar7 = _objc_msgSend(*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window),
                                "rootViewController"), IVar7 == 0)) {
        _swift_unknownObjectRelease(IVar3);
        return IVar3;
      }
      uVar6 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar7,uVar6);
      if (IVar7 == 0) {
        _swift_unknownObjectRelease(IVar3);
      }
      else {
        _swift_unknownObjectRelease(IVar3);
        FUN_10009cf18();
      }
    }
    return 0;
  }
  return 0;
}

