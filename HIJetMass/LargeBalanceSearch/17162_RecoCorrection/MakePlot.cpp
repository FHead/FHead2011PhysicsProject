#include <iostream>
using namespace std;

#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void BasicSetting(TProfile &P1, TProfile &P2, TProfile &P3, TProfile &P4, TProfile &P5);
void BasicSetting(TH1D &P1, TH1D &P2, TH1D &P3, TH1D &P4, TH1D &P5);
void BasicSetting(TH1D &P2, TH1D &P3, TH1D &P4, TH1D &P5);
void AddLatex();
void AddLabel(string Label);
void AddLabel(vector<string> Label);
void Division(TProfile P1, TProfile P2, TH1D &H);
vector<string> ToVector(int N, string S1 = "", string S2 = "", string S3 = "");

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("SomePlots.pdf");
   PdfFile.AddTextPage("Plots to check correction");

   TFile F1("LocalResult/AA6DijetCymbalV2Slimmed.root");
   TFile F2("LocalResult/PP6DijetSlimmed.root");
   TFile F3("LocalResult/PP6DijetHIRecoSlimmed.root");
   TFile F4("LocalResult/PP8DijetSlimmed.root");
   TFile F5("LocalResult/PP8DijetSlimmedLarge.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   TTree *T3 = (TTree *)F3.Get("Tree");
   TTree *T4 = (TTree *)F4.Get("Tree");
   TTree *T5 = (TTree *)F5.Get("Tree");

   string BaselineString = "MCWeight * (PTHat > 100 && JetPT > 150 && abs(JetEta) < 1.3)";
   T1->SetAlias("Baseline", BaselineString.c_str());
   T2->SetAlias("Baseline", BaselineString.c_str());
   T3->SetAlias("Baseline", BaselineString.c_str());
   T4->SetAlias("Baseline", BaselineString.c_str());
   T5->SetAlias("Baseline", BaselineString.c_str());

   T2->SetAlias("RhoWeight", "((0.449674+0.000656226*Rho-0.000000694354*Rho*Rho)/(0.474994+0.000630973*Rho-0.00000116451*Rho*Rho))");
   T3->SetAlias("RhoWeight", "((0.449674+0.000656226*Rho-0.000000694354*Rho*Rho)/(0.474994+0.000630973*Rho-0.00000116451*Rho*Rho))");
   T4->SetAlias("RhoWeight", "((0.449674+0.000656226*Rho-0.000000694354*Rho*Rho)/(0.474994+0.000630973*Rho-0.00000116451*Rho*Rho))");
   T5->SetAlias("RhoWeight", "((0.449674+0.000656226*Rho-0.000000694354*Rho*Rho)/(0.474994+0.000630973*Rho-0.00000116451*Rho*Rho))");

   TCanvas Canvas;

   {
      TH1D P1("P1", ";#hat{p}_{T};", 100, 100, 600);
      TH1D P2("P2", ";#hat{p}_{T};", 100, 100, 600);
      TH1D P3("P3", ";#hat{p}_{T};", 100, 100, 600);
      TH1D P4("P4", ";#hat{p}_{T};", 100, 100, 600);
      TH1D P5("P5", ";#hat{p}_{T};", 100, 100, 600);

      T1->Draw("PTHat>>P1", "Baseline", "");
      T2->Draw("PTHat>>P2", "Baseline", "same");
      T3->Draw("PTHat>>P3", "Baseline", "same");
      T4->Draw("PTHat>>P4", "Baseline", "same");
      T5->Draw("PTHat>>P5", "Baseline", "same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(1, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);

      T1->Draw("DR>0.1:Rho>>P1", "Baseline", "prof");
      T2->Draw("DR>0.1:Rho>>P2", "Baseline", "prof same");
      T3->Draw("DR>0.1:Rho>>P3", "Baseline", "prof same");
      T4->Draw("DR>0.1:Rho>>P4", "Baseline", "prof same");
      T5->Draw("DR>0.1:Rho>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(1, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(1, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);

      T1->Draw("DR>0.1:Rho>>P1", "Baseline", "prof");
      T2->Draw("(DR>0.1)*(1.01-DR*0.075):Rho>>P2", "Baseline", "prof same");
      T3->Draw("(DR>0.1)*(1.01-DR*0.075):Rho>>P3", "Baseline", "prof same");
      T4->Draw("(DR>0.1)*(1.01-DR*0.075):Rho>>P4", "Baseline", "prof same");
      T5->Draw("(DR>0.1)*(1.01-DR*0.075):Rho>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR Corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR Corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);

      T1->Draw("DR>0.1:Rho>>P1", "Baseline", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:Rho>>P2", "Baseline", "prof same");
      T3->Draw("(DR>0.1):Rho>>P3", "Baseline", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:Rho>>P4", "Baseline", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:Rho>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);

      T1->Draw("DR>0.1:Rho>>P1", "Baseline * (JetPT > 300)", "prof");
      T2->Draw("DR>0.1:Rho>>P2", "Baseline * (JetPT > 300)", "prof same");
      T3->Draw("DR>0.1:Rho>>P3", "Baseline * (JetPT > 300)", "prof same");
      T4->Draw("DR>0.1:Rho>>P4", "Baseline * (JetPT > 300)", "prof same");
      T5->Draw("DR>0.1:Rho>>P5", "Baseline * (JetPT > 300)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 300, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 300, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 23, Bins);

      T1->Draw("(DR>0.1):Rho>>P1", "Baseline * (JetPT > 300)", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:Rho>>P2", "Baseline * (JetPT > 300)", "prof same");
      T3->Draw("(DR>0.1):Rho>>P3", "Baseline * (JetPT > 300)", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:Rho>>P4", "Baseline * (JetPT > 300)", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:Rho>>P5", "Baseline * (JetPT > 300)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 300, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 300, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      double Bins[23+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200,
         220, 250, 275, 300, 320};

      TProfile P1("P1", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.2)", 23, Bins);
      TProfile P2("P2", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.2)", 23, Bins);
      TProfile P3("P3", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.2)", 23, Bins);
      TProfile P4("P4", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.2)", 23, Bins);
      TProfile P5("P5", ";#rho;P(#DeltaR^{z_{cut} = 0.1} > 0.2)", 23, Bins);

      T1->Draw("DR>0.2:Rho>>P1", "Baseline", "prof");
      T2->Draw("DR>0.2:Rho>>P2", "Baseline", "prof same");
      T3->Draw("DR>0.2:Rho>>P3", "Baseline", "prof same");
      T4->Draw("DR>0.2:Rho>>P4", "Baseline", "prof same");
      T5->Draw("DR>0.2:Rho>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
         
      TH1D H2("H2", ";#rho;Ratio", 23, Bins);
      TH1D H3("H3", ";#rho;Ratio", 23, Bins);
      TH1D H4("H4", ";#rho;Ratio", 23, Bins);
      TH1D H5("H5", ";#rho;Ratio", 23, Bins);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P2("P2", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P3("P3", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P4("P4", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P5("P5", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);

      T1->Draw("DR>0.1:JetPT>>P1", "Baseline", "prof");
      T2->Draw("DR>0.1:JetPT>>P2", "Baseline", "prof same");
      T3->Draw("DR>0.1:JetPT>>P3", "Baseline", "prof same");
      T4->Draw("DR>0.1:JetPT>>P4", "Baseline", "prof same");
      T5->Draw("DR>0.1:JetPT>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H3("H3", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H4("H4", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H5("H5", ";Jet p_{T};Ratio", 50, 150, 1000);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", ""));

      PdfFile.AddCanvas(Canvas);
   }
   
   {
      TProfile P1("P1", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P2("P2", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P3("P3", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P4("P4", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);
      TProfile P5("P5", ";Jet p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 150, 1000);

      T1->Draw("(DR>0.1):JetPT>>P1", "Baseline", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:JetPT>>P2", "Baseline", "prof same");
      T3->Draw("(DR>0.1):JetPT>>P3", "Baseline", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:JetPT>>P4", "Baseline", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:JetPT>>P5", "Baseline", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H3("H3", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H4("H4", ";Jet p_{T};Ratio", 50, 150, 1000);
      TH1D H5("H5", ";Jet p_{T};Ratio", 50, 150, 1000);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.5);
      H2.SetMaximum(1.5);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P2("P2", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P3("P3", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P4("P4", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P5("P5", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);

      T1->Draw("DR>0.1:Mass/JetPT>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("DR>0.1:Mass/JetPT>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("DR>0.1:Mass/JetPT>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("DR>0.1:Mass/JetPT>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("DR>0.1:Mass/JetPT>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H3("H3", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H4("H4", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H5("H5", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.95);
      H2.SetMaximum(1.05);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P2("P2", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P3("P3", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P4("P4", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);
      TProfile P5("P5", ";Jet SD Mass / p_{T};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.0, 0.3);

      T1->Draw("DR>0.1:Mass/JetPT>>P1", "Baseline * (Centrality < 0.1 && DR > 0)", "prof");
      T2->Draw("DR>0.1:Mass/JetPT>>P2", "Baseline * (Centrality < 0.1 && DR > 0)", "prof same");
      T3->Draw("DR>0.1:Mass/JetPT>>P3", "Baseline * (Centrality < 0.1 && DR > 0)", "prof same");
      T4->Draw("DR>0.1:Mass/JetPT>>P4", "Baseline * (Centrality < 0.1 && DR > 0)", "prof same");
      T5->Draw("DR>0.1:Mass/JetPT>>P5", "Baseline * (Centrality < 0.1 && DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H3("H3", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H4("H4", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);
      TH1D H5("H5", ";SD Mass / Jet p_{T};Ratio", 50, 0.0, 0.3);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.95);
      H2.SetMaximum(1.05);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P2("P2", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P3("P3", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P4("P4", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P5("P5", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);

      T1->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H3("H3", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H4("H4", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H5("H5", ";z_{G};Ratio", 10, 0.0, 0.5);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P2("P2", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P3("P3", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P4("P4", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P5("P5", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);

      T1->Draw("(DR>0.1):SJ2PT/(SJ1PT+SJ2PT)>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("(DR>0.1):SJ2PT/(SJ1PT+SJ2PT)>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H3("H3", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H4("H4", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H5("H5", ";z_{G};Ratio", 10, 0.0, 0.5);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P2("P2", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P3("P3", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P4("P4", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P5("P5", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);

      T1->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P1", "Baseline * (DR > 0 && Centrality < 0.1)", "prof");
      T2->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P2", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T3->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P3", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T4->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P4", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T5->Draw("DR>0.1:SJ2PT/(SJ1PT+SJ2PT)>>P5", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H3("H3", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H4("H4", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H5("H5", ";z_{G};Ratio", 10, 0.0, 0.5);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P2("P2", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P3("P3", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P4("P4", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);
      TProfile P5("P5", ";z_{G};P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 10, 0.00, 0.50);

      T1->Draw("(DR>0.1):SJ2PT/(SJ1PT+SJ2PT)>>P1", "Baseline * (DR > 0 && Centrality < 0.1)", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P2", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T3->Draw("(DR>0.1):SJ2PT/(SJ1PT+SJ2PT)>>P3", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P4", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:SJ2PT/(SJ1PT+SJ2PT)>>P5", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H3("H3", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H4("H4", ";z_{G};Ratio", 10, 0.0, 0.5);
      TH1D H5("H5", ";z_{G};Ratio", 10, 0.0, 0.5);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P2("P2", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P3("P3", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P4("P4", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P5("P5", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);

      T1->Draw("DR>0.1:SDPT/JetPT>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("DR>0.1:SDPT/JetPT>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("DR>0.1:SDPT/JetPT>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("DR>0.1:SDPT/JetPT>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("DR>0.1:SDPT/JetPT>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H3("H3", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H4("H4", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H5("H5", ";PTPT;Ratio", 50, 0.6, 1.0);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 20, 0.6, 1.0);
      TProfile P2("P2", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 20, 0.6, 1.0);
      TProfile P3("P3", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 20, 0.6, 1.0);
      TProfile P4("P4", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 20, 0.6, 1.0);
      TProfile P5("P5", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 20, 0.6, 1.0);

      T1->Draw("DR>0.1:SDPT/JetPT>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("DR>0.1:SDPT/JetPT>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("DR>0.1:SDPT/JetPT>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("DR>0.1:SDPT/JetPT>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("DR>0.1:SDPT/JetPT>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";PTPT;Ratio", 20, 0.6, 1.0);
      TH1D H3("H3", ";PTPT;Ratio", 20, 0.6, 1.0);
      TH1D H4("H4", ";PTPT;Ratio", 20, 0.6, 1.0);
      TH1D H5("H5", ";PTPT;Ratio", 20, 0.6, 1.0);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P2("P2", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P3("P3", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P4("P4", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P5("P5", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);

      T1->Draw("DR>0.1:SDPT/JetPT>>P1", "Baseline * (DR > 0)", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:SDPT/JetPT>>P2", "Baseline * (DR > 0)", "prof same");
      T3->Draw("(DR>0.1):SDPT/JetPT>>P3", "Baseline * (DR > 0)", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:SDPT/JetPT>>P4", "Baseline * (DR > 0)", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:SDPT/JetPT>>P5", "Baseline * (DR > 0)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H3("H3", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H4("H4", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H5("H5", ";PTPT;Ratio", 50, 0.6, 1.0);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P2("P2", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P3("P3", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P4("P4", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P5("P5", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);

      T1->Draw("DR>0.1:(SJ1PT+SJ2PT)/JetPT>>P1", "Baseline * (DR > 0 && Centrality < 0.1)", "prof");
      T2->Draw("DR>0.1:(SJ1PT+SJ2PT)/JetPT>>P2", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T3->Draw("DR>0.1:(SJ1PT+SJ2PT)/JetPT>>P3", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T4->Draw("DR>0.1:(SJ1PT+SJ2PT)/JetPT>>P4", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T5->Draw("DR>0.1:(SJ1PT+SJ2PT)/JetPT>>P5", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H3("H3", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H4("H4", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H5("H5", ";PTPT;Ratio", 50, 0.6, 1.0);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%"));

      PdfFile.AddCanvas(Canvas);
   }

   {
      TProfile P1("P1", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P2("P2", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P3("P3", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P4("P4", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);
      TProfile P5("P5", ";PTPT;P(#DeltaR^{z_{cut} = 0.1} > 0.1)", 50, 0.6, 1.0);

      T1->Draw("(DR>0.1):(SJ1PT+SJ2PT)/JetPT>>P1", "Baseline * (DR > 0 && Centrality < 0.1)", "prof");
      T2->Draw("(DR>0.1)*RhoWeight:(SJ1PT+SJ2PT)/JetPT>>P2", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T3->Draw("(DR>0.1):(SJ1PT+SJ2PT)/JetPT>>P3", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T4->Draw("(DR>0.1)*RhoWeight:(SJ1PT+SJ2PT)/JetPT>>P4", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");
      T5->Draw("(DR>0.1)*RhoWeight:(SJ1PT+SJ2PT)/JetPT>>P5", "Baseline * (DR > 0 && Centrality < 0.1)", "prof same");

      BasicSetting(P1, P2, P3, P4, P5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
      
      TH1D H2("H2", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H3("H3", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H4("H4", ";PTPT;Ratio", 50, 0.6, 1.0);
      TH1D H5("H5", ";PTPT;Ratio", 50, 0.6, 1.0);

      Division(P2, P1, H2);
      Division(P3, P1, H3);
      Division(P4, P3, H4);
      Division(P5, P3, H5);

      H2.SetMinimum(0.75);
      H2.SetMaximum(1.25);

      H2.Draw();
      H3.Draw("same");
      H4.Draw("same");
      H5.Draw("same");

      BasicSetting(H2, H3, H4, H5);
      AddLatex();
      AddLabel(ToVector(2, "Jet PT > 150, #hat{p}_{T} > 100, Jet |#eta| < 1.3", "#DeltaR > 0, Centrality < 10%, #rho corrected"));

      PdfFile.AddCanvas(Canvas);
   }


   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void BasicSetting(TProfile &P1, TProfile &P2, TProfile &P3, TProfile &P4, TProfile &P5)
{
   int Colors[] = {kBlack, kRed, kBlue, kGreen, kGreen + 3};

   P1.SetMinimum(0);
   P1.SetMaximum(1);

   P1.SetStats(0);
   P2.SetStats(0);
   P3.SetStats(0);
   P4.SetStats(0);
   P5.SetStats(0);

   P1.SetLineWidth(2);
   P2.SetLineWidth(2);
   P3.SetLineWidth(2);
   P4.SetLineWidth(2);
   P5.SetLineWidth(2);
   
   P1.SetMarkerStyle(20);
   P2.SetMarkerStyle(20);
   P3.SetMarkerStyle(20);
   P4.SetMarkerStyle(20);
   P5.SetMarkerStyle(20);

   P1.SetLineColor(Colors[0]);
   P2.SetLineColor(Colors[1]);
   P3.SetLineColor(Colors[2]);
   P4.SetLineColor(Colors[3]);
   P5.SetLineColor(Colors[4]);
   
   P1.SetMarkerColor(Colors[0]);
   P2.SetMarkerColor(Colors[1]);
   P3.SetMarkerColor(Colors[2]);
   P4.SetMarkerColor(Colors[3]);
   P5.SetMarkerColor(Colors[4]);
}

void BasicSetting(TH1D &P1, TH1D &P2, TH1D &P3, TH1D &P4, TH1D &P5)
{
   int Colors[] = {kBlack, kRed, kBlue, kGreen, kGreen + 3};

   P1.SetStats(0);
   P2.SetStats(0);
   P3.SetStats(0);
   P4.SetStats(0);
   P5.SetStats(0);

   P1.SetLineWidth(2);
   P2.SetLineWidth(2);
   P3.SetLineWidth(2);
   P4.SetLineWidth(2);
   P5.SetLineWidth(2);
   
   P1.SetMarkerStyle(20);
   P2.SetMarkerStyle(20);
   P3.SetMarkerStyle(20);
   P4.SetMarkerStyle(20);
   P5.SetMarkerStyle(20);

   P1.SetLineColor(Colors[0]);
   P2.SetLineColor(Colors[1]);
   P3.SetLineColor(Colors[2]);
   P4.SetLineColor(Colors[3]);
   P5.SetLineColor(Colors[4]);
   
   P1.SetMarkerColor(Colors[0]);
   P2.SetMarkerColor(Colors[1]);
   P3.SetMarkerColor(Colors[2]);
   P4.SetMarkerColor(Colors[3]);
   P5.SetMarkerColor(Colors[4]);
}

void BasicSetting(TH1D &P2, TH1D &P3, TH1D &P4, TH1D &P5)
{
   TH1D P1("htemp", "", 1, 0, 1);   // dummy
   BasicSetting(P1, P2, P3, P4, P5);
}

void AddLatex()
{
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(30);
   Latex.SetNDC();

   string LegendString1 = "Embedded:", LegendString2 = "Smeared:";
   LegendString1 = LegendString1 + " #color[1]{PYTHIA6}";
   LegendString2 = LegendString2 + " #color[632]{PYTHIA6 (pp)}";
   LegendString2 = LegendString2 + " #color[600]{PYTHIA8 (HI)}";
   LegendString2 = LegendString2 + " #color[416]{PYTHIA8 (pp)}";
   LegendString2 = LegendString2 + " #color[419]{PYTHIA8 (pp, inflated)}";

   Latex.DrawLatex(0.85, 0.935, LegendString2.c_str());
   Latex.DrawLatex(0.85, 0.910, LegendString1.c_str());
}

void Division(TProfile P1, TProfile P2, TH1D &H)
{
   for(int i = 1; i <= P1.GetNbinsX(); i++)
   {
      double V1 = P1.GetBinContent(i);
      double V2 = P2.GetBinContent(i);
      double E1 = P1.GetBinError(i);
      double E2 = P2.GetBinError(i);

      if(V2 > 0)
      {
         H.SetBinContent(i, V1 / V2);
         H.SetBinError(i, V1 / V2 * sqrt(E1 * E1 / V1 / V1 + E2 * E2 / V2 / V2));
      }
      else
      {
         H.SetBinContent(i, 0);
         H.SetBinError(i, 0);
      }
   }
}

void AddLabel(string Label)
{
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(30);
   Latex.SetNDC();

   Latex.DrawLatex(0.83, 0.85, Label.c_str());
}

void AddLabel(vector<string> Label)
{
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(30);
   Latex.SetNDC();

   for(int i = 0; i < (int)Label.size(); i++)
      Latex.DrawLatex(0.83, 0.85 - 0.025 * i, Label[i].c_str());
}

vector<string> ToVector(int N, string S1, string S2, string S3)
{
   vector<string> Result;

   if(N > 0)   Result.push_back(S1);
   if(N > 1)   Result.push_back(S2);
   if(N > 2)   Result.push_back(S3);

   return Result;
}




