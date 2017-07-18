#include "ReadTree.h"

StraightTreeMessenger::StraightTreeMessenger(TFile &File, string TreeName,
   bool ismc, int sd, int trigger)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   IsMC = ismc;
   SD = sd;
   Trigger = trigger;

   Initialize();
}
   
void StraightTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("JetCSPT", &JetPT);
   Tree->SetBranchAddress("JetCSEta", &JetEta);
   Tree->SetBranchAddress("JetCSPhi", &JetPhi);
   Tree->SetBranchAddress("MatchPT", &RawJetPT);
   Tree->SetBranchAddress("MatchDR", &MatchDR);
   
   if(SD == 0)
   {
      Tree->SetBranchAddress("SubJetDR0", &SDRecoDR);
      Tree->SetBranchAddress("SubJet1PT0", &SDSubJetPT1);
      Tree->SetBranchAddress("SubJet2PT0", &SDSubJetPT2);
      Tree->SetBranchAddress("SDMass0", &SDMass);
   }
   else
   {
      Tree->SetBranchAddress("SubJetDR7", &SDRecoDR);
      Tree->SetBranchAddress("SubJet1PT7", &SDSubJetPT1);
      Tree->SetBranchAddress("SubJet2PT7", &SDSubJetPT2);
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

   SDZG = min(SDSubJetPT1, SDSubJetPT2) / (SDSubJetPT1 + SDSubJetPT2);
   SDMassRatio = SDMass / RawJetPT;
   SysBin = SDMassRatio / (0.40 / 160);

   // Temporary fix because of the wrong cross section
   //    I reran current straight tree so it is not needed anymore, but for old samples we need them
   //
   // if(IsMC == true)
   // {
   //    if(PTHat < 220 && PTHat > 170)
   //       MCWeight = MCWeight / 1.08366;
   //    if(PTHat > 540)
   //       MCWeight = MCWeight / (1 - 0.4243);
   // }
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
   if(MatchDR > 0.1)
      return false;

   if(JetEta < -1.3 || JetEta > 1.3)
      return false;

   return true;
}

int StraightTreeMessenger::CentralityBin(double CBinEdge[], int BinCount)
{
   return GetBin(Centrality, CBinEdge, BinCount);
}

int StraightTreeMessenger::PTBin(double PTBinEdge[], int BinCount)
{
   return GetBin(JetPT, PTBinEdge, BinCount);
}
   
int StraightTreeMessenger::JetBin(double PTBinEdge[], int BinCount)
{
   int iPT = PTBin(PTBinEdge, BinCount);
   if(iPT < 0)
      return -1;

   double JetPercentage = (JetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
   int JetBin = JetPercentage * 50;

   return JetBin;
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

   GMBRMS = NULL;
   GSmearRMS = NULL;

   Initialize();
}

void SmearTreeMessenger::Initialize()
{
   Tree->SetBranchAddress("BestJetPT", &JetPT);
   Tree->SetBranchAddress("BestJetEta", &JetEta);
   Tree->SetBranchAddress("BestJetPhi", &JetPhi);
   Tree->SetBranchAddress("JetPT", &OriginalJetPT);
   Tree->SetBranchAddress("JetEta", &OriginalJetEta);
   Tree->SetBranchAddress("JetPhi", &OriginalJetPhi);

   if(SD == 0)
   {
      Tree->SetBranchAddress("BestJetDR", &SDRecoDR);
      Tree->SetBranchAddress("BestJetZG", &SDZG);
      Tree->SetBranchAddress("BestJetSDMass", &SDMass);
   }
   else
   {
      Tree->SetBranchAddress("BestJetDR2", &SDRecoDR);
      Tree->SetBranchAddress("BestJetZG2", &SDZG);
      Tree->SetBranchAddress("BestJetSDMass2", &SDMass);
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

   RawJetPT = JetPT;
   SDMassRatio = SDMass / RawJetPT;
   SysBin = SDMassRatio / (0.40 / 160);
   
   double DEta = JetEta - OriginalJetEta;
   double DPhi = JetPhi - OriginalJetPhi;
   if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   MatchDR = sqrt(DEta * DEta + DPhi * DPhi);
}

void SmearTreeMessenger::SetMB(TGraph *G)
{
   GMBRMS = G;
}

void SmearTreeMessenger::SetSmear(TGraph *G)
{
   GSmearRMS = G;
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
   if(OriginalJetPT < 50)
      return false;

   if(JetEta < -1.3 || JetEta > 1.3)
      return false;

   // This is the poor-man's emulation for pp trigger in MC
   // if(IsMC == true && OriginalJetPT < 80)
   //    return false;

   return true;
}

int SmearTreeMessenger::CentralityBin(double CBinEdge[], int BinCount)
{
   return GetBin(Centrality / 100, CBinEdge, BinCount);
}

int SmearTreeMessenger::PTBin(double PTBinEdge[], int BinCount){
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

double SmearTreeMessenger::SmearWeight()
{
   if(GMBRMS == NULL || GSmearRMS == NULL)
      return 1;

   double TargetRMS, SmearRMS, Dummy;
   GMBRMS->GetPoint((int)Centrality, Dummy, TargetRMS);
   GSmearRMS->GetPoint((int)Centrality, Dummy, SmearRMS);

   SmearRMS = SmearRMS / 1.1;

   double ExcessPT = PTInJet - Rho * 0.4 * 0.4 * PI;
   double Weight = exp(-ExcessPT * ExcessPT / (2 * TargetRMS * TargetRMS))
                 / exp(-ExcessPT * ExcessPT / (2 * SmearRMS * SmearRMS));

   return Weight;
}
   
int SmearTreeMessenger::CentralityInt()
{
   return (int)Centrality;
}

int GetBin(double X, double Edge[], int BinCount)
{
   int Bin = -1;
   for(int i = 0; i < BinCount; i++)
      if(Edge[i] <= X && X < Edge[i+1])
         Bin = i;

   return Bin;
}







