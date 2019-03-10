#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"
#include "Code/DrawRandom.h"

#include "AngleConversion.h"
#include "Cuts.h"

#include "Likelihood.h"
#include "ReducedLikelihood.h"

#include "FitClass.h"

#define MAXEVENT 50000
#define MAXDATASET 50000

#define MODE_FIXB 0
#define MODE_FLOATB 1

struct EventCount;
int main(int argc, char *argv[]);
vector<Likelihood> ReadTree(string FileName, char Cut, bool IsEM);

struct EventCount
{
   double SEM;
   double BEM;
   double SEE;
   double BEE;
   EventCount(double sem = -1, double bem = -1, double see = -1, double bee = -1)
   {
      SEM = sem;
      BEM = bem;
      SEE = see;
      BEE = bee;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " SignalEM SignalEE BackgroundEM BackgroundEE Cut Tag" << endl;
      return -1;
   }

   // Basic inputs
   char Cut = 'F';
   string Tag = "A1UU_F";
   string SEMFileName = "Phto2e2mu_A1UU_18p4GeV_noPDF_ForEff_1.root";
   string SEEFileName = "Phto4e_A1UU_18p4GeV_noPDF_ForEff_1.root";
   string BEMFileName = "ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root";
   string BEEFileName = "ddbar_noPDF_to_4e_18p4GeV_GenCuts_1.root";

   SEMFileName = argv[1];
   SEEFileName = argv[2];
   BEMFileName = argv[3];
   BEEFileName = argv[4];
   Cut = argv[5][0];
   Tag = argv[6];

   // Setup scenarios
   vector<EventCount> Scenarios;
   Scenarios.push_back(EventCount(-1, -1, 5, -1));
   Scenarios.push_back(EventCount(-1, -1, 7, -1));
   Scenarios.push_back(EventCount(-1, -1, 10, -1));
   Scenarios.push_back(EventCount(-1, -1, 14, -1));
   Scenarios.push_back(EventCount(-1, -1, 20, -1));
   Scenarios.push_back(EventCount(-1, -1, 30, -1));
   Scenarios.push_back(EventCount(-1, -1, 50, -1));
   Scenarios.push_back(EventCount(-1, -1, 70, -1));
   Scenarios.push_back(EventCount(-1, -1, 100, -1));
   Scenarios.push_back(EventCount(-1, -1, 140, -1));
   Scenarios.push_back(EventCount(-1, -1, 200, -1));
   Scenarios.push_back(EventCount(-1, -1, 300, -1));
   Scenarios.push_back(EventCount(-1, -1, 500, -1));
   Scenarios.push_back(EventCount(-1, -1, 700, -1));
   Scenarios.push_back(EventCount(-1, -1, 1000, -1));
   Scenarios.push_back(EventCount(5, -1, -1, -1));
   Scenarios.push_back(EventCount(7, -1, -1, -1));
   Scenarios.push_back(EventCount(10, -1, -1, -1));
   Scenarios.push_back(EventCount(14, -1, -1, -1));
   Scenarios.push_back(EventCount(20, -1, -1, -1));
   Scenarios.push_back(EventCount(30, -1, -1, -1));
   Scenarios.push_back(EventCount(50, -1, -1, -1));
   Scenarios.push_back(EventCount(70, -1, -1, -1));
   Scenarios.push_back(EventCount(100, -1, -1, -1));
   Scenarios.push_back(EventCount(140, -1, -1, -1));
   Scenarios.push_back(EventCount(200, -1, -1, -1));
   Scenarios.push_back(EventCount(300, -1, -1, -1));
   Scenarios.push_back(EventCount(500, -1, -1, -1));
   Scenarios.push_back(EventCount(700, -1, -1, -1));
   Scenarios.push_back(EventCount(1000, -1, -1, -1));
   Scenarios.push_back(EventCount(5, -1, 5, -1));
   Scenarios.push_back(EventCount(7, -1, 7, -1));
   Scenarios.push_back(EventCount(10, -1, 10, -1));
   Scenarios.push_back(EventCount(14, -1, 14, -1));
   Scenarios.push_back(EventCount(20, -1, 20, -1));
   Scenarios.push_back(EventCount(30, -1, 30, -1));
   Scenarios.push_back(EventCount(50, -1, 50, -1));
   Scenarios.push_back(EventCount(70, -1, 70, -1));
   Scenarios.push_back(EventCount(100, -1, 100, -1));
   Scenarios.push_back(EventCount(140, -1, 140, -1));
   Scenarios.push_back(EventCount(200, -1, 200, -1));
   Scenarios.push_back(EventCount(300, -1, 300, -1));
   Scenarios.push_back(EventCount(500, -1, 500, -1));
   Scenarios.push_back(EventCount(700, -1, 700, -1));
   Scenarios.push_back(EventCount(1000, -1, 1000, -1));
   Scenarios.push_back(EventCount(5, 5, 5, 5));
   Scenarios.push_back(EventCount(7, 7, 7, 7));
   Scenarios.push_back(EventCount(10, 10, 10, 10));
   Scenarios.push_back(EventCount(14, 14, 14, 14));
   Scenarios.push_back(EventCount(20, 20, 20, 20));
   Scenarios.push_back(EventCount(30, 30, 30, 30));
   Scenarios.push_back(EventCount(50, 50, 50, 50));
   Scenarios.push_back(EventCount(70, 70, 70, 70));
   Scenarios.push_back(EventCount(100, 100, 100, 100));
   Scenarios.push_back(EventCount(140, 140, 140, 140));
   Scenarios.push_back(EventCount(200, 200, 200, 200));
   Scenarios.push_back(EventCount(300, 300, 300, 300));
   Scenarios.push_back(EventCount(500, 500, 500, 500));
   Scenarios.push_back(EventCount(700, 700, 700, 700));
   Scenarios.push_back(EventCount(1000, 1000, 1000, 1000));

   // Read events
   vector<Likelihood> SEM, BEM, SEE, BEE;

   SEM = ReadTree(SEMFileName, Cut, true);
   SEE = ReadTree(SEEFileName, Cut, false);
   BEM = ReadTree(BEMFileName, Cut, true);
   BEE = ReadTree(BEEFileName, Cut, false);

   // output trees
   TFile OutputFile(Form("FitResult_%s.root", Tag.c_str()), "recreate");

   TTree OutputTree("OutputTree", "OutputTree");

   double TreeExpectedSEM, TreeExpectedSEE, TreeExpectedBEM, TreeExpectedBEE;
   double TreeSEM, TreeSEE, TreeBEM, TreeBEE;
   double TreeP[3][3];
   double TreeE[3][3];
   int TreeMode, TreeFloatMode;
   char TreeCut;

   string Component[3] = {"VV", "VZ", "VA"};

   OutputTree.Branch("ExpectedSEM", &TreeExpectedSEM, "ExpectedSEM/D");
   OutputTree.Branch("ExpectedSEE", &TreeExpectedSEE, "ExpectedSEE/D");
   OutputTree.Branch("ExpectedBEM", &TreeExpectedBEM, "ExpectedBEM/D");
   OutputTree.Branch("ExpectedBEE", &TreeExpectedBEE, "ExpectedBEE/D");
   OutputTree.Branch("SEM", &TreeSEM, "SEM/D");
   OutputTree.Branch("SEE", &TreeSEE, "SEE/D");
   OutputTree.Branch("BEM", &TreeBEM, "BEM/D");
   OutputTree.Branch("BEE", &TreeBEE, "BEE/D");
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         OutputTree.Branch(Form("A%d%s", i + 1, Component[i].c_str()),
            &TreeP[i][j], Form("A%d%s/D", i + 1, Component[j].c_str()));
         OutputTree.Branch(Form("E%d%s", i + 1, Component[j].c_str()),
            &TreeE[i][j], Form("E%d%s/D", i + 1, Component[j].c_str()));
      }
   }
   OutputTree.Branch("Mode", &TreeMode, "Mode/I");
   OutputTree.Branch("FloatMode", &TreeFloatMode, "FloatMode/I");
   OutputTree.Branch("Cut", &TreeCut, "Cut/B");

   TreeCut = Cut;

   // Loop over scenarios
   for(int iS = 0; iS < (int)Scenarios.size(); iS++)
   {
      cout << "Now running scenario #" << iS << " with (SEM = " << Scenarios[iS].SEM << ", "
         << "SEE = " << Scenarios[iS].SEE << ", "
         << "BEM = " << Scenarios[iS].BEM << ", "
         << "BEE = " << Scenarios[iS].BEE << ")" << endl;

      TreeExpectedSEM = Scenarios[iS].SEM;
      TreeExpectedSEE = Scenarios[iS].SEE;
      TreeExpectedBEM = Scenarios[iS].BEM;
      TreeExpectedBEE = Scenarios[iS].BEE;

      // Calculate handy flags on what is there and what is not
      bool DoEM = true, DoEE = true;
      if(Scenarios[iS].SEM < 0)
         DoEM = false;
      if(Scenarios[iS].SEE < 0)
         DoEE = false;

      bool DoBEM = true, DoBEE = true;
      if(DoEM == false || (DoEM == true && Scenarios[iS].BEM < 0))
         DoBEM = false;
      if(DoEE == false || (DoEE == true && Scenarios[iS].BEE < 0))
         DoBEE = false;
      
      // Prepare to start looping
      bool Good = true;

      int SEMIndex = 0, SEEIndex = 0;

      if(Scenarios[iS].BEM > 0 && Scenarios[iS].BEM * 5 > (int)BEM.size())
         Good = false;
      if(Scenarios[iS].BEE > 0 && Scenarios[iS].BEE * 5 > (int)BEE.size())
         Good = false;

      // Looping over all events
      while(Good == true)
      {
         // Get a different set of background events - takes a lot of time!
         // random_shuffle(BEM.begin(), BEM.end());
         // random_shuffle(BEE.begin(), BEE.end());

         // Draw random numbers based on poisson distribution
         EventCount ActualCount;
         if(Scenarios[iS].SEM > 0)  ActualCount.SEM = DrawPoisson(Scenarios[iS].SEM); else ActualCount.SEM = 0;
         if(Scenarios[iS].BEM > 0)  ActualCount.BEM = DrawPoisson(Scenarios[iS].BEM); else ActualCount.BEM = 0;
         if(Scenarios[iS].SEE > 0)  ActualCount.SEE = DrawPoisson(Scenarios[iS].SEE); else ActualCount.SEE = 0;
         if(Scenarios[iS].BEE > 0)  ActualCount.BEE = DrawPoisson(Scenarios[iS].BEE); else ActualCount.BEE = 0;

         TreeSEM = ActualCount.SEM;
         TreeSEE = ActualCount.SEE;
         TreeBEM = ActualCount.BEM;
         TreeBEE = ActualCount.BEE;

         if(ActualCount.SEM + ActualCount.BEM >= MAXEVENT || ActualCount.SEE + ActualCount.BEE >= MAXEVENT)
         {
            cerr << "Warning!  Dataset larger than MAXEVENT!  Recompile with larger array!" << endl;
            return -1;
         }

         // Not enough events for this coming run
         if(ActualCount.SEM > 0 && SEMIndex + ActualCount.SEM > (int)SEM.size())
            Good = false;
         if(ActualCount.SEE > 0 && SEEIndex + ActualCount.SEE > (int)SEE.size())
            Good = false;

         if(Good == false)
            break;
      
         int DatasetEMSize = ActualCount.SEM + ActualCount.BEM;
         int DatasetEESize = ActualCount.SEE + ActualCount.BEE;

         // What's the expected background fraction?
         double ExpectedFEM = Scenarios[iS].BEM / (Scenarios[iS].BEM + Scenarios[iS].SEM);
         double ExpectedFEE = Scenarios[iS].BEE / (Scenarios[iS].BEE + Scenarios[iS].SEE);

         if(DoBEM == false)
            ExpectedFEM = 0;
         if(DoBEE == false)
            ExpectedFEE = 0;

         // Get dataset and evaluate models
         FitClass Fit;
         for(int i = 0; i < ActualCount.SEM; i++)
            Fit.AddPoint(SEM[SEMIndex+i], true);
         for(int i = 0; i < ActualCount.BEM; i++)
         {
            int I = (int)(DrawRandom() * BEM.size());
            Fit.AddPoint(BEM[I], true);
         }
         for(int i = 0; i < ActualCount.SEE; i++)
            Fit.AddPoint(SEE[SEEIndex+i], false);
         for(int i = 0; i < ActualCount.BEE; i++)
         {
            int I = (int)(DrawRandom() * BEE.size());
            Fit.AddPoint(BEE[I], false);
         }
         
         SEMIndex = SEMIndex + ActualCount.SEM;
         SEEIndex = SEEIndex + ActualCount.SEE;

         double AVV[48] = {0};
         bool FloatAVV[48] = {false};

         AVV[3*8+0] = 1;   // A1VV

         // Calculate fix-B result
         for(int iM = 0; iM < 9; iM++)
         {
            if(iM == 0 || iM == 1)   FloatAVV[3*8+2] = true;   // A2VV
            else                     FloatAVV[3*8+2] = false;
            if(iM == 0 || iM == 2)   FloatAVV[3*8+4] = true;   // A3VV
            else                     FloatAVV[3*8+4] = false;
            if(iM == 0 || iM == 3)   FloatAVV[1*8+0] = true;   // A1ZV
            else                     FloatAVV[1*8+0] = false;
            if(iM == 0 || iM == 4)   FloatAVV[1*8+2] = true;   // A2ZV
            else                     FloatAVV[1*8+2] = false;
            if(iM == 0 || iM == 5)   FloatAVV[1*8+4] = true;   // A3ZV
            else                     FloatAVV[1*8+4] = false;
            if(iM == 0 || iM == 6)   FloatAVV[4*8+0] = true;   // A1AV
            else                     FloatAVV[4*8+0] = false;
            if(iM == 0 || iM == 7)   FloatAVV[4*8+2] = true;   // A2AV
            else                     FloatAVV[4*8+2] = false;
            if(iM == 0 || iM == 8)   FloatAVV[4*8+4] = true;   // A3AV
            else                     FloatAVV[4*8+4] = false;
            
            FitConfiguration Configuration;
            for(int i = 0; i < 48; i++)   Configuration.AVV[i] = AVV[i];
            for(int i = 0; i < 48; i++)   Configuration.FloatAVV[i] = FloatAVV[i];

            Configuration.FEM = ExpectedFEM;
            Configuration.FEE = ExpectedFEE;

            Configuration.FloatFEM = false;
            Configuration.FloatFEE = false;

            FitResult Result = Fit.DoFit(Configuration);

            TreeP[0][0] = Result.AVV.AVV.A1VVR;   TreeE[0][0] = Result.AVVError.AVV.A1VVR;
            TreeP[1][0] = Result.AVV.AVV.A2VVR;   TreeE[1][0] = Result.AVVError.AVV.A2VVR;
            TreeP[2][0] = Result.AVV.AVV.A3VVR;   TreeE[2][0] = Result.AVVError.AVV.A3VVR;
            TreeP[0][1] = Result.AVV.AVV.A1VZR;   TreeE[0][1] = Result.AVVError.AVV.A1VZR;
            TreeP[1][1] = Result.AVV.AVV.A2VZR;   TreeE[1][1] = Result.AVVError.AVV.A2VZR;
            TreeP[2][1] = Result.AVV.AVV.A3VZR;   TreeE[2][1] = Result.AVVError.AVV.A3VZR;
            TreeP[0][2] = Result.AVV.AVV.A1VAR;   TreeE[0][2] = Result.AVVError.AVV.A1VAR;
            TreeP[1][2] = Result.AVV.AVV.A2VAR;   TreeE[1][2] = Result.AVVError.AVV.A2VAR;
            TreeP[2][2] = Result.AVV.AVV.A3VAR;   TreeE[2][2] = Result.AVVError.AVV.A3VAR;
         
            TreeMode = MODE_FIXB;
            TreeFloatMode = iM;
            OutputTree.Fill();
         }

         // Calculate float-B result
         if(DoBEM == true || DoBEE == true)
         {
            for(int iM = 0; iM < 9; iM++)
            {
               if(iM == 0 || iM == 1)   FloatAVV[3*8+2] = true;   // A2VV
               else                     FloatAVV[3*8+2] = false;
               if(iM == 0 || iM == 2)   FloatAVV[3*8+4] = true;   // A3VV
               else                     FloatAVV[3*8+4] = false;
               if(iM == 0 || iM == 3)   FloatAVV[1*8+0] = true;   // A1ZV
               else                     FloatAVV[1*8+0] = false;
               if(iM == 0 || iM == 4)   FloatAVV[1*8+2] = true;   // A2ZV
               else                     FloatAVV[1*8+2] = false;
               if(iM == 0 || iM == 5)   FloatAVV[1*8+4] = true;   // A3ZV
               else                     FloatAVV[1*8+4] = false;
               if(iM == 0 || iM == 6)   FloatAVV[4*8+0] = true;   // A1AV
               else                     FloatAVV[4*8+0] = false;
               if(iM == 0 || iM == 7)   FloatAVV[4*8+2] = true;   // A2AV
               else                     FloatAVV[4*8+2] = false;
               if(iM == 0 || iM == 8)   FloatAVV[4*8+4] = true;   // A3AV
               else                     FloatAVV[4*8+4] = false;
               
               FitConfiguration Configuration;
               for(int i = 0; i < 48; i++)   Configuration.AVV[i] = AVV[i];
               for(int i = 0; i < 48; i++)   Configuration.FloatAVV[i] = FloatAVV[i];

               Configuration.FEM = ExpectedFEM;
               Configuration.FEE = ExpectedFEE;

               if(DoBEM == true)   Configuration.FloatFEM = true;
               if(DoBEE == true)   Configuration.FloatFEE = true;

               FitResult Result = Fit.DoFit(Configuration);

               TreeP[0][0] = Result.AVV.AVV.A1VVR;   TreeE[0][0] = Result.AVVError.AVV.A1VVR;
               TreeP[1][0] = Result.AVV.AVV.A2VVR;   TreeE[1][0] = Result.AVVError.AVV.A2VVR;
               TreeP[2][0] = Result.AVV.AVV.A3VVR;   TreeE[2][0] = Result.AVVError.AVV.A3VVR;
               TreeP[0][1] = Result.AVV.AVV.A1VZR;   TreeE[0][1] = Result.AVVError.AVV.A1VZR;
               TreeP[1][1] = Result.AVV.AVV.A2VZR;   TreeE[1][1] = Result.AVVError.AVV.A2VZR;
               TreeP[2][1] = Result.AVV.AVV.A3VZR;   TreeE[2][1] = Result.AVVError.AVV.A3VZR;
               TreeP[0][2] = Result.AVV.AVV.A1VAR;   TreeE[0][2] = Result.AVVError.AVV.A1VAR;
               TreeP[1][2] = Result.AVV.AVV.A2VAR;   TreeE[1][2] = Result.AVVError.AVV.A2VAR;
               TreeP[2][2] = Result.AVV.AVV.A3VAR;   TreeE[2][2] = Result.AVVError.AVV.A3VAR;

               TreeMode = MODE_FLOATB;
               TreeFloatMode = iM;
               OutputTree.Fill();
            }
         }   // if there is a need for background fraction floating
      }   // while good
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

vector<Likelihood> ReadTree(string FileName, char Cut, bool IsEM)
{
   vector<Likelihood> Result;
   // Result.reserve(100000);

   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("Tree");

   if(T == NULL)
      return Result;

   Likelihood Messenger;
   double L1ID;   double L1PT, L1Eta, L1Phi;
   double L2ID;   double L2PT, L2Eta, L2Phi;
   double L3ID;   double L3PT, L3Eta, L3Phi;
   double L4ID;   double L4PT, L4Eta, L4Phi;

   T->SetBranchAddress("L1ID", &L1ID);
   T->SetBranchAddress("L1PT", &L1PT);
   T->SetBranchAddress("L1Eta", &L1Eta);
   T->SetBranchAddress("L1Phi", &L1Phi);
   T->SetBranchAddress("L2ID", &L2ID);
   T->SetBranchAddress("L2PT", &L2PT);
   T->SetBranchAddress("L2Eta", &L2Eta);
   T->SetBranchAddress("L2Phi", &L2Phi);
   T->SetBranchAddress("L3ID", &L3ID);
   T->SetBranchAddress("L3PT", &L3PT);
   T->SetBranchAddress("L3Eta", &L3Eta);
   T->SetBranchAddress("L3Phi", &L3Phi);
   T->SetBranchAddress("L4ID", &L4ID);
   T->SetBranchAddress("L4PT", &L4PT);
   T->SetBranchAddress("L4Eta", &L4Eta);
   T->SetBranchAddress("L4Phi", &L4Phi);

   Messenger.SetBranchAddress(T);

   vector<string> Suffix = GetXVVSignalSuffixList();

   string Prefix = "XX";
   Prefix[0] = ((IsEM == true) ? 'T' : 'V');
   Prefix[1] = Cut;

   double IS[72][72] = {{0}};
   double IB = 0;

   DataHelper DHFile("Normalization.dh");
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         IS[i][j] = DHFile["0TeV"][Prefix+"1_"+Suffix[i]+"_"+Suffix[j]].GetDouble();
   IB = DHFile["0TeV"][Prefix+"2_DDbar"].GetDouble() * 2;

   // if(Cut == 'P' && IsEM == false)
   //    IS[32][32] = IS[32][32] / 1.02;

   Messenger.SetIS(IS);
   Messenger.SetIB(IB);

   Messenger.InitializeLikelihoodCalculation();

   int EntryCount = T->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || iE % (EntryCount / 150) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      T->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Messenger.CalculateLikelihood(Leptons, L1ID, L3ID);

      Leptons = Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[Cut-'A'] == false)
         continue;

      Result.push_back(Messenger);
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   F.Close();

   cout << "File " << FileName << ": " << Result.size() << "/" << EntryCount << " selected" << endl;

   return Result;
}










