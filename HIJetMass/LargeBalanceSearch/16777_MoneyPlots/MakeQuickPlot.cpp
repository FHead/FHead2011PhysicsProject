#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TFile.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax);
void AddPlotAlternate(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax);
void AddPlotPrime(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax);
void Divide(TH2D *H, int Base = 1);
void Subtract(TH2D *H1, TH2D *H2);
void SubtractPrime(TH2D *H1, TH2D *H2);
void Divide(TH2D *H1, TH2D *H2);
void Pullify(TH2D *H);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   gStyle->SetPaintTextFormat(".3g");

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputRootFile OutputBase" << endl;
      return -1;
   }

   string FileName = argv[1];
   string OutputBase = argv[2];

   PdfFileHelper PdfFile1(OutputBase + ".pdf");
   PdfFile1.AddTextPage(OutputBase);
   
   PdfFileHelper PdfFile2(OutputBase + "Ratio.pdf");
   PdfFile2.AddTextPage(OutputBase);

   PdfFileHelper PdfFile3(OutputBase + "Adjusted.pdf");
   PdfFile3.AddTextPage(OutputBase);

   int CBinCount = 5;
   double PTBinCount = 6;
   double CBinEdge[] = {0.00, 0.10, 0.30, 0.50, 0.80, 1.00};
   double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};

   TFile File(FileName.c_str());

   for(int iC = 0; iC < CBinCount; iC++)
   {
      for(int iPT = 0; iPT < PTBinCount; iPT++)
      {
         TH2D *H1 = (TH2D *)(File.Get(Form("HData_%d_%d", iC, iPT))->Clone());
         TH2D *H2 = (TH2D *)(File.Get(Form("HSmear_%d_%d", iC, iPT))->Clone());
         AddPlot(PdfFile1, H1, H2, CBinEdge[iC], CBinEdge[iC+1], PTBinEdge[iPT], PTBinEdge[iPT+1]);
         delete H2;
         delete H1;
         
         H1 = (TH2D *)(File.Get(Form("HData_%d_%d", iC, iPT))->Clone());
         H2 = (TH2D *)(File.Get(Form("HSmear_%d_%d", iC, iPT))->Clone());
         AddPlotAlternate(PdfFile2, H1, H2, CBinEdge[iC], CBinEdge[iC+1], PTBinEdge[iPT], PTBinEdge[iPT+1]);
         delete H2;
         delete H1;
         
         H1 = (TH2D *)(File.Get(Form("HData_%d_%d", iC, iPT))->Clone());
         H2 = (TH2D *)(File.Get(Form("HSmear_%d_%d", iC, iPT))->Clone());
         AddPlotPrime(PdfFile3, H1, H2, CBinEdge[iC], CBinEdge[iC+1], PTBinEdge[iPT], PTBinEdge[iPT+1]);
         delete H2;
         delete H1;
      }
   }

   File.Close();

   PdfFile3.AddTimeStampPage();
   PdfFile3.Close();

   PdfFile2.AddTimeStampPage();
   PdfFile2.Close();
   
   PdfFile1.AddTimeStampPage();
   PdfFile1.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax)
{
   if(GData == NULL || GSmear == NULL)
      return;

   Divide(GData, 1);
   Divide(GSmear, 1);

   PdfFile.AddTextPage(Form("Centrality: %.2f-%.2f, Jet PT: %.0f-%.0f", CMin, CMax, PTMin, PTMax));

   GData->SetTitle("PbPb");
   GData->SetStats(0);
   GData->SetMinimum(0.1);
   GData->SetMaximum(100);

   GSmear->SetTitle("Smeared pp");
   GSmear->SetStats(0);
   GSmear->SetMinimum(0.1);
   GSmear->SetMaximum(100);

   PdfFile.AddPlot(GData, "colz text error", false, true);
   PdfFile.AddPlot(GSmear, "colz text error", false, true);

   Subtract(GData, GSmear);

   GData->SetTitle("PbPb - Smeared pp");

   GData->SetMinimum(-5);
   GData->SetMaximum(+5);

   PdfFile.AddPlot(GData, "colz text error");

   Pullify(GData);
   
   PdfFile.AddPlot(GData, "colz text");
}

void AddPlotAlternate(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax)
{
   if(GData == NULL || GSmear == NULL)
      return;

   Divide(GData, 5);
   Divide(GSmear, 5);

   PdfFile.AddTextPage(Form("Centrality: %.2f-%.2f, Jet PT: %.0f-%.0f", CMin, CMax, PTMin, PTMax));

   GData->SetTitle("PbPb");
   GData->SetStats(0);
   GData->SetMinimum(0.1);
   GData->SetMaximum(100);

   GSmear->SetTitle("Smeared pp");
   GSmear->SetStats(0);
   GSmear->SetMinimum(0.1);
   GSmear->SetMaximum(100);

   PdfFile.AddPlot(GData, "colz text error", false, true);
   PdfFile.AddPlot(GSmear, "colz text error", false, true);

   // Divide(GData, GSmear);

   // GData->SetTitle("PbPb / Smeared pp - 1 (in %)");

   Subtract(GData, GSmear);

   GData->SetTitle("PbPb - Smeared pp");

   GData->SetMinimum(-5);
   GData->SetMaximum(+5);

   PdfFile.AddPlot(GData, "colz text error");

   Pullify(GData);
   
   PdfFile.AddPlot(GData, "colz text");
}

void AddPlotPrime(PdfFileHelper &PdfFile, TH2D *GData, TH2D *GSmear, double CMin, double CMax, double PTMin, double PTMax)
{
   if(GData == NULL || GSmear == NULL)
      return;

   Divide(GData, 1);
   Divide(GSmear, 1);

   PdfFile.AddTextPage(Form("Centrality: %.2f-%.2f, Jet PT: %.0f-%.0f", CMin, CMax, PTMin, PTMax));

   GData->SetTitle("PbPb");
   GData->SetStats(0);
   GData->SetMinimum(0.1);
   GData->SetMaximum(100);

   GSmear->SetTitle("Smeared pp");
   GSmear->SetStats(0);
   GSmear->SetMinimum(0.1);
   GSmear->SetMaximum(100);

   PdfFile.AddPlot(GData, "colz text error", false, true);
   PdfFile.AddPlot(GSmear, "colz text error", false, true);

   SubtractPrime(GData, GSmear);

   GData->SetTitle("PbPb - (Smeared pp) * (1 + Adjustment)");

   GData->SetMinimum(-5);
   GData->SetMaximum(+5);

   PdfFile.AddPlot(GData, "colz text error");

   Pullify(GData);
   
   PdfFile.AddPlot(GData, "colz text");
}

void Divide(TH2D *H, int Base)
{
   if(H == NULL)
      return;

   for(int iY = 1; iY <= H->GetNbinsY(); iY++)
   {
      double Total = H->GetBinContent(Base, iY);
      double TotalError = H->GetBinError(Base, iY);

      for(int iX = 1; iX <= H->GetNbinsX(); iX++)
      {
         double Value = H->GetBinContent(iX, iY);
         double Error = H->GetBinError(iX, iY);

         double Difference, DifferenceError;
         double Ratio, RatioError;

         if(iX > Base)
         {
            Difference = Total - Value;
            DifferenceError = sqrt(TotalError * TotalError - Error * Error);

            Ratio = Value / Total;
            RatioError = sqrt((Difference / Total / Total * Error) * (Difference / Total / Total * Error)
               + (1 / Total / Total * DifferenceError) * (1 / Total / Total * DifferenceError));
         }
         if(iX < Base)
         {
            Difference = Value - Total;
            DifferenceError = sqrt(Error * Error - TotalError * TotalError);
            
            Ratio = Value / Total;
            RatioError = sqrt(DifferenceError * DifferenceError / Total / Total
               + (Difference / Total / Total * TotalError) * (Difference / Total / Total * TotalError));
         }
         if(iX == Base)
         {
            Ratio = 1;
            RatioError = 0;
         }

         H->SetBinContent(iX, iY, Ratio * 100);
         H->SetBinError(iX, iY, RatioError * 100);
      }
   }
}

void Subtract(TH2D *H1, TH2D *H2)
{
   if(H1 == NULL || H2 == NULL)
      return;

   for(int iX = 1; iX <= H1->GetNbinsX(); iX++)
   {
      for(int iY = 1; iY <= H1->GetNbinsY(); iY++)
      {
         double V1 = H1->GetBinContent(iX, iY);
         double E1 = H1->GetBinError(iX, iY);
         double V2 = H2->GetBinContent(iX, iY);
         double E2 = H2->GetBinError(iX, iY);

         H1->SetBinContent(iX, iY, V1 - V2);
         H1->SetBinError(iX, iY, sqrt(E1 * E1 + E2 * E2));
      }
   }
}

void SubtractPrime(TH2D *H1, TH2D *H2)
{
   if(H1 == NULL || H2 == NULL)
      return;

   for(int iY = 1; iY <= H1->GetNbinsY(); iY++)
   {
      // double VPbPb = ((iY != 1) ? H1->GetBinContent(4, iY) : H1->GetBinContent(4, 2));
      // double VPP   = ((iY != 1) ? H2->GetBinContent(4, iY) : H2->GetBinContent(4, 2));
      
      double VPbPb = H1->GetBinContent(4, iY);
      double VPP   = H2->GetBinContent(4, iY);

      double x = VPbPb / VPP - 1;

      for(int iX = 1; iX <= H1->GetNbinsX(); iX++)
      {
         double V1 = H1->GetBinContent(iX, iY);
         double E1 = H1->GetBinError(iX, iY);
         double V2 = H2->GetBinContent(iX, iY) * (1 + x);
         double E2 = H2->GetBinError(iX, iY) * (1 + x);

         H1->SetBinContent(iX, iY, V1 - V2);
         H1->SetBinError(iX, iY, sqrt(E1 * E1 + E2 * E2));
      }

      H1->SetBinContent(1, iY, x);
      H1->SetBinError(1, iY, 0);
   }
}

void Divide(TH2D *H1, TH2D *H2)
{
   if(H1 == NULL || H2 == NULL)
      return;

   for(int iX = 1; iX <= H1->GetNbinsX(); iX++)
   {
      for(int iY = 1; iY <= H1->GetNbinsY(); iY++)
      {
         double V1 = H1->GetBinContent(iX, iY);
         double E1 = H1->GetBinError(iX, iY);
         double V2 = H2->GetBinContent(iX, iY);
         double E2 = H2->GetBinError(iX, iY);

         H1->SetBinContent(iX, iY, (V1 / V2 - 1) * 100);
         if(E1 > 0 && E2 > 0)
            H1->SetBinError(iX, iY, sqrt(E1 * E1 / V1 / V1 + E2 * E2 / V2 / V2) * V1 / V2 * 100);
         else
            H1->SetBinError(iX, iY, 0);
      }
   }
}

void Pullify(TH2D *H)
{
   if(H == NULL)
      return;
   
   for(int iX = 1; iX <= H->GetNbinsX(); iX++)
   {
      for(int iY = 1; iY <= H->GetNbinsY(); iY++)
      {
         double V = H->GetBinContent(iX, iY);
         double E = H->GetBinError(iX, iY);

         if(E > 0)
            H->SetBinContent(iX, iY, V / E);
         else
            H->SetBinContent(iX, iY, 0);
      }
   }
}

