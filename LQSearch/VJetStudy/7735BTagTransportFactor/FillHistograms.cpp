#include <iostream>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input CrossSection Output [AO]" << endl;
      return -1;
   }

   bool UsePhoton = true;
   if(argc >= 5 && argv[4][0] == 'O')
      UsePhoton = false;

   TFile InputFile(argv[1]);
   double TotalWeight = ((TH1D *)InputFile.Get("HPileUpCount"))->Integral();
   InputFile.Close();

   stringstream sigmastr(argv[2]);
   double CrossSection = -1;
   sigmastr >> CrossSection;

   TChain InputTree("ReducedTree", "ReducedTree");
   InputTree.AddFile(argv[1]);

   double MROriginal, ROriginal, MRPhoton, RPhoton;
   InputTree.SetBranchAddress("MR", &MROriginal);
   InputTree.SetBranchAddress("R", &ROriginal);
   InputTree.SetBranchAddress("MRPhoton", &MRPhoton);
   InputTree.SetBranchAddress("RPhoton", &RPhoton);

   int LooseTagCount, MediumTagCount;
   InputTree.SetBranchAddress("LooseBTagCount", &LooseTagCount);
   InputTree.SetBranchAddress("MediumBTagCount", &MediumTagCount);

   TFile OutputFile(argv[3], "recreate");

   TH1D HMR_R2010("HMR_R2010", "MR, R2 > 0.1;MR", 25, 0, 1000);
   TH1D HMR_R2010_L("HMR_R2010_L", "MR, R2 > 0.1, L >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2010_LL("HMR_R2010_LL", "MR, R2 > 0.1, LL >= 2;MR", 25, 0, 1000);
   TH1D HMR_R2010_M("HMR_R2010_M", "MR, R2 > 0.1, M >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2010_MM("HMR_R2010_MM", "MR, R2 > 0.1, MM >= 2;MR", 25, 0, 1000);

   TH1D HMR_R2020("HMR_R2020", "MR, R2 > 0.2;MR", 25, 0, 1000);
   TH1D HMR_R2020_L("HMR_R2020_L", "MR, R2 > 0.2, L >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2020_LL("HMR_R2020_LL", "MR, R2 > 0.2, LL >= 2;MR", 25, 0, 1000);
   TH1D HMR_R2020_M("HMR_R2020_M", "MR, R2 > 0.2, M >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2020_MM("HMR_R2020_MM", "MR, R2 > 0.2, MM >= 2;MR", 25, 0, 1000);
   
   TH1D HMR_R2030("HMR_R2030", "MR, R2 > 0.3;MR", 25, 0, 1000);
   TH1D HMR_R2030_L("HMR_R2030_L", "MR, R2 > 0.3, L >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2030_LL("HMR_R2030_LL", "MR, R2 > 0.3, LL >= 2;MR", 25, 0, 1000);
   TH1D HMR_R2030_M("HMR_R2030_M", "MR, R2 > 0.3, M >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2030_MM("HMR_R2030_MM", "MR, R2 > 0.3, MM >= 2;MR", 25, 0, 1000);
   
   TH1D HMR_R2040("HMR_R2040", "MR, R2 > 0.4;MR", 25, 0, 1000);
   TH1D HMR_R2040_L("HMR_R2040_L", "MR, R2 > 0.4, L >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2040_LL("HMR_R2040_LL", "MR, R2 > 0.4, LL >= 2;MR", 25, 0, 1000);
   TH1D HMR_R2040_M("HMR_R2040_M", "MR, R2 > 0.4, M >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2040_MM("HMR_R2040_MM", "MR, R2 > 0.4, MM >= 2;MR", 25, 0, 1000);
   
   TH1D HMR_R2050("HMR_R2050", "MR, R2 > 0.5;MR", 25, 0, 1000);
   TH1D HMR_R2050_L("HMR_R2050_L", "MR, R2 > 0.5, L >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2050_LL("HMR_R2050_LL", "MR, R2 > 0.5, LL >= 2;MR", 25, 0, 1000);
   TH1D HMR_R2050_M("HMR_R2050_M", "MR, R2 > 0.5, M >= 1;MR", 25, 0, 1000);
   TH1D HMR_R2050_MM("HMR_R2050_MM", "MR, R2 > 0.5, MM >= 2;MR", 25, 0, 1000);

   TH1D HR2_MR200("HR2_MR200", "R2, MR > 200;R2", 25, 0, 1);
   TH1D HR2_MR200_L("HR2_MR200_L", "R2, MR > 200, L >= 1;R2", 25, 0, 1);
   TH1D HR2_MR200_LL("HR2_MR200_LL", "R2, MR > 200, L >= 2;R2", 25, 0, 1);
   TH1D HR2_MR200_M("HR2_MR200_M", "R2, MR > 200, M >= 1;R2", 25, 0, 1);
   TH1D HR2_MR200_MM("HR2_MR200_MM", "R2, MR > 200, M >= 2;R2", 25, 0, 1);
   
   TH1D HR2_MR300("HR2_MR300", "R2, MR > 300;R2", 25, 0, 1);
   TH1D HR2_MR300_L("HR2_MR300_L", "R2, MR > 300, L >= 1;R2", 25, 0, 1);
   TH1D HR2_MR300_LL("HR2_MR300_LL", "R2, MR > 300, L >= 2;R2", 25, 0, 1);
   TH1D HR2_MR300_M("HR2_MR300_M", "R2, MR > 300, M >= 1;R2", 25, 0, 1);
   TH1D HR2_MR300_MM("HR2_MR300_MM", "R2, MR > 300, M >= 2;R2", 25, 0, 1);
   
   TH1D HR2_MR400("HR2_MR400", "R2, MR > 400;R2", 25, 0, 1);
   TH1D HR2_MR400_L("HR2_MR400_L", "R2, MR > 400, L >= 1;R2", 25, 0, 1);
   TH1D HR2_MR400_LL("HR2_MR400_LL", "R2, MR > 400, L >= 2;R2", 25, 0, 1);
   TH1D HR2_MR400_M("HR2_MR400_M", "R2, MR > 400, M >= 1;R2", 25, 0, 1);
   TH1D HR2_MR400_MM("HR2_MR400_MM", "R2, MR > 400, M >= 2;R2", 25, 0, 1);
   
   TH1D HR2_MR500("HR2_MR500", "R2, MR > 500;R2", 25, 0, 1);
   TH1D HR2_MR500_L("HR2_MR500_L", "R2, MR > 500, L >= 1;R2", 25, 0, 1);
   TH1D HR2_MR500_LL("HR2_MR500_LL", "R2, MR > 500, L >= 2;R2", 25, 0, 1);
   TH1D HR2_MR500_M("HR2_MR500_M", "R2, MR > 500, M >= 1;R2", 25, 0, 1);
   TH1D HR2_MR500_MM("HR2_MR500_MM", "R2, MR > 500, M >= 2;R2", 25, 0, 1);
   
   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      double MR = MRPhoton;
      double R = RPhoton;
      if(UsePhoton == false)
      {
         MR = MROriginal;
         R = ROriginal;
      }

      double Weight = 1;

      if(R * R > 0.1)                          HMR_R2010.Fill(MR, Weight);
      if(R * R > 0.1 && LooseTagCount >= 1)    HMR_R2010_L.Fill(MR, Weight);
      if(R * R > 0.1 && LooseTagCount >= 2)    HMR_R2010_LL.Fill(MR, Weight);
      if(R * R > 0.1 && MediumTagCount >= 1)   HMR_R2010_M.Fill(MR, Weight);
      if(R * R > 0.1 && MediumTagCount >= 2)   HMR_R2010_MM.Fill(MR, Weight);

      if(R * R > 0.2)                          HMR_R2020.Fill(MR, Weight);
      if(R * R > 0.2 && LooseTagCount >= 1)    HMR_R2020_L.Fill(MR, Weight);
      if(R * R > 0.2 && LooseTagCount >= 2)    HMR_R2020_LL.Fill(MR, Weight);
      if(R * R > 0.2 && MediumTagCount >= 1)   HMR_R2020_M.Fill(MR, Weight);
      if(R * R > 0.2 && MediumTagCount >= 2)   HMR_R2020_MM.Fill(MR, Weight);

      if(R * R > 0.3)                          HMR_R2030.Fill(MR, Weight);
      if(R * R > 0.3 && LooseTagCount >= 1)    HMR_R2030_L.Fill(MR, Weight);
      if(R * R > 0.3 && LooseTagCount >= 2)    HMR_R2030_LL.Fill(MR, Weight);
      if(R * R > 0.3 && MediumTagCount >= 1)   HMR_R2030_M.Fill(MR, Weight);
      if(R * R > 0.3 && MediumTagCount >= 2)   HMR_R2030_MM.Fill(MR, Weight);

      if(R * R > 0.4)                          HMR_R2040.Fill(MR, Weight);
      if(R * R > 0.4 && LooseTagCount >= 1)    HMR_R2040_L.Fill(MR, Weight);
      if(R * R > 0.4 && LooseTagCount >= 2)    HMR_R2040_LL.Fill(MR, Weight);
      if(R * R > 0.4 && MediumTagCount >= 1)   HMR_R2040_M.Fill(MR, Weight);
      if(R * R > 0.4 && MediumTagCount >= 2)   HMR_R2040_MM.Fill(MR, Weight);

      if(R * R > 0.5)                          HMR_R2050.Fill(MR, Weight);
      if(R * R > 0.5 && LooseTagCount >= 1)    HMR_R2050_L.Fill(MR, Weight);
      if(R * R > 0.5 && LooseTagCount >= 2)    HMR_R2050_LL.Fill(MR, Weight);
      if(R * R > 0.5 && MediumTagCount >= 1)   HMR_R2050_M.Fill(MR, Weight);
      if(R * R > 0.5 && MediumTagCount >= 2)   HMR_R2050_MM.Fill(MR, Weight);

      if(MR > 200)                             HR2_MR200.Fill(R * R, Weight);
      if(MR > 200 && LooseTagCount >= 1)       HR2_MR200_L.Fill(R * R, Weight);
      if(MR > 200 && LooseTagCount >= 2)       HR2_MR200_LL.Fill(R * R, Weight);
      if(MR > 200 && MediumTagCount >= 1)      HR2_MR200_M.Fill(R * R, Weight);
      if(MR > 200 && MediumTagCount >= 2)      HR2_MR200_MM.Fill(R * R, Weight);

      if(MR > 300)                             HR2_MR300.Fill(R * R, Weight);
      if(MR > 300 && LooseTagCount >= 1)       HR2_MR300_L.Fill(R * R, Weight);
      if(MR > 300 && LooseTagCount >= 2)       HR2_MR300_LL.Fill(R * R, Weight);
      if(MR > 300 && MediumTagCount >= 1)      HR2_MR300_M.Fill(R * R, Weight);
      if(MR > 300 && MediumTagCount >= 2)      HR2_MR300_MM.Fill(R * R, Weight);

      if(MR > 400)                             HR2_MR400.Fill(R * R, Weight);
      if(MR > 400 && LooseTagCount >= 1)       HR2_MR400_L.Fill(R * R, Weight);
      if(MR > 400 && LooseTagCount >= 2)       HR2_MR400_LL.Fill(R * R, Weight);
      if(MR > 400 && MediumTagCount >= 1)      HR2_MR400_M.Fill(R * R, Weight);
      if(MR > 400 && MediumTagCount >= 2)      HR2_MR400_MM.Fill(R * R, Weight);

      if(MR > 500)                             HR2_MR500.Fill(R * R, Weight);
      if(MR > 500 && LooseTagCount >= 1)       HR2_MR500_L.Fill(R * R, Weight);
      if(MR > 500 && LooseTagCount >= 2)       HR2_MR500_LL.Fill(R * R, Weight);
      if(MR > 500 && MediumTagCount >= 1)      HR2_MR500_M.Fill(R * R, Weight);
      if(MR > 500 && MediumTagCount >= 2)      HR2_MR500_MM.Fill(R * R, Weight);
   }

   if(CrossSection > 0)
   {
      HMR_R2010.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2010_L.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2010_LL.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2010_M.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2010_MM.Scale(CrossSection * 1000 / TotalWeight);
      
      HMR_R2020.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2020_L.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2020_LL.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2020_M.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2020_MM.Scale(CrossSection * 1000 / TotalWeight);
      
      HMR_R2030.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2030_L.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2030_LL.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2030_M.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2030_MM.Scale(CrossSection * 1000 / TotalWeight);
      
      HMR_R2040.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2040_L.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2040_LL.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2040_M.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2040_MM.Scale(CrossSection * 1000 / TotalWeight);
      
      HMR_R2050.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2050_L.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2050_LL.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2050_M.Scale(CrossSection * 1000 / TotalWeight);
      HMR_R2050_MM.Scale(CrossSection * 1000 / TotalWeight);

      HR2_MR200.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR200_L.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR200_LL.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR200_M.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR200_MM.Scale(CrossSection * 1000 / TotalWeight);

      HR2_MR300.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR300_L.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR300_LL.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR300_M.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR300_MM.Scale(CrossSection * 1000 / TotalWeight);

      HR2_MR400.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR400_L.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR400_LL.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR400_M.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR400_MM.Scale(CrossSection * 1000 / TotalWeight);

      HR2_MR500.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR500_L.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR500_LL.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR500_M.Scale(CrossSection * 1000 / TotalWeight);
      HR2_MR500_MM.Scale(CrossSection * 1000 / TotalWeight);
   }

   HMR_R2010.Write();
   HMR_R2010_L.Write();
   HMR_R2010_LL.Write();
   HMR_R2010_M.Write();
   HMR_R2010_MM.Write();

   HMR_R2020.Write();
   HMR_R2020_L.Write();
   HMR_R2020_LL.Write();
   HMR_R2020_M.Write();
   HMR_R2020_MM.Write();

   HMR_R2030.Write();
   HMR_R2030_L.Write();
   HMR_R2030_LL.Write();
   HMR_R2030_M.Write();
   HMR_R2030_MM.Write();

   HMR_R2040.Write();
   HMR_R2040_L.Write();
   HMR_R2040_LL.Write();
   HMR_R2040_M.Write();
   HMR_R2040_MM.Write();

   HMR_R2050.Write();
   HMR_R2050_L.Write();
   HMR_R2050_LL.Write();
   HMR_R2050_M.Write();
   HMR_R2050_MM.Write();

   HR2_MR200.Write();
   HR2_MR200_L.Write();
   HR2_MR200_LL.Write();
   HR2_MR200_M.Write();
   HR2_MR200_MM.Write();

   HR2_MR300.Write();
   HR2_MR300_L.Write();
   HR2_MR300_LL.Write();
   HR2_MR300_M.Write();
   HR2_MR300_MM.Write();

   HR2_MR400.Write();
   HR2_MR400_L.Write();
   HR2_MR400_LL.Write();
   HR2_MR400_M.Write();
   HR2_MR400_MM.Write();

   HR2_MR500.Write();
   HR2_MR500_L.Write();
   HR2_MR500_LL.Write();
   HR2_MR500_M.Write();
   HR2_MR500_MM.Write();

   OutputFile.Close();
}






