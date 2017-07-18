#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TGaxis.h"

#include "SetStyle.h"
#include "DataHelper.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[]);
double GetAverage(TFile &F, string GraphName);
double GetError(TFile &F, string GraphName);
double GetWidth(TFile &F, string GraphName);
double GetSkewness(TFile &F, string GraphName);
double GetKurtosis(TFile &F, string GraphName);

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SD=(0|7)" << endl;

      return -1;
   }

   string SD = ((argv[1][0] == '0') ? "0" : "7");

   SetThesisStyle();

   PdfFileHelper PdfFile("AverageMassSanityCheck_" + SD + ".pdf");
   PdfFile.AddTextPage("Sanity checks for average mass plots");

   DataHelper DHFileData("SystematicsCombined_" + SD + "_Data.dh");
   DataHelper DHFileMC("SystematicsCombined_" + SD + "_MC.dh");

   string FileName = "Graphs_SD" + SD + "_Picked.root";

   TFile File(FileName.c_str());

   vector<string> DataNames(16), MC1Names(16), MC2Names(16), MC3Names(16), States(16);

   DataNames[0]  = "Data_MassData_4_1";   MC1Names[0]  = "PP6_MassData_4_1";   MC2Names[0]  = "PPHerwig_MassData_4_1";   MC3Names[0]  = "PP8_MassData_4_1";       States[0]  = "GRatio_C4_P1";
   DataNames[1]  = "Data_MassData_4_2";   MC1Names[1]  = "PP6_MassData_4_2";   MC2Names[1]  = "PPHerwig_MassData_4_2";   MC3Names[1]  = "PP8_MassData_4_2";       States[1]  = "GRatio_C4_P2";
   DataNames[2]  = "Data_MassData_4_3";   MC1Names[2]  = "PP6_MassData_4_3";   MC2Names[2]  = "PPHerwig_MassData_4_3";   MC3Names[2]  = "PP8_MassData_4_3";       States[2]  = "GRatio_C4_P3";
   DataNames[3]  = "Data_MassData_4_4";   MC1Names[3]  = "PP6_MassData_4_4";   MC2Names[3]  = "PPHerwig_MassData_4_4";   MC3Names[3]  = "PP8_MassData_4_4";       States[3]  = "GRatio_C4_P4";
   DataNames[4]  = "Data_MassData_4_1";   MC1Names[4]  = "PP6_MassData_4_1";   MC2Names[4]  = "PPHerwig_MassData_4_1";   MC3Names[4]  = "PP8_MassData_4_1";       States[4]  = "GRatio_C4_P1";
   DataNames[5]  = "Data_MassData_4_2";   MC1Names[5]  = "PP6_MassData_4_2";   MC2Names[5]  = "PPHerwig_MassData_4_2";   MC3Names[5]  = "PP8_MassData_4_2";       States[5]  = "GRatio_C4_P2";
   DataNames[6]  = "Data_MassData_4_3";   MC1Names[6]  = "PP6_MassData_4_3";   MC2Names[6]  = "PPHerwig_MassData_4_3";   MC3Names[6]  = "PP8_MassData_4_3";       States[6]  = "GRatio_C4_P3";
   DataNames[7]  = "Data_MassData_4_4";   MC1Names[7]  = "PP6_MassData_4_4";   MC2Names[7]  = "PPHerwig_MassData_4_4";   MC3Names[7]  = "PP8_MassData_4_4";       States[7]  = "GRatio_C4_P4";
   DataNames[8]  = "Data_MassData_4_1";   MC1Names[8]  = "PP6_MassData_4_1";   MC2Names[8]  = "PPHerwig_MassData_4_1";   MC3Names[8]  = "PP8_MassData_4_1";       States[8]  = "GRatio_C4_P1";
   DataNames[9]  = "Data_MassData_4_2";   MC1Names[9]  = "PP6_MassData_4_2";   MC2Names[9]  = "PPHerwig_MassData_4_2";   MC3Names[9]  = "PP8_MassData_4_2";       States[9]  = "GRatio_C4_P2";
   DataNames[10] = "Data_MassData_4_3";   MC1Names[10] = "PP6_MassData_4_3";   MC2Names[10] = "PPHerwig_MassData_4_3";   MC3Names[10] = "PP8_MassData_4_3";       States[10] = "GRatio_C4_P3";
   DataNames[11] = "Data_MassData_4_4";   MC1Names[11] = "PP6_MassData_4_4";   MC2Names[11] = "PPHerwig_MassData_4_4";   MC3Names[11] = "PP8_MassData_4_4";       States[11] = "GRatio_C4_P4";
   DataNames[12] = "Data_MassData_4_1";   MC1Names[12] = "PP6_MassData_4_1";   MC2Names[12] = "PPHerwig_MassData_4_1";   MC3Names[12] = "PP8_MassData_4_1";       States[12] = "GRatio_C4_P1";
   DataNames[13] = "Data_MassData_4_2";   MC1Names[13] = "PP6_MassData_4_2";   MC2Names[13] = "PPHerwig_MassData_4_2";   MC3Names[13] = "PP8_MassData_4_2";       States[13] = "GRatio_C4_P2";
   DataNames[14] = "Data_MassData_4_3";   MC1Names[14] = "PP6_MassData_4_3";   MC2Names[14] = "PPHerwig_MassData_4_3";   MC3Names[14] = "PP8_MassData_4_3";       States[14] = "GRatio_C4_P3";
   DataNames[15] = "Data_MassData_4_4";   MC1Names[15] = "PP6_MassData_4_4";   MC2Names[15] = "PPHerwig_MassData_4_4";   MC3Names[15] = "PP8_MassData_4_4";       States[15] = "GRatio_C4_P4";

   TGraphAsymmErrors GData, GMC1, GMC2, GMC3;
   TGraphAsymmErrors GDataSys, GMC1Sys, GMC2Sys, GMC3Sys;

   GData.SetMarkerColor(kRed + 3);
   GData.SetLineColor(kRed + 3);
   GData.SetLineWidth(2);
   GDataSys.SetMarkerColor(kRed + 3);
   GDataSys.SetLineColor(kRed + 3);
   GDataSys.SetLineWidth(2);
   GDataSys.SetFillColor(kRed);
   
   GMC1.SetMarkerColor(kBlue);
   GMC1.SetLineColor(kBlue);
   GMC1.SetLineWidth(2);
   GMC1Sys.SetMarkerColor(kBlue);
   GMC1Sys.SetLineColor(kBlue);
   GMC1Sys.SetLineWidth(2);
   GMC1Sys.SetFillColor(kBlue - 3);
   GMC1Sys.SetFillStyle(3154);
   
   GMC2.SetMarkerColor(kGreen);
   GMC2.SetLineColor(kGreen);
   GMC2.SetLineWidth(2);
   GMC2Sys.SetMarkerColor(kGreen);
   GMC2Sys.SetLineColor(kGreen);
   GMC2Sys.SetLineWidth(2);
   GMC2Sys.SetFillColor(kGreen - 3);
   GMC2Sys.SetFillStyle(3145);
   
   GMC3.SetMarkerColor(kYellow - 3);
   GMC3.SetMarkerSize(1.5);
   GMC3.SetLineColor(kYellow - 3);
   GMC3.SetLineWidth(2);
   GMC3Sys.SetMarkerColor(kYellow - 3);
   GMC3Sys.SetMarkerSize(1.5);
   GMC3Sys.SetLineColor(kYellow - 3);
   GMC3Sys.SetLineWidth(2);
   GMC3Sys.SetFillColor(kYellow + 3);
   GMC3Sys.SetFillStyle(3145);

   double Min0[] = {0.080, 0.041, 0.031, 1.501};
   double Max0[] = {0.120, 0.0539, 1.249, 3.999};
   double Min7[] = {0.050, 0.031, 0.431, 2.001};
   double Max7[] = {0.100, 0.049, 2.799, 7.999};

   double *Min = ((SD == "0") ? Min0 : Min7);
   double *Max = ((SD == "0") ? Max0 : Max7);

   for(int i = 0; i < 16; i++)
   {
      double DataAverage, DataError, DataSys;
      double MC1Average, MC1Error, MC1Sys;
      double MC2Average, MC2Error, MC2Sys;
      double MC3Average, MC3Error, MC3Sys;

      if(i >= 0 && i < 4)
      {
         DataAverage = GetAverage(File, DataNames[i]);
         DataError = GetError(File, DataNames[i]);
         DataSys = DHFileData[States[i]]["All"].GetDouble();
         MC1Average = GetAverage(File, MC1Names[i]);
         MC1Error = GetError(File, MC1Names[i]);
         MC1Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC2Average = GetAverage(File, MC2Names[i]);
         MC2Error = GetError(File, MC2Names[i]);
         MC2Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC3Average = GetAverage(File, MC3Names[i]);
         MC3Error = GetError(File, MC3Names[i]);
         MC3Sys = DHFileMC[States[i]]["All"].GetDouble();
      }
      if(i >= 4 && i < 8)
      {
         DataAverage = GetWidth(File, DataNames[i]);
         DataError = GetError(File, DataNames[i]);
         DataSys = DHFileData[States[i]]["All"].GetDouble();
         MC1Average = GetWidth(File, MC1Names[i]);
         MC1Error = GetError(File, MC1Names[i]);
         MC1Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC2Average = GetWidth(File, MC2Names[i]);
         MC2Error = GetError(File, MC2Names[i]);
         MC2Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC3Average = GetWidth(File, MC3Names[i]);
         MC3Error = GetError(File, MC3Names[i]);
         MC3Sys = DHFileMC[States[i]]["All"].GetDouble();
      }
      if(i >= 8 && i < 12)
      {
         DataAverage = GetSkewness(File, DataNames[i]);
         DataError = GetError(File, DataNames[i]);
         DataSys = DHFileData[States[i]]["All"].GetDouble();
         MC1Average = GetSkewness(File, MC1Names[i]);
         MC1Error = GetError(File, MC1Names[i]);
         MC1Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC2Average = GetSkewness(File, MC2Names[i]);
         MC2Error = GetError(File, MC2Names[i]);
         MC2Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC3Average = GetSkewness(File, MC3Names[i]);
         MC3Error = GetError(File, MC3Names[i]);
         MC3Sys = DHFileMC[States[i]]["All"].GetDouble();
      }
      if(i >= 12 && i < 16)
      {
         DataAverage = GetKurtosis(File, DataNames[i]);
         DataError = GetError(File, DataNames[i]);
         DataSys = DHFileData[States[i]]["All"].GetDouble();
         MC1Average = GetKurtosis(File, MC1Names[i]);
         MC1Error = GetError(File, MC1Names[i]);
         MC1Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC2Average = GetKurtosis(File, MC2Names[i]);
         MC2Error = GetError(File, MC2Names[i]);
         MC2Sys = DHFileMC[States[i]]["All"].GetDouble();
         MC3Average = GetKurtosis(File, MC3Names[i]);
         MC3Error = GetError(File, MC3Names[i]);
         MC3Sys = DHFileMC[States[i]]["All"].GetDouble();
      }

      DataAverage = (DataAverage - Min[i/4]) / (Max[i/4] - Min[i/4]);
      MC1Average = (MC1Average - Min[i/4]) / (Max[i/4] - Min[i/4]);
      MC2Average = (MC2Average - Min[i/4]) / (Max[i/4] - Min[i/4]);
      MC3Average = (MC3Average - Min[i/4]) / (Max[i/4] - Min[i/4]);
      DataError = DataError / (Max[i/4] - Min[i/4]);
      MC1Error = MC1Error / (Max[i/4] - Min[i/4]);
      MC2Error = MC2Error / (Max[i/4] - Min[i/4]);
      MC3Error = MC3Error / (Max[i/4] - Min[i/4]);
      DataSys = DataSys / (Max[i/4] - Min[i/4]);
      MC1Sys = MC1Sys / (Max[i/4] - Min[i/4]);
      MC2Sys = MC2Sys / (Max[i/4] - Min[i/4]);
      MC3Sys = MC3Sys / (Max[i/4] - Min[i/4]);
      
      int offset = i / 4 + 1;

      GData.SetPoint(i, i + offset + 0.5, DataAverage);
      GData.SetPointError(i, 0, 0, DataError, DataError);

      GMC1.SetPoint(i, i + offset + 0.5, MC1Average);
      GMC1.SetPointError(i, 0, 0, MC1Error, MC1Error);
      
      GMC2.SetPoint(i, i + offset + 0.5, MC2Average);
      GMC2.SetPointError(i, 0, 0, MC2Error, MC2Error);
      
      GMC3.SetPoint(i, i + offset + 0.5, MC3Average);
      GMC3.SetPointError(i, 0, 0, MC3Error, MC3Error);

      GDataSys.SetPoint(i, i + offset + 0.5, DataAverage);
      GDataSys.SetPointError(i, 0.5, 0.5, DataAverage * (DataSys - 1), DataAverage * (1 - 1 / DataSys));
      
      GMC1Sys.SetPoint(i, i + offset + 0.5, MC1Average);
      GMC1Sys.SetPointError(i, 0.5, 0.5, MC1Average * (MC1Sys - 1), MC1Average * (1 - 1 / MC1Sys));
      
      GMC2Sys.SetPoint(i, i + offset + 0.5, MC2Average);
      GMC2Sys.SetPointError(i, 0.5, 0.5, MC2Average * (MC2Sys - 1), MC2Average * (1 - 1 / MC2Sys));
      
      GMC3Sys.SetPoint(i, i + offset + 0.5, MC3Average);
      GMC3Sys.SetPointError(i, 0.5, 0.5, MC3Average * (MC3Sys - 1), MC3Average * (1 - 1 / MC3Sys));
   }

   PdfFile.AddPlot(GData, "ap");
   PdfFile.AddPlot(GMC1, "ap");
   PdfFile.AddPlot(GMC2, "ap");
   PdfFile.AddPlot(GMC3, "ap");
   PdfFile.AddPlot(GDataSys, "a2");
   PdfFile.AddPlot(GMC1Sys, "a2");
   PdfFile.AddPlot(GMC2Sys, "a2");
   PdfFile.AddPlot(GMC3Sys, "a2");

   TCanvas C;

   TLatex Text;
   Text.SetTextFont(42);
   Text.SetTextSize(0.025);
   Text.SetTextAlign(22);
   Text.SetNDC();

   TH2D HWorld1("HWorld1", ";p_{T,jet} (GeV);Moments", 19, 1, 20, 100, 0, 1);
   HWorld1.SetStats(0);
   
   HWorld1.GetXaxis()->SetTickLength(0.02);
   HWorld1.GetXaxis()->SetTitleOffset(1.55);

   HWorld1.GetYaxis()->SetTickLength(0);
   HWorld1.GetYaxis()->SetLabelSize(0);
   HWorld1.GetYaxis()->SetTitleOffset(1.40);
   
   HWorld1.GetXaxis()->SetTitleSize(0.030);
   HWorld1.GetYaxis()->SetTitleSize(0.030);

   HWorld1.GetXaxis()->SetBinLabel(1,  "140-160");
   HWorld1.GetXaxis()->SetBinLabel(2,  "160-180");
   HWorld1.GetXaxis()->SetBinLabel(3,  "180-200");
   HWorld1.GetXaxis()->SetBinLabel(4,  "200-300");
   HWorld1.GetXaxis()->SetBinLabel(6,  "140-160");
   HWorld1.GetXaxis()->SetBinLabel(7,  "160-180");
   HWorld1.GetXaxis()->SetBinLabel(8,  "180-200");
   HWorld1.GetXaxis()->SetBinLabel(9,  "200-300");
   HWorld1.GetXaxis()->SetBinLabel(11, "140-160");
   HWorld1.GetXaxis()->SetBinLabel(12, "160-180");
   HWorld1.GetXaxis()->SetBinLabel(13, "180-200");
   HWorld1.GetXaxis()->SetBinLabel(14, "200-300");
   HWorld1.GetXaxis()->SetBinLabel(16, "140-160");
   HWorld1.GetXaxis()->SetBinLabel(17, "160-180");
   HWorld1.GetXaxis()->SetBinLabel(18, "180-200");
   HWorld1.GetXaxis()->SetBinLabel(19, "200-300");

   TGraph G;
   G.SetPoint(0, 5, -10);
   G.SetPoint(1, 5, 10);
   G.SetPoint(2, 10, 10);
   G.SetPoint(3, 10, -10);
   G.SetPoint(4, 15, -10);
   G.SetPoint(5, 15, 10);

   TGraph G2;
   G2.SetPoint(0, 16, (3 - Min[3]) / (Max[3] - Min[3]));
   G2.SetPoint(1, 20, (3 - Min[3]) / (Max[3] - Min[3]));
   G2.SetLineStyle(kDashed);

   double Location[4] = {2, 7, 12, 17};
   for(int i = 0; i < 4; i++)
      Location[i] = (Location[i] / 19 * 0.8 + 0.1) / 1.05 + 0.005;

   HWorld1.Draw("axis");
   Text.SetTextAlign(22);
   Text.DrawLatex(Location[0], 0.86, "Mean");
   Text.DrawLatex(Location[1], 0.86, "Width");
   Text.DrawLatex(Location[2], 0.86, "Skewness");
   Text.DrawLatex(Location[3], 0.86, "Kurtosis");
   Text.DrawLatex(Location[0], 0.83, "");
   Text.DrawLatex(Location[1], 0.83, "");
   Text.DrawLatex(Location[2], 0.83, "");
   Text.DrawLatex(Location[3], 0.83, "");

   Text.SetTextAlign(22);
   Text.DrawLatex(Location[0], 0.18, "Soft drop");
   if(SD == "0")
      Text.DrawLatex(Location[0], 0.15, "(0.1, 0.0)");
   else
      Text.DrawLatex(Location[0], 0.15, "(0.5, 1.5)");

   Text.DrawLatex(Location[1], 0.21, "anti-kt");
   Text.DrawLatex(Location[1], 0.18, "R = 0.4");
   Text.DrawLatex(Location[1], 0.15, "#Delta R_{1,2} > 0.1");
   
   Text.DrawLatex(Location[2], 0.15, "|#eta_{jet}| < 1.3");

   Text.SetTextAlign(11);
   Text.DrawLatex(0.10, 0.91, "CMS Preliminary");

   Text.SetTextAlign(31);
   Text.DrawLatex(0.90 / 1.05, 0.91, "#sqrt{s_{NN}} = 5.02 TeV, pp 28 pb^{-1}");

   // GDataSys.Draw("2");
   // GMC1Sys.Draw("2");
   // GMC2Sys.Draw("2");
   // GMC3Sys.Draw("2");
   GMC3.Draw("p");
   GData.Draw("p");
   GMC1.Draw("p");
   GMC2.Draw("p");
   G.Draw("l");
   G2.Draw("l");
   HWorld1.Draw("axis same");

   TGaxis Axis1(1.0, 0.0, 1.0, 1.0, Min[0], Max[0], 510, "S");
   TGaxis Axis2(6.0, 0.0, 6.0, 1.0, Min[1], Max[1], 510, "S");
   TGaxis Axis3(11.0, 0.0, 11.0, 1.0, Min[2], Max[2], 510, "S");
   TGaxis Axis4(16.0, 0.0, 16.0, 1.0, Min[3], Max[3], 510, "S");

   Axis1.SetLabelSize(0.018);
   Axis2.SetLabelSize(0.018);
   Axis3.SetLabelSize(0.018);
   Axis4.SetLabelSize(0.018);

   Axis1.SetLabelFont(42);
   Axis2.SetLabelFont(42);
   Axis3.SetLabelFont(42);
   Axis4.SetLabelFont(42);

   Axis1.SetTickSize(0.018);
   Axis2.SetTickSize(0.018);
   Axis3.SetTickSize(0.018);
   Axis4.SetTickSize(0.018);

   Axis1.Draw();
   Axis2.Draw();
   Axis3.Draw();
   Axis4.Draw();

   C.cd(0)->SetTicks(0, 1);

   TLegend Legend(0.55, 0.80, 0.80, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.030);
   Legend.SetBorderSize(1);
   Legend.AddEntry(&GDataSys, "Data", "lp");
   Legend.AddEntry(&GMC1Sys, "PYTHIA 6", "lp");
   Legend.AddEntry(&GMC2Sys, "HERWIG++", "lp");
   Legend.AddEntry(&GMC3Sys, "PYTHIA 8", "lp");
   Legend.Draw();

   C.SaveAs(("Plots/AverageMassPlot_" + SD + ".png").c_str());
   C.SaveAs(("Plots/AverageMassPlot_" + SD + ".C").c_str());
   C.SaveAs(("Plots/AverageMassPlot_" + SD + ".eps").c_str());
   C.SaveAs(("PDFPlots/AverageMassPlot_" + SD + ".pdf").c_str());

   PdfFile.AddCanvas(C);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetAverage(TFile &F, string GraphName)
{
   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(GraphName.c_str());

   double TotalXY = 0;
   double TotalY = 0;

   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      G->GetPoint(i, x, y);

      double xl, xr;
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      double B = xl + xr;

      if(x == x && y == y)
      {
         TotalXY = TotalXY + x * y * B;
         TotalY = TotalY + y * B;
      }
   }

   return TotalXY / TotalY;
}

double GetError(TFile &F, string GraphName)
{
   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(GraphName.c_str());

   double TotalE2 = 0;
   double TotalXXY = 0;
   double TotalXY = 0;
   double TotalY = 0;

   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y, ey;
      G->GetPoint(i, x, y);
      ey = G->GetErrorYlow(i);
      
      double xl, xr;
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      double B = xl + xr;

      if(x == x && y == y)
      {
         TotalE2 = TotalE2 + ey * ey * B * B;
         TotalXXY = TotalXXY + x * x * y * B;
         TotalXY = TotalXY + x * y * B;
         TotalY = TotalY + y * B;
      }
   }

   double Mean = TotalXY / TotalY;
   double Variance = (TotalXXY - TotalY * Mean * Mean) / TotalY;
   return sqrt(Variance) * sqrt(TotalE2) / TotalY;
}

double GetWidth(TFile &F, string GraphName)
{
   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(GraphName.c_str());

   double TotalXXY = 0;
   double TotalXY = 0;
   double TotalY = 0;

   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      G->GetPoint(i, x, y);

      double xl, xr;
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      double B = xl + xr;

      if(x == x && y == y)
      {
         TotalXXY = TotalXXY + x * x * y * B;
         TotalXY = TotalXY + x * y * B;
         TotalY = TotalY + y * B;
      }
   }

   double Mean = TotalXY / TotalY;
   double Variance = (TotalXXY - TotalY * Mean * Mean) / TotalY;

   return sqrt(Variance);
}

double GetSkewness(TFile &F, string GraphName)
{
   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(GraphName.c_str());

   double TotalXXXY = 0;
   double TotalXXY = 0;
   double TotalXY = 0;
   double TotalY = 0;

   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      G->GetPoint(i, x, y);

      double xl, xr;
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      double B = xl + xr;

      if(x == x && y == y)
      {
         TotalXXXY = TotalXXXY + x * x * x * y * B;
         TotalXXY = TotalXXY + x * x * y * B;
         TotalXY = TotalXY + x * y * B;
         TotalY = TotalY + y * B;
      }
   }

   double Mean = TotalXY / TotalY;
   double Variance = (TotalXXY - TotalY * Mean * Mean) / TotalY;
   double Moment3 = (TotalXXXY - 3 * TotalXXY * Mean + 2 * TotalY * Mean * Mean * Mean) / TotalY;

   return Moment3 / pow(Variance, 1.5);
}

double GetKurtosis(TFile &F, string GraphName)
{
   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(GraphName.c_str());

   double TotalXXXXY = 0;
   double TotalXXXY = 0;
   double TotalXXY = 0;
   double TotalXY = 0;
   double TotalY = 0;

   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      G->GetPoint(i, x, y);

      double xl, xr;
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      double B = xl + xr;

      if(x == x && y == y)
      {
         TotalXXXXY = TotalXXXXY + x * x * x * x * y * B;
         TotalXXXY = TotalXXXY + x * x * x * y * B;
         TotalXXY = TotalXXY + x * x * y * B;
         TotalXY = TotalXY + x * y * B;
         TotalY = TotalY + y * B;
      }
   }

   double Mean = TotalXY / TotalY;
   double Variance = (TotalXXY - TotalY * Mean * Mean) / TotalY;
   double Moment4 = (TotalXXXXY - 4 * TotalXXXY * Mean + 6 * TotalXXY * Mean * Mean - 3 * TotalY * Mean * Mean * Mean * Mean) / TotalY;

   return Moment4 / Variance / Variance;
}





