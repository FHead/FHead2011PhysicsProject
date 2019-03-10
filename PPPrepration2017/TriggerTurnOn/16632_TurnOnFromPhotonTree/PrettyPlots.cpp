#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("TurnOn.pdf");
   PdfFile.AddTextPage("Turn-on for jets");

   TFile File("Output.root");

   TGraphAsymmErrors GCalo30, GCalo40, GCalo50, GCalo80, GCalo100, GCalo120;
   TGraphAsymmErrors GCaloL116, GCaloL120, GCaloL128, GCaloL140, GCaloL160;
   TGraphAsymmErrors GPFL116, GPFL120, GPFL128, GPFL140, GPFL160;
   TGraphAsymmErrors GPF30, GPF50, GPF80, GPF100, GPF120;
   TGraphAsymmErrors GPFFWDL120, GPFFWDL135, GPFFWDL140, GPFFWDL150, GPFFWDL160;
   TGraphAsymmErrors GPFFWD30, GPFFWD50, GPFFWD60, GPFFWD70, GPFFWD80;

   GCalo30.Divide((TH1D *)File.Get("HCaloJet_Pass30"), (TH1D *)File.Get("HCaloJet_All"));
   GCalo40.Divide((TH1D *)File.Get("HCaloJet_Pass40"), (TH1D *)File.Get("HCaloJet_All"));
   GCalo50.Divide((TH1D *)File.Get("HCaloJet_Pass50"), (TH1D *)File.Get("HCaloJet_All"));
   GCalo80.Divide((TH1D *)File.Get("HCaloJet_Pass80"), (TH1D *)File.Get("HCaloJet_All"));
   GCalo100.Divide((TH1D *)File.Get("HCaloJet_Pass100"), (TH1D *)File.Get("HCaloJet_All"));
   GCalo120.Divide((TH1D *)File.Get("HCaloJet_Pass120"), (TH1D *)File.Get("HCaloJet_All"));
   
   GCaloL116.Divide((TH1D *)File.Get("HCaloJet_PassL116"), (TH1D *)File.Get("HCaloJet_All"));
   GCaloL120.Divide((TH1D *)File.Get("HCaloJet_PassL120"), (TH1D *)File.Get("HCaloJet_All"));
   GCaloL128.Divide((TH1D *)File.Get("HCaloJet_PassL128"), (TH1D *)File.Get("HCaloJet_All"));
   GCaloL140.Divide((TH1D *)File.Get("HCaloJet_PassL140"), (TH1D *)File.Get("HCaloJet_All"));
   GCaloL160.Divide((TH1D *)File.Get("HCaloJet_PassL160"), (TH1D *)File.Get("HCaloJet_All"));
   
   GPFL116.Divide((TH1D *)File.Get("HPFJet_PassL116"), (TH1D *)File.Get("HPFJet_All"));
   GPFL120.Divide((TH1D *)File.Get("HPFJet_PassL120"), (TH1D *)File.Get("HPFJet_All"));
   GPFL128.Divide((TH1D *)File.Get("HPFJet_PassL128"), (TH1D *)File.Get("HPFJet_All"));
   GPFL140.Divide((TH1D *)File.Get("HPFJet_PassL140"), (TH1D *)File.Get("HPFJet_All"));
   GPFL160.Divide((TH1D *)File.Get("HPFJet_PassL160"), (TH1D *)File.Get("HPFJet_All"));
   
   GPF30.Divide((TH1D *)File.Get("HPFJet_Pass30"), (TH1D *)File.Get("HPFJet_All"));
   GPF50.Divide((TH1D *)File.Get("HPFJet_Pass50"), (TH1D *)File.Get("HPFJet_All"));
   GPF80.Divide((TH1D *)File.Get("HPFJet_Pass80"), (TH1D *)File.Get("HPFJet_All"));
   GPF100.Divide((TH1D *)File.Get("HPFJet_Pass100"), (TH1D *)File.Get("HPFJet_All"));
   GPF120.Divide((TH1D *)File.Get("HPFJet_Pass120"), (TH1D *)File.Get("HPFJet_All"));

   GPFFWDL120.Divide((TH1D *)File.Get("HPFJetFWD_PassL120"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWDL135.Divide((TH1D *)File.Get("HPFJetFWD_PassL135"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWDL140.Divide((TH1D *)File.Get("HPFJetFWD_PassL140"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWDL150.Divide((TH1D *)File.Get("HPFJetFWD_PassL150"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWDL160.Divide((TH1D *)File.Get("HPFJetFWD_PassL160"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWD30.Divide((TH1D *)File.Get("HPFJetFWD_Pass30"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWD50.Divide((TH1D *)File.Get("HPFJetFWD_Pass50"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWD60.Divide((TH1D *)File.Get("HPFJetFWD_Pass60"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWD70.Divide((TH1D *)File.Get("HPFJetFWD_Pass70"), (TH1D *)File.Get("HPFJetFWD_All"));
   GPFFWD80.Divide((TH1D *)File.Get("HPFJetFWD_Pass80"), (TH1D *)File.Get("HPFJetFWD_All"));

   PdfFile.AddPlot(GCaloL116, "apl");
   PdfFile.AddPlot(GCaloL120, "apl");
   PdfFile.AddPlot(GCaloL128, "apl");
   PdfFile.AddPlot(GCaloL140, "apl");
   PdfFile.AddPlot(GCaloL160, "apl");
   PdfFile.AddPlot(GCalo30, "apl");
   PdfFile.AddPlot(GCalo40, "apl");
   PdfFile.AddPlot(GCalo50, "apl");
   PdfFile.AddPlot(GCalo80, "apl");
   PdfFile.AddPlot(GCalo100, "apl");
   PdfFile.AddPlot(GCalo120, "apl");
   
   PdfFile.AddPlot(GPFL116, "apl");
   PdfFile.AddPlot(GPFL120, "apl");
   PdfFile.AddPlot(GPFL128, "apl");
   PdfFile.AddPlot(GPFL140, "apl");
   PdfFile.AddPlot(GPFL160, "apl");
   PdfFile.AddPlot(GPF30, "apl");
   PdfFile.AddPlot(GPF50, "apl");
   PdfFile.AddPlot(GPF80, "apl");
   PdfFile.AddPlot(GPF100, "apl");
   PdfFile.AddPlot(GPF120, "apl");

   PdfFile.AddPlot(GPFFWDL120, "apl");
   PdfFile.AddPlot(GPFFWDL135, "apl");
   PdfFile.AddPlot(GPFFWDL140, "apl");
   PdfFile.AddPlot(GPFFWDL150, "apl");
   PdfFile.AddPlot(GPFFWDL160, "apl");
   PdfFile.AddPlot(GPFFWD30, "apl");
   PdfFile.AddPlot(GPFFWD50, "apl");
   PdfFile.AddPlot(GPFFWD60, "apl");
   PdfFile.AddPlot(GPFFWD70, "apl");
   PdfFile.AddPlot(GPFFWD80, "apl");

   GCaloL116.SetLineColor(kBlack);       GCaloL116.SetMarkerColor(kBlack);
   GCaloL120.SetLineColor(kPink - 3);    GCaloL120.SetMarkerColor(kPink - 3);
   GCaloL128.SetLineColor(kYellow - 3);  GCaloL128.SetMarkerColor(kYellow - 3);
   GCaloL140.SetLineColor(kGreen - 3);   GCaloL140.SetMarkerColor(kGreen - 3);
   GCaloL160.SetLineColor(kRed + 3);     GCaloL160.SetMarkerColor(kRed + 3);
   GCalo30.SetLineColor(kBlack);        GCalo30.SetMarkerColor(kBlack);
   GCalo40.SetLineColor(kGreen - 3);    GCalo40.SetMarkerColor(kGreen - 3);
   GCalo50.SetLineColor(kPink - 3);     GCalo50.SetMarkerColor(kPink - 3);
   GCalo80.SetLineColor(kYellow - 3);   GCalo80.SetMarkerColor(kYellow - 3);
   GCalo100.SetLineColor(kBlue - 3);    GCalo100.SetMarkerColor(kBlue - 3);
   GCalo120.SetLineColor(kRed + 3);     GCalo120.SetMarkerColor(kRed + 3);
   
   GPFL116.SetLineColor(kBlack);       GPFL116.SetMarkerColor(kBlack);
   GPFL120.SetLineColor(kPink - 3);    GPFL120.SetMarkerColor(kPink - 3);
   GPFL128.SetLineColor(kYellow - 3);  GPFL128.SetMarkerColor(kYellow - 3);
   GPFL140.SetLineColor(kGreen - 3);   GPFL140.SetMarkerColor(kGreen - 3);
   GPFL160.SetLineColor(kRed + 3);     GPFL160.SetMarkerColor(kRed + 3);
   GPF30.SetLineColor(kBlack);         GPF30.SetMarkerColor(kBlack);
   GPF50.SetLineColor(kPink - 3);      GPF50.SetMarkerColor(kPink - 3);
   GPF80.SetLineColor(kYellow - 3);    GPF80.SetMarkerColor(kYellow - 3);
   GPF100.SetLineColor(kGreen - 3);    GPF100.SetMarkerColor(kGreen - 3);
   GPF120.SetLineColor(kRed + 3);      GPF120.SetMarkerColor(kRed + 3);
   
   GPFFWDL120.SetLineColor(kBlack);        GPFFWDL120.SetMarkerColor(kBlack);
   GPFFWDL135.SetLineColor(kGreen - 3);    GPFFWDL135.SetMarkerColor(kGreen - 3);
   GPFFWDL140.SetLineColor(kPink - 3);     GPFFWDL140.SetMarkerColor(kPink - 3);
   GPFFWDL150.SetLineColor(kBlue - 3);     GPFFWDL150.SetMarkerColor(kBlue - 3);
   GPFFWDL160.SetLineColor(kYellow - 3);   GPFFWDL160.SetMarkerColor(kYellow - 3);
   
   GPFFWD30.SetLineColor(kBlack);        GPFFWD30.SetMarkerColor(kBlack);
   GPFFWD50.SetLineColor(kGreen - 3);    GPFFWD50.SetMarkerColor(kGreen - 3);
   GPFFWD60.SetLineColor(kYellow - 3);   GPFFWD60.SetMarkerColor(kYellow - 3);
   GPFFWD70.SetLineColor(kBlue - 3);     GPFFWD70.SetMarkerColor(kBlue - 3);
   GPFFWD80.SetLineColor(kRed + 3);      GPFFWD80.SetMarkerColor(kRed + 3);
   
   TCanvas C;

   TH2D HWorld1("HWorld1", ";Raw Calo Jet PT;Efficiency", 100, 10, 150, 100, 0.0, 1.1);
   HWorld1.SetStats(0);

   HWorld1.Draw("axis");
   GCalo30.Draw("p");
   GCalo40.Draw("p");
   GCalo50.Draw("p");
   GCalo80.Draw("p");
   GCalo100.Draw("p");
   GCalo120.Draw("p");

   TLegend Legend1(0.6, 0.15, 0.85, 0.5);
   Legend1.SetTextSize(0.035);
   Legend1.SetTextFont(42);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(&GCalo30, "Calo 30", "lp");
   Legend1.AddEntry(&GCalo40, "Calo 40", "lp");
   Legend1.AddEntry(&GCalo50, "Calo 50", "lp");
   Legend1.AddEntry(&GCalo80, "Calo 80", "lp");
   Legend1.AddEntry(&GCalo100, "Calo 100", "lp");
   Legend1.AddEntry(&GCalo120, "Calo 120", "lp");
   Legend1.Draw();

   PdfFile.AddCanvas(C);

   TH2D HWorld2("HWorld2", ";Raw PF Jet PT;Efficiency", 100, 10, 200, 100, 0.0, 1.1);
   HWorld2.SetStats(0);
   
   HWorld2.Draw("axis");
   GPF30.Draw("p");
   GPF50.Draw("p");
   GPF80.Draw("p");
   GPF100.Draw("p");
   GPF120.Draw("p");

   TLegend Legend2(0.6, 0.15, 0.85, 0.5);
   Legend2.SetTextSize(0.035);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&GPF30, "PF 30", "lp");
   Legend2.AddEntry(&GPF50, "PF 50", "lp");
   Legend2.AddEntry(&GPF80, "PF 80", "lp");
   Legend2.AddEntry(&GPF100, "PF 100", "lp");
   Legend2.AddEntry(&GPF120, "PF 120", "lp");
   Legend2.AddEntry("", "", "");
   Legend2.Draw();

   PdfFile.AddCanvas(C);

   TH2D HWorld3("HWorld3", ";Raw PF Jet PT;Efficiency", 100, 10, 100, 100, 0.0, 1.1);
   HWorld3.SetStats(0);
   
   HWorld3.Draw("axis");
   GPFFWDL120.Draw("p");
   GPFFWDL135.Draw("p");
   GPFFWDL140.Draw("p");
   GPFFWDL150.Draw("p");
   GPFFWDL160.Draw("p");

   TLegend Legend3(0.6, 0.15, 0.85, 0.5);
   Legend3.SetTextSize(0.035);
   Legend3.SetTextFont(42);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(&GPFFWDL120, "L1 20 FWD", "lp");
   Legend3.AddEntry(&GPFFWDL135, "L1 35 FWD", "lp");
   Legend3.AddEntry(&GPFFWDL140, "L1 40 FWD", "lp");
   Legend3.AddEntry(&GPFFWDL150, "L1 50 FWD", "lp");
   Legend3.AddEntry(&GPFFWDL160, "L1 60 FWD", "lp");
   Legend3.AddEntry("", "", "");
   Legend3.Draw();

   PdfFile.AddCanvas(C);
 
   TH2D HWorld4("HWorld4", ";Raw PF Jet PT;Efficiency", 100, 10, 100, 100, 0.0, 1.1);
   HWorld4.SetStats(0);
   
   HWorld4.Draw("axis");
   GPFFWD30.Draw("p");
   GPFFWD50.Draw("p");
   GPFFWD60.Draw("p");
   GPFFWD70.Draw("p");
   GPFFWD80.Draw("p");

   TLegend Legend4(0.6, 0.15, 0.85, 0.5);
   Legend4.SetTextSize(0.035);
   Legend4.SetTextFont(42);
   Legend4.SetFillStyle(0);
   Legend4.AddEntry(&GPFFWD30, "PF 30 FWD", "lp");
   Legend4.AddEntry(&GPFFWD50, "PF 50 FWD", "lp");
   Legend4.AddEntry(&GPFFWD60, "PF 60 FWD", "lp");
   Legend4.AddEntry(&GPFFWD70, "PF 70 FWD", "lp");
   Legend4.AddEntry(&GPFFWD80, "PF 80 FWD", "lp");
   Legend4.AddEntry("", "", "");
   Legend4.Draw();

   PdfFile.AddCanvas(C);

   TH2D HWorld5("HWorld5", ";Raw PF Jet PT;Efficiency", 100, 10, 100, 100, 0.0, 1.1);
   HWorld5.SetStats(0);
   
   HWorld5.Draw("axis");
   GPFL116.Draw("p");
   GPFL120.Draw("p");
   GPFL128.Draw("p");
   GPFL140.Draw("p");
   GPFL160.Draw("p");
   
   TLegend Legend5(0.6, 0.15, 0.85, 0.5);
   Legend5.SetTextSize(0.035);
   Legend5.SetTextFont(42);
   Legend5.SetFillStyle(0);
   Legend5.AddEntry(&GPFL116, "L1 16", "lp");
   Legend5.AddEntry(&GPFL120, "L1 20", "lp");
   Legend5.AddEntry(&GPFL128, "L1 28", "lp");
   Legend5.AddEntry(&GPFL140, "L1 40", "lp");
   Legend5.AddEntry(&GPFL160, "L1 60", "lp");
   Legend5.AddEntry("", "", "");
   Legend5.Draw();

   PdfFile.AddCanvas(C);

   TH2D HWorld6("HWorld6", ";Raw Calo Jet PT;Efficiency", 100, 10, 100, 100, 0.0, 1.1);
   HWorld6.SetStats(0);
   
   HWorld6.Draw("axis");
   GCaloL116.Draw("p");
   GCaloL120.Draw("p");
   GCaloL128.Draw("p");
   GCaloL140.Draw("p");
   GCaloL160.Draw("p");
   
   TLegend Legend6(0.6, 0.15, 0.85, 0.5);
   Legend6.SetTextSize(0.035);
   Legend6.SetTextFont(42);
   Legend6.SetFillStyle(0);
   Legend6.AddEntry(&GCaloL116, "L1 16", "lp");
   Legend6.AddEntry(&GCaloL120, "L1 20", "lp");
   Legend6.AddEntry(&GCaloL128, "L1 28", "lp");
   Legend6.AddEntry(&GCaloL140, "L1 40", "lp");
   Legend6.AddEntry(&GCaloL160, "L1 60", "lp");
   Legend6.AddEntry("", "", "");
   Legend6.Draw();

   PdfFile.AddCanvas(C);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}







