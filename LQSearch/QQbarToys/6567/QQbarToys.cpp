#include <iostream>
#include <cmath>
using namespace std;

#include "TStyle.h"
#include "TColor.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper.h"
#include "DrawRandom.h"
#include "TauHelperFunctions.h"

#include "ReadPDF.h"

int main();
void QQbarToys();

int main()
{
   gROOT->SetStyle("Plain");

   TStyle gStyle;
   
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);

   QQbarToys();

   return 0;
}

void QQbarToys()
{
   double BeamEnergy = 7000;

   double UpMass = 0.002;
   double DownMass = 0;
   double GluonMass = 0.005;

   vector<pair<double, double> > UpPDF = ReadPDF("CTEQ660__Q2_10000__Up.txt");
   vector<pair<double, double> > UpBarPDF = ReadPDF("CTEQ660__Q2_10000__UpBar.txt");
   vector<pair<double, double> > DownPDF = ReadPDF("CTEQ660__Q2_10000__Down.txt");
   vector<pair<double, double> > DownBarPDF = ReadPDF("CTEQ660__Q2_10000__DownBar.txt");
   vector<pair<double, double> > StrangePDF = ReadPDF("CTEQ660__Q2_10000__Strange.txt");
   vector<pair<double, double> > CharmPDF = ReadPDF("CTEQ660__Q2_10000__Charm.txt");
   vector<pair<double, double> > BottomPDF = ReadPDF("CTEQ660__Q2_10000__Bottom.txt");
   vector<pair<double, double> > GluonPDF = ReadPDF("CTEQ660__Q2_10000__Gluon.txt");

   TH1D HUpPDF("HUpPDF", "Up quark PDF", 500, 0, 1);
   TH1D HUpBarPDF("HUpBarPDF", "UpBar quark PDF", 500, 0, 1);
   TH1D HDownPDF("HDownPDF", "Down quark PDF", 500, 0, 1);
   TH1D HDownBarPDF("HDownBarPDF", "DownBar quark PDF", 500, 0, 1);
   TH1D HStrangePDF("HStrangePDF", "Strange quark PDF", 500, 0, 1);
   TH1D HCharmPDF("HCharmPDF", "Charm quark PDF", 500, 0, 1);
   TH1D HBottomPDF("HBottomPDF", "Bottom quark PDF", 500, 0, 1);
   TH1D HGluonPDF("HGluonPDF", "Gluon PDF", 500, 0, 1);

   TH2D HUUbarMassVsRapidity("HUUbarMassVsRapidity", "UUbar collision mass vs. rapidity;Rapidity;Mass",
      100, -5, 5, 100, 0, 1500);
   TH1D HUUbarRapiditySmall("HUUbarRapiditySmall", "UUbar collision rapidity for mass < 500 GeV", 100, -5, 5);
   TH1D HUUbarRapiditySmallBalanced("HUUbarRapiditySmallBalanced",
      "UUbar collision rapidity for mass < 500 GeV, balanced", 100, -5, 5);
   TH1D HUUbarRapidity500GeV("HUUbarRapidity500GeV", "UUbar collision rapidity for mass > 500 GeV", 100, -5, 5);
   TH1D HUUbarRapidity500GeVBalanced("HUUbarRapidity500GeVBalanced",
      "UUbar collision rapidity for mass > 500 GeV, balanced", 100, -5, 5);
   TH1D HUUbarRapidity700GeV("HUUbarRapidity700GeV", "UUbar collision rapidity for mass > 700 GeV", 100, -5, 5);
   TH1D HUUbarRapidity700GeVBalanced("HUUbarRapidity700GeVBalanced",
      "UUbar collision rapidity for mass > 700 GeV, balanced", 100, -5, 5);
   TH1D HUUbarRapidity900GeV("HUUbarRapidity900GeV", "UUbar collision rapidity for mass > 900 GeV", 100, -5, 5);
   TH1D HUUbarRapidity900GeVBalanced("HUUbarRapidity900GeVBalanced",
      "UUbar collision rapidity for mass > 900 GeV, balanced", 100, -5, 5);
   TH1D HUUbarMass("HUUbarMass", "Mass distribution from UUbar collision", 100, 0, 1500);

   TH2D HDDbarMassVsRapidity("HDDbarMassVsRapidity", "DDbar collision mass vs. rapidity;Rapidity;Mass",
      100, -5, 5, 100, 0, 1500);
   TH1D HDDbarRapiditySmall("HDDbarRapiditySmall", "DDbar collision rapidity for mass < 500 GeV", 100, -5, 5);
   TH1D HDDbarRapiditySmallBalanced("HDDbarRapiditySmallBalanced",
      "DDbar collision rapidity for mass < 500 GeV, balanced", 100, -5, 5);
   TH1D HDDbarRapidity500GeV("HDDbarRapidity500GeV", "DDbar collision rapidity for mass > 500 GeV", 100, -5, 5);
   TH1D HDDbarRapidity500GeVBalanced("HDDbarRapidity500GeVBalanced",
      "DDbar collision rapidity for mass > 500 GeV, balanced", 100, -5, 5);
   TH1D HDDbarRapidity700GeV("HDDbarRapidity700GeV", "DDbar collision rapidity for mass > 700 GeV", 100, -5, 5);
   TH1D HDDbarRapidity700GeVBalanced("HDDbarRapidity700GeVBalanced",
      "DDbar collision rapidity for mass > 700 GeV, balanced", 100, -5, 5);
   TH1D HDDbarRapidity900GeV("HDDbarRapidity900GeV", "DDbar collision rapidity for mass > 900 GeV", 100, -5, 5);
   TH1D HDDbarRapidity900GeVBalanced("HDDbarRapidity900GeVBalanced",
      "DDbar collision rapidity for mass > 900 GeV, balanced", 100, -5, 5);
   TH1D HDDbarMass("HDDbarMass", "Mass distribution from DDbar collision", 100, 0, 1500);

   TH2D HGGMassVsRapidity("HGGMassVsRapidity", "GG collision mass vs. rapidity;Rapidity;Mass",
      100, -5, 5, 100, 0, 1500);
   TH1D HGGRapiditySmall("HGGRapiditySmall", "GG collision rapidity for mass < 500 GeV", 100, -5, 5);
   TH1D HGGRapiditySmallBalanced("HGGRapiditySmallBalanced",
      "GG collision rapidity for mass < 500 GeV, balanced", 100, -5, 5);
   TH1D HGGRapidity500GeV("HGGRapidity500GeV", "GG collision rapidity for mass > 500 GeV", 100, -5, 5);
   TH1D HGGRapidity500GeVBalanced("HGGRapidity500GeVBalanced",
      "GG collision rapidity for mass > 500 GeV, balanced", 100, -5, 5);
   TH1D HGGRapidity700GeV("HGGRapidity700GeV", "GG collision rapidity for mass > 700 GeV", 100, -5, 5);
   TH1D HGGRapidity700GeVBalanced("HGGRapidity700GeVBalanced",
      "GG collision rapidity for mass > 700 GeV, balanced", 100, -5, 5);
   TH1D HGGRapidity900GeV("HGGRapidity900GeV", "GG collision rapidity for mass > 900 GeV", 100, -5, 5);
   TH1D HGGRapidity900GeVBalanced("HGGRapidity900GeVBalanced",
      "GG collision rapidity for mass > 900 GeV, balanced", 100, -5, 5);
   TH1D HGGMass("HGGMass", "Mass distribution from GG collision", 100, 0, 1500);

   // double-check PDF input
   for(int i = 0; i < 500000; i++)
   {
      HUpPDF.Fill(DrawX(UpPDF));
      HUpBarPDF.Fill(DrawX(UpBarPDF));
      HDownPDF.Fill(DrawX(DownPDF));
      HDownBarPDF.Fill(DrawX(DownBarPDF));
      HStrangePDF.Fill(DrawX(StrangePDF));
      HCharmPDF.Fill(DrawX(CharmPDF));
      HBottomPDF.Fill(DrawX(BottomPDF));
      HGluonPDF.Fill(DrawX(GluonPDF));
   }

   // Run toys on mass vs. rapidity, u + ubar
   for(int i = 0; i < 500000; i++)
   {
      double UpMomentum = DrawX(UpPDF) * BeamEnergy;
      double UpBarMomentum = DrawX(UpBarPDF) * BeamEnergy;

      double UpP[4] = {sqrt(UpMomentum * UpMomentum + UpMass * UpMass), 0, 0, UpMomentum};
      double UpBarP[4] = {sqrt(UpBarMomentum * UpBarMomentum + UpMass * UpMass), 0, 0, -UpBarMomentum};

      double TotalP[4] = {UpP[0] + UpBarP[0], UpP[1] + UpBarP[1], UpP[2] + UpBarP[2], UpP[3] + UpBarP[3]};

      double Mass = GetMass(TotalP);
      double Rapidity = GetRapidity(TotalP);

      HUUbarMassVsRapidity.Fill(Rapidity, Mass);
      HUUbarMass.Fill(Mass);

      if(Mass < 500)
      {
         HUUbarRapiditySmall.Fill(Rapidity);
         HUUbarRapiditySmallBalanced.Fill(Rapidity);
         HUUbarRapiditySmallBalanced.Fill(-Rapidity);
      }
      if(Mass > 500)
      {
         HUUbarRapidity500GeV.Fill(Rapidity);
         HUUbarRapidity500GeVBalanced.Fill(Rapidity);
         HUUbarRapidity500GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 700)
      {
         HUUbarRapidity700GeV.Fill(Rapidity);
         HUUbarRapidity700GeVBalanced.Fill(Rapidity);
         HUUbarRapidity700GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 900)
      {
         HUUbarRapidity900GeV.Fill(Rapidity);
         HUUbarRapidity900GeVBalanced.Fill(Rapidity);
         HUUbarRapidity900GeVBalanced.Fill(-Rapidity);
      }
   }

   // Run toys on mass vs. rapidity, d + dbar
   for(int i = 0; i < 500000; i++)
   {
      double DownMomentum = DrawX(DownPDF) * BeamEnergy;
      double DownBarMomentum = DrawX(DownBarPDF) * BeamEnergy;

      double DownP[4] = {sqrt(DownMomentum * DownMomentum + DownMass * DownMass), 0, 0, DownMomentum};
      double DownBarP[4] = {sqrt(DownBarMomentum * DownBarMomentum + DownMass * DownMass), 0, 0, -DownBarMomentum};

      double TotalP[4] = {DownP[0] + DownBarP[0], DownP[1] + DownBarP[1],
         DownP[2] + DownBarP[2], DownP[3] + DownBarP[3]};

      double Mass = GetMass(TotalP);
      double Rapidity = GetRapidity(TotalP);

      HDDbarMassVsRapidity.Fill(Rapidity, Mass);
      HDDbarMass.Fill(Mass);

      if(Mass < 500)
      {
         HDDbarRapiditySmall.Fill(Rapidity);
         HDDbarRapiditySmallBalanced.Fill(Rapidity);
         HDDbarRapiditySmallBalanced.Fill(-Rapidity);
      }
      if(Mass > 500)
      {
         HDDbarRapidity500GeV.Fill(Rapidity);
         HDDbarRapidity500GeVBalanced.Fill(Rapidity);
         HDDbarRapidity500GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 700)
      {
         HDDbarRapidity700GeV.Fill(Rapidity);
         HDDbarRapidity700GeVBalanced.Fill(Rapidity);
         HDDbarRapidity700GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 900)
      {
         HDDbarRapidity900GeV.Fill(Rapidity);
         HDDbarRapidity900GeVBalanced.Fill(Rapidity);
         HDDbarRapidity900GeVBalanced.Fill(-Rapidity);
      }
   }

   // Run toys on mass vs. rapidity, u + ubar
   for(int i = 0; i < 500000; i++)
   {
      double Gluon1Momentum = DrawX(GluonPDF) * BeamEnergy;
      double Gluon2Momentum = DrawX(GluonPDF) * BeamEnergy;

      double Gluon1P[4] = {sqrt(Gluon1Momentum * Gluon1Momentum + GluonMass * GluonMass), 0, 0, Gluon1Momentum};
      double Gluon2P[4] = {sqrt(Gluon2Momentum * Gluon2Momentum + GluonMass * GluonMass), 0, 0, -Gluon2Momentum};

      double TotalP[4] = {Gluon1P[0] + Gluon2P[0], Gluon1P[1] + Gluon2P[1],
         Gluon1P[2] + Gluon2P[2], Gluon1P[3] + Gluon2P[3]};

      double Mass = GetMass(TotalP);
      double Rapidity = GetRapidity(TotalP);

      HGGMassVsRapidity.Fill(Rapidity, Mass);
      HGGMass.Fill(Mass);

      if(Mass < 500)
      {
         HGGRapiditySmall.Fill(Rapidity);
         HGGRapiditySmallBalanced.Fill(Rapidity);
         HGGRapiditySmallBalanced.Fill(-Rapidity);
      }
      if(Mass > 500)
      {
         HGGRapidity500GeV.Fill(Rapidity);
         HGGRapidity500GeVBalanced.Fill(Rapidity);
         HGGRapidity500GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 700)
      {
         HGGRapidity700GeV.Fill(Rapidity);
         HGGRapidity700GeVBalanced.Fill(Rapidity);
         HGGRapidity700GeVBalanced.Fill(-Rapidity);
      }
      if(Mass > 900)
      {
         HGGRapidity900GeV.Fill(Rapidity);
         HGGRapidity900GeVBalanced.Fill(Rapidity);
         HGGRapidity900GeVBalanced.Fill(-Rapidity);
      }
   }

   PsFileHelper PsFile("ToyOnQQbar.ps");
   PsFile.AddTextPage("QQbar toys");

   vector<string> Explanations;
   Explanations.push_back("PDF: CTEQ 6.6 Central value");
   Explanations.push_back("Only exported PDF for Q^{2} = 10000 GeV^{2}");
   Explanations.push_back("....since I can't find any documentation for CTEQ file format");
   Explanations.push_back("All that's there is some interface, but no documentation :(");
   Explanations.push_back("But in any case, this should reflect, to first order, how the");
   Explanations.push_back("      rapidity distributions evolve with mass cuts");
   Explanations.push_back("==> the rapidity distribution in LQ samples are fine even though");
   Explanations.push_back("      a lot of them are from qqbar");
   PsFile.AddTextPage(Explanations);
   
   PsFile.AddTextPage("Quark PDF double-check");
   PsFile.AddPlot(HUpPDF);
   PsFile.AddPlot(HUpBarPDF);
   PsFile.AddPlot(HDownPDF);
   PsFile.AddPlot(HDownBarPDF);
   PsFile.AddPlot(HStrangePDF);
   PsFile.AddPlot(HCharmPDF);
   PsFile.AddPlot(HBottomPDF);
   PsFile.AddPlot(HGluonPDF);

   PsFile.AddTextPage("u vs. ubar");
   PsFile.AddPlot(HUUbarMassVsRapidity, "colz");
   PsFile.AddPlot(HUUbarRapiditySmall, "", false);
   PsFile.AddPlot(HUUbarRapiditySmallBalanced, "", false);
   PsFile.AddPlot(HUUbarRapidity500GeV, "", false);
   PsFile.AddPlot(HUUbarRapidity500GeVBalanced, "", false);
   PsFile.AddPlot(HUUbarRapidity700GeV, "", false);
   PsFile.AddPlot(HUUbarRapidity700GeVBalanced, "", false);
   PsFile.AddPlot(HUUbarRapidity900GeV, "", false);
   PsFile.AddPlot(HUUbarRapidity900GeVBalanced, "", false);
   PsFile.AddPlot(HUUbarMass, "", true);

   PsFile.AddTextPage("d vs. dbar");
   PsFile.AddPlot(HDDbarMassVsRapidity, "colz");
   PsFile.AddPlot(HDDbarRapiditySmall, "", false);
   PsFile.AddPlot(HDDbarRapiditySmallBalanced, "", false);
   PsFile.AddPlot(HDDbarRapidity500GeV, "", false);
   PsFile.AddPlot(HDDbarRapidity500GeVBalanced, "", false);
   PsFile.AddPlot(HDDbarRapidity700GeV, "", false);
   PsFile.AddPlot(HDDbarRapidity700GeVBalanced, "", false);
   PsFile.AddPlot(HDDbarRapidity900GeV, "", false);
   PsFile.AddPlot(HDDbarRapidity900GeVBalanced, "", false);
   PsFile.AddPlot(HDDbarMass, "", true);

   PsFile.AddTextPage("gluon vs. gluon");
   PsFile.AddPlot(HGGMassVsRapidity, "colz");
   PsFile.AddPlot(HGGRapiditySmall, "", false);
   PsFile.AddPlot(HGGRapiditySmallBalanced, "", false);
   PsFile.AddPlot(HGGRapidity500GeV, "", false);
   PsFile.AddPlot(HGGRapidity500GeVBalanced, "", false);
   PsFile.AddPlot(HGGRapidity700GeV, "", false);
   PsFile.AddPlot(HGGRapidity700GeVBalanced, "", false);
   PsFile.AddPlot(HGGRapidity900GeV, "", false);
   PsFile.AddPlot(HGGRapidity900GeVBalanced, "", false);
   PsFile.AddPlot(HGGMass, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}





