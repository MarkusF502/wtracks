// BufferedFilePlaybackAUFramework sha256 1903ed0433ce5dfb69675ebb76611507a5977af79f65cbba4d89c917ab7fa379 (Ghidra 12.1.4, all decompiled functions)

// ==== 00004000 AudioObfuscator::obfuscateAllAudioFilesAtURL: ====
/* Function Stack Size: 0x18 bytes */

bool AudioObfuscator::obfuscateAllAudioFilesAtURL_(ID param_1,SEL param_2,ID param_3)

{
  bool bVar1;
  
  bVar1 = __ZN19AudioObfuscatorImpl27obfuscateAllAudioFilesAtURLEP5NSURL(param_1 + 8,param_3);
  return bVar1;
}

// ==== 0000400c AudioObfuscator::performOperationOnObfuscatedAudioFile:audioOperationBlock: ====
/* Function Stack Size: 0x20 bytes */

void AudioObfuscator::performOperationOnObfuscatedAudioFile_audioOperationBlock_
               (ID param_1,SEL param_2,ID param_3,ID param_4,undefined4 param_5)

{
  __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE
            (param_1 + 8,param_3,param_4,param_4,param_5);
  return;
}

// ==== 0000401c AudioObfuscator::.cxx_destruct ====
/* Function Stack Size: 0x10 bytes */

void AudioObfuscator::_cxx_destruct(ID param_1,SEL param_2)

{
  __ZN19AudioObfuscatorImplD1Ev(param_1 + 8);
  return;
}

// ==== 00004024 AudioObfuscator::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID AudioObfuscator::_cxx_construct(ID param_1,SEL param_2)

{
  __ZN19AudioObfuscatorImplC1Ev(param_1 + 8);
  return param_1;
}

// ==== 0000404c BufferedFilePlaybackAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID BufferedFilePlaybackAudioUnit::initWithComponentDescription_options_error_
             (ID param_1,SEL param_2,AudioComponentDescription *param_3,unsigned_int param_4,
             ID *param_5)

{
  ID self;
  ID IVar1;
  ID IVar2;
  long lVar3;
  ID local_80;
  class_t *pcStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  unsigned_int local_60;
  undefined8 local_50;
  long local_48;
  
  local_48 = *(long *)PTR____stack_chk_guard_00010040;
  uStack_68._0_4_ = param_3->field2_0x8;
  uStack_68._4_4_ = param_3->field3_0xc;
  local_70._0_4_ = param_3->field0_0x0;
  local_70._4_4_ = param_3->field1_0x4;
  local_60 = param_3->field4_0x10;
  pcStack_78 = &objc::class_t::BufferedFilePlaybackAudioUnit;
  local_80 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_80,"initWithComponentDescription:options:error:",&local_70,
                    (ulong)param_4);
  if (self != 0) {
    IVar1 = _objc_alloc(&_OBJC_CLASS___AVAudioFormat);
    IVar1 = AVAudioFormat::initStandardFormatWithSampleRate_channels_(IVar1,0x40e5888000000000,2);
    TrackedAUAudioUnit::setDefaultFormat_(self,IVar1);
    TrackedAUAudioUnit::setIsMaster_(self,0);
    lVar3 = (long)_bufferedOutputBus;
    IVar1 = TrackedAUAudioUnit::defaultFormat(self);
    __ZN16BufferedAudioBus4initEP13AVAudioFormatj(self + lVar3,IVar1,2);
    IVar1 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBus);
    IVar2 = TrackedAUAudioUnit::defaultFormat(self);
    IVar1 = AUAudioUnitBus::initWithFormat_error_(IVar1,IVar2,0);
    lVar3 = (long)_auOutputBus;
    *(ID *)(self + lVar3) = IVar1;
    IVar1 = _objc_alloc(&_OBJC_CLASS___AUAudioUnitBusArray);
    local_50 = *(undefined8 *)(self + lVar3);
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_50,1);
    IVar1 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar1,self,2,IVar2);
    *(ID *)(self + (long)_auOutputBusArray) = IVar1;
  }
  if (*(long *)PTR____stack_chk_guard_00010040 == local_48) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 000042b4 __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 00004348 BufferedFilePlaybackAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void BufferedFilePlaybackAudioUnit::reset(ID param_1,SEL param_2)

{
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::BufferedFilePlaybackAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  __ZN29BufferedFilePlaybackDSPKernel5resetEv(*(undefined8 *)(param_1 + (long)_dspKernel));
  return;
}

// ==== 00004398 __ZN29BufferedFilePlaybackDSPKernel5resetEv ====
void __ZN29BufferedFilePlaybackDSPKernel5resetEv(long param_1)

{
  undefined *local_38;
  undefined8 local_30;
  code *local_28;
  undefined *puStack_20;
  long local_18;
  
  *(undefined1 *)(param_1 + 8) = 0;
  if ((0 < *(int *)(param_1 + 0xcc)) && (*(int *)(param_1 + 0xc0) != 0)) {
    local_38 = PTR___NSConcreteStackBlock_00010038;
    local_30 = 0xc0000000;
    local_28 = ____ZN29BufferedFilePlaybackDSPKernel5resetEv_block_invoke;
    puStack_20 = &___block_descriptor_40_e5_v8__0l;
    local_18 = param_1;
    _dispatch_sync(*(undefined8 *)(param_1 + 0x68),&local_38);
  }
  return;
}

// ==== 00004410 BufferedFilePlaybackAudioUnit::dealloc ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void BufferedFilePlaybackAudioUnit::dealloc(ID param_1,SEL param_2)

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
  local_58 = PTR___NSConcreteStackBlock_00010038;
  local_50 = 0xc0000000;
  local_48 = ____ZN29BufferedFilePlaybackDSPKernel7cleanupEv_block_invoke;
  puStack_40 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_38 + 0x68),&local_58);
  puVar3 = *(undefined8 **)(param_1 + lVar4);
  if (puVar3 == (undefined8 *)0x0) goto LAB_000044cc;
  *puVar3 = &DAT_00010168;
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(puVar3 + 0x28);
  plVar1 = (long *)puVar3[0x27];
  if (plVar1 == puVar3 + 0x24) {
    lVar2 = 0x20;
LAB_000044b0:
    (**(code **)(*plVar1 + lVar2))();
  }
  else if (plVar1 != (long *)0x0) {
    lVar2 = 0x28;
    goto LAB_000044b0;
  }
  __ZdlPv(puVar3);
LAB_000044cc:
  *(undefined8 *)(param_1 + lVar4) = 0;
  pcStack_60 = &objc::class_t::BufferedFilePlaybackAudioUnit;
  local_68 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_68,"dealloc");
  return;
}

// ==== 00004500 ___clang_call_terminate ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void ___clang_call_terminate
               (undefined8 param_1,undefined8 param_2,ID param_3,bool param_4,ID param_5)

{
  undefined *puVar1;
  bool bVar2;
  ID IVar3;
  ID IVar4;
  ID self;
  ID self_00;
  ID self_01;
  ID self_02;
  ID self_03;
  undefined8 *puVar5;
  SEL extraout_x1;
  SEL extraout_x1_00;
  SEL op;
  SEL op_00;
  SEL op_01;
  SEL op_02;
  SEL extraout_x1_01;
  SEL op_03;
  SEL op_04;
  SEL op_05;
  SEL op_06;
  SEL op_07;
  SEL op_08;
  SEL op_09;
  SEL op_10;
  SEL op_11;
  SEL op_12;
  SEL extraout_x1_02;
  SEL pcVar6;
  SEL op_13;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  undefined1 auVar11 [16];
  undefined1 auStack_1e8 [8];
  undefined *puStack_1e0;
  undefined8 uStack_1d8;
  code *pcStack_1d0;
  undefined *puStack_1c8;
  undefined8 *puStack_1c0;
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  code *pcStack_1a8;
  undefined *puStack_1a0;
  undefined8 *puStack_198;
  undefined8 uStack_190;
  undefined8 *puStack_188;
  undefined8 uStack_180;
  long lStack_178;
  undefined1 auStack_170 [8];
  undefined1 auStack_168 [8];
  undefined1 auStack_160 [8];
  undefined1 auStack_158 [8];
  undefined *puStack_150;
  undefined1 auStack_148 [16];
  undefined **ppuStack_138;
  ID IStack_130;
  ID IStack_128;
  undefined *puStack_120;
  undefined1 auStack_118 [16];
  undefined **ppuStack_108;
  undefined *puStack_100;
  undefined1 auStack_f8 [16];
  undefined **ppuStack_e8;
  undefined *puStack_e0;
  undefined1 auStack_d8 [16];
  undefined **ppuStack_c8;
  ID IStack_c0;
  ID IStack_b8;
  ID IStack_b0;
  ID IStack_a8;
  ID IStack_a0;
  ID IStack_98;
  long lStack_90;
  
  ___cxa_begin_catch();
  auVar11 = __ZSt9terminatev();
  IVar3 = auVar11._0_8_;
  lStack_90 = *(long *)PTR____stack_chk_guard_00010040;
  BufferedFilePlaybackAudioUnit::setUrl_(IVar3,auVar11._8_8_,param_3);
  BufferedFilePlaybackAudioUnit::setIsMaster_(IVar3,extraout_x1,param_4);
  BufferedFilePlaybackAudioUnit::setDelegate_(IVar3,extraout_x1_00,param_5);
  _objc_initWeak(auStack_158,IVar3);
  IVar4 = AUParameterTree::
          createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                    ((ID)&_OBJC_CLASS___AUParameterTree,op,0,0x3f800000,&cf_isPlayingParameter,
                     &cf_isPlaying,0,0x1a,0,0,0,0);
  self = AUParameterTree::
         createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                   ((ID)&_OBJC_CLASS___AUParameterTree,op_00,0,0x3f800000,&cf_isMutedParameter,
                    &cf_isMuted,1,0x1a,0,0,0,0);
  AUParameterTree::setValue_(IVar4,op_01,0);
  AUParameterTree::setValue_(self,op_02,0);
  bVar2 = BufferedFilePlaybackAudioUnit::isMaster(IVar3,extraout_x1_01);
  if (bVar2 == 0) {
    IStack_130 = IVar4;
    IStack_128 = self;
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,op_03,&IStack_130,2);
    IVar4 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,op_13,IVar4)
    ;
    lVar8 = (long)BufferedFilePlaybackAudioUnit::_parameterTree;
    *(ID *)(IVar3 + lVar8) = IVar4;
    lVar10 = (long)BufferedFilePlaybackAudioUnit::_dspKernel;
    lStack_178 = *(long *)(IVar3 + lVar10);
    if (lStack_178 == 0) {
      __Znwm(0x170);
      lStack_178 = __ZN29BufferedFilePlaybackDSPKernelC2Ev();
      *(long *)(IVar3 + lVar10) = lStack_178;
    }
  }
  else {
    self_00 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,op_03,0,0x7f7fffff,
                         &cf_startTimeParameter,&cf_startTime,2,4,0,0,0,0);
    self_01 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,op_04,0,0x7f7fffff,&cf_endTimeParameter,
                         &cf_endTime,3,4,0,0,0,0);
    self_02 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,op_05,0,0x7f7fffff,
                         &cf_enqueuedStartTimeParameter,&cf_enqueuedStartTime,4,4,0,0,0,0);
    self_03 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,op_06,0,0x7f7fffff,
                         &cf_enqueuedEndTimeParameter,&cf_enqueuedEndTime,5,4,0,0,0,0);
    AUParameterTree::setValue_(self_00,op_07,0);
    AUParameterTree::setValue_(self_01,op_08,0x7f7fffff);
    AUParameterTree::setValue_(self_02,op_09,0xbf800000);
    AUParameterTree::setValue_(self_03,op_10,0xbf800000);
    IStack_c0 = IVar4;
    IStack_b8 = self;
    IStack_b0 = self_00;
    IStack_a8 = self_01;
    IStack_a0 = self_02;
    IStack_98 = self_03;
    IVar4 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,op_11,&IStack_c0,6);
    IVar4 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,op_12,IVar4)
    ;
    lVar8 = (long)BufferedFilePlaybackAudioUnit::_parameterTree;
    *(ID *)(IVar3 + lVar8) = IVar4;
    lVar9 = (long)BufferedFilePlaybackAudioUnit::_dspKernel;
    lVar10 = *(long *)(IVar3 + lVar9);
    pcVar6 = extraout_x1_02;
    if (lVar10 == 0) {
      lVar10 = __Znwm(0x218);
      auVar11 = __ZN29BufferedFilePlaybackDSPKernelC2Ev();
      pcVar6 = auVar11._8_8_;
      puVar5 = auVar11._0_8_;
      *puVar5 = &DAT_00010208;
      *(undefined4 *)(puVar5 + 0x2e) = 0;
      *(int *)((long)puVar5 + 0x174) = (int)*(float *)(puVar5 + 2);
      puVar5[0x2f] = 0xffffffffffffffff;
      *(undefined4 *)(puVar5 + 0x30) = 0;
      *(int *)((long)puVar5 + 0x184) = (int)*(float *)(puVar5 + 2);
      puVar5[0x34] = 0;
      puVar5[0x38] = 0;
      puVar5[0x3d] = 0;
      puVar5[0x3c] = 0;
      puVar5[0x3f] = 0;
      puVar5[0x3e] = 0;
      puVar5[0x41] = 0;
      puVar5[0x40] = 0;
      puVar5[0x42] = 0;
      *(undefined8 **)(IVar3 + lVar9) = puVar5;
    }
    IVar4 = BufferedFilePlaybackAudioUnit::delegate(IVar3,pcVar6);
    if (IVar4 != 0) {
      _objc_copyWeak(auStack_160,auStack_158);
      ppuStack_c8 = (undefined **)0x0;
      puStack_e0 = &DAT_000102c8;
      _objc_moveWeak(auStack_d8,auStack_160);
      ppuStack_c8 = &puStack_e0;
      _objc_destroyWeak(auStack_160);
      __ZNSt3__18functionIFvfEEaSERKS2_(lVar10 + 0x188,&puStack_e0);
      if (ppuStack_c8 == &puStack_e0) {
        lVar7 = 0x20;
LAB_00004958:
        (**(code **)(*ppuStack_c8 + lVar7))();
      }
      else if (ppuStack_c8 != (undefined **)0x0) {
        lVar7 = 0x28;
        goto LAB_00004958;
      }
      _objc_copyWeak(auStack_168,auStack_158);
      ppuStack_e8 = (undefined **)0x0;
      puStack_100 = &DAT_00010358;
      _objc_moveWeak(auStack_f8,auStack_168);
      ppuStack_e8 = &puStack_100;
      _objc_destroyWeak(auStack_168);
      __ZNSt3__18functionIFvvEEaSERKS2_(lVar10 + 0x1a8,&puStack_100);
      if (ppuStack_e8 == &puStack_100) {
        lVar7 = 0x20;
LAB_000049c4:
        (**(code **)(*ppuStack_e8 + lVar7))();
      }
      else if (ppuStack_e8 != (undefined **)0x0) {
        lVar7 = 0x28;
        goto LAB_000049c4;
      }
      _objc_copyWeak(auStack_170,auStack_158);
      ppuStack_108 = (undefined **)0x0;
      puStack_120 = &DAT_000103e8;
      _objc_moveWeak(auStack_118,auStack_170);
      ppuStack_108 = &puStack_120;
      _objc_destroyWeak(auStack_170);
      __ZNSt3__18functionIFvvEEaSERKS2_(lVar10 + 0x1c8,&puStack_120);
      if (ppuStack_108 == &puStack_120) {
        lVar10 = 0x20;
      }
      else {
        if (ppuStack_108 == (undefined **)0x0) goto LAB_00004a40;
        lVar10 = 0x28;
      }
      (**(code **)(*ppuStack_108 + lVar10))();
    }
LAB_00004a40:
    lStack_178 = *(long *)(IVar3 + lVar9);
  }
  puVar1 = PTR___NSConcreteStackBlock_00010038;
  uStack_190 = 0;
  uStack_180 = 0x2020000000;
  puStack_1b8 = PTR___NSConcreteStackBlock_00010038;
  uStack_1b0 = 0xc2000000;
  pcStack_1a8 = 
  ___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke
  ;
  puStack_1a0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
  puStack_198 = &uStack_190;
  puStack_188 = &uStack_190;
  objc_stub::setImplementorValueObserver_(*(ID *)(IVar3 + lVar8),&puStack_1b8);
  puStack_1e0 = puVar1;
  uStack_1d8 = 0xc2000000;
  pcStack_1d0 = 
  ___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke_32
  ;
  puStack_1c8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
  puStack_1c0 = &uStack_190;
  objc_stub::setImplementorValueProvider_(*(ID *)(IVar3 + lVar8),&puStack_1e0);
  objc_stub::setImplementorStringFromValueCallback_(*(ID *)(IVar3 + lVar8),&___block_literal_global)
  ;
  lVar8 = puStack_188[3];
  _objc_copyWeak(auStack_1e8,auStack_158);
  ppuStack_138 = (undefined **)0x0;
  puStack_150 = &DAT_00010468;
  _objc_moveWeak(auStack_148,auStack_1e8);
  ppuStack_138 = &puStack_150;
  _objc_destroyWeak(auStack_1e8);
  __ZNSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEaSERKS6_
            (lVar8 + 0x120,&puStack_150);
  if (ppuStack_138 == &puStack_150) {
    lVar8 = 0x20;
  }
  else {
    if (ppuStack_138 == (undefined **)0x0) goto LAB_00004b6c;
    lVar8 = 0x28;
  }
  (**(code **)(*ppuStack_138 + lVar8))();
LAB_00004b6c:
  __Block_object_dispose(&uStack_190,8);
  _objc_destroyWeak(auStack_158);
  if (*(long *)PTR____stack_chk_guard_00010040 == lStack_90) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004510 BufferedFilePlaybackAudioUnit::configureDSPKernelWithFileURL:isMaster:delegate: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x24 bytes */

void BufferedFilePlaybackAudioUnit::configureDSPKernelWithFileURL_isMaster_delegate_
               (ID param_1,SEL param_2,ID param_3,bool param_4,ID param_5)

{
  undefined *puVar1;
  bool bVar2;
  ID IVar3;
  ID self;
  ID self_00;
  ID self_01;
  ID self_02;
  ID self_03;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  undefined1 auStack_1d8 [8];
  undefined *local_1d0;
  undefined8 local_1c8;
  code *local_1c0;
  undefined *puStack_1b8;
  undefined8 *local_1b0;
  undefined *local_1a8;
  undefined8 local_1a0;
  code *local_198;
  undefined *puStack_190;
  undefined8 *local_188;
  undefined8 local_180;
  undefined8 *local_178;
  undefined8 local_170;
  long local_168;
  undefined1 auStack_160 [8];
  undefined1 auStack_158 [8];
  undefined1 auStack_150 [8];
  undefined1 auStack_148 [8];
  undefined *local_140;
  undefined1 auStack_138 [16];
  undefined **local_128;
  ID local_120;
  ID IStack_118;
  undefined *local_110;
  undefined1 auStack_108 [16];
  undefined **local_f8;
  undefined *local_f0;
  undefined1 auStack_e8 [16];
  undefined **local_d8;
  undefined *local_d0;
  undefined1 auStack_c8 [16];
  undefined **local_b8;
  ID local_b0;
  ID IStack_a8;
  ID local_a0;
  ID IStack_98;
  ID local_90;
  ID IStack_88;
  long local_80;
  
  local_80 = *(long *)PTR____stack_chk_guard_00010040;
  setUrl_(param_1,param_3);
  setIsMaster_(param_1,param_4);
  setDelegate_(param_1,param_5);
  _objc_initWeak(auStack_148,param_1);
  IVar3 = AUParameterTree::
          createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                    ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isPlayingParameter,
                     &cf_isPlaying,0,0x1a,0,0,0,0);
  self = AUParameterTree::
         createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                   ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isMutedParameter,&cf_isMuted
                    ,1,0x1a,0,0,0,0);
  AUParameterTree::setValue_(IVar3,0);
  AUParameterTree::setValue_(self,0);
  bVar2 = isMaster(param_1);
  if (bVar2 == 0) {
    local_120 = IVar3;
    IStack_118 = self;
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_120,2);
    IVar3 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar3);
    lVar6 = (long)_parameterTree;
    *(ID *)(param_1 + lVar6) = IVar3;
    lVar8 = (long)_dspKernel;
    local_168 = *(long *)(param_1 + lVar8);
    if (local_168 == 0) {
      __Znwm(0x170);
      local_168 = __ZN29BufferedFilePlaybackDSPKernelC2Ev();
      *(long *)(param_1 + lVar8) = local_168;
    }
  }
  else {
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
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,
                         &cf_enqueuedStartTimeParameter,&cf_enqueuedStartTime,4,4,0,0,0,0);
    self_03 = AUParameterTree::
              createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                        ((ID)&_OBJC_CLASS___AUParameterTree,0,0x7f7fffff,
                         &cf_enqueuedEndTimeParameter,&cf_enqueuedEndTime,5,4,0,0,0,0);
    AUParameterTree::setValue_(self_00,0);
    AUParameterTree::setValue_(self_01,0x7f7fffff);
    AUParameterTree::setValue_(self_02,0xbf800000);
    AUParameterTree::setValue_(self_03,0xbf800000);
    local_b0 = IVar3;
    IStack_a8 = self;
    local_a0 = self_00;
    IStack_98 = self_01;
    local_90 = self_02;
    IStack_88 = self_03;
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_b0,6);
    IVar3 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar3);
    lVar6 = (long)_parameterTree;
    *(ID *)(param_1 + lVar6) = IVar3;
    lVar7 = (long)_dspKernel;
    lVar8 = *(long *)(param_1 + lVar7);
    if (lVar8 == 0) {
      lVar8 = __Znwm(0x218);
      puVar4 = (undefined8 *)__ZN29BufferedFilePlaybackDSPKernelC2Ev();
      *puVar4 = &DAT_00010208;
      *(undefined4 *)(puVar4 + 0x2e) = 0;
      *(int *)((long)puVar4 + 0x174) = (int)*(float *)(puVar4 + 2);
      puVar4[0x2f] = 0xffffffffffffffff;
      *(undefined4 *)(puVar4 + 0x30) = 0;
      *(int *)((long)puVar4 + 0x184) = (int)*(float *)(puVar4 + 2);
      puVar4[0x34] = 0;
      puVar4[0x38] = 0;
      puVar4[0x3d] = 0;
      puVar4[0x3c] = 0;
      puVar4[0x3f] = 0;
      puVar4[0x3e] = 0;
      puVar4[0x41] = 0;
      puVar4[0x40] = 0;
      puVar4[0x42] = 0;
      *(undefined8 **)(param_1 + lVar7) = puVar4;
    }
    IVar3 = delegate(param_1);
    if (IVar3 != 0) {
      _objc_copyWeak(auStack_150,auStack_148);
      local_b8 = (undefined **)0x0;
      local_d0 = &DAT_000102c8;
      _objc_moveWeak(auStack_c8,auStack_150);
      local_b8 = &local_d0;
      _objc_destroyWeak(auStack_150);
      __ZNSt3__18functionIFvfEEaSERKS2_(lVar8 + 0x188,&local_d0);
      if (local_b8 == &local_d0) {
        lVar5 = 0x20;
LAB_00004958:
        (**(code **)(*local_b8 + lVar5))();
      }
      else if (local_b8 != (undefined **)0x0) {
        lVar5 = 0x28;
        goto LAB_00004958;
      }
      _objc_copyWeak(auStack_158,auStack_148);
      local_d8 = (undefined **)0x0;
      local_f0 = &DAT_00010358;
      _objc_moveWeak(auStack_e8,auStack_158);
      local_d8 = &local_f0;
      _objc_destroyWeak(auStack_158);
      __ZNSt3__18functionIFvvEEaSERKS2_(lVar8 + 0x1a8,&local_f0);
      if (local_d8 == &local_f0) {
        lVar5 = 0x20;
LAB_000049c4:
        (**(code **)(*local_d8 + lVar5))();
      }
      else if (local_d8 != (undefined **)0x0) {
        lVar5 = 0x28;
        goto LAB_000049c4;
      }
      _objc_copyWeak(auStack_160,auStack_148);
      local_f8 = (undefined **)0x0;
      local_110 = &DAT_000103e8;
      _objc_moveWeak(auStack_108,auStack_160);
      local_f8 = &local_110;
      _objc_destroyWeak(auStack_160);
      __ZNSt3__18functionIFvvEEaSERKS2_(lVar8 + 0x1c8,&local_110);
      if (local_f8 == &local_110) {
        lVar8 = 0x20;
      }
      else {
        if (local_f8 == (undefined **)0x0) goto LAB_00004a40;
        lVar8 = 0x28;
      }
      (**(code **)(*local_f8 + lVar8))();
    }
LAB_00004a40:
    local_168 = *(long *)(param_1 + lVar7);
  }
  puVar1 = PTR___NSConcreteStackBlock_00010038;
  local_180 = 0;
  local_170 = 0x2020000000;
  local_1a8 = PTR___NSConcreteStackBlock_00010038;
  local_1a0 = 0xc2000000;
  local_198 = 
  ___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke
  ;
  puStack_190 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
  local_188 = &local_180;
  local_178 = &local_180;
  objc_stub::setImplementorValueObserver_(*(ID *)(param_1 + lVar6),&local_1a8);
  local_1d0 = puVar1;
  local_1c8 = 0xc2000000;
  local_1c0 = 
  ___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke_32
  ;
  puStack_1b8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
  local_1b0 = &local_180;
  objc_stub::setImplementorValueProvider_(*(ID *)(param_1 + lVar6),&local_1d0);
  objc_stub::setImplementorStringFromValueCallback_
            (*(ID *)(param_1 + lVar6),&___block_literal_global);
  lVar6 = local_178[3];
  _objc_copyWeak(auStack_1d8,auStack_148);
  local_128 = (undefined **)0x0;
  local_140 = &DAT_00010468;
  _objc_moveWeak(auStack_138,auStack_1d8);
  local_128 = &local_140;
  _objc_destroyWeak(auStack_1d8);
  __ZNSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEaSERKS6_
            (lVar6 + 0x120,&local_140);
  if (local_128 == &local_140) {
    lVar6 = 0x20;
  }
  else {
    if (local_128 == (undefined **)0x0) goto LAB_00004b6c;
    lVar6 = 0x28;
  }
  (**(code **)(*local_128 + lVar6))();
LAB_00004b6c:
  __Block_object_dispose(&local_180,8);
  _objc_destroyWeak(auStack_148);
  if (*(long *)PTR____stack_chk_guard_00010040 == local_80) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 00004d28 ___81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]_block_invoke ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke
          (undefined4 param_1,long param_2,ID param_3)

{
  ID IVar1;
  long *plVar2;
  
  plVar2 = *(long **)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  (**(code **)(*plVar2 + 0x20))(param_1,plVar2,IVar1);
  return 0;
}

// ==== 00004d9c ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00004dac ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00004db8 ___81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]_block_invoke.32 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke_32
          (long param_1,ID param_2)

{
  ID IVar1;
  long *plVar2;
  
  plVar2 = *(long **)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  (**(code **)(*plVar2 + 0x28))(plVar2,IVar1);
  return 0;
}

// ==== 00004e30 ___81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]_block_invoke.34 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate___block_invoke_34
          (undefined8 param_1,ID param_2,long param_3)

{
  ID IVar1;
  cfstringStruct *pcVar2;
  
  if (param_3 == 0) {
    objc_stub::value(param_2);
  }
  IVar1 = objc_stub::address(param_2);
  if (IVar1 - 2 < 4) {
    pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__f);
  }
  else if (IVar1 < 2) {
    pcVar2 = (cfstringStruct *)NSString::stringWithFormat_((ID)&_OBJC_CLASS___NSString,&cf__d);
  }
  else {
    pcVar2 = &cf__;
  }
  return pcVar2;
}

// ==== 00004f1c BufferedFilePlaybackAudioUnit::prepareToPlayFromPlayheadPosition: ====
/* Function Stack Size: 0x14 bytes */

void BufferedFilePlaybackAudioUnit::prepareToPlayFromPlayheadPosition_
               (ID param_1,SEL param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = isMaster(param_1);
  if (bVar1 != 0) {
                    /* WARNING: Could not recover jumptable at 0x00004f58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + (long)_dspKernel) + 0x30))
              (*(long **)(param_1 + (long)_dspKernel),param_3);
    return;
  }
  return;
}

// ==== 00004f68 BufferedFilePlaybackAudioUnit::prepareToPlayFromTime: ====
/* Function Stack Size: 0x14 bytes */

void BufferedFilePlaybackAudioUnit::prepareToPlayFromTime_(ID param_1,SEL param_2,float param_3)

{
  bool bVar1;
  long *plVar2;
  
  bVar1 = isMaster(param_1);
  if (bVar1 != 0) {
    plVar2 = *(long **)(param_1 + (long)_dspKernel);
                    /* WARNING: Could not recover jumptable at 0x00004fb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x30))(plVar2,(int)(*(float *)(plVar2 + 2) * param_3));
    return;
  }
  return;
}

// ==== 00004fc8 BufferedFilePlaybackAudioUnit::setChannelsGain: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setChannelsGain_(ID param_1,SEL param_2,ID param_3)

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
  *(undefined4 *)(lVar2 + 0xd8) = extraout_s0;
  *(undefined4 *)(lVar2 + 0xdc) = extraout_s0_00;
  return;
}

// ==== 00005088 BufferedFilePlaybackAudioUnit::assignFollowersWithFilePlayerAudioUnits:clickAudioUnits: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void BufferedFilePlaybackAudioUnit::assignFollowersWithFilePlayerAudioUnits_clickAudioUnits_
               (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ID IVar7;
  undefined8 local_1f0;
  long lStack_1e8;
  long *local_1e0;
  undefined8 uStack_1d8;
  undefined8 local_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 local_1b0;
  long lStack_1a8;
  long *local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined1 auStack_168 [128];
  undefined1 auStack_e8 [128];
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_00010040;
  bVar1 = isMaster(param_1);
  if ((bVar1 & 1) != 0) {
    lVar5 = (long)_dspKernel;
    lVar4 = *(long *)(param_1 + lVar5);
    *(undefined8 *)(lVar4 + 0x1f0) = *(undefined8 *)(lVar4 + 0x1e8);
    *(undefined8 *)(lVar4 + 0x208) = *(undefined8 *)(lVar4 + 0x200);
    lStack_1a8 = 0;
    local_1b0 = 0;
    uStack_198 = 0;
    local_1a0 = (long *)0x0;
    uStack_188 = 0;
    local_190 = 0;
    uStack_178 = 0;
    uStack_180 = 0;
    IVar2 = objc_stub::countByEnumeratingWithState_objects_count_
                      (param_3,&local_1b0,auStack_e8,0x10);
    if (IVar2 != 0) {
      lVar6 = *local_1a0;
      do {
        IVar7 = 0;
        do {
          if (*local_1a0 != lVar6) {
            _objc_enumerationMutation(param_3);
          }
          __ZN35BufferedFilePlaybackDSPKernelMaster21addFilePlayerFollowerEP29BufferedFilePlaybackDSPKernel
                    (lVar4,*(undefined8 *)(*(long *)(lStack_1a8 + IVar7 * 8) + lVar5));
          IVar7 = IVar7 + 1;
        } while (IVar2 != IVar7);
        IVar2 = objc_stub::countByEnumeratingWithState_objects_count_
                          (param_3,&local_1b0,auStack_e8,0x10);
      } while (IVar2 != 0);
    }
    uStack_1c8 = 0;
    local_1d0 = 0;
    uStack_1b8 = 0;
    uStack_1c0 = 0;
    lStack_1e8 = 0;
    local_1f0 = 0;
    uStack_1d8 = 0;
    local_1e0 = (long *)0x0;
    IVar2 = objc_stub::countByEnumeratingWithState_objects_count_
                      (param_4,&local_1f0,auStack_168,0x10);
    if (IVar2 != 0) {
      lVar5 = *local_1e0;
      do {
        IVar7 = 0;
        do {
          if (*local_1e0 != lVar5) {
            _objc_enumerationMutation(param_4);
          }
          IVar3 = objc_stub::mtDSPKernelAsVoid(*(ID *)(lStack_1e8 + IVar7 * 8));
          __ZN35BufferedFilePlaybackDSPKernelMaster11addFollowerEP11MTDSPKernel(lVar4,IVar3);
          IVar7 = IVar7 + 1;
        } while (IVar2 != IVar7);
        IVar2 = objc_stub::countByEnumeratingWithState_objects_count_
                          (param_4,&local_1f0,auStack_168,0x10);
      } while (IVar2 != 0);
    }
  }
  if (*(long *)PTR____stack_chk_guard_00010040 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return;
}

// ==== 000052d4 __ZN35BufferedFilePlaybackDSPKernelMaster21addFilePlayerFollowerEP29BufferedFilePlaybackDSPKernel ====
void __ZN35BufferedFilePlaybackDSPKernelMaster21addFilePlayerFollowerEP29BufferedFilePlaybackDSPKernel
               (long param_1,undefined8 param_2)

{
  ulong uVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  void *pvVar5;
  undefined8 *puVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined1 auVar9 [16];
  
  puVar6 = *(undefined8 **)(param_1 + 0x208);
  if (puVar6 < *(undefined8 **)(param_1 + 0x210)) {
    puVar8 = puVar6 + 1;
    *puVar6 = param_2;
  }
  else {
    lVar7 = (long)puVar6 - *(long *)(param_1 + 0x200) >> 3;
    uVar1 = lVar7 + 1;
    if (uVar1 >> 0x3d != 0) {
                    /* WARNING: Subroutine does not return */
      __ZNKSt3__16vectorIP29BufferedFilePlaybackDSPKernelNS_9allocatorIS2_EEE20__throw_length_errorB8ne190102Ev
                ();
    }
    uVar3 = (long)*(undefined8 **)(param_1 + 0x210) - *(long *)(param_1 + 0x200);
    uVar4 = (long)uVar3 >> 2;
    if (uVar4 <= uVar1) {
      uVar4 = uVar1;
    }
    if (0x7ffffffffffffff7 < uVar3) {
      uVar4 = 0x1fffffffffffffff;
    }
    if (uVar4 == 0) {
      auVar9 = ZEXT816(0);
    }
    else {
      auVar9 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                         (param_1 + 0x210);
    }
    puVar6 = (undefined8 *)(auVar9._0_8_ + lVar7 * 8);
    puVar8 = puVar6 + 1;
    *puVar6 = param_2;
    sVar2 = *(long *)(param_1 + 0x208) - (long)*(void **)(param_1 + 0x200);
    pvVar5 = (void *)((long)puVar6 - sVar2);
    _memcpy(pvVar5,*(void **)(param_1 + 0x200),sVar2);
    lVar7 = *(long *)(param_1 + 0x200);
    *(void **)(param_1 + 0x200) = pvVar5;
    *(undefined8 **)(param_1 + 0x208) = puVar8;
    *(long *)(param_1 + 0x210) = auVar9._0_8_ + auVar9._8_8_ * 8;
    if (lVar7 != 0) {
      __ZdlPv();
    }
  }
  *(undefined8 **)(param_1 + 0x208) = puVar8;
  return;
}

// ==== 000053ac __ZN35BufferedFilePlaybackDSPKernelMaster11addFollowerEP11MTDSPKernel ====
void __ZN35BufferedFilePlaybackDSPKernelMaster11addFollowerEP11MTDSPKernel
               (long param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 *puVar2;
  size_t sVar3;
  ulong uVar4;
  ulong uVar5;
  void *pvVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined1 auVar9 [16];
  
  puVar2 = *(undefined8 **)(param_1 + 0x1f0);
  if (puVar2 < *(undefined8 **)(param_1 + 0x1f8)) {
    puVar8 = puVar2 + 1;
    *puVar2 = param_2;
  }
  else {
    lVar7 = (long)puVar2 - *(long *)(param_1 + 0x1e8) >> 3;
    uVar1 = lVar7 + 1;
    if (uVar1 >> 0x3d != 0) {
                    /* WARNING: Subroutine does not return */
      __ZNKSt3__16vectorIP29BufferedFilePlaybackDSPKernelNS_9allocatorIS2_EEE20__throw_length_errorB8ne190102Ev
                (param_1 + 0x1e8);
    }
    uVar4 = (long)*(undefined8 **)(param_1 + 0x1f8) - *(long *)(param_1 + 0x1e8);
    uVar5 = (long)uVar4 >> 2;
    if (uVar5 <= uVar1) {
      uVar5 = uVar1;
    }
    if (0x7ffffffffffffff7 < uVar4) {
      uVar5 = 0x1fffffffffffffff;
    }
    if (uVar5 == 0) {
      auVar9 = ZEXT816(0);
    }
    else {
      auVar9 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                         (param_1 + 0x1f8);
    }
    puVar2 = (undefined8 *)(auVar9._0_8_ + lVar7 * 8);
    puVar8 = puVar2 + 1;
    *puVar2 = param_2;
    sVar3 = *(long *)(param_1 + 0x1f0) - (long)*(void **)(param_1 + 0x1e8);
    pvVar6 = (void *)((long)puVar2 - sVar3);
    _memcpy(pvVar6,*(void **)(param_1 + 0x1e8),sVar3);
    lVar7 = *(long *)(param_1 + 0x1e8);
    *(void **)(param_1 + 0x1e8) = pvVar6;
    *(undefined8 **)(param_1 + 0x1f0) = puVar8;
    *(long *)(param_1 + 0x1f8) = auVar9._0_8_ + auVar9._8_8_ * 8;
    if (lVar7 != 0) {
      __ZdlPv();
    }
  }
  *(undefined8 **)(param_1 + 0x1f0) = puVar8;
  return;
}

// ==== 00005478 BufferedFilePlaybackAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005488 BufferedFilePlaybackAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool BufferedFilePlaybackAudioUnit::allocateRenderResourcesAndReturnError_
               (ID param_1,SEL param_2,ID *param_3)

{
  ID IVar1;
  ID IVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  ID local_80;
  class_t *pcStack_78;
  
  pcStack_78 = &objc::class_t::BufferedFilePlaybackAudioUnit;
  local_80 = param_1;
  IVar1 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_80,"allocateRenderResourcesAndReturnError:");
  if ((int)IVar1 == 0) {
    return 0;
  }
  IVar1 = auOutputBus(param_1);
  IVar1 = objc_stub::format(IVar1);
  IVar1 = objc_stub::channelCount(IVar1);
  lVar5 = (long)_bufferedOutputBus;
  IVar2 = objc_stub::format(*(ID *)(param_1 + lVar5));
  IVar2 = objc_stub::channelCount(IVar2);
  if ((int)IVar1 == (int)IVar2) {
    IVar1 = url(param_1);
    if (IVar1 != 0) {
      IVar1 = NSFileManager::defaultManager((ID)&_OBJC_CLASS___NSFileManager);
      IVar2 = url(param_1);
      IVar2 = objc_stub::path(IVar2);
      IVar1 = NSFileManager::fileExistsAtPath_(IVar1,IVar2);
      if ((int)IVar1 != 0) {
        IVar1 = NSFileManager::defaultManager((ID)&_OBJC_CLASS___NSFileManager);
        IVar2 = url(param_1);
        IVar2 = objc_stub::path(IVar2);
        IVar1 = NSFileManager::isReadableFileAtPath_(IVar1,IVar2);
        if ((IVar1 & 1) != 0) {
          IVar1 = objc_stub::maximumFramesToRender(param_1);
          __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar5,IVar1);
          lVar5 = *(long *)(param_1 + (long)_dspKernel);
          IVar1 = auOutputBus(param_1);
          IVar1 = objc_stub::format(IVar1);
          IVar1 = objc_stub::channelCount(IVar1);
          IVar2 = auOutputBus(param_1);
          IVar2 = objc_stub::format(IVar2);
          objc_stub::sampleRate(IVar2);
          IVar2 = url(param_1);
          *(int *)(lVar5 + 0xc) = (int)IVar1;
          *(float *)(lVar5 + 0x10) = (float)(double)CONCAT44(extraout_var,extraout_s0);
          *(ID *)(lVar5 + 0x28) = IVar2;
          __ZN29BufferedFilePlaybackDSPKernel14setUpAudioFileEv(lVar5);
          __TPCircularBufferInit(lVar5 + 0xb8,*(undefined4 *)(lVar5 + 0xac),0x20);
          reset(param_1);
          return 1;
        }
      }
    }
    if (param_3 == (ID *)0x0) goto LAB_0000578c;
    uVar3 = *(undefined8 *)PTR__NSOSStatusErrorDomain_00010000;
    uVar4 = 0xffffffffffffd589;
  }
  else {
    if (param_3 == (ID *)0x0) goto LAB_0000578c;
    uVar3 = *(undefined8 *)PTR__NSOSStatusErrorDomain_00010000;
    uVar4 = 0xffffffffffffd585;
  }
  IVar1 = NSError::errorWithDomain_code_userInfo_((ID)&_OBJC_CLASS___NSError,uVar3,uVar4,0);
  *param_3 = IVar1;
LAB_0000578c:
  objc_stub::setRenderResourcesAllocated_(param_1,0);
  return 0;
}

// ==== 00005894 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00005934 BufferedFilePlaybackAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void BufferedFilePlaybackAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

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
  local_48 = PTR___NSConcreteStackBlock_00010038;
  local_40 = 0xc0000000;
  local_38 = ____ZN29BufferedFilePlaybackDSPKernel7cleanupEv_block_invoke;
  puStack_30 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_28 + 0x68),&local_48);
  pcStack_50 = &objc::class_t::BufferedFilePlaybackAudioUnit;
  local_58 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_58,"deallocateRenderResources");
  return;
}

// ==== 000059d8 BufferedFilePlaybackAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_00010038;
  local_80 = 0xc2000000;
  local_78 = ___52__BufferedFilePlaybackAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00005aa0 ___52-[BufferedFilePlaybackAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___52__BufferedFilePlaybackAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)BufferedFilePlaybackAudioUnit::_bufferedOutputBus,
               param_6,param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0xa0) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 00005b48 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00005be0 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 00005c18 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 00005c44 BufferedFilePlaybackAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool BufferedFilePlaybackAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 00005c4c BufferedFilePlaybackAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 00005c5c BufferedFilePlaybackAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 00005c70 BufferedFilePlaybackAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 00005c90 BufferedFilePlaybackAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 00005ca4 BufferedFilePlaybackAudioUnit::auOutputBus ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 00005cb4 BufferedFilePlaybackAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00005cc0 BufferedFilePlaybackAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00005cd0 BufferedFilePlaybackAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 00005cdc BufferedFilePlaybackAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 00005cec BufferedFilePlaybackAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00005cf8 BufferedFilePlaybackAudioUnit::url ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::url(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_url);
}

// ==== 00005d08 BufferedFilePlaybackAudioUnit::setUrl: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void BufferedFilePlaybackAudioUnit::setUrl_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_url) = param_3;
  return;
}

// ==== 00005d14 BufferedFilePlaybackAudioUnit::isMaster ====
/* Function Stack Size: 0x10 bytes */

bool BufferedFilePlaybackAudioUnit::isMaster(ID param_1,SEL param_2)

{
  return *(byte *)(param_1 + (long)_isMaster) & 1;
}

// ==== 00005d28 BufferedFilePlaybackAudioUnit::setIsMaster: ====
/* Function Stack Size: 0x14 bytes */

void BufferedFilePlaybackAudioUnit::setIsMaster_(ID param_1,SEL param_2,bool param_3)

{
  *(char *)(param_1 + (long)_isMaster) = (char)param_3;
  return;
}

// ==== 00005d38 BufferedFilePlaybackAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void BufferedFilePlaybackAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_url) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 00005de0 BufferedFilePlaybackAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID BufferedFilePlaybackAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 00005e00 ____ZN29BufferedFilePlaybackDSPKernel5resetEv_block_invoke ====
void ____ZN29BufferedFilePlaybackDSPKernel5resetEv_block_invoke(long param_1)

{
  undefined1 *puVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x20);
  puVar1 = (undefined1 *)(lVar2 + 0x70);
  *puVar1 = 1;
  _TPCircularBufferClear(lVar2 + 0xb8);
  *puVar1 = 0;
  return;
}

// ==== 00005e34 ____ZN29BufferedFilePlaybackDSPKernel7cleanupEv_block_invoke ====
void ____ZN29BufferedFilePlaybackDSPKernel7cleanupEv_block_invoke(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x20);
  *(undefined1 *)(lVar1 + 0x70) = 1;
  _TPCircularBufferClear(lVar1 + 0xb8);
  _TPCircularBufferCleanup(lVar1 + 0xb8);
  if (*(long *)(lVar1 + 0x30) != 0) {
    _ExtAudioFileDispose();
    *(undefined8 *)(lVar1 + 0x30) = 0;
  }
  *(undefined1 *)(lVar1 + 0x70) = 0;
  return;
}

// ==== 00005e80 __ZN29BufferedFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN29BufferedFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp
               (long param_1,uint param_2,int param_3,undefined8 *param_4)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  int iVar10;
  ulong uVar11;
  long *plVar12;
  ulong uVar13;
  float *pfVar14;
  long lVar15;
  float fVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  
  uVar18 = param_4[1];
  uVar17 = *param_4;
  uVar20 = param_4[3];
  uVar19 = param_4[2];
  uVar21 = param_4[4];
  uVar23 = param_4[7];
  uVar22 = param_4[6];
  *(undefined8 *)(param_1 + 0x108) = param_4[5];
  *(undefined8 *)(param_1 + 0x100) = uVar21;
  *(undefined8 *)(param_1 + 0x118) = uVar23;
  *(undefined8 *)(param_1 + 0x110) = uVar22;
  *(undefined8 *)(param_1 + 0xe8) = uVar18;
  *(undefined8 *)(param_1 + 0xe0) = uVar17;
  *(undefined8 *)(param_1 + 0xf8) = uVar20;
  *(undefined8 *)(param_1 + 0xf0) = uVar19;
  if ((*(byte *)(param_1 + 8) & 1) == 0) {
    if (param_2 != 0) {
      uVar11 = 0;
      uVar2 = *(uint *)(param_1 + 0xc);
      do {
        if (0 < (int)uVar2) {
          plVar12 = *(long **)(param_1 + 0xa0);
          uVar13 = (ulong)uVar2;
          pfVar14 = (float *)(param_1 + 0xd8);
          do {
            plVar12 = plVar12 + 2;
            *(float *)(*plVar12 + (long)((int)uVar11 + param_3) * 4) = *pfVar14 * 0.0;
            uVar13 = uVar13 - 1;
            pfVar14 = pfVar14 + 1;
          } while (uVar13 != 0);
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 != param_2);
    }
  }
  else {
    puVar1 = (uint *)(param_1 + 0xcc);
    if (*puVar1 == 0) {
      lVar8 = 0;
    }
    else {
      lVar8 = *(long *)(param_1 + 0xb8) + (ulong)*(uint *)(param_1 + 0xc4);
    }
    iVar9 = *(int *)(param_1 + 0xc);
    if (param_2 == 0) {
      iVar10 = 0;
    }
    else {
      uVar11 = 0;
      iVar10 = 0;
      uVar13 = 0;
      if ((long)iVar9 != 0) {
        uVar13 = (ulong)(*puVar1 >> 2) / (ulong)(long)iVar9;
      }
      do {
        if (0 < iVar9) {
          lVar15 = 0;
          lVar7 = 0x10;
          do {
            fVar16 = 0.0;
            if (uVar11 < uVar13) {
              if ((*(byte *)(param_1 + 9) & 1) == 0) {
                fVar16 = *(float *)(lVar8 + (long)((int)lVar15 + (int)uVar11 * iVar9) * 4);
              }
              if (lVar15 == 0) {
                iVar10 = iVar10 + 1;
              }
              iVar9 = *(int *)(param_1 + 0xc);
            }
            *(float *)(*(long *)(*(long *)(param_1 + 0xa0) + lVar7) +
                      (long)((int)uVar11 + param_3) * 4) =
                 fVar16 * *(float *)(param_1 + 0xd8 + lVar15 * 4);
            lVar15 = lVar15 + 1;
            lVar7 = lVar7 + 0x10;
          } while (lVar15 < iVar9);
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 != param_2);
      iVar10 = iVar10 << 2;
    }
    iVar9 = iVar9 * iVar10;
    if ((*puVar1 != 0) || (iVar9 < 1)) {
      uVar3 = *(uint *)(param_1 + 0xc0);
      uVar2 = *(int *)(param_1 + 0xc4) + iVar9;
      uVar6 = 0;
      if (uVar3 != 0) {
        uVar6 = uVar2 / uVar3;
      }
      *(uint *)(param_1 + 0xc4) = uVar2 - uVar6 * uVar3;
      if ((*(byte *)(param_1 + 0xd0) & 1) == 0) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar5) {
            *puVar1 = *puVar1 - iVar9;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
      }
      else {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar5) {
            *puVar1 = *puVar1 - iVar9;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
      }
      if ((int)*puVar1 < 0) {
        __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_cold_1();
        return;
      }
    }
  }
  return;
}

// ==== 00006038 __ZN29BufferedFilePlaybackDSPKernel9startRampEyfj ====
void __ZN29BufferedFilePlaybackDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 0000603c __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 00006040 __ZN11MTDSPKernel35syncRealTimeTimelineFrameWithMasterEi ====
void __ZN11MTDSPKernel35syncRealTimeTimelineFrameWithMasterEi(void)

{
  return;
}

// ==== 00006044 __ZN29BufferedFilePlaybackDSPKernel12setParameterEyf ====
void __ZN29BufferedFilePlaybackDSPKernel12setParameterEyf(float param_1,long param_2,long param_3)

{
  undefined *local_40;
  undefined8 local_38;
  code *local_30;
  undefined *puStack_28;
  long local_20;
  float local_18;
  
  if (param_3 == 1) {
    *(bool *)(param_2 + 9) = param_1 != 0.0;
  }
  else if (param_3 == 0) {
    local_40 = PTR___NSConcreteStackBlock_00010038;
    local_38 = 0xc0000000;
    local_30 = ____ZN29BufferedFilePlaybackDSPKernel12setParameterEyf_block_invoke;
    puStack_28 = &___block_descriptor_44_e5_v8__0l;
    local_20 = param_2;
    local_18 = param_1;
    _dispatch_async(*(undefined8 *)(param_2 + 0x68),&local_40);
    return;
  }
  return;
}

// ==== 000060c0 __ZN29BufferedFilePlaybackDSPKernel12getParameterEy ====
float __ZN29BufferedFilePlaybackDSPKernel12getParameterEy(long param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    lVar1 = 8;
  }
  else {
    if (param_2 != 1) {
      return 0.0;
    }
    lVar1 = 9;
  }
  return (float)(*(byte *)(param_1 + lVar1) & 1);
}

// ==== 000060f0 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(long param_1)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  
  puVar5 = *(undefined8 **)(param_1 + 8);
  puVar1 = *(undefined8 **)(param_1 + 0x10);
  *(undefined8 *)(param_1 + 0x28) = 0;
  lVar3 = (long)puVar1 - (long)puVar5;
  while (uVar2 = lVar3 >> 3, 2 < uVar2) {
    __ZdlPv(*puVar5);
    puVar1 = *(undefined8 **)(param_1 + 0x10);
    puVar5 = (undefined8 *)(*(long *)(param_1 + 8) + 8);
    *(undefined8 **)(param_1 + 8) = puVar5;
    lVar3 = (long)puVar1 - (long)puVar5;
  }
  if (uVar2 == 1) {
    uVar4 = 0x80;
  }
  else {
    if (uVar2 != 2) goto LAB_0000616c;
    uVar4 = 0x100;
  }
  *(undefined8 *)(param_1 + 0x20) = uVar4;
LAB_0000616c:
  for (; puVar5 != puVar1; puVar5 = puVar5 + 1) {
    __ZdlPv(*puVar5);
  }
  __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEED2Ev(param_1);
  return;
}

// ==== 00006188 __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEED2Ev ====
long * __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEED2Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[2];
  if (lVar1 != param_1[1]) {
    param_1[2] = lVar1 + ((param_1[1] - lVar1) + 7U & 0xfffffffffffffff8);
  }
  if (*param_1 != 0) {
    __ZdlPv();
  }
  return param_1;
}

// ==== 000061d4 ____ZN29BufferedFilePlaybackDSPKernel12setParameterEyf_block_invoke ====
void ____ZN29BufferedFilePlaybackDSPKernel12setParameterEyf_block_invoke(long param_1)

{
  *(bool *)(*(long *)(param_1 + 0x20) + 8) = *(float *)(param_1 + 0x28) != 0.0;
  return;
}

// ==== 000061f0 __ZN29BufferedFilePlaybackDSPKernelC2Ev ====
undefined8 * __ZN29BufferedFilePlaybackDSPKernelC2Ev(undefined8 *param_1)

{
  dispatch_queue_t pdVar1;
  undefined8 uVar2;
  
  *param_1 = &DAT_00010168;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined1 *)((long)param_1 + 10) = 0;
  *(undefined8 *)((long)param_1 + 0xc) = 0x472c440000000000;
  param_1[3] = 0x3ff0000000000000;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[6] = 0;
  param_1[0xc] = 0;
  pdVar1 = _dispatch_queue_create("BufferedFilePlaybackDSPKernelQueue",(dispatch_queue_attr_t)0x0);
  param_1[0xd] = pdVar1;
  *(undefined1 *)(param_1 + 0xe) = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0x2b11000005622;
  *(undefined4 *)(param_1 + 0x16) = 0x15888;
  uVar2 = NEON_fmov(0x3f800000,4);
  param_1[0x1b] = uVar2;
  param_1[0x28] = 0;
  param_1[0x27] = 0;
  param_1[0x2a] = 0;
  param_1[0x29] = 0;
  param_1[0x2c] = 0;
  param_1[0x2b] = 0;
  param_1[0x2d] = 0;
  return param_1;
}

// ==== 00006298 __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp ====
void __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp
               (long param_1,uint param_2,int param_3,undefined8 *param_4)

{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  uint uVar8;
  long *plVar9;
  long lVar10;
  long extraout_x1;
  undefined **ppuVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  ulong uVar15;
  uint uVar16;
  ulong uVar17;
  long lVar18;
  float *pfVar19;
  uint uVar20;
  long lVar21;
  undefined8 *puVar22;
  float fVar23;
  float extraout_s0;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined *puStack_f0;
  undefined8 uStack_e8;
  code *pcStack_e0;
  undefined *puStack_d8;
  long lStack_d0;
  float fStack_c8;
  undefined *puStack_c0;
  undefined8 uStack_b8;
  code *pcStack_b0;
  undefined *puStack_a8;
  long lStack_a0;
  float fStack_98;
  undefined1 *puStack_90;
  code *pcStack_88;
  undefined *local_80;
  undefined8 local_78;
  code *local_70;
  undefined *puStack_68;
  long local_60;
  float local_54;
  
  uVar24 = param_4[1];
  uVar14 = *param_4;
  uVar26 = param_4[3];
  uVar25 = param_4[2];
  uVar27 = param_4[4];
  uVar29 = param_4[7];
  uVar28 = param_4[6];
  *(undefined8 *)(param_1 + 0x108) = param_4[5];
  *(undefined8 *)(param_1 + 0x100) = uVar27;
  *(undefined8 *)(param_1 + 0x118) = uVar29;
  *(undefined8 *)(param_1 + 0x110) = uVar28;
  *(undefined8 *)(param_1 + 0xe8) = uVar24;
  *(undefined8 *)(param_1 + 0xe0) = uVar14;
  *(undefined8 *)(param_1 + 0xf8) = uVar26;
  *(undefined8 *)(param_1 + 0xf0) = uVar25;
  if ((*(byte *)(param_1 + 8) & 1) == 0) {
    if (param_2 == 0) {
      return;
    }
    uVar15 = 0;
    uVar4 = *(uint *)(param_1 + 0xc);
    do {
      if (0 < (int)uVar4) {
        plVar9 = *(long **)(param_1 + 0xa0);
        uVar17 = (ulong)uVar4;
        pfVar19 = (float *)(param_1 + 0xd8);
        do {
          plVar9 = plVar9 + 2;
          *(float *)(*plVar9 + (long)((int)uVar15 + param_3) * 4) = *pfVar19 * 0.0;
          uVar17 = uVar17 - 1;
          pfVar19 = pfVar19 + 1;
        } while (uVar17 != 0);
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 != param_2);
    return;
  }
  for (puVar22 = *(undefined8 **)(param_1 + 0x1e8); puVar22 < *(undefined8 **)(param_1 + 0x1f0);
      puVar22 = puVar22 + 1) {
    (**(code **)(*(long *)*puVar22 + 0x18))((long *)*puVar22,*(undefined4 *)(param_1 + 0x180));
  }
  puVar1 = (uint *)(param_1 + 0xcc);
  if (*puVar1 == 0) {
    lVar10 = 0;
  }
  else {
    lVar10 = *(long *)(param_1 + 0xb8) + (ulong)*(uint *)(param_1 + 0xc4);
  }
  uVar8 = *puVar1 >> 2;
  uVar4 = *(uint *)(param_1 + 0xc);
  if (param_2 == 0) {
    iVar12 = 0;
  }
  else {
    uVar15 = 0;
    iVar12 = 0;
    uVar17 = 0;
    uVar20 = uVar4;
    uVar16 = uVar4;
    if ((long)(int)uVar4 != 0) {
      uVar17 = (ulong)uVar8 / (ulong)(long)(int)uVar4;
    }
    do {
      if (0 < (int)uVar20) {
        lVar18 = 0;
        lVar21 = 0x10;
        do {
          fVar23 = 0.0;
          if (uVar15 < uVar17) {
            if ((*(byte *)(param_1 + 9) & 1) == 0) {
              fVar23 = *(float *)(lVar10 + (long)(int)((int)lVar18 + (int)uVar15 * uVar20) * 4);
            }
            if (lVar18 == 0) {
              iVar12 = iVar12 + 1;
            }
            uVar16 = *(uint *)(param_1 + 0xc);
          }
          uVar20 = uVar16;
          *(float *)(*(long *)(*(long *)(param_1 + 0xa0) + lVar21) +
                    (long)((int)uVar15 + param_3) * 4) =
               fVar23 * *(float *)(param_1 + 0xd8 + lVar18 * 4);
          lVar18 = lVar18 + 1;
          lVar21 = lVar21 + 0x10;
          uVar16 = uVar20;
        } while (lVar18 < (int)uVar20);
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 != param_2);
  }
  piVar2 = (int *)(param_1 + 0x180);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + iVar12;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  piVar2 = (int *)(param_1 + 0x180);
  piVar3 = (int *)(param_1 + 0x184);
  if (*piVar2 < *piVar3) {
LAB_000064a0:
    local_54 = (float)*piVar2 / *(float *)(param_1 + 0x10);
    plVar9 = *(long **)(param_1 + 0x1a0);
    if (plVar9 != (long *)0x0) {
      (**(code **)(*plVar9 + 0x30))(plVar9,&local_54);
      iVar12 = iVar12 * *(int *)(param_1 + 0xc);
      if ((*(int *)(param_1 + 0xcc) != 0) || (iVar12 * 4 < 1)) {
        uVar16 = *(uint *)(param_1 + 0xc0);
        uVar20 = *(int *)(param_1 + 0xc4) + iVar12 * 4;
        uVar7 = 0;
        if (uVar16 != 0) {
          uVar7 = uVar20 / uVar16;
        }
        *(uint *)(param_1 + 0xc4) = uVar20 - uVar7 * uVar16;
        if ((*(byte *)(param_1 + 0xd0) & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(puVar1,0x10);
            if (bVar6) {
              *puVar1 = *puVar1 + iVar12 * -4;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
        }
        else {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(puVar1,0x10);
            if (bVar6) {
              *puVar1 = *puVar1 + iVar12 * -4;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
        }
        if ((int)*puVar1 < 0) {
          __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_cold_1();
          goto LAB_000065ec;
        }
      }
      if (((*(int *)(param_1 + 0xcc) < *(int *)(param_1 + 0xb0)) &&
          ((*(byte *)(param_1 + 0x70) & 1) == 0)) && ((*(byte *)(param_1 + 10) & 1) == 0)) {
        local_80 = PTR___NSConcreteStackBlock_00010038;
        local_78 = 0xc0000000;
        local_70 = 
        ____ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_block_invoke;
        puStack_68 = &___block_descriptor_40_e5_v8__0l;
        local_60 = param_1;
        _dispatch_async(*(undefined8 *)(param_1 + 0x68),&local_80);
        return;
      }
      if (uVar4 <= uVar8) {
        return;
      }
      if ((*(byte *)(param_1 + 10) & 1) == 0) {
        return;
      }
      if (*(long **)(param_1 + 0x1e0) != (long *)0x0) {
        (**(code **)(**(long **)(param_1 + 0x1e0) + 0x30))();
        return;
      }
    }
  }
  else {
    *piVar2 = (*piVar2 - *piVar3) + *(int *)(param_1 + 0x170);
    *piVar3 = *(int *)(param_1 + 0x174);
    if (*(long **)(param_1 + 0x1c0) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x1c0) + 0x30))();
      goto LAB_000064a0;
    }
  }
LAB_000065ec:
  lVar10 = __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
  ppuVar11 = &puStack_f0;
  pcStack_88 = __ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf;
  puStack_90 = &stack0xfffffffffffffff0;
  if (extraout_x1 < 4) {
    if (extraout_x1 == 2) {
      uVar14 = *(undefined8 *)(lVar10 + 0x68);
      puStack_c0 = PTR___NSConcreteStackBlock_00010038;
      uStack_b8 = 0xc0000000;
      pcStack_b0 = ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke;
      puStack_a8 = &___block_descriptor_44_e5_v8__0l;
      ppuVar11 = &puStack_c0;
      lStack_a0 = lVar10;
      fStack_98 = extraout_s0;
    }
    else {
      if (extraout_x1 != 3) {
LAB_00006698:
        __ZN29BufferedFilePlaybackDSPKernel12setParameterEyf();
        return;
      }
      uVar14 = *(undefined8 *)(lVar10 + 0x68);
      puStack_f0 = PTR___NSConcreteStackBlock_00010038;
      uStack_e8 = 0xc0000000;
      pcStack_e0 = ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke_2;
      puStack_d8 = &___block_descriptor_44_e5_v8__0l;
      lStack_d0 = lVar10;
      fStack_c8 = extraout_s0;
    }
    _dispatch_async(uVar14,ppuVar11);
  }
  else if (extraout_x1 == 4) {
    if (0.0 <= extraout_s0) {
      iVar12 = (int)(*(double *)(lVar10 + 0x78) * (double)extraout_s0);
      if (*(long *)(lVar10 + 0x60) <= (long)iVar12) {
        iVar12 = -1;
      }
      *(int *)(lVar10 + 0x178) = iVar12;
    }
    else {
      *(undefined4 *)(lVar10 + 0x17c) = 0xffffffff;
    }
    if ((*(byte *)(lVar10 + 8) & 1) == 0) {
      *(undefined4 *)(lVar10 + 0x20) = *(undefined4 *)(lVar10 + 0x178);
      _ExtAudioFileSeek(*(undefined8 *)(lVar10 + 0x30),
                        (long)(*(double *)(lVar10 + 0x18) * (double)*(int *)(lVar10 + 0x170)));
      return;
    }
  }
  else {
    if (extraout_x1 != 5) goto LAB_00006698;
    if ((extraout_s0 < 0.0) ||
       (iVar12 = (int)(*(double *)(lVar10 + 0x78) * (double)extraout_s0),
       iVar12 <= *(int *)(lVar10 + 0x178))) {
      iVar13 = -1;
    }
    else {
      iVar13 = (int)*(long *)(lVar10 + 0x60);
      if ((long)iVar12 <= *(long *)(lVar10 + 0x60)) {
        iVar13 = iVar12;
      }
    }
    *(int *)(lVar10 + 0x17c) = iVar13;
  }
  return;
}

// ==== 000065f0 __ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf ====
void __ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf
               (float param_1,long param_2,long param_3)

{
  undefined **ppuVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined *local_70;
  undefined8 local_68;
  code *local_60;
  undefined *puStack_58;
  long local_50;
  float local_48;
  undefined *local_40;
  undefined8 local_38;
  code *local_30;
  undefined *puStack_28;
  long local_20;
  float local_18;
  
  ppuVar1 = &local_70;
  if (param_3 < 4) {
    if (param_3 == 2) {
      uVar4 = *(undefined8 *)(param_2 + 0x68);
      local_40 = PTR___NSConcreteStackBlock_00010038;
      local_38 = 0xc0000000;
      local_30 = ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke;
      puStack_28 = &___block_descriptor_44_e5_v8__0l;
      ppuVar1 = &local_40;
      local_20 = param_2;
      local_18 = param_1;
    }
    else {
      if (param_3 != 3) {
LAB_00006698:
        __ZN29BufferedFilePlaybackDSPKernel12setParameterEyf();
        return;
      }
      uVar4 = *(undefined8 *)(param_2 + 0x68);
      local_70 = PTR___NSConcreteStackBlock_00010038;
      local_68 = 0xc0000000;
      local_60 = ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke_2;
      puStack_58 = &___block_descriptor_44_e5_v8__0l;
      local_50 = param_2;
      local_48 = param_1;
    }
    _dispatch_async(uVar4,ppuVar1);
  }
  else if (param_3 == 4) {
    if (0.0 <= param_1) {
      iVar2 = (int)(*(double *)(param_2 + 0x78) * (double)param_1);
      if (*(long *)(param_2 + 0x60) <= (long)iVar2) {
        iVar2 = -1;
      }
      *(int *)(param_2 + 0x178) = iVar2;
    }
    else {
      *(undefined4 *)(param_2 + 0x17c) = 0xffffffff;
    }
    if ((*(byte *)(param_2 + 8) & 1) == 0) {
      *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_2 + 0x178);
      _ExtAudioFileSeek(*(undefined8 *)(param_2 + 0x30),
                        (long)(*(double *)(param_2 + 0x18) * (double)*(int *)(param_2 + 0x170)));
      return;
    }
  }
  else {
    if (param_3 != 5) goto LAB_00006698;
    if ((param_1 < 0.0) ||
       (iVar2 = (int)(*(double *)(param_2 + 0x78) * (double)param_1),
       iVar2 <= *(int *)(param_2 + 0x178))) {
      iVar3 = -1;
    }
    else {
      iVar3 = (int)*(long *)(param_2 + 0x60);
      if ((long)iVar2 <= *(long *)(param_2 + 0x60)) {
        iVar3 = iVar2;
      }
    }
    *(int *)(param_2 + 0x17c) = iVar3;
  }
  return;
}

// ==== 00006780 __ZN35BufferedFilePlaybackDSPKernelMaster12getParameterEy ====
float __ZN35BufferedFilePlaybackDSPKernelMaster12getParameterEy(long param_1,long param_2)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  
  if (param_2 < 3) {
    if (param_2 == 0) {
      lVar2 = 8;
LAB_000067e4:
      return (float)(*(byte *)(param_1 + lVar2) & 1);
    }
    if (param_2 == 1) {
      lVar2 = 9;
      goto LAB_000067e4;
    }
    if (param_2 != 2) {
      return 0.0;
    }
    piVar1 = (int *)(param_1 + 0x170);
  }
  else {
    if (param_2 != 3) {
      if (param_2 == 4) {
        iVar3 = *(int *)(param_1 + 0x178);
      }
      else {
        if (param_2 != 5) {
          return 0.0;
        }
        iVar3 = *(int *)(param_1 + 0x17c);
      }
      goto LAB_00006800;
    }
    piVar1 = (int *)(param_1 + 0x174);
  }
  iVar3 = *piVar1;
LAB_00006800:
  return (float)((double)iVar3 / *(double *)(param_1 + 0x78));
}

// ==== 00006814 __ZN35BufferedFilePlaybackDSPKernelMaster13prepareToPlayEi ====
void __ZN35BufferedFilePlaybackDSPKernelMaster13prepareToPlayEi(long param_1,uint param_2)

{
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  long lStack_20;
  uint local_18;
  
  if ((((-1 < (int)param_2) && (*(long *)(param_1 + 0x30) != 0)) &&
      ((long)(ulong)param_2 <= *(long *)(param_1 + 0x60))) && (*(int *)(param_1 + 0x90) != 0)) {
    lStack_20 = (long)(*(double *)(param_1 + 0x18) * (double)param_2);
    local_48 = PTR___NSConcreteStackBlock_00010038;
    local_40 = 0xc0000000;
    local_38 = ____ZN35BufferedFilePlaybackDSPKernelMaster13prepareToPlayEi_block_invoke;
    puStack_30 = &___block_descriptor_52_e5_v8__0l;
    local_28 = param_1;
    local_18 = param_2;
    _dispatch_async(*(undefined8 *)(param_1 + 0x68),&local_48);
  }
  return;
}

// ==== 000068a0 ____ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_block_invoke ====
void ____ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_block_invoke
               (long param_1)

{
  __ZN35BufferedFilePlaybackDSPKernelMaster18fillCircularBufferEb(*(undefined8 *)(param_1 + 0x20),0)
  ;
  return;
}

// ==== 000068ac __ZN35BufferedFilePlaybackDSPKernelMaster18fillCircularBufferEb ====
/* WARNING: Removing unreachable block (ram,0x00006f98) */
/* WARNING: Removing unreachable block (ram,0x00006ac4) */
/* WARNING: Removing unreachable block (ram,0x00006988) */
/* WARNING: Removing unreachable block (ram,0x00006b04) */
/* WARNING: Type propagation algorithm not settling */

void __ZN35BufferedFilePlaybackDSPKernelMaster18fillCircularBufferEb(long param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  size_t sVar7;
  undefined4 *puVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  undefined4 *puVar12;
  bool bVar13;
  long lVar14;
  uint *puVar15;
  uint *puVar16;
  undefined8 *puVar17;
  int iVar18;
  uint uVar19;
  uint *puVar20;
  uint *puVar21;
  int iVar22;
  undefined1 auVar23 [16];
  undefined4 auStack_130 [2];
  long local_128;
  undefined1 auStack_120 [48];
  undefined4 local_f0 [2];
  ulong local_e8;
  uint local_dc [3];
  undefined8 local_d0;
  undefined4 *local_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  uint *local_88;
  uint *local_80;
  uint *local_78;
  long local_70;
  
  local_70 = *(long *)PTR____stack_chk_guard_00010040;
  if ((*(int *)(param_1 + 0x90) != 0) && (*(long *)(param_1 + 0x30) != 0)) {
    if (((*(byte *)(param_1 + 8) & 1) != 0) ||
       ((param_2 != 0 && ((*(byte *)(param_1 + 0x70) & 1) == 0)))) {
      *(undefined1 *)(param_1 + 0x70) = 1;
      piVar1 = (int *)(param_1 + 0xcc);
      uVar4 = *(int *)(param_1 + 0xc0) - *piVar1;
      if (uVar4 == 0) {
        local_128 = 0;
      }
      else {
        local_128 = *(long *)(param_1 + 0xb8) + (ulong)*(uint *)(param_1 + 200);
      }
      uVar5 = 0;
      if (*(uint *)(param_1 + 0x90) != 0) {
        uVar5 = uVar4 / *(uint *)(param_1 + 0x90);
      }
      local_88 = (uint *)0x0;
      local_80 = (uint *)0x0;
      local_78 = (uint *)0x0;
      piVar2 = (int *)(param_1 + 0x20);
      if ((int)(*piVar2 + uVar5) < *(int *)(param_1 + 0x174)) {
        auVar23 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIiEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                            (&local_78,1);
        puVar20 = auVar23._0_8_;
        puVar16 = puVar20 + -((long)local_80 - (long)local_88 >> 2);
        puVar15 = puVar20 + 1;
        *puVar20 = uVar5;
        _memcpy(puVar16,local_88,(long)local_80 - (long)local_88);
        bVar13 = local_88 != (uint *)0x0;
        local_88 = puVar16;
        local_80 = puVar15;
        local_78 = puVar20 + auVar23._8_8_;
        if (bVar13) {
          __ZdlPv();
          local_80 = puVar15;
        }
      }
      else {
        iVar18 = *piVar2;
        iVar22 = *(int *)(param_1 + 0x174);
        do {
          if ((int)uVar5 < 1) goto LAB_00006be4;
          uVar4 = iVar22 - iVar18;
          uVar19 = uVar5;
          if (((int)uVar4 <= (int)uVar5) &&
             ((iVar18 = *(int *)(param_1 + 0x178), iVar18 == -1 ||
              (iVar22 = *(int *)(param_1 + 0x17c), uVar19 = uVar4, iVar22 == -1)))) {
            if (local_80 < local_78) {
              *local_80 = uVar4;
              local_80 = local_80 + 1;
            }
            else {
              sVar7 = (long)local_80 - (long)local_88;
              lVar14 = (long)sVar7 >> 2;
              uVar10 = lVar14 + 1;
              if (uVar10 >> 0x3e != 0) {
LAB_00006f8c:
                    /* WARNING: Subroutine does not return */
                __ZNKSt3__16vectorIP29BufferedFilePlaybackDSPKernelNS_9allocatorIS2_EEE20__throw_length_errorB8ne190102Ev
                          (&local_88);
              }
              uVar11 = (long)local_78 - (long)local_88 >> 1;
              if (uVar11 <= uVar10) {
                uVar11 = uVar10;
              }
              if (0x7ffffffffffffffb < (ulong)((long)local_78 - (long)local_88)) {
                uVar11 = 0x3fffffffffffffff;
              }
              if (uVar11 == 0) {
                auVar23 = ZEXT816(0);
                lVar9 = lVar14;
              }
              else {
                auVar23 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIiEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                                    (&local_78,uVar11);
                sVar7 = (long)local_80 - (long)local_88;
                lVar9 = (long)sVar7 >> 2;
              }
              puVar20 = (uint *)(auVar23._0_8_ + lVar14 * 4);
              puVar16 = (uint *)(auVar23._0_8_ + auVar23._8_8_ * 4);
              puVar15 = puVar20 + -lVar9;
              puVar21 = puVar20 + 1;
              *puVar20 = uVar4;
              _memcpy(puVar15,local_88,sVar7);
              bVar13 = local_88 != (uint *)0x0;
              local_88 = puVar15;
              local_80 = puVar21;
              local_78 = puVar16;
              if (bVar13) {
                __ZdlPv();
                local_80 = puVar21;
              }
            }
            break;
          }
          if (local_80 < local_78) {
            puVar21 = local_80 + 1;
            *local_80 = uVar19;
          }
          else {
            sVar7 = (long)local_80 - (long)local_88;
            lVar14 = (long)sVar7 >> 2;
            uVar10 = lVar14 + 1;
            if (uVar10 >> 0x3e != 0) goto LAB_00006f8c;
            uVar11 = (long)local_78 - (long)local_88 >> 1;
            if (uVar11 <= uVar10) {
              uVar11 = uVar10;
            }
            if (0x7ffffffffffffffb < (ulong)((long)local_78 - (long)local_88)) {
              uVar11 = 0x3fffffffffffffff;
            }
            if (uVar11 == 0) {
              auVar23 = ZEXT816(0);
              lVar9 = lVar14;
            }
            else {
              auVar23 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIiEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                                  (&local_78,uVar11);
              sVar7 = (long)local_80 - (long)local_88;
              lVar9 = (long)sVar7 >> 2;
            }
            puVar20 = (uint *)(auVar23._0_8_ + lVar14 * 4);
            puVar16 = (uint *)(auVar23._0_8_ + auVar23._8_8_ * 4);
            puVar15 = puVar20 + -lVar9;
            puVar21 = puVar20 + 1;
            *puVar20 = uVar19;
            _memcpy(puVar15,local_88,sVar7);
            bVar13 = local_88 != (uint *)0x0;
            local_88 = puVar15;
            local_78 = puVar16;
            if (bVar13) {
              local_80 = puVar21;
              __ZdlPv();
            }
          }
          uVar5 = uVar5 - uVar19;
          local_80 = puVar21;
        } while ((long)iVar18 < *(long *)(param_1 + 0x60) + -1);
        *(undefined1 *)(param_1 + 10) = 1;
      }
LAB_00006be4:
      uStack_a8 = 0;
      local_b0 = 0;
      uStack_98 = 0;
      uStack_a0 = 0;
      uStack_b8 = 0;
      local_c0 = 0;
      local_d0 = (long)(*(double *)(param_1 + 0x18) * (double)*(int *)(param_1 + 0x20));
      local_dc[1] = 0;
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_
                (&local_c0,local_dc + 1);
      if (local_88 != local_80) {
        iVar22 = 0;
        iVar18 = 0;
        puVar20 = local_88;
        do {
          uVar4 = *puVar20;
          if (uVar4 == 0) {
            if (((*(int *)(param_1 + 0x20) == *(int *)(param_1 + 0x174)) &&
                (*(int *)(param_1 + 0x178) != -1)) && (*(int *)(param_1 + 0x17c) != -1)) {
              *(int *)(param_1 + 0x170) = *(int *)(param_1 + 0x178);
              *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x17c);
              *(undefined8 *)(param_1 + 0x178) = 0xffffffffffffffff;
              uVar6 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x30),
                                        (long)(*(double *)(param_1 + 0x18) *
                                              (double)*(int *)(param_1 + 0x170)));
              if ((int)uVar6 != 0) {
                if (*(long *)(param_1 + 0x138) != 0) {
                  __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                            (param_1 + 0x120,uVar6,3,*(undefined8 *)(param_1 + 0x28));
                }
                goto LAB_00006ecc;
              }
              *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x170);
            }
          }
          else {
            uVar5 = *(int *)(param_1 + 0x90) * uVar4;
            local_c8 = (undefined4 *)((long)auStack_130 - ((ulong)uVar5 + 0xf & 0x1fffffff0));
            local_dc[1] = 1;
            local_d0 = CONCAT44(uVar5,*(undefined4 *)(param_1 + 0x94));
            local_dc[0] = uVar4;
            uVar6 = _ExtAudioFileRead(*(undefined8 *)(param_1 + 0x30),local_dc,local_dc + 1);
            if ((int)uVar6 != 0) {
              if (*(long *)(param_1 + 0x138) != 0) {
                __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                          (param_1 + 0x120,uVar6,2,*(undefined8 *)(param_1 + 0x28));
              }
LAB_00006ecc:
              bVar13 = false;
              goto LAB_00006ed0;
            }
            local_e8 = (ulong)local_dc[0];
            local_f0[0] = 1;
            __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_
                      (&local_c0,local_f0);
            if ((long)*(int *)(param_1 + 0x20) < *(long *)(param_1 + 0x60)) {
              uVar5 = *(int *)(param_1 + 0x94) * uVar4;
              uVar10 = (ulong)uVar5;
              if (0 < (int)uVar5) {
                lVar14 = (long)iVar18;
                iVar18 = iVar18 + uVar5;
                puVar8 = local_c8;
                puVar12 = (undefined4 *)(local_128 + lVar14 * 4);
                do {
                  *puVar12 = *puVar8;
                  uVar10 = uVar10 - 1;
                  puVar8 = puVar8 + 1;
                  puVar12 = puVar12 + 1;
                } while (uVar10 != 0);
              }
              do {
                cVar3 = '\x01';
                bVar13 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar13) {
                  *piVar2 = *piVar2 + uVar4;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              if (((*(int *)(param_1 + 0x20) == *(int *)(param_1 + 0x174)) &&
                  (*(int *)(param_1 + 0x178) != -1)) && (*(int *)(param_1 + 0x17c) != -1)) {
                *(int *)(param_1 + 0x170) = *(int *)(param_1 + 0x178);
                *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x17c);
                *(undefined8 *)(param_1 + 0x178) = 0xffffffffffffffff;
                uVar10 = (ulong)(*(double *)(param_1 + 0x18) * (double)*(int *)(param_1 + 0x170));
                uVar6 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x30),uVar10);
                if ((int)uVar6 != 0) {
                  if (*(long *)(param_1 + 0x138) != 0) {
                    __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                              (param_1 + 0x120,uVar6,3,*(undefined8 *)(param_1 + 0x28));
                  }
                  goto LAB_00006ecc;
                }
                local_f0[0] = 0;
                local_e8 = uVar10;
                __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_
                          (&local_c0,local_f0);
                *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x170);
              }
            }
            iVar22 = uVar4 + iVar22;
          }
          puVar20 = puVar20 + 1;
        } while (puVar20 != local_80);
        if (0 < iVar22) {
          iVar22 = *(int *)(param_1 + 0x90) * iVar22;
          uVar4 = *(int *)(param_1 + 200) + iVar22;
          uVar5 = *(uint *)(param_1 + 0xc0);
          uVar19 = 0;
          if (uVar5 != 0) {
            uVar19 = uVar4 / uVar5;
          }
          *(uint *)(param_1 + 200) = uVar4 - uVar19 * uVar5;
          do {
            cVar3 = '\x01';
            bVar13 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar13) {
              *piVar1 = *piVar1 + iVar22;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          if (*(uint *)(param_1 + 0xc0) < *(uint *)(param_1 + 0xcc)) {
                    /* WARNING: Subroutine does not return */
            ___assert_rtn("TPCircularBufferProduce","TPCircularBuffer.h",0xc5,
                          "buffer->fillCount <= buffer->length");
          }
        }
      }
      for (puVar17 = *(undefined8 **)(param_1 + 0x200); puVar17 < *(undefined8 **)(param_1 + 0x208);
          puVar17 = puVar17 + 1) {
        uVar6 = *puVar17;
        __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEEC2ERKS4_(auStack_120,&local_c0);
        __ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE
                  (uVar6,auStack_120);
        __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(auStack_120);
      }
      bVar13 = true;
LAB_00006ed0:
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(&local_c0);
      if (local_88 != (uint *)0x0) {
        local_80 = local_88;
        __ZdlPv();
      }
      if (!bVar13) goto LAB_00006ef4;
    }
    *(undefined1 *)(param_1 + 0x70) = 0;
  }
LAB_00006ef4:
  if (*(long *)PTR____stack_chk_guard_00010040 != local_70) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

// ==== 00007010 __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_00010280;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00007044 __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 00007048 __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 0000705c __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_ ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_
               (long param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  lVar3 = *(long *)(param_1 + 8);
  uVar2 = 0;
  if (*(long *)(param_1 + 0x10) != lVar3) {
    uVar2 = (*(long *)(param_1 + 0x10) - lVar3) * 0x20 - 1;
  }
  lVar4 = *(long *)(param_1 + 0x28);
  uVar5 = lVar4 + *(long *)(param_1 + 0x20);
  if (uVar2 == uVar5) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEv(param_1);
    lVar3 = *(long *)(param_1 + 8);
    lVar4 = *(long *)(param_1 + 0x28);
    uVar5 = *(long *)(param_1 + 0x20) + lVar4;
  }
  puVar1 = (undefined4 *)
           (*(long *)(lVar3 + (uVar5 >> 5 & 0x7fffffffffffff8)) + (uVar5 & 0xff) * 0x10);
  *puVar1 = *param_2;
  *(undefined8 *)(puVar1 + 2) = *(undefined8 *)(param_2 + 2);
  *(long *)(param_1 + 0x28) = lVar4 + 1;
  return;
}

// ==== 000070e8 __ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE ====
void __ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE
               (long param_1,long param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  
  uVar8 = *(long *)(param_1 + 0x160) + *(long *)(param_1 + 0x168);
  plVar1 = (long *)(*(long *)(param_1 + 0x148) + (uVar8 >> 8) * 8);
  if (*(long *)(param_1 + 0x150) == *(long *)(param_1 + 0x148)) {
    lVar4 = 0;
  }
  else {
    lVar4 = *plVar1 + (uVar8 & 0xff) * 0x10;
  }
  uVar8 = *(ulong *)(param_2 + 0x20);
  lVar3 = *(long *)(param_2 + 8);
  plVar2 = (long *)(lVar3 + (uVar8 >> 8) * 8);
  if (*(long *)(param_2 + 0x10) == lVar3) {
    lVar5 = 0;
    lVar7 = 0;
    plVar6 = (long *)(lVar3 + (*(long *)(param_2 + 0x28) + uVar8 >> 8) * 8);
  }
  else {
    lVar5 = *plVar2 + (uVar8 & 0xff) * 0x10;
    uVar8 = *(long *)(param_2 + 0x28) + uVar8;
    plVar6 = (long *)(lVar3 + (uVar8 >> 8) * 8);
    lVar7 = *plVar6 + (uVar8 & 0xff) * 0x10;
  }
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE6insertINS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEELi0EEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_
            (param_1 + 0x140,plVar1,lVar4,plVar2,lVar5,plVar6,lVar7);
  local_48 = PTR___NSConcreteStackBlock_00010038;
  local_40 = 0xc0000000;
  local_38 = 
  ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke
  ;
  puStack_30 = &___block_descriptor_40_e5_v8__0l;
  local_28 = param_1;
  _dispatch_async(*(undefined8 *)(param_1 + 0x68),&local_48);
  return;
}

// ==== 000071d4 __ZNKSt3__16vectorIP29BufferedFilePlaybackDSPKernelNS_9allocatorIS2_EEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__16vectorIP29BufferedFilePlaybackDSPKernelNS_9allocatorIS2_EEE20__throw_length_errorB8ne190102Ev
               (void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 000071e8 __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_00010050,PTR___ZNSt12length_errorD1Ev_00010010);
}

// ==== 00007238 __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_00010028 + 0x10);
  return;
}

// ==== 0000725c __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIiEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m ====
void __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIiEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
               (undefined8 param_1,ulong param_2)

{
  if (param_2 >> 0x3e == 0) {
    __Znwm(param_2 << 2);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZSt28__throw_bad_array_new_lengthB8ne190102v();
}

// ==== 00007290 __ZSt28__throw_bad_array_new_lengthB8ne190102v ====
void __ZSt28__throw_bad_array_new_lengthB8ne190102v(void)

{
  undefined8 uVar1;
  
  ___cxa_allocate_exception(8);
  uVar1 = __ZNSt20bad_array_new_lengthC1Ev();
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt20bad_array_new_length_00010020,
               PTR___ZNSt20bad_array_new_lengthD1Ev_00010018);
}

// ==== 000072b8 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEv ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEv
               (long *param_1)

{
  size_t sVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  long *plVar11;
  ulong uVar12;
  undefined8 uVar13;
  long lVar14;
  long lVar15;
  undefined1 auVar16 [16];
  undefined8 local_78;
  long local_70;
  long lStack_68;
  long local_60;
  long lStack_58;
  long *local_50;
  
  if ((ulong)param_1[4] < 0x100) {
    uVar12 = param_1[2] - param_1[1];
    plVar11 = param_1 + 3;
    lVar9 = *plVar11;
    uVar6 = lVar9 - *param_1;
    if (uVar6 <= uVar12) {
      lVar7 = (long)uVar6 >> 2;
      if (lVar9 == *param_1) {
        lVar7 = 1;
      }
      local_50 = plVar11;
      auVar16 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (plVar11,lVar7);
      local_70 = auVar16._0_8_;
      lStack_68 = local_70 + uVar12;
      lStack_58 = local_70 + auVar16._8_8_ * 8;
      local_60 = lStack_68;
      local_78 = __Znwm(0x1000);
      __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE9push_backEOS2_
                (&local_70,&local_78);
      lVar7 = param_1[2];
      lVar9 = -7 - lVar7;
      while (lVar5 = param_1[1], lVar7 != lVar5) {
        lVar7 = lVar7 + -8;
        lVar9 = lVar9 + 8;
        __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE10push_frontERKS2_
                  (&local_70,lVar7);
      }
      lVar2 = *param_1;
      lVar15 = param_1[3];
      lVar14 = param_1[2];
      param_1[1] = lStack_68;
      *param_1 = local_70;
      param_1[3] = lStack_58;
      param_1[2] = local_60;
      local_60 = lVar14;
      if (lVar7 != lVar14) {
        local_60 = lVar14 + (-(lVar14 + lVar9) & 0xfffffffffffffff8U);
      }
      if (lVar2 == 0) {
        return;
      }
      local_70 = lVar2;
      lStack_68 = lVar5;
      lStack_58 = lVar15;
      __ZdlPv();
      return;
    }
    if (lVar9 != param_1[2]) {
      local_70 = __Znwm(0x1000);
      __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE9push_backEOS2_
                (param_1,&local_70);
      return;
    }
    local_70 = __Znwm(0x1000);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
              (param_1,&local_70);
    puVar8 = (undefined8 *)param_1[2];
    puVar3 = (undefined8 *)param_1[1] + 1;
    uVar13 = *(undefined8 *)param_1[1];
    param_1[1] = (long)puVar3;
    if (puVar8 != (undefined8 *)param_1[3]) goto LAB_000074dc;
    puVar4 = (undefined8 *)*param_1;
    lVar9 = (long)puVar3 - (long)puVar4;
    if (puVar3 < puVar4 || lVar9 == 0) {
      uVar6 = (long)puVar8 - (long)puVar4 >> 2;
      if ((long)puVar8 - (long)puVar4 == 0) {
        uVar6 = 1;
      }
      auVar16 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (plVar11,uVar6);
      lVar5 = auVar16._0_8_;
      puVar3 = (undefined8 *)(lVar5 + (uVar6 >> 2) * 8);
      lVar9 = lVar5 + auVar16._8_8_ * 8;
      lVar7 = param_1[2] - param_1[1];
      puVar8 = puVar3;
      if (lVar7 != 0) {
        puVar8 = (undefined8 *)((long)puVar3 + lVar7);
        puVar4 = (undefined8 *)param_1[1];
        puVar10 = puVar3;
        do {
          *puVar10 = *puVar4;
          lVar7 = lVar7 + -8;
          puVar4 = puVar4 + 1;
          puVar10 = puVar10 + 1;
        } while (lVar7 != 0);
      }
      goto LAB_00007490;
    }
  }
  else {
    param_1[4] = param_1[4] - 0x100;
    puVar8 = (undefined8 *)param_1[2];
    puVar3 = (undefined8 *)param_1[1] + 1;
    uVar13 = *(undefined8 *)param_1[1];
    param_1[1] = (long)puVar3;
    if (puVar8 != (undefined8 *)param_1[3]) goto LAB_000074dc;
    puVar4 = (undefined8 *)*param_1;
    lVar9 = (long)puVar3 - (long)puVar4;
    if (puVar3 < puVar4 || lVar9 == 0) {
      uVar6 = (long)puVar8 - (long)puVar4 >> 2;
      if ((long)puVar8 - (long)puVar4 == 0) {
        uVar6 = 1;
      }
      auVar16 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (param_1 + 3,uVar6);
      lVar5 = auVar16._0_8_;
      puVar3 = (undefined8 *)(lVar5 + (uVar6 >> 2) * 8);
      lVar9 = lVar5 + auVar16._8_8_ * 8;
      lVar7 = param_1[2] - param_1[1];
      puVar8 = puVar3;
      if (lVar7 != 0) {
        puVar8 = (undefined8 *)((long)puVar3 + lVar7);
        puVar4 = (undefined8 *)param_1[1];
        puVar10 = puVar3;
        do {
          *puVar10 = *puVar4;
          lVar7 = lVar7 + -8;
          puVar4 = puVar4 + 1;
          puVar10 = puVar10 + 1;
        } while (lVar7 != 0);
      }
LAB_00007490:
      lVar7 = *param_1;
      *param_1 = lVar5;
      param_1[1] = (long)puVar3;
      param_1[2] = (long)puVar8;
      param_1[3] = lVar9;
      if (lVar7 != 0) {
        __ZdlPv(lVar7);
        puVar8 = (undefined8 *)param_1[2];
      }
      goto LAB_000074dc;
    }
  }
  lVar9 = ((lVar9 >> 3) + 1) / 2;
  puVar4 = puVar3 + -lVar9;
  sVar1 = (long)puVar8 - (long)puVar3;
  if (sVar1 != 0) {
    _memmove(puVar4,puVar3,sVar1);
    puVar3 = (undefined8 *)param_1[1];
  }
  puVar8 = (undefined8 *)((long)puVar4 + sVar1);
  param_1[1] = (long)(puVar3 + -lVar9);
  param_1[2] = (long)puVar8;
LAB_000074dc:
  *puVar8 = uVar13;
  param_1[2] = param_1[2] + 8;
  return;
}

// ==== 000075ac __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE9push_backEOS2_ ====
void __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE9push_backEOS2_
               (ulong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  size_t sVar2;
  ulong uVar3;
  void *pvVar4;
  ulong uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined8 *puVar9;
  void *pvVar10;
  undefined1 auVar11 [16];
  
  puVar7 = (undefined8 *)param_1[2];
  if (puVar7 == (undefined8 *)param_1[3]) {
    pvVar10 = (void *)*param_1;
    pvVar4 = (void *)param_1[1];
    if (pvVar4 < pvVar10 || (long)pvVar4 - (long)pvVar10 == 0) {
      uVar5 = (long)puVar7 - (long)pvVar10 >> 2;
      if ((long)puVar7 - (long)pvVar10 == 0) {
        uVar5 = 1;
      }
      auVar11 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (param_1 + 3,uVar5);
      uVar3 = auVar11._0_8_;
      puVar1 = (undefined8 *)(uVar3 + (uVar5 >> 2) * 8);
      lVar8 = param_1[2] - (long)param_1[1];
      puVar7 = puVar1;
      if (lVar8 != 0) {
        puVar7 = (undefined8 *)((long)puVar1 + lVar8);
        puVar6 = (undefined8 *)param_1[1];
        puVar9 = puVar1;
        do {
          *puVar9 = *puVar6;
          lVar8 = lVar8 + -8;
          puVar6 = puVar6 + 1;
          puVar9 = puVar9 + 1;
        } while (lVar8 != 0);
      }
      uVar5 = *param_1;
      *param_1 = uVar3;
      param_1[1] = (ulong)puVar1;
      param_1[2] = (ulong)puVar7;
      param_1[3] = uVar3 + auVar11._8_8_ * 8;
      if (uVar5 != 0) {
        __ZdlPv(uVar5);
        puVar7 = (undefined8 *)param_1[2];
      }
    }
    else {
      lVar8 = (((long)pvVar4 - (long)pvVar10 >> 3) + 1) / 2;
      pvVar10 = (void *)((long)pvVar4 + lVar8 * -8);
      sVar2 = (long)puVar7 - (long)pvVar4;
      if (sVar2 != 0) {
        _memmove(pvVar10,pvVar4,sVar2);
        pvVar4 = (void *)param_1[1];
      }
      puVar7 = (undefined8 *)((long)pvVar10 + sVar2);
      param_1[1] = (ulong)((long)pvVar4 + lVar8 * -8);
      param_1[2] = (ulong)puVar7;
    }
  }
  *puVar7 = *param_2;
  param_1[2] = param_1[2] + 8;
  return;
}

// ==== 000076b0 __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_ ====
void __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
               (long *param_1,undefined8 *param_2)

{
  long lVar1;
  ulong uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined1 auVar9 [16];
  
  puVar7 = (undefined8 *)param_1[1];
  if (puVar7 == (undefined8 *)*param_1) {
    uVar4 = param_1[3];
    uVar2 = param_1[2];
    if (uVar2 < uVar4) {
      lVar8 = (((long)(uVar4 - uVar2) >> 3) + 1) / 2;
      puVar5 = puVar7 + lVar8;
      if (uVar2 - (long)puVar7 != 0) {
        _memmove(puVar5,puVar7,uVar2 - (long)puVar7);
        uVar2 = param_1[2];
      }
      param_1[1] = (long)puVar5;
      param_1[2] = uVar2 + lVar8 * 8;
      puVar7 = puVar5;
    }
    else {
      lVar8 = (long)(uVar4 - (long)puVar7) >> 2;
      if (uVar4 - (long)puVar7 == 0) {
        lVar8 = 1;
      }
      auVar9 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                         ();
      lVar1 = auVar9._0_8_;
      puVar7 = (undefined8 *)(lVar1 + (lVar8 * 2 + 6U & 0xfffffffffffffff8));
      lVar8 = param_1[2] - param_1[1];
      puVar5 = puVar7;
      if (lVar8 != 0) {
        puVar5 = (undefined8 *)((long)puVar7 + lVar8);
        puVar3 = (undefined8 *)param_1[1];
        puVar6 = puVar7;
        do {
          *puVar6 = *puVar3;
          lVar8 = lVar8 + -8;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        } while (lVar8 != 0);
      }
      lVar8 = *param_1;
      *param_1 = lVar1;
      param_1[1] = (long)puVar7;
      param_1[2] = (long)puVar5;
      param_1[3] = lVar1 + auVar9._8_8_ * 8;
      if (lVar8 != 0) {
        __ZdlPv(lVar8);
        puVar7 = (undefined8 *)param_1[1];
      }
    }
  }
  puVar7[-1] = *param_2;
  param_1[1] = param_1[1] + -8;
  return;
}

// ==== 000077bc __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE9push_backEOS2_ ====
void __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE9push_backEOS2_
               (ulong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  size_t sVar2;
  ulong uVar3;
  void *pvVar4;
  ulong uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined8 *puVar9;
  void *pvVar10;
  undefined1 auVar11 [16];
  
  puVar7 = (undefined8 *)param_1[2];
  if (puVar7 == (undefined8 *)param_1[3]) {
    pvVar10 = (void *)*param_1;
    pvVar4 = (void *)param_1[1];
    if (pvVar4 < pvVar10 || (long)pvVar4 - (long)pvVar10 == 0) {
      uVar5 = (long)puVar7 - (long)pvVar10 >> 2;
      if ((long)puVar7 - (long)pvVar10 == 0) {
        uVar5 = 1;
      }
      auVar11 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (param_1[4],uVar5);
      uVar3 = auVar11._0_8_;
      puVar1 = (undefined8 *)(uVar3 + (uVar5 >> 2) * 8);
      lVar8 = param_1[2] - (long)param_1[1];
      puVar7 = puVar1;
      if (lVar8 != 0) {
        puVar7 = (undefined8 *)((long)puVar1 + lVar8);
        puVar6 = (undefined8 *)param_1[1];
        puVar9 = puVar1;
        do {
          *puVar9 = *puVar6;
          lVar8 = lVar8 + -8;
          puVar6 = puVar6 + 1;
          puVar9 = puVar9 + 1;
        } while (lVar8 != 0);
      }
      uVar5 = *param_1;
      *param_1 = uVar3;
      param_1[1] = (ulong)puVar1;
      param_1[2] = (ulong)puVar7;
      param_1[3] = uVar3 + auVar11._8_8_ * 8;
      if (uVar5 != 0) {
        __ZdlPv(uVar5);
        puVar7 = (undefined8 *)param_1[2];
      }
    }
    else {
      lVar8 = (((long)pvVar4 - (long)pvVar10 >> 3) + 1) / 2;
      pvVar10 = (void *)((long)pvVar4 + lVar8 * -8);
      sVar2 = (long)puVar7 - (long)pvVar4;
      if (sVar2 != 0) {
        _memmove(pvVar10,pvVar4,sVar2);
        pvVar4 = (void *)param_1[1];
      }
      puVar7 = (undefined8 *)((long)pvVar10 + sVar2);
      param_1[1] = (ulong)((long)pvVar4 + lVar8 * -8);
      param_1[2] = (ulong)puVar7;
    }
  }
  *puVar7 = *param_2;
  param_1[2] = param_1[2] + 8;
  return;
}

// ==== 000078c0 __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE10push_frontERKS2_ ====
void __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE10push_frontERKS2_
               (long *param_1,undefined8 *param_2)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined1 auVar9 [16];
  
  puVar7 = (undefined8 *)param_1[1];
  if (puVar7 == (undefined8 *)*param_1) {
    uVar3 = param_1[2];
    uVar1 = param_1[3];
    if (uVar3 < uVar1) {
      lVar8 = (((long)(uVar1 - uVar3) >> 3) + 1) / 2;
      puVar5 = puVar7 + lVar8;
      if (uVar3 - (long)puVar7 != 0) {
        _memmove(puVar5,puVar7,uVar3 - (long)puVar7);
        uVar3 = param_1[2];
      }
      param_1[1] = (long)puVar5;
      param_1[2] = uVar3 + lVar8 * 8;
      puVar7 = puVar5;
    }
    else {
      lVar8 = (long)(uVar1 - (long)puVar7) >> 2;
      if (uVar1 - (long)puVar7 == 0) {
        lVar8 = 1;
      }
      auVar9 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                         (param_1[4]);
      lVar2 = auVar9._0_8_;
      puVar7 = (undefined8 *)(lVar2 + (lVar8 * 2 + 6U & 0xfffffffffffffff8));
      lVar8 = param_1[2] - param_1[1];
      puVar5 = puVar7;
      if (lVar8 != 0) {
        puVar5 = (undefined8 *)((long)puVar7 + lVar8);
        puVar4 = (undefined8 *)param_1[1];
        puVar6 = puVar7;
        do {
          *puVar6 = *puVar4;
          lVar8 = lVar8 + -8;
          puVar4 = puVar4 + 1;
          puVar6 = puVar6 + 1;
        } while (lVar8 != 0);
      }
      lVar8 = *param_1;
      *param_1 = lVar2;
      param_1[1] = (long)puVar7;
      param_1[2] = (long)puVar5;
      param_1[3] = lVar2 + auVar9._8_8_ * 8;
      if (lVar8 != 0) {
        __ZdlPv(lVar8);
        puVar7 = (undefined8 *)param_1[1];
      }
    }
  }
  puVar7[-1] = *param_2;
  param_1[1] = param_1[1] + -8;
  return;
}

// ==== 000079c8 __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m ====
void __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
               (undefined8 param_1,ulong param_2)

{
  if (param_2 >> 0x3d == 0) {
    __Znwm(param_2 << 3);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZSt28__throw_bad_array_new_lengthB8ne190102v();
}

// ==== 000079fc __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_ ====
void __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
               (long param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,long param_5,
               undefined8 param_6,long param_7)

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
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
  if (param_7 == param_5) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m
              ();
    return;
  }
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m
            ();
  return;
}

// ==== 00007a44 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE6insertINS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEELi0EEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_ ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE6insertINS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEELi0EEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_
               (void)

{
  long in_x4;
  long in_x6;
  
  if (in_x6 == in_x4) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m
              ();
    return;
  }
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m
            ();
  return;
}

// ==== 00007a78 ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke ====
void ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke
               (long param_1)

{
  int *piVar1;
  uint *puVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char cVar7;
  bool bVar8;
  uint uVar9;
  uint uVar10;
  undefined8 uVar11;
  ulong uVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  long lVar15;
  ulong uVar16;
  undefined4 *puVar17;
  long lVar18;
  uint uVar19;
  int iVar20;
  byte bVar21;
  byte bVar22;
  byte bVar23;
  byte bVar24;
  byte bVar25;
  byte bVar26;
  byte bVar27;
  byte bVar28;
  long local_c0;
  long lStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined4 local_88 [2];
  undefined4 local_80;
  uint uStack_7c;
  undefined4 *local_78;
  uint local_6c;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_00010040;
  lVar18 = *(long *)(param_1 + 0x20);
  if (*(long *)(lVar18 + 0x168) != 0) {
    puVar2 = (uint *)(lVar18 + 0x20);
    piVar3 = (int *)(lVar18 + 0xcc);
    uStack_98 = 3;
    local_a0 = 2;
    uStack_a8 = 1;
    local_b0 = 0;
    lStack_b8 = -1;
    local_c0 = 1;
    do {
      piVar1 = (int *)(*(long *)(*(long *)(lVar18 + 0x148) +
                                (*(ulong *)(lVar18 + 0x160) >> 5 & 0x7fffffffffffff8)) +
                      (*(ulong *)(lVar18 + 0x160) & 0xff) * 0x10);
      if (*piVar1 == 1) {
        uVar4 = piVar1[2];
        if ((long)(ulong)(uVar4 + *(int *)(lVar18 + 0x20)) < *(long *)(lVar18 + 0x60)) {
          iVar20 = 0;
          local_6c = uVar4;
        }
        else {
          local_6c = ~*puVar2 + (int)*(long *)(lVar18 + 0x60);
          iVar20 = uVar4 - local_6c;
        }
        uStack_7c = *(int *)(lVar18 + 0x90) * uVar4;
        local_78 = (undefined4 *)((long)&local_c0 - ((ulong)uStack_7c + 0xf & 0x1fffffff0));
        local_80 = *(undefined4 *)(lVar18 + 0x94);
        local_88[0] = 1;
        uVar11 = _ExtAudioFileRead(*(undefined8 *)(lVar18 + 0x30),&local_6c,local_88);
        if ((int)uVar11 != 0) {
          if (*(long *)(lVar18 + 0x138) != 0) {
            __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                      (lVar18 + 0x120,uVar11,2,*(undefined8 *)(lVar18 + 0x28));
          }
          break;
        }
        uVar9 = *(int *)(lVar18 + 0xc0) - *(int *)(lVar18 + 0xcc);
        if (uVar9 == 0) {
          puVar13 = (undefined4 *)0x0;
        }
        else {
          puVar13 = (undefined4 *)(*(long *)(lVar18 + 0xb8) + (ulong)*(uint *)(lVar18 + 200));
        }
        uVar5 = *(uint *)(lVar18 + 0x90);
        uVar19 = 0;
        if (uVar5 != 0) {
          uVar19 = uVar9 / uVar5;
        }
        if (uVar19 < uVar4) {
          iVar20 = *(int *)(lVar18 + 0x94);
          if (local_6c < uVar19) {
            uVar4 = iVar20 * local_6c;
            uVar12 = (ulong)uVar4;
            puVar14 = local_78;
            puVar17 = puVar13;
            if (0 < (int)uVar4) {
              do {
                *puVar17 = *puVar14;
                uVar12 = uVar12 - 1;
                puVar14 = puVar14 + 1;
                puVar17 = puVar17 + 1;
              } while (uVar12 != 0);
            }
            if ((int)uVar4 < (int)(iVar20 * uVar19)) {
              uVar12 = 0;
              lVar15 = (long)(int)(iVar20 * uVar19) - (long)(int)uVar4;
              uVar16 = lVar15 - 1;
              puVar13 = puVar13 + (long)(int)uVar4 + 2;
              do {
                bVar21 = (byte)uVar12;
                bVar22 = (byte)(uVar12 >> 8);
                bVar23 = (byte)(uVar12 >> 0x10);
                bVar24 = (byte)(uVar12 >> 0x18);
                bVar25 = (byte)(uVar12 >> 0x20);
                bVar26 = (byte)(uVar12 >> 0x28);
                bVar27 = (byte)(uVar12 >> 0x30);
                bVar28 = (byte)(uVar12 >> 0x38);
                if (CONCAT17(bVar28 | (byte)((ulong)local_b0 >> 0x38),
                             CONCAT16(bVar27 | (byte)((ulong)local_b0 >> 0x30),
                                      CONCAT15(bVar26 | (byte)((ulong)local_b0 >> 0x28),
                                               CONCAT14(bVar25 | (byte)((ulong)local_b0 >> 0x20),
                                                        CONCAT13(bVar24 | (byte)((ulong)local_b0 >>
                                                                                0x18),
                                                                 CONCAT12(bVar23 | (byte)((ulong)
                                                  local_b0 >> 0x10),
                                                  CONCAT11(bVar22 | (byte)((ulong)local_b0 >> 8),
                                                           bVar21 | (byte)local_b0))))))) <= uVar16)
                {
                  puVar13[-2] = 0;
                }
                if (CONCAT17(bVar28 | (byte)((ulong)uStack_a8 >> 0x38),
                             CONCAT16(bVar27 | (byte)((ulong)uStack_a8 >> 0x30),
                                      CONCAT15(bVar26 | (byte)((ulong)uStack_a8 >> 0x28),
                                               CONCAT14(bVar25 | (byte)((ulong)uStack_a8 >> 0x20),
                                                        CONCAT13(bVar24 | (byte)((ulong)uStack_a8 >>
                                                                                0x18),
                                                                 CONCAT12(bVar23 | (byte)((ulong)
                                                  uStack_a8 >> 0x10),
                                                  CONCAT11(bVar22 | (byte)((ulong)uStack_a8 >> 8),
                                                           bVar21 | (byte)uStack_a8))))))) <= uVar16
                   ) {
                  puVar13[-1] = 0;
                }
                if (CONCAT17(bVar28 | (byte)((ulong)local_a0 >> 0x38),
                             CONCAT16(bVar27 | (byte)((ulong)local_a0 >> 0x30),
                                      CONCAT15(bVar26 | (byte)((ulong)local_a0 >> 0x28),
                                               CONCAT14(bVar25 | (byte)((ulong)local_a0 >> 0x20),
                                                        CONCAT13(bVar24 | (byte)((ulong)local_a0 >>
                                                                                0x18),
                                                                 CONCAT12(bVar23 | (byte)((ulong)
                                                  local_a0 >> 0x10),
                                                  CONCAT11(bVar22 | (byte)((ulong)local_a0 >> 8),
                                                           bVar21 | (byte)local_a0))))))) <= uVar16)
                {
                  *puVar13 = 0;
                }
                if (CONCAT17(bVar28 | (byte)((ulong)uStack_98 >> 0x38),
                             CONCAT16(bVar27 | (byte)((ulong)uStack_98 >> 0x30),
                                      CONCAT15(bVar26 | (byte)((ulong)uStack_98 >> 0x28),
                                               CONCAT14(bVar25 | (byte)((ulong)uStack_98 >> 0x20),
                                                        CONCAT13(bVar24 | (byte)((ulong)uStack_98 >>
                                                                                0x18),
                                                                 CONCAT12(bVar23 | (byte)((ulong)
                                                  uStack_98 >> 0x10),
                                                  CONCAT11(bVar22 | (byte)((ulong)uStack_98 >> 8),
                                                           bVar21 | (byte)uStack_98))))))) <= uVar16
                   ) {
                  puVar13[1] = 0;
                }
                uVar12 = uVar12 + 4;
                puVar13 = puVar13 + 4;
              } while ((lVar15 + 3U & 0xfffffffffffffffc) != uVar12);
            }
          }
          else if (0 < (int)(iVar20 * uVar19)) {
            uVar12 = 0;
            do {
              puVar13[uVar12] = local_78[uVar12];
              uVar12 = uVar12 + 1;
            } while (uVar12 < iVar20 * uVar19);
          }
        }
        else {
          iVar6 = *(int *)(lVar18 + 0x94);
          uVar9 = iVar6 * local_6c;
          uVar12 = (ulong)uVar9;
          puVar14 = local_78;
          puVar17 = puVar13;
          if (0 < (int)uVar9) {
            do {
              *puVar17 = *puVar14;
              uVar12 = uVar12 - 1;
              puVar14 = puVar14 + 1;
              puVar17 = puVar17 + 1;
            } while (uVar12 != 0);
          }
          uVar19 = local_6c;
          if ((local_6c < uVar4) && (uVar19 = local_6c + iVar20, (int)uVar9 < (int)(uVar19 * iVar6))
             ) {
            _bzero(puVar13 + (int)uVar9,(ulong)(iVar20 * iVar6 - 1) * 4 + 4);
          }
        }
        if (0 < (int)uVar19) {
          uVar4 = *(int *)(lVar18 + 200) + uVar19 * uVar5;
          uVar9 = *(uint *)(lVar18 + 0xc0);
          uVar10 = 0;
          if (uVar9 != 0) {
            uVar10 = uVar4 / uVar9;
          }
          *(uint *)(lVar18 + 200) = uVar4 - uVar10 * uVar9;
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar8) {
              *piVar3 = *piVar3 + uVar19 * uVar5;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          if (*(uint *)(lVar18 + 0xc0) < *(uint *)(lVar18 + 0xcc)) {
            ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke_cold_1
                      ();
            goto LAB_00007e6c;
          }
        }
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(puVar2,0x10);
          if (bVar8) {
            *puVar2 = *puVar2 + uVar19;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
      }
      else if (*piVar1 == 0) {
        uVar12 = *(ulong *)(piVar1 + 2) &
                 ((long)*(ulong *)(piVar1 + 2) >> 0x3f ^ 0xffffffffffffffffU);
        if (*(long *)(lVar18 + 0x60) <= (long)uVar12) {
          uVar12 = *(long *)(lVar18 + 0x60) - 1;
        }
        if (uVar12 != (long)*(int *)(lVar18 + 0x20)) {
          uVar11 = _ExtAudioFileSeek(*(undefined8 *)(lVar18 + 0x30),uVar12);
          if ((int)uVar11 != 0) {
            if (*(long *)(lVar18 + 0x138) != 0) {
              __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                        (lVar18 + 0x120,uVar11,3,*(undefined8 *)(lVar18 + 0x28));
            }
            break;
          }
          *puVar2 = (uint)uVar12;
        }
      }
      *(long *)(lVar18 + 0x168) = *(long *)(lVar18 + 0x168) + lStack_b8;
      *(long *)(lVar18 + 0x160) = *(long *)(lVar18 + 0x160) + local_c0;
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE26__maybe_remove_front_spareB8ne190102Eb
                (lVar18 + 0x140,1);
    } while (*(long *)(lVar18 + 0x168) != 0);
  }
  if (*(long *)PTR____stack_chk_guard_00010040 == local_68) {
    return;
  }
LAB_00007e6c:
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00007e70 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE22__insert_bidirectionalB8ne190102INS_16__deque_iteratorIS1_PS1_RS1_PS7_lLl256EEEEESA_NS6_IS1_PKS1_RSB_PKSC_lLl256EEET_SH_m
               (long param_1,long *param_2,long param_3,long *param_4,undefined4 *param_5,
               long *param_6,undefined4 *param_7,ulong param_8)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined4 *puVar6;
  long lVar7;
  undefined4 *puVar8;
  long lVar9;
  undefined8 uVar10;
  long *plVar11;
  undefined4 *puVar12;
  ulong uVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  ulong uVar16;
  undefined4 *puVar17;
  long *plVar18;
  long lVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  long *local_a0;
  undefined4 *puStack_98;
  undefined1 uStack_81;
  long *local_80;
  undefined4 *puStack_78;
  long *local_70;
  undefined4 *puStack_68;
  
  uVar5 = *(ulong *)(param_1 + 0x20);
  uVar13 = uVar5 >> 8;
  lVar9 = *(long *)(param_1 + 8);
  lVar19 = *(long *)(param_1 + 0x10);
  plVar18 = (long *)(lVar9 + uVar13 * 8);
  if (lVar19 - lVar9 == 0) {
    lVar7 = 0;
  }
  else {
    lVar7 = *plVar18 + (uVar5 & 0xff) * 0x10;
  }
  if (param_3 == lVar7) {
    uVar16 = 0;
  }
  else {
    uVar16 = ((param_3 - *param_2 >> 4) + ((long)param_2 - (long)plVar18) * 0x20) -
             (lVar7 - *plVar18 >> 4);
  }
  lVar7 = *(long *)(param_1 + 0x28);
  if (lVar7 - uVar16 <= uVar16) {
    lVar1 = 0;
    if (lVar19 != lVar9) {
      lVar1 = (lVar19 - lVar9) * 0x20 + -1;
    }
    uVar5 = uVar5 + lVar7;
    lVar2 = param_8 - (lVar1 - uVar5);
    if (lVar1 - uVar5 <= param_8 && lVar2 != 0) {
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEm
                (param_1,lVar2);
      lVar7 = *(long *)(param_1 + 0x28);
      lVar9 = *(long *)(param_1 + 8);
      lVar19 = *(long *)(param_1 + 0x10);
      uVar5 = *(long *)(param_1 + 0x20) + lVar7;
    }
    local_a0 = (long *)(lVar9 + (uVar5 >> 8) * 8);
    if (lVar19 == lVar9) {
      puStack_98 = (undefined4 *)0x0;
    }
    else {
      puStack_98 = (undefined4 *)(*local_a0 + (uVar5 & 0xff) * 0x10);
    }
    uVar5 = lVar7 - uVar16;
    puVar6 = param_7;
    plVar18 = local_a0;
    puVar17 = puStack_98;
    if (uVar5 < param_8) {
      if (uVar5 < param_8 >> 1) {
        puVar6 = param_5;
        param_6 = param_4;
        if (uVar5 != 0) {
          uVar13 = uVar5 + ((long)param_5 - *param_4 >> 4);
          if ((long)uVar13 < 1) {
            bVar3 = (byte)(0xff - uVar13);
            param_6 = param_4 + -(0xff - uVar13 >> 8);
            goto LAB_00008244;
          }
          param_6 = param_4 + (uVar13 >> 8);
LAB_00008060:
          puVar6 = (undefined4 *)(*param_6 + (uVar13 & 0xff) * 0x10);
        }
      }
      else {
        uVar13 = (uVar5 - param_8) + ((long)param_7 - *param_6 >> 4);
        if (0 < (long)uVar13) {
          param_6 = param_6 + (uVar13 >> 8);
          goto LAB_00008060;
        }
        bVar3 = (byte)(0xff - uVar13);
        param_6 = param_6 + -(0xff - uVar13 >> 8);
LAB_00008244:
        puVar6 = (undefined4 *)(*param_6 + (ulong)(byte)~bVar3 * 0x10);
      }
      param_8 = uVar5;
      if (puVar6 != param_7) {
        puVar8 = (undefined4 *)*local_a0;
        plVar11 = param_6;
        puVar14 = puVar6;
        do {
          *puVar17 = *puVar14;
          *(undefined8 *)(puVar17 + 2) = *(undefined8 *)(puVar14 + 2);
          puVar17 = puVar17 + 4;
          if ((long)puVar17 - (long)puVar8 == 0x1000) {
            plVar18 = plVar18 + 1;
            puVar8 = (undefined4 *)*plVar18;
            puVar17 = puVar8;
          }
          puVar14 = puVar14 + 4;
          if ((long)puVar14 - *plVar11 == 0x1000) {
            plVar11 = plVar11 + 1;
            puVar14 = (undefined4 *)*plVar11;
          }
          lVar7 = lVar7 + 1;
        } while (puVar14 != param_7);
        *(long *)(param_1 + 0x28) = lVar7;
      }
    }
    if (param_8 != 0) {
      auVar21 = __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEmiB8ne190102El
                          (&local_a0,param_8);
      puVar14 = auVar21._8_8_;
      uVar4 = auVar21._0_8_;
      if (puStack_98 != puVar14) {
        lVar9 = *(long *)(param_1 + 0x28);
        puVar8 = (undefined4 *)*plVar18;
        do {
          puVar12 = auVar21._8_8_;
          plVar11 = auVar21._0_8_;
          *puVar17 = *puVar12;
          *(undefined8 *)(puVar17 + 2) = *(undefined8 *)(puVar12 + 2);
          puVar17 = puVar17 + 4;
          if ((long)puVar17 - (long)puVar8 == 0x1000) {
            plVar18 = plVar18 + 1;
            puVar8 = (undefined4 *)*plVar18;
            puVar17 = puVar8;
          }
          puVar12 = puVar12 + 4;
          if ((long)puVar12 - *plVar11 == 0x1000) {
            plVar11 = plVar11 + 1;
            puVar12 = (undefined4 *)*plVar11;
          }
          auVar21._8_8_ = puVar12;
          auVar21._0_8_ = plVar11;
          lVar9 = lVar9 + 1;
        } while (puVar12 != puStack_98);
        *(long *)(param_1 + 0x28) = lVar9;
      }
      if (param_8 < uVar5) {
        auVar21 = __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEmiB8ne190102El
                            (&local_a0,uVar5);
        __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS5_RS5_PS6_lLl256EEES9_Li0EEENS_4pairIT_T0_EESB_SB_SC_
                  (&local_80,&uStack_81,auVar21._0_8_,auVar21._8_8_,uVar4,puVar14,local_a0,
                   puStack_98);
        local_a0 = local_70;
        puStack_98 = puStack_68;
      }
      __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS5_RS5_PS6_lLl256EEES9_Li0EEENS_4pairIT_T0_EESB_SB_SC_
                (&local_80,&uStack_81,param_4,param_5,param_6,puVar6,local_a0);
    }
    goto LAB_000083a4;
  }
  if (uVar5 <= param_8 && param_8 - uVar5 != 0) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE20__add_front_capacityEm
              (param_1,param_8 - uVar5);
    uVar5 = *(ulong *)(param_1 + 0x20);
    lVar9 = *(long *)(param_1 + 8);
    lVar19 = *(long *)(param_1 + 0x10);
    uVar13 = uVar5 >> 8;
  }
  local_a0 = (long *)(lVar9 + uVar13 * 8);
  if (lVar19 == lVar9) {
    puStack_98 = (undefined4 *)0x0;
  }
  else {
    puStack_98 = (undefined4 *)(*local_a0 + (uVar5 & 0xff) * 0x10);
  }
  puVar6 = param_5;
  puVar17 = puStack_98;
  plVar18 = local_a0;
  if (uVar16 <= param_8 && param_8 - uVar16 != 0) {
    if (uVar16 < param_8 >> 1) {
      puVar6 = param_7;
      param_4 = param_6;
      if (uVar16 != 0) {
        uVar13 = ((long)param_7 - *param_6 >> 4) - uVar16;
        if ((long)uVar13 < 1) {
          bVar3 = (byte)(0xff - uVar13);
          param_4 = param_6 + -(0xff - uVar13 >> 8);
          goto LAB_000080c8;
        }
        param_4 = param_6 + (uVar13 >> 8);
LAB_00008038:
        puVar6 = (undefined4 *)(*param_4 + (uVar13 & 0xff) * 0x10);
      }
    }
    else {
      uVar13 = (param_8 - uVar16) + ((long)param_5 - *param_4 >> 4);
      if (0 < (long)uVar13) {
        param_4 = param_4 + (uVar13 >> 8);
        goto LAB_00008038;
      }
      bVar3 = (byte)(0xff - uVar13);
      param_4 = param_4 + -(0xff - uVar13 >> 8);
LAB_000080c8:
      puVar6 = (undefined4 *)(*param_4 + (ulong)(byte)~bVar3 * 0x10);
    }
    param_8 = uVar16;
    if (puVar6 != param_5) {
      lVar9 = *(long *)(param_1 + 0x28);
      puVar12 = (undefined4 *)*local_a0;
      plVar11 = param_4;
      puVar8 = puVar6;
      puVar14 = puStack_98;
      do {
        if (puVar14 == puVar12) {
          plVar18 = plVar18 + -1;
          puVar12 = (undefined4 *)*plVar18;
          puVar14 = puVar12 + 0x400;
        }
        puVar15 = puVar8;
        if (puVar8 == (undefined4 *)*plVar11) {
          plVar11 = plVar11 + -1;
          puVar15 = (undefined4 *)(*plVar11 + 0x1000);
        }
        puVar17 = puVar14 + -4;
        puVar8 = puVar15 + -4;
        puVar14[-4] = *puVar8;
        *(undefined8 *)(puVar14 + -2) = *(undefined8 *)(puVar15 + -2);
        uVar5 = uVar5 - 1;
        lVar9 = lVar9 + 1;
        puVar14 = puVar17;
      } while (puVar8 != param_5);
      *(ulong *)(param_1 + 0x20) = uVar5;
      *(long *)(param_1 + 0x28) = lVar9;
    }
  }
  if (param_8 != 0) {
    auVar20 = __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El
                        (&local_a0,param_8);
    puVar14 = auVar20._8_8_;
    uVar4 = auVar20._0_8_;
    if (puStack_98 != puVar14) {
      lVar19 = *(long *)(param_1 + 0x28);
      lVar9 = *(long *)(param_1 + 0x20);
      puVar8 = (undefined4 *)*plVar18;
      do {
        if (puVar17 == puVar8) {
          plVar18 = plVar18 + -1;
          puVar8 = (undefined4 *)*plVar18;
          puVar17 = puVar8 + 0x400;
        }
        if (auVar20._8_8_ == *auVar20._0_8_) {
          plVar11 = auVar20._0_8_ + -1;
          auVar20._8_8_ = *plVar11 + 0x1000;
          auVar20._0_8_ = plVar11;
        }
        lVar7 = auVar20._8_8_;
        uVar10 = auVar20._0_8_;
        puVar12 = (undefined4 *)(lVar7 + -0x10);
        auVar20._8_8_ = puVar12;
        auVar20._0_8_ = uVar10;
        puVar17[-4] = *puVar12;
        *(undefined8 *)(puVar17 + -2) = *(undefined8 *)(lVar7 + -8);
        puVar17 = puVar17 + -4;
        lVar9 = lVar9 + -1;
        lVar19 = lVar19 + 1;
      } while (puVar12 != puStack_98);
      *(long *)(param_1 + 0x28) = lVar19;
      *(long *)(param_1 + 0x20) = lVar9;
    }
    if (param_8 < uVar16) {
      auVar21 = __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El
                          (&local_a0,uVar16);
      puStack_78 = puStack_98;
      local_80 = local_a0;
      __ZNSt3__118__for_each_segmentB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS2_RS2_PS3_lLl256EEENS_11__copy_implINS_17_ClassicAlgPolicyEE12_CopySegmentIS6_S6_EEEEvT_SC_T0_
                (uVar4,puVar14,auVar21._0_8_,auVar21._8_8_,&local_80);
      local_a0 = local_80;
      puStack_98 = puStack_78;
    }
    local_80 = local_a0;
    puStack_78 = puStack_98;
    __ZNSt3__118__for_each_segmentB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS2_RS2_PS3_lLl256EEENS_11__copy_implINS_17_ClassicAlgPolicyEE12_CopySegmentIS6_S6_EEEEvT_SC_T0_
              (param_4,puVar6,param_6,param_7,&local_80);
  }
LAB_000083a4:
  local_80 = (long *)(*(long *)(param_1 + 8) + (*(ulong *)(param_1 + 0x20) >> 8) * 8);
  if (*(long *)(param_1 + 0x10) == *(long *)(param_1 + 8)) {
    puStack_78 = (undefined4 *)0x0;
  }
  else {
    puStack_78 = (undefined4 *)(*local_80 + (*(ulong *)(param_1 + 0x20) & 0xff) * 0x10);
  }
  __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El
            (&local_80,uVar16);
  return;
}

// ==== 000083fc __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE20__add_front_capacityEm ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE20__add_front_capacityEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  size_t sVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  undefined8 *puVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 *puVar16;
  undefined8 *puVar17;
  ulong uVar18;
  undefined1 auVar19 [16];
  undefined8 local_88;
  undefined8 *local_80;
  undefined8 *puStack_78;
  undefined8 *local_70;
  undefined8 *local_68;
  long *local_60;
  
  lVar4 = param_1[1];
  lVar5 = param_1[2];
  lVar10 = lVar5 - lVar4;
  if (lVar10 == 0) {
    param_2 = param_2 + 1;
  }
  uVar14 = param_2 >> 8;
  lVar3 = 0;
  if (lVar10 != 0) {
    lVar3 = (lVar5 - lVar4) * 0x20 + -1;
  }
  if ((param_2 & 0xff) != 0) {
    uVar14 = uVar14 + 1;
  }
  lVar12 = param_1[4];
  uVar18 = lVar3 - (param_1[5] + lVar12);
  uVar11 = uVar14;
  if (uVar18 >> 8 <= uVar14) {
    uVar11 = uVar18 >> 8;
  }
  if (uVar14 <= uVar18 >> 8) {
    param_1[4] = lVar12 + uVar11 * 0x100;
    for (; uVar11 != 0; uVar11 = uVar11 - 1) {
      local_80 = *(undefined8 **)(param_1[2] + -8);
      param_1[2] = (long)(param_1[2] + -8);
      __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
                (param_1,&local_80);
    }
    return;
  }
  local_60 = param_1 + 3;
  uVar15 = uVar14 - uVar11;
  if ((ulong)((*local_60 - *param_1 >> 3) - (lVar10 >> 3)) < uVar15) {
    uVar9 = *local_60 - *param_1 >> 2;
    uVar1 = uVar15 + (lVar10 >> 3);
    if (uVar9 <= uVar1) {
      uVar9 = uVar1;
    }
    if (uVar9 == 0) {
      auVar19 = ZEXT816(0);
    }
    else {
      auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          ();
    }
    local_80 = auVar19._0_8_;
    local_68 = local_80 + auVar19._8_8_;
    puStack_78 = local_80;
    local_70 = local_80;
    do {
      local_88 = __Znwm(0x1000);
      __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE9push_backEOS2_
                (&local_80,&local_88);
      uVar15 = uVar15 - 1;
    } while (uVar15 != 0);
    puVar17 = (undefined8 *)param_1[2];
    if (0xff < uVar18) {
      do {
        if (local_70 == local_68) {
          if (puStack_78 < local_80 || (long)puStack_78 - (long)local_80 == 0) {
            uVar18 = (long)local_70 - (long)local_80 >> 2;
            if ((long)local_70 - (long)local_80 == 0) {
              uVar18 = 1;
            }
            auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                                (local_60,uVar18);
            puVar8 = local_80;
            puVar7 = auVar19._0_8_;
            puVar16 = puVar7 + (uVar18 >> 2);
            lVar10 = (long)local_70 - (long)puStack_78;
            local_70 = puVar16;
            if (lVar10 != 0) {
              local_70 = (undefined8 *)((long)puVar16 + lVar10);
              puVar13 = puVar16;
              do {
                *puVar13 = *puStack_78;
                lVar10 = lVar10 + -8;
                puStack_78 = puStack_78 + 1;
                puVar13 = puVar13 + 1;
              } while (lVar10 != 0);
            }
            local_68 = puVar7 + auVar19._8_8_;
            bVar2 = local_80 != (undefined8 *)0x0;
            local_80 = puVar7;
            puStack_78 = puVar16;
            if (bVar2) {
              __ZdlPv(puVar8);
            }
          }
          else {
            lVar10 = (((long)puStack_78 - (long)local_80 >> 3) + 1) / 2;
            puVar16 = puStack_78 + -lVar10;
            sVar6 = (long)local_70 - (long)puStack_78;
            if (sVar6 != 0) {
              _memmove(puVar16,puStack_78,sVar6);
            }
            local_70 = (undefined8 *)((long)puVar16 + sVar6);
            puStack_78 = puStack_78 + -lVar10;
          }
        }
        *local_70 = puVar17[-1];
        local_70 = local_70 + 1;
        puVar17 = (undefined8 *)(param_1[2] + -8);
        param_1[2] = (long)puVar17;
        uVar11 = uVar11 - 1;
      } while (uVar11 != 0);
    }
    puVar16 = (undefined8 *)param_1[1];
    if (puVar16 != puVar17) {
      do {
        if (local_70 == local_68) {
          if (puStack_78 < local_80 || (long)puStack_78 - (long)local_80 == 0) {
            uVar11 = (long)local_70 - (long)local_80 >> 2;
            if ((long)local_70 - (long)local_80 == 0) {
              uVar11 = 1;
            }
            auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                                (local_60,uVar11);
            puVar8 = local_80;
            puVar7 = auVar19._0_8_;
            puVar17 = puVar7 + (uVar11 >> 2);
            lVar10 = (long)local_70 - (long)puStack_78;
            local_70 = puVar17;
            if (lVar10 != 0) {
              local_70 = (undefined8 *)((long)puVar17 + lVar10);
              puVar13 = puVar17;
              do {
                *puVar13 = *puStack_78;
                lVar10 = lVar10 + -8;
                puStack_78 = puStack_78 + 1;
                puVar13 = puVar13 + 1;
              } while (lVar10 != 0);
            }
            local_68 = puVar7 + auVar19._8_8_;
            bVar2 = local_80 != (undefined8 *)0x0;
            local_80 = puVar7;
            puStack_78 = puVar17;
            if (bVar2) {
              __ZdlPv(puVar8);
            }
          }
          else {
            lVar10 = (((long)puStack_78 - (long)local_80 >> 3) + 1) / 2;
            puVar17 = puStack_78 + -lVar10;
            sVar6 = (long)local_70 - (long)puStack_78;
            if (sVar6 != 0) {
              _memmove(puVar17,puStack_78,sVar6);
            }
            local_70 = (undefined8 *)((long)puVar17 + sVar6);
            puStack_78 = puStack_78 + -lVar10;
          }
        }
        puVar8 = puVar16 + 1;
        *local_70 = *puVar16;
        local_70 = local_70 + 1;
        puVar17 = (undefined8 *)param_1[2];
        puVar16 = puVar8;
      } while (puVar8 != puVar17);
      puVar16 = (undefined8 *)param_1[1];
    }
    lVar10 = param_1[3];
    param_1[2] = (long)local_70;
    param_1[3] = (long)local_68;
    puVar8 = (undefined8 *)*param_1;
    param_1[1] = (long)puStack_78;
    *param_1 = (long)local_80;
    param_1[4] = (uVar14 * 0x100 - (ulong)(lVar5 == lVar4)) + param_1[4];
    local_70 = puVar17;
    if (puVar17 != puVar16) {
      local_70 = (undefined8 *)
                 ((long)puVar17 + ((long)puVar16 + (7 - (long)puVar17) & 0xfffffffffffffff8U));
    }
    if (puVar8 == (undefined8 *)0x0) {
      return;
    }
    local_80 = puVar8;
    puStack_78 = puVar16;
    local_68 = (undefined8 *)lVar10;
    __ZdlPv();
    return;
  }
  for (; uVar15 != 0; uVar15 = uVar15 - 1) {
    if (lVar4 == *param_1) goto LAB_00008544;
    local_80 = (undefined8 *)__Znwm(0x1000);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
              (param_1,&local_80);
    lVar4 = param_1[1];
    lVar12 = 0xff;
    if (param_1[2] - lVar4 != 8) {
      lVar12 = 0x100;
    }
    lVar12 = lVar12 + param_1[4];
    param_1[4] = lVar12;
    uVar14 = uVar14 - 1;
  }
LAB_0000856c:
  param_1[4] = lVar12 + uVar11 * 0x100;
  for (; uVar11 != 0; uVar11 = uVar11 - 1) {
    local_80 = *(undefined8 **)(param_1[2] + -8);
    param_1[2] = (long)(param_1[2] + -8);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
              (param_1,&local_80);
  }
  return;
LAB_00008544:
  do {
    local_80 = (undefined8 *)__Znwm(0x1000);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE9push_backEOS2_
              (param_1,&local_80);
    uVar15 = uVar15 - 1;
  } while (uVar15 != 0);
  lVar12 = param_1[4];
  uVar11 = uVar14;
  goto LAB_0000856c;
}

// ==== 00008898 __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El ====
void __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El
               (undefined8 *param_1,long param_2)

{
  if ((param_2 != 0) && (0 < param_2 + (param_1[1] - *(long *)*param_1 >> 4))) {
    return;
  }
  return;
}

// ==== 000088f4 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEm ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEm
               (long *param_1,ulong param_2)

{
  bool bVar1;
  size_t sVar2;
  undefined8 *puVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  long *plVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  undefined8 *puVar15;
  undefined8 uVar16;
  long lVar17;
  long lVar18;
  undefined1 auVar19 [16];
  undefined8 local_88;
  undefined8 *local_80;
  undefined8 *puStack_78;
  undefined8 *local_70;
  undefined8 *puStack_68;
  long *local_60;
  
  puVar15 = (undefined8 *)param_1[2];
  if ((long)puVar15 - param_1[1] == 0) {
    param_2 = param_2 + 1;
  }
  uVar8 = param_2 >> 8;
  if ((param_2 & 0xff) != 0) {
    uVar8 = uVar8 + 1;
  }
  uVar14 = param_1[4];
  uVar7 = uVar8;
  if (uVar14 >> 8 <= uVar8) {
    uVar7 = uVar14 >> 8;
  }
  if (uVar8 <= uVar14 >> 8) {
    param_1[4] = uVar14 + uVar7 * -0x100;
    for (; uVar7 != 0; uVar7 = uVar7 - 1) {
      puVar3 = (undefined8 *)param_1[1] + 1;
      uVar16 = *(undefined8 *)param_1[1];
      param_1[1] = (long)puVar3;
      if (puVar15 == (undefined8 *)param_1[3]) {
        puVar6 = (undefined8 *)*param_1;
        if (puVar3 < puVar6 || (long)puVar3 - (long)puVar6 == 0) {
          uVar8 = (long)puVar15 - (long)puVar6 >> 2;
          if ((long)puVar15 - (long)puVar6 == 0) {
            uVar8 = 1;
          }
          auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                              (param_1 + 3,uVar8);
          lVar12 = auVar19._0_8_;
          puVar3 = (undefined8 *)(lVar12 + (uVar8 >> 2) * 8);
          lVar4 = param_1[2] - param_1[1];
          puVar15 = puVar3;
          if (lVar4 != 0) {
            puVar15 = (undefined8 *)((long)puVar3 + lVar4);
            puVar6 = (undefined8 *)param_1[1];
            puVar10 = puVar3;
            do {
              *puVar10 = *puVar6;
              lVar4 = lVar4 + -8;
              puVar6 = puVar6 + 1;
              puVar10 = puVar10 + 1;
            } while (lVar4 != 0);
          }
          lVar4 = *param_1;
          *param_1 = lVar12;
          param_1[1] = (long)puVar3;
          param_1[2] = (long)puVar15;
          param_1[3] = lVar12 + auVar19._8_8_ * 8;
          if (lVar4 != 0) {
            __ZdlPv(lVar4);
            puVar15 = (undefined8 *)param_1[2];
          }
        }
        else {
          lVar4 = (((long)puVar3 - (long)puVar6 >> 3) + 1) / 2;
          puVar6 = puVar3 + -lVar4;
          sVar2 = (long)puVar15 - (long)puVar3;
          if (sVar2 != 0) {
            _memmove(puVar6,puVar3,sVar2);
            puVar3 = (undefined8 *)param_1[1];
          }
          puVar15 = (undefined8 *)((long)puVar6 + sVar2);
          param_1[1] = (long)(puVar3 + -lVar4);
          param_1[2] = (long)puVar15;
        }
      }
      *puVar15 = uVar16;
      puVar15 = (undefined8 *)(param_1[2] + 8);
      param_1[2] = (long)puVar15;
    }
    return;
  }
  plVar11 = param_1 + 3;
  uVar13 = uVar8 - uVar7;
  lVar4 = (long)puVar15 - param_1[1] >> 3;
  if ((ulong)((*plVar11 - *param_1 >> 3) - lVar4) < uVar13) {
    uVar8 = *plVar11 - *param_1 >> 2;
    if (uVar8 <= uVar13 + lVar4) {
      uVar8 = uVar13 + lVar4;
    }
    local_60 = plVar11;
    if (uVar8 == 0) {
      auVar19 = ZEXT816(0);
    }
    else {
      auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                          (plVar11);
    }
    local_80 = auVar19._0_8_;
    puStack_78 = local_80 + (lVar4 - uVar7);
    puStack_68 = local_80 + auVar19._8_8_;
    local_70 = puStack_78;
    do {
      local_88 = __Znwm(0x1000);
      __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE9push_backEOS2_
                (&local_80,&local_88);
      uVar13 = uVar13 - 1;
    } while (uVar13 != 0);
    if (0xff < uVar14) {
      puVar15 = (undefined8 *)param_1[1];
      uVar8 = uVar7;
      do {
        if (local_70 == puStack_68) {
          if (puStack_78 < local_80 || (long)puStack_78 - (long)local_80 == 0) {
            uVar14 = (long)local_70 - (long)local_80 >> 2;
            if ((long)local_70 - (long)local_80 == 0) {
              uVar14 = 1;
            }
            auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                                (local_60,uVar14);
            puVar6 = local_80;
            puVar10 = auVar19._0_8_;
            puVar3 = puVar10 + (uVar14 >> 2);
            lVar4 = (long)local_70 - (long)puStack_78;
            local_70 = puVar3;
            if (lVar4 != 0) {
              local_70 = (undefined8 *)((long)puVar3 + lVar4);
              puVar9 = puVar3;
              do {
                *puVar9 = *puStack_78;
                lVar4 = lVar4 + -8;
                puStack_78 = puStack_78 + 1;
                puVar9 = puVar9 + 1;
              } while (lVar4 != 0);
            }
            puStack_68 = puVar10 + auVar19._8_8_;
            bVar1 = local_80 != (undefined8 *)0x0;
            local_80 = puVar10;
            puStack_78 = puVar3;
            if (bVar1) {
              __ZdlPv(puVar6);
            }
          }
          else {
            lVar4 = (((long)puStack_78 - (long)local_80 >> 3) + 1) / 2;
            puVar3 = puStack_78 + -lVar4;
            sVar2 = (long)local_70 - (long)puStack_78;
            if (sVar2 != 0) {
              _memmove(puVar3,puStack_78,sVar2);
            }
            local_70 = (undefined8 *)((long)puVar3 + sVar2);
            puStack_78 = puStack_78 + -lVar4;
          }
        }
        *local_70 = *puVar15;
        local_70 = local_70 + 1;
        puVar15 = (undefined8 *)(param_1[1] + 8);
        param_1[1] = (long)puVar15;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
    }
    lVar12 = param_1[2];
    lVar4 = -7 - lVar12;
    while (lVar5 = param_1[1], lVar12 != lVar5) {
      lVar12 = lVar12 + -8;
      lVar4 = lVar4 + 8;
      __ZNSt3__114__split_bufferIP20BufferFollowerActionRNS_9allocatorIS2_EEE10push_frontERKS2_
                (&local_80,lVar12);
    }
    puVar15 = (undefined8 *)*param_1;
    lVar18 = param_1[3];
    lVar17 = param_1[2];
    param_1[1] = (long)puStack_78;
    *param_1 = (long)local_80;
    param_1[3] = (long)puStack_68;
    param_1[2] = (long)local_70;
    param_1[4] = param_1[4] + uVar7 * -0x100;
    local_70 = (undefined8 *)lVar17;
    if (lVar12 != lVar17) {
      local_70 = (undefined8 *)(lVar17 + (-(lVar17 + lVar4) & 0xfffffffffffffff8U));
    }
    if (puVar15 == (undefined8 *)0x0) {
      return;
    }
    local_80 = puVar15;
    puStack_78 = (undefined8 *)lVar5;
    puStack_68 = (undefined8 *)lVar18;
    __ZdlPv();
    return;
  }
  for (; uVar13 != 0; uVar13 = uVar13 - 1) {
    if (param_1[3] == param_1[2]) goto LAB_00008c78;
    local_80 = (undefined8 *)__Znwm(0x1000);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE9push_backEOS2_
              (param_1,&local_80);
    uVar8 = uVar8 - 1;
  }
  lVar4 = param_1[4];
  uVar8 = uVar7;
LAB_00008cb8:
  param_1[4] = lVar4 + uVar8 * -0x100;
  if (uVar8 != 0) {
    puVar15 = (undefined8 *)param_1[2];
    do {
      puVar3 = (undefined8 *)param_1[1] + 1;
      uVar16 = *(undefined8 *)param_1[1];
      param_1[1] = (long)puVar3;
      if (puVar15 == (undefined8 *)param_1[3]) {
        puVar6 = (undefined8 *)*param_1;
        if (puVar3 < puVar6 || (long)puVar3 - (long)puVar6 == 0) {
          uVar7 = (long)puVar15 - (long)puVar6 >> 2;
          if ((long)puVar15 - (long)puVar6 == 0) {
            uVar7 = 1;
          }
          auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIP29BufferedFilePlaybackDSPKernelEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS7_m
                              (plVar11,uVar7);
          lVar12 = auVar19._0_8_;
          puVar3 = (undefined8 *)(lVar12 + (uVar7 >> 2) * 8);
          lVar4 = param_1[2] - param_1[1];
          puVar15 = puVar3;
          if (lVar4 != 0) {
            puVar15 = (undefined8 *)((long)puVar3 + lVar4);
            puVar6 = (undefined8 *)param_1[1];
            puVar10 = puVar3;
            do {
              *puVar10 = *puVar6;
              lVar4 = lVar4 + -8;
              puVar6 = puVar6 + 1;
              puVar10 = puVar10 + 1;
            } while (lVar4 != 0);
          }
          lVar4 = *param_1;
          *param_1 = lVar12;
          param_1[1] = (long)puVar3;
          param_1[2] = (long)puVar15;
          param_1[3] = lVar12 + auVar19._8_8_ * 8;
          if (lVar4 != 0) {
            __ZdlPv(lVar4);
            puVar15 = (undefined8 *)param_1[2];
          }
        }
        else {
          lVar4 = (((long)puVar3 - (long)puVar6 >> 3) + 1) / 2;
          puVar6 = puVar3 + -lVar4;
          sVar2 = (long)puVar15 - (long)puVar3;
          if (sVar2 != 0) {
            _memmove(puVar6,puVar3,sVar2);
            puVar3 = (undefined8 *)param_1[1];
          }
          puVar15 = (undefined8 *)((long)puVar6 + sVar2);
          param_1[1] = (long)(puVar3 + -lVar4);
          param_1[2] = (long)puVar15;
        }
      }
      *puVar15 = uVar16;
      puVar15 = (undefined8 *)(param_1[2] + 8);
      param_1[2] = (long)puVar15;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  return;
LAB_00008c78:
  do {
    local_80 = (undefined8 *)__Znwm(0x1000);
    __ZNSt3__114__split_bufferIP20BufferFollowerActionNS_9allocatorIS2_EEE10push_frontERKS2_
              (param_1,&local_80);
    lVar4 = 0xff;
    if (param_1[2] - param_1[1] != 8) {
      lVar4 = 0x100;
    }
    lVar4 = lVar4 + param_1[4];
    param_1[4] = lVar4;
    uVar13 = uVar13 - 1;
  } while (uVar13 != 0);
  goto LAB_00008cb8;
}

// ==== 00008e3c __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEmiB8ne190102El ====
void __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEmiB8ne190102El
               (undefined8 *param_1,long param_2)

{
  if ((param_2 != 0) && (0 < (param_1[1] - *(long *)*param_1 >> 4) - param_2)) {
    return;
  }
  return;
}

// ==== 00008e9c __ZNSt3__118__for_each_segmentB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS2_RS2_PS3_lLl256EEENS_11__copy_implINS_17_ClassicAlgPolicyEE12_CopySegmentIS6_S6_EEEEvT_SC_T0_ ====
void __ZNSt3__118__for_each_segmentB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS2_RS2_PS3_lLl256EEENS_11__copy_implINS_17_ClassicAlgPolicyEE12_CopySegmentIS6_S6_EEEEvT_SC_T0_
               (long *param_1,long param_2,long *param_3,undefined8 param_4,undefined8 *param_5)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined1 auStack_58 [8];
  undefined8 local_50;
  undefined8 uStack_48;
  
  if (param_1 == param_3) {
    uVar1 = *param_5;
    uVar2 = param_5[1];
  }
  else {
    __ZNSt3__124__copy_move_unwrap_itersB8ne190102INS_11__copy_implINS_17_ClassicAlgPolicyEEEP20BufferFollowerActionS5_NS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT0_T2_EESB_T1_SC_
              (auStack_58,param_2,*param_1 + 0x1000,*param_5,param_5[1]);
    while( true ) {
      param_1 = param_1 + 1;
      param_5[1] = uStack_48;
      *param_5 = local_50;
      if (param_1 == param_3) break;
      __ZNSt3__124__copy_move_unwrap_itersB8ne190102INS_11__copy_implINS_17_ClassicAlgPolicyEEEP20BufferFollowerActionS5_NS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT0_T2_EESB_T1_SC_
                (auStack_58,*param_1,*param_1 + 0x1000,*param_5,param_5[1]);
    }
    param_2 = *param_1;
    uVar1 = *param_5;
    uVar2 = param_5[1];
  }
  __ZNSt3__124__copy_move_unwrap_itersB8ne190102INS_11__copy_implINS_17_ClassicAlgPolicyEEEP20BufferFollowerActionS5_NS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT0_T2_EESB_T1_SC_
            (auStack_58,param_2,param_4,uVar1,uVar2);
  param_5[1] = uStack_48;
  *param_5 = local_50;
  return;
}

// ==== 00008f5c __ZNSt3__124__copy_move_unwrap_itersB8ne190102INS_11__copy_implINS_17_ClassicAlgPolicyEEEP20BufferFollowerActionS5_NS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT0_T2_EESB_T1_SC_ ====
void __ZNSt3__124__copy_move_unwrap_itersB8ne190102INS_11__copy_implINS_17_ClassicAlgPolicyEEEP20BufferFollowerActionS5_NS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT0_T2_EESB_T1_SC_
               (long *param_1,undefined8 *param_2,undefined8 *param_3,long *param_4,
               undefined8 *param_5)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  
  if (param_2 != param_3) {
    puVar2 = (undefined8 *)*param_4;
    do {
      lVar3 = (long)puVar2 + (0x1000 - (long)param_5) >> 4;
      lVar4 = (long)param_3 - (long)param_2 >> 4;
      if (lVar3 <= lVar4) {
        lVar4 = lVar3;
      }
      if (lVar4 != 0) {
        lVar3 = lVar4 << 4;
        puVar2 = param_2 + lVar4 * 2;
        puVar1 = param_5;
        do {
          uVar5 = *param_2;
          param_5 = puVar1 + 2;
          puVar1[1] = param_2[1];
          *puVar1 = uVar5;
          lVar3 = lVar3 + -0x10;
          param_2 = param_2 + 2;
          puVar1 = param_5;
        } while (lVar3 != 0);
        param_2 = puVar2;
        if (puVar2 == param_3) goto LAB_00008fc0;
      }
      param_4 = param_4 + 1;
      param_5 = (undefined8 *)*param_4;
      puVar2 = param_5;
    } while( true );
  }
LAB_00008fd4:
  *param_1 = (long)param_3;
  param_1[1] = (long)param_4;
  param_1[2] = (long)param_5;
  return;
LAB_00008fc0:
  if (param_5 == (undefined8 *)(*param_4 + 0x1000)) {
    param_4 = param_4 + 1;
    param_5 = (undefined8 *)*param_4;
  }
  goto LAB_00008fd4;
}

// ==== 00008fe0 __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS5_RS5_PS6_lLl256EEES9_Li0EEENS_4pairIT_T0_EESB_SB_SC_ ====
void __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102INS_16__deque_iteratorI20BufferFollowerActionPS5_RS5_PS6_lLl256EEES9_Li0EEENS_4pairIT_T0_EESB_SB_SC_
               (undefined8 *param_1,undefined8 param_2,long *param_3,undefined8 param_4,
               long *param_5,long param_6,undefined8 param_7,undefined8 param_8)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  undefined1 uStack_59;
  undefined1 auStack_58 [8];
  undefined8 local_50;
  undefined8 uStack_48;
  
  lVar2 = param_6;
  if (param_3 != param_5) {
    lVar1 = *param_5;
    plVar3 = param_5;
    while( true ) {
      plVar3 = plVar3 + -1;
      __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102IP20BufferFollowerActionNS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT_T0_EESB_SB_SC_
                (auStack_58,&uStack_59,lVar1,lVar2,param_7,param_8);
      param_7 = local_50;
      param_8 = uStack_48;
      if (plVar3 == param_3) break;
      lVar1 = *plVar3;
      lVar2 = lVar1 + 0x1000;
    }
    lVar2 = *plVar3 + 0x1000;
  }
  __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102IP20BufferFollowerActionNS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT_T0_EESB_SB_SC_
            (auStack_58,&uStack_59,param_4,lVar2,param_7,param_8);
  *param_1 = param_5;
  param_1[1] = param_6;
  param_1[3] = uStack_48;
  param_1[2] = local_50;
  return;
}

// ==== 000090ac __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102IP20BufferFollowerActionNS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT_T0_EESB_SB_SC_ ====
void __ZNKSt3__120__copy_backward_implINS_17_ClassicAlgPolicyEEclB8ne190102IP20BufferFollowerActionNS_16__deque_iteratorIS4_S5_RS4_PS5_lLl256EEELi0EEENS_4pairIT_T0_EESB_SB_SC_
               (long *param_1,undefined8 param_2,undefined8 *param_3,undefined8 *param_4,
               long *param_5,long param_6)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  
  if (param_3 != param_4) {
    lVar4 = *param_5;
    puVar2 = param_4;
    while( true ) {
      lVar5 = param_6 - lVar4 >> 4;
      lVar4 = (long)puVar2 - (long)param_3 >> 4;
      if (lVar5 <= lVar4) {
        lVar4 = lVar5;
      }
      if (lVar4 != 0) {
        lVar5 = lVar4 * -0x10;
        lVar3 = param_6;
        puVar1 = puVar2;
        do {
          param_6 = lVar3 + -0x10;
          uVar6 = puVar1[-2];
          *(undefined8 *)(lVar3 + -8) = puVar1[-1];
          *(undefined8 *)(lVar3 + -0x10) = uVar6;
          lVar5 = lVar5 + 0x10;
          lVar3 = param_6;
          puVar1 = puVar1 + -2;
        } while (lVar5 != 0);
      }
      puVar2 = puVar2 + lVar4 * -2;
      if (puVar2 == param_3) break;
      param_5 = param_5 + -1;
      lVar4 = *param_5;
      param_6 = lVar4 + 0x1000;
    }
    param_3 = param_4;
    if (*param_5 + 0x1000 == param_6) {
      param_5 = param_5 + 1;
      param_6 = *param_5;
    }
  }
  *param_1 = (long)param_3;
  param_1[1] = (long)param_5;
  param_1[2] = param_6;
  return;
}

// ==== 00009144 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE26__maybe_remove_front_spareB8ne190102Eb ====
uint __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE26__maybe_remove_front_spareB8ne190102Eb
               (long param_1,uint param_2)

{
  uint uVar1;
  
  if (*(ulong *)(param_1 + 0x20) < 0x100) {
    param_2 = 1;
  }
  uVar1 = 0;
  if (*(ulong *)(param_1 + 0x20) < 0x200) {
    uVar1 = param_2;
  }
  if ((uVar1 & 1) == 0) {
    __ZdlPv(**(undefined8 **)(param_1 + 8));
    *(long *)(param_1 + 8) = *(long *)(param_1 + 8) + 8;
    *(long *)(param_1 + 0x20) = *(long *)(param_1 + 0x20) + -0x100;
  }
  return uVar1 ^ 1;
}

// ==== 000091a0 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEEC2ERKS4_ ====
undefined8 *
__ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEEC2ERKS4_
          (undefined8 *param_1,long param_2)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  uVar6 = *(ulong *)(param_2 + 0x20);
  lVar2 = *(long *)(param_2 + 8);
  plVar1 = (long *)(lVar2 + (uVar6 >> 8) * 8);
  if (*(long *)(param_2 + 0x10) == lVar2) {
    lVar3 = 0;
    lVar5 = 0;
    plVar4 = (long *)(lVar2 + (*(long *)(param_2 + 0x28) + uVar6 >> 8) * 8);
  }
  else {
    lVar3 = *plVar1 + (uVar6 & 0xff) * 0x10;
    uVar6 = *(long *)(param_2 + 0x28) + uVar6;
    plVar4 = (long *)(lVar2 + (uVar6 >> 8) * 8);
    lVar5 = *plVar4 + (uVar6 & 0xff) * 0x10;
  }
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE8__appendINS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEELi0EEEvT_SD_
            (param_1,plVar1,lVar3,plVar4,lVar5);
  return param_1;
}

// ==== 00009240 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE8__appendINS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEELi0EEEvT_SD_ ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE8__appendINS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEELi0EEEvT_SD_
               (undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,long param_5)

{
  if (param_5 == param_3) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE18__append_with_sizeB8ne190102INS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEEEEvT_m
              ();
    return;
  }
  __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE18__append_with_sizeB8ne190102INS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEEEEvT_m
            ();
  return;
}

// ==== 00009274 __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE18__append_with_sizeB8ne190102INS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEEEEvT_m ====
void __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE18__append_with_sizeB8ne190102INS_16__deque_iteratorIS1_PKS1_RS7_PKS8_lLl256EEEEEvT_m
               (long param_1,long *param_2,undefined4 *param_3,ulong param_4)

{
  long lVar1;
  undefined4 *puVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  ulong uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  long *plVar11;
  undefined4 *puVar12;
  undefined1 auVar13 [16];
  long *local_50;
  undefined4 *puStack_48;
  
  lVar3 = *(long *)(param_1 + 8);
  lVar5 = *(long *)(param_1 + 0x10);
  lVar4 = 0;
  if (lVar5 != lVar3) {
    lVar4 = (lVar5 - lVar3) * 0x20 + -1;
  }
  uVar8 = *(long *)(param_1 + 0x28) + *(long *)(param_1 + 0x20);
  lVar1 = param_4 - (lVar4 - uVar8);
  if (lVar4 - uVar8 <= param_4 && lVar1 != 0) {
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE19__add_back_capacityEm
              (param_1,lVar1);
    lVar3 = *(long *)(param_1 + 8);
    lVar5 = *(long *)(param_1 + 0x10);
    uVar8 = *(long *)(param_1 + 0x20) + *(long *)(param_1 + 0x28);
  }
  plVar11 = (long *)(lVar3 + (uVar8 >> 8) * 8);
  if (lVar5 == lVar3) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12 = (undefined4 *)(*plVar11 + (uVar8 & 0xff) * 0x10);
  }
  local_50 = plVar11;
  puStack_48 = puVar12;
  auVar13 = __ZNKSt3__116__deque_iteratorI20BufferFollowerActionPS1_RS1_PS2_lLl256EEplB8ne190102El
                      (&local_50,param_4);
  puVar2 = auVar13._8_8_;
  if (puVar12 != puVar2) {
    lVar4 = *(long *)(param_1 + 0x28);
    do {
      puVar6 = puVar2;
      if (plVar11 != auVar13._0_8_) {
        puVar6 = (undefined4 *)(*plVar11 + 0x1000);
      }
      puVar7 = puVar12;
      if (puVar12 != puVar6) {
        puVar9 = (undefined4 *)*param_2;
        puVar10 = puVar12;
        do {
          *puVar10 = *param_3;
          *(undefined8 *)(puVar10 + 2) = *(undefined8 *)(param_3 + 2);
          param_3 = param_3 + 4;
          if ((long)param_3 - (long)puVar9 == 0x1000) {
            param_2 = param_2 + 1;
            puVar9 = (undefined4 *)*param_2;
            param_3 = puVar9;
          }
          puVar10 = puVar10 + 4;
          puVar7 = puVar6;
        } while (puVar10 != puVar6);
      }
      lVar4 = lVar4 + ((long)puVar7 - (long)puVar12 >> 4);
      if (plVar11 == auVar13._0_8_) break;
      plVar11 = plVar11 + 1;
      puVar12 = (undefined4 *)*plVar11;
    } while (puVar12 != puVar2);
    *(long *)(param_1 + 0x28) = lVar4;
  }
  return;
}

// ==== 000093bc ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke ====
void ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke(long param_1)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  
  lVar2 = *(long *)(param_1 + 0x20);
  iVar3 = (int)(*(double *)(lVar2 + 0x78) * (double)*(float *)(param_1 + 0x28));
  if (*(long *)(lVar2 + 0x60) <= (long)iVar3) {
    iVar3 = (int)*(long *)(lVar2 + 0x60) + -1;
  }
  piVar1 = (int *)(lVar2 + 0x170);
  *piVar1 = iVar3;
  if ((*(byte *)(lVar2 + 8) & 1) != 0) {
    return;
  }
  *(int *)(lVar2 + 0x20) = *piVar1;
  _ExtAudioFileSeek(*(undefined8 *)(lVar2 + 0x30),
                    (long)(*(double *)(lVar2 + 0x18) * (double)*piVar1));
  return;
}

// ==== 00009424 ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke_2 ====
void ____ZN35BufferedFilePlaybackDSPKernelMaster12setParameterEyf_block_invoke_2(long param_1)

{
  int iVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  
  lVar2 = *(long *)(param_1 + 0x20);
  iVar3 = (int)(*(double *)(lVar2 + 0x78) * (double)*(float *)(param_1 + 0x28));
  if (*(int *)(lVar2 + 0x170) < iVar3) {
    iVar1 = (int)*(long *)(lVar2 + 0x60);
    if ((long)iVar3 <= *(long *)(lVar2 + 0x60)) {
      iVar1 = iVar3;
    }
    *(int *)(lVar2 + 0x174) = iVar1;
    iVar3 = *(int *)(lVar2 + 0x174);
    lVar4 = 0x184;
  }
  else {
    iVar3 = *(int *)(lVar2 + 0x60);
    lVar4 = 0x174;
  }
  *(int *)(lVar2 + lVar4) = iVar3;
  return;
}

// ==== 00009480 ____ZN35BufferedFilePlaybackDSPKernelMaster13prepareToPlayEi_block_invoke ====
void ____ZN35BufferedFilePlaybackDSPKernelMaster13prepareToPlayEi_block_invoke(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  int iVar3;
  undefined8 *puVar4;
  undefined1 auStack_a0 [48];
  undefined4 local_70 [2];
  long local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  lVar1 = *(long *)(param_1 + 0x20);
  uVar2 = _ExtAudioFileSeek(*(undefined8 *)(lVar1 + 0x30),*(undefined8 *)(param_1 + 0x28));
  if ((int)uVar2 == 0) {
    uStack_48 = 0;
    local_50 = 0;
    uStack_38 = 0;
    uStack_40 = 0;
    uStack_58 = 0;
    local_60 = 0;
    local_68 = (long)*(int *)(param_1 + 0x28);
    local_70[0] = 0;
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEE9push_backEOS1_(&local_60,local_70);
    for (puVar4 = *(undefined8 **)(lVar1 + 0x200); puVar4 < *(undefined8 **)(lVar1 + 0x208);
        puVar4 = puVar4 + 1) {
      uVar2 = *puVar4;
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEEC2ERKS4_(auStack_a0,&local_60);
      __ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE
                (uVar2,auStack_a0);
      __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(auStack_a0);
    }
    iVar3 = *(int *)(param_1 + 0x30);
    if ((long)iVar3 < *(long *)(lVar1 + 0x60)) {
      *(undefined1 *)(lVar1 + 10) = 0;
      iVar3 = *(int *)(param_1 + 0x30);
    }
    *(int *)(lVar1 + 0x20) = iVar3;
    *(int *)(lVar1 + 0x180) = *(int *)(lVar1 + 0x20);
    *(undefined1 *)(lVar1 + 0x70) = 0;
    __ZN35BufferedFilePlaybackDSPKernelMaster18fillCircularBufferEb(lVar1,1);
    __ZNSt3__15dequeI20BufferFollowerActionNS_9allocatorIS1_EEED2B8ne190102Ev(&local_60);
  }
  else if (*(long *)(lVar1 + 0x138) != 0) {
    __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
              (lVar1 + 0x120,uVar2,3,*(undefined8 *)(lVar1 + 0x28));
    return;
  }
  return;
}

// ==== 000095c0 __ZNSt3__18functionIFvfEEaSERKS2_ ====
undefined8 __ZNSt3__18functionIFvfEEaSERKS2_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
  __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvfEE4swapB8ne190102ERS3_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00009624;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00009624:
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00009654 __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_ ====
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

// ==== 000096b8 __ZNSt3__110__function12__value_funcIFvfEE4swapB8ne190102ERS3_ ====
void __ZNSt3__110__function12__value_funcIFvfEE4swapB8ne190102ERS3_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
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
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00009824 __ZNSt3__18functionIFvvEEaSERKS2_ ====
undefined8 __ZNSt3__18functionIFvvEEaSERKS2_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
  __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00009888;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00009888:
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 000098b8 __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_ ====
void __ZNSt3__110__function12__value_funcIFvvEE4swapB8ne190102ERS3_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
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
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00009a24 __ZNSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEaSERKS6_ ====
undefined8
__ZNSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEaSERKS6_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
  __ZNSt3__110__function12__value_funcIFvvEEC2B8ne190102ERKS3_(alStack_48);
  __ZNSt3__110__function12__value_funcIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
            (alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00009a88;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00009a88:
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00009ab8 __ZNSt3__110__function12__value_funcIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE4swapB8ne190102ERS7_ ====
void __ZNSt3__110__function12__value_funcIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE4swapB8ne190102ERS7_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_00010040;
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
  if (*(long *)PTR____stack_chk_guard_00010040 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00009c24 __ZN29BufferedFilePlaybackDSPKernel14setUpAudioFileEv ====
void __ZN29BufferedFilePlaybackDSPKernel14setUpAudioFileEv(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 local_24;
  
  uVar2 = _ExtAudioFileOpenURL(*(undefined8 *)(param_1 + 0x28),param_1 + 0x30);
  if ((int)uVar2 == 0) {
    uVar2 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x30),0);
    if ((int)uVar2 == 0) {
      local_24 = 0x28;
      uVar2 = _ExtAudioFileGetProperty
                        (*(undefined8 *)(param_1 + 0x30),0x66666d74,&local_24,param_1 + 0x38);
      if ((int)uVar2 == 0) {
        *(double *)(param_1 + 0x78) = (double)*(float *)(param_1 + 0x10);
        *(undefined8 *)(param_1 + 0x80) = 0x16c70636d;
        iVar1 = *(int *)(param_1 + 0xc) << 2;
        *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0xc);
        *(undefined4 *)(param_1 + 0x98) = 0x20;
        *(undefined4 *)(param_1 + 0x8c) = 1;
        *(int *)(param_1 + 0x90) = iVar1;
        *(int *)(param_1 + 0x88) = iVar1;
        local_24 = 0x28;
        uVar2 = _ExtAudioFileSetProperty(*(undefined8 *)(param_1 + 0x30),0x63666d74,0x28);
        if ((int)uVar2 == 0) {
          local_24 = 8;
          uVar2 = _ExtAudioFileGetProperty
                            (*(undefined8 *)(param_1 + 0x30),0x2366726d,&local_24,param_1 + 0x60);
          if ((int)uVar2 == 0) {
            *(double *)(param_1 + 0x18) = *(double *)(param_1 + 0x38) / *(double *)(param_1 + 0x78);
            return;
          }
          if (*(long *)(param_1 + 0x138) == 0) {
            return;
          }
          uVar4 = *(undefined8 *)(param_1 + 0x28);
          uVar3 = 5;
        }
        else {
          if (*(long *)(param_1 + 0x138) == 0) {
            return;
          }
          uVar4 = *(undefined8 *)(param_1 + 0x28);
          uVar3 = 6;
        }
      }
      else {
        if (*(long *)(param_1 + 0x138) == 0) {
          return;
        }
        uVar4 = *(undefined8 *)(param_1 + 0x28);
        uVar3 = 4;
      }
      __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
                (param_1 + 0x120,uVar2,uVar3,uVar4);
      return;
    }
    if (*(long *)(param_1 + 0x138) == 0) {
      return;
    }
    uVar4 = *(undefined8 *)(param_1 + 0x28);
    uVar3 = 3;
  }
  else {
    if (*(long *)(param_1 + 0x138) == 0) {
      return;
    }
    uVar4 = *(undefined8 *)(param_1 + 0x28);
    uVar3 = 1;
  }
  __ZNKSt3__18functionIFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEiS1_S4_
            (param_1 + 0x120,uVar2,uVar3,uVar4);
  return;
}

// ==== 00009dac __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 00009dd4 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00009dfc __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_000102c8;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 00009e3c __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE7__cloneEPNS0_6__baseIS5_EE ====
void __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE7__cloneEPNS0_6__baseIS5_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_000102c8;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 00009e58 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 00009e60 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00009e88 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEEclEOf ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEEclEOf
          (long param_1,float *param_2)

{
  ID self;
  float fVar1;
  
  fVar1 = *param_2;
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::bufferedFilePlaybackAudioUnitDidUpdateCurrentTime_(self,(double)fVar1);
  return 0;
}

// ==== 00009f08 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 00009f44 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_0NS_9allocatorIS2_EEFvfEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0NS_9allocatorIS2_EEFvfEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__0
  ;
}

// ==== 00009f50 __ZNKSt9type_infoeqB8ne190102ERKS_ ====
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

// ==== 00009f9c __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 00009fc4 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00009fec __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_00010358;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 0000a02c __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE ====
void __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_00010358;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 0000a048 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 0000a050 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000a078 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEEclEv ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEEclEv
          (long param_1)

{
  ID self;
  
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::bufferedFilePlaybackAudioUnitStartPlayingEnqueuedSection(self);
  return 0;
}

// ==== 0000a0e8 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000a124 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_1NS_9allocatorIS2_EEFvvEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1NS_9allocatorIS2_EEFvvEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__1
  ;
}

// ==== 0000a130 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 0000a158 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000a180 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_000103e8;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 0000a1c0 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE ====
void __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE7__cloneEPNS0_6__baseIS5_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_000103e8;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 0000a1dc __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 0000a1e4 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000a20c __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEEclEv ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEEclEv
          (long param_1)

{
  ID self;
  
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::bufferedFilePlaybackAudioUnitReachedSongEnd(self);
  return 0;
}

// ==== 0000a27c __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000a2b8 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_2NS_9allocatorIS2_EEFvvEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2NS_9allocatorIS2_EEFvvEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__2
  ;
}

// ==== 0000a2c4 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEED1Ev ====
long __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 0000a2ec __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEED0Ev ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000a314 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_00010468;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 0000a354 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE ====
void __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7__cloneEPNS0_6__baseIS9_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_00010468;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 0000a370 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 0000a378 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000a3a0 __ZNSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEOiOS5_OS8_ ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEEclEOiOS5_OS8_
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
  objc_stub::bufferedFilePlaybackAudioUnitDSPKernelErrorStatus_operation_fileURL_
            (self,(ulong)uVar1,(ulong)uVar2,uVar3);
  return 0;
}

// ==== 0000a430 __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 0000a46c __ZNKSt3__110__function6__funcIZ81-[BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL:isMaster:delegate:]E3$_3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3NS_9allocatorIS2_EEFvi33BufferedFilePlaybackFileOperationPK7__CFURLEE11target_typeEv
          (void)

{
  return &
         __ZTIZ81__BufferedFilePlaybackAudioUnit_configureDSPKernelWithFileURL_isMaster_delegate__E3__3
  ;
}

// ==== 0000a478 __ZN19AudioObfuscatorImplC2Ev ====
void __ZN19AudioObfuscatorImplC2Ev(void)

{
  return;
}

// ==== 0000a47c __ZN19AudioObfuscatorImplC1Ev ====
void __ZN19AudioObfuscatorImplC1Ev(void)

{
  return;
}

// ==== 0000a480 __ZN19AudioObfuscatorImplD2Ev ====
void __ZN19AudioObfuscatorImplD2Ev(void)

{
  return;
}

// ==== 0000a484 __ZN19AudioObfuscatorImplD1Ev ====
void __ZN19AudioObfuscatorImplD1Ev(void)

{
  return;
}

// ==== 0000a488 __ZN19AudioObfuscatorImpl27obfuscateAllAudioFilesAtURLEP5NSURL ====
undefined8 __ZN19AudioObfuscatorImpl27obfuscateAllAudioFilesAtURLEP5NSURL(void)

{
  return 1;
}

// ==== 0000a490 __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE ====
void __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE
               (undefined8 param_1,undefined8 param_2,long param_3)

{
                    /* WARNING: Could not recover jumptable at 0x0000a498. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_3 + 0x10))(param_3);
  return;
}

// ==== 0000a49c __ZN19AudioObfuscatorImpl22obfuscateFileExtensionEP5NSURL ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

ID __ZN19AudioObfuscatorImpl22obfuscateFileExtensionEP5NSURL(undefined8 param_1,ID param_2)

{
  ID self;
  ID IVar1;
  ID IVar2;
  ID IVar3;
  long local_58;
  
  self = NSFileManager::defaultManager((ID)&_OBJC_CLASS___NSFileManager);
  IVar1 = objc_stub::path(param_2);
  IVar1 = NSFileManager::fileExistsAtPath_(self,IVar1);
  if ((IVar1 & 1) == 0) {
    IVar1 = 0;
  }
  else {
    IVar1 = objc_stub::pathExtension(param_2);
    IVar2 = objc_stub::path(param_2);
    IVar2 = objc_stub::stringByReplacingOccurrencesOfString_withString_(IVar2,IVar1,&cf_pmt);
    IVar1 = NSURL::fileURLWithPath_((ID)&_OBJC_CLASS___NSURL,IVar2);
    IVar3 = NSFileManager::fileExistsAtPath_(self,IVar2);
    if ((int)IVar3 != 0) {
      NSFileManager::removeItemAtPath_error_(self,IVar2,0);
    }
    IVar2 = objc_stub::path(param_2);
    IVar2 = NSURL::fileURLWithPath_((ID)&_OBJC_CLASS___NSURL,IVar2);
    local_58 = 0;
    NSFileManager::moveItemAtURL_toURL_error_(self,IVar2,IVar1,&local_58);
    if (local_58 != 0) {
      _NSLog(&cf_Errorwritingfileproperty___);
      IVar1 = 0;
    }
  }
  return IVar1;
}

// ==== 0000a70c __ZN19AudioObfuscatorImpl23obfuscatedFileIsWavFileEP5NSURL ====
undefined8
__ZN19AudioObfuscatorImpl23obfuscatedFileIsWavFileEP5NSURL(undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  int iVar2;
  ID self;
  char *pcVar3;
  FILE *pFVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  undefined4 local_4c;
  uint uStack_48;
  uint local_44 [2];
  uint local_3c;
  long local_38;
  
  local_38 = *(long *)PTR____stack_chk_guard_00010040;
  self = _objc_retainAutorelease(param_2);
  pcVar3 = (char *)objc_stub::fileSystemRepresentation(self);
  pFVar4 = _fopen(pcVar3,"r+");
  if (pFVar4 == (FILE *)0x0) {
    uVar8 = 0;
    iVar2 = 0;
    goto LAB_0000a854;
  }
  _fseek(pFVar4,0,0);
  _fseek(pFVar4,0,0);
  lVar7 = 0;
  do {
    iVar2 = _fgetc(pFVar4);
    *(byte *)((long)local_44 + lVar7) = *(byte *)(_wavKey + lVar7) ^ (byte)iVar2;
    lVar7 = lVar7 + 1;
  } while (lVar7 != 0xc);
  local_4c = local_3c;
  uStack_48 = local_44[0];
  if ((local_44[0] & 0xff) == 0x52) {
    uVar1 = 0;
    do {
      uVar6 = uVar1;
      if (uVar6 == 3) break;
      uVar1 = uVar6 + 1;
    } while (*(char *)(((ulong)&uStack_48 | 1) + uVar6) == "RIFF"[uVar6 + 1]);
    if ((uVar6 < 3) || ((local_3c & 0xff) != 0x57)) goto LAB_0000a840;
    lVar7 = 1;
    do {
      lVar5 = lVar7;
      if (lVar5 == 4) goto LAB_0000a838;
      lVar7 = lVar5 + 1;
    } while (*(char *)((long)&local_4c + lVar5) == "WAVE"[lVar5]);
    if (lVar5 - 1U < 3) goto LAB_0000a840;
LAB_0000a838:
    uVar8 = 1;
  }
  else {
LAB_0000a840:
    uVar8 = 0;
  }
  iVar2 = _fclose(pFVar4);
LAB_0000a854:
  if (*(long *)PTR____stack_chk_guard_00010040 == local_38) {
    return uVar8;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(iVar2);
}

// ==== 0000a888 __ZN19AudioObfuscatorImpl13compareStringEPKcS1_i ====
bool __ZN19AudioObfuscatorImpl13compareStringEPKcS1_i
               (undefined8 param_1,char *param_2,char *param_3,uint param_4)

{
  ulong uVar1;
  ulong uVar2;
  
  if ((int)param_4 < 1) {
    return true;
  }
  if (*param_2 != *param_3) {
    return false;
  }
  uVar1 = 1;
  do {
    uVar2 = uVar1;
    if (param_4 == uVar2) break;
    uVar1 = uVar2 + 1;
  } while (param_2[uVar2] == param_3[uVar2]);
  return param_4 <= uVar2;
}

// ==== 0000a8e4 __ZN19AudioObfuscatorImpl21findMoovAtomInM4AFileEP7__sFILE ====
long __ZN19AudioObfuscatorImpl21findMoovAtomInM4AFileEP7__sFILE(undefined8 param_1,FILE *param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  char local_48 [4];
  int local_44;
  
  lVar2 = 0;
  do {
    _fseeko(param_2,lVar2,0);
    local_44 = 0;
    lVar3 = 3;
    do {
      iVar1 = _fgetc(param_2);
      if (iVar1 == -1) break;
      *(char *)((long)&local_44 + lVar3) = (char)iVar1;
      lVar3 = lVar3 + -1;
    } while (lVar3 != -1);
    lVar3 = 0;
    local_48[0] = '\0';
    local_48[1] = '\0';
    local_48[2] = '\0';
    local_48[3] = '\0';
    do {
      iVar1 = _fgetc(param_2);
      if (iVar1 == -1) break;
      local_48[lVar3] = (char)iVar1;
      lVar3 = lVar3 + 1;
    } while (lVar3 != 4);
    lVar3 = 0;
    while (local_48[lVar3] == "moov"[lVar3]) {
      lVar3 = lVar3 + 1;
      if (lVar3 == 4) {
        return lVar2;
      }
    }
    lVar2 = lVar2 + local_44;
  } while( true );
}

// ==== 0000a9c0 __ZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURL ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Type propagation algorithm not settling */

undefined8
__ZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURL
          (undefined8 param_1,int param_2,undefined8 param_3)

{
  uint uVar1;
  char cVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  ID self;
  char *pcVar6;
  FILE *pFVar7;
  undefined8 *puVar8;
  undefined8 *******pppppppuVar9;
  long lVar10;
  undefined8 *******pppppppuVar11;
  ulong uVar12;
  long lVar13;
  undefined8 ******ppppppuVar14;
  undefined8 *******pppppppuVar15;
  undefined8 *******pppppppuVar16;
  long local_68;
  undefined8 local_60;
  undefined8 *******local_58;
  undefined8 *******local_50;
  long local_48;
  
  self = _objc_retainAutorelease(param_3);
  pcVar6 = (char *)objc_stub::fileSystemRepresentation(self);
  pFVar7 = _fopen(pcVar6,"r+");
  if (pFVar7 == (FILE *)0x0) {
    return 0;
  }
  local_50 = (undefined8 *******)0x0;
  local_48 = 0;
  pppppppuVar15 = &local_50;
  local_60._0_4_ = 0;
  local_58 = pppppppuVar15;
  puVar8 = (undefined8 *)
           __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                     (&local_58,&local_60);
  *puVar8 = "ftypukwn";
  local_60._0_4_ = 0xa5;
  puVar8 = (undefined8 *)
           __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                     (&local_58,&local_60);
  *puVar8 = "ftypmp42";
  local_60 = CONCAT44(local_60._4_4_,0x2d);
  puVar8 = (undefined8 *)
           __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                     (&local_58,&local_60);
  *puVar8 = "ftypM4A ";
  if (param_2 == 0) {
    _fseek(pFVar7,4,0);
    lVar13 = 0;
    do {
      iVar4 = _fgetc(pFVar7);
      *(byte *)((long)&local_60 + lVar13) = "7bWx5Q,K"[lVar13] ^ (byte)iVar4;
      lVar13 = lVar13 + 1;
    } while (lVar13 != 8);
    _fseek(pFVar7,0,0);
    iVar4 = _fgetc(pFVar7);
    pppppppuVar11 = local_50;
    if ((iVar4 == 0x2d) || (iVar4 == 0xa5)) {
      while (pppppppuVar16 = pppppppuVar15, pppppppuVar11 != (undefined8 *******)0x0) {
        while (pppppppuVar9 = pppppppuVar11, *(int *)(pppppppuVar9 + 4) <= iVar4) {
          if (iVar4 <= *(int *)(pppppppuVar9 + 4)) goto LAB_0000ad18;
          pppppppuVar11 = (undefined8 *******)pppppppuVar9[1];
          if ((undefined8 *******)pppppppuVar9[1] == (undefined8 *******)0x0) {
            pppppppuVar15 = pppppppuVar9 + 1;
            pppppppuVar16 = pppppppuVar9;
            goto LAB_0000abb0;
          }
        }
        pppppppuVar15 = pppppppuVar9;
        pppppppuVar11 = (undefined8 *******)*pppppppuVar9;
      }
LAB_0000abb0:
      pppppppuVar9 = (undefined8 *******)__Znwm(0x30);
      *(int *)(pppppppuVar9 + 4) = iVar4;
      pppppppuVar9[5] = (undefined8 ******)0x0;
      *pppppppuVar9 = (undefined8 ******)0x0;
      pppppppuVar9[1] = (undefined8 ******)0x0;
      pppppppuVar9[2] = pppppppuVar16;
      *pppppppuVar15 = pppppppuVar9;
      pppppppuVar11 = pppppppuVar9;
      if ((undefined8 *******)*local_58 != (undefined8 *******)0x0) {
        local_58 = (undefined8 *******)*local_58;
        pppppppuVar11 = (undefined8 *******)*pppppppuVar15;
      }
      __ZNSt3__127__tree_balance_after_insertB8ne190102IPNS_16__tree_node_baseIPvEEEEvT_S5_
                (local_50,pppppppuVar11);
      local_48 = local_48 + 1;
LAB_0000ad18:
      ppppppuVar14 = pppppppuVar9[5];
      _fseek(pFVar7,4,0);
      lVar13 = 0;
      do {
        _fputc((int)*(char *)((long)ppppppuVar14 + lVar13),pFVar7);
        lVar13 = lVar13 + 1;
      } while (lVar13 != 8);
      _fseek(pFVar7,0,0);
      _fputc(0,pFVar7);
      _fseeko(pFVar7,local_60 + 4,0);
      lVar13 = 0;
      do {
        _fputc((int)(char)(&DAT_0000c71b)[lVar13],pFVar7);
        lVar13 = lVar13 + 1;
      } while (lVar13 != 0xc);
    }
    goto LAB_0000ad9c;
  }
  _fseeko(pFVar7,4,0);
  lVar13 = 0;
  local_60 = 0;
  do {
    iVar4 = _fgetc(pFVar7);
    if (iVar4 == -1) break;
    *(char *)((long)&local_60 + lVar13) = (char)iVar4;
    lVar13 = lVar13 + 1;
  } while (lVar13 != 8);
  local_68._0_4_ = 0xa5;
  puVar8 = (undefined8 *)
           __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                     (&local_58,&local_68);
  cVar2 = (char)local_60;
  if ((char)local_60 == *(char *)*puVar8) {
    lVar13 = 1;
    do {
      lVar10 = lVar13;
      if (lVar10 == 8) goto LAB_0000ab08;
      lVar13 = lVar10 + 1;
    } while (*(char *)((long)&local_60 + lVar10) == ((char *)*puVar8)[lVar10]);
    if (lVar10 - 1U < 7) goto LAB_0000ac00;
LAB_0000ab08:
    iVar4 = 0xa5;
  }
  else {
LAB_0000ac00:
    local_68._0_4_ = 0x2d;
    puVar8 = (undefined8 *)
             __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                       (&local_58,&local_68);
    if (cVar2 == *(char *)*puVar8) {
      uVar3 = 0;
      do {
        uVar12 = uVar3;
        if (uVar12 == 7) break;
        uVar3 = uVar12 + 1;
      } while (*(char *)(((ulong)&local_60 | 1) + uVar12) == ((char *)*puVar8)[uVar12 + 1]);
      iVar4 = 0x2d;
      if (uVar12 < 7) {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 0;
    }
  }
  lVar10 = __ZN19AudioObfuscatorImpl21findMoovAtomInM4AFileEP7__sFILE(puVar8,pFVar7);
  local_68 = lVar10;
  _fseek(pFVar7,0,0);
  _fputc(iVar4,pFVar7);
  _fseeko(pFVar7,4,0);
  lVar13 = 0;
  do {
    _fputc((int)(char)("7bWx5Q,K"[lVar13] ^ *(byte *)((long)&local_68 + lVar13)),pFVar7);
    lVar13 = lVar13 + 1;
  } while (lVar13 != 8);
  _fseeko(pFVar7,lVar10 + 4,0);
  iVar4 = 0xc;
  do {
    uVar5 = _rand();
    uVar1 = uVar5 & 0xff;
    if (-1 < (int)-uVar5) {
      uVar1 = -(-uVar5 & 0xff);
    }
    _fputc(uVar1,pFVar7);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
LAB_0000ad9c:
  _fclose(pFVar7);
  __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE
            (local_50);
  return 0;
}

// ==== 0000ae0c __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_ ====
long * __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_
                 (long param_1,int *param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  long *plVar4;
  long *plVar5;
  
  plVar3 = *(long **)(param_1 + 8);
  iVar1 = *param_2;
  plVar4 = (long *)(param_1 + 8);
  do {
    plVar5 = plVar4;
    if (plVar3 == (long *)0x0) {
LAB_0000ae70:
      plVar2 = (long *)__Znwm(0x30);
      *(int *)(plVar2 + 4) = iVar1;
      plVar2[5] = 0;
      __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE16__insert_node_atEPNS_15__tree_end_nodeIPNS_16__tree_node_baseIPvEEEERSK_SK_
                (param_1,plVar4,plVar5,plVar2);
LAB_0000ae9c:
      return plVar2 + 5;
    }
    while (plVar2 = plVar3, plVar4 = plVar2, (int)plVar2[4] <= iVar1) {
      if (iVar1 <= (int)plVar2[4]) goto LAB_0000ae9c;
      plVar3 = (long *)plVar2[1];
      if ((long *)plVar2[1] == (long *)0x0) {
        plVar5 = plVar2 + 1;
        goto LAB_0000ae70;
      }
    }
    plVar3 = (long *)*plVar2;
  } while( true );
}

// ==== 0000aeb4 __ZN19AudioObfuscatorImpl21obfuscateWAVFileAtURLEbP5NSURL ====
void __ZN19AudioObfuscatorImpl21obfuscateWAVFileAtURLEbP5NSURL
               (undefined8 param_1,int param_2,undefined8 param_3)

{
  ulong uVar1;
  int iVar2;
  ID self;
  char *pcVar3;
  FILE *pFVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined4 local_68;
  uint uStack_64;
  uint local_60 [10];
  long local_38;
  
  local_38 = *(long *)PTR____stack_chk_guard_00010040;
  self = _objc_retainAutorelease(param_3);
  pcVar3 = (char *)objc_stub::fileSystemRepresentation(self);
  pFVar4 = _fopen(pcVar3,"r+");
  iVar2 = 0;
  if (pFVar4 != (FILE *)0x0) {
    _fseek(pFVar4,0,0);
    local_60[8] = 0;
    local_60[9] = 0;
    local_60[2] = 0;
    local_60[3] = 0;
    local_60[0] = 0;
    local_60[1] = 0;
    local_60[6] = 0;
    local_60[7] = 0;
    local_60[4] = 0;
    local_60[5] = 0;
    if (param_2 == 0) {
      _fseek(pFVar4,0,0);
      lVar7 = 0;
      do {
        iVar2 = _fgetc(pFVar4);
        *(byte *)((long)local_60 + lVar7) = *(byte *)(_wavKey + lVar7) ^ (byte)iVar2;
        lVar7 = lVar7 + 1;
      } while (lVar7 != 0x28);
      local_68 = local_60[2];
      uStack_64 = local_60[0];
      if ((local_60[0] & 0xff) == 0x52) {
        uVar1 = 0;
        do {
          uVar6 = uVar1;
          if (uVar6 == 3) break;
          uVar1 = uVar6 + 1;
        } while (*(char *)(((ulong)&uStack_64 | 1) + uVar6) == "RIFF"[uVar6 + 1]);
        if ((2 < uVar6) && ((local_60[2] & 0xff) == 0x57)) {
          lVar7 = 1;
          do {
            lVar5 = lVar7;
            if (lVar5 == 4) goto LAB_0000b100;
            lVar7 = lVar5 + 1;
          } while (*(char *)((long)&local_68 + lVar5) == "WAVE"[lVar5]);
          if (2 < lVar5 - 1U) {
LAB_0000b100:
            _fseek(pFVar4,0,0);
            lVar7 = 0;
            do {
              _fputc((int)*(char *)((long)local_60 + lVar7),pFVar4);
              lVar7 = lVar7 + 1;
            } while (lVar7 != 0x28);
          }
        }
      }
    }
    else {
      lVar7 = 0;
      do {
        iVar2 = _fgetc(pFVar4);
        if (iVar2 == -1) break;
        *(char *)((long)local_60 + lVar7) = (char)iVar2;
        lVar7 = lVar7 + 1;
      } while (lVar7 != 0x28);
      local_68 = local_60[2];
      uStack_64 = local_60[0];
      if ((local_60[0] & 0xff) == 0x52) {
        uVar1 = 0;
        do {
          uVar6 = uVar1;
          if (uVar6 == 3) break;
          uVar1 = uVar6 + 1;
        } while (*(char *)(((ulong)&uStack_64 | 1) + uVar6) == "RIFF"[uVar6 + 1]);
        if ((2 < uVar6) && ((local_60[2] & 0xff) == 0x57)) {
          lVar7 = 1;
          do {
            lVar5 = lVar7;
            if (lVar5 == 4) goto LAB_0000afdc;
            lVar7 = lVar5 + 1;
          } while (*(char *)((long)&local_68 + lVar5) == "WAVE"[lVar5]);
          if (2 < lVar5 - 1U) {
LAB_0000afdc:
            _fseek(pFVar4,0,0);
            lVar7 = 0;
            do {
              _fputc((int)(char)(*(byte *)(_wavKey + lVar7) ^ *(byte *)((long)local_60 + lVar7)),
                     pFVar4);
              lVar7 = lVar7 + 1;
            } while (lVar7 != 0x28);
          }
        }
      }
    }
    iVar2 = _fclose(pFVar4);
  }
  if (*(long *)PTR____stack_chk_guard_00010040 != local_38) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(iVar2);
  }
  return;
}

// ==== 0000b168 __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE ====
void __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE
               (undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE
              (*param_1);
    __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE
              (param_1[1]);
    __ZdlPv(param_1);
    return;
  }
  return;
}

// ==== 0000b1a0 __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE16__insert_node_atEPNS_15__tree_end_nodeIPNS_16__tree_node_baseIPvEEEERSK_SK_ ====
void __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE16__insert_node_atEPNS_15__tree_end_nodeIPNS_16__tree_node_baseIPvEEEERSK_SK_
               (long *param_1,undefined8 param_2,undefined8 *param_3,undefined8 *param_4)

{
  *param_4 = 0;
  param_4[1] = 0;
  param_4[2] = param_2;
  *param_3 = param_4;
  if (*(long *)*param_1 != 0) {
    *param_1 = *(long *)*param_1;
    param_4 = (undefined8 *)*param_3;
  }
  __ZNSt3__127__tree_balance_after_insertB8ne190102IPNS_16__tree_node_baseIPvEEEEvT_S5_
            (param_1[1],param_4);
  param_1[2] = param_1[2] + 1;
  return;
}

// ==== 0000b1f4 __ZNSt3__127__tree_balance_after_insertB8ne190102IPNS_16__tree_node_baseIPvEEEEvT_S5_ ====
void __ZNSt3__127__tree_balance_after_insertB8ne190102IPNS_16__tree_node_baseIPvEEEEvT_S5_
               (long *param_1,long *param_2)

{
  bool bVar1;
  long *plVar2;
  long *plVar3;
  long *plVar4;
  long lVar5;
  undefined8 *puVar6;
  long *plVar7;
  
  bVar1 = param_2 == param_1;
  *(bool *)(param_2 + 3) = bVar1;
  do {
    if ((bVar1) || (plVar3 = (long *)param_2[2], (*(byte *)(plVar3 + 3) & 1) != 0)) {
      return;
    }
    plVar2 = (long *)plVar3[2];
    plVar4 = (long *)*plVar2;
    if (plVar4 == plVar3) {
      if ((plVar2[1] == 0) || (plVar7 = (long *)(plVar2[1] + 0x18), *(char *)plVar7 == '\x01')) {
        if ((long *)*plVar3 != param_2) {
          plVar7 = (long *)plVar3[1];
          lVar5 = *plVar7;
          plVar3[1] = lVar5;
          plVar4 = plVar3;
          if (lVar5 != 0) {
            *(long **)(lVar5 + 0x10) = plVar3;
            plVar2 = (long *)plVar3[2];
            plVar4 = (long *)*plVar2;
          }
          plVar7[2] = (long)plVar2;
          plVar2[plVar4 != plVar3] = (long)plVar7;
          *plVar7 = (long)plVar3;
          plVar3[2] = (long)plVar7;
          plVar2 = (long *)plVar7[2];
          plVar4 = (long *)*plVar2;
          plVar3 = plVar7;
        }
        *(undefined1 *)(plVar3 + 3) = 1;
        *(undefined1 *)(plVar2 + 3) = 0;
        lVar5 = plVar4[1];
        *plVar2 = lVar5;
        if (lVar5 != 0) {
          *(long **)(lVar5 + 0x10) = plVar2;
        }
        puVar6 = (undefined8 *)plVar2[2];
        plVar4[2] = (long)puVar6;
        puVar6[(long *)*puVar6 != plVar2] = plVar4;
        plVar4[1] = (long)plVar2;
        plVar2[2] = (long)plVar4;
        return;
      }
    }
    else if ((plVar4 == (long *)0x0) || (plVar7 = plVar4 + 3, (char)*plVar7 == '\x01')) {
      plVar4 = (long *)*plVar3;
      if (plVar4 == param_2) {
        lVar5 = plVar4[1];
        *plVar3 = lVar5;
        if (lVar5 != 0) {
          *(long **)(lVar5 + 0x10) = plVar3;
          plVar2 = (long *)plVar3[2];
        }
        plVar4[2] = (long)plVar2;
        plVar2[(long *)*plVar2 != plVar3] = (long)plVar4;
        plVar4[1] = (long)plVar3;
        plVar3[2] = (long)plVar4;
        plVar2 = (long *)plVar4[2];
        plVar3 = plVar4;
      }
      *(undefined1 *)(plVar3 + 3) = 1;
      *(undefined1 *)(plVar2 + 3) = 0;
      plVar3 = (long *)plVar2[1];
      lVar5 = *plVar3;
      plVar2[1] = lVar5;
      if (lVar5 != 0) {
        *(long **)(lVar5 + 0x10) = plVar2;
      }
      puVar6 = (undefined8 *)plVar2[2];
      plVar3[2] = (long)puVar6;
      puVar6[(long *)*puVar6 != plVar2] = plVar3;
      *plVar3 = (long)plVar2;
      plVar2[2] = (long)plVar3;
      return;
    }
    *(undefined1 *)(plVar3 + 3) = 1;
    bVar1 = plVar2 == param_1;
    *(bool *)(plVar2 + 3) = bVar1;
    *(char *)plVar7 = '\x01';
    param_2 = plVar2;
  } while( true );
}

// ==== 0000b390 __ZN9DSPKernel14handleOneEventEPK13AURenderEvent ====
void __ZN9DSPKernel14handleOneEventEPK13AURenderEvent(long *param_1,long param_2)

{
  if (*(byte *)(param_2 + 0x10) - 1 < 2) {
                    /* WARNING: Could not recover jumptable at 0x0000b3b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))
              (*(undefined4 *)(param_2 + 0x20),param_1,*(undefined8 *)(param_2 + 0x18),
               *(undefined4 *)(param_2 + 0x14));
    return;
  }
  if (*(byte *)(param_2 + 0x10) == 8) {
                    /* WARNING: Could not recover jumptable at 0x0000b3cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x10))();
    return;
  }
  return;
}

// ==== 0000b3d4 __ZN9DSPKernel28performAllSimultaneousEventsExRPK13AURenderEvent ====
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

// ==== 0000b428 __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent ====
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
                    /* WARNING: Could not recover jumptable at 0x0000b500. Too many branches */
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

// ==== 0000b504 __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp.cold.1 ====
void __ZN35BufferedFilePlaybackDSPKernelMaster7processEjjPK14AudioTimeStamp_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferConsume","TPCircularBuffer.h",0xa1,"buffer->fillCount >= 0");
}

// ==== 0000b52c ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke.cold.1 ====
void ____ZN29BufferedFilePlaybackDSPKernel28processBufferFollowerActionsENSt3__15dequeI20BufferFollowerActionNS0_9allocatorIS2_EEEE_block_invoke_cold_1
               (void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferProduce","TPCircularBuffer.h",0xc5,
                "buffer->fillCount <= buffer->length");
}

// ==== 0000b554 _ExtAudioFileDispose ====
void _ExtAudioFileDispose(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b55c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileDispose_00010d30)();
  return;
}

// ==== 0000b560 _ExtAudioFileGetProperty ====
void _ExtAudioFileGetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b568. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileGetProperty_00010d38)();
  return;
}

// ==== 0000b56c _ExtAudioFileOpenURL ====
void _ExtAudioFileOpenURL(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b574. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileOpenURL_00010d40)();
  return;
}

// ==== 0000b578 _ExtAudioFileRead ====
void _ExtAudioFileRead(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b580. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileRead_00010d48)();
  return;
}

// ==== 0000b584 _ExtAudioFileSeek ====
void _ExtAudioFileSeek(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b58c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSeek_00010d50)();
  return;
}

// ==== 0000b590 _ExtAudioFileSetProperty ====
void _ExtAudioFileSetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b598. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSetProperty_00010d58)();
  return;
}

// ==== 0000b59c _NSLog ====
void _NSLog(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__NSLog_00010d60)();
  return;
}

// ==== 0000b5a8 _TPCircularBufferCleanup ====
void _TPCircularBufferCleanup(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__TPCircularBufferCleanup_00010d68)();
  return;
}

// ==== 0000b5b4 _TPCircularBufferClear ====
void _TPCircularBufferClear(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__TPCircularBufferClear_00010d70)();
  return;
}

// ==== 0000b5c0 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_00010d78)(param_1,param_2,param_3);
  return;
}

// ==== 0000b5cc __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_00010d80)(param_1,param_2);
  return;
}

// ==== 0000b5d8 __TPCircularBufferInit ====
void __TPCircularBufferInit(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___TPCircularBufferInit_00010d88)();
  return;
}

// ==== 0000b5e4 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_00010d90)();
  return;
}

// ==== 0000b5f0 __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b5f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_00010d98)();
  return;
}

// ==== 0000b5fc __ZNSt20bad_array_new_lengthC1Ev ====
void __ZNSt20bad_array_new_lengthC1Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b604. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt20bad_array_new_lengthC1Ev_00010da0)();
  return;
}

// ==== 0000b608 __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b610. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_00010da8)();
  return;
}

// ==== 0000b614 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b61c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_00010db0)();
  return;
}

// ==== 0000b620 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_00010058)();
  return;
}

// ==== 0000b62c __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b634. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_00010060)();
  return;
}

// ==== 0000b638 ___assert_rtn ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ___assert_rtn(char *param_1,char *param_2,int param_3,char *param_4)

{
                    /* WARNING: Could not recover jumptable at 0x0000b640. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____assert_rtn_00010db8)(param_1,param_2,param_3);
  return;
}

// ==== 0000b644 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b64c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_00010dc0)();
  return;
}

// ==== 0000b650 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b658. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_00010dc8)();
  return;
}

// ==== 0000b65c ___cxa_end_catch ====
void ___cxa_end_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b664. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_end_catch_00010dd0)();
  return;
}

// ==== 0000b668 ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b670. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_00010dd8)();
  return;
}

// ==== 0000b674 ___cxa_rethrow ====
void ___cxa_rethrow(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b67c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_rethrow_00010de0)();
  return;
}

// ==== 0000b680 ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b688. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_00010de8)();
  return;
}

// ==== 0000b68c ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b694. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_00010df0)();
  return;
}

// ==== 0000b698 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0000b6a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_00010df8)();
  return;
}

// ==== 0000b6a4 _dispatch_async ====
void _dispatch_async(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b6ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_async_00010e00)();
  return;
}

// ==== 0000b6b0 _dispatch_queue_create ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

dispatch_queue_t _dispatch_queue_create(char *label,dispatch_queue_attr_t attr)

{
  dispatch_queue_t pdVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b6b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pdVar1 = (dispatch_queue_t)(*(code *)PTR__dispatch_queue_create_00010e08)();
  return pdVar1;
}

// ==== 0000b6bc _dispatch_sync ====
void _dispatch_sync(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b6c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_sync_00010e10)();
  return;
}

// ==== 0000b6c8 _fclose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fclose(FILE *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b6d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fclose_00010e18)((int)param_1);
  return iVar1;
}

// ==== 0000b6d4 _fgetc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fgetc(FILE *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b6dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fgetc_00010e20)((int)param_1);
  return iVar1;
}

// ==== 0000b6e0 _fopen ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * _fopen(char *param_1,char *param_2)

{
  FILE *pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b6e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = (FILE *)(*(code *)PTR__fopen_00010e28)();
  return pFVar1;
}

// ==== 0000b6ec _fputc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fputc(int param_1,FILE *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b6f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fputc_00010e30)(param_1);
  return iVar1;
}

// ==== 0000b6f8 _fseek ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fseek(FILE *param_1,long param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b700. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fseek_00010e38)((int)param_1,param_2,param_3);
  return iVar1;
}

// ==== 0000b704 _fseeko ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fseeko(FILE *param_1,off_t param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b70c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fseeko_00010e40)((int)param_1,param_2,param_3);
  return iVar1;
}

// ==== 0000b710 _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b718. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_00010e48)();
  return pvVar1;
}

// ==== 0000b71c _memmove ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memmove(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b724. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memmove_00010e50)();
  return pvVar1;
}

// ==== 0000b728 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b730. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_00010e58)();
  return;
}

// ==== 0000b734 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b73c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_00010e60)();
  return;
}

// ==== 0000b740 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b748. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_00010e68)();
  return;
}

// ==== 0000b74c _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b754. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_00010e70)();
  return;
}

// ==== 0000b758 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b760. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_00010e78)();
  return;
}

// ==== 0000b764 _objc_enumerationMutation ====
void _objc_enumerationMutation(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b76c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_enumerationMutation_00010e80)();
  return;
}

// ==== 0000b770 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b778. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_00010e88)();
  return;
}

// ==== 0000b77c _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b784. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_00010e90)();
  return;
}

// ==== 0000b788 _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b790. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_00010e98)();
  return;
}

// ==== 0000b794 _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b79c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_00010ea0)();
  return;
}

// ==== 0000b7a0 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b7a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_00010ea8)();
  return IVar1;
}

// ==== 0000b7ac _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_00010eb0)();
  return;
}

// ==== 0000b7b8 _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_00010eb8)();
  return;
}

// ==== 0000b7c4 _objc_retainAutorelease ====
void _objc_retainAutorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutorelease_00010ec0)();
  return;
}

// ==== 0000b7d0 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_00010ec8)();
  return;
}

// ==== 0000b7dc _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_00010ed0)();
  return;
}

// ==== 0000b7e8 _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_00010ed8)();
  return;
}

// ==== 0000b7f4 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b7fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_00010ee0)();
  return;
}

// ==== 0000b800 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b808. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_00010ee8)();
  return;
}

// ==== 0000b80c _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000b814. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_00010ef0)();
  return;
}

// ==== 0000b818 _rand ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _rand(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b820. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__rand_00010ef8)();
  return iVar1;
}

// ==== 0000b824 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000b82c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_00010f00)((int)param_1);
  return iVar1;
}

// ==== 0000bb20 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"address");
  return IVar1;
}

// ==== 0000bb40 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 0000bb60 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"auOutputBus");
  return IVar1;
}

// ==== 0000bb80 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"audioBufferList");
  return IVar1;
}

// ==== 0000bba0 objc_stub::bufferedFilePlaybackAudioUnitDSPKernelErrorStatus:operation:fileURL: ====
ID __objc_msgSend_stub
objc_stub::bufferedFilePlaybackAudioUnitDSPKernelErrorStatus_operation_fileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)
                    (self,"bufferedFilePlaybackAudioUnitDSPKernelErrorStatus:operation:fileURL:");
  return IVar1;
}

// ==== 0000bbc0 objc_stub::bufferedFilePlaybackAudioUnitDidUpdateCurrentTime: ====
ID __objc_msgSend_stub objc_stub::bufferedFilePlaybackAudioUnitDidUpdateCurrentTime_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)
                    (self,"bufferedFilePlaybackAudioUnitDidUpdateCurrentTime:");
  return IVar1;
}

// ==== 0000bbe0 objc_stub::bufferedFilePlaybackAudioUnitReachedSongEnd ====
ID __objc_msgSend_stub objc_stub::bufferedFilePlaybackAudioUnitReachedSongEnd(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"bufferedFilePlaybackAudioUnitReachedSongEnd");
  return IVar1;
}

// ==== 0000bc00 objc_stub::bufferedFilePlaybackAudioUnitStartPlayingEnqueuedSection ====
ID __objc_msgSend_stub
objc_stub::bufferedFilePlaybackAudioUnitStartPlayingEnqueuedSection(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)
                    (self,"bufferedFilePlaybackAudioUnitStartPlayingEnqueuedSection");
  return IVar1;
}

// ==== 0000bc20 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"channelCount");
  return IVar1;
}

// ==== 0000bc40 objc_stub::countByEnumeratingWithState:objects:count: ====
ID __objc_msgSend_stub objc_stub::countByEnumeratingWithState_objects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"countByEnumeratingWithState:objects:count:");
  return IVar1;
}

// ==== 0000bc60 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
ID __objc_msgSend_stub
objc_stub::
createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
          (ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)
                    (self,
                     "createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters:"
                    );
  return IVar1;
}

// ==== 0000bc80 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 0000bca0 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"defaultFormat");
  return IVar1;
}

// ==== 0000bcc0 objc_stub::defaultManager ====
ID __objc_msgSend_stub objc_stub::defaultManager(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"defaultManager");
  return IVar1;
}

// ==== 0000bce0 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"delegate");
  return IVar1;
}

// ==== 0000bd00 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 0000bd20 objc_stub::fileExistsAtPath: ====
ID __objc_msgSend_stub objc_stub::fileExistsAtPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"fileExistsAtPath:");
  return IVar1;
}

// ==== 0000bd40 objc_stub::fileSystemRepresentation ====
ID __objc_msgSend_stub objc_stub::fileSystemRepresentation(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"fileSystemRepresentation");
  return IVar1;
}

// ==== 0000bd60 objc_stub::fileURLWithPath: ====
ID __objc_msgSend_stub objc_stub::fileURLWithPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"fileURLWithPath:");
  return IVar1;
}

// ==== 0000bd80 objc_stub::floatValue ====
ID __objc_msgSend_stub objc_stub::floatValue(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"floatValue");
  return IVar1;
}

// ==== 0000bda0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"format");
  return IVar1;
}

// ==== 0000bdc0 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 0000bde0 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 0000be00 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 0000be20 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 0000be40 objc_stub::isMaster ====
ID __objc_msgSend_stub objc_stub::isMaster(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"isMaster");
  return IVar1;
}

// ==== 0000be60 objc_stub::isReadableFileAtPath: ====
ID __objc_msgSend_stub objc_stub::isReadableFileAtPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"isReadableFileAtPath:");
  return IVar1;
}

// ==== 0000be80 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 0000bea0 objc_stub::moveItemAtURL:toURL:error: ====
ID __objc_msgSend_stub objc_stub::moveItemAtURL_toURL_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"moveItemAtURL:toURL:error:");
  return IVar1;
}

// ==== 0000bec0 objc_stub::mtDSPKernelAsVoid ====
ID __objc_msgSend_stub objc_stub::mtDSPKernelAsVoid(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"mtDSPKernelAsVoid");
  return IVar1;
}

// ==== 0000bee0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 0000bf00 objc_stub::objectAtIndexedSubscript: ====
ID __objc_msgSend_stub objc_stub::objectAtIndexedSubscript_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"objectAtIndexedSubscript:");
  return IVar1;
}

// ==== 0000bf20 objc_stub::path ====
ID __objc_msgSend_stub objc_stub::path(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"path");
  return IVar1;
}

// ==== 0000bf40 objc_stub::pathExtension ====
ID __objc_msgSend_stub objc_stub::pathExtension(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"pathExtension");
  return IVar1;
}

// ==== 0000bf60 objc_stub::removeItemAtPath:error: ====
ID __objc_msgSend_stub objc_stub::removeItemAtPath_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"removeItemAtPath:error:");
  return IVar1;
}

// ==== 0000bf80 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"reset");
  return IVar1;
}

// ==== 0000bfa0 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"sampleRate");
  return IVar1;
}

// ==== 0000bfc0 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 0000bfe0 objc_stub::setDelegate: ====
ID __objc_msgSend_stub objc_stub::setDelegate_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setDelegate:");
  return IVar1;
}

// ==== 0000c000 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 0000c020 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 0000c040 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 0000c060 objc_stub::setIsMaster: ====
ID __objc_msgSend_stub objc_stub::setIsMaster_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setIsMaster:");
  return IVar1;
}

// ==== 0000c080 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 0000c0a0 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 0000c0c0 objc_stub::setUrl: ====
ID __objc_msgSend_stub objc_stub::setUrl_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setUrl:");
  return IVar1;
}

// ==== 0000c0e0 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"setValue:");
  return IVar1;
}

// ==== 0000c100 objc_stub::stringByReplacingOccurrencesOfString:withString: ====
ID __objc_msgSend_stub objc_stub::stringByReplacingOccurrencesOfString_withString_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)
                    (self,"stringByReplacingOccurrencesOfString:withString:");
  return IVar1;
}

// ==== 0000c120 objc_stub::stringWithFormat: ====
ID __objc_msgSend_stub objc_stub::stringWithFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"stringWithFormat:");
  return IVar1;
}

// ==== 0000c140 objc_stub::url ====
ID __objc_msgSend_stub objc_stub::url(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"url");
  return IVar1;
}

// ==== 0000c160 objc_stub::value ====
ID __objc_msgSend_stub objc_stub::value(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_00010008)(self,"value");
  return IVar1;
}

// ==== 00024101 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024201 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024301 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024302 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024303 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024401 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024501 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024601 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024701 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024801 NSFileManager::defaultManager ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::defaultManager(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024802 NSFileManager::fileExistsAtPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::fileExistsAtPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024803 NSFileManager::isReadableFileAtPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::isReadableFileAtPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024804 NSFileManager::removeItemAtPath:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::removeItemAtPath_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024805 NSFileManager::moveItemAtURL:toURL:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::moveItemAtURL_toURL_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024a01 NSString::stringWithFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSString::stringWithFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024b01 NSURL::fileURLWithPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSURL::fileURLWithPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c01 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c02 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c03 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c04 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c05 TrackedAUAudioUnit::setIsMaster: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setIsMaster_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c06 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c07 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00024c08 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 00025e00 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

