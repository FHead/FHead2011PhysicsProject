#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"

#define MASSBINCOUNT 9
#define ZGBINCOUNT 10
#define DRBINCOUNT 15
#define PTPTBINCOUNT 50

int main()
{
   TFile FGraphs0("Graphs_SD0_Centered.root");
   TFile FGraphs7("Graphs_SD7_Centered.root");

   TFile File("HEPDataGraphs.root", "RECREATE");

   FGraphs0.Get("Data_MassData_4_2")->Clone("Figure2_SD0")->Write();
   FGraphs0.Get("Data_MassDataSys_4_2")->Clone("Figure2_SD0_Sys")->Write();
   FGraphs7.Get("Data_MassData_4_2")->Clone("Figure2_SD7")->Write();
   FGraphs7.Get("Data_MassDataSys_4_2")->Clone("Figure2_SD7_Sys")->Write();

   File.Close();

   FGraphs7.Close();
   FGraphs0.Close();

   return 0;
}

   
