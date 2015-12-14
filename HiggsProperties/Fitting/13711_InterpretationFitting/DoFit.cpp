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
#include "Cuts.h"
#include "Lists.h"
#include "Constants.h"

#include "FitClass.h"
#include "StockM4l.h"

int main(int argc, char *argv[]);
void ReadEvents(vector<SingleEvent> &Events, string FileName, string CutLabel, bool UseStockM4l);
class FileHandle
{
public:
   string FileName;
   string CutLabel;
   StockM4l M4l;
   bool UseStockM4l;
   int CurrentIndex;
   DataHelper DHFile;
   TFile *File;
   TTree *Tree;
public:
   double l1id, l3id;
   double Value[154][5];
   double Integral[154][5];
   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   double Weight;
public:
   FileHandle(string filename, string cutlabel, bool usestockm4l);
   ~FileHandle();
   bool GiveNextEvent(SingleEvent &Event, bool Recycle = false);
};

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   PrintConstants();

   srand(time(NULL));

   string SEMFileName, SEEFileName, BEMFileName, BEEFileName;
   double SEMSize, SEESize, BEMSize, BEESize;
   string CutLabel = "A";

   if(argc <= 18)
   {
      cerr << "Usage: " << argv[0]
         << " SignalEMFile SignalEMSize BackgroundEMFile BackgroundEMSize"
         << " SignalEEFile SignalEESize BackgroundEEFile BackgroundEESize CutLabel"
         << " A2ZZ A3ZZ A4ZZ A5ZZ YT YTPhase MT GWW MW"
         << endl;
      return -1;
   }

   SEMFileName = argv[1];
   SEMSize = atof(argv[2]);
   BEMFileName = argv[3];
   BEMSize = atof(argv[4]);
   SEEFileName = argv[5];
   SEESize = atof(argv[6]);
   BEEFileName = argv[7];
   BEESize = atof(argv[8]);
   CutLabel = argv[9];

   double A2ZZ = atof(argv[10]);
   double A3ZZ = atof(argv[11]);
   double A4ZZ = atof(argv[12]);
   double A5ZZ = atof(argv[13]);
   double YT = atof(argv[14]);
   double YTPhase = atof(argv[15]);
   double MT = atof(argv[16]);
   double GWW = atof(argv[17]);
   double MW = atof(argv[18]);

   cout << "INITIAL " << YT << " " << YTPhase << " " << MT << " " << GWW << " " << MW << endl;

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   FileHandle SEM(SEMFileName, CutLabel, true);
   FileHandle BEM(BEMFileName, CutLabel, false);
   FileHandle SEE(SEEFileName, CutLabel, true);
   FileHandle BEE(BEEFileName, CutLabel, false);

   vector<FitResultSummary> Results;

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 255; i++)
   {
      if(i % 16 != 7 && i % 16 != 0 && i % 16 != 3)
         continue;

      string As = "NNNNNNNNN";
      if((i / 1) % 2 == 1)     As[0] = 'Y';
      if((i / 2) % 2 == 1)     As[1] = 'Y';
      if((i / 4) % 2 == 1)     As[2] = 'Y';
      if((i / 8) % 2 == 1)     As[3] = 'Y';
      if((i / 16) % 2 == 1)    As[4] = 'Y';
      if((i / 32) % 2 == 1)    As[5] = 'Y';
      if((i / 64) % 2 == 1)    As[6] = 'Y';
      if((i / 128) % 2 == 1)   As[7] = 'Y';
      if((i / 256) % 2 == 1)   As[8] = 'Y';

      string Phases = "NNNN";

      string Fs = "NNNN";
      if(BEMSize >= 0)
         Fs[0] = 'Y';
      if(BEESize >= 0)
         Fs[2] = 'Y';

      vector<double> AValues = ListToVector(9, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = A2ZZ;
      AValues[1] = A3ZZ;
      AValues[2] = A4ZZ;
      AValues[3] = A5ZZ;
      AValues[4] = YT;
      AValues[5] = YTPhase;
      AValues[6] = MT;
      AValues[7] = GWW;
      AValues[8] = MW;

      Configurations.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), 0, 0, 0),
         ListToVector(2, 0, 0),
         1.00));
   }

   int BackgroundCounter = 0;

   bool MoreEvents = true;
   while(MoreEvents == true)
   {
      int SEMCount = (SEMSize >= 0 ? DrawPoisson(SEMSize) : 0);
      int SEECount = (SEESize >= 0 ? DrawPoisson(SEESize) : 0);
      int BEMCount = (BEMSize >= 0 ? DrawPoisson(BEMSize) : 0);
      int BEECount = (BEESize >= 0 ? DrawPoisson(BEESize) : 0);

      SingleEvent NewEvent;
      bool Good = true;
      for(int i = 0; i < SEMCount; i++)
      {
         if(SEM.GiveNextEvent(NewEvent, false) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < SEECount; i++)
      {
         if(SEE.GiveNextEvent(NewEvent, false) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEMCount; i++)
      {
         if(BEM.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEECount; i++)
      {
         if(BEE.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }

      if(Good == false)
         break;

      Fits.SignalStateCount[0] = SEMCount;
      Fits.SignalStateCount[1] = 0;
      Fits.SignalStateCount[2] = SEECount;
      Fits.SignalStateCount[3] = 0;
      
      Fits.BackgroundStateCount[0] = BEMCount;
      Fits.BackgroundStateCount[1] = 0;
      Fits.BackgroundStateCount[2] = BEECount;
      Fits.BackgroundStateCount[3] = 0;
      
      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitConfiguration Temp = Configurations[iC];
         FitResultSummary ResultTemp;

         // cout << iC << endl;

         /*
         if(Temp.FloatFem == true || Temp.FloatFme == true || Temp.FloatFee == true || Temp.FloatFmm == true)
         {
            Temp.SetFloatFractions("NNNN");

            ResultTemp = Fits.DoFit(Temp);
            ResultTemp.A2ZZA1ZZ = 0;

            Temp = Configurations[iC];
            Temp.SetFloatAs("NNNNNNNN");
            Temp.SetInitialRatios(
               ListToVector(8,
                  ResultTemp.A2ZZA1ZZ, ResultTemp.A3ZZA1ZZ,
                  ResultTemp.A2ZAA1ZZ, ResultTemp.A3ZAA1ZZ,
                  ResultTemp.A2AAA1ZZ, ResultTemp.A3AAA1ZZ,
                  ResultTemp.A4ZZA1ZZ, ResultTemp.A5ZZA1ZZ
               )
            );
            
            ResultTemp = Fits.DoFit(Temp);
            
            Temp = Configurations[iC];
            Temp.SetInitialRatios(
               ListToVector(8,
                  ResultTemp.A2ZZA1ZZ, ResultTemp.A3ZZA1ZZ,
                  ResultTemp.A2ZAA1ZZ, ResultTemp.A3ZAA1ZZ,
                  ResultTemp.A2AAA1ZZ, ResultTemp.A3AAA1ZZ,
                  ResultTemp.A4ZZA1ZZ, ResultTemp.A5ZZA1ZZ
               )
            );
            Temp.SetInitialFractions(
               ListToVector(4,
                  ResultTemp.Fem,
                  ResultTemp.Fme,
                  ResultTemp.Fee,
                  ResultTemp.Fmm
               )
            );

            ResultTemp = Fits.DoFit(Temp);
         }
         else
            ResultTemp = Fits.DoFit(Temp);
         */

         ResultTemp = Fits.DoFit(Temp);

         Results.push_back(ResultTemp);
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }
      
   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";
   BranchList = BranchList + ":YT:YTPhase:MT";
   BranchList = BranchList + ":N1:N2:Fem:Fme:Fee:Fmm";
   BranchList = BranchList + ":A2ZZA1ZZError:A2ZZPhaseError:A3ZZA1ZZError:A3ZZPhaseError";
   BranchList = BranchList + ":YTError:YTPhaseError:MTError";
   BranchList = BranchList + ":N1Error:N2Error:FemError:FmeError:FeeError:FmmError";
   BranchList = BranchList + ":EDM:Status:Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";
   BranchList = BranchList + ":RatioFloats:NFloats:I1ZZModification:TruthNLL:BestNLL";
   BranchList = BranchList + ":A4ZZA1ZZ:A4ZZPhase:A5ZZA1ZZ:A5ZZPhase";
   BranchList = BranchList + ":A4ZZA1ZZError:A4ZZPhaseError:A5ZZA1ZZError:A5ZZPhaseError";
   BranchList = BranchList + ":GWW:MW";
   BranchList = BranchList + ":GWWError:MWError";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].A2ZZA1ZZ;     Array[13] = Results[i].A2ZZA1ZZError;
      Array[1] = Results[i].A2ZZPhase;    Array[14] = Results[i].A2ZZPhaseError;
      Array[2] = Results[i].A3ZZA1ZZ;     Array[15] = Results[i].A3ZZA1ZZError;
      Array[3] = Results[i].A3ZZPhase;    Array[16] = Results[i].A3ZZPhaseError;
      Array[4] = Results[i].YT;           Array[17] = Results[i].YTError;
      Array[5] = Results[i].YTPhase;      Array[18] = Results[i].YTPhaseError;
      Array[6] = Results[i].MT;           Array[19] = Results[i].MTError;
      Array[7] = Results[i].N1;           Array[20] = Results[i].N1Error;
      Array[8] = Results[i].N2;           Array[21] = Results[i].N2Error;
      Array[9] = Results[i].Fem;          Array[22] = Results[i].FemError;
      Array[10] = Results[i].Fme;         Array[23] = Results[i].FmeError;
      Array[11] = Results[i].Fee;         Array[24] = Results[i].FeeError;
      Array[12] = Results[i].Fmm;         Array[25] = Results[i].FmmError;

      Array[26] = Results[i].EDM;
      Array[27] = Results[i].FitStatus;

      Array[28] = Results[i].Sem;         Array[32] = Results[i].Bem;
      Array[29] = Results[i].Sme;         Array[33] = Results[i].Bme;
      Array[30] = Results[i].See;         Array[34] = Results[i].Bee;
      Array[31] = Results[i].Smm;         Array[35] = Results[i].Bmm;

      Array[36] = 0;
      Array[37] = 0;
      Array[38] = Results[i].I1ZZModificationFactor;

      Array[39] = Results[i].TruthNLL;    Array[40] = Results[i].BestNLL;

      Array[41] = Results[i].A4ZZA1ZZ;    Array[45] = Results[i].A4ZZA1ZZError;
      Array[42] = Results[i].A4ZZPhase;   Array[46] = Results[i].A4ZZPhaseError;
      Array[43] = Results[i].A5ZZA1ZZ;    Array[47] = Results[i].A5ZZA1ZZError;
      Array[44] = Results[i].A5ZZPhase;   Array[48] = Results[i].A5ZZPhaseError;

      Array[49] = Results[i].GWW;         Array[51] = Results[i].GWWError;
      Array[50] = Results[i].MW;          Array[52] = Results[i].MWError;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

FileHandle::~FileHandle()
{
   if(File != NULL)
   {
      File->Close();
      delete File;
   }
}

bool FileHandle::GiveNextEvent(SingleEvent &NewEvent, bool Recycle)
{
   if(Tree == NULL || File == NULL)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == false)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == true && Tree->GetEntries() == 0)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == true && Tree->GetEntries() > 0)
      CurrentIndex = 0;

   string SignalBranch[] = {"TA1", "TA3", "TA5", "TA7", "TA9"};
   string BackgroundBranch[] = {"TA2", "TA4", "TA6", "TA8", "TA10"};
   for(int i = 0; i < 5; i++)
   {
      SignalBranch[i][1] = CutLabel[0];
      BackgroundBranch[i][1] = CutLabel[0];
   }

   vector<string> Suffix = GetHLLSignalSuffixList();
   int iE = CurrentIndex;

   Tree->GetEntry(iE);
   CurrentIndex = CurrentIndex + 1;

   l1id = fabs(l1id);
   l3id = fabs(l3id);

   LeptonVectors Leptons;
   Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
   Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
   Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
   Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

   if(l1id == l3id)
      Leptons = Leptons.ReorderLeptons4e();
   else
      Leptons = Leptons.ReorderLeptons2e2mu();

   EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);
   if(UseStockM4l == true)
   {
      double Ratio = M4l[iE] / Event.HMass;
      Event.HMass = Event.HMass * Ratio;
      Event.ZMass = Event.ZMass * Ratio;
      Event.Z2Mass = Event.Z2Mass * Ratio;
      Leptons = ConvertAnglesToVectorsRoberto(Event);
   }

   if(Event.HMass > 135 || Event.HMass < 115)
      return GiveNextEvent(NewEvent);

   int CutIndex = CutLabel[0] - 'A';
   if(PassPairingCuts(Leptons)[CutIndex] == false)
      return GiveNextEvent(NewEvent);

   string State = "";
   if(l1id == 11 && l3id == 11)   State = "ee";
   if(l1id == 11 && l3id == 13)   State = "em";
   // if(l1id == 13 && l3id == 11)   State = "me";
   // if(l1id == 13 && l3id == 13)   State = "mm";

   string DHState = "Cut" + CutLabel;

   if(State == "em")
   {
      for(int i = 0; i < 5; i++)
         SignalBranch[i][0] = 'T', BackgroundBranch[i][0] = 'T';
   }
   else
   {
      for(int i = 0; i < 5; i++)
         SignalBranch[i][0] = 'V', BackgroundBranch[i][0] = 'V';
   }

   if(State == "")   // WTF
      return false;
   else
   {
      for(int j = 0; j < 5; j++)
      {
         Integral[0][j] = DHFile[DHState][BackgroundBranch[j]].GetDouble();
         for(int i = 1; i < 154; i++)
         {
            char BranchSuffix[100] = "";
            sprintf(BranchSuffix, "_%03d", i);
            string Branch = SignalBranch[j] + BranchSuffix;
            Integral[i][j] = DHFile[DHState][Branch].GetDouble();
         }
      }
   }

   for(int i = 0; i < 154; i++)
   {
      for(int j = 1; j < 5; j++)
      {
         Value[i][j] = Value[i][0];
         Integral[i][j] = Integral[i][0];
      }
   }

   bool Good = true;
   for(int i = 0; i < 154; i++)
      for(int j = 0; j < 5; j++)
         if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50))
            Good = false;
   if(Good == false)
      return GiveNextEvent(NewEvent);

   for(int i = 0; i < 154; i++)
      for(int j = 0; j < 5; j++)
         NewEvent.v[i][j] = Value[i][j];
   for(int i = 0; i < 154; i++)
      for(int j = 0; j < 5; j++)
         NewEvent.i[i][j] = Integral[i][j];
   NewEvent.event = Event;
   NewEvent.state = State;

   return true;
}

FileHandle::FileHandle(string filename, string cutlabel, bool usestockm4l)
   : M4l(31426, 100000), DHFile("Normalization.dh")
{
   FileName = filename;
   CutLabel = cutlabel;
   UseStockM4l = usestockm4l;
   CurrentIndex = 0;

   File = NULL;
   Tree = NULL;

   File = new TFile(FileName.c_str());
   Tree = (TTree *)File->Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File->Get("Tree");
   if(Tree == NULL)
      return;
   
   Tree->SetBranchAddress("L1ID", &l1id);
   Tree->SetBranchAddress("L3ID", &l3id);
   
   vector<string> Suffix = GetHLLSignalSuffixList();

   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);

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
   // Tree->SetBranchAddress("Weight", &Weight);
}


