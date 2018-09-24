#include <iostream>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string InputTreeName = CL.Get("tree", "DiscretizedJetTree");
   string OutputFileName = CL.Get("output", "JetImages.pdf");
   double MinJetPT = CL.GetDouble("minjetpt", 300);

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get(InputTreeName.c_str());
   assert(Tree != NULL);

   int HydjetEntry, PythiaEntry, AllJetCount, JetCount, JetIndex;
   float JetPT, JetEta, JetPhi;
   float Images[89][89][7];

   Tree->SetBranchAddress("HydjetEntry", &HydjetEntry);
   Tree->SetBranchAddress("PythiaEntry", &PythiaEntry);
   Tree->SetBranchAddress("AllJetCount", &AllJetCount);
   Tree->SetBranchAddress("JetCount", &JetCount);
   Tree->SetBranchAddress("JetIndex", &JetIndex);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("Images", &Images);

   int Count = 0;
   TH2D HAverageCETSignal("HAverageCETSignal", "Signal charged ET;Eta Bin;Phi Bin",
      89, 0, 89, 89, 0, 89);
   TH2D HAverageNETSignal("HAverageNETSignal", "Signal neutral ET;Eta Bin;Phi Bin",
      89, 0, 89, 89, 0, 89);
   TH2D HAverageCETBackground("HAverageCETBackground", "Background charged ET;Eta Bin;Phi Bin",
      89, 0, 89, 89, 0, 89);
   TH2D HAverageNETBackground("HAverageNETBackground", "Background neutral ET;Eta Bin;Phi Bin",
      89, 0, 89, 89, 0, 89);

   HAverageCETSignal.SetStats(0);
   HAverageNETSignal.SetStats(0);
   HAverageCETBackground.SetStats(0);
   HAverageNETBackground.SetStats(0);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(JetPT < MinJetPT)
         continue;

      Count = Count + 1;
      for(int i = 0; i < 89; i++)
      {
         for(int j = 0; j < 89; j++)
         {
            HAverageCETSignal.Fill(i + 0.5, j + 0.5, Images[i][j][1]);
            HAverageNETSignal.Fill(i + 0.5, j + 0.5, Images[i][j][2]);
            HAverageCETBackground.Fill(i + 0.5, j + 0.5, Images[i][j][4]);
            HAverageNETBackground.Fill(i + 0.5, j + 0.5, Images[i][j][5]);
         }
      }
   }

   HAverageCETSignal.Scale(double(1) / Count);
   HAverageNETSignal.Scale(double(1) / Count);
   HAverageCETBackground.Scale(double(1) / Count);
   HAverageNETBackground.Scale(double(1) / Count);

   TCanvas Canvas;

   Canvas.Divide(2, 2);

   Canvas.cd(1);
   Canvas.cd(1)->SetGridx();
   Canvas.cd(1)->SetGridy();
   HAverageCETSignal.Draw("colz");
   Canvas.cd(2);
   Canvas.cd(2)->SetGridx();
   Canvas.cd(2)->SetGridy();
   HAverageNETSignal.Draw("colz");
   Canvas.cd(3);
   Canvas.cd(3)->SetGridx();
   Canvas.cd(3)->SetGridy();
   HAverageCETBackground.Draw("colz");
   Canvas.cd(4);
   Canvas.cd(4)->SetGridx();
   Canvas.cd(4)->SetGridy();
   HAverageNETBackground.Draw("colz");

   Canvas.SaveAs("AverageJetImage.pdf");

   InputFile.Close();

   return 0;
}





