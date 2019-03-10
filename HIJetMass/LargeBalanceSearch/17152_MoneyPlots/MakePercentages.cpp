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

#define MODE_NOMINAL 0
#define MODE_JECUP 1
#define MODE_JECDOWN 2
#define MODE_RJECUP 3
#define MODE_RJECDOWN 4
#define MODE_RHOUP 5
#define MODE_RHODOWN 6
#define MODE_DATAJER 7
#define MODE_SMEARJER 8
#define MODE_RHOSHIFT 9
#define MODE_DRUP 10
#define MODE_DRDOWN 11
#define MODE_RDRUP 12
#define MODE_RDRDOWN 14
#define MODE_SHIFTED 15
#define MODE_HIRECO 16
#define MODE_PP8DIJET 17
#define MODE_PP8DIJETLARGE 18
#define MODE_CENTRALFOCUS 19

int main(int argc, char *argv[]);
void InitializeVectors(vector<double> A[5][6][ZCUTBINCOUNT], int Size);
void InitializeVectors(vector<int> A[5][6], int Size);
void InitializeVectors(vector<double> A[5][6], int Size);
void InitializeVectors(vector<double> A[6], int Size);
void FillVector(vector<double> &Count, double DR, double W, int Direction);
double AdjustCentrality(double Centrality, double Shift);
double CentralityToHF(double C);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   //////////////////
   // Usage string //
   //////////////////
   
   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " IsMC=Y PTHat Tag Mode" << endl;
      cerr << "Usage: " << argv[0] << " IsMC=S PTHat Tag Mode" << endl;
      cerr << "Usage: " << argv[0] << " IsMC=N Trigger=(100|80|60) Tag Mode" << endl;
      cerr << "Mode =" << endl;
      cerr << "   Default: nominal result" << endl;
      cerr << "   JECUp: JEC up" << endl;
      cerr << "   JECDown: JEC down" << endl;
      cerr << "   RJECUp: Relative JEC up" << endl;
      cerr << "   RJECDown: Relative JEC down" << endl;
      cerr << "   RhoUp: Rho up" << endl;
      cerr << "   RhoDown: Rho down" << endl;
      cerr << "   PbPbJER: JER on PbPb" << endl;
      cerr << "   PPJER: JER on pp" << endl;
      cerr << "   RhoShift: Rho shifted up by 10 GeV" << endl;
      cerr << "   DRUp: DR cut boundaries up" << endl;
      cerr << "   DRDown: DR cut boundaries down" << endl;
      cerr << "   RDRUp: DR cut boundaries up, smeared sample only" << endl;
      cerr << "   RDRDown: DR cut boundaries down, smeared sample only" << endl;
      cerr << "   Shifted: rho shifted" << endl;

      return -1;
   }

   ////////////////////////
   // Sorting out inputs //
   ////////////////////////

   bool IsMC = ((argv[1][0] == 'Y') ? true : false);

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

   string ModeString = argv[4];
   int Mode = MODE_NOMINAL;
   if(ModeString == "JECUp")        Mode = MODE_JECUP;
   if(ModeString == "JECDown")      Mode = MODE_JECDOWN;
   if(ModeString == "RJECUp")       Mode = MODE_RJECUP;
   if(ModeString == "RJECDown")     Mode = MODE_RJECDOWN;
   if(ModeString == "RhoUp")        Mode = MODE_RHOUP;
   if(ModeString == "RhoDown")      Mode = MODE_RHODOWN;
   if(ModeString == "PbPbJER")      Mode = MODE_DATAJER;
   if(ModeString == "PPJER")        Mode = MODE_SMEARJER;
   if(ModeString == "RhoShift")     Mode = MODE_RHOSHIFT;
   if(ModeString == "DRUp")         Mode = MODE_DRUP;
   if(ModeString == "DRDown")       Mode = MODE_DRDOWN;
   if(ModeString == "RDRUp")        Mode = MODE_RDRUP;
   if(ModeString == "RDRDown")      Mode = MODE_RDRDOWN;
   if(ModeString == "Shifted")      Mode = MODE_SHIFTED;
   if(ModeString == "HIReco")       Mode = MODE_HIRECO;
   if(ModeString == "Pythia8")      Mode = MODE_PP8DIJET;
   if(ModeString == "Pythia8Large") Mode = MODE_PP8DIJETLARGE;
   if(ModeString == "CentralFocus") Mode = MODE_CENTRALFOCUS;

   cout << "Running with MC = " << IsMC << endl;

   /////////////////////
   // Bin definitions //
   /////////////////////

   double CBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.7, 1.0};
   double SmearCBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.7, 1.0};
   double PTBinEdge[6+1] = {120, 140, 160, 180, 200, 300, 500};
   double ZBinEdge[ZCUTBINCOUNT+1] = {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.50};
   double DRBinEdge[DRCUTBINCOUNT+1] = {-1, 0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45};
   
   if(Mode == MODE_CENTRALFOCUS)
   {
      CBinEdge[0] = 0.00;
      CBinEdge[1] = 0.01;
      CBinEdge[2] = 0.05;
      CBinEdge[3] = 0.10;
      CBinEdge[4] = 0.15;
      CBinEdge[5] = 0.20;
      SmearCBinEdge[0] = 0.00;
      SmearCBinEdge[1] = 0.01;
      SmearCBinEdge[2] = 0.05;
      SmearCBinEdge[3] = 0.10;
      SmearCBinEdge[4] = 0.15;
      SmearCBinEdge[5] = 0.20;
   }

   if(Mode == MODE_RHOUP)
   {
      SmearCBinEdge[0] = 0.00;
      SmearCBinEdge[1] = 0.09;
      SmearCBinEdge[2] = 0.27;
      SmearCBinEdge[3] = 0.45;
      SmearCBinEdge[4] = 0.63;
      SmearCBinEdge[5] = 1.00;
   }
   if(Mode == MODE_RHODOWN)
   {
      SmearCBinEdge[0] = 0.00;
      SmearCBinEdge[1] = 0.11;
      SmearCBinEdge[2] = 0.33;
      SmearCBinEdge[3] = 0.55;
      SmearCBinEdge[4] = 0.77;
      SmearCBinEdge[5] = 1.00;
   }

   int DataDRDirection = 0, SmearDRDirection = 0;
   if(Mode == MODE_DRUP)
   {
      DataDRDirection = 1;
      SmearDRDirection = 1;
   }
   if(Mode == MODE_DRDOWN)
   {
      DataDRDirection = -1;
      SmearDRDirection = -1;
   }
   if(Mode == MODE_RDRUP)
      SmearDRDirection = 1;
   if(Mode == MODE_RDRDOWN)
      SmearDRDirection = -1;

   /////////////////////////////////////
   // Prepare to get stuff from files //
   /////////////////////////////////////

   string FileNameData = "StraightResult/AAData.root";
   string FileNameSmear = "MixedResult/PPDataHighPTJet.root";
   
   if(IsMC == true)
   {
      FileNameData = "StraightResult/Temp/AA6DijetCymbalV2.root";
      FileNameSmear = "MixedResult/PP6Dijet.root";
      PTHatMin = 100;
      PTHatMax = 10000000;
   }

   if(Mode == MODE_SHIFTED)
      FileNameSmear = "MixedResult/TempShifted/PP6Dijet.root";
   if(Mode == MODE_HIRECO)
      FileNameSmear = "MixedResult/PP6DijetHIReco.root";
   if(Mode == MODE_PP8DIJET)
      FileNameSmear = "MixedResult/PP8Dijet.root";
   if(Mode == MODE_PP8DIJETLARGE)
      FileNameSmear = "MixedResult/PP8DijetLarge.root";
   
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

   double DataJESFactor = 1;
   double SmearJESFactor = 1;

   if(Mode == MODE_JECUP)
   {
      DataJESFactor = 1.05;
      SmearJESFactor = 1.05;
   }
   if(Mode == MODE_JECDOWN)
   {
      DataJESFactor = 0.95;
      SmearJESFactor = 0.95;
   }
   if(Mode == MODE_RJECUP)
      SmearJESFactor = 1.05;
   if(Mode == MODE_RJECDOWN)
      SmearJESFactor = 0.95;

   double DataJERFactor = ((Mode == MODE_DATAJER) ? 0 : 0.05);
   double SmearJERFactor = ((Mode == MODE_SMEARJER) ? 0 : 0.05);

   MData.SetJES(&JES, DataJESFactor, DataJERFactor);
   MSmear.SetJES(&JES, SmearJESFactor, SmearJERFactor);

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
      if(Mode == MODE_RHOSHIFT)
         MSmear.Centrality = AdjustCentrality(MSmear.Centrality, 10);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(SmearCBinEdge, 5);
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
      if(Mode == MODE_RHOSHIFT)
         MSmear.Centrality = AdjustCentrality(MSmear.Centrality, 10);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(SmearCBinEdge, 5);
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

      FillVector(DataCount[CBin][PTBin][0], MData.SDRecoDR, TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][1], MData.SDRecoDRs[0], TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][2], MData.SDRecoDRs[1], TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][3], MData.SDRecoDRs[2], TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][4], MData.SDRecoDRs[3], TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][5], MData.SDRecoDRs[4], TotalWeight, DataDRDirection);
      FillVector(DataCount[CBin][PTBin][6], MData.SDRecoDRs[5], TotalWeight, DataDRDirection);

      FillVector(DataCount2[CBin][PTBin][0], MData.SDRecoDR, TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][1], MData.SDRecoDRs[0], TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][2], MData.SDRecoDRs[1], TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][3], MData.SDRecoDRs[2], TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][4], MData.SDRecoDRs[3], TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][5], MData.SDRecoDRs[4], TotalWeight * TotalWeight, DataDRDirection);
      FillVector(DataCount2[CBin][PTBin][6], MData.SDRecoDRs[5], TotalWeight * TotalWeight, DataDRDirection);
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
      if(Mode == MODE_RHOSHIFT)
         MSmear.Centrality = AdjustCentrality(MSmear.Centrality, 10);

      if(MSmear.PassSelection() == false)       continue;
      if(MSmear.PassPTHat(PTHatMin, PTHatMax) == false)   continue;
      
      int CBin = MSmear.CentralityBin(SmearCBinEdge, 5);
      int PTBin = MSmear.PTBin(PTBinEdge, 6);
      int JetBin = MSmear.JetBin(PTBinEdge, 6);
      int Centrality = MSmear.CentralityInt();

      if(CBin < 0 || PTBin < 0 || JetBin < 0)
         continue;

      double JetWeight = DataPT[CBin][PTBin][JetBin] / SmearPT[CBin][PTBin][JetBin];
      double CentralityWeight = DataCentralityBins[PTBin][Centrality]
         / SmearCentralityBins[PTBin][Centrality];

      double TotalWeight = MSmear.MCWeight * JetWeight * CentralityWeight;

      FillVector(SmearCount[CBin][PTBin][0], MSmear.SDRecoDR, TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][1], MSmear.SDRecoDRs[0], TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][2], MSmear.SDRecoDRs[1], TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][3], MSmear.SDRecoDRs[2], TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][4], MSmear.SDRecoDRs[3], TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][5], MSmear.SDRecoDRs[4], TotalWeight, SmearDRDirection);
      FillVector(SmearCount[CBin][PTBin][6], MSmear.SDRecoDRs[5], TotalWeight, SmearDRDirection);

      FillVector(SmearCount2[CBin][PTBin][0], MSmear.SDRecoDR, TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][1], MSmear.SDRecoDRs[0], TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][2], MSmear.SDRecoDRs[1], TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][3], MSmear.SDRecoDRs[2], TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][4], MSmear.SDRecoDRs[3], TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][5], MSmear.SDRecoDRs[4], TotalWeight * TotalWeight, SmearDRDirection);
      FillVector(SmearCount2[CBin][PTBin][6], MSmear.SDRecoDRs[5], TotalWeight * TotalWeight, SmearDRDirection);
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
         TH2D HSmear(Form("HSmear_%d_%d", CBin, PTBin), Form("C %.02f-%.02f, PT %f-%f;DR Cut;Z Cut;", SmearCBinEdge[CBin], SmearCBinEdge[CBin+1], PTBinEdge[PTBin], PTBinEdge[PTBin+1]), DRCUTBINCOUNT, 0, DRCUTBINCOUNT, ZCUTBINCOUNT, 0, ZCUTBINCOUNT);

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

void FillVector(vector<double> &Count, double DR, double W, int Direction)
{
   Count[0] = Count[0] + W;
   
   if(DR >= 0.00)                      Count[1] = Count[1] + W;
   if(DR >= 0.05 + 0.01 * Direction)   Count[2] = Count[2] + W;
   if(DR >= 0.10 + 0.01 * Direction)   Count[3] = Count[3] + W;
   if(DR >= 0.15 + 0.01 * Direction)   Count[4] = Count[4] + W;
   if(DR >= 0.20 + 0.01 * Direction)   Count[5] = Count[5] + W;
   if(DR >= 0.25 + 0.01 * Direction)   Count[6] = Count[6] + W;
   if(DR >= 0.30 + 0.01 * Direction)   Count[7] = Count[7] + W;
   if(DR >= 0.35 + 0.01 * Direction)   Count[8] = Count[8] + W;
   if(DR >= 0.40 + 0.01 * Direction)   Count[9] = Count[9] + W;
}

double AdjustCentrality(double Centrality, double Shift)
{
   double AdjustedCentrality = Centrality;

   double HF = CentralityToHF(Centrality);
   HF = HF + Shift;

   double L = 0.0;
   double R = 1.0;
   double Tolerance = 0.001;

   if(CentralityToHF(L) <= HF)
      return 0;
   if(CentralityToHF(R) >= HF)
      return 1;

   while(R - L > Tolerance)
   {
      double C = (L + R) / 2;
      double Check = CentralityToHF(C);

      if(Check >= HF)
         L = C;
      else
         R = C;
   }

   AdjustedCentrality = (L + R) / 2;

   return AdjustedCentrality;
}

double CentralityToHF(double C)
{
   double P[9] = {4518, -2.057e4, 5.406e4, -1.099e5, 1.387e5, -5.531e4, -7.506e4, 9.466e4, -3.11e4};

   double Result = 0;
   for(int i = 8; i >= 0; i--)
      Result = Result * C + P[i];

   return Result;
}



