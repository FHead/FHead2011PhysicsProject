#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

int main(int argc, char *argv[]);
double ToDouble(char *meow);

int main(int argc, char *argv[])
{
   // 5 fields: sample, distribution, selection, btagging, step

   if(argc < 4)
   {
      cerr << "Usage " << argv[0] << " Input CrossSection Output" << endl;
      return -1;
   }

   string InputFileName = argv[1];
   double CrossSection = ToDouble(argv[2]);
   string OutputFileName = argv[3];

   TFile InputFile(InputFileName.c_str());
   double TotalWeight = ((TH1D *)InputFile.Get("HPileUpCount"))->Integral();
   InputFile.Close();
   
   TChain Tree("ReducedTree", "ReducedTree");
   Tree.AddFile(InputFileName.c_str());

   double MR, R;
   int LooseBTagCount, MediumBTagCount, TightBTagCount;
   int GoodMuonLoose, GoodElectronLoose;
   int GoodMuonTight, GoodElectronTight;
   double MuonPT, ElectronPT, JetPT;
   int PileUpCount;

   Tree.SetBranchAddress("MR", &MR);
   Tree.SetBranchAddress("R", &R);
   Tree.SetBranchAddress("LooseBTagCount", &LooseBTagCount);
   Tree.SetBranchAddress("MediumBTagCount", &MediumBTagCount);
   Tree.SetBranchAddress("TightBTagCount", &TightBTagCount);
   Tree.SetBranchAddress("PileupCount", &PileUpCount);
   Tree.SetBranchAddress("GoodMuonCountTight", &GoodMuonTight);
   Tree.SetBranchAddress("GoodMuonCountLoose", &GoodMuonLoose);
   Tree.SetBranchAddress("GoodElectronCountTight", &GoodElectronTight);
   Tree.SetBranchAddress("GoodElectronCountLoose", &GoodElectronLoose);
   Tree.SetBranchAddress("Jet1PT", &JetPT);
   Tree.SetBranchAddress("MuonPT", &MuonPT);
   Tree.SetBranchAddress("ElectronPT", &ElectronPT);

   TFile F(OutputFileName.c_str(), "RECREATE");

   string Selection[5] = {"Had", "LooseMuon", "TightMuon", "LooseElectron", "TightElectron"};
   string Tagging[8] = {"All", "NoTag", "OneLoose", "TwoLoose", "OneMedium", "TwoMedium", "OneTight", "TwoTight"};
   string Step[6] = {"Jet60", "Leptons", "BTagging", "MR400", "R2020", "R2025"};

   TH1D *HMR[5][8][6] = {{{NULL}}};
   TH1D *HR2[5][8][6] = {{{NULL}}};
   TH1D *HJetPT[5][8][6] = {{{NULL}}};
   TH1D *HMuonPT[5][8][6] = {{{NULL}}};
   TH1D *HElectronPT[5][8][6] = {{{NULL}}};

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         for(int k = 0; k < 6; k++)
         {
            HMR[i][j][k] = new TH1D(Form("HMR_%s_%s_%s", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               Form("M_{R}, %s, %s, %s;M_{R}", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               30, 0, 1500);
            HR2[i][j][k] = new TH1D(Form("HR2_%s_%s_%s", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               Form("R^{2}, %s, %s, %s;R^{2}", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               30, 0, 1.5);
            HJetPT[i][j][k] = new TH1D(Form("HJetPT_%s_%s_%s", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               Form("JetPT, %s, %s, %s;PT", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               30, 0, 1500);
            HMuonPT[i][j][k] = new TH1D(Form("HMuonPT_%s_%s_%s", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               Form("MuonPT, %s, %s, %s;PT", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               30, 0, 1500);
            HElectronPT[i][j][k] = new TH1D(Form("HElectronPT_%s_%s_%s", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               Form("ElectronPT, %s, %s, %s;PT", Selection[i].c_str(), Tagging[j].c_str(), Step[k].c_str()),
               30, 0, 1500);
         }
      }
   }

   int Weight = 1;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      for(int i = 0; i < 5; i++)
      {
         for(int j = 0; j < 8; j++)
         {
            HMR[i][j][0]->Fill(MR, Weight);
            HR2[i][j][0]->Fill(R * R, Weight);
            HJetPT[i][j][0]->Fill(JetPT, Weight);
            HMuonPT[i][j][0]->Fill(MuonPT, Weight);
            HElectronPT[i][j][0]->Fill(ElectronPT, Weight);
            
            if(i == 0 && (GoodMuonLoose > 0 || GoodElectronLoose > 0))   continue;
            if(i == 1 && GoodMuonLoose != 1)                             continue;
            if(i == 2 && GoodMuonTight != 1)                             continue;
            if(i == 3 && GoodElectronLoose != 1)                         continue;
            if(i == 4 && GoodElectronTight != 1)                         continue;

            HMR[i][j][1]->Fill(MR, Weight);
            HR2[i][j][1]->Fill(R * R, Weight);
            HJetPT[i][j][1]->Fill(JetPT, Weight);
            if(i == 1 || i == 2)
               HMuonPT[i][j][1]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4)
               HElectronPT[i][j][1]->Fill(ElectronPT, Weight);

            if(j == 1 && LooseBTagCount > 0)     continue;
            if(j == 2 && LooseBTagCount != 1)    continue;
            if(j == 3 && LooseBTagCount < 2)     continue;
            if(j == 4 && MediumBTagCount != 1)   continue;
            if(j == 5 && MediumBTagCount < 2)    continue;
            if(j == 6 && TightBTagCount != 1)    continue;
            if(j == 7 && TightBTagCount < 2)     continue;
            
            HMR[i][j][2]->Fill(MR, Weight);
            HR2[i][j][2]->Fill(R * R, Weight);
            HJetPT[i][j][2]->Fill(JetPT, Weight);
            if(i == 1 || i == 2)
               HMuonPT[i][j][2]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4)
               HElectronPT[i][j][2]->Fill(ElectronPT, Weight);

            if(MR < 400)   continue;

            HMR[i][j][3]->Fill(MR, Weight);
            HR2[i][j][3]->Fill(R * R, Weight);
            HJetPT[i][j][3]->Fill(JetPT, Weight);
            if(i == 1 || i == 2)
               HMuonPT[i][j][3]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4)
               HElectronPT[i][j][3]->Fill(ElectronPT, Weight);

            if(R * R < 0.20)   continue;

            HMR[i][j][4]->Fill(MR, Weight);
            HR2[i][j][4]->Fill(R * R, Weight);
            HJetPT[i][j][4]->Fill(JetPT, Weight);
            if(i == 1 || i == 2)
               HMuonPT[i][j][4]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4)
               HElectronPT[i][j][4]->Fill(ElectronPT, Weight);

            if(R * R < 0.25)   continue;

            HMR[i][j][5]->Fill(MR, Weight);
            HR2[i][j][5]->Fill(R * R, Weight);
            HJetPT[i][j][5]->Fill(JetPT, Weight);
            if(i == 1 || i == 2)
               HMuonPT[i][j][5]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4)
               HElectronPT[i][j][5]->Fill(ElectronPT, Weight);
         }
      }
   }

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         for(int k = 0; k < 6; k++)
         {
            if(CrossSection > 0)
            {
               HMR[i][j][k]->Scale(CrossSection * 1000 / TotalWeight);
               HR2[i][j][k]->Scale(CrossSection * 1000 / TotalWeight);
               HJetPT[i][j][k]->Scale(CrossSection * 1000 / TotalWeight);
               HMuonPT[i][j][k]->Scale(CrossSection * 1000 / TotalWeight);
               HElectronPT[i][j][k]->Scale(CrossSection * 1000 / TotalWeight);
            }
            
            HMR[i][j][k]->Write();
            HR2[i][j][k]->Write();
            HJetPT[i][j][k]->Write();
            HMuonPT[i][j][k]->Write();
            HElectronPT[i][j][k]->Write();
            
            delete HMR[i][j][k];
            delete HR2[i][j][k];
            delete HJetPT[i][j][k];
            delete HMuonPT[i][j][k];
            delete HElectronPT[i][j][k];
         }
      }
   }

   F.Close();

   return 0;
}

double ToDouble(char *meow)
{
   stringstream str(meow);

   double temp = -1;
   str >> temp;

   return temp;
}



