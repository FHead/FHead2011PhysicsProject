#include <vector>
#include <string>
using namespace std;

#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper.h"
#include "DataHelper.h"

void MakeSummaryPlots(string Parameter = "AlphaL", string OutputBase = "AlphaLSummary")
{
   DataHelper DHFile("Database.dh");

   vector<string> States;
   States.push_back(Parameter + "900");
   States.push_back(Parameter + "950");
   States.push_back(Parameter + "975");
   States.push_back(Parameter + "990");
   States.push_back("Normal");
   States.push_back(Parameter + "1010");
   States.push_back(Parameter + "1025");
   States.push_back(Parameter + "1050");
   States.push_back(Parameter + "1100");

   vector<double> Percentages;
   Percentages.push_back(-0.1);
   Percentages.push_back(-0.05);
   Percentages.push_back(-0.025);
   Percentages.push_back(-0.01);
   Percentages.push_back(0);
   Percentages.push_back(0.01);
   Percentages.push_back(0.025);
   Percentages.push_back(0.05);
   Percentages.push_back(0.1);

   TGraphErrors Mean;
   Mean.SetNameTitle("Mean", Form("Mean of pull distribution varying %s", Parameter.c_str()));

   TGraphErrors Sigma;
   Sigma.SetNameTitle("Sigma", Form("Sigma of pull distribution varying %s", Parameter.c_str()));

   TGraphErrors RelativeYield;
   RelativeYield.SetNameTitle("RelativeYield", Form("Relative yield bias varying %s", Parameter.c_str()));

   for(int i = 0; i < (int)States.size(); i++)
   {
      Mean.SetPoint(i, Percentages[i], DHFile[States[i]]["Mean"].GetDouble());
      Mean.SetPointError(i, 0, DHFile[States[i]]["MeanError"].GetDouble());
      
      Sigma.SetPoint(i, Percentages[i], DHFile[States[i]]["Sigma"].GetDouble());
      Sigma.SetPointError(i, 0, DHFile[States[i]]["SigmaError"].GetDouble());

      RelativeYield.SetPoint(i, Percentages[i], (DHFile[States[i]]["YieldMean"].GetDouble() - 3000) / 3000);
      RelativeYield.SetPointError(i, 0, DHFile[States[i]]["YieldMeanError"].GetDouble() / 3000);
   }

   PsFileHelper PsFile(OutputBase + ".ps");

   TCanvas MeanCanvas("C", "C", 0, 0, 1024, 768);
   Mean.Draw("ap");
   Mean.GetHistogram()->GetXaxis()->SetTitle(Form("Percentage change in parameter %s", Parameter.c_str()));
   Mean.GetHistogram()->GetYaxis()->SetTitle("Mean in pull distribution");
   PsFile.AddCanvas(MeanCanvas);

   TCanvas SigmaCanvas("C2", "C", 0, 0, 1024, 768);
   Sigma.Draw("ap");
   Sigma.GetHistogram()->GetXaxis()->SetTitle(Form("Percentage change in parameter %s", Parameter.c_str()));
   Sigma.GetHistogram()->GetYaxis()->SetTitle("Sigma in pull distribution");
   PsFile.AddCanvas(SigmaCanvas);

   TCanvas TogetherCanvas("C3", "C", 0, 0, 1024, 768);

   Mean.SetTitle(Form("Mean and sigma of pull distribution varying parameter %s", Parameter.c_str()));
   Mean.GetHistogram()->SetMaximum(2.5);
   Mean.GetHistogram()->SetMinimum(-3);
   Mean.Draw("ap");
   Mean.GetHistogram()->GetYaxis()->SetTitle("");

   Sigma.SetLineColor(2);
   Sigma.Draw("p");

   TGraph Line1;
   Line1.SetLineColor(1);
   Line1.SetPoint(0, -1, 0);
   Line1.SetPoint(1, 1, 0);
   Line1.Draw("l");
   
   TGraph Line2;
   Line2.SetLineColor(2);
   Line2.SetPoint(0, -1, 1);
   Line2.SetPoint(1, 1, 1);
   Line2.Draw("l");

   TLegend legend(0.6, 0.35, 0.8, 0.2);
   legend.SetFillColor(0);
   legend.AddEntry(&Mean, "Mean", "l");
   legend.AddEntry(&Sigma, "Sigma", "l");
   legend.Draw();

   PsFile.AddCanvas(TogetherCanvas);

   TogetherCanvas.SaveAs(Form("SummaryPlot%s.C", Parameter.c_str()));
   TogetherCanvas.SaveAs(Form("SummaryPlot%s.eps", Parameter.c_str()));
   TogetherCanvas.SaveAs(Form("SummaryPlot%s.png", Parameter.c_str()));

   TCanvas RelativeYieldCanvas("CCC", "CCC", 0, 0, 1024, 768);

   RelativeYield.SetLineWidth(2);
   RelativeYield.Draw("ap");

   PsFile.AddCanvas(RelativeYieldCanvas);

   RelativeYieldCanvas.SaveAs(Form("ReltiveYield%s.C", Parameter.c_str()));
   RelativeYieldCanvas.SaveAs(Form("ReltiveYield%s.eps", Parameter.c_str()));
   RelativeYieldCanvas.SaveAs(Form("ReltiveYield%s.png", Parameter.c_str()));


   PsFile.AddTimeStampPage();
   PsFile.Close();
}






