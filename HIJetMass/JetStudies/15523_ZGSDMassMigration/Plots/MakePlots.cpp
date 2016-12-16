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
#include "TLegend.h"

#include "SetStyle.h"

#include "BasicUtilities.h"

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D *H);
void NormalizeHistogram(TH1D *H1, TH1D *H2);
void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag,
   string PlotOption = "colz", string POption = "");

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   char *InputFile = argv[1];
   string OutputBase = argv[2];

   bool IsPP = IsPPFromTag(InputFile);

   TFile F(InputFile);

   TCanvas Canvas;
   
   TLatex TagLatex;
   TagLatex.SetNDC();
   TagLatex.SetTextFont(42);
   TagLatex.SetTextSize(0.02);

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};

   for(int i = 0; i < 5; i++)
   {
      ExportHistogram2DWithProfile(F, "HSDMassRecoJetPT_" + CBin[i], "PSDMassRecoJetPT_" + CBin[i],
         OutputBase + "_SDMassRecoJetPT_" + CBin[i], OutputBase, "colz", "");
      ExportHistogram2DWithProfile(F, "HZGRecoJetPT_" + CBin[i], "PZGRecoJetPT_" + CBin[i],
         OutputBase + "_ZGRecoJetPT_" + CBin[i], OutputBase, "colz", "");
      ExportHistogram2D(F, "HSDMassZG_" + CBin[i],
         OutputBase + "_SDMassZG_" + CBin[i], OutputBase, "colz");
      ExportHistogram2D(F, "HSDMassOverPTZG_" + CBin[i],
         OutputBase + "_SDMassOverPTZG_" + CBin[i], OutputBase, "colz");
      ExportHistogram2DWithProfile(F, "HSDJetPTRecoJetPT_" + CBin[i], "PSDJetPTRecoJetPT_" + CBin[i],
         OutputBase + "_SDJetPTRecoJetPT_" + CBin[i], OutputBase, "colz", "");
      ExportHistogram2DWithProfile(F, "HSDDepthRecoJetPT_" + CBin[i], "PSDDepthRecoJetPT_" + CBin[i],
         OutputBase + "_SDDepthRecoJetPT_" + CBin[i], OutputBase, "colz", "");
   }

   F.Close();

   return 0;
}

void NormalizeHistogram(TH1D *H)
{
   if(H == NULL)
      return;

   int N = H->GetNbinsX();
   double L = H->GetXaxis()->GetBinLowEdge(1);
   double R = H->GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;
   H->Scale(1 / H->Integral() / BinSize);
}

void NormalizeHistogram(TH1D *H1, TH1D *H2)
{
   if(H1 == NULL || H2 == NULL)
      return;
   
   int N1 = H1->GetNbinsX();
   double L1 = H1->GetXaxis()->GetBinLowEdge(1);
   double R1 = H1->GetXaxis()->GetBinUpEdge(N1);
   double BinSize1 = (R1 - L1) / N1;
   
   int N2 = H2->GetNbinsX();
   double L2 = H2->GetXaxis()->GetBinLowEdge(1);
   double R2 = H2->GetXaxis()->GetBinUpEdge(N2);
   double BinSize2 = (R2 - L2) / N2;

   double Integral1 = H1->Integral() * BinSize1;
   double Integral2 = H2->Integral() * BinSize2;
   double Integral = Integral1 + Integral2;

   H1->Scale(1 / Integral);
   H2->Scale(1 / Integral);
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


