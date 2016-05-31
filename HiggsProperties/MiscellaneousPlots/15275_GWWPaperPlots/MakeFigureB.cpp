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

#include "SetStyle.h"

int main(int argc, char *argv[]);
void SetAlias(TTree *Tree);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string JobBase = "Result/JobBoth_5plet_ggPDF_J_";
   string Tag = "J_5plet";
   double TrueValue = -0.5;
   
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " JobBase Tag TrueValue" << endl;
      cerr << "Example: " << argv[0] << " " << JobBase
         << " " << Tag << " " << TrueValue << endl;
      return -1;
   }
   
   JobBase = argv[1];
   Tag = argv[2];
   TrueValue = atof(argv[3]);

   TGraphErrors GNNNYYNYN;
   TGraphErrors GYYYNNNYN;
   TGraphErrors GNNNNNNYN;
   TGraphErrors GNNNNYNYN;
   TGraphErrors GNNNYNNYN;
   TGraphErrors GYYYYYNYN;

   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int i = 0; i < 11; i++)
   {
      TFile F(Form("%s%d.root", JobBase.c_str(), Lumi[i]));
      TTree *Tree = (TTree *)F.Get("ResultTree");

      if(Tree == NULL)
         continue;
      
      SetAlias(Tree);

      TH1D HTemp("HTemp", "", 10000, 0, 100);

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && NNNYYNYN");
      GNNNYYNYN.SetPoint(GNNNYYNYN.GetN(), Lumi[i], HTemp.GetMean());
      GNNNYYNYN.SetPointError(GNNNYYNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && YYYNNNYN");
      GYYYNNNYN.SetPoint(GYYYNNNYN.GetN(), Lumi[i], HTemp.GetMean());
      GYYYNNNYN.SetPointError(GYYYNNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && NNNNNNYN");
      GNNNNNNYN.SetPoint(GNNNNNNYN.GetN(), Lumi[i], HTemp.GetMean());
      GNNNNNNYN.SetPointError(GNNNNNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && NNNNYNYN");
      GNNNNYNYN.SetPoint(GNNNNYNYN.GetN(), Lumi[i], HTemp.GetMean());
      GNNNNYNYN.SetPointError(GNNNNYNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && NNNYNNYN");
      GNNNYNNYN.SetPoint(GNNNYNNYN.GetN(), Lumi[i], HTemp.GetMean());
      GNNNYNNYN.SetPointError(GNNNYNNYN.GetN() - 1, 0, HTemp.GetMeanError());

      Tree->Draw(Form("abs(P7/2-%f)>>HTemp", TrueValue),
         "Status == 3 && Basis == 3 && YYYYYNYN");
      GYYYYYNYN.SetPoint(GYYYYYNYN.GetN(), Lumi[i], HTemp.GetMean());
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

   double Bins[12];
   for(int i = 0; i < 11; i++)
      Bins[i] = Lumi[i] / sqrt(2);
   Bins[11] = Lumi[10] * sqrt(2);

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});k #times #sigma(#lambda_{WZ})",
      11, Bins, 100, 0.01, 300);
   HWorld.SetStats(0);
   for(int i = 0; i < 11; i++)
      HWorld.GetXaxis()->SetBinLabel(i + 1, Form("%d", Lumi[i]));
   HWorld.GetXaxis()->SetTickLength(0);

   HWorld.Draw();
   GNNNYYNYN.Draw("pl");
   GYYYNNNYN.Draw("pl");
   GNNNNNNYN.Draw("pl");
   GNNNNYNYN.Draw("pl");
   GNNNYNNYN.Draw("pl");
   GYYYYYNYN.Draw("pl");

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

   C.SaveAs(("Plots/FigureB_" + Tag + ".png").c_str());
   C.SaveAs(("Plots/FigureB_" + Tag + ".C").c_str());
   C.SaveAs(("Plots/FigureB_" + Tag + ".eps").c_str());
   C.SaveAs(("Plots/FigureB_" + Tag + ".pdf").c_str());

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




