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
void Stack1DHistograms(TFile &F, TH2D &HWorld, string Name, vector<string> Tags, string OutputBase, string Tag,
   bool LogY = false);

int main(int argc, char *argv[])
{
   // if(argc != 3)
   // {
   //    cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
   //    return -1;
   // }

   SetThesisStyle();

   char *InputFile = "TaggedResult.root";
   string OutputBase = "Plots/";

   bool IsPP = IsPPFromTag(InputFile);

   vector<string> PP6DijetTags, PP8DijetTags, AA6DijetTags, AA8DijetTags;
   PP6DijetTags.push_back("PP6Dijet100");
   PP6DijetTags.push_back("PP6Dijet120");
   PP6DijetTags.push_back("PP6Dijet170");
   PP6DijetTags.push_back("PP6Dijet220");
   PP6DijetTags.push_back("PP6Dijet280");
   PP8DijetTags.push_back("PP8Dijet100");
   PP8DijetTags.push_back("PP8Dijet170");
   PP8DijetTags.push_back("PP8Dijet220");
   PP8DijetTags.push_back("PP8Dijet280");
   AA6DijetTags.push_back("AA6Dijet120");
   AA6DijetTags.push_back("AA6Dijet170");
   AA6DijetTags.push_back("AA6Dijet220");
   AA6DijetTags.push_back("AA6Dijet280");
   AA8DijetTags.push_back("AA8Dijet120");
   AA8DijetTags.push_back("AA8Dijet170");
   AA8DijetTags.push_back("AA8Dijet220");
   AA8DijetTags.push_back("AA8Dijet280");

   TFile F(InputFile);

   TH2D HWorldPTHat("HWorldPTHat", ";#hat{p}_{T};Yield", 100, 100, 500, 100, 1e-10, 1e-5);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatAll", PP6DijetTags, "Plots/PTHatAll_PP6Dijet", "PP6Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatAll", PP8DijetTags, "Plots/PTHatAll_PP8Dijet", "PP8Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatAll", AA6DijetTags, "Plots/PTHatAll_AA6Dijet", "AA6Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatAll", AA8DijetTags, "Plots/PTHatAll_AA8Dijet", "AA8Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatSelected", PP6DijetTags, "Plots/PTHatSelected_PP6Dijet", "PP6Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatSelected", PP8DijetTags, "Plots/PTHatSelected_PP8Dijet", "PP8Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatSelected", AA6DijetTags, "Plots/PTHatSelected_AA6Dijet", "AA6Dijet", true);
   Stack1DHistograms(F, HWorldPTHat, "HPTHatSelected", AA8DijetTags, "Plots/PTHatSelected_AA8Dijet", "AA8Dijet", true);

   TCanvas Canvas;
   
   TLatex TagLatex;
   TagLatex.SetNDC();
   TagLatex.SetTextFont(42);
   TagLatex.SetTextSize(0.02);

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

void Stack1DHistograms(TFile &F, TH2D &HWorld,
   string Name, vector<string> Tags, string OutputBase, string Tag,
   bool LogY)
{
   int Color[] = {kBlack, kRed, kBlue, kGreen - 3, kYellow, kCyan - 3};

   int N = Tags.size();

   vector<TH1 *> H(N);
   for(int i = 0; i < N; i++)
   {
      cout << i << " " << N << " " << Name << "__" << Tags[i] << endl;

      TObject *Object = (TObject *)F.Get(Form("%s__%s", Name.c_str(), Tags[i].c_str()));
      // TObject *Object = NULL;
      if(Object == NULL)
         H[i] = NULL;
      else
         H[i] = (TH1 *)Object->Clone(Form("H%d", i));
   }

   for(int i = 0; i < N; i++)
   {
      if(H[i] == NULL)
      {
         H.erase(H.begin() + i);
         i = i - 1;
      }
   }

   if(H.size() == 0)
      return;

   TCanvas C;
   
   HWorld.SetStats(0);
   HWorld.Draw();

   for(int i = 0; i < (int)H.size() - 1; i++)
      H[i+1]->Add(H[i]);

   for(int i = 0; i < (int)H.size(); i++)
   {
      H[i]->SetLineWidth(2);
      H[i]->SetLineColor(Color[i]);
      H[i]->SetFillColor(Color[i]);
   }

   for(int i = (int)H.size() - 1; i >= 0; i--)
      H[i]->Draw("bar same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SetLogy(LogY);

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   for(int i = 0; i < (int)H.size(); i++)
      if(H[i] != NULL)
         delete H[i];
}

