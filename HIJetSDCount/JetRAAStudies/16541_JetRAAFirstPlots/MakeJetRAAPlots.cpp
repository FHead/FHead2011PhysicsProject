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

int main();
void DivideByBinWidth(TH1D &H);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Result.pdf");
   PdfFile.AddTextPage("Result");

   int Bin = 20;
   double Binning[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 225, 250, 275, 300, 350, 400, 450, 500, 700, 1000};

   TH1D HSig("HSig", ";Jet PT;", 20, Binning);   HSig.Sumw2();
   TH1D HCS("HCS", ";Jet PT;", 20, Binning);     HCS.Sumw2();

   TFile File("16532Samples/Result_RecoilOff_S.root");

   TTree *T = (TTree *)File.Get("jetTree");

   vector<double> *SigPT = NULL, *SigEta = NULL, *SigPhi = NULL;
   vector<double> *CSPT = NULL, *CSEta = NULL, *CSPhi = NULL;
   vector<double> *W = NULL;

   T->SetBranchAddress("sigJetPt", &SigPT);
   T->SetBranchAddress("sigJetEta", &SigEta);
   T->SetBranchAddress("sigJetPhi", &SigPhi);
   T->SetBranchAddress("csJetPt", &CSPT);
   T->SetBranchAddress("csJetEta", &CSEta);
   T->SetBranchAddress("csJetPhi", &CSPhi);
   T->SetBranchAddress("eventWeight", &W);

   int EntryCount = T->GetEntries();
   int Mod = ((EntryCount > 500) ? (EntryCount / 300) : 1);
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(5);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.PrintWithMod(Mod);

      T->GetEntry(iE);

      for(int iJ = 0; iJ < (int)SigPT->size(); iJ++)
      {
         if(fabs((*SigEta)[iJ]) > 1.3)
            continue;

         HSig.Fill((*SigPT)[iJ], (*W)[0]);
         HCS.Fill((*CSPT)[iJ] * 0.95, (*W)[0]);
      }
   }

   DivideByBinWidth(HSig);
   DivideByBinWidth(HCS);

   PdfFile.AddPlot(HSig);
   PdfFile.AddPlot(HCS);

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

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
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

