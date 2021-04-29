#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void Add1D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int N, double Min, double Max);
void Add2D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string BaseName    = CL.Get("Base");
   string VariantName = CL.Get("Variant");
   string OutputName  = CL.Get("Output");

   TFile FBase(BaseName.c_str());
   TFile FVariant(VariantName.c_str());

   TTree *TBase = (TTree *)FBase.Get("UnfoldingTree");
   TTree *TVariant = (TTree *)FVariant.Get("UnfoldingTree");

   PdfFileHelper PdfFile(OutputName);
   PdfFile.AddTextPage("GAN output comparison");

   PdfFile.AddTextPage({"Input files", BaseName, VariantName});

   Add1D(PdfFile, TBase, TVariant, "GanJetE", "", ";Jet E;", 100, 0, 80);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta", "", ";Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetPhi", "", ";Jet #phi;", 100, -M_PI, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta", "GanJetE > 10", "Jet E > 10;Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta", "GanJetE > 20", "Jet E > 20;Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta", "GanJetE > 30", "Jet E > 30;Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta", "GanJetE > 40", "Jet E > 40;Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetE[0]", "", ";Leading Jet E;", 100, 0, 80);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta[0]", "", ";Leading Jet #theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetE[1]", "", ";Subleading Jet E;", 100, 0, 80);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta[1]", "", ";Subleading Jet #theta;", 100, 0, M_PI);
   Add2D(PdfFile, TBase, TVariant, "GanJetE[0]:GanJetE[1]", "",
      ";Leading Jet E;Subleading Jet E", 100, 0, 80, 100, 0, 80);
   Add2D(PdfFile, TBase, TVariant, "GanJetTheta[0]:GanJetTheta[1]", "",
      ";Leading Jet #theta;Subleading Jet #theta", 100, 0, M_PI, 100, 0, M_PI);
   Add2D(PdfFile, TBase, TVariant, "GanJetPhi[0]:GanJetPhi[1]", "",
      ";Leading Jet #phi;Subleading Jet #phi", 100, -M_PI, M_PI, 100, -M_PI, M_PI);
   Add1D(PdfFile, TBase, TVariant, "GanJetE[2]", "", ";3rd leading Jet E;", 100, 0, 80);
   Add1D(PdfFile, TBase, TVariant, "GanJetTheta[2]", "", ";3rd leading Jet #theta;", 100, 0, M_PI);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FVariant.Close();
   FBase.Close();

   return 0;
}

void Add1D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int N, double Min, double Max)
{
   static int index = 0;
   index = index + 1;

   static vector<int> Colors;
   if(Colors.size() == 0)
      Colors = GetPrimaryColors();

   TH1D H1(Form("H%d_1", index), Title.c_str(), N, Min, Max);
   TH1D H2(Form("H%d_2", index), Title.c_str(), N, Min, Max);

   T1->Draw(Form("%s>>H%d_1", ToPlot.c_str(), index), Selection.c_str());
   T2->Draw(Form("%s>>H%d_2", ToPlot.c_str(), index), Selection.c_str());

   H1.SetLineColor(Colors[1]);
   H1.SetMarkerStyle(20);
   H1.SetMarkerColor(Colors[1]);

   H2.SetLineColor(Colors[0]);
   H2.SetMarkerStyle(20);
   H2.SetMarkerColor(Colors[0]);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H1.SetStats(0);

   TCanvas Canvas;

   H1.Draw();
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Reference} #color[%d]{Meow}", Colors[1], Colors[0]));

   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   H1.SetMinimum(0);
   H1.Draw();
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Reference} #color[%d]{Meow}", Colors[1], Colors[0]));

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
}

void Add2D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int NX, double MinX, double MaxX, int NY, double MinY, double MaxY)
{
   static int index = 0;
   index = index + 1;

   TH2D H1(Form("H2D%d_1", index), Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);
   TH2D H2(Form("H2D%d_2", index), Title.c_str(), NX, MinX, MaxX, NY, MinY, MaxY);

   T1->Draw(Form("%s>>H2D%d_1", ToPlot.c_str(), index), Selection.c_str());
   T2->Draw(Form("%s>>H2D%d_2", ToPlot.c_str(), index), Selection.c_str());

   H1.SetStats(0);
   H2.SetStats(0);

   H1.GetXaxis()->SetTickLength(0.025);
   H1.GetYaxis()->SetTickLength(0.050);
   H2.GetXaxis()->SetTickLength(0.025);
   H2.GetYaxis()->SetTickLength(0.050);

   H1.GetXaxis()->SetLabelSize(0.05);
   H1.GetYaxis()->SetLabelSize(0.05);
   H2.GetXaxis()->SetLabelSize(0.05);
   H2.GetYaxis()->SetLabelSize(0.05);
   H1.GetXaxis()->SetTitleSize(0.05);
   H1.GetYaxis()->SetTitleSize(0.05);
   H2.GetXaxis()->SetTitleSize(0.05);
   H2.GetYaxis()->SetTitleSize(0.05);
   
   H1.GetXaxis()->SetLabelOffset(-0.01);
   H2.GetXaxis()->SetLabelOffset(-0.01);
   H1.GetXaxis()->SetTitleOffset(0.7);
   H2.GetXaxis()->SetTitleOffset(0.7);
   H1.GetYaxis()->SetTitleOffset(0.9);
   H2.GetYaxis()->SetTitleOffset(0.9);

   TCanvas Canvas;

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetNDC();
   
   Canvas.Divide(2, 1);

   Canvas.cd(1);
   H1.Draw("colz");
   Latex.DrawLatex(0.10, 0.92, "Reference");
   
   Canvas.cd(2);
   H2.Draw("colz");
   Latex.DrawLatex(0.10, 0.92, "Meow");

   PdfFile.AddCanvas(Canvas);
}


