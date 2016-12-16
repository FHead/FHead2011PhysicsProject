#include <iostream>
using namespace std;

#include "TProfile.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile F1("CombinedResult/AADataMB.root");
   TFile F2("CombinedResult/HydjetMB.root");
   TFile F3("CombinedResult/AAData.root");

   TProfile *Rho1 = (TProfile *)F1.Get("PRhoCentrality");
   TProfile *Rho2 = (TProfile *)F2.Get("PRhoCentrality");
   TProfile *Rho3 = (TProfile *)F2.Get("PRhoCentralityShifted2");
   TProfile *Rho4 = (TProfile *)F3.Get("PRhoCentrality");
   TProfile *RhoM1 = (TProfile *)F1.Get("PRhoMCentrality");
   TProfile *RhoM2 = (TProfile *)F2.Get("PRhoMCentrality");
   TProfile *RhoM3 = (TProfile *)F2.Get("PRhoMCentralityShifted2");
   TProfile *RhoM4 = (TProfile *)F3.Get("PRhoMCentrality");

   Rho1->SetMarkerStyle(8);
   Rho2->SetMarkerStyle(8);
   Rho3->SetMarkerStyle(8);
   Rho4->SetMarkerStyle(8);
   RhoM1->SetMarkerStyle(8);
   RhoM2->SetMarkerStyle(8);
   RhoM3->SetMarkerStyle(8);
   RhoM4->SetMarkerStyle(8);
   
   Rho2->SetMarkerColor(kRed);
   RhoM2->SetMarkerColor(kRed);
   Rho2->SetLineColor(kRed);
   RhoM2->SetLineColor(kRed);
   
   Rho3->SetMarkerColor(kCyan - 3);
   RhoM3->SetMarkerColor(kCyan - 3);
   Rho3->SetLineColor(kCyan - 3);
   RhoM3->SetLineColor(kCyan - 3);
   
   Rho4->SetMarkerColor(kBlue);
   RhoM4->SetMarkerColor(kBlue);
   Rho4->SetLineColor(kBlue);
   RhoM4->SetLineColor(kBlue);

   TCanvas C;

   TLegend Legend(0.4, 0.8, 0.8, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(Rho1, "Data (MB)", "lp");
   Legend.AddEntry(Rho4, "Data (HP)", "lp");
   Legend.AddEntry(Rho2, "Hydjet (MB)", "lp");
   Legend.AddEntry(Rho3, "Hydjet - shifted (MB)", "lp");
   
   TLegend Legend2(0.2, 0.2, 0.5, 0.4);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.SetTextSize(0.035);
   Legend2.AddEntry(Rho1, "Data (MB)", "lp");
   Legend2.AddEntry(Rho4, "Data (HP)", "lp");
   Legend2.AddEntry(Rho2, "Hydjet (MB)", "lp");
   Legend2.AddEntry(Rho3, "Hydjet - shifted (MB)", "lp");

   TH2D HWorld("HWorld", ";Centrality;#rho (GeV)", 100, 0, 1, 100, 0.3, 300);
   HWorld.SetStats(0);
   HWorld.Draw();
   Legend.Draw();

   Rho1->Draw("same");
   Rho2->Draw("same");
   Rho3->Draw("same");
   Rho4->Draw("same");
   
   C.SetLogy(false);

   C.SaveAs("RhoCentrality.png");
   C.SaveAs("RhoCentrality.C");
   C.SaveAs("RhoCentrality.eps");
   C.SaveAs("RhoCentrality.pdf");
   
   HWorld.Draw();
   Legend2.Draw();
   Rho1->Draw("same");
   Rho2->Draw("same");
   Rho3->Draw("same");
   Rho4->Draw("same");
   
   C.SetLogy(true);

   C.SaveAs("RhoCentralityLog.png");
   C.SaveAs("RhoCentralityLog.C");
   C.SaveAs("RhoCentralityLog.eps");
   C.SaveAs("RhoCentralityLog.pdf");
   
   TH2D HWorldM("HWorldM", ";Centrality;#rho_{M} (GeV)", 100, 0, 1, 100, 0.005, 1.2);
   HWorldM.SetStats(0);
   HWorldM.Draw();
   Legend.Draw();

   RhoM1->Draw("same");
   RhoM2->Draw("same");
   RhoM3->Draw("same");
   RhoM4->Draw("same");

   C.SetLogy(false);

   C.SaveAs("RhoMCentrality.png");
   C.SaveAs("RhoMCentrality.C");
   C.SaveAs("RhoMCentrality.eps");
   C.SaveAs("RhoMCentrality.pdf");

   HWorldM.Draw();
   Legend2.Draw();
   RhoM1->Draw("same");
   RhoM2->Draw("same");
   RhoM3->Draw("same");
   RhoM4->Draw("same");

   C.SetLogy(true);

   C.SaveAs("RhoMCentralityLog.png");
   C.SaveAs("RhoMCentralityLog.C");
   C.SaveAs("RhoMCentralityLog.eps");
   C.SaveAs("RhoMCentralityLog.pdf");

   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}



