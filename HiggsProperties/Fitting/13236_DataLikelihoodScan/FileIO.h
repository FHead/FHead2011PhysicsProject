//---------------------------------------------------------------------------
#ifndef FILEIO_H_13167_AJSDKGJASDKGJASKDGJADSKGJKADSJG
#define FILEIO_H_13167_AJSDKGJASDKGJASKDGJADSKGJKADSJG
//---------------------------------------------------------------------------
#include <vector>
#include <string>
//---------------------------------------------------------------------------
#include "FitClass.h"
//---------------------------------------------------------------------------
#define DEFAULT_PROCESS 153332
#define EVENTLIMIT 6000
//---------------------------------------------------------------------------
bool ReadEvents(std::vector<SingleEvent> &EventsEM, std::vector<SingleEvent> &EventsME,
   std::vector<SingleEvent> &EventsEE, std::vector<SingleEvent> &EventsMM,
   std::string FileName, bool Capital, int Process = DEFAULT_PROCESS,
   double MaxWeight = 1, bool Is7TeV = false, bool AlternativeWeight = false,
   int TargetToy = -1, bool EMMETogether = false, bool ChannelFromID = true,
   bool IgnoreWeight = false, double EventLimitFactor = 1,
   bool FillInJacobian = false);
int GetEventCount(double Mean, double Sigma);
int PullEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, double Mean, double Sigma,
   bool Recycle = false);
double PullAndReweightEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, double Mean);
int PullToyEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, int ToyNumber);
double GetCombinedWeight(double Values[154][13]);
//---------------------------------------------------------------------------
#endif
