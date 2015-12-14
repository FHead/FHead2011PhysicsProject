//---------------------------------------------------------------------------
#ifndef FILEIO_H_13167_AJSDKGJASDKGJASKDGJADSKGJKADSJG
#define FILEIO_H_13167_AJSDKGJASDKGJASKDGJADSKGJKADSJG
//---------------------------------------------------------------------------
#include <vector>
#include <string>
//---------------------------------------------------------------------------
#include "FitClass.h"
//---------------------------------------------------------------------------
#include "AngleConversion.h"
//---------------------------------------------------------------------------
#define DEFAULT_PROCESS 153332
#define EVENTLIMIT 6000
//---------------------------------------------------------------------------
#define JACOBIAN_NONE 0
#define JACOBIAN_SIGNAL 1
#define JACOBIAN_BACKGROUND 2
//---------------------------------------------------------------------------
bool ReadEvents(std::vector<SingleEvent> &EventsEM, std::vector<SingleEvent> &EventsME,
   std::vector<SingleEvent> &EventsEE, std::vector<SingleEvent> &EventsMM,
   std::string FileName, bool Capital, int Process = DEFAULT_PROCESS,
   double MaxWeight = 1, bool Is7TeV = false, bool AlternativeWeight = false,
   int TargetToy = -1, bool EMMETogether = false, bool ChannelFromID = true,   // Here the ID refers to "channel" branch
   bool IgnoreWeight = false, double EventLimitFactor = 1,
   int FillInJacobian = 0);
int GetEventCount(double Mean, double Sigma);
int PullEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, double Mean, double Sigma,
   bool Recycle = false);
double PullAndReweightEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, double Mean);
int PullToyEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, int ToyNumber);
double GetCombinedWeight(double Values[154][13]);
void ExportSimpleTree(std::string FileName, std::vector<SingleEvent> &Events);
bool WillBeSwapped(LeptonVectors &Leptons);
//---------------------------------------------------------------------------
#endif
