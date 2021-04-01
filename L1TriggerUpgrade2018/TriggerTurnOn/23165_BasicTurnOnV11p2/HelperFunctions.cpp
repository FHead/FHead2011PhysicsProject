#include "HelperFunctions.h"

int BestIndexInRange(vector<FourVector> &List, double AbsEta, double PTMin)
{
   return BestIndexInRange(List, -1, AbsEta, PTMin);
}

FourVector BestInRange(vector<FourVector> &List, double AbsEta, double PTMin)
{
   return BestInRange(List, -1, AbsEta, PTMin);
}

int BestIndexInRange(vector<FourVector> &List, double AbsEtaMin, double AbsEtaMax, double PTMin)
{
   int Best = -1;
   for(int i = 0; i < (int)List.size(); i++)
      if(List[i].GetAbsEta() < AbsEtaMax && List[i].GetAbsEta() > AbsEtaMin && List[i].GetPT() > PTMin)
         if(Best < 0 || List[Best].GetPT() < List[i].GetPT())
            Best = i;
   return Best;
}

FourVector BestInRange(vector<FourVector> &List, double AbsEtaMin, double AbsEtaMax, double PTMin)
{
   FourVector Best(-1, 0, 0, 0);
   for(int i = 0; i < (int)List.size(); i++)
      if(List[i].GetAbsEta() < AbsEtaMax && List[i].GetAbsEta() > AbsEtaMin && List[i].GetPT() > PTMin)
         if(Best.GetPT() < List[i].GetPT())
            Best = List[i];
   return Best;
}

int BestIndexInRange(vector<GenericObject> &List, FourVector &Reference, double MinEta, double MaxEta, double MinPT, double DRMax, int Qual, int Type, double IsoBB, double IsoEC)
{
   GenericObject Best;
   int BestIndex = -1;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;
   for(int i = 0; i < (int)List.size(); i++)
   {
      double AbsEta = List[i].P.GetAbsEta();

      if(AbsEta > MaxEta || (MinEta >= 0 && AbsEta < MinEta))
         continue;
      if(List[i].P.GetPT() < MinPT)
         continue;
      if(Qual >= 0 && List[i].Qual != Qual)
         continue;
      if(Qual == QUAL_CorrectRegion && AbsEta < 0.9 && List[i].Type != 1)
         continue;
      if(Qual == QUAL_CorrectRegion && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type != 2)
         continue;
      if(Qual == QUAL_CorrectRegion && AbsEta > 1.2 && List[i].Type != 3)
         continue;
      if(Qual == QUAL_Overlap12Endcap1CorrectRegion && AbsEta < 0.9 && List[i].Type != 1)
         continue;
      if(Qual == QUAL_Overlap12Endcap1CorrectRegion && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type != 2)
         continue;
      if(Qual == QUAL_Overlap12Endcap1CorrectRegion && AbsEta > 1.2 && List[i].Type != 3)
         continue;
      if(Qual == QUAL_Endcap1CorrectRegion && AbsEta < 0.9 && List[i].Type != 1)
         continue;
      if(Qual == QUAL_Endcap1CorrectRegion && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type != 2)
         continue;
      if(Qual == QUAL_Endcap1CorrectRegion && AbsEta > 1.2 && List[i].Type != 3)
         continue;
      if(Qual == QUAL_EndcapJaana1345 && List[i].Type == 3 &&
         (List[i].Qual != 11 && List[i].Qual != 13 && List[i].Qual != 14 && List[i].Qual != 15))
         continue;
      if(Qual == QUAL_OverlapNotRegion3 && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Endcap1OverlapNotRegion3 && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Overlap12Endcap1OverlapNotRegion3 && AbsEta > 0.9 && AbsEta < 1.2 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Odd && List[i].Qual % 2 == 0)
         continue;
      if(Qual == QUAL_12 && List[i].Qual < 12)
         continue;
      if(Qual == QUAL_Overlap12 && List[i].Qual < 12 && List[i].Type == 2)
         continue;
      if(Qual == QUAL_Overlap12Endcap1 && List[i].Qual < 12 && List[i].Type == 2)
         continue;
      if(Qual == QUAL_Overlap12Endcap1OverlapNotRegion3 && List[i].Qual < 12 && List[i].Type == 2)
         continue;
      if(Qual == QUAL_Overlap12Endcap1CorrectRegion && List[i].Qual < 12 && List[i].Type == 2)
         continue;
      if(Qual == QUAL_Endcap1 && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Endcap1OverlapNotRegion3 && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Endcap1CorrectRegion && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Overlap12Endcap1 && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Overlap12Endcap1OverlapNotRegion3 && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_Overlap12Endcap1CorrectRegion && List[i].Qual == 0 && List[i].Type == 3)
         continue;
      if(Qual == QUAL_BarrelOddEndcap2 && List[i].Type == 0 && List[i].Qual % 2 == 0)
         continue;
      if(Qual == QUAL_BarrelOddEndcap2 && List[i].Type == 1 && List[i].Qual < 2)
         continue;
      if(Qual == QUAL_BarrelNoneEndcap2 && List[i].Type == 1 && List[i].Qual < 2)
         continue;
      if(Qual == QUAL_BarrelNoneEndcap3 && List[i].Type == 1 && List[i].Qual != 3)
         continue;
      if(Qual == QUAL_BarrelNoneEndcap5 && List[i].Type == 1 && List[i].Qual != 5)
         continue;
      if(Qual == QUAL_UseFlag && List[i].Flag == false)
         continue;
      if(Qual == QUAL_QualAndFlag && List[i].Qual == 0)
         continue;
      if(Qual == QUAL_QualAndFlag && List[i].Flag == false)
         continue;
      if(Qual == QUAL_RegionNotFour && List[i].Type == 4)
         continue;
      if(Type >= 0 && List[i].Type != Type)
         continue;
      if(IsoBB >= 0 && AbsEta < 1.5 && List[i].Iso > IsoBB)
         continue;
      if(IsoEC >= 0 && AbsEta > 1.5 && List[i].Iso > IsoEC)
         continue;
      if(GetDR(List[i].P, Reference) <= DRMax)
      {
         if(Best.P.GetPT() < List[i].P.GetPT())
         {
            Best = List[i];
            BestIndex = i;
         }
      }
   }
   return BestIndex;
}

GenericObject BestInRange(vector<GenericObject> &List, FourVector &Reference, double MinEta, double MaxEta, double MinPT, double DRMax, int Qual, int Type, double IsoBB, double IsoEC)
{
   GenericObject Best;
   Best.P = FourVector(-1, 0, 0, 0);
   Best.Iso = -1;

   int Index = BestIndexInRange(List, Reference, MinEta, MaxEta, MinPT, DRMax, Qual, Type, IsoBB, IsoEC);
   if(Index != -1)
      Best = List[Index];

   if(Best.P[0] < 0)
      Best.Type = ((Reference.GetAbsEta() < 1.5) ? 0 : 1);

   return Best;
}

FourVector CalculateHT(vector<FourVector> &GenJets, double Eta, double PT)
{
   double HT = 0;

   for(auto Jet : GenJets)
   {
      if(Jet.GetAbsEta() > Eta)
         continue;
      if(Jet.GetPT() < PT)
         continue;

      HT = HT + Jet.GetPT();
   }

   FourVector Result;
   Result.SetPtEtaPhi(HT, 0, 0);
   return Result;
}

FourVector CalculateMHT(vector<FourVector> &GenJets, double Eta, double PT)
{
   FourVector Result;

   for(auto Jet : GenJets)
   {
      if(Jet.GetAbsEta() > Eta)
         continue;
      if(Jet.GetPT() < PT)
         continue;

      Result = Result + Jet;
   }

   return Result;
}

void FillHistograms(Histograms *Histogram, FourVector &Object, FourVector &Reference, double Isolation, int Type, double DXY)
{
   if(Histogram == nullptr)
      return;
   Histogram->Fill(Object, Reference, Isolation, Type, DXY);
}

void FillHistograms(Histograms *Histogram, FourVector &Object, double Isolation, int Type, double DXY)
{
   if(Histogram == nullptr)
      return;
   Histogram->Fill(Object, Object, Isolation, Type, DXY);
}

void FillHistograms(Histograms &Histogram, FourVector &Object, FourVector &Reference, double Isolation, int Type, double DXY)
{
   Histogram.Fill(Object, Reference, Isolation, Type, DXY);
}

void FillHistograms(Histograms &Histogram, FourVector &Object, double Isolation, int Type, double DXY)
{
   Histogram.Fill(Object, Object, Isolation, Type, DXY);
}

vector<FourVector> ClusterJets(vector<FourVector> &Particles)
{
   vector<fastjet::PseudoJet> Candidates;
   for(auto P : Particles)
      Candidates.push_back(fastjet::PseudoJet(P[1], P[2], P[3], P[0]));

   fastjet::JetDefinition Definition(fastjet::antikt_algorithm, 0.4);
   fastjet::ClusterSequence Sequence(Candidates, Definition);
   vector<fastjet::PseudoJet> Jets = Sequence.inclusive_jets();

   vector<FourVector> GenJets;
   for(auto J : Jets)
      GenJets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));
   return GenJets;
}

double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR)
{
   double Isolation = 0;

   for(auto G : Particles)
   {
      if(GetDR(G, P) < DR)
         Isolation = Isolation + G.GetPT();
   }

   return Isolation / P.GetPT() - 1;
}

vector<FourVector> CleanUpTaus(vector<FourVector> &Taus, vector<FourVector> &Avoid, double DR)
{
   for(int i = 0; i < (int)Taus.size(); i++)
   {
      bool HasSomethingClose = false;
      FourVector P = Taus[i];

      for(FourVector Q : Avoid)
         if(GetDR(P, Q) < DR)
            HasSomethingClose = true;

      if(HasSomethingClose == true)
      {
         Taus.erase(Taus.begin() + i);
         i = i - 1;
      }
   }

   return Taus;
}

FourVector GetVisTau(L1GenMessenger &MGen, int Index)
{
   vector<int> Indices;
   Indices.push_back(Index);

   int N = MGen.GenP.size();

   FourVector P;

   bool LeptonicDecay = false;

   while(Indices.size() > 0)
   {
      int Current = Indices[0];
      Indices.erase(Indices.begin());

      // cout << Current << endl;

      int DaughterCount = MGen.GenDaughter[Current].size();

      for(int i = 0; i < DaughterCount; i++)
      {
         int j = MGen.GenDaughter[Current][i];

         if(MGen.GenID[j] == 12 || MGen.GenID[j] == -12)
            continue;
         if(MGen.GenID[j] == 14 || MGen.GenID[j] == -14)
            continue;
         if(MGen.GenID[j] == 16 || MGen.GenID[j] == -16)
            continue;
         
         Indices.push_back(j);
      }

      if(DaughterCount == 0)   // we found a leaf!
      {
         P = P + MGen.GenP[Current];
         if(MGen.GenID[Current] == 11 || MGen.GenID[Current] == -11)
            LeptonicDecay = true;
         if(MGen.GenID[Current] == 13 || MGen.GenID[Current] == -13)
            LeptonicDecay = true;
      }
   }

   if(LeptonicDecay == false)
      return P;
   return FourVector(-1, 0, 0, 0);
}

FourVector GetVisTauAdhoc(L1GenMessenger &MGen, int Index)
{
   int ID = MGen.GenID[Index];

   FourVector P;
   bool LeptonicDecay = false;

   for(int i = 0; i < (int)MGen.GenID.size(); i++)
   {
      if(MGen.GenParent[i] != ID)
         continue;

      if(MGen.GenID[i] == 11 || MGen.GenID[i] == -11)
         LeptonicDecay = true;
      if(MGen.GenID[i] == 13 || MGen.GenID[i] == -13)
         LeptonicDecay = true;

      if(MGen.GenID[i] == 12 || MGen.GenID[i] == -12)
         continue;
      if(MGen.GenID[i] == 14 || MGen.GenID[i] == -14)
         continue;
      if(MGen.GenID[i] == 16 || MGen.GenID[i] == -16)
         continue;

      P = P + MGen.GenP[i];
   }

   if(LeptonicDecay == true)
      return FourVector(-1, 0, 0, 0);
   return P;
}

bool CheckLeptonicW(L1GenMessenger &MGen)
{
   bool Detected = false;
   for(int i = 0; i < (int)MGen.GenID.size(); i++)
   {
      int GenID = abs(MGen.GenID[i]);
      if(GenID < 11 || GenID > 16)
         continue;

      if(MGen.GenParent[i] == 24 || MGen.GenParent[i] == -24)
         Detected = true;
   }

   return Detected;
}



