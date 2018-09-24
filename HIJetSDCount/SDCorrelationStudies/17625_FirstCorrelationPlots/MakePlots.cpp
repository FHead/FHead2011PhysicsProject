#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, int N, double Min, double Max, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double LogMin = -1);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string RecoilFileName = CL.Get("Recoil");
   string NoRecoilFileName = CL.Get("NoRecoil");
   string VacuumFileName = CL.Get("Vacuum");
   string OutputFileName = CL.Get("Output");

   TFile RecoilFile(RecoilFileName.c_str());
   TFile NoRecoilFile(NoRecoilFileName.c_str());
   TFile VacuumFile(VacuumFileName.c_str());

   TTree *T1 = (TTree *)RecoilFile.Get("jetTree");
   TTree *T2 = (TTree *)NoRecoilFile.Get("jetTree");
   TTree *T3 = (TTree *)VacuumFile.Get("jetTree");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jewel plots");

   vector<string> Explanations(10);
   Explanations[0] = "Jewel samples from the jet workshop directory:";
   Explanations[1] = "   jewel_NR_2.1_5.02_testfeb8 and";
   Explanations[2] = "   jewel_R_2.1_5.02_testfeb8";
   Explanations[3] = "";
   Explanations[4] = "   Recoil = blue";
   Explanations[5] = "   No-Recoil = green";
   Explanations[6] = "   Vacuum = red";
   Explanations[7] = "";
   Explanations[8] = "";
   Explanations[9] = "";
   PdfFile.AddTextPage(Explanations);

   T1->SetAlias("PT", "sigJetJewelPt");
   T2->SetAlias("PT", "sigJetPt");
   T3->SetAlias("PT", "sigJetPt");
   
   PdfFile.AddTextPage("Basic plots");
   AddPlot(PdfFile, 100, 0, 1000, "SigJet PT;PT",
      T1, "PT", "eventWeight[0]",
      T2, "PT", "eventWeight[0]",
      T3, "PT", "eventWeight[0]",
      1e-15);
   AddPlot(PdfFile, 100, 0, 1000, "max SigJet PT;PT",
      T1, "Max$(PT)", "eventWeight[0]",
      T2, "Max$(PT)", "eventWeight[0]",
      T3, "Max$(PT)", "eventWeight[0]",
      1e-15);
   AddPlot(PdfFile, 100, 200, 1000, "max SigJet PT;PT",
      T1, "Max$(PT)", "eventWeight[0]",
      T2, "Max$(PT)", "eventWeight[0]",
      T3, "Max$(PT)", "eventWeight[0]",
      1e-7);
   
   PdfFile.AddTextPage("SD (0.1, 0.0) plots");
   AddPlot(PdfFile, 2, 0, 2, "(0.1, 0.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
      T1, "sigJetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      T2, "sigJetSDdr12 <= 0",      "eventWeight[0] * (PT > 200)",
      T3, "sigJetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) ZG, PT > 200, DR > 0.1;zg",
      T1, "sigJetSDJewelzg", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)",
      T2, "sigJetSDZg",      "eventWeight[0] * (PT > 200 && sigJetSDdr12 > 0.1)",
      T3, "sigJetSDJewelzg", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) DR, PT > 200, DR > 0.0;DR",
      T1, "sigJetSDJeweldr12", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.0)",
      T2, "sigJetSDdr12",      "eventWeight[0] * (PT > 200 && sigJetSDdr12 > 0.0)",
      T3, "sigJetSDJeweldr12", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.0)");
   AddPlot(PdfFile, 40, 0, 0.5, "(0.1, 0.0) DR, PT > 200, DR > 0.1;DR",
      T1, "sigJetSDJeweldr12", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)",
      T2, "sigJetSDdr12",      "eventWeight[0] * (PT > 200 && sigJetSDdr12 > 0.1)",
      T3, "sigJetSDJeweldr12", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.3, "(0.1, 0.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sigJetSDJewelM/PT", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)",
      T2, "sigJetSDM/PT",      "eventWeight[0] * (PT > 200 && sigJetSDdr12 > 0.1)",
      T3, "sigJetSDJewelM/PT", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.3, "(0.1, 0.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sigJetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)",
      T2, "sigJetSDM/sigJetSDPt",           "eventWeight[0] * (PT > 200 && sigJetSDdr12 > 0.1)",
      T3, "sigJetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sigJetSDJeweldr12 > 0.1)");

   PdfFile.AddTextPage("SD (0.5, 1.5) plots");
   AddPlot(PdfFile, 2, 0, 2, "(0.5, 1.5) Completely killed percentage, PT > 200;(left) good (right) killed;%",
      T1, "sig1JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      T2, "sig1JetSDdr12 <= 0",      "eventWeight[0] * (PT > 200)",
      T3, "sig1JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) ZG, PT > 200, DR > 0.1;zg",
      T1, "sig1JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)",
      T2, "sig1JetSDZg",      "eventWeight[0] * (PT > 200 && sig1JetSDdr12 > 0.1)",
      T3, "sig1JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) DR, PT > 200, DR > 0.0;DR",
      T1, "sig1JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.0)",
      T2, "sig1JetSDdr12",      "eventWeight[0] * (PT > 200 && sig1JetSDdr12 > 0.0)",
      T3, "sig1JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.0)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.5, 1.5) DR, PT > 200, DR > 0.1;DR",
      T1, "sig1JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)",
      T2, "sig1JetSDdr12",      "eventWeight[0] * (PT > 200 && sig1JetSDdr12 > 0.1)",
      T3, "sig1JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.3, "(0.5, 1.5) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig1JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig1JetSDJeweldr12 > 0.1)",
      T2, "sig1JetSDM/PT",           "eventWeight[0] * (PT > 200 && sig1JetSDdr12 > 0.1)",
      T3, "sig1JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig1JetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.3, "(0.5, 1.5) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig1JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)",
      T2, "sig1JetSDM/sigJetSDPt",           "eventWeight[0] * (PT > 200 && sig1JetSDdr12 > 0.1)",
      T3, "sig1JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig1JetSDJeweldr12 > 0.1)");
   // AddPlot(PdfFile, 50, 0, 1000, "(0.5, 1.5) DR > 0.3;PT",
   //    T1, "PT", "eventWeight[0] * (sig1JetSDJeweldr12 > 0.3)",
   //    T2, "PT", "eventWeight[0] * (sig1JetSDdr12 > 0.3)",
   //    T3, "PT", "eventWeight[0] * (sig1JetSDJeweldr12 > 0.3)");
   // AddPlot(PdfFile, 50, 0, 1000, "(0.5, 1.5) DR < 0.2;PT",
   //    T1, "PT", "eventWeight[0] * (sig1JetSDJeweldr12 < 0.2)",
   //    T2, "PT", "eventWeight[0] * (sig1JetSDdr12 < 0.2)",
   //    T3, "PT", "eventWeight[0] * (sig1JetSDJeweldr12 < 0.2)");
   
   PdfFile.AddTextPage("SD (0.15, -2.0) plots");
   AddPlot(PdfFile, 2, 0, 2, "(0.15, -2.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
      T1, "sig2JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      T2, "sig2JetSDdr12 <= 0",      "eventWeight[0] * (PT > 200)",
      T3, "sig2JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) ZG, PT > 200, DR > 0.1;zg",
      T1, "sig2JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)",
      T2, "sig2JetSDZg",      "eventWeight[0] * (PT > 200 && sig2JetSDdr12 > 0.1)",
      T3, "sig2JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)",
      1e-2);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) DR, PT > 200, DR > 0.0;DR",
      T1, "sig2JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.0)",
      T2, "sig2JetSDdr12",      "eventWeight[0] * (PT > 200 && sig2JetSDdr12 > 0.0)",
      T3, "sig2JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.0)");
   AddPlot(PdfFile, 40, 0, 0.5, "(0.15, -2.0) DR, PT > 200, DR > 0.1;DR",
      T1, "sig2JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)",
      T2, "sig2JetSDdr12",      "eventWeight[0] * (PT > 200 && sig2JetSDdr12 > 0.1)",
      T3, "sig2JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.3, "(0.15, -2.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig2JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig2JetSDJeweldr12 > 0.1)",
      T2, "sig2JetSDM/PT",           "eventWeight[0] * (PT > 200 && sig2JetSDdr12 > 0.1)",
      T3, "sig2JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig2JetSDJeweldr12 > 0.1)",
      1e-2);
   AddPlot(PdfFile, 40, 0, 0.3, "(0.15, -2.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig2JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)",
      T2, "sig2JetSDM/sigJetSDPt",           "eventWeight[0] * (PT > 200 && sig2JetSDdr12 > 0.1)",
      T3, "sig2JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig2JetSDJeweldr12 > 0.1)",
      1e-2);
   
   PdfFile.AddTextPage("SD (100, 10) plots");
   AddPlot(PdfFile, 2, 0, 2, "(100, 10) Completely killed percentage, PT > 200;(left) good (right) killed;%",
      T1, "sig3JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      T2, "sig3JetSDdr12 <= 0",      "eventWeight[0] * (PT > 200)",
      T3, "sig3JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) ZG, PT > 200, DR > 0.1;zg",
      T1, "sig3JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)",
      T2, "sig3JetSDZg",      "eventWeight[0] * (PT > 200 && sig3JetSDdr12 > 0.1)",
      T3, "sig3JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) DR, PT > 200, DR > 0.0;DR",
      T1, "sig3JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.0)",
      T2, "sig3JetSDdr12",      "eventWeight[0] * (PT > 200 && sig3JetSDdr12 > 0.0)",
      T3, "sig3JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.0)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(100, 10) DR, PT > 200, DR > 0.1;DR",
      T1, "sig3JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)",
      T2, "sig3JetSDdr12",      "eventWeight[0] * (PT > 200 && sig3JetSDdr12 > 0.1)",
      T3, "sig3JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)",
      1e-2);
   AddPlot(PdfFile, 40, 0, 0.3, "(100, 10) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig3JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig3JetSDJeweldr12 > 0.1)",
      T2, "sig3JetSDM/PT",           "eventWeight[0] * (PT > 200 && sig3JetSDdr12 > 0.1)",
      T3, "sig3JetSDJewelM/PT", "eventWeight[0] * (sigJetJewelPt > 200 && sig3JetSDJeweldr12 > 0.1)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.3, "(100, 10) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig3JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)",
      T2, "sig3JetSDM/sigJetSDPt",           "eventWeight[0] * (PT > 200 && sig3JetSDdr12 > 0.1)",
      T3, "sig3JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig3JetSDJeweldr12 > 0.1)",
      1e-3);
   
   PdfFile.AddTextPage("SD (0.25, 0.0) plots");
   AddPlot(PdfFile, 2, 0, 2, "(0.25, 0.0) Completely killed percentage, PT > 200;(left) good (right) killed;%",
      T1, "sig4JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      T2, "sig4JetSDdr12 <= 0",      "eventWeight[0] * (PT > 200)",
      T3, "sig4JetSDJeweldr12 <= 0", "eventWeight[0] * (PT > 200)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) ZG, PT > 200, DR > 0.1;zg",
      T1, "sig4JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      T2, "sig4JetSDZg",      "eventWeight[0] * (PT > 200 && sig4JetSDdr12 > 0.1)",
      T3, "sig4JetSDJewelzg", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)");
   AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) DR, PT > 200, DR > 0.0;DR",
      T1, "sig4JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.0)",
      T2, "sig4JetSDdr12",      "eventWeight[0] * (PT > 200 && sig4JetSDdr12 > 0.0)",
      T3, "sig4JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.0)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.5, "(0.25, 0.0) DR, PT > 200, DR > 0.1;DR",
      T1, "sig4JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      T2, "sig4JetSDdr12",      "eventWeight[0] * (PT > 200 && sig4JetSDdr12 > 0.1)",
      T3, "sig4JetSDJeweldr12", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      1e-2);
   AddPlot(PdfFile, 40, 0, 0.3, "(0.25, 0.0) Mass/PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig4JetSDJewelM/PT", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      T2, "sig4JetSDM/PT",           "eventWeight[0] * (PT > 200 && sig4JetSDdr12 > 0.1)",
      T3, "sig4JetSDJewelM/PT", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      1e-3);
   AddPlot(PdfFile, 40, 0, 0.3, "(0.25, 0.0) Mass/Guu PT, PT > 200, DR > 0.1;Mass/PT",
      T1, "sig4JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      T2, "sig4JetSDM/sigJetSDPt",           "eventWeight[0] * (PT > 200 && sig4JetSDdr12 > 0.1)",
      T3, "sig4JetSDJewelM/sigJetSDJewelPt", "eventWeight[0] * (PT > 200 && sig4JetSDJeweldr12 > 0.1)",
      1e-3);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   RecoilFile.Close();
   NoRecoilFile.Close();
   VacuumFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, int N, double Min, double Max, string Title,
   TTree *T1, string Plot1, string Selection1,
   TTree *T2, string Plot2, string Selection2,
   TTree *T3, string Plot3, string Selection3,
   double LogMin)
{
   TH1D H1("H1", Title.c_str(), N, Min, Max);
   TH1D H2("H2", Title.c_str(), N, Min, Max);
   TH1D H3("H3", Title.c_str(), N, Min, Max);

   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);

   H1.SetMarkerColor(kBlue);
   H2.SetMarkerColor(kGreen);
   H3.SetMarkerColor(kRed);
   H1.SetLineColor(kBlue);
   H2.SetLineColor(kGreen);
   H3.SetLineColor(kRed);

   T1->Draw(Form("%s>>H1", Plot1.c_str()), ("(eventWeight[0] < 1000) * (" + Selection1 + ")").c_str());
   T2->Draw(Form("%s>>H2", Plot2.c_str()), ("(eventWeight[0] < 1000) * (" + Selection2 + ")").c_str());
   T3->Draw(Form("%s>>H3", Plot3.c_str()), ("(eventWeight[0] < 1000) * (" + Selection3 + ")").c_str());

   H1.Scale(1 / H1.Integral() / (Max - Min) * N);
   H2.Scale(1 / H2.Integral() / (Max - Min) * N);
   H3.Scale(1 / H3.Integral() / (Max - Min) * N);

   TCanvas Canvas;

   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   H3.Draw("same");
   H3.Draw("hist same");

   PdfFile.AddCanvas(Canvas);
   
   Canvas.SetLogy();
   if(LogMin > 0)
      H1.SetMinimum(LogMin);
   
   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   H3.Draw("same");
   H3.Draw("hist same");

   PdfFile.AddCanvas(Canvas);

   H1.Divide(&H3);
   H2.Divide(&H3);

   Canvas.SetLogy(false);

   H1.GetYaxis()->SetTitle("Ratio to vacuum");
   H1.SetMinimum(0);
   H1.SetMaximum(3);

   H1.Draw("");
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");

   PdfFile.AddCanvas(Canvas);
}





