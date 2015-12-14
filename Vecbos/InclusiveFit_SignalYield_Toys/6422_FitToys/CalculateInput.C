#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "RooDataSet.h"
using namespace RooFit;

#include "PlotHelper.h"

void CalculateInput(string InputFile = "Samples/ToyForCaloJet.root")
{
   PsFileHelper PsFile("InputDistributions.ps");
   PsFile.AddTextPage("Input distributions for the toys");

   TFile F(InputFile.c_str());

   TH1D Input1("Input1", "input 1", 1000, 2500, 3500);

   for(int i = 0; i < 1000; i++)
   {
      RooDataSet *Roo = (RooDataSet *)F.Get(Form("ToyExperiment%d", i + 1));

      cout << Roo->sumEntries() << endl;

      Input1.Fill(Roo->sumEntries());
   }

   PsFile.AddPlot(Input1);

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}


