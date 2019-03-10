#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TFile.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
   
#define DRBinCount 10
#define ZBinCount 7

#define MODE_NORMAL 0
#define MODE_CENTRALFOCUS 1

int main(int argc, char *argv[]);
void Divide(TH2D *H, int Base = 1);
void Subtract(TH2D *H1, TH2D *H2);
void SubtractPrime(TH2D *H1, TH2D *H2);
void Divide(TH2D *H1, TH2D *H2);
void Pullify(TH2D *H);
void TidyHistogram(TH2D *H, int Mode);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   gStyle->SetPaintTextFormat(".3g");

   if(argc != 4 && argc != 5)
   {
      cerr << "Usage: " << argv[0] << " InputRootFile OutputBase DoCorrection=(N|Y) ExtraFlag" << endl;
      cerr << "ExtraFlag =" << endl;
      cerr << "   \"CentralFocus\": focus on central bins";
      return -1;
   }

   int Mode = MODE_NORMAL;
   if(argc == 5)
   {
      string ModeString = argv[4];
      if(ModeString == "CentralFocus")
         Mode = MODE_CENTRALFOCUS;
   }

   string FileName = argv[1];
   string OutputBase = argv[2];
   bool DoCorrection = ((argv[3][0] == 'Y') ? true : false);

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage(OutputBase);
   
   int CBinCount = 5;
   double PTBinCount = 6;
   double CBinEdge[] = {0.00, 0.10, 0.30, 0.50, 0.70, 1.00};
   double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};

   if(Mode == MODE_CENTRALFOCUS)
   {
      CBinEdge[0] = 0.00;
      CBinEdge[1] = 0.05;
      CBinEdge[2] = 0.10;
      CBinEdge[3] = 0.15;
      CBinEdge[4] = 0.20;
      CBinEdge[5] = 0.30;
   }

   TFile File(FileName.c_str());

   double DRCut[] = {-1, 0, 0.05, 0.1, 0.15, 0.20, 0.25, 0.3, 0.35, 0.4};
   double ZCut[] = {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45};

   TH2D *HData[DRBinCount][ZBinCount] = {{NULL}};
   TH2D *HSmear[DRBinCount][ZBinCount] = {{NULL}};
   TH2D *HDifference[DRBinCount][ZBinCount] = {{NULL}};
   TH2D *HRatio[DRBinCount][ZBinCount] = {{NULL}};
   for(int iDR = 0; iDR < DRBinCount; iDR++)
   {
      for(int iZ = 0; iZ < ZBinCount; iZ++)
      {
         HData[iDR][iZ] = new TH2D(Form("HDataSummary%d%d", iDR, iZ),
            Form("PbPb, DR Cut %.02f, Z Cut %.02f;;", DRCut[iDR], ZCut[iZ]),
            PTBinCount, 0, PTBinCount, CBinCount, 0, CBinCount);
         HSmear[iDR][iZ] = new TH2D(Form("HSmearSummary%d%d", iDR, iZ),
            Form("Smeared pp, DR Cut %.02f, Z Cut %.02f;;", DRCut[iDR], ZCut[iZ]),
            PTBinCount, 0, PTBinCount, CBinCount, 0, CBinCount);
         HDifference[iDR][iZ] = new TH2D(Form("HDifferenceSummary%d%d", iDR, iZ),
            Form("Difference (PbPb - smeared), DR Cut %.02f, Z Cut %.02f;;", DRCut[iDR], ZCut[iZ]),
            PTBinCount, 0, PTBinCount, CBinCount, 0, CBinCount);
         HRatio[iDR][iZ] = new TH2D(Form("HRatioSummary%d%d", iDR, iZ),
            Form("Ratio (PbPb / smeared), DR Cut %.02f, Z Cut %.02f;;", DRCut[iDR], ZCut[iZ]),
            PTBinCount, 0, PTBinCount, CBinCount, 0, CBinCount);

         TidyHistogram(HData[iDR][iZ], Mode);
         TidyHistogram(HSmear[iDR][iZ], Mode);
         TidyHistogram(HDifference[iDR][iZ], Mode);
         TidyHistogram(HRatio[iDR][iZ], Mode);

         HData[iDR][iZ]->SetMinimum(0);
         HData[iDR][iZ]->SetMaximum(100);
         HSmear[iDR][iZ]->SetMinimum(0);
         HSmear[iDR][iZ]->SetMaximum(100);
         HDifference[iDR][iZ]->SetMinimum(-10);
         HDifference[iDR][iZ]->SetMaximum(+10);
         HRatio[iDR][iZ]->SetMinimum(0.8);
         HRatio[iDR][iZ]->SetMaximum(1.2);
      }
   }

   double Correction[] = {0.9852, 0.9711, 0.9469, 0.9565, 0.9471};

   for(int iC = 0; iC < CBinCount; iC++)
   {
      for(int iPT = 0; iPT < PTBinCount; iPT++)
      {
         double AdhocCorrection = (DoCorrection ? Correction[iC] : 1);

         TH2D *H1 = (TH2D *)(File.Get(Form("HData_%d_%d", iC, iPT))->Clone(Form("HData_%d_%d_Clone", iC, iPT)));
         TH2D *H2 = (TH2D *)(File.Get(Form("HSmear_%d_%d", iC, iPT))->Clone(Form("HSmear_%d_%d_Clone", iC, iPT)));

         Divide(H1, 1);
         Divide(H2, 1);

         for(int iDR = 0; iDR < DRBinCount; iDR++)
         {
            for(int iZ = 0; iZ < ZBinCount; iZ++)
            {
               double V1 = H1->GetBinContent(iDR + 1, iZ + 1);
               double V2 = H2->GetBinContent(iDR + 1, iZ + 1) * AdhocCorrection;
               double E1 = H1->GetBinError(iDR + 1, iZ + 1);
               double E2 = H2->GetBinError(iDR + 1, iZ + 1) * AdhocCorrection;

               HData[iDR][iZ]->SetBinContent(iPT + 1, iC + 1, V1);
               HData[iDR][iZ]->SetBinError(iPT + 1, iC + 1, E1);
               HSmear[iDR][iZ]->SetBinContent(iPT + 1, iC + 1, V2);
               HSmear[iDR][iZ]->SetBinError(iPT + 1, iC + 1, E2);
               HRatio[iDR][iZ]->SetBinContent(iPT + 1, iC + 1, V1 / V2);
               HRatio[iDR][iZ]->SetBinError(iPT + 1, iC + 1, V1 / V2 * sqrt(E1 * E1 / V1 / V1 + E2 * E2 / V2 / V2));
               HDifference[iDR][iZ]->SetBinContent(iPT + 1, iC + 1, V1 - V2);
               HDifference[iDR][iZ]->SetBinError(iPT + 1, iC + 1, sqrt(E1 * E1 + E2 * E2));
            }
         }
         
         delete H2;
         delete H1;
      }
   }
   
   for(int iZ = 0; iZ < ZBinCount; iZ++)
   {
      for(int iDR = 0; iDR < DRBinCount; iDR++)
      {
         PdfFile.AddPlot(HData[iDR][iZ], "colz text error");
         PdfFile.AddPlot(HSmear[iDR][iZ], "colz text error");
         PdfFile.AddPlot(HDifference[iDR][iZ], "colz text error");
         PdfFile.AddPlot(HRatio[iDR][iZ], "colz text error");
      }
   }

   for(int iDR = 0; iDR < DRBinCount; iDR++)
   {
      for(int iZ = 0; iZ < ZBinCount; iZ++)
      {
         delete HData[iDR][iZ];
         delete HSmear[iDR][iZ];
         delete HDifference[iDR][iZ];
         delete HRatio[iDR][iZ];
      }
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
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

void TidyHistogram(TH2D *H, int Mode)
{
   if(H == NULL)
      return;

   H->SetStats(0);

   H->GetXaxis()->SetBinLabel(1, "120-140");
   H->GetXaxis()->SetBinLabel(2, "140-160");
   H->GetXaxis()->SetBinLabel(3, "160-180");
   H->GetXaxis()->SetBinLabel(4, "180-200");
   H->GetXaxis()->SetBinLabel(5, "200-300");
   H->GetXaxis()->SetBinLabel(6, "300-500");

   if(Mode == MODE_NORMAL)
   {
      H->GetYaxis()->SetBinLabel(1, "0%-10%");
      H->GetYaxis()->SetBinLabel(2, "10%-30%");
      H->GetYaxis()->SetBinLabel(3, "30%-50%");
      H->GetYaxis()->SetBinLabel(4, "50%-70%");
      H->GetYaxis()->SetBinLabel(5, "70%-100%");
   }
   if(Mode == MODE_CENTRALFOCUS)
   {
      H->GetYaxis()->SetBinLabel(1, "0%-1%");
      H->GetYaxis()->SetBinLabel(2, "1%-5%");
      H->GetYaxis()->SetBinLabel(3, "5%-10%");
      H->GetYaxis()->SetBinLabel(4, "10%-15%");
      H->GetYaxis()->SetBinLabel(5, "15%-20%");
   }

   H->SetMarkerSize(1.6);
}


