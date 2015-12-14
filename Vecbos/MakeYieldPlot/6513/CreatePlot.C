#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
using namespace RooFit;

// #include "PlotHelper.h"

void CreatePlot(string FileName = "combined-sim-exclfit0123410.root")
{
   TFile F(FileName.c_str());

   RooFitResult *FitResult = (RooFitResult *)F.Get("nll_myFit_data");
   if(FitResult == NULL)
      return;

   vector<string> BinNames;
   BinNames.push_back("N_sig_1j");
   BinNames.push_back("N_sig_2j");
   BinNames.push_back("N_sig_3j");
   BinNames.push_back("N_sig_4j");

   vector<double> ExclusiveYields;
   vector<double> ExclusiveErrors;

   for(int i = 0; i < (int)BinNames.size(); i++)
   {
      ExclusiveYields.push_back(((RooRealVar *)(FitResult->floatParsFinal().find(BinNames[i].c_str())))->getVal());
      ExclusiveErrors.push_back(((RooRealVar *)(FitResult->floatParsFinal().find(BinNames[i].c_str())))->getError());
   }

   vector<double> InclusiveYields;
   vector<double> InclusiveErrors;
   
   double YieldsSoFar = 0;
   double Error2SoFar = 0;

   for(int i = BinNames.size() - 1; i >= 0; i--)
   {
      YieldsSoFar = YieldsSoFar + ExclusiveYields[i];
      Error2SoFar = Error2SoFar + ExclusiveErrors[i] * ExclusiveErrors[i];

      InclusiveYields.push_back(YieldsSoFar);
      InclusiveErrors.push_back(sqrt(Error2SoFar));
   }

   reverse(InclusiveYields.begin(), InclusiveYields.end());
   reverse(InclusiveErrors.begin(), InclusiveErrors.end());

   TH1D HInclusiveYields("HInclusiveYields",
      Form("Inclusive yields for PF jets with threshold 30 GeV;Inclusive jet count;Yield"),
      BinNames.size(), 0.5, BinNames.size() + 0.5);
   TH1D HRatio("HRatio", ";N (Inclusive jet count);#frac{W + N Jets}{W + (N+1) Jets}",
      BinNames.size(), 0.5, BinNames.size() + 0.5);

   TGraphErrors GInclusiveYields;
   GInclusiveYields.SetName("GInclusiveYields");
   GInclusiveYields.SetLineWidth(2);
   TGraphErrors GRatio;
   GRatio.SetNameTitle("GRatio", Form(";N (Inclusive jet count);#frac{W + N Jets}{W + (N+1) Jets}"));
   GRatio.SetLineWidth(2);

   // TGraphErrors BandFromComplicatedFit;
   // TGraphErrors LineFromComplicatedFit;
   
   HInclusiveYields.GetYaxis()->SetRangeUser(0.3, InclusiveYields[0] * 3);

   HInclusiveYields.SetStats(0);
   HRatio.SetStats(0);

   for(int i = 0; i < (int)BinNames.size(); i++)
   {
      HInclusiveYields.SetBinContent(i + 1, InclusiveYields[i]);
      HInclusiveYields.SetBinError(i + 1, InclusiveErrors[i]);
      
      GInclusiveYields.SetPoint(i, i + 1, InclusiveYields[i]);
      GInclusiveYields.SetPointError(i, 0, InclusiveErrors[i]);

      if(i != (int)BinNames.size() - 1)
      {
         double y = ExclusiveYields[i];
         double x = InclusiveYields[i+1];
         double sy = ExclusiveErrors[i];
         double sx = InclusiveErrors[i+1];

         double Error2 = (y / x / x * sx) * (y / x / x * sx) + (sy / x) * (sy / x);

         HRatio.SetBinContent(i + 1, (x + y) / x);
         HRatio.SetBinError(i + 1, sqrt(Error2));
         
         GRatio.SetPoint(i, i + 1, (x + y) / x);
         GRatio.SetPointError(i, 0, sqrt(Error2));
      }
   }

   TF1 LinearFit("LinearFit", "pol1", 0.5, (int)BinNames.size() + 1);

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);

   TPad *Canvas_1 = new TPad("Canvas_1", "Canvas_1", 0, 0.4, 1, 1);
   Canvas_1->Draw();
   Canvas_1->cd();
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetLogy();

   HInclusiveYields.GetYaxis()->SetTitleOffset(HInclusiveYields.GetYaxis()->GetTitleOffset() / 2);
   HInclusiveYields.GetXaxis()->SetLabelSize(0.05);
   HInclusiveYields.GetXaxis()->SetTitleSize(0.05);
   HInclusiveYields.GetYaxis()->SetLabelSize(0.05);
   HInclusiveYields.GetYaxis()->SetTitleSize(0.05);
   HInclusiveYields.SetLineColor(0);
   HInclusiveYields.SetMarkerSize(2);
   HInclusiveYields.Draw("hist");

   GInclusiveYields.Draw("ep");

   Canvas.cd();
   TPad *Canvas_2 = new TPad("Canvas_2", "Canvas_2", 0, 0.0, 1, 0.4);
   Canvas_2->SetBottomMargin(0.25);
   Canvas_2->Draw();
   Canvas_2->cd();
   Canvas_2->SetFillColor(0);
   Canvas_2->SetBorderMode(0);
   Canvas_2->SetBorderSize(2);

   HRatio.GetYaxis()->SetTitleOffset(0.4);
   HRatio.GetXaxis()->SetLabelSize(0.07);
   HRatio.GetXaxis()->SetTitleSize(0.07);
   HRatio.GetYaxis()->SetLabelSize(0.07);
   HRatio.GetYaxis()->SetTitleSize(0.07);
   HRatio.SetLineWidth(2);
   HRatio.SetLineColor(0);
   HRatio.Draw("error");

   GRatio.Draw("ep");

   // PsFileHelper PsFile("Result.ps");
   // PsFile.AddCanvas(Canvas);
   // PsFile.AddTimeStampPage();
   // PsFile.Close();

   Canvas.SaveAs("Result.C");
   Canvas.SaveAs("Result.eps");
   Canvas.SaveAs("Resutl.png");

   F.Close();
}



