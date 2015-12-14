#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"

#include "PlotHelper.h"

int main()
{
   PsFileHelper PsFile("SummarizeFits.ps");
   PsFile.AddTextPage("Summarize Fits");

   for(int i = 1; i <= 7; i++)
   {
      PsFile.AddTextPage(Form("Razor variant with option %d", i));

      TFile F1(Form("Exp1_%d.root", i));
      PsFile.AddGraphFromFile(F1, "Graph", "ap");
      F1.Close();
      
      TFile F2(Form("Exp2_%d.root", i));
      PsFile.AddGraphFromFile(F2, "Graph", "ap");
      F2.Close();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}



