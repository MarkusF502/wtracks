// MIDIOutAUFramework sha256 a76d7007c4f1a53d5c687a094311ec1274e6e3ce9f10e8b4a28c670f9ff3101f (Ghidra 12.1.4, all decompiled functions)

// ==== 00004000 MIDIOutAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID MIDIOutAudioUnit::initWithComponentDescription_options_error_
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
  ID self_04;
  ID self_05;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined *local_150;
  undefined8 local_148;
  code *local_140;
  undefined *puStack_138;
  undefined8 *local_130;
  undefined *local_128;
  undefined8 local_120;
  code *local_118;
  undefined *puStack_110;
  undefined8 *local_108;
  undefined8 local_100;
  undefined8 *puStack_f8;
  undefined8 local_f0;
  undefined8 *local_e8;
  ID local_d8;
  class_t *pcStack_d0;
  ID local_c8;
  ID IStack_c0;
  ID local_b8;
  ID IStack_b0;
  ID local_a8;
  ID IStack_a0;
  ID local_98;
  ID IStack_90;
  undefined8 local_88;
  long local_80;
  
  local_80 = *(long *)PTR____stack_chk_guard_00008018;
  puStack_f8 = *(undefined8 **)&param_3->field2_0x8;
  local_100._0_4_ = param_3->field0_0x0;
  local_100._4_4_ = param_3->field1_0x4;
  local_f0 = CONCAT44(local_f0._4_4_,param_3->field4_0x10);
  pcStack_d0 = &objc::class_t::MIDIOutAudioUnit;
  local_d8 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_d8,"initWithComponentDescription:options:error:",&local_100,
                    (ulong)param_4);
  if (self != 0) {
    *(undefined8 *)(self + (long)_midiOutEventTimes) = 0;
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
    TrackedAUAudioUnit::setMaximumFramesToRender_(self,uVar4,0x200);
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_enabledParameter,
                       &cf_enabled,0,2,0,0,0,0);
    IVar3 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isPlayingParameter,
                       &cf_isPlaying,1,2,0,0,0,0,IVar2);
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
    self_04 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,
                         &cf_prerollOffsetTimeParameter,&cf_prerollOffsetTime,6,4,0,0,0,0);
    self_05 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,&cf_rewindTimeParameter,
                         &cf_rewindTime,7,4,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0x7f7fffff);
    AUParameterTree::setValue_(self_02,0xbf800000);
    AUParameterTree::setValue_(self_03,0xbf800000);
    AUParameterTree::setValue_(self_04,0);
    AUParameterTree::setValue_(self_05,0);
    local_c8 = IVar2;
    IStack_c0 = IVar3;
    local_b8 = self_00;
    IStack_b0 = self_01;
    local_a8 = self_02;
    IStack_a0 = self_03;
    local_98 = self_04;
    IStack_90 = self_05;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_c8,8);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar5 = (long)_parameterTree;
    *(ID *)(self + lVar5) = IVar2;
    lVar6 = (long)_dspKernel;
    local_e8 = *(undefined8 **)(self + lVar6);
    if (local_e8 == (undefined8 *)0x0) {
      local_e8 = (undefined8 *)__Znwm(0x68);
      *local_e8 = &DAT_00008158;
      *(undefined4 *)(local_e8 + 1) = 0x472c4400;
      local_e8[2] = 0;
      local_e8[3] = 0;
      *(undefined4 *)(local_e8 + 4) = 0;
      *(undefined8 *)((long)local_e8 + 0x2c) = 0xffffffff7fffffff;
      *(undefined8 *)((long)local_e8 + 0x24) = 0xffffffff;
      *(undefined4 *)((long)local_e8 + 0x34) = 0xffffffff;
      local_e8[0xc] = 0;
      local_e8[7] = 0;
      local_e8[8] = 0;
      *(undefined8 **)(self + lVar6) = local_e8;
    }
    puVar1 = PTR___NSConcreteStackBlock_00008010;
    local_100 = 0;
    local_f0 = 0x2020000000;
    local_128 = PTR___NSConcreteStackBlock_00008010;
    local_120 = 0xc2000000;
    local_118 = ___63__MIDIOutAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_110 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_108 = &local_100;
    puStack_f8 = &local_100;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar5),&local_128);
    local_150 = puVar1;
    local_148 = 0xc2000000;
    local_140 = ___63__MIDIOutAudioUnit_initWithComponentDescription_options_error___block_invoke_36
    ;
    puStack_138 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_130 = &local_100;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar5),&local_150);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar5),&___block_literal_global);
    __Block_object_dispose(&local_100,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008018 == local_80) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004758 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 000047ec ___63-[MIDIOutAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___63__MIDIOutAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN16MIDIOutDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return;
}

// ==== 00004830 __ZN16MIDIOutDSPKernel12setParameterEyf ====
void __ZN16MIDIOutDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  int iVar1;
  
  if (param_3 < 4) {
    if (param_3 < 2) {
      if (param_3 == 0) {
        *(bool *)(param_2 + 0x44) = param_1 != 0.0;
        return;
      }
      if ((param_3 == 1) &&
         (*(byte *)(param_2 + 0x45) = param_1 != 0.0, (*(byte *)(param_2 + 0x45) & 1) == 0)) {
        *(undefined1 *)(param_2 + 0x46) = 0;
        return;
      }
    }
    else {
      if (param_3 == 2) {
        *(int *)(param_2 + 0x28) = (int)(*(float *)(param_2 + 8) * param_1);
        return;
      }
      if (param_3 == 3) {
        *(int *)(param_2 + 0x2c) = (int)(*(float *)(param_2 + 8) * param_1);
        return;
      }
    }
  }
  else if (param_3 < 6) {
    if (param_3 == 4) {
      if (param_1 == -1.0) {
        *(undefined4 *)(param_2 + 0x30) = 0xffffffff;
        return;
      }
      *(int *)(param_2 + 0x30) = (int)(*(float *)(param_2 + 8) * param_1);
      return;
    }
    if (param_3 == 5) {
      if (param_1 == -1.0) {
        iVar1 = -1;
      }
      else {
        iVar1 = (int)(*(float *)(param_2 + 8) * param_1);
      }
      *(int *)(param_2 + 0x34) = iVar1;
      return;
    }
  }
  else if (param_3 == 6) {
    *(int *)(param_2 + 0x38) = (int)(*(float *)(param_2 + 8) * param_1);
  }
  else if (param_3 == 7) {
    *(int *)(param_2 + 0x3c) = (int)(*(float *)(param_2 + 8) * param_1);
    return;
  }
  return;
}

// ==== 00004960 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004970 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 0000497c ___63-[MIDIOutAudioUnit_initWithComponentDescription:options:error:]_block_invoke.36 ====
undefined1  [16]
___63__MIDIOutAudioUnit_initWithComponentDescription_options_error___block_invoke_36
          (undefined8 param_1,ID param_2)

{
  objc_stub::address(param_2);
  return ZEXT816(0);
}

// ==== 00004998 ___63-[MIDIOutAudioUnit_initWithComponentDescription:options:error:]_block_invoke.38 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___63__MIDIOutAudioUnit_initWithComponentDescription_options_error___block_invoke_38
          (undefined8 param_1,ID param_2,float *param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  cfstringStruct *pcVar3;
  float extraout_s0;
  float fVar4;
  
  if (param_3 == (float *)0x0) {
    objc_stub::value(param_2);
    fVar4 = extraout_s0;
  }
  else {
    fVar4 = *param_3;
  }
  IVar1 = objc_stub::address(param_2);
  if (IVar1 - 2 < 6) {
    pcVar2 = (cfstringStruct *)
             NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__fseconds);
  }
  else {
    if (IVar1 == 0) {
      pcVar3 = &cf_Disabled;
      pcVar2 = &cf_Enabled;
    }
    else {
      if (IVar1 != 1) {
        return &cf__;
      }
      pcVar3 = &cf_Stopped;
      pcVar2 = &cf_Playing;
    }
    if (fVar4 == 0.0) {
      pcVar2 = pcVar3;
    }
  }
  return pcVar2;
}

// ==== 00004a90 MIDIOutAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::reset(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::MIDIOutAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined1 *)(lVar1 + 0x46) = 0;
  *(undefined1 *)(lVar1 + 0x45) = 0;
  return;
}

// ==== 00004ae8 MIDIOutAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  ID local_40;
  class_t *pcStack_38;
  
  clearCVariables(param_1);
  lVar4 = (long)_dspKernel;
  *(undefined8 *)(*(long *)(param_1 + lVar4) + 0x10) = 0;
  puVar3 = *(undefined8 **)(param_1 + lVar4);
  if (puVar3 == (undefined8 *)0x0) goto LAB_00004b64;
  *puVar3 = &DAT_00008158;
  puVar3[2] = 0;
  plVar1 = (long *)puVar3[0xc];
  if (plVar1 == puVar3 + 9) {
    lVar2 = 0x20;
LAB_00004b50:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004b50;
  }
  __ZdlPv(puVar3);
LAB_00004b64:
  *(undefined8 *)(param_1 + lVar4) = 0;
  pcStack_38 = &objc::class_t::MIDIOutAudioUnit;
  local_40 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_40,"dealloc");
  return;
}

// ==== 00004bc4 ___clang_call_terminate ====
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
  lStack_48 = *(long *)PTR____stack_chk_guard_00008018;
  MIDIOutAudioUnit::setEventTimes_(IVar1,auVar4._8_8_,param_3);
  MIDIOutAudioUnit::setDelegate_(IVar1,extraout_x1,param_4);
  _objc_initWeak(auStack_70,IVar1);
  IVar2 = MIDIOutAudioUnit::delegate(IVar1,extraout_x1_00);
  if (IVar2 != 0) {
    lVar3 = *(long *)(IVar1 + (long)MIDIOutAudioUnit::_dspKernel);
    _objc_copyWeak(auStack_78,auStack_70);
    ppuStack_50 = (undefined **)0x0;
    puStack_68 = &DAT_000081e8;
    _objc_moveWeak(auStack_60,auStack_78);
    ppuStack_50 = &puStack_68;
    _objc_destroyWeak(auStack_78);
    __ZNSt3__18functionIFvibbEEaSERKS2_(lVar3 + 0x48,&puStack_68);
    if (ppuStack_50 == &puStack_68) {
      lVar3 = 0x20;
    }
    else {
      if (ppuStack_50 == (undefined **)0x0) goto LAB_00004cd8;
      lVar3 = 0x28;
    }
    (**(code **)(*ppuStack_50 + lVar3))();
  }
LAB_00004cd8:
  _objc_destroyWeak(auStack_70);
  if (*(long *)PTR____stack_chk_guard_00008018 == lStack_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004bd4 MIDIOutAudioUnit::configureDSPKernelWithEventTimes:delegate: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void MIDIOutAudioUnit::configureDSPKernelWithEventTimes_delegate_
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
  
  local_38 = *(long *)PTR____stack_chk_guard_00008018;
  setEventTimes_(param_1,param_3);
  setDelegate_(param_1,param_4);
  _objc_initWeak(auStack_60,param_1);
  IVar1 = delegate(param_1);
  if (IVar1 != 0) {
    lVar2 = *(long *)(param_1 + (long)_dspKernel);
    _objc_copyWeak(auStack_68,auStack_60);
    local_40 = (undefined **)0x0;
    local_58 = &DAT_000081e8;
    _objc_moveWeak(auStack_50,auStack_68);
    local_40 = &local_58;
    _objc_destroyWeak(auStack_68);
    __ZNSt3__18functionIFvibbEEaSERKS2_(lVar2 + 0x48,&local_58);
    if (local_40 == &local_58) {
      lVar2 = 0x20;
    }
    else {
      if (local_40 == (undefined **)0x0) goto LAB_00004cd8;
      lVar2 = 0x28;
    }
    (**(code **)(*local_40 + lVar2))();
  }
LAB_00004cd8:
  _objc_destroyWeak(auStack_60);
  if (*(long *)PTR____stack_chk_guard_00008018 == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004d84 MIDIOutAudioUnit::updateEventTimes: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::updateEventTimes_(ID param_1,SEL param_2,ID param_3)

{
  ID IVar1;
  void *pvVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  undefined *local_68;
  undefined8 local_60;
  code *local_58;
  undefined *puStack_50;
  ID local_48;
  
  setEventTimes_(param_1,param_3);
  clearCVariables(param_1);
  IVar1 = eventTimes(param_1);
  IVar1 = objc_stub::count(IVar1);
  pvVar2 = _malloc(IVar1 << 3);
  lVar3 = (long)_midiOutEventTimes;
  *(void **)(param_1 + lVar3) = pvVar2;
  IVar1 = eventTimes(param_1);
  local_68 = PTR___NSConcreteStackBlock_00008010;
  local_60 = 0xc2000000;
  local_58 = ___37__MIDIOutAudioUnit_updateEventTimes___block_invoke;
  puStack_50 = &___block_descriptor_40_ea8_32s_e25_v32__0__NSNumber_8Q16_B24l;
  local_48 = param_1;
  objc_stub::enumerateObjectsUsingBlock_(IVar1,&local_68);
  lVar5 = *(long *)(param_1 + (long)_dspKernel);
  uVar4 = *(undefined8 *)(param_1 + lVar3);
  IVar1 = eventTimes(param_1);
  IVar1 = objc_stub::count(IVar1);
  *(undefined8 *)(lVar5 + 0x18) = uVar4;
  *(int *)(lVar5 + 0x20) = (int)IVar1;
  return;
}

// ==== 00004ecc ___37-[MIDIOutAudioUnit_updateEventTimes:]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___37__MIDIOutAudioUnit_updateEventTimes___block_invoke(long param_1,ID param_2,long param_3)

{
  undefined8 extraout_d0;
  
  objc_stub::doubleValue(param_2);
  *(undefined8 *)
   (*(long *)(*(long *)(param_1 + 0x20) + (long)MIDIOutAudioUnit::_midiOutEventTimes) + param_3 * 8)
       = extraout_d0;
  return 0;
}

// ==== 00004f30 ___copy_helper_block_ea8_32s ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 ___copy_helper_block_ea8_32s(undefined8 param_1,long param_2)

{
  return *(undefined8 *)(param_2 + 0x20);
}

// ==== 00004f38 ___destroy_helper_block_ea8_32s ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 ___destroy_helper_block_ea8_32s(void)

{
  return 0;
}

// ==== 00004f40 MIDIOutAudioUnit::updateEventTimeIndex ====
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::updateEventTimeIndex(ID param_1,SEL param_2)

{
  long lVar1;
  ulong uVar2;
  
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  if (*(uint *)(lVar1 + 0x20) != 0) {
    uVar2 = 0;
    do {
      if (*(int *)(lVar1 + 0x40) <=
          (int)(*(double *)(*(long *)(lVar1 + 0x18) + uVar2 * 8) * (double)*(float *)(lVar1 + 8)))
      goto LAB_00004f90;
      uVar2 = uVar2 + 1;
    } while (*(uint *)(lVar1 + 0x20) != uVar2);
  }
  uVar2 = 0xffffffff;
LAB_00004f90:
  *(int *)(lVar1 + 0x24) = (int)uVar2;
  return;
}

// ==== 00004f98 MIDIOutAudioUnit::clearCVariables ====
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::clearCVariables(ID param_1,SEL param_2)

{
  long lVar1;
  
  lVar1 = (long)_midiOutEventTimes;
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZdaPv();
    *(undefined8 *)(param_1 + lVar1) = 0;
  }
  return;
}

// ==== 00004fcc MIDIOutAudioUnit::prepareToPlayFromPlayheadPosition: ====
/* Function Stack Size: 0x14 bytes */

void MIDIOutAudioUnit::prepareToPlayFromPlayheadPosition_(ID param_1,SEL param_2,int param_3)

{
  __ZN16MIDIOutDSPKernel13prepareToPlayEi(*(undefined8 *)(param_1 + (long)_dspKernel),param_3);
  return;
}

// ==== 00004fe0 __ZN16MIDIOutDSPKernel13prepareToPlayEi ====
void __ZN16MIDIOutDSPKernel13prepareToPlayEi(long param_1,int param_2)

{
  ulong uVar1;
  
  if (-1 < param_2) {
    *(int *)(param_1 + 0x40) = param_2;
    uVar1 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x30) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
    if (*(uint *)(param_1 + 0x20) != 0) {
      uVar1 = 0;
      do {
        if (*(int *)(param_1 + 0x40) <=
            (int)(*(double *)(*(long *)(param_1 + 0x18) + uVar1 * 8) *
                 (double)*(float *)(param_1 + 8))) goto LAB_0000503c;
        uVar1 = uVar1 + 1;
      } while (*(uint *)(param_1 + 0x20) != uVar1);
      uVar1 = 0xffffffff;
    }
LAB_0000503c:
    *(int *)(param_1 + 0x24) = (int)uVar1;
  }
  return;
}

// ==== 00005044 MIDIOutAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x14 bytes */

void MIDIOutAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,float param_3)

{
  __ZN16MIDIOutDSPKernel13prepareToPlayEi
            (*(long *)(param_1 + (long)_dspKernel),
             (int)(*(float *)(*(long *)(param_1 + (long)_dspKernel) + 8) * param_3));
  return;
}

// ==== 00005060 MIDIOutAudioUnit::mtDSPKernelAsVoid ====
/* Function Stack Size: 0x10 bytes */

void * MIDIOutAudioUnit::mtDSPKernelAsVoid(ID param_1,SEL param_2)

{
  return (void *)(param_1 + (long)_dspKernel);
}

// ==== 00005070 MIDIOutAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005080 MIDIOutAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

bool MIDIOutAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  ID IVar1;
  ID IVar2;
  void *pvVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  double extraout_d0;
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  ID local_68;
  ID local_60;
  class_t *pcStack_58;
  
  pcStack_58 = &objc::class_t::MIDIOutAudioUnit;
  local_60 = param_1;
  IVar1 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_60,"allocateRenderResourcesAndReturnError:");
  if ((bool)IVar1 != 0) {
    lVar4 = (long)_bufferedOutputBus;
    IVar2 = objc_stub::maximumFramesToRender(param_1);
    __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar4,IVar2);
    clearCVariables(param_1);
    IVar2 = eventTimes(param_1);
    IVar2 = objc_stub::count(IVar2);
    pvVar3 = _malloc(IVar2 << 3);
    lVar5 = (long)_midiOutEventTimes;
    *(void **)(param_1 + lVar5) = pvVar3;
    IVar2 = eventTimes(param_1);
    local_88 = PTR___NSConcreteStackBlock_00008010;
    local_80 = 0xc2000000;
    local_78 = ___58__MIDIOutAudioUnit_allocateRenderResourcesAndReturnError___block_invoke;
    puStack_70 = &___block_descriptor_40_ea8_32s_e25_v32__0__NSNumber_8Q16_B24l;
    local_68 = param_1;
    objc_stub::enumerateObjectsUsingBlock_(IVar2,&local_88);
    lVar7 = *(long *)(param_1 + (long)_dspKernel);
    IVar2 = objc_stub::format(*(ID *)(param_1 + lVar4));
    objc_stub::sampleRate(IVar2);
    uVar6 = *(undefined8 *)(param_1 + lVar5);
    IVar2 = eventTimes(param_1);
    IVar2 = objc_stub::count(IVar2);
    *(float *)(lVar7 + 8) = (float)extraout_d0;
    *(undefined8 *)(lVar7 + 0x18) = uVar6;
    *(int *)(lVar7 + 0x20) = (int)IVar2;
    *(undefined4 *)(lVar7 + 0x24) = 0xffffffff;
    reset(param_1);
  }
  return (bool)IVar1;
}

// ==== 00005234 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 000052d4 ___58-[MIDIOutAudioUnit_allocateRenderResourcesAndReturnError:]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___58__MIDIOutAudioUnit_allocateRenderResourcesAndReturnError___block_invoke
          (long param_1,ID param_2,long param_3)

{
  undefined8 extraout_d0;
  
  objc_stub::doubleValue(param_2);
  *(undefined8 *)
   (*(long *)(*(long *)(param_1 + 0x20) + (long)MIDIOutAudioUnit::_midiOutEventTimes) + param_3 * 8)
       = extraout_d0;
  return 0;
}

// ==== 00005338 MIDIOutAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  *(undefined8 *)(*(long *)(param_1 + (long)_dspKernel) + 0x10) = 0;
  clearCVariables(param_1);
  pcStack_28 = &objc::class_t::MIDIOutAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 000053ac MIDIOutAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool MIDIOutAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  long lVar5;
  long local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008018;
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
                         *(undefined8 *)PTR__NSInternalInconsistencyException_00008028,
                         &cf_Cannotinitoutputbuswithnewformat,0);
      NSException::raise(IVar3);
    }
  }
  else {
    IVar3 = NSException::exceptionWithName_reason_userInfo_
                      ((ID)&_OBJC_CLASS___NSException,
                       *(undefined8 *)PTR__NSInternalInconsistencyException_00008028,
                       &cf_Unrecognisedbustype,0);
    NSException::raise(IVar3);
  }
  if (*(long *)PTR____stack_chk_guard_00008018 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return (bool)(IVar2 == 2);
}

// ==== 00005618 MIDIOutAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_00008010;
  local_80 = 0xc2000000;
  local_78 = ___39__MIDIOutAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 000056e0 ___39-[MIDIOutAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___39__MIDIOutAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)MIDIOutAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x10) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005788 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00005820 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005858 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005884 MIDIOutAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool MIDIOutAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 0000588c MIDIOutAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 0000589c MIDIOutAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000058b0 MIDIOutAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 000058d0 MIDIOutAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 000058e4 MIDIOutAudioUnit::eventTimes ====
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::eventTimes(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_eventTimes);
}

// ==== 000058f4 MIDIOutAudioUnit::setEventTimes: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setEventTimes_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_eventTimes) = param_3;
  return;
}

// ==== 00005908 MIDIOutAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005918 MIDIOutAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 0000592c MIDIOutAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 0000593c MIDIOutAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005948 MIDIOutAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005958 MIDIOutAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIOutAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00005964 MIDIOutAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MIDIOutAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_eventTimes) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005a0c MIDIOutAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID MIDIOutAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00005a2c __ZN16MIDIOutDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN16MIDIOutDSPKernel7processEjjPK14AudioTimeStamp(long param_1,uint param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  ulong uVar8;
  int iVar9;
  uint *puVar10;
  long *plVar11;
  uint *puVar12;
  ulong uVar13;
  
  puVar10 = *(uint **)(param_1 + 0x10);
  uVar4 = *puVar10;
  if ((*(byte *)(param_1 + 0x45) & 1) == 0) {
    if (param_2 != 0) {
      uVar13 = 0;
      do {
        if (0 < (int)uVar4) {
          uVar8 = (ulong)uVar4;
          puVar12 = puVar10;
          do {
            puVar12 = puVar12 + 4;
            *(undefined4 *)(*(long *)puVar12 + (long)((int)uVar13 + param_3) * 4) = 0;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
        }
        uVar13 = uVar13 + 1;
      } while (uVar13 != param_2);
    }
  }
  else {
    if (param_2 != 0) {
      uVar13 = 0;
      do {
        iVar3 = *(int *)(param_1 + 0x40);
        if (0 < (int)uVar4) {
          plVar11 = *(long **)(param_1 + 0x10);
          uVar8 = (ulong)uVar4;
          do {
            plVar11 = plVar11 + 2;
            *(undefined4 *)(*plVar11 + (long)((int)uVar13 + param_3) * 4) = 0;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
        }
        if ((*(uint *)(param_1 + 0x20) != 0) &&
           (*(uint *)(param_1 + 0x24) < *(uint *)(param_1 + 0x20))) {
          if ((*(int *)(param_1 + 0x30) == -1) ||
             ((*(int *)(param_1 + 0x30) == *(int *)(param_1 + 0x2c) ||
              (*(int *)(param_1 + 0x40) < *(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x38))))) {
            iVar9 = 0;
          }
          else {
            iVar9 = 0x6e4;
            if (*(int *)(param_1 + 0x2c) <= *(int *)(param_1 + 0x40)) {
              iVar9 = 0;
            }
          }
          uVar8 = (ulong)*(int *)(param_1 + 0x24);
          iVar9 = iVar9 + (int)(*(double *)(*(long *)(param_1 + 0x18) + uVar8 * 8) *
                               (double)*(float *)(param_1 + 8));
          while (iVar7 = (int)uVar8, iVar9 == iVar3 + (int)uVar13) {
            if (*(char *)(param_1 + 0x44) == '\x01') {
              __ZNKSt3__18functionIFvibbEEclEibb
                        (param_1 + 0x48,*(undefined4 *)(param_1 + 0x24),
                         *(undefined1 *)(param_1 + 0x47),
                         *(int *)(param_1 + 0x40) < *(int *)(param_1 + 0x3c));
              iVar7 = *(int *)(param_1 + 0x24);
            }
            uVar1 = iVar7 + 1;
            uVar8 = (ulong)uVar1;
            *(uint *)(param_1 + 0x24) = uVar1;
            if (uVar1 < *(uint *)(param_1 + 0x20)) {
              iVar9 = (int)(*(double *)(*(long *)(param_1 + 0x18) + (long)(int)uVar1 * 8) *
                           (double)*(float *)(param_1 + 8));
            }
            else {
              iVar9 = -1;
            }
          }
        }
        uVar13 = uVar13 + 1;
      } while (uVar13 != param_2);
    }
    piVar2 = (int *)(param_1 + 0x40);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + param_2;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    if ((((*(int *)(param_1 + 0x30) != -1) && (*(int *)(param_1 + 0x30) != *(int *)(param_1 + 0x2c))
         ) && (*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x38) <= *(int *)(param_1 + 0x40))) &&
       (*(int *)(param_1 + 0x40) < *(int *)(param_1 + 0x2c))) {
      piVar2 = (int *)(param_1 + 0x40);
      *piVar2 = ((*piVar2 - *(int *)(param_1 + 0x2c)) +
                *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x30)) - *(int *)(param_1 + 0x38);
      *(int *)(param_1 + 0x28) = *piVar2;
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x30);
      if (*(uint *)(param_1 + 0x20) != 0) {
        uVar13 = 0;
        do {
          if (*piVar2 <=
              (int)(*(double *)(*(long *)(param_1 + 0x18) + uVar13 * 8) *
                   (double)*(float *)(param_1 + 8))) goto LAB_00005cd4;
          uVar13 = uVar13 + 1;
        } while (*(uint *)(param_1 + 0x20) != uVar13);
      }
      uVar13 = 0xffffffff;
LAB_00005cd4:
      *(int *)(param_1 + 0x24) = (int)uVar13;
      *(undefined1 *)(param_1 + 0x47) = 1;
    }
    if (*(int *)(param_1 + 0x2c) < *(int *)(param_1 + 0x40)) {
      iVar3 = *(int *)(param_1 + 0x40) - *(int *)(param_1 + 0x2c);
      if ((*(int *)(param_1 + 0x30) == -1) || (*(int *)(param_1 + 0x34) == -1)) {
        *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x28) + iVar3;
      }
      else {
        piVar2 = (int *)(param_1 + 0x30);
        *(int *)(param_1 + 0x40) = *piVar2 + iVar3;
        *(int *)(param_1 + 0x28) = *piVar2;
        *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x34);
        *piVar2 = -1;
        *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
        *(undefined1 *)(param_1 + 0x47) = 0;
      }
      if (*(uint *)(param_1 + 0x20) != 0) {
        uVar13 = 0;
        do {
          if (*(int *)(param_1 + 0x40) <=
              (int)(*(double *)(*(long *)(param_1 + 0x18) + uVar13 * 8) *
                   (double)*(float *)(param_1 + 8))) goto LAB_00005da4;
          uVar13 = uVar13 + 1;
        } while (*(uint *)(param_1 + 0x20) != uVar13);
      }
      uVar13 = 0xffffffff;
LAB_00005da4:
      *(int *)(param_1 + 0x24) = (int)uVar13;
    }
  }
  return;
}

// ==== 00005dc0 __ZN16MIDIOutDSPKernel9startRampEyfj ====
void __ZN16MIDIOutDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00005dc4 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00005dc8 __ZNKSt3__18functionIFvibbEEclEibb ====
void __ZNKSt3__18functionIFvibbEEclEibb
               (long param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  long *plVar1;
  undefined1 local_16;
  undefined1 local_15;
  undefined4 local_14;
  
  plVar1 = *(long **)(param_1 + 0x18);
  local_16 = param_4;
  local_15 = param_3;
  local_14 = param_2;
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x30))(plVar1,&local_14,&local_15,&local_16);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
}

// ==== 00005e10 __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_000081c0;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00005e44 __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 00005e48 __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 00005e5c __ZNSt3__18functionIFvibbEEaSERKS2_ ====
undefined8 __ZNSt3__18functionIFvibbEEaSERKS2_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00008018;
  __ZNSt3__110__function12__value_funcIFvibbEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvibbEE4swapB8ne190102ERS3_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00005ec0;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00005ec0:
  if (*(long *)PTR____stack_chk_guard_00008018 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00005ef0 __ZNSt3__110__function12__value_funcIFvibbEEC2B8ne190102ERKS3_ ====
long __ZNSt3__110__function12__value_funcIFvibbEEC2B8ne190102ERKS3_(long param_1,long *param_2)

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

// ==== 00005f54 __ZNSt3__110__function12__value_funcIFvibbEE4swapB8ne190102ERS3_ ====
void __ZNSt3__110__function12__value_funcIFvibbEE4swapB8ne190102ERS3_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00008018;
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
  if (*(long *)PTR____stack_chk_guard_00008018 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000060c0 __ZNSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEED1Ev ====
long __ZNSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 000060e8 __ZNSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEED0Ev ====
void __ZNSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00006110 __ZNKSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_000081e8;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 00006150 __ZNKSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE7__cloneEPNS0_6__baseIS5_EE ====
void __ZNKSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE7__cloneEPNS0_6__baseIS5_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_000081e8;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 0000616c __ZNSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 00006174 __ZNSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000619c __ZNSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEEclEOiObS8_ ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEEclEOiObS8_
          (long param_1,int *param_2,byte *param_3,byte *param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  ID self;
  
  iVar3 = *param_2;
  bVar1 = *param_3;
  bVar2 = *param_4;
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::midiOutAudioUnit_requestsMIDIEventOutputAtIndex_isPrerolled_isRewound_
            (self,*(undefined8 *)(param_1 + 8),(long)iVar3,(ulong)bVar1,(ulong)bVar2);
  return 0;
}

// ==== 00006254 __ZNKSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 00006290 __ZNKSt3__110__function6__funcIZ62-[MIDIOutAudioUnit_configureDSPKernelWithEventTimes:delegate:]E3$_0NS_9allocatorIS2_EEFvibbEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0NS_9allocatorIS2_EEFvibbEE11target_typeEv
          (void)

{
  return &__ZTIZ62__MIDIOutAudioUnit_configureDSPKernelWithEventTimes_delegate__E3__0;
}

// ==== 0000629c __ZNKSt9type_infoeqB8ne190102ERKS_ ====
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

// ==== 000062e8 __ZN9DSPKernel14handleOneEventEPK13AURenderEvent ====
void __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(long *param_1,long param_2)

{
  if (*(byte *)(param_2 + 0x10) - 1 < 2) {
                    /* WARNING: Could not recover jumptable at 0x00006310. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))
              (*(undefined4 *)(param_2 + 0x20),param_1,*(undefined8 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x14));
    return;
  }
  if (*(byte *)(param_2 + 0x10) == 8) {
                    /* WARNING: Could not recover jumptable at 0x00006324. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x10))();
    return;
  }
  return;
}

// ==== 0000632c __ZN9DSPKernel28performAllSimultaneousEventsExRPK13AURenderEvent ====
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

// ==== 00006380 __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent ====
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
                    /* WARNING: Could not recover jumptable at 0x00006440. Too many branches */
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

// ==== 00006444 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x0000644c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_00008a70)(param_1,param_2,param_3);
  return;
}

// ==== 00006450 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00006458. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_00008a78)(param_1,param_2);
  return;
}

// ==== 0000645c __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00006464. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_00008a80)();
  return;
}

// ==== 00006468 __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006470. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_00008a88)();
  return;
}

// ==== 00006474 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000647c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_00008a90)();
  return;
}

// ==== 00006480 __ZdaPv ====
void __ZdaPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006488. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdaPv_00008030)();
  return;
}

// ==== 0000648c __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006494. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008038)();
  return;
}

// ==== 00006498 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008040)();
  return;
}

// ==== 000064a4 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_00008a98)();
  return;
}

// ==== 000064b0 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_00008aa0)();
  return;
}

// ==== 000064bc ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_00008aa8)();
  return;
}

// ==== 000064c8 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00008ab0)();
  return;
}

// ==== 000064d4 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000064dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00008ab8)();
  return;
}

// ==== 000064e0 _malloc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _malloc(size_t param_1)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000064e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__malloc_00008ac0)();
  return pvVar1;
}

// ==== 000064ec _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x000064f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_00008ac8)();
  return;
}

// ==== 000064f8 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006500. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00008ad0)();
  return;
}

// ==== 00006504 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000650c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00008ad8)();
  return;
}

// ==== 00006510 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006518. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008ae0)();
  return;
}

// ==== 0000651c _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006524. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008ae8)();
  return;
}

// ==== 00006528 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006530. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008af0)();
  return;
}

// ==== 00006534 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000653c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008af8)();
  return;
}

// ==== 00006540 _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006548. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_00008b00)();
  return;
}

// ==== 0000654c _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006554. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008b08)();
  return IVar1;
}

// ==== 00006558 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008b10)();
  return;
}

// ==== 00006564 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000656c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008b18)();
  return;
}

// ==== 00006570 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006578. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00008b20)();
  return;
}

// ==== 0000657c _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006584. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00008b28)();
  return;
}

// ==== 00006588 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006590. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00008b30)();
  return;
}

// ==== 00006594 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000659c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00008b38)();
  return;
}

// ==== 000065a0 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00008b40)();
  return;
}

// ==== 000065ac _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x000065b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_00008b48)();
  return;
}

// ==== 000065b8 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000065c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_00008b50)((int)param_1);
  return iVar1;
}

// ==== 00006740 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"address");
  return IVar1;
}

// ==== 00006760 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00006780 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"audioBufferList");
  return IVar1;
}

// ==== 000067a0 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"busType");
  return IVar1;
}

// ==== 000067c0 objc_stub::clearCVariables ====
ID __objc_msgSend_stub objc_stub::clearCVariables(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"clearCVariables");
  return IVar1;
}

// ==== 000067e0 objc_stub::count ====
ID __objc_msgSend_stub objc_stub::count(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"count");
  return IVar1;
}

// ==== 00006800 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
ID __objc_msgSend_stub
objc_stub::
createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
          (ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)
                    (self,
                     "createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters:"
                    );
  return IVar1;
}

// ==== 00006820 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00006840 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"defaultFormat");
  return IVar1;
}

// ==== 00006860 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"delegate");
  return IVar1;
}

// ==== 00006880 objc_stub::doubleValue ====
ID __objc_msgSend_stub objc_stub::doubleValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"doubleValue");
  return IVar1;
}

// ==== 000068a0 objc_stub::enumerateObjectsUsingBlock: ====
ID __objc_msgSend_stub objc_stub::enumerateObjectsUsingBlock_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"enumerateObjectsUsingBlock:");
  return IVar1;
}

// ==== 000068c0 objc_stub::eventTimes ====
ID __objc_msgSend_stub objc_stub::eventTimes(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"eventTimes");
  return IVar1;
}

// ==== 000068e0 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 00006900 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"format");
  return IVar1;
}

// ==== 00006920 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00006940 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00006960 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00006980 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 000069a0 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 000069c0 objc_stub::midiOutAudioUnit:requestsMIDIEventOutputAtIndex:isPrerolled:isRewound: ====
ID __objc_msgSend_stub
objc_stub::midiOutAudioUnit_requestsMIDIEventOutputAtIndex_isPrerolled_isRewound_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)
                    (self,"midiOutAudioUnit:requestsMIDIEventOutputAtIndex:isPrerolled:isRewound:");
  return IVar1;
}

// ==== 000069e0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00006a00 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"raise");
  return IVar1;
}

// ==== 00006a20 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"reset");
  return IVar1;
}

// ==== 00006a40 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"sampleRate");
  return IVar1;
}

// ==== 00006a60 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00006a80 objc_stub::setDelegate: ====
ID __objc_msgSend_stub objc_stub::setDelegate_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setDelegate:");
  return IVar1;
}

// ==== 00006aa0 objc_stub::setEventTimes: ====
ID __objc_msgSend_stub objc_stub::setEventTimes_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setEventTimes:");
  return IVar1;
}

// ==== 00006ac0 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00006ae0 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00006b00 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00006b20 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00006b40 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00006b60 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setValue:");
  return IVar1;
}

// ==== 00006b80 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00006ba0 objc_stub::value ====
ID __objc_msgSend_stub objc_stub::value(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"value");
  return IVar1;
}

// ==== 00018101 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018201 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018301 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018302 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018303 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018401 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018501 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018601 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018701 NSException::exceptionWithName:reason:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::exceptionWithName_reason_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018702 NSException::raise ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::raise(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018801 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018901 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018902 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018903 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018904 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018905 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018906 TrackedAUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018907 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018908 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00019600 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

