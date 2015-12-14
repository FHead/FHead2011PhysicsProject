#include <iostream>
#include <cmath>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"

#include "ChainAll.h"
#include "TauHelperFunctions2.h"

int main()
{
   TChain *Tree = ChainAll("ResultList", "Tree");

   double ZPT = 0;
   double ZY = 0;
   double Nu1[3] = {0};
   double Nu2[3] = {0};

   Tree->SetBranchAddress("PT", &ZPT);
   Tree->SetBranchAddress("Y", &ZY);
   Tree->SetBranchAddress("Nu1", Nu1);
   Tree->SetBranchAddress("Nu2", Nu2);

   TFile F("Output.root", "RECREATE");

   TH2D HTotalCount("HTotalCount", "Total Count;Y;PT", 100, 0, 1.5, 100, 20, 1000);
   TH2D HPassedCount("HPassedCount", "Passed Count;Y;PT", 100, 0, 1.5, 100, 20, 1000);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      FourVector Nu1P(0, Nu1[0], Nu1[2], Nu1[3]);   Nu1P[0] = Nu1P.GetP();
      FourVector Nu2P(0, Nu2[0], Nu2[2], Nu2[3]);   Nu2P[0] = Nu2P.GetP();

      bool Pass = true;
      if(Nu1P.GetAbsEta() > 2.4 || Nu1P.GetPT() < 30)
         Pass = false;
      if(Nu2P.GetAbsEta() > 2.4 || Nu2P.GetPT() < 30)
         Pass = false;

      HTotalCount.Fill(fabs(ZY), ZPT);
      if(Pass == true)
         HPassedCount.Fill(fabs(ZY), ZPT);
   }

   HTotalCount.Write();
   HPassedCount.Write();

   F.Close();

   return 0;
}







