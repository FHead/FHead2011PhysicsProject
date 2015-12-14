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
   srand(time(NULL));

   string SEMFileName, SEEFileName, BEMFileName, BEEFileName;
   double SEMSize, SEESize, BEMSize, BEESize;
   string CutLabel = "A";

   if(argc <= 17)
   {
      cerr << "Usage: " << argv[0]
         << " SignalEMFile SignalEMSize BackgroundEMFile BackgroundEMSize"
         << " SignalEEFile SignalEESize BackgroundEEFile BackgroundEESize CutLabel"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA A4ZZ A5ZZ"
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
   double A2ZA = atof(argv[12]);
   double A3ZA = atof(argv[13]);
   double A2AA = atof(argv[14]);
   double A3AA = atof(argv[15]);
   double A4ZZ = atof(argv[16]);
   double A5ZZ = atof(argv[17]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   FileHandle SEM(SEMFileName, CutLabel, true);
   FileHandle BEM(BEMFileName, CutLabel, false);
   FileHandle SEE(SEEFileName, CutLabel, true);
   FileHandle BEE(BEEFileName, CutLabel, false);

   vector<FitResultSummary> Results;

   vector<FitConfiguration> Configurations;
   for(int i = 0; i <= 127; i++)
   {
      if(i != 0 && i != 63 && i != 127)
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
      if(BEMSize >= 0)
         Fs[0] = 'Y';
      if(BEESize >= 0)
         Fs[2] = 'Y';

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = A2ZZ;
      AValues[1] = A3ZZ;
      AValues[2] = A2ZA;
      AValues[3] = A3ZA;
      AValues[4] = A2AA;
      AValues[5] = A3AA;
      AValues[6] = A4ZZ;
      AValues[7] = A5ZZ;

      double InitialFEM = BEMSize / (SEMSize + BEMSize);
      double InitialFEE = BEESize / (SEESize + BEESize);

      Configurations.push_back(FitConfiguration(As, Phases, Fs, "NN",
         AValues,
         ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? InitialFEM : 0), 0, ((Fs[2] == 'Y') ? InitialFEE : 0), 0),
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
            
         Results.push_back(ResultTemp);
      }
      FitCount = FitCount + 1;

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
   BranchList = BranchList + ":A4ZZA1ZZ:A4ZZPhase:A5ZZA1ZZ:A5ZZPhase";
   BranchList = BranchList + ":A4ZZA1ZZError:A4ZZPhaseError:A5ZZA1ZZError:A5ZZPhaseError";
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

      Array[51] = Results[i].A4ZZA1ZZ;    Array[55] = Results[i].A4ZZA1ZZError;
      Array[52] = Results[i].A4ZZPhase;    Array[56] = Results[i].A4ZZPhaseError;
      Array[53] = Results[i].A5ZZA1ZZ;    Array[57] = Results[i].A5ZZA1ZZError;
      Array[54] = Results[i].A5ZZPhase;    Array[58] = Results[i].A5ZZPhaseError;
      
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

   // cout << Tree->GetEntries() << " " << CurrentIndex << endl;

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

   // cout << Value[0][0] << " " << Value[1][0] << endl;
   // cout << Integral[0][0] << " " << Integral[1][0] << endl;
   // cout << endl;

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


