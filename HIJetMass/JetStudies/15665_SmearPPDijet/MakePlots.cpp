#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main();
void ExportPlots(vector<TFile *> Files, vector<string> Labels, string OutputBase);
void Normalize(TH1D &H);

int main()
{
   SetThesisStyle();

   TFile File1("ScaledResult1/PP6Dijet.root");
   TFile File2("ScaledResult2/PP6Dijet.root");
   TFile File3("ScaledResult3/PP6Dijet.root");
   TFile File4("ScaledResult4/PP6Dijet.root");
   TFile File5("ScaledResult5/PP6Dijet.root");
   TFile File6("ScaledResult6/PP6Dijet.root");
   TFile File7("ScaledResult7/PP6Dijet.root");
   TFile File8("ScaledResult8/PP6Dijet.root");
   TFile File9("ScaledResult9/PP6Dijet.root");
   TFile File10("ScaledResult10/PP6Dijet.root");
   TFile File11("ScaledResult11/PP6Dijet.root");
   TFile File12("ScaledResult12/PP6Dijet.root");
   TFile File13("ScaledResult13/PP6Dijet.root");
   TFile File14("ScaledResult14/PP6Dijet.root");
   TFile File15("ScaledResult15/PP6Dijet.root");
   TFile File16("ScaledResult16/PP6Dijet.root");
   TFile File17("ScaledResult17/PP6Dijet.root");
   TFile File18("ScaledResult18/PP6Dijet.root");

   vector<TFile *> MBFiles(5);
   vector<string> MBLabels(5);

   MBFiles[0] = &File1;   MBLabels[0] = "1.00x";
   MBFiles[1] = &File2;   MBLabels[1] = "1.50x";
   MBFiles[2] = &File3;   MBLabels[2] = "2.00x";
   MBFiles[3] = &File4;   MBLabels[3] = "4.00x";
   MBFiles[4] = &File5;   MBLabels[4] = "0.50x";

   ExportPlots(MBFiles, MBLabels, "Plots/MBSpectrum");

   vector<TFile *> SmearFiles(4);
   vector<string> SmearLabels(4);

   SmearFiles[0] = &File1;   SmearLabels[0] = "20%";
   SmearFiles[1] = &File6;   SmearLabels[1] = "10%";
   SmearFiles[2] = &File7;   SmearLabels[2] = "5%";
   SmearFiles[3] = &File8;   SmearLabels[3] = "30%";

   ExportPlots(SmearFiles, SmearLabels, "Plots/Smear");

   vector<TFile *> RhoFiles(4);
   vector<string> RhoLabels(4);

   RhoFiles[0] = &File1;   RhoLabels[0] = "1.00x";
   RhoFiles[1] = &File9;   RhoLabels[1] = "1.20x";
   RhoFiles[2] = &File10;  RhoLabels[2] = "1.50x";
   RhoFiles[3] = &File11;  RhoLabels[3] = "0.80x";

   ExportPlots(RhoFiles, RhoLabels, "Plots/Rho");

   vector<TFile *> GhostFiles(4);
   vector<string> GhostLabels(4);

   GhostFiles[0] = &File1;   GhostLabels[0] = "0.07";
   GhostFiles[1] = &File12;  GhostLabels[1] = "0.10";
   GhostFiles[2] = &File15;  GhostLabels[2] = "0.04";
   GhostFiles[3] = &File16;  GhostLabels[3] = "0.02";

   ExportPlots(GhostFiles, GhostLabels, "Plots/Ghost");

   vector<TFile *> RangeFiles(4);
   vector<string> RangeLabels(4);

   RangeFiles[0] = &File1;   RangeLabels[0] = "0.80";
   RangeFiles[1] = &File13;  RangeLabels[1] = "1.20";
   RangeFiles[2] = &File14;  RangeLabels[2] = "0.60";
   RangeFiles[3] = &File17;  RangeLabels[3] = "1.60";
   // RangeFiles[4] = &File18;  RangeLabels[4] = "2.00";

   ExportPlots(RangeFiles, RangeLabels, "Plots/RangeSpectrum");

   File18.Close();
   File17.Close();
   File16.Close();
   File15.Close();
   File14.Close();
   File13.Close();
   File12.Close();
   File11.Close();
   File10.Close();
   File9.Close();
   File8.Close();
   File7.Close();
   File6.Close();
   File5.Close();
   File4.Close();
   File3.Close();
   File2.Close();
   File1.Close();

   return -1;
}

void ExportPlots(vector<TFile *> Files, vector<string> Labels, string OutputBase)
{
   int Colors[] = {kBlack, kBlue, kGreen - 3, kRed, kYellow + 3};

   vector<TH1D *> H;
   for(int i = 0; i < (int)Files.size(); i++)
      H.push_back((TH1D *)Files[i]->Get("HNewSDMass"));

   TCanvas Canvas;

   TLegend Legend(0.5, 0.8, 0.8, 0.5);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Normalize(*H[i]);
      H[i]->SetLineColor(Colors[i]);
      H[i]->SetLineWidth(2);

      Legend.AddEntry(H[i], Labels[i].c_str(), "l");
   }

   TH2D HWorld("HWorld", ";SD Mass;a.u.", 100, 0, 80, 100, 0, 0.06);
   HWorld.SetStats(0);

   HWorld.Draw();
   Legend.Draw();

   for(int i = 0; i < (int)Files.size(); i++)
      H[i]->Draw("same");

   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C",   OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void Normalize(TH1D &H)
{
   int N = H.GetNbinsX();
   double Left = H.GetBinLowEdge(1);
   double Right = H.GetXaxis()->GetBinUpEdge(N);
   double BinSize = (Right - Left) / N;

   H.Scale(1 / BinSize / H.Integral());
}







