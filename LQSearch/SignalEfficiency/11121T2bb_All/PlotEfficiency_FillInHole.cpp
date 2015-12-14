#include <iostream>
#include <fstream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
void FillInHoles(TH2D &H);

int main()
{
   SetStyle();

   TFile OutputFile("EfficiencyPlot.root", "RECREATE");

   TH2D HEfficiency("HEfficiency", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 50, 0, 1250, 50, 0, 1250);
   TH2D HEfficiencyZoomed("HEfficiencyZoomed", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 21, 0, 525, 21, 0, 525);
   TH2D HEfficiencyError("HEfficiencyError", "Efficiency error;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);

   ifstream in("Processed");

   while(in)
   {
      double m0 = 0;
      double m12 = 0;
      double eff = 0;
      double seff = 0;

      in >> m0 >> m12 >> eff >> seff;

      if(m0 == 0)
         continue;

      HEfficiency.Fill(m0, m12, eff);
      HEfficiencyZoomed.Fill(m0, m12, eff);
      HEfficiencyError.Fill(m0, m12, seff);
   }

   in.close();

   FillInHoles(HEfficiency);
   FillInHoles(HEfficiencyZoomed);
   FillInHoles(HEfficiencyError);

   HEfficiency.SetStats(0);
   HEfficiencyZoomed.SetStats(0);
   HEfficiencyError.SetStats(0);

   PsFileHelper PsFile("Efficiencies.ps");
   PsFile.AddTextPage("Efficiencies!");

   HEfficiency.SetMaximum(0.3);
   PsFile.AddPlot(HEfficiency, "colz");   HEfficiency.Write();
   PsFile.AddPlot(HEfficiencyZoomed, "colz");   HEfficiencyZoomed.Write();
   PsFile.AddPlot(HEfficiencyError, "colz");   HEfficiencyError.Write();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   double Contours[] = {0.01, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35};
   TH2D *HEfficiencyClone = (TH2D *)HEfficiency.Clone("ImAClone");
   HEfficiencyClone->SetContour(8, Contours);

   TCanvas C1("C1", "C1", 1024, 1024);
   
   HEfficiency.GetXaxis()->SetTitleOffset(1.20);
   HEfficiency.GetYaxis()->SetTitleOffset(1.40);
   HEfficiency.Draw("colz");
   // HEfficiencyClone->Draw("cont3 same");
   TPaletteAxis *EfficiencyPalette = (TPaletteAxis *)HEfficiency.GetListOfFunctions()->FindObject("palette");
   EfficiencyPalette->SetX1NDC(0.91);
   EfficiencyPalette->SetX2NDC(0.93);
   EfficiencyPalette->SetY1NDC(0.1);
   EfficiencyPalette->SetY2NDC(0.9);
   C1.Update();
   C1.SetLogz();
   C1.SaveAs("T2bbEfficiency.png");
   C1.SaveAs("T2bbEfficiency.C");
   C1.SaveAs("T2bbEfficiency.eps");
   C1.SaveAs("T2bbEfficiency.pdf");

   TH2D *HEfficiencyZoomedClone = (TH2D *)HEfficiencyZoomed.Clone("ImNotAClone");
   HEfficiencyZoomedClone->SetContour(7, Contours);

   HEfficiencyZoomed.GetXaxis()->SetTitleOffset(1.20);
   HEfficiencyZoomed.GetYaxis()->SetTitleOffset(1.40);
   HEfficiencyZoomed.Draw("colz");
   HEfficiencyZoomedClone->Draw("cont3 same");
   TPaletteAxis *EfficiencyZoomedPalette = (TPaletteAxis *)HEfficiencyZoomed.GetListOfFunctions()->FindObject("palette");
   EfficiencyZoomedPalette->SetX1NDC(0.91);
   EfficiencyZoomedPalette->SetX2NDC(0.93);
   EfficiencyZoomedPalette->SetY1NDC(0.1);
   EfficiencyZoomedPalette->SetY2NDC(0.9);
   C1.Update();
   C1.SaveAs("T2bbEfficiencyZoomed.png");
   C1.SaveAs("T2bbEfficiencyZoomed.C");
   C1.SaveAs("T2bbEfficiencyZoomed.eps");
   C1.SaveAs("T2bbEfficiencyZoomed.pdf");

   OutputFile.Close();

   return 0;
}

void FillInHoles(TH2D &H)
{
   bool Changed = true;

   while(Changed == true)
   {
      Changed = false;
      
      for(int i = 1 + 1; i <= H.GetNbinsX() - 1; i++)
      {
         for(int j = 1 + 1; j <= H.GetNbinsY() - 1; j++)
         {
            if(H.GetBinContent(i, j - 1) > 0 &&
                  H.GetBinContent(i, j + 1) > 0 &&
                  H.GetBinContent(i - 1, j - 1) > 0 &&
                  H.GetBinContent(i - 1, j) > 0 &&
                  H.GetBinContent(i - 1, j + 1) > 0 &&
                  H.GetBinContent(i + 1, j - 1) > 0 &&
                  H.GetBinContent(i + 1, j) > 0 &&
                  H.GetBinContent(i + 1, j + 1) > 0 &&
                  H.GetBinContent(i, j) == 0)
            {
               double Sum = H.GetBinContent(i, j - 1);
               Sum = Sum + H.GetBinContent(i, j + 1);
               Sum = Sum + H.GetBinContent(i - 1, j - 1);
               Sum = Sum + H.GetBinContent(i - 1, j);
               Sum = Sum + H.GetBinContent(i - 1, j + 1);
               Sum = Sum + H.GetBinContent(i + 1, j - 1);
               Sum = Sum + H.GetBinContent(i + 1, j);
               Sum = Sum + H.GetBinContent(i + 1, j + 1);
               H.SetBinContent(i, j, Sum / 8);

               Changed = true;
            }
         }
      }
      
      for(int i = 1 + 1; i <= H.GetNbinsX() - 1; i++)
      {
         for(int j = 1 + 1; j <= H.GetNbinsY() - 1; j++)
         {
            if(H.GetBinContent(i - 1, j - 1) > 0 &&
               H.GetBinContent(i - 1, j + 1) > 0 &&
               H.GetBinContent(i + 1, j - 1) > 0 &&
               H.GetBinContent(i + 1, j + 1) > 0 &&
               H.GetBinContent(i, j) == 0)
            {
               double Sum = H.GetBinContent(i - 1, j - 1);
               Sum = Sum + H.GetBinContent(i - 1, j + 1);
               Sum = Sum + H.GetBinContent(i + 1, j - 1);
               Sum = Sum + H.GetBinContent(i + 1, j + 1);
               H.SetBinContent(i, j, Sum / 4);

               Changed = true;
            }
         }
      }
      
      for(int i = 1 + 1; i <= H.GetNbinsX() - 1; i++)
      {
         for(int j = 1 + 1; j <= H.GetNbinsY() - 1; j++)
         {
            if(H.GetBinContent(i, j - 1) > 0 &&
               H.GetBinContent(i, j + 1) > 0 &&
               H.GetBinContent(i - 1, j) > 0 &&
               H.GetBinContent(i + 1, j) > 0 &&
               H.GetBinContent(i, j) == 0)
            {
               double Sum = H.GetBinContent(i, j - 1);
               Sum = Sum + H.GetBinContent(i, j + 1);
               Sum = Sum + H.GetBinContent(i - 1, j);
               Sum = Sum + H.GetBinContent(i + 1, j);
               H.SetBinContent(i, j, Sum / 4);

               Changed = true;
            }
         }
      }
   }
}



