#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TGaxis.h"

#include "SetStyle.h"
#include "DataHelper.h"

#define NO_PRIOR 0
#define NORMAL_PRIOR 1
#define LOOSE_PRIOR 2

int main(int argc, char *argv[]);
void SetAlias(TTree *Tree);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string JobBase = "Result/JobBoth_5plet_ggPDF_J_";
   string Tag = "J_5plet";
   double TrueValue = -0.5;
   string Cut = "J";
   string Model = "5plet";
   int Prior = NO_PRIOR;
   
   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " JobBase Tag TrueValue Cut Model Prior" << endl;
      cerr << "Example: " << argv[0] << " " << JobBase
         << " " << Tag << " " << TrueValue << " " << Prior << endl;
      cerr << "Prior code: 0 = no prior, 1 = normal prior, 2 = loose prior"
         << endl;
      return -1;
   }
   
   JobBase = argv[1];
   Tag = argv[2];
   TrueValue = atof(argv[3]);
   Cut = argv[4];
   Model = argv[5];
   Prior = atoi(argv[6]);

   TGraphErrors GNNNYYNYN;
   TGraphErrors GYYYNNNYN;
   TGraphErrors GNNNNNNYN;
   TGraphErrors GNNNNYNYN;
   TGraphErrors GNNNYNNYN;
   TGraphErrors GYYYYYNYN;

   DataHelper DHFile("Yields.dh");
   double YieldPerFB_2e2mu = DHFile[Model+"_2e2mu"]["Cut"+Cut].GetDouble();
   double YieldPerFB_4e = DHFile[Model+"_4e"]["Cut"+Cut].GetDouble();
   double YieldPerFB = YieldPerFB_2e2mu + YieldPerFB_4e;

   string PriorString = " && Prior8 == 0 && Prior9 == 0";
   if(Prior == NORMAL_PRIOR)
      PriorString = " && Prior8 > 0 && Prior9 == 0";
   if(Prior == LOOSE_PRIOR)
      PriorString = " && Prior8 == 0 && Prior9 > 0";

   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int i = 0; i < 11; i++)
   {
      TFile F(Form("%s%d.root", JobBase.c_str(), Lumi[i]));
      TTree *Tree = (TTree *)F.Get("ResultTree");

      if(Tree == NULL)
         continue;
      
      SetAlias(Tree);

      TH1D HTemp("HTemp", "", 10000, 0, 100);

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && NNNYYNYN" + PriorString).c_str());
      GNNNYYNYN.SetPoint(GNNNYYNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GNNNYYNYN.SetPointError(GNNNYYNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && YYYNNNYN" + PriorString).c_str());
      GYYYNNNYN.SetPoint(GYYYNNNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GYYYNNNYN.SetPointError(GYYYNNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && NNNNNNYN" + PriorString).c_str());
      GNNNNNNYN.SetPoint(GNNNNNNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GNNNNNNYN.SetPointError(GNNNNNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && NNNNYNYN" + PriorString).c_str());
      GNNNNYNYN.SetPoint(GNNNNYNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GNNNNYNYN.SetPointError(GNNNNYNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && NNNYNNYN" + PriorString).c_str());
      GNNNYNNYN.SetPoint(GNNNYNNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GNNNYNNYN.SetPointError(GNNNYNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue),
         ("Status == 3 && Basis == 3 && YYYYYNYN" + PriorString).c_str());
      GYYYYYNYN.SetPoint(GYYYYYNYN.GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
      GYYYYYNYN.SetPointError(GYYYYYNYN.GetN() - 1, 0, HTemp.GetMeanError());
      
      F.Close();
   }
   
   GNNNYYNYN.SetMarkerColor(kBlack);
   GNNNYYNYN.SetLineColor(kBlack);
   GYYYYYNYN.SetMarkerColor(kCyan);
   GYYYYYNYN.SetLineColor(kCyan);
   GYYYNNNYN.SetMarkerColor(kGreen);
   GYYYNNNYN.SetLineColor(kGreen);
   GNNNYNNYN.SetMarkerColor(kMagenta + 3);
   GNNNYNNYN.SetLineColor(kMagenta + 3);
   GNNNNYNYN.SetMarkerColor(kRed);
   GNNNNYNYN.SetLineColor(kRed);
   GNNNNNNYN.SetMarkerColor(kBlue);
   GNNNNNNYN.SetLineColor(kBlue);

   TCanvas C;

   double LeftYield = Lumi[0] / sqrt(2) * YieldPerFB;
   double RightYield = Lumi[10] * sqrt(2) * YieldPerFB;

   TH2D HWorld("HWorld", ";N_{S};#sigma(#lambda_{WZ})",
      11, LeftYield, RightYield, 100, 0.03, 300);
   HWorld.SetStats(0);

   double CrossSection = (43.92 + 3.748) * 1000;   // fb
   double BranchingRatio = 1.25e-4;
   double HZZ = CrossSection * BranchingRatio;

   TGaxis GAxis(LeftYield, 300, RightYield, 300,
      LeftYield / HZZ, RightYield / HZZ, 510, "-G");
   GAxis.SetLabelFont(42);
   GAxis.SetLabelSize(0.035);
   GAxis.SetTitleFont(42);
   GAxis.SetTitleSize(0.035);
   GAxis.SetTitleOffset(1.00);
   GAxis.SetTitle("L^{13 TeV} #times #epsilon (fb^{-1})");

   HWorld.Draw();
   GNNNYYNYN.Draw("pl");
   GYYYNNNYN.Draw("pl");
   GNNNNNNYN.Draw("pl");
   GNNNNYNYN.Draw("pl");
   GNNNYNNYN.Draw("pl");
   GYYYYYNYN.Draw("pl");

   C.SetTickx(0);
   GAxis.Draw();

   TLegend Legend(0.60, 0.85, 0.80, 0.55);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&GNNNYYNYN, "y_{t}, #tilde{y}_{t}, #lambda_{WZ}", "pl");
   Legend.AddEntry(&GYYYYYNYN, "A_{n}^{ZZ}, y_{t}, #tilde{y}_{t}, #lambda_{WZ}", "pl");
   Legend.AddEntry(&GYYYNNNYN, "A_{n}^{ZZ}, #lambda_{WZ}", "pl");
   Legend.AddEntry(&GNNNYNNYN, "y_{t}, #lambda_{WZ}", "pl");
   Legend.AddEntry(&GNNNNYNYN, "#tilde{y}_{t}, #lambda_{WZ}", "pl");
   Legend.AddEntry(&GNNNNNNYN, "#lambda_{WZ}", "pl");
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   string PriorTag = "_NoPrior";
   if(Prior == NORMAL_PRIOR)
      PriorTag = "_NormalPrior";
   if(Prior == LOOSE_PRIOR)
      PriorTag = "_LoosePrior";

   C.SaveAs(("Plots/FigureBPrime_" + Tag + PriorTag + ".png").c_str());
   C.SaveAs(("Plots/FigureBPrime_" + Tag + PriorTag + ".C").c_str());
   C.SaveAs(("Plots/FigureBPrime_" + Tag + PriorTag + ".eps").c_str());
   C.SaveAs(("Plots/FigureBPrime_" + Tag + PriorTag + ".pdf").c_str());

   return 0;
}

void SetAlias(TTree *Tree)
{
   string First = "NNNNNNNN";
   //               -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
   string Second = "P1Error == 0 && P2Error == 0 && P3Error == 0 && P4Error == 0 && P5Error == 0 && P6Error == 0 && P7Error == 0 && P8Error == 0";

   for(int i1 = 0; i1 < 2; i1++)
   {
      if(i1 == 0)   First[0] = 'N';
      else          First[0] = 'Y';
      if(i1 == 0)   Second[8] = '=', Second[9] = '=';
      else          Second[8] = '>', Second[9] = ' ';

      for(int i2 = 0; i2 < 2; i2++)
      {
         if(i2 == 0)   First[1] = 'N';
         else          First[1] = 'Y';
         if(i2 == 0)   Second[24] = '=' , Second[25] = '=';
         else          Second[24] = '>' , Second[25] = ' ';

         for(int i3 = 0; i3 < 2; i3++)
         {
            if(i3 == 0)   First[2] = 'N';
            else          First[2] = 'Y';
            if(i3 == 0)   Second[40] = '=' , Second[41] = '=';
            else          Second[40] = '>' , Second[41] = ' ';

            for(int i4 = 0; i4 < 2; i4++)
            {
               if(i4 == 0)   First[3] = 'N';
               else          First[3] = 'Y';
               if(i4 == 0)   Second[56] = '=' , Second[57] = '=';
               else          Second[56] = '>' , Second[57] = ' ';

               for(int i5 = 0; i5 < 2; i5++)
               {
                  if(i5 == 0)   First[4] = 'N';
                  else          First[4] = 'Y';
                  if(i5 == 0)   Second[72] = '=' , Second[73] = '=';
                  else          Second[72] = '>' , Second[73] = ' ';

                  for(int i6 = 0; i6 < 2; i6++)
                  {
                     if(i6 == 0)   First[5] = 'N';
                     else          First[5] = 'Y';
                     if(i6 == 0)   Second[88] = '=' , Second[89] = '=';
                     else          Second[88] = '>' , Second[89] = ' ';

                     for(int i7 = 0; i7 < 2; i7++)
                     {
                        if(i7 == 0)   First[6] = 'N';
                        else          First[6] = 'Y';
                        if(i7 == 0)   Second[104] = '=' , Second[105] = '=';
                        else          Second[104] = '>' , Second[105] = ' ';

                        for(int i8 = 0; i8 < 2; i8++)
                        {
                           if(i8 == 0)   First[7] = 'N';
                           else          First[7] = 'Y';
                           if(i8 == 0)   Second[120] = '=' , Second[121] = '=';
                           else          Second[120] = '>' , Second[121] = ' ';

                           Tree->SetAlias(First.c_str(), Second.c_str());
                        }
                     }
                  }
               }
            }
         }
      }
   }
}




