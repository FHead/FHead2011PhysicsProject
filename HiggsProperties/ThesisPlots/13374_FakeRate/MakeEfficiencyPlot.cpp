#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "LeptonResponse.h"

int main()
{
   SetThesisRegularStyle();

   TH2D HE7("HE7", ";|#eta|;p_{T};Fake rate (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HE8("HE8", ";|#eta|;p_{T};Fake rate (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HM7("HM7", ";|#eta|;p_{T};Fake rate (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HM8("HM8", ";|#eta|;p_{T};Fake rate (%)", 25, 0, 2.5, 60, 0, 60);

   for(int ix = 1; ix <= HM8.GetNbinsX(); ix++)
   {
      for(int iy = 1; iy <= HM8.GetNbinsY(); iy++)
      {
         double eta = HM8.GetXaxis()->GetBinCenter(ix);
         double pt = HM8.GetYaxis()->GetBinCenter(iy);
         
         FourVector X;
         X.SetPtEtaPhi(pt, eta, 0);

         double pzp = X[3] / X.GetP();

         HE7.SetBinContent(ix, iy, 100 * GetFakeElectronEfficiencyPtEta7TeV(pt, pzp, 0));
         HE8.SetBinContent(ix, iy, 100 * GetFakeElectronEfficiencyPtEta8TeV(pt, pzp, 0));
         HM7.SetBinContent(ix, iy, 100 * GetFakeMuonEfficiencyPtEta7TeV(pt, pzp, 0));
         HM8.SetBinContent(ix, iy, 100 * GetFakeMuonEfficiencyPtEta8TeV(pt, pzp, 0));
      }
   }

   HE7.SetStats(0);
   HE8.SetStats(0);
   HM7.SetStats(0);
   HM8.SetStats(0);

   HE7.SetMaximum(0.01 * 100);
   HE8.SetMaximum(0.001 * 100);
   HM7.SetMaximum(0.01 * 100);
   HM8.SetMaximum(0.001 * 100);

   // HE7.GetXaxis()->SetTitleOffset(1.1);
   // HE8.GetXaxis()->SetTitleOffset(1.1);
   // HM7.GetXaxis()->SetTitleOffset(1.1);
   // HM8.GetXaxis()->SetTitleOffset(1.1);

   // HE7.GetYaxis()->SetTitleOffset(1.2);
   // HE8.GetYaxis()->SetTitleOffset(1.2);
   // HM7.GetYaxis()->SetTitleOffset(1.2);
   // HM8.GetYaxis()->SetTitleOffset(1.2);

   HE7.GetZaxis()->SetTitleOffset(2.0);
   HE8.GetZaxis()->SetTitleOffset(2.0);
   HM7.GetZaxis()->SetTitleOffset(2.0);
   HM8.GetZaxis()->SetTitleOffset(2.0);

   // TCanvas C("C", "C", 1024, 1024);
   TCanvas C;

   HE7.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E7.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E7.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E7.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E7.pdf");

   HE8.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E8.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E8.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E8.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-E8.pdf");

   HM7.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M7.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M7.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M7.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M7.pdf");

   HM8.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M8.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M8.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M8.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRate-M8.pdf");

   return 0;
}




