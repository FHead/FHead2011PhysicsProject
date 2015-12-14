#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TAxis.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"

#include "Utilities.hcpp"

int main(int argc, char *argv[])
{
   string InputFileName = "ResultTree.root";
   string OutputFileName = "Hehehehe.root";

   if(argc > 1)   InputFileName = argv[1];
   if(argc > 2)   OutputFileName = argv[2];

   double A1ZZR = 0;
   double A2ZZR = 0;   double A2ZZI = 0;
   double A3ZZR = 0;   double A3ZZI = 0;
   double A2ZAR = 0;   double A2ZAI = 0;
   double A3ZAR = 0;   double A3ZAI = 0;
   double A2AAR = 1;   double A2AAI = 0;
   double A3AAR = 0;   double A3AAI = 0;

   gStyle->SetPaintTextFormat(".2e");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HMHem("HMHem", "MH", 100, 100, 160);
   TH1D HM1em("HM1em", "M1", 100, 0, 120);
   TH1D HM2em("HM2em", "M2", 100, 0, 65);
   TH1D HPhi0em("HPhi0em", "Phi0", 100, -PI, PI);
   TH1D HCosTheta0em("HCosTheta0em", "CosTheta0", 100, -1, 1);
   TH1D HPhiem("HPhiem", "Phi", 100, -PI, PI);
   TH1D HCosTheta1em("HCosTheta1em", "CosTheta1", 100, -1, 1);
   TH1D HCosTheta2em("HCosTheta2em", "CosTheta2", 100, -1, 1);
   TH2D HM1M2em("HM1M2em", "M1 vs. M2;M1;M2", 100, 0, 120, 100, 0, 65);
   
   TH1D HMHee("HMHee", "MH", 100, 100, 160);
   TH1D HM1ee("HM1ee", "M1", 100, 0, 120);
   TH1D HM2ee("HM2ee", "M2", 100, 0, 65);
   TH1D HPhi0ee("HPhi0ee", "Phi0", 100, -PI, PI);
   TH1D HCosTheta0ee("HCosTheta0ee", "CosTheta0", 100, -1, 1);
   TH1D HPhiee("HPhiee", "Phi", 100, -PI, PI);
   TH1D HCosTheta1ee("HCosTheta1ee", "CosTheta1", 100, -1, 1);
   TH1D HCosTheta2ee("HCosTheta2ee", "CosTheta2", 100, -1, 1);
   TH2D HM1M2ee("HM1M2ee", "M1 vs. M2;M1;M2", 100, 0, 120, 100, 0, 65);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   double Weight[92][4] = {{0}};
   EventParameters Event2e2mu, Event4e;

   Tree->SetBranchAddress("MH", &Event2e2mu.HMass);
   Tree->SetBranchAddress("M1", &Event2e2mu.ZMass);
   Tree->SetBranchAddress("M2", &Event2e2mu.Z2Mass);
   Tree->SetBranchAddress("Phi0", &Event2e2mu.Phi0);
   Tree->SetBranchAddress("Theta0", &Event2e2mu.Theta0);
   Tree->SetBranchAddress("Phi", &Event2e2mu.Phi);
   Tree->SetBranchAddress("Theta1", &Event2e2mu.Theta1);
   Tree->SetBranchAddress("Theta2", &Event2e2mu.Theta2);
   Tree->SetBranchAddress("HPT", &Event2e2mu.PTH);
   Tree->SetBranchAddress("HPhi", &Event2e2mu.PhiH);
   Tree->SetBranchAddress("HY", &Event2e2mu.YH);
   Tree->SetBranchAddress("PhiOffset", &Event2e2mu.PhiOffset);
   Tree->SetBranchAddress("RecalculatedMH", &Event4e.HMass);
   Tree->SetBranchAddress("RecalculatedM1", &Event4e.ZMass);
   Tree->SetBranchAddress("RecalculatedM2", &Event4e.Z2Mass);
   Tree->SetBranchAddress("RecalculatedPhi0", &Event4e.Phi0);
   Tree->SetBranchAddress("RecalculatedTheta0", &Event4e.Theta0);
   Tree->SetBranchAddress("RecalculatedPhi", &Event4e.Phi);
   Tree->SetBranchAddress("RecalculatedTheta1", &Event4e.Theta1);
   Tree->SetBranchAddress("RecalculatedTheta2", &Event4e.Theta2);
   Tree->SetBranchAddress("RecalculatedHPT", &Event4e.PTH);
   Tree->SetBranchAddress("RecalculatedHPhi", &Event4e.PhiH);
   Tree->SetBranchAddress("RecalculatedHY", &Event4e.YH);
   Tree->SetBranchAddress("RecalculatedPhiOffset", &Event4e.PhiOffset);
   Tree->SetBranchAddress("Weight", Weight);

   int EntryCount = Tree->GetEntries();

   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % (EntryCount / 300) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      if(Event4e.Phi > PI)    Event4e.Phi = Event4e.Phi - 2 * PI;
      if(Event4e.Phi0 > PI)   Event4e.Phi0 = Event4e.Phi0 - 2 * PI;

      LeptonVectors Lepton2e2mu = ConvertAnglesToVectorsRoberto(Event2e2mu);
      LeptonVectors Lepton4e = ConvertAnglesToVectorsRoberto(Event4e);

      double Weight2e2mu = Event2e2mu.ZMass * Event2e2mu.Z2Mass;
      double Weight4e = Event2e2mu.ZMass * Event2e2mu.Z2Mass;

      bool PassLoose2e2mu = LooseCut2e2mu(Lepton2e2mu);
      bool PassLoose4e = LooseCut4e(Lepton4e);

      double CombinedWeight2e2mu = 0;
      double CombinedWeight4e = 0;

      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[1][0] * A1ZZR * A1ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[2][0] * A2ZZR * A2ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[3][0] * A2ZZI * A2ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[4][0] * A3ZZR * A3ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[5][0] * A3ZZI * A3ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[6][0] * A2ZAR * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[7][0] * A2ZAI * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[8][0] * A3ZAR * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[9][0] * A3ZAI * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[10][0] * A2AAR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[11][0] * A2AAI * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[12][0] * A3AAR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[13][0] * A3AAI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[14][0] * A1ZZR * A2ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[15][0] * A1ZZR * A2ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[16][0] * A1ZZR * A3ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[17][0] * A1ZZR * A3ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[18][0] * A1ZZR * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[19][0] * A1ZZR * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[20][0] * A1ZZR * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[21][0] * A1ZZR * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[22][0] * A1ZZR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[23][0] * A1ZZR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[24][0] * A1ZZR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[25][0] * A1ZZR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[26][0] * A2ZZR * A2ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[27][0] * A2ZZR * A3ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[28][0] * A2ZZR * A3ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[29][0] * A2ZZR * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[30][0] * A2ZZR * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[31][0] * A2ZZR * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[32][0] * A2ZZR * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[33][0] * A2ZZR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[34][0] * A2ZZR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[35][0] * A2ZZR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[36][0] * A2ZZR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[37][0] * A2ZZI * A3ZZR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[38][0] * A2ZZI * A3ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[39][0] * A2ZZI * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[40][0] * A2ZZI * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[41][0] * A2ZZI * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[42][0] * A2ZZI * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[43][0] * A2ZZI * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[44][0] * A2ZZI * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[45][0] * A2ZZI * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[46][0] * A2ZZI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[47][0] * A3ZZR * A3ZZI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[48][0] * A3ZZR * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[49][0] * A3ZZR * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[50][0] * A3ZZR * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[51][0] * A3ZZR * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[52][0] * A3ZZR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[53][0] * A3ZZR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[54][0] * A3ZZR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[55][0] * A3ZZR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[56][0] * A3ZZI * A2ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[57][0] * A3ZZI * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[58][0] * A3ZZI * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[59][0] * A3ZZI * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[60][0] * A3ZZI * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[61][0] * A3ZZI * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[62][0] * A3ZZI * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[63][0] * A3ZZI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[64][0] * A2ZAR * A2ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[65][0] * A2ZAR * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[66][0] * A2ZAR * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[67][0] * A2ZAR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[68][0] * A2ZAR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[69][0] * A2ZAR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[70][0] * A2ZAR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[71][0] * A2ZAI * A3ZAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[72][0] * A2ZAI * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[73][0] * A2ZAI * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[74][0] * A2ZAI * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[75][0] * A2ZAI * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[76][0] * A2ZAI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[77][0] * A3ZAR * A3ZAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[78][0] * A3ZAR * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[79][0] * A3ZAR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[80][0] * A3ZAR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[81][0] * A3ZAR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[82][0] * A3ZAI * A2AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[83][0] * A3ZAI * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[84][0] * A3ZAI * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[85][0] * A3ZAI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[86][0] * A2AAR * A2AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[87][0] * A2AAR * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[88][0] * A2AAR * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[89][0] * A2AAI * A3AAR;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[90][0] * A2AAI * A3AAI;
      CombinedWeight2e2mu = CombinedWeight2e2mu + Weight[91][0] * A3AAR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[1][1] * A1ZZR * A1ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[2][1] * A2ZZR * A2ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[3][1] * A2ZZI * A2ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[4][1] * A3ZZR * A3ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[5][1] * A3ZZI * A3ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[6][1] * A2ZAR * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[7][1] * A2ZAI * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[8][1] * A3ZAR * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[9][1] * A3ZAI * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[10][1] * A2AAR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[11][1] * A2AAI * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[12][1] * A3AAR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[13][1] * A3AAI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[14][1] * A1ZZR * A2ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[15][1] * A1ZZR * A2ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[16][1] * A1ZZR * A3ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[17][1] * A1ZZR * A3ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[18][1] * A1ZZR * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[19][1] * A1ZZR * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[20][1] * A1ZZR * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[21][1] * A1ZZR * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[22][1] * A1ZZR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[23][1] * A1ZZR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[24][1] * A1ZZR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[25][1] * A1ZZR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[26][1] * A2ZZR * A2ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[27][1] * A2ZZR * A3ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[28][1] * A2ZZR * A3ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[29][1] * A2ZZR * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[30][1] * A2ZZR * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[31][1] * A2ZZR * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[32][1] * A2ZZR * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[33][1] * A2ZZR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[34][1] * A2ZZR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[35][1] * A2ZZR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[36][1] * A2ZZR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[37][1] * A2ZZI * A3ZZR;
      CombinedWeight4e = CombinedWeight4e + Weight[38][1] * A2ZZI * A3ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[39][1] * A2ZZI * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[40][1] * A2ZZI * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[41][1] * A2ZZI * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[42][1] * A2ZZI * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[43][1] * A2ZZI * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[44][1] * A2ZZI * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[45][1] * A2ZZI * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[46][1] * A2ZZI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[47][1] * A3ZZR * A3ZZI;
      CombinedWeight4e = CombinedWeight4e + Weight[48][1] * A3ZZR * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[49][1] * A3ZZR * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[50][1] * A3ZZR * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[51][1] * A3ZZR * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[52][1] * A3ZZR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[53][1] * A3ZZR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[54][1] * A3ZZR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[55][1] * A3ZZR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[56][1] * A3ZZI * A2ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[57][1] * A3ZZI * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[58][1] * A3ZZI * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[59][1] * A3ZZI * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[60][1] * A3ZZI * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[61][1] * A3ZZI * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[62][1] * A3ZZI * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[63][1] * A3ZZI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[64][1] * A2ZAR * A2ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[65][1] * A2ZAR * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[66][1] * A2ZAR * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[67][1] * A2ZAR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[68][1] * A2ZAR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[69][1] * A2ZAR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[70][1] * A2ZAR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[71][1] * A2ZAI * A3ZAR;
      CombinedWeight4e = CombinedWeight4e + Weight[72][1] * A2ZAI * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[73][1] * A2ZAI * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[74][1] * A2ZAI * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[75][1] * A2ZAI * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[76][1] * A2ZAI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[77][1] * A3ZAR * A3ZAI;
      CombinedWeight4e = CombinedWeight4e + Weight[78][1] * A3ZAR * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[79][1] * A3ZAR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[80][1] * A3ZAR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[81][1] * A3ZAR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[82][1] * A3ZAI * A2AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[83][1] * A3ZAI * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[84][1] * A3ZAI * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[85][1] * A3ZAI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[86][1] * A2AAR * A2AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[87][1] * A2AAR * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[88][1] * A2AAR * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[89][1] * A2AAI * A3AAR;
      CombinedWeight4e = CombinedWeight4e + Weight[90][1] * A2AAI * A3AAI;
      CombinedWeight4e = CombinedWeight4e + Weight[91][1] * A3AAR * A3AAI;

      if(PassLoose2e2mu == true)
      {
         HMHem.Fill(Event2e2mu.HMass, CombinedWeight2e2mu * Weight2e2mu);
         HM1em.Fill(Event2e2mu.ZMass, CombinedWeight2e2mu * Weight2e2mu);
         HM2em.Fill(Event2e2mu.Z2Mass, CombinedWeight2e2mu * Weight2e2mu);
         HPhi0em.Fill(Event2e2mu.Phi0, CombinedWeight2e2mu * Weight2e2mu);
         HCosTheta0em.Fill(cos(Event2e2mu.Theta0), CombinedWeight2e2mu * Weight2e2mu);
         HPhiem.Fill(Event2e2mu.Phi, CombinedWeight2e2mu * Weight2e2mu);
         HCosTheta1em.Fill(cos(Event2e2mu.Theta1), CombinedWeight2e2mu * Weight2e2mu);
         HCosTheta2em.Fill(cos(Event2e2mu.Theta2), CombinedWeight2e2mu * Weight2e2mu);
         HM1M2em.Fill(Event2e2mu.ZMass, Event2e2mu.Z2Mass, CombinedWeight2e2mu * Weight2e2mu);
      }
      if(PassLoose4e == true)
      {
         HMHee.Fill(Event4e.HMass, CombinedWeight4e * Weight4e);
         HM1ee.Fill(Event4e.ZMass, CombinedWeight4e * Weight4e);
         HM2ee.Fill(Event4e.Z2Mass, CombinedWeight4e * Weight4e);
         HPhi0ee.Fill(Event4e.Phi0, CombinedWeight4e * Weight4e);
         HCosTheta0ee.Fill(cos(Event4e.Theta0), CombinedWeight4e * Weight4e);
         HPhiee.Fill(Event4e.Phi, CombinedWeight4e * Weight4e);
         HCosTheta1ee.Fill(cos(Event4e.Theta1), CombinedWeight4e * Weight4e);
         HCosTheta2ee.Fill(cos(Event4e.Theta2), CombinedWeight4e * Weight4e);
         HM1M2ee.Fill(Event4e.ZMass, Event4e.Z2Mass, CombinedWeight4e * Weight4e);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   PsFileHelper PsFile("Projections.ps");
   PsFile.AddTextPage("Projections");

   PsFile.AddTextPage("2e2mu");
   PsFile.AddPlot(HMHem, "", false);
   PsFile.AddPlot(HMHem, "", true);
   PsFile.AddPlot(HM1em, "", false);
   PsFile.AddPlot(HM1em, "", true);
   PsFile.AddPlot(HM2em, "", false);
   PsFile.AddPlot(HM2em, "", true);
   PsFile.AddPlot(HPhi0em, "", false);
   PsFile.AddPlot(HPhi0em, "", true);
   PsFile.AddPlot(HCosTheta0em, "", false);
   PsFile.AddPlot(HCosTheta0em, "", true);
   PsFile.AddPlot(HPhiem, "", false);
   PsFile.AddPlot(HPhiem, "", true);
   PsFile.AddPlot(HCosTheta1em, "", false);
   PsFile.AddPlot(HCosTheta1em, "", true);
   PsFile.AddPlot(HCosTheta2em, "", false);
   PsFile.AddPlot(HCosTheta2em, "", true);
   PsFile.AddPlot(HM1M2em, "colz", false, false);
   PsFile.AddPlot(HM1M2em, "colz", false, true);
   
   PsFile.AddTextPage("4e");
   PsFile.AddPlot(HMHee, "", false);
   PsFile.AddPlot(HMHee, "", true);
   PsFile.AddPlot(HM1ee, "", false);
   PsFile.AddPlot(HM1ee, "", true);
   PsFile.AddPlot(HM2ee, "", false);
   PsFile.AddPlot(HM2ee, "", true);
   PsFile.AddPlot(HPhi0ee, "", false);
   PsFile.AddPlot(HPhi0ee, "", true);
   PsFile.AddPlot(HCosTheta0ee, "", false);
   PsFile.AddPlot(HCosTheta0ee, "", true);
   PsFile.AddPlot(HPhiee, "", false);
   PsFile.AddPlot(HPhiee, "", true);
   PsFile.AddPlot(HCosTheta1ee, "", false);
   PsFile.AddPlot(HCosTheta1ee, "", true);
   PsFile.AddPlot(HCosTheta2ee, "", false);
   PsFile.AddPlot(HCosTheta2ee, "", true);
   PsFile.AddPlot(HM1M2ee, "colz", false, false);
   PsFile.AddPlot(HM1M2ee, "colz", false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.cd();
   
   HMHem.Write();          HMHee.Write();
   HM1em.Write();          HM1ee.Write();
   HM2em.Write();          HM2ee.Write();
   HPhi0em.Write();        HPhi0ee.Write();
   HCosTheta0em.Write();   HCosTheta0ee.Write();
   HPhiem.Write();         HPhiee.Write();
   HCosTheta1em.Write();   HCosTheta1ee.Write();
   HCosTheta2em.Write();   HCosTheta2ee.Write();
   HM1M2em.Write();        HM1M2ee.Write();

   OutputFile.Close();

   return 0;
}


