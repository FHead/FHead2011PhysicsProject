#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

#define MAX 100000

int main(int argc, char *argv[]);
pair<double, double> GetFlow(vector<int> &ID, vector<float> &PT, vector<float> &Eta, vector<float> &Phi,
   double EtaMin, double EtaMax);
int GetMaxIndex(int N, float PT[], float Eta[], double EtaMin, double EtaMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   TFile File("Forest.root");

   TTree *HiTree  = (TTree *)File.Get("hiEvtAnalyzer/HiTree");
   TTree *PFTree  = (TTree *)File.Get("pfcandAnalyzer/pfTree");
   TTree *JetTree = (TTree *)File.Get("akCs4PFJetAnalyzer/t");

   int hiBin;

   HiTree->SetBranchAddress("hiBin", &hiBin);

   vector<int> *pfId = nullptr;
   vector<float> *pfPt = nullptr;
   vector<float> *pfEta = nullptr;
   vector<float> *pfPhi = nullptr;

   PFTree->SetBranchAddress("pfId", &pfId);
   PFTree->SetBranchAddress("pfPt", &pfPt);
   PFTree->SetBranchAddress("pfEta", &pfEta);
   PFTree->SetBranchAddress("pfPhi", &pfPhi);

   int NRef;
   float JetPT[MAX];
   float JetEta[MAX];
   float JetPhi[MAX];

   JetTree->SetBranchAddress("nref", &NRef);
   JetTree->SetBranchAddress("jtpt", &JetPT);
   JetTree->SetBranchAddress("jteta", &JetEta);
   JetTree->SetBranchAddress("jtphi", &JetPhi);

   TFile OutputFile("OutputFile.root", "RECREATE");

   TTree OutputTree("Tree", "Tree");

   double V12, V13, V22, V23, V32, V33, V42, V43;
   double J1PT, J1Eta, J1Phi, J2PT, J2Eta, J2Phi, J0PT, J0Eta, J0Phi;

   OutputTree.Branch("hiBin", &hiBin, "hiBin/I");
   OutputTree.Branch("V12", &V12, "V12/D");
   OutputTree.Branch("V13", &V13, "V13/D");
   OutputTree.Branch("V22", &V22, "V22/D");
   OutputTree.Branch("V23", &V23, "V23/D");
   OutputTree.Branch("V32", &V32, "V32/D");
   OutputTree.Branch("V33", &V33, "V33/D");
   OutputTree.Branch("V42", &V42, "V42/D");
   OutputTree.Branch("V43", &V43, "V43/D");
   OutputTree.Branch("J0PT", &J0PT, "J0PT/D");
   OutputTree.Branch("J0Eta", &J0Eta, "J0Eta/D");
   OutputTree.Branch("J0Phi", &J0Phi, "J0Phi/D");
   OutputTree.Branch("J1PT", &J1PT, "J1PT/D");
   OutputTree.Branch("J1Eta", &J1Eta, "J1Eta/D");
   OutputTree.Branch("J1Phi", &J1Phi, "J1Phi/D");
   OutputTree.Branch("J2PT", &J2PT, "J2PT/D");
   OutputTree.Branch("J2Eta", &J2Eta, "J2Eta/D");
   OutputTree.Branch("J2Phi", &J2Phi, "J2Phi/D");

   int EntryCount = HiTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      HiTree->GetEntry(iE);
      PFTree->GetEntry(iE);
      JetTree->GetEntry(iE);

      pair<double, double> V1 = GetFlow(*pfId, *pfPt, *pfEta, *pfPhi, -2.0, -1.0);
      pair<double, double> V2 = GetFlow(*pfId, *pfPt, *pfEta, *pfPhi, -1.0, -0.0);
      pair<double, double> V3 = GetFlow(*pfId, *pfPt, *pfEta, *pfPhi,  0.0,  1.0);
      pair<double, double> V4 = GetFlow(*pfId, *pfPt, *pfEta, *pfPhi,  1.0,  2.0);

      V12 = V1.first;   V13 = V1.second;
      V22 = V2.first;   V23 = V2.second;
      V32 = V3.first;   V33 = V3.second;
      V42 = V4.first;   V43 = V4.second;

      int I0 = GetMaxIndex(NRef, JetPT, JetEta, -2, 2);
      int I1 = GetMaxIndex(NRef, JetPT, JetEta, -2, -1);
      int I2 = GetMaxIndex(NRef, JetPT, JetEta, 1, 2);

      J0PT = -1, J0Eta = 0, J0Phi = 0;
      J1PT = -1, J1Eta = 0, J1Phi = 0;
      J2PT = -1, J2Eta = 0, J2Phi = 0;

      if(I0 >= 0)
      {
         J0PT = JetPT[I0];
         J0Eta = JetEta[I0];
         J0Phi = JetPhi[I0];
      }
      if(I1 >= 0)
      {
         J1PT = JetPT[I1];
         J1Eta = JetEta[I1];
         J1Phi = JetPhi[I1];
      }
      if(I2 >= 0)
      {
         J2PT = JetPT[I2];
         J2Eta = JetEta[I2];
         J2Phi = JetPhi[I2];
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}

pair<double, double> GetFlow(vector<int> &ID, vector<float> &PT, vector<float> &Eta, vector<float> &Phi,
   double EtaMin, double EtaMax)
{
   int NPF = ID.size();

   TH1D H1("H1", ";;", 10, -M_PI, M_PI);   H1.Sumw2();

   for(int iPF = 0; iPF < NPF; iPF++)
   {
      if(ID[iPF] != 1)
         continue;
      if(PT[iPF] < 0.3 || PT[iPF] > 3)
         continue;

      if(Eta[iPF] > EtaMin && Eta[iPF] < EtaMax)
         H1.Fill(Phi[iPF]);
   }

   bool Good = true;
   for(int i = 1; i <= 10; i++)
      if(H1.GetBinContent(i) < 10)
         Good = false;

   TF1 F("F", "[0]*(1+[1]*cos(2*x)+[2]*sin(2*x)+[3]*cos(3*x)+[4]*sin(3*x))", -M_PI, M_PI);

   H1.Fit(&F);

   double v2 = sqrt(F.GetParameter(1) * F.GetParameter(1) + F.GetParameter(2) * F.GetParameter(2));
   double v3 = sqrt(F.GetParameter(3) * F.GetParameter(3) + F.GetParameter(4) * F.GetParameter(4));

   if(Good == false)
      v2 = -1, v3 = -1;

   return pair<double, double>(v2, v3);
}

int GetMaxIndex(int N, float PT[], float Eta[], double EtaMin, double EtaMax)
{
   int Result = -1;

   for(int i = 0; i < N; i++)
   {
      if(Eta[i] < EtaMin || Eta[i] > EtaMax)
         continue;

      if(Result == -1 || PT[Result] < PT[i])
         Result = i;
   }

   return Result;
}


