#include <iostream>
#include <cmath>
using namespace std;

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TGraph.h"

#include "DataHelper.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   gStyle->SetPaintTextFormat(".2g");
   
   DataHelper DHFile("Normalization.dh");

   string Suffix[32];
   Suffix[0]  = "A1ZZR";
   Suffix[1]  = "A1ZZI";
   Suffix[2]  = "A2ZZR";
   Suffix[3]  = "A2ZZI";
   Suffix[4]  = "A3ZZR";
   Suffix[5]  = "A3ZZI";
   Suffix[6]  = "A4ZZR";
   Suffix[7]  = "A4ZZI";
   Suffix[8]  = "A1ZAR";
   Suffix[9]  = "A1ZAI";
   Suffix[10] = "A2ZAR";
   Suffix[11] = "A2ZAI";
   Suffix[12] = "A3ZAR";
   Suffix[13] = "A3ZAI";
   Suffix[14] = "A4ZAR";
   Suffix[15] = "A4ZAI";
   Suffix[16] = "A1AZR";
   Suffix[17] = "A1AZI";
   Suffix[18] = "A2AZR";
   Suffix[19] = "A2AZI";
   Suffix[20] = "A3AZR";
   Suffix[21] = "A3AZI";
   Suffix[22] = "A4AZR";
   Suffix[23] = "A4AZI";
   Suffix[24] = "A1AAR";
   Suffix[25] = "A1AAI";
   Suffix[26] = "A2AAR";
   Suffix[27] = "A2AAI";
   Suffix[28] = "A3AAR";
   Suffix[29] = "A3AAI";
   Suffix[30] = "A4AAR";
   Suffix[31] = "A4AAI";

   string Label[32];
   Label[0]  = "A_{1}^{ZZ}";
   Label[1]  = "A_{1}^{ZZ} (I)";
   Label[2]  = "A_{2}^{ZZ}";
   Label[3]  = "A_{2}^{ZZ} (I)";
   Label[4]  = "A_{3}^{ZZ}";
   Label[5]  = "A_{3}^{ZZ} (I)";
   Label[6]  = "A_{4}^{ZZ}";
   Label[7]  = "A_{4}^{ZZ} (I)";
   Label[8]  = "A_{1}^{Z#gamma}";
   Label[9]  = "A_{1}^{Z#gamma} (I)";
   Label[10] = "A_{2}^{Z#gamma}";
   Label[11] = "A_{2}^{Z#gamma} (I)";
   Label[12] = "A_{3}^{Z#gamma}";
   Label[13] = "A_{3}^{Z#gamma} (I)";
   Label[14] = "A_{4}^{Z#gamma}";
   Label[15] = "A_{4}^{Z#gamma} (I)";
   Label[16] = "A_{1}^{#gammaZ}";
   Label[17] = "A_{1}^{#gammaZ} (I)";
   Label[18] = "A_{2}^{#gammaZ}";
   Label[19] = "A_{2}^{#gammaZ} (I)";
   Label[20] = "A_{3}^{#gammaZ}";
   Label[21] = "A_{3}^{#gammaZ} (I)";
   Label[22] = "A_{4}^{#gammaZ}";
   Label[23] = "A_{4}^{#gammaZ} (I)";
   Label[24] = "A_{1}^{#gamma#gamma}";
   Label[25] = "A_{1}^{#gamma#gamma} (I)";
   Label[26] = "A_{2}^{#gamma#gamma}";
   Label[27] = "A_{2}^{#gamma#gamma} (I)";
   Label[28] = "A_{3}^{#gamma#gamma}";
   Label[29] = "A_{3}^{#gamma#gamma} (I)";
   Label[30] = "A_{4}^{#gamma#gamma}";
   Label[31] = "A_{4}^{#gamma#gamma} (I)";

   string Cuts[12];
   Cuts[0] = 'A';
   Cuts[1] = 'B';
   Cuts[2] = 'C';
   Cuts[3] = 'D';
   Cuts[4] = 'E';
   Cuts[5] = 'F';
   Cuts[6] = 'G';
   Cuts[7] = 'H';
   Cuts[8] = 'I';
   Cuts[9] = 'J';
   Cuts[10] = 'L';
   Cuts[11] = 'M';

   TGraph G;
   G.SetPoint(0, 4, -1);
   G.SetPoint(1, 4, 17);
   G.SetPoint(2, 8, 17);
   G.SetPoint(3, 8, -1);
   G.SetPoint(4, 12, -1);
   G.SetPoint(5, 12, 17);
   G.SetPoint(6, 17, 17);
   G.SetPoint(7, 17, 12);
   G.SetPoint(8, -1, 12);
   G.SetPoint(9, -1, 8);
   G.SetPoint(10, 17, 8);
   G.SetPoint(11, 17, 4);
   G.SetPoint(12, -1, 4);
   G.SetPoint(13, -1, -1);
   G.SetPoint(14, 4, -1);
   G.SetLineWidth(3);
   G.SetLineColor(kBlack);

   for(int iC = 0; iC < 12; iC++)
   {
      for(int iT = 0; iT < 2; iT++)
      {
         string ChannelString = "T", Channel = "2e2mu", ChannelLabel = "2e2#mu";   // 2e2mu
         if(iT == 1)
            ChannelString = "V", Channel = "4e", ChannelLabel = "4e/4#mu";   // 4e

         TH2D HReal(Form("HReal_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);
         TH2D HRealAbs(Form("HRealAbs_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);
         TH2D HScaled(Form("HScaled_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);
         TH2D HScaledAbs(Form("HScaledAbs_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);
         TH2D HError(Form("HError_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);
         TH2D HRelativeError(Form("HRelativeError_%d_%d", iC, iT), "", 16, 0, 16, 16, 0, 16);

         for(int i = 0; i < 16; i++)
         {
            HReal.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HReal.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HRealAbs.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HRealAbs.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HScaled.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HScaled.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HScaledAbs.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HScaledAbs.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HError.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HError.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HRelativeError.GetXaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
            HRelativeError.GetYaxis()->SetBinLabel(i + 1, Label[i*2].c_str());
         }

         double Normalization = DHFile["Cut"+Cuts[iC]][ChannelString+Cuts[iC]+"1_A1ZZR_A1ZZR"].GetDouble();

         for(int i = 0; i < 16; i++)
         {
            for(int j = 0; j < 16; j++)
            {
               double Factor = 1;
               if(i == 0)   Factor = Factor * 2;
               if(j == 0)   Factor = Factor * 2;

               string Name = ChannelString + Cuts[iC] + "1_" + Suffix[i*2] + "_" + Suffix[j*2];
               HReal.SetBinContent(i + 1, j + 1, DHFile["Cut"+Cuts[iC]][Name].GetDouble() / Normalization * Factor / 4);
               HRealAbs.SetBinContent(i + 1, j + 1, fabs(DHFile["Cut"+Cuts[iC]][Name].GetDouble() / Normalization * Factor / 4));
               HError.SetBinContent(i + 1, j + 1, fabs(DHFile["Cut"+Cuts[iC]]["Error_"+Name].GetDouble()) / Normalization * Factor / 4);
               HRelativeError.SetBinContent(i + 1, j + 1, HError.GetBinContent(i + 1, j + 1) / HReal.GetBinContent(i + 1, j + 1));
            }
         }

         for(int i = 1; i <= 16; i++)
         {
            for(int j = 1; j <= 16; j++)
            {
               HScaled.SetBinContent(i, j, HReal.GetBinContent(i, j) / sqrt(HReal.GetBinContent(i, i) * HReal.GetBinContent(j, j)));
               HScaledAbs.SetBinContent(i, j, HRealAbs.GetBinContent(i, j) / sqrt(HRealAbs.GetBinContent(i, i) * HRealAbs.GetBinContent(j, j)));
            }
         }

         // HReal.SetMaximum(1000);
         // HReal.SetMinimum(-1000);

         TCanvas C;

         HReal.SetStats(0);
         HRealAbs.SetStats(0);
         HRealAbs.Draw("colz");
         G.Draw("l");

         TLatex Text;
         Text.SetTextFont(42);
         Text.SetTextAlign(22);
         Text.SetTextSize(0.015);
         Text.SetTextAngle(-15);
         for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.2g", HReal.GetBinContent(i + 1, j + 1)));

         double x1 = ThesisNDCMappingX(0.1);
         double x2 = ThesisNDCMappingX(0.9);

         TLatex LatexLeft;
         LatexLeft.SetTextFont(42);
         LatexLeft.SetTextAlign(11);
         LatexLeft.SetTextSize(0.02);
         LatexLeft.SetNDC();
         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - CP-odd terms not zeroed out");
         
         TLatex LatexRight;
         LatexRight.SetTextFont(42);
         LatexRight.SetTextAlign(31);
         LatexRight.SetTextSize(0.02);
         LatexRight.SetNDC();
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SetLogz();

         C.SaveAs(Form("EFTComponentSizes_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizes_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizes_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizes_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HScaled.SetStats(0);
         HScaledAbs.SetStats(0);
         HScaledAbs.Draw("colz");
         G.Draw("l");

         for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.2g", HScaled.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - CP-odd terms not zeroed out");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SaveAs(Form("EFTComponentSizesScaled_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizesScaled_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizesScaled_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentSizesScaled_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HRelativeError.SetMaximum(1);
         HRelativeError.SetMinimum(0.01);
         HRelativeError.SetStats(0);
         HRelativeError.Draw("colz");
         G.Draw("l");

         for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.2g", HRelativeError.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - CP-odd terms not zeroed out");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SaveAs(Form("EFTComponentRelativeError_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentRelativeError_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentRelativeError_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentRelativeError_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HError.SetStats(0);
         HError.Draw("colz");
         G.Draw("l");

         for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.2g", HError.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - CP-odd terms not zeroed out");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SaveAs(Form("EFTComponentError_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentError_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentError_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTComponentError_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));
      }
   }
   
   return 0;
}




