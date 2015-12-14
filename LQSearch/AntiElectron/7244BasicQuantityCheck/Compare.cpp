#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

int main(int argc, char *argv);
void CompareHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string Name);

int main(int argc, char *argv)
{
   vector<TFile *> Files;
   Files.push_back(new TFile("WJet.root"));
   Files.push_back(new TFile("QCDAll.root"));
   Files.push_back(new TFile("TTbar.root"));
   Files.push_back(new TFile("Z.root"));
   Files.push_back(new TFile("Znunu.root"));
   Files.push_back(new TFile("LQ200.root"));
   Files.push_back(new TFile("LQ250.root"));

   vector<string> Labels;
   Labels.push_back("WJet");
   Labels.push_back("MultiJet");
   Labels.push_back("TTbar");
   Labels.push_back("Z");
   Labels.push_back("Znunu");
   Labels.push_back("LQ200");
   Labels.push_back("LQ250");

   PsFileHelper PsFile("Comparison.ps");
   PsFile.AddTextPage("Compare between different samples");

   CompareHistogram(PsFile, Files, Labels, "HNPU");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronCount");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronPT");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronEta");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronPhi");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronSigmaIEtaIEta");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronSigmaIEtaIEtaBarrel");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronSigmaIEtaIEtaEndcap");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronIsolation");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronIsolationBarrel");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronIsolationEndcap");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronRelativeIsolation");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronRelativeIsolationBarrel");
   CompareHistogram(PsFile, Files, Labels, "HAllElectronRelativeIsolationEndcap");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaCount");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaBarrelCount");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaEndcapCount");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaCountLL");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaBarrelCountLL");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaEndcapCountLL");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLLR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaLR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiSigmaIEtaIEtaR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiElectronR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiIsolationR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew_R2New005");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew_R2New010");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew_R2New015");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew_R2New020");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingMRNew_R2New025");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HAntiNothingR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "");
   CompareHistogram(PsFile, Files, Labels, "");
   CompareHistogram(PsFile, Files, Labels, "");
   CompareHistogram(PsFile, Files, Labels, "");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
      Files[i] = NULL;
   }

   return 0;
}

void CompareHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string Name)
{
   if(Name == "")
      return;

   vector<TH1D *> Histograms;
   for(int i = 0; i < (int)Files.size(); i++)
      Histograms.push_back((TH1D *)Files[i]->Get(Name.c_str()));

   double Maximum = 0;

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Histograms[i]->SetLineColor(i + 1);
      Histograms[i]->SetLineWidth(2);
      Histograms[i]->SetStats(0);
      if(Histograms[i]->GetMaximum() > Maximum)
         Maximum = Histograms[i]->GetMaximum();
   }
   
   Histograms[0]->SetMaximum(Maximum * 5);
   Histograms[0]->SetMinimum(0.2);

   TLegend legend(0.7, 0.85, 0.9, 0.45);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   for(int i = 0; i < (int)Files.size(); i++)
      legend.AddEntry(Histograms[i], Labels[i].c_str(), "l");

   TCanvas Canvas;

   Histograms[0]->Draw();
   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->Draw("same");

   legend.Draw();

   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);

   TCanvas Canvas2("C", "C", 1024, 1024);
   
   Histograms[0]->Draw();
   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->Draw("same");

   legend.Draw();

   Canvas2.SetLogy();
   Canvas2.SaveAs(Form("Plots/%s.png", Name.c_str()));
   Canvas2.SaveAs(Form("Plots/%s.C", Name.c_str()));
   Canvas2.SaveAs(Form("Plots/%s.eps", Name.c_str()));
   Canvas2.SaveAs(Form("Plots/%s.pdf", Name.c_str()));
}



