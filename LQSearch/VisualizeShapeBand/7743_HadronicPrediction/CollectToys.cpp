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

   TH1D HWRestrictedSB("HWRestrictedSB", "W in restricted region (SB)", 2000, 0, 2000);
   TH1D HTRestrictedSB("HTRestrictedSB", "T in restricted region (SB)", 2000, 0, 2000);
   TH1D HQRestrictedSB("HQRestrictedSB", "Q in restricted region (SB)", 2000, 0, 2000);
   TH1D HWRestrictedS("HWRestrictedS", "W in restricted region (S)", 2000, 0, 2000);
   TH1D HTRestrictedS("HTRestrictedS", "T in restricted region (S)", 2000, 0, 2000);
   TH1D HQRestrictedS("HQRestrictedS", "Q in restricted region (S)", 2000, 0, 2000);

   TH1D HTLowSignal("HTLowSignal", "TLowSignal", 400, 0, 400);

   for(int i = 1; i <= 200; i++)
   {
      RooDataSet *WToySB = (RooDataSet *)WFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToySB = (RooDataSet *)TFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToySB = (RooDataSet *)QFileSB.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *WToyS = (RooDataSet *)WFileS.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToyS = (RooDataSet *)TFileS.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToyS = (RooDataSet *)QFileS.Get(Form("ToyDataSet_SmearAB_%d", i));

      double WPrediction = WToySB->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double TPrediction = TToySB->sumEntries("MRL > 400 && MRL < 600 && RL * RL > 0.20 && RL * RL < 0.25");
      double QPrediction = QToySB->sumEntries("MRL > 400 && MRL < 600 && RL * RL > 0.20 && RL * RL < 0.25");

      double WSignal = WToyS->sumEntries("MR > 400 && R * R >= 0.25");
      double TSignal = TToyS->sumEntries("MRL > 400 && RL * RL >= 0.25");
      double QSignal = QToyS->sumEntries("MRL > 400 && RL * RL >= 0.25");
      double TLowSignal = TToyS->sumEntries("MRL > 400 && RL * RL < 0.20");
      // cout << TLowSignal << endl;
      HTLowSignal.Fill(TLowSignal);

      double WRestrictedSB = WToySB->sumEntries("MR > 400 && R * R >= 0.20");
      double TRestrictedSB = TToySB->sumEntries("MRL > 400 && RL * RL >= 0.20");
      double QRestrictedSB = QToySB->sumEntries("MRL > 400 && RL * RL >= 0.20");
      double WRestrictedS = WToyS->sumEntries("MR > 400 && R * R >= 0.20");
      double TRestrictedS = TToyS->sumEntries("MRL > 400 && RL * RL >= 0.20");
      double QRestrictedS = QToyS->sumEntries("MRL > 400 && RL * RL >= 0.20");

      if(WPrediction > 0)
         HWSideBand.Fill(WPrediction);
      if(WSignal > 0)
         HWSignal.Fill(WSignal);
      if(TPrediction > 0)
         HTSideBand.Fill(TPrediction);
      if(TLowSignal > 70 && TLowSignal < 900)
         HTSignal.Fill(TSignal);
      HQSideBand.Fill(QPrediction);
      HQSignal.Fill(QSignal);
      if(WPrediction > 0 && TPrediction > 0 && QPrediction > 0)
         HAllSideBand.Fill(WPrediction + TPrediction + QPrediction);
      if(WSignal > 0 && TSignal > 0 && QSignal > 0 && TSignal < 900)
         HAllSignal.Fill(WSignal + TSignal + QSignal);

      HWRestrictedSB.Fill(WRestrictedSB);
      HTRestrictedSB.Fill(TRestrictedSB);
      HQRestrictedSB.Fill(QRestrictedSB);
      HWRestrictedS.Fill(WRestrictedS);
      HTRestrictedS.Fill(TRestrictedS);
      HQRestrictedS.Fill(QRestrictedS);
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

   PsFile.AddPlot(HTLowSignal, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   cout << "SideBand" << endl;
   cout << "W " << HWSideBand.GetMean() << " +- " << HWSideBand.GetRMS() << endl;
   cout << "T " << HTSideBand.GetMean() << " +- " << HTSideBand.GetRMS() << endl;
   cout << "Q " << HQSideBand.GetMean() << " +- " << HQSideBand.GetRMS() << endl;
   cout << "Signal" << endl;
   cout << "W " << HWSignal.GetMean() << " +- " << HWSignal.GetRMS() << endl;
   cout << "T " << HTSignal.GetMean() << " +- " << HTSignal.GetRMS() << endl;
   cout << "Q " << HQSignal.GetMean() << " +- " << HQSignal.GetRMS() << endl;

   cout << endl;

   cout << "SideBand, restricted region" << endl;
   cout << "W " << HWRestrictedSB.GetMean() << " +- " << HWRestrictedSB.GetRMS() << endl;
   cout << "T " << HTRestrictedSB.GetMean() << " +- " << HTRestrictedSB.GetRMS() << endl;
   cout << "Q " << HQRestrictedSB.GetMean() << " +- " << HQRestrictedSB.GetRMS() << endl;
   cout << "Signal, restricted region" << endl;
   cout << "W " << HWRestrictedS.GetMean() << " +- " << HWRestrictedS.GetRMS() << endl;
   cout << "T " << HTRestrictedS.GetMean() << " +- " << HTRestrictedS.GetRMS() << endl;
   cout << "Q " << HQRestrictedS.GetMean() << " +- " << HQRestrictedS.GetRMS() << endl;

   QFileS.Close();
   TFileS.Close();
   WFileS.Close();
   QFileSB.Close();
   TFileSB.Close();
   WFileSB.Close();

   return 0;
}





