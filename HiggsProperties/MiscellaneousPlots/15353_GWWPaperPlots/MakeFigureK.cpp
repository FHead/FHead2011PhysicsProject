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
   int N = 4;
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Extended=(Y/N)" << endl;
      return -1;
   }

   if(argv[1][0] == 'Y')
      N = 5;
   else
      N = 4;

   SetThesisStyle();

   string JobBase[5] = {"Result/JobBoth_SMVV_ggPDF_J_", "Result/JobBoth_SMVV_ggPDF_J_",
      "Result/JobBoth_5plet_ggPDF_J_", "Result/JobBoth_SMVV_ggPDF_A_",
      "Result/JobBoth_SMVV_ggPDF_J_"};
   double TrueValue[5] = {1, 1, -0.5, 1, 1};
   string Cut[5] = {"J", "J", "J", "A", "J"};
   string Model[5] = {"SMVV", "SMVV", "5plet", "SMVV", "SMVV"};
   int Prior[5] = {NO_PRIOR, NORMAL_PRIOR, NORMAL_PRIOR, NORMAL_PRIOR, NO_PRIOR};
   string Float[5] = {"YYYYYNYN", "YYYYYNYN", "YYYYYNYN", "YYYYYNYN", "YYYNNNYN"};

   TGraphErrors G[5];

   DataHelper DHFile("Yields.dh");
   
   string PriorString[3] = {" && Prior8 == 0 && Prior9 == 0",
      " && Prior8 > 0 && Prior9 == 0",
      " && Prior8 == 0 && Prior9 > 0"};

   double MinYield = 10000;
   double MaxYield = -10000;

   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int j = 0; j < 5; j++)
   {
      for(int i = 0; i < 11; i++)
      {
         TFile F(Form("%s%d.root", JobBase[j].c_str(), Lumi[i]));
         TTree *Tree = (TTree *)F.Get("ResultTree");

         if(Tree == NULL)
            continue;

         SetAlias(Tree);

         double YieldPerFB_2e2mu = DHFile[Model[j]+"_2e2mu"]["Cut"+Cut[j]].GetDouble();
         double YieldPerFB_4e = DHFile[Model[j]+"_4e"]["Cut"+Cut[j]].GetDouble();
         double YieldPerFB = YieldPerFB_2e2mu + YieldPerFB_4e;

         if(YieldPerFB < MinYield)
            MinYield = YieldPerFB;
         if(YieldPerFB > MaxYield)
            MaxYield = YieldPerFB;

         TH1D HTemp("HTemp", "", 10000, 0, 100);

         Tree->Draw(Form("sqrt(3.14159265358979323846/2)*abs(P7/2-%f)>>HTemp", TrueValue[j]),
               ("Status == 3 && Basis == 3 && " + Float[j] + PriorString[Prior[j]]).c_str());
         G[j].SetPoint(G[j].GetN(), Lumi[i] * YieldPerFB, HTemp.GetMean());
         G[j].SetPointError(G[j].GetN() - 1, 0, HTemp.GetMeanError());

         F.Close();
      }
   }

   int Color[5] = {kMagenta - 9, kMagenta + 2, kGreen - 6, kMagenta + 4, kAzure - 4};
   for(int i = 0; i < 5; i++)
   {
      G[i].SetMarkerColor(Color[i]);
      G[i].SetLineColor(Color[i]);
   }

   TCanvas C;

   double LeftYield = Lumi[0] / sqrt(2) * MinYield;
   double RightYield = Lumi[10] * sqrt(2) * MaxYield;
   double BottomSigma = 0.075;
   double TopSigma = 50;
   double TopTopSigma = pow(TopSigma / BottomSigma, 0.125 * 0.55) * TopSigma;

   TH2D HWorld("HWorld", ";N_{S};#sigma(#lambda_{WZ})",
      11, LeftYield, RightYield, 100, BottomSigma, TopSigma);
   HWorld.SetStats(0);

   double CrossSection = (43.92 + 3.748) * 1000;   // fb
   double BranchingRatio = 1.25e-4;
   double HZZ = CrossSection * BranchingRatio;

   double JCutYieldPerFB_2e2mu = DHFile["SMVV_2e2mu"]["CutJ"].GetDouble();
   double JCutYieldPerFB_4e = DHFile["SMVV_4e"]["CutJ"].GetDouble();
   double JCutYieldPerFB = JCutYieldPerFB_2e2mu + JCutYieldPerFB_4e;

   TGaxis GAxis(LeftYield, TopSigma, RightYield, TopSigma,
      LeftYield / HZZ, RightYield / HZZ, 510, "-G");
   // GAxis.SetLabelFont(42);
   // GAxis.SetLabelSize(0.035);
   // GAxis.SetTitleFont(42);
   // GAxis.SetTitleSize(0.035);
   // GAxis.SetTitleOffset(1.00);
   GAxis.SetLabelFont(42);
   GAxis.SetLabelSize(0.020);
   GAxis.SetTitleFont(42);
   GAxis.SetTitleSize(0.020);
   GAxis.SetTitleOffset(1.00);
   GAxis.SetLabelOffset(-0.0065);
   GAxis.SetTitle("L^{13 TeV} #times #epsilon (fb^{-1})");

   TGaxis GAxis2(LeftYield, TopTopSigma, RightYield, TopTopSigma,
      LeftYield / JCutYieldPerFB, RightYield / JCutYieldPerFB, 510, "-GS");
   GAxis2.SetLabelFont(42);
   GAxis2.SetLabelSize(0.020);
   GAxis2.SetTitleFont(42);
   GAxis2.SetTitleSize(0.020);
   GAxis2.SetTitleOffset(1.00);
   GAxis2.SetLabelOffset(0.005);
   GAxis2.SetTickSize(0.015);
   GAxis2.SetTitle("L^{13 TeV} with nominal efficiency for Loose cut (fb^{-1})");

   HWorld.Draw();
   for(int i = 0; i < N; i++)
   {
      if(i == 2)
         continue;
      G[i].Draw("pl");
   }

   C.SetTickx(0);
   GAxis.Draw();
   GAxis2.Draw();

   string Text[5] = {"Loose cut, no prior",
      "Loose cut, prior on |y_{t}|",
      "5plet, loose cut, prior on |y_{t}|",
      "Run I CMS-like cut, prior on |y_{t}|",
      "Loose cut, y_{t} fixed"};

   TGraph G1;
   G1.SetPoint(0, 0, 1);
   G1.SetPoint(1, 10000000, 1);
   G1.SetLineStyle(kDashed);
   G1.Draw("l");

   double Bottom = 0.60;
   if(N == 5)
      Bottom = 0.85 - (0.85 - 0.60) * 0.8;
   else
      Bottom = 0.85 - (0.85 - 0.60) * 0.6;
   
   TLegend Legend(0.30, 0.85, 0.60, Bottom);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.03);
   for(int i = 0; i < N; i++)
   {
      if(i == 2)
         continue;
      Legend.AddEntry(&G[i], Text[i].c_str(), "pl");
   }
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   C.SaveAs(Form("Plots/FigureK_%d.png", N));
   C.SaveAs(Form("Plots/FigureK_%d.C", N));
   C.SaveAs(Form("Plots/FigureK_%d.eps", N));
   C.SaveAs(Form("Plots/FigureK_%d.pdf", N));

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




