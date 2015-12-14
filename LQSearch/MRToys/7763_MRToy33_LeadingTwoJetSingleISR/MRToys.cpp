#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TF1.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double ISREnergy, const string Tag);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy33_SingleISR_ExponentialEnergy.ps");
   PsFile.AddTextPage("Toys to understand MRStar better - part 33");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum zero, decay into two heavy object");
   Explanations.push_back("of certain mass (300 GeV), each then further decays into two light objects");
   Explanations.push_back("one of them visible (4.2 GeV), one invisible (0 GeV)");
   Explanations.push_back("This system finally gets a fixed-size ISR boost");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("Check MR(2011) and R(2011) distribution - with leading jets only");
   Explanations.push_back("");
   Explanations.push_back("Jet PT > 40, |eta| < 3 => but these are minor effects");
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   TFile F("output.root", "RECREATE");

   double DecayConstant = 1;
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 0, "A");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 30, "B");
   // DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 60, "C");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 90, "D");
   // DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 120, "E");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 150, "F");
   // DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 180, "G");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 210, "H");
   // DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 240, "I");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 270, "J");
   DoToyAndAppendPlots(PsFile, 300, 4.2, 0, DecayConstant, 600, "K");

   F.Close();
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double VisibleMass,
   const double InvisibleMass, const double DecayConstant, const double ISREnergy, const string Tag)
{
   TH2D HMRVsR2("HMRVsR2", "MR (2011) vs R^{2} (2011);MR (2011);R^{2} (2011)", 100, 0, HeavyMass * 5, 100, 0, 1.5);
   TH2D HMRVsR2Zoomed("HMRVsR2Zoomed",
      "MR (2011) vs R^{2} (2011);MR (2011);R^{2} (2011)", 100, 0, HeavyMass * 5, 100, 0, 0.5);
   TH1D HMR_R2020("HMR_R2020", "MR (2011), R^{2} (2011) > 0.20;MR (2011)", 100, 0, HeavyMass * 5);
   TH1D HMR_R2030("HMR_R2030", "MR (2011), R^{2} (2011) > 0.30;MR (2011)", 100, 0, HeavyMass * 5);
   TH1D HMR_R2040("HMR_R2040", "MR (2011), R^{2} (2011) > 0.40;MR (2011)", 100, 0, HeavyMass * 5);
   TH1D HMR_R2050("HMR_R2050", "MR (2011), R^{2} (2011) > 0.50;MR (2011)", 100, 0, HeavyMass * 5);

   TTree Tree(Form("Tree_%s", Tag.c_str()), "Tree!");

   double TreeMR;
   double TreeR;
   double TreeISRPT;

   Tree.Branch("MR", &TreeMR, "MR/D");
   Tree.Branch("R", &TreeR, "R/D");
   Tree.Branch("ISRPT", &TreeISRPT, "ISRPT/D");

   for(int iEntry = 0; iEntry < 10000000; iEntry++)
   {
      double Energy = HeavyMass * 2 * DrawExponential(-1 / DecayConstant, 1);

      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      FourVector HeavyParticle1Direction(1, sin(Theta) * cos(Phi), sin(Theta) * sin(Phi), cos(Theta));
      FourVector HeavyParticle2Direction(1, -sin(Theta) * cos(Phi), -sin(Theta) * sin(Phi), -cos(Theta));

      // CM frame child momentum calculation
      double M2 = HeavyMass * HeavyMass;
      double m12 = VisibleMass * VisibleMass;
      double m22 = InvisibleMass * InvisibleMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      FourVector VisibleChild1Heavy1CM(1, sin(Theta1) * cos(Phi1), sin(Theta1) * sin(Phi1), cos(Theta1));
      FourVector InvisibleChild1Heavy1CM(1, -sin(Theta1) * cos(Phi1), -sin(Theta1) * sin(Phi1), -cos(Theta1));
      
      for(int i = 1; i <= 3; i++)
      {
         VisibleChild1Heavy1CM[i] = VisibleChild1Heavy1CM[i] * Momentum;
         InvisibleChild1Heavy1CM[i] = InvisibleChild1Heavy1CM[i] * Momentum;
      }
      VisibleChild1Heavy1CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild1Heavy1CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      FourVector VisibleChild2Heavy2CM(1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2));
      FourVector InvisibleChild2Heavy2CM(1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2));
      
      for(int i = 1; i <= 3; i++)
      {
         VisibleChild2Heavy2CM[i] = VisibleChild2Heavy2CM[i] * Momentum;
         InvisibleChild2Heavy2CM[i] = InvisibleChild2Heavy2CM[i] * Momentum;
      }
      VisibleChild2Heavy2CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild2Heavy2CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);

      // boost back to almost-lab frame
      FourVector VisibleChild1 = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector InvisibleChild1 = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector VisibleChild2 = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector InvisibleChild2 = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      FourVector InvisibleTotal = InvisibleChild1 + InvisibleChild2;

      // yet another boost - ISR
      double ThetaISR = DrawSine(0, PI);
      double PhiISR = DrawRandom(-PI, PI);
      FourVector ISRJet;
      ISRJet.SetSizeThetaPhi(ISREnergy, ThetaISR, PhiISR);

      double ISRBoost = ISRJet.GetP() / (VisibleChild1 + VisibleChild2 + InvisibleTotal)[0];
      FourVector FinalVisible1 = VisibleChild1.Boost(ISRJet, ISRBoost);
      FourVector FinalVisible2 = VisibleChild2.Boost(ISRJet, ISRBoost);
      FourVector FinalInvisible = InvisibleTotal.Boost(ISRJet, ISRBoost);

      if(VisibleChild1.GetAbsEta() > 3 || VisibleChild2.GetAbsEta() > 3)
         continue;
      if(VisibleChild1.GetPT() < 40 || VisibleChild2.GetPT() < 40)
         continue;

      vector<FourVector> GoodJets;
      GoodJets.push_back(FinalVisible1);
      GoodJets.push_back(FinalVisible2);
      // if(ISRJet.GetAbsEta() < 3 && ISRJet.GetPT() > 40)
      //    GoodJets.push_back(ISRJet);

      vector<FourVector> Groups = SplitIntoGroups(GoodJets);

      double MR = Get2011MR(Groups[0], Groups[1]);
      double R = Get2011R(Groups[0], Groups[1], InvisibleTotal);

      HMRVsR2.Fill(MR, R * R);
      HMRVsR2Zoomed.Fill(MR, R * R);

      if(R * R > 0.20)
         HMR_R2020.Fill(MR);
      if(R * R > 0.30)
         HMR_R2030.Fill(MR);
      if(R * R > 0.40)
         HMR_R2040.Fill(MR);
      if(R * R > 0.50)
         HMR_R2050.Fill(MR);

      TreeMR = MR;
      TreeR = R;
      TreeISRPT = ISRJet.GetPT();

      Tree.Fill();
   }

   Tree.Write();

   PsFile.AddPlot(HMRVsR2, "colz", false, false);
   PsFile.AddPlot(HMRVsR2Zoomed, "colz", false, false);
   PsFile.AddPlot(HMR_R2020, "", true);
   PsFile.AddPlot(HMR_R2030, "", true);
   PsFile.AddPlot(HMR_R2040, "", true);
   PsFile.AddPlot(HMR_R2050, "", true);

   TCanvas C;
   HMR_R2020.Draw();
   HMR_R2030.Draw("same");
   HMR_R2040.Draw("same");
   HMR_R2050.Draw("same");
   C.SetLogy();
   PsFile.AddCanvas(C);

   return 0;
}





