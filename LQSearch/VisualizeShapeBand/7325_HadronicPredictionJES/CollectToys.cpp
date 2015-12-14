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
   TFile WFileSB_Down("WBandsSB_Down.root");
   TFile TFileSB_Down("TBandsSB_Down.root");
   TFile QFileSB_Down("QBandsSB_Down.root");
   TFile WFileS_Down("WBandsS_Down.root");
   TFile TFileS_Down("TBandsS_Down.root");
   TFile QFileS_Down("QBandsS_Down.root");
   TFile WFileSB_Up("WBandsSB_Up.root");
   TFile TFileSB_Up("TBandsSB_Up.root");
   TFile QFileSB_Up("QBandsSB_Up.root");
   TFile WFileS_Up("WBandsS_Up.root");
   TFile TFileS_Up("TBandsS_Up.root");
   TFile QFileS_Up("QBandsS_Up.root");

   TH1D HWSideBand_Down("HWSideBand_Down", "W prediction in side band (down)", 2000, 0, 2000);
   TH1D HTSideBand_Down("HTSideBand_Down", "Top prediction in side band (down)", 400, 0, 400);
   TH1D HQSideBand_Down("HQSideBand_Down", "QCD prediction in side band (down)", 2000, 0, 2000);
   TH1D HWSignal_Down("HWSignal_Down", "W prediction in signal region (down)", 2000, 0, 2000);
   TH1D HTSignal_Down("HTSignal_Down", "Top prediction in signal region (down)", 400, 0, 400);
   TH1D HQSignal_Down("HQSignal_Down", "QCD prediction in signal region (down)", 2000, 0, 2000);
   TH1D HWSideBand_Up("HWSideBand_Up", "W prediction in side band (up)", 2000, 0, 2000);
   TH1D HTSideBand_Up("HTSideBand_Up", "Top prediction in side band (up)", 400, 0, 400);
   TH1D HQSideBand_Up("HQSideBand_Up", "QCD prediction in side band (up)", 2000, 0, 2000);
   TH1D HWSignal_Up("HWSignal_Up", "W prediction in signal region (up)", 2000, 0, 2000);
   TH1D HTSignal_Up("HTSignal_Up", "Top prediction in signal region (up)", 400, 0, 400);
   TH1D HQSignal_Up("HQSignal_Up", "QCD prediction in signal region (up)", 2000, 0, 2000);

   for(int i = 1; i <= 100; i++)
   {
      RooDataSet *WToySB_Down = (RooDataSet *)WFileSB_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToySB_Down = (RooDataSet *)TFileSB_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToySB_Down = (RooDataSet *)QFileSB_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *WToyS_Down = (RooDataSet *)WFileS_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToyS_Down = (RooDataSet *)TFileS_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToyS_Down = (RooDataSet *)QFileS_Down.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *WToySB_Up = (RooDataSet *)WFileSB_Up.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToySB_Up = (RooDataSet *)TFileSB_Up.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToySB_Up = (RooDataSet *)QFileSB_Up.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *WToyS_Up = (RooDataSet *)WFileS_Up.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *TToyS_Up = (RooDataSet *)TFileS_Up.Get(Form("ToyDataSet_SmearAB_%d", i));
      RooDataSet *QToyS_Up = (RooDataSet *)QFileS_Up.Get(Form("ToyDataSet_SmearAB_%d", i));

      double WPrediction_Down = WToySB_Down->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double TPrediction_Down = TToySB_Down->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double QPrediction_Down = QToySB_Down->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double WSignal_Down = WToyS_Down->sumEntries("MR > 400 && R * R >= 0.50");
      double TSignal_Down = TToyS_Down->sumEntries("MR > 400 && R * R >= 0.50");
      double QSignal_Down = QToyS_Down->sumEntries("MR > 400 && R * R >= 0.50");
      double WPrediction_Up = WToySB_Up->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double TPrediction_Up = TToySB_Up->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double QPrediction_Up = QToySB_Up->sumEntries("MR > 400 && MR < 600 && R * R > 0.20 && R * R < 0.25");
      double WSignal_Up = WToyS_Up->sumEntries("MR > 400 && R * R >= 0.50");
      double TSignal_Up = TToyS_Up->sumEntries("MR > 400 && R * R >= 0.50");
      double QSignal_Up = QToyS_Up->sumEntries("MR > 400 && R * R >= 0.50");

      double TLowSignal_Down = TToyS_Down->sumEntries("MR > 400 && R * R < 0.20");
      double TLowSignal_Up = TToyS_Up->sumEntries("MR > 400 && R * R < 0.20");

      if(WPrediction_Down > 0)
         HWSideBand_Down.Fill(WPrediction_Down);
      if(WSignal_Down > 0)
         HWSignal_Down.Fill(WSignal_Down);
      if(TPrediction_Down > 0)
         HTSideBand_Down.Fill(TPrediction_Down);
      if(TLowSignal_Down > 70)
         HTSignal_Down.Fill(TSignal_Down);
      HQSideBand_Down.Fill(QPrediction_Down);
      HQSignal_Down.Fill(QSignal_Down);
      if(WPrediction_Up > 0)
         HWSideBand_Up.Fill(WPrediction_Up);
      if(WSignal_Up > 0)
         HWSignal_Up.Fill(WSignal_Up);
      if(TPrediction_Up > 0)
         HTSideBand_Up.Fill(TPrediction_Up);
      if(TLowSignal_Up > 70)
         HTSignal_Up.Fill(TSignal_Up);
      HQSideBand_Up.Fill(QPrediction_Up);
      HQSignal_Up.Fill(QSignal_Up);
   }

   PsFileHelper PsFile("FinalPredictionNumbers.ps");
   PsFile.AddTextPage("Final prediction numbers");

   PsFile.AddPlot(HWSideBand_Down, "", true);
   PsFile.AddPlot(HTSideBand_Down, "", true);
   PsFile.AddPlot(HQSideBand_Down, "", true);
   PsFile.AddPlot(HWSignal_Down, "", true);
   PsFile.AddPlot(HTSignal_Down, "", true);
   PsFile.AddPlot(HQSignal_Down, "", true);
   PsFile.AddPlot(HWSideBand_Up, "", true);
   PsFile.AddPlot(HTSideBand_Up, "", true);
   PsFile.AddPlot(HQSideBand_Up, "", true);
   PsFile.AddPlot(HWSignal_Up, "", true);
   PsFile.AddPlot(HTSignal_Up, "", true);
   PsFile.AddPlot(HQSignal_Up, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   QFileS_Down.Close();
   TFileS_Down.Close();
   WFileS_Down.Close();
   QFileSB_Down.Close();
   TFileSB_Down.Close();
   WFileSB_Down.Close();
   QFileS_Up.Close();
   TFileS_Up.Close();
   WFileS_Up.Close();
   QFileSB_Up.Close();
   TFileSB_Up.Close();
   WFileSB_Up.Close();

   return 0;
}





