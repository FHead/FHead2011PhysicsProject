#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "SDJetHelper.h"

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "I'd rather not run on data for this study" << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   double CBinMin[5+1] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   string PTBin[7] = {"PTBin0", "PTBin1", "PTBin2", "PTBin3", "PTBin4", "PTBin5", "PTBin6"};
   double PTBinMin[7+1] = {80, 100, 120, 140, 160, 200, 300, 500};

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TTree OutputTree("T", "T");

   double TreeJetPT, TreeJetEta, TreeJetPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");

   int TreeRegion;
   OutputTree.Branch("Region", &TreeRegion, "Region/I");

   double TreeSubJet1PT, TreeSubJet1Eta, TreeSubJet1Phi;
   OutputTree.Branch("SubJet1PT", &TreeSubJet1PT, "SubJet1PT/D");
   OutputTree.Branch("SubJet1Eta", &TreeSubJet1Eta, "SubJet1Eta/D");
   OutputTree.Branch("SubJet1Phi", &TreeSubJet1Phi, "SubJet1Phi/D");
   
   double TreeSubJet2PT, TreeSubJet2Eta, TreeSubJet2Phi;
   OutputTree.Branch("SubJet2PT", &TreeSubJet2PT, "SubJet2PT/D");
   OutputTree.Branch("SubJet2Eta", &TreeSubJet2Eta, "SubJet2Eta/D");
   OutputTree.Branch("SubJet2Phi", &TreeSubJet2Phi, "SubJet2Phi/D");

   double TreeGenSubJet1PT, TreeGenSubJet1Eta, TreeGenSubJet1Phi;
   OutputTree.Branch("GenSubJet1PT", &TreeGenSubJet1PT, "GenSubJet1PT/D");
   OutputTree.Branch("GenSubJet1Eta", &TreeGenSubJet1Eta, "GenSubJet1Eta/D");
   OutputTree.Branch("GenSubJet1Phi", &TreeGenSubJet1Phi, "GenSubJet1Phi/D");
   
   double TreeGenSubJet2PT, TreeGenSubJet2Eta, TreeGenSubJet2Phi;
   OutputTree.Branch("GenSubJet2PT", &TreeGenSubJet2PT, "GenSubJet2PT/D");
   OutputTree.Branch("GenSubJet2Eta", &TreeGenSubJet2Eta, "GenSubJet2Eta/D");
   OutputTree.Branch("GenSubJet2Phi", &TreeGenSubJet2Phi, "GenSubJet2Phi/D");

   double TreeGenWeightedX;
   OutputTree.Branch("GenWeightedX", &TreeGenWeightedX, "GenWeightedX/D");

   double TreeSubJetX1, TreeSubJetX2, TreeSubJetY1, TreeSubJetY2, TreeAverageX, TreeAverageY;
   OutputTree.Branch("SubJetX1", &TreeSubJetX1, "SubJetX1/D");
   OutputTree.Branch("SubJetX2", &TreeSubJetX2, "SubJetX2/D");
   OutputTree.Branch("SubJetY1", &TreeSubJetY1, "SubJetY1/D");
   OutputTree.Branch("SubJetY2", &TreeSubJetY2, "SubJetY2/D");
   OutputTree.Branch("AverageX", &TreeAverageX, "AverageX/D");
   OutputTree.Branch("AverageY", &TreeAverageY, "AverageY/D");

   bool TreeInside;
   OutputTree.Branch("Inside", &TreeInside, "Inside/O");

   double TreeSDMass, TreeGenSDMass;
   OutputTree.Branch("SDMass", &TreeSDMass, "SDMass/D");
   OutputTree.Branch("GenSDMass", &TreeGenSDMass, "GenSDMass/D");

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);
      
      double Centrality = GetCentrality(MHiEvent.hiBin);

      SDJetHelper HSDJet(MSDJet);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.JetPT[i] < 80 || MSDJet.JetPT[i] > 500)
            continue;
         if(MSDJet.JetEta[i] < -1.3 || MSDJet.JetEta[i] > 1.3)
            continue;

         if(HSDJet.GoodRecoSubJet[i] == false)
            continue;
         if(HSDJet.GoodGenSubJet[i] == false)
            continue;

         TreeJetPT = MSDJet.JetPT[i];
         TreeJetEta = MSDJet.JetEta[i];
         TreeJetPhi = MSDJet.JetPhi[i];

         TreeRegion = HSDJet.Region[i];

         TreeSubJet1PT = HSDJet.RecoSubJet1[i].GetPT();
         TreeSubJet1Eta = HSDJet.RecoSubJet1[i].GetEta();
         TreeSubJet1Phi = HSDJet.RecoSubJet1[i].GetPhi();
         TreeSubJet2PT = HSDJet.RecoSubJet2[i].GetPT();
         TreeSubJet2Eta = HSDJet.RecoSubJet2[i].GetEta();
         TreeSubJet2Phi = HSDJet.RecoSubJet2[i].GetPhi();
         
         TreeGenSubJet1PT = HSDJet.GenSubJet1[i].GetPT();
         TreeGenSubJet1Eta = HSDJet.GenSubJet1[i].GetEta();
         TreeGenSubJet1Phi = HSDJet.GenSubJet1[i].GetPhi();
         TreeGenSubJet2PT = HSDJet.GenSubJet2[i].GetPT();
         TreeGenSubJet2Eta = HSDJet.GenSubJet2[i].GetEta();
         TreeGenSubJet2Phi = HSDJet.GenSubJet2[i].GetPhi();

         TreeGenWeightedX = (1 * HSDJet.GenSubJet1[i].GetPT() + (-1) * HSDJet.GenSubJet2[i].GetPT())
            / (HSDJet.GenSubJet1[i].GetPT() + HSDJet.GenSubJet2[i].GetPT());

         TreeSubJetX1 = HSDJet.SubJetX1[i];
         TreeSubJetY1 = HSDJet.SubJetY1[i];
         TreeSubJetX2 = HSDJet.SubJetX2[i];
         TreeSubJetY2 = HSDJet.SubJetY2[i];

         TreeInside = false;
         if((HSDJet.SubJetX2[i] - 1) * (HSDJet.SubJetX2[i] - 1) + HSDJet.SubJetY2[i] * HSDJet.SubJetY2[i] < 2 * 2)
            TreeInside = true;
         if((HSDJet.SubJetX2[i] + 1) * (HSDJet.SubJetX2[i] + 1) + HSDJet.SubJetY2[i] * HSDJet.SubJetY2[i] < 2 * 2)
            TreeInside = true;

         TreeAverageX = (HSDJet.SubJetX1[i] * HSDJet.RecoSubJet1[i].GetPT() + HSDJet.SubJetX2[i] * HSDJet.RecoSubJet2[i].GetPT()) / (HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT());
         TreeAverageY = (HSDJet.SubJetY1[i] * HSDJet.RecoSubJet1[i].GetPT() + HSDJet.SubJetY2[i] * HSDJet.RecoSubJet2[i].GetPT()) / (HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT());

         TreeSDMass = MSDJet.JetM[i];
         TreeGenSDMass = (HSDJet.GenSubJet1[i] + HSDJet.GenSubJet2[i]).GetMass();

         OutputTree.Fill();
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

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





