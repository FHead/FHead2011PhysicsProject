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

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string BaseName    = CL.Get("Base");
   string VariantName = CL.Get("Variant");
   string OutputName  = CL.Get("Output");

   TFile FBase(BaseName.c_str());
   TFile FVariant(VariantName.c_str());

   TTree *TBase = (TTree *)FBase.Get("tgan");
   TTree *TVariant = (TTree *)FVariant.Get("tgan");

   PdfFileHelper PdfFile(OutputName);
   PdfFile.AddTextPage("GAN output comparison");

   Add1D(PdfFile, TBase, TVariant, "px", "", ";p_{x};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "py", "", ";p_{y};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pz", "", ";p_{z};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "theta", "", ";#theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "phi", "", ";#phi;", 100, -M_PI, M_PI);
   Add1D(PdfFile, TBase, TVariant, "pmag", "", ";p;", 100, 0, 50);
   Add1D(PdfFile, TBase, TVariant, "nParticle", "", ";Mult.;", 100, 0, 100);
   Add1D(PdfFile, TBase, TVariant, "Sum$(pmag>1)", "", ";Mult. (p > 1);", 70, 0, 70);
   Add1D(PdfFile, TBase, TVariant, "charge", "", ";charge;", 3, -1, 2);
   Add1D(PdfFile, TBase, TVariant, "charge", "pmag > 1", "p > 1;charge;", 3, -1, 2);
   Add1D(PdfFile, TBase, TVariant, "px[0]", "", "first particle;p_{x};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "py[0]", "", "first particle;p_{y};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pz[0]", "", "first particle;p_{z};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pmag[0]", "", "first particle;p;", 100, 0, 50);

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


