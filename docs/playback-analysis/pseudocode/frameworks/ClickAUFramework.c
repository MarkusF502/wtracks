// ClickAUFramework sha256 8e65001660756c8a0b4725306eeae50288ef060488d68d1ba3086c32fd794fe0 (Ghidra 12.1.4, all decompiled functions)

// ==== 00004000 __ZN9DSPKernel14handleOneEventEPK13AURenderEvent ====
void __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(long *param_1,long param_2)

{
  if (*(byte *)(param_2 + 0x10) - 1 < 2) {
                    /* WARNING: Could not recover jumptable at 0x00004028. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))
              (*(undefined4 *)(param_2 + 0x20),param_1,*(undefined8 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x14));
    return;
  }
  if (*(byte *)(param_2 + 0x10) == 8) {
                    /* WARNING: Could not recover jumptable at 0x0000403c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x10))();
    return;
  }
  return;
}

// ==== 00004044 __ZN9DSPKernel28performAllSimultaneousEventsExRPK13AURenderEvent ====
void __ZN9DSPKernel28performAllSimultaneousEventsExRPK13AURenderEvent
               (undefined8 param_1,long param_2,long *param_3)

{
  long lVar1;
  
  lVar1 = *param_3;
  do {
    __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(param_1,lVar1);
    lVar1 = *(long *)*param_3;
    *param_3 = lVar1;
    if (lVar1 == 0) {
      return;
    }
  } while (*(long *)(lVar1 + 8) <= param_2);
  return;
}

// ==== 00004098 __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent ====
void __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
               (undefined8 *param_1,double *param_2,ulong param_3,long *param_4)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  
  iVar1 = (int)param_3;
  if (iVar1 != 0) {
    lVar4 = (long)*param_2;
    do {
      iVar2 = (int)param_3;
      if (param_4 == (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00004170. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)*param_1)(param_1,param_3,iVar1 - iVar2,param_2);
        return;
      }
      uVar3 = param_4[1] - lVar4 & (param_4[1] - lVar4 >> 0x3f ^ 0xffffffffffffffffU);
      if ((int)uVar3 != 0) {
        (**(code **)*param_1)(param_1,uVar3,iVar1 - iVar2,param_2);
        param_3 = (ulong)(uint)(iVar2 - (int)uVar3);
        lVar4 = lVar4 + (uVar3 & 0xffffffff);
      }
      do {
        __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(param_1,param_4);
        param_4 = (long *)*param_4;
        if (param_4 == (long *)0x0) break;
      } while (param_4[1] <= lVar4);
    } while ((int)param_3 != 0);
  }
  return;
}

// ==== 00004174 ClickAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID ClickAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  ID IVar3;
  ID self_00;
  ID self_01;
  ID self_02;
  ID self_03;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined *local_140;
  undefined8 local_138;
  code *local_130;
  undefined *puStack_128;
  undefined8 *local_120;
  undefined *local_118;
  undefined8 local_110;
  code *local_108;
  undefined *puStack_100;
  undefined8 *local_f8;
  undefined8 local_f0;
  undefined8 *puStack_e8;
  undefined8 local_e0;
  undefined8 *local_d8;
  ID local_c8;
  class_t *pcStack_c0;
  ID local_b8;
  ID IStack_b0;
  ID local_a8;
  ID IStack_a0;
  ID local_98;
  ID IStack_90;
  undefined8 local_88;
  long local_80;
  
  local_80 = *(long *)PTR____stack_chk_guard_0000c020;
  puStack_e8 = *(undefined8 **)&param_3->field2_0x8;
  local_f0._0_4_ = param_3->field0_0x0;
  local_f0._4_4_ = param_3->field1_0x4;
  local_e0 = CONCAT44(local_e0._4_4_,param_3->field4_0x10);
  pcStack_c0 = &objc::class_t::ClickAudioUnit;
  local_c8 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_c8,"initWithComponentDescription:options:error:",&local_f0,
                    (ulong)param_4);
  if (self != 0) {
    *(undefined8 *)(self + (long)_clickTimesCArray) = 0;
    IVar2 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar2 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar2,0x40e5888000000000,2);
    TrackedAUAudioUnit::setDefaultFormat_(self,IVar2);
    lVar5 = (long)_bufferedOutputBus;
    IVar2 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar5,IVar2,2);
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar3 = TrackedAUAudioUnit::defaultFormat(self);
    IVar2 = AUAudioUnitBus::initWithFormat_error_(IVar2,IVar3,0);
    lVar5 = (long)_auOutputBus;
    *(ID *)(self + lVar5) = IVar2;
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_88 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_88,1);
    IVar2 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar3);
    uVar4 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,uVar4,0,0x3f800000,&cf_isPlayingParameter,
                       &cf_isPlaying,0,0x1a,0,0,0,0);
    IVar3 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isMutedParameter,
                       &cf_isMuted,1,0x1a,0,0,0,0);
    self_00 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x4f0000004f000000,
                         &cf_loopStartParameter,&cf_loopStart,2,4,0,0,0,0);
    self_01 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x4f0000004f000000,
                         &cf_loopEndParameter,&cf_loopEnd,3,4,0,0,0,0);
    self_02 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x4f0000004f000000,
                         &cf_enqueuedLoopStartParameter,&cf_enqueuedLoopStart,4,4,0,0,0,0);
    self_03 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x4f0000004f000000,
                         &cf_enqueuedLoopEndParameter,&cf_enqueuedLoopEnd,5,4,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0x3f800000);
    AUParameterTree::setValue_(self_00,0x40000000);
    AUParameterTree::setValue_(self_01,0x40400000);
    AUParameterTree::setValue_(self_02,0x40800000);
    AUParameterTree::setValue_(self_03,0x40a00000);
    local_b8 = IVar2;
    IStack_b0 = IVar3;
    local_a8 = self_00;
    IStack_a0 = self_01;
    local_98 = self_02;
    IStack_90 = self_03;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_b8,6);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    lVar5 = (long)_dspKernel;
    local_d8 = *(undefined8 **)(self + lVar5);
    if (local_d8 == (undefined8 *)0x0) {
      local_d8 = (undefined8 *)__Znwm(0x158);
      *local_d8 = &DAT_0000c130;
      local_d8[1] = 0x472c440000000000;
      local_d8[3] = 0;
      local_d8[9] = 0;
      local_d8[0x10] = 0;
      local_d8[0x11] = 0;
      local_d8[0xf] = 0;
      *(undefined2 *)(local_d8 + 0x12) = 0;
      *(undefined8 *)((long)local_d8 + 0x9c) = 0x7fffffff00000000;
      *(undefined8 *)((long)local_d8 + 0x94) = 0;
      *(undefined8 *)((long)local_d8 + 0xa4) = 0xffffffffffffffff;
      local_d8[0x16] = 0x3ff0000000000000;
      *(undefined4 *)(local_d8 + 0x17) = 0;
      local_d8[0x18] = 0;
      local_d8[0x19] = 0;
      uVar4 = NEON_fmov(0x3f800000,4);
      local_d8[0x1a] = uVar4;
      local_d8[0x26] = 0;
      local_d8[0x2a] = 0;
      *(undefined8 **)(self + lVar5) = local_d8;
    }
    puVar1 = PTR___NSConcreteStackBlock_0000c018;
    local_f0 = 0;
    local_e0 = 0x2020000000;
    local_118 = PTR___NSConcreteStackBlock_0000c018;
    local_110 = 0xc2000000;
    local_108 = ___61__ClickAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_100 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_f8 = &local_f0;
    puStack_e8 = &local_f0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_118);
    local_140 = puVar1;
    local_138 = 0xc2000000;
    local_130 = ___61__ClickAudioUnit_initWithComponentDescription_options_error___block_invoke_28;
    puStack_128 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_120 = &local_f0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_140);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar6),&___block_literal_global);
    __Block_object_dispose(&local_f0,8);
  }
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_80) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 000047ec __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZN16BufferedAudioBus4initEP13AVAudioFormatj(ID *param_1,undefined8 param_2,undefined8 param_3)

{
  ID IVar1;
  ID IVar2;
  
  *(undefined4 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  IVar1 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
  IVar1 = AUAudioUnitBus::initWithFormat_error_(IVar1,param_2,0);
  IVar2 = *param_1;
  *param_1 = IVar1;
  objc_stub::setMaximumChannelCount_(*param_1,IVar2,param_3);
  return 0;
}

// ==== 00004880 ___61-[ClickAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___61__ClickAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN14ClickDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return;
}

// ==== 000048c4 __ZN14ClickDSPKernel12setParameterEyf ====
void __ZN14ClickDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  if (2 < param_3) {
    if (param_3 == 3) {
      *(int *)(param_2 + 0xa0) = (int)(*(double *)(param_2 + 0x50) * (double)param_1);
      return;
    }
    if (param_3 == 4) {
      *(int *)(param_2 + 0xa4) = (int)(*(double *)(param_2 + 0x50) * (double)param_1);
    }
    else if (param_3 == 5) {
      *(int *)(param_2 + 0xa8) = (int)(*(double *)(param_2 + 0x50) * (double)param_1);
      return;
    }
    return;
  }
  if (param_3 == 0) {
    param_2 = param_2 + 0x90;
  }
  else {
    if (param_3 != 1) {
      if (param_3 != 2) {
        return;
      }
      *(int *)(param_2 + 0x9c) = (int)(*(double *)(param_2 + 0x50) * (double)param_1);
      return;
    }
    param_2 = param_2 + 0x91;
  }
  *(bool *)param_2 = param_1 != 0.0;
  return;
}

// ==== 0000497c ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 0000498c ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004998 ___61-[ClickAudioUnit_initWithComponentDescription:options:error:]_block_invoke.28 ====
undefined1  [16]
___61__ClickAudioUnit_initWithComponentDescription_options_error___block_invoke_28
          (undefined8 param_1,ID param_2)

{
  objc_stub::address(param_2);
  return ZEXT816(0);
}

// ==== 000049b4 ___61-[ClickAudioUnit_initWithComponentDescription:options:error:]_block_invoke.30 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

cfstringStruct *
___61__ClickAudioUnit_initWithComponentDescription_options_error___block_invoke_30
          (undefined8 param_1,ID param_2,long param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  
  if (param_3 == 0) {
    objc_stub::value(param_2);
  }
  IVar1 = objc_stub::address(param_2);
  if ((long)IVar1 < 3) {
    if (((IVar1 != 0) && (IVar1 != 1)) && (IVar1 != 2)) {
      return &cf__;
    }
  }
  else if (((IVar1 != 3) && (IVar1 != 4)) && (IVar1 != 5)) {
    return &cf__;
  }
  pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__d);
  return pcVar2;
}

// ==== 00004aa0 ClickAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void ClickAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::ClickAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  *(undefined1 *)(*(long *)(param_1 + (long)_dspKernel) + 0x90) = 0;
  return;
}

// ==== 00004af4 ClickAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void ClickAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long *plVar1;
  SEL extraout_x1;
  long lVar2;
  long lVar3;
  undefined8 *puVar4;
  ID local_40;
  class_t *pcStack_38;
  
  lVar3 = (long)_clickTimesCArray;
  if (*(long *)(param_1 + lVar3) != 0) {
    __ZdaPv();
    *(undefined8 *)(param_1 + lVar3) = 0;
    param_2 = extraout_x1;
  }
  lVar3 = (long)_dspKernel;
  __ZN14ClickDSPKernel7cleanupEv(*(undefined8 *)(param_1 + lVar3),param_2);
  puVar4 = *(undefined8 **)(param_1 + lVar3);
  if (puVar4 == (undefined8 *)0x0) goto LAB_00004bac;
  *puVar4 = &DAT_0000c130;
  plVar1 = (long *)puVar4[0x2a];
  if (plVar1 == puVar4 + 0x27) {
    lVar2 = 0x20;
LAB_00004b6c:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004b6c;
  }
  plVar1 = (long *)puVar4[0x26];
  if (plVar1 == puVar4 + 0x23) {
    lVar2 = 0x20;
LAB_00004b98:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004b98;
  }
  __ZdlPv(puVar4);
LAB_00004bac:
  *(undefined8 *)(param_1 + lVar3) = 0;
  pcStack_38 = &objc::class_t::ClickAudioUnit;
  local_40 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_40,"dealloc");
  return;
}

// ==== 00004c0c __ZN14ClickDSPKernel7cleanupEv ====
void __ZN14ClickDSPKernel7cleanupEv(long param_1)

{
  if (*(long *)(param_1 + 0x80) != 0) {
    __ZdaPv();
    *(undefined4 *)(param_1 + 0x88) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    _ExtAudioFileDispose();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== 00004c4c ___clang_call_terminate ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void ___clang_call_terminate
               (undefined8 param_1,undefined8 param_2,ID param_3,ID param_4,ID param_5,int param_6)

{
  ID IVar1;
  SEL extraout_x1;
  SEL extraout_x1_00;
  long lVar2;
  long lVar3;
  undefined1 auVar4 [16];
  undefined1 auStack_c0 [8];
  undefined1 auStack_b8 [8];
  undefined1 auStack_b0 [8];
  undefined *puStack_a8;
  undefined1 auStack_a0 [16];
  undefined **ppuStack_90;
  undefined *puStack_88;
  undefined1 auStack_80 [16];
  undefined **ppuStack_70;
  long lStack_68;
  
  ___cxa_begin_catch();
  auVar4 = __ZSt9terminatev();
  IVar1 = auVar4._0_8_;
  lStack_68 = *(long *)PTR____stack_chk_guard_0000c020;
  ClickAudioUnit::setUrl_(IVar1,auVar4._8_8_,param_3);
  ClickAudioUnit::setClickTimes_(IVar1,extraout_x1,param_4);
  ClickAudioUnit::setDelegate_(IVar1,extraout_x1_00,param_5);
  _objc_initWeak(auStack_b0,IVar1);
  lVar2 = (long)ClickAudioUnit::_dspKernel;
  lVar3 = *(long *)(IVar1 + lVar2);
  _objc_copyWeak(auStack_b8,auStack_b0);
  ppuStack_70 = (undefined **)0x0;
  puStack_88 = &DAT_0000c200;
  _objc_moveWeak(auStack_80,auStack_b8);
  ppuStack_70 = &puStack_88;
  _objc_destroyWeak(auStack_b8);
  __ZNSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEaSERKS6_(lVar3 + 0x118,&puStack_88);
  if (ppuStack_70 == &puStack_88) {
    lVar3 = 0x20;
LAB_00004d5c:
    (**(code **)(*ppuStack_70 + lVar3))();
  }
  else if (ppuStack_70 != (undefined **)0x0) {
    lVar3 = 0x28;
    goto LAB_00004d5c;
  }
  if (param_6 != 0) {
    lVar2 = *(long *)(IVar1 + lVar2);
    _objc_copyWeak(auStack_c0,auStack_b0);
    ppuStack_90 = (undefined **)0x0;
    puStack_a8 = &DAT_0000c290;
    _objc_moveWeak(auStack_a0,auStack_c0);
    ppuStack_90 = &puStack_a8;
    _objc_destroyWeak(auStack_c0);
    __ZNSt3__18functionIFvvEEaSERKS2_(lVar2 + 0x138,&puStack_a8);
    if (ppuStack_90 == &puStack_a8) {
      lVar2 = 0x20;
    }
    else {
      if (ppuStack_90 == (undefined **)0x0) goto LAB_00004de0;
      lVar2 = 0x28;
    }
    (**(code **)(*ppuStack_90 + lVar2))();
  }
LAB_00004de0:
  _objc_destroyWeak(auStack_b0);
  if (*(long *)PTR____stack_chk_guard_0000c020 == lStack_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004c5c ClickAudioUnit::configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x2c bytes */

void ClickAudioUnit::configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick_
               (ID param_1,SEL param_2,ID param_3,ID param_4,ID param_5,bool param_6)

{
  long lVar1;
  long lVar2;
  undefined1 auStack_b0 [8];
  undefined1 auStack_a8 [8];
  undefined1 auStack_a0 [8];
  undefined *local_98;
  undefined1 auStack_90 [16];
  undefined **local_80;
  undefined *local_78;
  undefined1 auStack_70 [16];
  undefined **local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_0000c020;
  setUrl_(param_1,param_3);
  setClickTimes_(param_1,param_4);
  setDelegate_(param_1,param_5);
  _objc_initWeak(auStack_a0,param_1);
  lVar1 = (long)_dspKernel;
  lVar2 = *(long *)(param_1 + lVar1);
  _objc_copyWeak(auStack_a8,auStack_a0);
  local_60 = (undefined **)0x0;
  local_78 = &DAT_0000c200;
  _objc_moveWeak(auStack_70,auStack_a8);
  local_60 = &local_78;
  _objc_destroyWeak(auStack_a8);
  __ZNSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEaSERKS6_(lVar2 + 0x118,&local_78);
  if (local_60 == &local_78) {
    lVar2 = 0x20;
LAB_00004d5c:
    (**(code **)(*local_60 + lVar2))();
  }
  else if (local_60 != (undefined **)0x0) {
    lVar2 = 0x28;
    goto LAB_00004d5c;
  }
  if (param_6 != 0) {
    lVar1 = *(long *)(param_1 + lVar1);
    _objc_copyWeak(auStack_b0,auStack_a0);
    local_80 = (undefined **)0x0;
    local_98 = &DAT_0000c290;
    _objc_moveWeak(auStack_90,auStack_b0);
    local_80 = &local_98;
    _objc_destroyWeak(auStack_b0);
    __ZNSt3__18functionIFvvEEaSERKS2_(lVar1 + 0x138,&local_98);
    if (local_80 == &local_98) {
      lVar1 = 0x20;
    }
    else {
      if (local_80 == (undefined **)0x0) goto LAB_00004de0;
      lVar1 = 0x28;
    }
    (**(code **)(*local_80 + lVar1))();
  }
LAB_00004de0:
  _objc_destroyWeak(auStack_a0);
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004eac ClickAudioUnit::prepareToPlayFromPlayheadPosition: ====
/* Function Stack Size: 0x14 bytes */

void ClickAudioUnit::prepareToPlayFromPlayheadPosition_(ID param_1,SEL param_2,int param_3)

{
  long lVar1;
  
  if (-1 < (int)param_3) {
    lVar1 = *(long *)(param_1 + (long)_dspKernel);
    *(int *)(lVar1 + 0x8c) = *(int *)(lVar1 + 0x88) + -1;
    *(int *)(lVar1 + 0xb8) = param_3;
    *(undefined4 *)(lVar1 + 0xcc) = 0;
    __ZN14ClickDSPKernel24resetClickTimesNextIndexEv();
    return;
  }
  return;
}

// ==== 00004ee4 ClickAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x14 bytes */

void ClickAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,float param_3)

{
  long lVar1;
  int iVar2;
  
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  iVar2 = (int)(*(float *)(lVar1 + 0xc) * param_3);
  if (-1 < iVar2) {
    *(int *)(lVar1 + 0x8c) = *(int *)(lVar1 + 0x88) + -1;
    *(int *)(lVar1 + 0xb8) = iVar2;
    *(undefined4 *)(lVar1 + 0xcc) = 0;
    __ZN14ClickDSPKernel24resetClickTimesNextIndexEv();
    return;
  }
  return;
}

// ==== 00004f28 ClickAudioUnit::setChannelsGain: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setChannelsGain_(ID param_1,SEL param_2,ID param_3)

{
  ID IVar1;
  long lVar2;
  undefined4 extraout_s0;
  undefined4 extraout_s0_00;
  
  IVar1 = objc_stub::objectAtIndexedSubscript_(param_3,0);
  objc_stub::floatValue(IVar1);
  IVar1 = objc_stub::objectAtIndexedSubscript_(param_3,1);
  objc_stub::floatValue(IVar1);
  lVar2 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined4 *)(lVar2 + 0xd0) = extraout_s0;
  *(undefined4 *)(lVar2 + 0xd4) = extraout_s0_00;
  return;
}

// ==== 00004fe8 ClickAudioUnit::updateClickTimesWithClickTimes: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::updateClickTimesWithClickTimes_(ID param_1,SEL param_2,ID param_3)

{
  ID IVar1;
  void *pvVar2;
  ID IVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  ID IVar8;
  undefined1 extraout_b0;
  undefined1 extraout_var;
  undefined1 extraout_var_00;
  undefined1 extraout_var_01;
  undefined1 extraout_var_02;
  undefined1 extraout_var_03;
  undefined1 extraout_var_04;
  undefined1 extraout_var_05;
  undefined8 local_130;
  long lStack_128;
  long *local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined1 auStack_e8 [128];
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_0000c020;
  setClickTimes_(param_1,param_3);
  lVar4 = (long)_clickTimesCArray;
  if (*(long *)(param_1 + lVar4) != 0) {
    __ZdaPv();
    *(undefined8 *)(param_1 + lVar4) = 0;
  }
  IVar1 = clickTimes(param_1);
  IVar1 = objc_stub::count(IVar1);
  pvVar2 = _malloc(IVar1 << 3);
  *(void **)(param_1 + lVar4) = pvVar2;
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  lStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  local_120 = (long *)0x0;
  IVar1 = clickTimes(param_1);
  IVar3 = objc_stub::countByEnumeratingWithState_objects_count_(IVar1,&local_130,auStack_e8,0x10);
  if (IVar3 != 0) {
    lVar6 = 0;
    lVar7 = *local_120;
    do {
      IVar8 = 0;
      do {
        if (*local_120 != lVar7) {
          _objc_enumerationMutation(IVar1);
        }
        objc_stub::doubleValue(*(ID *)(lStack_128 + IVar8 * 8));
        *(ulong *)(*(long *)(param_1 + lVar4) + lVar6 * 8) =
             CONCAT17(extraout_var_05,
                      CONCAT16(extraout_var_04,
                               CONCAT15(extraout_var_03,
                                        CONCAT14(extraout_var_02,
                                                 CONCAT13(extraout_var_01,
                                                          CONCAT12(extraout_var_00,
                                                                   CONCAT11(extraout_var,extraout_b0
                                                                           )))))));
        lVar6 = lVar6 + 1;
        IVar8 = IVar8 + 1;
      } while (IVar3 != IVar8);
      IVar3 = objc_stub::countByEnumeratingWithState_objects_count_
                        (IVar1,&local_130,auStack_e8,0x10);
    } while (IVar3 != 0);
  }
  lVar6 = *(long *)(param_1 + (long)_dspKernel);
  uVar5 = *(undefined8 *)(param_1 + lVar4);
  IVar1 = clickTimes(param_1);
  IVar1 = objc_stub::count(IVar1);
  *(undefined8 *)(lVar6 + 0xc0) = uVar5;
  *(int *)(lVar6 + 200) = (int)IVar1;
  *(undefined4 *)(lVar6 + 0xcc) = 0;
  reset(param_1);
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00005208 ClickAudioUnit::mtDSPKernelAsVoid ====
/* Function Stack Size: 0x10 bytes */

void * ClickAudioUnit::mtDSPKernelAsVoid(ID param_1,SEL param_2)

{
  return *(void **)(param_1 + (long)_dspKernel);
}

// ==== 00005218 ClickAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005228 ClickAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool ClickAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  void *pvVar4;
  long lVar5;
  long lVar6;
  ID IVar7;
  long lVar8;
  undefined8 uVar9;
  undefined1 extraout_b0;
  undefined1 extraout_b0_00;
  undefined1 extraout_var;
  undefined1 extraout_var_00;
  undefined1 extraout_var_01;
  undefined1 extraout_var_02;
  undefined1 extraout_var_03;
  undefined1 extraout_var_04;
  undefined1 extraout_var_05;
  undefined1 extraout_var_06;
  undefined1 extraout_var_07;
  undefined1 extraout_var_08;
  undefined1 extraout_var_09;
  undefined1 extraout_var_10;
  undefined1 extraout_var_11;
  undefined1 extraout_var_12;
  undefined8 local_150;
  long lStack_148;
  long *local_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  ID local_110;
  class_t *pcStack_108;
  undefined1 auStack_100 [128];
  long local_80;
  
  local_80 = *(long *)PTR____stack_chk_guard_0000c020;
  pcStack_108 = &objc::class_t::ClickAudioUnit;
  local_110 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_110,"allocateRenderResourcesAndReturnError:");
  bVar1 = 0;
  if ((int)IVar2 != 0) {
    IVar2 = auOutputBus(param_1);
    IVar2 = objc_stub::format(IVar2);
    IVar2 = objc_stub::channelCount(IVar2);
    lVar8 = (long)_bufferedOutputBus;
    IVar3 = objc_stub::format(*(ID *)(param_1 + lVar8));
    IVar3 = objc_stub::channelCount(IVar3);
    if ((int)IVar2 == (int)IVar3) {
      IVar2 = objc_stub::maximumFramesToRender(param_1);
      __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar8,IVar2);
      lVar8 = (long)_clickTimesCArray;
      if (*(long *)(param_1 + lVar8) != 0) {
        __ZdaPv();
        *(undefined8 *)(param_1 + lVar8) = 0;
      }
      IVar2 = clickTimes(param_1);
      IVar2 = objc_stub::count(IVar2);
      pvVar4 = _malloc(IVar2 << 3);
      *(void **)(param_1 + lVar8) = pvVar4;
      uStack_128 = 0;
      local_130 = 0;
      uStack_118 = 0;
      uStack_120 = 0;
      lStack_148 = 0;
      local_150 = 0;
      uStack_138 = 0;
      local_140 = (long *)0x0;
      IVar2 = clickTimes(param_1);
      IVar3 = objc_stub::countByEnumeratingWithState_objects_count_
                        (IVar2,&local_150,auStack_100,0x10);
      if (IVar3 != 0) {
        lVar5 = 0;
        lVar6 = *local_140;
        do {
          IVar7 = 0;
          do {
            if (*local_140 != lVar6) {
              _objc_enumerationMutation(IVar2);
            }
            objc_stub::doubleValue(*(ID *)(lStack_148 + IVar7 * 8));
            *(ulong *)(*(long *)(param_1 + lVar8) + lVar5 * 8) =
                 CONCAT17(extraout_var_11,
                          CONCAT16(extraout_var_09,
                                   CONCAT15(extraout_var_07,
                                            CONCAT14(extraout_var_05,
                                                     CONCAT13(extraout_var_03,
                                                              CONCAT12(extraout_var_01,
                                                                       CONCAT11(extraout_var,
                                                                                extraout_b0)))))));
            lVar5 = lVar5 + 1;
            IVar7 = IVar7 + 1;
          } while (IVar3 != IVar7);
          IVar3 = objc_stub::countByEnumeratingWithState_objects_count_
                            (IVar2,&local_150,auStack_100,0x10);
        } while (IVar3 != 0);
      }
      lVar5 = *(long *)(param_1 + (long)_dspKernel);
      IVar2 = auOutputBus(param_1);
      IVar2 = objc_stub::format(IVar2);
      IVar2 = objc_stub::channelCount(IVar2);
      IVar3 = auOutputBus(param_1);
      IVar3 = objc_stub::format(IVar3);
      objc_stub::sampleRate(IVar3);
      IVar3 = url(param_1);
      uVar9 = *(undefined8 *)(param_1 + lVar8);
      IVar7 = clickTimes(param_1);
      IVar7 = objc_stub::count(IVar7);
      *(int *)(lVar5 + 8) = (int)IVar2;
      *(float *)(lVar5 + 0xc) =
           (float)(double)CONCAT17(extraout_var_12,
                                   CONCAT16(extraout_var_10,
                                            CONCAT15(extraout_var_08,
                                                     CONCAT14(extraout_var_06,
                                                              CONCAT13(extraout_var_04,
                                                                       CONCAT12(extraout_var_02,
                                                                                CONCAT11(
                                                  extraout_var_00,extraout_b0_00)))))));
      *(ID *)(lVar5 + 0x10) = IVar3;
      *(undefined8 *)(lVar5 + 0xc0) = uVar9;
      *(int *)(lVar5 + 200) = (int)IVar7;
      *(undefined4 *)(lVar5 + 0xcc) = 0;
      *(undefined4 *)(lVar5 + 0x88) = 0;
      *(undefined8 *)(lVar5 + 0x80) = 0;
      __ZN14ClickDSPKernel14setUpAudioFileEv(lVar5);
      reset(param_1);
      bVar1 = 1;
    }
    else {
      if (param_3 != (ID *)0x0) {
        IVar2 = NSError::errorWithDomain_code_userInfo_
                          ((ID)&_OBJC_CLASS___NSError,
                           *(undefined8 *)PTR__NSOSStatusErrorDomain_0000c000,0xffffffffffffd585,0);
        *param_3 = IVar2;
      }
      objc_stub::setRenderResourcesAllocated_(param_1,0);
      bVar1 = 0;
    }
  }
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_80) {
    return bVar1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 0000561c __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void __ZN16BufferedAudioBus23allocateRenderResourcesEj(ID *param_1,undefined4 param_2)

{
  ID IVar1;
  ID IVar2;
  
  *(undefined4 *)(param_1 + 1) = param_2;
  IVar1 = _objc_alloc(&_OBJC_CLASS___AVAudioPCMBuffer);
  IVar2 = objc_stub::format(*param_1);
  IVar1 = AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(IVar1,IVar2,(ulong)(uint)param_1[1]);
  IVar2 = param_1[2];
  param_1[2] = IVar1;
  IVar1 = objc_stub::audioBufferList(param_1[2],IVar2);
  param_1[3] = IVar1;
  IVar1 = objc_stub::mutableAudioBufferList(param_1[2]);
  param_1[4] = IVar1;
  return;
}

// ==== 000056bc ClickAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void ClickAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  __ZN14ClickDSPKernel7cleanupEv(*(undefined8 *)(param_1 + (long)_dspKernel));
  pcStack_28 = &objc::class_t::ClickAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 00005728 ClickAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

{
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  undefined8 *local_68;
  undefined1 auStack_60 [8];
  undefined8 local_58;
  undefined8 *puStack_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined1 auStack_38 [8];
  
  _objc_initWeak(auStack_38,param_1);
  local_58 = 0;
  local_48 = 0x2020000000;
  local_40 = *(undefined8 *)(param_1 + (long)_dspKernel);
  local_88 = PTR___NSConcreteStackBlock_0000c018;
  local_80 = 0xc2000000;
  local_78 = ___37__ClickAudioUnit_internalRenderBlock__block_invoke;
  puStack_70 = &
               ___block_descriptor_48_ea8_32r40w_e433_i60__0_I8r__AudioTimeStamp_dQdQ_SMPTETime_ssIIIssss_II_16I24q28__AudioBufferList_I_1_AudioBuffer_II_v___36r__AURenderEvent__AURenderEventHeader___AURenderEvent_qCC__AUParameterEvent___AURenderEvent_qC_3C_IQf__AUMIDIEvent___AURenderEvent_qCCSC_3C___AUMIDIEventList___AURenderEvent_qCCC_MIDIEventList_iI_1_MIDIEventPacket_QI_64I______44__<i___I__AudioTimeStamp_dQdQ_SMPTETime_ssIIIssss_II_Iq__AudioBufferList_I[1_AudioBuffer_II_v_]_>52l
  ;
  puStack_50 = &local_58;
  _objc_copyWeak(auStack_60,auStack_38);
  local_68 = &local_58;
  _objc_destroyWeak(auStack_60);
  __Block_object_dispose(&local_58,8);
  _objc_destroyWeak(auStack_38);
  return (ID)&local_88;
}

// ==== 000057f0 ___37-[ClickAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___37__ClickAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)ClickAudioUnit::_bufferedOutputBus,param_6,param_4,
               1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x78) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005898 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
void __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
               (long param_1,uint *param_2,int param_3,int param_4)

{
  long lVar1;
  void *pvVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  
  uVar3 = (ulong)*param_2;
  if (*param_2 != 0) {
    lVar4 = 0;
    uVar5 = 0;
    do {
      lVar1 = *(long *)(param_1 + 0x18) + lVar4;
      *(undefined4 *)((long)param_2 + lVar4 + 8) = *(undefined4 *)(lVar1 + 8);
      *(int *)((long)param_2 + lVar4 + 0xc) = param_3 << 2;
      pvVar2 = *(void **)((long)param_2 + lVar4 + 0x10);
      if (pvVar2 == (void *)0x0) {
        pvVar2 = *(void **)(lVar1 + 0x10);
        *(void **)((long)param_2 + lVar4 + 0x10) = pvVar2;
      }
      if (param_4 != 0) {
        _bzero(pvVar2,(ulong)(uint)(param_3 << 2));
        uVar3 = (ulong)*param_2;
      }
      uVar5 = uVar5 + 1;
      lVar4 = lVar4 + 0x10;
    } while (uVar5 < uVar3);
  }
  return;
}

// ==== 00005930 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005968 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005994 ClickAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool ClickAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 0000599c ClickAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 000059ac ClickAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000059c0 ClickAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 000059e0 ClickAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 000059f4 ClickAudioUnit::auOutputBus ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005a04 ClickAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005a10 ClickAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005a20 ClickAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005a2c ClickAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005a3c ClickAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00005a48 ClickAudioUnit::url ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::url(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_url);
}

// ==== 00005a58 ClickAudioUnit::setUrl: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setUrl_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_url) = param_3;
  return;
}

// ==== 00005a64 ClickAudioUnit::clickTimes ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::clickTimes(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_clickTimes);
}

// ==== 00005a74 ClickAudioUnit::setClickTimes: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void ClickAudioUnit::setClickTimes_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_clickTimes) = param_3;
  return;
}

// ==== 00005a80 ClickAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void ClickAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_clickTimes) = 0;
  *(undefined8 *)(param_1 + (long)_url) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005b3c ClickAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID ClickAudioUnit::_cxx_construct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + (long)_bufferedOutputBus);
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 1) = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = 0;
  return param_1;
}

// ==== 00005b5c __ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp
               (long param_1,uint param_2,int param_3,undefined8 *param_4)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  uint uVar9;
  long lVar10;
  long *plVar11;
  ulong uVar12;
  float *pfVar13;
  ulong uVar14;
  float fVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined *local_c0;
  undefined8 local_b8;
  code *local_b0;
  undefined *puStack_a8;
  long local_a0;
  undefined *local_98;
  undefined8 local_90;
  code *local_88;
  undefined *puStack_80;
  long local_78;
  
  uVar17 = param_4[1];
  uVar16 = *param_4;
  uVar19 = param_4[3];
  uVar18 = param_4[2];
  uVar21 = param_4[5];
  uVar20 = param_4[4];
  uVar22 = param_4[6];
  *(undefined8 *)(param_1 + 0x110) = param_4[7];
  *(undefined8 *)(param_1 + 0x108) = uVar22;
  *(undefined8 *)(param_1 + 0x100) = uVar21;
  *(undefined8 *)(param_1 + 0xf8) = uVar20;
  *(undefined8 *)(param_1 + 0xf0) = uVar19;
  *(undefined8 *)(param_1 + 0xe8) = uVar18;
  *(undefined8 *)(param_1 + 0xe0) = uVar17;
  *(undefined8 *)(param_1 + 0xd8) = uVar16;
  puVar7 = PTR___dispatch_main_q_0000c028;
  if ((*(byte *)(param_1 + 0x90) & 1) == 0) {
    if (param_2 != 0) {
      uVar14 = 0;
      uVar9 = *(uint *)(param_1 + 8);
      do {
        if (0 < (int)uVar9) {
          plVar11 = *(long **)(param_1 + 0x78);
          uVar12 = (ulong)uVar9;
          pfVar13 = (float *)(param_1 + 0xd0);
          do {
            plVar11 = plVar11 + 2;
            *(float *)(*plVar11 + (long)((int)uVar14 + param_3) * 4) = *pfVar13 * 0.0;
            uVar12 = uVar12 - 1;
            pfVar13 = pfVar13 + 1;
          } while (uVar12 != 0);
        }
        uVar14 = uVar14 + 1;
      } while (uVar14 != param_2);
    }
  }
  else {
    piVar1 = (int *)(param_1 + 0x8c);
    piVar2 = (int *)(param_1 + 0xcc);
    if (param_2 != 0) {
      uVar14 = 0;
      iVar8 = (int)(*(double *)(*(long *)(param_1 + 0xc0) + (long)*piVar2 * 8) *
                   (double)*(float *)(param_1 + 0xc));
      uVar5 = *(int *)(param_1 + 0x88) - *piVar1;
      uVar9 = 0;
      if (*(int *)(param_1 + 8) != 0) {
        uVar9 = (int)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU)) / *(int *)(param_1 + 8);
      }
      if (param_2 <= uVar9) {
        uVar9 = param_2;
      }
      do {
        if (0 < *(int *)(param_1 + 8)) {
          lVar10 = 0;
          fVar15 = 0.0;
          do {
            if ((long)uVar14 < (long)(int)uVar9) {
              fVar15 = 0.0;
              if ((*(byte *)(param_1 + 0x91) & 1) == 0) {
                fVar15 = *(float *)(*(long *)(param_1 + 0x80) + (long)*(int *)(param_1 + 0x8c) * 4);
              }
              if (*(int *)(param_1 + 0x8c) < *(int *)(param_1 + 0x88) + -1) {
                do {
                  cVar3 = '\x01';
                  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar4) {
                    *piVar1 = *piVar1 + 1;
                    cVar3 = ExclusiveMonitorsStatus();
                  }
                } while (cVar3 != '\0');
              }
            }
            *(float *)(*(long *)(*(long *)(param_1 + 0x78) + lVar10 * 0x10 + 0x10) +
                      (long)((int)uVar14 + param_3) * 4) =
                 fVar15 * *(float *)(param_1 + 0xd0 + lVar10 * 4);
            lVar10 = lVar10 + 1;
          } while (lVar10 < *(int *)(param_1 + 8));
        }
        if (iVar8 <= *(int *)(param_1 + 0xb8) + (int)uVar14) {
          if (*(long *)(param_1 + 0x150) != 0) {
            local_98 = PTR___NSConcreteStackBlock_0000c018;
            local_90 = 0xc0000000;
            local_88 = ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke;
            puStack_80 = &___block_descriptor_40_e5_v8__0l;
            local_78 = param_1;
            _dispatch_async(puVar7,&local_98);
          }
          *piVar1 = 0;
          __ZZN14ClickDSPKernel7processEjjPK14AudioTimeStampE18currentSampleIndex = 0;
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar4) {
              *piVar2 = *piVar2 + 1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          if (*(int *)(param_1 + 200) <= *(int *)(param_1 + 0xcc)) {
            *piVar2 = *(int *)(param_1 + 200) + -1;
          }
          iVar8 = (int)(*(double *)(*(long *)(param_1 + 0xc0) + (long)*(int *)(param_1 + 0xcc) * 8)
                       * (double)*(float *)(param_1 + 0xc));
          uVar9 = param_2;
        }
        uVar14 = uVar14 + 1;
      } while (uVar14 != param_2);
    }
    piVar1 = (int *)(param_1 + 0xb8);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + param_2;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (*(int *)(param_1 + 0xa0) < *(int *)(param_1 + 0xb8)) {
      iVar8 = *(int *)(param_1 + 0xa4);
      iVar6 = *(int *)(param_1 + 0xb8) - *(int *)(param_1 + 0xa0);
      if ((iVar8 == -1) || (*(int *)(param_1 + 0xa8) == -1)) {
        *(int *)(param_1 + 0xb8) = *(int *)(param_1 + 0x9c) + iVar6;
      }
      else {
        *(int *)(param_1 + 0xb8) = iVar8 + iVar6;
        *(int *)(param_1 + 0x9c) = iVar8;
        *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa8);
        *(undefined8 *)(param_1 + 0xa4) = 0xffffffffffffffff;
      }
      __ZN14ClickDSPKernel24resetClickTimesNextIndexEv(param_1);
      if ((int)(*(double *)(*(long *)(param_1 + 0xc0) + (long)*(int *)(param_1 + 0xcc) * 8) *
               (double)*(float *)(param_1 + 0xc)) < *(int *)(param_1 + 0xb8)) {
        if (*(long *)(param_1 + 0x150) != 0) {
          local_c0 = PTR___NSConcreteStackBlock_0000c018;
          local_b8 = 0xc0000000;
          local_b0 = ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke_2;
          puStack_a8 = &___block_descriptor_40_e5_v8__0l;
          local_a0 = param_1;
          _dispatch_async(PTR___dispatch_main_q_0000c028,&local_c0);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        if (*(int *)(param_1 + 200) <= *(int *)(param_1 + 0xcc)) {
          *piVar2 = *(int *)(param_1 + 200) + -1;
        }
      }
    }
  }
  return;
}

// ==== 00005f08 __ZN14ClickDSPKernel9startRampEyfj ====
void __ZN14ClickDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00005f0c __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00005f10 __ZN14ClickDSPKernel35syncRealTimeTimelineFrameWithMasterEi ====
void __ZN14ClickDSPKernel35syncRealTimeTimelineFrameWithMasterEi(long param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 0xb8);
  if ((*piVar1 != param_2) &&
     (iVar2 = *piVar1, *piVar1 = param_2, param_2 + 0x400 < iVar2 || iVar2 < param_2 + -0x400)) {
    __ZN14ClickDSPKernel24resetClickTimesNextIndexEv();
    return;
  }
  return;
}

// ==== 00005f44 ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke ====
void ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(*(long *)(param_1 + 0x20) + 0x150);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00005f58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x30))();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
}

// ==== 00005f68 __ZN14ClickDSPKernel24resetClickTimesNextIndexEv ====
void __ZN14ClickDSPKernel24resetClickTimesNextIndexEv(long param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  
  if (-1 < *(int *)(param_1 + 0x9c)) {
    piVar1 = (int *)(param_1 + 0xcc);
    *piVar1 = 0;
    while (*(long *)(param_1 + 0xc0) != 0) {
      iVar6 = (int)(*(double *)(*(long *)(param_1 + 0xc0) + (long)*(int *)(param_1 + 0xcc) * 8) *
                   (double)*(float *)(param_1 + 0xc));
      if (*(int *)(param_1 + 0xb8) < iVar6) {
        return;
      }
      uVar5 = iVar6 - *(int *)(param_1 + 0xb8);
      uVar2 = -uVar5;
      if (-1 < (int)uVar5) {
        uVar2 = uVar5;
      }
      if (uVar2 < 10) {
        return;
      }
      if (*(int *)(param_1 + 200) + -1 <= *(int *)(param_1 + 0xcc)) {
        return;
      }
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
    }
  }
  return;
}

// ==== 00005ff0 ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke_2 ====
void ____ZN14ClickDSPKernel7processEjjPK14AudioTimeStamp_block_invoke_2(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(*(long *)(param_1 + 0x20) + 0x150);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00006004. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x30))();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
}

// ==== 00006014 __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_0000c1d8;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00006048 __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 0000604c __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 00006060 __ZNSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEaSERKS6_ ====
undefined8 __ZNSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEaSERKS6_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c020;
  __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvi18ClickFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
            (alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_000060c4;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_000060c4:
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000060f4 __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_ ====
long __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(long param_1,long *param_2)

{
  long *plVar1;
  undefined8 uVar2;
  
  plVar1 = (long *)param_2[3];
  if (plVar1 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  else if (plVar1 == param_2) {
    *(long *)(param_1 + 0x18) = param_1;
    (**(code **)(*(long *)param_2[3] + 0x18))((long *)param_2[3],param_1);
  }
  else {
    uVar2 = (**(code **)(*plVar1 + 0x10))();
    *(undefined8 *)(param_1 + 0x18) = uVar2;
  }
  return param_1;
}

// ==== 00006158 __ZNSt3__110__function12__value_funcIFvi18ClickFileOperationPK7__CFURLEE4swapB8ne190102ERS7_ ====
void __ZNSt3__110__function12__value_funcIFvi18ClickFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c020;
  if (param_2 != param_1) {
    plVar1 = (long *)param_1[3];
    plVar2 = (long *)param_2[3];
    if (plVar1 == param_1) {
      if (plVar2 == param_2) {
        (**(code **)(*plVar1 + 0x18))(plVar1,local_40);
        (**(code **)(*(long *)param_1[3] + 0x20))();
        param_1[3] = 0;
        (**(code **)(*(long *)param_2[3] + 0x18))((long *)param_2[3],param_1);
        (**(code **)(*(long *)param_2[3] + 0x20))();
        param_2[3] = 0;
        param_1[3] = (long)param_1;
        (**(code **)(local_40[0] + 0x18))(local_40,param_2);
        (**(code **)(local_40[0] + 0x20))(local_40);
      }
      else {
        (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
        (**(code **)(*(long *)param_1[3] + 0x20))();
        param_1[3] = param_2[3];
      }
      param_2[3] = (long)param_2;
    }
    else if (plVar2 == param_2) {
      (**(code **)(*plVar2 + 0x18))(plVar2,param_1);
      (**(code **)(*(long *)param_2[3] + 0x20))();
      param_2[3] = param_1[3];
      param_1[3] = (long)param_1;
    }
    else {
      param_1[3] = (long)plVar2;
      param_2[3] = (long)plVar1;
    }
  }
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000062c4 __ZNSt3__18functionIFvvEEaSERKS2_ ====
undefined8 __ZNSt3__18functionIFvvEEaSERKS2_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c020;
  __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00006328;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00006328:
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00006358 __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_ ====
void __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c020;
  if (param_2 != param_1) {
    plVar1 = (long *)param_1[3];
    plVar2 = (long *)param_2[3];
    if (plVar1 == param_1) {
      if (plVar2 == param_2) {
        (**(code **)(*plVar1 + 0x18))(plVar1,local_40);
        (**(code **)(*(long *)param_1[3] + 0x20))();
        param_1[3] = 0;
        (**(code **)(*(long *)param_2[3] + 0x18))((long *)param_2[3],param_1);
        (**(code **)(*(long *)param_2[3] + 0x20))();
        param_2[3] = 0;
        param_1[3] = (long)param_1;
        (**(code **)(local_40[0] + 0x18))(local_40,param_2);
        (**(code **)(local_40[0] + 0x20))(local_40);
      }
      else {
        (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
        (**(code **)(*(long *)param_1[3] + 0x20))();
        param_1[3] = param_2[3];
      }
      param_2[3] = (long)param_2;
    }
    else if (plVar2 == param_2) {
      (**(code **)(*plVar2 + 0x18))(plVar2,param_1);
      (**(code **)(*(long *)param_2[3] + 0x20))();
      param_2[3] = param_1[3];
      param_1[3] = (long)param_1;
    }
    else {
      param_1[3] = (long)plVar2;
      param_2[3] = (long)plVar1;
    }
  }
  if (*(long *)PTR____stack_chk_guard_0000c020 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000064c4 __ZN14ClickDSPKernel14setUpAudioFileEv ====
/* WARNING: Type propagation algorithm not settling */

void __ZN14ClickDSPKernel14setUpAudioFileEv(long param_1)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  void *pvVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 local_60 [2];
  undefined4 local_58;
  undefined4 uStack_54;
  void *local_50;
  int local_48 [2];
  
  uVar3 = _ExtAudioFileOpenURL(*(undefined8 *)(param_1 + 0x10),param_1 + 0x18);
  if ((int)uVar3 == 0) {
    uVar3 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x18),0);
    if ((int)uVar3 == 0) {
      local_48[1] = 0x28;
      uVar3 = _ExtAudioFileGetProperty
                        (*(undefined8 *)(param_1 + 0x18),0x66666d74,local_48 + 1,param_1 + 0x20);
      if ((int)uVar3 == 0) {
        *(double *)(param_1 + 0x50) = (double)*(float *)(param_1 + 0xc);
        *(undefined8 *)(param_1 + 0x58) = 0x16c70636d;
        iVar1 = *(int *)(param_1 + 8) << 2;
        *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 8);
        *(undefined4 *)(param_1 + 0x70) = 0x20;
        *(undefined4 *)(param_1 + 100) = 1;
        *(int *)(param_1 + 0x68) = iVar1;
        *(int *)(param_1 + 0x60) = iVar1;
        local_48[1] = 0x28;
        uVar3 = _ExtAudioFileSetProperty(*(undefined8 *)(param_1 + 0x18),0x63666d74,0x28);
        if ((int)uVar3 == 0) {
          local_48[1] = 8;
          uVar3 = _ExtAudioFileGetProperty
                            (*(undefined8 *)(param_1 + 0x18),0x2366726d,local_48 + 1,param_1 + 0x48)
          ;
          if ((int)uVar3 == 0) {
            *(double *)(param_1 + 0xb0) = *(double *)(param_1 + 0x20) / *(double *)(param_1 + 0x50);
            iVar1 = *(int *)(param_1 + 0x48);
            uVar2 = *(int *)(param_1 + 0x3c) * iVar1;
            pvVar4 = _malloc(-(ulong)(uVar2 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar2 << 2);
            local_58 = *(undefined4 *)(param_1 + 0x6c);
            local_60[0] = 1;
            uStack_54 = (undefined4)((ulong)uVar2 << 2);
            local_50 = pvVar4;
            local_48[0] = iVar1;
            uVar3 = _ExtAudioFileRead(*(undefined8 *)(param_1 + 0x18),local_48,local_60);
            if ((int)uVar3 == 0) {
              *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x88) + -1;
              lVar5 = *(long *)(param_1 + 0x80);
              *(void **)(param_1 + 0x80) = pvVar4;
              *(uint *)(param_1 + 0x88) = uVar2;
              if (lVar5 == 0) {
                return;
              }
              __ZdaPv();
              return;
            }
            if (*(long *)(param_1 + 0x130) == 0) {
              return;
            }
            uVar7 = *(undefined8 *)(param_1 + 0x10);
            uVar6 = 2;
          }
          else {
            if (*(long *)(param_1 + 0x130) == 0) {
              return;
            }
            uVar7 = *(undefined8 *)(param_1 + 0x10);
            uVar6 = 5;
          }
        }
        else {
          if (*(long *)(param_1 + 0x130) == 0) {
            return;
          }
          uVar7 = *(undefined8 *)(param_1 + 0x10);
          uVar6 = 6;
        }
      }
      else {
        if (*(long *)(param_1 + 0x130) == 0) {
          return;
        }
        uVar7 = *(undefined8 *)(param_1 + 0x10);
        uVar6 = 4;
      }
      __ZNKSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEclEiS1_S4_
                (param_1 + 0x118,uVar3,uVar6,uVar7);
      return;
    }
    if (*(long *)(param_1 + 0x130) == 0) {
      return;
    }
    uVar7 = *(undefined8 *)(param_1 + 0x10);
    uVar6 = 3;
  }
  else {
    if (*(long *)(param_1 + 0x130) == 0) {
      return;
    }
    uVar7 = *(undefined8 *)(param_1 + 0x10);
    uVar6 = 1;
  }
  __ZNKSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEclEiS1_S4_
            (param_1 + 0x118,uVar3,uVar6,uVar7);
  return;
}

// ==== 000066ec __ZNKSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEclEiS1_S4_ ====
void __ZNKSt3__18functionIFvi18ClickFileOperationPK7__CFURLEEclEiS1_S4_
               (long param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4)

{
  long *plVar1;
  undefined8 local_20;
  undefined4 local_18;
  undefined4 local_14;
  
  plVar1 = *(long **)(param_1 + 0x18);
  local_20 = param_4;
  local_18 = param_3;
  local_14 = param_2;
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x30))(plVar1,&local_14,&local_18,&local_20);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
}

// ==== 00006734 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 0000675c __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00006784 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_0000c200;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 000067c4 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE ====
void __ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_0000c200;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 000067e0 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 000067e8 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00006810 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEEclEOiOS5_OS8_ ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEEclEOiOS5_OS8_
          (long param_1,uint *param_2,uint *param_3,undefined8 *param_4)

{
  uint uVar1;
  uint uVar2;
  ID self;
  undefined8 uVar3;
  
  uVar1 = *param_2;
  uVar2 = *param_3;
  uVar3 = *param_4;
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::clickAudioUnitErrorStatus_operation_fileURL_(self,(ulong)uVar1,(ulong)uVar2,uVar3);
  return 0;
}

// ==== 000068a0 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 000068dc __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0NS_9allocatorIS2_EEFvi18ClickFileOperationPK7__CFURLEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__0
  ;
}

// ==== 000068e8 __ZNKSt9type_infoeqB8ne190102ERKS_ ====
bool __ZNKSt9type_infoeqB8ne190102ERKS_(long param_1,long param_2)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = *(ulong *)(param_1 + 8);
  uVar3 = *(ulong *)(param_2 + 8);
  if (uVar2 == uVar3) {
    return true;
  }
  if (-1 < (long)(uVar3 & uVar2)) {
    return false;
  }
  iVar1 = _strcmp((char *)(uVar2 & 0x7fffffffffffffff),(char *)(uVar3 & 0x7fffffffffffffff));
  return iVar1 == 0;
}

// ==== 00006934 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 0000695c __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00006984 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_0000c290;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 000069c4 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE ====
void __ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_0000c290;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 000069e0 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 000069e8 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00006a10 __ZNSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEEclEv ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEEclEv
          (long param_1)

{
  ID self;
  
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::clickAudioUnitDidInvokeClick(self);
  return 0;
}

// ==== 00006a80 __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 00006abc __ZNKSt3__110__function6__funcIZ81-[ClickAudioUnit_configureDSPKernelWithFileURL:clickTimes:delegate:reportsClick:]E3$_1NS_9allocatorIS2_EEFvvEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1NS_9allocatorIS2_EEFvvEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__ClickAudioUnit_configureDSPKernelWithFileURL_clickTimes_delegate_reportsClick__E3__1
  ;
}

// ==== 00006ac8 _ExtAudioFileDispose ====
void _ExtAudioFileDispose(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006ad0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileDispose_0000ca08)();
  return;
}

// ==== 00006ad4 _ExtAudioFileGetProperty ====
void _ExtAudioFileGetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006adc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileGetProperty_0000ca10)();
  return;
}

// ==== 00006ae0 _ExtAudioFileOpenURL ====
void _ExtAudioFileOpenURL(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileOpenURL_0000ca18)();
  return;
}

// ==== 00006aec _ExtAudioFileRead ====
void _ExtAudioFileRead(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006af4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileRead_0000ca20)();
  return;
}

// ==== 00006af8 _ExtAudioFileSeek ====
void _ExtAudioFileSeek(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSeek_0000ca28)();
  return;
}

// ==== 00006b04 _ExtAudioFileSetProperty ====
void _ExtAudioFileSetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSetProperty_0000ca30)();
  return;
}

// ==== 00006b10 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00006b18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_0000ca38)(param_1,param_2,param_3);
  return;
}

// ==== 00006b1c __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00006b24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_0000ca40)(param_1,param_2);
  return;
}

// ==== 00006b28 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00006b30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_0000ca48)();
  return;
}

// ==== 00006b34 __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_0000ca50)();
  return;
}

// ==== 00006b40 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_0000ca58)();
  return;
}

// ==== 00006b4c __ZdaPv ====
void __ZdaPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdaPv_0000c038)();
  return;
}

// ==== 00006b58 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_0000c040)();
  return;
}

// ==== 00006b64 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_0000c048)();
  return;
}

// ==== 00006b70 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_0000ca60)();
  return;
}

// ==== 00006b7c ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_0000ca68)();
  return;
}

// ==== 00006b88 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_0000ca70)();
  return;
}

// ==== 00006b94 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006b9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_0000ca78)();
  return;
}

// ==== 00006ba0 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00006ba8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_0000ca80)();
  return;
}

// ==== 00006bac _dispatch_async ====
void _dispatch_async(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006bb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_async_0000ca88)();
  return;
}

// ==== 00006bb8 _malloc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _malloc(size_t param_1)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006bc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__malloc_0000ca90)();
  return pvVar1;
}

// ==== 00006bc4 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006bcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_0000ca98)();
  return;
}

// ==== 00006bd0 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006bd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_0000caa0)();
  return;
}

// ==== 00006bdc _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006be4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_0000caa8)();
  return;
}

// ==== 00006be8 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006bf0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_0000cab0)();
  return;
}

// ==== 00006bf4 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006bfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_0000cab8)();
  return;
}

// ==== 00006c00 _objc_enumerationMutation ====
void _objc_enumerationMutation(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_enumerationMutation_0000cac0)();
  return;
}

// ==== 00006c0c _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_0000cac8)();
  return;
}

// ==== 00006c18 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_0000cad0)();
  return;
}

// ==== 00006c24 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_0000cad8)();
  return;
}

// ==== 00006c30 _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_0000cae0)();
  return;
}

// ==== 00006c3c _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006c44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_0000cae8)();
  return IVar1;
}

// ==== 00006c48 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_0000caf0)();
  return;
}

// ==== 00006c54 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_0000caf8)();
  return;
}

// ==== 00006c60 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_0000cb00)();
  return;
}

// ==== 00006c6c _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_0000cb08)();
  return;
}

// ==== 00006c78 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_0000cb10)();
  return;
}

// ==== 00006c84 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_0000cb18)();
  return;
}

// ==== 00006c90 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006c98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_0000cb20)();
  return;
}

// ==== 00006c9c _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006ca4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_0000cb28)();
  return;
}

// ==== 00006ca8 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006cb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_0000cb30)((int)param_1);
  return iVar1;
}

// ==== 00006ea0 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"address");
  return IVar1;
}

// ==== 00006ec0 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00006ee0 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00006f00 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00006f20 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"channelCount");
  return IVar1;
}

// ==== 00006f40 objc_stub::clickAudioUnitDidInvokeClick ====
ID __objc_msgSend_stub objc_stub::clickAudioUnitDidInvokeClick(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"clickAudioUnitDidInvokeClick");
  return IVar1;
}

// ==== 00006f60 objc_stub::clickAudioUnitErrorStatus:operation:fileURL: ====
ID __objc_msgSend_stub objc_stub::clickAudioUnitErrorStatus_operation_fileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"clickAudioUnitErrorStatus:operation:fileURL:")
  ;
  return IVar1;
}

// ==== 00006f80 objc_stub::clickTimes ====
ID __objc_msgSend_stub objc_stub::clickTimes(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"clickTimes");
  return IVar1;
}

// ==== 00006fa0 objc_stub::count ====
ID __objc_msgSend_stub objc_stub::count(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"count");
  return IVar1;
}

// ==== 00006fc0 objc_stub::countByEnumeratingWithState:objects:count: ====
ID __objc_msgSend_stub objc_stub::countByEnumeratingWithState_objects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"countByEnumeratingWithState:objects:count:");
  return IVar1;
}

// ==== 00006fe0 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
ID __objc_msgSend_stub
objc_stub::
createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
          (ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)
                    (self,
                     "createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters:"
                    );
  return IVar1;
}

// ==== 00007000 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00007020 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00007040 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"delegate");
  return IVar1;
}

// ==== 00007060 objc_stub::doubleValue ====
ID __objc_msgSend_stub objc_stub::doubleValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"doubleValue");
  return IVar1;
}

// ==== 00007080 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 000070a0 objc_stub::floatValue ====
ID __objc_msgSend_stub objc_stub::floatValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"floatValue");
  return IVar1;
}

// ==== 000070c0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"format");
  return IVar1;
}

// ==== 000070e0 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00007100 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00007120 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00007140 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00007160 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00007180 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 000071a0 objc_stub::objectAtIndexedSubscript: ====
ID __objc_msgSend_stub objc_stub::objectAtIndexedSubscript_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"objectAtIndexedSubscript:");
  return IVar1;
}

// ==== 000071c0 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"reset");
  return IVar1;
}

// ==== 000071e0 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"sampleRate");
  return IVar1;
}

// ==== 00007200 objc_stub::setClickTimes: ====
ID __objc_msgSend_stub objc_stub::setClickTimes_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setClickTimes:");
  return IVar1;
}

// ==== 00007220 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00007240 objc_stub::setDelegate: ====
ID __objc_msgSend_stub objc_stub::setDelegate_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setDelegate:");
  return IVar1;
}

// ==== 00007260 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00007280 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 000072a0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 000072c0 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 000072e0 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00007300 objc_stub::setUrl: ====
ID __objc_msgSend_stub objc_stub::setUrl_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setUrl:");
  return IVar1;
}

// ==== 00007320 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setValue:");
  return IVar1;
}

// ==== 00007340 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00007360 objc_stub::url ====
ID __objc_msgSend_stub objc_stub::url(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"url");
  return IVar1;
}

// ==== 00007380 objc_stub::value ====
ID __objc_msgSend_stub objc_stub::value(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"value");
  return IVar1;
}

// ==== 0001c101 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c201 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c301 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c302 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c303 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c401 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c501 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c601 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c701 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c801 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c901 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c902 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c903 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c904 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c905 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c906 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c907 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001d700 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

