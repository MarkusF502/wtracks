// LoopingFilePlaybackAUFramework sha256 70854b549062f9ce7e30f5e51ea2cd25144cc2410eb1435adf08532b3e08cb0f (Ghidra 12.1.4, all decompiled functions)

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

// ==== 00004174 __ZN19AudioObfuscatorImplC2Ev ====
void __ZN19AudioObfuscatorImplC2Ev(void)

{
  return;
}

// ==== 00004178 __ZN19AudioObfuscatorImplC1Ev ====
void __ZN19AudioObfuscatorImplC1Ev(void)

{
  return;
}

// ==== 0000417c __ZN19AudioObfuscatorImplD2Ev ====
void __ZN19AudioObfuscatorImplD2Ev(void)

{
  return;
}

// ==== 00004180 __ZN19AudioObfuscatorImplD1Ev ====
void __ZN19AudioObfuscatorImplD1Ev(void)

{
  return;
}

// ==== 00004184 __ZN19AudioObfuscatorImpl27obfuscateAllAudioFilesAtURLEP5NSURL ====
undefined8 __ZN19AudioObfuscatorImpl27obfuscateAllAudioFilesAtURLEP5NSURL(void)

{
  return 1;
}

// ==== 0000418c __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE ====
void __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE
               (undefined8 param_1,undefined8 param_2,long param_3)

{
                    /* WARNING: Could not recover jumptable at 0x00004194. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_3 + 0x10))(param_3);
  return;
}

// ==== 00004198 __ZN19AudioObfuscatorImpl22obfuscateFileExtensionEP5NSURL ====
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

// ==== 00004408 __ZN19AudioObfuscatorImpl23obfuscatedFileIsWavFileEP5NSURL ====
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
  
  local_38 = *(long *)PTR____stack_chk_guard_0000c040;
  self = _objc_retainAutorelease(param_2);
  pcVar3 = (char *)objc_stub::fileSystemRepresentation(self);
  pFVar4 = _fopen(pcVar3,"r+");
  if (pFVar4 == (FILE *)0x0) {
    uVar8 = 0;
    iVar2 = 0;
    goto LAB_00004550;
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
    if ((uVar6 < 3) || ((local_3c & 0xff) != 0x57)) goto LAB_0000453c;
    lVar7 = 1;
    do {
      lVar5 = lVar7;
      if (lVar5 == 4) goto LAB_00004534;
      lVar7 = lVar5 + 1;
    } while (*(char *)((long)&local_4c + lVar5) == "WAVE"[lVar5]);
    if (lVar5 - 1U < 3) goto LAB_0000453c;
LAB_00004534:
    uVar8 = 1;
  }
  else {
LAB_0000453c:
    uVar8 = 0;
  }
  iVar2 = _fclose(pFVar4);
LAB_00004550:
  if (*(long *)PTR____stack_chk_guard_0000c040 == local_38) {
    return uVar8;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(iVar2);
}

// ==== 00004584 __ZN19AudioObfuscatorImpl13compareStringEPKcS1_i ====
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

// ==== 000045e0 __ZN19AudioObfuscatorImpl21findMoovAtomInM4AFileEP7__sFILE ====
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

// ==== 000046bc __ZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURL ====
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
          if (iVar4 <= *(int *)(pppppppuVar9 + 4)) goto LAB_00004a14;
          pppppppuVar11 = (undefined8 *******)pppppppuVar9[1];
          if ((undefined8 *******)pppppppuVar9[1] == (undefined8 *******)0x0) {
            pppppppuVar15 = pppppppuVar9 + 1;
            pppppppuVar16 = pppppppuVar9;
            goto LAB_000048ac;
          }
        }
        pppppppuVar15 = pppppppuVar9;
        pppppppuVar11 = (undefined8 *******)*pppppppuVar9;
      }
LAB_000048ac:
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
LAB_00004a14:
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
        _fputc((int)(char)(&DAT_00007fb0)[lVar13],pFVar7);
        lVar13 = lVar13 + 1;
      } while (lVar13 != 0xc);
    }
    goto LAB_00004a98;
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
      if (lVar10 == 8) goto LAB_00004804;
      lVar13 = lVar10 + 1;
    } while (*(char *)((long)&local_60 + lVar10) == ((char *)*puVar8)[lVar10]);
    if (lVar10 - 1U < 7) goto LAB_000048fc;
LAB_00004804:
    iVar4 = 0xa5;
  }
  else {
LAB_000048fc:
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
LAB_00004a98:
  _fclose(pFVar7);
  __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE
            (local_50);
  return 0;
}

// ==== 00004b08 __ZNSt3__13mapIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcNS_4lessIS4_EENS_9allocatorINS_4pairIKS4_S6_EEEEEixEOS4_ ====
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
LAB_00004b6c:
      plVar2 = (long *)__Znwm(0x30);
      *(int *)(plVar2 + 4) = iVar1;
      plVar2[5] = 0;
      __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE16__insert_node_atEPNS_15__tree_end_nodeIPNS_16__tree_node_baseIPvEEEERSK_SK_
                (param_1,plVar4,plVar5,plVar2);
LAB_00004b98:
      return plVar2 + 5;
    }
    while (plVar2 = plVar3, plVar4 = plVar2, (int)plVar2[4] <= iVar1) {
      if (iVar1 <= (int)plVar2[4]) goto LAB_00004b98;
      plVar3 = (long *)plVar2[1];
      if ((long *)plVar2[1] == (long *)0x0) {
        plVar5 = plVar2 + 1;
        goto LAB_00004b6c;
      }
    }
    plVar3 = (long *)*plVar2;
  } while( true );
}

// ==== 00004bb0 __ZN19AudioObfuscatorImpl21obfuscateWAVFileAtURLEbP5NSURL ====
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
  
  local_38 = *(long *)PTR____stack_chk_guard_0000c040;
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
            if (lVar5 == 4) goto LAB_00004dfc;
            lVar7 = lVar5 + 1;
          } while (*(char *)((long)&local_68 + lVar5) == "WAVE"[lVar5]);
          if (2 < lVar5 - 1U) {
LAB_00004dfc:
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
            if (lVar5 == 4) goto LAB_00004cd8;
            lVar7 = lVar5 + 1;
          } while (*(char *)((long)&local_68 + lVar5) == "WAVE"[lVar5]);
          if (2 < lVar5 - 1U) {
LAB_00004cd8:
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
  if (*(long *)PTR____stack_chk_guard_0000c040 != local_38) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(iVar2);
  }
  return;
}

// ==== 00004e64 __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE7destroyEPNS_11__tree_nodeIS8_PvEE ====
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

// ==== 00004e9c __ZNSt3__16__treeINS_12__value_typeIZN19AudioObfuscatorImpl21obfuscateM4AFileAtURLEbP5NSURLE4FtypPKcEENS_19__map_value_compareIS5_S8_NS_4lessIS5_EELb1EEENS_9allocatorIS8_EEE16__insert_node_atEPNS_15__tree_end_nodeIPNS_16__tree_node_baseIPvEEEERSK_SK_ ====
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

// ==== 00004ef0 __ZNSt3__127__tree_balance_after_insertB8ne190102IPNS_16__tree_node_baseIPvEEEEvT_S5_ ====
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

// ==== 0000508c LoopingFilePlaybackAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x30 bytes */

ID LoopingFilePlaybackAudioUnit::initWithComponentDescription_options_error_
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
  long local_98;
  ID local_90;
  class_t *pcStack_88;
  ID local_80;
  ID IStack_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_0000c040;
  puStack_a8 = *(undefined8 **)&param_3->field2_0x8;
  local_b0._0_4_ = param_3->field0_0x0;
  local_b0._4_4_ = param_3->field1_0x4;
  local_a0 = CONCAT44(local_a0._4_4_,param_3->field4_0x10);
  pcStack_88 = &objc::class_t::LoopingFilePlaybackAudioUnit;
  local_90 = param_1;
  self = TrackedAUAudioUnit::initWithComponentDescription_options_error_
                   ((ID)&local_90,"initWithComponentDescription:options:error:",&local_b0,
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
    local_70 = *(undefined8 *)(self + lVar5);
    IVar3 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_70,1);
    IVar2 = AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(IVar2,self,2,IVar3);
    uVar4 = *(undefined8 *)(self + (long)_auOutputBusArray);
    *(ID *)(self + (long)_auOutputBusArray) = IVar2;
    TrackedAUAudioUnit::setMaximumFramesToRender_(self,uVar4,0x200);
    IVar2 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_isPlayingParameter,
                       &cf_isPlaying,0,2,0,0,0,0);
    IVar3 = AUParameterTree::
            createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
                      ((ID)&_OBJC_CLASS___AUParameterTree,0,0x3f800000,&cf_mutedParameter,&cf_muted,
                       1,2,0,0,0,0);
    AUParameterTree::setValue_(IVar2,0);
    AUParameterTree::setValue_(IVar3,0);
    local_80 = IVar2;
    IStack_78 = IVar3;
    IVar2 = NSArray::arrayWithObjects_count_((ID)&_OBJC_CLASS___NSArray,&local_80,2);
    IVar2 = AUParameterTree::createTreeWithChildren_((ID)&_OBJC_CLASS___AUParameterTree,IVar2);
    lVar6 = (long)_parameterTree;
    *(ID *)(self + lVar6) = IVar2;
    lVar5 = (long)_dspKernel;
    local_98 = *(long *)(self + lVar5);
    if (local_98 == 0) {
      __Znwm(0x110);
      local_98 = __ZN28LoopingFilePlaybackDSPKernelC2Ev();
      *(long *)(self + lVar5) = local_98;
    }
    puVar1 = PTR___NSConcreteStackBlock_0000c038;
    local_b0 = 0;
    local_a0 = 0x2020000000;
    local_d8 = PTR___NSConcreteStackBlock_0000c038;
    local_d0 = 0xc2000000;
    local_c8 = 
    ___75__LoopingFilePlaybackAudioUnit_initWithComponentDescription_options_error___block_invoke;
    puStack_c0 = &___block_descriptor_40_ea8_32r_e24_v20__0__AUParameter_8f16l;
    local_b8 = &local_b0;
    puStack_a8 = &local_b0;
    objc_stub::setImplementorValueObserver_(*(ID *)(self + lVar6),&local_d8);
    local_100 = puVar1;
    local_f8 = 0xc2000000;
    local_f0 = 
    ___75__LoopingFilePlaybackAudioUnit_initWithComponentDescription_options_error___block_invoke_12
    ;
    puStack_e8 = &___block_descriptor_40_ea8_32r_e21_f16__0__AUParameter_8l;
    local_e0 = &local_b0;
    objc_stub::setImplementorValueProvider_(*(ID *)(self + lVar6),&local_100);
    objc_stub::setImplementorStringFromValueCallback_
              (*(ID *)(self + lVar6),&___block_literal_global);
    __Block_object_dispose(&local_b0,8);
  }
  if (*(long *)PTR____stack_chk_guard_0000c040 == local_68) {
    return self;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

// ==== 0000550c __ZN16BufferedAudioBus4initEP13AVAudioFormatj ====
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

// ==== 000055a0 ___75-[LoopingFilePlaybackAudioUnit_initWithComponentDescription:options:error:]_block_invoke ====
void ___75__LoopingFilePlaybackAudioUnit_initWithComponentDescription_options_error___block_invoke
               (float param_1,long param_2,ID param_3)

{
  ID IVar1;
  long lVar2;
  long lVar3;
  
  lVar3 = *(long *)(*(long *)(*(long *)(param_2 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_3);
  if (IVar1 == 0) {
    lVar2 = 0xd8;
  }
  else {
    if (IVar1 != 1) {
      return;
    }
    lVar2 = 0xd9;
  }
  *(bool *)(lVar3 + lVar2) = param_1 != 0.0;
  return;
}

// ==== 00005600 ___copy_helper_block_ea8_32r ====
void ___copy_helper_block_ea8_32r(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  return;
}

// ==== 00005610 ___destroy_helper_block_ea8_32r ====
void ___destroy_helper_block_ea8_32r(long param_1)

{
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 0000561c ___75-[LoopingFilePlaybackAudioUnit_initWithComponentDescription:options:error:]_block_invoke.12 ====
undefined4
___75__LoopingFilePlaybackAudioUnit_initWithComponentDescription_options_error___block_invoke_12
          (long param_1,ID param_2)

{
  ID IVar1;
  long lVar2;
  long lVar3;
  undefined4 uVar4;
  
  lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18);
  IVar1 = objc_stub::address(param_2);
  if (IVar1 == 0) {
    lVar2 = 0xd8;
  }
  else {
    if (IVar1 != 1) {
      return 0;
    }
    lVar2 = 0xd9;
  }
  uVar4 = 0x3f800000;
  if ((*(byte *)(lVar3 + lVar2) & 1) == 0) {
    uVar4 = 0;
  }
  return uVar4;
}

// ==== 0000567c ___75-[LoopingFilePlaybackAudioUnit_initWithComponentDescription:options:error:]_block_invoke.14 ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */

cfstringStruct *
___75__LoopingFilePlaybackAudioUnit_initWithComponentDescription_options_error___block_invoke_14
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
    pcVar2 = &cf_Stopped;
    pcVar3 = &cf_Playing;
  }
  else {
    if (IVar1 != 1) {
      return &cf__;
    }
    pcVar2 = &cf_Unmuted;
    pcVar3 = &cf_Muted;
  }
  if (fVar4 == 0.0) {
    pcVar3 = pcVar2;
  }
  return pcVar3;
}

// ==== 00005738 LoopingFilePlaybackAudioUnit::reset ====
/* Function Stack Size: 0x10 bytes */

void LoopingFilePlaybackAudioUnit::reset(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_30;
  class_t *pcStack_28;
  
  pcStack_28 = &objc::class_t::LoopingFilePlaybackAudioUnit;
  local_30 = param_1;
  TrackedAUAudioUnit::reset((ID)&local_30,"reset");
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  *(undefined1 *)(lVar1 + 0xd8) = 0;
  if ((0 < *(int *)(lVar1 + 0xb4)) && (*(int *)(lVar1 + 0xa8) != 0)) {
    _TPCircularBufferClear(lVar1 + 0xa0);
  }
  return;
}

// ==== 000057ac LoopingFilePlaybackAudioUnit::dealloc ====
/* Function Stack Size: 0x10 bytes */

void LoopingFilePlaybackAudioUnit::dealloc(ID param_1,SEL param_2)

{
  long lVar1;
  ID local_58;
  class_t *pcStack_50;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  
  lVar1 = (long)_dspKernel;
  local_28 = *(long *)(param_1 + lVar1);
  local_48 = PTR___NSConcreteStackBlock_0000c038;
  local_40 = 0xc0000000;
  local_38 = ____ZN28LoopingFilePlaybackDSPKernel7cleanupEv_block_invoke;
  puStack_30 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_28 + 0x50),&local_48);
  if (*(long *)(param_1 + lVar1) != 0) {
    __ZN28LoopingFilePlaybackDSPKernelD2Ev();
    __ZdlPv();
  }
  *(undefined8 *)(param_1 + lVar1) = 0;
  pcStack_50 = &objc::class_t::LoopingFilePlaybackAudioUnit;
  local_58 = param_1;
  TrackedAUAudioUnit::dealloc((ID)&local_58,"dealloc");
  return;
}

// ==== 00005848 ___clang_call_terminate ====
void ___clang_call_terminate(undefined8 param_1,undefined8 param_2,ID param_3)

{
  ID IVar1;
  long lVar2;
  undefined1 auVar3 [16];
  undefined1 auStack_68 [8];
  undefined1 auStack_60 [8];
  undefined *puStack_58;
  undefined1 auStack_50 [16];
  undefined **ppuStack_40;
  long lStack_38;
  
  ___cxa_begin_catch();
  auVar3 = __ZSt9terminatev();
  IVar1 = auVar3._0_8_;
  lStack_38 = *(long *)PTR____stack_chk_guard_0000c040;
  LoopingFilePlaybackAudioUnit::setUrl_(IVar1,auVar3._8_8_,param_3);
  _objc_initWeak(auStack_60,IVar1);
  lVar2 = *(long *)(IVar1 + (long)LoopingFilePlaybackAudioUnit::_dspKernel);
  _objc_copyWeak(auStack_68,auStack_60);
  ppuStack_40 = (undefined **)0x0;
  puStack_58 = &DAT_0000c200;
  _objc_moveWeak(auStack_50,auStack_68);
  ppuStack_40 = &puStack_58;
  _objc_destroyWeak(auStack_68);
  __ZNSt3__18functionIFviPK7__CFURLEEaSERKS5_(lVar2 + 0xe8,&puStack_58);
  if (ppuStack_40 == &puStack_58) {
    lVar2 = 0x20;
  }
  else {
    if (ppuStack_40 == (undefined **)0x0) goto LAB_00005908;
    lVar2 = 0x28;
  }
  (**(code **)(*ppuStack_40 + lVar2))();
LAB_00005908:
  _objc_destroyWeak(auStack_60);
  if (*(long *)PTR____stack_chk_guard_0000c040 == lStack_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00005858 LoopingFilePlaybackAudioUnit::configureDSPKernelWithFileURL: ====
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::configureDSPKernelWithFileURL_(ID param_1,SEL param_2,ID param_3)

{
  long lVar1;
  undefined1 auStack_58 [8];
  undefined1 auStack_50 [8];
  undefined *local_48;
  undefined1 auStack_40 [16];
  undefined **local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c040;
  setUrl_(param_1,param_3);
  _objc_initWeak(auStack_50,param_1);
  lVar1 = *(long *)(param_1 + (long)_dspKernel);
  _objc_copyWeak(auStack_58,auStack_50);
  local_30 = (undefined **)0x0;
  local_48 = &DAT_0000c200;
  _objc_moveWeak(auStack_40,auStack_58);
  local_30 = &local_48;
  _objc_destroyWeak(auStack_58);
  __ZNSt3__18functionIFviPK7__CFURLEEaSERKS5_(lVar1 + 0xe8,&local_48);
  if (local_30 == &local_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (undefined **)0x0) goto LAB_00005908;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00005908:
  _objc_destroyWeak(auStack_50);
  if (*(long *)PTR____stack_chk_guard_0000c040 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00005980 LoopingFilePlaybackAudioUnit::prepareToPlay ====
/* Function Stack Size: 0x10 bytes */

void LoopingFilePlaybackAudioUnit::prepareToPlay(ID param_1,SEL param_2)

{
  __ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv(*(undefined8 *)(param_1 + (long)_dspKernel));
  return;
}

// ==== 00005990 LoopingFilePlaybackAudioUnit::outputBusses ====
/* WARNING: Function: _objc_retainAutoreleaseReturnValue replaced with injection: _objc_retain_fixup
    */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::outputBusses(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 000059a0 LoopingFilePlaybackAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x18 bytes */

bool LoopingFilePlaybackAudioUnit::allocateRenderResourcesAndReturnError_
               (ID param_1,SEL param_2,ID *param_3)

{
  bool bVar1;
  ID IVar2;
  ID IVar3;
  undefined8 uVar4;
  long lVar5;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  ID local_70;
  class_t *pcStack_68;
  
  pcStack_68 = &objc::class_t::LoopingFilePlaybackAudioUnit;
  local_70 = param_1;
  IVar2 = TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_
                    ((ID)&local_70,"allocateRenderResourcesAndReturnError:");
  bVar1 = 0;
  if ((int)IVar2 != 0) {
    IVar2 = auOutputBus(param_1);
    IVar2 = objc_stub::format(IVar2);
    IVar2 = objc_stub::channelCount(IVar2);
    lVar5 = (long)_bufferedOutputBus;
    IVar3 = objc_stub::format(*(ID *)(param_1 + lVar5));
    IVar3 = objc_stub::channelCount(IVar3);
    if ((int)IVar2 == (int)IVar3) {
      IVar2 = objc_stub::maximumFramesToRender(param_1);
      __ZN16BufferedAudioBus23allocateRenderResourcesEj(param_1 + lVar5,IVar2);
      uVar4 = *(undefined8 *)(param_1 + (long)_dspKernel);
      IVar2 = auOutputBus(param_1);
      IVar2 = objc_stub::format(IVar2);
      IVar2 = objc_stub::channelCount(IVar2);
      IVar3 = auOutputBus(param_1);
      IVar3 = objc_stub::format(IVar3);
      objc_stub::sampleRate(IVar3);
      IVar3 = url(param_1);
      __ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL
                ((float)(double)CONCAT44(extraout_var,extraout_s0),uVar4,IVar2,IVar3);
      reset(param_1);
      prepareToPlay(param_1);
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
  return bVar1;
}

// ==== 00005c10 __ZN16BufferedAudioBus23allocateRenderResourcesEj ====
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

// ==== 00005cb0 __ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL ====
void __ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL
               (undefined4 param_1,long param_2,undefined4 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined *local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  long local_30;
  undefined1 uStack_21;
  
  *(undefined4 *)(param_2 + 8) = param_3;
  *(undefined4 *)(param_2 + 0xc) = param_1;
  *(undefined8 *)(param_2 + 0x10) = param_4;
  uVar1 = __ZN19AudioObfuscatorImplC1Ev(&uStack_21);
  local_50 = PTR___NSConcreteStackBlock_0000c038;
  local_48 = 0xc0000000;
  local_40 = ____ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL_block_invoke;
  puStack_38 = &___block_descriptor_40_e5_v8__0l;
  local_30 = param_2;
  __ZN19AudioObfuscatorImpl37performOperationOnObfuscatedAudioFileEP5NSURLU13block_pointerFvvE
            (uVar1,*(undefined8 *)(param_2 + 0x10),&local_50);
  __TPCircularBufferInit(param_2 + 0xa0,*(undefined4 *)(param_2 + 0x94),0x20);
  __ZN19AudioObfuscatorImplD1Ev(&uStack_21);
  return;
}

// ==== 00005d50 LoopingFilePlaybackAudioUnit::deallocateRenderResources ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void LoopingFilePlaybackAudioUnit::deallocateRenderResources(ID param_1,SEL param_2)

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
  local_48 = PTR___NSConcreteStackBlock_0000c038;
  local_40 = 0xc0000000;
  local_38 = ____ZN28LoopingFilePlaybackDSPKernel7cleanupEv_block_invoke;
  puStack_30 = &___block_descriptor_40_e5_v8__0l;
  _dispatch_sync(*(undefined8 *)(local_28 + 0x50),&local_48);
  pcStack_50 = &objc::class_t::LoopingFilePlaybackAudioUnit;
  local_58 = param_1;
  TrackedAUAudioUnit::deallocateRenderResources((ID)&local_58,"deallocateRenderResources");
  return;
}

// ==== 00005df4 LoopingFilePlaybackAudioUnit::shouldChangeToFormat:forBus: ====
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* Function Stack Size: 0x20 bytes */

bool LoopingFilePlaybackAudioUnit::shouldChangeToFormat_forBus_
               (ID param_1,SEL param_2,ID param_3,ID param_4)

{
  long lVar1;
  ID IVar2;
  ID IVar3;
  ID IVar4;
  long lVar5;
  long local_68;
  undefined8 local_60;
  long local_58;
  
  local_58 = *(long *)PTR____stack_chk_guard_0000c040;
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
                         *(undefined8 *)PTR__NSInternalInconsistencyException_0000c050,
                         &cf_Cannotinitoutputbuswithnewformat,0);
      NSException::raise(IVar3);
    }
  }
  else {
    IVar3 = NSException::exceptionWithName_reason_userInfo_
                      ((ID)&_OBJC_CLASS___NSException,
                       *(undefined8 *)PTR__NSInternalInconsistencyException_0000c050,
                       &cf_Unrecognisedbustype,0);
    NSException::raise(IVar3);
  }
  if (*(long *)PTR____stack_chk_guard_0000c040 != local_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return (bool)(IVar2 == 2);
}

// ==== 00006060 LoopingFilePlaybackAudioUnit::internalRenderBlock ====
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::internalRenderBlock(ID param_1,SEL param_2)

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
  local_88 = PTR___NSConcreteStackBlock_0000c038;
  local_80 = 0xc2000000;
  local_78 = ___51__LoopingFilePlaybackAudioUnit_internalRenderBlock__block_invoke;
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

// ==== 00006128 ___51-[LoopingFilePlaybackAudioUnit_internalRenderBlock]_block_invoke ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
___51__LoopingFilePlaybackAudioUnit_internalRenderBlock__block_invoke
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7)

{
  if ((*(long *)(param_6 + 0x10) == 0) && (*(long *)(param_1 + 0x28) != 0)) {
    __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb
              (*(long *)(param_1 + 0x28) + (long)LoopingFilePlaybackAudioUnit::_bufferedOutputBus,
               param_6,param_4,1);
  }
  *(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) + 0x88) = param_6;
  __ZN9DSPKernel17processWithEventsEPK14AudioTimeStampjPK13AURenderEvent
            (*(undefined8 *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18),param_3,param_4,
             param_7);
  return 0;
}

// ==== 000061d0 __ZN17BufferedOutputBus23prepareOutputBufferListEP15AudioBufferListjb ====
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

// ==== 00006268 ___copy_helper_block_ea8_32r40w ====
void ___copy_helper_block_ea8_32r40w(long param_1,long param_2)

{
  __Block_object_assign((void *)(param_1 + 0x20),*(void **)(param_2 + 0x20),8);
  _objc_copyWeak(param_1 + 0x28,param_2 + 0x28);
  return;
}

// ==== 000062a0 ___destroy_helper_block_ea8_32r40w ====
void ___destroy_helper_block_ea8_32r40w(long param_1)

{
  _objc_destroyWeak(param_1 + 0x28);
  __Block_object_dispose(*(void **)(param_1 + 0x20),8);
  return;
}

// ==== 000062cc LoopingFilePlaybackAudioUnit::canProcessInPlace ====
/* Function Stack Size: 0x10 bytes */

bool LoopingFilePlaybackAudioUnit::canProcessInPlace(ID param_1,SEL param_2)

{
  return 0;
}

// ==== 000062d4 LoopingFilePlaybackAudioUnit::parameterTree ====
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::parameterTree(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_parameterTree);
}

// ==== 000062e4 LoopingFilePlaybackAudioUnit::setParameterTree: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setParameterTree_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_parameterTree) = param_3;
  return;
}

// ==== 000062f8 LoopingFilePlaybackAudioUnit::delegate ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_autoreleaseReturnValue replaced with injection: _objc_retain_fixup */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::delegate(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_delegate);
}

// ==== 00006318 LoopingFilePlaybackAudioUnit::setDelegate: ====
/* WARNING: Function: _objc_storeWeak replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setDelegate_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_delegate) = param_3;
  return;
}

// ==== 0000632c LoopingFilePlaybackAudioUnit::auOutputBus ====
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::auOutputBus(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBus);
}

// ==== 0000633c LoopingFilePlaybackAudioUnit::setAuOutputBus: ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setAuOutputBus_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBus) = param_3;
  return;
}

// ==== 00006350 LoopingFilePlaybackAudioUnit::auOutputBusArray ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::auOutputBusArray(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_auOutputBusArray);
}

// ==== 00006360 LoopingFilePlaybackAudioUnit::setAuOutputBusArray: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setAuOutputBusArray_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_auOutputBusArray) = param_3;
  return;
}

// ==== 0000636c LoopingFilePlaybackAudioUnit::defaultFormat ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::defaultFormat(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_defaultFormat);
}

// ==== 0000637c LoopingFilePlaybackAudioUnit::setDefaultFormat: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setDefaultFormat_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_defaultFormat) = param_3;
  return;
}

// ==== 00006388 LoopingFilePlaybackAudioUnit::url ====
/* WARNING: Function: _objc_getProperty replaced with injection: _objc_getProperty_fixup */
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::url(ID param_1,SEL param_2)

{
  return *(ID *)(param_1 + (long)_url);
}

// ==== 00006398 LoopingFilePlaybackAudioUnit::setUrl: ====
/* WARNING: Function: _objc_setProperty_atomic replaced with injection: _objc_setProperty_fixup */
/* Function Stack Size: 0x18 bytes */

void LoopingFilePlaybackAudioUnit::setUrl_(ID param_1,SEL param_2,ID param_3)

{
  *(ID *)(param_1 + (long)_url) = param_3;
  return;
}

// ==== 000063a4 LoopingFilePlaybackAudioUnit::.cxx_destruct ====
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x10 bytes */

void LoopingFilePlaybackAudioUnit::_cxx_destruct(ID param_1,SEL param_2)

{
  *(undefined8 *)(param_1 + (long)_url) = 0;
  *(undefined8 *)(param_1 + (long)_defaultFormat) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBusArray) = 0;
  *(undefined8 *)(param_1 + (long)_auOutputBus) = 0;
  _objc_destroyWeak(param_1 + (long)_delegate);
  *(undefined8 *)(param_1 + (long)_parameterTree) = 0;
  return;
}

// ==== 0000644c LoopingFilePlaybackAudioUnit::.cxx_construct ====
/* Function Stack Size: 0x10 bytes */

ID LoopingFilePlaybackAudioUnit::_cxx_construct(ID param_1,SEL param_2)

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

// ==== 0000646c __ZN28LoopingFilePlaybackDSPKernelC2Ev ====
undefined8 * __ZN28LoopingFilePlaybackDSPKernelC2Ev(undefined8 *param_1)

{
  dispatch_queue_t pdVar1;
  undefined8 uVar2;
  
  *param_1 = &DAT_0000c150;
  param_1[1] = 0x472c440000000000;
  param_1[3] = 0;
  param_1[9] = 0;
  pdVar1 = _dispatch_queue_create("LoopingFilePlaybackDSPKernelQueue",(dispatch_queue_attr_t)0x0);
  param_1[10] = pdVar1;
  *(undefined1 *)(param_1 + 0xb) = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0x2b11000005622;
  *(undefined4 *)(param_1 + 0x13) = 0x15888;
  param_1[0x18] = 0;
  *(int *)(param_1 + 0x19) = (int)*(float *)((long)param_1 + 0xc);
  param_1[0x1a] = 0x3ff0000000000000;
  *(undefined2 *)(param_1 + 0x1b) = 0;
  uVar2 = NEON_fmov(0x3f800000,4);
  *(undefined8 *)((long)param_1 + 0xdc) = uVar2;
  param_1[0x20] = 0;
  *(undefined4 *)(param_1 + 0x21) = 0;
  return param_1;
}

// ==== 0000650c __ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp ====
void __ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp
               (long param_1,uint param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  int iVar10;
  int iVar11;
  long *plVar12;
  ulong uVar13;
  float *pfVar14;
  long lVar15;
  float fVar16;
  undefined *local_38;
  undefined8 local_30;
  code *local_28;
  undefined *puStack_20;
  long local_18;
  
  if (((*(byte *)(param_1 + 0xd8) & 1) == 0) || (*(int *)(param_1 + 0x108) != 0)) {
    if (param_2 != 0) {
      uVar8 = 0;
      uVar3 = *(uint *)(param_1 + 8);
      do {
        if (0 < (int)uVar3) {
          plVar12 = *(long **)(param_1 + 0x88);
          uVar13 = (ulong)uVar3;
          pfVar14 = (float *)(param_1 + 0xdc);
          do {
            plVar12 = plVar12 + 2;
            *(float *)(*plVar12 + (long)((int)uVar8 + param_3) * 4) = *pfVar14 * 0.0;
            uVar13 = uVar13 - 1;
            pfVar14 = pfVar14 + 1;
          } while (uVar13 != 0);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 != param_2);
    }
  }
  else {
    puVar1 = (uint *)(param_1 + 0xb4);
    if (*puVar1 == 0) {
      lVar9 = 0;
    }
    else {
      lVar9 = *(long *)(param_1 + 0xa0) + (ulong)*(uint *)(param_1 + 0xac);
    }
    iVar10 = *(int *)(param_1 + 8);
    if (param_2 == 0) {
      iVar11 = 0;
    }
    else {
      uVar8 = 0;
      iVar11 = 0;
      uVar13 = 0;
      if ((long)iVar10 != 0) {
        uVar13 = (ulong)(*puVar1 >> 2) / (ulong)(long)iVar10;
      }
      do {
        if (0 < iVar10) {
          lVar15 = 0;
          lVar7 = 0x10;
          do {
            fVar16 = 0.0;
            if (uVar8 < uVar13) {
              if ((*(byte *)(param_1 + 0xd9) & 1) == 0) {
                fVar16 = *(float *)(lVar9 + (long)((int)lVar15 + (int)uVar8 * iVar10) * 4);
              }
              if (lVar15 == 0) {
                iVar11 = iVar11 + 1;
              }
              iVar10 = *(int *)(param_1 + 8);
            }
            *(float *)(*(long *)(*(long *)(param_1 + 0x88) + lVar7) +
                      (long)((int)uVar8 + param_3) * 4) =
                 fVar16 * *(float *)(param_1 + 0xdc + lVar15 * 4);
            lVar15 = lVar15 + 1;
            lVar7 = lVar7 + 0x10;
          } while (lVar15 < iVar10);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 != param_2);
      iVar11 = iVar11 << 2;
    }
    iVar10 = iVar10 * iVar11;
    uVar2 = *(uint *)(param_1 + 0xa8);
    uVar3 = *(int *)(param_1 + 0xac) + iVar10;
    uVar6 = 0;
    if (uVar2 != 0) {
      uVar6 = uVar3 / uVar2;
    }
    *(uint *)(param_1 + 0xac) = uVar3 - uVar6 * uVar2;
    if ((*(byte *)(param_1 + 0xb8) & 1) == 0) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
        if (bVar5) {
          *puVar1 = *puVar1 - iVar10;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
    }
    else {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
        if (bVar5) {
          *puVar1 = *puVar1 - iVar10;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
    }
    if ((int)*puVar1 < 0) {
      __ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp_cold_1();
      return;
    }
    if ((*(uint *)(param_1 + 0xb4) < *(uint *)(param_1 + 0x98)) &&
       ((*(byte *)(param_1 + 0x58) & 1) == 0)) {
      local_38 = PTR___NSConcreteStackBlock_0000c038;
      local_30 = 0xc0000000;
      local_28 = ____ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp_block_invoke;
      puStack_20 = &___block_descriptor_40_e5_v8__0l;
      local_18 = param_1;
      _dispatch_async(*(undefined8 *)(param_1 + 0x50),&local_38);
    }
  }
  return;
}

// ==== 00006714 __ZN28LoopingFilePlaybackDSPKernel9startRampEyfj ====
void __ZN28LoopingFilePlaybackDSPKernel9startRampEyfj(void)

{
  return;
}

// ==== 00006718 __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent ====
void __ZN9DSPKernel15handleMIDIEventERK11AUMIDIEvent(void)

{
  return;
}

// ==== 0000671c ____ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp_block_invoke ====
void ____ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp_block_invoke(long param_1)

{
  __ZN28LoopingFilePlaybackDSPKernel18fillCircularBufferEb(*(undefined8 *)(param_1 + 0x20),0);
  return;
}

// ==== 00006728 __ZN28LoopingFilePlaybackDSPKernel18fillCircularBufferEb ====
/* WARNING: Removing unreachable block (ram,0x00006850) */
/* WARNING: Removing unreachable block (ram,0x0000688c) */
/* WARNING: Removing unreachable block (ram,0x00006b6c) */
/* WARNING: Removing unreachable block (ram,0x00006820) */
/* WARNING: Removing unreachable block (ram,0x00006b78) */
/* WARNING: Removing unreachable block (ram,0x00006b80) */
/* WARNING: Removing unreachable block (ram,0x000068b8) */

void __ZN28LoopingFilePlaybackDSPKernel18fillCircularBufferEb(long param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  undefined8 uVar8;
  undefined4 *puVar9;
  ulong uVar10;
  uint *puVar11;
  long lVar12;
  bool bVar13;
  uint uVar14;
  int iVar15;
  uint *puVar16;
  ulong uVar17;
  double dVar18;
  undefined1 auVar19 [16];
  uint local_a0 [4];
  undefined4 *local_90;
  uint local_84;
  uint *local_80;
  uint *local_78;
  uint *local_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_0000c040;
  if (*(int *)(param_1 + 0x78) != 0) {
    if (((*(byte *)(param_1 + 0xd8) & 1) != 0) ||
       ((param_2 != 0 && ((*(byte *)(param_1 + 0x58) & 1) == 0)))) {
      *(undefined1 *)(param_1 + 0x58) = 1;
      piVar1 = (int *)(param_1 + 0xb4);
      uVar4 = *(int *)(param_1 + 0xa8) - *piVar1;
      if (uVar4 == 0) {
        lVar12 = 0;
      }
      else {
        lVar12 = *(long *)(param_1 + 0xa0) + (ulong)*(uint *)(param_1 + 0xb0);
      }
      uVar14 = 0;
      if (*(uint *)(param_1 + 0x78) != 0) {
        uVar14 = uVar4 / *(uint *)(param_1 + 0x78);
      }
      local_80 = (void *)0x0;
      local_78 = (uint *)0x0;
      local_70 = (uint *)0x0;
      piVar2 = (int *)(param_1 + 0xc0);
      if (*piVar2 + uVar14 < *(uint *)(param_1 + 200)) {
        auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIjEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                            (&local_70,1);
      }
      else {
        uVar14 = *(uint *)(param_1 + 200) - *piVar2;
        auVar19 = __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIjEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
                            (&local_70,1);
      }
      puVar7 = auVar19._0_8_;
      puVar11 = puVar7 + -((long)local_78 - (long)local_80 >> 2);
      puVar16 = puVar7 + 1;
      *puVar7 = uVar14;
      _memcpy(puVar11,local_80,(long)local_78 - (long)local_80);
      bVar13 = local_80 != (void *)0x0;
      local_80 = puVar11;
      local_70 = puVar7 + auVar19._8_8_;
      if (bVar13) {
        local_78 = puVar16;
        __ZdlPv();
      }
      bVar13 = true;
      local_78 = puVar16;
      if (local_80 != puVar16) {
        iVar15 = 0;
        uVar17 = 0;
        puVar7 = local_80;
        do {
          uVar4 = *puVar7;
          local_84 = uVar4;
          if (uVar4 == 0) {
            if (*(int *)(param_1 + 0xc0) == *(int *)(param_1 + 200)) {
              dVar18 = (double)NEON_ucvtf((ulong)*(uint *)(param_1 + 0xc4));
              iVar6 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x18),
                                        (long)(*(double *)(param_1 + 0xd0) * dVar18));
              if (iVar6 == 0) {
                if (*(long *)(param_1 + 0x100) != 0) {
                  __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_
                            (param_1 + 0xe8,0,*(undefined8 *)(param_1 + 0x10));
                }
                goto LAB_00006ab4;
              }
              *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xc4);
            }
          }
          else {
            local_a0[3] = *(int *)(param_1 + 0x78) * uVar4;
            local_90 = (undefined4 *)((long)local_a0 - ((ulong)local_a0[3] + 0xf & 0x1fffffff0));
            local_a0[2] = *(undefined4 *)(param_1 + 0x7c);
            local_a0[0] = 1;
            uVar8 = _ExtAudioFileRead(*(undefined8 *)(param_1 + 0x18),&local_84,local_a0);
            if ((int)uVar8 != 0) {
              if (*(long *)(param_1 + 0x100) != 0) {
                __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_
                          (param_1 + 0xe8,uVar8,*(undefined8 *)(param_1 + 0x10));
              }
LAB_00006ab4:
              bVar13 = false;
              goto LAB_00006abc;
            }
            if ((long)(ulong)*(uint *)(param_1 + 0xc0) < *(long *)(param_1 + 0x48)) {
              uVar14 = *(int *)(param_1 + 0x7c) * local_84;
              uVar10 = (ulong)uVar14;
              puVar9 = local_90;
              if (uVar14 != 0) {
                do {
                  *(undefined4 *)(lVar12 + uVar17 * 4) = *puVar9;
                  uVar17 = (ulong)((int)uVar17 + 1);
                  uVar10 = uVar10 - 1;
                  puVar9 = puVar9 + 1;
                } while (uVar10 != 0);
              }
              do {
                cVar3 = '\x01';
                bVar13 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar13) {
                  *piVar2 = *piVar2 + local_84;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              if (*(int *)(param_1 + 0xc0) == *(int *)(param_1 + 200)) {
                dVar18 = (double)NEON_ucvtf((ulong)*(uint *)(param_1 + 0xc4));
                uVar8 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x18),
                                          (long)(*(double *)(param_1 + 0xd0) * dVar18));
                if ((int)uVar8 != 0) {
                  if (*(long *)(param_1 + 0x100) != 0) {
                    __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_
                              (param_1 + 0xe8,uVar8,*(undefined8 *)(param_1 + 0x10));
                  }
                  goto LAB_00006ab4;
                }
                *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xc4);
              }
            }
            iVar15 = uVar4 + iVar15;
          }
          puVar7 = puVar7 + 1;
        } while (puVar7 != local_78);
        if (iVar15 != 0) {
          iVar15 = *(int *)(param_1 + 0x78) * iVar15;
          uVar4 = *(int *)(param_1 + 0xb0) + iVar15;
          uVar14 = *(uint *)(param_1 + 0xa8);
          uVar5 = 0;
          if (uVar14 != 0) {
            uVar5 = uVar4 / uVar14;
          }
          *(uint *)(param_1 + 0xb0) = uVar4 - uVar5 * uVar14;
          do {
            cVar3 = '\x01';
            bVar13 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar13) {
              *piVar1 = *piVar1 + iVar15;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          if (*(uint *)(param_1 + 0xa8) < *(uint *)(param_1 + 0xb4)) {
                    /* WARNING: Subroutine does not return */
            ___assert_rtn("TPCircularBufferProduce","TPCircularBuffer.h",0xc5,
                          "buffer->fillCount <= buffer->length");
          }
        }
        bVar13 = true;
      }
LAB_00006abc:
      if (local_80 != (uint *)0x0) {
        local_78 = local_80;
        __ZdlPv(local_80);
      }
      if (!bVar13) goto LAB_00006ad8;
    }
    *(undefined1 *)(param_1 + 0x58) = 0;
  }
LAB_00006ad8:
  if (*(long *)PTR____stack_chk_guard_0000c040 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

// ==== 00006bc0 __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_ ====
void __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_(long param_1,undefined4 param_2,undefined8 param_3)

{
  long *plVar1;
  undefined8 local_20;
  undefined4 local_14;
  
  plVar1 = *(long **)(param_1 + 0x18);
  local_20 = param_3;
  local_14 = param_2;
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x30))(plVar1,&local_14,&local_20);
    return;
  }
  __ZNSt3__125__throw_bad_function_callB8ne190102Ev();
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 00006c00 __ZNKSt3__16vectorIjNS_9allocatorIjEEE20__throw_length_errorB8ne190102Ev ====
void __ZNKSt3__16vectorIjNS_9allocatorIjEEE20__throw_length_errorB8ne190102Ev(void)

{
                    /* WARNING: Subroutine does not return */
  __ZNSt3__120__throw_length_errorB8ne190102EPKc("vector");
}

// ==== 00006c14 __ZNSt3__120__throw_length_errorB8ne190102EPKc ====
void __ZNSt3__120__throw_length_errorB8ne190102EPKc(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = ___cxa_allocate_exception(0x10);
  __ZNSt12length_errorC1B8ne190102EPKc(uVar1,param_1);
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt12length_error_0000c058,PTR___ZNSt12length_errorD1Ev_0000c010);
}

// ==== 00006c64 __ZNSt12length_errorC1B8ne190102EPKc ====
void __ZNSt12length_errorC1B8ne190102EPKc(void)

{
  long *plVar1;
  
  plVar1 = (long *)__ZNSt11logic_errorC2EPKc();
  *plVar1 = (long)(PTR___ZTVSt12length_error_0000c028 + 0x10);
  return;
}

// ==== 00006c88 __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIjEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m ====
void __ZNSt3__119__allocate_at_leastB8ne190102INS_9allocatorIjEEEENS_19__allocation_resultINS_16allocator_traitsIT_E7pointerEEERS5_m
               (undefined8 param_1,ulong param_2)

{
  if (param_2 >> 0x3e == 0) {
    __Znwm(param_2 << 2);
    return;
  }
                    /* WARNING: Subroutine does not return */
  __ZSt28__throw_bad_array_new_lengthB8ne190102v();
}

// ==== 00006cbc __ZSt28__throw_bad_array_new_lengthB8ne190102v ====
void __ZSt28__throw_bad_array_new_lengthB8ne190102v(void)

{
  undefined8 uVar1;
  
  ___cxa_allocate_exception(8);
  uVar1 = __ZNSt20bad_array_new_lengthC1Ev();
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(uVar1,PTR___ZTISt20bad_array_new_length_0000c020,
               PTR___ZNSt20bad_array_new_lengthD1Ev_0000c018);
}

// ==== 00006ce4 __ZNSt3__125__throw_bad_function_callB8ne190102Ev ====
void __ZNSt3__125__throw_bad_function_callB8ne190102Ev(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)___cxa_allocate_exception(8);
  *puVar1 = &DAT_0000c1d8;
                    /* WARNING: Subroutine does not return */
  ___cxa_throw(puVar1,&__ZTINSt3__117bad_function_callE,__ZNSt3__117bad_function_callD1Ev);
}

// ==== 00006d18 __ZNSt3__117bad_function_callD1Ev ====
void __ZNSt3__117bad_function_callD1Ev(void)

{
  __ZNSt9exceptionD2Ev();
  return;
}

// ==== 00006d1c __ZNSt3__117bad_function_callD0Ev ====
void __ZNSt3__117bad_function_callD0Ev(void)

{
  __ZNSt9exceptionD2Ev();
  __ZdlPv();
  return;
}

// ==== 00006d30 ____ZN28LoopingFilePlaybackDSPKernel7cleanupEv_block_invoke ====
void ____ZN28LoopingFilePlaybackDSPKernel7cleanupEv_block_invoke(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x20);
  *(undefined1 *)(lVar1 + 0x58) = 1;
  _TPCircularBufferClear(lVar1 + 0xa0);
  _TPCircularBufferCleanup(lVar1 + 0xa0);
  if (*(long *)(lVar1 + 0x18) != 0) {
    _ExtAudioFileDispose();
    *(undefined8 *)(lVar1 + 0x18) = 0;
  }
  *(undefined1 *)(lVar1 + 0x58) = 0;
  return;
}

// ==== 00006d7c __ZN28LoopingFilePlaybackDSPKernelD2Ev ====
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 * __ZN28LoopingFilePlaybackDSPKernelD2Ev(undefined8 *param_1)

{
  long *plVar1;
  long lVar2;
  
  *param_1 = &DAT_0000c150;
  param_1[0x11] = 0;
  plVar1 = (long *)param_1[0x20];
  if (plVar1 == param_1 + 0x1d) {
    lVar2 = 0x20;
  }
  else {
    if (plVar1 == (long *)0x0) {
      return param_1;
    }
    lVar2 = 0x28;
  }
  (**(code **)(*plVar1 + lVar2))();
  return param_1;
}

// ==== 00006de4 __ZNSt3__18functionIFviPK7__CFURLEEaSERKS5_ ====
undefined8 __ZNSt3__18functionIFviPK7__CFURLEEaSERKS5_(undefined8 param_1)

{
  long lVar1;
  long alStack_48 [3];
  long *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c040;
  __ZNSt3__110__function12__value_funcIFviPK7__CFURLEEC2B8ne190102ERKS6_(alStack_48);
  __ZNSt3__110__function12__value_funcIFviPK7__CFURLEE4swapB8ne190102ERS6_(alStack_48,param_1);
  if (local_30 == alStack_48) {
    lVar1 = 0x20;
  }
  else {
    if (local_30 == (long *)0x0) goto LAB_00006e48;
    lVar1 = 0x28;
  }
  (**(code **)(*local_30 + lVar1))();
LAB_00006e48:
  if (*(long *)PTR____stack_chk_guard_0000c040 == local_28) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00006e78 __ZNSt3__110__function12__value_funcIFviPK7__CFURLEEC2B8ne190102ERKS6_ ====
long __ZNSt3__110__function12__value_funcIFviPK7__CFURLEEC2B8ne190102ERKS6_
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

// ==== 00006edc __ZNSt3__110__function12__value_funcIFviPK7__CFURLEE4swapB8ne190102ERS6_ ====
void __ZNSt3__110__function12__value_funcIFviPK7__CFURLEE4swapB8ne190102ERS6_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long local_40 [3];
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_0000c040;
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
  if (*(long *)PTR____stack_chk_guard_0000c040 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

// ==== 00007048 __ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv ====
void __ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv(long param_1)

{
  undefined *local_38;
  undefined8 local_30;
  code *local_28;
  undefined *puStack_20;
  long local_18;
  
  if (*(int *)(param_1 + 0x78) == 0) {
    if (*(long *)(param_1 + 0x100) != 0) {
      __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_
                (param_1 + 0xe8,0x2173697a,*(undefined8 *)(param_1 + 0x10));
      return;
    }
  }
  else {
    local_38 = PTR___NSConcreteStackBlock_0000c038;
    local_30 = 0xc0000000;
    local_28 = ____ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv_block_invoke;
    puStack_20 = &___block_descriptor_40_e5_v8__0l;
    local_18 = param_1;
    _dispatch_async(*(undefined8 *)(param_1 + 0x50),&local_38);
  }
  return;
}

// ==== 000070c4 ____ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv_block_invoke ====
void ____ZN28LoopingFilePlaybackDSPKernel13prepareToPlayEv_block_invoke(long param_1)

{
  __ZN28LoopingFilePlaybackDSPKernel18fillCircularBufferEb(*(undefined8 *)(param_1 + 0x20),1);
  return;
}

// ==== 000070d0 ____ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL_block_invoke ====
void ____ZN28LoopingFilePlaybackDSPKernel4initEifPK7__CFURL_block_invoke(long param_1)

{
  __ZN28LoopingFilePlaybackDSPKernel18configureAudioFileEv(*(undefined8 *)(param_1 + 0x20));
  return;
}

// ==== 000070d8 __ZN28LoopingFilePlaybackDSPKernel18configureAudioFileEv ====
void __ZN28LoopingFilePlaybackDSPKernel18configureAudioFileEv(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined4 local_34;
  
  uVar2 = _ExtAudioFileOpenURL(*(undefined8 *)(param_1 + 0x10),param_1 + 0x18);
  *(int *)(param_1 + 0x108) = (int)uVar2;
  if ((int)uVar2 == 0) {
    uVar2 = _ExtAudioFileSeek(*(undefined8 *)(param_1 + 0x18),0);
    *(int *)(param_1 + 0x108) = (int)uVar2;
    if ((int)uVar2 == 0) {
      local_34 = 0x28;
      uVar2 = _ExtAudioFileGetProperty
                        (*(undefined8 *)(param_1 + 0x18),0x66666d74,&local_34,param_1 + 0x20);
      *(int *)(param_1 + 0x108) = (int)uVar2;
      if ((int)uVar2 == 0) {
        *(double *)(param_1 + 0x60) = (double)*(float *)(param_1 + 0xc);
        *(undefined8 *)(param_1 + 0x68) = 0x16c70636d;
        iVar1 = *(int *)(param_1 + 8) << 2;
        *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 8);
        *(undefined4 *)(param_1 + 0x80) = 0x20;
        *(undefined4 *)(param_1 + 0x74) = 1;
        *(int *)(param_1 + 0x78) = iVar1;
        *(int *)(param_1 + 0x70) = iVar1;
        local_34 = 0x28;
        uVar2 = _ExtAudioFileSetProperty
                          (*(undefined8 *)(param_1 + 0x18),0x63666d74,0x28,
                           (double *)(param_1 + 0x60));
        *(int *)(param_1 + 0x108) = (int)uVar2;
        if ((int)uVar2 == 0) {
          local_34 = 8;
          uVar2 = _ExtAudioFileGetProperty
                            (*(undefined8 *)(param_1 + 0x18),0x2366726d,&local_34,param_1 + 0x48);
          *(int *)(param_1 + 0x108) = (int)uVar2;
          if ((int)uVar2 == 0) {
            *(double *)(param_1 + 0xd0) = *(double *)(param_1 + 0x20) / *(double *)(param_1 + 0x60);
            *(int *)(param_1 + 200) = (int)*(undefined8 *)(param_1 + 0x48);
            return;
          }
        }
      }
      if (*(long *)(param_1 + 0x100) == 0) {
        return;
      }
      __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_
                (param_1 + 0xe8,uVar2,*(undefined8 *)(param_1 + 0x10));
      return;
    }
  }
  if (*(long *)(param_1 + 0x100) == 0) {
    return;
  }
  __ZNKSt3__18functionIFviPK7__CFURLEEclEiS3_(param_1 + 0xe8,uVar2,*(undefined8 *)(param_1 + 0x10));
  return;
}

// ==== 00007230 __ZNSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEED1Ev ====
long __ZNSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEED1Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return param_1;
}

// ==== 00007258 __ZNSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEED0Ev ====
void __ZNSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEED0Ev
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 00007280 __ZNKSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE7__cloneEv ====
undefined8 *
__ZNKSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE7__cloneEv
          (long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)__Znwm(0x10);
  *puVar1 = &DAT_0000c200;
  _objc_copyWeak(puVar1 + 1,param_1 + 8);
  return puVar1;
}

// ==== 000072c0 __ZNKSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE7__cloneEPNS0_6__baseIS8_EE ====
void __ZNKSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE7__cloneEPNS0_6__baseIS8_EE
               (long param_1,undefined8 *param_2)

{
  *param_2 = &DAT_0000c200;
  _objc_copyWeak(param_2 + 1,param_1 + 8);
  return;
}

// ==== 000072dc __ZNSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE7destroyEv ====
void __ZNSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE7destroyEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  return;
}

// ==== 000072e4 __ZNSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE18destroy_deallocateEv ====
void __ZNSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE18destroy_deallocateEv
               (long param_1)

{
  _objc_destroyWeak(param_1 + 8);
  __ZdlPv(param_1);
  return;
}

// ==== 0000730c __ZNSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEEclEOiOS7_ ====
/* WARNING: Function: _objc_loadWeakRetained replaced with injection: _objc_load_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
__ZNSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEEclEOiOS7_
          (long param_1,uint *param_2,undefined8 *param_3)

{
  uint uVar1;
  ID self;
  undefined8 uVar2;
  
  uVar1 = *param_2;
  uVar2 = *param_3;
  self = objc_stub::delegate(*(ID *)(param_1 + 8));
  objc_stub::loopingFilePlaybackAudioUnit_fileLoadError_fileURL_
            (self,*(undefined8 *)(param_1 + 8),(ulong)uVar1,uVar2);
  return 0;
}

// ==== 000073bc __ZNKSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE6targetERKSt9type_info ====
long __ZNKSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE6targetERKSt9type_info
               (long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = __ZNKSt9type_infoeqB8ne190102ERKS_
                    (param_2,&
                             __ZTIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0
                    );
  param_1 = param_1 + 8;
  if (iVar1 == 0) {
    param_1 = 0;
  }
  return param_1;
}

// ==== 000073f8 __ZNKSt3__110__function6__funcIZ62-[LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL:]E3$_0NS_9allocatorIS2_EEFviPK7__CFURLEE11target_typeEv ====
undefined **
__ZNKSt3__110__function6__funcIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0NS_9allocatorIS2_EEFviPK7__CFURLEE11target_typeEv
          (void)

{
  return &__ZTIZ62__LoopingFilePlaybackAudioUnit_configureDSPKernelWithFileURL__E3__0;
}

// ==== 00007404 __ZNKSt9type_infoeqB8ne190102ERKS_ ====
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

// ==== 00007450 __ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp.cold.1 ====
void __ZN28LoopingFilePlaybackDSPKernel7processEjjPK14AudioTimeStamp_cold_1(void)

{
                    /* WARNING: Subroutine does not return */
  ___assert_rtn("TPCircularBufferConsume","TPCircularBuffer.h",0xa1,"buffer->fillCount >= 0");
}

// ==== 00007478 _ExtAudioFileDispose ====
void _ExtAudioFileDispose(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileDispose_0000c890)();
  return;
}

// ==== 00007484 _ExtAudioFileGetProperty ====
void _ExtAudioFileGetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000748c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileGetProperty_0000c898)();
  return;
}

// ==== 00007490 _ExtAudioFileOpenURL ====
void _ExtAudioFileOpenURL(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007498. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileOpenURL_0000c8a0)();
  return;
}

// ==== 0000749c _ExtAudioFileRead ====
void _ExtAudioFileRead(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileRead_0000c8a8)();
  return;
}

// ==== 000074a8 _ExtAudioFileSeek ====
void _ExtAudioFileSeek(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSeek_0000c8b0)();
  return;
}

// ==== 000074b4 _ExtAudioFileSetProperty ====
void _ExtAudioFileSetProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__ExtAudioFileSetProperty_0000c8b8)();
  return;
}

// ==== 000074c0 _NSLog ====
void _NSLog(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__NSLog_0000c8c0)();
  return;
}

// ==== 000074cc _TPCircularBufferCleanup ====
void _TPCircularBufferCleanup(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__TPCircularBufferCleanup_0000c8c8)();
  return;
}

// ==== 000074d8 _TPCircularBufferClear ====
void _TPCircularBufferClear(void)

{
                    /* WARNING: Could not recover jumptable at 0x000074e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__TPCircularBufferClear_0000c8d0)();
  return;
}

// ==== 000074e4 __Block_object_assign ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_assign(void *param_1,void *param_2,int param_3)

{
                    /* WARNING: Could not recover jumptable at 0x000074ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_assign_0000c8d8)(param_1,param_2,param_3);
  return;
}

// ==== 000074f0 __Block_object_dispose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Block_object_dispose(void *param_1,int param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000074f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Block_object_dispose_0000c8e0)(param_1,param_2);
  return;
}

// ==== 000074fc __TPCircularBufferInit ====
void __TPCircularBufferInit(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007504. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___TPCircularBufferInit_0000c8e8)();
  return;
}

// ==== 00007508 __Unwind_Resume ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __Unwind_Resume(_Unwind_Exception *exception_object)

{
                    /* WARNING: Could not recover jumptable at 0x00007510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Unwind_Resume_0000c8f0)();
  return;
}

// ==== 00007514 __ZNSt11logic_errorC2EPKc ====
void __ZNSt11logic_errorC2EPKc(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000751c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt11logic_errorC2EPKc_0000c8f8)();
  return;
}

// ==== 00007520 __ZNSt20bad_array_new_lengthC1Ev ====
void __ZNSt20bad_array_new_lengthC1Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt20bad_array_new_lengthC1Ev_0000c900)();
  return;
}

// ==== 0000752c __ZNSt9exceptionD2Ev ====
void __ZNSt9exceptionD2Ev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007534. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZNSt9exceptionD2Ev_0000c908)();
  return;
}

// ==== 00007538 __ZSt9terminatev ====
void __ZSt9terminatev(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007540. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZSt9terminatev_0000c910)();
  return;
}

// ==== 00007544 __ZdlPv ====
void __ZdlPv(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000754c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___ZdlPv_0000c060)();
  return;
}

// ==== 00007550 __Znwm ====
void __Znwm(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007558. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___Znwm_0000c068)();
  return;
}

// ==== 0000755c ___assert_rtn ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ___assert_rtn(char *param_1,char *param_2,int param_3,char *param_4)

{
                    /* WARNING: Could not recover jumptable at 0x00007564. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____assert_rtn_0000c918)(param_1,param_2,param_3);
  return;
}

// ==== 00007568 ___cxa_allocate_exception ====
void ___cxa_allocate_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007570. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_allocate_exception_0000c920)();
  return;
}

// ==== 00007574 ___cxa_begin_catch ====
void ___cxa_begin_catch(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000757c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_begin_catch_0000c928)();
  return;
}

// ==== 00007580 ___cxa_free_exception ====
void ___cxa_free_exception(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007588. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_free_exception_0000c930)();
  return;
}

// ==== 0000758c ___cxa_throw ====
void ___cxa_throw(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007594. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____cxa_throw_0000c938)();
  return;
}

// ==== 00007598 ___stack_chk_fail ====
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x000075a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_0000c940)();
  return;
}

// ==== 000075a4 _bzero ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _bzero(void *param_1,size_t param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000075ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__bzero_0000c948)();
  return;
}

// ==== 000075b0 _dispatch_async ====
void _dispatch_async(void)

{
                    /* WARNING: Could not recover jumptable at 0x000075b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_async_0000c950)();
  return;
}

// ==== 000075bc _dispatch_queue_create ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

dispatch_queue_t _dispatch_queue_create(char *label,dispatch_queue_attr_t attr)

{
  dispatch_queue_t pdVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000075c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pdVar1 = (dispatch_queue_t)(*(code *)PTR__dispatch_queue_create_0000c958)();
  return pdVar1;
}

// ==== 000075c8 _dispatch_sync ====
void _dispatch_sync(void)

{
                    /* WARNING: Could not recover jumptable at 0x000075d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__dispatch_sync_0000c960)();
  return;
}

// ==== 000075d4 _fclose ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fclose(FILE *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000075dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fclose_0000c968)((int)param_1);
  return iVar1;
}

// ==== 000075e0 _fgetc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fgetc(FILE *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000075e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fgetc_0000c970)((int)param_1);
  return iVar1;
}

// ==== 000075ec _fopen ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * _fopen(char *param_1,char *param_2)

{
  FILE *pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000075f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = (FILE *)(*(code *)PTR__fopen_0000c978)();
  return pFVar1;
}

// ==== 000075f8 _fputc ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fputc(int param_1,FILE *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007600. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fputc_0000c980)(param_1);
  return iVar1;
}

// ==== 00007604 _fseek ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fseek(FILE *param_1,long param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000760c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fseek_0000c988)((int)param_1,param_2,param_3);
  return iVar1;
}

// ==== 00007610 _fseeko ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _fseeko(FILE *param_1,off_t param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__fseeko_0000c990)((int)param_1,param_2,param_3);
  return iVar1;
}

// ==== 0000761c _memcpy ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * _memcpy(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007624. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = (void *)(*(code *)PTR__memcpy_0000c998)();
  return pvVar1;
}

// ==== 00007628 _objc_alloc ====
void _objc_alloc(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007630. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_alloc_0000c9a0)();
  return;
}

// ==== 00007634 _objc_autorelease ====
/* WARNING: This is an inlined function */

void _objc_autorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000763c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autorelease_0000c9a8)();
  return;
}

// ==== 00007640 _objc_autoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_autoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007648. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_autoreleaseReturnValue_0000c9b0)();
  return;
}

// ==== 0000764c _objc_copyWeak ====
void _objc_copyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007654. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_copyWeak_0000c9b8)();
  return;
}

// ==== 00007658 _objc_destroyWeak ====
void _objc_destroyWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007660. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_destroyWeak_0000c9c0)();
  return;
}

// ==== 00007664 _objc_getProperty ====
/* WARNING: This is an inlined function */

void _objc_getProperty(void)

{
                    /* WARNING: Could not recover jumptable at 0x0000766c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_getProperty_0000c9c8)();
  return;
}

// ==== 00007670 _objc_initWeak ====
void _objc_initWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007678. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_initWeak_0000c9d0)();
  return;
}

// ==== 0000767c _objc_loadWeakRetained ====
/* WARNING: This is an inlined function */

void _objc_loadWeakRetained(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007684. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_loadWeakRetained_0000c9d8)();
  return;
}

// ==== 00007688 _objc_moveWeak ====
void _objc_moveWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007690. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_moveWeak_0000c9e0)();
  return;
}

// ==== 00007694 _objc_msgSendSuper2 ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSendSuper2(objc_super *super,SEL op,...)

{
  ID IVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0000769c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  IVar1 = (*(code *)PTR__objc_msgSendSuper2_0000c9e8)();
  return IVar1;
}

// ==== 000076a0 _objc_release ====
/* WARNING: This is an inlined function */

void _objc_release(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_release_0000c9f0)();
  return;
}

// ==== 000076ac _objc_retain ====
/* WARNING: This is an inlined function */

void _objc_retain(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retain_0000c9f8)();
  return;
}

// ==== 000076b8 _objc_retainAutorelease ====
void _objc_retainAutorelease(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutorelease_0000ca00)();
  return;
}

// ==== 000076c4 _objc_retainAutoreleaseReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleaseReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleaseReturnValue_0000ca08)();
  return;
}

// ==== 000076d0 _objc_retainAutoreleasedReturnValue ====
/* WARNING: This is an inlined function */

void _objc_retainAutoreleasedReturnValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainAutoreleasedReturnValue_0000ca10)();
  return;
}

// ==== 000076dc _objc_retainBlock ====
/* WARNING: This is an inlined function */

void _objc_retainBlock(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_retainBlock_0000ca18)();
  return;
}

// ==== 000076e8 _objc_setProperty_atomic ====
/* WARNING: This is an inlined function */

void _objc_setProperty_atomic(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_setProperty_atomic_0000ca20)();
  return;
}

// ==== 000076f4 _objc_storeStrong ====
/* WARNING: This is an inlined function */

void _objc_storeStrong(void)

{
                    /* WARNING: Could not recover jumptable at 0x000076fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeStrong_0000ca28)();
  return;
}

// ==== 00007700 _objc_storeWeak ====
/* WARNING: This is an inlined function */

void _objc_storeWeak(void)

{
                    /* WARNING: Could not recover jumptable at 0x00007708. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__objc_storeWeak_0000ca30)();
  return;
}

// ==== 0000770c _rand ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _rand(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007714. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__rand_0000ca38)();
  return iVar1;
}

// ==== 00007718 _strcmp ====
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _strcmp(char *param_1,char *param_2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00007720. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__strcmp_0000ca40)((int)param_1);
  return iVar1;
}

// ==== 000079e0 objc_stub::address ====
ID __objc_msgSend_stub objc_stub::address(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"address");
  return IVar1;
}

// ==== 00007a00 objc_stub::arrayWithObjects:count: ====
ID __objc_msgSend_stub objc_stub::arrayWithObjects_count_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"arrayWithObjects:count:");
  return IVar1;
}

// ==== 00007a20 objc_stub::auOutputBus ====
ID __objc_msgSend_stub objc_stub::auOutputBus(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"auOutputBus");
  return IVar1;
}

// ==== 00007a40 objc_stub::audioBufferList ====
ID __objc_msgSend_stub objc_stub::audioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"audioBufferList");
  return IVar1;
}

// ==== 00007a60 objc_stub::busType ====
ID __objc_msgSend_stub objc_stub::busType(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"busType");
  return IVar1;
}

// ==== 00007a80 objc_stub::channelCount ====
ID __objc_msgSend_stub objc_stub::channelCount(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"channelCount");
  return IVar1;
}

// ==== 00007aa0 objc_stub::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
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

// ==== 00007ac0 objc_stub::createTreeWithChildren: ====
ID __objc_msgSend_stub objc_stub::createTreeWithChildren_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"createTreeWithChildren:");
  return IVar1;
}

// ==== 00007ae0 objc_stub::defaultFormat ====
ID __objc_msgSend_stub objc_stub::defaultFormat(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"defaultFormat");
  return IVar1;
}

// ==== 00007b00 objc_stub::defaultManager ====
ID __objc_msgSend_stub objc_stub::defaultManager(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"defaultManager");
  return IVar1;
}

// ==== 00007b20 objc_stub::delegate ====
ID __objc_msgSend_stub objc_stub::delegate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"delegate");
  return IVar1;
}

// ==== 00007b40 objc_stub::errorWithDomain:code:userInfo: ====
ID __objc_msgSend_stub objc_stub::errorWithDomain_code_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"errorWithDomain:code:userInfo:");
  return IVar1;
}

// ==== 00007b60 objc_stub::exceptionWithName:reason:userInfo: ====
ID __objc_msgSend_stub objc_stub::exceptionWithName_reason_userInfo_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"exceptionWithName:reason:userInfo:");
  return IVar1;
}

// ==== 00007b80 objc_stub::fileExistsAtPath: ====
ID __objc_msgSend_stub objc_stub::fileExistsAtPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"fileExistsAtPath:");
  return IVar1;
}

// ==== 00007ba0 objc_stub::fileSystemRepresentation ====
ID __objc_msgSend_stub objc_stub::fileSystemRepresentation(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"fileSystemRepresentation");
  return IVar1;
}

// ==== 00007bc0 objc_stub::fileURLWithPath: ====
ID __objc_msgSend_stub objc_stub::fileURLWithPath_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"fileURLWithPath:");
  return IVar1;
}

// ==== 00007be0 objc_stub::format ====
ID __objc_msgSend_stub objc_stub::format(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"format");
  return IVar1;
}

// ==== 00007c00 objc_stub::initStandardFormatWithSampleRate:channels: ====
ID __objc_msgSend_stub objc_stub::initStandardFormatWithSampleRate_channels_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initStandardFormatWithSampleRate:channels:");
  return IVar1;
}

// ==== 00007c20 objc_stub::initWithAudioUnit:busType:busses: ====
ID __objc_msgSend_stub objc_stub::initWithAudioUnit_busType_busses_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithAudioUnit:busType:busses:");
  return IVar1;
}

// ==== 00007c40 objc_stub::initWithFormat:error: ====
ID __objc_msgSend_stub objc_stub::initWithFormat_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithFormat:error:");
  return IVar1;
}

// ==== 00007c60 objc_stub::initWithPCMFormat:frameCapacity: ====
ID __objc_msgSend_stub objc_stub::initWithPCMFormat_frameCapacity_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"initWithPCMFormat:frameCapacity:");
  return IVar1;
}

// ==== 00007c80 objc_stub::loopingFilePlaybackAudioUnit:fileLoadError:fileURL: ====
ID __objc_msgSend_stub objc_stub::loopingFilePlaybackAudioUnit_fileLoadError_fileURL_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)
                    (self,"loopingFilePlaybackAudioUnit:fileLoadError:fileURL:");
  return IVar1;
}

// ==== 00007ca0 objc_stub::maximumFramesToRender ====
ID __objc_msgSend_stub objc_stub::maximumFramesToRender(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"maximumFramesToRender");
  return IVar1;
}

// ==== 00007cc0 objc_stub::moveItemAtURL:toURL:error: ====
ID __objc_msgSend_stub objc_stub::moveItemAtURL_toURL_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"moveItemAtURL:toURL:error:");
  return IVar1;
}

// ==== 00007ce0 objc_stub::mutableAudioBufferList ====
ID __objc_msgSend_stub objc_stub::mutableAudioBufferList(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"mutableAudioBufferList");
  return IVar1;
}

// ==== 00007d00 objc_stub::path ====
ID __objc_msgSend_stub objc_stub::path(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"path");
  return IVar1;
}

// ==== 00007d20 objc_stub::pathExtension ====
ID __objc_msgSend_stub objc_stub::pathExtension(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"pathExtension");
  return IVar1;
}

// ==== 00007d40 objc_stub::prepareToPlay ====
ID __objc_msgSend_stub objc_stub::prepareToPlay(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"prepareToPlay");
  return IVar1;
}

// ==== 00007d60 objc_stub::raise ====
ID __objc_msgSend_stub objc_stub::raise(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"raise");
  return IVar1;
}

// ==== 00007d80 objc_stub::removeItemAtPath:error: ====
ID __objc_msgSend_stub objc_stub::removeItemAtPath_error_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"removeItemAtPath:error:");
  return IVar1;
}

// ==== 00007da0 objc_stub::reset ====
ID __objc_msgSend_stub objc_stub::reset(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"reset");
  return IVar1;
}

// ==== 00007dc0 objc_stub::sampleRate ====
ID __objc_msgSend_stub objc_stub::sampleRate(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"sampleRate");
  return IVar1;
}

// ==== 00007de0 objc_stub::setDefaultFormat: ====
ID __objc_msgSend_stub objc_stub::setDefaultFormat_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setDefaultFormat:");
  return IVar1;
}

// ==== 00007e00 objc_stub::setImplementorStringFromValueCallback: ====
ID __objc_msgSend_stub objc_stub::setImplementorStringFromValueCallback_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorStringFromValueCallback:");
  return IVar1;
}

// ==== 00007e20 objc_stub::setImplementorValueObserver: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueObserver_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueObserver:");
  return IVar1;
}

// ==== 00007e40 objc_stub::setImplementorValueProvider: ====
ID __objc_msgSend_stub objc_stub::setImplementorValueProvider_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setImplementorValueProvider:");
  return IVar1;
}

// ==== 00007e60 objc_stub::setMaximumChannelCount: ====
ID __objc_msgSend_stub objc_stub::setMaximumChannelCount_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setMaximumChannelCount:");
  return IVar1;
}

// ==== 00007e80 objc_stub::setMaximumFramesToRender: ====
ID __objc_msgSend_stub objc_stub::setMaximumFramesToRender_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setMaximumFramesToRender:");
  return IVar1;
}

// ==== 00007ea0 objc_stub::setRenderResourcesAllocated: ====
ID __objc_msgSend_stub objc_stub::setRenderResourcesAllocated_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setRenderResourcesAllocated:");
  return IVar1;
}

// ==== 00007ec0 objc_stub::setUrl: ====
ID __objc_msgSend_stub objc_stub::setUrl_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setUrl:");
  return IVar1;
}

// ==== 00007ee0 objc_stub::setValue: ====
ID __objc_msgSend_stub objc_stub::setValue_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"setValue:");
  return IVar1;
}

// ==== 00007f00 objc_stub::stringByReplacingOccurrencesOfString:withString: ====
ID __objc_msgSend_stub objc_stub::stringByReplacingOccurrencesOfString_withString_(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)
                    (self,"stringByReplacingOccurrencesOfString:withString:");
  return IVar1;
}

// ==== 00007f20 objc_stub::url ====
ID __objc_msgSend_stub objc_stub::url(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"url");
  return IVar1;
}

// ==== 00007f40 objc_stub::value ====
ID __objc_msgSend_stub objc_stub::value(ID self,...)

{
  ID IVar1;
  
  IVar1 = (*(code *)PTR__objc_msgSend_0000c008)(self,"value");
  return IVar1;
}

// ==== 0001c201 AUAudioUnitBus::initWithFormat:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBus::initWithFormat_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c301 AUAudioUnitBusArray::initWithAudioUnit:busType:busses: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUAudioUnitBusArray::initWithAudioUnit_busType_busses_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c401 AUParameterTree::createParameterWithIdentifier:name:address:min:max:unit:unitName:flags:valueStrings:dependentParameters: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::
   createParameterWithIdentifier_name_address_min_max_unit_unitName_flags_valueStrings_dependentParameters_
             (ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c402 AUParameterTree::setValue: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::setValue_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c403 AUParameterTree::createTreeWithChildren: ====
/* WARNING: Control flow encountered bad instruction data */

ID AUParameterTree::createTreeWithChildren_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c501 AVAudioFormat::initStandardFormatWithSampleRate:channels: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioFormat::initStandardFormatWithSampleRate_channels_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c601 AVAudioPCMBuffer::initWithPCMFormat:frameCapacity: ====
/* WARNING: Control flow encountered bad instruction data */

ID AVAudioPCMBuffer::initWithPCMFormat_frameCapacity_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c701 NSArray::arrayWithObjects:count: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSArray::arrayWithObjects_count_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c801 NSError::errorWithDomain:code:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSError::errorWithDomain_code_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c901 NSException::exceptionWithName:reason:userInfo: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::exceptionWithName_reason_userInfo_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001c902 NSException::raise ====
/* WARNING: Control flow encountered bad instruction data */

ID NSException::raise(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001ca01 NSFileManager::defaultManager ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::defaultManager(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001ca02 NSFileManager::fileExistsAtPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::fileExistsAtPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001ca03 NSFileManager::removeItemAtPath:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::removeItemAtPath_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001ca04 NSFileManager::moveItemAtURL:toURL:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSFileManager::moveItemAtURL_toURL_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cb01 NSURL::fileURLWithPath: ====
/* WARNING: Control flow encountered bad instruction data */

ID NSURL::fileURLWithPath_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc01 TrackedAUAudioUnit::reset ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::reset(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc02 TrackedAUAudioUnit::dealloc ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::dealloc(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc03 TrackedAUAudioUnit::deallocateRenderResources ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::deallocateRenderResources(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc04 TrackedAUAudioUnit::initWithComponentDescription:options:error: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::initWithComponentDescription_options_error_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc05 TrackedAUAudioUnit::allocateRenderResourcesAndReturnError: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::allocateRenderResourcesAndReturnError_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc06 TrackedAUAudioUnit::setDefaultFormat: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setDefaultFormat_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc07 TrackedAUAudioUnit::defaultFormat ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::defaultFormat(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001cc08 TrackedAUAudioUnit::setMaximumFramesToRender: ====
/* WARNING: Control flow encountered bad instruction data */

ID TrackedAUAudioUnit::setMaximumFramesToRender_(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

// ==== 0001de00 _objc_msgSend ====
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ID _objc_msgSend(ID self,SEL op,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

