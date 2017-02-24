#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "AngleConversion.h"
#include "Cuts.h"

int main(int argc, char *argv[]);
vector<pair<double, double>> ReadTree(string FileName);

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " FileName" << endl;
      return -1;
   }

   SetThesisStyle();

   string FileName = "ddbar_PDF_to_2e2mu_LO_ForEff_13TeV_10to25GeV_1.root";

   FileName = argv[1];

   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("Tree");

   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   T->SetBranchAddress("L1PT", &L1PT);
   T->SetBranchAddress("L1Eta", &L1Eta);
   T->SetBranchAddress("L1Phi", &L1Phi);
   T->SetBranchAddress("L2PT", &L2PT);
   T->SetBranchAddress("L2Eta", &L2Eta);
   T->SetBranchAddress("L2Phi", &L2Phi);
   T->SetBranchAddress("L3PT", &L3PT);
   T->SetBranchAddress("L3Eta", &L3Eta);
   T->SetBranchAddress("L3Phi", &L3Phi);
   T->SetBranchAddress("L4PT", &L4PT);
   T->SetBranchAddress("L4Eta", &L4Eta);
   T->SetBranchAddress("L4Phi", &L4Phi);

   int TotalEvents = 0;
   vector<int> PassedEvents(20, 0);

   int EntryCount = T->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % 500 == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      T->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      vector<bool> Decision = PassPairingCuts(Leptons);

      TotalEvents = TotalEvents + 1;
      for(int i = 0; i < 20; i++)
         if(Decision[i] == true)
            PassedEvents[i] = PassedEvents[i] + 1;
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   F.Close();

   for(int i = 0; i < 20; i++)
   {
      string Cut = "A";
      Cut[0] = char('A' + i);

      cout << "Cut " << Cut << ": "
         << PassedEvents[i] << "/" << TotalEvents << " = " << (double)PassedEvents[i] / TotalEvents << endl;
   }

   return 0;
}

