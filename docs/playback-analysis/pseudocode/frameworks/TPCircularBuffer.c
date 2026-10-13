// TPCircularBuffer sha256 184487f468f2858879ee57cade5cd62a5ab9b54c358e9e1e602afcd19182f554 (Ghidra 12.1.4, all decompiled functions)

// ==== 00004000 __TPCircularBufferInit ====
uint __TPCircularBufferInit(vm_address_t *param_1,ulong param_2,long param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  kern_return_t kVar3;
  int iVar4;
  ulong uVar5;
  uint unaff_w21;
  int iVar6;
  vm_prot_t vStack_78;
  vm_prot_t vStack_74;
  vm_address_t local_70;
  vm_address_t local_68;
  
  puVar2 = PTR__vm_page_size_00008010;
  puVar1 = PTR__mach_task_self__00008008;
  if ((int)param_2 == 0) {
    __TPCircularBufferInit_cold_2();
  }
  else if (param_3 == 0x20) {
    iVar6 = 3;
    do {
      uVar5 = (param_2 & 0xffffffff) + 0xffffffff + *(long *)puVar2 & -*(long *)puVar2;
      *(int *)(param_1 + 1) = (int)uVar5;
      kVar3 = _vm_allocate(*(vm_map_t *)puVar1,&local_68,(uVar5 & 0x7fffffff) << 1,1);
      if (kVar3 == 0) {
        kVar3 = _vm_deallocate(*(vm_map_t *)puVar1,local_68 + (uint)param_1[1],
                               (ulong)(uint)param_1[1]);
        if (kVar3 != 0) {
          if (iVar6 == 0) {
            _mach_error_string(kVar3);
            goto LAB_000041d0;
          }
LAB_000040f8:
          _vm_deallocate(*(vm_map_t *)puVar1,local_68,(ulong)(uint)param_1[1]);
          goto LAB_00004108;
        }
        local_70 = local_68 + (uint)param_1[1];
        kVar3 = _vm_remap(*(vm_map_t *)puVar1,&local_70,(ulong)(uint)param_1[1],0,0,
                          *(vm_map_t *)puVar1,local_68,0,&vStack_74,&vStack_78,1);
        if (kVar3 == 0) {
          if (local_70 != local_68 + (uint)param_1[1]) {
            if (iVar6 != 0) {
              _vm_deallocate(*(vm_map_t *)puVar1,local_70,(ulong)(uint)param_1[1]);
              goto LAB_000040f8;
            }
            _puts("Couldn\'t map buffer memory to end of buffer");
            goto LAB_00004194;
          }
          *param_1 = local_68;
          *(undefined4 *)((long)param_1 + 0x14) = 0;
          *(undefined4 *)((long)param_1 + 0xc) = 0;
          *(undefined4 *)(param_1 + 2) = 0;
          unaff_w21 = 1;
          iVar4 = 1;
          *(undefined1 *)(param_1 + 3) = 1;
        }
        else {
          if (iVar6 != 0) goto LAB_000040f8;
          _mach_error_string(kVar3);
          _printf("%s:%d: %s: %s\n");
LAB_00004194:
          unaff_w21 = 0;
          iVar4 = 1;
          iVar6 = -1;
        }
      }
      else {
        if (iVar6 == 0) {
          _mach_error_string(kVar3);
LAB_000041d0:
          _printf("%s:%d: %s: %s\n");
          unaff_w21 = 0;
          break;
        }
LAB_00004108:
        iVar6 = iVar6 + -1;
        iVar4 = 2;
      }
    } while (iVar4 == 2);
    return unaff_w21 & 1;
  }
                    /* WARNING: Subroutine does not return */
  __TPCircularBufferInit_cold_1();
}

// ==== 00004210 _TPCircularBufferCleanup ====
kern_return_t _TPCircularBufferCleanup(vm_address_t *param_1)

{
  kern_return_t kVar1;
  
  kVar1 = _vm_deallocate(*(vm_map_t *)PTR__mach_task_self__00008008,*param_1,
                         (ulong)(uint)((int)param_1[1] << 1));
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  return kVar1;
}

// ==== 00004250 _TPCircularBufferClear ====
void _TPCircularBufferClear(long *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  
  piVar1 = (int *)((long)param_1 + 0x14);
  iVar3 = *piVar1;
  if ((iVar3 != 0) && (*param_1 != 0)) {
    uVar4 = *(uint *)(param_1 + 1);
    uVar2 = *(int *)((long)param_1 + 0xc) + iVar3;
    uVar7 = 0;
    if (uVar4 != 0) {
      uVar7 = uVar2 / uVar4;
    }
    *(uint *)((long)param_1 + 0xc) = uVar2 - uVar7 * uVar4;
    if ((*(byte *)(param_1 + 3) & 1) == 0) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = *piVar1 - iVar3;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
    }
    else {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = *piVar1 - iVar3;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
    }
    if (*piVar1 < 0) {
                    /* WARNING: Subroutine does not return */
      _TPCircularBufferConsumeNextBufferListPartial_cold_1();
    }
  }
  return;
}

// ==== 000042c4 _TPCircularBufferSetAtomic ====
void _TPCircularBufferSetAtomic(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x18) = param_2;
  return;
}

// ==== 000042cc _TPCircularBufferPrepareEmptyAudioBufferList ====
undefined8 *
_TPCircularBufferPrepareEmptyAudioBufferList
          (long *param_1,uint param_2,uint param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  uint uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong *puVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  
  uVar2 = (int)param_1[1] - *(int *)((long)param_1 + 0x14);
  if (((uVar2 == 0) || (lVar8 = *param_1, lVar8 == 0)) ||
     (uVar4 = (ulong)(param_2 - 1), (ulong)uVar2 < (ulong)(param_3 * param_2) + uVar4 * 0x10 + 0x60)
     ) {
LAB_00004320:
    puVar3 = (undefined8 *)0x0;
  }
  else {
    uVar6 = *(uint *)(param_1 + 2);
    puVar1 = (undefined8 *)(lVar8 + (ulong)uVar6);
    if (param_4 == (undefined8 *)0x0) {
      uVar9 = 0;
      uVar10 = 0;
      puVar1[5] = 0;
      puVar1[4] = 0;
      puVar1[7] = 0;
      puVar1[6] = 0;
      puVar1[3] = 0;
      puVar1[2] = 0;
    }
    else {
      uVar10 = param_4[1];
      uVar9 = *param_4;
      uVar12 = param_4[3];
      uVar11 = param_4[2];
      uVar13 = param_4[4];
      uVar15 = param_4[7];
      uVar14 = param_4[6];
      puVar1[5] = param_4[5];
      puVar1[4] = uVar13;
      puVar1[7] = uVar15;
      puVar1[6] = uVar14;
      puVar1[3] = uVar12;
      puVar1[2] = uVar11;
    }
    puVar1[1] = uVar10;
    *puVar1 = uVar9;
    _bzero(puVar1 + 9,uVar4 * 0x10 + 0x18);
    *(uint *)(puVar1 + 9) = param_2;
    puVar3 = puVar1 + uVar4 * 2 + 0xc;
    if (param_2 == 0) {
      uVar6 = (int)puVar3 - (int)puVar1;
    }
    else {
      uVar4 = (ulong)param_2;
      puVar5 = (ulong *)((ulong)uVar6 + lVar8 + 0x58);
      do {
        uVar7 = (long)puVar3 + 0xfU & 0xfffffffffffffff0;
        puVar3 = (undefined8 *)(uVar7 + param_3);
        uVar6 = (int)puVar3 - (int)puVar1;
        if (uVar2 < uVar6) goto LAB_00004320;
        *puVar5 = uVar7;
        *(undefined4 *)(puVar5 + -1) = 1;
        *(uint *)((long)puVar5 + -4) = param_3;
        puVar5 = puVar5 + 2;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    uVar6 = uVar6 + 0xf & 0xfffffff0;
    *(uint *)(puVar1 + 8) = uVar6;
    puVar3 = (undefined8 *)0x0;
    if (uVar6 <= uVar2) {
      puVar3 = puVar1 + 9;
    }
  }
  return puVar3;
}

// ==== 000043f0 _TPCircularBufferPrepareEmptyAudioBufferListWithAudioFormat ====
void _TPCircularBufferPrepareEmptyAudioBufferListWithAudioFormat
               (undefined8 param_1,long param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_2 + 0xc) >> 5 & 1) == 0) {
    uVar1 = 1;
  }
  else {
    uVar1 = *(undefined4 *)(param_2 + 0x1c);
  }
  _TPCircularBufferPrepareEmptyAudioBufferList(param_1,uVar1,*(int *)(param_2 + 0x18) * param_3);
  return;
}

// ==== 00004414 _TPCircularBufferProduceAudioBufferList ====
long * _TPCircularBufferProduceAudioBufferList
                 (long *param_1,undefined8 *param_2,long *param_3,int param_4,long param_5)

{
  int *piVar1;
  uint uVar2;
  undefined8 *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char cVar7;
  bool bVar8;
  uint uVar9;
  uint *puVar10;
  long *plVar11;
  undefined4 *puVar12;
  long *plVar13;
  long *plVar14;
  ulong uVar15;
  long lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  long lVar19;
  undefined8 uVar20;
  long lVar21;
  undefined8 uVar22;
  long lVar23;
  undefined8 uVar24;
  long lVar25;
  undefined8 uVar26;
  long lVar27;
  undefined8 uVar28;
  long lVar29;
  undefined1 auVar30 [16];
  
  lVar16 = param_1[1];
  piVar1 = (int *)((long)param_1 + 0x14);
  iVar5 = *piVar1;
  if (((int)lVar16 == iVar5) || (*param_1 == 0)) goto LAB_00004500;
  puVar3 = (undefined8 *)(*param_1 + (ulong)*(uint *)(param_1 + 2));
  if (*(int *)((long)puVar3 + 0x54) == 0) {
    _TPCircularBufferProduceAudioBufferList_cold_3();
LAB_000044f8:
    _TPCircularBufferProduceAudioBufferList_cold_2();
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      uVar18 = param_2[1];
      uVar17 = *param_2;
      uVar22 = param_2[3];
      uVar20 = param_2[2];
      uVar24 = param_2[4];
      uVar28 = param_2[7];
      uVar26 = param_2[6];
      puVar3[5] = param_2[5];
      puVar3[4] = uVar24;
      puVar3[7] = uVar28;
      puVar3[6] = uVar26;
      puVar3[1] = uVar18;
      *puVar3 = uVar17;
      puVar3[3] = uVar22;
      puVar3[2] = uVar20;
    }
    uVar4 = ((*(int *)(puVar3 + (ulong)(*(int *)(puVar3 + 9) - 1) * 2 + 0xb) +
             *(int *)((long)puVar3 + (ulong)(*(int *)(puVar3 + 9) - 1) * 0x10 + 0x54)) - (int)puVar3
            ) + 0xfU & 0xfffffff0;
    if (*(uint *)(puVar3 + 8) < uVar4 || (uint)((int)lVar16 - iVar5) < uVar4) goto LAB_000044f8;
    *(uint *)(puVar3 + 8) = uVar4;
    uVar2 = (int)param_1[2] + uVar4;
    uVar6 = *(uint *)(param_1 + 1);
    uVar9 = 0;
    if (uVar6 != 0) {
      uVar9 = uVar2 / uVar6;
    }
    *(uint *)(param_1 + 2) = uVar2 - uVar9 * uVar6;
    if ((*(byte *)(param_1 + 3) & 1) == 0) {
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar8) {
          *piVar1 = *piVar1 + uVar4;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
    }
    else {
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar8) {
          *piVar1 = *piVar1 + uVar4;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
    }
    if (*(uint *)((long)param_1 + 0x14) <= *(uint *)(param_1 + 1)) {
      return param_1;
    }
  }
  _TPCircularBufferProduceAudioBufferList_cold_1();
LAB_00004500:
  auVar30 = _TPCircularBufferProduceAudioBufferList_cold_4();
  puVar12 = auVar30._8_8_;
  if (param_4 != 0) {
    uVar4 = puVar12[3];
    if ((param_4 != -1) && (uVar4 = *(int *)(param_5 + 0x18) * param_4, (uint)puVar12[3] < uVar4)) {
      auVar30 = _TPCircularBufferCopyAudioBufferList_cold_1();
      plVar13 = auVar30._8_8_;
      plVar11 = auVar30._0_8_;
      if (*(uint *)((long)plVar11 + 0x14) == 0) {
        plVar14 = (long *)0x0;
      }
      else {
        plVar14 = (long *)(*plVar11 + (ulong)*(uint *)((long)plVar11 + 0xc));
      }
      if ((plVar14 < plVar13) &&
         (plVar14 = (long *)((long)plVar14 + (ulong)*(uint *)((long)plVar11 + 0x14)),
         plVar13 < plVar14)) {
        plVar13 = (long *)((long)plVar13 + (ulong)*(uint *)(plVar13 + -1));
        if (plVar13 + -9 < plVar14) {
          if (param_3 != (long *)0x0) {
            lVar19 = plVar13[-8];
            lVar16 = plVar13[-9];
            lVar23 = plVar13[-6];
            lVar21 = plVar13[-7];
            lVar25 = plVar13[-5];
            lVar29 = plVar13[-2];
            lVar27 = plVar13[-3];
            param_3[5] = plVar13[-4];
            param_3[4] = lVar25;
            param_3[7] = lVar29;
            param_3[6] = lVar27;
            param_3[1] = lVar19;
            *param_3 = lVar16;
            param_3[3] = lVar23;
            param_3[2] = lVar21;
          }
          return plVar13;
        }
        return (long *)0x0;
      }
                    /* WARNING: Subroutine does not return */
      _TPCircularBufferNextBufferListAfter_cold_1();
    }
    if (uVar4 != 0) {
      puVar10 = (uint *)_TPCircularBufferPrepareEmptyAudioBufferList
                                  (auVar30._0_8_,*puVar12,(ulong)uVar4,param_3);
      if (puVar10 == (uint *)0x0) {
        return (long *)0x0;
      }
      if (*puVar10 != 0) {
        uVar15 = 0;
        lVar16 = 0x10;
        do {
          _memcpy(*(void **)((long)puVar10 + lVar16),*(void **)((long)puVar12 + lVar16),(ulong)uVar4
                 );
          uVar15 = uVar15 + 1;
          lVar16 = lVar16 + 0x10;
        } while (uVar15 < *puVar10);
      }
      _TPCircularBufferProduceAudioBufferList(auVar30._0_8_,0);
    }
  }
  return (long *)((long)&MACH_HEADER.magic + 1);
}

// ==== 00004504 _TPCircularBufferCopyAudioBufferList ====
long _TPCircularBufferCopyAudioBufferList
               (undefined8 param_1,undefined4 *param_2,undefined8 *param_3,int param_4,long param_5)

{
  uint uVar1;
  uint *puVar2;
  long *plVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined1 auVar15 [16];
  
  if (param_4 != 0) {
    uVar1 = param_2[3];
    if ((param_4 != -1) && (uVar1 = *(int *)(param_5 + 0x18) * param_4, (uint)param_2[3] < uVar1)) {
      auVar15 = _TPCircularBufferCopyAudioBufferList_cold_1();
      puVar4 = auVar15._8_8_;
      plVar3 = auVar15._0_8_;
      if (*(uint *)((long)plVar3 + 0x14) == 0) {
        puVar5 = (undefined8 *)0x0;
      }
      else {
        puVar5 = (undefined8 *)(*plVar3 + (ulong)*(uint *)((long)plVar3 + 0xc));
      }
      if ((puVar5 < puVar4) &&
         (puVar5 = (undefined8 *)((long)puVar5 + (ulong)*(uint *)((long)plVar3 + 0x14)),
         puVar4 < puVar5)) {
        lVar7 = (long)puVar4 + (ulong)*(uint *)(puVar4 + -1);
        if ((undefined8 *)(lVar7 - 0x48U) < puVar5) {
          if (param_3 != (undefined8 *)0x0) {
            uVar9 = *(undefined8 *)(lVar7 + -0x40);
            uVar8 = *(undefined8 *)(lVar7 - 0x48U);
            uVar11 = *(undefined8 *)(lVar7 + -0x30);
            uVar10 = *(undefined8 *)(lVar7 + -0x38);
            uVar12 = *(undefined8 *)(lVar7 + -0x28);
            uVar14 = *(undefined8 *)(lVar7 + -0x10);
            uVar13 = *(undefined8 *)(lVar7 + -0x18);
            param_3[5] = *(undefined8 *)(lVar7 + -0x20);
            param_3[4] = uVar12;
            param_3[7] = uVar14;
            param_3[6] = uVar13;
            param_3[1] = uVar9;
            *param_3 = uVar8;
            param_3[3] = uVar11;
            param_3[2] = uVar10;
          }
          return lVar7;
        }
        return 0;
      }
                    /* WARNING: Subroutine does not return */
      _TPCircularBufferNextBufferListAfter_cold_1();
    }
    if (uVar1 != 0) {
      puVar2 = (uint *)_TPCircularBufferPrepareEmptyAudioBufferList
                                 (param_1,*param_2,(ulong)uVar1,param_3);
      if (puVar2 == (uint *)0x0) {
        return 0;
      }
      if (*puVar2 != 0) {
        uVar6 = 0;
        lVar7 = 0x10;
        do {
          _memcpy(*(void **)((long)puVar2 + lVar7),*(void **)((long)param_2 + lVar7),(ulong)uVar1);
          uVar6 = uVar6 + 1;
          lVar7 = lVar7 + 0x10;
        } while (uVar6 < *puVar2);
      }
      _TPCircularBufferProduceAudioBufferList(param_1,0);
    }
  }
  return 1;
}

// ==== 000045d0 _TPCircularBufferNextBufferListAfter ====
long _TPCircularBufferNextBufferListAfter(long *param_1,undefined8 *param_2,undefined8 *param_3)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  if (*(uint *)((long)param_1 + 0x14) == 0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    puVar2 = (undefined8 *)(*param_1 + (ulong)*(uint *)((long)param_1 + 0xc));
  }
  if ((puVar2 < param_2) &&
     (puVar2 = (undefined8 *)((long)puVar2 + (ulong)*(uint *)((long)param_1 + 0x14)),
     param_2 < puVar2)) {
    lVar1 = (long)param_2 + (ulong)*(uint *)(param_2 + -1);
    if ((undefined8 *)(lVar1 - 0x48U) < puVar2) {
      if (param_3 != (undefined8 *)0x0) {
        uVar4 = *(undefined8 *)(lVar1 + -0x40);
        uVar3 = *(undefined8 *)(lVar1 - 0x48U);
        uVar6 = *(undefined8 *)(lVar1 + -0x30);
        uVar5 = *(undefined8 *)(lVar1 + -0x38);
        uVar7 = *(undefined8 *)(lVar1 + -0x28);
        uVar9 = *(undefined8 *)(lVar1 + -0x10);
        uVar8 = *(undefined8 *)(lVar1 + -0x18);
        param_3[5] = *(undefined8 *)(lVar1 + -0x20);
        param_3[4] = uVar7;
        param_3[7] = uVar9;
        param_3[6] = uVar8;
        param_3[1] = uVar4;
        *param_3 = uVar3;
        param_3[3] = uVar6;
        param_3[2] = uVar5;
      }
      return lVar1;
    }
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  _TPCircularBufferNextBufferListAfter_cold_1();
}

// ==== 00004648 _TPCircularBufferConsumeNextBufferListPartial ====
void _TPCircularBufferConsumeNextBufferListPartial(long *param_1,uint param_2,double *param_3)

{
  int *piVar1;
  uint uVar2;
  double *pdVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  ulong uVar9;
  long lVar10;
  long *plVar11;
  void *pvVar12;
  double dVar13;
  double dVar14;
  mach_timebase_info local_58;
  
  piVar1 = (int *)((long)param_1 + 0x14);
  if ((*piVar1 != 0) && (lVar10 = *param_1, lVar10 != 0)) {
    pdVar3 = (double *)(lVar10 + (ulong)*(uint *)((long)param_1 + 0xc));
    uVar4 = *(int *)(param_3 + 3) * param_2;
    uVar8 = *(uint *)((long)pdVar3 + 0x54);
    uVar2 = uVar4;
    if (uVar8 <= uVar4) {
      uVar2 = uVar8;
    }
    if (uVar4 < uVar8) {
      uVar8 = *(uint *)(pdVar3 + 9);
      uVar9 = (ulong)uVar8;
      if (uVar8 != 0) {
        plVar11 = (long *)((ulong)*(uint *)((long)param_1 + 0xc) + lVar10 + 0x58);
        do {
          if (*(uint *)((long)plVar11 + -4) < uVar2) {
            _TPCircularBufferConsumeNextBufferListPartial_cold_2();
            goto LAB_00004868;
          }
          *plVar11 = *plVar11 + (ulong)uVar2;
          *(uint *)((long)plVar11 + -4) = *(uint *)((long)plVar11 + -4) - uVar2;
          plVar11 = plVar11 + 2;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
      }
      if ((*(uint *)(pdVar3 + 7) & 1) != 0) {
        *pdVar3 = *pdVar3 + (double)param_2;
      }
      if ((*(uint *)(pdVar3 + 7) >> 1 & 1) != 0) {
        if (___secondsToHostTicks == 0.0) {
          _mach_timebase_info(&local_58);
          dVar13 = (double)NEON_ucvtf((ulong)local_58.numer);
          dVar14 = (double)NEON_ucvtf((ulong)local_58.denom);
          ___secondsToHostTicks = 1.0 / ((dVar13 / dVar14) * 1e-09);
          uVar8 = *(uint *)(pdVar3 + 9);
        }
        dVar13 = (double)NEON_ucvtf(pdVar3[1]);
        pdVar3[1] = (double)(long)(dVar13 + ___secondsToHostTicks * ((double)param_2 / *param_3));
      }
      pvVar12 = (void *)((ulong)uVar2 + (long)pdVar3 & 0xfffffffffffffff0);
      _memmove(pvVar12,pdVar3,(ulong)(uVar8 - 1) * 0x10 + 0x60);
      iVar7 = (int)pvVar12 - (int)pdVar3;
      *(int *)((long)pvVar12 + 0x40) = *(int *)((long)pvVar12 + 0x40) - iVar7;
      uVar8 = *(uint *)(param_1 + 1);
      uVar2 = *(int *)((long)param_1 + 0xc) + iVar7;
      uVar4 = 0;
      if (uVar8 != 0) {
        uVar4 = uVar2 / uVar8;
      }
      *(uint *)((long)param_1 + 0xc) = uVar2 - uVar4 * uVar8;
      if ((*(byte *)(param_1 + 3) & 1) == 0) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 - iVar7;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
      else {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 - iVar7;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
      if (*piVar1 < 0) {
                    /* WARNING: Subroutine does not return */
        _TPCircularBufferConsumeNextBufferListPartial_cold_1();
      }
    }
    else if ((*piVar1 != 0) && (*param_1 != 0)) {
      uVar8 = *(uint *)(param_1 + 1);
      iVar7 = *(int *)(*param_1 + (ulong)*(uint *)((long)param_1 + 0xc) + 0x40);
      uVar2 = iVar7 + *(uint *)((long)param_1 + 0xc);
      uVar4 = 0;
      if (uVar8 != 0) {
        uVar4 = uVar2 / uVar8;
      }
      *(uint *)((long)param_1 + 0xc) = uVar2 - uVar4 * uVar8;
      if ((*(byte *)(param_1 + 3) & 1) == 0) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 - iVar7;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
      else {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 - iVar7;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
      if (*piVar1 < 0) {
LAB_00004868:
                    /* WARNING: Subroutine does not return */
        _TPCircularBufferConsumeNextBufferListPartial_cold_1();
      }
    }
  }
  return;
}

// ==== 0000486c _TPCircularBufferDequeueBufferListFrames ====
void _TPCircularBufferDequeueBufferListFrames
               (long *param_1,int *param_2,uint *param_3,undefined8 *param_4,long param_5)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  long lVar4;
  undefined8 *puVar5;
  uint uVar6;
  uint uVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  
  uVar6 = *(int *)(param_5 + 0x18) * *param_2;
  if (uVar6 != 0) {
    uVar7 = 0;
    do {
      if ((*(int *)((long)param_1 + 0x14) == 0) || (lVar4 = *param_1, lVar4 == 0)) {
        if (param_4 != (undefined8 *)0x0) {
          param_4[5] = 0;
          param_4[4] = 0;
          param_4[7] = 0;
          param_4[6] = 0;
          param_4[1] = 0;
          *param_4 = 0;
          param_4[3] = 0;
          param_4[2] = 0;
        }
        break;
      }
      uVar2 = *(uint *)((long)param_1 + 0xc);
      puVar5 = (undefined8 *)(lVar4 + (ulong)uVar2);
      if (param_4 != (undefined8 *)0x0) {
        uVar10 = puVar5[1];
        uVar9 = *puVar5;
        uVar12 = puVar5[3];
        uVar11 = puVar5[2];
        uVar13 = puVar5[4];
        uVar15 = puVar5[7];
        uVar14 = puVar5[6];
        param_4[5] = puVar5[5];
        param_4[4] = uVar13;
        param_4[7] = uVar15;
        param_4[6] = uVar14;
        param_4[1] = uVar10;
        *param_4 = uVar9;
        param_4[3] = uVar12;
        param_4[2] = uVar11;
      }
      uVar1 = uVar6;
      if (*(uint *)((long)puVar5 + 0x54) <= uVar6) {
        uVar1 = *(uint *)((long)puVar5 + 0x54);
      }
      if ((param_3 != (uint *)0x0) && (*param_3 != 0)) {
        uVar8 = 0;
        puVar5 = (undefined8 *)(lVar4 + (ulong)uVar2 + 0x58);
        puVar3 = param_3;
        do {
          if (puVar3[3] < uVar1 + uVar7) {
                    /* WARNING: Subroutine does not return */
            _TPCircularBufferDequeueBufferListFrames_cold_1();
          }
          _memcpy((void *)(*(long *)(puVar3 + 4) + (ulong)uVar7),(void *)*puVar5,(ulong)uVar1);
          uVar8 = uVar8 + 1;
          puVar5 = puVar5 + 2;
          puVar3 = puVar3 + 4;
        } while (uVar8 < *param_3);
      }
      uVar2 = 0;
      if (*(uint *)(param_5 + 0x18) != 0) {
        uVar2 = uVar1 / *(uint *)(param_5 + 0x18);
      }
      _TPCircularBufferConsumeNextBufferListPartial(param_1,uVar2);
      param_4 = (undefined8 *)0x0;
      uVar7 = uVar1 + uVar7;
      uVar6 = uVar6 - uVar1;
    } while (uVar6 != 0);
  }
  uVar7 = 0;
  if (*(uint *)(param_5 + 0x18) != 0) {
    uVar7 = uVar6 / *(uint *)(param_5 + 0x18);
  }
  *param_2 = *param_2 - uVar7;
  return;
}

// ==== 000049bc _TPCircularBufferPeekContiguousWrapped ====
uint _TPCircularBufferPeekContiguousWrapped
               (long *param_1,double *param_2,long param_3,uint param_4,uint param_5)

{
  double *pdVar1;
  uint uVar2;
  uint uVar3;
  double *pdVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  uint uVar8;
  double *pdVar9;
  uint uVar10;
  double *pdVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  
  uVar2 = *(uint *)((long)param_1 + 0x14);
  if ((uVar2 == 0) || (*param_1 == 0)) {
    return 0;
  }
  pdVar1 = (double *)(*param_1 + (ulong)*(uint *)((long)param_1 + 0xc));
  if (param_2 != (double *)0x0) {
    dVar18 = pdVar1[1];
    dVar16 = *pdVar1;
    dVar12 = pdVar1[3];
    dVar17 = pdVar1[2];
    dVar13 = pdVar1[4];
    dVar15 = pdVar1[7];
    dVar14 = pdVar1[6];
    param_2[5] = pdVar1[5];
    param_2[4] = dVar13;
    param_2[7] = dVar15;
    param_2[6] = dVar14;
    param_2[1] = dVar18;
    *param_2 = dVar16;
    param_2[3] = dVar12;
    param_2[2] = dVar17;
  }
  uVar10 = *(uint *)((long)pdVar1 + 0x54);
  if (*(uint *)(pdVar1 + 8) < uVar2) {
    dVar16 = (double)param_5;
    dVar18 = (double)param_4;
    pdVar4 = (double *)((long)pdVar1 + (ulong)*(uint *)(pdVar1 + 8));
    pdVar11 = pdVar1;
    uVar8 = uVar10;
    do {
      pdVar9 = pdVar4;
      if (param_4 != 0xffffffff) {
        uVar3 = 0;
        if (*(uint *)(param_3 + 0x18) != 0) {
          uVar3 = uVar8 / *(uint *)(param_3 + 0x18);
        }
        dVar17 = *pdVar11 + (double)uVar3;
        if (param_5 == 0) {
          if (dVar18 < ABS(*pdVar9 - dVar17)) break;
        }
        else {
          dVar12 = (double)_fmod(dVar17,dVar16);
          if (dVar17 <= dVar16) {
            dVar12 = dVar17;
          }
          dVar17 = ABS(ABS(*pdVar9 - dVar12) - dVar16);
          bVar5 = false;
          bVar6 = true;
          bVar7 = false;
          if (dVar18 < ABS(*pdVar9 - dVar12)) {
            bVar5 = false;
            bVar6 = false;
            bVar7 = true;
            if (!NAN(dVar17) && !NAN(dVar18)) {
              bVar5 = dVar17 < dVar18;
              bVar6 = dVar17 == dVar18;
              bVar7 = false;
            }
          }
          if (!bVar6 && bVar5 == bVar7) break;
        }
      }
      uVar8 = *(uint *)((long)pdVar9 + 0x54);
      uVar10 = uVar8 + uVar10;
      pdVar4 = (double *)((long)pdVar9 + (ulong)*(uint *)(pdVar9 + 8));
      pdVar11 = pdVar9;
    } while ((double *)((long)pdVar9 + (ulong)*(uint *)(pdVar9 + 8)) <
             (double *)((long)pdVar1 + (ulong)uVar2));
  }
  uVar2 = 0;
  if (*(uint *)(param_3 + 0x18) != 0) {
    uVar2 = uVar10 / *(uint *)(param_3 + 0x18);
  }
  return uVar2;
}

// ==== 00004ae4 _TPCircularBufferPeek ====
void _TPCircularBufferPeek(void)

{
  _TPCircularBufferPeekContiguousWrapped();
  return;
}

// ==== 00004af0 _TPCircularBufferPeekContiguous ====
void _TPCircularBufferPeekContiguous(void)

{
  _TPCircularBufferPeekContiguousWrapped();
  return;
}

// ==== 00004af8 _TPCircularBufferGetAvailableSpace ====
uint _TPCircularBufferGetAvailableSpace(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar3 = (int)param_1[1] - *(int *)((long)param_1 + 0x14);
  if ((uVar3 != 0) && (*param_1 != 0)) {
    lVar2 = *param_1 + (ulong)*(uint *)(param_1 + 2);
    if ((*(byte *)(param_2 + 0xc) >> 5 & 1) == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = *(uint *)(param_2 + 0x1c);
    }
    uVar1 = lVar2 + (ulong)uVar3;
    uVar5 = lVar2 + (ulong)(uVar4 - 1) * 0x180 + 0x297 & 0xfffffffffffffff0;
    if (uVar5 < uVar1) {
      uVar3 = 0;
      if (uVar4 != 0) {
        uVar3 = (uint)((int)uVar1 - (int)uVar5) / uVar4;
      }
      if ((uVar3 / 0xf) * 0xf != 0) {
        uVar4 = 0;
        if (*(uint *)(param_2 + 0x18) != 0) {
          uVar4 = ((uVar3 / 0xf) * 0xf) / *(uint *)(param_2 + 0x18);
        }
        return uVar4;
      }
    }
  }
  return 0;
}

// ==== 00004b90 __TPCircularBufferInit.cold.1 ====
void __TPCircularBufferInit_cold_1(void)

{
  _fwrite("TPCircularBuffer: Header version mismatch. Check for old versions of TPCircularBuffer in your project\n"
          ,0x66,1,*(FILE **)PTR____stderrp_00008000);
                    /* WARNING: Subroutine does not return */
  _abort();
}

// ==== 00004bbc __TPCircularBufferInit.cold.2 ====
void __TPCircularBufferInit_cold_2(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("_TPCircularBufferInit","TPCircularBuffer.c",0x2e,"length > 0");
}

// ==== 00004be4 _TPCircularBufferConsumeNextBufferListPartial.cold.1 ====
void _TPCircularBufferConsumeNextBufferListPartial_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferConsume","TPCircularBuffer.h",0xa1,"buffer->fillCount >= 0");
}

// ==== 00004c0c _TPCircularBufferProduceAudioBufferList.cold.1 ====
void _TPCircularBufferProduceAudioBufferList_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferProduce","TPCircularBuffer.h",0xc5,
                "buffer->fillCount <= buffer->length");
}

// ==== 00004c34 _TPCircularBufferProduceAudioBufferList.cold.2 ====
void _TPCircularBufferProduceAudioBufferList_cold_2(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferProduceAudioBufferList","TPCircularBuffer+AudioBufferList.c",0x75,
                "calculatedLength <= block->totalLength && calculatedLength <= availableBytes");
}

// ==== 00004c5c _TPCircularBufferProduceAudioBufferList.cold.3 ====
void _TPCircularBufferProduceAudioBufferList_cold_3(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferProduceAudioBufferList","TPCircularBuffer+AudioBufferList.c",0x6a,
                "block->bufferList.mBuffers[0].mDataByteSize > 0");
}

// ==== 00004c84 _TPCircularBufferProduceAudioBufferList.cold.4 ====
void _TPCircularBufferProduceAudioBufferList_cold_4(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferProduceAudioBufferList","TPCircularBuffer+AudioBufferList.c",100,
                "block");
}

// ==== 00004cac _TPCircularBufferCopyAudioBufferList.cold.1 ====
void _TPCircularBufferCopyAudioBufferList_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferCopyAudioBufferList","TPCircularBuffer+AudioBufferList.c",0x82,
                "byteCount <= inBufferList->mBuffers[0].mDataByteSize");
}

// ==== 00004cd4 _TPCircularBufferNextBufferListAfter.cold.1 ====
void _TPCircularBufferNextBufferListAfter_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferNextBufferListAfter","TPCircularBuffer+AudioBufferList.c",0x97,
                "(void*)bufferList > (void*)tail && (void*)bufferList < end");
}

// ==== 00004cfc _TPCircularBufferConsumeNextBufferListPartial.cold.2 ====
void _TPCircularBufferConsumeNextBufferListPartial_cold_2(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferConsumeNextBufferListPartial","TPCircularBuffer+AudioBufferList.c",
                0xbf,"bytesToConsume <= block->bufferList.mBuffers[i].mDataByteSize");
}

// ==== 00004d24 _TPCircularBufferDequeueBufferListFrames.cold.1 ====
void _TPCircularBufferDequeueBufferListFrames_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferDequeueBufferListFrames","TPCircularBuffer+AudioBufferList.c",0xe7,
                "bytesCopied + bytesToCopy <= outputBufferList->mBuffers[i].mDataByteSize");
}

// ==== 00004d4c ___assert_rtn ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ___assert_rtn(char *param_1,char *param_2,int param_3,char *param_4)

{
                    /* WARNING: Could not recover jumptable at 0x00004d54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____assert_rtn_000080c0)(param_1,param_2,param_3);
  return;
}

// ==== 00004d58 _abort ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _abort(void)

{
                    /* WARNING: Could not recover jumptable at 0x00004d60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__abort_000080c8)();
  return;
}

// ==== 00004d64 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00004d6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_000080d0)();
  return;
}

// ==== 00004d70 _fmod ====
void _fmod(void)

{
                    /* WARNING: Could not recover jumptable at 0x00004d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__fmod_000080d8)();
  return;
}

// ==== 00004d7c _fwrite ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t _fwrite(void *param_1,size_t param_2,size_t param_3,FILE *param_4)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004d84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = (*(code *)PTR__fwrite_000080e0)();
  return sVar1;
}

// ==== 00004d88 _mach_error_string ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * _mach_error_string(mach_error_t error_value)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004d90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = (char *)(*(code *)PTR__mach_error_string_000080e8)(error_value);
  return pcVar1;
}

// ==== 00004d94 _mach_timebase_info ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

kern_return_t _mach_timebase_info(mach_timebase_info_t info)

{
  kern_return_t kVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004d9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  kVar1 = (*(code *)PTR__mach_timebase_info_000080f0)((int)info);
  return kVar1;
}

// ==== 00004da0 _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004da8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_000080f8)();
  return pvVar1;
}

// ==== 00004dac _memmove ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memmove(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004db4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memmove_00008100)();
  return pvVar1;
}

// ==== 00004db8 _printf ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004dc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_00008108)((int)param_1);
  return iVar1;
}

// ==== 00004dc4 _puts ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _puts(char *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004dcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__puts_00008110)((int)param_1);
  return iVar1;
}

// ==== 00004dd0 _vm_allocate ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

kern_return_t _vm_allocate(vm_map_t target_task,vm_address_t *address,vm_size_t size,int flags)

{
  kern_return_t kVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004dd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  kVar1 = (*(code *)PTR__vm_allocate_00008118)(target_task,address,size,flags);
  return kVar1;
}

// ==== 00004ddc _vm_deallocate ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

kern_return_t _vm_deallocate(vm_map_t target_task,vm_address_t address,vm_size_t size)

{
  kern_return_t kVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004de4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  kVar1 = (*(code *)PTR__vm_deallocate_00008120)(target_task);
  return kVar1;
}

// ==== 00004de8 _vm_remap ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

kern_return_t
_vm_remap(vm_map_t target_task,vm_address_t *target_address,vm_size_t size,vm_address_t mask,
         int flags,vm_map_t src_task,vm_address_t src_address,boolean_t copy,
         vm_prot_t *cur_protection,vm_prot_t *max_protection,vm_inherit_t inheritance)

{
  kern_return_t kVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00004df0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  kVar1 = (*(code *)PTR__vm_remap_00008128)(target_task);
  return kVar1;
}

