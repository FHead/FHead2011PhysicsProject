class RhoCalculator;

class RhoCalculator
{
private:
   const int EtaBinCount = 82;
   vector<double> EtaBins;
   vector<double> NTowers;
   double MinTowerFraction;
   double NSigmaPU;
   double PUPTMin;
   double JetR;
   double RadiusPU;
   double SigmaCut;
private:
   map<pair<int, int>, double> DiscretizePF(vector<FourVector> &PF);
   vector<PseudoJet> TowerToPseudoJet(const map<pair<int, int>, double> &PFTowers);
   pair<int, int> GetIEtaIPhi(pair<double, double> EtaPhi);
   pair<int, int> GetIEtaIPhi(double Eta, double Phi);
   pair<double, double> GetEtaPhi(pair<int, int> IEtaIPhi);
   pair<double, double> GetEtaPhi(int IEta, int IPhi);
   double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2);
public:
   RhoCalculator();
   vector<double> CalculateRho(vector<FourVector> &PF);
   void SetMinTowerFraction(double fraction = 0.7) { MinTowerFraction = fraction; }
   void SetNSigmaPU(double nsigmapu = 1)           { NSigmaPU = nsigmapu; }
   void SetPUPTMin(double PUPTMin = 15)            { PUPTMin = PUPTMin; }
   void SetJetR(double JetR = 0.3)                 { JetR = JetR; }
   void SetRadiusPU(double RadiusPU = 0.5)         { RadiusPU = RadiusPU; }
   void SetSigmaCut(double SigmaCut = 5.0)         { SigmaCut = SigmaCut; }
};




RhoCalculator::RhoCalculator()
{
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

   MinTowerFraction = 0.7;
   NSigmaPU = 1;
   PUPTMin = 15;
   JetR = 0.3;
   RadiusPU = 0.5;
   SigmaCut = 5.0;
}

vector<double> RhoCalculator::CalculateRho(vector<FourVector> &PF)
{
   vector<double> Result(EtaBinCount);

   // Basic settings come here
   double MinTowerFraction = 0.7;
   double NSigmaPU = 1;
   double PUPTMin = 15;
   double JetR = 0.3;
   double RadiusPU = 0.5;
   double SigmaCut = 5.0;
   
   // Discretize PF into "towers"
   map<pair<int, int>, double> PFTowers = DiscretizePF(PF);
   map<pair<int, int>, double> OriginalPFTowers = PFTowers;

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
   for(map<pair<int, int>, double>::iterator iter = PFTowers.begin(); iter != PFTowers.end(); iter++)
   {
      int IEta = iter->first.first;
      iter->second = iter->second - Mean[IEta] - RMS[IEta] * NSigmaPU;
      if(iter->second < 0)
         iter->second = 0;
   }

   // Cluster R = 0.3 jets
   JetDefinition Definition(antikt_algorithm, JetR);
   ClusterSequence Sequence(TowerToPseudoJet(PFTowers), Definition);
   vector<PseudoJet> FastJetJets = sorted_by_pt(Sequence.inclusive_jets(PUPTMin));

   cout << FastJetJets.size() << endl;
   for(int i = 0; i < (int)FastJetJets.size(); i++)
   {
      cout << "J" << i << " " << FastJetJets[i].perp() << " " << FastJetJets[i].eta() << " " << FastJetJets[i].phi() << endl;
   }

   // Find excluded towers overall
   vector<pair<int, int>> ExcludedTowers;
   int NJettyTowers[EtaBinCount] = {0};
   for(PseudoJet Jet : FastJetJets)
   {
      double JetEta = Jet.eta();
      double JetPhi = Jet.phi();

      for(int IEta = 0; IEta < EtaBinCount; IEta++)
      {
         for(int IPhi = 0; IPhi < NTowers[IEta]; IPhi++)
         {
            pair<int, int> IEtaIPhi(IEta, IPhi);
            pair<double, double> EtaPhi = GetEtaPhi(IEta, IPhi);
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
   map<pair<int, int>, double> OrphanTowers;
   for(auto iter: OriginalPFTowers)
   {
      if(find(ExcludedTowers.begin(), ExcludedTowers.end(), iter.first) != ExcludedTowers.end())
         continue;
      OrphanTowers.insert(iter);
   }

   for(auto iter : OrphanTowers)
   {
      int IEta = iter.first.first;
      int IPhi = iter.first.second;
      double ET = iter.second;
      if(ET > 2.5)
      {
         pair<double, double> EtaPhi = GetEtaPhi(IEta, IPhi);
         cout << "I " << ET << " " << EtaPhi.first << " " << EtaPhi.second << " " << Mean[IEta] << " " << RMS[IEta] << endl;
      }
   }

   // Let's calculate pedestal again
   int NOrphanTowers[EtaBinCount] = {0};
   double OrphanSum[EtaBinCount] = {0};
   double OrphanSum2[EtaBinCount] = {0};
   vector<double> OrphanTop[EtaBinCount];
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

      sort(OrphanTop[IEta].begin(), OrphanTop[IEta].end(), greater<double>());
      if(OrphanTop[IEta].size() > 4)
         OrphanTop[IEta].erase(OrphanTop[IEta].begin() + 4, OrphanTop[IEta].end());

      // Exclude big towers that are still around that are not in jets
      if(TowerCount > MinTowerFraction * NTowers[IEta])
      {
         int NumberToCheck = min(int(OrphanTop[IEta].size()), int(TowerCount - MinTowerFraction * NTowers[IEta]));
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

map<pair<int, int>, double> RhoCalculator::DiscretizePF(vector<FourVector> &PF)
{
   map<pair<int, int>, double> PFTowers;
   
   for(int i = 0; i < (int)PF.size(); i++)
   {
      pair<int, int> EtaPhi = GetIEtaIPhi(PF[i].GetEta(), PF[i].GetPhi());

      if(PFTowers.find(EtaPhi) == PFTowers.end())
         PFTowers.insert(pair<pair<int, int>, double>(EtaPhi, 0));
      PFTowers[EtaPhi] = PFTowers[EtaPhi] + PF[i].GetET();
   }

   return PFTowers;
}

vector<PseudoJet> RhoCalculator::TowerToPseudoJet(const map<pair<int, int>, double> &PFTowers)
{
   vector<PseudoJet> Result;
   
   for(auto iter : PFTowers)
   {
      pair<double, double> EtaPhi = GetEtaPhi(iter.first);
      PseudoJet P;
      P.reset_PtYPhiM(iter.second, EtaPhi.first, EtaPhi.second, 0);
      Result.push_back(P);
   }

   return Result;
}

pair<int, int> RhoCalculator::GetIEtaIPhi(pair<double, double> EtaPhi)
{
   return GetIEtaIPhi(EtaPhi.first, EtaPhi.second);
}

pair<int, int> RhoCalculator::GetIEtaIPhi(double Eta, double Phi)
{
   int IEta = (lower_bound(EtaBins.begin(), EtaBins.end(), Eta) - EtaBins.begin()) - 1;
   while(Phi < 0)          Phi = Phi + 2 * M_PI;
   while(Phi > 2 * M_PI)   Phi = Phi - 2 * M_PI;
   int IPhi = (int)(Phi / (2 * M_PI / NTowers[IEta]));

   return pair<int, int>(IEta, IPhi);
}

pair<double, double> RhoCalculator::GetEtaPhi(pair<int, int> IEtaIPhi)
{
   return GetEtaPhi(IEtaIPhi.first, IEtaIPhi.second);
}

pair<double, double> RhoCalculator::GetEtaPhi(int IEta, int IPhi)
{
   double Eta = (EtaBins[IEta] + EtaBins[IEta+1]) / 2;
   double Phi = 2 * M_PI / NTowers[IEta] * (IPhi + 0.5);

   return pair<double, double>(Eta, Phi);
}

double RhoCalculator::GetDR2(double Eta1, double Phi1, double Eta2, double Phi2)
{
   double DEta = Eta1 - Eta2;
   double DPhi = Phi1 - Phi2;
   while(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   while(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   return DEta * DEta + DPhi * DPhi;
}

