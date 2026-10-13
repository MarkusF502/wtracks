// AutomationAUFramework sha256 19a5173c77eb697226dcb11336f5266d9a51a8b1e2c274ca71d9a41be15caa98 (Ghidra 12.1.4, all decompiled functions)

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
                    /* WARNING: Could not recover jumptable at 0x00004158. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)*param_1)(param_1,param_3,iVar1 - iVar2);
        return;
      }
      uVar3 = param_4[1] - lVar4 & (param_4[1] - lVar4 >> 0x3f ^ 0xffffffffffffffffU);
      if ((int)uVar3 != 0) {
        (**(code **)*param_1)(param_1,uVar3,iVar1 - iVar2);
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

// ==== 0000415c AutomationAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID AutomationAudioUnit::initWithComponentDescription_options_error_
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
  
  local_80 = *(long *)PTR____stack_chk_guard_00008030;
  puStack_e8 = *(undefined8 **)&param_3->field2_0x8;
  local_f0._0_4_ = param_3->field0_0x0;
  local_f0._4_4_ = param_3->field1_0x4;
  local_e0 = CONCAT44(local_e0._4_4_,param_3->field4_0x10);
  pcStack_c0 = &objc::class_t::AutomationAudioUnit;
  local_c8 = param_1;
  self = AUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_c8,"initWithComponentDescription:options:error:",&local_f0,
                    (ulong)param_4);
  if (self != 0) {
    IVar2 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar2 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar2,0x40e5888000000000,2);
    AUAudioUnit::setDefaultFormat_(self,IVar2);
    lVar5 = (long)_bufferedOutputBus;
    IVar2 = AUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar5,IVar2,2);
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar3 = AUAudioUnit::defaultFormat(self);
    IVar2 = AUAudioUnitBus::initWithFormat_error_(IVar2,IVar3,0);
    lVar5 = (long)_auOutputBus;
    *(ID *)(self + lVar5) = IVar2;
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_88 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_88,1);
    IVar2 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar3);
    uVar4 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    AUAudioUnit::setMaximumFramesToRender_(self,uVar4,0x200);
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isEnabledParameter,
                       &cf_isEnabled,0,2,0,0,0,0);
    IVar3 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isPlayingParameter,
                       &cf_isPlaying,1,2,0,0,0,0);
    self_00 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,&cf_startTimeParameter,
                         &cf_startTime,2,4,0,0,0,0);
    self_01 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,&cf_endTimeParameter,
                         &cf_endTime,3,4,0,0,0,0);
    self_02 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0xbf800000,0x7f7fffff,
                         &cf_enqueuedStartTimeParameter,&cf_enqueuedStartTime,4,4,0,0,0,0);
    self_03 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0xbf800000,0x7f7fffff,
                         &cf_enqueuedEndTimeParameter,&cf_enqueuedEndTime,5,4,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0x7f7fffff);
    AUParameterTree::setValue_(self_02,0xbf800000);
    AUParameterTree::setValue_(self_03,0xbf800000);
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
      local_d8 = (undefined8 *)__Znwm(0x70);
      *local_d8 = &DAT_00008110;
      *(undefined4 *)(local_d8 + 1) = 0;
      local_d8[2] = 0x40e5888000000000;
      local_d8[3] = 0;
      *(undefined4 *)(local_d8 + 4) = 0;
      local_d8[5] = 0;
      local_d8[7] = 0x7fffffff00000000;
      local_d8[6] = 0xffffffff00000000;
      local_d8[8] = 0xffffffffffffffff;
      *(undefined2 *)(local_d8 + 9) = 0;
      local_d8[0xd] = 0;
      *(undefined8 **)(self + lVar5) = local_d8;
    }
    puVar1 = PTR___NSConcreteStackBlock_00008028;
    local_f0 = 0;
    local_e0 = 0x2020000000;
    local_118 = PTR___NSConcreteStackBlock_00008028;
    local_110 = 0xc2000000;
    local_108 = ___66__AutomationAudioUnit_initWithComponentDescription_options_error___block_invoke
    ;
    puStack_100 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_f8 = &local_f0;
    puStack_e8 = &local_f0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_118);
    local_140 = puVar1;
    local_138 = 0xc2000000;
    local_130 = 
    ___66__AutomationAudioUnit_initWithComponentDescription_options_error___block_invoke_28;
    puStack_128 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_120 = &local_f0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_140);
    __Block_object_dispose(&local_f0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008030 == local_80) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 000047c0 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 00004854 ___66-[AutomationAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___66__AutomationAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN19AutomationDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return;
}

// ==== 00004898 __ZN19AutomationDSPKernel12setParameterEyf ====
void __ZN19AutomationDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  if (2 < param_3) {
    if (param_3 == 3) {
      *(int *)(param_2 + 0x3c) = (int)(*(double *)(param_2 + 0x10) * (double)param_1);
      return;
    }
    if (param_3 == 4) {
      *(int *)(param_2 + 0x40) = (int)(*(double *)(param_2 + 0x10) * (double)param_1);
    }
    else if (param_3 == 5) {
      *(int *)(param_2 + 0x44) = (int)(*(double *)(param_2 + 0x10) * (double)param_1);
      return;
    }
    return;
  }
  if (param_3 == 0) {
    param_2 = param_2 + 0x48;
  }
  else {
    if (param_3 != 1) {
      if (param_3 != 2) {
        return;
      }
      *(int *)(param_2 + 0x38) = (int)(*(double *)(param_2 + 0x10) * (double)param_1);
      return;
    }
    param_2 = param_2 + 0x49;
  }
  *(bool *)param_2 = param_1 != 0.0;
  return;
}

// ==== 00004954 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004964 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004970 ___66-[AutomationAudioUnit_initWithComponentDescription:options:error:]_block_invoke.28 ====
void ___66__AutomationAudioUnit_initWithComponentDescription_options_error___block_invoke_28
               (long param_1,ID param_2)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  __ZN19AutomationDSPKernel12getParameterEy(uVar2,IVar1);
  return;
}

// ==== 000049a4 __ZN19AutomationDSPKernel12getParameterEy ====
float __ZN19AutomationDSPKernel12getParameterEy(long param_1,long param_2)

{
  float fVar1;
  int iVar2;
  byte *pbVar3;
  
  if (2 < param_2) {
    if (param_2 == 3) {
      iVar2 = *(int *)(param_1 + 0x3c);
    }
    else if (param_2 == 4) {
      iVar2 = *(int *)(param_1 + 0x40);
    }
    else {
      if (param_2 != 5) {
        return 0.0;
      }
      iVar2 = *(int *)(param_1 + 0x44);
    }
LAB_00004a1c:
    return (float)((double)iVar2 / *(double *)(param_1 + 0x10));
  }
  if (param_2 == 0) {
    pbVar3 = (byte *)(param_1 + 0x48);
  }
  else {
    if (param_2 != 1) {
      if (param_2 != 2) {
        return 0.0;
      }
      iVar2 = *(int *)(param_1 + 0x38);
      goto LAB_00004a1c;
    }
    pbVar3 = (byte *)(param_1 + 0x49);
  }
  fVar1 = 1.0;
  if ((*pbVar3 & 1) == 0) {
    fVar1 = 0.0;
  }
  return fVar1;
}

// ==== 00004a30 AutomationAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void AutomationAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::AutomationAudioUnit;
  local_30 = param_1;
  AUAudioUnit::reset((ID)&local_30,"reset");
  *(undefined1 *)(*(long *)(param_1 + (long)_dspKernel) + 0x49) = 0;
  return;
}

// ==== 00004a84 AutomationAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void AutomationAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  ID local_40;
  class_t *pcStack_38;
  
  lVar4 = (long)_dspKernel;
  __ZN19AutomationDSPKernel19clearAutomationCuesEv(*(undefined8 *)(param_1 + lVar4));
  puVar3 = *(undefined8 **)(param_1 + lVar4);
  if (puVar3 == (undefined8 *)0x0) goto LAB_00004afc;
  *puVar3 = &DAT_00008110;
  puVar3[3] = 0;
  plVar1 = (long *)puVar3[0xd];
  if (plVar1 == puVar3 + 10) {
    lVar2 = 0x20;
LAB_00004ae8:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004ae8;
  }
  __ZdlPv(puVar3);
LAB_00004afc:
  *(undefined8 *)(param_1 + lVar4) = 0;
  pcStack_38 = &objc::class_t::AutomationAudioUnit;
  local_40 = param_1;
  AUAudioUnit::dealloc((ID)&local_40,"dealloc");
  return;
}

// ==== 00004b30 ___clang_call_terminate ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void ___clang_call_terminate(undefined8 param_1,undefined8 param_2,ID param_3,ID param_4)

{
  ID IVar1;
  ID IVar2;
  SEL extraout_x1;
  SEL extraout_x1_00;
  long lVar3;
  undefined1 auVar4 [16];
  undefined1 auStack_78 [8];
  undefined1 auStack_70 [8];
  undefined *puStack_68;
  undefined1 auStack_60 [16];
  undefined **ppuStack_50;
  long lStack_48;
  
  ___cxa_begin_catch();
  auVar4 = __ZSt9terminatev();
  IVar1 = auVar4._0_8_;
  lStack_48 = *(long *)PTR____stack_chk_guard_00008030;
  AutomationAudioUnit::updateAutomationCuesWithCues_(IVar1,auVar4._8_8_,param_3);
  AutomationAudioUnit::setDelegate_(IVar1,extraout_x1,param_4);
  _objc_initWeak(auStack_70,IVar1);
  IVar2 = AutomationAudioUnit::delegate(IVar1,extraout_x1_00);
  if (IVar2 != 0) {
    lVar3 = *(long *)(IVar1 + (long)AutomationAudioUnit::_dspKernel);
    _objc_copyWeak(auStack_78,auStack_70);
    ppuStack_50 = (undefined **)0x0;
    puStack_68 = &DAT_000081a0;
    _objc_moveWeak(auStack_60,auStack_78);
    ppuStack_50 = &puStack_68;
    _objc_destroyWeak(auStack_78);
    __ZNSt3__18functionIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEaSERKS8_
              (lVar3 + 0x50,&puStack_68);
    if (ppuStack_50 == &puStack_68) {
      lVar3 = 0x20;
    }
    else {
      if (ppuStack_50 == (undefined **)0x0) goto LAB_00004c44;
      lVar3 = 0x28;
    }
    (**(code **)(*ppuStack_50 + lVar3))();
  }
LAB_00004c44:
  _objc_destroyWeak(auStack_70);
  if (*(long *)PTR____stack_chk_guard_00008030 == lStack_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004b40 AutomationAudioUnit::configureDSPKernelWithAutomationCues:delegate: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void AutomationAudioUnit::configureDSPKernelWithAutomationCues_delegate_
               (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  ID IVar1;
  long lVar2;
  undefined1 auStack_68 [8];
  undefined1 auStack_60 [8];
  undefined *local_58;
  undefined1 auStack_50 [16];
  undefined **local_40;
  long local_38;
  
  local_38 = *(long *)PTR____stack_chk_guard_00008030;
  updateAutomationCuesWithCues_(param_1,param_3);
  setDelegate_(param_1,param_4);
  _objc_initWeak(auStack_60,param_1);
  IVar1 = delegate(param_1);
  if (IVar1 != 0) {
    lVar2 = *(long *)(param_1 + (long)_dspKernel);
    _objc_copyWeak(auStack_68,auStack_60);
    local_40 = (undefined **)0x0;
    local_58 = &DAT_000081a0;
    _objc_moveWeak(auStack_50,auStack_68);
    local_40 = &local_58;
    _objc_destroyWeak(auStack_68);
    __ZNSt3__18functionIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEaSERKS8_
              (lVar2 + 0x50,&local_58);
    if (local_40 == &local_58) {
      lVar2 = 0x20;
    }
    else {
      if (local_40 == (undefined **)0x0) goto LAB_00004c44;
      lVar2 = 0x28;
    }
    (**(code **)(*local_40 + lVar2))();
  }
LAB_00004c44:
  _objc_destroyWeak(auStack_60);
  if (*(long *)PTR____stack_chk_guard_00008030 == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004cf0 AutomationAudioUnit::updateAutomationCuesWithCues: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::updateAutomationCuesWithCues_(ID param_1,SEL param_2,ID param_3)

{
  void *pvVar1;
  ID IVar2;
  long lVar3;
  
  pvVar1 = automationDSPCuesForAutomationCues_(param_1,param_3);
  lVar3 = *(long *)(param_1 + (long)_dspKernel);
  IVar2 = objc_stub::count(param_3);
  __ZN19AutomationDSPKernel19clearAutomationCuesEv(lVar3);
  *(void **)(lVar3 + 0x28) = pvVar1;
  *(int *)(lVar3 + 0x30) = (int)IVar2;
  __ZN19AutomationDSPKernel23prepareToPlayFromSampleEi(lVar3,*(undefined4 *)(lVar3 + 0x20));
  return;
}

// ==== 00004d88 AutomationAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,double param_3)

{
  __ZN19AutomationDSPKernel23prepareToPlayFromSampleEi
            (*(long *)(param_1 + (long)_dspKernel),
             (int)(*(double *)(*(long *)(param_1 + (long)_dspKernel) + 0x10) *
                  (double)(float)param_3));
  return;
}

// ==== 00004dac AutomationAudioUnit::automationDSPCuesForAutomationCues: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void * AutomationAudioUnit::automationDSPCuesForAutomationCues_(ID param_1,SEL param_2,ID param_3)

{
  ID IVar1;
  undefined8 *puVar2;
  ID IVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  ID self;
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
  undefined1 auStack_f0 [128];
  long local_70;
  
  local_70 = *(long *)PTR____stack_chk_guard_00008030;
  IVar1 = objc_stub::count(param_3);
  uVar4 = IVar1 << 5 | 0x10;
  if (IVar1 >> 0x3b != 0) {
    uVar4 = 0xffffffffffffffff;
  }
  puVar2 = (undefined8 *)__Znam(uVar4);
  *puVar2 = 0x20;
  puVar2[1] = IVar1;
  if (IVar1 != 0) {
    lVar5 = IVar1 << 5;
    puVar6 = puVar2 + 2;
    do {
      *puVar6 = 0;
      puVar6[1] = 0;
      puVar6[2] = 0;
      puVar6 = puVar6 + 4;
      lVar5 = lVar5 + -0x20;
    } while (lVar5 != 0);
  }
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  lStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  local_120 = (long *)0x0;
  IVar1 = objc_stub::countByEnumeratingWithState_objects_count_(param_3,&local_130,auStack_f0,0x10);
  if (IVar1 != 0) {
    lVar5 = 0;
    lVar7 = *local_120;
    do {
      IVar8 = 0;
      puVar6 = puVar2 + lVar5 * 4 + 5;
      do {
        if (*local_120 != lVar7) {
          _objc_enumerationMutation(param_3);
        }
        self = *(ID *)(lStack_128 + IVar8 * 8);
        IVar3 = objc_stub::uuid(self);
        _objc_retainAutorelease();
        IVar3 = objc_stub::cStringUsingEncoding_(IVar3,4);
        __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEPKc
                  (puVar6 + -3,IVar3);
        objc_stub::timecode(self);
        *puVar6 = CONCAT17(extraout_var_05,
                           CONCAT16(extraout_var_04,
                                    CONCAT15(extraout_var_03,
                                             CONCAT14(extraout_var_02,
                                                      CONCAT13(extraout_var_01,
                                                               CONCAT12(extraout_var_00,
                                                                        CONCAT11(extraout_var,
                                                                                 extraout_b0)))))));
        lVar5 = lVar5 + 1;
        IVar8 = IVar8 + 1;
        puVar6 = puVar6 + 4;
      } while (IVar1 != IVar8);
      IVar1 = objc_stub::countByEnumeratingWithState_objects_count_
                        (param_3,&local_130,auStack_f0,0x10);
    } while (IVar1 != 0);
  }
  if (*(long *)PTR____stack_chk_guard_00008030 == local_70) {
    return puVar2 + 2;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004fa8 AutomationAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00004fb8 AutomationAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool AutomationAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  undefined8 extraout_d0;
  ID local_60;
  class_t *pcStack_58;
  
  pcStack_58 = &objc::class_t::AutomationAudioUnit;
  local_60 = param_1;
  IVar2 = AUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_60,"allocateRenderResourcesAndReturnError:");
  bVar1 = 0;
  if ((int)IVar2 != 0) {
    IVar2 = auOutputBus(param_1);
    IVar2 = objc_stub::format(IVar2);
    IVar2 = objc_stub::channelCount(IVar2);
    lVar4 = (long)_bufferedOutputBus;
    IVar3 = objc_stub::format(*(ID *)(param_1 + lVar4));
    IVar3 = objc_stub::channelCount(IVar3);
    if ((int)IVar2 == (int)IVar3) {
      IVar2 = objc_stub::maximumFramesToRender(param_1);
      __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar4,IVar2);
      lVar4 = *(long *)(param_1 + (long)_dspKernel);
      IVar2 = auOutputBus(param_1);
      IVar2 = objc_stub::format(IVar2);
      IVar2 = objc_stub::channelCount(IVar2);
      IVar3 = auOutputBus(param_1);
      IVar3 = objc_stub::format(IVar3);
      objc_stub::sampleRate(IVar3);
      *(int *)(lVar4 + 8) = (int)IVar2;
      *(undefined8 *)(lVar4 + 0x10) = extraout_d0;
      reset(param_1);
      bVar1 = 1;
    }
    else {
      if (param_3 != (ID *)0x0) {
        IVar2 = NSError::errorWithDomain_code_userInfo_
                          ((ID)&_OBJC_CLASS___NSError,
                           *(undefined8 *)PTR__NSOSStatusErrorDomain_00008000,0xffffffffffffd585,0);
        *param_3 = IVar2;
      }
      objc_stub::setRenderResourcesAllocated_(param_1,0);
      bVar1 = 0;
    }
  }
  return bVar1;
}

// ==== 000051dc __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 0000527c AutomationAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void AutomationAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  pcStack_28 = &objc::class_t::AutomationAudioUnit;
  local_30 = param_1;
  AUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 000052d8 AutomationAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool AutomationAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  long lVar5;
  long local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008030;
  IVar2 = objc_stub::busType(param_4);
  if (IVar2 == 2) {
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(param_1 + (long)_bufferedOutputBus,param_3,2);
    IVar3 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    local_68 = 0;
    IVar3 = AUAudioUnitBus::initWithFormat_error_(IVar3,param_3,&local_68);
    lVar1 = local_68;
    lVar5 = (long)_auOutputBus;
    *(ID *)(param_1 + lVar5) = IVar3;
    IVar3 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_60 = *(undefined8 *)(param_1 + lVar5);
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_60,1);
    IVar3 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar3,param_1,2,IVar4);
    *(ID *)(param_1 + (long)_auOutputBusArray) = IVar3;
    if (lVar1 != 0) {
      IVar3 = NSException::exceptionWithName_reason_userInfo_
                        ((ID)&_OBJC_CLASS___NSException,
                         *(undefined8 *)PTR__NSInternalInconsistencyException_00008040,
                         &cf_Cannotinitoutputbuswithnewformat,0);
      NSException::raise(IVar3);
    }
  }
  else {
    IVar3 = NSException::exceptionWithName_reason_userInfo_
                      ((ID)&_OBJC_CLASS___NSException,
                       *(undefined8 *)PTR__NSInternalInconsistencyException_00008040,
                       &cf_Unrecognisedbustype,0);
    NSException::raise(IVar3);
  }
  if (*(long *)PTR____stack_chk_guard_00008030 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return (bool)(IVar2 == 2);
}

// ==== 00005544 AutomationAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_00008028;
  local_80 = 0xc2000000;
  local_78 = ___42__AutomationAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 0000560c ___42-[AutomationAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___42__AutomationAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)AutomationAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x18) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 000056b4 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 0000574c ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005784 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 000057b0 AutomationAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool AutomationAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 000057b8 AutomationAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 000057c8 AutomationAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000057dc AutomationAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 000057fc AutomationAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 00005810 AutomationAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005820 AutomationAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005834 AutomationAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005844 AutomationAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005850 AutomationAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005860 AutomationAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 0000586c AutomationAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void AutomationAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005900 AutomationAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00005920 __ZN19AutomationDSPKernel7processEjj ====
void __ZN19AutomationDSPKernel7processEjj(long param_1,uint param_2,int param_3)

{
  int *piVar1;
  undefined8 *puVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  code *pcVar7;
  int iVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  ulong uVar12;
  undefined8 local_90;
  undefined8 uStack_88;
  long local_80;
  undefined8 local_70;
  undefined8 uStack_68;
  long local_60;
  double local_58;
  
  if (((*(byte *)(param_1 + 0x48) & 1) == 0) || ((*(byte *)(param_1 + 0x49) & 1) == 0)) {
    if (param_2 != 0) {
      uVar12 = 0;
      uVar4 = *(uint *)(param_1 + 8);
      do {
        if (0 < (int)uVar4) {
          plVar10 = *(long **)(param_1 + 0x18);
          uVar9 = (ulong)uVar4;
          do {
            plVar10 = plVar10 + 2;
            *(undefined4 *)(*plVar10 + (long)((int)uVar12 + param_3) * 4) = 0;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 != param_2);
    }
  }
  else {
    if (param_2 != 0) {
      uVar12 = 0;
      piVar1 = (int *)(param_1 + 0x34);
      do {
        iVar3 = *(int *)(param_1 + 0x20);
        uVar9 = (ulong)*(uint *)(param_1 + 8);
        if (0 < (int)*(uint *)(param_1 + 8)) {
          plVar10 = *(long **)(param_1 + 0x18);
          do {
            plVar10 = plVar10 + 2;
            *(undefined4 *)(*plVar10 + (long)((int)uVar12 + param_3) * 4) = 0;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
        }
        if (((0 < *(int *)(param_1 + 0x30)) && (*piVar1 != -1)) &&
           (*(int *)(param_1 + 0x34) < *(int *)(param_1 + 0x30))) {
          puVar2 = (undefined8 *)(*(long *)(param_1 + 0x28) + (long)*(int *)(param_1 + 0x34) * 0x20)
          ;
          if (*(char *)((long)puVar2 + 0x17) < '\0') {
            __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE25__init_copy_ctor_externalEPKcm
                      (&local_70,*puVar2,puVar2[1]);
          }
          else {
            uStack_68 = puVar2[1];
            local_70 = *puVar2;
            local_60 = puVar2[2];
          }
          local_58 = (double)puVar2[3];
          iVar8 = (int)(local_58 * *(double *)(param_1 + 0x10));
          if ((iVar8 <= iVar3 + (int)uVar12) && (*(int *)(param_1 + 0x3c) != iVar8)) {
            if (local_60 < 0) {
              __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE25__init_copy_ctor_externalEPKcm
                        (&local_90,local_70,uStack_68);
            }
            else {
              uStack_88 = uStack_68;
              local_90 = local_70;
              local_80 = local_60;
            }
            plVar10 = *(long **)(param_1 + 0x68);
            if (plVar10 == (long *)0x0) {
              __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
                    /* WARNING: Does not return */
              pcVar7 = (code *)SoftwareBreakpoint(1,0x5c0c);
              (*pcVar7)();
            }
            (**(code **)(*plVar10 + 0x30))(plVar10,&local_90);
            if (local_80 < 0) {
              __ZdlPv(local_90);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar6) {
                *piVar1 = *piVar1 + 1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
          }
          if (local_60 < 0) {
            __ZdlPv(local_70);
          }
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 != param_2);
    }
    piVar1 = (int *)(param_1 + 0x20);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = *piVar1 + param_2;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    if (*(int *)(param_1 + 0x3c) < *(int *)(param_1 + 0x20)) {
      iVar3 = *(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x3c);
      if ((*(int *)(param_1 + 0x40) == -1) || (*(int *)(param_1 + 0x44) == -1)) {
        iVar8 = *(int *)(param_1 + 0x38);
        *(int *)(param_1 + 0x20) = iVar8 + iVar3;
      }
      else {
        piVar1 = (int *)(param_1 + 0x40);
        *(int *)(param_1 + 0x20) = *piVar1 + iVar3;
        iVar8 = *piVar1;
        *(int *)(param_1 + 0x38) = iVar8;
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x44);
        *piVar1 = -1;
        *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
      }
      if (*(int *)(param_1 + 0x30) != 0) {
        uVar12 = 0;
        lVar11 = 0x18;
        do {
          if (iVar8 <= (int)(*(double *)(*(long *)(param_1 + 0x28) + lVar11) *
                            *(double *)(param_1 + 0x10))) goto LAB_00005be0;
          uVar12 = uVar12 + 1;
          lVar11 = lVar11 + 0x20;
        } while (uVar12 < *(uint *)(param_1 + 0x30));
      }
      uVar12 = 0xffffffff;
LAB_00005be0:
      *(int *)(param_1 + 0x34) = (int)uVar12;
    }
  }
  return;
}

// ==== 00005c44 __ZN19AutomationDSPKernel9startRampEyfj ====
void __ZN19AutomationDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00005c48 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00005c4c __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_00008178;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00005c80 __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 00005c84 __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 00005c98 __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE25__init_copy_ctor_externalEPKcm ====
void __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE25__init_copy_ctor_externalEPKcm
               (undefined8 *param_1,void *param_2,ulong param_3)

{
  ulong uVar1;
  undefined8 *puVar2;
  
  if (param_3 < 0x17) {
    *(char *)((long)param_1 + 0x17) = (char)param_3;
    puVar2 = param_1;
  }
  else {
    if (0x7ffffffffffffff7 < param_3) {
                    /* WARNING: Subroutine does not return */
      __ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE20__throw_length_errorB8ne190102Ev
                (param_1);
    }
    uVar1 = 0x19;
    if ((param_3 | 7) != 0x17) {
      uVar1 = (param_3 | 7) + 1;
    }
    puVar2 = (undefined8 *)__Znwm(uVar1);
    param_1[1] = param_3;
    param_1[2] = uVar1 | 0x8000000000000000;
    *param_1 = puVar2;
  }
  _memmove(puVar2,param_2,param_3 + 1);
  return;
}

// ==== 00005d1c __ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE20__throw_length_errorB8ne190102Ev
               (void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("basic_string");
}

// ==== 00005d30 __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_00008048,PTR___ZNSt12length_errorD1Ev_00008010);
}

// ==== 00005d80 __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_00008018 + 0x10);
  return;
}

// ==== 00005da4 __ZN19AutomationDSPKernel19clearAutomationCuesEv ====
void __ZN19AutomationDSPKernel19clearAutomationCuesEv(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  char *pcVar4;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    lVar1 = *(long *)(param_1 + 0x28);
    if (lVar1 != 0) {
      lVar2 = *(long *)(lVar1 + -8);
      if (lVar2 != 0) {
        lVar3 = lVar2 * -0x20;
        pcVar4 = (char *)(lVar1 + lVar2 * 0x20 + -9);
        do {
          if (*pcVar4 < '\0') {
            __ZdlPv(*(undefined8 *)(pcVar4 + -0x17));
          }
          lVar3 = lVar3 + 0x20;
          pcVar4 = pcVar4 + -0x20;
        } while (lVar3 != 0);
      }
      __ZdaPv(lVar1 + -0x10);
    }
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  return;
}

// ==== 00005e2c __ZNSt3__18functionIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEaSERKS8_ ====
undefined8
__ZNSt3__18functionIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEaSERKS8_
          (undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00008030;
  __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEC2B8ne190102ERKS9_
            (alStack_48);
  __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEE4swapB8ne190102ERS9_
            (alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00005e90;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00005e90:
  if (*(long *)PTR____stack_chk_guard_00008030 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00005ec0 __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEC2B8ne190102ERKS9_ ====
long __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEEC2B8ne190102ERKS9_
               (long param_1,long *param_2)

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

// ==== 00005f24 __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEE4swapB8ne190102ERS9_ ====
void __ZNSt3__110__function12__value_funcIFvNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEE4swapB8ne190102ERS9_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00008030;
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
  if (*(long *)PTR____stack_chk_guard_00008030 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00006090 __ZN19AutomationDSPKernel23prepareToPlayFromSampleEi ====
void __ZN19AutomationDSPKernel23prepareToPlayFromSampleEi(long param_1,int param_2)

{
  ulong uVar1;
  long lVar2;
  
  if (-1 < param_2) {
    *(int *)(param_1 + 0x20) = param_2;
    uVar1 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
    if (*(int *)(param_1 + 0x30) != 0) {
      uVar1 = 0;
      lVar2 = 0x18;
      do {
        if (*(int *)(param_1 + 0x20) <=
            (int)(*(double *)(*(long *)(param_1 + 0x28) + lVar2) * *(double *)(param_1 + 0x10)))
        goto LAB_00006100;
        uVar1 = uVar1 + 1;
        lVar2 = lVar2 + 0x20;
      } while (uVar1 < *(uint *)(param_1 + 0x30));
      uVar1 = 0xffffffff;
    }
LAB_00006100:
    *(int *)(param_1 + 0x34) = (int)uVar1;
  }
  return;
}

// ==== 0000610c __ZNSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEED1Ev ====
long __ZNSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 00006134 __ZNSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEED0Ev ====
void __ZNSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000615c __ZNKSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_000081a0;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 0000619c __ZNKSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7__cloneEPNS0_6__baseISA_EE ====
void __ZNKSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7__cloneEPNS0_6__baseISA_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_000081a0;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 000061b8 __ZNSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 000061c0 __ZNSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 000061e8 __ZNSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEEclEOS9_ ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEEclEOS9_
          (long param_1,undefined8 *param_2)

{
  undefined1 **ppuVar1;
  ID IVar2;
  ID self;
  undefined8 uVar3;
  undefined1 *local_50;
  undefined8 uStack_48;
  long local_40;
  
  local_40 = param_2[2];
  uStack_48 = param_2[1];
  local_50 = (undefined1 *)*param_2;
  param_2[1] = 0;
  param_2[2] = 0;
  *param_2 = 0;
  ppuVar1 = (undefined1 **)local_50;
  if (-1 < local_40) {
    ppuVar1 = &local_50;
  }
  IVar2 = NSString::stringWithUTF8String_((ID)&_OBJC_CLASS___NSString,ppuVar1);
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::automationAudioUnit_didTriggerAutomationCueWithUUID_
            (self,*(undefined8 *)(param_1 + 8),IVar2);
  uVar3 = 0;
  if (local_40 < 0) {
    uVar3 = __ZdlPv(local_50);
  }
  return uVar3;
}

// ==== 00006310 __ZNKSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000634c __ZNKSt3__110__function6__funcIZ69-[AutomationAudioUnit_configureDSPKernelWithAutomationCues:delegate:]E3$_0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0NS_9allocatorIS2_EEFvNS_12basic_stringIcNS_11char_traitsIcEENS3_IcEEEEEE11target_typeEv
          (void)

{
  return &__ZTIZ69__AutomationAudioUnit_configureDSPKernelWithAutomationCues_delegate__E3__0;
}

// ==== 00006358 __ZNKSt9type_infoeqB8ne190102ERKS_ ====
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

// ==== 000063a4 AutomationAudioUnitCue::initWithUUID:timecode: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

ID AutomationAudioUnitCue::initWithUUID_timecode_(ID param_1,SEL param_2,ID param_3,double param_4)

{
  ID self;
  ID local_40;
  class_t *pcStack_38;
  
  pcStack_38 = &objc::class_t::AutomationAudioUnitCue;
  local_40 = param_1;
  self = NSObject::init((ID)&local_40,"init");
  if (self != 0) {
    NSObject::setUuid_(self,param_3);
    NSObject::setTimecode_(self,param_4);
  }
  return self;
}

// ==== 00006428 AutomationAudioUnitCue::uuid ====
/* Function Stack Size: 0x10 bytes */

ID AutomationAudioUnitCue::uuid(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + 8);
}

// ==== 00006430 AutomationAudioUnitCue::setUuid: ====
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnitCue::setUuid_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + 8) = param_3;
  return;
}

// ==== 00006438 AutomationAudioUnitCue::timecode ====
/* Function Stack Size: 0x10 bytes */

double AutomationAudioUnitCue::timecode(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + 0x10);
}

// ==== 00006440 AutomationAudioUnitCue::setTimecode: ====
/* Function Stack Size: 0x18 bytes */

void AutomationAudioUnitCue::setTimecode_(ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + 0x10) = param_3;
  return;
}

// ==== 00006448 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00006450. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_000089a8)(param_1,param_2,param_3);
  return;
}

// ==== 00006454 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0000645c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_000089b0)(param_1,param_2);
  return;
}

// ==== 00006460 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00006468. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_000089b8)();
  return;
}

// ==== 0000646c __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006474. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_000089c0)();
  return;
}

// ==== 00006478 __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEPKc ====
void __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEPKc_000089c8
  )();
  return;
}

// ==== 00006484 __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000648c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_000089d0)();
  return;
}

// ==== 00006490 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006498. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_000089d8)();
  return;
}

// ==== 0000649c __ZdaPv ====
void __ZdaPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdaPv_00008050)();
  return;
}

// ==== 000064a8 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008058)();
  return;
}

// ==== 000064b4 __Znam ====
void __Znam(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znam_00008060)();
  return;
}

// ==== 000064c0 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008068)();
  return;
}

// ==== 000064cc ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_000089e0)();
  return;
}

// ==== 000064d8 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_000089e8)();
  return;
}

// ==== 000064e4 ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_000089f0)();
  return;
}

// ==== 000064f0 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_000089f8)();
  return;
}

// ==== 000064fc ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006504. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00008a00)();
  return;
}

// ==== 00006508 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00006510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00008a08)();
  return;
}

// ==== 00006514 _memmove ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memmove(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000651c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memmove_00008a10)();
  return pvVar1;
}

// ==== 00006520 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_00008a18)();
  return;
}

// ==== 0000652c _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006534. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_00008a20)();
  return;
}

// ==== 00006538 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006540. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00008a28)();
  return;
}

// ==== 00006544 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000654c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00008a30)();
  return;
}

// ==== 00006550 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006558. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008a38)();
  return;
}

// ==== 0000655c _objc_enumerationMutation ====
void _objc_enumerationMutation(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006564. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_enumerationMutation_00008a40)();
  return;
}

// ==== 00006568 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006570. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008a48)();
  return;
}

// ==== 00006574 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000657c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008a50)();
  return;
}

// ==== 00006580 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006588. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008a58)();
  return;
}

// ==== 0000658c _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006594. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_00008a60)();
  return;
}

// ==== 00006598 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000065a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008a68)();
  return IVar1;
}

// ==== 000065a4 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008a70)();
  return;
}

// ==== 000065b0 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008a78)();
  return;
}

// ==== 000065bc _objc_retainAutorelease ====
void _objc_retainAutorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutorelease_00008a80)();
  return;
}

// ==== 000065c8 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00008a88)();
  return;
}

// ==== 000065d4 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00008a90)();
  return;
}

// ==== 000065e0 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00008a98)();
  return;
}

// ==== 000065ec _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00008aa0)();
  return;
}

// ==== 000065f8 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006600. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00008aa8)();
  return;
}

// ==== 00006604 _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000660c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_00008ab0)();
  return;
}

// ==== 00006610 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_00008ab8)((int)param_1);
  return iVar1;
}

// ==== 000067e0 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"address");
  return IVar1;
}

// ==== 00006800 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00006820 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00006840 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00006860 objc_stub::automationAudioUnit:didTriggerAutomationCueWithUUID: ====
ID __objc_msgSend_stub objc_stub::automationAudioUnit_didTriggerAutomationCueWithUUID_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)
                    (self,"automationAudioUnit:didTriggerAutomationCueWithUUID:");
  return IVar1;
}

// ==== 00006880 objc_stub::automationDSPCuesForAutomationCues: ====
ID __objc_msgSend_stub objc_stub::automationDSPCuesForAutomationCues_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"automationDSPCuesForAutomationCues:");
  return IVar1;
}

// ==== 000068a0 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"busType");
  return IVar1;
}

// ==== 000068c0 objc_stub::cStringUsingEncoding: ====
ID __objc_msgSend_stub objc_stub::cStringUsingEncoding_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"cStringUsingEncoding:");
  return IVar1;
}

// ==== 000068e0 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"channelCount");
  return IVar1;
}

// ==== 00006900 objc_stub::count ====
ID __objc_msgSend_stub objc_stub::count(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"count");
  return IVar1;
}

// ==== 00006920 objc_stub::countByEnumeratingWithState:objects:count: ====
ID __objc_msgSend_stub objc_stub::countByEnumeratingWithState_objects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"countByEnumeratingWithState:objects:count:");
  return IVar1;
}

// ==== 00006940 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
ID __objc_msgSend_stub
objc_stub::
createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
          (ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)
                    (self,
                     "createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters:"
                    );
  return IVar1;
}

// ==== 00006960 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00006980 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"defaultFormat");
  return IVar1;
}

// ==== 000069a0 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"delegate");
  return IVar1;
}

// ==== 000069c0 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 000069e0 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 00006a00 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"format");
  return IVar1;
}

// ==== 00006a20 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00006a40 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00006a60 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00006a80 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00006aa0 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00006ac0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00006ae0 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"raise");
  return IVar1;
}

// ==== 00006b00 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"reset");
  return IVar1;
}

// ==== 00006b20 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"sampleRate");
  return IVar1;
}

// ==== 00006b40 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00006b60 objc_stub::setDelegate: ====
ID __objc_msgSend_stub objc_stub::setDelegate_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDelegate:");
  return IVar1;
}

// ==== 00006b80 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00006ba0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00006bc0 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00006be0 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00006c00 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00006c20 objc_stub::setTimecode: ====
ID __objc_msgSend_stub objc_stub::setTimecode_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setTimecode:");
  return IVar1;
}

// ==== 00006c40 objc_stub::setUuid: ====
ID __objc_msgSend_stub objc_stub::setUuid_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setUuid:");
  return IVar1;
}

// ==== 00006c60 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setValue:");
  return IVar1;
}

// ==== 00006c80 objc_stub::stringWithUTF8String: ====
ID __objc_msgSend_stub objc_stub::stringWithUTF8String_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"stringWithUTF8String:");
  return IVar1;
}

// ==== 00006ca0 objc_stub::timecode ====
ID __objc_msgSend_stub objc_stub::timecode(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"timecode");
  return IVar1;
}

// ==== 00006cc0 objc_stub::updateAutomationCuesWithCues: ====
ID __objc_msgSend_stub objc_stub::updateAutomationCuesWithCues_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"updateAutomationCuesWithCues:");
  return IVar1;
}

// ==== 00006ce0 objc_stub::uuid ====
ID __objc_msgSend_stub objc_stub::uuid(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"uuid");
  return IVar1;
}

// ==== 00018201 AUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018202 AUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018203 AUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018204 AUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018205 AUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018206 AUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018207 AUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018208 AUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018301 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018401 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018501 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018502 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018503 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018601 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018701 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018801 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018901 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018a01 NSException::exceptionWithName:reason:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::exceptionWithName_reason_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018a02 NSException::raise ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::raise(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018b01 NSObject::init ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::init(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018b02 NSObject::setUuid: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setUuid_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018b03 NSObject::setTimecode: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setTimecode_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018c01 NSString::stringWithUTF8String: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithUTF8String_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00019b00 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

