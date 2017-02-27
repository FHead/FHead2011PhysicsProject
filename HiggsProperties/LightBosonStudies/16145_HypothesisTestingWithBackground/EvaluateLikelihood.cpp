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

#define MODELCOUNT 9
#define MAXEVENT 50000
#define MAXDATASET 50000

struct EventCount;
int main(int argc, char *argv[]);
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

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << "SignalEM BackgroundEM Cut Tag" << endl;
      return -1;
   }

   // Basic inputs
   char Cut = 'F';
   string Tag = "A1UU_F";
   string SEMFileName = "Phto2e2mu_A1UU_18p4GeV_noPDF_ForEff_1.root";
   string BEMFileName = "ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root";

   SEMFileName = argv[1];
   BEMFileName = argv[2];
   Cut = argv[3][0];
   Tag = argv[4];

   // Setup scenarios
   vector<EventCount> Scenarios;
   Scenarios.push_back(EventCount(10, -1, -1, -1));
   Scenarios.push_back(EventCount(50, -1, -1, -1));
   Scenarios.push_back(EventCount(200, -1, -1, -1));
   Scenarios.push_back(EventCount(1000, -1, -1, -1));
   Scenarios.push_back(EventCount(5000, -1, -1, -1));
   // Scenarios.push_back(EventCount(10, 10, -1, -1));
   // Scenarios.push_back(EventCount(50, 50, -1, -1));
   // Scenarios.push_back(EventCount(200, 200, -1, -1));
   // Scenarios.push_back(EventCount(1000, 1000, -1, -1));
   // Scenarios.push_back(EventCount(5000, 5000, -1, -1));

   // Get models to play with
   vector<FullAVVBasis> Models = GetModels();

   // Read events
   vector<Likelihood> SEM, BEM, SEE, BEE;

   SEM = ReadTree(SEMFileName, Cut, true);
   BEM = ReadTree(BEMFileName, Cut, true);

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
      if(DoEE == false || (DoEE == true && Scenarios[iS].BEE < 0))
         DoBEE = false;
      
      // Prepare to start looping
      bool Good = true;

      int SEMIndex = 0, SEEIndex = 0;

      if(Scenarios[iS].BEM > 0 && Scenarios[iS].BEM * 5 > (int)BEM.size())
         Good = false;
      if(Scenarios[iS].BEE > 0 && Scenarios[iS].BEE * 5 > (int)BEE.size())
         Good = false;

      // Likelihood values for datasets
      int DatasetCount = 0;
      double *LLFixB[MODELCOUNT];
      double *LLFloatB[MODELCOUNT];

      for(int i = 0; i < MODELCOUNT; i++)
      {
         LLFixB[i] = new double[MAXDATASET];
         LLFloatB[i] = new double[MAXDATASET];
      }
      
      // Event likelihood placeholder
      double *ValueSEM[MODELCOUNT];
      double *ValueSEE[MODELCOUNT];
      double ValueBEM[MAXEVENT] = {0};
      double ValueBEE[MAXEVENT] = {0};

      for(int i = 0; i < MODELCOUNT; i++)
      {
         ValueSEM[i] = new double[MAXEVENT];
         ValueSEE[i] = new double[MAXEVENT];
      }
      
      // Looping over all events
      while(Good == true)
      {
         // Get a different set of background events - takes a lot of time!
         // random_shuffle(BEM.begin(), BEM.end());
         // random_shuffle(BEE.begin(), BEE.end());

         // Draw random numbers based on poisson distribution
         EventCount ActualCount;
         if(Scenarios[iS].SEM > 0)  ActualCount.SEM = DrawPoisson(Scenarios[iS].SEM);
         if(Scenarios[iS].BEM > 0)  ActualCount.BEM = DrawPoisson(Scenarios[iS].BEM);
         if(Scenarios[iS].SEE > 0)  ActualCount.SEE = DrawPoisson(Scenarios[iS].SEE);
         if(Scenarios[iS].BEE > 0)  ActualCount.BEE = DrawPoisson(Scenarios[iS].BEE);

         if(ActualCount.SEM + ActualCount.BEM >= MAXEVENT || ActualCount.SEE + ActualCount.BEE >= MAXEVENT)
         {
            cerr << "Warning!  Dataset larger than MAXEVENT!  Recompile with larger array!" << endl;
            return -1;
         }

         if(DatasetCount >= MAXDATASET)
         {
            cerr << "Warning!  Too many datasets!  Recompile with larger array!" << endl;
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
         for(int i = 0; i < ActualCount.SEM; i++)
         {
            for(int iM = 0; iM < (int)Models.size(); iM++)
               ValueSEM[iM][i] = SEM[SEMIndex+i].Apply(Models[iM], 0);
            ValueBEM[i] = SEM[SEMIndex+i].Apply(Models[0], 1);
         }
         for(int i = 0; i < ActualCount.BEM; i++)
         {
            int I = (int)(DrawRandom() * BEM.size());
            for(int iM = 0; iM < (int)Models.size(); iM++)
               ValueSEM[iM][(int)ActualCount.SEM+i] = BEM[I].Apply(Models[iM], 0);
            ValueBEM[(int)ActualCount.SEM+i] = BEM[I].Apply(Models[0], 1);
         }
         for(int i = 0; i < ActualCount.SEE; i++)
         {
            for(int iM = 0; iM < (int)Models.size(); iM++)
               ValueSEE[iM][i] = SEE[SEEIndex+i].Apply(Models[iM], 0);
            ValueBEE[i] = SEE[SEEIndex+i].Apply(Models[0], 1);
         }
         for(int i = 0; i < ActualCount.BEE; i++)
         {
            int I = (int)(DrawRandom() * BEE.size());
            for(int iM = 0; iM < (int)Models.size(); iM++)
               ValueSEE[iM][(int)ActualCount.SEE+i] = BEE[I].Apply(Models[iM], 0);
            ValueBEE[(int)ActualCount.SEE+i] = BEE[I].Apply(Models[0], 1);
         }
         
         SEMIndex = SEMIndex + ActualCount.SEM;
         SEEIndex = SEEIndex + ActualCount.SEE;
         
         // Calculate fix-B result
         for(int iM = 0; iM < (int)Models.size(); iM++)
         {
            double LL = 0;

            if(DoEM == true)
               for(int i = 0; i < DatasetEMSize; i++)
                  LL = LL + log(ValueSEM[iM][i] * (1 - ExpectedFEM) + ValueBEM[i] * ExpectedFEM);
            if(DoEE == true)
               for(int i = 0; i < DatasetEESize; i++)
                  LL = LL + log(ValueSEE[iM][i] * (1 - ExpectedFEE) + ValueBEE[i] * ExpectedFEE);

            LLFixB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
            
            if(DoBEM == false && DoBEE == false)
               LLFloatB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
         }

         // Calculate float-B result
         if(DoBEM == true || DoBEE == true)
         {
            for(int iM = 0; iM < (int)Models.size(); iM++)
            {
               double LL = 0;

               double FEM = ExpectedFEM;
               double FEE = ExpectedFEE;

               int PassCount = 10;
               if(DoBEM != DoBEE)   // only 1D, only 1 pass is needed
                  PassCount = 1;

               for(int iP = 0; iP < PassCount; iP++)
               {
                  if(DoBEM == true)
                  {
                     double MinF = 0, MaxF = 1;
                     double BestF = -1;
                     double BestLL = 0;
                     
                     for(int iT = 0; iT < 5; iT++)
                     {
                        double StepSize = (MaxF - MinF) / 5;

                        for(int i = 0; i <= 5; i++)
                        {
                           double F = (MaxF - MinF) / 5 * i + MinF;
                           double CurrentLL = 0;
                           for(int j = 0; j < DatasetEMSize; j++)
                              CurrentLL = CurrentLL + log(ValueSEM[iM][j] * (1 - F) + ValueBEM[j] * F);
                           for(int j = 0; j < DatasetEESize; j++)
                              CurrentLL = CurrentLL + log(ValueSEE[iM][j] * (1 - FEE) + ValueBEE[j] * FEE);

                           if(CurrentLL == CurrentLL && (BestF < 0 || BestLL < CurrentLL))
                           {
                              BestF = F;
                              BestLL = CurrentLL;
                           }
                        }

                        MinF = BestF - StepSize;
                        MaxF = BestF + StepSize;

                        if(MinF < 0)   MinF = 0;
                        if(MaxF > 1)   MaxF = 1;
                     }

                     FEM = BestF;
                     LL = BestLL;
                  }

                  if(DoBEE == true)
                  {
                     double MinF = 0, MaxF = 1;
                     double BestF = -1;
                     double BestLL = 0;
                     
                     for(int iT = 0; iT < 5; iT++)
                     {
                        double StepSize = (MaxF - MinF) / 5;

                        for(int i = 0; i <= 5; i++)
                        {
                           double F = (MaxF - MinF) / 5 * i + MinF;
                           double CurrentLL = 0;
                           for(int j = 0; j < DatasetEMSize; j++)
                              CurrentLL = CurrentLL + log(ValueSEM[iM][j] * (1 - FEM) + ValueBEM[j] * FEM);
                           for(int j = 0; j < DatasetEESize; j++)
                              CurrentLL = CurrentLL + log(ValueSEE[iM][j] * (1 - F) + ValueBEE[j] * F);

                           if(CurrentLL == CurrentLL && (BestF < 0 || BestLL < CurrentLL))
                           {
                              BestF = F;
                              BestLL = CurrentLL;
                           }
                        }

                        MinF = BestF - StepSize;
                        MaxF = BestF + StepSize;
                        
                        if(MinF < 0)   MinF = 0;
                        if(MaxF > 1)   MaxF = 1;
                     }

                     FEE = BestF;
                     LL = BestLL;
                  }
               }

               LLFloatB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
            }   // model loop
         }   // if there is a need for background fraction floating

         DatasetCount = DatasetCount + 1;
      }   // while good

      if(DatasetCount == 0)   // no result
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

         for(int i = 0; i < DatasetCount; i++)
         {
            if(Min > LLFixB[iM][i])   Min = LLFixB[iM][i];
            if(Max < LLFixB[iM][i])   Max = LLFixB[iM][i];
         }

         double Range = Max - Min;
         Min = Min - Range * 0.1;
         Max = Max + Range * 0.1;

         TH1D H("H", Form(";LL with F fixed (Model %d)", iM), 200, Min, Max);
         
         for(int i = 0; i < DatasetCount; i++)
            H.Fill(LLFixB[iM][i]);

         H.SetStats(0);

         PdfFile.AddPlot(H);
      }
      
      // LL distribution - float B
      for(int iM = 0; iM < (int)Models.size(); iM++)
      {
         double Min = LLFloatB[iM][0];
         double Max = LLFloatB[iM][0];

         for(int i = 0; i < DatasetCount; i++)
         {
            if(Min > LLFloatB[iM][i])   Min = LLFloatB[iM][i];
            if(Max < LLFloatB[iM][i])   Max = LLFloatB[iM][i];
         }

         double Range = Max - Min;
         Min = Min - Range * 0.1;
         Max = Max + Range * 0.1;

         TH1D H("H", Form(";LL with F floated (Model %d);", iM), 200, Min, Max);
         
         for(int i = 0; i < DatasetCount; i++)
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

            for(int i = 0; i < DatasetCount; i++)
            {
               if(Min > LLFixB[iM1][i] - LLFixB[iM2][i])   Min = LLFixB[iM1][i] - LLFixB[iM2][i];
               if(Max < LLFixB[iM1][i] - LLFixB[iM2][i])   Max = LLFixB[iM1][i] - LLFixB[iM2][i];
            }

            double Range = Max - Min;
            Min = Min - Range * 0.1;
            Max = Max + Range * 0.1;

            TH1D H("H", Form(";LL with F fixed (Model %d - Model %d);", iM1, iM2), 200, Min, Max);

            for(int i = 0; i < DatasetCount; i++)
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

            for(int i = 0; i < DatasetCount; i++)
            {
               if(Min > LLFloatB[iM1][i] - LLFloatB[iM2][i])   Min = LLFloatB[iM1][i] - LLFloatB[iM2][i];
               if(Max < LLFloatB[iM1][i] - LLFloatB[iM2][i])   Max = LLFloatB[iM1][i] - LLFloatB[iM2][i];
            }

            double Range = Max - Min;
            Min = Min - Range * 0.1;
            Max = Max + Range * 0.1;

            TH1D H("H", Form(";LL with F floated (Model %d - Model %d);", iM1, iM2), 200, Min, Max);

            for(int i = 0; i < DatasetCount; i++)
               H.Fill(LLFloatB[iM1][i] - LLFloatB[iM2][i]);

            H.SetStats(0);

            PdfFile.AddPlot(H);
         }
      }

      // Export result into text files
      for(int i = 0; i < DatasetCount; i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_fix << LLFixB[iM][i] << " ";
         out_fix << endl;
      }
      for(int i = 0; i < DatasetCount; i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_float << LLFloatB[iM][i] << " ";
         out_float << endl;
      }

      // Close files
      out_float.close();
      out_fix.close();

      // Clean up
      for(int i = 0; i < MODELCOUNT; i++)
      {
         delete[] LLFixB[i];
         delete[] LLFloatB[i];

         delete[] ValueSEM[i];
         delete[] ValueSEE[i];
      }
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

   int EntryCount = T->GetEntries();
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
   vector<FullAVVBasis> Models(MODELCOUNT);

   Models[0].AVV.A1ZZR = 1;

   Models[1].AVV.A1VVR = 1;

   Models[2].AVV.A2VVR = 1;

   Models[3].AVV.A3VVR = 1;

   Models[4].AVV.A2VAR = 1;
   Models[4].AVV.A2AVR = 1;

   Models[5].AVV.A2ZVR = 1;
   Models[5].AVV.A2VZR = 1;
   
   Models[6].AVV.A1VVR = 1;
   Models[6].AVV.A3VVR = 1;
   
   Models[7].AVV.A1VVR = 1;
   Models[7].AVV.A1VZR = 1;
   Models[7].AVV.A1ZVR = 1;
   
   Models[8].AVV.A1VVR = 1;
   Models[8].AVV.A1VVI = 1;
   Models[8].AVV.A1VZR = 1;
   Models[8].AVV.A1ZVR = 1;
   Models[8].AVV.A1VZI = 1;
   Models[8].AVV.A1ZVI = 1;

   return Models;
}









