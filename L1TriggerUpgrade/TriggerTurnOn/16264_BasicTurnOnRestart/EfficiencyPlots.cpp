#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

class Graphs;
int main();
TGraphAsymmErrors *Divide(TFile &F1, string N1, TFile &F2, string N2, int Rebin = 1);
void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title, string Tag1, string Tag2);
void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title, string Tag);
void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, string N, string Title);

class Graphs
{
public:
   TGraphAsymmErrors *GPT;
   TGraphAsymmErrors *GPT_Rebin;
   TGraphAsymmErrors *GPT_Rebin2;
   TGraphAsymmErrors *GPTEta10;
   TGraphAsymmErrors *GPTEta10_Rebin;
   TGraphAsymmErrors *GPTEta10_Rebin2;
   TGraphAsymmErrors *GPTEtaLarge;
   TGraphAsymmErrors *GPTEtaLarge_Rebin;
   TGraphAsymmErrors *GPTEtaLarge_Rebin2;
   TGraphAsymmErrors *GEta;
   TGraphAsymmErrors *GEtaPT20;
   TGraphAsymmErrors *GEtaPT25;
   TGraphAsymmErrors *GEtaPT200;
public:
   Graphs(TFile &F1, string Tag1, TFile &F2, string Tag2, string Type = "TkEG", string PU = "PU140")
   {
      GPT                = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         5);
      GPT_Rebin          = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         -1);
      GPT_Rebin2         = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         -2);
      GPTEta10           = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    5);
      GPTEta10_Rebin     = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    -1);
      GPTEta10_Rebin2    = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    -2);
      GPTEtaLarge        = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", 5);
      GPTEtaLarge_Rebin  = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", -1);
      GPTEtaLarge_Rebin2 = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", -2);
      GEta               = Divide(F1, Tag1 + "_Eta_000000",        F2, Tag2 + "_Eta_000000",        2);
      GEtaPT20           = Divide(F1, Tag1 + "_EtaPT20_000000",    F2, Tag2 + "_EtaPT20_000000",    2);
      GEtaPT25           = Divide(F1, Tag1 + "_EtaPT25_000000",    F2, Tag2 + "_EtaPT25_000000",    2);
      GEtaPT200          = Divide(F1, Tag1 + "_EtaPT200_000000",   F2, Tag2 + "_EtaPT200_000000",   2);

      GPT->SetTitle((Type + ", PT, " + PU).c_str());
      GPT_Rebin->SetTitle((Type + ", PT, " + PU).c_str());
      GPT_Rebin2->SetTitle((Type + ", PT, " + PU).c_str());
      GPTEta10->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
      GPTEta10_Rebin->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
      GPTEta10_Rebin2->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
      GPTEtaLarge->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
      GPTEtaLarge_Rebin->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
      GPTEtaLarge_Rebin2->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
      GEta->SetTitle((Type + ", Eta, " + PU).c_str());
      GEtaPT20->SetTitle((Type + ", eta (PT > 20), " + PU).c_str());
      GEtaPT25->SetTitle((Type + ", eta (PT > 25), " + PU).c_str());
      GEtaPT200->SetTitle((Type + ", eta (PT > 200), " + PU).c_str());
   
      GPT->GetXaxis()->SetTitle("PT");
      GPT_Rebin->GetXaxis()->SetTitle("PT");
      GPT_Rebin2->GetXaxis()->SetTitle("PT");
      GPTEta10->GetXaxis()->SetTitle("PT");
      GPTEta10_Rebin->GetXaxis()->SetTitle("PT");
      GPTEta10_Rebin2->GetXaxis()->SetTitle("PT");
      GPTEtaLarge->GetXaxis()->SetTitle("PT");
      GPTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
      GPTEtaLarge_Rebin2->GetXaxis()->SetTitle("PT");
      GEta->GetXaxis()->SetTitle("Eta");
      GEtaPT20->GetXaxis()->SetTitle("Eta");
      GEtaPT25->GetXaxis()->SetTitle("Eta");
      GEtaPT200->GetXaxis()->SetTitle("Eta");
   }
   ~Graphs()
   {
      if(GPT == NULL)                 delete GPT;
      if(GPT_Rebin == NULL)           delete GPT_Rebin;         
      if(GPT_Rebin2 == NULL)          delete GPT_Rebin2;
      if(GPTEta10 == NULL)            delete GPTEta10;
      if(GPTEta10_Rebin == NULL)      delete GPTEta10_Rebin;
      if(GPTEta10_Rebin2 == NULL)     delete GPTEta10_Rebin2;
      if(GPTEtaLarge == NULL)         delete GPTEtaLarge;
      if(GPTEtaLarge_Rebin == NULL)   delete GPTEtaLarge_Rebin;
      if(GPTEtaLarge_Rebin2 == NULL)  delete GPTEtaLarge_Rebin2;
      if(GEta == NULL)                delete GEta;
      if(GEtaPT20 == NULL)            delete GEtaPT20;
      if(GEtaPT25 == NULL)            delete GEtaPT25;
      if(GEtaPT200 == NULL)           delete GEtaPT200;
   }
   void AddIndividualPlots(PdfFileHelper &PdfFile)
   {
      PdfFile.AddPlot(GPT, "ap");
      PdfFile.AddPlot(GPT_Rebin, "ap");
      PdfFile.AddPlot(GPT_Rebin2, "ap");
      PdfFile.AddPlot(GPTEta10, "ap");
      PdfFile.AddPlot(GPTEta10_Rebin, "ap");
      PdfFile.AddPlot(GPTEta10_Rebin2, "ap");
      PdfFile.AddPlot(GPTEtaLarge, "ap");
      PdfFile.AddPlot(GPTEtaLarge_Rebin, "ap");
      PdfFile.AddPlot(GPTEtaLarge_Rebin2, "ap");
      PdfFile.AddPlot(GEta, "ap");
      PdfFile.AddPlot(GEtaPT20, "ap");
      PdfFile.AddPlot(GEtaPT25, "ap");
      PdfFile.AddPlot(GEtaPT200, "ap");
   }
};

int main()
{
   SetThesisStyle();

   TFile FWENu140("Result/Combined/WToEnu140PU.root", "PU140");
   TFile FWENu200("Result/Combined/WToEnu200PU.root", "PU200");
   TFile FWENu140Tyler("Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "PU140");
   TFile FWENu200Tyler("Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", "PU200");
   TFile FHgg140("Result/Combined/Hgg140PU.root", "PU140");
   TFile FHgg200("Result/Combined/Hgg200PU.root", "PU200");
   TFile FTT140("Result/Combined/TTBar140PU.root", "PU140");
   TFile FTT200("Result/Combined/TTBar200PU.root", "PU200");

   Graphs TkEG140(FWENu140, "TkEG/TkEG", FWENu140, "TkEG/TkEGNoMatching", "TkEG", "PU140");
   Graphs TkEG200(FWENu200, "TkEG/TkEG", FWENu200, "TkEG/TkEGNoMatching", "TkEG", "PU200");
   Graphs TkIsoEG140(FWENu140, "TkIsoEG/TkIsoEG", FWENu140, "TkIsoEG/TkIsoEGNoMatching", "TkIsoEG", "PU140");
   Graphs TkIsoEG200(FWENu200, "TkIsoEG/TkIsoEG", FWENu200, "TkIsoEG/TkIsoEGNoMatching", "TkIsoEG", "PU200");
   Graphs EGEle140(FWENu140, "EGEle/EGEle", FWENu140, "EGEle/EGEleNoMatching", "EGEle", "PU140");
   Graphs EGEle200(FWENu200, "EGEle/EGEle", FWENu200, "EGEle/EGEleNoMatching", "EGEle", "PU200");

   Graphs TkEGTyler140(FWENu140Tyler, "TkEG/TkEG", FWENu140Tyler, "TkEG/TkEGNoMatching", "TkEG (Tyler)", "PU140");
   Graphs TkEGTyler200(FWENu200Tyler, "TkEG/TkEG", FWENu200Tyler, "TkEG/TkEGNoMatching", "TkEG (Tyler)", "PU200");
   Graphs TkIsoEGTyler140(FWENu140Tyler, "TkIsoEG/TkIsoEG", FWENu140Tyler, "TkIsoEG/TkIsoEGNoMatching", "TkIsoEG (Tyler)", "PU140");
   Graphs TkIsoEGTyler200(FWENu200Tyler, "TkIsoEG/TkIsoEG", FWENu200Tyler, "TkIsoEG/TkIsoEGNoMatching", "TkIsoEG (Tyler)", "PU200");
   Graphs EGEleTyler140(FWENu140Tyler, "EGEle/EGEle", FWENu140Tyler, "EGEle/EGEleNoMatching", "EG (Tyler)", "PU140");
   Graphs EGEleTyler200(FWENu200Tyler, "EGEle/EGEle", FWENu200Tyler, "EGEle/EGEleNoMatching", "EG (Tyler)", "PU200");
   Graphs IsoEGTyler140(FWENu140Tyler, "IsoEG/IsoEG", FWENu140Tyler, "IsoEG/IsoEGNoMatching", "IsoEG (Tyler)", "PU140");
   Graphs IsoEGTyler200(FWENu200Tyler, "IsoEG/IsoEG", FWENu200Tyler, "IsoEG/IsoEGNoMatching", "IsoEG (Tyler)", "PU200");
   
   Graphs TkEM140(FHgg140, "TkEM/TkEM", FHgg140, "TkEM/TkEMNoMatching", "TkEM", "PU140");
   Graphs TkEM200(FHgg200, "TkEM/TkEM", FHgg200, "TkEM/TkEMNoMatching", "TkEM", "PU200");
   Graphs EG140(FHgg140, "EG/EG", FHgg140, "EG/EGNoMatching", "EG", "PU140");
   Graphs EG200(FHgg200, "EG/EG", FHgg200, "EG/EGNoMatching", "EG", "PU200");
   Graphs IsoEG140(FHgg140, "IsoEG/IsoEG", FHgg140, "IsoEG/IsoEGNoMatching", "IsoEG", "PU140");
   Graphs IsoEG200(FHgg200, "IsoEG/IsoEG", FHgg200, "IsoEG/IsoEGNoMatching", "IsoEG", "PU200");

   Graphs TkEMEG140(FHgg140, "TkEM/TkEM", FHgg140, "EG/EG", "TkEM/EG", "PU140");
   Graphs TkEMEG200(FHgg200, "TkEM/TkEM", FHgg200, "EG/EG", "TkEM/EG", "PU200");
   
   Graphs TkEGEG140(FWENu140, "TkEG/TkEG", FWENu140, "EGEle/EGEle", "TkEG/EG", "PU140");
   Graphs TkEGEG200(FWENu200, "TkEG/TkEG", FWENu200, "EGEle/EGEle", "TkEG/EG", "PU200");
   Graphs TkEGEGTyler140(FWENu140Tyler, "TkEG/TkEG", FWENu140Tyler, "EGEle/EGEle", "TkEG/EG (Tyler)", "PU140");
   Graphs TkEGEGTyler200(FWENu200Tyler, "TkEG/TkEG", FWENu200Tyler, "EGEle/EGEle", "TkEG/EG (Tyler)", "PU200");

   Graphs Jet140(FTT140, "Jet/Jet", FTT140, "Jet/JetNoMatching", "Jet", "PU140");
   Graphs Jet200(FTT200, "Jet/Jet", FTT200, "Jet/JetNoMatching", "Jet", "PU200");
   Graphs TkJet140(FTT140, "TkJet/TkJet", FTT140, "TkJet/TkJetNoMatching", "TkJet", "PU140");
   Graphs TkJet200(FTT200, "TkJet/TkJet", FTT200, "TkJet/TkJetNoMatching", "TkJet", "PU200");
   Graphs JetGen140(FTT140, "JetGen/JetGen", FTT140, "JetGen/JetGenNoMatching", "JetGen", "PU140");
   Graphs JetGen200(FTT200, "JetGen/JetGen", FTT200, "JetGen/JetGenNoMatching", "JetGen", "PU200");
   Graphs TkJetGen140(FTT140, "TkJetGen/TkJetGen", FTT140, "TkJetGen/TkJetGenNoMatching", "TkJetGen", "PU140");
   Graphs TkJetGen200(FTT200, "TkJetGen/TkJetGen", FTT200, "TkJetGen/TkJetGenNoMatching", "TkJetGen", "PU200");

   PdfFileHelper PdfFile("ResultEfficiencyPlots.pdf");
   PdfFile.AddTextPage("Efficiency plots");
   
   PdfFileHelper PdfFile2("ResultIndividualEfficiencyPlots.pdf");
   PdfFile2.AddTextPage("Individual efficiency plots");

   vector<string> Explanation(15);
   Explanation[0] = "Look at gen-electron pt/eta for those within acceptance";
   Explanation[1] = "";
   Explanation[2] = "Numerator = Gen-particle spectrum";
   Explanation[3] = "Denominator = Gen-particle spectrum & track";
   Explanation[4] = "      EG/IsoEG/EM/jet object match";
   Explanation[5] = "";
   Explanation[6] = "Electron ones from W->e#nu sample";
   Explanation[7] = "EM ones from H->#gamma#gamma sample";
   Explanation[8] = "Jets are from ttbar sample";
   Explanation[9] = "   result with gen-jets are at the end";
   Explanation[10] = "";
   Explanation[11] = "Watch out for PT spectrum!";
   PdfFile.AddTextPage(Explanation);
   PdfFile2.AddTextPage(Explanation);

   PdfFile.AddTextPage("Gen-spectra");

   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_PT_000000",          "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_PT_000000",          "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FWENu140, "TkEG/TkEGNoMatching_Eta_000000",         "W->e#nu electrons (PU 140)");
   AddSpectrum(PdfFile, FWENu200, "TkEG/TkEGNoMatching_Eta_000000",         "W->e#nu electrons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_PT_000000",          "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_PT_000000",          "H->#gamma#gamma photons (PU 200)");
   AddSpectrum(PdfFile, FHgg140,  "TkEM/TkEMNoMatching_Eta_000000",         "H->#gamma#gamma photons (PU 140)");
   AddSpectrum(PdfFile, FHgg200,  "TkEM/TkEMNoMatching_Eta_000000",         "H->#gamma#gamma photons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJet/TkJetNoMatching_PT_000000",        "TTbar partons (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJet/TkJetNoMatching_PT_000000",        "TTbar partons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJet/TkJetNoMatching_Eta_000000",       "TTbar partons (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJet/TkJetNoMatching_Eta_000000",       "TTbar partons (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJetGen/TkJetGenNoMatching_PT_000000",  "TTbar gen-jets (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJetGen/TkJetGenNoMatching_PT_000000",  "TTbar gen-jets (PU 200)");
   AddSpectrum(PdfFile, FTT140,   "TkJetGen/TkJetGenNoMatching_Eta_000000", "TTbar gen-jets (PU 140)");
   AddSpectrum(PdfFile, FTT200,   "TkJetGen/TkJetGenNoMatching_Eta_000000", "TTbar gen-jets (PU 200)");

   TkEG140.AddIndividualPlots(PdfFile2);
   TkEG200.AddIndividualPlots(PdfFile2);
   TkIsoEG140.AddIndividualPlots(PdfFile2);
   TkIsoEG200.AddIndividualPlots(PdfFile2);

   TkEGTyler140.AddIndividualPlots(PdfFile2);
   TkEGTyler200.AddIndividualPlots(PdfFile2);
   TkIsoEGTyler140.AddIndividualPlots(PdfFile2);
   TkIsoEGTyler200.AddIndividualPlots(PdfFile2);
   EGEleTyler140.AddIndividualPlots(PdfFile2);
   EGEleTyler200.AddIndividualPlots(PdfFile2);
   IsoEGTyler140.AddIndividualPlots(PdfFile2);
   IsoEGTyler200.AddIndividualPlots(PdfFile2);
   
   TkEM140.AddIndividualPlots(PdfFile2);
   TkEM200.AddIndividualPlots(PdfFile2);
   EG140.AddIndividualPlots(PdfFile2);
   EG200.AddIndividualPlots(PdfFile2);
   IsoEG140.AddIndividualPlots(PdfFile2);
   IsoEG200.AddIndividualPlots(PdfFile2);

   TkEMEG140.AddIndividualPlots(PdfFile2);
   TkEMEG200.AddIndividualPlots(PdfFile2);
   
   TkEGEG140.AddIndividualPlots(PdfFile2);
   TkEGEG200.AddIndividualPlots(PdfFile2);
   TkEGEGTyler140.AddIndividualPlots(PdfFile2);
   TkEGEGTyler200.AddIndividualPlots(PdfFile2);

   Jet140.AddIndividualPlots(PdfFile2);
   Jet200.AddIndividualPlots(PdfFile2);
   TkJet140.AddIndividualPlots(PdfFile2);
   TkJet200.AddIndividualPlots(PdfFile2);
   JetGen140.AddIndividualPlots(PdfFile2);
   JetGen200.AddIndividualPlots(PdfFile2);
   TkJetGen140.AddIndividualPlots(PdfFile2);
   TkJetGen200.AddIndividualPlots(PdfFile2);
   
   PdfFile.AddTextPage("Summary plots");

   PdfFile.AddTextPage("TkEG + TkIsoEG (WENu)");
   AddFourPlots(PdfFile, TkEG140.GPT_Rebin, TkEG200.GPT_Rebin, TkIsoEG140.GPT_Rebin, TkIsoEG200.GPT_Rebin, "|eta| < 2.4", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG140.GPTEta10_Rebin, TkEG200.GPTEta10_Rebin, TkIsoEG140.GPTEta10_Rebin, TkIsoEG200.GPTEta10_Rebin, "|eta| < 1.0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG140.GPTEtaLarge_Rebin, TkEG200.GPTEtaLarge_Rebin, TkIsoEG140.GPTEtaLarge_Rebin, TkIsoEG200.GPTEtaLarge_Rebin, "|eta| > 1.0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG140.GEta, TkEG200.GEta, TkIsoEG140.GEta, TkIsoEG200.GEta, "PT > 0", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG140.GEtaPT20, TkEG200.GEtaPT20, TkIsoEG140.GEtaPT20, TkIsoEG200.GEtaPT20, "PT > 20", "TkEG", "TkIsoEG");
   AddFourPlots(PdfFile, TkEG140.GEtaPT25, TkEG200.GEtaPT25, TkIsoEG140.GEtaPT25, TkIsoEG200.GEtaPT25, "PT > 25", "TkEG", "TkIsoEG");
   
   PdfFile.AddTextPage("TkEG + TkIsoEG (WENu Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GPT_Rebin, TkEGTyler200.GPT_Rebin, TkIsoEGTyler140.GPT_Rebin, TkIsoEGTyler200.GPT_Rebin, "|eta| < 2.4", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GPTEta10_Rebin, TkEGTyler200.GPTEta10_Rebin, TkIsoEGTyler140.GPTEta10_Rebin, TkIsoEGTyler200.GPTEta10_Rebin, "|eta| < 1.0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GPTEtaLarge_Rebin, TkEGTyler200.GPTEtaLarge_Rebin, TkIsoEGTyler140.GPTEtaLarge_Rebin, TkIsoEGTyler200.GPTEtaLarge_Rebin, "|eta| > 1.0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GEta, TkEGTyler200.GEta, TkIsoEGTyler140.GEta, TkIsoEGTyler200.GEta, "PT > 0", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GEtaPT20, TkEGTyler200.GEtaPT20, TkIsoEGTyler140.GEtaPT20, TkIsoEGTyler200.GEtaPT20, "PT > 20", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   AddFourPlots(PdfFile, TkEGTyler140.GEtaPT25, TkEGTyler200.GEtaPT25, TkIsoEGTyler140.GEtaPT25, TkIsoEGTyler200.GEtaPT25, "PT > 25", "TkEG (Tyler)", "TkIsoEG (Tyler)");
   
   PdfFile.AddTextPage("TkEM (Hgg)");
   AddTwoPlots(PdfFile, TkEM140.GPT_Rebin, TkEM200.GPT_Rebin, "|eta| < 2.4", "TkEM");
   AddTwoPlots(PdfFile, TkEM140.GPTEta10_Rebin, TkEM200.GPTEta10_Rebin, "|eta| < 1.0", "TkEM");
   AddTwoPlots(PdfFile, TkEM140.GPTEtaLarge_Rebin, TkEM200.GPTEtaLarge_Rebin, "|eta| > 1.0", "TkEM");
   AddTwoPlots(PdfFile, TkEM140.GEta, TkEM200.GEta, "PT > 0", "TkEM");
   AddTwoPlots(PdfFile, TkEM140.GEtaPT20, TkEM200.GEtaPT20, "PT > 20", "TkEM");
   AddTwoPlots(PdfFile, TkEM140.GEtaPT25, TkEM200.GEtaPT25, "PT > 25", "TkEM");
   
   PdfFile.AddTextPage("TkEM/EG (Hgg)");
   AddTwoPlots(PdfFile, TkEMEG140.GPT_Rebin, TkEMEG200.GPT_Rebin, "|eta| < 2.4", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG140.GPTEta10_Rebin, TkEMEG200.GPTEta10_Rebin, "|eta| < 1.0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG140.GPTEtaLarge_Rebin, TkEMEG200.GPTEtaLarge_Rebin, "|eta| > 1.0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG140.GEta, TkEMEG200.GEta, "PT > 0", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG140.GEtaPT20, TkEMEG200.GEtaPT20, "PT > 20", "TkEM/EG");
   AddTwoPlots(PdfFile, TkEMEG140.GEtaPT25, TkEMEG200.GEtaPT25, "PT > 25", "TkEM/EG");

   PdfFile.AddTextPage("EG + IsoEG (Hgg)");
   AddFourPlots(PdfFile, EG140.GPT_Rebin, EG200.GPT_Rebin, IsoEG140.GPT_Rebin, IsoEG200.GPT_Rebin, "|eta| < 2.4", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG140.GPTEta10_Rebin, EG200.GPTEta10_Rebin, IsoEG140.GPTEta10_Rebin, IsoEG200.GPTEta10_Rebin, "|eta| < 1.0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG140.GPTEtaLarge_Rebin, EG200.GPTEtaLarge_Rebin, IsoEG140.GPTEtaLarge_Rebin, IsoEG200.GPTEtaLarge_Rebin, "|eta| > 1.0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG140.GEta, EG200.GEta, IsoEG140.GEta, IsoEG200.GEta, "PT > 0", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG140.GEtaPT20, EG200.GEtaPT20, IsoEG140.GEtaPT20, IsoEG200.GEtaPT20, "PT > 20", "EG", "IsoEG");
   AddFourPlots(PdfFile, EG140.GEtaPT25, EG200.GEtaPT25, IsoEG140.GEtaPT25, IsoEG200.GEtaPT25, "PT > 25", "EG", "IsoEG");
   
   PdfFile.AddTextPage("EG + IsoEG (WENu Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GPT_Rebin, EGEleTyler200.GPT_Rebin, IsoEGTyler140.GPT_Rebin, IsoEGTyler200.GPT_Rebin, "|eta| < 2.4", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GPTEta10_Rebin, EGEleTyler200.GPTEta10_Rebin, IsoEGTyler140.GPTEta10_Rebin, IsoEGTyler200.GPTEta10_Rebin, "|eta| < 1.0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GPTEtaLarge_Rebin, EGEleTyler200.GPTEtaLarge_Rebin, IsoEGTyler140.GPTEtaLarge_Rebin, IsoEGTyler200.GPTEtaLarge_Rebin, "|eta| > 1.0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GEta, EGEleTyler200.GEta, IsoEGTyler140.GEta, IsoEGTyler200.GEta, "PT > 0", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GEtaPT20, EGEleTyler200.GEtaPT20, IsoEGTyler140.GEtaPT20, IsoEGTyler200.GEtaPT20, "PT > 20", "EG (Tyler)", "IsoEG (Tyler)");
   AddFourPlots(PdfFile, EGEleTyler140.GEtaPT25, EGEleTyler200.GEtaPT25, IsoEGTyler140.GEtaPT25, IsoEGTyler200.GEtaPT25, "PT > 25", "EG (Tyler)", "IsoEG (Tyler)");
   
   PdfFile.AddTextPage("EG (WENu vs WENu Tyler)");
   AddFourPlots(PdfFile, EGEle140.GPT_Rebin, EGEle200.GPT_Rebin, EGEleTyler140.GPT_Rebin, EGEleTyler200.GPT_Rebin, "|eta| < 2.4", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EGEle140.GPTEta10_Rebin, EGEle200.GPTEta10_Rebin, EGEleTyler140.GPTEta10_Rebin, EGEleTyler200.GPTEta10_Rebin, "|eta| < 1.0", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EGEle140.GPTEtaLarge_Rebin, EGEle200.GPTEtaLarge_Rebin, EGEleTyler140.GPTEtaLarge_Rebin, EGEleTyler200.GPTEtaLarge_Rebin, "|eta| > 1.0", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EGEle140.GEtaPT20, EGEle200.GEtaPT20, EGEleTyler140.GEtaPT20, EGEleTyler200.GEtaPT20, "PT > 20", "EG", "EG (Tyler)");
   AddFourPlots(PdfFile, EGEle140.GEtaPT25, EGEle200.GEtaPT25, EGEleTyler140.GEtaPT25, EGEleTyler200.GEtaPT25, "PT > 25", "EG", "EG (Tyler)");

   PdfFile.AddTextPage("TkEG / EG (WENu vs WENu Tyler)");
   AddFourPlots(PdfFile, TkEGEG140.GPT_Rebin, TkEGEG200.GPT_Rebin, TkEGEGTyler140.GPT_Rebin, TkEGEGTyler200.GPT_Rebin, "|eta| < 2.4", "TkEG/EG", "TkEG/EG (Tyler)");
   AddFourPlots(PdfFile, TkEGEG140.GPTEta10_Rebin, TkEGEG200.GPTEta10_Rebin, TkEGEGTyler140.GPTEta10_Rebin, TkEGEGTyler200.GPTEta10_Rebin, "|eta| < 1.0", "TkEG/EG", "TkEG/EG (Tyler)");
   AddFourPlots(PdfFile, TkEGEG140.GPTEtaLarge_Rebin, TkEGEG200.GPTEtaLarge_Rebin, TkEGEGTyler140.GPTEtaLarge_Rebin, TkEGEGTyler200.GPTEtaLarge_Rebin, "|eta| > 1.0", "TkEG/EG", "TkEG/EG (Tyler)");
   AddFourPlots(PdfFile, TkEGEG140.GEtaPT20, TkEGEG200.GEtaPT20, TkEGEGTyler140.GEtaPT20, TkEGEGTyler200.GEtaPT20, "PT > 20", "TkEG/EG", "TkEG/EG (Tyler)");
   AddFourPlots(PdfFile, TkEGEG140.GEtaPT25, TkEGEG200.GEtaPT25, TkEGEGTyler140.GEtaPT25, TkEGEGTyler200.GEtaPT25, "PT > 25", "TkEG/EG", "TkEG/EG (Tyler)");

   PdfFile.AddTextPage("TkJet - parton (ttbar)");
   AddTwoPlots(PdfFile, TkJet140.GPT_Rebin2, TkJet200.GPT_Rebin2, "No |eta| cut", "TkJet");
   AddTwoPlots(PdfFile, TkJet140.GPTEta10_Rebin2, TkJet200.GPTEta10_Rebin2, "|eta| < 1.0", "TkJet");
   AddTwoPlots(PdfFile, TkJet140.GPTEtaLarge_Rebin2, TkJet200.GPTEtaLarge_Rebin2, "|eta| > 1.0", "TkJet");
   AddTwoPlots(PdfFile, TkJet140.GEta, TkJet200.GEta, "PT > 0", "TkJet");
   AddTwoPlots(PdfFile, TkJet140.GEtaPT200, TkJet200.GEtaPT200, "PT > 200", "TkJet");
   
   PdfFile.AddTextPage("TkJet - gen jet (ttbar)");
   AddTwoPlots(PdfFile, TkJetGen140.GPT_Rebin2, TkJetGen200.GPT_Rebin2, "No |eta| cut", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen140.GPTEta10_Rebin2, TkJetGen200.GPTEta10_Rebin2, "|eta| < 1.0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen140.GPTEtaLarge_Rebin2, TkJetGen200.GPTEtaLarge_Rebin2, "|eta| > 1.0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen140.GEta, TkJetGen200.GEta, "PT > 0", "TkJet (GenJet)");
   AddTwoPlots(PdfFile, TkJetGen140.GEtaPT200, TkJetGen200.GEtaPT200, "PT > 200", "TkJet (GenJet)");
   
   PdfFile2.AddTimeStampPage();
   PdfFile2.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FTT200.Close();
   FTT140.Close();
   FHgg200.Close();
   FHgg140.Close();
   FWENu200Tyler.Close();
   FWENu140Tyler.Close();
   FWENu200.Close();
   FWENu140.Close();

   return 0;
}

TGraphAsymmErrors *Divide(TFile &F1, string N1, TFile &F2, string N2, int Rebin)
{
   cout << N1 << " " << N2 << endl;

   // static PdfFileHelper Meow("Meow.pdf");
   // Meow.AddTextPage("Divide " + N1 + " " + N2);

   TGraphAsymmErrors *Result = NULL;

   TH1D *H1 = (TH1D *)F1.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F2.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return NULL;

   TH1D *H1Temp = NULL;
   TH1D *H2Temp = NULL;

   if(Rebin >= 1)
   {
      H1Temp = (TH1D *)H1->Clone("H1Temp");
      H2Temp = (TH1D *)H2->Clone("H2Temp");

      H1Temp->Rebin(Rebin);
      H2Temp->Rebin(Rebin);
   }
   
   if(Rebin < 0)
   {
      // this is the PT case - let's make variable binned histograms
      double Binning1[24] =
         {4, 6, 8, 10, 12, 14, 16, 18,
         20, 22, 24, 26, 28, 30, 34, 38, 42, 46,
         50, 60, 70, 90, 110, 150};
      double Binning2[24] =
         {14, 24, 32, 40, 48, 56, 64, 72,
         80, 88, 96, 104, 112, 120, 136, 152, 168, 184,
         200, 240, 280, 360, 440, 600};

      double Binning[24];

      if(Rebin == -2)
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning2[i];
      else
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning1[i];

      H1Temp = new TH1D("H1Temp", "", 23, Binning);
      H2Temp = new TH1D("H2Temp", "", 23, Binning);

      H1Temp->Sumw2();
      H2Temp->Sumw2();

      int N = H1->GetNbinsX();
      for(int i = 1; i <= N; i++)
      {
         for(int j = 0; j < H1->GetBinContent(i); j++)
            H1Temp->Fill(H1->GetBinCenter(i));
         for(int j = 0; j < H2->GetBinContent(i); j++)
            H2Temp->Fill(H2->GetBinCenter(i));
      }

      H1Temp->SetBinContent(0, 0);
      H1Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
      H2Temp->SetBinContent(0, 0);
      H2Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
   }

   Result = new TGraphAsymmErrors;
   Result->Divide(H1Temp, H2Temp);

   // TCanvas C;
   // H2Temp->SetLineColor(kRed);
   // H2Temp->Draw("hist");
   // H1Temp->Draw("hist same");
   // C.SetLogy();
   // Meow.AddCanvas(C);

   // Meow.AddPlot(Result, "ap");

   if(H1Temp != NULL)
      delete H1Temp;
   if(H2Temp != NULL)
      delete H2Temp;

   return Result;
}

void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, string Title, string Tag1, string Tag2)
{
   if(TkEG140 == NULL)
      return;
   if(TkEG200 == NULL)
      return;
   if(TkIsoEG140 == NULL)
      return;
   if(TkIsoEG200 == NULL)
      return;

   TkEG140->SetTitle(Title.c_str());

   TkEG140->SetMarkerColor(kBlue);
   TkEG200->SetMarkerColor(kRed);
   TkIsoEG140->SetMarkerColor(kGreen - 3);
   TkIsoEG200->SetMarkerColor(kYellow + 3);
   
   TkEG140->SetLineColor(kBlue);
   TkEG200->SetLineColor(kRed);
   TkIsoEG140->SetLineColor(kGreen - 3);
   TkIsoEG200->SetLineColor(kYellow + 3);

   TCanvas C;

   TkEG140->Draw("ap");
   
   TH2D HWorld("HWorld", "", 100, TkEG140->GetXaxis()->GetXmin(), TkEG140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEG140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEG140->Draw("p");
   TkEG200->Draw("p");
   TkIsoEG140->Draw("p");
   TkIsoEG200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEG140,    Form("%s, PU140", Tag1.c_str()), "pl");
   Legend.AddEntry(TkEG200,    Form("%s, PU200", Tag1.c_str()), "pl");
   Legend.AddEntry(TkIsoEG140, Form("%s, PU140", Tag2.c_str()), "pl");
   Legend.AddEntry(TkIsoEG200, Form("%s, PU200", Tag2.c_str()), "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, string Title, string Tag)
{
   if(TkEM140 == NULL)
      return;
   if(TkEM200 == NULL)
      return;

   TkEM140->SetTitle(Title.c_str());

   TkEM140->SetMarkerColor(kBlue);
   TkEM200->SetMarkerColor(kRed);
   
   TkEM140->SetLineColor(kBlue);
   TkEM200->SetLineColor(kRed);

   TCanvas C;

   TkEM140->Draw("ap");

   TH2D HWorld("HWorld", "", 100, TkEM140->GetXaxis()->GetXmin(), TkEM140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEM140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEM140->Draw("p");
   TkEM200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEM140, Form("%s, PU140", Tag.c_str()), "pl");
   Legend.AddEntry(TkEM200, Form("%s, PU200", Tag.c_str()), "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, string N, string Title)
{
   TH1D *H = (TH1D *)F.Get(N.c_str())->Clone("Yay");

   H->SetStats(0);
   H->SetTitle(Title.c_str());
   H->SetMinimum(0);

   PdfFile.AddPlot(H);

   delete H;
}


