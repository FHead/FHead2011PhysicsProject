#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void ResolutionPlot(PdfFileHelper &PdfFile, TTree *T, string Selection, string Title);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("MergedPlots.pdf");
   PdfFile.AddTextPage("Old EG vs Tyler EG");

   TFile File("Merged.root");
   TTree *T = (TTree *)File.Get("T");
   
   PdfFile.AddTextPage("Sanity plots for matching");
   PdfFile.AddPlot2D(T, "GenEtaOld:GenEtaNew", "", "colz",
      "Gen eta in old tree vs. gen eta in new tree;GenEtaNew;GenEtaOld", 100, -2.5, 2.5, 100, -2.5, 2.5);
   PdfFile.AddPlot2D(T, "GenPhiOld:GenPhiNew", "", "colz",
      "Gen Phi in old tree vs. gen Phi in new tree;GenPhiNew;GenPhiOld", 100, -3.2, 3.2, 100, -3.2, 3.2);
   PdfFile.AddPlot2D(T, "GenPTOld:GenPTNew", "", "colz",
      "Gen PT in old tree vs. gen PT in new tree;GenPTNew;GenPTOld", 100, 0, 100, 100, 0, 100);

   PdfFile.AddTextPage("Hit & miss summary");
   PdfFile.AddPlot2D(T, "L1PTOld>0:L1PTNew>0", "GenENew > 0", "colz text00",
      ";has L1 object near by (new)?;has L1 object near by (old)?", 2, 0, 2, 2, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld>0:L1PTNew>0", "GenENew > 0 && abs(GenEtaNew) < 1.5", "colz text00",
      "Barrel;has L1 object near by (new)?;has L1 object near by (old)?", 2, 0, 2, 2, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld>0:L1PTNew>0", "GenENew > 0 && abs(GenEtaNew) > 1.5", "colz text00",
      "Endcap;has L1 object near by (new)?;has L1 object near by (old)?", 2, 0, 2, 2, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld>0:L1PTNew>0", "GenENew > 0 && abs(GenEtaNew) < 1.5 && GenPTNew > 25", "colz text00",
      "GenPT > 25, Barrel;has L1 object near by (new)?;has L1 object near by (old)?", 2, 0, 2, 2, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld>0:L1PTNew>0", "GenENew > 0 && abs(GenEtaNew) > 1.5 && GenPTNew > 25", "colz text00",
      "GenPT > 25, Endcap;has L1 object near by (new)?;has L1 object near by (old)?", 2, 0, 2, 2, 0, 2, false, true);

   PdfFile.AddTextPage("How does the migration go");

   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0", "colz",
      ";L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0 && abs(GenEtaNew) < 1.5", "colz",
      "Barrel;L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0 && abs(GenEtaNew) > 1.5", "colz",
      "Endcap;L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);
   
   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0 && GenPTNew > 25", "colz",
      "GenPT > 25;L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0 && abs(GenEtaNew) < 1.5 && GenPTNew > 25", "colz",
      "GenPT > 25, Barrel;L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);
   PdfFile.AddPlot2D(T, "L1PTOld/GenPTOld:L1PTNew/GenPTNew", "GenENew > 0 && abs(GenEtaNew) > 1.5 && GenPTNew > 25", "colz",
      "GenPT > 25, Endcap;L1PT/GenPT (new);L1PT/GenPT (old)", 100, 0, 2, 100, 0, 2, false, true);

   PdfFile.AddTextPage("Some resolution plots");

   ResolutionPlot(PdfFile, T, "GenENew > 0 && L1PTNew > 0", "");
   ResolutionPlot(PdfFile, T, "GenENew > 0 && L1PTNew > 0 && abs(GenEtaNew) < 1.5", "Barrel");
   ResolutionPlot(PdfFile, T, "GenENew > 0 && L1PTNew > 0 && abs(GenEtaNew) > 1.5", "Endcap");
   ResolutionPlot(PdfFile, T, "GenENew > 0 && L1PTNew > 0 && abs(GenEtaNew) < 1.5 && GenPTNew > 25", "GenPT > 25, Barrel");
   ResolutionPlot(PdfFile, T, "GenENew > 0 && L1PTNew > 0 && abs(GenEtaNew) > 1.5 && GenPTNew > 25", "GenPT > 25, Endcap");

   PdfFile.AddTextPage("Recovered vs lost");

   PdfFile.AddPlot(T, "GenEtaNew", "GenENew > 0 && L1PTOld <= 0 && L1PTNew > 0", "",
      "Recovered;GenEta", 100, -2.5, 2.5);
   PdfFile.AddPlot(T, "GenEtaNew", "GenENew > 0 && L1PTOld > 0 && L1PTNew <= 0", "",
      "Lost;GenEta", 100, -2.5, 2.5);
   
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld <= 0 && L1PTNew > 0", "",
      "Recovered;GenPT", 100, 0, 100);
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld <= 0 && L1PTNew > 0 && abs(GenEtaNew) < 1.5", "",
      "Recovered, Barrel;GenPT", 100, 0, 100);
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld <= 0 && L1PTNew > 0 && abs(GenEtaNew) > 1.5", "",
      "Recovered, Endcap;GenPT", 100, 0, 100);
   
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld > 0 && L1PTNew <= 0", "",
      "Lost;GenPT", 100, 0, 100);
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld > 0 && L1PTNew <= 0 && abs(GenEtaNew) < 1.5", "",
      "Lost, Barrel;GenPT", 100, 0, 100);
   PdfFile.AddPlot(T, "GenPTNew", "GenENew > 0 && L1PTOld > 0 && L1PTNew <= 0 && abs(GenEtaNew) > 1.5", "",
      "Lost, Endcap;GenPT", 100, 0, 100);

   PdfFile.AddTextPage("Recovered vs lost, rates");
   
   PdfFile.AddPlotProfile(T, "L1PTOld <= 0 && L1PTNew > 0:GenEtaNew", "GenENew > 0", "prof",
      "Recovered;GenEta;N(Recovered) / N(All)", 100, -2.5, 2.5);
   PdfFile.AddPlotProfile(T, "L1PTOld > 0 && L1PTNew <= 0:GenEtaNew", "GenENew > 0", "prof",
      "Lost;GenEta;N(Lost) / N(All)", 100, -2.5, 2.5);
   
   PdfFile.AddPlotProfile(T, "L1PTOld <= 0 && L1PTNew > 0:GenPTNew", "GenENew > 0", "prof",
      "Recovered;GenPT;N(recovered) / N(all)", 100, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PTOld <= 0 && L1PTNew > 0:GenPTNew", "GenENew > 0 && abs(GenEtaNew) < 1.5", "prof",
      "Recovered, Barrel;GenPT;N(recovered) / N(all)", 100, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PTOld <= 0 && L1PTNew > 0:GenPTNew", "GenENew > 0 && abs(GenEtaNew) > 1.5", "prof",
      "Recovered, Endcap;GenPT;N(recovered) / N(all)", 100, 0, 100);
   
   PdfFile.AddPlotProfile(T, "L1PTOld > 0 && L1PTNew <= 0:GenPTNew", "GenENew > 0", "prof",
      "Lost;GenPT;N(Lost) / N(all)", 100, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PTOld > 0 && L1PTNew <= 0:GenPTNew", "GenENew > 0 && abs(GenEtaNew) < 1.5", "prof",
      "Lost, Barrel;GenPT;N(Lost) / N(all)", 100, 0, 100);
   PdfFile.AddPlotProfile(T, "L1PTOld > 0 && L1PTNew <= 0:GenPTNew", "GenENew > 0 && abs(GenEtaNew) > 1.5", "prof",
      "Lost, Endcap;GenPT;N(Lost) / N(all)", 100, 0, 100);
   
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ResolutionPlot(PdfFileHelper &PdfFile, TTree *T, string Selection, string Title)
{
   TH1D HHigh("HHigh", Form("%s;L1PT/GenPT;", Title.c_str()), 100, 0, 2);
   TH1D HMid("HMid", Form("%s;L1PT/GenPT;", Title.c_str()), 100, 0, 2);
   TH1D HLow("HLow", Form("%s;L1PT/GenPT;", Title.c_str()), 100, 0, 2);

   HHigh.SetStats(0);
   HMid.SetStats(0);
   HLow.SetStats(0);

   T->Draw("L1PTNew/GenPTNew>>HHigh", Form("(%s) * (L1PTOld/GenPTOld > 0.5)", Selection.c_str()));
   T->Draw("L1PTNew/GenPTNew>>HMid", Form("(%s) * (L1PTOld/GenPTOld < 0.5 && L1PTOld > 0)", Selection.c_str()));
   T->Draw("L1PTNew/GenPTNew>>HLow", Form("(%s) * (L1PTOld <= 0)", Selection.c_str()));

   HHigh.SetLineWidth(2);
   HMid.SetLineWidth(2);
   HLow.SetLineWidth(2);
   
   HHigh.SetLineColor(kBlack);
   HMid.SetLineColor(kBlue);
   HLow.SetLineColor(kRed);

   TLegend Legend(0.53, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.030);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HHigh, "L1/Gen (old) > 0.5", "l");
   Legend.AddEntry(&HMid, "L1/Gen (old) < 0.5", "l");
   Legend.AddEntry(&HLow, "No L1 (old) near by", "l");

   TCanvas Canvas;

   HHigh.Draw();
   HMid.Draw("same");
   HLow.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   Canvas.SetLogy();

   HHigh.Draw();
   HMid.Draw("same");
   HLow.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}





