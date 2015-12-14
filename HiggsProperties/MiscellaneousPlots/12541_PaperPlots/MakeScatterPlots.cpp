#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TFile.h"
#include "TGraph.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile Model" << endl;
      return -1;
   }

   TFile FInput(argv[1]);

   string Model = "11";
   if(string(argv[2]) == "16" || string(argv[2]) == "36")
      Model = "16";

   double CentralValue11[] = {99999, 0, 0, 0, 0, 0, 0, 0.375};
   double CentralValue16[] = {99999, 3.85, 5.05, 0, 0, 0, 0, 0.375};
   double *CentralValue;
   if(Model == "11")
      CentralValue = CentralValue11;
   else
      CentralValue = CentralValue16;

   string Labels[] = {"R_{1}^{ZZ}", "R_{2}^{ZZ}", "R_{3}^{ZZ}", "R_{2}^{Z#gamma}", "R_{3}^{Z#gamma}", "R_{2}^{#gamma#gamma}", "R_{3}^{#gamma#gamma}", "F_{B}"};

   string NNString, FString, SString, CString;

   for(int iN = 0; iN < 2; iN++)
   {
      if(iN == 0)   NNString = "NN";
      else          NNString = "YY";

      for(int iF = 0; iF < 2; iF++)
      {
         if(iF == 0)   FString = "N";
         else          FString = "Y";

         for(int iS = 1; iS <= 7; iS++)
         {
            SString = Form("%d", iS);

            for(int iC1 = 1; iC1 <= 8; iC1++)
            {
               for(int iC2 = iC1 + 1; iC2 <= 8; iC2++)
               {
                  CString = Form("%d%d", iC1, iC2);
                  
                  string HistogramID = "H_O_" + NNString + "_" + FString + "_" + SString + "_" + CString;

                  TH2D *H = (TH2D *)FInput.Get(HistogramID.c_str());
                  if(H == NULL)
                     continue;
                  if(H->GetMaximum() == 0)
                     continue;

                  H->SetStats(0);
                  H->Rebin2D(3, 3);

                  H->SetTitle("");
                  H->GetXaxis()->SetTitle(Labels[iC1-1].c_str());
                  H->GetYaxis()->SetTitle(Labels[iC2-1].c_str());

                  H->GetXaxis()->SetTitleSize(0.04);
                  H->GetYaxis()->SetTitleSize(0.04);
                  H->GetXaxis()->SetTitleOffset(1.25);
                  H->GetYaxis()->SetTitleOffset(1.6);

                  H->GetXaxis()->SetLabelSize(0.04);
                  H->GetYaxis()->SetLabelSize(0.04);
                  H->GetZaxis()->SetLabelSize(0.04);

                  H->GetXaxis()->CenterTitle(true);
                  H->GetYaxis()->CenterTitle(true);

                  TGraph G1, G2;
                  G1.SetLineWidth(3);
                  G2.SetLineWidth(3);
                  G1.SetLineStyle(10);
                  G2.SetLineStyle(10);
                  G1.SetPoint(0, CentralValue[iC1-1], -9999);
                  G1.SetPoint(1, CentralValue[iC1-1], +9999);
                  G2.SetPoint(0, -9999, CentralValue[iC2-1]);
                  G2.SetPoint(1, +9999, CentralValue[iC2-1]);

                  TCanvas C("C", "C", 1024, 1024);
                  C.SetLeftMargin(0.15);
                  C.SetBottomMargin(0.20);
                  C.SetRightMargin(0.15);

                  H->Draw("colz");

                  G1.Draw("l");
                  G2.Draw("l");

                  C.SaveAs(Form("Plots/Scatter_%s_%s_%s_%d_%d_%d.png", argv[1], NNString.c_str(),
                     FString.c_str(), iS, iC1, iC2));
                  C.SaveAs(Form("Plots/Scatter_%s_%s_%s_%d_%d_%d.C",   argv[1], NNString.c_str(),
                     FString.c_str(), iS, iC1, iC2));
                  C.SaveAs(Form("Plots/Scatter_%s_%s_%s_%d_%d_%d.eps", argv[1], NNString.c_str(),
                     FString.c_str(), iS, iC1, iC2));
                  C.SaveAs(Form("Plots/Scatter_%s_%s_%s_%d_%d_%d.pdf", argv[1], NNString.c_str(),
                     FString.c_str(), iS, iC1, iC2));
               }
            }
         }
      }
   }

   FInput.Close();

   return 0;
}







