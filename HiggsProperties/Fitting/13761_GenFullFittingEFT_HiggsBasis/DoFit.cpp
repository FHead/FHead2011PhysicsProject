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
#include "Constants.h"

#include "FitClass.h"
#include "StockM4l.h"

int main(int argc, char *argv[]);
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
   double VS[16][16];
   double IS[16][16];
   double VB;
   double IB;
   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
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
         << " DeltaCZ DeltaCW DeltaM CZZ CZZD CZA CZAD CAA CAAD"
         << endl;
      return -1;
   }

   SEMFileName = argv[1];   SEMSize = atof(argv[2]);
   BEMFileName = argv[3];   BEMSize = atof(argv[4]);
   SEEFileName = argv[5];   SEESize = atof(argv[6]);
   BEEFileName = argv[7];   BEESize = atof(argv[8]);
   CutLabel = argv[9];

   double DeltaCZ = atof(argv[10]);
   double DeltaCW = atof(argv[11]);
   double DeltaM  = atof(argv[12]);
   double CZZ     = atof(argv[13]);
   double CZZD    = atof(argv[14]);
   double CZA     = atof(argv[15]);
   double CZAD    = atof(argv[16]);
   double CAA     = atof(argv[17]);
   double CAAD    = atof(argv[18]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   FileHandle SEM(SEMFileName, CutLabel, true);
   FileHandle BEM(BEMFileName, CutLabel, false);
   FileHandle SEE(SEEFileName, CutLabel, true);
   FileHandle BEE(BEEFileName, CutLabel, false);

   vector<FitResultSummary> Results;

   // DeltaCZ = 1
   // DeltaCW = 2
   // DeltaM  = 4
   // CZZ     = 8
   // CZZD    = 16
   // CZA     = 32
   // CZAD    = 64
   // CAA     = 128
   // CAAD    = 256

   vector<int> IntConfigurations;
   IntConfigurations.push_back(0 + 2 + 0 + 0 +  0 +  0 +  0 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 4 + 0 +  0 +  0 +  0 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 8 +  0 +  0 +  0 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 0 + 16 +  0 +  0 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 0 +  0 + 32 +  0 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 0 +  0 +  0 + 64 +   0 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 0 +  0 +  0 +  0 + 128 +   0);
   IntConfigurations.push_back(0 + 0 + 0 + 0 +  0 +  0 +  0 +   0 + 256);
   IntConfigurations.push_back(0 + 0 + 0 + 8 + 16 + 32 + 64 + 128 + 256);
   IntConfigurations.push_back(0 + 2 + 0 + 8 + 16 + 32 + 64 + 128 + 256);
   IntConfigurations.push_back(0 + 0 + 4 + 8 + 16 + 32 + 64 + 128 + 256);

   vector<FitConfiguration> Configurations;
   for(int i = 0; i < (int)IntConfigurations.size(); i++)
   {
      int Index = IntConfigurations[i];

      string As = "NNNNNNNNN";
      if((Index / 1)   % 2 == 1)   As[0] = 'Y';
      if((Index / 2)   % 2 == 1)   As[1] = 'Y';
      if((Index / 4)   % 2 == 1)   As[2] = 'Y';
      if((Index / 8)   % 2 == 1)   As[3] = 'Y';
      if((Index / 16)  % 2 == 1)   As[4] = 'Y';
      if((Index / 32)  % 2 == 1)   As[5] = 'Y';
      if((Index / 64)  % 2 == 1)   As[6] = 'Y';
      if((Index / 128) % 2 == 1)   As[7] = 'Y';
      if((Index / 256) % 2 == 1)   As[8] = 'Y';

      string Fs = "NNNN";
      if(BEMSize >= 0)         Fs[0] = 'Y';
      if(BEESize >= 0)         Fs[2] = 'Y';

      double TrueFem = BEMSize / (BEMSize + SEMSize);
      double TrueFee = BEESize / (BEESize + SEESize);

      if(BEMSize < 0 || TrueFem <= 0)   TrueFem = 0;
      if(BEESize < 0 || TrueFee <= 0)   TrueFee = 0;

      vector<double> AValues = ListToVector(9, 0, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = DeltaCZ;
      AValues[1] = DeltaCW;
      AValues[2] = DeltaM;
      AValues[3] = CZZ;
      AValues[4] = CZZD;
      AValues[5] = CZA;
      AValues[6] = CZAD;
      AValues[7] = CAA;
      AValues[8] = CAAD;

      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false));
      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true));
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

         FitResultSummary ResultTemp = Fits.DoFit(Temp);

         Results.push_back(ResultTemp);
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }
      
   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "EDM:Status:TruthNLL:BestNLL";        // 4
   BranchList = BranchList + ":DeltaCZ:DeltaCZError";              // 6
   BranchList = BranchList + ":DeltaCW:DeltaCWError";              // 8
   BranchList = BranchList + ":DeltaM:DeltaMError";                // 10
   BranchList = BranchList + ":CZZ:CZZError";                      // 12    
   BranchList = BranchList + ":CZZD:CZZDError";                    // 14
   BranchList = BranchList + ":CZA:CZAError";                      // 16
   BranchList = BranchList + ":CZAD:CZADError";                    // 18
   BranchList = BranchList + ":CAA:CAAError";                      // 20
   BranchList = BranchList + ":CAAD:CAADError";                    // 22
   BranchList = BranchList + ":Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";   // 30
   BranchList = BranchList + ":Fem:FemError";                      // 32
   BranchList = BranchList + ":Fme:FmeError";                      // 34
   BranchList = BranchList + ":Fee:FeeError";                      // 36
   BranchList = BranchList + ":Fmm:FmmError";                      // 38
   BranchList = BranchList + ":NoSquareMode";                      // 39
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100] = {0};

      Array[0] = Results[i].EDM;          Array[1] = Results[i].FitStatus;
      Array[2] = Results[i].TruthNLL;     Array[3] = Results[i].BestNLL;

      Array[4] = Results[i].DeltaCZ;      Array[5] = Results[i].DeltaCZError;
      Array[6] = Results[i].DeltaCW;      Array[7] = Results[i].DeltaCWError;
      Array[8] = Results[i].DeltaM;       Array[9] = Results[i].DeltaMError;
      Array[10] = Results[i].CZZ;         Array[11] = Results[i].CZZError;
      Array[12] = Results[i].CZZD;        Array[13] = Results[i].CZZDError;
      Array[14] = Results[i].CZA;         Array[15] = Results[i].CZAError;
      Array[16] = Results[i].CZAD;        Array[17] = Results[i].CZADError;
      Array[18] = Results[i].CAA;         Array[19] = Results[i].CAAError;
      Array[20] = Results[i].CAAD;        Array[21] = Results[i].CAADError;

      Array[22] = Results[i].Sem;         Array[26] = Results[i].Bem;
      Array[23] = Results[i].Sme;         Array[27] = Results[i].Bme;
      Array[24] = Results[i].See;         Array[28] = Results[i].Bee;
      Array[25] = Results[i].Smm;         Array[29] = Results[i].Bmm;

      Array[30] = Results[i].Fem;         Array[31] = Results[i].FemError;
      Array[32] = Results[i].Fme;         Array[33] = Results[i].FmeError;
      Array[34] = Results[i].Fee;         Array[35] = Results[i].FeeError;
      Array[36] = Results[i].Fmm;         Array[37] = Results[i].FmmError;

      Array[38] = Results[i].NoSquareMode;

      OutputTree.Fill(Array);
   }

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

   string SignalBranch = "TA1";
   string BackgroundBranch = "TA2";

   SignalBranch[1] = CutLabel[0];
   BackgroundBranch[1] = CutLabel[0];

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
   if(l1id == l3id)   State = "ee";
   if(l1id != l3id)   State = "em";

   string DHState = "Cut" + CutLabel;

   if(State == "em")
      SignalBranch[0] = 'T', BackgroundBranch[0] = 'T';
   else
      SignalBranch[0] = 'V', BackgroundBranch[0] = 'V';

   if(State == "")   // WTF
      return false;
   else
   {
      string Suffix[16];
      Suffix[0]  = "A1ZZR";
      Suffix[1]  = "A2ZZR";
      Suffix[2]  = "A3ZZR";
      Suffix[3]  = "A4ZZR";
      Suffix[4]  = "A1ZAR";
      Suffix[5]  = "A2ZAR";
      Suffix[6]  = "A3ZAR";
      Suffix[7]  = "A4ZAR";
      Suffix[8]  = "A1AZR";
      Suffix[9]  = "A2AZR";
      Suffix[10] = "A3AZR";
      Suffix[11] = "A4AZR";
      Suffix[12] = "A1AAR";
      Suffix[13] = "A2AAR";
      Suffix[14] = "A3AAR";
      Suffix[15] = "A4AAR";

      for(int i = 0; i < 16; i++)
      {
         for(int j = 0; j < 16; j++)
         {
            string Branch = SignalBranch + "_" + Suffix[i] + "_" + Suffix[j];
            IS[i][j] = DHFile[DHState][Branch].GetDouble();
         }
      }
      IB = DHFile[DHState][BackgroundBranch].GetDouble();
   }

   // bool Good = true;
   // for(int i = 0; i < 16; i++)
   //    if(VS[i][i] > 0.99 || VS[i][i] < 1e-50)
   //       Good = false;
   // if(Good == false)
   //    return GiveNextEvent(NewEvent);

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         NewEvent.VS[i][j] = VS[i][j];
   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         NewEvent.IS[i][j] = IS[i][j];
   NewEvent.VB = VB;
   NewEvent.IB = IB;
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
   
   string Suffix[16];
   Suffix[0]  = "A1ZZR";
   Suffix[1]  = "A2ZZR";
   Suffix[2]  = "A3ZZR";
   Suffix[3]  = "A4ZZR";
   Suffix[4]  = "A1ZAR";
   Suffix[5]  = "A2ZAR";
   Suffix[6]  = "A3ZAR";
   Suffix[7]  = "A4ZAR";
   Suffix[8]  = "A1AZR";
   Suffix[9]  = "A2AZR";
   Suffix[10] = "A3AZR";
   Suffix[11] = "A4AZR";
   Suffix[12] = "A1AAR";
   Suffix[13] = "A2AAR";
   Suffix[14] = "A3AAR";
   Suffix[15] = "A4AAR";

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         Tree->SetBranchAddress(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), &VS[i][j]);
   Tree->SetBranchAddress("B2", &VB);

   Tree->SetBranchAddress("L1PT",  &l1pt);
   Tree->SetBranchAddress("L1Eta", &l1eta);
   Tree->SetBranchAddress("L1Phi", &l1phi);
   Tree->SetBranchAddress("L2PT",  &l2pt);
   Tree->SetBranchAddress("L2Eta", &l2eta);
   Tree->SetBranchAddress("L2Phi", &l2phi);
   Tree->SetBranchAddress("L3PT",  &l3pt);
   Tree->SetBranchAddress("L3Eta", &l3eta);
   Tree->SetBranchAddress("L3Phi", &l3phi);
   Tree->SetBranchAddress("L4PT",  &l4pt);
   Tree->SetBranchAddress("L4Eta", &l4eta);
   Tree->SetBranchAddress("L4Phi", &l4phi);
}


