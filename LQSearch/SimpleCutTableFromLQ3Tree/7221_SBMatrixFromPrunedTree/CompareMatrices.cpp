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
   SetStyle();

   TFile F("Matrices.root");

   vector<string> SignalNames;
   vector<string> BackgroundNames;

   SignalNames.push_back("HNewMRNewR2Matrix_LQ200");
   SignalNames.push_back("HNewMRNewR2Matrix_LQ250");
   SignalNames.push_back("HNewMRNewR2Matrix_LQ350");
   SignalNames.push_back("HNewMRNewR2Matrix_LQ450");
   SignalNames.push_back("HNewMRNewR2Matrix_LQ550");

   BackgroundNames.push_back("HNewMRNewR2Matrix_TTbar");
   BackgroundNames.push_back("HNewMRNewR2Matrix_W");
   BackgroundNames.push_back("HNewMRNewR2Matrix_GammaVJet");
   BackgroundNames.push_back("HNewMRNewR2Matrix_DY_50");
   BackgroundNames.push_back("HNewMRNewR2Matrix_Znunu");
   BackgroundNames.push_back("HNewMRNewR2Matrix_VV");
   BackgroundNames.push_back("HNewMRNewR2Matrix_QCD50");
   BackgroundNames.push_back("HNewMRNewR2Matrix_QCD100");
   BackgroundNames.push_back("HNewMRNewR2Matrix_QCD250");
   BackgroundNames.push_back("HNewMRNewR2Matrix_QCD500");
   BackgroundNames.push_back("HNewMRNewR2Matrix_QCD1000");

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
   
   TH2D HAllBackground("HAllBackground",
      "MR (new) vs. R^{2} (new), All SM background;MR (new);R^{2} (new)", 20, 0, 1000, 10, 0, 0.5);
   for(int i = 0; i < (int)BackgroundNames.size(); i++)
      HAllBackground.Add(((TH2D *)F.Get(BackgroundNames[i].c_str())));
   HAllBackground.SetStats(0);
   HAllBackground.SetMaximum(500);
   PsFile.AddPlot(HAllBackground, "colz text30", false, true);

   TCanvas C("C", "C", 1024, 768);
   HAllBackground.Draw("colz text30");
   C.SetLogz();
   C.SaveAs("Plots/AllSMBackground.png");
   C.SaveAs("Plots/AllSMBackground.C");
   C.SaveAs("Plots/AllSMBackground.eps");
   C.SaveAs("Plots/AllSMBackground.pdf");

   TH2D HQCDBackground("HQCDBackground",
      "MR (new) vs. R^{2} (new), QCD background;MR (new);R^{2} (new)", 20, 0, 1000, 10, 0, 0.5);
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
      "MR (new) vs. R^{2} (new), Non-QCD background;MR (new);R^{2} (new)", 20, 0, 1000, 10, 0, 0.5);
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

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}



