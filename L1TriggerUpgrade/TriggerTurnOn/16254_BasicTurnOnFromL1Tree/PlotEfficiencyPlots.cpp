#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Tag, string OutputBase, bool DoFit);

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " FileName Tag" << endl;
      return -1;
   }

   string Tag = "WENu200";
   string FileName = "Result/WENu200.root";

   FileName = argv[1];
   Tag = argv[2];

   SetThesisStyle();

   PdfFileHelper PdfFile("EfficiencyPlots" + Tag + ".pdf");
   PdfFile.AddTextPage(Tag);

   TFile File(FileName.c_str());

   AddPlot(PdfFile, File, "l1upgrade_EGamma/hTkIsoeggen", "l1upgrade_EGamma/gelectrons",
      "Tk Iso EG", "Plot/" + Tag + "IsoEG", true);
   AddPlot(PdfFile, File, "l1upgrade_EGamma/htkeggen", "l1upgrade_EGamma/gelectrons",
      "Tk EG", "Plot/" + Tag + "EG", true);
   
   AddPlot(PdfFile, File, "l1upgrade_EGamma/hTkIsoeggeneta", "l1upgrade_EGamma/hgeneta",
      "Tk Iso EG", "Plot/" + Tag + "IsoEGEta", false);
   AddPlot(PdfFile, File, "l1upgrade_EGamma/htkeggeneta", "l1upgrade_EGamma/hgeneta",
      "Tk EG", "Plot/" + Tag + "EGEta", false);
   
   // AddPlot(PdfFile, File, "l1upgrade_EGamma/htkemgen", "l1upgrade_EGamma/gelectrons", "Tk EM");

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Tag, string OutputBase, bool DoFit)
{
   TH1D *H1 = (TH1D *)F.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   H1->SetStats(0);
   H2->SetStats(0);

   H1->GetXaxis()->SetTitle("Gen particle PT");
   H2->GetXaxis()->SetTitle("Gen particle PT");

   H2->SetLineColor(kRed);
   H2->SetMarkerColor(kRed);

   PdfFile.AddTextPage(Tag);

   TCanvas C;

   H2->Draw();
   H1->Draw("same");

   TLegend Legend(0.2, 0.6, 0.5, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(H1, "Matched", "pl");
   Legend.AddEntry(H2, "All", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   TGraphAsymmErrors R;
   R.Divide(H1, H2);

   TF1 Fit("Fit", "[0]/2+[0]/2*tanh([1]*(x-[2]))");
   Fit.SetParameters(0.5, 1, 10);
   Fit.SetParName(0, "Plateau");
   Fit.SetParName(1, "Steepness");
   Fit.SetParName(2, "Mid-point");

   if(DoFit == true)
      R.Fit(&Fit);

   gStyle->SetOptFit(1);

   TH1D *H = (TH1D *)H1->Clone();
   H->SetMinimum(0);
   H->SetMaximum(1.2);

   H->Draw("axis");

   TGraph G;
   G.SetPoint(0, -100, 1);
   G.SetPoint(1, 100, 1);
   G.Draw("l");

   R.Draw("p");

   PdfFile.AddCanvas(C);

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   delete H;
}




