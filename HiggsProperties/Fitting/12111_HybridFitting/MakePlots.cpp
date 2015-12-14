#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"

#include "PlotHelper2.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main()
{
   TFile FA1("OutputFile_PureA1.root");
   TFile FA2("OutputFile_PureA2.root");
   TFile FA3("OutputFile_PureA3.root");

   TTree *TA1 = (TTree *)FA1.Get("ResultTree");
   TTree *TA2 = (TTree *)FA2.Get("ResultTree");
   TTree *TA3 = (TTree *)FA3.Get("ResultTree");

   float A3A1, A2A1, Status, A3A1Error, A2A1Error;
   TA1->SetBranchAddress("A3A1", &A3A1);
   TA1->SetBranchAddress("A3A1Error", &A3A1Error);
   TA1->SetBranchAddress("A2A1", &A2A1);
   TA1->SetBranchAddress("A2A1Error", &A2A1Error);
   TA1->SetBranchAddress("Status", &Status);
   TA2->SetBranchAddress("A3A1", &A3A1);
   TA2->SetBranchAddress("A3A1Error", &A3A1Error);
   TA2->SetBranchAddress("A2A1", &A2A1);
   TA2->SetBranchAddress("A2A1Error", &A2A1Error);
   TA2->SetBranchAddress("Status", &Status);
   TA3->SetBranchAddress("A3A1", &A3A1);
   TA3->SetBranchAddress("A3A1Error", &A3A1Error);
   TA3->SetBranchAddress("A2A1", &A2A1);
   TA3->SetBranchAddress("A2A1Error", &A2A1Error);
   TA3->SetBranchAddress("Status", &Status);

   int Entry1 = TA1->GetEntries();
   int Entry2 = TA2->GetEntries();
   int Entry3 = TA3->GetEntries();

   TH1D HA3A1_A1("HA3A1_A1", "|A3/A1|;atan(|A3/(5 A1)|)", 50, 0, PI / 2);
   TH1D HA3A1_A2("HA3A1_A2", "|A3/A1|;atan(|A3/(5 A1)|)", 50, 0, PI / 2);
   TH1D HA3A1_A3("HA3A1_A3", "|A3/A1|;atan(|A3/(5 A1)|)", 50, 0, PI / 2);
   TH1D HA2A1_A1("HA2A1_A1", "|A2/A1|;atan(|A2/(3.125 A1)|)", 50, 0, PI / 2);
   TH1D HA2A1_A2("HA2A1_A2", "|A2/A1|;atan(|A2/(3.125 A1)|)", 50, 0, PI / 2);
   TH1D HA2A1_A3("HA2A1_A3", "|A2/A1|;atan(|A2/(3.125 A1)|)", 50, 0, PI / 2);
   TH1D HA3A2_A1("HA3A2_A1", "|A3/A2|;atan(|A3/A2/1.6|)", 50, 0, PI / 2);
   TH1D HA3A2_A2("HA3A2_A2", "|A3/A2|;atan(|A3/A2/1.6|)", 50, 0, PI / 2);
   TH1D HA3A2_A3("HA3A2_A3", "|A3/A2|;atan(|A3/A2/1.6|)", 50, 0, PI / 2);
   TH1D HA1A_A1("HA1A_A1", "|A1s/As|;(|A1s|/|As|)", 50, 0, 1);
   TH1D HA1A_A2("HA1A_A2", "|A1s/As|;(|A1s|/|As|)", 50, 0, 1);
   TH1D HA1A_A3("HA1A_A3", "|A1s/As|;(|A1s|/|As|)", 50, 0, 1);
   TH1D HA2A_A1("HA2A_A1", "|A2s/As|;(|A2s|/|As|)", 50, 0, 1);
   TH1D HA2A_A2("HA2A_A2", "|A2s/As|;(|A2s|/|As|)", 50, 0, 1);
   TH1D HA2A_A3("HA2A_A3", "|A2s/As|;(|A2s|/|As|)", 50, 0, 1);
   TH1D HA3A_A1("HA3A_A1", "|A3s/As|;(|A3s|/|As|)", 50, 0, 1);
   TH1D HA3A_A2("HA3A_A2", "|A3s/As|;(|A3s|/|As|)", 50, 0, 1);
   TH1D HA3A_A3("HA3A_A3", "|A3s/As|;(|A3s|/|As|)", 50, 0, 1);

   HA3A1_A1.SetStats(0);
   HA3A1_A2.SetStats(0);
   HA3A1_A3.SetStats(0);
   HA2A1_A1.SetStats(0);
   HA2A1_A2.SetStats(0);
   HA2A1_A3.SetStats(0);
   HA3A2_A1.SetStats(0);
   HA3A2_A2.SetStats(0);
   HA3A2_A3.SetStats(0);
   HA1A_A1.SetStats(0);
   HA1A_A2.SetStats(0);
   HA1A_A3.SetStats(0);
   HA2A_A1.SetStats(0);
   HA2A_A2.SetStats(0);
   HA2A_A3.SetStats(0);
   HA3A_A1.SetStats(0);
   HA3A_A2.SetStats(0);
   HA3A_A3.SetStats(0);
   HA3A1_A1.SetLineColor(kBlack);
   HA3A1_A2.SetLineColor(kRed);
   HA3A1_A3.SetLineColor(kBlue);
   HA2A1_A1.SetLineColor(kBlack);
   HA2A1_A2.SetLineColor(kRed);
   HA2A1_A3.SetLineColor(kBlue);
   HA3A2_A1.SetLineColor(kBlack);
   HA3A2_A2.SetLineColor(kRed);
   HA3A2_A3.SetLineColor(kBlue);
   HA1A_A1.SetLineColor(kBlack);
   HA1A_A2.SetLineColor(kRed);
   HA1A_A3.SetLineColor(kBlue);
   HA2A_A1.SetLineColor(kBlack);
   HA2A_A2.SetLineColor(kRed);
   HA2A_A3.SetLineColor(kBlue);
   HA3A_A1.SetLineColor(kBlack);
   HA3A_A2.SetLineColor(kRed);
   HA3A_A3.SetLineColor(kBlue);
   HA3A1_A1.SetLineWidth(2);
   HA3A1_A2.SetLineWidth(2);
   HA3A1_A3.SetLineWidth(2);
   HA2A1_A1.SetLineWidth(2);
   HA2A1_A2.SetLineWidth(2);
   HA2A1_A3.SetLineWidth(2);
   HA3A2_A1.SetLineWidth(2);
   HA3A2_A2.SetLineWidth(2);
   HA3A2_A3.SetLineWidth(2);
   HA1A_A1.SetLineWidth(2);
   HA1A_A2.SetLineWidth(2);
   HA1A_A3.SetLineWidth(2);
   HA2A_A1.SetLineWidth(2);
   HA2A_A2.SetLineWidth(2);
   HA2A_A3.SetLineWidth(2);
   HA3A_A1.SetLineWidth(2);
   HA3A_A2.SetLineWidth(2);
   HA3A_A3.SetLineWidth(2);

   for(int iEntry = 0; iEntry < Entry1; iEntry++)
   {
      TA1->GetEntry(iEntry);
      if(Status == 3)
      {
         HA3A1_A1.Fill(atan(fabs(A3A1/5)));
         HA2A1_A1.Fill(atan(fabs(A2A1/3.125)));
         HA3A2_A1.Fill(atan(fabs(A3A1/A2A1/1.6)));

         double A = sqrt(A3A1 * A3A1 / 25 + A2A1 * A2A1 / 3.125 / 3.125 + 1);
         HA1A_A1.Fill((fabs(1/A)));
         HA2A_A1.Fill((fabs(A2A1/3.125/A)));
         HA3A_A1.Fill((fabs(A3A1/5/A)));
      }
   }
   for(int iEntry = 0; iEntry < Entry2; iEntry++)
   {
      TA2->GetEntry(iEntry);
      if(Status == 3)
      {
         HA3A1_A2.Fill(atan(fabs(A3A1/5)));
         HA2A1_A2.Fill(atan(fabs(A2A1/3.125)));
         HA3A2_A2.Fill(atan(fabs(A3A1/A2A1/1.6)));

         double A = sqrt(A3A1 * A3A1 / 25 + A2A1 * A2A1 / 3.125 / 3.125 + 1);
         HA1A_A2.Fill((fabs(1/A)));
         HA2A_A2.Fill((fabs(A2A1/3.125/A)));
         HA3A_A2.Fill((fabs(A3A1/5/A)));
      }
   }
   for(int iEntry = 0; iEntry < Entry3; iEntry++)
   {
      TA3->GetEntry(iEntry);
      if(Status == 3)
      {
         HA3A1_A3.Fill(atan(fabs(A3A1/5)));
         HA2A1_A3.Fill(atan(fabs(A2A1/3.125)));
         HA3A2_A3.Fill(atan(fabs(A3A1/A2A1/1.6)));

         double A = sqrt(A3A1 * A3A1 / 25 + A2A1 * A2A1 / 3.125 / 3.125 + 1);
         HA1A_A3.Fill((fabs(1/A)));
         HA2A_A3.Fill((fabs(A2A1/3.125/A)));
         HA3A_A3.Fill((fabs(A3A1/5/A)));
      }
   }

   PsFileHelper PsFile("Plots.ps");
   PsFile.AddTextPage("Fit result!");

   vector<string> Explanations(10);
   Explanations[0] = "Generate pure A1, pure A2 and pure A3 samples from Madgraph (50k each).";
   Explanations[1] = "Smear with lepton response and efficiencies to get \"RECO\" quantities.";
   Explanations[2] = "Attach all relevant branches and do fits.";
   Explanations[3] = "";
   Explanations[4] = "Compare A2/A1, A3/A1, A3/A2 from different fits.";
   Explanations[5] = "";
   Explanations[6] = "We see interesting feature with pure samples.  Both A1 and A3 are zero";
   Explanations[7] = "in pure A2 sample, so the A3/A1 ratio is a random number.";
   Explanations[8] = "Depending on absolute size of the terms result might slant left or right.";
   Explanations[9] = "With |Ax| / sqrt(sum |Ax|^2) it's much better.";
   PsFile.AddTextPage(Explanations);

   TLegend Legend(0.3, 0.6, 0.6, 0.8);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HA3A1_A1, "Pure A1", "l");
   Legend.AddEntry(&HA3A1_A2, "Pure A2", "l");
   Legend.AddEntry(&HA3A1_A3, "Pure A3", "l");

   TCanvas C;
   HA3A1_A3.Draw();
   HA3A1_A2.Draw("same");
   HA3A1_A1.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);
   
   HA2A1_A2.Draw();
   HA2A1_A3.Draw("same");
   HA2A1_A1.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);

   HA3A2_A3.Draw();
   HA3A2_A2.Draw("same");
   HA3A2_A1.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);
   
   HA1A_A1.Draw();
   HA1A_A2.Draw("same");
   HA1A_A3.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);
   
   HA2A_A2.Draw();
   HA2A_A3.Draw("same");
   HA2A_A1.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);

   HA3A_A3.Draw();
   HA3A_A2.Draw("same");
   HA3A_A1.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   FA3.Close();
   FA2.Close();
   FA1.Close();
}







