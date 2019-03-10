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

#include "PlotHelper4.h"
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

   string InputFileName =  CL.Get("input");
   string OutputFileName = CL.Get("output");
   string CurvesFileName = CL.Get("curves");

   bool DoJet  = CL.GetBool("DoJet", true);
   bool DoMuon = CL.GetBool("DoMu",  true);
   bool DoE    = CL.GetBool("DoE",   true);
   bool DoG    = CL.GetBool("DoG",   true);
   bool DoHT   = CL.GetBool("DoHT",  true);

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Scaling plots :D");

   PdfFile.SetAutomaticHomeButton();
   
   TFile OutputFile(CurvesFileName.c_str(), "RECREATE");
   OutputFile.Close();

   vector<double> EGThresholds = {12, 15, 20, 25, 30};
   vector<double> MuonThresholds = {12, 15, 20, 25, 30};
   vector<double> JetThresholds = {15, 20, 25, 30, 40, 50, 75, 100, 150, 200};
   vector<double> TkJetThresholds = {15, 20, 25, 30, 40, 50, 75, 100, 150};
   vector<double> CaloJetThresholds = {50, 75, 100, 125, 150, 175, 200};
   vector<double> HTThresholds = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
   vector<double> LowMHTThresholds = {20, 30, 40, 50, 60, 70};
   vector<double> MHTThresholds = {70, 80, 90, 100, 125, 150, 175};
   vector<double> LowMETThresholds = {20, 30, 40, 50, 60, 70};
   vector<double> METThresholds = {70, 80, 90, 100, 125, 150, 175};

   if(DoJet == true)
   {
      ProcessFile(PdfFile, InputFileName, "Jet",          JetThresholds,  0.95, "Jet",       "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkJet",        TkJetThresholds,  0.95, "TkJet",     "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkJetCharged", JetThresholds, 0.95, "TkJetCharged", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "TkCaloJet",    CaloJetThresholds, 0.95, "TkCaloJet", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "PuppiJetWide", JetThresholds,  0.95, "PuppiJetWide", "PT", TYPE_FITFIX);
      ProcessFile(PdfFile, InputFileName, "PuppiJet",     JetThresholds,  0.95, "PuppiJet",  "PT", TYPE_FITFIX);
   }
   if(DoMuon == true)
   {
      ProcessFile(PdfFile, InputFileName, "MuonIso",      MuonThresholds, 0.95, "MuonIso",   "PT", TYPE_FIT);
      ProcessFile(PdfFile, InputFileName, "MuonKFIso",    MuonThresholds, 0.95, "MuonKFIso", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMuonIso",    MuonThresholds, 0.95, "TkMuonIso", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkGlbMuonIso", MuonThresholds, 0.95, "TkGlbMuonIso", "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PFMuonIso",    MuonThresholds, 0.95, "PFMuonIso", "PT", TYPE_SMOOTH_TIGHT);
   }
   if(DoE == true)
   {
      ProcessFile(PdfFile, InputFileName, "EGElectron",   EGThresholds,   0.95, "EG",        "PT");
      ProcessFile(PdfFile, InputFileName, "EGElectron",   EGThresholds,   0.95, "EG",        "PTEta15");
      ProcessFile(PdfFile, InputFileName, "EGElectron",   EGThresholds,   0.95, "EG",        "PTEtaLarge");
      ProcessFile(PdfFile, InputFileName, "TkEGIso",      EGThresholds,   0.95, "TkEG",      "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkEGIso",      EGThresholds,   0.95, "TkEG",      "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkEGIso",      EGThresholds,   0.95, "TkEG",      "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso",   EGThresholds,   0.95, "TkIsoEG",   "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso",   EGThresholds,   0.95, "TkIsoEG",   "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEGIso",   EGThresholds,   0.95, "TkIsoEG",   "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoG == true)
   {
      ProcessFile(PdfFile, InputFileName, "EGPhoton",     EGThresholds,   0.95, "EG",        "PT");
      ProcessFile(PdfFile, InputFileName, "EGPhoton",     EGThresholds,   0.95, "EG",        "PTEta15");
      ProcessFile(PdfFile, InputFileName, "EGPhoton",     EGThresholds,   0.95, "EG",        "PTEtaLarge");
      ProcessFile(PdfFile, InputFileName, "TkEMIso",      EGThresholds,   0.95, "TkEM",      "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkEMIso",      EGThresholds,   0.95, "TkEM",      "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkEMIso",      EGThresholds,   0.95, "TkEM",      "PTEtaLarge", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso",   EGThresholds,   0.95, "TkIsoEM",   "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso",   EGThresholds,   0.95, "TkIsoEM",   "PTEta15", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkIsoEMIso",   EGThresholds,   0.95, "TkIsoEM",   "PTEtaLarge", TYPE_SMOOTH_TIGHT);
   }
   if(DoHT == true)
   {
      ProcessFile(PdfFile, InputFileName, "TkHT1",        HTThresholds,   0.95, "TkHT1",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT1",       MHTThresholds,  0.95, "TkMHT1",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMHT1",       LowMHTThresholds,  0.95, "LowTkMHT1",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkHT2",        HTThresholds,   0.95, "TkHT2",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT2",       MHTThresholds,  0.95, "TkMHT2",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMHT2",       LowMHTThresholds,  0.95, "LowTkMHT2",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkHT3",        HTThresholds,   0.95, "TkHT3",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT3",       MHTThresholds,  0.95, "TkMHT3",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMHT3",       LowMHTThresholds,  0.95, "LowTkMHT3",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkHT4",        HTThresholds,   0.95, "TkHT4",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT4",       MHTThresholds,  0.95, "TkMHT4",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMHT4",       LowMHTThresholds,  0.95, "LowTkMHT4",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkHT5",        HTThresholds,   0.95, "TkHT5",     "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "TkMHT5",       MHTThresholds,  0.95, "TkMHT5",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMHT5",       LowMHTThresholds,  0.95, "LowTkMHT5",    "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMET",        METThresholds,  0.95, "TkMET",     "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "TkMET",        LowMETThresholds,  0.95, "LowTkMET",     "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiHT1",     HTThresholds,   0.95, "PuppiHT1",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT1",    MHTThresholds,  0.95, "PuppiMHT1", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT1",    LowMHTThresholds,  0.95, "LowPuppiMHT1", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiHT2",     HTThresholds,   0.95, "PuppiHT2",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT2",    MHTThresholds,  0.95, "PuppiMHT2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT2",    LowMHTThresholds,  0.95, "LowPuppiMHT2", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiHT3",     HTThresholds,   0.95, "PuppiHT3",  "PT", TYPE_SMOOTH_TIGHT);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT3",    MHTThresholds,  0.95, "PuppiMHT3", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiMHT3",    LowMHTThresholds,  0.95, "LowPuppiMHT3", "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiMET",     METThresholds,  0.95, "PuppiMET",  "PT", TYPE_FITFIX2);
      ProcessFile(PdfFile, InputFileName, "PuppiMET",     LowMETThresholds,  0.95, "LowPuppiMET",  "PT", TYPE_FITFIX2);
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
   if(Type == TYPE_FITFIX2)
      TypeString = "Fit (plateau == 1 && float baseline)";
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

   Prefix = Prefix + "/" + Prefix;

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
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, false, false);
      if(Type == TYPE_FITFIX)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, true, false);
      if(Type == TYPE_FITFIX2)
         CrossOver[i] = FitTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%s_%s_%06d", Prefix.c_str(), Name.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%s_%s_000000", Prefix.c_str(), Name.c_str())), Target, false, false, true, true);
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


