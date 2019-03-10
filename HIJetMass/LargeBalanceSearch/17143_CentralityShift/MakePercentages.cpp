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
#include "DataHelper.h"

#include "ReadTree.h"
#include "JetEnergyScale.h"

#define PI 3.14159265358979323846264338327950288479716939937510
#define ZCUTBINCOUNT 7
#define DRCUTBINCOUNT 10

#define TRIGGER_NONE 0
#define TRIGGER_100 1
#define TRIGGER_80 2
#define TRIGGER_60 3

int main(int argc, char *argv[]);
void InitializeVectors(vector<double> A[5][6][ZCUTBINCOUNT], int Size);
void InitializeVectors(vector<int> A[5][6], int Size);
void InitializeVectors(vector<double> A[5][6], int Size);
void InitializeVectors(vector<double> A[6], int Size);
void FillVector(vector<double> &Count, double DR, double W);

int main(int argc, char *argv[])
{
   int Increment = 50;

   SetThesisStyle();

   //////////////////
   // Usage string //
   //////////////////
   
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " IsMC=Y PTHat Tag" << endl;
      cerr << "Usage: " << argv[0] << " IsMC=S PTHat Tag" << endl;
      cerr << "Usage: " << argv[0] << " IsMC=N Trigger=(100|80|60) Tag" << endl;
   }

   ////////////////////////
   // Sorting out inputs //
   ////////////////////////

   bool IsMC = ((argv[1][0] == 'Y' || argv[1][0] == 'S') ? true : false);

   string Tag = argv[3];

   int TriggerSelection = TRIGGER_NONE;
   if(IsMC == false)
   {
      if(string(argv[2]) == "100")       TriggerSelection = TRIGGER_100;
      else if(string(argv[2]) == "80")   TriggerSelection = TRIGGER_80;
      else if(string(argv[2]) == "60")   TriggerSelection = TRIGGER_60;
   }

   double PTHatMin = ((IsMC == true) ? atof(argv[2]) : 0);
   string PTHatString = argv[2];

   double PTHatMax = 1000000;

   cout << "Running with MC = " << IsMC << endl;

   /////////////////////
   // Bin definitions //
   /////////////////////

   double CBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBinEdge[6+1] = {120, 140, 160, 180, 200, 300, 500};
   double ZBinEdge[ZCUTBINCOUNT+1] = {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.50};
   double DRBinEdge[DRCUTBINCOUNT+1] = {-1, 0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45};

   /////////////////////////////////////
   // Prepare to get stuff from files //
   /////////////////////////////////////

   string FileNameData = "StraightResult/AAData.root";
   string FileNameSmear = "MixedResult/PPDataHighPTJet.root";
   
   if(IsMC == true)
   {
      // FileNameData = "AA6Dijet" + PTHatString + "Cymbal.root";
      // FileNameSmear = "PP6Dijet" + PTHatString + ".root";

      if(PTHatMin <= 0)
      {
         FileNameData = "StraightResult/AA6DijetCymbalV2.root";
         FileNameSmear = "MixedResult/PP6Dijet.root";
         PTHatMin = 100;
         PTHatMax = 10000000;
      }
   }
   // if(IsMC == false && TriggerSelection != TRIGGER_NONE)
   //    FileNameData = "SampleBase/PlainTree/16354NoRhoMSubJetInfo/AADataPrescale.root";

   cout << "Straight tree = " << FileNameData << endl;
   cout << "Smear tree = " << FileNameSmear << endl;

   ////////////////////
   // Get data trees //
   ////////////////////

   TFile FData(FileNameData.c_str());
   TFile FSmear(FileNameSmear.c_str());

   StraightTreeMessenger MData(FData, "T", IsMC, atoi(argv[3]));
   SmearTreeMessenger MSmear(FSmear, "OutputTree", IsMC);

   int DataEntryCount = MData.Tree->GetEntries() * 1.00;
   int SmearEntryCount = MSmear.Tree->GetEntries() * 1.00;

   ////////////////////////////
   // Get systematics graphs //
   ////////////////////////////

   // TFile FDataSystematics(Form("CombinedSystematics_Data16213_%d.root", SD));
   // TFile FSmearSystematics(Form("CombinedSystematics_All16213_%d.root", SD));

   // TGraphAsymmErrors *DataError[5][6] = {{0}};
   // TGraphAsymmErrors *SmearError[5][6] = {{0}};
   // for(int i = 0; i < 5; i++)
   // {
   //    for(int j = 0; j < 6; j++)
   //    {
   //       DataError[i][j] =
   //          (TGraphAsymmErrors *)FDataSystematics.Get(Form("GRatio_C%d_P%d", i, j));
   //       SmearError[i][j] =
   //          (TGraphAsymmErrors *)FSmearSystematics.Get(Form("GRatio_C%d_P%d", i, j));
   //    }
   // }

   ///////////////////
   // Setup outputs //
   ///////////////////

   TFile OutputFile(Form("Graphs_%s.root", Tag.c_str()), "RECREATE");

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
   for(int iE = 0; iE < DataEntryCount; iE = iE + Increment)
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
   MSmear.SetJES(&JES);

   /////////////////////////////////////
   // First step - get jet PT weights //
   /////////////////////////////////////

   vector<double> DataPT[5][6];
   InitializeVectors(DataPT, 50);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE = iE + Increment)
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
   for(int iE = 0; iE < SmearEntryCount; iE = iE + Increment)
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
   for(int iE = 0; iE < DataEntryCount; iE = iE + Increment)
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
   for(int iE = 0; iE < SmearEntryCount; iE = iE + Increment)
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

   vector<double> DataCount[5][6][7];
   vector<double> DataCount2[5][6][7];
   InitializeVectors(DataCount, DRCUTBINCOUNT);
   InitializeVectors(DataCount2, DRCUTBINCOUNT);

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

      double TotalWeight = MData.MCWeight;

      FillVector(DataCount[CBin][PTBin][0], MData.SDRecoDR, TotalWeight);
      FillVector(DataCount[CBin][PTBin][1], MData.SDRecoDRs[0], TotalWeight);
      FillVector(DataCount[CBin][PTBin][2], MData.SDRecoDRs[1], TotalWeight);
      FillVector(DataCount[CBin][PTBin][3], MData.SDRecoDRs[2], TotalWeight);
      FillVector(DataCount[CBin][PTBin][4], MData.SDRecoDRs[3], TotalWeight);
      FillVector(DataCount[CBin][PTBin][5], MData.SDRecoDRs[4], TotalWeight);
      FillVector(DataCount[CBin][PTBin][6], MData.SDRecoDRs[5], TotalWeight);

      FillVector(DataCount2[CBin][PTBin][0], MData.SDRecoDR, TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][1], MData.SDRecoDRs[0], TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][2], MData.SDRecoDRs[1], TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][3], MData.SDRecoDRs[2], TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][4], MData.SDRecoDRs[3], TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][5], MData.SDRecoDRs[4], TotalWeight * TotalWeight);
      FillVector(DataCount2[CBin][PTBin][6], MData.SDRecoDRs[5], TotalWeight * TotalWeight);
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   vector<double> SmearCount[5][6][7];
   vector<double> SmearCount2[5][6][7];
   InitializeVectors(SmearCount, DRCUTBINCOUNT);
   InitializeVectors(SmearCount2, DRCUTBINCOUNT);
   
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
      double CentralityWeight = DataCentralityBins[PTBin][Centrality]
         / SmearCentralityBins[PTBin][Centrality];

      double TotalWeight = MSmear.MCWeight * JetWeight * CentralityWeight;

      FillVector(SmearCount[CBin][PTBin][0], MSmear.SDRecoDR, TotalWeight);
      FillVector(SmearCount[CBin][PTBin][1], MSmear.SDRecoDRs[0], TotalWeight);
      FillVector(SmearCount[CBin][PTBin][2], MSmear.SDRecoDRs[1], TotalWeight);
      FillVector(SmearCount[CBin][PTBin][3], MSmear.SDRecoDRs[2], TotalWeight);
      FillVector(SmearCount[CBin][PTBin][4], MSmear.SDRecoDRs[3], TotalWeight);
      FillVector(SmearCount[CBin][PTBin][5], MSmear.SDRecoDRs[4], TotalWeight);
      FillVector(SmearCount[CBin][PTBin][6], MSmear.SDRecoDRs[5], TotalWeight);

      FillVector(SmearCount2[CBin][PTBin][0], MSmear.SDRecoDR, TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][1], MSmear.SDRecoDRs[0], TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][2], MSmear.SDRecoDRs[1], TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][3], MSmear.SDRecoDRs[2], TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][4], MSmear.SDRecoDRs[3], TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][5], MSmear.SDRecoDRs[4], TotalWeight * TotalWeight);
      FillVector(SmearCount2[CBin][PTBin][6], MSmear.SDRecoDRs[5], TotalWeight * TotalWeight);
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
         TH2D HData(Form("HData_%d_%d", CBin, PTBin), Form("C %.02f-%.02f, PT %f-%f;DR Cut;Z Cut;", CBinEdge[CBin], CBinEdge[CBin+1], PTBinEdge[PTBin], PTBinEdge[PTBin+1]), DRCUTBINCOUNT, 0, DRCUTBINCOUNT, ZCUTBINCOUNT, 0, ZCUTBINCOUNT);
         TH2D HSmear(Form("HSmear_%d_%d", CBin, PTBin), Form("C %.02f-%.02f, PT %f-%f;DR Cut;Z Cut;", CBinEdge[CBin], CBinEdge[CBin+1], PTBinEdge[PTBin], PTBinEdge[PTBin+1]), DRCUTBINCOUNT, 0, DRCUTBINCOUNT, ZCUTBINCOUNT, 0, ZCUTBINCOUNT);

         for(int iZ = 1; iZ <= ZCUTBINCOUNT; iZ++)
         {
            HData.GetYaxis()->SetBinLabel(iZ, Form("%.02f", ZBinEdge[iZ-1]));
            HSmear.GetYaxis()->SetBinLabel(iZ, Form("%.02f", ZBinEdge[iZ-1]));
         }
         for(int iDR = 1; iDR <= DRCUTBINCOUNT; iDR++)
         {
            HData.GetXaxis()->SetBinLabel(iDR, Form("%.02f", DRBinEdge[iDR-1]));
            HSmear.GetXaxis()->SetBinLabel(iDR, Form("%.02f", DRBinEdge[iDR-1]));
         }

         for(int iZ = 0; iZ < ZCUTBINCOUNT; iZ++)
         {
            for(int iDR = 0; iDR < DRCUTBINCOUNT; iDR++)
            {
               HData.SetBinContent(iDR + 1, iZ + 1, DataCount[CBin][PTBin][iZ][iDR]);
               HData.SetBinError(iDR + 1, iZ + 1, sqrt(DataCount2[CBin][PTBin][iZ][iDR]));
               HSmear.SetBinContent(iDR + 1, iZ + 1, SmearCount[CBin][PTBin][iZ][iDR]);
               HSmear.SetBinError(iDR + 1, iZ + 1, sqrt(SmearCount2[CBin][PTBin][iZ][iDR]));
            }
         }

         HData.Write();
         HSmear.Write();
      }
   }

   /////////////////////
   // Cleanup outputs //
   /////////////////////

   OutputFile.Close();

   /////////////////
   // Close files //
   /////////////////

   // FSmearSystematics.Close();
   // FDataSystematics.Close();

   FSmear.Close();
   FData.Close();

   return 0;
}

void InitializeVectors(vector<double> A[5][6][7], int Size)
{
   for(int i = 0; i < 5; i++)
      for(int j = 0; j < 6; j++)
         for(int k = 0; k < 7; k++)
            A[i][j][k].resize(Size, 0);
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

void FillVector(vector<double> &Count, double DR, double W)
{
   Count[0] = Count[0] + W;
   
   if(DR >= 0.00)   Count[1] = Count[1] + W;
   if(DR >= 0.05)   Count[2] = Count[2] + W;
   if(DR >= 0.10)   Count[3] = Count[3] + W;
   if(DR >= 0.15)   Count[4] = Count[4] + W;
   if(DR >= 0.20)   Count[5] = Count[5] + W;
   if(DR >= 0.25)   Count[6] = Count[6] + W;
   if(DR >= 0.30)   Count[7] = Count[7] + W;
   if(DR >= 0.35)   Count[8] = Count[8] + W;
   if(DR >= 0.40)   Count[9] = Count[9] + W;
}



