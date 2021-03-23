#include <iostream>
#include <vector>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
TGraphAsymmErrors TranscribeEtaScan(DataHelper &DHFile, string Prefix, int RBin, int CBin, bool DoError);
TGraphAsymmErrors TranscribeDPhiScan(DataHelper &DHFile, string Prefix, int RBin, int CBin, int EtaBin, bool DoError);
double FindMax(TGraphAsymmErrors &G);
double FindMin(TGraphAsymmErrors &G);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   int DefaultColor[7] = {-1, -1, -1, -1, -1, -1, -1};
   DefaultColor[0] = TColor::GetColor("#E74C3C");
   DefaultColor[1] = TColor::GetColor("#3498DB");
   DefaultColor[2] = TColor::GetColor("#F1C40F");
   DefaultColor[3] = TColor::GetColor("#2ECC71");
   DefaultColor[4] = TColor::GetColor("#7F7F7F");
   DefaultColor[5] = TColor::GetColor("#8E44AD");
   DefaultColor[6] = kMagenta;

   CommandLine CL(argc, argv);
   string DHFileNameMC      = CL.Get("MC");
   string DHFileNameData    = CL.Get("Data");
   string Output            = CL.Get("Output");
   bool DoError             = CL.GetBool("DoError", false);

   DataHelper DHFileMC(DHFileNameMC);
   DataHelper DHFileData(DHFileNameData);

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Random cone plots");

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   
   // Do eta scan plots
   {
      vector<double> Centrality{0.0, 0.1, 0.3, 0.5, 0.8};

      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         for(int iC = 0; iC < 4; iC++)
         {
            TGraphAsymmErrors GMC       = TranscribeEtaScan(DHFileMC, "RhoEta", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi0   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F0", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi1   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F1", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi2   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F2", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi3   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F3", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi4   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F4", iR, iC, DoError);
            TGraphAsymmErrors GMCPhi5   = TranscribeEtaScan(DHFileMC, "RhoPhiEta_F5", iR, iC, DoError);
            TGraphAsymmErrors GData     = TranscribeEtaScan(DHFileData, "RhoEta", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi0 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F0", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi1 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F1", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi2 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F2", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi3 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F3", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi4 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F4", iR, iC, DoError);
            TGraphAsymmErrors GDataPhi5 = TranscribeEtaScan(DHFileData, "RhoPhiEta_F5", iR, iC, DoError);

            GMCPhi0.SetMarkerColor(DefaultColor[0]);
            GMCPhi0.SetLineColor(DefaultColor[0]);
            GMCPhi1.SetMarkerColor(DefaultColor[1]);
            GMCPhi1.SetLineColor(DefaultColor[1]);
            GMCPhi2.SetMarkerColor(DefaultColor[2]);
            GMCPhi2.SetLineColor(DefaultColor[2]);
            GMCPhi3.SetMarkerColor(DefaultColor[3]);
            GMCPhi3.SetLineColor(DefaultColor[3]);
            GMCPhi4.SetMarkerColor(DefaultColor[4]);
            GMCPhi4.SetLineColor(DefaultColor[4]);
            GMCPhi5.SetMarkerColor(DefaultColor[5]);
            GMCPhi5.SetLineColor(DefaultColor[5]);
            GDataPhi0.SetMarkerColor(DefaultColor[0]);
            GDataPhi0.SetLineColor(DefaultColor[0]);
            GDataPhi1.SetMarkerColor(DefaultColor[1]);
            GDataPhi1.SetLineColor(DefaultColor[1]);
            GDataPhi2.SetMarkerColor(DefaultColor[2]);
            GDataPhi2.SetLineColor(DefaultColor[2]);
            GDataPhi3.SetMarkerColor(DefaultColor[3]);
            GDataPhi3.SetLineColor(DefaultColor[3]);
            GDataPhi4.SetMarkerColor(DefaultColor[4]);
            GDataPhi4.SetLineColor(DefaultColor[4]);
            GDataPhi5.SetMarkerColor(DefaultColor[5]);
            GDataPhi5.SetLineColor(DefaultColor[5]);

            double Max = FindMax(GMC);
            Max = max(Max, FindMax(GMCPhi0));
            Max = max(Max, FindMax(GMCPhi1));
            Max = max(Max, FindMax(GMCPhi2));
            Max = max(Max, FindMax(GMCPhi3));
            Max = max(Max, FindMax(GMCPhi4));
            Max = max(Max, FindMax(GMCPhi5));
            Max = max(Max, FindMax(GData));
            Max = max(Max, FindMax(GDataPhi0));
            Max = max(Max, FindMax(GDataPhi1));
            Max = max(Max, FindMax(GDataPhi2));
            Max = max(Max, FindMax(GDataPhi3));
            Max = max(Max, FindMax(GDataPhi4));
            Max = max(Max, FindMax(GDataPhi5));

            double Min = FindMin(GMC);
            Min = min(Min, FindMin(GMCPhi0));
            Min = min(Min, FindMin(GMCPhi1));
            Min = min(Min, FindMin(GMCPhi2));
            Min = min(Min, FindMin(GMCPhi3));
            Min = min(Min, FindMin(GMCPhi4));
            Min = min(Min, FindMin(GMCPhi5));
            Min = min(Min, FindMin(GData));
            Min = min(Min, FindMin(GDataPhi0));
            Min = min(Min, FindMin(GDataPhi1));
            Min = min(Min, FindMin(GDataPhi2));
            Min = min(Min, FindMin(GDataPhi3));
            Min = min(Min, FindMin(GDataPhi4));
            Min = min(Min, FindMin(GDataPhi5));

            double Distance = Max - Min;

            TCanvas Canvas;

            TH2D HWorld("HWorld", "", 100, 0, 3, 100, Min - Distance * 0.8, Max + Distance * 0.05);
            HWorld.SetTitle(Form("Centrality: [%d%, %d%], R = %.02f",
               int(Centrality[iC] * 100), int(Centrality[iC+1] * 100), Radius[iR]));
            HWorld.GetXaxis()->SetTitle("|#eta|");
            HWorld.GetYaxis()->SetTitle("#sigma");
            HWorld.SetStats(0);

            TLegend LegendMC(0.15, 0.15, 0.35, 0.45);
            LegendMC.SetTextFont(42);
            LegendMC.SetTextSize(0.025);
            LegendMC.SetFillStyle(0);
            LegendMC.SetBorderSize(0);
            LegendMC.AddEntry(&GMC, "MC (no #phi)", "lp");
            LegendMC.AddEntry(&GMCPhi0, "MC (#phi-modulated, |#eta| < 1.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendMC.AddEntry(&GMCPhi1, "MC (#phi-modulated, |#eta| < 1.5, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendMC.AddEntry(&GMCPhi2, "MC (#phi-modulated, |#eta| < 2.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendMC.AddEntry(&GMCPhi3, "MC (#phi-modulated, |#eta| < 2.5, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendMC.AddEntry(&GMCPhi4, "MC (#phi-modulated, |#eta| < 3.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendMC.AddEntry(&GMCPhi5, "MC (#phi-modulated, |#eta| < 1.0, p_{T} = 1.0-3.0 GeV)", "lp");

            TLegend LegendData(0.15, 0.15, 0.35, 0.45);
            LegendData.SetTextFont(42);
            LegendData.SetTextSize(0.025);
            LegendData.SetFillStyle(0);
            LegendData.SetBorderSize(0);
            LegendData.AddEntry(&GData, "Data (no #phi)", "lp");
            LegendData.AddEntry(&GDataPhi0, "Data (#phi-modulated, |#eta| < 1.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendData.AddEntry(&GDataPhi1, "Data (#phi-modulated, |#eta| < 1.5, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendData.AddEntry(&GDataPhi2, "Data (#phi-modulated, |#eta| < 2.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendData.AddEntry(&GDataPhi3, "Data (#phi-modulated, |#eta| < 2.5, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendData.AddEntry(&GDataPhi4, "Data (#phi-modulated, |#eta| < 3.0, p_{T} = 0.3-3.0 GeV)", "lp");
            LegendData.AddEntry(&GDataPhi5, "Data (#phi-modulated, |#eta| < 1.0, p_{T} = 1.0-3.0 GeV)", "lp");

            HWorld.Draw("axis");
            if(DoError == true)
            {
               GMC.Draw("pl");
               GMCPhi0.Draw("pl");
               GMCPhi1.Draw("p");
               GMCPhi2.Draw("p");
               GMCPhi3.Draw("p");
               GMCPhi4.Draw("pl");
               GMCPhi5.Draw("p");
            }
            else
            {
               GMC.Draw("pl");
               GMCPhi0.Draw("pl");
               GMCPhi1.Draw("pl");
               GMCPhi2.Draw("pl");
               GMCPhi3.Draw("pl");
               GMCPhi4.Draw("pl");
               GMCPhi5.Draw("pl");
            }
            LegendMC.Draw();

            PdfFile.AddCanvas(Canvas);

            HWorld.Draw("axis");
            if(DoError == true)
            {
               GData.Draw("pl");
               GDataPhi0.Draw("pl");
               GDataPhi1.Draw("p");
               GDataPhi2.Draw("p");
               GDataPhi3.Draw("p");
               GDataPhi4.Draw("pl");
               GDataPhi5.Draw("p");
            }
            else
            {
               GData.Draw("pl");
               GDataPhi0.Draw("pl");
               GDataPhi1.Draw("pl");
               GDataPhi2.Draw("pl");
               GDataPhi3.Draw("pl");
               GDataPhi4.Draw("pl");
               GDataPhi5.Draw("pl");
            }
            LegendData.Draw();

            PdfFile.AddCanvas(Canvas);
         }
      }
   }

   // Do phi scan plots
   {
      vector<double> Centrality{0.0, 0.1, 0.3, 0.5};
      vector<double> EtaBins{0.0, 1.0, 2.0, 2.5, 3.0};

      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         for(int iC = 0; iC < 3; iC++)
         {
            for(int iEta = 0; iEta < 4; iEta++)
            {
               TGraphAsymmErrors GMC       = TranscribeDPhiScan(DHFileMC, "RhoDPhi", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi0   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F0", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi1   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F1", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi2   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F2", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi3   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F3", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi4   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F4", iR, iC, iEta, DoError);
               TGraphAsymmErrors GMCPhi5   = TranscribeDPhiScan(DHFileMC, "RhoPhiDPhi_F5", iR, iC, iEta, DoError);
               TGraphAsymmErrors GData     = TranscribeDPhiScan(DHFileData, "RhoDPhi", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi0 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F0", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi1 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F1", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi2 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F2", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi3 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F3", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi4 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F4", iR, iC, iEta, DoError);
               TGraphAsymmErrors GDataPhi5 = TranscribeDPhiScan(DHFileData, "RhoPhiDPhi_F5", iR, iC, iEta, DoError);

               GMCPhi0.SetMarkerColor(DefaultColor[0]);
               GMCPhi0.SetLineColor(DefaultColor[0]);
               GMCPhi1.SetMarkerColor(DefaultColor[1]);
               GMCPhi1.SetLineColor(DefaultColor[1]);
               GMCPhi2.SetMarkerColor(DefaultColor[2]);
               GMCPhi2.SetLineColor(DefaultColor[2]);
               GMCPhi3.SetMarkerColor(DefaultColor[3]);
               GMCPhi3.SetLineColor(DefaultColor[3]);
               GMCPhi4.SetMarkerColor(DefaultColor[4]);
               GMCPhi4.SetLineColor(DefaultColor[4]);
               GMCPhi5.SetMarkerColor(DefaultColor[5]);
               GMCPhi5.SetLineColor(DefaultColor[5]);
               GDataPhi0.SetMarkerColor(DefaultColor[0]);
               GDataPhi0.SetLineColor(DefaultColor[0]);
               GDataPhi1.SetMarkerColor(DefaultColor[1]);
               GDataPhi1.SetLineColor(DefaultColor[1]);
               GDataPhi2.SetMarkerColor(DefaultColor[2]);
               GDataPhi2.SetLineColor(DefaultColor[2]);
               GDataPhi3.SetMarkerColor(DefaultColor[3]);
               GDataPhi3.SetLineColor(DefaultColor[3]);
               GDataPhi4.SetMarkerColor(DefaultColor[4]);
               GDataPhi4.SetLineColor(DefaultColor[4]);
               GDataPhi5.SetMarkerColor(DefaultColor[5]);
               GDataPhi5.SetLineColor(DefaultColor[5]);

               double Max = FindMax(GMC);
               Max = max(Max, FindMax(GMCPhi0));
               Max = max(Max, FindMax(GMCPhi1));
               Max = max(Max, FindMax(GMCPhi2));
               Max = max(Max, FindMax(GMCPhi3));
               Max = max(Max, FindMax(GMCPhi4));
               Max = max(Max, FindMax(GMCPhi5));
               Max = max(Max, FindMax(GData));
               Max = max(Max, FindMax(GDataPhi0));
               Max = max(Max, FindMax(GDataPhi1));
               Max = max(Max, FindMax(GDataPhi2));
               Max = max(Max, FindMax(GDataPhi3));
               Max = max(Max, FindMax(GDataPhi4));
               Max = max(Max, FindMax(GDataPhi5));

               double Min = FindMin(GMC);
               Min = min(Min, FindMin(GMCPhi0));
               Min = min(Min, FindMin(GMCPhi1));
               Min = min(Min, FindMin(GMCPhi2));
               Min = min(Min, FindMin(GMCPhi3));
               Min = min(Min, FindMin(GMCPhi4));
               Min = min(Min, FindMin(GMCPhi5));
               Min = min(Min, FindMin(GData));
               Min = min(Min, FindMin(GDataPhi0));
               Min = min(Min, FindMin(GDataPhi1));
               Min = min(Min, FindMin(GDataPhi2));
               Min = min(Min, FindMin(GDataPhi3));
               Min = min(Min, FindMin(GDataPhi4));
               Min = min(Min, FindMin(GDataPhi5));

               if(Min >= Max)
                  continue;

               double Distance = Max - Min;

               TCanvas Canvas;

               TH2D HWorld("HWorld", "", 100, 0, M_PI, 100, Min - Distance * 0.8, Max + Distance * 0.05);
               HWorld.SetTitle(Form("Centrality: [%d%, %d%], R = %.02f, Eta: [%.03f, %.03f]",
                  int(Centrality[iC] * 100), int(Centrality[iC+1] * 100), Radius[iR], EtaBins[iEta], EtaBins[iEta+1]));
               HWorld.GetXaxis()->SetTitle("|#Delta#phi_{2}|");
               HWorld.GetYaxis()->SetTitle("#sigma");
               HWorld.SetStats(0);

               TLegend LegendMC(0.15, 0.15, 0.35, 0.45);
               LegendMC.SetTextFont(42);
               LegendMC.SetTextSize(0.025);
               LegendMC.SetFillStyle(0);
               LegendMC.SetBorderSize(0);
               LegendMC.AddEntry(&GMC, "MC (no #phi)", "lp");
               LegendMC.AddEntry(&GMCPhi0, "MC (#phi-modulated, |#eta| < 1.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendMC.AddEntry(&GMCPhi1, "MC (#phi-modulated, |#eta| < 1.5, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendMC.AddEntry(&GMCPhi2, "MC (#phi-modulated, |#eta| < 2.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendMC.AddEntry(&GMCPhi3, "MC (#phi-modulated, |#eta| < 2.5, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendMC.AddEntry(&GMCPhi4, "MC (#phi-modulated, |#eta| < 3.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendMC.AddEntry(&GMCPhi5, "MC (#phi-modulated, |#eta| < 1.0, p_{T} = 1.0-3.0 GeV)", "lp");

               TLegend LegendData(0.15, 0.15, 0.35, 0.45);
               LegendData.SetTextFont(42);
               LegendData.SetTextSize(0.025);
               LegendData.SetFillStyle(0);
               LegendData.SetBorderSize(0);
               LegendData.AddEntry(&GData, "Data (no #phi)", "lp");
               LegendData.AddEntry(&GDataPhi0, "Data (#phi-modulated, |#eta| < 1.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendData.AddEntry(&GDataPhi1, "Data (#phi-modulated, |#eta| < 1.5, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendData.AddEntry(&GDataPhi2, "Data (#phi-modulated, |#eta| < 2.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendData.AddEntry(&GDataPhi3, "Data (#phi-modulated, |#eta| < 2.5, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendData.AddEntry(&GDataPhi4, "Data (#phi-modulated, |#eta| < 3.0, p_{T} = 0.3-3.0 GeV)", "lp");
               LegendData.AddEntry(&GDataPhi5, "Data (#phi-modulated, |#eta| < 1.0, p_{T} = 1.0-3.0 GeV)", "lp");

               HWorld.Draw("axis");
               if(DoError == true)
               {
                  GMC.Draw("pl");
                  GMCPhi0.Draw("pl");
                  GMCPhi1.Draw("p");
                  GMCPhi2.Draw("p");
                  GMCPhi3.Draw("p");
                  GMCPhi4.Draw("pl");
                  GMCPhi5.Draw("p");
               }
               else
               {
                  GMC.Draw("pl");
                  GMCPhi0.Draw("pl");
                  GMCPhi1.Draw("pl");
                  GMCPhi2.Draw("pl");
                  GMCPhi3.Draw("pl");
                  GMCPhi4.Draw("pl");
                  GMCPhi5.Draw("pl");
               }
               LegendMC.Draw();

               PdfFile.AddCanvas(Canvas);

               HWorld.Draw("axis");
               if(DoError == true)
               {
                  GData.Draw("pl");
                  GDataPhi0.Draw("pl");
                  GDataPhi1.Draw("p");
                  GDataPhi2.Draw("p");
                  GDataPhi3.Draw("p");
                  GDataPhi4.Draw("pl");
                  GDataPhi5.Draw("p");
               }
               else
               {
                  GData.Draw("pl");
                  GDataPhi0.Draw("pl");
                  GDataPhi1.Draw("pl");
                  GDataPhi2.Draw("pl");
                  GDataPhi3.Draw("pl");
                  GDataPhi4.Draw("pl");
                  GDataPhi5.Draw("pl");
               }
               LegendData.Draw();

               PdfFile.AddCanvas(Canvas);
            }
         }
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

TGraphAsymmErrors TranscribeEtaScan(DataHelper &DHFile, string Prefix,
   int RBin, int CBin, bool DoError)
{
   vector<string> States = DHFile.GetListOfKeys();

   TGraphAsymmErrors G;
   // G.SetLineWidth(2);

   for(string State : States)
   {
      if(State.find(Prefix + "_") != 0)   // we want the right prefix
         continue;
      if(State.find(Form("C%d", CBin)) == string::npos)   // wrong centrality bin
         continue;
      if(State.find(Form("R%d", RBin)) == string::npos)   // wrong radius bin
         continue;

      // we found a valid state!

      int N = G.GetN();
      double EtaMin     = DHFile[State]["EtaMin"].GetDouble();
      double EtaMax     = DHFile[State]["EtaMax"].GetDouble();
      double Sigma      = DHFile[State]["P2"].GetDouble();
      double SigmaError = DHFile[State]["P2Error"].GetDouble();

      G.SetPoint(N, (EtaMin + EtaMax) / 2, Sigma);
      if(DoError == true)
         G.SetPointError(N, (EtaMax - EtaMin) / 2, (EtaMax - EtaMin) / 2, SigmaError, SigmaError);
      else
         G.SetPointError(N, 0, 0, SigmaError, SigmaError);
   }

   G.Sort();

   return G;
}

TGraphAsymmErrors TranscribeDPhiScan(DataHelper &DHFile, string Prefix, int RBin, int CBin, int EtaBin, bool DoError)
{
   vector<string> States = DHFile.GetListOfKeys();

   TGraphAsymmErrors G;
   // G.SetLineWidth(2);

   for(string State : States)
   {
      if(State.find(Prefix + "_") != 0)   // we want the right prefix
         continue;
      if(State.find(Form("C%d", CBin)) == string::npos)   // wrong centrality bin
         continue;
      if(State.find(Form("R%d", RBin)) == string::npos)   // wrong radius bin
         continue;
      if(State.find(Form("Eta%d", EtaBin)) == string::npos)   // wrong radius bin
         continue;

      // we found a valid state!

      int N = G.GetN();
      double XMin       = DHFile[State]["XMin"].GetDouble();
      double XMax       = DHFile[State]["XMax"].GetDouble();
      if(DHFile[State].Exist("DPhiMin") == true)
         XMin = DHFile[State]["DPhiMin"].GetDouble();
      if(DHFile[State].Exist("DPhiMax") == true)
         XMax = DHFile[State]["DPhiMax"].GetDouble();
      double Sigma      = DHFile[State]["P2"].GetDouble();
      double SigmaError = DHFile[State]["P2Error"].GetDouble();

      G.SetPoint(N, (XMin + XMax) / 2, Sigma);
      if(DoError == true)
         G.SetPointError(N, (XMax - XMin) / 2, (XMax - XMin) / 2, SigmaError, SigmaError);
      else
         G.SetPointError(N, 0, 0, SigmaError, SigmaError);
   }

   G.Sort();

   return G;
}

double FindMax(TGraphAsymmErrors &G)
{
   double Max = 0;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      double ey = G.GetErrorYhigh(i);
      if(y + ey > Max)
         Max = y + ey;
   }
   return Max;
}

double FindMin(TGraphAsymmErrors &G)
{
   double Min = 99999;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      double ey = G.GetErrorYlow(i);
      if(y - ey < Min)
         Min = y - ey;
   }
   return Min;
}



