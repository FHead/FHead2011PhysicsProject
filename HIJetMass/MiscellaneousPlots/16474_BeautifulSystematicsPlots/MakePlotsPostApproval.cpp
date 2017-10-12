#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main();
void FillGraph(vector<string> &FileName, string GraphName, TGraph &G);

int main()
{
   SetThesisStyle();

   int PTBin[] = {120, 140, 160, 180, 200, 300, 500};
   int CBin[] = {0, 10, 30, 50, 80, 100};
   string SDString[] = {"Soft drop z_{cut} = 0.1, #beta = 0.0", "Soft drop z_{cut} = 0.5, #beta = 1.5"};

   int *PTMin = PTBin;
   int *PTMax = PTBin + 1;
   int *CMin = CBin;
   int *CMax = CBin + 1;

   for(int iSD = 0; iSD < 2; iSD++)
   {
      int SD = (iSD == 0) ? 0 : 7;

      vector<string> NameJet, NameDR, NameSmear, NameTrigger, NameMass, NameQuarkGluon;

      NameSmear.push_back(Form("Files/OutputFile_Ghost_%d.root", SD));
      NameJet.push_back(Form("Files/OutputFile_JER_%d.root", SD));
      NameJet.push_back(Form("Files/OutputFile_JetEta_%d.root", SD));
      NameSmear.push_back(Form("Files/OutputFile_MB2_%d.root", SD));
      NameJet.push_back(Form("Files/OutputFile_PTScale_%d.root", SD));
      NameSmear.push_back(Form("Files/OutputFile_Rho_%d.root", SD));
      NameSmear.push_back(Form("Files/OutputFile_NewSmear_%d.root", SD));
      NameDR.push_back(Form("Files/OutputFile_DR_%d.root", SD));
      NameSmear.push_back(Form("Files/OutputFile_Range_%d.root", SD));
      NameTrigger.push_back(Form("Files/OutputFile_Trigger_%d.root", SD));
      NameQuarkGluon.push_back(Form("Files/OutputFile_QuarkGluon_%d.root", SD));
      NameMass.push_back(Form("Files/OutputFile_MassScale_%d.root", SD));
      
      for(int iC = 0; iC < 5; iC++)
      {
         for(int iP = 0; iP < 6; iP++)
         {
            string GraphName = Form("GRatio_C%d_P%d", iC, iP);

            TGraph GJet, GDR, GSmear, GTrigger, GMass, GQuarkGluon;

            FillGraph(NameJet, GraphName, GJet);
            FillGraph(NameDR, GraphName, GDR);
            FillGraph(NameSmear, GraphName, GSmear);
            FillGraph(NameTrigger, GraphName, GTrigger);
            FillGraph(NameMass, GraphName, GMass);
            FillGraph(NameQuarkGluon, GraphName, GQuarkGluon);

            TH2D HWorld("HWorld", ";M_{g} / p_{T}^{jet};Percentage", 100, 0, 0.25, 100, 0, 100);
            HWorld.SetStats(0);

            TCanvas C;

            HWorld.Draw("axis");
            GJet.Draw("l");
            GDR.Draw("l");
            GSmear.Draw("l");
            GTrigger.Draw("l");
            GMass.Draw("l");
            GQuarkGluon.Draw("l");

            GJet.SetLineWidth(2);
            GDR.SetLineWidth(2);
            GSmear.SetLineWidth(2);
            GTrigger.SetLineWidth(2);
            GMass.SetLineWidth(2);
            GQuarkGluon.SetLineWidth(2);

            GJet.SetLineColor(kBlack);
            GDR.SetLineColor(kRed);
            GSmear.SetLineColor(kGreen);
            GTrigger.SetLineColor(kCyan);
            GMass.SetLineColor(kBlue);
            GQuarkGluon.SetLineColor(kMagenta);

            TLegend Legend(0.3, 0.8, 0.6, 0.2);
            Legend.SetTextFont(42);
            Legend.SetTextSize(0.035);
            Legend.SetFillStyle(0);
            Legend.AddEntry(&GJet, "Jet Reconstruction", "l");
            Legend.AddEntry(&GDR, "#DeltaR Cut", "l");
            Legend.AddEntry(&GSmear, "Smearing Procedure", "l");
            Legend.AddEntry(&GTrigger, "Trigger", "l");
            Legend.AddEntry(&GMass, "Mass Scale Correction", "l");
            Legend.AddEntry(&GQuarkGluon, "Quark-Gluon Composition", "l");
            Legend.AddEntry("", "", "");
            Legend.AddEntry("", Form("%d < p_{T}^{jet} < %d GeV", PTMin[iP], PTMax[iP]), "");
            Legend.AddEntry("", Form("Centrality: %d%% - %d%%", CMin[iC], CMax[iC]), "");
            Legend.AddEntry("", SDString[iSD].c_str(), "");
            Legend.AddEntry("", "", "");
            Legend.AddEntry("", "", "");
            Legend.Draw();

            TLatex Text;
            Text.SetTextFont(42);
            Text.SetTextAlign(12);
            Text.SetTextSize(0.03);
            Text.SetNDC();

            Text.SetTextSize(0.06);
            Text.DrawLatex(0.10, 0.925, "#font[62]{CMS} #font[52]{Preliminary}");

            C.SaveAs(Form("Plots/Result_SD%d_C%d_PT%d.png", SD, iC, iP));
            C.SaveAs(Form("Plots/Result_SD%d_C%d_PT%d.C",   SD, iC, iP));
            C.SaveAs(Form("Plots/Result_SD%d_C%d_PT%d.eps", SD, iC, iP));
            C.SaveAs(Form("PDFPlots/Result_SD%d_C%d_PT%d.pdf", SD, iC, iP));
         }
      }
   }

   return 0;
}

void FillGraph(vector<string> &FileName, string GraphName, TGraph &G)
{
   int N = FileName.size();

   vector<TFile *> Files;
   for(int i = 0; i < N; i++)
      Files.push_back(new TFile(FileName[i].c_str()));

   vector<TGraphAsymmErrors *> Graphs;
   for(int i = 0; i < N; i++)
   {
      if(Files[i] == NULL)
         Graphs.push_back(NULL);
      else
         Graphs.push_back((TGraphAsymmErrors *)Files[i]->Get(GraphName.c_str()));
   }

   for(int iB = 0; iB < 160; iB++)
   {
      double x, y, exl, exh, eyl, eyh;

      double el2 = 0, eh2 = 0;

      double totaly = 0;

      for(int i = 0; i < (int)FileName.size(); i++)
      {
         if(Graphs[i] == NULL)
            continue;

         eyl = Graphs[i]->GetErrorYlow(iB);
         eyh = Graphs[i]->GetErrorYhigh(iB);

         el2 = el2 + eyl * eyl;
         eh2 = eh2 + eyh * eyh;

         Graphs[i]->GetPoint(iB, x, y);
         totaly = totaly + y;
      }

      G.SetPoint(iB, x, (exp(sqrt(eh2)) - 1) * 100);
   }

   for(int i = 0; i < N; i++)
   {
      if(Files[i] != NULL)
      {
         Files[i]->Close();
         delete Files[i];
      }
   }
}







