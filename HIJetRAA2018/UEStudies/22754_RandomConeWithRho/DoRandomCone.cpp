#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"

#include "Messenger.h"
#include "RhoCalculator.h"

#define MAXRHO 100

int main(int argc, char *argv[]);
double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   vector<string> FileNames = CL.GetStringVector("input", vector<string>{});
   string OutputFileName    = CL.Get("output", "Result.root");
   double Fraction          = CL.GetDouble("fraction", 1.00);
   int NPerEvent            = CL.GetInt("n", 10);
   vector<double> Radius    = CL.GetDoubleVector("r", vector<double>{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20});
   double EtaMax            = CL.GetDouble("etamax", 3);
   bool IsData              = CL.GetBool("data", false);

   double MaxRadius = *max_element(Radius.begin(), Radius.end());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("RandomConeTree", "");

   double Eta, Phi;
   int NTry;
   OutputTree.Branch("Eta", &Eta, "Eta/D");
   OutputTree.Branch("Phi", &Phi, "Phi/D");
   OutputTree.Branch("NTry", &NTry, "NTry/I");
   
   int NRho;
   double TreeRho[MAXRHO];
   OutputTree.Branch("NRho", &NRho, "NRho/I");
   OutputTree.Branch("Rho", &TreeRho, "Rho[NRho]/D");

   double Centrality;
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   vector<double> RSum(Radius.size());
   for(int iR = 0; iR < Radius.size(); iR++)
      OutputTree.Branch(Form("R%03dSum", (int)(Radius[iR] * 100)), &RSum[iR], Form("R%03dSum/D", int(Radius[iR] * 100)));
   
   vector<FourVector> RVSum(Radius.size());
         
   RhoCalculator Calculator;
   Calculator.SetCMSPreset();

   for(string FileName : FileNames)
   {
      cout << "Processing file " << FileName << "..." << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MEvent(InputFile);
      PFTreeMessenger MPF(InputFile);

      TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");
      SkimTreeMessenger MSkim(InputFile);
      
      if(MEvent.Tree == nullptr)
         continue;

      int EntryCount = MEvent.Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 500 || (EntryCount % 300 == 0))
            Bar.Print();

         MEvent.GetEntry(iE);
         MPF.GetEntry(iE);

         if(IsData == true)
         {
            MTrigger.GetEntry(iE);
            MSkim.GetEntry(iE);

            if(MTrigger.CheckTrigger("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part0_v1") != 1
               && MTrigger.CheckTrigger("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part0_v1") != 1)
               continue;
            if(MSkim.PassBasicFilterLoose() == false)
               continue;
         }

         Centrality = MEvent.hiBin * 0.005;

         // Do rho calculation
         vector<FourVector> PF(MPF.PT->size());
         for(int iPF = 0; iPF < (int)MPF.PT->size(); iPF++)
         {
            double PFPT = (*MPF.PT)[iPF];
            double PFEta = (*MPF.Eta)[iPF];
            double PFPhi = (*MPF.Phi)[iPF];
            PF[iPF].SetPtEtaPhi(PFPT, PFEta, PFPhi);
         }
         vector<double> Rho = Calculator.CalculateRho(PF);
         NRho = min(MAXRHO, (int)Rho.size());
         for(int i = 0; i < NRho; i++)
            TreeRho[i] = Rho[i];

         // Do random cone calculation
         for(int iN = 0; iN < NPerEvent; iN++)
         {
            Eta = DrawRandom(-EtaMax, EtaMax);
            Phi = DrawRandom(-M_PI, M_PI);
            NTry = iN;

            OutputTree.Fill();

            for(int iR = 0; iR < (int)Radius.size(); iR++)
               RVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
            
            for(int iPF = 0; iPF < (int)MPF.PT->size(); iPF++)
            {
               double PFPT = (*MPF.PT)[iPF];
               double PFEta = (*MPF.Eta)[iPF];
               double PFPhi = (*MPF.Phi)[iPF];

               double DR2 = GetDR2(PFEta, PFPhi, Eta, Phi);

               if(DR2 > MaxRadius * MaxRadius)
                  continue;

               FourVector P;
               P.SetPtEtaPhiMass(PFPT, PFEta, PFPhi);

               for(int iR = 0; iR < (int)Radius.size(); iR++)
               {
                  if(DR2 < Radius[iR] * Radius[iR])
                     RVSum[iR] = RVSum[iR] + P;
               }
            }

            for(int iR = 0; iR < (int)Radius.size(); iR++)
               RSum[iR] = RVSum[iR].GetPT();

            OutputTree.Fill();
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();
   
   return 0;
}

double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2)
{
   double DEta = Eta1 - Eta2;
   double DPhi = Phi1 - Phi2;
   if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   return DEta * DEta + DPhi * DPhi;
}


