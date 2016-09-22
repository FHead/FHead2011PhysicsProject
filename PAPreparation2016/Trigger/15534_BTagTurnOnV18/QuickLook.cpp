#include <iostream>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Output.root");

   string V[4] = {"V1V1", "V1V2", "V2V1", "V2V2"};

   TCanvas C1, C2, C3;
   C1.Divide(2, 2);
   C2.Divide(2, 2);
   C3.Divide(2, 2);

   for(int i = 0; i < 4; i++)
   {
      C1.cd(i + 1);

      TH1D *H1 = (TH1D *)File.Get(Form("HJetBestCSV%s_All", V[i].c_str()));
      TH1D *H2 = (TH1D *)File.Get(Form("HJetBestCSV%s_Passed", V[i].c_str()));

      H1->SetStats(0);
      H2->SetStats(0);

      H2->SetLineColor(kRed);

      H1->Draw();
      H2->Draw("same");

      if(i == 0)
      {
         C3.cd(1);
         H1->Draw();
         H2->Draw("same");
      }
      if(i == 3)
      {
         C3.cd(3);
         H1->Draw();
         H2->Draw("same");
      }

      C2.cd(i + 1);

      TH1D *H1C = (TH1D *)H1->Clone(Form("H1%d", i));
      TH1D *H2C = (TH1D *)H2->Clone(Form("H2%d", i));
      
      H1C->Rebin(5);
      H2C->Rebin(5);

      H2C->Divide(H1C);

      H2C->SetMarkerColor(kBlack);
      H2C->SetMarkerStyle(11);
      H2C->SetMarkerSize(2);

      H2C->Draw("point");

      TF1 F("F", "[0]+[1]*erf((x-[2])*[3])", 0, 1);
      F.SetParameter(0, 0.6);
      F.SetParameter(1, 0.3);
      F.SetParameter(2, 0.8);
      F.SetParameter(3, 1);
      H2C->Fit(&F);

      if(i == 0)
      {
         C3.cd(2);
         H2C->Draw("point");
      }
      if(i == 3)
      {
         C3.cd(4);
         H2C->Draw("point");
      }
   }

   TH1D *H1 = (TH1D *)File.Get("HPFJetBestCSV_All");
   TH1D *H2 = (TH1D *)File.Get("HPFJetBestCSV_Passed");

   TCanvas C;

   C.Divide(2);

   C.cd(1);

   H1->SetStats(0);
   H2->SetStats(0);

   H2->SetLineColor(kRed);

   H1->Draw();
   H2->Draw("same");

   C.cd(2);

   TH1D *H1C = (TH1D *)H1->Clone("H1C");
   TH1D *H2C = (TH1D *)H2->Clone("H2C");

   H1C->Rebin(5);
   H2C->Rebin(5);

   H2C->Divide(H1C);

   H2C->SetMarkerColor(kRed);
   H2C->SetMarkerStyle(6);

   H2C->Draw("point");

   C1.SaveAs("Plots_C1.png");
   C1.SaveAs("Plots_C1.C");
   C1.SaveAs("Plots_C1.eps");
   C1.SaveAs("Plots_C1.pdf");
   C2.SaveAs("Plots_C2.png");
   C2.SaveAs("Plots_C2.C");
   C2.SaveAs("Plots_C2.eps");
   C2.SaveAs("Plots_C2.pdf");
   C3.SaveAs("Plots_C3.png");
   C3.SaveAs("Plots_C3.C");
   C3.SaveAs("Plots_C3.eps");
   C3.SaveAs("Plots_C3.pdf");
   C.SaveAs("Plots_C.png");
   C.SaveAs("Plots_C.C");
   C.SaveAs("Plots_C.eps");
   C.SaveAs("Plots_C.pdf");
}
