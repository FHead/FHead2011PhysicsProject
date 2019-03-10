#include "ReadTree.h"

#define PlainOriginalPP false
#define OriginalPP false

StraightTreeMessenger::StraightTreeMessenger(TFile &File, string TreeName,
   bool ismc, int trigger)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   IsMC = ismc;
   Trigger = trigger;

   JES = NULL;

   Initialize();
}

void StraightTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("JetCSPT", &JetPT);
   Tree->SetBranchAddress("JetCSRawPT", &RawJetPT);
   Tree->SetBranchAddress("JetCSEta", &JetEta);
   Tree->SetBranchAddress("JetCSPhi", &JetPhi);
   Tree->SetBranchAddress("MatchEta", &MatchJetEta);
   Tree->SetBranchAddress("MatchPhi", &MatchJetPhi);
   Tree->SetBranchAddress("MatchPT", &MatchJetPT);
   Tree->SetBranchAddress("MatchDR", &MatchDR);

   Tree->SetBranchAddress("Flavor", &Flavor);
   Tree->SetBranchAddress("FlavorB", &FlavorB);

   Tree->SetBranchAddress("SubJetDR0", &SDRecoDR);
   Tree->SetBranchAddress("SubJet1PT0", &SDSubJetPT1);
   Tree->SetBranchAddress("SubJet1Eta0", &SDSubJetEta1);
   Tree->SetBranchAddress("SubJet1Phi0", &SDSubJetPhi1);
   Tree->SetBranchAddress("SubJet2PT0", &SDSubJetPT2);
   Tree->SetBranchAddress("SubJet2Eta0", &SDSubJetEta2);
   Tree->SetBranchAddress("SubJet2Phi0", &SDSubJetPhi2);
   Tree->SetBranchAddress("SDMass0", &SDMass);
   Tree->SetBranchAddress("SubJetWTADR0", &SDWTADR);
   
   Tree->SetBranchAddress("SubJetDRs", &SDRecoDRs);
   Tree->SetBranchAddress("SubJet1PTs", &SDSubJetPT1s);
   Tree->SetBranchAddress("SubJet1Etas", &SDSubJetEta1s);
   Tree->SetBranchAddress("SubJet1Phis", &SDSubJetPhi1s);
   Tree->SetBranchAddress("SubJet2PTs", &SDSubJetPT2s);
   Tree->SetBranchAddress("SubJet2Etas", &SDSubJetEta2s);
   Tree->SetBranchAddress("SubJet2Phis", &SDSubJetPhi2s);
   Tree->SetBranchAddress("SDMasses", &SDMasses);
   Tree->SetBranchAddress("SubJetWTADRs", &SDWTADRs);

   if(Tree->GetBranch("MCWeight") != NULL)
      UseMCWeight = true;
   else
      UseMCWeight = false;

   if(IsMC == true && UseMCWeight == true)
      Tree->SetBranchAddress("MCWeight", &MCWeight);
   else
      MCWeight = 1;

   if(IsMC == true)
      Tree->SetBranchAddress("PTHat", &PTHat);
   else
      PTHat = 200;

   Tree->SetBranchAddress("Centrality", &Centrality);

   if(IsMC == false)
   {
      if(Trigger == 60)
         Tree->SetBranchAddress("PassPbPb60", &PassTrigger);
      else if(Trigger == 80)
         Tree->SetBranchAddress("PassPbPb80", &PassTrigger);
      else
         Tree->SetBranchAddress("PassPbPb100", &PassTrigger);
   }
   else
      PassTrigger = true;

   // Currently this is done at the plain tree maker level and not written out as a branch
   PassFilter = true;
}

void StraightTreeMessenger::GetEntry(int iE)
{
   if(Tree == NULL)
      return;

   Tree->GetEntry(iE);

   if(PlainOriginalPP == true)
      Centrality = 0.99;

   FourVector P1, P2;
   P1.SetPtEtaPhi(SDSubJetPT1, SDSubJetEta1, SDSubJetPhi1);
   P2.SetPtEtaPhi(SDSubJetPT2, SDSubJetEta2, SDSubJetPhi2);
   double NewSDMass = (P1 + P2).GetMass();

   if(JES != NULL)
      CorrectedJetPT = JES->Apply(MatchJetPT, MatchJetEta);
   else
      CorrectedJetPT = MatchJetPT;

   NewSDMass = SDMass;

   SDZG = min(SDSubJetPT1, SDSubJetPT2) / (SDSubJetPT1 + SDSubJetPT2);
   SDMassRatio = NewSDMass / MatchJetPT;

   for(int i = 0; i < 10; i++)
   {
      P1.SetPtEtaPhi(SDSubJetPT1s[i], SDSubJetEta1s[i], SDSubJetPhi1s[i]);
      P2.SetPtEtaPhi(SDSubJetPT2s[i], SDSubJetEta2s[i], SDSubJetPhi2s[i]);
      NewSDMass = (P1 + P2).GetMass();

      NewSDMass = SDMass;
   
      SDZGs[i] = min(SDSubJetPT1s[i], SDSubJetPT2s[i]) / (SDSubJetPT1s[i] + SDSubJetPT2s[i]);
      SDMassRatios[i] = NewSDMass / MatchJetPT;
   }
   
   SysBin = SDMassRatio / (0.40 / 160);

   PTPT = (P1 + P2).GetPT() / MatchJetPT;
   
   // bug fix
   if(SDRecoDR < 0)
      SDWTADR = SDRecoDR;
   for(int i = 0; i < 10; i++)
      if(SDRecoDRs[i] < 0)
         SDWTADRs[i] = SDRecoDRs[i];
}

bool StraightTreeMessenger::PassPTHat(double PTHatMin)
{
   if(IsMC == true && PTHat < PTHatMin)
      return false;
   return true;
}

bool StraightTreeMessenger::PassPTHat(double PTHatMin, double PTHatMax)
{
   if(IsMC == true && (PTHat < PTHatMin || PTHat >= PTHatMax))
      return false;
   return true;
}

bool StraightTreeMessenger::PassSelection()
{
   if(IsMC == false && PassFilter == false)
      return false;
   if(IsMC == false && PassTrigger == false)
      return false;
   // if(MatchDR > 0.05)
   //    return false;

   if(MatchJetEta < -1.3 || MatchJetEta > 1.3)
      return false;

   // if(PTPT > 0.9999)
   //    return false;

   // if(FlavorB != 21)
   //    return false;
   // if(FlavorB <= -5 || FlavorB >= 5)
   //    return false;

   return true;
}

void StraightTreeMessenger::SetJES(JetEnergyScale *jes)
{
   JES = jes;
}

int StraightTreeMessenger::CentralityBin(double CBinEdge[], int BinCount)
{
   return GetBin(Centrality, CBinEdge, BinCount);
}

int StraightTreeMessenger::PTBin(double PTBinEdge[], int BinCount)
{
   return GetBin(CorrectedJetPT, PTBinEdge, BinCount);
}

int StraightTreeMessenger::JetBin(double PTBinEdge[], int BinCount)
{
   int iPT = PTBin(PTBinEdge, BinCount);
   if(iPT < 0)
      return -1;

   double JetPercentage = (CorrectedJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
   int JetBin = JetPercentage * 50;

   return JetBin;
}

int StraightTreeMessenger::AngleBin(double AngleBinEdge[], int BinCount)
{
   return GetBin(SDRecoDR, AngleBinEdge, BinCount);
}

int StraightTreeMessenger::PTPTBin(double PTPTBinEdge[], int BinCount)
{
   return GetBin(PTPT, PTPTBinEdge, BinCount);
}

int StraightTreeMessenger::CentralityInt()
{
   return (int)(Centrality * 100);
}

SmearTreeMessenger::SmearTreeMessenger(TFile &File, string TreeName, bool ismc)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   IsMC = ismc;

   JES = NULL;

   Initialize();
}

void SmearTreeMessenger::Initialize()
{
   Tree->SetBranchAddress("BestJetPT", &JetRawPT);
   Tree->SetBranchAddress("BestJetEta", &JetEta);
   Tree->SetBranchAddress("BestJetPhi", &JetPhi);
   Tree->SetBranchAddress("JetPT", &OriginalJetPT);
   Tree->SetBranchAddress("JetEta", &OriginalJetEta);
   Tree->SetBranchAddress("JetPhi", &OriginalJetPhi);
   Tree->SetBranchAddress("TotalStuffInJet", &TotalStuffInJet);

   Tree->SetBranchAddress("BestJetDR", &SDRecoDR);
   Tree->SetBranchAddress("BestJetZG", &SDZG);
   Tree->SetBranchAddress("BestJetSDMass", &SDMass);
   Tree->SetBranchAddress("BestJetWTADR", &SDWTADR);
   Tree->SetBranchAddress("BestJetSDPT", &SDSubJetPT);
   Tree->SetBranchAddress("BestJetSJ1PT", &SDSubJetPT1);
   Tree->SetBranchAddress("BestJetSJ1Eta", &SDSubJetEta1);
   Tree->SetBranchAddress("BestJetSJ1Phi", &SDSubJetPhi1);
   Tree->SetBranchAddress("BestJetSJ2PT", &SDSubJetPT2);
   Tree->SetBranchAddress("BestJetSJ2Eta", &SDSubJetEta2);
   Tree->SetBranchAddress("BestJetSJ2Phi", &SDSubJetPhi2);
   
   Tree->SetBranchAddress("SubJetDRs", &SDRecoDRs);
   Tree->SetBranchAddress("SDMasses", &SDMasses);
   Tree->SetBranchAddress("SubJetWTADRs", &SDWTADRs);
   Tree->SetBranchAddress("SubJet1PTs", &SDSubJetPT1s);
   Tree->SetBranchAddress("SubJet1Etas", &SDSubJetEta1s);
   Tree->SetBranchAddress("SubJet1Phis", &SDSubJetPhi1s);
   Tree->SetBranchAddress("SubJet2PTs", &SDSubJetPT2s);
   Tree->SetBranchAddress("SubJet2Etas", &SDSubJetEta2s);
   Tree->SetBranchAddress("SubJet2Phis", &SDSubJetPhi2s);

   if(Tree->GetBranch("MCWeight") != NULL)
      UseMCWeight = true;
   else
      UseMCWeight = false;

   if(IsMC == true && UseMCWeight == true)
      Tree->SetBranchAddress("MCWeight", &MCWeight);
   else
      MCWeight = 1;

   if(IsMC == true)
      Tree->SetBranchAddress("PTHat", &PTHat);
   else
      PTHat = 200;

   Tree->SetBranchAddress("Centrality", &Centrality);

   Tree->SetBranchAddress("TotalPTInJet", &PTInJet);
   Tree->SetBranchAddress("Rho", &Rho);
   Tree->SetBranchAddress("TotalPT", &TotalPT);

   if(IsMC == false)
   {
      if(Tree->GetBranch("PassFilter") != NULL)
         Tree->SetBranchAddress("PassFilter", &PassFilter);
      else
         PassFilter = true;

      if(Tree->GetBranch("PassHLT") != NULL)
         Tree->SetBranchAddress("PassHLT", &PassTrigger);
      else
         PassTrigger = true;
   }
   else
   {
      PassFilter = true;
      PassTrigger = true;
   }
}

void SmearTreeMessenger::GetEntry(int iE)
{
   if(Tree == NULL)
      return;

   Tree->GetEntry(iE);

   if(OriginalPP == true)
      Centrality = 0.99;

   FourVector P1, P2;
   P1.SetPtEtaPhi(SDSubJetPT1, SDSubJetEta1, SDSubJetPhi1);
   P2.SetPtEtaPhi(SDSubJetPT2, SDSubJetEta2, SDSubJetPhi2);
   double NewSDMass = (P1 + P2).GetMass();

   NewSDMass = SDMass * (1.01 - SDRecoDR * 0.075);
   // NewSDMass = SDMass;

   SDMassRatio = NewSDMass / JetRawPT;
   // SDMassRatio = NewSDMass / SDSubJetPT / 1.025;
   
   for(int i = 0; i < 10; i++)
   {
      P1.SetPtEtaPhi(SDSubJetPT1s[i], SDSubJetEta1s[i], SDSubJetPhi1s[i]);
      P2.SetPtEtaPhi(SDSubJetPT2s[i], SDSubJetEta2s[i], SDSubJetPhi2s[i]);
      NewSDMass = (P1 + P2).GetMass();
      
      NewSDMass = SDMasses[i] * (1.01 - SDRecoDR * 0.075);
      SDMassRatios[i] = NewSDMass / JetRawPT;

      SDZGs[i] = min(SDSubJetPT1s[i], SDSubJetPT2s[i]) / (SDSubJetPT1s[i] + SDSubJetPT2s[i]);
   }

   SysBin = SDMassRatio / (0.40 / 160);

   // JetRawPT = JetRawPT - 6;
   if(JES != NULL)
      JetPT = JES->Apply(JetRawPT, JetEta);
   else
      JetPT = JetRawPT;

   double DEta = JetEta - OriginalJetEta;
   double DPhi = JetPhi - OriginalJetPhi;
   if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   MatchDR = sqrt(DEta * DEta + DPhi * DPhi);

   PTPT = (P1 + P2).GetPT() / JetRawPT;

   // bug fix
   if(SDRecoDR < 0)
      SDWTADR = SDRecoDR;
   for(int i = 0; i < 10; i++)
      if(SDRecoDRs[i] < 0)
         SDWTADRs[i] = SDRecoDRs[i];

   // MCWeight = 1 / (0.40 * tanh((OriginalJetPT - 80) / 10) + 0.60);
   // MCWeight = 1 / (0.45 * tanh((OriginalJetPT - 80) / 20) + 0.55);
   // MCWeight = 1 / (0.48 * tanh((OriginalJetPT - 80) / 20) + 0.52);
   // MCWeight = 1 / (0.45 * tanh((OriginalJetPT - 80) / 5) + 0.55);
}

bool SmearTreeMessenger::PassPTHat(double PTHatMin)
{
   if(IsMC == true && PTHat < PTHatMin)
      return false;
   return true;
}

bool SmearTreeMessenger::PassPTHat(double PTHatMin, double PTHatMax)
{
   if(IsMC == true && (PTHat < PTHatMin || PTHat >= PTHatMax))
      return false;
   return true;
}

bool SmearTreeMessenger::PassSelection()
{
   if(IsMC == false && PassFilter == false)
      return false;
   if(IsMC == false && PassTrigger == false)
      return false;
   // if(MatchDR > 0.1)
   //    return false;

   if(JetEta < -1.3 || JetEta > 1.3)
      return false;

   // if(PTPT > 0.9999)
   //    return false;

   return true;
}

void SmearTreeMessenger::SetJES(JetEnergyScale *jes)
{
   JES = jes;
}

int SmearTreeMessenger::CentralityBin(double CBinEdge[], int BinCount)
{
   return GetBin(Centrality, CBinEdge, BinCount);
}

int SmearTreeMessenger::PTBin(double PTBinEdge[], int BinCount)
{
   return GetBin(JetPT, PTBinEdge, BinCount);
}

int SmearTreeMessenger::JetBin(double PTBinEdge[], int BinCount)
{
   int iPT = PTBin(PTBinEdge, BinCount);
   if(iPT < 0)
      return -1;

   double JetPercentage = (JetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
   int JetBin = JetPercentage * 50;

   return JetBin;
}

int SmearTreeMessenger::AngleBin(double AngleBinEdge[], int BinCount)
{
   return GetBin(SDRecoDR, AngleBinEdge, BinCount);
}

int SmearTreeMessenger::PTPTBin(double PTPTBinEdge[], int BinCount)
{
   return GetBin(PTPT, PTPTBinEdge, BinCount);
}

int SmearTreeMessenger::CentralityInt()
{
   return (int)(Centrality * 100);
}

int GetBin(double X, double Edge[], int BinCount)
{
   int Bin = -1;
   for(int i = 0; i < BinCount; i++)
      if(Edge[i] <= X && X < Edge[i+1])
         Bin = i;

   return Bin;
}







