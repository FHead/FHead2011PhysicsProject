#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"

int main()
{
   TH1D HX1("HX1", "x", 300, 50, 150);
   TH1D HX2("HX2", "x", 300, 50, 150);
   TH1D HX3("HX3", "x", 300, 50, 150);
   TH1D HX4("HX4", "x", 300, 50, 150);
   TH1D HY1("HY1", "y", 300, -10, 20);
   TH1D HY2("HY2", "y", 300, -10, 20);
   TH1D HY3("HY3", "y", 300, -10, 20);
   TH1D HY4("HY4", "y", 300, -10, 20);

   TFile F1("SmearedSamples.root");
   TTree *Tree = (TTree *)F1.Get("Tree");

   double x, y, w;
   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("y", &y);

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      HX1.Fill(x);
      HY1.Fill(y);
   }

   TFile F2("UniformToyFirstTry.root");
   Tree = (TTree *)F2.Get("Tree");
   
   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("y", &y);
   Tree->SetBranchAddress("W", &w);

   EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      HX2.Fill(x, w);
      HY2.Fill(y, w);
   }

   TFile F3("SmearedSamples100.root");
   Tree = (TTree *)F3.Get("Tree");

   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("y", &y);

   EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      HX3.Fill(x);
      HY3.Fill(y);
   }

   TFile F4("UniformToy100.root");
   Tree = (TTree *)F4.Get("Tree");
   
   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("y", &y);
   Tree->SetBranchAddress("W", &w);

   EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      HX4.Fill(x, w);
      HY4.Fill(y, w);
   }

   HX1.Scale(1 / HX1.Integral());
   HX2.Scale(1 / HX2.Integral());
   HX3.Scale(1 / HX3.Integral());
   HX4.Scale(1 / HX4.Integral());
   HY1.Scale(1 / HY1.Integral());
   HY2.Scale(1 / HY2.Integral());
   HY3.Scale(1 / HY3.Integral());
   HY4.Scale(1 / HY4.Integral());

   HX2.SetLineColor(kRed);
   HY2.SetLineColor(kRed);
   HX4.SetLineColor(kRed);
   HY4.SetLineColor(kRed);

   HX1.SetStats(0);
   HY1.SetStats(0);
   HX3.SetStats(0);
   HY3.SetStats(0);

   TCanvas C;

   HX1.Draw();
   C.SaveAs("x.png");
   C.SaveAs("x.C");
   C.SaveAs("x.eps");
   C.SaveAs("x.pdf");

   HY1.Draw();
   C.SaveAs("y.png");
   C.SaveAs("y.C");
   C.SaveAs("y.eps");
   C.SaveAs("y.pdf");

   HX1.Draw();
   HX2.Draw("same");
   C.SaveAs("tx.png");
   C.SaveAs("tx.C");
   C.SaveAs("tx.eps");
   C.SaveAs("tx.pdf");

   HY1.Draw();
   HY2.Draw("same");
   C.SaveAs("ty.png");
   C.SaveAs("ty.C");
   C.SaveAs("ty.eps");
   C.SaveAs("ty.pdf");

   HX3.Draw();
   HX4.Draw("same");
   C.SaveAs("ttx.png");
   C.SaveAs("ttx.C");
   C.SaveAs("ttx.eps");
   C.SaveAs("ttx.pdf");

   HY3.Draw();
   HY4.Draw("same");
   C.SaveAs("tty.png");
   C.SaveAs("tty.C");
   C.SaveAs("tty.eps");
   C.SaveAs("tty.pdf");

   return 0;
}
