#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag,
   string PlotOption = "colz", string POption = "");

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << "InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   char *InputFile = argv[1];
   string OutputBase = argv[2];

   TFile F(InputFile);

   ExportHistogram2D(F, "HSubJetCountRecoVsGen", OutputBase + "_SubJetCountRecoVsGen", OutputBase, "text");
   ExportHistogram2D(F, "HSubJetDRVsGenPT", OutputBase + "_SubJetDRVsGenPT", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRRecoVsGen", OutputBase + "_SubJetDRRecoVsGen", OutputBase, "colz");
   ExportProfile2D(F, "PSDMassVsSubJetDRGenPT", OutputBase + "_SDMassVsSubJetDRGenPT", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassVsGenPT", OutputBase + "_SDMassVsGenPT", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassVsGenPT_DR01", OutputBase + "_SDMassVsGenPT_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassVsGenPT_DR02", OutputBase + "_SDMassVsGenPT_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassVsGenPT_DR03", OutputBase + "_SDMassVsGenPT_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassVsGenPT_DR04", OutputBase + "_SDMassVsGenPT_DR04", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsGenPT", OutputBase + "_SDMassRatioVsGenPT", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsGenPT_DR01", OutputBase + "_SDMassRatioVsGenPT_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsGenPT_DR02", OutputBase + "_SDMassRatioVsGenPT_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsGenPT_DR03", OutputBase + "_SDMassRatioVsGenPT_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsGenPT_DR04", OutputBase + "_SDMassRatioVsGenPT_DR04", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsSubJetDR", "PSDMassRatioVsSubJetDR",
      OutputBase + "_SDMassRatioVsSubJetDR", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_Centrality0",
      OutputBase + "_SDMassRatioVsSubJetDR_Centrality0", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_Centrality1",
      OutputBase + "_SDMassRatioVsSubJetDR_Centrality1", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_Centrality2",
      OutputBase + "_SDMassRatioVsSubJetDR_Centrality2", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_Centrality3",
      OutputBase + "_SDMassRatioVsSubJetDR_Centrality3", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_Centrality4",
      OutputBase + "_SDMassRatioVsSubJetDR_Centrality4", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsGenPT", OutputBase + "_SDPTRatioVsGenPT", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsGenPT_DR01", OutputBase + "_SDPTRatioVsGenPT_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsGenPT_DR02", OutputBase + "_SDPTRatioVsGenPT_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsGenPT_DR03", OutputBase + "_SDPTRatioVsGenPT_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsGenPT_DR04", OutputBase + "_SDPTRatioVsGenPT_DR04", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDPTRatioVsSubJetDR", "PSDPTRatioVsSubJetDR",
      OutputBase + "_SDPTRatioVsSubJetDR", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsSubJetDR_Centrality0",
      OutputBase + "_SDPTRatioVsSubJetDR_Centrality0", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsSubJetDR_Centrality1",
      OutputBase + "_SDPTRatioVsSubJetDR_Centrality1", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsSubJetDR_Centrality2",
      OutputBase + "_SDPTRatioVsSubJetDR_Centrality2", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsSubJetDR_Centrality3",
      OutputBase + "_SDPTRatioVsSubJetDR_Centrality3", OutputBase, "colz");
   ExportHistogram2D(F, "HSDPTRatioVsSubJetDR_Centrality4",
      OutputBase + "_SDPTRatioVsSubJetDR_Centrality4", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSDMassRatio",
      OutputBase + "_LeadingSubJetPTRatioVsSDMassRatio", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSDMassRatio_DR01",
      OutputBase + "_LeadingSubJetPTRatioVsSDMassRatio_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSDMassRatio_DR02",
      OutputBase + "_LeadingSubJetPTRatioVsSDMassRatio_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSDMassRatio_DR03",
      OutputBase + "_LeadingSubJetPTRatioVsSDMassRatio_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSDMassRatio_DR04",
      OutputBase + "_LeadingSubJetPTRatioVsSDMassRatio_DR04", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRSumVsSDMassRatio",
      OutputBase + "_SubJetDRSumVsSDMassRatio", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRSumVsSDMassRatio_DR01",
      OutputBase + "_SubJetDRSumVsSDMassRatio_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRSumVsSDMassRatio_DR02",
      OutputBase + "_SubJetDRSumVsSDMassRatio_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRSumVsSDMassRatio_DR03",
      OutputBase + "_SubJetDRSumVsSDMassRatio_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRSumVsSDMassRatio_DR04",
      OutputBase + "_SubJetDRSumVsSDMassRatio_DR04", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRMaxVsSDMassRatio",
      OutputBase + "_SubJetDRMaxVsSDMassRatio", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRMaxVsSDMassRatio_DR01",
      OutputBase + "_SubJetDRMaxVsSDMassRatio_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRMaxVsSDMassRatio_DR02",
      OutputBase + "_SubJetDRMaxVsSDMassRatio_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRMaxVsSDMassRatio_DR03",
      OutputBase + "_SubJetDRMaxVsSDMassRatio_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSubJetDRMaxVsSDMassRatio_DR04",
      OutputBase + "_SubJetDRMaxVsSDMassRatio_DR04", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax",
      "PSDMassRatioVsSubJetDR_SmallSubjetDRMax",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4",
      OutputBase + "_SDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4",
      OutputBase + "_SDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04",
      OutputBase + "_LeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04", OutputBase, "colz");

   TProfile *P = (TProfile *)F.Get("PSDMassRatioVsSubJetDR_SmallSubjetDRMax");
   if(P != NULL)
   {
      P->SetErrorOption("S");
      TGraph G;
      for(int i = 1; i <= P->GetNbinsX(); i++)
         G.SetPoint(i - 1, P->GetBinCenter(i), P->GetBinError(i));

      TH2D HWorld("HWorld", ";Sub-jet DR;RMS on SD Mass response (reco / gen)", 100, 0, 0.5, 100, 0, 0.5);
      HWorld.SetStats(0);

      TCanvas C;

      HWorld.Draw();
      G.Draw("p");
      
      TLatex Latex;
      Latex.SetNDC();
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.02);
      Latex.DrawLatex(0.10, 0.92, OutputBase.c_str());

      C.SaveAs((OutputBase + "_SDMassRatioRMSVsSubJetDR.png").c_str());
      C.SaveAs((OutputBase + "_SDMassRatioRMSVsSubJetDR.C").c_str());
      C.SaveAs((OutputBase + "_SDMassRatioRMSVsSubJetDR.eps").c_str());
      C.SaveAs((OutputBase + "_SDMassRatioRMSVsSubJetDR.pdf").c_str());
   }

   F.Close();

   return 0;
}

void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Histogram " << Name << " not found!" << endl;
      return;
   }

   TCanvas C;

   H->SetStats(0);
   H->Draw(PlotOption.c_str());

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}

void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption)
{
   TProfile2D *H = (TProfile2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Profile " << Name << " not found!" << endl;
      return;
   }

   TCanvas C;

   H->SetStats(0);
   H->Draw(PlotOption.c_str());

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}

void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag, string PlotOption, string POption)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Histogram " << Name << " not found!" << endl;
      return;
   }

   TProfile *P = (TProfile *)F.Get(PName.c_str());
   if(P == NULL)
   {
      cerr << "Profile " << PName << " not found!" << endl;
      return;
   }

   P->SetMarkerStyle(11);
   P->SetLineWidth(2);
   P->Rebin(2);

   TCanvas C;

   P->SetErrorOption(POption.c_str());

   H->SetStats(0);
   H->Draw(PlotOption.c_str());
   P->Draw("same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}


