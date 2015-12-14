#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   if(argc <= 2)
   {
      cerr << "Supply a file name and an output base please" << endl;
      return -1;
   }

   TFile InputFile(argv[1]);

   PsFileHelper PsFile(string(argv[2]) + ".ps");
   PsFile.AddTextPage(argv[2]);

   for(int i = 0; i < 4; i++)
   {
      string Tag = "";
      if(i == 0)   Tag = "L";
      if(i == 1)   Tag = "M";
      if(i == 2)   Tag = "LL";
      if(i == 3)   Tag = "MM";

      double MRViewMax = 1;
      if(i == 0)   MRViewMax = 0.7;
      if(i == 1)   MRViewMax = 0.3;
      if(i == 2)   MRViewMax = 0.2;
      if(i == 3)   MRViewMax = 0.02;

      PsFile.AddTextPage(Tag);

      TH1D *HMR_R2010 = (TH1D *)InputFile.Get("HMR_R2010");
      TH1D *HMR_R2020 = (TH1D *)InputFile.Get("HMR_R2020");
      TH1D *HMR_R2030 = (TH1D *)InputFile.Get("HMR_R2030");
      TH1D *HMR_R2040 = (TH1D *)InputFile.Get("HMR_R2040");
      TH1D *HMR_R2050 = (TH1D *)InputFile.Get("HMR_R2050");

      TH1D *HMR_R2010_Tag = (TH1D *)InputFile.Get(Form("HMR_R2010_%s", Tag.c_str()));
      TH1D *HMR_R2020_Tag = (TH1D *)InputFile.Get(Form("HMR_R2020_%s", Tag.c_str()));
      TH1D *HMR_R2030_Tag = (TH1D *)InputFile.Get(Form("HMR_R2030_%s", Tag.c_str()));
      TH1D *HMR_R2040_Tag = (TH1D *)InputFile.Get(Form("HMR_R2040_%s", Tag.c_str()));
      TH1D *HMR_R2050_Tag = (TH1D *)InputFile.Get(Form("HMR_R2050_%s", Tag.c_str()));
      
      TH1D *HR2_MR200 = (TH1D *)InputFile.Get("HR2_MR200");
      TH1D *HR2_MR300 = (TH1D *)InputFile.Get("HR2_MR300");
      TH1D *HR2_MR400 = (TH1D *)InputFile.Get("HR2_MR400");
      TH1D *HR2_MR500 = (TH1D *)InputFile.Get("HR2_MR500");

      TH1D *HR2_MR200_Tag = (TH1D *)InputFile.Get(Form("HR2_MR200_%s", Tag.c_str()));
      TH1D *HR2_MR300_Tag = (TH1D *)InputFile.Get(Form("HR2_MR300_%s", Tag.c_str()));
      TH1D *HR2_MR400_Tag = (TH1D *)InputFile.Get(Form("HR2_MR400_%s", Tag.c_str()));
      TH1D *HR2_MR500_Tag = (TH1D *)InputFile.Get(Form("HR2_MR500_%s", Tag.c_str()));

      TCanvas C;
      C.SetGridx();
      C.SetGridy();

      C.SetLogy();

      HMR_R2010->Draw("hist");
      HMR_R2010_Tag->Draw("same");
      PsFile.AddCanvas(C);

      HMR_R2020->Draw("hist");
      HMR_R2020_Tag->Draw("same");
      PsFile.AddCanvas(C);

      HMR_R2030->Draw("hist");
      HMR_R2030_Tag->Draw("same");
      PsFile.AddCanvas(C);

      HMR_R2040->Draw("hist");
      HMR_R2040_Tag->Draw("same");
      PsFile.AddCanvas(C);

      HMR_R2050->Draw("hist");
      HMR_R2050_Tag->Draw("same");
      PsFile.AddCanvas(C);

      HMR_R2010_Tag->SetStats(0);
      HMR_R2020_Tag->SetStats(0);
      HMR_R2030_Tag->SetStats(0);
      HMR_R2040_Tag->SetStats(0);
      HMR_R2050_Tag->SetStats(0);

      HMR_R2010->Sumw2();
      HMR_R2020->Sumw2();
      HMR_R2030->Sumw2();
      HMR_R2040->Sumw2();
      HMR_R2050->Sumw2();

      HMR_R2010_Tag->Sumw2();
      HMR_R2020_Tag->Sumw2();
      HMR_R2030_Tag->Sumw2();
      HMR_R2040_Tag->Sumw2();
      HMR_R2050_Tag->Sumw2();

      HMR_R2010_Tag->SetLineWidth(2);
      HMR_R2020_Tag->SetLineWidth(2);
      HMR_R2030_Tag->SetLineWidth(2);
      HMR_R2040_Tag->SetLineWidth(2);
      HMR_R2050_Tag->SetLineWidth(2);

      HMR_R2010_Tag->SetLineColor(1);
      HMR_R2020_Tag->SetLineColor(2);
      HMR_R2030_Tag->SetLineColor(3);
      HMR_R2040_Tag->SetLineColor(4);
      HMR_R2050_Tag->SetLineColor(5);

      HMR_R2010_Tag->Divide(HMR_R2010);
      HMR_R2020_Tag->Divide(HMR_R2020);
      HMR_R2030_Tag->Divide(HMR_R2030);
      HMR_R2040_Tag->Divide(HMR_R2040);
      HMR_R2050_Tag->Divide(HMR_R2050);

      TLegend Legend(0.15, 0.85, 0.35, 0.55);
      Legend.SetFillStyle(0);
      Legend.SetBorderSize(0);
      Legend.SetTextFont(42);
      Legend.AddEntry(HMR_R2010_Tag, "R^{2} > 0.1", "l");
      Legend.AddEntry(HMR_R2020_Tag, "R^{2} > 0.2", "l");
      Legend.AddEntry(HMR_R2030_Tag, "R^{2} > 0.3", "l");
      Legend.AddEntry(HMR_R2040_Tag, "R^{2} > 0.4", "l");
      Legend.AddEntry(HMR_R2050_Tag, "R^{2} > 0.5", "l");

      HMR_R2010_Tag->SetTitle(Form("At least %s tag / All for different R cuts", Tag.c_str()));
      HMR_R2010_Tag->SetMinimum(0);
      HMR_R2010_Tag->SetMaximum(MRViewMax);

      C.SetLogy(false);
      HMR_R2010_Tag->Draw();
      HMR_R2020_Tag->Draw("same");
      HMR_R2030_Tag->Draw("same");
      HMR_R2040_Tag->Draw("same");
      HMR_R2050_Tag->Draw("same");
      Legend.Draw();
      PsFile.AddCanvas(C);
      
      C.SetLogy(true);

      HR2_MR200->Draw("hist");
      HR2_MR200_Tag->Draw("hist same");
      PsFile.AddCanvas(C);
      
      HR2_MR300->Draw("hist");
      HR2_MR300_Tag->Draw("hist same");
      PsFile.AddCanvas(C);
      
      HR2_MR400->Draw("hist");
      HR2_MR400_Tag->Draw("hist same");
      PsFile.AddCanvas(C);
      
      HR2_MR500->Draw("hist");
      HR2_MR500_Tag->Draw("hist same");
      PsFile.AddCanvas(C);

      HR2_MR200_Tag->SetStats(0);
      HR2_MR300_Tag->SetStats(0);
      HR2_MR400_Tag->SetStats(0);
      HR2_MR500_Tag->SetStats(0);

      HR2_MR200->Sumw2();
      HR2_MR300->Sumw2();
      HR2_MR400->Sumw2();
      HR2_MR500->Sumw2();

      HR2_MR200_Tag->Sumw2();
      HR2_MR300_Tag->Sumw2();
      HR2_MR400_Tag->Sumw2();
      HR2_MR500_Tag->Sumw2();

      HR2_MR200_Tag->SetLineWidth(2);
      HR2_MR300_Tag->SetLineWidth(2);
      HR2_MR400_Tag->SetLineWidth(2);
      HR2_MR500_Tag->SetLineWidth(2);
      
      HR2_MR200_Tag->SetLineColor(1);
      HR2_MR300_Tag->SetLineColor(2);
      HR2_MR400_Tag->SetLineColor(3);
      HR2_MR500_Tag->SetLineColor(4);

      HR2_MR200_Tag->Divide(HR2_MR200);
      HR2_MR300_Tag->Divide(HR2_MR300);
      HR2_MR400_Tag->Divide(HR2_MR400);
      HR2_MR500_Tag->Divide(HR2_MR500);

      TLegend Legend2(0.15, 0.85, 0.35, 0.55);
      Legend2.SetFillStyle(0);
      Legend2.SetBorderSize(0);
      Legend2.SetTextFont(42);
      Legend2.AddEntry(HR2_MR200_Tag, "MR > 200", "l");
      Legend2.AddEntry(HR2_MR300_Tag, "MR > 300", "l");
      Legend2.AddEntry(HR2_MR400_Tag, "MR > 400", "l");
      Legend2.AddEntry(HR2_MR500_Tag, "MR > 500", "l");

      HR2_MR200_Tag->SetTitle(Form("At least %s tag / All for different MR cuts", Tag.c_str()));

      C.SetLogy(false);
      HR2_MR200_Tag->Draw();
      HR2_MR300_Tag->Draw("same");
      HR2_MR400_Tag->Draw("same");
      HR2_MR500_Tag->Draw("same");
      Legend2.Draw();
      PsFile.AddCanvas(C);
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   InputFile.Close();

   return 0;
}








