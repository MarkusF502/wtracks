// Playback (Ghidra 12.1.4), segunda passada da Fase 2. Gerado por tool/playback_lookup.py fn 1004f9cd8 0
// ===== FUN_1004f9cd8 @ 1004f9cd8 (depth 0)

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x0001004fab94) */
/* WARNING: Removing unreachable block (ram,0x0001004fad48) */
/* WARNING: Removing unreachable block (ram,0x0001004fad50) */
/* WARNING: Removing unreachable block (ram,0x0001004fadfc) */
/* WARNING: Removing unreachable block (ram,0x0001004fad98) */
/* WARNING: Removing unreachable block (ram,0x0001004fae04) */

void FUN_1004f9cd8(double param_1,ID param_2)

{
  undefined1 *puVar1;
  code *pcVar2;
  undefined *puVar3;
  long lVar4;
  ID IVar5;
  ulong uVar6;
  long lVar7;
  ID IVar8;
  ID IVar9;
  ID IVar10;
  ID IVar11;
  undefined *puVar12;
  long *plVar13;
  uint uVar14;
  long *plVar15;
  ulong uVar16;
  long unaff_x20;
  ulong uVar17;
  undefined8 uVar18;
  ulong uVar19;
  long lVar20;
  ulong uVar21;
  long lVar22;
  long lVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  undefined1 auStack_170 [8];
  ulong local_168;
  ulong local_160;
  long local_158;
  long local_150;
  undefined1 *local_148;
  ID local_140;
  double local_138 [21];
  
  puVar3 = &DAT_100af5490;
  FUN_100021774();
  local_148 = auStack_170 + -(*(long *)(*(long *)(puVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  FUN_10032c3bc();
  lVar20 = _TtC8Playback4Song::privateSongMap;
  local_140 = param_2;
  if (((ulong)puVar3 & 1) != 0) {
    lVar4 = *(long *)(param_2 + _TtC8Playback4Song::privateSongMap);
    lVar23 = lVar4;
    if (lVar4 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar4 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      param_1 = 0.0;
      *(undefined8 *)(lVar4 + 0x28) = 0;
      *(undefined8 *)(lVar4 + 0x20) = 0;
      *(undefined8 *)(lVar4 + 0x38) = 0;
      *(undefined8 *)(lVar4 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar4 + 0x10,param_2);
      _swift_retain(puVar3);
      FUN_10085ee38();
      uVar18 = *(undefined8 *)(param_2 + lVar20);
      *(long *)(param_2 + lVar20) = lVar4;
      _swift_retain(lVar4);
      _swift_release(uVar18);
      lVar23 = 0;
    }
    uVar17 = *(ulong *)(lVar4 + 0x18);
    _swift_retain(lVar23);
    _swift_bridgeObjectRetain(uVar17);
    _swift_release(lVar4);
    if (uVar17 >> 0x3e == 0) {
      uVar19 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar19 = uVar17 & 0xffffffffffffff8;
      if ((long)uVar17 < 0) {
        uVar19 = uVar17;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar19 != 0) {
      if ((long)uVar19 < 1) {
        (*pcVar2)();
      }
      uVar21 = 0;
      do {
        if ((uVar17 & 0xc000000000000001) == 0) {
          uVar6 = *(ulong *)(uVar17 + uVar21 * 8 + 0x20);
          _swift_retain(uVar6);
        }
        else {
          uVar6 = uVar21;
          FUN_1000cc314(uVar21,uVar17);
        }
        uVar21 = uVar21 + 1;
        IVar5 = _objc_msgSend(*(ID *)(uVar6 + _TtCC8Playback7SongMap7Element::section),
                              "presetInfiniteLoop");
        *(char *)(uVar6 + _TtCC8Playback7SongMap7Element::privateInfiniteLoop) = (char)IVar5;
        _swift_release(uVar6);
      } while (uVar19 != uVar21);
    }
    _swift_bridgeObjectRelease(uVar17);
  }
  lVar20 = _TtC8Playback4Song::privateSongMap;
  IVar5 = *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::song);
  lVar4 = *(long *)(IVar5 + _TtC8Playback4Song::privateSongMap);
  lVar23 = lVar4;
  if (lVar4 == 0) {
    FUN_100861310();
    _swift_allocObject();
    puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
    *(undefined **)(lVar4 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
    param_1 = 0.0;
    *(undefined8 *)(lVar4 + 0x28) = 0;
    *(undefined8 *)(lVar4 + 0x20) = 0;
    *(undefined8 *)(lVar4 + 0x38) = 0;
    *(undefined8 *)(lVar4 + 0x30) = 0;
    _swift_unknownObjectUnownedInit(lVar4 + 0x10,IVar5);
    _swift_retain(puVar3);
    FUN_10085ee38();
    uVar18 = *(undefined8 *)(IVar5 + lVar20);
    *(long *)(IVar5 + lVar20) = lVar4;
    _swift_retain(lVar4);
    _swift_release(uVar18);
    lVar23 = 0;
  }
  uVar17 = *(ulong *)(lVar4 + 0x18);
  _swift_retain(lVar23);
  _swift_bridgeObjectRetain(uVar17);
  _swift_release(lVar4);
  if (uVar17 >> 0x3e == 0) {
    uVar19 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
  }
  else {
    uVar19 = uVar17 & 0xffffffffffffff8;
    if ((long)uVar17 < 0) {
      uVar19 = uVar17;
    }
    __ss18_CocoaArrayWrapperV8endIndexSivg();
  }
  if (uVar19 != 0) {
    if ((long)uVar19 < 1) {
      (*pcVar2)();
    }
    uVar21 = 0;
    do {
      if ((uVar17 & 0xc000000000000001) == 0) {
        uVar6 = *(ulong *)(uVar17 + uVar21 * 8 + 0x20);
        _swift_retain();
      }
      else {
        uVar6 = uVar21;
        FUN_1000cc314(uVar21,uVar17);
      }
      uVar21 = uVar21 + 1;
      *(undefined8 *)(uVar6 + _TtCC8Playback7SongMap7Element::liveLoopCount) = 0;
      *(undefined1 *)(uVar6 + _TtCC8Playback7SongMap7Element::privateInfiniteLoop) = 0;
      _swift_release();
    } while (uVar19 != uVar21);
  }
  _swift_bridgeObjectRelease(uVar17);
  FUN_1004f5264();
  IVar11 = local_140;
  uVar17 = _objc_msgSend(local_140,"contentTypeID");
  FUN_100419df0();
  dVar27 = 5.0;
  if (((uint)uVar17 & 0xff) != 0xd) {
    FUN_100322198();
    if (uVar17 >> 0x3e == 0) {
      if (*(long *)((uVar17 & 0xfffffffffffff8) + 0x10) == 0) goto LAB_1004fa0d8;
LAB_1004fa038:
      if ((uVar17 & 0xc000000000000001) == 0) {
        if (*(long *)((uVar17 & 0xfffffffffffff8) + 0x10) == 0) {
          (*pcVar2)();
        }
        IVar10 = *(ID *)(uVar17 + 0x20);
      }
      else {
        IVar10 = 0;
        FUN_1000cc2ec();
      }
      _swift_bridgeObjectRelease();
      FUN_1003221bc();
      if (uVar17 == 0) goto LAB_1004fa0dc;
      if (*(long *)(uVar17 + 0x10) == 0) goto LAB_1004fa0d8;
      lVar23 = *(long *)(uVar17 + 0x40);
      lVar4 = *(long *)(uVar17 + 0x48);
      _swift_bridgeObjectRelease();
      IVar9 = _objc_msgSend(IVar10,"storedBPM");
      if (IVar9 == 0) {
        dVar27 = 0.0;
      }
      else {
        _objc_msgSend(IVar9,"doubleValue");
        dVar27 = param_1;
      }
      IVar10 = _objc_msgSend(IVar10,"song");
      if (IVar10 != 0) {
        FUN_1003220ec();
        dVar27 = dVar27 * (1.0 / param_1);
      }
      param_1 = 1.0 / (((double)lVar4 / 4.0) * (dVar27 / 60.0));
      dVar27 = param_1 * (double)lVar23;
    }
    else {
      uVar19 = uVar17 & 0xffffffffffffff8;
      if ((long)uVar17 < 0) {
        uVar19 = uVar17;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
      if (uVar19 != 0) goto LAB_1004fa038;
LAB_1004fa0d8:
      _swift_bridgeObjectRelease();
LAB_1004fa0dc:
      dVar27 = 2.0;
    }
    lVar23 = _TtC8Playback4Song::privateSongMap;
    lVar7 = *(long *)(IVar11 + _TtC8Playback4Song::privateSongMap);
    lVar4 = lVar7;
    if (lVar7 == 0) {
      FUN_100861310();
      _swift_allocObject();
      puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
      *(undefined **)(lVar7 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
      param_1 = 0.0;
      *(undefined8 *)(lVar7 + 0x28) = 0;
      *(undefined8 *)(lVar7 + 0x20) = 0;
      *(undefined8 *)(lVar7 + 0x38) = 0;
      *(undefined8 *)(lVar7 + 0x30) = 0;
      _swift_unknownObjectUnownedInit(lVar7 + 0x10,IVar11);
      _swift_retain(puVar3);
      FUN_10085ee38();
      uVar18 = *(undefined8 *)(IVar11 + lVar23);
      *(long *)(IVar11 + lVar23) = lVar7;
      _swift_retain(lVar7);
      _swift_release(uVar18);
      lVar4 = 0;
    }
    uVar17 = *(ulong *)(lVar7 + 0x18);
    _swift_retain(lVar4);
    _swift_bridgeObjectRetain(uVar17);
    _swift_release(lVar7);
    if (uVar17 >> 0x3e == 0) {
      uVar19 = *(ulong *)((uVar17 & 0xfffffffffffff8) + 0x10);
    }
    else {
      uVar19 = uVar17 & 0xffffffffffffff8;
      if ((long)uVar17 < 0) {
        uVar19 = uVar17;
      }
      __ss18_CocoaArrayWrapperV8endIndexSivg();
    }
    if (uVar19 == 0) {
      _swift_bridgeObjectRelease(uVar17);
      return;
    }
    if ((uVar17 & 0xc000000000000001) == 0) {
      if (*(long *)((uVar17 & 0xfffffffffffff8) + 0x10) == 0) {
        (*pcVar2)();
      }
      lVar23 = *(long *)(uVar17 + 0x20);
      _swift_retain(lVar23);
    }
    else {
      lVar23 = 0;
      FUN_1000cc314(0,uVar17);
    }
    _swift_bridgeObjectRelease();
    uVar14 = (uint)uVar17;
    FUN_1000344fc();
    lVar4 = _TtC8Playback4Song::privateWorkingCopyArrangement;
    if ((uVar14 & 0xff) == 0x19) {
      IVar10 = *(ID *)(IVar11 + _TtC8Playback4Song::privateWorkingCopyArrangement);
      if (IVar10 == 0) {
        IVar9 = _objc_msgSend(IVar11,"workingCopyArrangementID");
        if (IVar9 != 0) {
          IVar8 = IVar9;
          FUN_10032ee88();
          IVar10 = IVar8;
          FUN_1005e3b94(IVar8,IVar9);
          _swift_bridgeObjectRelease(IVar8);
          if (IVar10 != 0) {
            *(ID *)(IVar11 + lVar4) = IVar10;
            goto LAB_1004fa270;
          }
        }
      }
      else {
LAB_1004fa270:
        _objc_msgSend(IVar10,"storedStartTime");
        dVar24 = param_1;
        IVar10 = _objc_msgSend(IVar10,"song");
        dVar26 = dVar24;
        dVar25 = param_1;
        if (IVar10 != 0) {
          FUN_1003220ec();
          dVar26 = param_1 * dVar24;
          dVar25 = param_1 * dVar24;
        }
        param_1 = dVar26;
        if (dVar25 == 0.0) {
          if (DAT_100adfbb8 != -1) {
            _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
          }
          uVar14 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
          if ((uVar14 == 1) ||
             ((uVar14 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
            plVar13 = &_TtCC8Playback7SongMap7Element::fullTimelineStartTime;
            plVar15 = &_TtCC8Playback7SongMap7Element::fullTimelineEndTime;
          }
          else {
            plVar13 = &_TtCC8Playback7SongMap7Element::trimTimelineStartTime;
            plVar15 = &_TtCC8Playback7SongMap7Element::trimTimelineEndTime;
          }
          param_1 = *(double *)(lVar23 + *plVar15);
          dVar24 = *(double *)(lVar23 + *plVar13);
          _swift_release(lVar23);
          param_1 = param_1 - dVar24;
          dVar27 = dVar27 + param_1;
          goto LAB_1004fa408;
        }
      }
    }
    _swift_release(lVar23);
    dVar27 = dVar27 + dVar27;
  }
LAB_1004fa408:
  lVar23 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  IVar9 = *(ID *)(IVar5 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  IVar10 = IVar9;
  dVar24 = param_1;
  if (IVar9 == 0) {
    IVar9 = _objc_msgSend(IVar5,"workingCopyArrangementID");
    if (IVar9 != 0) {
      IVar8 = IVar9;
      FUN_10032ee88();
      IVar10 = IVar8;
      FUN_1005e3b94(IVar8,IVar9);
      _swift_bridgeObjectRelease(IVar8);
      if (IVar10 != 0) {
        *(ID *)(IVar5 + lVar23) = IVar10;
        IVar9 = 0;
        dVar24 = param_1;
        goto LAB_1004fa41c;
      }
    }
  }
  else {
LAB_1004fa41c:
    FUN_1004f240c(IVar9);
    dVar26 = dVar24;
    _objc_msgSend(IVar10,"storedEndTime");
    dVar25 = dVar26;
    IVar9 = _objc_msgSend(IVar10,"song");
    if (IVar9 == 0) {
      dVar25 = 1.0;
    }
    else {
      FUN_1003220ec();
    }
    param_1 = dVar26 * dVar25 - dVar27;
    if (param_1 <= dVar24) {
      _objc_msgSend(IVar10,"storedEndTime");
      dVar24 = param_1;
      IVar10 = _objc_msgSend(IVar10,"song");
      if (IVar10 == 0) {
        dVar27 = 1.0;
      }
      else {
        FUN_1003220ec();
        dVar27 = dVar24;
      }
      FUN_1004f240c(0);
      dVar27 = param_1 * dVar27 - dVar24;
      param_1 = dVar24;
    }
  }
  if (DAT_100adef08 != -1) {
    _swift_once(&DAT_100adef08,FUN_1002c44b8);
  }
  uVar17 = DAT_100b75e40;
  uVar19 = DAT_100b75e40;
  _swift_retain();
  FUN_1004f240c();
  dVar24 = param_1;
  FUN_10032c3bc();
  if ((uVar19 & 1) == 0) {
    IVar10 = _objc_msgSend(IVar5,"contentTypeID");
    uVar14 = (uint)IVar10;
    FUN_100419df0();
    if ((uVar14 & 0xff) == 0xd) goto LAB_1004fa5d0;
  }
  else {
LAB_1004fa5d0:
    uVar19 = *(ulong *)(unaff_x20 + _TtC8Playback9Sequencer::currentSongMapElement);
    if (uVar19 != 0) {
      local_150 = _TtC8Playback9Sequencer::currentSongMapElement;
      lVar23 = *(long *)(IVar5 + lVar20);
      if (lVar23 == 0) {
        lVar23 = 0;
        FUN_100861310();
        _swift_allocObject();
        puVar3 = PTR___swiftEmptyArrayStorage_100a1e050;
        *(undefined **)(lVar23 + 0x18) = PTR___swiftEmptyArrayStorage_100a1e050;
        dVar24 = 0.0;
        *(undefined8 *)(lVar23 + 0x28) = 0;
        *(undefined8 *)(lVar23 + 0x20) = 0;
        *(undefined8 *)(lVar23 + 0x38) = 0;
        *(undefined8 *)(lVar23 + 0x30) = 0;
        _swift_unknownObjectUnownedInit(lVar23 + 0x10,IVar5);
        _swift_retain(uVar19);
        _swift_retain(puVar3);
        FUN_10085ee38();
        uVar18 = *(undefined8 *)(IVar5 + lVar20);
        *(long *)(IVar5 + lVar20) = lVar23;
        _swift_retain(lVar23);
        _swift_release(uVar18);
        lVar20 = 0;
      }
      else {
        _swift_retain(uVar19);
        lVar20 = lVar23;
      }
      uVar21 = *(ulong *)(lVar23 + 0x18);
      _swift_retain(lVar20);
      _swift_bridgeObjectRetain(uVar21);
      _swift_release(lVar23);
      if (uVar21 >> 0x3e == 0) {
        uVar6 = *(ulong *)((uVar21 & 0xfffffffffffff8) + 0x10);
      }
      else {
        uVar6 = uVar21 & 0xffffffffffffff8;
        if ((long)uVar21 < 0) {
          uVar6 = uVar21;
        }
        __ss18_CocoaArrayWrapperV8endIndexSivg();
      }
      IVar11 = local_140;
      if (uVar6 == 0) {
        _swift_release(uVar19);
        _swift_bridgeObjectRelease(uVar21);
      }
      else {
        uVar16 = uVar6 - 1;
        if (SBORROW8(uVar6,1)) {
          (*pcVar2)();
        }
        if ((uVar21 & 0xc000000000000001) == 0) {
          if ((long)uVar16 < 0) {
            (*pcVar2)();
          }
          if (*(ulong *)((uVar21 & 0xfffffffffffff8) + 0x10) <= uVar16) {
            (*pcVar2)();
          }
          uVar16 = *(ulong *)(uVar21 + uVar16 * 8 + 0x20);
          _swift_retain(uVar16);
        }
        else {
          FUN_1000cc314(uVar16,uVar21);
        }
        _swift_bridgeObjectRelease(uVar21);
        uVar21 = uVar19 + _TtCC8Playback7SongMap7Element::uuid;
        __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar21,uVar16 + _TtCC8Playback7SongMap7Element::uuid);
        if (((uVar21 & 1) == 0) || (FUN_1004f8628(), (uVar21 & 1) == 0)) {
          if ((*(long *)(uVar17 + 0x18) != 0) &&
             (lVar20 = *(long *)(*(long *)(uVar17 + 0x18) + 0x18), lVar20 != 0)) {
            _swift_retain(lVar20);
            FUN_10064afa4();
            _swift_release(lVar20);
          }
          IVar10 = _objc_msgSend(IVar5,"clickTimes");
          if ((IVar10 != 0) && (FUN_1006a2d6c(), IVar10 != 0)) {
            local_160 = uVar17;
            lVar20 = *(long *)(IVar10 + 0x10);
            if (lVar20 == 0) {
              _swift_release(uVar16);
              _swift_release(uVar19);
              _swift_bridgeObjectRelease(IVar10);
              uVar17 = local_160;
            }
            else {
              local_158 = _TtC8Playback9Sequencer::sampleTimeCurrentTime;
              lVar23 = 0x20;
              lVar4 = local_150;
              local_168 = uVar16;
              do {
                lVar7 = DAT_100adfbb8;
                dVar26 = *(double *)(IVar10 + lVar23);
                lVar22 = *(long *)(unaff_x20 + lVar4);
                if (lVar22 == 0) {
                  dVar24 = 0.15;
                  if (0.15 < dVar26) goto LAB_1004fabd0;
                }
                else {
                  _swift_retain(lVar22);
                  if (lVar7 != -1) {
                    _swift_once(&DAT_100adfbb8,FUN_1005b50bc);
                  }
                  uVar14 = (uint)((ulong)*(long *)(DAT_100b77548 + 0x10) >> 0x3e);
                  if ((uVar14 == 1) ||
                     ((uVar14 == 2 && (*(long *)(DAT_100b77548 + 0x10) == -0x7fffffffffffffd0)))) {
                    plVar13 = &_TtCC8Playback7SongMap7Element::fullTimelineStartTime;
                  }
                  else {
                    plVar13 = &_TtCC8Playback7SongMap7Element::trimTimelineStartTime;
                  }
                  dVar28 = *(double *)(lVar22 + *plVar13);
                  uVar18 = *(undefined8 *)(unaff_x20 + local_158);
                  _swift_retain(uVar18);
                  __sSo17OS_dispatch_queueC8DispatchE4sync7executexxyKXE_tKlF
                            (local_138,FUN_100504fa8,uVar18,PTR___sSdN_100a1dd60);
                  _swift_release(uVar18);
                  dVar25 = local_138[0];
                  FUN_1000345bc(0);
                  dVar28 = dVar28 + (dVar25 - dVar24);
                  lVar4 = 0;
                  __ss25FloatingPointRoundingRuleOMa();
                  puVar1 = local_148;
                  (**(code **)(*(long *)(lVar4 + -8) + 0x38))(local_148,1,1,lVar4);
                  thunk_FUN_100035714(3,puVar1);
                  _swift_release(lVar22);
                  FUN_100023be4(puVar1,&DAT_100af5490);
                  dVar24 = dVar28 + 0.15;
                  lVar4 = local_150;
                  IVar11 = local_140;
                  if (dVar24 < dVar26) {
LAB_1004fabd0:
                    _swift_bridgeObjectRelease(IVar10);
                    _objc_msgSend(IVar11,"bpm");
                    _swift_release(local_168);
                    _swift_release(uVar19);
                    param_1 = dVar26 + (-1.0 / (dVar24 / 60.0)) * 0.25;
                    uVar17 = local_160;
                    goto LAB_1004fa988;
                  }
                }
                lVar23 = lVar23 + 8;
                lVar20 = lVar20 + -1;
              } while (lVar20 != 0);
              _swift_release(local_168);
              _swift_release(uVar19);
              _swift_bridgeObjectRelease(IVar10);
              uVar17 = local_160;
            }
            goto LAB_1004fa988;
          }
          _swift_release(uVar16);
        }
        else {
          _swift_release(uVar19);
          uVar19 = uVar16;
        }
        _swift_release(uVar19);
      }
    }
  }
LAB_1004fa988:
  *(double *)(unaff_x20 + _TtC8Playback9Sequencer::preloadNextSongSequenceTime) = param_1;
  *(double *)(unaff_x20 + _TtC8Playback9Sequencer::songTransitionDuration) = dVar27;
  *(undefined1 *)(IVar5 + _TtC8Playback4Song::isLiveCrossfading) = 1;
  *(ID *)(unaff_x20 + _TtC8Playback9Sequencer::songToLiveCrossfadeTo) = IVar11;
  if (*(long *)(uVar17 + 0x28) != 0) {
    FUN_1002c4ea4(1);
  }
  lVar20 = *(long *)(DAT_100b75e40 + 0x18);
  if (lVar20 == 0) goto LAB_1004faacc;
  uVar19 = *(ulong *)(lVar20 + 0x78);
  if (uVar19 == 0) {
    uVar19 = *(ulong *)(lVar20 + 0x10);
    FUN_10073f4a4(0);
    _swift_allocObject();
    _swift_retain(lVar20);
    FUN_10074128c();
    uVar18 = *(undefined8 *)(lVar20 + 0x78);
    *(ulong *)(lVar20 + 0x78) = uVar19;
    _swift_retain(uVar19);
    _swift_release(uVar18);
    uVar21 = 0;
  }
  else {
    _swift_retain(lVar20);
    uVar21 = uVar19;
  }
  _swift_retain(uVar21);
  _swift_release(lVar20);
  if ((*(byte *)(uVar19 + 0x39) & 1) != 0) {
    _swift_release(uVar19);
    goto LAB_1004faacc;
  }
  IVar5 = _objc_msgSend(IVar11,"contentTypeID");
  uVar14 = (uint)IVar5;
  FUN_100419df0();
  lVar20 = _TtC8Playback4Song::privateWorkingCopyArrangement;
  uVar14 = uVar14 & 0xff;
  if (((uVar14 - 0x10 < 2) || (uVar14 == 0xd)) || (uVar14 == 0x1a)) {
    _swift_release(uVar17);
    uVar17 = uVar19;
    goto LAB_1004faacc;
  }
  IVar10 = *(ID *)(IVar11 + _TtC8Playback4Song::privateWorkingCopyArrangement);
  IVar5 = IVar10;
  local_160 = uVar17;
  if (IVar10 == 0) {
    IVar10 = _objc_msgSend(IVar11,"workingCopyArrangementID");
    if (IVar10 != 0) {
      IVar9 = IVar10;
      FUN_10032ee88();
      IVar5 = IVar9;
      FUN_1005e3b94(IVar9,IVar10);
      _swift_bridgeObjectRelease(IVar9);
      if (IVar5 != 0) {
        *(ID *)(IVar11 + lVar20) = IVar5;
        IVar10 = 0;
        goto LAB_1004fab18;
      }
    }
    _swift_release(uVar19);
    uVar17 = local_160;
  }
  else {
LAB_1004fab18:
    FUN_1002dc978();
    uVar17 = local_160;
    if (IVar10 != 0) {
      IVar5 = _objc_msgSend(IVar5,"includePad");
      if ((IVar5 & 1) != 0) {
        FUN_1002e16c8();
        IVar11 = _objc_msgSend(IVar11,"keyID");
        FUN_10073b6dc(IVar10,(long)(int)IVar11,0,IVar5,dVar27,0);
        _swift_release(uVar17);
        _swift_release(uVar19);
        _swift_bridgeObjectRelease(IVar5);
        return;
      }
      if (*(char *)(uVar19 + 0x38) == '\x01') {
        if (((ulong)PTR___swiftEmptyArrayStorage_100a1e050 >> 0x3e == 0) ||
           (puVar12 = PTR___swiftEmptyArrayStorage_100a1e050,
           __ss18_CocoaArrayWrapperV8endIndexSivg(), puVar3 = PTR___swiftEmptyArrayStorage_100a1e050
           , puVar12 == (undefined *)0x0)) {
          puVar12 = PTR___swiftEmptySetSingleton_100a1e060;
          _swift_retain(PTR___swiftEmptySetSingleton_100a1e060);
        }
        else {
          puVar12 = PTR___swiftEmptyArrayStorage_100a1e050;
          _swift_retain(PTR___swiftEmptyArrayStorage_100a1e050);
          FUN_1000217d4();
          _swift_release(puVar3);
        }
        FUN_10073b6dc(0,0,1,puVar12,0,1);
        _swift_release(uVar19);
        _swift_bridgeObjectRelease(puVar12);
      }
      else {
        _swift_release(uVar19);
      }
      _swift_release(uVar17);
      return;
    }
    _swift_release(uVar19);
  }
LAB_1004faacc:
  _swift_release(uVar17);
  return;
}


