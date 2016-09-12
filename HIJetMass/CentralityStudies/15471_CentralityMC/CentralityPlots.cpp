#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TProfile.h"

#include "BasicUtilities.h"

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string TriggerString = "HLT_HIPuAK4CaloJet100_Eta5p1_v1";

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);

   TFile InputFile(Input.c_str());

   TTree *Tree = (TTree *)InputFile.Get("hiEvtAnalyzer/HiTree");
   TTree *RhoTree = (TTree *)InputFile.Get("hiFJRhoAnalyzer/t");
   TTree *HLTTree = (TTree *)InputFile.Get("hltanalysis/HltTree");
   TTree *SkimTree = (TTree *)InputFile.Get("skimanalysis/HltTree");

   TFile OutputFile(Output.c_str(), "RECREATE");
   
   TH1D HHFEnergy("HHFEnergy", ";Energy (GeV)", 1000, 0, 9000);
   TH1D HCentrality("HCentrality", ";Centrality", 200, 0, 1);
   TH1D HBinCentrality("HBinCentrality", ";Centrality", 200, 0, 200);
   TH1D HRho("HRho", ";Rho (GeV)", 1000, 0, 350);
   TH1D HRhoM("HRhoM", ";RhoM (GeV)", 1000, 0, 1.5);
   TProfile PRhoCentrality("PRhoCentrality", ";rho;centrality", 100, 0.00, 1.00);
   TProfile PRhoMCentrality("PRhoMCentrality", ";rhom;centrality", 100, 0.00, 1.00);
   TProfile PRhoCentralityShifted2("PRhoCentralityShifted2", ";rho;centrality", 100, 0.00, 1.00);
   TProfile PRhoMCentralityShifted2("PRhoMCentralityShifted2", ";rhom;centrality", 100, 0.00, 1.00);

   vector<TH1D *> HHFEnergyBin;
   vector<TH1D *> HCentralityBin;
   vector<TH1D *> HRhoBin;
   vector<TH1D *> HRhoMBin;

   for(int i = 0; i < 10; i++)
   {
      int Min = i * 10;
      int Max = i * 10 + 10;
      HHFEnergyBin.push_back(new TH1D(Form("HHFEnergy%d", i), Form("%d%%-%d%%;Energy (GeV)", Min, Max), 1000, 0, 9000));
      HCentralityBin.push_back(new TH1D(Form("HCentrality%d", i), Form("%d%%-%d%%;Centrality" , Min, Max), 200, 0, 1));
      HRhoBin.push_back(new TH1D(Form("HRho%d", i), Form("%d%%-%d%%;Rho (GeV)" , Min, Max), 1000, 0, 350));
      HRhoMBin.push_back(new TH1D(Form("HRhoM%d", i), Form("%d%%-%d%%;RhoM (GeV)" , Min, Max), 1000, 0, 1.5));
   }

   float hiHF;
   int hiBin;
   unsigned int run;
   Tree->SetBranchAddress("hiHF", &hiHF);
   Tree->SetBranchAddress("hiBin", &hiBin);
   Tree->SetBranchAddress("run", &run);
   
   int HBHENoise;
   int HBHENoiseRun2Loose;
   int PVFilter;
   int ClusterCompatibilityFilter;
   int HFCoincidenceFilter;
   int CollisionEventSelection;
   SkimTree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoise);
   SkimTree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseRun2Loose);
   SkimTree->SetBranchAddress("pprimaryVertexFilter", &PVFilter);
   SkimTree->SetBranchAddress("pclusterCompatibilityFilter", &ClusterCompatibilityFilter);
   SkimTree->SetBranchAddress("phfCoincFilter3", &HFCoincidenceFilter);
   SkimTree->SetBranchAddress("pcollisionEventSelection", &CollisionEventSelection);

   vector<double> *EtaMax = NULL;
   vector<double> *Rho = NULL;
   vector<double> *RhoM = NULL;
   
   RhoTree->SetBranchAddress("etaMax", &EtaMax);
   RhoTree->SetBranchAddress("rho", &Rho);
   RhoTree->SetBranchAddress("rhom", &RhoM);

   int Decision;
   if(IsData == true)
      HLTTree->SetBranchAddress(TriggerString.c_str(), &Decision);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);
      RhoTree->GetEntry(iEntry);
      SkimTree->GetEntry(iEntry);

      if(IsData == true)
      {
         HLTTree->GetEntry(iEntry);
         // if(Decision == false)
         //    continue;
         
         if(HBHENoise == 0)
            continue;
         if(HBHENoiseRun2Loose == 0)
            continue;
         if(PVFilter == 0)
            continue;
         if(ClusterCompatibilityFilter == 0)
            continue;
         if(HFCoincidenceFilter == 0)
            continue;
         if(CollisionEventSelection == 0)
            continue;
      }

      HHFEnergy.Fill(hiHF);
      HCentrality.Fill(GetCentrality(hiBin));
      HBinCentrality.Fill(hiBin);
      HRho.Fill(GetRho(EtaMax, Rho, 0));
      HRhoM.Fill(GetRho(EtaMax, RhoM, 0));
      PRhoCentrality.Fill(GetCentrality(hiBin), GetRho(EtaMax, Rho, 0));
      PRhoMCentrality.Fill(GetCentrality(hiBin), GetRho(EtaMax, RhoM, 0));
      PRhoCentralityShifted2.Fill(GetCentrality(hiBin) - 0.02, GetRho(EtaMax, Rho, 0));
      PRhoMCentralityShifted2.Fill(GetCentrality(hiBin) - 0.02, GetRho(EtaMax, RhoM, 0));

      int Bin = (int)(GetCentrality(hiBin) * 10);
      if(Bin >= 0 && Bin <= 10)
      {
         if(Bin == 10)
            Bin = 9;
         HHFEnergyBin[Bin]->Fill(hiHF);
         HCentralityBin[Bin]->Fill(GetCentrality(hiBin));
         HRhoBin[Bin]->Fill(GetRho(EtaMax, Rho, 0));
         HRhoMBin[Bin]->Fill(GetRho(EtaMax, RhoM, 0));
      }
   }

   HHFEnergy.Write();
   HCentrality.Write();
   HBinCentrality.Write();
   HRho.Write();
   HRhoM.Write();
   PRhoCentrality.Write();
   PRhoMCentrality.Write();
   PRhoCentralityShifted2.Write();
   PRhoMCentralityShifted2.Write();

   for(int i = 0; i < 10; i++)
   {
      HHFEnergyBin[i]->Write();
      HCentralityBin[i]->Write();
      HRhoBin[i]->Write();
      HRhoMBin[i]->Write();
   }
   
   for(int i = 0; i < 10; i++)
   {
      delete HHFEnergyBin[i];
      delete HCentralityBin[i];
      delete HRhoBin[i];
      delete HRhoMBin[i];
   }

   OutputFile.Close();

   InputFile.Close();
}







