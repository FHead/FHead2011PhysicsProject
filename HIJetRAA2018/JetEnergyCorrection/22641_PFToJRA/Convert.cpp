#include <iostream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[]);
void AddAlgorithm(TFile &InputFile, TFile &OutputFile, string FolderName, double R, double DR, double MinPT = 5, bool DoExclude = false);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   bool DoExclude        = CL.GetBool("ExcludeHEM", false);

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   AddAlgorithm(InputFile, OutputFile, "ak1pf", 0.15, 0.08, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak2pf", 0.20, 0.10, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak3pf", 0.30, 0.15, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak4pf", 0.40, 0.20, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak5pf", 0.50, 0.25, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak6pf", 0.60, 0.30, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak7pf", 0.80, 0.40, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak8pf", 1.00, 0.50, 5, DoExclude);
   AddAlgorithm(InputFile, OutputFile, "ak9pf", 1.20, 0.60, 5, DoExclude);

   OutputFile.Close();
   InputFile.Close();

   return 0;
}

void AddAlgorithm(TFile &InputFile, TFile &OutputFile, string FolderName, double R, double DR, double MinPT, bool DoExclude)
{
   double HEMHigh = -2.5 * (2 * pi) / 18;
   double HEMLow = -4.5 * (2 * pi) / 18;

   double Area = R * R * M_PI;

   TTree *PFTree = (TTree *)InputFile.Get("pfcandAnalyzer/pfTree");
   Assert(PFTree != nullptr, "PF tree not found!");

   int nPF;
   vector<float> *pfId = nullptr;
   vector<float> *pfPt = nullptr;
   vector<float> *pfEnergy = nullptr;
   vector<float> *pfEta = nullptr;
   vector<float> *pfPhi = nullptr;

   PFTree->SetBranchAddress("nPFpart", &nPF);
   PFTree->SetBranchAddress("pfId", &pfId);
   PFTree->SetBranchAddress("pfPt", &pfPt);
   PFTree->SetBranchAddress("pfEnergy", &pfEnergy);
   PFTree->SetBranchAddress("pfEta", &pfEta);
   PFTree->SetBranchAddress("pfPhi", &pfPhi);

   TTree *GenTree = (TTree *)InputFile.Get("HiGenParticleAna/hi");
   Assert(GenTree != nullptr, "Gen tree not found");

   int mult;
   vector<float> *pt = nullptr;
   vector<float> *eta = nullptr;
   vector<float> *phi = nullptr;
   vector<float> *pdg = nullptr;
   vector<int>   *nDaughters = nullptr;

   GenTree->SetBranchAddress("mult", &mult);
   GenTree->SetBranchAddress("pt", &pt);
   GenTree->SetBranchAddress("eta", &eta);
   GenTree->SetBranchAddress("phi", &phi);
   GenTree->SetBranchAddress("pdg", &pdg);
   GenTree->SetBranchAddress("nDaughters", &nDaughters);

   OutputFile.mkdir(FolderName.c_str())->cd();

   TTree Tree("t", Form("Tree with R = %.2f and DR = %.2f", R, DR));

   vector<int>     npus = {0};
   vector<float>   tnpus = {0};
   vector<float>   zpositions = {0};
   vector<int>     bxns = {0};
   vector<float>   sumpt_lowpt = {10};
   vector<float>   sumpt_highpt = {10};
   vector<int>     ntrks_lowpt = {5};
   vector<int>     ntrks_highpt = {5};
   vector<float>   rhos = {10};
   float           rho = 10;
   float           pthat = 10;
   float           beta = 1;
   float           betaStar = 1;
   float           weight = 1;
   float           refpvz = 1;
   float           pudensity = 0;
   float           gpudensity = 0;
   long            npv = 1;
   long            run = 1;
   long            lumi = 10;
   long            evt = 100;
   vector<unsigned char> refrank(100);
   vector<int>     refpdgid(100);
   vector<int>     refpdgid_algorithmicDef(100);
   vector<int>     refpdgid_physicsDef(100);
   vector<float>   jtjec(100);
   vector<float>   jtchf(100);
   vector<float>   jtnhf(100);
   vector<float>   jtnef(100);
   vector<float>   jtcef(100);
   vector<float>   jtmuf(100);
   vector<float>   jthfhf(100);
   vector<float>   jthfef(100);
   vector<float>   refdzvtx(100);

   Tree.Branch("npus", &npus);
   Tree.Branch("tnpus", &tnpus);
   Tree.Branch("zpositions", &zpositions);
   Tree.Branch("bxns", &bxns);
   Tree.Branch("sumpt_lowpt", &sumpt_lowpt);
   Tree.Branch("sumpt_highpt", &sumpt_highpt);
   Tree.Branch("ntrks_lowpt", &ntrks_lowpt);
   Tree.Branch("ntrks_highpt", &ntrks_highpt);
   Tree.Branch("rhos", &rhos, "rhos/F");
   Tree.Branch("rho", &rho, "rho/F");
   Tree.Branch("pthat", &pthat, "pthat/F");
   Tree.Branch("beta", &beta, "beta/F");
   Tree.Branch("betaStar", &betaStar, "betaStar/F");
   Tree.Branch("weight", &weight, "weight/F");
   Tree.Branch("refpvz", &refpvz, "refpvz/F");
   Tree.Branch("pudensity", &pudensity, "pudensity/F");
   Tree.Branch("gpudensity", &gpudensity, "gpudensity/F");
   Tree.Branch("npv", &npv, "npv/L");
   Tree.Branch("run", &run, "run/L");
   Tree.Branch("lumi", &lumi, "lumi/L");
   Tree.Branch("evt", &evt, "evt/L");
   Tree.Branch("refrank", &refrank);
   Tree.Branch("refpdgid", &refpdgid);
   Tree.Branch("refpdgid_algorithmicDef", &refpdgid_algorithmicDef);
   Tree.Branch("refpdgid_physicsDef", &refpdgid_physicsDef);
   Tree.Branch("jtjec", &jtjec);
   Tree.Branch("jtchf", &jtchf);
   Tree.Branch("jtnhf", &jtnhf);
   Tree.Branch("jtnef", &jtnef);
   Tree.Branch("jtcef", &jtcef);
   Tree.Branch("jtmuf", &jtmuf);
   Tree.Branch("jthfhf", &jthfhf);
   Tree.Branch("jthfef", &jthfef);
   Tree.Branch("refdzvtx", &refdzvtx);
 
   unsigned char   nref;
   vector<float>   RefE, RefPT, RefEta, RefPhi, RefY, RefArea;
   vector<float>   JetE, JetPT, JetEta, JetPhi, JetY, JetArea;
   vector<float>   MatchDR;

   Tree.Branch("nref",    &nref, "nref/b");
   Tree.Branch("refe",    &RefE);
   Tree.Branch("refpt",   &RefPT);
   Tree.Branch("refeta",  &RefEta);
   Tree.Branch("refphi",  &RefPhi);
   Tree.Branch("refy",    &RefY);
   Tree.Branch("refarea", &RefArea);
   Tree.Branch("refdrjt", &MatchDR);
   Tree.Branch("jte",     &JetE);
   Tree.Branch("jtpt",    &JetPT);
   Tree.Branch("jteta",   &JetEta);
   Tree.Branch("jtphi",   &JetPhi);
   Tree.Branch("jty",     &JetY);
   Tree.Branch("jtarea",  &JetArea);

   int EntryCount = PFTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      PFTree->GetEntry(iE);
      GenTree->GetEntry(iE);

      vector<PseudoJet> GenParticles;
      for(int i = 0; i < mult; i++)
      {
         if((*pdg)[i] == 12 || (*pdg)[i] == -12)   continue;
         if((*pdg)[i] == 14 || (*pdg)[i] == -14)   continue;
         if((*pdg)[i] == 16 || (*pdg)[i] == -16)   continue;
         if((*nDaughters)[i] > 0)                  continue;

         FourVector P;
         P.SetPtEtaPhiMass((*pt)[i], (*eta)[i], (*phi)[i], 0);
         GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, R);
      ClusterSequence GenSequence(GenParticles, Definition);
      vector<PseudoJet> GenJets = sorted_by_pt(GenSequence.inclusive_jets(MinPT));

      vector<PseudoJet> PFParticles;
      for(int i = 0; i < nPF; i++)
      {
         FourVector P;
         P.SetPtEtaPhiMass((*pfPt)[i], (*pfEta)[i], (*pfPhi)[i], 0);
         PFParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      ClusterSequence PFSequence(PFParticles, Definition);
      vector<PseudoJet> AllPFJets = sorted_by_pt(PFSequence.inclusive_jets(1));
      vector<FourVector> PFJets;
      for(int i = 0; i < (int)AllPFJets.size(); i++)
      {
         FourVector P(AllPFJets[i].e(), AllPFJets[i].px(), AllPFJets[i].py(), AllPFJets[i].pz());
         PFJets.push_back(P);
      }

      // cout << "Meow" << endl;
      // cout << GenJets.size() << " " << GenJets[0].perp() << " " << GenJets[0].eta() << " " << GenJets[0].phi() << endl;
      // cout << PFJets.size() << " " << PFJets[0].perp() << " " << PFJets[0].eta() << " " << PFJets[0].phi() << endl;

      RefE.clear();
      RefPT.clear();
      RefEta.clear();
      RefPhi.clear();
      RefY.clear();
      RefArea.clear();
      MatchDR.clear();
      JetE.clear();
      JetPT.clear();
      JetEta.clear();
      JetPhi.clear();
      JetY.clear();
      JetArea.clear();

      for(int i = 0; i < (int)GenJets.size(); i++)
      {
         FourVector P(GenJets[i].e(), GenJets[i].px(), GenJets[i].py(), GenJets[i].pz());

         if(DoExclude == true)
            if(P.GetPhi() < HEMHigh + R * 0.5 && P.GetPhi() > HEMLow - R * 0.5)
               continue;

         int BestIndex = -1;
         double MinDR = 1000;
         for(int j = 0; j < (int)PFJets.size(); j++)
         {
            double DR = GetDR(P, PFJets[j]);
            if(DR < MinDR)
            {
               BestIndex = j;
               MinDR = DR;
            }
         }

         if(BestIndex < 0)
            continue;

         RefE.push_back(P[0]);
         RefPT.push_back(P.GetPT());
         RefEta.push_back(P.GetEta());
         RefPhi.push_back(P.GetPhi());
         RefY.push_back(P.GetY());
         RefArea.push_back(Area);
         MatchDR.push_back(MinDR);
         JetE.push_back(PFJets[BestIndex][0]);
         JetPT.push_back(PFJets[BestIndex].GetPT());
         JetEta.push_back(PFJets[BestIndex].GetEta());
         JetPhi.push_back(PFJets[BestIndex].GetPhi());
         JetY.push_back(PFJets[BestIndex].GetY());
         JetArea.push_back(Area);
      }
      
      nref = RefPT.size();

      Tree.Fill();
   }

   Tree.Write();
}





