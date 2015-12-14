#include <string>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void JetPTCutEfficiency(string InputFileName, string OutputBase);
void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination);
void Get2DCumulativeHistogram(TH2D &Source, TH2D &Destination);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   string Tag = "LQ3Tree_350";
   if(argc > 1)
      Tag = argv[1];

   string InputFileName = "Samples/" + Tag + ".root";
   string OutputBase = Tag;

   JetPTCutEfficiency(InputFileName, OutputBase);
}

void JetPTCutEfficiency(string InputFileName, string OutputBase)
{
   TFile F(InputFileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");

   if(Tree == NULL)
      return;

   TreeRecord M;
   M.SetBranchAddress(Tree);

   double Contours[5] = {0.1, 0.5, 0.8, 0.9, 0.95};

   const int BinCount = 200;
   const double MaxBin = 400;
   const double CSVMaxBin = 1;
   const double TCHMaxBin = 15;

   TH1D HCaloJet1PT("HCaloJet1PT", "Leading calo jet PT", BinCount, 0, MaxBin);
   TH1D HCaloJet2PT("HCaloJet2PT", "Sub-leading calo jet PT", BinCount, 0, MaxBin);
   TH2D HCaloJet1PTVsCaloJet2PT("HCaloJet1PTVsCaloJet2PT",
      "(Calo) Leading vs. subleading jet PT;Leading;Sub-leading", BinCount, 0, MaxBin, BinCount, 0, MaxBin);

   TH1D HPFJet1PT("HPFJet1PT", "Leading PF jet PT", BinCount, 0, MaxBin);
   TH1D HPFJet2PT("HPFJet2PT", "Sub-leading PF jet PT", BinCount, 0, MaxBin);
   TH2D HPFJet1PTVsPFJet2PT("HPFJet1PTVsPFJet2PT", "(PF) Leading vs. subleading jet PT;Leading;Sub-leading",
      BinCount, 0, MaxBin, BinCount, 0, MaxBin);

   TH1D HPFJet1CSV("HPFJet1CSV", "Leading PF jet CSV", BinCount, 0, CSVMaxBin);
   TH1D HPFJet2CSV("HPFJet2CSV", "Sub-leading PF jet CSV", BinCount, 0, CSVMaxBin);
   TH2D HPFJetCSV("HPFJetCSV", "Leading vs. sub-leading PF jet CSV;leading;sub-leading",
      BinCount, 0, CSVMaxBin, BinCount, 0, CSVMaxBin);

   TH1D HPFJet1CSVM("HPFJet1CSVM", "Leading PF jet CSVM", BinCount, 0, CSVMaxBin);
   TH1D HPFJet2CSVM("HPFJet2CSVM", "Sub-leading PF jet CSVM", BinCount, 0, CSVMaxBin);
   TH2D HPFJetCSVM("HPFJetCSVM", "Leading vs. sub-leading PF jet CSVM;leading;sub-leading",
      BinCount, 0, CSVMaxBin, BinCount, 0, CSVMaxBin);

   TH1D HPFJet1TCHE("HPFJet1TCHE", "Leading PF jet TCHE", BinCount, 0, TCHMaxBin);
   TH1D HPFJet2TCHE("HPFJet2TCHE", "Sub-leading PF jet TCHE", BinCount, 0, TCHMaxBin);
   TH2D HPFJetTCHE("HPFJetTCHE", "Leading vs. sub-leading PF jet TCHE;leading;sub-leading",
      BinCount, 0, TCHMaxBin, BinCount, 0, TCHMaxBin);
   
   TH1D HPFJet1TCHP("HPFJet1TCHP", "Leading PF jet TCHP", BinCount, 0, TCHMaxBin);
   TH1D HPFJet2TCHP("HPFJet2TCHP", "Sub-leading PF jet TCHP", BinCount, 0, TCHMaxBin);
   TH2D HPFJetTCHP("HPFJetTCHP", "Leading vs. sub-leading PF jet TCHP;leading;sub-leading",
      BinCount, 0, TCHMaxBin, BinCount, 0, TCHMaxBin);

   HCaloJet1PT.SetStats(0);
   HCaloJet2PT.SetStats(0);
   HCaloJet1PTVsCaloJet2PT.SetStats(0);

   HPFJet1PT.SetStats(0);
   HPFJet2PT.SetStats(0);
   HPFJet1PTVsPFJet2PT.SetStats(0);

   HPFJet1CSV.SetStats(0);
   HPFJet2CSV.SetStats(0);
   HPFJetCSV.SetStats(0);
   
   HPFJet1CSVM.SetStats(0);
   HPFJet2CSVM.SetStats(0);
   HPFJetCSVM.SetStats(0);

   HPFJet1TCHE.SetStats(0);
   HPFJet2TCHE.SetStats(0);
   HPFJetTCHE.SetStats(0);
   
   HPFJet1TCHP.SetStats(0);
   HPFJet2TCHP.SetStats(0);
   HPFJetTCHP.SetStats(0);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 1; iEntry <= EntryCount; iEntry++)
   {
      if(iEntry % 500000 == 0)
         cout << "Processing entry " << iEntry << "/" << EntryCount << endl;

      M.Clear();
      Tree->GetEntry(iEntry - 1);

      double CaloJet1PT = -1;
      double CaloJet2PT = -1;

      if(M.CaloJetCount >= 1)    CaloJet1PT = M.CaloJetPT[0];
      if(M.CaloJetCount >= 2)    CaloJet2PT = M.CaloJetPT[1];

      if(CaloJet1PT >= MaxBin)   CaloJet1PT = MaxBin - 0.01;
      if(CaloJet2PT >= MaxBin)   CaloJet2PT = MaxBin - 0.01;

      HCaloJet1PT.Fill(CaloJet1PT);
      HCaloJet2PT.Fill(CaloJet2PT);
      HCaloJet1PTVsCaloJet2PT.Fill(CaloJet1PT, CaloJet2PT);

      double PFJet1PT = -1;
      double PFJet2PT = -1;

      if(M.PFJetCount >= 1)    PFJet1PT = M.PFJetPT[0];
      if(M.PFJetCount >= 2)    PFJet2PT = M.PFJetPT[1];

      if(PFJet1PT >= MaxBin)   PFJet1PT = MaxBin - 0.01;
      if(PFJet2PT >= MaxBin)   PFJet2PT = MaxBin - 0.01;

      HPFJet1PT.Fill(PFJet1PT);
      HPFJet2PT.Fill(PFJet2PT);
      HPFJet1PTVsPFJet2PT.Fill(PFJet1PT, PFJet2PT);

      double PFJet1CSV = -1;
      double PFJet2CSV = -1;

      if(M.PFJetCount >= 1)   PFJet1CSV = M.PFJetCSVTag[0];
      if(M.PFJetCount >= 2)   PFJet2CSV = M.PFJetCSVTag[1];

      if(PFJet1CSV >= CSVMaxBin)   PFJet1CSV = CSVMaxBin - 0.0001;
      if(PFJet2CSV >= CSVMaxBin)   PFJet2CSV = CSVMaxBin - 0.0001;

      HPFJet1CSV.Fill(PFJet1CSV);
      HPFJet2CSV.Fill(PFJet2CSV);
      HPFJetCSV.Fill(PFJet1CSV, PFJet2CSV);
      
      double PFJet1CSVM = -1;
      double PFJet2CSVM = -1;

      if(M.PFJetCount >= 1)   PFJet1CSVM = M.PFJetCSVMTag[0];
      if(M.PFJetCount >= 2)   PFJet2CSVM = M.PFJetCSVMTag[1];

      if(PFJet1CSVM >= CSVMaxBin)   PFJet1CSVM = CSVMaxBin - 0.0001;
      if(PFJet2CSVM >= CSVMaxBin)   PFJet2CSVM = CSVMaxBin - 0.0001;

      HPFJet1CSVM.Fill(PFJet1CSVM);
      HPFJet2CSVM.Fill(PFJet2CSVM);
      HPFJetCSVM.Fill(PFJet1CSVM, PFJet2CSVM);

      double PFJet1TCHE = -1;
      double PFJet2TCHE = -1;

      if(M.PFJetCount >= 1)   PFJet1TCHE = M.PFJetTCHETag[0];
      if(M.PFJetCount >= 2)   PFJet2TCHE = M.PFJetTCHETag[1];

      if(PFJet1TCHE >= TCHMaxBin)   PFJet1TCHE = TCHMaxBin - 0.0001;
      if(PFJet2TCHE >= TCHMaxBin)   PFJet2TCHE = TCHMaxBin - 0.0001;

      HPFJet1TCHE.Fill(PFJet1TCHE);
      HPFJet2TCHE.Fill(PFJet2TCHE);
      HPFJetTCHE.Fill(PFJet1TCHE, PFJet2TCHE);

      double PFJet1TCHP = -1;
      double PFJet2TCHP = -1;

      if(M.PFJetCount >= 1)   PFJet1TCHP = M.PFJetTCHPTag[0];
      if(M.PFJetCount >= 2)   PFJet2TCHP = M.PFJetTCHPTag[1];

      if(PFJet1TCHP >= TCHMaxBin)   PFJet1TCHP = TCHMaxBin - 0.0001;
      if(PFJet2TCHP >= TCHMaxBin)   PFJet2TCHP = TCHMaxBin - 0.0001;

      HPFJet1TCHP.Fill(PFJet1TCHP);
      HPFJet2TCHP.Fill(PFJet2TCHP);
      HPFJetTCHP.Fill(PFJet1TCHP, PFJet2TCHP);
   }

   TH1D HCaloJet1PTCutEfficiency("HCaloJet1PTCutEfficiency",
      "Percentage remaining after leading jet calo pt cut;Cut position (GeV)", HCaloJet1PT.GetNbinsX(), 0, MaxBin);
   Get1DCumulativeHistogram(HCaloJet1PT, HCaloJet1PTCutEfficiency);
   HCaloJet1PTCutEfficiency.Scale(1.0 / EntryCount);
   HCaloJet1PTCutEfficiency.SetStats(0);

   TH1D HCaloJet2PTCutEfficiency("HCaloJet2PTCutEfficiency",
      "Percentage remaining after sub-leading jet calo pt cut;Cut position (GeV)",
      HCaloJet1PT.GetNbinsX(), 0, MaxBin);
   Get1DCumulativeHistogram(HCaloJet2PT, HCaloJet2PTCutEfficiency);
   HCaloJet2PTCutEfficiency.Scale(1.0 / EntryCount);
   HCaloJet2PTCutEfficiency.SetStats(0);

   TH2D HCaloJetPTCutEfficiency("HCaloJetPTCutEfficiency",
      "Percentage remaining after leading 2 jet calo pt cut (contours 95, 90, 80, 50, 10);Cut on leading jet (GeV);Cut on sub-leading jet (GeV)",
      HCaloJet1PTVsCaloJet2PT.GetNbinsX(), 0, MaxBin, HCaloJet1PTVsCaloJet2PT.GetNbinsY(), 0, MaxBin);
   Get2DCumulativeHistogram(HCaloJet1PTVsCaloJet2PT, HCaloJetPTCutEfficiency);
   HCaloJetPTCutEfficiency.Scale(1.0 / EntryCount);
   HCaloJetPTCutEfficiency.SetStats(0);
   TH2D *HCaloJetPTCutEfficiencyContour = (TH2D *)HCaloJetPTCutEfficiency.Clone("HCaloJetPTCutEfficiencyContour");
   HCaloJetPTCutEfficiencyContour->SetContour(5, Contours);

   TH1D HPFJet1PTCutEfficiency("HPFJet1PTCutEfficiency",
      "Percentage remaining after leading jet PF pt cut;Cut position (GeV)", HPFJet1PT.GetNbinsX(), 0, MaxBin);
   Get1DCumulativeHistogram(HPFJet1PT, HPFJet1PTCutEfficiency);
   HPFJet1PTCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet1PTCutEfficiency.SetStats(0);

   TH1D HPFJet2PTCutEfficiency("HPFJet2PTCutEfficiency",
      "Percentage remaining after sub-leading PF jet pt cut;Cut position (GeV)", HPFJet1PT.GetNbinsX(), 0, MaxBin);
   Get1DCumulativeHistogram(HPFJet2PT, HPFJet2PTCutEfficiency);
   HPFJet2PTCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet2PTCutEfficiency.SetStats(0);

   TH2D HPFJetPTCutEfficiency("HPFJetPTCutEfficiency",
      "Percentage remaining after leading 2 PF jet pt cut (contours 95, 90, 80, 50, 10);Cut on leading jet (GeV);Cut on sub-leading jet (GeV)",
      HPFJet1PTVsPFJet2PT.GetNbinsX(), 0, MaxBin, HPFJet1PTVsPFJet2PT.GetNbinsY(), 0, MaxBin);
   Get2DCumulativeHistogram(HPFJet1PTVsPFJet2PT, HPFJetPTCutEfficiency);
   HPFJetPTCutEfficiency.Scale(1.0 / EntryCount);
   HPFJetPTCutEfficiency.SetStats(0);
   TH2D *HPFJetPTCutEfficiencyContour = (TH2D *)HPFJetPTCutEfficiency.Clone("HPFJetPTCutEfficiencyContour");
   HPFJetPTCutEfficiencyContour->SetContour(5, Contours);

   TH1D HPFJet1CSVCutEfficiency("HPFJet1CSVCutEfficiency",
      "PF leading jet efficiency vs. CSV tag cut;Cut position", HPFJet1CSV.GetNbinsX(), 0, CSVMaxBin);
   Get1DCumulativeHistogram(HPFJet1CSV, HPFJet1CSVCutEfficiency);
   HPFJet1CSVCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet1CSVCutEfficiency.SetStats(0);
   
   TH1D HPFJet2CSVCutEfficiency("HPFJet2CSVCutEfficiency",
      "PF sub-leading jet efficiency vs. CSV tag cut;Cut position", HPFJet2CSV.GetNbinsX(), 0, CSVMaxBin);
   Get1DCumulativeHistogram(HPFJet2CSV, HPFJet2CSVCutEfficiency);
   HPFJet2CSVCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet2CSVCutEfficiency.SetStats(0);
   
   TH2D HPFJetCSVCutEfficiency("HPFJetCSVCutEfficiency",
      "PF jets efficiency vs. CSV tag cut (contours 95, 90, 80, 50, 10);Cut position on leading;Cut position on sub-leading",
      HPFJet1CSV.GetNbinsX(), 0, CSVMaxBin, HPFJet2CSV.GetNbinsX(), 0, CSVMaxBin);
   Get2DCumulativeHistogram(HPFJetCSV, HPFJetCSVCutEfficiency);
   HPFJetCSVCutEfficiency.Scale(1.0 / EntryCount);
   HPFJetCSVCutEfficiency.SetStats(0);
   TH2D *HPFJetCSVCutEfficiencyContour = (TH2D *)HPFJetCSVCutEfficiency.Clone("HPFJetCSVCutEfficiencyContour");
   HPFJetCSVCutEfficiencyContour->SetContour(5, Contours);
   
   TH1D HPFJet1CSVMCutEfficiency("HPFJet1CSVMCutEfficiency",
      "PF leading jet efficiency vs. CSVM tag cut;Cut position", HPFJet1CSVM.GetNbinsX(), 0, CSVMaxBin);
   Get1DCumulativeHistogram(HPFJet1CSVM, HPFJet1CSVMCutEfficiency);
   HPFJet1CSVMCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet1CSVMCutEfficiency.SetStats(0);
   
   TH1D HPFJet2CSVMCutEfficiency("HPFJet2CSVMCutEfficiency",
      "PF sub-leading jet efficiency vs. CSVM tag cut;Cut position", HPFJet2CSVM.GetNbinsX(), 0, CSVMaxBin);
   Get1DCumulativeHistogram(HPFJet2CSVM, HPFJet2CSVMCutEfficiency);
   HPFJet2CSVMCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet2CSVMCutEfficiency.SetStats(0);
   
   TH2D HPFJetCSVMCutEfficiency("HPFJetCSVMCutEfficiency",
      "PF jets efficiency vs. CSVM tag cut (contours 95, 90, 80, 50, 10);Cut position on leading;Cut position on sub-leading",
      HPFJet1CSVM.GetNbinsX(), 0, CSVMaxBin, HPFJet2CSVM.GetNbinsX(), 0, CSVMaxBin);
   Get2DCumulativeHistogram(HPFJetCSVM, HPFJetCSVMCutEfficiency);
   HPFJetCSVMCutEfficiency.Scale(1.0 / EntryCount);
   HPFJetCSVMCutEfficiency.SetStats(0);
   TH2D *HPFJetCSVMCutEfficiencyContour = (TH2D *)HPFJetCSVMCutEfficiency.Clone("HPFJetCSVMCutEfficiencyContour");
   HPFJetCSVMCutEfficiencyContour->SetContour(5, Contours);

   TH1D HPFJet1TCHECutEfficiency("HPFJet1TCHECutEfficiency",
      "PF leading jet efficiency vs. TCHE tag cut;Cut position", HPFJet1TCHE.GetNbinsX(), 0, TCHMaxBin);
   Get1DCumulativeHistogram(HPFJet1TCHE, HPFJet1TCHECutEfficiency);
   HPFJet1TCHECutEfficiency.Scale(1.0 / EntryCount);
   HPFJet1TCHECutEfficiency.SetStats(0);
   
   TH1D HPFJet2TCHECutEfficiency("HPFJet2TCHECutEfficiency",
      "PF sub-leading jet efficiency vs. TCHE tag cut;Cut position", HPFJet2TCHE.GetNbinsX(), 0, TCHMaxBin);
   Get1DCumulativeHistogram(HPFJet2TCHE, HPFJet2TCHECutEfficiency);
   HPFJet2TCHECutEfficiency.Scale(1.0 / EntryCount);
   HPFJet2TCHECutEfficiency.SetStats(0);
   
   TH2D HPFJetTCHECutEfficiency("HPFJetTCHECutEfficiency",
      "PF jets efficiency vs. TCHE tag cut (contours 95, 90, 80, 50, 10);Cut position on leading;Cut position on sub-leading",
      HPFJet1TCHE.GetNbinsX(), 0, TCHMaxBin, HPFJet2TCHE.GetNbinsX(), 0, TCHMaxBin);
   Get2DCumulativeHistogram(HPFJetTCHE, HPFJetTCHECutEfficiency);
   HPFJetTCHECutEfficiency.Scale(1.0 / EntryCount);
   HPFJetTCHECutEfficiency.SetStats(0);
   TH2D *HPFJetTCHECutEfficiencyContour = (TH2D *)HPFJetTCHECutEfficiency.Clone("HPFJetTCHECutEfficiencyContour");
   HPFJetTCHECutEfficiencyContour->SetContour(5, Contours);
   
   TH1D HPFJet1TCHPCutEfficiency("HPFJet1TCHPCutEfficiency",
      "PF leading jet efficiency vs. TCHP tag cut;Cut position", HPFJet1TCHP.GetNbinsX(), 0, TCHMaxBin);
   Get1DCumulativeHistogram(HPFJet1TCHP, HPFJet1TCHPCutEfficiency);
   HPFJet1TCHPCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet1TCHPCutEfficiency.SetStats(0);
   
   TH1D HPFJet2TCHPCutEfficiency("HPFJet2TCHPCutEfficiency",
      "PF sub-leading jet efficiency vs. TCHP tag cut;Cut position", HPFJet2TCHP.GetNbinsX(), 0, TCHMaxBin);
   Get1DCumulativeHistogram(HPFJet2TCHP, HPFJet2TCHPCutEfficiency);
   HPFJet2TCHPCutEfficiency.Scale(1.0 / EntryCount);
   HPFJet2TCHPCutEfficiency.SetStats(0);
   
   TH2D HPFJetTCHPCutEfficiency("HPFJetTCHPCutEfficiency",
      "PF jets efficiency vs. TCHP tag cut (contours 95, 90, 80, 50, 10);Cut position on leading;Cut position on sub-leading",
      HPFJet1TCHP.GetNbinsX(), 0, TCHMaxBin, HPFJet2TCHP.GetNbinsX(), 0, TCHMaxBin);
   Get2DCumulativeHistogram(HPFJetTCHP, HPFJetTCHPCutEfficiency);
   HPFJetTCHPCutEfficiency.Scale(1.0 / EntryCount);
   HPFJetTCHPCutEfficiency.SetStats(0);
   TH2D *HPFJetTCHPCutEfficiencyContour = (TH2D *)HPFJetTCHPCutEfficiency.Clone("HPFJetTCHPCutEfficiencyContour");
   HPFJetTCHPCutEfficiencyContour->SetContour(5, Contours);
   
   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Jet PT cut efficiency plots for various samples");

   vector<string> Explanations;
   // PsFile.AddTextPage(Explanations);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Basic distributions for cross check");
   TableOfContentItems.push_back("PT cut efficiency");
   TableOfContentItems.push_back("b-tag (CSV) cut efficiency");
   TableOfContentItems.push_back("b-tag (CSVM) cut efficiency");
   TableOfContentItems.push_back("b-tag (TCHE) cut efficiency");
   TableOfContentItems.push_back("b-tag (TCHP) cut efficiency");

   vector<string> Destinations;
   Destinations.push_back("Distributions");
   Destinations.push_back("PTCut");
   Destinations.push_back("CSVTag");
   Destinations.push_back("CSVMTag");
   Destinations.push_back("TCHETag");
   Destinations.push_back("TCHPTag");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("TableOfContentPage");
   PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   PsFile.AddTextPage("Jet distributions");
   PsFile.InsertNamedDestination("Distributions");
   // PsFile.AddPlot(HCaloJet1PT, "", true);
   // PsFile.AddPlot(HCaloJet2PT, "", true);
   // PsFile.AddPlot(HCaloJet1PTVsCaloJet2PT, "colz", false, true);
   PsFile.AddPlot(HPFJet1PT, "", true);
   PsFile.AddPlot(HPFJet2PT, "", true);
   PsFile.AddPlot(HPFJet1PTVsPFJet2PT, "colz", false, true);
   PsFile.AddPlot(HPFJet1CSV, "", true);
   PsFile.AddPlot(HPFJet2CSV, "", true);
   PsFile.AddPlot(HPFJetCSV, "colz", false, true);
   PsFile.AddPlot(HPFJet1CSVM, "", true);
   PsFile.AddPlot(HPFJet2CSVM, "", true);
   PsFile.AddPlot(HPFJetCSVM, "colz", false, true);
   PsFile.AddPlot(HPFJet1TCHE, "", true);
   PsFile.AddPlot(HPFJet2TCHE, "", true);
   PsFile.AddPlot(HPFJetTCHE, "colz", false, true);
   PsFile.AddPlot(HPFJet1TCHP, "", true);
   PsFile.AddPlot(HPFJet2TCHP, "", true);
   PsFile.AddPlot(HPFJetTCHP, "colz", false, true);

   PsFile.AddTextPage("Jet PT cut efficiency");
   PsFile.InsertNamedDestination("PTCut");
   // PsFile.AddPlot(HCaloJet1PTCutEfficiency, "", true);
   // PsFile.AddPlot(HCaloJet2PTCutEfficiency, "", true);
   // PsFile.AddPlot(HCaloJetPTCutEfficiency, "colz", false, true);
   PsFile.AddPlot(HPFJet1PTCutEfficiency, "", true);
   PsFile.AddPlot(HPFJet2PTCutEfficiency, "", true);
   
   TCanvas PFJetPTCanvas;
   HPFJetPTCutEfficiency.Draw("colz");
   PFJetPTCanvas.SetLogz();
   HPFJetPTCutEfficiencyContour->Draw("cont3 same");
   PsFile.AddCanvas(PFJetPTCanvas);

   PsFile.AddTextPage("Jet CSV b-tag cut efficiency");
   PsFile.InsertNamedDestination("CSVTag");
   PsFile.AddPlot(HPFJet1CSVCutEfficiency, "", true);
   PsFile.AddPlot(HPFJet2CSVCutEfficiency, "", true);

   TCanvas PFJetCSVCanvas;
   HPFJetCSVCutEfficiency.Draw("colz");
   PFJetCSVCanvas.SetLogz();
   HPFJetCSVCutEfficiencyContour->Draw("cont3 same");
   PsFile.AddCanvas(PFJetCSVCanvas);

   PsFile.AddTextPage("Jet CSVM b-tag cut efficiency");
   PsFile.InsertNamedDestination("CSVMTag");
   PsFile.AddPlot(HPFJet1CSVMCutEfficiency, "", true);
   PsFile.AddPlot(HPFJet2CSVMCutEfficiency, "", true);
   
   TCanvas PFJetCSVMCanvas;
   HPFJetCSVMCutEfficiency.Draw("colz");
   PFJetCSVMCanvas.SetLogz();
   HPFJetCSVMCutEfficiencyContour->Draw("cont3 same");
   PsFile.AddCanvas(PFJetCSVMCanvas);

   PsFile.AddTextPage("Jet TCHE b-tag cut efficiency");
   PsFile.InsertNamedDestination("TCHETag");
   PsFile.AddPlot(HPFJet1TCHECutEfficiency, "", true);
   PsFile.AddPlot(HPFJet2TCHECutEfficiency, "", true);

   TCanvas PFJetTCHECanvas;
   HPFJetTCHECutEfficiency.Draw("colz");
   PFJetTCHECanvas.SetLogz();
   HPFJetTCHECutEfficiencyContour->Draw("cont3 same");
   PsFile.AddCanvas(PFJetTCHECanvas);

   PsFile.AddTextPage("Jet TCHP b-tag cut efficiency");
   PsFile.InsertNamedDestination("TCHPTag");
   PsFile.AddPlot(HPFJet1TCHPCutEfficiency, "", true);
   PsFile.AddPlot(HPFJet2TCHPCutEfficiency, "", true);
   
   TCanvas PFJetTCHPCanvas;
   HPFJetTCHPCutEfficiency.Draw("colz");
   PFJetTCHPCanvas.SetLogz();
   HPFJetTCHPCutEfficiencyContour->Draw("cont3 same");
   PsFile.AddCanvas(PFJetTCHPCanvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination)
{
   Destination.SetBinContent(Source.GetNbinsX(), Source.GetBinContent(Source.GetNbinsX()));
   for(int i = Destination.GetNbinsX() - 1; i >= 1; i--)
      Destination.SetBinContent(i, Destination.GetBinContent(i + 1) + Source.GetBinContent(i));
}

void Get2DCumulativeHistogram(TH2D &Source, TH2D &Destination)
{
   int XBin = Source.GetNbinsX();
   int YBin = Source.GetNbinsY();

   Destination.SetBinContent(XBin, YBin, Source.GetBinContent(XBin, YBin));
   for(int i = XBin - 1; i >= 1; i--)
      Destination.SetBinContent(i, YBin, Destination.GetBinContent(i + 1, YBin) + Source.GetBinContent(i, YBin));
   for(int y = YBin - 1; y >= 1; y--)
   {
      Destination.SetBinContent(XBin, y, Source.GetBinContent(XBin, y) + Destination.GetBinContent(XBin, y + 1));
      for(int x = XBin - 1; x >= 1; x--)
         Destination.SetBinContent(x, y, Destination.GetBinContent(x + 1, y) + Destination.GetBinContent(x, y + 1)
            - Destination.GetBinContent(x + 1, y + 1) + Source.GetBinContent(x, y));
   }
}





