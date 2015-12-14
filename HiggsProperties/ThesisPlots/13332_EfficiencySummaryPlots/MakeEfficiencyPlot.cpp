#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "LeptonResponse.h"

int main()
{
   SetThesisRegularStyle();

   TH2D HE7("HE7", ";|#eta|;p_{T}", 25, 0, 2.5, 60, 0, 60);
   TH2D HE8("HE8", ";|#eta|;p_{T}", 25, 0, 2.5, 60, 0, 60);
   TH2D HM7("HM7", ";|#eta|;p_{T}", 25, 0, 2.5, 60, 0, 60);
   TH2D HM8("HM8", ";|#eta|;p_{T}", 25, 0, 2.5, 60, 0, 60);

   for(int ix = 1; ix <= HM8.GetNbinsX(); ix++)
   {
      for(int iy = 1; iy <= HM8.GetNbinsY(); iy++)
      {
         double eta = HM8.GetXaxis()->GetBinCenter(ix);
         double pt = HM8.GetYaxis()->GetBinCenter(iy);
         
         FourVector X;
         X.SetPtEtaPhi(pt, eta, 0);

         double pzp = X[3] / X.GetP();

         HE7.SetBinContent(ix, iy, GetElectronEfficiencyPtEta7TeV(pt, pzp, 0));
         HE8.SetBinContent(ix, iy, GetElectronEfficiencyPtEta8TeV(pt, pzp, 0));
         HM7.SetBinContent(ix, iy, GetMuonEfficiencyPtEta7TeV(pt, pzp, 0));
         HM8.SetBinContent(ix, iy, GetMuonEfficiencyPtEta8TeV(pt, pzp, 0));
      }
   }

   HE7.SetStats(0);
   HE8.SetStats(0);
   HM7.SetStats(0);
   HM8.SetStats(0);

   HE7.SetMaximum(1);
   HE8.SetMaximum(1);
   HM7.SetMaximum(1);
   HM8.SetMaximum(1);

   TCanvas C;

   HE7.Draw("colz");

   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E7.png");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E7.C");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E7.eps");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E7.pdf");

   HE8.Draw("colz");

   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E8.png");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E8.C");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E8.eps");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-E8.pdf");

   HM7.Draw("colz");

   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M7.png");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M7.C");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M7.eps");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M7.pdf");

   HM8.Draw("colz");

   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M8.png");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M8.C");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M8.eps");
   C.SaveAs("DetectorParameterization-Extraction-Efficiency-M8.pdf");

   return 0;
}




