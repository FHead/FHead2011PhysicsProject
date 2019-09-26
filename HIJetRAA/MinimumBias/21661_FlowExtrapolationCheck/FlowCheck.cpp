#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   TFile File("Forest.root");

   TTree *Tree = (TTree *)File.Get("pfcandAnalyzer/pfTree");

   vector<int> *pfId = nullptr;
   vector<float> *pfPt = nullptr;
   vector<float> *pfEta = nullptr;
   vector<float> *pfPhi = nullptr;

   Tree->SetBranchAddress("pfId", &pfId);
   Tree->SetBranchAddress("pfPt", &pfPt);
   Tree->SetBranchAddress("pfEta", &pfEta);
   Tree->SetBranchAddress("pfPhi", &pfPhi);

   PdfFileHelper PdfFile("Output.pdf");
   PdfFile.AddTextPage("Flow check");

   TH2D HEtaPhi("HEtaPhi", ";#eta;#phi", 50, -2.5, 2.5, 50, -M_PI, M_PI);
   TH1D HChi2("HChi2", ";#chi^{2};", 20, 0, 50);

   HEtaPhi.SetStats(0);
   HChi2.SetStats(0);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int NPF = pfId->size();

      TH1D H1("H1", ";;", 10, -M_PI, M_PI);   H1.Sumw2();
      TH1D H2("H2", ";;", 10, -M_PI, M_PI);   H2.Sumw2();

      for(int iPF = 0; iPF < NPF; iPF++)
      {
         if((*pfId)[iPF] != 1)
            continue;
         if((*pfPt)[iPF] < 0.3 || (*pfPt)[iPF] > 3)
            continue;

         HEtaPhi.Fill((*pfEta)[iPF], (*pfPhi)[iPF]);

         if(fabs((*pfEta)[iPF]) < 1)
            H1.Fill((*pfPhi)[iPF]);
         else if(fabs((*pfEta)[iPF]) < 2)
            H2.Fill((*pfPhi)[iPF]);
      }

      bool Good = true;
      for(int i = 1; i <= 10; i++)
         if(H1.GetBinContent(i) < 10)
            Good = false;
      if(Good == false)
         continue;

      TF1 F("F", "[0]*(1+[1]*cos(2*x)+[2]*sin(2*x)+[3]*cos(3*x)+[4]*sin(3*x))", -M_PI, M_PI);

      H1.Fit(&F);

      if(iE < 20)
      {
         PdfFile.AddTextPage("Event");
         PdfFile.AddPlot(H1);
      }

      F.SetParameter(0, H2.Integral() / 10);

      if(iE < 20)
      {
         TCanvas Canvas;

         H2.Draw();
         F.Draw("same");

         PdfFile.AddCanvas(Canvas);
      }

      double Chi2 = 0;
      for(int i = 1; i <= 10; i++)
      {
         double x = H2.GetXaxis()->GetBinCenter(i);
         double y = F.Eval(x);

         double Chi = (y - H2.GetBinContent(i)) / H2.GetBinError(i);
         Chi2 = Chi2 + Chi * Chi;
      }

      HChi2.Fill(Chi2);
   }

   PdfFile.AddPlot(HEtaPhi, "colz");

   HChi2.Scale(1 / HChi2.Integral() / (double(50 - 0) / 20));

   TCanvas Canvas;

   TH1D H("H", ";;", 1000, 0, 50);
   for(int i = 1; i <= 1000; i++)
   {
      double x1 = H.GetXaxis()->GetBinLowEdge(i);
      double x2 = H.GetXaxis()->GetBinUpEdge(i);
      double y1 = TMath::Prob(x1, 10);
      double y2 = TMath::Prob(x2, 10);
      double m = -(y2 - y1) / (x2 - x1);
      H.SetBinContent(i, m);
   }

   H.Scale(1 / H.Integral() / (double(50 - 0) / 1000));

   HChi2.Draw();
   // H.Draw("same hist");
   Canvas.SetLogy();
   
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}




