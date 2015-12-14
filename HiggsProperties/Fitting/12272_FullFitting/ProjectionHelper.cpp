#include <iostream>
#include <algorithm>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PTYFunctions.h"

#include "ProjectionHelper.h"

#define MAXENTRY 500000

void ProjectionHelper::SetBranchAddress(TTree *Tree)
{
   if(Tree == NULL)
   {
      cerr << "[ProjectionHelper][SetBranchAddress] Tree is NULL.  Do nothing." << endl;
      return;
   }

   Tree->SetBranchAddress("MH", &Angles.HMass);
   Tree->SetBranchAddress("M1", &Angles.ZMass);
   Tree->SetBranchAddress("M2", &Angles.Z2Mass);
   Tree->SetBranchAddress("Phi0", &Angles.Phi0);
   Tree->SetBranchAddress("Theta0", &Angles.Theta0);
   Tree->SetBranchAddress("Phi", &Angles.Phi);
   Tree->SetBranchAddress("Theta1", &Angles.Theta1);
   Tree->SetBranchAddress("Theta2", &Angles.Theta2);
   Tree->SetBranchAddress("HPT", &Angles.PTH);
   Tree->SetBranchAddress("HY", &Angles.YH);
   Tree->SetBranchAddress("HPhi", &Angles.PhiH);
   Tree->SetBranchAddress("PhiOffset", &Angles.PhiOffset);
   Tree->SetBranchAddress("RecalculatedMH", &ReshuffledAngles.HMass);
   Tree->SetBranchAddress("RecalculatedM1", &ReshuffledAngles.ZMass);
   Tree->SetBranchAddress("RecalculatedM2", &ReshuffledAngles.Z2Mass);
   Tree->SetBranchAddress("RecalculatedPhi0", &ReshuffledAngles.Phi0);
   Tree->SetBranchAddress("RecalculatedTheta0", &ReshuffledAngles.Theta0);
   Tree->SetBranchAddress("RecalculatedPhi", &ReshuffledAngles.Phi);
   Tree->SetBranchAddress("RecalculatedTheta1", &ReshuffledAngles.Theta1);
   Tree->SetBranchAddress("RecalculatedTheta2", &ReshuffledAngles.Theta2);
   Tree->SetBranchAddress("RecalculatedHPT", &ReshuffledAngles.PTH);
   Tree->SetBranchAddress("RecalculatedHY", &ReshuffledAngles.YH);
   Tree->SetBranchAddress("RecalculatedHPhi", &ReshuffledAngles.PhiH);
   Tree->SetBranchAddress("RecalculatedPhiOffset", &ReshuffledAngles.PhiOffset);
   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("L3PT", &L3PT);
   Tree->SetBranchAddress("L3Eta", &L3Eta);
   Tree->SetBranchAddress("L3Phi", &L3Phi);
   Tree->SetBranchAddress("L4PT", &L4PT);
   Tree->SetBranchAddress("L4Eta", &L4Eta);
   Tree->SetBranchAddress("L4Phi", &L4Phi);
   Tree->SetBranchAddress("Weight", Weight);
   Tree->SetBranchAddress("PassBaseline2e2mu", &PassBaseline2e2mu);
   Tree->SetBranchAddress("PassBaseline4e", &PassBaseline4e);

   cerr << "[ProjectionHelper][SetBranchAddress] Branches set." << endl;
}

double ProjectionHelper::GetDimensionValue(Dimension dimension, EventParameters Event)
{
   switch(dimension)
   {
   case DimensionMH:
      return Event.HMass;
   case DimensionM1:
      return Event.ZMass;
   case DimensionM2:
      return Event.Z2Mass;
   case DimensionPhi0:
      return Event.Phi0;
   case DimensionTheta0:
      return Event.Theta0;
   case DimensionPhi:
      return Event.Phi;
   case DimensionTheta1:
      return Event.Theta1;
   case DimensionTheta2:
      return Event.Theta2;
   case DimensionCosTheta0:
      return cos(Event.Theta0);
   case DimensionCosTheta1:
      return cos(Event.Theta1);
   case DimensionCosTheta2:
      return cos(Event.Theta2);
   case DimensionL1PT:
      return L1PT;
   case DimensionL1Eta:
      return L1Eta;
   case DimensionL1Phi:
      return L1Phi;
   case DimensionL2PT:
      return L2PT;
   case DimensionL2Eta:
      return L2Eta;
   case DimensionL2Phi:
      return L2Phi;
   case DimensionL3PT:
      return L3PT;
   case DimensionL3Eta:
      return L3Eta;
   case DimensionL3Phi:
      return L3Phi;
   case DimensionL4PT:
      return L4PT;
   case DimensionL4Eta:
      return L4Eta;
   case DimensionL4Phi:
      return L4Phi;
   default:
      cerr << "[ProjectionHelper][GetDimensionValue] Unknown dimension " << dimension
         << endl;
      break;
   }

   return 0;
}

vector<double> ProjectionHelper::GetTotalWeight(const GeneralScalarParameters &P)
{
   const double &A1ZZR = P.ahR;
   const double &A2ZZR = P.aZR;     const double &A2ZZI = P.aZI;
   const double &A3ZZR = P.aZdR;    const double &A3ZZI = P.aZdI;
   const double &A2ZAR = P.aZAR;    const double &A2ZAI = P.aZAI;
   const double &A3ZAR = P.aZAdR;   const double &A3ZAI = P.aZAdI;
   const double &A2AAR = P.aAR;     const double &A2AAI = P.aAI;
   const double &A3AAR = P.aAdR;    const double &A3AAI = P.aAdI;

   vector<double> CombinedWeight(4);
   for(int i = 0; i < 4; i++)
   {
      CombinedWeight[i] = 0;
      
      CombinedWeight[i] = CombinedWeight[i] + Weight[1][i] * A1ZZR * A1ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[2][i] * A2ZZR * A2ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[3][i] * A2ZZI * A2ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[4][i] * A3ZZR * A3ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[5][i] * A3ZZI * A3ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[6][i] * A2ZAR * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[7][i] * A2ZAI * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[8][i] * A3ZAR * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[9][i] * A3ZAI * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[10][i] * A2AAR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[11][i] * A2AAI * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[12][i] * A3AAR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[13][i] * A3AAI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[14][i] * A1ZZR * A2ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[15][i] * A1ZZR * A2ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[16][i] * A1ZZR * A3ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[17][i] * A1ZZR * A3ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[18][i] * A1ZZR * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[19][i] * A1ZZR * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[20][i] * A1ZZR * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[21][i] * A1ZZR * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[22][i] * A1ZZR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[23][i] * A1ZZR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[24][i] * A1ZZR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[25][i] * A1ZZR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[26][i] * A2ZZR * A2ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[27][i] * A2ZZR * A3ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[28][i] * A2ZZR * A3ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[29][i] * A2ZZR * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[30][i] * A2ZZR * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[31][i] * A2ZZR * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[32][i] * A2ZZR * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[33][i] * A2ZZR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[34][i] * A2ZZR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[35][i] * A2ZZR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[36][i] * A2ZZR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[37][i] * A2ZZI * A3ZZR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[38][i] * A2ZZI * A3ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[39][i] * A2ZZI * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[40][i] * A2ZZI * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[41][i] * A2ZZI * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[42][i] * A2ZZI * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[43][i] * A2ZZI * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[44][i] * A2ZZI * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[45][i] * A2ZZI * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[46][i] * A2ZZI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[47][i] * A3ZZR * A3ZZI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[48][i] * A3ZZR * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[49][i] * A3ZZR * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[50][i] * A3ZZR * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[51][i] * A3ZZR * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[52][i] * A3ZZR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[53][i] * A3ZZR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[54][i] * A3ZZR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[55][i] * A3ZZR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[56][i] * A3ZZI * A2ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[57][i] * A3ZZI * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[58][i] * A3ZZI * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[59][i] * A3ZZI * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[60][i] * A3ZZI * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[61][i] * A3ZZI * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[62][i] * A3ZZI * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[63][i] * A3ZZI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[64][i] * A2ZAR * A2ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[65][i] * A2ZAR * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[66][i] * A2ZAR * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[67][i] * A2ZAR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[68][i] * A2ZAR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[69][i] * A2ZAR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[70][i] * A2ZAR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[71][i] * A2ZAI * A3ZAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[72][i] * A2ZAI * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[73][i] * A2ZAI * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[74][i] * A2ZAI * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[75][i] * A2ZAI * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[76][i] * A2ZAI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[77][i] * A3ZAR * A3ZAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[78][i] * A3ZAR * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[79][i] * A3ZAR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[80][i] * A3ZAR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[81][i] * A3ZAR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[82][i] * A3ZAI * A2AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[83][i] * A3ZAI * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[84][i] * A3ZAI * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[85][i] * A3ZAI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[86][i] * A2AAR * A2AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[87][i] * A2AAR * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[88][i] * A2AAR * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[89][i] * A2AAI * A3AAR;
      CombinedWeight[i] = CombinedWeight[i] + Weight[90][i] * A2AAI * A3AAI;
      CombinedWeight[i] = CombinedWeight[i] + Weight[91][i] * A3AAR * A3AAI;
   }

   return CombinedWeight;
}

bool ProjectionHelper::PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(Leptons.Lepton11.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.4)   return false;

   if(Event.ZMass < 40)    return false;
   if(Event.Z2Mass < 12)   return false;
   
   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;
   
   return true;
}

ProjectionHelper::ProjectionHelper(TTree *signaltree, TTree *backgroundtree)
{
   SetTree(true, signaltree);
   SetTree(false, backgroundtree);
}

ProjectionHelper::~ProjectionHelper()
{
}

void ProjectionHelper::SetTree(bool IsSignal, TTree *tree)
{
   if(IsSignal == true)
      SignalTree = tree;
   else
      BackgroundTree = tree;

   if(tree == NULL)
      cerr << "[ProjectionHelper][SetTree] Tree set to NULL." << endl;
   else
      cerr << "[ProjectionHelper][SetTree] Tree set." << endl;

   SetBranchAddress(tree);
}

void ProjectionHelper::FillProjection(TH1D *H, Dimension dimension, double Normalization,
   const GeneralScalarParameters &P, double EEWeight, double MMWeight,
   double EMWeight, double MEWeight, double EEFraction, double MMFraction,
   double EMFraction, double MEFraction)
{
   if(H != NULL)
      FillProjection(*H, dimension, Normalization, P, EEWeight, MMWeight, EMWeight, MEWeight,
         EEFraction, MMFraction, EMFraction, MEFraction);
}

void ProjectionHelper::FillProjection(TH1D &H, Dimension dimension, double Normalization,
   const GeneralScalarParameters &P, double EEWeight, double MMWeight,
   double EMWeight, double MEWeight, double EEFraction, double MMFraction,
   double EMFraction, double MEFraction)
{
   if(SignalTree == NULL || BackgroundTree == NULL)
   {
      cerr << "[ProjectionHelper][FillProjection] Please first set the tree to use!"
         << endl;
      return;
   }

   double EERatio = EEWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double EMRatio = EMWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double MERatio = MEWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double MMRatio = MMWeight / (EEWeight + EMWeight + MEWeight + MMWeight);

   TH1D *HCloneEMSignal = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseEMSignal");
   TH1D *HCloneMESignal = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseMESignal");
   TH1D *HCloneEESignal = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseEESignal");
   TH1D *HCloneMMSignal = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseMMSignal");
   TH1D *HCloneEMBackground = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseEMBackground");
   TH1D *HCloneMEBackground = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseMEBackground");
   TH1D *HCloneEEBackground = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseEEBackground");
   TH1D *HCloneMMBackground = (TH1D *)H.Clone("CloneForProjectionHelperInternalUseMMBackground");
   for(int i = 0; i <= H.GetNbinsX() + 1; i++)
   {
      HCloneEMSignal->SetBinContent(i, 0);
      HCloneMESignal->SetBinContent(i, 0);
      HCloneEESignal->SetBinContent(i, 0);
      HCloneMMSignal->SetBinContent(i, 0);
      HCloneEMBackground->SetBinContent(i, 0);
      HCloneMEBackground->SetBinContent(i, 0);
      HCloneEEBackground->SetBinContent(i, 0);
      HCloneMMBackground->SetBinContent(i, 0);
   }

   int SignalEntryCount = SignalTree->GetEntries();
   for(int iEntry = 0; iEntry < SignalEntryCount && iEntry < MAXENTRY; iEntry++)
   {
      SignalTree->GetEntry(iEntry);

      while(Angles.Phi0 > PI)             Angles.Phi0 = Angles.Phi0 - 2 * PI;
      while(Angles.Phi > PI)              Angles.Phi = Angles.Phi - 2 * PI;
      while(Angles.Phi0 < -PI)            Angles.Phi0 = Angles.Phi0 + 2 * PI;
      while(Angles.Phi < -PI)             Angles.Phi = Angles.Phi + 2 * PI;
      while(ReshuffledAngles.Phi0 > PI)   ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 - 2 * PI;
      while(ReshuffledAngles.Phi > PI)    ReshuffledAngles.Phi = ReshuffledAngles.Phi - 2 * PI;
      while(ReshuffledAngles.Phi0 < -PI)  ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 + 2 * PI;
      while(ReshuffledAngles.Phi < -PI)   ReshuffledAngles.Phi = ReshuffledAngles.Phi + 2 * PI;

      vector<double> TotalWeight = GetTotalWeight(P);
      double PTYWeight = GetPTYDensity(Angles.PTH, Angles.YH) + 1e-10;

      if(PassBaseline2e2mu == true)
      {
         double ExtraWeight = Angles.HMass * Angles.HMass / PTYWeight;

         HCloneEMSignal->Fill(GetDimensionValue(dimension, Angles), TotalWeight[0] * ExtraWeight);
         HCloneMESignal->Fill(GetDimensionValue(dimension, Angles), TotalWeight[1] * ExtraWeight);
      }
      if(PassBaseline4e == true)
      {
         double ExtraWeight = ReshuffledAngles.HMass * ReshuffledAngles.HMass / PTYWeight;

         HCloneEESignal->Fill(GetDimensionValue(dimension, ReshuffledAngles), TotalWeight[2] * ExtraWeight);
         HCloneMMSignal->Fill(GetDimensionValue(dimension, ReshuffledAngles), TotalWeight[3] * ExtraWeight);
      }
   }

   int BackgroundEntryCount = BackgroundTree->GetEntries();
   for(int iEntry = 0; iEntry < BackgroundEntryCount && iEntry < MAXENTRY; iEntry++)
   {
      BackgroundTree->GetEntry(iEntry);

      while(Angles.Phi0 > PI)             Angles.Phi0 = Angles.Phi0 - 2 * PI;
      while(Angles.Phi > PI)              Angles.Phi = Angles.Phi - 2 * PI;
      while(Angles.Phi0 < -PI)            Angles.Phi0 = Angles.Phi0 + 2 * PI;
      while(Angles.Phi < -PI)             Angles.Phi = Angles.Phi + 2 * PI;
      while(ReshuffledAngles.Phi0 > PI)   ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 - 2 * PI;
      while(ReshuffledAngles.Phi > PI)    ReshuffledAngles.Phi = ReshuffledAngles.Phi - 2 * PI;
      while(ReshuffledAngles.Phi0 < -PI)  ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 + 2 * PI;
      while(ReshuffledAngles.Phi < -PI)   ReshuffledAngles.Phi = ReshuffledAngles.Phi + 2 * PI;

      vector<double> TotalWeight(4);
      TotalWeight[0] = Weight[0][0];
      TotalWeight[1] = Weight[0][1];
      TotalWeight[2] = Weight[0][2];
      TotalWeight[3] = Weight[0][3];
      double PTYWeight = GetPTYDensity(Angles.PTH, Angles.YH) + 1e-10;

      if(PassBaseline2e2mu == true)
      {
         double ExtraWeight = Angles.HMass * Angles.HMass / PTYWeight;

         HCloneEMBackground->Fill(GetDimensionValue(dimension, Angles), TotalWeight[0] * ExtraWeight);
         HCloneMEBackground->Fill(GetDimensionValue(dimension, Angles), TotalWeight[1] * ExtraWeight);
      }
      if(PassBaseline4e == true)
      {
         double ExtraWeight = ReshuffledAngles.HMass * ReshuffledAngles.HMass / PTYWeight;

         HCloneEEBackground->Fill(GetDimensionValue(dimension, ReshuffledAngles), TotalWeight[2] * ExtraWeight);
         HCloneMMBackground->Fill(GetDimensionValue(dimension, ReshuffledAngles), TotalWeight[3] * ExtraWeight);
      }
   }

   double Left = H.GetXaxis()->GetBinLowEdge(1);
   double Right = H.GetXaxis()->GetBinUpEdge(H.GetNbinsX());

   double TotalIntegral = HCloneEMSignal->Integral() + HCloneMESignal->Integral()
      + HCloneEESignal->Integral() + HCloneMMSignal->Integral()
      + HCloneEMBackground->Integral() + HCloneMEBackground->Integral()
      + HCloneEEBackground->Integral() + HCloneMMBackground->Integral();

   HCloneEMSignal->Scale((1 - EMFraction) / (HCloneEMSignal->Integral() + TotalIntegral / 1e10));
   HCloneMESignal->Scale((1 - MEFraction) / (HCloneMESignal->Integral() + TotalIntegral / 1e10));
   HCloneEESignal->Scale((1 - EEFraction) / (HCloneEESignal->Integral() + TotalIntegral / 1e10));
   HCloneMMSignal->Scale((1 - MMFraction) / (HCloneMMSignal->Integral() + TotalIntegral / 1e10));
   HCloneEMBackground->Scale(EMFraction / (HCloneEMBackground->Integral() + TotalIntegral / 1e10));
   HCloneMEBackground->Scale(MEFraction / (HCloneMEBackground->Integral() + TotalIntegral / 1e10));
   HCloneEEBackground->Scale(EEFraction / (HCloneEEBackground->Integral() + TotalIntegral / 1e10));
   HCloneMMBackground->Scale(MMFraction / (HCloneMMBackground->Integral() + TotalIntegral / 1e10));

   HCloneEMSignal->Add(HCloneEMBackground);
   HCloneMESignal->Add(HCloneMEBackground);
   HCloneEESignal->Add(HCloneEEBackground);
   HCloneMMSignal->Add(HCloneMMBackground);

   HCloneEMSignal->Scale(Normalization / (Right - Left) * HCloneEMSignal->GetNbinsX() * EMRatio);
   HCloneMESignal->Scale(Normalization / (Right - Left) * HCloneMESignal->GetNbinsX() * MERatio);
   HCloneEESignal->Scale(Normalization / (Right - Left) * HCloneEESignal->GetNbinsX() * EERatio);
   HCloneMMSignal->Scale(Normalization / (Right - Left) * HCloneMMSignal->GetNbinsX() * MMRatio);

   H.Add(HCloneEMSignal);
   H.Add(HCloneMESignal);
   H.Add(HCloneEESignal);
   H.Add(HCloneMMSignal);

   delete HCloneEMSignal;
   delete HCloneMESignal;
   delete HCloneEESignal;
   delete HCloneMMSignal;
   delete HCloneEMBackground;
   delete HCloneMEBackground;
   delete HCloneEEBackground;
   delete HCloneMMBackground;
}

void ProjectionHelper::FillProjection(TH2D *H, Dimension dimension1,
   Dimension dimension2, double Normalization,
   const GeneralScalarParameters &P, double EEWeight, double MMWeight,
   double EMWeight, double MEWeight)
{
   if(H != NULL)
      FillProjection(*H, dimension1, dimension2, Normalization, P, EEWeight, MMWeight, EMWeight, MEWeight);
}

void ProjectionHelper::FillProjection(TH2D &H, Dimension dimension1,
   Dimension dimension2, double Normalization,
   const GeneralScalarParameters &P, double EEWeight, double MMWeight,
   double EMWeight, double MEWeight)
{
   if(SignalTree == NULL || BackgroundTree == NULL)
   {
      cerr << "[ProjectionHelper][FillProjection] Please first set the trees to use!"
         << endl;
      return;
   }
   
   double EEFraction = EEWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double EMFraction = EMWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double MEFraction = MEWeight / (EEWeight + EMWeight + MEWeight + MMWeight);
   double MMFraction = MMWeight / (EEWeight + EMWeight + MEWeight + MMWeight);

   TH2D *HCloneEM = (TH2D *)H.Clone("CloneForProjectionHelperInternalUseEM");
   TH2D *HCloneME = (TH2D *)H.Clone("CloneForProjectionHelperInternalUseME");
   TH2D *HCloneEE = (TH2D *)H.Clone("CloneForProjectionHelperInternalUseEE");
   TH2D *HCloneMM = (TH2D *)H.Clone("CloneForProjectionHelperInternalUseMM");
   for(int i = 0; i <= H.GetNbinsX() + 1; i++)
   {
      for(int j = 0; j <= H.GetNbinsY() + 1; j++)
      {
         HCloneEM->SetBinContent(i, j, 0);
         HCloneME->SetBinContent(i, j, 0);
         HCloneEE->SetBinContent(i, j, 0);
         HCloneMM->SetBinContent(i, j, 0);
      }
   }

   int SignalEntryCount = SignalTree->GetEntries();
   for(int iEntry = 0; iEntry < SignalEntryCount && iEntry < MAXENTRY; iEntry++)
   {
      SignalTree->GetEntry(iEntry);

      while(Angles.Phi0 > PI)             Angles.Phi0 = Angles.Phi0 - 2 * PI;
      while(Angles.Phi > PI)              Angles.Phi = Angles.Phi - 2 * PI;
      while(Angles.Phi0 < -PI)            Angles.Phi0 = Angles.Phi0 + 2 * PI;
      while(Angles.Phi < -PI)             Angles.Phi = Angles.Phi + 2 * PI;
      while(ReshuffledAngles.Phi0 > PI)   ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 - 2 * PI;
      while(ReshuffledAngles.Phi > PI)    ReshuffledAngles.Phi = ReshuffledAngles.Phi - 2 * PI;
      while(ReshuffledAngles.Phi0 < -PI)  ReshuffledAngles.Phi0 = ReshuffledAngles.Phi0 + 2 * PI;
      while(ReshuffledAngles.Phi < -PI)   ReshuffledAngles.Phi = ReshuffledAngles.Phi + 2 * PI;

      vector<double> TotalWeight = GetTotalWeight(P);
      double PTYWeight = GetPTYDensity(Angles.PTH, Angles.YH) + 1e-10;

      if(PassBaseline2e2mu == true)
      {
         HCloneEM->Fill(GetDimensionValue(dimension1, Angles),
            GetDimensionValue(dimension2, Angles),
            TotalWeight[0] / PTYWeight * Angles.HMass * Angles.HMass);
         HCloneME->Fill(GetDimensionValue(dimension1, Angles),
            GetDimensionValue(dimension2, Angles),
            TotalWeight[1] / PTYWeight * Angles.HMass * Angles.HMass);
      }
      if(PassBaseline4e == true)
      {
         HCloneEE->Fill(GetDimensionValue(dimension1, ReshuffledAngles),
            GetDimensionValue(dimension2, ReshuffledAngles),
            TotalWeight[2] / PTYWeight * ReshuffledAngles.HMass * ReshuffledAngles.HMass);
         HCloneMM->Fill(GetDimensionValue(dimension1, ReshuffledAngles),
            GetDimensionValue(dimension2, ReshuffledAngles),
            TotalWeight[3] / PTYWeight * ReshuffledAngles.HMass * ReshuffledAngles.HMass);
      }
   }

   double LeftX = H.GetXaxis()->GetBinLowEdge(1);
   double RightX = H.GetXaxis()->GetBinUpEdge(H.GetNbinsX());
   double LeftY = H.GetYaxis()->GetBinLowEdge(1);
   double RightY = H.GetYaxis()->GetBinUpEdge(H.GetNbinsY());

   double TotalIntegral = HCloneEM->Integral() + HCloneME->Integral() + HCloneEE->Integral() + HCloneMM->Integral();

   HCloneEM->Scale(1 / (HCloneEM->Integral() + TotalIntegral / 1e10));
   HCloneME->Scale(1 / (HCloneME->Integral() + TotalIntegral / 1e10));
   HCloneEE->Scale(1 / (HCloneEE->Integral() + TotalIntegral / 1e10));
   HCloneMM->Scale(1 / (HCloneMM->Integral() + TotalIntegral / 1e10));

   HCloneEM->Scale(Normalization / (RightX - LeftX) / (RightY - LeftY) * H.GetNbinsX() * H.GetNbinsY() * EMFraction);
   HCloneME->Scale(Normalization / (RightX - LeftX) / (RightY - LeftY) * H.GetNbinsX() * H.GetNbinsY() * MEFraction);
   HCloneEE->Scale(Normalization / (RightX - LeftX) / (RightY - LeftY) * H.GetNbinsX() * H.GetNbinsY() * EEFraction);
   HCloneMM->Scale(Normalization / (RightX - LeftX) / (RightY - LeftY) * H.GetNbinsX() * H.GetNbinsY() * MMFraction);

   H.Add(HCloneEM);
   H.Add(HCloneME);
   H.Add(HCloneEE);
   H.Add(HCloneMM);

   delete HCloneEM;
   delete HCloneME;
   delete HCloneEE;
   delete HCloneMM;
}








