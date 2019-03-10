#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input", "All.root");
   
   TFile File(InputFileName.c_str());

   TH1D *HN = (TH1D *)File.Get("HN");
   TH2D *HEtaPT = (TH2D *)File.Get("HEtaPT");

   HEtaPT->SetStats(0);
   HEtaPT->GetXaxis()->SetTitle("#eta");
   HEtaPT->GetYaxis()->SetTitle("p_{T}");
   HEtaPT->GetZaxis()->SetTitle("Number of jets per 1M events");

   HEtaPT->Scale(1000000 / HN->Integral());

   TCanvas Canvas;
   Canvas.SetLogy();

   HEtaPT->Draw("colz");

   Canvas.SaveAs("Meow1.pdf");

   HEtaPT->GetXaxis()->SetRangeUser(-3.5, -1.0);

   Canvas.SaveAs("Meow2.pdf");
   
   return 0;
}



