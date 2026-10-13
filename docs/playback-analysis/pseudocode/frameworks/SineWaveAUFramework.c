// SineWaveAUFramework sha256 8a628e8ba7badfd94e74ce4724f2e27341b5429b4e2a7a31e98d6a01d8a56d53 (Ghidra 12.1.4, all decompiled functions)

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

// ==== 0000415c SineWaveAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID SineWaveAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  ID IVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined *local_f0;
  undefined8 local_e8;
  code *local_e0;
  undefined *puStack_d8;
  undefined8 *local_d0;
  undefined *local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  undefined8 *local_a8;
  undefined8 local_a0;
  undefined8 *puStack_98;
  undefined8 local_90;
  undefined8 *local_88;
  ID local_78;
  class_t *pcStack_70;
  ID local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008050;
  puStack_98 = *(undefined8 **)&param_3->field2_0x8;
  local_a0._0_4_ = param_3->field0_0x0;
  local_a0._4_4_ = param_3->field1_0x4;
  local_90 = CONCAT44(local_90._4_4_,param_3->field4_0x10);
  pcStack_70 = &objc::class_t::SineWaveAudioUnit;
  local_78 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_78,"initWithComponentDescription:options:error:",&local_a0,
                    (ulong)param_4);
  if (self != 0) {
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
    local_60 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_60,1);
    IVar2 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar3);
    uVar4 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    TrackedAUAudioUnit::setMaximumFramesToRender_(self,uVar4,0x200);
    TrackedAUAudioUnit::setFrequency_(self,0x3ff0000000000000);
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isEnabledParameter,
                       &cf_isEnabled,0,2,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    local_68 = IVar2;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_68,1);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    lVar5 = (long)_dspKernel;
    local_88 = *(undefined8 **)(self + lVar5);
    if (local_88 == (undefined8 *)0x0) {
      local_88 = (undefined8 *)__Znwm(0x48);
      *local_88 = &DAT_00008128;
      local_88[1] = 0;
      local_88[2] = 0x407b800000000000;
      *(undefined4 *)(local_88 + 3) = 0;
      local_88[5] = 0;
      local_88[4] = 0;
      local_88[7] = 0;
      local_88[6] = 0;
      *(undefined1 *)(local_88 + 8) = 0;
      *(undefined8 **)(self + lVar5) = local_88;
    }
    puVar1 = PTR___NSConcreteStackBlock_00008048;
    local_a0 = 0;
    local_90 = 0x2020000000;
    local_c8 = PTR___NSConcreteStackBlock_00008048;
    local_c0 = 0xc2000000;
    local_b8 = ___64__SineWaveAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_b0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_a8 = &local_a0;
    puStack_98 = &local_a0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_c8);
    local_f0 = puVar1;
    local_e8 = 0xc2000000;
    local_e0 = ___64__SineWaveAudioUnit_initWithComponentDescription_options_error___block_invoke_8;
    puStack_d8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_d0 = &local_a0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_f0);
    __Block_object_dispose(&local_a0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008050 == local_58) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004594 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 00004628 ___64-[SineWaveAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___64__SineWaveAudioUnit_initWithComponentDescription_options_error___block_invoke
               (float param_1,long param_2,ID param_3)

{
  ID IVar1;
  long lVar2;
  
  lVar2 = *(long *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  if (IVar1 == 0) {
    *(bool *)(lVar2 + 0x40) = param_1 != 0.0;
  }
  return;
}

// ==== 00004670 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004680 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 0000468c ___64-[SineWaveAudioUnit_initWithComponentDescription:options:error:]_block_invoke.8 ====
undefined4
___64__SineWaveAudioUnit_initWithComponentDescription_options_error___block_invoke_8
          (long param_1,ID param_2)

{
  ID IVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  uVar3 = 0;
  if ((IVar1 == 0) && (uVar3 = 0x3f800000, *(char *)(lVar2 + 0x40) == '\0')) {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== 000046d0 SineWaveAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void SineWaveAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::SineWaveAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  *(undefined1 *)(*(long *)(param_1 + (long)_dspKernel) + 0x40) = 0;
  __ZN17SineWaveDSPKernel18recomputeWavetableEv();
  return;
}

// ==== 00004724 SineWaveAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void SineWaveAudioUnit::dealloc(ID param_1,SEL param_2)

{
  SEL extraout_x1;
  undefined8 *puVar1;
  long lVar2;
  ID local_40;
  class_t *pcStack_38;
  
  lVar2 = (long)_dspKernel;
  *(undefined8 *)(*(long *)(param_1 + lVar2) + 0x38) = 0;
  puVar1 = *(undefined8 **)(param_1 + lVar2);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = &DAT_00008128;
    puVar1[7] = 0;
    if (puVar1[4] != 0) {
      puVar1[5] = puVar1[4];
      __ZdlPv();
      param_2 = extraout_x1;
    }
    __ZdlPv(puVar1,param_2);
  }
  *(undefined8 *)(param_1 + lVar2) = 0;
  pcStack_38 = &objc::class_t::SineWaveAudioUnit;
  local_40 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_40,"dealloc");
  return;
}

// ==== 000047b4 SineWaveAudioUnit::configureDSPKernelWithFrequency: ====
/* Function Stack Size: 0x18 bytes */

ID __objc_msgSend_stub SineWaveAudioUnit::configureDSPKernelWithFrequency_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"updateFrequency:");
  return IVar1;
}

// ==== 000047b8 SineWaveAudioUnit::updateFrequency: ====
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::updateFrequency_(ID param_1,SEL param_2,double param_3)

{
  setFrequency_(param_1,param_3);
  *(double *)(*(long *)(param_1 + (long)_dspKernel) + 0x10) = (double)(float)param_3;
  __ZN17SineWaveDSPKernel18recomputeWavetableEv();
  return;
}

// ==== 000047fc SineWaveAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 0000480c SineWaveAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool SineWaveAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  double extraout_d0;
  double dVar5;
  ID local_70;
  class_t *pcStack_68;
  
  pcStack_68 = &objc::class_t::SineWaveAudioUnit;
  local_70 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_70,"allocateRenderResourcesAndReturnError:");
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
      dVar5 = frequency(param_1);
      *(int *)(lVar4 + 8) = (int)IVar2;
      *(int *)(lVar4 + 0xc) = (int)extraout_d0;
      *(double *)(lVar4 + 0x10) = dVar5;
      __ZN17SineWaveDSPKernel18recomputeWavetableEv(lVar4);
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

// ==== 00004a54 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00004af4 SineWaveAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void SineWaveAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  *(undefined8 *)(*(long *)(param_1 + (long)_dspKernel) + 0x38) = 0;
  pcStack_28 = &objc::class_t::SineWaveAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 00004b60 SineWaveAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool SineWaveAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  long lVar5;
  long local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008050;
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
                         *(undefined8 *)PTR__NSInternalInconsistencyException_00008060,
                         &cf_Cannotinitoutputbuswithnewformat,0);
      NSException::raise(IVar3);
    }
  }
  else {
    IVar3 = NSException::exceptionWithName_reason_userInfo_
                      ((ID)&_OBJC_CLASS___NSException,
                       *(undefined8 *)PTR__NSInternalInconsistencyException_00008060,
                       &cf_Unrecognisedbustype,0);
    NSException::raise(IVar3);
  }
  if (*(long *)PTR____stack_chk_guard_00008050 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return (bool)(IVar2 == 2);
}

// ==== 00004dcc SineWaveAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_00008048;
  local_80 = 0xc2000000;
  local_78 = ___40__SineWaveAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00004e94 ___40-[SineWaveAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___40__SineWaveAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)SineWaveAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x38) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00004f3c __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00004fd4 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 0000500c ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005038 SineWaveAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool SineWaveAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 00005040 SineWaveAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 00005050 SineWaveAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 00005064 SineWaveAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005074 SineWaveAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005088 SineWaveAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005098 SineWaveAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 000050a4 SineWaveAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 000050b4 SineWaveAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 000050c0 SineWaveAudioUnit::frequency ====
/* Function Stack Size: 0x10 bytes */

double SineWaveAudioUnit::frequency(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + (long)_frequency);
}

// ==== 000050d0 SineWaveAudioUnit::setFrequency: ====
/* Function Stack Size: 0x18 bytes */

void SineWaveAudioUnit::setFrequency_(ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + (long)_frequency) = param_3;
  return;
}

// ==== 000050e0 SineWaveAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void SineWaveAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005164 SineWaveAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID SineWaveAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00005184 __ZN17SineWaveDSPKernel7processEjj ====
void __ZN17SineWaveDSPKernel7processEjj(long param_1,uint param_2,int param_3)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  long *plVar9;
  
  if (*(char *)(param_1 + 0x40) != '\0') {
    lVar1 = *(long *)(param_1 + 0x20);
    lVar3 = *(long *)(param_1 + 0x28) - lVar1;
    if (lVar3 != 0) {
      if (param_2 == 0) {
        return;
      }
      uVar6 = 0;
      uVar7 = lVar3 >> 2;
      uVar2 = *(uint *)(param_1 + 8);
      iVar8 = *(int *)(param_1 + 0x18);
      do {
        if (0 < (int)uVar2) {
          if (uVar7 <= (ulong)(long)iVar8) {
            __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev
                      ((long *)(param_1 + 0x20));
            return;
          }
          plVar9 = *(long **)(param_1 + 0x38);
          uVar5 = (ulong)uVar2;
          do {
            plVar9 = plVar9 + 2;
            *(float *)(*plVar9 + (long)((int)uVar6 + param_3) * 4) =
                 *(float *)(lVar1 + (long)iVar8 * 4) * 0.1;
            uVar5 = uVar5 - 1;
          } while (uVar5 != 0);
        }
        iVar4 = 0;
        if (uVar7 != 0) {
          iVar4 = (int)((ulong)(long)(iVar8 + 1) / uVar7);
        }
        iVar8 = (iVar8 + 1) - iVar4 * (int)uVar7;
        *(int *)(param_1 + 0x18) = iVar8;
        uVar6 = uVar6 + 1;
      } while (uVar6 != param_2);
      return;
    }
  }
  if (param_2 != 0) {
    uVar6 = 0;
    uVar2 = *(uint *)(param_1 + 8);
    do {
      if (0 < (int)uVar2) {
        plVar9 = *(long **)(param_1 + 0x38);
        uVar7 = (ulong)uVar2;
        do {
          plVar9 = plVar9 + 2;
          *(undefined4 *)(*plVar9 + (long)((int)uVar6 + param_3) * 4) = 0;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 != param_2);
  }
  return;
}

// ==== 00005284 __ZN17SineWaveDSPKernel9startRampEyfj ====
void __ZN17SineWaveDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00005288 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 0000528c __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev ====
void __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc("vector");
}

// ==== 000052a0 __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc ====
void __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12out_of_rangeC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12out_of_range_00008070,PTR___ZNSt12out_of_rangeD1Ev_00008018);
}

// ==== 000052f0 __ZNSt12out_of_rangeC1B8ne190102EPKc ====
void __ZNSt12out_of_rangeC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12out_of_range_00008038 + 0x10);
  return;
}

// ==== 00005314 __ZN17SineWaveDSPKernel18recomputeWavetableEv ====
void __ZN17SineWaveDSPKernel18recomputeWavetableEv(long param_1)

{
  ulong uVar1;
  void *pvVar2;
  size_t sVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  ulong *puVar7;
  long lVar8;
  int iVar9;
  float *pfVar10;
  float *pfVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined1 auVar15 [16];
  
  puVar7 = (ulong *)(param_1 + 0x20);
  *(float **)(param_1 + 0x28) = (float *)*puVar7;
  if ((0.0 < *(double *)(param_1 + 0x10)) && (0 < (int)*(uint *)(param_1 + 0xc))) {
    dVar12 = (double)*(uint *)(param_1 + 0xc);
    iVar9 = (int)(dVar12 / *(double *)(param_1 + 0x10));
    if (0 < iVar9) {
      dVar14 = 0.0;
      pfVar10 = (float *)*puVar7;
      do {
        dVar13 = (double)_sin(dVar14 * *(double *)(param_1 + 0x10) * 6.283185307179586);
        if (pfVar10 < *(float **)(param_1 + 0x30)) {
          pfVar11 = pfVar10 + 1;
          *pfVar10 = (float)dVar13;
        }
        else {
          pvVar2 = (void *)*puVar7;
          sVar3 = (long)pfVar10 - (long)pvVar2;
          lVar8 = (long)sVar3 >> 2;
          uVar1 = lVar8 + 1;
          if (uVar1 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
            __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev(puVar7);
          }
          uVar4 = (long)*(float **)(param_1 + 0x30) - (long)pvVar2;
          uVar6 = (long)uVar4 >> 1;
          if (uVar6 <= uVar1) {
            uVar6 = uVar1;
          }
          if (0x7ffffffffffffffb < uVar4) {
            uVar6 = 0x3fffffffffffffff;
          }
          if (uVar6 == 0) {
            auVar15 = ZEXT816(0);
            lVar5 = lVar8;
          }
          else {
            auVar15 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIfEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                                (param_1 + 0x30,uVar6);
            pvVar2 = *(void **)(param_1 + 0x20);
            sVar3 = *(long *)(param_1 + 0x28) - (long)pvVar2;
            lVar5 = (long)sVar3 >> 2;
          }
          pfVar10 = (float *)(auVar15._0_8_ + lVar8 * 4);
          pfVar11 = pfVar10 + 1;
          *pfVar10 = (float)dVar13;
          _memcpy(pfVar10 + -lVar5,pvVar2,sVar3);
          lVar8 = *(long *)(param_1 + 0x20);
          *(float **)(param_1 + 0x20) = pfVar10 + -lVar5;
          *(float **)(param_1 + 0x28) = pfVar11;
          *(long *)(param_1 + 0x30) = auVar15._0_8_ + auVar15._8_8_ * 4;
          if (lVar8 != 0) {
            __ZdlPv();
          }
        }
        *(float **)(param_1 + 0x28) = pfVar11;
        dVar14 = 1.0 / dVar12 + dVar14;
        iVar9 = iVar9 + -1;
        pfVar10 = pfVar11;
      } while (iVar9 != 0);
    }
  }
  return;
}

// ==== 00005474 __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 00005488 __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_00008068,PTR___ZNSt12length_errorD1Ev_00008010);
}

// ==== 000054d8 __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_00008030 + 0x10);
  return;
}

// ==== 000054fc __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIfEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m ====
void __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIfEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
               (undefined8 param_1,ulong param_2)

{
  if (param_2 >> 0x3e == 0) {
    __Znwm(param_2 << 2);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZSt28__throw_bad_array_new_lengthB8ne190102v();
}

// ==== 00005530 __ZSt28__throw_bad_array_new_lengthB8ne190102v ====
void __ZSt28__throw_bad_array_new_lengthB8ne190102v(void)

{
  undefined8 uVar1;
  
  ___cxa_allocate_exception(8);
  uVar1 = __ZNSt20bad_array_new_lengthC1Ev();
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt20bad_array_new_length_00008028,
               PTR___ZNSt20bad_array_new_lengthD1Ev_00008020);
}

// ==== 00005558 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00005560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_000085f8)(param_1,param_2,param_3);
  return;
}

// ==== 00005564 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0000556c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_00008600)(param_1,param_2);
  return;
}

// ==== 00005570 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00005578. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_00008608)();
  return;
}

// ==== 0000557c __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005584. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_00008610)();
  return;
}

// ==== 00005588 __ZNSt20bad_array_new_lengthC1Ev ====
void __ZNSt20bad_array_new_lengthC1Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005590. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt20bad_array_new_lengthC1Ev_00008618)();
  return;
}

// ==== 00005594 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000559c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008078)();
  return;
}

// ==== 000055a0 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008080)();
  return;
}

// ==== 000055ac ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_00008620)();
  return;
}

// ==== 000055b8 ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_00008628)();
  return;
}

// ==== 000055c4 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_00008630)();
  return;
}

// ==== 000055d0 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00008638)();
  return;
}

// ==== 000055dc _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000055e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00008640)();
  return;
}

// ==== 000055e8 _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000055f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_00008648)();
  return pvVar1;
}

// ==== 000055f4 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x000055fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_00008650)();
  return;
}

// ==== 00005600 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005608. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_00008658)();
  return;
}

// ==== 0000560c _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005614. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00008660)();
  return;
}

// ==== 00005618 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005620. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00008668)();
  return;
}

// ==== 00005624 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000562c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008670)();
  return;
}

// ==== 00005630 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005638. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008678)();
  return;
}

// ==== 0000563c _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005644. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008680)();
  return;
}

// ==== 00005648 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005650. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008688)();
  return;
}

// ==== 00005654 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000565c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008690)();
  return IVar1;
}

// ==== 00005660 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005668. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008698)();
  return;
}

// ==== 0000566c _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005674. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_000086a0)();
  return;
}

// ==== 00005678 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005680. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_000086a8)();
  return;
}

// ==== 00005684 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000568c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_000086b0)();
  return;
}

// ==== 00005690 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005698. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_000086b8)();
  return;
}

// ==== 0000569c _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x000056a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_000086c0)();
  return;
}

// ==== 000056a8 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x000056b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_000086c8)();
  return;
}

// ==== 000056b4 _sin ====
void _sin(void)

{
                    /* WARNING: Could not recover jumptable at 0x000056bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__sin_000086d0)();
  return;
}

// ==== 00005840 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"address");
  return IVar1;
}

// ==== 00005860 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00005880 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"auOutputBus");
  return IVar1;
}

// ==== 000058a0 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"audioBufferList");
  return IVar1;
}

// ==== 000058c0 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"busType");
  return IVar1;
}

// ==== 000058e0 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"channelCount");
  return IVar1;
}

// ==== 00005900 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00005920 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00005940 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00005960 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00005980 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 000059a0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"format");
  return IVar1;
}

// ==== 000059c0 objc_stub::frequency ====
ID __objc_msgSend_stub objc_stub::frequency(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"frequency");
  return IVar1;
}

// ==== 000059e0 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00005a00 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00005a20 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00005a40 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00005a60 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00005a80 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00005aa0 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"raise");
  return IVar1;
}

// ==== 00005ac0 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"reset");
  return IVar1;
}

// ==== 00005ae0 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"sampleRate");
  return IVar1;
}

// ==== 00005b00 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00005b20 objc_stub::setFrequency: ====
ID __objc_msgSend_stub objc_stub::setFrequency_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setFrequency:");
  return IVar1;
}

// ==== 00005b40 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00005b60 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00005b80 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00005ba0 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00005bc0 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00005be0 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setValue:");
  return IVar1;
}

// ==== 00005c00 objc_stub::updateFrequency: ====
ID __objc_msgSend_stub objc_stub::updateFrequency_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"updateFrequency:");
  return IVar1;
}

// ==== 00014201 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014301 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014401 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014402 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014403 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014501 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014601 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014701 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014801 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014901 NSException::exceptionWithName:reason:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::exceptionWithName_reason_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014902 NSException::raise ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::raise(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a01 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a02 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a03 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a04 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a05 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a06 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a07 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a08 TrackedAUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a09 TrackedAUAudioUnit::setFrequency: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setFrequency_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00015c00 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

