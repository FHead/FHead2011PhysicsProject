#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   TGraphAsymmErrors GStat, GSys;
   GStat.SetName("GStat");
   GSys.SetName("GSys");

   TFile InputFile("Inc_Jet_Energy_NLO.root");

   TTree *Tree = (TTree *)InputFile.Get("Tree");

   double XLow, XHigh, Y, YStat, YSysLow, YSysHigh;
   Tree->SetBranchAddress("XLow", &XLow);
   Tree->SetBranchAddress("XHigh", &XHigh);
   Tree->SetBranchAddress("Y", &Y);
   Tree->SetBranchAddress("YStat", &YStat);
   Tree->SetBranchAddress("YSysLow", &YSysLow);
   Tree->SetBranchAddress("YSysHigh", &YSysHigh);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      GStat.SetPoint(iE, (XLow + XHigh) / 2, Y);
      GStat.SetPointError(iE, (XHigh - XLow) / 2, (XHigh - XLow) / 2, YStat, YStat);
      GSys.SetPoint(iE, (XLow + XHigh) / 2, Y);
      GSys.SetPointError(iE, (XHigh - XLow) / 2, (XHigh - XLow) / 2, Y - YSysLow, YSysHigh - Y);
   }

   InputFile.Close();

   TFile OutputFile("GraphsNLO.root", "RECREATE");

   GStat.Write();
   GSys.Write();

   OutputFile.Close();

   return 0;
}


