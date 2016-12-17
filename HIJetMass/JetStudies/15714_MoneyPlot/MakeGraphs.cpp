#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
// #include "DataHelper.h"

#define PI 3.14159265358979323846264338327950288479716939937510
#define MASSBINCOUNT 9
#define ZGBINCOUNT 10
#define DRBINCOUNT 15

int main(int argc, char *argv[]);
int GetBin(double X, double Edge[], int BinCount);
void InitializeVectors(vector<int> A[5][6], int Size);
void InitializeVectors(vector<double> A[5][6], int Size);

int main(int argc, char *argv[])
{
   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " SDChoice IsMC PTHatChoice Tag" << endl;
   }

   SetThesisStyle();

   int SD;
   if(argv[1][0] == '0')   SD = 0;
   else                    SD = 7;

   bool IsMC;
   if(argv[2][0] == 'Y')   IsMC = true;
   else                    IsMC = false;

   double MCWeightMax;
   if(argv[3][0] == '8')   MCWeightMax = 10000000;
   else                    MCWeightMax = 10000;

   string Tag = argv[4];

   cout << "Running with SD = " << SD << ", MC = " << IsMC << ", Weight max = " << MCWeightMax << endl;

   string FileNameData = "AAData_NoCrossSection.root";
   string FileNameSmear = "PPDataHightPTJet.root";
   if(IsMC == true)
   {
      FileNameData = "StraightAA6Dijet.root";
      FileNameSmear = "ScaledResult13PP6Dijet.root";
   }

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

   double DataRMS[5] = {17.2, 12.8, 7.5, 3.1, 1.0};
   double MCRMS[5] = {18.0, 13.3, 7.7, 3.4, 1.1};
   // double MCRMS[5] = {22.0, 12.3, 6.7, 2.7, 1.1};
   double BigRMS = 32.17;

   double *RMS = NULL;
   if(IsMC == true)
      RMS = MCRMS;
   else
      RMS = DataRMS;

   TFile FData(FileNameData.c_str());
   TFile FSmear(FileNameSmear.c_str());

   TTree *TData = (TTree *)FData.Get("Tree");
   TTree *TSmear = (TTree *)FSmear.Get("OutputTree");

   double DataSDRecoDR[10], DataSDZG[10], DataSDMass[10], DataSDPT[10], DataNewJetPT, DataJetPT, DataJetEta, DataJetPhi;
   double DataMCWeight = 1, DataCentrality;
   TData->SetBranchAddress("SDRecoDR", &DataSDRecoDR);
   TData->SetBranchAddress("SDZG", &DataSDZG);
   TData->SetBranchAddress("SDMass", &DataSDMass);
   TData->SetBranchAddress("SDPT", &DataSDPT);
   TData->SetBranchAddress("NewJetPT", &DataNewJetPT);
   TData->SetBranchAddress("JetPT", &DataJetPT);
   TData->SetBranchAddress("JetEta", &DataJetEta);
   TData->SetBranchAddress("JetPhi", &DataJetPhi);
   if(IsMC == true)
      TData->SetBranchAddress("MCWeight", &DataMCWeight);
   TData->SetBranchAddress("Centrality", &DataCentrality);

   double SmearSDRecoDR, SmearSDZG, SmearSDMass, SmearSDPT, SmearNewJetPT, SmearNewJetEta, SmearNewJetPhi;
   double SmearMCWeight = 1, SmearPTInJet, SmearRho, SmearTotalPT;
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
   TSmear->SetBranchAddress("TotalPTInJet", &SmearPTInJet);
   TSmear->SetBranchAddress("Rho", &SmearRho);
   TSmear->SetBranchAddress("TotalPT", &SmearTotalPT);

   TFile FDataSystematics("CombinedSystematics_Data15713.root");
   TFile FSmearSystematics("CombinedSystematics_All15713.root");

   TFile OutputFile(Form("Graphs_%s.root", Tag.c_str()), "RECREATE");

   int DataEntryCount = TData->GetEntries();
   int SmearEntryCount = TSmear->GetEntries();

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
   vector<double> DataGroomed[5][6];
   InitializeVectors(DataGroomed, 50);

   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      TData->GetEntry(iE);

      int iC = GetBin(DataCentrality, CBinEdge, 5);
      int iPT = GetBin(DataJetPT, PTBinEdge, 6);

      if(iC < 0 || iPT < 0)
         continue;

      if(fabs(DataJetEta) > 1.3)
         continue;
      if(DataMCWeight > MCWeightMax)
         continue;

      double Ratio = DataSDPT[SD] / DataNewJetPT;
      int RatioBin = Ratio * 50;
      if(RatioBin < 0)   continue;
      if(RatioBin >= 50) RatioBin = 49;
      DataGroomed[iC][iPT][RatioBin] = DataGroomed[iC][iPT][RatioBin] + DataMCWeight;
   }

   vector<double> SmearGroomed[5][6];
   InitializeVectors(SmearGroomed, 50);

   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      TSmear->GetEntry(iE);

      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;

      for(int iC = 0; iC < 5; iC++)
      {
         double ExcessPT = (SmearTotalPT - SmearRho * 1.2 * 1.2 * PI) / 9;
         double AdjustedExcessPT = ((ExcessPT > 0) ? ExcessPT : ExcessPT * 9);
         double AdjustedSmearWeight = exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * RMS[iC] * RMS[iC]))
            / exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * BigRMS * BigRMS));
         if(AdjustedExcessPT < 0)
            AdjustedSmearWeight = AdjustedSmearWeight * 9;

         double Ratio = SmearSDPT / SmearNewJetPT;
         int RatioBin = Ratio * 50;
         if(RatioBin < 0)   continue;
         if(RatioBin >= 50) RatioBin = 49;
         SmearGroomed[iC][iPT][RatioBin] = SmearGroomed[iC][iPT][RatioBin] + SmearMCWeight * AdjustedSmearWeight;
      }
   }

   // Step 2 - let's look at PT spectrum to make sure we don't see weird surprises here
   vector<double> DataPT[5][6];
   InitializeVectors(DataPT, 50);

   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      TData->GetEntry(iE);

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

   vector<double> SmearPT[5][6];
   InitializeVectors(SmearPT, 50);

   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      TSmear->GetEntry(iE);

      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;

      double JetPercentage = (SmearNewJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
      int JetBin = JetPercentage * 50;

      double Ratio = SmearSDPT / SmearNewJetPT;
      int RatioBin = Ratio * 50;
      if(RatioBin < 0)   continue;
      if(RatioBin >= 50) RatioBin = 49;

      for(int iC = 0; iC < 5; iC++)
      {
         double ExcessPT = (SmearTotalPT - SmearRho * 1.2 * 1.2 * PI) / 9;
         double AdjustedExcessPT = ((ExcessPT > 0) ? ExcessPT : ExcessPT * 9);
         double AdjustedSmearWeight = exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * RMS[iC] * RMS[iC]))
            / exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * BigRMS * BigRMS));
         if(AdjustedExcessPT < 0)
            AdjustedSmearWeight = AdjustedSmearWeight * 9;

         double GroomedWeight = DataGroomed[iC][iPT][RatioBin] / SmearGroomed[iC][iPT][RatioBin];

         SmearPT[iC][iPT][JetBin] = SmearPT[iC][iPT][JetBin] + SmearMCWeight * AdjustedSmearWeight * GroomedWeight;
      }
   }

   // Step 3 - build the graphs!
   double DataGrandTotal[5][6] = {{0}};
   vector<double> DataCountMass[5][6];      InitializeVectors(DataCountMass, MASSBINCOUNT);
   vector<double> DataTotalMassX[5][6];     InitializeVectors(DataTotalMassX, MASSBINCOUNT);
   vector<double> DataTotalMass[5][6];      InitializeVectors(DataTotalMass, MASSBINCOUNT);
   vector<double> DataTotalMass2[5][6];     InitializeVectors(DataTotalMass2, MASSBINCOUNT);
   vector<double> DataTotalMassUp[5][6];    InitializeVectors(DataTotalMassUp, MASSBINCOUNT);
   vector<double> DataTotalMassDown[5][6];  InitializeVectors(DataTotalMassDown, MASSBINCOUNT);
   vector<double> DataCountZG[5][6];        InitializeVectors(DataCountZG, ZGBINCOUNT);
   vector<double> DataTotalZGX[5][6];       InitializeVectors(DataTotalZGX, ZGBINCOUNT);
   vector<double> DataTotalZG[5][6];        InitializeVectors(DataTotalZG, ZGBINCOUNT);
   vector<double> DataTotalZG2[5][6];       InitializeVectors(DataTotalZG2, ZGBINCOUNT);
   vector<double> DataCountDR[5][6];        InitializeVectors(DataCountDR, DRBINCOUNT);
   vector<double> DataTotalDRX[5][6];       InitializeVectors(DataTotalDRX, DRBINCOUNT);
   vector<double> DataTotalDR[5][6];        InitializeVectors(DataTotalDR, DRBINCOUNT);
   vector<double> DataTotalDR2[5][6];       InitializeVectors(DataTotalDR2, DRBINCOUNT);

   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      TData->GetEntry(iE);

      int iC = GetBin(DataCentrality, CBinEdge, 5);
      int iPT = GetBin(DataJetPT, PTBinEdge, 6);
      if(iC < 0 || iPT < 0)
         continue;

      if(fabs(DataJetEta) > 1.3)
         continue;
      if(DataMCWeight > MCWeightMax)
         continue;
      if(DataSDRecoDR[SD] < 0.1)
         continue;

      double SDMassRatio = DataSDMass[SD] / DataNewJetPT;
      int SysBin = SDMassRatio / (0.40 / 160);

      int iMassB = GetBin(SDMassRatio, MassBinEdge, MASSBINCOUNT);
      int iZGB = GetBin(DataSDZG[SD], ZGBinEdge, ZGBINCOUNT);
      int iDRB = GetBin(DataSDRecoDR[SD], DRBinEdge, DRBINCOUNT);

      if(iMassB < 0 || iMassB >= MASSBINCOUNT)
         continue;

      double TotalWeight = DataMCWeight;
      double UpWeight = DataError[iC][iPT]->GetErrorYhigh(SysBin);
      double DownWeight = -DataError[iC][iPT]->GetErrorYlow(SysBin);

      DataGrandTotal    [iC][iPT]         = DataGrandTotal    [iC][iPT]         + TotalWeight;
      DataCountMass     [iC][iPT][iMassB] = DataCountMass     [iC][iPT][iMassB] + TotalWeight;
      DataTotalMassX    [iC][iPT][iMassB] = DataTotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
      DataTotalMass     [iC][iPT][iMassB] = DataTotalMass     [iC][iPT][iMassB] + TotalWeight;
      DataTotalMass2    [iC][iPT][iMassB] = DataTotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
      DataTotalMassUp   [iC][iPT][iMassB] = DataTotalMassUp   [iC][iPT][iMassB] + TotalWeight * pow(10, UpWeight);
      DataTotalMassDown [iC][iPT][iMassB] = DataTotalMassDown [iC][iPT][iMassB] + TotalWeight * pow(10, DownWeight);
      DataCountZG       [iC][iPT][iZGB]   = DataCountZG       [iC][iPT][iZGB]   + TotalWeight;
      DataTotalZGX      [iC][iPT][iZGB]   = DataTotalZGX      [iC][iPT][iZGB]   + DataSDZG[SD] * TotalWeight;
      DataTotalZG       [iC][iPT][iZGB]   = DataTotalZG       [iC][iPT][iZGB]   + TotalWeight;
      DataTotalZG2      [iC][iPT][iZGB]   = DataTotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
      DataCountDR       [iC][iPT][iDRB]   = DataCountDR       [iC][iPT][iDRB]   + TotalWeight;
      DataTotalDRX      [iC][iPT][iDRB]   = DataTotalDRX      [iC][iPT][iDRB]   + DataSDRecoDR[SD] * TotalWeight;
      DataTotalDR       [iC][iPT][iDRB]   = DataTotalDR       [iC][iPT][iDRB]   + TotalWeight;
      DataTotalDR2      [iC][iPT][iDRB]   = DataTotalDR2      [iC][iPT][iDRB]   + TotalWeight * TotalWeight;
   }

   double SmearGrandTotal[5][6] = {{0}};
   vector<double> SmearCountMass[5][6];      InitializeVectors(SmearCountMass, MASSBINCOUNT);
   vector<double> SmearTotalMassX[5][6];     InitializeVectors(SmearTotalMassX, MASSBINCOUNT);
   vector<double> SmearTotalMass[5][6];      InitializeVectors(SmearTotalMass, MASSBINCOUNT);
   vector<double> SmearTotalMass2[5][6];     InitializeVectors(SmearTotalMass2, MASSBINCOUNT);
   vector<double> SmearTotalMassUp[5][6];    InitializeVectors(SmearTotalMassUp, MASSBINCOUNT);
   vector<double> SmearTotalMassDown[5][6];  InitializeVectors(SmearTotalMassDown, MASSBINCOUNT);
   vector<double> SmearCountZG[5][6];        InitializeVectors(SmearCountZG, ZGBINCOUNT);
   vector<double> SmearTotalZGX[5][6];       InitializeVectors(SmearTotalZGX, ZGBINCOUNT);
   vector<double> SmearTotalZG[5][6];        InitializeVectors(SmearTotalZG, ZGBINCOUNT);
   vector<double> SmearTotalZG2[5][6];       InitializeVectors(SmearTotalZG2, ZGBINCOUNT);
   vector<double> SmearCountDR[5][6];        InitializeVectors(SmearCountDR, DRBINCOUNT);
   vector<double> SmearTotalDRX[5][6];       InitializeVectors(SmearTotalDRX, DRBINCOUNT);
   vector<double> SmearTotalDR[5][6];        InitializeVectors(SmearTotalDR, DRBINCOUNT);
   vector<double> SmearTotalDR2[5][6];       InitializeVectors(SmearTotalDR2, DRBINCOUNT);

   for(int iE = 0; iE < SmearEntryCount; iE++)
   {
      TSmear->GetEntry(iE);

      int iPT = GetBin(SmearNewJetPT, PTBinEdge, 6);
      if(iPT < 0)
         continue;

      if(fabs(SmearNewJetEta) > 1.3)
         continue;
      if(SmearSDRecoDR < 0.1)
         continue;

      for(int iC = 0; iC < 5; iC++)
      {
         double JetPercentage = (SmearNewJetPT - PTBinEdge[iPT]) / (PTBinEdge[iPT+1] - PTBinEdge[iPT]);
         int JetBin = JetPercentage * 50;
         double JetWeight = DataPT[iC][iPT][JetBin] / SmearPT[iC][iPT][JetBin];

         double ExcessPT = (SmearTotalPT - SmearRho * 1.2 * 1.2 * PI) / 9;
         double AdjustedExcessPT = ((ExcessPT > 0) ? ExcessPT : ExcessPT * 9);
         double AdjustedSmearWeight = exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * RMS[iC] * RMS[iC]))
            / exp(-AdjustedExcessPT * AdjustedExcessPT / (2 * BigRMS * BigRMS));
         if(AdjustedExcessPT < 0)
            AdjustedSmearWeight = AdjustedSmearWeight * 9;

         double Ratio = SmearSDPT / SmearNewJetPT;
         int RatioBin = Ratio * 50;
         if(RatioBin < 0)   continue;
         if(RatioBin >= 50) RatioBin = 49;
         double GroomedWeight = DataGroomed[iC][iPT][RatioBin] / SmearGroomed[iC][iPT][RatioBin];

         double SDMassRatio = SmearSDMass / SmearNewJetPT;
         int SysBin = SDMassRatio / (0.40 / 160);

         int iMassB = GetBin(SDMassRatio, MassBinEdge, MASSBINCOUNT);
         int iZGB = GetBin(SmearSDZG, ZGBinEdge, ZGBINCOUNT);
         int iDRB = GetBin(SmearSDRecoDR, DRBinEdge, DRBINCOUNT);
         
         if(iMassB < 0 || iMassB >= MASSBINCOUNT)
            continue;

         double TotalWeight = SmearMCWeight * AdjustedSmearWeight * GroomedWeight * JetWeight;
         double UpWeight = SmearError[iC][iPT]->GetErrorYhigh(SysBin);
         double DownWeight = -SmearError[iC][iPT]->GetErrorYlow(SysBin);

         SmearGrandTotal    [iC][iPT]         = SmearGrandTotal    [iC][iPT]         + TotalWeight;
         SmearCountMass     [iC][iPT][iMassB] = SmearCountMass     [iC][iPT][iMassB] + TotalWeight;
         SmearTotalMassX    [iC][iPT][iMassB] = SmearTotalMassX    [iC][iPT][iMassB] + SDMassRatio * TotalWeight;
         SmearTotalMass     [iC][iPT][iMassB] = SmearTotalMass     [iC][iPT][iMassB] + TotalWeight;
         SmearTotalMass2    [iC][iPT][iMassB] = SmearTotalMass2    [iC][iPT][iMassB] + TotalWeight * TotalWeight;
         SmearTotalMassUp   [iC][iPT][iMassB] = SmearTotalMassUp   [iC][iPT][iMassB] + TotalWeight * pow(10, UpWeight);
         SmearTotalMassDown [iC][iPT][iMassB] = SmearTotalMassDown [iC][iPT][iMassB] + TotalWeight * pow(10, DownWeight);
         SmearCountZG       [iC][iPT][iZGB]   = SmearCountZG       [iC][iPT][iZGB]   + TotalWeight;
         SmearTotalZGX      [iC][iPT][iZGB]   = SmearTotalZGX      [iC][iPT][iZGB]   + SmearSDZG * TotalWeight;
         SmearTotalZG       [iC][iPT][iZGB]   = SmearTotalZG       [iC][iPT][iZGB]   + TotalWeight;
         SmearTotalZG2      [iC][iPT][iZGB]   = SmearTotalZG2      [iC][iPT][iZGB]   + TotalWeight * TotalWeight;
         SmearCountDR       [iC][iPT][iDRB]   = SmearCountDR       [iC][iPT][iDRB]   + TotalWeight;
         SmearTotalDRX      [iC][iPT][iDRB]   = SmearTotalDRX      [iC][iPT][iDRB]   + SmearSDRecoDR * TotalWeight;
         SmearTotalDR       [iC][iPT][iDRB]   = SmearTotalDR       [iC][iPT][iDRB]   + TotalWeight;
         SmearTotalDR2      [iC][iPT][iDRB]   = SmearTotalDR2      [iC][iPT][iDRB]   + TotalWeight * TotalWeight;
      }
   }

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 6; iPT++)
      {
         PdfFile.AddTextPage(Form("C %.02f-%.02f, PT %.0f-%.0f", CBinEdge[iC], CBinEdge[iC+1], PTBinEdge[iPT], PTBinEdge[iPT+1]));

         TGraphAsymmErrors GMassData, GMassSmear, GMassDataSys, GMassSmearSys, GZGData, GZGSmear, GDRData, GDRSmear;

         GMassData.SetNameTitle(Form("MassData_%d_%d", iC, iPT), "");
         GMassDataSys.SetNameTitle(Form("MassDataSys_%d_%d", iC, iPT), "");
         GMassSmear.SetNameTitle(Form("MassSmear_%d_%d", iC, iPT), "");
         GMassSmearSys.SetNameTitle(Form("MassSmearSys_%d_%d", iC, iPT), "");
         GZGData.SetNameTitle(Form("ZGData_%d_%d", iC, iPT), "");
         GZGSmear.SetNameTitle(Form("ZGSmear_%d_%d", iC, iPT), "");
         GDRData.SetNameTitle(Form("DRData_%d_%d", iC, iPT), "");
         GDRSmear.SetNameTitle(Form("DRSmear_%d_%d", iC, iPT), "");

         GMassData.SetMarkerStyle(20);
         GMassSmear.SetMarkerStyle(20);
         GMassDataSys.SetMarkerStyle(20);
         GMassSmearSys.SetMarkerStyle(20);
         GZGData.SetMarkerStyle(20);
         GZGSmear.SetMarkerStyle(20);
         GDRData.SetMarkerStyle(20);
         GDRSmear.SetMarkerStyle(20);
         GMassData.SetMarkerSize(0.7);
         GMassSmear.SetMarkerSize(0.7);
         GMassDataSys.SetMarkerSize(0.7);
         GMassSmearSys.SetMarkerSize(0.7);
         GZGData.SetMarkerSize(0.7);
         GZGSmear.SetMarkerSize(0.7);
         GDRData.SetMarkerSize(0.7);
         GDRSmear.SetMarkerSize(0.7);

         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = DataTotalMassX[iC][iPT][i] / DataCountMass[iC][iPT][i];
            double Mass = DataTotalMass[iC][iPT][i] / MassBinSize / DataGrandTotal[iC][iPT];
            double MassRMS = sqrt(DataTotalMass2[iC][iPT][i]) / DataGrandTotal[iC][iPT] / MassBinSize;
            double MassUp = DataTotalMassUp[iC][iPT][i] / MassBinSize / DataGrandTotal[iC][iPT];
            double MassDown = DataTotalMassDown[iC][iPT][i] / MassBinSize / DataGrandTotal[iC][iPT];

            GMassData.SetPoint(i, MassX, Mass);
            GMassData.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassDataSys.SetPoint(i, MassX, Mass);
            GMassDataSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = DataTotalZGX[iC][iPT][i] / DataCountZG[iC][iPT][i];
            double ZG = DataTotalZG[iC][iPT][i] / ZGBinSize / DataGrandTotal[iC][iPT];
            double ZGRMS = sqrt(DataTotalZG2[iC][iPT][i]) / DataGrandTotal[iC][iPT] / ZGBinSize;

            GZGData.SetPoint(i, ZGX, ZG);
            GZGData.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = DataTotalDRX[iC][iPT][i] / DataCountDR[iC][iPT][i];
            double DR = DataTotalDR[iC][iPT][i] / DRBinSize / DataGrandTotal[iC][iPT];
            double DRRMS = sqrt(DataTotalDR2[iC][iPT][i]) / DataGrandTotal[iC][iPT] / DRBinSize;

            GDRData.SetPoint(i, DRX, DR);
            GDRData.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }
         
         for(int i = 0; i < MASSBINCOUNT; i++)
         {
            double MassBinSize = MassBinEdge[i+1] - MassBinEdge[i];
            double MassX = SmearTotalMassX[iC][iPT][i] / SmearCountMass[iC][iPT][i];
            double Mass = SmearTotalMass[iC][iPT][i] / MassBinSize / SmearGrandTotal[iC][iPT];
            double MassRMS = sqrt(SmearTotalMass2[iC][iPT][i]) / SmearGrandTotal[iC][iPT] / MassBinSize;
            double MassUp = SmearTotalMassUp[iC][iPT][i] / MassBinSize / SmearGrandTotal[iC][iPT];
            double MassDown = SmearTotalMassDown[iC][iPT][i] / MassBinSize / SmearGrandTotal[iC][iPT];

            GMassSmear.SetPoint(i, MassX, Mass);
            GMassSmear.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, MassRMS, MassRMS);
            GMassSmearSys.SetPoint(i, MassX, Mass);
            GMassSmearSys.SetPointError(i, MassX - MassBinEdge[i], MassBinEdge[i+1] - MassX, Mass - MassDown, MassUp - Mass);
         }
         for(int i = 0; i < ZGBINCOUNT; i++)
         {
            double ZGBinSize = ZGBinEdge[i+1] - ZGBinEdge[i];
            double ZGX = SmearTotalZGX[iC][iPT][i] / SmearCountZG[iC][iPT][i];
            double ZG = SmearTotalZG[iC][iPT][i] / ZGBinSize / SmearGrandTotal[iC][iPT];
            double ZGRMS = sqrt(SmearTotalZG2[iC][iPT][i]) / SmearGrandTotal[iC][iPT] / ZGBinSize;

            GZGSmear.SetPoint(i, ZGX, ZG);
            GZGSmear.SetPointError(i, ZGX - ZGBinEdge[i], ZGBinEdge[i+1] - ZGX, ZGRMS, ZGRMS);
         }
         for(int i = 0; i < DRBINCOUNT; i++)
         {
            double DRBinSize = DRBinEdge[i+1] - DRBinEdge[i];
            double DRX = SmearTotalDRX[iC][iPT][i] / SmearCountDR[iC][iPT][i];
            double DR = SmearTotalDR[iC][iPT][i] / DRBinSize / SmearGrandTotal[iC][iPT];
            double DRRMS = sqrt(SmearTotalDR2[iC][iPT][i]) / SmearGrandTotal[iC][iPT] / DRBinSize;

            GDRSmear.SetPoint(i, DRX, DR);
            GDRSmear.SetPointError(i, DRX - DRBinEdge[i], DRBinEdge[i+1] - DRX, DRRMS, DRRMS);
         }

         GMassData.Write();
         GMassSmear.Write();
         GMassDataSys.Write();
         GMassSmearSys.Write();
         GZGData.Write();
         GZGSmear.Write();
         GDRData.Write();
         GDRSmear.Write();

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
   FData.Close();

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





