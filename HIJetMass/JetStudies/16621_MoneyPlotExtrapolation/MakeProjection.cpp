#include <iostream>
using namespace std;

#include "TFile.h"
#include "TF1.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[]);
void ProjectionMass(PdfFileHelper &PdfFile, TGraphAsymmErrors *GData, TGraphAsymmErrors *GDataSys, TGraphAsymmErrors *GSmear, TGraphAsymmErrors *GSmearSys, int SD);
void ProjectionZG(PdfFileHelper &PdfFile, TGraphAsymmErrors *GData, TGraphAsymmErrors *GSmear);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio);
void Renormalize(TGraphAsymmErrors *G);
void FlatSystematics(TGraphAsymmErrors *G, TGraphAsymmErrors *GSys, double Percentage);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SD" << endl;
      return -1;
   }

   int SD = (argv[1][0] == '0') ? 0 : 7;

   TFile FInput(Form("Graphs_SD%d_DataCentered.root", SD));
   TFile FOutput(Form("Graphs_SD%d_DataProjected.root", SD), "RECREATE");

   PdfFileHelper PdfFile(string("ProjectionSanityCheck_") + argv[1] + ".pdf");
   PdfFile.AddTextPage("Sanity check");

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         cout << "Starting to run CBin " << i << " PTBin " << j << endl;

         TGraphAsymmErrors *GData     = (TGraphAsymmErrors *)FInput.Get(Form("MassData_%d_%d", i, j));
         TGraphAsymmErrors *GSmear    = (TGraphAsymmErrors *)FInput.Get(Form("MassSmear_%d_%d", i, j));
         TGraphAsymmErrors *GDataSys  = (TGraphAsymmErrors *)FInput.Get(Form("MassDataSys_%d_%d", i, j));
         TGraphAsymmErrors *GSmearSys = (TGraphAsymmErrors *)FInput.Get(Form("MassSmearSys_%d_%d", i, j));

         ProjectionMass(PdfFile, GData, GDataSys, GSmear, GSmearSys, SD);

         GData->Write();
         GSmear->Write();
         GDataSys->Write();
         GSmearSys->Write();
         
         GData     = (TGraphAsymmErrors *)FInput.Get(Form("MassData0_%d_%d", i, j));
         GSmear    = (TGraphAsymmErrors *)FInput.Get(Form("MassSmear0_%d_%d", i, j));
         GDataSys  = (TGraphAsymmErrors *)FInput.Get(Form("MassDataSys0_%d_%d", i, j));
         GSmearSys = (TGraphAsymmErrors *)FInput.Get(Form("MassSmearSys0_%d_%d", i, j));

         ProjectionMass(PdfFile, GData, GDataSys, GSmear, GSmearSys, SD);

         GData->Write();
         GSmear->Write();
         GDataSys->Write();
         GSmearSys->Write();
      
         GData     = (TGraphAsymmErrors *)FInput.Get(Form("ZGData_%d_%d", i, j));
         GSmear    = (TGraphAsymmErrors *)FInput.Get(Form("ZGSmear_%d_%d", i, j));

         ProjectionZG(PdfFile, GData, GSmear);

         GDataSys  = (TGraphAsymmErrors *)GData->Clone(Form("ZGDataSys_%d_%d", i, j));
         GSmearSys = (TGraphAsymmErrors *)GSmear->Clone(Form("ZGSmearSys_%d_%d", i, j));

         FlatSystematics(GData, GDataSys, 0.04);
         FlatSystematics(GSmear, GSmearSys, 0.04);
 
         GData->Write();
         GSmear->Write();
         GDataSys->Write();
         GSmearSys->Write();
      
         GData     = (TGraphAsymmErrors *)FInput.Get(Form("ZGData0_%d_%d", i, j));
         GSmear    = (TGraphAsymmErrors *)FInput.Get(Form("ZGSmear0_%d_%d", i, j));

         ProjectionZG(PdfFile, GData, GSmear);

         GDataSys  = (TGraphAsymmErrors *)GData->Clone(Form("ZGDataSys0_%d_%d", i, j));
         GSmearSys = (TGraphAsymmErrors *)GSmear->Clone(Form("ZGSmearSys0_%d_%d", i, j));

         FlatSystematics(GData, GDataSys, 0.04);
         FlatSystematics(GSmear, GSmearSys, 0.04);
         
         GData->Write();
         GSmear->Write();
         GDataSys->Write();
         GSmearSys->Write();
         
         ((TGraphAsymmErrors *)FInput.Get(Form("DRData_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("DRData0_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("DRSmear_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("DRSmear0_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("PTPTData_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("PTPTData0_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("PTPTSmear_%d_%d", i, j)))->Write();
         ((TGraphAsymmErrors *)FInput.Get(Form("PTPTSmear0_%d_%d", i, j)))->Write();
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FOutput.Close();
   FInput.Close();

   return 0;
}

void ProjectionMass(PdfFileHelper &PdfFile, TGraphAsymmErrors *GData, TGraphAsymmErrors *GDataSys, TGraphAsymmErrors *GSmear, TGraphAsymmErrors *GSmearSys, int SD)
{
   if(GData == NULL || GDataSys == NULL || GSmear == NULL || GSmearSys == NULL)
      return;

   if(GData->GetN() == 0 || GSmear->GetN() == 0)
      return;

   GData->SetMarkerColor(kRed);
   GDataSys->SetMarkerColor(kRed);
   GSmear->SetMarkerColor(kBlue);
   GSmearSys->SetMarkerColor(kBlue);
   GData->SetLineColor(kRed);
   GDataSys->SetLineColor(kRed);
   GSmear->SetLineColor(kBlue);
   GSmearSys->SetLineColor(kBlue);

   PdfFile.AddTextPage(string("Mass projection") + GData->GetName());

   TCanvas C;

   TH2D HWorld("HWorld", "Pre-projection;M/PT;", 100, 0.0, 0.30, 100, 0.0, 15.0);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   GData->Draw("p");
   GDataSys->Draw("p");
   GSmear->Draw("p");
   GSmearSys->Draw("p");

   PdfFile.AddCanvas(C);

   TGraphAsymmErrors GRatio;
   Division(GData, GSmear, GRatio);

   if(GRatio.GetN() == 0)
      return;

   TF1 FRatio("FRatio", "[0]+expo(1)");

   FRatio.SetParameters(0.95, -20, 0.01);

   FRatio.SetParLimits(0, 0.50, 1.00);
   FRatio.SetParLimits(1, -1000, -1000);
   FRatio.SetParLimits(2, 1.00, 1.00);

   GRatio.Fit(&FRatio, "N", "", 0.00, 0.15);

   FRatio.SetParLimits(0, FRatio.GetParameter(0), FRatio.GetParameter(0));
   FRatio.SetParLimits(1, -100.00, 100.00);
   FRatio.SetParLimits(2, 0.00, 10000.00);

   GRatio.Fit(&FRatio, "NW", "", 0.00, 0.27);

   if(SD == 7)
      FRatio.SetParameter(0, FRatio.GetParameter(0) * 4);
   
   TH2D HWorld2("HWorld2", "Ratio & fit;M/PT;R", 100, 0.0, 0.30, 100, 0.0, 5.0);
   HWorld2.SetStats(0);

   HWorld2.Draw("axis");
   GRatio.Draw("p");
   FRatio.Draw("l same");

   PdfFile.AddCanvas(C);

   double StatFactor = 5;
   double SysFactor = 2;

   for(int i = 0; i < GData->GetN(); i++)
   {
      double x, y;
      GSmear->GetPoint(i, x, y);
      
      double ex1 = GData->GetErrorXlow(i);
      double ex2 = GData->GetErrorXhigh(i);
      double ey1 = GData->GetErrorYlow(i);
      double ey2 = GData->GetErrorYhigh(i);
      double newy = y * FRatio.Eval(x) + DrawGaussian(0, (ey1 + ey2) / StatFactor);

      GData->SetPoint(i, x, newy);
      GData->SetPointError(i, ex1, ex2, ey1 / StatFactor, ey2 / StatFactor);

      ey1 = GDataSys->GetErrorYlow(i);
      ey2 = GDataSys->GetErrorYhigh(i);
      GDataSys->SetPoint(i, x, newy);
      GDataSys->SetPointError(i, ex1, ex2, ey1 / SysFactor, ey2 / SysFactor);
      
      ey1 = GSmearSys->GetErrorYlow(i);
      ey2 = GSmearSys->GetErrorYhigh(i);
      GSmearSys->SetPointError(i, ex1, ex2, ey1 / SysFactor, ey2 / SysFactor);
   }

   Renormalize(GData);
   Renormalize(GDataSys);
   
   HWorld.SetTitle("Post-projection");

   HWorld.Draw("axis");
   GData->Draw("p");
   GDataSys->Draw("p");
   GSmear->Draw("p");
   GSmearSys->Draw("p");

   PdfFile.AddCanvas(C);
}

void ProjectionZG(PdfFileHelper &PdfFile, TGraphAsymmErrors *GData, TGraphAsymmErrors *GSmear)
{
   if(GData == NULL || GSmear == NULL)
      return;

   if(GData->GetN() == 0 || GSmear->GetN() == 0)
      return;

   string Name = GData->GetName();

   if(Name == "ZGData_0_1" || Name == "ZGData0_0_1")
   {
      // do Marta trigger correction

      for(int i = 0; i < GData->GetN(); i++)
      {
         double x, y;
         GData->GetPoint(i, x, y);
         GData->SetPoint(i, x, y / (1 + 0.2 / 0.3 * (x - 0.2)));
      }
   }

   GData->SetMarkerColor(kRed);
   GSmear->SetMarkerColor(kBlue);
   GData->SetLineColor(kRed);
   GSmear->SetLineColor(kBlue);

   PdfFile.AddTextPage(string("ZG projection ") + GData->GetName());

   TCanvas C;

   TH2D HWorld("HWorld", "Pre-projection;ZG;", 100, 0.0, 0.50, 100, 0.0, 15.0);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   GData->Draw("p");
   GSmear->Draw("p");

   PdfFile.AddCanvas(C);

   TGraphAsymmErrors GRatio;
   Division(GData, GSmear, GRatio);

   if(GRatio.GetN() == 0)
      return;

   TF1 FRatio("FRatio", "expo+[2]");

   if(Name.substr(0, 9) == "ZGData_3_" || Name.substr(0, 10) == "ZGData0_3_")
      FRatio.SetParameters(0, 0, 0);
   else
   {
      GRatio.Fit(&FRatio, "N", "", 0.00, 0.50);
      if(Name.substr(0, 9) == "ZGData_2_" || Name.substr(0, 10) == "ZGData0_2_")
         FRatio.SetParameter(2, FRatio.GetParameter(2) * 2);
      if(Name.substr(0, 9) == "ZGData_1_" || Name.substr(0, 10) == "ZGData0_1_")
         FRatio.SetParameter(2, FRatio.GetParameter(2) * 1.5);
      if(Name.substr(0, 10) == "ZGData_0_4" || Name.substr(0, 11) == "ZGData0_0_4")
         FRatio.SetParameter(2, FRatio.GetParameter(2) * 1.25);
   }

   TH2D HWorld2("HWorld2", "Ratio & fit;ZG;R", 100, 0.0, 0.50, 100, 0.0, 2.0);
   HWorld2.SetStats(0);

   HWorld2.Draw("axis");
   GRatio.Draw("p");
   FRatio.Draw("l same");

   PdfFile.AddCanvas(C);

   double StatFactor = 5;
   double SysFactor = 2;

   for(int i = 0; i < GData->GetN(); i++)
   {
      double x, y;
      GSmear->GetPoint(i, x, y);
      
      double ex1 = GData->GetErrorXlow(i);
      double ex2 = GData->GetErrorXhigh(i);
      double ey1 = GData->GetErrorYlow(i);
      double ey2 = GData->GetErrorYhigh(i);
      double newy = y * FRatio.Eval(x) + DrawGaussian(0, (ey1 + ey2) / StatFactor / 2);

      GData->SetPoint(i, x, newy);
      GData->SetPointError(i, ex1, ex2, ey1 / StatFactor, ey2 / StatFactor);
   }

   Renormalize(GData);
   
   HWorld.SetTitle("Post-projection");

   HWorld.Draw("axis");
   GData->Draw("p");
   GSmear->Draw("p");

   PdfFile.AddCanvas(C);
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio)
{
   if(G1 == NULL || G2 == NULL)
      return;

   int BinCount = min(G1->GetN(), G2->GetN());

   GRatio.Set(0);

   for(int i = 0; i < BinCount; i++)
   {
      double x1, x2, y1, y2;
      G1->GetPoint(i, x1, y1);
      G2->GetPoint(i, x2, y2);

      double xl1, xh1, xl2, xh2;
      xl1 = G1->GetErrorXlow(i);
      xh1 = G1->GetErrorXhigh(i);
      xl2 = G2->GetErrorXlow(i);
      xh2 = G2->GetErrorXhigh(i);

      double yl1, yh1, yl2, yh2;
      yl1 = G1->GetErrorYlow(i);
      yh1 = G1->GetErrorYhigh(i);
      yl2 = G2->GetErrorYlow(i);
      yh2 = G2->GetErrorYhigh(i);

      double ratio = (y1 / y2);

      double yl = ratio * sqrt((yl1 / y1) * (yl1 / y1) + (yl2 / y2) * (yl2 / y2));
      double yh = ratio * sqrt((yh1 / y1) * (yh1 / y1) + (yh2 / y2) * (yh2 / y2));

      if(x1 == x1 && x2 == x2 && ratio == ratio)
      {
         int N = GRatio.GetN();
         GRatio.SetPoint(N, x1, ratio);
         GRatio.SetPointError(N, xl1, xh1, yl, yh);
      }
   }

   GRatio.SetName(Form("Ratio_%s_%s", G1->GetName(), G2->GetName()));
}

void Renormalize(TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   int N = G->GetN();

   double Integral = 0;
   for(int i = 0; i < N; i++)
   {
      double X, Y, EX1, EX2, EY1, EY2;
      G->GetPoint(i, X, Y);
      EX1 = G->GetErrorXlow(i);
      EX2 = G->GetErrorXhigh(i);
      EY1 = G->GetErrorYlow(i);
      EY2 = G->GetErrorYhigh(i);

      if(X != X || Y != Y || EX1 != EX1 || EX2 != EX2)
         continue;

      double BinSize = EX2 + EX1;
      Integral = Integral + Y * BinSize;
   }

   cout << "INTEGRAL " << G->GetName() << " " << Integral << endl;

   for(int i = 0; i < N; i++)
   {
      double X, Y, EX1, EX2, EY1, EY2;
      G->GetPoint(i, X, Y);
      EX1 = G->GetErrorXlow(i);
      EX2 = G->GetErrorXhigh(i);
      EY1 = G->GetErrorYlow(i);
      EY2 = G->GetErrorYhigh(i);

      if(X != X || Y != Y)
         continue;

      G->SetPoint(i, X, Y / Integral);
      // G->SetPointError(i, EX1, EX2, EY1 / Integral, EY2 / Integral);
   }
}

void FlatSystematics(TGraphAsymmErrors *G, TGraphAsymmErrors *GSys, double Percentage)
{
   if(G == NULL || GSys == NULL)
      return;

   int N = G->GetN();
   for(int i = 0; i < N; i++)
   {
      double X, Y, EX1, EX2;
      G->GetPoint(i, X, Y);
      EX1 = G->GetErrorXlow(i);
      EX2 = G->GetErrorXhigh(i);

      if(X != X || Y != Y)
         continue;

      GSys->SetPoint(i, X, Y);
      GSys->SetPointError(i, EX1, EX2, Y * Percentage, Y * Percentage);
   }
}







