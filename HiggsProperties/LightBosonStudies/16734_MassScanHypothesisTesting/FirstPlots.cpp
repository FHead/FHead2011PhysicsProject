#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"

#include "PlotHelper3.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   string ModelList[10] =
   {
      "A1UU",
      "A1UUpA2UURI",
      "A1UUpA3UU",
      "A1UZ",
      "A1UZpA2UA",
      "A2UA",
      "A2UApA2UZ",
      "A2UU",
      "A2UZ",
      "A3UU"
   };

   string ModelListDiscriminant[10] =
   {
      "A1UU",
      "A1UUpA2UURI",
      "A1UUpA3UU",
      "A1UZ",
      "A1UZpA2UA",
      "A2UA",
      // "A2UZpA2UA",   // typo!  Now rerunning without the typo
      "A2UApA2UZ",
      "A2UU",
      "A2UZ",
      "A3UU"
   };

   string Cuts[2] = {"F", "P"};

   int Events[15] = {5, 7, 10, 14, 20, 30, 50, 70, 100, 140, 200, 300, 500, 700, 1000};

   DataHelper DHFile("ResultDatabase.dh");

   PdfFileHelper PdfFile("SummaryPlots.pdf");
   PdfFile.AddTextPage("Some summary plots");

   for(int iC = 0; iC < 2; iC++)
   {
      for(int iM1 = 0; iM1 < 10; iM1++)
      {
         for(int iM2 = iM1 + 1; iM2 < 10; iM2++)
         {
            string M1 = ModelList[iM1];
            string M2 = ModelList[iM2];
            if(M1 > M2)
               swap(M1, M2);
            
            string M1D = ModelListDiscriminant[iM1];
            string M2D = ModelListDiscriminant[iM2];
            if(M1D > M2D)
               swap(M1D, M2D);

            PdfFile.AddTextPage(Form("Models %s vs %s, Cut %s", M1.c_str(), M2.c_str(), Cuts[iC].c_str()));

            TGraphAsymmErrors GLD1, GLD1Plus, GLD1Minus;
            TGraphAsymmErrors GLD2, GLD2Plus, GLD2Minus;
            TGraph GModelP;
            TGraphAsymmErrors GLD1B, GLD1PlusB, GLD1MinusB;
            TGraphAsymmErrors GLD2B, GLD2PlusB, GLD2MinusB;
            TGraph GModelPB;

            GLD1.SetNameTitle("GLD1", Form("LD1, Model %d vs %d", iM1, iM2));
            GLD1Plus.SetNameTitle("GLD1Plus", Form("LD1 (+), Model %d vs %d", iM1, iM2));
            GLD1Minus.SetNameTitle("GLD1Minus", Form("LD1 (-), Model %d vs %d", iM1, iM2));
            GLD2.SetNameTitle("GLD2", Form("LD2, Model %d vs %d", iM1, iM2));
            GLD2Plus.SetNameTitle("GLD2Plus", Form("LD2 (+), Model %d vs %d", iM1, iM2));
            GLD2Minus.SetNameTitle("GLD2Minus", Form("LD2 (-), Model %d vs %d", iM1, iM2));
            GModelP.SetNameTitle("GModelP", Form("Model p-value, Model %d vs %d", iM1, iM2));
            GLD1B.SetNameTitle("GLD1", Form("LD1, Model %d vs %d, S+B", iM1, iM2));
            GLD1PlusB.SetNameTitle("GLD1PlusB", Form("LD1 (+), Model %d vs %d, S+B", iM1, iM2));
            GLD1MinusB.SetNameTitle("GLD1MinusB", Form("LD1 (-), Model %d vs %d, S+B", iM1, iM2));
            GLD2B.SetNameTitle("GLD2B", Form("LD2, Model %d vs %d, S+B", iM1, iM2));
            GLD2PlusB.SetNameTitle("GLD2PlusB", Form("LD2 (+), Model %d vs %d, S+B", iM1, iM2));
            GLD2MinusB.SetNameTitle("GLD2MinusB", Form("LD2 (-), Model %d vs %d, S+B", iM1, iM2));
            GModelPB.SetNameTitle("GModelPB", Form("Model p-value, Model %d vs %d, S+B", iM1, iM2));

            string StatePrefix = M1 + " " + M2 + " Cut" + Cuts[iC] + " ";
            string StateSuffixS = Form(" [%s %s] Fixed", M1D.c_str(), M2D.c_str());
            string StateSuffixSB = Form(" [%s %s] Floated", M1D.c_str(), M2D.c_str());

            for(int iS = 0; iS < 15; iS++)
            {
               string State = StatePrefix + Form("S(%d %d %d %d)", Events[iS], Events[iS], -1, -1) + StateSuffixS;

               GLD1.SetPoint(iS, Events[iS] * 2, DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1Plus.SetPoint(iS, Events[iS]*1.05 * 2, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1Plus.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1Minus.SetPoint(iS, Events[iS]*0.95 * 2, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1Minus.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2.SetPoint(iS, Events[iS] * 2, DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2Plus.SetPoint(iS, Events[iS]*1.05 * 2, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2Plus.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2Minus.SetPoint(iS, Events[iS]*0.95 * 2, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2Minus.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelP.SetPoint(iS, Events[iS] * 2, DHFile[State]["Model PValue"].GetDouble());
               
               State = StatePrefix + Form("S(%d %d %d %d)", Events[iS], Events[iS], Events[iS], Events[iS]) + StateSuffixSB;
               
               GLD1B.SetPoint(iS, Events[iS] * 2, DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1B.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMedian Center"].GetDouble() - DHFile[State]["L1DMedian Low"].GetDouble(),
                  DHFile[State]["L1DMedian High"].GetDouble() - DHFile[State]["L1DMedian Center"].GetDouble());
               GLD1PlusB.SetPoint(iS, Events[iS]*1.05 * 2, DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1PlusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DPlus Center"].GetDouble() - DHFile[State]["L1DPlus Low"].GetDouble(),
                  DHFile[State]["L1DPlus High"].GetDouble() - DHFile[State]["L1DPlus Center"].GetDouble());
               GLD1MinusB.SetPoint(iS, Events[iS]*0.95 * 2, DHFile[State]["L1DMinus Center"].GetDouble());
               GLD1MinusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L1DMinus Center"].GetDouble() - DHFile[State]["L1DMinus Low"].GetDouble(),
                  DHFile[State]["L1DMinus High"].GetDouble() - DHFile[State]["L1DMinus Center"].GetDouble());
               GLD2B.SetPoint(iS, Events[iS] * 2, DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2B.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMedian Center"].GetDouble() - DHFile[State]["L2DMedian Low"].GetDouble(),
                  DHFile[State]["L2DMedian High"].GetDouble() - DHFile[State]["L2DMedian Center"].GetDouble());
               GLD2PlusB.SetPoint(iS, Events[iS]*1.05 * 2, DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2PlusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DPlus Center"].GetDouble() - DHFile[State]["L2DPlus Low"].GetDouble(),
                  DHFile[State]["L2DPlus High"].GetDouble() - DHFile[State]["L2DPlus Center"].GetDouble());
               GLD2MinusB.SetPoint(iS, Events[iS]*0.95 * 2, DHFile[State]["L2DMinus Center"].GetDouble());
               GLD2MinusB.SetPointError(iS, 0, 0,
                  DHFile[State]["L2DMinus Center"].GetDouble() - DHFile[State]["L2DMinus Low"].GetDouble(),
                  DHFile[State]["L2DMinus High"].GetDouble() - DHFile[State]["L2DMinus Center"].GetDouble());
               GModelPB.SetPoint(iS, Events[iS] * 2, DHFile[State]["Model PValue"].GetDouble());
            }

            TCanvas C;
            C.SetLogx();
            C.SetLogy();

            TGraph GUp;
            GUp.SetPoint(0, 0, 0.5);
            GUp.SetPoint(1, 1000000000, 0.5);

            TH2D HWorld("HWorld", ";N_{S};p-value", 100, 7, 3000, 100, 1e-5, 1);
            HWorld.SetStats(0);

            GModelP.SetMarkerColor(kBlue);
            GModelPB.SetMarkerColor(kRed);

            HWorld.SetTitle("Model p (S [blue] vs. S+B [red])");
            HWorld.Draw();
            GModelP.Draw("p");
            GModelPB.Draw("p");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);

            /*
            HWorld.SetTitle("LD1 (S)");
            HWorld.Draw();
            GLD1.Draw("pl");
            GLD1Plus.Draw("pl");
            GLD1Minus.Draw("pl");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);

            HWorld.SetTitle("LD2 (S)");
            HWorld.Draw();
            GLD2.Draw("pl");
            GLD2Plus.Draw("pl");
            GLD2Minus.Draw("pl");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);

            HWorld.SetTitle("LD1 (S+B)");
            HWorld.Draw();
            GLD1B.Draw("pl");
            GLD1PlusB.Draw("pl");
            GLD1MinusB.Draw("pl");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);

            HWorld.SetTitle("LD2 (S+B)");
            HWorld.Draw();
            GLD2B.Draw("pl");
            GLD2PlusB.Draw("pl");
            GLD2MinusB.Draw("pl");
            GUp.Draw("l");

            PdfFile.AddCanvas(C);
            */
         }
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}








