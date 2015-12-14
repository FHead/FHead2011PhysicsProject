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
   TFile WFileSB("WBandsSB.root");
   TFile TFileSB("TBandsSB.root");
   TFile QFileSB("QBandsSB.root");
   TFile WFileS("WBandsS.root");
   TFile TFileS("TBandsS.root");
   TFile QFileS("QBandsS.root");

   TH1D HWSideBand("HWSideBand", "W prediction in side band", 2000, 0, 2000);
   TH1D HTSideBand("HTSideBand", "Top prediction in side band", 400, 0, 400);
   TH1D HQSideBand("HQSideBand", "QCD prediction in side band", 2000, 0, 2000);
   TH1D HAllSideBand("HAllSideBand", "Total prediction in side band", 2000, 0, 2000);

   TH1D HWSignal("HWSignal", "W prediction in signal region", 2000, 0, 2000);
   TH1D HTSignal("HTSignal", "Top prediction in signal region", 400, 0, 400);
   TH1D HQSignal("HQSignal", "QCD prediction in signal region", 2000, 0, 2000);
   TH1D HAllSignal("HAllSignal", "Total prediction in signal region", 2000, 0, 2000);

   for(int i = 1; i <= 1000; i++)
   {
      RooDataSet *WToySB = (RooDataSet *)WFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToySB = (RooDataSet *)TFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToySB = (RooDataSet *)QFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *WToyS = (RooDataSet *)WFileS.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToyS = (RooDataSet *)TFileS.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToyS = (RooDataSet *)QFileS.Get(Form("ToyDataSet_SmearAB_%d", i));

      double WPrediction = WToySB->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double TPrediction = TToySB->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double QPrediction = QToySB->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");

      double WSignal = WToyS->sumEntries("MR > 400 && R * R >= 0.42 && R * R < 0.50");
      double TSignal = TToyS->sumEntries("MR > 400 && R * R >= 0.42 && R * R < 0.50");
      double QSignal = QToyS->sumEntries("MR > 400 && R * R >= 0.42 && R * R < 0.50");

      if(WPrediction > 0)
         HWSideBand.Fill(WPrediction);
      if(WSignal > 0)
         HWSignal.Fill(WSignal);
      if(TPrediction > 0)
         HTSideBand.Fill(TPrediction);
      if(TSignal > 0 && TSignal < 250)
         HTSignal.Fill(TSignal);
      if(QPrediction > 0)
         HQSideBand.Fill(QPrediction);
      if(QSignal > 0)
         HQSignal.Fill(QSignal);
      if(WPrediction > 0 && TPrediction > 0 && QPrediction > 0)
         HAllSideBand.Fill(WPrediction + TPrediction + QPrediction);
      if(WSignal > 0 && TSignal > 0 && QSignal > 0 && TSignal < 250)
         HAllSignal.Fill(WSignal + TSignal + QSignal);
   }

   PsFileHelper PsFile("FinalPredictionNumbers.ps");
   PsFile.AddTextPage("Final prediction numbers");

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

   QFileS.Close();
   TFileS.Close();
   WFileS.Close();
   QFileSB.Close();
   TFileSB.Close();
   WFileSB.Close();

   return 0;
}





