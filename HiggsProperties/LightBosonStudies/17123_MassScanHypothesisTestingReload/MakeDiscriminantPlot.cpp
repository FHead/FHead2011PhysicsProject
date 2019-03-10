#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, string L1, string L2, string M, double SEM, double SEE, double BEM, double BEE);
vector<double> ReadTree(TTree *T, string L1, string L2, double SEM, double SEE, double BEM, double BEE);
double GetMean(vector<double> &V);
double GetRMS(vector<double> &V);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Discriminants.pdf");
   PdfFile.AddTextPage("Some discriminants");

   AddPlot(PdfFile, "A1UU", "A1UZ", "18p94", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UZ", "18p94", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A1UZ", "19p0", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UZ", "19p0", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A1UZ", "19p3", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UZ", "19p3", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "18p4", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "18p8", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "18p9", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "18p92", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "18p94", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "19p0", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A3UU", "19p3", 5, -1, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UU", "18p9", 10, 10, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UU", "18p92", 10, 10, -1, -1);
   AddPlot(PdfFile, "A1UU", "A2UU", "18p94", 10, 10, -1, -1);
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, string L1, string L2, string M, double SEM, double SEE, double BEM, double BEE)
{
   TFile F1(("CombinedResult/Likelihood_" + L1 + "_P_" + M + ".root").c_str());
   TFile F2(("CombinedResult/Likelihood_" + L2 + "_P_" + M + ".root").c_str());

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   vector<double> V1 = ReadTree(T1, L1, L2, SEM, SEE, BEM, BEE);
   vector<double> V2 = ReadTree(T2, L1, L2, SEM, SEE, BEM, BEE);

   double M1 = GetMean(V1);
   double S1 = GetRMS(V1);
   double M2 = GetMean(V2);
   double S2 = GetRMS(V2);

   cout << M1 << " " << M2 << " " << S1 << " " << S2 << endl;

   double ML = min(M1, M2);
   double MR = max(M1, M2);

   double Min = ML - max(S1, S2) * 7;
   double Max = MR + max(S1, S2) * 7;

   TH1D H1("H1", ";;", 250, Min, Max);
   TH1D H2("H2", ";;", 250, Min, Max);
   TH1D H1Zoom("H1Zoom", ";;", 250, (4 * ML + 3 * MR) / (4 + 3), (3 * ML + 4 * MR) / (3 + 4));
   TH1D H2Zoom("H2Zoom", ";;", 250, (4 * ML + 3 * MR) / (4 + 3), (3 * ML + 4 * MR) / (3 + 4));

   H1.Sumw2();
   H2.Sumw2();
   H1Zoom.Sumw2();
   H2Zoom.Sumw2();

   for(int i = 0; i < (int)V1.size(); i++)
      H1.Fill(V1[i]);
   for(int i = 0; i < (int)V2.size(); i++)
      H2.Fill(V2[i]);
   for(int i = 0; i < (int)V1.size(); i++)
      H1Zoom.Fill(V1[i]);
   for(int i = 0; i < (int)V2.size(); i++)
      H2Zoom.Fill(V2[i]);

   H1Zoom.Scale(1 / H1.Integral());
   H2Zoom.Scale(1 / H2.Integral());
   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H1.SetLineWidth(2);
   H1.SetMarkerStyle(20);
   H1.SetLineColor(kRed);
   H1.SetMarkerColor(kRed);
   H1Zoom.SetLineWidth(2);
   H1Zoom.SetMarkerStyle(20);
   H1Zoom.SetLineColor(kRed);
   H1Zoom.SetMarkerColor(kRed);

   H2.SetLineWidth(2);
   H2.SetMarkerStyle(20);
   H2Zoom.SetLineWidth(2);
   H2Zoom.SetMarkerStyle(20);

   H1.SetStats(0);
   H1Zoom.SetStats(0);

   H1.SetTitle(Form("%s - %s, (%.0f %.0f %.0f %.0f), %s", L1.c_str(), L2.c_str(), SEM, SEE, BEM, BEE, M.c_str()));
   H1Zoom.SetTitle(Form("%s - %s, (%.0f %.0f %.0f %.0f), %s", L1.c_str(), L2.c_str(), SEM, SEE, BEM, BEE, M.c_str()));

   TCanvas C;

   H1.Draw();
   H2.Draw("same");
   H1.Draw("hist same");
   H2.Draw("hist same");

   C.SetLogy();

   PdfFile.AddCanvas(C);

   H1Zoom.Draw();
   H2Zoom.Draw("same");
   H1Zoom.Draw("hist same");
   H2Zoom.Draw("hist same");

   PdfFile.AddCanvas(C);

   F2.Close();
   F1.Close();
}

vector<double> ReadTree(TTree *T, string L1, string L2, double SEM, double SEE, double BEM, double BEE)
{
   if(T == NULL)
      return vector<double>();

   vector<double> Result;

   double TreeL1;
   double TreeL2;
   double TreeSEM;
   double TreeSEE;
   double TreeBEM;
   double TreeBEE;

   T->SetBranchAddress(("L" + L1).c_str(), &TreeL1);
   T->SetBranchAddress(("L" + L2).c_str(), &TreeL2);
   T->SetBranchAddress("ExpectedSEM", &TreeSEM);
   T->SetBranchAddress("ExpectedSEE", &TreeSEE);
   T->SetBranchAddress("ExpectedBEM", &TreeBEM);
   T->SetBranchAddress("ExpectedBEE", &TreeBEE);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(SEM != TreeSEM)   continue;
      if(SEE != TreeSEE)   continue;
      if(BEM != TreeBEM)   continue;
      if(BEE != TreeBEE)   continue;

      if(TreeL1 != TreeL1) continue;
      if(TreeL2 != TreeL2) continue;
      
      Result.push_back(TreeL1 - TreeL2);
   }

   return Result;
}

double GetMean(vector<double> &V)
{
   double X = 0;
   double N = 0;

   for(int i = 0; i < (int)V.size(); i++)
   {
      X = X + V[i];
      N = N + 1;
   }

   return X / N;
}

double GetRMS(vector<double> &V)
{
   double X2 = 0;
   double X = 0;
   double N = 0;

   for(int i = 0; i < (int)V.size(); i++)
   {
      X2 = X2 + V[i] * V[i];
      X = X + V[i];
      N = N + 1;
   }

   return sqrt((X2 - X * X / N) / N);
}


