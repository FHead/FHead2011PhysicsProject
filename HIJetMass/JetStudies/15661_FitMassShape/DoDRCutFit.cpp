#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   PdfFileHelper PdfFile("TurnOn.pdf");
   PdfFile.AddTextPage("Turn On Fit");

   TFile File("PP6Dijet.root");

   TTree *Tree = (TTree *)File.Get("OutputTree");

   double X[100], P0[100], P1[100], P2[100], P3[100];

   int Count = 0;
   for(double DR = 0.06; DR <= 0.12; DR = DR + 0.001)
   {
      TH1D HA("HA", "", 160, 0, 0.4);
      TH1D HB("HB", "", 160, 0, 0.4);

      Tree->Draw("NewJetSDMass2/NewJetPT>>HA", "MCWeight * (JetPT > 120 && JetPT < 140 && NewJetSDMass2 > 0)", "hist");
      Tree->Draw("NewJetSDMass2/NewJetPT>>HB", Form("MCWeight * (JetPT > 120 && JetPT < 140 && NewJetSDMass2 > 0 && NewJetDR2 > %f)", DR), "hist same");

      HB.Divide(&HA);

      TF1 F("F", "(erf([0]*(x-[1]))+1)*(erf([2]*(x-[3]))+1)/4");
      F.SetParameter(0, 100);
      F.SetParameter(1, 0.04);
      F.SetParameter(2, 50);
      F.SetParameter(3, 0.03);
      HB.Fit(&F);

      X[Count] = DR;
      P0[Count] = F.GetParameter(0);
      P1[Count] = F.GetParameter(1);
      P2[Count] = F.GetParameter(2);
      P3[Count] = F.GetParameter(3);

      if(P1[Count] < P3[Count])
      {
         swap(P0[Count], P2[Count]);
         swap(P1[Count], P3[Count]);
      }

      Count = Count + 1;
   }

   TGraph G0, G1, G2, G3;
   for(int i = 0; i < Count; i++)
   {
      G0.SetPoint(i, X[i], P0[i]);
      G1.SetPoint(i, X[i], P1[i]);
      G2.SetPoint(i, X[i], P2[i]);
      G3.SetPoint(i, X[i], P3[i]);
   }

   TH2D H1("H1", ";DR;", 100, 0.05, 0.15, 100, 0, 1000);
   TH2D H2("H2", ";DR;", 100, 0.05, 0.15, 100, 0, 0.1);

   TCanvas Canvas;

   G0.SetLineColor(kBlue);
   G1.SetLineColor(kBlue);
   G2.SetLineColor(kRed);
   G3.SetLineColor(kRed);

   H1.Draw("axis");
   G0.Draw("same");
   G2.Draw("same");
   PdfFile.AddCanvas(Canvas);

   H2.Draw("axis");
   G1.Draw("same");
   G3.Draw("same");
   PdfFile.AddCanvas(Canvas);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




