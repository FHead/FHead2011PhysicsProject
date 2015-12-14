#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TArrow.h"
#include "TChain.h"

#include "PlotHelper2.h"

int main()
{
   TChain Tree("ResultTree", "Tree");
   Tree.AddFile("FloatOnlyA2ZAA3ZA.root");

   bool Floated[6] = {false, false, true, true, false, false};

   float FitStatus;
   float Initial[6], Final[6];

   Tree.SetBranchAddress("Status", &FitStatus);
   Tree.SetBranchAddress("A2ZZA1ZZ", &Final[0]);
   Tree.SetBranchAddress("A3ZZA1ZZ", &Final[1]);
   Tree.SetBranchAddress("A2ZAA1ZZ", &Final[2]);
   Tree.SetBranchAddress("A3ZAA1ZZ", &Final[3]);
   Tree.SetBranchAddress("A2AAA1ZZ", &Final[4]);
   Tree.SetBranchAddress("A3AAA1ZZ", &Final[5]);
   Tree.SetBranchAddress("InitialA2ZZ", &Initial[0]);
   Tree.SetBranchAddress("InitialA3ZZ", &Initial[1]);
   Tree.SetBranchAddress("InitialA2ZA", &Initial[2]);
   Tree.SetBranchAddress("InitialA3ZA", &Initial[3]);
   Tree.SetBranchAddress("InitialA2AA", &Initial[4]);
   Tree.SetBranchAddress("InitialA3AA", &Initial[5]);

   PsFileHelper PsFile("InitialVsFinal.ps");
   PsFile.AddTextPage("Check stability of fits");

   int EntryCount = Tree.GetEntries();
   int EventCount = EntryCount / 1000;
   for(int iE = 0; iE < EventCount; iE++)
   {
      TH2D HInitialFinalA2ZZ("HInitialFinalA2ZZ", "Initial vs. final A2ZZ;initial;final", 100, -3, 3, 100, -3, 3);
      TH2D HInitialFinalA3ZZ("HInitialFinalA3ZZ", "Initial vs. final A3ZZ;initial;final", 100, -5, 5, 100, -5, 5);
      TH2D HInitialFinalA2ZA("HInitialFinalA2ZA", "Initial vs. final A2ZA;initial;final", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HInitialFinalA3ZA("HInitialFinalA3ZA", "Initial vs. final A3ZA;initial;final", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HInitialFinalA2AA("HInitialFinalA2AA", "Initial vs. final A2AA;initial;final", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HInitialFinalA3AA("HInitialFinalA3AA", "Initial vs. final A3AA;initial;final", 100, -0.1, 0.1, 100, -0.1, 0.1);

      TH2D HA2ZZA3ZZ("HA2ZZA3ZZ", "A2ZZ vs. A3ZZ;A2ZZ;A3ZZ", 100, -3, 3, 100, -5, 5);
      TH2D HA2ZZA2ZA("HA2ZZA2ZA", "A2ZZ vs. A2ZA;A2ZZ;A2ZA", 100, -3, 3, 100, -0.1, 0.1);
      TH2D HA2ZZA3ZA("HA2ZZA3ZA", "A2ZZ vs. A3ZA;A2ZZ;A3ZA", 100, -3, 3, 100, -0.1, 0.1);
      TH2D HA2ZZA2AA("HA2ZZA2AA", "A2ZZ vs. A2AA;A2ZZ;A2AA", 100, -3, 3, 100, -0.1, 0.1);
      TH2D HA2ZZA3AA("HA2ZZA3AA", "A2ZZ vs. A3AA;A2ZZ;A3AA", 100, -3, 3, 100, -0.1, 0.1);
      TH2D HA3ZZA2ZA("HA3ZZA2ZA", "A3ZZ vs. A2ZA;A3ZZ;A2ZA", 100, -5, 5, 100, -0.1, 0.1);
      TH2D HA3ZZA3ZA("HA3ZZA3ZA", "A3ZZ vs. A3ZA;A3ZZ;A3ZA", 100, -5, 5, 100, -0.1, 0.1);
      TH2D HA3ZZA2AA("HA3ZZA2AA", "A3ZZ vs. A2AA;A3ZZ;A2AA", 100, -5, 5, 100, -0.1, 0.1);
      TH2D HA3ZZA3AA("HA3ZZA3AA", "A3ZZ vs. A3AA;A3ZZ;A3AA", 100, -5, 5, 100, -0.1, 0.1);
      TH2D HA2ZAA3ZA("HA2ZAA3ZA", "A2ZA vs. A3ZA;A2ZA;A3ZA", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HA2ZAA2AA("HA2ZAA2AA", "A2ZA vs. A2AA;A2ZA;A2AA", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HA2ZAA3AA("HA2ZAA3AA", "A2ZA vs. A3AA;A2ZA;A3AA", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HA3ZAA2AA("HA3ZAA2AA", "A3ZA vs. A2AA;A3ZA;A2AA", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HA3ZAA3AA("HA3ZAA3AA", "A3ZA vs. A3AA;A3ZA;A3AA", 100, -0.1, 0.1, 100, -0.1, 0.1);
      TH2D HA2AAA3AA("HA2AAA3AA", "A2AA vs. A3AA;A2AA;A3AA", 100, -0.1, 0.1, 100, -0.1, 0.1);

      TH2D *HArrows[6][6] = {{NULL}};
      HArrows[0][1] = &HA2ZZA3ZZ;   HArrows[1][0] = &HA2ZZA3ZZ;
      HArrows[0][2] = &HA2ZZA2ZA;   HArrows[2][0] = &HA2ZZA2ZA;
      HArrows[0][3] = &HA2ZZA3ZA;   HArrows[3][0] = &HA2ZZA3ZA;
      HArrows[0][4] = &HA2ZZA2AA;   HArrows[4][0] = &HA2ZZA2AA;
      HArrows[0][5] = &HA2ZZA3AA;   HArrows[5][0] = &HA2ZZA3AA;
      HArrows[1][2] = &HA3ZZA2ZA;   HArrows[2][1] = &HA3ZZA2ZA;
      HArrows[1][3] = &HA3ZZA3ZA;   HArrows[3][1] = &HA3ZZA3ZA;
      HArrows[1][4] = &HA3ZZA2AA;   HArrows[4][1] = &HA3ZZA2AA;
      HArrows[1][5] = &HA3ZZA3AA;   HArrows[5][1] = &HA3ZZA3AA;
      HArrows[2][3] = &HA2ZAA3ZA;   HArrows[3][2] = &HA2ZAA3ZA;
      HArrows[2][4] = &HA2ZAA2AA;   HArrows[4][2] = &HA2ZAA2AA;
      HArrows[2][5] = &HA2ZAA3AA;   HArrows[5][2] = &HA2ZAA3AA;
      HArrows[3][4] = &HA3ZAA2AA;   HArrows[4][3] = &HA3ZAA2AA;
      HArrows[3][5] = &HA3ZAA3AA;   HArrows[5][3] = &HA3ZAA3AA;
      HArrows[4][5] = &HA2AAA3AA;   HArrows[5][4] = &HA2AAA3AA;

      vector<double> Initials[6];
      vector<double> Finals[6];

      for(int iT = 0; iT < 1000; iT++)
      {
         Tree.GetEntry(iE * 1000 + iT);

         if(FitStatus < 3)
            continue;

         for(int i = 0; i < 6; i++)
         {
            Initials[i].push_back(Initial[i]);
            Finals[i].push_back(Final[i]);
         }

         HInitialFinalA2ZZ.Fill(Initial[0], Final[0]);
         HInitialFinalA3ZZ.Fill(Initial[1], Final[1]);
         HInitialFinalA2ZA.Fill(Initial[2], Final[2]);
         HInitialFinalA3ZA.Fill(Initial[3], Final[3]);
         HInitialFinalA2AA.Fill(Initial[4], Final[4]);
         HInitialFinalA3AA.Fill(Initial[5], Final[5]);
      }

      PsFile.AddTextPage("DATASET SEPARATOR");
      if(Floated[0] == true)   PsFile.AddPlot(HInitialFinalA2ZZ, "colz");
      if(Floated[1] == true)   PsFile.AddPlot(HInitialFinalA3ZZ, "colz");
      if(Floated[2] == true)   PsFile.AddPlot(HInitialFinalA2ZA, "colz");
      if(Floated[3] == true)   PsFile.AddPlot(HInitialFinalA3ZA, "colz");
      if(Floated[4] == true)   PsFile.AddPlot(HInitialFinalA2AA, "colz");
      if(Floated[5] == true)   PsFile.AddPlot(HInitialFinalA3AA, "colz");
      
      for(int i = 0; i < 6; i++)
      {
         if(Floated[i] == false)
            continue;

         for(int j = i + 1; j < 6; j++)
         {
            if(Floated[j] == false)
               continue;

            TCanvas Canvas;

            HArrows[i][j]->SetStats(0);
            HArrows[i][j]->Draw();

            vector<TArrow *> Arrows;
            for(int k = 0; k < (int)Initials[i].size(); k++)
            {
               Arrows.push_back(new TArrow(Initials[i][k], Initials[j][k], Finals[i][k], Finals[j][k], 0.01, "|>"));
               Arrows[k]->SetAngle(30);
               Arrows[k]->Draw();
            }

            PsFile.AddCanvas(Canvas);

            for(int k = 0; k < (int)Arrows.size(); k++)
               delete Arrows[k];
         }
      }
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




