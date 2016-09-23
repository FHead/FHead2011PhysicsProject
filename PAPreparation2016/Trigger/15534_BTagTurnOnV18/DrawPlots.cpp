#include <iostream>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"

int main();
void ExportCurve(TFile &File, string H1, string H2, string OutputBase, bool IsCSV = false);

int main()
{
   SetThesisStyle();

   TFile File("Output.root");

   string V[4] = {"V1V1", "V1V2", "V2V1", "V2V2"};

   ExportCurve(File, "HCaloJetBestCSVV1V1_All60", "HCaloJetBestCSVV1V1_Passed60", "Plots/CaloJetCSVV1V160", true);
   ExportCurve(File, "HCaloJetBestCSVV1V1_All80", "HCaloJetBestCSVV1V1_Passed80", "Plots/CaloJetCSVV1V180", true);
   ExportCurve(File, "HCaloJetBestCSVV1V1_All100", "HCaloJetBestCSVV1V1_Passed100", "Plots/CaloJetCSVV1V1100", true);
   ExportCurve(File, "HCaloJetBestCSVV1V2_All60", "HCaloJetBestCSVV1V2_Passed60", "Plots/CaloJetCSVV1V260", true);
   ExportCurve(File, "HCaloJetBestCSVV1V2_All80", "HCaloJetBestCSVV1V2_Passed80", "Plots/CaloJetCSVV1V280", true);
   ExportCurve(File, "HCaloJetBestCSVV1V2_All100", "HCaloJetBestCSVV1V2_Passed100", "Plots/CaloJetCSVV1V2100", true);
   ExportCurve(File, "HCaloJetBestCSVV2V1_All60", "HCaloJetBestCSVV2V1_Passed60", "Plots/CaloJetCSVV2V160", true);
   ExportCurve(File, "HCaloJetBestCSVV2V1_All80", "HCaloJetBestCSVV2V1_Passed80", "Plots/CaloJetCSVV2V180", true);
   ExportCurve(File, "HCaloJetBestCSVV2V1_All100", "HCaloJetBestCSVV2V1_Passed100", "Plots/CaloJetCSVV2V1100", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All60", "HCaloJetBestCSVV2V2_Passed60", "Plots/CaloJetCSVV2V260", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All80", "HCaloJetBestCSVV2V2_Passed80", "Plots/CaloJetCSVV2V280", true);
   ExportCurve(File, "HCaloJetBestCSVV2V2_All100", "HCaloJetBestCSVV2V2_Passed100", "Plots/CaloJetCSVV2V2100", true);

   ExportCurve(File, "HPFJetBestCSV_All60", "HPFJetBestCSV_Passed60", "Plots/PFJetCSV60", true);
   ExportCurve(File, "HPFJetBestCSV_All80", "HPFJetBestCSV_Passed80", "Plots/PFJetCSV80", true);
   ExportCurve(File, "HPFJetBestCSV_All100", "HPFJetBestCSV_Passed100", "Plots/PFJetCSV100", true);
   
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed60", "Plots/CaloJetPT60", false);
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed80", "Plots/CaloJetPT80", false);
   ExportCurve(File, "HCaloJetBestPT_All", "HCaloJetBestPT_Passed100", "Plots/CaloJetPT100", false);
   
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed60", "Plots/PFJetPT60", false);
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed80", "Plots/PFJetPT80", false);
   ExportCurve(File, "HPFJetBestPT_All", "HPFJetBestPT_Passed100", "Plots/PFJetPT100", false);

   return 0;
}

void ExportCurve(TFile &File, string H1Name, string H2Name, string OutputBase, bool IsCSV)
{
   TCanvas C;

   TH1D *H1 = (TH1D *)File.Get(H1Name.c_str());
   TH1D *H2 = (TH1D *)File.Get(H2Name.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   H1->SetStats(0);
   H2->SetStats(0);

   H1->SetMinimum(0);

   H2->SetLineColor(kRed);

   H1->Draw();
   H2->Draw("same");

   C.SaveAs(Form("%s_Distribution.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_Distribution.pdf", OutputBase.c_str()));

   TH1D *H1C = (TH1D *)H1->Clone(Form("H1"));
   TH1D *H2C = (TH1D *)H2->Clone(Form("H2"));

   H1C->Rebin(5);
   H2C->Rebin(5);

   H2C->Divide(H1C);

   H2C->SetMarkerColor(kBlack);
   H2C->SetMarkerStyle(11);
   H2C->SetMarkerSize(2);

   H2C->SetMinimum(0);
   H2C->SetMaximum(1.1);

   H2C->Draw("point");

   TF1 F("F", "[0]+[1]*erf((x-[2])*[3])");
   if(IsCSV == true)
   {
      F.SetParameter(0, 0.6);
      F.SetParameter(1, 0.3);
      F.SetParameter(2, 0.8);
      F.SetParameter(3, 1);
   }
   else
   {
      F.SetParameter(0, 0.6);
      F.SetParameter(1, 0.3);
      F.SetParameter(2, 50);
      F.SetParameter(3, 0.1);
   }
   H2C->Fit(&F);

   C.SaveAs(Form("%s_TurnOn.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_TurnOn.pdf", OutputBase.c_str()));

   delete H1C;
   delete H2C;
}




