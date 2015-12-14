#include <iostream>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"
#include "DataHelper.h"
#include "PlotHelper2.h"

struct FitResultSummary;
class FitClass;
int main();

struct FitResultSummary
{
public:
   double A2A1, A2A1Error;
   double A2Phase, A2PhaseError;
   double A3A1, A3A1Error;
   double A3Phase, A3PhaseError;
   double F, FError;
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   vector<double> V[16][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   vector<double> I[16][5];   // same as above
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(double v[16][5], double I[16][5]);
   void ClearPoints();

   FitResultSummary DoFit(bool FixA2 = false, bool FixA3 = false, double AA = 0, double Phase = 0);
};

int main()
{
   DataHelper DHFile("Normalization.dh");

   TFile File("EventFMeow.root");
   TTree *Tree = (TTree *)File.Get("MCTree");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T26", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[16][5] = {{0}};
   double Integral[16][5] = {{0}};

   string suffix[15] = {"A1RA1R", "A2RA2R", "A2IA2I", "A3RA3R", "A3IA3I",
      "A1RA2R", "A1RA2I", "A1RA3R", "A1RA3I", "A2RA2I",
      "A2RA3R", "A2RA3I", "A2IA3R", "A2IA3I", "A3RA3I"};
   vector<string> Suffix(suffix, suffix + 15);

   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);

   float Weight;
   Tree->SetBranchAddress("weight", &Weight);

   PsFileHelper PsFile("Profiles.ps");
   PsFile.AddTextPage("MEOW");

   TFile OutputFile("Histograms.root", "RECREATE");
   
   FitClass Fits;
      
   TGraph GA3I, GA2I, GA3O, GA2O, GSizeO, GSizeI;
   // GA3I.SetPoint(0, 0.9977107944030137, -0.14103275058429116);
   // GA2I.SetPoint(0, 1.084817619829565, -0.14666649379719301);
   GA3I.SetPoint(0, sqrt(200), PI / 4);
   GA2I.SetPoint(0, 6, PI / 2);
   // GA3I.SetPoint(0, 0.91863042434, PI / 4);
   // GA2I.SetPoint(0, 0.38974188147, PI / 2);
   GA3I.SetMarkerStyle(33);
   GA2I.SetMarkerStyle(33);
   GA3I.SetMarkerColor(kWhite);
   GA2I.SetMarkerColor(kWhite);
   GA3I.SetMarkerSize(2);
   GA2I.SetMarkerSize(2);
   // GA3O.SetPoint(0, 0.9977107944030137, -0.14103275058429116);
   // GA2O.SetPoint(0, 1.084817619829565, -0.14666649379719301);
   GA3O.SetPoint(0, sqrt(200), PI / 4);
   GA2O.SetPoint(0, 6, PI / 2);
   // GA3O.SetPoint(0, 0.91863042434, PI / 4);
   // GA2O.SetPoint(0, 0.38974188147, PI / 2);
   GA3O.SetMarkerStyle(33);
   GA2O.SetMarkerStyle(33);
   GA3O.SetMarkerColor(kBlack);
   GA2O.SetMarkerColor(kBlack);
   GA3O.SetMarkerSize(3);
   GA2O.SetMarkerSize(3);

   GSizeI.SetPoint(0, sqrt(200), 6);
   GSizeI.SetMarkerStyle(33);
   GSizeI.SetMarkerColor(kWhite);
   GSizeI.SetMarkerSize(2);
   GSizeO.SetPoint(0, sqrt(200), 6);
   GSizeO.SetMarkerStyle(33);
   GSizeO.SetMarkerColor(kBlack);
   GSizeO.SetMarkerSize(3);

   int PageCount = 0;
   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      double RandomNumber = DrawRandom(0, 1);
      if(RandomNumber > Weight)   // killed by efficiency
         continue;

      for(int j = 0; j < 5; j++)
      {
         Value[10][j] = 0;
         Value[15][j] = 0;
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      // if(l1id == 13 && l3id == 13)   State = "mm";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
            Integral[0][j] = DHFile[State][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 16; i++)
            {
               char BranchSuffix[2] = "A";
               BranchSuffix[0] = char('A' + (i - 1));
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[State][Branch].GetDouble();

               if(i == 10 || i == 15)
                  Integral[i][j] = 0;
            }
         }
      }

      if(State == "em" || State == "me")   // bug fix of A2 cross terms!
      {
         for(int j = 1; j < 5; j++)
         {
            Integral[6][j] = -Integral[6][j];
            Integral[7][j] = -Integral[7][j];
            Integral[11][j] = -Integral[11][j];
            Integral[12][j] = -Integral[12][j];
            Integral[13][j] = -Integral[13][j];
            Integral[14][j] = -Integral[14][j];
         }
      }

      bool Good = true;
      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            if(Value[i][j] > 0.99)
               Good = false;
      if(Good == false)
         continue;

      Fits.AddPoint(Value, Integral);

      if(Fits.SampleSize < 500)
         continue;
   
      FitResultSummary Result = Fits.DoFit();

      if(Result.FitStatus == 3)
      {
         TH2D HA3Scan(Form("HA3Scan_%d", PageCount), "A3/A1 scan at correct A2/A1 value;|A3/A1|;Phase(A3/A1)", 50, 0, 30, 50, -PI, PI);
         TH2D HA2Scan(Form("HA2Scan_%d", PageCount), "A2/A1 scan at correct A3/A1 value;|A2/A1|;Phase(A2/A1)", 50, 0, 30, 50, -PI, PI);
         TH2D HSizeScan(Form("HSizeScan_%d", PageCount), "Ax/A1 scan at correct phase value;|A3/A1|;|A2/A1|", 50, 0, 30, 50, 0, 30);
         TH2D HA3ScanMin(Form("HA3ScanMin_%d", PageCount), "A3/A1 scan profiling out others", 50, 0, 30, 50, -PI, PI);
         TH2D HA2ScanMin(Form("HA2ScanMin_%d", PageCount), "A2/A1 scan profiling out others", 50, 0, 30, 50, -PI, PI);
         TH2D HSizeScanMin(Form("HSizeScanMin_%d", PageCount), "Ax/A1 scan profiling out others;|A3/A1|;|A2/A1|", 50, 0, 30, 50, 0, 30);

         HA3Scan.SetStats(0);
         HA2Scan.SetStats(0);
         HA3ScanMin.SetStats(0);
         HA2ScanMin.SetStats(0);

         double MinLL = 1e10;

         MinLL = 1e10;
         for(int i = 1; i <= HA3Scan.GetNbinsX(); i++)
         {
            for(int j = 1; j <= HA3Scan.GetNbinsY(); j++)
            {
               // double A2A1 = 1.084817619829565;
               // double A2Phase = -0.14666649379719301;
               double A2A1 = 6;
               double A2Phase = PI / 2;

               double A3A1 = HA3Scan.GetXaxis()->GetBinCenter(i);
               // double A3A1 = A3A * sqrt((1 + A2A1 * A2A1) / (1 - A3A * A3A));
               double A3Phase = HA3Scan.GetYaxis()->GetBinCenter(j);

               double Parameters[] = {A3A1, A3Phase, A2A1, A2Phase, 0, 0, 0};

               double LL = Fits.CalculateLogLikelihoodAll(Parameters);
               if(LL < MinLL)
                  MinLL = LL;

               HA3Scan.SetBinContent(i, j, LL);
            }
         }
         for(int i = 1; i <= HA3Scan.GetNbinsX(); i++)
            for(int j = 1; j <= HA3Scan.GetNbinsY(); j++)
               HA3Scan.SetBinContent(i, j, HA3Scan.GetBinContent(i, j) - MinLL);

         MinLL = 1e10;
         for(int i = 1; i <= HA2Scan.GetNbinsX(); i++)
         {
            for(int j = 1; j <= HA2Scan.GetNbinsY(); j++)
            {
               // double A3A1 = 0.9977107944030137;
               // double A3Phase = -0.14103275058429116;
               double A3A1 = sqrt(200);
               double A3Phase = PI / 4;

               double A2A1 = HA2Scan.GetXaxis()->GetBinCenter(i);
               // double A2A1 = A2A * sqrt((1 + A3A1 * A3A1) / (1 - A2A * A2A));
               double A2Phase = HA2Scan.GetYaxis()->GetBinCenter(j);

               double Parameters[] = {A3A1, A3Phase, A2A1, A2Phase, 0, 0, 0};

               double LL = Fits.CalculateLogLikelihoodAll(Parameters);
               if(LL < MinLL)
                  MinLL = LL;

               HA2Scan.SetBinContent(i, j, LL);
            }
         }
         for(int i = 1; i <= HA2Scan.GetNbinsX(); i++)
            for(int j = 1; j <= HA2Scan.GetNbinsY(); j++)
               HA2Scan.SetBinContent(i, j, HA2Scan.GetBinContent(i, j) - MinLL);

         MinLL = 1e10;
         for(int i = 1; i <= HSizeScan.GetNbinsX(); i++)
         {
            for(int j = 1; j <= HSizeScan.GetNbinsY(); j++)
            {
               double A3A1 = HSizeScan.GetXaxis()->GetBinCenter(i);
               double A3Phase = PI / 4;

               double A2A1 = HSizeScan.GetYaxis()->GetBinCenter(j);
               double A2Phase = PI / 2;

               double Parameters[] = {A3A1, A3Phase, A2A1, A2Phase, 0, 0, 0};

               double LL = Fits.CalculateLogLikelihoodAll(Parameters);
               if(LL < MinLL)
                  MinLL = LL;

               HSizeScan.SetBinContent(i, j, LL);
            }
         }
         for(int i = 1; i <= HSizeScan.GetNbinsX(); i++)
            for(int j = 1; j <= HSizeScan.GetNbinsY(); j++)
               HSizeScan.SetBinContent(i, j, HSizeScan.GetBinContent(i, j) - MinLL);

         MinLL = 1e10;
         for(int i = 1; i <= HA3ScanMin.GetNbinsX(); i++)
         {
            for(int j = 1; j <= HA3ScanMin.GetNbinsY(); j++)
            {
               double A3A1 = HA3ScanMin.GetXaxis()->GetBinCenter(i);
               // double A3A1 = A3A * sqrt((1 + A2A1 * A2A1) / (1 - A3A * A3A))
               double A3Phase = HA3ScanMin.GetYaxis()->GetBinCenter(j);

               FitResultSummary TempResult = Fits.DoFit(false, true, A3A1, A3Phase);

               double Parameters[] = {A3A1, A3Phase, TempResult.A2A1, TempResult.A2Phase,
                  TempResult.F, TempResult.N1, TempResult.N2};

               double LL = Fits.CalculateLogLikelihoodAll(Parameters);
               if(LL < MinLL)
                  MinLL = LL;

               HA3ScanMin.SetBinContent(i, j, LL);
            }
         }
         for(int i = 1; i <= HA3ScanMin.GetNbinsX(); i++)
            for(int j = 1; j <= HA3ScanMin.GetNbinsY(); j++)
               HA3ScanMin.SetBinContent(i, j, HA3ScanMin.GetBinContent(i, j) - MinLL);

         MinLL = 1e10;
         for(int i = 1; i <= HA2ScanMin.GetNbinsX(); i++)
         {
            for(int j = 1; j <= HA2ScanMin.GetNbinsY(); j++)
            {
               double A2A1 = HA2ScanMin.GetXaxis()->GetBinCenter(i);
               double A2Phase = HA2ScanMin.GetYaxis()->GetBinCenter(j);
               
               FitResultSummary TempResult = Fits.DoFit(true, false, A2A1, A2Phase);

               double Parameters[] = {TempResult.A3A1, TempResult.A3Phase, A2A1, A2Phase,
                  TempResult.F, TempResult.N1, TempResult.N2};

               double LL = Fits.CalculateLogLikelihoodAll(Parameters);
               if(LL < MinLL)
                  MinLL = LL;

               HA2ScanMin.SetBinContent(i, j, LL);
            }
         }
         for(int i = 1; i <= HA2ScanMin.GetNbinsX(); i++)
            for(int j = 1; j <= HA2ScanMin.GetNbinsY(); j++)
               HA2ScanMin.SetBinContent(i, j, HA2ScanMin.GetBinContent(i, j) - MinLL);

         HA3Scan.SetMaximum(HA3Scan.GetMinimum() + 5);
         HA2Scan.SetMaximum(HA2Scan.GetMinimum() + 5);
         HSizeScan.SetMaximum(HA2Scan.GetMinimum() + 5);
         HA3ScanMin.SetMaximum(HA3ScanMin.GetMinimum() + 5);
         HA2ScanMin.SetMaximum(HA2ScanMin.GetMinimum() + 5);

         HA3Scan.Write();
         HA2Scan.Write();
         HSizeScan.Write();
         HA3ScanMin.Write();
         HA2ScanMin.Write();

         TCanvas C;
         C.Divide(2);

         C.cd(1);
         HA3Scan.Draw("colz");
         GA3O.Draw("p");
         GA3I.Draw("p");

         C.cd(2);
         HA2Scan.Draw("colz");
         GA2O.Draw("p");
         GA2I.Draw("p");

         PsFile.AddCanvas(C);

         C.cd(1);
         HA3ScanMin.Draw("colz");
         GA3O.Draw("p");
         GA3I.Draw("p");

         C.cd(2);
         HA2ScanMin.Draw("colz");
         GA2O.Draw("p");
         GA2I.Draw("p");

         PsFile.AddCanvas(C);

         TCanvas C2;
         HSizeScan.Draw("colz");
         GSizeO.Draw("p");
         GSizeI.Draw("p");

         PsFile.AddCanvas(C2);

         PageCount = PageCount + 1;
         if(PageCount >= 1)
            break;
      }
      
      Fits.ClearPoints();
   }

   OutputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1R = 1;
   double A3R = Parameters[0] * cos(Parameters[1]);
   double A3I = Parameters[0] * sin(Parameters[1]);
   double A2R = Parameters[2] * cos(Parameters[3]);
   double A2I = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N1 = Parameters[5];
   double N2 = Parameters[6];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1R * A1R * V[1][i][iS] + A2R * A2R * V[2][i][iS] + A2I * A2I * V[3][i][iS]
            + A3R * A3R * V[4][i][iS] + A3I * A3I * V[5][i][iS]
            + A1R * A2R * V[6][i][iS] + A1R * A2I * V[7][i][iS] + A1R * A3R * V[8][i][iS]
            + A1R * A3I * V[9][i][iS] + A2R * A2I * V[10][i][iS]
            + A2R * A3R * V[11][i][iS] + A2R * A3I * V[12][i][iS] + A2I * A3R * V[13][i][iS]
            + A2I * A3I * V[14][i][iS] + A3R * A3I * V[15][i][iS];
         Integral[i] = A1R * A1R * I[1][i][iS] + A2R * A2R * I[2][i][iS] + A2I * A2I * I[3][i][iS]
            + A3R * A3R * I[4][i][iS] + A3I * A3I * I[5][i][iS]
            + A1R * A2R * I[6][i][iS] + A1R * A2I * I[7][i][iS] + A1R * A3R * I[8][i][iS]
            + A1R * A3I * I[9][i][iS] + A2R * A2I * I[10][i][iS]
            + A2R * A3R * I[11][i][iS] + A2R * A3I * I[12][i][iS] + A2I * A3R * I[13][i][iS]
            + A2I * A3I * I[14][i][iS] + A3R * A3I * I[15][i][iS];
         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 5; i++)
         if(Likelihood[i] <= 0)
            Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }
      double LSa = Likelihood[0];
      double LSb1 = (N1 > 0) ? (Likelihood[1] - Likelihood[0]) : (Likelihood[0] - Likelihood[2]);
      double LSb2 = (N2 > 0) ? (Likelihood[3] - Likelihood[0]) : (Likelihood[0] - Likelihood[4]);
      double LBa = LikelihoodB[0];
      double LBb1 = (N1 > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N2 > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);

      double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N1 * N1 / 2 - N2 * N2 / 2;
   }

   return -LogTotal;
}

void FitClass::AddPoint(double v[16][5], double i[16][5])
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].push_back(v[i1][i2]);
         I[i1][i2].push_back(i[i1][i2]);
      }
   }

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].clear();
         I[i1][i2].clear();
      }
   }

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(bool FixA2, bool FixA3, double AA, double Phase)
{
   ROOT::Math::Minimizer *PreWorker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   PreWorker->SetPrintLevel(1);
   PreWorker->SetMaxFunctionCalls(1e9);
   PreWorker->SetMaxIterations(1e8);
   PreWorker->SetTolerance(1e-3);
   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e8);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 7);
   PreWorker->SetFunction(Function);
   Worker->SetFunction(Function);

   double A3A1InitialValue = 14.14;
   double A3PhaseInitialValue = PI / 4;
   double A2A1InitialValue = 6;
   double A2PhaseInitialValue = PI / 2;
   double FInitialValue = 1e-5;
   double N1InitialValue = 0.0;
   double N2InitialValue = 0.0;

   if(FixA2 == true || FixA3 == true)
   {
      PreWorker->SetLimitedVariable(0, "A3A1", A3A1InitialValue, 0.5, -100, 100);
      PreWorker->SetLimitedVariable(1, "A3Phase", A3PhaseInitialValue, 0.01, -PI * 10, PI * 10);
      PreWorker->SetLimitedVariable(2, "A2A1", A2A1InitialValue, 0.5, -100, 100);
      PreWorker->SetLimitedVariable(3, "A2Phase", A2PhaseInitialValue, 0.01, -PI * 10, PI * 10);
      PreWorker->SetLimitedVariable(4, "F", FInitialValue, 0, 0, 1);
      PreWorker->SetLimitedVariable(5, "N1", N1InitialValue, 0, -1, 1);
      PreWorker->SetLimitedVariable(6, "N2", N2InitialValue, 0, -1, 1);

      PreWorker->Minimize();

      const double *PreParameters = PreWorker->X();

      A3A1InitialValue = PreParameters[0];
      A3PhaseInitialValue = PreParameters[1];
      A2A1InitialValue = PreParameters[2];
      A2PhaseInitialValue = PreParameters[3];
      FInitialValue = PreParameters[4];
      N1InitialValue = PreParameters[5];
      N2InitialValue = PreParameters[6];
   }

   if(FixA3 == false)
   {
      Worker->SetLimitedVariable(0, "A3A1", A3A1InitialValue, 0.5, -100, 100);
      Worker->SetLimitedVariable(1, "A3Phase", A3PhaseInitialValue, 0.01, -PI * 10, PI * 10);
   }
   else
   {
      Worker->SetLimitedVariable(0, "A3A1", AA, 0, AA - 0.0001, AA + 0.0001);
      Worker->SetLimitedVariable(1, "A3Phase", Phase, 0, Phase - 0.0001, Phase + 0.0001);
   }
   if(FixA2 == false)
   {
      Worker->SetLimitedVariable(2, "A2A1", A2A1InitialValue, 0.5, -100, 100);
      Worker->SetLimitedVariable(3, "A2Phase", A2PhaseInitialValue, 0.01, -PI * 10, PI * 10);
   }
   else
   {
      Worker->SetLimitedVariable(2, "A2A1", AA, 0, AA - 0.0001, AA + 0.0001);
      Worker->SetLimitedVariable(3, "A3Phase", Phase, 0, Phase - 0.0001, Phase + 0.0001);
   }
   Worker->SetLimitedVariable(4, "F", FInitialValue, 0, 0, 1);
   Worker->SetLimitedVariable(5, "N1", N1InitialValue, 0, -1, 1);
   Worker->SetLimitedVariable(6, "N2", N2InitialValue, 0, -1, 1);

   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.A2A1 = Parameters[2];
   Result.A2A1Error = Errors[2];
   Result.A2Phase = Parameters[3];
   Result.A2PhaseError = Errors[3];
   Result.F = Parameters[4];
   Result.FError = Errors[4];
   Result.N1 = Parameters[5];
   Result.N1Error = Errors[5];
   Result.N2 = Parameters[6];
   Result.N2Error = Errors[6];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   if(Result.A2A1 < 0)
   {
      Result.A2A1 = -Result.A2A1;
      Result.A2Phase = Result.A2Phase + PI;
   }
   if(Result.A3A1 < 0)
   {
      Result.A3A1 = -Result.A3A1;
      Result.A3Phase = Result.A3Phase + PI;
   }

   while(Result.A2Phase < -PI)   Result.A2Phase = Result.A2Phase + 2 * PI;
   while(Result.A2Phase > +PI)   Result.A2Phase = Result.A2Phase - 2 * PI;
   while(Result.A3Phase < -PI)   Result.A3Phase = Result.A3Phase + 2 * PI;
   while(Result.A3Phase > +PI)   Result.A3Phase = Result.A3Phase - 2 * PI;

   delete PreWorker;
   delete Worker;

   return Result;
}






