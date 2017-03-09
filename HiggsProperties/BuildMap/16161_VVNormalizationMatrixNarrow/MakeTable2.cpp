#include <algorithm>
#include <iostream>
using namespace std;

#include "TStyle.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "DataHelper.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Is2e2mu=(Y|N)" << endl;
      return -1;
   }

   bool Is2e2mu = ((argv[1][0] == 'Y') ? true : false);
   
   SetThesisStyle();

   gStyle->SetPaintTextFormat(".3g");

   DataHelper DHFile("Normalization.dh");

   const int ACount = 16;
   const string A[16] =
   {
      "A1VVR", "A2VVR", "A3VVR", "A1VZR", "A2VZR", "A3VZR", "A2VAR", "A3VAR",
      "A1VVI", "A2VVI", "A3VVI", "A1VZI", "A2VZI", "A3VZI", "A2VAI", "A3VAI"
   };
   const string APaper[16] =
   {
      "A_{1}^{VV}(R)", "A_{2}^{VV}(R)", "A_{3}^{VV}(R)",
      "A_{1}^{VZ}(R)", "A_{2}^{VZ}(R)", "A_{3}^{VZ}(R)",
      "A_{2}^{VA}(R)", "A_{3}^{VA}(R)",
      "A_{1}^{VV}(I)", "A_{2}^{VV}(I)", "A_{3}^{VV}(I)",
      "A_{1}^{VZ}(I)", "A_{2}^{VZ}(I)", "A_{3}^{VZ}(I)",
      "A_{2}^{VA}(I)", "A_{3}^{VA}(I)"
   };
   const double Scaling[16] =
   {
      0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815, 13.3815, 13.3815,
      0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815, 13.3815, 13.3815
   };

   TGraph Lines;
   Lines.SetPoint(Lines.GetN(), 3, 0);
   Lines.SetPoint(Lines.GetN(), 3, 16);
   Lines.SetPoint(Lines.GetN(), 6, 16);
   Lines.SetPoint(Lines.GetN(), 6, 0);
   Lines.SetPoint(Lines.GetN(), 8, 0);
   Lines.SetPoint(Lines.GetN(), 8, 16);
   Lines.SetPoint(Lines.GetN(), 11, 16);
   Lines.SetPoint(Lines.GetN(), 11, 0);
   Lines.SetPoint(Lines.GetN(), 14, 0);
   Lines.SetPoint(Lines.GetN(), 14, 16);
   Lines.SetPoint(Lines.GetN(), 16, 16);
   Lines.SetPoint(Lines.GetN(), 16, 14);
   Lines.SetPoint(Lines.GetN(), 0, 14);
   Lines.SetPoint(Lines.GetN(), 0, 11);
   Lines.SetPoint(Lines.GetN(), 16, 11);
   Lines.SetPoint(Lines.GetN(), 16, 8);
   Lines.SetPoint(Lines.GetN(), 0, 8);
   Lines.SetPoint(Lines.GetN(), 0, 6);
   Lines.SetPoint(Lines.GetN(), 16, 6);
   Lines.SetPoint(Lines.GetN(), 16, 3);
   Lines.SetPoint(Lines.GetN(), 0, 3);

   string State = "0TeV";

   string OutputFileName = "";

   if(Is2e2mu == true)
      OutputFileName = "NormalizationMatrices2e2mu_Narrow.pdf";
   else
      OutputFileName = "NormalizationMatrices4e_Narrow.pdf";

   PdfFileHelper PdfFile(OutputFileName);

   for(int iC = 0; iC < 20; iC++)   // A - T
   {
      string Cut = "TA1";
      Cut[1] = 'A' + iC;

      if(Is2e2mu == false)
         Cut[0] = 'V';

      TH2D HNormalization("HNormalization", Form("Cut %c (AVV)", 'A' + iC), ACount, 0, ACount, ACount, 0, ACount);
      TH2D HAbsNormalization("HAbsNormalization", Form("Cut %c (AVV)", 'A' + iC), ACount, 0, ACount, ACount, 0, ACount);
      TH2D HNormalizationPaper("HNormalizationPaper", Form("Cut %c (Paper)", 'A' + iC), ACount, 0, ACount, ACount, 0, ACount);
      TH2D HAbsNormalizationPaper("HAbsNormalizationPaper", Form("Cut %c (Paper)", 'A' + iC), ACount, 0, ACount, ACount, 0, ACount);
      
      TH2D HWorldRR("HWorldRR", "", ACount / 2, 0, ACount / 2, ACount / 2, 0, ACount / 2);
      TH2D HWorldRI("HWorldRI", "", ACount / 2, ACount / 2, ACount, ACount / 2, 0, ACount / 2);

      HNormalization.SetStats(0);
      HAbsNormalization.SetStats(0);
      HNormalizationPaper.SetStats(0);
      HAbsNormalizationPaper.SetStats(0);
      
      HWorldRR.SetStats(0);
      HWorldRI.SetStats(0);

      for(int iA = 0; iA < ACount; iA++)
      {
         HAbsNormalization.GetXaxis()->SetBinLabel(iA + 1, A[iA].c_str());
         HAbsNormalization.GetYaxis()->SetBinLabel(iA + 1, A[iA].c_str());
         HNormalization.GetXaxis()->SetBinLabel(iA + 1, A[iA].c_str());
         HNormalization.GetYaxis()->SetBinLabel(iA + 1, A[iA].c_str());
         HAbsNormalizationPaper.GetXaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
         HAbsNormalizationPaper.GetYaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
         HNormalizationPaper.GetXaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
         HNormalizationPaper.GetYaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
      }
      
      for(int iA = 0; iA < ACount / 2; iA++)
      {
         HWorldRR.GetXaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
         HWorldRR.GetYaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
         HWorldRI.GetXaxis()->SetBinLabel(iA + 1, APaper[iA+ACount/2].c_str());
         HWorldRI.GetYaxis()->SetBinLabel(iA + 1, APaper[iA].c_str());
      }

      for(int iA1 = 0; iA1 < ACount; iA1++)
      {
         for(int iA2 = 0; iA2 <= iA1; iA2++)
         {
            string A1 = A[iA1];
            string A2 = A[iA2];

            string AltA1 = A1;   swap(AltA1[2], AltA1[3]);
            string AltA2 = A2;   swap(AltA2[2], AltA2[3]);

            double V = DHFile[State][Cut+"_"+A1+"_"+A2].GetDouble();

            if(AltA1 != A1)
               V = V + DHFile[State][Cut+"_"+AltA1+"_"+A2].GetDouble();
            if(AltA2 != A2)
               V = V + DHFile[State][Cut+"_"+A1+"_"+AltA2].GetDouble();
            if(AltA1 != A1 && AltA2 != A2)
               V = V + DHFile[State][Cut+"_"+AltA1+"_"+AltA2].GetDouble();

            if(iA1 != iA2)
               V = V * 2;

            HNormalization.SetBinContent(iA1 + 1, iA2 + 1, V);
            HAbsNormalization.SetBinContent(iA1 + 1, iA2 + 1, fabs(V));
            
            HNormalizationPaper.SetBinContent(iA1 + 1, iA2 + 1, V * Scaling[iA1] * Scaling[iA2]);
            HAbsNormalizationPaper.SetBinContent(iA1 + 1, iA2 + 1, fabs(V) * Scaling[iA1] * Scaling[iA2]);
         }
      }

      TCanvas C;

      C.SetLogz();

      if(HNormalization.GetBinContent(1, 1) == 0)
         continue;

      HNormalization.SetMarkerSize(0.5);

      HAbsNormalization.SetMinimum(HAbsNormalization.GetMaximum() * 1e-5);
      HAbsNormalization.Draw("colz");
      HNormalization.Draw("text30 same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);

      double V11 = HNormalization.GetBinContent(1, 1);

      HNormalization.Scale(1 / V11);
      HAbsNormalization.Scale(1 / V11);
      HAbsNormalization.SetMinimum(HAbsNormalization.GetMaximum() * 1e-5);

      HAbsNormalization.Draw("colz");
      HNormalization.Draw("text30 same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);

      HNormalizationPaper.SetMarkerSize(0.5);

      HAbsNormalizationPaper.SetMinimum(HAbsNormalizationPaper.GetMaximum() * 1e-5);
      HAbsNormalizationPaper.Draw("colz");
      HNormalizationPaper.Draw("text30 same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);

      V11 = HNormalizationPaper.GetBinContent(1, 1);

      HNormalizationPaper.Scale(1 / V11);
      HAbsNormalizationPaper.Scale(1 / V11);
      HAbsNormalizationPaper.SetMinimum(HAbsNormalizationPaper.GetMaximum() * 1e-5);

      HAbsNormalizationPaper.Draw("colz");
      HNormalizationPaper.Draw("text30 same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);

      TH2D HNormalizationPaperRR("HNormalizationPaperRR", ";;", ACount / 2, 0, ACount / 2, ACount / 2, 0, ACount / 2);
      TH2D HNormalizationPaperRI("HNormalizationPaperRI", ";;", ACount / 2, ACount / 2, ACount, ACount / 2, 0, ACount / 2);

      for(int i = 1; i <= ACount / 2; i++)
      {
         for(int j = 1; j <= ACount / 2; j++)
         {
            HNormalizationPaperRR.SetBinContent(i, j, HNormalizationPaper.GetBinContent(i, j));
            HNormalizationPaperRI.SetBinContent(i, j, HNormalizationPaper.GetBinContent(i + ACount / 2, j));
         }
      }

      PdfFile.SetPageNumber(false);

      HWorldRR.Draw();
      HAbsNormalizationPaper.Draw("colz same");
      HNormalizationPaperRR.Draw("text30 same");
      HWorldRR.Draw("axis same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);

      HWorldRI.Draw();
      HAbsNormalizationPaper.Draw("colz same");
      HNormalizationPaperRI.Draw("text30 same");
      HWorldRI.Draw("axis same");
      Lines.Draw("l");

      PdfFile.AddCanvas(C);
      
      PdfFile.SetPageNumber(true);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}










