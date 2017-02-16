#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"

#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"

#include "LeptonResponse.h"

int main()
{
   PsFileHelper PsFile("LeptonSmearValidation.ps");
   PsFile.AddTextPage("Yay");

   double PT[15] = {6, 7.5, 8.5, 9.5, 11, 13.5, 15, 17, 19, 22.5, 27.5, 32.5, 37.5, 45, 55};
   double Eta[17] = {0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3221, 1.4999, 1.683, 1.9, 2.05, 2.15, 2.25, 2.35, 2.45, 2.55, 2.65};

   for(int i = 0; i < 15; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         FourVector Vector;
         Vector.SetPtEtaPhi(PT[i], Eta[j], 0);

         TH1D HElectron("HElectron", Form("Electron, PT %f Eta %f PzP %f", PT[i], Eta[j], Vector[3]/Vector.GetP()), 1000, -0.25, 0.25);
         TH1D HElectronWide("HElectronWide", Form("Electron (wide), PT %f Eta %f PzP %f", PT[i], Eta[j], Vector[3]/Vector.GetP()), 1000, -0.25, 0.25);
         TH1D HMuon("HMuon", Form("Muon, PT %f Eta %f PzP %f", PT[i], Eta[j], Vector[3]/Vector.GetP()), 1000, -0.25, 0.25);

         HElectron.SetStats(0);
         HMuon.SetStats(0);

         for(int k = 1; k < HElectron.GetNbinsX(); k++)
         {
            double Value = HElectron.GetXaxis()->GetBinCenter(k);

            HElectron.SetBinContent(k, SmearElectron(Vector, Value));
            HElectronWide.SetBinContent(k, SmearElectronWide(Vector, Value));
            HMuon.SetBinContent(k, SmearMuon(Vector, Value));
         }

         cout << i << " " << j << " " << HElectron.Integral() << " " << HMuon.Integral() << endl;

         cout << PT[i] << " " << Eta[j] << endl;
         cout << HElectron.GetMaximum() / HElectron.GetBinContent(HElectron.FindBin(0)) << endl;
         cout << HMuon.GetMaximum() / HMuon.GetBinContent(HMuon.FindBin(0)) << endl;

         // PsFile.AddPlot(HElectron);
         // PsFile.AddPlot(HElectronWide);
         PsFile.AddPlot(HMuon);
      }
   }

   TH2D HMuonEfficiency("HMuonEfficiency", "Muon efficiency;PT;Eta", 100, 0, 60, 100, 0, 2.6);
   TH2D HElectronEfficiency("HElectronEfficiency", "Electron efficiency;PT;Eta", 100, 0, 60, 100, 0, 2.6);

   for(int i = 1; i <= 100; i++)
   {
      for(int j = 1; j <= 100; j++)
      {
         double PT = HMuonEfficiency.GetXaxis()->GetBinCenter(i);
         double Eta = HMuonEfficiency.GetYaxis()->GetBinCenter(j);

         FourVector Momentum;
         Momentum.SetPtEtaPhi(PT, Eta, 0);

         HMuonEfficiency.SetBinContent(i, j, GetMuonEfficiencyPtEta8TeV(PT, Momentum[3] / Momentum.GetP(), 0));
         HElectronEfficiency.SetBinContent(i, j, GetElectronEfficiencyPtEta8TeV(PT, Momentum[3] / Momentum.GetP(), 0));
      }
   }

   PsFile.AddPlot(HMuonEfficiency, "colz");
   PsFile.AddPlot(HElectronEfficiency, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




