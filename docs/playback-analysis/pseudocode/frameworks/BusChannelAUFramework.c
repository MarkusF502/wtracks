// BusChannelAUFramework sha256 5692b4e9ff963e1c091bb0dcf5f1d3a867d3a5b22a5ff0eca9ff5d5b2a22006a (Ghidra 12.1.4, all decompiled functions)

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

// ==== 0000415c BusChannelAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID BusChannelAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  undefined8 *puVar3;
  ID IVar4;
  ID self_00;
  ID self_01;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
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
  undefined8 local_c8;
  ID local_b8;
  class_t *pcStack_b0;
  ID local_a8;
  ID IStack_a0;
  ID local_98;
  ID IStack_90;
  undefined8 local_88;
  undefined8 local_80;
  long local_78;
  
  local_78 = *(long *)PTR____stack_chk_guard_00008020;
  puStack_d8 = *(undefined8 **)&param_3->field2_0x8;
  local_e0._0_4_ = param_3->field0_0x0;
  local_e0._4_4_ = param_3->field1_0x4;
  local_d0 = CONCAT44(local_d0._4_4_,param_3->field4_0x10);
  pcStack_b0 = &objc::class_t::BusChannelAudioUnit;
  local_b8 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_b8,"initWithComponentDescription:options:error:",&local_e0,
                    (ulong)param_4);
  if (self != 0) {
    IVar2 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar2 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar2,0x40e5888000000000,2);
    TrackedAUAudioUnit::setDefaultFormat_(self,IVar2);
    lVar8 = (long)_dspKernel;
    if (*(long *)(self + lVar8) == 0) {
      puVar3 = (undefined8 *)__Znwm(0x50);
      *(undefined4 *)((long)puVar3 + 0x44) = 0;
      *(undefined4 *)(puVar3 + 9) = 0;
      puVar3[1] = 0;
      puVar3[2] = 0;
      *puVar3 = &DAT_00008120;
      *(undefined4 *)((long)puVar3 + 0x34) = 0x3f800000;
      *(undefined4 *)(puVar3 + 7) = 0x3f800000;
      *(undefined8 *)((long)puVar3 + 0x3c) = 0;
      *(undefined8 **)(self + lVar8) = puVar3;
    }
    lVar7 = (long)_bufferedInputBus;
    IVar2 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar7,IVar2,2);
    lVar6 = (long)_bufferedOutputBus;
    IVar2 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar6,IVar2,0x20);
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar4 = TrackedAUAudioUnit::defaultFormat(self);
    IVar2 = AUAudioUnitBus::initWithFormat_error_(IVar2,IVar4,0);
    lVar6 = (long)_auOutputBus;
    uVar5 = *(undefined8 *)(self + lVar6);
    *(ID *)(self + lVar6) = IVar2;
    IVar2 = _objc_alloc(uVar5,&_OBJC_CLASS___AUAudioUnitBusArray);
    local_80 = *(undefined8 *)(self + lVar7);
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_80,1);
    IVar2 = objc_stub::initWithAudioUnit_busType_busses_(IVar2,self,1,IVar4);
    uVar5 = *(undefined8 *)(self + (long)_auInputBusArray);
    *(ID *)(self + (long)_auInputBusArray) = IVar2;
    IVar2 = _objc_alloc(uVar5,&_OBJC_CLASS___AUAudioUnitBusArray);
    local_88 = *(undefined8 *)(self + lVar6);
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_88,1);
    IVar2 = objc_stub::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar4);
    uVar5 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,uVar5,0,0x3f800000,&cf_volumeParameter,
                       &cf_volume,0,0x1a,0,0,0,0);
    IVar4 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isMutedParameter,
                       &cf_isMuted,1,0x1a,0,0,0,0);
    self_00 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x41000000,&cf_outputChannelLParameter
                         ,&cf_outputChannelL,2,0x1a,0,0,0,0);
    self_01 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isStereoParameter,
                         &cf_isStereo,3,2,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0x3f800000);
    AUParameterTree::setValue_(IVar4,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0);
    local_a8 = IVar2;
    IStack_a0 = IVar4;
    local_98 = self_00;
    IStack_90 = self_01;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_a8,4);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    puVar1 = PTR___NSConcreteStackBlock_00008018;
    local_e0 = 0;
    local_d0 = 0x2020000000;
    local_c8 = *(undefined8 *)(self + lVar8);
    local_108 = PTR___NSConcreteStackBlock_00008018;
    local_100 = 0xc2000000;
    local_f8 = ___66__BusChannelAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_f0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_e8 = &local_e0;
    puStack_d8 = &local_e0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_108);
    local_130 = puVar1;
    local_128 = 0xc2000000;
    local_120 = 
    ___66__BusChannelAudioUnit_initWithComponentDescription_options_error___block_invoke_20;
    puStack_118 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_110 = &local_e0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_130);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar6),&___block_literal_global);
    TrackedAUAudioUnit::setMaximumFramesToRender_(self,0x200);
    __Block_object_dispose(&local_e0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008020 == local_78) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004770 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 00004804 ___66-[BusChannelAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___66__BusChannelAudioUnit_initWithComponentDescription_options_error___block_invoke
          (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN19BusChannelDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return 0;
}

// ==== 00004870 __ZN19BusChannelDSPKernel12setParameterEyf ====
void __ZN19BusChannelDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  
  if (param_3 < 2) {
    if (param_3 == 0) {
      *(float *)(param_2 + 0x34) = param_1;
      piVar1 = (int *)(param_2 + 0x44);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
    else if (param_3 == 1) {
      param_2 = param_2 + 0x20;
      goto LAB_000048b0;
    }
  }
  else {
    if (param_3 == 2) {
      *(int *)(param_2 + 0x24) = (int)param_1;
      return;
    }
    if (param_3 == 3) {
      param_2 = param_2 + 0x28;
LAB_000048b0:
      *(bool *)param_2 = param_1 != 0.0;
      return;
    }
  }
  return;
}

// ==== 000048ec ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 000048fc ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004908 ___66-[BusChannelAudioUnit_initWithComponentDescription:options:error:]_block_invoke.20 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___66__BusChannelAudioUnit_initWithComponentDescription_options_error___block_invoke_20
          (long param_1,ID param_2)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  __ZN19BusChannelDSPKernel12getParameterEy(uVar2,IVar1);
  return 0;
}

// ==== 00004978 __ZN19BusChannelDSPKernel12getParameterEy ====
float __ZN19BusChannelDSPKernel12getParameterEy(long param_1,long param_2)

{
  byte *pbVar1;
  float fVar2;
  
  fVar2 = 0.0;
  if (param_2 < 2) {
    if (param_2 == 0) {
      return *(float *)(param_1 + 0x34);
    }
    if (param_2 == 1) {
      pbVar1 = (byte *)(param_1 + 0x20);
LAB_000049ac:
      return (float)(*pbVar1 & 1);
    }
  }
  else if (param_2 == 2) {
    fVar2 = (float)*(int *)(param_1 + 0x24);
  }
  else if (param_2 == 3) {
    pbVar1 = (byte *)(param_1 + 0x28);
    goto LAB_000049ac;
  }
  return fVar2;
}

// ==== 000049dc ___66-[BusChannelAudioUnit_initWithComponentDescription:options:error:]_block_invoke.22 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___66__BusChannelAudioUnit_initWithComponentDescription_options_error___block_invoke_22
          (undefined8 param_1,ID param_2,long param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  
  if (param_3 == 0) {
    objc_stub::value(param_2);
  }
  IVar1 = objc_stub::address(param_2);
  if ((long)IVar1 < 2) {
    if (IVar1 == 0) {
      pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__f);
      return pcVar2;
    }
    if (IVar1 != 1) {
      return &cf__;
    }
  }
  else {
    if (IVar1 == 2) {
      pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__d);
      return pcVar2;
    }
    if (IVar1 != 3) {
      return &cf__;
    }
  }
  pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf___);
  return pcVar2;
}

// ==== 00004b20 BusChannelAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void BusChannelAudioUnit::reset(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::BusChannelAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined4 *)(lVar1 + 0x48) = 0;
  *(undefined4 *)(lVar1 + 0x44) = 0;
  return;
}

// ==== 00004b78 BusChannelAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void BusChannelAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = (long)_dspKernel;
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZdlPv();
  }
  *(undefined8 *)(param_1 + lVar1) = 0;
  pcStack_28 = &objc::class_t::BusChannelAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_30,"dealloc");
  return;
}

// ==== 00004bd0 BusChannelAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool BusChannelAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

{
  ID IVar1;
  ID IVar2;
  bool bVar3;
  long lVar4;
  undefined8 local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008020;
  IVar1 = objc_stub::busType(param_4);
  if (IVar1 == 1) {
    setInputFormat_(param_1,param_3);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(param_1 + (long)_bufferedInputBus,param_3,2);
  }
  else {
    IVar1 = objc_stub::busType(param_4);
    if (IVar1 != 2) {
      bVar3 = 0;
      goto LAB_00004d50;
    }
    setOutputFormat_(param_1,param_3);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(param_1 + (long)_bufferedOutputBus,param_3,0x20);
    IVar1 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    local_68 = 0;
    IVar1 = AUAudioUnitBus::initWithFormat_error_(IVar1,param_3,&local_68);
    lVar4 = (long)_auOutputBus;
    *(ID *)(param_1 + lVar4) = IVar1;
    IVar1 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_60 = *(undefined8 *)(param_1 + lVar4);
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_60,1);
    IVar1 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar1,param_1,2,IVar2);
    *(ID *)(param_1 + (long)_auOutputBusArray) = IVar1;
  }
  bVar3 = 1;
LAB_00004d50:
  if (*(long *)PTR____stack_chk_guard_00008020 == local_58) {
    return bVar3;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004de0 BusChannelAudioUnit::inputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::inputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auInputBusArray);
}

// ==== 00004df0 BusChannelAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00004e00 BusChannelAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool BusChannelAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  undefined4 uVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  long lVar5;
  double extraout_d0;
  ID local_70;
  class_t *pcStack_68;
  
  pcStack_68 = &objc::class_t::BusChannelAudioUnit;
  local_70 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_70,"allocateRenderResourcesAndReturnError:");
  if ((int)IVar2 != 0) {
    IVar2 = inputFormat(param_1);
    if (IVar2 != 0) {
      lVar5 = (long)_bufferedInputBus;
      IVar2 = objc_stub::format(*(ID *)(param_1 + lVar5));
      IVar2 = objc_stub::channelCount(IVar2);
      IVar3 = inputFormat(param_1);
      IVar3 = objc_stub::channelCount(IVar3);
      if (((int)IVar2 == (int)IVar3) && (IVar2 = outputFormat(param_1), IVar2 != 0)) {
        IVar2 = auOutputBus(param_1);
        IVar2 = objc_stub::format(IVar2);
        IVar2 = objc_stub::channelCount(IVar2);
        IVar3 = outputFormat(param_1);
        IVar3 = objc_stub::channelCount(IVar3);
        if ((int)IVar2 == (int)IVar3) {
          lVar4 = (long)_bufferedOutputBus;
          IVar2 = objc_stub::format(*(ID *)(param_1 + lVar4));
          IVar2 = objc_stub::channelCount(IVar2);
          IVar3 = outputFormat(param_1);
          IVar3 = objc_stub::channelCount(IVar3);
          if ((int)IVar2 == (int)IVar3) {
            IVar2 = objc_stub::format(*(ID *)(param_1 + lVar5));
            IVar2 = objc_stub::channelCount(IVar2);
            IVar3 = auOutputBus(param_1);
            IVar3 = objc_stub::format(IVar3);
            IVar3 = objc_stub::channelCount(IVar3);
            if ((uint)IVar2 <= (uint)IVar3) {
              IVar2 = objc_stub::maximumFramesToRender(param_1);
              __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar5,IVar2);
              IVar2 = objc_stub::maximumFramesToRender(param_1);
              __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar4,IVar2);
              lVar5 = (long)_dspKernel;
              lVar4 = *(long *)(param_1 + lVar5);
              IVar2 = defaultFormat(param_1);
              objc_stub::sampleRate(IVar2);
              *(float *)(lVar4 + 0x1c) = (float)extraout_d0;
              *(undefined1 *)(lVar4 + 0x20) = 0;
              *(undefined4 *)(lVar4 + 0x24) = 0;
              *(undefined1 *)(lVar4 + 0x28) = 1;
              *(int *)(lVar4 + 0x18) = (int)((float)extraout_d0 * 0.02);
              uVar1 = *(undefined4 *)(lVar4 + 0x34);
              *(undefined4 *)(lVar4 + 0x34) = uVar1;
              *(undefined4 *)(lVar4 + 0x38) = uVar1;
              *(undefined8 *)(lVar4 + 0x3c) = 0;
              lVar5 = *(long *)(param_1 + lVar5);
              *(undefined4 *)(lVar5 + 0x48) = 0;
              *(undefined4 *)(lVar5 + 0x44) = 0;
              return 1;
            }
          }
        }
      }
    }
    if (param_3 != (ID *)0x0) {
      IVar2 = NSError::errorWithDomain_code_userInfo_
                        ((ID)&_OBJC_CLASS___NSError,
                         *(undefined8 *)PTR__NSOSStatusErrorDomain_00008000,0xffffffffffffd585,0);
      *param_3 = IVar2;
    }
    objc_stub::setRenderResourcesAllocated_(param_1,0);
  }
  return 0;
}

// ==== 0000523c __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 000052dc BusChannelAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void BusChannelAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = param_1 + (long)_bufferedInputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  pcStack_28 = &objc::class_t::BusChannelAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_30,"deallocateRenderResources");
  return;
}

// ==== 00005338 BusChannelAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

{
  undefined *local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined *puStack_98;
  undefined8 *local_90;
  undefined8 *local_88;
  undefined1 auStack_80 [8];
  undefined8 local_78;
  undefined8 *puStack_70;
  undefined8 local_68;
  long local_60;
  undefined8 local_58;
  undefined8 *puStack_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined1 auStack_38 [8];
  
  _objc_initWeak(auStack_38,param_1);
  local_58 = 0;
  local_40 = *(undefined8 *)(param_1 + (long)_dspKernel);
  local_48 = 0x2020000000;
  local_90 = &local_78;
  local_78 = 0;
  local_68 = 0x2020000000;
  local_60 = param_1 + (long)_bufferedInputBus;
  local_b0 = PTR___NSConcreteStackBlock_00008018;
  local_a8 = 0xc2000000;
  local_a0 = ___42__BusChannelAudioUnit_internalRenderBlock__block_invoke;
  puStack_98 = &
               ___block_descriptor_56_ea8_32r40r48w_e433_i60__0_I8r__AudioTimeStamp_dQdQ_SMPTETime_ssIIIssss_II_16I24q28__AudioBufferList_I_1_AudioBuffer_II_v___36r__AURenderEvent__AURenderEventHeader___AURenderEvent_qCC__AUParameterEvent___AURenderEvent_qC_3C_IQf__AUMIDIEvent___AURenderEvent_qCCSC_3C___AUMIDIEventList___AURenderEvent_qCCC_MIDIEventList_iI_1_MIDIEventPacket_QI_64I______44__<i___I__AudioTimeStamp_dQdQ_SMPTETime_ssIIIssss_II_Iq__AudioBufferList_I[1_AudioBuffer_II_v_]_>52l
  ;
  puStack_70 = local_90;
  puStack_50 = &local_58;
  _objc_copyWeak(auStack_80,auStack_38);
  local_88 = &local_58;
  _objc_destroyWeak(auStack_80);
  __Block_object_dispose(&local_78,8);
  __Block_object_dispose(&local_58,8);
  _objc_destroyWeak(auStack_38);
  return (ID)(undefined1 *)&local_b0;
}

// ==== 0000542c ___42-[BusChannelAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___42__BusChannelAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7,undefined8 param_8)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 local_54;
  
  local_54 = 0;
  __ZN16BufferedInputBus9pullInputEPjPK14AudioTimeStampjlU13block_pointerFiS0_S3_jlP15AudioBufferListE
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),&local_54,param_3,
             param_4,0,param_8);
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x20);
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x30) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x30) + (long)BusChannelAudioUnit::_bufferedOutputBus,param_6,
               param_4,1);
  }
  lVar1 = *(long *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18);
  *(undefined8 *)(lVar1 + 8) = uVar2;
  *(long *)(lVar1 + 0x10) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005514 __ZN16BufferedInputBus9pullInputEPjPK14AudioTimeStampjlU13block_pointerFiS0_S3_jlP15AudioBufferListE ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZN16BufferedInputBus9pullInputEPjPK14AudioTimeStampjlU13block_pointerFiS0_S3_jlP15AudioBufferListE
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6)

{
  undefined8 uVar1;
  
  if (param_6 == 0) {
    uVar1 = 0xffffd584;
  }
  else {
    __ZN16BufferedInputBus22prepareInputBufferListEv(param_1);
    uVar1 = (**(code **)(param_6 + 0x10))
                      (param_6,param_2,param_3,param_4,param_5,*(undefined8 *)(param_1 + 0x20));
  }
  return uVar1;
}

// ==== 000055b4 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 0000564c ___copy_helper_block_ea8_32r40r48w ====
void ___copy_helper_block_ea8_32r40r48w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  __Block_object_assign((void *)(param_1 + 0x28),*(void **)(param_2 + 0x28),8);
  _objc_copyWeak(param_1 + 0x30,param_2 + 0x30);
  return;
}

// ==== 00005694 ___destroy_helper_block_ea8_32r40r48w ====
void ___destroy_helper_block_ea8_32r40r48w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x30);
  __Block_object_dispose(*(void **)(param_1 + 0x28),8);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 000056cc BusChannelAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 000056dc BusChannelAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000056f0 BusChannelAudioUnit::auInputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::auInputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auInputBusArray);
}

// ==== 00005700 BusChannelAudioUnit::setAuInputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setAuInputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auInputBusArray) = param_3;
  return;
}

// ==== 0000570c BusChannelAudioUnit::auOutputBus ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 0000571c BusChannelAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005728 BusChannelAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005738 BusChannelAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005744 BusChannelAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005754 BusChannelAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00005760 BusChannelAudioUnit::inputFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::inputFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_inputFormat);
}

// ==== 00005770 BusChannelAudioUnit::setInputFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setInputFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_inputFormat) = param_3;
  return;
}

// ==== 0000577c BusChannelAudioUnit::outputFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::outputFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_outputFormat);
}

// ==== 0000578c BusChannelAudioUnit::setOutputFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BusChannelAudioUnit::setOutputFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_outputFormat) = param_3;
  return;
}

// ==== 00005798 BusChannelAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void BusChannelAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_outputFormat) = 0;
  *(undefined8 *)(param_1 + (long)_inputFormat) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_auInputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005874 BusChannelAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID BusChannelAudioUnit::_cxx_construct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + (long)_bufferedInputBus);
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 1) = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = 0;
  puVar1 = (undefined8 *)(param_1 + (long)_bufferedOutputBus);
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 1) = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = 0;
  return param_1;
}

// ==== 000058b0 __ZN19BusChannelDSPKernel7processEjj ====
void __ZN19BusChannelDSPKernel7processEjj(long param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  ulong uVar2;
  long lVar3;
  uint uVar4;
  uint *puVar5;
  ulong uVar6;
  long lVar7;
  float fVar8;
  
  if ((**(int **)(param_1 + 8) == 2) &&
     (*(uint *)(param_1 + 0x24) < **(int **)(param_1 + 0x10) - (*(byte *)(param_1 + 0x28) & 1))) {
    __ZN15ParameterRamper13dezipperCheckEj(param_1 + 0x2c,*(undefined4 *)(param_1 + 0x18));
    puVar1 = *(uint **)(param_1 + 0x10);
    if (*puVar1 != 0) {
      uVar6 = 0;
      lVar7 = 0x10;
      do {
        _bzero((void *)(*(long *)((long)puVar1 + lVar7) + (ulong)param_3 * 4),(ulong)param_2 << 2);
        uVar6 = uVar6 + 1;
        puVar1 = *(uint **)(param_1 + 0x10);
        lVar7 = lVar7 + 0x10;
      } while (uVar6 < *puVar1);
    }
    if ((*(byte *)(param_1 + 0x20) & 1) == 0) {
      if ((*(byte *)(param_1 + 0x28) & 1) == 0) {
        if (param_2 != 0) {
          uVar6 = (ulong)param_2;
          do {
            if (*(uint *)(param_1 + 0x40) == 0) {
              fVar8 = *(float *)(param_1 + 0x38);
            }
            else {
              fVar8 = *(float *)(param_1 + 0x38) +
                      (float)*(uint *)(param_1 + 0x40) * *(float *)(param_1 + 0x3c);
              *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + -1;
            }
            *(float *)(*(long *)(*(long *)(param_1 + 0x10) + (long)*(int *)(param_1 + 0x24) * 0x10 +
                                0x10) + (long)(int)param_3 * 4) =
                 fVar8 * (*(float *)(*(long *)(*(long *)(param_1 + 8) + 0x10) +
                                    (long)(int)param_3 * 4) +
                         *(float *)(*(long *)(*(long *)(param_1 + 8) + 0x20) +
                                   (long)(int)param_3 * 4)) * 0.5;
            param_3 = param_3 + 1;
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0);
        }
      }
      else if (param_2 != 0) {
        uVar6 = 0;
        do {
          if (*(uint *)(param_1 + 0x40) == 0) {
            fVar8 = *(float *)(param_1 + 0x38);
          }
          else {
            fVar8 = *(float *)(param_1 + 0x38) +
                    (float)*(uint *)(param_1 + 0x40) * *(float *)(param_1 + 0x3c);
            *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + -1;
          }
          if (**(int **)(param_1 + 8) != 0) {
            uVar2 = 0;
            lVar3 = (long)(int)((int)uVar6 + param_3);
            lVar7 = 0x10;
            do {
              uVar4 = (int)uVar2 + *(int *)(param_1 + 0x24);
              puVar1 = *(uint **)(param_1 + 8);
              if (uVar4 < **(uint **)(param_1 + 0x10)) {
                *(float *)(*(long *)(*(uint **)(param_1 + 0x10) + (long)(int)uVar4 * 4 + 4) +
                          lVar3 * 4) =
                     fVar8 * *(float *)(*(long *)((long)puVar1 + lVar7) + lVar3 * 4);
              }
              uVar2 = uVar2 + 1;
              lVar7 = lVar7 + 0x10;
            } while (uVar2 < *puVar1);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 != param_2);
      }
    }
  }
  else if (param_2 != 0) {
    uVar6 = 0;
    puVar1 = *(uint **)(param_1 + 0x10);
    uVar4 = *puVar1;
    do {
      if (0 < (int)uVar4) {
        uVar2 = (ulong)uVar4;
        puVar5 = puVar1;
        do {
          puVar5 = puVar5 + 4;
          *(undefined4 *)(*(long *)puVar5 + (long)(int)((int)uVar6 + param_3) * 4) = 0;
          uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 != param_2);
  }
  return;
}

// ==== 00005b18 __ZN19BusChannelDSPKernel9startRampEyfj ====
void __ZN19BusChannelDSPKernel9startRampEyfj(float param_1,long param_2,long param_3,uint param_4)

{
  float fVar1;
  float fVar2;
  
  if (param_3 != 0) {
    return;
  }
  fVar2 = 0.0;
  if (0.0 <= param_1) {
    fVar2 = param_1;
  }
  fVar1 = 1.0;
  if (fVar2 <= 1.0) {
    fVar1 = fVar2;
  }
  if (param_4 != 0) {
    fVar2 = (float)NEON_ucvtf(*(undefined4 *)(param_2 + 0x40));
    *(float *)(param_2 + 0x3c) =
         ((*(float *)(param_2 + 0x38) + fVar2 * *(float *)(param_2 + 0x3c)) - fVar1) /
         (float)param_4;
    *(uint *)(param_2 + 0x40) = param_4;
    *(float *)(param_2 + 0x34) = fVar1;
    *(float *)(param_2 + 0x38) = fVar1;
    return;
  }
  *(float *)(param_2 + 0x34) = fVar1;
  *(float *)(param_2 + 0x38) = fVar1;
  *(undefined8 *)(param_2 + 0x3c) = 0;
  return;
}

// ==== 00005b98 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00005b9c __ZN15ParameterRamper13dezipperCheckEj ====
void __ZN15ParameterRamper13dezipperCheckEj(long param_1,uint param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  
  if (*(int *)(param_1 + 0x1c) != *(int *)(param_1 + 0x18)) {
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x18);
    pfVar1 = (float *)(param_1 + 8);
    fVar2 = *pfVar1;
    if (param_2 == 0) {
      *pfVar1 = fVar2;
      *(float *)(param_1 + 0xc) = fVar2;
      *(undefined8 *)(param_1 + 0x10) = 0;
      return;
    }
    fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x14));
    *(float *)(param_1 + 0x10) =
         ((*(float *)(param_1 + 0xc) + fVar3 * *(float *)(param_1 + 0x10)) - fVar2) / (float)param_2
    ;
    *(uint *)(param_1 + 0x14) = param_2;
    *pfVar1 = fVar2;
    *(float *)(param_1 + 0xc) = fVar2;
  }
  return;
}

// ==== 00005c10 __ZN16BufferedInputBus22prepareInputBufferListEv ====
void __ZN16BufferedInputBus22prepareInputBufferListEv(long param_1)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  
  iVar3 = *(int *)(param_1 + 8);
  puVar1 = *(uint **)(param_1 + 0x18);
  puVar2 = *(uint **)(param_1 + 0x20);
  uVar4 = *puVar1;
  uVar5 = (ulong)uVar4;
  *puVar2 = uVar4;
  if (uVar4 != 0) {
    do {
      uVar4 = puVar1[2];
      *(undefined8 *)(puVar2 + 4) = *(undefined8 *)(puVar1 + 4);
      puVar2[2] = uVar4;
      puVar2[3] = iVar3 << 2;
      uVar5 = uVar5 - 1;
      puVar1 = puVar1 + 4;
      puVar2 = puVar2 + 4;
    } while (uVar5 != 0);
  }
  return;
}

// ==== 00005c50 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00005c58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_00008820)(param_1,param_2,param_3);
  return;
}

// ==== 00005c5c __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005c64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_00008828)(param_1,param_2);
  return;
}

// ==== 00005c68 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00005c70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_00008830)();
  return;
}

// ==== 00005c74 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005c7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008030)();
  return;
}

// ==== 00005c80 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005c88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008038)();
  return;
}

// ==== 00005c8c ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005c94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00008838)();
  return;
}

// ==== 00005c98 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005ca0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00008840)();
  return;
}

// ==== 00005ca4 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_00008848)();
  return;
}

// ==== 00005cb0 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_00008850)();
  return;
}

// ==== 00005cbc _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00008858)();
  return;
}

// ==== 00005cc8 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00008860)();
  return;
}

// ==== 00005cd4 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00008868)();
  return;
}

// ==== 00005ce0 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005ce8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00008870)();
  return;
}

// ==== 00005cec _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005cf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00008878)();
  return;
}

// ==== 00005cf8 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008880)();
  return;
}

// ==== 00005d04 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005d0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008888)();
  return IVar1;
}

// ==== 00005d10 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008890)();
  return;
}

// ==== 00005d1c _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008898)();
  return;
}

// ==== 00005d28 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_000088a0)();
  return;
}

// ==== 00005d34 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_000088a8)();
  return;
}

// ==== 00005d40 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_000088b0)();
  return;
}

// ==== 00005d4c _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_000088b8)();
  return;
}

// ==== 00005d58 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005d60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_000088c0)();
  return;
}

// ==== 00005e80 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"address");
  return IVar1;
}

// ==== 00005ea0 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00005ec0 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00005ee0 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00005f00 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"busType");
  return IVar1;
}

// ==== 00005f20 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"channelCount");
  return IVar1;
}

// ==== 00005f40 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00005f60 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00005f80 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00005fa0 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00005fc0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"format");
  return IVar1;
}

// ==== 00005fe0 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00006000 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00006020 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00006040 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00006060 objc_stub::inputFormat ====
ID __objc_msgSend_stub objc_stub::inputFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"inputFormat");
  return IVar1;
}

// ==== 00006080 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 000060a0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 000060c0 objc_stub::outputFormat ====
ID __objc_msgSend_stub objc_stub::outputFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"outputFormat");
  return IVar1;
}

// ==== 000060e0 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"sampleRate");
  return IVar1;
}

// ==== 00006100 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00006120 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00006140 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00006160 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00006180 objc_stub::setInputFormat: ====
ID __objc_msgSend_stub objc_stub::setInputFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setInputFormat:");
  return IVar1;
}

// ==== 000061a0 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 000061c0 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 000061e0 objc_stub::setOutputFormat: ====
ID __objc_msgSend_stub objc_stub::setOutputFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setOutputFormat:");
  return IVar1;
}

// ==== 00006200 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00006220 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setValue:");
  return IVar1;
}

// ==== 00006240 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00006260 objc_stub::value ====
ID __objc_msgSend_stub objc_stub::value(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"value");
  return IVar1;
}

// ==== 00014101 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014201 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014301 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014302 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014303 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014401 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014501 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014601 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014701 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014801 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014901 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014902 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014903 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014904 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014905 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014906 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014907 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014908 TrackedAUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00015400 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

