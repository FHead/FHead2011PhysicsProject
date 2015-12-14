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

#include "FitClass.h"
// #include "ProjectionHelper.h"

int main(int argc, char *argv[]);
bool PassBaselineCut(EventParameters Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   srand(time(NULL));

   string FileName =  "EventF.root";
   int DatasetSize = 30;
   string BackgroundFileName = "EventF.root";
   int BackgroundDatasetSize = 30;

   if(argc <= 10)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile SignalDatasetSize BackgroundRootFile BackgroundDatasetSize"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA"
         << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);
   BackgroundFileName = argv[3];
   BackgroundDatasetSize = atoi(argv[4]);

   double A2ZZ = atof(argv[5]);
   double A3ZZ = atof(argv[6]);
   double A2ZA = atof(argv[7]);
   double A3ZA = atof(argv[8]);
   double A2AA = atof(argv[9]);
   double A3AA = atof(argv[10]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResult.ps");

   vector<SingleEvent> Signals, Backgrounds;
   ReadEvents(Signals, FileName);
   ReadEvents(Backgrounds, BackgroundFileName);

   vector<FitConfiguration> ConfigurationsA, ConfigurationsB, ConfigurationsC, ConfigurationsD, ConfigurationsE;
   for(int i = 1; i <= 63; i++)
   {
      string As = "NNNNNN";
      if((i / 1) % 2 == 1)    As[0] = 'Y';
      if((i / 2) % 2 == 1)    As[1] = 'Y';
      if((i / 4) % 2 == 1)    As[2] = 'Y';
      if((i / 8) % 2 == 1)    As[3] = 'Y';
      if((i / 16) % 2 == 1)   As[4] = 'Y';
      if((i / 32) % 2 == 1)   As[5] = 'Y';

      string Phases = "NNNNNN";

      string Fs = "NNNN";
      if(BackgroundDatasetSize > 0)
         Fs[0] = 'Y';

      vector<double> AValues = ListToVector(6, 0, 0, 0, 0, 0, 0);

      ConfigurationsA.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0)));
      
      if(As[0] == 'N')   AValues[0] = A2ZZ;
      else               AValues[0] = DrawRandom(-3, 3);
      if(As[1] == 'N')   AValues[1] = A3ZZ;
      else               AValues[1] = DrawRandom(-5, 5);
      if(As[2] == 'N')   AValues[2] = A2ZA;
      else               AValues[2] = DrawRandom(-0.1, 0.1);
      if(As[3] == 'N')   AValues[3] = A3ZA;
      else               AValues[3] = DrawRandom(-0.1, 0.1);
      if(As[4] == 'N')   AValues[4] = A2AA;
      else               AValues[4] = DrawRandom(-0.1, 0.1);
      if(As[5] == 'N')   AValues[5] = A3AA;
      else               AValues[5] = DrawRandom(-0.1, 0.1);

      ConfigurationsB.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0)));
      
      if(As[0] == 'N')   AValues[0] = A2ZZ;
      else               AValues[0] = DrawRandom(-3, 3);
      if(As[1] == 'N')   AValues[1] = A3ZZ;
      else               AValues[1] = DrawRandom(-5, 5);
      if(As[2] == 'N')   AValues[2] = A2ZA;
      else               AValues[2] = DrawRandom(-0.1, 0.1);
      if(As[3] == 'N')   AValues[3] = A3ZA;
      else               AValues[3] = DrawRandom(-0.1, 0.1);
      if(As[4] == 'N')   AValues[4] = A2AA;
      else               AValues[4] = DrawRandom(-0.1, 0.1);
      if(As[5] == 'N')   AValues[5] = A3AA;
      else               AValues[5] = DrawRandom(-0.1, 0.1);

      ConfigurationsC.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0)));
      
      if(As[0] == 'N')   AValues[0] = A2ZZ;
      else               AValues[0] = DrawRandom(-3, 3);
      if(As[1] == 'N')   AValues[1] = A3ZZ;
      else               AValues[1] = DrawRandom(-5, 5);
      if(As[2] == 'N')   AValues[2] = A2ZA;
      else               AValues[2] = DrawRandom(-0.1, 0.1);
      if(As[3] == 'N')   AValues[3] = A3ZA;
      else               AValues[3] = DrawRandom(-0.1, 0.1);
      if(As[4] == 'N')   AValues[4] = A2AA;
      else               AValues[4] = DrawRandom(-0.1, 0.1);
      if(As[5] == 'N')   AValues[5] = A3AA;
      else               AValues[5] = DrawRandom(-0.1, 0.1);

      ConfigurationsD.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0)));
      
      if(As[0] == 'N')   AValues[0] = A2ZZ;
      else               AValues[0] = DrawRandom(-3, 3);
      if(As[1] == 'N')   AValues[1] = A3ZZ;
      else               AValues[1] = DrawRandom(-5, 5);
      if(As[2] == 'N')   AValues[2] = A2ZA;
      else               AValues[2] = DrawRandom(-0.1, 0.1);
      if(As[3] == 'N')   AValues[3] = A3ZA;
      else               AValues[3] = DrawRandom(-0.1, 0.1);
      if(As[4] == 'N')   AValues[4] = A2AA;
      else               AValues[4] = DrawRandom(-0.1, 0.1);
      if(As[5] == 'N')   AValues[5] = A3AA;
      else               AValues[5] = DrawRandom(-0.1, 0.1);

      ConfigurationsE.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0)));
   }

   int BackgroundCounter = 0;

   for(int iS = 0; iS < (int)Signals.size(); iS++)
   {
      Fits.AddPoint(Signals[iS]);

      if(Signals[iS].state == "em")   Fits.SignalStateCount[0] = Fits.SignalStateCount[0] + 1;
      if(Signals[iS].state == "me")   Fits.SignalStateCount[1] = Fits.SignalStateCount[1] + 1;
      if(Signals[iS].state == "ee")   Fits.SignalStateCount[2] = Fits.SignalStateCount[2] + 1;
      if(Signals[iS].state == "mm")   Fits.SignalStateCount[3] = Fits.SignalStateCount[3] + 1;
      
      if(Fits.SampleSize < DatasetSize)
         continue;

      while(Fits.SampleSize < DatasetSize + BackgroundDatasetSize)
      {
         Fits.AddPoint(Backgrounds[BackgroundCounter]);

         if(Backgrounds[BackgroundCounter].state == "em")
            Fits.BackgroundStateCount[0] = Fits.BackgroundStateCount[0] + 1;
         if(Backgrounds[BackgroundCounter].state == "me")
            Fits.BackgroundStateCount[1] = Fits.BackgroundStateCount[1] + 1;
         if(Backgrounds[BackgroundCounter].state == "ee")
            Fits.BackgroundStateCount[2] = Fits.BackgroundStateCount[2] + 1;
         if(Backgrounds[BackgroundCounter].state == "mm")
            Fits.BackgroundStateCount[3] = Fits.BackgroundStateCount[3] + 1;

         BackgroundCounter = BackgroundCounter + 1;
         if(BackgroundCounter >= Backgrounds.size())
            BackgroundCounter = 0;
      }

      for(int iC = 0; iC < (int)ConfigurationsA.size(); iC++)
      {
         FitResultSummary ResultTemp;
         
         FitResultSummary ResultTempA = Fits.DoFit(ConfigurationsA[iC]);
         ResultTemp = ResultTempA;

         FitResultSummary ResultTempB = Fits.DoFit(ConfigurationsB[iC]);
         if(ResultTempB.NLL < ResultTemp.NLL)
            ResultTemp = ResultTempB;
         
         FitResultSummary ResultTempC = Fits.DoFit(ConfigurationsC[iC]);
         if(ResultTempC.NLL < ResultTemp.NLL)
            ResultTemp = ResultTempC;
         
         FitResultSummary ResultTempD = Fits.DoFit(ConfigurationsD[iC]);
         if(ResultTempD.NLL < ResultTemp.NLL)
            ResultTemp = ResultTempD;
         
         FitResultSummary ResultTempE = Fits.DoFit(ConfigurationsE[iC]);
         if(ResultTempE.NLL < ResultTemp.NLL)
            ResultTemp = ResultTempE;

         Results.push_back(ResultTemp);
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

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
   BranchList = BranchList + ":RatioFloats:NFloats:NLL";
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

      Array[48] = Results[i].NLL;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase1", "(A3ZAPhase+(A3ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase2", "(A3ZAPhase1-int(A3ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPrimaryPhase", "(A3ZAPhase2+(A3ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase1", "(A2ZAPhase+(A2ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase2", "(A2ZAPhase1-int(A2ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPrimaryPhase", "(A2ZAPhase2+(A2ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase1", "(A3AAPhase+(A3AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase2", "(A3AAPhase1-int(A3AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPrimaryPhase", "(A3AAPhase2+(A3AAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase1", "(A2AAPhase+(A2AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase2", "(A2AAPhase1-int(A2AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPrimaryPhase", "(A2AAPhase2+(A2AAPhase2<0)*2*3.1415926535)");

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

bool PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 4)    return false;
   if(Event.Z2Mass < 4)   return false;
   
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

   DataHelper DHFile("Normalization.dh");

   int l1id, l3id;
   Tree->SetBranchAddress("L1ID", &l1id);
   Tree->SetBranchAddress("L3ID", &l3id);

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[92][5] = {{0}};
   double Integral[92][5] = {{0}};

   string suffix[91] = {
      "A1ZZRA1ZZR",
      "A2ZZRA2ZZR",
      "A2ZZIA2ZZI",
      "A3ZZRA3ZZR",
      "A3ZZIA3ZZI",
      "A2ZARA2ZAR",
      "A2ZAIA2ZAI",
      "A3ZARA3ZAR",
      "A3ZAIA3ZAI",
      "A2AARA2AAR",
      "A2AAIA2AAI",
      "A3AARA3AAR",
      "A3AAIA3AAI",
      "A1ZZRA2ZZR",
      "A1ZZRA2ZZI",
      "A1ZZRA3ZZR",
      "A1ZZRA3ZZI",
      "A1ZZRA2ZAR",
      "A1ZZRA2ZAI",
      "A1ZZRA3ZAR",
      "A1ZZRA3ZAI",
      "A1ZZRA2AAR",
      "A1ZZRA2AAI",
      "A1ZZRA3AAR",
      "A1ZZRA3AAI",
      "A2ZZRA2ZZI",
      "A2ZZRA3ZZR",
      "A2ZZRA3ZZI",
      "A2ZZRA2ZAR",
      "A2ZZRA2ZAI",
      "A2ZZRA3ZAR",
      "A2ZZRA3ZAI",
      "A2ZZRA2AAR",
      "A2ZZRA2AAI",
      "A2ZZRA3AAR",
      "A2ZZRA3AAI",
      "A2ZZIA3ZZR",
      "A2ZZIA3ZZI",
      "A2ZZIA2ZAR",
      "A2ZZIA2ZAI",
      "A2ZZIA3ZAR",
      "A2ZZIA3ZAI",
      "A2ZZIA2AAR",
      "A2ZZIA2AAI",
      "A2ZZIA3AAR",
      "A2ZZIA3AAI",
      "A3ZZRA3ZZI",
      "A3ZZRA2ZAR",
      "A3ZZRA2ZAI",
      "A3ZZRA3ZAR",
      "A3ZZRA3ZAI",
      "A3ZZRA2AAR",
      "A3ZZRA2AAI",
      "A3ZZRA3AAR",
      "A3ZZRA3AAI",
      "A3ZZIA2ZAR",
      "A3ZZIA2ZAI",
      "A3ZZIA3ZAR",
      "A3ZZIA3ZAI",
      "A3ZZIA2AAR",
      "A3ZZIA2AAI",
      "A3ZZIA3AAR",
      "A3ZZIA3AAI",
      "A2ZARA2ZAI",
      "A2ZARA3ZAR",
      "A2ZARA3ZAI",
      "A2ZARA2AAR",
      "A2ZARA2AAI",
      "A2ZARA3AAR",
      "A2ZARA3AAI",
      "A2ZAIA3ZAR",
      "A2ZAIA3ZAI",
      "A2ZAIA2AAR",
      "A2ZAIA2AAI",
      "A2ZAIA3AAR",
      "A2ZAIA3AAI",
      "A3ZARA3ZAI",
      "A3ZARA2AAR",
      "A3ZARA2AAI",
      "A3ZARA3AAR",
      "A3ZARA3AAI",
      "A3ZAIA2AAR",
      "A3ZAIA2AAI",
      "A3ZAIA3AAR",
      "A3ZAIA3AAI",
      "A2AARA2AAI",
      "A2AARA3AAR",
      "A2AARA3AAI",
      "A2AAIA3AAR",
      "A2AAIA3AAI",
      "A3AARA3AAI"
   };
   vector<string> Suffix(suffix, suffix + 91);

   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);

   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   double Weight;
   Tree->SetBranchAddress("L1PT", &l1pt);
   Tree->SetBranchAddress("L1Eta", &l1eta);
   Tree->SetBranchAddress("L1Phi", &l1phi);
   Tree->SetBranchAddress("L2PT", &l2pt);
   Tree->SetBranchAddress("L2Eta", &l2eta);
   Tree->SetBranchAddress("L2Phi", &l2phi);
   Tree->SetBranchAddress("L3PT", &l3pt);
   Tree->SetBranchAddress("L3Eta", &l3eta);
   Tree->SetBranchAddress("L3Phi", &l3phi);
   Tree->SetBranchAddress("L4PT", &l4pt);
   Tree->SetBranchAddress("L4Eta", &l4eta);
   Tree->SetBranchAddress("L4Phi", &l4phi);
   Tree->SetBranchAddress("Weight", &Weight);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(DrawRandom(0, 1) > Weight)
         continue;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(Event.HMass > 135 || Event.HMass < 115)
         continue;
      if(PassBaselineCut(Event) == false)
         continue;

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      // if(l1id == 13 && l3id == 11)   State = "me";
      // if(l1id == 13 && l3id == 13)   State = "mm";
      
      char BranchPrefix = '\0';
      if(State == "em")   BranchPrefix = 'T';
      if(State == "me")   BranchPrefix = 'U';
      if(State == "ee")   BranchPrefix = 'V';
      if(State == "mm")   BranchPrefix = 'W';

      string DHState = State;

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
            BackgroundBranch[j][0] = BranchPrefix;
            SignalBranch[j][0] = BranchPrefix;

            Integral[0][j] = DHFile[DHState][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 92; i++)
            {
               char BranchSuffix[100] = "";
               sprintf(BranchSuffix, "_%02d", i);
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[DHState][Branch].GetDouble();
            }
         }
      }

      for(int i = 0; i < 92; i++)
      {
         // cout << i << " " << Integral[i][0] << endl;
         for(int j = 1; j < 5; j++)
         {
            Value[i][j] = Value[i][0];
            Integral[i][j] = Integral[i][0];
         }
      }

      bool Good = true;
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 1; j++)
            if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50))
               Good = false;
      if(Good == false)
         continue;

      SingleEvent NewEvent;

      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.v[i][j] = Value[i][j];
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.i[i][j] = Integral[i][j];
      NewEvent.event = Event;
      NewEvent.state = State;

      Events.push_back(NewEvent);
   }
   
   File.Close();

   random_shuffle(Events.begin(), Events.end());

   cout << "Events read: " << Events.size() << endl;
}



