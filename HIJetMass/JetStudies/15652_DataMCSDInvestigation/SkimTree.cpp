#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "ProgressBar.h"

#define MAX 10
#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];

   TFile InputFile(Input.c_str());

   TTree *InputTree = (TTree *)InputFile.Get("Tree");
   
   TFile OutputFile(Output.c_str(), "RECREATE");

   InputTree->CopyTree("JetPT > 100")->Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;

   TTree OutputTree("Tree", "Tree");

   double TreeJetPT, TreeJetEta, TreeJetPhi;
   InputTree->SetBranchAddress("JetPT", &TreeJetPT);
   InputTree->SetBranchAddress("JetEta", &TreeJetEta);
   InputTree->SetBranchAddress("JetPhi", &TreeJetPhi);
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");

   double TreeJetSDMass, TreeJetSDZG, TreeJetSDRecoDR;
   InputTree->SetBranchAddress("JetSDMass", &TreeJetSDMass);
   InputTree->SetBranchAddress("JetSDZG", &TreeJetSDZG);
   InputTree->SetBranchAddress("JetSDRecoDR", &TreeJetSDRecoDR);
   OutputTree.Branch("JetSDMass", &TreeJetSDMass, "JetSDMass/D");
   OutputTree.Branch("JetSDZG", &TreeJetSDZG, "JetSDZG/D");
   OutputTree.Branch("JetSDRecoDR", &TreeJetSDRecoDR, "JetSDRecoDR/D");
   
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi;
   InputTree->SetBranchAddress("NewJetPT", &TreeNewJetPT);
   InputTree->SetBranchAddress("NewJetEta", &TreeNewJetEta);
   InputTree->SetBranchAddress("NewJetPhi", &TreeNewJetPhi);
   OutputTree.Branch("NewJetPT", &TreeNewJetPT, "NewJetPT/D");
   OutputTree.Branch("NewJetEta", &TreeNewJetEta, "NewJetEta/D");
   OutputTree.Branch("NewJetPhi", &TreeNewJetPhi, "NewJetPhi/D");

   double TreeSDPT[MAX], TreeSDMass[MAX], TreeSDZG[MAX], TreeSDRecoDR[MAX];
   InputTree->SetBranchAddress("SDPT", &TreeSDPT);
   InputTree->SetBranchAddress("SDMass", &TreeSDMass);
   InputTree->SetBranchAddress("SDZG", &TreeSDZG);
   InputTree->SetBranchAddress("SDRecoDR", &TreeSDRecoDR);
   OutputTree.Branch("SDPT", &TreeSDPT, Form("SDPT[%d]/D", MAX));
   OutputTree.Branch("SDMass", &TreeSDMass, Form("SDMass[%d]/D", MAX));
   OutputTree.Branch("SDZG", &TreeSDZG, Form("SDZG[%d]/D", MAX));
   OutputTree.Branch("SDRecoDR", &TreeSDRecoDR, Form("SDRecoDR[%d]/D", MAX));

   int EntryCount = InputTree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount < 300 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      InputTree->GetEntry(iEntry);

      if(TreeJetPT < 100)
         continue;

      OutputTree.Fill();
   }
         
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();

   OutputFile.Close();

   InputFile.Close();
}

double CalculateDR(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
   if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
   return sqrt(DEta * DEta + DPhi * DPhi);
}





