#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"

#include "DataHelper.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   int SD = 7;
   bool IsMC = false;

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " SD=(0|7) IsMC=(Y|N)" << endl;
      return -1;
   }

   SD = ((argv[1][0] == '0') ? 0 : 7);
   IsMC = ((argv[2][0] == 'Y') ? true : false);

   string T = "";
   T = T + "" + ((SD == 0) ? "0" : "7");
   T = T + "_" + (IsMC ? "MC" : "Data");

   PdfFileHelper PdfFile("CombinedSystematics_" + T + ".pdf");
   PdfFile.AddTextPage(T);

   vector<string> Tags;
   if(IsMC == true)
   {
      Tags.push_back(Form("Ghost_%d", SD));
      Tags.push_back(Form("JER_%d", SD));
      Tags.push_back(Form("JetEta_%d", SD));
      Tags.push_back(Form("MB2_%d", SD));
      Tags.push_back(Form("PTScale_%d", SD));
      Tags.push_back(Form("Rho_%d", SD));
      Tags.push_back(Form("NewSmear_%d", SD));
      Tags.push_back(Form("DR_%d", SD));
      Tags.push_back(Form("Range_%d", SD));
      Tags.push_back(Form("Trigger_%d", SD));
      Tags.push_back(Form("QuarkGluonBig_%d", SD));
      Tags.push_back(Form("MassScale_%d", SD));
   }
   else
   {
      Tags.push_back(Form("Ghost_%d", SD));
      Tags.push_back(Form("JER_%d", SD));
      Tags.push_back(Form("PTScale_%d", SD));
      Tags.push_back(Form("DR_%d", SD));
      Tags.push_back(Form("NewSmear_%d", SD));
   }

   DataHelper DHFile("Systematics.dh");

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iP = 0; iP < 6; iP++)
      {
         string State = Form("GRatio_C%d_P%d", iC, iP);

         TH1D H("H", Form("%s (mean);;", State.c_str()), Tags.size() + 1, 0, Tags.size() + 1);
         H.SetMarkerStyle(20);
         H.SetStats(0);
         H.SetMaximum(0.10000);
         H.SetMinimum(0.00001);
         H.SetFillColor(kBlue - 7);
         H.SetFillStyle(3154);
         H.SetLineColor(kBlue + 2);
         
         TH1D H2("H2", Form("%s (width);;", State.c_str()), Tags.size() + 1, 0, Tags.size() + 1);
         H2.SetMarkerStyle(20);
         H2.SetStats(0);
         H2.SetMaximum(0.10000);
         H2.SetMinimum(0.00001);
         H2.SetFillColor(kBlue - 7);
         H2.SetFillStyle(3154);
         H2.SetLineColor(kBlue + 2);
         
         TH1D H3("H3", Form("%s (3rd moment);;", State.c_str()), Tags.size() + 1, 0, Tags.size() + 1);
         H3.SetMarkerStyle(20);
         H3.SetStats(0);
         H3.SetMaximum(0.10000);
         H3.SetMinimum(0.00001);
         H3.SetFillColor(kBlue - 7);
         H3.SetFillStyle(3154);
         H3.SetLineColor(kBlue + 2);
         
         TH1D H4("H4", Form("%s (4th moment);;", State.c_str()), Tags.size() + 1, 0, Tags.size() + 1);
         H4.SetMarkerStyle(20);
         H4.SetStats(0);
         H4.SetMaximum(0.10000);
         H4.SetMinimum(0.00001);
         H4.SetFillColor(kBlue - 7);
         H4.SetFillStyle(3154);
         H4.SetLineColor(kBlue + 2);
         
         TH1D H5("H5", Form("%s (5th moment);;", State.c_str()), Tags.size() + 1, 0, Tags.size() + 1);
         H5.SetMarkerStyle(20);
         H5.SetStats(0);
         H5.SetMaximum(0.10000);
         H5.SetMinimum(0.00001);
         H5.SetFillColor(kBlue - 7);
         H5.SetFillStyle(3154);
         H5.SetLineColor(kBlue + 2);

         double TotalR = 0;
         double TotalVR = 0;
         double TotalV3R = 0;
         double TotalV4R = 0;
         double TotalV5R = 0;

         for(int iT = 0; iT < (int)Tags.size(); iT++)
         {
            H.GetXaxis()->SetBinLabel(iT + 1, Tags[iT].c_str());
            H2.GetXaxis()->SetBinLabel(iT + 1, Tags[iT].c_str());
            H3.GetXaxis()->SetBinLabel(iT + 1, Tags[iT].c_str());
            H4.GetXaxis()->SetBinLabel(iT + 1, Tags[iT].c_str());
            H5.GetXaxis()->SetBinLabel(iT + 1, Tags[iT].c_str());

            double N = DHFile[State][Tags[iT]+"_Nominal"].GetDouble();
            double M = DHFile[State][Tags[iT]+"_Modified"].GetDouble();
            
            double VN = DHFile[State][Tags[iT]+"_NominalVariance"].GetDouble();
            double VM = DHFile[State][Tags[iT]+"_ModifiedVariance"].GetDouble();
            
            double V3N = DHFile[State][Tags[iT]+"_NominalMoment3"].GetDouble();
            double V3M = DHFile[State][Tags[iT]+"_ModifiedMoment3"].GetDouble();
            
            double V4N = DHFile[State][Tags[iT]+"_NominalMoment4"].GetDouble();
            double V4M = DHFile[State][Tags[iT]+"_ModifiedMoment4"].GetDouble();
            
            double V5N = DHFile[State][Tags[iT]+"_NominalMoment5"].GetDouble();
            double V5M = DHFile[State][Tags[iT]+"_ModifiedMoment5"].GetDouble();

            double R = ((M > M) ? M / N : N / M);
            double VR = ((VM > VN) ? VM / VN : VN / VM);
            double V3R = ((V3M > V3N) ? V3M / V3N : V3N / V3M);
            double V4R = ((V4M > V4N) ? V4M / V4N : V4N / V4M);
            double V5R = ((V5M > V5N) ? V5M / V5N : V5N / V5M);

            if(Tags[iT] == "QuarkGluon_0" || Tags[iT] == "QuarkGluon_7"
               || Tags[iT] == "QuarkGluonBig_0" || Tags[iT] == "QuarkGluonBig_7")
            {
               R = sqrt(R);
               VR = sqrt(VR);
               V3R = sqrt(V3R);
               V4R = sqrt(V4R);
               V5R = sqrt(V5R);
            }

            double ER = R * sqrt(VN / N / N + VM / M / M);

            if(R == R)
            {
               H.SetBinContent(iT + 1, R - 1);
               H.SetBinError(iT + 1, ER);

               TotalR = TotalR + log(R) * log(R);
            }
            if(VR == VR)
            {
               H2.SetBinContent(iT + 1, VR - 1);
               H2.SetBinError(iT + 1, 0.1);

               TotalVR = TotalVR + log(VR) * log(VR);
            }
            if(V3R == V3R)
            {
               H3.SetBinContent(iT + 1, VR - 1);
               H3.SetBinError(iT + 1, 0.1);

               TotalV3R = TotalV3R + log(V3R) * log(V3R);
            }
            if(V4R == V4R)
            {
               H4.SetBinContent(iT + 1, VR - 1);
               H4.SetBinError(iT + 1, 0.1);

               TotalV4R = TotalV4R + log(V4R) * log(V4R);
            }
            if(V5R == V5R)
            {
               H5.SetBinContent(iT + 1, VR - 1);
               H5.SetBinError(iT + 1, 0.1);

               TotalV5R = TotalV5R + log(V5R) * log(V5R);
            }
         }

         TotalR = exp(sqrt(TotalR));
         TotalVR = exp(sqrt(TotalVR));

         H.GetXaxis()->SetBinLabel(Tags.size() + 1, "Together");
         H.SetBinContent(Tags.size() + 1, TotalR - 1);
         
         H2.GetXaxis()->SetBinLabel(Tags.size() + 1, "Together");
         H2.SetBinContent(Tags.size() + 1, TotalVR - 1);
         
         H3.GetXaxis()->SetBinLabel(Tags.size() + 1, "Together");
         H3.SetBinContent(Tags.size() + 1, TotalVR - 1);
         
         H4.GetXaxis()->SetBinLabel(Tags.size() + 1, "Together");
         H4.SetBinContent(Tags.size() + 1, TotalVR - 1);
         
         H5.GetXaxis()->SetBinLabel(Tags.size() + 1, "Together");
         H5.SetBinContent(Tags.size() + 1, TotalVR - 1);

         DHFile[State]["All"] = TotalR;
         DHFile[State]["AllWidth"] = TotalVR;
         DHFile[State]["AllMoment3"] = TotalV3R;
         DHFile[State]["AllMoment4"] = TotalV4R;
         DHFile[State]["AllMoment5"] = TotalV5R;

         PdfFile.AddPlot(H, "BAR HIST P", true);
         PdfFile.AddPlot(H2, "BAR HIST P", true);
         PdfFile.AddPlot(H3, "BAR HIST P", true);
         PdfFile.AddPlot(H4, "BAR HIST P", true);
         PdfFile.AddPlot(H5, "BAR HIST P", true);
      }
   }

   DHFile.SaveToFile("SystematicsCombined_" + T + ".dh");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}


