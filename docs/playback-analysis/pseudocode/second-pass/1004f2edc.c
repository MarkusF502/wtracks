// Playback (Ghidra 12.1.4), segunda passada da Fase 1. Gerado por tool/playback_lookup.py fn 1004f2edc 0
// ===== FUN_1004f2edc @ 1004f2edc (depth 0)

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


