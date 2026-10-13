// Playback main executable sha256 2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423
// Ghidra 12.1.4 decompiler output, feature "meters": functions whose pseudocode matches /VUMeter|vuMeter|[Pp]eakLevel|meterLevel|MeterStart|meterStartDate|averagePower|peakPower|[Mm]etering/
// Addresses are image-relative VM addresses as exported (e.g. 100545a98).

// ==== 10024d89c _TtC8Playback19MixerViewController::leftVUMeter ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback19MixerViewController::leftVUMeter(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + leftVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 10024d8bc _TtC8Playback19MixerViewController::setLeftVUMeter: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback19MixerViewController::setLeftVUMeter_(ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + leftVUMeter,param_3);
  return;
}

// ==== 10024d8d0 _TtC8Playback19MixerViewController::rightVUMeter ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback19MixerViewController::rightVUMeter(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + rightVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 10024d8f0 _TtC8Playback19MixerViewController::setRightVUMeter: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback19MixerViewController::setRightVUMeter_(ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + rightVUMeter,param_3);
  return;
}

// ==== 1002500a8 FUN_1002500a8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8
FUN_1002500a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  undefined1 uVar2;
  long lVar3;
  code *pcVar4;
  uint uVar5;
  ID IVar6;
  long lVar7;
  undefined *puVar8;
  ID IVar9;
  ID IVar10;
  ulong uVar11;
  undefined8 uVar12;
  ulong uVar13;
  undefined *puVar14;
  undefined *puVar15;
  ulong uVar16;
  ID unaff_x20;
  long lVar17;
  ulong uVar18;
  ulong uVar19;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff70,"viewDidLoad");
  if (DAT_100adfbd0 != -1) {
    _swift_once(&DAT_100adfbd0,FUN_1005d0614);
  }
  lVar7 = DAT_100b77550;
  *(undefined ***)(DAT_100b77550 + 0x28) = &PTR_PTR_100a63c70;
  _swift_unknownObjectWeakAssign(lVar7 + 0x20);
  IVar6 = _objc_msgSend(unaff_x20,"view");
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c0c);
    (*pcVar4)();
  }
  _objc_msgSend(IVar6,"setMultipleTouchEnabled:",0);
  lVar7 = *(long *)(unaff_x20 + _TtC8Playback19MixerViewController::currentSetlist);
  if ((lVar7 != 0) && (FUN_1004a9df0(), lVar7 != 0)) {
    uVar2 = *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentMixerMode);
    *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentMixerMode) = 0;
    FUN_10024daa4(uVar2);
  }
  lVar7 = _TtC8Playback19MixerViewController::tracksCollectionView;
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::tracksCollectionView;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar6 != 0) && (IVar6 = _objc_msgSend(IVar6,"collectionViewLayout"), IVar6 != 0)) {
    puVar8 = &_OBJC_CLASS___UICollectionViewFlowLayout;
    _swift_getInitializedObjCClass(&_OBJC_CLASS___UICollectionViewFlowLayout);
    _swift_dynamicCastObjCClass(IVar6,puVar8);
    if (IVar6 != 0) {
      param_1 = 0;
      _objc_msgSend(IVar6,"setMinimumInteritemSpacing:",0);
    }
  }
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    if (DAT_100adff10 != -1) {
      _swift_once(&DAT_100adff10,FUN_1007c0580);
    }
    _objc_msgSend(IVar6,"setBackgroundColor:",DAT_100b77c78);
  }
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    puVar8 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    IVar9 = _objc_msgSend((ID)puVar8,"currentDevice");
    FUN_100826670(IVar9);
    IVar10 = _objc_msgSend(unaff_x20,"view");
    FUN_100250c2c(IVar10,IVar9);
    _objc_msgSend(IVar6,"setContentInset:",param_1,param_2,param_3,param_4);
  }
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    IVar6 = _objc_msgSend(IVar6,"collectionViewLayout");
    _objc_msgSend(IVar6,"invalidateLayout");
  }
  puVar8 = &_OBJC_CLASS___UIPanGestureRecognizer;
  _objc_allocWithZone();
  IVar9 = _objc_msgSend((ID)puVar8,"initWithTarget:action:");
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar6 == 0) || (uVar11 = _objc_msgSend(IVar6,"gestureRecognizers"), uVar11 == 0))
  goto LAB_1002505f4;
  uVar12 = 0;
  FUN_100023404(0,&DAT_100af7868,&PTR__OBJC_CLASS___UIGestureRecognizer_100aa3fa8);
  __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar11,uVar12);
  if (uVar11 >> 0x3e == 0) {
    uVar18 = *(ulong *)((uVar11 & 0xfffffffffffff8) + 0x10);
    if (uVar18 == 0) goto LAB_10025055c;
LAB_1002503e4:
    puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
    if ((long)uVar18 < 1) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c04);
      (*pcVar4)();
    }
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    _swift_bridgeObjectRetain(uVar11);
    uVar19 = 0;
    do {
      if ((uVar11 & 0xc000000000000001) == 0) {
        uVar13 = *(ulong *)(uVar11 + uVar19 * 8 + 0x20);
      }
      else {
        uVar13 = uVar19;
        FUN_1000cd068(uVar19,uVar11);
      }
      puVar14 = &_OBJC_CLASS___UIPanGestureRecognizer;
      _swift_getInitializedObjCClass(&_OBJC_CLASS___UIPanGestureRecognizer);
      _swift_dynamicCastObjCClass(uVar13,puVar14);
      if (uVar13 != 0) {
        puVar14 = puVar8;
        _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
        if ((((int)puVar14 == 0) || ((long)puVar8 < 0)) ||
           (puVar14 = puVar8, ((ulong)puVar8 >> 0x3e & 1) != 0)) {
          if ((ulong)puVar8 >> 0x3e == 0) {
            puVar15 = *(undefined **)(((ulong)puVar8 & 0xfffffffffffff8) + 0x10);
          }
          else {
            puVar15 = (undefined *)((ulong)puVar8 & 0xffffffffffffff8);
            if ((long)puVar8 < 0) {
              puVar15 = puVar8;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg(puVar15);
          }
          puVar14 = (undefined *)0x0;
          FUN_10079139c(0,puVar15 + 1,1,puVar8);
        }
        uVar16 = (ulong)puVar14 & 0xffffffffffffff8;
        uVar1 = *(ulong *)(uVar16 + 0x10);
        puVar8 = puVar14;
        if (*(ulong *)(uVar16 + 0x18) >> 1 <= uVar1) {
          puVar8 = (undefined *)(ulong)(1 < *(ulong *)(uVar16 + 0x18));
          FUN_10079139c(puVar8,uVar1 + 1,1,puVar14);
          uVar16 = (ulong)puVar8 & 0xffffffffffffff8;
        }
        *(ulong *)(uVar16 + 0x10) = uVar1 + 1;
        *(ulong *)(uVar16 + uVar1 * 8 + 0x20) = uVar13;
      }
      uVar19 = uVar19 + 1;
    } while (uVar18 != uVar19);
    _swift_bridgeObjectRelease(uVar11);
  }
  else {
    uVar18 = uVar11 & 0xffffffffffffff8;
    if ((long)uVar11 < 0) {
      uVar18 = uVar11;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (uVar18 != 0) goto LAB_1002503e4;
LAB_10025055c:
    puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  _swift_bridgeObjectRelease(uVar11);
  if ((ulong)puVar8 >> 0x3e == 0) {
    puVar14 = *(undefined **)(((ulong)puVar8 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar14 = (undefined *)((ulong)puVar8 & 0xffffffffffffff8);
    if ((long)puVar8 < 0) {
      puVar14 = puVar8;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar14 == (undefined *)0x0) {
    _swift_bridgeObjectRelease(puVar8);
  }
  else {
    if ((long)puVar14 < 1) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c08);
      (*pcVar4)();
    }
    _swift_bridgeObjectRetain(puVar8);
    lVar17 = 0x20;
    do {
      _objc_msgSend(IVar9,"requireGestureRecognizerToFail:",*(undefined8 *)(puVar8 + lVar17));
      lVar17 = lVar17 + 8;
      puVar14 = puVar14 + -1;
    } while (puVar14 != (undefined *)0x0);
    _swift_bridgeObjectRelease_n(puVar8,2);
  }
LAB_1002505f4:
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"addGestureRecognizer:",IVar9);
  }
  _swift_unknownObjectWeakLoadStrong();
  lVar7 = _TtC8Playback19MixerViewController::masterFaderLabel;
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::masterFaderLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    puVar8 = &_OBJC_CLASS___UIFont;
    _swift_getInitializedObjCClass();
    if (DAT_100adea78 != -1) {
      _swift_once(&DAT_100adea78,FUN_1001beae0);
    }
    IVar9 = _objc_msgSend((ID)puVar8,"systemFontOfSize:",DAT_100b75850);
    _objc_msgSend(IVar6,"setFont:",IVar9);
  }
  puVar8 = &_OBJC_CLASS___UITapGestureRecognizer;
  _objc_allocWithZone();
  IVar9 = _objc_msgSend((ID)puVar8,"initWithTarget:action:");
  _objc_msgSend(IVar9,"setNumberOfTapsRequired:",3);
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"addGestureRecognizer:",IVar9);
  }
  FUN_1002996cc();
  puVar8 = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar9 = _objc_msgSend((ID)puVar8,"currentDevice");
  FUN_100826670(IVar9);
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::modeButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c10);
    (*pcVar4)();
  }
  uVar5 = (uint)(((uint)IVar9 & 0xff) < 0x1b) & 0x4000fa0U >> (ulong)((uint)IVar9 & 0x1f);
  _objc_msgSend(IVar6,"setHidden:",(ulong)uVar5);
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::modePageControl;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c14);
    (*pcVar4)();
  }
  _objc_msgSend(IVar6,"setHidden:",(ulong)uVar5);
  lVar7 = _TtC8Playback19MixerViewController::modeMultiControlContainerView;
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::modeMultiControlContainerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c18);
    (*pcVar4)();
  }
  _objc_msgSend(IVar6,"setHidden:",(ulong)(uVar5 ^ 1));
  IVar6 = unaff_x20 + lVar7;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c1c);
    (*pcVar4)();
  }
  puVar14 = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar9 = _objc_msgSend((ID)puVar14,"clearColor");
  _objc_msgSend(IVar6,"setBackgroundColor:",IVar9);
  IVar6 = _objc_msgSend((ID)puVar8,"currentDevice");
  uVar5 = (uint)IVar6;
  FUN_100826670();
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::masterPanelButtonStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    uVar12 = 0x4028000000000000;
    if ((uVar5 & 0xff) != 0x1a) {
      uVar12 = 0x4024000000000000;
    }
    _objc_msgSend(IVar6,"setSpacing:",uVar12);
  }
  lVar17 = _TtC8Playback19MixerViewController::singleLoopButton;
  lVar7 = unaff_x20 + _TtC8Playback19MixerViewController::singleLoopButton;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar7 != 0) {
    lVar7 = lVar7 + _TtC8Playback15MixerLoopButton::delegate;
    *(undefined ***)(lVar7 + 8) = &PTR_PTR_100a63be8;
    _swift_unknownObjectWeakAssign(lVar7);
  }
  lVar3 = _TtC8Playback19MixerViewController::infiniteLoopButton;
  lVar7 = unaff_x20 + _TtC8Playback19MixerViewController::infiniteLoopButton;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar7 != 0) {
    lVar7 = lVar7 + _TtC8Playback15MixerLoopButton::delegate;
    *(undefined ***)(lVar7 + 8) = &PTR_PTR_100a63be8;
    _swift_unknownObjectWeakAssign(lVar7);
  }
  IVar6 = unaff_x20 + lVar17;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c20);
    (*pcVar4)();
  }
  IVar6 = _objc_msgSend(IVar6,"isEnabled");
  if ((IVar6 & 1) == 0) {
    IVar6 = unaff_x20 + lVar17;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar6 == 0) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c28);
      (*pcVar4)();
    }
    _objc_msgSend(IVar6,"setSelected:",0);
  }
  IVar6 = unaff_x20 + lVar3;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c24);
    (*pcVar4)();
  }
  IVar6 = _objc_msgSend(IVar6,"isEnabled");
  if ((IVar6 & 1) == 0) {
    IVar6 = unaff_x20 + lVar3;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar6 == 0) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(1,0x100250c2c);
      (*pcVar4)();
    }
    _objc_msgSend(IVar6,"setSelected:",0);
  }
  lVar17 = _TtC8Playback19MixerViewController::muteMIDIButton;
  lVar7 = unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButton;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar7 != 0) {
    lVar7 = lVar7 + _TtC8Playback19MixerMuteMIDIButton::delegate;
    *(undefined ***)(lVar7 + 8) = &PTR_PTR_100a63bf8;
    _swift_unknownObjectWeakAssign(lVar7);
  }
  IVar6 = unaff_x20 + lVar17;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar12 = DAT_100b757a8;
    FUN_1001736c4(DAT_100b757a8);
    _objc_msgSend(IVar6,"setSelected:",(ulong)((uint)uVar12 & 1));
  }
  lVar7 = unaff_x20 + _TtC8Playback19MixerViewController::leftVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar7 != 0) {
    FUN_1007f6c90(0,1);
  }
  lVar7 = unaff_x20 + _TtC8Playback19MixerViewController::rightVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar7 != 0) {
    FUN_1007f6c90(0,1);
  }
  FUN_100250d74();
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelContainerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setHidden:",1);
  }
  if ((*(long *)(unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelViewController) != 0)
     && (lVar7 = *(long *)(*(long *)(unaff_x20 +
                                    _TtC8Playback19MixerViewController::mixerPadPanelViewController)
                          + _TtC8Playback27MixerPadPanelViewController::selectedPad), lVar7 != 0)) {
    FUN_1001cbc9c(lVar7);
  }
  IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::padPanelContainerViewLeftConstraint;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setPriority:",0x4479c000);
  }
  FUN_10025160c();
  return 0;
}

// ==== 100250d74 FUN_100250d74 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_100250d74(undefined8 param_1)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  ID IVar11;
  undefined8 uVar12;
  long lVar13;
  undefined *puVar14;
  undefined8 *puVar15;
  ID self;
  ID IVar16;
  long lVar17;
  undefined8 uVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  long lVar22;
  long unaff_x20;
  long lVar23;
  long lVar24;
  undefined1 auStack_150 [8];
  undefined *local_148;
  undefined *local_140;
  undefined8 local_138;
  undefined *local_130;
  undefined8 local_128;
  undefined8 local_120;
  long local_118;
  undefined4 local_10c;
  undefined1 *local_108;
  long lStack_100;
  long local_f8;
  long local_f0;
  long local_e8;
  long local_e0;
  long lStack_d8;
  long local_d0;
  long lStack_c8;
  long local_c0;
  long local_b8;
  long local_b0;
  undefined *local_88;
  undefined8 local_80;
  
  lVar8 = 0;
  __sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyOMa();
  lVar24 = *(long *)(lVar8 + -8);
  lVar19 = *(long *)(lVar24 + 0x40);
  lVar9 = 0;
  __sSo17OS_dispatch_queueC8DispatchE10AttributesVMa();
  lVar20 = (long)(auStack_150 + -(lVar19 + 0xfU & 0xfffffffffffffff0)) -
           (*(long *)(*(long *)(lVar9 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar10 = 0;
  local_d0 = lVar20;
  lStack_c8 = lVar9;
  __s8Dispatch0A3QoSVMa();
  lVar20 = lVar20 - (*(long *)(*(long *)(lVar10 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar9 = 0;
  local_b8 = lVar20;
  __s10Foundation4UUIDVMa();
  local_e0 = *(long *)(lVar9 + -8);
  lVar20 = lVar20 - (*(long *)(local_e0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar10 = 0;
  local_e8 = lVar20;
  lStack_d8 = lVar9;
  __s10Foundation9IndexPathVMa();
  lVar9 = _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks;
  lVar21 = *(long *)(lVar10 + -8);
  lVar20 = lVar20 - (*(long *)(lVar21 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar22 = *(long *)(unaff_x20 + _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks
                    );
  if (lVar22 == 0) {
    lVar17 = unaff_x20;
    FUN_10024e1d4();
    uVar12 = *(undefined8 *)(unaff_x20 + lVar9);
    *(long *)(unaff_x20 + lVar9) = lVar17;
    _swift_bridgeObjectRetain();
    _swift_bridgeObjectRelease(uVar12);
    lVar9 = *(long *)(lVar17 + 0x10);
    lVar1 = _TtC8Playback19MixerViewController::tracksCollectionView;
  }
  else {
    lVar9 = *(long *)(lVar22 + 0x10);
    lVar17 = lVar22;
    lVar1 = _TtC8Playback19MixerViewController::tracksCollectionView;
  }
  _TtC8Playback19MixerViewController::tracksCollectionView = lVar1;
  if (lVar9 == 0) {
    _swift_bridgeObjectRetain(lVar22);
    _swift_bridgeObjectRelease(lVar17);
    return;
  }
  local_10c = *(undefined4 *)
               PTR___sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyO7inherityA2EmFWC_100a1e0e8
  ;
  local_108 = auStack_150 + -(lVar19 + 0xfU & 0xfffffffffffffff0);
  lStack_100 = lVar24;
  local_f8 = lVar8;
  _swift_bridgeObjectRetain(lVar22);
  lVar8 = 0;
  lVar19 = 0x20;
  local_c0 = lVar9;
  do {
    lVar22 = *(long *)(lVar17 + lVar19);
    _swift_unknownObjectRetain(lVar22);
    __s10Foundation9IndexPathV5UIKitE4item7sectionACSi_SitcfC(lVar20,lVar8,0);
    IVar11 = unaff_x20 + lVar1;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar11 == 0) {
LAB_100250ec8:
      _swift_unknownObjectRelease(lVar22);
LAB_100250ed0:
      (**(code **)(lVar21 + 8))(lVar20,lVar10);
      uVar12 = param_1;
    }
    else {
      IVar16 = IVar11;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      IVar11 = _objc_msgSend(IVar11,"cellForItemAtIndexPath:",IVar16);
      if (IVar11 == 0) goto LAB_100250ec8;
      uVar12 = 0;
      FUN_1007c0440(0);
      _swift_dynamicCastClass(IVar11,uVar12);
      if (IVar11 == 0) {
        _swift_unknownObjectRelease(lVar22);
        goto LAB_100250ed0;
      }
      lVar24 = lVar22;
      _swift_getObjectType();
      lVar13 = lVar24;
      _swift_conformsToProtocol();
      if ((lVar13 == 0) || (lVar22 == 0)) {
        _swift_unknownObjectRelease(lVar22);
        goto LAB_100250ed0;
      }
      local_b0 = lVar13;
      _swift_conformsToProtocol(lVar24,&TargetProtocolDescriptor_1009ab3b8);
      lVar13 = DAT_100adef08;
      if (lVar24 == 0) {
        _swift_unknownObjectRetain(lVar22);
LAB_100251420:
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        uVar4 = DAT_100b77550;
        lVar24 = lVar22;
        _swift_getObjectType(lVar22);
        _swift_unknownObjectRetain(lVar22);
        _swift_retain(uVar4);
        uVar18 = 0;
        FUN_1005ebc74(lVar22,0,0,lVar24,local_b0);
        uVar12 = param_1;
        _swift_release(uVar4);
        _swift_unknownObjectRelease(lVar22);
        lVar24 = _TtC8Playback14MixerTrackCell::vuMeter;
        if (*(char *)(IVar11 + _TtC8Playback14MixerTrackCell::muteState) == '\0') {
          param_1 = 0;
        }
        lVar13 = IVar11 + _TtC8Playback14MixerTrackCell::vuMeter;
        _swift_unknownObjectWeakLoadStrong();
        if (lVar13 != 0) {
          uVar12 = 0;
          FUN_1007f6c90(0,1);
        }
        IVar11 = IVar11 + lVar24;
        _swift_unknownObjectWeakLoadStrong();
        if (IVar11 == 0) {
          _swift_unknownObjectRelease_n(lVar22,2);
        }
        else {
          IVar16 = IVar11;
          __sSd11descriptionSSvg(param_1);
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
          _swift_bridgeObjectRelease(uVar18);
          _objc_msgSend(IVar11,"setAccessibilityLabel:",IVar16);
          _swift_unknownObjectRelease_n(lVar22,2);
          uVar12 = param_1;
        }
        (**(code **)(lVar21 + 8))(lVar20,lVar10);
      }
      else {
        _swift_unknownObjectRetain_n(lVar22,2);
        if (lVar13 != -1) {
          _swift_once(&DAT_100adef08,FUN_1002c44b8);
        }
        lVar13 = *(long *)(DAT_100b75e40 + 0x18);
        if (lVar13 == 0) {
LAB_100251418:
          _swift_unknownObjectRelease(lVar22);
          goto LAB_100251420;
        }
        lVar23 = *(long *)(lVar13 + 0x78);
        local_f0 = lVar24;
        if (lVar23 == 0) {
          local_120 = *(ID *)(lVar13 + 0x10);
          lVar23 = 0;
          local_118 = lVar13;
          FUN_10073f4a4();
          _swift_allocObject();
          puVar14 = &_OBJC_CLASS___AVAudioMixerNode;
          _objc_allocWithZone();
          _swift_retain(lVar13);
          IVar16 = _objc_msgSend((ID)puVar14,"init");
          *(ID *)(lVar23 + 0x10) = IVar16;
          _swift_unknownObjectWeakInit(lVar23 + 0x18,0);
          *(undefined1 *)(lVar23 + 0x20) = 1;
          puVar14 = &DAT_100af5be0;
          FUN_100021774();
          _swift_allocObject();
          uVar12 = 0;
          puVar15 = &DAT_100af52a0;
          local_140 = puVar14;
          FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
          lVar9 = local_e8;
          local_88 = (undefined *)0x755163696d6f7441;
          local_80 = 0xec0000005f657565;
          local_128 = uVar12;
          __s10Foundation4UUIDVACycfC(local_e8);
          __s10Foundation4UUIDV10uuidStringSSvg();
          local_130 = (undefined *)uVar12;
          (**(code **)(local_e0 + 8))(lVar9,lStack_d8);
          __sSS6appendyySSF(local_130,puVar15);
          _swift_bridgeObjectRelease(puVar15);
          local_130 = local_88;
          local_138 = local_80;
          __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_b8);
          puVar3 = PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVMa_100a1e0d0;
          puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
          local_88 = PTR___swiftEmptyArrayStorage_100a1e050;
          puVar14 = &DAT_100af5be8;
          FUN_100023140(&DAT_100af5be8,
                        PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVMa_100a1e0d0,
                        PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVs10SetAlgebraACMc_100a1e0e0
                       );
          local_148 = puVar14;
          _swift_retain(puVar2);
          puVar14 = &DAT_100af5bf0;
          FUN_100021774(&DAT_100af5bf0);
          puVar15 = &DAT_100af5bf8;
          FUN_1001d598c(&DAT_100af5bf8,&DAT_100af5c00,puVar3);
          lVar9 = local_d0;
          __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                    (local_d0,&local_88,puVar14,puVar15,lStack_c8,local_148);
          puVar5 = local_108;
          (**(code **)(lStack_100 + 0x68))(local_108,local_10c,local_f8);
          puVar14 = local_130;
          __sSo17OS_dispatch_queueC8DispatchE5label3qos10attributes20autoreleaseFrequency6targetABSS_AC0D3QoSVAbCE10AttributesVAbCE011AutoreleaseI0OABSgtcfC
                    (local_130,local_138,local_b8,lVar9,puVar5,0);
          *(undefined8 *)(local_140 + 0x18) = 0;
          *(undefined8 *)(local_140 + 0x20) = 0;
          *(undefined **)(local_140 + 0x10) = puVar14;
          *(undefined **)(lVar23 + 0x28) = local_140;
          _swift_weakInit(lVar23 + 0x30,0);
          IVar16 = local_120;
          *(undefined2 *)(lVar23 + 0x38) = 0;
          *(undefined **)(lVar23 + 0x40) = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined8 *)(lVar23 + 0x48) = 0;
          _swift_unknownObjectWeakAssign(lVar23 + 0x18,local_120);
          uVar12 = *(undefined8 *)(lVar23 + 0x10);
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          _objc_msgSend(IVar16,"attachNode:",uVar12);
          lVar13 = local_118;
          uVar12 = *(undefined8 *)(local_118 + 0x78);
          *(long *)(local_118 + 0x78) = lVar23;
          _swift_retain(lVar23);
          _swift_release(uVar12);
          lVar9 = 0;
        }
        else {
          _swift_retain();
          lVar9 = lVar23;
        }
        _swift_retain(lVar9);
        _swift_release(lVar13);
        if (*(char *)(lVar23 + 0x38) != '\x01') {
          _swift_release(lVar23);
          _swift_unknownObjectRelease(lVar22);
          lVar9 = local_c0;
          goto LAB_100251420;
        }
        lVar24 = lVar23 + 0x30;
        _swift_weakLoadStrong();
        lVar9 = local_c0;
        if (lVar24 == 0) {
          _swift_release(lVar23);
          goto LAB_100251418;
        }
        local_118 = lVar23;
        self = _objc_msgSend(*(ID *)(lVar24 + 0x60),"type");
        IVar16 = 0;
        if (self != 0) {
          IVar16 = _objc_msgSend(self,"integerValue");
          local_120 = IVar16;
        }
        uVar6 = (uint)IVar16;
        FUN_10055ee18();
        uVar7 = 0;
        if ((uVar6 & 0xff) != 0x14) {
          uVar7 = uVar6;
        }
        local_120 = CONCAT44(local_120._4_4_,uVar7) & 0xffffffff000000ff;
        lVar13 = lVar22;
        _swift_getObjectType();
        uVar7 = (uint)lVar13;
        (**(code **)(local_f0 + 0x30))();
        _swift_release(local_118);
        _swift_release(lVar24);
        _swift_unknownObjectRelease(lVar22);
        if ((uint)local_120 != (uVar7 & 0xff)) goto LAB_100251420;
        (**(code **)(lVar21 + 8))(lVar20,lVar10);
        _swift_unknownObjectRelease_n(lVar22,2);
        uVar12 = param_1;
      }
    }
    lVar8 = lVar8 + 1;
    lVar19 = lVar19 + 0x10;
    param_1 = uVar12;
    if (lVar9 == lVar8) {
      _swift_bridgeObjectRelease(lVar17);
      return;
    }
  } while( true );
}

// ==== 10025278c _TtC8Playback19MixerViewController::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback19MixerViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_unknownObjectWeakDestroy(param_1 + mainStackView);
  _swift_unknownObjectWeakDestroy(param_1 + waveformViewDummySpacer);
  _swift_unknownObjectWeakDestroy(param_1 + tracksCollectionView);
  _swift_unknownObjectWeakDestroy(param_1 + mixerPadPanelContainerView);
  _swift_unknownObjectWeakDestroy(param_1 + panelSeparatorView);
  _swift_unknownObjectWeakDestroy(param_1 + errorStackView);
  _swift_unknownObjectWeakDestroy(param_1 + errorTitleLabel);
  _swift_unknownObjectWeakDestroy(param_1 + errorDescriptionLabel);
  _swift_unknownObjectWeakDestroy(param_1 + errorActionButton);
  _swift_unknownObjectWeakDestroy(param_1 + masterPanelButtonStackView);
  _swift_unknownObjectWeakDestroy(param_1 + modeMultiControlContainerView);
  _swift_unknownObjectWeakDestroy(param_1 + modePageControl);
  _swift_unknownObjectWeakDestroy(param_1 + modeButton);
  _swift_unknownObjectWeakDestroy(param_1 + muteMIDIButton);
  _swift_unknownObjectWeakDestroy(param_1 + singleLoopButton);
  _swift_unknownObjectWeakDestroy(param_1 + infiniteLoopButton);
  _swift_unknownObjectWeakDestroy(param_1 + leftVUMeter);
  _swift_unknownObjectWeakDestroy(param_1 + rightVUMeter);
  _swift_unknownObjectWeakDestroy(param_1 + masterFader);
  _swift_unknownObjectWeakDestroy(param_1 + masterFaderLabel);
  _swift_unknownObjectWeakDestroy(param_1 + masterFaderCapLeadingSpaceConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + masterPanelStackViewTopSpaceConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + padPanelContainerViewLeftConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + muteMIDIButtonWidthConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + muteMIDIButtonHeightConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + padPanelLeadingSpacerViewWidthConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + mixerModeMultiControlViewController);
  FUN_1000cf9ec(*(undefined8 *)(param_1 + currentTrackSet),
                *(undefined1 *)((undefined8 *)(param_1 + currentTrackSet) + 1));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + modeScrollViewContentOffsets));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + masterClickFollowIndex));
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + privateCurrentDisplayableTracks));
  return;
}

// ==== 100254dd8 FUN_100254dd8 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Type propagation algorithm not settling */

undefined8 FUN_100254dd8(char *param_1,char *param_2)

{
  ulong *puVar1;
  class_rw_t *pcVar2;
  long lVar3;
  undefined1 uVar4;
  byte bVar5;
  char cVar6;
  method_list_t *pmVar7;
  char cVar8;
  char cVar9;
  bool bVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  class_rw_t *pcVar17;
  undefined8 uVar18;
  ulong uVar19;
  ulong uVar20;
  undefined *puVar21;
  ID IVar22;
  class_rw_t *pcVar23;
  class_rw_t *pcVar24;
  method_list_t mVar25;
  method_list_t mVar26;
  char *pcVar27;
  undefined8 uVar28;
  ulong uVar29;
  ulong uVar30;
  undefined **ppuVar31;
  ID IVar32;
  class_t *pcVar33;
  class_rw_t *pcVar34;
  method_list_t mVar35;
  method_list_t mVar36;
  ivar_list_t iVar37;
  undefined8 uVar38;
  long unaff_x20;
  long lVar39;
  class_rw_t *pcVar40;
  class_t *pcVar41;
  ulong uVar42;
  class_rw_t *pcVar43;
  ulong uVar44;
  protocol_list_t *ppVar45;
  long lVar46;
  code *pcVar47;
  method_list_t *pmVar48;
  Cache CVar49;
  code *pcVar50;
  long lVar51;
  long *plVar52;
  long lVar53;
  long lVar54;
  double dVar55;
  char *pcVar56;
  method_list_t *pmVar57;
  char *pcVar58;
  char *pcVar59;
  char *pcVar60;
  char *pcVar61;
  undefined1 auStack_1e0 [16];
  undefined8 auStack_1d0 [2];
  class_rw_t *local_1c0;
  class_t *local_1b8;
  class_rw_t *local_1b0;
  class_rw_t *local_1a8;
  long local_1a0;
  long local_198;
  long local_190;
  undefined8 local_188;
  long local_180;
  class_rw_t *local_178;
  class_rw_t *local_158;
  class_rw_t cStack_f0;
  
  lVar12 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar46 = *(long *)(lVar12 + -8);
  lVar54 = (long)&local_1c0 - (*(long *)(lVar46 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar13 = 0;
  __s10Foundation9IndexPathVMa();
  lVar53 = *(long *)(lVar13 + -8);
  lVar51 = lVar54 - (*(long *)(lVar53 + 0x40) + 0xfU & 0xfffffffffffffff0);
  if (*(char *)(unaff_x20 + _TtC8Playback19MixerViewController::currentMixerMode) != '\x01') {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar29 = DAT_100b757a8;
    FUN_1001711d0();
    if ((uVar29 & 1) == 0) {
      if (DAT_100adfba8 != -1) {
        _swift_once(&DAT_100adfba8,FUN_100596ba8);
      }
      uVar29 = DAT_100b77538;
      uVar44 = DAT_100b77538;
      _swift_retain();
      FUN_10059671c();
      _swift_release(uVar29);
      if ((uVar44 & 1) != 0) {
        if (DAT_100adef08 != -1) {
          _swift_once(&DAT_100adef08,FUN_1002c44b8);
        }
        lVar14 = *(long *)(DAT_100b75e40 + 0x18);
        if (lVar14 != 0) {
          _swift_retain();
          FUN_100732b68();
          lVar15 = unaff_x20 + _TtC8Playback19MixerViewController::leftVUMeter;
          pcVar59 = param_1;
          _swift_unknownObjectWeakLoadStrong();
          if (lVar15 != 0) {
            FUN_1007f6c90(0);
            pcVar59 = param_1;
          }
          lVar15 = unaff_x20 + _TtC8Playback19MixerViewController::rightVUMeter;
          _swift_unknownObjectWeakLoadStrong();
          if (lVar15 != 0) {
            FUN_1007f6c90(0);
            pcVar59 = param_2;
          }
          lVar15 = _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks;
          lVar39 = *(long *)(unaff_x20 +
                            _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks);
          lVar16 = lVar39;
          if (lVar39 == 0) {
            lVar16 = unaff_x20;
            FUN_10024e1d4();
            uVar18 = *(undefined8 *)(unaff_x20 + lVar15);
            *(long *)(unaff_x20 + lVar15) = lVar16;
            _swift_bridgeObjectRetain();
            _swift_bridgeObjectRelease(uVar18);
          }
          lVar3 = _TtC8Playback19MixerViewController::masterClickFollowIndex;
          lVar15 = _TtC8Playback19MixerViewController::tracksCollectionView;
          uVar29 = *(ulong *)(lVar16 + 0x10);
          if (uVar29 != 0) {
            puVar1 = (ulong *)(unaff_x20 + _TtC8Playback19MixerViewController::currentTrackSet);
            _swift_bridgeObjectRetain(lVar39);
            local_190 = lVar3;
            _swift_beginAccess(unaff_x20 + lVar3,&cStack_f0.ivars,0,0);
            local_158 = (class_rw_t *)0x0;
            local_188 = 0;
            pcVar60 = (char *)0x0;
            pcVar61 = (char *)0x0;
            uVar44 = 0;
            local_1a0 = lVar54;
            local_198 = lVar46;
            local_180 = lVar12;
LAB_100255124:
            if (*(ulong *)(lVar16 + 0x10) <= uVar44) {
                    /* WARNING: Does not return */
              pcVar47 = (code *)SoftwareBreakpoint(1,0x100256f6c);
              (*pcVar47)();
            }
            plVar52 = (long *)(lVar16 + 0x20 + uVar44 * 0x10);
            pcVar2 = (class_rw_t *)*plVar52;
            lVar12 = plVar52[1];
            _swift_unknownObjectRetain(pcVar2);
            __s10Foundation9IndexPathV5UIKitE3row7sectionACSi_SitcfC(lVar51,uVar44,0);
            IVar22 = unaff_x20 + lVar15;
            _swift_unknownObjectWeakLoadStrong();
            if (IVar22 == 0) {
LAB_1002551dc:
              pcVar17 = (class_rw_t *)0x0;
            }
            else {
              IVar32 = IVar22;
              __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
              pcVar17 = (class_rw_t *)_objc_msgSend(IVar22,"cellForItemAtIndexPath:",IVar32);
              if (pcVar17 == (class_rw_t *)0x0) goto LAB_1002551dc;
              uVar18 = 0;
              FUN_1007c0440(0);
              _swift_dynamicCastClass(pcVar17,uVar18);
            }
            pcVar34 = pcVar2;
            _swift_getObjectType(pcVar2);
            uVar42 = *puVar1;
            pcVar47 = *(code **)(lVar12 + 0x90);
            uVar4 = (undefined1)puVar1[1];
            FUN_1000cf9b4(uVar42,uVar4);
            uVar30 = uVar42;
            (*pcVar47)(uVar42,uVar4,pcVar34,lVar12);
            FUN_1000cf9ec(uVar42,uVar4);
            if ((uVar30 & 1) != 0) {
              uVar18 = 0;
              FUN_1000cda74(0);
              pcVar34 = pcVar2;
              _swift_dynamicCastClass(pcVar2,uVar18);
              if (pcVar34 != (class_rw_t *)0x0) {
                if (*(long *)(DAT_100b75e40 + 0x20) == 0) {
                  _swift_unknownObjectRelease(pcVar2);
                }
                else if (((*(byte *)(*(long *)(DAT_100b75e40 + 0x20) +
                                    _TtC8Playback9Sequencer::privatePlayState) & 1) == 0) ||
                        (lVar12 = *(long *)(lVar14 + 0x18), lVar12 == 0)) {
                  _swift_unknownObjectRelease(pcVar2);
                }
                else {
                  lVar46 = *(long *)((long)&_TtC8Playback16SongChannelGroup::allChannels->flags +
                                    lVar12);
                  uVar30 = *(ulong *)(lVar46 + 0x10);
                  if (uVar30 != 0) {
                    local_178 = _TtC8Playback16SongChannelGroup::allChannels;
                    _swift_unknownObjectRetain(pcVar2);
                    _swift_retain(lVar12);
                    _swift_bridgeObjectRetain(lVar46);
                    lVar54 = 0;
                    uVar42 = 0;
                    pcVar58 = pcVar59;
                    do {
                      uVar20 = *(ulong *)(lVar46 + lVar54 + 0x20);
                      lVar39 = *(long *)(lVar46 + lVar54 + 0x28);
                      uVar19 = uVar20;
                      _swift_getObjectType();
                      pcVar47 = *(code **)(lVar39 + 0x18);
                      _swift_unknownObjectRetain(uVar20);
                      (*pcVar47)(uVar19,lVar39);
                      if (uVar19 == 0) {
                        _swift_unknownObjectRelease(uVar20);
                        pcVar59 = pcVar58;
                      }
                      else {
                        _swift_unknownObjectRetain(pcVar2);
                        __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar19,pcVar34);
                        _swift_unknownObjectRelease(uVar20);
                        _swift_unknownObjectRelease(pcVar2);
                        pcVar59 = pcVar58;
                        if ((uVar19 & 1) != 0) {
                          _swift_bridgeObjectRelease(lVar46);
                          lVar46 = *(long *)((long)&local_178->flags + lVar12);
                          if (*(long *)(lVar46 + 0x10) <= (long)uVar42) {
                            _swift_release();
                            _swift_unknownObjectRelease_n(pcVar2,2);
                            pcVar59 = pcVar58;
                            goto LAB_100255100;
                          }
                          lVar46 = lVar46 + lVar54;
                          pcVar34 = *(class_rw_t **)(lVar46 + 0x20);
                          lVar46 = *(long *)(lVar46 + 0x28);
                          pcVar40 = pcVar34;
                          _swift_getObjectType();
                          pcVar47 = *(code **)(lVar46 + 0x20);
                          _swift_unknownObjectRetain(pcVar34);
                          local_1a8 = pcVar40;
                          (*pcVar47)(pcVar40,lVar46);
                          if (((ulong)pcVar40 & 1) == 0) goto LAB_100255f3c;
                          lVar39 = *(long *)((long)&local_178->flags + lVar12);
                          lVar54 = *(long *)(lVar39 + 0x10);
                          if (lVar54 == 0) goto LAB_100255f3c;
                          _swift_bridgeObjectRetain(lVar39);
                          plVar52 = (long *)(lVar39 + 0x28);
                          goto LAB_1002554b4;
                        }
                      }
                      uVar42 = uVar42 + 1;
                      lVar54 = lVar54 + 0x10;
                      pcVar58 = pcVar59;
                    } while (uVar30 != uVar42);
                    _swift_release(lVar12);
                    _swift_unknownObjectRelease(pcVar2);
                    _swift_bridgeObjectRelease(lVar46);
                  }
                  _swift_unknownObjectRelease(pcVar2);
                }
                goto LAB_100255100;
              }
              FUN_10065ad50();
              pcVar40 = pcVar2;
              _swift_dynamicCastClass(pcVar2,pcVar34);
              if (pcVar40 != (class_rw_t *)0x0) {
                if (pcVar17 != (class_rw_t *)0x0) {
                  _swift_unknownObjectRetain(pcVar2);
                  FUN_1006582b4();
                  uVar30 = DAT_100b757a8;
                  pcVar58 = pcVar59;
                  FUN_100171178(DAT_100b757a8);
                  pcVar27 = "volume";
                  _objc_msgSend((ID)pcVar40,"volume");
                  lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
                  cVar6 = *(char *)((long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::muteState
                                   );
                  pcVar56 = pcVar58;
                  if (cVar6 == '\0') {
                    pcVar56 = (char *)0x0;
                  }
                  lVar46 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                  _swift_unknownObjectWeakLoadStrong();
                  if (lVar46 != 0) {
                    pcVar58 = pcVar59;
                    if (cVar6 == '\0') {
                      pcVar58 = (char *)0x0;
                    }
                    FUN_1007f6c90((uint)uVar30 & 1);
                  }
                  IVar22 = (long)&pcVar17->flags + lVar12;
                  _swift_unknownObjectWeakLoadStrong();
                  if (IVar22 == 0) {
                    _swift_unknownObjectRelease(pcVar2);
                    pcVar59 = pcVar58;
                  }
                  else {
                    IVar32 = IVar22;
                    __sSd11descriptionSSvg();
                    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                    _swift_bridgeObjectRelease(pcVar27);
                    pcVar27 = "setAccessibilityLabel:";
                    _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                    _swift_unknownObjectRelease(pcVar2);
                    pcVar59 = pcVar56;
                  }
                  goto LAB_1002556e8;
                }
LAB_10025599c:
                _swift_unknownObjectRelease(pcVar2);
                goto LAB_100255cfc;
              }
              FUN_100286674();
              pcVar34 = pcVar2;
              _swift_dynamicCastClass(pcVar2,pcVar40);
              if (pcVar34 != (class_rw_t *)0x0) {
                lVar12 = *(long *)(lVar14 + 0x78);
                local_178 = pcVar40;
                if (lVar12 == 0) {
                  IVar32 = *(ID *)(lVar14 + 0x10);
                  lVar46 = 0;
                  FUN_10073f4a4();
                  _swift_allocObject();
                  puVar21 = &_OBJC_CLASS___AVAudioMixerNode;
                  _objc_allocWithZone();
                  _swift_unknownObjectRetain(pcVar2);
                  IVar22 = _objc_msgSend((ID)puVar21,"init");
                  *(ID *)(lVar46 + 0x10) = IVar22;
                  _swift_unknownObjectWeakInit(lVar46 + 0x18,0);
                  *(undefined1 *)(lVar46 + 0x20) = 1;
                  puVar21 = &DAT_100af5be0;
                  FUN_100021774();
                  _swift_allocObject();
                  pcVar59 = (char *)0x0;
                  FUN_10073ca48(0,0);
                  *(undefined **)(lVar46 + 0x28) = puVar21;
                  _swift_weakInit(lVar46 + 0x30,0);
                  *(undefined2 *)(lVar46 + 0x38) = 0;
                  puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
                  *(undefined **)(lVar46 + 0x40) = PTR___swiftEmptyArrayStorage_100a1e050;
                  *(undefined8 *)(lVar46 + 0x48) = 0;
                  _swift_unknownObjectWeakAssign(lVar46 + 0x18,IVar32);
                  uVar18 = *(undefined8 *)(lVar46 + 0x10);
                  _swift_retain(puVar21);
                  _objc_msgSend(IVar32,"attachNode:",uVar18);
                  uVar18 = *(undefined8 *)(lVar14 + 0x78);
                  *(long *)(lVar14 + 0x78) = lVar46;
                  _swift_retain(lVar46);
                  _swift_release(uVar18);
                }
                else {
                  _swift_unknownObjectRetain(pcVar2);
                  lVar46 = lVar12;
                }
                bVar5 = *(byte *)(lVar46 + 0x38);
                pcVar27 = (char *)&cStack_f0;
                _swift_beginAccess(lVar46 + 0x40,pcVar27,0,0);
                pcVar40 = *(class_rw_t **)(lVar46 + 0x40);
                if ((ulong)pcVar40 >> 0x3e == 0) {
                  if (*(long *)(((ulong)pcVar40 & 0xfffffffffffff8) + 0x10) != 0)
                  goto LAB_100255b38;
LAB_100256678:
                  _swift_retain(lVar12);
                  pcVar58 = pcVar59;
                  if ((bVar5 & 1) != 0) goto LAB_100256690;
                  pcVar40 = (class_rw_t *)0x0;
LAB_100256688:
                  _swift_bridgeObjectRelease(pcVar40);
                  pcVar58 = pcVar59;
                }
                else {
                  pcVar43 = (class_rw_t *)((ulong)pcVar40 & 0xffffffffffffff8);
                  if ((long)pcVar40 < 0) {
                    pcVar43 = pcVar40;
                  }
                  __ss18_CocoaArrayWrapperV8endIndexSivg();
                  if (pcVar43 == (class_rw_t *)0x0) goto LAB_100256678;
LAB_100255b38:
                  if (((ulong)pcVar40 & 0xc000000000000001) == 0) {
                    if (*(long *)(((ulong)pcVar40 & 0xfffffffffffff8) + 0x10) == 0) {
                    /* WARNING: Does not return */
                      pcVar47 = (code *)SoftwareBreakpoint(1,0x100256fb8);
                      (*pcVar47)();
                    }
                    pmVar48 = pcVar40->baseMethods;
                    _swift_retain(lVar12);
                    _swift_retain(pmVar48);
                  }
                  else {
                    _swift_retain(lVar12);
                    _swift_bridgeObjectRetain(pcVar40);
                    pmVar48 = (method_list_t *)0x0;
                    pcVar27 = (char *)pcVar40;
                    FUN_1000cc648();
                    _swift_bridgeObjectRelease(pcVar40);
                  }
                  pcVar40 = *(class_rw_t **)
                             ((long)&pmVar48->entsizeAndFlags +
                             _TtC8Playback15PadChannelGroup::channels);
                  _swift_bridgeObjectRetain(pcVar40);
                  _swift_release(pmVar48);
                  if ((bVar5 & 1) == 0) goto LAB_100256688;
                  pcVar58 = pcVar59;
                  if (pcVar40 != (class_rw_t *)0x0) {
                    CVar49 = pcVar40->instanceSize;
                    local_1a8 = pcVar40;
                    if (CVar49 == 0) {
                      pcVar43 = (class_rw_t *)0x0;
                      ppuVar31 = (undefined **)0x0;
                    }
                    else {
                      _swift_bridgeObjectRetain(pcVar40);
                      lVar12 = 0x20;
                      do {
                        pcVar43 = *(class_rw_t **)((long)&pcVar40->flags + lVar12);
                        _swift_unknownObjectRetain_n(pcVar43,2);
                        pcVar27 = "partID";
                        IVar22 = _objc_msgSend((ID)pcVar34,"partID");
                        if ((int)IVar22 == 0x4ea) {
                          pcVar23 = pcVar43;
                          _object_getClass();
                          if (pcVar23 ==
                              (class_rw_t *)&objc::class_t::_TtC8Playback22PadPlayerMasterChannel &&
                              pcVar43 != (class_rw_t *)0x0) {
                            _swift_unknownObjectRelease(pcVar43);
                            _swift_bridgeObjectRelease(pcVar40);
                            ppuVar31 = &PTR_PTR_100a6ae00;
                            goto LAB_1002563fc;
                          }
                          if (pcVar23 !=
                              (class_rw_t *)&objc::class_t::_TtC8Playback20PadPlayerFileChannel ||
                              pcVar43 == (class_rw_t *)0x0) goto LAB_100255c38;
LAB_100255bc8:
                          pcVar27 = (char *)0x2;
                          _swift_unknownObjectRelease_n(pcVar43);
                        }
                        else {
LAB_100255c38:
                          pcVar23 = pcVar43;
                          _object_getClass();
                          if (pcVar23 !=
                              (class_rw_t *)&objc::class_t::_TtC8Playback20PadPlayerFileChannel ||
                              pcVar43 == (class_rw_t *)0x0) goto LAB_100255bc8;
                          pcVar23 = pcVar43 + 1;
                          _swift_unknownObjectWeakLoadStrong();
                          if (pcVar23 == (class_rw_t *)0x0) {
                            pcVar27 = (char *)0x2;
                            _swift_unknownObjectRelease_n(pcVar43);
                          }
                          else {
                            _swift_unknownObjectRetain_n(pcVar2,2);
                            _swift_unknownObjectRetain(pcVar43);
                            pcVar24 = pcVar34;
                            __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(pcVar34,pcVar23);
                            _swift_unknownObjectRelease_n(pcVar2,2);
                            pcVar27 = (char *)0x2;
                            _swift_unknownObjectRelease_n(pcVar43);
                            if (((ulong)pcVar24 & 1) != 0) {
                              _swift_bridgeObjectRelease(pcVar40);
                              ppuVar31 = &PTR_PTR_100a34308;
                              goto LAB_1002563fc;
                            }
                            _swift_unknownObjectRelease(pcVar43);
                          }
                        }
                        lVar12 = lVar12 + 0x10;
                        CVar49 = CVar49 - 1;
                      } while (CVar49 != 0);
                      _swift_bridgeObjectRelease(pcVar40);
                      pcVar43 = (class_rw_t *)0x0;
                      ppuVar31 = (undefined **)0x0;
                    }
LAB_1002563fc:
                    lVar12 = local_180;
                    if (pcVar17 == (class_rw_t *)0x0) {
                      _swift_release(lVar46);
                      _swift_bridgeObjectRelease(local_1a8);
                      _swift_unknownObjectRelease(pcVar2);
                    }
                    else {
                      if (pcVar43 != (class_rw_t *)0x0) {
                        pcVar34 = pcVar43;
                        local_1b8 = (class_t *)ppuVar31;
                        local_1b0 = pcVar17;
                        _swift_unknownObjectRetain();
                        FUN_100173aa8();
                        if ((class_rw_t *)pcVar27 == (class_rw_t *)0x0) {
LAB_1002565f0:
                          bVar10 = false;
                        }
                        else {
                          FUN_1001d3fe4(pcVar34,pcVar27);
                          _swift_bridgeObjectRelease();
                          if (pcVar34 == (class_rw_t *)0x0) goto LAB_1002565f0;
                          local_1c0 = pcVar34;
                          FUN_1001ca220();
                          if ((ulong)pcVar27 >> 0x3e == 0) {
                            pcVar17 = *(class_rw_t **)(((ulong)pcVar27 & 0xfffffffffffff8) + 0x10);
                            if (pcVar17 != (class_rw_t *)0x0) goto LAB_1002564ac;
LAB_1002567c8:
                            mVar36 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
                            _swift_retain();
                          }
                          else {
                            pcVar17 = (class_rw_t *)((ulong)pcVar27 & 0xffffffffffffff8);
                            if ((long)pcVar27 < 0) {
                              pcVar17 = (class_rw_t *)pcVar27;
                            }
                            __ss18_CocoaArrayWrapperV8endIndexSivg();
                            if (pcVar17 == (class_rw_t *)0x0) goto LAB_1002567c8;
LAB_1002564ac:
                            if ((long)pcVar17 < 1) {
                    /* WARNING: Does not return */
                              pcVar47 = (code *)SoftwareBreakpoint(1,0x100256fbc);
                              (*pcVar47)();
                            }
                            uVar30 = (ulong)pcVar27 & 0xc000000000000001;
                            mVar36 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
                            _swift_retain();
                            pcVar34 = (class_rw_t *)0x0;
                            local_178 = (class_rw_t *)pcVar27;
                            do {
                              if (uVar30 == 0) {
                                pcVar40 = (class_rw_t *)
                                          (&((class_rw_t *)pcVar27)->baseMethods)[(long)pcVar34];
                              }
                              else {
                                pcVar40 = pcVar34;
                                FUN_1000cc534(pcVar34,pcVar27);
                              }
                              IVar22 = _objc_msgSend((ID)pcVar40,"included");
                              if ((int)IVar22 != 0) {
                                mVar35 = mVar36;
                                _swift_isUniquelyReferenced_nonNull_native();
                                cStack_f0.baseMethods = (method_list_t *)mVar36;
                                if (((ulong)mVar35 & 1) == 0) {
                                  FUN_1001cc5f4(0,(long)*(method_list_t *)((long)mVar36 + 0x10) + 1,
                                                1);
                                  pcVar27 = (char *)local_178;
                                }
                                mVar36 = *(method_list_t *)((long)cStack_f0.baseMethods + 0x10);
                                if ((ulong)*(method_list_t *)((long)cStack_f0.baseMethods + 0x18) >>
                                    1 <= (ulong)mVar36) {
                                  FUN_1001cc5f4(1 < (ulong)*(method_list_t *)
                                                            ((long)cStack_f0.baseMethods + 0x18),
                                                (long)mVar36 + 1U,1);
                                  pcVar27 = (char *)local_178;
                                }
                                *(ulong *)((long)cStack_f0.baseMethods + 0x10) = (long)mVar36 + 1U;
                                *(class_rw_t **)
                                 ((long)cStack_f0.baseMethods + ((long)mVar36 + 4U) * 8) = pcVar40;
                                mVar36 = (method_list_t)cStack_f0.baseMethods;
                                lVar12 = local_180;
                              }
                              pcVar34 = (class_rw_t *)((long)&pcVar34->flags + 1);
                            } while (pcVar17 != pcVar34);
                          }
                          _swift_bridgeObjectRelease(pcVar27);
                          if (((long)mVar36 < 0) || (((ulong)mVar36 >> 0x3e & 1) != 0)) {
                            mVar35 = mVar36;
                            __ss18_CocoaArrayWrapperV8endIndexSivg();
                            if (mVar35 == (method_list_t)0x0) goto LAB_10025694c;
LAB_1002567f0:
                            if ((long)mVar35 < 1) {
                    /* WARNING: Does not return */
                              pcVar47 = (code *)SoftwareBreakpoint(1,0x100256fc0);
                              (*pcVar47)();
                            }
                            mVar26 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
                            _swift_retain();
                            lVar54 = 0;
                            do {
                              if (((ulong)mVar36 & 0xc000000000000001) == 0) {
                                lVar39 = *(long *)((long)mVar36 + (lVar54 + 4) * 8);
                              }
                              else {
                                lVar39 = lVar54;
                                FUN_1000cc534(lVar54,mVar36);
                              }
                              if (DAT_100adfbd0 != -1) {
                                _swift_once(&DAT_100adfbd0,FUN_1005d0614);
                              }
                              if ((*(byte *)(lVar39 + _TtC8Playback8PadTrack::soloState) & 1) == 0)
                              {
                                mVar25 = mVar26;
                                _swift_isUniquelyReferenced_nonNull_native();
                                cStack_f0.baseMethods = (method_list_t *)mVar26;
                                if (((ulong)mVar25 & 1) == 0) {
                                  FUN_1001cc5f4(0,(long)*(method_list_t *)((long)mVar26 + 0x10) + 1,
                                                1);
                                }
                                mVar26 = *(method_list_t *)((long)cStack_f0.baseMethods + 0x10);
                                if ((ulong)*(method_list_t *)((long)cStack_f0.baseMethods + 0x18) >>
                                    1 <= (ulong)mVar26) {
                                  FUN_1001cc5f4(1 < (ulong)*(method_list_t *)
                                                            ((long)cStack_f0.baseMethods + 0x18),
                                                (long)mVar26 + 1U,1);
                                }
                                *(ulong *)((long)cStack_f0.baseMethods + 0x10) = (long)mVar26 + 1U;
                                *(long *)((long)cStack_f0.baseMethods + ((long)mVar26 + 4U) * 8) =
                                     lVar39;
                                mVar26 = (method_list_t)cStack_f0.baseMethods;
                                lVar12 = local_180;
                              }
                              lVar54 = lVar54 + 1;
                            } while (mVar35 != (method_list_t)lVar54);
                          }
                          else {
                            mVar35 = *(method_list_t *)((long)mVar36 + 0x10);
                            if (mVar35 != (method_list_t)0x0) goto LAB_1002567f0;
LAB_10025694c:
                            mVar26 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
                            _swift_retain();
                          }
                          _swift_release(mVar36);
                          if (((long)mVar26 < 0) || (((ulong)mVar26 >> 0x3e & 1) != 0)) {
                            mVar36 = mVar26;
                            __ss18_CocoaArrayWrapperV8endIndexSivg();
                          }
                          else {
                            mVar36 = *(method_list_t *)((long)mVar26 + 0x10);
                          }
                          _swift_release(mVar26);
                          bVar10 = mVar36 != (method_list_t)0x0;
                        }
                        pcVar17 = pcVar43;
                        _swift_getObjectType();
                        pcVar41 = local_1b8;
                        pcVar33 = local_1b8->superclass;
                        _swift_unknownObjectRetain(pcVar43);
                        pcVar34 = pcVar17;
                        (*(code *)pcVar33)(pcVar17,pcVar41);
                        pcVar40 = pcVar43;
                        _object_getClass();
                        if (((ulong)pcVar34 & 1) == 0) {
                          if (!(bool)(pcVar40 ==
                                      (class_rw_t *)
                                      &objc::class_t::_TtC8Playback22PadPlayerMasterChannel & bVar10
                                     )) {
LAB_100256d8c:
                            _swift_unknownObjectRelease(pcVar43);
                            IVar22 = (long)&local_1b0->flags +
                                     _TtC8Playback14MixerTrackCell::vuMeter;
                            _swift_unknownObjectWeakLoadStrong();
                            if (IVar22 == 0) {
                              _swift_release(lVar46);
                              _swift_bridgeObjectRelease(local_1a8);
                              _swift_unknownObjectRelease(pcVar2);
                              pcVar27 = (char *)0x2;
                              _swift_unknownObjectRelease_n(pcVar43,2);
                            }
                            else {
                              pcVar59 = (char *)0x0;
                              IVar32 = IVar22;
                              __sSd11descriptionSSvg();
                              __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                              _swift_bridgeObjectRelease(pcVar41);
                              _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                              _swift_release(lVar46);
                              _swift_bridgeObjectRelease(local_1a8);
                              _swift_unknownObjectRelease(pcVar2);
                              pcVar27 = (char *)0x2;
                              _swift_unknownObjectRelease_n(pcVar43,2);
                            }
                            goto LAB_1002556e8;
                          }
LAB_100256c50:
                          uVar38 = *(undefined8 *)(lVar46 + 0x28);
                          _swift_retain(uVar38);
                          uVar18 = local_188;
                          uVar28 = uVar38;
                          __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                                    (&cStack_f0.baseMethods,FUN_10026fbc8,uVar38,&DAT_100a5cf68);
                          local_188 = uVar18;
                          _swift_release(uVar38);
                          pmVar48 = cStack_f0.baseMethods;
                          pcVar17 = local_1b0;
                          lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
                          dVar55 = (double)CONCAT71(cStack_f0.baseProtocols._1_7_,
                                                    (char)cStack_f0.baseProtocols);
                          pcVar59 = pcVar43->name;
                          cVar6 = *(char *)((long)&local_1b0->flags +
                                           _TtC8Playback14MixerTrackCell::muteState);
                          pcVar58 = pcVar59;
                          if (cVar6 == '\0') {
                            pcVar58 = (char *)0x0;
                          }
                          lVar54 = (long)&local_1b0->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                          _swift_unknownObjectWeakLoadStrong();
                          if (lVar54 != 0) {
                            pcVar59 = (char *)(((double)pmVar48 + 0.0 + dVar55) * 0.5);
                            if (cVar6 == '\0') {
                              pcVar59 = (char *)0x0;
                            }
                            FUN_1007f6c90(0);
                          }
                          IVar22 = (long)&pcVar17->flags + lVar12;
                          _swift_unknownObjectWeakLoadStrong();
                          if (IVar22 == 0) {
                            _swift_release(lVar46);
                            _swift_bridgeObjectRelease(local_1a8);
                            _swift_unknownObjectRelease(pcVar2);
                            pcVar27 = (char *)0x3;
                            _swift_unknownObjectRelease_n(pcVar43,3);
                            goto LAB_1002556e8;
                          }
                          IVar32 = IVar22;
                          __sSd11descriptionSSvg();
                          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                          _swift_bridgeObjectRelease(uVar28);
                          _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                          _swift_release(lVar46);
                          _swift_bridgeObjectRelease(local_1a8);
                          _swift_unknownObjectRelease(pcVar2);
                          pcVar27 = (char *)0x3;
                        }
                        else {
                          if (pcVar40 ==
                              (class_rw_t *)&objc::class_t::_TtC8Playback22PadPlayerMasterChannel)
                          goto LAB_100256c50;
                          if (pcVar40 !=
                              (class_rw_t *)&objc::class_t::_TtC8Playback20PadPlayerFileChannel)
                          goto LAB_100256d8c;
                          cStack_f0.baseMethods = (method_list_t *)0x0;
                          cStack_f0.baseProtocols._0_1_ = '\x01';
                          iVar37 = pcVar43->ivars[3];
                          _swift_unknownObjectRetain(pcVar43);
                          lVar54 = local_1a0;
                          __s8Dispatch0A13WorkItemFlagsV7barrierACvgZ(local_1a0,iVar37);
                          *(method_list_t ***)(lVar51 + -0x10) = &cStack_f0.baseMethods;
                          *(class_rw_t **)(lVar51 + -8) = pcVar43;
                          uVar18 = local_188;
                          __sSo17OS_dispatch_queueC8DispatchE4sync5flags7executexAC0D13WorkItemFlagsV_xyKXEtKlF
                                    (lVar54,FUN_10026e204,lVar51 + -0x20,PTR___sytN_100a1e040 + 8);
                          pcVar47 = *(code **)(local_198 + 8);
                          (*pcVar47)(lVar54,lVar12);
                          cVar8 = (char)cStack_f0.baseProtocols;
                          pmVar48 = cStack_f0.baseMethods;
                          cStack_f0.baseMethods = (method_list_t *)0x0;
                          cStack_f0.baseProtocols._0_1_ = '\x01';
                          __s8Dispatch0A13WorkItemFlagsV7barrierACvgZ(lVar54,pcVar43->ivars[3]);
                          *(method_list_t ***)(lVar51 + -0x10) = &cStack_f0.baseMethods;
                          *(class_rw_t **)(lVar51 + -8) = pcVar43;
                          __sSo17OS_dispatch_queueC8DispatchE4sync5flags7executexAC0D13WorkItemFlagsV_xyKXEtKlF
                                    (lVar54,FUN_10026e218,lVar51 + -0x20,PTR___sytN_100a1e040 + 8);
                          local_188 = uVar18;
                          (*pcVar47)(lVar54,local_180);
                          cVar9 = (char)cStack_f0.baseProtocols;
                          pmVar7 = cStack_f0.baseMethods;
                          pcVar41 = local_1b8;
                          (*(code *)local_1b8->data)(pcVar17);
                          lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
                          cVar6 = *(char *)((long)&local_1b0->flags +
                                           _TtC8Playback14MixerTrackCell::muteState);
                          pcVar58 = pcVar59;
                          if (cVar6 == '\0') {
                            pcVar58 = (char *)0x0;
                          }
                          lVar54 = (long)&local_1b0->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                          _swift_unknownObjectWeakLoadStrong();
                          if (lVar54 != 0) {
                            pmVar57 = (method_list_t *)0x0;
                            if (cVar9 == '\0') {
                              pmVar57 = pmVar7;
                            }
                            dVar55 = 0.0;
                            if (cVar8 == '\0') {
                              dVar55 = (double)pmVar48 + 0.0;
                            }
                            pcVar59 = (char *)(((double)pmVar57 + dVar55) * 0.5);
                            if (cVar6 == '\0') {
                              pcVar59 = (char *)0x0;
                            }
                            FUN_1007f6c90(0);
                          }
                          IVar22 = (long)&local_1b0->flags + lVar12;
                          _swift_unknownObjectWeakLoadStrong();
                          if (IVar22 == 0) {
                            _swift_release(lVar46);
                            _swift_bridgeObjectRelease(local_1a8);
                            _swift_unknownObjectRelease(pcVar2);
                            pcVar27 = (char *)0x4;
                            _swift_unknownObjectRelease_n(pcVar43,4);
                            goto LAB_1002556e8;
                          }
                          IVar32 = IVar22;
                          __sSd11descriptionSSvg();
                          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                          _swift_bridgeObjectRelease(pcVar41);
                          _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                          _swift_release(lVar46);
                          _swift_bridgeObjectRelease(local_1a8);
                          _swift_unknownObjectRelease(pcVar2);
                          pcVar27 = (char *)0x4;
                        }
                        _swift_unknownObjectRelease_n(pcVar43,pcVar27);
                        pcVar59 = pcVar58;
                        goto LAB_1002556e8;
                      }
                      _swift_release(lVar46);
                      _swift_bridgeObjectRelease(local_1a8);
                      pcVar43 = pcVar2;
                    }
                    _swift_unknownObjectRelease(pcVar43);
                    goto LAB_100255680;
                  }
                }
LAB_100256690:
                lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
                if (pcVar17 != (class_rw_t *)0x0) {
                  lVar54 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                  _swift_unknownObjectWeakLoadStrong();
                  if (lVar54 != 0) {
                    pcVar58 = (char *)0x0;
                    FUN_1007f6c90(1);
                  }
                  IVar22 = (long)&pcVar17->flags + lVar12;
                  _swift_unknownObjectWeakLoadStrong();
                  if (IVar22 == 0) {
                    _swift_release(lVar46);
                    _swift_unknownObjectRelease(pcVar2);
                    pcVar59 = pcVar58;
                  }
                  else {
                    pcVar59 = (char *)0x0;
                    IVar32 = IVar22;
                    __sSd11descriptionSSvg();
                    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                    _swift_bridgeObjectRelease(pcVar27);
                    pcVar27 = "setAccessibilityLabel:";
                    _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                    _swift_release(lVar46);
                    _swift_unknownObjectRelease(pcVar2);
                  }
                  goto LAB_1002556e8;
                }
                _swift_release(lVar46);
                goto LAB_100256754;
              }
              pcVar27 = (char *)pcVar2;
              _swift_getObjectType();
              _swift_conformsToProtocol();
              if (((class_rw_t *)pcVar27 == (class_rw_t *)0x0) || (pcVar2 == (class_rw_t *)0x0)) {
                _swift_unknownObjectRelease(pcVar2);
                goto LAB_100255cfc;
              }
              if (pcVar17 == (class_rw_t *)0x0) goto LAB_10025599c;
              pcVar34 = pcVar2;
              _swift_getObjectType();
              ppVar45 = ((class_rw_t *)pcVar27)->baseProtocols;
              _swift_unknownObjectRetain(pcVar2);
              (*(code *)ppVar45)();
              if (pcVar34 == (class_rw_t *)0x0) {
                IVar22 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::trackFader;
                _swift_unknownObjectWeakLoadStrong();
                if (IVar22 != 0) {
                  uVar30 = DAT_100b757a8;
                  FUN_1001711d0(DAT_100b757a8);
                  _objc_msgSend(IVar22,"setExclusiveTouch:",(ulong)((uint)uVar30 & 1));
                  IVar22 = IVar22 + _TtC8Playback15MixerTrackFader::faderBackgroundButton;
                  _swift_unknownObjectWeakLoadStrong();
                  if (IVar22 != 0) {
                    _objc_msgSend(IVar22,"setHidden:",1);
                  }
                }
                lVar12 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                _swift_unknownObjectWeakLoadStrong();
                if (lVar12 == 0) {
                  _swift_unknownObjectRelease_n(pcVar2,2);
                }
                else {
                  *(undefined8 *)(lVar12 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) =
                       0x3fa1111111111111;
                  pcVar59 = (char *)0x0;
                  FUN_1007f6c90(1);
                  _swift_unknownObjectRelease_n(pcVar2,2);
                }
                goto LAB_100255100;
              }
              pcVar40 = pcVar34;
              _swift_getObjectType();
              pcVar43 = pcVar40;
              pcVar23 = (class_rw_t *)pcVar27;
              (*(code *)((class_rw_t *)((long)pcVar27 + 0x48))->weakIvarLayout)();
              lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
              if (((ulong)pcVar43 & 1) == 0) {
                lVar46 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                _swift_unknownObjectWeakLoadStrong();
                pcVar27 = (char *)pcVar23;
                if (lVar46 != 0) {
                  *(undefined8 *)(lVar46 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) =
                       0x3fa1111111111111;
                  pcVar59 = (char *)0x0;
                  FUN_1007f6c90(1);
                  pcVar27 = (char *)pcVar23;
                }
                IVar22 = (long)&pcVar17->flags + lVar12;
                _swift_unknownObjectWeakLoadStrong();
                if (IVar22 == 0) {
                  _swift_unknownObjectRelease(pcVar2);
                  goto LAB_10025623c;
                }
                pcVar58 = (char *)0x0;
                IVar32 = IVar22;
                __sSd11descriptionSSvg();
                __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                _swift_bridgeObjectRelease(pcVar27);
                pcVar27 = "setAccessibilityLabel:";
                _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                _swift_unknownObjectRelease(pcVar2);
              }
              else {
                pcVar47 = (code *)((class_rw_t *)((long)pcVar27 + 0x48))->instanceStart;
                pcVar43 = pcVar40;
                (*pcVar47)(pcVar40,pcVar27);
                uVar18 = local_188;
                __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                          (&cStack_f0.baseMethods,FUN_10026e1bc,pcVar43,&DAT_100a5cf68);
                _swift_release(pcVar43);
                pmVar48 = cStack_f0.baseMethods;
                pcVar43 = pcVar40;
                (*pcVar47)(pcVar40,pcVar27);
                __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                          (&cStack_f0.baseMethods,FUN_10026fbc8,pcVar43,&DAT_100a5cf68);
                _swift_release(pcVar43);
                dVar55 = (double)CONCAT71(cStack_f0.baseProtocols._1_7_,
                                          (char)cStack_f0.baseProtocols);
                uVar30 = DAT_100b757a8;
                FUN_100171178();
                local_188 = uVar18;
                if ((uVar30 & 1) == 0) {
                  bVar10 = false;
                }
                else {
                  pcVar43 = pcVar40;
                  (*(code *)((class_rw_t *)((long)pcVar27 + 0x90))->baseProtocols)(pcVar40,pcVar27);
                  bVar10 = ((uint)pcVar43 & 0xff) == 1;
                }
                (*(code *)((class_rw_t *)((long)pcVar27 + 0x90))->instanceStart)(pcVar40,pcVar27);
                lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
                cVar6 = *(char *)((long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::muteState);
                pcVar58 = pcVar59;
                if (cVar6 == '\0') {
                  pcVar58 = (char *)0x0;
                }
                lVar46 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
                _swift_unknownObjectWeakLoadStrong();
                if (lVar46 != 0) {
                  pcVar59 = (char *)(((double)pmVar48 + 0.0 + dVar55) * 0.5);
                  if (cVar6 == '\0') {
                    pcVar59 = (char *)0x0;
                  }
                  FUN_1007f6c90(bVar10);
                }
                IVar22 = (long)&pcVar17->flags + lVar12;
                _swift_unknownObjectWeakLoadStrong();
                if (IVar22 == 0) {
                  _swift_unknownObjectRelease(pcVar34);
                  pcVar34 = pcVar2;
LAB_10025623c:
                  _swift_unknownObjectRelease(pcVar34);
                  goto LAB_1002556e8;
                }
                IVar32 = IVar22;
                __sSd11descriptionSSvg();
                __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
                _swift_bridgeObjectRelease(pcVar27);
                pcVar27 = "setAccessibilityLabel:";
                _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
                _swift_unknownObjectRelease(pcVar34);
                pcVar34 = pcVar2;
              }
              _swift_unknownObjectRelease(pcVar34);
              pcVar59 = pcVar58;
              goto LAB_1002556e8;
            }
            if (pcVar17 == (class_rw_t *)0x0) {
              (**(code **)(lVar53 + 8))(lVar51,lVar13);
              _swift_unknownObjectRelease(pcVar2);
            }
            else {
              lVar12 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
              _swift_unknownObjectWeakLoadStrong();
              if (lVar12 != 0) {
                *(undefined8 *)(lVar12 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) =
                     0x3fa1111111111111;
                pcVar59 = (char *)0x0;
                FUN_1007f6c90(1);
                _swift_unknownObjectRelease(pcVar2);
                goto LAB_100255100;
              }
LAB_100255680:
              _swift_unknownObjectRelease(pcVar2);
LAB_100255100:
              (**(code **)(lVar53 + 8))(lVar51,lVar13);
            }
            goto LAB_100255110;
          }
          _swift_bridgeObjectRetain(lVar39);
          _swift_bridgeObjectRelease(lVar16);
          goto LAB_100256f24;
        }
      }
    }
  }
  lVar12 = unaff_x20 + _TtC8Playback19MixerViewController::leftVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar12 != 0) {
    FUN_1007f6c90(0,1);
  }
  lVar12 = unaff_x20 + _TtC8Playback19MixerViewController::rightVUMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar12 != 0) {
    FUN_1007f6c90(0,1);
  }
  uVar18 = 0;
  FUN_100250d74();
  return uVar18;
  while( true ) {
    plVar52 = plVar52 + 2;
    lVar54 = lVar54 + -1;
    if (lVar54 == 0) break;
LAB_1002554b4:
    uVar30 = plVar52[-1];
    lVar3 = *plVar52;
    uVar20 = uVar30;
    _swift_getObjectType();
    pcVar47 = *(code **)(lVar3 + 0x28);
    _swift_unknownObjectRetain(uVar30);
    (*pcVar47)(uVar20,lVar3);
    _swift_unknownObjectRelease(uVar30);
    if ((uVar20 & 1) != 0) {
      _swift_release(lVar12);
      _swift_unknownObjectRelease(pcVar34);
      _swift_unknownObjectRelease_n(pcVar2,2);
      _swift_bridgeObjectRelease(lVar39);
      (**(code **)(lVar53 + 8))(lVar51,lVar13);
      pcVar59 = pcVar58;
      local_158 = pcVar17;
      goto LAB_100255110;
    }
  }
  _swift_bridgeObjectRelease(lVar39);
LAB_100255f3c:
  pcVar40 = pcVar34;
  _swift_getObjectType();
  _swift_conformsToProtocol();
  if ((pcVar40 == (class_rw_t *)0x0) || (pcVar34 == (class_rw_t *)0x0)) {
    _swift_unknownObjectRelease(pcVar34);
    _swift_release(lVar12);
    _swift_unknownObjectRelease_n(pcVar2,2);
    pcVar59 = pcVar58;
LAB_100255cfc:
    (**(code **)(lVar53 + 8))(lVar51,lVar13);
    goto LAB_100255110;
  }
  pcVar43 = pcVar34;
  _swift_getObjectType();
  pcVar41 = (class_t *)pcVar40->instanceStart;
  pcVar33 = pcVar41->superclass;
  local_1b0 = pcVar40;
  _swift_unknownObjectRetain();
  pcVar40 = pcVar43;
  local_1b8 = pcVar41;
  local_178 = pcVar34;
  (*(code *)pcVar33)(pcVar43,pcVar41);
  if (((ulong)pcVar40 & 1) == 0) {
    if (pcVar17 == (class_rw_t *)0x0) {
      _swift_release(lVar12);
      pcVar34 = local_178;
    }
    else {
      IVar22 = (long)&pcVar17->flags + _TtC8Playback14MixerTrackCell::vuMeter;
      _swift_unknownObjectWeakLoadStrong();
      pcVar34 = local_178;
      if (IVar22 != 0) {
        pcVar59 = (char *)0x0;
        __sSd11descriptionSSvg(pcVar17);
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
        _swift_bridgeObjectRelease(pcVar41);
        _objc_msgSend(IVar22,"setAccessibilityLabel:",pcVar17);
        _swift_release(lVar12);
        pcVar27 = (char *)0x2;
        _swift_unknownObjectRelease_n(pcVar34,2);
        _swift_unknownObjectRelease(pcVar2);
        goto LAB_1002556e8;
      }
      _swift_release(lVar12);
    }
    pcVar27 = (char *)0x2;
    _swift_unknownObjectRelease_n(pcVar34,2);
LAB_100256754:
    _swift_unknownObjectRelease(pcVar2);
    pcVar59 = pcVar58;
  }
  else {
    uVar30 = DAT_100b757a8;
    local_1c0 = pcVar43;
    FUN_100171178();
    if ((uVar30 & 1) == 0) {
      uVar11 = 0;
    }
    else {
      pcVar34 = local_1a8;
      (**(code **)(lVar46 + 0x28))(local_1a8);
      uVar11 = (uint)pcVar34;
    }
    pcVar40 = local_1b0;
    pcVar34 = local_1c0;
    pcVar47 = (code *)local_1b0->weakIvarLayout;
    (*pcVar47)(local_1c0,local_1b0);
    pcVar50 = (code *)pcVar40[1].instanceStart;
    pcVar59 = pcVar58;
    (*pcVar50)(pcVar34,pcVar40);
    if (pcVar17 != (class_rw_t *)0x0) {
      dVar55 = (double)pcVar58 + 0.0 + (double)pcVar59;
      pcVar59 = (char *)(dVar55 * 0.5);
      (*(code *)local_1b8->data)(pcVar34,local_1b8);
      FUN_1007bc7a8(pcVar59,dVar55,uVar11 & 1);
    }
    FUN_1005c9f20(uVar42,*(undefined8 *)(unaff_x20 + local_190));
    pcVar40 = local_178;
    pcVar34 = local_1b0;
    pcVar17 = local_1c0;
    if ((uVar42 & 1) == 0) {
      _swift_release(lVar12);
      pcVar27 = (char *)0x2;
      _swift_unknownObjectRelease_n(local_178,2);
      _swift_unknownObjectRelease(pcVar2);
    }
    else {
      (*pcVar47)(local_1c0,local_1b0);
      pcVar58 = pcVar59;
      (*pcVar50)(pcVar17,pcVar34);
      pcVar41 = local_1b8;
      pcVar56 = pcVar58;
      if ((double)pcVar58 < (double)pcVar59) {
        pcVar56 = pcVar59;
      }
      pcVar34 = local_1b8->data;
      (*(code *)pcVar34)(pcVar17,local_1b8);
      pcVar56 = (char *)((double)pcVar56 * (double)pcVar58);
      pcVar61 = (char *)((double)pcVar61 + (double)pcVar56);
      (*(code *)pcVar34)(pcVar17,pcVar41);
      pcVar59 = pcVar56;
      _swift_release(lVar12);
      pcVar27 = (char *)0x2;
      _swift_unknownObjectRelease_n(pcVar40,2);
      _swift_unknownObjectRelease(pcVar2);
      pcVar60 = (char *)((double)pcVar60 + (double)pcVar56);
    }
  }
LAB_1002556e8:
  if (local_158 == (class_rw_t *)0x0) {
    (**(code **)(lVar53 + 8))(lVar51,lVar13);
    _swift_unknownObjectRelease(pcVar2);
    local_158 = (class_rw_t *)0x0;
  }
  else {
    uVar30 = DAT_100b757a8;
    FUN_100171178(DAT_100b757a8);
    lVar12 = _TtC8Playback14MixerTrackCell::vuMeter;
    cVar6 = *(char *)((long)&local_158->flags + _TtC8Playback14MixerTrackCell::muteState);
    pcVar58 = pcVar60;
    if (cVar6 == '\0') {
      pcVar58 = (char *)0x0;
    }
    lVar46 = (long)&local_158->flags + _TtC8Playback14MixerTrackCell::vuMeter;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar46 != 0) {
      pcVar59 = pcVar61;
      if (cVar6 == '\0') {
        pcVar59 = (char *)0x0;
      }
      FUN_1007f6c90((uint)uVar30 & 1);
    }
    IVar22 = (long)&local_158->flags + lVar12;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar22 == 0) {
      _swift_unknownObjectRelease(pcVar2);
    }
    else {
      IVar32 = IVar22;
      __sSd11descriptionSSvg();
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
      _swift_bridgeObjectRelease(pcVar27);
      _objc_msgSend(IVar22,"setAccessibilityLabel:",IVar32);
      _swift_unknownObjectRelease(pcVar2);
      pcVar59 = pcVar58;
    }
    (**(code **)(lVar53 + 8))(lVar51,lVar13);
  }
LAB_100255110:
  uVar44 = uVar44 + 1;
  if (uVar44 == uVar29) goto LAB_100256efc;
  goto LAB_100255124;
LAB_100256efc:
  _swift_bridgeObjectRelease(lVar16);
LAB_100256f24:
  _swift_release(lVar14);
  return 0;
}

// ==== 10025eef0 FUN_10025eef0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10025eef0(undefined8 param_1,long param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  long lVar2;
  undefined *puVar3;
  ID IVar4;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::mainStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::waveformViewDummySpacer,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::tracksCollectionView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::panelSeparatorView,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorStackView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorTitleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::errorDescriptionLabel,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorActionButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterPanelButtonStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::modeMultiControlContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::modePageControl,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::modeButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::singleLoopButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::infiniteLoopButton,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::leftVUMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::rightVUMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::masterFader,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::masterFaderLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterFaderCapLeadingSpaceConstraint,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterPanelStackViewTopSpaceConstraint,
             0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::padPanelContainerViewLeftConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButtonWidthConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButtonHeightConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 +
             _TtC8Playback19MixerViewController::padPanelLeadingSpacerViewWidthConstraint,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::isConfigured) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentSetlist) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelViewController) = 0;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::mixerModeMultiControlViewController,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::preEditingModeMixerMode) = 4;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::preEditingModePadExpandedState) =
       2;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentMixerMode) = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentTrackSet);
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 1) = 4;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::collectionViewOffset);
  *puVar1 = 0;
  puVar1[1] = 0;
  lVar2 = _TtC8Playback19MixerViewController::modeScrollViewContentOffsets;
  puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079d1ac();
  *(undefined **)(unaff_x20 + lVar2) = puVar3;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::scrollStartMixerMode) = 4;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::padFadersExpandedState) = 0;
  *(undefined **)(unaff_x20 + _TtC8Playback19MixerViewController::masterClickFollowIndex) =
       PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks) =
       0;
  if (param_2 == 0) {
    _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
    param_1 = 0;
  }
  else {
    _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_1,param_2);
    _swift_bridgeObjectRelease(param_2);
  }
  IVar4 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa0,"initWithNibName:bundle:",
                              param_1,param_3);
  return IVar4;
}

// ==== 10025f2e8 FUN_10025f2e8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10025f2e8(undefined8 param_1)

{
  undefined8 *puVar1;
  long lVar2;
  undefined *puVar3;
  ID IVar4;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::mainStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::waveformViewDummySpacer,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::tracksCollectionView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::panelSeparatorView,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorStackView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorTitleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::errorDescriptionLabel,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::errorActionButton,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterPanelButtonStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::modeMultiControlContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::modePageControl,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::modeButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::singleLoopButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::infiniteLoopButton,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::leftVUMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::rightVUMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::masterFader,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback19MixerViewController::masterFaderLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterFaderCapLeadingSpaceConstraint,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::masterPanelStackViewTopSpaceConstraint,
             0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::padPanelContainerViewLeftConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButtonWidthConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::muteMIDIButtonHeightConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 +
             _TtC8Playback19MixerViewController::padPanelLeadingSpacerViewWidthConstraint,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::isConfigured) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentSetlist) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::mixerPadPanelViewController) = 0;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback19MixerViewController::mixerModeMultiControlViewController,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::preEditingModeMixerMode) = 4;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::preEditingModePadExpandedState) =
       2;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentMixerMode) = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::currentTrackSet);
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 1) = 4;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::collectionViewOffset);
  *puVar1 = 0;
  puVar1[1] = 0;
  lVar2 = _TtC8Playback19MixerViewController::modeScrollViewContentOffsets;
  puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
  FUN_10079d1ac();
  *(undefined **)(unaff_x20 + lVar2) = puVar3;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::scrollStartMixerMode) = 4;
  *(undefined1 *)(unaff_x20 + _TtC8Playback19MixerViewController::padFadersExpandedState) = 0;
  *(undefined **)(unaff_x20 + _TtC8Playback19MixerViewController::masterClickFollowIndex) =
       PTR___swiftEmptySetSingleton_100a1e060;
  *(undefined8 *)(unaff_x20 + _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks) =
       0;
  _swift_retain();
  IVar4 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"initWithCoder:",param_1);
  return IVar4;
}

// ==== 100545a98 FUN_100545a98 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_100545a98(double param_1,ID param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  ID IVar4;
  long lVar5;
  undefined1 *self;
  ulong uVar6;
  undefined *puVar7;
  ID IVar8;
  ID IVar9;
  char *pcVar10;
  long lVar11;
  uint uVar12;
  undefined8 *unaff_x20;
  undefined *puVar13;
  undefined8 *puVar14;
  double dVar15;
  undefined1 auStack_100 [8];
  long local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  
  local_e8 = *unaff_x20;
  lVar1 = 0;
  local_e0 = param_4;
  local_d8 = param_5;
  __s10Foundation3URLVMa();
  lVar11 = *(long *)(lVar1 + -8);
  self = auStack_100 + -(*(long *)(lVar11 + 0x40) + 0xfU & 0xfffffffffffffff0);
  unaff_x20[4] = 0;
  _swift_unknownObjectWeakInit(unaff_x20 + 3,0);
  *(undefined2 *)(unaff_x20 + 6) = 0;
  *(undefined1 *)((long)unaff_x20 + 0x32) = 1;
  *(undefined1 *)(unaff_x20 + 8) = 1;
  unaff_x20[9] = 0x3ff0000000000000;
  uVar2 = 0;
  FUN_1000ef300();
  _swift_allocObject();
  FUN_1000ef5c8();
  unaff_x20[10] = uVar2;
  *(undefined1 *)(unaff_x20 + 0xb) = 1;
  *(undefined1 *)(unaff_x20 + 0xd) = 1;
  unaff_x20[0xe] = 0;
  unaff_x20[0xf] = 0;
  lVar5 = _TtC8Playback12ClickChannel::meterStartDate;
  lVar3 = 0;
  __s10Foundation4DateVMa();
  puVar14 = (undefined8 *)((long)unaff_x20 + lVar5);
  (**(code **)(*(long *)(lVar3 + -8) + 0x38))(puVar14,1,1,lVar3);
  *(undefined1 *)
   ((long)unaff_x20 + _TtC8Playback12ClickChannel::currentElementIsLastSongMapElementEnding) = 0;
  if (DAT_100adef08 != -1) {
    puVar14 = &DAT_100adef08;
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if (*(long *)(DAT_100b75e40 + 0x20) == 0) {
    FUN_100546c10();
    _swift_allocError(&DAT_100a504a8,puVar14,0,0);
    puVar13 = (undefined *)0x0;
  }
  else {
    local_f8 = lVar1;
    uStack_f0 = param_3;
    IVar4 = _objc_msgSend(param_2,"partID");
    if (IVar4 != 0) {
      IVar4 = _objc_msgSend(IVar4,"integerValue");
      lVar5 = 0;
      FUN_1000c6320();
      if (lVar5 != 0) {
        (**(code **)(lVar11 + 0x10))(self,uStack_f0,local_f8);
        FUN_1001de8bc(0);
        _objc_allocWithZone();
        uVar2 = local_d8;
        _swift_unknownObjectRetain(local_d8);
        FUN_1001de0f4(self,lVar5,uVar2,param_6,0);
        unaff_x20[0xc] = self;
        _objc_msgSend(*(ID *)(DAT_100b75e40 + 0x10),"attachNode:",self);
        unaff_x20[2] = IVar4;
        unaff_x20[5] = param_2;
        uVar6 = _objc_msgSend(param_2,"arrangement");
        if (uVar6 == 0) {
          uVar12 = 0;
        }
        else {
          FUN_1002dbb48();
          uVar12 = 0;
          if (uVar6 != 0) {
            if (DAT_100adfbd0 != -1) {
              _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            }
            uVar2 = DAT_100b77550;
            _swift_retain(DAT_100b77550);
            FUN_1005ecd4c(uVar6,0);
            _swift_release(uVar2);
            uVar2 = DAT_100b77550;
            if ((uVar6 & 1) == 0) {
              uVar12 = 0;
            }
            else {
              _swift_retain(DAT_100b77550);
              IVar4 = param_2;
              FUN_1005ecd4c(param_2,0);
              uVar12 = (uint)IVar4;
              _swift_release(uVar2);
            }
          }
        }
        FUN_1001de044(uVar12 & 1);
        *(char *)((long)unaff_x20 + 0x32) = (char)(uVar12 & 1);
        IVar4 = _objc_msgSend(param_2,"arrangement");
        dVar15 = 0.0;
        if ((IVar4 != 0) && (FUN_1002dbb48(), IVar4 != 0)) {
          dVar15 = param_1;
          if (DAT_100adfbd0 != -1) {
            _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            dVar15 = param_1;
          }
          uVar2 = DAT_100b77550;
          _swift_retain(DAT_100b77550);
          FUN_100654f08(IVar4,0,0);
          param_1 = dVar15;
          _swift_release(uVar2);
        }
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        uVar2 = DAT_100b77550;
        _swift_retain(DAT_100b77550);
        FUN_100654f08(param_2,0,0);
        _swift_release(uVar2);
        unaff_x20[7] = param_1;
        uVar6 = (ulong)(uint)(float)(dVar15 * param_1);
        IVar4 = _objc_msgSend((ID)self,"setVolume:");
        FUN_1000c5c34();
        uVar2 = DAT_100b77550;
        if (IVar4 != 0) {
          _swift_retain(DAT_100b77550);
          IVar8 = IVar4;
          FUN_1005e99e0(IVar4,0);
          _swift_release(uVar2);
          *(byte *)(unaff_x20 + 8) = (byte)IVar8 & 1;
          uVar2 = DAT_100b77550;
          _swift_retain(DAT_100b77550);
          FUN_100654efc(IVar4,0,0);
          _swift_release(uVar2);
          unaff_x20[9] = uVar6;
        }
        FUN_1001de044(*(byte *)((long)unaff_x20 + 0x32) & *(byte *)(unaff_x20 + 0xd) &
                      *(byte *)(unaff_x20 + 8) & 1);
        FUN_100545974(0,1,0,1);
        _swift_unknownObjectRelease(local_d8);
        (**(code **)(lVar11 + 8))(uStack_f0,local_f8);
        return;
      }
    }
    IVar4 = 0x3e6c696e3c;
    puVar7 = &DAT_100af5338;
    FUN_100021774();
    _swift_initStackObject();
    *(undefined8 *)(puVar7 + 0x18) = 4;
    *(undefined8 *)(puVar7 + 0x10) = 2;
    puVar14 = (undefined8 *)(puVar7 + 0x20);
    *puVar14 = &DAT_444974726170;
    *(undefined8 *)(puVar7 + 0x28) = 0xe600000000000000;
    IVar8 = _objc_msgSend(param_2,"partID");
    if (IVar8 == 0) {
      pcVar10 = &DAT_e500000000000000;
      IVar8 = IVar4;
    }
    else {
      pcVar10 = "description";
      IVar8 = _objc_msgSend(IVar8,"description");
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
    IVar9 = 0;
    *(ID *)(puVar7 + 0x30) = IVar8;
    *(char **)(puVar7 + 0x38) = pcVar10;
    *(undefined8 *)(puVar7 + 0x40) = 0x6d69546b63696c63;
    *(undefined8 *)(puVar7 + 0x48) = 0xea00000000007365;
    FUN_1000c6320();
    param_3 = uStack_f0;
    lVar1 = local_f8;
    if (IVar9 == 0) {
      puVar13 = &DAT_e500000000000000;
    }
    else {
      IVar4 = IVar9;
      puVar13 = PTR___sSdN_100a1dd60;
      __sSa11descriptionSSvg();
      _swift_bridgeObjectRelease(IVar9);
    }
    *(ID *)(puVar7 + 0x50) = IVar4;
    *(undefined **)(puVar7 + 0x58) = puVar13;
    puVar13 = puVar7;
    FUN_10079bfc8();
    _swift_setDeallocating(puVar7);
    puVar7 = &DAT_100af5340;
    FUN_100021774(&DAT_100af5340);
    _swift_arrayDestroy(puVar14,2,puVar7);
    FUN_100546c10();
    _swift_allocError(&DAT_100a504a8,puVar14,0,0);
  }
  *puVar14 = puVar13;
  _swift_willThrow();
  _swift_unknownObjectRelease(local_d8);
  (**(code **)(lVar11 + 8))(param_3,lVar1);
  FUN_100026610(unaff_x20 + 3);
  _swift_release(unaff_x20[10]);
  FUN_100023be4((long)unaff_x20 + _TtC8Playback12ClickChannel::meterStartDate,&DAT_100af56b8);
  _swift_deallocPartialClassInstance();
  return;
}

// ==== 1005461dc FUN_1005461dc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1005461dc(void)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined *puVar3;
  undefined8 uVar4;
  long unaff_x20;
  undefined8 uVar5;
  
  uVar1 = _objc_msgSend(*(ID *)(unaff_x20 + 0x60),"engine");
  if (uVar1 != 0) {
    FUN_1001c4c9c(0);
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar1,*(undefined8 *)(DAT_100b75e40 + 0x10));
    if ((uVar1 & 1) != 0) {
      _objc_msgSend(*(ID *)(DAT_100b75e40 + 0x10),"detachNode:",*(undefined8 *)(unaff_x20 + 0x60));
      goto LAB_100546314;
    }
  }
  uVar2 = 0;
  __sSo13os_log_type_ta0A0E4infoABvgZ(0);
  puVar3 = &DAT_100af52c8;
  FUN_100021774();
  _swift_initStackObject();
  *(undefined8 *)(puVar3 + 0x18) = 2;
  *(undefined8 *)(puVar3 + 0x10) = 1;
  uVar5 = *(undefined8 *)(unaff_x20 + 0x60);
  uVar4 = 0;
  FUN_1001de8bc();
  *(undefined8 *)(puVar3 + 0x38) = uVar4;
  FUN_100546c70();
  *(undefined8 *)(puVar3 + 0x40) = uVar4;
  *(undefined8 *)(puVar3 + 0x20) = uVar5;
  FUN_10041ac94(uVar2,0x13,"ALERT: Detaching %@ from Audio Engine failed",0x2c,2,puVar3);
  _swift_setDeallocating(puVar3);
  FUN_100023468(puVar3 + 0x20);
LAB_100546314:
  FUN_100026610(unaff_x20 + 0x18);
  _swift_release(*(undefined8 *)(unaff_x20 + 0x50));
  FUN_100023be4(unaff_x20 + _TtC8Playback12ClickChannel::meterStartDate,&DAT_100af56b8);
  return;
}

// ==== 1005468f4 FUN_1005468f4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1005468f4(double param_1,ID param_2,undefined8 param_3,long param_4)

{
  long lVar1;
  undefined1 *puVar2;
  long lVar3;
  undefined *puVar4;
  ID IVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  code *pcVar13;
  double dVar14;
  undefined1 auStack_b0 [8];
  undefined1 *local_a8;
  undefined1 auStack_a0 [24];
  undefined1 auStack_88 [24];
  
  lVar3 = 0;
  __s10Foundation4DateVMa();
  lVar9 = *(long *)(lVar3 + -8);
  uVar7 = *(long *)(lVar9 + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_a8 = auStack_b0 + -uVar7;
  uVar11 = (long)local_a8 - uVar7;
  lVar8 = uVar11 - uVar7;
  puVar4 = &DAT_100af56b8;
  FUN_100021774();
  uVar7 = *(long *)(*(long *)(puVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar12 = lVar8 - uVar7;
  lVar10 = lVar12 - uVar7;
  IVar5 = _objc_msgSend(param_2,"format");
  IVar5 = _objc_msgSend(IVar5,"channelCount");
  if ((int)IVar5 != 0) {
    FUN_10012d330(0);
    dVar14 = param_1;
    FUN_10012d330(1);
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar7 = DAT_100b757a8;
    FUN_100171178();
    if ((uVar7 & 1) == 0) {
      FUN_10004bcf8(param_1,0);
      FUN_10004bd14(dVar14);
    }
    else {
      if ((*(double *)(param_4 + 0x70) == 0.0) && (0.0 < param_1 + dVar14)) {
        __s10Foundation4DateVACycfC(lVar10);
        (**(code **)(lVar9 + 0x38))(lVar10,0,1,lVar3);
        lVar1 = _TtC8Playback12ClickChannel::meterStartDate;
        _swift_beginAccess(param_4 + _TtC8Playback12ClickChannel::meterStartDate,auStack_88,0x21,0);
        FUN_1000c3024(lVar10,param_4 + lVar1);
        _swift_endAccess(auStack_88);
        FUN_10004bcf8(0x3ff0000000000000);
        FUN_10004bd14(0x3ff0000000000000);
      }
      lVar1 = _TtC8Playback12ClickChannel::meterStartDate;
      _swift_beginAccess(param_4 + _TtC8Playback12ClickChannel::meterStartDate,auStack_88,0,0);
      FUN_10003fb00(param_4 + lVar1,lVar12);
      lVar6 = lVar12;
      (**(code **)(lVar9 + 0x30))(lVar12,1,lVar3);
      if ((int)lVar6 == 1) {
        FUN_100023be4(lVar12,&DAT_100af56b8);
      }
      else {
        (**(code **)(lVar9 + 0x20))(lVar8,lVar12,lVar3);
        __s10Foundation4DateV18addingTimeIntervalyACSdF(uVar11,0x3fa999999999999a);
        puVar2 = local_a8;
        __s10Foundation4DateVACycfC(local_a8);
        uVar7 = uVar11;
        __s10Foundation4DateV1loiySbAC_ACtFZ(uVar11,puVar2);
        pcVar13 = *(code **)(lVar9 + 8);
        (*pcVar13)(puVar2,lVar3);
        (*pcVar13)(uVar11,lVar3);
        if ((uVar7 & 1) != 0) {
          (**(code **)(lVar9 + 0x38))(lVar10,1,1,lVar3);
          _swift_beginAccess(param_4 + lVar1,auStack_a0,0x21,0);
          FUN_1000c3024(lVar10,param_4 + lVar1);
          _swift_endAccess(auStack_a0);
          FUN_10004bcf8(0);
          FUN_10004bd14(0);
        }
        (*pcVar13)(lVar8,lVar3);
      }
      *(double *)(param_4 + 0x70) = param_1 + dVar14;
    }
  }
  return;
}

// ==== 100746c6c FUN_100746c6c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_100746c6c(ID param_1,ID param_2,long param_3,undefined8 param_4,long param_5,
                  undefined8 param_6)

{
  undefined8 *puVar1;
  undefined *puVar2;
  code *pcVar3;
  undefined1 *puVar4;
  ID IVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  undefined *puVar10;
  long lVar11;
  ID self;
  ID IVar12;
  undefined8 uVar13;
  char *pcVar14;
  undefined1 *puVar15;
  long lVar16;
  undefined8 local_80;
  ulong uStack_78;
  
  puVar4 = (undefined1 *)0x0;
  FUN_1000cda74();
  IVar5 = param_1;
  _swift_dynamicCastClass(param_1,puVar4);
  if (IVar5 == 0) {
    FUN_100286674();
    IVar12 = param_1;
    _swift_dynamicCastClass(param_1,IVar5);
    if (IVar12 != 0) {
      _swift_unknownObjectRetain(param_1);
      IVar5 = _objc_msgSend(IVar12,"partID");
      uVar6 = (ulong)(int)IVar5;
      FUN_10056fe0c();
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      switch(uVar6 & 0xff) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      case 0xb:
        break;
      case 0xc:
        break;
      case 0xd:
        break;
      case 0xe:
        break;
      case 0xf:
        pcVar14 = "MixerTrackFaderPadCell_";
        uVar7 = 0xd000000000000017;
LAB_100746e18:
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                  (uVar7,(ulong)pcVar14 | 0x8000000000000000);
        _objc_msgSend(param_2,"setAccessibilityIdentifier:",uVar7);
        goto LAB_10074708c;
      case 0x10:
        goto switchD_100746d94_caseD_10;
      }
switchD_100746d94_caseD_10:
      pcVar14 = "MixerTrackFaderPadCell_";
      goto LAB_100747024;
    }
    _objc_msgSend(param_2,"setAccessibilityIdentifier:",0);
  }
  else {
    _swift_unknownObjectRetain(param_1);
    IVar5 = _objc_msgSend(IVar5,"partID");
    if (IVar5 == 0) {
LAB_100746da4:
      puVar10 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
      __ss23CustomStringConvertibleP11descriptionSSvgTj
                (PTR___sSiN_100a1dd88,PTR___sSis23CustomStringConvertiblesWP_100a1dda8);
      local_80 = 0x617254726578694d;
      uStack_78 = 0xef5f6c6c65436b63;
    }
    else {
      IVar5 = _objc_msgSend(IVar5,"integerValue");
      if ((long)IVar5 < 0x4e3) {
        if (IVar5 == 0x2c) {
          uVar7 = 0xd000000000000019;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                    (0xd000000000000019,0x8000000100909ce0);
          _objc_msgSend(param_2,"setAccessibilityIdentifier:",uVar7);
          if (DAT_100adea10 != -1) {
            _swift_once(&DAT_100adea10,FUN_1001709a4);
          }
          uVar7 = DAT_100b757a8;
          FUN_10016fd54();
          IVar5 = param_2 + _TtC8Playback14MixerTrackCell::muteButton;
          _swift_unknownObjectWeakLoadStrong();
          if (((uint)uVar7 & 0xff) < 2) {
            if ((IVar5 != 0) && (IVar5 = _objc_msgSend(IVar5,"titleLabel"), IVar5 != 0)) {
              uVar7 = 0x4320726576726553;
              uVar13 = 0xec0000006b63696c;
              goto LAB_100746f64;
            }
          }
          else if ((IVar5 != 0) && (IVar5 = _objc_msgSend(IVar5,"titleLabel"), IVar5 != 0)) {
            uVar7 = 0x6e492d746c697542;
            uVar13 = 0xee006b63696c4320;
LAB_100746f64:
            __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar13);
            _objc_msgSend(IVar5,"setAccessibilityValue:",uVar7);
          }
          goto LAB_10074708c;
        }
        if ((IVar5 == 0x33) || (IVar5 == 0x4bd)) {
          pcVar14 = "MixerTrackPadMasterCell";
          uVar7 = 0xd000000000000013;
          goto LAB_100746e18;
        }
        goto LAB_100746da4;
      }
      if (3 < IVar5 - 0x4e3) goto LAB_100746da4;
      pcVar14 = "MixerTrackSubclickCell_";
LAB_100747024:
      uStack_78 = (ulong)(pcVar14 + -0x20) | 0x8000000000000000;
      puVar10 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
      __ss23CustomStringConvertibleP11descriptionSSvgTj
                (PTR___sSiN_100a1dd88,PTR___sSis23CustomStringConvertiblesWP_100a1dda8);
      local_80 = 0xd000000000000017;
    }
    __sSS6appendyySSF();
    _swift_bridgeObjectRelease(puVar10);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(local_80,uStack_78);
    _swift_bridgeObjectRelease(uStack_78);
    _objc_msgSend(param_2,"setAccessibilityIdentifier:",local_80);
  }
LAB_10074708c:
  lVar11 = _TtC8Playback14MixerTrackCell::trackFader;
  IVar5 = param_2 + _TtC8Playback14MixerTrackCell::trackFader;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setIsAccessibilityElement:",0);
  }
  IVar5 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    uVar7 = 0x617254726578694d;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x617254726578694d,0xef72656461466b63);
    _objc_msgSend(IVar5,"setAccessibilityIdentifier:",uVar7);
  }
  lVar8 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar8 != 0) {
    IVar5 = lVar8 + _TtC8Playback15MixerTrackFader::faderCapView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar5 != 0) {
      puVar15 = (undefined1 *)0xec000000656d756c;
      lVar16 = 0x6f76206b63617254;
      lVar8 = param_2 + _TtC8Playback14MixerTrackCell::identifiableTrack;
      _swift_unknownObjectWeakLoadStrong();
      if ((lVar8 != 0) && (lVar9 = lVar8, _swift_dynamicCastClass(), lVar9 != 0)) {
        FUN_1000c4c18();
        lVar16 = 0x6b63617254;
        if (puVar4 != (undefined1 *)0x0) {
          lVar16 = lVar8;
        }
        puVar15 = &DAT_e500000000000000;
        if (puVar4 != (undefined1 *)0x0) {
          puVar15 = puVar4;
        }
        _swift_bridgeObjectRetain(puVar15);
        __sSS6appendyySSF(0x656d756c6f7620,0xe700000000000000);
        _swift_bridgeObjectRelease(puVar15);
      }
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(lVar16,puVar15);
      _swift_bridgeObjectRelease(puVar15);
      _objc_msgSend(IVar5,"setAccessibilityValue:",lVar16);
    }
  }
  lVar8 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar8 != 0) {
    IVar5 = lVar8 + _TtC8Playback15MixerTrackFader::faderCapView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar5 != 0) {
      puVar10 = &DAT_100af52c8;
      FUN_100021774();
      _swift_allocObject();
      *(undefined8 *)(puVar10 + 0x18) = 2;
      *(undefined8 *)(puVar10 + 0x10) = 1;
      lVar8 = param_2 + lVar11;
      _swift_unknownObjectWeakLoadStrong();
      puVar2 = PTR___sSds7CVarArgsWP_100a1dd78;
      if (lVar8 == 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x100747674);
        (*pcVar3)();
      }
      uVar7 = *(undefined8 *)(lVar8 + _TtC8Playback15MixerTrackFader::volume);
      *(undefined **)(puVar10 + 0x38) = PTR___sSdN_100a1dd60;
      *(undefined **)(puVar10 + 0x40) = puVar2;
      *(undefined8 *)(puVar10 + 0x20) = uVar7;
      uVar7 = 0x66322e25;
      uVar13 = 0xe400000000000000;
      __sSS10FoundationE6format_S2Sh_s7CVarArg_pdtcfC(0x66322e25,0xe400000000000000,puVar10);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
      _swift_bridgeObjectRelease(uVar13);
      _objc_msgSend(IVar5,"setAccessibilityLabel:",uVar7);
    }
  }
  lVar8 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar8 != 0) {
    lVar8 = lVar8 + _TtC8Playback15MixerTrackFader::faderCapView;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar8 != 0) {
      _swift_allocObject(param_5,0x18,7);
      *(ID *)(param_5 + 0x10) = param_2;
      puVar1 = (undefined8 *)(lVar8 + _TtC8Playback22MixerTrackFaderCapView::incrementAction);
      uVar7 = *puVar1;
      uVar13 = puVar1[1];
      *puVar1 = param_6;
      puVar1[1] = param_5;
      FUN_1000274b4(uVar7,uVar13);
    }
  }
  lVar11 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar11 != 0) {
    lVar11 = lVar11 + _TtC8Playback15MixerTrackFader::faderCapView;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar11 != 0) {
      _swift_allocObject(param_3,0x18,7);
      *(ID *)(param_3 + 0x10) = param_2;
      puVar1 = (undefined8 *)(lVar11 + _TtC8Playback22MixerTrackFaderCapView::decrementAction);
      uVar7 = *puVar1;
      uVar13 = puVar1[1];
      *puVar1 = param_4;
      puVar1[1] = param_3;
      FUN_1000274b4(uVar7,uVar13);
    }
  }
  IVar5 = param_2 + _TtC8Playback14MixerTrackCell::vuMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 == 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x100747670);
    (*pcVar3)();
  }
  uVar7 = 0xd000000000000011;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000011,0x8000000100909c20);
  _objc_msgSend(IVar5,"setAccessibilityIdentifier:",uVar7);
  lVar11 = _TtC8Playback14MixerTrackCell::muteButton;
  IVar5 = param_2 + _TtC8Playback14MixerTrackCell::muteButton;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar5 != 0) && (IVar5 = _objc_msgSend(IVar5,"titleLabel"), IVar5 != 0)) {
    _objc_msgSend(IVar5,"setIsAccessibilityElement:",1);
  }
  IVar5 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar5 != 0) && (IVar5 = _objc_msgSend(IVar5,"titleLabel"), IVar5 != 0)) {
    uVar7 = 0xd000000000000014;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000014,0x8000000100909c40);
    _objc_msgSend(IVar5,"setAccessibilityIdentifier:",uVar7);
  }
  IVar5 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 == 0) {
    return;
  }
  IVar5 = _objc_msgSend(IVar5,"titleLabel");
  if (IVar5 == 0) {
    return;
  }
  param_2 = param_2 + lVar11;
  _swift_unknownObjectWeakLoadStrong();
  if (param_2 != 0) {
    self = _objc_msgSend(param_2,"titleLabel");
    IVar12 = 0;
    if (self == 0) goto LAB_10074760c;
    pcVar14 = "text";
    IVar12 = _objc_msgSend(self,"text");
    if (IVar12 != 0) {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(IVar12);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar12,pcVar14);
      _swift_bridgeObjectRelease(pcVar14);
      goto LAB_10074760c;
    }
  }
  IVar12 = 0;
LAB_10074760c:
  _objc_msgSend(IVar5,"setAccessibilityLabel:",IVar12);
  return;
}

// ==== 1007bc7a8 FUN_1007bc7a8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_1007bc7a8(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4)

{
  char cVar1;
  long lVar2;
  long lVar3;
  ID self;
  ID IVar4;
  long unaff_x20;
  
  lVar2 = _TtC8Playback14MixerTrackCell::vuMeter;
  cVar1 = *(char *)(unaff_x20 + _TtC8Playback14MixerTrackCell::muteState);
  if (cVar1 == '\0') {
    param_2 = 0;
  }
  lVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::vuMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    if (cVar1 == '\0') {
      param_1 = 0;
    }
    FUN_1007f6c90(param_1,param_3 & 1);
  }
  self = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (self != 0) {
    IVar4 = self;
    __sSd11descriptionSSvg(param_2);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease(param_4);
    _objc_msgSend(self,"setAccessibilityLabel:",IVar4);
    return 0;
  }
  return 0;
}

// ==== 1007bcbd4 _TtC8Playback14MixerTrackCell::soloVUMeterContainterView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback14MixerTrackCell::soloVUMeterContainterView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + soloVUMeterContainterView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1007bcbf4 _TtC8Playback14MixerTrackCell::setSoloVUMeterContainterView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback14MixerTrackCell::setSoloVUMeterContainterView_(ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + soloVUMeterContainterView,param_3);
  return;
}

// ==== 1007bcc3c _TtC8Playback14MixerTrackCell::vuMeter ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback14MixerTrackCell::vuMeter(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + vuMeter;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 1007bcc5c _TtC8Playback14MixerTrackCell::setVuMeter: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback14MixerTrackCell::setVuMeter_(ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + vuMeter,param_3);
  return;
}

// ==== 1007bd11c FUN_1007bd11c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007bd11c(void)

{
  code *pcVar1;
  int iVar2;
  undefined *puVar3;
  ID IVar5;
  long lVar6;
  ID unaff_x20;
  undefined8 uVar7;
  ID IVar4;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff90,"awakeFromNib");
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::faderCapLeadingConstraint;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    puVar3 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    IVar4 = _objc_msgSend((ID)puVar3,"currentDevice");
    iVar2 = (int)IVar4;
    FUN_100826670();
    uVar7 = 0xc00c000000000000;
    if (0xd < (iVar2 - 0xcU & 0xff)) {
      uVar7 = 0xc012000000000000;
    }
    _objc_msgSend(IVar5,"setConstant:",uVar7);
  }
  lVar6 = _TtC8Playback14MixerTrackCell::trackFader;
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trackFader;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    IVar5 = _objc_msgSend(IVar5,"layer");
    _objc_msgSend(IVar5,"setCornerRadius:",0x4018000000000000);
  }
  lVar6 = unaff_x20 + lVar6;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar6 != 0) {
    lVar6 = lVar6 + _TtC8Playback15MixerTrackFader::delegate;
    *(undefined ***)(lVar6 + 8) = &PTR_PTR_100a66a68;
    _swift_unknownObjectWeakAssign(lVar6);
  }
  lVar6 = unaff_x20 + _TtC8Playback14MixerTrackCell::trackExpandedLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar6 != 0) {
    IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::muteButtonStackView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"sendSubviewToBack:",lVar6);
    }
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",0);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",0);
  }
  lVar6 = _TtC8Playback14MixerTrackCell::leadingShadowView;
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    *(undefined1 *)(IVar5 + _TtC8Playback18ShadowGradientView::direction) = 3;
    _objc_msgSend(IVar5,"setNeedsDisplay");
  }
  IVar5 = unaff_x20 + lVar6;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  lVar6 = _TtC8Playback14MixerTrackCell::trailingShadowView;
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    *(undefined1 *)(IVar5 + _TtC8Playback18ShadowGradientView::direction) = 4;
    _objc_msgSend(IVar5,"setNeedsDisplay");
  }
  IVar5 = unaff_x20 + lVar6;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::faderControlStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    lVar6 = unaff_x20 + _TtC8Playback14MixerTrackCell::soloVUMeterContainterView;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar6 == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x1007bd5cc);
      (*pcVar1)();
    }
    _objc_msgSend(IVar5,"bringSubviewToFront:",lVar6);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::muteButtonStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    IVar5 = _objc_msgSend(IVar5,"layer");
    _objc_msgSend(IVar5,"setCornerRadius:",0x4010000000000000);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::genreMarkerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::previewInfoButtonWidthConstraint;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    puVar3 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    IVar4 = _objc_msgSend((ID)puVar3,"currentDevice");
    IVar4 = _objc_msgSend(IVar4,"userInterfaceIdiom");
    uVar7 = 0x4031000000000000;
    if (IVar4 != 0) {
      uVar7 = 0x4036000000000000;
    }
    _objc_msgSend(IVar5,"setConstant:",uVar7);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::rentalPreviewInfoButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  _objc_msgSend(unaff_x20,"setClipsToBounds:",0);
  return;
}

// ==== 1007bd5f4 FUN_1007bd5f4 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1007bd5f4(void)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ID IVar5;
  undefined8 uVar6;
  ID unaff_x20;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"prepareForReuse");
  lVar4 = unaff_x20 + _TtC8Playback14MixerTrackCell::delegate;
  *(undefined8 *)(lVar4 + 8) = 0;
  _swift_unknownObjectWeakAssign(lVar4,0);
  lVar4 = unaff_x20 + _TtC8Playback14MixerTrackCell::identifiableTrack;
  *(undefined8 *)(lVar4 + 8) = 0;
  _swift_unknownObjectWeakAssign(lVar4,0);
  lVar1 = _TtC8Playback14MixerTrackCell::trackFader;
  lVar2 = unaff_x20 + _TtC8Playback14MixerTrackCell::trackFader;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    lVar3 = lVar4;
    _swift_unknownObjectWeakLoadStrong(lVar4);
    lVar2 = lVar2 + _TtC8Playback15MixerTrackFader::identifiableTrack;
    *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(lVar4 + 8);
    _swift_unknownObjectWeakAssign(lVar2,lVar3);
  }
  lVar4 = unaff_x20 + _TtC8Playback14MixerTrackCell::muteButton;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar4 != 0) {
    lVar4 = lVar4 + _TtC8Playback20MixerTrackMuteButton::track;
    *(undefined8 *)(lVar4 + 8) = 0;
    _swift_unknownObjectWeakAssign(lVar4,0);
  }
  lVar4 = unaff_x20 + lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar4 != 0) {
    lVar4 = lVar4 + _TtC8Playback15MixerTrackFader::identifiableTrack;
    *(undefined8 *)(lVar4 + 8) = 0;
    _swift_unknownObjectWeakAssign(lVar4,0);
  }
  lVar4 = unaff_x20 + lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar4 != 0) {
    FUN_1007a9ac0(0);
  }
  IVar5 = unaff_x20 + lVar1;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar6 = DAT_100b757a8;
    FUN_1001711d0(DAT_100b757a8);
    _objc_msgSend(IVar5,"setExclusiveTouch:",(ulong)((uint)uVar6 & 1));
    IVar5 = IVar5 + _TtC8Playback15MixerTrackFader::faderBackgroundButton;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setHidden:",1);
    }
  }
  lVar4 = unaff_x20 + _TtC8Playback14MixerTrackCell::vuMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar4 != 0) {
    *(undefined8 *)(lVar4 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) = 0x3fa1111111111111;
    FUN_1007f6c90(0,1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",0);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",0);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  lVar4 = _TtC8Playback14MixerTrackCell::expandSubtracksButton;
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::expandSubtracksButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + lVar4;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setSelected:",0);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::genreMarkerView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  IVar5 = unaff_x20 + _TtC8Playback14MixerTrackCell::rentalPreviewInfoButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar5 != 0) {
    _objc_msgSend(IVar5,"setHidden:",1);
  }
  _objc_msgSend(unaff_x20,"setHidden:",0);
  return;
}

// ==== 1007be5c0 FUN_1007be5c0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_1007be5c0(void)

{
  code *pcVar1;
  long lVar2;
  ID IVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  ulong *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  ID unaff_x20;
  undefined *puVar11;
  undefined *puVar12;
  
  if (DAT_100adff10 != -1) {
    _swift_once(&DAT_100adff10,FUN_1007c0580);
  }
  _objc_msgSend(unaff_x20,"setBackgroundColor:",DAT_100b77c78);
  lVar2 = unaff_x20 + _TtC8Playback14MixerTrackCell::vuMeter;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    *(undefined8 *)(lVar2 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) = 0x3fa1111111111111;
    FUN_1007f6c90(0,1);
  }
  lVar2 = _TtC8Playback14MixerTrackCell::trackFader;
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::trackFader;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar7 = DAT_100b757a8;
    FUN_1001711d0(DAT_100b757a8);
    _objc_msgSend(IVar3,"setExclusiveTouch:",(ulong)((uint)uVar7 & 1));
    IVar3 = IVar3 + _TtC8Playback15MixerTrackFader::faderBackgroundButton;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar3 != 0) {
      _objc_msgSend(IVar3,"setHidden:",1);
    }
  }
  lVar6 = unaff_x20 + _TtC8Playback14MixerTrackCell::identifiableTrack;
  *(undefined8 *)(lVar6 + 8) = 0;
  _swift_unknownObjectWeakAssign(lVar6,0);
  lVar4 = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar4 != 0) {
    lVar5 = lVar6;
    _swift_unknownObjectWeakLoadStrong(lVar6);
    lVar4 = lVar4 + _TtC8Playback15MixerTrackFader::identifiableTrack;
    *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(lVar6 + 8);
    _swift_unknownObjectWeakAssign(lVar4,lVar5);
  }
  lVar4 = _TtC8Playback14MixerTrackCell::muteButton;
  lVar6 = unaff_x20 + _TtC8Playback14MixerTrackCell::muteButton;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar6 != 0) {
    lVar6 = lVar6 + _TtC8Playback20MixerTrackMuteButton::track;
    *(undefined8 *)(lVar6 + 8) = 0;
    _swift_unknownObjectWeakAssign(lVar6,0);
  }
  lVar6 = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar6 != 0) {
    lVar6 = lVar6 + _TtC8Playback15MixerTrackFader::identifiableTrack;
    *(undefined8 *)(lVar6 + 8) = 0;
    _swift_unknownObjectWeakAssign(lVar6,0);
  }
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::muteState) = 1;
  FUN_1007bcfb0();
  lVar6 = _TtC8Playback14MixerTrackCell::soloButton;
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::soloButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x1007bec6c);
    (*pcVar1)();
  }
  _objc_msgSend(IVar3,"setHidden:",0);
  IVar3 = unaff_x20 + lVar6;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x1007bec70);
    (*pcVar1)();
  }
  _objc_msgSend(IVar3,"setUserInteractionEnabled:",1);
  IVar3 = unaff_x20 + lVar4;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    uVar7 = 0x20;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x20,0xe100000000000000);
    _objc_msgSend(IVar3,"setTitle:forState:",uVar7,0);
    uVar7 = 0x20;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x20,0xe100000000000000);
    _objc_msgSend(IVar3,"setTitle:forState:",uVar7,4);
    FUN_1001bed90(0);
  }
  IVar3 = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar7 = DAT_100b757a8;
    FUN_1001711d0(DAT_100b757a8);
    _objc_msgSend(IVar3,"setExclusiveTouch:",(ulong)((uint)uVar7 & 1));
    IVar3 = IVar3 + _TtC8Playback15MixerTrackFader::faderBackgroundButton;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar3 != 0) {
      _objc_msgSend(IVar3,"setHidden:",1);
    }
  }
  puVar8 = (ulong *)(unaff_x20 + lVar2);
  _swift_unknownObjectWeakLoadStrong();
  if (puVar8 != (ulong *)0x0) {
    (**(code **)((*(ulong *)PTR__swift_isaMask_100a1e080 & *puVar8) + 0x210))(4);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::trackExpandedLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingBorderView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",0);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",0);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::leadingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::trailingShadowView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  lVar2 = _TtC8Playback14MixerTrackCell::expandSubtracksButton;
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::expandSubtracksButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  IVar3 = unaff_x20 + lVar2;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setSelected:",0);
  }
  IVar3 = unaff_x20 + _TtC8Playback14MixerTrackCell::rentalPreviewInfoButton;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar3 != 0) {
    _objc_msgSend(IVar3,"setHidden:",1);
  }
  FUN_1007bf7b0();
  puVar9 = (undefined *)_objc_msgSend(unaff_x20,"gestureRecognizers");
  puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
  if (puVar9 == (undefined *)0x0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    puVar9 = puVar11;
  }
  else {
    uVar7 = 0;
    FUN_100728d64(0);
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(puVar9,uVar7);
  }
  if ((ulong)puVar9 >> 0x3e == 0) {
    puVar11 = *(undefined **)(((ulong)puVar9 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar11 = (undefined *)((ulong)puVar9 & 0xffffffffffffff8);
    if ((long)puVar9 < 0) {
      puVar11 = puVar9;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar11 != (undefined *)0x0) {
    if ((long)puVar11 < 1) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x1007bec68);
      (*pcVar1)();
    }
    puVar12 = (undefined *)0x0;
    do {
      if (((ulong)puVar9 & 0xc000000000000001) == 0) {
        puVar10 = *(undefined **)(puVar9 + (long)puVar12 * 8 + 0x20);
      }
      else {
        puVar10 = puVar12;
        FUN_1000cd068(puVar12,puVar9);
      }
      puVar12 = puVar12 + 1;
      _objc_msgSend(unaff_x20,"removeGestureRecognizer:",puVar10);
    } while (puVar11 != puVar12);
  }
  _swift_bridgeObjectRelease(puVar9);
  return;
}

// ==== 1007bfda4 FUN_1007bfda4 ====
void FUN_1007bfda4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  long lVar1;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::faderControlStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::soloVUMeterContainterView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::soloButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::vuMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trackFader,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::muteButtonStackView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::genreMarkerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::muteButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trackExpandedLabel,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::rentalPreviewInfoButton,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::expandSubtracksButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingBorderView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingBorderView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingInsetView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingShadowView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingShadowView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetViewWidthConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::faderCapLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::previewInfoButtonWidthConstraint,0);
  lVar1 = unaff_x20 + _TtC8Playback14MixerTrackCell::identifiableTrack;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::muteState) = 1;
  *(undefined8 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::partID) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::isEditing) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::expandedState) = 1;
  lVar1 = unaff_x20 + _TtC8Playback14MixerTrackCell::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"initWithFrame:",param_1,param_2,
                      param_3,param_4);
  return;
}

// ==== 1007c0028 FUN_1007c0028 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1007c0028(undefined8 param_1)

{
  long lVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::faderControlStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::soloVUMeterContainterView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::soloButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::vuMeter,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trackFader,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::muteButtonStackView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::genreMarkerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::muteButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trackExpandedLabel,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::rentalPreviewInfoButton,0)
  ;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::expandSubtracksButton,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingBorderView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingBorderView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingInsetView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::leadingShadowView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback14MixerTrackCell::trailingShadowView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::trailingInsetViewWidthConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::faderCapLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback14MixerTrackCell::previewInfoButtonWidthConstraint,0);
  lVar1 = unaff_x20 + _TtC8Playback14MixerTrackCell::identifiableTrack;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::muteState) = 1;
  *(undefined8 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::partID) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::isEditing) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback14MixerTrackCell::expandedState) = 1;
  lVar1 = unaff_x20 + _TtC8Playback14MixerTrackCell::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffc0,"initWithCoder:",param_1);
  return IVar2;
}

// ==== 1007c02b8 _TtC8Playback14MixerTrackCell::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback14MixerTrackCell::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_unknownObjectWeakDestroy(param_1 + faderControlStackView);
  _swift_unknownObjectWeakDestroy(param_1 + soloVUMeterContainterView);
  _swift_unknownObjectWeakDestroy(param_1 + soloButton);
  _swift_unknownObjectWeakDestroy(param_1 + vuMeter);
  _swift_unknownObjectWeakDestroy(param_1 + trackFader);
  _swift_unknownObjectWeakDestroy(param_1 + muteButtonStackView);
  _swift_unknownObjectWeakDestroy(param_1 + genreMarkerView);
  _swift_unknownObjectWeakDestroy(param_1 + muteButton);
  _swift_unknownObjectWeakDestroy(param_1 + trackExpandedLabel);
  _swift_unknownObjectWeakDestroy(param_1 + rentalPreviewInfoButton);
  _swift_unknownObjectWeakDestroy(param_1 + expandSubtracksButton);
  _swift_unknownObjectWeakDestroy(param_1 + leadingBorderView);
  _swift_unknownObjectWeakDestroy(param_1 + trailingBorderView);
  _swift_unknownObjectWeakDestroy(param_1 + leadingInsetView);
  _swift_unknownObjectWeakDestroy(param_1 + trailingInsetView);
  _swift_unknownObjectWeakDestroy(param_1 + leadingShadowView);
  _swift_unknownObjectWeakDestroy(param_1 + trailingShadowView);
  _swift_unknownObjectWeakDestroy(param_1 + trailingInsetViewWidthConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + faderCapLeadingConstraint);
  _swift_unknownObjectWeakDestroy(param_1 + previewInfoButtonWidthConstraint);
  FUN_100026610(param_1 + identifiableTrack);
  FUN_100026610(param_1 + delegate);
  return;
}

// ==== 1007daeb4 FUN_1007daeb4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001007f96a4) */
/* WARNING: Removing unreachable block (ram,0x0001007f96a8) */
/* WARNING: Removing unreachable block (ram,0x0001007f96bc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
FUN_1007daeb4(undefined8 param_1,ulong param_2,undefined8 param_3,class_rw_t *param_4,
             undefined8 param_5,class_rw_t *param_6)

{
  ulong uVar1;
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  ushort *puVar8;
  code *pcVar9;
  undefined1 in_ZR;
  byte bVar10;
  class_rw_t *pcVar11;
  undefined1 *puVar12;
  objc_property_list oVar13;
  TargetProtocolConformanceDescriptor *pTVar14;
  class_t *pcVar15;
  qword qVar16;
  long lVar17;
  class_t *pcVar18;
  undefined8 *puVar19;
  long lVar20;
  ID IVar21;
  undefined *puVar22;
  ID IVar23;
  undefined *puVar24;
  void *pvVar25;
  undefined8 uVar26;
  protocol_list_t *ppVar27;
  protocol_list_t *ppVar28;
  ID IVar29;
  ID IVar30;
  undefined8 uVar31;
  char *op;
  undefined8 *puVar32;
  undefined8 uVar33;
  char *pcVar34;
  objc_property_list *poVar35;
  ulong uVar36;
  ushort *puVar37;
  ushort *puVar38;
  ulong in_x12;
  objc_property_list oVar39;
  int iVar40;
  ID unaff_x19;
  class_rw_t *unaff_x20;
  code cVar41;
  protocol_list_t *unaff_x21;
  Cache CVar42;
  class_rw_t *unaff_x22;
  class_rw_t *pcVar43;
  qword qVar44;
  class_rw_t *pcVar45;
  class_rw_t *unaff_x23;
  class_rw_t *unaff_x24;
  class_rw_t *unaff_x25;
  long lVar46;
  undefined8 *puVar47;
  undefined8 *unaff_x26;
  class_rw_t *unaff_x27;
  long lVar48;
  class_rw_t *pcVar49;
  undefined8 *unaff_x28;
  long unaff_x29;
  undefined8 in_register_00005008;
  undefined8 uVar50;
  undefined8 uVar51;
  undefined8 uVar52;
  undefined8 uVar53;
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
  undefined *in_stack_00000000;
  objc_property_list in_stack_00000008;
  class_rw_t *in_stack_00000010;
  class_rw_t *in_stack_00000018;
  protocol_list_t *in_stack_00000020;
  method_list_t *in_stack_00000028;
  protocol_list_t *in_stack_00000030;
  class_rw_t *in_stack_00000038;
  qword in_stack_00000040;
  class_rw_t *in_stack_00000048;
  undefined8 in_stack_00000050;
  undefined8 in_stack_00000058;
  undefined8 in_stack_00000060;
  undefined8 in_stack_00000068;
  undefined8 in_stack_00000070;
  undefined8 in_stack_00000078;
  undefined8 in_stack_00000080;
  undefined8 in_stack_00000088;
  undefined2 in_stack_00000090;
  undefined2 uStack0000000000000098;
  undefined6 uStack000000000000009a;
  undefined2 in_stack_000000a0;
  class_rw_t *in_stack_000000f0;
  protocol_list_t *in_stack_000000f8;
  method_list_t *in_stack_00000100;
  protocol_list_t *in_stack_00000108;
  ivar_list_t *in_stack_00000110;
  qword in_stack_00000118;
  objc_property_list *in_stack_00000120;
  undefined8 in_stack_00000128;
  undefined8 in_stack_00000130;
  undefined8 in_stack_00000138;
  undefined8 in_stack_00000140;
  undefined8 in_stack_00000148;
  undefined8 in_stack_00000150;
  undefined8 in_stack_00000158;
  undefined8 in_stack_00000160;
  undefined2 in_stack_00000168;
  undefined2 in_stack_00000170;
  undefined8 uStack0000000000000172;
  
  uVar26 = _DAT_6165627472616568;
  lVar20 = DAT_100b778c8;
  op = &DAT_e900000000000074;
  pcVar11 = (class_rw_t *)&DAT_6165627472616568;
  pcVar34 = (char *)(param_2 & 0xff);
  puVar37 = &switchD_1007daeec::switchdataD_100952aa0;
  puVar38 = (ushort *)(ulong)(&switchD_1007daeec::switchdataD_100952aa0)[(long)pcVar34];
  oVar13 = (objc_property_list)((long)puVar38 * 4 + 0x1007daef0);
  iVar40 = (int)unaff_x19;
  pcVar49 = pcVar11;
  pcVar45 = unaff_x22;
  pcVar43 = unaff_x23;
  switch(pcVar34) {
  default:
    pcVar34 = "Updated %{public}@ output routings from %@";
  case (char *)0x9a:
  case (char *)0xa1:
  case (char *)0xae:
  case (char *)0xb5:
    pcVar34 = (char *)((long)pcVar34 + 0xb90);
    goto switchD_1007daeec_caseD_99;
  case (char *)0x1:
    pcVar34 = "hostAccessResponse";
    goto LAB_1007db1ec;
  case (char *)0x2:
    pcVar34 = "clientUpdateSetlistRequest";
  case (char *)0x50:
    goto LAB_1007db2b4;
  case (char *)0x3:
    pcVar34 = "hostUpdateSetlistResponse";
    goto LAB_1007db248;
  case (char *)0x4:
    pcVar34 = "hostUnownedContentChanged";
    goto LAB_1007db248;
  case (char *)0x5:
    pcVar11 = (class_rw_t *)0xd000000000000011;
    pcVar34 = "hostServerStopped";
    break;
  case (char *)0x6:
    pcVar11 = (class_rw_t *)0xd000000000000011;
    pcVar34 = "hostRemovedClient";
    break;
  case (char *)0x7:
    pcVar34 = "contentLoadSetlist";
    goto LAB_1007db1ec;
  case (char *)0x8:
    pcVar34 = "contentUpdateRentalTypes";
    goto LAB_1007db318;
  case (char *)0x9:
    pcVar34 = "contentUpdateSetlist";
    goto LAB_1007db294;
  case (char *)0xa:
    pcVar34 = "contentRefreshMIDICues";
    goto LAB_1007db004;
  case (char *)0xb:
    goto switchD_1007daeec_caseD_b;
  case (char *)0xc:
    pcVar11 = (class_rw_t *)0xd000000000000011;
    pcVar34 = "mixerInfiniteLoop";
  case (char *)0x85:
    break;
  case (char *)0xd:
    auVar67._8_8_ = 0xe900000000000070;
    auVar67._0_8_ = 0x6f6f4c726578696d;
    return auVar67;
  case (char *)0xe:
    auVar59._8_8_ = 0x800000010090ed10;
    auVar59._0_8_ = 0xd00000000000001e;
    return auVar59;
  case (char *)0xf:
    pcVar34 = "mixerMasterVolumeValueChanged";
    goto LAB_1007db0a8;
  case (char *)0x10:
    auVar58._8_8_ = 0xed00004944494d65;
    auVar58._0_8_ = 0x74754d726578696d;
    return auVar58;
  case (char *)0x11:
    uVar36 = 0x6574754d6b63;
    goto LAB_1007db1c0;
  case (char *)0x12:
    op = (char *)0x6b63;
  case (char *)0x7e:
    uVar36 = (ulong)op | 0x6f6c6f530000;
LAB_1007db1c0:
    op = (char *)(uVar36 & 0xffffffffffff | 0xee00000000000000);
    pcVar11 = (class_rw_t *)0x617254726578696d;
switchD_1007daeec_caseD_48:
    auVar68._8_8_ = op;
    auVar68._0_8_ = pcVar11;
    return auVar68;
  case (char *)0x13:
    auVar72._8_8_ = 0x800000010090ed50;
    auVar72._0_8_ = 0xd000000000000010;
    return auVar72;
  case (char *)0x14:
    op = (char *)0x646f4d72;
  case (char *)0x7d:
    auVar65._8_8_ = (ulong)op & 0xffffffffffff | 0xed00006500000000;
    auVar65._0_8_ = 0x6579616c50646170;
    return auVar65;
  case (char *)0x15:
    pcVar11 = (class_rw_t *)0x50646170;
  case (char *)0x51:
    auVar66._0_8_ = (ulong)pcVar11 & 0xffffffff | 0x6579616c00000000;
    auVar66._8_8_ = 0xed000079616c5072;
    return auVar66;
  case (char *)0x16:
    pcVar34 = "Updated %{public}@ output routings from %@";
  case (char *)0x75:
    pcVar34 = (char *)&((class_t *)((long)pcVar34 + 0xd70))->data;
LAB_1007db2b4:
    op = (char *)((ulong)&((class_t *)((long)pcVar34 + -0x28))->superclass | 0x8000000000000000);
switchD_1007daeec_caseD_7c:
    auVar74._8_8_ = op;
    auVar74._0_8_ = 0xd00000000000001a;
    return auVar74;
  case (char *)0x17:
    pcVar34 = "setlistRemovedByHost";
LAB_1007db294:
    auVar73._8_8_ = (ulong)(pcVar34 + -0x20) | 0x8000000000000000;
    auVar73._0_8_ = 0xd000000000000014;
    return auVar73;
  case (char *)0x18:
    pcVar11 = (class_rw_t *)0x11;
  case (char *)0x8a:
    pcVar11 = (class_rw_t *)((ulong)pcVar11 & 0xffffffffffff | 0xd000000000000000);
    pcVar34 = "setlistSelectSong";
    break;
  case (char *)0x19:
    op = (char *)0x800000010090edd0;
    pcVar11 = (class_rw_t *)0xd00000000000001b;
  case (char *)0x52:
    auVar61._8_8_ = op;
    auVar61._0_8_ = pcVar11;
    return auVar61;
  case (char *)0x1a:
    pcVar34 = "setlistUpdateContinuePad";
LAB_1007db318:
    op = (char *)((ulong)(pcVar34 + -0x20) | 0x8000000000000000);
    pcVar11 = (class_rw_t *)0xd000000000000018;
switchD_1007daeec_caseD_6a:
    auVar77._8_8_ = op;
    auVar77._0_8_ = pcVar11;
    return auVar77;
  case (char *)0x1b:
    pcVar34 = "generalSettingUpdateClickType";
LAB_1007db0a8:
    op = (char *)((ulong)(pcVar34 + -0x20) | 0x8000000000000000);
    pcVar34._0_4_ = 0x11;
    pcVar34._4_4_ = 0xd0000000;
switchD_1007daeec_caseD_7f:
    pcVar11 = (class_rw_t *)((ulong)pcVar34 | 0xc);
switchD_1007daeec_caseD_ce:
    auVar62._8_8_ = op;
    auVar62._0_8_ = pcVar11;
    return auVar62;
  case (char *)0x1c:
    pcVar34 = "generalSettingUpdateToggle";
    goto LAB_1007db2b4;
  case (char *)0x1d:
    auVar75._8_8_ = 0x800000010090ee50;
    auVar75._0_8_ = 0xd000000000000022;
    return auVar75;
  case (char *)0x1e:
    uVar36 = 0xed00006564614674;
    goto LAB_1007db2fc;
  case (char *)0x1f:
    auVar63._8_8_ = 0x800000010090ee80;
    auVar63._0_8_ = 0xd000000000000026;
    return auVar63;
  case (char *)0x20:
    pcVar11 = (class_rw_t *)0xd000000000000011;
    pcVar34 = "transportNextSong";
    break;
  case (char *)0x21:
    uVar36 = 0xec00000064615074;
    goto LAB_1007db2fc;
  case (char *)0x22:
  case (char *)0xa5:
  case (char *)0xb9:
    auVar57._8_8_ = 0xed000079616c5074;
    auVar57._0_8_ = 0x726f70736e617274;
    return auVar57;
  case (char *)0x23:
    pcVar34 = "transportNextSong";
  case (char *)0x93:
  case (char *)0x9d:
  case (char *)0xa7:
  case (char *)0xb1:
    auVar55._8_8_ = (ulong)pcVar34 | 0x8000000000000000;
    auVar55._0_8_ = 0xd000000000000015;
    return auVar55;
  case (char *)0x24:
    auVar56._8_8_ = 0x800000010090eef0;
    auVar56._0_8_ = 0xd000000000000024;
    return auVar56;
  case (char *)0x25:
    pcVar34 = "transportReturnToStart";
LAB_1007db004:
    auVar60._8_8_ = (ulong)(pcVar34 + -0x20) | 0x8000000000000000;
    auVar60._0_8_ = 0xd000000000000016;
    return auVar60;
  case (char *)0x26:
    op = (char *)0x6c655374;
  case (char *)0x3d:
    uVar36 = (ulong)op & 0xffffffffffff | 0xef74636500000000;
LAB_1007db2fc:
    auVar76._8_8_ = uVar36;
    auVar76._0_8_ = 0x726f70736e617274;
    return auVar76;
  case (char *)0x27:
    pcVar34 = "transportTapTempoAutoPlay";
LAB_1007db248:
    op = (char *)((ulong)(pcVar34 + -0x20) | 0x8000000000000000);
    pcVar34._0_4_ = 0x11;
    pcVar34._4_4_ = 0;
switchD_1007daeec_caseD_4f:
    auVar71._0_8_ = (ulong)pcVar34 | 0xd000000000000008;
    auVar71._8_8_ = op;
    return auVar71;
  case (char *)0x28:
    pcVar11 = (class_rw_t *)0xd000000000000011;
  case (char *)0x58:
    pcVar34 = "waveformDoubleTap";
    break;
  case (char *)0x29:
    uVar36 = 0x706f6f4c;
    goto LAB_1007db118;
  case (char *)0x2a:
    pcVar34 = "waveformPresetInfiniteLoop";
    goto LAB_1007db2b4;
  case (char *)0x2b:
    uVar36 = 0x6b656553;
LAB_1007db118:
    auVar64._8_8_ = uVar36 | 0xec00000000000000;
    auVar64._0_8_ = 0x6d726f6665766177;
    return auVar64;
  case (char *)0x2c:
    pcVar34 = "audioDeviceChanged";
LAB_1007db1ec:
    op = (char *)((ulong)(pcVar34 + -0x20) | 0x8000000000000000);
    pcVar11 = (class_rw_t *)0xd000000000000012;
switchD_1007daeec_caseD_b:
    auVar69._8_8_ = op;
    auVar69._0_8_ = pcVar11;
    return auVar69;
  case (char *)0x2e:
    goto switchD_1007daeec_caseD_2e;
  case (char *)0x2f:
    goto switchD_1007daeec_caseD_2f;
  case (char *)0x30:
  case (char *)0x69:
    goto switchD_1007daeec_caseD_30;
  case (char *)0x31:
    goto switchD_1007daeec_caseD_31;
  case (char *)0x32:
    goto switchD_1007daeec_caseD_32;
  case (char *)0x33:
    param_6 = (class_rw_t *)(unaff_x29 + -0xf0);
    FUN_10066fff0();
    unaff_x23 = (class_rw_t *)(ulong)*(uint *)&param_6->flags;
    unaff_x22 = (class_rw_t *)(ulong)(byte)*(code *)((long)&param_6->flags + 4);
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0x2a;
    FUN_1007e06f0();
    pcVar11 = (class_rw_t *)&DAT_100a69fe8;
    op = (char *)(unaff_x19 + 0x4e0);
    unaff_x26 = *(undefined8 **)(unaff_x19 + 0x410);
  case (char *)0x6f:
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (unaff_x26,pcVar11,op,unaff_x24,pcVar11,param_6);
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0;
    uVar26 = *(undefined8 *)(unaff_x19 + 0x420);
    lVar20 = *(long *)(unaff_x19 + 0x430);
    __ss22KeyedEncodingContainerV6encode_6forKeyys5Int32V_xtKF(unaff_x23,unaff_x19 + 0x4e0,uVar26);
    if (lVar20 == 0) {
      *(undefined1 *)(unaff_x19 + 0x4e0) = 1;
      __ss22KeyedEncodingContainerV6encode_6forKeyySb_xtKF(unaff_x22,unaff_x19 + 0x4e0,uVar26);
    }
    lVar20 = *(long *)(unaff_x19 + 0x120);
LAB_1007dd648:
    pcVar9 = *(code **)(lVar20 + 8);
    pcVar43 = unaff_x24;
    pcVar11 = unaff_x25;
LAB_1007dd650:
    (*pcVar9)();
    pcVar34 = *(char **)(*(long *)(unaff_x19 + 0x428) + 8);
LAB_1007dd668:
    (*(code *)pcVar34)(pcVar11,pcVar43);
    goto LAB_1007dd66c;
  case (char *)0x34:
    goto switchD_1007daeec_caseD_34;
  case (char *)0x35:
    goto switchD_1007daeec_caseD_35;
  case (char *)0x36:
    goto switchD_1007daeec_caseD_36;
  case (char *)0x37:
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x438);
  case (char *)0x64:
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF();
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0;
    lVar20 = *(long *)(unaff_x19 + 0x430);
    __ss22KeyedEncodingContainerV6encode_6forKeyys5Int32V_xtKF();
    if (lVar20 == 0) {
      *(undefined1 *)(unaff_x19 + 0x4e0) = 1;
      __ss22KeyedEncodingContainerV6encode_6forKeyySb_xtKF();
    }
    lVar20 = *(long *)(unaff_x19 + 0x110);
    goto LAB_1007dd648;
  case (char *)0x38:
    goto switchD_1007daeec_caseD_38;
  case (char *)0x39:
    goto switchD_1007daeec_caseD_39;
  case (char *)0x3a:
    pcVar11 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF();
    pcVar9 = *(code **)(*(long *)(unaff_x19 + 0x3b0) + 8);
    pcVar43 = unaff_x22;
    goto LAB_1007dd578;
  case (char *)0x3b:
    goto switchD_1007daeec_caseD_3b;
  case (char *)0x3c:
    goto switchD_1007daeec_caseD_3c;
  case (char *)0x3e:
    goto switchD_1007daeec_caseD_3e;
  case (char *)0x3f:
    goto switchD_1007daeec_caseD_3f;
  case (char *)0x40:
    FUN_1007e08b0();
    pcVar43 = *(class_rw_t **)(unaff_x19 + 0x440);
    pcVar49 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (*(undefined8 *)(unaff_x19 + 0x350),&DAT_100a69d48,unaff_x19 + 0x4e0,pcVar43,
               &DAT_100a69d48,pcVar11);
    pcVar9 = *(code **)(*(long *)(unaff_x19 + 0x360) + 8);
    pcVar11 = pcVar49;
    goto LAB_1007dd578;
  case (char *)0x41:
    unaff_x26[1] = uRam6165627472616570;
    *unaff_x26 = uVar26;
    uVar26 = _DAT_6165627472616578;
    unaff_x26[3] = uRam6165627472616580;
    unaff_x26[2] = uVar26;
    uVar26 = _DAT_6165627472616588;
    unaff_x26[5] = uRam6165627472616590;
    unaff_x26[4] = uVar26;
    uVar26 = _DAT_6165627472616598;
    unaff_x26[7] = uRam61656274726165a0;
    unaff_x26[6] = uVar26;
    unaff_x22 = (class_rw_t *)(ulong)DAT_61656274726165e0;
    *(undefined1 *)(unaff_x19 + 0x450) = 0;
    FUN_1007e12f0();
    pcVar49 = (class_rw_t *)&DAT_100a68b58;
    unaff_x27 = *(class_rw_t **)(unaff_x19 + 0x140);
    unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (unaff_x27,&DAT_100a68b58,unaff_x19 + 0x450,unaff_x23,&DAT_100a68b58,pcVar11);
    uVar26 = unaff_x26[8];
    uVar31 = unaff_x26[0xb];
    uVar33 = unaff_x26[10];
    *(undefined8 *)(unaff_x19 + 0x498) = unaff_x26[9];
    *(undefined8 *)(unaff_x19 + 0x490) = uVar26;
    *(undefined8 *)(unaff_x19 + 0x4a8) = uVar31;
    *(undefined8 *)(unaff_x19 + 0x4a0) = uVar33;
  case (char *)0x83:
    in_register_00005008 = unaff_x26[0xd];
    param_1 = unaff_x26[0xc];
switchD_1007daeec_caseD_32:
    *(undefined8 *)(unaff_x19 + 0x4b8) = in_register_00005008;
    *(undefined8 *)(unaff_x19 + 0x4b0) = param_1;
    *(undefined8 *)(unaff_x19 + 0x4c0) = unaff_x26[0xe];
    uVar26 = *unaff_x26;
    uVar31 = unaff_x26[3];
    uVar33 = unaff_x26[2];
    *(undefined8 *)(unaff_x19 + 0x458) = unaff_x26[1];
    *(undefined8 *)(unaff_x19 + 0x450) = uVar26;
    *(undefined8 *)(unaff_x19 + 0x468) = uVar31;
    *(undefined8 *)(unaff_x19 + 0x460) = uVar33;
    uVar26 = unaff_x26[4];
    uVar31 = unaff_x26[7];
    uVar33 = unaff_x26[6];
    *(undefined8 *)(unaff_x19 + 0x478) = unaff_x26[5];
    *(undefined8 *)(unaff_x19 + 0x470) = uVar26;
    *(undefined8 *)(unaff_x19 + 0x488) = uVar31;
    *(undefined8 *)(unaff_x19 + 0x480) = uVar33;
    *(undefined1 *)(unaff_x19 + 0x44f) = 0;
    FUN_1007e1330();
    pcVar11 = (class_rw_t *)(unaff_x19 + 0x450);
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x158);
    lVar20 = *(long *)(unaff_x19 + 0x430);
    __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF
              (pcVar11,unaff_x19 + 0x44f,unaff_x25,&DAT_100a64068,pcVar49);
    pcVar43 = unaff_x23;
    pcVar49 = unaff_x25;
    if (lVar20 == 0) {
      *(byte *)(unaff_x19 + 0x450) = (byte)unaff_x22 & 1;
      *(undefined1 *)(unaff_x19 + 0x44f) = 1;
switchD_1007daeec_caseD_42:
      FUN_1007e1370();
      param_6 = pcVar11;
      pcVar43 = unaff_x23;
switchD_1007daeec_caseD_6e:
      __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF
                (unaff_x19 + 0x450,unaff_x19 + 0x44f,unaff_x25,&DAT_100a64958,param_6);
      pcVar49 = unaff_x25;
    }
    unaff_x25 = unaff_x27;
    unaff_x22 = pcVar49;
    pcVar11 = unaff_x24;
    pcVar18 = *(class_t **)(*(long *)(unaff_x19 + 0x10) + 8);
LAB_1007dd518:
    (*(code *)pcVar18)(unaff_x25,unaff_x22);
    pcVar34 = *(char **)(*(long *)(unaff_x19 + 0x428) + 8);
    goto LAB_1007dd668;
  case (char *)0x42:
    goto switchD_1007daeec_caseD_42;
  case (char *)0x43:
    pcVar34 = *(char **)(unaff_x19 + 0x48);
  case (char *)0x81:
LAB_1007dd50c:
    pcVar18 = *(class_t **)((long)pcVar34 + 8);
    pcVar43 = unaff_x23;
    pcVar11 = unaff_x24;
    goto LAB_1007dd518;
  case (char *)0x44:
    goto switchD_1007daeec_caseD_44;
  case (char *)0x45:
    goto switchD_1007daeec_caseD_45;
  case (char *)0x46:
    goto switchD_1007daeec_caseD_46;
  case (char *)0x47:
    FUN_10066fff0();
    pcVar49 = (class_rw_t *)(ulong)(byte)*(code *)&pcVar11->flags;
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0x10;
    FUN_1007e0e70();
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x220);
    unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (unaff_x25,&DAT_100a693e8,unaff_x19 + 0x4e0,unaff_x23,&DAT_100a693e8,pcVar11);
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x228);
  case (char *)0x74:
    __ss22KeyedEncodingContainerV6encode_6forKeyySb_xtKF(pcVar49);
    pcVar34 = *(char **)(unaff_x19 + 0x78);
    goto LAB_1007dd50c;
  case (char *)0x48:
    goto switchD_1007daeec_caseD_48;
  case (char *)0x49:
    unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (&DAT_6165627472616568,&DAT_e900000000000074,unaff_x23,&DAT_6165627472616568);
    *(char *)(unaff_x19 + 0x4e0) = (char)unaff_x22;
    FUN_100778e3c();
    pcVar11 = (class_rw_t *)(unaff_x19 + 0x4e0);
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x2d8);
  case (char *)0x76:
    __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF(pcVar11);
    pcVar34 = *(char **)(unaff_x19 + 200);
    goto LAB_1007dd50c;
  case (char *)0x4a:
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (*(undefined8 *)(unaff_x19 + 0x2c8),&DAT_6165627472616568,&DAT_e900000000000074,
               unaff_x24,&DAT_6165627472616568);
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0;
    lVar20 = *(long *)(unaff_x19 + 0x430);
    __ss22KeyedEncodingContainerV6encode_6forKeyySb_xtKF();
    if (lVar20 == 0) {
      pcVar34._0_4_ = 1;
      pcVar34._4_4_ = 0;
      goto switchD_1007daeec_caseD_77;
    }
    goto LAB_1007dc6cc;
  case (char *)0x4b:
    goto switchD_1007daeec_caseD_4b;
  case (char *)0x4c:
  case (char *)0x5b:
    goto switchD_1007daeec_caseD_4c;
  case (char *)0x4d:
  case (char *)0x70:
    pcVar34 = *(char **)(unaff_x19 + 0x108);
    goto LAB_1007dd50c;
  case (char *)0x4e:
    goto switchD_1007daeec_caseD_4e;
  case (char *)0x4f:
    goto switchD_1007daeec_caseD_4f;
  case (char *)0x53:
    pcVar43 = *(class_rw_t **)(unaff_x19 + 0x440);
    pcVar11 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (&DAT_100a68c78,unaff_x19 + 0x4e0,pcVar43,&DAT_100a68c78,&DAT_6165627472616568);
    __ss22KeyedEncodingContainerV6encode_6forKeyySi_xtKF();
    (*(code *)unaff_x24->instanceStart)();
    pcVar34 = *(char **)(*(long *)(unaff_x19 + 0x428) + 8);
  case (char *)0x80:
    goto LAB_1007dd668;
  case (char *)0x54:
    FUN_1007e61b4(0x6165627472616cf0,FUN_100778304,PTR___sSayxGSEsSERzlMc_100a1dd20);
    pcVar11 = (class_rw_t *)(unaff_x19 + 0x4e0);
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x168);
  case (char *)0x6d:
    __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF(pcVar11);
    pcVar34 = *(char **)(unaff_x19 + 0x18);
    goto LAB_1007dd50c;
  case (char *)0x55:
    goto switchD_1007daeec_caseD_55;
  case (char *)0x56:
    goto switchD_1007daeec_caseD_56;
  case (char *)0x57:
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF();
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x1f8);
    __ss22KeyedEncodingContainerV6encode_6forKeyySb_xtKF();
    pcVar34 = *(char **)(unaff_x19 + 0x60);
    goto LAB_1007dd50c;
  case (char *)0x59:
    goto switchD_1007daeec_caseD_59;
  case (char *)0x5c:
    goto switchD_1007daeec_caseD_5c;
  case (char *)0x5d:
    goto switchD_1007daeec_caseD_5d;
  case (char *)0x5e:
    goto switchD_1007daeec_caseD_5e;
  case (char *)0x5f:
    *(undefined1 *)(unaff_x19 + 0x4e0) = 5;
    FUN_1007e1170();
    pcVar43 = *(class_rw_t **)(unaff_x19 + 0x440);
    pcVar49 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (*(undefined8 *)(unaff_x19 + 0x130),&DAT_100a68db8,unaff_x19 + 0x4e0,pcVar43,
               &DAT_100a68db8,pcVar11);
    pcVar9 = *(code **)(*(long *)(unaff_x19 + 0x138) + 8);
    pcVar11 = pcVar49;
    goto LAB_1007dd578;
  case (char *)0x60:
    FUN_10066fff0();
    cVar41 = *(code *)&pcVar11->flags;
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0x1d;
    FUN_1007e0a70();
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x2e8);
    unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (unaff_x25,&DAT_100a69ac8,unaff_x19 + 0x4e0,unaff_x23,&DAT_100a69ac8,pcVar11);
    *(code *)(unaff_x19 + 0x4e0) = cVar41;
    FUN_100586edc();
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x2f8);
    __ss22KeyedEncodingContainerV15encodeIfPresent_6forKeyyqd__Sg_xtKSERd__lF(unaff_x19 + 0x4e0);
  case (char *)0x6c:
    pcVar34 = *(char **)(unaff_x19 + 0xd0);
    goto LAB_1007dd50c;
  case (char *)0x61:
    goto switchD_1007daeec_caseD_61;
  case (char *)0x62:
    *(undefined1 *)(unaff_x19 + 0x450) = 0;
    unaff_x20 = (class_rw_t *)&DAT_100af52f8;
    FUN_100021774(&DAT_100af52f8);
    param_6 = (class_rw_t *)&DAT_100b0da58;
    FUN_1007e6088(&DAT_100b0da58,PTR___sSSSEsWP_100a1dce8,PTR___sSayxGSEsSERzlMc_100a1dd20);
    goto switchD_1007daeec_caseD_35;
  case (char *)0x63:
    goto switchD_1007daeec_caseD_63;
  case (char *)0x65:
    goto switchD_1007daeec_caseD_65;
  case (char *)0x66:
    goto switchD_1007daeec_caseD_66;
  case (char *)0x67:
    puVar47 = (undefined8 *)(unaff_x29 + -0xf0);
    FUN_10066fff0();
    param_1 = *puVar47;
    *(undefined1 *)(unaff_x19 + 0x4e0) = 0x2b;
    FUN_1007e06b0();
    unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x3f0);
    unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x440);
    unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (unaff_x25,&DAT_100a6a078,unaff_x19 + 0x4e0,unaff_x22,&DAT_100a6a078,puVar47);
    goto switchD_1007daeec_caseD_3f;
  case (char *)0x68:
    goto switchD_1007daeec_caseD_68;
  case (char *)0x6a:
    goto switchD_1007daeec_caseD_6a;
  case (char *)0x6b:
    goto switchD_1007daeec_caseD_6b;
  case (char *)0x6e:
    goto switchD_1007daeec_caseD_6e;
  case (char *)0x71:
    goto switchD_1007daeec_caseD_71;
  case (char *)0x72:
    goto switchD_1007daeec_caseD_72;
  case (char *)0x73:
    goto switchD_1007daeec_caseD_73;
  case (char *)0x77:
switchD_1007daeec_caseD_77:
    *(char *)(unaff_x19 + 0x4e0) = (char)pcVar34;
    __ss22KeyedEncodingContainerV6encode_6forKeyySi_xtKF();
LAB_1007dc6cc:
    lVar20 = *(long *)(unaff_x19 + 0xc0);
    goto LAB_1007dd648;
  case (char *)0x78:
    pcVar43 = *(class_rw_t **)(unaff_x19 + 0x440);
    pcVar11 = *(class_rw_t **)(unaff_x19 + 0x438);
    __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
              (*(undefined8 *)(unaff_x19 + 1000),&DAT_6165627472616568,unaff_x19 + 0x4e0,pcVar43,
               &DAT_6165627472616568);
    pcVar9 = *(code **)(*(long *)(unaff_x19 + 0x3f8) + 8);
LAB_1007dd578:
    (*pcVar9)();
    (**(code **)(*(long *)(unaff_x19 + 0x428) + 8))(pcVar11,pcVar43);
LAB_1007dd66c:
    auVar79._8_8_ = pcVar43;
    auVar79._0_8_ = pcVar11;
    return auVar79;
  case (char *)0x79:
    goto switchD_1007daeec_caseD_79;
  case (char *)0x7a:
    __ss22KeyedEncodingContainerV6encode_6forKeyySd_xtKF();
    goto switchD_1007daeec_caseD_4b;
  case (char *)0x7b:
    goto switchD_1007daeec_caseD_7b;
  case (char *)0x7c:
    goto switchD_1007daeec_caseD_7c;
  case (char *)0x7f:
  case (char *)0x90:
    goto switchD_1007daeec_caseD_7f;
  case (char *)0x82:
    goto switchD_1007daeec_caseD_82;
  case (char *)0x84:
    *(undefined1 *)(unaff_x19 + 0x4e0) = 10;
    FUN_1007e1030();
    param_6 = pcVar11;
    goto switchD_1007daeec_caseD_44;
  case (char *)0x86:
    lVar20 = 0x6165627472616d70;
    FUN_100021774();
    *(long *)(unaff_x19 + 0x418) = lVar20;
    lVar20 = *(long *)(lVar20 + -8);
    *(long *)(unaff_x19 + 0x118) = lVar20;
    register0x00000008 =
         (BADSPACEBASE *)
         ((long)&stack0x00000000 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
    *(BADSPACEBASE **)(unaff_x19 + 0x3f0) = register0x00000008;
    puVar22 = &DAT_100b0d810;
    FUN_100021774();
    *(undefined **)(unaff_x19 + 0x420) = puVar22;
    pcVar34 = *(char **)(puVar22 + -8);
    goto switchD_1007daeec_caseD_59;
  case (char *)0x87:
    goto switchD_1007daeec_caseD_87;
  case (char *)0x88:
  case (char *)0xc5:
  case (char *)0xd4:
    goto switchD_1007daeec_caseD_88;
  case (char *)0x89:
    unaff_x21 = *(protocol_list_t **)
                 ((long)&unaff_x20->flags +
                 _TtC8Playback30TransportMappingViewController::previousSongButton);
    if (unaff_x21 == (protocol_list_t *)0x0) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x1007f4fa8);
      (*pcVar9)();
    }
    pcVar11 = (class_rw_t *)&DAT_100af9980;
    op = (char *)FUN_1001dd000;
  case (char *)0xbc:
  case (char *)0xdb:
  case (char *)0xef:
    FUN_100023140(pcVar11,(undefined1 *)
                          ((long)&((class_rw_t *)((long)op + 0xc18))->baseProperties + 4),
                  &TargetProtocolConformanceDescriptor_10092bc18);
    qVar44 = *(qword *)((long)&unaff_x20->flags +
                       _TtC8Playback30TransportMappingViewController::previousSectionButton);
    in_stack_00000030 = unaff_x21;
    in_stack_00000038 = pcVar11;
    if (qVar44 == 0) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x1007f4fac);
      (*pcVar9)();
    }
    lVar20 = *(long *)((long)&unaff_x20->flags +
                      _TtC8Playback30TransportMappingViewController::selectButton);
    in_stack_00000040 = qVar44;
    in_stack_00000048 = pcVar11;
    if (lVar20 == 0) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x1007f4fb0);
      (*pcVar9)();
    }
    puVar22 = &DAT_100af9978;
    FUN_100023140(&DAT_100af9978,FUN_1001d9480,&TargetProtocolConformanceDescriptor_10092ba58);
    puVar24 = PTR___swiftEmptyArrayStorage_100a1e050;
    lVar48 = *(long *)((long)&unaff_x20->flags +
                      _TtC8Playback30TransportMappingViewController::nextSectionButton);
    if (lVar48 == 0) {
                    /* WARNING: Does not return */
      pcVar9 = (code *)SoftwareBreakpoint(1,0x1007f4fb4);
      (*pcVar9)();
    }
    lVar46 = *(long *)((long)&unaff_x20->flags +
                      _TtC8Playback30TransportMappingViewController::nextSongButton);
    if (lVar46 != 0) {
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      pcVar15 = (class_t *)0x0;
      FUN_10078e124(0,1,1,puVar24);
      uVar36 = pcVar15->cache;
      uVar1 = pcVar15->vtable;
      in_stack_00000008 = (objc_property_list)pcVar15;
      _swift_unknownObjectRetain(unaff_x21);
      pcVar18 = pcVar15;
      if (uVar1 >> 1 <= uVar36) {
        pcVar18 = (class_t *)(ulong)(1 < uVar1);
        FUN_10078e124(pcVar18,uVar36 + 1,1,pcVar15);
        in_stack_00000008 = (objc_property_list)pcVar18;
      }
      ppVar27 = unaff_x21;
      _swift_getObjectType(unaff_x21);
      FUN_1001516d8(uVar36,unaff_x21,&stack0x00000008,ppVar27,pcVar11);
      uVar36 = pcVar18->cache;
      uVar1 = pcVar18->vtable;
      in_stack_00000008 = (objc_property_list)pcVar18;
      _swift_unknownObjectRetain(qVar44);
      pcVar15 = pcVar18;
      if (uVar1 >> 1 <= uVar36) {
        pcVar15 = (class_t *)(ulong)(1 < uVar1);
        FUN_10078e124(pcVar15,uVar36 + 1,1,pcVar18);
        in_stack_00000008 = (objc_property_list)pcVar15;
      }
      qVar16 = qVar44;
      _swift_getObjectType(qVar44);
      FUN_1001516d8(uVar36,qVar44,&stack0x00000008,qVar16,pcVar11);
      uVar36 = pcVar15->cache;
      uVar1 = pcVar15->vtable;
      in_stack_00000008 = (objc_property_list)pcVar15;
      _swift_unknownObjectRetain(lVar20);
      pcVar18 = pcVar15;
      if (uVar1 >> 1 <= uVar36) {
        pcVar18 = (class_t *)(ulong)(1 < uVar1);
        FUN_10078e124(pcVar18,uVar36 + 1,1,pcVar15);
        in_stack_00000008 = (objc_property_list)pcVar18;
      }
      lVar17 = lVar20;
      _swift_getObjectType(lVar20);
      FUN_1001516d8(uVar36,lVar20,&stack0x00000008,lVar17,puVar22);
      uVar36 = pcVar18->cache;
      uVar1 = pcVar18->vtable;
      in_stack_00000008 = (objc_property_list)pcVar18;
      _swift_unknownObjectRetain(lVar48);
      pcVar15 = pcVar18;
      if (uVar1 >> 1 <= uVar36) {
        pcVar15 = (class_t *)(ulong)(1 < uVar1);
        FUN_10078e124(pcVar15,uVar36 + 1,1,pcVar18);
        in_stack_00000008 = (objc_property_list)pcVar15;
      }
      lVar20 = lVar48;
      _swift_getObjectType(lVar48);
      FUN_1001516d8(uVar36,lVar48,&stack0x00000008,lVar20,pcVar11);
      uVar36 = pcVar15->cache;
      uVar1 = pcVar15->vtable;
      in_stack_00000008 = (objc_property_list)pcVar15;
      _swift_unknownObjectRetain(lVar46);
      pcVar18 = pcVar15;
      if (uVar1 >> 1 <= uVar36) {
        pcVar18 = (class_t *)(ulong)(1 < uVar1);
        FUN_10078e124(pcVar18,uVar36 + 1,1,pcVar15);
        in_stack_00000008 = (objc_property_list)pcVar18;
      }
      lVar20 = lVar46;
      _swift_getObjectType(lVar46);
      FUN_1001516d8(uVar36,lVar46,&stack0x00000008,lVar20,pcVar11);
      puVar22 = &DAT_100afba00;
      FUN_100021774(&DAT_100afba00);
      uVar26 = 5;
      _swift_arrayDestroy(&stack0x00000030,5,puVar22);
      auVar94._8_8_ = uVar26;
      auVar94._0_8_ = pcVar18;
      return auVar94;
    }
                    /* WARNING: Does not return */
    pcVar9 = (code *)SoftwareBreakpoint(1,0x1007f4fb8);
    (*pcVar9)();
  case (char *)0x8b:
    _swift_getObjectType();
    *(undefined8 *)((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::currentLevel) = 0;
    *(undefined8 *)((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::maxAscentDelta) =
         0x7fefffffffffffff;
    *(undefined8 *)((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::maxDecayDelta) =
         0x7fefffffffffffff;
    *(code *)((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::configured) = (code)0x0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::___lazy_storage___mainStackView) =
         0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView
     ) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView) =
         0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback16MixerVUMeterView::___lazy_storage___levelLayer) = 0;
    pcVar9 = (code *)((long)&unaff_x20->flags +
                     _TtC8Playback16MixerVUMeterView::___lazy_storage___meterFrame);
    *(undefined8 *)(pcVar9 + 8) = 0;
    *(undefined8 *)pcVar9 = 0;
    *(undefined8 *)(pcVar9 + 0x18) = 0;
    *(undefined8 *)(pcVar9 + 0x10) = 0;
    pcVar9[0x20] = (code)0x1;
    pcVar34 = "initWithCoder:";
    in_stack_00000008 = (objc_property_list)pcVar11;
    auVar104._0_8_ = _objc_msgSendSuper2((objc_super *)&stack0x00000000,"initWithCoder:");
    if (auVar104._0_8_ != 0) {
      FUN_1007f72cc(auVar104._0_8_);
    }
    auVar104._8_8_ = pcVar34;
    return auVar104;
  case (char *)0x8c:
    goto switchD_1007daeec_caseD_8c;
  case (char *)0x8d:
    in_stack_00000008 = (objc_property_list)(PTR___sBi64_WV_100a1dca8 + 0x40);
    in_stack_00000018 = (class_rw_t *)&DAT_100956050;
    in_stack_00000020 = (protocol_list_t *)0x100956050;
    in_stack_00000028 = (method_list_t *)&DAT_100956050;
    lVar20 = 0x13f;
    in_stack_00000010 = (class_rw_t *)in_stack_00000008;
    FUN_1000acfc8();
    if (op < (class_rw_t *)0x40) {
      in_stack_00000030 = (protocol_list_t *)(*(long *)(lVar20 + -8) + 0x40);
      in_stack_00000038 = (class_rw_t *)(PTR___sBbWV_100a1dc90 + 0x40);
      _swift_initStructMetadata
                (&DAT_6165627472616568,0x100,7,&stack0x00000008,&DAT_6165627472616578);
      lVar20 = 0;
      uVar26 = 0;
    }
    else {
      uVar26 = 0x3f;
    }
    auVar85._8_8_ = uVar26;
    auVar85._0_8_ = lVar20;
    return auVar85;
  case (char *)0x8e:
    _swift_bridgeObjectRelease();
    op = (char *)unaff_x26[0x112];
    pcVar11 = unaff_x20;
  case (char *)0xc8:
    _objc_msgSend((ID)pcVar11,op);
switchD_1007daeec_caseD_e8:
    unaff_x21 = (protocol_list_t *)_objc_msgSend((ID)unaff_x20,(SEL)unaff_x25[0x1e].baseProtocols);
    if (DAT_100adf4f8 != -1) {
      _swift_once(&DAT_100adf4f8,FUN_10052de80);
    }
switchD_1007daeec_caseD_88:
    pcVar11 = DAT_100b768d8;
    unaff_x22 = DAT_100b768d0;
    *(ID *)(unaff_x29 + -0x58) = unaff_x19;
    *(class_rw_t **)(unaff_x29 + -0x70) = unaff_x20;
    unaff_x23 = pcVar11;
switchD_1007daeec_caseD_be:
    _swift_bridgeObjectRetain(pcVar11);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(unaff_x22,unaff_x23);
    _swift_bridgeObjectRelease(unaff_x23);
    if (unaff_x19 == 0) {
      lVar20 = 0;
    }
    else {
      lVar20 = unaff_x29 + -0x70;
      FUN_100023444(lVar20);
      lVar46 = *(long *)(unaff_x19 - 8);
      lVar48 = (long)&stack0x00000000 - (*(long *)(lVar46 + 0x40) + 0xfU & 0xfffffffffffffff0);
      (**(code **)(lVar46 + 0x10))(lVar48,lVar20);
      lVar20 = lVar48;
      __ss27_bridgeAnythingToObjectiveCyyXlxlF(lVar48);
      (**(code **)(lVar46 + 8))(lVar48);
      FUN_100023468(unaff_x29 + -0x70);
    }
    IVar21 = 0;
    FUN_1007711fc();
    _swift_getObjCClassFromMetadata();
    _objc_allocWithZone();
    IVar21 = _objc_msgSend(IVar21,"initWithTitle:style:target:action:",unaff_x22,0,lVar20,
                           "importButtonItemTapped:");
    _swift_unknownObjectRelease(lVar20);
    pcVar34 = "setRightBarButtonItem:";
    _objc_msgSend((ID)unaff_x21,"setRightBarButtonItem:",IVar21);
    auVar6._8_8_ = 0;
    auVar6._0_8_ = pcVar34;
    return auVar6 << 0x40;
  case (char *)0x8f:
  case (char *)0xe5:
  case (char *)0xfc:
    goto switchD_1007daeec_caseD_8f;
  case (char *)0x92:
    goto switchD_1007daeec_caseD_92;
  case (char *)0x94:
    if (DAT_100adfa40 != -1) {
      _swift_once(&DAT_100adfa40,FUN_1005309d4);
    }
    uVar33 = DAT_100b77368;
    uVar26 = DAT_100b77360;
    IVar21 = 0;
    FUN_100497ca4();
    _swift_bridgeObjectRetain(uVar33);
    _swift_bridgeObjectRetain();
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar26,uVar33);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease();
    _swift_getObjCClassFromMetadata();
    IVar21 = _objc_msgSend(IVar21,"alertControllerWithTitle:message:preferredStyle:",uVar26,
                           unaff_x22,1);
    if (DAT_100adf6d8 != -1) {
      _swift_once(&DAT_100adf6d8,FUN_10052eb50);
    }
    uVar31 = DAT_100b76c98;
    uVar26 = DAT_100b76c90;
    _swift_bridgeObjectRetain(DAT_100b76c98);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar26,uVar31);
    _swift_bridgeObjectRelease(uVar31);
    puVar22 = &_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    IVar23 = _objc_msgSend((ID)puVar22,"actionWithTitle:style:handler:",uVar26,0,0);
    _objc_msgSend(IVar21,"addAction:",IVar23);
    _objc_msgSend(IVar21,"setPreferredAction:",IVar23);
    _swift_bridgeObjectRelease(uVar33);
    _swift_bridgeObjectRelease();
    op = "presentViewController:animated:completion:";
    _objc_msgSend((ID)unaff_x20,"presentViewController:animated:completion:",IVar21,1,0);
    unaff_x19 = 0;
    goto LAB_1007efc2c;
  case (char *)0x95:
  case (char *)0xa9:
    goto switchD_1007daeec_caseD_95;
  case (char *)0x99:
  case (char *)0xad:
    goto switchD_1007daeec_caseD_99;
  case (char *)0x9c:
    goto switchD_1007daeec_caseD_9c;
  case (char *)0x9e:
    unaff_x23 = (class_rw_t *)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    FUN_1004a6154();
    if ((ulong)unaff_x23 >> 0x3e == 0) {
      unaff_x24 = *(class_rw_t **)(((ulong)unaff_x23 & 0xfffffffffffff8) + 0x10);
      unaff_x21 = (protocol_list_t *)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    else {
      unaff_x24 = (class_rw_t *)((ulong)unaff_x23 & 0xffffffffffffff8);
      if ((long)unaff_x23 < 0) {
        unaff_x24 = unaff_x23;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      unaff_x21 = (protocol_list_t *)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    PTR___swiftEmptyArrayStorage_100a1e050 = (undefined *)unaff_x21;
    if (unaff_x24 == (class_rw_t *)0x0) {
      _swift_bridgeObjectRelease(unaff_x23);
      unaff_x21 = (protocol_list_t *)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    else {
      in_stack_00000008 = (objc_property_list)pcVar34;
      if ((long)unaff_x24 < 1) {
                    /* WARNING: Does not return */
        pcVar9 = (code *)SoftwareBreakpoint(1,0x10080dda4);
        (*pcVar9)();
      }
      pcVar45 = (class_rw_t *)0x0;
      unaff_x27 = (class_rw_t *)((ulong)unaff_x23 & 0xc000000000000001);
      in_stack_00000010 = unaff_x22;
      do {
        if (unaff_x27 == (class_rw_t *)0x0) {
          pcVar49 = (class_rw_t *)(&unaff_x23->baseMethods)[(long)pcVar45];
        }
        else {
          pcVar49 = pcVar45;
          FUN_1000cbedc(pcVar45,unaff_x23);
        }
        op = "modularClickLengthValue";
        IVar21 = _objc_msgSend((ID)pcVar49,"modularClickLengthValue");
        if ((int)IVar21 == 0) {
          pcVar11 = DAT_100b757a8;
          if (DAT_100adea10 != -1) {
            pcVar9 = FUN_1001709a4;
            _swift_once(&DAT_100adea10,FUN_1001709a4);
            pcVar11 = DAT_100b757a8;
            op = (char *)pcVar9;
          }
switchD_1007daeec_caseD_b2:
          bVar10 = (byte)pcVar11;
          FUN_1001718ec();
          pcVar49 = pcVar45;
        }
        else {
          op = "modularClickLengthValue";
          IVar21 = _objc_msgSend((ID)pcVar49,"modularClickLengthValue");
          bVar10 = (int)IVar21 == 4;
          pcVar49 = pcVar45;
        }
        ppVar27 = unaff_x21;
        _swift_isUniquelyReferenced_nonNull_native();
        ppVar28 = unaff_x21;
        if (((ulong)ppVar27 & 1) == 0) {
          op = (char *)(unaff_x21[2].count + 1);
          ppVar28 = (protocol_list_t *)0x0;
          FUN_100790e50(0,op,1,unaff_x21);
        }
        uVar36 = ppVar28[2].count;
        pcVar11 = (class_rw_t *)(uVar36 + 1);
        unaff_x21 = ppVar28;
        if (ppVar28[3].count >> 1 <= uVar36) {
          unaff_x21 = (protocol_list_t *)(ulong)(1 < ppVar28[3].count);
          op = (char *)pcVar11;
          FUN_100790e50(unaff_x21,pcVar11,1,ppVar28);
        }
        pcVar45 = (class_rw_t *)((long)&pcVar49->flags + 1);
        unaff_x21[2].count = (qword)pcVar11;
        unaff_x21[uVar36 * 2 + 4].count = (qword)pcVar49;
        *(byte *)&unaff_x21[uVar36 * 2 + 5].count = bVar10 & 1;
      } while (unaff_x24 != pcVar45);
      _swift_bridgeObjectRelease(unaff_x23);
      unaff_x22 = in_stack_00000010;
    }
    in_stack_00000018 = unaff_x22;
    in_stack_00000020 = unaff_x21;
    FUN_10048fd9c(&stack0x00000018);
    in_stack_00000158 = in_stack_00000080;
    in_stack_00000150 = in_stack_00000078;
    in_stack_00000168 = in_stack_00000090;
    in_stack_00000160 = in_stack_00000088;
    uStack0000000000000172 = CONCAT26(in_stack_000000a0,uStack000000000000009a);
    in_stack_00000170 = uStack0000000000000098;
    in_stack_00000118 = in_stack_00000040;
    in_stack_00000110 = (ivar_list_t *)in_stack_00000038;
    in_stack_00000128 = in_stack_00000050;
    in_stack_00000120 = (objc_property_list *)in_stack_00000048;
    in_stack_00000138 = in_stack_00000060;
    in_stack_00000130 = in_stack_00000058;
    in_stack_00000148 = in_stack_00000070;
    in_stack_00000140 = in_stack_00000068;
    in_stack_000000f8 = in_stack_00000020;
    in_stack_000000f0 = in_stack_00000018;
    in_stack_00000108 = in_stack_00000030;
    in_stack_00000100 = in_stack_00000028;
    FUN_1007dfdc0(&stack0x000000f0);
    _swift_bridgeObjectRelease(unaff_x21);
    _swift_bridgeObjectRelease(unaff_x22);
    auVar106._8_8_ = op;
    auVar106._0_8_ = unaff_x22;
    return auVar106;
  case (char *)0x9f:
  case (char *)0xb3:
    __sSQ2eeoiySbx_xtFZTj();
    pcVar9 = *(code **)(unaff_x19 + 8);
    (*pcVar9)();
    pcVar34 = &DAT_100af56b8;
    FUN_100023be4(*(undefined8 *)(unaff_x29 + -0xe8),&DAT_100af56b8);
    FUN_100023be4();
    (*pcVar9)();
    FUN_100023be4();
    if (((ulong)pcVar11 & 1) != 0) goto LAB_10081b7a4;
    iVar40 = (int)unaff_x23 + 1;
    pcVar11 = DAT_100b757a8;
    FUN_10016f2bc();
    pcVar49 = DAT_100b757a8;
    if (pcVar11 == (class_rw_t *)0x0) {
      if (DAT_100adfd70 != -1) {
        _swift_once(&DAT_100adfd70,FUN_100742498);
      }
      lVar20 = DAT_100b778d0;
      puVar47 = *(undefined8 **)(unaff_x29 + -0x100);
      *puVar47 = 0xd000000000000014;
      puVar47[1] = 0x80000001009119c0;
      lVar48 = lVar20;
      _swift_retain();
      FUN_10016fe5c();
      if (lVar48 == 0) {
        uVar26 = 0;
      }
      else {
        uVar26 = *(undefined8 *)(lVar48 + _TtC8Playback15APIOrganization::customerID);
      }
      lVar46 = 0;
      puVar47[2] = uVar26;
      *(bool *)(puVar47 + 3) = lVar48 == 0;
      FUN_100170a78();
      if (lVar46 == 0) {
        uVar26 = 0;
        cVar41 = (code)0x1;
      }
      else {
        pcVar9 = (code *)((long)&pcVar49->flags +
                         _TtC8Playback15DefaultsManager::___lazy_storage___privateCurrentUserID);
        uVar26 = *(undefined8 *)pcVar9;
        cVar41 = pcVar9[8];
      }
      puVar22 = &DAT_100b086f0;
      FUN_100021774();
      iVar2 = *(int *)(puVar22 + 0x50);
      puVar47[4] = uVar26;
      *(code *)(puVar47 + 5) = cVar41;
      lVar48 = 0;
      FUN_1006a8c58();
      (**(code **)(*(long *)(lVar48 + -8) + 0x38))((long)puVar47 + (long)iVar2,1,1,lVar48);
      _swift_storeEnumTagMultiPayload(puVar47,*(undefined8 *)(unaff_x29 + -0x108),4);
      FUN_1007421dc(puVar47);
      _swift_release(lVar20);
      FUN_1000233c8(puVar47,FUN_100893664);
    }
    else {
      *(short *)((long)&pcVar11->flags + _TtC8Playback7APIUser::subscriptionTierID) = (short)iVar40;
      lVar20 = _TtC8Playback7APIUser::subscriptionExpirationDate;
      _swift_beginAccess((code *)((long)&pcVar11->flags +
                                 _TtC8Playback7APIUser::subscriptionExpirationDate),
                         unaff_x29 + -0x98,0x21,0);
      (**(code **)(*(long *)(unaff_x29 + -0xd8) + 0x18))
                ((code *)((long)&pcVar11->flags + lVar20),*(undefined8 *)(unaff_x29 + -0xd0));
      _swift_endAccess(unaff_x29 + -0x98);
      uVar26 = *(undefined8 *)
                ((long)&DAT_100b757a8->flags +
                _TtC8Playback15DefaultsManager::___lazy_storage___currentUser);
      *(class_rw_t **)
       ((long)&DAT_100b757a8->flags + _TtC8Playback15DefaultsManager::___lazy_storage___currentUser)
           = pcVar11;
      FUN_10003995c(uVar26);
      puVar22 = &_OBJC_CLASS___NSUserDefaults;
      _swift_getInitializedObjCClass();
      IVar21 = _objc_msgSend((ID)puVar22,"standardUserDefaults");
      FUN_10016f2bc(IVar21);
      FUN_1000bc8a4();
    }
    if (iVar40 == 3) {
      puVar22 = &_OBJC_CLASS___UIDevice;
      _swift_getInitializedObjCClass();
      _objc_msgSend((ID)puVar22,"currentDevice");
      if (DAT_100ae0098 != -1) {
        _swift_once(&DAT_100ae0098,FUN_1008261bc);
      }
      if ((7 < DAT_100b0ec78) || ((1 << (ulong)(DAT_100b0ec78 & 0x1f) & 0xc2U) == 0))
      goto LAB_10081b034;
      uVar36 = 0xd000000000000021;
      thunk_FUN_1001794a0(0xd000000000000021,0x80000001008d4a00,0);
      if ((uVar36 & 1) != 0) goto LAB_10081b034;
      puVar22 = &_OBJC_CLASS___NSBundle;
      _swift_getInitializedObjCClass();
      IVar21 = _objc_msgSend((ID)puVar22,"mainBundle");
      uVar26 = 0xd00000000000009b;
      uVar33 = 0x80000001009119e0;
      __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
                (0xd00000000000009b,0x80000001009119e0,0,0,IVar21,0,0xe000000000000000,0,
                 0xe000000000000000);
      puVar22 = &_OBJC_CLASS___UIApplication;
      _swift_getInitializedObjCClass();
      IVar21 = _objc_msgSend((ID)puVar22,"sharedApplication");
      IVar21 = _objc_msgSend(IVar21,"delegate");
      if (IVar21 == 0) {
        _swift_bridgeObjectRelease(uVar33);
      }
      else {
        uVar31 = 0;
        FUN_100842dec(0);
        IVar23 = IVar21;
        _swift_dynamicCastClass(IVar21,uVar31);
        if (((IVar23 == 0) || (*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window) == 0)) ||
           (IVar23 = _objc_msgSend(*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window),
                                   "rootViewController"), IVar23 == 0)) {
          _swift_bridgeObjectRelease(uVar33);
          _swift_unknownObjectRelease(IVar21);
        }
        else {
          IVar29 = _objc_msgSend(IVar23,"presentedViewController");
          while (IVar29 != 0) {
            IVar30 = _objc_msgSend(IVar29,"presentedViewController",IVar23);
            IVar23 = IVar29;
            IVar29 = IVar30;
          }
          _swift_unknownObjectRelease(IVar21);
          if (DAT_100ae0080 != -1) {
            _swift_once(&DAT_100ae0080,FUN_100819dec);
          }
          uVar31 = DAT_100b77e90;
          *(undefined8 *)(unaff_x29 + -200) = DAT_100b77e88;
          lVar20 = DAT_100adf6d8;
          _swift_bridgeObjectRetain(uVar31);
          if (lVar20 != -1) {
            _swift_once(&DAT_100adf6d8,FUN_10052eb50);
          }
          uVar51 = DAT_100b76c98;
          uVar50 = DAT_100b76c90;
          _swift_bridgeObjectRetain(DAT_100b76c98);
          FUN_100430fec(*(undefined8 *)(unaff_x29 + -200),uVar31,uVar26,uVar33,0,0,0,0,uVar50,uVar51
                        ,0,0,0,0);
          _swift_bridgeObjectRelease(uVar31);
          _swift_bridgeObjectRelease(uVar51);
          _swift_bridgeObjectRelease(uVar33);
        }
      }
      puVar22 = &_OBJC_CLASS___NSUserDefaults;
      _swift_getInitializedObjCClass();
      IVar21 = _objc_msgSend((ID)puVar22,"standardUserDefaults");
      uVar26 = 0xd000000000000021;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000021,0x80000001008d4a00);
      _objc_msgSend(IVar21,"setBool:forKey:",1,uVar26);
    }
    else {
LAB_10081b034:
      uVar36 = (ulong)*(uint *)(unaff_x29 + -200);
      if ((*(uint *)(unaff_x29 + -200) & 0xff) < (uint)unaff_x28) {
        puVar22 = &_OBJC_CLASS___NSUserDefaults;
        _swift_getInitializedObjCClass();
        IVar21 = _objc_msgSend((ID)puVar22,"standardUserDefaults");
        uVar26 = 0xd000000000000021;
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000021,0x80000001008d4a00)
        ;
        _objc_msgSend(IVar21,"removeObjectForKey:",uVar26);
        FUN_100819154();
        if (uVar36 != 0) {
          puVar22 = &_OBJC_CLASS___UIApplication;
          _swift_getInitializedObjCClass();
          IVar21 = _objc_msgSend((ID)puVar22,"sharedApplication");
          IVar21 = _objc_msgSend(IVar21,"delegate");
          if (IVar21 == 0) {
            _swift_bridgeObjectRelease(uVar36);
          }
          else {
            uVar26 = 0;
            FUN_100842dec(0);
            IVar23 = IVar21;
            _swift_dynamicCastClass(IVar21,uVar26);
            if (((IVar23 == 0) || (*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window) == 0)) ||
               (IVar23 = _objc_msgSend(*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window),
                                       "rootViewController"), IVar23 == 0)) {
              _swift_bridgeObjectRelease(uVar36);
              _swift_unknownObjectRelease(IVar21);
            }
            else {
              IVar29 = _objc_msgSend(IVar23,"presentedViewController");
              while (IVar29 != 0) {
                IVar30 = _objc_msgSend(IVar29,"presentedViewController",IVar23);
                IVar23 = IVar29;
                IVar29 = IVar30;
              }
              _swift_unknownObjectRelease(IVar21);
              if (DAT_100ae0080 != -1) {
                _swift_once(&DAT_100ae0080,FUN_100819dec);
              }
              uVar33 = DAT_100b77e90;
              uVar26 = DAT_100b77e88;
              lVar20 = DAT_100adf6d8;
              _swift_bridgeObjectRetain(DAT_100b77e90);
              if (lVar20 != -1) {
                _swift_once(&DAT_100adf6d8,FUN_10052eb50);
              }
              uVar50 = DAT_100b76c98;
              uVar31 = DAT_100b76c90;
              _swift_bridgeObjectRetain(DAT_100b76c98);
              FUN_100430fec(uVar26,uVar33,unaff_x28,uVar36,0,0,0,0,uVar31,uVar50,0,0,0,0);
              _swift_bridgeObjectRelease(uVar33);
              _swift_bridgeObjectRelease(uVar50);
              _swift_bridgeObjectRelease(uVar36);
            }
          }
        }
      }
    }
    puVar22 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar21 = _objc_msgSend((ID)puVar22,"sharedApplication");
    IVar21 = _objc_msgSend(IVar21,"delegate");
    if (IVar21 != 0) {
      uVar26 = 0;
      FUN_100842dec(0);
      IVar23 = IVar21;
      _swift_dynamicCastClass(IVar21,uVar26);
      if (((IVar23 == 0) || (*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar23 = _objc_msgSend(*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window),
                                 "rootViewController"), IVar23 == 0)) {
        _swift_unknownObjectRelease(IVar21);
      }
      else {
        uVar26 = 0;
        FUN_100413a94(0);
        _swift_dynamicCastClass(IVar23,uVar26);
        _swift_unknownObjectRelease(IVar21);
        if ((IVar23 != 0) &&
           (lVar20 = *(long *)(IVar23 + _TtC8Playback18MainViewController::mixerViewController),
           lVar20 != 0)) {
          uVar26 = *(undefined8 *)
                    (lVar20 + _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks);
          *(undefined8 *)
           (lVar20 + _TtC8Playback19MixerViewController::privateCurrentDisplayableTracks) = 0;
          _swift_bridgeObjectRelease(uVar26);
        }
      }
    }
    IVar21 = _objc_msgSend((ID)puVar22,"sharedApplication");
    IVar21 = _objc_msgSend(IVar21,"delegate");
    if (IVar21 != 0) {
      uVar26 = 0;
      FUN_100842dec(0);
      IVar23 = IVar21;
      _swift_dynamicCastClass(IVar21,uVar26);
      if (((IVar23 == 0) || (*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar23 = _objc_msgSend(*(ID *)(IVar23 + _TtC8Playback11AppDelegate::window),
                                 "rootViewController"), IVar23 == 0)) {
        _swift_unknownObjectRelease(IVar21);
      }
      else {
        uVar26 = 0;
        FUN_100413a94(0);
        _swift_dynamicCastClass(IVar23,uVar26);
        _swift_unknownObjectRelease(IVar21);
        if ((IVar23 != 0) &&
           (*(long *)(IVar23 + _TtC8Playback18MainViewController::mixerViewController) != 0)) {
          lVar20 = *(long *)(IVar23 + _TtC8Playback18MainViewController::mixerViewController) +
                   _TtC8Playback19MixerViewController::tracksCollectionView;
          _swift_unknownObjectWeakLoadStrong();
          if (lVar20 != 0) {
            uVar26 = 0;
            FUN_100307654();
            *(long *)(unaff_x29 + -0xa8) = lVar20;
            *(undefined8 *)(unaff_x29 + -0xa0) = uVar26;
            _objc_msgSendSuper2((objc_super *)(unaff_x29 + -0xa8),"reloadData");
          }
        }
      }
    }
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    IVar21 = *(ID *)(DAT_100b75a80 + 0x10);
    if (IVar21 != 0) {
      IVar23 = _objc_msgSend(IVar21,"currentSetlistIndex");
      if (IVar23 == 0xffffffffffffffff) {
        FUN_1004aaf8c();
      }
      else {
        IVar21 = _objc_msgSend(IVar21,"currentSetlistIndex");
        FUN_1004a67f4(IVar21,1,1,0);
      }
    }
    puVar22 = &_OBJC_CLASS___NSNotificationCenter;
    _swift_getInitializedObjCClass();
    IVar21 = _objc_msgSend((ID)puVar22,"defaultCenter");
    if (DAT_100adeb80 != -1) {
      _swift_once(&DAT_100adeb80,FUN_1001f9144);
    }
    pcVar34 = "postNotificationName:object:";
    _objc_msgSend(IVar21,"postNotificationName:object:",DAT_100b75948,0);
    unaff_x26 = (undefined8 *)0x0;
LAB_10081b7a4:
    auVar107._8_8_ = pcVar34;
    auVar107._0_8_ = unaff_x26;
    return auVar107;
  case (char *)0xa4:
    if (param_4 == (class_rw_t *)0x0) {
      param_4 = (class_rw_t *)0x0;
      op = (char *)0x0;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(param_4);
    }
    FUN_1007f5f2c(param_4,op,param_5);
    auVar97._8_8_ = op;
    auVar97._0_8_ = param_4;
    return auVar97;
  case (char *)0xa6:
    goto switchD_1007daeec_caseD_a6;
  case (char *)0xa8:
    FUN_1007efe94();
    _swift_bridgeObjectRelease();
LAB_1007efc2c:
    auVar81._8_8_ = op;
    auVar81._0_8_ = unaff_x19;
    return auVar81;
  case (char *)0xb0:
    goto switchD_1007daeec_caseD_b0;
  case (char *)0xb2:
    goto switchD_1007daeec_caseD_b2;
  case (char *)0xb8:
    FUN_1007f60b0(param_4);
    auVar99._8_8_ = op;
    auVar99._0_8_ = param_4;
    return auVar99;
  case (char *)0xba:
  case (char *)0xd9:
  case (char *)0xed:
    goto switchD_1007daeec_caseD_ba;
  case (char *)0xbb:
  case (char *)0xda:
  case (char *)0xee:
    _swift_once(0x6165627472617120,FUN_1005b50bc);
    CVar42 = DAT_100b77548->instanceSize;
    FUN_1000a1b5c(CVar42);
    FUN_1001d8b1c(CVar42);
    FUN_100092550(CVar42);
    pcVar18 = *(class_t **)(unaff_x19 + _TtC8Playback30TransportMappingViewController::deleteButton)
    ;
    if (pcVar18 != (class_t *)0x0) {
      *(code *)((long)&pcVar18->isa + _TtC8Playback21TransportDeleteButton::mode) = (code)0x1;
      pcVar15 = pcVar18;
      if (DAT_100adf390 != -1) {
        pcVar15 = (class_t *)&DAT_100adf390;
        _swift_once(&DAT_100adf390,FUN_10052d408);
      }
      in_stack_00000040 = DAT_100b76600;
      in_stack_00000048 = (class_rw_t *)DAT_100b76608;
      in_stack_00000030 = (protocol_list_t *)0x20;
      in_stack_00000038 = (class_rw_t *)0xe100000000000000;
      in_stack_00000020 = (protocol_list_t *)0xa;
      in_stack_00000028 = (method_list_t *)0xe100000000000000;
      FUN_10003bed0();
      in_stack_00000000 = PTR___sSSN_100a1dce0;
      puVar47 = &stack0x00000030;
      puVar19 = &stack0x00000020;
      in_stack_00000008 = (objc_property_list)pcVar15;
      in_stack_00000010 = (class_rw_t *)pcVar15;
      in_stack_00000018 = (class_rw_t *)pcVar15;
      __sSy10FoundationE20replacingOccurrences2of4with7options5rangeSSqd___qd_0_So22NSStringCompareOptionsVSnySS5IndexVGSgtSyRd__SyRd_0_r0_lF
                (puVar47,puVar19,0,0,0,1,PTR___sSSN_100a1dce0,PTR___sSSN_100a1dce0);
      puVar32 = puVar19;
      __sSS10uppercasedSSyF();
      _swift_bridgeObjectRelease(puVar19);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(puVar47,puVar32);
      _swift_bridgeObjectRelease(puVar32);
      _objc_msgSend((ID)pcVar18,"setTitle:forState:",puVar47,0);
    }
    puVar22 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    pcVar34 = "currentDevice";
    IVar21 = _objc_msgSend((ID)puVar22,"currentDevice");
    iVar40 = (int)IVar21;
    FUN_100826670();
    if ((iVar40 - 0xcU & 0xff) < 0xe) {
      uVar26 = *(undefined8 *)(&DAT_100956868 + ((ulong)(iVar40 - 0xcU) & 0xff) * 8);
      if (*(ID *)(unaff_x19 +
                 _TtC8Playback30TransportMappingViewController::selectButtonWidthConstaint) != 0) {
        pcVar34 = "setConstant:";
        _objc_msgSend(*(ID *)(unaff_x19 +
                             _TtC8Playback30TransportMappingViewController::
                             selectButtonWidthConstaint),"setConstant:",uVar26);
      }
      if (*(ID *)(unaff_x19 +
                 _TtC8Playback30TransportMappingViewController::globalTemplatesButtonWidthConstaint)
          != 0) {
        pcVar34 = "setConstant:";
        _objc_msgSend(*(ID *)(unaff_x19 +
                             _TtC8Playback30TransportMappingViewController::
                             globalTemplatesButtonWidthConstaint),"setConstant:",uVar26);
      }
    }
    IVar21 = 0;
    if (*(ID *)(unaff_x19 + _TtC8Playback30TransportMappingViewController::globalTemplatesButton) !=
        0) {
      pcVar34 = "setHidden:";
      IVar21 = _objc_msgSend(*(ID *)(unaff_x19 +
                                    _TtC8Playback30TransportMappingViewController::
                                    globalTemplatesButton),"setHidden:",1);
    }
    auVar95._8_8_ = pcVar34;
    auVar95._0_8_ = IVar21;
    return auVar95;
  case (char *)0xbd:
  case (char *)0xdc:
  case (char *)0xf0:
    *(undefined1 **)pcVar34 = &DAT_6165627472616568;
    goto switchD_1007daeec_caseD_87;
  case (char *)0xbe:
  case (char *)0xdd:
  case (char *)0xf1:
    goto switchD_1007daeec_caseD_be;
  case (char *)0xc0:
  case (char *)0xe0:
    pcVar34 = "initWithNibName:bundle:";
    auVar96._0_8_ = _objc_msgSendSuper2((objc_super *)&stack0x00000000,"initWithNibName:bundle:");
    auVar96._8_8_ = pcVar34;
    return auVar96;
  case (char *)0xc1:
  case (char *)0xe1:
    uVar26 = 0xe900000000000b04;
    _swift_getWitnessTable(&DAT_6165627472616568,0xe900000000000b04);
    DAT_100b0e348 = pcVar11;
    auVar91._8_8_ = uVar26;
    auVar91._0_8_ = pcVar11;
    return auVar91;
  case (char *)0xc2:
  case (char *)0xe2:
  case (char *)0xd1:
  case (char *)0xec:
  case (char *)0xf9:
    FUN_10041ac94();
    _swift_setDeallocating();
    FUN_100023468();
    *(class_rw_t **)(unaff_x29 + -200) = unaff_x23;
    _swift_errorRetain();
    FUN_100021774(&DAT_100af5dc0);
    pcVar49 = unaff_x24;
    _swift_dynamicCast();
    if ((int)pcVar49 != 0) {
      pcVar49 = unaff_x24;
      _swift_getEnumCaseMultiPayload();
      if ((int)pcVar49 == 7) {
        pcVar49 = (class_rw_t *)unaff_x24->instanceStart;
        pcVar11 = (class_rw_t *)unaff_x24->instanceSize;
        pcVar34 = unaff_x24->name;
        pcVar45 = (class_rw_t *)unaff_x24->baseMethods;
        unaff_x23 = (class_rw_t *)unaff_x24->baseProtocols;
        unaff_x20 = (class_rw_t *)unaff_x24->ivars;
        puVar22 = &DAT_100af5e18;
        FUN_100021774();
        FUN_10004ca78((code *)((long)&unaff_x24->flags + (long)*(int *)(puVar22 + 0x60)),
                      *(undefined8 *)(unaff_x29 + -0x128));
        IVar21 = 0;
        FUN_100497ca4();
        if (pcVar11 == (class_rw_t *)0x0) {
          if (unaff_x20 != (class_rw_t *)0x0) {
            _swift_bridgeObjectRetain(unaff_x20);
            pcVar49 = unaff_x23;
            pcVar11 = unaff_x20;
            goto LAB_1007f816c;
          }
          pcVar49 = (class_rw_t *)0x0;
          if (pcVar45 == (class_rw_t *)0x0) goto LAB_1007f847c;
LAB_1007f8188:
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(pcVar34,pcVar45);
          _swift_bridgeObjectRelease(pcVar45);
        }
        else {
LAB_1007f816c:
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(pcVar49,pcVar11);
          _swift_bridgeObjectRelease(pcVar11);
          if (pcVar45 != (class_rw_t *)0x0) goto LAB_1007f8188;
LAB_1007f847c:
          pcVar34 = (char *)0x0;
        }
        _swift_getObjCClassFromMetadata();
        unaff_x24 = (class_rw_t *)
                    _objc_msgSend(IVar21,"alertControllerWithTitle:message:preferredStyle:",pcVar49,
                                  pcVar34,1);
switchD_1007daeec_caseD_c7:
        if (DAT_100adf290 != -1) {
          _swift_once(&DAT_100adf290,FUN_10052c998);
        }
        uVar33 = DAT_100b76408;
        uVar26 = DAT_100b76400;
        _swift_bridgeObjectRetain(DAT_100b76408);
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar26,uVar33);
        _swift_bridgeObjectRelease(uVar33);
        puVar24 = &_OBJC_CLASS___UIAlertAction;
        _swift_getInitializedObjCClass();
        IVar21 = _objc_msgSend((ID)puVar24,"actionWithTitle:style:handler:",uVar26,1,0);
        _objc_msgSend((ID)unaff_x24,"addAction:",IVar21);
        FUN_10004cac0(*(undefined8 *)(unaff_x29 + -0x128));
        uVar36 = (ulong)(byte)unaff_x21[10].count;
        puVar22 = &DAT_100a6af60;
        _swift_allocObject(&DAT_100a6af60,
                           (uVar36 + 0x10 & (uVar36 ^ 0xffffffffffffffff)) +
                           *(long *)(unaff_x29 + -0x130),uVar36 | 7);
        FUN_10004ca78();
        if (unaff_x20 == (class_rw_t *)0x0) {
          unaff_x23 = (class_rw_t *)0x0;
        }
        else {
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(unaff_x23,unaff_x20);
          _swift_bridgeObjectRelease(unaff_x20);
        }
        *(code **)(unaff_x29 + -0xf8) = FUN_1007fa3bc;
        *(undefined **)(unaff_x29 + -0xf0) = puVar22;
        *(undefined **)(unaff_x29 + -0x118) = PTR___NSConcreteStackBlock_100a1d8e8;
        *(undefined8 *)(unaff_x29 + -0x110) = 0x42000000;
        *(code **)(unaff_x29 + -0x108) = FUN_100029ac0;
        *(undefined **)(unaff_x29 + -0x100) = &DAT_100a6af78;
        pvVar25 = __Block_copy((void *)(unaff_x29 + -0x118));
        _swift_release(*(undefined8 *)(unaff_x29 + -0xf0));
        IVar21 = _objc_msgSend((ID)puVar24,"actionWithTitle:style:handler:",unaff_x23,0,pvVar25);
        __Block_release(pvVar25);
        _objc_msgSend((ID)unaff_x24,"addAction:",IVar21);
        pcVar34 = "presentViewController:animated:completion:";
        _objc_msgSend(*(ID *)(unaff_x29 + -0x120),"presentViewController:animated:completion:",
                      unaff_x24,1,0);
        FUN_1000975d0(*(undefined8 *)(unaff_x29 + -0x128));
        uVar26 = *(undefined8 *)(unaff_x29 + -200);
        _swift_errorRelease(uVar26);
        goto LAB_1007f86a0;
      }
      FUN_1000233c8();
    }
    _swift_errorRelease(*(undefined8 *)(unaff_x29 + -200));
    if (DAT_100adf470 != -1) {
      _swift_once(&DAT_100adf470,FUN_10052d9d0);
    }
    unaff_x21 = DAT_100b767c8;
    unaff_x22 = DAT_100b767c0;
    puVar22 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    _swift_bridgeObjectRetain(unaff_x21);
    IVar21 = _objc_msgSend((ID)puVar22,"mainBundle");
    uVar33 = 0x80000001009101a0;
    uVar26 = 0xd00000000000001c;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd00000000000001c,0x80000001009101a0,0,0,IVar21,0,0xe000000000000000,0,
               0xe000000000000000);
    *(undefined8 *)(unaff_x29 + -0x118) = uVar26;
    *(undefined8 *)(unaff_x29 + -0x110) = uVar33;
    _swift_bridgeObjectRetain(uVar33);
    __sSS6appendyySSF(0x202d20,0xe300000000000000);
    _swift_bridgeObjectRelease(uVar33);
    pcVar34 = (char *)(unaff_x29 + -0x18);
switchD_1007daeec_caseD_b0:
    unaff_x25 = (class_rw_t *)((class_t *)((long)pcVar34 + -0x118))->vtable;
    unaff_x19 = *(ID *)(unaff_x29 + -0x110);
    _swift_getErrorValue();
    unaff_x23 = *(class_rw_t **)(unaff_x29 + -0xe0);
    unaff_x24 = *(class_rw_t **)(unaff_x29 + -0xd8);
    FUN_1002c33f8(unaff_x23,unaff_x24);
switchD_1007daeec_caseD_a6:
    *(class_rw_t **)(unaff_x29 + -0x118) = unaff_x25;
    *(ID *)(unaff_x29 + -0x110) = unaff_x19;
    _swift_bridgeObjectRetain(unaff_x19);
    __sSS6appendyySSF(unaff_x23,unaff_x24);
    _swift_bridgeObjectRelease(unaff_x19);
switchD_1007daeec_caseD_9c:
    _swift_bridgeObjectRelease(unaff_x24);
    unaff_x19 = *(ID *)(unaff_x29 + -0x118);
    pcVar11 = *(class_rw_t **)(unaff_x29 + -0x110);
    unaff_x23 = (class_rw_t *)0x0;
    FUN_100497ca4();
    _swift_bridgeObjectRetain(unaff_x21);
    unaff_x20 = pcVar11;
switchD_1007daeec_caseD_92:
    _swift_bridgeObjectRetain(pcVar11);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(unaff_x22,unaff_x21);
    _swift_bridgeObjectRelease(unaff_x21);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(unaff_x19,unaff_x20);
    _swift_bridgeObjectRelease(unaff_x20);
    _swift_getObjCClassFromMetadata();
    IVar21 = _objc_msgSend((ID)unaff_x23,"alertControllerWithTitle:message:preferredStyle:",
                           unaff_x22,unaff_x19,1);
    if (DAT_100adf6d8 != -1) {
      _swift_once(&DAT_100adf6d8,FUN_10052eb50);
    }
    uVar33 = DAT_100b76c98;
    uVar26 = DAT_100b76c90;
    _swift_bridgeObjectRetain(DAT_100b76c98);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar26,uVar33);
    _swift_bridgeObjectRelease(uVar33);
    puVar22 = &_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    IVar23 = _objc_msgSend((ID)puVar22,"actionWithTitle:style:handler:",uVar26,0,0);
    _objc_msgSend(IVar21,"addAction:",IVar23);
    _objc_msgSend(IVar21,"setPreferredAction:",IVar23);
    _swift_bridgeObjectRelease(unaff_x20);
    _swift_bridgeObjectRelease(unaff_x21);
    pcVar34 = "presentViewController:animated:completion:";
    _objc_msgSend(*(ID *)(unaff_x29 + -0x120),"presentViewController:animated:completion:",IVar21,1,
                  0);
    uVar26 = 0;
LAB_1007f86a0:
    auVar105._8_8_ = pcVar34;
    auVar105._0_8_ = uVar26;
    return auVar105;
  case (char *)0xc3:
  case (char *)0xd2:
    if ((int)unaff_x22 == 0x952aa0) {
      pcVar9 = (code *)((long)&unaff_x20->flags + (long)*(int *)((long)&unaff_x21[4].count + 4));
                    /* WARNING: Could not emulate address calculation at 0x0001007f3c04 */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)((long)pcVar34 + 0x38))(pcVar9);
      auVar83._8_8_ = unaff_x19;
      auVar83._0_8_ = pcVar9;
      return auVar83;
    }
    *(ulong *)((long)&unaff_x20->flags + (long)(int)unaff_x21[5].count) = (ulong)(iVar40 - 1);
    auVar84._8_8_ = &DAT_e900000000000074;
    auVar84._0_8_ = &DAT_6165627472616568;
    return auVar84;
  case (char *)0xc4:
  case (char *)0xd3:
    auVar90._8_8_ = &DAT_e900000000000074;
    auVar90._0_8_ = &DAT_6165627472616568;
    return auVar90;
  case (char *)0xc6:
  case (char *)0xd5:
    auVar88._8_8_ = &DAT_e900000000000074;
    auVar88._0_8_ = &DAT_6165627472616568;
    return auVar88;
  case (char *)0xc7:
    goto switchD_1007daeec_caseD_c7;
  case (char *)0xc9:
    FUN_10079c390();
    _swift_setDeallocating();
    puVar22 = &DAT_100af6c60;
    FUN_100023be4();
    _swift_bridgeObjectRelease(unaff_x21);
    auVar80._8_8_ = puVar22;
    auVar80._0_8_ = unaff_x21;
    return auVar80;
  case (char *)0xca:
    __ss22KeyedEncodingContainerV6encode_6forKeyySS_xtKF();
    (*(code *)unaff_x25->instanceStart)();
    auVar86._8_8_ = unaff_x19;
    auVar86._0_8_ = unaff_x23;
    return auVar86;
  case (char *)0xcb:
    goto switchD_1007daeec_caseD_cb;
  case (char *)0xcc:
    pcVar34 = (char *)0xe800000000000000;
    __s14KeychainAccess0A0C6remove_31ignoringAttributeSynchronizableySS_SbtKF
              (&DAT_6165627472616568,0xe800000000000000,1);
    if (unaff_x21 != (protocol_list_t *)0x0) {
      _swift_errorRelease();
    }
    _swift_release();
    _swift_release();
    FUN_1007f0e48();
    if (((ulong)unaff_x23 & 1) != 0) {
      *(undefined1 *)
       (unaff_x22[0x1b].instanceSize +
       _TtC8Playback15DefaultsManager::___lazy_storage___biometricLoginEnablePopupShown) = 1;
      puVar22 = &_OBJC_CLASS___NSUserDefaults;
      _swift_getInitializedObjCClass();
      IVar23 = _objc_msgSend((ID)puVar22,"standardUserDefaults");
      IVar21 = IVar23;
      FUN_100172d48();
      puVar12 = (undefined1 *)((long)&unaff_x27->instanceStart + 3);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(puVar12,0x80000001008da5f0);
      pcVar34 = "setBool:forKey:";
      _objc_msgSend(IVar23,"setBool:forKey:",(ulong)((uint)IVar21 & 1),puVar12);
    }
    auVar3._8_8_ = 0;
    auVar3._0_8_ = pcVar34;
    return auVar3 << 0x40;
  case (char *)0xcd:
    iVar40 = 0;
    if (unaff_x25 == *(class_rw_t **)pcVar34) {
      iVar40 = (int)unaff_x27;
    }
    if (iVar40 == 1) {
      _swift_bridgeObjectRelease();
      IVar21 = _objc_msgSend(unaff_x19,"navigationController");
      pcVar34 = "popViewControllerAnimated:";
      _objc_msgSend(IVar21,"popViewControllerAnimated:",1);
    }
    else {
      in_stack_00000010 = unaff_x25;
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      IVar21 = _objc_msgSend((ID)unaff_x21,"cellForRowAtIndexPath:",pcVar11);
      if (IVar21 != 0) {
        iVar40 = 2;
        FUN_1008c26ac(2,0xd,0,0);
        puVar22 = &_OBJC_CLASS___UIActivityIndicatorView;
        _objc_allocWithZone();
        uVar26 = 2;
        if (iVar40 != 0) {
          uVar26 = 100;
        }
        IVar23 = _objc_msgSend((ID)puVar22,"initWithActivityIndicatorStyle:",uVar26);
        _objc_msgSend(IVar23,"startAnimating");
        _objc_msgSend(IVar21,"setAccessoryView:",IVar23);
      }
      in_stack_00000008 =
           *(objc_property_list *)
            (unaff_x19 + _TtC8Playback44SongMenuProductionCuesSelectorViewController::contentID);
      pcVar34 = *(char **)(unaff_x19 +
                          _TtC8Playback44SongMenuProductionCuesSelectorViewController::
                          demoSetlistSongID);
      iVar40 = 0;
      if ((int)unaff_x27 == 0) {
        iVar40 = (int)unaff_x23;
      }
      puVar22 = &DAT_100a6af10;
      _swift_allocObject(&DAT_100a6af10,0x18,7);
      _swift_unknownObjectWeakInit(puVar22 + 0x10);
      puVar24 = &DAT_100a6af38;
      _swift_allocObject(&DAT_100a6af38,0x40,7);
      *(undefined **)(puVar24 + 0x10) = puVar22;
      *(class_rw_t **)(puVar24 + 0x18) = in_stack_00000010;
      *(undefined8 **)(puVar24 + 0x20) = unaff_x26;
      *(class_rw_t **)(puVar24 + 0x28) = unaff_x22;
      *(ID *)(puVar24 + 0x30) = IVar21;
      *(protocol_list_t **)(puVar24 + 0x38) = unaff_x21;
      _swift_bridgeObjectRetain();
      _swift_retain(puVar22);
      FUN_100450684(in_stack_00000008,pcVar34,iVar40,FUN_1007fa31c,puVar24,in_stack_00000010);
      _swift_release(puVar22);
      _swift_release(puVar24);
      _swift_bridgeObjectRelease();
    }
    auVar7._8_8_ = 0;
    auVar7._0_8_ = pcVar34;
    return auVar7 << 0x40;
  case (char *)0xce:
    goto switchD_1007daeec_caseD_ce;
  case (char *)0xd0:
  case (char *)0xf8:
    _swift_once();
    pcVar11 = DAT_100b77548;
    _swift_retain(DAT_100b77548);
    FUN_1005b4ed4(0x8000000000000000);
    goto switchD_1007daeec_caseD_ba;
  case (char *)0xd6:
    IVar21 = _objc_msgSend(0x6165627472616568,&DAT_e900000000000074);
    _objc_msgSend(unaff_x19,"setBackgroundColor:",IVar21);
    pcVar34 = "setTranslatesAutoresizingMaskIntoConstraints:";
    _objc_msgSend(unaff_x19,"setTranslatesAutoresizingMaskIntoConstraints:",0);
    *(ID *)((long)&unaff_x22->flags + (long)&unaff_x20->flags) = unaff_x19;
    auVar103._8_8_ = pcVar34;
    auVar103._0_8_ = unaff_x19;
    return auVar103;
  case (char *)0xd7:
    op = (char *)&stack0x00000008;
    _swift_beginAccess(DAT_100b778c8 + 0x18,op,0x21,0);
    _swift_retain(lVar20);
    FUN_100799168();
    _swift_endAccess(&stack0x00000008);
    _swift_release(lVar20);
    pcVar11 = (class_rw_t *)0x0;
    goto switchD_1007daeec_caseD_cb;
  case (char *)0xd8:
    goto switchD_1007daeec_caseD_8f;
  case (char *)0xe3:
  case (char *)0xfa:
    auVar102._8_8_ = &DAT_e900000000000074;
    auVar102._0_8_ = unaff_x19;
    return auVar102;
  case (char *)0xe4:
  case (char *)0xfb:
    __ss6HasherV5_seedABSi_tcfC();
    pcVar34 = &DAT_e500000000000000;
    puVar37 = (ushort *)0x4449737562;
    oVar13.entsize = 0;
    oVar13.count = 0xe3000000;
    puVar38 = (ushort *)0x737562;
    in_ZR = iVar40 == 3;
    in_x12 = 0x6e6f6974;
    goto switchD_1007daeec_caseD_8c;
  case (char *)0xe6:
  case (char *)0xfd:
    pTVar14 = &TargetProtocolConformanceDescriptor_100956258;
    puVar22 = &DAT_100a6aa00;
    _swift_getWitnessTable(&TargetProtocolConformanceDescriptor_100956258,&DAT_100a6aa00);
    DAT_100b0e340 = pTVar14;
    auVar89._8_8_ = puVar22;
    auVar89._0_8_ = pTVar14;
    return auVar89;
  case (char *)0xe7:
  case (char *)0xfe:
    _swift_getObjectType();
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::previousSongButton) =
         0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::previousSectionButton
     ) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::selectButton) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::nextSectionButton) =
         0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::nextSongButton) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::deleteButton) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags + _TtC8Playback30TransportMappingViewController::globalTemplatesButton
     ) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags +
     _TtC8Playback30TransportMappingViewController::selectButtonWidthConstaint) = 0;
    *(undefined8 *)
     ((long)&unaff_x20->flags +
     _TtC8Playback30TransportMappingViewController::globalTemplatesButtonWidthConstaint) = 0;
    pcVar9 = (code *)((long)&unaff_x20->flags +
                     _TtC8Playback30TransportMappingViewController::delegate);
    *(undefined8 *)(pcVar9 + 8) = 0;
    _swift_unknownObjectWeakInit(pcVar9,0);
    pcVar34 = "initWithCoder:";
    auVar98._0_8_ =
         _objc_msgSendSuper2((objc_super *)&stack0x00000000,"initWithCoder:",&DAT_6165627472616568);
    auVar98._8_8_ = pcVar34;
    return auVar98;
  case (char *)0xe8:
  case (char *)0xff:
    goto switchD_1007daeec_caseD_e8;
  case (char *)0xe9:
    (*(code *)unaff_x25)();
    *(class_rw_t **)((long)&unaff_x21->count + (long)&unaff_x24->flags) = unaff_x27;
    _swift_bridgeObjectRetain();
    uVar26 = *(undefined8 *)(unaff_x29 + -0xb8);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar26);
    _swift_bridgeObjectRelease();
    *(code **)(unaff_x29 + -0x60) = thunk_FUN_100242554;
    *(class_rw_t **)(unaff_x29 + -0x58) = unaff_x24;
    *(undefined **)(unaff_x29 + -0x80) = PTR___NSConcreteStackBlock_100a1d8e8;
    *(undefined8 *)(unaff_x29 + -0x78) = 0x42000000;
    *(code **)(unaff_x29 + -0x70) = FUN_100029ac0;
    *(undefined **)(unaff_x29 + -0x68) = &DAT_100a6a400;
    pvVar25 = __Block_copy((void *)(unaff_x29 + -0x80));
    _swift_release(*(undefined8 *)(unaff_x29 + -0x58));
    IVar21 = _objc_msgSend(*(ID *)(unaff_x29 + -0x90),"actionWithTitle:style:handler:",uVar26,0,
                           pvVar25);
    __Block_release(pvVar25);
    _objc_msgSend((ID)unaff_x22,"addAction:",IVar21);
    (**(code **)(*(long *)(unaff_x29 + -0xa8) + 8))
              (*(undefined8 *)(unaff_x29 + -0xa0),*(undefined8 *)(unaff_x29 + -0xb0));
    _objc_msgSend((ID)unaff_x22,"setPreferredAction:");
    pcVar34 = "presentViewController:animated:completion:";
    _objc_msgSend(*(ID *)(unaff_x29 + -0x88),"presentViewController:animated:completion:");
    auVar4._8_8_ = 0;
    auVar4._0_8_ = pcVar34;
    return auVar4 << 0x40;
  case (char *)0xea:
    IVar21 = _objc_msgSend(0x6165627472616568,(SEL)unaff_x23[0x2e].baseProperties);
    IVar23 = _objc_msgSend((ID)unaff_x20,(SEL)unaff_x23[0x2e].baseProperties);
    IVar21 = _objc_msgSend(IVar21,"constraintEqualToAnchor:",IVar23);
    IVar23 = 0;
    *(ID *)(unaff_x19 + 0x30) = IVar21;
    FUN_1007f6f40();
    IVar21 = _objc_msgSend(IVar23,"centerYAnchor");
    IVar23 = _objc_msgSend((ID)unaff_x20,"centerYAnchor");
    IVar21 = _objc_msgSend(IVar21,"constraintEqualToAnchor:",IVar23);
    *(ID *)(unaff_x19 + 0x38) = IVar21;
    puVar22 = &_OBJC_CLASS___NSLayoutConstraint;
    _swift_getInitializedObjCClass();
    uVar26 = 0;
    FUN_100023404(0,&DAT_100af5690,&PTR__OBJC_CLASS___NSLayoutConstraint_100aa3ea8);
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF();
    _swift_bridgeObjectRelease();
    _objc_msgSend((ID)puVar22,"activateConstraints:",unaff_x19);
    IVar21 = 0;
    FUN_1007f6f40();
    puVar47 = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView;
    puVar19 = puVar47;
    FUN_1007f7068(&_TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView);
    _objc_msgSend(IVar21,"addArrangedSubview:",puVar19);
    IVar21 = 0;
    FUN_1007f6f40();
    puVar19 = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView;
    FUN_1007f7068(&_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView);
    _objc_msgSend(IVar21,"addArrangedSubview:",puVar19);
    lVar48 = 0;
    FUN_10078bde8();
    _swift_allocObject();
    *(undefined8 *)(lVar48 + 0x18) = 3;
    *(undefined8 *)(lVar48 + 0x10) = 1;
    FUN_1007f7068();
    IVar21 = _objc_msgSend((ID)puVar47,"heightAnchor");
    IVar21 = _objc_msgSend(IVar21,"constraintEqualToConstant:",0x402e000000000000);
    *(ID *)(lVar48 + 0x20) = IVar21;
    lVar20 = lVar48;
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(lVar48,uVar26);
    _swift_bridgeObjectRelease(lVar48);
    pcVar34 = "activateConstraints:";
    _objc_msgSend((ID)puVar22,"activateConstraints:",lVar20);
    auVar5._8_8_ = 0;
    auVar5._0_8_ = pcVar34;
    return auVar5 << 0x40;
  case (char *)0xeb:
    pTVar14 = &TargetProtocolConformanceDescriptor_100956168;
    puVar22 = &DAT_100a6aa90;
    _swift_getWitnessTable(&TargetProtocolConformanceDescriptor_100956168,&DAT_100a6aa90);
    DAT_100b0e350 = pTVar14;
    auVar93._8_8_ = puVar22;
    auVar93._0_8_ = pTVar14;
    return auVar93;
  }
  auVar70._8_8_ = (ulong)&((class_t *)((long)pcVar34 + -0x28))->superclass | 0x8000000000000000;
  auVar70._0_8_ = pcVar11;
  return auVar70;
switchD_1007daeec_caseD_59:
  *(char **)(unaff_x19 + 0x120) = pcVar34;
  register0x00000008 =
       (BADSPACEBASE *)
       ((long)register0x00000008 +
       -(((class_t *)((long)pcVar34 + 0x28))->vtable + 0xf & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x410) = register0x00000008;
  puVar22 = &DAT_100b0d818;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x400) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x110) = lVar20;
  pcVar34 = *(char **)(lVar20 + 0x40);
switchD_1007daeec_caseD_68:
  pcVar34 = (char *)((long)register0x00000008 + -((ulong)((long)pcVar34 + 0xf) & 0xfffffffffffffff0)
                    );
switchD_1007daeec_caseD_3b:
  *(char **)(unaff_x19 + 0x3e0) = pcVar34;
  puVar22 = &DAT_100b0d820;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x3d8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x108) = lVar20;
  puVar37 = (ushort *)((long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x3d0) = puVar37;
  puVar22 = &DAT_100b0d828;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x3c8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x100) = lVar20;
  pcVar34 = *(char **)(lVar20 + 0x40);
switchD_1007daeec_caseD_7b:
  pcVar34 = (char *)((long)puVar37 - ((ulong)((long)pcVar34 + 0xf) & 0xfffffffffffffff0));
  *(char **)(unaff_x19 + 0x3c0) = pcVar34;
switchD_1007daeec_caseD_4e:
  puVar22 = &DAT_100b0d830;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x3b8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x3b0) = lVar20;
  puVar37 = (ushort *)((long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x3a8) = puVar37;
  puVar22 = &DAT_100b0d838;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x3a0) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x398) = lVar20;
  pcVar34 = (char *)(*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
switchD_1007daeec_caseD_65:
  register0x00000008 = (BADSPACEBASE *)((long)puVar37 - (long)pcVar34);
  *(BADSPACEBASE **)(unaff_x19 + 0x390) = register0x00000008;
switchD_1007daeec_caseD_38:
  puVar22 = &DAT_100b0d840;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x388) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x380) = lVar20;
  lVar20 = (long)register0x00000008 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x378) = lVar20;
  puVar22 = &DAT_100b0d848;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x368) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x360) = lVar48;
  register0x00000008 =
       (BADSPACEBASE *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x350) = register0x00000008;
  pcVar11 = (class_rw_t *)&DAT_100b0d000;
  goto switchD_1007daeec_caseD_31;
switchD_1007daeec_caseD_4b:
  lVar20 = *(long *)(unaff_x19 + 0x70);
  pcVar43 = unaff_x22;
  pcVar11 = unaff_x23;
  goto LAB_1007dcfdc;
switchD_1007daeec_caseD_44:
  unaff_x25 = *(class_rw_t **)(unaff_x19 + 0x1b0);
  unaff_x23 = *(class_rw_t **)(unaff_x19 + 0x440);
  unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x438);
  __ss22KeyedEncodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xts06CodingH0Rd__lF
            (unaff_x25,&DAT_100a69088,unaff_x19 + 0x4e0,unaff_x23,&DAT_100a69088,param_6);
  *unaff_x26 = unaff_x22;
  FUN_100021774(&DAT_100af9d40);
  FUN_100778344(&DAT_100b0b798,PTR___ss5Int32VSEsWP_100a1df30,PTR___sSayxGSEsSERzlMc_100a1dd20);
  pcVar11 = (class_rw_t *)(unaff_x19 + 0x4e0);
  unaff_x22 = *(class_rw_t **)(unaff_x19 + 0x1b8);
switchD_1007daeec_caseD_71:
  __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF(pcVar11);
  pcVar34 = *(char **)(unaff_x19 + 0x40);
  goto LAB_1007dd50c;
switchD_1007daeec_caseD_3f:
  unaff_x24 = *(class_rw_t **)(unaff_x19 + 0x418);
  __ss22KeyedEncodingContainerV6encode_6forKeyySd_xtKF(param_1);
  lVar20 = *(long *)(unaff_x19 + 0x118);
  pcVar43 = unaff_x22;
  pcVar11 = unaff_x23;
LAB_1007dcfdc:
  (**(code **)(lVar20 + 8))(unaff_x25,unaff_x24);
  pcVar34 = *(char **)(*(long *)(unaff_x19 + 0x428) + 8);
  goto LAB_1007dd668;
switchD_1007daeec_caseD_35:
  lVar20 = unaff_x19 + 0x4e0;
  uVar26 = *(undefined8 *)(unaff_x19 + 0x240);
  lVar48 = *(long *)(unaff_x19 + 0x430);
  __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF
            (lVar20,unaff_x19 + 0x450,uVar26,unaff_x20,param_6);
  if (lVar48 == 0) {
    *(char *)(unaff_x19 + 0x4e0) = (char)unaff_x22;
    *(undefined1 *)(unaff_x19 + 0x450) = 1;
    FUN_1007e0e30();
    __ss22KeyedEncodingContainerV6encode_6forKeyyqd___xtKSERd__lF
              (unaff_x19 + 0x4e0,unaff_x19 + 0x450,uVar26,&DAT_100a2d410,lVar20);
  }
  pcVar9 = *(code **)(*(long *)(unaff_x19 + 0x80) + 8);
  pcVar43 = unaff_x24;
  pcVar11 = unaff_x25;
  goto LAB_1007dd650;
switchD_1007daeec_caseD_31:
  pcVar11 = (class_rw_t *)&pcVar11[0x1d].baseProtocols;
  FUN_100021774();
  *(class_rw_t **)(unaff_x19 + 0x370) = pcVar11;
switchD_1007daeec_caseD_5e:
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0xf8) = poVar35;
  lVar48 = (long)register0x00000008 - ((long)poVar35[8] + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x358) = lVar48;
  puVar22 = &DAT_100b0d858;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x348) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xf0) = lVar20;
  lVar48 = lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x340) = lVar48;
  puVar22 = &DAT_100b0d860;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x330) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 800) = lVar20;
  register0x00000008 =
       (BADSPACEBASE *)(lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x310) = register0x00000008;
  pcVar11 = (class_rw_t *)&DAT_100b0d868;
  FUN_100021774();
switchD_1007daeec_caseD_55:
  *(class_rw_t **)(unaff_x19 + 0x338) = pcVar11;
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0xe8) = poVar35;
  pcVar34 = *(char **)(poVar35 + 8);
  puVar37 = (ushort *)register0x00000008;
switchD_1007daeec_caseD_82:
  puVar37 = (ushort *)((long)puVar37 - ((ulong)((long)pcVar34 + 0xf) & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x318) = puVar37;
  puVar22 = &DAT_100b0d870;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x328) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xe0) = lVar20;
  pcVar34 = (char *)(*(long *)(lVar20 + 0x40) + 0xf);
switchD_1007daeec_caseD_39:
  puVar37 = (ushort *)((long)puVar37 - ((ulong)pcVar34 & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x300) = puVar37;
  puVar22 = &DAT_100b0d878;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2f8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xd0) = lVar20;
  pcVar34 = (char *)(*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
switchD_1007daeec_caseD_66:
  puVar37 = (ushort *)((long)puVar37 - (long)pcVar34);
  *(ushort **)(unaff_x19 + 0x2e8) = puVar37;
  puVar22 = &DAT_100b0d880;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x308) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xd8) = lVar20;
  pcVar34 = (char *)(*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
switchD_1007daeec_caseD_36:
  *(long *)(unaff_x19 + 0x2f0) = (long)puVar37 - (long)pcVar34;
  puVar22 = &DAT_100b0d888;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2d8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 200) = lVar20;
  pcVar34 = (char *)(((long)puVar37 - (long)pcVar34) -
                    (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(char **)(unaff_x19 + 0x2c0) = pcVar34;
switchD_1007daeec_caseD_63:
  puVar22 = &DAT_100b0d890;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2e0) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xc0) = lVar20;
  lVar20 = (long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x2c8) = lVar20;
  puVar22 = &DAT_100b0d898;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2d0) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xb8) = lVar48;
  pcVar34 = (char *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(char **)(unaff_x19 + 0x2b8) = pcVar34;
switchD_1007daeec_caseD_46:
  puVar22 = &DAT_100b0d8a0;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2b0) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0xb0) = lVar20;
  lVar20 = (long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x2a8) = lVar20;
  puVar22 = &DAT_100b0d8a8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x298) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x288) = lVar48;
  register0x00000008 =
       (BADSPACEBASE *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x278) = register0x00000008;
  puVar22 = &DAT_100b0d8b0;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x2a0) = puVar22;
  pcVar34 = *(char **)(puVar22 + -8);
switchD_1007daeec_caseD_45:
  *(char **)(unaff_x19 + 0xa8) = pcVar34;
  register0x00000008 =
       (BADSPACEBASE *)
       ((long)register0x00000008 +
       -(((class_t *)((long)pcVar34 + 0x28))->vtable + 0xf & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x280) = register0x00000008;
  puVar22 = &DAT_100b0d8b8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x270) = puVar22;
  pcVar34 = *(char **)(puVar22 + -8);
  *(char **)(unaff_x19 + 0x98) = pcVar34;
switchD_1007daeec_caseD_73:
  lVar20 = (long)register0x00000008 -
           (((class_t *)((long)pcVar34 + 0x28))->vtable + 0xf & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x250) = lVar20;
  puVar22 = &DAT_100b0d8c0;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 600) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x88) = lVar48;
  register0x00000008 =
       (BADSPACEBASE *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x238) = register0x00000008;
  puVar22 = &DAT_100b0d8c8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x290) = puVar22;
  pcVar34 = *(char **)(puVar22 + -8);
  *(char **)(unaff_x19 + 0xa0) = pcVar34;
switchD_1007daeec_caseD_2f:
  register0x00000008 =
       (BADSPACEBASE *)
       ((long)register0x00000008 +
       -(((class_t *)((long)pcVar34 + 0x28))->vtable + 0xf & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x260) = register0x00000008;
  pcVar11 = (class_rw_t *)&DAT_100b0d8d0;
  FUN_100021774();
switchD_1007daeec_caseD_72:
  *(class_rw_t **)(unaff_x19 + 0x268) = pcVar11;
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0x90) = poVar35;
  lVar20 = (long)register0x00000008 - ((long)poVar35[8] + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x248) = lVar20;
  puVar22 = &DAT_100b0d8d8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x240) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x80) = lVar48;
  pcVar34 = (char *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
switchD_1007daeec_caseD_3c:
  register0x00000008 = (BADSPACEBASE *)pcVar34;
  *(BADSPACEBASE **)(unaff_x19 + 0x230) = register0x00000008;
  puVar22 = &DAT_100b0d8e0;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x228) = puVar22;
  pcVar34 = *(char **)(puVar22 + -8);
switchD_1007daeec_caseD_5c:
  *(char **)(unaff_x19 + 0x78) = pcVar34;
  lVar20 = (long)register0x00000008 -
           (((class_t *)((long)pcVar34 + 0x28))->vtable + 0xf & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x220) = lVar20;
  puVar22 = &DAT_100b0d8e8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x218) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x70) = lVar48;
  pcVar34 = (char *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(char **)(unaff_x19 + 0x210) = pcVar34;
switchD_1007daeec_caseD_30:
  puVar22 = &DAT_100b0d8f0;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x208) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x68) = lVar20;
  lVar20 = (long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x200) = lVar20;
  puVar22 = &DAT_100b0d8f8;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x1f8) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x60) = lVar48;
  pcVar34 = (char *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(char **)(unaff_x19 + 0x1e8) = pcVar34;
switchD_1007daeec_caseD_5d:
  puVar22 = &DAT_100b0d900;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x1d8) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x48) = lVar20;
  register0x00000008 =
       (BADSPACEBASE *)((long)pcVar34 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x1c0) = register0x00000008;
switchD_1007daeec_caseD_34:
  puVar22 = &DAT_100b0d908;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x1e0) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x50) = lVar20;
  lVar48 = (long)register0x00000008 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x1c8) = lVar48;
  puVar22 = &DAT_100b0d910;
  FUN_100021774();
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x40) = lVar20;
  lVar48 = lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x1b0) = lVar48;
  *(undefined **)(unaff_x19 + 0x1b8) = puVar22;
  puVar22 = &DAT_100b0d918;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x1f0) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x58) = lVar20;
  register0x00000008 =
       (BADSPACEBASE *)(lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x1d0) = register0x00000008;
  pcVar11 = (class_rw_t *)&DAT_100b0d920;
  FUN_100021774();
switchD_1007daeec_caseD_2e:
  *(class_rw_t **)(unaff_x19 + 0x1a0) = pcVar11;
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0x30) = poVar35;
  lVar20 = (long)register0x00000008 - ((long)poVar35[8] + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 400) = lVar20;
  puVar22 = &DAT_100b0d928;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x1a8) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x38) = lVar48;
  puVar37 = (ushort *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x198) = puVar37;
  pcVar11 = (class_rw_t *)&DAT_100b0d930;
  FUN_100021774();
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0x20) = poVar35;
  pcVar34 = *(char **)(poVar35 + 8);
switchD_1007daeec_caseD_61:
  lVar48 = (long)puVar37 - ((ulong)((long)pcVar34 + 0xf) & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x170) = lVar48;
  *(class_rw_t **)(unaff_x19 + 0x178) = pcVar11;
  puVar22 = &DAT_100b0d938;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x150) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x138) = lVar20;
  lVar48 = lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x130) = lVar48;
  puVar22 = &DAT_100b0d940;
  FUN_100021774();
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x18) = lVar20;
  register0x00000008 =
       (BADSPACEBASE *)(lVar48 - (*(long *)(lVar20 + 0x40) + 0xfU & 0xfffffffffffffff0));
  *(BADSPACEBASE **)(unaff_x19 + 0x160) = register0x00000008;
  *(undefined **)(unaff_x19 + 0x168) = puVar22;
  pcVar11 = (class_rw_t *)&DAT_100b0d948;
  FUN_100021774();
switchD_1007daeec_caseD_4c:
  poVar35 = pcVar11[-1].baseProperties;
  *(objc_property_list **)(unaff_x19 + 0x28) = poVar35;
  lVar20 = (long)register0x00000008 - ((long)poVar35[8] + 0xfU & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x180) = lVar20;
  *(class_rw_t **)(unaff_x19 + 0x188) = pcVar11;
  puVar22 = &DAT_100b0d950;
  FUN_100021774();
  register0x00000008 =
       (BADSPACEBASE *)
       (lVar20 - (*(long *)(*(long *)(puVar22 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0));
  puVar22 = &DAT_100b0d958;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x148) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 8) = lVar20;
  pcVar34 = *(char **)(lVar20 + 0x40);
switchD_1007daeec_caseD_3e:
  puVar37 = (ushort *)
            ((long)register0x00000008 + -((ulong)((long)pcVar34 + 0xf) & 0xfffffffffffffff0));
  *(ushort **)(unaff_x19 + 0x128) = puVar37;
  puVar22 = &DAT_100b0d960;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x158) = puVar22;
  lVar20 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x10) = lVar20;
  pcVar34 = (char *)(*(long *)(lVar20 + 0x40) + 0xf);
switchD_1007daeec_caseD_79:
  lVar20 = (long)puVar37 - ((ulong)pcVar34 & 0xfffffffffffffff0);
  *(long *)(unaff_x19 + 0x140) = lVar20;
  puVar22 = &DAT_100b0d968;
  FUN_100021774();
  *(undefined **)(unaff_x19 + 0x440) = puVar22;
  lVar48 = *(long *)(puVar22 + -8);
  *(long *)(unaff_x19 + 0x428) = lVar48;
  pcVar34 = (char *)(lVar20 - (*(long *)(lVar48 + 0x40) + 0xfU & 0xfffffffffffffff0));
  unaff_x22 = (class_rw_t *)unaff_x20->name;
  unaff_x23 = (class_rw_t *)unaff_x20->baseMethods;
  FUN_100023444();
  FUN_1007e0630();
  pcVar11 = (class_rw_t *)&DAT_100a68ac8;
  *(char **)(unaff_x19 + 0x438) = pcVar34;
  unaff_x26 = (undefined8 *)(unaff_x19 + 0x4e0);
  param_4 = unaff_x20;
  goto switchD_1007daeec_caseD_6b;
switchD_1007daeec_caseD_cb:
  auVar100._8_8_ = op;
  auVar100._0_8_ = pcVar11;
  return auVar100;
switchD_1007daeec_caseD_99:
  op = (char *)((ulong)pcVar34 | 0x8000000000000000);
  pcVar34._0_4_ = 0x11;
  pcVar34._4_4_ = 0xd0000000;
switchD_1007daeec_caseD_95:
  auVar54._0_8_ = (ulong)pcVar34 | 2;
  auVar54._8_8_ = op;
  return auVar54;
switchD_1007daeec_caseD_6b:
  __ss7EncoderP9container7keyedBys22KeyedEncodingContainerVyqd__Gqd__m_ts9CodingKeyRd__lFTj
            (pcVar34,pcVar11,pcVar11,param_4,unaff_x22,unaff_x23);
  uVar33 = unaff_x28[0xd];
  uVar26 = unaff_x28[0xc];
  uVar50 = unaff_x28[0xf];
  uVar31 = unaff_x28[0xe];
  uVar53 = unaff_x28[9];
  uVar52 = unaff_x28[8];
  uVar51 = unaff_x28[10];
  unaff_x26[0x1d] = unaff_x28[0xb];
  unaff_x26[0x1c] = uVar51;
  unaff_x26[0x1f] = uVar33;
  unaff_x26[0x1e] = uVar26;
  unaff_x26[0x21] = uVar50;
  unaff_x26[0x20] = uVar31;
  uVar26 = *(undefined8 *)((long)unaff_x28 + 0x7a);
  *(undefined8 *)(unaff_x29 + -0x6e) = *(undefined8 *)((long)unaff_x28 + 0x82);
  *(undefined8 *)(unaff_x29 + -0x76) = uVar26;
  uVar26 = unaff_x28[4];
  uVar31 = unaff_x28[7];
  uVar33 = unaff_x28[6];
  *(undefined8 *)(unaff_x29 + -200) = unaff_x28[5];
  *(undefined8 *)(unaff_x29 + -0xd0) = uVar26;
  *(undefined8 *)(unaff_x29 + -0xb8) = uVar31;
  *(undefined8 *)(unaff_x29 + -0xc0) = uVar33;
  *(undefined8 *)(unaff_x29 + -0xa8) = uVar53;
  *(undefined8 *)(unaff_x29 + -0xb0) = uVar52;
  uVar31 = *unaff_x28;
  uVar33 = unaff_x28[3];
  uVar26 = unaff_x28[2];
  *(undefined8 *)(unaff_x29 + -0xe8) = unaff_x28[1];
  *(undefined8 *)(unaff_x29 + -0xf0) = uVar31;
  *(undefined8 *)(unaff_x29 + -0xd8) = uVar33;
  *(undefined8 *)(unaff_x29 + -0xe0) = uVar26;
  op = (char *)pcVar11;
switchD_1007daeec_caseD_56:
  uVar36 = unaff_x29 - 0xf0;
  FUN_10066e788();
                    /* WARNING: Could not recover jumptable at 0x0001007dbd30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&UNK_1007dbd34 + (ulong)(&USHORT_100952afa)[uVar36 & 0xffffffff] * 4))();
  auVar78._8_8_ = op;
  auVar78._0_8_ = uVar36;
  return auVar78;
switchD_1007daeec_caseD_8c:
  oVar39 = (objc_property_list)(in_x12 & 0xffffffffffff | 0xec00000000000000);
  puVar8 = (ushort *)0x6169766572626261;
  if (!(bool)in_ZR) {
    oVar39.entsize = 0;
    oVar39.count = 0xe7000000;
    puVar8 = (ushort *)0x676e6974756f72;
  }
  if (iVar40 != 2) {
    oVar13 = oVar39;
    puVar38 = puVar8;
  }
  if (iVar40 != 0) {
    pcVar34 = &DAT_e500000000000000;
    puVar37 = (ushort *)0x726564726f;
  }
  if (iVar40 < 2) {
    oVar13 = (objc_property_list)pcVar34;
    puVar38 = puVar37;
  }
  __sSS4hash4intoys6HasherVz_tF(&stack0x00000008,puVar38,oVar13);
  _swift_bridgeObjectRelease(oVar13);
  __ss6HasherV9_finalizeSiyF();
  auVar82._8_8_ = puVar38;
  auVar82._0_4_ = oVar13.entsize;
  auVar82._4_4_ = oVar13.count;
  return auVar82;
switchD_1007daeec_caseD_87:
  auVar87._8_8_ = &DAT_e900000000000074;
  auVar87._0_8_ = &DAT_6165627472616568;
  return auVar87;
switchD_1007daeec_caseD_8f:
  auVar92._8_8_ = &DAT_e900000000000074;
  auVar92._0_8_ = &DAT_6165627472616568;
  return auVar92;
switchD_1007daeec_caseD_ba:
  _swift_release(pcVar11);
  auVar101._8_8_ = op;
  auVar101._0_8_ = pcVar11;
  return auVar101;
}

// ==== 1007f6c90 FUN_1007f6c90 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8
FUN_1007f6c90(double param_1,undefined8 param_2,double param_3,double param_4,ulong param_5)

{
  double *pdVar1;
  long lVar2;
  undefined8 *self;
  undefined8 *puVar3;
  ID IVar4;
  ID self_00;
  undefined8 uVar5;
  long unaff_x20;
  double dVar6;
  double dVar7;
  
  lVar2 = _TtC8Playback16MixerVUMeterView::currentLevel;
  if (param_1 <= 0.0) {
    dVar6 = 0.0;
  }
  else {
    dVar6 = 1.0;
    if (param_1 <= 1.0) {
      dVar6 = param_1;
    }
  }
  if ((param_5 & 1) == 0) {
    param_3 = *(double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::currentLevel);
    param_4 = *(double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::maxDecayDelta);
    if (param_3 - param_1 <= param_4) {
      dVar7 = param_1 - param_3;
      param_4 = *(double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::maxAscentDelta);
      param_1 = param_3 + param_4;
      if (param_4 < dVar7) {
        dVar6 = param_1;
      }
    }
    else {
      dVar6 = param_3 - param_4;
    }
  }
  *(double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::currentLevel) = dVar6;
  puVar3 = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView;
  self = puVar3;
  FUN_1007f7068();
  _objc_msgSend((ID)self,"frame");
  _CGRectGetHeight(param_1,dVar6,0);
  dVar6 = *(double *)(unaff_x20 + lVar2);
  dVar7 = param_1 * dVar6;
  FUN_1007f7068();
  _objc_msgSend((ID)puVar3,"frame");
  IVar4 = 0;
  _CGRectGetHeight(param_1,dVar6);
  dVar6 = param_1 - dVar7;
  FUN_1007f7228();
  pdVar1 = (double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterFrame);
  *pdVar1 = param_1;
  pdVar1[1] = dVar6;
  pdVar1[2] = param_3;
  pdVar1[3] = param_4;
  *(undefined1 *)(pdVar1 + 4) = 0;
  FUN_1007f7134();
  IVar4 = _objc_msgSend(IVar4,"superlayer");
  self_00 = 0;
  if (*(double *)(unaff_x20 + lVar2) <= 0.0) {
    if (IVar4 == 0) {
      return 0;
    }
    FUN_1007f7134();
    _objc_msgSend(self_00,"removeFromSuperlayer");
  }
  else {
    pdVar1[3] = dVar7;
    *(undefined1 *)(pdVar1 + 4) = 0;
    FUN_1007f7134();
    _objc_msgSend(self_00,"setFrame:",*pdVar1,pdVar1[1],pdVar1[2],pdVar1[3]);
    if (IVar4 != 0) {
      return 0;
    }
    puVar3 = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView;
    FUN_1007f7068();
    IVar4 = _objc_msgSend((ID)puVar3,"layer");
    uVar5 = 0;
    FUN_1007f7134(0);
    _objc_msgSend(IVar4,"addSublayer:",uVar5);
  }
  return 0;
}

// ==== 1007f6f40 FUN_1007f6f40 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1007f6f40(void)

{
  undefined *puVar1;
  long lVar2;
  ID self;
  undefined *self_00;
  undefined *puVar3;
  long unaff_x20;
  
  lVar2 = _TtC8Playback16MixerVUMeterView::___lazy_storage___mainStackView;
  self = *(ID *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___mainStackView);
  if (self == 0) {
    self_00 = &_OBJC_CLASS___UIStackView;
    _objc_allocWithZone();
    FUN_100023404(0,&DAT_100af5698,&PTR__OBJC_CLASS___UIView_100aa3dd8);
    puVar1 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF();
    _swift_release(puVar1);
    self = _objc_msgSend((ID)self_00,"initWithArrangedSubviews:",puVar3);
    _objc_msgSend(self,"setTranslatesAutoresizingMaskIntoConstraints:",0);
    _objc_msgSend(self,"setAxis:",1);
    _objc_msgSend(self,"setDistribution:",0);
    _objc_msgSend(self,"setSpacing:",0x4010000000000000);
    *(ID *)(unaff_x20 + lVar2) = self;
  }
  return self;
}

// ==== 1007f7134 FUN_1007f7134 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1007f7134(void)

{
  long lVar1;
  ID self;
  undefined *self_00;
  ID IVar2;
  long unaff_x20;
  
  lVar1 = _TtC8Playback16MixerVUMeterView::___lazy_storage___levelLayer;
  self = *(ID *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___levelLayer);
  if (self == 0) {
    self_00 = &_OBJC_CLASS___CALayer;
    _objc_allocWithZone();
    self = _objc_msgSend((ID)self_00,"init");
    if (DAT_100adffa8 != -1) {
      _swift_once(&DAT_100adffa8,FUN_1007f6ef4);
    }
    IVar2 = _objc_msgSend(DAT_100b0e558,"CGColor");
    _objc_msgSend(self,"setBackgroundColor:",IVar2);
    FUN_1007f7228(0);
    _objc_msgSend(self,"setFrame:");
    *(ID *)(unaff_x20 + lVar1) = self;
  }
  return self;
}

// ==== 1007f7228 FUN_1007f7228 ====
double FUN_1007f7228(double param_1,undefined8 param_2,double param_3,double param_4)

{
  double *pdVar1;
  ID unaff_x20;
  
  pdVar1 = (double *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterFrame);
  if (((ulong)pdVar1[4] & 1) == 0) {
    param_1 = *pdVar1;
  }
  else {
    _objc_msgSend(unaff_x20,"bounds");
    param_1 = param_1 + 1.0;
    _objc_msgSend(unaff_x20,"bounds");
    _objc_msgSend(unaff_x20,"frame");
    *pdVar1 = param_1;
    pdVar1[1] = param_4;
    pdVar1[2] = param_3 + -2.0;
    pdVar1[3] = 0.0;
    *(undefined1 *)(pdVar1 + 4) = 0;
  }
  return param_1;
}

// ==== 1007f72cc FUN_1007f72cc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_1007f72cc(void)

{
  undefined *puVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  long lVar7;
  undefined8 *self;
  long lVar8;
  ID unaff_x20;
  
  puVar1 = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar2 = _objc_msgSend((ID)puVar1,"clearColor");
  _objc_msgSend(unaff_x20,"setBackgroundColor:",IVar2);
  IVar2 = _objc_msgSend(unaff_x20,"setOpaque:",0);
  FUN_1007f6f40();
  _objc_msgSend(unaff_x20,"addSubview:",IVar2);
  IVar3 = 0;
  FUN_10078bde8();
  _swift_allocObject();
  *(undefined8 *)(IVar3 + 0x18) = 9;
  *(undefined8 *)(IVar3 + 0x10) = 4;
  IVar2 = IVar3;
  FUN_1007f6f40();
  IVar2 = _objc_msgSend(IVar2,"leadingAnchor");
  IVar4 = _objc_msgSend(unaff_x20,"leadingAnchor");
  IVar2 = _objc_msgSend(IVar2,"constraintEqualToAnchor:constant:",0,IVar4);
  IVar4 = 0;
  *(ID *)(IVar3 + 0x20) = IVar2;
  FUN_1007f6f40();
  IVar2 = _objc_msgSend(IVar4,"topAnchor");
  IVar4 = _objc_msgSend(unaff_x20,"topAnchor");
  IVar2 = _objc_msgSend(IVar2,"constraintEqualToAnchor:constant:",0,IVar4);
  IVar4 = 0;
  *(ID *)(IVar3 + 0x28) = IVar2;
  FUN_1007f6f40();
  IVar2 = _objc_msgSend(IVar4,"centerXAnchor");
  IVar4 = _objc_msgSend(unaff_x20,"centerXAnchor");
  IVar2 = _objc_msgSend(IVar2,"constraintEqualToAnchor:",IVar4);
  IVar4 = 0;
  *(ID *)(IVar3 + 0x30) = IVar2;
  FUN_1007f6f40();
  IVar2 = _objc_msgSend(IVar4,"centerYAnchor");
  IVar4 = _objc_msgSend(unaff_x20,"centerYAnchor");
  IVar2 = _objc_msgSend(IVar2,"constraintEqualToAnchor:",IVar4);
  *(ID *)(IVar3 + 0x38) = IVar2;
  puVar1 = &_OBJC_CLASS___NSLayoutConstraint;
  _swift_getInitializedObjCClass();
  uVar5 = 0;
  FUN_100023404(0,&DAT_100af5690,&PTR__OBJC_CLASS___NSLayoutConstraint_100aa3ea8);
  IVar2 = IVar3;
  __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(IVar3,uVar5);
  _swift_bridgeObjectRelease(IVar3);
  _objc_msgSend((ID)puVar1,"activateConstraints:",IVar2);
  IVar2 = 0;
  FUN_1007f6f40();
  self = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView;
  puVar6 = self;
  FUN_1007f7068(&_TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView);
  _objc_msgSend(IVar2,"addArrangedSubview:",puVar6);
  IVar2 = 0;
  FUN_1007f6f40();
  puVar6 = &_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView;
  FUN_1007f7068(&_TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView);
  _objc_msgSend(IVar2,"addArrangedSubview:",puVar6);
  lVar7 = 0;
  FUN_10078bde8();
  _swift_allocObject();
  *(undefined8 *)(lVar7 + 0x18) = 3;
  *(undefined8 *)(lVar7 + 0x10) = 1;
  FUN_1007f7068();
  IVar2 = _objc_msgSend((ID)self,"heightAnchor");
  IVar2 = _objc_msgSend(IVar2,"constraintEqualToConstant:",0x402e000000000000);
  *(ID *)(lVar7 + 0x20) = IVar2;
  lVar8 = lVar7;
  __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(lVar7,uVar5);
  _swift_bridgeObjectRelease(lVar7);
  _objc_msgSend((ID)puVar1,"activateConstraints:",lVar8);
  return 0;
}

// ==== 1007f7700 _TtC8Playback16MixerVUMeterView::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback16MixerVUMeterView::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  FUN_1007f77e0();
  return param_3;
}

// ==== 1007f773c _TtC8Playback16MixerVUMeterView::initWithFrame: ====
/* Function Stack Size: 0x30 bytes */

ID _TtC8Playback16MixerVUMeterView::initWithFrame_(ID param_1,SEL param_2,CGRect param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.MixerVUMeterView",0x19,"init(frame:)",0xc,0,param_3.field1_0x10.field1_0x8);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1007f7768);
  (*pcVar1)();
}

// ==== 1007f7768 _TtC8Playback16MixerVUMeterView::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback16MixerVUMeterView::_cxx_destruct(ID param_1,SEL param_2)

{
  return;
}

// ==== 1007f77c0 FUN_1007f77c0 ====
void FUN_1007f77c0(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback16MixerVUMeterView);
  return;
}

// ==== 1007f77e0 FUN_1007f77e0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1007f77e0(undefined8 param_1)

{
  undefined8 *puVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::currentLevel) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::maxAscentDelta) = 0x7fefffffffffffff;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::maxDecayDelta) = 0x7fefffffffffffff;
  *(undefined1 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::configured) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___mainStackView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterOverloadView)
       = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterBodyView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___levelLayer) = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback16MixerVUMeterView::___lazy_storage___meterFrame)
  ;
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  *(undefined1 *)(puVar1 + 4) = 1;
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffd0,"initWithCoder:",param_1);
  if (IVar2 != 0) {
    FUN_1007f72cc(IVar2);
  }
  return IVar2;
}

