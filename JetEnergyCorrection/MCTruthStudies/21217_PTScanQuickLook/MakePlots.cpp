#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddProfile(PdfFileHelper &PdfFile, TTree *TCalo, TTree *TPF,
   string ToPlot, string Cut, string Title,
   int NBinX, double XMin, double XMax,
   int NBinY, double YMin, double YMax, bool Separate = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileNameCalo   = CL.Get("calo", "MergedCalo.root");
   string FileNamePF     = CL.Get("pf", "MergedPF.root");
   string FileNameOutput = CL.Get("output", "Output.pdf");
   
   PdfFileHelper PdfFile(FileNameOutput);
   PdfFile.AddTextPage("Calo vs PF");

   TFile FCalo(FileNameCalo.c_str());
   TFile FPF(FileNamePF.c_str());

   TTree *TCalo = (TTree *)FCalo.Get("OutputTree");
   TTree *TPF = (TTree *)FPF.Get("OutputTree");

   AddProfile(PdfFile, TCalo, TPF,
      "PUPT-NoPUPT:log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset (GeV)", 25, 2.0, 2.8, 100, -20, 20);
   AddProfile(PdfFile, TCalo, TPF,
      "PUPT-NoPUPT:log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset (GeV)", 20, 2.0, 2.8, 100, -20, 20);
   AddProfile(PdfFile, TCalo, TPF,
      "PUPT-NoPUPT:log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset (GeV)", 15, 2.0, 2.8, 100, -20, 20);
   AddProfile(PdfFile, TCalo, TPF,
      "PUPT-NoPUPT:log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset (GeV)", 15, 2.0, 2.8, 100, -15, 5);
   AddProfile(PdfFile, TCalo, TPF,
      "PUPT*PUEMF-NoPUPT*NoPUEMF:log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset in ECAL (GeV)", 15, 2.0, 2.8, 100, -10, 0, true);
   AddProfile(PdfFile, TCalo, TPF,
      "PUPT*(1-PUEMF)-NoPUPT*(1-NoPUEMF):log(RefPT)/log(10)", "abs(RefEta) < 0.2",
      ";log_{10}(RefPT);Offset in HCAL (GeV)", 15, 2.0, 2.8, 100, -5, 5, true);

   FPF.Close();
   FCalo.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddProfile(PdfFileHelper &PdfFile, TTree *TCalo, TTree *TPF,
   string ToPlot, string Cut, string Title,
   int NBinX, double XMin, double XMax,
   int NBinY, double YMin, double YMax, bool Separate)
{
   TProfile P1("P1", Title.c_str(), NBinX, XMin, XMax);
   TProfile P2("P2", Title.c_str(), NBinX, XMin, XMax);

   P1.SetMarkerColor(kRed);
   P2.SetMarkerColor(kBlack);
   P1.SetMarkerStyle(20);
   P2.SetMarkerStyle(20);
   P1.SetMarkerSize(1.5);
   P2.SetMarkerSize(1.5);

   TCalo->Draw((ToPlot + ">>P1").c_str(), Cut.c_str(), "prof");
   TPF->Draw((ToPlot + ">>P2").c_str(), Cut.c_str(), "prof");

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), NBinX, XMin, XMax, NBinY, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   P1.Draw("same");
   P2.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.92, "#color[2]{Calo} #color[1]{PF}");

   PdfFile.AddCanvas(Canvas);

   if(Separate == true)
   {
      HWorld.Draw("axis");
      P1.Draw("same");
      Latex.DrawLatex(0.10, 0.92, "#color[2]{Calo}");
      PdfFile.AddCanvas(Canvas);
      
      HWorld.Draw("axis");
      P2.Draw("same");
      Latex.DrawLatex(0.10, 0.92, "#color[1]{PF}");
      PdfFile.AddCanvas(Canvas);
   }
}





