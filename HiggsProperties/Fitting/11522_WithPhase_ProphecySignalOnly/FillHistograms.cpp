//---------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"
//---------------------------------------------------------------------------
#include "PlotHelper2.h"
#include "ProgressBar.h"
#include "SetStyle.h"
//---------------------------------------------------------------------------
#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164
//---------------------------------------------------------------------------
struct Likelihoods;
struct ParameterizedLikelihoods;
int main(int argc, char *argv[]);
void SetBranchAddresses(TTree *Tree, Likelihoods &M);
ParameterizedLikelihoods FindParameters(Likelihoods M);
double CalculateLogLikelihood(ParameterizedLikelihoods P,
   double A1, double A3, double A4, double F, double NuisanceParameter);
void SynthesizeHistogram(TH2D &H);
void BlankoutHistogram(TH2D &H, const TH2D &LookUp, double Threshold);
double FindBestFractionAndNuisanceParameter(const vector<ParameterizedLikelihoods> &D,
   const double A1, const double A3, const double A4, double &F, double &N);
double FindBestNuisanceParameter(const vector<ParameterizedLikelihoods> &D,
   const double A1, const double A3, const double A4, const double F, double &N);
//---------------------------------------------------------------------------
struct Likelihoods
{
   double L1, L3, L13, L4, L14, L34, LB;
   double I1, I3, I13, I4, I14, I34, IB;
   double L1Up, L3Up, L13Up, L4Up, L14Up, L34Up, LBUp;
   double I1Up, I3Up, I13Up, I4Up, I14Up, I34Up, IBUp;
   double L1Down, L3Down, L13Down, L4Down, L14Down, L34Down, LBDown;
   double I1Down, I3Down, I13Down, I4Down, I14Down, I34Down, IBDown;
};
//---------------------------------------------------------------------------
struct ParameterizedLikelihoods
{
   double V1A, V3A, V13A, V4A, V14A, V34A, VBA;
   double V1B, V3B, V13B, V4B, V14B, V34B, VBB;
   double I1A, I3A, I13A, I4A, I14A, I34A, IBA;
   double I1B, I3B, I13B, I4B, I14B, I34B, IBB;
};
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   SetStyle();

   srand(31426);

   //////////////////////
   // Input parameters //
   //////////////////////

   string SignalFileName = "HZZ4l_Prophecy4f_125_100K_tree_11521.root";
   string DirectoryName = "zz4lTree";
   string TreeName = "probe_tree";

   ///////////////////////
   // Output parameters //
   ///////////////////////

   string OutputFileName = "FitResults";

   //////////////////////
   // Other parameters //
   //////////////////////

   int SignalDatasetSize = (argc > 1 ? atoi(argv[1]) : 30);

   ///////////////////////////////////////////
   // Output files and histograms and trees //
   ///////////////////////////////////////////

   string Tag = Form("%d", SignalDatasetSize);
   TFile OutputFile(Form("%s_%s.root", OutputFileName.c_str(), Tag.c_str()), "RECREATE");

   TNtuple OutputTree("OutputTree", "THIS IS TITLE!",
      "SignalSize:MedianFraction:PlusFraction:MinusFraction");
   
   TNtuple OutputTreeComplex("OutputTreeComplex", "THIS IS TITLE!",
      "SignalSize:ATanA3A1:A3Phase:F:N:Likelihood");

   TH1D HBestA3A1(Form("HBestA3A1_%s", Tag.c_str()),
      "Best fitted position of atan(A_{3}^{ZZ}/(5.1 A_{1}^{ZZ}))", 100, -PI / 2, PI / 2);
   TH1D HBestA3A1Real(Form("HBestA3A1Real_%s", Tag.c_str()),
      "Best fitted position of A_{3}^{ZZ}/(5.1 A_{1}^{ZZ})", 100, -100, 100);
   TH1D HBestA3Phase(Form("HBestA3Phase_%s", Tag.c_str()),
      "Best fitted phase of A_{3}^{ZZ}/A_{1}^{ZZ}", 100, 0, 2 * PI);
   TH1D HBestFraction(Form("HBestFraction_%s", Tag.c_str()),
      "Best fitted background fraction", 100, 0, 2 * PI);

   PsFileHelper PsFile(Form("%s_%s.ps", OutputFileName.c_str(), Tag.c_str()));
   PsFile.AddTextPage("Fits with nuisance parameters!");

   //////////////////////
   // Initialize trees //
   //////////////////////

   Likelihoods M;

   TFile SignalInputFile(SignalFileName.c_str());
   TTree *SignalTree = (TTree *)SignalInputFile.Get((DirectoryName + "/" + TreeName).c_str());
   SetBranchAddresses(SignalTree, M);
   
   /////////////////////////////////////////////
   // Collect likelihoods and randomize order //
   /////////////////////////////////////////////

   int SignalEntryCount = SignalTree->GetEntries();
   vector<Likelihoods> AllSignalLikelihoods(SignalEntryCount);
   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      SignalTree->GetEntry(iEntry);
      M.LB = M.LB / 4;
      M.LBUp = M.LBUp / 4;
      M.LBDown = M.LBDown / 4;
      M.IB = M.IB / 10;
      M.I1 = M.I1 / 10;
      M.I3 = M.I3 / 10;
      M.I4 = M.I4 / 10;
      M.I13 = M.I13 / 10;
      M.I14 = M.I14 / 10;
      M.I34 = M.I34 / 10;
      
      AllSignalLikelihoods[iEntry] = M;
   }
   cout << "Number of selected signal events: " << AllSignalLikelihoods.size() << endl;
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());
   random_shuffle(AllSignalLikelihoods.begin(), AllSignalLikelihoods.end());

   /////////////////////////////////////
   // Now we loop over events and fit //
   /////////////////////////////////////

   int FitCount = 0;
   int MaxFitCount = 1000;

   ProgressBar Bar(cout, MaxFitCount);
   Bar.SetStyle(4);
   Bar.Print();

   vector<ParameterizedLikelihoods> CurrentDataset(SignalDatasetSize);
   vector<double> BestFitFractions;

   for(int iEntry = 0; iEntry < SignalEntryCount; iEntry++)
   {
      ////////////////////////////////////////////////////
      // Collect dataset with correct signal and counts //
      ////////////////////////////////////////////////////

      CurrentDataset[iEntry%SignalDatasetSize] = FindParameters(AllSignalLikelihoods[iEntry]);
      
      if((iEntry + 1) % SignalDatasetSize != 0)
         continue;

      Bar.Update(FitCount);
      Bar.Print();

      //////////////////////////////
      // Now we do the rough scan //
      //////////////////////////////

      int BinCount = 100;
      if(FitCount >= 1)
         BinCount = 50;
      if(FitCount >= 10)
         BinCount = 20;

      TH2D HLikelihood("HLikelihood", "Likelihood scan;atan(A_{3}^{ZZ}/(5.1 A_{1}^{ZZ}));A_{3}^{ZZ} Phase",
         BinCount, 0, PI / 2, BinCount, 0, 2 * PI);
      TH2D HFraction("HFraction", "Best background fraction;atan(A_{3}^{ZZ}/(5.1 A_{1}^{ZZ}));A_{3}^{ZZ} Phase",
         BinCount, 0, PI / 2, BinCount, 0, 2 * PI);
      TH2D HNuisance("HNuisance", "Best nuisance position;atan(A_{3}^{ZZ}/(5.1 A_{1}^{ZZ}));A_{3}^{ZZ} Phase",
         BinCount, 0, PI / 2, BinCount, 0, 2 * PI);

      double BestA3Phase = 0;
      double BestATanA3A1 = 0;
      double BestF = 0;
      double BestN = 0;
      double BestLikelihood = 1;

      for(int iX = 1; iX <= BinCount; iX++)
      {
         for(int iY = 1; iY <= BinCount; iY++)
         {
            double A1 = 1;
            double A3 = tan(HLikelihood.GetXaxis()->GetBinCenter(iX)) * 5.1;
            double A3Phase = HLikelihood.GetYaxis()->GetBinCenter(iY);
            double A3R = A3 * cos(A3Phase);
            double A3I = A3 * sin(A3Phase);

            double F = 0;
            double N = 0;

            double Likelihood = FindBestFractionAndNuisanceParameter(CurrentDataset, A1, A3R, A3I, F, N);

            if(BestLikelihood > 0 || Likelihood > BestLikelihood)
            {
               BestA3Phase = A3Phase;
               BestATanA3A1 = HLikelihood.GetXaxis()->GetBinCenter(iX);
               BestLikelihood = Likelihood;
               BestF = F;
               BestN = N;
            }

            HLikelihood.SetBinContent(iX, iY, Likelihood);
            HFraction.SetBinContent(iX, iY, F);
            HNuisance.SetBinContent(iX, iY, N);
         }
      }

      if(FitCount < 20)   // only for the first few fits we do this
      {
         HLikelihood.SetStats(0);
         HLikelihood.Scale(-1);
         SynthesizeHistogram(HLikelihood);
         HLikelihood.SetMaximum(20);

         HFraction.SetStats(0);
         HFraction.SetMinimum(0);
         HFraction.SetMaximum(1);
         BlankoutHistogram(HFraction, HLikelihood, 20);

         HNuisance.SetStats(0);
         HNuisance.SetMinimum(-5);
         HNuisance.SetMaximum(5);
         BlankoutHistogram(HNuisance, HLikelihood, 20);

         PsFile.AddPlot(HLikelihood, "colz");
         PsFile.AddPlot(HLikelihood, "colz", false, true);
         PsFile.AddPlot(HFraction, "colz");
         PsFile.AddPlot(HNuisance, "colz");
      }

      ////////////////////////////////////////
      // Finer scan to get better precision //
      ////////////////////////////////////////

      double BinSizeX = (PI / 2) / BinCount;
      double BinSizeY = (2 * PI) / BinCount;

      for(int iTry = 0; iTry < 20; iTry++)
      {
         double CenterATanA3A1 = BestATanA3A1;
         double CenterA3Phase = BestA3Phase;

         for(int iX = -1; iX <= 1; iX++)
         {
            for(int iY = -1; iY <= 1; iY++)
            {
               double A1 = 1;
               double A3 = tan(CenterATanA3A1 + BinSizeX * iX) * 5.1;
               double A3Phase = CenterA3Phase + BinSizeY * iY;
               double A3R = A3 * cos(A3Phase);
               double A3I = A3 * sin(A3Phase);

               double F = 0;
               double N = 0;

               double Likelihood = FindBestFractionAndNuisanceParameter(CurrentDataset, A1, A3R, A3I, F, N);

               if(Likelihood > BestLikelihood || BestLikelihood > 0)
               {
                  BestATanA3A1 = CenterATanA3A1 + BinSizeX * iX;
                  BestA3Phase = A3Phase;
                  BestLikelihood = Likelihood;
                  BestF = F;
                  BestN = N;
               }
            }
         }

         BinSizeX = BinSizeX / 2;
         BinSizeY = BinSizeY / 2;
      }

      /////////////////////////
      // Do some bookkeeping //
      /////////////////////////

      HBestA3A1.Fill(BestATanA3A1);
      HBestA3A1Real.Fill(tan(BestATanA3A1) * 5.1);
      HBestA3Phase.Fill(BestA3Phase);
      HBestFraction.Fill(BestF);

      OutputTreeComplex.Fill(SignalDatasetSize, BestATanA3A1, BestA3Phase,
         BestF, BestN, BestLikelihood);

      BestFitFractions.push_back(BestF);

      FitCount = FitCount + 1;
      if(FitCount >= MaxFitCount)
         break;
   }

   Bar.Update(MaxFitCount);
   Bar.Print();
   Bar.PrintLine();

   ///////////////////////////
   // Output, cleanup, etc. //
   ///////////////////////////

   sort(BestFitFractions.begin(), BestFitFractions.end());

   SignalInputFile.Close();
   
   OutputFile.cd();

   HBestA3A1.Write();
   HBestA3A1Real.Write();
   HBestA3Phase.Write();
   HBestFraction.Write();

   OutputTreeComplex.Write();

   OutputTree.Fill(SignalDatasetSize,
      BestFitFractions[BestFitFractions.size()*0.5000],
      BestFitFractions[BestFitFractions.size()*0.8413],
      BestFitFractions[BestFitFractions.size()*0.1587]);
   OutputTree.Write();

   OutputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}
//---------------------------------------------------------------------------
void SetBranchAddresses(TTree *Tree, Likelihoods &M)
{
   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("Likelihood_ExtSig1", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3", true);
   Tree->SetBranchStatus("Likelihood_ExtSig14", true);
   Tree->SetBranchStatus("Likelihood_ExtSig34", true);
   Tree->SetBranchStatus("Likelihood_EffMEE", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig4", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig14", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig34", true);
   Tree->SetBranchStatus("LikelihoodUp_EffMEE", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig4", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig14", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig34", true);
   Tree->SetBranchStatus("LikelihoodDown_EffMEE", true);
   Tree->SetBranchStatus("Likelihood_ExtSig1_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig3_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig13_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig4_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig14_Integral", true);
   Tree->SetBranchStatus("Likelihood_ExtSig34_Integral", true);
   Tree->SetBranchStatus("Likelihood_EffMEE_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig4_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig14_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_ExtSig34_Integral", true);
   Tree->SetBranchStatus("LikelihoodUp_EffMEE_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig1_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig3_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig13_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig4_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig14_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_ExtSig34_Integral", true);
   Tree->SetBranchStatus("LikelihoodDown_EffMEE_Integral", true);
   
   Tree->SetBranchAddress("Likelihood_ExtSig1", &M.L1);
   Tree->SetBranchAddress("Likelihood_ExtSig3", &M.L3);
   Tree->SetBranchAddress("Likelihood_ExtSig13", &M.L13);
   Tree->SetBranchAddress("Likelihood_ExtSig4", &M.L4);
   Tree->SetBranchAddress("Likelihood_ExtSig14", &M.L14);
   Tree->SetBranchAddress("Likelihood_ExtSig34", &M.L34);
   Tree->SetBranchAddress("Likelihood_EffMEE", &M.LB);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1", &M.L1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3", &M.L3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13", &M.L13Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig4", &M.L4Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig14", &M.L14Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig34", &M.L34Up);
   Tree->SetBranchAddress("LikelihoodUp_EffMEE", &M.LBUp);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1", &M.L1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3", &M.L3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13", &M.L13Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig4", &M.L4Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig14", &M.L14Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig34", &M.L34Down);
   Tree->SetBranchAddress("LikelihoodDown_EffMEE", &M.LBDown);
   Tree->SetBranchAddress("Likelihood_ExtSig1_Integral", &M.I1);
   Tree->SetBranchAddress("Likelihood_ExtSig3_Integral", &M.I3);
   Tree->SetBranchAddress("Likelihood_ExtSig13_Integral", &M.I13);
   Tree->SetBranchAddress("Likelihood_ExtSig4_Integral", &M.I4);
   Tree->SetBranchAddress("Likelihood_ExtSig14_Integral", &M.I14);
   Tree->SetBranchAddress("Likelihood_ExtSig34_Integral", &M.I34);
   Tree->SetBranchAddress("Likelihood_EffMEE_Integral", &M.IB);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig1_Integral", &M.I1Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig3_Integral", &M.I3Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig13_Integral", &M.I13Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig4_Integral", &M.I4Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig14_Integral", &M.I14Up);
   Tree->SetBranchAddress("LikelihoodUp_ExtSig34_Integral", &M.I34Up);
   Tree->SetBranchAddress("LikelihoodUp_EffMEE_Integral", &M.IBUp);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig1_Integral", &M.I1Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig3_Integral", &M.I3Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig13_Integral", &M.I13Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig4_Integral", &M.I4Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig14_Integral", &M.I14Down);
   Tree->SetBranchAddress("LikelihoodDown_ExtSig34_Integral", &M.I34Down);
   Tree->SetBranchAddress("LikelihoodDown_EffMEE_Integral", &M.IBDown);
}
//---------------------------------------------------------------------------
ParameterizedLikelihoods FindParameters(Likelihoods M)
{
   ParameterizedLikelihoods P;

   P.V1A = (M.L1Up * M.I1Up - M.L1Down * M.I1Down) / 2;
   P.V3A = (M.L3Up * M.I3Up - M.L3Down * M.I3Down) / 2;
   P.V13A = (M.L13Up * M.I13Up - M.L13Down * M.I13Down) / 2;
   P.V4A = (M.L4Up * M.I4Up - M.L4Down * M.I4Down) / 2;
   P.V14A = (M.L14Up * M.I14Up - M.L14Down * M.I14Down) / 2;
   // P.V34A = (M.L34Up * M.I34Up - M.L34Down * M.I34Down) / 2;
   P.VBA = (M.LBUp * M.IBUp - M.LBDown * M.IBDown) / 2;
   
   P.V1B = (M.L1Up * M.I1Up + M.L1 * M.I1 + M.L1Down * M.I1Down) / 3;
   P.V3B = (M.L3Up * M.I3Up + M.L3 * M.I3 + M.L3Down * M.I3Down) / 3;
   P.V13B = (M.L13Up * M.I13Up + M.L13 * M.I13 + M.L13Down * M.I13Down) / 3;
   P.V4B = (M.L4Up * M.I4Up + M.L4 * M.I4 + M.L4Down * M.I4Down) / 3;
   P.V14B = (M.L14Up * M.I14Up + M.L14 * M.I14 + M.L14Down * M.I14Down) / 3;
   // P.V34B = (M.L34Up * M.I34Up + M.L34 * M.I34 + M.L34Down * M.I34Down) / 3;
   P.VBB = (M.LBUp * M.IBUp + M.LB * M.IB + M.LBDown * M.IBDown) / 3;

   P.I1A = (M.I1Up - M.I1Down) / 2;
   P.I3A = (M.I3Up - M.I3Down) / 2;
   P.I13A = (M.I13Up - M.I13Down) / 2;
   P.I4A = (M.I4Up - M.I4Down) / 2;
   P.I14A = (M.I14Up - M.I14Down) / 2;
   // P.I34A = (M.I34Up - M.I34Down) / 2;
   P.IBA = (M.IBUp - M.IBDown) / 2;
   
   P.I1B = (M.I1Up + M.I1 + M.I1Down) / 3;
   P.I3B = (M.I3Up + M.I3 + M.I3Down) / 3;
   P.I13B = (M.I13Up + M.I13 + M.I13Down) / 3;
   P.I4B = (M.I4Up + M.I4 + M.I4Down) / 3;
   P.I14B = (M.I14Up + M.I14 + M.I14Down) / 3;
   // P.I34B = (M.I34Up + M.I34 + M.I34Down) / 3;
   P.IBB = (M.IBUp + M.IB + M.IBDown) / 3;

   P.V4A = P.V3A;   // quick-and-dirty fix
   P.V4B = P.V3B;
   P.I4A = P.I3A;
   P.I4B = P.I3B;

   return P;
}
//---------------------------------------------------------------------------
double CalculateLogLikelihood(ParameterizedLikelihoods P,
   double A1, double A3, double A4, double F, double NuisanceParameter)
{
   double CombinedIntegral = 0;
   CombinedIntegral = CombinedIntegral + (P.I1A * NuisanceParameter + P.I1B) * A1 * A1;
   CombinedIntegral = CombinedIntegral + (P.I3A * NuisanceParameter + P.I3B) * A3 * A3;
   CombinedIntegral = CombinedIntegral + (P.I13A * NuisanceParameter + P.I13B) * A1 * A3;
   CombinedIntegral = CombinedIntegral + (P.I4A * NuisanceParameter + P.I4B) * A4 * A4;
   CombinedIntegral = CombinedIntegral + (P.I14A * NuisanceParameter + P.I14B) * A1 * A4;
   // CombinedIntegral = CombinedIntegral + (P.I34A * NuisanceParameter + P.I34B) * A3 * A4;

   double CombinedValue = 0;
   CombinedValue = CombinedValue + (P.V1A * NuisanceParameter + P.V1B) * A1 * A1;
   CombinedValue = CombinedValue + (P.V3A * NuisanceParameter + P.V3B) * A3 * A3;
   CombinedValue = CombinedValue + (P.V13A * NuisanceParameter + P.V13B) * A1 * A3;
   CombinedValue = CombinedValue + (P.V4A * NuisanceParameter + P.V4B) * A4 * A4;
   CombinedValue = CombinedValue + (P.V14A * NuisanceParameter + P.V14B) * A1 * A4;
   // CombinedValue = CombinedValue + (P.V34A * NuisanceParameter + P.V34B) * A3 * A4;

   double SignalLikelihood = CombinedValue / CombinedIntegral;
   double BackgroundLikelihood = (P.VBA * NuisanceParameter + P.VBB) / (P.IBA * NuisanceParameter + P.IBB);

   if(SignalLikelihood < 0)
      return -9999999;
   if(BackgroundLikelihood < 0)
      return -9999999;

   static const double Sigma = 1;
   return log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F)
      - NuisanceParameter * NuisanceParameter / (2 * Sigma * Sigma);
}
//---------------------------------------------------------------------------
void SynthesizeHistogram(TH2D &H)
{
   double Minimum = H.GetMinimum();
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      for(int j = 1; j <= H.GetNbinsY(); j++)
         H.SetBinContent(i, j, H.GetBinContent(i, j) - Minimum);
   }
}
//---------------------------------------------------------------------------
void BlankoutHistogram(TH2D &H, const TH2D &LookUp, double Threshold)
{
   int XSize = LookUp.GetNbinsX();
   int YSize = LookUp.GetNbinsY();

   for(int iX = 1; iX <= XSize; iX++)
   {
      for(int iY = 1; iY < YSize; iY++)
      {
         if(LookUp.GetBinContent(iX, iY) > Threshold)
            H.SetBinContent(iX, iY, 999999);
      }
   }
}
//---------------------------------------------------------------------------
double FindBestFractionAndNuisanceParameter(const vector<ParameterizedLikelihoods> &D,
   const double A1, const double A3, const double A4, double &F, double &N)
{
   double BestF = 0;
   double BestN = 0;
   double BestValue = 1;

   double CenterF = 0.5;
   double StepSize = 0.5;

   int DataSize = (int)D.size();

   for(int iTry = 0; iTry < 5; iTry++)
   {
      for(int iS = -5; iS <= 5; iS++)
      {
         double CurrentF = CenterF + StepSize * iS / 5;
         double CurrentN = -1000;

         if(CurrentF < 0 || CurrentF > 1)
            continue;

         double TotalLikelihood = FindBestNuisanceParameter(D, A1, A3, A4, CurrentF, CurrentN);

         if(TotalLikelihood > BestValue || BestValue > 0)
         {
            BestF = CurrentF;
            BestN = CurrentN;
            BestValue = TotalLikelihood;
         }
      }

      StepSize = StepSize / 5;
      CenterF = BestF;
   }

   F = BestF;
   N = BestN;
   return BestValue;
}
//---------------------------------------------------------------------------
double FindBestNuisanceParameter(const vector<ParameterizedLikelihoods> &D,
   const double A1, const double A3, const double A4, const double F, double &N)
{
   double BestN = 0;
   double BestValue = 1;

   double CenterN = 0;
   double StepSize = 5;

   int DataSize = (int)D.size();

   for(int iTry = 0; iTry < 5; iTry++)
   {
      for(int iS = -5; iS <= 5; iS++)
      {
         double CurrentN = CenterN + StepSize * iS / 5;

         double TotalLikelihood = 0;
         for(int iD = 0; iD < DataSize; iD++)
            TotalLikelihood = TotalLikelihood + CalculateLogLikelihood(D[iD], A1, A3, A4, F, CurrentN);

         if(TotalLikelihood > BestValue || BestValue > 0)
         {
            BestN = CurrentN;
            BestValue = TotalLikelihood;
         }
      }

      StepSize = StepSize / 5;
      CenterN = BestN;
   }

   N = BestN;
   return BestValue;
}
//---------------------------------------------------------------------------






