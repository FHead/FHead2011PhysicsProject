#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"

#include "JetCorrector.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string L1FileName = CL.Get("l1");
   string L2L3FileName = CL.Get("l2l3");
   string OutputFileName = CL.Get("output", "Response.pdf");

   JetCorrector L1Corrector(L1FileName);
   JetCorrector L2L3Corrector(L2L3FileName);

   int EtaBinCount = 41;
   double EtaBins[] = {0,0.087,0.174,0.261,0.348,0.435,0.522,0.609,
      0.696,0.783,0.879,0.957,1.044,1.131,1.218,1.305,1.392,1.479,1.566,1.653,1.74,1.83,1.93,2.043,2.172,2.322,
      2.5,2.65,2.853,2.964,3.139,3.314,3.489,3.664,3.839,4.013,4.191,4.363,4.538,4.716,4.889,5.191};

   int PTCount = 6;
   double PTPoints[] = {15, 30, 60, 110, 400, 2000};
   double MaxEta[] = {5.2, 5.2, 5.2, 4.2, 3, 1.25};
   TGraphErrors G[6];
   int Colors[] = {kGreen + 3, kBlack, kOrange + 7, kBlue, kRed, kYellow + 3};
   int Styles[] = {20, 24, 21, 25, 22, 27};

   for(int iPT = 0; iPT < PTCount; iPT++)
   {
      for(int iEta = 0; iEta < EtaBinCount; iEta++)
      {
         double Eta = (EtaBins[iEta] + EtaBins[iEta+1]) / 2;
         double PTMin = PTPoints[iPT] * 0.6;
         double PTMax = PTPoints[iPT] * 1.2;

         if(Eta > MaxEta[iPT])
            continue;

         double PT;
         while(PTMax - PTMin > 0.001)
         {
            PT = (PTMax + PTMin) / 2;

            L1Corrector.SetJetPT(PT);
            L1Corrector.SetJetEta(Eta);
            L1Corrector.SetJetPhi(0);
            L1Corrector.SetJetArea(0.50265);
            L1Corrector.SetRho(1);

            L2L3Corrector.SetJetPT(PT * L1Corrector.GetCorrection());
            L2L3Corrector.SetJetEta(Eta);
            L2L3Corrector.SetJetPhi(0);
            L2L3Corrector.SetJetArea(0.50265);
            L2L3Corrector.SetRho(1);

            if(PT * L1Corrector.GetCorrection() * L2L3Corrector.GetCorrection() > PTPoints[iPT])
               PTMax = PT;
            else
               PTMin = PT;
         }

         G[iPT].SetPoint(iEta, Eta, PT / PTPoints[iPT]);
         // G[iPT].SetPointError(iEta, (EtaBins[iEta+1] - EtaBins[iEta]) / 2, 0);
      }

      G[iPT].SetMarkerSize(1.5);
      G[iPT].SetMarkerStyle(Styles[iPT]);
      G[iPT].SetMarkerColor(Colors[iPT]);
      G[iPT].SetLineColor(Colors[iPT]);
   }

   TGraph Lines[5];
   Lines[0].SetPoint(0, 1.25, 0.70);
   Lines[0].SetPoint(1, 1.25, 1.06);
   Lines[1].SetPoint(0, 2.50, 0.70);
   Lines[1].SetPoint(1, 2.50, 1.06);
   Lines[2].SetPoint(0, 3.00, 0.70);
   Lines[2].SetPoint(1, 3.00, 1.06);
   Lines[3].SetPoint(0, 3.20, 0.70);
   Lines[3].SetPoint(1, 3.20, 1.06);
   Lines[4].SetPoint(0, 4.50, 0.70);
   Lines[4].SetPoint(1, 4.50, 1.06);

   Lines[3].SetLineStyle(kDashed);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";Jet |#eta|;Simulated jet response", 100, 0, 4.8, 100, 0.4, 1.35);
   HWorld.SetStats(0);

   HWorld.GetXaxis()->SetLabelSize(0.045);
   HWorld.GetYaxis()->SetLabelSize(0.045);
   HWorld.GetXaxis()->SetTitleSize(0.045);
   HWorld.GetYaxis()->SetTitleSize(0.045);
   HWorld.GetXaxis()->SetTitleOffset(1.00);
   HWorld.GetYaxis()->SetTitleOffset(1.00);

   TLegend Legend1(0.15, 0.14, 0.45, 0.29);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.045);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(&G[0], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[0], PTPoints[0]), "p");
   Legend1.AddEntry(&G[1], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[1], PTPoints[1]), "p");
   Legend1.AddEntry(&G[2], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[2], PTPoints[2]), "p");
   
   TLegend Legend2(0.45, 0.14, 0.75, 0.29);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.045);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&G[3], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[3], PTPoints[3]), "p");
   Legend2.AddEntry(&G[4], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[4], PTPoints[4]), "p");
   if(PTCount >= 6) Legend2.AddEntry(&G[5], Form("#color[%d]{p_{T} = %.0f GeV}", Colors[5], PTPoints[5]), "p");
   else             Legend2.AddEntry("", " ", "");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.045);

   Latex.SetNDC();

   HWorld.Draw("axis");
   for(int iPT = 0; iPT < PTCount; iPT++)
      G[iPT].Draw("p");

   Latex.SetTextAlign(22);
   Latex.DrawLatex(0.20, 0.75, "Barrel");
   Latex.DrawLatex(0.45, 0.75, "Endcap");
   Latex.DrawLatex(0.70, 0.75, "Forward");
   Latex.DrawLatex(0.20, 0.70, "BB");
   Latex.DrawLatex(0.40, 0.70, "EC1");
   Latex.DrawLatex(0.535, 0.70, "EC2");
   Latex.DrawLatex(0.70, 0.70, "HF");

   Latex.DrawLatex(0.475, 0.82, "#font[62]{2016 JES: Anti-k_{T} R = 0.4, PF + CHS}");

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{#scale[0.8]{Simulation Preliminary}}");
   
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.85, 0.92, "#scale[0.9]{13 TeV}");

   Legend1.Draw();
   Legend2.Draw();

   Lines[0].Draw("l");
   Lines[1].Draw("l");
   Lines[2].Draw("l");
   Lines[3].Draw("l");
   Lines[4].Draw("l");

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}

