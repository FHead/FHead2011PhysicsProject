#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TFile.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TH2D *HC0, TH2D *HC3, double PTMin, double PTMax);
void Divide(TH2D *H, int Base = 1);
void Subtract(TH2D *H1, TH2D *H2);
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

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage(OutputBase);
   
   int CBinCount = 5;
   double PTBinCount = 6;
   double CBinEdge[] = {0.00, 0.10, 0.30, 0.50, 0.80, 1.00};
   double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};

   TFile File(FileName.c_str());

   for(int iPT = 0; iPT < PTBinCount; iPT++)
   {
      TH2D *H1 = (TH2D *)(File.Get(Form("HData_%d_%d", 0, iPT))->Clone());
      TH2D *H2 = (TH2D *)(File.Get(Form("HData_%d_%d", 3, iPT))->Clone());
      AddPlot(PdfFile, H1, H2, PTBinEdge[iPT], PTBinEdge[iPT+1]);
      delete H2;
      delete H1;
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TH2D *HC0, TH2D *HC3, double PTMin, double PTMax)
{
   if(HC0 == NULL || HC3 == NULL)
      return;

   Divide(HC0, 1);
   Divide(HC3, 1);

   PdfFile.AddTextPage(Form("Jet PT: %.0f-%.0f", PTMin, PTMax));

   HC0->SetTitle("0-10%");
   HC0->SetStats(0);
   HC0->SetMinimum(0.1);
   HC0->SetMaximum(100);

   HC3->SetTitle("50-80%");
   HC3->SetStats(0);
   HC3->SetMinimum(0.1);
   HC3->SetMaximum(100);

   PdfFile.AddPlot(HC0, "colz text30 error", false, true);
   PdfFile.AddPlot(HC3, "colz text30 error", false, true);

   Subtract(HC0, HC3);

   HC0->SetTitle("P(0-10%) - P(50-80%)");

   HC0->SetMinimum(-5);
   HC0->SetMaximum(+5);

   PdfFile.AddPlot(HC0, "colz text30 error");

   Pullify(HC0);

   PdfFile.AddPlot(HC0, "colz text30");
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

