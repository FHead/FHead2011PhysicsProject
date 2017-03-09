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

   // const int ACount = 24;
   // const string A[24] =
   // {
   //    "A1VVR", "A2VVR", "A3VVR", "A4VVR", "A1VZR", "A2VZR", "A3VZR", "A4VZR", "A1VAR", "A2VAR", "A3VAR", "A4VAR",
   //    "A1VVI", "A2VVI", "A3VVI", "A4VVI", "A1VZI", "A2VZI", "A3VZI", "A4VZI", "A1VAI", "A2VAI", "A3VAI", "A4VAI"
   // };
   
   const int ACount = 18;
   const string A[18] =
   {
      "A1VVR", "A2VVR", "A3VVR", "A1VZR", "A2VZR", "A3VZR", "A1VAR", "A2VAR", "A3VAR",
      "A1VVI", "A2VVI", "A3VVI", "A1VZI", "A2VZI", "A3VZI", "A1VAI", "A2VAI", "A3VAI"
   };
   const string APaper[18] =
   {
      "#hat{A}1VVR", "#hat{A}2VVR", "#hat{A}3VVR",
      "#hat{A}1VZR", "#hat{A}2VZR", "#hat{A}3VZR",
      "#hat{A}1VAR", "#hat{A}2VAR", "#hat{A}3VAR",
      "#hat{A}1VVI", "#hat{A}2VVI", "#hat{A}3VVI",
      "#hat{A}1VZI", "#hat{A}2VZI", "#hat{A}3VZI",
      "#hat{A}1VAI", "#hat{A}2VAI", "#hat{A}3VAI"
   };
   const double Scaling[18] =
   {
      0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815,
      0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815, 0.54484, 13.3815, 13.3815
   };

   TGraph Lines;
   Lines.SetPoint(Lines.GetN(), 3, 0);
   Lines.SetPoint(Lines.GetN(), 3, 18);
   Lines.SetPoint(Lines.GetN(), 6, 18);
   Lines.SetPoint(Lines.GetN(), 6, 0);
   Lines.SetPoint(Lines.GetN(), 9, 0);
   Lines.SetPoint(Lines.GetN(), 9, 18);
   Lines.SetPoint(Lines.GetN(), 12, 18);
   Lines.SetPoint(Lines.GetN(), 12, 0);
   Lines.SetPoint(Lines.GetN(), 15, 0);
   Lines.SetPoint(Lines.GetN(), 15, 18);
   Lines.SetPoint(Lines.GetN(), 18, 18);
   Lines.SetPoint(Lines.GetN(), 18, 15);
   Lines.SetPoint(Lines.GetN(), 0, 15);
   Lines.SetPoint(Lines.GetN(), 0, 12);
   Lines.SetPoint(Lines.GetN(), 18, 12);
   Lines.SetPoint(Lines.GetN(), 18, 9);
   Lines.SetPoint(Lines.GetN(), 0, 9);
   Lines.SetPoint(Lines.GetN(), 0, 6);
   Lines.SetPoint(Lines.GetN(), 18, 6);
   Lines.SetPoint(Lines.GetN(), 18, 3);
   Lines.SetPoint(Lines.GetN(), 0, 3);

   string State = "0TeV";

   string OutputFileName = "";

   if(Is2e2mu == true)
      OutputFileName = "NormalizationMatrices2e2mu.pdf";
   else
      OutputFileName = "NormalizationMatrices4e.pdf";

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
      
      HNormalization.SetStats(0);
      HAbsNormalization.SetStats(0);
      HNormalizationPaper.SetStats(0);
      HAbsNormalizationPaper.SetStats(0);

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

      for(int iA1 = 1; iA1 <= ACount; iA1++)
         for(int iA2 = 1; iA2 <= ACount; iA2++)
            HNormalization.SetBinContent(iA1, iA2, HNormalization.GetBinContent(iA1, iA2) / V11);
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

      for(int iA1 = 1; iA1 <= ACount; iA1++)
         for(int iA2 = 1; iA2 <= ACount; iA2++)
            HNormalizationPaper.SetBinContent(iA1, iA2, HNormalizationPaper.GetBinContent(iA1, iA2) / V11);
      HAbsNormalizationPaper.Scale(1 / V11);
      HAbsNormalizationPaper.SetMinimum(HAbsNormalizationPaper.GetMaximum() * 1e-5);

      HAbsNormalizationPaper.Draw("colz");
      HNormalizationPaper.Draw("text30 same");
      Lines.Draw("l");

      cout << Cut << " " << HNormalizationPaper.GetBinContent(8, 7) << endl;

      PdfFile.AddCanvas(C);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}










