// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME sourcedIL1Classes

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/L1Classes.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisCSCTFDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisCSCTFDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisCSCTFDataFormat*)
   {
      ::L1Analysis::L1AnalysisCSCTFDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisCSCTFDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisCSCTFDataFormat", "include/L1AnalysisCSCTFDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisCSCTFDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisCSCTFDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisCSCTFDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisCSCTFDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisCSCTFDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisCSCTFDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisCSCTFDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisCSCTFDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisCSCTFDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisCSCTFDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisCSCTFDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisCSCTFDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisCSCTFDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisCaloTPDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisCaloTPDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisCaloTPDataFormat*)
   {
      ::L1Analysis::L1AnalysisCaloTPDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisCaloTPDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisCaloTPDataFormat", "include/L1AnalysisCaloTPDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisCaloTPDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisCaloTPDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisCaloTPDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisCaloTPDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisCaloTPDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisCaloTPDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisCaloTPDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisCaloTPDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisCaloTPDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisCaloTPDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisCaloTPDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisCaloTPDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisCaloTPDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisDTTFDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisDTTFDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisDTTFDataFormat*)
   {
      ::L1Analysis::L1AnalysisDTTFDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisDTTFDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisDTTFDataFormat", "include/L1AnalysisDTTFDataFormat.h", 17,
                  typeid(::L1Analysis::L1AnalysisDTTFDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisDTTFDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisDTTFDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisDTTFDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisDTTFDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisDTTFDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisDTTFDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisDTTFDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisDTTFDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisDTTFDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisDTTFDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisDTTFDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisDTTFDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisEventDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisEventDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisEventDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisEventDataFormat*)
   {
      ::L1Analysis::L1AnalysisEventDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisEventDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisEventDataFormat", "include/L1AnalysisEventDataFormat.h", 18,
                  typeid(::L1Analysis::L1AnalysisEventDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisEventDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisEventDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisEventDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisEventDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisEventDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisEventDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisEventDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisEventDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisEventDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisEventDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisEventDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisEventDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisEventDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisEventDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisGCTDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisGCTDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisGCTDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisGCTDataFormat*)
   {
      ::L1Analysis::L1AnalysisGCTDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisGCTDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisGCTDataFormat", "include/L1AnalysisGCTDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisGCTDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisGCTDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisGCTDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisGCTDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisGCTDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisGCTDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisGCTDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisGCTDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisGCTDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisGCTDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGCTDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisGCTDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGCTDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisGCTDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisGCTDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisGMTDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisGMTDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisGMTDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisGMTDataFormat*)
   {
      ::L1Analysis::L1AnalysisGMTDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisGMTDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisGMTDataFormat", "include/L1AnalysisGMTDataFormat.h", 16,
                  typeid(::L1Analysis::L1AnalysisGMTDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisGMTDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisGMTDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisGMTDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisGMTDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisGMTDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisGMTDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisGMTDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisGMTDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisGMTDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGMTDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisGMTDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGMTDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisGMTDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisGMTDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisGTDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisGTDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisGTDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisGTDataFormat*)
   {
      ::L1Analysis::L1AnalysisGTDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisGTDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisGTDataFormat", "include/L1AnalysisGTDataFormat.h", 16,
                  typeid(::L1Analysis::L1AnalysisGTDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisGTDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisGTDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisGTDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisGTDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisGTDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisGTDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisGTDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisGTDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisGTDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGTDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisGTDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGTDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisGTDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisGTDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisGeneratorDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisGeneratorDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisGeneratorDataFormat*)
   {
      ::L1Analysis::L1AnalysisGeneratorDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisGeneratorDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisGeneratorDataFormat", "include/L1AnalysisGeneratorDataFormat.h", 17,
                  typeid(::L1Analysis::L1AnalysisGeneratorDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisGeneratorDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisGeneratorDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisGeneratorDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisGeneratorDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisGeneratorDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisGeneratorDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisGeneratorDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGeneratorDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisGeneratorDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisGeneratorDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisGeneratorDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisGeneratorDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisL1ExtraDataFormat*)
   {
      ::L1Analysis::L1AnalysisL1ExtraDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisL1ExtraDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisL1ExtraDataFormat", "include/L1AnalysisL1ExtraDataFormat.h", 16,
                  typeid(::L1Analysis::L1AnalysisL1ExtraDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisL1ExtraDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisL1ExtraDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisL1ExtraDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1ExtraDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1ExtraDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisL1ExtraDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisL1MenuDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisL1MenuDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisL1MenuDataFormat*)
   {
      ::L1Analysis::L1AnalysisL1MenuDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisL1MenuDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisL1MenuDataFormat", "include/L1AnalysisL1MenuDataFormat.h", 8,
                  typeid(::L1Analysis::L1AnalysisL1MenuDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisL1MenuDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisL1MenuDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisL1MenuDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisL1MenuDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisL1MenuDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisL1MenuDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisL1MenuDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1MenuDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisL1MenuDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1MenuDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisL1MenuDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisL1MenuDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRCTDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRCTDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRCTDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRCTDataFormat*)
   {
      ::L1Analysis::L1AnalysisRCTDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRCTDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRCTDataFormat", "include/L1AnalysisRCTDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRCTDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRCTDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRCTDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRCTDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRCTDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRCTDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRCTDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRCTDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRCTDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRCTDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRCTDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRCTDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRCTDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRCTDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRCTDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoClusterDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoClusterDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoClusterDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoClusterDataFormat", "include/L1AnalysisRecoClusterDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoClusterDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoClusterDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoClusterDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoClusterDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoClusterDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoClusterDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoClusterDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoJetDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoJetDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoJetDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoJetDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoJetDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoJetDataFormat", "include/L1AnalysisRecoJetDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoJetDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoJetDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoJetDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoJetDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoJetDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoJetDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoJetDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoJetDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoJetDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoJetDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoJetDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoJetDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoJetDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoMetDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoMetDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoMetDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoMetDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoMetDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoMetDataFormat", "include/L1AnalysisRecoMetDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoMetDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoMetDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoMetDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoMetDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoMetDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoMetDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoMetDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoMetDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoMetDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoMetDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoMetDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoMetDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoMetDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoMuonDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoMuonDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoMuonDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoMuonDataFormat", "include/L1AnalysisRecoMuonDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoMuonDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoMuonDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoMuonDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoMuonDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoMuonDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoMuonDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoMuonDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoTrackDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoTrackDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoTrackDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoTrackDataFormat", "include/L1AnalysisRecoTrackDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoTrackDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoTrackDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoTrackDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoTrackDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoTrackDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoTrackDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoTrackDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisRecoVertexDataFormat*)
   {
      ::L1Analysis::L1AnalysisRecoVertexDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisRecoVertexDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisRecoVertexDataFormat", "include/L1AnalysisRecoVertexDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisRecoVertexDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisRecoVertexDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisRecoVertexDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisRecoVertexDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoVertexDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisRecoVertexDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisRecoVertexDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisSimulationDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisSimulationDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisSimulationDataFormat*)
   {
      ::L1Analysis::L1AnalysisSimulationDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisSimulationDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisSimulationDataFormat", "include/L1AnalysisSimulationDataFormat.h", 15,
                  typeid(::L1Analysis::L1AnalysisSimulationDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisSimulationDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisSimulationDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisSimulationDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisSimulationDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisSimulationDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisSimulationDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisSimulationDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisSimulationDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisSimulationDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisSimulationDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisSimulationDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisSimulationDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_Dictionary();
   static void L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_TClassManip(TClass*);
   static void *new_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p = 0);
   static void *newArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(Long_t size, void *p);
   static void delete_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p);
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p);
   static void destruct_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)
   {
      ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat));
      static ::ROOT::TGenericClassInfo 
         instance("L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat", "include/L1AnalysisL1ExtraUpgradeDataFormat.h", 16,
                  typeid(::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_Dictionary, isa_proxy, 4,
                  sizeof(::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat) );
      instance.SetNew(&new_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat);
      instance.SetNewArray(&newArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat);
      instance.SetDelete(&delete_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat);
      instance.SetDeleteArray(&deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat);
      instance.SetDestructor(&destruct_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)
   {
      return GenerateInitInstanceLocal((::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)0x0)->GetClass();
      L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_TClassManip(theClass);
   return theClass;
   }

   static void L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisCSCTFDataFormat : new ::L1Analysis::L1AnalysisCSCTFDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisCSCTFDataFormat[nElements] : new ::L1Analysis::L1AnalysisCSCTFDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisCSCTFDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisCSCTFDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisCSCTFDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisCSCTFDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisCSCTFDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisCaloTPDataFormat : new ::L1Analysis::L1AnalysisCaloTPDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisCaloTPDataFormat[nElements] : new ::L1Analysis::L1AnalysisCaloTPDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisCaloTPDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisCaloTPDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisCaloTPDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisCaloTPDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisCaloTPDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisDTTFDataFormat : new ::L1Analysis::L1AnalysisDTTFDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisDTTFDataFormat[nElements] : new ::L1Analysis::L1AnalysisDTTFDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisDTTFDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisDTTFDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisDTTFDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisDTTFDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisDTTFDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisEventDataFormat : new ::L1Analysis::L1AnalysisEventDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisEventDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisEventDataFormat[nElements] : new ::L1Analysis::L1AnalysisEventDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisEventDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisEventDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisEventDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisEventDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisEventDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGCTDataFormat : new ::L1Analysis::L1AnalysisGCTDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisGCTDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGCTDataFormat[nElements] : new ::L1Analysis::L1AnalysisGCTDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisGCTDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisGCTDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisGCTDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisGCTDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisGCTDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGMTDataFormat : new ::L1Analysis::L1AnalysisGMTDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisGMTDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGMTDataFormat[nElements] : new ::L1Analysis::L1AnalysisGMTDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisGMTDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisGMTDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisGMTDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisGMTDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisGMTDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGTDataFormat : new ::L1Analysis::L1AnalysisGTDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisGTDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGTDataFormat[nElements] : new ::L1Analysis::L1AnalysisGTDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisGTDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisGTDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisGTDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisGTDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisGTDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGeneratorDataFormat : new ::L1Analysis::L1AnalysisGeneratorDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisGeneratorDataFormat[nElements] : new ::L1Analysis::L1AnalysisGeneratorDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisGeneratorDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisGeneratorDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisGeneratorDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisGeneratorDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisGeneratorDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1ExtraDataFormat : new ::L1Analysis::L1AnalysisL1ExtraDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1ExtraDataFormat[nElements] : new ::L1Analysis::L1AnalysisL1ExtraDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisL1ExtraDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisL1ExtraDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisL1ExtraDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisL1ExtraDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisL1ExtraDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1MenuDataFormat : new ::L1Analysis::L1AnalysisL1MenuDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1MenuDataFormat[nElements] : new ::L1Analysis::L1AnalysisL1MenuDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisL1MenuDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisL1MenuDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisL1MenuDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisL1MenuDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisL1MenuDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRCTDataFormat : new ::L1Analysis::L1AnalysisRCTDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRCTDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRCTDataFormat[nElements] : new ::L1Analysis::L1AnalysisRCTDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRCTDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRCTDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRCTDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRCTDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRCTDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoClusterDataFormat : new ::L1Analysis::L1AnalysisRecoClusterDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoClusterDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoClusterDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoClusterDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoClusterDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoClusterDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoClusterDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoClusterDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoJetDataFormat : new ::L1Analysis::L1AnalysisRecoJetDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoJetDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoJetDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoJetDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoJetDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoJetDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoJetDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoJetDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoMetDataFormat : new ::L1Analysis::L1AnalysisRecoMetDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoMetDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoMetDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoMetDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoMetDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoMetDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoMetDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoMetDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoMuonDataFormat : new ::L1Analysis::L1AnalysisRecoMuonDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoMuonDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoMuonDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoMuonDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoMuonDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoMuonDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoMuonDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoMuonDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoTrackDataFormat : new ::L1Analysis::L1AnalysisRecoTrackDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoTrackDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoTrackDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoTrackDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoTrackDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoTrackDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoTrackDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoTrackDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoVertexDataFormat : new ::L1Analysis::L1AnalysisRecoVertexDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisRecoVertexDataFormat[nElements] : new ::L1Analysis::L1AnalysisRecoVertexDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisRecoVertexDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisRecoVertexDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisRecoVertexDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisRecoVertexDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisRecoVertexDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisSimulationDataFormat : new ::L1Analysis::L1AnalysisSimulationDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisSimulationDataFormat[nElements] : new ::L1Analysis::L1AnalysisSimulationDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisSimulationDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisSimulationDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisSimulationDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisSimulationDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisSimulationDataFormat

namespace ROOT {
   // Wrappers around operator new
   static void *new_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat : new ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat;
   }
   static void *newArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat[nElements] : new ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat[nElements];
   }
   // Wrapper around operator delete
   static void delete_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p) {
      delete ((::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)p);
   }
   static void deleteArray_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p) {
      delete [] ((::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat*)p);
   }
   static void destruct_L1AnalysiscLcLL1AnalysisL1ExtraUpgradeDataFormat(void *p) {
      typedef ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat

namespace ROOT {
   static TClass *vectorlEunsignedsPlonggR_Dictionary();
   static void vectorlEunsignedsPlonggR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPlonggR(void *p = 0);
   static void *newArray_vectorlEunsignedsPlonggR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPlonggR(void *p);
   static void deleteArray_vectorlEunsignedsPlonggR(void *p);
   static void destruct_vectorlEunsignedsPlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned long>*)
   {
      vector<unsigned long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned long>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned long>", -2, "vector", 458,
                  typeid(vector<unsigned long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPlonggR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned long>) );
      instance.SetNew(&new_vectorlEunsignedsPlonggR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPlonggR);
      instance.SetDelete(&delete_vectorlEunsignedsPlonggR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPlonggR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<unsigned long>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned long>*)0x0)->GetClass();
      vectorlEunsignedsPlonggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPlonggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned long> : new vector<unsigned long>;
   }
   static void *newArray_vectorlEunsignedsPlonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned long>[nElements] : new vector<unsigned long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPlonggR(void *p) {
      delete ((vector<unsigned long>*)p);
   }
   static void deleteArray_vectorlEunsignedsPlonggR(void *p) {
      delete [] ((vector<unsigned long>*)p);
   }
   static void destruct_vectorlEunsignedsPlonggR(void *p) {
      typedef vector<unsigned long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned long>

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 458,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<unsigned int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned int>*)0x0)->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete ((vector<unsigned int>*)p);
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] ((vector<unsigned int>*)p);
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlEshortgR_Dictionary();
   static void vectorlEshortgR_TClassManip(TClass*);
   static void *new_vectorlEshortgR(void *p = 0);
   static void *newArray_vectorlEshortgR(Long_t size, void *p);
   static void delete_vectorlEshortgR(void *p);
   static void deleteArray_vectorlEshortgR(void *p);
   static void destruct_vectorlEshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<short>*)
   {
      vector<short> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<short>", -2, "vector", 458,
                  typeid(vector<short>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<short>) );
      instance.SetNew(&new_vectorlEshortgR);
      instance.SetNewArray(&newArray_vectorlEshortgR);
      instance.SetDelete(&delete_vectorlEshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEshortgR);
      instance.SetDestructor(&destruct_vectorlEshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<short> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<short>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<short>*)0x0)->GetClass();
      vectorlEshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEshortgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<short> : new vector<short>;
   }
   static void *newArray_vectorlEshortgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<short>[nElements] : new vector<short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEshortgR(void *p) {
      delete ((vector<short>*)p);
   }
   static void deleteArray_vectorlEshortgR(void *p) {
      delete [] ((vector<short>*)p);
   }
   static void destruct_vectorlEshortgR(void *p) {
      typedef vector<short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<short>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 458,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 458,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 458,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEboolgR_Dictionary();
   static void vectorlEboolgR_TClassManip(TClass*);
   static void *new_vectorlEboolgR(void *p = 0);
   static void *newArray_vectorlEboolgR(Long_t size, void *p);
   static void delete_vectorlEboolgR(void *p);
   static void deleteArray_vectorlEboolgR(void *p);
   static void destruct_vectorlEboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bool>*)
   {
      vector<bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bool>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bool>", -2, "vector", 2116,
                  typeid(vector<bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEboolgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<bool>) );
      instance.SetNew(&new_vectorlEboolgR);
      instance.SetNewArray(&newArray_vectorlEboolgR);
      instance.SetDelete(&delete_vectorlEboolgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboolgR);
      instance.SetDestructor(&destruct_vectorlEboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<bool>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bool>*)0x0)->GetClass();
      vectorlEboolgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool> : new vector<bool>;
   }
   static void *newArray_vectorlEboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool>[nElements] : new vector<bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboolgR(void *p) {
      delete ((vector<bool>*)p);
   }
   static void deleteArray_vectorlEboolgR(void *p) {
      delete [] ((vector<bool>*)p);
   }
   static void destruct_vectorlEboolgR(void *p) {
      typedef vector<bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bool>

namespace ROOT {
   static TClass *vectorlEULong64_tgR_Dictionary();
   static void vectorlEULong64_tgR_TClassManip(TClass*);
   static void *new_vectorlEULong64_tgR(void *p = 0);
   static void *newArray_vectorlEULong64_tgR(Long_t size, void *p);
   static void delete_vectorlEULong64_tgR(void *p);
   static void deleteArray_vectorlEULong64_tgR(void *p);
   static void destruct_vectorlEULong64_tgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ULong64_t>*)
   {
      vector<ULong64_t> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ULong64_t>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ULong64_t>", -2, "vector", 458,
                  typeid(vector<ULong64_t>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEULong64_tgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<ULong64_t>) );
      instance.SetNew(&new_vectorlEULong64_tgR);
      instance.SetNewArray(&newArray_vectorlEULong64_tgR);
      instance.SetDelete(&delete_vectorlEULong64_tgR);
      instance.SetDeleteArray(&deleteArray_vectorlEULong64_tgR);
      instance.SetDestructor(&destruct_vectorlEULong64_tgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ULong64_t> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<ULong64_t>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEULong64_tgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ULong64_t>*)0x0)->GetClass();
      vectorlEULong64_tgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEULong64_tgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEULong64_tgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ULong64_t> : new vector<ULong64_t>;
   }
   static void *newArray_vectorlEULong64_tgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ULong64_t>[nElements] : new vector<ULong64_t>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEULong64_tgR(void *p) {
      delete ((vector<ULong64_t>*)p);
   }
   static void deleteArray_vectorlEULong64_tgR(void *p) {
      delete [] ((vector<ULong64_t>*)p);
   }
   static void destruct_vectorlEULong64_tgR(void *p) {
      typedef vector<ULong64_t> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ULong64_t>

namespace ROOT {
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 458,
                  typeid(vector<TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace {
  void TriggerDictionaryInitialization_L1Classes_Impl() {
    static const char* headers[] = {
"include/L1Classes.h",
0
    };
    static const char* includePaths[] = {
"/Users/yichen/Programs/root/root-6.06.08/include",
"/Users/yichen/PhysicsWorkspace/L1TriggerUpgrade/CommonCode/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "L1Classes dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisCSCTFDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisCaloTPDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisDTTFDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisEventDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisGCTDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisGMTDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisGTDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisGeneratorDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisL1ExtraDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisL1MenuDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRCTDataFormat;}
namespace L1Analysis{class __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoClusterDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoJetDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoMetDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoMuonDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoTrackDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisRecoVertexDataFormat;}
namespace L1Analysis{class __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisSimulationDataFormat;}
namespace L1Analysis{struct __attribute__((annotate("$clingAutoload$include/L1Classes.h")))  L1AnalysisL1ExtraUpgradeDataFormat;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "L1Classes dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/L1Classes.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"L1Analysis::L1AnalysisCSCTFDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisCaloTPDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisDTTFDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisEventDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisGCTDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisGMTDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisGTDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisGeneratorDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisL1ExtraDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisL1MenuDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRCTDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoClusterDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoJetDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoMetDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoMuonDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoTrackDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisRecoVertexDataFormat", payloadCode, "@",
"L1Analysis::L1AnalysisSimulationDataFormat", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("L1Classes",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_L1Classes_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_L1Classes_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_L1Classes() {
  TriggerDictionaryInitialization_L1Classes_Impl();
}
