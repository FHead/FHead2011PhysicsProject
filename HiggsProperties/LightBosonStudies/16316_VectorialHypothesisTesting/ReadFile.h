#ifndef ReadFile_H_16234
#define ReadFile_H_16234

#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"

#include "Likelihood.h"
#include "ReducedLikelihood.h"

using namespace RealLikelihood;

class FileHandle
{
public:
   TFile *File;
   TTree *Tree;
   char Cut;
   bool ReUse;
   Likelihood Messenger;
   int CurrentEvent;
   int EntryCount;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;
   bool HasMoreEvents;
public:
   FileHandle(string FileName, char cut, bool reuse, bool IsEM);
   ~FileHandle();
   bool IsThereNext();
   bool ReadFirstEvent();
   Likelihood GetNextEvent();
};



#endif

