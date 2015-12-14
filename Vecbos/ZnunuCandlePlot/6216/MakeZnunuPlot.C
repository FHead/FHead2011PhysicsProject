#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"

void MakeZnunuPlot()
{
   TFile FMuMu("Samples/ZJetsAll.root");
   TFile FNuNu("Samples/ZnunuAll.root");

   TH1D *HMuMuDiMuonPT = (TH1D *)FMuMu.Get("HHighZPt");
   TH1D *HNuNuMET = (TH1D *)FNuNu.Get("HMET");
   TH1D *HNuNuPFMET = (TH1D *)FNuNu.Get("HPFMET");

   HMuMuDiMuonPT->SetLineColor(1);
   HNuNuMET->SetLineColor(2);
   HNuNuPFMET->SetLineColor(3);

   TCanvas Canvas("C1", "C1");

   HMuMuDiMuonPT->Draw();
   HNuNuPFMET->Draw("same");
   Canvas.SetLogy();
   Canvas.SaveAs("WithPFMET.png");

   HMuMuDiMuonPT->Draw();
   HNuNuMET->Draw("same");
   Canvas.SaveAs("WithCaloMET.png");

   HNuNuPFMET->Divide(HMuMuDiMuonPT);
   HNuNuPFMET->Draw();
   Canvas.SaveAs("PFMETRatio.png");
   
   HNuNuMET->Divide(HMuMuDiMuonPT);
   HNuNuMET->Draw();
   Canvas.SaveAs("CaloMETRatio.png");

   FMuMu.Close();
   FNuNu.Close();
}
