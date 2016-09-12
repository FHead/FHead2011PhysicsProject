#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TProfile2D.h"
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

   ExportHistogram2DWithProfile(F, "HSDMassRatioVsJetPT", "PSDMassRatioVsJetPT",
      OutputBase + "_SDMassRatioVsJetPT", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsJetPT_DR01", "PSDMassRatioVsJetPT_DR01",
      OutputBase + "_SDMassRatioVsJetPT_DR01", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsJetPT_DR02", "PSDMassRatioVsJetPT_DR02",
      OutputBase + "_SDMassRatioVsJetPT_DR02", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsJetPT_DR03", "PSDMassRatioVsJetPT_DR03",
      OutputBase + "_SDMassRatioVsJetPT_DR03", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsJetPT_DR04", "PSDMassRatioVsJetPT_DR04",
      OutputBase + "_SDMassRatioVsJetPT_DR04", OutputBase, "colz", "S");
   
   ExportHistogram2D(F, "HToyMassResponseVsSubJetDR_Smear0",
      OutputBase + "_ToyMassResponseVsSubJetDR_Smear0", OutputBase, "colz");
   ExportHistogram2D(F, "HToyMassResponseVsSubJetDR_Smear1",
      OutputBase + "_ToyMassResponseVsSubJetDR_Smear1", OutputBase, "colz");
   ExportHistogram2D(F, "HToyMassResponseVsSubJetDR_Smear2",
      OutputBase + "_ToyMassResponseVsSubJetDR_Smear2", OutputBase, "colz");
   ExportHistogram2D(F, "HToyMassResponseVsSubJetDR_Smear3",
      OutputBase + "_ToyMassResponseVsSubJetDR_Smear3", OutputBase, "colz");
   
   ExportHistogram2DWithProfile(F, "HToyMassResponseVsSubJetDR_PTSmear0", "PToyMassResponseVsSubJetDR_PTSmear0",
      OutputBase + "_ToyMassResponseVsSubJetDR_PTSmear0", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HToyMassResponseVsSubJetDR_PTSmear1", "PToyMassResponseVsSubJetDR_PTSmear1",
      OutputBase + "_ToyMassResponseVsSubJetDR_PTSmear1", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HToyMassResponseVsSubJetDR_PTSmear2", "PToyMassResponseVsSubJetDR_PTSmear2",
      OutputBase + "_ToyMassResponseVsSubJetDR_PTSmear2", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HToyMassResponseVsSubJetDR_PTSmear3", "PToyMassResponseVsSubJetDR_PTSmear3",
      OutputBase + "_ToyMassResponseVsSubJetDR_PTSmear3", OutputBase, "colz", "S");

   ExportHistogram2D(F, "HGenSubJetPositionSpread",
      OutputBase + "_GenSubJetPositionSpread", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPositionSpread",
      OutputBase + "_LeadingSubJetPositionSpread", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPositionSpread_DR01",
      OutputBase + "_LeadingSubJetPositionSpread_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPositionSpread_DR02",
      OutputBase + "_LeadingSubJetPositionSpread_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPositionSpread_DR03",
      OutputBase + "_LeadingSubJetPositionSpread_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetPositionSpread_DR04",
      OutputBase + "_LeadingSubJetPositionSpread_DR04", OutputBase, "colz");
   ExportHistogram2D(F, "HSubleadingSubJetPositionSpread",
      OutputBase + "_SubleadingSubJetPositionSpread", OutputBase, "colz");
   ExportHistogram2D(F, "HSubleadingSubJetPositionSpread_DR01",
      OutputBase + "_SubleadingSubJetPositionSpread_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HSubleadingSubJetPositionSpread_DR02",
      OutputBase + "_SubleadingSubJetPositionSpread_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HSubleadingSubJetPositionSpread_DR03",
      OutputBase + "_SubleadingSubJetPositionSpread_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HSubleadingSubJetPositionSpread_DR04",
      OutputBase + "_SubleadingSubJetPositionSpread_DR04", OutputBase, "colz");

   ExportHistogram2D(F, "HLeadingSubJetXVsSubleadingSubJetX",
      OutputBase + "_LeadingSubJetXVsSubleadingSubjetX", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetXVsSubleadingSubJetX_DR01",
      OutputBase + "_LeadingSubJetXVsSubleadingSubjetX_DR01", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetXVsSubleadingSubJetX_DR02",
      OutputBase + "_LeadingSubJetXVsSubleadingSubjetX_DR02", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetXVsSubleadingSubJetX_DR03",
      OutputBase + "_LeadingSubJetXVsSubleadingSubjetX_DR03", OutputBase, "colz");
   ExportHistogram2D(F, "HLeadingSubJetXVsSubleadingSubJetX_DR04",
      OutputBase + "_LeadingSubJetXVsSubleadingSubjetX_DR04", OutputBase, "colz");

   ExportHistogram2DWithProfile(F, "HLeadingSubJetPTResponseVsLeadingX", "PLeadingSubJetPTResponseVsLeadingX",
      OutputBase + "_LeadingSubJetPTResponseVsLeadingX", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSubleadingSubJetPTResponseVsLeadingX", "PSubleadingSubJetPTResponseVsLeadingX",
      OutputBase + "_SubleadingSubJetPTResponseVsLeadingX", OutputBase, "colz");

   ExportHistogram2D(F, "HSDMassOverGenSubJet1MassVsDR_PositiveXPositiveX",
      OutputBase + "_SDMassOverGenSubJet1MassVsDR_PositiveXPositiveX", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassOverGenSubJet1MassVsDR_NegativeXPositiveX",
      OutputBase + "_SDMassOverGenSubJet1MassVsDR_NegativeXPositiveX", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassOverGenSubJet1MassVsDR_PositiveXNegativeX",
      OutputBase + "_SDMassOverGenSubJet1MassVsDR_PositiveXNegativeX", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsDR_PositiveXPositiveX",
      OutputBase + "_SDMassRatioVsDR_PositiveXPositiveX", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsDR_NegativeXPositiveX",
      OutputBase + "_SDMassRatioVsDR_NegativeXPositiveX", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsDR_PositiveXNegativeX",
      OutputBase + "_SDMassRatioVsDR_PositiveXNegativeX", OutputBase, "colz");

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

   C.SetLogz(true);

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
   
   C.SetLogz(true);

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


