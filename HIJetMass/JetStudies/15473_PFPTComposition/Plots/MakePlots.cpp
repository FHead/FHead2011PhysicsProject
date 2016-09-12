#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.020);

   SetThesisStyle();

   string InputFile = argv[1];
   string OutputBase = argv[2];

   TFile File(InputFile.c_str());

   int CentralityBin[6] = {0, 10, 30, 50, 80, 100};

   for(int i = 0; i < 5; i++)
   {
      TH1D *HMuonEta          = (TH1D *)File.Get(Form("HMuonEta%d", CentralityBin[i]));
      TH1D *HElectronEta      = (TH1D *)File.Get(Form("HElectronEta%d", CentralityBin[i]));
      TH1D *HPhotonEta        = (TH1D *)File.Get(Form("HPhotonEta%d", CentralityBin[i]));
      TH1D *HChargedHadronEta = (TH1D *)File.Get(Form("HChargedHadronEta%d", CentralityBin[i]));
      TH1D *HNeutralHadronEta = (TH1D *)File.Get(Form("HNeutralHadronEta%d", CentralityBin[i]));
      TH1D *HMuonPT           = (TH1D *)File.Get(Form("HMuonPT%d", CentralityBin[i]));
      TH1D *HElectronPT       = (TH1D *)File.Get(Form("HElectronPT%d", CentralityBin[i]));
      TH1D *HPhotonPT         = (TH1D *)File.Get(Form("HPhotonPT%d", CentralityBin[i]));
      TH1D *HChargedHadronPT  = (TH1D *)File.Get(Form("HChargedHadronPT%d", CentralityBin[i]));
      TH1D *HNeutralHadronPT  = (TH1D *)File.Get(Form("HNeutralHadronPT%d", CentralityBin[i]));

      TH1D *HTotalEta = (TH1D *)HMuonEta->Clone("HTotalEta");
      HTotalEta->Add(HElectronEta);
      HTotalEta->Add(HPhotonEta);
      HTotalEta->Add(HChargedHadronEta);
      HTotalEta->Add(HNeutralHadronEta);
      TH1D *HTotalPT = (TH1D *)HMuonPT->Clone("HTotalPT");
      HTotalPT->Add(HElectronPT);
      HTotalPT->Add(HPhotonPT);
      HTotalPT->Add(HChargedHadronPT);
      HTotalPT->Add(HNeutralHadronPT);

      HMuonEta->Divide(HTotalEta);
      HElectronEta->Divide(HTotalEta);
      HPhotonEta->Divide(HTotalEta);
      HChargedHadronEta->Divide(HTotalEta);
      HNeutralHadronEta->Divide(HTotalEta);
      HMuonPT->Divide(HTotalPT);
      HElectronPT->Divide(HTotalPT);
      HPhotonPT->Divide(HTotalPT);
      HChargedHadronPT->Divide(HTotalPT);
      HNeutralHadronPT->Divide(HTotalPT);

      HChargedHadronEta->Add(HNeutralHadronEta);
      HPhotonEta->Add(HChargedHadronEta);
      HElectronEta->Add(HPhotonEta);
      HMuonEta->Add(HElectronEta);
      HChargedHadronPT->Add(HNeutralHadronPT);
      HPhotonPT->Add(HChargedHadronPT);
      HElectronPT->Add(HPhotonPT);
      HMuonPT->Add(HElectronPT);

      HMuonEta->SetFillColor(kRed - 3);
      HElectronEta->SetFillColor(kBlue);
      HPhotonEta->SetFillColor(kOrange);
      HChargedHadronEta->SetFillColor(kCyan - 3);
      HNeutralHadronEta->SetFillColor(kGreen - 3);
      HMuonPT->SetFillColor(kRed - 3);
      HElectronPT->SetFillColor(kBlue);
      HPhotonPT->SetFillColor(kOrange);
      HChargedHadronPT->SetFillColor(kCyan - 3);
      HNeutralHadronPT->SetFillColor(kGreen - 3);

      TCanvas C;

      TH2D HWorldEta(Form("HWorldEta%d", i), ";#eta_{jet};p_{T} fraction", 100, -1.3, 1.3, 100, 0, 1);
      HWorldEta.SetStats(0);

      HWorldEta.Draw();

      HMuonEta->Draw("same bar hist");
      HElectronEta->Draw("same bar hist");
      HPhotonEta->Draw("same bar hist");
      HChargedHadronEta->Draw("same bar hist");
      HNeutralHadronEta->Draw("same bar hist");

      HWorldEta.Draw("axis same");

      TLegend LegendEta(0.20, 0.25, 0.30, 0.45);
      LegendEta.SetBorderSize(0);
      LegendEta.SetTextFont(42);
      LegendEta.SetTextSize(0.035);
      LegendEta.AddEntry(HMuonEta, "#mu", "f");
      LegendEta.AddEntry(HElectronEta, "e", "f");
      LegendEta.AddEntry(HPhotonEta, "#gamma", "f");
      LegendEta.AddEntry(HChargedHadronEta, "h^{#pm}", "f");
      LegendEta.AddEntry(HNeutralHadronEta, "h^{0}", "f");
      LegendEta.Draw();

      Latex.DrawLatex(0.10, 0.92, OutputBase.c_str());

      C.SaveAs(Form("%sEta_%d_%d.png", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sEta_%d_%d.C",   OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sEta_%d_%d.eps", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sEta_%d_%d.pdf", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      
      TH2D HWorldPT(Form("HWorldPT%d", i), ";p_{T}^{jet};p_{T} fraction", 100, 100, 300, 100, 0, 1);
      HWorldPT.SetStats(0);

      HWorldPT.Draw();

      HMuonPT->Draw("same bar hist");
      HElectronPT->Draw("same bar hist");
      HPhotonPT->Draw("same bar hist");
      HChargedHadronPT->Draw("same bar hist");
      HNeutralHadronPT->Draw("same bar hist");

      HWorldPT.Draw("axis same");

      TLegend LegendPT(0.20, 0.25, 0.30, 0.45);
      LegendPT.SetBorderSize(0);
      LegendPT.SetTextFont(42);
      LegendPT.SetTextSize(0.035);
      LegendPT.AddEntry(HMuonPT, "#mu", "f");
      LegendPT.AddEntry(HElectronPT, "e", "f");
      LegendPT.AddEntry(HPhotonPT, "#gamma", "f");
      LegendPT.AddEntry(HChargedHadronPT, "h^{#pm}", "f");
      LegendPT.AddEntry(HNeutralHadronPT, "h^{0}", "f");
      LegendPT.Draw();
      
      Latex.DrawLatex(0.10, 0.92, OutputBase.c_str());

      C.SaveAs(Form("%sPT_%d_%d.png", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sPT_%d_%d.C",   OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sPT_%d_%d.eps", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
      C.SaveAs(Form("%sPT_%d_%d.pdf", OutputBase.c_str(), CentralityBin[i], CentralityBin[i+1]));
   }

   File.Close();

   return 0;
}






