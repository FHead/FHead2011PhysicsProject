#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TGraph2DErrors.h"
#include "TGraphErrors.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper3.h"
#include "CustomAssert.h"

int main(int argc, char *argv[]);
void PerformFit(PdfFileHelper &PdfFile, TGraph2DErrors *G, string Function);
void StandardPlotsGraph2D(PdfFileHelper &PdfFile, TGraph2DErrors *G, string Label);
void SummaryProfilePlots(PdfFileHelper &PdfFile, TGraph2DErrors *G, bool RestrictColor = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string GraphName = CL.Get("graph");
   string OutputFileName = CL.Get("output", "fit.pdf");
   string Function = CL.Get("function", "Standard");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Fits to L1Offset");

   vector<string> Explanations = {"File: " + InputFileName, "Graph: " + GraphName, "Function: " + Function};
   PdfFile.AddTextPage(Explanations);

   TFile File(InputFileName.c_str());

   TGraph2DErrors *G = (TGraph2DErrors *)File.Get(GraphName.c_str());
   Assert(G != NULL, "Input graph not found!");

   PerformFit(PdfFile, G, Function);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PerformFit(PdfFileHelper &PdfFile, TGraph2DErrors *G, string Function)
{
   Assert(G != NULL, "[PerformFit] Graph is NULL");

   string FunctionString = "[0]";
   vector<double> InitialParameters = {1};

   // x is rho, y is jet PT
   if(Function == "MikkoSuggestionExtraFull")
   {
      double AverageRho = 20;
      double PTNorm = 30;
      FunctionString = Form("[0]*(x-([5]+[6]*x))*(1+[1]*(x-%.1f))*(1+[2]*log(y/%.1f))+([3]+[4]*log(y))", AverageRho, PTNorm);
      InitialParameters = {0.2, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0};
   }
   else if(Function == "MikkoSuggestionFull")
   {
      double RhoUE0 = 2;
      double RhoUE1 = 0;
      double AverageRho = 0;
      double PTNorm = 30;
      FunctionString = Form("[0]*(x-(%.1f+%.1f*x))*(1+[1]*(x-%.1f))*(1+[2]*log(y/%.1f))+([3]+[4]*log(y))", RhoUE0, RhoUE1, AverageRho, PTNorm);
      InitialParameters = {0.2, 0.0, 0.0, 0.0, 0.0};
   }
   else if(Function == "MikkoSuggestion")
   {
      double RhoUE0 = 2;
      double RhoUE1 = 0;
      double AverageRho = 0;
      double PTNorm = 30;
      FunctionString = Form("[0]*(x-(%.1f+%.1f*x))*(1+[1]*(x-%.1f))*(1+[2]*log(y/%.1f))", RhoUE0, RhoUE1, AverageRho, PTNorm);
      InitialParameters = {0.2, 0.0, 0.0};
   }
   else if(Function == "Andrew2017")
   {
      FunctionString = "[0]+[1]*(x-20)+[2]*log(y/30)+[3]*log(y/30)*log(y/30)+[4]*(x-20)*log(y/30)+[5]*(x-20)*log(y/30)*log(y/30)";
      InitialParameters = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   }
   else if(Function == "Andrew2017Preset")
   {
      FunctionString = "[0]+[1]*(x-20.0)+[2]*log(y/30.0)+[3]*pow(log(y/30.0),2)+[4]*(x-20.0)*log(y/30.0)+[5]*(x-20.0)*pow(log(y/30.0),2)";

      // Bin 41, AK4PF
      // InitialParameters = {18.36330385, 1.049264345, -1.044256827, -0.7654794029, -0.01256976899, -0.003552073571};

      // Bin 40, AK4PFchs
      InitialParameters = {5.96516658, 0.4147244453, -1.703610708, -0.4711823258, -0.0509480646, 0.01100796545};
   }
   else
      cerr << "[PerformFit] Warning!  Function not found!  Fit to a constant!" << endl;

   StandardPlotsGraph2D(PdfFile, G, "Pre-fit");
   SummaryProfilePlots(PdfFile, G);

   TF2 Fit("Fit", FunctionString.c_str(), 0, 50, 1, 3000);
   for(int i = 0; i < (int)InitialParameters.size(); i++)
      Fit.SetParameter(i, InitialParameters[i]);

   if(Function != "Andrew2017Preset")
   {
      bool Good = false;
      int FitCount = 0;
      do
      {
         G->Fit(&Fit, "0QMER");
         FitCount = FitCount + 1;

         double Chi2 = Fit.GetChisquare() / Fit.GetNDF();

         if(Chi2 < 10)
            Good = true;
      } while(Good == false && FitCount < 100);
   }

   Fit.SetTitle("Fit function");
   PdfFile.AddPlot(Fit, "colz");

   vector<string> FitParameters(20);
   FitParameters[0] = "Fit function = " + FunctionString;
   FitParameters[1] = "";
   for(int i = 0; i < (int)InitialParameters.size(); i++)
      FitParameters[2+i] = Form("P%d = %f #pm %f", i, Fit.GetParameter(i), Fit.GetParError(i));
   FitParameters[2+InitialParameters.size()+1] = Form("PT 30 Rho 20 = %f", Fit.Eval(20, 30));
   PdfFile.AddTextPage(FitParameters);

   TGraph2DErrors GResidual, GPull;

   GResidual.GetXaxis()->SetTitle("Rho");
   GResidual.GetYaxis()->SetTitle("P_{T}^{PU}");
   GResidual.GetZaxis()->SetTitle("Residual");
   GPull.GetXaxis()->SetTitle("Rho");
   GPull.GetYaxis()->SetTitle("P_{T}^{PU}");
   GPull.GetZaxis()->SetTitle("Pull");

   for(int i = 0; i < G->GetN(); i++)
   {
      double X = G->GetX()[i];
      double Y = G->GetY()[i];
      double Z = G->GetZ()[i];
      double EX = G->GetEX()[i];
      double EY = G->GetEY()[i];
      double EZ = G->GetEZ()[i];

      double FunctionValue = Fit.Eval(X, Y);
      double Pull = (Z - FunctionValue) / EZ;
      if(Pull < -10)   Pull = -10;
      if(Pull > 10)    Pull = 10;

      GResidual.SetPoint(i, X, Y, Z - FunctionValue);
      GResidual.SetPointError(i, EX, EY, EZ);
      
      GPull.SetPoint(i, X, Y, Pull);
      GPull.SetPointError(i, EX, EY, 0);
   }

   StandardPlotsGraph2D(PdfFile, &GResidual, "Fit residual");
   SummaryProfilePlots(PdfFile, &GResidual, true);
   StandardPlotsGraph2D(PdfFile, &GPull, "Fit pull");
}

void StandardPlotsGraph2D(PdfFileHelper &PdfFile, TGraph2DErrors *G, string Label)
{
   Assert(G != NULL, "[StandardPlotsGraph2D] Graph is NULL");

   PdfFile.AddTextPage(Label);

   TCanvas Canvas;
   Canvas.SetLogy();

   G->Draw("pcolz error");
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz error");
   Canvas.SetTheta(0.1);
   Canvas.SetPhi(0.1);
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz error");
   Canvas.SetTheta(0.1);
   Canvas.SetPhi(-90.1);
   PdfFile.AddCanvas(Canvas);

   G->Draw("pcolz error");
   Canvas.SetTheta(90.1);
   Canvas.SetPhi(0.1);
   PdfFile.AddCanvas(Canvas);
}

void SummaryProfilePlots(PdfFileHelper &PdfFile, TGraph2DErrors *G, bool RestrictColor)
{
   Assert(G != NULL, "[SummaryProfilePlots] Graph is NULL");

   // int PTBin = 47;
   // double PTBins[] = {5,6,7,8,9,10,
   //    12,14,16,18,20,23,26,30,33,36,40,45,50,55,60,65,70,75,80,90,100,
   //    120,140,160,180,200,230,260,300,330,360,400,450,500,550,600,650,700,750,800,900,1000};
   int PTBin = 24;
   double PTBins[] = {6,8,10,
      14,18,23,30,36,45,55,65,75,85,100,
      140,180,230,300,360,450,550,650,750,850,1000};
   
   int PUBin = 60;
   double PUBins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};
   // int PUBin = 30;
   // double PUBins[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60};

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
      double EX = G->GetEX()[i];
      double EY = G->GetEY()[i];
      double EZ = G->GetEZ()[i];

      if(EZ < 1e-5)
         continue;

      ProfilePT.Fill(Y, Z, 1 / EZ / EZ);
      ProfilePU.Fill(X, Z, 1 / EZ / EZ);
      ProfilePTPU.Fill(Y, X, Z, 1 / EZ / EZ);
   }

   if(RestrictColor == true)
   {
      double Limit = 7;
      ProfilePT.SetMinimum(-Limit);
      ProfilePT.SetMaximum(Limit);
      ProfilePU.SetMinimum(-Limit);
      ProfilePU.SetMaximum(Limit);
      ProfilePTPU.SetMinimum(-Limit);
      ProfilePTPU.SetMaximum(Limit);
   }

   PdfFile.AddPlot(ProfilePT, "", false, false, false, true);
   PdfFile.AddPlot(ProfilePU);
   PdfFile.AddPlot(ProfilePTPU, "colz", false, false, false, true);
}


