#include <iostream>
#include <algorithm>
using namespace std;

#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TAxis.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"

int main(int argc, char *argv[]);
void DrawComparisonPlots(PsFileHelper &PsFile, TH1D &H1, TH1D &H2, TH1D &HI, bool Flip, string Title, bool IsPhi = false);
string GiveMeComponentLabel(int Index);
int GetIndex(int X, int Y);

int main(int argc, char *argv[])
{
   string InputFileName = "PartialCrossSection300.root";
   if(argc > 1)
      InputFileName = argv[1];

   TFile File(InputFileName.c_str());

   vector<TH1D *> HM2emLoose, HM2eeLoose;
   vector<TH1D *> HM2emTight, HM2eeTight;
   vector<TH1D *> HM2emOpt, HM2eeOpt;
   vector<TH1D *> HPhiemLoose, HPhieeLoose;
   vector<TH1D *> HPhiemTight, HPhieeTight;
   vector<TH1D *> HPhiemOpt, HPhieeOpt;
   for(int i = 0; i < 92; i++)
   {
      HM2emLoose.push_back((TH1D *)File.Get(Form("HM2%demLoose", i)));
      HM2emTight.push_back((TH1D *)File.Get(Form("HM2%demTight", i)));
      HM2emOpt.push_back((TH1D *)File.Get(Form("HM2%demOpt", i)));
      HPhiemLoose.push_back((TH1D *)File.Get(Form("HPhi%demLoose", i)));
      HPhiemTight.push_back((TH1D *)File.Get(Form("HPhi%demTight", i)));
      HPhiemOpt.push_back((TH1D *)File.Get(Form("HPhi%demOpt", i)));
      HM2eeLoose.push_back((TH1D *)File.Get(Form("HM2%deeLoose", i)));
      HM2eeTight.push_back((TH1D *)File.Get(Form("HM2%deeTight", i)));
      HM2eeOpt.push_back((TH1D *)File.Get(Form("HM2%deeOpt", i)));
      HPhieeLoose.push_back((TH1D *)File.Get(Form("HPhi%deeLoose", i)));
      HPhieeTight.push_back((TH1D *)File.Get(Form("HPhi%deeTight", i)));
      HPhieeOpt.push_back((TH1D *)File.Get(Form("HPhi%deeOpt", i)));
   }

   PsFileHelper PsFileEMLoose("PartialCrossSectionResultEMLoose.ps");
   PsFileHelper PsFileEMTight("PartialCrossSectionResultEMTight.ps");
   PsFileHelper PsFileEMOpt("PartialCrossSectionResultEMOpt.ps");
   PsFileHelper PsFileEELoose("PartialCrossSectionResultEELoose.ps");
   PsFileHelper PsFileEETight("PartialCrossSectionResultEETight.ps");
   PsFileHelper PsFileEEOpt("PartialCrossSectionResultEEOpt.ps");

   PsFileEMLoose.AddTextPage("A bunch of plots for us to look at");
   PsFileEMTight.AddTextPage("A bunch of plots for us to look at");
   PsFileEMOpt.AddTextPage("A bunch of plots for us to look at");
   PsFileEELoose.AddTextPage("A bunch of plots for us to look at");
   PsFileEETight.AddTextPage("A bunch of plots for us to look at");
   PsFileEEOpt.AddTextPage("A bunch of plots for us to look at");

   PsFileEMLoose.SetAutomaticHomeButton(true);
   PsFileEMTight.SetAutomaticHomeButton(true);
   PsFileEMOpt.SetAutomaticHomeButton(true);
   PsFileEELoose.SetAutomaticHomeButton(true);
   PsFileEETight.SetAutomaticHomeButton(true);
   PsFileEEOpt.SetAutomaticHomeButton(true);
   
   vector<string> Labels;
   vector<string> Destinations;
   for(int i = 1; i <= 14; i++)
   {
      Labels.push_back(GiveMeComponentLabel(i - 1) + " x others");
      Destinations.push_back(Form("MARKER_%d", i));
   }

   PsFileEMLoose.AddTableOfContentPage(Labels, Destinations);
   PsFileEMTight.AddTableOfContentPage(Labels, Destinations);
   PsFileEMOpt.AddTableOfContentPage(Labels, Destinations);
   PsFileEELoose.AddTableOfContentPage(Labels, Destinations);
   PsFileEETight.AddTableOfContentPage(Labels, Destinations);
   PsFileEEOpt.AddTableOfContentPage(Labels, Destinations);

   PsFileEMLoose.InsertNamedDestination("HomePage");
   PsFileEMTight.InsertNamedDestination("HomePage");
   PsFileEMOpt.InsertNamedDestination("HomePage");
   PsFileEELoose.InsertNamedDestination("HomePage");
   PsFileEETight.InsertNamedDestination("HomePage");
   PsFileEEOpt.InsertNamedDestination("HomePage");

   for(int i = 1; i <= 14; i++)
   {
      PsFileEMLoose.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");
      PsFileEMTight.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");
      PsFileEMOpt.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");
      PsFileEELoose.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");
      PsFileEETight.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");
      PsFileEEOpt.AddTextPage(GiveMeComponentLabel(i - 1) + " x others");

      PsFileEMLoose.InsertNamedDestination(Form("MARKER_%d", i));
      PsFileEMTight.InsertNamedDestination(Form("MARKER_%d", i));
      PsFileEMOpt.InsertNamedDestination(Form("MARKER_%d", i));
      PsFileEELoose.InsertNamedDestination(Form("MARKER_%d", i));
      PsFileEETight.InsertNamedDestination(Form("MARKER_%d", i));
      PsFileEEOpt.InsertNamedDestination(Form("MARKER_%d", i));

      for(int j = 1; j <= 14; j++)
      {
         if(i == j)
            continue;

         int IndexIJ = GetIndex(i - 1, j - 1);
         int IndexII = GetIndex(i - 1, i - 1);
         int IndexJJ = GetIndex(j - 1, j - 1);

         bool Flip = false;
         if(IndexIJ < 0)
         {
            Flip = true;
            IndexIJ = -IndexIJ;
         }

         string Title = GiveMeComponentLabel(i - 1) + " x " + GiveMeComponentLabel(j - 1);

         DrawComparisonPlots(PsFileEMLoose, *HM2emLoose[IndexII], *HM2emLoose[IndexJJ], *HM2emLoose[IndexIJ],
            Flip, Title);
         DrawComparisonPlots(PsFileEMTight, *HM2emTight[IndexII], *HM2emTight[IndexJJ], *HM2emTight[IndexIJ],
            Flip, Title);
         DrawComparisonPlots(PsFileEMOpt, *HM2emOpt[IndexII], *HM2emOpt[IndexJJ], *HM2emOpt[IndexIJ],
            Flip, Title);
         DrawComparisonPlots(PsFileEELoose, *HM2eeLoose[IndexII], *HM2eeLoose[IndexJJ], *HM2eeLoose[IndexIJ],
            Flip, Title);
         DrawComparisonPlots(PsFileEETight, *HM2eeTight[IndexII], *HM2eeTight[IndexJJ], *HM2eeTight[IndexIJ],
            Flip, Title);
         DrawComparisonPlots(PsFileEEOpt, *HM2eeOpt[IndexII], *HM2eeOpt[IndexJJ], *HM2eeOpt[IndexIJ],
            Flip, Title);
         
         DrawComparisonPlots(PsFileEMLoose, *HPhiemLoose[IndexII], *HPhiemLoose[IndexJJ], *HPhiemLoose[IndexIJ],
            Flip, Title, true);
         DrawComparisonPlots(PsFileEMTight, *HPhiemTight[IndexII], *HPhiemTight[IndexJJ], *HPhiemTight[IndexIJ],
            Flip, Title, true);
         DrawComparisonPlots(PsFileEMOpt, *HPhiemOpt[IndexII], *HPhiemOpt[IndexJJ], *HPhiemOpt[IndexIJ],
            Flip, Title, true);
         DrawComparisonPlots(PsFileEELoose, *HPhieeLoose[IndexII], *HPhieeLoose[IndexJJ], *HPhieeLoose[IndexIJ],
            Flip, Title, true);
         DrawComparisonPlots(PsFileEETight, *HPhieeTight[IndexII], *HPhieeTight[IndexJJ], *HPhieeTight[IndexIJ],
            Flip, Title, true);
         DrawComparisonPlots(PsFileEEOpt, *HPhieeOpt[IndexII], *HPhieeOpt[IndexJJ], *HPhieeOpt[IndexIJ],
            Flip, Title, true);
      }
   }

   PsFileEMLoose.AddTimeStampPage();
   PsFileEMTight.AddTimeStampPage();
   PsFileEMOpt.AddTimeStampPage();
   PsFileEELoose.AddTimeStampPage();
   PsFileEETight.AddTimeStampPage();
   PsFileEEOpt.AddTimeStampPage();
   PsFileEMLoose.Close();
   PsFileEMTight.Close();
   PsFileEMOpt.Close();
   PsFileEELoose.Close();
   PsFileEETight.Close();
   PsFileEEOpt.Close();

   File.Close();

   return 0;
}

void DrawComparisonPlots(PsFileHelper &PsFile, TH1D &H1, TH1D &H2, TH1D &HI, bool Flip, string Title, bool IsPhi)
{
   double Min = 0, Max = 65;
   if(IsPhi == true)
   {
      Min = -3.14159;
      Max = 3.14159;
   }

   TH1D HWorld("HWorld", Title.c_str(), 100, Min, Max);
   HWorld.SetStats(0);
   
   if(IsPhi == false)
      HWorld.GetXaxis()->SetTitle("M2");
   else
      HWorld.GetXaxis()->SetTitle("Phi");

   if(Flip == true)
      HI.Scale(-1);

   TH1D *HClone = (TH1D *)HI.Clone("IAmAClone");
   HClone->Scale(-1);

   H1.SetLineWidth(2);
   H1.SetLineColor(kBlack);
   H2.SetLineWidth(2);
   H2.SetLineColor(kBlue);
   HI.SetLineWidth(2);
   HI.SetLineColor(kRed);
   HClone->SetLineWidth(1);
   HClone->SetLineColor(kRed);

   TCanvas C;

   HWorld.SetMaximum(max(H1.GetMaximum(), H2.GetMaximum()) * 1.2);
   HWorld.SetMinimum(0.0);
   HWorld.Draw();
   H1.Draw("same");
   H2.Draw("same");
   HI.Draw("same");
   HClone->Draw("same");

   C.SetLogy(false);
   PsFile.AddCanvas(C);

   HWorld.SetMaximum(max(H1.GetMaximum(), H2.GetMaximum()) * 2);
   HWorld.SetMinimum(HWorld.GetMaximum() / 1e6);
   HWorld.Draw();
   H1.Draw("same");
   H2.Draw("same");
   HI.Draw("same");
   HClone->Draw("same");
   
   C.SetLogy(true);
   PsFile.AddCanvas(C);
   
   if(Flip == true)
      HI.Scale(-1);
}

string GiveMeComponentLabel(int Index)
{
   switch(Index)
   {
   case 0:    return "A1ZZR";
   case 1:    return "A1ZZI";
   case 2:    return "A2ZZR";
   case 3:    return "A2ZZI";
   case 4:    return "A3ZZR";
   case 5:    return "A3ZZI";
   case 6:    return "A2ZAR";
   case 7:    return "A2ZAI";
   case 8:    return "A3ZAR";
   case 9:    return "A3ZAI";
   case 10:   return "A2AAR";
   case 11:   return "A2AAI";
   case 12:   return "A3AAR";
   case 13:   return "A3AAI";
   }

   return "N/A";
}

int GetIndex(int X, int Y)
{
   if(X < 0 || Y < 0 || X >= 14 || Y >= 14)
      return -1;

   int Indices[14][14] =
      {{1,   0,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25},
      {0,    1, -15,  14, -17,  16, -19,  18, -21,  20, -23,  22, -25,  24},
      {14, -15,   2,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36},
      {15,  14,  26,   3,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46},
      {16, -17,  27,  37,   4,  47,  48,  49,  50,  51,  52,  53,  54,  55},
      {17,  16,  28,  38,  47,   5,  56,  57,  58,  59,  60,  61,  62,  63},
      {18, -19,  29,  39,  48,  56,   6,  64,  65,  66,  67,  68,  69,  70},
      {19,  18,  30,  40,  49,  57,  64,   7,  71,  72,  73,  74,  75,  76},
      {20, -21,  31,  41,  50,  58,  65,  71,   8,  77,  78,  79,  80,  81},
      {21,  20,  32,  42,  51,  59,  66,  72,  77,   9,  82,  83,  84,  85},
      {22, -23,  33,  43,  52,  60,  67,  73,  78,  82,  10,  86,  87,  88},
      {23,  22,  34,  44,  53,  61,  68,  74,  79,  83,  86,  11,  89,  90},
      {24, -25,  35,  45,  54,  62,  69,  75,  80,  84,  87,  89,  12,  91},
      {25,  24,  36,  46,  55,  63,  70,  76,  81,  85,  88,  90,  91,  13}};

   return Indices[X][Y];
}




