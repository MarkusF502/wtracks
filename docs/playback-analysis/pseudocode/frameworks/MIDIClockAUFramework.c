// MIDIClockAUFramework sha256 8a282176f92a429bfc4bde96fc34d2f159f2b2d84ae231ce0e7487d63abcec4c (Ghidra 12.1.4, all decompiled functions)

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

// ==== 00004174 __ZN14CAHostTimeBase10InitializeEv ====
kern_return_t __ZN14CAHostTimeBase10InitializeEv(void)

{
  kern_return_t kVar1;
  mach_timebase_info local_18;
  
  kVar1 = _mach_timebase_info(&local_18);
  __ZN14CAHostTimeBase9sMinDeltaE = 1;
  __ZN14CAHostTimeBase17sToNanosNumeratorE = local_18.numer;
  __ZN14CAHostTimeBase19sToNanosDenominatorE = local_18.denom;
  __ZN14CAHostTimeBase10sFrequencyE =
       ((double)local_18.denom / (double)local_18.numer) * 1000000000.0;
  __ZN14CAHostTimeBase17sInverseFrequencyE = 1.0 / __ZN14CAHostTimeBase10sFrequencyE;
  return kVar1;
}

// ==== 000041e4 MIDIClockAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID MIDIClockAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  ID IVar3;
  ID self_00;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined *local_110;
  undefined8 local_108;
  code *local_100;
  undefined *puStack_f8;
  undefined8 *local_f0;
  undefined *local_e8;
  undefined8 local_e0;
  code *local_d8;
  undefined *puStack_d0;
  undefined8 *local_c8;
  undefined8 local_c0;
  undefined8 *puStack_b8;
  undefined8 local_b0;
  undefined8 *local_a8;
  ID local_98;
  class_t *pcStack_90;
  ID local_88;
  ID IStack_80;
  ID local_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_00008018;
  puStack_b8 = *(undefined8 **)&param_3->field2_0x8;
  local_c0._0_4_ = param_3->field0_0x0;
  local_c0._4_4_ = param_3->field1_0x4;
  local_b0 = CONCAT44(local_b0._4_4_,param_3->field4_0x10);
  pcStack_90 = &objc::class_t::MIDIClockAudioUnit;
  local_98 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_98,"initWithComponentDescription:options:error:",&local_c0,
                    (ulong)param_4);
  if (self != 0) {
    *(undefined8 *)(self + (long)_midiEndpointRefs) = 0;
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
    local_70 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_70,1);
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
                       &cf_isPlaying,1,2,0,0,0,0);
    self_00 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x43960000,&cf_tempoParameter,
                         &cf_tempo,2,0x16,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    AUParameterTree::setValue_(self_00,0x42f00000);
    local_88 = IVar2;
    IStack_80 = IVar3;
    local_78 = self_00;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_88,3);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    lVar5 = (long)_dspKernel;
    local_a8 = *(undefined8 **)(self + lVar5);
    if (local_a8 == (undefined8 *)0x0) {
      local_a8 = (undefined8 *)__Znwm(0x50);
      *local_a8 = &DAT_00008160;
      *(undefined4 *)(local_a8 + 1) = 0x472c4400;
      local_a8[2] = 0;
      local_a8[4] = 0;
      local_a8[5] = 0;
      *(undefined8 *)((long)local_a8 + 0x2e) = 0;
      *(undefined4 *)(local_a8 + 7) = 0x42f00000;
      *(undefined1 *)((long)local_a8 + 0x3c) = 0;
      *(undefined8 **)(self + lVar5) = local_a8;
    }
    puVar1 = PTR___NSConcreteStackBlock_00008010;
    local_c0 = 0;
    local_b0 = 0x2020000000;
    local_e8 = PTR___NSConcreteStackBlock_00008010;
    local_e0 = 0xc2000000;
    local_d8 = ___65__MIDIClockAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_d0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_c8 = &local_c0;
    puStack_b8 = &local_c0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_e8);
    local_110 = puVar1;
    local_108 = 0xc2000000;
    local_100 = 
    ___65__MIDIClockAudioUnit_initWithComponentDescription_options_error___block_invoke_16;
    puStack_f8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_f0 = &local_c0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_110);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar6),&___block_literal_global);
    __Block_object_dispose(&local_c0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008018 == local_68) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004710 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 000047a4 ___65-[MIDIClockAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___65__MIDIClockAudioUnit_initWithComponentDescription_options_error___block_invoke
          (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN18MIDIClockDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return 0;
}

// ==== 00004810 __ZN18MIDIClockDSPKernel12setParameterEyf ====
void __ZN18MIDIClockDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  if (param_3 == 2) {
    *(float *)(param_2 + 0x38) = param_1;
    return;
  }
  if (param_3 == 1) {
    *(bool *)(param_2 + 0x35) = param_1 != 0.0;
    if ((param_1 == 0.0) &&
       (*(undefined1 *)(param_2 + 0x3c) = 0, *(char *)(param_2 + 0x34) == '\x01')) {
      __ZN18MIDIClockDSPKernel20sendMIDIClockMessageE16MIDIClockMessage(param_2,0xfc);
      return;
    }
  }
  else if (param_3 == 0) {
    *(bool *)(param_2 + 0x34) = param_1 != 0.0;
    return;
  }
  return;
}

// ==== 00004868 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004878 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004884 ___65-[MIDIClockAudioUnit_initWithComponentDescription:options:error:]_block_invoke.16 ====
undefined1  [16]
___65__MIDIClockAudioUnit_initWithComponentDescription_options_error___block_invoke_16
          (undefined8 param_1,ID param_2)

{
  objc_stub::address(param_2);
  return ZEXT816(0);
}

// ==== 000048a0 ___65-[MIDIClockAudioUnit_initWithComponentDescription:options:error:]_block_invoke.18 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___65__MIDIClockAudioUnit_initWithComponentDescription_options_error___block_invoke_18
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
  if (IVar1 == 0) {
    pcVar2 = &cf_Disabled;
    pcVar3 = &cf_Enabled;
  }
  else {
    if (IVar1 != 1) {
      if (IVar1 == 2) {
        pcVar2 = (cfstringStruct *)
                 NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__fBPM);
        return pcVar2;
      }
      return &cf__;
    }
    pcVar2 = &cf_Stopped;
    pcVar3 = &cf_Playing;
  }
  if (fVar4 == 0.0) {
    pcVar3 = pcVar2;
  }
  return pcVar3;
}

// ==== 00004994 MIDIClockAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::reset(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::MIDIClockAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined1 *)(lVar1 + 0x3c) = 0;
  *(undefined1 *)(lVar1 + 0x35) = 0;
  *(undefined4 *)(lVar1 + 0x38) = 0x42f00000;
  return;
}

// ==== 000049f0 MIDIClockAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  clearCVariables(param_1);
  lVar1 = (long)_dspKernel;
  *(undefined8 *)(*(long *)(param_1 + lVar1) + 0x10) = 0;
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZdlPv();
  }
  *(undefined8 *)(param_1 + lVar1) = 0;
  pcStack_28 = &objc::class_t::MIDIClockAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_30,"dealloc");
  return;
}

// ==== 00004a80 ___clang_call_terminate ====
void ___clang_call_terminate(void)

{
  long lVar1;
  long lVar2;
  
  ___cxa_begin_catch();
  lVar1 = __ZSt9terminatev();
  lVar2 = (long)MIDIClockAudioUnit::_midiEndpointRefs;
  if (*(long *)(lVar1 + lVar2) != 0) {
    __ZdaPv();
    *(undefined8 *)(lVar1 + lVar2) = 0;
  }
  return;
}

// ==== 00004a90 MIDIClockAudioUnit::clearCVariables ====
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::clearCVariables(ID param_1,SEL param_2)

{
  long lVar1;
  
  lVar1 = (long)_midiEndpointRefs;
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZdaPv();
    *(undefined8 *)(param_1 + lVar1) = 0;
  }
  return;
}

// ==== 00004ac4 MIDIClockAudioUnit::prepareToPlayFromPlayheadPosition: ====
/* Function Stack Size: 0x14 bytes */

void MIDIClockAudioUnit::prepareToPlayFromPlayheadPosition_(ID param_1,SEL param_2,int param_3)

{
  __ZN18MIDIClockDSPKernel13prepareToPlayEi(*(undefined8 *)(param_1 + (long)_dspKernel),param_3);
  return;
}

// ==== 00004ad8 __ZN18MIDIClockDSPKernel13prepareToPlayEi ====
ulong __ZN18MIDIClockDSPKernel13prepareToPlayEi(ulong param_1,uint param_2)

{
  uint uVar1;
  float fVar2;
  
  if ((int)param_2 < 0) {
    fVar2 = *(float *)(param_1 + 0x38);
  }
  else {
    fVar2 = *(float *)(param_1 + 0x38);
    *(uint *)(param_1 + 0x2c) = param_2;
    *(int *)(param_1 + 0x30) =
         (int)((float)param_2 + *(float *)(param_1 + 8) * (1.0 / ((fVar2 * 24.0) / 60.0)));
  }
  if (0.0 < fVar2) {
    return param_1;
  }
  uVar1 = _puts("Error: MIDI clock AU has a tempo of 0.0. No MIDI clock messages will be sent.");
  return (ulong)uVar1;
}

// ==== 00004b30 MIDIClockAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x14 bytes */

void MIDIClockAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,float param_3)

{
  __ZN18MIDIClockDSPKernel13prepareToPlayEi
            (*(long *)(param_1 + (long)_dspKernel),
             (int)(*(float *)(*(long *)(param_1 + (long)_dspKernel) + 8) * param_3));
  return;
}

// ==== 00004b4c MIDIClockAudioUnit::updateDestinationEndpoints ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::updateDestinationEndpoints(ID param_1,SEL param_2)

{
  unsigned_int uVar1;
  ID IVar2;
  void *pvVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  double extraout_d0;
  undefined *local_78;
  undefined8 local_70;
  code *local_68;
  undefined *puStack_60;
  ID local_58;
  
  clearCVariables(param_1);
  IVar2 = endpointRefs(param_1);
  IVar2 = objc_stub::count(IVar2);
  pvVar3 = _malloc(IVar2 << 2);
  lVar5 = (long)_midiEndpointRefs;
  *(void **)(param_1 + lVar5) = pvVar3;
  IVar2 = endpointRefs(param_1);
  local_78 = PTR___NSConcreteStackBlock_00008010;
  local_70 = 0xc2000000;
  local_68 = ___48__MIDIClockAudioUnit_updateDestinationEndpoints__block_invoke;
  puStack_60 = &___block_descriptor_40_ea8_32s_e25_v32__0__NSNumber_8Q16_B24l;
  local_58 = param_1;
  objc_stub::enumerateObjectsUsingBlock_(IVar2,&local_78);
  lVar4 = *(long *)(param_1 + (long)_dspKernel);
  IVar2 = objc_stub::format(*(ID *)(param_1 + (long)_bufferedOutputBus));
  objc_stub::sampleRate(IVar2);
  uVar1 = midiOutputPortRef(param_1);
  uVar6 = *(undefined8 *)(param_1 + lVar5);
  IVar2 = endpointRefs(param_1);
  IVar2 = objc_stub::count(IVar2);
  *(undefined8 *)(lVar4 + 0x10) = 0;
  *(float *)(lVar4 + 8) = (float)extraout_d0;
  *(unsigned_int *)(lVar4 + 0x18) = uVar1;
  *(undefined8 *)(lVar4 + 0x20) = uVar6;
  *(int *)(lVar4 + 0x28) = (int)IVar2;
  __ZN18MIDIClockDSPKernel21setMessagePacketListsEv(lVar4);
  return;
}

// ==== 00004cd4 ___48-[MIDIClockAudioUnit_updateDestinationEndpoints]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___48__MIDIClockAudioUnit_updateDestinationEndpoints__block_invoke
          (long param_1,ID param_2,long param_3)

{
  ID IVar1;
  
  IVar1 = objc_stub::unsignedIntValue(param_2);
  *(int *)(*(long *)(*(long *)(param_1 + 0x20) + (long)MIDIClockAudioUnit::_midiEndpointRefs) +
          param_3 * 4) = (int)IVar1;
  return 0;
}

// ==== 00004d38 ___copy_helper_block_ea8_32s ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */

undefined8 ___copy_helper_block_ea8_32s(undefined8 param_1,long param_2)

{
  return *(undefined8 *)(param_2 + 0x20);
}

// ==== 00004d40 ___destroy_helper_block_ea8_32s ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 ___destroy_helper_block_ea8_32s(void)

{
  return 0;
}

// ==== 00004d48 MIDIClockAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00004d58 MIDIClockAudioUnit::allocateRenderResourcesAndReturnError: ====
/* Function Stack Size: 0x18 bytes */

bool MIDIClockAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  ID IVar1;
  ID IVar2;
  long lVar3;
  ID local_40;
  class_t *pcStack_38;
  
  pcStack_38 = &objc::class_t::MIDIClockAudioUnit;
  local_40 = param_1;
  IVar1 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_40,"allocateRenderResourcesAndReturnError:");
  if ((bool)IVar1 != 0) {
    lVar3 = (long)_bufferedOutputBus;
    IVar2 = objc_stub::maximumFramesToRender(param_1);
    __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar3,IVar2);
    updateDestinationEndpoints(param_1);
    reset(param_1);
  }
  return (bool)IVar1;
}

// ==== 00004dd8 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00004e78 MIDIClockAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

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
  pcStack_28 = &objc::class_t::MIDIClockAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 00004eec MIDIClockAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool MIDIClockAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

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
                         *(undefined8 *)PTR__NSInternalInconsistencyException_00008030,
                         &cf_Cannotinitoutputbuswithnewformat,0);
      NSException::raise(IVar3);
    }
  }
  else {
    IVar3 = NSException::exceptionWithName_reason_userInfo_
                      ((ID)&_OBJC_CLASS___NSException,
                       *(undefined8 *)PTR__NSInternalInconsistencyException_00008030,
                       &cf_Unrecognisedbustype,0);
    NSException::raise(IVar3);
  }
  if (*(long *)PTR____stack_chk_guard_00008018 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return (bool)(IVar2 == 2);
}

// ==== 00005158 MIDIClockAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_78 = ___41__MIDIClockAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00005220 ___41-[MIDIClockAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___41__MIDIClockAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)MIDIClockAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x10) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 000052c8 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00005360 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005398 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 000053c4 MIDIClockAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool MIDIClockAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 000053cc MIDIClockAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 000053dc MIDIClockAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIClockAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000053f0 MIDIClockAudioUnit::endpointRefs ====
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::endpointRefs(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_endpointRefs);
}

// ==== 00005400 MIDIClockAudioUnit::setEndpointRefs: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIClockAudioUnit::setEndpointRefs_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_endpointRefs) = param_3;
  return;
}

// ==== 00005414 MIDIClockAudioUnit::midiOutputPortRef ====
/* Function Stack Size: 0x10 bytes */

unsigned_int MIDIClockAudioUnit::midiOutputPortRef(ID param_1,SEL param_2)

{
  return *(unsigned_int *)(param_1 + (long)_midiOutputPortRef);
}

// ==== 00005424 MIDIClockAudioUnit::setMidiOutputPortRef: ====
/* Function Stack Size: 0x14 bytes */

void MIDIClockAudioUnit::setMidiOutputPortRef_(ID param_1,SEL param_2,unsigned_int param_3)

{
  *(unsigned_int *)(param_1 + (long)_midiOutputPortRef) = param_3;
  return;
}

// ==== 00005434 MIDIClockAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005444 MIDIClockAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIClockAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005458 MIDIClockAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005468 MIDIClockAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIClockAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005474 MIDIClockAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005484 MIDIClockAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MIDIClockAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00005490 MIDIClockAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MIDIClockAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_endpointRefs) = 0;
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005528 MIDIClockAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID MIDIClockAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00005548 __ZN18MIDIClockDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN18MIDIClockDSPKernel7processEjjPK14AudioTimeStamp(long param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  ulong uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  if (param_2 != 0) {
    uVar6 = 0;
    uVar2 = **(uint **)(param_1 + 0x10);
    do {
      iVar3 = *(int *)(param_1 + 0x2c);
      if (0 < (int)uVar2) {
        plVar4 = *(long **)(param_1 + 0x10);
        uVar5 = (ulong)uVar2;
        do {
          plVar4 = plVar4 + 2;
          *(undefined4 *)(*plVar4 + (long)((int)uVar6 + param_3) * 4) = 0;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      if ((((*(char *)(param_1 + 0x34) != '\0') && (*(char *)(param_1 + 0x35) != '\0')) &&
          (*(int *)(param_1 + 0x28) != 0)) && (0.0 < *(float *)(param_1 + 0x38))) {
        uVar1 = iVar3 + (int)uVar6;
        if ((*(byte *)(param_1 + 0x3c) & 1) == 0) {
          uVar7 = 0xfa;
          if (4 < uVar1) {
            uVar7 = 0xfb;
          }
          __ZN18MIDIClockDSPKernel20sendMIDIClockMessageE16MIDIClockMessage(param_1,uVar7);
          *(undefined1 *)(param_1 + 0x3c) = 1;
        }
        if (uVar1 == *(uint *)(param_1 + 0x30)) {
          __ZN18MIDIClockDSPKernel20sendMIDIClockMessageE16MIDIClockMessage(param_1,0xf8);
          *(int *)(param_1 + 0x30) =
               (int)((float)*(int *)(param_1 + 0x30) +
                    *(float *)(param_1 + 8) * (1.0 / ((*(float *)(param_1 + 0x38) * 24.0) / 60.0)));
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 != param_2);
  }
  if (((*(byte *)(param_1 + 0x34) & 1) != 0) && (*(char *)(param_1 + 0x35) == '\x01')) {
    *(uint *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + param_2;
  }
  return;
}

// ==== 0000569c __ZN18MIDIClockDSPKernel9startRampEyfj ====
void __ZN18MIDIClockDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 000056a0 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 000056a4 __ZN18MIDIClockDSPKernel20sendMIDIClockMessageE16MIDIClockMessage ====
void __ZN18MIDIClockDSPKernel20sendMIDIClockMessageE16MIDIClockMessage(long param_1,int param_2)

{
  int iVar1;
  uint64_t uVar2;
  undefined8 uVar3;
  void *pvVar4;
  long lVar5;
  undefined1 uVar6;
  ulong uVar7;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
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
  undefined8 uStack_58;
  undefined4 local_50;
  uint local_44;
  
  iVar1 = ___isPlatformVersionAtLeast(2,0xe,0,0);
  if (iVar1 != 0) {
    if (param_2 == 0xf2) {
      return;
    }
    local_44 = param_2 << 0x10 | 0x10000000;
    uVar2 = _mach_absolute_time();
    local_50 = 0;
    uStack_68 = 0;
    local_70 = 0;
    uStack_58 = 0;
    uStack_60 = 0;
    uStack_88 = 0;
    local_90 = 0;
    uStack_78 = 0;
    uStack_80 = 0;
    uStack_a8 = 0;
    local_b0 = 0;
    uStack_98 = 0;
    uStack_a0 = 0;
    uStack_c8 = 0;
    local_d0 = 0;
    uStack_b8 = 0;
    uStack_c0 = 0;
    uStack_e8 = 0;
    local_f0 = 0;
    uStack_d8 = 0;
    uStack_e0 = 0;
    uStack_108 = 0;
    local_110 = 0;
    uStack_f8 = 0;
    uStack_100 = 0;
    uStack_128 = 0;
    local_130 = 0;
    uStack_118 = 0;
    uStack_120 = 0;
    uStack_148 = 0;
    local_150 = 0;
    uStack_138 = 0;
    uStack_140 = 0;
    uStack_158 = 0;
    local_160 = 0;
    uVar3 = _MIDIEventListInit(&local_160,1);
    _MIDIEventListAdd(&local_160,0x10c,uVar3,uVar2,1,&local_44);
    if (*(int *)(param_1 + 0x28) == 0) {
      return;
    }
    uVar7 = 0;
    do {
      _MIDISendEventList(*(undefined4 *)(param_1 + 0x18),
                         *(undefined4 *)(*(long *)(param_1 + 0x20) + uVar7 * 4),&local_160);
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(param_1 + 0x28));
    return;
  }
  uVar7 = 10000000;
  uVar2 = _mach_absolute_time();
  _pthread_once((pthread_once_t *)&__ZN14CAHostTimeBase9sIsInitedE,
                __ZN14CAHostTimeBase10InitializeEv);
  if (__ZN14CAHostTimeBase19sToNanosDenominatorE != __ZN14CAHostTimeBase17sToNanosNumeratorE) {
    uVar7 = 0;
    if ((ulong)__ZN14CAHostTimeBase17sToNanosNumeratorE != 0) {
      uVar7 = ((ulong)__ZN14CAHostTimeBase19sToNanosDenominatorE * 10000000) /
              (ulong)__ZN14CAHostTimeBase17sToNanosNumeratorE;
    }
  }
  if (param_2 < 0xfa) {
    if (param_2 == 0xf2) {
      local_160 = CONCAT53(local_160._3_5_,0xf2);
      pvVar4 = _malloc(0x11);
      uVar3 = _MIDIPacketListInit();
      _MIDIPacketListAdd(pvVar4,0x11,uVar3,0,3,&local_160);
      __ZN18MIDIClockDSPKernel18sendMIDIPacketListEP14MIDIPacketList(param_1,pvVar4);
    }
    else {
      if (param_2 != 0xf8) {
        return;
      }
      uVar6 = 0xf8;
LAB_00005838:
      local_160 = CONCAT71(local_160._1_7_,uVar6);
      pvVar4 = _malloc(0xf);
      uVar3 = _MIDIPacketListInit();
      _MIDIPacketListAdd(pvVar4,0xf,uVar3,uVar7 + uVar2,1,&local_160);
      __ZN18MIDIClockDSPKernel18sendMIDIPacketListEP14MIDIPacketList(param_1,pvVar4);
    }
    _free(pvVar4);
  }
  else {
    if (param_2 == 0xfa) {
      lVar5 = *(long *)(param_1 + 0x48);
    }
    else {
      if (param_2 == 0xfc) {
        uVar6 = 0xfc;
        goto LAB_00005838;
      }
      if (param_2 != 0xfb) {
        return;
      }
      lVar5 = *(long *)(param_1 + 0x40);
    }
    if (lVar5 != 0) {
      __ZN18MIDIClockDSPKernel18sendMIDIPacketListEP14MIDIPacketList(param_1);
      return;
    }
  }
  return;
}

// ==== 000058e0 __ZN18MIDIClockDSPKernel18sendMIDIPacketListEP14MIDIPacketList ====
ulong __ZN18MIDIClockDSPKernel18sendMIDIPacketListEP14MIDIPacketList
                (ulong param_1,undefined8 param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = param_1;
  if (*(int *)(param_1 + 0x28) != 0) {
    uVar3 = 0;
    do {
      uVar2 = _MIDISend(*(undefined4 *)(param_1 + 0x18),
                        *(undefined4 *)(*(long *)(param_1 + 0x20) + uVar3 * 4),param_2);
      if ((int)uVar2 != 0) {
        uVar1 = _printf("MIDISend error: %i");
        uVar2 = (ulong)uVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x28));
  }
  return uVar2;
}

// ==== 00005958 __ZN18MIDIClockDSPKernel21setMessagePacketListsEv ====
void __ZN18MIDIClockDSPKernel21setMessagePacketListsEv(long param_1)

{
  int iVar1;
  void *pvVar2;
  undefined8 uVar3;
  undefined1 local_22;
  undefined1 local_21;
  
  iVar1 = ___isPlatformVersionAtLeast(2,0xe,0,0);
  if (iVar1 == 0) {
    local_21 = 0xfb;
    pvVar2 = _malloc(0xf);
    uVar3 = _MIDIPacketListInit();
    _MIDIPacketListAdd(pvVar2,0xf,uVar3,0,1,&local_21);
    *(void **)(param_1 + 0x40) = pvVar2;
    local_22 = 0xfa;
    pvVar2 = _malloc(0xf);
    uVar3 = _MIDIPacketListInit();
    _MIDIPacketListAdd(pvVar2,0xf,uVar3,0,1,&local_22);
    *(void **)(param_1 + 0x48) = pvVar2;
  }
  return;
}

// ==== 00005a04 _compatibilityInitializeAvailabilityCheck ====
void _compatibilityInitializeAvailabilityCheck(void)

{
  __initializeAvailabilityCheck(1);
  return;
}

// ==== 00005a0c ___isPlatformVersionAtLeast ====
void ___isPlatformVersionAtLeast(undefined4 param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined4 local_40;
  uint uStack_3c;
  long local_38;
  
  local_38 = *(long *)PTR____stack_chk_guard_00008018;
  if (DAT_00008bc8 != -1) {
    ___isPlatformVersionAtLeast_cold_1();
  }
  if (DAT_00008bd0 != 0) {
    uStack_3c = param_2 << 0x10 | (param_3 & 0xff) << 8 | param_4 & 0xff;
    local_40 = param_1;
    uVar2 = __availability_version_check(1,&local_40);
    if (*(long *)PTR____stack_chk_guard_00008018 == local_38) {
      return;
    }
    goto LAB_00005b60;
  }
  if (DAT_00008bc0 == -1) {
    iVar1 = __MergedGlobals - param_2;
  }
  else {
    ___isPlatformVersionAtLeast_cold_2();
    iVar1 = __MergedGlobals - param_2;
  }
  if (param_2 < __MergedGlobals) {
LAB_00005b04:
    uVar2 = 1;
    lVar3 = *(long *)PTR____stack_chk_guard_00008018;
  }
  else if (iVar1 < 0 == SBORROW4(__MergedGlobals,param_2)) {
    if ((int)param_3 < DAT_00008bb4) goto LAB_00005b04;
    if (DAT_00008bb4 < (int)param_3) goto LAB_00005ad4;
    uVar2 = (ulong)((int)param_4 <= DAT_00008bb8);
    lVar3 = *(long *)PTR____stack_chk_guard_00008018;
  }
  else {
LAB_00005ad4:
    uVar2 = 0;
    lVar3 = *(long *)PTR____stack_chk_guard_00008018;
  }
  if (lVar3 == local_38) {
    return;
  }
LAB_00005b60:
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(uVar2);
}

// ==== 00005b94 _initializeAvailabilityCheck ====
void _initializeAvailabilityCheck(void)

{
  __initializeAvailabilityCheck(0);
  return;
}

// ==== 00005b9c __initializeAvailabilityCheck ====
void __initializeAvailabilityCheck(code *param_1)

{
  int iVar1;
  uint uVar2;
  undefined8 *puVar3;
  code *pcVar4;
  code *pcVar5;
  code *pcVar6;
  code *pcVar7;
  code *pcVar8;
  code *pcVar9;
  code *pcVar10;
  code *pcVar11;
  code *pcVar12;
  FILE *pFVar13;
  size_t sVar14;
  void *pvVar15;
  size_t sVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  undefined8 uVar22;
  char acStack_88 [32];
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_00008018;
  if (DAT_00008bd0 == (undefined *)0x0 || (int)param_1 != 0) {
    if (PTR___availability_version_check_00008020 != (undefined *)0x0) {
      DAT_00008bd0 = PTR___availability_version_check_00008020;
    }
    if (DAT_00008bd0 == (undefined *)0x0 || (int)param_1 != 0) {
      puVar3 = (undefined8 *)_dlsym(0xfffffffffffffffe,"kCFAllocatorNull");
      param_1 = (code *)0x0;
      if (puVar3 != (undefined8 *)0x0) {
        uVar22 = *puVar3;
        pcVar4 = (code *)_dlsym(0xfffffffffffffffe,"CFDataCreateWithBytesNoCopy");
        param_1 = (code *)0x0;
        if (pcVar4 != (code *)0x0) {
          pcVar5 = (code *)_dlsym(0xfffffffffffffffe,"CFPropertyListCreateWithData");
          pcVar6 = (code *)_dlsym(0xfffffffffffffffe,"CFPropertyListCreateFromXMLData");
          param_1 = pcVar6;
          if (pcVar5 != (code *)0x0 || pcVar6 != (code *)0x0) {
            pcVar7 = (code *)_dlsym(0xfffffffffffffffe,"CFStringCreateWithCStringNoCopy");
            param_1 = (code *)0x0;
            if (pcVar7 != (code *)0x0) {
              pcVar8 = (code *)_dlsym(0xfffffffffffffffe,"CFDictionaryGetValue");
              param_1 = (code *)0x0;
              if (pcVar8 != (code *)0x0) {
                pcVar9 = (code *)_dlsym(0xfffffffffffffffe,"CFGetTypeID");
                param_1 = (code *)0x0;
                if (pcVar9 != (code *)0x0) {
                  pcVar10 = (code *)_dlsym(0xfffffffffffffffe,"CFStringGetTypeID");
                  param_1 = (code *)0x0;
                  if (pcVar10 != (code *)0x0) {
                    pcVar11 = (code *)_dlsym(0xfffffffffffffffe,"CFStringGetCString");
                    param_1 = (code *)0x0;
                    if (pcVar11 != (code *)0x0) {
                      pcVar12 = (code *)_dlsym(0xfffffffffffffffe,"CFRelease");
                      param_1 = (code *)0x0;
                      if (pcVar12 != (code *)0x0) {
                        pFVar13 = _fopen("/System/Library/CoreServices/SystemVersion.plist","r");
                        param_1 = (code *)0x0;
                        if (pFVar13 != (FILE *)0x0) {
                          _fseek(pFVar13,0,2);
                          sVar14 = _ftell(pFVar13);
                          if ((long)sVar14 < 0) {
                            pvVar15 = (void *)0x0;
                          }
                          else {
                            _rewind(pFVar13);
                            pvVar15 = _malloc(sVar14);
                            if (((pvVar15 != (void *)0x0) &&
                                (sVar16 = _fread(pvVar15,1,sVar14,pFVar13), sVar16 == sVar14)) &&
                               (lVar17 = (*pcVar4)(0,pvVar15,sVar14,uVar22), lVar17 != 0)) {
                              if (pcVar5 == (code *)0x0) {
                                lVar18 = (*pcVar6)(0,lVar17,0,0);
                              }
                              else {
                                lVar18 = (*pcVar5)();
                              }
                              if (lVar18 != 0) {
                                lVar19 = (*pcVar7)(0,"ProductVersion",0x600,uVar22);
                                if (lVar19 != 0) {
                                  lVar20 = (*pcVar8)(lVar18,lVar19);
                                  (*pcVar12)(lVar19);
                                  if (lVar20 != 0) {
                                    lVar19 = (*pcVar9)(lVar20);
                                    lVar21 = (*pcVar10)();
                                    if ((lVar19 == lVar21) &&
                                       (iVar1 = (*pcVar11)(lVar20,acStack_88,0x20,0x8000100),
                                       iVar1 != 0)) {
                                      _sscanf(acStack_88,"%d.%d.%d");
                                    }
                                  }
                                }
                                (*pcVar12)(lVar18);
                              }
                              (*pcVar12)(lVar17);
                            }
                          }
                          _free(pvVar15);
                          uVar2 = _fclose(pFVar13);
                          param_1 = (code *)(ulong)uVar2;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (*(long *)PTR____stack_chk_guard_00008018 == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(param_1);
}

// ==== 00005ebc _OUTLINED_FUNCTION_0 ====
void _OUTLINED_FUNCTION_0(dispatch_once_t *param_1,undefined8 param_2,dispatch_function_t param_3)

{
  _dispatch_once_f(param_1,(void *)0x0,param_3);
  return;
}

// ==== 00005ec4 ___isPlatformVersionAtLeast.cold.1 ====
void ___isPlatformVersionAtLeast_cold_1(undefined8 param_1,undefined8 param_2)

{
  _OUTLINED_FUNCTION_0(&DAT_00008bc8,param_2,_initializeAvailabilityCheck);
  return;
}

// ==== 00005ed8 ___isPlatformVersionAtLeast.cold.2 ====
void ___isPlatformVersionAtLeast_cold_2(undefined8 param_1,undefined8 param_2)

{
  _OUTLINED_FUNCTION_0(&DAT_00008bc0,param_2,_compatibilityInitializeAvailabilityCheck);
  return;
}

// ==== 00005eec _MIDIEventListAdd ====
void _MIDIEventListAdd(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ef4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDIEventListAdd_00008820)();
  return;
}

// ==== 00005ef8 _MIDIEventListInit ====
void _MIDIEventListInit(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDIEventListInit_00008828)();
  return;
}

// ==== 00005f04 _MIDIPacketListAdd ====
void _MIDIPacketListAdd(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDIPacketListAdd_00008830)();
  return;
}

// ==== 00005f10 _MIDIPacketListInit ====
void _MIDIPacketListInit(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDIPacketListInit_00008838)();
  return;
}

// ==== 00005f1c _MIDISend ====
void _MIDISend(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDISend_00008840)();
  return;
}

// ==== 00005f28 _MIDISendEventList ====
void _MIDISendEventList(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__MIDISendEventList_00008848)();
  return;
}

// ==== 00005f34 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00005f3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_00008850)(param_1,param_2,param_3);
  return;
}

// ==== 00005f40 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005f48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_00008858)(param_1,param_2);
  return;
}

// ==== 00005f4c __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00005f54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_00008860)();
  return;
}

// ==== 00005f58 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_00008868)();
  return;
}

// ==== 00005f64 __ZdaPv ====
void __ZdaPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdaPv_00008038)();
  return;
}

// ==== 00005f70 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008040)();
  return;
}

// ==== 00005f7c __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008048)();
  return;
}

// ==== 00005f88 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_00008870)();
  return;
}

// ==== 00005f94 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00008878)();
  return;
}

// ==== 00005fa0 __availability_version_check ====
void __availability_version_check(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005fa8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___availability_version_check_00008880)();
  return;
}

// ==== 00005fac _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005fb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00008888)();
  return;
}

// ==== 00005fb8 _dispatch_once_f ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _dispatch_once_f(dispatch_once_t *predicate,void *context,dispatch_function_t function)

{
                    /* WARNING: Could not recover jumptable at 0x00005fc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_once_f_00008890)();
  return;
}

// ==== 00005fc4 _dlsym ====
void _dlsym(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005fcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dlsym_00008898)();
  return;
}

// ==== 00005fd0 _fclose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fclose(FILE *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005fd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fclose_000088a0)((int)param_1);
  return iVar1;
}

// ==== 00005fdc _fopen ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * _fopen(char *param_1,char *param_2)

{
  FILE *pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005fe4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = (FILE *)(*(code *)PTR__fopen_000088a8)();
  return pFVar1;
}

// ==== 00005fe8 _fread ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t _fread(void *param_1,size_t param_2,size_t param_3,FILE *param_4)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005ff0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = (*(code *)PTR__fread_000088b0)();
  return sVar1;
}

// ==== 00005ff4 _free ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _free(void *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00005ffc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__free_000088b8)();
  return;
}

// ==== 00006000 _fseek ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fseek(FILE *param_1,long param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006008. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fseek_000088c0)((int)param_1,param_2,param_3);
  return iVar1;
}

// ==== 0000600c _ftell ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long _ftell(FILE *param_1)

{
  long lVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006014. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar1 = (*(code *)PTR__ftell_000088c8)();
  return lVar1;
}

// ==== 00006018 _mach_absolute_time ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

uint64_t _mach_absolute_time(void)

{
  uint64_t uVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006020. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (*(code *)PTR__mach_absolute_time_000088d0)();
  return uVar1;
}

// ==== 00006024 _mach_timebase_info ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

kern_return_t _mach_timebase_info(mach_timebase_info_t info)

{
  kern_return_t kVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000602c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  kVar1 = (*(code *)PTR__mach_timebase_info_000088d8)((int)info);
  return kVar1;
}

// ==== 00006030 _malloc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _malloc(size_t param_1)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006038. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__malloc_000088e0)();
  return pvVar1;
}

// ==== 0000603c _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006044. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_000088e8)();
  return;
}

// ==== 00006048 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006050. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_000088f0)();
  return;
}

// ==== 00006054 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000605c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_000088f8)();
  return;
}

// ==== 00006060 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006068. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008900)();
  return;
}

// ==== 0000606c _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006074. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008908)();
  return;
}

// ==== 00006078 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00006080. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008910)();
  return;
}

// ==== 00006084 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000608c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008918)();
  return;
}

// ==== 00006090 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006098. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008920)();
  return IVar1;
}

// ==== 0000609c _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008928)();
  return;
}

// ==== 000060a8 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008930)();
  return;
}

// ==== 000060b4 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00008938)();
  return;
}

// ==== 000060c0 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00008940)();
  return;
}

// ==== 000060cc _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00008948)();
  return;
}

// ==== 000060d8 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00008950)();
  return;
}

// ==== 000060e4 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x000060ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00008958)();
  return;
}

// ==== 000060f0 _printf ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000060f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_00008960)((int)param_1);
  return iVar1;
}

// ==== 000060fc _pthread_once ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _pthread_once(pthread_once_t *param_1,void *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006104. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__pthread_once_00008968)((int)param_1);
  return iVar1;
}

// ==== 00006108 _puts ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _puts(char *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006110. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__puts_00008970)((int)param_1);
  return iVar1;
}

// ==== 00006114 _rewind ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _rewind(FILE *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0000611c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__rewind_00008978)();
  return;
}

// ==== 00006120 _sscanf ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _sscanf(char *param_1,char *param_2,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00006128. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__sscanf_00008980)((int)param_1);
  return iVar1;
}

// ==== 00006360 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"address");
  return IVar1;
}

// ==== 00006380 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 000063a0 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"audioBufferList");
  return IVar1;
}

// ==== 000063c0 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"busType");
  return IVar1;
}

// ==== 000063e0 objc_stub::clearCVariables ====
ID __objc_msgSend_stub objc_stub::clearCVariables(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"clearCVariables");
  return IVar1;
}

// ==== 00006400 objc_stub::count ====
ID __objc_msgSend_stub objc_stub::count(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"count");
  return IVar1;
}

// ==== 00006420 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00006440 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00006460 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"defaultFormat");
  return IVar1;
}

// ==== 00006480 objc_stub::endpointRefs ====
ID __objc_msgSend_stub objc_stub::endpointRefs(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"endpointRefs");
  return IVar1;
}

// ==== 000064a0 objc_stub::enumerateObjectsUsingBlock: ====
ID __objc_msgSend_stub objc_stub::enumerateObjectsUsingBlock_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"enumerateObjectsUsingBlock:");
  return IVar1;
}

// ==== 000064c0 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 000064e0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"format");
  return IVar1;
}

// ==== 00006500 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00006520 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00006540 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00006560 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00006580 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 000065a0 objc_stub::midiOutputPortRef ====
ID __objc_msgSend_stub objc_stub::midiOutputPortRef(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"midiOutputPortRef");
  return IVar1;
}

// ==== 000065c0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 000065e0 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"raise");
  return IVar1;
}

// ==== 00006600 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"reset");
  return IVar1;
}

// ==== 00006620 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"sampleRate");
  return IVar1;
}

// ==== 00006640 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00006660 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00006680 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 000066a0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 000066c0 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 000066e0 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00006700 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"setValue:");
  return IVar1;
}

// ==== 00006720 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00006740 objc_stub::unsignedIntValue ====
ID __objc_msgSend_stub objc_stub::unsignedIntValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"unsignedIntValue");
  return IVar1;
}

// ==== 00006760 objc_stub::updateDestinationEndpoints ====
ID __objc_msgSend_stub objc_stub::updateDestinationEndpoints(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008000)(self,"updateDestinationEndpoints");
  return IVar1;
}

// ==== 00006780 objc_stub::value ====
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

// ==== 00018903 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018904 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018905 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018906 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018907 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00018908 TrackedAUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00019400 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

