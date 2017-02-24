#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main();
void DoPlot(string Tag, string OutputBase);

int main()
{
   SetThesisStyle();

   DoPlot("120_140_0.0_0.1", "Plot/120_140_0.0_0.1_");
   DoPlot("120_140_0.1_0.3", "Plot/120_140_0.1_0.3_");
   DoPlot("120_140_0.3_0.5", "Plot/120_140_0.3_0.5_");
   DoPlot("120_140_0.5_0.8", "Plot/120_140_0.5_0.8_");
   DoPlot("140_160_0.0_0.1", "Plot/140_160_0.0_0.1_");
   DoPlot("140_160_0.1_0.3", "Plot/140_160_0.1_0.3_");
   DoPlot("140_160_0.3_0.5", "Plot/140_160_0.3_0.5_");
   DoPlot("140_160_0.5_0.8", "Plot/140_160_0.5_0.8_");
   DoPlot("160_180_0.0_0.1", "Plot/160_180_0.0_0.1_");
   DoPlot("160_180_0.1_0.3", "Plot/160_180_0.1_0.3_");
   DoPlot("160_180_0.3_0.5", "Plot/160_180_0.3_0.5_");
   DoPlot("160_180_0.5_0.8", "Plot/160_180_0.5_0.8_");
   DoPlot("180_200_0.0_0.1", "Plot/180_200_0.0_0.1_");
   DoPlot("180_200_0.1_0.3", "Plot/180_200_0.1_0.3_");
   DoPlot("180_200_0.3_0.5", "Plot/180_200_0.3_0.5_");
   DoPlot("180_200_0.5_0.8", "Plot/180_200_0.5_0.8_");
   DoPlot("200_300_0.0_0.1", "Plot/200_300_0.0_0.1_");
   DoPlot("200_300_0.1_0.3", "Plot/200_300_0.1_0.3_");
   DoPlot("200_300_0.3_0.5", "Plot/200_300_0.3_0.5_");
   DoPlot("200_300_0.5_0.8", "Plot/200_300_0.5_0.8_");
   DoPlot("300_500_0.0_0.1", "Plot/300_500_0.0_0.1_");
   DoPlot("300_500_0.1_0.3", "Plot/300_500_0.1_0.3_");
   DoPlot("300_500_0.3_0.5", "Plot/300_500_0.3_0.5_");
   DoPlot("300_500_0.5_0.8", "Plot/300_500_0.5_0.8_");

   return 0;
}

void DoPlot(string Tag, string OutputBase)
{
   TFile File1(Form("Output_PPData_HiForest_0_%s.root", Tag.c_str()));
   TFile File2(Form("Output_AAData_HiForest_0_%s.root", Tag.c_str()));

   TH1D *HN1 = (TH1D *)File1.Get("HNPF");
   TH1D *HJ1 = (TH1D *)File1.Get("HJetPF");
   TH1D *HA1 = (TH1D *)File1.Get("HAddedPF");
   TH1D *HN2 = (TH1D *)File2.Get("HNPF");
   TH1D *HJ2 = (TH1D *)File2.Get("HJetPF");

   if(HN1 == NULL || HN2 == NULL)
      return;

   double HA1Integral = HA1->Integral();
   for(int i = 1; i <= HA1->GetNbinsX(); i++)
   {
      double x = HA1->GetBinCenter(i);
      double f = 0.6326 + 0.4143 * x;
      if(x > 1)
         f = 1.342 - 0.3497 * exp(-(x - 1.916) * (x - 1.916) / (2 * 0.8441 * 0.8441));
      HA1->SetBinContent(i, f * HA1->GetBinContent(i));
   }
   HA1->Scale(HA1Integral / HA1->Integral());

   HJ1->Scale(1.0 / HN1->GetEntries());
   HA1->Scale(1.0 / HN1->GetEntries());
   HJ2->Scale(1.0 / HN2->GetEntries());

   TH1D *HT1 = (TH1D *)HA1->Clone("HT1");
   HT1->Add(HJ1);

   HJ1->SetLineColor(kBlue);
   HA1->SetLineColor(kRed);
   HT1->SetLineColor(kBlack);
   HJ2->SetLineColor(kGreen + 3);

   TH2D HWorld1("HWorld1", ";PT;#", 100, 0, 100, 100, 0.0001, 50);
   TH2D HWorld2("HWorld2", ";PT;#", 100, 0, 15, 100, 0.0001, 50);
   TH2D HWorld3("HWorld3", ";PT;#", 100, 0, 5, 100, 0, 10);
   HWorld1.SetStats(0);
   HWorld2.SetStats(0);
   HWorld3.SetStats(0);

   TCanvas C;
   
   HWorld1.Draw();
   HA1->Draw("same");
   HJ1->Draw("same");
   HT1->Draw("same");
   HJ2->Draw("same");

   C.SetLogy();

   C.SaveAs((OutputBase + "Meow1.pdf").c_str());
   
   HWorld2.Draw();
   HA1->Draw("same");
   HJ1->Draw("same");
   HT1->Draw("same");
   HJ2->Draw("same");

   C.SetLogy();

   C.SaveAs((OutputBase + "Meow2.pdf").c_str());

   HWorld3.Draw();
   HA1->Draw("same");
   HJ1->Draw("same");
   HT1->Draw("same");
   HJ2->Draw("same");

   C.SetLogy(false);

   C.SaveAs((OutputBase + "Meow3.pdf").c_str());

   TTree *T1 = (TTree *)File1.Get("OutputTree");
   TTree *T2 = (TTree *)File2.Get("T");

   T1->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T1->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T1->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T1->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   
   TH1D H1("H1", "", 100, 0, 1000);
   TH1D H2("H2", "", 100, 0, 1000);

   T1->Draw("TotalStuffInJet+TotalPTInJet>>H1", "abs(BestJetEta) < 1.3 && BestJetPT > 140 && BestJetPT < 1000 && MatchedDR < 0.1");
   T2->Draw("TotalPF>>H2", "JetPT > 140 && JetPT < 1000");

   H1.Scale(1.0 / H1.Integral());
   H2.Scale(1.0 / H2.Integral());

   TH2D HWorld4("HWorld4", ";;", 100, 0, 1000, 100, 0, 0.15);
   HWorld4.SetStats(0);

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kGreen + 3);

   HWorld4.Draw();
   H1.Draw("same");
   H2.Draw("same");

   C.SaveAs((OutputBase + "Meow4.pdf").c_str());
}
