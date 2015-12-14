#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "LeptonResponse.h"

int main()
{
   SetThesisRegularStyle();

   TH2D HE7("HE7", ";|#eta|;p_{T};Relative width (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HE8("HE8", ";|#eta|;p_{T};Relative width (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HM7("HM7", ";|#eta|;p_{T};Relative width (%)", 25, 0, 2.5, 60, 0, 60);
   TH2D HM8("HM8", ";|#eta|;p_{T};Relative width (%)", 25, 0, 2.5, 60, 0, 60);

   for(int ix = 1; ix <= HM8.GetNbinsX(); ix++)
   {
      for(int iy = 1; iy <= HM8.GetNbinsY(); iy++)
      {
         double eta = HM8.GetXaxis()->GetBinCenter(ix);
         double pt = HM8.GetYaxis()->GetBinCenter(iy);
         
         FourVector X;
         X.SetPtEtaPhi(pt, eta, 0);

         double pzp = X[3] / X.GetP();

         TH1D H1("H1", "", 5000, -0.75, 0.75);
         TH1D H2("H2", "", 5000, -0.75, 0.75);
         TH1D H3("H3", "", 5000, -0.75, 0.75);
         TH1D H4("H4", "", 5000, -0.75, 0.75);

         for(int i = 1; i <= 5000; i++)
         {
            double x = H1.GetBinCenter(i);
            H1.SetBinContent(i, SmearFakeElectron7TeV(X, x));
            H2.SetBinContent(i, SmearFakeElectron8TeV(X, x));
            H3.SetBinContent(i, SmearFakeMuon7TeV(X, x));
            H4.SetBinContent(i, SmearFakeMuon8TeV(X, x));
         }

         if(pt > 7 && eta < 2.5)
         {
            HE7.SetBinContent(ix, iy, H1.GetRMS() * 100); 
            HE8.SetBinContent(ix, iy, H2.GetRMS() * 100);
         }
         if(pt > 5 && eta < 2.4)
         {
            HM7.SetBinContent(ix, iy, H3.GetRMS() * 100);
            HM8.SetBinContent(ix, iy, H4.GetRMS() * 100);
         }
      }
   }

   HE7.SetStats(0);
   HE8.SetStats(0);
   HM7.SetStats(0);
   HM8.SetStats(0);

   HE7.SetMaximum(25);
   HE8.SetMaximum(25);
   HM7.SetMaximum(25);
   HM8.SetMaximum(25);
   
   HE7.GetZaxis()->SetTitleOffset(2.0);
   HE8.GetZaxis()->SetTitleOffset(2.0);
   HM7.GetZaxis()->SetTitleOffset(2.0);
   HM8.GetZaxis()->SetTitleOffset(2.0);

   TCanvas C;

   HE7.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E7.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E7.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E7.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E7.pdf");

   HE8.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E8.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E8.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E8.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-E8.pdf");

   HM7.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M7.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M7.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M7.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M7.pdf");

   HM8.Draw("colz");

   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M8.png");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M8.C");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M8.eps");
   C.SaveAs("MultiDimensionalOverview-Template-FakeRateSummary-M8.pdf");

   return 0;
}




