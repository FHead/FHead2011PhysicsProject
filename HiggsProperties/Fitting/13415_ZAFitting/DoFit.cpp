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
#include "CalculateZAME.h"
#include "Lists.h"

#include "FitClass.h"

#define BackgroundNormalizationCorrection 1

int main(int argc, char *argv[]);
double GetPhi(double x, double y);
bool PassLooseCut(ZALeptonVectors Event);
bool PassTightCut(ZALeptonVectors Event);
double GetWeight(double Phis[3], double Phases[4], ZAEventParameters &Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

// #define USE_LOOSE_CUT
#define USE_TIGHT_CUT

int main(int argc, char *argv[])
{
   string SignalFile, BackgroundFile;
   double SignalSize = 30, BackgroundSize = 30;

   if(argc < 9)
   {
      cerr << "Usage: " << argv[0]
         << " SignalFile SignalSize BackgroundFile BackgroundSize A2ZA A3ZA A2AA A3AA [Seed]"
         << endl;
      return -1;
   }

   SignalFile = argv[1];
   SignalSize = atof(argv[2]);
   BackgroundFile = argv[3];
   BackgroundSize = atof(argv[4]);

   double A2ZA = atof(argv[5]);
   double A3ZA = atof(argv[6]);
   double A2AA = atof(argv[7]);
   double A3AA = atof(argv[8]);

   if(argc >= 10)
      srand(atoi(argv[9]));
   else
      srand(time(NULL));

   double AZA = sqrt(A2ZA * A2ZA + A3ZA * A3ZA);
   double AAA = sqrt(A2AA * A2AA + A3AA * A3AA);

   double PhiV = 0, PhiZA = 0, PhiAA = 0;
   PhiV = GetPhi(AZA, AAA);
   PhiZA = GetPhi(A2ZA, A3ZA);
   PhiAA = GetPhi(A2AA, A3AA);

   double Phis[3] = {PhiV, PhiZA, PhiAA};
   double Phases[4] = {0, 0, 0, 0};

   vector<FitResultSummary> Results;

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 7; i++)
   {
      if(i != 7)
         continue;

      string Phis = "NNN";
      if((i / 1) % 2 == 1)    Phis[0] = 'Y';
      if((i / 2) % 2 == 1)    Phis[1] = 'Y';
      if((i / 4) % 2 == 1)    Phis[2] = 'Y';

      string Phases = "NNNN";

      string Fractions = "N";
      if(BackgroundSize > 0)
         Fractions = "Y";

      vector<double> PhiValues = ListToVector(3, PhiV, PhiZA, PhiAA);

      vector<double> FractionValues = ListToVector(1, 0);
      if(BackgroundSize > 0)
         FractionValues[0] = (double)BackgroundSize / (BackgroundSize + SignalSize);

      Configurations.push_back(FitConfiguration(Phis, Phases, Fractions,
         PhiValues, ListToVector(4, 0, 0, 0, 0), FractionValues));
   }

   FitClass Fits;
   Fits.ClearPoints();

   vector<SingleEvent> SignalEvents, BackgroundEvents;
   ReadEvents(SignalEvents, SignalFile);
   ReadEvents(BackgroundEvents, BackgroundFile);

   double SignalRead = SignalEvents.size();
   double BackgroundRead = BackgroundEvents.size();

   ProgressBar Bar(cout, SignalRead);
   Bar.SetStyle(3);

   bool MoreEvents = true;
   while(MoreEvents == true)
   {
      Bar.Update(SignalRead - SignalEvents.size());
      Bar.Print();

      if(SignalSize >= 0 && SignalEvents.size() == 0)   MoreEvents = false;
      if(BackgroundSize >= 0 && BackgroundEvents.size() == 0)   MoreEvents = false;

      int SignalCount = (SignalSize >= 0 ? DrawPoisson(SignalSize) : 0);
      int BackgroundCount = (BackgroundSize >= 0 ? DrawPoisson(BackgroundSize) : 0);

      if(SignalCount > SignalEvents.size())   MoreEvents = false;
      if(BackgroundCount > BackgroundEvents.size())   MoreEvents = false;

      if(MoreEvents == false)
         break;

      for(int i = 0; i < SignalCount; i++)   Fits.AddPoint(SignalEvents[i]);
      for(int i = 0; i < BackgroundCount; i++)   Fits.AddPoint(BackgroundEvents[i]);

      SignalEvents.erase(SignalEvents.begin(), SignalEvents.begin() + SignalCount);
      BackgroundEvents.erase(BackgroundEvents.begin(), BackgroundEvents.begin() + BackgroundCount);

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);
      }

      Fits.ClearPoints();
   }
      
   Bar.Update(SignalRead);
   Bar.Print();
   Bar.PrintLine();


   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "PhiV:PhiZA:PhiAA";
   BranchList = BranchList + ":PhaseA2ZA:PhaseA3ZA:PhaseA2AA:PhaseA3AA";
   BranchList = BranchList + ":PhiVError:PhiZAError:PhiAAError";
   BranchList = BranchList + ":PhaseA2ZAError:PhaseA3ZAError:PhaseA2AAError:PhaseA3AAError";
   BranchList = BranchList + ":EDM:Status:SignalSize:BackgroundSize:TruthNLL:BestNLL";
   BranchList = BranchList + ":Fraction:FractionError";

   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].Phi[0];       Array[7] = Results[i].PhiError[0];
      Array[1] = Results[i].Phi[1];       Array[8] = Results[i].PhiError[2];
      Array[2] = Results[i].Phi[2];       Array[9] = Results[i].PhiError[1];
      Array[3] = Results[i].Phase[0];     Array[10] = Results[i].PhaseError[0];
      Array[4] = Results[i].Phase[0];     Array[11] = Results[i].PhaseError[0];
      Array[5] = Results[i].Phase[0];     Array[12] = Results[i].PhaseError[0];
      Array[6] = Results[i].Phase[0];     Array[13] = Results[i].PhaseError[0];

      Array[14] = Results[i].EDM;
      Array[15] = Results[i].FitStatus;

      Array[16] = SignalSize;
      Array[17] = BackgroundSize;

      Array[18] = Results[i].TruthNLL;    Array[19] = Results[i].BestNLL;

      Array[20] = Results[i].Fraction;    Array[21] = Results[i].FractionError;
      
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

bool PassLooseCut(ZALeptonVectors Vectors)
{
   if(Vectors.Lepton1.GetPT() < 2)   return false;
   if(Vectors.Lepton2.GetPT() < 2)   return false;
   if(Vectors.Photon.GetPT() < 2)    return false;

   if(Vectors.Lepton1.GetAbsEta() > 2.4)   return false;
   if(Vectors.Lepton2.GetAbsEta() > 2.4)   return false;
   if(Vectors.Photon.GetAbsEta() > 2.4)    return false;

   if(GetDR(Vectors.Lepton1, Vectors.Photon) < 0.2)   return false;
   if(GetDR(Vectors.Lepton2, Vectors.Photon) < 0.2)   return false;

   double M1 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass();
   if(M1 < 4)   return false;

   return true;
}

bool PassTightCut(ZALeptonVectors Vectors)
{
   double PT1 = Vectors.Lepton1.GetPT();
   double PT2 = Vectors.Lepton2.GetPT();

   if(max(PT1, PT2) < 20)            return false;
   if(min(PT1, PT2) < 10)            return false;
   if(Vectors.Photon.GetPT() < 15)   return false;
   
   if(Vectors.Lepton1.GetAbsEta() > 2.4)   return false;
   if(Vectors.Lepton2.GetAbsEta() > 2.4)   return false;
   if(Vectors.Photon.GetAbsEta() > 2.4)    return false;

   if(GetDR(Vectors.Lepton1, Vectors.Photon) < 0.2)   return false;
   if(GetDR(Vectors.Lepton2, Vectors.Photon) < 0.2)   return false;

   double M1 = (Vectors.Lepton1 + Vectors.Lepton2).GetMass();
   if(M1 < 50)   return false;

   return true;
}

void ReadEvents(vector<SingleEvent> &Events, string FileName)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return;

   DataHelper DHFile("ZANormalization.dh");
   double NormalizationS[36] = {0};
   double NormalizationB[1] = {0};

   int Linking[36] = {0};
   Linking[0] = 0;     // A2ZAR x A2ZAR
   Linking[1] = 0;     // A2ZAI x A2ZAI -
   Linking[2] = 1;     // A3ZAR x A3ZAR
   Linking[3] = 2;     // A3ZAI x A3ZAI
   Linking[4] = 3;     // A2AAR x A2AAR
   Linking[5] = 4;     // A2AAI x A2AAI
   Linking[6] = 5;     // A3AAR x A3AAR
   Linking[7] = 6;     // A3AAI x A3AAI
   Linking[8] = 999;   // A2ZAR x A2ZAI -
   Linking[9] = 7;     // A2ZAR x A3ZAR
   Linking[10] = 8;    // A2ZAR x A3ZAI
   Linking[11] = 9;    // A2ZAR x A2AAR
   Linking[12] = 10;   // A2ZAR x A2AAI
   Linking[13] = 11;   // A2ZAR x A3AAR
   Linking[14] = 12;   // A2ZAR x A3AAI
   Linking[15] = -8;   // A2ZAI x A3ZAR -
   Linking[16] = 7;    // A2ZAI x A3ZAI -
   Linking[17] = -10;  // A2ZAI x A2AAR -
   Linking[18] = 9;    // A2ZAI x A2AAI -
   Linking[19] = -12;  // A2ZAI x A3AAR -
   Linking[20] = 11;   // A2ZAI x A3AAI -
   Linking[21] = 13;   // A3ZAR x A3ZAI
   Linking[22] = 14;   // A3ZAR x A2AAR
   Linking[23] = 15;   // A3ZAR x A2AAI
   Linking[24] = 16;   // A3ZAR x A3AAR
   Linking[25] = 17;   // A3ZAR x A3AAI
   Linking[26] = 18;   // A3ZAI x A2AAR
   Linking[27] = 19;   // A3ZAI x A2AAI
   Linking[28] = 20;   // A3ZAI x A3AAR
   Linking[29] = 21;   // A3ZAI x A3AAI
   Linking[30] = 22;   // A2AAR x A2AAI
   Linking[31] = 23;   // A2AAR x A3AAR
   Linking[32] = 24;   // A2AAR x A3AAI
   Linking[33] = 25;   // A2AAI x A3AAR
   Linking[34] = 26;   // A2AAI x A3AAI
   Linking[35] = 27;   // A3AAR x A3AAI

   for(int i = 0; i < 36; i++)
   {
      char NumberString[10] = "";
      sprintf(NumberString, "X%02d", i + 1);

#ifdef USE_LOOSE_CUT
      NormalizationS[i] = DHFile["Loose"][NumberString].GetDouble();
#elif defined USE_TIGHT_CUT
      NormalizationS[i] = DHFile["Tight"][NumberString].GetDouble();
#endif
   }

#ifdef USE_LOOSE_CUT
      NormalizationB[0] = DHFile["Loose"]["XB"].GetDouble() / BackgroundNormalizationCorrection;
#elif defined USE_TIGHT_CUT
      NormalizationB[0] = DHFile["Tight"]["XB"].GetDouble() / BackgroundNormalizationCorrection;
#endif

   double ValueS[28] = {0};
   double ValueB[1] = {0};
    
   vector<string> Suffix = GetHLLZASignalSuffixList();

   for(int i = 0; i < 28; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &ValueS[i]);
   Tree->SetBranchAddress("B2", &ValueB[0]);

   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, PPT, PEta, PPhi;
   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("PPT", &PPT);
   Tree->SetBranchAddress("PEta", &PEta);
   Tree->SetBranchAddress("PPhi", &PPhi);

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 1000 || (iE % (EntryCount / 1000) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      ZALeptonVectors Vectors;
      Vectors.Lepton1.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Vectors.Lepton2.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Vectors.Photon.SetPtEtaPhi(PPT, PEta, PPhi);

      ZAEventParameters Event = ConvertVectorsToAnglesRoberto(Vectors);

      if(Event.HMass > 135 || Event.HMass < 115)
         continue;

#ifdef USE_LOOSE_CUT
      if(PassLooseCut(Vectors) == false)
         continue;
#elif defined USE_TIGHT_CUT
      if(PassTightCut(Vectors) == false)
         continue;
#endif

      double ExpandedValue[36] = {0};
      for(int i = 0; i < 36; i++)
      {
         if(Linking[i] >= 0 && Linking[i] < 36)
            ExpandedValue[i] = ValueS[Linking[i]];
         else if(Linking[i] >= -35)
            ExpandedValue[i] = -ValueS[-Linking[i]];
         else
            ExpandedValue[i] = 0;
      }

      SingleEvent NewEvent;

      for(int i = 0; i < 36; i++)
         NewEvent.vs[i] = ExpandedValue[i];
      for(int i = 0; i < 36; i++)
         NewEvent.is[i] = NormalizationS[i];
      NewEvent.vb[0] = ValueB[0];
      NewEvent.ib[0] = NormalizationB[0];
      NewEvent.event = Event;

      Events.push_back(NewEvent);
   }
   
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   random_shuffle(Events.begin(), Events.end());

   cout << "Events read: " << Events.size() << endl;
}


