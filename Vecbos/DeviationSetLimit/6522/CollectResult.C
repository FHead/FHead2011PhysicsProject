#include <vector>
#include <string>
using namespace std;

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "PlotHelper.h"

void CollectResult()
{
   DataHelper DHFile("Database.dh");

   PsFileHelper PsFile("MinLLResult.ps");
   PsFile.AddTextPage("Attempt at setting limit");

   TGraph MinLLGraph;
   MinLLGraph.SetNameTitle("MinLLGraph", "MinLLGraph");
   
   TGraph DeltaMinLLGraph;
   DeltaMinLLGraph.SetNameTitle("DeltaMinLLGraph", "DeltaMinLLGraph");

   TGraph LimitGraph;
   LimitGraph.SetNameTitle("LimitGraph", "LimitGraph");
   LimitGraph.SetPoint(0, -50, 1.96);
   LimitGraph.SetPoint(1, 60, 1.96);

   TGraphErrors AlphaGraph;
   AlphaGraph.SetNameTitle("AlphaGraph", "AlphaGraph");
   
   TGraphErrors BetaGraph;
   BetaGraph.SetNameTitle("BetaGraph", "BetaGraph");

   TGraph CorrelationGraph;
   CorrelationGraph.SetNameTitle("Correlation", "Correlation");

   double MinNLL = 10000000;

   vector<string> States = DHFile.GetListOfKeys();
   for(int i = 0; i < (int)States.size(); i++)
      if(MinNLL > DHFile[States[i]]["MinNLL"].GetDouble())
         MinNLL = DHFile[States[i]]["MinNLL"].GetDouble();

   int EntryCount = 0;

   for(int i = 0; i < (int)States.size(); i++)
   {
      CorrelationGraph.SetPoint(i, DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["AlphaBetaCorrelation"].GetDouble());
      
      double Correlation = DHFile[States[i]]["AlphaBetaCorrelation"].GetDouble();
      if(Correlation > -0.5)
         continue;

      MinLLGraph.SetPoint(EntryCount, DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["MinNLL"].GetDouble());
      
      DeltaMinLLGraph.SetPoint(EntryCount, DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["MinNLL"].GetDouble() - MinNLL);

      AlphaGraph.SetPoint(EntryCount, DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["Alpha"].GetDouble());
      AlphaGraph.SetPointError(EntryCount, 0, DHFile[States[i]]["AlphaError"].GetDouble());
      
      BetaGraph.SetPoint(EntryCount, DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["Beta"].GetDouble());
      BetaGraph.SetPointError(EntryCount, 0, DHFile[States[i]]["BetaError"].GetDouble());
      
      EntryCount = EntryCount + 1;
   }

   MinLLGraph.SetMarkerStyle(20);
   PsFile.AddPlot(MinLLGraph, "ap");
   
   TCanvas DeltaMinLLCanvas("DeltaMinLLCanvas", "DeltaMinLLCanvas", 0, 0, 1024, 768);
   DeltaMinLLGraph.SetMarkerStyle(20);
   DeltaMinLLGraph.Draw("ap");
   LimitGraph.Draw("l");
   PsFile.AddCanvas(DeltaMinLLCanvas);

   AlphaGraph.SetMarkerStyle(20);
   AlphaGraph.SetLineWidth(2);
   PsFile.AddPlot(AlphaGraph, "ap");

   BetaGraph.SetMarkerStyle(20);
   BetaGraph.SetLineWidth(2);
   PsFile.AddPlot(BetaGraph, "ap");

   CorrelationGraph.SetMarkerStyle(20);
   PsFile.AddPlot(CorrelationGraph, "ap");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}





