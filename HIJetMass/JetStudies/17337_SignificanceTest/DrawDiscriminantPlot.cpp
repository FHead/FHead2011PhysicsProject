#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TArrow.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
double PValue(vector<double> Value, double Target);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   double Observed = 0.001;

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Observed" << endl;
      return -1;
   }

   TFile File("Result.root");

   Observed = atof(argv[1]);

   TH1D HD("HD", ";KS Discriminant", 100, 0, 0.14);
   TH1D HS("HS", ";KS Discriminant", 100, 0, 0.14);

   HD.SetStats(0);
   HS.SetStats(0);

   HD.SetMarkerColor(kRed);
   HS.SetMarkerColor(kBlue);

   vector<double> VD, VS;

   TTree *Tree = (TTree *)File.Get("Tree");

   double D, S;
   Tree->SetBranchAddress("D", &D);
   Tree->SetBranchAddress("S", &S);

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);
      HD.Fill(D);
      HS.Fill(S);
      VD.push_back(D);
      VS.push_back(S);
   }

   HD.Scale(1 / HD.Integral());
   HS.Scale(1 / HS.Integral());

   TCanvas Canvas;

   HD.Draw();
   HS.Draw("same");

   TArrow Arrow(Observed, HD.GetMaximum() * 0.15, Observed, 0, 0.02, "-|>");
   Arrow.SetLineWidth(2);
   Arrow.SetFillColor(kBlack);
   Arrow.Draw();

   TLegend Legend(0.45, 0.85, 0.80, 0.60);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HD, "PbPb = truth", "p");
   Legend.AddEntry(&HS, "Smeared pp = truth", "p");
   Legend.AddEntry(&Arrow, "Observed", "l");
   Legend.AddEntry("", Form("p-value (PbPb) = %.3f", PValue(VD, Observed)), "");
   Legend.AddEntry("", Form("p-value (pp) = %.3f", PValue(VS, Observed)), "");
   Legend.Draw();

   Canvas.SaveAs("KSTest.pdf");

   File.Close();

   return 0;
}

double PValue(vector<double> Value, double Target)
{
   sort(Value.begin(), Value.end());

   auto iter = lower_bound(Value.begin(), Value.end(), Target);
   int Distance = iter - Value.begin();

   return 1 - double(Distance) / Value.size();
}


