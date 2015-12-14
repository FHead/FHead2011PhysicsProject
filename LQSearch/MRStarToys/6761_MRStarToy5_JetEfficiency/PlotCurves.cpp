#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"
#include "TGraph.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetStyle();

   double TCHELPTTemp[] = {40, 60, 80, 100, 200, 300, 500, 1000};
   double FlatEfficiencyTemp[] = {0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8};
   double TCHELEfficiencyTemp[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.82, 0.7, 0.4};
   double TCHELEfficiencyTempModerateDrop[] = {0.75, 0.825, 0.85, 0.87, 0.82, 0.77, 0.65, 0.3};
   double TCHELEfficiencyTempUp[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.87, 0.87, 0.87};
   double TCHELEfficiencyTempDown[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.72, 0.35, 0.0};
   double TCHELEfficiencyTempNoHighPT[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.82, 0.0, 0.0};
   double TCHELEfficiencyTempExtremeDrop[] = {0.75, 0.825, 0.85, 0.87, 0.60, 0.20, 0.0, 0.0};

   TGraph GFlat(8, TCHELPTTemp, FlatEfficiencyTemp);
   TGraph GTCHEL(8, TCHELPTTemp, TCHELEfficiencyTemp);
   TGraph GTCHELModerateDrop(8, TCHELPTTemp, TCHELEfficiencyTempModerateDrop);
   TGraph GTCHELUp(8, TCHELPTTemp, TCHELEfficiencyTempUp);
   TGraph GTCHELDown(8, TCHELPTTemp, TCHELEfficiencyTempDown);
   TGraph GTCHELNoHighPT(8, TCHELPTTemp, TCHELEfficiencyTempNoHighPT);
   TGraph GTCHELExtremeDrop(8, TCHELPTTemp, TCHELEfficiencyTempExtremeDrop);

   PsFileHelper PsFile("Curves.ps");
   PsFile.AddTextPage("CurvesTried");

   PsFile.AddPlot(GFlat, "apel");
   PsFile.AddPlot(GTCHEL, "apel");
   PsFile.AddPlot(GTCHELModerateDrop, "apel");
   PsFile.AddPlot(GTCHELUp, "apel");
   PsFile.AddPlot(GTCHELDown, "apel");
   PsFile.AddPlot(GTCHELNoHighPT, "apel");
   PsFile.AddPlot(GTCHELExtremeDrop, "apel");

   TCanvas C("C", "C", 1024, 1024);
   GTCHELExtremeDrop.SetTitle("Different toy efficiency curves");
   GTCHELExtremeDrop.SetLineColor(1);
   GTCHELExtremeDrop.SetLineWidth(2);
   GTCHELExtremeDrop.Draw("apel");
   GTCHELExtremeDrop.GetXaxis()->SetTitle("Jet PT");
   GTCHELExtremeDrop.GetYaxis()->SetTitle("Fake b-tagging efficiency");
   GFlat.SetLineColor(2);
   GFlat.SetLineWidth(2);
   GFlat.Draw("pel");
   GTCHEL.SetLineColor(8);
   GTCHEL.SetLineWidth(3);
   GTCHEL.Draw("pel");
   GTCHELModerateDrop.SetLineColor(4);
   GTCHELModerateDrop.SetLineWidth(2);
   GTCHELModerateDrop.Draw("pel");
   GTCHELUp.SetLineColor(9);
   GTCHELUp.SetLineWidth(2);
   GTCHELUp.Draw("pel");
   GTCHELDown.SetLineColor(6);
   GTCHELDown.SetLineWidth(2);
   GTCHELDown.Draw("pel");
   GTCHELNoHighPT.SetLineColor(7);
   GTCHELNoHighPT.SetLineWidth(2);
   GTCHELNoHighPT.Draw("pel");
   C.SaveAs("CurvesTried.png");
   C.SaveAs("CurvesTried.C");
   C.SaveAs("CurvesTried.eps");
   PsFile.AddCanvas(C);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}





