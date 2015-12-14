#include <string>
#include <iostream>
using namespace std;

#include "TGraphErrors.h"
#include "TFile.h"

void CollectLatexFragment(string InputFile = "UncorrectedCalo.root")
{
   TFile F(InputFile.c_str());

   TGraphErrors *Mass = (TGraphErrors *)F.Get("GMass");
   TGraphErrors *AlphaL = (TGraphErrors *)F.Get("GAlphaL");
   TGraphErrors *AlphaR = (TGraphErrors *)F.Get("GAlphaR");
   TGraphErrors *SigmaL = (TGraphErrors *)F.Get("GSigmaL");
   TGraphErrors *SigmaR = (TGraphErrors *)F.Get("GSigmaR");

   for(int i = 0; i <= 4; i++)
   {
      double dummy = 0;
      double mass = 0;
      double alphal = 0;
      double alphar = 0;
      double sigmal = 0;
      double sigmar = 0;

      Mass->GetPoint(i, dummy, mass);
      AlphaL->GetPoint(i, dummy, alphal);
      AlphaR->GetPoint(i, dummy, alphar);
      SigmaL->GetPoint(i, dummy, sigmal);
      SigmaR->GetPoint(i, dummy, sigmar);

      printf("$N(\\geq %d~jets)$     & $ %.2f \\pm %.2f $ & $ %.3f \\pm %.3f $ & $ %.3f \\pm %.3f $ & $ %.3f \\pm %.3f $ & $ %.3f \\pm %.3f $ \\\\\n",
         i,
         mass, Mass->GetErrorY(i),
         alphal, AlphaL->GetErrorY(i),
         alphar, AlphaR->GetErrorY(i),
         sigmal, SigmaL->GetErrorY(i),
         sigmar, SigmaR->GetErrorY(i));
   }

   F.Close();
}



