#include <iostream>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "HelperFunctions.h"

int main(int argc, char *argv[]);
void ProcessFile(PdfFileHelper &PdfFile, string FileName,
   string Prefix, vector<double> Thresholds,
   double Target, string Tag, string Name = "PT", int Type = TYPE_SMOOTH_SUPERTIGHT);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string CurvesFileName = CL.Get("curves");

   bool DoJet = CL.GetBool("dojet", true);
   bool DoMuon = CL.GetBool("domuon", true);
   bool DoEG = CL.GetBool("doeg", true);
   bool DoHT = CL.GetBool("doht", true);

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Scaling plots :D");
   
   TFile OutputFile(CurvesFileName.c_str(), "RECREATE");
   OutputFile.Close();

   vector<double> EGThresholds = {12, 15, 20, 25, 30};
   vector<double> MuonThresholds = {12, 15, 20, 25, 30};
   vector<double> JetThresholds = {15, 20, 25, 30, 40, 50, 75, 100, 150, 200};
   vector<double> CaloJetThresholds = {20, 40, 50, 75, 100, 125, 150, 175, 200};
   vector<double> HTThresholds = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
   vector<double> MHTThresholds = {10, 20, 30, 40, 50, 60};
   vector<double> METThresholds = {10, 20, 30, 40, 50, 60};

   if(DoJet == true)
   {
      ProcessFile(PdfFile, InputFileName, "Jet/Jet",             JetThresholds,  0.95, "TTbarJet",       "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkJet/TkJet",         JetThresholds,  0.95, "TTbarTkJet",     "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkJetCharged/TkJetCharged", JetThresholds,  0.95, "TTbarTkJetCharged",     "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkCaloJet/TkCaloJet", CaloJetThresholds,  0.95, "TTbarTkCaloJet", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "PuppiJetWide/PuppiJetWide",   JetThresholds,  0.95, "TTbarPuppiJetWide",  "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "PuppiJet/PuppiJet",   JetThresholds,  0.95, "TTbarPuppiJet",  "PT", TYPE_FITFIX);
   }
   if(DoMuon == true)
   {
      ProcessFile(PdfFile, InputFileName, "Muon/Muon",           MuonThresholds, 0.95, "TTbarMuon",      "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, "MuonKF/MuonKF",       MuonThresholds, 0.95, "TTbarMuonKF",    "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkGlbMuon/TkGlbMuon", MuonThresholds, 0.95, "TTbarTkGlbMuon",    "PT", TYPE_FITFIX);
   }
   if(DoEG == true)
   {
      ProcessFile(PdfFile, InputFileName, "EG/EG",               EGThresholds,   0.95, "TTbarEG",        "PT");
      ProcessFile(PdfFile, InputFileName, "EG/EG",               EGThresholds,   0.95, "TTbarEG",        "PTEta15");
      ProcessFile(PdfFile, InputFileName, "EG/EG",               EGThresholds,   0.95, "TTbarEG",        "PTEtaLarge");
      ProcessFile(PdfFile, InputFileName, "TkEGIso/TkEGIso",     EGThresholds,   0.95, "TTbarTkEG",      "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkEGIso/TkEGIso",     EGThresholds,   0.95, "TTbarTkEG",      "PTEta15", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkEGIso/TkEGIso",     EGThresholds,   0.95, "TTbarTkEG",      "PTEtaLarge", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkEMIso/TkEMIso",     EGThresholds,   0.95, "TTbarTkEM",      "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkEMIso/TkEMIso",     EGThresholds,   0.95, "TTbarTkEM",      "PTEta15", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkEMIso/TkEMIso",     EGThresholds,   0.95, "TTbarTkEM",      "PTEtaLarge", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso/TkIsoEGIso", EGThresholds,   0.95, "TTbarTkIsoEG",      "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso/TkIsoEGIso", EGThresholds,   0.95, "TTbarTkIsoEG",      "PTEta15", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso/TkIsoEGIso", EGThresholds,   0.95, "TTbarTkIsoEG",      "PTEtaLarge", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso/TkIsoEMIso", EGThresholds,   0.95, "TTbarTkIsoEM",      "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso/TkIsoEMIso", EGThresholds,   0.95, "TTbarTkIsoEM",      "PTEta15", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso/TkIsoEMIso", EGThresholds,   0.95, "TTbarTkIsoEM",      "PTEtaLarge", TYPE_FITFIX);
   }
   if(DoHT == true)
   {
      ProcessFile(PdfFile, InputFileName, "TkHT1/TkHT1",         HTThresholds,   0.95, "TTbarTkHT1",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT1/TkMHT1",       MHTThresholds,  0.95, "TTbarTkMHT1",    "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkHT2/TkHT2",         HTThresholds,   0.95, "TTbarTkHT2",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT2/TkMHT2",       MHTThresholds,  0.95, "TTbarTkMHT2",    "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkHT3/TkHT3",         HTThresholds,   0.95, "TTbarTkHT3",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT3/TkMHT3",       MHTThresholds,  0.95, "TTbarTkMHT3",    "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkHT4/TkHT4",         HTThresholds,   0.95, "TTbarTkHT4",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT4/TkMHT4",       MHTThresholds,  0.95, "TTbarTkMHT4",    "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkHT5/TkHT5",         HTThresholds,   0.95, "TTbarTkHT5",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT5/TkMHT5",       MHTThresholds,  0.95, "TTbarTkMHT5",    "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMET/TkMET",         METThresholds,  0.95, "TTbarTkMET",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiHT1/PuppiHT1",   HTThresholds,   0.95, "TTbarPuppiHT1",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT1/PuppiMHT1", MHTThresholds,  0.95, "TTbarPuppiMHT1", "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, "PuppiHT2/PuppiHT2",   HTThresholds,   0.95, "TTbarPuppiHT2",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT2/PuppiMHT2", MHTThresholds,  0.95, "TTbarPuppiMHT2", "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, "PuppiHT3/PuppiHT3",   HTThresholds,   0.95, "TTbarPuppiHT3",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT3/PuppiMHT3", MHTThresholds,  0.95, "TTbarPuppiMHT3", "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, "PuppiMET/PuppiMET",   METThresholds,  0.95, "TTbarPuppiMET",  "PT", TYPE_FIT);
   }
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ProcessFile(PdfFileHelper &PdfFile, string FileName,
   string Prefix, vector<double> Thresholds,
   double Target, string Tag, string Name, int Type)
{
   string TypeString = "UNKNOWN";
   if(Type == TYPE_FIT)
      TypeString = "Fit";
   if(Type == TYPE_FITFIX)
      TypeString = "Fit (plateau == 1)";
   if(Type == TYPE_SMOOTH_LOOSE)
      TypeString = "Stringterpolate (loose)";
   if(Type == TYPE_SMOOTH_TIGHT)
      TypeString = "Stringterpolate (tight)";
   if(Type == TYPE_SMOOTH_SUPERTIGHT)
      TypeString = "Stringterpolate (super tight)";
   if(Type == TYPE_SMOOTH_ULTRATIGHT)
      TypeString = "Stringterpolate (ultra tight)";

   vector<string> Text(11);
   Text[0] = "Plots for file";
   Text[1] = FileName;
   Text[2] = "";
   Text[3] = "...and object prefix";
   Text[4] = Prefix;
   Text[5] = "";
   Text[6] = "...and type";
   Text[7] = TypeString;
   Text[8] = "";
   Text[9] = "...and name";
   Text[10] = Name;
   PdfFile.AddTextPage(Text);

   TFile File(FileName.c_str());

   vector<double> CrossOver(Thresholds.size());

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      PdfFile.AddTextPage(Form("Threshold = %.1f", Thresholds[i]));
      if(Type == TYPE_SMOOTH_LOOSE || Type == TYPE_SMOOTH_TIGHT
         || Type == TYPE_SMOOTH_SUPERTIGHT || Type == TYPE_SMOOTH_ULTRATIGHT)
         CrossOver[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, Type);
      if(Type == TYPE_FIT)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false);
      if(Type == TYPE_FITFIX)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, true);
   }

   File.Close();
   
   PdfFile.AddTextPage("Scaling Curve for " + Prefix);
   
   TFile OutputFile("ScalingCurves.root", "UPDATE");

   TGraph G;
   G.SetNameTitle(Tag.c_str(), "");
   G.GetXaxis()->SetTitle("Threshold");
   G.GetYaxis()->SetTitle("95\% location");

   double Min = 0;
   double Max = Thresholds[Thresholds.size()-1];
   double Difference = Max - Min;
   Max = Max + Difference * 0.2;

   double YMin = 0;
   double YMax = -10000;
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      cout << Thresholds[i] << " " << CrossOver[i] << endl;
      if(CrossOver[i] != CrossOver[i])
         continue;
      if(CrossOver[i] < 0)
         continue;
      if(i == Thresholds.size() - 1 || CrossOver[i+1] > CrossOver[i])
      {
         G.SetPoint(G.GetN(), Thresholds[i], CrossOver[i]);
         if(YMin > CrossOver[i])
            YMin = CrossOver[i];
         if(YMax < CrossOver[i])
            YMax = CrossOver[i];
      }
   }
   Difference = YMax - YMin;
   YMax = YMax + Difference * 0.2;

   TF1 Function("Function", "pol1", Min, Max);
   G.Fit(&Function, "N");

   TH2D HWorld("HWorld", ";Thresholds;95\% location", 100, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw("axis");
   G.Draw("pl");
   Function.Draw("same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextColor(kMagenta);
   Latex.DrawLatex(0.15, 0.80, Form("p0 = %.03f #pm %.03f", Function.GetParameter(0), Function.GetParError(0)));
   Latex.DrawLatex(0.15, 0.75, Form("p1 = %.03f #pm %.03f", Function.GetParameter(1), Function.GetParError(1)));

   PdfFile.AddCanvas(Canvas);

   G.Write();

   OutputFile.Close();
}


