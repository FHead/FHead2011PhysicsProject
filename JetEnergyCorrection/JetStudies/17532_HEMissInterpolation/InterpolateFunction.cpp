#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "SetStyle.h"
#include "TH2D.h"
#include "TProfile.h"

#include "PlotHelper3.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
double Evaluate(double R1, double D, double BadPhiMin, double BadPhiMax, double R0, double JetPhi);
double Integrate(double R1, double D, double BadPhiMin, double BadPhiMax, double PhiMin, double PhiMax, double R0);
double FindD(double R1, double Rbad, double BadPhiMin, double BadPhiMax, double PhiMin, double PhiMax, double R0);
void PlotFunction(PdfFileHelper &PdfFile, double R1, double D, double BadPhiMin, double BadPhiMax, double R0);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string Algorithm = CL.Get("algorithm", "ak4pf");
   
   double PhiMin = CL.GetDouble("phimin", -1.6);
   double PhiMax = CL.GetDouble("phimax", -0.9);
   double BadPhiMin = CL.GetDouble("badphimin", -4.67 * 20.0 / 360.0 * 2 * M_PI);
   double BadPhiMax = CL.GetDouble("badphimax", -2.67 * 20.0 / 360.0 * 2 * M_PI);
   double PTMin = CL.GetDouble("ptmin", 100);
   double PTMax = CL.GetDouble("ptmax", 200);
   double EtaMin = CL.GetDouble("etamin", -2.5);
   double EtaMax = CL.GetDouble("etamax", -1.7);
   double R0 = CL.GetDouble("r0", 0.4);

   double R1 = CL.GetDouble("r1", 0.9098);
   double Rbad = CL.GetDouble("rbad", 0.7052);

   double D = FindD(R1, Rbad, BadPhiMin, BadPhiMax, PhiMin, PhiMax, R0);
   cout << R1 << " " << Rbad << " " << D << endl;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Interpolated MC truth");

   PlotFunction(PdfFile, R1, D, BadPhiMin, BadPhiMax, R0);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get(Form("%s/t", Algorithm.c_str()));
   assert(Tree != NULL);

   vector<float> *JetPT = NULL, *JetEta = NULL, *JetPhi = NULL;
   vector<float> *RefPT = NULL, *RefEta = NULL, *RefPhi = NULL;

   Tree->SetBranchAddress("jtpt", &JetPT);
   Tree->SetBranchAddress("jteta", &JetEta);
   Tree->SetBranchAddress("jtphi", &JetPhi);
   Tree->SetBranchAddress("refpt", &RefPT);
   Tree->SetBranchAddress("refeta", &RefEta);
   Tree->SetBranchAddress("refphi", &RefPhi);

   TH2D HRaw("HRaw", ";#phi;Raw response", 100, -M_PI, M_PI, 100, 0.0, 2.0);
   TH2D HCorrected("HCorrected", ";#phi;Corrected response", 100, -M_PI, M_PI, 100, 0.0, 2.0);
   TProfile PRaw("PRaw", ";#phi;Raw response", 50, -M_PI, M_PI);
   TProfile PCorrected("PCorrected", ";#phi;Corrected response", 50, -M_PI, M_PI);

   HRaw.SetStats(0);
   HCorrected.SetStats(0);

   PRaw.SetLineColor(kMagenta);
   PRaw.SetMarkerColor(kMagenta);
   PRaw.SetMarkerSize(2.0);
   PCorrected.SetLineColor(kMagenta);
   PCorrected.SetMarkerColor(kMagenta);
   PCorrected.SetMarkerSize(2.0);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      for(int i = 0; i < (int)RefPT->size(); i++)
      {
         if((*RefPT)[i] < PTMin || (*RefPT)[i] > PTMax)
            continue;
         if((*RefEta)[i] < EtaMin || (*RefEta)[i] > EtaMax)
            continue;

         double Response = Evaluate(R1, D, BadPhiMin, BadPhiMax, R0, (*JetPhi)[i]);

         HRaw.Fill((*JetPhi)[i], (*JetPT)[i] / (*RefPT)[i]);
         HCorrected.Fill((*JetPhi)[i], (*JetPT)[i] / (*RefPT)[i] / Response);
         PRaw.Fill((*JetPhi)[i], (*JetPT)[i] / (*RefPT)[i]);
         PCorrected.Fill((*JetPhi)[i], (*JetPT)[i] / (*RefPT)[i] / Response);
      }
   }

   TGraph G;
   G.SetPoint(0, -M_PI, 1.0);
   G.SetPoint(1, +M_PI, 1.0);

   TCanvas Canvas;

   HRaw.Draw("colz");
   PRaw.Draw("same");
   G.Draw("l");
   PdfFile.AddCanvas(Canvas);

   HCorrected.Draw("colz");
   PCorrected.Draw("same");
   G.Draw("l");
   PdfFile.AddCanvas(Canvas);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double Evaluate(double R1, double D, double BadPhiMin, double BadPhiMax, double R0, double JetPhi)
{
   if(JetPhi + R0 < BadPhiMin)
      return R1;
   if(JetPhi - R0 > BadPhiMax)
      return R1;
   
   double R2 = R1 * D;

   double FullArea = M_PI * R0 * R0;
   double GoodArea = FullArea;
   double BadArea = 0;

   if(JetPhi < BadPhiMin)
   {
      double X = BadPhiMin - JetPhi;
      double AbsTheta = fabs(acos(X / R0));
      double Area = R0 * R0 * AbsTheta - X * X * tan(AbsTheta);

      GoodArea = Area;
      BadArea = FullArea - Area;
   }
   else if(JetPhi > BadPhiMax)
   {
      double X = JetPhi - BadPhiMax;
      double AbsTheta = fabs(acos(X / R0));
      double Area = R0 * R0 * AbsTheta - X * X * tan(AbsTheta);

      GoodArea = Area;
      BadArea = FullArea - Area;
   }
   else
   {
      if(JetPhi - R0 < BadPhiMin)
      {
         double X = JetPhi - BadPhiMin;
         double AbsTheta = fabs(acos(X / R0));
         double Area = R0 * R0 * AbsTheta - X * X * tan(AbsTheta);

         GoodArea = GoodArea - Area;
         BadArea = BadArea + Area;
      }
      if(JetPhi + R0 > BadPhiMax)
      {
         double X = BadPhiMax - JetPhi;
         double AbsTheta = fabs(acos(X / R0));
         double Area = R0 * R0 * AbsTheta - X * X * tan(AbsTheta);

         GoodArea = GoodArea - Area;
         BadArea = BadArea + Area;
      }
   }

   return (GoodArea * R2 + BadArea * R1) / FullArea;
}

double Integrate(double R1, double D, double BadPhiMin, double BadPhiMax, double PhiMin, double PhiMax, double R0)
{
   int N = 1000;

   double Total = 0;

   for(int i = 0; i < N; i++)
   {
      double JetPhi = (PhiMax - PhiMin) / N * (i + 0.5) + PhiMin;

      double Value = Evaluate(R1, D, BadPhiMin, BadPhiMax, R0, JetPhi);
      Total = Total + Value;
   }

   return Total / N;
}

double FindD(double R1, double Rbad, double BadPhiMin, double BadPhiMax, double PhiMin, double PhiMax, double R0)
{
   double DMin = 0.0;
   double DMax = 1.0;

   while(DMax - DMin > 0.0001)
   {
      double D = (DMax + DMin) / 2;

      double Value = Integrate(R1, D, BadPhiMin, BadPhiMax, PhiMin, PhiMax, R0);

      if(Value < Rbad)
         DMin = D;
      else
         DMax = D;
   }

   return (DMax + DMin) / 2;
}

void PlotFunction(PdfFileHelper &PdfFile, double R1, double D, double BadPhiMin, double BadPhiMax, double R0)
{
   TGraph G;

   int N = 1000;

   for(int i = 0; i < 1000; i++)
   {
      double Phi = -M_PI + 2 * M_PI / N * (i + 0.5);

      double Value = Evaluate(R1, D, BadPhiMin, BadPhiMax, R0, Phi);

      G.SetPoint(i, Phi, Value);
   }

   G.SetTitle("Interpolated response");
   G.GetXaxis()->SetTitle("#phi");
   G.GetYaxis()->SetTitle("Response");

   PdfFile.AddPlot(G, "al");
}



