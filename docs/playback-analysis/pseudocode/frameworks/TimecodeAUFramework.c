// TimecodeAUFramework sha256 ae88b748f0e40b7333c0ad34f314f8f60d55fc084a39e13a548cfa747303d7da (Ghidra 12.1.4, all decompiled functions)

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

// ==== 0000415c TimecodeAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID TimecodeAudioUnit::initWithComponentDescription_options_error_
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
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined *local_130;
  undefined8 local_128;
  code *local_120;
  undefined *puStack_118;
  undefined8 *local_110;
  undefined *local_108;
  undefined8 local_100;
  code *local_f8;
  undefined *puStack_f0;
  undefined8 *local_e8;
  undefined8 local_e0;
  undefined8 *puStack_d8;
  undefined8 local_d0;
  undefined8 *local_c8;
  ID local_b8;
  class_t *pcStack_b0;
  ID local_a8;
  ID IStack_a0;
  ID local_98;
  ID IStack_90;
  ID local_88;
  undefined8 local_80;
  long local_78;
  
  local_78 = *(long *)PTR____stack_chk_guard_00008050;
  puStack_d8 = *(undefined8 **)&param_3->field2_0x8;
  local_e0._0_4_ = param_3->field0_0x0;
  local_e0._4_4_ = param_3->field1_0x4;
  local_d0 = CONCAT44(local_d0._4_4_,param_3->field4_0x10);
  pcStack_b0 = &objc::class_t::TimecodeAudioUnit;
  local_b8 = param_1;
  self = AUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_b8,"initWithComponentDescription:options:error:",&local_e0,
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
    local_80 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_80,1);
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
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,
                         &cf_markerTimelineLocationParameter,&cf_markerTimelineLocation,2,4,0,0,0,0)
    ;
    self_01 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,
                         &cf_markerTimecodeValueParameter,&cf_markerTimecodeValue,3,4,0,0,0,0);
    self_02 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,&cf_playheadTimeParameter,
                         &cf_playheadTime,4,4,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0);
    AUParameterTree::setValue_(self_02,0);
    local_a8 = IVar2;
    IStack_a0 = IVar3;
    local_98 = self_00;
    IStack_90 = self_01;
    local_88 = self_02;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_a8,5);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    lVar5 = (long)_dspKernel;
    local_c8 = *(undefined8 **)(self + lVar5);
    if (local_c8 == (undefined8 *)0x0) {
      local_c8 = (undefined8 *)__Znwm(0x90);
      *local_c8 = &DAT_00008128;
      *(undefined4 *)(local_c8 + 1) = 0;
      local_c8[2] = 0;
      local_c8[3] = 0;
      *(undefined8 *)((long)local_c8 + 0x1e) = 0;
      local_c8[5] = 0;
      local_c8[6] = 0;
      *(undefined4 *)(local_c8 + 7) = 3;
      local_c8[9] = 0;
      local_c8[10] = 0;
      local_c8[8] = 0;
      *(undefined4 *)(local_c8 + 0xb) = 0;
      local_c8[0xd] = 0;
      local_c8[0xe] = 0;
      local_c8[0xc] = 0;
      *(undefined1 *)(local_c8 + 0xf) = 0;
      *(undefined8 *)((long)local_c8 + 0x84) = 0;
      *(undefined8 *)((long)local_c8 + 0x7c) = 0;
      *(undefined8 **)(self + lVar5) = local_c8;
    }
    puVar1 = PTR___NSConcreteStackBlock_00008048;
    local_e0 = 0;
    local_d0 = 0x2020000000;
    local_108 = PTR___NSConcreteStackBlock_00008048;
    local_100 = 0xc2000000;
    local_f8 = ___64__TimecodeAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_f0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_e8 = &local_e0;
    puStack_d8 = &local_e0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_108);
    local_130 = puVar1;
    local_128 = 0xc2000000;
    local_120 = 
    ___64__TimecodeAudioUnit_initWithComponentDescription_options_error___block_invoke_24;
    puStack_118 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_110 = &local_e0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_130);
    __Block_object_dispose(&local_e0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008050 == local_78) {
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

// ==== 000047ec ___64-[TimecodeAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___64__TimecodeAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN17TimecodeDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return;
}

// ==== 00004830 __ZN17TimecodeDSPKernel12setParameterEyf ====
void __ZN17TimecodeDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  float *pfVar1;
  
  if (param_3 < 2) {
    if (param_3 == 0) {
      param_2 = param_2 + 0x24;
    }
    else {
      if (param_3 != 1) {
        return;
      }
      param_2 = param_2 + 0x25;
    }
    *(bool *)param_2 = param_1 != 0.0;
    return;
  }
  if (param_3 == 2) {
    pfVar1 = (float *)(param_2 + 0x28);
  }
  else {
    if (param_3 != 3) {
      if (param_3 == 4) {
        *(int *)(param_2 + 0x20) = (int)(*(double *)(param_2 + 0x10) * (double)param_1);
      }
      return;
    }
    pfVar1 = (float *)(param_2 + 0x2c);
  }
  *pfVar1 = param_1;
  return;
}

// ==== 000048b4 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 000048c4 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 000048d0 ___64-[TimecodeAudioUnit_initWithComponentDescription:options:error:]_block_invoke.24 ====
void ___64__TimecodeAudioUnit_initWithComponentDescription_options_error___block_invoke_24
               (long param_1,ID param_2)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  __ZN17TimecodeDSPKernel12getParameterEy(uVar2,IVar1);
  return;
}

// ==== 00004904 __ZN17TimecodeDSPKernel12getParameterEy ====
float __ZN17TimecodeDSPKernel12getParameterEy(long param_1,long param_2)

{
  float *pfVar1;
  byte *pbVar2;
  float fVar3;
  
  fVar3 = 0.0;
  if (param_2 < 2) {
    if (param_2 == 0) {
      pbVar2 = (byte *)(param_1 + 0x24);
    }
    else {
      if (param_2 != 1) {
        return 0.0;
      }
      pbVar2 = (byte *)(param_1 + 0x25);
    }
    fVar3 = 1.0;
    if ((*pbVar2 & 1) == 0) {
      fVar3 = 0.0;
    }
    return fVar3;
  }
  if (param_2 == 2) {
    pfVar1 = (float *)(param_1 + 0x28);
  }
  else {
    if (param_2 != 3) {
      if (param_2 == 4) {
        fVar3 = (float)((double)*(int *)(param_1 + 0x20) / *(double *)(param_1 + 0x10));
      }
      return fVar3;
    }
    pfVar1 = (float *)(param_1 + 0x2c);
  }
  return *pfVar1;
}

// ==== 00004990 TimecodeAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void TimecodeAudioUnit::reset(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::TimecodeAudioUnit;
  local_30 = param_1;
  AUAudioUnit::reset((ID)&local_30,"reset");
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined1 *)(lVar1 + 0x25) = 0;
  *(undefined4 *)(lVar1 + 0x20) = 0;
  *(undefined1 *)(lVar1 + 0x78) = 0;
  *(undefined8 *)(lVar1 + 0x40) = 0;
  return;
}

// ==== 000049f4 TimecodeAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void TimecodeAudioUnit::dealloc(ID param_1,SEL param_2)

{
  SEL extraout_x1;
  undefined8 *puVar1;
  long lVar2;
  ID local_40;
  class_t *pcStack_38;
  
  lVar2 = (long)_dspKernel;
  *(undefined8 *)(*(long *)(param_1 + lVar2) + 0x18) = 0;
  puVar1 = *(undefined8 **)(param_1 + lVar2);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = &DAT_00008128;
    puVar1[3] = 0;
    if (puVar1[0xc] != 0) {
      puVar1[0xd] = puVar1[0xc];
      __ZdlPv();
      param_2 = extraout_x1;
    }
    __ZdlPv(puVar1,param_2);
  }
  *(undefined8 *)(param_1 + lVar2) = 0;
  pcStack_38 = &objc::class_t::TimecodeAudioUnit;
  local_40 = param_1;
  AUAudioUnit::dealloc((ID)&local_40,"dealloc");
  return;
}

// ==== 00004a84 TimecodeAudioUnit::configureDSPKernelWithMode:frameRate: ====
/* Function Stack Size: 0x1c bytes */

void TimecodeAudioUnit::configureDSPKernelWithMode_frameRate_
               (ID param_1,SEL param_2,unsigned_long_long param_3,unsigned_int param_4)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(unsigned_long_long *)(lVar1 + 0x30) = param_3;
  *(unsigned_int *)(lVar1 + 0x38) = param_4;
  *(undefined8 *)(lVar1 + 0x40) = 0;
  return;
}

// ==== 00004aa0 TimecodeAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x18 bytes */

void TimecodeAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,double param_3)

{
  __ZN17TimecodeDSPKernel21prepareToPlayFromTimeEd(*(undefined8 *)(param_1 + (long)_dspKernel));
  return;
}

// ==== 00004ab0 __ZN17TimecodeDSPKernel21prepareToPlayFromTimeEd ====
void __ZN17TimecodeDSPKernel21prepareToPlayFromTimeEd(double param_1,long param_2)

{
  float fVar1;
  
  *(undefined4 *)(param_2 + 0x58) = 0;
  *(int *)(param_2 + 0x20) = (int)(*(double *)(param_2 + 0x10) * param_1);
  *(undefined1 *)(param_2 + 0x78) = 0;
  *(undefined8 *)(param_2 + 0x40) = 0;
  fVar1 = *(float *)(param_2 + 0x2c);
  if ((double)*(float *)(param_2 + 0x28) <= param_1) {
    fVar1 = (float)((param_1 - (double)*(float *)(param_2 + 0x28)) +
                   (double)*(float *)(param_2 + 0x2c));
  }
  __ZN17TimecodeDSPKernel26updateSMPTECounterWithTimeEf(fVar1,param_2);
  __ZN17TimecodeDSPKernel20updateSMPTEFrameBitsEv(param_2);
  return;
}

// ==== 00004b44 TimecodeAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00004b54 TimecodeAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool TimecodeAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  undefined8 extraout_d0;
  ID local_60;
  class_t *pcStack_58;
  
  pcStack_58 = &objc::class_t::TimecodeAudioUnit;
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
      *(undefined8 *)(lVar4 + 0x40) = 0;
      *(undefined8 *)(lVar4 + 0x84) = 0;
      *(undefined8 *)(lVar4 + 0x7c) = 0;
      __ZN17TimecodeDSPKernel20updateSMPTEFrameBitsEv(lVar4);
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

// ==== 00004d8c __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00004e2c TimecodeAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void TimecodeAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  *(undefined8 *)(*(long *)(param_1 + (long)_dspKernel) + 0x18) = 0;
  pcStack_28 = &objc::class_t::TimecodeAudioUnit;
  local_30 = param_1;
  AUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 00004e98 TimecodeAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool TimecodeAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

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

// ==== 00005104 TimecodeAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_78 = ___40__TimecodeAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 000051cc ___40-[TimecodeAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___40__TimecodeAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)TimecodeAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x18) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005274 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 0000530c ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005344 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005370 TimecodeAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool TimecodeAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 00005378 TimecodeAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 00005388 TimecodeAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void TimecodeAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 0000539c TimecodeAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 000053ac TimecodeAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void TimecodeAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 000053c0 TimecodeAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 000053d0 TimecodeAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void TimecodeAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 000053dc TimecodeAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 000053ec TimecodeAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void TimecodeAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 000053f8 TimecodeAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void TimecodeAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 0000547c TimecodeAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID TimecodeAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 0000549c __ZN17TimecodeDSPKernel7processEjj ====
void __ZN17TimecodeDSPKernel7processEjj(long param_1,uint param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  bool bVar7;
  ulong uVar8;
  long *plVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (((*(byte *)(param_1 + 0x24) & 1) == 0) || ((*(byte *)(param_1 + 0x25) & 1) == 0)) {
    if (param_2 != 0) {
      uVar11 = 0;
      uVar4 = *(uint *)(param_1 + 8);
      do {
        if (0 < (int)uVar4) {
          plVar9 = *(long **)(param_1 + 0x18);
          uVar8 = (ulong)uVar4;
          do {
            plVar9 = plVar9 + 2;
            *(undefined4 *)(*plVar9 + (long)((int)uVar11 + param_3) * 4) = 0;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 != param_2);
    }
  }
  else if (*(long *)(param_1 + 0x30) == 0) {
    if (param_2 != 0) {
      uVar11 = 0;
      do {
        iVar2 = (int)uVar11 + param_3;
        uVar4 = *(uint *)(param_1 + 8);
        uVar8 = (ulong)uVar4;
        if (*(int *)(param_1 + 0x20) + (int)uVar11 <
            (int)(*(double *)(param_1 + 0x10) * (double)*(float *)(param_1 + 0x28))) {
          if (0 < (int)uVar4) {
            plVar9 = *(long **)(param_1 + 0x18);
            do {
              plVar9 = plVar9 + 2;
              *(undefined4 *)(*plVar9 + (long)iVar2 * 4) = 0;
              uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
          }
LAB_000055bc:
          *(undefined4 *)(param_1 + 0x58) = 0;
        }
        else {
          iVar5 = *(int *)(param_1 + 0x58);
          lVar3 = *(long *)(param_1 + 0x60);
          if ((int)uVar4 < 1) {
            uVar10 = *(long *)(param_1 + 0x68) - lVar3 >> 2;
          }
          else {
            uVar10 = *(long *)(param_1 + 0x68) - lVar3 >> 2;
            if (uVar10 <= (ulong)(long)iVar5) {
              __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev
                        (param_1 + 0x60);
              return;
            }
            plVar9 = *(long **)(param_1 + 0x18);
            do {
              plVar9 = plVar9 + 2;
              *(float *)(*plVar9 + (long)iVar2 * 4) = *(float *)(lVar3 + (long)iVar5 * 4) * 0.5;
              uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
          }
          *(int *)(param_1 + 0x58) = iVar5 + 1;
          if (uVar10 <= (ulong)(long)(iVar5 + 1)) {
            __ZN17TimecodeDSPKernel24incrementSMPTEFrameCountEv(param_1);
            __ZN17TimecodeDSPKernel20updateSMPTEFrameBitsEv(param_1);
            goto LAB_000055bc;
          }
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 != param_2);
    }
    piVar1 = (int *)(param_1 + 0x20);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = *piVar1 + param_2;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
  }
  return;
}

// ==== 00005648 __ZN17TimecodeDSPKernel9startRampEyfj ====
void __ZN17TimecodeDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 0000564c __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00005650 __ZN17TimecodeDSPKernel24incrementSMPTEFrameCountEv ====
void __ZN17TimecodeDSPKernel24incrementSMPTEFrameCountEv(long param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  dVar4 = (double)__ZN17TimecodeDSPKernel16rateForFrameRateE13SMPTETimeType
                            (param_1,*(undefined4 *)(param_1 + 0x38));
  uVar2 = *(uint *)(param_1 + 0x38);
  if (uVar2 < 10 && (1 << (ulong)(uVar2 & 0x1f) & 0x2b0U) != 0) {
    iVar3 = (int)dVar4;
    dVar5 = *(double *)(param_1 + 0x40);
    iVar1 = iVar3;
    if (1.0 < dVar5) {
      iVar1 = iVar3 + 1;
    }
    if (*(int *)(param_1 + 0x7c) < iVar1) {
      return;
    }
    dVar7 = (double)iVar3;
    if ((1.0 < dVar5) || (dVar4 != dVar7)) {
      dVar6 = dVar5 + -1.0;
      if (dVar5 <= 1.0) {
        dVar6 = dVar5;
      }
      dVar5 = (dVar4 - dVar7) + dVar6;
      if (dVar4 == dVar7) {
        dVar5 = dVar6;
      }
      *(double *)(param_1 + 0x40) = dVar5;
    }
  }
  else if (*(int *)(param_1 + 0x7c) < (int)dVar4) {
    return;
  }
  iVar3 = *(int *)(param_1 + 0x80);
  iVar1 = iVar3 + 1;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(int *)(param_1 + 0x80) = iVar1;
  if (iVar3 < 0x3b) {
    if (((uVar2 < 10) && ((1 << (ulong)(uVar2 & 0x1f) & 0x324U) != 0)) &&
       (0x19999998 <
        (*(int *)(param_1 + 0x84) * -0x33333333 + 0x19999998U >> 1 |
        *(int *)(param_1 + 0x84) * -0x80000000) && iVar1 == 0)) {
      *(undefined4 *)(param_1 + 0x7c) = 2;
    }
  }
  else {
    iVar3 = *(int *)(param_1 + 0x84);
    iVar1 = iVar3 + 1;
    *(undefined4 *)(param_1 + 0x80) = 0;
    *(int *)(param_1 + 0x84) = iVar1;
    if (((uVar2 < 10) && ((1 << (ulong)(uVar2 & 0x1f) & 0x324U) != 0)) &&
       (0x19999998 < (iVar1 * -0x33333333 + 0x19999998U >> 1 | iVar1 * -0x80000000))) {
      *(undefined4 *)(param_1 + 0x7c) = 2;
    }
    if (0x3a < iVar3) {
      *(undefined4 *)(param_1 + 0x84) = 0;
      *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 1;
    }
  }
  return;
}

// ==== 000057e8 __ZN17TimecodeDSPKernel20updateSMPTEFrameBitsEv ====
void __ZN17TimecodeDSPKernel20updateSMPTEFrameBitsEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar4 = 0;
  uVar1 = *(int *)(param_1 + 0x7c) / 10;
  uVar2 = *(int *)(param_1 + 0x88) / 10;
  uVar5 = *(ulong *)(param_1 + 0x48);
  do {
    uVar3 = 1L << (uVar4 & 0x3f);
    uVar6 = uVar5 | uVar3;
    uVar5 = uVar5 & (uVar3 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x7c) % 10) >> (ulong)((uint)uVar4 & 0x1f) & 1) != 0) {
      uVar5 = uVar6;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 != 4);
  uVar3 = (ulong)((uVar1 & 1) << 8);
  uVar4 = uVar5 & 0xfffffffffffffc0f | uVar3;
  if ((uVar1 & 2) != 0) {
    uVar4 = uVar5 & 0xfffffffffffffe0f | uVar3 | 0x200;
  }
  if ((*(uint *)(param_1 + 0x38) < 10) &&
     ((1 << (ulong)(*(uint *)(param_1 + 0x38) & 0x1f) & 0x324U) != 0)) {
    uVar4 = uVar4 | 0x400;
  }
  else {
    uVar4 = uVar4 & 0xfffffffffffffb0f;
  }
  uVar5 = 0;
  uVar4 = uVar4 & 0xffffffffffff07ff;
  do {
    uVar6 = 0x10000L << (uVar5 & 0x3f);
    uVar3 = uVar4 | uVar6;
    uVar4 = uVar4 & (uVar6 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x80) % 10) >> (ulong)((uint)uVar5 & 0x1f) & 1) != 0) {
      uVar4 = uVar3;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 4);
  uVar5 = 0;
  uVar4 = uVar4 & 0xffffffffff0fffff;
  do {
    uVar6 = 0x1000000L << (uVar5 & 0x3f);
    uVar3 = uVar4 | uVar6;
    uVar4 = uVar4 & (uVar6 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x80) / 10) >> (ulong)((uint)uVar5 & 0x1f) & 1) != 0) {
      uVar4 = uVar3;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 3);
  uVar5 = 0;
  uVar4 = uVar4 & 0xffffffff07ffffff;
  do {
    uVar6 = 0x100000000 << (uVar5 & 0x3f);
    uVar3 = uVar4 | uVar6;
    uVar4 = uVar4 & (uVar6 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x84) % 10) >> (ulong)((uint)uVar5 & 0x1f) & 1) != 0) {
      uVar4 = uVar3;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 4);
  uVar5 = 0;
  uVar4 = uVar4 & 0xffffff0fffffffff;
  do {
    uVar6 = 0x10000000000 << (uVar5 & 0x3f);
    uVar3 = uVar4 | uVar6;
    uVar4 = uVar4 & (uVar6 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x84) / 10) >> (ulong)((uint)uVar5 & 0x1f) & 1) != 0) {
      uVar4 = uVar3;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 3);
  uVar5 = 0;
  uVar4 = uVar4 & 0xffff07ffffffffff;
  do {
    uVar6 = 0x1000000000000 << (uVar5 & 0x3f);
    uVar3 = uVar4 | uVar6;
    uVar4 = uVar4 & (uVar6 ^ 0xffffffffffffffff);
    if (((uint)(*(int *)(param_1 + 0x88) % 10) >> (ulong)((uint)uVar5 & 0x1f) & 1) != 0) {
      uVar4 = uVar3;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 4);
  uVar5 = (ulong)(uVar2 & 1) << 0x38;
  uVar3 = uVar4 & 0xfffffffffffff | uVar5;
  if ((uVar2 & 2) != 0) {
    uVar3 = uVar4 & 0xfe0fffffffffffff | uVar5 | 0x200000000000000;
  }
  *(ulong *)(param_1 + 0x48) = uVar3 & 0x3ffffffffffffff;
  *(undefined2 *)(param_1 + 0x50) = 0xbffc;
  __ZN17TimecodeDSPKernel27generateSMPTEFrameWavetableEv();
  return;
}

// ==== 000059e8 __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev ====
void __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_out_of_rangeB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc("vector");
}

// ==== 000059fc __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc ====
void __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12out_of_rangeC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12out_of_range_00008070,PTR___ZNSt12out_of_rangeD1Ev_00008018);
}

// ==== 00005a4c __ZNSt12out_of_rangeC1B8ne190102EPKc ====
void __ZNSt12out_of_rangeC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12out_of_range_00008038 + 0x10);
  return;
}

// ==== 00005a70 __ZN17TimecodeDSPKernel16rateForFrameRateE13SMPTETimeType ====
undefined1  [16]
__ZN17TimecodeDSPKernel16rateForFrameRateE13SMPTETimeType(undefined8 param_1,uint param_2)

{
  undefined1 auVar1 [16];
  
  if (param_2 < 0xb) {
    auVar1._0_8_ = *(ulong *)(&DAT_000064e0 + (ulong)param_2 * 8);
    auVar1._8_8_ = 0;
    return auVar1;
  }
  return ZEXT816(0x4037f9dcb5112287);
}

// ==== 00005a94 __ZN17TimecodeDSPKernel27generateSMPTEFrameWavetableEv ====
void __ZN17TimecodeDSPKernel27generateSMPTEFrameWavetableEv(long param_1)

{
  ulong uVar1;
  uint uVar2;
  undefined4 *puVar3;
  byte bVar4;
  void *pvVar5;
  size_t sVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  long *plVar11;
  long lVar12;
  ulong uVar13;
  bool bVar14;
  uint uVar15;
  undefined4 *puVar16;
  double dVar17;
  double dVar18;
  undefined4 uVar19;
  undefined1 auVar20 [16];
  
  plVar11 = (long *)(param_1 + 0x60);
  *(long *)(param_1 + 0x68) = *plVar11;
  dVar17 = (double)__ZN17TimecodeDSPKernel16rateForFrameRateE13SMPTETimeType
                             (param_1,*(undefined4 *)(param_1 + 0x38));
  uVar13 = 0;
  dVar18 = *(double *)(param_1 + 0x10) / (dVar17 * 80.0);
  dVar17 = 0.0;
  do {
    uVar2 = (int)dVar17 + (int)dVar18;
    if (0 < (int)uVar2) {
      uVar15 = 0;
      bVar14 = false;
      uVar7 = *(ulong *)(param_1 + 0x48 + (uVar13 >> 3 & 0x1ffffffffffffff8));
      do {
        bVar4 = *(byte *)(param_1 + 0x78);
        if ((((uVar7 & 1L << (uVar13 & 0x3f)) != 0) && (!bVar14)) && (dVar18 * 0.5 < (double)uVar15)
           ) {
          *(byte *)(param_1 + 0x78) = bVar4 ^ 1;
          bVar4 = bVar4 == 0;
          bVar14 = true;
        }
        uVar19 = 0x3f800000;
        if ((bVar4 & 1) == 0) {
          uVar19 = 0xbf800000;
        }
        puVar3 = *(undefined4 **)(param_1 + 0x68);
        if (puVar3 < *(undefined4 **)(param_1 + 0x70)) {
          puVar16 = puVar3 + 1;
          *puVar3 = uVar19;
        }
        else {
          pvVar5 = (void *)*plVar11;
          sVar6 = (long)puVar3 - (long)pvVar5;
          lVar12 = (long)sVar6 >> 2;
          uVar1 = lVar12 + 1;
          if (uVar1 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
            __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev(plVar11);
          }
          uVar8 = (long)*(undefined4 **)(param_1 + 0x70) - (long)pvVar5;
          uVar10 = (long)uVar8 >> 1;
          if (uVar10 <= uVar1) {
            uVar10 = uVar1;
          }
          if (0x7ffffffffffffffb < uVar8) {
            uVar10 = 0x3fffffffffffffff;
          }
          if (uVar10 == 0) {
            auVar20 = ZEXT816(0);
            lVar9 = lVar12;
          }
          else {
            auVar20 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIfEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                                (param_1 + 0x70,uVar10);
            pvVar5 = *(void **)(param_1 + 0x60);
            sVar6 = *(long *)(param_1 + 0x68) - (long)pvVar5;
            lVar9 = (long)sVar6 >> 2;
          }
          puVar3 = (undefined4 *)(auVar20._0_8_ + lVar12 * 4);
          puVar16 = puVar3 + 1;
          *puVar3 = uVar19;
          _memcpy(puVar3 + -lVar9,pvVar5,sVar6);
          lVar12 = *(long *)(param_1 + 0x60);
          *(undefined4 **)(param_1 + 0x60) = puVar3 + -lVar9;
          *(undefined4 **)(param_1 + 0x68) = puVar16;
          *(long *)(param_1 + 0x70) = auVar20._0_8_ + auVar20._8_8_ * 4;
          if (lVar12 != 0) {
            __ZdlPv();
          }
        }
        *(undefined4 **)(param_1 + 0x68) = puVar16;
        uVar15 = uVar15 + 1;
      } while (uVar2 != uVar15);
    }
    if (1.0 <= dVar17) {
      dVar17 = dVar17 + -1.0;
    }
    dVar17 = (dVar18 - (double)(int)dVar18) + dVar17;
    *(byte *)(param_1 + 0x78) = *(byte *)(param_1 + 0x78) ^ 1;
    uVar13 = uVar13 + 1;
  } while (uVar13 != 0x50);
  return;
}

// ==== 00005ca8 __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__16vectorIfNS_9allocatorIfEEE20__throw_length_errorB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 00005cbc __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_00008068,PTR___ZNSt12length_errorD1Ev_00008010);
}

// ==== 00005d0c __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_00008030 + 0x10);
  return;
}

// ==== 00005d30 __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIfEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m ====
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

// ==== 00005d64 __ZSt28__throw_bad_array_new_lengthB8ne190102v ====
void __ZSt28__throw_bad_array_new_lengthB8ne190102v(void)

{
  undefined8 uVar1;
  
  ___cxa_allocate_exception(8);
  uVar1 = __ZNSt20bad_array_new_lengthC1Ev();
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt20bad_array_new_length_00008028,
               PTR___ZNSt20bad_array_new_lengthD1Ev_00008020);
}

// ==== 00005d8c __ZN17TimecodeDSPKernel26updateSMPTECounterWithTimeEf ====
void __ZN17TimecodeDSPKernel26updateSMPTECounterWithTimeEf(float param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  *(undefined8 *)(param_2 + 0x40) = 0;
  *(undefined8 *)(param_2 + 0x84) = 0;
  *(undefined8 *)(param_2 + 0x7c) = 0;
  if (0.0 <= param_1) {
    dVar3 = (double)__ZN17TimecodeDSPKernel16rateForFrameRateE13SMPTETimeType
                              (param_2,*(undefined4 *)(param_2 + 0x38));
    uVar1 = *(int *)(param_2 + 0x38) - 2;
    dVar4 = 1.0;
    if (uVar1 < 8) {
      dVar4 = *(double *)(&DAT_00006538 + (ulong)uVar1 * 8);
    }
    iVar2 = (int)(dVar4 * (double)(int)(dVar3 * (double)param_1));
    if (0 < iVar2) {
      do {
        __ZN17TimecodeDSPKernel24incrementSMPTEFrameCountEv(param_2);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

// ==== 00005e1c __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00005e24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_00008698)(param_1,param_2,param_3);
  return;
}

// ==== 00005e28 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005e30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_000086a0)(param_1,param_2);
  return;
}

// ==== 00005e34 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00005e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_000086a8)();
  return;
}

// ==== 00005e40 __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_000086b0)();
  return;
}

// ==== 00005e4c __ZNSt20bad_array_new_lengthC1Ev ====
void __ZNSt20bad_array_new_lengthC1Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt20bad_array_new_lengthC1Ev_000086b8)();
  return;
}

// ==== 00005e58 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008078)();
  return;
}

// ==== 00005e64 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008080)();
  return;
}

// ==== 00005e70 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_000086c0)();
  return;
}

// ==== 00005e7c ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_000086c8)();
  return;
}

// ==== 00005e88 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_000086d0)();
  return;
}

// ==== 00005e94 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005e9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_000086d8)();
  return;
}

// ==== 00005ea0 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005ea8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_000086e0)();
  return;
}

// ==== 00005eac _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005eb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_000086e8)();
  return pvVar1;
}

// ==== 00005eb8 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_000086f0)();
  return;
}

// ==== 00005ec4 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ecc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_000086f8)();
  return;
}

// ==== 00005ed0 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ed8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00008700)();
  return;
}

// ==== 00005edc _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ee4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00008708)();
  return;
}

// ==== 00005ee8 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ef0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008710)();
  return;
}

// ==== 00005ef4 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005efc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008718)();
  return;
}

// ==== 00005f00 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008720)();
  return;
}

// ==== 00005f0c _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008728)();
  return;
}

// ==== 00005f18 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005f20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008730)();
  return IVar1;
}

// ==== 00005f24 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008738)();
  return;
}

// ==== 00005f30 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008740)();
  return;
}

// ==== 00005f3c _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00008748)();
  return;
}

// ==== 00005f48 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00008750)();
  return;
}

// ==== 00005f54 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00008758)();
  return;
}

// ==== 00005f60 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00008760)();
  return;
}

// ==== 00005f6c _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005f74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00008768)();
  return;
}

// ==== 000060e0 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"address");
  return IVar1;
}

// ==== 00006100 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00006120 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00006140 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00006160 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"busType");
  return IVar1;
}

// ==== 00006180 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"channelCount");
  return IVar1;
}

// ==== 000061a0 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 000061c0 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 000061e0 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00006200 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00006220 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 00006240 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"format");
  return IVar1;
}

// ==== 00006260 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00006280 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 000062a0 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 000062c0 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 000062e0 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00006300 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00006320 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"raise");
  return IVar1;
}

// ==== 00006340 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"reset");
  return IVar1;
}

// ==== 00006360 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"sampleRate");
  return IVar1;
}

// ==== 00006380 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 000063a0 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 000063c0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 000063e0 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00006400 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00006420 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00006440 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setValue:");
  return IVar1;
}

// ==== 00014201 AUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014202 AUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014203 AUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014204 AUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014205 AUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014206 AUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014207 AUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014208 AUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014301 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014401 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014501 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014502 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014503 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014601 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014701 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014801 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014901 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a01 NSException::exceptionWithName:reason:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::exceptionWithName_reason_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a02 NSException::raise ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::raise(ID self,SEL op,...)

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

