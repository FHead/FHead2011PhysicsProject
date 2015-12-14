#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"

#include "DrawRandom.h"
#include "TauHelperFunctions.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double TopMass, const double Energy,
   const double BottomMass, const double WMass, const double LeptonMass, const double InvisibleMass);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   PsFileHelper PsFile("MRToy6_TTbarLikeChangeMass.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 6");

   vector<string> TOCItems;
   TOCItems.push_back("Explanations");
   TOCItems.push_back("Realistic setting: ttbar -> bWbW, W -> mu nu");
   TOCItems.push_back("Realistic setting: ttbar -> bWbW, W -> e nu");
   TOCItems.push_back("Changing mass of b quark and W (set to be the same)");
   TOCItems.push_back("Changing mass of b quark only");
   TOCItems.push_back("Changing mass of W boson only");
   TOCItems.push_back("Changing mass of lepton and neutrino together");
   TOCItems.push_back("Changing mass of lepton only");
   TOCItems.push_back("Changing mass of neutrino only");

   vector<string> Destinations;
   Destinations.push_back("Explanations");
   Destinations.push_back("RealisticMuNu");
   Destinations.push_back("RealisticENu");
   Destinations.push_back("ChangeWBMass");
   Destinations.push_back("ChangeBMass");
   Destinations.push_back("ChangeWMass");
   Destinations.push_back("ChangeMuNuMass");
   Destinations.push_back("ChangeMuMass");
   Destinations.push_back("ChangeNuMass");

   PsFile.AddTableOfContentPage(TOCItems, Destinations);
   PsFile.InsertNamedDestination("TableOfContentPage");
   PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum zero, decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two lighter objects");
   Explanations.push_back("one is stable and visible, another one is unstable");
   Explanations.push_back("The unstable one decays into a stable object and a invisible object");
   Explanations.push_back("(ex. ttbar -> bWbW -> b l nu b l nu)");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("Assume perfect association of the objects");
   Explanations.push_back("Check MR distribution changing the masses");
   Explanations.push_back("Top mass is always 172.5, and Gamma CM is always 1.1");
   PsFile.AddTextPage(Explanations);
   PsFile.InsertNamedDestination("Explanations");

   PsFile.AddTextPage("Realistic setting: ttbar -> bWbW, both W -> nu mu");
   PsFile.InsertNamedDestination("RealisticMuNu");
   double TopMass = 172.5;
   double GammaCM = 1.1;
   double BottomMass = 4.2;
   double WMass = 80.5;
   double MuonMass = 0.1;
   double ElectronMass = 0.000511;
   double NuMass = 0;
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, NuMass);
   
   PsFile.AddTextPage("Realistic setting: ttbar -> bWbW, both W -> e mu");
   PsFile.InsertNamedDestination("RealisticENu");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);
   
   PsFile.AddTextPage("Direct children massive and equal, indirect massless");
   PsFile.InsertNamedDestination("ChangeWBMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 0.0001, 0.0001, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 1, 1, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 5, 5, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 10, 10, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 20, 20, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 33, 33, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 50, 50, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 75, 75, 0, 0);

   PsFile.AddTextPage("Changing B quark mass, W -> mu nu");
   PsFile.InsertNamedDestination("ChangeBMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 0, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 0.1, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 1, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 5, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 10, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 20, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, 50, WMass, MuonMass, NuMass);
   
   PsFile.AddTextPage("Changing W mass, W -> mu nu");
   PsFile.InsertNamedDestination("ChangeWMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 1, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 2, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 5, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 10, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 20, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 50, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 100, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, 125, MuonMass, NuMass);

   PsFile.AddTextPage("Changing lepton and nu mass");
   PsFile.InsertNamedDestination("ChangeMuNuMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 0, 0);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 0.1, 0.1);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 1, 1);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 2, 2);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 4, 4);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 10, 10);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 20, 20);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 40, 40);
   
   PsFile.AddTextPage("Changing lepton mass");
   PsFile.InsertNamedDestination("ChangeMuMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 0, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 0.1, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 1, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 2, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 4, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 10, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 20, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 40, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 60, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, 75, NuMass);
   
   PsFile.AddTextPage("Changing neutrino mass");
   PsFile.InsertNamedDestination("ChangeNuMass");
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, NuMass);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 0.1);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 0.2);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 0.4);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 1);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 2);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 4);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 10);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 20);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 40);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 60);
   DoToyAndAppendPlots(PsFile, TopMass, TopMass * 2 * GammaCM, BottomMass, WMass, MuonMass, 75);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double TopMass, const double Energy,
   const double BottomMass, const double WMass, const double LeptonMass, const double InvisibleMass)
{
   TH1D HMR("HMR", Form("MR distribution, TopMass %.2f, Energy %.2f, BottomMass %.2f, WMass %.2f",
      TopMass, Energy, BottomMass, WMass), 100, 0, TopMass * 4);
   TH1D HMRT("HMRT", Form("MRT distribution, LeptonMass %.2f, InvisibleMass %.2f",
      LeptonMass, InvisibleMass), 100, 0, TopMass * 4);
   TH1D HR("HR", "R distribution", 100, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R;MR;R", 100, 0, TopMass * 4, 100, 0, 1.5);
   
   TH1D HBMR("HBMR", Form("MR distribution from b only, TopMass %.2f, Energy %.2f, BottomMass %.2f, WMass %.2f",
      TopMass, Energy, BottomMass, WMass), 100, 0, TopMass * 4);
   TH1D HBMRT("HBMRT", Form("b MRT distribution, LeptonMass %.2f, InvisibleMass %.2f",
      LeptonMass, InvisibleMass), 100, 0, TopMass * 4);
   TH1D HBR("HBR", "b R distribution", 100, 0, 1.5);
   TH2D HBMRVsR("HBMRVsR", "b MR vs R;MR;R", 100, 0, TopMass * 4, 100, 0, 1.5);

   for(int iEntry = 0; iEntry < 1000000; iEntry++)
   {
      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / TopMass;
      double Beta = GammaToBeta(Gamma);

      double HeavyParticle1Direction[4] = {1, sin(Theta) * cos(Phi), sin(Theta) * sin(Phi), cos(Theta)};
      double HeavyParticle2Direction[4] = {1, -sin(Theta) * cos(Phi), -sin(Theta) * sin(Phi), -cos(Theta)};

      // CM frame child momentum calculation
      double M2 = TopMass * TopMass;
      double m12 = BottomMass * BottomMass;
      double m22 = WMass * WMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      double Bottom1Heavy1CM[4] = {1, sin(Theta1) * cos(Phi1), sin(Theta1) * sin(Phi1), cos(Theta1)};
      double W1Heavy1CM[4] = {1, -sin(Theta1) * cos(Phi1), -sin(Theta1) * sin(Phi1), -cos(Theta1)};

      for(int i = 1; i <= 3; i++)
      {
         Bottom1Heavy1CM[i] = Bottom1Heavy1CM[i] * Momentum;
         W1Heavy1CM[i] = W1Heavy1CM[i] * Momentum;
      }
      Bottom1Heavy1CM[0] = sqrt(BottomMass * BottomMass + Momentum * Momentum);
      W1Heavy1CM[0] = sqrt(WMass * WMass + Momentum * Momentum);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      double Bottom2Heavy2CM[4] = {1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2)};
      double W2Heavy2CM[4] = {1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2)};

      for(int i = 1; i <= 3; i++)
      {
         Bottom2Heavy2CM[i] = Bottom2Heavy2CM[i] * Momentum;
         W2Heavy2CM[i] = W2Heavy2CM[i] * Momentum;
      }
      Bottom2Heavy2CM[0] = sqrt(BottomMass * BottomMass + Momentum * Momentum);
      W2Heavy2CM[0] = sqrt(WMass * WMass + Momentum * Momentum);

      // W CM frame child momentum calculation
      double MW2 = WMass * WMass;
      double mL2 = LeptonMass * LeptonMass;
      double mN2 = InvisibleMass * InvisibleMass;
      double WChildMomentum = sqrt(((MW2 - mL2 - mN2) * (MW2 - mL2 - mN2) - 4 * mL2 * mN2) / (4 * MW2));

      // in CM of first W
      double ThetaW1 = DrawSine(0, PI);
      double PhiW1 = DrawRandom(-PI, PI);
      double Lepton1W1CM[4] = {1, sin(ThetaW1) * cos(PhiW1), sin(ThetaW1) * sin(PhiW1), cos(ThetaW1)};
      double Nu1W1CM[4] = {1, -sin(ThetaW1) * cos(PhiW1), -sin(ThetaW1) * sin(PhiW1), -cos(ThetaW1)};

      for(int i = 1; i <= 3; i++)
      {
         Lepton1W1CM[i] = Lepton1W1CM[i] * WChildMomentum;
         Nu1W1CM[i] = Nu1W1CM[i] * WChildMomentum;
      }
      Lepton1W1CM[0] = sqrt(LeptonMass * LeptonMass + WChildMomentum * WChildMomentum);
      Nu1W1CM[0] = sqrt(InvisibleMass * InvisibleMass + WChildMomentum * WChildMomentum);

      // in CM of second W
      double ThetaW2 = DrawSine(0, PI);
      double PhiW2 = DrawRandom(-PI, PI);
      double Lepton2W2CM[4] = {1, sin(ThetaW2) * cos(PhiW2), sin(ThetaW2) * sin(PhiW2), cos(ThetaW2)};
      double Nu2W2CM[4] = {1, -sin(ThetaW2) * cos(PhiW2), -sin(ThetaW2) * sin(PhiW2), -cos(ThetaW2)};

      for(int i = 1; i <= 3; i++)
      {
         Lepton2W2CM[i] = Lepton2W2CM[i] * WChildMomentum;
         Nu2W2CM[i] = Nu2W2CM[i] * WChildMomentum;
      }
      Lepton2W2CM[0] = sqrt(LeptonMass * LeptonMass + WChildMomentum * WChildMomentum);
      Nu2W2CM[0] = sqrt(InvisibleMass * InvisibleMass + WChildMomentum * WChildMomentum);

      // boost to heavy object frame
      double Lepton1Heavy1CM[4], Nu1Heavy1CM[4];
      double Lepton2Heavy2CM[4], Nu2Heavy2CM[4];

      Boost(Lepton1W1CM, Lepton1Heavy1CM, W1Heavy1CM, GammaToBeta(GetGamma(W1Heavy1CM)));
      Boost(Nu1W1CM, Nu1Heavy1CM, W1Heavy1CM, GammaToBeta(GetGamma(W1Heavy1CM)));
      Boost(Lepton2W2CM, Lepton2Heavy2CM, W2Heavy2CM, GammaToBeta(GetGamma(W2Heavy2CM)));
      Boost(Nu2W2CM, Nu2Heavy2CM, W2Heavy2CM, GammaToBeta(GetGamma(W2Heavy2CM)));

      // boost back to lab frame
      double Lepton1P[4], Nu1P[4], Bottom1P[4];
      double Lepton2P[4], Nu2P[4], Bottom2P[4];

      Boost(Lepton1Heavy1CM, Lepton1P, HeavyParticle1Direction, Beta);
      Boost(Nu1Heavy1CM, Nu1P, HeavyParticle1Direction, Beta);
      Boost(Bottom1Heavy1CM, Bottom1P, HeavyParticle1Direction, Beta);
      Boost(Lepton2Heavy2CM, Lepton2P, HeavyParticle2Direction, Beta);
      Boost(Nu2Heavy2CM, Nu2P, HeavyParticle2Direction, Beta);
      Boost(Bottom2Heavy2CM, Bottom2P, HeavyParticle2Direction, Beta);

      double InvisibleTotal[4];
      InvisibleTotal[0] = Nu1P[0] + Nu2P[0];
      InvisibleTotal[1] = Nu1P[1] + Nu2P[1];
      InvisibleTotal[2] = Nu1P[2] + Nu2P[2];
      InvisibleTotal[3] = Nu1P[3] + Nu2P[3];

      double VisibleHalf1[4];
      VisibleHalf1[0] = Lepton1P[0] + Bottom1P[0];
      VisibleHalf1[1] = Lepton1P[1] + Bottom1P[1];
      VisibleHalf1[2] = Lepton1P[2] + Bottom1P[2];
      VisibleHalf1[3] = Lepton1P[3] + Bottom1P[3];

      double VisibleHalf2[4];
      VisibleHalf2[0] = Lepton2P[0] + Bottom2P[0];
      VisibleHalf2[1] = Lepton2P[1] + Bottom2P[1];
      VisibleHalf2[2] = Lepton2P[2] + Bottom2P[2];
      VisibleHalf2[3] = Lepton2P[3] + Bottom2P[3];

      double MR = GetMR(VisibleHalf1, VisibleHalf2);
      double MRT = GetMRT(VisibleHalf1, VisibleHalf2, InvisibleTotal);
      double R = GetR(VisibleHalf1, VisibleHalf2, InvisibleTotal);

      HMR.Fill(MR);
      HMRT.Fill(MRT);
      HR.Fill(R);
      HMRVsR.Fill(MR, R);

      double bMR = GetMR(Bottom1P, Bottom2P);
      double bMRT = GetMRT(Bottom1P, Bottom2P, InvisibleTotal);
      double bR = GetR(Bottom1P, Bottom2P, InvisibleTotal);

      HBMR.Fill(bMR);
      HBMRT.Fill(bMRT);
      HBR.Fill(bR);
      HBMRVsR.Fill(bMR, bR);
   }

   TCanvas canvas;

   canvas.Divide(2, 2);

   canvas.cd(1);
   HMR.Draw();
   canvas.cd(1)->SetLogy();

   canvas.cd(2);
   HMRT.Draw();
   canvas.cd(2)->SetLogy();
   
   canvas.cd(3);
   HR.Draw();
   canvas.cd(3)->SetLogy();
   
   canvas.cd(4);
   HMRVsR.Draw("colz");

   PsFile.AddCanvas(canvas);
   
   /*
   TCanvas bcanvas;

   bcanvas.Divide(2, 2);

   bcanvas.cd(1);
   HBMR.Draw();
   bcanvas.cd(1)->SetLogy();

   bcanvas.cd(2);
   HBMRT.Draw();
   bcanvas.cd(2)->SetLogy();
   
   bcanvas.cd(3);
   HBR.Draw();
   bcanvas.cd(3)->SetLogy();
   
   bcanvas.cd(4);
   HBMRVsR.Draw("colz");

   PsFile.AddCanvas(bcanvas);
   */
}





