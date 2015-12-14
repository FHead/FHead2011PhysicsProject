#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "TH2D.h"
#include "TFile.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   bool SideBand = true;
   
   string SideBandString = "";
   if(SideBand == true)
      SideBandString = "SideBand";

   SetStyle();

   TFile F("Matrices.root");

   vector<string> SignalNames;
   vector<string> BackgroundNames;

   SignalNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_LQ200");
   SignalNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_LQ250");
   SignalNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_LQ350");
   SignalNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_LQ450");
   SignalNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_LQ550");

   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_TTbar");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_W");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_GammaVJet");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_DY_50");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_Znunu");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_VV");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_QCD50");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_QCD100");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_QCD250");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_QCD500");
   BackgroundNames.push_back("HNewMRNewR2Matrix" + SideBandString + "_QCD1000");

   PsFileHelper PsFile("MatrixComparison.ps");
   PsFile.AddTextPage("Compare yield matrix!!!");

   PsFile.AddTextPage("Signal samples!!!!");
   for(int i = 0; i < (int)SignalNames.size(); i++)
   {
      TH2D *H = (TH2D *)F.Get(SignalNames[i].c_str());
      H->SetMaximum(500);
      PsFile.AddPlot(H, "colz text30", false, true);

      TCanvas C("C", "C", 1024, 768);
      H->Draw("colz text30");
      C.SetLogz();
      C.SaveAs(Form("Plots/%s.png", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.C", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.eps", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.pdf", SignalNames[i].c_str()));
   }

   PsFile.AddTextPage("Background samples!!!!");
   for(int i = 0; i < (int)BackgroundNames.size(); i++)
   {
      TH2D *H = (TH2D *)F.Get(BackgroundNames[i].c_str());
      H->SetMaximum(500);
      PsFile.AddPlot(H, "colz text30", false, true);

      TCanvas C("C", "C", 1024, 768);
      H->Draw("colz text30");
      C.SetLogz();
      C.SaveAs(Form("Plots/%s.png", BackgroundNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.C", BackgroundNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.eps", BackgroundNames[i].c_str()));
      C.SaveAs(Form("Plots/%s.pdf", BackgroundNames[i].c_str()));
   }

   TH2D *HS = (TH2D *)F.Get(SignalNames[0].c_str());
   
   TH2D HAllBackground("HAllBackground",
      "MR (new) vs. R^{2} (new), All SM background;MR (new);R^{2} (new)",
      HS->GetNbinsX(), HS->GetXaxis()->GetBinLowEdge(1), HS->GetXaxis()->GetBinUpEdge(HS->GetNbinsX()),
      HS->GetNbinsY(), HS->GetYaxis()->GetBinLowEdge(1), HS->GetYaxis()->GetBinUpEdge(HS->GetNbinsY()));
   for(int i = 0; i < (int)BackgroundNames.size(); i++)
      HAllBackground.Add(((TH2D *)F.Get(BackgroundNames[i].c_str())));
   HAllBackground.SetStats(0);
   HAllBackground.SetMaximum(500);
   PsFile.AddPlot(HAllBackground, "colz text30", false, true);

   TCanvas C1("C1", "C1", 1024, 768);
   HAllBackground.Draw("colz text30");
   C1.SetLogz();
   C1.SaveAs("Plots/AllSMBackground.png");
   C1.SaveAs("Plots/AllSMBackground.C");
   C1.SaveAs("Plots/AllSMBackground.eps");
   C1.SaveAs("Plots/AllSMBackground.pdf");

   TH2D HQCDBackground("HQCDBackground",
      "MR (new) vs. R^{2} (new), QCD background;MR (new);R^{2} (new)",
      HS->GetNbinsX(), HS->GetXaxis()->GetBinLowEdge(1), HS->GetXaxis()->GetBinUpEdge(HS->GetNbinsX()),
      HS->GetNbinsY(), HS->GetYaxis()->GetBinLowEdge(1), HS->GetYaxis()->GetBinUpEdge(HS->GetNbinsY()));
   for(int i = 0; i < (int)BackgroundNames.size(); i++)
      if(BackgroundNames[i].find("QCD") != string::npos)
         HQCDBackground.Add(((TH2D *)F.Get(BackgroundNames[i].c_str())));
   HQCDBackground.SetStats(0);
   HQCDBackground.SetMaximum(500);
   PsFile.AddPlot(HQCDBackground, "colz text30", false, true);
   
   TCanvas C2("C2", "C2", 1024, 768);
   HQCDBackground.Draw("colz text30");
   C2.SetLogz();
   C2.SaveAs("Plots/QCDSMBackground.png");
   C2.SaveAs("Plots/QCDSMBackground.C");
   C2.SaveAs("Plots/QCDSMBackground.eps");
   C2.SaveAs("Plots/QCDSMBackground.pdf");
   
   TH2D HNonQCDBackground("HNonQCDBackground",
      "MR (new) vs. R^{2} (new), Non-QCD background;MR (new);R^{2} (new)",
      HS->GetNbinsX(), HS->GetXaxis()->GetBinLowEdge(1), HS->GetXaxis()->GetBinUpEdge(HS->GetNbinsX()),
      HS->GetNbinsY(), HS->GetYaxis()->GetBinLowEdge(1), HS->GetYaxis()->GetBinUpEdge(HS->GetNbinsY()));
   for(int i = 0; i < (int)BackgroundNames.size(); i++)
      if(BackgroundNames[i].find("QCD") == string::npos)
         HNonQCDBackground.Add(((TH2D *)F.Get(BackgroundNames[i].c_str())));
   HNonQCDBackground.SetStats(0);
   HNonQCDBackground.SetMaximum(500);
   PsFile.AddPlot(HNonQCDBackground, "colz text30", false, true);
   
   TCanvas C3("C3", "C3", 1024, 768);
   HNonQCDBackground.Draw("colz text30");
   C3.SetLogz();
   C3.SaveAs("Plots/NonQCDSMBackground.png");
   C3.SaveAs("Plots/NonQCDSMBackground.C");
   C3.SaveAs("Plots/NonQCDSMBackground.eps");
   C3.SaveAs("Plots/NonQCDSMBackground.pdf");

   TH2D HQCDOverSM("HQCDOverSM", "QCD / SM, MR (new) vs. R^{2} (new);MR (new);R^{2} (new)",
      HS->GetNbinsX(), HS->GetXaxis()->GetBinLowEdge(1), HS->GetXaxis()->GetBinUpEdge(HS->GetNbinsX()),
      HS->GetNbinsY(), HS->GetYaxis()->GetBinLowEdge(1), HS->GetYaxis()->GetBinUpEdge(HS->GetNbinsY()));
   for(int i = 1; i <= HQCDOverSM.GetNbinsX(); i++)
      for(int j = 1; j <= HQCDOverSM.GetNbinsY(); j++)
         if(HQCDBackground.GetBinContent(i, j) > 0 && HAllBackground.GetBinContent(i, j) > 0)
            HQCDOverSM.SetBinContent(i, j, HQCDBackground.GetBinContent(i, j) / HAllBackground.GetBinContent(i, j));
   HQCDOverSM.SetStats(0);
   HQCDOverSM.SetMaximum(1);
   PsFile.AddPlot(HQCDOverSM, "colz, text30", false, false);
   
   TCanvas C4("C4", "C4", 1024, 768);
   HQCDOverSM.Draw("colz text30");
   C4.SaveAs("Plots/QCDOverSM.png");
   C4.SaveAs("Plots/QCDOverSM.C");
   C4.SaveAs("Plots/QCDOverSM.eps");
   C4.SaveAs("Plots/QCDOverSM.pdf");

   PsFile.AddTextPage("Signal samples, S/S+B");
   for(int i = 0; i < (int)SignalNames.size(); i++)
   {
      TH2D *HSample = (TH2D *)F.Get(SignalNames[i].c_str());
      TH2D H(Form("SSB%d", i), Form("S/(S+B), %s", HSample->GetTitle()),
         HSample->GetNbinsX(), HSample->GetXaxis()->GetBinLowEdge(1),
         HSample->GetXaxis()->GetBinUpEdge(HSample->GetNbinsX()), HSample->GetNbinsY(),
         HSample->GetYaxis()->GetBinLowEdge(1), HSample->GetYaxis()->GetBinUpEdge(HSample->GetNbinsY()));
      TH2D HTotal = HAllBackground;
      HTotal.Add(&H);
      for(int j = 1; j <= H.GetNbinsX(); j++)
      {
         for(int k = 1; k <= H.GetNbinsY(); k++)
         {
            double Background = HAllBackground.GetBinContent(j, k);
            double Signal = HSample->GetBinContent(j, k);
            if(Signal > 0 && Background > 0)
               H.SetBinContent(j, k, Signal / (Signal + Background));
         }
      }
      H.SetMaximum(1);
      H.SetStats(0);
      PsFile.AddPlot(H, "colz text30", false, true);

      TCanvas C("C", "C", 1024, 768);
      H.Draw("colz text30");
      C.SaveAs(Form("Plots/%s_SSB.png", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s_SSB.C", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s_SSB.eps", SignalNames[i].c_str()));
      C.SaveAs(Form("Plots/%s_SSB.pdf", SignalNames[i].c_str()));
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}



