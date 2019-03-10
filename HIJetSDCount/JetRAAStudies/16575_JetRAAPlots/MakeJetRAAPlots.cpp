#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void TidyHistogram(TH1D &H, double TotalWeight);
void DivideByBinWidth(TH1D &H);

int main(int argc, char *argv[])
{
   string InputFileName = "16532Samples/Result_RecoilOff_S.root";
   string OutputBase = "Curves_RecoilOff_S";
   bool Jewel = false;
   
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " InputFileName OutputBase Jewel=(Y|N)" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputBase = argv[2];
   Jewel = ((argv[3][0] == 'Y') ? true : false);

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Result");

   // int Bin = 20;
   // double Binning[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 225, 250, 275, 300, 350, 400, 450, 500, 700, 1000};
   int Bin = 10;
   double Binning[] = {100, 120, 140, 160, 180, 200, 250, 300, 400, 500, 1000};
   // int Bin = 6;
   // double Binning[] = {100, 120, 140, 200, 300, 500, 1000};

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HSig("HSig", "Sig;Jet PT;", Bin, Binning);                                   HSig.Sumw2();
   TH1D HSigSD0DR0("HSigSD0DR0", "Sig (SD0DR < 0.1);Jet PT;", Bin, Binning);         HSigSD0DR0.Sumw2();
   TH1D HSigSD0DR1("HSigSD0DR1", "Sig (0.1 < SD0DR < 0.2);Jet PT;", Bin, Binning);   HSigSD0DR1.Sumw2();
   TH1D HSigSD0DR2("HSigSD0DR2", "Sig (0.2 < SD0DR < 0.3);Jet PT;", Bin, Binning);   HSigSD0DR2.Sumw2();
   TH1D HSigSD0DR3("HSigSD0DR3", "Sig (0.3 < SD0DR);Jet PT;", Bin, Binning);         HSigSD0DR3.Sumw2();
   TH1D HSigSD7DR0("HSigSD7DR0", "Sig (SD7DR < 0.1);Jet PT;", Bin, Binning);         HSigSD7DR0.Sumw2();
   TH1D HSigSD7DR1("HSigSD7DR1", "Sig (0.1 < SD7DR < 0.2);Jet PT;", Bin, Binning);   HSigSD7DR1.Sumw2();
   TH1D HSigSD7DR2("HSigSD7DR2", "Sig (0.2 < SD7DR < 0.3);Jet PT;", Bin, Binning);   HSigSD7DR2.Sumw2();
   TH1D HSigSD7DR3("HSigSD7DR3", "Sig (0.3 < SD7DR);Jet PT;", Bin, Binning);         HSigSD7DR3.Sumw2();
   TH1D HCS("HCS", "CS;Jet PT;", Bin, Binning);                                      HCS.Sumw2();
   TH1D HCSSD0DR0("HCSSD0DR0", "CS (SD0DR < 0.1);Jet PT;", Bin, Binning);            HCSSD0DR0.Sumw2();
   TH1D HCSSD0DR1("HCSSD0DR1", "CS (0.1 < SD0DR < 0.2);Jet PT;", Bin, Binning);      HCSSD0DR1.Sumw2();
   TH1D HCSSD0DR2("HCSSD0DR2", "CS (0.2 < SD0DR < 0.3);Jet PT;", Bin, Binning);      HCSSD0DR2.Sumw2();
   TH1D HCSSD0DR3("HCSSD0DR3", "CS (0.3 < SD0DR);Jet PT;", Bin, Binning);            HCSSD0DR3.Sumw2();
   TH1D HCSSD7DR0("HCSSD7DR0", "CS (SD7DR < 0.1);Jet PT;", Bin, Binning);            HCSSD7DR0.Sumw2();
   TH1D HCSSD7DR1("HCSSD7DR1", "CS (0.1 < SD7DR < 0.2);Jet PT;", Bin, Binning);      HCSSD7DR1.Sumw2();
   TH1D HCSSD7DR2("HCSSD7DR2", "CS (0.2 < SD7DR < 0.3);Jet PT;", Bin, Binning);      HCSSD7DR2.Sumw2();
   TH1D HCSSD7DR3("HCSSD7DR3", "CS (0.3 < SD7DR);Jet PT;", Bin, Binning);            HCSSD7DR3.Sumw2();

   TFile File(InputFileName.c_str());

   TTree *T = (TTree *)File.Get("jetTree");

   vector<double> *SigPT = NULL, *SigEta = NULL, *SigPhi = NULL, *SigSD0DR = NULL, *SigSD7DR = NULL;
   vector<double> *CSPT = NULL, *CSEta = NULL, *CSPhi = NULL, *CSSD0DR = NULL, *CSSD7DR = NULL;
   vector<double> *W = NULL;

   if(Jewel == false)
   {
      T->SetBranchAddress("sigJetPt", &SigPT);
      T->SetBranchAddress("sigJetEta", &SigEta);
      T->SetBranchAddress("sigJetPhi", &SigPhi);
      T->SetBranchAddress("sigJetSDdr12", &SigSD0DR);
      T->SetBranchAddress("sigJetSD2dr12", &SigSD7DR);
      T->SetBranchAddress("csJetPt", &CSPT);
      T->SetBranchAddress("csJetEta", &CSEta);
      T->SetBranchAddress("csJetPhi", &CSPhi);
      T->SetBranchAddress("csJetSDdr12", &CSSD0DR);
      T->SetBranchAddress("csJetSD2dr12", &CSSD7DR);
      T->SetBranchAddress("eventWeight", &W);
   }
   else
   {
      T->SetBranchAddress("sigJetJewelPt", &SigPT);
      T->SetBranchAddress("sigJetJewelEta", &SigEta);
      T->SetBranchAddress("sigJetJewelPhi", &SigPhi);
      T->SetBranchAddress("sigJetSDJeweldr12", &SigSD0DR);
      T->SetBranchAddress("sigJetSD2Jeweldr12", &SigSD7DR);
      T->SetBranchAddress("csJetJewelPt", &CSPT);
      T->SetBranchAddress("csJetJewelEta", &CSEta);
      T->SetBranchAddress("csJetJewelPhi", &CSPhi);
      T->SetBranchAddress("csJetSDJeweldr12", &CSSD0DR);
      T->SetBranchAddress("csJetSD2Jeweldr12", &CSSD7DR);
      T->SetBranchAddress("eventWeight", &W);
   }

   double TotalWeight = 0;

   int EntryCount = T->GetEntries();
   int Mod = ((EntryCount > 500) ? (EntryCount / 300) : 1);
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(5);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.PrintWithMod(Mod);

      T->GetEntry(iE);

      TotalWeight = TotalWeight + (*W)[0];

      for(int iJ = 0; iJ < (int)SigPT->size(); iJ++)
      {
         if(fabs((*SigEta)[iJ]) > 1.3)
            continue;

         HSig.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD0DR)[iJ] < 0.1)
            HSigSD0DR0.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD0DR)[iJ] < 0.2 && (*SigSD0DR)[iJ] > 0.1)
            HSigSD0DR1.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD0DR)[iJ] < 0.3 && (*SigSD0DR)[iJ] > 0.2)
            HSigSD0DR2.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD0DR)[iJ] > 0.3)
            HSigSD0DR3.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD7DR)[iJ] < 0.1)
            HSigSD7DR0.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD7DR)[iJ] < 0.2 && (*SigSD7DR)[iJ] > 0.1)
            HSigSD7DR1.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD7DR)[iJ] < 0.3 && (*SigSD7DR)[iJ] > 0.2)
            HSigSD7DR2.Fill((*SigPT)[iJ], (*W)[0]);
         if((*SigSD7DR)[iJ] > 0.3)
            HSigSD7DR3.Fill((*SigPT)[iJ], (*W)[0]);
         HCS.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD0DR)[iJ] < 0.1)
            HCSSD0DR0.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD0DR)[iJ] < 0.2 && (*CSSD0DR)[iJ] > 0.1)
            HCSSD0DR1.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD0DR)[iJ] < 0.3 && (*CSSD0DR)[iJ] > 0.2)
            HCSSD0DR2.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD0DR)[iJ] > 0.3)
            HCSSD0DR3.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD7DR)[iJ] < 0.1)
            HCSSD7DR0.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD7DR)[iJ] < 0.2 && (*CSSD7DR)[iJ] > 0.1)
            HCSSD7DR1.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD7DR)[iJ] < 0.3 && (*CSSD7DR)[iJ] > 0.2)
            HCSSD7DR2.Fill((*CSPT)[iJ], (*W)[0]);
         if((*CSSD7DR)[iJ] > 0.3)
            HCSSD7DR3.Fill((*CSPT)[iJ], (*W)[0]);
      }
   }

   TidyHistogram(HSig, TotalWeight);
   TidyHistogram(HSigSD0DR0, TotalWeight);
   TidyHistogram(HSigSD0DR1, TotalWeight);
   TidyHistogram(HSigSD0DR2, TotalWeight);
   TidyHistogram(HSigSD0DR3, TotalWeight);
   TidyHistogram(HSigSD7DR0, TotalWeight);
   TidyHistogram(HSigSD7DR1, TotalWeight);
   TidyHistogram(HSigSD7DR2, TotalWeight);
   TidyHistogram(HSigSD7DR3, TotalWeight);
   TidyHistogram(HCS, TotalWeight);
   TidyHistogram(HCSSD0DR0, TotalWeight);
   TidyHistogram(HCSSD0DR1, TotalWeight);
   TidyHistogram(HCSSD0DR2, TotalWeight);
   TidyHistogram(HCSSD0DR3, TotalWeight);
   TidyHistogram(HCSSD7DR0, TotalWeight);
   TidyHistogram(HCSSD7DR1, TotalWeight);
   TidyHistogram(HCSSD7DR2, TotalWeight);
   TidyHistogram(HCSSD7DR3, TotalWeight);

   PdfFile.AddPlot(HSig);
   PdfFile.AddPlot(HSigSD0DR0);
   PdfFile.AddPlot(HSigSD0DR1);
   PdfFile.AddPlot(HSigSD0DR2);
   PdfFile.AddPlot(HSigSD0DR3);
   PdfFile.AddPlot(HSigSD7DR0);
   PdfFile.AddPlot(HSigSD7DR1);
   PdfFile.AddPlot(HSigSD7DR2);
   PdfFile.AddPlot(HSigSD7DR3);
   PdfFile.AddPlot(HCS);
   PdfFile.AddPlot(HCSSD0DR0);
   PdfFile.AddPlot(HCSSD0DR1);
   PdfFile.AddPlot(HCSSD0DR2);
   PdfFile.AddPlot(HCSSD0DR3);
   PdfFile.AddPlot(HCSSD7DR0);
   PdfFile.AddPlot(HCSSD7DR1);
   PdfFile.AddPlot(HCSSD7DR2);
   PdfFile.AddPlot(HCSSD7DR3);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   HSig.SetMarkerColor(kRed);
   HSig.SetLineColor(kRed);

   HSig.Draw();
   HCS.Draw("same");

   PdfFile.AddCanvas(C);

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   OutputFile.cd();

   HSig.Write();
   HSigSD0DR0.Write();
   HSigSD0DR1.Write();
   HSigSD0DR2.Write();
   HSigSD0DR3.Write();
   HSigSD7DR0.Write();
   HSigSD7DR1.Write();
   HSigSD7DR2.Write();
   HSigSD7DR3.Write();
   HCS.Write();
   HCSSD0DR0.Write();
   HCSSD0DR1.Write();
   HCSSD0DR2.Write();
   HCSSD0DR3.Write();
   HCSSD7DR0.Write();
   HCSSD7DR1.Write();
   HCSSD7DR2.Write();
   HCSSD7DR3.Write();

   OutputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void TidyHistogram(TH1D &H, double TotalWeight)
{
   H.SetMarkerStyle(20);
   H.SetLineWidth(2);
   H.SetStats(0);
   H.Scale(1 / TotalWeight);
   DivideByBinWidth(H);
}

void DivideByBinWidth(TH1D &H)
{
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double L = H.GetXaxis()->GetBinLowEdge(i);
      double R = H.GetXaxis()->GetBinUpEdge(i);

      H.SetBinContent(i, H.GetBinContent(i) / (R - L));
      H.SetBinError(i, H.GetBinError(i) / (R - L));
   }
}

