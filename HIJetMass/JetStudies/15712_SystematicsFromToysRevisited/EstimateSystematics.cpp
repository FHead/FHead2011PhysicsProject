#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"

#define BIN 20

int main(int argc, char *argv[]);
double GetFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);
pair<double, double> GetCentralFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, double Left, double Right);
void GetSystematics(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, double Left, double Right, TGraphAsymmErrors &G);
void SetAlias(TTree *Tree);
void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);

int main(int argc, char *argv[])
{
   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile Type Tag Left Right" << endl;
      return -1;
   }

   char *BaseFile = argv[1];
   char *ModifiedFile = argv[2];
   string Type = argv[3];
   char *Tag = argv[4];
   double Left = atof(argv[5]);
   double Right = atof(argv[6]);

   SetThesisStyle();

   PdfFileHelper PdfFile(string("Systematics_") + Tag + ".pdf");
   PdfFile.AddTextPage("Systematics");

   TFile F1(BaseFile);
   TFile F2(ModifiedFile);

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   SetAlias(T1);
   SetAlias(T2);

   TFile OutputFile((string("OutputFile_") + Tag + ".root").c_str(), "RECREATE");

   TH1D HNominal_P0("HNominal_P0", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P1("HNominal_P1", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P2("HNominal_P2", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P3("HNominal_P3", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P4("HNominal_P4", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P5("HNominal_P5", ";mass/pt;a.u.", BIN, 0, 0.4);

   TH1D HModified_P0("HModified_P0", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P1("HModified_P1", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P2("HModified_P2", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P3("HModified_P3", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P4("HModified_P4", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P5("HModified_P5", ";mass/pt;a.u.", BIN, 0, 0.4);

   T1->SetAlias("ExcessPT", "((TotalPT - Rho * 0.8 * 0.8 * 3.1415926535)*0.25)");
   T1->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*17.2*17.2)) / exp(-ExcessPT*ExcessPT/(2*21.4*21.4)))");
   T2->SetAlias("ExcessPT", "((TotalPT - Rho * 0.8 * 0.8 * 3.1415926535)*0.25)");
   T2->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*17.2*17.2)) / exp(-ExcessPT*ExcessPT/(2*21.4*21.4)))");

   T1->SetAlias("Baseline", "MCWeight * SmearWeight * (JetShift < 0.2 && NewJetDR2 > 0.1)");
   T2->SetAlias("Baseline", "MCWeight * SmearWeight * (JetShift < 0.2 && NewJetDR2 > 0.1)");

   if(Type == "Normal")
   {
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500)");

      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500)");
   }
   if(Type == "PT")
   {
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500)");

      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "Baseline * (JetPT*1.1 > 120 && JetPT*1.1 < 140)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "Baseline * (JetPT*1.1 > 140 && JetPT*1.1 < 160)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "Baseline * (JetPT*1.1 > 160 && JetPT*1.1 < 180)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "Baseline * (JetPT*1.1 > 180 && JetPT*1.1 < 200)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "Baseline * (JetPT*1.1 > 200 && JetPT*1.1 < 300)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "Baseline * (JetPT*1.1 > 300 && JetPT*1.1 < 500)");
   }
   if(Type == "Eta")
   {
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140) * (1 + (abs(JetEta) > 0.5))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160) * (1 + (abs(JetEta) > 0.5))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180) * (1 + (abs(JetEta) > 0.5))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200) * (1 + (abs(JetEta) > 0.5))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300) * (1 + (abs(JetEta) > 0.5))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500) * (1 + (abs(JetEta) > 0.5))");

      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140) * (1 + (abs(JetEta) < 0.5))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160) * (1 + (abs(JetEta) < 0.5))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180) * (1 + (abs(JetEta) < 0.5))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200) * (1 + (abs(JetEta) < 0.5))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300) * (1 + (abs(JetEta) < 0.5))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500) * (1 + (abs(JetEta) < 0.5))");
   }
   if(Type == "JER")
   {
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300)");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500)");

      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "Baseline * (JetPT*Smear > 120 && JetPT*Smear < 140)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "Baseline * (JetPT*Smear > 140 && JetPT*Smear < 160)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "Baseline * (JetPT*Smear > 160 && JetPT*Smear < 180)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "Baseline * (JetPT*Smear > 180 && JetPT*Smear < 200)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "Baseline * (JetPT*Smear > 200 && JetPT*Smear < 300)");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "Baseline * (JetPT*Smear > 300 && JetPT*Smear < 500)");
   }
   if(Type == "Smear")
   {
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "Baseline * (NewJetPT > 120 && NewJetPT < 140))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "Baseline * (NewJetPT > 140 && NewJetPT < 160))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "Baseline * (NewJetPT > 160 && NewJetPT < 180))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "Baseline * (NewJetPT > 180 && NewJetPT < 200))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "Baseline * (NewJetPT > 200 && NewJetPT < 300))");
      T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "Baseline * (NewJetPT > 300 && NewJetPT < 500))");

      T2->SetAlias("SmearChange", "(exp(-ExcessPT*ExcessPT/(2*17.2*17.2*0.9*0.9)) / exp(-ExcessPT*ExcessPT/(2*17.2*17.2)))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "Baseline * SmearChange * (NewJetPT > 120 && NewJetPT < 140))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "Baseline * SmearChange * (NewJetPT > 140 && NewJetPT < 160))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "Baseline * SmearChange * (NewJetPT > 160 && NewJetPT < 180))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "Baseline * SmearChange * (NewJetPT > 180 && NewJetPT < 200))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "Baseline * SmearChange * (NewJetPT > 200 && NewJetPT < 300))");
      T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "Baseline * SmearChange * (NewJetPT > 300 && NewJetPT < 500))");
   }

   HNominal_P0.Scale(1 / HNominal_P0.Integral());
   HNominal_P1.Scale(1 / HNominal_P1.Integral());
   HNominal_P2.Scale(1 / HNominal_P2.Integral());
   HNominal_P3.Scale(1 / HNominal_P3.Integral());
   HNominal_P4.Scale(1 / HNominal_P4.Integral());
   HNominal_P5.Scale(1 / HNominal_P5.Integral());

   PdfFile.AddPlot(HNominal_P0);
   PdfFile.AddPlot(HNominal_P1);
   PdfFile.AddPlot(HNominal_P2);
   PdfFile.AddPlot(HNominal_P3);
   PdfFile.AddPlot(HNominal_P4);
   PdfFile.AddPlot(HNominal_P5);

   HModified_P0.Scale(1 / HModified_P0.Integral());
   HModified_P1.Scale(1 / HModified_P1.Integral());
   HModified_P2.Scale(1 / HModified_P2.Integral());
   HModified_P3.Scale(1 / HModified_P3.Integral());
   HModified_P4.Scale(1 / HModified_P4.Integral());
   HModified_P5.Scale(1 / HModified_P5.Integral());

   PdfFile.AddPlot(HModified_P0);
   PdfFile.AddPlot(HModified_P1);
   PdfFile.AddPlot(HModified_P2);
   PdfFile.AddPlot(HModified_P3);
   PdfFile.AddPlot(HModified_P4);
   PdfFile.AddPlot(HModified_P5);

   AddPlots(PdfFile, HNominal_P0, HModified_P0);
   AddPlots(PdfFile, HNominal_P1, HModified_P1);
   AddPlots(PdfFile, HNominal_P2, HModified_P2);
   AddPlots(PdfFile, HNominal_P3, HModified_P3);
   AddPlots(PdfFile, HNominal_P4, HModified_P4);
   AddPlots(PdfFile, HNominal_P5, HModified_P5);

   TGraphAsymmErrors GRatio_C0_P0;   GRatio_C0_P0.SetNameTitle("GRatio_C0_P0", "");
   TGraphAsymmErrors GRatio_C0_P1;   GRatio_C0_P1.SetNameTitle("GRatio_C0_P1", "");
   TGraphAsymmErrors GRatio_C0_P2;   GRatio_C0_P2.SetNameTitle("GRatio_C0_P2", "");
   TGraphAsymmErrors GRatio_C0_P3;   GRatio_C0_P3.SetNameTitle("GRatio_C0_P3", "");
   TGraphAsymmErrors GRatio_C0_P4;   GRatio_C0_P4.SetNameTitle("GRatio_C0_P4", "");
   TGraphAsymmErrors GRatio_C0_P5;   GRatio_C0_P5.SetNameTitle("GRatio_C0_P5", "");
   TGraphAsymmErrors GRatio_C1_P0;   GRatio_C1_P0.SetNameTitle("GRatio_C1_P0", "");
   TGraphAsymmErrors GRatio_C1_P1;   GRatio_C1_P1.SetNameTitle("GRatio_C1_P1", "");
   TGraphAsymmErrors GRatio_C1_P2;   GRatio_C1_P2.SetNameTitle("GRatio_C1_P2", "");
   TGraphAsymmErrors GRatio_C1_P3;   GRatio_C1_P3.SetNameTitle("GRatio_C1_P3", "");
   TGraphAsymmErrors GRatio_C1_P4;   GRatio_C1_P4.SetNameTitle("GRatio_C1_P4", "");
   TGraphAsymmErrors GRatio_C1_P5;   GRatio_C1_P5.SetNameTitle("GRatio_C1_P5", "");
   TGraphAsymmErrors GRatio_C2_P0;   GRatio_C2_P0.SetNameTitle("GRatio_C2_P0", "");
   TGraphAsymmErrors GRatio_C2_P1;   GRatio_C2_P1.SetNameTitle("GRatio_C2_P1", "");
   TGraphAsymmErrors GRatio_C2_P2;   GRatio_C2_P2.SetNameTitle("GRatio_C2_P2", "");
   TGraphAsymmErrors GRatio_C2_P3;   GRatio_C2_P3.SetNameTitle("GRatio_C2_P3", "");
   TGraphAsymmErrors GRatio_C2_P4;   GRatio_C2_P4.SetNameTitle("GRatio_C2_P4", "");
   TGraphAsymmErrors GRatio_C2_P5;   GRatio_C2_P5.SetNameTitle("GRatio_C2_P5", "");
   TGraphAsymmErrors GRatio_C3_P0;   GRatio_C3_P0.SetNameTitle("GRatio_C3_P0", "");
   TGraphAsymmErrors GRatio_C3_P1;   GRatio_C3_P1.SetNameTitle("GRatio_C3_P1", "");
   TGraphAsymmErrors GRatio_C3_P2;   GRatio_C3_P2.SetNameTitle("GRatio_C3_P2", "");
   TGraphAsymmErrors GRatio_C3_P3;   GRatio_C3_P3.SetNameTitle("GRatio_C3_P3", "");
   TGraphAsymmErrors GRatio_C3_P4;   GRatio_C3_P4.SetNameTitle("GRatio_C3_P4", "");
   TGraphAsymmErrors GRatio_C3_P5;   GRatio_C3_P5.SetNameTitle("GRatio_C3_P5", "");
   TGraphAsymmErrors GRatio_C4_P0;   GRatio_C4_P0.SetNameTitle("GRatio_C4_P0", "");
   TGraphAsymmErrors GRatio_C4_P1;   GRatio_C4_P1.SetNameTitle("GRatio_C4_P1", "");
   TGraphAsymmErrors GRatio_C4_P2;   GRatio_C4_P2.SetNameTitle("GRatio_C4_P2", "");
   TGraphAsymmErrors GRatio_C4_P3;   GRatio_C4_P3.SetNameTitle("GRatio_C4_P3", "");
   TGraphAsymmErrors GRatio_C4_P4;   GRatio_C4_P4.SetNameTitle("GRatio_C4_P4", "");
   TGraphAsymmErrors GRatio_C4_P5;   GRatio_C4_P5.SetNameTitle("GRatio_C4_P5", "");

   GetSystematics(PdfFile, HNominal_P0, HModified_P0, Left, Right, GRatio_C0_P0);
   GetSystematics(PdfFile, HNominal_P1, HModified_P1, Left, Right, GRatio_C0_P1);
   GetSystematics(PdfFile, HNominal_P2, HModified_P2, Left, Right, GRatio_C0_P2);
   GetSystematics(PdfFile, HNominal_P3, HModified_P3, Left, Right, GRatio_C0_P3);
   GetSystematics(PdfFile, HNominal_P4, HModified_P4, Left, Right, GRatio_C0_P4);
   GetSystematics(PdfFile, HNominal_P5, HModified_P5, Left, Right, GRatio_C0_P5);
   GetSystematics(PdfFile, HNominal_P0, HModified_P0, Left, Right, GRatio_C1_P0);
   GetSystematics(PdfFile, HNominal_P1, HModified_P1, Left, Right, GRatio_C1_P1);
   GetSystematics(PdfFile, HNominal_P2, HModified_P2, Left, Right, GRatio_C1_P2);
   GetSystematics(PdfFile, HNominal_P3, HModified_P3, Left, Right, GRatio_C1_P3);
   GetSystematics(PdfFile, HNominal_P4, HModified_P4, Left, Right, GRatio_C1_P4);
   GetSystematics(PdfFile, HNominal_P5, HModified_P5, Left, Right, GRatio_C1_P5);
   GetSystematics(PdfFile, HNominal_P0, HModified_P0, Left, Right, GRatio_C2_P0);
   GetSystematics(PdfFile, HNominal_P1, HModified_P1, Left, Right, GRatio_C2_P1);
   GetSystematics(PdfFile, HNominal_P2, HModified_P2, Left, Right, GRatio_C2_P2);
   GetSystematics(PdfFile, HNominal_P3, HModified_P3, Left, Right, GRatio_C2_P3);
   GetSystematics(PdfFile, HNominal_P4, HModified_P4, Left, Right, GRatio_C2_P4);
   GetSystematics(PdfFile, HNominal_P5, HModified_P5, Left, Right, GRatio_C2_P5);
   GetSystematics(PdfFile, HNominal_P0, HModified_P0, Left, Right, GRatio_C3_P0);
   GetSystematics(PdfFile, HNominal_P1, HModified_P1, Left, Right, GRatio_C3_P1);
   GetSystematics(PdfFile, HNominal_P2, HModified_P2, Left, Right, GRatio_C3_P2);
   GetSystematics(PdfFile, HNominal_P3, HModified_P3, Left, Right, GRatio_C3_P3);
   GetSystematics(PdfFile, HNominal_P4, HModified_P4, Left, Right, GRatio_C3_P4);
   GetSystematics(PdfFile, HNominal_P5, HModified_P5, Left, Right, GRatio_C3_P5);
   GetSystematics(PdfFile, HNominal_P0, HModified_P0, Left, Right, GRatio_C4_P0);
   GetSystematics(PdfFile, HNominal_P1, HModified_P1, Left, Right, GRatio_C4_P1);
   GetSystematics(PdfFile, HNominal_P2, HModified_P2, Left, Right, GRatio_C4_P2);
   GetSystematics(PdfFile, HNominal_P3, HModified_P3, Left, Right, GRatio_C4_P3);
   GetSystematics(PdfFile, HNominal_P4, HModified_P4, Left, Right, GRatio_C4_P4);
   GetSystematics(PdfFile, HNominal_P5, HModified_P5, Left, Right, GRatio_C4_P5);

   GRatio_C0_P0.Write();
   GRatio_C0_P1.Write();
   GRatio_C0_P2.Write();
   GRatio_C0_P3.Write();
   GRatio_C0_P4.Write();
   GRatio_C0_P5.Write();
   GRatio_C1_P0.Write();
   GRatio_C1_P1.Write();
   GRatio_C1_P2.Write();
   GRatio_C1_P3.Write();
   GRatio_C1_P4.Write();
   GRatio_C1_P5.Write();
   GRatio_C2_P0.Write();
   GRatio_C2_P1.Write();
   GRatio_C2_P2.Write();
   GRatio_C2_P3.Write();
   GRatio_C2_P4.Write();
   GRatio_C2_P5.Write();
   GRatio_C3_P0.Write();
   GRatio_C3_P1.Write();
   GRatio_C3_P2.Write();
   GRatio_C3_P3.Write();
   GRatio_C3_P4.Write();
   GRatio_C3_P5.Write();
   GRatio_C4_P0.Write();
   GRatio_C4_P1.Write();
   GRatio_C4_P2.Write();
   GRatio_C4_P3.Write();
   GRatio_C4_P4.Write();
   GRatio_C4_P5.Write();

   PdfFile.AddPlot(GRatio_C0_P0);
   PdfFile.AddPlot(GRatio_C0_P1);
   PdfFile.AddPlot(GRatio_C0_P2);
   PdfFile.AddPlot(GRatio_C0_P3);
   PdfFile.AddPlot(GRatio_C0_P4);
   PdfFile.AddPlot(GRatio_C0_P5);

   OutputFile.Close();

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   TH1D HLogRatio("HLogRatio", "log(Ratio)", BIN, 0, 0.4);

   TH1D H("H", "H", 10000, -5, 5);

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V1 = H1.GetBinContent(i);
      double E1 = H1.GetBinError(i);
      double V2 = H2.GetBinContent(i);
      double E2 = H2.GetBinError(i);

      double LV = (log(V1) - log(V2)) / log(10);
      double LE = sqrt((E1 / V1) * (E1 / V1) + (E2 / V2) * (E2 / V2)) / log(10);

      cout << i << " " << V1 << " " << V2 << " " << LV << " " << LE << endl;

      if(V1 == 0 || V2 == 0)
         continue;

      HLogRatio.SetBinContent(i, LV);
      HLogRatio.SetBinError(i, LE);

      for(int j = 0; j < 10000; j++)
         H.Fill(DrawGaussian(LV, LE), 1 / LE / LE);
   }

   TF1 F("F", "gaus");
   H.Fit(&F);

   TGraph G1, G2;
   G1.SetPoint(0, 0,  F.GetParameter(2) * 1.00);
   G1.SetPoint(1, 1,  F.GetParameter(2) * 1.00);
   G2.SetPoint(0, 0, -F.GetParameter(2) * 1.00);
   G2.SetPoint(1, 1, -F.GetParameter(2) * 1.00);

   TCanvas C;

   HLogRatio.Draw();
   G1.Draw("same");
   G2.Draw("same");

   PdfFile.AddCanvas(C);

   PdfFile.AddPlot(H);

   return F.GetParameter(2) * 1.00;
}

pair<double, double> GetCentralFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, double Left, double Right)
{
   TH1D HLogRatio("HLogRatioX", "log(Ratio)", BIN, 0, 0.4);

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V1 = H1.GetBinContent(i);
      double E1 = H1.GetBinError(i);
      double V2 = H2.GetBinContent(i);
      double E2 = H2.GetBinError(i);

      double LV = (log(V1) - log(V2)) / log(10);
      double LE = sqrt((E1 / V1) * (E1 / V1) + (E2 / V2) * (E2 / V2)) / log(10);

      if(V1 == 0 || V2 == 0)
         continue;

      HLogRatio.SetBinContent(i, LV);
      HLogRatio.SetBinError(i, LE);
   }

   double Percentage = 0.65;

   int BinLeft = H1.FindBin(Left);
   int BinRight = H1.FindBin(Right);

   vector<double> Ratios;
   for(int i = BinLeft; i <= BinRight; i++)
   {
      double R = log(H1.GetBinContent(i) / H2.GetBinContent(i)) / log(10);
      if(R < 0)
         R = -R;
      Ratios.push_back(R);
   }
   sort(Ratios.begin(), Ratios.end());

   double Index = Ratios.size() * Percentage;
   int IntIndex = (int)Index;
   if(Index - IntIndex > 1e-8)
      IntIndex = IntIndex + 1;
   if(IntIndex >= Ratios.size())
      IntIndex = Ratios.size() - 1;
   double Size = Ratios[IntIndex];

   pair<double, double> Result(-Size, Size);

   TCanvas C;

   TGraph G1, G2;
   G1.SetPoint(0, 0, Result.first);
   G1.SetPoint(1, 1, Result.first);
   G2.SetPoint(0, 0, Result.second);
   G2.SetPoint(1, 1, Result.second);

   HLogRatio.Draw();
   G1.Draw("same");
   G2.Draw("same");

   PdfFile.AddCanvas(C);

   return Result;
}

void GetSystematics(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, double Left, double Right, TGraphAsymmErrors &G)
{
   TH1D HLogRatio("HLogRatio", "log(Ratio)", BIN, 0, 0.4);

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V1 = H1.GetBinContent(i);
      double V2 = H2.GetBinContent(i);
      double LV = (log(V1) - log(V2)) / log(10);

      if(V1 == 0 || V2 == 0)
         continue;

      HLogRatio.SetBinContent(i, LV);
   }

   double RMS = GetCentralFlatRMS(PdfFile, H1, H2, Left, Right).second;

   TH1D H("H", "", 160, 0, 0.4);

   int LeftBin = H.FindBin(Left);
   int RightBin = H.FindBin(Right);
   for(int i = LeftBin; i <= RightBin; i++)
      H.SetBinContent(i, RMS);

   for(int i = RightBin + 1; i <= 160; i++)
   {
      double R = HLogRatio.GetBinContent(HLogRatio.FindBin(H.GetBinCenter(i)));
      if(R < 0)
         R = -R;
      H.SetBinContent(i, max(H.GetBinContent(i - 1), R));
   }

   for(int i = LeftBin - 1; i >= 1; i--)
   {
      double R = HLogRatio.GetBinContent(HLogRatio.FindBin(H.GetBinCenter(i)));
      if(R < 0)
         R = -R;
      H.SetBinContent(i, max(H.GetBinContent(i + 1), R));
   }

   for(int i = 1; i <= 160; i++)
   {
      G.SetPoint(i - 1, H.GetBinCenter(i), 0);
      G.SetPointError(i - 1, 0, 0, H.GetBinContent(i), H.GetBinContent(i));
   }

   TCanvas C;

   G.SetFillColor(kCyan - 9);
   G.Draw("a3");
   HLogRatio.Draw("same");

   PdfFile.AddCanvas(C);
}

void SetAlias(TTree *Tree)
{
   if(Tree == NULL)
      return;
   Tree->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   Tree->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   Tree->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   Tree->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   Tree->SetAlias("rng", "sin(2*pi*rndm)*sqrt(-2*log(rndm))");
   Tree->SetAlias("Smear", "(rng*0.10+1)");
}

void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);
   H1.SetMarkerColor(kBlack);
   H2.SetMarkerColor(kRed);

   TCanvas C;

   H1.Draw();
   H2.Draw("same");

   PdfFile.AddCanvas(C);
}





