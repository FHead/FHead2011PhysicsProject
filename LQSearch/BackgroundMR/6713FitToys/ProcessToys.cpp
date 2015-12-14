#include <vector>
#include <string>
using namespace std;

#include "TROOT.h"
#include "TStyle.h"
#include "TH1D.h"

#include "PlotHelper2.h"
#include "DataHelper.h"

int main()
{
   gROOT->SetStyle("Plain");

   DataHelper DHFile("ToyResults.dh");

   vector<string> States = DHFile.GetListOfKeys();

   PsFileHelper PsFile("FinalResults.ps");
   PsFile.AddTextPage("Final results of the toys");

   TH1D HParameterA("HParameterA", "Parameter A distribution", 100, 0.005, 0.008);
   TH1D HParameterB("HParameterB", "Parameter B distribution", 100, 0.03, 0.06);
   TH1D HParameterAError("HParameterAError", "Error on parameter A distribution", 100, 0.00027, 0.00031);
   TH1D HParameterBError("HParameterBError", "Error on parameter B distribution", 100, 0.002, 0.0024);
   TH1D HParameterAPullToMean("HParameterAPullToMean", "Pull to mean on parameter A distribution", 100, -8, 8);
   TH1D HParameterBPullToMean("HParameterBPullToMean", "Pull to mean on parameter B distribution", 100, -8, 8);

   double MeanA = 0.006662;
   double MeanB = 0.04857;

   for(int i = 0; i < (int)States.size(); i++)
   {
      double A = DHFile[States[i]]["SimultaneousA"].GetDouble();
      double AError = DHFile[States[i]]["SimultaneousAError"].GetDouble();
      double B = DHFile[States[i]]["SimultaneousB"].GetDouble();
      double BError = DHFile[States[i]]["SimultaneousBError"].GetDouble();

      HParameterA.Fill(A);
      HParameterB.Fill(B);
      HParameterAError.Fill(AError);
      HParameterBError.Fill(BError);
      HParameterAPullToMean.Fill((A - MeanA) / AError);
      HParameterBPullToMean.Fill((B - MeanB) / BError);
   }

   PsFile.AddPlot(HParameterA, "", true);
   PsFile.AddPlot(HParameterAError, "", true);
   PsFile.AddPlot(HParameterB, "", true);
   PsFile.AddPlot(HParameterBError, "", true);
   PsFile.AddPlot(HParameterAPullToMean, "", true);
   PsFile.AddPlot(HParameterBPullToMean, "", true);

   HParameterA.Fit("gaus");
   HParameterAError.Fit("gaus");
   HParameterAPullToMean.Fit("gaus");
   HParameterB.Fit("gaus");
   HParameterBError.Fit("gaus");
   HParameterBPullToMean.Fit("gaus");

   // gStyle->SetOptFit(111);

   TCanvas ResultCanvas;
   ResultCanvas.Divide(3, 2);

   ResultCanvas.cd(1)->SetLogy();
   HParameterA.Draw();
   ResultCanvas.cd(2)->SetLogy();
   HParameterAError.Draw();
   ResultCanvas.cd(3)->SetLogy();
   HParameterAPullToMean.Draw();
   
   ResultCanvas.cd(4)->SetLogy();
   HParameterB.Draw();
   ResultCanvas.cd(5)->SetLogy();
   HParameterBError.Draw();
   ResultCanvas.cd(6)->SetLogy();
   HParameterBPullToMean.Draw();
   
   PsFile.AddCanvas(ResultCanvas);
   ResultCanvas.SaveAs("ResultOfToys.png");
   ResultCanvas.SaveAs("ResultOfToys.C");
   ResultCanvas.SaveAs("ResultOfToys.eps");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}



