#include <cmath>
#include <algorithm>
#include <functional>

#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"

#include "Code/TauHelperFunctions3.h"
#include "Code/DrawRandom.h"

#include "include/RhoCalculator.h"

RhoCalculator::RhoCalculator()
{
   InitializeCMSEtaBins();
   
   MinTowerFraction = 0.7;
   NSigmaPU = 1;
   PUPTMin = 15;
   JetR = 0.3;
   RadiusPU = 0.5;
   SigmaCut = 5.0;
}

void RhoCalculator::InitializeCMSEtaBins()
{
   EtaBinCount = 82;
   EtaBins = 
   {
      0.000, -0.087, -0.174, -0.261, -0.348, -0.435,
      -0.522, -0.609, -0.696, -0.783, -0.870,
      -0.957, -1.044, -1.131, -1.218, -1.305,
      -1.392, -1.479, -1.566, -1.653, -1.740,
      -1.830, -1.930, -2.043, -2.172, -2.322,
      -2.500, -2.650, -2.853, -3.000, -3.139,
      -3.314, -3.489, -3.664, -3.839, -4.013,
      -4.191, -4.363, -4.538, -4.716, -4.889,
      -5.191, 0.087, 0.174, 0.261, 0.348,
      0.435, 0.522, 0.609, 0.696, 0.783,
      0.870, 0.957, 1.044, 1.131, 1.218,
      1.305, 1.392, 1.479, 1.566, 1.653,
      1.740, 1.830, 1.930, 2.043, 2.172,
      2.322, 2.500, 2.650, 2.853, 3.000,
      3.139, 3.314, 3.489, 3.664, 3.839,
      4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191
   };
   sort(EtaBins.begin(), EtaBins.end());

   NTowers =
   {
      18, 18, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 18, 18
   };

   RhoParameters.clear();
   RhoParameters.resize(EtaBins.size() - 1, 0);
}

void RhoCalculator::InitializeCMSReducedEtaBins()
{
   EtaBinCount = 78;
   EtaBins = 
   {
      0.000, -0.087, -0.174, -0.261, -0.348, -0.435,
      -0.522, -0.609, -0.696, -0.783, -0.870,
      -0.957, -1.044, -1.131, -1.218, -1.305,
      -1.392, -1.479, -1.566, -1.653, -1.740,
      -1.830, -1.930, -2.043, -2.172, -2.322,
      -2.500, -3.000, -3.139,
      -3.314, -3.489, -3.664, -3.839, -4.013,
      -4.191, -4.363, -4.538, -4.716, -4.889,
      -5.191, 0.087, 0.174, 0.261, 0.348,
      0.435, 0.522, 0.609, 0.696, 0.783,
      0.870, 0.957, 1.044, 1.131, 1.218,
      1.305, 1.392, 1.479, 1.566, 1.653,
      1.740, 1.830, 1.930, 2.043, 2.172,
      2.322, 2.500, 3.000,
      3.139, 3.314, 3.489, 3.664, 3.839,
      4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191
   };
   sort(EtaBins.begin(), EtaBins.end());

   NTowers =
   {
      18, 18, 36, 36, 36, 36,
      36, 36, 36, 36, 36,
      36, 108, 36,
      36, 36, 36, 36, 36,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      72, 72, 72, 72, 72,
      36, 36, 36, 36, 36,
      36, 108, 36,
      36, 36, 36, 36, 36,
      36, 36, 36, 36, 18, 18
   };

   RhoParameters.clear();
   RhoParameters.resize(EtaBins.size() - 1, 0);
}

std::vector<double> RhoCalculator::CalculateRho(const std::vector<FourVector> &PF)
{
   std::vector<double> &Result = RhoParameters;

   // Basic settings come here
   // double MinTowerFraction = 0.7;
   // double NSigmaPU = 1;
   // double PUPTMin = 15;
   // double JetR = 0.3;
   // double RadiusPU = 0.5;
   // double SigmaCut = 5.0;
   
   // Discretize PF into "towers"
   std::map<std::pair<int, int>, double> PFTowers = DiscretizePF(PF);
   std::map<std::pair<int, int>, double> OriginalPFTowers = PFTowers;

   // Calculate the pedestal
   int NEtaTowers[EtaBinCount] = {0};
   double Sum[EtaBinCount] = {0};
   double Sum2[EtaBinCount] = {0};
   for(auto iter : PFTowers)
   {
      int IEta = iter.first.first;
      int IPhi = iter.first.second;
      double ET = iter.second;

      NEtaTowers[IEta] = NEtaTowers[IEta] + 1;
      Sum[IEta] = Sum[IEta] + ET;
      Sum2[IEta] = Sum2[IEta] + ET * ET;
   }

   double Mean[EtaBinCount] = {0};
   double RMS[EtaBinCount] = {0};
   for(int IEta = 0; IEta < EtaBinCount; IEta++)
   {
      if(NEtaTowers[IEta] == 0)
         continue;
      Mean[IEta] = Sum[IEta] / NTowers[IEta];
      RMS[IEta] = sqrt((Sum2[IEta] - Sum[IEta] * Sum[IEta] / NTowers[IEta]) / (NTowers[IEta]));
   }

   // Subtract the pedestal
   for(std::map<std::pair<int, int>, double>::iterator iter = PFTowers.begin(); iter != PFTowers.end(); iter++)
   {
      int IEta = iter->first.first;
      iter->second = iter->second - Mean[IEta] - RMS[IEta] * NSigmaPU;
      if(iter->second < 0)
         iter->second = 0;
   }

   // Cluster R = 0.3 jets
   fastjet::JetDefinition Definition(fastjet::antikt_algorithm, JetR);
   fastjet::ClusterSequence Sequence(TowerToPseudoJet(PFTowers), Definition);
   std::vector<fastjet::PseudoJet> FastJetJets = fastjet::sorted_by_pt(Sequence.inclusive_jets(PUPTMin));

   /*
   cout << FastJetJets.size() << endl;
   for(int i = 0; i < (int)FastJetJets.size(); i++)
   {
      cout << "J" << i << " " << FastJetJets[i].perp() << " " << FastJetJets[i].eta() << " " << FastJetJets[i].phi() << endl;
   }
   */

   // Find excluded towers overall
   std::vector<std::pair<int, int>> ExcludedTowers;
   int NJettyTowers[EtaBinCount] = {0};
   for(fastjet::PseudoJet Jet : FastJetJets)
   {
      double JetEta = Jet.eta();
      double JetPhi = Jet.phi();

      for(int IEta = 0; IEta < EtaBinCount; IEta++)
      {
         for(int IPhi = 0; IPhi < NTowers[IEta]; IPhi++)
         {
            std::pair<int, int> IEtaIPhi(IEta, IPhi);
            std::pair<double, double> EtaPhi = GetEtaPhi(IEta, IPhi);
            double DR2 = GetDR2(EtaPhi.first, EtaPhi.second, JetEta, JetPhi);

            if(DR2 > RadiusPU * RadiusPU)
               continue;
            if(find(ExcludedTowers.begin(), ExcludedTowers.end(), IEtaIPhi) != ExcludedTowers.end())
               continue;
            if(NTowers[IEta] - NJettyTowers[IEta] <= MinTowerFraction * NTowers[IEta])
               continue;

            NJettyTowers[IEta] = NJettyTowers[IEta] + 1;
            ExcludedTowers.push_back(IEtaIPhi);
         }
      }
   }
   sort(ExcludedTowers.begin(), ExcludedTowers.end());

   // Make a collection of orphaned towers
   std::map<std::pair<int, int>, double> OrphanTowers;
   for(auto iter: OriginalPFTowers)
   {
      if(find(ExcludedTowers.begin(), ExcludedTowers.end(), iter.first) != ExcludedTowers.end())
         continue;
      OrphanTowers.insert(iter);
   }

   /*
   for(auto iter : OrphanTowers)
   {
      int IEta = iter.first.first;
      int IPhi = iter.first.second;
      double ET = iter.second;
      if(ET > 2.5)
      {
         std::pair<double, double> EtaPhi = GetEtaPhi(IEta, IPhi);
         cout << "I " << ET << " " << EtaPhi.first << " " << EtaPhi.second << " " << Mean[IEta] << " " << RMS[IEta] << endl;
      }
   }
   */

   // Let's calculate pedestal again
   int NOrphanTowers[EtaBinCount] = {0};
   double OrphanSum[EtaBinCount] = {0};
   double OrphanSum2[EtaBinCount] = {0};
   std::vector<double> OrphanTop[EtaBinCount];
   for(auto iter : OrphanTowers)
   {
      int IEta = iter.first.first;
      int IPhi = iter.first.second;
      double ET = iter.second;

      NOrphanTowers[IEta] = NOrphanTowers[IEta] + 1;
      OrphanSum[IEta] = OrphanSum[IEta] + ET;
      OrphanSum2[IEta] = OrphanSum2[IEta] + ET * ET;
      OrphanTop[IEta].push_back(ET);
   }

   double OrphanMean[EtaBinCount] = {0};
   double OrphanRMS[EtaBinCount] = {0};
   for(int IEta = 0; IEta < EtaBinCount; IEta++)
   {
      if(NOrphanTowers[IEta] == 0)
         continue;

      int TowerCount = NTowers[IEta] - NJettyTowers[IEta];

      OrphanMean[IEta] = OrphanSum[IEta] / TowerCount;
      OrphanRMS[IEta] = sqrt((OrphanSum2[IEta] - OrphanSum[IEta] * OrphanSum[IEta] / TowerCount) / (TowerCount));

      std::sort(OrphanTop[IEta].begin(), OrphanTop[IEta].end(), std::greater<double>());
      if(OrphanTop[IEta].size() > 4)
         OrphanTop[IEta].erase(OrphanTop[IEta].begin() + 4, OrphanTop[IEta].end());

      // Exclude big towers that are still around that are not in jets
      if(TowerCount > MinTowerFraction * NTowers[IEta])
      {
         int NumberToCheck = std::min(int(OrphanTop[IEta].size()), int(TowerCount - MinTowerFraction * NTowers[IEta]));
         for(int i = 0; i < NumberToCheck; i++)
         {
            if(SigmaCut <= 0)
               continue;
            if(OrphanTop[IEta][i] < OrphanMean[IEta] + SigmaCut * OrphanRMS[IEta])
               continue;

            // Why not subtract Sum^2 as well?  Oh well
            OrphanSum[IEta] = OrphanSum[IEta] - OrphanTop[IEta][i];
            TowerCount = TowerCount - 1;
         }
      }
      
      OrphanMean[IEta] = OrphanSum[IEta] / TowerCount;
      OrphanRMS[IEta] = sqrt((OrphanSum2[IEta] - OrphanSum[IEta] * OrphanSum[IEta] / TowerCount) / (TowerCount));

      double TowerDEta = EtaBins[IEta+1] - EtaBins[IEta];
      double TowerDPhi = 2 * M_PI / NTowers[IEta];

      double Rho = OrphanMean[IEta] / (TowerDEta * TowerDPhi);

      Result[IEta] = Rho;
   }

   return Result;
}

std::map<std::pair<int, int>, double> RhoCalculator::DiscretizePF(const std::vector<FourVector> &PF)
{
   std::map<std::pair<int, int>, double> PFTowers;
   
   for(int i = 0; i < (int)PF.size(); i++)
   {
      std::pair<int, int> EtaPhi = GetIEtaIPhi(PF[i].InnerGetEta(), PF[i].InnerGetPhi());

      if(PFTowers.find(EtaPhi) == PFTowers.end())
         PFTowers.insert(std::pair<std::pair<int, int>, double>(EtaPhi, 0));
      PFTowers[EtaPhi] = PFTowers[EtaPhi] + PF[i].InnerGetET();
   }

   return PFTowers;
}

std::vector<fastjet::PseudoJet> RhoCalculator::TowerToPseudoJet(const std::map<std::pair<int, int>, double> &PFTowers)
{
   std::vector<fastjet::PseudoJet> Result;
   
   for(auto iter : PFTowers)
   {
      std::pair<double, double> EtaPhi = GetEtaPhi(iter.first);
      fastjet::PseudoJet P;
      P.reset_PtYPhiM(iter.second, EtaPhi.first, EtaPhi.second, 0);
      Result.push_back(P);
   }

   return Result;
}

std::pair<int, int> RhoCalculator::GetIEtaIPhi(std::pair<double, double> EtaPhi)
{
   return GetIEtaIPhi(EtaPhi.first, EtaPhi.second);
}

std::pair<int, int> RhoCalculator::GetIEtaIPhi(double Eta, double Phi)
{
   int IEta = (lower_bound(EtaBins.begin(), EtaBins.end(), Eta) - EtaBins.begin()) - 1;
   while(Phi < 0)          Phi = Phi + 2 * M_PI;
   while(Phi > 2 * M_PI)   Phi = Phi - 2 * M_PI;
   int IPhi = (int)(Phi / (2 * M_PI / NTowers[IEta]));

   return std::pair<int, int>(IEta, IPhi);
}

std::pair<double, double> RhoCalculator::GetEtaPhi(std::pair<int, int> IEtaIPhi)
{
   return GetEtaPhi(IEtaIPhi.first, IEtaIPhi.second);
}

std::pair<double, double> RhoCalculator::GetEtaPhi(int IEta, int IPhi)
{
   double Eta = (EtaBins[IEta] + EtaBins[IEta+1]) / 2;
   double Phi = 2 * M_PI / NTowers[IEta] * (IPhi + 0.5);

   return std::pair<double, double>(Eta, Phi);
}

double RhoCalculator::GetDR2(double Eta1, double Phi1, double Eta2, double Phi2)
{
   double DEta = Eta1 - Eta2;
   double DPhi = Phi1 - Phi2;
   while(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   while(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   return DEta * DEta + DPhi * DPhi;
}
   
double RhoCalculator::GetRho(double Eta)
{
   int Index = std::lower_bound(EtaBins.begin(), EtaBins.end(), Eta) - EtaBins.begin();
   if(Index <= 0)
      return 0;
   return RhoParameters[Index-1];
}

void RhoCalculator::SetCMSPreset()
{
   MinTowerFraction = 0.7;
   NSigmaPU = 1;
   PUPTMin = 15;
   JetR = 0.3;
   RadiusPU = 0.5;
   SigmaCut = 5.0;
}

RhoModulationCalculator::RhoModulationCalculator()
{
   SetCMSPreset();
}
   
double RhoModulationCalculator::SetCMSPreset()
{
   AbsEtaMax = 1.0;
   PTMin = 0.3;
   PTMax = 3.0;

   UseExternalPhi = false;
   ExternalPhi2 = 0;
   ExternalPhi3 = 0;

   Parameters.clear();
   Parameters.resize(9);
}

std::vector<double> RhoModulationCalculator::DoRhoModulationFit(const std::vector<FourVector> &PF, bool FloatEventPlane, bool RandomizePhi)
{
   TCanvas Canvas;

   Parameters.clear();
   Parameters.resize(9, 0);
   
   std::vector<double> &Result = Parameters;

   double Phi2 = -100, Phi3 = -100;
   int Stats = 0;

   if(UseExternalPhi == true)
   {
      Phi2 = ExternalPhi2;
      Phi3 = ExternalPhi3;
   }
   else
   {
      double CosPhi2 = 0, SinPhi2 = 0, CosPhi3 = 0, SinPhi3 = 0;
      for(FourVector P : PF)
      {
         if(P.GetAbsEta() > AbsEtaMax)   continue;
         if(P.GetPT() < PTMin)           continue;
         if(P.GetPT() > PTMax)           continue;

         Stats = Stats + 1;

         CosPhi2 = CosPhi2 + cos(2 * P.GetPhi());
         SinPhi2 = SinPhi2 + sin(2 * P.GetPhi());

         CosPhi3 = CosPhi3 + cos(3 * P.GetPhi());
         SinPhi3 = SinPhi3 + sin(3 * P.GetPhi());
      }

      Phi2 = atan2(SinPhi2, CosPhi2) / 2;
      Phi3 = atan2(SinPhi3, CosPhi3) / 3;
   }

   if(Stats >= 100 && Phi2 > -100)
   {
      int BinCount = std::max(10, Stats / 30);

      TH1D HPhi("HPhi", ";#phi;Count", BinCount, -M_PI, M_PI);

      for(FourVector P : PF)
      {
         if(P.GetAbsEta() > AbsEtaMax)   continue;
         if(P.GetPT() < PTMin)           continue;
         if(P.GetPT() > PTMax)           continue;

         if(RandomizePhi == false)
            HPhi.Fill(P.GetPhi());
         else
            HPhi.Fill(DrawRandom(-M_PI, M_PI));
      }

      TF1 FLine("FLine", "[0]", -M_PI, M_PI);
      TF1 FFlow("FFlow", "[0]*(1+2*([1]*cos(2*(x-[2]))+[3]*cos(3*(x-[4]))))", -M_PI, M_PI);

      FFlow.SetParameters(10, 0, Phi2, 0, Phi3);
      FLine.SetParameter(0, 10);
      if(FloatEventPlane == false)
      {
         FFlow.FixParameter(2, Phi2);
         FFlow.FixParameter(4, Phi3);
      }

      HPhi.Fit(&FFlow, "Q", "", -M_PI, M_PI);
      HPhi.Fit(&FLine, "Q", "", -M_PI, M_PI);

      Result[0] = FFlow.GetParameter(0);
      Result[1] = FFlow.GetParameter(1);
      Result[2] = FFlow.GetParameter(2);
      Result[3] = FFlow.GetParameter(3);
      Result[4] = FFlow.GetParameter(4);
      Result[5] = FFlow.GetChisquare();
      Result[6] = BinCount - 3;
      Result[7] = FLine.GetChisquare();
      Result[8] = BinCount - 1;
   }

   return Result;
}
   
double RhoModulationCalculator::GetModulation(double Phi)
{
   double V2Term = Parameters[1] * cos(2 * (Phi - Parameters[2]));
   double V3Term = Parameters[3] * cos(3 * (Phi - Parameters[4]));
   return 1 + 2 * (V2Term + V3Term);
}

