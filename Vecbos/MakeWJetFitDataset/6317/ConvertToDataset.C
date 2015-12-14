#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
using namespace RooFit;

void ConvertToDataset(string InputFile, string OutputFile, double CrossSection = 1)
{
   TFile F(InputFile.c_str());

   TTree *Tree = (TTree *)F.Get("WJetTree");

   double btag;            Tree->SetBranchAddress("HighestBTag", &btag);
   double btag_2;          Tree->SetBranchAddress("SecondHighestBTag", &btag_2);
   double CosThb;          Tree->SetBranchAddress("ChrisKinematicTopVariable", &CosThb);
   double Dxy;             Tree->SetBranchAddress("Muon1Dxy", &Dxy);
   double Dz;              Tree->SetBranchAddress("Muon1Dz", &Dz);
   double Event;           Tree->SetBranchAddress("EventNumber", &Event);
   double firstJet_pt;     Tree->SetBranchAddress("PFJet1PT", &firstJet_pt);
   bool HasBHadron;        Tree->SetBranchAddress("HasB", &HasBHadron);
   int Index;              // ?
   double Iso_pf_abs = 999;
   double Iso_pf_relmt = 999;
   double Iso_pf_relpt = 999;
   double Iso_tk_abs;      Tree->SetBranchAddress("Muon1Isolation", &Iso_tk_abs);
   double Iso_tk_relmt;    Tree->SetBranchAddress("Muon1IsolationOverMT", &Iso_tk_relmt);
   double Iso_tk_relpt;    Tree->SetBranchAddress("Muon1RelativeIsolation", &Iso_tk_relpt);
   double Lumi;            Tree->SetBranchAddress("LumiSection", &Lumi);
   double MR;              Tree->SetBranchAddress("MR", &MR);
   double MRp;             Tree->SetBranchAddress("MRPrime", &MRp);
   double Met_calo;        Tree->SetBranchAddress("CaloMET", &Met_calo);
   double Met_pf;          Tree->SetBranchAddress("PFMET", &Met_pf);
   double Met_tc;          Tree->SetBranchAddress("TCMET", &Met_tc);
   double Mt_calo;         Tree->SetBranchAddress("CaloMT", &Mt_calo);
   double Mt_pf;           Tree->SetBranchAddress("PFMT", &Mt_pf);
   double Mt_tc;           Tree->SetBranchAddress("TCMT", &Mt_tc);
   double muPt;            Tree->SetBranchAddress("Muon1PT", &muPt);
   double mu2Pt = 999;
   int Npf_10;          Tree->SetBranchAddress("NPFJet10", &Npf_10);
   int Npf_15;          Tree->SetBranchAddress("NPFJet15", &Npf_15);
   int Npf_20;          Tree->SetBranchAddress("NPFJet20", &Npf_20);
   int Npf_25;          Tree->SetBranchAddress("NPFJet25", &Npf_25);
   int Npf_30;          Tree->SetBranchAddress("NPFJet30", &Npf_30);
   int Npf_35;          Tree->SetBranchAddress("NPFJet35", &Npf_35);
   int Npf_40;          Tree->SetBranchAddress("NPFJet40", &Npf_40);
   int Npf_45;          Tree->SetBranchAddress("NPFJet45", &Npf_45);
   int Ncalo_10;        Tree->SetBranchAddress("NCaloJet10", &Ncalo_10);
   int Ncalo_15;        Tree->SetBranchAddress("NCaloJet15", &Ncalo_15);
   int Ncalo_20;        Tree->SetBranchAddress("NCaloJet20", &Ncalo_20);
   int Ncalo_25;        Tree->SetBranchAddress("NCaloJet25", &Ncalo_25);
   int Ncalo_30;        Tree->SetBranchAddress("NCaloJet30", &Ncalo_30);
   int Ncalo_35;        Tree->SetBranchAddress("NCaloJet35", &Ncalo_35);
   int Ncalo_40;        Tree->SetBranchAddress("NCaloJet40", &Ncalo_40);
   int Ncalo_45;        Tree->SetBranchAddress("NCaloJet45", &Ncalo_45);
   int q;                  Tree->SetBranchAddress("Muon1Charge", &q);
   int q2 = 999;
   double R;               Tree->SetBranchAddress("R", &R);
   double Rp;              Tree->SetBranchAddress("RPrime", &Rp);
   double Run;                Tree->SetBranchAddress("RunNumber", &Run);
   double secondJet_pt;    Tree->SetBranchAddress("PFJet2PT", &secondJet_pt);
   double W = CrossSection / Tree->GetEntries();
   double Z_eta = 999;
   double Z_phi = 999;
   double Z_pt = 999;

   TFile F2(OutputFile.c_str(), "RECREATE");

   TTree TemporaryTree("TemporaryTree", "Temporary Tree");

   TemporaryTree.Branch("btag", &btag, "btag/D");
   TemporaryTree.Branch("btag_2", &btag_2, "btag_2/D");
   TemporaryTree.Branch("CosThb", &CosThb, "CosThb/D");
   TemporaryTree.Branch("Dxy", &Dxy, "Dxy/D");
   TemporaryTree.Branch("Dz", &Dz, "Dz/D");
   TemporaryTree.Branch("Event", &Event, "Event/D");
   TemporaryTree.Branch("firstJet_pt", &firstJet_pt, "firstJet_pt/D");
   TemporaryTree.Branch("HasBHadron", &HasBHadron, "HasBHadron/D");
   TemporaryTree.Branch("Index", &Index, "Index/D");
   TemporaryTree.Branch("Iso_pf_abs", &Iso_pf_abs, "Iso_pf_abs/D");
   TemporaryTree.Branch("Iso_pf_relmt", &Iso_pf_relmt, "Iso_pf_relmt/D");
   TemporaryTree.Branch("Iso_pf_relpt", &Iso_pf_relpt, "Iso_pf_relpt/D");
   TemporaryTree.Branch("Iso_tk_abs", &Iso_tk_abs, "Iso_tk_abs/D");
   TemporaryTree.Branch("Iso_tk_relmt", &Iso_tk_relmt, "Iso_tk_relmt/D");
   TemporaryTree.Branch("Iso_tk_relpt", &Iso_tk_relpt, "Iso_tk_relpt/D");
   TemporaryTree.Branch("Lumi", &Lumi, "Lumi/D");
   TemporaryTree.Branch("MR", &MR, "MR/D");
   TemporaryTree.Branch("MRp", &MRp, "MRp/D");
   TemporaryTree.Branch("Met_calo", &Met_calo, "Met_calo/D");
   TemporaryTree.Branch("Met_pf", &Met_pf, "Met_pf/D");
   TemporaryTree.Branch("Met_tc", &Met_tc, "Met_tc/D");
   TemporaryTree.Branch("Mt_calo", &Mt_calo, "Mt_calo/D");
   TemporaryTree.Branch("Mt_pf", &Mt_pf, "Mt_pf/D");
   TemporaryTree.Branch("Mt_tc", &Mt_tc, "Mt_tc/D");
   TemporaryTree.Branch("muPt", &muPt, "muPt/D");
   TemporaryTree.Branch("mu2Pt", &mu2Pt, "mu2Pt/D");
   TemporaryTree.Branch("Npf_10", &Npf_10, "Npf_10/D");
   TemporaryTree.Branch("Npf_15", &Npf_15, "Npf_15/D");
   TemporaryTree.Branch("Npf_20", &Npf_20, "Npf_20/D");
   TemporaryTree.Branch("Npf_25", &Npf_25, "Npf_25/D");
   TemporaryTree.Branch("Npf_30", &Npf_30, "Npf_30/D");
   TemporaryTree.Branch("Npf_35", &Npf_35, "Npf_35/D");
   TemporaryTree.Branch("Npf_40", &Npf_40, "Npf_40/D");
   TemporaryTree.Branch("Npf_45", &Npf_45, "Npf_45/D");
   TemporaryTree.Branch("Ncalo_10", &Ncalo_10, "Ncalo_10/D");
   TemporaryTree.Branch("Ncalo_15", &Ncalo_15, "Ncalo_15/D");
   TemporaryTree.Branch("Ncalo_20", &Ncalo_20, "Ncalo_20/D");
   TemporaryTree.Branch("Ncalo_25", &Ncalo_25, "Ncalo_25/D");
   TemporaryTree.Branch("Ncalo_30", &Ncalo_30, "Ncalo_30/D");
   TemporaryTree.Branch("Ncalo_35", &Ncalo_35, "Ncalo_35/D");
   TemporaryTree.Branch("Ncalo_40", &Ncalo_40, "Ncalo_40/D");
   TemporaryTree.Branch("Ncalo_45", &Ncalo_45, "Ncalo_45/D");
   TemporaryTree.Branch("q", &q, "q/D");
   TemporaryTree.Branch("q2", &q2, "q2/D");
   TemporaryTree.Branch("R", &R, "R/D");
   TemporaryTree.Branch("Rp", &Rp, "Rp/D");
   TemporaryTree.Branch("secondJet_pt", &secondJet_pt, "secondJet_pt/D");
   TemporaryTree.Branch("W", &W, "W/D");
   TemporaryTree.Branch("Z_eta", &Z_eta, "Z_eta/D");
   TemporaryTree.Branch("Z_phi", &Z_phi, "Z_phi/D");
   TemporaryTree.Branch("Z_pt", &Z_pt, "Z_pt/D");

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if(i % 50000 == 0)
         cout << "Processing entry " << i << "/" << EntryCount << endl;

      Tree->GetEntry(i);

      Index = i;

      TemporaryTree.Fill();
   }

   TemporaryTree.Write();

   RooArgSet Variables;

   RooRealVar Var_btag("btag", "btag", -10000, 10000);                     Variables.add(Var_btag);
   RooRealVar Var_btag_2("btag_2", "btag_2", -10000, 10000);               Variables.add(Var_btag_2);
   RooRealVar Var_CosThb("CosThb", "CosThb", -1, 1);                       Variables.add(Var_CosThb);
   RooRealVar Var_Dxy("Dxy", "Dxy", -10000, 10000);                        Variables.add(Var_Dxy);
   RooRealVar Var_Dz("Dz", "Dz", -10000, 10000);                           Variables.add(Var_Dz);
   RooRealVar Var_Event("Event", "Event", 0, 100000000);                   Variables.add(Var_Event);
   RooRealVar Var_firstJet_pt("firstJet_pt", "firstJet_pt", -10000, 10000);Variables.add(Var_firstJet_pt);
   RooRealVar Var_HasBHadron("HasBHadron", "HasBHadron", -10000, 10000);   Variables.add(Var_HasBHadron);
   RooRealVar Var_Index("Index", "Index", 0, 100000000);                   Variables.add(Var_Index);
   RooRealVar Var_Iso_pf_abs("Iso_pf_abs", "Iso_pf_abs", 0, 10000);        Variables.add(Var_Iso_pf_abs);
   RooRealVar Var_Iso_pf_relmt("Iso_pf_relmt", "Iso_pf_relmt", 0, 10000);  Variables.add(Var_Iso_pf_relmt);
   RooRealVar Var_Iso_pf_relpt("Iso_pf_relpt", "Iso_pf_relpt", 0, 10000);  Variables.add(Var_Iso_pf_relpt);
   RooRealVar Var_Iso_tk_abs("Iso_tk_abs", "Iso_tk_abs", 0, 10000);        Variables.add(Var_Iso_tk_abs);
   RooRealVar Var_Iso_tk_relmt("Iso_tk_relmt", "Iso_tk_relmt", 0, 10000);  Variables.add(Var_Iso_tk_relmt);
   RooRealVar Var_Iso_tk_relpt("Iso_tk_relpt", "Iso_tk_relpt", 0, 10000);  Variables.add(Var_Iso_tk_relpt);
   RooRealVar Var_Lumi("Lumi", "Lumi", -100000000, 100000000);             Variables.add(Var_Lumi);
   RooRealVar Var_MR("MR", "MR", -10000, 10000);                           Variables.add(Var_MR);
   RooRealVar Var_MRp("MRp", "MRp", -10000, 10000);                        Variables.add(Var_MRp);
   RooRealVar Var_Met_calo("Met_calo", "Met_calo", 0, 100000);             Variables.add(Var_Met_calo);
   RooRealVar Var_Met_pf("Met_pf", "Met_pf", 0, 100000);                   Variables.add(Var_Met_pf);
   RooRealVar Var_Met_tc("Met_tc", "Met_tc", 0, 100000);                   Variables.add(Var_Met_tc);
   RooRealVar Var_Mt_calo("Mt_calo", "Mt_calo", 0, 100000);                Variables.add(Var_Mt_calo);
   RooRealVar Var_Mt_pf("Mt_pf", "Mt_pf", 0, 100000);                      Variables.add(Var_Mt_pf);
   RooRealVar Var_Mt_tc("Mt_tc", "Mt_tc", 0, 100000);                      Variables.add(Var_Mt_tc);
   RooRealVar Var_muPt("muPt", "muPt", 0, 100000);                         Variables.add(Var_muPt);
   RooRealVar Var_mu2Pt("mu2Pt", "mu2Pt", 0, 100000);                      Variables.add(Var_mu2Pt);
   RooRealVar Var_Npf_10("Npf_10", "Npf_10", 0, 10000);                    Variables.add(Var_Npf_10);
   RooRealVar Var_Npf_15("Npf_15", "Npf_15", 0, 10000);                    Variables.add(Var_Npf_15);
   RooRealVar Var_Npf_20("Npf_20", "Npf_20", 0, 10000);                    Variables.add(Var_Npf_20);
   RooRealVar Var_Npf_25("Npf_25", "Npf_25", 0, 10000);                    Variables.add(Var_Npf_25);
   RooRealVar Var_Npf_30("Npf_30", "Npf_30", 0, 10000);                    Variables.add(Var_Npf_30);
   RooRealVar Var_Npf_35("Npf_35", "Npf_35", 0, 10000);                    Variables.add(Var_Npf_35);
   RooRealVar Var_Npf_40("Npf_40", "Npf_40", 0, 10000);                    Variables.add(Var_Npf_40);
   RooRealVar Var_Npf_45("Npf_45", "Npf_45", 0, 10000);                    Variables.add(Var_Npf_45);
   RooRealVar Var_Ncalo_10("Ncalo_10", "Ncalo_10", 0, 10000);              Variables.add(Var_Ncalo_10);
   RooRealVar Var_Ncalo_15("Ncalo_15", "Ncalo_15", 0, 10000);              Variables.add(Var_Ncalo_15);
   RooRealVar Var_Ncalo_20("Ncalo_20", "Ncalo_20", 0, 10000);              Variables.add(Var_Ncalo_20);
   RooRealVar Var_Ncalo_25("Ncalo_25", "Ncalo_25", 0, 10000);              Variables.add(Var_Ncalo_25);
   RooRealVar Var_Ncalo_30("Ncalo_30", "Ncalo_30", 0, 10000);              Variables.add(Var_Ncalo_30);
   RooRealVar Var_Ncalo_35("Ncalo_35", "Ncalo_35", 0, 10000);              Variables.add(Var_Ncalo_35);
   RooRealVar Var_Ncalo_40("Ncalo_40", "Ncalo_40", 0, 10000);              Variables.add(Var_Ncalo_40);
   RooRealVar Var_Ncalo_45("Ncalo_45", "Ncalo_45", 0, 10000);              Variables.add(Var_Ncalo_45);
   RooRealVar Var_q("q", "q", -10000, 10000);                              Variables.add(Var_q);
   RooRealVar Var_q2("q2", "q2", -10000, 10000);                           Variables.add(Var_q2);
   RooRealVar Var_R("R", "R", -10000, 10000);                              Variables.add(Var_R);
   RooRealVar Var_Rp("Rp", "Rp", -10000, 10000);                           Variables.add(Var_Rp);
   RooRealVar Var_Run("Run", "Run", 0, 100000000);                         Variables.add(Var_Run);
   RooRealVar Var_secondJet_pt("secondJet_pt", "secondJet_pt", 0, 100000000); Variables.add(Var_secondJet_pt);
   RooRealVar Var_W("W", "W", 0, 1000000);                                 Variables.add(Var_W);
   RooRealVar Var_Z_eta("Z_eta", "Z_eta", -10000, 10000);                  Variables.add(Var_Z_eta);
   RooRealVar Var_Z_phi("Z_phi", "Z_phi", -10000, 10000);                  Variables.add(Var_Z_phi);
   RooRealVar Var_Z_pt("Z_pt", "Z_pt", 0, 100000000);                      Variables.add(Var_Z_pt);

   RooDataSet Dataset("Dataset", "Dataset", &TemporaryTree, Variables);

   Dataset.Write();

   F2.Close();

   F.Close();
}


