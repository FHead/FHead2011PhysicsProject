#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

int main()
{
   TFile FData("Histograms/PhotonHadRun2011All.root");
   TFile FMC("Histograms/GJet_All.root");

   TH1D *H1Data = (TH1D *)FData.Get("HPhotonMR_R2025_Photon_All");
   TH1D *H1MC = (TH1D *)FMC.Get("HPhotonMR_R2025_Photon_All");
   H1MC->Scale(4.716);   // lumi
   H1MC->SetStats(0);
   H1MC->SetLineWidth(2);
   H1MC->SetLineColor(kRed);
   H1MC->SetTitle("Data vs. GJet MC comparison, MR, R2 > 0.25");
   H1Data->SetStats(0);
   H1Data->SetLineWidth(2);
   TCanvas C1("C1", "C1", 1024, 1024);
   H1MC->Draw();
   H1Data->Draw("same error");
   C1.SetLogy();
   C1.SaveAs("HPhotonMR_R2025_Photon_All.png");
   C1.SaveAs("HPhotonMR_R2025_Photon_All.C");
   C1.SaveAs("HPhotonMR_R2025_Photon_All.eps");
   C1.SaveAs("HPhotonMR_R2025_Photon_All.pdf");

   TH1D *H2Data = (TH1D *)FData.Get("HPhotonR2_MR400_Photon_All");
   TH1D *H2MC = (TH1D *)FMC.Get("HPhotonR2_MR400_Photon_All");
   H2MC->Scale(4.716);   // lumi
   H2MC->SetStats(0);
   H2MC->SetLineWidth(2);
   H2MC->SetLineColor(kRed);
   H2MC->SetTitle("Data vs. GJet MC comparison, R2, MR > 400");
   H2Data->SetStats(0);
   H2Data->SetLineWidth(2);
   TCanvas C2("C2", "C2", 1024, 1024);
   H2MC->Draw();
   H2Data->Draw("same error");
   C2.SetLogy();
   C2.SaveAs("HPhotonR2_MR400_Photon_All.png");
   C2.SaveAs("HPhotonR2_MR400_Photon_All.C");
   C2.SaveAs("HPhotonR2_MR400_Photon_All.eps");
   C2.SaveAs("HPhotonR2_MR400_Photon_All.pdf");

   TH1D *H3Data = (TH1D *)FData.Get("HPhotonPT_MR400R2025_Photon_All");
   TH1D *H3MC = (TH1D *)FMC.Get("HPhotonPT_MR400R2025_Photon_All");
   H3MC->Scale(4.716);   // lumi
   H3MC->SetStats(0);
   H3MC->SetLineWidth(2);
   H3MC->SetLineColor(kRed);
   H3MC->SetTitle("Data vs. GJet MC comparison, Photon PT, MR > 400, R2 > 0.25");
   H3Data->SetStats(0);
   H3Data->SetLineWidth(2);
   TCanvas C3("C3", "C3", 1024, 1024);
   H3MC->Draw();
   H3Data->Draw("same error");
   C3.SetLogy();
   C3.SaveAs("HPhotonPT_MR400R2025_Photon_All.png");
   C3.SaveAs("HPhotonPT_MR400R2025_Photon_All.C");
   C3.SaveAs("HPhotonPT_MR400R2025_Photon_All.eps");
   C3.SaveAs("HPhotonPT_MR400R2025_Photon_All.pdf");

   FMC.Close();
   FData.Close();

   return 0;
}




