// MixerAUFramework sha256 d0b6117feeabbd3681224b2966350b1f8a86a1ca26d1106e643d132583242677 (Ghidra 12.1.4, all decompiled functions)

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

// ==== 0000415c MixerAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID MixerAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  undefined8 *puVar3;
  ID IVar4;
  ID IVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  undefined *local_100;
  undefined8 local_f8;
  code *local_f0;
  undefined *puStack_e8;
  undefined8 *local_e0;
  undefined *local_d8;
  undefined8 local_d0;
  code *local_c8;
  undefined *puStack_c0;
  undefined8 *local_b8;
  undefined8 local_b0;
  undefined8 *puStack_a8;
  undefined8 local_a0;
  undefined8 local_98;
  ID local_88;
  class_t *pcStack_80;
  ID local_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_00008020;
  puStack_a8 = *(undefined8 **)&param_3->field2_0x8;
  local_b0._0_4_ = param_3->field0_0x0;
  local_b0._4_4_ = param_3->field1_0x4;
  local_a0 = CONCAT44(local_a0._4_4_,param_3->field4_0x10);
  pcStack_80 = &objc::class_t::MixerAudioUnit;
  local_88 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_88,"initWithComponentDescription:options:error:",&local_b0,
                    (ulong)param_4);
  if (self != 0) {
    IVar2 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar2 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar2,0x40e5888000000000,1);
    TrackedAUAudioUnit::setDefaultFormat_(self,IVar2);
    lVar8 = (long)_dspKernel;
    if (*(long *)(self + lVar8) == 0) {
      puVar3 = (undefined8 *)__Znwm(0x48);
      *puVar3 = &DAT_00008120;
      puVar3[1] = 0;
      *(undefined4 *)(puVar3 + 2) = 0;
      puVar3[3] = 0;
      puVar3[7] = 0;
      puVar3[8] = 0;
      *(undefined4 *)(puVar3 + 6) = 0x3f800000;
      *(undefined4 *)((long)puVar3 + 0x34) = 0x3f800000;
      *(undefined8 **)(self + lVar8) = puVar3;
    }
    IVar2 = NSMutableArray::array((ID)&_OBJC_CLASS___NSMutableArray);
    puVar3 = (undefined8 *)(self + (long)_bufferedInputBus);
    lVar7 = 0x20;
    do {
      IVar4 = TrackedAUAudioUnit::defaultFormat(self);
      __ZN16BufferedAudioBus4initEP13AVAudioFormatj(puVar3,IVar4,0x20);
      NSMutableArray::addObject_(IVar2,*puVar3);
      puVar3 = puVar3 + 5;
      lVar7 = lVar7 + -1;
    } while (lVar7 != 0);
    lVar7 = (long)_bufferedOutputBus;
    IVar4 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar7,IVar4,0x20);
    IVar4 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar5 = TrackedAUAudioUnit::defaultFormat(self);
    IVar4 = AUAudioUnitBus::initWithFormat_error_(IVar4,IVar5,0);
    lVar7 = (long)_auOutputBus;
    uVar6 = *(undefined8 *)(self + lVar7);
    *(ID *)(self + lVar7) = IVar4;
    IVar4 = _objc_alloc(uVar6,&_OBJC_CLASS___AUAudioUnitBusArray);
    IVar2 = objc_stub::initWithAudioUnit_busType_busses_(IVar4,self,1,IVar2);
    uVar6 = *(undefined8 *)(self + (long)_auInputBusArray);
    *(ID *)(self + (long)_auInputBusArray) = IVar2;
    IVar2 = _objc_alloc(uVar6,&_OBJC_CLASS___AUAudioUnitBusArray);
    local_70 = *(undefined8 *)(self + lVar7);
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_70,1);
    IVar2 = objc_stub::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar4);
    uVar6 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,uVar6,0,0x3f800000,&cf_volumeParameter,
                       &cf_volume,0,0x1a,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    local_78 = IVar2;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_78,1);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar7 = (long)_parameterTree;
    *(ID *)(self + lVar7) = IVar2;
    puVar1 = PTR___NSConcreteStackBlock_00008018;
    local_b0 = 0;
    local_a0 = 0x2020000000;
    local_98 = *(undefined8 *)(self + lVar8);
    local_d8 = PTR___NSConcreteStackBlock_00008018;
    local_d0 = 0xc2000000;
    local_c8 = ___61__MixerAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_c0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_b8 = &local_b0;
    puStack_a8 = &local_b0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar7),&local_d8);
    local_100 = puVar1;
    local_f8 = 0xc2000000;
    local_f0 = ___61__MixerAudioUnit_initWithComponentDescription_options_error___block_invoke_9;
    puStack_e8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_e0 = &local_b0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar7),&local_100);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar7),&___block_literal_global);
    TrackedAUAudioUnit::setMaximumFramesToRender_(self,0x200);
    __Block_object_dispose(&local_b0,8);
  }
  if (*(long *)PTR____stack_chk_guard_00008020 == local_68) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004654 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 000046e8 ___61-[MixerAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___61__MixerAudioUnit_initWithComponentDescription_options_error___block_invoke
               (undefined4 param_1,long param_2,ID param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ID IVar4;
  long lVar5;
  
  lVar5 = *(long *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar4 = objc_stub::address(param_3);
  if (IVar4 == 0) {
    *(undefined4 *)(lVar5 + 0x30) = param_1;
    piVar1 = (int *)(lVar5 + 0x40);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return;
}

// ==== 00004744 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004754 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004760 ___61-[MixerAudioUnit_initWithComponentDescription:options:error:]_block_invoke.9 ====
undefined4
___61__MixerAudioUnit_initWithComponentDescription_options_error___block_invoke_9
          (long param_1,ID param_2)

{
  ID IVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  uVar3 = 0;
  if (IVar1 == 0) {
    uVar3 = *(undefined4 *)(lVar2 + 0x30);
  }
  return uVar3;
}

// ==== 000047a0 ___61-[MixerAudioUnit_initWithComponentDescription:options:error:]_block_invoke.11 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */

cfstringStruct *
___61__MixerAudioUnit_initWithComponentDescription_options_error___block_invoke_11
          (undefined8 param_1,ID param_2,long param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  
  if (param_3 == 0) {
    objc_stub::value(param_2);
  }
  IVar1 = objc_stub::address(param_2);
  if (IVar1 == 0) {
    pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__f);
  }
  else {
    pcVar2 = &cf__;
  }
  return pcVar2;
}

// ==== 00004850 MixerAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void MixerAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_20;
  class_t *pcStack_18;
  
  pcStack_18 = &objc::class_t::MixerAudioUnit;
  local_20 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_20,"reset");
  return;
}

// ==== 00004884 MixerAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void MixerAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  lVar1 = (long)_dspKernel;
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZdlPv();
  }
  *(undefined8 *)(param_1 + lVar1) = 0;
  pcStack_28 = &objc::class_t::MixerAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_30,"dealloc");
  return;
}

// ==== 000048dc MixerAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool MixerAudioUnit::shouldChangeToFormat_forBus_(ID param_1,SEL param_2,ID param_3,ID param_4)

{
  ID IVar1;
  ID *pIVar2;
  ID IVar3;
  long lVar4;
  bool bVar5;
  undefined8 local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_00008020;
  IVar1 = objc_stub::busType(param_4);
  if (IVar1 == 1) {
    setInputFormat_(param_1,param_3);
    pIVar2 = (ID *)(param_1 + (long)_bufferedInputBus);
    lVar4 = 0x20;
    do {
      if (*pIVar2 == param_4) {
        __ZN16BufferedAudioBus4initEP13AVAudioFormatj(pIVar2,param_3,0x20);
        break;
      }
      pIVar2 = pIVar2 + 5;
      lVar4 = lVar4 + -1;
    } while (lVar4 != 0);
  }
  else {
    IVar1 = objc_stub::busType(param_4);
    if (IVar1 != 2) {
      bVar5 = 0;
      goto LAB_00004a7c;
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
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_60,1);
    IVar1 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar1,param_1,2,IVar3);
    *(ID *)(param_1 + (long)_auOutputBusArray) = IVar1;
  }
  bVar5 = 1;
LAB_00004a7c:
  if (*(long *)PTR____stack_chk_guard_00008020 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return bVar5;
}

// ==== 00004b10 MixerAudioUnit::inputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::inputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auInputBusArray);
}

// ==== 00004b20 MixerAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00004b30 MixerAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool MixerAudioUnit::allocateRenderResourcesAndReturnError_(ID param_1,SEL param_2,ID *param_3)

{
  undefined4 uVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  long lVar5;
  ID *pIVar6;
  double extraout_d0;
  ID local_70;
  class_t *pcStack_68;
  
  pcStack_68 = &objc::class_t::MixerAudioUnit;
  local_70 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_70,"allocateRenderResourcesAndReturnError:");
  if ((int)IVar2 != 0) {
    IVar2 = inputFormat(param_1);
    if (IVar2 != 0) {
      pIVar6 = (ID *)(param_1 + (long)_bufferedInputBus);
      IVar2 = objc_stub::format(*pIVar6);
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
            IVar2 = objc_stub::format(*pIVar6);
            IVar2 = objc_stub::channelCount(IVar2);
            IVar3 = auOutputBus(param_1);
            IVar3 = objc_stub::format(IVar3);
            IVar3 = objc_stub::channelCount(IVar3);
            if ((uint)IVar2 <= (uint)IVar3) {
              lVar5 = 0x20;
              do {
                IVar2 = objc_stub::maximumFramesToRender(param_1);
                __ZN16BufferedAudioBus23allocateRenderResourcesEj(pIVar6,IVar2);
                pIVar6 = pIVar6 + 5;
                lVar5 = lVar5 + -1;
              } while (lVar5 != 0);
              IVar2 = objc_stub::maximumFramesToRender(param_1);
              __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar4,IVar2);
              lVar4 = *(long *)(param_1 + (long)_dspKernel);
              IVar2 = defaultFormat(param_1);
              objc_stub::sampleRate(IVar2);
              *(float *)(lVar4 + 0x24) = (float)extraout_d0;
              *(int *)(lVar4 + 0x20) = (int)((float)extraout_d0 * 0.02);
              uVar1 = *(undefined4 *)(lVar4 + 0x30);
              *(undefined4 *)(lVar4 + 0x30) = uVar1;
              *(undefined4 *)(lVar4 + 0x34) = uVar1;
              *(undefined8 *)(lVar4 + 0x38) = 0;
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

// ==== 00004f58 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00004ff8 MixerAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MixerAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  long lVar2;
  ID local_40;
  class_t *pcStack_38;
  
  puVar1 = (undefined8 *)((long)_bufferedInputBus + param_1 + 0x10);
  lVar2 = 0x20;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1 = puVar1 + 5;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  pcStack_38 = &objc::class_t::MixerAudioUnit;
  local_40 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_40,"deallocateRenderResources");
  return;
}

// ==== 00005070 MixerAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_a0 = ___37__MixerAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00005164 ___37-[MixerAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___37__MixerAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7,undefined8 param_8)

{
  long lVar1;
  long lVar2;
  undefined4 local_54;
  
  lVar2 = 0;
  lVar1 = 0;
  local_54 = 0;
  do {
    __ZN16BufferedInputBus9pullInputEPjPK14AudioTimeStampjlU13block_pointerFiS0_S3_jlP15AudioBufferListE
              (*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + lVar2,&local_54,param_3,
               param_4,lVar1,param_8);
    lVar1 = lVar1 + 1;
    lVar2 = lVar2 + 0x28;
  } while (lVar1 != 0x20);
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x30) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x30) + (long)MixerAudioUnit::_bufferedOutputBus,param_6,param_4,
               1);
  }
  lVar1 = *(long *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18);
  *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  *(undefined4 *)(lVar1 + 0x10) = 0x20;
  *(long *)(lVar1 + 0x18) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x28) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005278 __ZN16BufferedInputBus9pullInputEPjPK14AudioTimeStampjlU13block_pointerFiS0_S3_jlP15AudioBufferListE ====
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

// ==== 00005318 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 000053b0 ___copy_helper_block_ea8_32r40r48w ====
void ___copy_helper_block_ea8_32r40r48w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  __Block_object_assign((void *)(param_1 + 0x28),*(void **)(param_2 + 0x28),8);
  _objc_copyWeak(param_1 + 0x30,param_2 + 0x30);
  return;
}

// ==== 000053f8 ___destroy_helper_block_ea8_32r40r48w ====
void ___destroy_helper_block_ea8_32r40r48w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x30);
  __Block_object_dispose(*(void **)(param_1 + 0x28),8);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005430 MixerAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 00005440 MixerAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 00005454 MixerAudioUnit::auInputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::auInputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auInputBusArray);
}

// ==== 00005464 MixerAudioUnit::setAuInputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setAuInputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auInputBusArray) = param_3;
  return;
}

// ==== 00005470 MixerAudioUnit::auOutputBus ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005480 MixerAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 0000548c MixerAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 0000549c MixerAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 000054a8 MixerAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 000054b8 MixerAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 000054c4 MixerAudioUnit::inputFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::inputFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_inputFormat);
}

// ==== 000054d4 MixerAudioUnit::setInputFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setInputFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_inputFormat) = param_3;
  return;
}

// ==== 000054e0 MixerAudioUnit::outputFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::outputFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_outputFormat);
}

// ==== 000054f0 MixerAudioUnit::setOutputFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void MixerAudioUnit::setOutputFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_outputFormat) = param_3;
  return;
}

// ==== 000054fc MixerAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void MixerAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  long lVar1;
  
  *(undefined8 *)(param_1 + (long)_outputFormat) = 0;
  *(undefined8 *)(param_1 + (long)_inputFormat) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  *(undefined8 *)(param_1 + (long)_auInputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  lVar1 = -0x500;
  do {
    lVar1 = lVar1 + 0x28;
  } while (lVar1 != 0);
  return;
}

// ==== 000055f0 MixerAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID MixerAudioUnit::_cxx_construct(ID param_1,SEL param_2)

{
  undefined8 *puVar1;
  long lVar2;
  
  lVar2 = 0x500;
  puVar1 = (undefined8 *)((long)_bufferedInputBus + param_1 + 0x10);
  do {
    puVar1[-2] = 0;
    *(undefined4 *)(puVar1 + -1) = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    lVar2 = lVar2 + -0x28;
    puVar1 = puVar1 + 5;
  } while (lVar2 != 0);
  puVar1 = (undefined8 *)(param_1 + (long)_bufferedOutputBus);
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 1) = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[2] = 0;
  return param_1;
}

// ==== 0000563c __ZN14MixerDSPKernel7processEjj ====
void __ZN14MixerDSPKernel7processEjj(long param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  undefined8 *puVar9;
  float fVar10;
  float fVar11;
  
  __ZN15ParameterRamper13dezipperCheckEj(param_1 + 0x28,*(undefined4 *)(param_1 + 0x20));
  if (param_2 != 0) {
    uVar3 = 0;
    do {
      if (*(uint *)(param_1 + 0x3c) == 0) {
        fVar10 = *(float *)(param_1 + 0x34);
      }
      else {
        fVar10 = *(float *)(param_1 + 0x34) +
                 (float)*(uint *)(param_1 + 0x3c) * *(float *)(param_1 + 0x38);
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
      }
      lVar7 = *(long *)(param_1 + 8);
      uVar1 = **(uint **)(lVar7 + 0x20);
      if (0 < (int)uVar1) {
        uVar4 = 0;
        uVar2 = *(uint *)(param_1 + 0x10);
        lVar5 = (long)((int)uVar3 + param_3);
        lVar6 = *(long *)(param_1 + 0x18);
        do {
          fVar11 = 0.0;
          uVar8 = (ulong)uVar2;
          puVar9 = (undefined8 *)(lVar7 + 0x20);
          if (uVar2 != 0) {
            do {
              if (*(uint *)*puVar9 <= uVar4) break;
              fVar11 = fVar11 + fVar10 * *(float *)(*(long *)((uint *)*puVar9 + uVar4 * 4 + 4) +
                                                   lVar5 * 4);
              uVar8 = uVar8 - 1;
              puVar9 = puVar9 + 5;
            } while (uVar8 != 0);
          }
          *(float *)(*(long *)(lVar6 + uVar4 * 0x10 + 0x10) + lVar5 * 4) = fVar11;
          uVar4 = uVar4 + 1;
        } while (uVar4 != uVar1);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 != param_2);
  }
  return;
}

// ==== 0000574c __ZN14MixerDSPKernel9startRampEyfj ====
void __ZN14MixerDSPKernel9startRampEyfj(float param_1,long param_2,long param_3,uint param_4)

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
    fVar2 = (float)NEON_ucvtf(*(undefined4 *)(param_2 + 0x3c));
    *(float *)(param_2 + 0x38) =
         ((*(float *)(param_2 + 0x34) + fVar2 * *(float *)(param_2 + 0x38)) - fVar1) /
         (float)param_4;
    *(uint *)(param_2 + 0x3c) = param_4;
    *(float *)(param_2 + 0x30) = fVar1;
    *(float *)(param_2 + 0x34) = fVar1;
    return;
  }
  *(float *)(param_2 + 0x30) = fVar1;
  *(float *)(param_2 + 0x34) = fVar1;
  *(undefined8 *)(param_2 + 0x38) = 0;
  return;
}

// ==== 000057cc __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 000057d0 __ZN15ParameterRamper13dezipperCheckEj ====
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

// ==== 00005844 __ZN16BufferedInputBus22prepareInputBufferListEv ====
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

// ==== 00005884 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x0000588c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_000086a0)(param_1,param_2,param_3);
  return;
}

// ==== 00005890 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x00005898. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_000086a8)(param_1,param_2);
  return;
}

// ==== 0000589c __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x000058a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_000086b0)();
  return;
}

// ==== 000058a8 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00008030)();
  return;
}

// ==== 000058b4 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00008038)();
  return;
}

// ==== 000058c0 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_000086b8)();
  return;
}

// ==== 000058cc _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000058d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_000086c0)();
  return;
}

// ==== 000058d8 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_000086c8)();
  return;
}

// ==== 000058e4 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_000086d0)();
  return;
}

// ==== 000058f0 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000058f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_000086d8)();
  return;
}

// ==== 000058fc _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005904. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_000086e0)();
  return;
}

// ==== 00005908 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005910. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_000086e8)();
  return;
}

// ==== 00005914 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000591c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_000086f0)();
  return;
}

// ==== 00005920 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005928. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_000086f8)();
  return;
}

// ==== 0000592c _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005934. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00008700)();
  return;
}

// ==== 00005938 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005940. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00008708)();
  return IVar1;
}

// ==== 00005944 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000594c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00008710)();
  return;
}

// ==== 00005950 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005958. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00008718)();
  return;
}

// ==== 0000595c _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005964. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00008720)();
  return;
}

// ==== 00005968 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005970. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00008728)();
  return;
}

// ==== 00005974 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000597c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00008730)();
  return;
}

// ==== 00005980 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005988. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00008738)();
  return;
}

// ==== 0000598c _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x00005994. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00008740)();
  return;
}

// ==== 00005ac0 objc_stub::addObject: ====
ID __objc_msgSend_stub objc_stub::addObject_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"addObject:");
  return IVar1;
}

// ==== 00005ae0 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"address");
  return IVar1;
}

// ==== 00005b00 objc_stub::array ====
ID __objc_msgSend_stub objc_stub::array(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"array");
  return IVar1;
}

// ==== 00005b20 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00005b40 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00005b60 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00005b80 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"busType");
  return IVar1;
}

// ==== 00005ba0 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"channelCount");
  return IVar1;
}

// ==== 00005bc0 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00005be0 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00005c00 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00005c20 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00005c40 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"format");
  return IVar1;
}

// ==== 00005c60 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00005c80 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00005ca0 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00005cc0 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00005ce0 objc_stub::inputFormat ====
ID __objc_msgSend_stub objc_stub::inputFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"inputFormat");
  return IVar1;
}

// ==== 00005d00 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00005d20 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00005d40 objc_stub::outputFormat ====
ID __objc_msgSend_stub objc_stub::outputFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"outputFormat");
  return IVar1;
}

// ==== 00005d60 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"sampleRate");
  return IVar1;
}

// ==== 00005d80 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00005da0 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00005dc0 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00005de0 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00005e00 objc_stub::setInputFormat: ====
ID __objc_msgSend_stub objc_stub::setInputFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setInputFormat:");
  return IVar1;
}

// ==== 00005e20 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00005e40 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00005e60 objc_stub::setOutputFormat: ====
ID __objc_msgSend_stub objc_stub::setOutputFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setOutputFormat:");
  return IVar1;
}

// ==== 00005e80 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00005ea0 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"setValue:");
  return IVar1;
}

// ==== 00005ec0 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00008008)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 00005ee0 objc_stub::value ====
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

// ==== 00014801 NSMutableArray::array ====
/* WARNING: Control flow encountered bad instruction data */

ID NSMutableArray::array(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014802 NSMutableArray::addObject: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSMutableArray::addObject_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014901 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

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

// ==== 00014a04 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a05 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a06 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00014a07 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

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

// ==== 00015500 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

