#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"

int main()
{
   TFile File("OutputFile_EventF_2e2mu.root");
   TTree *ResultTree = (TTree *)File.Get("ResultTree");

   TH2D HDensity3("HDensity3", "A3 Fit Result;real(A3/A);imag(A3/A)", 100, -1, 1, 100, -1, 1);
   TH2D HDensity2("HDensity2", "A2 Fit Result;real(A2/A);imag(A2/A)", 100, -1, 1, 100, -1, 1);

   float A2A1, A3A1, A2Phase, A3Phase;
   ResultTree->SetBranchAddress("A2A1", &A2A1);
   ResultTree->SetBranchAddress("A3A1", &A3A1);
   ResultTree->SetBranchAddress("A2Phase", &A2Phase);
   ResultTree->SetBranchAddress("A3Phase", &A3Phase);

   int EntryCount = ResultTree->GetEntries();
   for()

   TCanvas C("C", "C", 1024, 512);
   C.Divide(2);

   C.cd(1);
   HDensity3.SetStats(0);
   HDensity3.Draw();
   ResultTree->Draw("A3A*sin(A3Phase):A3A*cos(A3Phase)", "", "same");
   TGraph G3;
   G3.SetPoint(0, 0.64956980246, 0.64956980246);
   G3.SetMarkerStyle(30);
   G3.SetMarkerSize(1.5);
   G3.Draw("p");

   C.cd(2);
   HDensity2.SetStats(0);
   HDensity2.Draw();
   ResultTree->Draw("A2A*sin(A2Phase):A2A*cos(A2Phase)", "", "same");
   TGraph G2;
   G2.SetPoint(0, 0, 0.38974188147);
   G2.SetMarkerStyle(30);
   G2.SetMarkerSize(1.5);
   G2.Draw("p");

   C.SaveAs("FitResult2DPlanes.png");
   C.SaveAs("FitResult2DPlanes.C");
   C.SaveAs("FitResult2DPlanes.eps");
   C.SaveAs("FitResult2DPlanes.pdf");
}


