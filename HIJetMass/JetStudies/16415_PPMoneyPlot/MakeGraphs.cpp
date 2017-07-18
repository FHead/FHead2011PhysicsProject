#include <iostream>
#include <cmath>
#include <fstream>
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
   
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " FileName SDChoice IsMC=Y PTHat Tag" << endl;
      cerr << "Usage: " << argv[0] << " FileName SDChoice IsMC=N DUMMY Tag" << endl;
   }

   ////////////////////////
   // Sorting out inputs //
   ////////////////////////

   string FileNameData = argv[1];

   int SD = ((argv[2][0] == '0') ? 0 : 7);
   bool IsMC = ((argv[3][0] == 'Y') ? true : false);

   bool DoDRReweight = false;

   string Tag = argv[5];

   int TriggerSelection = TRIGGER_NONE;
   if(IsMC == false)
   {
      if(string(argv[4]) == "100")       TriggerSelection = TRIGGER_100;
      else if(string(argv[4]) == "80")   TriggerSelection = TRIGGER_80;
      else if(string(argv[4]) == "60")   TriggerSelection = TRIGGER_60;
   }

   double PTHatMin = ((IsMC == true) ? atof(argv[4]) : 0);
   string PTHatString = argv[4];

   double PTHatMax = 1000000;

   cout << "Running with SD = " << SD << ", MC = " << IsMC << endl;

   /////////////////////
   // Bin definitions //
   /////////////////////

   double CBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBinEdge[6+1] = {120, 140, 160, 180, 200, 300, 500};

   // Original mass binning
   double MassBinEdge[MASSBINCOUNT+1] =
      {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26};
   double Mass0BinEdge[MASSBINCOUNT+1] =
      {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26};

   // Optimized mass binning for massless subjets
   // double MassBinEdge[MASSBINCOUNT+1] =
   //    {0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.125, 0.155, 0.19, 0.26};
   // double Mass0BinEdge[MASSBINCOUNT+1] =
   //    {0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.19};

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

   if(IsMC == true)
   {
      if(PTHatMin <= 0)
      {
         PTHatMin = 100;
         PTHatMax = 10000000;
      }
   }
      
   ////////////////////
   // Get data trees //
   ////////////////////

   TFile FData(FileNameData.c_str());

   StraightTreeMessenger MData(FData, "T", IsMC, SD, atoi(argv[3]));

   int DataEntryCount = MData.Tree->GetEntries() * 1.00;

   ////////////////////////////
   // Get systematics graphs //
   ////////////////////////////

   TFile FDataSystematics(Form("CombinedSystematics_%d_%s.root", SD, (IsMC ? "Y" : "N")));

   TGraphAsymmErrors *DataError[5][6] = {{0}};
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         DataError[i][j] =
            (TGraphAsymmErrors *)FDataSystematics.Get(Form("GRatio_C%d_P%d", i, j));
      }
   }

   ///////////////////
   // Setup outputs //
   ///////////////////

   TFile OutputFile(Form("Graphs_%s.root", Tag.c_str()), "RECREATE");

   PdfFileHelper PdfFile("QuickView_" + Tag + ".pdf");
   PdfFile.AddTextPage("Quick view of the result!");

   ofstream OutputMassFile("Mass_" + Tag + ".txt");
   
   ///////////////////
   // Progress bars //
   ///////////////////

   ProgressBar BarData(cout, DataEntryCount);

   BarData.SetStyle(0);

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

   MData.SetJES(&JES);

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
      int AngleBin = MData.AngleBin(DRBinEdge, DRBINCOUNT);

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      int iMassB = GetBin(MData.SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iMassB0 = GetBin(MData.SDMassRatio, Mass0BinEdge, MASSBINCOUNT);
      int iZGB = GetBin(MData.SDZG, ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(MData.SDRecoDR, DRBinEdge, DRBINCOUNT);
      int iDRB0 = GetBin(MData.SDRecoDR, DR0BinEdge, DRBINCOUNT);
      int iPTPT = GetBin(MData.PTPT, PTPTBinEdge, PTPTBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double TotalWeight = MData.MCWeight;
      double UpWeight = DataError[CBin][PTBin]->GetErrorYhigh(MData.SysBin);
      double DownWeight = -DataError[CBin][PTBin]->GetErrorYlow(MData.SysBin);

      OutputMassFile << "Data " << Centrality << " " << MData.JetPT
         << " " << MData.SDMassRatio << " " << MData.SDZG << " " << MData.SDRecoDR
         << " " << MData.PTPT << " " << TotalWeight << endl;

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
      if(MData.SDRecoDR > 0.1 && MData.SDRecoDR < 0.35)
      {
         Data0CountMass     [CBin][PTBin][iMassB0] += TotalWeight;
         Data0TotalMassX    [CBin][PTBin][iMassB0] += MData.SDMassRatio * TotalWeight;
         Data0TotalMass     [CBin][PTBin][iMassB0] += TotalWeight;
         Data0TotalMass2    [CBin][PTBin][iMassB0] += TotalWeight * TotalWeight;
         Data0TotalMassUp   [CBin][PTBin][iMassB0] += TotalWeight * exp(UpWeight);
         Data0TotalMassDown [CBin][PTBin][iMassB0] += TotalWeight * exp(DownWeight);
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

   ////////////////////////
   // Build final graphs //
   ////////////////////////

   for(int CBin = 0; CBin < 5; CBin++)
   {
      for(int PTBin = 0; PTBin < 6; PTBin++)
      {
         PdfFile.AddTextPage(Form("C %.02f-%.02f, PT %.0f-%.0f", CBinEdge[CBin], CBinEdge[CBin+1], PTBinEdge[PTBin], PTBinEdge[PTBin+1]));

         TGraphAsymmErrors GMassData, GMassDataSys, GZGData, GDRData, GPTPTData;
         TGraphAsymmErrors GMassData0, GMassDataSys0, GZGData0, GDRData0, GPTPTData0; 

         GMassData.SetNameTitle(Form("MassData_%d_%d", CBin, PTBin), "");
         GMassDataSys.SetNameTitle(Form("MassDataSys_%d_%d", CBin, PTBin), "");
         GZGData.SetNameTitle(Form("ZGData_%d_%d", CBin, PTBin), "");
         GDRData.SetNameTitle(Form("DRData_%d_%d", CBin, PTBin), "");
         GPTPTData.SetNameTitle(Form("PTPTData_%d_%d", CBin, PTBin), "");
         GMassData0.SetNameTitle(Form("MassData0_%d_%d", CBin, PTBin), "");
         GMassDataSys0.SetNameTitle(Form("MassDataSys0_%d_%d", CBin, PTBin), "");
         GZGData0.SetNameTitle(Form("ZGData0_%d_%d", CBin, PTBin), "");
         GDRData0.SetNameTitle(Form("DRData0_%d_%d", CBin, PTBin), "");
         GPTPTData0.SetNameTitle(Form("PTPTData0_%d_%d", CBin, PTBin), "");

         GMassData.SetMarkerStyle(20);
         GMassDataSys.SetMarkerStyle(20);
         GZGData.SetMarkerStyle(20);
         GDRData.SetMarkerStyle(20);
         GPTPTData.SetMarkerStyle(20);
         GMassData0.SetMarkerStyle(20);
         GMassDataSys0.SetMarkerStyle(20);
         GZGData0.SetMarkerStyle(20);
         GDRData0.SetMarkerStyle(20);
         GPTPTData0.SetMarkerStyle(20);
         GMassData.SetMarkerSize(0.7);
         GMassDataSys.SetMarkerSize(0.7);
         GZGData.SetMarkerSize(0.7);
         GDRData.SetMarkerSize(0.7);
         GPTPTData.SetMarkerSize(0.7);
         GMassData0.SetMarkerSize(0.7);
         GMassDataSys0.SetMarkerSize(0.7);
         GZGData0.SetMarkerSize(0.7);
         GDRData0.SetMarkerSize(0.7);
         GPTPTData0.SetMarkerSize(0.7);

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

            double MassBinSize = Mass0BinEdge[i+1] - Mass0BinEdge[i];
            double MassX = Data0TotalMassX[CBin][PTBin][i] / Data0CountMass[CBin][PTBin][i];
            double Mass = Data0TotalMass[CBin][PTBin][i] / MassBinSize * Factor;
            double MassRMS = sqrt(Data0TotalMass2[CBin][PTBin][i]) / MassBinSize * Factor;
            double MassUp = Data0TotalMassUp[CBin][PTBin][i] / MassBinSize * Factor;
            double MassDown = Data0TotalMassDown[CBin][PTBin][i] / MassBinSize * Factor;

            GMassData0.SetPoint(i, MassX, Mass);
            GMassData0.SetPointError(i, MassX - Mass0BinEdge[i], Mass0BinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys0.SetPoint(i, MassX, Mass);
            GMassDataSys0.SetPointError(i, MassX - Mass0BinEdge[i], Mass0BinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
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
  
         GMassData.Write();
         GMassDataSys.Write();
         GZGData.Write();
         GDRData.Write();
         GPTPTData.Write();
         GMassData0.Write();
         GMassDataSys0.Write();
         GZGData0.Write();
         GDRData0.Write();
         GPTPTData0.Write();

         TLegend Legend(0.5, 0.8, 0.8, 0.5);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetFillStyle(0);
         Legend.AddEntry(&GMassData, "PbPb (stat.)", "pl");
         Legend.AddEntry(&GMassDataSys, "PbPb (sys.)", "pl");

         TCanvas C;

         GMassData.SetMarkerColor(kBlack);
         GMassData.SetLineColor(kBlue);
         GZGData.SetMarkerColor(kBlack);
         GZGData.SetLineColor(kBlue);
         GDRData.SetMarkerColor(kBlack);
         GDRData.SetLineColor(kBlue);
         GPTPTData.SetMarkerColor(kBlack);
         GPTPTData.SetLineColor(kBlue);

         TH2D HWorld("HWorld", ";Jet SD Mass / Jet PT;a.u.", 100, 0, 0.3, 100, 0, 25);
         HWorld.SetStats(0);
         HWorld.Draw();
         GMassDataSys.Draw("p");
         GMassData.Draw("p");
         Legend.Draw();

         PdfFile.AddCanvas(C);

         TH2D HWorld2("HWorld2", ";Jet SD Mass / Jet PT;a.u.", 100, 0, 0.3, 100, 0.01, 500);
         HWorld2.SetStats(0);
         HWorld2.Draw();
         GMassDataSys.Draw("p");
         GMassData.Draw("p");
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
         Legend.Draw();

         C.SetLogy(true);
         PdfFile.AddCanvas(C);
      }
   }

   /////////////////////
   // Cleanup outputs //
   /////////////////////

   OutputMassFile.close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.Close();

   /////////////////
   // Close files //
   /////////////////

   FDataSystematics.Close();

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




