#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "ProgressBar.h"

struct Record;
int main(int argc, char *argv[]);

struct Record
{
   int Run;
   int Lumi;
   unsigned long long Event;
   bool operator <(const Record &other) const
   {
      if(Run < other.Run)   return true;
      if(Run > other.Run)   return false;
      if(Lumi < other.Lumi)   return true;
      if(Lumi > other.Lumi)   return false;
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string GenInputFileName    = CL.Get("GenInput");
   string HLTInputFileName    = CL.Get("HLTInput");
   string OutputFileName      = CL.Get("Output");

   string GenTreeName         = CL.Get("GenTreeName", "HiGenParticleAna/hi");
   string HLTTreeName         = CL.Get("HLTTreeName", "hltanalysis/HltTree");
   string HLTObjectTreeName   = CL.Get("HLTObjectTreeName", "hltobject/HLT_HICsAK4PFJet60Eta1p5_v");
   string OutputDirectoryName = CL.Get("Directory", "ak4pf");

   TFile GenInputFile(GenInputFileName.c_str());
   TFile HLTInputFile(HLTInputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   
   TTree *GenTree = (TTree *)GenInputFile.Get(GenTreeName.c_str());
   TTree *HLTTree = (TTree *)HLTInputFile.Get(HLTTreeName.c_str());
   TTree *HLTObjectTree = (TTree *)HLTInputFile.Get(HLTObjectTreeName.c_str());

   Assert(GenTree != nullptr,       "Gen tree not found");
   Assert(HLTTree != nullptr,       "HLT tree not found");
   Assert(HLTObjectTree != nullptr, "HLT object tree not found");

   OutputFile.mkdir(OutputDirectoryName.c_str())->cd();
   TTree OutputTree("t", "tree");

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

   OutputTree.Branch("npus", &npus);
   OutputTree.Branch("tnpus", &tnpus);
   OutputTree.Branch("zpositions", &zpositions);
   OutputTree.Branch("bxns", &bxns);
   OutputTree.Branch("sumpt_lowpt", &sumpt_lowpt);
   OutputTree.Branch("sumpt_highpt", &sumpt_highpt);
   OutputTree.Branch("ntrks_lowpt", &ntrks_lowpt);
   OutputTree.Branch("ntrks_highpt", &ntrks_highpt);
   OutputTree.Branch("rhos", &rhos, "rhos/F");
   OutputTree.Branch("rho", &rho, "rho/F");
   OutputTree.Branch("pthat", &pthat, "pthat/F");
   OutputTree.Branch("beta", &beta, "beta/F");
   OutputTree.Branch("betaStar", &betaStar, "betaStar/F");
   OutputTree.Branch("weight", &weight, "weight/F");
   OutputTree.Branch("refpvz", &refpvz, "refpvz/F");
   OutputTree.Branch("pudensity", &pudensity, "pudensity/F");
   OutputTree.Branch("gpudensity", &gpudensity, "gpudensity/F");
   OutputTree.Branch("npv", &npv, "npv/L");
   OutputTree.Branch("run", &run, "run/L");
   OutputTree.Branch("lumi", &lumi, "lumi/L");
   OutputTree.Branch("evt", &evt, "evt/L");
   OutputTree.Branch("refrank", &refrank);
   OutputTree.Branch("refpdgid", &refpdgid);
   OutputTree.Branch("refpdgid_algorithmicDef", &refpdgid_algorithmicDef);
   OutputTree.Branch("refpdgid_physicsDef", &refpdgid_physicsDef);
   OutputTree.Branch("jtjec", &jtjec);
   OutputTree.Branch("jtchf", &jtchf);
   OutputTree.Branch("jtnhf", &jtnhf);
   OutputTree.Branch("jtnef", &jtnef);
   OutputTree.Branch("jtcef", &jtcef);
   OutputTree.Branch("jtmuf", &jtmuf);
   OutputTree.Branch("jthfhf", &jthfhf);
   OutputTree.Branch("jthfef", &jthfef);
   OutputTree.Branch("refdzvtx", &refdzvtx);

   unsigned char   nref;
   vector<float>   RefE, RefPT, RefEta, RefPhi, RefY, RefArea;
   vector<float>   JetE, JetPT, JetEta, JetPhi, JetY, JetArea;
   vector<float>   MatchDR;

   OutputTree.Branch("nref",    &nref, "nref/b");
   OutputTree.Branch("refe",    &RefE);
   OutputTree.Branch("refpt",   &RefPT);
   OutputTree.Branch("refeta",  &RefEta);
   OutputTree.Branch("refphi",  &RefPhi);
   OutputTree.Branch("refy",    &RefY);
   OutputTree.Branch("refarea", &RefArea);
   OutputTree.Branch("refdrjt", &MatchDR);
   OutputTree.Branch("jte",     &JetE);
   OutputTree.Branch("jtpt",    &JetPT);
   OutputTree.Branch("jteta",   &JetEta);
   OutputTree.Branch("jtphi",   &JetPhi);
   OutputTree.Branch("jty",     &JetY);
   OutputTree.Branch("jtarea",  &JetArea);

   Record Messenger;
   HLTTree->SetBranchAddress("Run",       &Messenger.Run);
   HLTTree->SetBranchAddress("LumiBlock", &Messenger.Lumi);
   HLTTree->SetBranchAddress("Event",     &Messenger.Event);
   
   vector<float> *HLTJetPT = nullptr;
   vector<float> *HLTJetEta = nullptr;
   vector<float> *HLTJetPhi = nullptr;
   vector<float> *HLTJetMass = nullptr;
   HLTObjectTree->SetBranchAddress("pt",   &HLTJetPT);
   HLTObjectTree->SetBranchAddress("eta",  &HLTJetEta);
   HLTObjectTree->SetBranchAddress("phi",  &HLTJetPhi);
   HLTObjectTree->SetBranchAddress("mass", &HLTJetMass);

   cout << "Now building event list from HLT tree" << endl;

   map<Record, int> HLTEventList;
   int EntryCount = HLTTree->GetEntries();
   ProgressBar Bar1(cout, EntryCount);
   Bar1.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 250 || (iE % (EntryCount / 200) == 0))
      {
         Bar1.Update(iE);
         Bar1.Print();
      }
      
      HLTTree->GetEntry(iE);
      HLTEventList.insert(pair<Record, int>(Messenger, iE));
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   GenTree->SetBranchAddress("run",   &Messenger.Run);
   GenTree->SetBranchAddress("lumi",  &Messenger.Lumi);
   GenTree->SetBranchAddress("event", &Messenger.Event);

   int NParticles;
   vector<float> *PT = nullptr;
   vector<float> *Eta = nullptr;
   vector<float> *Phi = nullptr;
   vector<float> *Mass = nullptr;
   vector<int> *NDaughters = nullptr;
   GenTree->SetBranchAddress("mult", &NParticles);
   GenTree->SetBranchAddress("pt", &PT);
   GenTree->SetBranchAddress("eta", &Eta);
   GenTree->SetBranchAddress("phi", &Phi);
   GenTree->SetBranchAddress("mass", &Mass);
   GenTree->SetBranchAddress("nDaughters", &NDaughters);

   cout << "Now starting to loop over trees" << endl;

   int EventCount = 0;

   EntryCount = GenTree->GetEntries();
   ProgressBar Bar2(cout, EntryCount);
   Bar2.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 250 || (iE % (EntryCount / 200) == 0))
      {
         Bar2.Update(iE);
         Bar2.Print();
      }

      GenTree->GetEntry(iE);

      if(HLTEventList.find(Messenger) == HLTEventList.end())
         continue;
      int IE = HLTEventList[Messenger];
      HLTObjectTree->GetEntry(IE);

      EventCount = EventCount + 1;

      // Cluster gen jets
      vector<PseudoJet> GenParticles;
      for(int i = 0; i < NParticles; i++)
      {
         PseudoJet P;
         // For massless particle, eta and rapidity is the same.  So we can set px/py/pz this way.
         P.reset_momentum_PtYPhiM(PT->at(i), Eta->at(i), Phi->at(i), 0);
         // Now we update energy to have the mass
         double Energy = sqrt(P[0] * P[0] + P[1] * P[1] + P[2] * P[2] + Mass->at(i) * Mass->at(i));

         GenParticles.emplace_back(PseudoJet(P[0], P[1], P[2], Energy));
      }

      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence GenSequence(GenParticles, Definition);
      vector<PseudoJet> GenJets = GenSequence.inclusive_jets(0.5);

      // Convert HLT jets to pseudojet format
      int NJet = HLTJetPT->size();
      vector<PseudoJet> HLTJets;
      for(int i = 0; i < NJet; i++)
      {
         PseudoJet P;
         P.reset_momentum_PtYPhiM(HLTJetPT->at(i), HLTJetEta->at(i), HLTJetPhi->at(i), 0);
         double Energy = sqrt(P[0] * P[0] + P[1] * P[1] + P[2] * P[2] + HLTJetMass->at(i) * HLTJetMass->at(i));
         HLTJets.emplace_back(PseudoJet(P[0], P[1], P[2], Energy));
      }

      // Now we do the matching and fill outputs

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

      for(PseudoJet &J : GenJets)
      {
         double BestDistance = -1;
         PseudoJet BestJet;

         for(PseudoJet &HLTJet : HLTJets)
         {
            double Distance = J.delta_R(HLTJet);
            if(BestDistance < 0 || Distance < BestDistance)
            {
               BestDistance = Distance;
               BestJet = HLTJet;
            }
         }

         if(BestDistance < 0)
            continue;

         RefE.push_back(J[3]);
         RefPT.push_back(J.perp());
         RefEta.push_back(J.eta());
         RefPhi.push_back(J.phi());
         RefY.push_back(J.rapidity());
         RefArea.push_back(0.504);
         MatchDR.push_back(BestDistance);
         JetE.push_back(BestJet[3]);
         JetPT.push_back(BestJet.perp());
         JetEta.push_back(BestJet.eta());
         JetPhi.push_back(BestJet.phi());
         JetY.push_back(BestJet.rapidity());
         JetArea.push_back(0.504);
      }

      nref = RefPT.size();

      OutputTree.Fill();
   }
   Bar2.Update(EntryCount);
   Bar2.Print();
   Bar2.PrintLine();

   cout << EventCount << " events matched." << endl;

   OutputTree.Write();

   OutputFile.Close();
   HLTInputFile.Close();
   GenInputFile.Close();

   return 0;
}


