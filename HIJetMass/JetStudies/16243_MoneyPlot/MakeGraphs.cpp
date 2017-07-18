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

#define PI 3.14159265358979323846264338327950288479716939937510
#define MASSBINCOUNT 9
#define ZGBINCOUNT 10
#define DRBINCOUNT 15

#define TRIGGER_NONE 0
#define TRIGGER_100 1
#define TRIGGER_80 2
#define TRIGGER_60 3

int main(int argc, char *argv[]);
int GetBin(double X, double Edge[], int BinCount);
void InitializeVectors(vector<int> A[5][6], int Size);
void InitializeVectors(vector<double> A[5][6], int Size);
void InitializeVectors(vector<double> A[6], int Size);

int main(int argc, char *argv[])
{
   double FudgeFactor = 1.0;   // Watch out for these factors!  If it's not (1.0, 1.0, 0.0) it's just experimentation!
   double FudgeA = 0.80;
   double FudgeB = 0.016;

   FudgeFactor = 1.0;
   FudgeA = 1.0;
   FudgeB = 0.0;

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " SDChoice IsMC=Y PTHatMin Tag" << endl;
      cerr << "Usage: " << argv[0] << " SDChoice IsMC=N Trigger=(100|80|60) Tag" << endl;
   }

   SetThesisStyle();

   int SD;
   if(argv[1][0] == '0')   SD = 0;
   else                    SD = 7;

   bool IsMC;
   if(argv[2][0] == 'Y')   IsMC = true;
   else                    IsMC = false;

   double MCWeightMax = 1000000;

   string Tag = argv[4];

   cout << "Running with SD = " << SD << ", MC = " << IsMC << ", Weight max = " << MCWeightMax << endl;

   int TriggerSelection = TRIGGER_NONE;
   if(IsMC == false && string(argv[3]) == "100")
      TriggerSelection = TRIGGER_100;
   else if(IsMC == false && string(argv[3]) == "80")
      TriggerSelection = TRIGGER_80;
   else if(IsMC == false && string(argv[3]) == "60")
      TriggerSelection = TRIGGER_60;

   double PTHatMin = 0;
   if(IsMC == true)
      PTHatMin = atof(argv[3]);

   string FileNameData = "AAData16241/AAData.root";
   string FileNameSmear = "PPDataHighPTJet_16153.root";
   if(IsMC == true)
   {
      // FileNameData = "AA6DijetCymbal.root";
      // FileNameSmear = "PP6DijetCymbal.root";
      
      FileNameData = "PowerfulAA.root";
      FileNameSmear = "PowerfulPP.root";
   }
   if(IsMC == false && TriggerSelection != TRIGGER_NONE)
      FileNameData = "AADataPrescale16241/AADataPrescale.root";

   double SmearJump = 1;

   double CBinEdge[5+1] = {0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBinEdge[6+1] = {120, 140, 160, 180, 200, 300, 500};

   // double MassBinEdge[MASSBINCOUNT+1] = {0.00, 0.02, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30};
   double MassBinEdge[MASSBINCOUNT+1] = {0.00, 0.04, 0.06, 0.08, 0.10, 0.12, 0.15, 0.18, 0.21, 0.26};

   double ZGBinEdge[ZGBINCOUNT+1] = {0};
   for(int i = 0; i <= ZGBINCOUNT; i++)
      ZGBinEdge[i] = 0.5 / ZGBINCOUNT * i;
   double DRBinEdge[DRBINCOUNT+1] = {0};
   for(int i = 0; i <= DRBINCOUNT; i++)
      DRBinEdge[i] = 0.4 / DRBINCOUNT * i + 0.1;
   double DR0BinEdge[DRBINCOUNT+1] = {0};
   for(int i = 0; i <= DRBINCOUNT; i++)
      DR0BinEdge[i] = 0.5 / DRBINCOUNT * i + 0.0;

   TFile FCentrality("CentralityDependence.root");

   TProfile2D *HMeanShift = (TProfile2D *)FCentrality.Get("HMBCymbalMean");

   TGraph *GMBRMS = (TGraph *)FCentrality.Get("AADataMB");
   TGraph *GSmearRMS = (TGraph *)FCentrality.Get("SmearPPDataInJet2");
   if(IsMC == true)
   {
      GMBRMS = (TGraph *)FCentrality.Get("CymbalMB");
      GSmearRMS = (TGraph *)FCentrality.Get("SmearPP6DijetInJet16264Cymbal");
   }

   TFile FData(FileNameData.c_str());
   TFile FSmear(FileNameSmear.c_str());

   TTree *TData = (TTree *)FData.Get("T");
   TTree *TSmear = (TTree *)FSmear.Get("OutputTree");

   double DataSDRecoDR, DataSDSubJetPT1, DataSDSubJetPT2, DataSDMass, DataNewJetPT, DataJetPT, DataJetEta, DataJetPhi;
   double DataMCWeight = 1, DataCentrality, DataPTHat = 150;
   bool DataPassHLT = true;
   if(SD == 7)
   {
      TData->SetBranchAddress("SubJetDR7", &DataSDRecoDR);
      TData->SetBranchAddress("SubJet1PT7", &DataSDSubJetPT1);
      TData->SetBranchAddress("SubJet2PT7", &DataSDSubJetPT2);
      TData->SetBranchAddress("SDMass7", &DataSDMass);
   }
   else
   {
      TData->SetBranchAddress("SubJetDR0", &DataSDRecoDR);
      TData->SetBranchAddress("SubJet1PT0", &DataSDSubJetPT1);
      TData->SetBranchAddress("SubJet2PT0", &DataSDSubJetPT2);
      TData->SetBranchAddress("SDMass0", &DataSDMass);
   }
   TData->SetBranchAddress("MatchPT", &DataNewJetPT);
   TData->SetBranchAddress("JetPT", &DataJetPT);
   TData->SetBranchAddress("JetEta", &DataJetEta);
   TData->SetBranchAddress("JetPhi", &DataJetPhi);
   if(IsMC == true)
      TData->SetBranchAddress("MCWeight", &DataMCWeight);
   if(IsMC == true)
      TData->SetBranchAddress("PTHat", &DataPTHat);
   TData->SetBranchAddress("Centrality", &DataCentrality);
   if(IsMC == false)
   {
      if(TriggerSelection == TRIGGER_NONE || TriggerSelection == TRIGGER_100)
         TData->SetBranchAddress("PassPbPb100", &DataPassHLT);
      if(TriggerSelection == TRIGGER_80)
         TData->SetBranchAddress("PassPbPb80", &DataPassHLT);
      if(TriggerSelection == TRIGGER_60)
         TData->SetBranchAddress("PassPbPb60", &DataPassHLT);
   }

   double SmearSDRecoDR, SmearSDZG, SmearSDMass, SmearSDPT, SmearNewJetPT, SmearNewJetEta, SmearNewJetPhi;
   double SmearMCWeight = 1, SmearPTInJet, SmearRho, SmearTotalPT, SmearCentrality, SmearPTHat = 150;
   bool PassFilter = true, PassHLT = true;
   if(SD == 7)
   {
      TSmear->SetBranchAddress("BestJetDR2", &SmearSDRecoDR);
      TSmear->SetBranchAddress("BestJetZG2", &SmearSDZG);
      TSmear->SetBranchAddress("BestJetSDMass2", &SmearSDMass);
      TSmear->SetBranchAddress("BestJetSDPT2", &SmearSDPT);
   }
   else
   {
      TSmear->SetBranchAddress("BestJetDR", &SmearSDRecoDR);
      TSmear->SetBranchAddress("BestJetZG", &SmearSDZG);
      TSmear->SetBranchAddress("BestJetSDMass", &SmearSDMass);
      TSmear->SetBranchAddress("BestJetSDPT", &SmearSDPT);
   }
   TSmear->SetBranchAddress("BestJetPT", &SmearNewJetPT);
   TSmear->SetBranchAddress("BestJetEta", &SmearNewJetEta);
   TSmear->SetBranchAddress("BestJetPhi", &SmearNewJetPhi);
   if(IsMC == true)
      TSmear->SetBranchAddress("MCWeight", &SmearMCWeight);
   if(IsMC == true)
      TSmear->SetBranchAddress("PTHat", &SmearPTHat);
   TSmear->SetBranchAddress("TotalPTInJet", &SmearPTInJet);
   TSmear->SetBranchAddress("Rho", &SmearRho);
   TSmear->SetBranchAddress("TotalPT", &SmearTotalPT);
   TSmear->SetBranchAddress("Centrality", &SmearCentrality);
   if(IsMC == false)
   {
      TSmear->SetBranchAddress("PassFilter", &PassFilter);
      TSmear->SetBranchAddress("PassHLT", &PassHLT);
   }

   // TFile FDataSystematics(Form("CombinedSystematics_Data16141_%d.root", SD));
   // TFile FSmearSystematics(Form("CombinedSystematics_All16141_%d.root", SD));
   TFile FDataSystematics(Form("CombinedSystematics_Data16213_%d.root", SD));
   TFile FSmearSystematics(Form("CombinedSystematics_All16213_%d.root", SD));

   TFile OutputFile(Form("Graphs_%s.root", Tag.c_str()), "RECREATE");

   int DataEntryCount = TData->GetEntries() * 1.00;
   int SmearEntryCount = TSmear->GetEntries() * 1.00;

   ProgressBar BarData(cout, DataEntryCount);
   ProgressBar BarSmear(cout, SmearEntryCount);

   BarData.SetStyle(0);
   BarSmear.SetStyle(2);

   PdfFileHelper PdfFile("SanityCheck_" + Tag + ".pdf");
   PdfFile.AddTextPage("Sanity checks!");

   // DataHelper DHFile("Workspace.dh");

   TGraphAsymmErrors *DataError[5][6] = {{0}};
   TGraphAsymmErrors *SmearError[5][6] = {{0}};
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         DataError[i][j] = (TGraphAsymmErrors *)FDataSystematics.Get(Form("GRatio_C%d_P%d", i, j));
         SmearError[i][j] = (TGraphAsymmErrors *)FSmearSystematics.Get(Form("GRatio_C%d_P%d", i, j));
      }
   }

   // Step 1 - get groomedPT fraction and derive reweighting
   // We don't do this anymore!  There is no need to do this!

   // Step 2 - let's look at PT spectrum to make sure we don't see weird surprises here
   vector<double> DataPT[5][6];
   InitializeVectors(DataPT, 50);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      if(DataEntryCount < 200 || (iE % (DataEntryCount / 300)) == 0)
         BarData.Print();

      TData->GetEntry(iE);
      if(DataPassHLT == false)
         continue;

      if(IsMC == true && DataPTHat < PTHatMin)
         continue;

      if(IsMC == true)
      {
         if(DataPTHat < 220 && DataPTHat > 170)
            DataMCWeight = DataMCWeight / 1.08366;
         if(DataPTHat > 540)
            DataMCWeight = DataMCWeight / (1 - 0.4243);
      }

      int iC = GetBin(DataCentrality, CBinEdge, 5);
      int iPT = GetBin(DataJetPT, PTBinEdge, 6);

      if(iC < 0 || iPT < 0)
         continue;

      if(fabs(DataJetEta) > 1.3)
         continue;
      if(DataMCWeight > MCWeightMax)
         continue;

      double JetPercentage = (DataJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
      int JetBin = JetPercentage * 50;

      DataPT[iC][iPT][JetBin] = DataPT[iC][iPT][JetBin] + DataMCWeight;
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   vector<double> SmearPT[5][6];
   InitializeVectors(SmearPT, 50);

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE = iE + SmearJump)
   {
      BarSmear.Update(iE);
      if(SmearEntryCount < 200 || (iE % (SmearEntryCount / 300)) == 0)
         BarSmear.Print();

      TSmear->GetEntry(iE);
      if(PassFilter == false || PassHLT == false)
         continue;
      
      if(IsMC == true && SmearPTHat < PTHatMin)
         continue;

      if(IsMC == true)
      {
         if(SmearPTHat < 220 && SmearPTHat > 170)
            SmearMCWeight = SmearMCWeight / 1.08366;
      }
      
      if(HMeanShift != NULL)
      {
         int EtaBin = (int)(fabs(SmearNewJetEta) * 50) + 1;
         int CentralityBin = (int)(SmearCentrality * 0.5) + 1;
         SmearNewJetPT = SmearNewJetPT + HMeanShift->GetBinContent(CentralityBin, EtaBin);
      }

      int iC = GetBin(SmearCentrality / 100, CBinEdge, 5);
      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;

      double JetPercentage = (SmearNewJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
      int JetBin = JetPercentage * 50;

      double TargetRMS, SmearRMS, Dummy;
      GMBRMS->GetPoint((int)SmearCentrality, Dummy, TargetRMS);
      GSmearRMS->GetPoint((int)SmearCentrality, Dummy, SmearRMS);
      TargetRMS = TargetRMS * FudgeFactor * (FudgeA + FudgeB * SmearCentrality);

      double ExcessPT = SmearPTInJet - SmearRho * 0.4 * 0.4 * PI;
      double SmearWeight = exp(-ExcessPT * ExcessPT / (2 * TargetRMS * TargetRMS)) / exp(-ExcessPT * ExcessPT / (2 * SmearRMS * SmearRMS));

      SmearPT[iC][iPT][JetBin] = SmearPT[iC][iPT][JetBin] + SmearMCWeight * SmearWeight;
   }
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();

   // Step 3 - centrality dependence
   vector<double> DataCentralityBins[6];
   InitializeVectors(DataCentralityBins, PTHatMin);

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      if(DataEntryCount < 200 || (iE % (DataEntryCount / 300)) == 0)
         BarData.Print();

      TData->GetEntry(iE);
      if(DataPassHLT == false)
         continue;
      
      if(IsMC == true && DataPTHat < PTHatMin)
         continue;

      if(IsMC == true)
      {
         if(DataPTHat < 220 && DataPTHat > 170)
            DataMCWeight = DataMCWeight / 1.08366;
         if(DataPTHat > 540)
            DataMCWeight = DataMCWeight / (1 - 0.4243);
      }
      
      int iC = GetBin(DataCentrality, CBinEdge, 5);
      int iPT = GetBin(DataJetPT, PTBinEdge, 6);

      if(iC < 0 || iPT < 0)
         continue;

      if(fabs(DataJetEta) > 1.3)
         continue;
      if(DataMCWeight > MCWeightMax)
         continue;

      DataCentralityBins[iPT][DataCentrality*100] = DataCentralityBins[iPT][DataCentrality*100] + DataMCWeight;
   }
   BarData.Update(DataEntryCount);
   BarData.Print();
   BarData.PrintLine();

   vector<double> SmearCentralityBins[6];
   InitializeVectors(SmearCentralityBins, 100);

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE = iE + SmearJump)
   {
      BarSmear.Update(iE);
      if(SmearEntryCount < 200 || (iE % (SmearEntryCount / 300)) == 0)
         BarSmear.Print();

      TSmear->GetEntry(iE);
      if(PassFilter == false || PassHLT == false)
         continue;
      
      if(IsMC == true && SmearPTHat < PTHatMin)
         continue;

      if(IsMC == true)
      {
         if(SmearPTHat < 220 && SmearPTHat > 170)
            SmearMCWeight = SmearMCWeight / 1.08366;
      }

      if(HMeanShift != NULL)
      {
         int EtaBin = (int)(fabs(SmearNewJetEta) * 50) + 1;
         int CentralityBin = (int)(SmearCentrality * 0.5) + 1;
         SmearNewJetPT = SmearNewJetPT + HMeanShift->GetBinContent(CentralityBin, EtaBin);
      }

      int iC = GetBin(SmearCentrality / 100, CBinEdge, 5);
      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;

      double JetPercentage = (SmearNewJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
      int JetBin = JetPercentage * 50;
      double JetWeight = DataPT[iC][iPT][JetBin] / SmearPT[iC][iPT][JetBin];

      double TargetRMS, SmearRMS, Dummy;
      GMBRMS->GetPoint((int)SmearCentrality, Dummy, TargetRMS);
      GSmearRMS->GetPoint((int)SmearCentrality, Dummy, SmearRMS);
      TargetRMS = TargetRMS * FudgeFactor * (FudgeA + FudgeB * SmearCentrality);

      double ExcessPT = SmearPTInJet - SmearRho * 0.4 * 0.4 * PI;
      double SmearWeight = exp(-ExcessPT * ExcessPT / (2 * TargetRMS * TargetRMS)) / exp(-ExcessPT * ExcessPT / (2 * SmearRMS * SmearRMS));

      SmearCentralityBins[iPT][SmearCentrality] = SmearCentralityBins[iPT][SmearCentrality] + SmearMCWeight * SmearWeight * JetWeight;
   }   
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();

   // Step 3 - build the graphs!
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

   BarData.Update(0);
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      BarData.Update(iE);
      if(DataEntryCount < 200 || (iE % (DataEntryCount / 300)) == 0)
         BarData.Print();

      TData->GetEntry(iE);
      if(DataPassHLT == false)
         continue;

      int iC = GetBin(DataCentrality, CBinEdge, 5);
      int iPT = GetBin(DataJetPT, PTBinEdge, 6);
      if(iC < 0 || iPT < 0)
         continue;

      if(fabs(DataJetEta) > 1.3)
         continue;
      if(DataMCWeight > MCWeightMax)
         continue;
      
      if(IsMC == true && DataPTHat < PTHatMin)
         continue;

      if(IsMC == true)
      {
         if(DataPTHat < 220 && DataPTHat > 170)
            DataMCWeight = DataMCWeight / 1.08366;
         if(DataPTHat > 540)
            DataMCWeight = DataMCWeight / (1 - 0.4243);
      }

      double SDMassRatio = DataSDMass / DataNewJetPT;
      int SysBin = SDMassRatio / (0.40 / 160);

      double DataSDZG = min(DataSDSubJetPT1, DataSDSubJetPT2) / (DataSDSubJetPT1 + DataSDSubJetPT2);

      int iMassB = GetBin(SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iZGB = GetBin(DataSDZG, ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(DataSDRecoDR, DRBinEdge, DRBINCOUNT);
      int iDRB0 = GetBin(DataSDRecoDR, DR0BinEdge, DRBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double TotalWeight = DataMCWeight;
      double UpWeight = DataError[iC][iPT]->GetErrorYhigh(SysBin);
      double DownWeight = -DataError[iC][iPT]->GetErrorYlow(SysBin);

      if(DataSDRecoDR > 0.0)
         DataPreCutGrandTotal[iC][iPT] = DataPreCutGrandTotal[iC][iPT] + TotalWeight;
      if(DataSDRecoDR > 0.1)
      {
         DataCountMass     [iC][iPT][iMassB] = DataCountMass     [iC][iPT][iMassB] + TotalWeight;
         DataTotalMassX    [iC][iPT][iMassB] = DataTotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
         DataTotalMass     [iC][iPT][iMassB] = DataTotalMass     [iC][iPT][iMassB] + TotalWeight;
         DataTotalMass2    [iC][iPT][iMassB] = DataTotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
         DataTotalMassUp   [iC][iPT][iMassB] = DataTotalMassUp   [iC][iPT][iMassB] + TotalWeight * exp(UpWeight);
         DataTotalMassDown [iC][iPT][iMassB] = DataTotalMassDown [iC][iPT][iMassB] + TotalWeight * exp(DownWeight);
         DataCountZG       [iC][iPT][iZGB]   = DataCountZG       [iC][iPT][iZGB]   + TotalWeight;
         DataTotalZGX      [iC][iPT][iZGB]   = DataTotalZGX      [iC][iPT][iZGB]   + DataSDZG * TotalWeight;
         DataTotalZG       [iC][iPT][iZGB]   = DataTotalZG       [iC][iPT][iZGB]   + TotalWeight;
         DataTotalZG2      [iC][iPT][iZGB]   = DataTotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
         DataCountDR       [iC][iPT][iDRB]   = DataCountDR       [iC][iPT][iDRB]   + TotalWeight;
         DataTotalDRX      [iC][iPT][iDRB]   = DataTotalDRX      [iC][iPT][iDRB]   + DataSDRecoDR * TotalWeight;
         DataTotalDR       [iC][iPT][iDRB]   = DataTotalDR       [iC][iPT][iDRB]   + TotalWeight;
         DataTotalDR2      [iC][iPT][iDRB]   = DataTotalDR2      [iC][iPT][iDRB]   + TotalWeight * TotalWeight;
         DataGrandTotal    [iC][iPT]         = DataGrandTotal    [iC][iPT]         + TotalWeight;
      }
      if(DataSDRecoDR > 0.1 && DataSDRecoDR < 0.15)
      {
         Data0CountMass     [iC][iPT][iMassB] = Data0CountMass     [iC][iPT][iMassB] + TotalWeight;
         Data0TotalMassX    [iC][iPT][iMassB] = Data0TotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
         Data0TotalMass     [iC][iPT][iMassB] = Data0TotalMass     [iC][iPT][iMassB] + TotalWeight;
         Data0TotalMass2    [iC][iPT][iMassB] = Data0TotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
         Data0TotalMassUp   [iC][iPT][iMassB] = Data0TotalMassUp   [iC][iPT][iMassB] + TotalWeight * exp(UpWeight);
         Data0TotalMassDown [iC][iPT][iMassB] = Data0TotalMassDown [iC][iPT][iMassB] + TotalWeight * exp(DownWeight);
         Data0CountZG       [iC][iPT][iZGB]   = Data0CountZG       [iC][iPT][iZGB]   + TotalWeight;
         Data0TotalZGX      [iC][iPT][iZGB]   = Data0TotalZGX      [iC][iPT][iZGB]   + DataSDZG * TotalWeight;
         Data0TotalZG       [iC][iPT][iZGB]   = Data0TotalZG       [iC][iPT][iZGB]   + TotalWeight;
         Data0TotalZG2      [iC][iPT][iZGB]   = Data0TotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
         Data0CountDR       [iC][iPT][iDRB0]  = Data0CountDR       [iC][iPT][iDRB0]  + TotalWeight;
         Data0TotalDRX      [iC][iPT][iDRB0]  = Data0TotalDRX      [iC][iPT][iDRB0]  + DataSDRecoDR * TotalWeight;
         Data0TotalDR       [iC][iPT][iDRB0]  = Data0TotalDR       [iC][iPT][iDRB0]  + TotalWeight;
         Data0TotalDR2      [iC][iPT][iDRB0]  = Data0TotalDR2      [iC][iPT][iDRB0]  + TotalWeight * TotalWeight;
         Data0GrandTotal    [iC][iPT]         = Data0GrandTotal    [iC][iPT]         + TotalWeight;
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

   BarSmear.Update(0);
   for(int iE = 0; iE < SmearEntryCount; iE = iE + SmearJump)
   {
      BarSmear.Update(iE);
      if(SmearEntryCount < 200 || (iE % (SmearEntryCount / 300)) == 0)
         BarSmear.Print();

      TSmear->GetEntry(iE);
      if(PassFilter == false || PassHLT == false)
         continue;

      double SmearJetPT = SmearNewJetPT;
      if(HMeanShift != NULL)
      {
         int EtaBin = (int)(fabs(SmearNewJetEta) * 50) + 1;
         int CentralityBin = (int)(SmearCentrality * 0.5) + 1;
         SmearNewJetPT = SmearNewJetPT + HMeanShift->GetBinContent(CentralityBin, EtaBin);
      }

      int iC = GetBin(SmearCentrality / 100, CBinEdge, 5);
      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;
      
      if(IsMC == true && SmearPTHat < 100)
         continue;
      
      if(IsMC == true)
      {
         if(SmearPTHat < 220 && SmearPTHat > 170)
            SmearMCWeight = SmearMCWeight / 1.08366;
      }

      double TargetRMS, SmearRMS, Dummy;
      GMBRMS->GetPoint((int)SmearCentrality, Dummy, TargetRMS);
      GSmearRMS->GetPoint((int)SmearCentrality, Dummy, SmearRMS);
      TargetRMS = TargetRMS * FudgeFactor * (FudgeA + FudgeB * SmearCentrality);

      double JetPercentage = (SmearNewJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
      int JetBin = JetPercentage * 50;
      double JetWeight = DataPT[iC][iPT][JetBin] / SmearPT[iC][iPT][JetBin];

      double ExcessPT = SmearPTInJet - SmearRho * 0.4 * 0.4 * PI;
      double SmearWeight = exp(-ExcessPT * ExcessPT / (2 * TargetRMS * TargetRMS)) / exp(-ExcessPT * ExcessPT / (2 * SmearRMS * SmearRMS));

      double SDMassRatio = SmearSDMass / SmearJetPT;
      int SysBin = SDMassRatio / (0.40 / 160);

      int iMassB = GetBin(SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iZGB = GetBin(SmearSDZG, ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(SmearSDRecoDR, DRBinEdge, DRBINCOUNT);
      int iDRB0 = GetBin(SmearSDRecoDR, DR0BinEdge, DRBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double CentralityWeight = DataCentralityBins[iPT][SmearCentrality] / SmearCentralityBins[iPT][SmearCentrality];

      // JetWeight = 1;
      // CentralityWeight = 1;

      double TotalWeight = SmearMCWeight * SmearWeight * JetWeight * CentralityWeight;
      double UpWeight = SmearError[iC][iPT]->GetErrorYhigh(SysBin);
      double DownWeight = -SmearError[iC][iPT]->GetErrorYlow(SysBin);

      if(SmearSDRecoDR > 0.0)
         SmearPreCutGrandTotal[iC][iPT] = SmearPreCutGrandTotal[iC][iPT] + TotalWeight;
      if(SmearSDRecoDR > 0.1)
      {
         SmearCountMass     [iC][iPT][iMassB] = SmearCountMass     [iC][iPT][iMassB] + TotalWeight;
         SmearTotalMassX    [iC][iPT][iMassB] = SmearTotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
         SmearTotalMass     [iC][iPT][iMassB] = SmearTotalMass     [iC][iPT][iMassB] + TotalWeight;
         SmearTotalMass2    [iC][iPT][iMassB] = SmearTotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
         SmearTotalMassUp   [iC][iPT][iMassB] = SmearTotalMassUp   [iC][iPT][iMassB] + TotalWeight * exp(UpWeight);
         SmearTotalMassDown [iC][iPT][iMassB] = SmearTotalMassDown [iC][iPT][iMassB] + TotalWeight * exp(DownWeight);
         SmearCountZG       [iC][iPT][iZGB]   = SmearCountZG       [iC][iPT][iZGB]   + TotalWeight;
         SmearTotalZGX      [iC][iPT][iZGB]   = SmearTotalZGX      [iC][iPT][iZGB]   + SmearSDZG * TotalWeight;
         SmearTotalZG       [iC][iPT][iZGB]   = SmearTotalZG       [iC][iPT][iZGB]   + TotalWeight;
         SmearTotalZG2      [iC][iPT][iZGB]   = SmearTotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
         SmearCountDR       [iC][iPT][iDRB]   = SmearCountDR       [iC][iPT][iDRB]   + TotalWeight;
         SmearTotalDRX      [iC][iPT][iDRB]   = SmearTotalDRX      [iC][iPT][iDRB]   + SmearSDRecoDR * TotalWeight;
         SmearTotalDR       [iC][iPT][iDRB]   = SmearTotalDR       [iC][iPT][iDRB]   + TotalWeight;
         SmearTotalDR2      [iC][iPT][iDRB]   = SmearTotalDR2      [iC][iPT][iDRB]   + TotalWeight * TotalWeight;
         SmearGrandTotal    [iC][iPT]         = SmearGrandTotal    [iC][iPT]         + TotalWeight;
      }
      if(SmearSDRecoDR > 0.1 && SmearSDRecoDR < 0.15)
      {
         Smear0CountMass     [iC][iPT][iMassB] = Smear0CountMass     [iC][iPT][iMassB] + TotalWeight;
         Smear0TotalMassX    [iC][iPT][iMassB] = Smear0TotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
         Smear0TotalMass     [iC][iPT][iMassB] = Smear0TotalMass     [iC][iPT][iMassB] + TotalWeight;
         Smear0TotalMass2    [iC][iPT][iMassB] = Smear0TotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
         Smear0TotalMassUp   [iC][iPT][iMassB] = Smear0TotalMassUp   [iC][iPT][iMassB] + TotalWeight * exp(UpWeight);
         Smear0TotalMassDown [iC][iPT][iMassB] = Smear0TotalMassDown [iC][iPT][iMassB] + TotalWeight * exp(DownWeight);
         Smear0CountZG       [iC][iPT][iZGB]   = Smear0CountZG       [iC][iPT][iZGB]   + TotalWeight;
         Smear0TotalZGX      [iC][iPT][iZGB]   = Smear0TotalZGX      [iC][iPT][iZGB]   + SmearSDZG * TotalWeight;
         Smear0TotalZG       [iC][iPT][iZGB]   = Smear0TotalZG       [iC][iPT][iZGB]   + TotalWeight;
         Smear0TotalZG2      [iC][iPT][iZGB]   = Smear0TotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
         Smear0CountDR       [iC][iPT][iDRB0]  = Smear0CountDR       [iC][iPT][iDRB0]  + TotalWeight;
         Smear0TotalDRX      [iC][iPT][iDRB0]  = Smear0TotalDRX      [iC][iPT][iDRB0]  + SmearSDRecoDR * TotalWeight;
         Smear0TotalDR       [iC][iPT][iDRB0]  = Smear0TotalDR       [iC][iPT][iDRB0]  + TotalWeight;
         Smear0TotalDR2      [iC][iPT][iDRB0]  = Smear0TotalDR2      [iC][iPT][iDRB0]  + TotalWeight * TotalWeight;
         Smear0GrandTotal    [iC][iPT]         = Smear0GrandTotal    [iC][iPT]         + TotalWeight;
      }
   }
   BarSmear.Update(SmearEntryCount);
   BarSmear.Print();
   BarSmear.PrintLine();

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 6; iPT++)
      {
         PdfFile.AddTextPage(Form("C %.02f-%.02f, PT %.0f-%.0f", CBinEdge[iC], CBinEdge[iC+1], PTBinEdge[iPT], PTBinEdge[iPT+1]));

         TGraphAsymmErrors GMassData, GMassSmear, GMassDataSys, GMassSmearSys, GZGData, GZGSmear, GDRData, GDRSmear;
         TGraphAsymmErrors GMassData0, GMassSmear0, GMassDataSys0, GMassSmearSys0, GZGData0, GZGSmear0, GDRData0, GDRSmear0;

         GMassData.SetNameTitle(Form("MassData_%d_%d", iC, iPT), "");
         GMassDataSys.SetNameTitle(Form("MassDataSys_%d_%d", iC, iPT), "");
         GMassSmear.SetNameTitle(Form("MassSmear_%d_%d", iC, iPT), "");
         GMassSmearSys.SetNameTitle(Form("MassSmearSys_%d_%d", iC, iPT), "");
         GZGData.SetNameTitle(Form("ZGData_%d_%d", iC, iPT), "");
         GZGSmear.SetNameTitle(Form("ZGSmear_%d_%d", iC, iPT), "");
         GDRData.SetNameTitle(Form("DRData_%d_%d", iC, iPT), "");
         GDRSmear.SetNameTitle(Form("DRSmear_%d_%d", iC, iPT), "");
         GMassData0.SetNameTitle(Form("MassData0_%d_%d", iC, iPT), "");
         GMassDataSys0.SetNameTitle(Form("MassDataSys0_%d_%d", iC, iPT), "");
         GMassSmear0.SetNameTitle(Form("MassSmear0_%d_%d", iC, iPT), "");
         GMassSmearSys0.SetNameTitle(Form("MassSmearSys0_%d_%d", iC, iPT), "");
         GZGData0.SetNameTitle(Form("ZGData0_%d_%d", iC, iPT), "");
         GZGSmear0.SetNameTitle(Form("ZGSmear0_%d_%d", iC, iPT), "");
         GDRData0.SetNameTitle(Form("DRData0_%d_%d", iC, iPT), "");
         GDRSmear0.SetNameTitle(Form("DRSmear0_%d_%d", iC, iPT), "");

         GMassData.SetMarkerStyle(20);
         GMassSmear.SetMarkerStyle(20);
         GMassDataSys.SetMarkerStyle(20);
         GMassSmearSys.SetMarkerStyle(20);
         GZGData.SetMarkerStyle(20);
         GZGSmear.SetMarkerStyle(20);
         GDRData.SetMarkerStyle(20);
         GDRSmear.SetMarkerStyle(20);
         GMassData0.SetMarkerStyle(20);
         GMassSmear0.SetMarkerStyle(20);
         GMassDataSys0.SetMarkerStyle(20);
         GMassSmearSys0.SetMarkerStyle(20);
         GZGData0.SetMarkerStyle(20);
         GZGSmear0.SetMarkerStyle(20);
         GDRData0.SetMarkerStyle(20);
         GDRSmear0.SetMarkerStyle(20);
         GMassData.SetMarkerSize(0.7);
         GMassSmear.SetMarkerSize(0.7);
         GMassDataSys.SetMarkerSize(0.7);
         GMassSmearSys.SetMarkerSize(0.7);
         GZGData.SetMarkerSize(0.7);
         GZGSmear.SetMarkerSize(0.7);
         GDRData.SetMarkerSize(0.7);
         GDRSmear.SetMarkerSize(0.7);
         GMassData0.SetMarkerSize(0.7);
         GMassSmear0.SetMarkerSize(0.7);
         GMassDataSys0.SetMarkerSize(0.7);
         GMassSmearSys0.SetMarkerSize(0.7);
         GZGData0.SetMarkerSize(0.7);
         GZGSmear0.SetMarkerSize(0.7);
         GDRData0.SetMarkerSize(0.7);
         GDRSmear0.SetMarkerSize(0.7);

         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / DataGrandTotal[iC][iPT];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = DataTotalMassX[iC][iPT][i] / DataCountMass[iC][iPT][i];
            double Mass = DataTotalMass[iC][iPT][i] / MassBinSize * Factor;
            double MassRMS = sqrt(DataTotalMass2[iC][iPT][i]) / MassBinSize * Factor;
            double MassUp = DataTotalMassUp[iC][iPT][i] / MassBinSize * Factor;
            double MassDown = DataTotalMassDown[iC][iPT][i] / MassBinSize * Factor;

            GMassData.SetPoint(i, MassX, Mass);
            GMassData.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys.SetPoint(i, MassX, Mass);
            GMassDataSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / DataGrandTotal[iC][iPT];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = DataTotalZGX[iC][iPT][i] / DataCountZG[iC][iPT][i];
            double ZG = DataTotalZG[iC][iPT][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(DataTotalZG2[iC][iPT][i]) / ZGBinSize * Factor;

            GZGData.SetPoint(i, ZGX, ZG);
            GZGData.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / DataGrandTotal[iC][iPT];

            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = DataTotalDRX[iC][iPT][i] / DataCountDR[iC][iPT][i];
            double DR = DataTotalDR[iC][iPT][i] / DRBinSize * Factor;
            double DRRMS = sqrt(DataTotalDR2[iC][iPT][i]) / DRBinSize * Factor;

            GDRData.SetPoint(i, DRX, DR);
            GDRData.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
        
         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Data0GrandTotal[iC][iPT];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = Data0TotalMassX[iC][iPT][i] / Data0CountMass[iC][iPT][i];
            double Mass = Data0TotalMass[iC][iPT][i] / MassBinSize * Factor;
            double MassRMS = sqrt(Data0TotalMass2[iC][iPT][i]) / MassBinSize * Factor;
            double MassUp = Data0TotalMassUp[iC][iPT][i] / MassBinSize * Factor;
            double MassDown = Data0TotalMassDown[iC][iPT][i] / MassBinSize * Factor;

            GMassData0.SetPoint(i, MassX, Mass);
            GMassData0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys0.SetPoint(i, MassX, Mass);
            GMassDataSys0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Data0GrandTotal[iC][iPT];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = Data0TotalZGX[iC][iPT][i] / Data0CountZG[iC][iPT][i];
            double ZG = Data0TotalZG[iC][iPT][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(Data0TotalZG2[iC][iPT][i]) / ZGBinSize * Factor;

            GZGData0.SetPoint(i, ZGX, ZG);
            GZGData0.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            // double Factor = 1 / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Data0GrandTotal[iC][iPT];

            double DRBinSize = DR0BinEdge[i+1] - DR0BinEdge[i];
            double DRX = Data0TotalDRX[iC][iPT][i] / Data0CountDR[iC][iPT][i];
            double DR = Data0TotalDR[iC][iPT][i] / DRBinSize * Factor;
            double DRRMS = sqrt(Data0TotalDR2[iC][iPT][i]) / DRBinSize * Factor;

            GDRData0.SetPoint(i, DRX, DR);
            GDRData0.SetPointError(i, DRX - DR0BinEdge[i], DR0BinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
  
         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            // double Factor = 1 / SmearGrandTotal[iC][iPT] * DataGrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / SmearGrandTotal[iC][iPT];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = SmearTotalMassX[iC][iPT][i] / SmearCountMass[iC][iPT][i];
            double Mass = SmearTotalMass[iC][iPT][i] / MassBinSize * Factor;
            double MassRMS = sqrt(SmearTotalMass2[iC][iPT][i]) / MassBinSize * Factor;
            double MassUp = SmearTotalMassUp[iC][iPT][i] / MassBinSize * Factor;
            double MassDown = SmearTotalMassDown[iC][iPT][i] / MassBinSize * Factor;

            GMassSmear.SetPoint(i, MassX, Mass);
            GMassSmear.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassSmearSys.SetPoint(i, MassX, Mass);
            GMassSmearSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            // double Factor = 1 / SmearGrandTotal[iC][iPT] * DataGrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / SmearGrandTotal[iC][iPT];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = SmearTotalZGX[iC][iPT][i] / SmearCountZG[iC][iPT][i];
            double ZG = SmearTotalZG[iC][iPT][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(SmearTotalZG2[iC][iPT][i]) / ZGBinSize * Factor;

            GZGSmear.SetPoint(i, ZGX, ZG);
            GZGSmear.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            // double Factor = 1 / SmearGrandTotal[iC][iPT] * DataGrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / SmearGrandTotal[iC][iPT];
            
            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = SmearTotalDRX[iC][iPT][i] / SmearCountDR[iC][iPT][i];
            double DR = SmearTotalDR[iC][iPT][i] / DRBinSize * Factor;
            double DRRMS = sqrt(SmearTotalDR2[iC][iPT][i]) / DRBinSize * Factor;

            GDRSmear.SetPoint(i, DRX, DR);
            GDRSmear.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }

         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            // double Factor = 1 / Smear0GrandTotal[iC][iPT] * Data0GrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Smear0GrandTotal[iC][iPT];

            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = Smear0TotalMassX[iC][iPT][i] / Smear0CountMass[iC][iPT][i];
            double Mass = Smear0TotalMass[iC][iPT][i] / MassBinSize * Factor;
            double MassRMS = sqrt(Smear0TotalMass2[iC][iPT][i]) / MassBinSize * Factor;
            double MassUp = Smear0TotalMassUp[iC][iPT][i] / MassBinSize * Factor;
            double MassDown = Smear0TotalMassDown[iC][iPT][i] / MassBinSize * Factor;

            GMassSmear0.SetPoint(i, MassX, Mass);
            GMassSmear0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassSmearSys0.SetPoint(i, MassX, Mass);
            GMassSmearSys0.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            // double Factor = 1 / Smear0GrandTotal[iC][iPT] * Data0GrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Smear0GrandTotal[iC][iPT];

            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = Smear0TotalZGX[iC][iPT][i] / Smear0CountZG[iC][iPT][i];
            double ZG = Smear0TotalZG[iC][iPT][i] / ZGBinSize * Factor;
            double ZGRMS = sqrt(Smear0TotalZG2[iC][iPT][i]) / ZGBinSize * Factor;

            GZGSmear0.SetPoint(i, ZGX, ZG);
            GZGSmear0.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            // double Factor = 1 / Smear0GrandTotal[iC][iPT] * Data0GrandTotal[iC][iPT] / DataPreCutGrandTotal[iC][iPT];
            double Factor = 1 / Smear0GrandTotal[iC][iPT];

            double DRBinSize = DR0BinEdge[i+1] - DR0BinEdge[i];
            double DRX = Smear0TotalDRX[iC][iPT][i] / Smear0CountDR[iC][iPT][i];
            double DR = Smear0TotalDR[iC][iPT][i] / DRBinSize * Factor;
            double DRRMS = sqrt(Smear0TotalDR2[iC][iPT][i]) / DRBinSize * Factor;

            GDRSmear0.SetPoint(i, DRX, DR);
            GDRSmear0.SetPointError(i, DRX - DR0BinEdge[i], DR0BinEdge[i+1] - DRX, DRRMS, DRRMS);
         }

         GMassData.Write();
         GMassSmear.Write();
         GMassDataSys.Write();
         GMassSmearSys.Write();
         GZGData.Write();
         GZGSmear.Write();
         GDRData.Write();
         GDRSmear.Write();
         GMassData0.Write();
         GMassSmear0.Write();
         GMassDataSys0.Write();
         GMassSmearSys0.Write();
         GZGData0.Write();
         GZGSmear0.Write();
         GDRData0.Write();
         GDRSmear0.Write();

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
      }
   }

   // DHFile.SaveToFile("Workspace.dh");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.Close();

   FSmearSystematics.Close();
   FDataSystematics.Close();

   FSmear.Close();
   // FData.Close();

   return 0;
}

int GetBin(double X, double Edge[], int BinCount)
{
   int Bin = -1;
   for(int i = 0; i < BinCount; i++)
      if(Edge[i] <= X && X < Edge[i+1])
         Bin = i;

   return Bin;
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




