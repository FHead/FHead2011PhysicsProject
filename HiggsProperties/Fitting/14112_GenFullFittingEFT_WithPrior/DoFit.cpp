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

   if(argc <= 17)
   {
      cerr << "Usage: " << argv[0]
         << " SignalEMFile SignalEMSize BackgroundEMFile BackgroundEMSize"
         << " SignalEEFile SignalEESize BackgroundEEFile BackgroundEESize CutLabel"
         << " A2ZZ A3ZZ A4ZZ A2ZA A3ZA A4ZA A2AA A3AA"
         << endl;
      return -1;
   }

   SEMFileName = argv[1];   SEMSize = atof(argv[2]);
   BEMFileName = argv[3];   BEMSize = atof(argv[4]);
   SEEFileName = argv[5];   SEESize = atof(argv[6]);
   BEEFileName = argv[7];   BEESize = atof(argv[8]);
   CutLabel = argv[9];

   double A2ZZ = atof(argv[10]);
   double A3ZZ = atof(argv[11]);
   double A4ZZ = atof(argv[12]);
   double A2ZA = atof(argv[13]);
   double A3ZA = atof(argv[14]);
   double A4ZA = atof(argv[15]);
   double A2AA = atof(argv[16]);
   double A3AA = atof(argv[17]);

   AVVBasis TrueA;
   TrueA.A1ZZ = 2;   TrueA.A2ZZ = A2ZZ;   TrueA.A3ZZ = A3ZZ;   TrueA.A4ZZ = A4ZZ;
   TrueA.A1ZA = 0;   TrueA.A2ZA = A2ZA;   TrueA.A3ZA = A3ZA;   TrueA.A4ZA = A4ZA;
   TrueA.A1AA = 0;   TrueA.A2AA = A2AA;   TrueA.A3AA = A3AA;   TrueA.A4AA = 0;

   HiggsBasis TrueH(TrueA);
   WarsawBasis TrueW(TrueA);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   FileHandle SEM(SEMFileName, CutLabel, true);
   FileHandle BEM(BEMFileName, CutLabel, false);
   FileHandle SEE(SEEFileName, CutLabel, true);
   FileHandle BEE(BEEFileName, CutLabel, false);

   vector<FitResultSummary> Results;

   vector<string> AVVConfigurations, AVVPriors;
   AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNN");
   AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNN");
   AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("YNNY");
   AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("YNNY");
   AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNN");
   AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("YNNY");

   vector<string> HiggsConfigurations, HiggsPriors;
   HiggsConfigurations.push_back("NNYNNNNN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNYNNNN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNNYNNN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNNNYNN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNNNNYN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNNNNNY");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("YNNY");
   HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("YNNY");
   HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNN");
   HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNN");

   vector<string> WarsawConfigurations, WarsawPriors;
   WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNN");
   WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("YNNY");
   WarsawConfigurations.push_back("YNNNNNNN");   WarsawPriors.push_back("NNNN");
   WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNN");
   WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNN");
   WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("YNNY");

   string Fs = "NNNN";
   if(BEMSize >= 0)         Fs[0] = 'Y';
   if(BEESize >= 0)         Fs[2] = 'Y';

   double TrueFem = BEMSize / (BEMSize + SEMSize);
   double TrueFee = BEESize / (BEESize + SEESize);

   if(BEMSize < 0 || TrueFem <= 0)   TrueFem = 0;
   if(BEESize < 0 || TrueFee <= 0)   TrueFee = 0;

   vector<FitConfiguration> Configurations;
   for(int i = 0; i < AVVConfigurations.size(); i++)
   {
      string As = AVVConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueA.A2ZZ;   AValues[1] = TrueA.A3ZZ;   AValues[2] = TrueA.A4ZZ;
      AValues[3] = TrueA.A2ZA;   AValues[4] = TrueA.A3ZA;   AValues[5] = TrueA.A4ZA;
      AValues[6] = TrueA.A2AA;   AValues[7] = TrueA.A3AA;

      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_AVV, AVVPriors[i]));
      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_AVV, AVVPriors[i]));
   }
   for(int i = 0; i < HiggsConfigurations.size(); i++)
   {
      string As = HiggsConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueH.DeltaCZ;   AValues[1] = TrueH.CZB;
      AValues[2] = TrueH.CZZ;       AValues[3] = TrueH.CZZD;
      AValues[4] = TrueH.CZA;       AValues[5] = TrueH.CZAD;
      AValues[6] = TrueH.CAA;       AValues[7] = TrueH.CAAD;

      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_HIGGS, HiggsPriors[i]));
      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_HIGGS, HiggsPriors[i]));
   }
   for(int i = 0; i < WarsawConfigurations.size(); i++)
   {
      string As = WarsawConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueW.CT;    AValues[1] = TrueW.CH;
      AValues[2] = TrueW.CWW;   AValues[3] = TrueW.CWWD;
      AValues[4] = TrueW.CWB;   AValues[5] = TrueW.CWBD;
      AValues[6] = TrueW.CBB;   AValues[7] = TrueW.CBBD;

      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_WARSAW, WarsawPriors[i]));
      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_WARSAW, WarsawPriors[i]));
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
   BranchList = BranchList + ":P1:P1Error";                        // 6
   BranchList = BranchList + ":P2:P2Error";                        // 8
   BranchList = BranchList + ":P3:P3Error";                        // 10
   BranchList = BranchList + ":P4:P4Error";                        // 12    
   BranchList = BranchList + ":P5:P5Error";                        // 14
   BranchList = BranchList + ":P6:P6Error";                        // 16
   BranchList = BranchList + ":P7:P7Error";                        // 18
   BranchList = BranchList + ":P8:P8Error";                        // 20
   BranchList = BranchList + ":Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";   // 28
   BranchList = BranchList + ":Fem:FemError";                      // 30
   BranchList = BranchList + ":Fme:FmeError";                      // 32
   BranchList = BranchList + ":Fee:FeeError";                      // 34
   BranchList = BranchList + ":Fmm:FmmError";                      // 36
   BranchList = BranchList + ":NoSquareMode:Basis";                // 38
   BranchList = BranchList + ":Prior0:Prior1:Prior2:Prior3";       // 42
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100] = {0};

      Array[0] = Results[i].EDM;          Array[1] = Results[i].FitStatus;
      Array[2] = Results[i].TruthNLL;     Array[3] = Results[i].BestNLL;

      Array[4] = Results[i].Parameter1;   Array[5] = Results[i].Parameter1Error;
      Array[6] = Results[i].Parameter2;   Array[7] = Results[i].Parameter2Error;
      Array[8] = Results[i].Parameter3;   Array[9] = Results[i].Parameter3Error;
      Array[10] = Results[i].Parameter4;  Array[11] = Results[i].Parameter4Error;
      Array[12] = Results[i].Parameter5;  Array[13] = Results[i].Parameter5Error;
      Array[14] = Results[i].Parameter6;  Array[15] = Results[i].Parameter6Error;
      Array[16] = Results[i].Parameter7;  Array[17] = Results[i].Parameter7Error;
      Array[18] = Results[i].Parameter8;  Array[19] = Results[i].Parameter8Error;

      Array[20] = Results[i].Sem;         Array[24] = Results[i].Bem;
      Array[21] = Results[i].Sme;         Array[25] = Results[i].Bme;
      Array[22] = Results[i].See;         Array[26] = Results[i].Bee;
      Array[23] = Results[i].Smm;         Array[27] = Results[i].Bmm;

      Array[28] = Results[i].Fem;         Array[29] = Results[i].FemError;
      Array[30] = Results[i].Fme;         Array[31] = Results[i].FmeError;
      Array[32] = Results[i].Fee;         Array[33] = Results[i].FeeError;
      Array[34] = Results[i].Fmm;         Array[35] = Results[i].FmmError;

      Array[36] = Results[i].NoSquareMode;
      Array[37] = Results[i].Basis;

      Array[38] = Results[i].UsedPriors[0];
      Array[39] = Results[i].UsedPriors[1];
      Array[40] = Results[i].UsedPriors[2];
      Array[41] = Results[i].UsedPriors[3];

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


