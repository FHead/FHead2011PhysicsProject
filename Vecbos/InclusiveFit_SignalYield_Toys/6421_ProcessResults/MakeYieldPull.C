#include <string>
using namespace std;

#include "TH1D.h"
#include "TChain.h"
#include "TCanvas.h"

void MakeYieldPull(string RootFile = "CaloFitResult_00001_01000.root")
{
   TH1D Pull1("Pull1", "Pull for at least one CaloJet", 50, -4, 4);
   TH1D Pull2("Pull2", "Pull for at least two CaloJet", 50, -4, 4);
   TH1D Pull3("Pull3", "Pull for at least three CaloJet", 50, -4, 4);
   TH1D Pull4("Pull4", "Pull for at least four CaloJet", 50, -4, 4);

   TChain ResultTree("ResultTree", "ResultTree");
   ResultTree.AddFile(RootFile.c_str());

   double InclusiveSignal[10];
   double InclusiveSignalError[10];

   for(int N = 1; N <= 4; N++)
   {
      ResultTree.SetBranchAddress(Form("InclusiveSignal%d", N), &InclusiveSignal[N-1]);
      ResultTree.SetBranchAddress(Form("InclusiveSignal%dError", N), &InclusiveSignalError[N-1]);
   }
   
   double SignalYield[] = {3469, 767, 159, 36.8};

   int EntryCount = ResultTree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      ResultTree.GetEntry(i);

      Pull1.Fill((InclusiveSignal[0] - SignalYield[0]) / InclusiveSignalError[0] * sqrt(2));
      Pull2.Fill((InclusiveSignal[1] - SignalYield[1]) / InclusiveSignalError[1]);
      Pull3.Fill((InclusiveSignal[2] - SignalYield[2]) / InclusiveSignalError[2]);
      Pull4.Fill((InclusiveSignal[3] - SignalYield[3]) / InclusiveSignalError[3]);
   }

   Pull1.SetStats(0);
   Pull2.SetStats(0);
   Pull3.SetStats(0);
   Pull4.SetStats(0);

   Pull1.Fit("gaus");
   Pull2.Fit("gaus");
   Pull3.Fit("gaus");
   Pull4.Fit("gaus");

   TCanvas C1;
   Pull1.Draw();
   C1.SaveAs("Temp1.png");

   TCanvas C2;
   Pull2.Draw();
   C2.SaveAs("Temp2.png");

   TCanvas C3;
   Pull3.Draw();
   C3.SaveAs("Temp3.png");
   
   TCanvas C4;
   Pull4.Draw();
   C4.SaveAs("Temp4.png");

   TCanvas C("C", "C", 0, 0, 1024, 1024);
   C.Divide(2, 2);
   C.cd(1);
   Pull1.Draw();
   C.cd(2);
   Pull2.Draw();
   C.cd(3);
   Pull3.Draw();
   C.cd(4);
   Pull4.Draw();
   C.SaveAs("Temp.png");
}
