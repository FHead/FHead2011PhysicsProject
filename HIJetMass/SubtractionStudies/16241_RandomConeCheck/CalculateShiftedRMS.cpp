#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

#define CBinCount 100
#define EtaBinCount 130

int main()
{
   SetThesisStyle();

   TFile File("MBCymbal.root");
   TFile FileReference("CentralityDependence.root");

   PdfFileHelper PdfFile("CorrectedRMS.pdf");
   PdfFile.AddTextPage("eta-corrected RMS");

   TTree *Tree = (TTree *)File.Get("T");

   double Eta, Phi, Rho, TotalPT, Centrality;
   Tree->SetBranchAddress("Eta", &Eta);
   Tree->SetBranchAddress("Phi", &Phi);
   Tree->SetBranchAddress("Rho", &Rho);
   Tree->SetBranchAddress("TotalPT", &TotalPT);
   Tree->SetBranchAddress("Centrality", &Centrality);

   double Total2[CBinCount][EtaBinCount] = {{0}};
   double Total[CBinCount][EtaBinCount] = {{0}};
   double Count[CBinCount][EtaBinCount] = {{0}};

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int CBin = int(Centrality * 100);
      int EtaBin = int(fabs(Eta) * 100);

      if(EtaBin >= EtaBinCount || CBin >= CBinCount)   // WTF
         continue;

      Total2[CBin][EtaBin] = Total2[CBin][EtaBin] + (TotalPT - Rho * 0.4 * 0.4 * PI) * (TotalPT - Rho * 0.4 * 0.4 * PI);
      Total[CBin][EtaBin] = Total[CBin][EtaBin] + (TotalPT - Rho * 0.4 * 0.4 * PI);
      Count[CBin][EtaBin] = Count[CBin][EtaBin] + 1;
   }

   TH2D HMean("HMean", "Mean of the subtracted random cone;Centrality;|eta|", CBinCount, 0, 1, EtaBinCount, 0, 1.3);
   HMean.SetStats(0);
   
   TH2D HRMS("HRMS", "RMS of the subtracted random cone;Centrality;|eta|", CBinCount, 0, 1, EtaBinCount, 0, 1.3);
   HRMS.SetStats(0);

   double Mean[CBinCount][EtaBinCount] = {{0}};
   double RMS[CBinCount][EtaBinCount] = {{0}};
   for(int iC = 0; iC < CBinCount; iC++)
   {
      for(int iEta = 0; iEta < EtaBinCount; iEta++)
      {
         Mean[iC][iEta] = Total[iC][iEta] / Count[iC][iEta];
         HMean.SetBinContent(iC + 1, iEta + 1, Mean[iC][iEta]);
         
         RMS[iC][iEta] = sqrt((Total2[iC][iEta] - Total[iC][iEta] * Mean[iC][iEta]) / (Count[iC][iEta] - 1));
         HRMS.SetBinContent(iC + 1, iEta + 1, RMS[iC][iEta]);
      }
   }

   PdfFile.AddPlot(HMean, "colz");
   PdfFile.AddPlot(HRMS, "colz");

   double Total2Eta[CBinCount] = {0};
   double TotalEta[CBinCount] = {0};
   double CountEta[CBinCount] = {0};

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int CBin = int(Centrality * 100);
      int EtaBin = int(fabs(Eta) * 100);

      if(EtaBin >= EtaBinCount || CBin >= CBinCount)   // WTF
         continue;

      double D = (TotalPT - Rho * 0.4 * 0.4 * PI) - Mean[CBin][EtaBin];

      Total2Eta[CBin] = Total2Eta[CBin] + D * D;
      TotalEta[CBin] = TotalEta[CBin] + D;
      CountEta[CBin] = CountEta[CBin] + 1;
   }

   double RMSEta[CBinCount] = {0};

   for(int iC = 0; iC < CBinCount; iC++)
   {
      if(CountEta[iC] > 1)
         RMSEta[iC] = sqrt((Total2Eta[iC] - TotalEta[iC] * TotalEta[iC] / CountEta[iC]) / (CountEta[iC] - 1));
      else
         RMSEta[iC] = 0;

      cout << iC << " " << RMS[iC] << endl;
   }

   TGraph G;
   for(int iC = 0; iC < CBinCount; iC++)
      G.SetPoint(iC, (iC + 1) * 0.01, RMSEta[iC]);

   G.SetMarkerColor(kRed);
   G.SetLineColor(kRed);

   TCanvas C;

   TGraphErrors *GReference = (TGraphErrors *)FileReference.Get("CymbalMB");

   GReference->Draw("ap");
   G.Draw("p");

   GReference->GetXaxis()->SetTitle("Centrality");
   GReference->GetYaxis()->SetTitle("RMS");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&G, "New", "p");
   Legend.AddEntry(GReference, "Reference", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   File.Close();

   return 0;
}






