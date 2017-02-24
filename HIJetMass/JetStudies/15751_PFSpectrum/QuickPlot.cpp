#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File1("Output_PPData_HiForest_0_ModifiedPTData_30_50.root");
   TFile File2("Output_AAData_HiForest_0_30_50.root");

   TH1D *HN1 = (TH1D *)File1.Get("HNPF");
   TH1D *HJ1 = (TH1D *)File1.Get("HJetPF");
   TH1D *HA1 = (TH1D *)File1.Get("HAddedPF");
   TH1D *HN2 = (TH1D *)File2.Get("HNPF");
   TH1D *HJ2 = (TH1D *)File2.Get("HJetPF");

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
   TH2D HWorld3("HWorld3", ";PT;#", 100, 0, 5, 100, 0, 5);
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

   C.SaveAs("Meow1.pdf");
   
   HWorld2.Draw();
   HA1->Draw("same");
   HJ1->Draw("same");
   HT1->Draw("same");
   HJ2->Draw("same");

   C.SetLogy();

   C.SaveAs("Meow2.pdf");

   HWorld3.Draw();
   HA1->Draw("same");
   HJ1->Draw("same");
   HT1->Draw("same");
   HJ2->Draw("same");

   C.SetLogy(false);

   C.SaveAs("Meow3.pdf");

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

   C.SaveAs("Meow4.pdf");

   return 0;
}
