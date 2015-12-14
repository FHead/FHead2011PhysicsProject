#include <iostream>
#include <cmath>
using namespace std;

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TGraph.h"

#include "EFTBases.h"

#include "DataHelper.h"
#include "SetStyle.h"

int main();
double Evaluate(DataHelper &DHFile, string State, string Prefix, AVVBasis &A);

int main()
{
   SetThesisStyle();

   gStyle->SetPaintTextFormat(".2g");
   
   DataHelper DHFile("Normalization.dh");
   DataHelper DHFileAbs("AbsNormalization.dh");

   string HiggsLabel[8];
   HiggsLabel[0] = "#delta_{CZ}";
   HiggsLabel[1] = "#delta_{CW}";
   HiggsLabel[2] = "C_{ZZ}";
   HiggsLabel[3] = "#tilde{C}_{ZZ}";
   HiggsLabel[4] = "C_{ZA}";
   HiggsLabel[5] = "#tilde{C}_{ZA}";
   HiggsLabel[6] = "C_{AA}";
   HiggsLabel[7] = "#tilde{C}_{AA}";

   string WarsawLabel[8];
   WarsawLabel[0] = "C_{T}";
   WarsawLabel[1] = "C_{H}";
   WarsawLabel[2] = "C_{WW}";
   WarsawLabel[3] = "#tilde{C}_{WW}";
   WarsawLabel[4] = "C_{WB}";
   WarsawLabel[5] = "#tilde{C}_{WB}";
   WarsawLabel[6] = "C_{BB}";
   WarsawLabel[7] = "#tilde{C}_{BB}";

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

   for(int iC = 0; iC < 12; iC++)
   {
      for(int iT = 0; iT < 2; iT++)
      {
         string ChannelString = "T", Channel = "2e2mu", ChannelLabel = "2e2#mu";   // 2e2mu
         if(iT == 1)
            ChannelString = "V", Channel = "4e", ChannelLabel = "4e/4#mu";   // 4e

         TH2D HHiggsReal(Form("HHiggsReal_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HHiggsRealAbs(Form("HHiggsRealAbs_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HHiggsAbsReal(Form("HHiggsAbsReal_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HHiggsAbsRealAbs(Form("HHiggsAbsRealAbs_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HWarsawReal(Form("HWarsawReal_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HWarsawAbsReal(Form("HWarsawAbsReal_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HWarsawRealAbs(Form("HWarsawRealAbs_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);
         TH2D HWarsawAbsRealAbs(Form("HWarsawAbsRealAbs_%d_%d", iC, iT), "", 8, 0, 8, 8, 0, 8);

         for(int i = 0; i < 8; i++)
         {
            HHiggsReal.GetXaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsReal.GetYaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsRealAbs.GetXaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsRealAbs.GetYaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsAbsReal.GetXaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsAbsReal.GetYaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsAbsRealAbs.GetXaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HHiggsAbsRealAbs.GetYaxis()->SetBinLabel(i + 1, HiggsLabel[i].c_str());
            HWarsawReal.GetXaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawReal.GetYaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawRealAbs.GetXaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawRealAbs.GetYaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawAbsReal.GetXaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawAbsReal.GetYaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawAbsRealAbs.GetXaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
            HWarsawAbsRealAbs.GetYaxis()->SetBinLabel(i + 1, WarsawLabel[i].c_str());
         }

         double Array00[8] = {0};
         
         HiggsBasis H00(Array00);
         AVVBasis AVVH00(H00);
         double HiggsNormalization = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVH00);
         double HiggsAbsNormalization = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVH00);
         
         WarsawBasis W00(Array00);
         AVVBasis AVVW00(W00);
         double WarsawNormalization = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVW00);
         double WarsawAbsNormalization = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVW00);

         for(int i = 0; i < 8; i++)
         {
            for(int j = 0; j < 8; j++)
            {
               double ArrayII[8] = {0};   ArrayII[i] = 1;
               double ArrayJJ[8] = {0};   ArrayJJ[j] = 1;
               double ArrayIJ[8] = {0};   ArrayIJ[i] = 1;   ArrayIJ[j] = 1;

               HiggsBasis HII(ArrayII);
               HiggsBasis HJJ(ArrayJJ);
               HiggsBasis HIJ(ArrayIJ);

               AVVBasis AVVHII(HII);
               AVVBasis AVVHJJ(HJJ);
               AVVBasis AVVHIJ(HIJ);

               double ValueHII = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHII) / HiggsNormalization - 1;
               double ValueHJJ = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHJJ) / HiggsNormalization - 1;
               double ValueHIJ = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHIJ) / HiggsNormalization - 1;

               double HiggsValue = 0;
               if(i == j)   HiggsValue = ValueHII;
               else         HiggsValue = (ValueHIJ - ValueHII - ValueHJJ) / 2;

               HHiggsReal.SetBinContent(i + 1, j + 1, HiggsValue);
               HHiggsRealAbs.SetBinContent(i + 1, j + 1, fabs(HiggsValue));

               double ValueAbsHII = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHII) / HiggsAbsNormalization - 1;
               double ValueAbsHJJ = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHJJ) / HiggsAbsNormalization - 1;
               double ValueAbsHIJ = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVHIJ) / HiggsAbsNormalization - 1;

               double HiggsAbsValue = 0;
               if(i == j)   HiggsAbsValue = ValueAbsHII;
               else         HiggsAbsValue = (ValueAbsHIJ - ValueAbsHII - ValueAbsHJJ) / 2;

               HHiggsAbsReal.SetBinContent(i + 1, j + 1, HiggsAbsValue);
               HHiggsAbsRealAbs.SetBinContent(i + 1, j + 1, fabs(HiggsAbsValue));

               WarsawBasis WII(ArrayII);
               WarsawBasis WJJ(ArrayJJ);
               WarsawBasis WIJ(ArrayIJ);

               AVVBasis AVVWII(WII);
               AVVBasis AVVWJJ(WJJ);
               AVVBasis AVVWIJ(WIJ);

               double ValueWII = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWII) / WarsawNormalization - 1;
               double ValueWJJ = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWJJ) / WarsawNormalization - 1;
               double ValueWIJ = Evaluate(DHFile, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWIJ) / WarsawNormalization - 1;

               double WarsawValue = 0;
               if(i == j)   WarsawValue = ValueWII;
               else         WarsawValue = (ValueWIJ - ValueWII - ValueWJJ) / 2;

               HWarsawReal.SetBinContent(i + 1, j + 1, WarsawValue);
               HWarsawRealAbs.SetBinContent(i + 1, j + 1, fabs(WarsawValue));

               double ValueAbsWII = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWII) / WarsawAbsNormalization - 1;
               double ValueAbsWJJ = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWJJ) / WarsawAbsNormalization - 1;
               double ValueAbsWIJ = Evaluate(DHFileAbs, "Cut" + Cuts[iC], ChannelString + Cuts[iC] + "1", AVVWIJ) / WarsawAbsNormalization - 1;

               double WarsawAbsValue = 0;
               if(i == j)   WarsawAbsValue = ValueAbsWII;
               else         WarsawAbsValue = (ValueAbsWIJ - ValueAbsWII - ValueAbsWJJ) / 2;

               HWarsawAbsReal.SetBinContent(i + 1, j + 1, WarsawAbsValue);
               HWarsawAbsRealAbs.SetBinContent(i + 1, j + 1, fabs(WarsawAbsValue));
            }
         }

         TCanvas C;

         HHiggsReal.SetStats(0);
         HHiggsRealAbs.SetStats(0);
         HHiggsRealAbs.Draw("colz");

         TLatex Text;
         Text.SetTextFont(42);
         Text.SetTextAlign(22);
         Text.SetTextSize(0.02);
         Text.SetTextAngle(-15);
         for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.4g", HHiggsReal.GetBinContent(i + 1, j + 1)));

         double x1 = ThesisNDCMappingX(0.1);
         double x2 = ThesisNDCMappingX(0.9);

         TLatex LatexLeft;
         LatexLeft.SetTextFont(42);
         LatexLeft.SetTextAlign(11);
         LatexLeft.SetTextSize(0.02);
         LatexLeft.SetNDC();
         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - Normalize to offset");
         
         TLatex LatexRight;
         LatexRight.SetTextFont(42);
         LatexRight.SetTextAlign(31);
         LatexRight.SetTextSize(0.02);
         LatexRight.SetNDC();
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SetLogz();

         C.SaveAs(Form("EFTHiggsComponentSizes_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsComponentSizes_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsComponentSizes_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsComponentSizes_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HHiggsAbsReal.SetStats(0);
         HHiggsAbsRealAbs.SetStats(0);
         HHiggsAbsRealAbs.Draw("colz");
      
         for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.4g", HHiggsAbsReal.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - Normalize to offset");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));
         
         C.SaveAs(Form("EFTHiggsAbsoluteComponentSizes_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsAbsoluteComponentSizes_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsAbsoluteComponentSizes_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTHiggsAbsoluteComponentSizes_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HWarsawReal.SetStats(0);
         HWarsawRealAbs.SetStats(0);
         HWarsawRealAbs.Draw("colz");

         for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.4g", HWarsawReal.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - Normalize to offset");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));

         C.SaveAs(Form("EFTWarsawComponentSizes_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawComponentSizes_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawComponentSizes_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawComponentSizes_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));

         HWarsawAbsReal.SetStats(0);
         HWarsawAbsRealAbs.SetStats(0);
         HWarsawAbsRealAbs.Draw("colz");
      
         for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
               Text.DrawLatex(i + 0.5, j + 0.5, Form("%.4g", HWarsawAbsReal.GetBinContent(i + 1, j + 1)));

         LatexLeft.DrawLatex(x1, 0.91, "Preliminary - Normalize to offset");
         LatexRight.DrawLatex(x2, 0.91, Form("Cut %s, %s", Cuts[iC].c_str(), ChannelLabel.c_str()));
         
         C.SaveAs(Form("EFTWarsawAbsoluteComponentSizes_Cut%s_%s.png", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawAbsoluteComponentSizes_Cut%s_%s.C"  , Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawAbsoluteComponentSizes_Cut%s_%s.eps", Cuts[iC].c_str(), Channel.c_str()));
         C.SaveAs(Form("EFTWarsawAbsoluteComponentSizes_Cut%s_%s.pdf", Cuts[iC].c_str(), Channel.c_str()));
      }
   }
   
   return 0;
}

double Evaluate(DataHelper &DHFile, string State, string Prefix, AVVBasis &A)
{
   double Answer = 0;

   double As[16] = {0};
   As[0]  = A.A1ZZ;
   As[1]  = A.A2ZZ;
   As[2]  = A.A3ZZ;
   As[3]  = A.A4ZZ;
   As[4]  = A.A1ZA;
   As[5]  = A.A2ZA;
   As[6]  = A.A3ZA;
   As[7]  = A.A4ZA;
   As[8]  = A.A1ZA;
   As[9]  = A.A2ZA;
   As[10] = A.A3ZA;
   As[11] = A.A4ZA;
   As[12] = A.A1AA;
   As[13] = A.A2AA;
   As[14] = A.A3AA;
   As[15] = A.A4AA;

   string Suffix[16];
   Suffix[0]  = "_A1ZZR";
   Suffix[1]  = "_A2ZZR";
   Suffix[2]  = "_A3ZZR";
   Suffix[3]  = "_A4ZZR";
   Suffix[4]  = "_A1ZAR";
   Suffix[5]  = "_A2ZAR";
   Suffix[6]  = "_A3ZAR";
   Suffix[7]  = "_A4ZAR";
   Suffix[8]  = "_A1AZR";
   Suffix[9]  = "_A2AZR";
   Suffix[10] = "_A3AZR";
   Suffix[11] = "_A4AZR";
   Suffix[12] = "_A1AAR";
   Suffix[13] = "_A2AAR";
   Suffix[14] = "_A3AAR";
   Suffix[15] = "_A4AAR";
   
   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         Answer = Answer + DHFile[State][Prefix+Suffix[i]+Suffix[j]].GetDouble() * As[i] * As[j];

   return Answer;
}



