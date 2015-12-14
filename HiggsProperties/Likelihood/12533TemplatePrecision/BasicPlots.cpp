#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "PlotHelper2.h"

int main()
{
   TCanvas C;

   TFile File("HZZEventFitFormat_qqZZGenerated.tmp.root");
   gROOT->Macro("SetAlias.C");
   TTree *Tree = (TTree *)File.Get("Tree");

   PsFileHelper PsFile("ComparisonPlots.ps");
   PsFile.AddTextPage("Plots!");

   Tree->Draw("T", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("G", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("A", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G:zzmass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G:z1mass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G:z2mass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G:hpt", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G:hy", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-G)/G-0.1*z2mass", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A", "C");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:zzmass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:z1mass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:z2mass", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:z2mass", "C && (T-A)/A < 4", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:hpt", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A:hy", "C", "colz");
   PsFile.AddCanvas(C);
   Tree->Draw("(T-A)/A-0.05*z2mass", "C");
   PsFile.AddCanvas(C);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}


