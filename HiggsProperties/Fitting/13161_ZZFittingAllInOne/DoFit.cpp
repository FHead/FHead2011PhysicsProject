#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"
#include "DataHelper.h"
#include "PlotHelper2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "MEFunctions.h"
#include "CalculateME.h"

#include "FitClass.h"

#define USE_TIGHT_CUT
#define MAX_SIGNAL_WEIGHT 1.0e-12
#define MAX_BACKGROUND_WEIGHT 2.0e-14
#define BackgroundNormalizationCorrection 1

#define FINALSTATE_2e2mu 0
#define FINALSTATE_4e4mu 1
#define FINALSTATE_mixed 2

int main(int argc, char *argv[]);
double GetPhi(double x, double y);
bool PassLooseCut(LeptonVectors Event);
bool PassTightCut(LeptonVectors Event);
SingleEvent GiveMeSignalPoint(double As[8], int FinalState = FINALSTATE_2e2mu);
SingleEvent GiveMeBackgroundPoint(int FinalState = FINALSTATE_2e2mu);
SingleEvent CalculateLikelihoods(EventParameters &Event, bool Is2e2mu);
vector<double (*)(LeptonVectors &)> GetSignalMEs(bool Is2e2mu);
double GetWeight(double As[8], EventParameters &Event, bool Is2e2mu);

#define PI 3.14159265358979323846264338327950288479716939937510

// #define USE_LOOSE_CUT
#define USE_TIGHT_CUT

int main(int argc, char *argv[])
{
   int SignalDatasetSize = 30, BackgroundDatasetSize = 30;

   if(argc < 11)
   {
      cerr << "Usage: " << argv[0]
         << " SignalDatasetSize BackgroundDatasetSize A1ZZ A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA A1L1 [Seed]"
         << endl;
      return -1;
   }

   SignalDatasetSize = atoi(argv[1]);
   BackgroundDatasetSize = atoi(argv[2]);

   double A1ZZ = atof(argv[3]);
   double A2ZZ = atof(argv[4]);
   double A3ZZ = atof(argv[5]);
   double A2ZA = atof(argv[6]);
   double A3ZA = atof(argv[7]);
   double A2AA = atof(argv[8]);
   double A3AA = atof(argv[9]);
   double A1L1ZZ = atof(argv[10]);
   double A1LQZZ = 0;

   double As[] = {A1ZZ, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA, A1L1ZZ, A1LQZZ};

   if(argc >= 12)
      srand(atoi(argv[10]));
   else
      srand(time(NULL));

   vector<FitResultSummary> Results;

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 127; i++)
   {
      if(i != 63)
         continue;

      string As = "NNNNNNNN";
      if((i / 1) % 2 == 1)    As[0] = 'Y';
      if((i / 2) % 2 == 1)    As[1] = 'Y';
      if((i / 4) % 2 == 1)    As[2] = 'Y';
      if((i / 8) % 2 == 1)    As[3] = 'Y';
      if((i / 16) % 2 == 1)   As[4] = 'Y';
      if((i / 32) % 2 == 1)   As[5] = 'Y';
      if((i / 64) % 2 == 1)   As[6] = 'Y';
      if((i / 128) % 2 == 1)   As[7] = 'Y';

      string Phases = "NNNNNNNN";

      string Fs = "NNNN";
      if(BackgroundDatasetSize > 0)
         Fs = "YNNN";

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = A2ZZ / A1ZZ;
      AValues[1] = A3ZZ / A1ZZ;
      AValues[2] = A2ZA / A1ZZ;
      AValues[3] = A3ZA / A1ZZ;
      AValues[4] = A2AA / A1ZZ;
      AValues[5] = A3AA / A1ZZ;
      AValues[6] = A1L1ZZ / A1ZZ;
      AValues[7] = A1LQZZ / A1ZZ;

      Configurations.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, ((Fs[2] == 'Y') ? 0.5 : 0), 0),
         ListToVector(2, 0, 0)));
   }

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 100;

   for(int iT = 0; iT < FitCount; iT++)
   {
      for(int iE = 0; iE < SignalDatasetSize; iE++)
      {
         SingleEvent Event = GiveMeSignalPoint(As, true);
         Fits.AddPoint(Event);
      }
      for(int iE = 0; iE < BackgroundDatasetSize; iE++)
      {
         SingleEvent Event = GiveMeBackgroundPoint(true);
         Fits.AddPoint(Event);
      }

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);
      }

      Fits.ClearPoints();
   }

   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";
   BranchList = BranchList + ":N1:N2:Fem:Fme:Fee:Fmm";
   BranchList = BranchList + ":A2ZZA1ZZError:A2ZZPhaseError:A3ZZA1ZZError:A3ZZPhaseError";
   BranchList = BranchList + ":A2ZAA1ZZError:A2ZAPhaseError:A3ZAA1ZZError:A3ZAPhaseError";
   BranchList = BranchList + ":A2AAA1ZZError:A2AAPhaseError:A3AAA1ZZError:A3AAPhaseError";
   BranchList = BranchList + ":N1Error:N2Error:FemError:FmeError:FeeError:FmmError";
   BranchList = BranchList + ":EDM:Status:Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";
   BranchList = BranchList + ":RatioFloats:NFloats:I1ZZModification:TruthNLL:BestNLL";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].A2ZZA1ZZ;     Array[18] = Results[i].A2ZZA1ZZError;
      Array[1] = Results[i].A2ZZPhase;    Array[19] = Results[i].A2ZZPhaseError;
      Array[2] = Results[i].A3ZZA1ZZ;     Array[20] = Results[i].A3ZZA1ZZError;
      Array[3] = Results[i].A3ZZPhase;    Array[21] = Results[i].A3ZZPhaseError;
      Array[4] = Results[i].A2ZAA1ZZ;     Array[22] = Results[i].A2ZAA1ZZError;
      Array[5] = Results[i].A2ZAPhase;    Array[23] = Results[i].A2ZAPhaseError;
      Array[6] = Results[i].A3ZAA1ZZ;     Array[24] = Results[i].A3ZAA1ZZError;
      Array[7] = Results[i].A3ZAPhase;    Array[25] = Results[i].A3ZAPhaseError;
      Array[8] = Results[i].A2AAA1ZZ;     Array[26] = Results[i].A2AAA1ZZError;
      Array[9] = Results[i].A2AAPhase;    Array[27] = Results[i].A2AAPhaseError;
      Array[10] = Results[i].A3AAA1ZZ;    Array[28] = Results[i].A3AAA1ZZError;
      Array[11] = Results[i].A3AAPhase;   Array[29] = Results[i].A3AAPhaseError;
      Array[12] = Results[i].N1;          Array[30] = Results[i].N1Error;
      Array[13] = Results[i].N2;          Array[31] = Results[i].N2Error;
      Array[14] = Results[i].Fem;         Array[32] = Results[i].FemError;
      Array[15] = Results[i].Fme;         Array[33] = Results[i].FmeError;
      Array[16] = Results[i].Fee;         Array[34] = Results[i].FeeError;
      Array[17] = Results[i].Fmm;         Array[35] = Results[i].FmmError;

      Array[36] = Results[i].EDM;
      Array[37] = Results[i].FitStatus;

      Array[38] = Results[i].Sem;         Array[42] = Results[i].Bem;
      Array[39] = Results[i].Sme;         Array[43] = Results[i].Bme;
      Array[40] = Results[i].See;         Array[44] = Results[i].Bee;
      Array[41] = Results[i].Smm;         Array[45] = Results[i].Bmm;

      Array[46] = 0;
      Array[47] = 0;
      Array[48] = Results[i].I1ZZModificationFactor;

      Array[49] = Results[i].TruthNLL;    Array[50] = Results[i].BestNLL;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double GetPhi(double x, double y)
{
   FourVector X;
   X[1] = x;
   X[2] = y;
   return X.GetPhi();
}

bool PassLooseCut(LeptonVectors Leptons)
{
   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   if(max(M1, M2) < 4)    return false;
   if(min(M1, M2) < 4)    return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 2)    return false;
   if(LPTs[2] < 2)    return false;
   if(LPTs[1] < 2)    return false;
   if(LPTs[0] < 2)    return false;

   if(GetDR(Leptons.Lepton11, Leptons.Lepton12) < 0.2)   return false;
   if(GetDR(Leptons.Lepton11, Leptons.Lepton21) < 0.2)   return false;
   if(GetDR(Leptons.Lepton11, Leptons.Lepton22) < 0.2)   return false;
   if(GetDR(Leptons.Lepton12, Leptons.Lepton21) < 0.2)   return false;
   if(GetDR(Leptons.Lepton12, Leptons.Lepton22) < 0.2)   return false;
   if(GetDR(Leptons.Lepton21, Leptons.Lepton22) < 0.2)   return false;

   return true;
}

bool PassTightCut(LeptonVectors Leptons)
{
   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   if(max(M1, M2) < 4)    return false;
   if(min(M1, M2) < 4)    return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)    return false;
   if(LPTs[2] < 10)    return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if(GetDR(Leptons.Lepton11, Leptons.Lepton12) < 0.2)   return false;
   if(GetDR(Leptons.Lepton11, Leptons.Lepton21) < 0.2)   return false;
   if(GetDR(Leptons.Lepton11, Leptons.Lepton22) < 0.2)   return false;
   if(GetDR(Leptons.Lepton12, Leptons.Lepton21) < 0.2)   return false;
   if(GetDR(Leptons.Lepton12, Leptons.Lepton22) < 0.2)   return false;
   if(GetDR(Leptons.Lepton21, Leptons.Lepton22) < 0.2)   return false;

   return true;
}

SingleEvent GiveMeSignalPoint(double As[8], int FinalState)
{
   EventParameters Event;
   SingleEvent Result;

   bool Is2e2mu = false;

   bool Good = false;
   while(Good == false)
   {
      Event.HMass     = 125;
      Event.ZMass     = DrawRandom(4, 125);
      Event.Z2Mass    = DrawRandom(4, 125);
      Event.Phi0      = DrawRandom(0, 2 * PI);
      Event.Theta0    = acos(DrawRandom(-1, 1));
      Event.Phi       = DrawRandom(0, 2 * PI);
      Event.Theta1    = acos(DrawRandom(-1, 1));
      Event.Theta2    = acos(DrawRandom(-1, 1));
      Event.YH        = 0;
      Event.PTH       = 0;
      Event.PhiH      = DrawRandom(0, 2 * PI);
      Event.PhiOffset = DrawRandom(0, 2 * PI);

      if(Event.ZMass + Event.Z2Mass > Event.HMass)
         continue;

      LeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Event);

      if(FinalState == FINALSTATE_2e2mu)   Is2e2mu = true;
      if(FinalState == FINALSTATE_4e4mu)   Is2e2mu = false;
      if(FinalState == FINALSTATE_mixed)   Is2e2mu = !Is2e2mu;

#ifdef USE_LOOSE_CUT
      if(Is2e2mu == true && PassLooseCut(Vectors.ReorderLeptons2e2mu()) == false)
         continue;
      if(Is2e2mu == false && PassLooseCut(Vectors.ReorderLeptons4e()) == false)
         continue;
#elif defined USE_TIGHT_CUT
      if(Is2e2mu == true && PassTightCut(Vectors.ReorderLeptons2e2mu()) == false)
         continue;
      if(Is2e2mu == false && PassTightCut(Vectors.ReorderLeptons4e()) == false)
         continue;
#endif

      double CombinedWeight = GetWeight(As, Event, Is2e2mu);
      if(DrawRandom(0, 1) < CombinedWeight / MAX_SIGNAL_WEIGHT)
         Good = true;
      if(Good == false)
         continue;
      
      if(CombinedWeight > MAX_SIGNAL_WEIGHT)
         cerr << "ERROR!  Combined weight = " << CombinedWeight
            << ", greater than max weight (" << MAX_SIGNAL_WEIGHT << ")" << endl;

      Result = CalculateLikelihoods(Event, Is2e2mu);
      Result.event = Event;
   }

   return Result;
}

SingleEvent GiveMeBackgroundPoint(int FinalState)
{
   EventParameters Event;
   SingleEvent Result;

   bool Is2e2mu = true;

   bool Good = false;
   while(Good == false)
   {
      Event.HMass = 125;
      Event.ZMass = DrawRandom(4, 125);
      Event.Z2Mass = DrawRandom(4, 125);
      Event.Phi0 = DrawRandom(0, 2 * PI);
      Event.Theta0 = DrawRandom(0, PI);
      Event.Phi = DrawRandom(0, 2 * PI);
      Event.Theta1 = DrawRandom(0, PI);
      Event.Theta2 = DrawRandom(0, PI);
      Event.YH = 0;
      Event.PTH = 0;
      Event.PhiH = DrawRandom(0, 2 * PI);
      Event.PhiOffset = DrawRandom(0, 2 * PI);

      if(Event.ZMass + Event.Z2Mass > Event.HMass)
         continue;

      LeptonVectors Vectors = ConvertAnglesToVectorsRoberto(Event);

      if(FinalState == FINALSTATE_2e2mu)   Is2e2mu = true;
      if(FinalState == FINALSTATE_4e4mu)   Is2e2mu = false;
      if(FinalState == FINALSTATE_mixed)   Is2e2mu = !Is2e2mu;

#ifdef USE_LOOSE_CUT
      if(Is2e2mu == true && PassLooseCut(Vectors.ReorderLeptons2e2mu()) == false)
         continue;
      if(Is2e2mu == false && PassLooseCut(Vectors.ReorderLeptons4e()) == false)
         continue;
#elif defined USE_TIGHT_CUT
      if(Is2e2mu == true && PassTightCut(Vectors.ReorderLeptons2e2mu()) == false)
         continue;
      if(Is2e2mu == false && PassTightCut(Vectors.ReorderLeptons4e()) == false)
         continue;
#endif

      LeptonVectors VectorsAtRest = Vectors.GoToRest();
      double CombinedWeight = 1;
      if(Is2e2mu == true)
         CombinedWeight = GetZZZAAABackground(VectorsAtRest, true, true)
            + GetZZZAAABackground(VectorsAtRest, true, false)
            + GetZZZAAABackground(VectorsAtRest, false, true)
            + GetZZZAAABackground(VectorsAtRest, false, false);
      if(Is2e2mu == false)
         CombinedWeight = GetZZZAAA4eBackground(VectorsAtRest, true, true)
            + GetZZZAAA4eBackground(VectorsAtRest, true, false)
            + GetZZZAAA4eBackground(VectorsAtRest, false, true)
            + GetZZZAAA4eBackground(VectorsAtRest, false, false);
      CombinedWeight = CombinedWeight * Event.ZMass * Event.Z2Mass * Event.HMass
         * sin(Event.Theta0) * sin(Event.Theta1) * sin(Event.Theta2);
      if(DrawRandom(0, 1) < CombinedWeight / MAX_BACKGROUND_WEIGHT)
         Good = true;
      if(Good == false)
         continue;

      if(CombinedWeight > MAX_BACKGROUND_WEIGHT)
      {
         cerr << "ERROR!  Background weight = " << CombinedWeight
            << ", greater than max weight (" << MAX_BACKGROUND_WEIGHT << ")" << endl;
         // cerr << Vectors << " " << VectorsAtRest << " " << Event << endl;
      }

      Result = CalculateLikelihoods(Event, Is2e2mu);
      Result.event = Event;
   }

   return Result;
}

SingleEvent CalculateLikelihoods(EventParameters &Event, bool Is2e2mu)
{
   static DataHelper DHFile("Normalization.dh");

   vector<double (*)(LeptonVectors &)> SignalMEs = GetSignalMEs(Is2e2mu);
   double (*BackgroundME)(LeptonVectors &, bool, bool);
   if(Is2e2mu == true)
      BackgroundME = GetZZZAAABackground;
   else
      BackgroundME = GetZZZAAA4eBackground;

   SingleEvent Result;

   if(Is2e2mu == true)
   {
      LeptonVectors Leptons1 = ConvertAnglesToVectorsRoberto(Event);
      LeptonVectors Leptons2 = Leptons1.FlipZ1Z2();

      Result.v[0][0] = BackgroundME(Leptons1, true, true) + BackgroundME(Leptons1, true, false)
         + BackgroundME(Leptons1, false, true) + BackgroundME(Leptons1, false, false)
         + BackgroundME(Leptons2, true, true) + BackgroundME(Leptons2, true, false)
         + BackgroundME(Leptons2, false, true) + BackgroundME(Leptons2, false, false);
      for(int i = 0; i < 153; i++)
         Result.v[i+1][0] = (*SignalMEs[i])(Leptons1) + (*SignalMEs[i])(Leptons2);

#ifdef USE_LOOSE_CUT
      Result.i[0][0] = DHFile["LooseCutEM"]["t2"].GetDouble();
      for(int i = 0; i < 153; i++)
         Result.i[i+1][0] = DHFile["LooseCutEM"][Form("t1_%03d",i+1)].GetDouble();
#elif defined USE_TIGHT_CUT
      Result.i[0][0] = DHFile["TightCutEM"]["T2"].GetDouble();
      for(int i = 0; i < 153; i++)
         Result.i[i+1][0] = DHFile["TightCutEM"][Form("T1_%03d",i+1)].GetDouble();
#endif
   }
   else
   {
      LeptonVectors Leptons1 = ConvertAnglesToVectorsRoberto(Event);
      LeptonVectors Leptons2 = Leptons1.FlipZ1Z2();
      LeptonVectors Leptons3 = Leptons1;
      LeptonVectors Leptons4 = Leptons1;

      swap(Leptons3.Lepton11, Leptons3.Lepton21);
      swap(Leptons4.Lepton12, Leptons4.Lepton22);

      Result.v[0][0] = BackgroundME(Leptons1, true, true) + BackgroundME(Leptons1, true, false)
         + BackgroundME(Leptons1, false, true) + BackgroundME(Leptons1, false, false)
         + BackgroundME(Leptons2, true, true) + BackgroundME(Leptons2, true, false)
         + BackgroundME(Leptons2, false, true) + BackgroundME(Leptons2, false, false)
         + BackgroundME(Leptons3, true, true) + BackgroundME(Leptons3, true, false)
         + BackgroundME(Leptons3, false, true) + BackgroundME(Leptons3, false, false)
         + BackgroundME(Leptons4, true, true) + BackgroundME(Leptons4, true, false)
         + BackgroundME(Leptons4, false, true) + BackgroundME(Leptons4, false, false);
      for(int i = 0; i < 153; i++)
         Result.v[i+1][0] = (*SignalMEs[i])(Leptons1) + (*SignalMEs[i])(Leptons2)
            + (*SignalMEs[i])(Leptons3) + (*SignalMEs[i])(Leptons4);

#ifdef USE_LOOSE_CUT
      Result.i[0][0] = DHFile["LooseCutEE"]["v2"].GetDouble();
      for(int i = 0; i < 153; i++)
         Result.i[i+1][0] = DHFile["LooseCutEE"][Form("v1_%03d",i+1)].GetDouble();
#elif defined USE_TIGHT_CUT
      Result.i[0][0] = DHFile["TightCutEE"]["V2"].GetDouble();
      for(int i = 0; i < 153; i++)
         Result.i[i+1][0] = DHFile["TightCutEE"][Form("V1_%03d",i+1)].GetDouble();
#endif
   }

   for(int i = 0; i <= 153; i++)
   {
      for(int j = 1; j < 5; j++)
      {
         Result.v[i][j] = Result.v[i][0];
         Result.i[i][j] = Result.i[i][0];
      }
   }

   return Result;
}

vector<double (*)(LeptonVectors &)> GetSignalMEs(bool Is2e2mu)
{
   vector<double (*)(LeptonVectors &)> Result;

   if(Is2e2mu == true)
   {
      Result.push_back(CalculateA1ZZRA1ZZRSignal2e2mu);
      Result.push_back(CalculateA2ZZRA2ZZRSignal2e2mu);
      Result.push_back(CalculateA2ZZIA2ZZISignal2e2mu);
      Result.push_back(CalculateA3ZZRA3ZZRSignal2e2mu);
      Result.push_back(CalculateA3ZZIA3ZZISignal2e2mu);
      Result.push_back(CalculateA2ZARA2ZARSignal2e2mu);
      Result.push_back(CalculateA2ZAIA2ZAISignal2e2mu);
      Result.push_back(CalculateA3ZARA3ZARSignal2e2mu);
      Result.push_back(CalculateA3ZAIA3ZAISignal2e2mu);
      Result.push_back(CalculateA2AARA2AARSignal2e2mu);
      Result.push_back(CalculateA2AAIA2AAISignal2e2mu);
      Result.push_back(CalculateA3AARA3AARSignal2e2mu);
      Result.push_back(CalculateA3AAIA3AAISignal2e2mu);

      Result.push_back(CalculateA1ZZRA2ZZRSignal2e2mu);
      Result.push_back(CalculateA1ZZRA2ZZISignal2e2mu);
      Result.push_back(CalculateA1ZZRA3ZZRSignal2e2mu);
      Result.push_back(CalculateA1ZZRA3ZZISignal2e2mu);
      Result.push_back(CalculateA1ZZRA2ZARSignal2e2mu);
      Result.push_back(CalculateA1ZZRA2ZAISignal2e2mu);
      Result.push_back(CalculateA1ZZRA3ZARSignal2e2mu);
      Result.push_back(CalculateA1ZZRA3ZAISignal2e2mu);
      Result.push_back(CalculateA1ZZRA2AARSignal2e2mu);
      Result.push_back(CalculateA1ZZRA2AAISignal2e2mu);
      Result.push_back(CalculateA1ZZRA3AARSignal2e2mu);
      Result.push_back(CalculateA1ZZRA3AAISignal2e2mu);
      Result.push_back(CalculateA2ZZRA2ZZISignal2e2mu);
      Result.push_back(CalculateA2ZZRA3ZZRSignal2e2mu);
      Result.push_back(CalculateA2ZZRA3ZZISignal2e2mu);
      Result.push_back(CalculateA2ZZRA2ZARSignal2e2mu);
      Result.push_back(CalculateA2ZZRA2ZAISignal2e2mu);
      Result.push_back(CalculateA2ZZRA3ZARSignal2e2mu);
      Result.push_back(CalculateA2ZZRA3ZAISignal2e2mu);
      Result.push_back(CalculateA2ZZRA2AARSignal2e2mu);
      Result.push_back(CalculateA2ZZRA2AAISignal2e2mu);
      Result.push_back(CalculateA2ZZRA3AARSignal2e2mu);
      Result.push_back(CalculateA2ZZRA3AAISignal2e2mu);
      Result.push_back(CalculateA2ZZIA3ZZRSignal2e2mu);
      Result.push_back(CalculateA2ZZIA3ZZISignal2e2mu);
      Result.push_back(CalculateA2ZZIA2ZARSignal2e2mu);
      Result.push_back(CalculateA2ZZIA2ZAISignal2e2mu);
      Result.push_back(CalculateA2ZZIA3ZARSignal2e2mu);
      Result.push_back(CalculateA2ZZIA3ZAISignal2e2mu);
      Result.push_back(CalculateA2ZZIA2AARSignal2e2mu);
      Result.push_back(CalculateA2ZZIA2AAISignal2e2mu);
      Result.push_back(CalculateA2ZZIA3AARSignal2e2mu);
      Result.push_back(CalculateA2ZZIA3AAISignal2e2mu);
      Result.push_back(CalculateA3ZZRA3ZZISignal2e2mu);
      Result.push_back(CalculateA3ZZRA2ZARSignal2e2mu);
      Result.push_back(CalculateA3ZZRA2ZAISignal2e2mu);
      Result.push_back(CalculateA3ZZRA3ZARSignal2e2mu);
      Result.push_back(CalculateA3ZZRA3ZAISignal2e2mu);
      Result.push_back(CalculateA3ZZRA2AARSignal2e2mu);
      Result.push_back(CalculateA3ZZRA2AAISignal2e2mu);
      Result.push_back(CalculateA3ZZRA3AARSignal2e2mu);
      Result.push_back(CalculateA3ZZRA3AAISignal2e2mu);
      Result.push_back(CalculateA3ZZIA2ZARSignal2e2mu);
      Result.push_back(CalculateA3ZZIA2ZAISignal2e2mu);
      Result.push_back(CalculateA3ZZIA3ZARSignal2e2mu);
      Result.push_back(CalculateA3ZZIA3ZAISignal2e2mu);
      Result.push_back(CalculateA3ZZIA2AARSignal2e2mu);
      Result.push_back(CalculateA3ZZIA2AAISignal2e2mu);
      Result.push_back(CalculateA3ZZIA3AARSignal2e2mu);
      Result.push_back(CalculateA3ZZIA3AAISignal2e2mu);
      Result.push_back(CalculateA2ZARA2ZAISignal2e2mu);
      Result.push_back(CalculateA2ZARA3ZARSignal2e2mu);
      Result.push_back(CalculateA2ZARA3ZAISignal2e2mu);
      Result.push_back(CalculateA2ZARA2AARSignal2e2mu);
      Result.push_back(CalculateA2ZARA2AAISignal2e2mu);
      Result.push_back(CalculateA2ZARA3AARSignal2e2mu);
      Result.push_back(CalculateA2ZARA3AAISignal2e2mu);
      Result.push_back(CalculateA2ZAIA3ZARSignal2e2mu);
      Result.push_back(CalculateA2ZAIA3ZAISignal2e2mu);
      Result.push_back(CalculateA2ZAIA2AARSignal2e2mu);
      Result.push_back(CalculateA2ZAIA2AAISignal2e2mu);
      Result.push_back(CalculateA2ZAIA3AARSignal2e2mu);
      Result.push_back(CalculateA2ZAIA3AAISignal2e2mu);
      Result.push_back(CalculateA3ZARA3ZAISignal2e2mu);
      Result.push_back(CalculateA3ZARA2AARSignal2e2mu);
      Result.push_back(CalculateA3ZARA2AAISignal2e2mu);
      Result.push_back(CalculateA3ZARA3AARSignal2e2mu);
      Result.push_back(CalculateA3ZARA3AAISignal2e2mu);
      Result.push_back(CalculateA3ZAIA2AARSignal2e2mu);
      Result.push_back(CalculateA3ZAIA2AAISignal2e2mu);
      Result.push_back(CalculateA3ZAIA3AARSignal2e2mu);
      Result.push_back(CalculateA3ZAIA3AAISignal2e2mu);
      Result.push_back(CalculateA2AARA2AAISignal2e2mu);
      Result.push_back(CalculateA2AARA3AARSignal2e2mu);
      Result.push_back(CalculateA2AARA3AAISignal2e2mu);
      Result.push_back(CalculateA2AAIA3AARSignal2e2mu);
      Result.push_back(CalculateA2AAIA3AAISignal2e2mu);
      Result.push_back(CalculateA3AARA3AAISignal2e2mu);

      Result.push_back(CalculateA1L1ZZRA1L1ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA1L1ZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA1LQZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA1LQZZISignal2e2mu);

      Result.push_back(CalculateA1ZZRA1L1ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2ZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3ZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2ZARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2ZAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3ZARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3ZAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2AARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA2AAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3AARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA3AAISignal2e2mu);

      Result.push_back(CalculateA1ZZRA1L1ZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2ZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3ZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3ZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2ZARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2ZAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3ZARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3ZAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2AARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA2AAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3AARSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA3AAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA1L1ZZISignal2e2mu);

      Result.push_back(CalculateA1ZZRA1LQZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2ZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2ZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3ZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3ZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2ZARSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2ZAISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3ZARSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3ZAISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2AARSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA2AAISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3AARSignal2e2mu);
      Result.push_back(CalculateA1LQZZRA3AAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA1LQZZRSignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA1LQZZRSignal2e2mu);

      Result.push_back(CalculateA1ZZRA1LQZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2ZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2ZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3ZZRSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3ZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2ZARSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2ZAISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3ZARSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3ZAISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2AARSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA2AAISignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3AARSignal2e2mu);
      Result.push_back(CalculateA1LQZZIA3AAISignal2e2mu);
      Result.push_back(CalculateA1L1ZZRA1LQZZISignal2e2mu);
      Result.push_back(CalculateA1L1ZZIA1LQZZISignal2e2mu);
      Result.push_back(CalculateA1LQZZRA1LQZZISignal2e2mu);
   }
   else
   {
      Result.push_back(CalculateA1ZZRA1ZZRSignal4e);
      Result.push_back(CalculateA2ZZRA2ZZRSignal4e);
      Result.push_back(CalculateA2ZZIA2ZZISignal4e);
      Result.push_back(CalculateA3ZZRA3ZZRSignal4e);
      Result.push_back(CalculateA3ZZIA3ZZISignal4e);
      Result.push_back(CalculateA2ZARA2ZARSignal4e);
      Result.push_back(CalculateA2ZAIA2ZAISignal4e);
      Result.push_back(CalculateA3ZARA3ZARSignal4e);
      Result.push_back(CalculateA3ZAIA3ZAISignal4e);
      Result.push_back(CalculateA2AARA2AARSignal4e);
      Result.push_back(CalculateA2AAIA2AAISignal4e);
      Result.push_back(CalculateA3AARA3AARSignal4e);
      Result.push_back(CalculateA3AAIA3AAISignal4e);

      Result.push_back(CalculateA1ZZRA2ZZRSignal4e);
      Result.push_back(CalculateA1ZZRA2ZZISignal4e);
      Result.push_back(CalculateA1ZZRA3ZZRSignal4e);
      Result.push_back(CalculateA1ZZRA3ZZISignal4e);
      Result.push_back(CalculateA1ZZRA2ZARSignal4e);
      Result.push_back(CalculateA1ZZRA2ZAISignal4e);
      Result.push_back(CalculateA1ZZRA3ZARSignal4e);
      Result.push_back(CalculateA1ZZRA3ZAISignal4e);
      Result.push_back(CalculateA1ZZRA2AARSignal4e);
      Result.push_back(CalculateA1ZZRA2AAISignal4e);
      Result.push_back(CalculateA1ZZRA3AARSignal4e);
      Result.push_back(CalculateA1ZZRA3AAISignal4e);
      Result.push_back(CalculateA2ZZRA2ZZISignal4e);
      Result.push_back(CalculateA2ZZRA3ZZRSignal4e);
      Result.push_back(CalculateA2ZZRA3ZZISignal4e);
      Result.push_back(CalculateA2ZZRA2ZARSignal4e);
      Result.push_back(CalculateA2ZZRA2ZAISignal4e);
      Result.push_back(CalculateA2ZZRA3ZARSignal4e);
      Result.push_back(CalculateA2ZZRA3ZAISignal4e);
      Result.push_back(CalculateA2ZZRA2AARSignal4e);
      Result.push_back(CalculateA2ZZRA2AAISignal4e);
      Result.push_back(CalculateA2ZZRA3AARSignal4e);
      Result.push_back(CalculateA2ZZRA3AAISignal4e);
      Result.push_back(CalculateA2ZZIA3ZZRSignal4e);
      Result.push_back(CalculateA2ZZIA3ZZISignal4e);
      Result.push_back(CalculateA2ZZIA2ZARSignal4e);
      Result.push_back(CalculateA2ZZIA2ZAISignal4e);
      Result.push_back(CalculateA2ZZIA3ZARSignal4e);
      Result.push_back(CalculateA2ZZIA3ZAISignal4e);
      Result.push_back(CalculateA2ZZIA2AARSignal4e);
      Result.push_back(CalculateA2ZZIA2AAISignal4e);
      Result.push_back(CalculateA2ZZIA3AARSignal4e);
      Result.push_back(CalculateA2ZZIA3AAISignal4e);
      Result.push_back(CalculateA3ZZRA3ZZISignal4e);
      Result.push_back(CalculateA3ZZRA2ZARSignal4e);
      Result.push_back(CalculateA3ZZRA2ZAISignal4e);
      Result.push_back(CalculateA3ZZRA3ZARSignal4e);
      Result.push_back(CalculateA3ZZRA3ZAISignal4e);
      Result.push_back(CalculateA3ZZRA2AARSignal4e);
      Result.push_back(CalculateA3ZZRA2AAISignal4e);
      Result.push_back(CalculateA3ZZRA3AARSignal4e);
      Result.push_back(CalculateA3ZZRA3AAISignal4e);
      Result.push_back(CalculateA3ZZIA2ZARSignal4e);
      Result.push_back(CalculateA3ZZIA2ZAISignal4e);
      Result.push_back(CalculateA3ZZIA3ZARSignal4e);
      Result.push_back(CalculateA3ZZIA3ZAISignal4e);
      Result.push_back(CalculateA3ZZIA2AARSignal4e);
      Result.push_back(CalculateA3ZZIA2AAISignal4e);
      Result.push_back(CalculateA3ZZIA3AARSignal4e);
      Result.push_back(CalculateA3ZZIA3AAISignal4e);
      Result.push_back(CalculateA2ZARA2ZAISignal4e);
      Result.push_back(CalculateA2ZARA3ZARSignal4e);
      Result.push_back(CalculateA2ZARA3ZAISignal4e);
      Result.push_back(CalculateA2ZARA2AARSignal4e);
      Result.push_back(CalculateA2ZARA2AAISignal4e);
      Result.push_back(CalculateA2ZARA3AARSignal4e);
      Result.push_back(CalculateA2ZARA3AAISignal4e);
      Result.push_back(CalculateA2ZAIA3ZARSignal4e);
      Result.push_back(CalculateA2ZAIA3ZAISignal4e);
      Result.push_back(CalculateA2ZAIA2AARSignal4e);
      Result.push_back(CalculateA2ZAIA2AAISignal4e);
      Result.push_back(CalculateA2ZAIA3AARSignal4e);
      Result.push_back(CalculateA2ZAIA3AAISignal4e);
      Result.push_back(CalculateA3ZARA3ZAISignal4e);
      Result.push_back(CalculateA3ZARA2AARSignal4e);
      Result.push_back(CalculateA3ZARA2AAISignal4e);
      Result.push_back(CalculateA3ZARA3AARSignal4e);
      Result.push_back(CalculateA3ZARA3AAISignal4e);
      Result.push_back(CalculateA3ZAIA2AARSignal4e);
      Result.push_back(CalculateA3ZAIA2AAISignal4e);
      Result.push_back(CalculateA3ZAIA3AARSignal4e);
      Result.push_back(CalculateA3ZAIA3AAISignal4e);
      Result.push_back(CalculateA2AARA2AAISignal4e);
      Result.push_back(CalculateA2AARA3AARSignal4e);
      Result.push_back(CalculateA2AARA3AAISignal4e);
      Result.push_back(CalculateA2AAIA3AARSignal4e);
      Result.push_back(CalculateA2AAIA3AAISignal4e);
      Result.push_back(CalculateA3AARA3AAISignal4e);

      Result.push_back(CalculateA1L1ZZRA1L1ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZIA1L1ZZISignal4e);
      Result.push_back(CalculateA1LQZZRA1LQZZRSignal4e);
      Result.push_back(CalculateA1LQZZIA1LQZZISignal4e);

      Result.push_back(CalculateA1ZZRA1L1ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZRA2ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZRA2ZZISignal4e);
      Result.push_back(CalculateA1L1ZZRA3ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZRA3ZZISignal4e);
      Result.push_back(CalculateA1L1ZZRA2ZARSignal4e);
      Result.push_back(CalculateA1L1ZZRA2ZAISignal4e);
      Result.push_back(CalculateA1L1ZZRA3ZARSignal4e);
      Result.push_back(CalculateA1L1ZZRA3ZAISignal4e);
      Result.push_back(CalculateA1L1ZZRA2AARSignal4e);
      Result.push_back(CalculateA1L1ZZRA2AAISignal4e);
      Result.push_back(CalculateA1L1ZZRA3AARSignal4e);
      Result.push_back(CalculateA1L1ZZRA3AAISignal4e);

      Result.push_back(CalculateA1ZZRA1L1ZZISignal4e);
      Result.push_back(CalculateA1L1ZZIA2ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZIA2ZZISignal4e);
      Result.push_back(CalculateA1L1ZZIA3ZZRSignal4e);
      Result.push_back(CalculateA1L1ZZIA3ZZISignal4e);
      Result.push_back(CalculateA1L1ZZIA2ZARSignal4e);
      Result.push_back(CalculateA1L1ZZIA2ZAISignal4e);
      Result.push_back(CalculateA1L1ZZIA3ZARSignal4e);
      Result.push_back(CalculateA1L1ZZIA3ZAISignal4e);
      Result.push_back(CalculateA1L1ZZIA2AARSignal4e);
      Result.push_back(CalculateA1L1ZZIA2AAISignal4e);
      Result.push_back(CalculateA1L1ZZIA3AARSignal4e);
      Result.push_back(CalculateA1L1ZZIA3AAISignal4e);
      Result.push_back(CalculateA1L1ZZRA1L1ZZISignal4e);

      Result.push_back(CalculateA1ZZRA1LQZZRSignal4e);
      Result.push_back(CalculateA1LQZZRA2ZZRSignal4e);
      Result.push_back(CalculateA1LQZZRA2ZZISignal4e);
      Result.push_back(CalculateA1LQZZRA3ZZRSignal4e);
      Result.push_back(CalculateA1LQZZRA3ZZISignal4e);
      Result.push_back(CalculateA1LQZZRA2ZARSignal4e);
      Result.push_back(CalculateA1LQZZRA2ZAISignal4e);
      Result.push_back(CalculateA1LQZZRA3ZARSignal4e);
      Result.push_back(CalculateA1LQZZRA3ZAISignal4e);
      Result.push_back(CalculateA1LQZZRA2AARSignal4e);
      Result.push_back(CalculateA1LQZZRA2AAISignal4e);
      Result.push_back(CalculateA1LQZZRA3AARSignal4e);
      Result.push_back(CalculateA1LQZZRA3AAISignal4e);
      Result.push_back(CalculateA1L1ZZRA1LQZZRSignal4e);
      Result.push_back(CalculateA1L1ZZIA1LQZZRSignal4e);

      Result.push_back(CalculateA1ZZRA1LQZZISignal4e);
      Result.push_back(CalculateA1LQZZIA2ZZRSignal4e);
      Result.push_back(CalculateA1LQZZIA2ZZISignal4e);
      Result.push_back(CalculateA1LQZZIA3ZZRSignal4e);
      Result.push_back(CalculateA1LQZZIA3ZZISignal4e);
      Result.push_back(CalculateA1LQZZIA2ZARSignal4e);
      Result.push_back(CalculateA1LQZZIA2ZAISignal4e);
      Result.push_back(CalculateA1LQZZIA3ZARSignal4e);
      Result.push_back(CalculateA1LQZZIA3ZAISignal4e);
      Result.push_back(CalculateA1LQZZIA2AARSignal4e);
      Result.push_back(CalculateA1LQZZIA2AAISignal4e);
      Result.push_back(CalculateA1LQZZIA3AARSignal4e);
      Result.push_back(CalculateA1LQZZIA3AAISignal4e);
      Result.push_back(CalculateA1L1ZZRA1LQZZISignal4e);
      Result.push_back(CalculateA1L1ZZIA1LQZZISignal4e);
      Result.push_back(CalculateA1LQZZRA1LQZZISignal4e);
   }

   return Result;
}

double GetWeight(double As[8], EventParameters &Event, bool Is2e2mu)
{
   double A1ZZR = As[0];
   double A2ZZR = As[1];
   double A3ZZR = As[2];
   double A2ZAR = As[3];
   double A3ZAR = As[4];
   double A2AAR = As[5];
   double A3AAR = As[6];
   double A1L1ZZR = As[7];

   double S1 = Event.ZMass * Event.ZMass;
   double S2 = Event.Z2Mass * Event.Z2Mass;

   GeneralScalarParameters Parameters;
   Parameters.ahR   = A1ZZR + A1L1ZZR * (S1 + S2);   Parameters.ahI = 0;
   Parameters.aZR   = A2ZZR;                         Parameters.aZI = 0;
   Parameters.aZdR  = A3ZZR;                         Parameters.aZdI = 0;
   Parameters.aZAR  = A2ZAR;                         Parameters.aZAI = 0;
   Parameters.aZAdR = A3ZAR;                         Parameters.aZAdI = 0;
   Parameters.aAR   = A2AAR;                         Parameters.aAI = 0;
   Parameters.aAdR  = A3AAR;                         Parameters.aAdI = 0;

   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   double Weight = 1;
   if(Is2e2mu == true)
      Weight = GetGeneralScalar(Leptons, Parameters);
   else
      Weight = GetGeneralScalar4e(Leptons, Parameters);

   return Weight * Event.HMass * Event.ZMass * Event.Z2Mass;
}



