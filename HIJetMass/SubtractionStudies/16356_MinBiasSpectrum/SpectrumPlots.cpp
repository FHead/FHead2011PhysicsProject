#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"

#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
double GetDPhi(double phi1, double phi2);

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
   // double PTHatMin = atof(argv[4]);
   // double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   TFile InputFile(Input.c_str());

   string PFTreeName = "pfcandAnalyzer/pfTree";

   HiEventTreeMessenger MHiEvent(InputFile);
   GenParticleTreeMessenger MGen(InputFile);
   PFTreeMessenger MPF(InputFile);
   RhoTreeMessenger MRho(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", "Raw event count", 1, 0, 1);

   TH2D HRhoEta("HRhoEta", ";rho;eta", 100, 0, 400, 100, -1.3, 1.3);

   TTree Tree("Tree", "Tree");

   long long event;
   double centrality;
   double rho;
   Tree.Branch("Event", &event, "Event/L");
   Tree.Branch("Centrality", &centrality, "Centrality/D");
   Tree.Branch("Rho", &rho, "Rho/D");

   int pfcount;
   double eta[10000], phi[10000], pt[10000];
   int type[10000];
   Tree.Branch("PFCount", &pfcount, "PFCount/I");
   Tree.Branch("Eta", &eta, "Eta[10000]/D");
   Tree.Branch("Phi", &phi, "Phi[10000]/D");
   Tree.Branch("PT", &pt, "PT[10000]/D");
   Tree.Branch("ID", &type, "ID[10000]/I");

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(3);

   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount < 500 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      MHiEvent.GetEntry(iEntry);
      MGen.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MRho.GetEntry(iEntry);

      event = MHiEvent.Event;

      HN.Fill(0);

      double EventRho = -1;
      if(MRho.EtaMax->size() > 0 && MRho.Rho->size() > 0)
         EventRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      centrality = GetCentrality(MHiEvent.hiBin);
      rho = EventRho;

      pfcount = 0;
      for(int i = 0; i < 10000; i++)
      {
         eta[i] = 0;
         phi[i] = 0;
         pt[i] = 0;
         type[i] = 0;
      }
      
      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         HRhoEta.Fill(EventRho, (*MPF.Eta)[i]);

         if((*MPF.Eta)[i] < 1.7 && (*MPF.Eta)[i] > -1.7)
         {
            eta[pfcount] = (*MPF.Eta)[i];
            phi[pfcount] = (*MPF.Phi)[i];
            pt[pfcount] = (*MPF.PT)[i];
            type[pfcount] = (*MPF.ID)[i];
            pfcount = pfcount + 1;
         }
         if(pfcount >= 10000)
            break;
      }
         
      Tree.Fill();
   }

   Tree.Write();

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HN.Write();

   HRhoEta.Write();

   OutputFile.Close();

   InputFile.Close();
}

double GetDPhi(double phi1, double phi2)
{
   double dphi = phi1 - phi2;

   if(dphi < -PI)   dphi = dphi + 2 * PI;
   if(dphi > +PI)   dphi = dphi - 2 * PI;

   return dphi;
}






