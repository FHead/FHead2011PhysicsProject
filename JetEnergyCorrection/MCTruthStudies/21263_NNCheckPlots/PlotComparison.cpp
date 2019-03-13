#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TProfile.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "PlotHelper4.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *TNew, TTree *TOld, string ToPlot, string Selection,
   string Title, int Bin, double Min, double Max);

int main()
{
   SetThesisStyle();

   TFile FOld("Old.root");
   TFile FNew("New.root");

   TTree *TOld = (TTree *)FOld.Get("OutputTree");
   TTree *TNew = (TTree *)FNew.Get("OutputTree");

   PdfFileHelper PdfFile("NNValidation.pdf");
   PdfFile.AddTextPage("NN Validation");

   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 30 && RefPT < 50",
      "P_{T}^{Gen} = 30-50;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 30 && RefPT < 50 && Rho < 20",
      "P_{T}^{Gen} = 30-50, Rho < 20;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 30 && RefPT < 50 && Rho > 20 && Rho < 40",
      "P_{T}^{Gen} = 30-50, Rho = 20-40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 30 && RefPT < 50 && Rho < 40",
      "P_{T}^{Gen} = 30-50, Rho > 40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 50 && RefPT < 100",
      "P_{T}^{Gen} = 50-100;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 50 && RefPT < 100 && Rho < 20",
      "P_{T}^{Gen} = 50-100, Rho < 20;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 50 && RefPT < 100 && Rho > 20 && Rho < 40",
      "P_{T}^{Gen} = 50-100, Rho = 20-40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 50 && RefPT < 100 && Rho < 40",
      "P_{T}^{Gen} = 50-100, Rho > 40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 200 && RefPT < 300",
      "P_{T}^{Gen} = 200-300;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 200 && RefPT < 300 && Rho < 20",
      "P_{T}^{Gen} = 200-300, Rho < 20;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 200 && RefPT < 300 && Rho > 20 && Rho < 40",
      "P_{T}^{Gen} = 200-300, Rho = 20-40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 200 && RefPT < 300 && Rho < 40",
      "P_{T}^{Gen} = 200-300, Rho > 40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 400 && RefPT < 600",
      "P_{T}^{Gen} = 400-600;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 400 && RefPT < 600 && Rho < 20",
      "P_{T}^{Gen} = 400-600, Rho < 20;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 400 && RefPT < 600 && Rho > 20 && Rho < 40",
      "P_{T}^{Gen} = 400-600, Rho = 20-40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 400 && RefPT < 600 && Rho < 40",
      "P_{T}^{Gen} = 400-600, Rho > 40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 800 && RefPT < 1200",
      "P_{T}^{Gen} = 800-1200;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 800 && RefPT < 1200 && Rho < 20",
      "P_{T}^{Gen} = 800-1200, Rho < 20;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 800 && RefPT < 1200 && Rho > 20 && Rho < 40",
      "P_{T}^{Gen} = 800-1200, Rho = 20-40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:RefEta", "RefPT > 800 && RefPT < 1200 && Rho < 40",
      "P_{T}^{Gen} = 800-1200, Rho > 40;#eta;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 100, -5.2, 5.2);
   
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:Rho", "RefPT > 30 && RefPT < 50 && abs(RefEta) < 1.5",
      "P_{T}^{Gen} = 30-50, |#eta| < 1.5;#rho;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 70, 0, 70);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:Rho", "RefPT > 50 && RefPT < 100 && abs(RefEta) < 1.5",
      "P_{T}^{Gen} = 50-100, |#eta| < 1.5;#rho;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 70, 0, 70);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:Rho", "RefPT > 200 && RefPT < 300 && abs(RefEta) < 1.5",
      "P_{T}^{Gen} = 200-300, |#eta| < 1.5;#rho;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 70, 0, 70);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:Rho", "RefPT > 400 && RefPT < 600 && abs(RefEta) < 1.5",
      "P_{T}^{Gen} = 400-600, |#eta| < 1.5;#rho;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 70, 0, 70);
   AddPlot(PdfFile, TNew, TOld, "PUPT-NoPUPT:Rho", "RefPT > 800 && RefPT < 1200 && abs(RefEta) < 1.5",
      "P_{T}^{Gen} = 800-1200, |#eta| < 1.5;#rho;<P_{T}^{PU} - P_{T}^{NoPU}> (GeV)", 70, 0, 70);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FNew.Close();
   FOld.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *TNew, TTree *TOld, string ToPlot, string Selection,
   string Title, int Bin, double Min, double Max)
{
   TProfile POld("POld", Title.c_str(), Bin, Min, Max);
   TProfile PNew("PNew", Title.c_str(), Bin, Min, Max);

   POld.SetStats(0);

   POld.SetMarkerStyle(20);
   POld.SetMarkerColor(kBlack);
   POld.SetLineColor(kBlack);
   PNew.SetMarkerStyle(20);
   PNew.SetMarkerColor(kRed);
   PNew.SetLineColor(kRed);

   TOld->Draw((ToPlot + ">>POld").c_str(), Selection.c_str(), "prof");
   TNew->Draw((ToPlot + ">>PNew").c_str(), Selection.c_str(), "prof");

   TCanvas Canvas;

   POld.Draw();
   PNew.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.91, "#color[1]{Old} #color[2]{New}");

   PdfFile.AddCanvas(Canvas);

   POld.Add(&PNew, -1);

   POld.GetYaxis()->SetTitle("Old - New (GeV)");
   POld.Draw();

   PdfFile.AddCanvas(Canvas);
}





