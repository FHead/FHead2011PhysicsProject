#include <iostream>
#include <vector>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TF2.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "SetStyle.h"
#include "CustomAssert.h"
#include "CommandLine.h"
#include "PlotHelper3.h"

class Fitter;
int main(int argc, char *argv[]);
void PlotGraph(PdfFileHelper &PdfFile, string Label, TGraph2D *G, Fitter *F);
void PlotClosure(PdfFileHelper &PdfFile, string Label, TTree *T, Fitter *F);
void PlotOneClosure(PdfFileHelper &PdfFile, TTree *T, Fitter *F,
   double MinPT, double MaxPT, double MinRho, double MaxRho, bool XIsPT);

class Fitter
{
private:
   vector<double> X, Y, Z;
   string Function;
   vector<double> P;
public:
   Fitter() {}
   Fitter(TGraph2D *G) {Initialize(G);}
   ~Fitter() {}
   void Initialize(TGraph2D *G);
   double GetNLL(const double *Parameters);
   void SetFunction(string function) {Function = function;}
   double Evaluate(double x, double y);
   void SetParameters(int N, const double *Parameters);
};
   
void Fitter::Initialize(TGraph2D *G)
{
   Assert(G != NULL, "Attempting to initialize things with a null graph");

   int N = G->GetN();
   X.resize(N);
   Y.resize(N);
   Z.resize(N);

   for(int i = 0; i < N; i++)
   {
      X[i] = G->GetX()[i];
      Y[i] = G->GetY()[i];
      Z[i] = G->GetZ()[i];
   }
}

double Fitter::GetNLL(const double *Parameters)
{
   double NLL = 0;

   if(Function == "MikkoSuggestion")
   {
      double RhoUE0 = 2;
      double RhoUE1 = 0;
      double AverageRho = 0;
      double PTNorm = 30;
      
      int N = X.size();
      for(int i = 0; i < N; i++)
      {
         double Value = Parameters[0]
            * (X[i] - (RhoUE0 + RhoUE1 * X[i]))
            * (1 + Parameters[1] * (X[i] - AverageRho))
            * (1 + Parameters[2] * log(Y[i] / PTNorm))
            + (Parameters[3] + Parameters[4] * log(Y[i]));
         Value = Value - Z[i];

         NLL = NLL + Value * Value;
      }
   }
   if(Function == "Andrew2017")
   {
      int N = X.size();
      for(int i = 0; i < N; i++)
      {
         double x = X[i] - 20;
         double y = log(Y[i] / 30);

         double Value = Parameters[0]
            + Parameters[1] * x
            + Parameters[2] * y
            + Parameters[3] * y * y
            + Parameters[4] * x * y
            + Parameters[5] * x * y * y - Z[i];

         NLL = NLL + Value * Value;
      }
   }

   return NLL;
}

double Fitter::Evaluate(double x, double y)
{
   double Value = 0;

   if(Function == "MikkoSuggestion")
   {
      double RhoUE0 = 2;
      double RhoUE1 = 0;
      double AverageRho = 0;
      double PTNorm = 30;

      Value = P[0]
         * (x - (RhoUE0 + RhoUE1 * x))
         * (1 + P[1] * (x - AverageRho))
         * (1 + P[2] * log(y / PTNorm))
         + (P[3] + P[4] * log(y));
   }
   if(Function == "Andrew2017")
   {
      x = x - 20;
      y = log(y / 30);

      Value = P[0]
         + P[1] * x
         + P[2] * y
         + P[3] * y * y
         + P[4] * x * y
         + P[5] * x * y * y;
   }

   return Value;
}
   
void Fitter::SetParameters(int N, const double *Parameters)
{
   P.resize(N);
   for(int i = 0; i < N; i++)
      P[i] = Parameters[i];
}

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // Gather inputs
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string InputTreeName = CL.Get("tree", "FitData");
   string OutputFileName = CL.Get("output", "Result.pdf");
   string Function = CL.Get("function", "MikkoSuggestion");

   double Percentage = CL.GetDouble("percentage", 1.00);

   // Getting input and setup tree
   TFile File(InputFileName.c_str());
   TTree *Tree = (TTree *)File.Get(InputTreeName.c_str());
   Assert(Tree != NULL, "Problem getting tree");

   double OOA, PT, Rho;
   Tree->SetBranchAddress("OOA", &OOA);
   Tree->SetBranchAddress("PT", &PT);
   Tree->SetBranchAddress("Rho", &Rho);
   
   // Fill the big graph to be used in the fit
   TGraph2D G;
   G.SetNameTitle("InputData", "");
   G.GetXaxis()->SetTitle("Rho");
   G.GetYaxis()->SetTitle("P_{T}^{PU}");
   G.GetZaxis()->SetTitle("Offset/Area");
   
   int EntryCount = Tree->GetEntries() * Percentage;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      G.SetPoint(G.GetN(), Rho, PT, OOA);
   }

   // Setup function
   Fitter Fit(&G);
   Fit.SetFunction(Function);

   vector<double> InitialParameters;
   if(Function == "MikkoSuggestion")
      InitialParameters = {0.2, 0.0, 0.0, 0.0, 0.0};
   else if(Function == "Andrew2017")
      InitialParameters = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0};

   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   // Worker->SetTolerance(1e-10);
   Worker->SetStrategy(1);   // 0 = speed, 2 = robustness, 1 is in the middle

   ROOT::Math::Functor BoundFunction(&Fit, &Fitter::GetNLL, InitialParameters.size());
   Worker->SetFunction(BoundFunction);

   for(int i = 0; i < (int)InitialParameters.size(); i++)
      Worker->SetLimitedVariable(i, Form("P%d", i), InitialParameters[i], 0.1, -1000, 1000);

   cout << G.GetN() << endl;

   // Do the fit
   Worker->Minimize();

   Fit.SetParameters(InitialParameters.size(), Worker->X());

   // Some visualization
   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Fits");

   PlotGraph(PdfFile, "Pre-fit", &G, NULL);
   PlotGraph(PdfFile, "Post-fit", &G, &Fit);
   PlotClosure(PdfFile, "Closure", Tree, &Fit);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   // Cleanup
   File.Close();

   return 0;
}

void PlotGraph(PdfFileHelper &PdfFile, string Label, TGraph2D *G, Fitter *F)
{
   if(G == NULL)
      return;

   if(F != NULL)
   {
      TGraph2D G2;
      for(int i = 0; i < G->GetN(); i++)
      {
         double X = G->GetX()[i];
         double Y = G->GetY()[i];
         double Z = G->GetZ()[i] - F->Evaluate(X, Y);
         G2.SetPoint(i, X, Y, Z);
      }

      G2.GetXaxis()->SetTitle(G->GetXaxis()->GetTitle());
      G2.GetYaxis()->SetTitle(G->GetYaxis()->GetTitle());
      G2.GetZaxis()->SetTitle(G->GetZaxis()->GetTitle());
      
      PlotGraph(PdfFile, Label, &G2, NULL);
      return;
   }

   PdfFile.AddTextPage(Label);

   TCanvas Canvas;
   Canvas.SetLogy();

   G->Draw("pcolz");
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz");
   Canvas.SetTheta(0.1);
   Canvas.SetPhi(0.1);
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz");
   Canvas.SetTheta(0.1);
   Canvas.SetPhi(-90.1);
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz");
   Canvas.SetTheta(90.1);
   Canvas.SetPhi(0.1);
   PdfFile.AddCanvas(Canvas);

   int PTBin = 24;
   double PTBins[] = {6,8,10,
      14,18,23,30,36,45,55,65,75,85,100,
      140,180,230,300,360,450,550,650,750,850,1000};

   int PUBin = 60;
   double PUBins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};

   TProfile ProfilePT("ProfilePT", ";PT", PTBin, PTBins);
   TProfile ProfilePU("ProfilePU", ";PU", PUBin, PUBins);
   TProfile2D ProfilePTPU("ProfilePTPU", ";PT;PU", PTBin, PTBins, PUBin, PUBins);

   ProfilePT.SetStats(0);
   ProfilePU.SetStats(0);
   ProfilePTPU.SetStats(0);

   for(int i = 0; i < G->GetN(); i++)
   {
      double X = G->GetX()[i];
      double Y = G->GetY()[i];
      double Z = G->GetZ()[i];

      ProfilePT.Fill(Y, Z);
      ProfilePU.Fill(X, Z);
      ProfilePTPU.Fill(Y, X, Z);
   }

   ProfilePTPU.SetMinimum(-10);
   ProfilePTPU.SetMaximum(30);

   PdfFile.AddPlot(ProfilePT, "", false, false, false, true);
   PdfFile.AddPlot(ProfilePU);
   PdfFile.AddPlot(ProfilePTPU, "colz", false, false, false, true);
}

void PlotClosure(PdfFileHelper &PdfFile, string Label, TTree *T, Fitter *F)
{
   if(T == NULL || F == NULL)
      return;

   PdfFile.AddTextPage(Label);

   int PTCategory = 9;
   double PTCategories[] = {5, 10, 18, 30, 55, 100, 180, 300, 550, 1000};
   int RhoCategory = 8;
   double RhoCategories[] = {0, 10, 15, 20, 25, 30, 35, 40, 50};

   for(int i = 0; i < PTCategory; i++)
      PlotOneClosure(PdfFile, T, F, PTCategories[i], PTCategories[i+1], 0, 60, false);
   for(int i = 0; i < RhoCategory; i++)
      PlotOneClosure(PdfFile, T, F, 6, 1000, RhoCategories[i], RhoCategories[i+1], true);
}

void PlotOneClosure(PdfFileHelper &PdfFile, TTree *T, Fitter *F,
   double MinPT, double MaxPT, double MinRho, double MaxRho, bool XIsPT)
{
   double RefPT, OOA, Rho, PUPT;
   T->SetBranchAddress("RefPT", &RefPT);
   T->SetBranchAddress("OOA", &OOA);
   T->SetBranchAddress("Rho", &Rho);
   T->SetBranchAddress("PT", &PUPT);

   const int NBINS = 20;
   double Bins[NBINS+1];
   if(XIsPT == false)
      for(int i = 0; i <= NBINS; i++)
         Bins[i] = double(60 - 0) / NBINS * i + 0;
   else
      for(int i = 0; i <= NBINS; i++)
         Bins[i] = exp((log(1000) - log(6)) / NBINS * i + log(6));

   TProfile P1("P1", "", NBINS, Bins);
   TProfile P2("P2", "", NBINS, Bins);

   P1.SetStats(0);
   P2.SetStats(0);

   if(XIsPT == true)
      P1.SetTitle(Form("Rho = %.1f-%.1f", MinRho, MaxRho));
   else
      P1.SetTitle(Form("PT = %.1f-%.1f", MinPT, MaxPT));

   P1.SetMarkerColor(kRed);
   P1.SetLineColor(kRed);

   int EntryCount = T->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      T->GetEntry(i);

      if(RefPT < MinPT || RefPT > MaxPT)   continue;
      if(Rho < MinRho || Rho > MaxRho)     continue;

      if(XIsPT == true)
      {
         P1.Fill(RefPT, OOA);
         P2.Fill(RefPT, OOA - F->Evaluate(Rho, PUPT));
      }
      else
      {
         P1.Fill(Rho, OOA);
         P2.Fill(Rho, OOA - F->Evaluate(Rho, PUPT));
      }
   }

   P1.SetMinimum(-20);
   P1.SetMaximum(20);

   TCanvas Canvas;

   P1.Draw();
   P2.Draw("same");

   if(XIsPT == true)
      Canvas.SetLogx();

   PdfFile.AddCanvas(Canvas);
}



