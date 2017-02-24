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

struct EventCount;
int main();
vector<Likelihood> ReadTree(string FileName, char Cut, bool IsEM);
vector<FullAVVBasis> GetModels();

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

int main()
{
   SetThesisStyle();

   char Cut = 'F';

   // Basic inputs
   string Tag = "A1UU_F";

   // Setup scenarios
   vector<EventCount> Scenarios;
   Scenarios.push_back(EventCount(5, 5, -1, -1));
   Scenarios.push_back(EventCount(10, 10, -1, -1));
   Scenarios.push_back(EventCount(20, 20, -1, -1));
   Scenarios.push_back(EventCount(50, 50, -1, -1));
   Scenarios.push_back(EventCount(100, 100, -1, -1));
   Scenarios.push_back(EventCount(200, 200, -1, -1));

   // Get models to play with
   vector<FullAVVBasis> Models = GetModels();

   // Read events
   vector<Likelihood> SEM, BEM, SEE, BEE;

   SEM = ReadTree("Phto2e2mu_A1UU_18p4GeV_noPDF_ForEff_1.root", Cut, true);
   BEM = ReadTree("ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root", Cut, true);

   // output pdf
   PdfFileHelper PdfFile("ResultHypothesisTesting_" + Tag + ".pdf");
   PdfFile.AddTextPage("Hypothesis testing (" + Tag + ")");

   // Loop over scenarios
   for(int iS = 0; iS < (int)Scenarios.size(); iS++)
   {
      // output text file
      ofstream out_fix("LikelihoodFixed_" + Tag + Form("_Scenario%d", iS));
      ofstream out_float("LikelihoodFloated_" + Tag + Form("_Scenario%d", iS));

      // Calculate handy flags on what is there and what is not
      bool DoEM = true, DoEE = true;
      if(Scenarios[iS].SEM < 0)
         DoEM = false;
      if(Scenarios[iS].SEE < 0)
         DoEE = false;

      bool DoBEM = true, DoBEE = true;
      if(DoEM == false || (DoEM == true && Scenarios[iS].BEM < 0))
         DoBEM = false;
      if(DoEM == false || (DoEE == true && Scenarios[iS].BEE < 0))
         DoBEE = false;
      
      // Prepare to start looping
      bool Good = true;

      int SEMIndex = 0, SEEIndex = 0;

      if(Scenarios[iS].BEM > 0 && Scenarios[iS].BEM * 10 > (int)BEM.size())
         Good = false;
      if(Scenarios[iS].BEE > 0 && Scenarios[iS].BEE * 10 > (int)BEE.size())
         Good = false;

      // Likelihood values for datasets
      vector<vector<double>> LLFixB(Models.size());
      vector<vector<double>> LLFloatB(Models.size());

      // Looping over all events
      while(Good == true)
      {
         // Get a different set of background events
         random_shuffle(BEM.begin(), BEM.end());
         random_shuffle(BEE.begin(), BEE.end());

         // Draw random numbers based on poisson distribution
         EventCount ActualCount;
         if(Scenarios[iS].SEM > 0)  ActualCount.SEM = DrawPoisson(Scenarios[iS].SEM);
         if(Scenarios[iS].BEM > 0)  ActualCount.BEM = DrawPoisson(Scenarios[iS].BEM);
         if(Scenarios[iS].SEE > 0)  ActualCount.SEE = DrawPoisson(Scenarios[iS].SEE);
         if(Scenarios[iS].BEE > 0)  ActualCount.BEE = DrawPoisson(Scenarios[iS].BEE);

         // Not enough events for this coming run
         if(ActualCount.SEM > 0 && SEMIndex + ActualCount.SEM > (int)SEM.size())
            Good = false;
         if(ActualCount.SEE > 0 && SEEIndex + ActualCount.SEE > (int)SEE.size())
            Good = false;

         if(Good == false)
            break;
      
         // Get dataset
         vector<Likelihood> DatasetEM, DatasetEE;

         for(int i = 0; i < ActualCount.SEM; i++)
            DatasetEM.push_back(SEM[SEMIndex+i]);
         for(int i = 0; i < ActualCount.SEE; i++)
            DatasetEE.push_back(SEE[SEEIndex+i]);
         for(int i = 0; i < ActualCount.BEM; i++)
            DatasetEM.push_back(BEM[i]);
         for(int i = 0; i < ActualCount.BEE; i++)
            DatasetEE.push_back(BEE[i]);

         SEMIndex = SEMIndex + ActualCount.SEM;
         SEEIndex = SEEIndex + ActualCount.SEE;

         // What's the expected background fraction?
         double ExpectedFEM = Scenarios[iS].BEM / (Scenarios[iS].BEM + Scenarios[iS].SEM);
         double ExpectedFEE = Scenarios[iS].BEE / (Scenarios[iS].BEE + Scenarios[iS].SEE);

         if(DoBEM == false)
            ExpectedFEM = 0;
         if(DoBEE == false)
            ExpectedFEE = 0;

         // Calculate fix-B result
         for(int iM = 0; iM < (int)Models.size(); iM++)
         {
            double LL = 0;

            if(DoEM == true)
               for(int i = 0; i < (int)DatasetEM.size(); i++)
                  LL = LL + log(DatasetEM[i].Apply(Models[iM], ExpectedFEM));
            if(DoEE == true)
               for(int i = 0; i < (int)DatasetEE.size(); i++)
                  LL = LL + log(DatasetEE[i].Apply(Models[iM], ExpectedFEE));

            LLFixB[iM].push_back(LL / (DatasetEM.size() + DatasetEE.size()));
         
            // let's put some dummy thing here and upgrade later
            LLFloatB[iM].push_back(LL / (DatasetEM.size() + DatasetEE.size()));
         }

         // Calculate float-B result
         //
         // See above in fix-B section - placeholder is put there
      }

      if(LLFixB[0].size() == 0 || LLFloatB[0].size() == 0)   // no result
         continue;

      // Make plots, and profit!

      vector<string> ScenarioString(10);

      ScenarioString[0] = "Scenario:";
      ScenarioString[1] = "";
      ScenarioString[2] = Form("   S_{2e2#mu} = %.2f", Scenarios[iS].SEM);
      ScenarioString[3] = Form("   B_{2e2#mu} = %.2f", Scenarios[iS].BEM);
      ScenarioString[4] = Form("   S_{4e/4#mu} = %.2f", Scenarios[iS].SEE);
      ScenarioString[5] = Form("   B_{4e/4#mu} = %.2f", Scenarios[iS].BEE);
      PdfFile.AddTextPage(ScenarioString);

      // LL distribution - fix B
      for(int iM = 0; iM < (int)Models.size(); iM++)
      {
         double Min = LLFixB[iM][0];
         double Max = LLFixB[iM][0];

         for(int i = 0; i < (int)LLFixB[iM].size(); i++)
         {
            if(Min > LLFixB[iM][i])   Min = LLFixB[iM][i];
            if(Max < LLFixB[iM][i])   Max = LLFixB[iM][i];
         }

         double Range = Max - Min;
         Min = Min - Range * 0.1;
         Max = Max + Range * 0.1;

         TH1D H("H", Form(";LL with F fixed (Model %d)", iM), 200, Min, Max);
         
         for(int i = 0; i < (int)LLFixB[iM].size(); i++)
            H.Fill(LLFixB[iM][i]);

         H.SetStats(0);

         PdfFile.AddPlot(H);
      }
      
      // LL distribution - float B
      for(int iM = 0; iM < (int)Models.size(); iM++)
      {
         double Min = LLFloatB[iM][0];
         double Max = LLFloatB[iM][0];

         for(int i = 0; i < (int)LLFloatB[iM].size(); i++)
         {
            if(Min > LLFloatB[iM][i])   Min = LLFloatB[iM][i];
            if(Max < LLFloatB[iM][i])   Max = LLFloatB[iM][i];
         }

         double Range = Max - Min;
         Min = Min - Range * 0.1;
         Max = Max + Range * 0.1;

         TH1D H("H", Form(";LL with F floated (Model %d);", iM), 200, Min, Max);
         
         for(int i = 0; i < (int)LLFloatB[iM].size(); i++)
            H.Fill(LLFloatB[iM][i]);

         H.SetStats(0);

         PdfFile.AddPlot(H);
      }

      // LL difference - fix B
      for(int iM1 = 0; iM1 < (int)Models.size(); iM1++)
      {
         for(int iM2 = iM1 + 1; iM2 < (int)Models.size(); iM2++)
         {
            double Min = LLFixB[iM1][0] - LLFixB[iM2][0];
            double Max = LLFixB[iM1][0] - LLFixB[iM2][0];

            for(int i = 0; i < (int)LLFixB[iM1].size(); i++)
            {
               if(Min > LLFixB[iM1][i] - LLFixB[iM2][i])   Min = LLFixB[iM1][i] - LLFixB[iM2][i];
               if(Max < LLFixB[iM1][i] - LLFixB[iM2][i])   Max = LLFixB[iM1][i] - LLFixB[iM2][i];
            }

            double Range = Max - Min;
            Min = Min - Range * 0.1;
            Max = Max + Range * 0.1;

            TH1D H("H", Form(";LL with F fixed (Model %d - Model %d);", iM1, iM2), 200, Min, Max);

            for(int i = 0; i < (int)LLFixB[iM1].size(); i++)
               H.Fill(LLFixB[iM1][i] - LLFixB[iM2][i]);

            H.SetStats(0);

            PdfFile.AddPlot(H);
         }
      }
      
      // LL difference - float B
      for(int iM1 = 0; iM1 < (int)Models.size(); iM1++)
      {
         for(int iM2 = iM1 + 1; iM2 < (int)Models.size(); iM2++)
         {
            double Min = LLFloatB[iM1][0] - LLFloatB[iM2][0];
            double Max = LLFloatB[iM1][0] - LLFloatB[iM2][0];

            for(int i = 0; i < (int)LLFloatB[iM1].size(); i++)
            {
               if(Min > LLFloatB[iM1][i] - LLFloatB[iM2][i])   Min = LLFloatB[iM1][i] - LLFloatB[iM2][i];
               if(Max < LLFloatB[iM1][i] - LLFloatB[iM2][i])   Max = LLFloatB[iM1][i] - LLFloatB[iM2][i];
            }

            double Range = Max - Min;
            Min = Min - Range * 0.1;
            Max = Max + Range * 0.1;

            TH1D H("H", Form(";LL with F floated (Model %d - Model %d);", iM1, iM2), 200, Min, Max);

            for(int i = 0; i < (int)LLFloatB[iM1].size(); i++)
               H.Fill(LLFloatB[iM1][i] - LLFloatB[iM2][i]);

            H.SetStats(0);

            PdfFile.AddPlot(H);
         }
      }

      // Export result into text files
      for(int i = 0; i < (int)LLFixB[0].size(); i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_fix << LLFixB[iM][i] << " ";
         out_fix << endl;
      }
      for(int i = 0; i < (int)LLFloatB[0].size(); i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_float << LLFloatB[iM][i] << " ";
         out_float << endl;
      }

      // Close files
      out_float.close();
      out_fix.close();
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<Likelihood> ReadTree(string FileName, char Cut, bool IsEM)
{
   vector<Likelihood> Result;

   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("Tree");

   Likelihood Messenger;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   T->SetBranchAddress("L1PT", &L1PT);
   T->SetBranchAddress("L1Eta", &L1Eta);
   T->SetBranchAddress("L1Phi", &L1Phi);
   T->SetBranchAddress("L2PT", &L2PT);
   T->SetBranchAddress("L2Eta", &L2Eta);
   T->SetBranchAddress("L2Phi", &L2Phi);
   T->SetBranchAddress("L3PT", &L3PT);
   T->SetBranchAddress("L3Eta", &L3Eta);
   T->SetBranchAddress("L3Phi", &L3Phi);
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

   int EntryCount = T->GetEntries() * 0.2;
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || iE % (EntryCount / 300) == 0)
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

      Leptons = Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[Cut-'A'] == false)
         continue;

      for(int i = 0; i < 72; i++)
         for(int j = 0; j < 72; j++)
            Messenger.IS[i][j] = IS[i][j];
      Messenger.IB = IB;

      Result.push_back(Messenger);
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   F.Close();

   cout << "File " << FileName << ": " << Result.size() << "/" << EntryCount << " selected" << endl;

   return Result;
}

vector<FullAVVBasis> GetModels()
{
   vector<FullAVVBasis> Models(5);

   Models[0].AVV.A1ZZR = 1;

   Models[1].AVV.A1VVR = 1;

   Models[2].AVV.A2VVR = 1;

   Models[3].AVV.A3VVR = 1;

   Models[4].AVV.A1VVR = 1;
   Models[4].AVV.A2VVR = 1;

   return Models;
}









