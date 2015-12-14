#include <iostream>
#include <fstream>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TFile.h"
#include "TList.h"
#include "TClass.h"
#include "TLegend.h"

#include "SetStyle.h"

int main();
double MakePlot(TH1D *H1, TH1D *H2, TH1F *H3, string Identifier);

int main()
{
   SetStyle();

   TFile F1("Output.root");
   TFile F2("ISRWeights_TopologyT2bb.root");

   TList *ListOfKeys = F1.GetListOfKeys();
   TIter KeyIterator(ListOfKeys);
   TObject *Object = KeyIterator();

   TH2D HFilledMasses("HFilledMasses", ";#tilde{b} Mass [GeV];#tilde{#chi}_{1}^{0} Mass [GeV]",
      50, 0, 1250, 50, 0, 1250);
   TH2D HFilledMasses2("HFilledMasses2", "(Weighted efficiency) / (Efficiency);sbottom;neutralino",
      24, 0, 600, 24, 0, 600);
   TH2D HFilledMassesContour("HFilledMassesContour", "(Weighted efficiency) / (Efficiency);sbottom;neutralino",
      50, 0, 1250, 50, 0, 1250);

   ofstream out("DefineList.js");

   out << "var OccupiedList = new Array();" << endl;
   out << "" << endl;
   out << "function Initialize()" << endl;
   out << "{" << endl;
   out << "   OccupiedList.length = 0;" << endl;
   out << "" << endl;

   while(Object != NULL)
   {
      if(Object->IsFolder() == true)
      {
         Object = KeyIterator();
         continue;
      }

      TObject *RealObject = F1.Get(Object->GetName());
      string Name = RealObject->GetName();
      string Type = RealObject->IsA()->GetName();

      if(Type == "TH1D" && Name.find("AllEventsPT_") == 0)
      {
         string Name2 = Name;
         Name2 = Name2.replace(0, 3, "Passed");

         string Identifier = Name.substr(12);
         string Mass1String = Identifier.substr(0, 4);
         string Mass2String = Identifier.substr(5, 4);

         int Mass1 = atoi(Mass1String.c_str());
         int Mass2 = atoi(Mass2String.c_str());

         if(Mass1 == 475 && Mass2 == 425)
         {
            Object = KeyIterator();
            continue;
         }

         TH1D *H1 = (TH1D *)F1.Get(Name.c_str());
         TH1D *H2 = (TH1D *)F1.Get(Name2.c_str());
         TH1F *H3 = (TH1F *)F2.Get(Form("h_ISRWeight_lastPt_%d_%d", Mass1, Mass2));

         double EfficiencyRatio = MakePlot(H1, H2, H3, Identifier);

         HFilledMasses.Fill(Mass1, Mass2, EfficiencyRatio);
         HFilledMasses2.Fill(Mass1, Mass2, EfficiencyRatio);
         HFilledMassesContour.Fill(Mass1, Mass2, EfficiencyRatio);
         
         out << "   OccupiedList[OccupiedList.length] = {\"X\": " << Mass1 << ", \"Y\": " << Mass2
            << ", \"Identifier\": \"" << Identifier << "\"};" << endl;
      }

      Object = KeyIterator();
   }

   double Contours[] = {0.5, 0.8, 0.9, 0.95};
   HFilledMassesContour.SetContour(4, Contours);
   HFilledMassesContour.SetLineWidth(2);

   TLatex L;
   L.SetTextFont(42);
   L.SetTextSize(0.04);

   TCanvas C("C", "C", 0, 0, 512, 512);
   HFilledMasses.SetStats(0);
   HFilledMasses.GetXaxis()->SetTitleOffset(1.4);
   HFilledMasses.GetYaxis()->SetTitleOffset(1.4);
   HFilledMasses.Draw("colz");
   HFilledMassesContour.Draw("cont3 same");
   L.DrawLatex(100, 1100, "Efficiency drop contours:");
   L.DrawLatex(150, 1000, "5%, 10%, 20%, 50%");
   C.SaveAs("FilledMass.png");
   C.SaveAs("FilledMass.C");
   C.SaveAs("FilledMass.eps");
   C.SaveAs("FilledMass.pdf");
   
   HFilledMasses2.SetStats(0);
   HFilledMasses2.Draw("colz");
   HFilledMassesContour.Draw("cont3 same");
   L.DrawLatex(100, 1100, "Efficiency drop contours:");
   L.DrawLatex(150, 1000, "5%, 10%, 20%, 50%");
   C.SaveAs("FilledMass2.png");
   C.SaveAs("FilledMass2.C");
   C.SaveAs("FilledMass2.eps");
   C.SaveAs("FilledMass2.pdf");

   out << "};" << endl;

   out.close();

   F2.Close();
   F1.Close();
}

double MakePlot(TH1D *H1, TH1D *H2, TH1F *H3, string Identifier)
{
   if(H1 == NULL || H2 == NULL)
      return 0;

   double WeightedPass = 0;
   double WeightedTotal = 0;
   for(int i = 1; i <= H1->GetNbinsX(); i++)
   {
      double X = H1->GetBinCenter(i);
      int Bin = H3->FindBin(X);

      WeightedPass = WeightedPass + H2->GetBinContent(i) * H3->GetBinContent(Bin);
      WeightedTotal = WeightedTotal + H1->GetBinContent(i) * H3->GetBinContent(Bin);
   }
   
   double Efficiency = H2->Integral() / H1->Integral();
   double WeightedEfficiency = WeightedPass / WeightedTotal;

   string Title = H1->GetTitle();
   Title = Title.replace(6, 3, "all and passed");
   H1->SetTitle(Title.c_str());
   H1->GetXaxis()->SetTitle("di-sbottom PT (GeV)");

   H1->SetLineWidth(2);
   H2->SetLineWidth(2);

   H1->SetLineColor(kGreen);
   H2->SetLineColor(kBlue);

   H1->SetStats(0);
   H2->SetStats(0);

   TCanvas C("C", "C", 512, 400);

   H1->Draw();
   H2->Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.5);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(H1, "All events", "l");
   Legend.AddEntry(H2, "Passed events", "l");
   Legend.AddEntry(H1, Form("Efficiency = %.6f", Efficiency), "");
   Legend.AddEntry(H1, Form("Weighted = %.6f", WeightedEfficiency), "");
   Legend.Draw();

   C.SetLogy(true);
   // C.SaveAs(Form("Histograms/PT_%s.png", Identifier.c_str()));

   H3->SetMinimum(0);
   H3->SetMaximum(1.5);
   H3->SetStats(0);
   H3->Draw();
   C.SetLogy(false);
   // C.SaveAs(Form("Histograms/Weight_%s.png", Identifier.c_str()));

   return WeightedEfficiency / Efficiency;
}





