#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "DataHelper.h"

#include "MBReadTree.h"

int main(int argc, char *argv[]);
void RhoCentrality(PdfFileHelper &PdfFile, SmearTreeMessenger &M, string DHFileName, string State);
void SmearRMS(PdfFileHelper &PdfFile, SmearTreeMessenger &M, string ReferenceFileName, string GraphName);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SmearTree" << endl;
      return -1;
   }

   PdfFileHelper PdfFile("UnitTest.pdf");
   PdfFile.AddTextPage("Sanity checks");

   // TFile File("../../Samples/SmearTree/16333Type6Stock/PP6Dijet.root");
   TFile File(argv[1]);
   
   SmearTreeMessenger M(File, "OutputTree", true, 0);   // SD doesn't matter
   if(M.Tree == NULL)
      return -1;

   RhoCentrality(PdfFile, M, "RhoDatabase.dh", "AA6DijetCymbal");
   SmearRMS(PdfFile, M, "CentralityDependence.root", "SmearPP6DijetV1InJet");

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void RhoCentrality(PdfFileHelper &PdfFile, SmearTreeMessenger &M, string DHFileName, string State)
{
   PdfFile.AddTextPage("Checking extraction of rho");

   double Max = 300;
   int Bin = 300;
   int BinFine = 2000;

   TH1D H1("H1", ";Rho;a.u.", Bin, 0, Max);   // 0-5%
   TH1D H2("H2", ";Rho;a.u.", Bin, 0, Max);   // 15-20%
   TH1D H3("H3", ";Rho;a.u.", Bin, 0, Max);   // 30-35%
   TH1D H4("H4", ";Rho;a.u.", Bin, 0, Max);   // 45-50%
   TH1D H5("H5", ";Rho;a.u.", Bin, 0, Max);   // 60-65%

   int EntryCount = M.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      M.GetEntry(iE);

      if(M.CentralityInt() >= 0 && M.CentralityInt() < 5)
         H1.Fill(M.Rho, M.MCWeight);
      if(M.CentralityInt() >= 15 && M.CentralityInt() < 20)
         H2.Fill(M.Rho, M.MCWeight);
      if(M.CentralityInt() >= 30 && M.CentralityInt() < 35)
         H3.Fill(M.Rho, M.MCWeight);
      if(M.CentralityInt() >= 45 && M.CentralityInt() < 50)
         H4.Fill(M.Rho, M.MCWeight);
      if(M.CentralityInt() >= 60 && M.CentralityInt() < 65)
         H5.Fill(M.Rho, M.MCWeight);
   }

   double Scale = H1.Integral() * ((Max - 0) / Bin);
   H1.Scale(1 / Scale);
   H2.Scale(1 / Scale);
   H3.Scale(1 / Scale);
   H4.Scale(1 / Scale);
   H5.Scale(1 / Scale);

   TH1D G1("G1", ";Rho;a.u.", BinFine, 0, Max);
   TH1D G2("G2", ";Rho;a.u.", BinFine, 0, Max);
   TH1D G3("G3", ";Rho;a.u.", BinFine, 0, Max);
   TH1D G4("G4", ";Rho;a.u.", BinFine, 0, Max);
   TH1D G5("G5", ";Rho;a.u.", BinFine, 0, Max);

   DataHelper DHFile(DHFileName);

   double A[100] = {0};
   double B[100] = {0};
   double C[100] = {0};
   for(int i = 0; i < 99; i++)
   {
      A[i] = DHFile[State][Form("C%02d_A", i)].GetDouble();
      B[i] = DHFile[State][Form("C%02d_B", i)].GetDouble();
      C[i] = DHFile[State][Form("C%02d_C", i)].GetDouble();
   }
   
   for(int i = 1; i <= BinFine; i++)
   {
      double x = G1.GetXaxis()->GetBinCenter(i);

      for(int j = 0; j < 5; j++)
         G1.Fill(x, A[j] * exp(-(x - B[j]) * (x - B[j]) / (2 * C[j] * C[j])));
      for(int j = 15; j < 20; j++)
         G2.Fill(x, A[j] * exp(-(x - B[j]) * (x - B[j]) / (2 * C[j] * C[j])));
      for(int j = 30; j < 35; j++)
         G3.Fill(x, A[j] * exp(-(x - B[j]) * (x - B[j]) / (2 * C[j] * C[j])));
      for(int j = 45; j < 50; j++)
         G4.Fill(x, A[j] * exp(-(x - B[j]) * (x - B[j]) / (2 * C[j] * C[j])));
      for(int j = 60; j < 65; j++)
         G5.Fill(x, A[j] * exp(-(x - B[j]) * (x - B[j]) / (2 * C[j] * C[j])));
   }

   Scale = G1.Integral() * ((Max - 0) / BinFine);
   G1.Scale(1 / Scale);
   G2.Scale(1 / Scale);
   G3.Scale(1 / Scale);
   G4.Scale(1 / Scale);
   G5.Scale(1 / Scale);

   G1.SetLineColor(kRed);
   G2.SetLineColor(kRed);
   G3.SetLineColor(kRed);
   G4.SetLineColor(kRed);
   G5.SetLineColor(kRed);

   TH2D HWorld("HWorld", ";Rho;a.u.", 100, 0, Max, 100, 0, H5.GetMaximum() * 1.1);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw();

   H1.Draw("same");
   H2.Draw("same");
   H3.Draw("same");
   H4.Draw("same");
   H5.Draw("same");

   G1.Draw("same hist");
   G2.Draw("same hist");
   G3.Draw("same hist");
   G4.Draw("same hist");
   G5.Draw("same hist");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&H1, "Smear tree", "p");
   Legend.AddEntry(&G1, "DHFile", "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

void SmearRMS(PdfFileHelper &PdfFile, SmearTreeMessenger &M, string ReferenceFileName, string GraphName)
{
   double Total0[101] = {0};
   double Total1[101] = {0};
   double Total2[101] = {0};
   
   PdfFile.AddTextPage("Check RMS reference graph");

   int EntryCount = M.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      M.GetEntry(iE);

      int C = M.CentralityInt();
      double ExcessPT = M.PTInJet - M.Rho * 0.4 * 0.4 * M_PI;

      Total0[C] = Total0[C] + M.MCWeight;
      Total1[C] = Total1[C] + M.MCWeight * ExcessPT;
      Total2[C] = Total2[C] + M.MCWeight * ExcessPT * ExcessPT;
   }

   TGraph G;
   for(int i = 0; i <= 100; i++)
   {
      if(Total0[i] == 0)
         continue;

      double RMS = sqrt((Total2[i] - Total1[i] * Total1[i] / Total0[i]) / Total0[i]);

      G.SetPoint(G.GetN(), 0.01 * i, RMS);
   }

   TFile File(ReferenceFileName.c_str());

   TGraph *GReference = (TGraph *)File.Get(GraphName.c_str());
   if(GReference != NULL)
      GReference->SetLineColor(kRed);

   TCanvas C;

   G.Draw("ap");
   if(GReference != NULL)
      GReference->Draw("l");

   G.GetXaxis()->SetTitle("Centrality");
   G.GetYaxis()->SetTitle("RMS");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&G, "Smear tree", "p");
   Legend.AddEntry(GReference, "Reference", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   File.Close();
}







