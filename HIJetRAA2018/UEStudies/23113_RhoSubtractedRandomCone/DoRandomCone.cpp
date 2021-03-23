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

#define FLOWCOUNT 7

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

   double MaxRadius = *max_element(Radius.begin(), Radius.end());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("RandomConeTree", "");

   double V[3], VError[3], VChi2, VSumPT, VNTrack;
   OutputTree.Branch("V", &V, "V[3]/D");
   OutputTree.Branch("VError", &VError, "VError[3]/D");
   OutputTree.Branch("VChi2", &VChi2, "VChi2/D");
   OutputTree.Branch("VSumPT", &VSumPT, "VSumPT/D");
   OutputTree.Branch("VNTrack", &VNTrack, "VNTrack/D");

   double Eta, Phi;
   int NTry;
   OutputTree.Branch("Eta", &Eta, "Eta/D");
   OutputTree.Branch("Phi", &Phi, "Phi/D");
   OutputTree.Branch("NTry", &NTry, "NTry/I");

   double RhoAtCenter;
   double RhoAtCenterReduced;
   OutputTree.Branch("Rho", &RhoAtCenter, "Rho/D");
   OutputTree.Branch("RhoReduced", &RhoAtCenterReduced, "RhoReduced/D");

   double ExternalPhi2, ExternalPhi3;
   int FlowCount = FLOWCOUNT;
   double Phi2[FLOWCOUNT], Phi3[FLOWCOUNT], V2[FLOWCOUNT], V3[FLOWCOUNT];
   OutputTree.Branch("ExternalPhi2", &ExternalPhi2, "ExternalPhi2/D");
   OutputTree.Branch("ExternalPhi3", &ExternalPhi3, "ExternalPhi3/D");
   OutputTree.Branch("FlowCount", &FlowCount, "FlowCount/I");
   OutputTree.Branch("Phi2", &Phi2, "Phi2[FlowCount]/D");
   OutputTree.Branch("Phi3", &Phi3, "Phi3[FlowCount]/D");
   OutputTree.Branch("V2", &V2, "V2[FlowCount]/D");
   OutputTree.Branch("V3", &V3, "V3[FlowCount]/D");

   double Centrality;
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   vector<double> RSum(Radius.size());
   vector<double> RhoSum(Radius.size());
   vector<double> RhoReducedSum(Radius.size());
   vector<double> RhoPhiSum[FLOWCOUNT];
   for(int iF = 0; iF < FlowCount; iF++)
      RhoPhiSum[iF].resize(Radius.size());
   
   for(int iR = 0; iR < Radius.size(); iR++)
   {
      OutputTree.Branch(Form("R%03dSum", (int)(Radius[iR] * 100)), &RSum[iR], Form("R%03dSum/D", int(Radius[iR] * 100)));
      OutputTree.Branch(Form("Rho%03dSum", (int)(Radius[iR] * 100)), &RhoSum[iR], Form("Rho%03dSum/D", int(Radius[iR] * 100)));
      OutputTree.Branch(Form("RhoReduced%03dSum", (int)(Radius[iR] * 100)), &RhoReducedSum[iR], Form("RhoReduced%03dSum/D", int(Radius[iR] * 100)));
      for(int iF = 0; iF < FlowCount; iF++)
         OutputTree.Branch(Form("RhoPhi%03dFlow%dSum", (int)(Radius[iR] * 100), iF), &RhoPhiSum[iF][iR], Form("RhoPhi%03dFlow%dSum/D", int(Radius[iR] * 100), iF));
   }
   
   vector<FourVector> RVSum(Radius.size());
   vector<FourVector> RhoVSum(Radius.size());
   vector<FourVector> RhoReducedVSum(Radius.size());
   vector<FourVector> RhoPhiVSum[FLOWCOUNT];
   for(int iF = 0; iF < FlowCount; iF++)
      RhoPhiVSum[iF].resize(Radius.size());
   
   RhoCalculator CRho, CRhoReduced;
   RhoModulationCalculator CRhoModulation[FLOWCOUNT];
   
   CRhoReduced.SetReducedEtaBins();

   CRhoModulation[1].SetAbsEtaMax(1.5);
   CRhoModulation[2].SetAbsEtaMax(2.0);
   CRhoModulation[3].SetAbsEtaMax(2.5);
   CRhoModulation[4].SetAbsEtaMax(3.0);
   CRhoModulation[5].SetAbsEtaMax(1.0);
   CRhoModulation[5].SetPTMin(0.5);
   CRhoModulation[6].SetExternalPhi(true);

   for(string FileName : FileNames)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MEvent(InputFile);
      PFTreeMessenger MPF(InputFile);
      TrackTreeMessenger MTrack(InputFile);
      TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");
      SkimTreeMessenger MSkim(InputFile);
      
      if(MEvent.Tree == nullptr)
         continue;

      int EntryCount = MEvent.Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         MEvent.GetEntry(iE);
         MPF.GetEntry(iE);
         MTrack.GetEntry(iE);

         int IV = MTrack.GetBestVertexIndex();
         if(IV >= 0)
         {
            V[0]      = MTrack.xVtx[IV];
            V[1]      = MTrack.yVtx[IV];
            V[2]      = MTrack.zVtx[IV];
            VError[0] = MTrack.xVtxErr[IV];
            VError[1] = MTrack.yVtxErr[IV];
            VError[2] = MTrack.zVtxErr[IV];
            VChi2     = MTrack.normChi2Vtx[IV];
            VSumPT    = MTrack.sumPtVtx[IV];
            VNTrack   = MTrack.nTrkVtx[IV];
         }
         else
         {
            V[0]      = 0;
            V[1]      = 0;
            V[2]      = 0;
            VError[0] = 0;
            VError[1] = 0;
            VError[2] = 0;
            VChi2     = 0;
            VSumPT    = 0;
            VNTrack   = 0;
         }

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
         CRhoReduced.CalculateRho(PF);
         
         if(MEvent.hiNevtPlane >= 16)
         {
            ExternalPhi2 = MEvent.hiEvtPlanes[8];
            ExternalPhi3 = MEvent.hiEvtPlanes[15];
         }
         else
         {
            ExternalPhi2 = -1000;
            ExternalPhi3 = -1000;
         }
         CRhoModulation[6].SetExternalPhi(true, MEvent.hiEvtPlanes[8], MEvent.hiEvtPlanes[15]);
         
         vector<double> Modulation[FLOWCOUNT];
         for(int iF = 0; iF < FlowCount; iF++)
         {
            Modulation[iF] = CRhoModulation[iF].DoRhoModulationFit(PFID1, false, false);

            Phi2[iF] = Modulation[iF][1];
            V2[iF]   = Modulation[iF][2];
            Phi3[iF] = Modulation[iF][3];
            V3[iF]   = Modulation[iF][4];
         }

         for(int iN = 0; iN < NPerEvent; iN++)
         {
            Eta = DrawRandom(-EtaMax, EtaMax);
            Phi = DrawRandom(-M_PI, M_PI);
            NTry = iN;

            RhoAtCenter = CRho.GetRho(Eta);
            RhoAtCenterReduced = CRhoReduced.GetRho(Eta);

            OutputTree.Fill();

            // Calculate random cone sum
            for(int iR = 0; iR < (int)Radius.size(); iR++)
            {
               RVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
               RhoVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
               RhoReducedVSum[iR].SetPtEtaPhiMass(0, 0, 0, 0);
               for(int iF = 0; iF < FlowCount; iF++)
                  RhoPhiVSum[iF][iR].SetPtEtaPhiMass(0, 0, 0, 0);
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
               for(int iF = 0; iF < FlowCount; iF++)
                  RhoPhiSum[iF][iR] = 0;
            }

            for(int iR = 0; iR < (int)Radius.size(); iR++)
            {
               double TotalWeight = 0;
               for(int iRho = 0; iRho < NRho; iRho++)
               {
                  double R = sqrt(DrawRandom(0, Radius[iR]));
                  double A = DrawRandom(-M_PI, M_PI);

                  double DEta = R * cos(A);
                  double DPhi = R * sin(A);

                  double Rho = CRho.GetRho(Eta + DEta);
                  double RhoReduced = CRhoReduced.GetRho(Eta + DEta);

                  FourVector P;

                  P.SetPtEtaPhi(Rho, Eta + DEta, Phi + DPhi);
                  RhoVSum[iR] = RhoVSum[iR] + P;

                  P.SetPtEtaPhi(RhoReduced, Eta + DEta, Phi + DPhi);
                  RhoReducedVSum[iR] = RhoReducedVSum[iR] + P;

                  for(int iF = 0; iF < FlowCount; iF++)
                  {
                     double LocalRho = Rho * CRhoModulation[iF].GetModulation(Phi + DPhi);
                     P.SetPtEtaPhi(LocalRho, Eta + DEta, Phi + DPhi);
                     RhoPhiVSum[iF][iR] = RhoPhiVSum[iF][iR] + P;
                  }

                  TotalWeight = TotalWeight + 1;
               }
               
               RhoSum[iR]        = RhoVSum[iR].GetPT()        / TotalWeight * M_PI * Radius[iR] * Radius[iR];
               RhoReducedSum[iR] = RhoReducedVSum[iR].GetPT() / TotalWeight * M_PI * Radius[iR] * Radius[iR];
               for(int iF = 0; iF < FlowCount; iF++)
                  RhoPhiSum[iF][iR] = RhoPhiVSum[iF][iR].GetPT() / TotalWeight * M_PI * Radius[iR] * Radius[iR];
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


