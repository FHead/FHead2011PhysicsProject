#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"

#define MAX 10000

struct Configuration;
int main(int argc, char *argv[]);
void AddPTScans(vector<Configuration> &C);
void AddEtaScans(vector<Configuration> &C);
void AddDPhiScans(vector<Configuration> &C);
void AddCentralityScans(vector<Configuration> &C);

struct Configuration
{
   string Tag;
   double PTMin;
   double PTMax;
   double EtaMin;
   double EtaMax;
   double DPhiMin;
   double DPhiMax;
   double CentralityMin;
   double CentralityMax;
   int BinCount;
   double RangeMin, RangeMax;
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   vector<string> InputFileNames = CL.GetStringVector("input");
   string OutputFileName = CL.Get("output", "result.dh");

   DataHelper DHFile(OutputFileName);

   vector<Configuration> C;
   // AddPTScans(C);
   // AddEtaScans(C);
   AddDPhiScans(C);
   // AddCentralityScans(C);

   vector<TH1D> H;
   for(int iC = 0; iC < (int)C.size(); iC++)
      H.emplace_back(C[iC].Tag.c_str(), "", C[iC].BinCount, C[iC].RangeMin, C[iC].RangeMax);
   
   cout << "[Main] Looping through files..." << endl;
   for(string InputFileName : InputFileNames)
   {
      TFile File(InputFileName.c_str());

      TTree *Tree = (TTree *)File.Get("Tree");
      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      double Centrality;
      Tree->SetBranchAddress("Centrality", &Centrality);

      int NJet;
      double JetPT[MAX], RawPT[MAX], JetEta[MAX], JetPhi[MAX];
      double GenPT[MAX], GenEta[MAX], GenPhi[MAX];
      Tree->SetBranchAddress("NJet", &NJet);
      Tree->SetBranchAddress("JetPT", &JetPT);
      Tree->SetBranchAddress("JetEta", &JetEta);
      Tree->SetBranchAddress("JetPhi", &JetPhi);
      Tree->SetBranchAddress("RawPT", &RawPT);
      Tree->SetBranchAddress("GenPT", &GenPT);
      Tree->SetBranchAddress("GenEta", &GenEta);
      Tree->SetBranchAddress("GenPhi", &GenPhi);

      double V2, Phi2, V3, Phi3;
      Tree->SetBranchAddress("V2", &V2);
      Tree->SetBranchAddress("V3", &V3);
      Tree->SetBranchAddress("Phi2", &Phi2);
      Tree->SetBranchAddress("Phi3", &Phi3);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         for(int iJ = 0; iJ < NJet; iJ++)
         {
            for(int iC = 0; iC < (int)C.size(); iC++)
            {
               if(Centrality < C[iC].CentralityMin || Centrality > C[iC].CentralityMax)
                  continue;
               if(GenPT[iJ] < C[iC].PTMin || GenPT[iJ] > C[iC].PTMax)
                  continue;
               if(GenEta[iJ] < C[iC].EtaMin || GenEta[iJ] > C[iC].EtaMax)
                  continue;

               double DPhi = GenPhi[iJ] - Phi2;
               while(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
               while(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
               if(fabs(DPhi) < C[iC].DPhiMin || fabs(DPhi) > C[iC].DPhiMax)
                  continue;

               H[iC].Fill(JetPT[iJ] / GenPT[iJ]);
            }
         }
      }
      
      File.Close();
   }

   cout << "[Main] dealing with histograms..." << endl;
   for(int iC = 0; iC < (int)C.size(); iC++)
   {
      string State = C[iC].Tag;

      DHFile[State]["CentralityMin"] = C[iC].CentralityMin;
      DHFile[State]["CentralityMax"] = C[iC].CentralityMax;
      DHFile[State]["PTMin"]         = C[iC].PTMin;
      DHFile[State]["PTMax"]         = C[iC].PTMax;
      DHFile[State]["EtaMin"]        = C[iC].EtaMin;
      DHFile[State]["EtaMax"]        = C[iC].EtaMax;
      DHFile[State]["DPhiMin"]       = C[iC].DPhiMin;
      DHFile[State]["DPhiMax"]       = C[iC].DPhiMax;
      DHFile[State]["BinCount"]      = C[iC].BinCount;
      DHFile[State]["RangeMin"]      = C[iC].RangeMin;
      DHFile[State]["RangeMax"]      = C[iC].RangeMax;

      DHFile[State]["N"]             = H[iC].GetEntries();
      DHFile[State]["Mean"]          = H[iC].GetMean();
      DHFile[State]["MeanError"]     = H[iC].GetMeanError();
      DHFile[State]["RMS"]           = H[iC].GetRMS();
      DHFile[State]["RMSError"]      = H[iC].GetRMSError();

      TF1 F("F", "gaus", 0, 2);
      H[iC].Fit(&F, "Q");

      DHFile[State]["P0"]            = F.GetParameter(0);
      DHFile[State]["P1"]            = F.GetParameter(1);
      DHFile[State]["P2"]            = F.GetParameter(2);
      DHFile[State]["P0Error"]       = F.GetParError(0);
      DHFile[State]["P1Error"]       = F.GetParError(1);
      DHFile[State]["P2Error"]       = F.GetParError(2);
      DHFile[State]["Chi2"]          = F.GetChisquare();
   }

   DHFile.SaveToFile();

   return 0;
}

void AddPTScans(vector<Configuration> &C)
{
   cout << "[AddPTScans] Generating configurations..." << endl;

   vector<double> PTBins{30, 40, 50, 60, 70, 85, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600, 800, 1000};
   vector<double> CentralityBins{0.0, 0.1, 0.3, 0.5, 0.8};
   vector<double> EtaBins{0.00, 0.50, 1.00, 1.50, 2.00, 2.50, 3.00};

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = 0.0;
   Default.RangeMax = 2.0;
   Default.DPhiMin = -M_PI;
   Default.DPhiMax = M_PI;

   for(int iPT = 0; iPT + 1 < (int)PTBins.size(); iPT++)
   {
      for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
      {
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            Configuration New = Default;
            New.EtaMin = EtaBins[iEta];
            New.EtaMax = EtaBins[iEta+1];
            New.PTMin = PTBins[iPT];
            New.PTMax = PTBins[iPT+1];
            New.CentralityMin = CentralityBins[iC];
            New.CentralityMax = CentralityBins[iC+1];

            New.Tag = Form("PTScan_PT%d_Eta%d_Centrality%d", iPT, iEta, iC);

            C.push_back(New);
         }
      }
   }
}

void AddEtaScans(vector<Configuration> &C)
{
   cout << "[AddEtaScans] Generating configurations..." << endl;

   vector<double> PTBins{30, 50, 100, 200, 300, 500, 750, 1000};
   vector<double> CentralityBins{0.0, 0.1, 0.3, 0.5, 0.8};
   vector<double> EtaBins{0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90,
      1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90,
      2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00};
   int N = EtaBins.size();
   for(int i = 0; i < N; i++)
      if(EtaBins[i] != 0)
         EtaBins.push_back(-EtaBins[i]);
   sort(EtaBins.begin(), EtaBins.end());

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = 0.0;
   Default.RangeMax = 2.0;
   Default.DPhiMin = -M_PI;
   Default.DPhiMax = M_PI;

   for(int iPT = 0; iPT + 1 < (int)PTBins.size(); iPT++)
   {
      for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
      {
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            Configuration New = Default;
            New.EtaMin = EtaBins[iEta];
            New.EtaMax = EtaBins[iEta+1];
            New.PTMin = PTBins[iPT];
            New.PTMax = PTBins[iPT+1];
            New.CentralityMin = CentralityBins[iC];
            New.CentralityMax = CentralityBins[iC+1];

            New.Tag = Form("EtaScan_PT%d_Eta%d_Centrality%d", iPT, iEta, iC);

            C.push_back(New);
         }
      }
   }
}

void AddDPhiScans(vector<Configuration> &C)
{
   cout << "[AddDPhiScans] Generating configurations..." << endl;

   vector<double> PTBins{30, 50, 100, 200, 300, 500, 750, 1000};
   vector<double> CentralityBins{0.0, 0.1, 0.3, 0.5, 0.8};
   vector<double> EtaBins{0.00, 0.50, 1.00, 1.50, 2.00, 2.50, 3.00};
   vector<double> DPhiBins{0.00, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95, 1.00};

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = 0.0;
   Default.RangeMax = 2.0;

   for(int iPT = 0; iPT + 1 < (int)PTBins.size(); iPT++)
   {
      for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
      {
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            for(int iDPhi = 0; iDPhi + 1 < (int)DPhiBins.size(); iDPhi++)
            {
               Configuration New = Default;
               New.EtaMin = EtaBins[iEta];
               New.EtaMax = EtaBins[iEta+1];
               New.PTMin = PTBins[iPT];
               New.PTMax = PTBins[iPT+1];
               New.DPhiMin = DPhiBins[iDPhi] * M_PI;
               New.DPhiMax = DPhiBins[iDPhi+1] * M_PI;
               New.CentralityMin = CentralityBins[iC];
               New.CentralityMax = CentralityBins[iC+1];

               New.Tag = Form("DPhiScan_PT%d_Eta%d_Centrality%d_DPhi%d", iPT, iEta, iC, iDPhi);

               C.push_back(New);
            }
         }
      }
   }
}

void AddCentralityScans(vector<Configuration> &C)
{
   cout << "[AddCentralityScans] Generating configurations..." << endl;

   vector<double> PTBins{30, 50, 100, 200, 300, 500, 750, 1000};
   vector<double> EtaBins{0.00, 0.50, 1.00, 1.50, 2.00, 2.50, 3.00};
   vector<double> CentralityBins(101);
   for(int iC = 0; iC < (int)CentralityBins.size(); iC++)
      CentralityBins[iC] = iC * 0.01;

   Configuration Default;
   Default.BinCount = 200;
   Default.RangeMin = 0.0;
   Default.RangeMax = 2.0;
   Default.DPhiMin = -M_PI;
   Default.DPhiMax = M_PI;

   for(int iPT = 0; iPT + 1 < (int)PTBins.size(); iPT++)
   {
      for(int iC = 0; iC + 1 < (int)CentralityBins.size(); iC++)
      {
         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            Configuration New = Default;
            New.EtaMin = EtaBins[iEta];
            New.EtaMax = EtaBins[iEta+1];
            New.PTMin = PTBins[iPT];
            New.PTMax = PTBins[iPT+1];
            New.CentralityMin = CentralityBins[iC];
            New.CentralityMax = CentralityBins[iC+1];

            New.Tag = Form("CentralityScan_PT%d_Eta%d_Centrality%d", iPT, iEta, iC);

            C.push_back(New);
         }
      }
   }
}


