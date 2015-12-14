#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "LeptonResponse.h"

int main()
{
   SetThesisRegularStyle();

   TH1D HMuA("HMuA", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);
   TH1D HMuB("HMuB", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);
   TH1D HMuC("HMuC", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);
   TH1D HEleA("HEleA", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);
   TH1D HEleB("HEleB", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);
   TH1D HEleC("HEleC", ";c - 1;T(c_{i}|#vec{p}_{i}^{G})", 1000, -0.25, 0.25);

   HMuA.GetXaxis()->SetNdivisions(505);
   HMuB.GetXaxis()->SetNdivisions(505);
   HMuC.GetXaxis()->SetNdivisions(505);
   HEleA.GetXaxis()->SetNdivisions(505);
   HEleB.GetXaxis()->SetNdivisions(505);
   HEleC.GetXaxis()->SetNdivisions(505);

   for(int ix = 1; ix <= HMuA.GetNbinsX(); ix++)
   {
      double Delta = HMuA.GetXaxis()->GetBinCenter(ix);

      FourVector A, B, C;
      A.SetPtEtaPhi(15, 0.6, 0);
      B.SetPtEtaPhi(30, 0.6, 0);
      C.SetPtEtaPhi(45, 0.6, 0);

      HMuA.SetBinContent(ix, SmearMuon(A, Delta));
      HMuB.SetBinContent(ix, SmearMuon(B, Delta));
      HMuC.SetBinContent(ix, SmearMuon(C, Delta));
      HEleA.SetBinContent(ix, SmearElectron(A, Delta));
      HEleB.SetBinContent(ix, SmearElectron(B, Delta));
      HEleC.SetBinContent(ix, SmearElectron(C, Delta));
   }

   HMuA.SetStats(0);
   HMuB.SetStats(0);
   HMuC.SetStats(0);
   HEleA.SetStats(0);
   HEleB.SetStats(0);
   HEleC.SetStats(0);

   TCanvas C;
   C.SetLogy();

   HMuA.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-MuA.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuA.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuA.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuA.pdf");

   HMuB.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-MuB.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuB.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuB.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuB.pdf");

   HMuC.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-MuC.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuC.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuC.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-MuC.pdf");

   HEleA.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-EleA.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleA.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleA.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleA.pdf");

   HEleB.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-EleB.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleB.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleB.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleB.pdf");

   HEleC.Draw();

   C.SaveAs("DetectorParameterization-Extraction-Example-EleC.png");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleC.C");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleC.eps");
   C.SaveAs("DetectorParameterization-Extraction-Example-EleC.pdf");

   return 0;
}




