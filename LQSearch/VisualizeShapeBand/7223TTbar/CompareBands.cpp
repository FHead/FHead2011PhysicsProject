#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TFile.h"

#include "PlotHelper2.h"

int main()
{
   PsFileHelper PsFile("BandComparison.ps");
   PsFile.AddTextPage("Compare bands from the ttbar fit");

   vector<string> Explanations;
   Explanations.push_back("Start from the ttbar fit result in e-mu box (loose tag x1, 30 GeV)");
   Explanations.push_back("Vary floated parameters (a,b,yields) according to RooFitResult");
   Explanations.push_back("      and find out the 1-sigma (and 2-sigma bands, not plotted here)");
   Explanations.push_back("On top of the result, insert additional gaussian smearing to parameters a and b");
   Explanations.push_back("      assuming different correlation coefficient of the two smearing");
   Explanations.push_back("The extra smearing is uncorrelated with the rest of correlation from the fit");
   Explanations.push_back("Extra sigma on a is always 10%, and extra sigma on b is always 40%");
   Explanations.push_back("Correlation coefficient can change from -0.85, 0 to 0.999");
   Explanations.push_back("First few pages serve as sanity check on the generation of correlated gaussian");
   Explanations.push_back("");
   Explanations.push_back("Then, look at the bands and compare with original");
   Explanations.push_back("The total PDF (R (new) > 0.3) is normalized to 1 in all cases as is default in");
   Explanations.push_back("      RooFit.  We can scale everything up linearly to get expected band");
   PsFile.AddTextPage(Explanations);

   TFile F("Bands_100Bins1000Tries.root");

   PsFile.AddHistogramFromFile(F, "HChangeAB_SmearA", "colz");
   PsFile.AddHistogramFromFile(F, "HChangeAB_SmearBoth", "colz");
   PsFile.AddHistogramFromFile(F, "HChangeAB_SmearBothNoCorrelation", "colz");
   PsFile.AddHistogramFromFile(F, "HChangeAB_SmearBothFullCorrelation", "colz");

   TGraphAsymmErrors *GFull = (TGraphAsymmErrors *)F.Get("OneSigma_SmearBothFullCorrelation");
   TGraphAsymmErrors *GNone = (TGraphAsymmErrors *)F.Get("OneSigma_SmearBothNoCorrelation");
   TGraphAsymmErrors *GNominal = (TGraphAsymmErrors *)F.Get("OneSigma_SmearBoth");
   TGraphAsymmErrors *GA = (TGraphAsymmErrors *)F.Get("OneSigma_SmearA");
   TGraphAsymmErrors *GFit = (TGraphAsymmErrors *)F.Get("OneSigma_Fit");
   
   TGraphAsymmErrors *GFull04 = (TGraphAsymmErrors *)F.Get("OneSigma01_SmearBothFullCorrelation");
   TGraphAsymmErrors *GNone04 = (TGraphAsymmErrors *)F.Get("OneSigma01_SmearBothNoCorrelation");
   TGraphAsymmErrors *GNominal04 = (TGraphAsymmErrors *)F.Get("OneSigma01_SmearBoth");
   TGraphAsymmErrors *GFit04 = (TGraphAsymmErrors *)F.Get("OneSigma01_Fit");

   TGraphAsymmErrors *GFull05 = (TGraphAsymmErrors *)F.Get("OneSigma02_SmearBothFullCorrelation");
   TGraphAsymmErrors *GNone05 = (TGraphAsymmErrors *)F.Get("OneSigma02_SmearBothNoCorrelation");
   TGraphAsymmErrors *GNominal05 = (TGraphAsymmErrors *)F.Get("OneSigma02_SmearBoth");
   TGraphAsymmErrors *GFit05 = (TGraphAsymmErrors *)F.Get("OneSigma02_Fit");

   TGraphAsymmErrors *GFull06 = (TGraphAsymmErrors *)F.Get("OneSigma03_SmearBothFullCorrelation");
   TGraphAsymmErrors *GNone06 = (TGraphAsymmErrors *)F.Get("OneSigma03_SmearBothNoCorrelation");
   TGraphAsymmErrors *GNominal06 = (TGraphAsymmErrors *)F.Get("OneSigma03_SmearBoth");
   TGraphAsymmErrors *GFit06 = (TGraphAsymmErrors *)F.Get("OneSigma03_Fit");

   GFull->SetFillColor(kGreen + 2);
   GNone->SetFillColor(kMagenta + 2);
   GNominal->SetFillColor(kBlue + 2);
   GA->SetFillColor(kCyan + 2);
   GFit->SetFillColor(kRed + 2);
   
   GFull04->SetFillColor(kGreen + 2);
   GNone04->SetFillColor(kMagenta + 2);
   GNominal04->SetFillColor(kBlue + 2);
   GFit04->SetFillColor(kRed + 2);
   
   GFull05->SetFillColor(kGreen + 2);
   GNone05->SetFillColor(kMagenta + 2);
   GNominal05->SetFillColor(kBlue + 2);
   GFit05->SetFillColor(kRed + 2);

   GFull06->SetFillColor(kGreen + 2);
   GNone06->SetFillColor(kMagenta + 2);
   GNominal06->SetFillColor(kBlue + 2);
   GFit06->SetFillColor(kRed + 2);
   
   TCanvas C1;

   TH1D HWorld1("HWorld1", "Smear parameter a vs. original (R (new) > 0.3);MR (new);a.u.", 10, 400, 1000);
   HWorld1.SetStats(0);
   HWorld1.SetMinimum(0.0001);
   HWorld1.SetMaximum(1);
   HWorld1.Draw();

   GA->Draw("3");
   GFit->Draw("3");

   TLegend legend1(0.5, 0.8, 0.8, 0.6);
   legend1.SetFillStyle(0);
   legend1.SetBorderSize(0);
   legend1.SetTextFont(42);
   legend1.AddEntry(GFit, "Fit", "f");
   legend1.AddEntry(GA, "Fit + smear in a", "f");
   legend1.Draw();

   C1.SetLogy();
   PsFile.AddCanvas(C1);

   C1.SaveAs("Plots/SmearAComparison.png");
   C1.SaveAs("Plots/SmearAComparison.C");
   C1.SaveAs("Plots/SmearAComparison.eps");
   C1.SaveAs("Plots/SmearAComparison.pdf");

   TCanvas C2;
   
   TH1D HWorld2("HWorld2", "Smear a/b vs. original (R (new) > 0.3);MR (new);a.u.", 10, 400, 1000);
   HWorld2.SetStats(0);
   HWorld2.SetMinimum(0.0005);
   HWorld2.SetMaximum(0.5);
   HWorld2.Draw();

   GFull->Draw("3");
   GNone->Draw("3");
   GNominal->Draw("3");
   GFit->Draw("3");

   TLegend legend2(0.5, 0.8, 0.8, 0.6);
   legend2.SetFillStyle(0);
   legend2.SetBorderSize(0);
   legend2.SetTextFont(42);
   legend2.AddEntry(GFit, "Fit", "f");
   legend2.AddEntry(GFull, "#rho_{#sigma_{a},#sigma_{b}} = 0.999", "f");
   legend2.AddEntry(GNone, "#rho_{#sigma_{a},#sigma_{b}} = 0", "f");
   legend2.AddEntry(GNominal, "#rho_{#sigma_{a},#sigma_{b}} = -0.85", "f");
   legend2.Draw();

   C2.SetLogy();
   PsFile.AddCanvas(C2);
   
   C2.SaveAs("Plots/SmearComparison03.png");
   C2.SaveAs("Plots/SmearComparison03.C");
   C2.SaveAs("Plots/SmearComparison03.eps");
   C2.SaveAs("Plots/SmearComparison03.pdf");

   TCanvas C3;
   
   TH1D HWorld3("HWorld3", "Smear a/b vs. original (R (new) > 0.4);MR (new);a.u.", 10, 400, 1000);
   HWorld3.SetStats(0);
   HWorld3.SetMinimum(0.0005);
   HWorld3.SetMaximum(0.5);
   HWorld3.Draw();

   GFull04->Draw("3");
   GNone04->Draw("3");
   GNominal04->Draw("3");
   GFit04->Draw("3");

   legend2.Draw();

   C3.SetLogy();
   PsFile.AddCanvas(C3);
   
   C3.SaveAs("Plots/SmearComparison04.png");
   C3.SaveAs("Plots/SmearComparison04.C");
   C3.SaveAs("Plots/SmearComparison04.eps");
   C3.SaveAs("Plots/SmearComparison04.pdf");

   TCanvas C4;
   
   TH1D HWorld4("HWorld4", "Smear a/b vs. original (R (new) > 0.5);MR (new);a.u.", 10, 400, 1000);
   HWorld4.SetStats(0);
   HWorld4.SetMinimum(0.0005);
   HWorld4.SetMaximum(0.5);
   HWorld4.Draw();

   GFull05->Draw("3");
   GNone05->Draw("3");
   GNominal05->Draw("3");
   GFit05->Draw("3");

   legend2.Draw();

   C4.SetLogy();
   PsFile.AddCanvas(C4);
   
   C4.SaveAs("Plots/SmearComparison05.png");
   C4.SaveAs("Plots/SmearComparison05.C");
   C4.SaveAs("Plots/SmearComparison05.eps");
   C4.SaveAs("Plots/SmearComparison05.pdf");

   TCanvas C5;
   
   TH1D HWorld5("HWorld5", "Smear a/b vs. original (R (new) > 0.6);MR (new);a.u.", 10, 400, 1000);
   HWorld5.SetStats(0);
   HWorld5.SetMinimum(0.0005);
   HWorld5.SetMaximum(0.5);
   HWorld5.Draw();

   GFull06->Draw("3");
   GNone06->Draw("3");
   GNominal06->Draw("3");
   GFit06->Draw("3");

   legend2.Draw();

   C5.SetLogy();
   PsFile.AddCanvas(C5);

   C5.SaveAs("Plots/SmearComparison06.png");
   C5.SaveAs("Plots/SmearComparison06.C");
   C5.SaveAs("Plots/SmearComparison06.eps");
   C5.SaveAs("Plots/SmearComparison06.pdf");

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}
