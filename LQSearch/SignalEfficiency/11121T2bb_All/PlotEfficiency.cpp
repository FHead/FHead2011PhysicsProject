#include <iostream>
#include <fstream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   TFile OutputFile("EfficiencyPlot.root", "RECREATE");

   TH2D HEfficiency("HEfficiency", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 50, 0, 1250, 50, 0, 1250);
   TH2D HEfficiencyZoomed("HEfficiencyZoomed", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 20, 0, 500, 20, 0, 500);
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

   double Contours[] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35};
   TH2D *HEfficiencyClone = (TH2D *)HEfficiency.Clone("ImAClone");
   HEfficiencyClone->SetContour(7, Contours);
   
   TCanvas C1("C1", "C1", 1024, 1024);
   HEfficiency.Draw("colz");
   HEfficiencyClone->Draw("cont3 same");
   C1.SaveAs("T2bbEfficiency.png");
   C1.SaveAs("T2bbEfficiency.C");
   C1.SaveAs("T2bbEfficiency.eps");
   C1.SaveAs("T2bbEfficiency.pdf");

   TH2D *HEfficiencyZoomedClone = (TH2D *)HEfficiencyZoomed.Clone("ImNotAClone");
   HEfficiencyZoomedClone->SetContour(7, Contours);

   HEfficiencyZoomed.Draw("colz");
   HEfficiencyZoomedClone->Draw("cont3 same");
   C1.SaveAs("T2bbEfficiencyZoomed.png");
   C1.SaveAs("T2bbEfficiencyZoomed.C");
   C1.SaveAs("T2bbEfficiencyZoomed.eps");
   C1.SaveAs("T2bbEfficiencyZoomed.pdf");

   OutputFile.Close();

   return 0;
}





