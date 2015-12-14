#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TArrow.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisRegularStyle();

   TFile FA2("FA2Toy.root");
   TFile FA3("FA3Toy.root");

   TTree *TA2 = (TTree *)FA2.Get("ResultTree");
   TTree *TA3 = (TTree *)FA3.Get("ResultTree");

   int BinCount = 100;

   TH1D HA2A1("HA2A1", ";A_{2}^{ZZ}/A_{1}^{ZZ};a.u.", 50, -10, 10);
   TH1D HA3A1("HA3A1", ";A_{3}^{ZZ}/A_{1}^{ZZ};a.u.", 50, -15, 15);
   TH1D HLogAbsA2A1("HLogAbsA2A1", ";log |A_{2}^{ZZ}/A_{1}^{ZZ}|;a.u.", 50, -5, 5);
   TH1D HLogAbsA3A1("HLogAbsA3A1", ";log |A_{3}^{ZZ}/A_{1}^{ZZ}|;a.u.", 50, -5, 5);

   HA2A1.SetStats(0);
   HA3A1.SetStats(0);
   HLogAbsA2A1.SetStats(0);
   HLogAbsA3A1.SetStats(0);

   HA2A1.SetLineWidth(2);
   HA3A1.SetLineWidth(2);
   HLogAbsA2A1.SetLineWidth(2);
   HLogAbsA3A1.SetLineWidth(2);
   
   HA2A1.SetNdivisions(505);
   HA3A1.SetNdivisions(505);
   HLogAbsA2A1.SetNdivisions(505);
   HLogAbsA3A1.SetNdivisions(505);
   
   TArrow Arrow;
   Arrow.SetLineWidth(2);
   Arrow.SetArrowSize(0.03);
   Arrow.SetAngle(30);
   Arrow.SetFillColor(kBlack);

   TA2->Draw("A2ZZA1ZZ>>HA2A1", "Status == 3");
   TA3->Draw("A3ZZA1ZZ>>HA3A1", "Status == 3");
   TA2->Draw("log(abs(A2ZZA1ZZ))>>HLogAbsA2A1", "Status == 3");
   TA3->Draw("log(abs(A3ZZA1ZZ))>>HLogAbsA3A1", "Status == 3");

   HA2A1.Scale(1 / HA2A1.Integral());
   HA3A1.Scale(1 / HA3A1.Integral());
   HLogAbsA2A1.Scale(1 / HLogAbsA2A1.Integral());
   HLogAbsA3A1.Scale(1 / HLogAbsA3A1.Integral());

   HA2A1.SetMaximum(0.138);
   HA3A1.SetMaximum(0.138);
   HLogAbsA2A1.SetMaximum(0.138);
   HLogAbsA3A1.SetMaximum(0.138);
   
   TCanvas C;

   HA2A1.Draw();
   Arrow.DrawArrow(0.2639, 0.02, 0.2639, 0);
   
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA2.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA2.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA2.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA2.pdf");

   HA3A1.Draw();
   Arrow.DrawArrow(0.1139, 0.02, 0.1139, 0);
   
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA3.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA3.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA3.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityA3.pdf");

   HLogAbsA2A1.Draw();
   Arrow.DrawArrow(log(0.2639), 0.02, log(0.2639), 0);
   
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA2.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA2.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA2.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA2.pdf");

   HLogAbsA3A1.Draw();
   Arrow.DrawArrow(log(0.1139), 0.02, log(0.1139), 0);
   
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA3.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA3.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA3.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityLogAbsA3.pdf");

   return 0;
}






