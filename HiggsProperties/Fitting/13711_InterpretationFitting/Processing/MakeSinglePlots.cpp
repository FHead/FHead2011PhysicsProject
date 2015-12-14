#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   string FileName = "Result/ResultBothS_SM_A_10000.root";
   string OutputBase = "Meow";

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(FileName);

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("ResultTree");

   string Cut = "Status == 3 && A2ZZA1ZZError == 0 && A3ZZA1ZZError == 0 && A4ZZA1ZZError == 0";

   TH1D HYTSingle("HYTSingle", "YT, float only YT;YT", 100, -10, 10);
   Tree->Draw("YT>>HYTSingle", (Cut + " && YTError > 0 && YTAError == 0 && MTError == 0").c_str());
   PsFile.AddPlot(HYTSingle);
 
   TH1D HYTPullSingle("HYTPullSingle", "(YT - 1) / YTError, float only YT;YT Pull", 100, -5, 5);
   Tree->Draw("(YT-1)/YTError>>HYTPullSingle", (Cut + " && YTError > 0 && YTAError == 0 && MTError == 0").c_str());
   PsFile.AddPlot(HYTPullSingle);

   TH1D HYTASingle("HYTASingle", "YTA, float only YTA;YTA", 100, -10, 10);
   Tree->Draw("YTA>>HYTASingle", (Cut + " && YTError == 0 && YTAError > 0 && MTError == 0").c_str());
   PsFile.AddPlot(HYTASingle);

   TH1D HYTAPullSingle("HYTAPullSingle", "YTA / YTAError, float only YTA;YTA Pull", 100, -5, 5);
   Tree->Draw("YTA/YTAError>>HYTAPullSingle", (Cut + " && YTError == 0 && YTAError > 0 && MTError == 0").c_str());
   PsFile.AddPlot(HYTAPullSingle);

   TH1D HMTSingle("HMTSingle", "MT, float only MT;MT", 100, 50, 1001);
   Tree->Draw("MT>>HMTSingle", (Cut + " && YTError == 0 && YTAError == 0 && MTError > 0").c_str());
   PsFile.AddPlot(HMTSingle);

   TH2D HMTMTErrorSingle("HMTMTErrorSingle", "MT, float only MT;MT error;MT", 100, 50, 1001, 100, 0, 1000);
   Tree->Draw("MT:MTError>>HMTMTErrorSingle", (Cut + " && YTError == 0 && YTAError == 0 && MTError > 0").c_str());
   PsFile.AddPlot(HMTMTErrorSingle, "colz");

   File.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}



