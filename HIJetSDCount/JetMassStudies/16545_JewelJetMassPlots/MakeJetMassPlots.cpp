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

   bool WithBackground = false;
   if(OutputBase.find("PB") != string::npos || OutputBase.find("SB") != string::npos)
      WithBackground = true;

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Result");

   // int Bin = 6;
   // double Binning[] = {0.0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30};
   // int Bin = 10;
   // double Binning[] = {0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.18, 0.22, 0.26, 0.30};
   int Bin0 = 10;
   double Binning0[] = {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.24, 0.27};
   int Bin7 = 10;
   double Binning7[] = {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26, 0.30};

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HSD0SigPT0("HSD0SigPT0", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT0.Sumw2();
   TH1D HSD0SigPT1("HSD0SigPT1", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT1.Sumw2();
   TH1D HSD0SigPT2("HSD0SigPT2", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT2.Sumw2();
   TH1D HSD0SigPT3("HSD0SigPT3", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT3.Sumw2();
   TH1D HSD0SigPT4("HSD0SigPT4", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT4.Sumw2();
   TH1D HSD0SigPT5("HSD0SigPT5", "Sig;Mass / Jet PT;", Bin0, Binning0);     HSD0SigPT5.Sumw2();
   TH1D HSD0CSPT0("HSD0CSPT0", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT0.Sumw2();
   TH1D HSD0CSPT1("HSD0CSPT1", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT1.Sumw2();
   TH1D HSD0CSPT2("HSD0CSPT2", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT2.Sumw2();
   TH1D HSD0CSPT3("HSD0CSPT3", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT3.Sumw2();
   TH1D HSD0CSPT4("HSD0CSPT4", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT4.Sumw2();
   TH1D HSD0CSPT5("HSD0CSPT5", "CS;Mass / Jet PT;", Bin0, Binning0);        HSD0CSPT5.Sumw2();
   TH1D HSD7SigPT0("HSD7SigPT0", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT0.Sumw2();
   TH1D HSD7SigPT1("HSD7SigPT1", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT1.Sumw2();
   TH1D HSD7SigPT2("HSD7SigPT2", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT2.Sumw2();
   TH1D HSD7SigPT3("HSD7SigPT3", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT3.Sumw2();
   TH1D HSD7SigPT4("HSD7SigPT4", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT4.Sumw2();
   TH1D HSD7SigPT5("HSD7SigPT5", "Sig;Mass / Jet PT;", Bin7, Binning7);     HSD7SigPT5.Sumw2();
   TH1D HSD7CSPT0("HSD7CSPT0", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT0.Sumw2();
   TH1D HSD7CSPT1("HSD7CSPT1", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT1.Sumw2();
   TH1D HSD7CSPT2("HSD7CSPT2", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT2.Sumw2();
   TH1D HSD7CSPT3("HSD7CSPT3", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT3.Sumw2();
   TH1D HSD7CSPT4("HSD7CSPT4", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT4.Sumw2();
   TH1D HSD7CSPT5("HSD7CSPT5", "CS;Mass / Jet PT;", Bin7, Binning7);        HSD7CSPT5.Sumw2();

   TFile File(InputFileName.c_str());

   TTree *T = (TTree *)File.Get("jetTree");

   vector<double> *SigPT = NULL, *SigEta = NULL, *SigPhi = NULL, *SigSD0DR = NULL, *SigSD7DR = NULL, *SigSD0Mass = NULL, *SigSD7Mass = NULL;
   vector<double> *CSPT = NULL, *CSEta = NULL, *CSPhi = NULL, *CSSD0DR = NULL, *CSSD7DR = NULL, *CSSD0Mass = NULL, *CSSD7Mass = NULL;
   vector<double> *W = NULL;

   if(Jewel == false)
   {
      T->SetBranchAddress("sigJetPt", &SigPT);
      T->SetBranchAddress("sigJetEta", &SigEta);
      T->SetBranchAddress("sigJetPhi", &SigPhi);
      T->SetBranchAddress("sigJetSDdr12", &SigSD0DR);
      T->SetBranchAddress("sigJetSD2dr12", &SigSD7DR);
      T->SetBranchAddress("sigJetSDM", &SigSD0Mass);
      T->SetBranchAddress("sigJetSD2M", &SigSD7Mass);
      T->SetBranchAddress("csJetPt", &CSPT);
      T->SetBranchAddress("csJetEta", &CSEta);
      T->SetBranchAddress("csJetPhi", &CSPhi);
      T->SetBranchAddress("csJetSDdr12", &CSSD0DR);
      T->SetBranchAddress("csJetSD2dr12", &CSSD7DR);
      T->SetBranchAddress("csJetSDM", &CSSD0Mass);
      T->SetBranchAddress("csJetSD2M", &CSSD7Mass);
      T->SetBranchAddress("eventWeight", &W);
   }
   else
   {
      T->SetBranchAddress("sigJetJewelPt", &SigPT);
      T->SetBranchAddress("sigJetJewelEta", &SigEta);
      T->SetBranchAddress("sigJetJewelPhi", &SigPhi);
      T->SetBranchAddress("sigJetSDJeweldr12", &SigSD0DR);
      T->SetBranchAddress("sigJetSD2Jeweldr12", &SigSD7DR);
      T->SetBranchAddress("sigJetSDJewelM", &SigSD0Mass);
      T->SetBranchAddress("sigJetSD2JewelM", &SigSD7Mass);
      T->SetBranchAddress("csJetJewelPt", &CSPT);
      T->SetBranchAddress("csJetJewelEta", &CSEta);
      T->SetBranchAddress("csJetJewelPhi", &CSPhi);
      T->SetBranchAddress("csJetSDJeweldr12", &CSSD0DR);
      T->SetBranchAddress("csJetSD2Jeweldr12", &CSSD7DR);
      T->SetBranchAddress("csJetSDJewelM", &CSSD0Mass);
      T->SetBranchAddress("csJetSD2JewelM", &CSSD7Mass);
      T->SetBranchAddress("eventWeight", &W);
   }

   double TotalWeight = 0;

   int EntryCount = T->GetEntries();
   int Mod = ((EntryCount > 500) ? (EntryCount / 300) : 1);
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(5);

   double Hack = 1;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.PrintWithMod(Mod);

      T->GetEntry(iE);

      TotalWeight = TotalWeight + (*W)[0];

      for(int iJ = 0; iJ < (int)SigPT->size(); iJ++)
      {
         if(fabs((*SigEta)[iJ]) > 1.3 || (*CSEta)[iJ] > 5)
            continue;

         if((*SigSD0DR)[iJ] > 0.1)
         {
            double Ratio = (*SigSD0Mass)[iJ] / (*SigPT)[iJ] * Hack;
            if((*SigPT)[iJ] >= 120 && (*SigPT)[iJ] < 140)   HSD0SigPT0.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 140 && (*SigPT)[iJ] < 160)   HSD0SigPT1.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 160 && (*SigPT)[iJ] < 180)   HSD0SigPT2.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 180 && (*SigPT)[iJ] < 200)   HSD0SigPT3.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 200 && (*SigPT)[iJ] < 300)   HSD0SigPT4.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 300 && (*SigPT)[iJ] < 500)   HSD0SigPT5.Fill(Ratio, (*W)[0]);
         }
         if((*SigSD7DR)[iJ] > 0.1)
         {
            double Ratio = (*SigSD7Mass)[iJ] / (*SigPT)[iJ] * Hack;
            if((*SigPT)[iJ] >= 120 && (*SigPT)[iJ] < 140)   HSD7SigPT0.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 140 && (*SigPT)[iJ] < 160)   HSD7SigPT1.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 160 && (*SigPT)[iJ] < 180)   HSD7SigPT2.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 180 && (*SigPT)[iJ] < 200)   HSD7SigPT3.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 200 && (*SigPT)[iJ] < 300)   HSD7SigPT4.Fill(Ratio, (*W)[0]);
            if((*SigPT)[iJ] >= 300 && (*SigPT)[iJ] < 500)   HSD7SigPT5.Fill(Ratio, (*W)[0]);
         }
         if((*CSSD0DR)[iJ] > 0.1)
         {
            double Ratio = (*CSSD0Mass)[iJ] / (*CSPT)[iJ] * Hack;
            if((*CSPT)[iJ] >= 120 && (*CSPT)[iJ] < 140)   HSD0CSPT0.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 140 && (*CSPT)[iJ] < 160)   HSD0CSPT1.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 160 && (*CSPT)[iJ] < 180)   HSD0CSPT2.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 180 && (*CSPT)[iJ] < 200)   HSD0CSPT3.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 200 && (*CSPT)[iJ] < 300)   HSD0CSPT4.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 300 && (*CSPT)[iJ] < 500)   HSD0CSPT5.Fill(Ratio, (*W)[0]);
         }
         if((*CSSD7DR)[iJ] > 0.1)
         {
            double Ratio = (*CSSD7Mass)[iJ] / (*CSPT)[iJ] * Hack;
            if((*CSPT)[iJ] >= 120 && (*CSPT)[iJ] < 140)   HSD7CSPT0.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 140 && (*CSPT)[iJ] < 160)   HSD7CSPT1.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 160 && (*CSPT)[iJ] < 180)   HSD7CSPT2.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 180 && (*CSPT)[iJ] < 200)   HSD7CSPT3.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 200 && (*CSPT)[iJ] < 300)   HSD7CSPT4.Fill(Ratio, (*W)[0]);
            if((*CSPT)[iJ] >= 300 && (*CSPT)[iJ] < 500)   HSD7CSPT5.Fill(Ratio, (*W)[0]);
         }
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   TidyHistogram(HSD0SigPT0, TotalWeight);
   TidyHistogram(HSD0SigPT1, TotalWeight);
   TidyHistogram(HSD0SigPT2, TotalWeight);
   TidyHistogram(HSD0SigPT3, TotalWeight);
   TidyHistogram(HSD0SigPT4, TotalWeight);
   TidyHistogram(HSD0SigPT5, TotalWeight);
   TidyHistogram(HSD0CSPT0, TotalWeight);
   TidyHistogram(HSD0CSPT1, TotalWeight);
   TidyHistogram(HSD0CSPT2, TotalWeight);
   TidyHistogram(HSD0CSPT3, TotalWeight);
   TidyHistogram(HSD0CSPT4, TotalWeight);
   TidyHistogram(HSD0CSPT5, TotalWeight);
   TidyHistogram(HSD7SigPT0, TotalWeight);
   TidyHistogram(HSD7SigPT1, TotalWeight);
   TidyHistogram(HSD7SigPT2, TotalWeight);
   TidyHistogram(HSD7SigPT3, TotalWeight);
   TidyHistogram(HSD7SigPT4, TotalWeight);
   TidyHistogram(HSD7SigPT5, TotalWeight);
   TidyHistogram(HSD7CSPT0, TotalWeight);
   TidyHistogram(HSD7CSPT1, TotalWeight);
   TidyHistogram(HSD7CSPT2, TotalWeight);
   TidyHistogram(HSD7CSPT3, TotalWeight);
   TidyHistogram(HSD7CSPT4, TotalWeight);
   TidyHistogram(HSD7CSPT5, TotalWeight);

   PdfFile.AddPlot(HSD0SigPT0);
   PdfFile.AddPlot(HSD0SigPT1);
   PdfFile.AddPlot(HSD0SigPT2);
   PdfFile.AddPlot(HSD0SigPT3);
   PdfFile.AddPlot(HSD0SigPT4);
   PdfFile.AddPlot(HSD0SigPT5);
   PdfFile.AddPlot(HSD0CSPT0);
   PdfFile.AddPlot(HSD0CSPT1);
   PdfFile.AddPlot(HSD0CSPT2);
   PdfFile.AddPlot(HSD0CSPT3);
   PdfFile.AddPlot(HSD0CSPT4);
   PdfFile.AddPlot(HSD0CSPT5);
   PdfFile.AddPlot(HSD7SigPT0);
   PdfFile.AddPlot(HSD7SigPT1);
   PdfFile.AddPlot(HSD7SigPT2);
   PdfFile.AddPlot(HSD7SigPT3);
   PdfFile.AddPlot(HSD7SigPT4);
   PdfFile.AddPlot(HSD7SigPT5);
   PdfFile.AddPlot(HSD7CSPT0);
   PdfFile.AddPlot(HSD7CSPT1);
   PdfFile.AddPlot(HSD7CSPT2);
   PdfFile.AddPlot(HSD7CSPT3);
   PdfFile.AddPlot(HSD7CSPT4);
   PdfFile.AddPlot(HSD7CSPT5);

   File.Close();

   OutputFile.cd();

   HSD0SigPT0.Write();
   HSD0SigPT1.Write();
   HSD0SigPT2.Write();
   HSD0SigPT3.Write();
   HSD0SigPT4.Write();
   HSD0SigPT5.Write();
   HSD0CSPT0.Write();
   HSD0CSPT1.Write();
   HSD0CSPT2.Write();
   HSD0CSPT3.Write();
   HSD0CSPT4.Write();
   HSD0CSPT5.Write();
   HSD7SigPT0.Write();
   HSD7SigPT1.Write();
   HSD7SigPT2.Write();
   HSD7SigPT3.Write();
   HSD7SigPT4.Write();
   HSD7SigPT5.Write();
   HSD7CSPT0.Write();
   HSD7CSPT1.Write();
   HSD7CSPT2.Write();
   HSD7CSPT3.Write();
   HSD7CSPT4.Write();
   HSD7CSPT5.Write();

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
   DivideByBinWidth(H);
}

void DivideByBinWidth(TH1D &H)
{
   H.Scale(1 / H.Integral());
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double L = H.GetXaxis()->GetBinLowEdge(i);
      double R = H.GetXaxis()->GetBinUpEdge(i);

      H.SetBinContent(i, H.GetBinContent(i) / (R - L));
      H.SetBinError(i, H.GetBinError(i) / (R - L));
   }
}

