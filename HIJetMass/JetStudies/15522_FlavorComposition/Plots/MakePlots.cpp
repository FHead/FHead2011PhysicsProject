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

#define PROJECTION_NONE 0
#define PROJECTION_X 1
#define PROJECTION_Y 2

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D *H);
void NormalizeHistogram(TH1D *H1, TH1D *H2);
void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag,
   string PlotOption = "colz", string POption = "");
void Stack1DHistograms(TFile &F, TH2D &HWorld, vector<string> Names, vector<string> Labels,
   string OutputBase, string Tag,
   int Projection, int ProjectionMin = -1, int ProjectionMax = -1, bool LogY = false);

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

   vector<string> FBin;
   FBin.push_back("Gluon");
   FBin.push_back("Light");
   FBin.push_back("Charm");
   FBin.push_back("Heavy");

   vector<string> CBin;
   CBin.push_back("CBin0");
   CBin.push_back("CBin1");
   CBin.push_back("CBin2");
   CBin.push_back("CBin3");
   CBin.push_back("CBin4");

   vector<string> PTBin;
   PTBin.push_back("PTBin0");
   PTBin.push_back("PTBin1");
   PTBin.push_back("PTBin2");
   PTBin.push_back("PTBin3");
   PTBin.push_back("PTBin4");
   PTBin.push_back("PTBin5");
   PTBin.push_back("PTBin6");

   int CBinMin[6] = {0, 10, 30, 50, 80, 100};
   int PTBinMin[8] = {80, 100, 120, 140, 160, 200, 300, 500};

   int PTBinIndex[8] = {0};
   double PTMin = 80, PTMax = 500;
   int PTBinCount = 100;
   for(int i = 0; i < 8; i++)
      PTBinIndex[i] = (int)((PTBinMin[i] - PTMin) / (PTMax - PTMin) * PTBinCount + 1);

   double SDMassPTLogAxisMin[7] = {1e1, 5e1, 2e1, 1e1, 5e0, 2e0, 1e0};
   double SDMassPTLogAxisMax[7] = {1e5, 5e5, 2e5, 1e5, 5e4, 2e6, 1e6};
   double SDMassPTLinearAxisMin[7] = {0, 0, 0, 0, 0, 0, 0};
   double SDMassPTLinearAxisMax[7] = {1e5, 1e5, 8e4, 5e4, 5e4, 2e4, 1e3};
   double ZGPTLogAxisMin[7] = {1e2, 1e2, 1e2, 3e2, 1e2, 1e2, 1e1};
   double ZGPTLogAxisMax[7] = {1e6, 5e6, 2e6, 3e6, 5e6, 2e6, 1e5};
   double ZGPTLinearAxisMin[7] = {0, 0, 0, 0, 0, 0, 0};
   double ZGPTLinearAxisMax[7] = {1e5, 1.5e5, 2e5, 1.5e5, 1e5, 4e4, 2.5e3};

   double PPShift = 1;
   if(IsPP == true)
      PPShift = 10;
   double CBinShift[] = {1, 2, 2, 3, 1.5};

   TFile F(InputFile);

   for(int i = 0; i < (int)CBin.size(); i++)
   {
      double Shift = 1;
      if(IsPP == true)   // This factor of 2 comes from the rebinning of histograms (2 => 4)
         Shift = PPShift * 2;
      else
         Shift = CBinShift[i] * 2;

      vector<string> Names;
      for(int j = 0; j < (int)FBin.size(); j++)
         Names.push_back("H" + FBin[j] + "SDMassVsRecoJetPT_" + CBin[i]);

      TH2D HWorldSDMass("HWorldSDMass", ";SD Mass;Yield", 100, 0, 80, 100, 100 * Shift, 1e6 * Shift);
      Stack1DHistograms(F, HWorldSDMass, Names, FBin, OutputBase + "_SDMass_" + CBin[i],
         OutputBase, PROJECTION_Y, 1, 100, true);
      TH2D HWorldSDMassLinear("HWorldSDMassLinear", ";SD Mass;Yield", 100, 0, 80, 100, 0 * Shift, 2.5e5 * Shift);
      Stack1DHistograms(F, HWorldSDMassLinear, Names, FBin, OutputBase + "_SDMass_" + CBin[i] + "_Linear",
         OutputBase, PROJECTION_Y, 1, 100, false);

      TH2D HWorldJetPT("HWorldJetPT", ";Jet PT;Yield", 100, 80, 500, 100, 100 * Shift, 1e7 * Shift);
      Stack1DHistograms(F, HWorldJetPT, Names, FBin, OutputBase + "_JetPT_" + CBin[i],
         OutputBase, PROJECTION_X, 1, 100, true);
      TH2D HWorldJetPTLinear("HWorldJetPTLinear", ";Jet PT;Yield", 100, 80, 500, 100, 0 * Shift, 8e5 * Shift);
      Stack1DHistograms(F, HWorldJetPTLinear, Names, FBin, OutputBase + "_JetPT_" + CBin[i] + "_Linear",
         OutputBase, PROJECTION_X, 1, 100, false);
      
      for(int k = 0; k < (int)PTBin.size(); k++)
      {
         TH2D HWorldSDMassPT(Form("HWorldSDMassPT%d", k),
            Form("Jet PT = %d - %d;SD Mass;Yield", PTBinMin[k], PTBinMin[k+1]),
            100, 0, 80, 100, SDMassPTLogAxisMin[k] * Shift, SDMassPTLogAxisMax[k] * Shift);
         TH2D HWorldSDMassPTLinear(Form("HWorldSDMassPT%dLinear", k),
            Form("Jet PT = %d - %d;SD Mass;Yield", PTBinMin[k], PTBinMin[k+1]),
            100, 0, 80, 100, SDMassPTLinearAxisMin[k] * Shift, SDMassPTLinearAxisMax[k] * Shift);

         Stack1DHistograms(F, HWorldSDMassPT, Names, FBin, OutputBase + "_SDMass_" + CBin[i] + "_" + PTBin[k],
            OutputBase, PROJECTION_Y, PTBinIndex[k], PTBinIndex[k+1], true);
         Stack1DHistograms(F, HWorldSDMassPTLinear, Names, FBin, OutputBase + "_SDMass_" + CBin[i] + "_" + PTBin[k] + "_Linear",
            OutputBase, PROJECTION_Y, PTBinIndex[k], PTBinIndex[k+1], false);
      }
      
      Names.clear();
      for(int j = 0; j < (int)FBin.size(); j++)
         Names.push_back("H" + FBin[j] + "ZGVsRecoJetPT_" + CBin[i]);

      TH2D HWorldZG("HWorldZG", ";ZG;Yield", 100, 0.1, 0.5, 100, 1e4 * Shift, 1e6 * Shift);
      Stack1DHistograms(F, HWorldZG, Names, FBin, OutputBase + "_ZG_" + CBin[i],
         OutputBase, PROJECTION_Y, 1, 100, true);
      TH2D HWorldZGLinear("HWorldZGLinaer", ";ZG;Yield", 100, 0.1, 0.5, 100, 0 * Shift, 7e5 * Shift);
      Stack1DHistograms(F, HWorldZGLinear, Names, FBin, OutputBase + "_ZG_" + CBin[i] + "_Linear",
         OutputBase, PROJECTION_Y, 1, 100, false);
      
      for(int k = 0; k < (int)PTBin.size(); k++)
      {
         TH2D HWorldZGPT(Form("HWorldZGPT%d", k),
            Form("Jet PT = %d - %d;ZG;Yield", PTBinMin[k], PTBinMin[k+1]),
            100, 0.1, 0.5, 100, ZGPTLogAxisMin[k] * Shift, ZGPTLogAxisMax[k] * Shift);
         TH2D HWorldZGPTLinear(Form("HWorldZGPT%dLinear", k),
            Form("Jet PT = %d - %d;ZG;Yield", PTBinMin[k], PTBinMin[k+1]),
            100, 0.1, 0.5, 100, ZGPTLinearAxisMin[k] * Shift, ZGPTLinearAxisMax[k] * Shift);

         Stack1DHistograms(F, HWorldZGPT, Names, FBin, OutputBase + "_ZG_" + CBin[i] + "_" + PTBin[k],
            OutputBase, PROJECTION_Y, PTBinIndex[k], PTBinIndex[k+1], true);
         Stack1DHistograms(F, HWorldZGPTLinear, Names, FBin, OutputBase + "_ZG_" + CBin[i] + "_" + PTBin[k] + "_Linear",
            OutputBase, PROJECTION_Y, PTBinIndex[k], PTBinIndex[k+1], false);
      }
   }

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

void Stack1DHistograms(TFile &F, TH2D &HWorld, vector<string> Names, vector<string> Labels,
   string OutputBase, string Tag,
   int Projection, int ProjectionMin, int ProjectionMax, bool LogY)
{
   int Color[] = {kBlack, kRed, kBlue, kGreen - 3, kYellow, kCyan - 3};

   int N = Names.size();
   if(Labels.size() < N)
      Labels.resize(N);

   vector<TH1 *> H(N);
   for(int i = 0; i < N; i++)
   {
      TObject *Object = (TObject *)F.Get(Names[i].c_str());
      if(Object == NULL)
      {
         cerr << "Histogram " << Names[i] << " not found!" << endl;
         return;
      }
      else
      {
         if(Projection == PROJECTION_NONE)
            H[i] = (TH1 *)Object->Clone(Form("H%d", i));
         else if(Projection == PROJECTION_X)
            H[i] = ((TH2 *)Object)->ProjectionX(Form("H%d", i), ProjectionMin, ProjectionMax);
         else if(Projection == PROJECTION_Y)
            H[i] = ((TH2 *)Object)->ProjectionY(Form("H%d", i), ProjectionMin, ProjectionMax);
         else
         {
            cerr << "Bad projection setting!" << endl;
            return;
         }
      }
   }

   TCanvas C;
   
   HWorld.SetStats(0);
   HWorld.Draw();

   for(int i = H.size() - 2; i >= 0; i--)
      H[i]->Add(H[i+1]);

   for(int i = 0; i < (int)H.size(); i++)
   {
      H[i]->SetLineWidth(2);
      H[i]->SetLineColor(Color[i]);
      H[i]->SetFillColor(Color[i]);
      H[i]->Rebin(4);
   }

   for(int i = 0; i < (int)H.size(); i++)
      H[i]->Draw("bar same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   TLegend Legend(0.6, 0.8, 0.9, 0.5);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   for(int i = 0; i < (int)H.size(); i++)
      Legend.AddEntry(H[i], Labels[i].c_str(), "f");
   Legend.Draw();

   HWorld.Draw("hist same");

   C.SetLogy(LogY);

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   for(int i = 0; i < (int)H.size(); i++)
      if(H[i] != NULL)
         delete H[i];
}

