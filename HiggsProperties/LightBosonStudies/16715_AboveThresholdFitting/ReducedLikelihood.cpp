#include "ReducedLikelihood.h"

using namespace RealLikelihood;

Likelihood::Likelihood()
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = 0;
         IS[i][j] = 1;
      }
   }

   VB = 0;
   IB = 1;

   // InitializeLikelihoodCalculation();
}

Likelihood::Likelihood(const Likelihood &L)
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = L.VS[i][j];
         IS[i][j] = L.IS[i][j];
      }
   }

   VB = L.VB;
   IB = L.IB;

   // InitializeLikelihoodCalculation();
}

void Likelihood::InitializeLikelihoodCalculation()
{
   ZP.VMass = 9.46;
   ZP.VWidth = 0.000054;
   ZP.G1VL = 0.073348;
   ZP.G1VR = 0.073348;
   ZP.G2VL = 0.073348;
   ZP.G2VR = 0.073348;

   CalculatorEM.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorEM.SetSmear12(SmearElectronCentral);
   CalculatorEM.SetSmear34(SmearMuonCentral);
   CalculatorEM.SetToleranceF(1e-12);
   CalculatorEM.SetMaxDepthF(30);
   CalculatorEM.SetSimpleMassIntegralStep(180);
   CalculatorEM.SetExpansionOrder(2);
   CalculatorEM.SetDoDeltaMH(true, 125);
   CalculatorEM.SetIgnorePhi(true);
   CalculatorEM.SetApplyEfficiencyAtEnd(true);
   CalculatorEM.SetIntegralCRange(0.75, 1.25);
   CalculatorEM.SetAttractorStrength(2);
   CalculatorEM.SetIntegralCStep(20);
   CalculatorEM.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEM.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEM.SetFlatApproximation(false);
   CalculatorEM.SetIncludeSwapping(true);
   CalculatorEM.SetIgnoreTip(false);
   CalculatorEM.SetTipRangeFactor(0.05);
   CalculatorEM.SetUseSmartCenter(true);
   CalculatorEM.SetZPrimeParameter(ZP);
   CalculatorEM.SetPTYDensity(JustFlatPTYDensity);

   MEArrayZPrime MEEM = GetSpin0XVVFunctionListEM();   // ME, 2e2mu = ME,EM = MEEM
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         CalculatorEM.SetMECalculator(MEEM[i][j]);

   CalculatorME = CalculatorEM;
   CalculatorME.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorME.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorME.SetSmear12(SmearMuonCentral);
   CalculatorME.SetSmear34(SmearElectronCentral);

   CalculatorEE.SetEfficiency12(GetElectronEfficiencyPtEta);
   CalculatorEE.SetEfficiency34(GetElectronEfficiencyPtEta);
   CalculatorEE.SetSmear12(SmearElectronCentral);
   CalculatorEE.SetSmear34(SmearElectronCentral);
   CalculatorEE.SetToleranceF(1e-12);
   CalculatorEE.SetMaxDepthF(30);
   CalculatorEE.SetSimpleMassIntegralStep(180);
   CalculatorEE.SetExpansionOrder(2);
   CalculatorEE.SetDoDeltaMH(true, 125);
   CalculatorEE.SetIgnorePhi(true);
   CalculatorEE.SetApplyEfficiencyAtEnd(true);
   CalculatorEE.SetIntegralCRange(0.75, 1.25);
   CalculatorEE.SetAttractorStrength(2);
   CalculatorEE.SetIntegralCStep(20);
   CalculatorEE.SetSimpleMassIntegralWindow(true, 30);
   CalculatorEE.SetSimpleMassIntegralWindow(false, 40);
   CalculatorEE.SetFlatApproximation(false);
   CalculatorEE.SetIncludeSwapping(true);
   CalculatorEE.SetIgnoreTip(false);
   CalculatorEE.SetTipRangeFactor(0.05);
   CalculatorEE.SetUseSmartCenter(true);
   CalculatorEE.SetZPrimeParameter(ZP);
   CalculatorEE.SetPTYDensity(JustFlatPTYDensity);

   MEArrayZPrime MEEE = GetSpin0XVVFunctionListEE();   // ME, 4e = ME,EE = MEEE
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         CalculatorEE.SetMECalculator(MEEE[i][j]);

   CalculatorMM = CalculatorEE;
   CalculatorMM.SetEfficiency12(GetMuonEfficiencyPtEta);
   CalculatorMM.SetEfficiency34(GetMuonEfficiencyPtEta);
   CalculatorMM.SetSmear12(SmearMuonCentral);
   CalculatorMM.SetSmear34(SmearMuonCentral);

   // CalculatorEM.PrintSettings();
   // CalculatorME.PrintSettings();
   // CalculatorEE.PrintSettings();
   // CalculatorMM.PrintSettings();
}

Likelihood &Likelihood::operator =(const Likelihood &L)
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = L.VS[i][j];
         IS[i][j] = L.IS[i][j];
      }
   }

   VB = L.VB;
   IB = L.IB;

   CalculatorEM = L.CalculatorEM;
   CalculatorME = L.CalculatorME;
   CalculatorEE = L.CalculatorEE;
   CalculatorMM = L.CalculatorMM;

   return *this;
}

double Likelihood::Apply(FullAVVBasis &A, double F) const
{
   double VSAll = 0;
   double ISAll = 0;

   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};
   
   for(int i = 0; i < 16; i++)
   {
      if(A.A[Map[i]] == 0)
         continue;

      for(int j = 0; j < 16; j++)
      {
         if(A.A[Map[j]] == 0)
            continue;

         VSAll = VSAll + A.A[Map[i]] * A.A[Map[j]] * VS[i][j];
         ISAll = ISAll + A.A[Map[i]] * A.A[Map[j]] * IS[i][j];
      }
   }

   double LS = VSAll / ISAll;
   double LB = VB / IB;

   if(ISAll <= 0)
      LS = 0;
   if(IB <= 0)
      LB = 0;

   double Answer = (1 - F) * LS + F * LB;
   if(Answer == 0)
      cerr << "Warning! Likeilhood = 0!" << endl;

   return Answer;
}

void Likelihood::SetBranchAddress(TTree *T)
{
   if(T == NULL)
   {
      cerr << "Tree is NULL while attempting to set branches" << endl;
      return;
   }

   vector<string> Suffix = GetXVVSignalSuffixList();

   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};
   
   /*
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         T->SetBranchStatus(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), false);

   for(int i = 0; i < 16; i++)
   {
      cout << i << " " << Suffix[Map[i]] << endl;

      for(int j = 0; j < 16; j++)
      {
         T->SetBranchStatus(Form("B1_%s_%s", Suffix[Map[i]].c_str(), Suffix[Map[j]].c_str()), true);
         T->SetBranchAddress(Form("B1_%s_%s", Suffix[Map[i]].c_str(), Suffix[Map[j]].c_str()), &VS[i][j]);
      }
   }

   T->SetBranchAddress("B2_DDbar", &VB);
   */
}

void Likelihood::SetIS(double is[72][72])
{
   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         IS[i][j] = is[Map[i]][Map[j]];
}

void Likelihood::SetIB(double ib)
{
   IB = ib;
}

void Likelihood::CalculateLikelihood(LeptonVectors &Leptons, int L1ID, int L3ID)
{
   if(L1ID == L3ID)
      Leptons = Leptons.ReorderLeptons4e();
   else
      Leptons = Leptons.ReorderLeptons2e2mu();

   LeptonVectors AlternativeLeptons;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() > (Leptons.Lepton21 + Leptons.Lepton12).GetMass())
   {
      AlternativeLeptons.Lepton11 = Leptons.Lepton11;
      AlternativeLeptons.Lepton12 = Leptons.Lepton22;
      AlternativeLeptons.Lepton21 = Leptons.Lepton21;
      AlternativeLeptons.Lepton22 = Leptons.Lepton12;
   }
   else
   {
      AlternativeLeptons.Lepton11 = Leptons.Lepton21;
      AlternativeLeptons.Lepton12 = Leptons.Lepton12;
      AlternativeLeptons.Lepton21 = Leptons.Lepton11;
      AlternativeLeptons.Lepton22 = Leptons.Lepton22;
   }

   EventParameters Angles = ConvertVectorsToAnglesRoberto(Leptons);
   EventParameters AlternativeAngles = ConvertVectorsToAnglesRoberto(AlternativeLeptons);

   vector<double> Integral;
   vector<double> AlternativeIntegral;

   double RecoJ12 = VolumeElement::EstimateVolumeFull5(Angles);
   double SortedRecoJ12 = VolumeElement::EstimateVolumeFull5(AlternativeAngles);

   if(abs(L1ID) == 11 && abs(L3ID) == 11)
   {
      Integral = CalculatorEE.PassThroughMode(Angles);
      AlternativeIntegral = CalculatorEE.PassThroughMode(AlternativeAngles);

      for(int i = 0; i < (int)Integral.size(); i++)
         Integral[i] = (Integral[i] + AlternativeIntegral[i] * SortedRecoJ12 / RecoJ12);
   }
   else if(abs(L1ID) == 11 && abs(L3ID) == 13)
      Integral = CalculatorEM.PassThroughMode(Angles);
   else if(abs(L1ID) == 13 && abs(L3ID) == 11)
      Integral = CalculatorME.PassThroughMode(Angles);
   else if(abs(L1ID) == 13 && abs(L3ID) == 13)
   {
      Integral = CalculatorMM.PassThroughMode(Angles);
      AlternativeIntegral = CalculatorMM.PassThroughMode(AlternativeAngles);

      for(int i = 0; i < (int)Integral.size(); i++)
         Integral[i] = (Integral[i] + AlternativeIntegral[i] * SortedRecoJ12 / RecoJ12);
   }
   
   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};
   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         VS[i][j] = Integral[Map[i]*72+Map[j]];

   VB = 1;
}



