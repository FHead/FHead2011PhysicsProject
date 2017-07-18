#include "ReadTree.h"

#define PlainOriginalPP false
#define OriginalPP false

StraightTreeMessenger::StraightTreeMessenger(TFile &File, string TreeName,
   bool ismc, int sd, int trigger)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   IsMC = ismc;
   SD = sd;
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

   if(SD == 0)
   {
      Tree->SetBranchAddress("SubJetDR0", &SDRecoDR);
      Tree->SetBranchAddress("SubJet1PT0", &SDSubJetPT1);
      Tree->SetBranchAddress("SubJet1Eta0", &SDSubJetEta1);
      Tree->SetBranchAddress("SubJet1Phi0", &SDSubJetPhi1);
      Tree->SetBranchAddress("SubJet2PT0", &SDSubJetPT2);
      Tree->SetBranchAddress("SubJet2Eta0", &SDSubJetEta2);
      Tree->SetBranchAddress("SubJet2Phi0", &SDSubJetPhi2);
      Tree->SetBranchAddress("SDMass0", &SDMass);
   }
   else
   {
      Tree->SetBranchAddress("SubJetDR7", &SDRecoDR);
      Tree->SetBranchAddress("SubJet1PT7", &SDSubJetPT1);
      Tree->SetBranchAddress("SubJet1Eta7", &SDSubJetEta1);
      Tree->SetBranchAddress("SubJet1Phi7", &SDSubJetPhi1);
      Tree->SetBranchAddress("SubJet2PT7", &SDSubJetPT2);
      Tree->SetBranchAddress("SubJet2Eta7", &SDSubJetEta2);
      Tree->SetBranchAddress("SubJet2Phi7", &SDSubJetPhi2);
      Tree->SetBranchAddress("SDMass7", &SDMass);
   }

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
   // SDMassRatio = NewSDMass / (SDSubJetPT1 + SDSubJetPT2);
   SysBin = SDMassRatio / (0.40 / 160);

   PTPT = (P1 + P2).GetPT() / MatchJetPT;
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

int StraightTreeMessenger::CentralityInt()
{
   return (int)(Centrality * 100);
}

SmearTreeMessenger::SmearTreeMessenger(TFile &File, string TreeName, bool ismc, int sd)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   IsMC = ismc;
   SD = sd;

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

   if(SD == 0)
   {
      Tree->SetBranchAddress("BestJetDR", &SDRecoDR);
      Tree->SetBranchAddress("BestJetZG", &SDZG);
      Tree->SetBranchAddress("BestJetSDMass", &SDMass);
      Tree->SetBranchAddress("BestJetSDPT", &SDSubJetPT);
      Tree->SetBranchAddress("BestJetSJ1PT", &SDSubJetPT1);
      Tree->SetBranchAddress("BestJetSJ1Eta", &SDSubJetEta1);
      Tree->SetBranchAddress("BestJetSJ1Phi", &SDSubJetPhi1);
      Tree->SetBranchAddress("BestJetSJ2PT", &SDSubJetPT2);
      Tree->SetBranchAddress("BestJetSJ2Eta", &SDSubJetEta2);
      Tree->SetBranchAddress("BestJetSJ2Phi", &SDSubJetPhi2);
   }
   else
   {
      Tree->SetBranchAddress("BestJetDR2", &SDRecoDR);
      Tree->SetBranchAddress("BestJetZG2", &SDZG);
      Tree->SetBranchAddress("BestJetSDMass2", &SDMass);
      Tree->SetBranchAddress("BestJetSDPT2", &SDSubJetPT);
      Tree->SetBranchAddress("BestJetSJ1PT2", &SDSubJetPT1);
      Tree->SetBranchAddress("BestJetSJ1Eta2", &SDSubJetEta1);
      Tree->SetBranchAddress("BestJetSJ1Phi2", &SDSubJetPhi1);
      Tree->SetBranchAddress("BestJetSJ2PT2", &SDSubJetPT2);
      Tree->SetBranchAddress("BestJetSJ2Eta2", &SDSubJetEta2);
      Tree->SetBranchAddress("BestJetSJ2Phi2", &SDSubJetPhi2);
   }

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
   SysBin = SDMassRatio / (0.40 / 160);

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
   if(MatchDR > 0.1)
      return false;

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







