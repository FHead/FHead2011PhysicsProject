#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "RooDataSet.h"
using namespace std;

#include "PlotHelper2.h"

int main()
{
   TFile WFile("WBands.root");
   TFile TopFile("TBands.root");
   TFile QFile("QBands.root");

   TH1D HWSideBand("HWSideBand", "W prediction in side band", 300, 0, 300);
   TH1D HTSideBand("HTSideBand", "Top prediction in side band", 300, 0, 300);
   TH1D HQSideBand("HQSideBand", "QCD prediction in side band", 300, 0, 300);
   TH1D HAllSideBand("HAllSideBand", "Total prediction in side band", 300, 0, 300);
   
   TH1D HWSignal("HWSignal", "W prediction in signal region", 600, 0, 600);
   TH1D HTSignal("HTSignal", "Top prediction in signal region", 600, 0, 600);
   TH1D HQSignal("HQSignal", "QCD prediction in signal region", 600, 0, 600);
   TH1D HAllSignal("HAllSignal", "Total prediction in signal region", 600, 0, 600);

   vector<double> TTbarSignal;

   for(int i = 1; i <= 1000; i++)
   {
      RooDataSet *WToy = (RooDataSet *)WFile.Get(Form("ToyDataSet_Fit_%d", i));
      RooDataSet *TToy = (RooDataSet *)TopFile.Get(Form("ToyDataSet_Fit_%d", i));
      RooDataSet *QToy = (RooDataSet *)QFile.Get(Form("ToyDataSet_Fit_%d", i));

      double WPrediction = WToy->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double TPrediction = TToy->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double QPrediction = QToy->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");

      double WSignal = WToy->sumEntries("MR > 400 && R * R > 0.25");
      double TSignal = TToy->sumEntries("MR > 400 && R * R > 0.25");
      double QSignal = QToy->sumEntries("MR > 400 && R * R > 0.25");

      HWSideBand.Fill(WPrediction);
      HTSideBand.Fill(TPrediction);
      HQSideBand.Fill(QPrediction);
      HAllSideBand.Fill(WPrediction + TPrediction + QPrediction);
      
      HWSignal.Fill(WSignal);
      HTSignal.Fill(TSignal);
      HQSignal.Fill(QSignal);
      HAllSignal.Fill(WSignal + TSignal + QSignal);

      TTbarSignal.push_back(TSignal);
   }

   PsFileHelper PsFile("ElectronBox.ps");
   PsFile.AddTextPage("Check in electron box....");

   PsFile.AddPlot(HWSideBand, "", true);
   PsFile.AddPlot(HTSideBand, "", true);
   PsFile.AddPlot(HQSideBand, "", true);
   PsFile.AddPlot(HAllSideBand, "", true);
   
   PsFile.AddPlot(HWSignal, "", true);
   PsFile.AddPlot(HTSignal, "", true);
   PsFile.AddPlot(HQSignal, "", true);
   PsFile.AddPlot(HAllSignal, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   QFile.Close();
   TopFile.Close();
   WFile.Close();

   sort(TTbarSignal.begin(), TTbarSignal.end());
   cout << TTbarSignal[317] << " " << TTbarSignal[500] << " " << TTbarSignal[683] << endl;

   return 0;
}





