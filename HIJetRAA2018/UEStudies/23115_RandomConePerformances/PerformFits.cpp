#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TH1D.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "ProgressBar.h"

#define MAX 20

struct Configuration;
int main(int argc, char *argv[]);
void AddEtaScans(vector<Configuration> &C);
void AddDPhiScans(vector<Configuration> &C);
void AddCentralityScans(vector<Configuration> &C);
void PerformFits(vector<Configuration> &C, string InputFileName, string DHFileName, bool AdjustRange);

struct Configuration
{
   int RadiusIndex;
   enum RandomConeType {NoPhi = -2, EtaReduced = -1, Phi0 = 0, Phi1 = 1, Phi2 = 2, Phi3 = 3, Phi4 = 4, Phi5 = 5}
      RandomConeIndex;
   double EtaMin, EtaMax;
   double CentralityMin, CentralityMax;
   enum DPhiType {None = -1, DPhi0 = 0, DPhi1 = 1, DPhi2 = 2, DPhi3 = 3, DPhi4 = 4, DPhi5 = 5}
      DPhiIndex;
   double DPhiMin, DPhiMax;
   int BinCount;
   double RangeMin, RangeMax;
   string Tag;
};

int main(int argc, char *argv[])
{
   cout << "Warning!  Phi & V switch assumed." << endl;

   CommandLine CL(argc, argv);

   string InputFileName   = CL.Get("input");
   string VerboseFileName = CL.Get("output", "Meow.pdf");
   string DHFileName      = CL.Get("dhfile", "Fits.dh");

   vector<Configuration> Configurations;
   // AddEtaScans(Configurations);
   // AddDPhiScans(Configurations);
   AddCentralityScans(Configurations);
   
   PerformFits(Configurations, InputFileName, DHFileName, true);
   PerformFits(Configurations, InputFileName, DHFileName, false);
   
   return 0;
}

void AddEtaScans(vector<Configuration> &C)
{
   cout << "[AddEtaScans] Generating configurations..." << endl;

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   vector<double> CentralityBins{0.0, 0.1, 0.3, 0.5, 0.8};
   vector<double> EtaBins{0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90,
      1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90,
      2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00};

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = -80;
   Default.RangeMax = 200;
   Default.DPhiMin = -M_PI;
   Default.DPhiMax = M_PI;

   for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         string RString = Form("%03d", int(Radius[iR] * 100));
         
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            Configuration New = Default;
            New.RadiusIndex = iR;
            New.EtaMin = EtaBins[iEta];
            New.EtaMax = EtaBins[iEta+1];
            New.CentralityMin = CentralityBins[iC];
            New.CentralityMax = CentralityBins[iC+1];
            New.DPhiIndex = Configuration::None;
            
            New.RandomConeIndex = Configuration::NoPhi;
            New.Tag = Form("RhoEta_R%d_C%d_Eta%d", iR, iC, iEta);
            C.push_back(New);
            
            New.RandomConeIndex = Configuration::EtaReduced;
            New.Tag = Form("RhoReducedEta_R%d_C%d_Eta%d", iR, iC, iEta);
            C.push_back(New);

            for(int iF = 0; iF < 6; iF++)
            {
               New.RandomConeIndex = static_cast<Configuration::RandomConeType>(iF);
               New.Tag = Form("RhoPhiEta_F%d_R%d_C%d_Eta%d", iF, iR, iC, iEta);
               C.push_back(New);
            }
         }
      }
   }
}

void AddDPhiScans(vector<Configuration> &C)
{
   cout << "[AddDPhiScans] Generating configurations..." << endl;

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   vector<double> CentralityBins{0.0, 0.1, 0.3, 0.5};
   vector<double> EtaBins{0.00, 1.00, 2.00, 2.50, 3.00};
   vector<double> DPhiBins{0.00, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95, 1.00};

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = -80;
   Default.RangeMax = 200;

   for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         string RString = Form("%03d", int(Radius[iR] * 100));
         
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            for(int iDPhi = 0; iDPhi + 1 < (int)DPhiBins.size(); iDPhi++)
            {
               Configuration New = Default;
               New.RadiusIndex = iR;
               New.EtaMin = EtaBins[iEta];
               New.EtaMax = EtaBins[iEta+1];
               New.CentralityMin = CentralityBins[iC];
               New.CentralityMax = CentralityBins[iC+1];
               New.DPhiMin = DPhiBins[iDPhi] * M_PI;
               New.DPhiMax = DPhiBins[iDPhi+1] * M_PI;

               New.RandomConeIndex = Configuration::NoPhi;
               New.DPhiIndex = Configuration::DPhi0;
               New.Tag = Form("RhoDPhi_R%d_C%d_Eta%d_DPhi%d", iR, iC, iEta, iDPhi);
               C.push_back(New);

               New.RandomConeIndex = Configuration::EtaReduced;
               New.DPhiIndex = Configuration::DPhi0;
               New.Tag = Form("RhoReducedDPhi_R%d_C%d_Eta%d_DPhi%d", iR, iC, iEta, iDPhi);
               C.push_back(New);

               for(int iF = 0; iF < 6; iF++)
               {
                  New.RandomConeIndex = static_cast<Configuration::RandomConeType>(iF);
                  New.DPhiIndex = static_cast<Configuration::DPhiType>(iF);
                  New.Tag = Form("RhoPhiDPhi_F%d_R%d_C%d_Eta%d_DPhi%d", iF, iR, iC, iEta, iDPhi);
                  C.push_back(New);
               }
            }
         }
      }
   }
}

void AddCentralityScans(vector<Configuration> &C)
{
   cout << "[AddCentralityScans] Generating configurations..." << endl;

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   vector<double> CentralityBins(101);
   vector<double> EtaBins{0.00, 1.00, 2.00, 2.50, 3.00};

   for(int iC = 0; iC < (int)CentralityBins.size(); iC++)
      CentralityBins[iC] = iC * 0.01;

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = -80;
   Default.RangeMax = 200;
   Default.DPhiMin = -M_PI;
   Default.DPhiMax = M_PI;

   for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         string RString = Form("%03d", int(Radius[iR] * 100));

         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            Configuration New = Default;
            New.RadiusIndex = iR;
            New.EtaMin = EtaBins[iEta];
            New.EtaMax = EtaBins[iEta+1];
            New.CentralityMin = CentralityBins[iC];
            New.CentralityMax = CentralityBins[iC+1];
            New.DPhiIndex = Configuration::None;
            
            New.RandomConeIndex = Configuration::NoPhi;
            New.Tag = Form("RhoCentrality_R%d_C%d_Eta%d", iR, iC, iEta);
            C.push_back(New);
            
            New.RandomConeIndex = Configuration::EtaReduced;
            New.Tag = Form("RhoReducedCentrality_R%d_C%d_Eta%d", iR, iC, iEta);
            C.push_back(New);

            for(int iF = 0; iF < 6; iF++)
            {
               New.RandomConeIndex = static_cast<Configuration::RandomConeType>(iF);
               New.Tag = Form("RhoPhiCentrality_F%d_R%d_C%d_Eta%d", iF, iR, iC, iEta);
               C.push_back(New);
            }
         }
      }
   }
}

void PerformFits(vector<Configuration> &C, string InputFileName, string DHFileName, bool AdjustRange)
{
   cout << "[PerformFits] Generating histograms.  N = " << C.size() << endl;
   
   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   
   DataHelper DHFile(DHFileName);

   TFile File(InputFileName.c_str());
   TTree *Tree = (TTree *)File.Get("RandomConeTree");
   Assert(Tree != nullptr, "Input tree not fonud!");

   int NConfiguration = C.size();

   vector<TH1D> H;
   for(int iC = 0; iC < (int)C.size(); iC++)
      H.emplace_back(TH1D(C[iC].Tag.c_str(), "", C[iC].BinCount, C[iC].RangeMin, C[iC].RangeMax));

   double Eta, Phi;
   Tree->SetBranchAddress("Eta", &Eta);
   Tree->SetBranchAddress("Phi", &Phi);
   
   double Phi2[MAX], Phi3[MAX], V2[MAX], V3[MAX];
   Tree->SetBranchAddress("Phi2", &V2);
   Tree->SetBranchAddress("Phi3", &V3);
   Tree->SetBranchAddress("V2", &Phi2);
   Tree->SetBranchAddress("V3", &Phi3);

   double Centrality;
   Tree->SetBranchAddress("Centrality", &Centrality);

   double RSum[MAX];
   double RhoSum[MAX];
   double RhoReducedSum[MAX];
   double RhoPhiSum[MAX][MAX];

   for(int iR = 0; iR < (int)Radius.size(); iR++)
   {
      Tree->SetBranchAddress(Form("R%03dSum", (int)(Radius[iR] * 100)), &RSum[iR]);
      Tree->SetBranchAddress(Form("Rho%03dSum", (int)(Radius[iR] * 100)), &RhoSum[iR]);
      Tree->SetBranchAddress(Form("RhoReduced%03dSum", (int)(Radius[iR] * 100)), &RhoReducedSum[iR]);
      for(int iF = 0; iF < 6; iF++)
         Tree->SetBranchAddress(Form("RhoPhi%03dFlow%dSum", (int)(Radius[iR] * 100), iF), &RhoPhiSum[iR][iF]);
   }

   cout << "[PerformFits] Filling histograms..." << endl;
   
   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      if(EntryCount < 500 || (iE % 300) == 0)
         Bar.Print();

      Tree->GetEntry(iE);

      for(int iC = 0; iC < NConfiguration; iC++)
      {
         if(Centrality >= C[iC].CentralityMax)   continue;
         if(Centrality < C[iC].CentralityMin)    continue;
         if(Eta > C[iC].EtaMax)    continue;
         if(Eta < C[iC].EtaMin)    continue;

         int iR = C[iC].RadiusIndex;

         double RC = 0;
         if(C[iC].RandomConeIndex == Configuration::NoPhi)        RC = RhoSum[iR];
         if(C[iC].RandomConeIndex == Configuration::EtaReduced)   RC = RhoReducedSum[iR];
         if(C[iC].RandomConeIndex == Configuration::Phi0)         RC = RhoPhiSum[iR][0];
         if(C[iC].RandomConeIndex == Configuration::Phi1)         RC = RhoPhiSum[iR][1];
         if(C[iC].RandomConeIndex == Configuration::Phi2)         RC = RhoPhiSum[iR][2];
         if(C[iC].RandomConeIndex == Configuration::Phi3)         RC = RhoPhiSum[iR][3];
         if(C[iC].RandomConeIndex == Configuration::Phi4)         RC = RhoPhiSum[iR][4];
         if(C[iC].RandomConeIndex == Configuration::Phi5)         RC = RhoPhiSum[iR][5];

         double DPhi = 0;
         if(C[iC].DPhiIndex == Configuration::DPhi0)   DPhi = Phi - Phi2[0];
         if(C[iC].DPhiIndex == Configuration::DPhi1)   DPhi = Phi - Phi2[1];
         if(C[iC].DPhiIndex == Configuration::DPhi2)   DPhi = Phi - Phi2[2];
         if(C[iC].DPhiIndex == Configuration::DPhi3)   DPhi = Phi - Phi2[3];
         if(C[iC].DPhiIndex == Configuration::DPhi4)   DPhi = Phi - Phi2[4];
         if(C[iC].DPhiIndex == Configuration::DPhi5)   DPhi = Phi - Phi2[5];
         if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
         if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

         if(C[iC].DPhiIndex != Configuration::None && fabs(DPhi) >= C[iC].DPhiMax)   continue;
         if(C[iC].DPhiIndex != Configuration::None && fabs(DPhi) < C[iC].DPhiMin)    continue;

         H[iC].Fill(RSum[iR] - RC);
      }
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();
   
   cout << "[PerformFits] Fitting histograms..." << endl;
   
   for(int iC = 0; iC < NConfiguration; iC++)
   {
      TF1 F("F", "gaus");

      double FitMin = C[iC].RangeMin;
      double FitMax = C[iC].RangeMax;
      double BinWidth = (C[iC].RangeMax - C[iC].RangeMin) / C[iC].BinCount;

      if(AdjustRange == true)
      {
         H[iC].Fit(&F, "Q", "", FitMin, FitMax);
         C[iC].RangeMax = F.GetParameter(1) + 10 * F.GetParameter(2);
         C[iC].RangeMin = F.GetParameter(1) - 5 * F.GetParameter(2);
      }
      else
      {
         for(int iT = 0; iT < 5; iT++)
         {
            H[iC].Fit(&F, "Q", "", FitMin, FitMax);
            FitMax = F.GetParameter(1) + F.GetParameter(2);
            FitMin = F.GetParameter(1) - 5 * F.GetParameter(2);
         }
      }

      DHFile[C[iC].Tag]["FitMin"] = FitMin;
      DHFile[C[iC].Tag]["FitMax"] = FitMax;
      DHFile[C[iC].Tag]["RangeMin"] = C[iC].RangeMin;
      DHFile[C[iC].Tag]["RangeMax"] = C[iC].RangeMax;
      DHFile[C[iC].Tag]["EtaMin"] = C[iC].EtaMin;
      DHFile[C[iC].Tag]["EtaMax"] = C[iC].EtaMax;
      DHFile[C[iC].Tag]["DPhiMin"] = C[iC].DPhiMin;
      DHFile[C[iC].Tag]["DPhiMax"] = C[iC].DPhiMax;
      DHFile[C[iC].Tag]["CentralityMin"] = C[iC].CentralityMin;
      DHFile[C[iC].Tag]["CentralityMax"] = C[iC].CentralityMax;
      DHFile[C[iC].Tag]["NBin"] = C[iC].BinCount;
      DHFile[C[iC].Tag]["P0"] = F.GetParameter(0);
      DHFile[C[iC].Tag]["P1"] = F.GetParameter(1);
      DHFile[C[iC].Tag]["P2"] = F.GetParameter(2);
      DHFile[C[iC].Tag]["P0Error"] = F.GetParError(0);
      DHFile[C[iC].Tag]["P1Error"] = F.GetParError(1);
      DHFile[C[iC].Tag]["P2Error"] = F.GetParError(2);
      DHFile[C[iC].Tag]["Chi2"] = F.GetChisquare();
      DHFile[C[iC].Tag]["Ndof"] = (FitMax - FitMin) / BinWidth - 3;
   }

   File.Close();

   DHFile.SaveToFile(DHFileName);
}

