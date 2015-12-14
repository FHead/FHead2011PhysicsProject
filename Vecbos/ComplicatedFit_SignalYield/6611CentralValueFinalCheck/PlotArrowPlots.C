#include <string>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TArrow.h"

#include "PlotHelper.h"
#include "DataHelper.h"

void PlotArrowPlots()
{
   PsFileHelper PsFile("Minima.ps");
   PsFile.AddTextPage("Check Z mumu alpha/beta fit central value");

   vector<string> Explanations;
   Explanations.push_back("Repeat fit many times with different initial values,");
   Explanations.push_back("      look at where they ends and what the minimum FCN is");
   Explanations.push_back("In the arrow plot each arrow is a pair of initial -> final values from one fit");
   Explanations.push_back("The next page shows the final alpha vs. minimum FCN.");
   Explanations.push_back("      (since it's in a valley, we don't need to make a 3D plot)");
   Explanations.push_back("We can see that the minimum at 5.8 is the one we want");
   Explanations.push_back("Note that there is a non-ideal local minimum around 4.7");
   Explanations.push_back("");
   Explanations.push_back("ps. fit done with Z2 PU smearing matrix");
   PsFile.AddTextPage(Explanations);

   DataHelper DHFile("CentralValue.dh");

   TCanvas Canvas;

   TGraph GAlphaVsMinFCN;
   GAlphaVsMinFCN.SetNameTitle("GAlphaVsMinFCN", "Alpha Vs Min FCN;Alpha;MinFCN");

   TH2D HRange("HRange", "Initial vs. final values of the fit;Alpha;Beta", 10, 3, 8, 10, -2, 2);
   HRange.SetStats(0);
   HRange.Draw();

   vector<TArrow *> Arrows;

   vector<string> States = DHFile.GetListOfKeys();
   for(int i = 0; i < (int)States.size(); i++)
   {
      if(DHFile[States[i]].Exist("AlphaStart") == false)
         continue;
      if(DHFile[States[i]].Exist("AlphaEnd") == false)
         continue;
      if(DHFile[States[i]].Exist("BetaStart") == false)
         continue;
      if(DHFile[States[i]].Exist("BetaEnd") == false)
         continue;
      if(DHFile[States[i]].Exist("MinFCN") == false)
         continue;

      double AlphaStart = DHFile[States[i]]["AlphaStart"].GetDouble();
      double AlphaEnd = DHFile[States[i]]["AlphaEnd"].GetDouble();
      double BetaStart = DHFile[States[i]]["BetaStart"].GetDouble();
      double BetaEnd = DHFile[States[i]]["BetaEnd"].GetDouble();
      double MinFCN = DHFile[States[i]]["MinFCN"].GetDouble();

      if(MinFCN >= -50000 && MinFCN < -46059)
      {
         GAlphaVsMinFCN.SetPoint(Arrows.size(), AlphaEnd, MinFCN);

         Arrows.push_back(new TArrow(AlphaStart, BetaStart, AlphaEnd, BetaEnd, 0.015, "|>"));
         Arrows[Arrows.size()-1]->SetAngle(20);
         Arrows[Arrows.size()-1]->Draw();
      }
   }

   PsFile.AddCanvas(Canvas);

   GAlphaVsMinFCN.SetMarkerStyle(4);
   PsFile.AddPlot(GAlphaVsMinFCN, "ap");

   for(int i = 0; i < (int)Arrows.size(); i++)
      delete Arrows[i];
   Arrows.clear();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




