#include <string>
#include <iostream>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TF1.h"

#include "PlotHelper.h"

void FitForAlphaBeta(string InputFile = "CaloFitResult_00001_00500.root", int BinCount = 5)
{
   TChain ResultTree("ResultTree", "ResultTree");
   ResultTree.AddFile(InputFile.c_str());

   double InclusiveSignal[10];
   double InclusiveSignalError[10];

   for(int N = 1; N <= BinCount; N++)
   {
      ResultTree.SetBranchAddress(Form("InclusiveSignal%d", N), &InclusiveSignal[N-1]);
      ResultTree.SetBranchAddress(Form("InclusiveSignal%dError", N), &InclusiveSignalError[N-1]);
   }

   PsFileHelper PullOutput("Pulls.ps");
   PullOutput.AddTextPage("Pull distribution from toys");

   TH1D Parameter1Pull("Parameter1Pull", "Alpha parameter pull", 100, -10, 10);
   TH1D Parameter2Pull("Parameter2Pull", "Beta parameter pull", 100, -10, 10);

   int EventCount = ResultTree.GetEntries();
   for(int i = 0; i < EventCount; i++)
   {
      ResultTree.GetEntry(i);

      cout << InclusiveSignal[0] << " "
         << InclusiveSignal[1] << " "
         << InclusiveSignal[2] << " "
         << InclusiveSignal[3] << endl;

      TH1D XD("XD", "XD", BinCount, 0.5, BinCount + 0.5);

      for(int N = 1; N < BinCount; N++)
      {
         XD.SetBinContent(N, InclusiveSignal[N-1] / InclusiveSignal[N]);
         XD.SetBinError(N, InclusiveSignal[N-1] / InclusiveSignal[N] * sqrt((InclusiveSignalError[N-1] / InclusiveSignal[N-1]) * (InclusiveSignalError[N-1] / InclusiveSignal[N-1]) + (InclusiveSignalError[N] / InclusiveSignal[N]) * (InclusiveSignalError[N] / InclusiveSignal[N])));
      }

      TF1 Line("line", "pol1", 0, BinCount + 1);

      XD.Fit(&Line);

      cout << i << endl;
      cout << Line.GetParameter(0) << " " << Line.GetParError(0) << endl;
      cout << Line.GetParameter(1) << " " << Line.GetParError(1) << endl;

      Parameter1Pull.Fill((Line.GetParameter(0) - 4.41427) / Line.GetParError(0));
      Parameter2Pull.Fill((Line.GetParameter(1) - 0.121362) / Line.GetParError(1));
   }

   Parameter1Pull.Fit("gaus");
   Parameter2Pull.Fit("gaus");

   PullOutput.AddPlot(Parameter1Pull);
   PullOutput.AddPlot(Parameter2Pull);

   PullOutput.AddTimeStampPage();
   PullOutput.Close();
}



