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
#include "ReadFile.h"

#include "FitClass.h"

#define MODELCOUNT 8
#define MAXEVENT 50000
#define MAXDATASET 50000

class EventFile;
struct EventCount;
int main(int argc, char *argv[]);
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

   if(argc != 11)
   {
      cerr << "Usage: " << argv[0] << "SignalEM SignalEE BackgroundEM BackgroundEE Cut Tag SEM SEE BEM BEE" << endl;
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

   double ExpectedSEM = atof(argv[7]);
   double ExpectedSEE = atof(argv[8]);
   double ExpectedBEM = atof(argv[9]);
   double ExpectedBEE = atof(argv[10]);

   // Setup scenarios
   vector<EventCount> Scenarios;
   Scenarios.push_back(EventCount(ExpectedSEM, ExpectedBEM, ExpectedSEE, ExpectedBEE));

   // Get models to play with
   vector<FullAVVBasis> Models = GetModels();

   // Read events
   FileHandle SEM(SEMFileName, Cut, false, true);
   FileHandle SEE(SEEFileName, Cut, false, false);
   FileHandle BEM(BEMFileName, Cut, true, true);
   FileHandle BEE(BEEFileName, Cut, true, false);

   // output pdf
   PdfFileHelper PdfFile("ResultHypothesisTesting_" + Tag + ".pdf");
   PdfFile.AddTextPage("Hypothesis testing (" + Tag + ")");

   // Loop over scenarios
   for(int iS = 0; iS < (int)Scenarios.size(); iS++)
   {
      cout << "Now running scenario #" << iS << " with (SEM = " << Scenarios[iS].SEM << ", "
         << "SEE = " << Scenarios[iS].SEE << ", "
         << "BEM = " << Scenarios[iS].BEM << ", "
         << "BEE = " << Scenarios[iS].BEE << ")" << endl;

      // output text file
      ofstream out_fix("LikelihoodFixed_" + Tag + Form("_Scenario%d", iS));
      ofstream out_float("LikelihoodFloated_" + Tag + Form("_Scenario%d", iS));
      ofstream out_fix_A2UV("LikelihoodFixedA2UV_" + Tag + Form("_Scenario%d", iS));
      ofstream out_float_A2UV("LikelihoodFloatedA2UV_" + Tag + Form("_Scenario%d", iS));

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

      // Likelihood values for datasets
      int DatasetCount = 0;
      double *LLFixB[MODELCOUNT];
      double *LLFloatB[MODELCOUNT];
      double *LLFixBFloatA2UV[MODELCOUNT];
      double *LLFloatBFloatA2UV[MODELCOUNT];

      for(int i = 0; i < MODELCOUNT; i++)
      {
         LLFixB[i] = new double[MAXDATASET];
         LLFloatB[i] = new double[MAXDATASET];
         LLFixBFloatA2UV[i] = new double[MAXDATASET];
         LLFloatBFloatA2UV[i] = new double[MAXDATASET];
      }

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
         Good = true;
         
         FitClass Fit;
         for(int i = 0; i < ActualCount.SEM && Good == true; i++)
         {
            if(SEM.IsThereNext())   Fit.AddPoint(SEM.GetNextEvent(), true);
            else                    Good = false;
         }
         for(int i = 0; i < ActualCount.BEM && Good == true; i++)
         {
            if(BEM.IsThereNext())   Fit.AddPoint(BEM.GetNextEvent(), true);
            else                    Good = false;
         }
         for(int i = 0; i < ActualCount.SEE && Good == true; i++)
         {
            if(SEE.IsThereNext())   Fit.AddPoint(SEE.GetNextEvent(), false);
            else                    Good = false;
         }
         for(int i = 0; i < ActualCount.BEE && Good == true; i++)
         {
            if(BEE.IsThereNext())   Fit.AddPoint(BEE.GetNextEvent(), false);
            else                    Good = false;
         }
         
         // Not enough events for this coming run
         if(Good == false)
            break;

         // Calculate fix-B result
         for(int iM = 0; iM < (int)Models.size(); iM++)
         {
            FitConfiguration Configuration;
            Configuration.SetAVV(Models[iM]);

            Configuration.FEM = ExpectedFEM;
            Configuration.FEE = ExpectedFEE;

            Configuration.FloatFEM = false;
            Configuration.FloatFEE = false;

            double LL = Fit.DoFit(Configuration).BestLL;

            LLFixB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
            
            if(DoBEM == false && DoBEE == false)
               LLFloatB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
         }

         // Calculate float-B result
         if(DoBEM == true || DoBEE == true)
         {
            for(int iM = 0; iM < (int)Models.size(); iM++)
            {
               FitConfiguration Configuration;
               Configuration.SetAVV(Models[iM]);

               Configuration.FEM = ExpectedFEM;
               Configuration.FEE = ExpectedFEE;

               if(DoBEM == true)   Configuration.FloatFEM = true;
               if(DoBEE == true)   Configuration.FloatFEE = true;

               double LL = Fit.DoFit(Configuration).BestLL;

               LLFloatB[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
            }   // model loop
         }   // if there is a need for background fraction floating

         // Calculate fix-B, A2UZ+A2UA floating result
         for(int iM = 0; iM < (int)Models.size(); iM++)
         {
            FitConfiguration Configuration;
            Configuration.SetAVV(Models[iM]);

            // Ordering: ZZ, ZV, ZA, VV, VA, AA
            //    each of them A1R A1I A2R A2I A3R A3I A4R A4I
            Configuration.FloatAVV[1*8+2] = true;   // A2ZVR
            Configuration.FloatAVV[4*8+2] = true;   // A2VAR

            Configuration.FEM = ExpectedFEM;
            Configuration.FEE = ExpectedFEE;

            Configuration.FloatFEM = false;
            Configuration.FloatFEE = false;

            double LL = Fit.DoFit(Configuration).BestLL;

            LLFixBFloatA2UV[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
            
            if(DoBEM == false && DoBEE == false)
               LLFloatBFloatA2UV[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
         }

         // Calculate float-B result
         if(DoBEM == true || DoBEE == true)
         {
            for(int iM = 0; iM < (int)Models.size(); iM++)
            {
               FitConfiguration Configuration;
               Configuration.SetAVV(Models[iM]);

               // Ordering: ZZ, ZV, ZA, VV, VA, AA
               //    each of them A1R A1I A2R A2I A3R A3I A4R A4I
               Configuration.FloatAVV[1*8+2] = true;   // A2ZVR
               Configuration.FloatAVV[4*8+2] = true;   // A2VAR

               Configuration.FEM = ExpectedFEM;
               Configuration.FEE = ExpectedFEE;

               if(DoBEM == true)   Configuration.FloatFEM = true;
               if(DoBEE == true)   Configuration.FloatFEE = true;

               double LL = Fit.DoFit(Configuration).BestLL;

               LLFloatBFloatA2UV[iM][DatasetCount] = LL / (DatasetEMSize + DatasetEESize);
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
      for(int i = 0; i < DatasetCount; i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_fix_A2UV << LLFixBFloatA2UV[iM][i] << " ";
         out_fix_A2UV << endl;
      }
      for(int i = 0; i < DatasetCount; i++)
      {
         for(int iM = 0; iM < (int)Models.size(); iM++)
            out_float_A2UV << LLFloatBFloatA2UV[iM][i] << " ";
         out_float_A2UV << endl;
      }

      // Close files
      out_float.close();
      out_fix.close();
      out_float_A2UV.close();
      out_fix_A2UV.close();

      // Clean up
      for(int i = 0; i < MODELCOUNT; i++)
      {
         delete[] LLFixB[i];
         delete[] LLFloatB[i];
         delete[] LLFixBFloatA2UV[i];
         delete[] LLFloatBFloatA2UV[i];
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<FullAVVBasis> GetModels()
{
   vector<FullAVVBasis> Models(MODELCOUNT);

   Models[0].AVV.A1VVR = 1;

   Models[1].AVV.A2VVR = 1;

   Models[2].AVV.A3VVR = 1;

   Models[3].AVV.A2VAR = 1;
   Models[3].AVV.A2AVR = 1;

   Models[4].AVV.A2ZVR = 1;
   Models[4].AVV.A2VZR = 1;
   
   Models[5].AVV.A1VVR = 1;
   Models[5].AVV.A3VVR = 1;
   
   Models[6].AVV.A1VVR = 1;
   Models[6].AVV.A1VZR = 1;
   Models[6].AVV.A1ZVR = 1;
   
   Models[7].AVV.A1VVR = 1;
   Models[7].AVV.A1VVI = 1;
   Models[7].AVV.A1VZR = 1;
   Models[7].AVV.A1ZVR = 1;
   Models[7].AVV.A1VZI = 1;
   Models[7].AVV.A1ZVI = 1;

   return Models;
}









