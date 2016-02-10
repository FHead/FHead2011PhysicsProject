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

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
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

   PsFileHelper PsFile("MRToy7_StaticGluon_Hemispheres.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 7");

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
   TOCItems.push_back("Changing mass of top only");

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
   Destinations.push_back("ChangeTopMass");

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
   Explanations.push_back("Associate objects into two groups so that the sum mass squared is minimum");
   Explanations.push_back("Check MR distribution changing the masses");
   Explanations.push_back("Gamma CM is always 1.1");
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

   PsFile.AddTextPage("Realistic setting: ttbar -> bWbW, both W -> e nu");
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

   PsFile.AddTextPage("Changing top mass");
   PsFile.InsertNamedDestination("ChangeTopMass");
   DoToyAndAppendPlots(PsFile, 300, 300 * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);
   DoToyAndAppendPlots(PsFile, 500, 500 * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);
   DoToyAndAppendPlots(PsFile, 800, 800 * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);
   DoToyAndAppendPlots(PsFile, 1000, 1000 * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);
   DoToyAndAppendPlots(PsFile, 1500, 1500 * 2 * GammaCM, BottomMass, WMass, ElectronMass, NuMass);

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

      FourVector HeavyParticle1Direction(1, sin(Theta) * cos(Phi), sin(Theta) * sin(Phi), cos(Theta));
      FourVector HeavyParticle2Direction(1, -sin(Theta) * cos(Phi), -sin(Theta) * sin(Phi), -cos(Theta));

      // CM frame child momentum calculation
      double M2 = TopMass * TopMass;
      double m12 = BottomMass * BottomMass;
      double m22 = WMass * WMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      FourVector Bottom1Heavy1CM, W1Heavy1CM;
      Bottom1Heavy1CM.SetSizeThetaPhiMass(Momentum, Theta1, Phi1, BottomMass);
      W1Heavy1CM.SetSizeThetaPhiMass(Momentum, PI - Theta1, PI + Phi1, WMass);

      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      FourVector Bottom2Heavy2CM, W2Heavy2CM;
      Bottom2Heavy2CM.SetSizeThetaPhiMass(Momentum, Theta2, Phi2, BottomMass);
      W2Heavy2CM.SetSizeThetaPhiMass(Momentum, PI - Theta2, PI + Phi2, WMass);

      // W CM frame child momentum calculation
      double MW2 = WMass * WMass;
      double mL2 = LeptonMass * LeptonMass;
      double mN2 = InvisibleMass * InvisibleMass;
      double WChildMomentum = sqrt(((MW2 - mL2 - mN2) * (MW2 - mL2 - mN2) - 4 * mL2 * mN2) / (4 * MW2));

      // in CM of first W
      double ThetaW1 = DrawSine(0, PI);
      double PhiW1 = DrawRandom(-PI, PI);
      FourVector Lepton1W1CM, Nu1W1CM;
      Lepton1W1CM.SetSizeThetaPhiMass(WChildMomentum, ThetaW1, PhiW1, LeptonMass);
      Nu1W1CM.SetSizeThetaPhiMass(WChildMomentum, PI - ThetaW1, PI + PhiW1, InvisibleMass);

      // in CM of second W
      double ThetaW2 = DrawSine(0, PI);
      double PhiW2 = DrawRandom(-PI, PI);
      FourVector Lepton2W2CM, Nu2W2CM;
      Lepton2W2CM.SetSizeThetaPhiMass(WChildMomentum, ThetaW2, PhiW2, LeptonMass);
      Nu2W2CM.SetSizeThetaPhiMass(WChildMomentum, PI - ThetaW2, PI + PhiW2, InvisibleMass);

      // boost to heavy object frame
      FourVector Lepton1Heavy1CM = Lepton1W1CM.Boost(W1Heavy1CM, W1Heavy1CM.GetBeta());
      FourVector Nu1Heavy1CM = Nu1W1CM.Boost(W1Heavy1CM, W1Heavy1CM.GetBeta());
      FourVector Lepton2Heavy2CM = Lepton2W2CM.Boost(W2Heavy2CM, W2Heavy2CM.GetBeta());
      FourVector Nu2Heavy2CM = Nu2W2CM.Boost(W2Heavy2CM, W2Heavy2CM.GetBeta());

      // boost back to lab frame
      FourVector Lepton1P = Lepton1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Nu1P = Nu1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Bottom1P = Bottom1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Lepton2P = Lepton2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector Nu2P = Nu2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector Bottom2P = Bottom2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      FourVector InvisibleTotal = Nu1P + Nu2P;

      vector<FourVector> Jets;
      Jets.push_back(Bottom1P);
      Jets.push_back(Bottom2P);
      Jets.push_back(Lepton1P);
      Jets.push_back(Lepton2P);

      vector<FourVector> Hemispheres = SplitIntoGroups(Jets, true);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double MRT = GetMRT(Hemispheres[0], Hemispheres[1], InvisibleTotal);
      double R = GetR(Hemispheres[0], Hemispheres[1], InvisibleTotal);

      if(MR != MR || MRT != MRT || R != R)
         continue;

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

