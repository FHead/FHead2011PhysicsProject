#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   string InputFile = argv[1];
   string OutputBase = argv[2];

   TFile File(InputFile.c_str());

   TH1D *HMuon = (TH1D *)File.Get("HMuonEta");
   TH1D *HElectron = (TH1D *)File.Get("HElectronEta");
   TH1D *HPhoton = (TH1D *)File.Get("HPhotonEta");
   TH1D *HChargedHadron = (TH1D *)File.Get("HChargedHadronEta");
   TH1D *HNeutralHadron = (TH1D *)File.Get("HNeutralHadronEta");

   TH1D *HTotal = (TH1D *)HMuon->Clone("HTotal");
   HTotal->Add(HElectron);
   HTotal->Add(HPhoton);
   HTotal->Add(HChargedHadron);
   HTotal->Add(HNeutralHadron);

   HMuon->Divide(HTotal);
   HElectron->Divide(HTotal);
   HPhoton->Divide(HTotal);
   HChargedHadron->Divide(HTotal);
   HNeutralHadron->Divide(HTotal);

   HChargedHadron->Add(HNeutralHadron);
   HPhoton->Add(HChargedHadron);
   HElectron->Add(HPhoton);
   HMuon->Add(HElectron);

   HMuon->SetFillColor(kRed - 3);
   HElectron->SetFillColor(kBlue);
   HPhoton->SetFillColor(kOrange);
   HChargedHadron->SetFillColor(kCyan - 3);
   HNeutralHadron->SetFillColor(kGreen - 3);

   TCanvas C;

   TH2D HWorld("HWorld", ";#eta_{jet};p_{T} fraction", 100, -1.3, 1.3, 100, 0, 1);
   HWorld.SetStats(0);

   HWorld.Draw();

   HMuon->Draw("same bar hist");
   HElectron->Draw("same bar hist");
   HPhoton->Draw("same bar hist");
   HChargedHadron->Draw("same bar hist");
   HNeutralHadron->Draw("same bar hist");

   HWorld.Draw("axis same");

   TLegend Legend(0.2, 0.2, 0.3, 0.4);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(HMuon, "#mu", "f");
   Legend.AddEntry(HElectron, "e", "f");
   Legend.AddEntry(HPhoton, "#gamma", "f");
   Legend.AddEntry(HChargedHadron, "h^{#pm}", "f");
   Legend.AddEntry(HNeutralHadron, "h^{0}", "f");
   Legend.Draw();

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   File.Close();

   return 0;
}





