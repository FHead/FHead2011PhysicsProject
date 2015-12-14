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

#include "Code/DrawRandom2.h"
#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double DecayConstant);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy32_W.ps");
   PsFile.AddTextPage("Toys to understand MRStar better - part 32");

   vector<string> Explanations;
   Explanations.push_back("");
   Explanations.push_back("");
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   TFile F("output.root", "RECREATE");

   DoToyAndAppendPlots(PsFile, 81, 0.5);

   F.Close();
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double DecayConstant)
{
   RandomBase Random;

   TH2D HMRVsR2("HMRVsR2", "R*R vs. MR;MR;R^{2}", 100, 0, 500, 100, 0, 1.2);
   TH1D HMR_R2020("HMR_R2020", "MR, R^{2} > 0.2;MR", 100, 0, 500);
   TH1D HMR_R2030("HMR_R2030", "MR, R^{2} > 0.3;MR", 100, 0, 500);
   TH1D HMR_R2040("HMR_R2040", "MR, R^{2} > 0.4;MR", 100, 0, 500);
   TH1D HMR_R2050("HMR_R2050", "MR, R^{2} > 0.5;MR", 100, 0, 500);

   for(int iEntry = 0; iEntry < 10000; iEntry++)
   {
      // double Energy = HeavyMass * Random.DrawExponential(-1 / DecayConstant, 1);
      double Energy = HeavyMass / 10;

      // Direction of W
      double Theta = Random.DrawSine(0, PI);
      double Phi = Random.DrawRandom(-PI, PI);
      double Momentum = (Energy * Energy - HeavyMass * HeavyMass) / (2 * Energy);

      FourVector W, Jet;
      W.SetSizeThetaPhiMass(Momentum, Theta, Phi, HeavyMass);
      Jet.SetSizeThetaPhiMass(Momentum, PI - Theta, Phi + PI, 0);

      // Direction of decay product of W - both massless :3
      double ThetaChild = Random.DrawSine(0, PI);
      double PhiChild = Random.DrawRandom(-PI, PI);

      FourVector Visible;
      FourVector Invisible;
      Visible.SetSizeThetaPhiMass(HeavyMass / 2, ThetaChild, PhiChild, 0);
      Invisible.SetSizeThetaPhiMass(HeavyMass / 2, PI - ThetaChild, PI + PhiChild, 0);

      double BoostBeta = W.GetP() / W[0];

      // Boost back to lab frame
      FourVector FinalVisible = Visible.Boost(W, -BoostBeta);
      FourVector FinalInvisible = Invisible.Boost(W, -BoostBeta);

      // calculate MR/R
      double MR = Get2011MR(FinalVisible, Jet);
      double R = Get2011R(FinalVisible, Jet, FinalInvisible);

      HMRVsR2.Fill(MR, R * R);
      if(R * R > 0.2)   HMR_R2020.Fill(MR);
      if(R * R > 0.3)   HMR_R2030.Fill(MR);
      if(R * R > 0.4)   HMR_R2040.Fill(MR);
      if(R * R > 0.5)   HMR_R2050.Fill(MR);
   }

   PsFile.AddPlot(HMRVsR2, "colz", false, true);

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





