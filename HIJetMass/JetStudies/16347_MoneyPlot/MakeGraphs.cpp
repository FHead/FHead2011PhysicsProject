#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TProfile2D.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
#include "ProgressBar.h"

#include "ReadTree.h"
#include "JetEnergyScale.h"

#define PI 3.14159265358979323846264338327950288479716939937510
#define MASSBINCOUNT 9
#define ZGBINCOUNT 10
#define DRBINCOUNT 15
#define PTPTBINCOUNT 50

#define TRIGGER_NONE 0
#define TRIGGER_100 1
#define TRIGGER_80 2
#define TRIGGER_60 3

int main(int argc, char *argv[]);
void InitializeVectors(vector<int> A[5][6], int Size);
void InitializeVectors(vector<double> A[5][6], int Size);
void InitializeVectors(vector<double> A[6], int Size);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   //////////////////
   // Usage string //
   //////////////////
   
   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " SDChoice IsMC=Y PTHat Tag" << endl;
      cerr << "Usage: " << argv[0] << " SDChoice IsMC=N Trigger=(100|80|60) Tag" << endl;
   }

   ////////////////////////
   // Sorting out inputs //
   ////////////////////////

   int SD = ((argv[1][0] == '0') ? 0 : 7);
   bool IsMC = ((argv[2][0] == 'Y') ? true : false);

   string Tag = argv[4];

   int TriggerSelection = TRIGGER_NONE;
   if(IsMC == false)
   {
      if(string(argv[3]) == "100")       TriggerSelection = TRIGGER_100;
      else if(string(argv[3]) == "80")   TriggerSelection = TRIGGER_80;
      else if(string(argv[3]) == "60")   TriggerSelection = TRIGGER_60;
   }

   double PTHatMin = ((IsMC == true) ? atof(argv[3]) : 0);
   string PTHatString = argv[3];

   double PTHatMax = 1000000;

   cout << "Running with SD = " << SD << ", MC = " << IsMC << endl;

   /////////////////////
   // Bin definitions //
   /////////////////////

   double CBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBinEdge[6+1] = {120, 140, 160, 180, 200, 300, 500};
   double MassBinEdge[MASSBINCOUNT+1] =
      {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26};
   double ZGBinEdge[ZGBINCOUNT+1] = {0};
   double DRBinEdge[DRBINCOUNT+1] = {0};
   double DR0BinEdge[DRBINCOUNT+1] = {0};
   double PTPTBinEdge[PTPTBINCOUNT+1] = {0};
   
   for(int i = 0; i <= ZGBINCOUNT; i++)     ZGBinEdge[i] = 0.5 / ZGBINCOUNT * i;
   for(int i = 0; i <= DRBINCOUNT; i++)     DRBinEdge[i] = 0.4 / DRBINCOUNT * i + 0.1;
   for(int i = 0; i <= DRBINCOUNT; i++)     DR0BinEdge[i] = 0.5 / DRBINCOUNT * i + 0.0;
   for(int i = 0; i <= PTPTBINCOUNT; i++)   PTPTBinEdge[i] = 1.0 / PTPTBINCOUNT * i + 0.0;

   /////////////////////////////////////
   // Prepare to get stuff from files //
   /////////////////////////////////////

   string FileNameData = "SampleBase/PlainTree/16325RhoM/AAData.root";
   string FileNameSmear = "SampleBase/MBSmearTree/16335RhoMAndFixFilterFix/Meow.root";
   FileNameSmear = "SampleBase/MBSmearTree/16335RhoMAlternateMB/RichMB.root";
   
   if(IsMC == true)
   {
      FileNameData = "AA6Dijet" + PTHatString + "Cymbal.root";
      FileNameSmear = "PP6Dijet" + PTHatString + ".root";

      if(PTHatMin <= 0)
      {
         FileNameData = "SampleBase/PlainTree/16354NoRhoM/AA6DijetCymbal.root";
         FileNameSmear = "SampleBase/MBSmearTree/16354NoRhoM/PP6DijetHIReco.root";
         PTHatMin = 100;
         PTHatMax = 10000000;
      }
   }
   if(IsMC == false && TriggerSelection != TRIGGER_NONE)
      FileNameData = "SampleBase/PlainTree/16325RhoM/AADataPrescale.root";
      
   ////////////////////
   // Get data trees //
   ////////////////////

   TFile FData(FileNameData.c_str());
   TFile FSmear(FileNameSmear.c_str());

   StraightTreeMessenger MData(FData, "T", IsMC, SD, atoi(argv[3]));
   SmearTreeMessenger MSmear(FSmear, "OutputTree", IsMC, SD);

   int DataEntryCount = MData.Tree->GetEntries() * 1.00;
   int SmearEntryCount = MSmear.Tree->GetEntries() * 1.00;

   ////////////////////////////
   // Get systematics graphs //
   ////////////////////////////

   TFile FDataSystematics(Form("CombinedSystematics_Data16213_%d.root", SD));
   TFile FSmearSystematics(Form("CombinedSystematics_All16213_%d.root", SD));

   TGraphAsymmErrors *DataError[5][6] = {{0}};
   TGraphAsymmErrors *SmearError[5][6] = {{0}};
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         DataError[i][j] =
            (TGraphAsymmErrors *)FDataSystematics.Get(Form("GRatio_C%d_P%d", i, j));
         SmearError[i][j] =
            (TGraphAsymmErrors *)FSmearSystematics.Get(Form("GRatio_C%d_P%d", i, j));
      }
   }

   ///////////////////
   // Setup outputs //
   ///////////////////

   TFile OutputFile(Form("Graphs_%s.root", Tag.c_str()), "RECREATE");

   PdfFileHelper PdfFile("QuickView_" + Tag + ".pdf");
   PdfFile.AddTextPage("Quick view of the result!");
   
   ///////////////////
   // Progress bars //
   ///////////////////

   ProgressBar BarData(cout, DataEntryCount);
   ProgressBar BarSmear(cout, SmearEntryCount);

   BarData.SetStyle(0);
   BarSmear.SetStyle(2);

   //////////////////////////////////
   // Preparation - Jet PT scaling //
   //////////////////////////////////

   JetEnergyScale JES;

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      BarData.PrintWithMod(300);

      MData.GetEntry(iE);

      if(MData.PassSelection() == false)       continue;
      if(MData.PassPTHat(PTHatMin, PTHatMax) == false)   continue;

      JES.Fill(MData.JetPT, MData.RawJetPT, MData.JetEta, MData.MCWeight);
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   JES.DoFit();

   MSmear.SetJES(&JES);

   /////////////////////////////////////
   // First step - get jet PT weights //
   /////////////////////////////////////

   vector<double> DataPT[5][6];
   InitializeVectors(DataPT, 50);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      BarData.PrintWithMod(300);

      MData.GetEntry(iE);

      if(MData.PassSelection() == false)       continue;
      if(MData.PassPTHat(PTHatMin, PTHatMax) == false)   continue;

      int CBin = MData.CentralityBin(CBinEdge, 5);
      int PTBin = MData.PTBin(PTBinEdge, 6);
      int JetBin = MData.JetBin(PTBinEdge, 6);

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      DataPT[CBin][PTBin][JetBin] += MData.MCWeight;
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   vector<double> SmearPT[5][6];
   InitializeVectors(SmearPT, 50);

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      BarSmear.Update(iE);
      BarSmear.PrintWithMod(300);

      MSmear.GetEntry(iE);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(CBinEdge, 5);
      int PTBin = MSmear.PTBin(PTBinEdge, 6);
      int JetBin = MSmear.JetBin(PTBinEdge, 6);

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      SmearPT[CBin][PTBin][JetBin] += MSmear.MCWeight;
   }
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();
   
   //////////////////////////////////////////
   // Second step - get centrality weights //
   //////////////////////////////////////////

   vector<double> DataCentralityBins[6];
   InitializeVectors(DataCentralityBins, 100);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      BarData.PrintWithMod(300);

      MData.GetEntry(iE);

      if(MData.PassSelection() == false)       continue;
      if(MData.PassPTHat(PTHatMin, PTHatMax) == false)   continue;

      int CBin = MData.CentralityBin(CBinEdge, 5);
      int PTBin = MData.PTBin(PTBinEdge, 6);
      int JetBin = MData.JetBin(PTBinEdge, 6);
      int Centrality = MData.CentralityInt();

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;
   
      DataCentralityBins[PTBin][Centrality] += MData.MCWeight;
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   vector<double> SmearCentralityBins[6];
   InitializeVectors(SmearCentralityBins, 100);

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      BarSmear.Update(iE);
      BarSmear.PrintWithMod(300);

      MSmear.GetEntry(iE);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(CBinEdge, 5);
      int PTBin = MSmear.PTBin(PTBinEdge, 6);
      int JetBin = MSmear.JetBin(PTBinEdge, 6);
      int Centrality = MSmear.CentralityInt();
      
      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      double JetWeight = DataPT[CBin][PTBin][JetBin] / SmearPT[CBin][PTBin][JetBin];

      SmearCentralityBins[PTBin][Centrality] += MSmear.MCWeight * JetWeight;
   }   
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();

   
   //////////////////////////////////
   // Third step - collect results //
   //////////////////////////////////

   double DataPreCutGrandTotal[5][6] = {{0}};
   double DataGrandTotal[5][6] = {{0}};
   double Data0GrandTotal[5][6] = {{0}};
   vector<double> DataCountMass[5][6];       InitializeVectors(DataCountMass, MASSBINCOUNT);
   vector<double> DataTotalMassX[5][6];      InitializeVectors(DataTotalMassX, MASSBINCOUNT);
   vector<double> DataTotalMass[5][6];       InitializeVectors(DataTotalMass, MASSBINCOUNT);
   vector<double> DataTotalMass2[5][6];      InitializeVectors(DataTotalMass2, MASSBINCOUNT);
   vector<double> DataTotalMassUp[5][6];     InitializeVectors(DataTotalMassUp, MASSBINCOUNT);
   vector<double> DataTotalMassDown[5][6];   InitializeVectors(DataTotalMassDown, MASSBINCOUNT);
   vector<double> DataCountZG[5][6];         InitializeVectors(DataCountZG, ZGBINCOUNT);
   vector<double> DataTotalZGX[5][6];        InitializeVectors(DataTotalZGX, ZGBINCOUNT);
   vector<double> DataTotalZG[5][6];         InitializeVectors(DataTotalZG, ZGBINCOUNT);
   vector<double> DataTotalZG2[5][6];        InitializeVectors(DataTotalZG2, ZGBINCOUNT);
   vector<double> DataCountDR[5][6];         InitializeVectors(DataCountDR, DRBINCOUNT);
   vector<double> DataTotalDRX[5][6];        InitializeVectors(DataTotalDRX, DRBINCOUNT);
   vector<double> DataTotalDR[5][6];         InitializeVectors(DataTotalDR, DRBINCOUNT);
   vector<double> DataTotalDR2[5][6];        InitializeVectors(DataTotalDR2, DRBINCOUNT);
   vector<double> DataCountPTPT[5][6];       InitializeVectors(DataCountPTPT, PTPTBINCOUNT);
   vector<double> DataTotalPTPTX[5][6];      InitializeVectors(DataTotalPTPTX, PTPTBINCOUNT);
   vector<double> DataTotalPTPT[5][6];       InitializeVectors(DataTotalPTPT, PTPTBINCOUNT);
   vector<double> DataTotalPTPT2[5][6];      InitializeVectors(DataTotalPTPT2, PTPTBINCOUNT);
   vector<double> Data0CountMass[5][6];      InitializeVectors(Data0CountMass, MASSBINCOUNT);
   vector<double> Data0TotalMassX[5][6];     InitializeVectors(Data0TotalMassX, MASSBINCOUNT);
   vector<double> Data0TotalMass[5][6];      InitializeVectors(Data0TotalMass, MASSBINCOUNT);
   vector<double> Data0TotalMass2[5][6];     InitializeVectors(Data0TotalMass2, MASSBINCOUNT);
   vector<double> Data0TotalMassUp[5][6];    InitializeVectors(Data0TotalMassUp, MASSBINCOUNT);
   vector<double> Data0TotalMassDown[5][6];  InitializeVectors(Data0TotalMassDown, MASSBINCOUNT);
   vector<double> Data0CountZG[5][6];        InitializeVectors(Data0CountZG, ZGBINCOUNT);
   vector<double> Data0TotalZGX[5][6];       InitializeVectors(Data0TotalZGX, ZGBINCOUNT);
   vector<double> Data0TotalZG[5][6];        InitializeVectors(Data0TotalZG, ZGBINCOUNT);
   vector<double> Data0TotalZG2[5][6];       InitializeVectors(Data0TotalZG2, ZGBINCOUNT);
   vector<double> Data0CountDR[5][6];        InitializeVectors(Data0CountDR, DRBINCOUNT);
   vector<double> Data0TotalDRX[5][6];       InitializeVectors(Data0TotalDRX, DRBINCOUNT);
   vector<double> Data0TotalDR[5][6];        InitializeVectors(Data0TotalDR, DRBINCOUNT);
   vector<double> Data0TotalDR2[5][6];       InitializeVectors(Data0TotalDR2, DRBINCOUNT);
   vector<double> Data0CountPTPT[5][6];      InitializeVectors(Data0CountPTPT, PTPTBINCOUNT);
   vector<double> Data0TotalPTPTX[5][6];     InitializeVectors(Data0TotalPTPTX, PTPTBINCOUNT);
   vector<double> Data0TotalPTPT[5][6];      InitializeVectors(Data0TotalPTPT, PTPTBINCOUNT);
   vector<double> Data0TotalPTPT2[5][6];     InitializeVectors(Data0TotalPTPT2, PTPTBINCOUNT);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      BarData.PrintWithMod(300);

      MData.GetEntry(iE);

      if(MData.PassSelection() == false)       continue;
      if(MData.PassPTHat(PTHatMin, PTHatMax) == false)   continue;

      int CBin = MData.CentralityBin(CBinEdge, 5);
      int PTBin = MData.PTBin(PTBinEdge, 6);
      int JetBin = MData.JetBin(PTBinEdge, 6);
      int Centrality = MData.CentralityInt();

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      int iMassB = GetBin(MData.SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iZGB = GetBin(MData.SDZG, ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(MData.SDRecoDR, DRBinEdge, DRBINCOUNT);
      int iDRB0 = GetBin(MData.SDRecoDR, DR0BinEdge, DRBINCOUNT);
      int iPTPT = GetBin(MData.PTPT, PTPTBinEdge, PTPTBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double TotalWeight = MData.MCWeight;
      double UpWeight = DataError[CBin][PTBin]->GetErrorYhigh(MData.SysBin);
      double DownWeight = -DataError[CBin][PTBin]->GetErrorYlow(MData.SysBin);

      if(MData.SDRecoDR > 0.0)
         DataPreCutGrandTotal[CBin][PTBin] += TotalWeight;
      if(MData.SDRecoDR > 0.1)
      {
         DataCountMass     [CBin][PTBin][iMassB] += TotalWeight;
         DataTotalMassX    [CBin][PTBin][iMassB] += MData.SDMassRatio * TotalWeight;
         DataTotalMass     [CBin][PTBin][iMassB] += TotalWeight;
         DataTotalMass2    [CBin][PTBin][iMassB] += TotalWeight * TotalWeight;
         DataTotalMassUp   [CBin][PTBin][iMassB] += TotalWeight * exp(UpWeight);
         DataTotalMassDown [CBin][PTBin][iMassB] += TotalWeight * exp(DownWeight);
         DataCountZG       [CBin][PTBin][iZGB]   += TotalWeight;
         DataTotalZGX      [CBin][PTBin][iZGB]   += MData.SDZG * TotalWeight;
         DataTotalZG       [CBin][PTBin][iZGB]   += TotalWeight;
         DataTotalZG2      [CBin][PTBin][iZGB]   += TotalWeight * TotalWeight;
         DataCountDR       [CBin][PTBin][iDRB]   += TotalWeight;
         DataTotalDRX      [CBin][PTBin][iDRB]   += MData.SDRecoDR * TotalWeight;
         DataTotalDR       [CBin][PTBin][iDRB]   += TotalWeight;
         DataTotalDR2      [CBin][PTBin][iDRB]   += TotalWeight * TotalWeight;
         DataCountPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         DataTotalPTPTX    [CBin][PTBin][iPTPT]  += MData.PTPT * TotalWeight;
         DataTotalPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         DataTotalPTPT2    [CBin][PTBin][iPTPT]  += TotalWeight * TotalWeight;
         DataGrandTotal    [CBin][PTBin]         += TotalWeight;
      }
      if(MData.SDRecoDR > 0.1 && MData.SDRecoDR < 0.25)
      {
         Data0CountMass     [CBin][PTBin][iMassB] += TotalWeight;
         Data0TotalMassX    [CBin][PTBin][iMassB] += MData.SDMassRatio * TotalWeight;
         Data0TotalMass     [CBin][PTBin][iMassB] += TotalWeight;
         Data0TotalMass2    [CBin][PTBin][iMassB] += TotalWeight * TotalWeight;
         Data0TotalMassUp   [CBin][PTBin][iMassB] += TotalWeight * exp(UpWeight);
         Data0TotalMassDown [CBin][PTBin][iMassB] += TotalWeight * exp(DownWeight);
         Data0CountZG       [CBin][PTBin][iZGB]   += TotalWeight;
         Data0TotalZGX      [CBin][PTBin][iZGB]   += MData.SDZG * TotalWeight;
         Data0TotalZG       [CBin][PTBin][iZGB]   += TotalWeight;
         Data0TotalZG2      [CBin][PTBin][iZGB]   += TotalWeight * TotalWeight;
         Data0CountDR       [CBin][PTBin][iDRB0]  += TotalWeight;
         Data0TotalDRX      [CBin][PTBin][iDRB0]  += MData.SDRecoDR * TotalWeight;
         Data0TotalDR       [CBin][PTBin][iDRB0]  += TotalWeight;
         Data0TotalDR2      [CBin][PTBin][iDRB0]  += TotalWeight * TotalWeight;
         Data0CountPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         Data0TotalPTPTX    [CBin][PTBin][iPTPT]  += MData.PTPT * TotalWeight;
         Data0TotalPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         Data0TotalPTPT2    [CBin][PTBin][iPTPT]  += TotalWeight * TotalWeight;
         Data0GrandTotal    [CBin][PTBin]         += TotalWeight;
      }
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   double SmearPreCutGrandTotal[5][6] = {{0}};
   double SmearGrandTotal[5][6] = {{0}};
   double Smear0GrandTotal[5][6] = {{0}};
   vector<double> SmearCountMass[5][6];       InitializeVectors(SmearCountMass, MASSBINCOUNT);
   vector<double> SmearTotalMassX[5][6];      InitializeVectors(SmearTotalMassX, MASSBINCOUNT);
   vector<double> SmearTotalMass[5][6];       InitializeVectors(SmearTotalMass, MASSBINCOUNT);
   vector<double> SmearTotalMass2[5][6];      InitializeVectors(SmearTotalMass2, MASSBINCOUNT);
   vector<double> SmearTotalMassUp[5][6];     InitializeVectors(SmearTotalMassUp, MASSBINCOUNT);
   vector<double> SmearTotalMassDown[5][6];   InitializeVectors(SmearTotalMassDown, MASSBINCOUNT);
   vector<double> SmearCountZG[5][6];         InitializeVectors(SmearCountZG, ZGBINCOUNT);
   vector<double> SmearTotalZGX[5][6];        InitializeVectors(SmearTotalZGX, ZGBINCOUNT);
   vector<double> SmearTotalZG[5][6];         InitializeVectors(SmearTotalZG, ZGBINCOUNT);
   vector<double> SmearTotalZG2[5][6];        InitializeVectors(SmearTotalZG2, ZGBINCOUNT);
   vector<double> SmearCountDR[5][6];         InitializeVectors(SmearCountDR, DRBINCOUNT);
   vector<double> SmearTotalDRX[5][6];        InitializeVectors(SmearTotalDRX, DRBINCOUNT);
   vector<double> SmearTotalDR[5][6];         InitializeVectors(SmearTotalDR, DRBINCOUNT);
   vector<double> SmearTotalDR2[5][6];        InitializeVectors(SmearTotalDR2, DRBINCOUNT);
   vector<double> SmearCountPTPT[5][6];       InitializeVectors(SmearCountPTPT, PTPTBINCOUNT);
   vector<double> SmearTotalPTPTX[5][6];      InitializeVectors(SmearTotalPTPTX, PTPTBINCOUNT);
   vector<double> SmearTotalPTPT[5][6];       InitializeVectors(SmearTotalPTPT, PTPTBINCOUNT);
   vector<double> SmearTotalPTPT2[5][6];      InitializeVectors(SmearTotalPTPT2, PTPTBINCOUNT);
   vector<double> Smear0CountMass[5][6];      InitializeVectors(Smear0CountMass, MASSBINCOUNT);
   vector<double> Smear0TotalMassX[5][6];     InitializeVectors(Smear0TotalMassX, MASSBINCOUNT);
   vector<double> Smear0TotalMass[5][6];      InitializeVectors(Smear0TotalMass, MASSBINCOUNT);
   vector<double> Smear0TotalMass2[5][6];     InitializeVectors(Smear0TotalMass2, MASSBINCOUNT);
   vector<double> Smear0TotalMassUp[5][6];    InitializeVectors(Smear0TotalMassUp, MASSBINCOUNT);
   vector<double> Smear0TotalMassDown[5][6];  InitializeVectors(Smear0TotalMassDown, MASSBINCOUNT);
   vector<double> Smear0CountZG[5][6];        InitializeVectors(Smear0CountZG, ZGBINCOUNT);
   vector<double> Smear0TotalZGX[5][6];       InitializeVectors(Smear0TotalZGX, ZGBINCOUNT);
   vector<double> Smear0TotalZG[5][6];        InitializeVectors(Smear0TotalZG, ZGBINCOUNT);
   vector<double> Smear0TotalZG2[5][6];       InitializeVectors(Smear0TotalZG2, ZGBINCOUNT);
   vector<double> Smear0CountDR[5][6];        InitializeVectors(Smear0CountDR, DRBINCOUNT);
   vector<double> Smear0TotalDRX[5][6];       InitializeVectors(Smear0TotalDRX, DRBINCOUNT);
   vector<double> Smear0TotalDR[5][6];        InitializeVectors(Smear0TotalDR, DRBINCOUNT);
   vector<double> Smear0TotalDR2[5][6];       InitializeVectors(Smear0TotalDR2, DRBINCOUNT);
   vector<double> Smear0CountPTPT[5][6];      InitializeVectors(Smear0CountPTPT, PTPTBINCOUNT);
   vector<double> Smear0TotalPTPTX[5][6];     InitializeVectors(Smear0TotalPTPTX, PTPTBINCOUNT);
   vector<double> Smear0TotalPTPT[5][6];      InitializeVectors(Smear0TotalPTPT, PTPTBINCOUNT);
   vector<double> Smear0TotalPTPT2[5][6];     InitializeVectors(Smear0TotalPTPT2, PTPTBINCOUNT);

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      BarSmear.Update(iE);
      BarSmear.PrintWithMod(300);

      MSmear.GetEntry(iE);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(CBinEdge, 5);
      int PTBin = MSmear.PTBin(PTBinEdge, 6);
      int JetBin = MSmear.JetBin(PTBinEdge, 6);
      int Centrality = MSmear.CentralityInt();
      
      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      double JetWeight = DataPT[CBin][PTBin][JetBin] / SmearPT[CBin][PTBin][JetBin];

      int iMassB = GetBin(MSmear.SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iZGB = GetBin(MSmear.SDZG, ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(MSmear.SDRecoDR, DRBinEdge, DRBINCOUNT);
      int iDRB0 = GetBin(MSmear.SDRecoDR, DR0BinEdge, DRBINCOUNT);
      int iPTPT = GetBin(MSmear.PTPT, PTPTBinEdge, PTPTBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double CentralityWeight = DataCentralityBins[PTBin][Centrality]
         / SmearCentralityBins[PTBin][Centrality];

      double TotalWeight = MSmear.MCWeight * JetWeight * CentralityWeight;
      // double TotalWeight = MSmear.MCWeight;
      double UpWeight = SmearError[CBin][PTBin]->GetErrorYhigh(MSmear.SysBin);
      double DownWeight = -SmearError[CBin][PTBin]->GetErrorYlow(MSmear.SysBin);

      if(MSmear.SDRecoDR > 0.0)
         SmearPreCutGrandTotal[CBin][PTBin] += TotalWeight;
      if(MSmear.SDRecoDR > 0.1)
      {
         SmearCountMass     [CBin][PTBin][iMassB] += TotalWeight;
         SmearTotalMassX    [CBin][PTBin][iMassB] += MSmear.SDMassRatio * TotalWeight;
         SmearTotalMass     [CBin][PTBin][iMassB] += TotalWeight;
         SmearTotalMass2    [CBin][PTBin][iMassB] += TotalWeight * TotalWeight;
         SmearTotalMassUp   [CBin][PTBin][iMassB] += TotalWeight * exp(UpWeight);
         SmearTotalMassDown [CBin][PTBin][iMassB] += TotalWeight * exp(DownWeight);
         SmearCountZG       [CBin][PTBin][iZGB]   += TotalWeight;
         SmearTotalZGX      [CBin][PTBin][iZGB]   += MSmear.SDZG * TotalWeight;
         SmearTotalZG       [CBin][PTBin][iZGB]   += TotalWeight;
         SmearTotalZG2      [CBin][PTBin][iZGB]   += TotalWeight * TotalWeight;
         SmearCountDR       [CBin][PTBin][iDRB]   += TotalWeight;
         SmearTotalDRX      [CBin][PTBin][iDRB]   += MSmear.SDRecoDR * TotalWeight;
         SmearTotalDR       [CBin][PTBin][iDRB]   += TotalWeight;
         SmearTotalDR2      [CBin][PTBin][iDRB]   += TotalWeight * TotalWeight;
         SmearCountPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         SmearTotalPTPTX    [CBin][PTBin][iPTPT]  += MSmear.PTPT * TotalWeight;
         SmearTotalPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         SmearTotalPTPT2    [CBin][PTBin][iPTPT]  += TotalWeight * TotalWeight;
         SmearGrandTotal    [CBin][PTBin]         += TotalWeight;
      }
      if(MSmear.SDRecoDR > 0.1 && MSmear.SDRecoDR < 0.25)
      {
         Smear0CountMass     [CBin][PTBin][iMassB] += TotalWeight;
         Smear0TotalMassX    [CBin][PTBin][iMassB] += MSmear.SDMassRatio * TotalWeight;
         Smear0TotalMass     [CBin][PTBin][iMassB] += TotalWeight;
         Smear0TotalMass2    [CBin][PTBin][iMassB] += TotalWeight * TotalWeight;
         Smear0TotalMassUp   [CBin][PTBin][iMassB] += TotalWeight * exp(UpWeight);
         Smear0TotalMassDown [CBin][PTBin][iMassB] += TotalWeight * exp(DownWeight);
         Smear0CountZG       [CBin][PTBin][iZGB]   += TotalWeight;
         Smear0TotalZGX      [CBin][PTBin][iZGB]   += MSmear.SDZG * TotalWeight;
         Smear0TotalZG       [CBin][PTBin][iZGB]   += TotalWeight;
         Smear0TotalZG2      [CBin][PTBin][iZGB]   += TotalWeight * TotalWeight;
         Smear0CountDR       [CBin][PTBin][iDRB0]  += TotalWeight;
         Smear0TotalDRX      [CBin][PTBin][iDRB0]  += MSmear.SDRecoDR * TotalWeight;
         Smear0TotalDR       [CBin][PTBin][iDRB0]  += TotalWeight;
         Smear0TotalDR2      [CBin][PTBin][iDRB0]  += TotalWeight * TotalWeight;
         Smear0CountPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         Smear0TotalPTPTX    [CBin][PTBin][iPTPT]  += MSmear.PTPT * TotalWeight;
         Smear0TotalPTPT     [CBin][PTBin][iPTPT]  += TotalWeight;
         Smear0TotalPTPT2    [CBin][PTBin][iPTPT]  += TotalWeight * TotalWeight;
         Smear0GrandTotal    [CBin][PTBin]         += TotalWeight;
      }
   }
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();


   ////////////////////////
   // Build final graphs //
   ////////////////////////

   for(int CBin = 0; CBin < 5; CBin++)
   {
      for(int PTBin = 0; PTBin < 6; PTBin++)
      {
         PdfFile.AddTextPage(Form("C %.02f-%.02f, PT %.0f-%.0f", CBinEdge[CBin], CBinEdge[CBin+1], PTBinEdge[PTBin], PTBinEdge[PTBin+1]));

         TGraphAsymmErrors GMassData, GMassSmear, GMassDataSys, GMassSmearSys, GZGData, GZGSmear, GDRData, GDRSmear, GPTPTData, GPTPTSmear;
         TGraphAsymmErrors GMassData0, GMassSmear0, GMassDataSys0, GMassSmearSys0, GZGData0, GZGSmear0, GDRData0, GDRSmear0, GPTPTData0, GPTPTSmear0;

         GMassData.SetNameTitle(Form("MassData_%d_%d", CBin, PTBin), "");
         GMassDataSys.SetNameTitle(Form("MassDataSys_%d_%d", CBin, PTBin), "");
         GMassSmear.SetNameTitle(Form("MassSmear_%d_%d", CBin, PTBin), "");
         GMassSmearSys.SetNameTitle(Form("MassSmearSys_%d_%d", CBin, PTBin), "");
         GZGData.SetNameTitle(Form("ZGData_%d_%d", CBin, PTBin), "");
         GZGSmear.SetNameTitle(Form("ZGSmear_%d_%d", CBin, PTBin), "");
         GDRData.SetNameTitle(Form("DRData_%d_%d", CBin, PTBin), "");
         GDRSmear.SetNameTitle(Form("DRSmear_%d_%d", CBin, PTBin), "");
         GPTPTData.SetNameTitle(Form("PTPTData_%d_%d", CBin, PTBin), "");
         GPTPTSmear.SetNameTitle(Form("PTPTSmear_%d_%d", CBin, PTBin), "");
         GMassData0.SetNameTitle(Form("MassData0_%d_%d", CBin, PTBin), "");
         GMassDataSys0.SetNameTitle(Form("MassDataSys0_%d_%d", CBin, PTBin), "");
         GMassSmear0.SetNameTitle(Form("MassSmear0_%d_%d", CBin, PTBin), "");
         GMassSmearSys0.SetNameTitle(Form("MassSmearSys0_%d_%d", CBin, PTBin), "");
         GZGData0.SetNameTitle(Form("ZGData0_%d_%d", CBin, PTBin), "");
         GZGSmear0.SetNameTitle(Form("ZGSmear0_%d_%d", CBin, PTBin), "");
         GDRData0.SetNameTitle(Form("DRData0_%d_%d", CBin, PTBin), "");
         GDRSmear0.SetNameTitle(Form("DRSmear0_%d_%d", CBin, PTBin), "");
         GPTPTData0.SetNameTitle(Form("PTPTData0_%d_%d", CBin, PTBin), "");
         GPTPTSmear0.SetNameTitle(Form("PTPTSmear0_%d_%d", CBin, PTBin), "");

         GMassData.SetMarkerStyle(20);
         GMassSmear.SetMarkerStyle(20);
         GMassDataSys.SetMarkerStyle(20);
         GMassSmearSys.SetMarkerStyle(20);
         GZGData.SetMarkerStyle(20);
         GZGSmear.SetMarkerStyle(20);
         GDRData.SetMarkerStyle(20);
         GDRSmear.SetMarkerStyle(20);
         GPTPTData.SetMarkerStyle(20);
         GPTPTSmear.SetMarkerStyle(20);
         GMassData0.SetMarkerStyle(20);
         GMassSmear0.SetMarkerStyle(20);
         GMassDataSys0.SetMarkerStyle(20);
         GMassSmearSys0.SetMarkerStyle(20);
         GZGData0.SetMarkerStyle(20);
         GZGSmear0.SetMarkerStyle(20);
         GDRData0.SetMarkerStyle(20);
         GDRSmear0.SetMarkerStyle(20);
         GPTPTData0.SetMarkerStyle(20);
         GPTPTSmear0.SetMarkerStyle(20);
         GMassData.SetMarkerSize(0.7);
         GMassSmear.SetMarkerSize(0.7);
         GMassDataSys.SetMarkerSize(0.7);
         GMassSmearSys.SetMarkerSize(0.7);
         GZGData.SetMarkerSize(0.7);
         GZGSmear.SetMarkerSize(0.7);
         GDRData.SetMarkerSize(0.7);
         GDRSmear.SetMarkerSize(0.7);
         GPTPTData.SetMarkerSize(0.7);
         GPTPTSmear.SetMarkerSize(0.7);
         GMassData0.SetMarkerSize(0.7);
         GMassSmear0.SetMarkerSize(0.7);
         GMassDataSys0.SetMarkerSize(0.7);
         GMassSmearSys0.SetMarkerSize(0.7);
         GZGData0.SetMarkerSize(0.7);
         GZGSmear0.SetMarkerSize(0.7);
         GDRData0.SetMarkerSize(0.7);
         GDRSmear0.SetMarkerSize(0.7);
         GPTPTData0.SetMarkerSize(0.7);
         GPTPTSmear0.SetMarkerSize(0.7);

         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double Factor = 1 / DataGrandTotal[CBin][PTBin];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = DataTotalMassX[CBin][PTBin][i] / DataCountMass[CBin][PTBin][i];
            double Mass = DataTotalMass[CBin][PTBin][i] / MassBinSize * Factor;
            double MassRMS = sqrt(DataTotalMass2[CBin][PTBin][i]) / MassBinSize * Factor;
            double MassUp = DataTotalMassUp[CBin][PTBin][i] / MassBinSize * Factor;
            double MassDown = DataTotalMassDown[CBin][PTBin][i] / MassBinSize * Factor;

            GMassData.SetPoint(i, MassX, Mass);
            GMassData.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys.SetPoint(i, MassX, Mass);
            GMassDataSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double Factor = 1 / DataGrandTotal[CBin][PTBin];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = DataTotalZGX[CBin][PTBin][i] / DataCountZG[CBin][PTBin][i];
            double ZG = DataTotalZG[CBin][PTBin][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(DataTotalZG2[CBin][PTBin][i]) / ZGBinSize * Factor;

            GZGData.SetPoint(i, ZGX, ZG);
            GZGData.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double Factor = 1 / DataGrandTotal[CBin][PTBin];

            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = DataTotalDRX[CBin][PTBin][i] / DataCountDR[CBin][PTBin][i];
            double DR = DataTotalDR[CBin][PTBin][i] / DRBinSize * Factor;
            double DRRMS = sqrt(DataTotalDR2[CBin][PTBin][i]) / DRBinSize * Factor;

            GDRData.SetPoint(i, DRX, DR);
            GDRData.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
         for(int i = 0; i < PTPTBINCOUNT; i++)
         {
            double Factor = 1 / DataGrandTotal[CBin][PTBin];

            double PTPTBinSize = PTPTBinEdge[i+1] - PTPTBinEdge[i];
            double PTPTX = DataTotalPTPTX[CBin][PTBin][i] / DataCountPTPT[CBin][PTBin][i];
            double PTPT = DataTotalPTPT[CBin][PTBin][i] / PTPTBinSize * Factor;
            double PTPTRMS = sqrt(DataTotalPTPT2[CBin][PTBin][i]) / PTPTBinSize * Factor;

            GPTPTData.SetPoint(i, PTPTX, PTPT);
            GPTPTData.SetPointError(i, PTPTX - PTPTBinEdge[i], PTPTBinEdge[i+1] - PTPTX, PTPTRMS, PTPTRMS);
         }
        
         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double Factor = 1 / Data0GrandTotal[CBin][PTBin];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = Data0TotalMassX[CBin][PTBin][i] / Data0CountMass[CBin][PTBin][i];
            double Mass = Data0TotalMass[CBin][PTBin][i] / MassBinSize * Factor;
            double MassRMS = sqrt(Data0TotalMass2[CBin][PTBin][i]) / MassBinSize * Factor;
            double MassUp = Data0TotalMassUp[CBin][PTBin][i] / MassBinSize * Factor;
            double MassDown = Data0TotalMassDown[CBin][PTBin][i] / MassBinSize * Factor;

            GMassData0.SetPoint(i, MassX, Mass);
            GMassData0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys0.SetPoint(i, MassX, Mass);
            GMassDataSys0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double Factor = 1 / Data0GrandTotal[CBin][PTBin];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = Data0TotalZGX[CBin][PTBin][i] / Data0CountZG[CBin][PTBin][i];
            double ZG = Data0TotalZG[CBin][PTBin][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(Data0TotalZG2[CBin][PTBin][i]) / ZGBinSize * Factor;

            GZGData0.SetPoint(i, ZGX, ZG);
            GZGData0.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double Factor = 1 / Data0GrandTotal[CBin][PTBin];

            double DRBinSize = DR0BinEdge[i+1] - DR0BinEdge[i];
            double DRX = Data0TotalDRX[CBin][PTBin][i] / Data0CountDR[CBin][PTBin][i];
            double DR = Data0TotalDR[CBin][PTBin][i] / DRBinSize * Factor;
            double DRRMS = sqrt(Data0TotalDR2[CBin][PTBin][i]) / DRBinSize * Factor;

            GDRData0.SetPoint(i, DRX, DR);
            GDRData0.SetPointError(i, DRX - DR0BinEdge[i], DR0BinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
         for(int i = 0; i < PTPTBINCOUNT; i++)
         {
            double Factor = 1 / Data0GrandTotal[CBin][PTBin];

            double PTPTBinSize = PTPTBinEdge[i+1] - PTPTBinEdge[i];
            double PTPTX = Data0TotalPTPTX[CBin][PTBin][i] / Data0CountPTPT[CBin][PTBin][i];
            double PTPT = Data0TotalPTPT[CBin][PTBin][i] / PTPTBinSize * Factor;
            double PTPTRMS = sqrt(Data0TotalPTPT2[CBin][PTBin][i]) / PTPTBinSize * Factor;

            GPTPTData0.SetPoint(i, PTPTX, PTPT);
            GPTPTData0.SetPointError(i, PTPTX - PTPTBinEdge[i], PTPTBinEdge[i+1] - PTPTX, PTPTRMS, PTPTRMS);
         }
  
         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double Factor = 1 / SmearGrandTotal[CBin][PTBin];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = SmearTotalMassX[CBin][PTBin][i] / SmearCountMass[CBin][PTBin][i];
            double Mass = SmearTotalMass[CBin][PTBin][i] / MassBinSize * Factor;
            double MassRMS = sqrt(SmearTotalMass2[CBin][PTBin][i]) / MassBinSize * Factor;
            double MassUp = SmearTotalMassUp[CBin][PTBin][i] / MassBinSize * Factor;
            double MassDown = SmearTotalMassDown[CBin][PTBin][i] / MassBinSize * Factor;

            GMassSmear.SetPoint(i, MassX, Mass);
            GMassSmear.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassSmearSys.SetPoint(i, MassX, Mass);
            GMassSmearSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double Factor = 1 / SmearGrandTotal[CBin][PTBin];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = SmearTotalZGX[CBin][PTBin][i] / SmearCountZG[CBin][PTBin][i];
            double ZG = SmearTotalZG[CBin][PTBin][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(SmearTotalZG2[CBin][PTBin][i]) / ZGBinSize * Factor;

            GZGSmear.SetPoint(i, ZGX, ZG);
            GZGSmear.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double Factor = 1 / SmearGrandTotal[CBin][PTBin];
            
            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = SmearTotalDRX[CBin][PTBin][i] / SmearCountDR[CBin][PTBin][i];
            double DR = SmearTotalDR[CBin][PTBin][i] / DRBinSize * Factor;
            double DRRMS = sqrt(SmearTotalDR2[CBin][PTBin][i]) / DRBinSize * Factor;

            GDRSmear.SetPoint(i, DRX, DR);
            GDRSmear.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
         for(int i = 0; i < PTPTBINCOUNT; i++)
         {
            double Factor = 1 / SmearGrandTotal[CBin][PTBin];
            
            double PTPTBinSize = PTPTBinEdge[i+1] - PTPTBinEdge[i];
            double PTPTX = SmearTotalPTPTX[CBin][PTBin][i] / SmearCountPTPT[CBin][PTBin][i];
            double PTPT = SmearTotalPTPT[CBin][PTBin][i] / PTPTBinSize * Factor;
            double PTPTRMS = sqrt(SmearTotalPTPT2[CBin][PTBin][i]) / PTPTBinSize * Factor;

            GPTPTSmear.SetPoint(i, PTPTX, PTPT);
            GPTPTSmear.SetPointError(i, PTPTX - PTPTBinEdge[i], PTPTBinEdge[i+1] - PTPTX, PTPTRMS, PTPTRMS);
         }

         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double Factor = 1 / Smear0GrandTotal[CBin][PTBin];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = Smear0TotalMassX[CBin][PTBin][i] / Smear0CountMass[CBin][PTBin][i];
            double Mass = Smear0TotalMass[CBin][PTBin][i] / MassBinSize * Factor;
            double MassRMS = sqrt(Smear0TotalMass2[CBin][PTBin][i]) / MassBinSize * Factor;
            double MassUp = Smear0TotalMassUp[CBin][PTBin][i] / MassBinSize * Factor;
            double MassDown = Smear0TotalMassDown[CBin][PTBin][i] / MassBinSize * Factor;

            GMassSmear0.SetPoint(i, MassX, Mass);
            GMassSmear0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassSmearSys0.SetPoint(i, MassX, Mass);
            GMassSmearSys0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double Factor = 1 / Smear0GrandTotal[CBin][PTBin];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = Smear0TotalZGX[CBin][PTBin][i] / Smear0CountZG[CBin][PTBin][i];
            double ZG = Smear0TotalZG[CBin][PTBin][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(Smear0TotalZG2[CBin][PTBin][i]) / ZGBinSize * Factor;

            GZGSmear0.SetPoint(i, ZGX, ZG);
            GZGSmear0.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double Factor = 1 / Smear0GrandTotal[CBin][PTBin];

            double DRBinSize = DR0BinEdge[i+1] - DR0BinEdge[i];
            double DRX = Smear0TotalDRX[CBin][PTBin][i] / Smear0CountDR[CBin][PTBin][i];
            double DR = Smear0TotalDR[CBin][PTBin][i] / DRBinSize * Factor;
            double DRRMS = sqrt(Smear0TotalDR2[CBin][PTBin][i]) / DRBinSize * Factor;

            GDRSmear0.SetPoint(i, DRX, DR);
            GDRSmear0.SetPointError(i, DRX - DR0BinEdge[i], DR0BinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
         for(int i = 0; i < PTPTBINCOUNT; i++)
         {
            double Factor = 1 / Smear0GrandTotal[CBin][PTBin];

            double PTPTBinSize = PTPTBinEdge[i+1] - PTPTBinEdge[i];
            double PTPTX = Smear0TotalPTPTX[CBin][PTBin][i] / Smear0CountPTPT[CBin][PTBin][i];
            double PTPT = Smear0TotalPTPT[CBin][PTBin][i] / PTPTBinSize * Factor;
            double PTPTRMS = sqrt(Smear0TotalPTPT2[CBin][PTBin][i]) / PTPTBinSize * Factor;

            GPTPTSmear0.SetPoint(i, PTPTX, PTPT);
            GPTPTSmear0.SetPointError(i, PTPTX - PTPTBinEdge[i], PTPTBinEdge[i+1] - PTPTX, PTPTRMS, PTPTRMS);
         }

         GMassData.Write();
         GMassSmear.Write();
         GMassDataSys.Write();
         GMassSmearSys.Write();
         GZGData.Write();
         GZGSmear.Write();
         GDRData.Write();
         GDRSmear.Write();
         GPTPTData.Write();
         GPTPTSmear.Write();
         GMassData0.Write();
         GMassSmear0.Write();
         GMassDataSys0.Write();
         GMassSmearSys0.Write();
         GZGData0.Write();
         GZGSmear0.Write();
         GDRData0.Write();
         GDRSmear0.Write();
         GPTPTData0.Write();
         GPTPTSmear0.Write();

         TLegend Legend(0.5, 0.8, 0.8, 0.5);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetFillStyle(0);
         Legend.AddEntry(&GMassData, "PbPb (stat.)", "pl");
         Legend.AddEntry(&GMassDataSys, "PbPb (sys.)", "pl");
         Legend.AddEntry(&GMassSmear, "smeared pp (stat.)", "pl");
         Legend.AddEntry(&GMassSmearSys, "smeared pp (sys.)", "pl");

         TCanvas C;

         GMassData.SetMarkerColor(kBlack);
         GMassData.SetLineColor(kBlue);
         GMassSmear.SetMarkerColor(kRed);
         GMassSmear.SetLineColor(kMagenta);
         GMassSmearSys.SetMarkerColor(kRed);
         GMassSmearSys.SetLineColor(kRed);
         GZGData.SetMarkerColor(kBlack);
         GZGData.SetLineColor(kBlue);
         GZGSmear.SetMarkerColor(kRed);
         GZGSmear.SetLineColor(kMagenta);
         GDRData.SetMarkerColor(kBlack);
         GDRData.SetLineColor(kBlue);
         GDRSmear.SetMarkerColor(kRed);
         GDRSmear.SetLineColor(kMagenta);
         GPTPTData.SetMarkerColor(kBlack);
         GPTPTData.SetLineColor(kBlue);
         GPTPTSmear.SetMarkerColor(kRed);
         GPTPTSmear.SetLineColor(kMagenta);

         TH2D HWorld("HWorld", ";Jet SD Mass / Jet PT;a.u.", 100, 0, 0.3, 100, 0, 25);
         HWorld.SetStats(0);
         HWorld.Draw();
         GMassDataSys.Draw("p");
         GMassData.Draw("p");
         GMassSmearSys.Draw("p");
         GMassSmear.Draw("p");
         Legend.Draw();

         PdfFile.AddCanvas(C);

         TH2D HWorld2("HWorld2", ";Jet SD Mass / Jet PT;a.u.", 100, 0, 0.3, 100, 0.01, 500);
         HWorld2.SetStats(0);
         HWorld2.Draw();
         GMassDataSys.Draw("p");
         GMassData.Draw("p");
         GMassSmearSys.Draw("p");
         GMassSmear.Draw("p");
         Legend.Draw();

         C.SetLogy();
         PdfFile.AddCanvas(C);

         double MaxZG = 0;
         if(SD == 7)
            MaxZG = 6;
         else
            MaxZG = 15;
         TH2D HWorld3("HWorld3", ";z_{g};a.u.", 100, 0, 0.5, 100, 0, MaxZG);
         HWorld3.SetStats(0);
         HWorld3.Draw();
         GZGData.Draw("p");
         GZGSmear.Draw("p");
         Legend.Draw();

         C.SetLogy(false);
         PdfFile.AddCanvas(C);

         double MaxDR = 0;
         if(SD == 7)
            MaxDR = 30;
         else
            MaxDR = 15;
         TH2D HWorld4("HWorld4", ";Reconstructed sub-jet DR;a.u.", 100, 0, 0.5, 100, 0, MaxDR);
         HWorld4.SetStats(0);
         HWorld4.Draw();
         GDRData.Draw("p");
         GDRSmear.Draw("p");
         Legend.Draw();

         C.SetLogy(false);
         PdfFile.AddCanvas(C);

         double MaxPTPT = 0;
         if(SD == 7)
            MaxPTPT = 50;
         else
            MaxPTPT = 50;
         TH2D HWorld5("HWorld5", ";PT / PT;a.u.", 100, 0, 1.0, 100, 0.0001, MaxPTPT);
         HWorld5.SetStats(0);
         HWorld5.Draw();
         GPTPTData.Draw("p");
         GPTPTSmear.Draw("p");
         Legend.Draw();

         C.SetLogy(true);
         PdfFile.AddCanvas(C);
      }
   }

   /////////////////////
   // Cleanup outputs //
   /////////////////////

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.Close();

   /////////////////
   // Close files //
   /////////////////

   FSmearSystematics.Close();
   FDataSystematics.Close();

   FSmear.Close();
   FData.Close();

   return 0;
}

void InitializeVectors(vector<int> A[5][6], int Size)
{
   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 6; j++)
         A[i][j].resize(Size, 0);
}

void InitializeVectors(vector<double> A[5][6], int Size)
{
   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 6; j++)
         A[i][j].resize(Size, 0);
}

void InitializeVectors(vector<double> A[6], int Size)
{
   for(int j = 0; j < 6; j++)
      A[j].resize(Size, 0);
}




