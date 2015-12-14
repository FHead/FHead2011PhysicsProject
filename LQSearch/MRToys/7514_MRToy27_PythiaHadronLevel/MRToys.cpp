#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName);
double GetDifference8(FourVector &P1, FourVector &P2, FourVector &ME, double BetaX);
double GetDifference9(FourVector &P1, FourVector &P2, FourVector &ME, double BetaZ);
double EstimateMass(FourVector J1, FourVector J2, FourVector ME, FourVector ISR);
double EstimateTransverseMass(FourVector J1, FourVector J2, FourVector ME, FourVector ISR, char Variant);
double FindMR11MinimumPz(FourVector J1, FourVector J2, FourVector ME, FourVector ISR);
int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID);
int TraceBHadron(GenParticleTree &Tree, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi);
double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy27_ISRScaled.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 27");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   DoToyAndAppendPlots(PsFile, 150, "LQ150.root");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("OutputTree", "Tree! ®");

   double B1E, B1x, B1y, B1z;
   double B2E, B2x, B2y, B2z;
   double Nu1E, Nu1x, Nu1y, Nu1z;
   double Nu2E, Nu2x, Nu2y, Nu2z;
   double RealBeta;
   double BlindMR, BlindR;
   double MR1, R1, Beta1;
   double MR2, R2, Beta2;
   double MR3, R3, Beta3;
   double MR4, R4, Beta4;
   double MR5, R5, Beta5;
   double MR6, R6, Beta6;
   double MR7, R7, Beta7;
   double MR8, R8, Beta8, MinimumDifference8;
   double MR9, R9, Beta9, MinimumDifference9;
   double MR10, R10, Beta10, MinimumDifference10;
   double MR11, R11a, R11b, R11c, R11d, R11e, R11f, R11g, Beta11;

   OutputTree.Branch("B1E", &B1E, "B1E/D");
   OutputTree.Branch("B1x", &B1x, "B1x/D");
   OutputTree.Branch("B1y", &B1y, "B1y/D");
   OutputTree.Branch("B1z", &B1z, "B1z/D");
   OutputTree.Branch("B2E", &B2E, "B2E/D");
   OutputTree.Branch("B2x", &B2x, "B2x/D");
   OutputTree.Branch("B2y", &B2y, "B2y/D");
   OutputTree.Branch("B2z", &B2z, "B2z/D");
   OutputTree.Branch("Nu1E", &Nu1E, "Nu1E/D");
   OutputTree.Branch("Nu1x", &Nu1x, "Nu1x/D");
   OutputTree.Branch("Nu1y", &Nu1y, "Nu1y/D");
   OutputTree.Branch("Nu1z", &Nu1z, "Nu1z/D");
   OutputTree.Branch("Nu2E", &Nu2E, "Nu2E/D");
   OutputTree.Branch("Nu2x", &Nu2x, "Nu2x/D");
   OutputTree.Branch("Nu2y", &Nu2y, "Nu2y/D");
   OutputTree.Branch("Nu2z", &Nu2z, "Nu2z/D");
   OutputTree.Branch("RealBeta", &RealBeta, "RealBeta/D");
   OutputTree.Branch("BlindMR", &BlindMR, "BlindMR/D");
   OutputTree.Branch("BlindR", &BlindR, "BlindR/D");
   OutputTree.Branch("MR1", &MR1, "MR1/D");
   OutputTree.Branch("R1", &R1, "R1/D");
   OutputTree.Branch("Beta1", &Beta1, "Beta1/D");
   OutputTree.Branch("MR2", &MR2, "MR2/D");
   OutputTree.Branch("R2", &R2, "R2/D");
   OutputTree.Branch("Beta2", &Beta2, "Beta2/D");
   OutputTree.Branch("MR3", &MR3, "MR3/D");
   OutputTree.Branch("R3", &R3, "R3/D");
   OutputTree.Branch("Beta3", &Beta3, "Beta3/D");
   OutputTree.Branch("MR4", &MR4, "MR4/D");
   OutputTree.Branch("R4", &R4, "R4/D");
   OutputTree.Branch("Beta4", &Beta4, "Beta4/D");
   OutputTree.Branch("MR5", &MR5, "MR5/D");
   OutputTree.Branch("R5", &R5, "R5/D");
   OutputTree.Branch("Beta5", &Beta5, "Beta5/D");
   OutputTree.Branch("MR6", &MR6, "MR6/D");
   OutputTree.Branch("R6", &R6, "R6/D");
   OutputTree.Branch("Beta6", &Beta6, "Beta6/D");
   OutputTree.Branch("MR7", &MR7, "MR7/D");
   OutputTree.Branch("R7", &R7, "R7/D");
   OutputTree.Branch("Beta7", &Beta7, "Beta7/D");
   OutputTree.Branch("MR8", &MR8, "MR8/D");
   OutputTree.Branch("R8", &R8, "R8/D");
   OutputTree.Branch("Beta8", &Beta8, "Beta8/D");
   OutputTree.Branch("MinimumDifference8", &MinimumDifference8, "MinimumDifference8/D");
   OutputTree.Branch("MR9", &MR9, "MR9/D");
   OutputTree.Branch("R9", &R9, "R9/D");
   OutputTree.Branch("Beta9", &Beta9, "Beta9/D");
   OutputTree.Branch("MinimumDifference9", &MinimumDifference9, "MinimumDifference9/D");
   OutputTree.Branch("MR10", &MR10, "MR10/D");
   OutputTree.Branch("R10", &R10, "R10/D");
   OutputTree.Branch("Beta10", &Beta10, "Beta10/D");
   OutputTree.Branch("MinimumDifference10", &MinimumDifference10, "MinimumDifference10/D");
   OutputTree.Branch("MR11", &MR11, "MR11/D");
   OutputTree.Branch("R11a", &R11a, "R11a/D");
   OutputTree.Branch("R11b", &R11b, "R11b/D");
   OutputTree.Branch("R11c", &R11c, "R11c/D");
   OutputTree.Branch("R11d", &R11d, "R11d/D");
   OutputTree.Branch("R11e", &R11e, "R11e/D");
   OutputTree.Branch("R11f", &R11f, "R11f/D");
   OutputTree.Branch("R11g", &R11g, "R11g/D");
   OutputTree.Branch("Beta11", &Beta11, "Beta11/D");
   
   stringstream LQMassStream;
   LQMassStream << "42: m0 = " << LQMass;

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("42:0:products = 5 16");              // Force decay to b nu_tau
   pythia.readString(LQMassStream.str().c_str());          // LQ mass set to input value
   pythia.readString("LeptoQuark:gg2LQLQbar = on");        // production mechanism: gg
   pythia.readString("LeptoQuark:qqbar2LQLQbar = on");     // production mechanism: qqbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   int EntryCount = 10000;
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      // Generate event
      pythia.next();

      // Particles
      vector<GenParticle> Particles(pythia.event.size());

      // Loop over particles
      for(int j = 0; j < pythia.event.size(); j++)
      {
         Particles[j].P[0] = pythia.event[j].e();
         Particles[j].P[1] = pythia.event[j].px();
         Particles[j].P[2] = pythia.event[j].py();
         Particles[j].P[3] = pythia.event[j].pz();

         Particles[j].V[0] = pythia.event[j].tProd();
         Particles[j].V[1] = pythia.event[j].xProd();
         Particles[j].V[2] = pythia.event[j].yProd();
         Particles[j].V[3] = pythia.event[j].zProd();

         Particles[j].PDGID = pythia.event[j].id();
         Particles[j].StatusCode = pythia.event.statusHepMC(j);

         Particles[j].Mothers = pythia.event.motherList(j);
         Particles[j].Daughters = pythia.event.daughterList(j);
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // Add up everything
      FourVector TotalInTheEvent(0, 0, 0, 0);
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;
         if(FourVector(Tree[j].P).GetAbsEta() > 3)
            continue;

         TotalInTheEvent = TotalInTheEvent + FourVector(Tree[j].P);
      }

      // find b's and nu's
      int B1Index = FindChildIndex(Tree, 5, 42);
      int B2Index = FindChildIndex(Tree, -5, -42);
      int Nu1Index = FindChildIndex(Tree, 16, 42);
      int Nu2Index = FindChildIndex(Tree, -16, -42);

      B1E = Tree[B1Index].P[0];
      B1x = Tree[B1Index].P[1];
      B1y = Tree[B1Index].P[2];
      B1z = Tree[B1Index].P[3];
      B2E = Tree[B2Index].P[0];
      B2x = Tree[B2Index].P[1];
      B2y = Tree[B2Index].P[2];
      B2z = Tree[B2Index].P[3];
      Nu1E = Tree[Nu1Index].P[0];
      Nu1x = Tree[Nu1Index].P[1];
      Nu1y = Tree[Nu1Index].P[2];
      Nu1z = Tree[Nu1Index].P[3];
      Nu2E = Tree[Nu2Index].P[0];
      Nu2x = Tree[Nu2Index].P[1];
      Nu2y = Tree[Nu2Index].P[2];
      Nu2z = Tree[Nu2Index].P[3];

      FourVector B1P = Tree[B1Index].P;
      FourVector B2P = Tree[B2Index].P;
      FourVector Nu1P = Tree[Nu1Index].P;
      FourVector Nu2P = Tree[Nu2Index].P;
      FourVector ME = Nu1P + Nu2P;

      FourVector Total = B1P + B2P + Nu1P + Nu2P;
      RealBeta = Total.GetPT() / Total[0];

      // extra jets
      FourVector ExtraJets = TotalInTheEvent - Total;

      // calculate various MR and R's

      // Blind
      BlindMR = Get2011MR(B1P, B2P);
      BlindR = Get2011R(B1P, B2P, ME);

      // Assumption 1 - ME3 = 0, ME0 = |MET|
      FourVector ME1 = ME;
      ME1[3] = 0;
      ME1[0] = ME1.GetP();

      FourVector Total1 = B1P + B2P + ME1;
      Beta1 = Total1.GetPT() / Total1[0];
      Total1[3] = 0;
      FourVector B1P1 = B1P.Boost(-Total1, Beta1);
      FourVector B2P1 = B2P.Boost(-Total1, Beta1);
      ME1 = ME1.Boost(-Total1, Beta1);

      MR1 = Get2011MR(B1P1, B2P1);
      R1 = Get2011R(B1P1, B2P1, ME1);

      // Assumption 2 - Projection of ME to J1 and J2 are massless, ME[3] = 0
      FourVector ME2 = ME;
      ME2[3] = 0;
      double Bottom = B1P.SpatialDot(B2P) * B1P.SpatialDot(B2P) - B1P.GetP2() * B2P.GetP2();
      double Projection1Top = B2P.SpatialDot(ME2) * B2P.SpatialDot(B1P) - B1P.SpatialDot(ME2) * B2P.GetP2();
      double Projection2Top = B1P.SpatialDot(ME2) * B1P.SpatialDot(B2P) - B2P.SpatialDot(ME2) * B1P.GetP2();
      FourVector ME2B1Projection = B1P * Projection1Top / Bottom;
      FourVector ME2B2Projection = B2P * Projection2Top / Bottom;
      ME2[0] = ME2B1Projection.GetP() + ME2B2Projection.GetP();

      FourVector Total2 = B1P + B2P + ME2;
      Beta2 = Total2.GetPT() / Total2[0];
      Total2[3] = 0;
      FourVector B1P2 = B1P.Boost(-Total2, Beta2);
      FourVector B2P2 = B2P.Boost(-Total2, Beta2);
      ME2 = ME2.Boost(-Total2, Beta2);

      MR2 = Get2011MR(B1P2, B2P2);
      R2 = Get2011R(B1P2, B2P2, ME2);

      // Assumption 3 - ME[3] = -(j1[3] + j2[3]), massless
      FourVector ME3 = ME;
      ME3[3] = -(B1P[3] + B2P[3]);
      ME3[0] = ME3.GetP();

      FourVector Total3 = B1P + B2P + ME3;
      Beta3 = Total3.GetPT() / Total3[0];
      Total3[3] = 0;
      FourVector B1P3 = B1P.Boost(-Total3, Beta3);
      FourVector B2P3 = B2P.Boost(-Total3, Beta3);
      ME3 = ME3.Boost(-Total3, Beta3);

      MR3 = Get2011MR(B1P3, B2P3);
      R3 = Get2011R(B1P3, B2P3, ME3);

      // Assumption 4 - Projection of ME to J1 and J2 are massless, ME[3] = -(j1[3] + j2[3])
      FourVector ME4 = ME;
      ME4[3] = -(B1P[3] + B2P[3]);
      double Bottom4 = B1P.SpatialDot(B2P) * B1P.SpatialDot(B2P) - B1P.GetP2() * B2P.GetP2();
      double Projection1Top4 = B2P.SpatialDot(ME4) * B2P.SpatialDot(B1P) - B1P.SpatialDot(ME4) * B2P.GetP2();
      double Projection2Top4 = B1P.SpatialDot(ME4) * B1P.SpatialDot(B2P) - B2P.SpatialDot(ME4) * B1P.GetP2();
      FourVector ME2B1Projection4 = B1P * Projection1Top4 / Bottom4;
      FourVector ME2B2Projection4 = B2P * Projection2Top4 / Bottom4;
      ME4[0] = ME2B1Projection4.GetP() + ME2B2Projection4.GetP();

      FourVector Total4 = B1P + B2P + ME4;
      Beta4 = Total4.GetPT() / Total4[0];
      Total4[3] = 0;
      FourVector B1P4 = B1P.Boost(-Total4, Beta4);
      FourVector B2P4 = B2P.Boost(-Total4, Beta4);
      ME4 = ME4.Boost(-Total4, Beta4);

      MR4 = Get2011MR(B1P4, B2P4);
      R4 = Get2011R(B1P4, B2P4, ME4);

      // Assumption 5 - 2D projection!! - ME[3] assumed to be zero
      FourVector B1PTemp5 = B1P;
      FourVector B2PTemp5 = B2P;
      FourVector METemp5 = ME;
      FourVector Total5 = B1P + B2P + ME;

      B1PTemp5[3] = 0;   B1PTemp5[0] = B1PTemp5.GetPT();
      B2PTemp5[3] = 0;   B2PTemp5[0] = B2PTemp5.GetPT();
      METemp5[3] = 0;
      Total5[3] = 0;

      B1PTemp5 = B1PTemp5.RotateZ(-Total5.GetPhi());
      B2PTemp5 = B2PTemp5.RotateZ(-Total5.GetPhi());
      METemp5 = METemp5.RotateZ(-Total5.GetPhi());

      // visible: particle 1 (B1) and 3 (B2), partners: particle 2 and 4
      // rotated so that boost is in the x direction
      // y direction is then trivial
      double P2XPrime5 = (B1PTemp5[1] + B2PTemp5[1] + METemp5[1]) / 2 - B1PTemp5[1];
      double P2YPrime5 = -B1PTemp5[2];
      double P4XPrime5 = (B1PTemp5[1] + B2PTemp5[1] + METemp5[1]) / 2 - B2PTemp5[1];
      double P4YPrime5 = -B2PTemp5[2];
      double E2 = sqrt(P2XPrime5 * P2XPrime5 + P2YPrime5 * P2YPrime5);
      double E4 = sqrt(P4XPrime5 * P4XPrime5 + P4YPrime5 * P4YPrime5);
      Beta5 = (B1PTemp5[1] + P2XPrime5 + B2PTemp5[1] + P4XPrime5) / (B1PTemp5[0] + E2 + B2PTemp5[0] + E4);
      METemp5[0] = E2 + E4;

      /*
      FourVector Temp5 = B1PTemp5 + B2PTemp5 + METemp5;
      cout << "Rotated total: " << Temp5 << ", Beta =  " << Beta5 << endl;
      cout << "Boosted 1: " << Temp5.BoostX(-Beta5) << endl;
      cout << "Boosted 2: " << Temp5.BoostX(Beta5) << endl;
      */

      FourVector ME5 = ME;
      ME5[3] = 0;
      ME5[0] = sqrt((E2 + E4) * (E2 + E4) + ME5[3] * ME5[3]);

      FourVector B1P5 = B1P.Boost(-Total5, Beta5);
      FourVector B2P5 = B2P.Boost(-Total5, Beta5);
      ME5 = ME5.Boost(-Total5, Beta5);

      MR5 = Get2011MR(B1P5, B2P5);
      R5 = Get2011R(B1P5, B2P5, ME5);

      // Assumption 6 - better calculation than #5, E1 = E2 != E3 = E4
      FourVector B1PTemp6 = B1PTemp5;
      FourVector B2PTemp6 = B2PTemp5;
      FourVector METemp6 = METemp5;

      double E13_6 = B1PTemp6[0] + B2PTemp6[0];
      double P13x_6 = B1PTemp6[1] + B2PTemp6[1];
      double P24x_6 = METemp6[1];
      double P1234x_6 = P13x_6 + P24x_6;
      Beta6 = (-E13_6 + sqrt(E13_6 * E13_6 + P24x_6 * P24x_6 - P13x_6 * P13x_6)) / P1234x_6;

      double E24_6 = (-P1234x_6 - Beta6 * E13_6) / Beta6;

      // double Beta6_1 = (-E13_6 + sqrt(E13_6 * E13_6 + P24x_6 * P24x_6 - P13x_6 * P13x_6)) / P1234x_6;
      // double Beta6_2 = (-E13_6 - sqrt(E13_6 * E13_6 + P24x_6 * P24x_6 - P13x_6 * P13x_6)) / P1234x_6;
      // cout << Beta6_1 << " " << Beta6_2 << endl;

      FourVector ME6 = METemp6;
      ME6[3] = 0;
      ME6[0] = sqrt(E24_6 * E24_6 + ME6[3] * ME6[3]);

      FourVector Total6 = B1PTemp6 + B2PTemp6 + ME6;
      FourVector B1P6 = B1PTemp6.Boost(-Total6, fabs(Beta6));
      FourVector B2P6 = B2PTemp6.Boost(-Total6, fabs(Beta6));
      ME6 = ME6.Boost(-Total6, fabs(Beta6));

      MR6 = Get2011MR(B1P6, B2P6);
      R6 = Get2011R(B1P6, B2P6, ME6);

      // Assumption 7 - after transverse boost, E(j1) + E(j2) = E(nu1) + E(nu2)
      FourVector B1PTemp7 = B1P;
      FourVector B2PTemp7 = B2P;
      FourVector METemp7 = ME;
      FourVector Total7 = B1P + B2P + ME;

      B1PTemp7 = B1PTemp7.RotateZ(-Total7.GetPhi());
      B2PTemp7 = B2PTemp7.RotateZ(-Total7.GetPhi());
      METemp7 = METemp7.RotateZ(-Total7.GetPhi());

      double PxJet7 = B1PTemp7[1] + B2PTemp7[1];
      double EJet7 = B1PTemp7[0] + B2PTemp7[0];

      // Beta7 = (EJet7 + sqrt(EJet7 * EJet7 - PxJet7 * PxJet7 + METemp7[1] * METemp7[1])) / (PxJet7 - METemp7[1]);
      // cout << Beta7 << endl;
      Beta7 = (EJet7 - sqrt(EJet7 * EJet7 - PxJet7 * PxJet7 + METemp7[1] * METemp7[1])) / (PxJet7 - METemp7[1]);

      METemp7[3] = 0;
      METemp7[0] = EJet7 + Beta7 * (METemp7[1] - PxJet7);

      Total7 = B1PTemp7 + B2PTemp7 + METemp7;
      FourVector B1P7 = B1PTemp7.Boost(-Total7, -Beta7);
      FourVector B2P7 = B2PTemp7.Boost(-Total7, -Beta7);
      FourVector ME7 = METemp7.Boost(-Total7, -Beta7);

      MR7 = Get2011MR(B1P7, B2P7);
      R7 = Get2011R(B1P7, B2P7, ME7);

      // Assumption 8 - trasverse boost + longitudinal boost!
      FourVector B1PTemp8 = B1PTemp7;
      FourVector B2PTemp8 = B2PTemp7;
      FourVector METemp8 = METemp7;

      double MinimumBetaX = 1000;
      double MinimumDifference = 999999;
      double SearchCenter = 0;
      double SearchStep = 0.1;
      for(int i = 0; i < 5; i++)
      {
         for(double BetaX = SearchCenter - SearchStep * 10; BetaX < SearchCenter + SearchStep * 10;
            BetaX = BetaX + SearchStep)
         {
            double Difference = GetDifference8(B1PTemp8, B2PTemp8, METemp8, BetaX);

            if(fabs(Difference) < MinimumDifference)
            {
               MinimumBetaX = BetaX;
               MinimumDifference = fabs(Difference);
            }
         }

         SearchCenter = MinimumBetaX;
         SearchStep = SearchStep / 10;
      }
         
      Beta8 = MinimumBetaX;
      MinimumDifference8 = MinimumDifference;

      double GammaX8 = BetaToGamma(Beta8);
      double BetaZ8 = GammaX8 * ((B1PTemp8[0] - B2PTemp8[0]) - Beta8 * (B1PTemp8[1] - B2PTemp8[1]))
         / (B1P[3] - B2P[3]);
      double GammaZ8 = BetaToGamma(BetaZ8);
      double Beta8E8 = METemp8[1] + B1PTemp8[1] + B2PTemp8[1] - Beta8 * (B1PTemp8[0] + B2PTemp8[0]);

      double FinalMEx = GammaX8 * METemp8[1] - GammaX8 * Beta8E8;
      double FinalMEy = METemp8[2];
      double FinalMET = sqrt(FinalMEx * FinalMEx + FinalMEy * FinalMEy);

      double FinalJx = GammaX8 * B1PTemp8[1] - GammaX8 * Beta8 * B1PTemp8[0]
         + GammaX8 * B2PTemp8[1] - GammaX8 * Beta8 * B2PTemp8[0];
      double FinalJy = B1PTemp8[2] + B2PTemp8[2];
      double FinalJT = sqrt(FinalJx * FinalJx + FinalJy * FinalJy);

      // cout << "x " << FinalMEx << " " << FinalJx << endl;
      // cout << "y " << FinalMEy << " " << FinalJy << endl;
      // cout << "T " << FinalMET << " " << FinalJT << endl;

      MR8 = GammaZ8 * ((GammaX8 * (B1PTemp8[0] + B2PTemp8[0]) - GammaX8 * Beta8 * (B1PTemp8[1] + B2PTemp8[1]))
         - BetaZ8 * (B1P[3] + B2P[3]));
      double MT8 = sqrt(2 * (FinalMET * FinalJT - FinalMEx * FinalJx - FinalMEy * FinalJy));
      R8 = MT8 / MR8 / 2;

      // cout << Beta8 << " " << GammaX8 << " " << BetaZ8 << " " << GammaZ8 << endl;

      // assumption 9 - longitudinal boost + transverse boost!
      FourVector B1PTemp9 = B1PTemp7;
      FourVector B2PTemp9 = B2PTemp7;
      FourVector METemp9 = METemp7;

      double MinimumBetaZ = 1000;
      MinimumDifference9 = 99999999;
      double SearchCenter9 = 0;
      double SearchStep9 = 0.05;
      for(int i = 0; i < 5; i++)
      {
         for(double BetaZ = SearchCenter9 - SearchStep9 * 20; BetaZ < SearchCenter9 + SearchStep9 * 20;
            BetaZ = BetaZ + SearchStep9)
         {
            double Difference = GetDifference9(B1PTemp9, B2PTemp9, METemp9, BetaZ);

            if(fabs(Difference) < MinimumDifference9)
            {
               MinimumBetaZ = BetaZ;
               MinimumDifference9 = fabs(Difference);
            }
         }

         SearchCenter9 = MinimumBetaZ;
         SearchStep9 = SearchStep9 / 10;
      }

      // cout << "======" << endl;

      double GammaZ9 = BetaToGamma(MinimumBetaZ);
      double BetaX9 = (GammaZ9 * (B1PTemp9[0] - B2PTemp9[0]) - GammaZ9 * MinimumBetaZ * (B1PTemp9[3] - B2PTemp9[3]))
         / (B1PTemp9[1] - B2PTemp9[1]);
      double GammaX9 = BetaToGamma(BetaX9);

      double FinalJE = GammaX9 * (GammaZ9 * (B1PTemp9[0] + B2PTemp9[0])
         - GammaZ9 * MinimumBetaZ * (B1PTemp9[3] - B2PTemp9[3]))
         - GammaX9 * BetaX9 * (B1PTemp9[1] + B2PTemp9[0]);
      double FinalJx9 = GammaX9 * (B1PTemp9[1] + B2PTemp9[1]) - GammaX9 * BetaX9
         * (GammaZ9 * (B1PTemp9[0] + B2PTemp9[0]) - GammaZ9 * MinimumBetaZ * (B1PTemp9[3] - B2PTemp9[3]));
      double FinalJy9 = B1PTemp9[2] + B2PTemp9[2];
      double FinalJT9 = sqrt(FinalJx9 * FinalJx9 + FinalJy9 * FinalJy9);

      Beta9 = BetaX9;
      MR9 = FinalJE;
      double MT9 = 2 * FinalJT9;
      R9 = MT9 / MR9 / 2;

      // Assumption 10 - longitudinal boost + trasverse boost + longitudinal boost!
      FourVector B1PTemp10 = B1PTemp7;
      FourVector B2PTemp10 = B2PTemp7;
      FourVector METemp10 = METemp7;

      double InitialBetaZ = ExtraJets[3] / ExtraJets[0];

      B1PTemp10 = B1PTemp10.BoostZ(InitialBetaZ);
      B2PTemp10 = B2PTemp10.BoostZ(InitialBetaZ);
      METemp10 = METemp10.BoostZ(InitialBetaZ);

      // cout << ExtraJets.BoostZ(InitialBetaZ) << endl;

      double MinimumBetaX10 = 1000;
      MinimumDifference10 = 999999;
      double SearchCenter10 = 0;
      double SearchStep10 = 0.1;
      for(int i = 0; i < 5; i++)
      {
         for(double BetaX = SearchCenter10 - SearchStep10 * 10; BetaX < SearchCenter10 + SearchStep10 * 10;
            BetaX = BetaX + SearchStep10)
         {
            double Difference = GetDifference8(B1PTemp10, B2PTemp10, METemp10, BetaX);

            if(fabs(Difference) < MinimumDifference10)
            {
               MinimumBetaX10 = BetaX;
               MinimumDifference10 = fabs(Difference);
            }
         }

         SearchCenter10 = MinimumBetaX10;
         SearchStep10 = SearchStep10 / 10;
      }

      Beta10 = MinimumBetaX10;

      double GammaX10 = BetaToGamma(Beta10);
      double BetaZ10 = GammaX10 * ((B1PTemp10[0] - B2PTemp10[0]) - Beta10 * (B1PTemp10[1] - B2PTemp10[1]))
         / (B1P[3] - B2P[3]);
      double GammaZ10 = BetaToGamma(BetaZ10);
      double Beta10E10 = METemp10[1] + B1PTemp10[1] + B2PTemp10[1] - Beta10 * (B1PTemp10[0] + B2PTemp10[0]);

      double FinalMEx10 = GammaX10 * METemp10[1] - GammaX10 * Beta10E10;
      double FinalMEy10 = METemp10[2];
      double FinalMET10 = sqrt(FinalMEx10 * FinalMEx10 + FinalMEy10 * FinalMEy10);

      double FinalJx10 = GammaX10 * B1PTemp10[1] - GammaX10 * Beta10 * B1PTemp10[0]
         + GammaX10 * B2PTemp10[1] - GammaX10 * Beta10 * B2PTemp10[0];
      double FinalJy10 = B1PTemp10[2] + B2PTemp10[2];
      double FinalJT10 = sqrt(FinalJx10 * FinalJx10 + FinalJy10 * FinalJy10);

      MR10 = GammaZ10 * ((GammaX10 * (B1PTemp10[0] + B2PTemp10[0]) - GammaX10 * Beta10 * (B1PTemp10[1] + B2PTemp10[1]))
         - BetaZ10 * (B1P[3] + B2P[3]));
      double MT10 = sqrt(2 * (FinalMET10 * FinalJT10 - FinalMEx10 * FinalJx10 - FinalMEy10 * FinalJy10));
      R10 = MT10 / MR10 / 2;

      // cout << Beta10 << " " << GammaX10 << " " << BetaZ10 << " " << GammaZ10 << endl;

      // Assumption 11!  Scan through Pz and assume equal-mass
      double JJMass2 = (B1P + B2P).GetMass2();
      FourVector METemp11 = ME;

      METemp11[3] = FindMR11MinimumPz(B1P, B2P, METemp11, ExtraJets);
      METemp11[0] = sqrt(JJMass2 + METemp11.GetP2());

      MR11 = EstimateMass(B1P, B2P, METemp11, ExtraJets);
      double MRT11a = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'a');
      double MRT11b = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'b');
      double MRT11c = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'c');
      double MRT11d = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'd');
      double MRT11e = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'e');
      double MRT11f = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'f');
      double MRT11g = EstimateTransverseMass(B1P, B2P, METemp11, ExtraJets, 'g');
      R11a = MRT11a / MR11;
      R11b = MRT11b / MR11;
      R11c = MRT11c / MR11;
      R11d = MRT11d / MR11;
      R11e = MRT11e / MR11;
      R11f = MRT11f / MR11;
      R11g = MRT11g / MR11;

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();
}

double GetDifference8(FourVector &P1, FourVector &P2, FourVector &ME, double BetaX)
{
   double DeltaPx = P1[1] - P2[1];
   double Pxj = P1[1] + P2[1];
   double Px = ME[1];
   double DeltaPz = P1[3] - P2[3];
   double Pzj = P1[3] + P2[3];
   double DeltaE = P1[0] - P2[0];
   double Ej = P1[0] + P2[0];

   double GammaX = BetaToGamma(BetaX);
   double DeltaPzBetaZ = GammaX * DeltaE - GammaX * BetaX * DeltaPx;
   double BetaXE = Px + Pxj - BetaX * Ej;
   double BetaXDeltaPzPz = -BetaX * DeltaPz * Pzj
      + DeltaPzBetaZ * GammaX * (BetaXE + BetaX * Ej - BetaX * BetaX * (Px + Pxj));
   double Left = DeltaPz * DeltaPz * BetaX * GammaX * Ej
      - GammaX * BetaX * BetaX * DeltaPz * Pxj * DeltaPz
      - Pzj * BetaX * DeltaPzBetaZ * DeltaPz;
   double Right = GammaX * BetaXE * DeltaPz * DeltaPz
      - GammaX * BetaX * BetaX * Px * DeltaPz * DeltaPz
      - DeltaPzBetaZ * BetaXDeltaPzPz;

   return Left - Right;
}

double GetDifference9(FourVector &P1, FourVector &P2, FourVector &ME, double BetaZ)
{
   double DeltaPx = P1[1] - P2[1];
   double Pxj = P1[1] + P2[1];
   double Px = ME[1];
   double DeltaPz = P1[3] - P2[3];
   double Pzj = P1[3] + P2[3];
   double DeltaE = P1[0] - P2[0];
   double Ej = P1[0] + P2[0];

   double GammaZ = BetaToGamma(BetaZ);
   double InvGammaZ = sqrt(1 - BetaZ * BetaZ);
   double DeltaPxBetaX = GammaZ * DeltaE - GammaZ * BetaZ * DeltaPz;
   double DeltaPxInvGammaE = GammaZ * Ej * DeltaPx * (1 + BetaZ * BetaZ)
      - 2 * GammaZ * BetaZ * Pzj * DeltaPx
      + DeltaPxBetaX * (Px - Pxj);
   double DeltaPxInvGammaPz = DeltaPx * InvGammaZ * Ej * BetaZ
      - DeltaPx * InvGammaZ * Pzj + BetaZ * DeltaPxInvGammaE;

   double Left = DeltaPx * DeltaPx * InvGammaZ * (Pxj + Px);
   double Right = DeltaPxBetaX * (GammaZ * (DeltaPxInvGammaE + DeltaPx * InvGammaZ * Ej)
      - GammaZ * BetaZ * (DeltaPxInvGammaPz + DeltaPx * InvGammaZ * Pzj));

   /*
   cout << "BetaZ = " << BetaZ << endl;
   cout << "BetaX = " << DeltaPxBetaX / DeltaPx << endl;
   cout << "E = " << DeltaPxInvGammaE / DeltaPx / InvGammaZ << endl;
   cout << "Pz = " << DeltaPxInvGammaPz / DeltaPx / InvGammaZ << endl;
   cout << "Left = " << Left << endl;
   cout << "Right = " << Right << endl;
   */

   return fabs(Left - Right);
}

double EstimateMass(FourVector J1, FourVector J2, FourVector ME, FourVector ISR)
{
   FourVector TempTotal = ME + J1 + J2 + ISR;
   double TempBetaZ = TempTotal[3] / TempTotal[0];

   FourVector TempJ1 = J1.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempJ2 = J2.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempME = ME.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempISR = ISR.Boost(FourVector(1, 0, 0, 1), TempBetaZ);

   TempTotal = TempJ1 + TempJ2 + TempME;
   double TempBeta = TempTotal.GetP() / TempTotal[0];

   TempJ1 = TempJ1.Boost(TempTotal, TempBeta);
   TempJ2 = TempJ2.Boost(TempTotal, TempBeta);
   TempME = TempME.Boost(TempTotal, TempBeta);

   double EMET = TempME[0];
   double SumE = TempJ1[0] + TempJ2[0];
   double DeltaE = TempJ1[0] - TempJ2[0];
   double ES = (TempJ1 + TempJ2).GetP();
   double ED = (TempJ1 - TempJ2).GetP();
   double A = SumE * DeltaE / ES;
   double B = sqrt(ED * ED - A * A);

   double m0 = (SumE - EMET) / (2 * DeltaE) - SumE * DeltaE / ES / ES;
   double m1 = DeltaE * (SumE + EMET) / 2;

   double EQA = m0 * m0 + B * B / ES / ES;
   double EQB = 2 * m0 * m1 - B * B;
   double EQC = m1 * m1;

   double X2Max = (-EQB + sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);
   double X2Min = (-EQB - sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);

   if(X2Min > ES * ES)
      return -1;
   if(X2Max < 0)
      return -1;

   if(X2Max > ES * ES)
      X2Max = ES * ES;

   double X = sqrt(X2Max);
   double Y = ((X * X + DeltaE * DeltaE) * SumE - (X * X - DeltaE * DeltaE) * EMET) / (2 * X * DeltaE);

   double M2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

   if(M2 < 0)
      return -1;

   return sqrt(M2) * 2;
}

double EstimateTransverseMass(FourVector J1, FourVector J2, FourVector ME, FourVector ISR, char Variant)
{
   FourVector TempTotal = ME + J1 + J2 + ISR;
   double TempBetaZ = TempTotal[3] / TempTotal[0];

   FourVector TempJ1 = J1.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempJ2 = J2.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempME = ME.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
   FourVector TempISR = ISR.Boost(FourVector(1, 0, 0, 1), TempBetaZ);

   TempTotal = TempJ1 + TempJ2 + TempME;
   double TempBeta = TempTotal.GetP() / TempTotal[0];

   TempJ1 = TempJ1.Boost(TempTotal, TempBeta);
   TempJ2 = TempJ2.Boost(TempTotal, TempBeta);
   TempME = TempME.Boost(TempTotal, TempBeta);

   double MT = 0;

   double EMET = TempME[0];
   double SumE = TempJ1[0] + TempJ2[0];
   double DeltaE = TempJ1[0] - TempJ2[0];
   double ES = (TempJ1 + TempJ2).GetP();
   double ED = (TempJ1 - TempJ2).GetP();
   double A = SumE * DeltaE / ES;
   double B = sqrt(ED * ED - A * A);

   double P1P1 = TempJ1.SpatialDot(TempJ1);
   double P1P2 = TempJ1.SpatialDot(TempJ2);

   double m0 = (SumE - EMET) / (2 * DeltaE) - SumE * DeltaE / ES / ES;
   double m1 = DeltaE * (SumE + EMET) / 2;

   double EQA = m0 * m0 + B * B / ES / ES;
   double EQB = 2 * m0 * m1 - B * B;
   double EQC = m1 * m1;

   double X2Max = (-EQB + sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);
   double X2Min = (-EQB - sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);

   double X = sqrt(X2Max);
   double Y = ((X * X + DeltaE * DeltaE) * SumE - (X * X - DeltaE * DeltaE) * EMET) / (2 * X * DeltaE);
   double M2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

   double A0 = X / ES;
   double B0 = (Y - A * A0) / B;
   double C0 = sqrt(1 - A0 * A0 - B0 * B0);
   if(A0 * A0 + B0 * B0 >= 1)
      C0 = 0;

   FourVector DirectionA = (TempJ1 + TempJ2).SpatialNormalize();
   FourVector DirectionB = ((TempJ1 - TempJ2) - DirectionA * A).SpatialNormalize();
   FourVector DirectionC = DirectionA.SpatialCross(DirectionB);   // ambiguity in direction...

   double BetaCMSize = DeltaE / X;
   FourVector BetaCM = (DirectionA * A0 + DirectionB * B0 + DirectionC * C0).SpatialNormalize() * BetaCMSize;
      
   FourVector J1Boosted = TempJ1.Boost(BetaCM, -BetaCMSize);
   FourVector J2Boosted = TempJ2.Boost(BetaCM, BetaCMSize);

   if(fabs(J1Boosted.GetP() - J2Boosted.GetP()) > 0.1)   // wrong boost direction!
   {
      J1Boosted = TempJ1.Boost(BetaCM, BetaCMSize);
      J2Boosted = TempJ2.Boost(BetaCM, -BetaCMSize);
   }

   if(Variant == 'a')
      MT = GetMRT(TempJ1, TempJ2, TempME);
   if(Variant == 'b')
   {
      FourVector TransverseVector = (TempJ1 - (TempJ1 + TempJ2) * (P1P1 + P1P2) / (ES * ES)) * 2;
      MT = sqrt(M2 * 4 - TransverseVector.GetP2());
   }
   if(Variant == 'c')
   {
      double MT1 = J1Boosted.GetPT();
      double MT2 = J2Boosted.GetPT();
      MT = sqrt(M2) * 2 - (MT1 + MT2);
   }
   if(Variant == 'd')
   {
      double MT1 = J1Boosted.GetPT();
      double MT2 = J2Boosted.GetPT();
      MT = sqrt(M2) * 2 - sqrt(MT1 * MT1 + MT2 * MT2) * sqrt(2);
   }
   if(Variant == 'e')
      MT = (J1Boosted + J2Boosted).GetPT();
   if(Variant == 'f')
   {
      double MT1 = J1Boosted.GetPT();
      double MT2 = J2Boosted.GetPT();
      MT = sqrt(2 * M2 - MT1 * MT1 - MT2 * MT2);
   }
   if(Variant == 'g')
      MT = GetMRT(TempJ1, TempJ2, TempME) / BetaToGamma(BetaCMSize);

   return MT;
}

double FindMR11MinimumPz(FourVector J1, FourVector J2, FourVector ME, FourVector ISR)
{
   double JJMass2 = (J1 + J2).GetMass2();

   int InitialStep = 400;
   double InitialStepSize = 5;
   double InitialCenter = 0;
   int SearchStep = 10;
   double SearchStepSize = 1;

   vector<double> Masses;
   for(int i = 0; i <= InitialStep; i++)
   {
      ME[3] = InitialCenter - InitialStep / 2 * InitialStepSize + i * InitialStepSize;
      ME[0] = sqrt(JJMass2 + ME.GetP2());

      double Mass = EstimateMass(J1, J2, ME, ISR);
      Masses.push_back(Mass);
   }

   vector<double> LocalMinima;
   for(int i = 1; i < InitialStep; i++)
      if(Masses[i] <= Masses[i-1] && Masses[i] <= Masses[i+1])
         LocalMinima.push_back(InitialCenter - InitialStep / 2 * InitialStepSize + i * InitialStepSize);
   if(Masses[0] <= Masses[1])
      LocalMinima.push_back(InitialCenter - InitialStep / 2 * InitialStepSize);
   if(Masses[InitialStep] <= Masses[InitialStep-1])
      LocalMinima.push_back(InitialCenter + InitialStep / 2 * InitialStepSize);

   for(int i = 0; i <= 5; i++)
   {
      vector<double> NewMinima;
      for(int j = 0; j < (int)LocalMinima.size(); j++)
      {
         double SearchCenter = LocalMinima[j];

         Masses.clear();
         for(int k = 0; k <= SearchStep; k++)
         {
            ME[3] = SearchCenter - SearchStep / 2 * SearchStepSize + k * SearchStepSize;
            ME[0] = sqrt(JJMass2 + ME.GetP2());
            
            double Mass = EstimateMass(J1, J2, ME, ISR);
            Masses.push_back(Mass);
         }

         for(int k = 1; k < SearchStep; k++)
            if(Masses[k] <= Masses[k-1] && Masses[k] <= Masses[k+1])
               NewMinima.push_back(SearchCenter - SearchStep / 2 * SearchStepSize + k * SearchStepSize);
         if(Masses[0] <= Masses[1])
            NewMinima.push_back(SearchCenter - SearchStep / 2 * SearchStepSize);
         if(Masses[InitialStep] <= Masses[InitialStep-1])
            NewMinima.push_back(SearchCenter + SearchStep / 2 * SearchStepSize);
      }

      SearchStepSize = SearchStepSize / 5;
      LocalMinima = NewMinima;
   }

   double BestPz = -1;
   double BestMass = -1;
   for(int i = 0; i < (int)LocalMinima.size(); i++)
   {
      ME[3] = LocalMinima[i];
      ME[0] = sqrt(JJMass2 + ME.GetP2());

      double Mass = EstimateMass(J1, J2, ME, ISR);

      if(Mass < BestMass || BestMass < 0)
      {
         BestPz = LocalMinima[i];
         BestMass = Mass;
      }
   }

   return BestPz;
}

int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID)
{
   int MotherIndex = -1;

   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].PDGID == ChildPDGID)
      {
         for(int j = 0; j < (int)Tree[i].Mothers.size(); j++)
         {
            if(Tree[Tree[i].Mothers[j]].PDGID == ParentPDGID)
               return i;
         }
      }
   }

   return -1;
}

int TraceBHadron(GenParticleTree &Tree, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= Tree.ParticleCount())
      return -1;
   if(HasB(Tree[StartIndex].PDGID) == false && Tree[StartIndex].PDGID != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;;
      for(int i = 0; i < (int)Tree[CurrentIndex].Daughters.size(); i++)
      {
         if(Tree[Tree[CurrentIndex].Daughters[i]].PDGID != 92
            && HasB(Tree[Tree[CurrentIndex].Daughters[i]].PDGID) == false)
            continue;
         ChildrenIndex.push_back(Tree[CurrentIndex].Daughters[i]);
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = FourVector(Tree[ChildrenIndex[0]].P).GetPT();
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = FourVector(Tree[ChildrenIndex[i]].P).GetPT();
            if(PT > BestCandidatePT)
            {
               BestCandidate = i;
               BestCandidatePT = PT;
            }
         }

         CurrentIndex = ChildrenIndex[BestCandidate];
      }
   }

   return -1;

}

bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)
   //    s is spin, let's happily ignore

   if(PDGID < 0)
      PDGID = -PDGID;

   if(PDGID == 5)
      return true;
   if((PDGID % 100) / 10 == 5)
      return true;
   if((PDGID % 1000) / 100 == 5)
      return true;
   if((PDGID % 10000) / 1000 == 5)
      return true;

   return false;
}

int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < (int)Jets.size(); i++)
   {
      double EtaJet = Jets[i].eta();
      double PhiJet = Jets[i].phi();

      double DEta = Eta - EtaJet;
      double DPhi = Phi - PhiJet;
      if(DPhi > PI)   DPhi = DPhi - 2 * PI;
      if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
      double DR = sqrt(DPhi * DPhi + DEta * DEta);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}

double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency)
{
   if(JetPT.size() == 0)
      return 0;
   if(PT < JetPT[0])
      return 0;
   if(PT > JetPT[JetPT.size()-1])
      return JetEfficiency[JetPT.size()-1];

   for(int i = 0; i < JetPT.size() - 1; i++)
   {
      if(JetPT[i] < PT && JetPT[i+1] >= PT)
         return JetEfficiency[i] +
            (PT - JetPT[i]) / (JetPT[i+1] - JetPT[i]) * (JetEfficiency[i+1] - JetEfficiency[i]);
   }

   return 0;
}





