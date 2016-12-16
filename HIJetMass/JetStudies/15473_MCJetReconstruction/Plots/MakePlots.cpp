#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFitResult.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
TH1D *GetStandardDeviation(TProfile *P);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   string InputFile = argv[1];
   string OutputBase = argv[2];

   TFile File(InputFile.c_str());

   TProfile *PJetResponsesEta[5][5] = {{NULL}};
   TProfile *PJetResponsesPT[4][5] = {{NULL}};
   TProfile *PJetResponsesEtaFull[5] = {NULL};
   TProfile *PJetResponsesPTFull[5] = {NULL};
   TH1D *HJetResponsesSigmaEta[5][5] = {{NULL}};
   TH1D *HJetResponsesSigmaPT[5][5] = {{NULL}};
   TH1D *HJetResponsesSigmaEtaFull[5] = {NULL};
   TH1D *HJetResponsesSigmaPTFull[5] = {NULL};

   int PTMin[6] = {100, 120, 140, 160, 200, 300};
   double AbsEtaMin[5] = {0, 0.5, 1, 1.5, 2};
   int CentralityMin[6] = {0, 10, 30, 50, 80, 100};

   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
         PJetResponsesEta[i][j] = (TProfile *)File.Get(Form("PJetResponseEta_%d_%d", PTMin[i], CentralityMin[j]));
   for(int j = 0; j < 5; j++)
      PJetResponsesEtaFull[j] = (TProfile *)File.Get(Form("PJetResponseEtaFull_%d", CentralityMin[j]));
   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
         PJetResponsesPT[i][j] = (TProfile *)File.Get(Form("PJetResponsePT_%2.1f_%d", AbsEtaMin[i], CentralityMin[j]));
   for(int j = 0; j < 5; j++)
      PJetResponsesPTFull[j] = (TProfile *)File.Get(Form("PJetResponsePTFull_%d", CentralityMin[j]));

   int Color[5] = {kCyan - 3, kBlack, kBlue, kRed, kGreen - 3};

   for(int j = 0; j < 5; j++)
   {
      PJetResponsesEtaFull[j]->Rebin(5);

      PJetResponsesEtaFull[j]->SetLineColor(kBlack);
      PJetResponsesEtaFull[j]->SetMarkerColor(kBlack);
      PJetResponsesEtaFull[j]->SetMarkerStyle(11);
      
      for(int i = 0; i < 5; i++)
      {
         PJetResponsesEta[i][j]->Rebin(5);

         PJetResponsesEta[i][j]->SetLineColor(Color[i]);
         PJetResponsesEta[i][j]->SetMarkerColor(Color[i]);
         PJetResponsesEta[i][j]->SetMarkerStyle(11);
      }
   }
   for(int j = 0; j < 5; j++)
   {
      PJetResponsesPTFull[j]->Rebin(5);

      PJetResponsesPTFull[j]->SetLineColor(kBlack);
      PJetResponsesPTFull[j]->SetMarkerColor(kBlack);
      PJetResponsesPTFull[j]->SetMarkerStyle(11);
      
      for(int i = 0; i < 4; i++)
      {
         PJetResponsesPT[i][j]->Rebin(5);

         PJetResponsesPT[i][j]->SetLineColor(Color[i]);
         PJetResponsesPT[i][j]->SetMarkerColor(Color[i]);
         PJetResponsesPT[i][j]->SetMarkerStyle(11);
      }
   }

   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
         HJetResponsesSigmaEta[i][j] = GetStandardDeviation(PJetResponsesEta[i][j]);
   for(int j = 0; j < 5; j++)
      HJetResponsesSigmaEtaFull[j] = GetStandardDeviation(PJetResponsesEtaFull[j]);
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 5; j++)
         HJetResponsesSigmaPT[i][j] = GetStandardDeviation(PJetResponsesPT[i][j]);
   for(int j = 0; j < 5; j++)
      HJetResponsesSigmaPTFull[j] = GetStandardDeviation(PJetResponsesPTFull[j]);
   
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         HJetResponsesSigmaEta[i][j]->SetLineColor(Color[i]);
         HJetResponsesSigmaEta[i][j]->SetMarkerColor(Color[i]);
         HJetResponsesSigmaEta[i][j]->SetMarkerStyle(11);
      }
   }
   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         HJetResponsesSigmaPT[i][j]->SetLineColor(Color[i]);
         HJetResponsesSigmaPT[i][j]->SetMarkerColor(Color[i]);
         HJetResponsesSigmaPT[i][j]->SetMarkerStyle(11);
      }
   }

   for(int j = 0; j < 5; j++)
   {
      TCanvas C;

      TH2D HWorld(Form("HWorldEta_%d", j),
         Form("Centrality %d%%-%d%%;#eta;rec / gen - 1", CentralityMin[j], CentralityMin[j+1]),
         100, -2, 2, 100, -0.3, 0.3);
      HWorld.SetStats(0);

      HWorld.Draw();

      for(int i = 0; i < 5; i++)
         PJetResponsesEta[i][j]->Draw("same");

      TLegend Legend(0.15, 0.15, 0.5, 0.4);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.03);
      for(int i = 0; i < 5; i++)
         Legend.AddEntry(PJetResponsesEta[i][j], Form("p_{T} = %d - %d GeV", PTMin[i], PTMin[i+1]), "lp");
      Legend.Draw();

      TGraph G0;
      G0.SetPoint(0, -2, 0);
      G0.SetPoint(1, +2, 0);
      G0.Draw("l");

      C.SaveAs(Form("%sEta_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEta_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEta_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEta_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      
      TH2D HWorldSmall(Form("HWorldSmallEta_%d", j),
         Form("Centrality %d%%-%d%%;#eta;rec / gen - 1", CentralityMin[j], CentralityMin[j+1]),
         100, -1.3, 1.3, 100, -0.3, 0.3);
      HWorldSmall.SetStats(0);
      
      HWorldSmall.Draw();

      PJetResponsesEtaFull[j]->Draw("same p");
      G0.Draw("l");
      
      C.SaveAs(Form("%sEtaFull_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEtaFull_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEtaFull_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sEtaFull_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));

      TH2D HWorldSigma(Form("HWorldSigmaEta_%d", j),
         Form("Centrality %d%%-%d%%;#eta;#sigma(rec / gen) / #mu", CentralityMin[j], CentralityMin[j+1]),
         100, -2, 2, 100, 0, 1);
      HWorldSigma.SetStats(0);

      HWorldSigma.Draw();

      for(int i = 0; i < 5; i++)
         HJetResponsesSigmaEta[i][j]->Draw("same");

      TLegend LegendSigma(0.45, 0.85, 0.80, 0.6);
      LegendSigma.SetBorderSize(0);
      LegendSigma.SetFillStyle(0);
      LegendSigma.SetTextFont(42);
      LegendSigma.SetTextSize(0.03);
      for(int i = 0; i < 5; i++)
         LegendSigma.AddEntry(PJetResponsesEta[i][j], Form("p_{T} = %d - %d GeV", PTMin[i], PTMin[i+1]), "lp");
      LegendSigma.Draw();

      C.SaveAs(Form("%sSigmaEta_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEta_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEta_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEta_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));

      TH2D HWorldSigmaSmall(Form("HWorldSigmaSmallEta_%d", j),
         Form("Centrality %d%%-%d%%;#eta;#sigma(rec / gen) / #mu", CentralityMin[j], CentralityMin[j+1]),
         100, -1.3, 1.3, 100, 0, 1);
      HWorldSigmaSmall.SetStats(0);
      
      HWorldSigmaSmall.Draw();

      HJetResponsesSigmaEtaFull[j]->Draw("same p");

      C.SaveAs(Form("%sSigmaEtaFull_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEtaFull_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEtaFull_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaEtaFull_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
   }

   for(int j = 0; j < 5; j++)
   {
      TCanvas C;

      TH2D HWorld(Form("HWorldPT_%d", j),
         Form("Centrality %d%%-%d%%;p_{T};rec / gen - 1", CentralityMin[j], CentralityMin[j+1]),
         100, 100, 300, 100, -0.3, 0.3);
      HWorld.SetStats(0);

      HWorld.Draw();

      for(int i = 0; i < 4; i++)
         PJetResponsesPT[i][j]->Draw("same");

      TLegend Legend(0.15, 0.15, 0.5, 0.4);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.03);
      for(int i = 0; i < 4; i++)
         Legend.AddEntry(PJetResponsesPT[i][j], Form("|#eta| = %2.1f - %2.1f", AbsEtaMin[i], AbsEtaMin[i+1]), "lp");
      Legend.Draw();

      TGraph G0;
      G0.SetPoint(0, 100, 0);
      G0.SetPoint(1, 300, 0);
      G0.Draw("l");

      C.SaveAs(Form("%sPT_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPT_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPT_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPT_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      
      HWorld.Draw();

      PJetResponsesPTFull[j]->Draw("same p");
      G0.Draw("l");
      
      C.SaveAs(Form("%sPTFull_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPTFull_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPTFull_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sPTFull_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      
      TH2D HWorldSigma(Form("HWorldSigmaPT_%d", j),
         Form("Centrality %d%%-%d%%;p_{T};#sigma(rec / gen) / #mu", CentralityMin[j], CentralityMin[j+1]),
         100, 100, 300, 100, 0, 1);
      HWorldSigma.SetStats(0);

      HWorldSigma.Draw();

      for(int i = 0; i < 4; i++)
         HJetResponsesSigmaPT[i][j]->Draw("same");

      TLegend LegendSigma(0.45, 0.85, 0.80, 0.6);
      LegendSigma.SetBorderSize(0);
      LegendSigma.SetFillStyle(0);
      LegendSigma.SetTextFont(42);
      LegendSigma.SetTextSize(0.03);
      for(int i = 0; i < 4; i++)
         LegendSigma.AddEntry(HJetResponsesSigmaPT[i][j], Form("|#eta| = %2.1f - %2.1f", AbsEtaMin[i], AbsEtaMin[i+1]), "lp");
      LegendSigma.Draw();

      C.SaveAs(Form("%sSigmaPT_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPT_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPT_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPT_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));

      TF1 F("F", "sqrt([0]*[0] + [1]*[1] / x + [2]*[2] / x / x)", 100, 300);
      F.SetParameter(0, 0.05);
      F.SetParameter(1, 1.00);
      F.SetParameter(2, 20.00);
      F.SetParLimits(0, 0, 1);
      F.SetParLimits(1, 0, 10);
      F.SetParLimits(2, 0, 100);
      bool Good = false;
      int FitCount = 0;
      do
      {
         // for(int i = 1; i <= HJetResponsesSigmaPTFull[j]->GetNbinsX(); i++)
         //    HJetResponsesSigmaPTFull[j]->SetBinError(i, 0.05);

         TFitResultPtr Result = HJetResponsesSigmaPTFull[j]->Fit(&F, "s", "", 100, 300);
         FitCount = FitCount + 1;

         if(Result->CovMatrixStatus() == 3)
            Good = true;
      } while(Good == false && FitCount < 100);

      HWorldSigma.Draw();

      HJetResponsesSigmaPTFull[j]->Draw("same p");

      TLegend LegendParameter(0.3, 0.8, 0.8, 0.6);
      LegendParameter.SetBorderSize(0);
      LegendParameter.SetTextFont(42);
      LegendParameter.SetTextSize(0.035);
      LegendParameter.SetFillStyle(0);
      LegendParameter.AddEntry("", Form("C: %4.2f #pm %4.2f", F.GetParameter(0), F.GetParError(0)), "");
      LegendParameter.AddEntry("", Form("S: %4.2f #pm %4.2f", F.GetParameter(1), F.GetParError(1)), "");
      LegendParameter.AddEntry("", Form("N: %4.2f #pm %4.2f", F.GetParameter(2), F.GetParError(2)), "");
      LegendParameter.Draw();

      C.SaveAs(Form("%sSigmaPTFull_%d_%d.png", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPTFull_%d_%d.C", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPTFull_%d_%d.eps", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
      C.SaveAs(Form("%sSigmaPTFull_%d_%d.pdf", OutputBase.c_str(), CentralityMin[j], CentralityMin[j+1]));
   }

   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
         delete HJetResponsesSigmaEta[i][j];
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 5; j++)
         delete HJetResponsesSigmaPT[i][j];
   for(int j = 0; j < 5; j++)
      delete HJetResponsesSigmaEtaFull[j];
   for(int j = 0; j < 5; j++)
      delete HJetResponsesSigmaPTFull[j];

   TH2D *HJetCount = (TH2D *)File.Get("HJetCount");
   TH2D *HMatchedJetCount = (TH2D *)File.Get("HMatchedJetCount");

   HMatchedJetCount->Divide(HJetCount);

   HMatchedJetCount->SetStats(0);
   HMatchedJetCount->SetTitle("Percentage of jets matched");
   HMatchedJetCount->SetMaximum(1.00);
   HMatchedJetCount->SetMinimum(0.80);

   TCanvas C;

   gStyle->SetPaintTextFormat("4.3f");
   HMatchedJetCount->Draw("text00 colz");

   C.SaveAs(Form("%s_MatchedPercentage.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_MatchedPercentage.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_MatchedPercentage.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_MatchedPercentage.pdf", OutputBase.c_str()));

   File.Close();

   return 0;
}

TH1D *GetStandardDeviation(TProfile *P)
{
   if(P == NULL)
      return NULL;

   static int Counter = 0;
   Counter = Counter + 1;

   int N = P->GetNbinsX();
   double L = P->GetXaxis()->GetBinLowEdge(1);
   double R = P->GetXaxis()->GetBinUpEdge(N);
   TH1D *H = new TH1D(Form("HDeviation%d", Counter), ";;", N, L, R);

   string ErrorOption = P->GetErrorOption();
   P->SetErrorOption("s");

   for(int i = 1; i <= N; i++)
      H->SetBinContent(i, P->GetBinError(i) / (1 + P->GetBinContent(i)));

   P->SetErrorOption(ErrorOption.c_str());

   return H;
}





