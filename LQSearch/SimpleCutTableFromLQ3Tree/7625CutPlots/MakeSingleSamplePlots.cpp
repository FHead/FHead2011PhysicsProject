#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

int main(int argc, char *argv[])
{
   string InputFile = "Histograms/TTJets_TuneZ2_7TeV-madgraph-tauola_HIGHSTAT_All.root";
   string OutputBase = "IndividualPlots/TTbar";
   double Luminosity = -1;

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile Tag" << endl;
      return -1;
   }

   InputFile = argv[1];
   OutputBase = string("IndividualPlots/") + argv[2];

   bool Data = false;
   if(OutputBase.find("Data") != string::npos)
      Data = true;

   TFile File(InputFile.c_str());

   string Type[5] = {"HMR", "HR2", "HJetPT", "HMuonPT", "HElectronPT"};
   string Selection[5] = {"Had", "LooseMuon", "TightMuon", "LooseElectron", "TightElectron"};
   string Tagging[8] = {"All", "NoTag", "OneLoose", "TwoLoose", "OneMedium", "TwoMedium", "OneTight", "TwoTight"};
   string Step[6] = {"Jet60", "Leptons", "BTagging", "MR400", "R2020", "R2025"};

   for(int i = 0; i < 5; i++)   // type
   {
      for(int j = 0; j < 5; j++)   // selection
      {
         if(Data == false)
         {
            if(j == 0)   Luminosity = 4.625;
            if(j == 1)   Luminosity = 2.826;
            if(j == 2)   Luminosity = 2.826;
            if(j == 3)   Luminosity = 4.700;
            if(j == 4)   Luminosity = 4.700;
         }
         else
            Luminosity = 1.000;   // do scale anything

         for(int k = 0; k < 8; k++)   // tagging
         {
            vector<TH1D *> Histograms;

            for(int l = 0; l < 6; l++)
               Histograms.push_back((TH1D *)File.Get(Form("%s_%s_%s_%s",
                  Type[i].c_str(), Selection[j].c_str(), Tagging[k].c_str(), Step[l].c_str())));

            for(int l = 0; l < 6; l++)   // steps
            {
               TCanvas C("C", "C", 800, 800);

               Histograms[l]->Scale(Luminosity);
               Histograms[l]->SetMinimum(0.50);
               Histograms[l]->SetStats(0);
               Histograms[l]->Draw();

               C.SetLogy();
               C.SaveAs((OutputBase + "_" + Type[i] + "_" + Selection[j] + "_"
                  + Tagging[k] + "_" + Step[l] + ".png").c_str());
            }

            TCanvas C("C", "C", 800, 800);

            TLegend Legend(0.65, 0.85, 0.85, 0.55);
            Legend.SetFillStyle(0);
            Legend.SetBorderSize(0);
            Legend.SetTextFont(42);

            for(int l = 0; l < 6; l++)
            {
               Histograms[l]->SetLineColor(l + 1);

               if(l == 0)
               {
                  Histograms[l]->SetTitle(Form("Distribution after each cut for %s", Type[i].c_str()));
                  Histograms[l]->Draw();
               }
               else
                  Histograms[l]->Draw("same");

               Legend.AddEntry(Histograms[l], Step[l].c_str(), "l");
            }

            Legend.Draw();

            C.SetLogy();
            C.SaveAs((OutputBase + "_" + Type[i] + "_" + Selection[j] + "_" + Tagging[k] + "_AllSteps.png").c_str());
         }
      }
   }

   File.Close();

   return 0;
}






