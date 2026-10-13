// Playback main executable sha256 2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423
// Ghidra 12.1.4 decompiler output, feature "transition": functions whose pseudocode matches /Transition(?!Layout|Coordinator|Context|Style|Duration)|transitionBeats|storedTransition|cueNextSong|stayInSong|ContinuePad|continuePad/
// Addresses are image-relative VM addresses as exported (e.g. 100545a98).

// ==== 10002a3f0 FUN_10002a3f0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_10002a3f0(undefined8 param_1,ID param_2,ulong param_3)

{
  ID IVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  if ((param_2 == 0) || (IVar1 = _objc_msgSend(param_2,"cue"), IVar1 == 0)) {
    return 0;
  }
  _objc_msgSend(param_2,"storedValue");
  uVar4 = param_1;
  IVar1 = _objc_msgSend(IVar1,"transitionBeats");
  if ((param_3 & 1) == 0) {
    if ((int)IVar1 == 0) {
      FUN_100029630(param_1);
      return 0;
    }
  }
  else if ((int)IVar1 == 0) {
    uVar2 = 2;
    uVar3 = 0;
    goto LAB_10002a48c;
  }
  uVar2 = 0;
  uVar3 = 1;
LAB_10002a48c:
  FUN_1008223d4(uVar2,uVar3);
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  if (*(long *)(DAT_100b75e40 + 0x18) == 0) {
    return 0;
  }
  uVar2 = *(undefined8 *)(*(long *)(DAT_100b75e40 + 0x18) + 0x30);
  _swift_retain(uVar2);
  FUN_100032fb8(param_1,0,2,uVar4,0);
  _swift_release(uVar2);
  return uVar2;
}

// ==== 100040f1c FUN_100040f1c ====
long FUN_100040f1c(void)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long unaff_x20;
  undefined8 uVar4;
  
  lVar1 = _TtC8Playback28TransitionMenuViewController::___lazy_storage___transitions;
  lVar2 = *(long *)(unaff_x20 +
                   _TtC8Playback28TransitionMenuViewController::___lazy_storage___transitions);
  lVar3 = lVar2;
  if (lVar2 == 0) {
    lVar3 = unaff_x20;
    FUN_100040f80();
    uVar4 = *(undefined8 *)(unaff_x20 + lVar1);
    *(long *)(unaff_x20 + lVar1) = lVar3;
    _swift_bridgeObjectRetain();
    _swift_bridgeObjectRelease(uVar4);
    lVar2 = 0;
  }
  _swift_bridgeObjectRetain(lVar2);
  return lVar3;
}

// ==== 100040f80 FUN_100040f80 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined * FUN_100040f80(long param_1)

{
  char cVar1;
  undefined1 uVar2;
  code *pcVar3;
  uint uVar4;
  undefined *puVar6;
  ulong uVar7;
  undefined *puVar8;
  char *pcVar9;
  undefined *puVar10;
  char *pcVar11;
  ulong uVar12;
  ID self;
  long lVar13;
  undefined *puVar14;
  ulong uVar15;
  undefined *puVar16;
  ulong uVar17;
  ID IVar5;
  
  if ((*(long *)(param_1 + _TtC8Playback28TransitionMenuViewController::setlist) != 0) &&
     (self = *(ID *)(param_1 + _TtC8Playback28TransitionMenuViewController::song), self != 0)) {
    IVar5 = _objc_msgSend(self,"contentTypeID");
    uVar4 = (uint)IVar5;
    FUN_100419df0();
    if ((uVar4 - 1 & 0xff) < 0x19) {
      if (DAT_100adfbd8 != -1) {
        _swift_once(&DAT_100adfbd8,FUN_1005fd17c);
      }
      puVar8 = DAT_100b77558;
      if ((uVar4 & 0xff) == 0x16 || (uVar4 & 0xff) == 0xd) {
        puVar16 = *(undefined **)(DAT_100b77558 + 0x10);
        if (puVar16 != (undefined *)0x0) {
          puVar14 = (undefined *)0x0;
LAB_100041024:
          if ((DAT_100b77558 + (long)puVar14)[0x20] != '\x04') goto code_r0x000100041034;
          if (SCARRY8((long)puVar14,1)) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100041580);
            (*pcVar3)();
          }
          _swift_bridgeObjectRetain(DAT_100b77558);
          if (puVar14 + 1 != puVar16) {
            puVar6 = puVar14 + 0x21;
            puVar16 = puVar8;
            _swift_isUniquelyReferenced_nonNull_native();
            if (((ulong)puVar16 & 1) == 0) {
              FUN_100793504();
            }
            do {
              puVar16 = *(undefined **)(puVar8 + 0x10);
              if (puVar16 <= puVar6 + -0x20) {
                    /* WARNING: Does not return */
                pcVar3 = (code *)SoftwareBreakpoint(1,0x100041484);
                (*pcVar3)();
              }
              if (puVar8[(long)puVar6] != '\x04') {
                if (puVar6 + -0x20 != puVar14) {
                  if (puVar16 <= puVar14) {
                    /* WARNING: Does not return */
                    pcVar3 = (code *)SoftwareBreakpoint(1,0x100041264);
                    (*pcVar3)();
                  }
                  uVar2 = (puVar8 + 0x20)[(long)puVar14];
                  (puVar8 + 0x20)[(long)puVar14] = puVar8[(long)puVar6];
                  puVar8[(long)puVar6] = uVar2;
                  puVar16 = *(undefined **)(puVar8 + 0x10);
                }
                puVar14 = puVar14 + 1;
              }
              puVar10 = puVar6 + -0x1f;
              puVar6 = puVar6 + 1;
            } while (puVar10 != puVar16);
          }
          if ((long)puVar16 < (long)puVar14) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x1000414ec);
            (*pcVar3)();
          }
          if ((long)puVar14 < 0) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x1000414f0);
            (*pcVar3)();
          }
          goto LAB_1000410bc;
        }
LAB_100041040:
        _swift_bridgeObjectRetain(DAT_100b77558);
        puVar14 = puVar16;
LAB_1000410bc:
        if (SCARRY8((long)puVar16,(long)puVar14 - (long)puVar16)) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x1000414f4);
          (*pcVar3)();
        }
        puVar6 = puVar8;
        _swift_isUniquelyReferenced_nonNull_native();
        if (((int)puVar6 == 0) ||
           ((long)(*(ulong *)(puVar8 + 0x18) >> 1) <
            (long)(puVar16 + ((long)puVar14 - (long)puVar16)))) {
          FUN_10078f72c();
          puVar8 = puVar6;
        }
        thunk_FUN_1001d7aec(puVar14,puVar16,0);
      }
      else {
        puVar14 = DAT_100b77558;
        _swift_bridgeObjectRetain();
      }
      FUN_1004a6154();
      if ((ulong)puVar14 >> 0x3e == 0) {
        puVar16 = *(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10);
      }
      else {
        puVar16 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
        if ((long)puVar14 < 0) {
          puVar16 = puVar14;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      if (puVar16 == (undefined *)0x0) {
        _swift_bridgeObjectRelease(puVar14);
        return puVar8;
      }
      puVar6 = puVar16 + -1;
      if (SBORROW8((long)puVar16,1)) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x1000414f8);
        (*pcVar3)();
      }
      if (((ulong)puVar14 & 0xc000000000000001) == 0) {
        if ((long)puVar6 < 0) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100041508);
          (*pcVar3)();
        }
        if (*(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10) <= puVar6) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x10004150c);
          (*pcVar3)();
        }
        puVar6 = *(undefined **)(puVar14 + (long)puVar6 * 8 + 0x20);
      }
      else {
        FUN_1000cbedc(puVar6,puVar14);
      }
      _swift_bridgeObjectRelease(puVar14);
      FUN_10034293c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(puVar6,self);
      if (((ulong)puVar6 & 1) == 0) {
        return puVar8;
      }
      uVar17 = *(ulong *)(puVar8 + 0x10);
      if (uVar17 != 0) {
        uVar15 = 0;
LAB_1000411c8:
        if ((puVar8[uVar15 + 0x20] | 4) == 4) goto code_r0x0001000411dc;
        if (SCARRY8(uVar15,1)) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100041598);
          (*pcVar3)();
        }
        if (uVar15 + 1 != uVar17) {
          lVar13 = uVar15 + 0x21;
          puVar14 = puVar8;
          _swift_isUniquelyReferenced_nonNull_native();
          if (((ulong)puVar14 & 1) == 0) {
            FUN_100793504();
          }
          do {
            uVar17 = *(ulong *)(puVar8 + 0x10);
            if (uVar17 <= lVar13 - 0x20U) {
                    /* WARNING: Does not return */
              pcVar3 = (code *)SoftwareBreakpoint(1,0x100041490);
              (*pcVar3)();
            }
            if ((puVar8[lVar13] | 4) == 4) {
              if (lVar13 - 0x20U != uVar15) {
                if (uVar17 <= uVar15) {
                    /* WARNING: Does not return */
                  pcVar3 = (code *)SoftwareBreakpoint(1,0x100041480);
                  (*pcVar3)();
                }
                uVar2 = puVar8[uVar15 + 0x20];
                puVar8[uVar15 + 0x20] = puVar8[lVar13];
                puVar8[lVar13] = uVar2;
                uVar17 = *(ulong *)(puVar8 + 0x10);
              }
              uVar15 = uVar15 + 1;
            }
            uVar7 = lVar13 - 0x1f;
            lVar13 = lVar13 + 1;
          } while (uVar7 != uVar17);
        }
        if ((long)uVar17 < (long)uVar15) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100041514);
          (*pcVar3)();
        }
        uVar7 = uVar15;
        if ((long)uVar15 < 0) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100041518);
          (*pcVar3)();
        }
        goto LAB_100041280;
      }
      uVar7 = 0;
LAB_100041280:
      if (SCARRY8(uVar17,uVar7 - uVar17)) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x10004151c);
        (*pcVar3)();
      }
      puVar14 = puVar8;
      _swift_isUniquelyReferenced_nonNull_native();
      if (((int)puVar14 == 0) ||
         ((long)(*(ulong *)(puVar8 + 0x18) >> 1) < (long)(uVar17 + (uVar7 - uVar17)))) {
        FUN_10078f72c();
        puVar8 = puVar14;
      }
      thunk_FUN_1001d7aec(uVar7,uVar17,0);
      uVar17 = *(ulong *)(puVar8 + 0x10);
      if (uVar17 == 0) {
        uVar15 = 0;
      }
      else {
        pcVar9 = puVar8 + 0x20;
        if (*pcVar9 == '\0') {
          uVar7 = 0;
LAB_100041308:
          uVar15 = uVar7 + 1;
          if (SCARRY8(uVar7,1)) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100041594);
            (*pcVar3)();
          }
          if (uVar15 != uVar17) {
            pcVar11 = puVar8 + uVar7 + 0x21;
            uVar12 = uVar15;
            do {
              if ((long)uVar15 < 0) {
                    /* WARNING: Does not return */
                pcVar3 = (code *)SoftwareBreakpoint(1,0x100041488);
                (*pcVar3)();
              }
              if (uVar17 <= uVar12) {
                    /* WARNING: Does not return */
                pcVar3 = (code *)SoftwareBreakpoint(1,0x10004148c);
                (*pcVar3)();
              }
              if (*pcVar11 != '\0') {
                if (uVar12 != uVar7) {
                  if (uVar17 <= uVar7) {
                    /* WARNING: Does not return */
                    pcVar3 = (code *)SoftwareBreakpoint(1,0x100041510);
                    (*pcVar3)();
                  }
                  cVar1 = pcVar9[uVar7];
                  pcVar9[uVar7] = *pcVar11;
                  *pcVar11 = cVar1;
                  uVar17 = *(ulong *)(puVar8 + 0x10);
                }
                uVar7 = uVar7 + 1;
              }
              uVar12 = uVar12 + 1;
              pcVar11 = pcVar11 + 1;
            } while (uVar12 != uVar17);
          }
          if ((long)uVar17 < (long)uVar7) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100041520);
            (*pcVar3)();
          }
          uVar15 = uVar7;
          if ((long)uVar7 < 0) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100041328);
            (*pcVar3)();
          }
        }
        else if (uVar17 == 1) {
          uVar15 = 1;
        }
        else {
          uVar7 = 1;
          pcVar11 = puVar8 + 0x21;
          do {
            if (*pcVar11 == '\0') goto LAB_100041308;
            uVar12 = uVar7 + 1;
            if (SCARRY8(uVar7,1)) {
                    /* WARNING: Does not return */
              pcVar3 = (code *)SoftwareBreakpoint(1,0x1000414e8);
              (*pcVar3)();
            }
            uVar7 = uVar7 + 1;
            uVar15 = uVar17;
            pcVar11 = pcVar11 + 1;
          } while (uVar12 != uVar17);
        }
      }
      uVar7 = uVar17 + (uVar15 - uVar17);
      if (!SCARRY8(uVar17,uVar15 - uVar17)) {
        puVar14 = puVar8;
        if ((long)(*(ulong *)(puVar8 + 0x18) >> 1) < (long)uVar7) {
          uVar12 = uVar17;
          if (uVar17 <= uVar7) {
            uVar12 = uVar7;
          }
          puVar14 = (undefined *)0x1;
          FUN_10078f72c(1,uVar12,1,puVar8);
        }
        thunk_FUN_1001d7aec(uVar15,uVar17,0);
        puVar8 = puVar14;
        if (*(ulong *)(puVar14 + 0x18) >> 1 <= *(ulong *)(puVar14 + 0x10)) {
          puVar8 = (undefined *)0x1;
          FUN_10078f72c(1,*(ulong *)(puVar14 + 0x10) + 1,1,puVar14);
        }
        thunk_FUN_1001d21e4(0,0,1,5);
        return puVar8;
      }
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x100041524);
      (*pcVar3)();
    }
  }
  puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  return puVar8;
code_r0x000100041034:
  puVar14 = puVar14 + 1;
  if (puVar16 == puVar14) goto LAB_100041040;
  goto LAB_100041024;
code_r0x0001000411dc:
  uVar15 = uVar15 + 1;
  uVar7 = uVar17;
  if (uVar17 == uVar15) goto LAB_100041280;
  goto LAB_1000411c8;
}

// ==== 100041684 _TtC8Playback28TransitionMenuViewController::viewDidLoad ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback28TransitionMenuViewController::viewDidLoad(ID param_1,SEL param_2)

{
  FUN_1000415a8(param_1);
  return;
}

// ==== 1000416ac _TtC8Playback28TransitionMenuViewController::viewDidLayoutSubviews ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void __thiscall
_TtC8Playback28TransitionMenuViewController::viewDidLayoutSubviews
          (_TtC8Playback28TransitionMenuViewController *this,ID param_1,SEL param_2)

{
  class_t *pcVar1;
  ID self;
  undefined8 in_d1;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  _objc_msgSendSuper2(&local_40,"viewDidLayoutSubviews");
  self = _objc_msgSend(param_1,"tableView");
  if (self != 0) {
    _objc_msgSend(self,"contentSize");
    if (DAT_100ade930 != -1) {
      _swift_once(&DAT_100ade930,FUN_100040e74);
    }
    _objc_msgSend(param_1,"setPreferredContentSize:",DAT_100af5758,in_d1);
  }
  return;
}

// ==== 100041784 FUN_100041784 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_100041784(long param_1)

{
  undefined1 uVar1;
  long lVar2;
  long lVar3;
  ID self;
  ID unaff_x20;
  undefined1 local_160;
  undefined7 uStack_15f;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 local_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_de;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_4e;
  
  FUN_100040f1c();
  lVar3 = param_1;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if ((-1 < lVar3) && (lVar3 < *(long *)(param_1 + 0x10))) {
    uVar1 = *(undefined1 *)(param_1 + lVar3 + 0x20);
    _swift_bridgeObjectRelease(param_1);
    self = _objc_msgSend(unaff_x20,"tableView");
    _objc_msgSend(self,"reloadData");
    lVar2 = _TtC8Playback28TransitionMenuViewController::songIndex;
    uStack_158 = *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::songIndex)
    ;
    local_160 = uVar1;
    FUN_100042a90(&local_160);
    uStack_68 = uStack_f8;
    local_70 = local_100;
    uStack_60 = uStack_f0;
    uStack_4e = uStack_de;
    uStack_a8 = uStack_138;
    local_b0 = local_140;
    uStack_98 = uStack_128;
    uStack_a0 = uStack_130;
    uStack_88 = uStack_118;
    local_90 = local_120;
    uStack_78 = uStack_108;
    uStack_80 = uStack_110;
    local_d0 = CONCAT71(uStack_15f,local_160);
    uStack_c8 = uStack_158;
    uStack_b8 = uStack_148;
    uStack_c0 = uStack_150;
    FUN_1007dfdc0(&local_d0);
    lVar3 = unaff_x20 + _TtC8Playback28TransitionMenuViewController::delegate;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar3 != 0) {
      FUN_1003a1a04(uVar1,*(undefined8 *)
                           (unaff_x20 + _TtC8Playback28TransitionMenuViewController::song),
                    *(undefined8 *)(unaff_x20 + lVar2));
      _swift_unknownObjectRelease(lVar3);
    }
    return;
  }
  _swift_bridgeObjectRelease(param_1);
  return;
}

// ==== 1000418e0 _TtC8Playback28TransitionMenuViewController::initWithStyle: ====
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback28TransitionMenuViewController::initWithStyle_
             (ID param_1,SEL param_2,long_long param_3)

{
  long lVar1;
  class_t *pcVar2;
  ID IVar3;
  objc_super local_40;
  
  pcVar2 = (class_t *)param_1;
  _swift_getObjectType();
  *(undefined8 *)(param_1 + setlist) = 0;
  *(undefined8 *)(param_1 + song) = 0;
  *(undefined8 *)(param_1 + songIndex) = 0;
  lVar1 = param_1 + delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined8 *)(param_1 + ___lazy_storage___transitions) = 0;
  local_40.receiver = param_1;
  local_40.super_class = pcVar2;
  IVar3 = _objc_msgSendSuper2(&local_40,"initWithStyle:",param_3);
  return IVar3;
}

// ==== 100041978 FUN_100041978 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_100041978(undefined8 param_1,long param_2,undefined8 param_3)

{
  long lVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::setlist) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::song) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::songIndex) = 0;
  lVar1 = unaff_x20 + _TtC8Playback28TransitionMenuViewController::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback28TransitionMenuViewController::___lazy_storage___transitions) = 0;
  if (param_2 == 0) {
    param_1 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_1,param_2);
    _swift_bridgeObjectRelease(param_2);
  }
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"initWithNibName:bundle:",
                              param_1,param_3);
  return IVar2;
}

// ==== 100041a60 _TtC8Playback28TransitionMenuViewController::initWithNibName:bundle: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback28TransitionMenuViewController::initWithNibName_bundle_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  if (param_3 == 0) {
    param_3 = 0;
    param_2 = (SEL)0x0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  FUN_100041978(param_3,param_2,param_4);
  return param_3;
}

// ==== 100041ac0 FUN_100041ac0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_100041ac0(undefined8 param_1)

{
  long lVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::setlist) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::song) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::songIndex) = 0;
  lVar1 = unaff_x20 + _TtC8Playback28TransitionMenuViewController::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback28TransitionMenuViewController::___lazy_storage___transitions) = 0;
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffc0,"initWithCoder:",param_1);
  return IVar2;
}

// ==== 100041b7c _TtC8Playback28TransitionMenuViewController::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback28TransitionMenuViewController::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  FUN_100041ac0();
  return param_3;
}

// ==== 100041ba4 _TtC8Playback28TransitionMenuViewController::.cxx_destruct ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback28TransitionMenuViewController::_cxx_destruct(ID param_1,SEL param_2)

{
  FUN_100026610(param_1 + delegate);
  _swift_bridgeObjectRelease(*(undefined8 *)(param_1 + ___lazy_storage___transitions));
  return;
}

// ==== 100041bfc FUN_100041bfc ====
void FUN_100041bfc(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback28TransitionMenuViewController);
  return;
}

// ==== 100041c1c _TtC8Playback28TransitionMenuViewController::numberOfSectionsInTableView: ====
/* Function Stack Size: 0x18 bytes */

long_long _TtC8Playback28TransitionMenuViewController::numberOfSectionsInTableView_
                    (ID param_1,SEL param_2,ID param_3)

{
  return 1;
}

// ==== 100041c24 _TtC8Playback28TransitionMenuViewController::tableView:numberOfRowsInSection: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

long_long _TtC8Playback28TransitionMenuViewController::tableView_numberOfRowsInSection_
                    (ID param_1,SEL param_2,ID param_3,long_long param_4)

{
  long_long lVar1;
  
  FUN_100040f1c();
  lVar1 = *(long_long *)(param_1 + 0x10);
  _swift_bridgeObjectRelease(param_1);
  return lVar1;
}

// ==== 100041c88 FUN_100041c88 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_100041c88(ID param_1)

{
  byte bVar1;
  undefined8 uVar2;
  code *pcVar3;
  ID IVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 uVar7;
  ID IVar8;
  undefined *self;
  long lVar9;
  ID IVar10;
  ID IVar11;
  ID IVar12;
  undefined8 uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  long unaff_x20;
  ID IVar17;
  ID IVar18;
  
  IVar8 = param_1;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  uVar16 = IVar8;
  FUN_100040f1c();
  if ((long)IVar8 < 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x100042408);
    (*pcVar3)();
  }
  if (*(ulong *)(uVar16 + 0x10) <= IVar8) {
                    /* WARNING: Does not return */
    pcVar3 = (code *)SoftwareBreakpoint(1,0x10004240c);
    (*pcVar3)();
  }
  bVar1 = *(byte *)(uVar16 + IVar8 + 0x20);
  uVar16 = (ulong)bVar1;
  _swift_bridgeObjectRelease();
  uVar14 = (uint)bVar1;
  uVar15 = (uint)bVar1;
  if (bVar1 < 6 && (1 << (ulong)(uVar14 & 0x1f) & 0x31U) != 0) {
    uVar5 = 0xd000000000000022;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000022,0x80000001008d2510);
    uVar7 = uVar5;
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    IVar4 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar5,uVar7);
    uVar5 = 0;
    FUN_1006426e8(0);
    IVar8 = IVar4;
    _swift_dynamicCastClass(IVar4,uVar5);
    lVar9 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    lVar6 = _TtC8Playback28TransitionMenuViewController::song;
    if (IVar8 == 0) {
      return IVar4;
    }
    IVar17 = *(ID *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::song);
    if (IVar17 == 0) {
      IVar17 = 0;
    }
    else {
      IVar18 = *(ID *)(IVar17 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar18 == 0) {
        IVar11 = _objc_msgSend(IVar17,"workingCopyArrangementID");
        if (IVar11 == 0) {
          IVar17 = 0;
        }
        else {
          IVar10 = IVar11;
          FUN_10032ee88();
          IVar18 = IVar10;
          FUN_1005e3b94(IVar10,IVar11);
          _swift_bridgeObjectRelease(IVar10);
          if (IVar18 != 0) {
            *(ID *)(IVar17 + lVar9) = IVar18;
            goto LAB_100041db0;
          }
          IVar17 = 0;
        }
      }
      else {
LAB_100041db0:
        IVar17 = _objc_msgSend(IVar18,"transitionContinuePad");
      }
      lVar9 = _TtC8Playback4Song::privateWorkingCopyArrangement;
      IVar18 = *(ID *)(unaff_x20 + lVar6);
      if (IVar18 != 0) {
        lVar6 = *(long *)(IVar18 + _TtC8Playback4Song::privateWorkingCopyArrangement);
        if (lVar6 != 0) {
LAB_100041df0:
          FUN_1002da058(lVar6);
          goto LAB_100042070;
        }
        IVar11 = _objc_msgSend(IVar18,"workingCopyArrangementID");
        if (IVar11 != 0) {
          IVar10 = IVar11;
          FUN_10032ee88();
          IVar12 = IVar10;
          FUN_1005e3b94(IVar10,IVar11);
          _swift_bridgeObjectRelease(IVar10);
          if (IVar12 != 0) {
            *(ID *)(IVar18 + lVar9) = IVar12;
            lVar6 = 0;
            goto LAB_100041df0;
          }
        }
      }
    }
    lVar6 = 6;
LAB_100042070:
    FUN_100641948(uVar16,lVar6,IVar17);
    lVar6 = IVar8 + _TtC8Playback34TransitionContinuePadTableViewCell::delegate;
    *(undefined ***)(lVar6 + 8) = &PTR_PTR_100a21ef0;
    _swift_unknownObjectWeakAssign(lVar6,unaff_x20);
    uVar5 = 0x4038000000000000;
    if (uVar15 != 4) {
      uVar5 = 0x4051000000000000;
    }
    _objc_msgSend(IVar8,"setSeparatorInset:",0,uVar5,0,0);
    return IVar4;
  }
  uVar7 = 0xd000000000000019;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000019,0x80000001008d0540);
  uVar5 = uVar7;
  __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
  IVar8 = _objc_msgSend(param_1,"dequeueReusableCellWithIdentifier:forIndexPath:",uVar7,uVar5);
  IVar4 = _objc_msgSend(IVar8,"textLabel");
  if (IVar4 != 0) {
    uVar5 = 0x70616c7265764f;
    if (uVar14 != 2) {
      uVar5 = 0x64616673736f7243;
    }
    uVar7 = 0xe700000000000000;
    if (uVar14 != 2) {
      uVar7 = 0xe900000000000065;
    }
    uVar13 = 0xed0000676e6f5320;
    uVar2 = 0x7478654e20657543;
    if (uVar14 != 0) {
      uVar13 = 0xe800000000000000;
      uVar2 = 0x6b6e694c6f747541;
    }
    if (uVar15 < 2) {
      uVar7 = uVar13;
      uVar5 = uVar2;
    }
    self = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar17 = _objc_msgSend((ID)self,"mainBundle");
    uVar13 = uVar7;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (uVar5,uVar7,0,0,IVar17,0,0xe000000000000000,0,0xe000000000000000);
    _swift_bridgeObjectRelease(uVar7);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar5,uVar13);
    _swift_bridgeObjectRelease(uVar13);
    _objc_msgSend(IVar4,"setText:",uVar5);
  }
  IVar4 = _objc_msgSend(IVar8,"imageView");
  if (IVar4 != 0) {
    FUN_1005fd008(uVar16);
    _objc_msgSend(IVar4,"setImage:",uVar16);
  }
  lVar6 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar4 = *(ID *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::song);
  if (IVar4 != 0) {
    lVar9 = *(long *)(IVar4 + _TtC8Playback4Song::privateWorkingCopyArrangement);
    if (lVar9 == 0) {
      IVar17 = _objc_msgSend(IVar4,"workingCopyArrangementID");
      if (IVar17 != 0) {
        IVar18 = IVar17;
        FUN_10032ee88();
        IVar11 = IVar18;
        FUN_1005e3b94(IVar18,IVar17);
        _swift_bridgeObjectRelease(IVar18);
        if (IVar11 != 0) {
          *(ID *)(IVar4 + lVar6) = IVar11;
          lVar9 = 0;
          goto LAB_10004203c;
        }
      }
    }
    else {
LAB_10004203c:
      uVar14 = (uint)lVar9;
      FUN_1002da058();
      if (uVar15 == (uVar14 & 0xff)) {
        uVar5 = 3;
        goto LAB_1000422c4;
      }
    }
  }
  uVar5 = 0;
LAB_1000422c4:
  _objc_msgSend(IVar8,"setAccessoryType:",uVar5);
  uVar5 = 0x70616c7265764f;
  if (uVar15 != 2) {
    uVar5 = 0x64616673736f7243;
  }
  uVar7 = 0xe700000000000000;
  if (uVar15 != 2) {
    uVar7 = 0xe900000000000065;
  }
  uVar13 = 0xeb00000000676e6f;
  uVar2 = 0x537478654e657543;
  if (uVar15 != 0) {
    uVar13 = 0xe800000000000000;
    uVar2 = 0x6b6e694c6f747541;
  }
  if (bVar1 < 2) {
    uVar7 = uVar13;
    uVar5 = uVar2;
  }
  __sSS6appendyySSF(uVar5,uVar7);
  uVar5 = 0xd00000000000001c;
  _swift_bridgeObjectRelease(uVar7);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001c,0x80000001008d24f0);
  _swift_bridgeObjectRelease(0x80000001008d24f0);
  _objc_msgSend(IVar8,"setAccessibilityIdentifier:",uVar5);
  return IVar8;
}

// ==== 10004240c _TtC8Playback28TransitionMenuViewController::tableView:cellForRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback28TransitionMenuViewController::tableView_cellForRowAtIndexPath_
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
  FUN_100041c88(param_3,puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return param_3;
}

// ==== 10004259c _TtC8Playback28TransitionMenuViewController::tableView:willSelectRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback28TransitionMenuViewController::tableView_willSelectRowAtIndexPath_
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
  FUN_1000424c4(lVar5,param_1,puVar7);
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

// ==== 1000426bc _TtC8Playback28TransitionMenuViewController::tableView:didSelectRowAtIndexPath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void _TtC8Playback28TransitionMenuViewController::tableView_didSelectRowAtIndexPath_
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
  FUN_100041784(puVar2);
  (**(code **)(lVar3 + 8))(puVar2,lVar1);
  return;
}

// ==== 1000428f4 FUN_1000428f4 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1000428f4(ID param_1)

{
  long lVar1;
  ID IVar2;
  long lVar3;
  long unaff_x20;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 local_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_de;
  undefined1 local_d0;
  undefined7 uStack_cf;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_4e;
  
  IVar2 = _objc_msgSend(param_1,"isOn");
  lVar1 = _TtC8Playback28TransitionMenuViewController::songIndex;
  uStack_c8 = *(undefined8 *)(unaff_x20 + _TtC8Playback28TransitionMenuViewController::songIndex);
  local_d0 = (undefined1)IVar2;
  FUN_1000429f0(&local_d0);
  uStack_f8 = uStack_68;
  local_100 = local_70;
  uStack_f0 = uStack_60;
  uStack_de = uStack_4e;
  uStack_138 = uStack_a8;
  local_140 = local_b0;
  uStack_128 = uStack_98;
  uStack_130 = uStack_a0;
  uStack_118 = uStack_88;
  local_120 = local_90;
  uStack_108 = uStack_78;
  uStack_110 = uStack_80;
  local_160 = CONCAT71(uStack_cf,local_d0);
  uStack_158 = uStack_c8;
  uStack_148 = uStack_b8;
  uStack_150 = uStack_c0;
  FUN_1007dfdc0(&local_160);
  lVar3 = unaff_x20 + _TtC8Playback28TransitionMenuViewController::delegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    IVar2 = _objc_msgSend(param_1,"isOn");
    FUN_1003a215c(IVar2,*(undefined8 *)
                         (unaff_x20 + _TtC8Playback28TransitionMenuViewController::song),
                  *(undefined8 *)(unaff_x20 + lVar1),0);
    _swift_unknownObjectRelease(lVar3);
  }
  return;
}

// ==== 1000ea8b8 _TtC8Playback33PremiumSubscriptionViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback33PremiumSubscriptionViewController::
viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback33PremiumSubscriptionViewController *this,ID param_1,SEL param_2,
          CGSize param_3,ID param_4)

{
  class_t *pcVar1;
  double dVar2;
  objc_super local_50;
  
  dVar2 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  _swift_unknownObjectRetain(dVar2);
  _objc_msgSendSuper2(&local_50,"viewWillTransitionToSize:withTransitionCoordinator:",dVar2);
  FUN_1000e9510();
  _swift_unknownObjectRelease(dVar2);
  return;
}

// ==== 10019bb58 FUN_10019bb58 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10019bb58(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  code *pcVar1;
  long lVar2;
  ID self;
  ID unaff_x20;
  undefined8 uVar3;
  undefined8 uVar4;
  
  _swift_getObjectType();
  uVar3 = param_1;
  uVar4 = param_2;
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,
                      "viewWillTransitionToSize:withTransitionCoordinator:",param_1,param_2,param_3)
  ;
  lVar2 = unaff_x20 + _TtC8Playback26SettingsMainViewController::delegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar2 != 0) {
    FUN_1003fd18c(0);
    _swift_unknownObjectRelease(lVar2);
    self = _objc_msgSend(unaff_x20,"view");
    if (self == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x10019bc38);
      (*pcVar1)();
    }
    _objc_msgSend(self,"setFrame:",uVar3,uVar4,param_1,param_2);
  }
  return;
}

// ==== 10019bc38 _TtC8Playback26SettingsMainViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback26SettingsMainViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback26SettingsMainViewController *this,ID param_1,SEL param_2,CGSize param_3,
          ID param_4)

{
  double dVar1;
  
  dVar1 = param_3.field0_0x0;
  _swift_unknownObjectRetain(dVar1,param_2,dVar1,param_3.field1_0x8);
  FUN_10019bb58(dVar1);
  _swift_unknownObjectRelease(dVar1);
  return;
}

// ==== 1001af9d0 FUN_1001af9d0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_1001af9d0(void)

{
  ulong uVar1;
  code *pcVar2;
  ulong uVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  ID IVar9;
  ID IVar10;
  ID IVar11;
  ulong uVar12;
  ID unaff_x20;
  ID IVar13;
  ulong uVar14;
  long lVar15;
  ulong uVar16;
  
  uVar3 = _objc_msgSend(unaff_x20,"subviews");
  uVar4 = 0;
  FUN_100023404(0,&DAT_100af5698,&PTR__OBJC_CLASS___UIView_100aa3dd8);
  __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar3,uVar4);
  if (uVar3 >> 0x3e == 0) {
    uVar14 = *(ulong *)((uVar3 & 0xfffffffffffff8) + 0x10);
    puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    uVar14 = uVar3 & 0xffffffffffffff8;
    if ((long)uVar3 < 0) {
      uVar14 = uVar3;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar8;
  if (uVar14 == 0) {
    _swift_retain(puVar8);
  }
  else {
    if ((long)uVar14 < 1) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1001afddc);
      (*pcVar2)();
    }
    _swift_retain(puVar8);
    _swift_bridgeObjectRetain(uVar3);
    uVar16 = 0;
    do {
      if ((uVar3 & 0xc000000000000001) == 0) {
        uVar5 = *(ulong *)(uVar3 + uVar16 * 8 + 0x20);
      }
      else {
        uVar5 = uVar16;
        FUN_1000ccea8(uVar16,uVar3);
      }
      uVar4 = 0;
      FUN_100242880(0);
      _swift_dynamicCastClass(uVar5,uVar4);
      if (uVar5 != 0) {
        puVar7 = puVar8;
        _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
        if ((((int)puVar7 == 0) || ((long)puVar8 < 0)) ||
           (puVar7 = puVar8, ((ulong)puVar8 >> 0x3e & 1) != 0)) {
          if ((ulong)puVar8 >> 0x3e == 0) {
            puVar6 = *(undefined **)(((ulong)puVar8 & 0xfffffffffffff8) + 0x10);
          }
          else {
            puVar6 = (undefined *)((ulong)puVar8 & 0xffffffffffffff8);
            if ((long)puVar8 < 0) {
              puVar6 = puVar8;
            }
            __ss18_CocoaArrayWrapperV8endIndexSivg(puVar6);
          }
          puVar7 = (undefined *)0x0;
          FUN_10078eae4(0,puVar6 + 1,1,puVar8);
        }
        uVar12 = (ulong)puVar7 & 0xffffffffffffff8;
        uVar1 = *(ulong *)(uVar12 + 0x10);
        puVar8 = puVar7;
        if (*(ulong *)(uVar12 + 0x18) >> 1 <= uVar1) {
          puVar8 = (undefined *)(ulong)(1 < *(ulong *)(uVar12 + 0x18));
          FUN_10078eae4(puVar8,uVar1 + 1,1,puVar7);
          uVar12 = (ulong)puVar8 & 0xffffffffffffff8;
        }
        *(ulong *)(uVar12 + 0x10) = uVar1 + 1;
        *(ulong *)(uVar12 + uVar1 * 8 + 0x20) = uVar5;
      }
      uVar16 = uVar16 + 1;
    } while (uVar14 != uVar16);
    _swift_bridgeObjectRelease(uVar3);
  }
  _swift_bridgeObjectRelease(uVar3);
  if ((ulong)puVar8 >> 0x3e == 0) {
    puVar7 = *(undefined **)(((ulong)puVar8 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar7 = (undefined *)((ulong)puVar8 & 0xffffffffffffff8);
    if ((long)puVar8 < 0) {
      puVar7 = puVar8;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar7 == (undefined *)0x0) {
    _swift_bridgeObjectRelease(puVar8);
  }
  else {
    if ((long)puVar7 < 1) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1001afde0);
      (*pcVar2)();
    }
    _swift_bridgeObjectRetain(puVar8);
    lVar15 = 0x20;
    do {
      _objc_msgSend(*(ID *)(puVar8 + lVar15),"removeFromSuperview");
      lVar15 = lVar15 + 8;
      puVar7 = puVar7 + -1;
    } while (puVar7 != (undefined *)0x0);
    _swift_bridgeObjectRelease_n(puVar8,2);
  }
  IVar13 = (ID)*(byte *)(unaff_x20 + _TtC8Playback23SetlistTransitionButton::transition);
  uVar4 = 0;
  FUN_100242880(0);
  _objc_allocWithZone();
  FUN_100242658(IVar13,uVar4);
  _objc_msgSend(IVar13,"setTranslatesAutoresizingMaskIntoConstraints:",0);
  IVar9 = _objc_msgSend(unaff_x20,"addSubview:",IVar13);
  FUN_10078bde8();
  _swift_allocObject();
  *(undefined8 *)(IVar9 + 0x18) = 5;
  *(undefined8 *)(IVar9 + 0x10) = 2;
  IVar10 = _objc_msgSend(IVar13,"centerXAnchor");
  IVar11 = _objc_msgSend(unaff_x20,"centerXAnchor");
  IVar10 = _objc_msgSend(IVar10,"constraintEqualToAnchor:",IVar11);
  *(ID *)(IVar9 + 0x20) = IVar10;
  IVar13 = _objc_msgSend(IVar13,"centerYAnchor");
  IVar10 = _objc_msgSend(unaff_x20,"centerYAnchor");
  IVar13 = _objc_msgSend(IVar13,"constraintEqualToAnchor:constant:",0xbff0000000000000,IVar10);
  *(ID *)(IVar9 + 0x28) = IVar13;
  uVar4 = 0;
  FUN_100023404(0,&DAT_100af5690,&PTR__OBJC_CLASS___NSLayoutConstraint_100aa3ea8);
  IVar13 = IVar9;
  __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(IVar9,uVar4);
  _swift_bridgeObjectRelease(IVar9);
  _objc_msgSend(unaff_x20,"addConstraints:",IVar13);
  return 0;
}

// ==== 1001b03b8 FUN_1001b03b8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_1001b03b8(void)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined *puVar4;
  ID IVar5;
  ID unaff_x20;
  code *pcVar6;
  long lVar7;
  undefined8 uVar8;
  undefined1 *puVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined1 auStack_80 [32];
  
  iVar1 = 2;
  FUN_1008c26ac(2,0xf,0,0);
  if (iVar1 == 0) {
    uVar3 = 0xd000000000000018;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000018,0x80000001008e0f40);
    puVar4 = &_OBJC_CLASS___UIImage;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)puVar4,"imageNamed:",uVar3);
    _objc_msgSend(unaff_x20,"setBackgroundImage:forState:",IVar5,0);
    IVar5 = _objc_msgSend(unaff_x20,"imageView");
    if (IVar5 != 0) {
      _objc_msgSend(IVar5,"setContentMode:",1);
    }
    _objc_msgSend(unaff_x20,"setAdjustsImageWhenDisabled:",0);
  }
  else {
    lVar2 = 0;
    __sSo8UIButtonC5UIKitE13ConfigurationVMa();
    lVar11 = *(long *)(lVar2 + -8);
    puVar9 = auStack_80 + -(*(long *)(lVar11 + 0x40) + 0xfU & 0xfffffffffffffff0);
    puVar4 = &DAT_100af5730;
    FUN_100021774();
    lVar12 = *(long *)(*(long *)(puVar4 + -8) + 0x40);
    lVar10 = (long)puVar9 - (lVar12 + 0xfU & 0xfffffffffffffff0);
    __sSo8UIButtonC5UIKitE13configurationAbCE13ConfigurationVSgvg(lVar10);
    pcVar6 = *(code **)(lVar11 + 0x30);
    lVar7 = lVar10;
    (*pcVar6)(lVar10,1,lVar2);
    if ((int)lVar7 == 1) {
      __sSo8UIButtonC5UIKitE13ConfigurationV5plainAEyFZ(puVar9);
      lVar7 = lVar10;
      (*pcVar6)(lVar10,1,lVar2);
      if ((int)lVar7 != 1) {
        FUN_100040c24(lVar10);
      }
    }
    else {
      (**(code **)(lVar11 + 0x20))(puVar9,lVar10,lVar2);
    }
    uVar3 = 0xd000000000000018;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000018,0x80000001008e0f40);
    puVar4 = &_OBJC_CLASS___UIImage;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)puVar4,"imageNamed:",uVar3);
    pcVar6 = (code *)auStack_80;
    __sSo8UIButtonC5UIKitE13ConfigurationV10backgroundAC012UIBackgroundC0VvM();
    __s5UIKit25UIBackgroundConfigurationV5imageSo7UIImageCSgvs(IVar5);
    (*pcVar6)(auStack_80,0);
    lVar7 = (long)puVar9 - (lVar12 + 0xfU & 0xfffffffffffffff0);
    (**(code **)(lVar11 + 0x10))(lVar7,puVar9,lVar2);
    (**(code **)(lVar11 + 0x38))(lVar7,0,1,lVar2);
    __sSo8UIButtonC5UIKitE13configurationAbCE13ConfigurationVSgvs(lVar7);
    (**(code **)(lVar11 + 8))(puVar9,lVar2);
  }
  FUN_1001af9d0();
  FUN_1001afde0(*(undefined1 *)(unaff_x20 + _TtC8Playback23SetlistTransitionButton::continuePad));
  uVar3 = 0xd000000000000017;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000017,0x800000010092a900);
  _objc_msgSend(unaff_x20,"setAccessibilityIdentifier:",uVar3);
  uVar8 = 0x61725420676e6f53;
  uVar3 = uVar8;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x61725420676e6f53,0xef6e6f697469736e);
  _objc_msgSend(unaff_x20,"setAccessibilityLabel:",uVar3);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x61725420676e6f53,0xef6e6f697469736e);
  _objc_msgSend(unaff_x20,"setAccessibilityHint:",uVar8);
  return 0;
}

// ==== 1001b0748 _TtC8Playback23SetlistTransitionButton::initWithFrame: ====
/* Function Stack Size: 0x30 bytes */

ID _TtC8Playback23SetlistTransitionButton::initWithFrame_(ID param_1,SEL param_2,CGRect param_3)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_50;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType
            (param_1,param_2,param_3.field0_0x0.field0_0x0,param_3.field0_0x0.field1_0x8,
             param_3.field1_0x10.field0_0x0,param_3.field1_0x10.field1_0x8);
  *(undefined1 *)(param_1 + transition) = 0;
  *(undefined1 *)(param_1 + continuePad) = 0;
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_50,"initWithFrame:");
  return IVar2;
}

// ==== 1001b07cc _TtC8Playback23SetlistTransitionButton::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback23SetlistTransitionButton::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  *(undefined1 *)(param_1 + transition) = 0;
  *(undefined1 *)(param_1 + continuePad) = 0;
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithCoder:",param_3);
  return IVar2;
}

// ==== 1001b0864 FUN_1001b0864 ====
void FUN_1001b0864(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback23SetlistTransitionButton);
  return;
}

// ==== 1001b4e7c thunk_FUN_1004f2edc ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001004f36a0) */
/* WARNING: Removing unreachable block (ram,0x0001004f35c8) */
/* WARNING: Removing unreachable block (ram,0x0001004f39a8) */

long thunk_FUN_1004f2edc(double param_1)

{
  double *pdVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  ID IVar5;
  long lVar6;
  double dVar7;
  undefined *puVar8;
  double dVar9;
  undefined8 uVar10;
  ID IVar11;
  ulong uVar12;
  undefined *puVar13;
  char *pcVar14;
  long lVar15;
  long unaff_x20;
  ID IVar16;
  long lVar17;
  long lVar18;
  ID self;
  long lVar19;
  long lVar20;
  undefined1 auStack_80 [16];
  
  lVar20 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar15 = *(long *)(unaff_x20 + _TtC8Playback9Sequencer::channelGroup);
  if (lVar15 == 0) {
    puVar8 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    _objc_msgSend((ID)puVar8,"sharedApplication");
    return 0;
  }
  self = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::song);
  IVar16 = *(ID *)(self + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar16 == 0) {
    _swift_retain(lVar15);
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 != 0) {
      IVar5 = IVar11;
      FUN_10032ee88();
      IVar16 = IVar5;
      FUN_1005e3b94(IVar5,IVar11);
      _swift_bridgeObjectRelease(IVar5);
      if (IVar16 != 0) {
        *(ID *)(self + lVar20) = IVar16;
        goto LAB_1004f2f44;
      }
    }
  }
  else {
    _swift_retain(lVar15);
LAB_1004f2f44:
    _objc_msgSend(IVar16,"storedEndTime");
    dVar7 = param_1;
    IVar16 = _objc_msgSend(IVar16,"song");
    if (IVar16 == 0) {
      dVar9 = 1.0;
    }
    else {
      FUN_1003220ec();
      dVar9 = dVar7;
    }
    FUN_1004f240c(0);
    param_1 = ABS(param_1 * dVar9 - dVar7);
    if (param_1 < 0.6) {
      *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEndThreshold) = 1;
    }
  }
  FUN_1004f240c();
  if (*(double *)(unaff_x20 + _TtC8Playback9Sequencer::nextPreparationSequenceTime) <= param_1) {
    if (*(long *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) != 0) goto LAB_1004f3c70;
    FUN_1004fdbe0();
  }
  IVar16 = *(ID *)(self + lVar20);
  if (IVar16 == 0) {
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 != 0) {
      IVar5 = IVar11;
      FUN_10032ee88();
      IVar16 = IVar5;
      FUN_1005e3b94(IVar5,IVar11);
      _swift_bridgeObjectRelease(IVar5);
      if (IVar16 != 0) {
        *(ID *)(self + lVar20) = IVar16;
        goto LAB_1004f30f8;
      }
    }
LAB_1004f322c:
    bVar3 = false;
  }
  else {
LAB_1004f30f8:
    IVar16 = _objc_msgSend(IVar16,"song");
    if ((IVar16 == 0) || (*(char *)(IVar16 + _TtC8Playback4Song::isLiveCrossfading) != '\x01')) {
      uVar4 = 0;
      FUN_1002da058();
      if ((uVar4 & 0xff) != 3) goto LAB_1004f322c;
    }
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    lVar6 = *(long *)(DAT_100b75a80 + 0x10);
    if ((lVar6 == 0) || (FUN_1004b7958(), lVar6 == 0)) goto LAB_1004f322c;
    bVar3 = true;
  }
  if (DAT_100adeca8 != -1) {
    _swift_once(&DAT_100adeca8,FUN_100224b00);
  }
  lVar6 = *(long *)(DAT_100b75a80 + 0x10);
  if ((lVar6 != 0) && (FUN_1004a9df0(), lVar6 != 0)) {
    FUN_10034293c(0);
    IVar16 = self;
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(self,lVar6);
    if ((IVar16 & 1) != 0) {
      IVar16 = *(ID *)(self + lVar20);
      if (IVar16 == 0) {
        IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
        dVar7 = 0.0;
        if (IVar11 != 0) {
          IVar5 = IVar11;
          FUN_10032ee88();
          IVar16 = IVar5;
          FUN_1005e3b94(IVar5,IVar11);
          _swift_bridgeObjectRelease(IVar5);
          dVar7 = 0.0;
          if (IVar16 != 0) {
            *(ID *)(self + lVar20) = IVar16;
            goto LAB_1004f32c0;
          }
        }
      }
      else {
LAB_1004f32c0:
        pcVar14 = "endFade";
        IVar16 = _objc_msgSend(IVar16,"endFade");
        dVar7 = 0.0;
        if ((((int)IVar16 != 0) &&
            (*(char *)(lVar15 + _TtC8Playback16SongChannelGroup::fadeStartTimecode + 8) == '\x01'))
           && (FUN_1004fbb78(), ((ulong)pcVar14 & 1) == 0)) {
          dVar9 = dVar7;
          FUN_1004f240c();
          lVar6 = _TtC8Playback9Sequencer::fadeOutAtEndDidBegin;
          if (param_1 < dVar7) {
            bVar3 = true;
          }
          dVar7 = dVar9;
          if ((!bVar3) &&
             ((*(byte *)(unaff_x20 + _TtC8Playback9Sequencer::fadeOutAtEndDidBegin) & 1) == 0)) {
            FUN_100647c80(1,0,0,0);
            *(undefined1 *)(unaff_x20 + lVar6) = 1;
            puVar8 = &_OBJC_CLASS___UIApplication;
            _swift_getInitializedObjCClass();
            IVar16 = _objc_msgSend((ID)puVar8,"sharedApplication");
            dVar9 = (double)_objc_msgSend(IVar16,"delegate");
            dVar7 = 0.0;
            if (dVar9 != 0.0) {
              uVar10 = 0;
              FUN_100842dec(0);
              dVar7 = dVar9;
              _swift_dynamicCastClass(dVar9,uVar10);
              if (((dVar7 == 0.0) ||
                  (*(ID *)((long)dVar7 + _TtC8Playback11AppDelegate::window) == 0)) ||
                 (IVar16 = _objc_msgSend(*(ID *)((long)dVar7 + _TtC8Playback11AppDelegate::window),
                                         "rootViewController"), IVar16 == 0)) {
                _swift_unknownObjectRelease();
                dVar7 = dVar9;
              }
              else {
                uVar10 = 0;
                FUN_100413a94(0);
                _swift_dynamicCastClass(IVar16,uVar10);
                _swift_unknownObjectRelease(dVar9);
                if (IVar16 != 0) {
                  dVar7 = 0.0;
                  if (*(long *)(IVar16 + _TtC8Playback18MainViewController::transportViewController)
                      == 0) goto LAB_1004f3c9c;
                  IVar16 = *(long *)(IVar16 + _TtC8Playback18MainViewController::
                                              transportViewController) +
                           _TtC8Playback23TransportViewController::fadeButton;
                  _swift_unknownObjectWeakLoadStrong();
                  if (IVar16 == 0) {
                    /* WARNING: Does not return */
                    pcVar2 = (code *)SoftwareBreakpoint(1,0x1004f3f10);
                    (*pcVar2)();
                  }
                  _objc_msgSend(IVar16,"setSelected:",1);
                  FUN_100867240(0);
                }
                dVar7 = 0.0;
              }
            }
          }
        }
      }
LAB_1004f3c9c:
      FUN_100500a94();
      if (((ulong)dVar7 & 1) != 0) {
        uVar10 = *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement);
        *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) = 0;
        _swift_release(uVar10);
        FUN_1004f3f10();
      }
    }
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar6 = *(long *)(DAT_100b75e40 + 0x18);
  if (lVar6 != 0) {
    lVar17 = *(long *)(lVar6 + 0x78);
    if (lVar17 == 0) {
      lVar18 = *(long *)(lVar6 + 0x10);
      FUN_10073f4a4(0);
      _swift_allocObject();
      _swift_retain(lVar6);
      FUN_10074128c();
      uVar10 = *(undefined8 *)(lVar6 + 0x78);
      *(long *)(lVar6 + 0x78) = lVar18;
      _swift_retain(lVar18);
      _swift_release(uVar10);
      lVar17 = 0;
    }
    else {
      _swift_retain(lVar6);
      lVar18 = lVar17;
    }
    _swift_retain(lVar17);
    _swift_release(lVar6);
    IVar16 = *(ID *)(self + lVar20);
    if (IVar16 == 0) {
      IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
      if (IVar11 != 0) {
        IVar5 = IVar11;
        FUN_10032ee88();
        IVar16 = IVar5;
        FUN_1005e3b94(IVar5,IVar11);
        _swift_bridgeObjectRelease(IVar5);
        if (IVar16 != 0) {
          *(ID *)(self + lVar20) = IVar16;
          goto LAB_1004f3530;
        }
      }
      _swift_release(lVar18);
    }
    else {
LAB_1004f3530:
      if (((*(byte *)(lVar18 + 0x39) & 1) == 0) &&
         (IVar11 = _objc_msgSend(IVar16,"padIntroOutroOnly"), (int)IVar11 != 0)) {
        pdVar1 = (double *)(unaff_x20 + _TtC8Playback9Sequencer::padIntroTrigger);
        if ((((ulong)pdVar1[1] & 1) == 0) &&
           (((*(byte *)((long)pdVar1 + 9) & 1) == 0 && (FUN_1004f240c(), *pdVar1 < param_1)))) {
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar13 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(),
             puVar8 = PTR___swiftEmptyArrayStorage_100a1e050, puVar13 == (undefined *)0x0)) {
            puVar13 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(puVar8);
          }
          FUN_10073b6dc(0,0,1,puVar13,0,1);
          _swift_bridgeObjectRelease(puVar13);
          *(undefined1 *)(pdVar1 + 1) = 1;
        }
        pdVar1 = (double *)(unaff_x20 + _TtC8Playback9Sequencer::padOutroTrigger);
        if ((((((ulong)pdVar1[1] & 1) == 0) && ((*(byte *)((long)pdVar1 + 9) & 1) == 0)) &&
            (IVar16 = _objc_msgSend(IVar16,"includePad"), (int)IVar16 != 0)) &&
           ((FUN_1004f240c(), *pdVar1 < param_1 && (FUN_1002dc978(), IVar16 != 0)))) {
          IVar11 = _objc_msgSend(self,"keyID");
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar8 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(), puVar8 == (undefined *)0x0)) {
            puVar8 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(PTR___swiftEmptyArrayStorage_100a1e050);
          }
          FUN_10073b6dc(IVar16,(long)(int)IVar11,0,puVar8,0,1);
          _swift_bridgeObjectRelease(puVar8);
          *(undefined1 *)(pdVar1 + 1) = 1;
        }
        if (*(char *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEndThreshold) == '\x01') {
          IVar16 = *(ID *)(self + lVar20);
          if (IVar16 == 0) {
            IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
            if (IVar11 != 0) {
              IVar5 = IVar11;
              FUN_10032ee88();
              IVar16 = IVar5;
              FUN_1005e3b94(IVar5,IVar11);
              _swift_bridgeObjectRelease(IVar5);
              if (IVar16 != 0) {
                *(ID *)(self + lVar20) = IVar16;
                goto LAB_1004f36f8;
              }
            }
            goto LAB_1004f3928;
          }
LAB_1004f36f8:
          IVar16 = _objc_msgSend(IVar16,"song");
          if ((IVar16 != 0) && (*(char *)(IVar16 + _TtC8Playback4Song::isLiveCrossfading) == '\x01')
             ) goto LAB_1004f3928;
          uVar4 = 0;
          FUN_1002da058();
          bVar3 = (uVar4 & 0xff) == 4;
        }
        else {
LAB_1004f3928:
          bVar3 = false;
        }
        if ((((*(long *)(DAT_100b75e40 + 0x28) == 0) && (!bVar3)) &&
            (*(char *)(pdVar1 + 1) == '\x01')) &&
           (((*(byte *)((long)pdVar1 + 9) & 1) == 0 && (FUN_1004f240c(), param_1 < *pdVar1)))) {
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar13 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(),
             puVar8 = PTR___swiftEmptyArrayStorage_100a1e050, puVar13 == (undefined *)0x0)) {
            puVar13 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(puVar8);
          }
          FUN_10073b6dc(0,0,1,puVar13,0,1);
          _swift_release(lVar18);
          _swift_bridgeObjectRelease(puVar13);
          *(undefined1 *)(pdVar1 + 1) = 0;
          goto LAB_1004f39e8;
        }
      }
      _swift_release(lVar18);
    }
  }
LAB_1004f39e8:
  lVar6 = _TtC8Playback9Sequencer::uuid;
  lVar17 = *(long *)(DAT_100b75e40 + 0x28);
  if (lVar17 == 0) goto LAB_1004f3c70;
  _swift_retain();
  _swift_retain(lVar17);
  uVar12 = unaff_x20 + lVar6;
  __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar12,lVar17 + lVar6);
  _swift_release();
  _swift_release(lVar17);
  if ((uVar12 & 1) == 0) goto LAB_1004f3c70;
  IVar11 = *(ID *)(self + lVar20);
  IVar16 = IVar11;
  if (IVar11 == 0) {
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 == 0) goto LAB_1004f3c70;
    IVar5 = IVar11;
    FUN_10032ee88();
    IVar16 = IVar5;
    FUN_1005e3b94(IVar5,IVar11);
    _swift_bridgeObjectRelease(IVar5);
    if (IVar16 == 0) goto LAB_1004f3c70;
    *(ID *)(self + lVar20) = IVar16;
    IVar11 = 0;
  }
  FUN_1004f240c(IVar11);
  dVar7 = param_1;
  IVar11 = _objc_msgSend(IVar16,"storedSMPTETimelineLocation");
  if (IVar11 == 0) {
    FUN_1002e4b7c();
    lVar20 = _TtC8Playback9Sequencer::uuid;
    lVar17 = _TtC8Playback9Sequencer::smpteBeganDuringTransition;
  }
  else {
    _objc_msgSend(IVar11,"doubleValue");
    lVar20 = _TtC8Playback9Sequencer::uuid;
    lVar17 = _TtC8Playback9Sequencer::smpteBeganDuringTransition;
  }
  _TtC8Playback9Sequencer::uuid = lVar20;
  _TtC8Playback9Sequencer::smpteBeganDuringTransition = lVar17;
  if (((param_1 < dVar7) || ((*(byte *)(unaff_x20 + lVar17) & 1) != 0)) ||
     ((lVar18 = *(long *)(DAT_100b75e40 + 0x18), lVar18 == 0 ||
      (lVar19 = *(long *)(DAT_100b75e40 + 0x28), lVar19 == 0)))) goto LAB_1004f3c70;
  _swift_retain();
  _swift_retain(lVar18);
  _swift_retain(lVar19);
  uVar12 = lVar19 + lVar20;
  __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar12,unaff_x20 + lVar6);
  _swift_release(lVar19);
  _swift_release();
  if ((uVar12 & 1) == 0) {
    _swift_release(lVar15);
    lVar15 = lVar18;
    goto LAB_1004f3c70;
  }
  lVar20 = *(long *)(lVar18 + 0x48);
  _swift_retain(lVar20);
  _swift_release(lVar18);
  if (lVar20 == 0) goto LAB_1004f3c70;
  uVar12 = 0;
  thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
  if ((uVar12 & 1) == 0) {
    if (DAT_100ae0030 != -1) {
      _swift_once(&DAT_100ae0030,FUN_1008174c0);
    }
    uVar12 = 0;
    FUN_100819fe0();
    if ((uVar12 & 1) != 0) goto LAB_1004f3bec;
  }
  else {
LAB_1004f3bec:
    IVar11 = _objc_msgSend(IVar16,"storedSMPTEEnabled");
    if ((int)IVar11 != 0) {
      IVar11 = _objc_msgSend(IVar16,"storedSMPTETimelineLocation");
      if (IVar11 == 0) {
        FUN_1002e4b7c();
      }
      else {
        _objc_msgSend(IVar11,"doubleValue");
      }
      dVar9 = dVar7;
      _objc_msgSend(IVar16,"smpteStartTime");
      FUN_1000cfba4(dVar7);
      FUN_1000cfbac(dVar9);
      uVar12 = 0;
      thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
      if ((uVar12 & 1) == 0) {
        if (DAT_100ae0030 != -1) {
          _swift_once(&DAT_100ae0030,FUN_1008174c0);
        }
        uVar12 = 0;
        FUN_100819fe0();
        if ((uVar12 & 1) != 0) goto LAB_1004f3d2c;
      }
      else {
LAB_1004f3d2c:
        IVar16 = _objc_msgSend(self,"storedSMPTEFollowsDefaultArrangement");
        if ((IVar16 & 1) == 0) {
          FUN_1004f240c();
          goto LAB_1004f3d8c;
        }
      }
      uVar10 = *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
      _swift_retain(uVar10);
      __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                (auStack_80,FUN_100504fa8,uVar10,PTR___sSdN_100a1dd60);
      _swift_release(uVar10);
LAB_1004f3d8c:
      FUN_1000cfd9c();
      FUN_1000cfac8(*(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::privatePlayState));
      _swift_release(lVar20);
      _swift_release(lVar15);
      *(undefined1 *)(unaff_x20 + lVar17) = 1;
      return lVar15;
    }
  }
  FUN_1000cfac8(0);
  _swift_release(lVar20);
LAB_1004f3c70:
  _swift_release(lVar15);
  return lVar15;
}

// ==== 1001c01d4 FUN_1001c01d4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001001c08b4) */

void FUN_1001c01d4(double param_1,char *param_2,ID param_3,uint param_4,undefined8 param_5,
                  undefined8 param_6)

{
  byte bVar1;
  long lVar2;
  long lVar3;
  undefined *puVar4;
  ID self;
  undefined8 uVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined1 *puVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  undefined8 unaff_x20;
  ulong uVar14;
  char *pcVar15;
  char *pcVar16;
  code *pcVar17;
  long lVar18;
  long lVar19;
  byte *pbVar20;
  long lVar21;
  long lVar22;
  undefined8 auStack_1d0 [2];
  undefined1 auStack_1c0 [8];
  undefined8 auStack_1b8 [5];
  undefined1 auStack_190 [8];
  long local_188;
  long local_180;
  ID local_170;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined1 auStack_e8 [24];
  long local_d0;
  undefined *puStack_c8;
  char *local_b8;
  char *local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined1 local_80;
  
  lVar2 = 0;
  __s10Foundation10URLRequestVMa();
  lVar22 = *(long *)(lVar2 + -8);
  lVar10 = *(long *)(lVar22 + 0x40);
  uVar11 = lVar10 + 0xfU & 0xfffffffffffffff0;
  puVar8 = auStack_190 + -uVar11;
  lVar18 = (long)puVar8 - uVar11;
  lVar3 = 0;
  __s10Foundation3URLVMa();
  lVar21 = *(long *)(lVar3 + -8);
  uVar11 = *(long *)(lVar21 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar12 = lVar18 - uVar11;
  lVar13 = lVar12 - uVar11;
  lVar9 = lVar13 - uVar11;
  pcVar7 = param_2;
  _swift_bridgeObjectRetain();
  FUN_1001c14fc();
  local_b0 = pcVar7;
  FUN_1001c0098(&local_b0);
  _swift_bridgeObjectRelease(param_2);
  pcVar16 = local_b0;
  puVar4 = &_OBJC_CLASS___UIScreen;
  _swift_getInitializedObjCClass();
  _swift_retain(pcVar16);
  self = _objc_msgSend((ID)puVar4,"mainScreen");
  pcVar7 = "scale";
  _objc_msgSend(self,"scale");
  if (param_1 == 1.0) {
    uVar11 = 0;
  }
  else if (param_1 == 2.0) {
    uVar11 = 1;
  }
  else {
    if (param_1 != 3.0) {
      _swift_release(pcVar16);
      lVar19 = *(long *)(pcVar16 + 0x10);
      goto joined_r0x0001001c0878;
    }
    uVar11 = 2;
  }
  uVar14 = uVar11;
  pcVar7 = pcVar16;
  thunk_FUN_1002db810();
  pcVar15 = PTR___swiftEmptyArrayStorage_100a1e050;
  if ((uVar14 & 1) == 0) {
    _swift_release(pcVar16);
  }
  else {
    lVar19 = *(long *)(pcVar16 + 0x10);
    local_188 = lVar22;
    local_180 = lVar2;
    if (lVar19 == 0) {
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    }
    else {
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      pbVar20 = (byte *)(pcVar16 + 0x20);
      do {
        bVar1 = *pbVar20;
        if ((uint)bVar1 != (uint)uVar11) {
          pcVar7 = pcVar15;
          _swift_isUniquelyReferenced_nonNull_native();
          local_b0 = pcVar15;
          if (((ulong)pcVar7 & 1) == 0) {
            FUN_1001cd1e4(0,*(long *)(pcVar15 + 0x10) + 1,1);
          }
          uVar14 = *(ulong *)(local_b0 + 0x10);
          if (*(ulong *)(local_b0 + 0x18) >> 1 <= uVar14) {
            FUN_1001cd1e4(1 < *(ulong *)(local_b0 + 0x18),uVar14 + 1,1);
          }
          *(ulong *)(local_b0 + 0x10) = uVar14 + 1;
          local_b0[uVar14 + 0x20] = bVar1;
          pcVar15 = local_b0;
        }
        lVar19 = lVar19 + -1;
        pbVar20 = pbVar20 + 1;
      } while (lVar19 != 0);
    }
    _swift_release_n(pcVar16,2);
    uVar14 = *(ulong *)(pcVar15 + 0x10);
    pcVar7 = pcVar15;
    _swift_isUniquelyReferenced_nonNull_native();
    if (((int)pcVar7 == 0) || (pcVar16 = pcVar15, *(ulong *)(pcVar15 + 0x18) >> 1 <= uVar14)) {
      local_b8 = pcVar15;
      FUN_100790180();
      pcVar16 = pcVar7;
    }
    lVar2 = local_180;
    lVar22 = local_188;
    pcVar7 = (char *)0x0;
    local_b8 = pcVar16;
    thunk_FUN_1001d21e4(0,0,1,uVar11);
  }
  lVar19 = *(long *)(pcVar16 + 0x10);
joined_r0x0001001c0878:
  if (lVar19 == 0) {
    _swift_bridgeObjectRelease(pcVar16);
  }
  else {
    uVar11 = (ulong)(byte)pcVar16[0x20];
    _swift_bridgeObjectRelease(pcVar16);
    if (*(long *)(param_2 + 0x10) == 0) {
      return;
    }
    thunk_FUN_100793d2c(uVar11);
    if (((ulong)pcVar7 & 1) == 0) {
      return;
    }
    pcVar17 = *(code **)(lVar21 + 0x10);
    (*pcVar17)(lVar13,*(long *)(param_2 + 0x38) + *(long *)(lVar21 + 0x48) * uVar11,lVar3);
    (**(code **)(lVar21 + 0x20))(lVar9,lVar13,lVar3);
    local_170 = param_3;
    if (param_3 == 0) {
      uVar5 = 0x6f777472615f6f6e;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x6f777472615f6f6e,0xea00000000006b72);
      puVar4 = &_OBJC_CLASS___UIImage;
      _swift_getInitializedObjCClass();
      local_170 = _objc_msgSend((ID)puVar4,"imageNamed:",uVar5);
    }
    (*pcVar17)(lVar12,lVar9,lVar3);
    __s10Foundation10URLRequestV3url11cachePolicy15timeoutIntervalAcA3URLV_So017NSURLRequestCacheE0VSdtcfC
              (lVar18,0x405e000000000000,lVar12,0);
    __s14AlamofireImage0B18ResponseSerializerCMa(0);
    puVar4 = &DAT_100af52f0;
    FUN_100021774(&DAT_100af52f0);
    _swift_initStaticObject();
    puVar6 = puVar4;
    _swift_retain();
    FUN_100022d48();
    _swift_release(puVar4);
    FUN_1001c136c(puVar4 + 0x20);
    __s14AlamofireImage0B18ResponseSerializerC013addAcceptableB12ContentTypesyyShySSGFZ(puVar6);
    _swift_bridgeObjectRelease(puVar6);
    puStack_c8 = PTR___s10Foundation10URLRequestV9Alamofire0B11ConvertibleADWP_100a1d518;
    local_d0 = lVar2;
    FUN_1000881c8(auStack_e8);
    pcVar17 = *(code **)(lVar22 + 0x10);
    (*pcVar17)();
    local_f0 = 0;
    uStack_108 = 0;
    local_110 = 0;
    uStack_f8 = 0;
    uStack_100 = 0;
    (*pcVar17)(puVar8,lVar18,lVar2);
    uVar11 = (ulong)*(byte *)(lVar22 + 0x50);
    uVar14 = uVar11 + 0x30 & (uVar11 ^ 0xffffffffffffffff);
    puVar4 = &DAT_100a36550;
    _swift_allocObject(&DAT_100a36550,uVar14 + lVar10,uVar11 | 7);
    *(undefined8 *)(puVar4 + 0x10) = unaff_x20;
    *(ID *)(puVar4 + 0x18) = local_170;
    *(undefined8 *)(puVar4 + 0x20) = param_5;
    *(undefined8 *)(puVar4 + 0x28) = param_6;
    (**(code **)(lVar22 + 0x20))(puVar4 + uVar14,puVar8,lVar2);
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    FUN_100027524(param_5,param_6);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    uStack_a8 = 0;
    local_b0 = (char *)0x0;
    uStack_98 = 0;
    uStack_a0 = 0;
    uStack_88 = 0;
    local_90 = 0;
    local_80 = 8;
    uVar5 = 0;
    FUN_100023404(0,&DAT_100afb678,&PTR__OBJC_CLASS___UIImageView_100aa3db0);
    *(undefined8 *)(lVar9 + -0x18) = unaff_x20;
    *(undefined8 *)(lVar9 + -0x10) = uVar5;
    *(code **)(lVar9 + -0x28) = FUN_1001c1424;
    *(undefined **)(lVar9 + -0x20) = puVar4;
    *(undefined1 *)(lVar9 + -0x30) = 0;
    *(undefined8 *)(lVar9 + -0x40) = param_5;
    *(char ***)(lVar9 + -0x38) = &local_b0;
    __s9Alamofire0A9ExtensionV0A5ImageSo11UIImageViewCRbzlE03setC014withURLRequest8cacheKey011placeholderC010serializer6filter8progress0N5Queue15imageTransition03runcQ8IfCached10completionyAA0H11Convertible_p_SSSgSo0D0CSgAD0C18ResponseSerializerCSgAD0C6Filter_pSgySo10NSProgressCYbcSgSo17OS_dispatch_queueCAfDE0cQ0OSbyAA04DataW0VyAuD8AFIErrorOGcSgtF
              (auStack_e8,0,0,local_170,0,&local_110,0,0);
    _swift_release(puVar4);
    FUN_100023be4(&local_110,&DAT_100afb680);
    (**(code **)(lVar22 + 8))(lVar18,lVar2);
    (**(code **)(lVar21 + 8))(lVar9,lVar3);
    FUN_100023468(auStack_e8);
  }
  if ((param_4 & 1) == 0) {
    FUN_1000bd588();
  }
  return;
}

// ==== 1002425c0 _TtC8Playback23TransitionIconImageView::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback23TransitionIconImageView::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  class_t *pcVar1;
  ID IVar2;
  objc_super local_40;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  *(undefined1 *)(param_1 + transition) = 0;
  local_40.receiver = param_1;
  local_40.super_class = pcVar1;
  IVar2 = _objc_msgSendSuper2(&local_40,"initWithCoder:",param_3);
  if (IVar2 != 0) {
    FUN_1002428a0(IVar2);
  }
  return IVar2;
}

// ==== 100242658 FUN_100242658 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_100242658(ID param_1)

{
  bool bVar1;
  int iVar2;
  undefined *self;
  long unaff_x20;
  uint uVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  long lVar8;
  ID IVar3;
  
  _swift_getObjectType();
  uVar4 = (uint)param_1;
  *(char *)(unaff_x20 + _TtC8Playback23TransitionIconImageView::transition) = (char)param_1;
  FUN_1005fd008();
  if (param_1 == 0) {
    IVar3 = 0;
  }
  else {
    self = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    IVar3 = _objc_msgSend((ID)self,"currentDevice");
    iVar2 = (int)IVar3;
    FUN_100826670();
    bVar1 = 0xd < (iVar2 - 0xcU & 0xff);
    dVar5 = 18.0;
    if (bVar1) {
      dVar5 = 23.0;
    }
    dVar6 = 26.0;
    if (bVar1) {
      dVar6 = 32.0;
    }
    dVar7 = dVar5;
    if ((uVar4 & 0xff) != 5) {
      dVar7 = dVar6;
    }
    _objc_msgSend(param_1,"size");
    _objc_msgSend(param_1,"size");
    dVar6 = (dVar7 / dVar5) * dVar6;
    lVar8 = (long)dVar6;
    _objc_msgSend(param_1,"scale");
    _UIGraphicsBeginImageContextWithOptions(dVar7,lVar8,dVar6,0);
    IVar3 = _objc_msgSend(param_1,"drawInRect:",0,0,dVar7,lVar8);
    _UIGraphicsGetImageFromCurrentImageContext();
    _UIGraphicsEndImageContext();
  }
  IVar3 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa0,"initWithImage:",IVar3);
  return IVar3;
}

// ==== 1002427dc _TtC8Playback23TransitionIconImageView::initWithImage: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback23TransitionIconImageView::initWithImage_(ID param_1,SEL param_2,ID param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.TransitionIconImageView",0x20,"init(image:)",0xc,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x100242810);
  (*pcVar1)();
}

// ==== 100242810 _TtC8Playback23TransitionIconImageView::initWithImage:highlightedImage: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback23TransitionIconImageView::initWithImage_highlightedImage_
             (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.TransitionIconImageView",0x20,"init(image:highlightedImage:)",0x1d,0);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x100242854);
  (*pcVar1)();
}

// ==== 100242854 _TtC8Playback23TransitionIconImageView::initWithFrame: ====
/* Function Stack Size: 0x30 bytes */

ID _TtC8Playback23TransitionIconImageView::initWithFrame_(ID param_1,SEL param_2,CGRect param_3)

{
  code *pcVar1;
  
  __swift_stdlib_reportUnimplementedInitializer
            ("Playback.TransitionIconImageView",0x20,"init(frame:)",0xc,0,
             param_3.field1_0x10.field1_0x8);
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x100242880);
  (*pcVar1)();
}

// ==== 100242880 FUN_100242880 ====
void FUN_100242880(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback23TransitionIconImageView);
  return;
}

// ==== 1002428a0 FUN_1002428a0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_1002428a0(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  ID IVar4;
  undefined *self;
  ID unaff_x20;
  double dVar6;
  double dVar7;
  double dVar8;
  long lVar9;
  ID IVar5;
  
  lVar9 = _TtC8Playback23TransitionIconImageView::transition;
  IVar4 = (ID)*(byte *)(unaff_x20 + _TtC8Playback23TransitionIconImageView::transition);
  FUN_1005fd008();
  if (IVar4 == 0) {
    IVar4 = 0;
  }
  else {
    cVar1 = *(char *)(unaff_x20 + lVar9);
    self = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    IVar5 = _objc_msgSend((ID)self,"currentDevice");
    iVar3 = (int)IVar5;
    FUN_100826670();
    bVar2 = 0xd < (iVar3 - 0xcU & 0xff);
    dVar6 = 18.0;
    if (bVar2) {
      dVar6 = 23.0;
    }
    dVar7 = 26.0;
    if (bVar2) {
      dVar7 = 32.0;
    }
    dVar8 = dVar6;
    if (cVar1 != '\x05') {
      dVar8 = dVar7;
    }
    _objc_msgSend(IVar4,"size");
    _objc_msgSend(IVar4,"size");
    dVar7 = (dVar8 / dVar6) * dVar7;
    lVar9 = (long)dVar7;
    _objc_msgSend(IVar4,"scale");
    _UIGraphicsBeginImageContextWithOptions(dVar8,lVar9,dVar7,0);
    IVar4 = _objc_msgSend(IVar4,"drawInRect:",0,0,dVar8,lVar9);
    _UIGraphicsGetImageFromCurrentImageContext();
    _UIGraphicsEndImageContext();
  }
  _objc_msgSend(unaff_x20,"setImage:",IVar4);
  return 0;
}

// ==== 1002529bc FUN_1002529bc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1002529bc(undefined8 param_1,undefined8 param_2,ID param_3)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  void *pvVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  long unaff_x20;
  undefined1 *puVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined1 auStack_c0 [8];
  undefined8 local_b8;
  undefined *local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined *puStack_98;
  code *local_90;
  undefined *local_88;
  ID IVar6;
  
  _swift_getObjectType();
  lVar3 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar14 = *(long *)(lVar3 + -8);
  puVar11 = auStack_c0 + -(*(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar13 = *(long *)(lVar4 + -8);
  lVar12 = (long)puVar11 - (*(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff80,
                      "viewWillTransitionToSize:withTransitionCoordinator:",param_1,param_2,param_3)
  ;
  puVar5 = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar6 = _objc_msgSend((ID)puVar5,"currentDevice");
  uVar2 = (uint)IVar6;
  FUN_100826670();
  if ((uVar2 & 0xff) - 0xc < 0xe) {
    puVar5 = &DAT_100a3b0c0;
    _swift_allocObject(&DAT_100a3b0c0,0x18,7);
    *(long *)(puVar5 + 0x10) = unaff_x20;
    local_90 = FUN_10026fb64;
    local_b0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_a8 = 0x42000000;
    local_a0 = FUN_100252d98;
    puStack_98 = &DAT_100a3b0d8;
    local_88 = puVar5;
    pvVar7 = __Block_copy(&local_b0);
    _swift_release(local_88);
    _objc_msgSend(param_3,"animateAlongsideTransition:completion:",pvVar7,0);
    __Block_release(pvVar7);
  }
  else if (0xb < (uVar2 & 0xff)) {
    IVar6 = unaff_x20 + _TtC8Playback19MixerViewController::tracksCollectionView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar6 != 0) {
      IVar6 = _objc_msgSend(IVar6,"collectionViewLayout");
      _objc_msgSend(IVar6,"invalidateLayout");
    }
    uVar8 = 0;
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    puVar5 = &DAT_100a3b070;
    local_b8 = uVar8;
    _swift_allocObject(&DAT_100a3b070,0x18,7);
    *(long *)(puVar5 + 0x10) = unaff_x20;
    local_90 = FUN_10026fb5c;
    local_b0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_a8 = 0x42000000;
    local_a0 = FUN_10056b3d8;
    puStack_98 = &DAT_100a3b088;
    local_88 = puVar5;
    pvVar7 = __Block_copy(&local_b0);
    _swift_release(local_88);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar12);
    puVar1 = PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098;
    puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_b0 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar9 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar5);
    puVar5 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar10 = &DAT_100af52b8;
    FUN_1001d598c(&DAT_100af52b8,&DAT_100af52c0,puVar1);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (puVar11,&local_b0,puVar5,puVar10,lVar3,puVar9);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,lVar12,puVar11,pvVar7);
    __Block_release(pvVar7);
    (**(code **)(lVar14 + 8))(puVar11,lVar3);
    (**(code **)(lVar13 + 8))(lVar12,lVar4);
  }
  return;
}

// ==== 100252de0 _TtC8Playback19MixerViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback19MixerViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback19MixerViewController *this,ID param_1,SEL param_2,CGSize param_3,ID param_4
          )

{
  double dVar1;
  
  dVar1 = param_3.field0_0x0;
  _swift_unknownObjectRetain(dVar1,param_2,dVar1,param_3.field1_0x8);
  FUN_1002529bc(dVar1);
  _swift_unknownObjectRelease(dVar1);
  return;
}

// ==== 10027397c FUN_10027397c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Type propagation algorithm not settling */

void FUN_10027397c(undefined8 *param_1,undefined8 ******param_2,ID param_3,undefined8 param_4,
                  undefined8 *******param_5)

{
  long *plVar1;
  undefined8 *****pppppuVar2;
  undefined8 *puVar3;
  uint uVar4;
  undefined8 ******ppppppuVar5;
  undefined1 uVar6;
  undefined2 uVar7;
  long lVar8;
  undefined1 *puVar9;
  code *pcVar10;
  bool bVar11;
  int iVar12;
  undefined8 *******pppppppuVar13;
  ID IVar14;
  ID IVar15;
  ID IVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined8 *******pppppppuVar19;
  undefined8 ******ppppppuVar20;
  undefined *puVar21;
  undefined8 *******pppppppuVar22;
  undefined8 ****ppppuVar23;
  undefined8 ******ppppppuVar24;
  char *pcVar25;
  char *pcVar26;
  uint uVar27;
  undefined8 ******ppppppuVar28;
  ulong uVar29;
  undefined8 uVar30;
  long unaff_x21;
  undefined8 ****ppppuVar31;
  ulong uVar32;
  undefined8 *******pppppppuVar33;
  undefined8 ******ppppppuVar34;
  undefined *puVar35;
  undefined8 *******pppppppuVar36;
  undefined4 uVar37;
  long lVar38;
  undefined8 *****pppppuVar39;
  undefined4 uVar40;
  undefined8 ******ppppppuVar41;
  undefined8 ******ppppppuVar42;
  undefined1 auStack_380 [8];
  undefined1 *local_378;
  undefined8 ******local_370;
  undefined8 *******pppppppuStack_368;
  undefined8 *******local_360;
  undefined4 local_354;
  undefined8 *local_350;
  ID local_348;
  ulong local_340;
  undefined8 *******local_338;
  undefined8 *******local_330;
  undefined4 local_324;
  undefined4 local_320;
  undefined4 local_31c;
  undefined8 *******local_318;
  ID local_310;
  undefined8 *******local_308;
  undefined8 local_300;
  undefined8 *******local_2f8;
  undefined8 local_2f0;
  undefined *local_2e0;
  undefined8 ****local_2d8;
  undefined8 ******local_2d0;
  undefined8 ******ppppppuStack_2c8;
  undefined1 local_2c0;
  undefined7 uStack_2bf;
  undefined8 ******local_2b8;
  undefined1 local_2b0;
  undefined1 uStack_2af;
  undefined2 uStack_2ae;
  undefined4 uStack_2ac;
  undefined1 uStack_2a8;
  undefined1 uStack_2a7;
  undefined6 uStack_2a6;
  undefined8 ******local_2a0;
  undefined1 local_298;
  undefined7 uStack_297;
  undefined8 ******local_290;
  undefined1 uStack_288;
  undefined7 uStack_287;
  undefined *local_280;
  undefined8 *******pppppppuStack_278;
  undefined8 *******local_270;
  undefined8 *******pppppppuStack_268;
  undefined8 *******local_260;
  undefined4 uStack_258;
  undefined4 local_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined2 uStack_248;
  undefined1 uStack_246;
  undefined1 uStack_245;
  undefined8 *******local_240;
  undefined8 ******ppppppuStack_238;
  undefined1 local_230;
  undefined8 ******local_228;
  undefined1 local_220;
  undefined1 local_21f;
  undefined4 local_21c;
  undefined1 local_218;
  undefined1 local_217;
  undefined4 local_216;
  undefined2 local_212;
  undefined8 ******local_210;
  undefined1 local_208;
  undefined8 ******local_200;
  undefined1 local_1f8;
  undefined *local_1f0;
  undefined8 *******pppppppuStack_1e8;
  undefined8 *******local_1e0;
  undefined8 *******pppppppuStack_1d8;
  undefined8 *******local_1d0;
  ulong uStack_1c8;
  undefined8 *******local_1c0;
  undefined2 local_1b8;
  undefined1 local_1b6;
  undefined1 local_1b5;
  undefined1 local_1a8;
  undefined1 local_1a0;
  undefined4 local_19e;
  undefined2 local_19a;
  undefined1 local_198;
  undefined8 ******local_190;
  undefined8 ******ppppppuStack_188;
  undefined8 ******local_180;
  undefined8 ******ppppppuStack_178;
  undefined8 ******local_170;
  undefined8 ******ppppppuStack_168;
  undefined8 ******local_160;
  undefined8 ******ppppppuStack_158;
  undefined8 ******local_150;
  undefined8 ******ppppppuStack_148;
  undefined1 local_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 ******local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 ******local_d0;
  undefined8 ******ppppppuStack_c8;
  undefined8 ******local_c0;
  undefined8 ******ppppppuStack_b8;
  undefined8 ******local_b0;
  undefined8 ******ppppppuStack_a8;
  undefined8 ******local_a0;
  undefined8 ******ppppppuStack_98;
  undefined2 local_90;
  
  pppppppuVar13 = (undefined8 *******)0x0;
  __s10Foundation4UUIDVMa();
  local_370 = pppppppuVar13[-1];
  local_378 = auStack_380 + -((long)local_370[8] + 0xfU & 0xfffffffffffffff0);
  pppppppuStack_368 = pppppppuVar13;
  _objc_msgSend(param_3,"storedStartTime");
  ppppppuVar41 = param_2;
  _objc_msgSend(param_3,"storedEndTime");
  ppppppuVar42 = ppppppuVar41;
  IVar14 = _objc_msgSend(param_3,"endFade");
  _objc_msgSend(param_3,"masterVolumeLevel");
  ppppppuVar20 = ppppppuVar42;
  local_310 = param_3;
  IVar15 = _objc_msgSend(param_3,"song");
  if (IVar15 == 0) {
    local_31c = 1;
  }
  else {
    IVar15 = _objc_msgSend(IVar15,"metadataVersion");
    local_31c = (undefined4)IVar15;
  }
  IVar15 = local_310;
  local_320 = 0;
  local_198 = 0;
  FUN_1002da058();
  IVar16 = _objc_msgSend(IVar15,"transitionContinuePad");
  local_324 = (undefined4)IVar16;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  IVar15 = _objc_msgSend(IVar15,"storedSections");
  if (IVar15 == 0) {
LAB_100273b24:
    puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    puVar17 = (undefined *)_objc_msgSend(IVar15,"array");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (puVar17,PTR___sypN_100a1e038 + 8);
    puVar21 = puVar17;
    FUN_1002d7d28();
    _swift_bridgeObjectRelease(puVar17);
    if (puVar21 == (undefined *)0x0) goto LAB_100273b24;
  }
  if ((ulong)puVar21 >> 0x3e == 0) {
    puVar17 = *(undefined **)(((ulong)puVar21 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar17 = (undefined *)((ulong)puVar21 & 0xffffffffffffff8);
    if ((long)puVar21 < 0) {
      puVar17 = puVar21;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  local_354 = (undefined4)IVar14;
  local_350 = param_1;
  if (puVar17 == (undefined *)0x0) {
    local_2e0 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    if ((long)puVar17 < 1) {
                    /* WARNING: Does not return */
      pcVar10 = (code *)SoftwareBreakpoint(1,0x100274114);
      (*pcVar10)();
    }
    puVar35 = (undefined *)0x0;
    local_2e0 = PTR___swiftEmptyArrayStorage_100a1e050;
    do {
      if (((ulong)puVar21 & 0xc000000000000001) != 0) {
        FUN_1000cbf0c(puVar35,puVar21);
      }
      FUN_10055a168(&local_138);
      puVar18 = local_2e0;
      _swift_isUniquelyReferenced_nonNull_native();
      if (((ulong)puVar18 & 1) == 0) {
        plVar1 = (long *)(local_2e0 + 0x10);
        local_2e0 = (undefined *)0x0;
        param_5 = (undefined8 *******)0x1;
        FUN_10078f970(0,*plVar1 + 1);
      }
      uVar29 = *(ulong *)(local_2e0 + 0x10);
      if (*(ulong *)(local_2e0 + 0x18) >> 1 <= uVar29) {
        puVar18 = (undefined *)(ulong)(1 < *(ulong *)(local_2e0 + 0x18));
        param_5 = (undefined8 *******)0x1;
        FUN_10078f970(puVar18,uVar29 + 1,1,local_2e0);
        local_2e0 = puVar18;
      }
      puVar35 = puVar35 + 1;
      *(ulong *)(local_2e0 + 0x10) = uVar29 + 1;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x38) = uStack_120;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x30) = local_128;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x48) = uStack_110;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x40) = local_118;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x28) = uStack_130;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x20) = local_138;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x80) = local_d8;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x68) = uStack_f0;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x60) = local_f8;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x78) = uStack_e0;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x70) = local_e8;
      *(undefined8 *)(local_2e0 + uVar29 * 0x68 + 0x58) = uStack_100;
      *(undefined8 *******)(local_2e0 + uVar29 * 0x68 + 0x50) = local_108;
      ppppppuVar20 = local_108;
    } while (puVar17 != puVar35);
  }
  _swift_bridgeObjectRelease(puVar21);
  puVar21 = local_2e0;
  _swift_bridgeObjectRetain_n(local_2e0,2);
  FUN_1002dc2dc();
  if ((ulong)puVar21 >> 0x3e == 0) {
    puVar17 = *(undefined **)(((ulong)puVar21 & 0xfffffffffffff8) + 0x10);
    if (puVar17 == (undefined *)0x0) goto LAB_100273e18;
LAB_100273cac:
    local_240 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    param_5 = (undefined8 *******)0x0;
    FUN_1001ccef4(0,(ulong)puVar17 & ((long)puVar17 >> 0x3f ^ 0xffffffffffffffffU));
    if ((long)puVar17 < 0) {
                    /* WARNING: Does not return */
      pcVar10 = (code *)SoftwareBreakpoint(1,0x100274118);
      (*pcVar10)();
    }
    lVar38 = 0;
    do {
      pppppppuVar13 = local_240;
      puVar35 = (undefined *)(lVar38 + 1);
      if (SCARRY8(lVar38,1)) {
                    /* WARNING: Does not return */
        pcVar10 = (code *)SoftwareBreakpoint(1,0x100273de8);
        (*pcVar10)();
      }
      if (((ulong)puVar21 & 0xc000000000000001) != 0) {
        FUN_1000cc338(lVar38,puVar21);
      }
      FUN_10055a4e8(&local_190);
      if (unaff_x21 != 0) {
        _swift_bridgeObjectRelease(puVar21);
        _swift_bridgeObjectRelease_n(local_2e0,3);
        _swift_release(pppppppuVar13);
        return;
      }
      ppppppuVar20 = pppppppuVar13[2];
      local_240 = pppppppuVar13;
      if ((undefined8 ******)((ulong)pppppppuVar13[3] >> 1) <= ppppppuVar20) {
        param_5 = (undefined8 *******)0x1;
        FUN_1001ccef4((undefined8 ******)0x1 < pppppppuVar13[3],
                      (undefined8 ******)((long)ppppppuVar20 + 1U));
      }
      local_240[2] = (undefined8 ******)((long)ppppppuVar20 + 1U);
      local_240[(long)ppppppuVar20 * 0xb + 5] = ppppppuStack_188;
      local_240[(long)ppppppuVar20 * 0xb + 4] = local_190;
      local_240[(long)ppppppuVar20 * 0xb + 7] = ppppppuStack_178;
      local_240[(long)ppppppuVar20 * 0xb + 6] = local_180;
      *(undefined1 *)(local_240 + (long)ppppppuVar20 * 0xb + 0xe) = local_140;
      local_240[(long)ppppppuVar20 * 0xb + 0xb] = ppppppuStack_158;
      local_240[(long)ppppppuVar20 * 0xb + 10] = local_160;
      local_240[(long)ppppppuVar20 * 0xb + 0xd] = ppppppuStack_148;
      local_240[(long)ppppppuVar20 * 0xb + 0xc] = local_150;
      local_240[(long)ppppppuVar20 * 0xb + 9] = ppppppuStack_168;
      local_240[(long)ppppppuVar20 * 0xb + 8] = local_170;
      lVar38 = lVar38 + 1;
      local_360 = local_240;
      ppppppuVar20 = local_170;
    } while (puVar35 != puVar17);
  }
  else {
    puVar17 = (undefined *)((ulong)puVar21 & 0xffffffffffffff8);
    if ((long)puVar21 < 0) {
      puVar17 = puVar21;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (puVar17 != (undefined *)0x0) goto LAB_100273cac;
LAB_100273e18:
    puVar17 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    local_360 = (undefined8 *******)puVar17;
  }
  _swift_bridgeObjectRelease(puVar21);
  _swift_bridgeObjectRetain(local_360);
  pcVar25 = "song";
  IVar14 = _objc_msgSend(local_310,"song");
  pppppppuVar13 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
  if (IVar14 == 0) {
    _swift_bridgeObjectRelease(local_2e0);
    puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    ppppppuVar28 = *(undefined8 *******)(puVar21 + 0x10);
    local_318 = (undefined8 *******)puVar21;
  }
  else {
    pcVar25 = "storedSongGenres";
    IVar14 = _objc_msgSend(IVar14,"storedSongGenres");
    if (IVar14 == 0) {
LAB_100273f1c:
      pppppppuVar33 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    }
    else {
      pppppppuVar19 = (undefined8 *******)_objc_msgSend(IVar14,"allObjects");
      pcVar25 = PTR___sypN_100a1e038 + 8;
      __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ();
      pppppppuVar33 = pppppppuVar19;
      FUN_1002d7d3c();
      _swift_bridgeObjectRelease(pppppppuVar19);
      if (pppppppuVar33 == (undefined8 *******)0x0) goto LAB_100273f1c;
      pppppppuVar19 = (undefined8 *******)((ulong)pppppppuVar33 & 0xffffffffffffff8);
      if ((ulong)pppppppuVar33 >> 0x3e == 0) {
        _swift_bridgeObjectRetain(pppppppuVar33);
      }
      else {
        pppppppuVar36 = pppppppuVar33;
        if (-1 < (long)pppppppuVar33) {
          pppppppuVar36 = pppppppuVar19;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        pppppppuVar19 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
        if (pppppppuVar36 == (undefined8 *******)0x0) {
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        }
        else {
          pppppppuVar19 = pppppppuVar36;
          FUN_10078d80c();
          _swift_bridgeObjectRetain_n(pppppppuVar33,2);
          pcVar25 = (char *)pppppppuVar36;
          pppppppuVar13 = pppppppuVar33;
          FUN_1005dadc4(pppppppuVar19 + 4);
          param_5 = pppppppuVar13;
          _swift_bridgeObjectRelease();
          if (pppppppuVar13 != pppppppuVar36) {
                    /* WARNING: Does not return */
            pcVar10 = (code *)SoftwareBreakpoint(1,0x100274f00);
            (*pcVar10)();
          }
          _swift_bridgeObjectRelease(pppppppuVar33);
          pppppppuVar13 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
        }
      }
      local_240 = pppppppuVar19;
      FUN_1003232e4(&local_240);
      if (unaff_x21 != 0) {
        _swift_release(local_240);
                    /* WARNING: Does not return */
        pcVar10 = (code *)SoftwareBreakpoint(1,0x100274f0c);
        (*pcVar10)();
      }
      _swift_bridgeObjectRelease(pppppppuVar33);
      pppppppuVar33 = local_240;
    }
    if ((ulong)pppppppuVar33 >> 0x3e == 0) {
      pppppppuVar19 = *(undefined8 ********)(((ulong)pppppppuVar33 & 0xfffffffffffff8) + 0x10);
      local_318 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    else {
      pppppppuVar19 = (undefined8 *******)((ulong)pppppppuVar33 & 0xffffffffffffff8);
      if ((long)pppppppuVar33 < 0) {
        pppppppuVar19 = pppppppuVar33;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      local_318 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    PTR___swiftEmptyArrayStorage_100a1e050 = (undefined *)local_318;
    if (pppppppuVar19 == (undefined8 *******)0x0) {
      _swift_retain(local_318);
      _swift_bridgeObjectRelease(local_2e0);
      _swift_bridgeObjectRelease(pppppppuVar33);
      ppppppuVar28 = local_318[2];
    }
    else {
      local_240 = pppppppuVar13;
      _swift_retain(pppppppuVar13);
      param_5 = (undefined8 *******)0x0;
      FUN_1001ccec8(0,(ulong)pppppppuVar19 & ((long)pppppppuVar19 >> 0x3f ^ 0xffffffffffffffffU));
      if ((long)pppppppuVar19 < 0) {
                    /* WARNING: Does not return */
        pcVar10 = (code *)SoftwareBreakpoint(1,0x100274e70);
        (*pcVar10)();
      }
      pppppppuVar13 = (undefined8 *******)0x0;
      local_308 = (undefined8 *******)((ulong)pppppppuVar33 & 0xc000000000000001);
      local_300 = pppppppuVar19;
      local_2f8 = pppppppuVar33;
      do {
        pppppppuVar33 = local_240;
        if (local_308 == (undefined8 *******)0x0) {
          pppppppuVar19 = (undefined8 *******)local_2f8[(long)((long)pppppppuVar13 + 4)];
          ppppppuVar28 = ppppppuVar20;
        }
        else {
          pppppppuVar19 = pppppppuVar13;
          FUN_1000cbf38();
          ppppppuVar28 = ppppppuVar20;
        }
        IVar14 = _objc_msgSend((ID)pppppppuVar19,"genreID");
        IVar15 = _objc_msgSend((ID)pppppppuVar19,"songID");
        pcVar25 = "storedUUID";
        ppppppuVar20 = (undefined8 ******)_objc_msgSend((ID)pppppppuVar19,"storedUUID");
        if (ppppppuVar20 == (undefined8 ******)0x0) {
          local_2f0 = (undefined8 ******)0x0;
          pcVar25 = (char *)0x0;
        }
        else {
          __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
          local_2f0 = ppppppuVar20;
        }
        _objc_msgSend((ID)pppppppuVar19,"volume");
        ppppppuVar20 = ppppppuVar28;
        IVar16 = _objc_msgSend((ID)pppppppuVar19,"muted");
        ppppppuVar24 = pppppppuVar33[2];
        local_240 = pppppppuVar33;
        if ((undefined8 ******)((ulong)pppppppuVar33[3] >> 1) <= ppppppuVar24) {
          param_5 = (undefined8 *******)0x1;
          FUN_1001ccec8((undefined8 ******)0x1 < pppppppuVar33[3],
                        (undefined8 ******)((long)ppppppuVar24 + 1U));
        }
        pppppppuVar19 = local_240;
        pppppppuVar33 = local_2f8;
        pppppppuVar13 = (undefined8 *******)((long)pppppppuVar13 + 1);
        local_240[2] = (undefined8 ******)((long)ppppppuVar24 + 1U);
        local_240[(long)ppppppuVar24 * 6 + 4] = (undefined8 ******)(long)(int)IVar14;
        local_240[(long)ppppppuVar24 * 6 + 5] = (undefined8 ******)(long)(int)IVar15;
        local_240[(long)ppppppuVar24 * 6 + 6] = local_2f0;
        local_240[(long)ppppppuVar24 * 6 + 7] = (undefined8 ******)pcVar25;
        local_240[(long)ppppppuVar24 * 6 + 8] = ppppppuVar28;
        *(char *)(local_240 + (long)ppppppuVar24 * 6 + 9) = (char)IVar16;
      } while (local_300 != pppppppuVar13);
      pcVar25 = (char *)local_2f8;
      _swift_bridgeObjectRelease(local_2e0);
      _swift_bridgeObjectRelease(pppppppuVar33);
      ppppppuVar28 = pppppppuVar19[2];
      pppppppuVar13 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
      local_318 = pppppppuVar19;
    }
  }
  if (ppppppuVar28 == (undefined8 ******)0x0) {
    _swift_bridgeObjectRelease(local_318);
    local_318 = (undefined8 *******)0x0;
  }
  lVar38 = DAT_100b01660;
  if (DAT_100b01660 == 0) {
    _swift_bridgeObjectRetain(local_318);
    pppppppuVar33 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    FUN_1003d4908();
    uVar40 = SUB84(param_5,0);
    lVar38 = DAT_100b01660;
    if (DAT_100b01660 != 0) goto LAB_1002741bc;
LAB_100274850:
    ppppppuVar28 = pppppppuVar33[2];
  }
  else {
    _swift_bridgeObjectRetain(local_318);
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_1002741bc:
    lVar8 = _TtC8Playback11AudioDevice::privateMixerBuses;
    uVar29 = *(ulong *)(lVar38 + _TtC8Playback11AudioDevice::privateMixerBuses);
    if (uVar29 >> 0x3e == 0) {
      uVar32 = *(ulong *)((uVar29 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar32 = uVar29 & 0xffffffffffffff8;
      if ((long)uVar29 < 0) {
        uVar32 = uVar29;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar32 == 0) {
      puVar21 = (undefined *)0x2;
      FUN_1003d0d94();
      if (unaff_x21 != 0) {
        _swift_errorRelease(unaff_x21);
        puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain();
        unaff_x21 = 0;
      }
      uVar30 = *(undefined8 *)(lVar38 + lVar8);
      *(undefined **)(lVar38 + lVar8) = puVar21;
      _swift_bridgeObjectRelease(uVar30);
    }
    pppppppuVar33 = *(undefined8 ********)(lVar38 + lVar8);
    _swift_bridgeObjectRetain(pppppppuVar33);
    uVar40 = SUB84(param_5,0);
    if ((ulong)pppppppuVar33 >> 0x3e == 0) {
      pppppppuVar19 = *(undefined8 ********)(((ulong)pppppppuVar33 & 0xfffffffffffff8) + 0x10);
    }
    else {
      pppppppuVar19 = (undefined8 *******)((ulong)pppppppuVar33 & 0xffffffffffffff8);
      if ((long)pppppppuVar33 < 0) {
        pppppppuVar19 = pppppppuVar33;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      uVar40 = SUB84(param_5,0);
    }
    if (pppppppuVar19 != (undefined8 *******)0x0) {
      pppppppuVar36 = (undefined8 *******)0x0;
      local_340 = (ulong)pppppppuVar33 & 0xc000000000000001;
      local_2f0 = (undefined8 ******)((ulong)pppppppuVar33 & 0xffffffffffffff8);
      local_2f8 = pppppppuVar33 + 4;
      uVar29 = local_340;
      local_338 = pppppppuVar19;
      local_330 = pppppppuVar33;
      do {
        while( true ) {
          if (uVar29 == 0) {
            if (local_2f0[2] <= pppppppuVar36) {
                    /* WARNING: Does not return */
              pcVar10 = (code *)SoftwareBreakpoint(1,0x100274b2c);
              (*pcVar10)();
            }
            pppppppuVar22 = (undefined8 *******)local_2f8[(long)pppppppuVar36];
          }
          else {
            pppppppuVar22 = pppppppuVar36;
            FUN_1000cc184(pppppppuVar36,pppppppuVar33);
          }
          bVar11 = SCARRY8((long)pppppppuVar36,1);
          pppppppuVar36 = (undefined8 *******)((long)pppppppuVar36 + 1);
          if (bVar11) {
                    /* WARNING: Does not return */
            pcVar10 = (code *)SoftwareBreakpoint(1,0x100274b20);
            (*pcVar10)();
          }
          pcVar25 = "type";
          IVar14 = _objc_msgSend((ID)pppppppuVar22,"type");
          if (IVar14 == 0) {
            uVar32 = 0;
          }
          else {
            pcVar25 = "integerValue";
            uVar32 = _objc_msgSend(IVar14,"integerValue");
          }
          FUN_10055ee18();
          uVar27 = (uint)uVar32 & 0xff;
          if ((0x14 < uVar27) ||
             (((1 << (ulong)((uint)uVar32 & 0x1f) & 0x21801U) == 0 && (uVar27 != 0x14)))) break;
LAB_100274270:
          uVar40 = SUB84(param_5,0);
          if (pppppppuVar36 == pppppppuVar19) goto LAB_100274848;
        }
        pcVar25 = "storedBuses";
        IVar14 = _objc_msgSend(local_310,"storedBuses");
        if (IVar14 == 0) goto LAB_100274270;
        local_308 = pppppppuVar13;
        local_300 = pppppppuVar22;
        IVar14 = _objc_msgSend(IVar14,"array");
        __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                  (IVar14,PTR___sypN_100a1e038 + 8);
        pcVar25 = *(char **)(IVar14 + 0x10);
        local_2d0 = (undefined8 ******)PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain();
        param_5 = (undefined8 *******)0x0;
        FUN_1001cc5c4(0);
        IVar16 = IVar14;
        IVar15 = local_348;
        ppppppuVar28 = local_2d0;
        for (lVar38 = *(long *)(IVar14 + 0x10); local_348 = IVar16, local_2d0 = ppppppuVar28,
            lVar38 != 0; lVar38 = lVar38 + -1) {
          IVar14 = IVar14 + 0x20;
          FUN_10003b4f8(IVar14,&local_240);
          FUN_100386198(0);
          iVar12 = (int)&local_2d8;
          pcVar25 = (char *)&local_240;
          param_5 = (undefined8 *******)(PTR___sypN_100a1e038 + 8);
          _swift_dynamicCast();
          ppppuVar31 = local_2d8;
          if (iVar12 == 0) {
            _swift_release(ppppppuVar28);
            local_2d8 = (undefined8 ****)0x0;
            _swift_bridgeObjectRelease(local_348);
            pppppppuVar13 = local_308;
            goto LAB_1002747c4;
          }
          ppppuVar23 = ppppppuVar28[2];
          local_2d0 = ppppppuVar28;
          if ((undefined8 ****)((ulong)ppppppuVar28[3] >> 1) <= ppppuVar23) {
            param_5 = (undefined8 *******)0x1;
            pcVar25 = (char *)((long)ppppuVar23 + 1U);
            FUN_1001cc5c4((undefined8 ****)0x1 < ppppppuVar28[3]);
          }
          local_2d0[2] = (undefined8 *******)((long)ppppuVar23 + 1U);
          local_2d0[(long)ppppuVar23 + 4] = (undefined8 *****)ppppuVar31;
          IVar16 = local_348;
          IVar15 = local_348;
          ppppppuVar28 = local_2d0;
        }
        IVar14 = local_348;
        local_348 = IVar15;
        _swift_bridgeObjectRelease(IVar14);
        if (((long)ppppppuVar28 < 0) || (((ulong)ppppppuVar28 >> 0x3e & 1) != 0)) {
          pppppuVar39 = ppppppuVar28;
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (pppppuVar39 != (undefined8 *****)0x0) goto LAB_1002744ac;
LAB_1002747b4:
          _swift_release(ppppppuVar28);
          pppppppuVar13 = local_308;
        }
        else {
          pppppuVar39 = ppppppuVar28[2];
          if (pppppuVar39 == (undefined8 *****)0x0) goto LAB_1002747b4;
LAB_1002744ac:
          _swift_retain(ppppppuVar28);
          lVar38 = 4;
          do {
            ppppuVar31 = (undefined8 ****)(lVar38 - 4);
            if (((ulong)ppppppuVar28 & 0xc000000000000001) == 0) {
              ppppuVar23 = ppppppuVar28[lVar38];
            }
            else {
              ppppuVar23 = ppppuVar31;
              FUN_1000cce70(ppppuVar31,ppppppuVar28);
            }
            pppppuVar2 = (undefined8 *****)(lVar38 - 3);
            if (SCARRY8((long)ppppuVar31,1)) {
                    /* WARNING: Does not return */
              pcVar10 = (code *)SoftwareBreakpoint(1,0x100274b24);
              (*pcVar10)();
            }
            IVar14 = _objc_msgSend((ID)ppppuVar23,"id");
            if ((long)(int)IVar14 == (uVar32 & 0xff)) {
              _swift_release_n(ppppppuVar28,2);
              if (DAT_100adea10 != -1) {
                _swift_once(&DAT_100adea10,FUN_1001709a4);
              }
              uVar29 = DAT_100b757a8;
              FUN_1001714e4();
              pppppppuVar13 = local_308;
              if ((uVar29 & 1) == 0) {
                IVar14 = _objc_msgSend((ID)local_300,"volume");
                if (IVar14 == 0) {
                  ppppppuVar28 = (undefined8 ******)0x0;
                }
                else {
                  _objc_msgSend(IVar14,"doubleValue");
                  ppppppuVar28 = ppppppuVar20;
                }
              }
              else {
                uVar29 = 0x15;
                thunk_FUN_1002db810(0x15,PTR___swiftEmptyArrayStorage_100a1e050);
                if ((uVar29 & 1) == 0) {
                  if (DAT_100ae0030 != -1) {
                    _swift_once(&DAT_100ae0030,FUN_1008174c0);
                  }
                  uVar29 = 1;
                  FUN_100819fe0();
                  ppppppuVar28 = (undefined8 ******)0x3ff0000000000000;
                  if ((uVar29 & 1) == 0) goto LAB_100274604;
                }
                _objc_msgSend((ID)ppppuVar23,"volume");
                ppppppuVar28 = ppppppuVar20;
              }
LAB_100274604:
              uVar29 = DAT_100b757a8;
              FUN_1001714e4();
              pppppppuVar33 = local_300;
              if ((uVar29 & 1) == 0) {
                IVar14 = _objc_msgSend((ID)local_300,"isMuted");
                if (IVar14 == 0) {
                  local_348 = local_348 & 0xffffffff00000000;
                }
                else {
                  IVar14 = _objc_msgSend(IVar14,"boolValue");
                  local_348 = CONCAT44(local_348._4_4_,(int)IVar14);
                }
              }
              else {
                IVar14 = _objc_msgSend((ID)ppppuVar23,"muted");
                local_348 = CONCAT44(local_348._4_4_,(int)IVar14);
                pppppppuVar33 = local_300;
              }
              pcVar26 = "type";
              IVar14 = _objc_msgSend((ID)pppppppuVar33,"type");
              if (IVar14 == 0) {
                uVar27 = 0;
              }
              else {
                pcVar26 = "integerValue";
                IVar14 = _objc_msgSend(IVar14,"integerValue");
                uVar27 = (uint)IVar14;
              }
              FUN_10055ee18();
              puVar9 = local_378;
              uVar4 = 0;
              if ((uVar27 & 0xff) != 0x14) {
                uVar4 = uVar27;
              }
              puVar3 = (undefined8 *)((long)ppppuVar23 + _TtC8Playback7SongBus::storedUUID);
              pppppppuVar33 = (undefined8 *******)puVar3[1];
              if (pppppppuVar33 == (undefined8 *******)0x0) {
                __s10Foundation4UUIDVACycfC(local_378);
                __s10Foundation4UUIDV10uuidStringSSvg();
                pcVar25 = (char *)pppppppuStack_368;
                (*(code *)local_370[1])(puVar9);
                uVar30 = puVar3[1];
                *puVar3 = pppppppuVar33;
                puVar3[1] = pcVar26;
                _swift_bridgeObjectRetain(pcVar26);
                _swift_bridgeObjectRelease(uVar30);
                pppppppuVar19 = (undefined8 *******)0x0;
                pppppppuVar22 = pppppppuVar33;
              }
              else {
                pppppppuVar19 = pppppppuVar33;
                pcVar25 = pcVar26;
                pppppppuVar22 = (undefined8 *******)*puVar3;
                pcVar26 = (char *)pppppppuVar33;
              }
              _swift_bridgeObjectRetain(pppppppuVar19);
              pppppppuVar33 = pppppppuVar13;
              _swift_isUniquelyReferenced_nonNull_native();
              if (((ulong)pppppppuVar33 & 1) == 0) {
                pcVar25 = (char *)((long)pppppppuVar13[2] + 1);
                pppppppuVar13 = (undefined8 *******)0x0;
                param_5 = (undefined8 *******)0x1;
                FUN_10078f854();
              }
              ppppppuVar24 = pppppppuVar13[2];
              if ((undefined8 ******)((ulong)pppppppuVar13[3] >> 1) <= ppppppuVar24) {
                pppppppuVar13 =
                     (undefined8 *******)(ulong)((undefined8 ******)0x1 < pppppppuVar13[3]);
                param_5 = (undefined8 *******)0x1;
                pcVar25 = (char *)((long)ppppppuVar24 + 1U);
                FUN_10078f854();
              }
              pppppppuVar13[2] = (undefined8 *******)((long)ppppppuVar24 + 1U);
              pppppppuVar13[(long)ppppppuVar24 * 5 + 4] = (undefined8 ******)((ulong)uVar4 & 0xff);
              pppppppuVar13[(long)ppppppuVar24 * 5 + 5] = ppppppuVar28;
              *(char *)(pppppppuVar13 + (long)ppppppuVar24 * 5 + 6) = (char)local_348;
              pppppppuVar13[(long)ppppppuVar24 * 5 + 7] = pppppppuVar22;
              pppppppuVar13[(long)ppppppuVar24 * 5 + 8] = (undefined8 ******)pcVar26;
              goto LAB_1002747c4;
            }
            lVar38 = lVar38 + 1;
          } while (pppppuVar2 != pppppuVar39);
          pcVar25 = (char *)0x2;
          _swift_release_n(ppppppuVar28);
          pppppppuVar13 = local_308;
        }
LAB_1002747c4:
        uVar40 = SUB84(param_5,0);
        pppppppuVar33 = local_330;
        pppppppuVar19 = local_338;
        uVar29 = local_340;
      } while (pppppppuVar36 != local_338);
LAB_100274848:
      _swift_bridgeObjectRelease(pppppppuVar33);
      pppppppuVar33 = pppppppuVar13;
      goto LAB_100274850;
    }
    _swift_bridgeObjectRelease(pppppppuVar33);
    ppppppuVar28 = *(undefined8 *******)(PTR___swiftEmptyArrayStorage_100a1e050 + 0x10);
    pppppppuVar33 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
  }
  if (ppppppuVar28 == (undefined8 ******)0x0) {
    _swift_bridgeObjectRelease(pppppppuVar33);
    pppppppuVar33 = (undefined8 *******)0x0;
  }
  pppppppuVar19 = pppppppuVar33;
  _swift_bridgeObjectRetain();
  FUN_1002e1f58();
  pppppppuVar13 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
  uVar29 = 0;
  thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
  lVar38 = DAT_100ae0030;
  local_2f8 = (undefined8 *******)pcVar25;
  if ((uVar29 & 1) == 0) {
    _swift_bridgeObjectRetain(pcVar25);
    if (lVar38 != -1) {
      _swift_once(&DAT_100ae0030,FUN_1008174c0);
    }
    uVar29 = 0;
    FUN_100819fe0();
    if ((uVar29 & 1) == 0) {
      uVar37 = 0;
      IVar14 = local_310;
      goto LAB_1002748f0;
    }
  }
  else {
    _swift_bridgeObjectRetain(pcVar25);
  }
  IVar14 = local_310;
  IVar15 = _objc_msgSend(local_310,"storedSMPTEEnabled");
  uVar37 = (undefined4)IVar15;
LAB_1002748f0:
  _objc_msgSend(IVar14,"smpteStartTime");
  local_1a0 = 0;
  ppppppuVar28 = ppppppuVar20;
  IVar14 = _objc_msgSend(IVar14,"storedSMPTETimelineLocation");
  if (IVar14 == 0) {
    FUN_1002e4b7c();
  }
  else {
    _objc_msgSend(IVar14,"doubleValue");
  }
  local_1a8 = 0;
  ppppppuVar24 = (undefined8 ******)0x1;
  FUN_1002e1174();
  if ((ulong)ppppppuVar24 >> 0x3e == 0) {
    ppppppuVar34 = *(undefined8 *******)(((ulong)ppppppuVar24 & 0xfffffffffffff8) + 0x10);
  }
  else {
    ppppppuVar34 = (undefined8 ******)((ulong)ppppppuVar24 & 0xffffffffffffff8);
    if ((long)ppppppuVar24 < 0) {
      ppppppuVar34 = ppppppuVar24;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  local_300 = (undefined8 *******)CONCAT44(local_300._4_4_,uVar37);
  if (ppppppuVar34 == (undefined8 ******)0x0) {
    _swift_retain(pppppppuVar13);
    _swift_bridgeObjectRelease(ppppppuVar24);
  }
  else {
    local_240 = pppppppuVar13;
    _swift_retain(pppppppuVar13);
    FUN_1001cce9c(0,(ulong)ppppppuVar34 & ((long)ppppppuVar34 >> 0x3f ^ 0xffffffffffffffffU),0);
    if ((long)ppppppuVar34 < 0) {
                    /* WARNING: Does not return */
      pcVar10 = (code *)SoftwareBreakpoint(1,0x100274e54);
      (*pcVar10)();
    }
    local_338 = (undefined8 *******)CONCAT44(local_338._4_4_,uVar40);
    lVar38 = 0;
    local_330 = pppppppuVar19;
    local_308 = pppppppuVar33;
    local_2f0 = ppppppuVar34;
    do {
      pppppppuVar13 = local_240;
      ppppppuVar34 = (undefined8 ******)(lVar38 + 1);
      if (SCARRY8(lVar38,1)) {
                    /* WARNING: Does not return */
        pcVar10 = (code *)SoftwareBreakpoint(1,0x100274b28);
        (*pcVar10)();
      }
      if (((ulong)ppppppuVar24 & 0xc000000000000001) != 0) {
        FUN_1000cc5b8(lVar38,ppppppuVar24);
      }
      FUN_1007cd924(&local_d0);
      if (unaff_x21 != 0) {
        _swift_bridgeObjectRelease(ppppppuVar24);
        _swift_bridgeObjectRelease_n(local_2e0,2);
        _swift_bridgeObjectRelease_n(local_360,2);
        pppppppuVar33 = local_308;
        _swift_bridgeObjectRelease(local_308);
        _swift_release(pppppppuVar13);
        pppppppuVar19 = local_2f8;
        _swift_bridgeObjectRelease(local_2f8);
        pppppppuVar13 = local_318;
        _swift_bridgeObjectRelease(local_318);
        _swift_bridgeObjectRelease(pppppppuVar19);
        _swift_bridgeObjectRelease(pppppppuVar33);
        _swift_bridgeObjectRelease(pppppppuVar13);
        return;
      }
      ppppppuVar5 = pppppppuVar13[2];
      local_240 = pppppppuVar13;
      if ((undefined8 ******)((ulong)pppppppuVar13[3] >> 1) <= ppppppuVar5) {
        FUN_1001cce9c((undefined8 ******)0x1 < pppppppuVar13[3],
                      (undefined8 ******)((long)ppppppuVar5 + 1U),1);
      }
      pppppppuVar13 = local_240;
      local_240[2] = (undefined8 ******)((long)ppppppuVar5 + 1U);
      local_240[(long)ppppppuVar5 * 9 + 5] = ppppppuStack_c8;
      local_240[(long)ppppppuVar5 * 9 + 4] = local_d0;
      *(undefined2 *)(local_240 + (long)ppppppuVar5 * 9 + 0xc) = local_90;
      local_240[(long)ppppppuVar5 * 9 + 9] = ppppppuStack_a8;
      local_240[(long)ppppppuVar5 * 9 + 8] = local_b0;
      local_240[(long)ppppppuVar5 * 9 + 0xb] = ppppppuStack_98;
      local_240[(long)ppppppuVar5 * 9 + 10] = local_a0;
      local_240[(long)ppppppuVar5 * 9 + 7] = ppppppuStack_b8;
      local_240[(long)ppppppuVar5 * 9 + 6] = local_c0;
      lVar38 = lVar38 + 1;
    } while (ppppppuVar34 != local_2f0);
    _swift_bridgeObjectRelease(ppppppuVar24);
    pppppppuVar33 = local_308;
    pppppppuVar19 = local_330;
    uVar40 = local_338._0_4_;
    uVar37 = (undefined4)local_300;
  }
  uVar29 = (ulong)pppppppuVar19 & 0xffff0001ffffffff;
  _swift_bridgeObjectRetain(pppppppuVar13);
  IVar14 = _objc_msgSend(local_310,"song");
  local_2f0 = (undefined8 ******)(CONCAT44(local_2f0._4_4_,uVar40) & 0xffffffff00010101);
  if (IVar14 == 0) {
    uVar27 = 2;
  }
  else {
    IVar15 = _objc_msgSend(IVar14,"modularClickLengthValue");
    if ((int)IVar15 == 0) {
      if (DAT_100adea10 != -1) {
        _swift_once(&DAT_100adea10,FUN_1001709a4);
      }
      uVar32 = DAT_100b757a8;
      FUN_1001718ec();
      uVar27 = (uint)uVar32 & 1;
    }
    else {
      IVar14 = _objc_msgSend(IVar14,"modularClickLengthValue");
      uVar27 = (uint)((int)IVar14 == 4);
    }
  }
  pppppppuVar22 = local_2f8;
  pppppppuVar36 = local_318;
  pppppppuVar19 = local_360;
  local_330 = (undefined8 *******)CONCAT44(local_330._4_4_,uVar27);
  uVar6 = (undefined1)local_354;
  local_2b0 = (undefined1)local_320;
  uStack_2af = (undefined1)local_324;
  uStack_2ac = local_31c;
  uStack_2a8 = 0;
  uStack_2a7 = (undefined1)uVar37;
  local_298 = 0;
  uStack_288 = 0;
  local_280 = local_2e0;
  pppppppuStack_278 = local_360;
  local_270 = local_318;
  uStack_258 = (undefined4)uVar29;
  local_254 = (undefined4)(uVar29 >> 0x20);
  uStack_250 = SUB84(local_2f8,0);
  uStack_24c = (undefined4)((ulong)local_2f8 >> 0x20);
  local_310 = CONCAT44(local_310._4_4_,(uint)local_2f0 >> 0x10);
  uStack_246 = (undefined1)((ulong)local_2f0 >> 0x10);
  uVar7 = SUB82(local_2f0,0);
  uStack_245 = (undefined1)uVar27;
  local_308 = (undefined8 *******)uVar29;
  local_2d0 = param_2;
  ppppppuStack_2c8 = ppppppuVar41;
  local_2c0 = uVar6;
  local_2b8 = ppppppuVar42;
  local_2a0 = ppppppuVar20;
  local_290 = ppppppuVar28;
  pppppppuStack_268 = pppppppuVar33;
  local_260 = pppppppuVar13;
  uStack_248 = uVar7;
  FUN_1002756fc(&local_2d0);
  _swift_bridgeObjectRelease(local_2e0);
  _swift_bridgeObjectRelease(pppppppuVar19);
  _swift_bridgeObjectRelease(pppppppuVar33);
  _swift_bridgeObjectRelease(pppppppuVar13);
  _swift_bridgeObjectRelease(pppppppuVar22);
  _swift_bridgeObjectRelease(pppppppuVar36);
  local_220 = (undefined1)local_320;
  local_21f = (undefined1)local_324;
  local_21c = local_31c;
  local_218 = local_198;
  local_217 = SUB81(local_300,0);
  local_216 = local_19e;
  local_212 = local_19a;
  local_208 = local_1a0;
  local_1f8 = local_1a8;
  local_1f0 = local_2e0;
  pppppppuStack_1e8 = pppppppuVar19;
  local_1e0 = pppppppuVar36;
  uStack_1c8 = (ulong)local_308;
  local_1c0 = pppppppuVar22;
  local_1b6 = (undefined1)local_310;
  local_1b5 = SUB81(local_330,0);
  local_240 = (undefined8 *******)param_2;
  ppppppuStack_238 = ppppppuVar41;
  local_230 = uVar6;
  local_228 = ppppppuVar42;
  local_210 = ppppppuVar20;
  local_200 = ppppppuVar28;
  pppppppuStack_1d8 = pppppppuVar33;
  local_1d0 = pppppppuVar13;
  local_1b8 = uVar7;
  FUN_100275784(&local_240);
  local_350[0xd] = pppppppuStack_268;
  local_350[0xc] = local_270;
  local_350[0xf] = CONCAT44(local_254,uStack_258);
  local_350[0xe] = local_260;
  *(ulong *)((long)local_350 + 0x84) =
       CONCAT17(uStack_245,CONCAT16(uStack_246,CONCAT24(uStack_248,uStack_24c)));
  *(ulong *)((long)local_350 + 0x7c) = CONCAT44(uStack_250,local_254);
  local_350[5] = CONCAT62(uStack_2a6,CONCAT11(uStack_2a7,uStack_2a8));
  local_350[4] = CONCAT44(uStack_2ac,CONCAT22(uStack_2ae,CONCAT11(uStack_2af,local_2b0)));
  local_350[7] = CONCAT71(uStack_297,local_298);
  local_350[6] = local_2a0;
  local_350[9] = CONCAT71(uStack_287,uStack_288);
  local_350[8] = local_290;
  local_350[0xb] = pppppppuStack_278;
  local_350[10] = local_280;
  local_350[1] = ppppppuStack_2c8;
  *local_350 = local_2d0;
  local_350[3] = local_2b8;
  local_350[2] = CONCAT71(uStack_2bf,local_2c0);
  return;
}

// ==== 1002b1db0 _TtC8Playback42StackMenuPlaybackRemoteTableViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback42StackMenuPlaybackRemoteTableViewController::
viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback42StackMenuPlaybackRemoteTableViewController *this,ID param_1,SEL param_2,
          CGSize param_3,ID param_4)

{
  class_t *pcVar1;
  double dVar2;
  objc_super local_50;
  
  dVar2 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  _swift_unknownObjectRetain(dVar2);
  _objc_msgSendSuper2(&local_50,"viewWillTransitionToSize:withTransitionCoordinator:",dVar2);
  FUN_1002b1ba8();
  _swift_unknownObjectRelease(dVar2);
  return;
}

// ==== 1002c71a8 FUN_1002c71a8 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_1002c71a8(undefined8 param_1)

{
  undefined1 uVar1;
  ulong uVar2;
  undefined8 uVar3;
  ID IVar4;
  ID IVar5;
  long lVar6;
  long unaff_x20;
  long lVar7;
  ID IVar8;
  long lVar9;
  ID IVar10;
  long lVar11;
  long lVar12;
  undefined1 local_80 [16];
  
  lVar6 = *(long *)(unaff_x20 + 0x18);
  if (lVar6 != 0) {
    lVar7 = *(long *)(lVar6 + 0x18);
    if (lVar7 != 0) {
      _swift_retain(lVar7);
      FUN_100647944();
      _swift_release(lVar7);
      lVar6 = *(long *)(unaff_x20 + 0x18);
      if (lVar6 == 0) goto LAB_1002c7218;
    }
    lVar6 = *(long *)(lVar6 + 0x20);
    if (lVar6 != 0) {
      _swift_retain(lVar6);
      FUN_100647944();
      _swift_release(lVar6);
    }
  }
LAB_1002c7218:
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar2 = DAT_100b757a8;
  FUN_100171514();
  if (((uVar2 & 1) != 0) && (lVar6 = *(long *)(unaff_x20 + 0x18), lVar6 != 0)) {
    _swift_retain(lVar6);
    FUN_100732ddc();
    _swift_release(lVar6);
  }
  uVar3 = *(undefined8 *)(unaff_x20 + 0x20);
  *(undefined8 *)(unaff_x20 + 0x20) = *(undefined8 *)(unaff_x20 + 0x28);
  _swift_retain();
  _swift_release(uVar3);
  lVar6 = *(long *)(unaff_x20 + 0x18);
  if (lVar6 != 0) {
    uVar3 = *(undefined8 *)(lVar6 + 0x18);
    *(undefined8 *)(lVar6 + 0x18) = *(undefined8 *)(lVar6 + 0x20);
    _swift_retain();
    _swift_release(uVar3);
  }
  uVar3 = *(undefined8 *)(unaff_x20 + 0x28);
  *(undefined8 *)(unaff_x20 + 0x28) = 0;
  _swift_release(uVar3);
  lVar6 = *(long *)(unaff_x20 + 0x18);
  if (lVar6 != 0) {
    uVar3 = *(undefined8 *)(lVar6 + 0x20);
    *(undefined8 *)(lVar6 + 0x20) = 0;
    _swift_release(uVar3);
  }
  lVar7 = _TtC8Playback9Sequencer::song;
  lVar6 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar9 = *(long *)(unaff_x20 + 0x20);
  if ((lVar9 == 0) ||
     ((*(byte *)(lVar9 + _TtC8Playback9Sequencer::smpteBeganDuringTransition) & 1) != 0))
  goto LAB_1002c75e0;
  IVar8 = *(ID *)(lVar9 + _TtC8Playback9Sequencer::song);
  IVar10 = *(ID *)(IVar8 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar10 == 0) {
    _swift_retain(lVar9);
    IVar4 = _objc_msgSend(IVar8,"workingCopyArrangementID");
    if (IVar4 != 0) {
      IVar5 = IVar4;
      FUN_10032ee88();
      IVar10 = IVar5;
      FUN_1005e3b94(IVar5,IVar4);
      _swift_bridgeObjectRelease(IVar5);
      if (IVar10 != 0) {
        *(ID *)(IVar8 + lVar6) = IVar10;
        lVar6 = *(long *)(unaff_x20 + 0x18);
        lVar12 = DAT_100adef08;
        goto joined_r0x0001002c749c;
      }
    }
    _swift_release(lVar9);
    goto LAB_1002c75e0;
  }
  _swift_retain(lVar9);
  lVar6 = *(long *)(unaff_x20 + 0x18);
  lVar12 = DAT_100adef08;
joined_r0x0001002c749c:
  DAT_100adef08 = lVar12;
  if (lVar6 == 0) {
LAB_1002c75d4:
    _swift_release(lVar9);
  }
  else {
    _swift_retain(lVar6);
    if (lVar12 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar12 = _TtC8Playback9Sequencer::uuid;
    lVar11 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar11 != 0) {
      _swift_retain(lVar9);
      _swift_retain(lVar11);
      uVar2 = lVar11 + lVar12;
      __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar2,lVar9 + lVar12);
      _swift_release(lVar11);
      _swift_release(lVar9);
      if ((uVar2 & 1) != 0) {
        lVar12 = *(long *)(lVar6 + 0x48);
        _swift_retain(lVar12);
        _swift_release(lVar6);
        if (lVar12 == 0) goto LAB_1002c75d4;
        uVar2 = 0;
        thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
        if ((uVar2 & 1) == 0) {
          if (DAT_100ae0030 != -1) {
            _swift_once(&DAT_100ae0030,FUN_1008174c0);
          }
          uVar2 = 0;
          FUN_100819fe0();
          if ((uVar2 & 1) != 0) goto LAB_1002c73c4;
LAB_1002c74d8:
          uVar1 = 0;
        }
        else {
LAB_1002c73c4:
          IVar8 = _objc_msgSend(IVar10,"storedSMPTEEnabled");
          if ((int)IVar8 == 0) goto LAB_1002c74d8;
          IVar8 = _objc_msgSend(IVar10,"storedSMPTETimelineLocation");
          if (IVar8 == 0) {
            FUN_1002e4b7c();
          }
          else {
            _objc_msgSend(IVar8,"doubleValue");
          }
          uVar3 = param_1;
          _objc_msgSend(IVar10,"smpteStartTime");
          FUN_1000cfba4(param_1);
          FUN_1000cfbac(uVar3);
          IVar10 = *(ID *)(lVar9 + lVar7);
          uVar2 = 0;
          thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
          if ((uVar2 & 1) == 0) {
            if (DAT_100ae0030 != -1) {
              _swift_once(&DAT_100ae0030,FUN_1008174c0);
            }
            uVar2 = 0;
            FUN_100819fe0();
            if ((uVar2 & 1) != 0) goto LAB_1002c754c;
LAB_1002c7560:
            uVar3 = *(undefined8 *)(lVar9 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
            _swift_retain(uVar3);
            __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                      (local_80,FUN_1001b4e10,uVar3,PTR___sSdN_100a1dd60);
            _swift_release(uVar3);
          }
          else {
LAB_1002c754c:
            IVar10 = _objc_msgSend(IVar10,"storedSMPTEFollowsDefaultArrangement");
            if ((IVar10 & 1) != 0) goto LAB_1002c7560;
            FUN_1004f240c();
          }
          FUN_1000cfd9c();
          uVar1 = *(undefined1 *)(lVar9 + _TtC8Playback9Sequencer::privatePlayState);
        }
        FUN_1000cfac8(uVar1);
        _swift_release(lVar9);
        lVar9 = lVar12;
        goto LAB_1002c75d4;
      }
    }
    _swift_release(lVar9);
    _swift_release(lVar6);
  }
LAB_1002c75e0:
  IVar10 = _objc_msgSend(*(ID *)(unaff_x20 + 0x10),"isRunning");
  if ((IVar10 & 1) == 0) {
    FUN_1002c4030(1);
  }
  return;
}

// ==== 1002da058 FUN_1002da058 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1002da058(void)

{
  code *pcVar1;
  uint uVar2;
  ID IVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ID unaff_x20;
  
  IVar3 = _objc_msgSend(unaff_x20,"storedTransition");
  uVar2 = (uint)IVar3;
  FUN_100142b7c();
  if ((((uVar2 & 0xff) != 4) && (IVar3 = _objc_msgSend(unaff_x20,"song"), IVar3 != 0)) &&
     (uVar4 = _objc_msgSend(IVar3,"setlist"), uVar4 != 0)) {
    FUN_1004a6154();
    if (uVar4 >> 0x3e == 0) {
      uVar5 = *(ulong *)((uVar4 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar5 = uVar4 & 0xffffffffffffff8;
      if ((long)uVar4 < 0) {
        uVar5 = uVar4;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar5 == 0) {
      _swift_bridgeObjectRelease(uVar4);
    }
    else {
      uVar6 = uVar5 - 1;
      if (SBORROW8(uVar5,1)) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1,0x1002da1c8);
        (*pcVar1)();
      }
      if ((uVar4 & 0xc000000000000001) == 0) {
        if ((long)uVar6 < 0) {
                    /* WARNING: Does not return */
          pcVar1 = (code *)SoftwareBreakpoint(1,0x1002da1d8);
          (*pcVar1)();
        }
        if (*(ulong *)((uVar4 & 0xfffffffffffff8) + 0x10) <= uVar6) {
                    /* WARNING: Does not return */
          pcVar1 = (code *)SoftwareBreakpoint(1,0x1002da1dc);
          (*pcVar1)();
        }
        uVar6 = *(ulong *)(uVar4 + uVar6 * 8 + 0x20);
      }
      else {
        FUN_1000cbedc(uVar6,uVar4);
      }
      _swift_bridgeObjectRelease(uVar4);
      FUN_10034293c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(IVar3,uVar6);
    }
  }
  return;
}

// ==== 1002dd148 FUN_1002dd148 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001002dd650) */
/* WARNING: Removing unreachable block (ram,0x0001002dd58c) */
/* WARNING: Removing unreachable block (ram,0x0001002dd6e8) */
/* WARNING: Type propagation algorithm not settling */

long FUN_1002dd148(long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  ulong *puVar1;
  byte bVar2;
  bool bVar3;
  undefined *puVar4;
  uint uVar5;
  long lVar6;
  ID IVar7;
  ID IVar8;
  undefined *puVar9;
  ID IVar10;
  ulong uVar11;
  undefined8 uVar12;
  undefined8 *******pppppppuVar13;
  ID IVar14;
  ulong uVar15;
  uint uVar16;
  ulong uVar17;
  ID unaff_x20;
  long lVar18;
  code *pcVar19;
  long lVar20;
  long *plVar21;
  undefined8 *puVar22;
  long lVar23;
  long lVar24;
  double dVar25;
  undefined8 uVar26;
  double dVar27;
  double dVar28;
  long local_260;
  long local_258;
  long local_250;
  long local_248;
  ID local_240 [4];
  ulong local_220;
  ID local_218;
  long local_210;
  undefined8 local_200;
  undefined8 uStack_1f8;
  ulong local_1f0;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 uStack_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 uStack_1b8;
  long local_1b0;
  undefined8 uStack_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined *local_190;
  uint local_188;
  byte local_184;
  undefined1 uStack_183;
  ushort uStack_182;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  byte bStack_178;
  byte bStack_177;
  byte bStack_176;
  byte bStack_175;
  long local_168;
  ulong local_160;
  ulong uStack_158;
  ulong local_150;
  ulong uStack_148;
  ulong local_140;
  ulong uStack_138;
  ulong uStack_130;
  ulong uStack_128;
  undefined2 local_120;
  undefined8 *******local_110;
  undefined8 uStack_108;
  ulong local_100;
  long lStack_f8;
  ulong local_f0;
  long local_e8;
  double local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  long local_b0;
  
  lVar6 = 0;
  FUN_10020acbc();
  lVar23 = *(long *)(lVar6 + -8);
  lVar20 = (long)&local_260 - (*(long *)(lVar23 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar9 = &DAT_100af7568;
  FUN_100021774();
  uVar17 = *(long *)(*(long *)(puVar9 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar24 = lVar20 - uVar17;
  local_248 = lVar24 - uVar17;
  local_220 = local_248 - uVar17;
  local_240[1] = local_220 - uVar17;
  lVar18 = local_240[1] - uVar17;
  IVar7 = _objc_msgSend(unaff_x20,"song");
  if (IVar7 == 0) {
    return 0;
  }
  local_258 = lVar24;
  local_250 = lVar20;
  local_240[0] = param_2;
  local_240[2] = lVar23;
  local_240[3] = lVar6;
  local_218 = IVar7;
  local_210 = param_1;
  FUN_1003270b8();
  lVar6 = *(long *)(IVar7 + 0x10);
  if (lVar6 != 0) {
    plVar21 = (long *)(IVar7 + 0x28);
    do {
      lVar20 = plVar21[-1];
      lVar23 = *plVar21;
      lVar24 = lVar20;
      _swift_getObjectType();
      pcVar19 = *(code **)(lVar23 + 0x38);
      _swift_unknownObjectRetain(lVar20);
      (*pcVar19)(lVar24,lVar23);
      if (7 < ((uint)lVar24 & 0xff)) {
        _swift_bridgeObjectRelease(IVar7);
        _swift_unknownObjectRelease(lVar20);
        return lVar20;
      }
      _swift_unknownObjectRelease(lVar20);
      plVar21 = plVar21 + 2;
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
  }
  _swift_bridgeObjectRelease(IVar7);
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar17 = DAT_100b757a8;
  FUN_10016fe5c();
  lVar6 = local_210;
  IVar7 = local_218;
  if ((((uVar17 == 0) || ((*(byte *)(uVar17 + _TtC8Playback15APIOrganization::hasRentals) & 1) != 0)
       ) || (uVar17 = DAT_100b757a8, FUN_10016fe5c(), uVar17 == 0)) ||
     ((*(byte *)(uVar17 + _TtC8Playback15APIOrganization::hasCloud) & 1) != 0)) {
LAB_1002dd380:
    dVar27 = *(double *)(lVar6 + 0x88);
    dVar25 = 0.0;
    dVar28 = *(double *)(lVar6 + 0x80);
    if (*(double *)(lVar6 + 0x80) < dVar27) {
LAB_1002dd398:
      dVar25 = dVar28;
    }
LAB_1002dd39c:
    IVar8 = local_240[0];
    _objc_msgSend(unaff_x20,"setStoredStartTime:",dVar25);
    _objc_msgSend(unaff_x20,"setStoredEndTime:",dVar27);
    bVar3 = false;
  }
  else {
    IVar8 = _objc_msgSend(IVar7,"contentTypeID");
    uVar5 = (uint)IVar8;
    FUN_100419df0();
    if ((uVar5 & 0xff) != 3) goto LAB_1002dd380;
    if (*(short *)(lVar6 + 0x10) == 0xc) {
      dVar27 = *(double *)(lVar6 + 0x88);
      dVar25 = 0.0;
      dVar28 = *(double *)(lVar6 + 0x80);
      if (*(double *)(lVar6 + 0x80) < dVar27) goto LAB_1002dd398;
      goto LAB_1002dd39c;
    }
    bVar3 = true;
    IVar8 = local_240[0];
  }
  uStack_198 = *(undefined8 *)(lVar6 + 0xe8);
  local_1a0 = *(undefined8 *)(lVar6 + 0xe0);
  local_190 = *(undefined **)(lVar6 + 0xf0);
  local_188 = (uint)*(undefined8 *)(lVar6 + 0xf8);
  uVar26 = *(undefined8 *)(lVar6 + 0x104);
  uVar12 = *(undefined8 *)(lVar6 + 0xfc);
  uStack_17c = (undefined4)uVar26;
  bStack_178 = (byte)((ulong)uVar26 >> 0x20);
  bStack_177 = (byte)((ulong)uVar26 >> 0x28);
  bStack_176 = (byte)((ulong)uVar26 >> 0x30);
  bStack_175 = (byte)((ulong)uVar26 >> 0x38);
  local_184 = (byte)uVar12;
  uStack_183 = (undefined1)((ulong)uVar12 >> 8);
  uStack_182 = (ushort)((ulong)uVar12 >> 0x10);
  uStack_180 = (undefined4)((ulong)uVar12 >> 0x20);
  uStack_1d8 = *(undefined8 *)(lVar6 + 0xa8);
  local_1e0 = *(undefined8 *)(lVar6 + 0xa0);
  local_1c8 = *(undefined8 *)(lVar6 + 0xb8);
  local_1d0 = *(undefined8 *)(lVar6 + 0xb0);
  uStack_1b8 = *(undefined8 *)(lVar6 + 200);
  local_1c0 = *(undefined8 *)(lVar6 + 0xc0);
  uStack_1a8 = *(undefined8 *)(lVar6 + 0xd8);
  local_1b0 = *(long *)(lVar6 + 0xd0);
  uStack_1f8 = *(undefined8 *)(lVar6 + 0x88);
  local_200 = *(undefined8 *)(lVar6 + 0x80);
  local_1e8 = *(undefined8 *)(lVar6 + 0x98);
  local_1f0 = *(ulong *)(lVar6 + 0x90);
  _objc_msgSend(unaff_x20,"setEndFade:",local_1f0 & 0xff);
  uVar5 = 0;
  if ((byte)local_1e0 != 5) {
    uVar5 = (uint)(byte)local_1e0;
  }
  _objc_msgSend(unaff_x20,"setStoredTransition:",(ulong)uVar5);
  _objc_msgSend(unaff_x20,"setTransitionContinuePad:",(ulong)(local_1e0._1_1_ & 1));
  _objc_msgSend(unaff_x20,"setStoredSMPTEEnabled:",
                (ulong)((uStack_1d8._1_1_ == 2 | uStack_1d8._1_1_) & 1));
  uVar12 = 0;
  if ((char)local_1c8 == '\0') {
    uVar12 = local_1d0;
  }
  _objc_msgSend(unaff_x20,"setSmpteStartTime:",uVar12);
  FUN_10032c6b8();
  puVar9 = &_OBJC_CLASS___NSNumber;
  _objc_allocWithZone();
  IVar10 = _objc_msgSend((ID)puVar9,"initWithDouble:",uVar12);
  _objc_msgSend(unaff_x20,"setStoredSMPTETimelineLocation:",IVar10);
  IVar10 = _objc_msgSend(IVar7,"contentTypeID");
  uVar5 = (uint)IVar10;
  FUN_100419df0();
  if ((uVar5 & 0xff) == 3) {
    FUN_10003b4b4(IVar8,lVar18,&DAT_100af7568);
    lVar20 = lVar18;
    (**(code **)(local_240[2] + 0x30))(lVar18,1,local_240[3]);
    if ((int)lVar20 == 1) {
      FUN_100023be4(lVar18,&DAT_100af7568);
    }
    else {
      IVar10 = *(ID *)(lVar18 + 0x20);
      FUN_1000233c8(lVar18,FUN_10020acbc);
      FUN_100571c08();
      IVar14 = _objc_msgSend(IVar10,"timeSignatureID");
      lVar18 = (long)(int)IVar14;
      FUN_10055ee18();
      if (((uint)lVar18 & 0xff) != 0x14) {
        IVar8 = _objc_msgSend(IVar10,"bpm");
        FUN_10032bcf0((double)(int)IVar8);
        FUN_10032be28(lVar18);
        _objc_msgSend(IVar7,"setClickTimes:",0);
        goto LAB_1002dd74c;
      }
    }
  }
  uVar17 = local_220;
  IVar10 = _objc_msgSend(IVar7,"contentTypeID");
  uVar5 = (uint)IVar10;
  FUN_100419df0();
  if ((uVar5 & 0xff) != 3) {
    IVar10 = _objc_msgSend(IVar7,"contentTypeID");
    uVar5 = (uint)IVar10;
    FUN_100419df0();
    if ((uVar5 & 0xff) != 0xd) goto LAB_1002dd74c;
  }
  IVar10 = local_240[1];
  FUN_10003b4b4(IVar8,local_240[1],&DAT_100af7568);
  pcVar19 = *(code **)(local_240[2] + 0x30);
  IVar14 = IVar10;
  (*pcVar19)(IVar10,1,local_240[3]);
  if ((int)IVar14 == 1) {
    FUN_100023be4(IVar10,&DAT_100af7568);
LAB_1002dd670:
    uVar5 = 1;
  }
  else {
    uVar5 = (uint)*(ushort *)(IVar10 + 0x28);
    FUN_100419df0();
    if ((((uVar5 & 0xff) != 0xd) || ((*(byte *)(IVar10 + 0xa8) & 1) != 0)) ||
       (lVar6 = *(long *)(IVar10 + 0xa0), lVar6 == 0)) {
      FUN_1000233c8(IVar10,FUN_10020acbc);
      goto LAB_1002dd670;
    }
    FUN_100571c08();
    uVar5 = (uint)lVar6;
    FUN_100571458();
    local_260 = param_4;
    FUN_1000233c8(local_240[1],FUN_10020acbc);
    if (local_260 == 0) {
      uVar5 = 1;
      uVar17 = local_220;
    }
    else {
      _swift_bridgeObjectRelease();
      uVar17 = local_220;
    }
  }
  FUN_10003b4b4(IVar8,uVar17,&DAT_100af7568);
  uVar15 = 1;
  uVar11 = uVar17;
  (*pcVar19)(uVar17,1,local_240[3]);
  if ((int)uVar11 == 1) {
    FUN_100023be4(uVar17,&DAT_100af7568);
    lVar6 = local_210;
LAB_1002dd700:
    uVar17 = *(ulong *)(lVar6 + 0x28);
  }
  else {
    uVar16 = (uint)*(ushort *)(uVar17 + 0x28);
    FUN_100419df0();
    lVar6 = local_210;
    if ((((uVar16 & 0xff) != 0xd) || ((*(byte *)(uVar17 + 0xa8) & 1) != 0)) ||
       (*(long *)(uVar17 + 0xa0) == 0)) {
      FUN_1000233c8(uVar17,FUN_10020acbc);
      goto LAB_1002dd700;
    }
    FUN_100571c08();
    FUN_100571458();
    IVar8 = local_240[0];
    local_220 = uVar15;
    FUN_1000233c8(uVar17,FUN_10020acbc);
    uVar17 = local_220;
    if (param_4 == 0) goto LAB_1002dd700;
    _swift_bridgeObjectRelease(param_4);
  }
  FUN_1002e90b0(IVar8,lVar6);
  FUN_1002e3e90(uVar5 & 1);
  FUN_10032bcf0(uVar17);
  FUN_10032be28(IVar8);
  _objc_msgSend(IVar7,"setClickTimes:",0);
LAB_1002dd74c:
  IVar8 = _objc_msgSend(IVar7,"contentTypeID");
  uVar5 = (uint)IVar8;
  FUN_100419df0();
  if ((uVar5 & 0xff) == 3) {
    if (*(long *)(lVar6 + 0x48) == 0) {
      uVar12 = 0;
    }
    else {
      uVar12 = *(undefined8 *)(lVar6 + 0x40);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar12);
    }
    _objc_msgSend(IVar7,"setCustomName:",uVar12);
  }
  if ((*(byte *)(lVar6 + 0x68) & 1) == 0) {
    uVar12 = *(undefined8 *)(lVar6 + 0x60);
    puVar9 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar8 = _objc_msgSend((ID)puVar9,"initWithInteger:",uVar12);
    _objc_msgSend(IVar7,"setMidiProPresenterPlaylist:",IVar8);
    bVar2 = *(byte *)(lVar6 + 0x78);
  }
  else {
    bVar2 = *(byte *)(lVar6 + 0x78);
  }
  lVar18 = local_1b0;
  if ((bVar2 & 1) == 0) {
    uVar12 = *(undefined8 *)(lVar6 + 0x70);
    puVar9 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar8 = _objc_msgSend((ID)puVar9,"initWithInteger:",uVar12);
    _objc_msgSend(IVar7,"setMidiProPresenterPlaylistItem:",IVar8);
    lVar18 = local_1b0;
  }
  if (!bVar3) {
    lVar20 = *(long *)(lVar18 + 0x10);
    local_1b0 = lVar18;
    local_168 = lVar18;
    if (lVar20 != 0) {
      FUN_1002e8928(0);
      puVar22 = (undefined8 *)(lVar18 + 0x20);
      _swift_bridgeObjectRetain(lVar18);
      local_220 = CONCAT44(local_220._4_4_,1);
      dVar28 = 0.0;
      do {
        uStack_108 = puVar22[1];
        local_110 = (undefined8 *******)*puVar22;
        lStack_f8 = puVar22[3];
        local_100 = puVar22[2];
        local_e8 = puVar22[5];
        local_f0 = puVar22[4];
        uStack_d8 = puVar22[7];
        dVar25 = (double)puVar22[6];
        uStack_c8 = puVar22[9];
        local_d0 = puVar22[8];
        local_b8 = puVar22[0xb];
        local_c0 = puVar22[10];
        local_b0 = puVar22[0xc];
        local_e0 = dVar25;
        FUN_1002f99e8(&local_110);
        IVar8 = _objc_msgSend(unaff_x20,"song");
        if (IVar8 == 0) {
LAB_1002dd924:
          lVar18 = lStack_f8;
          if ((local_f0 & 1) == 0) {
            if ((long)local_110 < -0x8000) {
                    /* WARNING: Does not return */
              pcVar19 = (code *)SoftwareBreakpoint(1,0x1002de234);
              (*pcVar19)();
            }
            if (0x7fff < (long)local_110) {
                    /* WARNING: Does not return */
              pcVar19 = (code *)SoftwareBreakpoint(1,0x1002de238);
              (*pcVar19)();
            }
            pppppppuVar13 = local_110;
            FUN_100722ff4();
            uVar5 = (uint)pppppppuVar13;
            if (((uVar5 & 0xff) == 0x4b) || (((ulong)pppppppuVar13 & 0xff) == 0)) {
              if (((ulong)local_e0 & 1) == 0) {
                if (local_e8 == 0x3d) goto LAB_1002ddc30;
              }
              else if ((uVar5 & 0xff) == 0x18) {
LAB_1002ddc30:
                if (lVar18 < 1) goto LAB_1002ddc50;
              }
              goto LAB_1002dd92c;
            }
            if (((uVar5 & 0xff) != 0x18) || (0 < lVar18)) goto LAB_1002dd92c;
LAB_1002ddc50:
            IVar8 = _objc_msgSend(unaff_x20,"song");
            if (IVar8 == 0) goto LAB_1002dd888;
            uVar17 = (ulong)bStack_175;
            FUN_10032d88c(uVar17,local_100 & 0xff);
            FUN_10003be48(&local_110);
            if (uVar17 != 0) {
              _objc_msgSend(unaff_x20,"addStoredSectionsObject:",uVar17);
            }
          }
          else {
LAB_1002dd92c:
            dVar25 = *(double *)(lVar6 + 0x28);
            pppppppuVar13 = &local_110;
            FUN_10032dda0(dVar25);
            if (pppppppuVar13 == (undefined8 *******)0x0) goto LAB_1002dd888;
LAB_1002dd944:
            FUN_100039048(0);
            FUN_100039b64(pppppppuVar13,local_e8,(ulong)local_e0 & 0xff);
            lVar6 = local_b0;
            uVar12 = local_b8;
            if (local_b0 != 0) {
              FUN_1002f99e8(&local_110);
              __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar12,lVar6);
              FUN_10003be48(&local_110);
              _objc_msgSend((ID)pppppppuVar13,"setStoredUUID:",uVar12);
            }
            if ((local_220 & 1) == 0) {
              _objc_msgSend((ID)pppppppuVar13,"startTimeOriginal");
              dVar25 = dVar28 + dVar25;
              _objc_msgSend((ID)pppppppuVar13,"setStartTimeOriginal:",dVar25);
              _objc_msgSend((ID)pppppppuVar13,"endTimeOriginal");
              dVar25 = dVar28 + dVar25;
              _objc_msgSend((ID)pppppppuVar13,"setEndTimeOriginal:");
            }
            IVar8 = _objc_msgSend((ID)pppppppuVar13,"editedSectionTypeID");
            IVar7 = local_218;
            if (IVar8 == 0) {
              IVar8 = _objc_msgSend((ID)pppppppuVar13,"storedSectionType");
            }
            else {
              IVar8 = _objc_msgSend(IVar8,"shortValue");
            }
            lVar6 = local_210;
            FUN_100722ff4();
            uVar5 = (uint)IVar8 & 0xff;
            if (uVar5 == 0x18) {
              if ((*(byte *)(lVar6 + 0x58) & 1) == 0) {
                lVar6 = *(long *)(lVar6 + 0x50);
                FUN_1003221bc();
                IVar7 = local_218;
                if (IVar8 != 0) {
                  if (*(long *)(IVar8 + 0x10) == 0) {
                    _swift_bridgeObjectRelease();
                    IVar7 = local_218;
                  }
                  else {
                    lVar23 = *(long *)(IVar8 + 0x40);
                    lVar18 = *(long *)(IVar8 + 0x48);
                    _swift_bridgeObjectRelease();
                    IVar7 = local_218;
                    _objc_msgSend(local_218,"bpm");
                    dVar25 = 1.0 / ((double)lVar18 * 0.25 * (dVar25 / 60.0));
                    dVar27 = dVar25 * (double)lVar23;
                    lVar18 = 2;
                    if (lVar6 != -1) {
                      lVar18 = lVar6;
                    }
                    _objc_msgSend((ID)pppppppuVar13,"endTimeOriginal");
                    dVar28 = dVar25;
                    _objc_msgSend((ID)pppppppuVar13,"startTimeOriginal");
                    dVar28 = dVar28 + dVar27 * (double)lVar18;
                    _objc_msgSend((ID)pppppppuVar13,"setEndTimeOriginal:",dVar28);
                    _objc_msgSend((ID)pppppppuVar13,"endTimeOriginal");
                    dVar28 = dVar28 - dVar25;
                    puVar9 = &_OBJC_CLASS___NSNumber;
                    _objc_allocWithZone();
                    IVar8 = _objc_msgSend((ID)puVar9,"initWithInteger:",lVar6);
                    _objc_msgSend(IVar7,"setClickSongMeasureCount:",IVar8);
                    _objc_msgSend(IVar7,"setClickTimes:",0);
                    local_220 = local_220 & 0xffffffff00000000;
                  }
                }
              }
            }
            else if (uVar5 == 0x4b) {
              __sSo13os_log_type_ta0A0E7defaultABvgZ();
              puVar9 = PTR___swiftEmptyArrayStorage_100a1e050;
              _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
              FUN_10041ac94(IVar8,0x70,"Unknown sectionType for this song",0x21,2,puVar9);
              _swift_release(puVar9);
            }
            if (DAT_100ae0030 != -1) {
              _swift_once(&DAT_100ae0030,FUN_1008174c0);
            }
            uVar5 = 1;
            FUN_100819fe0(1);
            _objc_msgSend((ID)pppppppuVar13,"setPresetInfiniteLoop:",
                          (ulong)(uVar5 & (byte)local_100 & 1));
            uVar12 = 0;
            if ((char)local_d0 == '\0') {
              uVar12 = uStack_d8;
            }
            _objc_msgSend((ID)pppppppuVar13,"setStoredStartTimeTrimOffset:",uVar12);
            uVar12 = 0;
            if ((char)local_c0 == '\0') {
              uVar12 = uStack_c8;
            }
            _objc_msgSend((ID)pppppppuVar13,"setStoredEndTimeTrimOffset:",uVar12);
            uVar5 = (uint)local_c0._1_1_;
            if (uVar5 == 2) {
              _objc_msgSend((ID)pppppppuVar13,"setStoredPlayGuideCue:",0);
            }
            else {
              FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
              uVar17 = (ulong)(uVar5 & 1);
              __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(uVar17);
              _objc_msgSend((ID)pppppppuVar13,"setStoredPlayGuideCue:",uVar17);
            }
            uVar5 = (uint)local_c0._2_1_;
            if (uVar5 == 2) {
              _objc_msgSend((ID)pppppppuVar13,"setStoredPlayCountIn:",0);
            }
            else {
              FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
              uVar17 = (ulong)(uVar5 & 1);
              __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(uVar17);
              _objc_msgSend((ID)pppppppuVar13,"setStoredPlayCountIn:",uVar17);
            }
            lVar6 = local_210;
            FUN_10003be48(&local_110);
            _objc_msgSend(unaff_x20,"addStoredSectionsObject:",pppppppuVar13);
          }
        }
        else {
          IVar8 = _objc_msgSend(IVar8,"contentTypeID");
          uVar5 = (uint)IVar8;
          FUN_100419df0();
          if ((uVar5 & 0xff) != 3) goto LAB_1002dd924;
          pppppppuVar13 = local_110;
          FUN_10032d640();
          if (pppppppuVar13 != (undefined8 *******)0x0) goto LAB_1002dd944;
LAB_1002dd888:
          FUN_10003be48(&local_110);
        }
        puVar22 = puVar22 + 0xd;
        lVar20 = lVar20 + -1;
      } while (lVar20 != 0);
      FUN_1001d7e54(&local_168);
      FUN_10032d02c(0);
      FUN_1002e75d4();
    }
    IVar8 = local_240[0];
    lVar20 = local_248;
    FUN_10003b4b4(local_240[0],local_248,&DAT_100af7568);
    IVar10 = local_240[2];
    lVar23 = lVar20;
    (**(code **)(local_240[2] + 0x30))(lVar20,1,local_240[3]);
    lVar18 = local_250;
    if ((int)lVar23 == 1) {
      FUN_100023be4(lVar20,&DAT_100af7568);
    }
    else {
      FUN_100023340(lVar20,local_250);
      lVar20 = local_258;
      FUN_100023384(lVar18,local_258,FUN_10020acbc);
      (**(code **)(IVar10 + 0x38))(lVar20,0,1,local_240[3]);
      FUN_1002ded8c(lVar20);
      IVar7 = local_218;
      FUN_100023be4(lVar20,&DAT_100af7568);
      FUN_1000233c8(lVar18,FUN_10020acbc);
    }
    FUN_1002e9208(lVar6,IVar7,IVar8,0);
    if (CONCAT44(uStack_17c,uStack_180) != 1) {
      local_160 = CONCAT71(local_160._1_7_,local_184) & 0xffffffffffffff01;
      uVar5 = 0x100;
      if ((bStack_177 & 1) == 0) {
        uVar5 = 0;
      }
      uVar16 = 0x10000;
      if ((bStack_176 & 1) == 0) {
        uVar16 = 0;
      }
      FUN_1002e9b7c((ulong)local_188 | (ulong)uStack_182 << 0x30 | (ulong)(local_184 & 1) << 0x20,
                    CONCAT44(uStack_17c,uStack_180),uVar5 | bStack_178 & 1 | uVar16);
    }
    uVar17 = DAT_100b757a8;
    FUN_100171514();
    if ((uVar17 & 1) != 0) {
      _objc_msgSend(unaff_x20,"setMasterVolumeLevel:",local_1e8);
    }
    IVar7 = _objc_msgSend(unaff_x20,"song");
    puVar4 = local_190;
    puVar9 = PTR___swiftEmptyArrayStorage_100a1e050;
    if (IVar7 != 0) {
      if (local_190 == (undefined *)0x0) {
        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        lVar6 = *(long *)(puVar9 + 0x10);
      }
      else {
        lVar6 = *(long *)(local_190 + 0x10);
        puVar9 = local_190;
      }
      if (lVar6 == 0) {
        _swift_bridgeObjectRetain(puVar4);
        _swift_bridgeObjectRelease(puVar9);
      }
      else {
        FUN_100823c68(0);
        _swift_bridgeObjectRetain(puVar4);
        _swift_bridgeObjectRetain(puVar9);
        lVar18 = 0x20;
        do {
          puVar1 = (ulong *)(puVar9 + lVar18);
          uStack_158 = puVar1[1];
          local_160 = *puVar1;
          uStack_148 = puVar1[3];
          local_150 = puVar1[2];
          uStack_138 = puVar1[5];
          local_140 = puVar1[4];
          uStack_128 = puVar1[7];
          uStack_130 = puVar1[6];
          local_120 = (undefined2)puVar1[8];
          FUN_1002f9a10(&local_160);
          FUN_1002f9a10(&local_160);
          FUN_100822c4c(&local_160,IVar7);
          FUN_1002f9a58(&local_160);
          lVar18 = lVar18 + 0x48;
          lVar6 = lVar6 + -1;
        } while (lVar6 != 0);
        _swift_bridgeObjectRelease_n(puVar9,2);
      }
    }
  }
  return 0;
}

// ==== 1002e5438 FUN_1002e5438 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001002e5f20) */
/* WARNING: Removing unreachable block (ram,0x0001002e5d00) */
/* WARNING: Removing unreachable block (ram,0x0001002e5f40) */
/* WARNING: Removing unreachable block (ram,0x0001002e5e10) */

ID FUN_1002e5438(double param_1,ulong param_2,undefined4 param_3,uint param_4,undefined8 param_5,
                undefined8 param_6,undefined8 param_7,long param_8,undefined4 param_9,byte param_10,
                undefined4 param_11,undefined8 param_12,byte param_13)

{
  uint uVar1;
  code *pcVar2;
  long lVar3;
  ID IVar4;
  ID IVar5;
  ID IVar6;
  long lVar7;
  ID IVar8;
  undefined8 uVar9;
  ID *pIVar10;
  undefined1 *puVar11;
  undefined *puVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  ID unaff_x20;
  long unaff_x21;
  ulong uVar16;
  long lVar17;
  ulong uVar18;
  ID local_140 [4];
  long local_120;
  long local_118;
  long local_110;
  ID *local_108;
  long local_100;
  ulong local_f8;
  undefined8 local_f0;
  long local_e8;
  ulong local_e0;
  ID local_d8;
  ulong local_d0;
  ID local_c0;
  undefined1 auStack_b8 [40];
  undefined1 auStack_90 [24];
  long local_78;
  
  local_e0 = CONCAT44(local_e0._4_4_,param_9);
  local_d8 = CONCAT44(local_d8._4_4_,param_3);
  lVar3 = 0;
  local_e8 = param_8;
  local_d0 = param_2;
  FUN_10068e908();
  uVar13 = *(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_140[3] = (long)local_140 - uVar13;
  local_110 = local_140[3] - uVar13;
  lVar14 = local_110 - uVar13;
  uVar13 = 0;
  local_120 = lVar14;
  local_118 = lVar3;
  FUN_1001436fc();
  uVar15 = *(long *)(*(long *)(uVar13 - 8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_108 = (ID *)(lVar14 - uVar15);
  lVar14 = (long)local_108 - uVar15;
  lVar3 = 0;
  local_100 = lVar14;
  local_f8 = uVar13;
  __s10Foundation4DateVMa();
  lVar17 = *(long *)(lVar3 + -8);
  lVar14 = lVar14 - (*(long *)(lVar17 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar4 = _objc_msgSend(DAT_100b755c8,"viewContext");
  IVar4 = _objc_msgSend(unaff_x20,"initWithContext:",IVar4);
  _objc_msgSend(IVar4,"setId:",0);
  _objc_msgSend(IVar4,"setReadOnly:",(ulong)(param_4 & 1));
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_5,param_6);
  _swift_bridgeObjectRelease(param_6);
  _objc_msgSend(IVar4,"setTitle:",param_5);
  IVar5 = _objc_msgSend(IVar4,"setSong:",param_7);
  __s10Foundation4DateVACycfC(lVar14);
  __s10Foundation4DateV19_bridgeToObjectiveCSo6NSDateCyF();
  (**(code **)(lVar17 + 8))(lVar14,lVar3);
  _objc_msgSend(IVar4,"setLastSavedDate:",IVar5);
  FUN_1002e6134(local_d0,(uint)local_d8 & 1,0,0);
  lVar3 = local_e8;
  if (unaff_x21 != 0) goto LAB_1002e60f8;
  local_f0 = param_7;
  FUN_1000cda74(0);
  IVar5 = IVar4;
  FUN_1000c7ea4();
  _objc_msgSend(IVar4,"addStoredTracksObject:",IVar5);
  IVar8 = IVar4;
  FUN_1000c79fc(IVar4,1,0,0);
  _objc_msgSend(IVar4,"addStoredTracksObject:",IVar8);
  FUN_1002dcf18();
  IVar6 = _objc_msgSend(IVar4,"song");
  lVar3 = local_e8;
  if (IVar6 == 0) {
    param_1 = 1.0;
  }
  else {
    FUN_1003220ec();
  }
  param_1 = 0.0 / param_1;
  local_140[2] = IVar8;
  _objc_msgSend(IVar4,"setStoredStartTime:",param_1);
  _objc_msgSend(IVar4,"setEndFade:",0);
  _objc_msgSend(IVar4,"setStoredTransition:",0);
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  FUN_1001726d0(DAT_100b757a8);
  _objc_msgSend(IVar4,"setMasterVolumeLevel:",param_1);
  FUN_10003b4b4(lVar3,auStack_90,&DAT_100af5d38);
  IVar8 = IVar4;
  local_d8 = IVar4;
  if (local_78 != 0) {
    FUN_10003b4b4(auStack_90,auStack_b8,&DAT_100af5d38);
    puVar12 = &DAT_100af5d40;
    FUN_100021774(&DAT_100af5d40);
    lVar17 = local_100;
    lVar7 = local_100;
    _swift_dynamicCast(local_100,auStack_b8,puVar12,local_f8,0);
    pIVar10 = local_108;
    lVar14 = local_120;
    if ((int)lVar7 == 0) {
      lVar7 = local_120;
      _swift_dynamicCast(local_120,auStack_b8,puVar12,local_118,0);
      lVar17 = local_110;
      if ((int)lVar7 == 0) {
        uVar9 = 0;
        FUN_1001cc624(0);
        pIVar10 = &local_c0;
        _swift_dynamicCast(pIVar10,auStack_b8,puVar12,uVar9,0);
        if ((int)pIVar10 == 0) {
          FUN_100023468(auStack_b8);
        }
        else {
          uVar13 = _objc_msgSend(local_c0,"managedObjectContext");
          if (uVar13 == 0) {
            FUN_100023468(auStack_b8);
          }
          else {
            local_140[1] = IVar5;
            IVar5 = _objc_msgSend(DAT_100b755c8,"viewContext");
            FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
            __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar13,IVar5);
            if ((uVar13 & 1) == 0) {
              _objc_msgSend(IVar5,"insertObject:",local_c0);
            }
            IVar8 = local_d8;
            _objc_msgSend(local_d8,"setStoredPad:",local_c0);
            FUN_100023468(auStack_b8);
            IVar5 = local_140[1];
          }
        }
      }
      else {
        local_140[1] = IVar5;
        FUN_100023340(lVar14,local_110,FUN_10068e908);
        IVar5 = (ID)*(uint *)(lVar17 + 4);
        FUN_1001d3358(IVar5,*(undefined2 *)(lVar17 + 2));
        if (IVar5 == 0) {
          FUN_1001cc624();
          IVar5 = local_140[3];
          FUN_100023384(lVar17,local_140[3],FUN_10068e908);
          FUN_1001c91d8();
          uVar13 = _objc_msgSend(IVar5,"managedObjectContext");
          if (uVar13 != 0) {
            IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
            goto LAB_1002e5b88;
          }
        }
        else {
          uVar13 = _objc_msgSend(IVar5,"managedObjectContext");
          if (uVar13 != 0) {
            IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
LAB_1002e5b88:
            FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
            __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar13,IVar8);
            if ((uVar13 & 1) == 0) {
              _objc_msgSend(IVar8,"insertObject:",IVar5);
            }
            _objc_msgSend(local_d8,"setStoredPad:",IVar5);
          }
        }
        FUN_1000233c8(local_110,FUN_10068e908);
        FUN_100023468(auStack_b8);
        IVar8 = local_d8;
        IVar5 = local_140[1];
      }
    }
    else {
      FUN_100023340(lVar17,local_108,FUN_1001436fc);
      IVar6 = *pIVar10;
      if ((long)IVar6 < -0x80000000) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002e6130);
        (*pcVar2)();
      }
      if (0x7fffffff < (long)IVar6) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002e6134);
        (*pcVar2)();
      }
      FUN_1001d3358(IVar6,0x24);
      if ((IVar6 != 0) &&
         (uVar13 = _objc_msgSend(IVar6,"managedObjectContext"), IVar8 = local_d8, uVar13 != 0)) {
        IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
        FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
        __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar13,IVar8);
        if ((uVar13 & 1) == 0) {
          _objc_msgSend(IVar8,"insertObject:",IVar6);
        }
        _objc_msgSend(local_d8,"setStoredPad:",IVar6);
        IVar8 = local_d8;
        pIVar10 = local_108;
      }
      FUN_1000233c8(pIVar10,FUN_1001436fc);
      FUN_100023468(auStack_b8);
    }
  }
  puVar11 = auStack_90;
  FUN_100023be4(puVar11,&DAT_100af5d38);
  FUN_1002dc978();
  if (puVar11 == (undefined1 *)0x0) {
    IVar6 = DAT_100afb908;
    IVar8 = DAT_100afb908;
    if (DAT_100afb908 == 0) {
      IVar6 = DAT_100b757a8;
      FUN_10017103c();
      FUN_1001d3358(IVar6,0x24);
      IVar8 = IVar6;
      if (IVar6 == 0) {
        FUN_1001d3a50();
        IVar8 = DAT_100afb908;
      }
    }
    DAT_100afb908 = IVar8;
    IVar8 = local_d8;
    FUN_1002e4900(IVar6);
  }
  uVar1 = (uint)local_e0;
  _objc_msgSend(IVar8,"setIncludePad:",(ulong)(*(long *)(lVar3 + 0x18) != 0));
  _objc_msgSend(IVar8,"setUseDefaultPad:",(ulong)((uint)(*(long *)(lVar3 + 0x18) == 0) | uVar1 & 1))
  ;
  uVar13 = _objc_msgSend(IVar8,"setPadIntroOutroOnly:",0);
  FUN_1002dc978();
  if (uVar13 != 0) {
    FUN_1001c8dfc();
    local_140[0] = IVar4;
    local_140[1] = IVar5;
    if (uVar13 >> 0x3e == 0) {
      uVar15 = *(ulong *)((uVar13 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar15 = uVar13 & 0xffffffffffffff8;
      if ((long)uVar13 < 0) {
        uVar15 = uVar13;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar15 != 0) {
      FUN_1002939cc(0);
      if ((long)uVar15 < 1) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002e612c);
        (*pcVar2)();
      }
      uVar18 = 0;
      uVar16 = uVar13 & 0xc000000000000001;
      local_f8 = uVar13;
      local_e0 = uVar16;
      local_d0 = uVar15;
      do {
        if (uVar16 == 0) {
          uVar15 = *(ulong *)(uVar13 + uVar18 * 8 + 0x20);
        }
        else {
          uVar15 = uVar18;
          FUN_1000cc534(uVar18,uVar13);
        }
        IVar4 = _objc_msgSend(IVar8,"useDefaultPad");
        if ((int)IVar4 == 0) {
          IVar4 = _objc_msgSend(IVar8,"storedPad");
          IVar5 = DAT_100afb908;
          if (IVar4 == 0) {
            FUN_1001d3a50();
            IVar5 = DAT_100afb908;
          }
        }
        else {
          IVar8 = local_d8;
          IVar4 = DAT_100afb908;
          uVar16 = local_e0;
          IVar5 = DAT_100afb908;
          if (DAT_100afb908 == 0) {
            IVar4 = DAT_100b757a8;
            FUN_10017103c();
            FUN_1001d3358(IVar4,0x24);
            IVar8 = local_d8;
            uVar16 = local_e0;
            uVar13 = local_f8;
            IVar5 = IVar4;
            if (IVar4 == 0) {
              FUN_1001d3a50();
              IVar8 = local_d8;
              uVar16 = local_e0;
              uVar13 = local_f8;
              IVar5 = DAT_100afb908;
            }
          }
        }
        DAT_100afb908 = IVar5;
        FUN_1002939ec(uVar15,IVar4);
        _objc_msgSend(IVar8,"addStoredPadTracksObject:",uVar15);
        uVar18 = uVar18 + 1;
      } while (local_d0 != uVar18);
    }
    _swift_bridgeObjectRelease(uVar13);
    IVar4 = local_140[0];
    lVar3 = local_e8;
  }
  _objc_msgSend(IVar8,"setStoredSMPTEEnabled:",(ulong)(param_10 & 1));
  if ((param_13 & 1) == 0) {
    puVar12 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar5 = _objc_msgSend((ID)puVar12,"initWithDouble:",param_12);
    _objc_msgSend(IVar8,"setStoredSMPTETimelineLocation:",IVar5);
  }
  else {
    _objc_msgSend(IVar8,"setStoredSMPTETimelineLocation:",0);
  }
LAB_1002e60f8:
  FUN_100023be4(lVar3,&DAT_100af5d38);
  return IVar4;
}

// ==== 1002f7e1c FUN_1002f7e1c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_1002f7e1c(double param_1,ID param_2,ID param_3,ulong param_4,uint param_5,ID param_6,
                char *param_7,double param_8,uint param_9,double param_10,byte param_11,
                undefined4 param_12,undefined8 param_13)

{
  uint uVar1;
  ulong uVar2;
  code *pcVar3;
  uint uVar4;
  long lVar5;
  ID IVar6;
  ID IVar7;
  ID IVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined8 uVar11;
  undefined8 *puVar12;
  ID IVar13;
  undefined *puVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  ulong *puVar18;
  long lVar19;
  ID unaff_x20;
  undefined *puVar20;
  ulong uVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  undefined1 auStack_100 [8];
  ulong *local_f8;
  long lStack_f0;
  double local_e8;
  double local_e0;
  ulong local_d8;
  uint local_d0;
  uint local_cc;
  ID local_c8;
  ulong local_c0;
  ulong *local_b8;
  undefined *local_b0;
  ID local_a8;
  undefined *local_a0;
  ulong *puStack_98;
  ulong local_90;
  long lStack_88;
  ulong local_80;
  
  lVar5 = 0;
  local_e0 = param_8;
  local_cc = param_9;
  local_c8 = param_2;
  __s10Foundation4DateVMa();
  lVar19 = *(long *)(lVar5 + -8);
  lVar15 = *(long *)(lVar19 + 0x40);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  local_b8 = (ulong *)param_13;
  IVar6 = _objc_msgSend(DAT_100b755c8,"viewContext");
  IVar6 = _objc_msgSend(unaff_x20,"initWithContext:",IVar6);
  if ((param_4 & 1) != 0) {
    param_3 = _objc_msgSend(local_c8,"id");
  }
  _objc_msgSend(IVar6,"setId:",param_3);
  _objc_msgSend(IVar6,"setReadOnly:",(ulong)(param_5 & 1));
  IVar8 = local_c8;
  if (param_7 == (char *)0x0) {
    param_7 = "title";
    param_6 = _objc_msgSend(local_c8,"title");
    if (param_6 != 0) {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      goto LAB_1002f7f80;
    }
    param_6 = 0;
  }
  else {
LAB_1002f7f80:
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_6,param_7);
    _swift_bridgeObjectRelease(param_7);
  }
  _objc_msgSend(IVar6,"setTitle:",param_6);
  IVar7 = _objc_msgSend(IVar6,"setSong:",local_b8);
  __s10Foundation4DateVACycfC(auStack_100 + -(lVar15 + 0xfU & 0xfffffffffffffff0));
  __s10Foundation4DateV19_bridgeToObjectiveCSo6NSDateCyF();
  (**(code **)(lVar19 + 8))(auStack_100 + -(lVar15 + 0xfU & 0xfffffffffffffff0),lVar5);
  _objc_msgSend(IVar6,"setLastSavedDate:",IVar7);
  IVar8 = _objc_msgSend(IVar8,"storedSections");
  if (IVar8 != 0) {
    puVar9 = (undefined *)_objc_msgSend(IVar8,"array");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (puVar9,PTR___sypN_100a1e038 + 8);
    puVar14 = puVar9;
    FUN_1002d86c4(puVar9,FUN_1001cc32c,FUN_100039048);
    _swift_bridgeObjectRelease(puVar9);
    if (puVar14 != (undefined *)0x0) goto LAB_1002f809c;
  }
  puVar14 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_1002f809c:
  if ((ulong)puVar14 >> 0x3e == 0) {
    puVar9 = *(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar9 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
    if ((long)puVar14 < 0) {
      puVar9 = puVar14;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar9 != (undefined *)0x0) {
    FUN_100039048(0);
    if ((long)puVar9 < 1) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x1002f89b8);
      (*pcVar3)();
    }
    puVar20 = (undefined *)0x0;
    do {
      if (((ulong)puVar14 & 0xc000000000000001) == 0) {
        puVar10 = *(undefined **)(puVar14 + (long)puVar20 * 8 + 0x20);
      }
      else {
        puVar10 = puVar20;
        FUN_1000cbf0c(puVar20,puVar14);
      }
      puVar20 = puVar20 + 1;
      FUN_100039b64();
      _objc_msgSend(IVar6,"addStoredSectionsObject:",puVar10);
    } while (puVar9 != puVar20);
  }
  _swift_bridgeObjectRelease();
  FUN_1002dc2dc();
  if ((ulong)puVar14 >> 0x3e == 0) {
    puVar9 = *(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar9 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
    if ((long)puVar14 < 0) {
      puVar9 = puVar14;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (puVar9 != (undefined *)0x0) {
    FUN_1000cda74(0);
    if ((long)puVar9 < 1) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x1002f89bc);
      (*pcVar3)();
    }
    puVar20 = (undefined *)0x0;
    do {
      if (((ulong)puVar14 & 0xc000000000000001) == 0) {
        puVar10 = *(undefined **)(puVar14 + (long)puVar20 * 8 + 0x20);
      }
      else {
        puVar10 = puVar20;
        FUN_1000cc338(puVar20,puVar14);
      }
      puVar20 = puVar20 + 1;
      FUN_1000c6d04(puVar10,IVar6);
      _objc_msgSend(IVar6,"addStoredTracksObject:",puVar10);
    } while (puVar9 != puVar20);
  }
  local_e8 = param_10;
  _swift_bridgeObjectRelease();
  FUN_1002e16c8();
  if (((ulong)puVar14 & 0xc000000000000001) == 0) {
    lVar5 = 0;
    uVar17 = -1L << ((ulong)(byte)puVar14[0x20] & 0x3f);
    puStack_98 = (ulong *)(puVar14 + 0x38);
    local_90 = ~uVar17;
    uVar17 = -uVar17;
    uVar21 = 0xffffffffffffffff;
    if ((long)uVar17 < 0x40) {
      uVar21 = ~(-1L << (uVar17 & 0x3f));
    }
    uVar21 = uVar21 & *puStack_98;
    puVar9 = puVar14;
  }
  else {
    puVar9 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
    if ((long)puVar14 < 0) {
      puVar9 = puVar14;
    }
    __ss10__CocoaSetV12makeIteratorAB0D0CyF();
    uVar11 = 0;
    FUN_1002939cc(0);
    puVar12 = &DAT_100afe560;
    FUN_100023140(&DAT_100afe560,FUN_1002939cc,PTR___sSo8NSObjectCSH10ObjectiveCMc_100a1e0f0);
    __sSh8IteratorV6_cocoaAByx_Gs10__CocoaSetVAACn_tcfC(&local_a0,puVar9,uVar11,puVar12);
    puVar14 = puVar9;
    puVar9 = local_a0;
    lVar5 = lStack_88;
    uVar21 = local_80;
  }
  local_d0 = (uint)param_11;
  local_c0 = local_90 + 0x40 >> 6;
  lStack_f0 = local_c0 - 7;
  local_f8 = puStack_98 + 7;
  uVar17 = uVar21;
  local_d8 = local_90;
  local_b8 = puStack_98;
  if ((long)puVar9 < 0) goto LAB_1002f843c;
  do {
    uVar17 = uVar21;
    lVar15 = lVar5;
    lVar19 = lVar5;
    if (uVar21 == 0) {
      lVar15 = lVar5 + 1;
      if (SCARRY8(lVar5,1)) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x1002f89b4);
        (*pcVar3)();
      }
      if ((long)local_c0 <= lVar15) {
LAB_1002f8630:
        uVar17 = 0;
LAB_1002f8634:
        FUN_10003bf10(puVar9,local_b8,local_d8,lVar19,uVar17);
        IVar8 = local_c8;
        FUN_1002dc978();
        FUN_1002e4900();
        IVar7 = _objc_msgSend(IVar8,"includePad");
        _objc_msgSend(IVar6,"setIncludePad:",IVar7);
        IVar7 = _objc_msgSend(IVar8,"useDefaultPad");
        _objc_msgSend(IVar6,"setUseDefaultPad:",IVar7);
        IVar7 = _objc_msgSend(IVar8,"padIntroOutroOnly");
        _objc_msgSend(IVar6,"setPadIntroOutroOnly:",IVar7);
        dVar23 = local_e0;
        if ((local_cc & 1) != 0) {
          _objc_msgSend(IVar8,"storedStartTime");
          dVar24 = param_1;
          IVar7 = _objc_msgSend(IVar8,"song");
          if (IVar7 == 0) {
            dVar23 = 1.0;
          }
          else {
            FUN_1003220ec();
            dVar23 = dVar24;
          }
          dVar23 = param_1 * dVar23;
          param_1 = dVar24;
        }
        IVar7 = _objc_msgSend(IVar6,"song");
        if (IVar7 == 0) {
          param_1 = 1.0;
        }
        else {
          FUN_1003220ec();
        }
        dVar23 = dVar23 / param_1;
        _objc_msgSend(IVar6,"setStoredStartTime:",dVar23);
        dVar24 = local_e8;
        if ((local_d0 & 1) != 0) {
          _objc_msgSend(IVar8,"storedEndTime");
          dVar22 = dVar23;
          IVar7 = _objc_msgSend(IVar8,"song");
          if (IVar7 == 0) {
            dVar24 = 1.0;
          }
          else {
            FUN_1003220ec();
            dVar24 = dVar22;
          }
          dVar24 = dVar23 * dVar24;
          dVar23 = dVar22;
        }
        IVar7 = _objc_msgSend(IVar6,"song");
        if (IVar7 == 0) {
          dVar23 = 1.0;
        }
        else {
          FUN_1003220ec();
        }
        _objc_msgSend(IVar6,"setStoredEndTime:",dVar24 / dVar23);
        IVar7 = _objc_msgSend(IVar8,"endFade");
        IVar7 = _objc_msgSend(IVar6,"setEndFade:",IVar7);
        uVar4 = (uint)IVar7;
        FUN_1002da058();
        uVar1 = 0;
        if ((uVar4 & 0xff) != 5) {
          uVar1 = uVar4;
        }
        _objc_msgSend(IVar6,"setStoredTransition:",(ulong)(uVar1 & 0xff));
        IVar7 = _objc_msgSend(IVar8,"transitionContinuePad");
        _objc_msgSend(IVar6,"setTransitionContinuePad:",IVar7);
        _objc_msgSend(IVar8,"masterVolumeLevel");
        _objc_msgSend(IVar6,"setMasterVolumeLevel:");
        uVar21 = 0;
        FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
        if ((uVar21 & 1) == 0) {
          if (DAT_100ae0030 != -1) {
            _swift_once(&DAT_100ae0030,FUN_1008174c0);
          }
          uVar21 = 0;
          FUN_100819fe0();
          if ((uVar21 & 1) == 0) {
            IVar7 = 0;
            goto LAB_1002f88f4;
          }
        }
        IVar7 = _objc_msgSend(IVar8,"storedSMPTEEnabled");
LAB_1002f88f4:
        _objc_msgSend(IVar6,"setStoredSMPTEEnabled:",IVar7);
        _objc_msgSend(IVar8,"smpteStartTime");
        _objc_msgSend(IVar6,"setSmpteStartTime:");
        IVar7 = _objc_msgSend(IVar8,"storedSMPTETimelineLocation");
        _objc_msgSend(IVar6,"setStoredSMPTETimelineLocation:",IVar7);
        IVar8 = _objc_msgSend(IVar8,"midiBankID");
        _objc_msgSend(IVar6,"setMidiBankID:",IVar8);
        return IVar6;
      }
      uVar17 = local_b8[lVar15];
      if (uVar17 == 0) {
        lVar15 = lVar5 + 2;
        if ((long)local_c0 <= lVar15) goto LAB_1002f8630;
        uVar17 = local_b8[lVar15];
        if (uVar17 == 0) {
          lVar15 = lVar5 + 3;
          if ((long)local_c0 <= lVar15) goto LAB_1002f8630;
          uVar17 = local_b8[lVar15];
          if (uVar17 == 0) {
            lVar15 = lVar5 + 4;
            if ((long)local_c0 <= lVar15) goto LAB_1002f8630;
            uVar17 = local_b8[lVar15];
            if (uVar17 == 0) {
              lVar15 = lVar5 + 5;
              if ((long)local_c0 <= lVar15) goto LAB_1002f8630;
              uVar17 = local_b8[lVar15];
              if (uVar17 == 0) {
                lVar15 = lVar5 + 6;
                if ((long)local_c0 <= lVar15) goto LAB_1002f8630;
                uVar17 = local_b8[lVar15];
                if (uVar17 == 0) {
                  lVar16 = lStack_f0 - lVar5;
                  puVar18 = local_f8 + lVar5;
                  do {
                    if (lVar16 == 0) goto LAB_1002f8630;
                    lVar15 = lVar15 + 1;
                    uVar17 = *puVar18;
                    lVar16 = lVar16 + -1;
                    puVar18 = puVar18 + 1;
                  } while (uVar17 == 0);
                }
              }
            }
          }
        }
      }
    }
    uVar2 = (uVar17 & 0xaaaaaaaaaaaaaaaa) >> 1 | (uVar17 & 0x5555555555555555) << 1;
    uVar2 = (uVar2 & 0xcccccccccccccccc) >> 2 | (uVar2 & 0x3333333333333333) << 2;
    uVar2 = (uVar2 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar2 & 0xf0f0f0f0f0f0f0f) << 4;
    uVar2 = (uVar2 & 0xff00ff00ff00ff00) >> 8 | (uVar2 & 0xff00ff00ff00ff) << 8;
    uVar2 = (uVar2 & 0xffff0000ffff0000) >> 0x10 | (uVar2 & 0xffff0000ffff) << 0x10;
    IVar8 = *(ID *)(*(long *)(puVar9 + 0x30) +
                   (lVar15 << 9 | LZCOUNT(uVar2 >> 0x20 | uVar2 << 0x20) << 3));
    uVar2 = uVar17 - 1 & uVar17;
    uVar17 = uVar21;
    while( true ) {
      lVar5 = lVar15;
      uVar21 = uVar2;
      if (IVar8 == 0) goto LAB_1002f8634;
      IVar7 = 0;
      FUN_1002939cc();
      _objc_allocWithZone();
      IVar13 = _objc_msgSend(DAT_100b755c8,"viewContext");
      IVar7 = _objc_msgSend(IVar7,"initWithContext:",IVar13);
      _objc_msgSend(IVar7,"setArrangement:",IVar6);
      IVar13 = _objc_msgSend(IVar8,"padContentID");
      _objc_msgSend(IVar7,"setPadContentID:",IVar13);
      IVar13 = _objc_msgSend(IVar8,"padContentTypeID");
      _objc_msgSend(IVar7,"setPadContentTypeID:",IVar13);
      IVar13 = _objc_msgSend(IVar8,"title");
      _objc_msgSend(IVar7,"setTitle:",IVar13);
      _objc_msgSend(IVar8,"volume");
      _objc_msgSend(IVar7,"setVolume:");
      IVar8 = _objc_msgSend(IVar8,"muted");
      _objc_msgSend(IVar7,"setMuted:",IVar8);
      _objc_msgSend(IVar6,"addStoredPadTracksObject:",IVar7);
      puVar14 = (undefined *)0x0;
      uVar17 = uVar21;
      if (-1 < (long)puVar9) break;
LAB_1002f843c:
      __ss10__CocoaSetV8IteratorC4nextyXlSgyF();
      lVar19 = lVar5;
      if (puVar14 == (undefined *)0x0) goto LAB_1002f8634;
      uVar11 = 0;
      local_b0 = puVar14;
      FUN_1002939cc(0);
      _swift_unknownObjectRetain(puVar14);
      _swift_dynamicCast(&local_a8,&local_b0,PTR___syXlN_100a1e030 + 8,uVar11,7);
      IVar8 = local_a8;
      _swift_unknownObjectRelease(puVar14);
      uVar2 = uVar17;
      lVar15 = lVar5;
    }
  } while( true );
}

// ==== 1002f9aa0 FUN_1002f9aa0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001002fb5cc) */

ID FUN_1002f9aa0(double param_1,double param_2,double param_3,long param_4,undefined4 param_5,
                undefined *param_6,undefined8 param_7,ID param_8,double param_9,long param_10,
                long param_11,undefined8 param_12,uint param_13,undefined4 param_14,
                undefined8 param_15,uint param_16,undefined4 param_17,undefined8 param_18,
                byte param_19)

{
  long lVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  ID IVar8;
  ID IVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  double dVar13;
  double *pdVar14;
  undefined8 uVar15;
  undefined **ppuVar16;
  ID IVar17;
  ID *pIVar18;
  undefined *puVar19;
  undefined1 *puVar20;
  ulong uVar21;
  long lVar22;
  double *pdVar23;
  long *plVar24;
  ID unaff_x20;
  long lVar25;
  ulong uVar26;
  char *pcVar27;
  long lVar28;
  double dVar29;
  double dVar30;
  undefined8 auStack_3a0 [2];
  ID aIStack_390 [4];
  ID *local_370;
  long local_368;
  long local_360;
  long lStack_358;
  long local_350;
  long local_348;
  long local_340;
  long local_338;
  long local_330;
  long local_328;
  undefined8 local_320;
  undefined8 uStack_318;
  char *local_308;
  undefined8 local_300;
  undefined8 local_2f8;
  ID local_2f0;
  char *local_2e8;
  undefined8 local_2e0;
  undefined8 uStack_2d8;
  undefined8 local_2d0;
  ID local_2c8;
  undefined8 local_2c0;
  double local_2b8;
  ID local_2b0;
  undefined8 local_2a8;
  ulong local_2a0;
  undefined *local_298;
  undefined1 auStack_290 [128];
  double local_210;
  double dStack_208;
  double local_200;
  double dStack_1f8;
  double local_1f0;
  undefined8 uStack_1e8;
  double local_1e0;
  double dStack_1d8;
  double local_1d0;
  undefined1 uStack_1c8;
  char cStack_1c7;
  undefined1 uStack_1c6;
  undefined5 uStack_1c5;
  undefined3 uStack_1c0;
  undefined8 uStack_1bd;
  ID local_1a8;
  undefined *local_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  long local_188;
  undefined8 local_180;
  char local_121;
  double local_120;
  double dStack_118;
  double dStack_110;
  undefined1 uStack_108;
  undefined7 uStack_107;
  undefined1 local_100;
  undefined7 uStack_ff;
  undefined1 uStack_f8;
  undefined7 uStack_f7;
  double dStack_f0;
  double dStack_e8;
  double local_e0;
  undefined3 uStack_d8;
  undefined5 uStack_d5;
  undefined3 uStack_d0;
  undefined8 uStack_cd;
  double local_c0;
  double dStack_b8;
  double dStack_b0;
  undefined1 local_a8;
  undefined7 uStack_a7;
  undefined1 uStack_a0;
  undefined7 uStack_9f;
  undefined1 uStack_98;
  
  local_2a0 = CONCAT44(local_2a0._4_4_,param_5);
  lVar6 = 0;
  local_330 = param_10;
  local_328 = param_11;
  local_2c8 = param_8;
  local_298 = param_6;
  FUN_10068e908();
  uVar21 = *(long *)(*(long *)(lVar6 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  aIStack_390[1] = (long)aIStack_390 - uVar21;
  aIStack_390[2] = aIStack_390[1] - uVar21;
  lVar22 = aIStack_390[2] - uVar21;
  lVar7 = 0;
  aIStack_390[3] = lVar6;
  local_338 = lVar22;
  FUN_1001436fc();
  uVar21 = *(long *)(*(long *)(lVar7 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  local_370 = (ID *)(lVar22 - uVar21);
  lVar22 = (long)local_370 - uVar21;
  lVar6 = 0;
  local_368 = lVar7;
  local_340 = lVar22;
  __s10Foundation25NSFastEnumerationIteratorVMa();
  local_360 = *(long *)(lVar6 + -8);
  lVar22 = lVar22 - (*(long *)(local_360 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar7 = 0;
  lStack_358 = lVar6;
  local_348 = lVar22;
  FUN_100893664();
  pcVar27 = (char *)(lVar22 - (*(long *)(*(long *)(lVar7 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0))
  ;
  lVar6 = 0;
  local_2a8 = lVar7;
  __s10Foundation4DateVMa();
  lVar22 = *(long *)(lVar6 + -8);
  lVar7 = (long)pcVar27 - (*(long *)(lVar22 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
  IVar8 = _objc_msgSend(unaff_x20,"initWithContext:",IVar8);
  local_350 = param_4;
  _objc_msgSend(IVar8,"setId:",param_4);
  _objc_msgSend(IVar8,"setReadOnly:",(ulong)((uint)local_2a0 & 1));
  puVar19 = local_298;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(local_298,param_7);
  _swift_bridgeObjectRelease(param_7);
  _objc_msgSend(IVar8,"setTitle:",puVar19);
  IVar9 = _objc_msgSend(IVar8,"setSong:",local_2c8);
  __s10Foundation4DateVACycfC(lVar7);
  __s10Foundation4DateV19_bridgeToObjectiveCSo6NSDateCyF();
  (**(code **)(lVar22 + 8))(lVar7,lVar6);
  _objc_msgSend(IVar8,"setLastSavedDate:",IVar9);
  lVar6 = *(long *)((long)param_9 + 0x10);
  if (lVar6 == 0) {
LAB_1002f9d28:
    bVar3 = false;
  }
  else if (*(long *)((long)param_9 + 0x30) == 0) {
    bVar3 = true;
  }
  else {
    if (lVar6 == 1) goto LAB_1002f9d28;
    lVar22 = 1;
    plVar24 = (long *)((long)param_9 + 0x60);
    do {
      lVar25 = lVar22 + 1;
      if (SCARRY8(lVar22,1)) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb554);
        (*pcVar2)();
      }
      lVar28 = *plVar24;
      bVar3 = lVar28 == 0;
      lVar22 = lVar22 + 1;
      plVar24 = plVar24 + 6;
    } while (lVar28 != 0 && lVar25 != lVar6);
  }
  local_121 = '\x03';
  local_120 = param_9;
  _swift_bridgeObjectRetain(param_9);
  lVar6 = 0;
  FUN_1002da65c(&local_120,bVar3,&local_121);
  _swift_bridgeObjectRelease(param_9);
  dVar29 = local_120;
  if (local_121 != '\x03') {
    *pcVar27 = local_121;
    *(ID *)(pcVar27 + 8) = local_2c8;
    _swift_storeEnumTagMultiPayload(pcVar27,local_2a8,0x11);
    if (DAT_100adfd70 != -1) {
      _swift_once(&DAT_100adfd70,FUN_100742498);
    }
    uVar15 = DAT_100b778d0;
    _swift_retain(DAT_100b778d0);
    FUN_1007421dc(pcVar27);
    _swift_release(uVar15);
    FUN_1000233c8(pcVar27,FUN_100893664);
  }
  puVar19 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_2a0 = *(ulong *)((long)dVar29 + 0x10);
  local_2b0 = IVar8;
  if (local_2a0 == 0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    local_2c0 = _TtC8Playback15SongArrangement::validationError;
    local_2a8 = (long)dVar29 + 0x20;
    local_2e8 = "section %{public}@";
    local_2f0 = *(ID *)PTR__NSLocalizedDescriptionKey_100a1d638;
    local_2f8 = ", then download again.";
    local_300 = *(undefined8 *)PTR__NSLocalizedFailureReasonErrorKey_100a1d640;
    local_308 = "n Start Times Detected";
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    uVar21 = 0;
    uStack_2d8 = 2;
    local_2e0 = 1;
    uStack_318 = 4;
    local_320 = 2;
    local_2b8 = dVar29;
    do {
      if (*(ulong *)((long)dVar29 + 0x10) <= uVar21) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb550);
        (*pcVar2)();
      }
      pdVar23 = (double *)(local_2a8 + uVar21 * 0x30);
      dStack_b8 = pdVar23[1];
      local_c0 = *pdVar23;
      dVar30 = pdVar23[3];
      dStack_b0 = pdVar23[2];
      uStack_9f = (undefined7)*(undefined8 *)((long)pdVar23 + 0x21);
      uStack_98 = (undefined1)((ulong)*(undefined8 *)((long)pdVar23 + 0x21) >> 0x38);
      uStack_a0 = (undefined1)((ulong)*(undefined8 *)((long)pdVar23 + 0x19) >> 0x38);
      local_a8 = SUB81(dVar30,0);
      uStack_a7 = (undefined7)((ulong)dVar30 >> 8);
      lVar22 = CONCAT71(uStack_9f,uStack_a0);
      lVar25 = *(long *)(puVar19 + 0x10);
      if (lVar25 == 0) {
LAB_1002fa154:
        local_298 = puVar19;
        FUN_100039048(0);
        FUN_1002fb5d8(&local_c0);
        FUN_1002fb5d8(&local_c0);
        pdVar23 = &local_c0;
        FUN_10003a5f4(pdVar23,IVar8);
        if (lVar6 == 0) {
          _objc_msgSend(IVar8,"addStoredSectionsObject:",pdVar23);
        }
        else {
          uVar15 = 0;
          __sSo13os_log_type_ta0A0E7defaultABvgZ(0);
          puVar19 = &DAT_100af52c8;
          FUN_100021774();
          _swift_initStackObject();
          *(undefined8 *)(puVar19 + 0x18) = uStack_2d8;
          *(ulong *)(puVar19 + 0x10) = local_2e0;
          dStack_118 = dStack_b8;
          local_120 = local_c0;
          uStack_108 = local_a8;
          dStack_110 = dStack_b0;
          uStack_ff = uStack_9f;
          uStack_f8 = uStack_98;
          uStack_107 = uStack_a7;
          local_100 = uStack_a0;
          _swift_bridgeObjectRetain(lVar22);
          pdVar23 = &local_120;
          puVar12 = &DAT_100a5a208;
          __sSS10describingSSx_tclufC();
          *(undefined **)(puVar19 + 0x38) = PTR___sSSN_100a1dce0;
          pdVar14 = pdVar23;
          FUN_100026528();
          *(double **)(puVar19 + 0x40) = pdVar14;
          *(double **)(puVar19 + 0x20) = pdVar23;
          *(undefined **)(puVar19 + 0x28) = puVar12;
          FUN_10041ac94(uVar15,0x5a,"Failed to add song sections for section %{public}@",0x32,2,
                        puVar19);
          _swift_setDeallocating(puVar19);
          FUN_100023468(puVar19 + 0x20);
          _swift_errorRelease(lVar6);
          lVar6 = 0;
        }
        puVar19 = local_298;
        puVar12 = local_298;
        _swift_isUniquelyReferenced_nonNull_native();
        dVar29 = local_2b8;
        puVar10 = puVar19;
        if (((ulong)puVar12 & 1) == 0) {
          puVar10 = (undefined *)0x0;
          FUN_10078ddf0(0,*(long *)(puVar19 + 0x10) + 1,1,puVar19);
        }
        IVar8 = local_2b0;
        uVar26 = *(ulong *)(puVar10 + 0x10);
        puVar19 = puVar10;
        if (*(ulong *)(puVar10 + 0x18) >> 1 <= uVar26) {
          puVar19 = (undefined *)(ulong)(1 < *(ulong *)(puVar10 + 0x18));
          FUN_10078ddf0(puVar19,uVar26 + 1,1,puVar10);
        }
        *(ulong *)(puVar19 + 0x10) = uVar26 + 1;
        *(double *)(puVar19 + uVar26 * 0x10 + 0x20) = dVar30;
        *(long *)(puVar19 + uVar26 * 0x10 + 0x28) = lVar22;
      }
      else {
        dVar13 = *(double *)(puVar19 + 0x20);
        if (((dVar13 != dVar30) || (*(long *)(puVar19 + 0x28) != lVar22)) &&
           (__ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                      (dVar13,*(long *)(puVar19 + 0x28),dVar30,lVar22,0), ((ulong)dVar13 & 1) == 0))
        {
          if (lVar25 != 1) {
            dVar13 = *(double *)(puVar19 + 0x30);
            if (((dVar13 == dVar30) && (*(long *)(puVar19 + 0x38) == lVar22)) ||
               (__ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                          (dVar13,*(long *)(puVar19 + 0x38),dVar30,lVar22,0),
               ((ulong)dVar13 & 1) != 0)) goto LAB_1002fa134;
            if (lVar25 != 2) {
              plVar24 = (long *)(puVar19 + 0x48);
              lVar28 = 2;
              local_298 = puVar19;
              do {
                lVar1 = lVar28 + 1;
                if (SCARRY8(lVar28,1)) {
                    /* WARNING: Does not return */
                  pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb558);
                  (*pcVar2)();
                }
                dVar13 = (double)plVar24[-1];
                puVar19 = local_298;
                dVar29 = local_2b8;
                if ((dVar13 == dVar30 && *plVar24 == lVar22) ||
                   (__ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                              (dVar13,*plVar24,dVar30,lVar22,0), puVar19 = local_298,
                   dVar29 = local_2b8, ((ulong)dVar13 & 1) != 0)) goto LAB_1002fa134;
                lVar28 = lVar28 + 1;
                plVar24 = plVar24 + 2;
              } while (lVar1 != lVar25);
            }
          }
          goto LAB_1002fa154;
        }
LAB_1002fa134:
        lVar22 = local_2c0;
        if (*(long *)(IVar8 + local_2c0) == 0) {
          puVar12 = &DAT_100af6c58;
          FUN_100021774();
          puVar20 = auStack_290;
          _swift_initStackObject();
          *(undefined8 *)(puVar12 + 0x18) = uStack_318;
          *(undefined8 *)(puVar12 + 0x10) = local_320;
          IVar8 = local_2f0;
          __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
          *(ID *)(puVar12 + 0x20) = IVar8;
          *(undefined1 **)(puVar12 + 0x28) = puVar20;
          puVar10 = &_OBJC_CLASS___NSBundle;
          _swift_getInitializedObjCClass();
          IVar8 = _objc_msgSend((ID)puVar10,"mainBundle");
          local_2d0 = lVar6;
          local_298 = puVar19;
          *(undefined8 *)(lVar7 + -0x10) = 0xe000000000000000;
          uVar15 = 0xd000000000000026;
          uVar26 = (ulong)local_2f8 | 0x8000000000000000;
          __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
                    (0xd000000000000026,uVar26,0,0,IVar8,0,0xe000000000000000,0);
          *(undefined **)(puVar12 + 0x48) = PTR___sSSN_100a1dce0;
          *(undefined8 *)(puVar12 + 0x30) = uVar15;
          *(ulong *)(puVar12 + 0x38) = uVar26;
          uVar15 = local_300;
          __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
          *(undefined8 *)(puVar12 + 0x50) = uVar15;
          *(ulong *)(puVar12 + 0x58) = uVar26;
          IVar8 = _objc_msgSend((ID)puVar10,"mainBundle");
          *(undefined8 *)(lVar7 + -0x10) = 0xe000000000000000;
          uVar15 = 0xd0000000000000a6;
          uVar26 = (ulong)local_2e8 | 0x8000000000000000;
          __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
                    (0xd0000000000000a6,uVar26,0,0,IVar8,0,0xe000000000000000,0);
          dVar29 = local_2b8;
          puVar10 = PTR___sSSN_100a1dce0;
          *(undefined **)(puVar12 + 0x78) = PTR___sSSN_100a1dce0;
          *(undefined8 *)(puVar12 + 0x60) = uVar15;
          *(ulong *)(puVar12 + 0x68) = uVar26;
          puVar11 = puVar12;
          FUN_10079c390(puVar12);
          _swift_setDeallocating(puVar12);
          puVar19 = &DAT_100af6c60;
          FUN_100021774(&DAT_100af6c60);
          _swift_arrayDestroy(puVar12 + 0x20,2,puVar19);
          puVar12 = &_OBJC_CLASS___NSError;
          _objc_allocWithZone();
          uVar15 = 0xd000000000000012;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                    (0xd000000000000012,(ulong)local_308 | 0x8000000000000000);
          puVar19 = puVar11;
          __sSD10FoundationE19_bridgeToObjectiveCSo12NSDictionaryCyF
                    (puVar11,puVar10,PTR___sypN_100a1e038 + 8,PTR___sSSSHsWP_100a1dcf0);
          _swift_bridgeObjectRelease(puVar11);
          IVar9 = _objc_msgSend((ID)puVar12,"initWithDomain:code:userInfo:",uVar15,0x4b0,puVar19);
          puVar19 = local_298;
          IVar8 = local_2b0;
          lVar6 = local_2d0;
          uVar15 = *(undefined8 *)(local_2b0 + lVar22);
          *(ID *)(local_2b0 + lVar22) = IVar9;
          _swift_errorRelease(uVar15);
        }
      }
      uVar21 = uVar21 + 1;
    } while (uVar21 != local_2a0);
  }
  _swift_release(dVar29);
  local_2e8 = (char *)param_18;
  FUN_1002e4f5c(param_3);
  lVar6 = local_330;
  IVar8 = *(ID *)(local_330 + 0x10);
  local_2a0 = param_12;
  local_2f0 = IVar8;
  if (IVar8 != 0) {
    local_298 = puVar19;
    FUN_1000cda74(0);
    _swift_bridgeObjectRetain(lVar6);
    IVar9 = local_2b0;
    lVar7 = 0x20;
    do {
      pdVar23 = (double *)(lVar6 + lVar7);
      dStack_e8 = pdVar23[7];
      dStack_f0 = pdVar23[6];
      uStack_f8 = SUB81(pdVar23[5],0);
      uStack_f7 = (undefined7)((ulong)pdVar23[5] >> 8);
      local_100 = SUB81(pdVar23[4],0);
      uStack_ff = (undefined7)((ulong)pdVar23[4] >> 8);
      local_e0 = pdVar23[8];
      uStack_d8 = SUB83(pdVar23[9],0);
      uStack_cd = *(undefined8 *)((long)pdVar23 + 0x53);
      uStack_d5 = (undefined5)*(undefined8 *)((long)pdVar23 + 0x4b);
      uStack_d0 = (undefined3)((ulong)*(undefined8 *)((long)pdVar23 + 0x4b) >> 0x28);
      dStack_118 = pdVar23[1];
      param_3 = *pdVar23;
      dStack_110 = pdVar23[2];
      uStack_108 = SUB81(pdVar23[3],0);
      uStack_107 = (undefined7)((ulong)pdVar23[3] >> 8);
      local_120 = param_3;
      FUN_1000cf7b8(&local_120);
      pdVar23 = &local_120;
      FUN_1000c7404(pdVar23,IVar9);
      _objc_msgSend(IVar9,"addStoredTracksObject:",pdVar23);
      lVar7 = lVar7 + 0x60;
      IVar8 = IVar8 - 1;
    } while (IVar8 != 0);
    _swift_bridgeObjectRelease(lVar6);
    puVar19 = local_298;
  }
  uVar21 = local_2a0;
  local_2b8 = (double)CONCAT44(local_2b8._4_4_,(uint)param_19);
  local_2c0 = CONCAT44(local_2c0._4_4_,param_16 >> 8) & 0xffffffff000000ff;
  local_2e0 = CONCAT44(local_2e0._4_4_,param_13 >> 8) & 0xffffffff000000ff;
  local_2d0 = CONCAT44(local_2d0._4_4_,param_13) & 0xffffffff000000ff;
  IVar8 = _objc_msgSend(local_2c8,"contentTypeID");
  uVar5 = (uint)IVar8;
  FUN_100419df0();
  IVar9 = local_2b0;
  IVar8 = local_2f0;
  puVar12 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_2a8 = CONCAT44(local_2a8._4_4_,param_16) & 0xffffffff000000ff;
  if (((1 << (ulong)(uVar5 & 0x1f) & 0x3ffdfffU) == 0) && ((uVar5 & 0xff) == 0xd)) {
    local_2f8 = (char *)(CONCAT44(local_2f8._4_4_,param_13 >> 0x10) & 0xffffffff000000ff);
    if (local_2f0 == 0) {
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      _swift_bridgeObjectRelease(puVar19);
    }
    else {
      local_300 = param_15;
      local_298 = puVar19;
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      _swift_bridgeObjectRetain(lVar6);
      lVar7 = 0x20;
      while( true ) {
        IVar8 = IVar8 - 1;
        pdVar23 = (double *)(lVar6 + lVar7);
        dStack_1d8 = pdVar23[7];
        local_1e0 = pdVar23[6];
        dVar29 = pdVar23[9];
        local_1d0 = pdVar23[8];
        uStack_1c8 = SUB81(dVar29,0);
        cStack_1c7 = (char)((ulong)dVar29 >> 8);
        uStack_1c6 = (undefined1)((ulong)dVar29 >> 0x10);
        dStack_1f8 = pdVar23[3];
        local_200 = pdVar23[2];
        uStack_1e8 = pdVar23[5];
        local_1f0 = pdVar23[4];
        uStack_1bd = *(undefined8 *)((long)pdVar23 + 0x53);
        uStack_1c5 = (undefined5)*(undefined8 *)((long)pdVar23 + 0x4b);
        uStack_1c0 = (undefined3)((ulong)*(undefined8 *)((long)pdVar23 + 0x4b) >> 0x28);
        dStack_208 = pdVar23[1];
        local_210 = *pdVar23;
        param_3 = local_210;
        if (cStack_1c7 == '\x01') {
          FUN_1000cf7b8(&local_210);
          puVar19 = puVar12;
          _swift_isUniquelyReferenced_nonNull_native();
          local_1a0 = puVar12;
          if (((ulong)puVar19 & 1) == 0) {
            FUN_1001ccff0(0,*(long *)(puVar12 + 0x10) + 1,1);
          }
          uVar26 = *(ulong *)(local_1a0 + 0x10);
          if (*(ulong *)(local_1a0 + 0x18) >> 1 <= uVar26) {
            FUN_1001ccff0(1 < *(ulong *)(local_1a0 + 0x18),uVar26 + 1,1);
          }
          *(ulong *)(local_1a0 + 0x10) = uVar26 + 1;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x28) = dStack_208;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x20) = local_210;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x38) = dStack_1f8;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x30) = local_200;
          *(undefined8 *)(local_1a0 + uVar26 * 0x60 + 0x73) = uStack_1bd;
          *(ulong *)(local_1a0 + uVar26 * 0x60 + 0x6b) = CONCAT35(uStack_1c0,uStack_1c5);
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x58) = dStack_1d8;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x50) = local_1e0;
          *(ulong *)(local_1a0 + uVar26 * 0x60 + 0x68) =
               CONCAT53(uStack_1c5,CONCAT12(uStack_1c6,CONCAT11(cStack_1c7,uStack_1c8)));
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x60) = local_1d0;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x48) = uStack_1e8;
          *(double *)(local_1a0 + uVar26 * 0x60 + 0x40) = local_1f0;
          puVar12 = local_1a0;
          lVar6 = local_330;
          param_3 = local_1f0;
        }
        if (IVar8 == 0) break;
        lVar7 = lVar7 + 0x60;
      }
      _swift_bridgeObjectRelease(local_298);
      _swift_bridgeObjectRelease(lVar6);
      param_15 = local_300;
    }
    lVar25 = *(long *)(puVar12 + 0x10);
    _swift_release(puVar12);
    lVar22 = local_328;
    lVar7 = local_338;
    lVar6 = local_340;
    if (lVar25 == 0) {
      FUN_1000cda74(0);
      IVar8 = IVar9;
      FUN_1000c79fc(IVar9,(uint)local_2f8 & 1,0,0);
      _objc_msgSend(IVar9,"addStoredTracksObject:",IVar8);
    }
  }
  else {
    _swift_bridgeObjectRelease(puVar19);
    lVar7 = local_338;
    lVar6 = local_340;
    lVar22 = local_328;
  }
  FUN_1002dcf18();
  IVar8 = _objc_msgSend(IVar9,"storedTracks");
  lVar28 = local_330;
  lVar25 = local_350;
  if (IVar8 == 0) {
    _swift_bridgeObjectRelease(local_330);
    lVar28 = lVar22;
LAB_1002fabe0:
    _swift_bridgeObjectRelease(lVar28);
  }
  else {
    if (lVar22 == 0) goto LAB_1002fabe0;
    lVar7 = local_330;
    FUN_1002e05b8(local_330,lVar22);
    _swift_bridgeObjectRelease(lVar28);
    lVar6 = local_348;
    local_2f0 = IVar8;
    __sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF(local_348);
    __s10Foundation25NSFastEnumerationIteratorV4nextypSgyF(&local_210);
    if (dStack_1f8 != 0.0) {
      uVar15 = 0;
      FUN_1000cda74(0);
      puVar19 = PTR___sypN_100a1e038;
      local_298 = (undefined *)CONCAT44(local_298._4_4_,(uint)(lVar25 == 0) & (uint)lVar7);
      do {
        ppuVar16 = &local_1a0;
        _swift_dynamicCast(ppuVar16,&local_210,puVar19 + 8,uVar15,6);
        puVar12 = local_1a0;
        if (((ulong)ppuVar16 & 1) == 0) goto LAB_1002fa5a4;
        IVar8 = _objc_msgSend(local_2c8,"contentTypeID");
        uVar5 = (uint)IVar8;
        FUN_100419df0();
        if (((uVar5 & 0xff) == 0xd) && (IVar8 = _objc_msgSend((ID)puVar12,"partID"), IVar8 != 0)) {
          IVar8 = _objc_msgSend(IVar8,"integerValue");
          uVar5 = (uint)IVar8;
          IVar8 = _objc_msgSend((ID)puVar12,"isClickOrGuide");
          if ((IVar8 == 0) ||
             ((IVar8 = _objc_msgSend(IVar8,"boolValue"), lVar6 = local_348, (int)IVar8 == 0 ||
              (IVar8 = _objc_msgSend((ID)puVar12,"partID"), lVar6 = local_348, IVar8 == 0))))
          goto LAB_1002fa798;
          IVar8 = _objc_msgSend(IVar8,"integerValue");
          uVar4 = (uint)IVar8;
          FUN_10056fe0c();
          lVar6 = local_348;
          if (((uVar4 & 0xff) == 1) || ((uVar4 & 0xff) == 8)) goto LAB_1002fa798;
          FUN_10056fe0c();
          lVar6 = local_348;
          if ((uVar5 & 0xff) != 0x10) {
            if (DAT_100adfb10 != -1) {
              _swift_once(&DAT_100adfb10,FUN_10056b7a4);
            }
            lVar7 = *(long *)(DAT_100b77450 + 0x10);
            if (lVar7 != 0) {
              lVar22 = (&DAT_100931fb0)[(char)uVar5];
              if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x20)] == lVar22) goto LAB_1002fa798;
              if (lVar7 != 1) {
                if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x21)] == lVar22) goto LAB_1002fa798;
                if (lVar7 != 2) {
                  if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x22)] == lVar22)
                  goto LAB_1002fa798;
                  if (lVar7 != 3) {
                    pcVar27 = (char *)(DAT_100b77450 + 0x23);
                    lVar25 = 3;
                    do {
                      lVar28 = lVar25 + 1;
                      if (SCARRY8(lVar25,1)) {
                    /* WARNING: Does not return */
                        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb5c8);
                        (*pcVar2)();
                      }
                      if ((&DAT_100931fb0)[*pcVar27] == lVar22) goto LAB_1002fa798;
                      lVar25 = lVar25 + 1;
                      pcVar27 = pcVar27 + 1;
                    } while (lVar28 != lVar7);
                  }
                }
              }
            }
          }
          goto LAB_1002fa5a4;
        }
LAB_1002fa798:
        IVar8 = _objc_msgSend((ID)puVar12,"partID");
        if ((IVar8 != 0) && (IVar8 = _objc_msgSend(IVar8,"integerValue"), IVar8 == 0x4b3))
        goto LAB_1002fa588;
        IVar8 = _objc_msgSend((ID)puVar12,"partID");
        if (IVar8 == 0) {
LAB_1002fa868:
          IVar8 = _objc_msgSend(local_2c8,"contentTypeID");
          uVar5 = (uint)IVar8;
          FUN_100419df0();
          if ((uVar5 & 0xff) != 0x17) goto LAB_1002fab30;
          if ((int)local_298 != 0) goto LAB_1002fa588;
          IVar8 = _objc_msgSend((ID)puVar12,"genreID");
          if (IVar8 == 0) goto LAB_1002fab30;
          IVar8 = _objc_msgSend((ID)puVar12,"partID");
          if (IVar8 == 0) {
LAB_1002faaa4:
            IVar8 = _objc_msgSend((ID)puVar12,"isClickOrGuide");
            if (((IVar8 != 0) && (IVar8 = _objc_msgSend(IVar8,"boolValue"), (int)IVar8 != 0)) &&
               (IVar8 = _objc_msgSend((ID)puVar12,"partID"), IVar8 != 0)) {
              IVar8 = _objc_msgSend(IVar8,"integerValue");
              uVar5 = (uint)IVar8;
              FUN_10056fe0c();
              if (((uVar5 & 0xff) == 1) || ((uVar5 & 0xff) == 8)) goto LAB_1002fa588;
            }
LAB_1002fab30:
            lVar7 = local_328;
            FUN_1000ca034(local_328,1);
            uVar21 = (ulong)((uint)lVar7 & 1);
          }
          else {
            IVar8 = _objc_msgSend(IVar8,"integerValue");
            uVar5 = (uint)IVar8;
            IVar8 = _objc_msgSend((ID)puVar12,"isClickOrGuide");
            if (((IVar8 == 0) ||
                (IVar8 = _objc_msgSend(IVar8,"boolValue"), lVar6 = local_348, (int)IVar8 == 0)) ||
               (IVar8 = _objc_msgSend((ID)puVar12,"partID"), lVar6 = local_348, IVar8 == 0))
            goto LAB_1002faaa4;
            IVar8 = _objc_msgSend(IVar8,"integerValue");
            uVar4 = (uint)IVar8;
            FUN_10056fe0c();
            lVar6 = local_348;
            if (((uVar4 & 0xff) == 8) || ((uVar4 & 0xff) == 1)) goto LAB_1002faaa4;
            FUN_10056fe0c();
            lVar6 = local_348;
            if ((uVar5 & 0xff) != 0x10) {
              if (DAT_100adfb10 != -1) {
                _swift_once(&DAT_100adfb10,FUN_10056b7a4);
              }
              lVar7 = *(long *)(DAT_100b77450 + 0x10);
              if (lVar7 != 0) {
                lVar22 = (&DAT_100931fb0)[(char)uVar5];
                if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x20)] == lVar22) goto LAB_1002faaa4;
                if (lVar7 != 1) {
                  if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x21)] == lVar22)
                  goto LAB_1002faaa4;
                  if (lVar7 != 2) {
                    pcVar27 = (char *)(DAT_100b77450 + 0x22);
                    lVar25 = 2;
                    do {
                      lVar28 = lVar25 + 1;
                      if (SCARRY8(lVar25,1)) {
                    /* WARNING: Does not return */
                        pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb5cc);
                        (*pcVar2)();
                      }
                      if ((&DAT_100931fb0)[*pcVar27] == lVar22) goto LAB_1002faaa4;
                      lVar25 = lVar25 + 1;
                      pcVar27 = pcVar27 + 1;
                    } while (lVar28 != lVar7);
                  }
                }
              }
            }
LAB_1002fa588:
            uVar21 = 1;
          }
          _objc_msgSend((ID)puVar12,"setIncluded:",uVar21);
        }
        else {
          IVar8 = _objc_msgSend(IVar8,"integerValue");
          uVar5 = (uint)IVar8;
          FUN_10056fe0c();
          if ((uVar5 & 0xff) == 0x10) goto LAB_1002fa868;
          if (DAT_100adfb10 != -1) {
            _swift_once(&DAT_100adfb10,FUN_10056b7a4);
          }
          lVar7 = *(long *)(DAT_100b77450 + 0x10);
          if (lVar7 == 0) goto LAB_1002fa868;
          lVar22 = (&DAT_100931fb0)[(char)uVar5];
          if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x20)] != lVar22) {
            if (lVar7 != 1) {
              if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x21)] == lVar22) goto LAB_1002fa5a4;
              if (lVar7 != 2) {
                if ((&DAT_100931fb0)[*(char *)(DAT_100b77450 + 0x22)] == lVar22) goto LAB_1002fa5a4;
                if (lVar7 != 3) {
                  pcVar27 = (char *)(DAT_100b77450 + 0x23);
                  lVar25 = 3;
                  do {
                    lVar28 = lVar25 + 1;
                    if (SCARRY8(lVar25,1)) {
                    /* WARNING: Does not return */
                      pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb5c4);
                      (*pcVar2)();
                    }
                    if ((&DAT_100931fb0)[*pcVar27] == lVar22) goto LAB_1002fa5a4;
                    lVar25 = lVar25 + 1;
                    pcVar27 = pcVar27 + 1;
                  } while (lVar28 != lVar7);
                }
              }
            }
            goto LAB_1002fa868;
          }
        }
LAB_1002fa5a4:
        __s10Foundation25NSFastEnumerationIteratorV4nextypSgyF(&local_210);
      } while (dStack_1f8 != 0.0);
    }
    (**(code **)(local_360 + 8))(lVar6,lStack_358);
    _swift_bridgeObjectRelease(local_328);
    lVar7 = local_338;
    lVar6 = local_340;
    uVar21 = local_2a0;
    IVar9 = local_2b0;
  }
  FUN_10003b4b4(uVar21,&local_210,&DAT_100aff678);
  IVar8 = local_2c8;
  if (dStack_1f8 == 4.94065645841247e-324) {
    FUN_100023be4(&local_210,&DAT_100aff678);
    param_3 = 0.0;
    uStack_198 = 0;
    local_1a0 = (undefined *)0x0;
    local_188 = 0;
    uStack_190 = 0;
    local_180 = 0;
  }
  else {
    FUN_10003b4b4(&local_210,&local_1a0,&DAT_100af5d38);
    FUN_1002fb600(&local_210);
    if (local_188 != 0) {
      FUN_10003b4b4(&local_1a0,&local_210,&DAT_100af5d38);
      puVar19 = &DAT_100af5d40;
      FUN_100021774(&DAT_100af5d40);
      lVar22 = lVar6;
      _swift_dynamicCast(lVar6,&local_210,puVar19,local_368,0);
      pIVar18 = local_370;
      if ((int)lVar22 == 0) {
        lVar6 = lVar7;
        _swift_dynamicCast(lVar7,&local_210,puVar19,aIStack_390[3],0);
        IVar17 = aIStack_390[2];
        if ((int)lVar6 == 0) {
          uVar15 = 0;
          FUN_1001cc624(0);
          pIVar18 = &local_1a8;
          _swift_dynamicCast(pIVar18,&local_210,puVar19,uVar15,0);
          if ((int)pIVar18 == 0) goto LAB_1002fb02c;
          uVar26 = _objc_msgSend(local_1a8,"managedObjectContext");
          if (uVar26 != 0) {
            IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
            FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
            __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar26,IVar8);
            if ((uVar26 & 1) == 0) {
              _objc_msgSend(IVar8,"insertObject:",local_1a8);
            }
            _objc_msgSend(IVar9,"setStoredPad:",local_1a8);
          }
        }
        else {
          FUN_100023340(lVar7,aIStack_390[2],FUN_10068e908);
          IVar8 = (ID)*(uint *)(IVar17 + 4);
          FUN_1001d3358(IVar8,*(undefined2 *)(IVar17 + 2));
          if (IVar8 == 0) {
            FUN_1001cc624();
            IVar8 = aIStack_390[1];
            FUN_100023384(IVar17,aIStack_390[1],FUN_10068e908);
            FUN_1001c91d8();
            uVar26 = _objc_msgSend(IVar8,"managedObjectContext");
            if (uVar26 != 0) {
              IVar17 = _objc_msgSend(DAT_100b755c8,"viewContext");
              goto LAB_1002fb0a0;
            }
          }
          else {
            uVar26 = _objc_msgSend(IVar8,"managedObjectContext");
            if (uVar26 != 0) {
              IVar17 = _objc_msgSend(DAT_100b755c8,"viewContext");
LAB_1002fb0a0:
              FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
              __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar26,IVar17);
              if ((uVar26 & 1) == 0) {
                _objc_msgSend(IVar17,"insertObject:",IVar8);
              }
              _objc_msgSend(IVar9,"setStoredPad:",IVar8);
            }
          }
          FUN_1000233c8(aIStack_390[2],FUN_10068e908);
        }
        FUN_100023468(&local_210);
        IVar8 = local_2c8;
      }
      else {
        FUN_100023340(lVar6,local_370,FUN_1001436fc);
        IVar17 = *pIVar18;
        if ((long)IVar17 < -0x80000000) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb5bc);
          (*pcVar2)();
        }
        if (0x7fffffff < (long)IVar17) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1002fb5c0);
          (*pcVar2)();
        }
        FUN_1001d3358(IVar17,0x24);
        if ((IVar17 != 0) &&
           (uVar26 = _objc_msgSend(IVar17,"managedObjectContext"), IVar8 = local_2c8, uVar26 != 0))
        {
          IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
          FUN_100023404(0,&DAT_100af6ce8,&PTR__OBJC_CLASS___NSManagedObjectContext_100aa3f48);
          __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar26,IVar8);
          if ((uVar26 & 1) == 0) {
            _objc_msgSend(IVar8,"insertObject:",IVar17);
          }
          _objc_msgSend(IVar9,"setStoredPad:",IVar17);
          pIVar18 = local_370;
          IVar8 = local_2c8;
        }
        FUN_1000233c8(pIVar18,FUN_1001436fc);
LAB_1002fb02c:
        FUN_100023468(&local_210);
      }
    }
  }
  FUN_100023be4(&local_1a0,&DAT_100af5d38);
  IVar8 = _objc_msgSend(IVar8,"contentTypeID");
  uVar5 = (uint)IVar8;
  FUN_100419df0();
  if ((uVar5 & 0xff) == 0x1a) {
    if ((local_2e0 & 1) == 0) {
LAB_1002fb1d0:
      FUN_10003b4b4(uVar21,&local_210,&DAT_100aff678);
      if (dStack_1f8 != 4.94065645841247e-324) {
        uVar5 = (uint)uStack_1e8._1_1_;
        FUN_1002fb600(&local_210);
        goto LAB_1002fb23c;
      }
      FUN_100023be4(&local_210,&DAT_100aff678);
    }
  }
  else if ((local_2e0 & 1) == 0) {
    if ((uVar5 & 0xff) == 0xd) {
      uVar5 = 0;
      goto LAB_1002fb23c;
    }
    goto LAB_1002fb1d0;
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar15 = DAT_100b757a8;
  FUN_10017156c(DAT_100b757a8);
  uVar5 = (uint)uVar15;
LAB_1002fb23c:
  _objc_msgSend(IVar9,"setIncludePad:",(ulong)(uVar5 & 1));
  FUN_10003b4b4(uVar21,&local_210,&DAT_100aff678);
  if (dStack_1f8 == 4.94065645841247e-324) {
    FUN_100023be4(&local_210,&DAT_100aff678);
    uVar26 = 1;
  }
  else {
    uVar26 = (ulong)uStack_1e8 & 0xff;
    FUN_1002fb600(&local_210);
  }
  _objc_msgSend(IVar9,"setUseDefaultPad:",uVar26);
  FUN_10003b4b4(uVar21,&local_210,&DAT_100aff678);
  if (dStack_1f8 == 4.94065645841247e-324) {
    FUN_100023be4(&local_210,&DAT_100aff678);
    uVar26 = 0;
  }
  else {
    uVar26 = (ulong)uStack_1e8 >> 0x10 & 0xff;
    FUN_1002fb600(&local_210);
  }
  _objc_msgSend(IVar9,"setPadIntroOutroOnly:",uVar26);
  IVar8 = _objc_msgSend(IVar9,"song");
  dVar29 = 1.0;
  if (IVar8 != 0) {
    FUN_1003220ec();
    dVar29 = param_3;
  }
  param_1 = param_1 / dVar29;
  _objc_msgSend(IVar9,"setStoredStartTime:",param_1);
  IVar8 = _objc_msgSend(IVar9,"song");
  dVar29 = 1.0;
  if (IVar8 != 0) {
    FUN_1003220ec();
    dVar29 = param_1;
  }
  param_2 = param_2 / dVar29;
  _objc_msgSend(IVar9,"setStoredEndTime:",param_2);
  _objc_msgSend(IVar9,"setEndFade:",(ulong)((uint)local_2d0 & 1));
  _objc_msgSend(IVar9,"setStoredTransition:",0);
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  FUN_1001726d0(DAT_100b757a8);
  _objc_msgSend(IVar9,"setMasterVolumeLevel:",param_2);
  _objc_msgSend(IVar9,"setStoredSMPTEEnabled:",(ulong)((uint)local_2c0 & 1));
  pcVar27 = local_2e8;
  if (((ulong)local_2b8 & 1) == 0) {
    puVar19 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar8 = _objc_msgSend((ID)puVar19,"initWithDouble:",pcVar27);
    _objc_msgSend(IVar9,"setStoredSMPTETimelineLocation:",IVar8);
  }
  else {
    _objc_msgSend(IVar9,"setStoredSMPTETimelineLocation:",0);
  }
  uVar15 = 0;
  if ((local_2a8 & 1) == 0) {
    uVar15 = param_15;
  }
  _objc_msgSend(IVar9,"setMidiBankID:",uVar15);
  FUN_100023be4(uVar21,&DAT_100aff678);
  return IVar9;
}

// ==== 100343d80 FUN_100343d80 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8
FUN_100343d80(double param_1,double *param_2,undefined8 param_3,undefined *param_4,
             undefined8 param_5)

{
  byte bVar1;
  uint3 uVar2;
  bool bVar3;
  uint uVar4;
  long lVar5;
  undefined **ppuVar6;
  ID IVar7;
  undefined *puVar8;
  ID IVar9;
  undefined8 *puVar10;
  undefined *puVar11;
  undefined *self;
  undefined1 *puVar12;
  ulong uVar13;
  long lVar14;
  long *plVar15;
  ID unaff_x20;
  undefined1 *puVar16;
  undefined8 uVar17;
  undefined *puVar18;
  double dVar19;
  double *pdVar20;
  ulong uVar21;
  code *pcVar22;
  double dVar23;
  long lVar24;
  long lVar25;
  undefined *puVar26;
  long lVar27;
  undefined **ppuVar28;
  undefined *puVar29;
  undefined8 uVar30;
  undefined1 auStack_210 [8];
  undefined1 *local_208;
  long local_200;
  undefined *local_1f8;
  long local_1f0;
  code *local_1e8;
  long local_1e0;
  long local_1d8;
  undefined8 local_1d0;
  long local_1c8;
  long local_1c0;
  double *local_1b8;
  undefined *local_1b0;
  undefined *local_1a8;
  undefined **local_1a0;
  undefined *local_198;
  undefined8 local_180;
  undefined8 auStack_178 [4];
  long lStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined2 local_140;
  double local_130;
  double local_128;
  char local_120;
  byte local_11f;
  undefined8 local_88;
  undefined *local_80;
  
  local_1c0 = 0;
  puVar8 = &DAT_100af7568;
  local_1d0 = param_3;
  FUN_100021774();
  uVar13 = *(long *)(*(long *)(puVar8 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  puVar16 = auStack_210 + -uVar13;
  local_1f0 = (long)puVar16 - uVar13;
  lVar25 = local_1f0 - uVar13;
  lVar5 = 0;
  local_198 = (undefined *)(lVar25 - uVar13);
  FUN_1004da4ec();
  lVar14 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar24 = *(long *)(lVar5 + -8);
  lVar27 = (long)(lVar25 - uVar13) - (*(long *)(lVar24 + 0x40) + 0xfU & 0xfffffffffffffff0);
  local_208 = puVar16;
  local_1f8 = param_4;
  local_1c8 = lVar5;
  local_1b8 = param_2;
  if (param_4 == (undefined *)0x0) {
    puVar8 = *(undefined **)(unaff_x20 + _TtC8Playback4Song::privateWorkingCopyArrangement);
    if (puVar8 == (undefined *)0x0) {
      IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
      if (IVar7 != 0) {
        ppuVar28 = &PTR_s_arrangements_100aa0c98;
        FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                      PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                      ,FUN_1002eda7c,FUN_10078e138);
        lVar5 = local_1c0;
        ppuVar6 = ppuVar28;
        FUN_1005e3b94(ppuVar28,IVar7);
        local_1c0 = lVar5;
        local_1a0 = ppuVar6;
        _swift_bridgeObjectRelease(ppuVar28);
        param_2 = local_1b8;
        if (local_1a0 != (undefined **)0x0) {
          *(undefined ***)(unaff_x20 + lVar14) = local_1a0;
          puVar8 = (undefined *)0x0;
          goto LAB_100343e6c;
        }
      }
      local_1f8 = PTR___swiftEmptyArrayStorage_100a1e050;
      _swift_retain();
    }
    else {
LAB_100343e6c:
      param_2 = local_1b8;
      FUN_1002dc2dc();
      local_1f8 = puVar8;
    }
  }
  _swift_bridgeObjectRetain();
  FUN_100325e68();
  if (param_4 != (undefined *)0x0) {
    lVar14 = *(long *)(param_4 + 0x10);
    if (lVar14 != 0) {
      lVar5 = ((ulong)*(byte *)(lVar24 + 0x50) + 0x20 &
              ((ulong)*(byte *)(lVar24 + 0x50) ^ 0xffffffffffffffff)) +
              (long)*(int *)(local_1c8 + 0x58);
      do {
        if (*(long *)(param_4 + lVar5) ==
            *(long *)((long)param_2 + (long)*(int *)(local_1c8 + 0x58))) {
          _swift_bridgeObjectRelease();
          goto LAB_100344050;
        }
        lVar5 = lVar5 + *(long *)(lVar24 + 0x48);
        lVar14 = lVar14 + -1;
      } while (lVar14 != 0);
    }
    _swift_bridgeObjectRelease();
    FUN_100325e68();
    if (param_4 == (undefined *)0x0) {
      FUN_1003267c8();
    }
    else {
      FUN_100023384(param_2,lVar27,FUN_1004da4ec);
      puVar8 = param_4;
      _swift_isUniquelyReferenced_nonNull_native();
      puVar11 = param_4;
      if (((ulong)puVar8 & 1) == 0) {
        puVar11 = (undefined *)0x0;
        FUN_10078fa94(0,*(long *)(param_4 + 0x10) + 1,1,param_4);
      }
      uVar13 = *(ulong *)(puVar11 + 0x10);
      puVar8 = puVar11;
      if (*(ulong *)(puVar11 + 0x18) >> 1 <= uVar13) {
        puVar8 = (undefined *)(ulong)(1 < *(ulong *)(puVar11 + 0x18));
        FUN_10078fa94(puVar8,uVar13 + 1,1,puVar11);
      }
      *(ulong *)(puVar8 + 0x10) = uVar13 + 1;
      FUN_100023340(lVar27,puVar8 + *(long *)(lVar24 + 0x48) * uVar13 +
                                    ((ulong)*(byte *)(lVar24 + 0x50) + 0x20 &
                                    ((ulong)*(byte *)(lVar24 + 0x50) ^ 0xffffffffffffffff)),
                    FUN_1004da4ec);
      FUN_1003267c8(puVar8);
      param_2 = local_1b8;
    }
  }
LAB_100344050:
  lVar14 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  local_1d8 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  if (*(long *)(unaff_x20 + _TtC8Playback4Song::privateWorkingCopyArrangement) == 0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 != 0) {
      ppuVar28 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar6 = ppuVar28;
      FUN_1005e3b94(ppuVar28,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar28);
      param_2 = local_1b8;
      lVar14 = local_1d8;
      if (ppuVar6 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar6;
        goto LAB_100344064;
      }
    }
  }
  else {
LAB_100344064:
    lVar14 = local_1d8;
    FUN_1002ea0d8(param_2);
  }
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar7 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar7);
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 == 0) goto LAB_1003442d0;
    ppuVar6 = &PTR_s_arrangements_100aa0c98;
    FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                  PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8,
                  FUN_1002eda7c,FUN_10078e138);
    lVar14 = local_1c0;
    ppuVar28 = ppuVar6;
    FUN_1005e3b94(ppuVar6,IVar7);
    local_1c0 = lVar14;
    _swift_bridgeObjectRelease(ppuVar6);
    lVar14 = local_1d8;
    param_2 = local_1b8;
    if (ppuVar28 != (undefined **)0x0) {
      *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
      goto LAB_1003440c4;
    }
    ppuVar28 = *(undefined ***)(unaff_x20 + local_1d8);
    if (ppuVar28 == (undefined **)0x0) goto LAB_100345288;
LAB_1003442dc:
    FUN_10003b4b4(param_5,&local_180,&DAT_100b00070);
    if (lStack_158 == 0) {
      FUN_100023be4(&local_180,&DAT_100b00070);
LAB_100344334:
      dVar19 = param_2[1];
    }
    else {
      FUN_100313fa8(&local_180);
      dVar19 = local_128;
      if (local_120 == '\x01') goto LAB_100344334;
    }
    IVar7 = _objc_msgSend((ID)ppuVar28,"song");
    if (IVar7 == 0) {
      param_1 = 1.0;
    }
    else {
      FUN_1003220ec();
    }
    puVar8 = local_198;
    param_1 = dVar19 / param_1;
    _objc_msgSend((ID)ppuVar28,"setStoredEndTime:",param_1);
  }
  else {
LAB_1003440c4:
    FUN_10003b4b4(param_5,&local_180,&DAT_100b00070);
    if (lStack_158 == 0) {
      FUN_100023be4(&local_180,&DAT_100b00070);
      dVar19 = *param_2;
    }
    else {
      FUN_100313fa8(&local_180);
      dVar19 = local_130;
    }
    IVar7 = _objc_msgSend((ID)ppuVar28,"song");
    if (IVar7 == 0) {
      param_1 = 1.0;
    }
    else {
      FUN_1003220ec();
    }
    param_1 = dVar19 / param_1;
    _objc_msgSend((ID)ppuVar28,"setStoredStartTime:",param_1);
LAB_1003442d0:
    ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
    if (ppuVar28 != (undefined **)0x0) goto LAB_1003442dc;
LAB_100345288:
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    puVar8 = local_198;
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      param_2 = local_1b8;
      lVar14 = local_1d8;
      puVar8 = local_198;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        goto LAB_1003442dc;
      }
    }
  }
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      param_2 = local_1b8;
      lVar14 = local_1d8;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        goto LAB_100344398;
      }
    }
  }
  else {
LAB_100344398:
    FUN_10003b4b4(param_5,&local_180,&DAT_100b00070);
    if (lStack_158 == 0) {
      FUN_100023be4(&local_180,&DAT_100b00070);
      local_11f = *(byte *)((long)param_2 + 0x11);
    }
    else {
      FUN_100313fa8(&local_180);
    }
    _objc_msgSend((ID)ppuVar28,"setEndFade:",(ulong)local_11f);
  }
  if (DAT_100adea10 != -1) {
    _swift_once(&DAT_100adea10,FUN_1001709a4);
  }
  uVar13 = DAT_100b757a8;
  FUN_100171514();
  if ((uVar13 & 1) != 0) {
    ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
    if (ppuVar28 == (undefined **)0x0) {
      IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
      if (IVar7 != 0) {
        ppuVar6 = &PTR_s_arrangements_100aa0c98;
        FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                      PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                      ,FUN_1002eda7c,FUN_10078e138);
        lVar14 = local_1c0;
        ppuVar28 = ppuVar6;
        FUN_1005e3b94(ppuVar6,IVar7);
        local_1c0 = lVar14;
        _swift_bridgeObjectRelease(ppuVar6);
        param_2 = local_1b8;
        lVar14 = local_1d8;
        if (ppuVar28 != (undefined **)0x0) {
          *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
          goto LAB_1003444f8;
        }
      }
    }
    else {
LAB_1003444f8:
      param_1 = param_2[3];
      _objc_msgSend((ID)ppuVar28,"setMasterVolumeLevel:",param_1);
    }
  }
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      param_2 = local_1b8;
      lVar14 = local_1d8;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        goto LAB_100344528;
      }
    }
  }
  else {
LAB_100344528:
    uVar4 = 0;
    if (*(byte *)(param_2 + 2) != 5) {
      uVar4 = (uint)*(byte *)(param_2 + 2);
    }
    _objc_msgSend((ID)ppuVar28,"setStoredTransition:",(ulong)uVar4);
  }
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      lVar14 = local_1d8;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        param_2 = local_1b8;
        goto LAB_100344560;
      }
    }
  }
  else {
LAB_100344560:
    _objc_msgSend((ID)ppuVar28,"setTransitionContinuePad:",
                  (ulong)(*(byte *)((long)param_2 + (long)*(int *)(local_1c8 + 0x68)) & 1));
  }
  FUN_10003b4b4(local_1d0,puVar8,&DAT_100af7568);
  lVar5 = 0;
  FUN_10020acbc();
  local_200 = *(long *)(lVar5 + -8);
  local_1e8 = *(code **)(local_200 + 0x30);
  puVar11 = puVar8;
  local_1e0 = lVar5;
  (*local_1e8)(puVar8,1);
  if ((int)puVar11 == 1) {
    FUN_100023be4(puVar8,&DAT_100af7568);
    puVar10 = (undefined8 *)((long)local_1b8 + (long)*(int *)(local_1c8 + 0x74));
    if ((*(byte *)(puVar10 + 1) & 1) == 0) {
      uVar17 = *puVar10;
      goto LAB_10034461c;
    }
  }
  else {
    uVar17 = *(undefined8 *)(puVar8 + 0x90);
    FUN_1000233c8(puVar8,FUN_10020acbc);
LAB_10034461c:
    puVar8 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar7 = _objc_msgSend((ID)puVar8,"initWithInteger:",uVar17);
    _objc_msgSend(unaff_x20,"setMidiProPresenterPlaylist:",IVar7);
  }
  FUN_10003b4b4(local_1d0,lVar25,&DAT_100af7568);
  lVar5 = lVar25;
  (*local_1e8)(lVar25,1,local_1e0);
  if ((int)lVar5 == 1) {
    FUN_100023be4(lVar25,&DAT_100af7568);
    puVar10 = (undefined8 *)((long)local_1b8 + (long)*(int *)(local_1c8 + 0x78));
    if ((*(byte *)(puVar10 + 1) & 1) == 0) {
      uVar17 = *puVar10;
      goto LAB_1003446c0;
    }
  }
  else {
    uVar17 = *(undefined8 *)(lVar25 + 0x98);
    FUN_1000233c8(lVar25,FUN_10020acbc);
LAB_1003446c0:
    puVar8 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar7 = _objc_msgSend((ID)puVar8,"initWithInteger:",uVar17);
    _objc_msgSend(unaff_x20,"setMidiProPresenterPlaylistItem:",IVar7);
  }
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    pdVar20 = local_1b8;
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      pdVar20 = local_1b8;
      lVar14 = local_1d8;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        goto LAB_100344700;
      }
    }
  }
  else {
LAB_100344700:
    pdVar20 = local_1b8;
    param_1 = 0.0;
    if (*(char *)(local_1b8 + 0xb) == '\0') {
      param_1 = local_1b8[10];
    }
    _objc_msgSend((ID)ppuVar28,"setSmpteStartTime:",param_1);
  }
  ppuVar28 = *(undefined ***)(unaff_x20 + lVar14);
  if (ppuVar28 == (undefined **)0x0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 != 0) {
      ppuVar6 = &PTR_s_arrangements_100aa0c98;
      FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                    PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                    ,FUN_1002eda7c,FUN_10078e138);
      lVar14 = local_1c0;
      ppuVar28 = ppuVar6;
      FUN_1005e3b94(ppuVar6,IVar7);
      local_1c0 = lVar14;
      _swift_bridgeObjectRelease(ppuVar6);
      pdVar20 = local_1b8;
      if (ppuVar28 != (undefined **)0x0) {
        *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
        goto LAB_100344744;
      }
    }
  }
  else {
LAB_100344744:
    FUN_10032c634(0);
    puVar8 = &_OBJC_CLASS___NSNumber;
    _objc_allocWithZone();
    IVar7 = _objc_msgSend((ID)puVar8,"initWithDouble:",param_1);
    _objc_msgSend((ID)ppuVar28,"setStoredSMPTETimelineLocation:",IVar7);
  }
  puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar18 = (undefined *)pdVar20[7];
  puVar11 = puVar18;
  if (puVar18 == (undefined *)0x0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    puVar11 = puVar8;
  }
  local_1a0 = *(undefined ***)(puVar11 + 0x10);
  if (local_1a0 == (undefined **)0x0) {
    _swift_bridgeObjectRetain(puVar18);
    _swift_bridgeObjectRelease(puVar11);
  }
  else {
    local_1a8 = puVar11 + 0x20;
    _swift_bridgeObjectRetain(puVar18);
    puVar8 = (undefined *)0x0;
    local_1b0 = puVar11;
    do {
      if (*(undefined **)(local_1b0 + 0x10) <= puVar8) {
                    /* WARNING: Does not return */
        pcVar22 = (code *)SoftwareBreakpoint(1,0x1003453a4);
        (*pcVar22)();
      }
      plVar15 = (long *)(local_1a8 + (long)puVar8 * 0x30);
      lVar5 = *plVar15;
      lVar24 = plVar15[4];
      local_198 = (undefined *)CONCAT44(local_198._4_4_,(uint)*(byte *)(plVar15 + 5));
      lVar14 = plVar15[3];
      _swift_bridgeObjectRetain();
      IVar7 = _objc_msgSend(unaff_x20,"storedSongGenres");
      if (IVar7 == 0) {
LAB_100344c68:
        puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain();
      }
      else {
        IVar9 = _objc_msgSend(IVar7,"allObjects");
        __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                  (IVar9,PTR___sypN_100a1e038 + 8);
        uVar17 = *(undefined8 *)(IVar9 + 0x10);
        local_80 = PTR___swiftEmptyArrayStorage_100a1e050;
        _swift_retain();
        FUN_1001cc35c(0,uVar17,0);
        IVar7 = IVar9;
        puVar11 = local_80;
        for (lVar25 = *(long *)(IVar9 + 0x10); local_80 = puVar11, lVar25 != 0; lVar25 = lVar25 + -1
            ) {
          IVar7 = IVar7 + 0x20;
          FUN_10003b4f8(IVar7,&local_180);
          uVar17 = 0;
          FUN_10065ad50(0);
          puVar10 = &local_88;
          _swift_dynamicCast(puVar10,&local_180,PTR___sypN_100a1e038 + 8,uVar17,6);
          uVar17 = local_88;
          if ((int)puVar10 == 0) {
            _swift_release(puVar11);
            local_88 = 0;
            _swift_bridgeObjectRelease(IVar9);
            goto LAB_100344c68;
          }
          uVar13 = *(ulong *)(puVar11 + 0x10);
          local_80 = puVar11;
          if (*(ulong *)(puVar11 + 0x18) >> 1 <= uVar13) {
            FUN_1001cc35c(1 < *(ulong *)(puVar11 + 0x18),uVar13 + 1,1);
          }
          *(ulong *)(local_80 + 0x10) = uVar13 + 1;
          *(undefined8 *)(local_80 + uVar13 * 8 + 0x20) = uVar17;
          puVar11 = local_80;
        }
        _swift_bridgeObjectRelease(IVar9);
      }
      if ((ulong)puVar11 >> 0x3e == 0) {
        puVar18 = *(undefined **)(((ulong)puVar11 & 0xfffffffffffff8) + 0x10);
        if (puVar18 == (undefined *)0x0) goto LAB_100344ac4;
LAB_100344c8c:
        _swift_bridgeObjectRetain(puVar11);
        lVar25 = 4;
        do {
          IVar7 = lVar25 - 4;
          if (((ulong)puVar11 & 0xc000000000000001) == 0) {
            IVar9 = *(ID *)(puVar11 + lVar25 * 8);
          }
          else {
            IVar9 = IVar7;
            FUN_1000cbf38(IVar7,puVar11);
          }
          puVar29 = (undefined *)(lVar25 + -3);
          if (SCARRY8(IVar7,1)) {
                    /* WARNING: Does not return */
            pcVar22 = (code *)SoftwareBreakpoint(1,0x10034538c);
            (*pcVar22)();
          }
          IVar7 = _objc_msgSend(IVar9,"genreID");
          if (lVar5 == (int)IVar7) {
            _swift_bridgeObjectRelease_n(puVar11,2);
            _objc_msgSend(IVar9,"setVolume:",lVar24);
            _swift_bridgeObjectRelease(lVar14);
            _objc_msgSend(IVar9,"setMuted:",(ulong)local_198 & 0xffffffff);
            goto LAB_100344ad4;
          }
          lVar25 = lVar25 + 1;
        } while (puVar29 != puVar18);
        _swift_bridgeObjectRelease(lVar14);
        _swift_bridgeObjectRelease_n(puVar11,2);
      }
      else {
        puVar18 = (undefined *)((ulong)puVar11 & 0xffffffffffffff8);
        if ((long)puVar11 < 0) {
          puVar18 = puVar11;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        if (puVar18 != (undefined *)0x0) goto LAB_100344c8c;
LAB_100344ac4:
        _swift_bridgeObjectRelease(lVar14);
        _swift_bridgeObjectRelease(puVar11);
      }
LAB_100344ad4:
      puVar8 = puVar8 + 1;
    } while ((undefined **)puVar8 != local_1a0);
    _swift_bridgeObjectRelease(local_1b0);
    pdVar20 = local_1b8;
  }
  lVar14 = local_1f0;
  dVar19 = pdVar20[6];
  (**(code **)(local_200 + 0x38))(local_1f0,1,1,local_1e0);
  puVar8 = local_1f8;
  bVar1 = *(byte *)((long)pdVar20 + (long)*(int *)(local_1c8 + 0x7c));
  pcVar22 = (code *)(ulong)bVar1;
  FUN_100327b8c(local_1f8,dVar19,lVar14);
  _swift_bridgeObjectRelease(puVar8);
  FUN_100023be4(lVar14,&DAT_100af7568);
  uVar13 = 0x15;
  thunk_FUN_1002db810(0x15,PTR___swiftEmptyArrayStorage_100a1e050);
  if ((uVar13 & 1) == 0) {
    if (DAT_100ae0030 != -1) {
      _swift_once(&DAT_100ae0030,FUN_1008174c0);
    }
    uVar13 = 1;
    FUN_100819fe0();
    if ((uVar13 & 1) != 0) goto LAB_100344e2c;
  }
  else {
LAB_100344e2c:
    uVar13 = DAT_100b757a8;
    FUN_1001714e4();
    if ((((uint)bVar1 | (uint)uVar13 ^ 0xffffffff) & 1) == 0) {
      ppuVar28 = *(undefined ***)(unaff_x20 + local_1d8);
      if (ppuVar28 == (undefined **)0x0) {
        IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
        if (IVar7 != 0) {
          ppuVar6 = &PTR_s_arrangements_100aa0c98;
          pcVar22 = FUN_10078e138;
          FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                        PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                        ,FUN_1002eda7c);
          lVar14 = local_1c0;
          ppuVar28 = ppuVar6;
          FUN_1005e3b94(ppuVar6,IVar7);
          local_1c0 = lVar14;
          _swift_bridgeObjectRelease(ppuVar6);
          pdVar20 = local_1b8;
          if (ppuVar28 != (undefined **)0x0) {
            *(undefined ***)(unaff_x20 + local_1d8) = ppuVar28;
            goto LAB_100344e64;
          }
        }
      }
      else {
LAB_100344e64:
        IVar7 = _objc_msgSend((ID)ppuVar28,"storedBuses");
        if (IVar7 != 0) {
          puVar11 = (undefined *)_objc_msgSend(IVar7,"array");
          __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                    (puVar11,PTR___sypN_100a1e038 + 8);
          puVar8 = puVar11;
          FUN_1002d7d64();
          _swift_bridgeObjectRelease(puVar11);
          if (puVar8 != (undefined *)0x0) {
            ppuVar28 = (undefined **)((ulong)puVar8 & 0xffffffffffffff8);
            if ((ulong)puVar8 >> 0x3e == 0) {
              puVar11 = *(undefined **)((long)ppuVar28 + 0x10);
            }
            else {
              puVar11 = puVar8;
              if (-1 < (long)puVar8) {
                puVar11 = (undefined *)ppuVar28;
              }
              __ss18_CocoaArrayWrapperV8endIndexSivg();
            }
            if (puVar11 != (undefined *)0x0) {
              puVar29 = (undefined *)0x0;
              puVar26 = (undefined *)((ulong)puVar8 & 0xc000000000000001);
              puVar18 = puVar8 + 0x20;
              local_1b0 = puVar26;
              local_1a8 = puVar11;
              local_1a0 = ppuVar28;
              local_198 = puVar18;
              do {
                if (puVar26 == (undefined *)0x0) {
                  if (*(undefined **)((long)ppuVar28 + 0x10) <= puVar29) {
                    /* WARNING: Does not return */
                    pcVar22 = (code *)SoftwareBreakpoint(1,0x1003453dc);
                    (*pcVar22)();
                  }
                  self = *(undefined **)(puVar18 + (long)puVar29 * 8);
                }
                else {
                  self = puVar29;
                  FUN_1000cce70(puVar29,puVar8);
                }
                bVar3 = SCARRY8((long)puVar29,1);
                puVar29 = puVar29 + 1;
                if (bVar3) {
                    /* WARNING: Does not return */
                  pcVar22 = (code *)SoftwareBreakpoint(1,0x1003453a8);
                  (*pcVar22)();
                }
                IVar7 = _objc_msgSend((ID)self,"id");
                uVar4 = (uint)IVar7;
                FUN_10055ee18();
                if ((((0x14 < (uVar4 & 0xff)) ||
                     (((1 << (ulong)(uVar4 & 0x1f) & 0x21801U) == 0 && ((uVar4 & 0xff) != 0x14))))
                    && (dVar19 = pdVar20[8], dVar19 != 0.0)) &&
                   (lVar14 = *(long *)((long)dVar19 + 0x10), puVar18 = local_198, lVar14 != 0)) {
                  _swift_bridgeObjectRetain_n(dVar19,2);
                  puVar10 = (undefined8 *)((long)dVar19 + 0x40);
                  do {
                    uVar30 = puVar10[-3];
                    bVar1 = *(byte *)(puVar10 + -2);
                    uVar17 = *puVar10;
                    uVar21 = puVar10[-4];
                    uVar13 = 0x14;
                    if (uVar21 < 0x14) {
                      uVar13 = uVar21;
                    }
                    _swift_bridgeObjectRetain(uVar17);
                    IVar7 = _objc_msgSend((ID)self,"id");
                    pdVar20 = local_1b8;
                    if ((uint)IVar7 < 5 || ((uint)IVar7 - 5 & 0xffff) < 0xf) {
                      if (uVar21 < 0x14) {
                        uVar21 = IVar7 & 0xffff;
LAB_100344fd0:
                        if (uVar13 == uVar21) {
                          _swift_bridgeObjectRelease_n(dVar19,2);
                          _objc_msgSend((ID)self,"setVolume:",uVar30);
                          _swift_bridgeObjectRelease(uVar17);
                          _objc_msgSend((ID)self,"setMuted:",(ulong)bVar1);
                          puVar18 = local_198;
                          ppuVar28 = local_1a0;
                          puVar11 = local_1a8;
                          puVar26 = local_1b0;
                          goto LAB_100344f30;
                        }
                      }
                    }
                    else if (uVar21 < 0x14) {
                      uVar21 = 0;
                      goto LAB_100344fd0;
                    }
                    puVar10 = puVar10 + 5;
                    _swift_bridgeObjectRelease(uVar17);
                    lVar14 = lVar14 + -1;
                  } while (lVar14 != 0);
                  _swift_bridgeObjectRelease_n(dVar19,2);
                  puVar18 = local_198;
                  ppuVar28 = local_1a0;
                  puVar11 = local_1a8;
                  puVar26 = local_1b0;
                }
LAB_100344f30:
              } while (puVar29 != puVar11);
            }
            _swift_bridgeObjectRelease(puVar8);
          }
        }
      }
    }
  }
  FUN_10034e664(pdVar20);
  puVar16 = local_208;
  FUN_10003b4b4(local_1d0,local_208,&DAT_100af7568);
  uVar17 = 1;
  puVar12 = puVar16;
  lVar14 = local_1e0;
  (*local_1e8)(puVar16,1);
  if ((int)puVar12 == 1) {
    FUN_100023be4(puVar16,&DAT_100af7568);
    goto LAB_1003454f4;
  }
  uVar4 = (uint)*(ushort *)(puVar16 + 0x28);
  FUN_100419df0();
  lVar5 = local_1c0;
  if ((((uVar4 & 0xff) == 0xd) && ((puVar16[0xa8] & 1) == 0)) &&
     (lVar24 = *(long *)(puVar16 + 0xa0), lVar24 != 0)) {
    FUN_100571c08();
    uVar4 = (uint)lVar24;
    if (lVar5 != 0) {
      _swift_errorRelease(lVar5);
      local_1c0 = 0;
      pdVar20 = local_1b8;
      goto LAB_1003454e4;
    }
    local_1c0 = lVar5;
    FUN_100571458();
    FUN_1000233c8(puVar16,FUN_10020acbc);
    pdVar20 = local_1b8;
    if (pcVar22 != (code *)0x0) {
      _swift_bridgeObjectRetain(pcVar22);
      FUN_10055faec(lVar14,pcVar22);
      if (((uint)lVar14 & 0xff) == 0x14) {
        _swift_bridgeObjectRelease(pcVar22);
      }
      else {
        if (*(long *)(unaff_x20 + local_1d8) == 0) {
          IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
          if (IVar7 != 0) {
            ppuVar28 = &PTR_s_arrangements_100aa0c98;
            FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                          PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8
                          ,FUN_1002eda7c,FUN_10078e138);
            lVar5 = local_1c0;
            ppuVar6 = ppuVar28;
            FUN_1005e3b94(ppuVar28,IVar7);
            local_1c0 = lVar5;
            _swift_bridgeObjectRelease(ppuVar28);
            pdVar20 = local_1b8;
            if (ppuVar6 != (undefined **)0x0) {
              *(undefined ***)(unaff_x20 + local_1d8) = ppuVar6;
              goto LAB_1003457a4;
            }
          }
        }
        else {
LAB_1003457a4:
          FUN_1002e3e90(uVar4 & 1);
        }
        FUN_10032bcf0(uVar17,0);
        _swift_bridgeObjectRelease(pcVar22);
        FUN_10032be28(lVar14);
        _objc_msgSend(unaff_x20,"setClickTimes:",0);
      }
    }
  }
  else {
LAB_1003454e4:
    FUN_1000233c8(puVar16,FUN_10020acbc);
  }
LAB_1003454f4:
  dVar19 = pdVar20[0x10];
  if (dVar19 == 4.94065645841247e-324) goto LAB_100345550;
  uVar2 = *(uint3 *)(pdVar20 + 0x11);
  dVar23 = pdVar20[0xf];
  if (*(long *)(unaff_x20 + local_1d8) == 0) {
    IVar7 = _objc_msgSend(unaff_x20,"workingCopyArrangementID");
    if (IVar7 == 0) goto LAB_100345550;
    ppuVar28 = &PTR_s_arrangements_100aa0c98;
    FUN_10032eeac(&PTR_s_arrangements_100aa0c98,
                  PTR___sSo5NSSetC10FoundationE12makeIteratorAC017NSFastEnumerationD0VyF_100a1e2f8,
                  FUN_1002eda7c,FUN_10078e138);
    ppuVar6 = ppuVar28;
    FUN_1005e3b94(ppuVar28,IVar7);
    _swift_bridgeObjectRelease(ppuVar28);
    pdVar20 = local_1b8;
    if (ppuVar6 == (undefined **)0x0) goto LAB_100345550;
    *(undefined ***)(unaff_x20 + local_1d8) = ppuVar6;
  }
  FUN_1002e9b7c((ulong)dVar23 & 0xffff0000ffffffff | ((ulong)dVar23 >> 0x20 & 1) << 0x20,dVar19,
                uVar2 & 0x10101);
  pdVar20 = local_1b8;
LAB_100345550:
  puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar11 = (undefined *)pdVar20[0xe];
  if (puVar11 == (undefined *)0x0) {
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    lVar14 = *(long *)(puVar8 + 0x10);
  }
  else {
    lVar14 = *(long *)(puVar11 + 0x10);
    puVar8 = puVar11;
  }
  if (lVar14 == 0) {
    _swift_bridgeObjectRetain(puVar11);
  }
  else {
    FUN_100823c68(0);
    _swift_bridgeObjectRetain(puVar11);
    _swift_bridgeObjectRetain(puVar8);
    lVar5 = 0x20;
    do {
      puVar10 = (undefined8 *)(puVar8 + lVar5);
      auStack_178[0] = puVar10[1];
      local_180 = *puVar10;
      auStack_178[2] = puVar10[3];
      auStack_178[1] = puVar10[2];
      lStack_158 = puVar10[5];
      auStack_178[3] = puVar10[4];
      uStack_148 = puVar10[7];
      uStack_150 = puVar10[6];
      local_140 = *(undefined2 *)(puVar10 + 8);
      FUN_1002f9a10(&local_180);
      FUN_1002f9a10(&local_180);
      FUN_100822c4c(&local_180,unaff_x20);
      FUN_1002f9a58(&local_180);
      lVar5 = lVar5 + 0x48;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    _swift_bridgeObjectRelease(puVar8);
  }
  _swift_bridgeObjectRelease(puVar8);
  IVar7 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar7);
  return 0;
}

// ==== 10038af08 _TtC8Playback33TracksBusesSettingsViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback33TracksBusesSettingsViewController::
viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback33TracksBusesSettingsViewController *this,ID param_1,SEL param_2,
          CGSize param_3,ID param_4)

{
  class_t *pcVar1;
  ID IVar2;
  double dVar3;
  objc_super local_60;
  
  dVar3 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  IVar2 = param_1 + collectionView;
  _swift_unknownObjectWeakLoadStrong();
  _swift_unknownObjectRetain(dVar3);
  if (IVar2 != 0) {
    IVar2 = _objc_msgSend(IVar2,"collectionViewLayout");
    _objc_msgSend(IVar2,"invalidateLayout");
  }
  local_60.receiver = param_1;
  local_60.super_class = pcVar1;
  _objc_msgSendSuper2(&local_60,"viewWillTransitionToSize:withTransitionCoordinator:",dVar3);
  _swift_unknownObjectRelease(dVar3);
  return;
}

// ==== 100398264 FUN_100398264 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_100398264(undefined8 param_1,double param_2)

{
  undefined *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  double dVar6;
  long lVar7;
  code *pcVar8;
  char cVar9;
  undefined1 uVar10;
  uint uVar11;
  int iVar12;
  ID IVar13;
  undefined *puVar14;
  undefined *puVar15;
  ID IVar16;
  undefined *puVar17;
  undefined *puVar18;
  ID IVar19;
  ID IVar20;
  ID IVar21;
  undefined *puVar22;
  undefined8 uVar23;
  undefined *puVar24;
  ulong uVar25;
  ulong uVar26;
  long unaff_x20;
  undefined *puVar27;
  ulong uVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  double dVar32;
  undefined *local_128;
  uint local_e8;
  undefined *local_e0;
  undefined1 auStack_c0 [32];
  
  lVar5 = _TtC8Playback21SetlistViewController::setlistCollectionView;
  IVar13 = unaff_x20 + _TtC8Playback21SetlistViewController::setlistCollectionView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar13 == 0) {
                    /* WARNING: Does not return */
    pcVar8 = (code *)SoftwareBreakpoint(1,0x100399080);
    (*pcVar8)();
  }
  IVar13 = _objc_msgSend(IVar13,"isDragging");
  if ((IVar13 & 1) != 0) {
LAB_1003982f8:
    *(undefined1 *)(unaff_x20 + _TtC8Playback21SetlistViewController::requiresOverlayRefresh) = 1;
    return;
  }
  IVar13 = unaff_x20 + lVar5;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar13 == 0) {
                    /* WARNING: Does not return */
    pcVar8 = (code *)SoftwareBreakpoint(1,0x100399084);
    (*pcVar8)();
  }
  IVar13 = _objc_msgSend(IVar13,"isDecelerating");
  if ((IVar13 & 1) != 0) goto LAB_1003982f8;
  FUN_10039a83c(0);
  if (DAT_100adfbb8 != -1) {
    _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
  }
  lVar7 = DAT_100b77548;
  lVar4 = _TtC8Playback21SetlistViewController::currentSetlist;
  uVar28 = *(ulong *)(DAT_100b77548 + 0x10);
  if (uVar28 >> 0x3e == 2 && (uVar28 + 0x7fffffffffffffe8 & 0xffffffffffffffef) == 0) {
    return;
  }
  _swift_beginAccess(unaff_x20 + _TtC8Playback21SetlistViewController::currentSetlist,auStack_c0,0,0
                    );
  uVar25 = *(ulong *)(unaff_x20 + lVar4);
  if (uVar25 == 0) {
    _swift_retain(lVar7);
LAB_100398f04:
    uVar25 = *(ulong *)(unaff_x20 + _TtC8Playback21SetlistViewController::addButtons);
    if (uVar25 >> 0x3e == 0) {
      IVar13 = *(ID *)((uVar25 & 0xfffffffffffff8) + 0x10);
    }
    else {
      IVar13 = uVar25 & 0xffffffffffffff8;
      if ((long)uVar25 < 0) {
        IVar13 = uVar25;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (IVar13 == 0) {
      _swift_release(lVar7);
      return;
    }
    if ((long)IVar13 < 1) {
                    /* WARNING: Does not return */
      pcVar8 = (code *)SoftwareBreakpoint(1,0x10039905c);
      (*pcVar8)();
    }
    _swift_bridgeObjectRetain_n(uVar25,2);
    IVar21 = 0;
    do {
      if ((uVar25 & 0xc000000000000001) == 0) {
        IVar16 = *(ID *)(uVar25 + IVar21 * 8 + 0x20);
      }
      else {
        IVar16 = IVar21;
        FUN_1000cd438(IVar21,uVar25);
      }
      IVar21 = IVar21 + 1;
      _objc_msgSend(IVar16,"setHidden:",(ulong)(uVar28 != 0x8000000000000030));
    } while (IVar13 != IVar21);
    _swift_release(lVar7);
    _swift_bridgeObjectRelease_n(uVar25,2);
    return;
  }
  _swift_retain(lVar7);
  FUN_1004a6154();
  if (uVar25 >> 0x3e == 0) {
    uVar26 = *(ulong *)((uVar25 & 0xfffffffffffff8) + 0x10);
    _swift_bridgeObjectRelease();
    puVar14 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    uVar26 = uVar25 & 0xffffffffffffff8;
    if ((long)uVar25 < 0) {
      uVar26 = uVar25;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    _swift_bridgeObjectRelease(uVar25);
    puVar14 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar14;
  if (uVar26 == 0) goto LAB_100398f04;
  _swift_retain_n(puVar14,2);
  FUN_1004a6154();
  if ((ulong)puVar14 >> 0x3e == 0) {
    puVar27 = *(undefined **)(((ulong)puVar14 & 0xfffffffffffff8) + 0x10);
    puVar24 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_128 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_e0 = puVar27;
    if (puVar27 == (undefined *)0x0) goto LAB_100398dc0;
  }
  else {
    local_e0 = (undefined *)((ulong)puVar14 & 0xffffffffffffff8);
    if ((long)puVar14 < 0) {
      local_e0 = puVar14;
    }
    puVar27 = local_e0;
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    puVar24 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_128 = PTR___swiftEmptyArrayStorage_100a1e050;
    if (puVar27 == (undefined *)0x0) goto LAB_100398dc0;
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  _swift_bridgeObjectRetain(puVar14);
  IVar13 = 0;
  local_128 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar24 = PTR___swiftEmptyArrayStorage_100a1e050;
  do {
    if (((ulong)puVar14 & 0xc000000000000001) == 0) {
      IVar21 = *(ID *)(puVar14 + IVar13 * 8 + 0x20);
    }
    else {
      IVar21 = IVar13;
      FUN_1000cbedc(IVar13,puVar14);
    }
    puVar1 = (undefined *)(IVar13 + 1);
    if (SCARRY8(IVar13,1)) {
                    /* WARNING: Does not return */
      pcVar8 = (code *)SoftwareBreakpoint(1,0x100398eb4);
      (*pcVar8)();
    }
    if (1 < (long)local_e0) {
      puVar15 = &_OBJC_CLASS___UIDevice;
      _swift_getInitializedObjCClass();
      IVar16 = _objc_msgSend((ID)puVar15,"currentDevice");
      FUN_100826670(IVar16);
      IVar16 = _objc_msgSend((ID)puVar15,"currentDevice");
      cVar9 = (char)IVar16;
      FUN_100826670();
      dVar32 = *(double *)(&DAT_100934410 + (long)cVar9 * 8);
      if (DAT_100adf178 != -1) {
        _swift_once(&DAT_100adf178,FUN_1004e6120);
      }
      dVar30 = DAT_100b76190;
      puVar17 = (undefined *)_objc_msgSend((ID)puVar15,"currentDevice");
      FUN_100826670();
      FUN_1001c195c();
      if ((long)puVar27 < 0) {
                    /* WARNING: Does not return */
        pcVar8 = (code *)SoftwareBreakpoint(1,0x100398eb8);
        (*pcVar8)();
      }
      if (puVar1 < puVar27) {
        if (((ulong)puVar14 & 0xc000000000000001) == 0) {
          puVar17 = *(undefined **)(puVar14 + (long)puVar1 * 8 + 0x20);
          puVar22 = puVar17;
        }
        else {
          _swift_bridgeObjectRetain(puVar14);
          puVar22 = puVar1;
          FUN_1000cbedc(puVar1,puVar14);
          puVar17 = puVar14;
          _swift_bridgeObjectRelease();
        }
      }
      else {
        puVar22 = (undefined *)0x0;
      }
      FUN_1003303f8();
      puVar18 = puVar17;
      FUN_100367440();
      if (puVar17 == (undefined *)0x2) {
        FUN_10081a304();
        if (((ulong)puVar18 & 1) == 0) {
          puVar18 = (undefined *)_objc_msgSend(IVar21,"contentTypeID");
          FUN_100419df0();
          if (((uint)puVar18 & 0xff) != 6) goto LAB_1003986b0;
          IVar16 = _objc_msgSend(IVar21,"unowned");
          local_e8 = (uint)IVar16 ^ 1;
        }
        else {
LAB_1003986b0:
          FUN_10012d944();
          if (((ulong)puVar18 & 1) != 0) {
            IVar16 = _objc_msgSend(IVar21,"contentTypeID");
            uVar11 = (uint)IVar16;
            FUN_100419df0();
            if ((uVar11 & 0xff) != 6) goto LAB_100398700;
          }
          if (puVar22 == (undefined *)0x0) {
            local_e8 = 0;
          }
          else {
            FUN_10012d944();
            local_e8 = (uint)puVar22;
          }
        }
      }
      else {
LAB_100398700:
        local_e8 = 1;
      }
      lVar4 = _TtC8Playback4Song::privateWorkingCopyArrangement;
      IVar16 = *(ID *)(IVar21 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar16 == 0) {
        IVar19 = _objc_msgSend(IVar21,"workingCopyArrangementID");
        if (IVar19 == 0) {
          IVar16 = 0;
        }
        else {
          IVar20 = IVar19;
          FUN_10032ee88();
          IVar16 = IVar20;
          FUN_1005e3b94(IVar20,IVar19);
          _swift_bridgeObjectRelease(IVar20);
          if (IVar16 != 0) {
            *(ID *)(IVar21 + lVar4) = IVar16;
          }
        }
      }
      IVar21 = 0;
      FUN_1001b0864();
      _swift_getObjCClassFromMetadata();
      IVar21 = _objc_msgSend(IVar21,"buttonWithType:",0);
      if (IVar16 == 0) {
        *(undefined1 *)(IVar21 + _TtC8Playback23SetlistTransitionButton::transition) = 0;
        uVar10 = 0;
      }
      else {
        IVar19 = IVar16;
        FUN_1002da058();
        uVar10 = 0;
        *(char *)(IVar21 + _TtC8Playback23SetlistTransitionButton::transition) = (char)IVar19;
        if ((((uint)IVar19 & 0xff) < 6) && ((1 << (ulong)((uint)IVar19 & 0x1f) & 0x31U) != 0)) {
          IVar16 = _objc_msgSend(IVar16,"transitionContinuePad");
          uVar10 = (undefined1)IVar16;
        }
      }
      dVar31 = dVar32 * (double)(long)IVar13 + dVar32 + dVar30 * -0.5 + param_2;
      *(undefined1 *)(IVar21 + _TtC8Playback23SetlistTransitionButton::continuePad) = uVar10;
      FUN_1001b03b8();
      _objc_msgSend(IVar21,"addTarget:action:forControlEvents:",unaff_x20,"transitionButtonTapped:",
                    0x40);
      _objc_msgSend(IVar21,"setTag:",IVar13);
      param_2 = 0.0;
      dVar32 = dVar31;
      dVar30 = DAT_100b76190;
      dVar29 = DAT_100b76190;
      _objc_msgSend(IVar21,"setFrame:",dVar31,0,DAT_100b76190,DAT_100b76190);
      _objc_msgSend(IVar21,"layoutIfNeeded");
      IVar16 = unaff_x20 + lVar5;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar16 != 0) {
        _objc_msgSend(IVar16,"addSubview:",IVar21);
      }
      puVar17 = puVar24;
      _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
      if ((((int)puVar17 == 0) || ((long)puVar24 < 0)) ||
         (puVar17 = puVar24, ((ulong)puVar24 >> 0x3e & 1) != 0)) {
        if ((ulong)puVar24 >> 0x3e == 0) {
          puVar22 = *(undefined **)(((ulong)puVar24 & 0xfffffffffffff8) + 0x10);
        }
        else {
          puVar22 = (undefined *)((ulong)puVar24 & 0xffffffffffffff8);
          if ((long)puVar24 < 0) {
            puVar22 = puVar24;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg(puVar22);
        }
        puVar17 = (undefined *)0x0;
        FUN_10078eaac(0,puVar22 + 1,1,puVar24);
      }
      uVar26 = (ulong)puVar17 & 0xffffffffffffff8;
      uVar25 = *(ulong *)(uVar26 + 0x10);
      puVar24 = puVar17;
      if (*(ulong *)(uVar26 + 0x18) >> 1 <= uVar25) {
        puVar24 = (undefined *)(ulong)(1 < *(ulong *)(uVar26 + 0x18));
        FUN_10078eaac(puVar24,uVar25 + 1,1,puVar17);
        uVar26 = (ulong)puVar24 & 0xffffffffffffff8;
      }
      *(ulong *)(uVar26 + 0x10) = uVar25 + 1;
      *(ID *)(uVar26 + uVar25 * 8 + 0x20) = IVar21;
      uVar25 = _objc_msgSend(IVar21,"setHidden:",(ulong)(local_e8 & 1));
      dVar6 = DAT_100b04400;
      if ((DAT_100b04408 & 1) == 0) {
        FUN_1004a6154();
        if (uVar25 >> 0x3e == 0) {
          uVar26 = *(ulong *)((uVar25 & 0xfffffffffffff8) + 0x10);
        }
        else {
          uVar26 = uVar25 & 0xffffffffffffff8;
          if ((long)uVar25 < 0) {
            uVar26 = uVar25;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
        }
        _swift_bridgeObjectRelease();
        if (SBORROW8(uVar26,1)) {
                    /* WARNING: Does not return */
          pcVar8 = (code *)SoftwareBreakpoint(1,0x100398ebc);
          (*pcVar8)();
        }
        if ((long)IVar13 < (long)(uVar26 - 1)) {
          IVar21 = 0;
          FUN_1001ae670();
          _swift_getObjCClassFromMetadata();
          IVar16 = _objc_msgSend(IVar21,"buttonWithType:",0);
          puVar2 = (undefined8 *)(IVar16 + _TtC8Playback10ItemButton::mode);
          uVar23 = *puVar2;
          uVar3 = puVar2[1];
          *puVar2 = 0;
          puVar2[1] = 0;
          FUN_1000fb574(uVar23,uVar3);
          FUN_1001ae2c4();
          IVar21 = unaff_x20 + lVar5;
          _swift_unknownObjectWeakLoadStrong();
          if (IVar21 == 0) {
                    /* WARNING: Does not return */
            pcVar8 = (code *)SoftwareBreakpoint(1,0x100399088);
            (*pcVar8)();
          }
          _objc_msgSend(IVar21,"frame");
          _CGRectGetHeight(dVar32,param_2,dVar30,dVar29,0);
          dVar30 = DAT_100b76190;
          IVar21 = _objc_msgSend((ID)puVar15,"currentDevice");
          iVar12 = (int)IVar21;
          FUN_100826670();
          dVar29 = 0.7;
          if (0xd < (iVar12 - 0xcU & 0xff)) {
            dVar29 = 1.05;
          }
          param_2 = (dVar32 - dVar6) - dVar30 * dVar29;
          _objc_msgSend(IVar16,"setFrame:",dVar31,param_2,DAT_100b76190,DAT_100b76190);
          _objc_msgSend(IVar16,"addTarget:action:forControlEvents:",unaff_x20,"addButtonTapped:",
                        0x40);
          _objc_msgSend(IVar16,"setTag:",IVar13);
          IVar21 = _objc_msgSend(IVar16,"layer");
          _objc_msgSend(IVar21,"setBorderWidth:",0);
          IVar21 = _objc_msgSend(IVar16,"layer");
          _objc_msgSend(IVar21,"setShadowRadius:",0);
          uVar23 = 0x676e6f5320646441;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                    (0x676e6f5320646441,0xe800000000000000);
          _objc_msgSend(IVar16,"setAccessibilityLabel:",uVar23);
          uVar23 = 0xd000000000000018;
          __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                    (0xd000000000000018,0x80000001008f06d0);
          _objc_msgSend(IVar16,"setAccessibilityIdentifier:",uVar23);
          IVar21 = unaff_x20 + lVar5;
          _swift_unknownObjectWeakLoadStrong();
          if (IVar21 != 0) {
            _objc_msgSend(IVar21,"addSubview:",IVar16);
          }
          puVar15 = local_128;
          _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
          if ((((int)puVar15 == 0) || ((long)local_128 < 0)) ||
             (puVar15 = local_128, ((ulong)local_128 >> 0x3e & 1) != 0)) {
            if ((ulong)local_128 >> 0x3e == 0) {
              puVar17 = *(undefined **)(((ulong)local_128 & 0xfffffffffffff8) + 0x10);
            }
            else {
              puVar17 = (undefined *)((ulong)local_128 & 0xffffffffffffff8);
              if ((long)local_128 < 0) {
                puVar17 = local_128;
              }
              __ss18_CocoaArrayWrapperV8endIndexSivg(puVar17);
            }
            puVar15 = (undefined *)0x0;
            FUN_10078eac8(0,puVar17 + 1,1,local_128);
          }
          uVar26 = (ulong)puVar15 & 0xffffffffffffff8;
          uVar25 = *(ulong *)(uVar26 + 0x10);
          local_128 = puVar15;
          if (*(ulong *)(uVar26 + 0x18) >> 1 <= uVar25) {
            local_128 = (undefined *)(ulong)(1 < *(ulong *)(uVar26 + 0x18));
            FUN_10078eac8(local_128,uVar25 + 1,1,puVar15);
            uVar26 = (ulong)local_128 & 0xffffffffffffff8;
          }
          *(ulong *)(uVar26 + 0x10) = uVar25 + 1;
          *(ID *)(uVar26 + uVar25 * 8 + 0x20) = IVar16;
        }
      }
    }
    IVar13 = IVar13 + 1;
  } while (puVar1 != puVar27);
  _swift_bridgeObjectRelease(puVar14);
LAB_100398dc0:
  _swift_bridgeObjectRelease(puVar14);
  uVar23 = *(undefined8 *)(unaff_x20 + _TtC8Playback21SetlistViewController::transitionButtons);
  *(undefined **)(unaff_x20 + _TtC8Playback21SetlistViewController::transitionButtons) = puVar24;
  _swift_bridgeObjectRetain(puVar24);
  _swift_bridgeObjectRelease(uVar23);
  lVar5 = _TtC8Playback21SetlistViewController::addButtons;
  uVar23 = *(undefined8 *)(unaff_x20 + _TtC8Playback21SetlistViewController::addButtons);
  *(undefined **)(unaff_x20 + _TtC8Playback21SetlistViewController::addButtons) = local_128;
  _swift_bridgeObjectRetain(local_128);
  _swift_bridgeObjectRelease(uVar23);
  uVar25 = *(ulong *)(unaff_x20 + lVar5);
  if (uVar25 >> 0x3e == 0) {
    IVar13 = *(ID *)((uVar25 & 0xfffffffffffff8) + 0x10);
  }
  else {
    IVar13 = uVar25 & 0xffffffffffffff8;
    if ((long)uVar25 < 0) {
      IVar13 = uVar25;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (IVar13 == 0) {
    _swift_bridgeObjectRetain(uVar25);
    _swift_release(lVar7);
  }
  else {
    if ((long)IVar13 < 1) {
                    /* WARNING: Does not return */
      pcVar8 = (code *)SoftwareBreakpoint(1,0x100399060);
      (*pcVar8)();
    }
    _swift_bridgeObjectRetain_n(uVar25,2);
    IVar21 = 0;
    do {
      if ((uVar25 & 0xc000000000000001) == 0) {
        IVar16 = *(ID *)(uVar25 + IVar21 * 8 + 0x20);
      }
      else {
        IVar16 = IVar21;
        FUN_1000cd438(IVar21,uVar25);
      }
      IVar21 = IVar21 + 1;
      _objc_msgSend(IVar16,"setHidden:",(ulong)(uVar28 != 0x8000000000000030));
    } while (IVar13 != IVar21);
    _swift_release(lVar7);
    _swift_bridgeObjectRelease(uVar25);
  }
  _swift_bridgeObjectRelease(puVar24);
  _swift_bridgeObjectRelease(local_128);
  _swift_bridgeObjectRelease(uVar25);
  return;
}

// ==== 1003995a0 FUN_1003995a0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

long FUN_1003995a0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  ID param_5,undefined8 param_6,undefined8 param_7)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  ID IVar6;
  undefined *puVar7;
  void *aBlock;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulong uVar10;
  ID unaff_x20;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long local_120;
  long local_118;
  ID local_110;
  undefined8 local_108;
  code *local_100;
  long local_f8;
  long local_f0;
  long lStack_e8;
  long local_e0;
  undefined *local_d8;
  undefined8 local_d0;
  code *local_c8;
  undefined *puStack_c0;
  code *local_b8;
  undefined *local_b0;
  undefined1 auStack_a8 [24];
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined1 local_70;
  
  lVar2 = 0;
  local_108 = param_7;
  local_100 = (code *)param_5;
  __s8Dispatch0A13WorkItemFlagsVMa();
  local_e0 = *(long *)(lVar2 + -8);
  lVar11 = (long)&local_120 - (*(long *)(local_e0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  local_f0 = *(long *)(lVar3 + -8);
  lVar12 = lVar11 - (*(long *)(local_f0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  lStack_e8 = lVar3;
  __s8Dispatch0A4TimeVMa();
  lVar1 = _TtC8Playback21SetlistViewController::transitionMenuViewController;
  lVar13 = *(long *)(lVar4 + -8);
  uVar10 = *(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar15 = lVar12 - uVar10;
  lVar14 = lVar15 - uVar10;
  lVar3 = unaff_x20 + _TtC8Playback21SetlistViewController::transitionMenuViewController;
  local_f8 = lVar4;
  _swift_unknownObjectWeakLoadStrong();
  lVar4 = 0;
  if (lVar3 == 0) {
    if (DAT_100ade928 != -1) {
      _swift_once(&DAT_100ade928,FUN_100040df8);
    }
    local_110 = _objc_msgSend(DAT_100b754c0,"instantiateInitialViewController");
    lVar4 = 0;
    if (local_110 != 0) {
      uVar5 = 0;
      FUN_100041bfc(0);
      IVar6 = local_110;
      _swift_dynamicCastClass(local_110,uVar5);
      lVar3 = _TtC8Playback21SetlistViewController::currentSetlist;
      if (IVar6 == 0) {
        return 0;
      }
      local_118 = lVar2;
      _swift_beginAccess(unaff_x20 + _TtC8Playback21SetlistViewController::currentSetlist,auStack_a8
                         ,0,0);
      local_120 = *(long *)(unaff_x20 + lVar3);
      if (local_120 == 0) {
        lVar4 = 0;
      }
      else {
        *(long *)(IVar6 + _TtC8Playback28TransitionMenuViewController::setlist) = local_120;
        *(undefined8 *)(IVar6 + _TtC8Playback28TransitionMenuViewController::song) = param_6;
        *(undefined8 *)(IVar6 + _TtC8Playback28TransitionMenuViewController::songIndex) = local_108;
        *(undefined ***)(IVar6 + _TtC8Playback28TransitionMenuViewController::delegate + 8) =
             &PTR_PTR_100a4f280;
        _swift_unknownObjectWeakAssign();
        lVar3 = unaff_x20 + _TtC8Playback21SetlistViewController::setlistCollectionView;
        _swift_unknownObjectWeakLoadStrong(lVar3);
        _objc_msgSend((ID)local_100,"frame");
        local_70 = 0;
        local_90 = param_1;
        uStack_88 = param_2;
        local_80 = param_3;
        uStack_78 = param_4;
        FUN_100430978(0,1,0xc,0,lVar3,&local_90);
        _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar6,1,0);
        FUN_100398264();
        _swift_unknownObjectWeakAssign(unaff_x20 + lVar1,IVar6);
        FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
        __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
        __s8Dispatch0A4TimeV3nowACyFZ(lVar15);
        __s8Dispatch1poiyAA0A4TimeVAD_SdtF(lVar14,0x3fc999999999999a,lVar15);
        lVar1 = local_f8;
        local_100 = *(code **)(lVar13 + 8);
        (*local_100)(lVar15,local_f8);
        puVar7 = &DAT_100a42bf0;
        _swift_allocObject(&DAT_100a42bf0,0x18,7);
        *(ID *)(puVar7 + 0x10) = unaff_x20;
        local_b8 = FUN_1003a86bc;
        local_d8 = PTR___NSConcreteStackBlock_100a1d8e8;
        local_d0 = 0x42000000;
        local_c8 = FUN_10056b3d8;
        puStack_c0 = &DAT_100a42c08;
        local_b0 = puVar7;
        aBlock = __Block_copy(&local_d8);
        _swift_release(local_b0);
        __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar12);
        puVar7 = PTR___swiftEmptyArrayStorage_100a1e050;
        local_d8 = PTR___swiftEmptyArrayStorage_100a1e050;
        puVar8 = &DAT_100af52a8;
        FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                      PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
        _swift_retain(puVar7);
        puVar7 = &DAT_100af52b0;
        FUN_100021774(&DAT_100af52b0);
        puVar9 = &DAT_100af52b8;
        FUN_100023140(&DAT_100af52b8,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
        lVar3 = local_118;
        __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
                  (lVar11,&local_d8,puVar7,puVar9,local_118,puVar8);
        __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
                  (lVar14,lVar12,lVar11,aBlock);
        __Block_release(aBlock);
        (**(code **)(local_e0 + 8))(lVar11,lVar3);
        (**(code **)(local_f0 + 8))(lVar12,lStack_e8);
        (*local_100)(lVar14,lVar1);
        lVar4 = lVar14;
      }
    }
  }
  return lVar4;
}

// ==== 1003a1a04 FUN_1003a1a04 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1003a1a04(uint param_1,ulong param_2,ulong param_3)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  code *pcVar6;
  ulong uVar7;
  undefined *puVar8;
  ID IVar9;
  ID IVar10;
  ID IVar11;
  long unaff_x20;
  ID IVar12;
  ulong uVar13;
  undefined8 uVar14;
  undefined1 auStack_78 [24];
  
  lVar4 = _TtC8Playback21SetlistViewController::currentSetlist;
  if (param_2 == 0) {
    _swift_beginAccess(unaff_x20 + _TtC8Playback21SetlistViewController::currentSetlist,auStack_78,0
                       ,0);
    uVar13 = *(ulong *)(unaff_x20 + lVar4);
    if (uVar13 == 0) {
      return;
    }
    FUN_1004a6154();
    if (uVar13 >> 0x3e == 0) {
      uVar7 = *(ulong *)((uVar13 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar7 = uVar13 & 0xffffffffffffff8;
      if ((long)uVar13 < 0) {
        uVar7 = uVar13;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if ((long)uVar7 < 0) {
                    /* WARNING: Does not return */
        pcVar6 = (code *)SoftwareBreakpoint(1,0x1003a2130);
        (*pcVar6)();
      }
    }
    if (((long)param_3 < 0) || (uVar7 <= param_3)) {
      _swift_bridgeObjectRelease(uVar13);
      return;
    }
    if ((uVar13 & 0xc000000000000001) == 0) {
      if (*(ulong *)((uVar13 & 0xfffffffffffff8) + 0x10) <= param_3) {
                    /* WARNING: Does not return */
        pcVar6 = (code *)SoftwareBreakpoint(1,0x1003a215c);
        (*pcVar6)();
      }
      param_2 = *(ulong *)(uVar13 + param_3 * 8 + 0x20);
    }
    else {
      param_2 = param_3;
      FUN_1000cbedc(param_3,uVar13);
    }
    _swift_bridgeObjectRelease(uVar13);
  }
  lVar4 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar12 = *(ID *)(param_2 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar12 == 0) {
    IVar9 = _objc_msgSend(param_2,"workingCopyArrangementID");
    if (IVar9 == 0) {
      return;
    }
    IVar10 = IVar9;
    FUN_10032ee88();
    IVar12 = IVar10;
    FUN_1005e3b94(IVar10,IVar9);
    _swift_bridgeObjectRelease(IVar10);
    if (IVar12 == 0) {
      return;
    }
    *(ID *)(param_2 + lVar4) = IVar12;
  }
  uVar1 = param_1 & 0xff;
  uVar2 = 0;
  if (uVar1 != 5) {
    uVar2 = uVar1;
  }
  _objc_msgSend(IVar12,"setStoredTransition:",(ulong)uVar2);
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar12 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar12);
  uVar13 = *(ulong *)(unaff_x20 + _TtC8Playback21SetlistViewController::transitionButtons);
  if (uVar13 >> 0x3e == 0) {
    uVar7 = *(ulong *)((uVar13 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar7 = uVar13 & 0xffffffffffffff8;
    if ((long)uVar13 < 0) {
      uVar7 = uVar13;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if ((long)uVar7 < 0) {
                    /* WARNING: Does not return */
      pcVar6 = (code *)SoftwareBreakpoint(1,0x1003a20f0);
      (*pcVar6)();
    }
  }
  if (uVar7 <= param_3) goto LAB_1003a1d94;
  if ((uVar13 & 0xc000000000000001) == 0) {
    if (*(ulong *)((uVar13 & 0xfffffffffffff8) + 0x10) <= param_3) {
                    /* WARNING: Does not return */
      pcVar6 = (code *)SoftwareBreakpoint(1,0x1003a2118);
      (*pcVar6)();
    }
    param_3 = *(ulong *)(uVar13 + param_3 * 8 + 0x20);
  }
  else {
    _swift_bridgeObjectRetain(uVar13);
    FUN_1000cd28c(param_3,uVar13);
    _swift_bridgeObjectRelease(uVar13);
  }
  lVar3 = _TtC8Playback23SetlistTransitionButton::transition;
  if (*(byte *)(param_3 + _TtC8Playback23SetlistTransitionButton::transition) != uVar1) {
    puVar8 = &_OBJC_CLASS___UIDevice;
    _swift_getInitializedObjCClass();
    uVar13 = _objc_msgSend((ID)puVar8,"currentDevice");
    FUN_100826a8c();
    if ((uVar13 & 0xff) == 0) {
      uVar14 = 1;
    }
    else {
      if (((uint)uVar13 & 0xff) == 1) goto LAB_1003a1ce0;
      uVar14 = 3;
    }
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    uVar5 = DAT_100b75a80;
    _swift_retain(DAT_100b75a80);
    FUN_1002242c0(uVar14);
    _swift_release(uVar5);
  }
LAB_1003a1ce0:
  *(char *)(param_3 + lVar3) = (char)param_1;
  FUN_1001af9d0();
  if (5 < *(byte *)(param_3 + lVar3) ||
      (1 << (ulong)(*(byte *)(param_3 + lVar3) & 0x1f) & 0x31U) == 0) {
    *(undefined1 *)(param_3 + _TtC8Playback23SetlistTransitionButton::continuePad) = 0;
    FUN_1001afde0(0);
  }
  if ((5 < uVar1) || ((1 << (ulong)(param_1 & 0x1f) & 0x31U) == 0)) goto LAB_1003a1d94;
  IVar12 = *(ID *)(param_2 + lVar4);
  if (IVar12 == 0) {
    IVar9 = _objc_msgSend(param_2,"workingCopyArrangementID");
    if (IVar9 == 0) goto LAB_1003a1d94;
    IVar10 = IVar9;
    FUN_10032ee88();
    IVar12 = IVar10;
    FUN_1005e3b94(IVar10,IVar9);
    _swift_bridgeObjectRelease(IVar10);
    if (IVar12 == 0) goto LAB_1003a1d94;
    *(ID *)(param_2 + lVar4) = IVar12;
  }
  IVar12 = _objc_msgSend(IVar12,"transitionContinuePad");
  *(char *)(param_3 + _TtC8Playback23SetlistTransitionButton::continuePad) = (char)IVar12;
  if ((5 < *(byte *)(param_3 + lVar3)) ||
     ((1 << (ulong)(*(byte *)(param_3 + lVar3) & 0x1f) & 0x31U) == 0)) {
    IVar12 = 0;
  }
  FUN_1001afde0(IVar12);
LAB_1003a1d94:
  puVar8 = &_OBJC_CLASS___UIApplication;
  _swift_getInitializedObjCClass();
  IVar12 = _objc_msgSend((ID)puVar8,"sharedApplication");
  IVar12 = _objc_msgSend(IVar12,"delegate");
  if (IVar12 != 0) {
    uVar14 = 0;
    FUN_100842dec(0);
    IVar9 = IVar12;
    _swift_dynamicCastClass(IVar12,uVar14);
    if (((IVar9 == 0) || (*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window) == 0)) ||
       (IVar9 = _objc_msgSend(*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window),
                              "rootViewController"), IVar9 == 0)) {
      _swift_unknownObjectRelease(IVar12);
    }
    else {
      IVar10 = _objc_msgSend(IVar9,"presentedViewController");
      while (IVar10 != 0) {
        IVar11 = _objc_msgSend(IVar10,"presentedViewController",IVar9);
        IVar9 = IVar10;
        IVar10 = IVar11;
      }
      _swift_unknownObjectRelease(IVar12);
      uVar14 = 0;
      FUN_100041bfc(0);
      _swift_dynamicCastClass(IVar9,uVar14);
      if (IVar9 != 0) {
        IVar12 = _objc_msgSend(IVar9,"tableView");
        _objc_msgSend(IVar12,"reloadData");
      }
    }
  }
  IVar12 = _objc_msgSend((ID)puVar8,"sharedApplication");
  IVar12 = _objc_msgSend(IVar12,"delegate");
  if (IVar12 != 0) {
    uVar14 = 0;
    FUN_100842dec(0);
    IVar9 = IVar12;
    _swift_dynamicCastClass(IVar12,uVar14);
    if (((IVar9 == 0) || (*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window) == 0)) ||
       (IVar9 = _objc_msgSend(*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window),
                              "rootViewController"), IVar9 == 0)) {
      _swift_unknownObjectRelease(IVar12);
    }
    else {
      uVar14 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar9,uVar14);
      if (IVar9 == 0) {
        _swift_unknownObjectRelease(IVar12);
      }
      else {
        _swift_unknownObjectRelease(IVar12);
        if (*(long *)(IVar9 + _TtC8Playback18MainViewController::transportViewController) != 0) {
          FUN_100867240(0);
        }
      }
    }
  }
  return;
}

// ==== 1003a215c FUN_1003a215c ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_1003a215c(uint param_1,ulong param_2,ulong param_3,ulong param_4)

{
  long lVar1;
  code *pcVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  ID IVar6;
  ID IVar7;
  ID IVar8;
  long unaff_x20;
  ulong uVar9;
  ID IVar10;
  undefined1 auStack_78 [24];
  
  lVar1 = _TtC8Playback21SetlistViewController::currentSetlist;
  if (param_2 == 0) {
    _swift_beginAccess(unaff_x20 + _TtC8Playback21SetlistViewController::currentSetlist,auStack_78,0
                       ,0);
    uVar9 = *(ulong *)(unaff_x20 + lVar1);
    if (uVar9 == 0) goto LAB_1003a2334;
    FUN_1004a6154();
    if (uVar9 >> 0x3e == 0) {
      uVar3 = *(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar3 = uVar9 & 0xffffffffffffff8;
      if ((long)uVar9 < 0) {
        uVar3 = uVar9;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if ((long)uVar3 < 0) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1003a26dc);
        (*pcVar2)();
      }
    }
    if (((long)param_3 < 0) || (uVar3 <= param_3)) {
      _swift_bridgeObjectRelease(uVar9);
      goto LAB_1003a2334;
    }
    if ((uVar9 & 0xc000000000000001) == 0) {
      if (*(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10) <= param_3) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1003a26f0);
        (*pcVar2)();
      }
      param_2 = *(ulong *)(uVar9 + param_3 * 8 + 0x20);
    }
    else {
      param_2 = param_3;
      FUN_1000cbedc(param_3,uVar9);
    }
    _swift_bridgeObjectRelease(uVar9);
  }
  lVar1 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar10 = *(ID *)(param_2 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar10 == 0) {
    IVar6 = _objc_msgSend(param_2,"workingCopyArrangementID");
    if (IVar6 == 0) goto LAB_1003a2334;
    IVar7 = IVar6;
    FUN_10032ee88();
    IVar10 = IVar7;
    FUN_1005e3b94(IVar7,IVar6);
    _swift_bridgeObjectRelease(IVar7);
    if (IVar10 == 0) goto LAB_1003a2334;
    *(ID *)(param_2 + lVar1) = IVar10;
  }
  _objc_msgSend(IVar10,"setTransitionContinuePad:",(ulong)(param_1 & 1));
LAB_1003a2334:
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar10 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar10);
  uVar9 = *(ulong *)(unaff_x20 + _TtC8Playback21SetlistViewController::transitionButtons);
  if (uVar9 >> 0x3e == 0) {
    uVar3 = *(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar3 = uVar9 & 0xffffffffffffff8;
    if ((long)uVar9 < 0) {
      uVar3 = uVar9;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if ((long)uVar3 < 0) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1003a269c);
      (*pcVar2)();
    }
  }
  if (param_3 < uVar3) {
    if ((uVar9 & 0xc000000000000001) == 0) {
      if (*(ulong *)((uVar9 & 0xfffffffffffff8) + 0x10) <= param_3) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(1,0x1003a26c4);
        (*pcVar2)();
      }
      param_3 = *(ulong *)(uVar9 + param_3 * 8 + 0x20);
    }
    else {
      _swift_bridgeObjectRetain(uVar9);
      FUN_1000cd28c(param_3,uVar9);
      _swift_bridgeObjectRelease(uVar9);
    }
    *(byte *)(param_3 + _TtC8Playback23SetlistTransitionButton::continuePad) = (byte)param_1 & 1;
    if (5 < *(byte *)(param_3 + _TtC8Playback23SetlistTransitionButton::transition) ||
        (1 << (ulong)(*(byte *)(param_3 + _TtC8Playback23SetlistTransitionButton::transition) & 0x1f
                     ) & 0x31U) == 0) {
      param_1 = 0;
    }
    FUN_1001afde0(param_1 & 1);
  }
  if ((param_4 & 1) != 0) {
    puVar4 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar10 = _objc_msgSend((ID)puVar4,"sharedApplication");
    IVar10 = _objc_msgSend(IVar10,"delegate");
    if (IVar10 != 0) {
      uVar5 = 0;
      FUN_100842dec(0);
      IVar6 = IVar10;
      _swift_dynamicCastClass(IVar10,uVar5);
      if (((IVar6 == 0) || (*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar6 = _objc_msgSend(*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window),
                                "rootViewController"), IVar6 == 0)) {
        _swift_unknownObjectRelease(IVar10);
      }
      else {
        IVar7 = _objc_msgSend(IVar6,"presentedViewController");
        while (IVar7 != 0) {
          IVar8 = _objc_msgSend(IVar7,"presentedViewController",IVar6);
          IVar6 = IVar7;
          IVar7 = IVar8;
        }
        _swift_unknownObjectRelease(IVar10);
        uVar5 = 0;
        FUN_100041bfc(0);
        _swift_dynamicCastClass(IVar6,uVar5);
        if (IVar6 != 0) {
          IVar10 = _objc_msgSend(IVar6,"tableView");
          _objc_msgSend(IVar10,"reloadData");
        }
      }
    }
  }
  puVar4 = &_OBJC_CLASS___UIApplication;
  _swift_getInitializedObjCClass();
  IVar10 = _objc_msgSend((ID)puVar4,"sharedApplication");
  IVar10 = _objc_msgSend(IVar10,"delegate");
  if (IVar10 != 0) {
    uVar5 = 0;
    FUN_100842dec(0);
    IVar6 = IVar10;
    _swift_dynamicCastClass(IVar10,uVar5);
    if (((IVar6 == 0) || (*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window) == 0)) ||
       (IVar6 = _objc_msgSend(*(ID *)(IVar6 + _TtC8Playback11AppDelegate::window),
                              "rootViewController"), IVar6 == 0)) {
      _swift_unknownObjectRelease(IVar10);
    }
    else {
      uVar5 = 0;
      FUN_100413a94(0);
      _swift_dynamicCastClass(IVar6,uVar5);
      _swift_unknownObjectRelease(IVar10);
      if ((IVar6 != 0) &&
         (*(long *)(IVar6 + _TtC8Playback18MainViewController::transportViewController) != 0)) {
        FUN_100867240(0);
      }
    }
  }
  return 0;
}

// ==== 1003fb9a8 FUN_1003fb9a8 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_1003fb9a8(double param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                byte param_5,ulong *param_6,ID param_7,ID param_8,undefined8 param_9,
                undefined8 param_10)

{
  ulong uVar1;
  code *pcVar2;
  ID IVar3;
  ulong uVar4;
  undefined8 uVar5;
  ID IVar6;
  ulong uVar7;
  ulong uVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  void *aBlock;
  ulong uVar12;
  ID unaff_x20;
  ulong uVar13;
  long lVar14;
  ID IVar15;
  ulong uVar16;
  double dVar17;
  undefined8 uVar18;
  undefined *local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  code *local_a8;
  undefined *local_a0;
  
  (**(code **)((*(ulong *)PTR__swift_isaMask_100a1e080 & *param_6) + 0x70))();
  if ((*(byte *)(unaff_x20 + _TtC8Playback18MainViewController::viewIsTransitioning) & 1) != 0) {
    IVar3 = _objc_msgSend(param_8,"setConstant:",-param_1);
    return IVar3;
  }
  if (*(long *)(unaff_x20 + _TtC8Playback18MainViewController::transportViewController) != 0) {
    IVar3 = *(long *)(unaff_x20 + _TtC8Playback18MainViewController::transportViewController) +
            _TtC8Playback23TransportViewController::editButton;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar3 == 0) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fc20c);
      (*pcVar2)();
    }
    _objc_msgSend(IVar3,"setUserInteractionEnabled:",0);
  }
  IVar3 = _objc_msgSend(unaff_x20,"view");
  _objc_msgSend(IVar3,"layoutIfNeeded");
  if (param_5 < 2) {
    uVar4 = _objc_msgSend(unaff_x20,"childViewControllers");
    uVar5 = 0;
    FUN_100023404(0,&DAT_100af4f38,&PTR__OBJC_CLASS___UIViewController_100aa3e10);
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar4,uVar5);
    if (uVar4 >> 0x3e == 0) {
      IVar3 = *(ID *)((uVar4 & 0xfffffffffffff8) + 0x10);
    }
    else {
      IVar3 = uVar4 & 0xffffffffffffff8;
      if ((long)uVar4 < 0) {
        IVar3 = uVar4;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (IVar3 == 0) {
      _swift_bridgeObjectRelease(uVar4);
    }
    else {
      _swift_bridgeObjectRetain(uVar4);
      IVar15 = 0;
      do {
        if ((uVar4 & 0xc000000000000001) == 0) {
          IVar6 = *(ID *)(uVar4 + 0x20 + IVar15 * 8);
        }
        else {
          IVar6 = IVar15;
          FUN_1000cbef8(IVar15,uVar4);
        }
        if (SCARRY8(IVar15,1)) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fbe7c);
          (*pcVar2)();
        }
        IVar15 = IVar15 + 1;
        IVar6 = _objc_msgSend(IVar6,"view");
        if (IVar6 == 0) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fc204);
          (*pcVar2)();
        }
        uVar7 = _objc_msgSend(IVar6,"subviews");
        uVar5 = 0;
        FUN_100023404(0,&DAT_100af5698,&PTR__OBJC_CLASS___UIView_100aa3dd8);
        __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar7,uVar5);
        if (uVar7 >> 0x3e == 0) {
          uVar16 = *(ulong *)((uVar7 & 0xfffffffffffff8) + 0x10);
          if (uVar16 == 0) goto LAB_1003fbd90;
LAB_1003fbc48:
          puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
          if ((long)uVar16 < 1) {
                    /* WARNING: Does not return */
            pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fbe80);
            (*pcVar2)();
          }
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          _swift_bridgeObjectRetain(uVar7);
          uVar13 = 0;
          do {
            if ((uVar7 & 0xc000000000000001) == 0) {
              uVar8 = *(ulong *)(uVar7 + uVar13 * 8 + 0x20);
            }
            else {
              uVar8 = uVar13;
              FUN_1000ccea8(uVar13,uVar7);
            }
            uVar5 = 0;
            FUN_10029c2cc(0);
            _swift_dynamicCastClass(uVar8,uVar5);
            if (uVar8 != 0) {
              puVar10 = puVar11;
              _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
              if ((((int)puVar10 == 0) || ((long)puVar11 < 0)) ||
                 (puVar10 = puVar11, ((ulong)puVar11 >> 0x3e & 1) != 0)) {
                if ((ulong)puVar11 >> 0x3e == 0) {
                  puVar9 = *(undefined **)(((ulong)puVar11 & 0xfffffffffffff8) + 0x10);
                }
                else {
                  puVar9 = (undefined *)((ulong)puVar11 & 0xffffffffffffff8);
                  if ((long)puVar11 < 0) {
                    puVar9 = puVar11;
                  }
                  __ss18_CocoaArrayWrapperV8endIndexSivg(puVar9);
                }
                puVar10 = (undefined *)0x0;
                FUN_10078faa8(0,puVar9 + 1,1,puVar11);
              }
              uVar12 = (ulong)puVar10 & 0xffffffffffffff8;
              uVar1 = *(ulong *)(uVar12 + 0x10);
              puVar11 = puVar10;
              if (*(ulong *)(uVar12 + 0x18) >> 1 <= uVar1) {
                puVar11 = (undefined *)(ulong)(1 < *(ulong *)(uVar12 + 0x18));
                FUN_10078faa8(puVar11,uVar1 + 1,1,puVar10);
                uVar12 = (ulong)puVar11 & 0xffffffffffffff8;
              }
              *(ulong *)(uVar12 + 0x10) = uVar1 + 1;
              *(ulong *)(uVar12 + uVar1 * 8 + 0x20) = uVar8;
            }
            uVar13 = uVar13 + 1;
          } while (uVar16 != uVar13);
          _swift_bridgeObjectRelease(uVar7);
        }
        else {
          uVar16 = uVar7 & 0xffffffffffffff8;
          if ((long)uVar7 < 0) {
            uVar16 = uVar7;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (uVar16 != 0) goto LAB_1003fbc48;
LAB_1003fbd90:
          puVar11 = PTR___swiftEmptyArrayStorage_100a1e050;
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
        }
        _swift_bridgeObjectRelease(uVar7);
        if ((ulong)puVar11 >> 0x3e == 0) {
          puVar10 = *(undefined **)(((ulong)puVar11 & 0xfffffffffffff8) + 0x10);
          if (puVar10 == (undefined *)0x0) goto LAB_1003fbb78;
LAB_1003fbdc8:
          if ((long)puVar10 < 1) {
                    /* WARNING: Does not return */
            pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fbe84);
            (*pcVar2)();
          }
          _swift_bridgeObjectRetain(puVar11);
          lVar14 = 0x20;
          do {
            _objc_msgSend(*(ID *)(puVar11 + lVar14),"removeFromSuperview");
            lVar14 = lVar14 + 8;
            puVar10 = puVar10 + -1;
          } while (puVar10 != (undefined *)0x0);
          _swift_bridgeObjectRelease_n(puVar11,2);
        }
        else {
          puVar10 = (undefined *)((ulong)puVar11 & 0xffffffffffffff8);
          if ((long)puVar11 < 0) {
            puVar10 = puVar11;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (puVar10 != (undefined *)0x0) goto LAB_1003fbdc8;
LAB_1003fbb78:
          _swift_bridgeObjectRelease(puVar11);
        }
      } while (IVar15 != IVar3);
      _swift_bridgeObjectRelease_n(uVar4,2);
    }
  }
  else {
    FUN_10040e570(param_6,param_7);
    IVar3 = _objc_msgSend(param_7,"isHidden");
    if ((int)IVar3 != 0) {
      _objc_msgSend(param_7,"setHidden:",0);
    }
  }
  IVar3 = _objc_msgSend(param_7,"layer");
  dVar17 = 0.0;
  uVar18 = 0x3fe0000000000000;
  _objc_msgSend(IVar3,"setAnchorPoint:",0,0x3fe0000000000000);
  puVar11 = &_OBJC_CLASS___CATransaction;
  _swift_getInitializedObjCClass();
  _objc_msgSend((ID)puVar11,"begin");
  IVar3 = _objc_msgSend(param_7,"layer");
  _objc_msgSend(IVar3,"position");
  uVar5 = uVar18;
  IVar3 = _objc_msgSend(unaff_x20,"view");
  if (IVar3 == 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(1,0x1003fc208);
    (*pcVar2)();
  }
  _objc_msgSend(IVar3,"frame");
  _CGRectGetWidth(dVar17,uVar5,param_3,param_4,0);
  IVar3 = _objc_msgSend(param_7,"layer");
  _objc_msgSend(IVar3,"setPosition:",dVar17 - param_1,uVar18);
  uVar5 = 0x6e6f697469736f70;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0x6e6f697469736f70,0xe800000000000000);
  puVar10 = &_OBJC_CLASS___CABasicAnimation;
  _swift_getInitializedObjCClass();
  IVar3 = _objc_msgSend((ID)puVar10,"animationWithKeyPath:",uVar5);
  uVar5 = *(undefined8 *)PTR__kCAMediaTimingFunctionEaseInEaseOut_100a1d810;
  puVar10 = &_OBJC_CLASS___CAMediaTimingFunction;
  _swift_getInitializedObjCClass();
  IVar15 = _objc_msgSend((ID)puVar10,"functionWithName:",uVar5);
  _objc_msgSend(IVar3,"setTimingFunction:",IVar15);
  _objc_msgSend(IVar3,"setDuration:",0x3fd3333333333333);
  puVar10 = &DAT_100a46b70;
  _swift_allocObject(&DAT_100a46b70,0x18,7);
  _swift_unknownObjectWeakInit(puVar10 + 0x10,unaff_x20);
  puVar9 = &DAT_100a46b98;
  _swift_allocObject(&DAT_100a46b98,0x48,7);
  *(undefined **)(puVar9 + 0x10) = puVar10;
  *(ID *)(puVar9 + 0x18) = param_7;
  *(ID *)(puVar9 + 0x20) = param_8;
  *(double *)(puVar9 + 0x28) = param_1;
  puVar9[0x30] = param_5;
  *(undefined8 *)(puVar9 + 0x38) = param_9;
  *(undefined8 *)(puVar9 + 0x40) = param_10;
  local_a8 = FUN_100416e24;
  local_c8 = PTR___NSConcreteStackBlock_100a1d8e8;
  local_c0 = 0x42000000;
  local_b8 = FUN_10056b3d8;
  puStack_b0 = &DAT_100a46bb0;
  local_a0 = puVar9;
  aBlock = __Block_copy(&local_c8);
  puVar10 = local_a0;
  FUN_100027524(param_9,param_10);
  _swift_release(puVar10);
  _objc_msgSend((ID)puVar11,"setCompletionBlock:",aBlock);
  __Block_release(aBlock);
  IVar15 = _objc_msgSend(param_7,"layer");
  _objc_msgSend(IVar15,"addAnimation:forKey:",IVar3,0);
  _objc_msgSend((ID)puVar11,"commit");
  _objc_msgSend(param_7,"setHidden:",0);
  return 0;
}

// ==== 10040efd0 FUN_10040efd0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8
FUN_10040efd0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 param_5,long param_6,long param_7)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  undefined *self;
  undefined1 *puVar8;
  ulong uVar9;
  ID unaff_x20;
  void *aBlock;
  ID self_00;
  undefined8 uVar10;
  undefined1 *puVar11;
  long lVar12;
  undefined8 *puVar13;
  long local_d0 [2];
  undefined *local_c0;
  undefined8 local_b8;
  code *local_b0;
  undefined *puStack_a8;
  long local_a0;
  long local_98;
  ID IVar7;
  
  puVar3 = &DAT_100b021f0;
  local_d0[1] = param_6;
  FUN_100021774();
  puVar11 = (undefined1 *)
            ((long)local_d0 - (*(long *)(*(long *)(puVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0)
            );
  lVar4 = 0;
  FUN_100575df8();
  uVar9 = *(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  self_00 = (long)puVar11 - uVar9;
  lVar12 = self_00 - uVar9;
  lVar4 = 0;
  FUN_1007a3aec();
  puVar13 = (undefined8 *)
            (lVar12 - (*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0));
  FUN_100023384(param_5,puVar13,FUN_1007a3aec);
  puVar5 = puVar13;
  _swift_getEnumCaseMultiPayload(puVar13,lVar4);
  local_d0[0] = param_7;
  if ((int)puVar5 == 1) {
    uVar10 = *puVar13;
    if (DAT_100adea70 != -1) {
      _swift_once(&DAT_100adea70,FUN_1001b4ea8);
    }
    self_00 = _objc_msgSend(DAT_100b75848,"instantiateInitialViewController");
    if (self_00 == 0) {
      return 0;
    }
    uVar6 = 0;
    FUN_1001b6080(0);
    _swift_dynamicCastClass(self_00,uVar6);
    if (self_00 == 0) {
      return 0;
    }
    *(undefined8 *)(self_00 + _TtC8Playback32RentalTransferMainViewController::setlist) = uVar10;
  }
  else {
    FUN_100023340(puVar13,lVar12,FUN_100575df8);
    FUN_100023384(lVar12,self_00,FUN_100575df8);
    FUN_100575d28(0);
    _objc_allocWithZone();
    FUN_100416704();
    FUN_1000233c8(lVar12,FUN_100575df8);
  }
  self = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar7 = _objc_msgSend((ID)self,"currentDevice");
  uVar2 = (uint)IVar7;
  FUN_100826670();
  iVar1 = *(int *)(puVar3 + 0x30);
  *puVar11 = (char)uVar2;
  FUN_100023384(param_5,puVar11 + iVar1,FUN_1007a3aec);
  puVar8 = puVar11 + iVar1;
  _swift_getEnumCaseMultiPayload(puVar8,lVar4);
  if ((int)puVar8 == 1) {
    FUN_1007a35c8(0);
    FUN_1007a35c8();
    _objc_msgSend(self_00,"setPreferredContentSize:",param_1);
    _objc_msgSend(self_00,"setModalPresentationStyle:",2);
    lVar4 = local_d0[0];
  }
  else if ((uVar2 & 0xff) == 0x1a) {
    IVar7 = _objc_msgSend(self_00,"presentationController");
    if (IVar7 == 0) {
      FUN_1007a35c8();
    }
    else {
      _objc_msgSend(IVar7,"frameOfPresentedViewInContainerView");
      _CGRectGetWidth(param_1,param_2,param_3,param_4,0);
    }
    uVar10 = param_1;
    IVar7 = _objc_msgSend(self_00,"presentationController");
    if (IVar7 == 0) {
      FUN_1007a35c8();
    }
    else {
      _objc_msgSend(IVar7,"frameOfPresentedViewInContainerView");
      _CGRectGetHeight(uVar10,param_2,param_3,param_4,0);
    }
    _objc_msgSend(self_00,"setPreferredContentSize:",param_1);
    _objc_msgSend(self_00,"setModalPresentationStyle:",2);
    FUN_1000233c8(puVar11 + iVar1,FUN_1007a3aec);
    lVar4 = local_d0[0];
  }
  else {
    _objc_msgSend(self_00,"setTransitioningDelegate:");
    FUN_10040f460();
    FUN_100023be4(puVar11,&DAT_100b021f0);
    lVar4 = local_d0[0];
  }
  local_d0[0] = lVar4;
  if (local_d0[1] == 0) {
    aBlock = (void *)0x0;
  }
  else {
    local_b8 = 0x42000000;
    local_b0 = FUN_10056b3d8;
    puStack_a8 = &DAT_100a46700;
    local_c0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_a0 = local_d0[1];
    local_98 = lVar4;
    aBlock = __Block_copy(&local_c0);
    lVar12 = local_98;
    _swift_retain(lVar4);
    _swift_release(lVar12);
  }
  _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",self_00,1,aBlock);
  __Block_release(aBlock);
  return 0;
}

// ==== 100413268 FUN_100413268 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_100413268(undefined8 param_1,long param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long lVar3;
  undefined *puVar4;
  ID IVar5;
  long unaff_x20;
  
  _swift_getObjectType();
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::webPageDismissedCompletion)
  ;
  *puVar1 = 0;
  puVar1[1] = 0;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback18MainViewController::mainStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportMappingContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::setlistContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback18MainViewController::mixerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportMappingTopSpacerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportBottomSpacerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::stackMenuContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mainStackViewTopConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportContainerViewHeightConstraint,0
            );
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::setlistContainerViewHeightConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerViewHeightConstraint,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerViewWidthConstraint,0);
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::transportViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::transportMappingViewController) = 0
  ;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::setlistViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::waveformViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mixerViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerViewController) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::viewHasAppeared) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::viewIsTransitioning) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::statusBarView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::overscreenModalViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::backgroundOverlayView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::stackMenuViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::stackMenuCloseButtonImageView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuContainerView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuViewController) = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuState);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[7] = 0;
  puVar1[6] = 0;
  puVar1[9] = 0;
  puVar1[8] = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mainDisplayLink) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::coreActivityStackView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::metricsDisplayLink) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldPromptMIDICuesLocalOnlySave)
       = 1;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldResetContentForNewUser) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldPresentRouteChangeView) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldForceReloadWaveform) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::webSocketHeartbeatTimer) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityViewDisplayTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityViewTimer) = 0;
  lVar3 = _TtC8Playback18MainViewController::hiddenAccessibilityLabels;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain();
  FUN_10079d3d8();
  _swift_release(puVar2);
  *(undefined **)(unaff_x20 + lVar3) = puVar4;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback18MainViewController::___lazy_storage___transportResponders) = 0;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback18MainViewController::___lazy_storage___playbackRemoteOverlayView) = 0;
  if (param_2 == 0) {
    param_1 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_1,param_2);
    _swift_bridgeObjectRelease(param_2);
  }
  IVar5 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff90,"initWithNibName:bundle:",
                              param_1,param_3);
  return IVar5;
}

// ==== 1004136b0 FUN_1004136b0 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

ID FUN_1004136b0(undefined8 param_1)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long lVar3;
  undefined *puVar4;
  ID IVar5;
  long unaff_x20;
  
  _swift_getObjectType();
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::webPageDismissedCompletion)
  ;
  *puVar1 = 0;
  puVar1[1] = 0;
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback18MainViewController::mainStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportMappingContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::setlistContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerView,0);
  _swift_unknownObjectWeakInit(unaff_x20 + _TtC8Playback18MainViewController::mixerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerLeadingConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportMappingTopSpacerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportBottomSpacerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::stackMenuContainerView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::mainStackViewTopConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::transportContainerViewHeightConstraint,0
            );
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::setlistContainerViewHeightConstraint,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerViewHeightConstraint,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback18MainViewController::waveformContainerViewWidthConstraint,0);
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::transportViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::transportMappingViewController) = 0
  ;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::setlistViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::waveformViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mixerViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mtConnectDrawerViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::editMenuDrawerViewController) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::viewHasAppeared) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::viewIsTransitioning) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::statusBarView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::overscreenModalViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::backgroundOverlayView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::stackMenuViewController) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::stackMenuCloseButtonImageView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuContainerView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuViewController) = 0;
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::buttonStripMenuState);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[7] = 0;
  puVar1[6] = 0;
  puVar1[9] = 0;
  puVar1[8] = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::mainDisplayLink) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::coreActivityStackView) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::metricsDisplayLink) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldPromptMIDICuesLocalOnlySave)
       = 1;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldResetContentForNewUser) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldPresentRouteChangeView) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18MainViewController::shouldForceReloadWaveform) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::webSocketHeartbeatTimer) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityViewDisplayTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18MainViewController::activityViewTimer) = 0;
  lVar3 = _TtC8Playback18MainViewController::hiddenAccessibilityLabels;
  puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar4 = PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain();
  FUN_10079d3d8();
  _swift_release(puVar2);
  *(undefined **)(unaff_x20 + lVar3) = puVar4;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback18MainViewController::___lazy_storage___transportResponders) = 0;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback18MainViewController::___lazy_storage___playbackRemoteOverlayView) = 0;
  IVar5 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa0,"initWithCoder:",param_1);
  return IVar5;
}

// ==== 10043cf14 _TtC8Playback31TransitionContinuePadSymbolView::circlePadding ====
/* Function Stack Size: 0x10 bytes */

double _TtC8Playback31TransitionContinuePadSymbolView::circlePadding(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + circlePadding);
}

// ==== 10043cf24 _TtC8Playback31TransitionContinuePadSymbolView::setCirclePadding: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback31TransitionContinuePadSymbolView::setCirclePadding_
               (ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + circlePadding) = param_3;
  return;
}

// ==== 10043cf34 _TtC8Playback31TransitionContinuePadSymbolView::circleYOffset ====
/* Function Stack Size: 0x10 bytes */

double _TtC8Playback31TransitionContinuePadSymbolView::circleYOffset(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + circleYOffset);
}

// ==== 10043cf44 _TtC8Playback31TransitionContinuePadSymbolView::setCircleYOffset: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback31TransitionContinuePadSymbolView::setCircleYOffset_
               (ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + circleYOffset) = param_3;
  return;
}

// ==== 10043cf54 _TtC8Playback31TransitionContinuePadSymbolView::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback31TransitionContinuePadSymbolView::initWithCoder_(ID param_1,SEL param_2,ID param_3)

{
  FUN_10043d390();
  return param_3;
}

// ==== 10043cf90 FUN_10043cf90 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10043cf90(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined *puVar2;
  ID IVar4;
  long unaff_x20;
  undefined8 uVar5;
  ID IVar3;
  
  _swift_getObjectType();
  puVar2 = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar3 = _objc_msgSend((ID)puVar2,"currentDevice");
  iVar1 = (int)IVar3;
  FUN_100826670();
  uVar5 = 0x4026000000000000;
  if (0xd < (iVar1 - 0xcU & 0xff)) {
    uVar5 = 0x402e000000000000;
  }
  *(undefined8 *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circlePadding) = uVar5
  ;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circleYOffset) =
       0xbff0000000000000;
  IVar3 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffa0,"initWithFrame:",param_1,
                              param_2,param_3,param_4);
  puVar2 = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar4 = _objc_msgSend((ID)puVar2,"clearColor");
  _objc_msgSend(IVar3,"setBackgroundColor:",IVar4);
  _objc_msgSend(IVar3,"setOpaque:",0);
  _objc_msgSend(IVar3,"setUserInteractionEnabled:",0);
  return IVar3;
}

// ==== 10043d118 _TtC8Playback31TransitionContinuePadSymbolView::initWithFrame: ====
/* Function Stack Size: 0x30 bytes */

ID _TtC8Playback31TransitionContinuePadSymbolView::initWithFrame_
             (ID param_1,SEL param_2,CGRect param_3)

{
  FUN_10043cf90(param_1,param_2,param_3.field0_0x0.field0_0x0,param_3.field0_0x0.field1_0x8,
                param_3.field1_0x10.field0_0x0,param_3.field1_0x10.field1_0x8);
  return param_1;
}

// ==== 10043d138 FUN_10043d138 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
FUN_10043d138(double param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5)

{
  long lVar1;
  undefined *self;
  ID IVar2;
  long unaff_x20;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  _UIGraphicsGetCurrentContext();
  if (param_5 != 0) {
    self = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    IVar2 = _objc_msgSend((ID)self,"clearColor");
    IVar2 = _objc_msgSend(IVar2,"CGColor");
    _CGContextSetFillColorWithColor(param_5,IVar2);
    if (DAT_100adfd50 != -1) {
      _swift_once(&DAT_100adfd50,FUN_10073e434);
    }
    IVar2 = _objc_msgSend(DAT_100b0ad90,"CGColor");
    _CGContextSetStrokeColorWithColor(param_5,IVar2);
    _CGContextSetLineWidth(0x4000000000000000,param_5);
    lVar1 = _TtC8Playback31TransitionContinuePadSymbolView::circlePadding;
    dVar6 = (*(double *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circlePadding)
            + 2.0) * 0.5;
    dVar3 = *(double *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circleYOffset);
    dVar4 = param_1;
    _CGRectGetWidth(param_1,param_2,param_3,param_4);
    dVar5 = *(double *)(unaff_x20 + lVar1);
    _CGRectGetHeight(param_1,param_2,param_3,param_4);
    _CGContextAddEllipseInRect
              (dVar6,dVar6 + dVar3,(dVar4 + -2.0) - dVar5,
               (param_1 + -2.0) - *(double *)(unaff_x20 + lVar1),param_5);
    _CGContextDrawPath(param_5,3);
    return 0;
  }
  return 0;
}

// ==== 10043d318 _TtC8Playback31TransitionContinuePadSymbolView::drawRect: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x30 bytes */

void _TtC8Playback31TransitionContinuePadSymbolView::drawRect_
               (ID param_1,SEL param_2,CGRect param_3)

{
  FUN_10043d138(param_1,param_2,param_3.field0_0x0.field0_0x0,param_3.field0_0x0.field1_0x8,
                param_3.field1_0x10.field0_0x0,param_3.field1_0x10.field1_0x8);
  return;
}

// ==== 10043d370 FUN_10043d370 ====
void FUN_10043d370(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback31TransitionContinuePadSymbolView);
  return;
}

// ==== 10043d390 FUN_10043d390 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10043d390(undefined8 param_1)

{
  int iVar1;
  undefined *puVar2;
  ID IVar4;
  long unaff_x20;
  undefined8 uVar5;
  ID IVar3;
  
  _swift_getObjectType();
  puVar2 = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar3 = _objc_msgSend((ID)puVar2,"currentDevice");
  iVar1 = (int)IVar3;
  FUN_100826670();
  uVar5 = 0x4026000000000000;
  if (0xd < (iVar1 - 0xcU & 0xff)) {
    uVar5 = 0x402e000000000000;
  }
  *(undefined8 *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circlePadding) = uVar5
  ;
  *(undefined8 *)(unaff_x20 + _TtC8Playback31TransitionContinuePadSymbolView::circleYOffset) =
       0xbff0000000000000;
  IVar3 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"initWithCoder:",param_1);
  if (IVar3 != 0) {
    puVar2 = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    IVar4 = _objc_msgSend((ID)puVar2,"clearColor");
    _objc_msgSend(IVar3,"setBackgroundColor:",IVar4);
    _objc_msgSend(IVar3,"setOpaque:",0);
    _objc_msgSend(IVar3,"setUserInteractionEnabled:",0);
  }
  return IVar3;
}

// ==== 100458e64 FUN_100458e64 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

void FUN_100458e64(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  class_t *pcVar4;
  undefined *puVar5;
  void *aBlock;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long unaff_x20;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined *local_c0;
  undefined8 local_b8;
  code *local_b0;
  undefined *puStack_a8;
  code *local_a0;
  undefined *local_98;
  objc_super local_90;
  ID IVar6;
  
  _swift_getObjectType();
  lVar2 = 0;
  __s8Dispatch0A13WorkItemFlagsVMa();
  lVar11 = *(long *)(lVar2 + -8);
  lVar9 = (long)&local_c0 - (*(long *)(lVar11 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  __s8Dispatch0A3QoSVMa();
  lVar12 = *(long *)(lVar3 + -8);
  lVar10 = lVar9 - (*(long *)(lVar12 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff80,
                      "viewWillTransitionToSize:withTransitionCoordinator:",param_1,param_2,param_3)
  ;
  IVar6 = unaff_x20 + _TtC8Playback22WaveformViewController::collectionView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    pcVar4 = (class_t *)0x0;
    FUN_1003e34f8();
    local_90.receiver = IVar6;
    local_90.super_class = pcVar4;
    _objc_msgSendSuper2(&local_90,"reloadData");
  }
  puVar5 = &_OBJC_CLASS___UIDevice;
  _swift_getInitializedObjCClass();
  IVar6 = _objc_msgSend((ID)puVar5,"currentDevice");
  uVar1 = (uint)IVar6;
  FUN_100826670();
  if (0x19 < (uVar1 & 0xff)) {
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    puVar5 = &DAT_100a49c48;
    _swift_allocObject(&DAT_100a49c48,0x18,7);
    _swift_unknownObjectWeakInit(puVar5 + 0x10);
    local_a0 = FUN_100468b1c;
    local_c0 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_b8 = 0x42000000;
    local_b0 = FUN_10056b3d8;
    puStack_a8 = &DAT_100a49d78;
    local_98 = puVar5;
    aBlock = __Block_copy(&local_c0);
    _swift_release(local_98);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(lVar10);
    puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
    local_c0 = PTR___swiftEmptyArrayStorage_100a1e050;
    puVar7 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar5);
    puVar5 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar8 = &DAT_100af52b8;
    FUN_100023140(&DAT_100af52b8,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (lVar9,&local_c0,puVar5,puVar8,lVar2,puVar7);
    __sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (0,lVar10,lVar9,aBlock);
    __Block_release(aBlock);
    (**(code **)(lVar11 + 8))(lVar9,lVar2);
    (**(code **)(lVar12 + 8))(lVar10,lVar3);
  }
  return;
}

// ==== 100459168 _TtC8Playback22WaveformViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback22WaveformViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback22WaveformViewController *this,ID param_1,SEL param_2,CGSize param_3,
          ID param_4)

{
  double dVar1;
  
  dVar1 = param_3.field0_0x0;
  _swift_unknownObjectRetain(dVar1,param_2,dVar1,param_3.field1_0x8);
  FUN_100458e64(dVar1);
  _swift_unknownObjectRelease(dVar1);
  return;
}

// ==== 1004674f4 FUN_1004674f4 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x000100467b4c) */
/* WARNING: Removing unreachable block (ram,0x000100468ad4) */

undefined8 *
FUN_1004674f4(undefined *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  long *plVar1;
  ulong *puVar2;
  code *pcVar3;
  uint uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  class_t *pcVar7;
  long lVar8;
  ID IVar9;
  undefined *puVar10;
  ID IVar11;
  ID IVar12;
  class_t *pcVar13;
  ID IVar15;
  ID IVar16;
  undefined *puVar17;
  undefined *puVar18;
  ulong uVar19;
  ID unaff_x20;
  undefined *puVar20;
  undefined *puVar21;
  ulong uVar22;
  long lVar23;
  long lVar24;
  ulong uVar25;
  undefined8 uVar26;
  uint uVar27;
  long lVar28;
  undefined *puVar29;
  double dVar30;
  double dVar31;
  undefined8 local_100;
  ID local_f8;
  undefined *local_f0;
  undefined *local_e8;
  ID local_e0;
  objc_super local_d8;
  objc_super local_c8;
  undefined *local_b0;
  undefined8 uStack_a8;
  undefined *local_a0;
  undefined *puStack_98;
  undefined1 local_90;
  ID IVar14;
  
  puVar5 = (undefined8 *)&DAT_100af5490;
  FUN_100021774();
  lVar24 = (long)&local_100 - (*(long *)(puVar5[-1] + 0x40) + 0xfU & 0xfffffffffffffff0);
  if (DAT_100adfbb8 != -1) {
    puVar5 = &DAT_100adfbb8;
    _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
  }
  lVar28 = _TtC8Playback22WaveformViewController::currentSetlist;
  uVar22 = *(ulong *)(DAT_100b77548 + 0x10);
  if (uVar22 >> 0x3e != 2) {
    return puVar5;
  }
  uVar19 = uVar22 + 0x7ffffffffffffff8 >> 3 | uVar22 << 0x3d;
  if (2 < (long)uVar19) {
    if (uVar19 != 3) {
      if (uVar19 != 6) {
        return puVar5;
      }
      uVar22 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
      _swift_unknownObjectWeakLoadStrong();
      if (uVar22 == 0) {
        return (undefined8 *)0x0;
      }
      FUN_1004a9df0();
      if (uVar22 == 0) {
        return (undefined8 *)0x0;
      }
      IVar11 = unaff_x20 + _TtC8Playback22WaveformViewController::playheadAddButton;
      _swift_unknownObjectWeakLoadStrong();
      if (IVar11 == 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ab4);
        (*pcVar3)();
      }
      FUN_10054ee80(0);
      _objc_allocWithZone();
      IVar9 = uVar22 | 0x8000000000000000;
      FUN_1005fca9c();
      puVar29 = &_OBJC_CLASS___UINavigationController;
      _objc_allocWithZone();
      IVar12 = _objc_msgSend((ID)puVar29,"initWithRootViewController:",IVar9);
      IVar9 = _objc_msgSend(IVar9,"tableView");
      if (IVar9 == 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ab8);
        (*pcVar3)();
      }
      _objc_msgSend(IVar9,"contentSize");
      _objc_msgSend(IVar12,"setPreferredContentSize:");
      _objc_msgSend(IVar11,"bounds");
      local_90 = 0;
      local_b0 = param_1;
      uStack_a8 = param_2;
      local_a0 = (undefined *)param_3;
      puStack_98 = (undefined *)param_4;
      FUN_100430978(0,1,0xc,0,IVar11,&local_b0,0);
      _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar12,1,0);
      return (undefined8 *)0x0;
    }
    IVar11 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
    _swift_unknownObjectWeakLoadStrong();
    if ((IVar11 == 0) || (FUN_1004a9df0(), IVar11 == 0)) {
LAB_1004681c0:
      lVar28 = unaff_x20 + lVar28;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar28 == 0) {
        return (undefined8 *)0x0;
      }
      FUN_1004a9df0();
      if (lVar28 != 0) {
        IVar11 = unaff_x20 + _TtC8Playback22WaveformViewController::playheadAddButton;
        _swift_unknownObjectWeakLoadStrong();
        if (IVar11 != 0) {
          _objc_msgSend(IVar11,"bounds");
          _CGRectGetWidth();
          puVar29 = param_1;
          _objc_msgSend(IVar11,"bounds");
          _CGRectGetHeight();
          FUN_1003ae4b0(0);
          _objc_allocWithZone();
          FUN_1005fc54c(lVar28,0);
          puVar10 = &_OBJC_CLASS___UINavigationController;
          _objc_allocWithZone();
          IVar9 = _objc_msgSend((ID)puVar10,"initWithRootViewController:",lVar28);
          local_b0 = (undefined *)0x0;
          uStack_a8 = 0;
          local_90 = 0;
          local_a0 = param_1;
          puStack_98 = puVar29;
          FUN_100430978(0,1,0xc,0,IVar11,&local_b0,0);
          _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar9,1,0);
        }
        return (undefined8 *)0x0;
      }
      return (undefined8 *)0x0;
    }
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    uVar22 = *(ulong *)(DAT_100b75e40 + 0x20);
    if ((uVar22 == 0) || ((*(byte *)(uVar22 + _TtC8Playback9Sequencer::privatePlayState) & 1) == 0))
    goto LAB_1004681c0;
    uVar19 = uVar22;
    _swift_retain();
    FUN_1004303d8();
    if (uVar19 == 0) {
      _swift_release(uVar22);
      goto LAB_1004681c0;
    }
    uVar25 = uVar19 & 0xffffffffffffff8;
    if (uVar19 >> 0x3e == 0) {
      uVar6 = *(ulong *)(uVar25 + 0x10);
    }
    else {
      uVar6 = uVar19;
      if (-1 < (long)uVar19) {
        uVar6 = uVar25;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar6 == 0) {
      _swift_release(uVar22);
      _swift_bridgeObjectRelease(uVar19);
      goto LAB_1004681c0;
    }
    if ((uVar19 & 0xc000000000000001) == 0) {
      if (*(long *)(uVar25 + 0x10) == 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x100468a9c);
        (*pcVar3)();
      }
      IVar9 = *(ID *)(uVar19 + 0x20);
    }
    else {
      IVar9 = 0;
      FUN_1000cc6c0(0,uVar19);
    }
    local_e0 = IVar9;
    _swift_bridgeObjectRelease(uVar19);
    FUN_1004f240c();
    puVar10 = param_1;
    FUN_1003220ec();
    lVar24 = _TtC8Playback9Sequencer::sampleTimeCurrentTime;
    uVar19 = *(ulong *)(uVar22 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
    puVar20 = puVar10;
    _swift_retain(uVar19);
    __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
              (&local_b0,FUN_1003afbec,uVar19,PTR___sSdN_100a1dd60);
    _swift_release();
    puVar29 = local_b0;
    FUN_1003220ec();
    dVar31 = (double)puVar29 / (double)puVar20;
    FUN_1004f8628();
    if (((uVar19 & 1) != 0) &&
       (*(long *)(uVar22 + _TtC8Playback9Sequencer::currentSongMapElement) != 0)) {
      FUN_100034820(0);
      lVar28 = 0;
      puVar29 = puVar20;
      FUN_1004f8730();
      if (lVar28 != 0) {
        _swift_release(*(undefined8 *)(lVar28 + _TtCC8Playback7SongMap7Element::section),lVar28);
        FUN_1000345bc(0);
        uVar26 = *(undefined8 *)(uVar22 + lVar24);
        _swift_retain(uVar26);
        __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                  (&local_b0,FUN_1003afbec,uVar26,PTR___sSdN_100a1dd60);
        _swift_release(uVar26);
        dVar30 = (double)puVar20 - (double)local_b0;
        dVar31 = (double)puVar29 - dVar30;
        FUN_1003220ec();
        dVar31 = dVar31 / dVar30;
      }
    }
    IVar12 = 0;
    FUN_1000287b8();
    FUN_100028304();
    IVar9 = _objc_msgSend(IVar12,"bus");
    if (IVar9 == 0) {
      IVar9 = local_e0;
    }
    local_e8 = (undefined *)IVar12;
    if (IVar12 == 0) {
      IVar14 = 0x13;
      uVar27 = 1;
      IVar12 = 0;
    }
    else {
      IVar14 = _objc_msgSend(IVar12,"storedType");
      uVar4 = (uint)IVar14;
      FUN_100028d34();
      uVar27 = 0;
      if ((uVar4 & 0xff) != 5) {
        uVar27 = uVar4;
      }
      IVar14 = _objc_msgSend(IVar12,"note");
      IVar12 = _objc_msgSend(IVar12,"velocity");
    }
    IVar15 = _objc_msgSend(IVar9,"id");
    IVar16 = _objc_msgSend(local_e0,"id");
    if ((int)IVar15 == (int)IVar16) {
      FUN_100455658();
      IVar12 = IVar16;
    }
    FUN_1000290a0();
    FUN_100027f64((double)param_1 / (double)puVar10,dVar31,0,IVar16,IVar9,uVar27,IVar14,IVar12,0,0,0
                 );
    IVar9 = _objc_msgSend(IVar11,"midiEventsDefaultArrangement");
    puVar29 = PTR___sypN_100a1e038;
    if (IVar9 != 0) {
      puVar20 = (undefined *)_objc_msgSend(IVar9,"array");
      __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                (puVar20,puVar29 + 8);
      puVar10 = puVar20;
      FUN_1002d7d78();
      _swift_bridgeObjectRelease(puVar20);
      if (puVar10 != (undefined *)0x0) goto LAB_1004687fc;
    }
    puVar10 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
LAB_1004687fc:
    puVar20 = puVar10;
    _swift_isUniquelyReferencedNonObjC_nonNull_bridgeObject();
    if ((((int)puVar20 == 0) || ((long)puVar10 < 0)) ||
       (puVar20 = puVar10, ((ulong)puVar10 >> 0x3e & 1) != 0)) {
      if ((ulong)puVar10 >> 0x3e == 0) {
        puVar21 = *(undefined **)(((ulong)puVar10 & 0xfffffffffffff8) + 0x10);
      }
      else {
        puVar21 = (undefined *)((ulong)puVar10 & 0xffffffffffffff8);
        if ((long)puVar10 < 0) {
          puVar21 = puVar10;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg(puVar21);
      }
      puVar20 = (undefined *)0x0;
      FUN_1007900e0(0,puVar21 + 1,1,puVar10);
    }
    uVar25 = (ulong)puVar20 & 0xffffffffffffff8;
    uVar19 = *(ulong *)(uVar25 + 0x10);
    puVar10 = puVar20;
    if (*(ulong *)(uVar25 + 0x18) >> 1 <= uVar19) {
      puVar10 = (undefined *)(ulong)(1 < *(ulong *)(uVar25 + 0x18));
      FUN_1007900e0(puVar10,uVar19 + 1,1,puVar20);
      uVar25 = (ulong)puVar10 & 0xffffffffffffff8;
    }
    *(ulong *)(uVar25 + 0x10) = uVar19 + 1;
    *(ID *)(uVar25 + uVar19 * 8 + 0x20) = IVar16;
    puVar20 = puVar10;
    FUN_1001c61b8(puVar10);
    _swift_bridgeObjectRelease(puVar10);
    puVar21 = &_OBJC_CLASS___NSMutableOrderedSet;
    _objc_allocWithZone();
    puVar10 = puVar20;
    __sSa10FoundationE19_bridgeToObjectiveCSo7NSArrayCyF(puVar20,puVar29 + 8);
    _swift_bridgeObjectRelease(puVar20);
    IVar9 = _objc_msgSend((ID)puVar21,"initWithArray:",puVar10);
    _objc_msgSend(IVar11,"setMidiEventsDefaultArrangement:",IVar9);
    FUN_1005f1624(IVar16);
    _swift_release(uVar22);
    return (undefined8 *)0x0;
  }
  if (uVar19 == 0) {
    puVar5 = (undefined8 *)0x0;
    FUN_100459860(0,0,1,1,0,1,0);
    if (DAT_100adef08 != -1) {
      puVar5 = &DAT_100adef08;
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar24 = *(long *)(DAT_100b75e40 + 0x20);
    if (lVar24 == 0) {
      return puVar5;
    }
    puVar29 = *(undefined **)(lVar24 + _TtC8Playback9Sequencer::currentSongMapElement);
    if (puVar29 == (undefined *)0x0) {
      return puVar5;
    }
    uVar26 = *(undefined8 *)(lVar24 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
    _swift_retain(lVar24);
    _swift_retain(puVar29);
    _swift_retain(uVar26);
    __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
              (&local_b0,FUN_1003afbec,uVar26,PTR___sSdN_100a1dd60);
    _swift_release(uVar26);
    local_e8 = local_b0;
    FUN_1004f240c();
    puVar20 = *(undefined **)
               (unaff_x20 + _TtC8Playback22WaveformViewController::automationMarkerViews);
    puVar10 = param_1;
    if ((ulong)puVar20 >> 0x3e == 0) {
      _swift_bridgeObjectRetain_n(puVar20,2);
      puVar21 = puVar29;
      puVar17 = (undefined *)((ulong)puVar20 & 0xffffffffffffff8);
    }
    else {
      puVar21 = (undefined *)((ulong)puVar20 & 0xffffffffffffff8);
      if ((long)puVar20 < 0) {
        puVar21 = puVar20;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if (puVar21 != (undefined *)0x0) {
        puVar17 = puVar21;
        FUN_10078d9fc();
        _swift_bridgeObjectRetain_n(puVar20,3);
        _swift_retain(puVar29);
        puVar18 = puVar20;
        FUN_1005daf80(puVar17 + 0x20,puVar21);
        _swift_bridgeObjectRelease();
        if (puVar18 != puVar21) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ac4);
          (*pcVar3)();
        }
        _swift_bridgeObjectRelease(puVar20);
        goto LAB_100467878;
      }
      _swift_retain(puVar29);
      _swift_bridgeObjectRetain(puVar20);
      puVar21 = PTR___swiftEmptyArrayStorage_100a1e050;
      puVar17 = PTR___swiftEmptyArrayStorage_100a1e050;
    }
    _swift_retain(puVar21);
LAB_100467878:
    local_b0 = puVar17;
    FUN_10045514c(&local_b0);
    _swift_bridgeObjectRelease(puVar20);
    puVar20 = local_b0;
    if (((long)local_b0 < 0) || (((ulong)local_b0 >> 0x3e & 1) != 0)) {
      puVar21 = local_b0;
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    else {
      puVar21 = *(undefined **)(local_b0 + 0x10);
    }
    if (puVar21 != (undefined *)0x0) {
      local_f0 = puVar29;
      _swift_retain(puVar20);
      lVar28 = 4;
      do {
        lVar23 = lVar28 + -4;
        if (((ulong)puVar20 & 0xc000000000000001) == 0) {
          local_e0 = *(long *)(puVar20 + lVar28 * 8);
        }
        else {
          lVar8 = lVar23;
          FUN_1000cd4c0(lVar23,puVar20);
          local_e0 = lVar8;
        }
        if (SCARRY8(lVar23,1)) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x100468958);
          (*pcVar3)();
        }
        puVar29 = (undefined *)(lVar28 + -3);
        plVar1 = (long *)(local_e0 + _TtC8Playback18TimelineMarkerView::markerType);
        if (((char)plVar1[2] == '\0') &&
           (puVar10 = *(undefined **)(*plVar1 + 0x20), (double)puVar10 == (double)param_1)) {
          _swift_release_n(puVar20,2);
          IVar11 = local_e0;
          puVar29 = local_f0;
          if ((char)plVar1[2] != '\0') goto LAB_100467b74;
          lVar28 = *plVar1;
          puVar29 = (undefined *)plVar1[1];
          *(ID *)(unaff_x20 + _TtC8Playback22WaveformViewController::selectedTimelineMarkerView) =
               local_e0;
          FUN_100239d00(lVar28,puVar29,0);
          local_e8 = puVar29;
          FUN_100239d00(lVar28,puVar29,0);
          lVar23 = 0;
          FUN_100465034();
          local_e0 = IVar11;
          if ((lVar23 != 0) &&
             (*(long *)(lVar23 + _TtC8Playback18MainViewController::transportViewController) != 0))
          {
            FUN_100868a50(IVar11);
          }
          uVar19 = *(ulong *)(lVar28 + 0x10);
          lVar23 = unaff_x20 + _TtC8Playback22WaveformViewController::automationCopyCue;
          _swift_unknownObjectWeakLoadStrong();
          IVar11 = unaff_x20 + _TtC8Playback22WaveformViewController::playheadAddButton;
          _swift_unknownObjectWeakLoadStrong();
          local_f8 = IVar11;
          if (IVar11 == 0) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ad0);
            (*pcVar3)();
          }
          pcVar7 = (class_t *)0x0;
          FUN_100589fc4();
          pcVar13 = pcVar7;
          _objc_allocWithZone();
          puVar5 = (undefined8 *)
                   ((long)&pcVar13->isa +
                   _TtC8Playback36AutomationEditingTableViewController::stagedName);
          *puVar5 = 0;
          puVar5[1] = 0xe000000000000000;
          *(undefined2 *)
           ((long)&pcVar13->isa +
           _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) = 0;
          puVar5 = (undefined8 *)
                   ((long)&pcVar13->isa +
                   _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
          *puVar5 = 0;
          puVar5[1] = 0xe000000000000000;
          lVar8 = _TtC8Playback36AutomationEditingTableViewController::copyCue;
          *(undefined8 *)
           ((long)&pcVar13->isa + _TtC8Playback36AutomationEditingTableViewController::copyCue) = 0;
          *(undefined8 *)
           ((long)&pcVar13->isa +
           _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) = 0;
          puVar2 = (ulong *)((long)&pcVar13->isa +
                            _TtC8Playback36AutomationEditingTableViewController::mode);
          *puVar2 = uVar19 | 0x8000000000000000;
          puVar2[1] = 0;
          puVar2[2] = 0;
          *(undefined ***)
           ((long)&pcVar13->superclass +
           _TtC8Playback36AutomationEditingTableViewController::delegate) = &PTR_PTR_100a6f5e8;
          _swift_unknownObjectUnownedInit();
          local_100 = *(undefined8 *)((long)&pcVar13->isa + lVar8);
          *(long *)((long)&pcVar13->isa + lVar8) = lVar23;
          local_d8.receiver = (ID)pcVar13;
          local_d8.super_class = pcVar7;
          IVar9 = _objc_msgSendSuper2(&local_d8,"initWithStyle:",1);
          puVar29 = &_OBJC_CLASS___UINavigationController;
          _objc_allocWithZone();
          IVar11 = _objc_msgSend((ID)puVar29,"initWithRootViewController:",IVar9);
          IVar9 = _objc_msgSend(IVar9,"tableView");
          if (IVar9 == 0) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ad4);
            (*pcVar3)();
          }
          _objc_msgSend(IVar9,"contentSize");
          _objc_msgSend(IVar11,"setPreferredContentSize:");
          IVar9 = local_f8;
          _objc_msgSend(local_f8,"bounds");
          local_90 = 0;
          local_b0 = puVar10;
          uStack_a8 = param_2;
          local_a0 = (undefined *)param_3;
          puStack_98 = (undefined *)param_4;
          FUN_100430978(0,1,0xc,0,IVar9,&local_b0,0);
          FUN_100239d24(lVar28,local_e8,0);
          puVar29 = local_f0;
          goto LAB_100467d7c;
        }
        lVar28 = lVar28 + 1;
      } while (puVar29 != puVar21);
      _swift_release(puVar20);
      puVar29 = local_f0;
    }
    _swift_release(puVar20);
    local_e0 = 0;
LAB_100467b74:
    lVar28 = unaff_x20 + _TtC8Playback22WaveformViewController::automationCopyCue;
    _swift_unknownObjectWeakLoadStrong();
    IVar9 = unaff_x20 + _TtC8Playback22WaveformViewController::playheadAddButton;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar9 == 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x100468abc);
      (*pcVar3)();
    }
    pcVar7 = (class_t *)0x0;
    FUN_100589fc4();
    pcVar13 = pcVar7;
    _objc_allocWithZone();
    puVar5 = (undefined8 *)
             ((long)&pcVar13->isa + _TtC8Playback36AutomationEditingTableViewController::stagedName)
    ;
    *puVar5 = 0;
    puVar5[1] = 0xe000000000000000;
    *(undefined2 *)
     ((long)&pcVar13->isa +
     _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) = 0;
    puVar5 = (undefined8 *)
             ((long)&pcVar13->isa +
             _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
    *puVar5 = 0;
    puVar5[1] = 0xe000000000000000;
    lVar23 = _TtC8Playback36AutomationEditingTableViewController::copyCue;
    *(undefined8 *)
     ((long)&pcVar13->isa + _TtC8Playback36AutomationEditingTableViewController::copyCue) = 0;
    *(undefined8 *)
     ((long)&pcVar13->isa +
     _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) = 0;
    puVar5 = (undefined8 *)
             ((long)&pcVar13->isa + _TtC8Playback36AutomationEditingTableViewController::mode);
    *puVar5 = puVar29;
    puVar5[1] = local_e8;
    puVar5[2] = param_1;
    *(undefined ***)
     ((long)&pcVar13->superclass + _TtC8Playback36AutomationEditingTableViewController::delegate) =
         &PTR_PTR_100a6f5e8;
    _swift_unknownObjectUnownedInit();
    *(long *)((long)&pcVar13->isa + lVar23) = lVar28;
    _swift_retain_n(puVar29,2);
    local_c8.receiver = (ID)pcVar13;
    local_c8.super_class = pcVar7;
    IVar12 = _objc_msgSendSuper2(&local_c8,"initWithStyle:",1);
    puVar20 = &_OBJC_CLASS___UINavigationController;
    _objc_allocWithZone();
    IVar11 = _objc_msgSend((ID)puVar20,"initWithRootViewController:",IVar12);
    IVar12 = _objc_msgSend(IVar12,"tableView");
    if (IVar12 == 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ac0);
      (*pcVar3)();
    }
    _objc_msgSend(IVar12,"contentSize");
    _objc_msgSend(IVar11,"setPreferredContentSize:");
    _objc_msgSend(IVar9,"bounds");
    local_90 = 0;
    local_b0 = puVar10;
    uStack_a8 = param_2;
    local_a0 = (undefined *)param_3;
    puStack_98 = (undefined *)param_4;
    FUN_100430978(0,1,0xc,0,IVar9,&local_b0,0);
    _swift_release(puVar29);
    lVar28 = 0;
LAB_100467d7c:
    _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar11,1,0);
    _swift_release(lVar24);
    _swift_release(lVar28);
    _swift_release_n(puVar29,2);
    FUN_100092550(uVar22);
    return (undefined8 *)0x0;
  }
  if (uVar19 != 1) {
    return puVar5;
  }
  IVar11 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar11 == 0) {
    return (undefined8 *)0x0;
  }
  FUN_1004a9df0();
  if (IVar11 == 0) {
    return (undefined8 *)0x0;
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar23 = *(long *)(DAT_100b75e40 + 0x20);
  if (lVar23 == 0) {
    return (undefined8 *)0x0;
  }
  if ((*(byte *)(lVar23 + _TtC8Playback9Sequencer::privatePlayState) & 1) != 0) {
    return (undefined8 *)0x0;
  }
  _swift_retain(lVar23);
  FUN_100459860(0,0,1,0,0,1,0);
  uVar26 = *(undefined8 *)(lVar23 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
  _swift_retain(uVar26);
  __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
            (&local_b0,FUN_1003afbec,uVar26,PTR___sSdN_100a1dd60);
  _swift_release(uVar26);
  FUN_1003220ec();
  param_1 = (undefined *)((double)local_b0 / (double)param_1);
  lVar8 = 0;
  __ss25FloatingPointRoundingRuleOMa();
  (**(code **)(*(long *)(lVar8 + -8) + 0x38))(lVar24,1,1,lVar8);
  thunk_FUN_100035714(3,lVar24);
  FUN_100023be4(lVar24,&DAT_100af5490);
  lVar24 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar9 = *(ID *)(IVar11 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar9 == 0) {
    IVar12 = _objc_msgSend(IVar11,"workingCopyArrangementID");
    if (IVar12 == 0) goto LAB_100468198;
    IVar14 = IVar12;
    FUN_10032ee88();
    IVar9 = IVar14;
    FUN_1005e3b94(IVar14,IVar12);
    _swift_bridgeObjectRelease(IVar14);
    if (IVar9 == 0) goto LAB_100468198;
    *(ID *)(IVar11 + lVar24) = IVar9;
  }
  IVar9 = _objc_msgSend(IVar9,"storedSections");
  if (IVar9 == 0) {
LAB_100467f3c:
    puVar29 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    puVar10 = (undefined *)_objc_msgSend(IVar9,"array");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (puVar10,PTR___sypN_100a1e038 + 8);
    puVar29 = puVar10;
    FUN_1002d7d28();
    _swift_bridgeObjectRelease(puVar10);
    if (puVar29 == (undefined *)0x0) goto LAB_100467f3c;
  }
  puVar10 = puVar29;
  FUN_100465838(puVar29,IVar11);
  _swift_bridgeObjectRelease(puVar29);
  lVar24 = _TtC8Playback22WaveformViewController::playheadAddButton;
  if (puVar10 != (undefined *)0x0) {
    lVar8 = unaff_x20 + _TtC8Playback22WaveformViewController::playheadAddButton;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar8 == 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x100468ac8);
      (*pcVar3)();
    }
    IVar11 = unaff_x20 + lVar24;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar11 == 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(1,0x100468acc);
      (*pcVar3)();
    }
    _objc_msgSend(IVar11,"bounds");
    lVar28 = unaff_x20 + lVar28;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar28 == 0) {
      _swift_release(lVar23);
      return (undefined8 *)0x0;
    }
    puVar29 = puVar10;
    FUN_1004a9df0();
    if (puVar29 != (undefined *)0x0) {
      FUN_10077d4a8(0);
      _objc_allocWithZone();
      FUN_100464e60(puVar10,puVar29);
      IVar11 = 0;
      FUN_1007f6a7c();
      _objc_allocWithZone();
      IVar11 = _objc_msgSend(IVar11,"initWithRootViewController:",puVar10);
      local_90 = 0;
      local_b0 = param_1;
      uStack_a8 = param_2;
      local_a0 = (undefined *)param_3;
      puStack_98 = (undefined *)param_4;
      FUN_100430978(0,1,0xc,0,lVar8,&local_b0,0);
      _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar11,1,0);
      _swift_release(lVar23);
      return (undefined8 *)0x0;
    }
    _swift_release(lVar23);
    return (undefined8 *)0x0;
  }
LAB_100468198:
  FUN_100459d10(0);
  _swift_release(lVar23);
  return (undefined8 *)0x0;
}

// ==== 100471d84 _TtC8Playback27MixerPadPanelViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback27MixerPadPanelViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback27MixerPadPanelViewController *this,ID param_1,SEL param_2,CGSize param_3,
          ID param_4)

{
  class_t *pcVar1;
  double dVar2;
  objc_super local_50;
  
  dVar2 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  _swift_unknownObjectRetain(dVar2);
  _objc_msgSendSuper2(&local_50,"viewWillTransitionToSize:withTransitionCoordinator:",dVar2);
  FUN_100471c50();
  _swift_unknownObjectRelease(dVar2);
  return;
}

// ==== 1004bad90 FUN_1004bad90 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined1  [16] FUN_1004bad90(void)

{
  uint uVar1;
  ulong uVar2;
  code *pcVar3;
  bool bVar4;
  long lVar5;
  ID IVar6;
  char *pcVar7;
  ulong uVar8;
  ulong uVar9;
  ID IVar10;
  ID IVar11;
  undefined *self;
  undefined8 *puVar12;
  undefined1 *puVar13;
  undefined *puVar14;
  char *pcVar15;
  long lVar16;
  ulong uVar17;
  ID unaff_x20;
  char *pcVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  ID IVar21;
  ulong uVar22;
  undefined *puVar23;
  long lVar24;
  char *pcVar25;
  long lVar26;
  undefined1 auVar27 [16];
  char acStack_130 [8];
  undefined *local_128;
  char *local_120;
  ulong local_118;
  undefined8 local_110;
  char *local_108;
  ID local_100;
  char *local_f8;
  long local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  ID local_d8;
  char *local_d0;
  ulong local_c8;
  char *local_c0;
  undefined8 local_b8;
  ulong local_b0;
  char *local_a8;
  undefined8 local_a0;
  char *local_98;
  char *local_88;
  undefined *local_80;
  ID local_78;
  char *local_70;
  
  IVar21 = 0x3e6c696e3c;
  lVar5 = 0;
  __s10Foundation4DateVMa();
  lVar26 = *(long *)(lVar5 + -8);
  lVar16 = *(long *)(lVar26 + 0x40);
  puVar14 = &DAT_100af56b8;
  local_98 = acStack_130 + -(lVar16 + 0xfU & 0xfffffffffffffff0);
  FUN_100021774();
  uVar17 = *(long *)(*(long *)(puVar14 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0;
  lVar24 = (long)(acStack_130 + -(lVar16 + 0xfU & 0xfffffffffffffff0)) - uVar17;
  lVar16 = lVar24 - uVar17;
  puVar14 = &DAT_100af52f0;
  FUN_100021774();
  _swift_allocObject();
  *(undefined8 *)(puVar14 + 0x18) = 0x12;
  *(undefined8 *)(puVar14 + 0x10) = 9;
  *(undefined8 *)(puVar14 + 0x20) = 0x5453494c544553;
  *(undefined8 *)(puVar14 + 0x28) = 0xe700000000000000;
  *(undefined8 *)(puVar14 + 0x30) = 0x2d2d2d2d2d2d2d;
  *(undefined8 *)(puVar14 + 0x38) = 0xe700000000000000;
  local_78 = _objc_msgSend(unaff_x20,"setlistID");
  puVar23 = PTR___ss5Int64Vs23CustomStringConvertiblesWP_100a1df80;
  __ss23CustomStringConvertibleP11descriptionSSvgTj
            (PTR___ss5Int64VN_100a1df58,PTR___ss5Int64Vs23CustomStringConvertiblesWP_100a1df80);
  local_78 = 0x207473696c746553;
  local_70 = (char *)0xec000000203a4449;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(puVar23);
  *(ID *)(puVar14 + 0x40) = local_78;
  *(char **)(puVar14 + 0x48) = local_70;
  IVar6 = _objc_msgSend(unaff_x20,"serverVersion");
  local_78 = CONCAT44(local_78._4_4_,(int)IVar6);
  puVar23 = PTR___ss5Int32Vs23CustomStringConvertiblesWP_100a1df40;
  __ss23CustomStringConvertibleP11descriptionSSvgTj
            (PTR___ss5Int32VN_100a1df28,PTR___ss5Int32Vs23CustomStringConvertiblesWP_100a1df40);
  local_78 = 0x3a6e6f6973726556;
  local_70 = (char *)0xe900000000000020;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(puVar23);
  *(ID *)(puVar14 + 0x50) = local_78;
  *(char **)(puVar14 + 0x58) = local_70;
  pcVar15 = "title";
  local_128 = puVar14;
  IVar6 = _objc_msgSend(unaff_x20,"title");
  if (IVar6 == 0) {
    pcVar15 = &DAT_e500000000000000;
    IVar6 = IVar21;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  local_78 = 0x203a656c746954;
  local_70 = (char *)0xe700000000000000;
  __sSS6appendyySSF(IVar6,pcVar15);
  _swift_bridgeObjectRelease(pcVar15);
  *(ID *)(local_128 + 0x60) = local_78;
  *(char **)(local_128 + 0x68) = local_70;
  IVar6 = _objc_msgSend(unaff_x20,"performanceDate");
  if (IVar6 != 0) {
    __s10Foundation4DateV36_unconditionallyBridgeFromObjectiveCyACSo6NSDateCSgFZ(lVar24);
  }
  (**(code **)(lVar26 + 0x38))(lVar24,IVar6 == 0,1,lVar5);
  FUN_1000c32e4(lVar24,lVar16,&DAT_100af56b8);
  lVar24 = lVar16;
  (**(code **)(lVar26 + 0x30))(lVar16,1,lVar5);
  pcVar15 = local_98;
  if ((int)lVar24 == 0) {
    (**(code **)(lVar26 + 0x10))(local_98,lVar16,lVar5);
    FUN_100023be4(lVar16,&DAT_100af56b8);
    puVar14 = &_OBJC_CLASS___NSDateFormatter;
    _objc_allocWithZone();
    IVar6 = _objc_msgSend((ID)puVar14,"init");
    _objc_msgSend(IVar6,"setDateStyle:",2);
    IVar10 = _objc_msgSend(IVar6,"setTimeStyle:",1);
    __s10Foundation4DateV19_bridgeToObjectiveCSo6NSDateCyF();
    pcVar18 = "stringFromDate:";
    IVar6 = _objc_msgSend(IVar6,"stringFromDate:",IVar10);
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    (**(code **)(lVar26 + 8))(pcVar15,lVar5);
  }
  else {
    FUN_100023be4(lVar16,&DAT_100af56b8);
    IVar6 = 0;
    pcVar18 = (char *)0x0;
  }
  puVar14 = &DAT_100af5bb8;
  local_78 = IVar6;
  local_70 = pcVar18;
  FUN_100021774(&DAT_100af5bb8);
  __sSS10describingSSx_tclufC(&local_78,puVar14);
  local_78 = 0xd000000000000012;
  local_70 = (char *)0x80000001008fa620;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(puVar14);
  puVar14 = local_128;
  *(ID *)(local_128 + 0x70) = local_78;
  *(char **)(local_128 + 0x78) = local_70;
  IVar6 = _objc_msgSend(unaff_x20,"isReported");
  bVar4 = (int)IVar6 == 0;
  local_78 = 0x646574726f706552;
  if (bVar4) {
    local_78 = 0x6f70655220746f4e;
  }
  local_70 = (char *)0xe800000000000000;
  if (bVar4) {
    local_70 = (char *)0xec00000064657472;
  }
  puVar23 = PTR___sSSN_100a1dce0;
  __sSSySSxcs25LosslessStringConvertibleRzSTRzSJ7ElementSTRtzlufC
            (&local_78,PTR___sSSN_100a1dce0,PTR___sSSs25LosslessStringConvertiblesWP_100a1dd10,
             PTR___sSSSTsWP_100a1dcf8);
  local_b8 = 0xd000000000000010;
  local_78 = 0xd000000000000010;
  local_70 = (char *)0x80000001008fa640;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(puVar23);
  *(ID *)(puVar14 + 0x80) = local_78;
  *(char **)(puVar14 + 0x88) = local_70;
  pcVar15 = "setlistSaveError";
  IVar6 = _objc_msgSend(unaff_x20,"setlistSaveError");
  if (IVar6 == 0) {
    pcVar15 = &DAT_e500000000000000;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    IVar21 = IVar6;
  }
  pcVar18 = (char *)0xec0000000a2d2d2d;
  local_78 = 0xd000000000000013;
  local_70 = (char *)0x80000001008fa660;
  __sSS6appendyySSF(IVar21,pcVar15);
  _swift_bridgeObjectRelease();
  *(ID *)(local_128 + 0x90) = local_78;
  *(char **)(local_128 + 0x98) = local_70;
  *(undefined8 *)(local_128 + 0xa0) = 10;
  *(undefined8 *)(local_128 + 0xa8) = 0xe100000000000000;
  local_78 = 0x2d2d0a53474e4f53;
  local_70 = (char *)0xec0000000a2d2d2d;
  FUN_1004a6154();
  if ((ulong)pcVar15 >> 0x3e == 0) {
    pcVar25 = *(char **)(((ulong)pcVar15 & 0xfffffffffffff8) + 0x10);
  }
  else {
    pcVar25 = (char *)((ulong)pcVar15 & 0xffffffffffffff8);
    if ((long)pcVar15 < 0) {
      pcVar25 = pcVar15;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (pcVar25 == (char *)0x0) {
    _swift_bridgeObjectRelease(pcVar15);
    IVar21 = 0x2d2d0a53474e4f53;
  }
  else {
    pcVar18 = (char *)0x0;
    local_a0 = 0;
    local_d8 = 0x80000001008fa6a0;
    local_d0 = "Latest Save Error: ";
    local_e8 = 0x80000001008fa6e0;
    local_e0 = 0x80000001008fa6c0;
    local_c8 = (ulong)pcVar15 & 0xc000000000000001;
    local_118 = (ulong)pcVar15 & 0xffffffffffffff8;
    local_120 = pcVar15 + 0x20;
    local_110 = 0x80000001008fa750;
    local_108 = "<No Working Copy Arrangement>";
    local_100 = 0x80000001008fa700;
    local_f8 = pcVar15;
    local_c0 = pcVar25;
    do {
      if (local_c8 == 0) {
        if (*(char **)(local_118 + 0x10) <= pcVar18) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(1,0x1004bc194);
          (*pcVar3)();
        }
        pcVar7 = *(char **)(local_120 + (long)pcVar18 * 8);
      }
      else {
        pcVar7 = pcVar18;
        FUN_1000cbedc(pcVar18,pcVar15);
      }
      bVar4 = SCARRY8((long)pcVar18,1);
      pcVar18 = pcVar18 + 1;
      if (bVar4) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(1,0x1004bc188);
        (*pcVar3)();
      }
      puVar14 = PTR___sSiN_100a1dd88;
      puVar23 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
      local_88 = pcVar18;
      __ss23CustomStringConvertibleP11descriptionSSvgTj();
      local_88 = puVar14;
      local_80 = puVar23;
      _swift_bridgeObjectRetain(puVar23);
      __sSS6appendyySSF(0x93a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar23);
      puVar14 = local_80;
      puVar23 = local_80;
      __sSS6appendyySSF(local_88);
      _swift_bridgeObjectRelease();
      FUN_100334724();
      local_88 = puVar14;
      local_80 = puVar23;
      _swift_bridgeObjectRetain(puVar23);
      __sSS6appendyySSF(0x90a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar23);
      puVar14 = local_80;
      __sSS6appendyySSF(local_88,local_80);
      _swift_bridgeObjectRelease(puVar14);
      lVar5 = _TtC8Playback4Song::privateWorkingCopyArrangement;
      uVar17 = *(ulong *)(pcVar7 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      local_98 = pcVar7;
      if (uVar17 == 0) {
        IVar21 = _objc_msgSend((ID)pcVar7,"workingCopyArrangementID");
        if (IVar21 != 0) {
          IVar6 = IVar21;
          FUN_10032ee88();
          uVar19 = local_a0;
          IVar10 = IVar6;
          FUN_1005e3b94(IVar6,IVar21);
          local_a0 = uVar19;
          _swift_bridgeObjectRelease(IVar6);
          if (IVar10 != 0) {
            *(ID *)(pcVar7 + lVar5) = IVar10;
            uVar17 = 0;
            goto LAB_1004bb4dc;
          }
        }
        uVar19 = 0xd00000000000001d;
        IVar21 = local_100;
      }
      else {
LAB_1004bb4dc:
        FUN_1002da058();
        uVar1 = (uint)uVar17 & 0xff;
        if (uVar1 < 3) {
          if ((uVar17 & 0xff) == 0) {
            uVar19 = 0x7478654e20657543;
            IVar21 = 0xed0000676e6f5320;
          }
          else {
            uVar19 = 0x6b6e694c6f747541;
            if (uVar1 != 1) {
              uVar19 = 0x70616c7265764f;
            }
            IVar21 = 0xe800000000000000;
            if (uVar1 != 1) {
              IVar21 = 0xe700000000000000;
            }
          }
        }
        else if (uVar1 == 3) {
          uVar19 = 0x64616673736f7243;
          IVar21 = 0xe900000000000065;
        }
        else if (uVar1 == 4) {
          uVar19 = 0x206e492079617453;
          IVar21 = 0xec000000676e6f53;
        }
        else {
          uVar19 = 0x7372694620657543;
          IVar21 = 0xee00676e6f532074;
        }
      }
      pcVar7 = local_98;
      IVar6 = *(ID *)(local_98 + lVar5);
      if (IVar6 == 0) {
        IVar10 = _objc_msgSend((ID)local_98,"workingCopyArrangementID");
        uVar17 = 0;
        if (IVar10 != 0) {
          IVar11 = IVar10;
          FUN_10032ee88();
          uVar20 = local_a0;
          IVar6 = IVar11;
          FUN_1005e3b94(IVar11,IVar10);
          local_a0 = uVar20;
          _swift_bridgeObjectRelease(IVar11);
          pcVar25 = local_c0;
          if (IVar6 != 0) {
            *(ID *)(pcVar7 + lVar5) = IVar6;
            goto LAB_1004bb680;
          }
          uVar17 = 0;
        }
      }
      else {
LAB_1004bb680:
        uVar17 = _objc_msgSend(IVar6,"transitionContinuePad");
      }
      local_88 = (char *)0x202d2d;
      local_80 = (undefined *)0xe300000000000000;
      __sSS6appendyySSF(uVar19,IVar21);
      _swift_bridgeObjectRelease(IVar21);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(local_b8,(ulong)local_d0 | 0x8000000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      bVar4 = (uVar17 & 1) == 0;
      uVar19 = 0x65757274;
      if (bVar4) {
        uVar19 = 0x65736c6166;
      }
      puVar13 = (undefined1 *)0xe400000000000000;
      if (bVar4) {
        puVar13 = &DAT_e500000000000000;
      }
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(uVar19,puVar13);
      _swift_bridgeObjectRelease(puVar14);
      _swift_bridgeObjectRelease(puVar13);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x29,0xe100000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x2d2d20,0xe300000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x90a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      puVar23 = local_80;
      __sSS6appendyySSF(local_88,local_80);
      _swift_bridgeObjectRelease(puVar14);
      pcVar7 = local_98;
      FUN_1003390f0();
      local_88 = (char *)0x1000000000000012;
      local_80 = (undefined *)local_d8;
      __sSS6appendyySSF();
      _swift_bridgeObjectRelease(puVar23);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x90a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      puVar23 = local_80;
      __sSS6appendyySSF(local_88,local_80);
      _swift_bridgeObjectRelease(puVar14);
      lVar16 = *(long *)(pcVar7 + lVar5);
      if (lVar16 == 0) {
        puVar23 = (undefined *)_objc_msgSend((ID)pcVar7,"workingCopyArrangementID");
        if (puVar23 == (undefined *)0x0) {
          lVar16 = -0x2fffffffffffffe3;
          puVar23 = (undefined *)local_100;
        }
        else {
          IVar21 = (ID)puVar23;
          FUN_10032ee88();
          uVar19 = local_a0;
          IVar6 = IVar21;
          FUN_1005e3b94(IVar21,puVar23);
          local_a0 = uVar19;
          _swift_bridgeObjectRelease(IVar21);
          if (IVar6 != 0) {
            *(ID *)(pcVar7 + lVar5) = IVar6;
            lVar16 = 0;
            goto LAB_1004bb84c;
          }
          lVar16 = -0x2fffffffffffffe3;
          puVar23 = (undefined *)local_100;
        }
      }
      else {
LAB_1004bb84c:
        FUN_1002e438c(lVar16);
      }
      local_88 = (undefined *)0x1000000000000012;
      local_80 = (undefined *)local_e0;
      __sSS6appendyySSF(lVar16,puVar23);
      _swift_bridgeObjectRelease(puVar23);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x90a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      __sSS6appendyySSF(local_88,local_80);
      _swift_bridgeObjectRelease(puVar14);
      uVar8 = *(ulong *)(pcVar7 + lVar5);
      uVar17 = uVar8;
      if (uVar8 == 0) {
        IVar21 = _objc_msgSend((ID)pcVar7,"workingCopyArrangementID");
        if (IVar21 == 0) {
          puVar13 = (undefined1 *)0xd00000000000001d;
          IVar21 = local_100;
        }
        else {
          IVar6 = IVar21;
          FUN_10032ee88();
          uVar19 = local_a0;
          uVar17 = IVar6;
          FUN_1005e3b94(IVar6,IVar21);
          local_a0 = uVar19;
          _swift_bridgeObjectRelease(IVar6);
          if (uVar17 != 0) {
            *(ulong *)(pcVar7 + lVar5) = uVar17;
            uVar8 = 0;
            goto LAB_1004bb8d8;
          }
          puVar13 = (undefined1 *)0xd00000000000001d;
          IVar21 = local_100;
        }
      }
      else {
LAB_1004bb8d8:
        local_b0 = uVar17;
        FUN_1002f6e9c();
        if (uVar8 >> 0x3e == 0) {
          uVar17 = *(ulong *)((uVar8 & 0xfffffffffffff8) + 0x10);
          if (uVar17 == 0) goto LAB_1004bbc6c;
LAB_1004bb900:
          if ((long)uVar17 < 1) {
                    /* WARNING: Does not return */
            pcVar3 = (code *)SoftwareBreakpoint(1,0x1004bc18c);
            local_a8 = pcVar18;
            (*pcVar3)();
          }
          local_a8 = pcVar18;
          _swift_bridgeObjectRetain(uVar8);
          pcVar15 = PTR___swiftEmptyArrayStorage_100a1e050;
          _swift_retain();
          uVar22 = 0;
          do {
            if ((uVar8 & 0xc000000000000001) == 0) {
              uVar9 = *(ulong *)(uVar8 + uVar22 * 8 + 0x20);
            }
            else {
              uVar9 = uVar22;
              FUN_1000cc338(uVar22,uVar8);
            }
            if (DAT_100adfbd0 != -1) {
              _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            }
            if ((*(byte *)(uVar9 + _TtC8Playback9SongTrack::soloState) & 1) == 0) {
              puVar14 = pcVar15;
              _swift_isUniquelyReferenced_nonNull_native();
              local_88 = pcVar15;
              if (((ulong)puVar14 & 1) == 0) {
                FUN_1001cc4d4(0,*(long *)(pcVar15 + 0x10) + 1,1);
              }
              uVar2 = *(ulong *)(local_88 + 0x10);
              if (*(ulong *)(local_88 + 0x18) >> 1 <= uVar2) {
                FUN_1001cc4d4(1 < *(ulong *)(local_88 + 0x18),uVar2 + 1,1);
              }
              *(ulong *)(local_88 + 0x10) = uVar2 + 1;
              *(ulong *)(local_88 + uVar2 * 8 + 0x20) = uVar9;
              pcVar15 = local_88;
            }
            uVar22 = uVar22 + 1;
          } while (uVar17 != uVar22);
          _swift_bridgeObjectRelease(uVar8);
          if (-1 < (long)pcVar15) goto LAB_1004bbc84;
LAB_1004bbe18:
          pcVar7 = local_98;
          puVar14 = pcVar15;
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (puVar14 != (undefined *)0x0) {
            puVar14 = pcVar15;
            __ss18_CocoaArrayWrapperV8endIndexSivg();
            pcVar18 = PTR___swiftEmptyArrayStorage_100a1e050;
            if (puVar14 == (undefined *)0x0) {
              _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
              _swift_release(pcVar15);
            }
            else {
LAB_1004bbc90:
              local_88 = PTR___swiftEmptyArrayStorage_100a1e050;
              _swift_retain();
              FUN_1001cc2e4(0,(ulong)puVar14 & ((long)puVar14 >> 0x3f ^ 0xffffffffffffffffU),0);
              if ((long)puVar14 < 0) {
                    /* WARNING: Does not return */
                pcVar3 = (code *)SoftwareBreakpoint(1,0x1004bc190);
                (*pcVar3)();
              }
              local_f0 = lVar5;
              puVar23 = (undefined *)0x0;
              do {
                pcVar18 = local_88;
                if (((ulong)pcVar15 & 0xc000000000000001) == 0) {
                  self = *(undefined **)(pcVar15 + (long)puVar23 * 8 + 0x20);
                }
                else {
                  self = puVar23;
                  FUN_1000cc338(puVar23,pcVar15);
                }
                pcVar25 = "title";
                IVar21 = _objc_msgSend((ID)self,"title");
                if (IVar21 == 0) {
                  IVar21 = 0;
                  pcVar25 = (char *)0xe000000000000000;
                }
                else {
                  __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
                }
                uVar17 = *(ulong *)(pcVar18 + 0x10);
                local_88 = pcVar18;
                if (*(ulong *)(pcVar18 + 0x18) >> 1 <= uVar17) {
                  FUN_1001cc2e4(1 < *(ulong *)(pcVar18 + 0x18),uVar17 + 1,1);
                }
                pcVar18 = local_88;
                puVar23 = puVar23 + 1;
                *(ulong *)(local_88 + 0x10) = uVar17 + 1;
                *(ID *)(local_88 + uVar17 * 0x10 + 0x20) = IVar21;
                *(char **)(local_88 + uVar17 * 0x10 + 0x28) = pcVar25;
              } while (puVar14 != puVar23);
              _swift_release(pcVar15);
              lVar5 = local_f0;
            }
            puVar14 = &DAT_100af52f8;
            local_88 = pcVar18;
            FUN_100021774(&DAT_100af52f8);
            puVar12 = &DAT_100af5300;
            FUN_1004d3b88(&DAT_100af5300,&DAT_100af5308,PTR___sSaMa_100a1dd18,
                          PTR___sSayxGSKsMc_100a1dd28);
            puVar13 = (undefined1 *)0x202c;
            IVar21 = 0xe200000000000000;
            __sSKsSS7ElementRtzrlE6joined9separatorS2S_tF(0x202c,0xe200000000000000,puVar14,puVar12)
            ;
            _swift_bridgeObjectRelease(pcVar18);
            pcVar7 = local_98;
            pcVar15 = local_f8;
            pcVar25 = local_c0;
            pcVar18 = local_a8;
            goto LAB_1004bbe78;
          }
        }
        else {
          uVar17 = uVar8 & 0xffffffffffffff8;
          if ((long)uVar8 < 0) {
            uVar17 = uVar8;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (uVar17 != 0) goto LAB_1004bb900;
LAB_1004bbc6c:
          pcVar15 = PTR___swiftEmptyArrayStorage_100a1e050;
          local_a8 = pcVar18;
          _swift_retain();
          if ((long)pcVar15 < 0) goto LAB_1004bbe18;
LAB_1004bbc84:
          if (((ulong)pcVar15 >> 0x3e & 1) != 0) goto LAB_1004bbe18;
          puVar14 = *(undefined **)(pcVar15 + 0x10);
          pcVar7 = local_98;
          if (puVar14 != (undefined *)0x0) goto LAB_1004bbc90;
        }
        _swift_release(pcVar15);
        puVar13 = &DAT_656e6f4e;
        IVar21 = 0xe400000000000000;
        pcVar15 = local_f8;
        pcVar25 = local_c0;
        pcVar18 = local_a8;
      }
LAB_1004bbe78:
      local_88 = (char *)0x1000000000000012;
      local_80 = (undefined *)local_e8;
      __sSS6appendyySSF(puVar13,IVar21);
      _swift_bridgeObjectRelease(IVar21);
      puVar14 = local_80;
      _swift_bridgeObjectRetain(local_80);
      __sSS6appendyySSF(0x90a,0xe200000000000000);
      _swift_bridgeObjectRelease(puVar14);
      puVar14 = local_80;
      __sSS6appendyySSF(local_88,local_80);
      _swift_bridgeObjectRelease(puVar14);
      uVar17 = *(ulong *)(pcVar7 + lVar5);
      if (uVar17 == 0) {
        IVar21 = _objc_msgSend((ID)pcVar7,"workingCopyArrangementID");
        if (IVar21 != 0) {
          IVar6 = IVar21;
          FUN_10032ee88();
          uVar19 = local_a0;
          IVar10 = IVar6;
          FUN_1005e3b94(IVar6,IVar21);
          local_a0 = uVar19;
          _swift_bridgeObjectRelease(IVar6);
          if (IVar10 != 0) {
            *(ID *)(pcVar7 + lVar5) = IVar10;
            uVar17 = 0;
            goto LAB_1004bbee8;
          }
        }
LAB_1004bb3a4:
        __sSS6appendyySSF(0x100000000000002f,(ulong)local_108 | 0x8000000000000000);
      }
      else {
LAB_1004bbee8:
        FUN_1002de548();
        if (uVar17 >> 0x3e == 0) {
          uVar8 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
          _swift_bridgeObjectRelease();
        }
        else {
          uVar8 = uVar17 & 0xffffffffffffff8;
          if ((long)uVar17 < 0) {
            uVar8 = uVar17;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          _swift_bridgeObjectRelease();
        }
        if (uVar8 == 0) goto LAB_1004bb3a4;
        FUN_1002de548();
        if (uVar17 >> 0x3e == 0) {
          uVar8 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
          if (uVar8 == 0) goto LAB_1004bc0dc;
LAB_1004bbf2c:
          _swift_bridgeObjectRetain(uVar17);
          lVar5 = 4;
          do {
            lVar16 = lVar5 + -4;
            if ((uVar17 & 0xc000000000000001) == 0) {
              lVar24 = *(long *)(uVar17 + lVar5 * 8);
            }
            else {
              lVar24 = lVar16;
              FUN_1000cc338(lVar16,uVar17);
            }
            if (SCARRY8(lVar16,1)) {
                    /* WARNING: Does not return */
              pcVar3 = (code *)SoftwareBreakpoint(1,0x1004bc184);
              (*pcVar3)();
            }
            uVar22 = lVar5 - 3;
            if (DAT_100adfbd0 != -1) {
              _swift_once(&DAT_100adfbd0,FUN_1005d0614);
            }
            if (*(char *)(lVar24 + _TtC8Playback9SongTrack::soloState) != '\x01') {
              uVar19 = 0xe600000000000000;
              uVar20 = 0x64656f6c6f53;
              goto LAB_1004bc084;
            }
            lVar5 = lVar5 + 1;
          } while (uVar22 != uVar8);
          uVar19 = 0xe800000000000000;
          uVar20 = 0x64656f6c6f736e55;
LAB_1004bc084:
          _swift_bridgeObjectRelease(uVar17);
        }
        else {
          uVar8 = uVar17 & 0xffffffffffffff8;
          if ((long)uVar17 < 0) {
            uVar8 = uVar17;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
          if (uVar8 != 0) goto LAB_1004bbf2c;
LAB_1004bc0dc:
          uVar19 = 0xe800000000000000;
          uVar20 = 0x64656f6c6f736e55;
        }
        _swift_bridgeObjectRelease(uVar17);
        local_88 = (char *)0x100000000000001b;
        local_80 = (undefined *)local_110;
        __sSS6appendyySSF(uVar20,uVar19);
        _swift_bridgeObjectRelease(uVar19);
        puVar14 = local_80;
        _swift_bridgeObjectRetain(local_80);
        __sSS6appendyySSF(0x90a,0xe200000000000000);
        _swift_bridgeObjectRelease(puVar14);
        puVar14 = local_80;
        __sSS6appendyySSF(local_88,local_80);
        _swift_bridgeObjectRelease(puVar14);
      }
      __sSS6appendyySSF(10,0xe100000000000000);
    } while (pcVar18 != pcVar25);
    _swift_bridgeObjectRelease(pcVar15);
    IVar21 = local_78;
    pcVar18 = local_70;
  }
  uVar17 = *(ulong *)(local_128 + 0x10);
  if (*(ulong *)(local_128 + 0x18) >> 1 <= uVar17) {
    puVar14 = (undefined *)(ulong)(1 < *(ulong *)(local_128 + 0x18));
    FUN_10078ddf0(puVar14,uVar17 + 1,1,local_128);
    local_128 = puVar14;
  }
  puVar23 = local_128;
  *(ulong *)(local_128 + 0x10) = uVar17 + 1;
  *(ID *)(local_128 + uVar17 * 0x10 + 0x20) = IVar21;
  *(char **)(local_128 + uVar17 * 0x10 + 0x28) = pcVar18;
  local_88 = local_128;
  puVar14 = &DAT_100af52f8;
  FUN_100021774(&DAT_100af52f8);
  puVar12 = &DAT_100af5300;
  FUN_1004d3b88(&DAT_100af5300,&DAT_100af5308,PTR___sSaMa_100a1dd18,PTR___sSayxGSKsMc_100a1dd28);
  uVar19 = 10;
  uVar20 = 0xe100000000000000;
  __sSKsSS7ElementRtzrlE6joined9separatorS2S_tF(10,0xe100000000000000,puVar14,puVar12);
  _swift_bridgeObjectRelease(puVar23);
  auVar27._8_8_ = uVar20;
  auVar27._0_8_ = uVar19;
  return auVar27;
}

// ==== 1004d57a0 FUN_1004d57a0 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1004d57a0(long param_1)

{
  ID *pIVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined1 *puVar4;
  byte bVar5;
  byte bVar6;
  code *pcVar7;
  undefined *puVar8;
  ID *pIVar9;
  ID self;
  ID IVar10;
  long lVar11;
  long lVar12;
  ID *pIVar13;
  ID IVar14;
  ID IVar15;
  undefined1 auStack_1c0 [8];
  long local_1b8;
  undefined8 local_1b0;
  undefined1 *local_1a8;
  long local_1a0;
  long local_198;
  ID local_178 [20];
  byte local_d8;
  byte local_d7;
  
  puVar8 = &DAT_100af7568;
  FUN_100021774();
  local_1a8 = auStack_1c0 + -(*(long *)(*(long *)(puVar8 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  local_198 = *(long *)(param_1 + 0x10);
  if (local_198 != 0) {
    local_1a0 = param_1 + 0x20;
    local_1b8 = param_1;
    _swift_bridgeObjectRetain(param_1);
    lVar12 = 0;
    local_1b0 = 0;
    do {
      _memcpy(local_178,(void *)(local_1a0 + lVar12 * 0x110),0x10c);
      pIVar9 = local_178;
      FUN_1000c2f28();
      FUN_1004a6154();
      if ((ulong)pIVar9 >> 0x3e == 0) {
        pIVar13 = *(ID **)(((ulong)pIVar9 & 0xfffffffffffff8) + 0x10);
        if (pIVar13 == (ID *)0x0) goto LAB_1004d5ab0;
LAB_1004d588c:
        IVar14 = local_178[0];
        _swift_bridgeObjectRetain(pIVar9);
        lVar11 = 4;
        do {
          IVar15 = lVar11 - 4;
          if (((ulong)pIVar9 & 0xc000000000000001) == 0) {
            self = pIVar9[lVar11];
          }
          else {
            self = IVar15;
            FUN_1000cbedc(IVar15,pIVar9);
          }
          pIVar1 = (ID *)(lVar11 + -3);
          if (SCARRY8(IVar15,1)) {
                    /* WARNING: Does not return */
            pcVar7 = (code *)SoftwareBreakpoint(1,0x1004d5af0);
            (*pcVar7)();
          }
          IVar15 = _objc_msgSend(self,"setlistSongID");
          if ((IVar15 != 0) && (IVar15 = _objc_msgSend(IVar15,"integerValue"), IVar15 == IVar14)) {
            _swift_bridgeObjectRelease_n(pIVar9,2);
            lVar11 = _TtC8Playback4Song::privateWorkingCopyArrangement;
            IVar14 = *(ID *)(self + _TtC8Playback4Song::privateWorkingCopyArrangement);
            if (IVar14 == 0) {
              IVar15 = _objc_msgSend(self,"workingCopyArrangementID");
              if (IVar15 != 0) {
                IVar10 = IVar15;
                FUN_10032ee88();
                uVar3 = local_1b0;
                IVar14 = IVar10;
                FUN_1005e3b94(IVar10,IVar15);
                local_1b0 = uVar3;
                _swift_bridgeObjectRelease(IVar10);
                if (IVar14 != 0) {
                  *(ID *)(self + lVar11) = IVar14;
                  goto LAB_1004d594c;
                }
              }
              FUN_10013916c(local_178);
            }
            else {
LAB_1004d594c:
              bVar6 = local_d7;
              bVar5 = local_d8;
              lVar11 = 0;
              FUN_10020acbc();
              puVar4 = local_1a8;
              (**(code **)(*(long *)(lVar11 + -8) + 0x38))(local_1a8,1,1,lVar11);
              FUN_1002e9208(local_178,self,puVar4,1);
              FUN_100023be4(puVar4,&DAT_100af7568);
              uVar2 = 0;
              if (bVar5 != 5) {
                uVar2 = (uint)bVar5;
              }
              _objc_msgSend(IVar14,"setStoredTransition:",(ulong)uVar2);
              FUN_10013916c(local_178);
              _objc_msgSend(IVar14,"setTransitionContinuePad:",(ulong)(bVar6 & 1));
            }
            goto LAB_1004d583c;
          }
          lVar11 = lVar11 + 1;
        } while (pIVar1 != pIVar13);
        _swift_bridgeObjectRelease_n(pIVar9,2);
        FUN_10013916c(local_178);
      }
      else {
        pIVar13 = (ID *)((ulong)pIVar9 & 0xffffffffffffff8);
        if ((long)pIVar9 < 0) {
          pIVar13 = pIVar9;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        if (pIVar13 != (ID *)0x0) goto LAB_1004d588c;
LAB_1004d5ab0:
        _swift_bridgeObjectRelease(pIVar9);
        FUN_10013916c(local_178);
      }
LAB_1004d583c:
      lVar12 = lVar12 + 1;
    } while (lVar12 != local_198);
    _swift_bridgeObjectRelease(local_1b8);
  }
  return;
}

// ==== 1004da640 FUN_1004da640 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Type propagation algorithm not settling */

void FUN_1004da640(double *param_1,double param_2,ID param_3,undefined8 *******param_4,
                  undefined8 *******param_5,ID param_6,ulong param_7,undefined8 *******param_8,
                  double param_9,char *param_10,undefined1 param_11)

{
  ulong uVar1;
  ID *pIVar2;
  undefined8 *****pppppuVar3;
  undefined8 ******ppppppuVar4;
  undefined1 *puVar5;
  double *pdVar6;
  code *pcVar7;
  byte bVar8;
  undefined1 uVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  undefined8 *******pppppppuVar14;
  long lVar15;
  ID IVar16;
  ID IVar17;
  undefined *puVar18;
  undefined *puVar19;
  undefined8 ******self;
  undefined8 *******pppppppuVar20;
  ID IVar21;
  undefined8 *******pppppppuVar22;
  ulong uVar23;
  undefined8 uVar24;
  char *pcVar25;
  char *pcVar26;
  long unaff_x21;
  undefined8 *******pppppppuVar27;
  undefined8 ******ppppppuVar28;
  long lVar29;
  undefined8 *******pppppppuVar30;
  undefined *puVar31;
  undefined8 ******ppppppuVar32;
  undefined8 *******pppppppuVar33;
  ulong uVar34;
  undefined8 ******ppppppuVar35;
  undefined8 *******pppppppuVar36;
  double dVar37;
  undefined8 ******ppppppuVar38;
  double dVar39;
  undefined1 auStack_280 [8];
  ulong local_278;
  ID local_270;
  undefined8 *******local_268;
  undefined8 *******local_260;
  undefined8 *******local_258;
  undefined8 *******local_250;
  undefined8 *******local_248;
  undefined1 *local_240;
  undefined8 ******local_238;
  undefined8 *******pppppppuStack_230;
  char *local_228;
  long local_220;
  char *local_218;
  undefined8 *******local_210;
  undefined8 ******local_208;
  uint local_1fc;
  long local_1f8;
  ID local_1f0;
  undefined8 *******local_1e8;
  undefined8 *******local_1e0;
  undefined8 *******local_1d8;
  undefined8 *******local_1d0;
  double *local_1c8;
  undefined8 *******local_1c0;
  undefined8 local_1b0;
  undefined8 *******local_1a8 [4];
  undefined *local_188;
  undefined8 *****local_180;
  undefined8 *****pppppuStack_178;
  undefined8 *****pppppuStack_170;
  undefined8 *****pppppuStack_168;
  undefined8 *****local_160;
  undefined8 *****pppppuStack_158;
  undefined8 ******local_150;
  undefined8 *****pppppuStack_148;
  undefined8 *****pppppuStack_140;
  undefined8 *****pppppuStack_138;
  undefined8 *****local_130;
  undefined8 *****pppppuStack_128;
  undefined8 *****local_120;
  undefined8 ******local_118;
  undefined8 ******ppppppuStack_110;
  undefined8 ******ppppppuStack_108;
  undefined8 ******ppppppuStack_100;
  undefined8 ******local_f8;
  undefined8 ******ppppppuStack_f0;
  undefined8 ******ppppppuStack_e8;
  undefined8 ******ppppppuStack_e0;
  undefined8 ******local_d8;
  undefined8 ******ppppppuStack_d0;
  undefined1 local_c8;
  undefined8 ******local_c0;
  undefined8 ******ppppppuStack_b8;
  undefined8 ******local_b0;
  undefined8 ******ppppppuStack_a8;
  undefined8 ******ppppppuStack_a0;
  undefined8 ******ppppppuStack_98;
  undefined8 ******local_90;
  undefined8 ******ppppppuStack_88;
  undefined2 local_80;
  
  local_1fc = (uint)param_5;
  pppppppuVar14 = (undefined8 *******)0x0;
  local_1c8 = param_1;
  __s10Foundation4UUIDVMa();
  lVar15 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  local_238 = pppppppuVar14[-1];
  local_240 = auStack_280 + -((long)local_238[8] + 0xfU & 0xfffffffffffffff0);
  pppppppuStack_230 = pppppppuVar14;
  local_1f0 = param_3;
  local_1e8 = param_4;
  if ((param_4 == (undefined8 *******)0x0) &&
     (local_1e8 = *(undefined8 ********)
                   (param_3 + _TtC8Playback4Song::privateWorkingCopyArrangement),
     local_1c0 = param_8, local_1e8 == (undefined8 *******)0x0)) {
    pppppppuVar14 = (undefined8 *******)_objc_msgSend(param_3,"workingCopyArrangementID");
    if (pppppppuVar14 == (undefined8 *******)0x0) {
LAB_1004daf08:
      _swift_bridgeObjectRelease();
      FUN_1003b2424();
      _swift_allocError(&DAT_100a514a0,param_10,0,0);
      param_10[0] = '\0';
      param_10[1] = '\0';
      param_10[2] = '\0';
      param_10[3] = '\0';
      param_10[4] = '\0';
      param_10[5] = '\0';
      param_10[6] = '\0';
      param_10[7] = '\0';
      param_10[8] = '\0';
      param_10[9] = '\0';
      param_10[10] = '\0';
      param_10[0xb] = '\0';
      param_10[0xc] = '\0';
      param_10[0xd] = '\0';
      param_10[0xe] = '\0';
      param_10[0xf] = '\0';
      param_10[0x10] = '\x02';
      _swift_willThrow();
      return;
    }
    pppppppuVar27 = pppppppuVar14;
    FUN_10032ee88();
    pppppppuVar36 = pppppppuVar27;
    FUN_1005e3b94(pppppppuVar27,pppppppuVar14);
    local_1d0 = pppppppuVar36;
    _swift_bridgeObjectRelease(pppppppuVar27);
    if (local_1d0 == (undefined8 *******)0x0) goto LAB_1004daf08;
    *(undefined8 ********)(local_1f0 + lVar15) = local_1d0;
    local_1e8 = local_1d0;
    param_8 = local_1c0;
  }
  local_210 = param_4;
  if ((param_7 & 1) != 0) {
    param_6 = _objc_msgSend((ID)local_1e8,"id");
  }
  lVar15 = 0;
  FUN_1004da4ec();
  *(ID *)((long)local_1c8 + (long)*(int *)(lVar15 + 0x58)) = param_6;
  local_1f8 = lVar15;
  if (param_10 == (char *)0x0) {
    param_10 = "title";
    param_9 = (double)_objc_msgSend((ID)local_1e8,"title");
    if (param_9 == 0.0) {
      if (DAT_100adef30 != -1) {
        _swift_once(&DAT_100adef30,FUN_1002e2be4);
      }
      param_10 = DAT_100b75e80;
      param_9 = DAT_100b75e78;
      _swift_bridgeObjectRetain(DAT_100b75e80);
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
  }
  pdVar6 = local_1c8;
  lVar15 = local_1f8;
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x88));
  local_1c8[0x12] = param_9;
  local_1c8[0x13] = (double)param_10;
  lVar29 = (long)*(int *)(local_1f8 + 0x54);
  local_218 = param_10;
  __s10Foundation4DateVACycfC((long)local_1c8 + lVar29);
  *(byte *)((long)pdVar6 + (long)*(int *)(lVar15 + 0x7c)) = (byte)local_1fc & 1;
  *(undefined1 *)((long)pdVar6 + (long)*(int *)(lVar15 + 0x80)) = param_11;
  *pIVar2 = (ID)param_8;
  *(undefined1 *)(pIVar2 + 1) = 0;
  IVar16 = _objc_msgSend((ID)local_1e8,"song");
  if (IVar16 == 0) {
    uVar10 = 1;
  }
  else {
    IVar16 = _objc_msgSend(IVar16,"metadataVersion");
    uVar10 = (undefined4)IVar16;
  }
  pppppppuVar14 = local_1e8;
  *(undefined4 *)(local_1c8 + 4) = uVar10;
  *(undefined1 *)((long)local_1c8 + 0x24) = 0;
  _objc_msgSend((ID)local_1e8,"storedStartTime");
  dVar37 = param_2;
  IVar16 = _objc_msgSend((ID)pppppppuVar14,"song");
  dVar39 = 1.0;
  if (IVar16 != 0) {
    FUN_1003220ec();
    dVar39 = dVar37;
  }
  pppppppuVar14 = local_1e8;
  param_2 = param_2 * dVar39;
  *local_1c8 = param_2;
  _objc_msgSend((ID)local_1e8,"storedEndTime");
  dVar37 = param_2;
  IVar16 = _objc_msgSend((ID)pppppppuVar14,"song");
  dVar39 = 1.0;
  if (IVar16 != 0) {
    FUN_1003220ec();
    dVar39 = dVar37;
  }
  pdVar6 = local_1c8;
  pppppppuVar14 = local_1e8;
  ppppppuVar38 = (undefined8 ******)(param_2 * dVar39);
  local_1c8[1] = (double)ppppppuVar38;
  IVar16 = _objc_msgSend((ID)local_1e8,"endFade");
  *(char *)((long)pdVar6 + 0x11) = (char)IVar16;
  IVar16 = _objc_msgSend((ID)pppppppuVar14,"masterVolumeLevel");
  uVar9 = (undefined1)IVar16;
  pdVar6[3] = (double)ppppppuVar38;
  FUN_1002da058();
  *(undefined1 *)(pdVar6 + 2) = uVar9;
  IVar17 = _objc_msgSend((ID)pppppppuVar14,"transitionContinuePad");
  IVar16 = local_1f0;
  *(char *)((long)pdVar6 + (long)*(int *)(local_1f8 + 0x68)) = (char)IVar17;
  IVar17 = _objc_msgSend(local_1f0,"keyID");
  IVar17 = (ID)(int)IVar17;
  if (((local_1fc & 1) != 0) && (IVar16 = _objc_msgSend(IVar16,"storedOfficialKeyID"), IVar16 != 0))
  {
    IVar17 = _objc_msgSend(IVar16,"integerValue");
  }
  pdVar6 = local_1c8;
  lVar15 = local_1f8;
  *(ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 100)) = IVar17;
  IVar16 = _objc_msgSend(local_1f0,"bpm");
  *(undefined8 *******)((long)pdVar6 + (long)*(int *)(lVar15 + 0x5c)) = ppppppuVar38;
  FUN_1003221bc();
  if (IVar16 == 0) {
    uVar9 = 3;
  }
  else {
    if (*(long *)(IVar16 + 0x10) == 0) {
      uVar9 = 3;
    }
    else {
      uVar9 = *(undefined1 *)(IVar16 + 0x20);
    }
    _swift_bridgeObjectRelease();
  }
  IVar16 = local_1f0;
  IVar17 = _objc_msgSend(local_1f0,"contentTypeID");
  uVar11 = (uint)IVar17;
  FUN_100419df0();
  if ((uVar11 & 0xff) == 0xd) {
    IVar16 = _objc_msgSend(IVar16,"storedTimeSignatureIDOriginal");
    if (IVar16 == 0) {
      uVar9 = 0x14;
      IVar16 = local_1f0;
    }
    else {
      IVar16 = _objc_msgSend(IVar16,"integerValue");
      uVar9 = (undefined1)IVar16;
      FUN_10055ee18();
      IVar16 = local_1f0;
    }
  }
  *(undefined1 *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x60)) = uVar9;
  pcVar25 = "customName";
  IVar16 = _objc_msgSend(IVar16,"customName");
  if (IVar16 == 0) {
    IVar16 = 0;
    pcVar25 = (char *)0x0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x6c));
  *pIVar2 = IVar16;
  pIVar2[1] = (ID)pcVar25;
  IVar16 = _objc_msgSend(local_1f0,"clickSongMeasureCount");
  if (IVar16 == 0) {
    IVar17 = 0;
  }
  else {
    IVar17 = _objc_msgSend(IVar16,"integerValue");
  }
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x70));
  *pIVar2 = IVar17;
  *(bool *)(pIVar2 + 1) = IVar16 == 0;
  IVar16 = _objc_msgSend(local_1f0,"midiProPresenterPlaylist");
  if (IVar16 == 0) {
    IVar17 = 0;
  }
  else {
    IVar17 = _objc_msgSend(IVar16,"integerValue");
  }
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x74));
  *pIVar2 = IVar17;
  *(bool *)(pIVar2 + 1) = IVar16 == 0;
  IVar16 = _objc_msgSend(local_1f0,"midiProPresenterPlaylistItem");
  if (IVar16 == 0) {
    IVar17 = 0;
  }
  else {
    IVar17 = _objc_msgSend(IVar16,"integerValue");
  }
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x78));
  *pIVar2 = IVar17;
  *(bool *)(pIVar2 + 1) = IVar16 == 0;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  IVar16 = _objc_msgSend((ID)local_1e8,"storedSections");
  puVar19 = PTR___sypN_100a1e038;
  if (IVar16 == 0) {
LAB_1004daccc:
    puVar19 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  else {
    puVar18 = (undefined *)_objc_msgSend(IVar16,"array");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (puVar18,puVar19 + 8);
    puVar19 = puVar18;
    FUN_1002d7d28();
    _swift_bridgeObjectRelease(puVar18);
    if (puVar19 == (undefined *)0x0) goto LAB_1004daccc;
  }
  if ((ulong)puVar19 >> 0x3e == 0) {
    puVar18 = *(undefined **)(((ulong)puVar19 & 0xfffffffffffff8) + 0x10);
  }
  else {
    puVar18 = (undefined *)((ulong)puVar19 & 0xffffffffffffff8);
    if ((long)puVar19 < 0) {
      puVar18 = puVar19;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  ppppppuVar32 = (undefined8 ******)PTR___swiftEmptyArrayStorage_100a1e050;
  local_228 = pcVar25;
  local_220 = lVar29;
  if (puVar18 != (undefined *)0x0) {
    if ((long)puVar18 < 1) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1004db150);
      (*pcVar7)();
    }
    puVar31 = (undefined *)0x0;
    do {
      if (((ulong)puVar19 & 0xc000000000000001) != 0) {
        FUN_1000cbf0c(puVar31,puVar19);
      }
      FUN_10055a168(&local_180);
      ppppppuVar38 = ppppppuVar32;
      _swift_isUniquelyReferenced_nonNull_native();
      if (((ulong)ppppppuVar38 & 1) == 0) {
        ppppppuVar38 = (undefined8 ******)0x0;
        param_5 = (undefined8 *******)0x1;
        FUN_10078f970(0,(long)ppppppuVar32[2] + 1,1,ppppppuVar32);
        ppppppuVar32 = ppppppuVar38;
      }
      pppppuVar3 = ppppppuVar32[2];
      if ((undefined8 *****)((ulong)ppppppuVar32[3] >> 1) <= pppppuVar3) {
        ppppppuVar32 = (undefined8 ******)(ulong)((undefined8 *****)0x1 < ppppppuVar32[3]);
        param_5 = (undefined8 *******)0x1;
        FUN_10078f970(ppppppuVar32,(undefined8 *****)((long)pppppuVar3 + 1U));
      }
      puVar31 = puVar31 + 1;
      ppppppuVar32[2] = (undefined8 *****)((long)pppppuVar3 + 1U);
      ppppppuVar32[(long)pppppuVar3 * 0xd + 7] = pppppuStack_168;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 6] = pppppuStack_170;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 9] = pppppuStack_158;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 8] = local_160;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 5] = pppppuStack_178;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 4] = local_180;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0x10] = local_120;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0xd] = pppppuStack_138;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0xc] = pppppuStack_140;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0xf] = pppppuStack_128;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0xe] = local_130;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 0xb] = pppppuStack_148;
      ppppppuVar32[(long)pppppuVar3 * 0xd + 10] = local_150;
      ppppppuVar38 = local_150;
    } while (puVar18 != puVar31);
  }
  _swift_bridgeObjectRelease(puVar19);
  local_1c8[5] = (double)ppppppuVar32;
  ppppppuVar28 = ppppppuVar32;
  _swift_bridgeObjectRetain();
  FUN_1002dc2dc();
  local_208 = ppppppuVar32;
  if ((ulong)ppppppuVar28 >> 0x3e == 0) {
    ppppppuVar32 = *(undefined8 *******)(((ulong)ppppppuVar28 & 0xfffffffffffff8) + 0x10);
    if (ppppppuVar32 == (undefined8 ******)0x0) goto LAB_1004daf88;
LAB_1004dae2c:
    pppppppuVar14 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    if ((long)ppppppuVar32 < 1) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1004db154);
      (*pcVar7)();
    }
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    ppppppuVar35 = (undefined8 ******)0x0;
    do {
      if (((ulong)ppppppuVar28 & 0xc000000000000001) == 0) {
        self = (undefined8 ******)ppppppuVar28[(long)((long)ppppppuVar35 + 4)];
      }
      else {
        self = ppppppuVar35;
        FUN_1000cc338(ppppppuVar35,ppppppuVar28);
      }
      IVar16 = _objc_msgSend((ID)self,"included");
      if ((int)IVar16 != 0) {
        pppppppuVar27 = pppppppuVar14;
        _swift_isUniquelyReferenced_nonNull_native();
        local_1a8[0] = pppppppuVar14;
        if (((ulong)pppppppuVar27 & 1) == 0) {
          param_5 = (undefined8 *******)0x1;
          FUN_1001cc4d4(0,(long)pppppppuVar14[2] + 1);
        }
        ppppppuVar4 = local_1a8[0][2];
        if ((undefined8 ******)((ulong)local_1a8[0][3] >> 1) <= ppppppuVar4) {
          param_5 = (undefined8 *******)0x1;
          FUN_1001cc4d4((undefined8 ******)0x1 < local_1a8[0][3],
                        (undefined8 ******)((long)ppppppuVar4 + 1U));
        }
        local_1a8[0][2] = (undefined8 ******)((long)ppppppuVar4 + 1U);
        local_1a8[0][(long)ppppppuVar4 + 4] = self;
        pppppppuVar14 = local_1a8[0];
      }
      ppppppuVar35 = (undefined8 ******)((long)ppppppuVar35 + 1);
    } while (ppppppuVar32 != ppppppuVar35);
  }
  else {
    ppppppuVar32 = (undefined8 ******)((ulong)ppppppuVar28 & 0xffffffffffffff8);
    if ((long)ppppppuVar28 < 0) {
      ppppppuVar32 = ppppppuVar28;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (ppppppuVar32 != (undefined8 ******)0x0) goto LAB_1004dae2c;
LAB_1004daf88:
    pppppppuVar14 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  }
  _swift_bridgeObjectRelease(ppppppuVar28);
  if (((long)pppppppuVar14 < 0) || (((ulong)pppppppuVar14 >> 0x3e & 1) != 0)) {
    pppppppuVar27 = pppppppuVar14;
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  else {
    pppppppuVar27 = (undefined8 *******)pppppppuVar14[2];
  }
  puVar19 = PTR___sypN_100a1e038;
  _swift_release();
  ppppppuVar32 = local_208;
  if (pppppppuVar27 == (undefined8 *******)0x0) {
    FUN_1002dc2dc();
    if ((ulong)pppppppuVar14 >> 0x3e == 0) {
      pppppppuVar27 = *(undefined8 ********)(((ulong)pppppppuVar14 & 0xfffffffffffff8) + 0x10);
      if (pppppppuVar27 == (undefined8 *******)0x0) goto LAB_1004db16c;
LAB_1004dafec:
      pppppppuVar36 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
      if ((long)pppppppuVar27 < 1) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dc070);
        (*pcVar7)();
      }
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      pppppppuVar20 = (undefined8 *******)0x0;
      do {
        if (((ulong)pppppppuVar14 & 0xc000000000000001) == 0) {
          pppppppuVar30 = (undefined8 *******)pppppppuVar14[(long)((long)pppppppuVar20 + 4)];
        }
        else {
          pppppppuVar30 = pppppppuVar20;
          FUN_1000cc338(pppppppuVar20,pppppppuVar14);
        }
        IVar16 = _objc_msgSend((ID)pppppppuVar30,"isClickOrGuide");
        if (((IVar16 != 0) && (IVar16 = _objc_msgSend(IVar16,"boolValue"), (IVar16 & 1) != 0)) &&
           (IVar16 = _objc_msgSend((ID)pppppppuVar30,"partID"), IVar16 != 0)) {
          IVar16 = _objc_msgSend(IVar16,"integerValue");
          uVar11 = (uint)IVar16;
          FUN_10056fe0c();
          if ((uVar11 & 0xff) != 1 && (uVar11 & 0xff) != 8) {
            pppppppuVar33 = pppppppuVar36;
            _swift_isUniquelyReferenced_nonNull_native();
            local_1a8[0] = pppppppuVar36;
            if (((ulong)pppppppuVar33 & 1) == 0) {
              param_5 = (undefined8 *******)0x1;
              FUN_1001cc4d4(0,(long)pppppppuVar36[2] + 1);
            }
            ppppppuVar32 = local_1a8[0][2];
            if ((undefined8 ******)((ulong)local_1a8[0][3] >> 1) <= ppppppuVar32) {
              param_5 = (undefined8 *******)0x1;
              FUN_1001cc4d4((undefined8 ******)0x1 < local_1a8[0][3],
                            (undefined8 ******)((long)ppppppuVar32 + 1U));
            }
            local_1a8[0][2] = (undefined8 ******)((long)ppppppuVar32 + 1U);
            local_1a8[0][(long)ppppppuVar32 + 4] = pppppppuVar30;
            pppppppuVar36 = local_1a8[0];
          }
        }
        pppppppuVar20 = (undefined8 *******)((long)pppppppuVar20 + 1);
      } while (pppppppuVar27 != pppppppuVar20);
    }
    else {
      pppppppuVar27 = (undefined8 *******)((ulong)pppppppuVar14 & 0xffffffffffffff8);
      if ((long)pppppppuVar14 < 0) {
        pppppppuVar27 = pppppppuVar14;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if (pppppppuVar27 != (undefined8 *******)0x0) goto LAB_1004dafec;
LAB_1004db16c:
      pppppppuVar36 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
      _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    }
    _swift_bridgeObjectRelease(pppppppuVar14);
    if (((long)pppppppuVar36 < 0) || (((ulong)pppppppuVar36 >> 0x3e & 1) != 0)) {
      pppppppuVar14 = pppppppuVar36;
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    else {
      pppppppuVar14 = (undefined8 *******)pppppppuVar36[2];
    }
    if (pppppppuVar14 != (undefined8 *******)0x0) {
      if ((long)pppppppuVar14 < 1) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dc074);
        (*pcVar7)();
      }
      _swift_retain(pppppppuVar36);
      pppppppuVar27 = (undefined8 *******)0x0;
      do {
        if (((ulong)pppppppuVar36 & 0xc000000000000001) == 0) {
          pppppppuVar20 = (undefined8 *******)pppppppuVar36[(long)((long)pppppppuVar27 + 4)];
        }
        else {
          pppppppuVar20 = pppppppuVar27;
          FUN_1000cc338(pppppppuVar27,pppppppuVar36);
        }
        pppppppuVar27 = (undefined8 *******)((long)pppppppuVar27 + 1);
        param_5 = (undefined8 *******)0x1;
        _objc_msgSend((ID)pppppppuVar20,"setIncluded:");
      } while (pppppppuVar14 != pppppppuVar27);
      _swift_release(pppppppuVar36);
    }
    ppppppuVar32 = local_208;
    puVar19 = PTR___sypN_100a1e038;
    _swift_release();
    pppppppuVar14 = pppppppuVar36;
  }
  FUN_1002dc2dc();
  if ((ulong)pppppppuVar14 >> 0x3e == 0) {
    pppppppuVar27 = *(undefined8 ********)(((ulong)pppppppuVar14 & 0xfffffffffffff8) + 0x10);
    if (pppppppuVar27 == (undefined8 *******)0x0) goto LAB_1004db3c4;
LAB_1004db240:
    local_1a8[0] = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    param_5 = (undefined8 *******)0x0;
    FUN_1001ccef4(0,(ulong)pppppppuVar27 & ((long)pppppppuVar27 >> 0x3f ^ 0xffffffffffffffffU));
    if ((long)pppppppuVar27 < 0) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbbc4);
      (*pcVar7)();
    }
    lVar15 = 0;
    local_1c0 = (undefined8 *******)((ulong)pppppppuVar14 & 0xc000000000000001);
    do {
      pppppppuVar20 = local_1a8[0];
      pppppppuVar36 = (undefined8 *******)(lVar15 + 1);
      if (SCARRY8(lVar15,1)) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x1004db3ac);
        (*pcVar7)();
      }
      if (local_1c0 != (undefined8 *******)0x0) {
        FUN_1000cc338(lVar15,pppppppuVar14);
      }
      FUN_10055a4e8(&local_118);
      if (unaff_x21 != 0) {
        _swift_bridgeObjectRelease(local_218);
        _swift_bridgeObjectRelease_n(local_208,2);
        _swift_bridgeObjectRelease(pppppppuVar14);
        _swift_release(pppppppuVar20);
        goto LAB_1004dbf1c;
      }
      ppppppuVar38 = pppppppuVar20[2];
      local_1a8[0] = pppppppuVar20;
      if ((undefined8 ******)((ulong)pppppppuVar20[3] >> 1) <= ppppppuVar38) {
        param_5 = (undefined8 *******)0x1;
        FUN_1001ccef4((undefined8 ******)0x1 < pppppppuVar20[3],
                      (undefined8 ******)((long)ppppppuVar38 + 1U));
      }
      pppppppuVar20 = local_1a8[0];
      local_1a8[0][2] = (undefined8 ******)((long)ppppppuVar38 + 1U);
      local_1a8[0][(long)ppppppuVar38 * 0xb + 5] = ppppppuStack_110;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 4] = local_118;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 7] = ppppppuStack_100;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 6] = ppppppuStack_108;
      *(undefined1 *)(local_1a8[0] + (long)ppppppuVar38 * 0xb + 0xe) = local_c8;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 0xb] = ppppppuStack_e0;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 10] = ppppppuStack_e8;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 0xd] = ppppppuStack_d0;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 0xc] = local_d8;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 9] = ppppppuStack_f0;
      local_1a8[0][(long)ppppppuVar38 * 0xb + 8] = local_f8;
      lVar15 = lVar15 + 1;
    } while (pppppppuVar36 != pppppppuVar27);
    _swift_bridgeObjectRelease(pppppppuVar14);
    ppppppuVar32 = local_208;
    puVar19 = PTR___sypN_100a1e038;
    ppppppuVar38 = local_f8;
  }
  else {
    pppppppuVar27 = (undefined8 *******)((ulong)pppppppuVar14 & 0xffffffffffffff8);
    if ((long)pppppppuVar14 < 0) {
      pppppppuVar27 = pppppppuVar14;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (pppppppuVar27 != (undefined8 *******)0x0) goto LAB_1004db240;
LAB_1004db3c4:
    pppppppuVar20 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    _swift_bridgeObjectRelease(pppppppuVar14);
  }
  local_1c8[6] = (double)pppppppuVar20;
  local_248 = pppppppuVar20;
  IVar16 = _objc_msgSend(local_1f0,"storedSongGenres");
  if (IVar16 == 0) {
LAB_1004db494:
    pppppppuVar14 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
  }
  else {
    pppppppuVar27 = (undefined8 *******)_objc_msgSend(IVar16,"allObjects");
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
              (pppppppuVar27,puVar19 + 8);
    pppppppuVar14 = pppppppuVar27;
    FUN_1002d7d3c();
    _swift_bridgeObjectRelease(pppppppuVar27);
    if (pppppppuVar14 == (undefined8 *******)0x0) goto LAB_1004db494;
    pppppppuVar27 = (undefined8 *******)((ulong)pppppppuVar14 & 0xffffffffffffff8);
    if ((ulong)pppppppuVar14 >> 0x3e == 0) {
      _swift_bridgeObjectRetain(pppppppuVar14);
    }
    else {
      pppppppuVar36 = pppppppuVar14;
      if (-1 < (long)pppppppuVar14) {
        pppppppuVar36 = pppppppuVar27;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      pppppppuVar27 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
      if (pppppppuVar36 == (undefined8 *******)0x0) {
        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
      }
      else {
        pppppppuVar27 = pppppppuVar36;
        FUN_10078d80c();
        _swift_bridgeObjectRetain_n(pppppppuVar14,2);
        pppppppuVar20 = pppppppuVar14;
        FUN_1005dadc4(pppppppuVar27 + 4,pppppppuVar36);
        param_5 = pppppppuVar20;
        _swift_bridgeObjectRelease();
        if (pppppppuVar20 != pppppppuVar36) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dc0c0);
          (*pcVar7)();
        }
        _swift_bridgeObjectRelease(pppppppuVar14);
      }
    }
    local_1a8[0] = pppppppuVar27;
    FUN_1003232e4(local_1a8);
    if (unaff_x21 != 0) {
      _swift_release(local_1a8[0]);
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dc0cc);
      (*pcVar7)();
    }
    _swift_bridgeObjectRelease(pppppppuVar14);
    pppppppuVar14 = local_1a8[0];
  }
  if ((ulong)pppppppuVar14 >> 0x3e == 0) {
    pppppppuVar27 = *(undefined8 ********)(((ulong)pppppppuVar14 & 0xfffffffffffff8) + 0x10);
    if (pppppppuVar27 == (undefined8 *******)0x0) goto LAB_1004dbb94;
LAB_1004db4b8:
    local_1a8[0] = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain();
    param_5 = (undefined8 *******)0x0;
    FUN_1001ccec8(0,(ulong)pppppppuVar27 & ((long)pppppppuVar27 >> 0x3f ^ 0xffffffffffffffffU));
    if ((long)pppppppuVar27 < 0) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbbc8);
      (*pcVar7)();
    }
    pppppppuVar36 = (undefined8 *******)0x0;
    local_1e0 = (undefined8 *******)((ulong)pppppppuVar14 & 0xc000000000000001);
    local_1d8 = pppppppuVar27;
    local_1d0 = pppppppuVar14;
    do {
      pppppppuVar14 = local_1a8[0];
      if (local_1e0 == (undefined8 *******)0x0) {
        pppppppuVar27 = (undefined8 *******)local_1d0[(long)((long)pppppppuVar36 + 4)];
        ppppppuVar32 = ppppppuVar38;
      }
      else {
        pppppppuVar27 = pppppppuVar36;
        FUN_1000cbf38();
        ppppppuVar32 = ppppppuVar38;
      }
      IVar16 = _objc_msgSend((ID)pppppppuVar27,"genreID");
      IVar17 = _objc_msgSend((ID)pppppppuVar27,"songID");
      pcVar25 = "storedUUID";
      pppppppuVar20 = (undefined8 *******)_objc_msgSend((ID)pppppppuVar27,"storedUUID");
      if (pppppppuVar20 == (undefined8 *******)0x0) {
        local_1c0 = (undefined8 *******)0x0;
        pcVar25 = (char *)0x0;
      }
      else {
        __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
        local_1c0 = pppppppuVar20;
      }
      _objc_msgSend((ID)pppppppuVar27,"volume");
      ppppppuVar38 = ppppppuVar32;
      IVar21 = _objc_msgSend((ID)pppppppuVar27,"muted");
      ppppppuVar28 = pppppppuVar14[2];
      local_1a8[0] = pppppppuVar14;
      if ((undefined8 ******)((ulong)pppppppuVar14[3] >> 1) <= ppppppuVar28) {
        param_5 = (undefined8 *******)0x1;
        FUN_1001ccec8((undefined8 ******)0x1 < pppppppuVar14[3],
                      (undefined8 ******)((long)ppppppuVar28 + 1));
      }
      pppppppuVar27 = local_1a8[0];
      pppppppuVar14 = local_1d0;
      pppppppuVar36 = (undefined8 *******)((long)pppppppuVar36 + 1);
      local_1a8[0][2] = (undefined8 ******)((long)ppppppuVar28 + 1);
      local_1a8[0][(long)ppppppuVar28 * 6 + 4] = (undefined8 ******)(long)(int)IVar16;
      local_1a8[0][(long)ppppppuVar28 * 6 + 5] = (undefined8 ******)(long)(int)IVar17;
      local_1a8[0][(long)ppppppuVar28 * 6 + 6] = local_1c0;
      local_1a8[0][(long)ppppppuVar28 * 6 + 7] = (undefined8 ******)pcVar25;
      local_1a8[0][(long)ppppppuVar28 * 6 + 8] = ppppppuVar32;
      *(char *)(local_1a8[0] + (long)ppppppuVar28 * 6 + 9) = (char)IVar21;
    } while (local_1d8 != pppppppuVar36);
    _swift_bridgeObjectRelease(local_208);
    _swift_bridgeObjectRelease(pppppppuVar14);
    ppppppuVar32 = pppppppuVar27[2];
    puVar19 = PTR___sypN_100a1e038;
    local_250 = pppppppuVar27;
  }
  else {
    pppppppuVar27 = (undefined8 *******)((ulong)pppppppuVar14 & 0xffffffffffffff8);
    if ((long)pppppppuVar14 < 0) {
      pppppppuVar27 = pppppppuVar14;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (pppppppuVar27 != (undefined8 *******)0x0) goto LAB_1004db4b8;
LAB_1004dbb94:
    puVar18 = PTR___swiftEmptyArrayStorage_100a1e050;
    _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
    _swift_bridgeObjectRelease(ppppppuVar32);
    _swift_bridgeObjectRelease(pppppppuVar14);
    ppppppuVar32 = *(undefined8 *******)(puVar18 + 0x10);
    local_250 = (undefined8 *******)puVar18;
  }
  if (ppppppuVar32 == (undefined8 ******)0x0) {
    _swift_bridgeObjectRelease(local_250);
    local_250 = (undefined8 *******)0x0;
  }
  local_1c8[7] = (double)local_250;
  pppppppuVar27 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
  _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
  pcVar25 = "storedBuses";
  IVar16 = _objc_msgSend((ID)local_1e8,"storedBuses");
  uVar10 = SUB84(param_5,0);
  pppppppuVar14 = (undefined8 *******)0x0;
  if (IVar16 != 0) {
    pppppppuVar14 = (undefined8 *******)_objc_msgSend(IVar16,"array");
    pcVar25 = puVar19 + 8;
    __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ();
    pppppppuVar36 = pppppppuVar14;
    FUN_1002d7d64();
    _swift_bridgeObjectRelease();
    uVar10 = SUB84(param_5,0);
    if (pppppppuVar36 != (undefined8 *******)0x0) {
      pppppppuVar20 = (undefined8 *******)((ulong)pppppppuVar36 & 0xffffffffffffff8);
      if ((ulong)pppppppuVar36 >> 0x3e == 0) {
        pppppppuVar30 = (undefined8 *******)pppppppuVar20[2];
      }
      else {
        pppppppuVar30 = pppppppuVar36;
        if (-1 < (long)pppppppuVar36) {
          pppppppuVar30 = pppppppuVar20;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
        uVar10 = SUB84(param_5,0);
      }
      pppppppuVar14 = pppppppuVar36;
      if (pppppppuVar30 != (undefined8 *******)0x0) {
        pppppppuVar33 = (undefined8 *******)0x0;
        local_1d0 = (undefined8 *******)((ulong)pppppppuVar36 & 0xc000000000000001);
        local_1d8 = pppppppuVar36 + 4;
        local_268 = pppppppuVar20;
        local_260 = pppppppuVar36;
        local_258 = pppppppuVar30;
        do {
          if (local_1d0 == (undefined8 *******)0x0) {
            if (pppppppuVar20[2] <= pppppppuVar33) {
                    /* WARNING: Does not return */
              pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbb78);
              (*pcVar7)();
            }
            pppppppuVar22 = (undefined8 *******)local_1d8[(long)pppppppuVar33];
            pppppppuVar36 = local_1c0;
          }
          else {
            pppppppuVar22 = pppppppuVar33;
            FUN_1000cce70(pppppppuVar33,pppppppuVar14);
            pppppppuVar36 = local_1c0;
          }
          local_1c0 = pppppppuVar22;
          if (SCARRY8((long)pppppppuVar33,1)) {
                    /* WARNING: Does not return */
            pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbb70);
            local_1c0 = pppppppuVar36;
            (*pcVar7)();
          }
          pppppppuVar33 = (undefined8 *******)((long)pppppppuVar33 + 1);
          pcVar25 = "id";
          IVar16 = _objc_msgSend((ID)local_1c0,"id");
          uVar23 = (ulong)(int)IVar16;
          FUN_10055ee18();
          uVar11 = (uint)uVar23 & 0xff;
          if ((0x14 < uVar11) ||
             (((1 << (ulong)((uint)uVar23 & 0x1f) & 0x21801U) == 0 && (uVar11 != 0x14)))) {
            pcVar25 = "storedBuses";
            IVar16 = _objc_msgSend((ID)local_1e8,"storedBuses");
            if (IVar16 != 0) {
              local_1e0 = pppppppuVar27;
              IVar16 = _objc_msgSend(IVar16,"array");
              __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                        (IVar16,puVar19 + 8);
              pcVar25 = *(char **)(IVar16 + 0x10);
              local_188 = PTR___swiftEmptyArrayStorage_100a1e050;
              _swift_retain();
              param_5 = (undefined8 *******)0x0;
              FUN_1001cc5c4(0);
              puVar18 = local_188;
              lVar15 = *(long *)(IVar16 + 0x10);
              IVar17 = IVar16;
              if (lVar15 == 0) {
                _swift_bridgeObjectRelease(IVar16);
                if (-1 < (long)puVar18) goto LAB_1004db914;
LAB_1004dbafc:
                puVar31 = puVar18;
                __ss18_CocoaArrayWrapperV8endIndexSivg();
              }
              else {
                do {
                  local_270 = IVar17;
                  puVar18 = local_188;
                  IVar16 = IVar16 + 0x20;
                  FUN_10003b4f8(IVar16,local_1a8);
                  FUN_100386198(0);
                  iVar12 = (int)&local_1b0;
                  pcVar25 = (char *)local_1a8;
                  param_5 = (undefined8 *******)(puVar19 + 8);
                  _swift_dynamicCast();
                  uVar24 = local_1b0;
                  if (iVar12 == 0) {
                    _swift_release(puVar18);
                    local_1b0 = 0;
                    _swift_bridgeObjectRelease(local_270);
                    pppppppuVar20 = local_268;
                    pppppppuVar14 = local_260;
                    pppppppuVar30 = local_258;
                    pppppppuVar27 = local_1e0;
                    goto LAB_1004db724;
                  }
                  uVar34 = *(ulong *)(puVar18 + 0x10);
                  local_188 = puVar18;
                  if (*(ulong *)(puVar18 + 0x18) >> 1 <= uVar34) {
                    param_5 = (undefined8 *******)0x1;
                    pcVar25 = (char *)(uVar34 + 1);
                    FUN_1001cc5c4(1 < *(ulong *)(puVar18 + 0x18));
                  }
                  puVar18 = local_188;
                  *(undefined8 ********)(local_188 + 0x10) = (undefined8 *******)(uVar34 + 1);
                  *(undefined8 *)(local_188 + uVar34 * 8 + 0x20) = uVar24;
                  puVar19 = PTR___sypN_100a1e038;
                  lVar15 = lVar15 + -1;
                  IVar17 = local_270;
                } while (lVar15 != 0);
                _swift_bridgeObjectRelease(local_270);
                pppppppuVar30 = local_258;
                if ((long)puVar18 < 0) goto LAB_1004dbafc;
LAB_1004db914:
                if (((ulong)puVar18 >> 0x3e & 1) != 0) goto LAB_1004dbafc;
                puVar31 = *(undefined **)(puVar18 + 0x10);
              }
              if (puVar31 == (undefined *)0x0) {
                _swift_release(puVar18);
                pppppppuVar20 = local_268;
                pppppppuVar14 = local_260;
                pppppppuVar27 = local_1e0;
              }
              else {
                _swift_retain(puVar18);
                lVar15 = 4;
                do {
                  IVar16 = lVar15 - 4;
                  if (((ulong)puVar18 & 0xc000000000000001) == 0) {
                    IVar17 = *(ID *)(puVar18 + lVar15 * 8);
                  }
                  else {
                    IVar17 = IVar16;
                    FUN_1000cce70(IVar16,puVar18);
                  }
                  puVar19 = (undefined *)(lVar15 - 3);
                  if (SCARRY8(IVar16,1)) {
                    /* WARNING: Does not return */
                    pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbb74);
                    (*pcVar7)();
                  }
                  IVar16 = _objc_msgSend(IVar17,"id");
                  if ((long)(int)IVar16 == (uVar23 & 0xff)) {
                    _swift_release_n(puVar18,2);
                    pppppppuVar14 = local_1c0;
                    IVar16 = _objc_msgSend((ID)local_1c0,"id");
                    uVar13 = (uint)IVar16;
                    FUN_10055ee18();
                    uVar11 = 0;
                    if ((uVar13 & 0xff) != 0x14) {
                      uVar11 = uVar13;
                    }
                    local_278 = (ulong)uVar11;
                    _objc_msgSend(IVar17,"volume");
                    pcVar26 = "muted";
                    ppppppuVar32 = ppppppuVar38;
                    IVar16 = _objc_msgSend(IVar17,"muted");
                    pppppppuVar27 = local_1e0;
                    puVar5 = local_240;
                    local_270 = CONCAT44(local_270._4_4_,(int)IVar16);
                    pIVar2 = (ID *)((long)pppppppuVar14 + _TtC8Playback7SongBus::storedUUID);
                    pppppppuVar14 = (undefined8 *******)pIVar2[1];
                    if (pppppppuVar14 == (undefined8 *******)0x0) {
                      __s10Foundation4UUIDVACycfC(local_240);
                      __s10Foundation4UUIDV10uuidStringSSvg();
                      pcVar25 = (char *)pppppppuStack_230;
                      (*(code *)local_238[1])(puVar5);
                      IVar16 = pIVar2[1];
                      *pIVar2 = (ID)pppppppuVar14;
                      pIVar2[1] = (ID)pcVar26;
                      _swift_bridgeObjectRetain(pcVar26);
                      _swift_bridgeObjectRelease(IVar16);
                      pppppppuVar36 = (undefined8 *******)0x0;
                    }
                    else {
                      pppppppuVar36 = pppppppuVar14;
                      pcVar25 = pcVar26;
                      pcVar26 = (char *)pppppppuVar14;
                      pppppppuVar14 = (undefined8 *******)*pIVar2;
                    }
                    _swift_bridgeObjectRetain(pppppppuVar36);
                    pppppppuVar36 = pppppppuVar27;
                    _swift_isUniquelyReferenced_nonNull_native();
                    if (((ulong)pppppppuVar36 & 1) == 0) {
                      pcVar25 = (char *)((long)pppppppuVar27[2] + 1);
                      pppppppuVar27 = (undefined8 *******)0x0;
                      param_5 = (undefined8 *******)0x1;
                      FUN_10078f854();
                    }
                    ppppppuVar28 = pppppppuVar27[2];
                    if ((undefined8 ******)((ulong)pppppppuVar27[3] >> 1) <= ppppppuVar28) {
                      pppppppuVar27 =
                           (undefined8 *******)(ulong)((undefined8 ******)0x1 < pppppppuVar27[3]);
                      param_5 = (undefined8 *******)0x1;
                      pcVar25 = (char *)((long)ppppppuVar28 + 1U);
                      FUN_10078f854();
                    }
                    pppppppuVar27[2] = (undefined8 *******)((long)ppppppuVar28 + 1U);
                    pppppppuVar27[(long)ppppppuVar28 * 5 + 4] =
                         (undefined8 ******)(local_278 & 0xff);
                    pppppppuVar27[(long)ppppppuVar28 * 5 + 5] = ppppppuVar38;
                    *(char *)(pppppppuVar27 + (long)ppppppuVar28 * 5 + 6) = (char)local_270;
                    pppppppuVar27[(long)ppppppuVar28 * 5 + 7] = pppppppuVar14;
                    pppppppuVar27[(long)ppppppuVar28 * 5 + 8] = (undefined8 ******)pcVar26;
                    pppppppuVar20 = local_268;
                    pppppppuVar14 = local_260;
                    pppppppuVar30 = local_258;
                    puVar19 = PTR___sypN_100a1e038;
                    ppppppuVar38 = ppppppuVar32;
                    goto LAB_1004db724;
                  }
                  lVar15 = lVar15 + 1;
                } while (puVar19 != puVar31);
                pcVar25 = (char *)0x2;
                _swift_release_n(puVar18);
                pppppppuVar20 = local_268;
                pppppppuVar14 = local_260;
                pppppppuVar30 = local_258;
                puVar19 = PTR___sypN_100a1e038;
                pppppppuVar27 = local_1e0;
              }
            }
          }
LAB_1004db724:
          uVar10 = SUB84(param_5,0);
        } while (pppppppuVar33 != pppppppuVar30);
      }
      _swift_bridgeObjectRelease();
    }
  }
  pppppppuVar36 = pppppppuVar27;
  if (pppppppuVar27[2] == (undefined8 ******)0x0) {
    _swift_bridgeObjectRelease();
    pppppppuVar36 = (undefined8 *******)0x0;
    pppppppuVar14 = pppppppuVar27;
  }
  pdVar6 = local_1c8;
  local_1c8[8] = (double)pppppppuVar36;
  FUN_1002e1f58();
  pdVar6[0xf] = (double)((ulong)pppppppuVar14 & 0xffff0001ffffffff);
  pdVar6[0x10] = (double)pcVar25;
  *(byte *)((long)pdVar6 + 0x8a) = (byte)((uint)uVar10 >> 0x10) & 1;
  *(ushort *)(pdVar6 + 0x11) = (ushort)uVar10 & 0x101;
  puVar19 = PTR___swiftEmptyArrayStorage_100a1e050;
  uVar23 = 0;
  thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
  if ((uVar23 & 1) == 0) {
    if (DAT_100ae0030 != -1) {
      _swift_once(&DAT_100ae0030,FUN_1008174c0);
    }
    uVar23 = 0;
    FUN_100819fe0();
    if ((uVar23 & 1) == 0) {
      uVar9 = 0;
      pppppppuVar14 = local_1e8;
      goto LAB_1004dbcf8;
    }
  }
  pppppppuVar14 = local_1e8;
  IVar16 = _objc_msgSend((ID)local_1e8,"storedSMPTEEnabled");
  uVar9 = (undefined1)IVar16;
LAB_1004dbcf8:
  pdVar6 = local_1c8;
  *(undefined1 *)(local_1c8 + 9) = uVar9;
  _objc_msgSend((ID)pppppppuVar14,"smpteStartTime");
  pdVar6[10] = (double)ppppppuVar38;
  *(undefined1 *)(pdVar6 + 0xb) = 0;
  IVar16 = _objc_msgSend((ID)pppppppuVar14,"storedSMPTETimelineLocation");
  if (IVar16 == 0) {
    FUN_1002e4b7c();
  }
  else {
    _objc_msgSend(IVar16,"doubleValue");
  }
  pIVar2 = (ID *)((long)local_1c8 + (long)*(int *)(local_1f8 + 0x84));
  local_1c8[0xc] = (double)ppppppuVar38;
  *(undefined1 *)(local_1c8 + 0xd) = 0;
  IVar16 = _objc_msgSend((ID)pppppppuVar14,"midiBankID");
  *pIVar2 = IVar16;
  *(undefined1 *)(pIVar2 + 1) = 0;
  if ((local_1fc & 1) == 0) {
    uVar23 = 1;
    FUN_1002e1174();
    if (uVar23 >> 0x3e == 0) {
      uVar34 = *(ulong *)((uVar23 & 0xfffffffffffff8) + 0x10);
      pppppppuVar14 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    else {
      uVar34 = uVar23 & 0xffffffffffffff8;
      if ((long)uVar23 < 0) {
        uVar34 = uVar23;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      pppppppuVar14 = (undefined8 *******)PTR___swiftEmptyArrayStorage_100a1e050;
    }
    PTR___swiftEmptyArrayStorage_100a1e050 = (undefined *)pppppppuVar14;
    if (uVar34 == 0) {
      _swift_retain(pppppppuVar14);
    }
    else {
      local_1a8[0] = (undefined8 *******)puVar19;
      local_1e0 = pppppppuVar36;
      local_1c0 = (undefined8 *******)pcVar25;
      _swift_retain(puVar19);
      FUN_1001cce9c(0,uVar34 & ((long)uVar34 >> 0x3f ^ 0xffffffffffffffffU),0);
      if ((long)uVar34 < 0) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dc090);
        (*pcVar7)();
      }
      lVar15 = 0;
      do {
        pppppppuVar14 = local_1a8[0];
        uVar1 = lVar15 + 1;
        if (SCARRY8(lVar15,1)) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x1004dbf50);
          (*pcVar7)();
        }
        if ((uVar23 & 0xc000000000000001) != 0) {
          FUN_1000cc5b8(lVar15,uVar23);
        }
        FUN_1007cd924(&local_c0);
        if (unaff_x21 != 0) {
          _swift_bridgeObjectRelease(local_248);
          _swift_bridgeObjectRelease(local_208);
          _swift_bridgeObjectRelease(uVar23);
          _swift_release(pppppppuVar14);
          _swift_bridgeObjectRelease(local_250);
          _swift_bridgeObjectRelease(local_218);
          _swift_bridgeObjectRelease(local_1e0);
          _swift_bridgeObjectRelease(local_1c0);
LAB_1004dbf1c:
          lVar15 = 0;
          __s10Foundation4DateVMa();
          (**(code **)(*(long *)(lVar15 + -8) + 8))((long)local_1c8 + local_220,lVar15);
          _swift_bridgeObjectRelease(local_228);
          return;
        }
        ppppppuVar38 = pppppppuVar14[2];
        local_1a8[0] = pppppppuVar14;
        if ((undefined8 ******)((ulong)pppppppuVar14[3] >> 1) <= ppppppuVar38) {
          FUN_1001cce9c((undefined8 ******)0x1 < pppppppuVar14[3],
                        (undefined8 ******)((long)ppppppuVar38 + 1U),1);
        }
        local_1a8[0][2] = (undefined8 ******)((long)ppppppuVar38 + 1U);
        local_1a8[0][(long)ppppppuVar38 * 9 + 5] = ppppppuStack_b8;
        local_1a8[0][(long)ppppppuVar38 * 9 + 4] = local_c0;
        *(undefined2 *)(local_1a8[0] + (long)ppppppuVar38 * 9 + 0xc) = local_80;
        local_1a8[0][(long)ppppppuVar38 * 9 + 9] = ppppppuStack_98;
        local_1a8[0][(long)ppppppuVar38 * 9 + 8] = ppppppuStack_a0;
        local_1a8[0][(long)ppppppuVar38 * 9 + 0xb] = ppppppuStack_88;
        local_1a8[0][(long)ppppppuVar38 * 9 + 10] = local_90;
        local_1a8[0][(long)ppppppuVar38 * 9 + 7] = ppppppuStack_a8;
        local_1a8[0][(long)ppppppuVar38 * 9 + 6] = local_b0;
        lVar15 = lVar15 + 1;
        pppppppuVar14 = local_1a8[0];
      } while (uVar1 != uVar34);
    }
    _swift_bridgeObjectRelease(uVar23);
  }
  else {
    pppppppuVar14 = (undefined8 *******)0x0;
  }
  IVar16 = local_1f0;
  local_1c8[0xe] = (double)pppppppuVar14;
  IVar17 = _objc_msgSend(local_1f0,"modularClickLengthValue");
  if ((int)IVar17 == 0) {
    if (DAT_100adea10 != -1) {
      _swift_once(&DAT_100adea10,FUN_1001709a4);
    }
    uVar24 = DAT_100b757a8;
    FUN_1001718ec();
    bVar8 = (byte)uVar24;
  }
  else {
    IVar16 = _objc_msgSend(IVar16,"modularClickLengthValue");
    bVar8 = (int)IVar16 == 4;
  }
  *(byte *)((long)local_1c8 + 0x8b) = bVar8 & 1;
  return;
}

// ==== 1004f2edc FUN_1004f2edc ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001004f36a0) */
/* WARNING: Removing unreachable block (ram,0x0001004f35c8) */
/* WARNING: Removing unreachable block (ram,0x0001004f39a8) */

long FUN_1004f2edc(double param_1)

{
  double *pdVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  ID IVar5;
  long lVar6;
  double dVar7;
  undefined *puVar8;
  double dVar9;
  undefined8 uVar10;
  ID IVar11;
  ulong uVar12;
  undefined *puVar13;
  char *pcVar14;
  long lVar15;
  long unaff_x20;
  ID IVar16;
  long lVar17;
  long lVar18;
  ID self;
  long lVar19;
  long lVar20;
  undefined1 local_80 [16];
  
  lVar20 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar15 = *(long *)(unaff_x20 + _TtC8Playback9Sequencer::channelGroup);
  if (lVar15 == 0) {
    puVar8 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    _objc_msgSend((ID)puVar8,"sharedApplication");
    return 0;
  }
  self = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::song);
  IVar16 = *(ID *)(self + _TtC8Playback4Song::privateWorkingCopyArrangement);
  if (IVar16 == 0) {
    _swift_retain(lVar15);
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 != 0) {
      IVar5 = IVar11;
      FUN_10032ee88();
      IVar16 = IVar5;
      FUN_1005e3b94(IVar5,IVar11);
      _swift_bridgeObjectRelease(IVar5);
      if (IVar16 != 0) {
        *(ID *)(self + lVar20) = IVar16;
        goto LAB_1004f2f44;
      }
    }
  }
  else {
    _swift_retain(lVar15);
LAB_1004f2f44:
    _objc_msgSend(IVar16,"storedEndTime");
    dVar7 = param_1;
    IVar16 = _objc_msgSend(IVar16,"song");
    if (IVar16 == 0) {
      dVar9 = 1.0;
    }
    else {
      FUN_1003220ec();
      dVar9 = dVar7;
    }
    FUN_1004f240c(0);
    param_1 = ABS(param_1 * dVar9 - dVar7);
    if (param_1 < 0.6) {
      *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEndThreshold) = 1;
    }
  }
  FUN_1004f240c();
  if (*(double *)(unaff_x20 + _TtC8Playback9Sequencer::nextPreparationSequenceTime) <= param_1) {
    if (*(long *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) != 0) goto LAB_1004f3c70;
    FUN_1004fdbe0();
  }
  IVar16 = *(ID *)(self + lVar20);
  if (IVar16 == 0) {
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 != 0) {
      IVar5 = IVar11;
      FUN_10032ee88();
      IVar16 = IVar5;
      FUN_1005e3b94(IVar5,IVar11);
      _swift_bridgeObjectRelease(IVar5);
      if (IVar16 != 0) {
        *(ID *)(self + lVar20) = IVar16;
        goto LAB_1004f30f8;
      }
    }
LAB_1004f322c:
    bVar3 = false;
  }
  else {
LAB_1004f30f8:
    IVar16 = _objc_msgSend(IVar16,"song");
    if ((IVar16 == 0) || (*(char *)(IVar16 + _TtC8Playback4Song::isLiveCrossfading) != '\x01')) {
      uVar4 = 0;
      FUN_1002da058();
      if ((uVar4 & 0xff) != 3) goto LAB_1004f322c;
    }
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    lVar6 = *(long *)(DAT_100b75a80 + 0x10);
    if ((lVar6 == 0) || (FUN_1004b7958(), lVar6 == 0)) goto LAB_1004f322c;
    bVar3 = true;
  }
  if (DAT_100adeca8 != -1) {
    _swift_once(&DAT_100adeca8,FUN_100224b00);
  }
  lVar6 = *(long *)(DAT_100b75a80 + 0x10);
  if ((lVar6 != 0) && (FUN_1004a9df0(), lVar6 != 0)) {
    FUN_10034293c(0);
    IVar16 = self;
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(self,lVar6);
    if ((IVar16 & 1) != 0) {
      IVar16 = *(ID *)(self + lVar20);
      if (IVar16 == 0) {
        IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
        dVar7 = 0.0;
        if (IVar11 != 0) {
          IVar5 = IVar11;
          FUN_10032ee88();
          IVar16 = IVar5;
          FUN_1005e3b94(IVar5,IVar11);
          _swift_bridgeObjectRelease(IVar5);
          dVar7 = 0.0;
          if (IVar16 != 0) {
            *(ID *)(self + lVar20) = IVar16;
            goto LAB_1004f32c0;
          }
        }
      }
      else {
LAB_1004f32c0:
        pcVar14 = "endFade";
        IVar16 = _objc_msgSend(IVar16,"endFade");
        dVar7 = 0.0;
        if ((((int)IVar16 != 0) &&
            (*(char *)(lVar15 + _TtC8Playback16SongChannelGroup::fadeStartTimecode + 8) == '\x01'))
           && (FUN_1004fbb78(), ((ulong)pcVar14 & 1) == 0)) {
          dVar9 = dVar7;
          FUN_1004f240c();
          lVar6 = _TtC8Playback9Sequencer::fadeOutAtEndDidBegin;
          if (param_1 < dVar7) {
            bVar3 = true;
          }
          dVar7 = dVar9;
          if ((!bVar3) &&
             ((*(byte *)(unaff_x20 + _TtC8Playback9Sequencer::fadeOutAtEndDidBegin) & 1) == 0)) {
            FUN_100647c80(1,0,0,0);
            *(undefined1 *)(unaff_x20 + lVar6) = 1;
            puVar8 = &_OBJC_CLASS___UIApplication;
            _swift_getInitializedObjCClass();
            IVar16 = _objc_msgSend((ID)puVar8,"sharedApplication");
            dVar9 = (double)_objc_msgSend(IVar16,"delegate");
            dVar7 = 0.0;
            if (dVar9 != 0.0) {
              uVar10 = 0;
              FUN_100842dec(0);
              dVar7 = dVar9;
              _swift_dynamicCastClass(dVar9,uVar10);
              if (((dVar7 == 0.0) ||
                  (*(ID *)((long)dVar7 + _TtC8Playback11AppDelegate::window) == 0)) ||
                 (IVar16 = _objc_msgSend(*(ID *)((long)dVar7 + _TtC8Playback11AppDelegate::window),
                                         "rootViewController"), IVar16 == 0)) {
                _swift_unknownObjectRelease();
                dVar7 = dVar9;
              }
              else {
                uVar10 = 0;
                FUN_100413a94(0);
                _swift_dynamicCastClass(IVar16,uVar10);
                _swift_unknownObjectRelease(dVar9);
                if (IVar16 != 0) {
                  dVar7 = 0.0;
                  if (*(long *)(IVar16 + _TtC8Playback18MainViewController::transportViewController)
                      == 0) goto LAB_1004f3c9c;
                  IVar16 = *(long *)(IVar16 + _TtC8Playback18MainViewController::
                                              transportViewController) +
                           _TtC8Playback23TransportViewController::fadeButton;
                  _swift_unknownObjectWeakLoadStrong();
                  if (IVar16 == 0) {
                    /* WARNING: Does not return */
                    pcVar2 = (code *)SoftwareBreakpoint(1,0x1004f3f10);
                    (*pcVar2)();
                  }
                  _objc_msgSend(IVar16,"setSelected:",1);
                  FUN_100867240(0);
                }
                dVar7 = 0.0;
              }
            }
          }
        }
      }
LAB_1004f3c9c:
      FUN_100500a94();
      if (((ulong)dVar7 & 1) != 0) {
        uVar10 = *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement);
        *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) = 0;
        _swift_release(uVar10);
        FUN_1004f3f10();
      }
    }
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar6 = *(long *)(DAT_100b75e40 + 0x18);
  if (lVar6 != 0) {
    lVar17 = *(long *)(lVar6 + 0x78);
    if (lVar17 == 0) {
      lVar18 = *(long *)(lVar6 + 0x10);
      FUN_10073f4a4(0);
      _swift_allocObject();
      _swift_retain(lVar6);
      FUN_10074128c();
      uVar10 = *(undefined8 *)(lVar6 + 0x78);
      *(long *)(lVar6 + 0x78) = lVar18;
      _swift_retain(lVar18);
      _swift_release(uVar10);
      lVar17 = 0;
    }
    else {
      _swift_retain(lVar6);
      lVar18 = lVar17;
    }
    _swift_retain(lVar17);
    _swift_release(lVar6);
    IVar16 = *(ID *)(self + lVar20);
    if (IVar16 == 0) {
      IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
      if (IVar11 != 0) {
        IVar5 = IVar11;
        FUN_10032ee88();
        IVar16 = IVar5;
        FUN_1005e3b94(IVar5,IVar11);
        _swift_bridgeObjectRelease(IVar5);
        if (IVar16 != 0) {
          *(ID *)(self + lVar20) = IVar16;
          goto LAB_1004f3530;
        }
      }
      _swift_release(lVar18);
    }
    else {
LAB_1004f3530:
      if (((*(byte *)(lVar18 + 0x39) & 1) == 0) &&
         (IVar11 = _objc_msgSend(IVar16,"padIntroOutroOnly"), (int)IVar11 != 0)) {
        pdVar1 = (double *)(unaff_x20 + _TtC8Playback9Sequencer::padIntroTrigger);
        if ((((ulong)pdVar1[1] & 1) == 0) &&
           (((*(byte *)((long)pdVar1 + 9) & 1) == 0 && (FUN_1004f240c(), *pdVar1 < param_1)))) {
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar13 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(),
             puVar8 = PTR___swiftEmptyArrayStorage_100a1e050, puVar13 == (undefined *)0x0)) {
            puVar13 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(puVar8);
          }
          FUN_10073b6dc(0,0,1,puVar13,0,1);
          _swift_bridgeObjectRelease(puVar13);
          *(undefined1 *)(pdVar1 + 1) = 1;
        }
        pdVar1 = (double *)(unaff_x20 + _TtC8Playback9Sequencer::padOutroTrigger);
        if ((((((ulong)pdVar1[1] & 1) == 0) && ((*(byte *)((long)pdVar1 + 9) & 1) == 0)) &&
            (IVar16 = _objc_msgSend(IVar16,"includePad"), (int)IVar16 != 0)) &&
           ((FUN_1004f240c(), *pdVar1 < param_1 && (FUN_1002dc978(), IVar16 != 0)))) {
          IVar11 = _objc_msgSend(self,"keyID");
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar8 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(), puVar8 == (undefined *)0x0)) {
            puVar8 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(PTR___swiftEmptyArrayStorage_100a1e050);
          }
          FUN_10073b6dc(IVar16,(long)(int)IVar11,0,puVar8,0,1);
          _swift_bridgeObjectRelease(puVar8);
          *(undefined1 *)(pdVar1 + 1) = 1;
        }
        if (*(char *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEndThreshold) == '\x01') {
          IVar16 = *(ID *)(self + lVar20);
          if (IVar16 == 0) {
            IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
            if (IVar11 != 0) {
              IVar5 = IVar11;
              FUN_10032ee88();
              IVar16 = IVar5;
              FUN_1005e3b94(IVar5,IVar11);
              _swift_bridgeObjectRelease(IVar5);
              if (IVar16 != 0) {
                *(ID *)(self + lVar20) = IVar16;
                goto LAB_1004f36f8;
              }
            }
            goto LAB_1004f3928;
          }
LAB_1004f36f8:
          IVar16 = _objc_msgSend(IVar16,"song");
          if ((IVar16 != 0) && (*(char *)(IVar16 + _TtC8Playback4Song::isLiveCrossfading) == '\x01')
             ) goto LAB_1004f3928;
          uVar4 = 0;
          FUN_1002da058();
          bVar3 = (uVar4 & 0xff) == 4;
        }
        else {
LAB_1004f3928:
          bVar3 = false;
        }
        if ((((*(long *)(DAT_100b75e40 + 0x28) == 0) && (!bVar3)) &&
            (*(char *)(pdVar1 + 1) == '\x01')) &&
           (((*(byte *)((long)pdVar1 + 9) & 1) == 0 && (FUN_1004f240c(), param_1 < *pdVar1)))) {
          if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
             (puVar13 = PTR___swiftEmptyArrayStorage_100a1e050,
             __ss18_CocoaArrayWrapperV8endIndexSivg(),
             puVar8 = PTR___swiftEmptyArrayStorage_100a1e050, puVar13 == (undefined *)0x0)) {
            puVar13 = PTR___swiftEmptySetSingleton_100a1e060;
            _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
          }
          else {
            puVar13 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
            FUN_1000217d4();
            _swift_release(puVar8);
          }
          FUN_10073b6dc(0,0,1,puVar13,0,1);
          _swift_release(lVar18);
          _swift_bridgeObjectRelease(puVar13);
          *(undefined1 *)(pdVar1 + 1) = 0;
          goto LAB_1004f39e8;
        }
      }
      _swift_release(lVar18);
    }
  }
LAB_1004f39e8:
  lVar6 = _TtC8Playback9Sequencer::uuid;
  lVar17 = *(long *)(DAT_100b75e40 + 0x28);
  if (lVar17 == 0) goto LAB_1004f3c70;
  _swift_retain();
  _swift_retain(lVar17);
  uVar12 = unaff_x20 + lVar6;
  __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar12,lVar17 + lVar6);
  _swift_release();
  _swift_release(lVar17);
  if ((uVar12 & 1) == 0) goto LAB_1004f3c70;
  IVar11 = *(ID *)(self + lVar20);
  IVar16 = IVar11;
  if (IVar11 == 0) {
    IVar11 = _objc_msgSend(self,"workingCopyArrangementID");
    if (IVar11 == 0) goto LAB_1004f3c70;
    IVar5 = IVar11;
    FUN_10032ee88();
    IVar16 = IVar5;
    FUN_1005e3b94(IVar5,IVar11);
    _swift_bridgeObjectRelease(IVar5);
    if (IVar16 == 0) goto LAB_1004f3c70;
    *(ID *)(self + lVar20) = IVar16;
    IVar11 = 0;
  }
  FUN_1004f240c(IVar11);
  dVar7 = param_1;
  IVar11 = _objc_msgSend(IVar16,"storedSMPTETimelineLocation");
  if (IVar11 == 0) {
    FUN_1002e4b7c();
    lVar20 = _TtC8Playback9Sequencer::uuid;
    lVar17 = _TtC8Playback9Sequencer::smpteBeganDuringTransition;
  }
  else {
    _objc_msgSend(IVar11,"doubleValue");
    lVar20 = _TtC8Playback9Sequencer::uuid;
    lVar17 = _TtC8Playback9Sequencer::smpteBeganDuringTransition;
  }
  _TtC8Playback9Sequencer::uuid = lVar20;
  _TtC8Playback9Sequencer::smpteBeganDuringTransition = lVar17;
  if (((param_1 < dVar7) || ((*(byte *)(unaff_x20 + lVar17) & 1) != 0)) ||
     ((lVar18 = *(long *)(DAT_100b75e40 + 0x18), lVar18 == 0 ||
      (lVar19 = *(long *)(DAT_100b75e40 + 0x28), lVar19 == 0)))) goto LAB_1004f3c70;
  _swift_retain();
  _swift_retain(lVar18);
  _swift_retain(lVar19);
  uVar12 = lVar19 + lVar20;
  __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar12,unaff_x20 + lVar6);
  _swift_release(lVar19);
  _swift_release();
  if ((uVar12 & 1) == 0) {
    _swift_release(lVar15);
    lVar15 = lVar18;
    goto LAB_1004f3c70;
  }
  lVar20 = *(long *)(lVar18 + 0x48);
  _swift_retain(lVar20);
  _swift_release(lVar18);
  if (lVar20 == 0) goto LAB_1004f3c70;
  uVar12 = 0;
  thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
  if ((uVar12 & 1) == 0) {
    if (DAT_100ae0030 != -1) {
      _swift_once(&DAT_100ae0030,FUN_1008174c0);
    }
    uVar12 = 0;
    FUN_100819fe0();
    if ((uVar12 & 1) != 0) goto LAB_1004f3bec;
  }
  else {
LAB_1004f3bec:
    IVar11 = _objc_msgSend(IVar16,"storedSMPTEEnabled");
    if ((int)IVar11 != 0) {
      IVar11 = _objc_msgSend(IVar16,"storedSMPTETimelineLocation");
      if (IVar11 == 0) {
        FUN_1002e4b7c();
      }
      else {
        _objc_msgSend(IVar11,"doubleValue");
      }
      dVar9 = dVar7;
      _objc_msgSend(IVar16,"smpteStartTime");
      FUN_1000cfba4(dVar7);
      FUN_1000cfbac(dVar9);
      uVar12 = 0;
      thunk_FUN_1002db810(0x26,PTR___swiftEmptyArrayStorage_100a1e050);
      if ((uVar12 & 1) == 0) {
        if (DAT_100ae0030 != -1) {
          _swift_once(&DAT_100ae0030,FUN_1008174c0);
        }
        uVar12 = 0;
        FUN_100819fe0();
        if ((uVar12 & 1) != 0) goto LAB_1004f3d2c;
      }
      else {
LAB_1004f3d2c:
        IVar16 = _objc_msgSend(self,"storedSMPTEFollowsDefaultArrangement");
        if ((IVar16 & 1) == 0) {
          FUN_1004f240c();
          goto LAB_1004f3d8c;
        }
      }
      uVar10 = *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::sampleTimeCurrentTime);
      _swift_retain(uVar10);
      __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                (local_80,FUN_100504fa8,uVar10,PTR___sSdN_100a1dd60);
      _swift_release(uVar10);
LAB_1004f3d8c:
      FUN_1000cfd9c();
      FUN_1000cfac8(*(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::privatePlayState));
      _swift_release(lVar20);
      _swift_release(lVar15);
      *(undefined1 *)(unaff_x20 + lVar17) = 1;
      return lVar15;
    }
  }
  FUN_1000cfac8(0);
  _swift_release(lVar20);
LAB_1004f3c70:
  _swift_release(lVar15);
  return lVar15;
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

// ==== 100502d0c FUN_100502d0c ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001005035b0) */
/* WARNING: Removing unreachable block (ram,0x00010050316c) */
/* WARNING: Removing unreachable block (ram,0x000100503170) */

void FUN_100502d0c(long param_1)

{
  bool bVar1;
  uint uVar2;
  ID IVar3;
  ID IVar4;
  ulong uVar5;
  undefined *puVar6;
  ID IVar7;
  undefined8 uVar8;
  ID IVar9;
  undefined *puVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined1 auStack_78 [24];
  
  _swift_beginAccess(param_1 + 0x10,auStack_78,0,0);
  param_1 = param_1 + 0x10;
  _swift_weakLoadStrong();
  if (param_1 == 0) {
    return;
  }
  if ((*(char *)(param_1 + _TtC8Playback9Sequencer::privatePlayState) != '\x01') ||
     (*(long *)(param_1 + _TtC8Playback9Sequencer::nextSongMapElement) != 0)) goto LAB_10050339c;
  if (*(char *)(param_1 + _TtC8Playback9Sequencer::fadeOutAtEndDidBegin) == '\x01') {
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    bVar1 = *(long *)(DAT_100b75e40 + 0x28) == 0;
  }
  else {
    bVar1 = false;
  }
  FUN_1004f5388(0);
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar13 = *(long *)(DAT_100b75e40 + 0x18);
  if (lVar13 != 0) {
    lVar11 = *(long *)(lVar13 + 0x78);
    if (lVar11 == 0) {
      lVar12 = *(long *)(lVar13 + 0x10);
      FUN_10073f4a4(0);
      _swift_allocObject();
      _swift_retain(lVar13);
      FUN_10074128c();
      uVar8 = *(undefined8 *)(lVar13 + 0x78);
      *(long *)(lVar13 + 0x78) = lVar12;
      _swift_retain(lVar12);
      _swift_release(uVar8);
      lVar11 = 0;
    }
    else {
      _swift_retain(lVar13);
      lVar12 = lVar11;
    }
    _swift_retain(lVar11);
    _swift_release(lVar13);
    lVar13 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    if ((*(byte *)(lVar12 + 0x39) & 1) == 0) {
      IVar9 = *(ID *)(param_1 + _TtC8Playback9Sequencer::song);
      IVar7 = *(ID *)(IVar9 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar7 == 0) {
        IVar3 = _objc_msgSend(IVar9,"workingCopyArrangementID");
        if (IVar3 == 0) {
          _swift_release(lVar12);
        }
        else {
          IVar4 = IVar3;
          FUN_10032ee88();
          IVar7 = IVar4;
          FUN_1005e3b94(IVar4,IVar3);
          _swift_bridgeObjectRelease(IVar4);
          if (IVar7 != 0) {
            *(ID *)(IVar9 + lVar13) = IVar7;
            goto LAB_100502ea8;
          }
          _swift_release(lVar12);
        }
      }
      else {
LAB_100502ea8:
        IVar9 = _objc_msgSend(IVar7,"song");
        if ((IVar9 == 0) || ((*(byte *)(IVar9 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
          uVar2 = 0;
          FUN_1002da058();
          if ((uVar2 & 0xff) < 6 && (1 << (ulong)(uVar2 & 0x1f) & 0x31U) != 0) {
            IVar9 = _objc_msgSend(IVar7,"transitionContinuePad");
            IVar7 = _objc_msgSend(IVar7,"song");
            if ((IVar7 == 0) ||
               ((*(byte *)(IVar7 + _TtC8Playback4Song::isLiveCrossfading) & 1) == 0)) {
              uVar5 = 0;
              FUN_1002da058();
            }
            else {
              uVar5 = 3;
            }
            if (DAT_100adeca8 != -1) {
              _swift_once(&DAT_100adeca8,FUN_100224b00);
            }
            lVar13 = *(long *)(DAT_100b75a80 + 0x10);
            if (lVar13 == 0) {
              if ((IVar9 & 1) != 0) {
LAB_1005030dc:
                _swift_release(lVar12);
                goto LAB_10050324c;
              }
            }
            else {
              FUN_1004b9338();
              lVar11 = _TtC8Playback4Song::privateWorkingCopyArrangement;
              if ((IVar9 & 1) != 0) {
                if (((lVar13 == 0) || ((uVar5 & 0xff) != 0)) ||
                   (*(long *)(DAT_100b75e40 + 0x28) == 0)) goto LAB_1005030dc;
                IVar7 = *(ID *)(*(long *)(DAT_100b75e40 + 0x28) + _TtC8Playback9Sequencer::song);
                lVar13 = *(long *)(IVar7 + _TtC8Playback4Song::privateWorkingCopyArrangement);
                if (lVar13 == 0) {
                  IVar9 = _objc_msgSend(IVar7,"workingCopyArrangementID");
                  if (IVar9 != 0) {
                    IVar3 = IVar9;
                    FUN_10032ee88();
                    IVar4 = IVar3;
                    FUN_1005e3b94(IVar3,IVar9);
                    _swift_bridgeObjectRelease(IVar3);
                    if (IVar4 != 0) {
                      *(ID *)(IVar7 + lVar11) = IVar4;
                      lVar13 = 0;
                      goto LAB_100503098;
                    }
                  }
                  _swift_release(lVar12);
                }
                else {
LAB_100503098:
                  FUN_1002dc978();
                  if (lVar13 == 0) {
                    _swift_release(lVar12);
                  }
                  else {
                    puVar6 = *(undefined **)(IVar7 + lVar11);
                    if (puVar6 == (undefined *)0x0) {
                      IVar9 = _objc_msgSend(IVar7,"workingCopyArrangementID");
                      if (IVar9 != 0) {
                        IVar3 = IVar9;
                        FUN_10032ee88();
                        IVar4 = IVar3;
                        FUN_1005e3b94(IVar3,IVar9);
                        _swift_bridgeObjectRelease(IVar3);
                        if (IVar4 != 0) {
                          *(ID *)(IVar7 + lVar11) = IVar4;
                          puVar6 = (undefined *)0x0;
                          goto LAB_1005030c0;
                        }
                      }
                      if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
                         (puVar6 = PTR___swiftEmptyArrayStorage_100a1e050,
                         __ss18_CocoaArrayWrapperV8endIndexSivg(),
                         puVar10 = PTR___swiftEmptyArrayStorage_100a1e050,
                         puVar6 == (undefined *)0x0)) {
                        puVar6 = PTR___swiftEmptySetSingleton_100a1e060;
                        _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
                      }
                      else {
                        puVar6 = PTR___swiftEmptyArrayStorage_100a1e050;
                        _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
                        FUN_1000217d4();
                        _swift_release(puVar10);
                      }
                    }
                    else {
LAB_1005030c0:
                      FUN_1002e16c8(puVar6);
                    }
                    IVar7 = _objc_msgSend(IVar7,"keyID");
                    FUN_10073b6dc(lVar13,(long)(int)IVar7,0,puVar6,0,1);
                    _swift_bridgeObjectRelease(puVar6);
                    if ((*(byte *)(lVar12 + 0x39) & 1) == 0) {
                      puVar6 = &_OBJC_CLASS___UIApplication;
                      _swift_getInitializedObjCClass();
                      IVar7 = _objc_msgSend((ID)puVar6,"sharedApplication");
                      IVar7 = _objc_msgSend(IVar7,"delegate");
                      if (IVar7 != 0) {
                        uVar8 = 0;
                        FUN_100842dec(0);
                        IVar9 = IVar7;
                        _swift_dynamicCastClass(IVar7,uVar8);
                        if (((IVar9 == 0) ||
                            (*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window) == 0)) ||
                           (IVar9 = _objc_msgSend(*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window
                                                         ),"rootViewController"), IVar9 == 0)) {
                          _swift_unknownObjectRelease(IVar7);
                        }
                        else {
                          uVar8 = 0;
                          FUN_100413a94(0);
                          _swift_dynamicCastClass(IVar9,uVar8);
                          if (IVar9 != 0) {
                            _swift_unknownObjectRelease(IVar7);
                            if ((*(long *)(IVar9 + _TtC8Playback18MainViewController::
                                                   mixerViewController) == 0) ||
                               (*(long *)(*(long *)(IVar9 + _TtC8Playback18MainViewController::
                                                            mixerViewController) +
                                         _TtC8Playback19MixerViewController::
                                         mixerPadPanelViewController) == 0)) {
                              _swift_release(lVar12);
                            }
                            else {
                              FUN_10046f9a4(lVar13);
                              _swift_release(lVar12);
                            }
                            goto LAB_10050324c;
                          }
                          _swift_unknownObjectRelease(IVar7);
                        }
                      }
                      _swift_release(lVar12);
                    }
                    else {
                      _swift_release(lVar12);
                    }
                  }
                }
                goto LAB_10050324c;
              }
            }
            if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
               (puVar10 = PTR___swiftEmptyArrayStorage_100a1e050,
               __ss18_CocoaArrayWrapperV8endIndexSivg(),
               puVar6 = PTR___swiftEmptyArrayStorage_100a1e050, puVar10 == (undefined *)0x0)) {
              puVar10 = PTR___swiftEmptySetSingleton_100a1e060;
              _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
            }
            else {
              puVar10 = PTR___swiftEmptyArrayStorage_100a1e050;
              _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
              FUN_1000217d4();
              _swift_release(puVar6);
            }
            FUN_10073b6dc(0,0,1,puVar10,0,1);
            _swift_bridgeObjectRelease(puVar10);
            _swift_release(lVar12);
            goto LAB_10050324c;
          }
        }
        _swift_release(lVar12);
      }
    }
    else {
      _swift_release(lVar12);
    }
  }
LAB_10050324c:
  uVar5 = *(ulong *)(param_1 + _TtC8Playback9Sequencer::song);
  if (DAT_100adeca8 != -1) {
    _swift_once(&DAT_100adeca8,FUN_100224b00);
  }
  lVar13 = *(long *)(DAT_100b75a80 + 0x10);
  if ((lVar13 != 0) && (FUN_1004a9df0(), lVar13 != 0)) {
    FUN_10034293c(0);
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar5,lVar13);
    if ((uVar5 & 1) != 0) {
      puVar6 = &_OBJC_CLASS___UIApplication;
      _swift_getInitializedObjCClass();
      IVar7 = _objc_msgSend((ID)puVar6,"sharedApplication");
      IVar7 = _objc_msgSend(IVar7,"delegate");
      if (IVar7 != 0) {
        uVar8 = 0;
        FUN_100842dec(0);
        IVar9 = IVar7;
        _swift_dynamicCastClass(IVar7,uVar8);
        if (((IVar9 == 0) || (*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window) == 0)) ||
           (IVar9 = _objc_msgSend(*(ID *)(IVar9 + _TtC8Playback11AppDelegate::window),
                                  "rootViewController"), IVar9 == 0)) {
          _swift_release(param_1);
          _swift_unknownObjectRelease(IVar7);
          return;
        }
        uVar8 = 0;
        FUN_100413a94(0);
        _swift_dynamicCastClass(IVar9,uVar8);
        if (IVar9 == 0) {
          _swift_release(param_1);
          _swift_unknownObjectRelease(IVar7);
          return;
        }
        _swift_unknownObjectRelease(IVar7);
        FUN_10009d028(bVar1);
      }
    }
  }
LAB_10050339c:
  _swift_release();
  return;
}

// ==== 100504280 FUN_100504280 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100504280(undefined8 param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined *puVar6;
  undefined8 *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  ID self;
  long lVar11;
  long unaff_x20;
  long lVar12;
  long lVar13;
  long local_90;
  long local_88;
  long local_80;
  long local_78;
  undefined *local_70;
  undefined8 uStack_68;
  
  lVar3 = 0;
  __sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyOMa();
  local_80 = *(long *)(lVar3 + -8);
  lVar11 = (long)&local_90 - (*(long *)(local_80 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  local_88 = lVar11;
  local_78 = lVar3;
  __sSo17OS_dispatch_queueC8DispatchE10AttributesVMa();
  puVar1 = PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVMa_100a1e0d0;
  lVar11 = lVar11 - (*(long *)(*(long *)(lVar4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0;
  local_90 = lVar11;
  __s8Dispatch0A3QoSVMa();
  lVar11 = lVar11 - (*(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  __s10Foundation4UUIDVMa();
  lVar12 = *(long *)(lVar5 + -8);
  lVar13 = lVar11 - (*(long *)(lVar12 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::channelGroup) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElement) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextSongMapElement) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::enqueuedSongMapElement) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::nextPreparationSequenceTime) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::rebuildGuideForLoopedSection) = 0;
  puVar7 = (undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::___lazy_storage___currentBPM);
  *puVar7 = 0;
  *(undefined1 *)(puVar7 + 1) = 1;
  lVar3 = _TtC8Playback9Sequencer::sampleTimeCurrentTime;
  puVar10 = &DAT_100b048f0;
  FUN_100021774();
  _swift_allocObject();
  FUN_10073cc74(0);
  *(undefined **)(unaff_x20 + lVar3) = puVar10;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::rewindTime) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::fadeOutAtEndDidBegin) = 0;
  puVar7 = (undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::padIntroTrigger);
  *puVar7 = 0;
  *(undefined2 *)(puVar7 + 1) = 0;
  puVar7 = (undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::padOutroTrigger);
  *puVar7 = 0;
  *(undefined2 *)(puVar7 + 1) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEnd) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didReachSongEndThreshold) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::preloadNextSongSequenceTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::autoLinkStartTime) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionDuration) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionBufferOffset) =
       0x3fb0624dd2f1a9fc;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::songToLiveCrossfadeTo) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::didLiveReorderFromFinalSection) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::smpteBeganDuringTransition) = 0;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::remoteSequenceTimeDeviationCount) = 0;
  *(undefined1 *)(unaff_x20 + _TtC8Playback9Sequencer::privatePlayState) = 0;
  __s10Foundation4UUIDVACycfC(lVar13);
  (**(code **)(lVar12 + 0x20))(unaff_x20 + _TtC8Playback9Sequencer::uuid,lVar13,lVar5);
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::song) = param_1;
  *(undefined8 *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElementIndex) = 0;
  FUN_10032fa14(param_1);
  local_70 = (undefined *)0xd00000000000001f;
  uStack_68 = 0x80000001008fb8c0;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(lVar13);
  uVar2 = uStack_68;
  puVar8 = local_70;
  FUN_10004cb08(0);
  __s8Dispatch0A3QoSV15userInteractiveACvgZ(lVar11);
  puVar9 = PTR___swiftEmptyArrayStorage_100a1e050;
  local_70 = PTR___swiftEmptyArrayStorage_100a1e050;
  puVar10 = &DAT_100af5be8;
  FUN_100023140(&DAT_100af5be8,puVar1,
                PTR___sSo17OS_dispatch_queueC8DispatchE10AttributesVs10SetAlgebraACMc_100a1e0e0);
  _swift_retain(puVar9);
  puVar6 = &DAT_100af5bf0;
  FUN_100021774(&DAT_100af5bf0);
  puVar7 = &DAT_100af5bf8;
  FUN_1001d598c(&DAT_100af5bf8,&DAT_100af5c00,puVar1);
  lVar3 = local_90;
  __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
            (local_90,&local_70,puVar6,puVar7,lVar4,puVar10);
  lVar4 = local_88;
  (**(code **)(local_80 + 0x68))
            (local_88,*(undefined4 *)
                       PTR___sSo17OS_dispatch_queueC8DispatchE20AutoreleaseFrequencyO7inherityA2EmFWC_100a1e0e8
             ,local_78);
  __sSo17OS_dispatch_queueC8DispatchE5label3qos10attributes20autoreleaseFrequency6targetABSS_AC0D3QoSVAbCE10AttributesVAbCE011AutoreleaseI0OABSgtcfC
            (puVar8,uVar2,lVar11,lVar3,lVar4,0);
  *(undefined **)(unaff_x20 + _TtC8Playback9Sequencer::timeCriticalQueue) = puVar8;
  lVar3 = 0;
  FUN_100099b80();
  _swift_allocObject();
  *(undefined8 *)(lVar3 + 0x20) = 0;
  *(undefined8 *)(lVar3 + 0x28) = 0;
  *(undefined **)(lVar3 + 0x18) = puVar9;
  _swift_retain();
  FUN_1000be560();
  *(undefined **)(lVar3 + 0x10) = puVar9;
  *(long *)(unaff_x20 + _TtC8Playback9Sequencer::guide) = lVar3;
  puVar10 = &_OBJC_CLASS___NSNotificationCenter;
  _swift_getInitializedObjCClass();
  self = _objc_msgSend((ID)puVar10,"defaultCenter");
  lVar3 = DAT_100adeb98;
  _swift_retain();
  if (lVar3 != -1) {
    _swift_once(&DAT_100adeb98,FUN_1001f91e0);
  }
  _objc_msgSend(self,"addObserver:selector:name:object:");
  _swift_release();
  return;
}

// ==== 10056dea8 FUN_10056dea8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_10056dea8(double param_1,ID param_2,ulong param_3)

{
  int iVar1;
  undefined *puVar2;
  ID IVar3;
  undefined8 uVar4;
  ID IVar5;
  ID IVar6;
  ulong uVar7;
  long lVar8;
  ID IVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  TargetProtocolDescriptor *pTVar15;
  TargetProtocolDescriptor *pTVar16;
  long unaff_x20;
  long lVar17;
  long lVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double local_b0;
  
  puVar2 = &_OBJC_CLASS___UIApplication;
  _swift_getInitializedObjCClass();
  IVar3 = _objc_msgSend((ID)puVar2,"sharedApplication");
  IVar3 = _objc_msgSend(IVar3,"delegate");
  if (IVar3 == 0) {
    return 0;
  }
  uVar4 = 0;
  FUN_100842dec(0);
  IVar5 = IVar3;
  _swift_dynamicCastClass(IVar3,uVar4);
  if (((IVar5 == 0) || (*(ID *)(IVar5 + _TtC8Playback11AppDelegate::window) == 0)) ||
     (IVar5 = _objc_msgSend(*(ID *)(IVar5 + _TtC8Playback11AppDelegate::window),"rootViewController"
                           ), IVar5 == 0)) {
    _swift_unknownObjectRelease(IVar3);
    return IVar3;
  }
  uVar4 = 0;
  FUN_100413a94(0);
  _swift_dynamicCastClass(IVar5,uVar4);
  _swift_unknownObjectRelease(IVar3);
  if (IVar5 == 0) {
    return 0;
  }
  if (*(long *)(IVar5 + _TtC8Playback18MainViewController::mixerViewController) == 0) {
    return 0;
  }
  IVar3 = *(ID *)(*(long *)(IVar5 + _TtC8Playback18MainViewController::mixerViewController) +
                 _TtC8Playback19MixerViewController::currentSetlist);
  if (IVar3 == 0) {
    IVar5 = 0;
  }
  else {
    FUN_1004a9df0();
    lVar12 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    if (IVar3 == 0) {
      IVar5 = 0;
    }
    else {
      IVar5 = *(ID *)(IVar3 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if ((IVar5 == 0) && (IVar5 = _objc_msgSend(IVar3,"workingCopyArrangementID"), IVar5 != 0)) {
        IVar9 = IVar5;
        FUN_10032ee88();
        IVar6 = IVar9;
        FUN_1005e3b94(IVar9,IVar5);
        _swift_bridgeObjectRelease(IVar9);
        IVar5 = IVar6;
        if (IVar6 != 0) {
          *(ID *)(IVar3 + lVar12) = IVar6;
        }
      }
    }
  }
  if ((param_2 == 0) || (IVar3 = _objc_msgSend(param_2,"cue"), IVar3 == 0)) {
    iVar1 = 0;
  }
  else {
    IVar3 = _objc_msgSend(IVar3,"transitionBeats");
    iVar1 = (int)IVar3;
  }
  if (*(char *)(unaff_x20 + 0x50) == '\0') {
    if (param_2 == 0) {
      lVar12 = unaff_x20 + 0x40;
      _swift_unknownObjectWeakLoadStrong();
      if (lVar12 == 0) {
        return 0;
      }
      lVar8 = lVar12;
      _swift_getObjectType();
      _swift_conformsToProtocol();
      if (lVar8 == 0) {
        return 0;
      }
      if (DAT_100adfbd0 != -1) {
        _swift_once(&DAT_100adfbd0,FUN_1005d0614);
      }
      uVar4 = DAT_100b77550;
      lVar17 = lVar12;
      _swift_getObjectType(lVar12);
      _swift_retain(uVar4);
      FUN_1005db3b8(lVar12,0,uVar4,lVar17,lVar8);
      _swift_release(uVar4);
      FUN_10025cc78(unaff_x20,((uint)lVar12 ^ 0xffffffff) & 1,0);
      return 0;
    }
    IVar3 = _objc_msgSend(param_2,"cue");
    IVar3 = _objc_msgSend(IVar3,"songSection");
    uVar7 = _objc_msgSend(IVar3,"arrangement");
    if (uVar7 == 0) {
      if (IVar5 == 0) {
LAB_10056e4b4:
        _objc_msgSend(param_2,"storedValue");
        FUN_10025cc78(unaff_x20,0.5 <= param_1,0);
        return 0;
      }
    }
    else if (IVar5 != 0) {
      FUN_1002eda7c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar7,IVar5);
      if ((uVar7 & 1) != 0) goto LAB_10056e4b4;
    }
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar12 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    lVar8 = *(long *)(DAT_100b75e40 + 0x28);
    if (lVar8 == 0) {
      return 0;
    }
    IVar5 = *(ID *)(lVar8 + _TtC8Playback9Sequencer::song);
    IVar3 = *(ID *)(IVar5 + _TtC8Playback4Song::privateWorkingCopyArrangement);
    _swift_retain(lVar8);
    if ((IVar3 == 0) &&
       (IVar9 = _objc_msgSend(IVar5,"workingCopyArrangementID"), IVar3 = IVar9, IVar9 != 0)) {
      IVar6 = IVar9;
      FUN_10032ee88();
      IVar3 = IVar6;
      FUN_1005e3b94(IVar6,IVar9);
      _swift_bridgeObjectRelease(IVar6);
      if (IVar3 != 0) {
        *(ID *)(IVar5 + lVar12) = IVar3;
      }
    }
    IVar5 = _objc_msgSend(param_2,"cue");
    IVar5 = _objc_msgSend(IVar5,"songSection");
    IVar5 = _objc_msgSend(IVar5,"arrangement");
    if (IVar3 == 0) {
      if (IVar5 != 0) {
        _swift_release(lVar8);
        return 0;
      }
    }
    else {
      if (IVar5 == 0) {
        _swift_release(lVar8);
        return 0;
      }
      FUN_1002eda7c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(IVar3,IVar5);
      if ((IVar3 & 1) == 0) goto LAB_10056ee78;
    }
    lVar12 = unaff_x20 + 0x40;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar12 != 0) {
      lVar17 = lVar12;
      _swift_getObjectType();
      _swift_conformsToProtocol();
      if (lVar17 != 0) {
        _objc_msgSend(param_2,"storedValue");
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        uVar4 = DAT_100b77550;
        lVar18 = lVar12;
        _swift_getObjectType(lVar12);
        _swift_retain(lVar8);
        _swift_retain(uVar4);
        FUN_1005db3d8(lVar12,param_1 < 0.5,1,0,lVar8,0,uVar4,lVar18,lVar17);
        _swift_release(uVar4);
        _swift_release_n(lVar8,2);
        return 0;
      }
    }
LAB_10056ee78:
    _swift_release(lVar8);
    return 0;
  }
  if (*(char *)(unaff_x20 + 0x50) == '\x01') {
    return 0;
  }
  if (param_2 == 0) {
    lVar12 = unaff_x20 + 0x40;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar12 == 0) {
      return 0;
    }
    lVar8 = lVar12;
    _swift_getObjectType();
    _swift_conformsToProtocol();
    if (lVar8 == 0) {
      return 0;
    }
    if (DAT_100adfbd0 != -1) {
      _swift_once(&DAT_100adfbd0,FUN_1005d0614);
    }
    uVar4 = DAT_100b77550;
    lVar17 = lVar12;
    _swift_getObjectType(lVar12);
    _swift_retain(uVar4);
    FUN_1005e1358(lVar12,0,0,uVar4,lVar17,lVar8);
    dVar20 = param_1;
    _swift_release(uVar4);
    if ((param_3 & 1) != 0) {
      if (DAT_100adef08 != -1) {
        _swift_once(&DAT_100adef08,FUN_1002c44b8);
      }
      lVar12 = _TtC8Playback4Song::privateSongMap;
      lVar8 = *(long *)(DAT_100b75e40 + 0x20);
      if (lVar8 == 0) {
        dVar19 = 0.0;
      }
      else {
        lVar18 = *(long *)(lVar8 + _TtC8Playback9Sequencer::song);
        lVar17 = *(long *)(lVar18 + _TtC8Playback4Song::privateSongMap);
        if (lVar17 == 0) {
          lVar11 = 0;
          FUN_100861310();
          _swift_allocObject();
          puVar2 = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined **)(lVar11 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
          dVar20 = 0.0;
          *(undefined8 *)(lVar11 + 0x28) = 0;
          *(undefined8 *)(lVar11 + 0x20) = 0;
          *(undefined8 *)(lVar11 + 0x38) = 0;
          *(undefined8 *)(lVar11 + 0x30) = 0;
          _swift_unknownObjectUnownedInit(lVar11 + 0x10,lVar18);
          _swift_retain(lVar8);
          _swift_retain(puVar2);
          FUN_10085ee38();
          uVar4 = *(undefined8 *)(lVar18 + lVar12);
          *(long *)(lVar18 + lVar12) = lVar11;
          _swift_retain(lVar11);
          _swift_release(uVar4);
          lVar17 = 0;
        }
        else {
          _swift_retain(lVar8);
          lVar11 = lVar17;
        }
        _swift_retain(lVar17);
        FUN_1004f240c();
        lVar12 = 1;
        FUN_100860ea8(1,1);
        lVar17 = 1;
        FUN_10085ca74();
        if (lVar12 < 0) {
          _swift_bridgeObjectRelease();
          dVar21 = 0.0;
        }
        else if (lVar12 < *(long *)(lVar17 + 0x10)) {
          dVar21 = *(double *)(lVar17 + lVar12 * 8 + 0x20);
          _swift_bridgeObjectRelease();
        }
        else {
          _swift_bridgeObjectRelease();
          dVar21 = 0.0;
        }
        _swift_release(lVar8);
        _swift_release(lVar11);
        dVar19 = 0.0;
        if (0.0 < dVar21 - dVar20) {
          dVar19 = dVar21 - dVar20;
        }
      }
      FUN_10025d3c4(param_1,dVar19,unaff_x20,0);
      return 0;
    }
    FUN_10025d0b8(param_1,unaff_x20,0);
    return 0;
  }
  IVar3 = _objc_msgSend(param_2,"cue");
  IVar3 = _objc_msgSend(IVar3,"songSection");
  uVar7 = _objc_msgSend(IVar3,"arrangement");
  if (iVar1 == 0) {
    if (uVar7 == 0) {
      if (IVar5 == 0) {
LAB_10056e940:
        if ((param_3 & 1) == 0) {
          _objc_msgSend(param_2,"storedValue");
          FUN_10025d0b8(unaff_x20,0);
          return 0;
        }
        IVar3 = _objc_msgSend(param_2,"cue");
        if (IVar3 == 0) {
          dVar20 = 0.0;
        }
        else {
          FUN_1008223d4(2,0);
          dVar20 = param_1;
        }
        _objc_msgSend(param_2,"storedValue");
        goto LAB_10056efa8;
      }
    }
    else if (IVar5 != 0) {
      FUN_1002eda7c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar7,IVar5);
      if ((uVar7 & 1) != 0) goto LAB_10056e940;
    }
    if (DAT_100adef08 != -1) {
      _swift_once(&DAT_100adef08,FUN_1002c44b8);
    }
    lVar12 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    lVar8 = *(long *)(DAT_100b75e40 + 0x28);
    if (lVar8 == 0) {
      return 0;
    }
    IVar5 = *(ID *)(lVar8 + _TtC8Playback9Sequencer::song);
    IVar3 = *(ID *)(IVar5 + _TtC8Playback4Song::privateWorkingCopyArrangement);
    _swift_retain(lVar8);
    if ((IVar3 == 0) &&
       (IVar9 = _objc_msgSend(IVar5,"workingCopyArrangementID"), IVar3 = IVar9, IVar9 != 0)) {
      IVar6 = IVar9;
      FUN_10032ee88();
      IVar3 = IVar6;
      FUN_1005e3b94(IVar6,IVar9);
      _swift_bridgeObjectRelease(IVar6);
      if (IVar3 != 0) {
        *(ID *)(IVar5 + lVar12) = IVar3;
      }
    }
    IVar5 = _objc_msgSend(param_2,"cue");
    IVar5 = _objc_msgSend(IVar5,"songSection");
    IVar5 = _objc_msgSend(IVar5,"arrangement");
    if (IVar3 == 0) {
      if (IVar5 != 0) goto LAB_10056ed58;
    }
    else {
      if (IVar5 == 0) {
        _swift_release(lVar8);
        return 0;
      }
      FUN_1002eda7c(0);
      __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(IVar3,IVar5);
      if ((IVar3 & 1) == 0) goto LAB_10056f134;
    }
    lVar12 = unaff_x20 + 0x40;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar12 != 0) {
      lVar17 = lVar12;
      _swift_getObjectType();
      _swift_conformsToProtocol();
      if (lVar17 != 0) {
        if (DAT_100adfbd0 != -1) {
          _swift_once(&DAT_100adfbd0,FUN_1005d0614);
        }
        uVar4 = DAT_100b77550;
        _swift_retain(DAT_100b77550);
        _objc_msgSend(param_2,"storedValue");
        lVar18 = lVar12;
        _swift_getObjectType(lVar12);
        _swift_retain(lVar8);
        FUN_1005e18bc(param_1,lVar12,0,lVar8,0,uVar4,lVar18,lVar17);
        _swift_release(uVar4);
        _swift_release_n(lVar8,2);
        return 0;
      }
    }
    goto LAB_10056f134;
  }
  if (uVar7 == 0) {
    if (IVar5 == 0) {
LAB_10056e710:
      IVar3 = _objc_msgSend(param_2,"cue");
      if (IVar3 == 0) {
        dVar20 = 0.0;
      }
      else {
        FUN_1008223d4(0,1);
        dVar20 = param_1;
      }
      _objc_msgSend(param_2,"storedValue");
LAB_10056efa8:
      FUN_10025d3c4(param_1,dVar20,unaff_x20,param_2);
      return 0;
    }
  }
  else if (IVar5 != 0) {
    FUN_1002eda7c(0);
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar7,IVar5);
    if ((uVar7 & 1) != 0) goto LAB_10056e710;
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  lVar12 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  lVar8 = *(long *)(DAT_100b75e40 + 0x28);
  if (lVar8 == 0) {
    return 0;
  }
  IVar5 = *(ID *)(lVar8 + _TtC8Playback9Sequencer::song);
  IVar3 = *(ID *)(IVar5 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  _swift_retain();
  if ((IVar3 == 0) &&
     (IVar9 = _objc_msgSend(IVar5,"workingCopyArrangementID"), IVar3 = IVar9, IVar9 != 0)) {
    IVar6 = IVar9;
    FUN_10032ee88();
    IVar3 = IVar6;
    FUN_1005e3b94(IVar6,IVar9);
    _swift_bridgeObjectRelease(IVar6);
    if (IVar3 != 0) {
      *(ID *)(IVar5 + lVar12) = IVar3;
    }
  }
  IVar5 = _objc_msgSend(param_2,"cue");
  IVar5 = _objc_msgSend(IVar5,"songSection");
  IVar5 = _objc_msgSend(IVar5,"arrangement");
  if (IVar3 == 0) {
    if (IVar5 != 0) {
LAB_10056ed58:
      _swift_release(lVar8);
      return 0;
    }
  }
  else {
    if (IVar5 == 0) {
      _swift_release(lVar8);
      return 0;
    }
    FUN_1002eda7c(0);
    __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(IVar3,IVar5);
    if ((IVar3 & 1) == 0) {
LAB_10056f134:
      _swift_release(lVar8);
      return 0;
    }
  }
  uVar7 = unaff_x20 + 0x40;
  _swift_unknownObjectWeakLoadStrong();
  if (uVar7 == 0) {
    _swift_release(lVar8);
    return 0;
  }
  uVar10 = uVar7;
  _swift_getObjectType();
  pTVar15 = &TargetProtocolDescriptor_1009aea40;
  FUN_10026e150();
  if (uVar7 == 0) {
    _swift_release(lVar8);
    return 0;
  }
  pTVar16 = pTVar15;
  IVar3 = _objc_msgSend(param_2,"cue");
  if (IVar3 == 0) {
    local_b0 = 0.0;
  }
  else {
    FUN_1008223d4(0,1);
    local_b0 = param_1;
  }
  if (DAT_100adfbd0 != -1) {
    _swift_once(&DAT_100adfbd0,FUN_1005d0614);
  }
  uVar4 = DAT_100b77550;
  _swift_retain();
  _objc_msgSend(param_2,"storedValue");
  dVar20 = param_1;
  _swift_getObjectType();
  (**(code **)&pTVar15[2].NumRequirements)(uVar7,pTVar15);
  if (ABS(dVar20 - param_1) <= 0.001) goto LAB_10056f188;
  uVar13 = uVar7;
  uVar14 = uVar10;
  (**(code **)(uVar10 + 0x68))();
  if (((uint)pTVar16 & 0xff) - 1 < 3) {
LAB_10056f100:
    (**(code **)(uVar10 + 0xb8))(uVar7,uVar10);
    FUN_100033784(uVar13,uVar14,pTVar16);
  }
  else if (((ulong)pTVar16 & 0xff) == 0) {
    if ((uVar13 & 1) != 0) goto LAB_10056f188;
    goto LAB_10056f100;
  }
  (**(code **)(uVar10 + 0xb0))(param_1,param_2,2,1,local_b0,0,uVar7,uVar10);
LAB_10056f188:
  _swift_release(uVar4);
  _swift_release(lVar8);
  return 0;
}

// ==== 10057b154 FUN_10057b154 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10057b154(double param_1,undefined8 param_2,long param_3,long param_4,ulong param_5,
                undefined1 param_6,byte param_7,undefined8 param_8,undefined8 param_9)

{
  long *plVar1;
  char cVar2;
  long lVar3;
  ID IVar4;
  undefined *puVar5;
  ID IVar6;
  long unaff_x20;
  double dVar7;
  double dVar8;
  
  dVar7 = param_1;
  _swift_getObjectType();
  *(undefined8 *)(unaff_x20 + _TtC8Playback18TimelineMarkerView::horizontalOffset) = 0;
  lVar3 = unaff_x20 + _TtC8Playback18TimelineMarkerView::delegate;
  *(undefined8 *)(lVar3 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar3,0);
  plVar1 = (long *)(unaff_x20 + _TtC8Playback18TimelineMarkerView::markerType);
  *plVar1 = param_3;
  plVar1[1] = param_4;
  *(char *)(plVar1 + 2) = (char)param_5;
  *(undefined8 *)(unaff_x20 + _TtC8Playback18TimelineMarkerView::collectionViewLeftInset) = param_2;
  *(undefined1 *)(unaff_x20 + _TtC8Playback18TimelineMarkerView::isLoopingDuplicate) = param_6;
  *(byte *)(unaff_x20 + _TtC8Playback18TimelineMarkerView::enabledState) = param_7 & 1;
  *(undefined8 *)(lVar3 + 8) = param_9;
  _swift_unknownObjectWeakAssign();
  dVar8 = param_1;
  if ((param_5 & 0xff) == 0) {
    IVar4 = *(ID *)(param_3 + 0x10);
    _swift_retain(param_3);
    IVar4 = _objc_msgSend(IVar4,"transitionBeats");
    if (0 < (int)IVar4) {
      FUN_1008223d4(0,1);
      cVar2 = '\0';
      FUN_10009483c();
      dVar8 = param_1 * 0.5 + dVar7 * *(double *)(&DAT_10093f788 + (long)cVar2 * 8);
    }
  }
  else {
    FUN_100239d00(param_3,param_4,param_5);
  }
  IVar4 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff80,"initWithFrame:",0,0,dVar8,
                              param_1);
  puVar5 = &_OBJC_CLASS___UIColor;
  _swift_getInitializedObjCClass();
  IVar6 = _objc_msgSend((ID)puVar5,"clearColor");
  _objc_msgSend(IVar4,"setBackgroundColor:",IVar6);
  puVar5 = &_OBJC_CLASS___UITapGestureRecognizer;
  _objc_allocWithZone();
  IVar6 = _objc_msgSend((ID)puVar5,"initWithTarget:action:",IVar4,"markerViewTapped:");
  _objc_msgSend(IVar4,"addGestureRecognizer:",IVar6);
  _swift_unknownObjectRelease(param_8);
  FUN_100239d24(param_3,param_4,param_5);
  return IVar4;
}

// ==== 10057b3bc FUN_10057b3bc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_10057b3bc(double param_1,undefined8 param_2,double param_3,double param_4,ID param_5,
                  undefined8 param_6,byte param_7)

{
  long lVar1;
  long lVar2;
  undefined *puVar3;
  ID IVar4;
  long lVar5;
  long lVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double local_b0;
  undefined8 local_a8;
  
  lVar1 = 0;
  __s12CoreGraphics14CGPathFillRuleOMa();
  lVar6 = *(long *)(lVar1 + -8);
  lVar5 = (long)&local_b0 - (*(long *)(lVar6 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar2 = lVar1;
  _UIGraphicsGetCurrentContext();
  if (lVar2 != 0) {
    if (param_7 < 2) {
      if (param_7 == 0) {
        _swift_retain(param_5);
        dVar9 = param_1;
        _CGRectGetHeight(param_1,param_2,param_3,param_4);
        dVar10 = dVar9 * 0.56;
        dVar9 = dVar9 * 0.5 - dVar10 * 0.5;
        _CGContextBeginPath(lVar2);
        local_b0 = dVar9;
        _CGContextAddEllipseInRect(dVar9,0,dVar10,dVar10,lVar2);
        _CGContextClosePath(lVar2);
        puVar3 = &_OBJC_CLASS___UIColor;
        _objc_allocWithZone();
        IVar4 = _objc_msgSend((ID)puVar3,"initWithRed:green:blue:alpha:",0x3fd0d0d0d0d0d0d1,
                              0x3fe5151515151515,0x3fdb1b1b1b1b1b1b,0x3ff0000000000000);
        IVar4 = _objc_msgSend(IVar4,"CGColor");
        _CGContextSetFillColorWithColor(lVar2,IVar4);
        (**(code **)(lVar6 + 0x68))
                  (lVar5,*(undefined4 *)
                          PTR___s12CoreGraphics14CGPathFillRuleO7windingyA2CmFWC_100a1e320,lVar1);
        __sSo12CGContextRefa12CoreGraphicsE8fillPath5usingyAC14CGPathFillRuleO_tF(lVar5);
        (**(code **)(lVar6 + 8))(lVar5,lVar1);
        IVar4 = _objc_msgSend(*(ID *)(param_5 + 0x10),"transitionBeats");
        if (0 < (int)IVar4) {
          puVar3 = &_OBJC_CLASS___UIColor;
          _objc_allocWithZone();
          IVar4 = _objc_msgSend((ID)puVar3,"initWithRed:green:blue:alpha:",0x3fd0d0d0d0d0d0d1,
                                0x3fe5151515151515,0x3fdb1b1b1b1b1b1b,0x3ff0000000000000);
          IVar4 = _objc_msgSend(IVar4,"CGColor");
          _CGContextSetStrokeColorWithColor(lVar2,IVar4);
          _CGContextSetLineWidth(0x3ff8000000000000,lVar2);
          dVar9 = local_b0;
          dVar12 = local_b0;
          _CGRectGetMidX(local_b0,0,dVar10,dVar10);
          dVar7 = dVar9;
          _CGRectGetMidY(dVar9,0,dVar10,dVar10);
          __sSo12CGContextRefa12CoreGraphicsE4move2toySo7CGPointV_tF(dVar12,dVar7);
          _CGRectGetMaxX(param_1,param_2,param_3,param_4);
          _CGRectGetMidY(dVar9,0,dVar10,dVar10);
          __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(param_1,dVar9);
          _CGContextDrawPath(lVar2,2);
        }
        FUN_100239d24(param_5,param_6,0);
        return;
      }
      dVar9 = param_1;
      _CGRectGetWidth(param_1,param_2,param_3,param_4);
      dVar9 = dVar9 * 0.72;
      dVar10 = param_1;
      _CGRectGetHeight(param_1,param_2,param_3,param_4);
      dVar10 = dVar10 * 0.36;
      dVar12 = param_1;
      _CGRectGetWidth(param_1,param_2,param_3,param_4);
      dVar11 = dVar12 * 0.5 - dVar9 * 0.5;
      dVar12 = param_1;
      local_a8 = param_2;
      _CGRectGetHeight(param_1,param_2,param_3,param_4);
      dVar12 = dVar12 - dVar10;
      _CGContextBeginPath(lVar2);
      dVar7 = dVar11;
      _CGRectGetMinX(dVar11,dVar12,dVar9,dVar10);
      dVar8 = dVar11;
      _CGRectGetMaxY(dVar11,dVar12,dVar9,dVar10);
      __sSo12CGContextRefa12CoreGraphicsE4move2toySo7CGPointV_tF(dVar7,dVar8);
      dVar7 = dVar11;
      _CGRectGetMaxX(dVar11,dVar12,dVar9,dVar10);
      dVar8 = dVar11;
      _CGRectGetMaxY(dVar11,dVar12,dVar9,dVar10);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(dVar7,dVar8);
      _CGRectGetMaxX(param_1,local_a8,param_3,param_4);
      _CGRectGetMinY(dVar11,dVar12,dVar9,dVar10);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(param_1 * 0.5,dVar11);
      _CGContextClosePath(lVar2);
      FUN_10057a2ec(param_5,param_6,1);
      IVar4 = _objc_msgSend(param_5,"CGColor");
    }
    else if (param_7 == 2) {
      _CGContextBeginPath(lVar2);
      dVar9 = param_1;
      _CGRectGetMinX(param_1,param_2,param_3,param_4);
      dVar10 = param_1;
      _CGRectGetMaxY(param_1,param_2,param_3,param_4);
      __sSo12CGContextRefa12CoreGraphicsE4move2toySo7CGPointV_tF(dVar9,dVar10 * 0.75);
      dVar9 = param_1;
      _CGRectGetMaxX(param_1,param_2,param_3,param_4);
      dVar10 = param_1;
      _CGRectGetMaxY(param_1,param_2,param_3,param_4);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(dVar9,dVar10 * 0.75);
      dVar9 = param_1;
      _CGRectGetMaxX(param_1,param_2,param_3,param_4);
      _CGRectGetMaxY(param_1,param_2,param_3,param_4);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(dVar9 * 0.5,param_1 * 0.25);
      _CGContextClosePath(lVar2);
      IVar4 = _objc_msgSend(param_5,"CGColor");
    }
    else {
      dVar10 = param_3 * 0.64 * 0.5;
      _CGRectGetMaxX(param_1,param_2,param_3,param_4);
      param_1 = param_1 * 0.5;
      dVar9 = param_4 * 0.64 * 0.5;
      _CGContextBeginPath(lVar2);
      __sSo12CGContextRefa12CoreGraphicsE4move2toySo7CGPointV_tF(param_1,0);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(dVar10 + param_1,dVar9);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(param_1,param_4 * 0.64);
      __sSo12CGContextRefa12CoreGraphicsE7addLine2toySo7CGPointV_tF(param_1 - dVar10,dVar9);
      _CGContextClosePath(lVar2);
      puVar3 = &_OBJC_CLASS___UIColor;
      _objc_allocWithZone();
      IVar4 = _objc_msgSend((ID)puVar3,"initWithRed:green:blue:alpha:",0x3fd0d0d0d0d0d0d1,
                            0x3fe5151515151515,0x3fdb1b1b1b1b1b1b,0x3ff0000000000000);
      IVar4 = _objc_msgSend(IVar4,"CGColor");
    }
    _CGContextSetFillColorWithColor(lVar2,IVar4);
    (**(code **)(lVar6 + 0x68))
              (lVar5,*(undefined4 *)PTR___s12CoreGraphics14CGPathFillRuleO7windingyA2CmFWC_100a1e320
               ,lVar1);
    __sSo12CGContextRefa12CoreGraphicsE8fillPath5usingyAC14CGPathFillRuleO_tF(lVar5);
    (**(code **)(lVar6 + 8))(lVar5,lVar1);
  }
  return;
}

// ==== 100589064 FUN_100589064 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_100589064(void)

{
  ulong *puVar1;
  ID *pIVar2;
  ulong uVar3;
  int iVar4;
  undefined *puVar5;
  ID IVar6;
  undefined8 uVar7;
  undefined1 *puVar8;
  class_t *pcVar9;
  class_t *self;
  class_t *self_00;
  ID self_01;
  ID IVar10;
  ulong self_02;
  undefined8 uVar11;
  char *pcVar12;
  undefined8 *puVar13;
  ID unaff_x20;
  long lVar14;
  long lVar15;
  long lVar16;
  ulong local_e0;
  ulong uStack_d8;
  ID local_d0;
  ulong local_c8;
  objc_super local_c0;
  objc_super local_b0;
  
  IVar10 = unaff_x20;
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffff80,"viewDidLoad");
  puVar1 = (ulong *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::mode);
  uVar3 = *puVar1;
  uStack_d8 = puVar1[1];
  local_e0 = puVar1[2];
  puVar5 = &_OBJC_CLASS___NSBundle;
  _swift_getInitializedObjCClass();
  IVar6 = _objc_msgSend((ID)puVar5,"mainBundle");
  if ((long)uVar3 < 0) {
    uVar7 = 0x7475412074696445;
    uVar11 = 0xef6e6f6974616d6f;
  }
  else {
    uVar7 = 0x6f74754120646441;
    uVar11 = 0xee006e6f6974616d;
  }
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (uVar7,uVar11,0,0,IVar6,0,0xe000000000000000,0,0xe000000000000000);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar11);
  _swift_bridgeObjectRelease(uVar11);
  _objc_msgSend(unaff_x20,"setTitle:",uVar7);
  if (DAT_100adf290 != -1) {
    _swift_once(&DAT_100adf290,FUN_10052c998);
  }
  uVar11 = DAT_100b76408;
  uVar7 = DAT_100b76400;
  local_c8 = uVar3;
  _swift_bridgeObjectRetain(DAT_100b76408);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar11);
  _swift_bridgeObjectRelease(uVar11);
  if (IVar10 == 0) {
    lVar16 = 0;
  }
  else {
    puVar8 = &stack0xffffffffffffff60;
    FUN_100023444(puVar8,IVar10);
    lVar14 = *(long *)(IVar10 - 8);
    lVar15 = (long)&local_e0 - (*(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0);
    (**(code **)(lVar14 + 0x10))(lVar15,puVar8,IVar10);
    lVar16 = lVar15;
    __ss27_bridgeAnythingToObjectiveCyyXlxlF(lVar15,IVar10);
    (**(code **)(lVar14 + 8))(lVar15,IVar10);
    FUN_100023468(&stack0xffffffffffffff60);
  }
  pcVar9 = (class_t *)0x0;
  FUN_1007711fc();
  self = pcVar9;
  _swift_getObjCClassFromMetadata();
  self_00 = self;
  _objc_allocWithZone();
  IVar6 = _objc_msgSend((ID)self_00,"initWithTitle:style:target:action:",uVar7,2,lVar16,
                        "cancelBarButtonTapped:");
  _swift_unknownObjectRelease(lVar16);
  self_01 = _objc_msgSend(unaff_x20,"navigationItem");
  local_d0 = IVar6;
  _objc_msgSend(self_01,"setLeftBarButtonItem:",IVar6);
  if ((long)local_c8 < 0) {
    if (DAT_100adfa18 != -1) {
      _swift_once(&DAT_100adfa18,FUN_100530890);
    }
    puVar13 = &DAT_100b77310;
  }
  else {
    if (DAT_100adf208 != -1) {
      _swift_once(&DAT_100adf208,FUN_10052c5a0);
    }
    puVar13 = &DAT_100b762f0;
  }
  uVar7 = *puVar13;
  uVar11 = puVar13[1];
  _swift_bridgeObjectRetain(uVar11);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar7,uVar11);
  _swift_bridgeObjectRelease(uVar11);
  if (IVar10 == 0) {
    lVar16 = 0;
  }
  else {
    puVar8 = &stack0xffffffffffffff60;
    FUN_100023444(puVar8,IVar10);
    lVar14 = *(long *)(IVar10 - 8);
    lVar15 = (long)&local_e0 - (*(long *)(lVar14 + 0x40) + 0xfU & 0xfffffffffffffff0);
    (**(code **)(lVar14 + 0x10))(lVar15,puVar8,IVar10);
    lVar16 = lVar15;
    __ss27_bridgeAnythingToObjectiveCyyXlxlF(lVar15,IVar10);
    (**(code **)(lVar14 + 8))(lVar15,IVar10);
    FUN_100023468(&stack0xffffffffffffff60);
  }
  _objc_allocWithZone();
  IVar10 = _objc_msgSend((ID)self,"initWithTitle:style:target:action:",uVar7,2,lVar16,
                         "updateBarButtonTapped:");
  _swift_unknownObjectRelease(lVar16);
  local_b0.receiver = IVar10;
  local_b0.super_class = pcVar9;
  _objc_msgSendSuper2(&local_b0,"setEnabled:",0);
  iVar4 = 2;
  FUN_1008c26ac(2,0x1a,0,0);
  if (iVar4 != 0) {
    local_c0.receiver = IVar10;
    local_c0.super_class = pcVar9;
    IVar6 = _objc_msgSendSuper2(&local_c0,"isEnabled");
    uVar7 = 0x3ff0000000000000;
    if ((int)IVar6 == 0) {
      uVar7 = 0x3fd999999999999a;
    }
    puVar5 = &_OBJC_CLASS___UIColor;
    _swift_getInitializedObjCClass();
    IVar6 = _objc_msgSend((ID)puVar5,"systemBlueColor");
    IVar6 = _objc_msgSend(IVar6,"colorWithAlphaComponent:",uVar7);
    _objc_msgSend(IVar10,"setTintColor:",IVar6);
  }
  IVar6 = _objc_msgSend(unaff_x20,"navigationItem");
  _objc_msgSend(IVar6,"setRightBarButtonItem:",IVar10);
  IVar10 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar10 != 0) {
    if (DAT_100adfa80 != -1) {
      _swift_once(&DAT_100adfa80,FUN_1005477e4);
    }
    uVar11 = DAT_100b773c0;
    uVar7 = 0xd00000000000001b;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd00000000000001b,0x80000001008e2d20);
    _objc_msgSend(IVar10,"registerNib:forCellReuseIdentifier:",uVar11,uVar7);
  }
  IVar10 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar10 != 0) {
    FUN_1002bec84(0);
    __sSo11UITableViewC8ReusableE8register8cellTypeyxm_tSo0aB4CellCRbzAC11NibLoadableRzA2CRzlF();
  }
  IVar10 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar10 != 0) {
    if (DAT_100adfc88 != -1) {
      _swift_once(&DAT_100adfc88,FUN_1006f9b98);
    }
    uVar11 = DAT_100b77808;
    uVar7 = 0xd000000000000020;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000020,0x80000001008f0c40);
    _objc_msgSend(IVar10,"registerNib:forCellReuseIdentifier:",uVar11,uVar7);
  }
  IVar10 = _objc_msgSend(unaff_x20,"tableView");
  if (IVar10 != 0) {
    uVar7 = 0;
    FUN_1000a4d04(0);
    _swift_getObjCClassFromMetadata();
    uVar11 = 0xd000000000000019;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000019,0x80000001008d0540);
    _objc_msgSend(IVar10,"registerClass:forCellReuseIdentifier:",uVar7,uVar11);
  }
  uVar3 = local_c8;
  if ((long)local_c8 < 0) {
    self_02 = local_c8 & 0x7fffffffffffffff;
    pcVar12 = "name";
    IVar10 = _objc_msgSend(self_02,"name");
    if (IVar10 == 0) {
      IVar10 = 0;
      pcVar12 = (char *)0xe000000000000000;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
    pIVar2 = (ID *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
    IVar6 = pIVar2[1];
    *pIVar2 = IVar10;
    pIVar2[1] = (ID)pcVar12;
    _swift_bridgeObjectRelease(IVar6);
    pcVar12 = "details";
    IVar10 = _objc_msgSend(self_02,"details");
    if (IVar10 == 0) {
      IVar10 = 0;
      pcVar12 = (char *)0xe000000000000000;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
    pIVar2 = (ID *)(unaff_x20 +
                   _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
    IVar6 = pIVar2[1];
    *pIVar2 = IVar10;
    pIVar2[1] = (ID)pcVar12;
    _swift_bridgeObjectRelease(IVar6);
    IVar10 = _objc_msgSend(self_02,"transitionBeats");
    FUN_10058bff0(uVar3,uStack_d8,local_e0);
    *(short *)(unaff_x20 +
              _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) =
         (short)IVar10;
  }
  FUN_100589880();
  return 0;
}

// ==== 100589880 FUN_100589880 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ulong FUN_100589880(void)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  char *pcVar4;
  ulong self;
  ulong uVar5;
  ID IVar6;
  char *pcVar7;
  ulong uVar8;
  ID unaff_x20;
  
  puVar1 = (ulong *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::mode);
  uVar8 = *puVar1;
  if (-1 < (long)uVar8) goto LAB_100589a5c;
  uVar2 = puVar1[1];
  uVar3 = puVar1[2];
  self = uVar8 & 0x7fffffffffffffff;
  pcVar7 = "name";
  uVar5 = _objc_msgSend(self,"name");
  if ((uVar5 != 0) &&
     (__sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(),
     pcVar7 != (char *)0x0)) {
    IVar6 = *(ID *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
    pcVar4 = (char *)((ID *)(unaff_x20 +
                            _TtC8Playback36AutomationEditingTableViewController::stagedName))[1];
    if (uVar5 == IVar6 && pcVar7 == pcVar4) {
      _swift_bridgeObjectRelease(pcVar7);
    }
    else {
      __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                (uVar5,pcVar7,IVar6,pcVar4,0);
      _swift_bridgeObjectRelease(pcVar7);
      if ((uVar5 & 1) == 0) goto LAB_100589a4c;
    }
    pcVar7 = "details";
    uVar5 = _objc_msgSend(self,"details");
    if ((uVar5 != 0) &&
       (__sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(),
       pcVar7 != (char *)0x0)) {
      IVar6 = *(ID *)(unaff_x20 +
                     _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
      pcVar4 = (char *)((ID *)(unaff_x20 +
                              _TtC8Playback36AutomationEditingTableViewController::stagedDescription
                              ))[1];
      if (uVar5 == IVar6 && pcVar7 == pcVar4) {
        _swift_bridgeObjectRelease(pcVar7);
      }
      else {
        __ss27_stringCompareWithSmolCheck__9expectingSbs11_StringGutsV_ADs01_G16ComparisonResultOtF
                  (uVar5,pcVar7,IVar6,pcVar4,0);
        _swift_bridgeObjectRelease(pcVar7);
        if ((uVar5 & 1) == 0) goto LAB_100589a4c;
      }
      IVar6 = _objc_msgSend(self,"transitionBeats");
      if ((uint)*(ushort *)
                 (unaff_x20 +
                 _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) ==
          ((uint)IVar6 & 0xffff)) {
        IVar6 = _objc_msgSend(unaff_x20,"navigationItem");
        IVar6 = _objc_msgSend(IVar6,"rightBarButtonItem");
        if (IVar6 != 0) {
          _objc_msgSend(IVar6,"setEnabled:",0);
          FUN_10058bff0(uVar8,uVar2,uVar3);
          return 0;
        }
        FUN_10058bff0(uVar8,uVar2,uVar3);
        return uVar8;
      }
    }
  }
LAB_100589a4c:
  FUN_10058bff0(uVar8,uVar2,uVar3);
LAB_100589a5c:
  IVar6 = _objc_msgSend(unaff_x20,"navigationItem");
  IVar6 = _objc_msgSend(IVar6,"rightBarButtonItem");
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setEnabled:",1);
    return 0;
  }
  return 0;
}

// ==== 100589c90 FUN_100589c90 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_100589c90(long param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined2 uVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  undefined *puVar10;
  undefined *puVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 auStack_a0 [2];
  undefined *local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined1 auStack_78 [24];
  
  lVar7 = 0;
  __s10Foundation12CharacterSetVMa();
  lVar13 = *(long *)(lVar7 + -8);
  lVar6 = -(*(long *)(lVar13 + 0x40) + 0xfU & 0xfffffffffffffff0);
  uVar12 = (long)&local_90 + lVar6;
  _swift_beginAccess(param_1 + 0x10,auStack_78,0,0);
  param_1 = param_1 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (param_1 != 0) {
    puVar1 = (undefined8 *)
             (param_1 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
    local_88 = *puVar1;
    uVar2 = puVar1[1];
    uVar8 = uVar2;
    uStack_80 = uVar2;
    _swift_bridgeObjectRetain(uVar2);
    __s10Foundation12CharacterSetV22whitespacesAndNewlinesACvgZ(uVar12);
    FUN_10003bed0();
    uVar9 = uVar12;
    puVar11 = PTR___sSSN_100a1dce0;
    __sSy10FoundationE18trimmingCharacters2inSSAA12CharacterSetV_tF
              (uVar12,PTR___sSSN_100a1dce0,uVar8);
    (**(code **)(lVar13 + 8))(uVar12,lVar7);
    _swift_bridgeObjectRelease(uVar2);
    puVar10 = puVar11;
    _swift_bridgeObjectRelease();
    uVar12 = uVar9 & 0xffffffffffff;
    if (((ulong)puVar11 & 0x2000000000000000) != 0) {
      uVar12 = (ulong)puVar11 >> 0x38 & 0xf;
    }
    if (uVar12 == 0) {
      FUN_10058c334();
      local_90 = puVar10;
    }
    else {
      local_90 = (undefined *)*puVar1;
      lVar7 = puVar1[1];
      _swift_bridgeObjectRetain(lVar7);
    }
    lVar13 = param_1 + _TtC8Playback36AutomationEditingTableViewController::delegate;
    _swift_unknownObjectUnownedLoadStrong(lVar13);
    puVar1 = (undefined8 *)(param_1 + _TtC8Playback36AutomationEditingTableViewController::mode);
    uVar2 = *puVar1;
    uVar3 = puVar1[1];
    uVar14 = puVar1[2];
    uVar8 = *(undefined8 *)
             (param_1 + _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
    uVar4 = ((undefined8 *)
            (param_1 + _TtC8Playback36AutomationEditingTableViewController::stagedDescription))[1];
    uVar15 = *(undefined8 *)
              (param_1 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems)
    ;
    uVar5 = *(undefined2 *)
             (param_1 + _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats);
    FUN_10058bfd0(uVar2,uVar3,uVar14);
    _swift_bridgeObjectRetain(uVar15);
    _swift_bridgeObjectRetain(uVar4);
    *(undefined8 *)((long)auStack_a0 + lVar6) = uVar15;
    FUN_10087e150(uVar2,uVar3,uVar14,local_90,lVar7,uVar5,uVar8,uVar4);
    _swift_bridgeObjectRelease(uVar4);
    _swift_bridgeObjectRelease(uVar15);
    FUN_10058bff0(uVar2,uVar3,uVar14);
    _swift_bridgeObjectRelease(lVar7);
    _swift_unknownObjectRelease(lVar13);
  }
  return;
}

// ==== 10058af18 FUN_10058af18 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined * FUN_10058af18(ID param_1)

{
  undefined8 *puVar1;
  ID *pIVar2;
  undefined8 uVar3;
  undefined1 uVar4;
  undefined *puVar5;
  long lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  undefined *puVar9;
  void *pvVar10;
  undefined *puVar11;
  ID IVar12;
  ID IVar13;
  char *pcVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  ID unaff_x20;
  undefined *puVar19;
  undefined *local_90;
  char *local_88;
  code *local_80;
  undefined *puStack_78;
  code *local_70;
  undefined *local_68;
  
  puVar1 = (undefined8 *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::mode);
  puVar11 = (undefined *)*puVar1;
  uVar3 = puVar1[1];
  uVar18 = puVar1[2];
  puVar7 = &DAT_100b067c0;
  FUN_100021774();
  _swift_initStaticObject();
  puVar19 = puVar7;
  _swift_bridgeObjectRetain();
  __s10Foundation9IndexPathV5UIKitE7sectionSivg();
  if (((long)puVar19 < 0) || (*(long *)(puVar7 + 0x10) <= (long)puVar19)) {
LAB_10058b0a4:
    _swift_bridgeObjectRelease(puVar7);
    return puVar7;
  }
  uVar4 = (puVar7 + (long)puVar19)[0x20];
  _swift_bridgeObjectRelease(puVar7);
  puVar7 = puVar11;
  FUN_1005889d4(puVar11,uVar3,uVar18,
                *(undefined8 *)
                 (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::copyCue),uVar4);
  puVar19 = puVar7;
  __s10Foundation9IndexPathV5UIKitE3rowSivg();
  if (((long)puVar19 < 0) || (*(long *)(puVar7 + 0x10) <= (long)puVar19)) goto LAB_10058b0a4;
  puVar19 = *(undefined **)(puVar7 + (long)puVar19 * 8 + 0x20);
  FUN_10058c274(puVar19);
  _swift_bridgeObjectRelease(puVar7);
  if ((long)puVar19 < 2) {
    if (puVar19 == (undefined *)0x0) {
      if (-1 < (long)puVar11) {
        return puVar7;
      }
      lVar6 = unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::delegate;
      _swift_unknownObjectUnownedLoadStrong(lVar6);
      _swift_unknownObjectWeakAssign
                (lVar6 + _TtC8Playback22WaveformViewController::automationCopyCue,
                 (ulong)puVar11 & 0x7fffffffffffffff);
      FUN_10058bfd0(puVar11,uVar3,uVar18);
      _objc_msgSend(unaff_x20,"dismissViewControllerAnimated:completion:",1,0);
      _swift_unknownObjectRelease(lVar6);
      FUN_10058bff0(puVar11,uVar3,uVar18);
      goto LAB_10058b914;
    }
    if (puVar19 == (undefined *)0x1) goto LAB_10058b0d0;
  }
  else {
    if (puVar19 == (undefined *)0x2) {
      puVar7 = puVar11;
      FUN_10058bfd0(puVar11,uVar3,uVar18);
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      IVar12 = _objc_msgSend(param_1,"cellForRowAtIndexPath:",puVar7);
      if (IVar12 != 0) {
        uVar17 = 0;
        FUN_1002bec84(0);
        _swift_dynamicCastClass(IVar12,uVar17);
        if (IVar12 != 0) {
          FUN_1002bdf08();
          __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
          IVar12 = _objc_msgSend(param_1,"cellForRowAtIndexPath:",IVar12);
          if (IVar12 != 0) {
            puVar7 = &DAT_100a53520;
            _swift_allocObject(&DAT_100a53520,0x18,7);
            *(ID *)(puVar7 + 0x10) = IVar12;
            puVar5 = &_OBJC_CLASS___UIView;
            _swift_getInitializedObjCClass();
            local_70 = FUN_1000b8be4;
            local_90 = PTR___NSConcreteStackBlock_100a1d8e8;
            local_88 = (char *)0x42000000;
            local_80 = FUN_10056b3d8;
            puStack_78 = &DAT_100a53538;
            local_68 = puVar7;
            pvVar10 = __Block_copy(&local_90);
            puVar19 = local_68;
            _swift_retain(puVar7);
            _swift_release(puVar19);
            _objc_msgSend((ID)puVar5,"animateWithDuration:animations:completion:",0x3fd3333333333333
                          ,pvVar10,0);
            __Block_release(pvVar10);
            _objc_msgSend(param_1,"beginUpdates");
            _objc_msgSend(param_1,"endUpdates");
            _swift_release(puVar7);
            FUN_10058bff0(puVar11,uVar3,uVar18);
            return (undefined *)0x0;
          }
        }
        FUN_10058bff0(puVar11,uVar3,uVar18);
        return (undefined *)0x0;
      }
      goto LAB_10058b914;
    }
    if (puVar19 == (undefined *)0x3) {
LAB_10058b0d0:
      FUN_10058c284(puVar19);
      return puVar19;
    }
    if (puVar19 == (undefined *)0x4) {
      puVar7 = puVar11;
      FUN_10058bfd0(puVar11,uVar3,uVar18);
      __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
      _objc_msgSend(param_1,"deselectRowAtIndexPath:animated:",puVar7,1);
      IVar12 = unaff_x20;
      FUN_100837390();
      if (IVar12 != 0) {
        _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar12,1,0);
      }
      goto LAB_10058b914;
    }
  }
  if ((long)puVar11 < 0) {
    puVar7 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    FUN_10058c274(puVar19);
    FUN_10058c274(puVar19);
    FUN_10058bfd0(puVar11,uVar3,uVar18);
    IVar12 = _objc_msgSend((ID)puVar7,"mainBundle");
    uVar17 = 0x746972777265764f;
    uVar15 = 0xea00000000003f65;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0x746972777265764f,0xea00000000003f65,0,0,IVar12,0,0xe000000000000000,0,
               0xe000000000000000);
    IVar12 = _objc_msgSend((ID)puVar7,"mainBundle");
    uVar16 = 0x8000000100901560;
    uVar8 = 0xd000000000000022;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0xd000000000000022,0x8000000100901560,0,0,IVar12,0,0xe000000000000000,0,
               0xe000000000000000);
    IVar12 = 0;
    FUN_100497ca4();
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar17,uVar15);
    _swift_bridgeObjectRelease(uVar15);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar8,uVar16);
    _swift_bridgeObjectRelease(uVar16);
    _swift_getObjCClassFromMetadata();
    IVar12 = _objc_msgSend(IVar12,"alertControllerWithTitle:message:preferredStyle:",uVar17,uVar8,1)
    ;
    if (DAT_100adf290 != -1) {
      _swift_once(&DAT_100adf290,FUN_10052c998);
    }
    uVar8 = DAT_100b76408;
    uVar17 = DAT_100b76400;
    _swift_bridgeObjectRetain(DAT_100b76408);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar17,uVar8);
    _swift_bridgeObjectRelease(uVar8);
    puVar7 = &_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    IVar13 = _objc_msgSend((ID)puVar7,"actionWithTitle:style:handler:",uVar17,1,0);
    _objc_msgSend(IVar12,"addAction:",IVar13);
    if (DAT_100adf728 != -1) {
      _swift_once(&DAT_100adf728,FUN_10052ed24);
    }
    uVar8 = DAT_100b76d38;
    uVar17 = DAT_100b76d30;
    puVar5 = &DAT_100a53570;
    _swift_allocObject(&DAT_100a53570,0x18,7);
    _swift_unknownObjectWeakInit(puVar5 + 0x10);
    puVar9 = &DAT_100a53598;
    _swift_allocObject(&DAT_100a53598,0x28,7);
    *(undefined **)(puVar9 + 0x10) = puVar5;
    *(undefined **)(puVar9 + 0x18) = puVar19;
    *(ID *)(puVar9 + 0x20) = param_1;
    FUN_10058c274(puVar19);
    _swift_bridgeObjectRetain(uVar8);
    _swift_retain(puVar5);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar17,uVar8);
    _swift_bridgeObjectRelease(uVar8);
    local_70 = FUN_10058c328;
    local_90 = PTR___NSConcreteStackBlock_100a1d8e8;
    local_88 = (char *)0x42000000;
    local_80 = FUN_100029ac0;
    puStack_78 = &DAT_100a535b0;
    local_68 = puVar9;
    pvVar10 = __Block_copy(&local_90);
    _swift_release(local_68);
    IVar13 = _objc_msgSend((ID)puVar7,"actionWithTitle:style:handler:",uVar17,2,pvVar10);
    __Block_release(pvVar10);
    _swift_release(puVar5);
    _objc_msgSend(IVar12,"addAction:",IVar13);
    _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",IVar12,1,0);
    FUN_10058c284(puVar19);
    FUN_10058c284(puVar19);
    FUN_10058c284(puVar19);
    FUN_10058bff0(puVar11,uVar3,uVar18);
    return puVar11;
  }
  FUN_10058c274(puVar19);
  FUN_10058bfd0(puVar11,uVar3,uVar18);
  pcVar14 = "name";
  puVar7 = (undefined *)_objc_msgSend((ID)puVar19,"name");
  if (puVar7 == (undefined *)0x0) {
    puVar7 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar12 = _objc_msgSend((ID)puVar7,"mainBundle");
    puVar7 = (undefined *)0x6974616d6f747541;
    pcVar14 = (char *)0xee00657563206e6f;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0x6974616d6f747541,0xee00657563206e6f,0,0,IVar12,0,0xe000000000000000,0,
               0xe000000000000000);
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  local_90 = puVar7;
  local_88 = pcVar14;
  _swift_bridgeObjectRetain(pcVar14);
  __sSS6appendyySSF(0x20,0xe100000000000000);
  _swift_bridgeObjectRelease(pcVar14);
  pcVar14 = local_88;
  puVar7 = local_90;
  if (DAT_100adf328 != -1) {
    _swift_once(&DAT_100adf328,FUN_10052ceb4);
  }
  uVar8 = DAT_100b76538;
  uVar17 = DAT_100b76530;
  local_90 = puVar7;
  local_88 = pcVar14;
  _swift_bridgeObjectRetain(pcVar14);
  __sSS6appendyySSF(uVar17,uVar8);
  _swift_bridgeObjectRelease(pcVar14);
  pIVar2 = (ID *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
  IVar12 = pIVar2[1];
  *pIVar2 = (ID)local_90;
  pIVar2[1] = (ID)local_88;
  _swift_bridgeObjectRelease(IVar12);
  IVar12 = _objc_msgSend((ID)puVar19,"transitionBeats");
  *(short *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats)
       = (short)IVar12;
  pcVar14 = "details";
  IVar12 = _objc_msgSend((ID)puVar19,"details");
  if (IVar12 == 0) {
    IVar12 = 0;
    pcVar14 = (char *)0xe000000000000000;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  pIVar2 = (ID *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedDescription
                 );
  IVar13 = pIVar2[1];
  *pIVar2 = IVar12;
  pIVar2[1] = (ID)pcVar14;
  _swift_bridgeObjectRelease();
  FUN_100822b68();
  uVar17 = *(undefined8 *)
            (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems)
  ;
  *(ID *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) =
       IVar13;
  _swift_bridgeObjectRelease(uVar17);
  _objc_msgSend(param_1,"reloadData");
  FUN_10058c284(puVar19);
  FUN_10058c284(puVar19);
LAB_10058b914:
  FUN_10058bff0(puVar11,uVar3,uVar18);
  return puVar11;
}

// ==== 10058b988 FUN_10058b988 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10058b988(undefined8 param_1,long param_2,ID param_3,ID param_4)

{
  ID *pIVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  char *pcVar5;
  ID IVar6;
  undefined8 uVar7;
  ID IVar8;
  undefined1 auStack_c8 [24];
  undefined1 auStack_b0 [24];
  undefined1 auStack_98 [24];
  ID local_80;
  char *pcStack_78;
  undefined1 auStack_68 [24];
  
  _swift_beginAccess(param_2 + 0x10,auStack_68,0,0);
  lVar3 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    pcVar5 = "name";
    local_80 = _objc_msgSend(param_3,"name");
    if (local_80 == 0) {
      local_80 = 0;
      pcVar5 = (char *)0xe000000000000000;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
    pcStack_78 = pcVar5;
    _swift_bridgeObjectRetain(pcVar5);
    __sSS6appendyySSF(0x20,0xe100000000000000);
    _swift_bridgeObjectRelease(pcVar5);
    pcVar5 = pcStack_78;
    IVar6 = local_80;
    if (DAT_100adf328 != -1) {
      _swift_once(&DAT_100adf328,FUN_10052ceb4);
    }
    uVar2 = DAT_100b76538;
    uVar7 = DAT_100b76530;
    local_80 = IVar6;
    pcStack_78 = pcVar5;
    _swift_bridgeObjectRetain(pcVar5);
    __sSS6appendyySSF(uVar7,uVar2);
    _swift_bridgeObjectRelease(pcVar5);
    pIVar1 = (ID *)(lVar3 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
    IVar6 = pIVar1[1];
    *pIVar1 = local_80;
    pIVar1[1] = (ID)pcStack_78;
    _swift_bridgeObjectRelease(IVar6);
  }
  _swift_beginAccess(param_2 + 0x10,&local_80,0,0);
  lVar3 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    IVar6 = _objc_msgSend(param_3,"transitionBeats");
    *(short *)(lVar3 + _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) =
         (short)IVar6;
  }
  _swift_beginAccess(param_2 + 0x10,auStack_98,0,0);
  lVar3 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    pcVar5 = "details";
    IVar6 = _objc_msgSend(param_3,"details");
    if (IVar6 == 0) {
      IVar6 = 0;
      pcVar5 = (char *)0xe000000000000000;
    }
    else {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    }
    pIVar1 = (ID *)(lVar3 + _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
    IVar8 = pIVar1[1];
    *pIVar1 = IVar6;
    pIVar1[1] = (ID)pcVar5;
    _swift_bridgeObjectRelease(IVar8);
  }
  _swift_beginAccess(param_2 + 0x10,auStack_b0,0,0);
  lVar3 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar3 != 0) {
    lVar4 = lVar3;
    FUN_100822b68();
    uVar7 = *(undefined8 *)
             (lVar3 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems);
    *(long *)(lVar3 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) =
         lVar4;
    _swift_bridgeObjectRelease(uVar7);
  }
  _swift_beginAccess(param_2 + 0x10,auStack_c8,0,0);
  param_2 = param_2 + 0x10;
  _swift_unknownObjectWeakLoadStrong();
  if (param_2 != 0) {
    FUN_100589880();
  }
  _objc_msgSend(param_4,"reloadData");
  return;
}

// ==== 10058c1dc FUN_10058c1dc ====
void FUN_10058c1dc(undefined8 param_1,long param_2)

{
  code *pcVar1;
  long unaff_x20;
  
  if (param_2 < -0x8000) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x10058c200);
    (*pcVar1)();
  }
  if (param_2 < 0x8000) {
    *(short *)(unaff_x20 +
              _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) =
         (short)param_2;
    FUN_100589880();
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x10058c204);
  (*pcVar1)();
}

// ==== 10058c578 FUN_10058c578 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10058c578(void)

{
  undefined8 *puVar1;
  code *pcVar2;
  long unaff_x20;
  
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedName);
  *puVar1 = 0;
  puVar1[1] = 0xe000000000000000;
  *(undefined2 *)
   (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) = 0;
  puVar1 = (undefined8 *)
           (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
  *puVar1 = 0;
  puVar1[1] = 0xe000000000000000;
  *(undefined8 *)(unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::copyCue) = 0;
  *(undefined8 *)
   (unaff_x20 + _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) = 0;
  __ss17_assertionFailure__4file4line5flagss5NeverOs12StaticStringV_SSAHSus6UInt32VtF
            ("Fatal error",0xb,2,0xd00000000000001f,0x80000001008d0650,
             "Playback/AutomationEditingTableViewController.swift",0x33,2,0xe2,0);
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(1,0x10058c620);
  (*pcVar2)();
}

// ==== 1005f0ebc FUN_1005f0ebc ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

void FUN_1005f0ebc(double param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  code *pcVar4;
  bool bVar5;
  char cVar6;
  ID self;
  ulong uVar7;
  undefined8 uVar8;
  ulong uVar9;
  long lVar10;
  undefined *self_00;
  ID IVar11;
  ulong uVar12;
  long lVar13;
  ID IVar14;
  ulong uVar15;
  long unaff_x20;
  long lVar16;
  long lVar17;
  ulong uVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  undefined1 auStack_e0 [24];
  long local_c8 [3];
  undefined8 local_b0;
  
  FUN_1005f5160();
  if (DAT_100adfbb8 != -1) {
    _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
  }
  if (*(long *)(DAT_100b77548 + 0x10) != -0x7ffffffffffffff8) {
    return;
  }
  self = unaff_x20 + _TtC8Playback22WaveformViewController::collectionView;
  _swift_unknownObjectWeakLoadStrong();
  if (self == 0) {
    return;
  }
  uVar7 = _objc_msgSend(self,"visibleCells");
  uVar8 = 0;
  FUN_100023404(0,&DAT_100af5488,&PTR__OBJC_CLASS___UICollectionViewCell_100aa3e80);
  __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar7,uVar8);
  if (uVar7 >> 0x3e == 0) {
    uVar9 = *(ulong *)((uVar7 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar9 = uVar7 & 0xffffffffffffff8;
    if ((long)uVar7 < 0) {
      uVar9 = uVar7;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar9 == 0) {
    _swift_bridgeObjectRelease(uVar7);
LAB_1005f1058:
    lVar10 = 0;
LAB_1005f105c:
    _objc_msgSend(self,"frame");
    _CGRectGetMaxY();
    dVar22 = param_1;
    if (lVar10 != 0) goto LAB_1005f1084;
  }
  else {
    if ((uVar7 & 0xc000000000000001) == 0) {
      if (*(long *)((uVar7 & 0xfffffffffffff8) + 0x10) == 0) {
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(1,0x1005f1624);
        (*pcVar4)();
      }
      lVar10 = *(long *)(uVar7 + 0x20);
    }
    else {
      lVar10 = 0;
      FUN_1000cd278(0,uVar7);
    }
    _swift_bridgeObjectRelease(uVar7);
    uVar8 = 0;
    FUN_1000f9af4(0);
    _swift_dynamicCastClass(lVar10,uVar8);
    if (lVar10 == 0) goto LAB_1005f1058;
    IVar14 = lVar10 + _TtC8Playback19WaveformSectionCell::sectionBackgroundView;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar14 == 0) goto LAB_1005f105c;
    _objc_msgSend(IVar14,"frame");
    _CGRectGetHeight(param_1,param_2,param_3,param_4,0);
LAB_1005f1084:
    IVar14 = lVar10 + _TtC8Playback19WaveformSectionCell::sectionBackgroundView;
    dVar22 = param_1;
    _swift_unknownObjectWeakLoadStrong();
    if (IVar14 != 0) {
      _objc_msgSend(IVar14,"frame");
      goto LAB_1005f10c4;
    }
  }
  param_2 = 0;
LAB_1005f10c4:
  uVar7 = *(ulong *)(unaff_x20 + _TtC8Playback22WaveformViewController::automationMarkerViews);
  if (uVar7 >> 0x3e == 0) {
    uVar9 = *(ulong *)((uVar7 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar9 = uVar7 & 0xffffffffffffff8;
    if ((long)uVar7 < 0) {
      uVar9 = uVar7;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar9 == 0) {
    _swift_bridgeObjectRetain(uVar7);
  }
  else {
    _swift_bridgeObjectRetain(uVar7);
    uVar18 = 0;
    do {
      if ((uVar7 & 0xc000000000000001) == 0) {
        if (*(ulong *)((uVar7 & 0xffffffffffffff8) + 0x10) <= uVar18) {
                    /* WARNING: Does not return */
          pcVar4 = (code *)SoftwareBreakpoint(1,0x1005f1570);
          (*pcVar4)();
        }
        uVar12 = *(ID *)(uVar7 + 0x20 + uVar18 * 8);
      }
      else {
        uVar12 = uVar18;
        FUN_1000cd4c0(uVar18,uVar7);
      }
      bVar5 = SCARRY8(uVar18,1);
      uVar18 = uVar18 + 1;
      if (bVar5) {
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(1,0x1005f156c);
        (*pcVar4)();
      }
      plVar2 = (long *)(uVar12 + _TtC8Playback18TimelineMarkerView::markerType);
      if ((char)plVar2[2] == '\0') {
        lVar10 = *plVar2;
        lVar3 = plVar2[1];
        IVar14 = *(ID *)(lVar10 + 0x10);
        _swift_retain(lVar10);
        IVar14 = _objc_msgSend(IVar14,"transitionBeats");
        if ((int)IVar14 == 0) {
          _objc_msgSend(uVar12,"bounds");
          _CGRectGetWidth();
          dVar21 = 0.0;
          dVar20 = dVar22;
        }
        else {
          FUN_1008223d4(0,1);
          cVar6 = '\0';
          FUN_10009483c();
          dVar19 = *(double *)(&DAT_100941b08 + (long)cVar6 * 8);
          dVar20 = dVar22 * dVar19;
          _objc_msgSend(uVar12,"frame");
          _CGRectGetHeight();
          dVar21 = dVar19 * 0.5;
          dVar22 = dVar19;
        }
        _objc_msgSend(uVar12,"frame");
        dVar22 = dVar21 + dVar22;
        IVar14 = 0;
        FUN_1001e2f10();
        _objc_allocWithZone();
        IVar14 = _objc_msgSend(IVar14,"initWithFrame:",dVar22,param_2,dVar20,param_1);
        _objc_msgSend(IVar14,"addTarget:action:forControlEvents:",unaff_x20,
                      "waveformOverlayButtonTouchUpInside:",0x40);
        lVar17 = _TtC8Playback21WaveformOverlayButton::editingMode;
        uVar8 = *(undefined8 *)(IVar14 + _TtC8Playback21WaveformOverlayButton::editingMode);
        *(undefined8 *)(IVar14 + _TtC8Playback21WaveformOverlayButton::editingMode) =
             0x8000000000000008;
        FUN_1000a1b5c(0x8000000000000008);
        FUN_1000a1b5c(0x8000000000000008);
        FUN_100092550(uVar8);
        self_00 = &_OBJC_CLASS___UIColor;
        if (*(long *)(IVar14 + lVar17) == -0x7ffffffffffffff8) {
          _objc_allocWithZone();
          IVar11 = _objc_msgSend((ID)self_00,"initWithRed:green:blue:alpha:",0x3fd0d0d0d0d0d0d1,
                                 0x3fe5151515151515,0x3fdb1b1b1b1b1b1b,0x3ff0000000000000);
          dVar22 = 0.2;
          IVar11 = _objc_msgSend(IVar11,"colorWithAlphaComponent:");
        }
        else {
          _swift_getInitializedObjCClass();
          IVar11 = _objc_msgSend((ID)self_00,"clearColor");
        }
        _objc_msgSend(IVar14,"setBackgroundColor:",IVar11);
        FUN_100092550(0x8000000000000008);
        uVar8 = 0;
        FUN_10021451c();
        lVar17 = _TtC8Playback21WaveformOverlayButton::payload;
        local_c8[0] = lVar10;
        local_b0 = uVar8;
        _swift_beginAccess(IVar14 + _TtC8Playback21WaveformOverlayButton::payload,auStack_e0,0x21,0)
        ;
        _swift_retain(lVar10);
        FUN_1005fab58(local_c8,IVar14 + lVar17);
        _swift_endAccess(auStack_e0);
        uVar12 = _objc_msgSend(self,"subviews");
        uVar8 = 0;
        FUN_100023404(0,&DAT_100af5698,&PTR__OBJC_CLASS___UIView_100aa3dd8);
        __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ(uVar12,uVar8);
        if (uVar12 >> 0x3e == 0) {
          uVar15 = *(ulong *)((uVar12 & 0xfffffffffffff8) + 0x10);
        }
        else {
          uVar15 = uVar12 & 0xffffffffffffff8;
          if ((long)uVar12 < 0) {
            uVar15 = uVar12;
          }
          __ss18_CocoaArrayWrapperV8endIndexSivg();
        }
        if (uVar15 != 0) {
          _swift_bridgeObjectRetain(uVar12);
          lVar17 = 4;
          do {
            lVar16 = lVar17 + -4;
            if ((uVar12 & 0xc000000000000001) == 0) {
              lVar13 = *(long *)(uVar12 + lVar17 * 8);
            }
            else {
              lVar13 = lVar16;
              FUN_1000ccea8(lVar16,uVar12);
            }
            uVar1 = lVar17 - 3;
            if (SCARRY8(lVar16,1)) {
                    /* WARNING: Does not return */
              pcVar4 = (code *)SoftwareBreakpoint(1,0x1005f1568);
              (*pcVar4)();
            }
            uVar8 = 0;
            FUN_100239890(0);
            lVar16 = lVar13;
            _swift_dynamicCastClass(lVar13,uVar8);
            if (lVar16 != 0) {
              _swift_bridgeObjectRelease_n(uVar12,2);
              _objc_msgSend(self,"insertSubview:belowSubview:",IVar14,lVar13);
              FUN_100239d24(lVar10,lVar3,0);
              goto LAB_1005f118c;
            }
            lVar17 = lVar17 + 1;
          } while (uVar1 != uVar15);
          _swift_bridgeObjectRelease(uVar12);
        }
        _swift_bridgeObjectRelease(uVar12);
        _objc_msgSend(self,"addSubview:",IVar14);
        FUN_100239d24(lVar10,lVar3,0);
      }
LAB_1005f118c:
    } while (uVar18 != uVar9);
  }
  FUN_100092550(0x8000000000000008);
  _swift_bridgeObjectRelease(uVar7);
  return;
}

// ==== 1005f1c00 FUN_1005f1c00 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8
FUN_1005f1c00(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 param_5)

{
  long *plVar1;
  undefined8 *puVar2;
  ulong *puVar3;
  undefined8 uVar4;
  char cVar5;
  long lVar6;
  code *pcVar7;
  ulong uVar8;
  class_t *pcVar9;
  class_t *pcVar10;
  ID IVar11;
  undefined *self;
  ID self_00;
  long lVar12;
  ID unaff_x20;
  ID self_01;
  objc_super local_a8;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined1 local_78;
  
  self_01 = *(ID *)(unaff_x20 + _TtC8Playback22WaveformViewController::selectedTimelineMarkerView);
  if (self_01 != 0) {
    IVar11 = self_01;
    FUN_100465034();
    if ((((IVar11 == 0) ||
         (*(long *)(IVar11 + _TtC8Playback18MainViewController::waveformViewController) == 0)) ||
        (lVar12 = *(long *)(*(long *)(IVar11 + _TtC8Playback18MainViewController::
                                               waveformViewController) +
                           _TtC8Playback22WaveformViewController::selectedTimelineMarkerView),
        lVar12 == 0)) ||
       (plVar1 = (long *)(lVar12 + _TtC8Playback18TimelineMarkerView::markerType),
       (char)plVar1[2] != '\0')) {
      return 0;
    }
    uVar8 = *(ulong *)(*plVar1 + 0x10);
    puVar2 = (undefined8 *)(self_01 + _TtC8Playback18TimelineMarkerView::markerType);
    param_5 = *puVar2;
    uVar4 = puVar2[1];
    cVar5 = *(char *)(puVar2 + 2);
    if (cVar5 != '\0') {
      FUN_100239d00(param_5,uVar4,cVar5);
      FUN_100239d24(param_5,uVar4,cVar5);
      return param_5;
    }
    lVar12 = unaff_x20 + _TtC8Playback22WaveformViewController::automationCopyCue;
    _swift_unknownObjectWeakLoadStrong();
    pcVar9 = (class_t *)0x0;
    FUN_100589fc4();
    pcVar10 = pcVar9;
    _objc_allocWithZone();
    puVar2 = (undefined8 *)
             ((long)&pcVar10->isa + _TtC8Playback36AutomationEditingTableViewController::stagedName)
    ;
    *puVar2 = 0;
    puVar2[1] = 0xe000000000000000;
    *(undefined2 *)
     ((long)&pcVar10->isa +
     _TtC8Playback36AutomationEditingTableViewController::stagedTransitionBeats) = 0;
    puVar2 = (undefined8 *)
             ((long)&pcVar10->isa +
             _TtC8Playback36AutomationEditingTableViewController::stagedDescription);
    *puVar2 = 0;
    puVar2[1] = 0xe000000000000000;
    lVar6 = _TtC8Playback36AutomationEditingTableViewController::copyCue;
    *(undefined8 *)
     ((long)&pcVar10->isa + _TtC8Playback36AutomationEditingTableViewController::copyCue) = 0;
    *(undefined8 *)
     ((long)&pcVar10->isa +
     _TtC8Playback36AutomationEditingTableViewController::pastedAutomationItems) = 0;
    puVar3 = (ulong *)((long)&pcVar10->isa +
                      _TtC8Playback36AutomationEditingTableViewController::mode);
    *puVar3 = uVar8 | 0x8000000000000000;
    puVar3[1] = 0;
    puVar3[2] = 0;
    *(undefined ***)
     ((long)&pcVar10->superclass + _TtC8Playback36AutomationEditingTableViewController::delegate) =
         &PTR_PTR_100a6f5e8;
    _swift_unknownObjectUnownedInit();
    *(long *)((long)&pcVar10->isa + lVar6) = lVar12;
    FUN_100239d00(param_5,uVar4,0);
    local_a8.receiver = (ID)pcVar10;
    local_a8.super_class = pcVar9;
    IVar11 = _objc_msgSendSuper2(&local_a8,"initWithStyle:",1);
    self = &_OBJC_CLASS___UINavigationController;
    _objc_allocWithZone();
    self_00 = _objc_msgSend((ID)self,"initWithRootViewController:",IVar11);
    IVar11 = _objc_msgSend(IVar11,"tableView");
    if (IVar11 == 0) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(1,0x1005f1fc8);
      (*pcVar7)();
    }
    _objc_msgSend(IVar11,"contentSize");
    _objc_msgSend(self_00,"setPreferredContentSize:");
    _objc_msgSend(self_01,"bounds");
    local_78 = 0;
    local_98 = param_1;
    uStack_90 = param_2;
    local_88 = param_3;
    uStack_80 = param_4;
    FUN_100430978(0,1,0xc,0,self_01,&local_98,0);
    _objc_msgSend(unaff_x20,"presentViewController:animated:completion:",self_00,1,0);
    FUN_100239d24(param_5,uVar4,0);
  }
  return param_5;
}

// ==== 100641948 FUN_100641948 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_100641948(ulong param_1,uint param_2,uint param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  ID IVar6;
  ulong uVar7;
  undefined *self;
  ID IVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long unaff_x20;
  uint uVar11;
  uint uVar12;
  
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionImageView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    uVar7 = param_1;
    FUN_1005fd008(param_1);
    _objc_msgSend(IVar6,"setImage:",uVar7);
  }
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::titleLabel;
  _swift_unknownObjectWeakLoadStrong();
  uVar11 = (uint)param_1;
  if (IVar6 != 0) {
    uVar12 = uVar11 & 0xff;
    uVar10 = 0xec000000676e6f53;
    uVar1 = 0x206e492079617453;
    if (uVar12 != 4) {
      uVar10 = 0xee00676e6f532074;
      uVar1 = 0x7372694620657543;
    }
    uVar3 = 0xe900000000000065;
    uVar9 = 0x64616673736f7243;
    if (uVar12 != 3) {
      uVar3 = uVar10;
      uVar9 = uVar1;
    }
    uVar10 = 0x6b6e694c6f747541;
    if (uVar12 != 1) {
      uVar10 = 0x70616c7265764f;
    }
    uVar1 = 0xe800000000000000;
    if (uVar12 != 1) {
      uVar1 = 0xe700000000000000;
    }
    uVar2 = 0xed0000676e6f5320;
    uVar4 = 0x7478654e20657543;
    if ((param_1 & 0xff) != 0) {
      uVar2 = uVar1;
      uVar4 = uVar10;
    }
    if (uVar12 < 3) {
      uVar3 = uVar2;
      uVar9 = uVar4;
    }
    self = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar8 = _objc_msgSend((ID)self,"mainBundle");
    uVar10 = uVar3;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (uVar9,uVar3,0,0,IVar8,0,0xe000000000000000,0,0xe000000000000000);
    _swift_bridgeObjectRelease(uVar3);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar9,uVar10);
    _swift_bridgeObjectRelease(uVar10);
    _objc_msgSend(IVar6,"setText:",uVar9);
  }
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::checkmarkView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setHidden:",
                  (ulong)((param_2 & 0xff) == 6 || (param_2 & 0xff) != (uVar11 & 0xff)));
  }
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setHidden:",(ulong)((uVar11 & 0xff) != 4));
  }
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::middleSeparatorView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setHidden:",(ulong)((uVar11 & 0xff) != 4));
  }
  uVar11 = 0x31 >> (ulong)(param_2 & 0x1f);
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel;
  _swift_unknownObjectWeakLoadStrong();
  uVar12 = (uint)((param_2 & 0xff) < 6);
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setEnabled:",(ulong)(uVar12 & uVar11));
  }
  lVar5 = _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch;
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setEnabled:",(ulong)(uVar12 & uVar11));
  }
  IVar6 = unaff_x20 + lVar5;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 != 0) {
    _objc_msgSend(IVar6,"setOn:",(ulong)(param_3 & 1));
  }
  IVar6 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSymbolView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar6 == 0) {
    return 0;
  }
  _objc_msgSend(IVar6,"setNeedsDisplay");
  return 0;
}

// ==== 100641cfc _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + transitionStackView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641d1c _TtC8Playback34TransitionContinuePadTableViewCell::setTransitionStackView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setTransitionStackView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + transitionStackView,param_3);
  return;
}

// ==== 100641d30 _TtC8Playback34TransitionContinuePadTableViewCell::transitionImageView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::transitionImageView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + transitionImageView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641d50 _TtC8Playback34TransitionContinuePadTableViewCell::setTransitionImageView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setTransitionImageView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + transitionImageView,param_3);
  return;
}

// ==== 100641d64 _TtC8Playback34TransitionContinuePadTableViewCell::titleLabel ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::titleLabel(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + titleLabel;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641d84 _TtC8Playback34TransitionContinuePadTableViewCell::setTitleLabel: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setTitleLabel_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + titleLabel,param_3);
  return;
}

// ==== 100641d98 _TtC8Playback34TransitionContinuePadTableViewCell::checkmarkView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::checkmarkView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + checkmarkView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641db8 _TtC8Playback34TransitionContinuePadTableViewCell::setCheckmarkView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setCheckmarkView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + checkmarkView,param_3);
  return;
}

// ==== 100641dcc _TtC8Playback34TransitionContinuePadTableViewCell::middleSeparatorView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::middleSeparatorView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + middleSeparatorView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641dec _TtC8Playback34TransitionContinuePadTableViewCell::setMiddleSeparatorView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setMiddleSeparatorView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + middleSeparatorView,param_3);
  return;
}

// ==== 100641e00 _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + continuePadStackView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641e20 _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadStackView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadStackView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + continuePadStackView,param_3);
  return;
}

// ==== 100641e34 _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSymbolView ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSymbolView(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + continuePadSymbolView;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641e54 _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadSymbolView: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadSymbolView_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + continuePadSymbolView,param_3);
  return;
}

// ==== 100641e68 _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + continuePadLabel;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641e88 _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadLabel: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadLabel_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + continuePadLabel,param_3);
  return;
}

// ==== 100641e9c _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch ====
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch(ID param_1,SEL param_2)

{
  ID IVar1;
  
  IVar1 = param_1 + continuePadSwitch;
  _swift_unknownObjectWeakLoadStrong();
  return IVar1;
}

// ==== 100641ebc _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadSwitch: ====
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::setContinuePadSwitch_
               (ID param_1,SEL param_2,ID param_3)

{
  _swift_unknownObjectWeakAssign(param_1 + continuePadSwitch,param_3);
  return;
}

// ==== 100641ed0 FUN_100641ed0 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8 FUN_100641ed0(void)

{
  ID IVar1;
  undefined *puVar2;
  ID IVar3;
  undefined8 uVar4;
  ID self;
  undefined8 uVar5;
  double dVar6;
  long unaff_x20;
  
  _swift_getObjectType();
  _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,"awakeFromNib");
  IVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar1 != 0) {
    _objc_msgSend(IVar1,"setHidden:",1);
  }
  IVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar1 != 0) {
    puVar2 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    IVar3 = _objc_msgSend((ID)puVar2,"mainBundle");
    uVar4 = 0x65756e69746e6f43;
    uVar5 = 0xec00000064615020;
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
              (0x65756e69746e6f43,0xec00000064615020,0,0,IVar3,0,0xe000000000000000,0,
               0xe000000000000000);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar4,uVar5);
    _swift_bridgeObjectRelease(uVar5);
    _objc_msgSend(IVar1,"setText:",uVar4);
  }
  IVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar1 != 0) {
    puVar2 = &_OBJC_CLASS___UIColor;
    _objc_allocWithZone();
    dVar6 = 0.15;
    IVar3 = _objc_msgSend((ID)puVar2,"initWithWhite:alpha:",0x3fc3333333333333,0x3ff0000000000000);
    self = _objc_msgSend(IVar1,"layer");
    _objc_msgSend(IVar1,"frame");
    _CGRectGetHeight();
    _objc_msgSend(self,"setCornerRadius:",dVar6 * 0.5);
    _objc_msgSend(IVar1,"setClipsToBounds:",1);
    _objc_msgSend(IVar1,"setTintColor:",IVar3);
    _objc_msgSend(IVar1,"setBackgroundColor:",IVar3);
  }
  puVar2 = &_OBJC_CLASS___UITapGestureRecognizer;
  _objc_allocWithZone();
  IVar3 = _objc_msgSend((ID)puVar2,"initWithTarget:action:");
  _objc_msgSend(IVar3,"setCancelsTouchesInView:",0);
  IVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (IVar1 != 0) {
    _objc_msgSend(IVar1,"addGestureRecognizer:",IVar3);
  }
  return 0;
}

// ==== 100642168 _TtC8Playback34TransitionContinuePadTableViewCell::awakeFromNib ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::awakeFromNib(ID param_1,SEL param_2)

{
  FUN_100641ed0(param_1);
  return;
}

// ==== 100642190 _TtC8Playback34TransitionContinuePadTableViewCell::prepareForReuse ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::prepareForReuse(ID param_1,SEL param_2)

{
  class_t *pcVar1;
  ID self;
  objc_super local_30;
  
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_30.receiver = param_1;
  local_30.super_class = pcVar1;
  _objc_msgSendSuper2(&local_30,"prepareForReuse");
  self = param_1 + continuePadStackView;
  _swift_unknownObjectWeakLoadStrong();
  if (self != 0) {
    _objc_msgSend(self,"setHidden:",1);
  }
  return;
}

// ==== 100642218 _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackViewTappedWithGestureRecognizer: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::
     transitionStackViewTappedWithGestureRecognizer_(ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  
  lVar1 = param_1 + delegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar1 != 0) {
    FUN_100042768(param_1);
    _swift_unknownObjectRelease(lVar1);
    return;
  }
  return;
}

// ==== 100642298 _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitchValueChanged: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitchValueChanged_
               (ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  
  lVar1 = param_1 + delegate;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar1 != 0) {
    FUN_1000428f4(param_3);
    _swift_unknownObjectRelease(lVar1);
    return;
  }
  return;
}

// ==== 10064231c FUN_10064231c ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_10064231c(undefined8 param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionImageView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::titleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::checkmarkView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::middleSeparatorView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSymbolView,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch,0);
  lVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  if (param_3 == 0) {
    param_2 = 0;
  }
  else {
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_2,param_3);
    _swift_bridgeObjectRelease(param_3);
  }
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffb0,
                              "initWithStyle:reuseIdentifier:",param_1,param_2);
  return IVar2;
}

// ==== 100642480 _TtC8Playback34TransitionContinuePadTableViewCell::initWithStyle:reuseIdentifier: ====
/* Function Stack Size: 0x20 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::initWithStyle_reuseIdentifier_
             (ID param_1,SEL param_2,long_long param_3,ID param_4)

{
  if (param_4 == 0) {
    param_2 = (SEL)0x0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ(param_4);
  }
  FUN_10064231c(param_3,param_4,param_2);
  return param_3;
}

// ==== 1006424c8 FUN_1006424c8 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

ID FUN_1006424c8(undefined8 param_1)

{
  long lVar1;
  ID IVar2;
  long unaff_x20;
  
  _swift_getObjectType();
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::transitionImageView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::titleLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::checkmarkView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::middleSeparatorView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadStackView,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSymbolView,0)
  ;
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadLabel,0);
  _swift_unknownObjectWeakInit
            (unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::continuePadSwitch,0);
  lVar1 = unaff_x20 + _TtC8Playback34TransitionContinuePadTableViewCell::delegate;
  *(undefined8 *)(lVar1 + 8) = 0;
  _swift_unknownObjectWeakInit(lVar1,0);
  IVar2 = _objc_msgSendSuper2((objc_super *)&stack0xffffffffffffffc0,"initWithCoder:",param_1);
  return IVar2;
}

// ==== 100642608 _TtC8Playback34TransitionContinuePadTableViewCell::initWithCoder: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

ID _TtC8Playback34TransitionContinuePadTableViewCell::initWithCoder_
             (ID param_1,SEL param_2,ID param_3)

{
  FUN_1006424c8();
  return param_3;
}

// ==== 100642630 _TtC8Playback34TransitionContinuePadTableViewCell::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void _TtC8Playback34TransitionContinuePadTableViewCell::_cxx_destruct(ID param_1,SEL param_2)

{
  _swift_unknownObjectWeakDestroy(param_1 + transitionStackView);
  _swift_unknownObjectWeakDestroy(param_1 + transitionImageView);
  _swift_unknownObjectWeakDestroy(param_1 + titleLabel);
  _swift_unknownObjectWeakDestroy(param_1 + checkmarkView);
  _swift_unknownObjectWeakDestroy(param_1 + middleSeparatorView);
  _swift_unknownObjectWeakDestroy(param_1 + continuePadStackView);
  _swift_unknownObjectWeakDestroy(param_1 + continuePadSymbolView);
  _swift_unknownObjectWeakDestroy(param_1 + continuePadLabel);
  _swift_unknownObjectWeakDestroy(param_1 + continuePadSwitch);
  FUN_100026610(param_1 + delegate);
  return;
}

// ==== 1006426e8 FUN_1006426e8 ====
void FUN_1006426e8(void)

{
  _swift_getInitializedObjCClass(&objc::class_t::_TtC8Playback34TransitionContinuePadTableViewCell);
  return;
}

// ==== 1006e9ee4 _TtC8Playback32StackMenuListTableViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback32StackMenuListTableViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback32StackMenuListTableViewController *this,ID param_1,SEL param_2,
          CGSize param_3,ID param_4)

{
  class_t *pcVar1;
  double dVar2;
  objc_super local_50;
  
  dVar2 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  FUN_1006ea114();
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  _swift_unknownObjectRetain(dVar2);
  _objc_msgSendSuper2(&local_50,"viewWillTransitionToSize:withTransitionCoordinator:",dVar2);
  FUN_1006e9c30();
  _swift_unknownObjectRelease(dVar2);
  return;
}

// ==== 100705ad4 _TtC8Playback23StackMenuViewController::viewWillTransitionToSize:withTransitionCoordinator: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void __thiscall
_TtC8Playback23StackMenuViewController::viewWillTransitionToSize_withTransitionCoordinator_
          (_TtC8Playback23StackMenuViewController *this,ID param_1,SEL param_2,CGSize param_3,
          ID param_4)

{
  class_t *pcVar1;
  double dVar2;
  objc_super local_50;
  
  dVar2 = param_3.field0_0x0;
  pcVar1 = (class_t *)param_1;
  _swift_getObjectType();
  local_50.receiver = param_1;
  local_50.super_class = pcVar1;
  _swift_unknownObjectRetain(dVar2);
  _objc_msgSendSuper2(&local_50,"viewWillTransitionToSize:withTransitionCoordinator:",dVar2);
  FUN_1007053e0();
  _swift_unknownObjectRelease(dVar2);
  return;
}

// ==== 10071af98 FUN_10071af98 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined1  [16] FUN_10071af98(ulong param_1)

{
  undefined **self;
  undefined **ppuVar1;
  undefined *self_00;
  SEL op;
  ulong uVar2;
  undefined **ppuVar3;
  char *pcVar4;
  byte *pbVar5;
  long lVar6;
  char *unaff_x19;
  undefined **unaff_x21;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  
  ppuVar3 = (undefined **)(param_1 & 0xff);
  self = (undefined **)0x0;
  pbVar5 = &switchD_10071afbc::switchdataD_10094a708;
  lVar6 = (ulong)(&switchD_10071afbc::switchdataD_10094a708)[(long)ppuVar3] * 4 + 0x10071afc0;
  op = (SEL)0x0;
  ppuVar1 = self;
  pcVar4 = (char *)ppuVar3;
  switch(ppuVar3) {
  default:
    ppuVar3 = (undefined **)"[Artist unknown]";
  case (undefined **)0x52:
  case (undefined **)0x8a:
  case (undefined **)0xca:
  case (undefined **)0xe4:
  case (undefined **)0xf2:
    pcVar4 = (char *)(ppuVar3 + 0x22);
  case (undefined **)0x76:
LAB_10071b124:
    auVar13._8_8_ = (ulong)((long)pcVar4 + -0x20) | 0x8000000000000000;
    auVar13._0_8_ = 0xd00000000000001e;
    return auVar13;
  case (undefined **)0x1:
    self = (undefined **)0xd000000000000021;
  case (undefined **)0xfc:
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0x28:
    pcVar4 = (char *)(ppuVar3 + 0x1b2);
    goto LAB_10071b1e0;
  case (undefined **)0x2:
    op = (SEL)0x8000000100908d40;
  case (undefined **)0x84:
    auVar9._8_8_ = op;
    auVar9._0_8_ = 0xd000000000000028;
    return auVar9;
  case (undefined **)0x3:
    auVar11._8_8_ = 0x8000000100908d10;
    auVar11._0_8_ = 0xd00000000000002c;
    return auVar11;
  case (undefined **)0x4:
    ppuVar3 = (undefined **)"cloudSongSectionsEditActionsControlsTooltipShown";
  case (undefined **)0x7c:
    ppuVar3 = ppuVar3 + -4;
  case (undefined **)0x26:
  case (undefined **)0x3a:
  case (undefined **)0x42:
  case (undefined **)0x4a:
  case (undefined **)0x5e:
  case (undefined **)0x72:
  case (undefined **)0x7a:
  case (undefined **)0x82:
  case (undefined **)0x96:
  case (undefined **)0xaa:
  case (undefined **)0xb2:
  case (undefined **)0xba:
  case (undefined **)0xc2:
  case (undefined **)0xd6:
  case (undefined **)0xea:
    auVar7._8_8_ = (ulong)ppuVar3 | 0x8000000000000000;
    auVar7._0_8_ = 0xd000000000000030;
    return auVar7;
  case (undefined **)0x5:
    pcVar4 = "cloudSongSectionsQuickTapTooltipShown";
    goto LAB_10071b144;
  case (undefined **)0x6:
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0x58:
    pcVar4 = (char *)(ppuVar3 + 0x192);
LAB_10071b144:
    ppuVar3 = (undefined **)((long)pcVar4 + -0x20);
switchD_10071afbc_caseD_3d:
    auVar14._8_8_ = (ulong)ppuVar3 | 0x8000000000000000;
    auVar14._0_8_ = 0xd000000000000025;
    return auVar14;
  case (undefined **)0x7:
    self = (undefined **)0xd000000000000021;
    pcVar4 = "midiTimelineEditModesTooltipShown";
  case (undefined **)0xf8:
LAB_10071b1e0:
    auVar18._8_8_ = (ulong)((long)pcVar4 + -0x20) | 0x8000000000000000;
    auVar18._0_8_ = self;
    return auVar18;
  case (undefined **)0x8:
  case (undefined **)0x1d:
  case (undefined **)0xfe:
  case (undefined **)0xff:
    pcVar4 = "midiTimelineCueControlsTooltipShown";
    goto LAB_10071b178;
  case (undefined **)0x9:
    pcVar4 = "midiTimelineAddAMIDICueTooltipShown";
    goto LAB_10071b178;
  case (undefined **)0xa:
    self = (undefined **)&DAT_00000021;
  case (undefined **)0x4c:
    self = (undefined **)((ulong)self | 0xd000000000000000);
  case (undefined **)0x1f:
    pcVar4 = "midiTimelineNudgeModeTooltipShown";
    goto LAB_10071b1e0;
  case (undefined **)0xb:
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0x60:
    pcVar4 = (char *)(ppuVar3 + 0x176);
LAB_10071b104:
    ppuVar3 = (undefined **)((long)pcVar4 + -0x20);
switchD_10071afbc_caseD_25:
    op = (SEL)((ulong)ppuVar3 | 0x8000000000000000);
    ppuVar3 = (undefined **)0x21;
    goto switchD_10071afbc_caseD_1a;
  case (undefined **)0xc:
  case (undefined **)0x4d:
  case (undefined **)0x7d:
    pcVar4 = "padPlayerPaneCycleTooltipShown";
    goto LAB_10071b124;
  case (undefined **)0xd:
    pcVar4 = "padPlayerInterfaceTooltipShown";
    goto LAB_10071b124;
  case (undefined **)0xe:
    pcVar4 = "padPlayerPadFaderTooltipShown";
    goto LAB_10071b1b8;
  case (undefined **)0xf:
    auVar10._8_8_ = 0x8000000100908b00;
    auVar10._0_8_ = 0xd000000000000022;
    return auVar10;
  case (undefined **)0x10:
  case (undefined **)0x32:
  case (undefined **)0x34:
  case (undefined **)0x3e:
  case (undefined **)0x46:
  case (undefined **)0x6a:
  case (undefined **)0x6c:
  case (undefined **)0xa2:
  case (undefined **)0xae:
  case (undefined **)0xe2:
    self = (undefined **)&DAT_00000021;
  case (undefined **)0xa4:
    self = (undefined **)((ulong)self | 0xd000000000000000);
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0x2a:
  case (undefined **)0x62:
  case (undefined **)0x9a:
  case (undefined **)0xda:
    pcVar4 = (char *)(ppuVar3 + 0x15e);
    goto LAB_10071b1e0;
  case (undefined **)0x11:
    pcVar4 = "padPlayerNewTransitionsTooltipShown";
LAB_10071b178:
    ppuVar3 = (undefined **)(pcVar4 + -0x20);
switchD_10071afbc_caseD_1b:
    op = (SEL)((ulong)ppuVar3 | 0x8000000000000000);
    goto switchD_10071afbc_caseD_20;
  case (undefined **)0x13:
    pcVar4 = "SetlistManagementTooltipShown";
LAB_10071b1b8:
    auVar17._8_8_ = (ulong)(pcVar4 + -0x20) | 0x8000000000000000;
    auVar17._0_8_ = 0xd00000000000001d;
    return auVar17;
  case (undefined **)0x14:
    pcVar4 = "DemoSetlistTransportTooltipShown";
    goto LAB_10071b198;
  case (undefined **)0x15:
    pcVar4 = "DemoSetlistWaveformTooltipShown";
    goto LAB_10071b104;
  case (undefined **)0x16:
  case (undefined **)0x1e:
  case (undefined **)0x86:
  case (undefined **)0xee:
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0xb6:
  case (undefined **)0xbe:
  case (undefined **)0xc6:
    pcVar4 = (char *)(ppuVar3 + 0x144);
LAB_10071b198:
    op = (SEL)((ulong)((long)pcVar4 + -0x20) | 0x8000000000000000);
    ppuVar3 = (undefined **)0x21;
switchD_10071afbc_caseD_e8:
    self = (undefined **)(((ulong)ppuVar3 | 0xd000000000000000) - 1);
    goto switchD_10071afbc_caseD_3c;
  case (undefined **)0x17:
    self = (undefined **)&DAT_00000021;
  case (undefined **)0xd4:
    self = (undefined **)((ulong)self | 0xd000000000000000);
    pcVar4 = "DemoSetlistTrackMixerTooltipShown";
    goto LAB_10071b1e0;
  case (undefined **)0x18:
    ppuVar3 = (undefined **)0x100908000;
  case (undefined **)0xac:
  case (undefined **)0xb5:
  case (undefined **)0xbd:
  case (undefined **)0xc5:
    op = (SEL)((ulong)(ppuVar3 + 0x134) | 0x8000000000000000);
  case (undefined **)0x5a:
  case (undefined **)0x92:
  case (undefined **)0xd2:
  case (undefined **)0xfa:
    self = (undefined **)0xd000000000000024;
  case (undefined **)0x12:
    auVar8._8_8_ = op;
    auVar8._0_8_ = self;
    return auVar8;
  case (undefined **)0x1a:
switchD_10071afbc_caseD_1a:
    auVar12._0_8_ = ((ulong)ppuVar3 | 0xd000000000000000) - 2;
    auVar12._8_8_ = op;
    return auVar12;
  case (undefined **)0x1b:
  case (undefined **)0x1c:
  case (undefined **)0x75:
  case (undefined **)0xfd:
    goto switchD_10071afbc_caseD_1b;
  case (undefined **)0x20:
switchD_10071afbc_caseD_20:
    auVar15._8_8_ = op;
    auVar15._0_8_ = 0xd000000000000023;
    return auVar15;
  case (undefined **)0x24:
    unaff_x19 = "Quick Tap to Edit";
    self = (undefined **)&_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    ppuVar3 = &PTR__swift_weakDestroy_100aa0000;
  case (undefined **)0x98:
    self = (undefined **)_objc_msgSend((ID)self,ppuVar3[0x8d]);
    ppuVar1 = (undefined **)0xd00000000000001b;
    break;
  case (undefined **)0x25:
  case (undefined **)0x39:
  case (undefined **)0x41:
  case (undefined **)0x49:
  case (undefined **)0x5d:
  case (undefined **)0x71:
  case (undefined **)0x79:
  case (undefined **)0x81:
  case (undefined **)0x95:
  case (undefined **)0xa9:
  case (undefined **)0xb1:
  case (undefined **)0xb9:
  case (undefined **)0xc1:
  case (undefined **)0xd5:
  case (undefined **)0xe9:
    goto switchD_10071afbc_caseD_25;
  case (undefined **)0x3c:
  case (undefined **)0x44:
switchD_10071afbc_caseD_3c:
    auVar16._8_8_ = op;
    auVar16._0_8_ = self;
    return auVar16;
  case (undefined **)0x3d:
  case (undefined **)0x45:
  case (undefined **)0xad:
    goto switchD_10071afbc_caseD_3d;
  case (undefined **)0x4e:
  case (undefined **)0x7e:
    _swift_getInitializedObjCClass();
    unaff_x21 = (undefined **)_objc_msgSend((ID)self,"mainBundle");
    ppuVar3 = (undefined **)0xd000000000000011;
  case (undefined **)0xd0:
    self = unaff_x21;
    ppuVar1 = (undefined **)((long)ppuVar3 + 7);
    break;
  case (undefined **)0x4f:
  case (undefined **)0x7f:
  case (undefined **)0x87:
  case (undefined **)0xb7:
  case (undefined **)0xbf:
  case (undefined **)0xc7:
  case (undefined **)0xef:
    unaff_x19 = (char *)(ppuVar3 + 0xf6);
    self_00 = &_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
    self = (undefined **)_objc_msgSend((ID)self_00,"mainBundle");
    ppuVar1 = (undefined **)0xd000000000000010;
    break;
  case (undefined **)0x59:
  case (undefined **)0x91:
  case (undefined **)0xd1:
    op = ppuVar3[0x8d];
  case (undefined **)0xf9:
    self = (undefined **)_objc_msgSend(0,op);
    ppuVar1 = (undefined **)0x494d206120646441;
    uVar2 = 0xee00657543204944;
    goto LAB_10071b7f0;
  case (undefined **)0x70:
  case (undefined **)0x78:
  case (undefined **)0x80:
    unaff_x19 = "Manage Your Setlists";
  case (undefined **)0x99:
  case (undefined **)0xc4:
  case (undefined **)0xd9:
    ppuVar3 = &PTR_s_padPlayerPlayStateDidChange__100aa3000;
  case (undefined **)0x29:
  case (undefined **)0x61:
    self = (undefined **)ppuVar3[0x1bd];
    _swift_getInitializedObjCClass();
  case (undefined **)0xed:
    unaff_x21 = (undefined **)_objc_msgSend((ID)self,"mainBundle");
  case (undefined **)0x5c:
    ppuVar3 = (undefined **)0xd000000000000011;
  case (undefined **)0xbc:
    self = unaff_x21;
    ppuVar1 = ppuVar3 + 2;
    break;
  case (undefined **)0x74:
  case (undefined **)0x94:
    self = (undefined **)_objc_msgSend(0,"mainBundle");
  case (undefined **)0x85:
    ppuVar1 = (undefined **)0xd000000000000017;
    unaff_x21 = self;
  case (undefined **)0x90:
    self = unaff_x21;
    break;
  case (undefined **)0xa8:
  case (undefined **)0xb0:
  case (undefined **)0xb8:
  case (undefined **)0xc0:
    lVar6 = 0x10071b20c;
    pbVar5 = (byte *)&switchD_10071b218::switchdataD_10071b8cc;
  case (undefined **)0xd8:
                    /* WARNING: Could not recover jumptable at 0x00010071b218. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(lVar6 + (int)*(uint *)((long)pbVar5 + ppuVar3 * 4)))();
    auVar19._8_8_ = op;
    auVar19._0_8_ = self;
    return auVar19;
  case (undefined **)0xe8:
    goto switchD_10071afbc_caseD_e8;
  case (undefined **)0xec:
    unaff_x19 = (char *)(ppuVar3 + 0x10c);
    self = (undefined **)&_OBJC_CLASS___NSBundle;
    _swift_getInitializedObjCClass();
  case (undefined **)0x38:
  case (undefined **)0x40:
  case (undefined **)0x48:
    self = (undefined **)_objc_msgSend((ID)self,"mainBundle");
  case (undefined **)0xb4:
    uVar2 = (ulong)unaff_x19 | 0x8000000000000000;
    ppuVar1 = (undefined **)0xd000000000000011;
    goto LAB_10071b7f0;
  }
  uVar2 = (ulong)unaff_x19 | 0x8000000000000000;
LAB_10071b7f0:
  __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF
            (ppuVar1,uVar2,0,0,self,0,0xe000000000000000,0);
  auVar20._8_8_ = uVar2;
  auVar20._0_8_ = ppuVar1;
  return auVar20;
}

// ==== 10071be38 FUN_10071be38 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_10071be38(long param_1)

{
  undefined *self;
  ID self_00;
  undefined8 uVar1;
  long lVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  FUN_10071ad20();
  lVar2 = *(long *)(param_1 + 0x10);
  if (lVar2 != 0) {
    puVar3 = (undefined1 *)(param_1 + 0x20);
    do {
      uVar1 = 0xd00000000000001e;
      pcVar4 = "HasViewedDemoSetlistAds";
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      switch(*puVar3) {
      case 1:
        pcVar4 = "automationSetSnapshotTooltipShown";
        goto LAB_10071c00c;
      case 2:
        pcVar4 = "sAddSongSectionsTooltipShown";
        uVar1 = 0xd000000000000028;
        break;
      case 3:
        pcVar4 = "rolsTooltipShown";
        uVar1 = 0xd00000000000002c;
        break;
      case 4:
        pcVar4 = "sQuickTapTooltipShown";
        uVar1 = 0xd000000000000030;
        break;
      case 5:
        pcVar4 = "cloudSongSectionsQuickTapTooltipShown";
        goto LAB_10071bfa4;
      case 6:
        pcVar4 = "midiTimelineCopyPasteCuesTooltipShown";
LAB_10071bfa4:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd000000000000025;
        break;
      case 7:
        pcVar4 = "midiTimelineEditModesTooltipShown";
        goto LAB_10071c00c;
      case 8:
        pcVar4 = "midiTimelineCueControlsTooltipShown";
        goto LAB_10071bfc4;
      case 9:
        pcVar4 = "midiTimelineAddAMIDICueTooltipShown";
        goto LAB_10071bfc4;
      case 10:
        pcVar4 = "midiTimelineNudgeModeTooltipShown";
        goto LAB_10071c00c;
      case 0xb:
        pcVar4 = "padPlayerNewFeatureTooltipShown";
        goto LAB_10071bf7c;
      case 0xc:
        pcVar4 = "padPlayerPaneCycleTooltipShown";
        goto LAB_10071bf90;
      case 0xd:
        pcVar4 = "padPlayerInterfaceTooltipShown";
LAB_10071bf90:
        pcVar4 = pcVar4 + -0x20;
        break;
      case 0xe:
        pcVar4 = "padPlayerPadFaderTooltipShown";
        goto LAB_10071bff8;
      case 0xf:
        pcVar4 = "gMenuTooltipShown";
        uVar1 = 0xd000000000000022;
        break;
      case 0x10:
        pcVar4 = "padPlayerEditSongMenuTooltipShown";
        goto LAB_10071c00c;
      case 0x11:
        pcVar4 = "padPlayerNewTransitionsTooltipShown";
LAB_10071bfc4:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd000000000000023;
        break;
      case 0x12:
        goto switchD_10071bea0_caseD_12;
      case 0x13:
        pcVar4 = "SetlistManagementTooltipShown";
LAB_10071bff8:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd00000000000001d;
        break;
      case 0x14:
        pcVar4 = "DemoSetlistTransportTooltipShown";
        goto LAB_10071bfe4;
      case 0x15:
        pcVar4 = "DemoSetlistWaveformTooltipShown";
LAB_10071bf7c:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd00000000000001f;
        break;
      case 0x16:
        pcVar4 = "DemoSetlistSongTilesTooltipShown";
LAB_10071bfe4:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd000000000000020;
        break;
      case 0x17:
        pcVar4 = "DemoSetlistTrackMixerTooltipShown";
LAB_10071c00c:
        pcVar4 = pcVar4 + -0x20;
        uVar1 = 0xd000000000000021;
        break;
      case 0x18:
        pcVar4 = "Add an Automation Point";
        uVar1 = 0xd000000000000024;
      }
      self = &_OBJC_CLASS___NSUserDefaults;
      _swift_getInitializedObjCClass();
      self_00 = _objc_msgSend((ID)self,"standardUserDefaults");
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF
                (uVar1,(ulong)pcVar4 | 0x8000000000000000);
      _swift_bridgeObjectRelease((ulong)pcVar4 | 0x8000000000000000);
      _objc_msgSend(self_00,"setBool:forKey:",0,uVar1);
switchD_10071bea0_caseD_12:
      lVar2 = lVar2 + -1;
      puVar3 = puVar3 + 1;
    } while (lVar2 != 0);
  }
  _swift_bridgeObjectRelease(param_1);
  return;
}

// ==== 1007cd924 FUN_1007cd924 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void FUN_1007cd924(undefined8 *param_1,undefined8 param_2,ID param_3)

{
  undefined8 *puVar1;
  ulong uVar2;
  undefined8 *puVar3;
  char *pcVar4;
  code *pcVar5;
  undefined8 *puVar6;
  ID IVar7;
  ID IVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined *puVar13;
  undefined8 **ppuVar14;
  char *pcVar15;
  char *pcVar16;
  char *pcVar17;
  undefined1 uVar18;
  char cVar19;
  undefined8 *puVar20;
  undefined8 *puVar21;
  ulong uVar22;
  undefined *puVar23;
  ulong uVar24;
  undefined8 *puVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 *local_118;
  char *pcStack_110;
  ulong local_108;
  char *pcStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined2 local_e8;
  undefined6 uStack_e6;
  undefined *puStack_e0;
  undefined2 local_d8;
  undefined8 *local_d0;
  char *pcStack_c8;
  ID local_c0;
  char *pcStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined2 local_a0;
  undefined4 local_9e;
  undefined2 local_9a;
  undefined *local_98;
  undefined1 local_90;
  undefined1 local_8f;
  undefined *local_88;
  undefined4 local_7e;
  undefined2 local_7a;
  
  pcVar15 = "name";
  puVar6 = (undefined8 *)_objc_msgSend(param_3,"name");
  if (puVar6 == (undefined8 *)0x0) {
    FUN_1003b2424();
    _swift_allocError(&DAT_100a514a0,puVar6,0,0);
    puVar6[1] = 0;
    *puVar6 = 1;
    *(undefined1 *)(puVar6 + 2) = 2;
    _swift_willThrow();
    return;
  }
  __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  _swift_bridgeObjectRetain(pcVar15);
  pcVar16 = "details";
  IVar7 = _objc_msgSend(param_3,"details");
  if (IVar7 == 0) {
    IVar7 = 0;
    pcVar16 = (char *)0x0;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  _swift_bridgeObjectRetain(pcVar16);
  _objc_msgSend(param_3,"storedSampleTimecode");
  uVar26 = param_2;
  _objc_msgSend(param_3,"storedSequenceTimecode");
  uVar27 = uVar26;
  IVar8 = _objc_msgSend(param_3,"transitionBeats");
  puVar9 = (undefined8 *)_objc_msgSend(param_3,"applyTransitionLengthCorrection");
  puVar10 = puVar9;
  FUN_100822b68();
  uVar2 = (ulong)puVar10 & 0xc000000000000001;
  if (uVar2 == 0) {
    puVar20 = (undefined8 *)puVar10[2];
    puVar23 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  else {
    puVar20 = (undefined8 *)((ulong)puVar10 & 0xffffffffffffff8);
    if ((long)puVar10 < 0) {
      puVar20 = puVar10;
    }
    __ss10__CocoaSetV5countSivg();
    puVar23 = PTR___swiftEmptyArrayStorage_100a1e050;
  }
  PTR___swiftEmptyArrayStorage_100a1e050 = puVar23;
  if (puVar20 == (undefined8 *)0x0) {
    _swift_retain(puVar23);
    _swift_bridgeObjectRelease(puVar10);
  }
  else {
    uVar22 = (ulong)puVar20 & ((long)puVar20 >> 0x3f ^ 0xffffffffffffffffU);
    local_88 = puVar23;
    _swift_retain();
    uVar18 = 0;
    FUN_1001cd844(0);
    puVar23 = local_88;
    if (uVar2 == 0) {
      puVar25 = puVar10;
      thunk_FUN_100286c08();
    }
    else {
      puVar25 = (undefined8 *)((ulong)puVar10 & 0xffffffffffffff8);
      if ((long)puVar10 < 0) {
        puVar25 = puVar10;
      }
      __ss10__CocoaSetV10startIndexAB0D0Vvg();
      uVar18 = 1;
    }
    local_108 = CONCAT71(local_108._1_7_,uVar18) & 0xffffffffffffff01;
    local_118 = puVar25;
    pcStack_110 = (char *)uVar22;
    if ((long)puVar20 < 0) {
                    /* WARNING: Does not return */
      pcVar5 = (code *)SoftwareBreakpoint(1,0x1007cdeac);
      (*pcVar5)();
    }
    puVar25 = (undefined8 *)0x0;
    puVar3 = (undefined8 *)((ulong)puVar10 & 0xffffffffffffff8);
    if ((long)puVar10 < 0) {
      puVar3 = puVar10;
    }
    do {
      pcVar4 = pcStack_110;
      puVar21 = local_118;
      if (puVar20 <= puVar25) {
                    /* WARNING: Does not return */
        pcVar5 = (code *)SoftwareBreakpoint(1,0x1007cdea4);
        (*pcVar5)();
      }
      puVar1 = (undefined8 *)((long)puVar25 + 1);
      if (SCARRY8((long)puVar25,1)) {
                    /* WARNING: Does not return */
        pcVar5 = (code *)SoftwareBreakpoint(1,0x1007cdea8);
        (*pcVar5)();
      }
      cVar19 = (char)local_108;
      uVar22 = local_108 & 0xff;
      puVar11 = local_118;
      FUN_100286984(local_118,pcStack_110,uVar22,puVar10);
      pcVar17 = "automationID";
      puVar12 = (undefined8 *)_objc_msgSend((ID)puVar11,"automationID");
      if (puVar12 == (undefined8 *)0x0) {
        FUN_1003b2424();
        _swift_allocError(&DAT_100a514a0,puVar12,0,0);
        puVar12[1] = 0;
        *puVar12 = 2;
        *(undefined1 *)(puVar12 + 2) = 2;
        _swift_willThrow();
        FUN_100286fc0(puVar21,pcVar4,uVar22);
        _swift_bridgeObjectRelease(puVar10);
        _swift_bridgeObjectRelease_n(pcVar15,2);
        _swift_bridgeObjectRelease_n(pcVar16,2);
        _swift_release(puVar23);
        return;
      }
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      _objc_msgSend((ID)puVar11,"storedValue");
      uVar24 = *(ulong *)(puVar23 + 0x10);
      uVar28 = uVar27;
      local_88 = puVar23;
      if (*(ulong *)(puVar23 + 0x18) >> 1 <= uVar24) {
        FUN_1001cd844(1 < *(ulong *)(puVar23 + 0x18),uVar24 + 1,1);
      }
      puVar23 = local_88;
      *(ulong *)(local_88 + 0x10) = uVar24 + 1;
      *(undefined8 **)(local_88 + uVar24 * 0x18 + 0x20) = puVar12;
      *(char **)(local_88 + uVar24 * 0x18 + 0x28) = pcVar17;
      *(undefined8 *)(local_88 + uVar24 * 0x18 + 0x30) = uVar27;
      if (uVar2 == 0) {
        puVar11 = puVar21;
        pcVar17 = pcVar4;
        FUN_1007cd828();
        FUN_100286fc0(puVar21,pcVar4,uVar22);
        local_108 = CONCAT71(local_108._1_7_,cVar19) & 0xffffffffffffff01;
        local_118 = puVar11;
        pcStack_110 = pcVar17;
      }
      else {
        if (cVar19 == '\0') {
                    /* WARNING: Does not return */
          pcVar5 = (code *)SoftwareBreakpoint(1,0x1007cdeb0);
          (*pcVar5)();
        }
        __ss10__CocoaSetV5IndexV16handleBitPatternSuvg(puVar21,pcVar4);
        if (puVar21 == (undefined8 *)0x0) {
          puVar21 = (undefined8 *)0x1;
        }
        else {
          _swift_isUniquelyReferenced_nonNull_native();
        }
        _swift_bridgeObjectRetain(puVar10);
        puVar13 = &DAT_100b0d448;
        FUN_100021774(&DAT_100b0d448);
        ppuVar14 = &local_d0;
        __sSh5IndexV8_asCocoas02__C3SetVAAVvM(ppuVar14,puVar13);
        __ss10__CocoaSetV9formIndex5after8isUniqueyAB0D0Vz_SbtF(puVar13,puVar21,puVar3);
        _swift_bridgeObjectRelease(puVar10);
        (*(code *)ppuVar14)(&local_d0,0);
      }
      puVar25 = (undefined8 *)((long)puVar25 + 1);
      uVar27 = uVar28;
    } while (puVar1 != puVar20);
    FUN_100286fc0(local_118,pcStack_110,local_108 & 0xff);
    _swift_bridgeObjectRelease(puVar10);
  }
  local_d8 = CONCAT11(1,(char)puVar9);
  local_118 = puVar6;
  pcStack_110 = pcVar15;
  local_108 = IVar7;
  pcStack_100 = pcVar16;
  local_f8 = param_2;
  uStack_f0 = uVar26;
  local_e8 = (short)IVar8;
  puStack_e0 = puVar23;
  FUN_1002f9a10(&local_118);
  _swift_bridgeObjectRelease(pcVar15);
  _swift_bridgeObjectRelease(pcVar16);
  local_9e = local_7e;
  local_9a = local_7a;
  local_8f = 1;
  local_d0 = puVar6;
  pcStack_c8 = pcVar15;
  local_c0 = IVar7;
  pcStack_b8 = pcVar16;
  local_b0 = param_2;
  uStack_a8 = uVar26;
  local_a0 = (short)IVar8;
  local_98 = puVar23;
  local_90 = (char)puVar9;
  FUN_1002f9a58(&local_d0);
  param_1[5] = uStack_f0;
  param_1[4] = local_f8;
  param_1[7] = puStack_e0;
  param_1[6] = CONCAT62(uStack_e6,local_e8);
  *(undefined2 *)(param_1 + 8) = local_d8;
  param_1[1] = pcStack_110;
  *param_1 = local_118;
  param_1[3] = pcStack_100;
  param_1[2] = local_108;
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

// ==== 1007e2b80 FUN_1007e2b80 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x0001007e54c8) */
/* WARNING: Removing unreachable block (ram,0x0001007e4eb0) */
/* WARNING: Removing unreachable block (ram,0x0001007e3ca8) */
/* WARNING: Removing unreachable block (ram,0x0001007e4238) */
/* WARNING: Removing unreachable block (ram,0x0001007e3ea0) */
/* WARNING: Removing unreachable block (ram,0x0001007e3ea8) */
/* WARNING: Removing unreachable block (ram,0x0001007e4808) */
/* WARNING: Removing unreachable block (ram,0x0001007e3d88) */
/* WARNING: Removing unreachable block (ram,0x0001007e3b08) */
/* WARNING: Removing unreachable block (ram,0x0001007e3a1c) */
/* WARNING: Removing unreachable block (ram,0x0001007e462c) */
/* WARNING: Removing unreachable block (ram,0x0001007e3fa8) */
/* WARNING: Removing unreachable block (ram,0x0001007e3f38) */
/* WARNING: Removing unreachable block (ram,0x0001007e5008) */
/* WARNING: Removing unreachable block (ram,0x0001007e58b0) */
/* WARNING: Removing unreachable block (ram,0x0001007e4db0) */
/* WARNING: Removing unreachable block (ram,0x0001007e4350) */
/* WARNING: Removing unreachable block (ram,0x0001007e39ac) */
/* WARNING: Removing unreachable block (ram,0x0001007e3d18) */
/* WARNING: Removing unreachable block (ram,0x0001007e44bc) */
/* WARNING: Removing unreachable block (ram,0x0001007e5850) */
/* WARNING: Removing unreachable block (ram,0x0001007e55c4) */
/* WARNING: Removing unreachable block (ram,0x0001007e4aa0) */
/* WARNING: Removing unreachable block (ram,0x0001007e3b78) */
/* WARNING: Removing unreachable block (ram,0x0001007e4940) */
/* WARNING: Removing unreachable block (ram,0x0001007e4d2c) */
/* WARNING: Removing unreachable block (ram,0x0001007e500c) */
/* WARNING: Removing unreachable block (ram,0x0001007e393c) */
/* WARNING: Removing unreachable block (ram,0x0001007e5920) */
/* WARNING: Removing unreachable block (ram,0x0001007e531c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4a30) */
/* WARNING: Removing unreachable block (ram,0x0001007e4540) */
/* WARNING: Removing unreachable block (ram,0x0001007e4b94) */
/* WARNING: Removing unreachable block (ram,0x0001007e4b9c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4f78) */
/* WARNING: Removing unreachable block (ram,0x0001007e4f80) */
/* WARNING: Removing unreachable block (ram,0x0001007e443c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4444) */
/* WARNING: Removing unreachable block (ram,0x0001007e5924) */
/* WARNING: Removing unreachable block (ram,0x0001007e592c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4060) */
/* WARNING: Removing unreachable block (ram,0x0001007e469c) */
/* WARNING: Removing unreachable block (ram,0x0001007e3bfc) */
/* WARNING: Removing unreachable block (ram,0x0001007e48b4) */
/* WARNING: Removing unreachable block (ram,0x0001007e48b8) */
/* WARNING: Removing unreachable block (ram,0x0001007e470c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4aa4) */
/* WARNING: Removing unreachable block (ram,0x0001007e4198) */
/* WARNING: Removing unreachable block (ram,0x0001007e41a0) */
/* WARNING: Removing unreachable block (ram,0x0001007e42b8) */
/* WARNING: Removing unreachable block (ram,0x000100816290) */
/* WARNING: Removing unreachable block (ram,0x0001007e3738) */
/* WARNING: Removing unreachable block (ram,0x0001007e4db4) */
/* WARNING: Removing unreachable block (ram,0x0001007e4dbc) */
/* WARNING: Removing unreachable block (ram,0x0001007e4c10) */
/* WARNING: Removing unreachable block (ram,0x0001007e5930) */
/* WARNING: Removing unreachable block (ram,0x0001007e3ff8) */
/* WARNING: Removing unreachable block (ram,0x0001007e4e7c) */
/* WARNING: Removing unreachable block (ram,0x0001007e41b4) */
/* WARNING: Removing unreachable block (ram,0x0001007e3600) */
/* WARNING: Removing unreachable block (ram,0x0001007e4e18) */
/* WARNING: Removing unreachable block (ram,0x0001007e4e28) */
/* WARNING: Removing unreachable block (ram,0x0001007e475c) */
/* WARNING: Removing unreachable block (ram,0x0001007e4e80) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] FUN_1007e2b80(method_list_t param_1,method_list_t param_2,method_list_t param_3)

{
  method_list_t mVar1;
  byte bVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  protocol_list_t *ppVar17;
  method_list_t mVar18;
  method_list_t mVar19;
  code *pcVar20;
  bool bVar21;
  undefined1 uVar22;
  int iVar23;
  method_list_t *pmVar24;
  dword *pdVar25;
  method_list_t self;
  undefined8 uVar26;
  ID IVar27;
  undefined8 uVar28;
  ID IVar29;
  void *pvVar30;
  protocol_list_t *self_00;
  method_list_t mVar31;
  ID IVar32;
  protocol_list_t *ppVar33;
  char *pcVar34;
  method_list_t mVar35;
  undefined *puVar36;
  code cVar37;
  method_list_t mVar38;
  long lVar39;
  undefined8 *puVar40;
  undefined **ppuVar41;
  undefined **ppuVar42;
  method_list_t mVar43;
  method_list_t mVar44;
  method_list_t mVar45;
  protocol_list_t *ppVar46;
  protocol_list_t *ppVar47;
  protocol_list_t *ppVar48;
  protocol_list_t *ppVar49;
  protocol_list_t *ppVar50;
  protocol_list_t *ppVar51;
  method_list_t mVar52;
  method_list_t mVar53;
  uint uVar54;
  method_list_t mVar55;
  ulong uVar56;
  long unaff_x21;
  undefined *puVar57;
  method_list_t mVar58;
  dword dVar59;
  method_list_t self_01;
  long lVar60;
  method_list_t mVar61;
  undefined *puVar62;
  undefined **ppuVar63;
  method_list_t mVar64;
  method_list_t self_02;
  method_list_t mVar65;
  undefined **ppuVar66;
  method_list_t mVar67;
  method_list_t mVar68;
  undefined8 *puVar69;
  double dVar70;
  double dVar71;
  double dVar72;
  undefined *puVar73;
  undefined *unaff_d8;
  double dVar74;
  undefined8 uVar75;
  undefined8 unaff_d9;
  double unaff_d11;
  double unaff_d12;
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
  undefined *apuStack_760 [2];
  method_list_t amStack_750 [3];
  undefined *puStack_738;
  method_list_t mStack_730;
  undefined *apuStack_728 [3];
  protocol_list_t pStack_710;
  method_list_t local_700 [4];
  undefined *local_6e0;
  method_list_t local_6d8;
  undefined *local_6d0 [6];
  method_list_t local_6a0;
  long local_698;
  undefined1 auStack_696 [6];
  undefined8 local_690;
  undefined *local_688;
  method_list_t local_680;
  undefined *local_678 [14];
  long local_608;
  undefined1 auStack_606 [6];
  undefined8 local_600;
  long local_5f8;
  undefined *local_5f0;
  long local_5e8;
  undefined *local_5e0;
  long local_5d8;
  undefined *local_5d0;
  long local_5c8;
  undefined *local_5c0;
  undefined *local_5b8;
  long local_5b0;
  long local_5a8;
  long local_5a0;
  long local_598;
  undefined *local_590;
  undefined *local_588;
  undefined *local_580;
  long local_578;
  undefined *local_570;
  long local_568;
  long local_560;
  long local_558;
  undefined *local_550;
  undefined *local_548;
  undefined *local_540;
  long local_538;
  undefined *local_530;
  long local_528;
  long local_520;
  undefined *local_518;
  undefined *local_510;
  long local_508;
  long local_500;
  undefined *local_4f8;
  undefined *local_4f0;
  long local_4e8;
  undefined *local_4e0;
  long local_4d8;
  long local_4d0;
  undefined *local_4c8;
  undefined *local_4c0;
  long local_4b8;
  undefined *local_4b0;
  long local_4a8;
  undefined *local_4a0;
  long local_498;
  undefined *local_490;
  long local_488;
  undefined *local_480;
  long local_478;
  undefined *local_470;
  long local_468;
  long local_460;
  long local_458;
  undefined *local_450;
  undefined *local_448;
  undefined *local_440;
  undefined *local_438;
  long local_430;
  method_list_t local_428;
  long local_420;
  long local_418;
  long local_410;
  long local_408;
  long local_400;
  long local_3f8;
  long local_3f0;
  long local_3e8;
  long local_3e0;
  long local_3d8;
  long local_3d0;
  long local_3c8;
  long local_3c0;
  long local_3b8;
  long local_3b0;
  long local_3a8;
  long local_3a0;
  long local_398;
  long local_390;
  long local_388;
  long local_380;
  long local_378;
  long local_370;
  long local_368;
  long local_360;
  long local_358;
  long local_350;
  long local_348;
  long local_340;
  long local_338;
  long local_330;
  long local_328;
  long local_320;
  long local_318;
  long local_310;
  long local_308;
  long local_300;
  long local_2f8;
  long local_2f0;
  long local_2e8;
  method_list_t local_2e0;
  method_list_t local_2d8;
  undefined8 *local_2d0;
  method_list_t local_2c8;
  method_list_t local_2c0;
  method_list_t local_2b8;
  undefined1 local_2a2;
  undefined1 local_2a1;
  method_list_t local_2a0;
  method_list_t mStack_298;
  method_list_t local_290;
  method_list_t mStack_288;
  method_list_t local_280;
  method_list_t mStack_278;
  method_list_t local_270;
  method_list_t mStack_268;
  method_list_t local_260;
  class_t *pcStack_258;
  method_list_t local_250;
  method_list_t mStack_248;
  method_list_t local_240;
  method_list_t mStack_238;
  method_list_t local_230;
  dword local_220;
  dword dStack_21c;
  method_list_t mStack_218;
  undefined1 local_210;
  undefined7 uStack_20f;
  method_list_t local_208;
  undefined1 local_200;
  undefined1 uStack_1ff;
  undefined6 uStack_1fe;
  method_list_t mStack_1f8;
  short sStack_1f0;
  undefined6 uStack_1ee;
  method_list_t mStack_1e8;
  byte local_1e0;
  undefined7 uStack_1df;
  class_t *pcStack_1d8;
  method_list_t mStack_1d0;
  method_list_t mStack_1c8;
  method_list_t local_1c0;
  method_list_t mStack_1b8;
  method_list_t local_1b0;
  undefined1 uStack_1a8;
  undefined7 local_1a7;
  undefined1 uStack_1a0;
  undefined8 uStack_19f;
  undefined1 local_191;
  method_list_t local_190;
  method_list_t mStack_188;
  method_list_t local_180;
  method_list_t local_178;
  method_list_t local_170;
  method_list_t mStack_168;
  method_list_t mStack_160;
  method_list_t mStack_158;
  method_list_t local_150;
  class_t *pcStack_148;
  method_list_t local_140;
  method_list_t mStack_138;
  method_list_t local_130;
  method_list_t mStack_128;
  method_list_t local_120;
  undefined1 uStack_118;
  undefined1 uStack_117;
  undefined6 uStack_116;
  undefined1 uStack_110;
  undefined1 uStack_10f;
  undefined7 uStack_10e;
  undefined1 uStack_107;
  method_list_t local_100;
  method_list_t mStack_f8;
  method_list_t mStack_f0;
  method_list_t mStack_e8;
  method_list_t local_e0;
  method_list_t mStack_d8;
  method_list_t mStack_d0;
  method_list_t mStack_c8;
  objc_super local_c0;
  objc_super local_b0;
  method_list_t local_a0;
  method_list_t mStack_98;
  method_list_t mStack_90;
  undefined2 uStack_88;
  undefined6 local_86;
  undefined2 uStack_80;
  undefined6 uStack_7e;
  undefined2 uStack_78;
  undefined6 uStack_76;
  code *pcStack_70;
  undefined *puStack_68;
  
  ppuVar66 = (undefined **)&stack0xfffffffffffffff0;
  ppVar33 = &pStack_710;
  ppuVar42 = (undefined **)&pStack_710;
  ppVar46 = &pStack_710;
  self_00 = &pStack_710;
  puVar62 = &DAT_100b0db28;
  local_2d8 = param_1;
  FUN_100021774();
  local_460 = *(long *)(puVar62 + -8);
  lVar39 = (long)&pStack_710 - (*(long *)(local_460 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db30;
  local_448 = puVar62;
  local_2e8 = lVar39;
  FUN_100021774();
  local_458 = *(long *)(puVar57 + -8);
  mVar38 = (method_list_t)(lVar39 - (*(long *)(local_458 + 0x40) + 0xfU & 0xfffffffffffffff0));
  puVar62 = &DAT_100b0db38;
  local_440 = puVar57;
  local_2e0 = mVar38;
  FUN_100021774();
  local_430 = *(long *)(puVar62 + -8);
  mVar38 = (method_list_t)((long)mVar38 - (*(long *)(local_430 + 0x40) + 0xfU & 0xfffffffffffffff0))
  ;
  puVar57 = &DAT_100b0db40;
  local_438 = puVar62;
  local_2c0 = mVar38;
  FUN_100021774();
  local_468 = *(long *)(puVar57 + -8);
  lVar39 = (long)mVar38 - (*(long *)(local_468 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db48;
  local_450 = puVar57;
  local_2f0 = lVar39;
  FUN_100021774();
  local_478 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_478 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db50;
  local_470 = puVar62;
  local_2f8 = lVar39;
  FUN_100021774();
  local_488 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_488 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db58;
  local_480 = puVar57;
  local_300 = lVar39;
  FUN_100021774();
  local_498 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_498 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db60;
  local_490 = puVar62;
  local_308 = lVar39;
  FUN_100021774();
  local_4a8 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_4a8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db68;
  local_4a0 = puVar57;
  local_310 = lVar39;
  FUN_100021774();
  local_4b8 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_4b8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db70;
  local_4b0 = puVar62;
  local_318 = lVar39;
  FUN_100021774();
  local_4d0 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_4d0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db78;
  local_4c8 = puVar57;
  local_328 = lVar39;
  FUN_100021774();
  local_4d8 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_4d8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db80;
  local_4c0 = puVar62;
  local_320 = lVar39;
  FUN_100021774();
  local_4e8 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_4e8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db88;
  local_4e0 = puVar57;
  local_330 = lVar39;
  FUN_100021774();
  local_508 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_508 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0db90;
  local_4f8 = puVar62;
  local_340 = lVar39;
  FUN_100021774();
  local_500 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_500 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0db98;
  local_4f0 = puVar57;
  local_338 = lVar39;
  FUN_100021774();
  local_520 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_520 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dba0;
  local_510 = puVar62;
  local_348 = lVar39;
  FUN_100021774();
  local_538 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_538 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dba8;
  local_530 = puVar57;
  local_358 = lVar39;
  FUN_100021774();
  local_528 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_528 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dbb0;
  local_518 = puVar62;
  local_350 = lVar39;
  FUN_100021774();
  local_558 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_558 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dbb8;
  local_548 = puVar57;
  local_368 = lVar39;
  FUN_100021774();
  local_560 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_560 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dbc0;
  local_540 = puVar62;
  local_360 = lVar39;
  FUN_100021774();
  local_568 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_568 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dbc8;
  local_550 = puVar57;
  local_370 = lVar39;
  FUN_100021774();
  local_578 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_578 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dbd0;
  local_570 = puVar62;
  local_378 = lVar39;
  FUN_100021774();
  local_5a8 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_5a8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dbd8;
  local_590 = puVar57;
  local_390 = lVar39;
  FUN_100021774();
  local_5a0 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_5a0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dbe0;
  local_588 = puVar62;
  local_388 = lVar39;
  FUN_100021774();
  local_5c8 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_5c8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dbe8;
  local_5b8 = puVar57;
  local_398 = lVar39;
  FUN_100021774();
  local_5e8 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_5e8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dbf0;
  local_5d0 = puVar62;
  local_3a0 = lVar39;
  FUN_100021774();
  local_598 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_598 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dbf8;
  local_580 = puVar57;
  local_380 = lVar39;
  FUN_100021774();
  local_5b0 = *(long *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)(local_5b0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc00;
  local_5e0 = puVar62;
  local_3b0 = lVar39;
  FUN_100021774();
  local_5d8 = *(long *)(puVar57 + -8);
  mVar38 = (method_list_t)(lVar39 - (*(long *)(local_5d8 + 0x40) + 0xfU & 0xfffffffffffffff0));
  puVar62 = &DAT_100b0dc08;
  local_5c0 = puVar57;
  local_2c8 = mVar38;
  FUN_100021774();
  local_5f8 = *(long *)(puVar62 + -8);
  lVar39 = (long)mVar38 - (*(long *)(local_5f8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc10;
  local_5f0 = puVar62;
  local_3a8 = lVar39;
  FUN_100021774();
  local_608 = *(long *)(puVar57 + -8);
  puVar40 = (undefined8 *)(lVar39 - (*(long *)(local_608 + 0x40) + 0xfU & 0xfffffffffffffff0));
  puVar62 = &DAT_100b0dc18;
  local_600 = puVar57;
  local_2d0 = puVar40;
  FUN_100021774();
  local_678[0xc] = *(undefined **)(puVar62 + -8);
  lVar39 = (long)puVar40 - (*(long *)((long)local_678[0xc] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc20;
  local_678[0xd] = puVar62;
  local_3b8 = lVar39;
  FUN_100021774();
  local_678[8] = *(undefined **)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_678[8] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc28;
  local_678[10] = puVar57;
  local_3c8 = lVar39;
  FUN_100021774();
  local_678[6] = *(undefined **)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_678[6] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc30;
  local_678[7] = puVar62;
  local_3d0 = lVar39;
  FUN_100021774();
  local_678[3] = *(undefined **)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_678[3] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc38;
  local_678[5] = puVar57;
  local_3d8 = lVar39;
  FUN_100021774();
  local_678[2] = *(undefined **)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_678[2] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc40;
  local_678[4] = puVar62;
  local_3e0 = lVar39;
  FUN_100021774();
  local_678[9] = *(undefined **)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_678[9] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc48;
  local_678[0xb] = puVar57;
  local_3c0 = lVar39;
  FUN_100021774();
  local_680 = *(method_list_t *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_680 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc50;
  local_678[1] = puVar62;
  local_3e8 = lVar39;
  FUN_100021774();
  local_698 = *(long *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)(local_698 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc58;
  local_690 = puVar57;
  local_3f8 = lVar39;
  FUN_100021774();
  local_6d0[5] = *(undefined **)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_6d0[5] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc60;
  local_6a0 = (method_list_t)puVar62;
  local_400 = lVar39;
  FUN_100021774();
  local_6d0[1] = *(undefined **)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_6d0[1] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc68;
  local_6d0[2] = puVar57;
  local_410 = lVar39;
  FUN_100021774();
  local_6d0[3] = *(undefined **)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_6d0[3] + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc70;
  local_6d0[4] = puVar62;
  local_408 = lVar39;
  FUN_100021774();
  local_688 = *(undefined **)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_688 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar62 = &DAT_100b0dc78;
  local_678[0] = puVar57;
  local_3f0 = lVar39;
  FUN_100021774();
  local_6d8 = *(method_list_t *)(puVar62 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_6d8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar57 = &DAT_100b0dc80;
  local_6d0[0] = puVar62;
  local_418 = lVar39;
  FUN_100021774();
  local_700[3] = *(method_list_t *)(puVar57 + -8);
  lVar39 = lVar39 - (*(long *)((long)local_700[3] + 0x40) + 0xfU & 0xfffffffffffffff0);
  mVar38 = (method_list_t)&DAT_100b0dc88;
  local_6e0 = puVar57;
  local_420 = lVar39;
  FUN_100021774();
  puVar62 = *(undefined **)((long)mVar38 + -8);
  mVar68 = (method_list_t)(lVar39 - (*(long *)(puVar62 + 0x40) + 0xfU & 0xfffffffffffffff0));
  mVar31 = (method_list_t)&DAT_100b0dc90;
  local_428 = mVar38;
  FUN_100021774();
  mVar58 = *(method_list_t *)((long)mVar31 + -8);
  mVar65 = (method_list_t)
           ((long)mVar68 -
           ((ulong)(*(undefined **)((long)mVar58 + 0x40) + 0xf) & 0xfffffffffffffff0));
  local_2b8 = param_3;
  FUN_100023444(param_3,*(undefined **)((long)param_3 + 0x18));
  FUN_1007e0630();
  pcVar34 = &DAT_100a68ac8;
  __ss7DecoderP9container7keyedBys22KeyedDecodingContainerVyqd__Gqd__m_tKs9CodingKeyRd__lFTj(mVar65)
  ;
  mVar52 = local_2c0;
  mVar38 = local_2c8;
  puVar40 = local_2d0;
  if (unaff_x21 != 0) {
LAB_1007e594c:
    mVar31 = (method_list_t)pcVar34;
    FUN_100023468(local_2b8);
    goto LAB_1007e5954;
  }
  self_01 = mVar31;
  local_700[0] = (method_list_t)puVar62;
  local_700[1] = mVar68;
  local_700[2] = mVar58;
  __ss22KeyedDecodingContainerV7allKeysSayxGvg();
  puVar62 = PTR___sSSN_100a1dce0;
  if ((*(method_list_t *)((long)self_01 + 0x10) == (method_list_t)0x0) ||
     (*(method_list_t *)((long)self_01 + 0x10) != (method_list_t)0x1)) {
LAB_1007e3614:
    lVar39 = 0;
    __ss13DecodingErrorOMa();
    puVar40 = (undefined8 *)PTR___ss13DecodingErrorOs0B0sWP_100a1de48;
    _swift_allocError();
    puVar62 = &DAT_100af7ef0;
    FUN_100021774();
    iVar23 = *(int *)(puVar62 + 0x30);
    *puVar40 = &DAT_100a68a38;
    __ss22KeyedDecodingContainerV10codingPathSays9CodingKey_pGvg(mVar31);
    __ss13DecodingErrorO7ContextV10codingPath16debugDescription010underlyingB0ADSays9CodingKey_pG_SSs0B0_pSgtcfC
              ((long)puVar40 + (long)iVar23);
    (**(code **)(*(long *)(lVar39 + -8) + 0x68))
              (puVar40,*(undefined4 *)
                        PTR___ss13DecodingErrorO12typeMismatchyABypXp_AB7ContextVtcABmFWC_100a1de38,
               lVar39);
    _swift_willThrow();
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    pcVar34 = (char *)mVar31;
    goto LAB_1007e594c;
  }
  cVar37 = *(code *)((long)self_01 + 0x20);
  ppuVar41._1_7_ = 0;
  ppuVar41._0_1_ = cVar37;
  if (cVar37 == (code)0x2d) goto LAB_1007e3614;
  mVar68 = (method_list_t)&local_220;
  IVar27 = 0;
  mVar1.entsizeAndFlags = 0;
  mVar1.count = 0;
  puVar57 = (undefined *)0x0;
  IVar29 = 0;
  mVar64.entsizeAndFlags = 0;
  mVar64.count = 0;
  ppuVar63 = (undefined **)0x0;
  self_02.entsizeAndFlags = 0;
  self_02.count = 0;
  mVar58 = self_01;
  mVar35 = (method_list_t)pcVar34;
  ppVar17 = &pStack_710;
  ppVar47 = &pStack_710;
  ppVar48 = &pStack_710;
  ppVar49 = &pStack_710;
  ppVar50 = &pStack_710;
  ppVar51 = &pStack_710;
  mVar53 = (method_list_t)&pStack_710;
  mVar18 = (method_list_t)&pStack_710;
  mVar43 = (method_list_t)&pStack_710;
  mVar44 = (method_list_t)&pStack_710;
  mVar45 = (method_list_t)&pStack_710;
  mVar19 = (method_list_t)&pStack_710;
  mVar55 = mVar65;
  mVar61 = self_01;
  self = self_01;
  mVar67 = mVar65;
  puVar69 = puVar40;
  switch(ppuVar41) {
  case (undefined **)0x1:
    local_190.entsizeAndFlags._0_1_ = 1;
    mVar38 = self_01;
    FUN_1007e1270();
    lVar39 = local_420;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_420,&DAT_100a68be8,&local_190,mVar31,&DAT_100a68be8,mVar38);
    FUN_1007e62c0();
    puVar62 = local_6e0;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    (**(code **)((long)local_700[3] + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    mStack_128 = mStack_1b8;
    local_130 = local_1c0;
    uStack_118 = uStack_1a8;
    local_120 = local_1b0;
    uStack_10f = (undefined1)uStack_19f;
    uStack_10e = (undefined7)((ulong)uStack_19f >> 8);
    uStack_117 = (undefined1)local_1a7;
    uStack_116 = (undefined6)((uint7)local_1a7 >> 8);
    uStack_110 = uStack_1a0;
    local_170.entsizeAndFlags._1_1_ = uStack_1ff;
    local_170.entsizeAndFlags._0_1_ = local_200;
    local_170._2_6_ = uStack_1fe;
    mStack_160._2_6_ = uStack_1ee;
    mStack_160.entsizeAndFlags._0_2_ = sStack_1f0;
    mStack_168 = mStack_1f8;
    mStack_158 = mStack_1e8;
    local_150._1_7_ = uStack_1df;
    local_150.entsizeAndFlags._0_1_ = local_1e0;
    pcStack_148 = pcStack_1d8;
    mStack_138 = mStack_1c8;
    local_140 = mStack_1d0;
    local_190.count = dStack_21c;
    local_190.entsizeAndFlags = local_220;
    local_180._1_7_ = uStack_20f;
    local_180.entsizeAndFlags._0_1_ = local_210;
    mStack_188 = mStack_218;
    local_178 = local_208;
    FUN_100670048(&local_190);
    break;
  case (undefined **)0x2:
    local_190.entsizeAndFlags._0_1_ = 2;
    mVar52 = self_01;
    FUN_1007e1230();
    lVar39 = local_418;
    mVar38 = (method_list_t)&DAT_100a68c78;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_418,&DAT_100a68c78,&local_190,mVar31,&DAT_100a68c78,mVar52);
    puVar62 = local_6d0[0];
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF();
    mVar52 = local_700[2];
    (**(code **)((long)local_6d8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = mVar38;
    FUN_100232e28(&local_190);
    break;
  case (undefined **)0x3:
    local_190.entsizeAndFlags._0_1_ = 3;
    mVar38 = self_01;
    FUN_1007e11f0();
    lVar39 = local_3f0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3f0,&DAT_100a68d08,&local_190,mVar31,&DAT_100a68d08,mVar38);
    puVar57 = local_678[0];
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    mVar38 = (method_list_t)&local_190;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF(mVar38,local_678[0]);
    puVar62 = &DAT_100b0b750;
    local_2c0 = mVar38;
    FUN_100021774(&DAT_100b0b750);
    local_190.entsizeAndFlags._0_1_ = 1;
    puVar40 = &DAT_100b0b758;
    FUN_1007e61b4(&DAT_100b0b758,FUN_100778250,PTR___sSayxGSesSeRzlMc_100a1dd38);
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,puVar62,&local_190,puVar57,puVar62,puVar40);
    mVar53.count = dStack_21c;
    mVar53.entsizeAndFlags = local_220;
    puVar62 = &DAT_100b0b700;
    FUN_100021774(&DAT_100b0b700);
    local_191 = 2;
    puVar40 = &DAT_100b0b708;
    FUN_1007e6228(&DAT_100b0b708,FUN_100778068,PTR___sSayxGSesSeRzlMc_100a1dd38);
    __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
              (&local_2a0,puVar62,&local_191,puVar57,puVar62,puVar40);
    (**(code **)((long)local_688 + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    local_190 = local_2c0;
    local_180 = local_2a0;
    mStack_188 = mVar53;
    FUN_10067001c(&local_190);
    mStack_98 = mStack_128;
    local_a0 = local_130;
    uStack_88 = CONCAT11(uStack_117,uStack_118);
    mStack_90 = local_120;
    uStack_7e = (undefined6)uStack_10e;
    uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
    local_86 = uStack_116;
    uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
    mStack_d8 = mStack_168;
    local_e0 = local_170;
    mStack_c8 = mStack_158;
    mStack_d0 = mStack_160;
    local_c0.super_class = pcStack_148;
    local_c0.receiver = (ID)local_150;
    local_b0.super_class = (class_t *)mStack_138;
    local_b0.receiver = (ID)local_140;
    mVar52 = local_2d8;
    local_100 = local_190;
    mStack_f8 = mStack_188;
    mStack_f0 = local_180;
    mStack_e8 = local_178;
    goto LAB_1007e5d88;
  case (undefined **)0x4:
    local_190.entsizeAndFlags._0_1_ = 4;
    mVar38 = self_01;
    FUN_1007e11b0();
    lVar39 = local_408;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_408,&DAT_100a68d98,&local_190,mVar31,&DAT_100a68d98,mVar38);
    puVar62 = &DAT_100b0b750;
    FUN_100021774(&DAT_100b0b750);
    FUN_1007e61b4(&DAT_100b0b758,FUN_100778250,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar57 = local_6d0[4];
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220,puVar62);
    mVar38 = local_700[2];
    (**(code **)((long)local_6d0[3] + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.count = dStack_21c;
    local_190.entsizeAndFlags = local_220;
    FUN_10035d9a8(&local_190);
    break;
  case (undefined **)0x5:
    local_220 = CONCAT31(local_220._1_3_,5);
    mVar38 = self_01;
    FUN_1007e1170();
    lVar39 = local_410;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_410,&DAT_100a68db8,&local_220,mVar31,&DAT_100a68db8,mVar38);
    (**(code **)((long)local_6d0[1] + 8))(lVar39,local_6d0[2]);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e629c(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x6:
    local_190.entsizeAndFlags._0_1_ = 6;
    mVar52 = self_01;
    FUN_1007e1130();
    lVar39 = local_400;
    mVar38 = (method_list_t)&DAT_100a68e48;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_400,&DAT_100a68e48,&local_190,mVar31,&DAT_100a68e48,mVar52);
    mVar58 = local_6a0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF();
    mVar52 = local_700[2];
    (**(code **)((long)local_6d0[5] + 8))(lVar39,mVar58);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = mVar38;
    FUN_1002bb998(&local_190);
    break;
  case (undefined **)0x7:
    local_190.entsizeAndFlags._0_1_ = 7;
    mVar38 = self_01;
    FUN_1007e10f0();
    lVar39 = local_3f8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3f8,&DAT_100a68ed8,&local_190,mVar31,&DAT_100a68ed8,mVar38);
    FUN_100779948();
    puVar62 = local_690;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)(local_698 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_150._1_7_ = uStack_1df;
    local_150.entsizeAndFlags._0_1_ = local_1e0;
    pcStack_148 = pcStack_1d8;
    mStack_138 = mStack_1c8;
    local_140 = mStack_1d0;
    mStack_128 = mStack_1b8;
    local_130 = local_1c0;
    local_120 = local_1b0;
    local_190.count = dStack_21c;
    local_190.entsizeAndFlags = local_220;
    local_180._1_7_ = uStack_20f;
    local_180.entsizeAndFlags._0_1_ = local_210;
    mStack_188 = mStack_218;
    local_178 = local_208;
    local_170.entsizeAndFlags._1_1_ = uStack_1ff;
    local_170.entsizeAndFlags._0_1_ = local_200;
    local_170._2_6_ = uStack_1fe;
    mStack_160._2_6_ = uStack_1ee;
    mStack_160.entsizeAndFlags._0_2_ = sStack_1f0;
    mStack_168 = mStack_1f8;
    mStack_158 = mStack_1e8;
    FUN_1001f1aa0(&local_190);
    break;
  case (undefined **)0x8:
    local_190.entsizeAndFlags._0_1_ = 8;
    mVar38 = self_01;
    FUN_1007e10b0();
    lVar39 = local_3e8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3e8,&DAT_100a68f68,&local_190,mVar31,&DAT_100a68f68,mVar38);
    puVar62 = &DAT_100b0b750;
    FUN_100021774(&DAT_100b0b750);
    FUN_1007e61b4(&DAT_100b0b758,FUN_100778250,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar57 = local_678[1];
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220,puVar62);
    mVar38 = local_700[2];
    (**(code **)((long)local_680 + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.count = dStack_21c;
    local_190.entsizeAndFlags = local_220;
    FUN_100186100(&local_190);
    break;
  case (undefined **)0x9:
    local_190.entsizeAndFlags._0_1_ = 9;
    mVar38 = self_01;
    FUN_1007e1070();
    lVar39 = local_3c0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3c0,&DAT_100a68ff8,&local_190,mVar31,&DAT_100a68ff8,mVar38);
    puVar62 = &DAT_100b0b750;
    FUN_100021774(&DAT_100b0b750);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    puVar40 = &DAT_100b0b758;
    FUN_1007e61b4(&DAT_100b0b758,FUN_100778250,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar57 = local_678[0xb];
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,puVar62,&local_190,local_678[0xb],puVar62,puVar40);
    mVar38 = local_700[2];
    local_2c0.count = dStack_21c;
    local_2c0.entsizeAndFlags = local_220;
    puVar62 = &DAT_100b0b700;
    FUN_100021774(&DAT_100b0b700);
    local_191 = 1;
    puVar40 = &DAT_100b0b708;
    FUN_1007e6228(&DAT_100b0b708,FUN_100778068,PTR___sSayxGSesSeRzlMc_100a1dd38);
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_2a0,puVar62,&local_191,puVar57,puVar62,puVar40);
    (**(code **)((long)local_678[9] + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = local_2c0;
    mStack_188 = local_2a0;
    FUN_10048fd9c(&local_190);
    goto LAB_1007e5be0;
  case (undefined **)0xa:
    local_190.entsizeAndFlags._0_1_ = 10;
    mVar38 = self_01;
    FUN_1007e1030();
    lVar39 = local_3e0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3e0,&DAT_100a69088,&local_190,mVar31,&DAT_100a69088,mVar38);
    puVar62 = &DAT_100af9d40;
    FUN_100021774(&DAT_100af9d40);
    FUN_100778344(&DAT_100b0b770,PTR___ss5Int32VSesWP_100a1df38,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar57 = local_678[4];
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220,puVar62);
    mVar38 = local_700[2];
    (**(code **)((long)local_678[2] + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.count = dStack_21c;
    local_190.entsizeAndFlags = local_220;
    FUN_1004171b0(&local_190);
    break;
  case (undefined **)0xb:
    local_190.entsizeAndFlags._0_1_ = 0xb;
    mVar38 = self_01;
    FUN_1007e0fb0();
    lVar39 = local_3d8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3d8,&DAT_100a69118,&local_190,mVar31,&DAT_100a69118,mVar38);
    FUN_1007e6174();
    puVar62 = local_678[5];
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)((long)local_678[3] + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = (undefined1)local_220;
    local_190.count = dStack_21c;
    mStack_188 = mStack_218;
    local_180.entsizeAndFlags._0_1_ = local_210;
    local_178 = local_208;
    local_170.entsizeAndFlags._1_1_ = uStack_1ff;
    local_170.entsizeAndFlags._0_1_ = local_200;
    FUN_10050d524(&local_190);
    break;
  case (undefined **)0xc:
    local_190.entsizeAndFlags._0_1_ = 0xc;
    mVar38 = self_01;
    FUN_1007e0f70();
    lVar39 = local_3d0;
    uVar22 = 0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3d0,&DAT_100a691a8,&local_190,mVar31,&DAT_100a691a8,mVar38);
    puVar62 = local_678[7];
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF();
    mVar38 = local_700[2];
    (**(code **)((long)local_678[6] + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,uVar22) & 0xffffffffffffff01);
    FUN_10026fb28(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0xd:
    local_190.entsizeAndFlags._0_1_ = 0xd;
    mVar38 = self_01;
    FUN_1007e0f30();
    lVar39 = local_3c8;
    uVar22 = 0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3c8,&DAT_100a69238,&local_190,mVar31,&DAT_100a69238,mVar38);
    puVar62 = local_678[10];
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF();
    mVar38 = local_700[2];
    (**(code **)((long)local_678[8] + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,uVar22) & 0xffffffffffffff01);
    FUN_10026faac(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0xe:
    local_190.entsizeAndFlags._0_1_ = 0xe;
    mVar38 = self_01;
    FUN_1007e0ef0();
    lVar39 = local_3b8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3b8,&DAT_100a692c8,&local_190,mVar31,&DAT_100a692c8,mVar38);
    puVar62 = local_678[0xd];
    __ss22KeyedDecodingContainerV6decode_6forKeyS2dm_xtKF();
    mVar38 = local_700[2];
    (**(code **)((long)local_678[0xc] + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = param_2;
    FUN_10026fa8c(&local_190);
    break;
  case (undefined **)0xf:
    local_190.entsizeAndFlags._0_1_ = 0xf;
    mVar38 = self_01;
    FUN_1007e0eb0();
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (puVar40,&DAT_100a69358,&local_190,mVar31,&DAT_100a69358,mVar38);
    puVar62 = local_600;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2dm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_608 + 8))(puVar40,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = param_2;
    FUN_1005ed7b0(&local_190);
    break;
  case (undefined **)0x10:
    local_190.entsizeAndFlags._0_1_ = 0x10;
    mVar38 = self_01;
    FUN_1007e0e70();
    lVar39 = local_3a8;
    uVar22 = 0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3a8,&DAT_100a693e8,&local_190,mVar31,&DAT_100a693e8,mVar38);
    puVar62 = local_5f0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_5f8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,uVar22) & 0xffffffffffffff01);
    FUN_10026fb44(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x11:
    local_190.entsizeAndFlags._0_1_ = 0x11;
    mVar52 = self_01;
    FUN_1007e0df0();
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (mVar38,&DAT_100a69478,&local_190,mVar31,&DAT_100a69478,mVar52);
    puVar62 = &DAT_100af52f8;
    FUN_100021774(&DAT_100af52f8);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    puVar57 = &DAT_100b0dca8;
    FUN_1007e6088(&DAT_100b0dca8,PTR___sSSSesWP_100a1dd00,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar36 = local_5c0;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,puVar62,&local_190,local_5c0,puVar62,puVar57);
    mVar52 = local_700[2];
    mVar35.count = dStack_21c;
    mVar35.entsizeAndFlags = local_220;
    local_191 = 1;
    FUN_1007e6134();
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_2a0,&DAT_100a2d410,&local_191,puVar36,&DAT_100a2d410,puVar62);
    (**(code **)(local_5d8 + 8))(mVar38,puVar36);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    mStack_188.entsizeAndFlags._0_1_ = (undefined1)local_2a0.entsizeAndFlags;
    local_190 = mVar35;
    FUN_100570968(&local_190);
    goto LAB_1007e5be0;
  case (undefined **)0x12:
    local_190.entsizeAndFlags._0_1_ = 0x12;
    local_2c0 = self_01;
    FUN_1007e0d70();
    lVar39 = local_3b0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3b0,&DAT_100a69508,&local_190,mVar31,&DAT_100a69508,self_01);
    puVar62 = &DAT_100af52f8;
    FUN_100021774(&DAT_100af52f8);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    puVar57 = &DAT_100b0dca8;
    FUN_1007e6088(&DAT_100b0dca8,PTR___sSSSesWP_100a1dd00,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar36 = local_5e0;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,puVar62,&local_190,local_5e0,puVar62,puVar57);
    mVar38 = local_700[2];
    mVar55.count = dStack_21c;
    mVar55.entsizeAndFlags = local_220;
    local_191 = 1;
    FUN_1007e60f4();
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_2a0,&DAT_100a2d380,&local_191,puVar36,&DAT_100a2d380,puVar62);
    (**(code **)(local_5b0 + 8))(lVar39,puVar36);
    _swift_unknownObjectRelease(local_2c0);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    mStack_188.entsizeAndFlags._0_1_ = (undefined1)local_2a0.entsizeAndFlags;
    local_190 = mVar55;
    FUN_10057094c(&local_190);
    goto LAB_1007e5be0;
  case (undefined **)0x13:
    local_190.entsizeAndFlags._0_1_ = 0x13;
    mVar38 = self_01;
    FUN_1007e0d30();
    lVar39 = local_380;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_380,&DAT_100a69598,&local_190,mVar31,&DAT_100a69598,mVar38);
    puVar62 = &DAT_100af52f8;
    FUN_100021774(&DAT_100af52f8);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    puVar57 = &DAT_100b0dca8;
    FUN_1007e6088(&DAT_100b0dca8,PTR___sSSSesWP_100a1dd00,PTR___sSayxGSesSeRzlMc_100a1dd38);
    puVar36 = local_580;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,puVar62,&local_190,local_580,puVar62,puVar57);
    mVar38 = local_700[2];
    mVar52.count = dStack_21c;
    mVar52.entsizeAndFlags = local_220;
    local_2a0.entsizeAndFlags._0_1_ = 1;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2dm_xtKF(&local_2a0,puVar36);
    (**(code **)(local_598 + 8))(lVar39,puVar36);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = mVar52;
    mStack_188 = param_2;
    FUN_100570138(&local_190);
    goto LAB_1007e5be0;
  case (undefined **)0x14:
    local_190.entsizeAndFlags._0_1_ = 0x14;
    mVar38 = self_01;
    FUN_1007e0cb0();
    lVar39 = local_3a0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_3a0,&DAT_100a69628,&local_190,mVar31,&DAT_100a69628,mVar38);
    FUN_1007e6048();
    puVar62 = local_5d0;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)(local_5e8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = (undefined1)local_220;
    FUN_100475410(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x15:
    local_190.entsizeAndFlags._0_1_ = 0x15;
    mVar52 = self_01;
    FUN_1007e0c70();
    lVar39 = local_398;
    mVar38 = (method_list_t)&DAT_100a696b8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_398,&DAT_100a696b8,&local_190,mVar31,&DAT_100a696b8,mVar52);
    puVar62 = local_5b8;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF();
    mVar52 = local_700[2];
    (**(code **)(local_5c8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = mVar38;
    FUN_1005b9d50(&local_190);
    break;
  case (undefined **)0x16:
    local_190.entsizeAndFlags._0_1_ = 0x16;
    mVar38 = self_01;
    FUN_1007e0c30();
    lVar39 = local_388;
    dVar59 = 0xa69748;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_388,&DAT_100a69748,&local_190,mVar31,&DAT_100a69748,mVar38);
    puVar62 = local_588;
    __ss22KeyedDecodingContainerV6decode_6forKeys5Int32VAFm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_5a0 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags = dVar59;
    FUN_1003a40dc(&local_190);
    break;
  case (undefined **)0x17:
    local_220 = CONCAT31(local_220._1_3_,0x17);
    mVar38 = self_01;
    FUN_1007e0bf0();
    lVar39 = local_390;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_390,&DAT_100a69768,&local_220,mVar31,&DAT_100a69768,mVar38);
    (**(code **)(local_5a8 + 8))(lVar39,local_590);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_100490120(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x18:
    local_190.entsizeAndFlags._0_1_ = 0x18;
    mVar38 = self_01;
    FUN_1007e0bb0();
    lVar39 = local_378;
    dVar59 = 0xa697f8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_378,&DAT_100a697f8,&local_190,mVar31,&DAT_100a697f8,mVar38);
    puVar62 = local_570;
    __ss22KeyedDecodingContainerV6decode_6forKeys5Int32VAFm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_578 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags = dVar59;
    FUN_1003a40c0(&local_190);
    break;
  case (undefined **)0x19:
    local_190.entsizeAndFlags._0_1_ = 0x19;
    mVar38 = self_01;
    FUN_1007e0b70();
    lVar39 = local_370;
    puVar62 = &DAT_100a69888;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_370,&DAT_100a69888,&local_190,mVar31,&DAT_100a69888,mVar38);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    FUN_100277d74();
    puVar57 = local_550;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,&DAT_100a55c38,&local_190,local_550,&DAT_100a55c38,puVar62);
    mVar52 = local_700[2];
    uVar22 = (undefined1)local_220;
    local_2a0.entsizeAndFlags._0_1_ = 1;
    mVar38 = (method_list_t)&local_2a0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF(mVar38,puVar57);
    local_2c0 = mVar38;
    (**(code **)(local_568 + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = uVar22;
    mStack_188 = local_2c0;
    FUN_100042a90(&local_190);
    break;
  case (undefined **)0x1a:
    local_190.entsizeAndFlags._0_1_ = 0x1a;
    mVar38 = self_01;
    FUN_1007e0b30();
    lVar39 = local_360;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_360,&DAT_100a69918,&local_190,mVar31,&DAT_100a69918,mVar38);
    puVar62 = local_540;
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    pmVar24 = &local_190;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF(pmVar24,local_540);
    mVar52 = local_700[2];
    local_220 = CONCAT31(local_220._1_3_,1);
    mVar38 = (method_list_t)&local_220;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF(mVar38,puVar62);
    local_2c0 = mVar38;
    (**(code **)(local_560 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,(char)pmVar24) & 0xffffffffffffff01);
    mStack_188 = local_2c0;
    FUN_1000429f0(&local_190);
    break;
  case (undefined **)0x1b:
    local_190.entsizeAndFlags._0_1_ = 0x1b;
    mVar38 = self_01;
    FUN_1007e0af0();
    lVar39 = local_368;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_368,&DAT_100a699a8,&local_190,mVar31,&DAT_100a699a8,mVar38);
    FUN_100778d48();
    puVar62 = local_548;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)(local_558 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = (undefined1)local_220;
    FUN_10067cfa8(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x1c:
    local_190.entsizeAndFlags._0_1_ = 0x1c;
    mVar38 = self_01;
    FUN_1007e0ab0();
    lVar39 = local_350;
    puVar62 = &DAT_100a69a38;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_350,&DAT_100a69a38,&local_190,mVar31,&DAT_100a69a38,mVar38);
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    FUN_100778ebc();
    puVar57 = local_518;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
              (&local_220,&DAT_100a52cb8,&local_190,local_518,&DAT_100a52cb8,puVar62);
    mVar38 = local_700[2];
    local_2c0 = (method_list_t)(CONCAT44(local_2c0.count,local_220) & 0xffffffff000000ff);
    local_2a0.entsizeAndFlags._0_1_ = 1;
    pmVar24 = &local_2a0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF(pmVar24,puVar57);
    (**(code **)(local_528 + 8))(lVar39,puVar57);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)
                (CONCAT62(local_190._2_6_,CONCAT11((char)pmVar24,(char)local_2c0.entsizeAndFlags)) &
                0xffffffffffff01ff);
    FUN_1000931c8(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x1d:
    local_190.entsizeAndFlags._0_1_ = 0x1d;
    mVar38 = self_01;
    FUN_1007e0a70();
    lVar39 = local_358;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_358,&DAT_100a69ac8,&local_190,mVar31,&DAT_100a69ac8,mVar38);
    FUN_100586e48();
    puVar62 = local_530;
    __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)(local_538 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = (undefined1)local_220;
    FUN_100092520(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x1e:
    local_190.entsizeAndFlags._0_1_ = 0x1e;
    mVar38 = self_01;
    FUN_1007e09f0();
    lVar39 = local_348;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_348,&DAT_100a69b58,&local_190,mVar31,&DAT_100a69b58,mVar38);
    FUN_1007e5fec();
    puVar62 = local_510;
    __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF(&local_220);
    mVar38 = local_700[2];
    (**(code **)(local_520 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags._0_1_ = (undefined1)local_220;
    FUN_1007e602c(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x1f:
    local_190.entsizeAndFlags._0_1_ = 0x1f;
    mVar52 = self_01;
    FUN_1007e09b0();
    lVar39 = local_338;
    mVar38 = (method_list_t)&DAT_100a69be8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_338,&DAT_100a69be8,&local_190,mVar31,&DAT_100a69be8,mVar52);
    puVar62 = local_4f0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF();
    mVar52 = local_700[2];
    (**(code **)(local_500 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = mVar38;
    FUN_1007e5fcc(&local_190);
    break;
  case (undefined **)0x20:
    local_220 = CONCAT31(local_220._1_3_,0x20);
    mVar38 = self_01;
    FUN_1007e0970();
    lVar39 = local_340;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_340,&DAT_100a69c08,&local_220,mVar31,&DAT_100a69c08,mVar38);
    (**(code **)(local_508 + 8))(lVar39,local_4f8);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e5f94(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x21:
    local_190.entsizeAndFlags._0_1_ = 0x21;
    mVar38 = self_01;
    FUN_1007e0930();
    lVar39 = local_330;
    uVar22 = 0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_330,&DAT_100a69c98,&local_190,mVar31,&DAT_100a69c98,mVar38);
    puVar62 = local_4e0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_4e8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,uVar22) & 0xffffffffffffff01);
    FUN_1007e5f78(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x22:
    local_190.entsizeAndFlags._0_1_ = 0x22;
    mVar38 = self_01;
    FUN_1007e08f0();
    lVar39 = local_320;
    uVar22 = 0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_320,&DAT_100a69d28,&local_190,mVar31,&DAT_100a69d28,mVar38);
    puVar62 = local_4c0;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_4d8 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)(CONCAT71(local_190._1_7_,uVar22) & 0xffffffffffffff01);
    FUN_1007e5f60(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x23:
    local_220 = CONCAT31(local_220._1_3_,0x23);
    mVar38 = self_01;
    FUN_1007e08b0();
    lVar39 = local_328;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_328,&DAT_100a69d48,&local_220,mVar31,&DAT_100a69d48,mVar38);
    (**(code **)(local_4d0 + 8))(lVar39,local_4c8);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e5f28(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x24:
    local_220 = CONCAT31(local_220._1_3_,0x24);
    mVar38 = self_01;
    FUN_1007e0870();
    lVar39 = local_318;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_318,&DAT_100a69d68,&local_220,mVar31,&DAT_100a69d68,mVar38);
    (**(code **)(local_4b8 + 8))(lVar39,local_4b0);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e5ef0(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x26:
    local_220 = CONCAT31(local_220._1_3_,0x26);
    mVar38 = self_01;
    FUN_1007e07f0();
    lVar39 = local_308;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_308,&DAT_100a69da8,&local_220,mVar31,&DAT_100a69da8,mVar38);
    (**(code **)(local_498 + 8))(lVar39,local_490);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e5e80(&local_190);
    goto LAB_1007e5cd8;
  case (undefined **)0x27:
    local_190.entsizeAndFlags._0_1_ = 0x27;
    mVar52 = self_01;
    FUN_1007e07b0();
    lVar39 = local_300;
    mVar38 = (method_list_t)&DAT_100a69e38;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_300,&DAT_100a69e38,&local_190,mVar31,&DAT_100a69e38,mVar52);
    puVar62 = local_480;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2im_xtKF();
    mVar52 = local_700[2];
    (**(code **)(local_488 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
    local_190 = mVar38;
    FUN_1007e5e68(&local_190);
    break;
  case (undefined **)0x28:
    local_190.entsizeAndFlags._0_1_ = 0x28;
    mVar38 = self_01;
    FUN_1007e0770();
    lVar39 = local_2f8;
    dVar59 = 0xa69ec8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_2f8,&DAT_100a69ec8,&local_190,mVar31,&DAT_100a69ec8,mVar38);
    puVar62 = local_470;
    __ss22KeyedDecodingContainerV6decode_6forKeys5Int32VAFm_xtKF();
    mVar38 = local_700[2];
    (**(code **)(local_478 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190.entsizeAndFlags = dVar59;
    FUN_10003beb4(&local_190);
    break;
  case (undefined **)0x29:
    local_190.entsizeAndFlags._0_1_ = 0x29;
    mVar38 = self_01;
    FUN_1007e0730();
    lVar39 = local_2f0;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_2f0,&DAT_100a69f58,&local_190,mVar31,&DAT_100a69f58,mVar38);
    puVar62 = local_450;
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    pmVar24 = &local_190;
    __ss22KeyedDecodingContainerV6decode_6forKeys5Int32VAFm_xtKF(pmVar24,local_450);
    mVar38 = local_700[2];
    local_2c0.entsizeAndFlags = (dword)pmVar24;
    local_220 = CONCAT31(local_220._1_3_,1);
    pdVar25 = &local_220;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF(pdVar25,puVar62);
    (**(code **)(local_468 + 8))(lVar39,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)
                (CONCAT35(local_190.count._1_3_,CONCAT14((char)pdVar25,local_2c0.entsizeAndFlags)) &
                0xffffff01ffffffff);
    FUN_1000f9f00(&local_190);
LAB_1007e5be0:
    uStack_88 = CONCAT11(uStack_117,uStack_118);
    mStack_98 = mStack_128;
    local_a0 = local_130;
    mStack_90 = local_120;
    uStack_7e = (undefined6)uStack_10e;
    uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
    local_86 = uStack_116;
    uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
    mStack_d8 = mStack_168;
    local_e0 = local_170;
    mStack_c8 = mStack_158;
    mStack_d0 = mStack_160;
    local_c0.super_class = pcStack_148;
    local_c0.receiver._0_4_ = local_150.entsizeAndFlags;
    local_c0.receiver._4_4_ = local_150.count;
    local_b0.super_class = (class_t *)mStack_138;
    local_b0.receiver._0_4_ = local_140.entsizeAndFlags;
    local_b0.receiver._4_4_ = local_140.count;
    mVar52 = local_2d8;
    local_100 = local_190;
    mStack_f8 = mStack_188;
    mStack_f0 = local_180;
    mStack_e8 = local_178;
    goto LAB_1007e5d88;
  case (undefined **)0x2a:
    local_190.entsizeAndFlags._0_1_ = 0x2a;
    mVar38 = self_01;
    FUN_1007e06f0();
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (mVar52,&DAT_100a69fe8,&local_190,mVar31,&DAT_100a69fe8,mVar38);
    puVar62 = local_438;
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
    pmVar24 = &local_190;
    __ss22KeyedDecodingContainerV6decode_6forKeys5Int32VAFm_xtKF(pmVar24,local_438);
    mVar38 = local_700[2];
    local_2c8.entsizeAndFlags = (dword)pmVar24;
    local_220 = CONCAT31(local_220._1_3_,1);
    pdVar25 = &local_220;
    __ss22KeyedDecodingContainerV6decode_6forKeyS2bm_xtKF(pdVar25,puVar62);
    (**(code **)(local_430 + 8))(mVar52,puVar62);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)mVar38 + 8))(mVar65,mVar31);
    local_190 = (method_list_t)
                (CONCAT35(local_190.count._1_3_,CONCAT14((char)pdVar25,local_2c8.entsizeAndFlags)) &
                0xffffff01ffffffff);
    FUN_1007e5e4c(&local_190);
    uStack_88 = CONCAT11(uStack_117,uStack_118);
    mStack_98 = mStack_128;
    local_a0 = local_130;
    mStack_90 = local_120;
    uStack_7e = (undefined6)uStack_10e;
    uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
    local_86 = uStack_116;
    uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
    mStack_d8 = mStack_168;
    local_e0 = local_170;
    mStack_c8 = mStack_158;
    mStack_d0 = mStack_160;
    local_c0.super_class = pcStack_148;
    local_c0.receiver._0_4_ = local_150.entsizeAndFlags;
    local_c0.receiver._4_4_ = local_150.count;
    local_b0.super_class = (class_t *)mStack_138;
    local_b0.receiver._0_4_ = local_140.entsizeAndFlags;
    local_b0.receiver._4_4_ = local_140.count;
    mStack_f8 = mStack_188;
    local_100 = local_190;
    mStack_e8 = local_178;
    mStack_f0 = local_180;
    mVar52 = local_2d8;
    goto LAB_1007e5d88;
  case (undefined **)0x2b:
    local_190.entsizeAndFlags._0_1_ = 0x2b;
    FUN_1007e06b0();
    ppuVar41 = (undefined **)local_2e0;
    mVar68 = mVar31;
    mVar38 = local_2e0;
    goto switchD_1007e3574_caseD_30;
  case (undefined **)0x2c:
    local_220 = CONCAT31(local_220._1_3_,0x2c);
    mVar38 = self_01;
    FUN_1007e0670();
    lVar39 = local_2e8;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_2e8,&DAT_100a6a0b8,&local_220,mVar31,&DAT_100a6a0b8,mVar38);
    (**(code **)(local_460 + 8))(lVar39,local_448);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_100417460(&local_190);
LAB_1007e5cd8:
    uStack_88 = CONCAT11(uStack_117,uStack_118);
    mStack_98 = mStack_128;
    local_a0 = local_130;
    mStack_90 = local_120;
    uStack_7e = (undefined6)uStack_10e;
    uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
    local_86 = uStack_116;
    uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
    mStack_d8 = mStack_168;
    local_e0 = local_170;
    mStack_c8 = mStack_158;
    mStack_d0 = mStack_160;
    local_c0.super_class = pcStack_148;
    local_c0.receiver._0_4_ = local_150.entsizeAndFlags;
    local_c0.receiver._4_4_ = local_150.count;
    local_b0.super_class = (class_t *)mStack_138;
    local_b0.receiver._0_4_ = local_140.entsizeAndFlags;
    local_b0.receiver._4_4_ = local_140.count;
    mVar52 = local_2d8;
    local_100 = local_190;
    mStack_f8 = mStack_188;
    mStack_f0 = local_180;
    mStack_e8 = local_178;
    goto LAB_1007e5d88;
  case (undefined **)0x2e:
  case (undefined **)0x6b:
  case (undefined **)0x7a:
    goto switchD_1007e3574_caseD_2e;
  case (undefined **)0x2f:
    if (*(ID *)(*(undefined **)((long)ppuVar41 + 0x1a8) + (long)self_01) != 0) {
      pcVar34 = "rootViewController";
      IVar27 = _objc_msgSend(*(ID *)(*(undefined **)((long)ppuVar41 + 0x1a8) + (long)self_01),
                             "rootViewController");
      if (IVar27 != 0) {
        self_01.entsizeAndFlags = 0;
        self_01.count = 0;
        FUN_100413a94(0);
        goto switchD_1007e3574_caseD_62;
      }
    }
    _swift_unknownObjectRelease(mVar65);
    auVar86._8_4_ = (dword)pcVar34;
    auVar86._12_4_ = SUB84(pcVar34,4);
    auVar86._0_4_ = mVar65.entsizeAndFlags;
    auVar86._4_4_ = mVar65.count;
    return auVar86;
  case (undefined **)0x30:
    goto switchD_1007e3574_caseD_30;
  case (undefined **)0x31:
switchD_1007e3574_caseD_31:
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    mVar31 = (method_list_t)_objc_msgSend((ID)self_00,"initWithEntityName:",mVar58);
    if (DAT_100ade9d8 != -1) {
      _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
    }
    _objc_msgSend(DAT_100b755c8,"viewContext");
    uVar28 = 0;
    FUN_10056a2a0(0);
    __sSo22NSManagedObjectContextC8CoreDataE5fetchySayxGSo14NSFetchRequestCyxGKSo0gH6ResultRzlF
              (mVar31,uVar28);
    if (puVar57 != (undefined *)0x0) {
      _swift_errorRelease(puVar57);
switchD_1007e3574_caseD_d2:
      mVar31 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
      _swift_retain();
      puVar57 = (undefined *)0x0;
    }
    mVar58 = DAT_100b05f70;
    DAT_100b05f70 = mVar31;
    _swift_bridgeObjectRetain(mVar31);
    _swift_bridgeObjectRelease(mVar58);
    if ((ulong)mVar31 >> 0x3e == 0) goto LAB_1007ffda8;
LAB_1007fffbc:
    mVar58 = (method_list_t)((ulong)mVar31 & 0xffffffffffffff8);
    if ((long)mVar31 < 0) {
      mVar58 = mVar31;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
    if (mVar58 != (method_list_t)0x0) goto LAB_1007ffdb4;
    do {
      _swift_bridgeObjectRetain(mVar55);
      _swift_bridgeObjectRelease(mVar31);
      while( true ) {
        if (DAT_100ade9d8 != -1) {
          _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
        }
        pcVar34 = "viewContext";
        IVar27 = _objc_msgSend(DAT_100b755c8,"viewContext");
        FUN_1000f0934(IVar27);
        if (mVar38 == *(method_list_t *)((long)mVar65 + 0x28)) {
          _swift_bridgeObjectRelease(mVar52);
          mVar68 = *(method_list_t *)mVar65;
          goto LAB_10080013c;
        }
LAB_1007ffb80:
        if (*(undefined **)((long)mVar65 + 0x20) == (undefined *)0x0) {
          self_02 = *(method_list_t *)(*(undefined **)((long)mVar65 + 8) + (long)mVar38 * 8);
        }
        else {
          self_02 = mVar38;
          FUN_1000cbf0c(mVar38,mVar52);
        }
        bVar21 = SCARRY8((long)mVar38,1);
        mVar38 = (method_list_t)((long)mVar38 + 1);
        if (bVar21) {
                    /* WARNING: Does not return */
          pcVar20 = (code *)SoftwareBreakpoint(1,0x1008001c4);
          (*pcVar20)();
        }
        uVar28 = 1;
        __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(1);
        _objc_msgSend((ID)self_02,"setStoredPlayGuideCue:",uVar28);
        uVar28 = 0;
        __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(0);
        _objc_msgSend((ID)self_02,"setStoredPlayCountIn:",uVar28);
        IVar27 = _objc_msgSend((ID)self_02,*(undefined **)((long)self_01 + 0xac8));
        dVar74 = 0.0;
        dVar72 = 0.0;
        if (IVar27 != 0) {
          IVar27 = _objc_msgSend(IVar27,"song");
          dVar70 = 0.0;
          dVar72 = dVar70;
          if (IVar27 != 0) {
            IVar29 = _objc_msgSend(IVar27,"contentTypeID");
            uVar54 = (uint)IVar29;
            FUN_100419df0();
            if ((((uVar54 & 0xfe) == 0x10) || (_objc_msgSend(IVar27,"bpm"), dVar70 < unaff_d11)) ||
               (_objc_msgSend(IVar27,"bpmOriginal"), dVar70 < unaff_d11)) {
              dVar72 = 0.0;
            }
            else {
              _objc_msgSend(IVar27,"bpmOriginal");
              dVar71 = dVar70;
              _objc_msgSend(IVar27,"bpm");
              dVar72 = 0.0;
              if ((dVar70 / dVar71 != 0.0) && (dVar72 = unaff_d12 / (dVar70 / dVar71), dVar72 < 0.0)
                 ) {
                dVar72 = unaff_d12;
              }
            }
          }
        }
        _objc_msgSend((ID)self_02,"setStoredStartTimeTrimOffset:");
        pcVar20 = (code *)((long)self_02 + _TtC8Playback11SongSection::transientStartTimeTrimOffset)
        ;
        *(undefined8 *)pcVar20 = 0;
        pcVar20[8] = mVar68.entsizeAndFlags._0_1_;
        IVar27 = _objc_msgSend((ID)self_02,*(undefined **)((long)self_01 + 0xac8));
        if ((IVar27 != 0) && (IVar27 = _objc_msgSend(IVar27,"song"), IVar27 != 0)) {
          IVar29 = _objc_msgSend(IVar27,"contentTypeID");
          uVar54 = (uint)IVar29;
          FUN_100419df0();
          if (((uVar54 & 0xfe) != 0x10) &&
             ((_objc_msgSend(IVar27,"bpm"), unaff_d11 <= dVar72 &&
              (_objc_msgSend(IVar27,"bpmOriginal"), unaff_d11 <= dVar72)))) {
            _objc_msgSend(IVar27,"bpmOriginal");
            dVar70 = dVar72;
            _objc_msgSend(IVar27,"bpm");
            if ((dVar72 / dVar70 != 0.0) && (dVar74 = unaff_d12 / (dVar72 / dVar70), dVar74 < 0.0))
            {
              dVar74 = unaff_d12;
            }
          }
        }
        _objc_msgSend((ID)self_02,"setStoredEndTimeTrimOffset:",dVar74);
        pcVar20 = (code *)((long)self_02 + _TtC8Playback11SongSection::transientEndTimeTrimOffset);
        *(undefined8 *)pcVar20 = 0;
        pcVar20[8] = mVar68.entsizeAndFlags._0_1_;
        mVar55 = DAT_100b05f70;
        if (DAT_100b05f70 == (method_list_t)0x0) {
          self_00 = (protocol_list_t *)&_OBJC_CLASS___NSFetchRequest;
          _objc_allocWithZone();
          mVar58.entsizeAndFlags = 0x6174654d;
          mVar58.count = 0x61746164;
          goto switchD_1007e3574_caseD_31;
        }
        mVar31 = DAT_100b05f70;
        if ((ulong)DAT_100b05f70 >> 0x3e != 0) goto LAB_1007fffbc;
LAB_1007ffda8:
        mVar58 = *(method_list_t *)(((ulong)mVar31 & 0xfffffffffffff8) + 0x10);
        if (mVar58 == (method_list_t)0x0) break;
LAB_1007ffdb4:
        *(undefined **)((long)mVar65 + 0x30) = puVar57;
        _swift_bridgeObjectRetain(mVar55);
        _swift_bridgeObjectRetain(mVar31);
        lVar39 = 4;
        do {
          mVar52 = (method_list_t)(lVar39 + -4);
          if (((ulong)mVar31 & 0xc000000000000001) == 0) {
            mVar68 = *(method_list_t *)((long)mVar31 + lVar39 * 8);
          }
          else {
            mVar68 = mVar52;
            FUN_1000cd490(mVar52,mVar31);
          }
          mVar1 = (method_list_t)(lVar39 + -3);
          if (SCARRY8((long)mVar52,1)) {
                    /* WARNING: Does not return */
            pcVar20 = (code *)SoftwareBreakpoint(1,0x1008001c0);
            (*pcVar20)();
          }
          IVar27 = _objc_msgSend((ID)mVar68,"partID");
          IVar29 = _objc_msgSend((ID)self_02,"storedSectionType");
          if ((int)IVar27 == (int)IVar29) {
            _swift_bridgeObjectRelease_n(mVar31,2);
            uVar28 = *(undefined8 *)
                      ((long)self_02 + _TtC8Playback11SongSection::___lazy_storage___metadataSection
                      );
            *(method_list_t *)
             ((long)self_02 + _TtC8Playback11SongSection::___lazy_storage___metadataSection) =
                 mVar68;
            FUN_10003995c(uVar28);
            _objc_msgSend((ID)self_02,"setEditedSectionTypeID:",0);
            goto LAB_1007fff70;
          }
          lVar39 = lVar39 + 1;
        } while (mVar1 != mVar58);
        _swift_bridgeObjectRelease_n(mVar31,2);
LAB_1007fff70:
        mVar52 = *(method_list_t *)((long)mVar65 + 0x10);
        mVar68.entsizeAndFlags = 1;
        mVar68.count = 0;
        puVar57 = *(undefined **)((long)mVar65 + 0x30);
      }
    } while( true );
  case (undefined **)0x32:
  case (undefined **)0xf2:
    __swift_stdlib_reportUnimplementedInitializer();
                    /* WARNING: Does not return */
    pcVar20 = (code *)SoftwareBreakpoint(1,0x1007fbb50);
    (*pcVar20)();
  case (undefined **)0x33:
    goto switchD_1007e3574_caseD_33;
  case (undefined **)0x34:
  case (undefined **)0x6e:
  case (undefined **)0xa7:
switchD_1007e3574_caseD_8e:
    __swift_stdlib_reportUnimplementedInitializer();
                    /* WARNING: Does not return */
    pcVar20 = (code *)SoftwareBreakpoint(1,0x100800324);
    (*pcVar20)();
  case (undefined **)0x35:
  case (undefined **)0x8b:
  case (undefined **)0xa2:
  case (undefined **)0xbd:
    goto switchD_1007e3574_caseD_35;
  case (undefined **)0x36:
  case (undefined **)0x25:
    cVar37 = (code)0x25;
  case (undefined **)0x74:
  case (undefined **)0xaf:
  case (undefined **)0xc7:
  case (undefined **)0xdb:
  case (undefined **)0xeb:
    local_220 = CONCAT31(local_220._1_3_,cVar37);
    mVar38 = self_01;
    FUN_1007e0830();
    lVar39 = local_310;
    __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
              (local_310,&DAT_100a69d88,&local_220,mVar31,&DAT_100a69d88,mVar38);
    (**(code **)(local_4a8 + 8))(lVar39,local_4a0);
    _swift_unknownObjectRelease(self_01);
    (**(code **)((long)local_700[2] + 8))(mVar65,mVar31);
    FUN_1007e5eb8(&local_190);
    goto LAB_1007e5cd8;
  default:
    local_190 = (method_list_t)((ulong)local_190 & 0xffffffffffffff00);
  case (undefined **)0x40:
  case (undefined **)0x47:
  case (undefined **)0x54:
  case (undefined **)0x5b:
    FUN_1007e12f0();
    goto switchD_1007e3574_caseD_3f;
  case (undefined **)0x38:
    goto switchD_1007e3574_caseD_38;
  case (undefined **)0x39:
  case (undefined **)0x43:
  case (undefined **)0x4d:
  case (undefined **)0x57:
    goto switchD_1007e3574_caseD_39;
  case (undefined **)0x3a:
    goto switchD_1007e3574_caseD_3a;
  case (undefined **)0x3b:
  case (undefined **)0x4f:
    goto switchD_1007e3574_caseD_3b;
  case (undefined **)0x3f:
  case (undefined **)0x53:
    goto switchD_1007e3574_caseD_3f;
  case (undefined **)0x42:
    goto switchD_1007e3574_caseD_42;
  case (undefined **)0x44:
    auVar95._8_4_ = (dword)pcVar34;
    auVar95._12_4_ = SUB84(pcVar34,4);
    auVar95._0_4_ = self_01.entsizeAndFlags;
    auVar95._4_4_ = self_01.count;
    return auVar95;
  case (undefined **)0x45:
  case (undefined **)0x59:
    _objc_msgSend((ID)self_01,"setStoredSampleTimecode:");
    _objc_msgSend((ID)self_01,"setStoredSequenceTimecode:",mStack_1f8);
    _objc_msgSend((ID)self_01,"setTransitionBeats:",(long)sStack_1f0);
    pcVar34 = "setApplyTransitionLengthCorrection:";
    _objc_msgSend((ID)self_01,"setApplyTransitionLengthCorrection:",(ulong)(local_1e0 & 1));
    uStack_78 = (undefined2)mStack_1e8.entsizeAndFlags;
    uStack_76 = mStack_1e8._2_6_;
    lVar39 = *(long *)((long)mStack_1e8 + 0x10);
    if (lVar39 == 0) {
      _swift_bridgeObjectRetain(mStack_1e8);
    }
    else {
      IVar27 = 0;
      mStack_90 = mVar68;
      FUN_1003ac3f8();
      _swift_bridgeObjectRetain_n(mStack_1e8,2);
      puVar40 = (undefined8 *)((long)mStack_1e8 + 0x30);
      do {
        uVar28 = puVar40[-2];
        uVar26 = puVar40[-1];
        uVar75 = *puVar40;
        IVar29 = IVar27;
        _objc_allocWithZone();
        puVar62 = *(undefined **)((long)mVar38 + 0x5c8);
        _swift_bridgeObjectRetain_n(uVar26,2);
        IVar32 = _objc_msgSend((ID)puVar62,pcRam00000000000009b0);
        IVar29 = _objc_msgSend(IVar29,"initWithContext:",IVar32);
        _swift_bridgeObjectRetain(uVar26);
        __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar28,uVar26);
        _swift_bridgeObjectRelease(uVar26);
        _objc_msgSend(IVar29,"setAutomationID:",uVar28);
        _objc_msgSend(IVar29,"setStoredValue:",uVar75);
        _swift_bridgeObjectRelease(uVar26);
        pcVar34 = "addStoredItemsObject:";
        _objc_msgSend((ID)self_01,"addStoredItemsObject:",IVar29);
        _swift_bridgeObjectRelease(uVar26);
        lVar39 = lVar39 + -1;
        puVar40 = puVar40 + 3;
      } while (lVar39 != 0);
      FUN_1001d7e54(&uStack_78);
      mVar68 = mStack_90;
    }
    FUN_1002f9a58(mVar68);
    FUN_1001d7e54(&uStack_78);
    auVar97._8_8_ = pcVar34;
    auVar97._0_4_ = self_01.entsizeAndFlags;
    auVar97._4_4_ = self_01.count;
    return auVar97;
  case (undefined **)0x4a:
switchD_1007e3574_caseD_4a:
    (**(code **)((long)ppVar46 + 0x10))(mVar64);
    mVar38 = mVar64;
    __ss27_bridgeAnythingToObjectiveCyyXlxlF(mVar64,mVar65);
    (**(code **)((long)ppVar46 + 8))(mVar64,mVar65);
    ppuVar66 = &PTR__swift_weakDestroy_100aa0000;
    FUN_100023468(&local_a0);
    goto LAB_1007fe720;
  case (undefined **)0x4b:
  case (undefined **)0x5f:
    goto switchD_1007e3574_caseD_4b;
  case (undefined **)0x4c:
    *(undefined8 *)((long)mVar65 + -0x50) = unaff_d9;
    *(undefined **)((long)mVar65 + -0x48) = unaff_d8;
    *(method_list_t *)((long)mVar65 + -0x40) = mVar52;
    *(method_list_t *)((long)mVar65 + -0x38) = self_01;
    *(method_list_t *)((long)mVar65 + -0x30) = mVar68;
    *(undefined **)((long)mVar65 + -0x28) = (undefined *)0x0;
    *(method_list_t *)((long)mVar65 + -0x20) = mVar65;
    *(protocol_list_t **)((long)mVar65 + -0x18) = &pStack_710;
    *(undefined ***)((long)mVar65 + -0x10) = ppuVar66;
    *(undefined **)((long)mVar65 + -8) = (undefined *)0x1007e3538;
    mVar61.count = 0;
    mVar61.entsizeAndFlags = (uint)pcVar34 & 0xff;
    mVar58 = (method_list_t)_objc_msgSend((ID)self_01,"textLabel");
    mVar53 = self_01;
    mVar65 = param_3;
    goto switchD_1007e3574_caseD_42;
  case (undefined **)0x4e:
    _swift_getErrorValue(self_01);
    mVar31 = mStack_f0;
    mVar52 = mStack_e8;
    FUN_1002c33f8(mStack_f0,mStack_e8);
    mStack_128 = mVar38;
    local_120 = (method_list_t)&pStack_710;
    _swift_bridgeObjectRetain(&pStack_710);
    __sSS6appendyySSF(mVar31,mVar52);
    _swift_bridgeObjectRelease(&pStack_710);
    _swift_bridgeObjectRelease(mVar52);
    ppuVar41 = (undefined **)&stack0xffffffffffffffe0;
    mVar19 = mStack_128;
  case (undefined **)0xf3:
    self_01 = mVar19;
    mVar65 = *(method_list_t *)((long)ppuVar41 + -0x100);
    self.entsizeAndFlags = 0;
    self.count = 0;
    FUN_100497ca4();
    _swift_bridgeObjectRetain(0);
    _swift_bridgeObjectRetain(mVar65);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(mVar68,0);
    _swift_bridgeObjectRelease(0);
    mVar52 = mVar68;
switchD_1007e3574_caseD_3a:
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF();
    _swift_bridgeObjectRelease(mVar65);
    _swift_getObjCClassFromMetadata();
    IVar27 = _objc_msgSend((ID)self,"alertControllerWithTitle:message:preferredStyle:",mVar52,
                           self_01,1);
    if (DAT_100adf6d8 != -1) {
      _swift_once(&DAT_100adf6d8,FUN_10052eb50);
    }
    uVar26 = DAT_100b76c98;
    uVar28 = DAT_100b76c90;
    _swift_bridgeObjectRetain(DAT_100b76c98);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar28,uVar26);
    _swift_bridgeObjectRelease(uVar26);
    puVar62 = &_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    IVar29 = _objc_msgSend((ID)puVar62,"actionWithTitle:style:handler:",uVar28,0,0);
    _objc_msgSend(IVar27,"addAction:",IVar29);
    _objc_msgSend(IVar27,"setPreferredAction:",IVar29);
    _swift_bridgeObjectRelease(mVar65);
    _swift_bridgeObjectRelease(0);
    pcVar34 = "presentViewController:animated:completion:";
    _objc_msgSend((ID)local_130,"presentViewController:animated:completion:",IVar27,1,0);
    auVar5._8_8_ = 0;
    auVar5._0_8_ = pcVar34;
    return auVar5 << 0x40;
  case (undefined **)0x56:
    goto LAB_100800930;
  case (undefined **)0x58:
    *(undefined **)((long)self_01 + 0x38) = PTR___sSSN_100a1dce0;
    FUN_100026528();
    uVar28 = 0x20;
    _DAT_00000020 = mVar52;
    uRam0000000000000028 = 0xe600000000000000;
    mRam0000000000000040 = self_01;
    _swift_getErrorValue(mVar65,(undefined **)((long)mVar65 + 0x18),mVar65);
    puVar57 = *(undefined **)((long)mVar65 + 8);
    puVar36 = *(undefined **)((long)mVar65 + 0x10);
    FUN_1002c2c2c();
    puRam0000000000000060 = puVar62;
    _DAT_00000048 = puVar57;
    _DAT_00000050 = puVar36;
    _DAT_00000068 = self_01;
    FUN_10041ac94(&pStack_710,0x72,"Error with Core Data All Instances %@: %@",0x29,2,0);
    _swift_setDeallocating(0);
    puVar62 = &DAT_100af5bc8;
    FUN_100021774(&DAT_100af5bc8);
    uVar26 = 2;
    _swift_arrayDestroy(0x20,2,puVar62);
    auVar96._8_8_ = uVar26;
    auVar96._0_8_ = uVar28;
    return auVar96;
  case (undefined **)0x5e:
    goto switchD_1007e3574_caseD_5e;
  case (undefined **)0x60:
  case (undefined **)0x7f:
  case (undefined **)0x93:
  case (undefined **)0xee:
  case (undefined **)0xf7:
  case (undefined **)0xfe:
    IVar27 = _objc_msgSend(puVar40[0xb9],"viewContext");
    FUN_1000f0934(IVar27);
    mVar68 = (method_list_t)&DAT_100a6b410;
    _swift_allocObject(&DAT_100a6b410,0x18,7);
    ((method_list_t *)((long)mVar68 + 0x10))->entsizeAndFlags = 0;
    ((method_list_t *)((long)mVar68 + 0x10))->count = 0;
    *(code **)((long)mVar65 + 8) = FUN_100801c04;
    self_02 = **(method_list_t **)((long)mVar38 + 0x828);
    mVar67 = *(method_list_t *)mVar52;
    mVar55 = *(method_list_t *)((long)mVar67 + (long)self_02);
    uVar56 = 0;
    thunk_FUN_1002db810(0x1e,PTR___swiftEmptyArrayStorage_100a1e050);
    puVar69 = &DAT_100ae0000;
    self_01 = (method_list_t)&DAT_100b0e000;
    if ((uVar56 & 1) == 0) {
      ppVar17 = (protocol_list_t *)puVar40;
      if (DAT_100ae0030 != -1) goto switchD_1007e3574_caseD_76;
      goto LAB_1007fedec;
    }
LAB_1007fedf8:
    IVar27 = _objc_msgSend((ID)mVar55,"storedPlayGuideCue");
    if (IVar27 == 0) goto LAB_1007fee50;
    IVar27 = _objc_msgSend(IVar27,"boolValue");
    bVar2 = **(undefined **)((long)self_01 + 0x840);
    if ((uint)bVar2 != (uint)IVar27) goto LAB_1007fee60;
    self_01.entsizeAndFlags = 0;
    self_01.count = 0;
    goto LAB_1007feec4;
  case (undefined **)0x61:
  case (undefined **)0x80:
  case (undefined **)0x94:
  case (undefined **)0xf8:
    *(undefined **)mVar65 = (undefined *)0xe000000000000000;
    self_01 = (method_list_t)((ulong)ppuVar41 | 8);
    pcVar34 = (char *)((ulong)&pStack_710 | 0x8000000000000000);
  case (undefined **)0xe4:
  case (undefined **)0xf5:
    __s10Foundation17NSLocalizedString_9tableName6bundle5value7commentS2S_SSSgSo8NSBundleCS2StF();
    auVar87._8_4_ = (dword)pcVar34;
    auVar87._12_4_ = SUB84(pcVar34,4);
    auVar87._0_4_ = self_01.entsizeAndFlags;
    auVar87._4_4_ = self_01.count;
    return auVar87;
  case (undefined **)0x62:
  case (undefined **)0x81:
  case (undefined **)0x95:
  case (undefined **)0xf9:
switchD_1007e3574_caseD_62:
    _swift_dynamicCastClass(IVar27,self_01);
    _swift_unknownObjectRelease(mVar65);
    if (IVar27 != 0) {
      IVar27 = _objc_msgSend((ID)&pStack_710,"song");
      self_01.entsizeAndFlags = 0;
      self_01.count = 0;
      FUN_1003f9800(IVar27,0,0,0,0,1,0,0);
    }
    auVar8._8_8_ = 0;
    auVar8._0_4_ = self_01.entsizeAndFlags;
    auVar8._4_4_ = self_01.count;
    return auVar8 << 0x40;
  case (undefined **)0x63:
  case (undefined **)0x82:
  case (undefined **)0x96:
  case (undefined **)0xfa:
    ppuVar41 = (undefined **)
               ((ulong)(byte)(*(undefined **)((long)self_01 + -8))[0x50] + 0x20 &
               ((ulong)(byte)(*(undefined **)((long)self_01 + -8))[0x50] ^ 0xffffffffffffffff));
    pcVar34 = *(char **)((long)mVar65 + 0x10);
    self_01 = (method_list_t)&pStack_710;
  case (undefined **)0x6c:
  case (undefined **)0x7b:
  case (undefined **)0xe0:
switchD_1007e3574_caseD_8c:
    FUN_1007fc458(ppuVar41);
    auVar82._8_4_ = (dword)pcVar34;
    auVar82._12_4_ = SUB84(pcVar34,4);
    auVar82._0_4_ = self_01.entsizeAndFlags;
    auVar82._4_4_ = self_01.count;
    return auVar82;
  case (undefined **)0x64:
  case (undefined **)0x83:
  case (undefined **)0x97:
  case (undefined **)0xfb:
    *(undefined ***)((long)mVar65 + 0x10) = ppuVar66;
    *(undefined **)((long)mVar65 + 0x18) = (undefined *)0x1007e3538;
    _swift_release(*(undefined8 *)
                    ((long)self_01 + _TtC8Playback25SongMapEditViewController::sectionElement));
    _swift_release(*(undefined8 *)
                    ((long)self_01 +
                    _TtC8Playback25SongMapEditViewController::precedingSectionElement));
    FUN_100026610((code *)((long)self_01 + _TtC8Playback25SongMapEditViewController::delegate));
    uVar28 = *(undefined8 *)
              ((long)self_01 + _TtC8Playback25SongMapEditViewController::___lazy_storage___sections)
    ;
    _swift_bridgeObjectRelease(uVar28);
    auVar91._8_4_ = (dword)pcVar34;
    auVar91._12_4_ = SUB84(pcVar34,4);
    auVar91._0_8_ = uVar28;
    return auVar91;
  case (undefined **)0x66:
  case (undefined **)0x86:
    _swift_bridgeObjectRetain(mVar38);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(mVar52,mVar38);
    _swift_bridgeObjectRelease(mVar38);
    if (mVar65 != (method_list_t)0x0) {
      FUN_100023444(&local_a0,mVar65);
      ppVar46 = *(protocol_list_t **)((long)mVar65 + -8);
      mVar64 = (method_list_t)
               ((long)mVar65 - (*(long *)((long)ppVar46 + 0x40) + 0xfU & 0xfffffffffffffff0));
      goto switchD_1007e3574_caseD_4a;
    }
    mVar38.entsizeAndFlags = 0;
    mVar38.count = 0;
    ppuVar66 = (undefined **)0x0;
LAB_1007fe720:
    _objc_allocWithZone();
    mVar58 = (method_list_t)
             _objc_msgSend((ID)self_01,ppuVar66[0x116],mVar52,2,mVar38,"updateButtonTapped");
switchD_1007e3574_caseD_8d:
    _swift_unknownObjectRelease(mVar38);
    local_b0.receiver = (ID)mVar58;
    local_b0.super_class = (class_t *)mVar68;
    _objc_msgSendSuper2(&local_b0,"setEnabled:",0);
    iVar23 = 2;
    FUN_1008c26ac(2,0x1a,0,0);
    if (iVar23 != 0) {
      local_c0.receiver = (ID)mVar58;
      local_c0.super_class = (class_t *)mVar68;
      IVar27 = _objc_msgSendSuper2(&local_c0,"isEnabled");
      uVar28 = 0x3ff0000000000000;
      if ((int)IVar27 == 0) {
        uVar28 = 0x3fd999999999999a;
      }
      puVar62 = &_OBJC_CLASS___UIColor;
      _swift_getInitializedObjCClass();
      IVar27 = _objc_msgSend((ID)puVar62,"systemBlueColor");
      IVar27 = _objc_msgSend(IVar27,"colorWithAlphaComponent:",uVar28);
      _objc_msgSend((ID)mVar58,"setTintColor:",IVar27);
    }
    mVar38.entsizeAndFlags = 0x18;
    mVar38.count = 0xd0000000;
    self_01 = (method_list_t)_objc_msgSend(0,(SEL)puVar40[0x113]);
    mVar65 = mVar58;
switchD_1007e3574_caseD_5e:
    _objc_msgSend((ID)self_01,"setRightBarButtonItem:",mVar65);
    IVar27 = _objc_msgSend(0,"tableView");
    if (IVar27 != 0) {
      if (DAT_100adea48 != -1) {
        _swift_once(&DAT_100adea48,FUN_1001942c0);
      }
      uVar28 = DAT_100b757d8;
      uVar26 = 0xd000000000000018;
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(0xd000000000000018,0x80000001008d7480);
      _objc_msgSend(IVar27,"registerNib:forCellReuseIdentifier:",uVar28,uVar26);
    }
    pcVar34 = "tableView";
    IVar27 = _objc_msgSend(0,"tableView");
    if (IVar27 != 0) {
      uVar28 = 0;
      FUN_100023404(0,&DAT_100af5008,&PTR__OBJC_CLASS___UITableViewCell_100aa3e28);
      _swift_getObjCClassFromMetadata();
      pcVar20 = (code *)((long)mVar38 + 1);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(pcVar20,0x80000001008d0540);
      pcVar34 = "registerClass:forCellReuseIdentifier:";
      _objc_msgSend(IVar27,"registerClass:forCellReuseIdentifier:",uVar28,pcVar20);
    }
    auVar10._8_8_ = 0;
    auVar10._0_8_ = pcVar34;
    return auVar10 << 0x40;
  case (undefined **)0x67:
  case (undefined **)0x87:
    goto switchD_1007e3574_caseD_67;
  case (undefined **)0x68:
  case (undefined **)0x88:
  case (undefined **)0xbe:
  case (undefined **)0xef:
  case (undefined **)0xff:
    goto switchD_1007e3574_caseD_68;
  case (undefined **)0x69:
  case (undefined **)0x78:
    mStack_90 = *(method_list_t *)((long)ppuVar41 + 0x8e8);
    uStack_88 = 0;
    local_86 = 0x4200;
    uStack_80 = 0x9ac0;
    uStack_7e = 0x10002;
    uStack_78 = 0xb108;
    uStack_76 = 0x100a6;
    pvVar30 = __Block_copy(&mStack_90);
    _swift_release(puStack_68);
    self_01 = (method_list_t)&_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    ppuVar42 = &PTR__swift_weakDestroy_100aa0000;
    IVar29 = _objc_msgSend((ID)self_01,"actionWithTitle:style:handler:",mVar38,2,pvVar30);
    __Block_release(pvVar30);
    ppuVar63 = &PTR__swift_weakDestroy_100aa0000;
    pcVar34 = "addAction:";
    mVar58 = mVar65;
    goto switchD_1007e3574_caseD_33;
  case (undefined **)0x6a:
  case (undefined **)0x79:
    _swift_deallocObject();
    auVar83._8_4_ = (dword)pcVar34;
    auVar83._12_4_ = SUB84(pcVar34,4);
    auVar83._0_4_ = self_01.entsizeAndFlags;
    auVar83._4_4_ = self_01.count;
    return auVar83;
  case (undefined **)0x6d:
    auVar94._8_4_ = (dword)pcVar34;
    auVar94._12_4_ = SUB84(pcVar34,4);
    auVar94._0_4_ = self_01.entsizeAndFlags;
    auVar94._4_4_ = self_01.count;
    return auVar94;
  case (undefined **)0x6f:
  case (undefined **)0xe6:
    DAT_100b0e320 = self_01;
    auVar78._8_4_ = (dword)pcVar34;
    auVar78._12_4_ = SUB84(pcVar34,4);
    auVar78._0_4_ = self_01.entsizeAndFlags;
    auVar78._4_4_ = self_01.count;
    return auVar78;
  case (undefined **)0x70:
  case (undefined **)0xab:
  case (undefined **)0xc3:
  case (undefined **)0xd7:
  case (undefined **)0xe7:
    _objc_msgSend((ID)puVar40,pcVar34,3);
    FUN_100023404(0,&DAT_100af52a0,&PTR__OBJC_CLASS___OS_dispatch_queue_100aa3e48);
    __sSo17OS_dispatch_queueC8DispatchE4mainABvgZ();
    __s8Dispatch0A4TimeV3nowACyFZ(mVar38);
    __s8Dispatch1poiyAA0A4TimeVAD_SdtF(mStack_c8,0x4000000000000000,mVar38);
    mStack_d8 = *(method_list_t *)((long)self_01 + 8);
    (*(code *)mStack_d8)(mVar38,local_c0.receiver);
    puVar62 = &DAT_100a6b140;
    _swift_allocObject(&DAT_100a6b140,0x18,7);
    *(undefined8 **)(puVar62 + 0x10) = puVar40;
    pcStack_70 = FUN_1007fcb08;
    mStack_90 = (method_list_t)PTR___NSConcreteStackBlock_100a1d8e8;
    uStack_88 = 0;
    local_86 = 0x4200;
    uStack_80 = 0xb3d8;
    uStack_7e = 0x10056;
    uStack_78 = 0xb158;
    uStack_76 = 0x100a6;
    puStack_68 = puVar62;
    pvVar30 = __Block_copy(&mStack_90);
    _swift_release(puStack_68);
    __s8Dispatch0A3QoSV11unspecifiedACvgZ(local_c0.super_class);
    puVar62 = PTR___swiftEmptyArrayStorage_100a1e050;
    mStack_90 = (method_list_t)PTR___swiftEmptyArrayStorage_100a1e050;
    puVar40 = &DAT_100af52a8;
    FUN_100023140(&DAT_100af52a8,PTR___s8Dispatch0A13WorkItemFlagsVMa_100a1e098,
                  PTR___s8Dispatch0A13WorkItemFlagsVs10SetAlgebraAAMc_100a1e0a8);
    _swift_retain(puVar62);
    puVar62 = &DAT_100af52b0;
    FUN_100021774(&DAT_100af52b0);
    puVar69 = &DAT_100af52b8;
    FUN_100023140(&DAT_100af52b8,FUN_1000264d4,PTR___sSayxGSTsMc_100a1dd30);
    __ss10SetAlgebraPyxqd__ncSTRd__7ElementQyd__ACRtzlufCTj
              (local_a0,&mStack_90,puVar62,puVar69,mStack_d0,puVar40);
    __sSo17OS_dispatch_queueC8DispatchE10asyncAfter8deadline3qos5flags7executeyAC0D4TimeV_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF
              (mStack_c8,local_c0.super_class,local_a0,pvVar30);
    __Block_release(pvVar30);
    (**(code **)((long)mStack_98 + 8))(local_a0,mStack_d0);
    (**(code **)(local_b0.receiver + 8))(local_c0.super_class,local_b0.super_class);
    (*(code *)mStack_d8)(mStack_c8,local_c0.receiver);
    auVar81._8_4_ = (dword)local_c0.receiver;
    auVar81._12_4_ = SUB84(local_c0.receiver,4);
    auVar81._0_8_ = mStack_c8;
    return auVar81;
  case (undefined **)0x71:
  case (undefined **)0xac:
  case (undefined **)0xc4:
  case (undefined **)0xd8:
  case (undefined **)0xe8:
    goto switchD_1007e3574_caseD_71;
  case (undefined **)0x72:
  case (undefined **)0xad:
  case (undefined **)0xc5:
  case (undefined **)0xd9:
  case (undefined **)0xe9:
    _swift_dynamicCastClass();
    _swift_unknownObjectRelease(&pStack_710);
    if (self_01 != (method_list_t)0x0) {
      ppuVar66 = (undefined **)0x0;
      if (*(long *)((long)self_01 + _TtC8Playback18MainViewController::waveformViewController) != 0)
      {
        puVar40 = (undefined8 *)
                  (*(long *)((long)self_01 +
                            _TtC8Playback18MainViewController::waveformViewController) +
                  _TtC8Playback22WaveformViewController::mappingSongMapElementScrollIndex);
        ppuVar66 = (undefined **)0x0;
        if ((*(byte *)(puVar40 + 1) & 1) == 0) {
          *(undefined **)mVar65 = (undefined *)*puVar40;
          FUN_1007e5fcc(mVar65);
          *(undefined **)((long)mVar65 + 0xf8) = *(undefined **)((long)mVar65 + 0x68);
          *(undefined **)((long)mVar65 + 0xf0) = *(undefined **)((long)mVar65 + 0x60);
          *(undefined **)((long)mVar65 + 0x108) = *(undefined **)((long)mVar65 + 0x78);
          *(undefined **)((long)mVar65 + 0x100) = *(undefined **)((long)mVar65 + 0x70);
          *(undefined8 *)((long)mVar65 + 0x112) = *(undefined8 *)((long)mVar65 + 0x82);
          *(undefined8 *)((long)mVar65 + 0x10a) = *(undefined8 *)((long)mVar65 + 0x7a);
          *(undefined **)((long)mVar65 + 0xb8) = *(undefined **)((long)mVar65 + 0x28);
          *(undefined **)((long)mVar65 + 0xb0) = *(undefined **)((long)mVar65 + 0x20);
          *(undefined **)((long)mVar65 + 200) = *(undefined **)((long)mVar65 + 0x38);
          *(undefined **)((long)mVar65 + 0xc0) = *(undefined **)((long)mVar65 + 0x30);
          *(undefined **)((long)mVar65 + 0xd8) = *(undefined **)((long)mVar65 + 0x48);
          *(undefined **)((long)mVar65 + 0xd0) = *(undefined **)((long)mVar65 + 0x40);
          *(undefined **)((long)mVar65 + 0xe8) = *(undefined **)((long)mVar65 + 0x58);
          *(undefined **)((long)mVar65 + 0xe0) = *(undefined **)((long)mVar65 + 0x50);
          *(undefined **)((long)mVar65 + 0x98) = *(undefined **)((long)mVar65 + 8);
          *(undefined **)((long)mVar65 + 0x90) = *(undefined **)mVar65;
          *(undefined **)((long)mVar65 + 0xa8) = *(undefined **)((long)mVar65 + 0x18);
          *(undefined **)((long)mVar65 + 0xa0) = *(undefined **)((long)mVar65 + 0x10);
          ppuVar66 = (undefined **)((long)mVar65 + 0x90);
          FUN_1007dfdc0(ppuVar66);
        }
      }
      auVar79._8_4_ = (dword)pcVar34;
      auVar79._12_4_ = SUB84(pcVar34,4);
      auVar79._0_8_ = ppuVar66;
      return auVar79;
    }
    auVar3._8_8_ = 0;
    auVar3._0_4_ = (dword)pcVar34;
    auVar3._4_4_ = SUB84(pcVar34,4);
    return auVar3 << 0x40;
  case (undefined **)0x73:
  case (undefined **)0xae:
  case (undefined **)0xc6:
  case (undefined **)0xda:
  case (undefined **)0xea:
    auVar15._8_8_ = 0;
    auVar15._0_4_ = (dword)pcVar34;
    auVar15._4_4_ = SUB84(pcVar34,4);
    return auVar15 << 0x40;
  case (undefined **)0x76:
  case (undefined **)0x9e:
  case (undefined **)0xb6:
  case (undefined **)0xce:
  case (undefined **)0xde:
switchD_1007e3574_caseD_76:
    puVar40 = &ppVar17->count;
    _swift_once();
LAB_1007fedec:
    uVar56 = 0;
    FUN_100819fe0();
    if ((uVar56 & 1) != 0) goto LAB_1007fedf8;
LAB_1007fee50:
    bVar2 = **(undefined **)((long)self_01 + 0x840);
LAB_1007fee60:
    uVar56 = (ulong)bVar2;
    IVar27 = *(ID *)((long)mVar67 + (long)self_02);
    FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
    __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(uVar56);
    _objc_msgSend(IVar27,"setStoredPlayGuideCue:",uVar56);
    self_01.entsizeAndFlags = 1;
    self_01.count = 0;
LAB_1007feec4:
    mVar55 = *(method_list_t *)((long)mVar67 + (long)self_02);
    pcVar34 = (char *)&PTR___ss6UInt64VN_100a1e000;
    ppVar47 = (protocol_list_t *)puVar40;
switchD_1007e3574_caseD_b8:
    uVar56 = 0;
    thunk_FUN_1002db810(0x1e,*(undefined **)
                              &((method_list_t *)((long)pcVar34 + 0x50))->entsizeAndFlags);
    if ((uVar56 & 1) == 0) {
      ppVar48 = ppVar47;
      if (puVar69[6] != -1) {
        _swift_once(&DAT_100ae0030,FUN_1008174c0);
      }
switchD_1007e3574_caseD_c0:
      uVar56 = 0;
      FUN_100819fe0();
      ppVar47 = ppVar48;
      if ((uVar56 & 1) != 0) goto LAB_1007fef08;
LAB_1007fef64:
      bVar2 = *_TtC8Playback25SongMapEditViewController::stagedPlaySectionCountIn;
LAB_1007fef78:
      uVar56 = (ulong)bVar2;
      IVar27 = *(ID *)((long)mVar67 + (long)self_02);
      FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
      __sSo8NSNumberC10FoundationE14booleanLiteralABSb_tcfC(uVar56);
      _objc_msgSend(IVar27,"setStoredPlayCountIn:",uVar56);
    }
    else {
LAB_1007fef08:
      ppuVar41 = &PTR__swift_weakDestroy_100aa0000;
      ppVar49 = ppVar47;
      mVar58 = self_01;
switchD_1007e3574_caseD_e5:
      self_01 = (method_list_t)_objc_msgSend((ID)mVar55,*(undefined **)((long)ppuVar41 + 0xc10));
      ppVar50 = ppVar49;
switchD_1007e3574_caseD_71:
      ppVar48 = ppVar50;
      if (self_01 == (method_list_t)0x0) goto LAB_1007fef64;
      self_01 = (method_list_t)_objc_msgSend((ID)self_01,"boolValue");
      ppVar51 = ppVar50;
switchD_1007e3574_caseD_7d:
      bVar2 = *_TtC8Playback25SongMapEditViewController::stagedPlaySectionCountIn;
      ppVar48 = ppVar51;
      if ((uint)bVar2 != self_01.entsizeAndFlags) goto LAB_1007fef78;
      if (mVar58.entsizeAndFlags == 0) goto LAB_1007ff104;
    }
    if (DAT_100ade9d8 != -1) {
      _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
    }
    IVar27 = _objc_msgSend(ppVar48[0xb9].count,"viewContext");
    FUN_1000f0934(IVar27);
    puVar62 = &_OBJC_CLASS___UIApplication;
    _swift_getInitializedObjCClass();
    IVar27 = _objc_msgSend((ID)puVar62,"sharedApplication");
    IVar27 = _objc_msgSend(IVar27,"delegate");
    if (IVar27 != 0) {
      uVar28 = 0;
      FUN_100842dec(0);
      IVar29 = IVar27;
      _swift_dynamicCastClass(IVar27,uVar28);
      if (((IVar29 == 0) || (*(ID *)(IVar29 + _TtC8Playback11AppDelegate::window) == 0)) ||
         (IVar29 = _objc_msgSend(*(ID *)(IVar29 + _TtC8Playback11AppDelegate::window),
                                 "rootViewController"), IVar29 == 0)) {
        _swift_unknownObjectRelease(IVar27);
      }
      else {
        uVar28 = 0;
        FUN_100413a94(0);
        _swift_dynamicCastClass(IVar29,uVar28);
        _swift_unknownObjectRelease(IVar27);
        if ((IVar29 != 0) &&
           (*(long *)(IVar29 + _TtC8Playback18MainViewController::waveformViewController) != 0)) {
          FUN_100461a1c(1);
        }
      }
    }
LAB_1007ff104:
    if (DAT_100adeca8 != -1) {
      _swift_once(&DAT_100adeca8,FUN_100224b00);
    }
    uVar28 = DAT_100b75a80;
    _swift_retain(DAT_100b75a80);
    FUN_1002242c0(1);
    _swift_release(uVar28);
    IVar27 = _objc_msgSend(0,"navigationController");
    puVar62 = *(undefined **)((long)mVar65 + 8);
    if (IVar27 != 0) {
      if (*(undefined **)mVar65 == (undefined *)0x0) {
        pvVar30 = (void *)0x0;
      }
      else {
        *(undefined **)((long)mVar65 + 0x30) = puVar62;
        *(method_list_t *)((long)mVar65 + 0x38) = mVar68;
        *(undefined **)((long)mVar65 + 0x10) = PTR___NSConcreteStackBlock_100a1d8e8;
        *(undefined **)((long)mVar65 + 0x18) = (undefined *)0x42000000;
        *(code **)((long)mVar65 + 0x20) = FUN_10056b3d8;
        *(undefined **)((long)mVar65 + 0x28) = &DAT_100a6b3d8;
        pvVar30 = __Block_copy((undefined **)((long)mVar65 + 0x10));
        puVar57 = *(undefined **)((long)mVar65 + 0x38);
        _swift_retain(mVar68);
        _swift_release(puVar57);
      }
      _objc_msgSend(IVar27,"dismissViewControllerAnimated:completion:",1,pvVar30);
      FUN_1000274b4(puVar62,mVar68);
      __Block_release(pvVar30);
      auVar11._8_8_ = 0;
      auVar11._0_4_ = mVar68.entsizeAndFlags;
      auVar11._4_4_ = mVar68.count;
      return auVar11 << 0x40;
    }
    FUN_1000274b4(puVar62,mVar68);
    auVar88._8_4_ = mVar68.entsizeAndFlags;
    auVar88._12_4_ = mVar68.count;
    auVar88._0_8_ = puVar62;
    return auVar88;
  case (undefined **)0x77:
  case (undefined **)0x92:
  case (undefined **)0x9f:
  case (undefined **)0xb7:
  case (undefined **)0xcf:
  case (undefined **)0xdf:
  case (undefined **)0xf6:
    goto switchD_1007e3574_caseD_77;
  case (undefined **)0x7c:
    goto switchD_1007e3574_caseD_7c;
  case (undefined **)0x7d:
  case (undefined **)0xbc:
    goto switchD_1007e3574_caseD_7d;
  case (undefined **)0x7e:
    goto switchD_1007e3574_caseD_7e;
  case (undefined **)0x89:
  case (undefined **)0xa0:
    _swift_unknownObjectWeakInit((undefined **)((long)self_01 + 0x10),mVar65);
    puVar62 = &DAT_100a6b348;
    _swift_allocObject(&DAT_100a6b348,0x19,7);
    *(method_list_t *)(puVar62 + 0x10) = self_01;
    puVar62[0x18] = 0;
    _swift_bridgeObjectRetain(mVar38);
    _swift_retain(self_01);
    mVar52 = self_01;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(self_01,mVar38);
    _swift_bridgeObjectRelease(mVar38);
    *(code **)((long)mVar65 + 0x20) = FUN_100801a88;
    *(undefined **)((long)mVar65 + 0x28) = puVar62;
    ppuVar41 = &PTR_TargetEnumDescriptor_100a1d000;
    mVar68 = self_01;
  case (undefined **)0xd4:
    *(undefined **)mVar65 = *(undefined **)((long)ppuVar41 + 0x8e8);
    param_2.entsizeAndFlags = 0x42000000;
    param_2.count = 0;
switchD_1007e3574_caseD_7c:
    *(method_list_t *)((long)mVar65 + 8) = param_2;
    *(code **)((long)mVar65 + 0x10) = FUN_100029ac0;
    *(undefined **)((long)mVar65 + 0x18) = &DAT_100a6b360;
    pvVar30 = __Block_copy((void *)mVar65);
    _swift_release(*(undefined **)((long)mVar65 + 0x28));
    puVar62 = &_OBJC_CLASS___UIAlertAction;
    _swift_getInitializedObjCClass();
    IVar27 = _objc_msgSend((ID)puVar62,"actionWithTitle:style:handler:",mVar52,2,pvVar30);
    __Block_release(pvVar30);
    _swift_release(mVar68);
    if (DAT_100adf290 != -1) {
      _swift_once(&DAT_100adf290,FUN_10052c998);
    }
    uVar26 = DAT_100b76408;
    uVar28 = DAT_100b76400;
    _swift_bridgeObjectRetain(DAT_100b76408);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar28,uVar26);
    _swift_bridgeObjectRelease(uVar26);
    IVar29 = _objc_msgSend((ID)puVar62,"actionWithTitle:style:handler:",uVar28,1,0);
    _objc_msgSend((ID)&pStack_710,"addAction:",IVar29);
    _objc_msgSend((ID)&pStack_710,"addAction:",IVar27);
    pcVar34 = "presentViewController:animated:completion:";
    _objc_msgSend((ID)mVar65,"presentViewController:animated:completion:",&pStack_710,1,0);
    auVar12._8_8_ = 0;
    auVar12._0_8_ = pcVar34;
    return auVar12 << 0x40;
  case (undefined **)0x8a:
  case (undefined **)0xa1:
    auVar6._8_8_ = 0;
    auVar6._0_4_ = (dword)pcVar34;
    auVar6._4_4_ = SUB84(pcVar34,4);
    return auVar6 << 0x40;
  case (undefined **)0x8c:
  case (undefined **)0xa3:
  case (undefined **)0xd0:
    goto switchD_1007e3574_caseD_8c;
  case (undefined **)0x8d:
  case (undefined **)0xa4:
    goto switchD_1007e3574_caseD_8d;
  case (undefined **)0x8e:
  case (undefined **)0xa5:
    goto switchD_1007e3574_caseD_8e;
  case (undefined **)0x8f:
  case (undefined **)0xa6:
    auVar80._8_4_ = (dword)pcVar34;
    auVar80._12_4_ = SUB84(pcVar34,4);
    auVar80._0_4_ = self_01.entsizeAndFlags;
    auVar80._4_4_ = self_01.count;
    return auVar80;
  case (undefined **)0x90:
    _swift_retain();
    if ((ulong)mVar52 >> 0x3e == 0) {
      mVar38 = *(method_list_t *)(((ulong)mVar52 & 0xfffffffffffff8) + 0x10);
      *(method_list_t *)((long)mVar65 + 0x28) = mVar38;
    }
    else {
      mVar38 = (method_list_t)((ulong)mVar52 & 0xffffffffffffff8);
      if ((long)mVar52 < 0) {
        mVar38 = mVar52;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      *(method_list_t *)((long)mVar65 + 0x28) = mVar38;
    }
    if (mVar38 != (method_list_t)0x0) {
      *(method_list_t *)mVar65 = mVar68;
      puVar62 = (undefined *)0x0;
      FUN_100023404(0,&DAT_100af5578,&PTR__OBJC_CLASS___NSNumber_100aa3d48);
      *(undefined **)((long)mVar65 + 0x18) = puVar62;
      *(undefined **)((long)mVar65 + 0x20) = (undefined *)((ulong)mVar52 & 0xc000000000000001);
      *(method_list_t **)((long)mVar65 + 8) = (method_list_t *)((long)mVar52 + 0x20);
      _swift_bridgeObjectRetain(mVar52);
      mVar38.entsizeAndFlags = 0;
      mVar38.count = 0;
      puVar57 = (undefined *)0x0;
      mVar68.entsizeAndFlags = 1;
      mVar68.count = 0;
      unaff_d11 = 1.0;
      unaff_d12 = 0.0;
      *(method_list_t *)((long)mVar65 + 0x10) = mVar52;
      goto LAB_1007ffb80;
    }
LAB_10080013c:
    _swift_bridgeObjectRelease(mVar52);
    pcVar20 = (code *)((long)mVar68 + _TtC8Playback25SongMapEditViewController::delegate);
    _swift_unknownObjectWeakLoadStrong();
    if (pcVar20 != (code *)0x0) {
      FUN_10087f4a0();
      _swift_unknownObjectRelease(pcVar20);
      auVar90._8_4_ = (dword)pcVar34;
      auVar90._12_4_ = SUB84(pcVar34,4);
      auVar90._0_8_ = pcVar20;
      return auVar90;
    }
    auVar16._8_8_ = 0;
    auVar16._0_4_ = (dword)pcVar34;
    auVar16._4_4_ = SUB84(pcVar34,4);
    return auVar16 << 0x40;
  case (undefined **)0x91:
    goto switchD_1007e3574_caseD_91;
  case (undefined **)0xa8:
    goto switchD_1007e3574_caseD_a8;
  case (undefined **)0xa9:
    goto switchD_1007e3574_caseD_2e;
  case (undefined **)0xaa:
    goto switchD_1007e3574_caseD_aa;
  case (undefined **)0xb8:
    goto switchD_1007e3574_caseD_b8;
  case (undefined **)0xb9:
    (*(code *)0x0)();
    FUN_100092550(0);
    FUN_100023468(mVar65);
    _swift_release(&pStack_710);
    auVar14._8_8_ = 0;
    auVar14._0_4_ = (dword)pcVar34;
    auVar14._4_4_ = SUB84(pcVar34,4);
    return auVar14 << 0x40;
  case (undefined **)0xba:
    *(method_list_t *)((long)mVar65 + 0x70) = mVar52;
    *(method_list_t *)((long)mVar65 + 0x78) = self_01;
    *(method_list_t *)((long)mVar65 + 0x80) = mVar68;
    *(undefined **)((long)mVar65 + 0x88) = (undefined *)0x0;
  case (undefined **)0xd5:
    *(method_list_t *)((long)mVar65 + 0x90) = mVar65;
    *(protocol_list_t **)((long)mVar65 + 0x98) = &pStack_710;
    *(undefined ***)((long)mVar65 + 0xa0) = ppuVar66;
    *(undefined **)((long)mVar65 + 0xa8) = (undefined *)0x1007e3538;
    ppuVar66 = (undefined **)((long)mVar65 + 0xa0);
switchD_1007e3574_caseD_7e:
    mVar43 = (method_list_t)ppuVar41;
    goto switchD_1007e3574_caseD_35;
  case (undefined **)0xbb:
  case (undefined **)0xc2:
  case (undefined **)0xd6:
  case (undefined **)0xe3:
    ppuVar41 = (undefined **)((long)ppuVar41 + 0x318);
    goto switchD_1007e3574_caseD_aa;
  case (undefined **)0xbf:
    DAT_100b0e7f0 = 0x4008000000000000;
    if (0xd < (self_01.entsizeAndFlags - 0xc & 0xff)) {
      DAT_100b0e7f0 = 0x4014000000000000;
    }
    auVar9._8_8_ = 0;
    auVar9._0_4_ = (dword)pcVar34;
    auVar9._4_4_ = SUB84(pcVar34,4);
    return auVar9 << 0x40;
  case (undefined **)0xc0:
    goto switchD_1007e3574_caseD_c0;
  case (undefined **)0xc1:
    pcVar34 = *(char **)((long)ppuVar41 + 0x840);
    goto switchD_1007e3574_caseD_67;
  case (undefined **)0xd1:
    if (self_01 == (method_list_t)0x0) {
      self_01 = *(method_list_t *)
                 (*(long *)(*(undefined **)((long)mVar38 + 0x828) + (long)&pStack_710.count) +
                 (long)*(method_list_t *)mVar52);
      FUN_100034ce8(self_01);
    }
    IVar27 = _objc_msgSend(*(ID *)(*(long *)(*(undefined **)((long)mVar38 + 0x828) +
                                            (long)&pStack_710.count) +
                                  (long)*(method_list_t *)mVar52),"editedSectionTypeID");
    FUN_10049e1c4(self_01,&pStack_710,&PTR_PTR_100a6b248,IVar27 == 0);
    pcVar34 = "navigationController";
    IVar27 = _objc_msgSend((ID)&pStack_710,"navigationController");
    if (IVar27 != 0) {
      pcVar34 = "pushViewController:animated:";
      _objc_msgSend(IVar27,"pushViewController:animated:",mVar68,1);
    }
    auVar13._8_8_ = 0;
    auVar13._0_8_ = pcVar34;
    return auVar13 << 0x40;
  case (undefined **)0xd2:
    goto switchD_1007e3574_caseD_d2;
  case (undefined **)0xd3:
    mVar38 = self_01;
    __s10Foundation9IndexPathV19_bridgeToObjectiveCSo07NSIndexC0CyF();
    mVar55 = (method_list_t)
             _objc_msgSend((ID)mVar68,"dequeueReusableCellWithIdentifier:forIndexPath:",self_01,
                           mVar38);
  case (undefined **)0xf4:
    switchD_1007e3574::caseD_4c();
    pcVar34._0_4_ = 0;
    pcVar34._4_4_ = 0;
    FUN_100194890(0);
    self_01 = mVar55;
    _swift_dynamicCastClass(mVar55,pcVar34);
    if (self_01 != (method_list_t)0x0) {
switchD_1007e3574_caseD_68:
      mVar35 = (method_list_t)pcVar34;
      mVar68 = self_01;
switchD_1007e3574_caseD_77:
      FUN_1007fd954(0);
      *(undefined **)((long)mVar65 + 0x28) = &DAT_100a6b4a8;
      *(code *)((long)mVar65 + 0x10) = (code)0x0;
      *(undefined **)mVar65 = (undefined *)0x0;
      *(method_list_t *)((long)mVar65 + 8) = mVar68;
      pcVar34 = (char *)mVar35;
      FUN_100855de8();
      _swift_bridgeObjectRelease(mVar35);
      FUN_10003d930((undefined **)((long)mVar65 + 0x10));
    }
LAB_100800930:
    auVar92._8_4_ = (dword)pcVar34;
    auVar92._12_4_ = SUB84(pcVar34,4);
    auVar92._0_4_ = mVar55.entsizeAndFlags;
    auVar92._4_4_ = mVar55.count;
    return auVar92;
  case (undefined **)0xe1:
    *(method_list_t *)((long)mVar65 + 0x20) = mVar65;
    *(protocol_list_t **)((long)mVar65 + 0x28) = &pStack_710;
    *(undefined ***)((long)mVar65 + 0x30) = ppuVar66;
    *(undefined **)((long)mVar65 + 0x38) = (undefined *)0x1007e3538;
switchD_1007e3574_caseD_a8:
    uVar56 = *(ulong *)((long)self_01 + _TtC8Playback25SongMapEditViewController::stagedSection);
    if (uVar56 != 0) {
      mVar38 = *(method_list_t *)
                (*(long *)((long)self_01 + _TtC8Playback25SongMapEditViewController::sectionElement)
                + _TtCC8Playback7SongMap7Element::section);
      FUN_100034ce8();
      if (mVar38 != (method_list_t)0x0) {
        FUN_10056a2a0(0);
        __sSo8NSObjectC10ObjectiveCE2eeoiySbAB_ABtFZ(uVar56,mVar38);
        pcVar34 = (char *)mVar38;
        if ((uVar56 & 1) != 0) goto LAB_1007ff3dc;
      }
LAB_1007ff4d4:
      uVar54 = 1;
      goto LAB_1007ff578;
    }
LAB_1007ff3dc:
    lVar39 = _TtCC8Playback7SongMap7Element::section;
    lVar60 = *(long *)((long)self_01 + _TtC8Playback25SongMapEditViewController::sectionElement);
    IVar27 = *(ID *)(lVar60 + _TtCC8Playback7SongMap7Element::section);
    uVar56 = 0;
    pcVar34 = PTR___swiftEmptyArrayStorage_100a1e050;
    thunk_FUN_1002db810(0x1e,PTR___swiftEmptyArrayStorage_100a1e050);
    if ((uVar56 & 1) == 0) {
      if (DAT_100ae0030 != -1) {
        pcVar20 = FUN_1008174c0;
        _swift_once(&DAT_100ae0030,FUN_1008174c0);
        pcVar34 = (char *)pcVar20;
      }
      uVar56 = 0;
      FUN_100819fe0();
      if ((uVar56 & 1) != 0) goto LAB_1007ff430;
LAB_1007ff488:
      if (((byte)*(code *)((long)self_01 +
                          _TtC8Playback25SongMapEditViewController::stagedPlaySectionGuideCue) & 1)
          == 0) goto LAB_1007ff4d4;
    }
    else {
LAB_1007ff430:
      pcVar34 = "storedPlayGuideCue";
      IVar27 = _objc_msgSend(IVar27,"storedPlayGuideCue");
      if (IVar27 == 0) goto LAB_1007ff488;
      pcVar34 = "boolValue";
      IVar27 = _objc_msgSend(IVar27,"boolValue");
      if ((uint)IVar27 !=
          (uint)(byte)*(code *)((long)self_01 +
                               _TtC8Playback25SongMapEditViewController::stagedPlaySectionGuideCue))
      goto LAB_1007ff4d4;
    }
    IVar27 = *(ID *)(lVar60 + lVar39);
    uVar56 = 0;
    pcVar34 = PTR___swiftEmptyArrayStorage_100a1e050;
    thunk_FUN_1002db810(0x1e,PTR___swiftEmptyArrayStorage_100a1e050);
    if ((uVar56 & 1) == 0) {
      if (DAT_100ae0030 != -1) {
        pcVar20 = FUN_1008174c0;
        _swift_once(&DAT_100ae0030,FUN_1008174c0);
        pcVar34 = (char *)pcVar20;
      }
      uVar56 = 0;
      FUN_100819fe0();
      if ((uVar56 & 1) != 0) goto LAB_1007ff500;
LAB_1007ff530:
      if (DAT_100adea10 != -1) {
        pcVar20 = FUN_1001709a4;
        _swift_once(&DAT_100adea10,FUN_1001709a4);
        pcVar34 = (char *)pcVar20;
      }
      uVar28 = DAT_100b757a8;
      FUN_10016fa38(DAT_100b757a8);
      uVar54 = (uint)uVar28;
    }
    else {
LAB_1007ff500:
      pcVar34 = "storedPlayCountIn";
      IVar27 = _objc_msgSend(IVar27,"storedPlayCountIn");
      if (IVar27 == 0) goto LAB_1007ff530;
      pcVar34 = "boolValue";
      IVar27 = _objc_msgSend(IVar27,"boolValue");
      uVar54 = (uint)IVar27;
    }
    uVar54 = uVar54 ^ _TtC8Playback25SongMapEditViewController::stagedPlaySectionCountIn
                      [(long)self_01];
LAB_1007ff578:
    auVar89._4_4_ = 0;
    auVar89._0_4_ = uVar54 & 1;
    auVar89._8_4_ = (dword)pcVar34;
    auVar89._12_4_ = SUB84(pcVar34,4);
    return auVar89;
  case (undefined **)0xe2:
    goto switchD_1007e3574_caseD_e2;
  case (undefined **)0xe5:
  case (undefined **)0xf0:
    goto switchD_1007e3574_caseD_e5;
  case (undefined **)0xf1:
    _swift_beginAccess();
    _swift_retain(0);
    FUN_1005d3400((undefined **)((long)mVar65 + 0x18),&pStack_710);
    _swift_endAccess(mVar65);
    _swift_release(0);
    auVar4._8_8_ = 0;
    auVar4._0_8_ = ppVar33;
    return auVar4 << 0x40;
  }
LAB_1007e5d54:
  uStack_88 = CONCAT11(uStack_117,uStack_118);
  mStack_98 = mStack_128;
  local_a0 = local_130;
  mStack_90 = local_120;
  uStack_7e = (undefined6)uStack_10e;
  uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
  local_86 = uStack_116;
  uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
  mStack_d8 = mStack_168;
  local_e0 = local_170;
  mStack_c8 = mStack_158;
  mStack_d0 = mStack_160;
  local_c0.super_class = pcStack_148;
  local_c0.receiver._0_4_ = local_150.entsizeAndFlags;
  local_c0.receiver._4_4_ = local_150.count;
  local_b0.super_class = (class_t *)mStack_138;
  local_b0.receiver._0_4_ = local_140.entsizeAndFlags;
  local_b0.receiver._4_4_ = local_140.count;
  mVar52 = local_2d8;
  local_100 = local_190;
  mStack_f8 = mStack_188;
  mStack_f0 = local_180;
  mStack_e8 = local_178;
LAB_1007e5d88:
  local_190 = local_100;
  mStack_188 = mStack_f8;
  local_180 = mStack_f0;
  local_178 = mStack_e8;
  local_170 = local_e0;
  mStack_168 = mStack_d8;
  mStack_160 = mStack_d0;
  mStack_158 = mStack_c8;
  local_150 = (method_list_t)local_c0.receiver;
  pcStack_148 = local_c0.super_class;
  local_140 = (method_list_t)local_b0.receiver;
  mStack_138 = (method_list_t)local_b0.super_class;
  local_130 = local_a0;
  mStack_128 = mStack_98;
  local_120 = mStack_90;
  uStack_116 = local_86;
  FUN_100023468(local_2b8);
  mVar65._2_6_ = local_86;
  mVar65.entsizeAndFlags._0_2_ = uStack_88;
  *(method_list_t *)((long)mVar52 + 0x68) = mStack_98;
  *(method_list_t *)((long)mVar52 + 0x60) = local_a0;
  *(method_list_t *)((long)mVar52 + 0x78) = mVar65;
  *(method_list_t *)((long)mVar52 + 0x70) = mStack_90;
  *(ulong *)((long)mVar52 + 0x82) = CONCAT26(uStack_78,uStack_7e);
  *(ulong *)((long)mVar52 + 0x7a) = CONCAT26(uStack_80,local_86);
  *(method_list_t *)((long)mVar52 + 0x28) = mStack_d8;
  *(method_list_t *)((long)mVar52 + 0x20) = local_e0;
  *(method_list_t *)((long)mVar52 + 0x38) = mStack_c8;
  *(method_list_t *)((long)mVar52 + 0x30) = mStack_d0;
  *(class_t **)&((method_list_t *)((long)mVar52 + 0x48))->entsizeAndFlags = local_c0.super_class;
  ((method_list_t *)((long)mVar52 + 0x40))->entsizeAndFlags = (undefined4)local_c0.receiver;
  ((method_list_t *)((long)mVar52 + 0x40))->count = local_c0.receiver._4_4_;
  *(class_t **)((long)mVar52 + 0x58) = local_b0.super_class;
  ((method_list_t *)((long)mVar52 + 0x50))->entsizeAndFlags = (undefined4)local_b0.receiver;
  ((method_list_t *)((long)mVar52 + 0x50))->count = local_b0.receiver._4_4_;
  *(method_list_t *)((long)mVar52 + 8) = mStack_f8;
  *(method_list_t *)mVar52 = local_100;
  *(method_list_t *)((long)mVar52 + 0x18) = mStack_e8;
  *(method_list_t *)((long)mVar52 + 0x10) = mStack_f0;
LAB_1007e5954:
  auVar76._8_4_ = mVar31.entsizeAndFlags;
  auVar76._12_4_ = mVar31.count;
  auVar76._0_4_ = local_2b8.entsizeAndFlags;
  auVar76._4_4_ = local_2b8.count;
  return auVar76;
switchD_1007e3574_caseD_3f:
  mVar58 = (method_list_t)&DAT_100a68b58;
switchD_1007e3574_caseD_3b:
  mVar52 = local_700[1];
  __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF
            (local_700[1]);
  mVar68 = mVar31;
  local_2c0 = self_01;
switchD_1007e3574_caseD_39:
  mVar55 = mVar52;
  local_191 = 0;
  FUN_1007e6300();
  mVar38 = local_428;
  self_01 = (method_list_t)&DAT_100a64068;
  __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
            (&local_220,&DAT_100a64068,&local_191,local_428,&DAT_100a64068,mVar58);
  mVar58 = local_700[2];
  mVar52 = local_2d8;
switchD_1007e3574_caseD_4b:
  mVar31 = mVar68;
  local_260._1_7_ = uStack_1df;
  local_260.entsizeAndFlags._0_1_ = local_1e0;
  pcStack_258 = pcStack_1d8;
  mStack_248 = mStack_1c8;
  local_250 = mStack_1d0;
  mStack_238 = mStack_1b8;
  local_240 = local_1c0;
  local_230 = local_1b0;
  local_2a0.count = dStack_21c;
  local_2a0.entsizeAndFlags = local_220;
  local_290._1_7_ = uStack_20f;
  local_290.entsizeAndFlags._0_1_ = local_210;
  mStack_298 = mStack_218;
  mStack_288 = local_208;
  local_280.entsizeAndFlags._1_1_ = uStack_1ff;
  local_280.entsizeAndFlags._0_1_ = local_200;
  local_280._2_6_ = uStack_1fe;
  local_270._2_6_ = uStack_1ee;
  local_270.entsizeAndFlags._0_2_ = sStack_1f0;
  mStack_278 = mStack_1f8;
  mStack_268 = mStack_1e8;
  local_2a2 = 1;
  FUN_1007e6340();
  __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
            (&local_2a1,&DAT_100a64958,&local_2a2,mVar38,&DAT_100a64958,self_01);
  (**(code **)((long)local_700[0] + 8))(mVar55,local_428);
  _swift_unknownObjectRelease(local_2c0);
  (**(code **)((long)mVar58 + 8))(mVar65,mVar31);
  pcStack_148 = pcStack_258;
  local_150 = local_260;
  mStack_138 = mStack_248;
  local_140 = local_250;
  mStack_128 = mStack_238;
  local_130 = local_240;
  local_120 = local_230;
  mStack_188 = mStack_298;
  local_190 = local_2a0;
  local_178 = mStack_288;
  local_180 = local_290;
  mStack_168 = mStack_278;
  local_170 = local_280;
  mStack_158 = mStack_268;
  mStack_160 = local_270;
  uStack_118 = local_2a1;
  FUN_100211efc(&local_190);
  local_b0.super_class = (class_t *)mStack_138;
  local_b0.receiver._0_4_ = local_140.entsizeAndFlags;
  local_b0.receiver._4_4_ = local_140.count;
  mStack_98 = mStack_128;
  local_a0 = local_130;
  uStack_88 = CONCAT11(uStack_117,uStack_118);
  mStack_90 = local_120;
  uStack_7e = (undefined6)uStack_10e;
  uStack_78 = (undefined2)(CONCAT17(uStack_107,uStack_10e) >> 0x30);
  local_86 = uStack_116;
  uStack_80 = (undefined2)(CONCAT17(uStack_10f,CONCAT16(uStack_110,uStack_116)) >> 0x30);
  mStack_d8 = mStack_168;
  local_e0 = local_170;
  mStack_c8 = mStack_158;
  mStack_d0 = mStack_160;
  local_c0.super_class = pcStack_148;
  local_c0.receiver._0_4_ = local_150.entsizeAndFlags;
  local_c0.receiver._4_4_ = local_150.count;
  mStack_f8 = mStack_188;
  local_100 = local_190;
  mStack_e8 = local_178;
  mStack_f0 = local_180;
  goto LAB_1007e5d88;
switchD_1007e3574_caseD_35:
  mVar55 = *(method_list_t *)((long)mVar65 + 0x10);
  mVar44 = mVar43;
  goto switchD_1007e3574_caseD_91;
switchD_1007e3574_caseD_30:
  mVar31 = mVar68;
  __ss22KeyedDecodingContainerV06nestedC07keyedBy6forKeyAByqd__Gqd__m_xtKs06CodingH0Rd__lF(ppuVar41)
  ;
  puVar62 = local_440;
  __ss22KeyedDecodingContainerV6decode_6forKeyS2dm_xtKF();
  mVar52 = local_700[2];
  (**(code **)(local_458 + 8))(mVar38,puVar62);
  _swift_unknownObjectRelease(self_01);
  (**(code **)((long)mVar52 + 8))(mVar65,mVar31);
  local_190 = param_2;
  FUN_1007e5e30(&local_190);
  goto LAB_1007e5d54;
switchD_1007e3574_caseD_aa:
  *ppuVar41 = (undefined *)self_01;
  auVar77._8_4_ = (dword)pcVar34;
  auVar77._12_4_ = SUB84(pcVar34,4);
  auVar77._0_4_ = self_01.entsizeAndFlags;
  auVar77._4_4_ = self_01.count;
  return auVar77;
switchD_1007e3574_caseD_67:
  auVar84._0_8_ = _objc_msgSend((ID)self_01,pcVar34);
  auVar84._8_4_ = (dword)pcVar34;
  auVar84._12_4_ = SUB84(pcVar34,4);
  return auVar84;
switchD_1007e3574_caseD_2e:
  __swift_stdlib_reportUnimplementedInitializer();
                    /* WARNING: Does not return */
  pcVar20 = (code *)SoftwareBreakpoint(1,0x100800358);
  (*pcVar20)();
switchD_1007e3574_caseD_33:
  _objc_msgSend((ID)mVar58,pcVar34,IVar29);
  if (DAT_100adf290 != -1) {
    _swift_once(&DAT_100adf290,FUN_10052c998);
  }
  uVar26 = DAT_100b76408;
  uVar28 = DAT_100b76400;
  _swift_bridgeObjectRetain(DAT_100b76408);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar28,uVar26);
  _swift_bridgeObjectRelease(uVar26);
  IVar27 = _objc_msgSend((ID)self_01,ppuVar42[0x1db],uVar28,1,0);
  _objc_msgSend((ID)mVar65,ppuVar63[0x1dd],IVar27);
  pcVar34 = "presentViewController:animated:completion:";
  _objc_msgSend((ID)mStack_98,"presentViewController:animated:completion:",mVar65,1,0);
  auVar7._8_8_ = 0;
  auVar7._0_8_ = pcVar34;
  return auVar7 << 0x40;
switchD_1007e3574_caseD_91:
  mVar45 = mVar44;
switchD_1007e3574_caseD_e2:
  ppuVar42 = ppuVar66 + -9;
  _swift_beginAccess();
  _swift_retain(mVar55);
  _pthread_mutex_lock((pthread_mutex_t *)((long)mVar55 + 0x18));
  pcVar20 = (code *)((long)mVar55 + _TtC8Playback14InnerWebSocket::privateEvents);
  puVar57 = *(undefined **)pcVar20;
  puVar62 = *(undefined **)(pcVar20 + 0x58);
  puVar36 = *(undefined **)(pcVar20 + 8);
  *(undefined **)((long)mVar65 + 0x48) = *(undefined **)(pcVar20 + 0x10);
  *(undefined **)((long)mVar65 + 0x40) = puVar36;
  _swift_retain(puVar36);
  puVar36 = *(undefined **)(pcVar20 + 0x18);
  *(undefined **)((long)mVar65 + 0x38) = *(undefined **)(pcVar20 + 0x20);
  *(undefined **)((long)mVar65 + 0x30) = puVar36;
  _swift_retain(puVar36);
  puVar36 = *(undefined **)(pcVar20 + 0x28);
  *(undefined **)((long)mVar65 + 0x28) = *(undefined **)(pcVar20 + 0x30);
  *(undefined **)((long)mVar65 + 0x20) = puVar36;
  _swift_retain(puVar36);
  puVar36 = *(undefined **)(pcVar20 + 0x38);
  *(undefined **)((long)mVar65 + 0x18) = *(undefined **)(pcVar20 + 0x40);
  *(undefined **)((long)mVar65 + 0x10) = puVar36;
  _swift_retain(puVar36);
  puVar36 = *(undefined **)(pcVar20 + 0x48);
  *(undefined **)((long)mVar65 + 8) = *(undefined **)(pcVar20 + 0x50);
  *(undefined **)mVar65 = puVar36;
  _swift_retain(puVar36);
  _swift_retain(puVar62);
  _pthread_mutex_unlock((pthread_mutex_t *)((long)mVar55 + 0x18));
  _swift_endAccess(ppuVar66 + -9);
  _swift_release(mVar55);
  *(undefined **)mVar45 = puVar57;
  puVar36 = *(undefined **)((long)mVar65 + 0x38);
  puVar57 = *(undefined **)((long)mVar65 + 0x30);
  puVar73 = *(undefined **)((long)mVar65 + 0x40);
  *(undefined **)((long)mVar45 + 0x10) = *(undefined **)((long)mVar65 + 0x48);
  *(undefined **)((long)mVar45 + 8) = puVar73;
  *(undefined **)((long)mVar45 + 0x20) = puVar36;
  *(undefined **)((long)mVar45 + 0x18) = puVar57;
  puVar36 = *(undefined **)((long)mVar65 + 0x18);
  puVar57 = *(undefined **)((long)mVar65 + 0x10);
  puVar73 = *(undefined **)((long)mVar65 + 0x20);
  *(undefined **)((long)mVar45 + 0x30) = *(undefined **)((long)mVar65 + 0x28);
  *(undefined **)((long)mVar45 + 0x28) = puVar73;
  *(undefined **)((long)mVar45 + 0x40) = puVar36;
  *(undefined **)((long)mVar45 + 0x38) = puVar57;
  puVar57 = *(undefined **)mVar65;
  *(undefined **)((long)mVar45 + 0x50) = *(undefined **)((long)mVar65 + 8);
  *(undefined **)((long)mVar45 + 0x48) = puVar57;
  *(undefined **)((long)mVar45 + 0x58) = puVar62;
  auVar85._8_8_ = ppuVar42;
  auVar85._0_4_ = mVar55.entsizeAndFlags;
  auVar85._4_4_ = mVar55.count;
  return auVar85;
switchD_1007e3574_caseD_42:
  dVar59 = mVar61.entsizeAndFlags;
  if (mVar58 != (method_list_t)0x0) {
    if (dVar59 - 5 < 2) {
      self_01 = (method_list_t)&_OBJC_CLASS___UIColor;
      _swift_getInitializedObjCClass();
      ppuVar41 = &PTR_s_systemBlueColor_100aa0870;
      mVar18 = mVar53;
      mVar1 = mVar58;
switchD_1007e3574_caseD_38:
      mVar58 = mVar1;
      mVar53 = mVar18;
      dVar59 = mVar61.entsizeAndFlags;
    }
    else {
      iVar23 = 2;
      FUN_1008c26ac(2,0xd,0,0);
      self_01 = (method_list_t)&_OBJC_CLASS___UIColor;
      _swift_getInitializedObjCClass();
      ppuVar41 = &PTR_s_blackColor_100aa0880;
      if (iVar23 != 0) {
        ppuVar41 = &PTR_s_labelColor_100aa0878;
      }
    }
    IVar27 = _objc_msgSend((ID)self_01,*ppuVar41);
    _objc_msgSend((ID)mVar58,"setTextColor:",IVar27);
  }
  _objc_msgSend((ID)mVar53,"setAccessoryType:",(ulong)(dVar59 == 0));
  if (dVar59 == 3) {
    uVar56 = *(ulong *)(*(long *)((long)mVar65 +
                                 _TtC8Playback25SongMapEditViewController::sectionElement) +
                       _TtCC8Playback7SongMap7Element::section);
    FUN_1000366c8();
    uVar54 = (uint)uVar56;
    uVar28 = 0x3ff0000000000000;
    if ((uVar56 & 1) == 0) {
      uVar28 = 0x3fe0000000000000;
    }
  }
  else {
    uVar54 = 1;
    uVar28 = 0x3ff0000000000000;
  }
  IVar27 = _objc_msgSend((ID)mVar53,"contentView");
  _objc_msgSend(IVar27,"setAlpha:",uVar28);
  pcVar34 = "setUserInteractionEnabled:";
  auVar93._0_8_ = _objc_msgSend((ID)mVar53,"setUserInteractionEnabled:",(ulong)(uVar54 & 1));
  auVar93._8_8_ = pcVar34;
  return auVar93;
}

// ==== 1008223d4 FUN_1008223d4 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 FUN_1008223d4(long param_1,uint param_2)

{
  ulong uVar1;
  code *pcVar2;
  undefined *puVar3;
  ID IVar4;
  ID IVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  ID unaff_x20;
  undefined1 *puVar10;
  undefined8 uVar11;
  uint uVar12;
  ulong uVar13;
  undefined1 auStack_d0 [12];
  uint local_c4;
  char local_c0 [40];
  long local_98;
  
  puVar3 = &DAT_100af5490;
  FUN_100021774();
  puVar10 = auStack_d0 + -(*(long *)(*(long *)(puVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  IVar4 = _objc_msgSend(unaff_x20,"songSection");
  if (((IVar4 != 0) && (IVar4 = _objc_msgSend(IVar4,"arrangement"), IVar4 != 0)) &&
     (IVar4 = _objc_msgSend(IVar4,"song"), IVar4 != 0)) {
    local_c4 = param_2;
    IVar5 = _objc_msgSend(unaff_x20,"applyTransitionLengthCorrection");
    uVar13 = 1;
    if ((int)IVar5 != 0) {
      _objc_msgSend(unaff_x20,"storedSampleTimecode");
      FUN_100823b10();
      FUN_1003224d0(local_c0);
      uVar12 = 1;
      if (local_98 == 8 && local_c0[0] != '\x14') {
        uVar12 = 2;
      }
      uVar13 = (ulong)uVar12;
    }
    lVar9 = _TtC8Playback4Song::privateSongMap;
    lVar6 = *(long *)(IVar4 + _TtC8Playback4Song::privateSongMap);
    lVar8 = lVar6;
    if (lVar6 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar6 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar6 + 0x28) = 0;
      *(undefined8 *)(lVar6 + 0x20) = 0;
      *(undefined8 *)(lVar6 + 0x38) = 0;
      *(undefined8 *)(lVar6 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar6 + 0x10,IVar4);
      _swift_retain(puVar3);
      FUN_10085ee38();
      uVar11 = *(undefined8 *)(IVar4 + lVar9);
      *(long *)(IVar4 + lVar9) = lVar6;
      _swift_retain(lVar6);
      _swift_release(uVar11);
      lVar8 = 0;
    }
    _swift_retain(lVar8);
    uVar7 = uVar13;
    FUN_10085ca74();
    _swift_release(lVar6);
    lVar6 = *(long *)(IVar4 + lVar9);
    lVar8 = lVar6;
    if (lVar6 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar6 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined8 *)(lVar6 + 0x28) = 0;
      *(undefined8 *)(lVar6 + 0x20) = 0;
      *(undefined8 *)(lVar6 + 0x38) = 0;
      *(undefined8 *)(lVar6 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar6 + 0x10,IVar4);
      _swift_retain(puVar3);
      FUN_10085ee38();
      uVar11 = *(undefined8 *)(IVar4 + lVar9);
      *(long *)(IVar4 + lVar9) = lVar6;
      _swift_retain(lVar6);
      _swift_release(uVar11);
      lVar8 = 0;
    }
    _swift_retain(lVar8);
    _objc_msgSend(unaff_x20,"storedSequenceTimecode");
    FUN_100823b10();
    FUN_100860ea8(uVar13,1);
    _swift_release(lVar6);
    if ((local_c4 & 1) != 0) {
      IVar5 = _objc_msgSend(unaff_x20,"transitionBeats");
      param_1 = (long)(int)IVar5;
    }
    uVar1 = uVar13 + param_1;
    if (SCARRY8(uVar13,param_1)) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(1,0x100822874);
      (*pcVar2)();
    }
    uVar13 = *(ulong *)(uVar7 + 0x10);
    if (((long)uVar1 < 0) || (uVar13 <= uVar1)) {
      _swift_bridgeObjectRelease(uVar7);
      if ((long)uVar13 <= (long)uVar1) {
        lVar6 = *(long *)(IVar4 + lVar9);
        lVar8 = lVar6;
        if (lVar6 == 0) {
          FUN_100861310();
          _swift_allocObject();
          puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined **)(lVar6 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined8 *)(lVar6 + 0x28) = 0;
          *(undefined8 *)(lVar6 + 0x20) = 0;
          *(undefined8 *)(lVar6 + 0x38) = 0;
          *(undefined8 *)(lVar6 + 0x30) = 0;
          _swift_unknownObjectUnownedInit(lVar6 + 0x10,IVar4);
          _swift_retain(puVar3);
          FUN_10085ee38();
          uVar11 = *(undefined8 *)(IVar4 + lVar9);
          *(long *)(IVar4 + lVar9) = lVar6;
          _swift_retain(lVar6);
          _swift_release(uVar11);
          lVar8 = 0;
        }
        lVar9 = DAT_100adfbb8;
        _swift_retain(lVar8);
        if (lVar9 != -1) {
          _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
        }
        lVar9 = 0;
        __ss25FloatingPointRoundingRuleOMa();
        (**(code **)(*(long *)(lVar9 + -8) + 0x38))(puVar10,1,1,lVar9);
        thunk_FUN_100035714(3,puVar10);
        FUN_1000f9e50(puVar10);
        _swift_release(lVar6);
        _objc_msgSend(unaff_x20,"storedSequenceTimecode");
        FUN_100823b10();
      }
    }
    else {
      _swift_bridgeObjectRelease(uVar7);
      _objc_msgSend(unaff_x20,"storedSequenceTimecode");
      FUN_100823b10();
    }
  }
  return 0;
}

// ==== 10082288c FUN_10082288c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_10082288c(double param_1,ID param_2)

{
  long lVar1;
  ID IVar2;
  ID self;
  char *pcVar3;
  long lVar4;
  ID unaff_x20;
  long lVar5;
  double dVar6;
  undefined1 auStack_70 [16];
  
  lVar1 = 0;
  __s10Foundation4UUIDVMa();
  lVar5 = *(long *)(lVar1 + -8);
  lVar4 = *(long *)(lVar5 + 0x40);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar2 = _objc_msgSend(DAT_100b755c8,"viewContext");
  pcVar3 = "initWithContext:";
  self = _objc_msgSend(unaff_x20,"initWithContext:",IVar2);
  IVar2 = self;
  __s10Foundation4UUIDVACycfC(auStack_70 + -(lVar4 + 0xfU & 0xfffffffffffffff0));
  __s10Foundation4UUIDV10uuidStringSSvg();
  (**(code **)(lVar5 + 8))(auStack_70 + -(lVar4 + 0xfU & 0xfffffffffffffff0),lVar1);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar2,pcVar3);
  _swift_bridgeObjectRelease(pcVar3);
  _objc_msgSend(self,"setStoredUUID:",IVar2);
  IVar2 = _objc_msgSend(param_2,"name");
  _objc_msgSend(self,"setName:",IVar2);
  IVar2 = _objc_msgSend(param_2,"details");
  _objc_msgSend(self,"setDetails:",IVar2);
  IVar2 = _objc_msgSend(param_2,"songSection");
  _objc_msgSend(self,"setSongSection:",IVar2);
  _objc_msgSend(param_2,"storedSampleTimecode");
  dVar6 = param_1;
  FUN_100823b10();
  param_1 = param_1 * dVar6;
  _objc_msgSend(self,"setStoredSampleTimecode:",param_1);
  _objc_msgSend(param_2,"storedSequenceTimecode");
  dVar6 = param_1;
  FUN_100823b10();
  _objc_msgSend(self,"setStoredSequenceTimecode:",param_1 * dVar6);
  IVar2 = _objc_msgSend(param_2,"transitionBeats");
  _objc_msgSend(self,"setTransitionBeats:",IVar2);
  IVar2 = _objc_msgSend(param_2,"applyTransitionLengthCorrection");
  IVar2 = _objc_msgSend(self,"setApplyTransitionLengthCorrection:",IVar2);
  FUN_100822b68();
  FUN_100823c88(IVar2,self);
  _swift_bridgeObjectRelease(IVar2);
  return self;
}

// ==== 100822c4c FUN_100822c4c ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_100822c4c(double param_1,undefined8 *param_2,ID param_3,undefined8 param_4,undefined8 param_5
                )

{
  undefined8 uVar1;
  long lVar2;
  ID IVar3;
  ID self;
  ID IVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined *puVar7;
  undefined *puVar8;
  ID IVar9;
  char *pcVar10;
  long lVar11;
  ID unaff_x20;
  long lVar12;
  long lVar13;
  undefined8 *puVar14;
  double dVar15;
  double dVar16;
  undefined8 uVar17;
  undefined8 *local_90;
  ID local_88;
  ID local_78;
  
  lVar2 = 0;
  __s10Foundation4UUIDVMa();
  lVar11 = *(long *)(lVar2 + -8);
  lVar12 = (long)&local_90 - (*(long *)(lVar11 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar3 = _objc_msgSend(DAT_100b755c8,"viewContext");
  pcVar10 = "initWithContext:";
  self = _objc_msgSend(unaff_x20,"initWithContext:",IVar3);
  IVar3 = self;
  __s10Foundation4UUIDVACycfC(lVar12);
  __s10Foundation4UUIDV10uuidStringSSvg();
  (**(code **)(lVar11 + 8))(lVar12,lVar2);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar3,pcVar10);
  _swift_bridgeObjectRelease(pcVar10);
  _objc_msgSend(self,"setStoredUUID:",IVar3);
  uVar6 = *param_2;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar6,param_2[1]);
  _objc_msgSend(self,"setName:",uVar6);
  lVar2 = param_2[3];
  if (lVar2 == 0) {
    lVar11 = 0;
  }
  else {
    lVar11 = param_2[2];
    _swift_bridgeObjectRetain(lVar2);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(lVar11,lVar2);
    _swift_bridgeObjectRelease(lVar2);
  }
  _objc_msgSend(self,"setDetails:");
  pcVar10 = "setlist";
  IVar3 = _objc_msgSend(param_3,"setlist");
  local_88 = param_3;
  if ((IVar3 != 0) && (FUN_1004a917c(), lVar11 != 0)) {
    _swift_bridgeObjectRelease(lVar11);
    _swift_bridgeObjectRelease(param_5);
    lVar2 = _TtC8Playback4Song::privateSongMap;
    if ((((ulong)pcVar10 & 1) == 0) && (1 < (long)IVar3)) {
      if ((*(byte *)((long)param_2 + 0x41) & 1) == 0) {
        IVar3 = _objc_msgSend(param_3,"arrangements");
        if (IVar3 == 0) {
          puVar5 = (undefined *)0x0;
        }
        else {
          local_78 = 0;
          uVar6 = 0;
          FUN_1002eda7c(0);
          puVar5 = &DAT_100af92a8;
          FUN_100023140(&DAT_100af92a8,FUN_1002eda7c,PTR___sSo8NSObjectCSH10ObjectiveCMc_100a1e0f0);
          __sSh10FoundationE34_conditionallyBridgeFromObjectiveC_6resultSbSo5NSSetC_ShyxGSgztFZ
                    (IVar3,&local_78,uVar6,puVar5);
          IVar3 = local_78;
          if (local_78 == 0) {
            puVar5 = (undefined *)0x0;
          }
          else {
            IVar4 = local_78;
            FUN_100321e20();
            _swift_bridgeObjectRelease(IVar3);
            if (IVar4 == 0) {
              puVar5 = (undefined *)0x0;
            }
            else {
              IVar3 = _objc_msgSend(IVar4,"storedSections");
              if (IVar3 == 0) {
LAB_100823280:
                puVar7 = PTR___swiftEmptyArrayStorage_100a1e050;
                _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
              }
              else {
                puVar5 = (undefined *)_objc_msgSend(IVar3,"array");
                __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                          (puVar5,PTR___sypN_100a1e038 + 8);
                puVar7 = puVar5;
                FUN_1002d7d28();
                _swift_bridgeObjectRelease(puVar5);
                if (puVar7 == (undefined *)0x0) goto LAB_100823280;
              }
              FUN_1002f9a10(param_2);
              puVar5 = puVar7;
              FUN_1008248a0(puVar7,param_3,param_2);
              FUN_1002f9a58(param_2);
              _swift_bridgeObjectRelease(puVar7);
            }
          }
        }
        lVar2 = _TtC8Playback4Song::privateWorkingCopyArrangement;
        IVar3 = *(ID *)(param_3 + _TtC8Playback4Song::privateWorkingCopyArrangement);
        if (IVar3 == 0) {
          IVar4 = _objc_msgSend(param_3,"workingCopyArrangementID");
          if (IVar4 == 0) {
            puVar7 = (undefined *)0x0;
          }
          else {
            IVar9 = IVar4;
            FUN_10032ee88();
            IVar3 = IVar9;
            FUN_1005e3b94(IVar9,IVar4);
            _swift_bridgeObjectRelease(IVar9);
            if (IVar3 != 0) {
              *(ID *)(param_3 + lVar2) = IVar3;
              goto LAB_100823428;
            }
            puVar7 = (undefined *)0x0;
          }
        }
        else {
LAB_100823428:
          local_90 = (undefined8 *)0x0;
          IVar3 = _objc_msgSend(IVar3,"storedSections");
          if (IVar3 == 0) {
LAB_1008234a0:
            puVar8 = PTR___swiftEmptyArrayStorage_100a1e050;
            _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          }
          else {
            puVar7 = (undefined *)_objc_msgSend(IVar3,"array");
            __sSa10FoundationE36_unconditionallyBridgeFromObjectiveCySayxGSo7NSArrayCSgFZ
                      (puVar7,PTR___sypN_100a1e038 + 8);
            puVar8 = puVar7;
            FUN_1002d7d28();
            _swift_bridgeObjectRelease(puVar7);
            if (puVar8 == (undefined *)0x0) goto LAB_1008234a0;
          }
          puVar7 = puVar8;
          FUN_100824094(puVar8,puVar5);
          _swift_bridgeObjectRelease(puVar8);
        }
        _objc_msgSend(self,"setSongSection:",puVar7);
      }
      else {
        lVar12 = *(long *)(param_3 + _TtC8Playback4Song::privateSongMap);
        lVar11 = lVar12;
        if (lVar12 == 0) {
          lVar12 = 0;
          FUN_100861310();
          _swift_allocObject();
          puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined **)(lVar12 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
          *(undefined8 *)(lVar12 + 0x28) = 0;
          *(undefined8 *)(lVar12 + 0x20) = 0;
          *(undefined8 *)(lVar12 + 0x38) = 0;
          *(undefined8 *)(lVar12 + 0x30) = 0;
          _swift_unknownObjectUnownedInit(lVar12 + 0x10,param_3);
          _swift_retain(puVar5);
          FUN_10085ee38();
          uVar6 = *(undefined8 *)(param_3 + lVar2);
          *(long *)(param_3 + lVar2) = lVar12;
          _swift_retain(lVar12);
          _swift_release(uVar6);
          lVar11 = 0;
        }
        lVar13 = *(long *)(lVar12 + 0x18);
        _swift_bridgeObjectRetain(lVar13);
        _swift_retain(lVar11);
        _swift_release(lVar12);
        FUN_1002f9a10(param_2);
        lVar2 = lVar13;
        FUN_1008241bc(lVar13,param_3,param_2);
        FUN_1002f9a58(param_2);
        _swift_bridgeObjectRelease(lVar13);
        if (lVar2 == 0) {
          uVar6 = 0;
        }
        else {
          uVar6 = *(undefined8 *)(lVar2 + _TtCC8Playback7SongMap7Element::section);
        }
        _objc_msgSend(self,"setSongSection:",uVar6);
        _swift_release(lVar2);
      }
      _objc_msgSend(self,"setStoredSampleTimecode:",param_2[4]);
      _objc_msgSend(self,"setStoredSequenceTimecode:",param_2[5]);
      goto LAB_100822fc0;
    }
  }
  lVar2 = _TtC8Playback4Song::privateSongMap;
  lVar12 = *(long *)(param_3 + _TtC8Playback4Song::privateSongMap);
  lVar11 = lVar12;
  if (lVar12 == 0) {
    lVar12 = 0;
    FUN_100861310();
    _swift_allocObject();
    puVar5 = PTR___swiftEmptyArrayStorage_100a1e050;
    *(undefined **)(lVar12 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
    param_1 = 0.0;
    *(undefined8 *)(lVar12 + 0x28) = 0;
    *(undefined8 *)(lVar12 + 0x20) = 0;
    *(undefined8 *)(lVar12 + 0x38) = 0;
    *(undefined8 *)(lVar12 + 0x30) = 0;
    _swift_unknownObjectUnownedInit(lVar12 + 0x10,param_3);
    _swift_retain(puVar5);
    FUN_10085ee38();
    uVar6 = *(undefined8 *)(param_3 + lVar2);
    *(long *)(param_3 + lVar2) = lVar12;
    _swift_retain(lVar12);
    _swift_release(uVar6);
    lVar11 = 0;
  }
  lVar13 = *(long *)(lVar12 + 0x18);
  _swift_bridgeObjectRetain(lVar13);
  _swift_retain(lVar11);
  _swift_release(lVar12);
  FUN_1002f9a10(param_2);
  lVar2 = lVar13;
  FUN_100824494(lVar13,param_2);
  FUN_1002f9a58(param_2);
  _swift_bridgeObjectRelease(lVar13);
  if (lVar2 == 0) {
    uVar6 = 0;
  }
  else {
    uVar6 = *(undefined8 *)(lVar2 + _TtCC8Playback7SongMap7Element::section);
  }
  _objc_msgSend(self,"setSongSection:",uVar6);
  dVar15 = (double)param_2[4];
  FUN_100823b10(0);
  dVar15 = dVar15 / param_1;
  _objc_msgSend(self,"setStoredSampleTimecode:",dVar15);
  dVar16 = (double)param_2[5];
  FUN_100823b10();
  _objc_msgSend(self,"setStoredSequenceTimecode:",dVar16 / dVar15);
  _swift_release(lVar2);
LAB_100822fc0:
  _objc_msgSend(self,"setTransitionBeats:",(long)*(short *)(param_2 + 6));
  _objc_msgSend(self,"setApplyTransitionLengthCorrection:",(ulong)(*(byte *)(param_2 + 8) & 1));
  IVar3 = param_2[7];
  lVar2 = *(long *)(IVar3 + 0x10);
  local_78 = IVar3;
  if (lVar2 == 0) {
    _swift_bridgeObjectRetain(IVar3);
  }
  else {
    IVar4 = 0;
    local_90 = param_2;
    FUN_1003ac3f8();
    _swift_bridgeObjectRetain_n(IVar3,2);
    puVar14 = (undefined8 *)(IVar3 + 0x30);
    do {
      uVar6 = puVar14[-2];
      uVar1 = puVar14[-1];
      uVar17 = *puVar14;
      IVar9 = IVar4;
      _objc_allocWithZone();
      IVar3 = DAT_100b755c8;
      _swift_bridgeObjectRetain_n(uVar1,2);
      IVar3 = _objc_msgSend(IVar3,"viewContext");
      IVar3 = _objc_msgSend(IVar9,"initWithContext:",IVar3);
      _swift_bridgeObjectRetain(uVar1);
      __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(uVar6,uVar1);
      _swift_bridgeObjectRelease(uVar1);
      _objc_msgSend(IVar3,"setAutomationID:",uVar6);
      _objc_msgSend(IVar3,"setStoredValue:",uVar17);
      _swift_bridgeObjectRelease(uVar1);
      _objc_msgSend(self,"addStoredItemsObject:",IVar3);
      _swift_bridgeObjectRelease(uVar1);
      lVar2 = lVar2 + -1;
      puVar14 = puVar14 + 3;
    } while (lVar2 != 0);
    FUN_1001d7e54(&local_78);
    param_2 = local_90;
  }
  FUN_1002f9a58(param_2);
  FUN_1001d7e54(&local_78);
  return self;
}

// ==== 100823650 FUN_100823650 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined1  [16] FUN_100823650(void)

{
  undefined1 auVar1 [16];
  long lVar2;
  ID IVar3;
  undefined *puVar4;
  ID IVar5;
  undefined *puVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  char *pcVar9;
  undefined8 uVar10;
  long lVar11;
  ID unaff_x20;
  long lVar12;
  undefined *puVar13;
  ID IVar14;
  char *pcVar15;
  char *local_80;
  ID local_78;
  undefined2 local_70;
  undefined6 uStack_6e;
  undefined8 uStack_68;
  
  pcVar15 = (char *)0xe90000000000003e;
  IVar14 = 0x6e776f6e6b6e753c;
  lVar2 = 0;
  __s10Foundation4UUIDVMa();
  lVar11 = *(long *)(lVar2 + -8);
  lVar12 = (long)&local_80 - (*(long *)(lVar11 + 0x40) + 0xfU & 0xfffffffffffffff0);
  pcVar9 = "name";
  IVar3 = _objc_msgSend(unaff_x20,"name");
  local_78 = 0x6e776f6e6b6e753c;
  if (IVar3 == 0) {
    pcVar9 = (char *)0xe90000000000003e;
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
    IVar14 = IVar3;
  }
  IVar3 = _objc_msgSend(unaff_x20,"songSection");
  local_80 = pcVar15;
  if (((IVar3 != 0) && (IVar3 = _objc_msgSend(IVar3,"arrangement"), IVar3 != 0)) &&
     (IVar3 = _objc_msgSend(IVar3,"song"), IVar3 != 0)) {
    pcVar15 = "title";
    IVar3 = _objc_msgSend(IVar3,"title");
    if (IVar3 != 0) {
      __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
      local_80 = pcVar15;
      local_78 = IVar3;
    }
  }
  puVar4 = &DAT_100af52f0;
  FUN_100021774();
  _swift_allocObject();
  *(undefined8 *)(puVar4 + 0x18) = 0xe;
  *(undefined8 *)(puVar4 + 0x10) = 7;
  pcVar15 = "storedUUID";
  IVar3 = _objc_msgSend(unaff_x20,"storedUUID");
  if (IVar3 == 0) {
    __s10Foundation4UUIDVACycfC(lVar12);
    __s10Foundation4UUIDV10uuidStringSSvg();
    (**(code **)(lVar11 + 8))(lVar12,lVar2);
    IVar5 = IVar3;
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar3,pcVar15);
    _objc_msgSend(unaff_x20,"setStoredUUID:",IVar5);
  }
  else {
    __sSS10FoundationE36_unconditionallyBridgeFromObjectiveCySSSo8NSStringCSgFZ();
  }
  local_70 = 0x5555;
  uStack_6e = 0x203a4449;
  uStack_68 = 0xe600000000000000;
  __sSS6appendyySSF(IVar3,pcVar15);
  _swift_bridgeObjectRelease(pcVar15);
  *(ulong *)(puVar4 + 0x20) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x28) = uStack_68;
  local_70 = 0x614e;
  uStack_6e = 0x203a656d;
  uStack_68 = 0xe600000000000000;
  __sSS6appendyySSF(IVar14,pcVar9);
  _swift_bridgeObjectRelease(pcVar9);
  *(ulong *)(puVar4 + 0x30) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x38) = uStack_68;
  pcVar9 = "storedSequenceTimecode";
  _objc_msgSend(unaff_x20,"storedSequenceTimecode");
  __sSd11descriptionSSvg();
  local_70 = 0x13;
  uStack_6e = 0xd00000000000;
  uStack_68 = 0x8000000100912200;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(pcVar9);
  *(ulong *)(puVar4 + 0x40) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x48) = uStack_68;
  pcVar9 = "storedSampleTimecode";
  _objc_msgSend(unaff_x20,"storedSampleTimecode");
  __sSd11descriptionSSvg();
  local_70 = 0x11;
  uStack_6e = 0xd00000000000;
  uStack_68 = 0x8000000100912220;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(pcVar9);
  *(ulong *)(puVar4 + 0x50) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x58) = uStack_68;
  IVar14 = _objc_msgSend(unaff_x20,"transitionBeats");
  local_70 = (undefined2)IVar14;
  puVar6 = PTR___ss5Int16Vs23CustomStringConvertiblesWP_100a1df10;
  __ss23CustomStringConvertibleP11descriptionSSvgTj(PTR___ss5Int16VN_100a1def8);
  local_70 = 0x12;
  uStack_6e = 0xd00000000000;
  uStack_68 = 0x8000000100912240;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease();
  *(ulong *)(puVar4 + 0x60) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x68) = uStack_68;
  FUN_100822b68();
  if (((ulong)puVar6 & 0xc000000000000001) == 0) {
    puVar13 = *(undefined **)(puVar6 + 0x10);
  }
  else {
    puVar13 = (undefined *)((ulong)puVar6 & 0xffffffffffffff8);
    if ((long)puVar6 < 0) {
      puVar13 = puVar6;
    }
    __ss10__CocoaSetV5countSivg();
  }
  IVar14 = local_78;
  pcVar9 = local_80;
  _swift_bridgeObjectRelease();
  local_70 = SUB82(puVar13,0);
  uStack_6e = (undefined6)((ulong)puVar13 >> 0x10);
  puVar6 = PTR___sSis23CustomStringConvertiblesWP_100a1dda8;
  __ss23CustomStringConvertibleP11descriptionSSvgTj
            (PTR___sSiN_100a1dd88,PTR___sSis23CustomStringConvertiblesWP_100a1dda8);
  local_70 = 0x7449;
  uStack_6e = 0x6f6320736d65;
  uStack_68 = 0xed0000203a746e75;
  __sSS6appendyySSF();
  _swift_bridgeObjectRelease(puVar6);
  *(ulong *)(puVar4 + 0x70) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x78) = uStack_68;
  local_70 = 0x6f53;
  uStack_6e = 0x74697420676e;
  uStack_68 = 0xec000000203a656c;
  __sSS6appendyySSF(IVar14,pcVar9);
  _swift_bridgeObjectRelease(pcVar9);
  *(ulong *)(puVar4 + 0x80) = CONCAT62(uStack_6e,local_70);
  *(undefined8 *)(puVar4 + 0x88) = uStack_68;
  local_70 = SUB82(puVar4,0);
  uStack_6e = (undefined6)((ulong)puVar4 >> 0x10);
  puVar6 = &DAT_100af52f8;
  FUN_100021774(&DAT_100af52f8);
  puVar7 = &DAT_100af5300;
  FUN_100023140(&DAT_100af5300,FUN_1000265c0,PTR___sSayxGSKsMc_100a1dd28);
  uVar8 = 0x203b;
  uVar10 = 0xe200000000000000;
  __sSKsSS7ElementRtzrlE6joined9separatorS2S_tF(0x203b,0xe200000000000000,puVar6,puVar7);
  _swift_bridgeObjectRelease(puVar4);
  local_70 = 0x10;
  uStack_6e = 0xd00000000000;
  uStack_68 = 0x8000000100912260;
  __sSS6appendyySSF(uVar8,uVar10);
  _swift_bridgeObjectRelease(uVar10);
  auVar1._2_6_ = uStack_6e;
  auVar1._0_2_ = local_70;
  auVar1._8_8_ = uStack_68;
  return auVar1;
}

// ==== 100824b08 FUN_100824b08 ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

ID FUN_100824b08(double param_1,double param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,long param_7,undefined4 param_8)

{
  undefined *puVar1;
  long lVar2;
  ID IVar3;
  ID self;
  undefined8 uVar4;
  char *pcVar5;
  ID unaff_x20;
  long lVar6;
  undefined1 *puVar7;
  code *pcVar8;
  long lVar9;
  double dVar10;
  undefined1 auStack_90 [8];
  undefined8 local_88;
  long local_80;
  undefined4 local_74;
  
  puVar1 = &DAT_100af5490;
  local_88 = param_5;
  local_80 = param_7;
  local_74 = param_8;
  FUN_100021774();
  puVar7 = auStack_90 + -(*(long *)(*(long *)(puVar1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  __s10Foundation4UUIDVMa();
  lVar9 = *(long *)(lVar2 + -8);
  lVar6 = (long)puVar7 - (*(long *)(lVar9 + 0x40) + 0xfU & 0xfffffffffffffff0);
  _objc_allocWithZone();
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar3 = _objc_msgSend(DAT_100b755c8,"viewContext");
  pcVar5 = "initWithContext:";
  self = _objc_msgSend(unaff_x20,"initWithContext:",IVar3);
  IVar3 = self;
  __s10Foundation4UUIDVACycfC(lVar6);
  __s10Foundation4UUIDV10uuidStringSSvg();
  (**(code **)(lVar9 + 8))(lVar6,lVar2);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(IVar3,pcVar5);
  _swift_bridgeObjectRelease(pcVar5);
  _objc_msgSend(self,"setStoredUUID:",IVar3);
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_3,param_4);
  _swift_bridgeObjectRelease(param_4);
  _objc_msgSend(self,"setName:",param_3);
  uVar4 = local_88;
  __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(local_88,param_6);
  _swift_bridgeObjectRelease(param_6);
  _objc_msgSend(self,"setDetails:",uVar4);
  _objc_msgSend(self,"setSongSection:",
                *(undefined8 *)(local_80 + _TtCC8Playback7SongMap7Element::section));
  lVar2 = 0;
  __ss25FloatingPointRoundingRuleOMa();
  pcVar8 = *(code **)(*(long *)(lVar2 + -8) + 0x38);
  (*pcVar8)(puVar7,1,1,lVar2);
  thunk_FUN_100035714(param_1,3,puVar7);
  dVar10 = param_1;
  FUN_1000f9e50(puVar7);
  FUN_100823b10();
  _objc_msgSend(self,"setStoredSampleTimecode:",param_1 / dVar10);
  (*pcVar8)(puVar7,1,1,lVar2);
  thunk_FUN_100035714(param_2,3,puVar7);
  dVar10 = param_2;
  FUN_1000f9e50(puVar7);
  FUN_100823b10();
  _objc_msgSend(self,"setStoredSequenceTimecode:",param_2 / dVar10);
  _objc_msgSend(self,"setTransitionBeats:",(ulong)(uint)(int)(short)local_74);
  _objc_msgSend(self,"setApplyTransitionLengthCorrection:",1);
  return self;
}

// ==== 10087e150 FUN_10087e150 ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

undefined8
FUN_10087e150(ulong param_1,undefined8 param_2,undefined8 param_3,char *param_4,char *param_5,
             undefined8 param_6,undefined8 param_7,undefined8 param_8,long param_9)

{
  code *pcVar1;
  uint uVar2;
  char *pcVar3;
  undefined8 uVar4;
  char *pcVar5;
  char *pcVar6;
  ID IVar7;
  ID IVar8;
  ulong uVar9;
  undefined *puVar10;
  undefined8 uVar11;
  ID IVar12;
  ID IVar13;
  ulong uVar14;
  long lVar15;
  ulong *puVar16;
  ulong *puVar17;
  ulong uVar18;
  long lVar19;
  long unaff_x20;
  long lVar20;
  long lVar21;
  ulong uVar22;
  ulong uVar23;
  ulong uVar24;
  ulong local_b8 [2];
  char *local_a8;
  ulong local_a0;
  ulong *puStack_98;
  ulong local_90;
  long lStack_88;
  ulong local_80;
  
  if ((long)param_1 < 0) {
    pcVar3 = (char *)(param_1 & 0x7fffffffffffffff);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_4,param_5);
    _objc_msgSend((ID)pcVar3,"setName:",param_4);
    __sSS10FoundationE19_bridgeToObjectiveCSo8NSStringCyF(param_7,param_8);
    _objc_msgSend((ID)pcVar3,"setDetails:",param_7);
    IVar8 = _objc_msgSend((ID)pcVar3,"transitionBeats");
    if (((uint)IVar8 & 0xffff) != ((uint)param_6 & 0xffff)) {
      _objc_msgSend((ID)pcVar3,"setApplyTransitionLengthCorrection:",1);
    }
    uVar9 = _objc_msgSend((ID)pcVar3,"setTransitionBeats:",(ulong)(uint)(int)(short)param_6);
    if (param_9 != 0) {
      FUN_100822b68();
      if ((uVar9 & 0xc000000000000001) == 0) {
        lVar19 = 0;
        uVar14 = -1L << ((ulong)*(byte *)(uVar9 + 0x20) & 0x3f);
        puVar17 = (ulong *)(uVar9 + 0x38);
        uVar18 = ~uVar14;
        uVar14 = -uVar14;
        uVar23 = 0xffffffffffffffff;
        if ((long)uVar14 < 0x40) {
          uVar23 = ~(-1L << (uVar14 & 0x3f));
        }
        uVar23 = uVar23 & *puVar17;
        uVar14 = uVar9;
      }
      else {
        uVar23 = uVar9 & 0xffffffffffffff8;
        if ((long)uVar9 < 0) {
          uVar23 = uVar9;
        }
        __ss10__CocoaSetV12makeIteratorAB0D0CyF();
        uVar11 = 0;
        FUN_1003ac3f8(0);
        puVar10 = &DAT_100afb478;
        FUN_100023140(&DAT_100afb478,FUN_1003ac3f8,PTR___sSo8NSObjectCSH10ObjectiveCMc_100a1e0f0);
        __sSh8IteratorV6_cocoaAByx_Gs10__CocoaSetVAACn_tcfC(&local_a0,uVar23,uVar11,puVar10);
        uVar9 = uVar23;
        puVar17 = puStack_98;
        uVar18 = local_90;
        lVar19 = lStack_88;
        uVar14 = local_a0;
        uVar23 = local_80;
      }
      uVar22 = uVar18 + 0x40 >> 6;
      uVar24 = uVar23;
      if (-1 < (long)uVar14) goto LAB_10087e640;
      while (__ss10__CocoaSetV8IteratorC4nextyXlSgyF(), lVar20 = lVar19, uVar9 != 0) {
        uVar11 = 0;
        local_b8[0] = uVar9;
        FUN_1003ac3f8(0);
        _swift_unknownObjectRetain(uVar9);
        _swift_dynamicCast(&local_a8,local_b8,PTR___syXlN_100a1e030 + 8,uVar11,7);
        pcVar5 = local_a8;
        _swift_unknownObjectRelease(uVar9);
        uVar9 = uVar24;
        while( true ) {
          uVar23 = uVar9;
          if (pcVar5 == (char *)0x0) goto LAB_10087e7b8;
          _objc_msgSend((ID)pcVar3,"removeStoredItemsObject:",pcVar5);
          if (DAT_100ade9d8 != -1) {
            _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
          }
          IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
          _objc_msgSend(IVar8,"deleteObject:",pcVar5);
          uVar9 = 0;
          uVar24 = uVar23;
          if ((long)uVar14 < 0) break;
LAB_10087e640:
          uVar9 = uVar23;
          lVar21 = lVar19;
          lVar20 = lVar19;
          if (uVar23 == 0) {
            lVar21 = lVar19 + 1;
            if (SCARRY8(lVar19,1)) {
                    /* WARNING: Does not return */
              pcVar1 = (code *)SoftwareBreakpoint(1,0x10087ece4);
              (*pcVar1)();
            }
            if ((long)uVar22 <= lVar21) {
LAB_10087e7b4:
              uVar24 = 0;
              goto LAB_10087e7b8;
            }
            uVar9 = puVar17[lVar21];
            if (uVar9 == 0) {
              lVar21 = lVar19 + 2;
              if ((long)uVar22 <= lVar21) goto LAB_10087e7b4;
              uVar9 = puVar17[lVar21];
              if (uVar9 == 0) {
                lVar21 = lVar19 + 3;
                if ((long)uVar22 <= lVar21) goto LAB_10087e7b4;
                uVar9 = puVar17[lVar21];
                if (uVar9 == 0) {
                  lVar21 = lVar19 + 4;
                  if ((long)uVar22 <= lVar21) goto LAB_10087e7b4;
                  uVar9 = puVar17[lVar21];
                  if (uVar9 == 0) {
                    lVar21 = lVar19 + 5;
                    if ((long)uVar22 <= lVar21) goto LAB_10087e7b4;
                    uVar9 = puVar17[lVar21];
                    if (uVar9 == 0) {
                      lVar21 = lVar19 + 6;
                      if ((long)uVar22 <= lVar21) goto LAB_10087e7b4;
                      uVar9 = puVar17[lVar21];
                      if (uVar9 == 0) {
                        lVar15 = (uVar22 - 7) - lVar19;
                        puVar16 = puVar17 + lVar19 + 7;
                        do {
                          if (lVar15 == 0) goto LAB_10087e7b4;
                          lVar21 = lVar21 + 1;
                          uVar9 = *puVar16;
                          lVar15 = lVar15 + -1;
                          puVar16 = puVar16 + 1;
                        } while (uVar9 == 0);
                      }
                    }
                  }
                }
              }
            }
          }
          uVar24 = (uVar9 & 0xaaaaaaaaaaaaaaaa) >> 1 | (uVar9 & 0x5555555555555555) << 1;
          uVar24 = (uVar24 & 0xcccccccccccccccc) >> 2 | (uVar24 & 0x3333333333333333) << 2;
          uVar24 = (uVar24 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar24 & 0xf0f0f0f0f0f0f0f) << 4;
          uVar24 = (uVar24 & 0xff00ff00ff00ff00) >> 8 | (uVar24 & 0xff00ff00ff00ff) << 8;
          uVar24 = (uVar24 & 0xffff0000ffff0000) >> 0x10 | (uVar24 & 0xffff0000ffff) << 0x10;
          pcVar5 = *(char **)(*(long *)(uVar14 + 0x30) +
                             (lVar21 << 9 | LZCOUNT(uVar24 >> 0x20 | uVar24 << 0x20) << 3));
          lVar19 = lVar21;
          uVar9 = uVar9 - 1 & uVar9;
          uVar24 = uVar23;
        }
      }
LAB_10087e7b8:
      FUN_10003bf10(uVar14,puVar17,uVar18,lVar20,uVar24);
      FUN_10058bfd0(param_1,param_2,param_3);
      FUN_100823c88(param_9,pcVar3);
      FUN_10058bff0(param_1,param_2,param_3);
    }
  }
  else {
    FUN_100823c68(0);
    _swift_bridgeObjectRetain(param_5);
    _swift_bridgeObjectRetain(param_8);
    FUN_10058bfd0(param_1,param_2,param_3);
    FUN_100824b08(param_2,param_3,param_4,param_5,param_7,param_8,param_1,param_6);
    pcVar3 = param_4;
    FUN_100465034();
    if (pcVar3 != (char *)0x0) {
      FUN_1003fa474(1);
    }
    lVar20 = _TtC8Playback22WaveformViewController::currentSetlist;
    lVar19 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
    _swift_unknownObjectWeakLoadStrong();
    if (lVar19 != 0) {
      FUN_1004ab720(1);
    }
    IVar8 = unaff_x20 + lVar20;
    _swift_unknownObjectWeakLoadStrong();
    if ((IVar8 != 0) &&
       (FUN_1004a9df0(), lVar19 = _TtC8Playback4Song::privateWorkingCopyArrangement, IVar8 != 0)) {
      pcVar3 = *(char **)(IVar8 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (pcVar3 == (char *)0x0) {
        param_5 = "workingCopyArrangementID";
        pcVar5 = (char *)_objc_msgSend(IVar8,"workingCopyArrangementID");
        if (pcVar5 != (char *)0x0) {
          pcVar6 = pcVar5;
          FUN_10032ee88();
          pcVar3 = pcVar6;
          FUN_1005e3b94();
          _swift_bridgeObjectRelease(pcVar6);
          param_5 = pcVar5;
          if (pcVar3 != (char *)0x0) {
            *(char **)(IVar8 + lVar19) = pcVar3;
            goto LAB_10087e2a8;
          }
        }
      }
      else {
LAB_10087e2a8:
        uVar2 = 0;
        FUN_1002dce60();
        if ((uVar2 & 0xff) != 1) {
          if (DAT_100adfa98 != -1) {
            _swift_once(&DAT_100adfa98,FUN_100549fc4);
          }
          *(undefined1 *)(DAT_100b773d0 + 0x6a) = 9;
        }
        param_5 = "setAutomationSaveStateValue:";
        param_7 = 1;
        _objc_msgSend((ID)pcVar3,"setAutomationSaveStateValue:",1);
      }
    }
    if (param_9 != 0) {
      param_5 = param_4;
      FUN_100823c88(param_9);
    }
    uVar11 = 0;
    FUN_100465288();
    pcVar3 = param_4;
    if (param_5 == (char *)0x0) {
      FUN_10058bff0(param_1,param_2,param_3);
    }
    else {
      uVar4 = 0;
      FUN_100881e0c(0);
      FUN_10087fea8(uVar11,param_5,param_7,0,0,uVar4);
      FUN_10058bff0(param_1,param_2,param_3);
    }
  }
  lVar20 = _TtC8Playback22WaveformViewController::currentSetlist;
  lVar19 = unaff_x20 + _TtC8Playback22WaveformViewController::currentSetlist;
  local_a8 = pcVar3;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar19 != 0) {
    FUN_1004ab720(1);
  }
  IVar8 = unaff_x20 + lVar20;
  _swift_unknownObjectWeakLoadStrong();
  if ((IVar8 != 0) &&
     (FUN_1004a9df0(), lVar19 = _TtC8Playback4Song::privateWorkingCopyArrangement, IVar8 != 0)) {
    IVar7 = *(ID *)(IVar8 + _TtC8Playback4Song::privateWorkingCopyArrangement);
    if (IVar7 == 0) {
      IVar12 = _objc_msgSend(IVar8,"workingCopyArrangementID");
      if (IVar12 != 0) {
        IVar13 = IVar12;
        FUN_10032ee88();
        IVar7 = IVar13;
        FUN_1005e3b94(IVar13,IVar12);
        _swift_bridgeObjectRelease(IVar13);
        if (IVar7 != 0) {
          *(ID *)(IVar8 + lVar19) = IVar7;
          goto LAB_10087e88c;
        }
      }
    }
    else {
LAB_10087e88c:
      uVar2 = 0;
      FUN_1002dce60();
      if ((uVar2 & 0xff) != 1) {
        if (DAT_100adfa98 != -1) {
          _swift_once(&DAT_100adfa98,FUN_100549fc4);
        }
        *(undefined1 *)(DAT_100b773d0 + 0x6a) = 9;
      }
      _objc_msgSend(IVar7,"setAutomationSaveStateValue:",1);
    }
  }
  if (DAT_100ade9d8 != -1) {
    _swift_once(&DAT_100ade9d8,FUN_1000f0ce4);
  }
  IVar8 = _objc_msgSend(DAT_100b755c8,"viewContext");
  FUN_1000f0934(IVar8);
  FUN_1005f2f10(0,1);
  FUN_1005f0ebc();
  lVar20 = *(long *)(unaff_x20 + _TtC8Playback22WaveformViewController::automationMarkerViews);
  lVar19 = lVar20;
  _swift_bridgeObjectRetain();
  FUN_100876308();
  _swift_bridgeObjectRelease(lVar20);
  if (lVar19 != 0) {
    FUN_1005f1fc8(lVar19,1,1);
  }
  uVar9 = 1;
  FUN_10071ac0c();
  if ((uVar9 & 1) != 0) {
    return 0;
  }
  puVar10 = &_OBJC_CLASS___UIApplication;
  _swift_getInitializedObjCClass();
  IVar8 = _objc_msgSend((ID)puVar10,"sharedApplication");
  IVar8 = _objc_msgSend(IVar8,"delegate");
  if (IVar8 == 0) {
    return 0;
  }
  uVar11 = 0;
  FUN_100842dec(0);
  IVar7 = IVar8;
  _swift_dynamicCastClass(IVar8,uVar11);
  if ((IVar7 == 0) || (*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window) == 0)) {
    _swift_unknownObjectRelease(IVar8);
    return 0;
  }
  IVar7 = _objc_msgSend(*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window),"rootViewController");
  if (IVar7 == 0) {
    _swift_unknownObjectRelease(IVar8);
    return 0;
  }
  uVar4 = 0;
  FUN_100413a94(0);
  _swift_dynamicCastClass(IVar7,uVar4);
  _swift_unknownObjectRelease(IVar8);
  if (IVar7 == 0) {
    return 0;
  }
  if (*(long *)(IVar7 + _TtC8Playback18MainViewController::mixerViewController) == 0) {
    return 0;
  }
  lVar19 = *(long *)(IVar7 + _TtC8Playback18MainViewController::mixerViewController) +
           _TtC8Playback19MixerViewController::tracksCollectionView;
  _swift_unknownObjectWeakLoadStrong();
  if (lVar19 == 0) {
    return 0;
  }
  IVar8 = _objc_msgSend((ID)puVar10,"sharedApplication");
  IVar8 = _objc_msgSend(IVar8,"delegate");
  if (IVar8 != 0) {
    IVar7 = IVar8;
    _swift_dynamicCastClass(IVar8,uVar11);
    if ((IVar7 == 0) || (*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window) == 0)) {
      _swift_unknownObjectRelease(IVar8);
      IVar8 = 0;
      goto LAB_10087ec94;
    }
    IVar7 = _objc_msgSend(*(ID *)(IVar7 + _TtC8Playback11AppDelegate::window),"rootViewController");
    if (IVar7 != 0) {
      _swift_dynamicCastClass(IVar7,uVar4);
      _swift_unknownObjectRelease(IVar8);
      IVar8 = 0;
      if (IVar7 != 0) {
        IVar8 = _objc_msgSend(IVar7,"view");
      }
      goto LAB_10087ec94;
    }
    _swift_unknownObjectRelease(IVar8);
  }
  IVar8 = 0;
LAB_10087ec94:
  FUN_100881e0c(0);
  FUN_10087fea8(1,lVar19,IVar8,0,0);
  return 0;
}

// ==== 1008c6328 _$s9Alamofire0A9ExtensionV0A5ImageSo11UIImageViewCRbzlE03setC014withURLRequest8cacheKey011placeholderC010serializer6filter8progress0N5Queue15imageTransition03runcQ8IfCached10completionyAA0H11Convertible_p_SSSgSo0D0CSgAD0C18ResponseSerializerCSgAD0C6Filter_pSgySo10NSProgressCYbcSgSo17OS_dispatch_queueCAfDE0cQ0OSbyAA04DataW0VyAuD8AFIErrorOGcSgtF ====
void __s9Alamofire0A9ExtensionV0A5ImageSo11UIImageViewCRbzlE03setC014withURLRequest8cacheKey011placeholderC010serializer6filter8progress0N5Queue15imageTransition03runcQ8IfCached10completionyAA0H11Convertible_p_SSSgSo0D0CSgAD0C18ResponseSerializerCSgAD0C6Filter_pSgySo10NSProgressCYbcSgSo17OS_dispatch_queueCAfDE0cQ0OSbyAA04DataW0VyAuD8AFIErrorOGcSgtF
               (void)

{
                    /* WARNING: Could not recover jumptable at 0x0001008c6330. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)
    PTR___s9Alamofire0A9ExtensionV0A5ImageSo11UIImageViewCRbzlE03setC014withURLRequest8cacheKey011placeholderC010serializer6filter8progress0N5Queue15imageTransition03runcQ8IfCached10completionyAA0H11Convertible_p_SSSgSo0D0CSgAD0C18ResponseSerializerCSgAD0C6Filter_pSgySo10NSProgressCYbcSgSo17OS_dispatch_queueCAfDE0cQ0OSbyAA04DataW0VyAuD8AFIErrorOGcSgtF_100a9e978
  )();
  return;
}

