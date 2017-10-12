#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "DataHelper.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[]);
double GetAverage(TFile &F, string GraphName);
double GetError(TFile &F, string GraphName);

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " SD=(0|7) Data=(Y|N)" << endl;

      return -1;
   }

   string SD = ((argv[1][0] == '0') ? "0" : "7");
   string Data = ((argv[2][0] == 'Y') ? "Data" : "MC");

   SetThesisStyle();

   PdfFileHelper PdfFile("WidthMassSanityCheck_" + SD + "_" + Data + ".pdf");
   PdfFile.AddTextPage("Sanity checks for width mass plots");

   DataHelper DHFileData("SystematicsCombined_" + SD + "_Data.dh");
   DataHelper DHFileSmear("SystematicsCombined_" + SD + "_MC.dh");

   string FileName = "Graphs_SD" + SD;
   if(Data == "Data")
      FileName = FileName + "_DataPicked.root";
   else
      FileName = FileName + "_MC.root";

   TFile File(FileName.c_str());

   vector<string> DataNames(16), SmearNames(16), States(16);

   DataNames[0]  = "MassData_0_1";   SmearNames[0]  = "MassSmear_0_1";   States[0]  = "GRatio_C0_P1";
   DataNames[1]  = "MassData_0_2";   SmearNames[1]  = "MassSmear_0_2";   States[1]  = "GRatio_C0_P2";
   DataNames[2]  = "MassData_0_3";   SmearNames[2]  = "MassSmear_0_3";   States[2]  = "GRatio_C0_P3";
   DataNames[3]  = "MassData_0_4";   SmearNames[3]  = "MassSmear_0_4";   States[3]  = "GRatio_C0_P4";
   DataNames[4]  = "MassData_1_1";   SmearNames[4]  = "MassSmear_1_1";   States[4]  = "GRatio_C1_P1";
   DataNames[5]  = "MassData_1_2";   SmearNames[5]  = "MassSmear_1_2";   States[5]  = "GRatio_C1_P2";
   DataNames[6]  = "MassData_1_3";   SmearNames[6]  = "MassSmear_1_3";   States[6]  = "GRatio_C1_P3";
   DataNames[7]  = "MassData_1_4";   SmearNames[7]  = "MassSmear_1_4";   States[7]  = "GRatio_C1_P4";
   DataNames[8]  = "MassData_2_1";   SmearNames[8]  = "MassSmear_2_1";   States[8]  = "GRatio_C2_P1";
   DataNames[9]  = "MassData_2_2";   SmearNames[9]  = "MassSmear_2_2";   States[9]  = "GRatio_C2_P2";
   DataNames[10] = "MassData_2_3";   SmearNames[10] = "MassSmear_2_3";   States[10] = "GRatio_C2_P3";
   DataNames[11] = "MassData_2_4";   SmearNames[11] = "MassSmear_2_4";   States[11] = "GRatio_C2_P4";
   DataNames[12] = "MassData_3_1";   SmearNames[12] = "MassSmear_3_1";   States[12] = "GRatio_C3_P1";
   DataNames[13] = "MassData_3_2";   SmearNames[13] = "MassSmear_3_2";   States[13] = "GRatio_C3_P2";
   DataNames[14] = "MassData_3_3";   SmearNames[14] = "MassSmear_3_3";   States[14] = "GRatio_C3_P3";
   DataNames[15] = "MassData_3_4";   SmearNames[15] = "MassSmear_3_4";   States[15] = "GRatio_C3_P4";

   TGraphAsymmErrors GData, GSmear, GRatio;
   TGraphAsymmErrors GDataSys, GSmearSys, GRatioSys;

   GData.SetMarkerColor(kRed + 3);
   GData.SetLineColor(kRed + 3);
   GData.SetLineWidth(2);
   GDataSys.SetMarkerColor(kRed + 3);
   GDataSys.SetLineColor(kRed + 3);
   GDataSys.SetLineWidth(2);
   GDataSys.SetFillColor(kRed);
   
   GSmear.SetMarkerColor(kBlue);
   GSmear.SetLineColor(kBlue);
   GSmear.SetLineWidth(2);
   GSmearSys.SetMarkerColor(kBlue);
   GSmearSys.SetLineColor(kBlue);
   GSmearSys.SetLineWidth(2);
   GSmearSys.SetFillColor(kBlue - 3);
   GSmearSys.SetFillStyle(3154);

   for(int i = 0; i < 16; i++)
   {
      double DataAverage, DataError, DataSys;
      double SmearAverage, SmearError, SmearSys;

      DataAverage = GetAverage(File, DataNames[i]);
      DataError = GetError(File, DataNames[i]);
      DataSys = DHFileData[States[i]]["AllWidth"].GetDouble();
      SmearAverage = GetAverage(File, SmearNames[i]);
      SmearError = GetError(File, SmearNames[i]);
      SmearSys = DHFileSmear[States[i]]["AllWidth"].GetDouble();
      
      GData.SetPoint(i, i + 0.5, DataAverage);
      GData.SetPointError(i, 0, 0, DataError, DataError);

      GSmear.SetPoint(i, i + 0.5, SmearAverage);
      GSmear.SetPointError(i, 0, 0, SmearError, SmearError);

      GRatio.SetPoint(i, i + 0.5, DataAverage / SmearAverage);
      GRatio.SetPointError(i, 0, 0, DataAverage / SmearAverage * sqrt(DataError * DataError / DataAverage / DataAverage + SmearError * SmearError / SmearAverage / SmearAverage), DataAverage / SmearAverage * sqrt(DataError * DataError / DataAverage / DataAverage + SmearError * SmearError / SmearAverage / SmearAverage));

      GDataSys.SetPoint(i, i + 0.5, DataAverage);
      GDataSys.SetPointError(i, 0.5, 0.5, DataAverage * (DataSys - 1), DataAverage * (1 - 1 / DataSys));
      
      GSmearSys.SetPoint(i, i + 0.5, SmearAverage);
      GSmearSys.SetPointError(i, 0.5, 0.5, SmearAverage * (SmearSys - 1), SmearAverage * (1 - 1 / SmearSys));

      GRatioSys.SetPoint(i, i + 0.5, DataAverage / SmearAverage);
      GRatioSys.SetPointError(i, 0, 0, DataAverage / SmearAverage * sqrt((DataSys - 1) * (DataSys - 1) + (SmearSys - 1) * (SmearSys - 1)), DataAverage / SmearAverage * sqrt((1 - 1 / DataSys) * (1 - 1 / DataSys) + (1 - 1 / SmearSys) * (1 - 1 / SmearSys)));
   }

   PdfFile.AddPlot(GData, "ap");
   PdfFile.AddPlot(GSmear, "ap");
   PdfFile.AddPlot(GDataSys, "a2");
   PdfFile.AddPlot(GSmearSys, "a2");

   TCanvas C;

   double Min = ((SD == "0") ? 0.030 : 0.025);
   double Max = ((SD == "0") ? 0.070 : 0.065);

   TLatex Text;
   Text.SetTextFont(42);
   Text.SetTextSize(0.025);
   Text.SetTextAlign(22);
   Text.SetNDC();

   TH2D HWorld1("HWorld1", ";p_{T,jet} (GeV);#sigma(M_{g}/p_{T})", 16, 0, 16, 100, Min, Max);
   HWorld1.SetStats(0);
   HWorld1.GetXaxis()->SetTickLength(0.02);
   HWorld1.GetXaxis()->SetTitleOffset(1.35);
   HWorld1.GetYaxis()->SetTitleOffset(1.40);

   HWorld1.GetXaxis()->SetBinLabel(1,  "140-160");
   HWorld1.GetXaxis()->SetBinLabel(2,  "160-180");
   HWorld1.GetXaxis()->SetBinLabel(3,  "180-200");
   HWorld1.GetXaxis()->SetBinLabel(4,  "200-300");
   HWorld1.GetXaxis()->SetBinLabel(5,  "140-160");
   HWorld1.GetXaxis()->SetBinLabel(6,  "160-180");
   HWorld1.GetXaxis()->SetBinLabel(7,  "180-200");
   HWorld1.GetXaxis()->SetBinLabel(8,  "200-300");
   HWorld1.GetXaxis()->SetBinLabel(9,  "140-160");
   HWorld1.GetXaxis()->SetBinLabel(10, "160-180");
   HWorld1.GetXaxis()->SetBinLabel(11, "180-200");
   HWorld1.GetXaxis()->SetBinLabel(12, "200-300");
   HWorld1.GetXaxis()->SetBinLabel(13, "140-160");
   HWorld1.GetXaxis()->SetBinLabel(14, "160-180");
   HWorld1.GetXaxis()->SetBinLabel(15, "180-200");
   HWorld1.GetXaxis()->SetBinLabel(16, "200-300");

   TGraph G;
   G.SetPoint(0, 4, -10);
   G.SetPoint(1, 4, 10);
   G.SetPoint(2, 8, 10);
   G.SetPoint(3, 8, -10);
   G.SetPoint(4, 12, -10);
   G.SetPoint(5, 12, 10);
   G.SetLineStyle(kDashed);

   HWorld1.Draw("axis");
   Text.SetTextAlign(22);
   Text.DrawLatex(0.2 / 1.05, 0.86, "Centrality");
   Text.DrawLatex(0.4 / 1.05, 0.86, "Centrality");
   Text.DrawLatex(0.6 / 1.05, 0.86, "Centrality");
   Text.DrawLatex(0.8 / 1.05, 0.86, "Centrality");
   Text.DrawLatex(0.2 / 1.05, 0.83, "0% - 10%");
   Text.DrawLatex(0.4 / 1.05, 0.83, "10% - 30%");
   Text.DrawLatex(0.6 / 1.05, 0.83, "30% - 50%");
   Text.DrawLatex(0.8 / 1.05, 0.83, "50% - 80%");

   Text.SetTextAlign(22);
   Text.DrawLatex(0.2 / 1.05, 0.18, "Soft drop");
   if(SD == "0")
      Text.DrawLatex(0.2 / 1.05, 0.15, "(0.1, 0.0)");
   else
      Text.DrawLatex(0.2 / 1.05, 0.15, "(0.5, 1.5)");

   Text.DrawLatex(0.4 / 1.05, 0.18, "anti-kt R = 0.4");
   Text.DrawLatex(0.4 / 1.05, 0.15, "#Delta R_{1,2} > 0.1");
   
   Text.DrawLatex(0.6 / 1.05, 0.15, "|#eta_{jet}| < 1.3");

   Text.SetTextAlign(11);
   if(Data == "Data")
      Text.DrawLatex(0.10, 0.91, "CMS Preliminary");
   else
      Text.DrawLatex(0.10, 0.91, "CMS Simulation");

   Text.SetTextAlign(31);
   if(Data == "Data")
      Text.DrawLatex(0.90 / 1.05, 0.91, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp 28 pb^{-1}");

   GDataSys.Draw("2");
   GSmearSys.Draw("2");
   GData.Draw("p");
   GSmear.Draw("p");
   G.Draw("l");
   HWorld1.Draw("axis same");

   TLegend Legend(0.5, 0.75, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(1);
   if(Data == "Data")
      Legend.AddEntry(&GDataSys, "PbPb", "lpf");
   else
      Legend.AddEntry(&GDataSys, "Embedded pp", "lpf");
   Legend.AddEntry(&GSmearSys, "Smeared pp", "lpf");
   Legend.Draw();

   C.cd(0)->SetTicks(0, 1);

   C.SaveAs(("Plots/WidthMassPlot_" + SD + "_" + Data + ".png").c_str());
   C.SaveAs(("Plots/WidthMassPlot_" + SD + "_" + Data + ".C").c_str());
   C.SaveAs(("Plots/WidthMassPlot_" + SD + "_" + Data + ".eps").c_str());
   C.SaveAs(("PDFPlots/WidthMassPlot_" + SD + "_" + Data + ".pdf").c_str());

   PdfFile.AddCanvas(C);

   PdfFile.AddPlot(GRatio, "ap");
   PdfFile.AddPlot(GRatioSys, "a2");

   GRatio.Draw("ap");
   GRatioSys.Draw("2");
   G.Draw("l");

   PdfFile.AddCanvas(C);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetAverage(TFile &F, string GraphName)
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
   return sqrt(Variance);
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



