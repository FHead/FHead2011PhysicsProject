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

#include "Messenger.h"
#include "RhoCalculator.h"

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
   int NRho                 = CL.GetInt("nrho", 50);
   int NRhoPhi              = CL.GetInt("nrhophi", 50);
   bool DoGrid              = CL.GetBool("dogrid", false);
   bool DoReduced           = CL.GetBool("doreduced", false);

   double MaxRadius = *max_element(Radius.begin(), Radius.end());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("RandomConeTree", "");

   double Eta, Phi;
   int NTry;
   OutputTree.Branch("Eta", &Eta, "Eta/D");
   OutputTree.Branch("Phi", &Phi, "Phi/D");
   OutputTree.Branch("NTry", &NTry, "NTry/I");

   double RhoAtCenter;
   OutputTree.Branch("Rho", &RhoAtCenter, "Rho/D");

   double Phi2, Phi3, V2, V3;
   OutputTree.Branch("Phi2", &Phi2, "Phi2/D");
   OutputTree.Branch("Phi3", &Phi3, "Phi3/D");
   OutputTree.Branch("V2", &V2, "V2/D");
   OutputTree.Branch("V3", &V3, "V3/D");

   double Centrality;
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   vector<double> RSum(Radius.size());
   vector<double> RhoSum(Radius.size());
   vector<double> RhoPhiSum(Radius.size());
   for(int iR = 0; iR < Radius.size(); iR++)
   {
      OutputTree.Branch(Form("R%03dSum", (int)(Radius[iR] * 100)), &RSum[iR], Form("R%03dSum/D", int(Radius[iR] * 100)));
      OutputTree.Branch(Form("Rho%03dSum", (int)(Radius[iR] * 100)), &RhoSum[iR], Form("Rho%03dSum/D", int(Radius[iR] * 100)));
      OutputTree.Branch(Form("RhoPhi%03dSum", (int)(Radius[iR] * 100)), &RhoPhiSum[iR], Form("RhoPhi%03dSum/D", int(Radius[iR] * 100)));
   }
   
   vector<FourVector> RVSum(Radius.size());
   vector<FourVector> RhoVSum(Radius.size());
   vector<FourVector> RhoPhiVSum(Radius.size());
   
   RhoCalculator CRho;
   RhoModulationCalculator CRhoModulation;
   
   if(DoReduced == true)
      CRho.SetReducedEtaBins();

   for(string FileName : FileNames)
   {
      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MEvent(InputFile);
      PFTreeMessenger MPF(InputFile);

      TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");
      SkimTreeMessenger MSkim(InputFile);
      
      if(MEvent.Tree == nullptr)
         continue;

      int EntryCount = MEvent.Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
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

         vector<FourVector> PF, PFID1;
         for(int iPF = 0; iPF < (int)MPF.PT->size(); iPF++)
         {
            FourVector P;
            P.SetPtEtaPhiMass((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF], 0.135);
            PF.push_back(P);
            if((*MPF.ID)[iPF] == 1)
               PFID1.push_back(P);
         }

         CRho.CalculateRho(PF);
         vector<double> Modulation = CRhoModulation.DoRhoModulationFit(PFID1, false, false);

         Phi2 = Modulation[1];
         V2   = Modulation[2];
         Phi3 = Modulation[3];
         V3   = Modulation[4];

         for(int iN = 0; iN < NPerEvent; iN++)
         {
            Eta = DrawRandom(-EtaMax, EtaMax);
            Phi = DrawRandom(-M_PI, M_PI);
            NTry = iN;

            RhoAtCenter = CRho.GetRho(Eta);

            OutputTree.Fill();

            // Calculate random cone sum
            for(int iR = 0; iR < (int)Radius.size(); iR++)
            {
               RVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
               RhoVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
               RhoPhiVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
            }
            
            for(auto P : PF)
            {
               double PFPT  = P.GetPT();
               double PFEta = P.GetEta();
               double PFPhi = P.GetPhi();

               double DR2 = GetDR2(PFEta, PFPhi, Eta, Phi);

               if(DR2 > MaxRadius * MaxRadius)
                  continue;

               for(int iR = 0; iR < (int)Radius.size(); iR++)
               {
                  if(DR2 < Radius[iR] * Radius[iR])
                     RVSum[iR] = RVSum[iR] + P;
               }
            }

            for(int iR = 0; iR < (int)Radius.size(); iR++)
               RSum[iR] = RVSum[iR].GetPT();
            
            // Calculate rho x A
            for(int iR = 0; iR < (int)Radius.size(); iR++)
            {
               RhoSum[iR] = 0;
               RhoPhiSum[iR] = 0;
            }

            for(int iR = 0; iR < (int)Radius.size(); iR++)
            {
               double TotalWeight = 0;
               for(int iRho = 0; iRho < NRho; iRho++)
               {
                  if(DoGrid == true)
                  {
                     double RhoEta = Eta - Radius[iR] + (2 * Radius[iR]) / NRho * (iRho + 0.5);
                     double RhoPhiSize = 2 * sqrt(Radius[iR] * Radius[iR] - (RhoEta - Eta) * (RhoEta - Eta));

                     double Rho = CRho.GetRho(RhoEta);

                     double PhiMax = Phi + RhoPhiSize / 2;
                     double PhiMin = Phi - RhoPhiSize / 2;

                     double ModulationWeight = 0;
                     double ModulationWeightNoPhi = 0;
                     for(int i = 0; i < NRhoPhi; i++)
                     {
                        double RhoPhi = (PhiMax - PhiMin) / NRhoPhi * (i + 0.5) + PhiMin;
                        double LocalRho = CRhoModulation.GetModulation(RhoPhi);
                        double R = sqrt((RhoPhi - Phi) * (RhoPhi - Phi) + (RhoEta - Eta) * (RhoEta - Eta));
                        ModulationWeight      = ModulationWeight      + cos(R) * LocalRho;
                        ModulationWeightNoPhi = ModulationWeightNoPhi + cos(R);
                     }
                     ModulationWeight      = ModulationWeight      / NRhoPhi * RhoPhiSize;
                     ModulationWeightNoPhi = ModulationWeightNoPhi / NRhoPhi * RhoPhiSize;

                     RhoSum[iR]    = RhoSum[iR]    + Rho * ModulationWeightNoPhi;
                     RhoPhiSum[iR] = RhoPhiSum[iR] + Rho * ModulationWeight;

                     TotalWeight = TotalWeight + RhoPhiSize;
                  }
                  else   // Do random
                  {
                     double R = sqrt(DrawRandom(0, Radius[iR]));
                     double A = DrawRandom(-M_PI, M_PI);

                     double DEta = R * cos(A);
                     double DPhi = R * sin(A);

                     double Rho = CRho.GetRho(Eta + DEta);
                     double LocalRho = Rho * CRhoModulation.GetModulation(Phi + DPhi);

                     FourVector P;
                     
                     P.SetPtEtaPhi(Rho, Eta + DEta, Phi + DPhi);
                     RhoVSum[iR] = RhoVSum[iR] + P;
                     
                     P.SetPtEtaPhi(LocalRho, Eta + DEta, Phi + DPhi);
                     RhoPhiVSum[iR] = RhoPhiVSum[iR] + P;

                     TotalWeight = TotalWeight + 1;
                  }
               }
               
               if(DoGrid == true)
               {
                  RhoSum[iR]    = RhoSum[iR]    / TotalWeight * M_PI * Radius[iR] * Radius[iR];
                  RhoPhiSum[iR] = RhoPhiSum[iR] / TotalWeight * M_PI * Radius[iR] * Radius[iR];
               }
               else
               {
                  RhoSum[iR]    = RhoVSum[iR].GetPT()    / TotalWeight * M_PI * Radius[iR] * Radius[iR];
                  RhoPhiSum[iR] = RhoPhiVSum[iR].GetPT() / TotalWeight * M_PI * Radius[iR] * Radius[iR];
               }
            }

            OutputTree.Fill();
         }
      }
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


