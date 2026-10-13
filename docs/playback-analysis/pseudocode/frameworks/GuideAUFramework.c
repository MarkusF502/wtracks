// GuideAUFramework sha256 2522677d34ef08ac038f4dbecd8aaff5989079ac173a4a002d4c7b20b37dedd9 (Ghidra 12.1.4, all decompiled functions)

// ==== 00004000 GuideAudioUnitCue::initWithCueType:sectionTypeID:cueSequenceTimecode:songMapElementStartTimecode:cueEnabled:cueFilePath:replacementCountCueFilePath: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x40 bytes */

ID GuideAudioUnitCue::
   initWithCueType_sectionTypeID_cueSequenceTimecode_songMapElementStartTimecode_cueEnabled_cueFilePath_replacementCountCueFilePath_
             (ID param_1,SEL param_2,long_long param_3,short param_4,double param_5,double param_6,
             bool param_7,ID param_8,ID param_9)

{
  ID self;
  ID IVar1;
  double extraout_d0;
  ID local_60;
  class_t *pcStack_58;
  
  pcStack_58 = &objc::class_t::GuideAudioUnitCue;
  local_60 = param_1;
  self = NSObject::init((ID)&local_60,"init");
  if (self != 0) {
    NSObject::setCueType_(self,param_3);
    NSObject::setSectionTypeID_(self,(ulong)param_4);
    NSObject::setCueSequenceTimecode_(self,param_5);
    NSObject::cueSequenceTimecode(self);
    if ((extraout_d0 <= 0.0) && (IVar1 = NSObject::cueType(self), IVar1 == 0)) {
      NSObject::setCueSequenceTimecode_(self,0x3f50624dd2f1a9fc);
    }
    NSObject::setSongMapElementStartTimecode_(self,param_6);
    NSObject::setCueEnabled_(self,(ulong)param_7);
    NSObject::setCueFilePath_(self,param_8);
    NSObject::setReplacementCountCueFilePath_(self,param_9);
  }
  return self;
}

// ==== 00004124 GuideAudioUnitCue::cueType ====
/* Function Stack Size: 0x10 bytes */

long_long GuideAudioUnitCue::cueType(ID param_1,SEL param_2)

{
  return *(long_long *)(param_1 + 0x10);
}

// ==== 0000412c GuideAudioUnitCue::setCueType: ====
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnitCue::setCueType_(ID param_1,SEL param_2,long_long param_3)

{
  *(long_long *)(param_1 + 0x10) = param_3;
  return;
}

// ==== 00004134 GuideAudioUnitCue::sectionTypeID ====
/* Function Stack Size: 0x10 bytes */

short GuideAudioUnitCue::sectionTypeID(ID param_1,SEL param_2)

{
  return *(short *)(param_1 + 10);
}

// ==== 0000413c GuideAudioUnitCue::setSectionTypeID: ====
/* Function Stack Size: 0x14 bytes */

void GuideAudioUnitCue::setSectionTypeID_(ID param_1,SEL param_2,short param_3)

{
  *(short *)(param_1 + 10) = param_3;
  return;
}

// ==== 00004144 GuideAudioUnitCue::cueEnabled ====
/* Function Stack Size: 0x10 bytes */

bool GuideAudioUnitCue::cueEnabled(ID param_1,SEL param_2)

{
  return (bool)*(byte *)(param_1 + 8);
}

// ==== 0000414c GuideAudioUnitCue::setCueEnabled: ====
/* Function Stack Size: 0x14 bytes */

void GuideAudioUnitCue::setCueEnabled_(ID param_1,SEL param_2,bool param_3)

{
  *(char *)(param_1 + 8) = (char)param_3;
  return;
}

// ==== 00004154 GuideAudioUnitCue::cueSequenceTimecode ====
/* Function Stack Size: 0x10 bytes */

double GuideAudioUnitCue::cueSequenceTimecode(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + 0x18);
}

// ==== 0000415c GuideAudioUnitCue::setCueSequenceTimecode: ====
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnitCue::setCueSequenceTimecode_(ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + 0x18) = param_3;
  return;
}

// ==== 00004164 GuideAudioUnitCue::songMapElementStartTimecode ====
/* Function Stack Size: 0x10 bytes */

double GuideAudioUnitCue::songMapElementStartTimecode(ID param_1,SEL param_2)

{
  return *(double *)(param_1 + 0x20);
}

// ==== 0000416c GuideAudioUnitCue::setSongMapElementStartTimecode: ====
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnitCue::setSongMapElementStartTimecode_(ID param_1,SEL param_2,double param_3)

{
  *(double *)(param_1 + 0x20) = param_3;
  return;
}

// ==== 00004174 GuideAudioUnitCue::cueFilePath ====
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnitCue::cueFilePath(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + 0x28);
}

// ==== 0000417c GuideAudioUnitCue::setCueFilePath: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnitCue::setCueFilePath_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + 0x28) = param_3;
  return;
}

// ==== 00004188 GuideAudioUnitCue::replacementCountCueFilePath ====
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnitCue::replacementCountCueFilePath(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + 0x30);
}

// ==== 00004190 GuideAudioUnitCue::setReplacementCountCueFilePath: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnitCue::setReplacementCountCueFilePath_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + 0x30) = param_3;
  return;
}

// ==== 0000419c GuideAudioUnitCue::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnitCue::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}

// ==== 000041cc __ZN9DSPKernel14handleOneEventEPK13AURenderEvent ====
void __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(long *param_1,long param_2)

{
  if (*(byte *)(param_2 + 0x10) - 1 < 2) {
                    /* WARNING: Could not recover jumptable at 0x000041f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))
              (*(undefined4 *)(param_2 + 0x20),param_1,*(undefined8 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x14));
    return;
  }
  if (*(byte *)(param_2 + 0x10) == 8) {
                    /* WARNING: Could not recover jumptable at 0x00004208. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x10))();
    return;
  }
  return;
}

// ==== 00004210 __ZN9DSPKernel28performAllSimultaneousEventsExRPK13AURenderEvent ====
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

// ==== 00004264 __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent ====
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
                    /* WARNING: Could not recover jumptable at 0x0000433c. Too many branches */
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

// ==== 00004340 GuideAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID GuideAudioUnit::initWithComponentDescription_options_error_
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
  dispatch_queue_t pdVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
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
  ID local_d0;
  class_t *pcStack_c8;
  ID local_c0;
  ID IStack_b8;
  ID local_b0;
  ID IStack_a8;
  ID local_a0;
  ID IStack_98;
  ID local_90;
  undefined8 local_88;
  long local_80;
  
  local_80 = *(long *)PTR____stack_chk_guard_0000c050;
  puStack_e8 = *(undefined8 **)&param_3->field2_0x8;
  local_f0._0_4_ = param_3->field0_0x0;
  local_f0._4_4_ = param_3->field1_0x4;
  local_e0 = CONCAT44(local_e0._4_4_,param_3->field4_0x10);
  pcStack_c8 = &objc::class_t::GuideAudioUnit;
  local_d0 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_d0,"initWithComponentDescription:options:error:",&local_f0,
                    (ulong)param_4);
  if (self != 0) {
    IVar2 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar2 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar2,0x40e5888000000000,2);
    TrackedAUAudioUnit::setDefaultFormat_(self,IVar2);
    lVar6 = (long)_bufferedOutputBus;
    IVar2 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar6,IVar2,2);
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar3 = TrackedAUAudioUnit::defaultFormat(self);
    IVar2 = AUAudioUnitBus::initWithFormat_error_(IVar2,IVar3,0);
    lVar6 = (long)_auOutputBus;
    *(ID *)(self + lVar6) = IVar2;
    IVar2 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_88 = *(undefined8 *)(self + lVar6);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_88,1);
    IVar2 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar3);
    uVar5 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,uVar5,0,0x3f800000,&cf_isPlayingParameter,
                       &cf_isPlaying,0,0x1a,0,0,0,0);
    IVar3 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isMutedParameter,
                       &cf_isMuted,1,0x1a,0,0,0,0);
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
                        ((ID)&_OBJC_CLASS___AUParameterTree,0xbf800000,0x7f7fffff,
                         &cf_enqueuedSectionTypeIDParameter,&cf_enqueuedSectionTypeID,6,0x1a,0,0,0,0
                        );
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0x7f7fffff);
    AUParameterTree::setValue_(self_02,0xbf800000);
    AUParameterTree::setValue_(self_03,0xbf800000);
    AUParameterTree::setValue_(self_04,0xbf800000);
    local_c0 = IVar2;
    IStack_b8 = IVar3;
    local_b0 = self_00;
    IStack_a8 = self_01;
    local_a0 = self_02;
    IStack_98 = self_03;
    local_90 = self_04;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_c0,7);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar7 = (long)_parameterTree;
    *(ID *)(self + lVar7) = IVar2;
    lVar6 = (long)_dspKernel;
    local_d8 = *(undefined8 **)(self + lVar6);
    if (local_d8 == (undefined8 *)0x0) {
      local_d8 = (undefined8 *)__Znwm(0x160);
      *local_d8 = &DAT_0000c1a0;
      local_d8[1] = 0x472c440000000000;
      local_d8[3] = 0;
      local_d8[9] = 0;
      pdVar4 = _dispatch_queue_create("GuideDSPKernelQueue",(dispatch_queue_attr_t)0x0);
      local_d8[10] = pdVar4;
      local_d8[0x10] = 0;
      *(undefined4 *)(local_d8 + 0x19) = 0;
      *(undefined2 *)((long)local_d8 + 0xcc) = 0;
      local_d8[0x1b] = 0xffffffffffffffff;
      local_d8[0x1a] = 0x7fffffff00000000;
      *(undefined4 *)(local_d8 + 0x1c) = 0;
      *(undefined2 *)((long)local_d8 + 0xe4) = 0;
      local_d8[0x1d] = 0x3ff0000000000000;
      *(undefined4 *)(local_d8 + 0x1e) = 0;
      local_d8[0x20] = 0;
      local_d8[0x1f] = 0;
      local_d8[0x22] = 0;
      local_d8[0x21] = 0;
      uVar5 = NEON_fmov(0x3f800000,4);
      local_d8[0x23] = uVar5;
      local_d8[0x27] = 0;
      local_d8[0x2b] = 0;
      *(undefined8 **)(self + lVar6) = local_d8;
    }
    puVar1 = PTR___NSConcreteStackBlock_0000c048;
    local_f0 = 0;
    local_e0 = 0x2020000000;
    local_118 = PTR___NSConcreteStackBlock_0000c048;
    local_110 = 0xc2000000;
    local_108 = ___61__GuideAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_100 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_f8 = &local_f0;
    puStack_e8 = &local_f0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar7),&local_118);
    local_140 = puVar1;
    local_138 = 0xc2000000;
    local_130 = ___61__GuideAudioUnit_initWithComponentDescription_options_error___block_invoke_32;
    puStack_128 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_120 = &local_f0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar7),&local_140);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar7),&___block_literal_global);
    __Block_object_dispose(&local_f0,8);
  }
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_80) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004a54 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 00004ae8 ___61-[GuideAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___61__GuideAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  __ZN14GuideDSPKernel12setParameterEyf(param_1,uVar2,IVar1);
  return;
}

// ==== 00004b2c __ZN14GuideDSPKernel12setParameterEyf ====
void __ZN14GuideDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  int *piVar1;
  double dVar2;
  
  if (param_3 < 3) {
    if (param_3 == 0) {
      param_2 = param_2 + 0xcc;
    }
    else {
      if (param_3 != 1) {
        if (param_3 != 2) {
          return;
        }
        *(int *)(param_2 + 0xd0) = (int)(*(double *)(param_2 + 0x58) * (double)param_1);
        return;
      }
      param_2 = param_2 + 0xcd;
    }
    *(bool *)param_2 = param_1 != 0.0;
    return;
  }
  if (param_3 < 5) {
    if (param_3 == 3) {
      *(int *)(param_2 + 0xd4) = (int)(*(double *)(param_2 + 0x58) * (double)param_1);
      return;
    }
    if (param_3 != 4) {
      return;
    }
    dVar2 = *(double *)(param_2 + 0x58) * (double)param_1;
    piVar1 = (int *)(param_2 + 0xd8);
  }
  else {
    if (param_3 != 5) {
      if (param_3 != 6) {
        return;
      }
      *(int *)(param_2 + 0xe0) = (int)param_1;
      return;
    }
    dVar2 = *(double *)(param_2 + 0x58) * (double)param_1;
    piVar1 = (int *)(param_2 + 0xdc);
  }
  *piVar1 = (int)dVar2;
  return;
}

// ==== 00004c04 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004c14 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004c20 ___61-[GuideAudioUnit_initWithComponentDescription:options:error:]_block_invoke.32 ====
undefined1  [16]
___61__GuideAudioUnit_initWithComponentDescription_options_error___block_invoke_32
          (undefined8 param_1,ID param_2)

{
  objc_stub::address(param_2);
  return ZEXT816(0);
}

// ==== 00004c3c ___61-[GuideAudioUnit_initWithComponentDescription:options:error:]_block_invoke.34 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___61__GuideAudioUnit_initWithComponentDescription_options_error___block_invoke_34
          (undefined8 param_1,ID param_2,long param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  
  if (param_3 == 0) {
    objc_stub::value(param_2);
  }
  IVar1 = objc_stub::address(param_2);
  if ((long)IVar1 < 2) {
    if ((IVar1 != 0) && (IVar1 != 1)) {
      return &cf__;
    }
  }
  else {
    if (IVar1 - 2 < 4) {
      pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__f);
      return pcVar2;
    }
    if (IVar1 != 6) {
      return &cf__;
    }
  }
  pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__d);
  return pcVar2;
}

// ==== 00004d40 GuideAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::GuideAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  *(undefined1 *)(*(long *)(param_1 + (long)_dspKernel) + 0xcc) = 0;
  return;
}

// ==== 00004d94 GuideAudioUnit::dealloc ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  ID local_68;
  class_t *pcStack_60;
  undefined *local_58;
  undefined8 local_50;
  code *local_48;
  undefined *puStack_40;
  long local_38;
  
  lVar4 = (long)_dspKernel;
  local_38 = *(long *)(param_1 + lVar4);
  local_58 = PTR___NSConcreteStackBlock_0000c048;
  local_50 = 0xc0000000;
  local_48 = ____ZN14GuideDSPKernel7cleanupEv_block_invoke;
  puStack_40 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_38 + 0x50),&local_58);
  puVar3 = *(undefined8 **)(param_1 + lVar4);
  if (puVar3 == (undefined8 *)0x0) goto LAB_00004e84;
  *puVar3 = &DAT_0000c1a0;
  plVar1 = (long *)puVar3[0x2b];
  if (plVar1 == puVar3 + 0x28) {
    lVar2 = 0x20;
LAB_00004e2c:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004e2c;
  }
  plVar1 = (long *)puVar3[0x27];
  if (plVar1 == puVar3 + 0x24) {
    lVar2 = 0x20;
LAB_00004e58:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_00004e58;
  }
  if (puVar3[0x1f] != 0) {
    puVar3[0x20] = puVar3[0x1f];
    __ZdlPv();
  }
  __ZdlPv(puVar3);
LAB_00004e84:
  *(undefined8 *)(param_1 + lVar4) = 0;
  pcStack_60 = &objc::class_t::GuideAudioUnit;
  local_68 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_68,"dealloc");
  return;
}

// ==== 00004eb8 ___clang_call_terminate ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void ___clang_call_terminate
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,ID param_4,ID param_5,
               bool param_6)

{
  ID self;
  SEL extraout_x1;
  SEL extraout_x1_00;
  SEL extraout_x1_01;
  long lVar1;
  undefined1 auStack_88 [8];
  undefined1 auStack_80 [8];
  undefined *puStack_78;
  undefined1 auStack_70 [16];
  undefined **ppuStack_60;
  long lStack_58;
  
  ___cxa_begin_catch();
  self = __ZSt9terminatev();
  lStack_58 = *(long *)PTR____stack_chk_guard_0000c050;
  GuideAudioUnit::setFileURL_(self,param_3);
  GuideAudioUnit::setGuideTimeGrid_(self,extraout_x1,param_4);
  GuideAudioUnit::setIsRunningTest_(self,extraout_x1_00,param_6);
  GuideAudioUnit::setDelegate_(self,extraout_x1_01,param_5);
  _objc_initWeak(auStack_80,self);
  lVar1 = *(long *)(self + (long)GuideAudioUnit::_dspKernel);
  _objc_copyWeak(auStack_88,auStack_80);
  ppuStack_60 = (undefined **)0x0;
  puStack_78 = &DAT_0000c2c0;
  _objc_moveWeak(auStack_70,auStack_88);
  ppuStack_60 = &puStack_78;
  _objc_destroyWeak(auStack_88);
  __ZNSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEaSERKS6_(lVar1 + 0x140,&puStack_78);
  if (ppuStack_60 == &puStack_78) {
    lVar1 = 0x20;
  }
  else {
    if (ppuStack_60 == (undefined **)0x0) goto LAB_00004fdc;
    lVar1 = 0x28;
  }
  (**(code **)(*ppuStack_60 + lVar1))();
LAB_00004fdc:
  _objc_destroyWeak(auStack_80);
  if (*(long *)PTR____stack_chk_guard_0000c050 == lStack_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004ec8 GuideAudioUnit::configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x2c bytes */

void GuideAudioUnit::configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest_
               (ID param_1,SEL param_2,ID param_3,ID param_4,ID param_5,bool param_6)

{
  long lVar1;
  undefined1 auStack_78 [8];
  undefined1 auStack_70 [8];
  undefined *local_68;
  undefined1 auStack_60 [16];
  undefined **local_50;
  long local_48;
  
  local_48 = *(long *)PTR____stack_chk_guard_0000c050;
  setFileURL_(param_1,param_3);
  setGuideTimeGrid_(param_1,param_4);
  setIsRunningTest_(param_1,param_6);
  setDelegate_(param_1,param_5);
  _objc_initWeak(auStack_70,param_1);
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  _objc_copyWeak(auStack_78,auStack_70);
  local_50 = (undefined **)0x0;
  local_68 = &DAT_0000c2c0;
  _objc_moveWeak(auStack_60,auStack_78);
  local_50 = &local_68;
  _objc_destroyWeak(auStack_78);
  __ZNSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEaSERKS6_(lVar1 + 0x140,&local_68);
  if (local_50 == &local_68) {
    lVar1 = 0x20;
  }
  else {
    if (local_50 == (undefined **)0x0) goto LAB_00004fdc;
    lVar1 = 0x28;
  }
  (**(code **)(*local_50 + lVar1))();
LAB_00004fdc:
  _objc_destroyWeak(auStack_70);
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00005094 GuideAudioUnit::setFileURL: ====
/* Function Stack Size: 0x18 bytes */

ID __objc_msgSend_stub GuideAudioUnit::setFileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setUrl:");
  return IVar1;
}

// ==== 00005098 GuideAudioUnit::setGuideTimeGrid: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setGuideTimeGrid_(ID param_1,SEL param_2,ID param_3)

{
  undefined8 uVar1;
  long local_48;
  long local_40;
  
  setGuideCues_(param_1,param_3);
  uVar1 = *(undefined8 *)(param_1 + (long)_dspKernel);
  dspGuideCues(param_1);
  __ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE
            (uVar1,&local_48);
  if (local_48 != 0) {
    local_40 = local_48;
    __ZdlPv();
  }
  return;
}

// ==== 00005144 __ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE ====
void __ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE
               (long param_1,long *param_2)

{
  undefined8 uVar1;
  undefined *local_60;
  undefined8 local_58;
  code *local_50;
  undefined *puStack_48;
  long local_40;
  long local_38;
  long local_30;
  undefined8 uStack_28;
  
  *(undefined1 *)(param_1 + 0xe5) = 1;
  uVar1 = *(undefined8 *)(param_1 + 0x50);
  local_60 = PTR___NSConcreteStackBlock_0000c048;
  local_58 = 0xc6000000;
  local_50 = 
  ____ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE_block_invoke
  ;
  puStack_48 = &
               ___block_descriptor_64_ea8_40c53_ZTSNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEEE_e5_v8__0l
  ;
  local_38 = 0;
  local_30 = 0;
  uStack_28 = 0;
  local_40 = param_1;
  __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE16__init_with_sizeB8ne190102IPS1_S6_EEvT_T0_m
            (&local_38,*param_2,param_2[1],(param_2[1] - *param_2 >> 3) * -0x3333333333333333);
  _dispatch_async(uVar1,&local_60);
  if (local_38 != 0) {
    local_30 = local_38;
    __ZdlPv();
  }
  return;
}

// ==== 000051e8 GuideAudioUnit::prepareToPlayFromPlayheadPosition: ====
/* Function Stack Size: 0x14 bytes */

void GuideAudioUnit::prepareToPlayFromPlayheadPosition_(ID param_1,SEL param_2,int param_3)

{
  undefined *local_40;
  undefined8 local_38;
  code *local_30;
  undefined *puStack_28;
  long local_20;
  int local_18;
  undefined1 local_14;
  
  local_20 = *(long *)(param_1 + (long)_dspKernel);
  local_40 = PTR___NSConcreteStackBlock_0000c048;
  local_38 = 0xc0000000;
  local_30 = ____ZN14GuideDSPKernel13prepareToPlayEib_block_invoke;
  puStack_28 = &___block_descriptor_45_e5_v8__0l;
  local_14 = 1;
  local_18 = param_3;
  _dispatch_async(*(undefined8 *)(local_20 + 0x50),&local_40);
  return;
}

// ==== 00005254 GuideAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x14 bytes */

void GuideAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,float param_3)

{
  undefined *local_40;
  undefined8 local_38;
  code *local_30;
  undefined *puStack_28;
  long local_20;
  int local_18;
  undefined1 local_14;
  
  local_20 = *(long *)(param_1 + (long)_dspKernel);
  local_18 = (int)(*(float *)(local_20 + 0xc) * param_3);
  local_40 = PTR___NSConcreteStackBlock_0000c048;
  local_38 = 0xc0000000;
  local_30 = ____ZN14GuideDSPKernel13prepareToPlayEib_block_invoke;
  puStack_28 = &___block_descriptor_45_e5_v8__0l;
  local_14 = 1;
  _dispatch_async(*(undefined8 *)(local_20 + 0x50),&local_40);
  return;
}

// ==== 000052cc GuideAudioUnit::setChannelsGain: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setChannelsGain_(ID param_1,SEL param_2,ID param_3)

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
  *(undefined4 *)(lVar2 + 0x118) = extraout_s0;
  *(undefined4 *)(lVar2 + 0x11c) = extraout_s0_00;
  return;
}

// ==== 00005390 GuideAudioUnit::dspGuideCues ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnit::dspGuideCues
               (vector<DSPGuideCue,_std::allocator<DSPGuideCue>> *__return_storage_ptr__,ID param_1,
               SEL param_2)

{
  ID self;
  undefined *local_a0;
  undefined8 local_98;
  code *local_90;
  undefined *puStack_88;
  undefined8 *local_80;
  undefined8 local_78;
  undefined8 *local_70;
  undefined8 local_68;
  code *local_60;
  code *pcStack_58;
  char *local_50;
  long local_48;
  long local_40;
  undefined8 uStack_38;
  
  local_78 = 0;
  local_68 = 0x4812000000;
  local_60 = ___Block_byref_object_copy_;
  pcStack_58 = ___Block_byref_object_dispose_;
  local_50 = "";
  local_48 = 0;
  local_40 = 0;
  uStack_38 = 0;
  local_70 = &local_78;
  self = guideCues(param_1);
  local_a0 = PTR___NSConcreteStackBlock_0000c048;
  local_98 = 0xc2000000;
  local_90 = ___30__GuideAudioUnit_dspGuideCues__block_invoke;
  puStack_88 = &___block_descriptor_40_ea8_32r_e34_v32__0__GuideAudioUnitCue_8Q16_B24l;
  local_80 = &local_78;
  objc_stub::enumerateObjectsUsingBlock_(self,&local_a0);
  __return_storage_ptr__->field1_0x8 = (DSPGuideCue *)0x0;
  (__return_storage_ptr__->field2_0x10).field0_0x0 = (DSPGuideCue *)0x0;
  __return_storage_ptr__->field0_0x0 = (DSPGuideCue *)0x0;
  __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE16__init_with_sizeB8ne190102IPS1_S6_EEvT_T0_m
            (__return_storage_ptr__,local_70[6],local_70[7],
             ((long)(local_70[7] - local_70[6]) >> 3) * -0x3333333333333333);
  __Block_object_dispose(&local_78,8);
  if (local_48 != 0) {
    local_40 = local_48;
    __ZdlPv();
  }
  return;
}

// ==== 000054c4 ___Block_byref_object_copy_ ====
void ___Block_byref_object_copy_(long param_1,long param_2)

{
  undefined8 uVar1;
  
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  uVar1 = *(undefined8 *)(param_2 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
  *(undefined8 *)(param_1 + 0x30) = uVar1;
  *(undefined8 *)(param_1 + 0x40) = *(undefined8 *)(param_2 + 0x40);
  *(undefined8 *)(param_2 + 0x30) = 0;
  *(undefined8 *)(param_2 + 0x38) = 0;
  *(undefined8 *)(param_2 + 0x40) = 0;
  return;
}

// ==== 000054e8 ___Block_byref_object_dispose_ ====
void ___Block_byref_object_dispose_(long param_1)

{
  if (*(long *)(param_1 + 0x30) != 0) {
    *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x30);
    __ZdlPv();
    return;
  }
  return;
}

// ==== 00005500 ___30-[GuideAudioUnit_dspGuideCues]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 ___30__GuideAudioUnit_dspGuideCues__block_invoke(long param_1,ID param_2)

{
  ulong uVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  ID IVar5;
  ID IVar6;
  ID IVar7;
  size_t sVar8;
  undefined4 *puVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  void *pvVar13;
  undefined4 *puVar14;
  long lVar15;
  undefined8 extraout_d0;
  undefined8 extraout_d0_00;
  undefined1 auVar16 [16];
  
  IVar2 = objc_stub::cueType(param_2);
  IVar3 = objc_stub::sectionTypeID(param_2);
  IVar4 = objc_stub::cueEnabled(param_2);
  objc_stub::cueSequenceTimecode(param_2);
  objc_stub::songMapElementStartTimecode(param_2);
  IVar5 = objc_stub::cueFilePath(param_2);
  IVar6 = 0;
  if (IVar5 != 0) {
    IVar6 = objc_stub::cueFilePath(param_2);
    IVar6 = NSURL::fileURLWithPath_((ID)&_OBJC_CLASS___NSURL,IVar6);
  }
  IVar7 = objc_stub::replacementCountCueFilePath(param_2);
  IVar5 = 0;
  if (IVar7 != 0) {
    IVar5 = objc_stub::replacementCountCueFilePath(param_2);
    IVar5 = NSURL::fileURLWithPath_((ID)&_OBJC_CLASS___NSURL,IVar5);
  }
  lVar15 = *(long *)(*(long *)(param_1 + 0x20) + 8);
  puVar9 = *(undefined4 **)(lVar15 + 0x38);
  if (puVar9 < *(undefined4 **)(lVar15 + 0x40)) {
    *puVar9 = (int)IVar2;
    *(short *)(puVar9 + 1) = (short)IVar3;
    *(char *)((long)puVar9 + 6) = (char)IVar4;
    *(undefined1 *)((long)puVar9 + 7) = 0;
    *(undefined8 *)(puVar9 + 2) = extraout_d0;
    *(undefined8 *)(puVar9 + 4) = extraout_d0_00;
    puVar14 = puVar9 + 10;
    *(ID *)(puVar9 + 6) = IVar6;
    *(ID *)(puVar9 + 8) = IVar5;
  }
  else {
    lVar10 = (long)puVar9 - *(long *)(lVar15 + 0x30) >> 3;
    uVar1 = lVar10 * -0x3333333333333333 + 1;
    if (0x666666666666666 < uVar1) {
                    /* WARNING: Subroutine does not return */
      __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_length_errorB8ne190102Ev
                (lVar15 + 0x30);
    }
    lVar11 = (long)*(undefined4 **)(lVar15 + 0x40) - *(long *)(lVar15 + 0x30) >> 3;
    uVar12 = lVar11 * -0x6666666666666666;
    if (uVar12 < uVar1 || uVar12 - uVar1 == 0) {
      uVar12 = uVar1;
    }
    if (0x333333333333332 < (ulong)(lVar11 * -0x3333333333333333)) {
      uVar12 = 0x666666666666666;
    }
    if (uVar12 == 0) {
      auVar16 = ZEXT816(0);
    }
    else {
      auVar16 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorI11DSPGuideCueEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS6_m
                          ();
    }
    puVar9 = (undefined4 *)(auVar16._0_8_ + lVar10 * 8);
    *puVar9 = (int)IVar2;
    *(short *)(puVar9 + 1) = (short)IVar3;
    *(char *)((long)puVar9 + 6) = (char)IVar4;
    *(undefined1 *)((long)puVar9 + 7) = 0;
    *(undefined8 *)(puVar9 + 2) = extraout_d0;
    *(undefined8 *)(puVar9 + 4) = extraout_d0_00;
    *(ID *)(puVar9 + 6) = IVar6;
    *(ID *)(puVar9 + 8) = IVar5;
    puVar14 = puVar9 + 10;
    sVar8 = *(long *)(lVar15 + 0x38) - (long)*(void **)(lVar15 + 0x30);
    pvVar13 = (void *)((long)puVar9 - sVar8);
    _memcpy(pvVar13,*(void **)(lVar15 + 0x30),sVar8);
    lVar10 = *(long *)(lVar15 + 0x30);
    *(void **)(lVar15 + 0x30) = pvVar13;
    *(undefined4 **)(lVar15 + 0x38) = puVar14;
    *(long *)(lVar15 + 0x40) = auVar16._0_8_ + auVar16._8_8_ * 0x28;
    if (lVar10 != 0) {
      __ZdlPv();
    }
  }
  *(undefined4 **)(lVar15 + 0x38) = puVar14;
  return 0;
}

// ==== 00005768 GuideAudioUnit::mtDSPKernelAsVoid ====
/* Function Stack Size: 0x10 bytes */

void * GuideAudioUnit::mtDSPKernelAsVoid(ID param_1,SEL param_2)

{
  return (void *)(param_1 + (long)_dspKernel);
}

// ==== 00005778 GuideAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005788 GuideAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool GuideAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined1 auStack_c0 [8];
  undefined1 auStack_b8 [8];
  long local_b0;
  long local_a8;
  ID local_98;
  class_t *pcStack_90;
  undefined *local_88;
  undefined1 auStack_80 [16];
  undefined **local_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_0000c050;
  pcStack_90 = &objc::class_t::GuideAudioUnit;
  local_98 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_98,"allocateRenderResourcesAndReturnError:");
  bVar1 = 0;
  if ((int)IVar2 == 0) goto LAB_00005a80;
  IVar2 = auOutputBus(param_1);
  IVar2 = objc_stub::format(IVar2);
  IVar2 = objc_stub::channelCount(IVar2);
  lVar7 = (long)_bufferedOutputBus;
  IVar3 = objc_stub::format(*(ID *)(param_1 + lVar7));
  IVar3 = objc_stub::channelCount(IVar3);
  if ((int)IVar2 != (int)IVar3) {
    if (param_3 != (ID *)0x0) {
      IVar2 = NSError::errorWithDomain_code_userInfo_
                        ((ID)&_OBJC_CLASS___NSError,
                         *(undefined8 *)PTR__NSOSStatusErrorDomain_0000c000,0xffffffffffffd585,0);
      *param_3 = IVar2;
    }
    objc_stub::setRenderResourcesAllocated_(param_1,0);
    bVar1 = 0;
    goto LAB_00005a80;
  }
  IVar2 = objc_stub::maximumFramesToRender(param_1);
  __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar7,IVar2);
  lVar7 = (long)_dspKernel;
  uVar4 = *(undefined8 *)(param_1 + lVar7);
  dspGuideCues(param_1);
  __ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE
            (uVar4,&local_b0);
  if (local_b0 != 0) {
    local_a8 = local_b0;
    __ZdlPv();
  }
  IVar2 = delegate(param_1);
  if ((IVar2 != 0) && (bVar1 = isRunningTest(param_1), bVar1 != 0)) {
    _objc_initWeak(auStack_b8,param_1);
    lVar5 = *(long *)(param_1 + lVar7);
    _objc_copyWeak(auStack_c0,auStack_b8);
    local_70 = (undefined **)0x0;
    local_88 = &DAT_0000c350;
    _objc_moveWeak(auStack_80,auStack_c0);
    local_70 = &local_88;
    _objc_destroyWeak(auStack_c0);
    __ZNSt3__18functionIFvPK7__CFURLEEaSERKS5_(lVar5 + 0x120,&local_88);
    if (local_70 == &local_88) {
      lVar5 = 0x20;
LAB_00005984:
      (**(code **)(*local_70 + lVar5))();
    }
    else if (local_70 != (undefined **)0x0) {
      lVar5 = 0x28;
      goto LAB_00005984;
    }
    _objc_destroyWeak(auStack_b8);
  }
  lVar6 = *(long *)(param_1 + lVar7);
  IVar2 = auOutputBus(param_1);
  IVar2 = objc_stub::format(IVar2);
  IVar2 = objc_stub::channelCount(IVar2);
  IVar3 = auOutputBus(param_1);
  IVar3 = objc_stub::format(IVar3);
  objc_stub::sampleRate(IVar3);
  IVar3 = url(param_1);
  *(int *)(lVar6 + 8) = (int)IVar2;
  *(float *)(lVar6 + 0xc) = (float)(double)CONCAT44(extraout_var,extraout_s0);
  *(ID *)(lVar6 + 0x10) = IVar3;
  lVar7 = 0x88;
  lVar5 = 0xa8;
  do {
    *(undefined8 *)(lVar6 + lVar7) = 0;
    *(undefined4 *)(lVar6 + lVar5) = 0;
    ((undefined4 *)(lVar6 + lVar5))[4] = 0;
    lVar7 = lVar7 + 8;
    lVar5 = lVar5 + 4;
  } while (lVar7 != 0xa8);
  __ZN14GuideDSPKernel14setUpAudioFileEv(lVar6);
  reset(param_1);
  bVar1 = 1;
LAB_00005a80:
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_68) {
    return bVar1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00005ba8 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00005c48 GuideAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_58;
  class_t *pcStack_50;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  
  lVar1 = param_1 + (long)_bufferedOutputBus;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(undefined8 *)(lVar1 + 0x18) = 0;
  *(undefined8 *)(lVar1 + 0x20) = 0;
  local_28 = *(long *)(param_1 + (long)_dspKernel);
  local_48 = PTR___NSConcreteStackBlock_0000c048;
  local_40 = 0xc0000000;
  local_38 = ____ZN14GuideDSPKernel7cleanupEv_block_invoke;
  puStack_30 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_28 + 0x50),&local_48);
  pcStack_50 = &objc::class_t::GuideAudioUnit;
  local_58 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_58,"deallocateRenderResources");
  return;
}

// ==== 00005cec GuideAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_0000c048;
  local_80 = 0xc2000000;
  local_78 = ___37__GuideAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00005db4 ___37-[GuideAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___37__GuideAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)GuideAudioUnit::_bufferedOutputBus,param_6,param_4,
               1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x80) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005e5c __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00005ef4 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005f2c ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005f58 GuideAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool GuideAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 00005f60 GuideAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 00005f70 GuideAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 00005f84 GuideAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 00005fa4 GuideAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 00005fb8 GuideAudioUnit::auOutputBus ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005fc8 GuideAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005fd4 GuideAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005fe4 GuideAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005ff0 GuideAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00006000 GuideAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 0000600c GuideAudioUnit::url ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::url(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_url);
}

// ==== 0000601c GuideAudioUnit::setUrl: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setUrl_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_url) = param_3;
  return;
}

// ==== 00006028 GuideAudioUnit::isRunningTest ====
/* Function Stack Size: 0x10 bytes */

bool GuideAudioUnit::isRunningTest(ID param_1,SEL param_2)

{
  return (bool)*(byte *)(param_1 + (long)_isRunningTest);
}

// ==== 00006038 GuideAudioUnit::setIsRunningTest: ====
/* Function Stack Size: 0x14 bytes */

void GuideAudioUnit::setIsRunningTest_(ID param_1,SEL param_2,bool param_3)

{
  *(char *)(param_1 + (long)_isRunningTest) = (char)param_3;
  return;
}

// ==== 00006048 GuideAudioUnit::guideCues ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::guideCues(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_guideCues);
}

// ==== 00006058 GuideAudioUnit::setGuideCues: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void GuideAudioUnit::setGuideCues_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_guideCues) = param_3;
  return;
}

// ==== 00006064 GuideAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void GuideAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_guideCues) = 0;
  *(undefined8 *)(param_1 + (long)_url) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00006120 GuideAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID GuideAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00006140 __ZN14GuideDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN14GuideDSPKernel7processEjjPK14AudioTimeStamp(long param_1,uint param_2,int param_3)

{
  ulong *puVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined *puVar7;
  int iVar8;
  long lVar9;
  int *piVar10;
  ulong uVar11;
  int *piVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  long *plVar16;
  float *pfVar17;
  ulong uVar18;
  float fVar19;
  float fVar20;
  undefined *local_c0;
  undefined8 local_b8;
  code *local_b0;
  undefined *puStack_a8;
  long local_a0;
  long lStack_98;
  undefined1 local_90;
  uint local_88 [4];
  long local_78;
  
  local_78 = *(long *)PTR____stack_chk_guard_0000c050;
  if ((*(byte *)(param_1 + 0xcc) & 1) == 0) {
    if (param_2 != 0) {
      uVar18 = 0;
      uVar2 = *(uint *)(param_1 + 8);
      do {
        if (0 < (int)uVar2) {
          plVar16 = *(long **)(param_1 + 0x80);
          uVar11 = (ulong)uVar2;
          pfVar17 = (float *)(param_1 + 0x118);
          do {
            plVar16 = plVar16 + 2;
            *(float *)(*plVar16 + (long)((int)uVar18 + param_3) * 4) = *pfVar17 * 0.0;
            uVar11 = uVar11 - 1;
            pfVar17 = pfVar17 + 1;
          } while (uVar11 != 0);
        }
        uVar18 = uVar18 + 1;
      } while (uVar18 != param_2);
    }
  }
  else {
    lVar9 = 0;
    do {
      uVar5 = *(int *)(param_1 + lVar9 + 0xa8) - *(int *)(param_1 + lVar9 + 0xb8);
      uVar2 = 0;
      if (*(int *)(param_1 + 8) != 0) {
        uVar2 = (int)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU)) / *(int *)(param_1 + 8);
      }
      if (param_2 <= uVar2) {
        uVar2 = param_2;
      }
      *(uint *)((long)local_88 + lVar9) = uVar2;
      lVar9 = lVar9 + 4;
    } while (lVar9 != 0x10);
    if (param_2 != 0) {
      uVar18 = 0;
      puVar1 = (ulong *)(param_1 + 0x110);
      puVar7 = PTR___NSConcreteStackBlock_0000c048;
      do {
        if (0 < *(int *)(param_1 + 8)) {
          lVar9 = 0;
          fVar19 = 0.0;
          do {
            lVar14 = 0;
            do {
              if ((long)uVar18 < (long)(int)local_88[lVar14]) {
                piVar10 = (int *)(param_1 + 0xb8 + lVar14 * 4);
                fVar20 = 0.0;
                if (((*(byte *)(param_1 + 0xcd) & 1) == 0) &&
                   (lVar15 = *(long *)(param_1 + 0x88 + lVar14 * 8), fVar20 = fVar19, lVar15 != 0))
                {
                  fVar20 = fVar19 + *(float *)(lVar15 + (long)*piVar10 * 4);
                }
                fVar19 = fVar20;
                if (*piVar10 < *(int *)(param_1 + 0xa8 + lVar14 * 4) + -1) {
                  do {
                    cVar3 = '\x01';
                    bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                    if (bVar4) {
                      *piVar10 = *piVar10 + 1;
                      cVar3 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar3 != '\0');
                }
              }
              lVar14 = lVar14 + 1;
            } while (lVar14 != 4);
            *(float *)(*(long *)(*(long *)(param_1 + 0x80) + lVar9 * 0x10 + 0x10) +
                      (long)((int)uVar18 + param_3) * 4) =
                 fVar19 * *(float *)(param_1 + 0x118 + lVar9 * 4);
            lVar9 = lVar9 + 1;
          } while (lVar9 < *(int *)(param_1 + 8));
        }
        if ((*(byte *)(param_1 + 0xe5) & 1) == 0) {
          piVar10 = (int *)(*(long *)(param_1 + 0xf8) + *(long *)(param_1 + 0x110) * 0x28);
          if (*piVar10 == 1) {
            if ((*(int *)(param_1 + 0xd8) != -1) && (*(int *)(param_1 + 0xdc) != -1)) {
              lVar9 = *(long *)(param_1 + 0xf8);
              lVar14 = *(long *)(param_1 + 0x100);
              if (lVar14 != lVar9) {
                lVar15 = 0;
                uVar11 = 0;
                do {
                  if ((*(byte *)(param_1 + 0xe4) & 1) != 0) break;
                  if (*(int *)(lVar9 + lVar15) != 0) {
                    uVar5 = (int)(*(double *)(lVar9 + lVar15 + 0x10) *
                                 (double)*(float *)(param_1 + 0xc)) - *(int *)(param_1 + 0xd8);
                    uVar2 = -uVar5;
                    if (-1 < (int)uVar5) {
                      uVar2 = uVar5;
                    }
                    if (uVar2 < 10) {
                      *(undefined1 *)(param_1 + 0xe4) = 1;
                      goto LAB_00006408;
                    }
                    lVar9 = *(long *)(param_1 + 0xf8);
                    lVar14 = *(long *)(param_1 + 0x100);
                  }
                  uVar11 = uVar11 + 1;
                  uVar13 = (lVar14 - lVar9 >> 3) * -0x3333333333333333;
                  lVar15 = lVar15 + 0x28;
                } while (uVar11 <= uVar13 && uVar13 - uVar11 != 0);
              }
            }
          }
          else if (((*piVar10 == 0) &&
                   ((((short)piVar10[1] == 7 ||
                     ((*(int *)(param_1 + 0xd8) != -1 && (*(int *)(param_1 + 0xdc) != -1)))) &&
                    ((int)(*(double *)(piVar10 + 2) * (double)*(float *)(param_1 + 0xc)) <=
                     *(int *)(param_1 + 0xf0) + (int)uVar18)))) &&
                  (uVar11 = *puVar1, uVar11 != 0xffffffffffffffff)) {
LAB_00006408:
            lVar9 = *(long *)(param_1 + 0xf8);
            uVar13 = (*(long *)(param_1 + 0x100) - lVar9 >> 3) * -0x3333333333333333;
            lVar14 = uVar13 - uVar11;
            if (uVar11 <= uVar13 && lVar14 != 0) {
              piVar10 = (int *)(lVar9 + uVar11 * 0x28);
              if (*piVar10 == 0) {
                if (((short)piVar10[1] != 7) ||
                   (*(int *)(param_1 + 0xd8) != *(int *)(param_1 + 0xd0))) goto LAB_00006478;
LAB_0000651c:
                if (*(long *)(piVar10 + 8) != 0) {
                  uVar6 = *(undefined8 *)(param_1 + 0x50);
                  lStack_98 = *(long *)(piVar10 + 8);
                  goto LAB_00006490;
                }
              }
              else {
                if (*piVar10 == 1) {
                  piVar12 = (int *)(lVar9 + uVar11 * 0x28);
                  do {
                    if (*piVar12 == 1) {
                      if ((*(byte *)((long)piVar12 + 6) & 1) == 0) goto LAB_0000651c;
                      break;
                    }
                    piVar12 = piVar12 + 10;
                    lVar14 = lVar14 + -1;
                  } while (lVar14 != 0);
                }
LAB_00006478:
                if (*(long *)(piVar10 + 6) != 0) {
                  uVar6 = *(undefined8 *)(param_1 + 0x50);
                  lStack_98 = *(long *)(piVar10 + 6);
LAB_00006490:
                  local_b8 = 0xc0000000;
                  puStack_a8 = &___block_descriptor_49_e5_v8__0l;
                  local_b0 = ____ZN14GuideDSPKernel20updateFileURLAndPlayEPK7__CFURLb_block_invoke;
                  local_90 = 1;
                  local_c0 = puVar7;
                  local_a0 = param_1;
                  _dispatch_async(uVar6,&local_c0);
                  puVar7 = PTR___NSConcreteStackBlock_0000c048;
                }
              }
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                if (bVar4) {
                  *puVar1 = *puVar1 + 1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              uVar11 = (*(long *)(param_1 + 0x100) - *(long *)(param_1 + 0xf8) >> 3) *
                       -0x3333333333333333;
              if (uVar11 <= *(ulong *)(param_1 + 0x110)) {
                *puVar1 = uVar11 - 1;
              }
            }
          }
        }
        uVar18 = uVar18 + 1;
      } while (uVar18 != param_2);
    }
    piVar10 = (int *)(param_1 + 0xf0);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = *piVar10 + param_2;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (*(int *)(param_1 + 0xd4) < *(int *)(param_1 + 0xf0)) {
      iVar8 = *(int *)(param_1 + 0xf0) - *(int *)(param_1 + 0xd4);
      if ((*(int *)(param_1 + 0xd8) == -1) || (piVar10 = (int *)(param_1 + 0xdc), *piVar10 == -1)) {
        iVar8 = *(int *)(param_1 + 0xd0) + iVar8;
        piVar10 = (int *)(param_1 + 0xf0);
      }
      else {
        *(undefined1 *)(param_1 + 0xe4) = 0;
        piVar12 = (int *)(param_1 + 0xd8);
        *(int *)(param_1 + 0xf0) = *piVar12 + iVar8;
        *(int *)(param_1 + 0xd0) = *piVar12;
        *(int *)(param_1 + 0xd4) = *piVar10;
        iVar8 = -1;
        *piVar12 = -1;
      }
      *piVar10 = iVar8;
      __ZN14GuideDSPKernel23resetGuideCuesNextIndexEv(param_1);
    }
  }
  if (*(long *)PTR____stack_chk_guard_0000c050 != local_78) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

// ==== 00006674 __ZN14GuideDSPKernel9startRampEyfj ====
void __ZN14GuideDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00006678 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 0000667c __ZN14GuideDSPKernel23resetGuideCuesNextIndexEv ====
void __ZN14GuideDSPKernel23resetGuideCuesNextIndexEv(long param_1)

{
  ulong *puVar1;
  char cVar2;
  bool bVar3;
  code *pcVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  
  puVar1 = (ulong *)(param_1 + 0x110);
  *puVar1 = 0;
  uVar7 = *puVar1;
  lVar8 = *(long *)(param_1 + 0xf8);
  uVar5 = (*(long *)(param_1 + 0x100) - lVar8 >> 3) * -0x3333333333333333;
  if (uVar7 <= uVar5 && uVar5 - uVar7 != 0) {
    do {
      iVar6 = (int)((double)(int)((double)*(float *)(param_1 + 0xc) * 0.05) +
                   (double)*(float *)(param_1 + 0xc) * *(double *)(lVar8 + uVar7 * 0x28 + 8));
      if (((*(int *)(param_1 + 0xf0) <= iVar6) && (iVar6 < *(int *)(param_1 + 0xd4))) ||
         ((*(long *)(param_1 + 0x100) - *(long *)(param_1 + 0xf8) >> 3) * -0x3333333333333333 - 1U
          <= *(ulong *)(param_1 + 0x110))) {
        return;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(puVar1,0x10);
        if (bVar3) {
          *puVar1 = *puVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar7 = *(ulong *)(param_1 + 0x110);
      lVar8 = *(long *)(param_1 + 0xf8);
      uVar5 = (*(long *)(param_1 + 0x100) - lVar8 >> 3) * -0x3333333333333333;
    } while (uVar7 <= uVar5 && uVar5 - uVar7 != 0);
  }
  __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_out_of_rangeB8ne190102Ev
            ((long *)(param_1 + 0xf8));
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(1,0x6760);
  (*pcVar4)();
}

// ==== 00006780 ____ZN14GuideDSPKernel20updateFileURLAndPlayEPK7__CFURLb_block_invoke ====
void ____ZN14GuideDSPKernel20updateFileURLAndPlayEPK7__CFURLb_block_invoke(long param_1)

{
  int *piVar1;
  long lVar2;
  long *plVar3;
  undefined8 local_38;
  
  lVar2 = *(long *)(param_1 + 0x20);
  *(undefined8 *)(lVar2 + 0x10) = *(undefined8 *)(param_1 + 0x28);
  piVar1 = (int *)(lVar2 + 0xb8 + (long)*(int *)(lVar2 + 200) * 4);
  *piVar1 = *(int *)(lVar2 + (long)*(int *)(lVar2 + 200) * 4 + 0xa8) + -1;
  __ZN14GuideDSPKernel14setUpAudioFileEv(lVar2);
  if (*(char *)(param_1 + 0x30) == '\x01') {
    *piVar1 = 0;
    plVar3 = *(long **)(lVar2 + 0x138);
    if (plVar3 != (long *)0x0) {
      local_38 = *(undefined8 *)(lVar2 + 0x10);
      (**(code **)(*plVar3 + 0x30))(plVar3,&local_38);
    }
  }
  return;
}

// ==== 0000680c __ZN14GuideDSPKernel14setUpAudioFileEv ====
/* WARNING: Type propagation algorithm not settling */

void __ZN14GuideDSPKernel14setUpAudioFileEv(long param_1)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  undefined8 uVar5;
  void *pvVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int iVar10;
  long *plVar11;
  undefined4 local_50 [2];
  undefined4 local_48;
  undefined4 uStack_44;
  void *local_40;
  int local_38 [2];
  
  plVar11 = (long *)(param_1 + 0x18);
  if (*plVar11 != 0) {
    _ExtAudioFileDispose();
    *plVar11 = 0;
  }
  uVar5 = _ExtAudioFileOpenURL(*(undefined8 *)(param_1 + 0x10),plVar11);
  if ((int)uVar5 == 0) {
    uVar5 = _ExtAudioFileSeek(*plVar11,0);
    if ((int)uVar5 == 0) {
      local_38[1] = 0x28;
      uVar5 = _ExtAudioFileGetProperty
                        (*(undefined8 *)(param_1 + 0x18),0x66666d74,local_38 + 1,param_1 + 0x20);
      if ((int)uVar5 == 0) {
        *(double *)(param_1 + 0x58) = (double)*(float *)(param_1 + 0xc);
        *(undefined8 *)(param_1 + 0x60) = 0x16c70636d;
        iVar10 = *(int *)(param_1 + 8) << 2;
        *(int *)(param_1 + 0x74) = *(int *)(param_1 + 8);
        *(undefined4 *)(param_1 + 0x78) = 0x20;
        *(undefined4 *)(param_1 + 0x6c) = 1;
        *(int *)(param_1 + 0x70) = iVar10;
        *(int *)(param_1 + 0x68) = iVar10;
        local_38[1] = 0x28;
        uVar5 = _ExtAudioFileSetProperty(*(undefined8 *)(param_1 + 0x18),0x63666d74,0x28);
        if ((int)uVar5 == 0) {
          local_38[1] = 8;
          uVar5 = _ExtAudioFileGetProperty
                            (*(undefined8 *)(param_1 + 0x18),0x2366726d,local_38 + 1,param_1 + 0x48)
          ;
          if ((int)uVar5 == 0) {
            *(double *)(param_1 + 0xe8) = *(double *)(param_1 + 0x20) / *(double *)(param_1 + 0x58);
            iVar10 = *(int *)(param_1 + 0x48);
            uVar3 = *(int *)(param_1 + 0x3c) * iVar10;
            uVar4 = (ulong)uVar3 << 2;
            pvVar6 = _malloc(-(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | uVar4);
            local_48 = *(undefined4 *)(param_1 + 0x74);
            local_50[0] = 1;
            uStack_44 = (undefined4)uVar4;
            local_40 = pvVar6;
            local_38[0] = iVar10;
            uVar5 = _ExtAudioFileRead(*(undefined8 *)(param_1 + 0x18),local_38,local_50);
            if ((int)uVar5 == 0) {
              iVar10 = *(int *)(param_1 + 0x3c);
              *(int *)(param_1 + (long)*(int *)(param_1 + 200) * 4 + 0xb8) =
                   *(int *)(param_1 + 0xa8 + (long)*(int *)(param_1 + 200) * 4) + -1;
              iVar2 = *(int *)(param_1 + 200);
              lVar1 = param_1 + (long)iVar2 * 8;
              lVar7 = *(long *)(lVar1 + 0x88);
              *(void **)(lVar1 + 0x88) = pvVar6;
              *(int *)(param_1 + 0xa8 + (long)iVar2 * 4) = iVar10 * local_38[0];
              if (lVar7 != 0) {
                __ZdaPv();
              }
              iVar2 = *(int *)(param_1 + 200);
              iVar10 = 3;
              if (iVar2 + 1 < 3) {
                iVar10 = iVar2 + 1;
              }
              *(uint *)(param_1 + 200) = (iVar2 + 1) - ((iVar2 - iVar10) + 4U & 0xfffffffc);
              return;
            }
            if (*(long *)(param_1 + 0x158) == 0) {
              return;
            }
            uVar9 = *(undefined8 *)(param_1 + 0x10);
            uVar8 = 2;
          }
          else {
            if (*(long *)(param_1 + 0x158) == 0) {
              return;
            }
            uVar9 = *(undefined8 *)(param_1 + 0x10);
            uVar8 = 5;
          }
        }
        else {
          if (*(long *)(param_1 + 0x158) == 0) {
            return;
          }
          uVar9 = *(undefined8 *)(param_1 + 0x10);
          uVar8 = 6;
        }
      }
      else {
        if (*(long *)(param_1 + 0x158) == 0) {
          return;
        }
        uVar9 = *(undefined8 *)(param_1 + 0x10);
        uVar8 = 4;
      }
      __ZNKSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEclEiS1_S4_
                (param_1 + 0x140,uVar5,uVar8,uVar9);
      return;
    }
    if (*(long *)(param_1 + 0x158) == 0) {
      return;
    }
    uVar9 = *(undefined8 *)(param_1 + 0x10);
    uVar8 = 3;
  }
  else {
    if (*(long *)(param_1 + 0x158) == 0) {
      return;
    }
    uVar9 = *(undefined8 *)(param_1 + 0x10);
    uVar8 = 1;
  }
  __ZNKSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEclEiS1_S4_
            (param_1 + 0x140,uVar5,uVar8,uVar9);
  return;
}

// ==== 00006a90 __ZNKSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEclEiS1_S4_ ====
void __ZNKSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEclEiS1_S4_
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

// ==== 00006ad8 __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_0000c228;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00006b0c __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 00006b10 __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 00006b24 __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_out_of_rangeB8ne190102Ev ====
void __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_out_of_rangeB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc("vector");
}

// ==== 00006b38 __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc ====
void __ZNSt3__120__throw_out_of_rangeB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12out_of_rangeC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12out_of_range_0000c070,PTR___ZNSt12out_of_rangeD1Ev_0000c018);
}

// ==== 00006b88 __ZNSt12out_of_rangeC1B8ne190102EPKc ====
void __ZNSt12out_of_rangeC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12out_of_range_0000c038 + 0x10);
  return;
}

// ==== 00006bac ____ZN14GuideDSPKernel7cleanupEv_block_invoke ====
void ____ZN14GuideDSPKernel7cleanupEv_block_invoke(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  lVar3 = 0;
  lVar2 = *(long *)(param_1 + 0x20);
  do {
    lVar1 = lVar2 + lVar3 * 8;
    if (*(long *)(lVar1 + 0x88) != 0) {
      __ZdaPv();
      *(undefined4 *)(lVar2 + lVar3 * 4 + 0xa8) = 0;
      *(undefined8 *)(lVar1 + 0x88) = 0;
    }
    lVar3 = lVar3 + 1;
  } while (lVar3 != 4);
  if (*(long *)(lVar2 + 0x18) != 0) {
    _ExtAudioFileDispose();
    *(undefined8 *)(lVar2 + 0x18) = 0;
  }
  __ZN14GuideDSPKernel16releaseGuideCuesEv(lVar2);
  return;
}

// ==== 00006c14 __ZN14GuideDSPKernel16releaseGuideCuesEv ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

long __ZN14GuideDSPKernel16releaseGuideCuesEv(long param_1)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  
  lVar2 = *(long *)(param_1 + 0xf8);
  lVar1 = param_1;
  if (*(long *)(param_1 + 0x100) != lVar2) {
    uVar4 = 0;
    do {
      lVar1 = 0;
      uVar4 = uVar4 + 1;
      lVar2 = *(long *)(param_1 + 0xf8);
      uVar3 = (*(long *)(param_1 + 0x100) - lVar2 >> 3) * -0x3333333333333333;
    } while (uVar4 <= uVar3 && uVar3 - uVar4 != 0);
  }
  *(long *)(param_1 + 0x100) = lVar2;
  return lVar1;
}

// ==== 00006c9c __ZNSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEaSERKS6_ ====
undefined8 __ZNSt3__18functionIFvi18GuideFileOperationPK7__CFURLEEaSERKS6_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c050;
  __ZNSt3__110__function12__value_funcIFvPK7__CFURLEEC2B8ne190102ERKS6_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvi18GuideFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
            (alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00006d00;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00006d00:
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00006d30 __ZNSt3__110__function12__value_funcIFvPK7__CFURLEEC2B8ne190102ERKS6_ ====
long __ZNSt3__110__function12__value_funcIFvPK7__CFURLEEC2B8ne190102ERKS6_
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

// ==== 00006d94 __ZNSt3__110__function12__value_funcIFvi18GuideFileOperationPK7__CFURLEE4swapB8ne190102ERS7_ ====
void __ZNSt3__110__function12__value_funcIFvi18GuideFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c050;
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
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00006f00 ____ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE_block_invoke ====
void ____ZN14GuideDSPKernel15updateGuideCuesENSt3__16vectorI11DSPGuideCueNS0_9allocatorIS2_EEEE_block_invoke
               (long param_1)

{
  long lVar1;
  undefined *local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  long local_30;
  undefined4 local_28;
  undefined1 local_24;
  
  lVar1 = *(long *)(param_1 + 0x20);
  __ZN14GuideDSPKernel16releaseGuideCuesEv(lVar1);
  if (lVar1 + 0xf8 != param_1 + 0x28) {
    __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE18__assign_with_sizeB8ne190102IPS1_S6_EEvT_T0_l
              ();
  }
  local_28 = *(undefined4 *)(lVar1 + 0xf0);
  local_50 = PTR___NSConcreteStackBlock_0000c048;
  local_48 = 0xc0000000;
  local_40 = ____ZN14GuideDSPKernel13prepareToPlayEib_block_invoke;
  puStack_38 = &___block_descriptor_45_e5_v8__0l;
  local_24 = 0;
  local_30 = lVar1;
  _dispatch_async(*(undefined8 *)(lVar1 + 0x50),&local_50);
  return;
}

// ==== 00006fa8 ___copy_helper_block_ea8_40c53_ZTSNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEEE ====
void ___copy_helper_block_ea8_40c53_ZTSNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEEE
               (long param_1,long param_2)

{
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE16__init_with_sizeB8ne190102IPS1_S6_EEvT_T0_m
            ((undefined8 *)(param_1 + 0x28),*(long *)(param_2 + 0x28),*(long *)(param_2 + 0x30),
             (*(long *)(param_2 + 0x30) - *(long *)(param_2 + 0x28) >> 3) * -0x3333333333333333);
  return;
}

// ==== 00006fd0 ___destroy_helper_block_ea8_40c53_ZTSNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEEE ====
void ___destroy_helper_block_ea8_40c53_ZTSNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEEE
               (long param_1)

{
  if (*(long *)(param_1 + 0x28) != 0) {
    *(long *)(param_1 + 0x30) = *(long *)(param_1 + 0x28);
    __ZdlPv();
    return;
  }
  return;
}

// ==== 00006fe8 __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE18__assign_with_sizeB8ne190102IPS1_S6_EEvT_T0_l ====
void __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE18__assign_with_sizeB8ne190102IPS1_S6_EEvT_T0_l
               (undefined8 *param_1,void *param_2,long param_3,ulong param_4)

{
  size_t sVar1;
  size_t sVar2;
  long lVar3;
  ulong uVar4;
  void *pvVar5;
  void *pvVar6;
  
  lVar3 = param_1[2];
  pvVar5 = (void *)*param_1;
  if ((ulong)((lVar3 - (long)pvVar5 >> 3) * -0x3333333333333333) < param_4) {
    if (pvVar5 != (void *)0x0) {
      param_1[1] = pvVar5;
      __ZdlPv(pvVar5);
      lVar3 = 0;
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
    if (0x666666666666666 < param_4) {
                    /* WARNING: Subroutine does not return */
      __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_length_errorB8ne190102Ev
                (param_1);
    }
    uVar4 = (lVar3 >> 3) * -0x6666666666666666;
    if (uVar4 < param_4 || uVar4 - param_4 == 0) {
      uVar4 = param_4;
    }
    if (0x333333333333332 < (ulong)((lVar3 >> 3) * -0x3333333333333333)) {
      uVar4 = 0x666666666666666;
    }
    __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE11__vallocateB8ne190102Em(param_1,uVar4);
    pvVar5 = (void *)param_1[1];
    sVar2 = param_3 - (long)param_2;
    if (sVar2 != 0) {
      _memmove(pvVar5,param_2,sVar2);
    }
    lVar3 = (long)pvVar5 + sVar2;
  }
  else {
    pvVar6 = (void *)param_1[1];
    sVar2 = (long)pvVar6 - (long)pvVar5;
    if ((ulong)(((long)sVar2 >> 3) * -0x3333333333333333) < param_4) {
      if (pvVar6 != pvVar5) {
        _memmove(pvVar5,param_2,sVar2);
        pvVar6 = (void *)param_1[1];
      }
      sVar1 = param_3 - (long)((long)param_2 + sVar2);
      if (sVar1 != 0) {
        _memmove(pvVar6,(void *)((long)param_2 + sVar2),sVar1);
      }
      lVar3 = (long)pvVar6 + sVar1;
    }
    else {
      sVar2 = param_3 - (long)param_2;
      if (sVar2 != 0) {
        _memmove(pvVar5,param_2,sVar2);
      }
      lVar3 = (long)pvVar5 + sVar2;
    }
  }
  param_1[1] = lVar3;
  return;
}

// ==== 00007144 __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE11__vallocateB8ne190102Em ====
void __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE11__vallocateB8ne190102Em
               (long *param_1,ulong param_2)

{
  long lVar1;
  undefined1 auVar2 [16];
  
  if (param_2 < 0x666666666666667) {
    auVar2 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorI11DSPGuideCueEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS6_m
                       (param_1 + 2);
    lVar1 = auVar2._0_8_;
    *param_1 = lVar1;
    param_1[1] = lVar1;
    param_1[2] = lVar1 + auVar2._8_8_ * 0x28;
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_length_errorB8ne190102Ev(param_1);
}

// ==== 00007194 __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE20__throw_length_errorB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 000071a8 __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorI11DSPGuideCueEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS6_m ====
void __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorI11DSPGuideCueEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS6_m
               (undefined8 param_1,ulong param_2)

{
  if (param_2 < 0x666666666666667) {
    __Znwm(param_2 * 0x28);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZSt28__throw_bad_array_new_lengthB8ne190102v();
}

// ==== 000071ec __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_0000c068,PTR___ZNSt12length_errorD1Ev_0000c010);
}

// ==== 0000723c __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_0000c030 + 0x10);
  return;
}

// ==== 00007260 __ZSt28__throw_bad_array_new_lengthB8ne190102v ====
void __ZSt28__throw_bad_array_new_lengthB8ne190102v(void)

{
  undefined8 uVar1;
  
  ___cxa_allocate_exception(8);
  uVar1 = __ZNSt20bad_array_new_lengthC1Ev();
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt20bad_array_new_length_0000c028,
               PTR___ZNSt20bad_array_new_lengthD1Ev_0000c020);
}

// ==== 00007288 ____ZN14GuideDSPKernel13prepareToPlayEib_block_invoke ====
void ____ZN14GuideDSPKernel13prepareToPlayEib_block_invoke(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x20);
  if (-1 < *(int *)(param_1 + 0x28)) {
    lVar1 = 0;
    do {
      *(int *)(lVar2 + lVar1 + 0xb8) = *(int *)(lVar2 + lVar1 + 0xa8) + -1;
      lVar1 = lVar1 + 4;
    } while (lVar1 != 0x10);
    *(undefined4 *)(lVar2 + 0xf0) = *(undefined4 *)(param_1 + 0x28);
    if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
      *(undefined1 *)(lVar2 + 0xe4) = 0;
      *(undefined4 *)(lVar2 + 0xd8) = 0xffffffff;
      *(undefined4 *)(lVar2 + 0xdc) = 0xffffffff;
    }
    __ZN14GuideDSPKernel23resetGuideCuesNextIndexEv(lVar2);
  }
  *(undefined1 *)(lVar2 + 0xe5) = 0;
  return;
}

// ==== 0000730c __ZNSt3__18functionIFvPK7__CFURLEEaSERKS5_ ====
undefined8 __ZNSt3__18functionIFvPK7__CFURLEEaSERKS5_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c050;
  __ZNSt3__110__function12__value_funcIFvPK7__CFURLEEC2B8ne190102ERKS6_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvPK7__CFURLEE4swapB8ne190102ERS6_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00007370;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00007370:
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000073a0 __ZNSt3__110__function12__value_funcIFvPK7__CFURLEE4swapB8ne190102ERS6_ ====
void __ZNSt3__110__function12__value_funcIFvPK7__CFURLEE4swapB8ne190102ERS6_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c050;
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
  if (*(long *)PTR____stack_chk_guard_0000c050 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 0000750c __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE16__init_with_sizeB8ne190102IPS1_S6_EEvT_T0_m ====
void __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE16__init_with_sizeB8ne190102IPS1_S6_EEvT_T0_m
               (long param_1,void *param_2,long param_3,long param_4)

{
  size_t sVar1;
  void *pvVar2;
  
  if (param_4 != 0) {
    __ZNSt3__16vectorI11DSPGuideCueNS_9allocatorIS1_EEE11__vallocateB8ne190102Em(param_1,param_4);
    pvVar2 = *(void **)(param_1 + 8);
    sVar1 = param_3 - (long)param_2;
    if (sVar1 != 0) {
      _memmove(pvVar2,param_2,sVar1);
    }
    *(size_t *)(param_1 + 8) = (long)pvVar2 + sVar1;
  }
  return;
}

// ==== 00007584 __ZNSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 000075ac __ZNSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 000075d4 __ZNKSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_0000c2c0;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 00007614 __ZNKSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE ====
void __ZNKSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_0000c2c0;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 00007630 __ZNSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 00007638 __ZNSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00007660 __ZNSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEEclEOiOS5_OS8_ ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEEclEOiOS5_OS8_
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
  objc_stub::guideAudioUnitErrorStatus_operation_fileURL_(self,(ulong)uVar1,(ulong)uVar2,uVar3);
  return 0;
}

// ==== 000076f0 __ZNKSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000772c __ZNKSt3__110__function6__funcIZ81-[GuideAudioUnit_configureDSPKernelWithFileURL:guideCues:delegate:isRunningTest:]E3$_0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0NS_9allocatorIS2_EEFvi18GuideFileOperationPK7__CFURLEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__GuideAudioUnit_configureDSPKernelWithFileURL_guideCues_delegate_isRunningTest__E3__0
  ;
}

// ==== 00007738 __ZNKSt9type_infoeqB8ne190102ERKS_ ====
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

// ==== 00007784 __ZNSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEED1Ev ====
long __ZNSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 000077ac __ZNSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEED0Ev ====
void __ZNSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 000077d4 __ZNKSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_0000c350;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 00007814 __ZNKSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE7__cloneEPNS0_6__baseIS8_EE ====
void __ZNKSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE7__cloneEPNS0_6__baseIS8_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_0000c350;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 00007830 __ZNSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 00007838 __ZNSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00007860 __ZNSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEEclEOS7_ ====
void __ZNSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEEclEOS7_
               (long param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined *local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  undefined1 auStack_30 [8];
  undefined8 local_28;
  
  uVar1 = *param_2;
  local_50 = PTR___NSConcreteStackBlock_0000c048;
  local_48 = 0xc2000000;
  local_40 = 
  ____ZZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__ENK3__1clEPK7__CFURL_block_invoke;
  puStack_38 = &___block_descriptor_48_ea8_32w_e5_v8__0l;
  _objc_copyWeak(auStack_30,param_1 + 8);
  local_28 = uVar1;
  _dispatch_async(PTR___dispatch_main_q_0000c058,&local_50);
  _objc_destroyWeak(auStack_30);
  return;
}

// ==== 000078e0 __ZNKSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&__ZTIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1)
  ;
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000791c __ZNKSt3__110__function6__funcIZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]E3$_1NS_9allocatorIS2_EEFvPK7__CFURLEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1NS_9allocatorIS2_EEFvPK7__CFURLEE11target_typeEv
          (void)

{
  return &__ZTIZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__E3__1;
}

// ==== 00007928 ____ZZ56-[GuideAudioUnit_allocateRenderResourcesAndReturnError:]ENK3$_1clEPK7__CFURL_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
____ZZ56__GuideAudioUnit_allocateRenderResourcesAndReturnError__ENK3__1clEPK7__CFURL_block_invoke
          (long param_1)

{
  ID self;
  
  self = objc_stub::delegate(*(ID *)(param_1 + 0x20));
  objc_stub::guideAudioUnitDidMakeAnnouncementWithFileURL_(self,*(undefined8 *)(param_1 + 0x28));
  return 0;
}

// ==== 000079a0 ___copy_helper_block_ea8_32w ====
void ___copy_helper_block_ea8_32w(long param_1,long param_2)

{
  _objc_copyWeak(param_1 + 0x20,param_2 + 0x20);
  return;
}

// ==== 000079ac ___destroy_helper_block_ea8_32w ====
void ___destroy_helper_block_ea8_32w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x20);
  return;
}

// ==== 000079b4 _ExtAudioFileDispose ====
void _ExtAudioFileDispose(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileDispose_0000cf58)();
  return;
}

// ==== 000079c0 _ExtAudioFileGetProperty ====
void _ExtAudioFileGetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileGetProperty_0000cf60)();
  return;
}

// ==== 000079cc _ExtAudioFileOpenURL ====
void _ExtAudioFileOpenURL(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileOpenURL_0000cf68)();
  return;
}

// ==== 000079d8 _ExtAudioFileRead ====
void _ExtAudioFileRead(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileRead_0000cf70)();
  return;
}

// ==== 000079e4 _ExtAudioFileSeek ====
void _ExtAudioFileSeek(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSeek_0000cf78)();
  return;
}

// ==== 000079f0 _ExtAudioFileSetProperty ====
void _ExtAudioFileSetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x000079f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSetProperty_0000cf80)();
  return;
}

// ==== 000079fc __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00007a04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_0000cf88)(param_1,param_2,param_3);
  return;
}

// ==== 00007a08 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00007a10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_0000cf90)(param_1,param_2);
  return;
}

// ==== 00007a14 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00007a1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_0000cf98)();
  return;
}

// ==== 00007a20 __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_0000cfa0)();
  return;
}

// ==== 00007a2c __ZNSt20bad_array_new_lengthC1Ev ====
void __ZNSt20bad_array_new_lengthC1Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt20bad_array_new_lengthC1Ev_0000cfa8)();
  return;
}

// ==== 00007a38 __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_0000cfb0)();
  return;
}

// ==== 00007a44 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_0000cfb8)();
  return;
}

// ==== 00007a50 __ZdaPv ====
void __ZdaPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdaPv_0000c078)();
  return;
}

// ==== 00007a5c __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_0000c080)();
  return;
}

// ==== 00007a68 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_0000c088)();
  return;
}

// ==== 00007a74 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_0000cfc0)();
  return;
}

// ==== 00007a80 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_0000cfc8)();
  return;
}

// ==== 00007a8c ___cxa_end_catch ====
void ___cxa_end_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007a94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_end_catch_0000cfd0)();
  return;
}

// ==== 00007a98 ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007aa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_0000cfd8)();
  return;
}

// ==== 00007aa4 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007aac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_0000cfe0)();
  return;
}

// ==== 00007ab0 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007ab8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_0000cfe8)();
  return;
}

// ==== 00007abc _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00007ac4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_0000cff0)();
  return;
}

// ==== 00007ac8 _dispatch_async ====
void _dispatch_async(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007ad0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_async_0000cff8)();
  return;
}

// ==== 00007ad4 _dispatch_queue_create ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

dispatch_queue_t _dispatch_queue_create(char *label,dispatch_queue_attr_t attr)

{
  dispatch_queue_t pdVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007adc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pdVar1 = (dispatch_queue_t)(*(code *)PTR__dispatch_queue_create_0000d000)();
  return pdVar1;
}

// ==== 00007ae0 _dispatch_sync ====
void _dispatch_sync(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_sync_0000d008)();
  return;
}

// ==== 00007aec _malloc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _malloc(size_t param_1)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007af4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__malloc_0000d010)();
  return pvVar1;
}

// ==== 00007af8 _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007b00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_0000d018)();
  return pvVar1;
}

// ==== 00007b04 _memmove ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memmove(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007b0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memmove_0000d020)();
  return pvVar1;
}

// ==== 00007b10 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_0000d028)();
  return;
}

// ==== 00007b1c _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_0000d030)();
  return;
}

// ==== 00007b28 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_0000d038)();
  return;
}

// ==== 00007b34 _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_0000d040)();
  return;
}

// ==== 00007b40 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_0000d048)();
  return;
}

// ==== 00007b4c _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_0000d050)();
  return;
}

// ==== 00007b58 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_0000d058)();
  return;
}

// ==== 00007b64 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_0000d060)();
  return;
}

// ==== 00007b70 _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_0000d068)();
  return;
}

// ==== 00007b7c _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007b84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_0000d070)();
  return IVar1;
}

// ==== 00007b88 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_0000d078)();
  return;
}

// ==== 00007b94 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007b9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_0000d080)();
  return;
}

// ==== 00007ba0 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007ba8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_0000d088)();
  return;
}

// ==== 00007bac _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007bb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_0000d090)();
  return;
}

// ==== 00007bb8 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007bc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_0000d098)();
  return;
}

// ==== 00007bc4 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007bcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_0000d0a0)();
  return;
}

// ==== 00007bd0 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007bd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_0000d0a8)();
  return;
}

// ==== 00007bdc _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007be4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_0000d0b0)();
  return;
}

// ==== 00007be8 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007bf0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_0000d0b8)((int)param_1);
  return iVar1;
}

// ==== 00007e40 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"address");
  return IVar1;
}

// ==== 00007e60 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00007e80 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00007ea0 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00007ec0 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"channelCount");
  return IVar1;
}

// ==== 00007ee0 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00007f00 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00007f20 objc_stub::cueEnabled ====
ID __objc_msgSend_stub objc_stub::cueEnabled(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"cueEnabled");
  return IVar1;
}

// ==== 00007f40 objc_stub::cueFilePath ====
ID __objc_msgSend_stub objc_stub::cueFilePath(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"cueFilePath");
  return IVar1;
}

// ==== 00007f60 objc_stub::cueSequenceTimecode ====
ID __objc_msgSend_stub objc_stub::cueSequenceTimecode(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"cueSequenceTimecode");
  return IVar1;
}

// ==== 00007f80 objc_stub::cueType ====
ID __objc_msgSend_stub objc_stub::cueType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"cueType");
  return IVar1;
}

// ==== 00007fa0 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00007fc0 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"delegate");
  return IVar1;
}

// ==== 00007fe0 objc_stub::dspGuideCues ====
ID __objc_msgSend_stub objc_stub::dspGuideCues(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"dspGuideCues");
  return IVar1;
}

// ==== 00008000 objc_stub::enumerateObjectsUsingBlock: ====
ID __objc_msgSend_stub objc_stub::enumerateObjectsUsingBlock_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"enumerateObjectsUsingBlock:");
  return IVar1;
}

// ==== 00008020 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00008040 objc_stub::fileURLWithPath: ====
ID __objc_msgSend_stub objc_stub::fileURLWithPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"fileURLWithPath:");
  return IVar1;
}

// ==== 00008060 objc_stub::floatValue ====
ID __objc_msgSend_stub objc_stub::floatValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"floatValue");
  return IVar1;
}

// ==== 00008080 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"format");
  return IVar1;
}

// ==== 000080a0 objc_stub::guideAudioUnitDidMakeAnnouncementWithFileURL: ====
ID __objc_msgSend_stub objc_stub::guideAudioUnitDidMakeAnnouncementWithFileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)
                    (self,"guideAudioUnitDidMakeAnnouncementWithFileURL:");
  return IVar1;
}

// ==== 000080c0 objc_stub::guideAudioUnitErrorStatus:operation:fileURL: ====
ID __objc_msgSend_stub objc_stub::guideAudioUnitErrorStatus_operation_fileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"guideAudioUnitErrorStatus:operation:fileURL:")
  ;
  return IVar1;
}

// ==== 000080e0 objc_stub::guideCues ====
ID __objc_msgSend_stub objc_stub::guideCues(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"guideCues");
  return IVar1;
}

// ==== 00008100 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00008120 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00008140 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00008160 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00008180 objc_stub::isRunningTest ====
ID __objc_msgSend_stub objc_stub::isRunningTest(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"isRunningTest");
  return IVar1;
}

// ==== 000081a0 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 000081c0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 000081e0 objc_stub::objectAtIndexedSubscript: ====
ID __objc_msgSend_stub objc_stub::objectAtIndexedSubscript_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"objectAtIndexedSubscript:");
  return IVar1;
}

// ==== 00008200 objc_stub::replacementCountCueFilePath ====
ID __objc_msgSend_stub objc_stub::replacementCountCueFilePath(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"replacementCountCueFilePath");
  return IVar1;
}

// ==== 00008220 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"reset");
  return IVar1;
}

// ==== 00008240 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"sampleRate");
  return IVar1;
}

// ==== 00008260 objc_stub::sectionTypeID ====
ID __objc_msgSend_stub objc_stub::sectionTypeID(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"sectionTypeID");
  return IVar1;
}

// ==== 00008280 objc_stub::setCueEnabled: ====
ID __objc_msgSend_stub objc_stub::setCueEnabled_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setCueEnabled:");
  return IVar1;
}

// ==== 000082a0 objc_stub::setCueFilePath: ====
ID __objc_msgSend_stub objc_stub::setCueFilePath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setCueFilePath:");
  return IVar1;
}

// ==== 000082c0 objc_stub::setCueSequenceTimecode: ====
ID __objc_msgSend_stub objc_stub::setCueSequenceTimecode_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setCueSequenceTimecode:");
  return IVar1;
}

// ==== 000082e0 objc_stub::setCueType: ====
ID __objc_msgSend_stub objc_stub::setCueType_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setCueType:");
  return IVar1;
}

// ==== 00008300 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00008320 objc_stub::setDelegate: ====
ID __objc_msgSend_stub objc_stub::setDelegate_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setDelegate:");
  return IVar1;
}

// ==== 00008340 objc_stub::setFileURL: ====
ID __objc_msgSend_stub objc_stub::setFileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setFileURL:");
  return IVar1;
}

// ==== 00008360 objc_stub::setGuideCues: ====
ID __objc_msgSend_stub objc_stub::setGuideCues_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setGuideCues:");
  return IVar1;
}

// ==== 00008380 objc_stub::setGuideTimeGrid: ====
ID __objc_msgSend_stub objc_stub::setGuideTimeGrid_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setGuideTimeGrid:");
  return IVar1;
}

// ==== 000083a0 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 000083c0 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 000083e0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00008400 objc_stub::setIsRunningTest: ====
ID __objc_msgSend_stub objc_stub::setIsRunningTest_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setIsRunningTest:");
  return IVar1;
}

// ==== 00008420 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00008440 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00008460 objc_stub::setReplacementCountCueFilePath: ====
ID __objc_msgSend_stub objc_stub::setReplacementCountCueFilePath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setReplacementCountCueFilePath:");
  return IVar1;
}

// ==== 00008480 objc_stub::setSectionTypeID: ====
ID __objc_msgSend_stub objc_stub::setSectionTypeID_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setSectionTypeID:");
  return IVar1;
}

// ==== 000084a0 objc_stub::setSongMapElementStartTimecode: ====
ID __objc_msgSend_stub objc_stub::setSongMapElementStartTimecode_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setSongMapElementStartTimecode:");
  return IVar1;
}

// ==== 000084c0 objc_stub::setUrl: ====
ID __objc_msgSend_stub objc_stub::setUrl_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setUrl:");
  return IVar1;
}

// ==== 000084e0 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setValue:");
  return IVar1;
}

// ==== 00008500 objc_stub::songMapElementStartTimecode ====
ID __objc_msgSend_stub objc_stub::songMapElementStartTimecode(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"songMapElementStartTimecode");
  return IVar1;
}

// ==== 00008520 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00008540 objc_stub::url ====
ID __objc_msgSend_stub objc_stub::url(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"url");
  return IVar1;
}

// ==== 00008560 objc_stub::value ====
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

// ==== 0001c801 NSObject::init ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::init(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c802 NSObject::setCueType: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setCueType_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c803 NSObject::setSectionTypeID: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setSectionTypeID_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c804 NSObject::setCueSequenceTimecode: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setCueSequenceTimecode_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c805 NSObject::cueSequenceTimecode ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::cueSequenceTimecode(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c806 NSObject::cueType ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::cueType(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c807 NSObject::setSongMapElementStartTimecode: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setSongMapElementStartTimecode_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c808 NSObject::setCueEnabled: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setCueEnabled_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c809 NSObject::setCueFilePath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setCueFilePath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c80a NSObject::setReplacementCountCueFilePath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSObject::setReplacementCountCueFilePath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c901 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001ca01 NSURL::fileURLWithPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSURL::fileURLWithPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb01 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb02 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb03 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb04 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb05 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb06 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb07 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001e100 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

