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

   double rho, eta, pt;
   Tree.Branch("Rho", &rho, "Rho/D");
   Tree.Branch("Eta", &eta, "Eta/D");
   Tree.Branch("PT", &pt, "PT/D");

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

      HN.Fill(0);

      double EventRho = -1;
      if(MRho.EtaMax->size() > 0 && MRho.Rho->size() > 0)
         EventRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      rho = EventRho;

      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         HRhoEta.Fill(EventRho, (*MPF.Eta)[i]);

         eta = (*MPF.Eta)[i];
         pt = (*MPF.PT)[i];

         if(eta < 1.3 && eta > -1.3)
            Tree.Fill();
      }
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






