#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"
#include "ProgressBar.h"

#define BIN 20
#define SYSBIN 160
#define WEIGHTBIN 400
#define WEIGHTMIN -15
#define WEIGHTMAX 25

#define TypeNormal 0
#define TypePT 1
#define TypeEta 2
#define TypeJER 3
#define TypeSmear 4
#define TypeDR 5
#define TypeRho 6
#define TypeGhost 7
#define TypeMB 8
#define TypeRange 9
#define TypeRange2 10
#define TypeMass 11

#define TypeLinear -1
#define TypeQuadratic 1
#define TypeExponential 2

struct Box;
class TreeMessenger;
int main(int argc, char *argv[]);
pair<double, double> GetCentralFlatRMS(PdfFileHelper &PdfFile, vector<double> D, double Left, double Right);
vector<double> GetSystematics(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, double Left, double Right);
vector<pair<double, double>> QuadraticError(PdfFileHelper &PdfFile,
   vector<double> HN, vector<double> HM, vector<double> HN2, vector<double> HM2, int FunctionType);
double GetDR(double eta1, double phi1, double eta2, double phi2);
double GetBinCenter(int B);
double GetSysBinCenter(int B);
int FindBin(double X);
void Transcribe(vector<double> V, TGraphAsymmErrors *G);
void TranscribeQuadratic(vector<pair<double, double>> V, TGraphAsymmErrors *G);
void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, vector<double> N2, vector<double> M2, TGraphAsymmErrors *G);

struct Box
{
   double PTMin;
   double PTMax;
   double CentralityMin;
   double CentralityMax;
   Box(double ptmin, double ptmax, double centralitymin, double centralitymax)
      : PTMin(ptmin), PTMax(ptmax), CentralityMin(centralitymin), CentralityMax(centralitymax)
   {
   }
};

class TreeMessenger
{
public:
   TTree *Tree;
   double MCWeight;
   double Centrality;
   double JetPT;
   double JetEta;
   double JetPhi;
   double OriginalJetPT;
   double OriginalJetEta;
   double OriginalJetPhi;
   double SDMass;
   double SDZG;
   double SDDR;
   double ExcessPT;
   double TotalPTInJet;
   double Rho;
   double MatchedDR;
   double Weight;
   int Type;
   bool IsNominal;
public:
   TreeMessenger(TTree *T, int SD = 0, int type = TypeNormal, bool isnominal = true)
   {
      Tree = T;

      if(Tree == NULL)
         return;

      Type = type;
      IsNominal = isnominal;

      Tree->SetBranchAddress("MCWeight",     &MCWeight);
      Tree->SetBranchAddress("Centrality",   &Centrality);
      Tree->SetBranchAddress("NewJetPT",     &JetPT);
      Tree->SetBranchAddress("NewJetEta",    &JetEta);
      Tree->SetBranchAddress("NewJetPhi",    &JetPhi);
      Tree->SetBranchAddress("JetPT",        &OriginalJetPT);
      Tree->SetBranchAddress("JetEta",       &OriginalJetEta);
      Tree->SetBranchAddress("JetPhi",       &OriginalJetPhi);
      Tree->SetBranchAddress("TotalPTInJet", &TotalPTInJet);
      Tree->SetBranchAddress("Rho",          &Rho);

      if(SD == 0)
      {
         Tree->SetBranchAddress("NewJetSDMass", &SDMass);
         Tree->SetBranchAddress("NewJetZG",     &SDZG);
         Tree->SetBranchAddress("NewJetDR",     &SDDR);
      }
      else
      {
         Tree->SetBranchAddress("NewJetSDMass2", &SDMass);
         Tree->SetBranchAddress("NewJetZG2",     &SDZG);
         Tree->SetBranchAddress("NewJetDR2",     &SDDR);
      }
   }
   void GetEntry(int IEntry)
   {
      if(Tree == NULL)
         return;

      Tree->GetEntry(IEntry);

      MatchedDR = GetDR(JetEta, JetPhi, OriginalJetEta, OriginalJetPhi);

      double X = Centrality / 100;
      // double RMST = 19.15 - 23.28 * X + 4.567e-7 * X * X - 467.4 * X * X * X + 2110 * X * X * X * X
      //    - 2993 * X * X * X * X * X + 227.9 * X * X * X * X * X * X + 2019 * X * X * X * X * X * X * X
      //    + 876.3 * X * X * X * X * X * X * X * X - 3027 * X * X * X * X * X * X * X * X * X
      //    + 1239 * X * X * X * X * X * X * X * X * X * X;
      
      double RMST = exp(1.14611 - 27.2452 * X) + exp(3.27512 - 3.59286 * X);   // 1
      
      double RMS = exp(1.14611 - 27.2452 * X) + exp(3.27512 - 3.59286 * X);   // 1
      if(Type == TypeRho && IsNominal == false)   // 9
         RMS = exp(1.10327 - 25.3083 * X) + exp(3.27481 - 3.50281 * X);
      else if(Type == TypeGhost && IsNominal == false)   // 15
         RMS = exp(1.14485 - 27.1929 * X) + exp(3.27483 - 3.59216 * X);
      else if(Type == TypeMB && IsNominal == false)   // 21 & 22
         RMS = exp(1.07477 - 28.1021 * X) + exp(3.28557 - 3.59269 * X);
      else if(Type == TypeRange && IsNominal == false)   // 13
         RMS = exp(1.25321 - 27.3256 * X) + exp(3.3154 - 3.53261 * X);
      else if(Type == TypeRange2 && IsNominal == true)   // 13
         RMS = exp(1.25321 - 27.3256 * X) + exp(3.3154 - 3.53261 * X);
      else if(Type == TypeRange2 && IsNominal == false)   // 17
         RMS = exp(1.28384 - 29.506 * X) + exp(3.34358 - 3.537 * X);

      if(Type == TypeSmear && IsNominal == false)
         RMST = RMST * 0.95;

      ExcessPT = TotalPTInJet - 0.4 * 0.4 * PI * Rho;
      Weight = MCWeight * exp(-ExcessPT * ExcessPT / (2 * RMST * RMST)) / exp(-ExcessPT * ExcessPT / (2 * RMS * RMS));

      if(Type == TypeEta)
      {
         if(IsNominal == true && fabs(JetEta) < 0.5)
            Weight = Weight * 2;
         if(IsNominal == false && fabs(JetEta) > 0.5)
            Weight = Weight * 2;
      }

      if(Type == TypeJER && IsNominal == false)
      {
         double Factor = DrawGaussian(1, 0.05);
         JetPT = JetPT * Factor;
         SDMass = SDMass * Factor;
      }
      
      if(Type == TypeMass)
      {
         if(IsNominal == true)   SDMass = SDMass * (1.01 - 0.075 * SDDR);
         else                    SDMass = SDMass * (1.01 - 0.075 * SDDR) / 1.005;
      }
   }
   bool InBox(Box B)
   {
      double Factor = 1;
      if(IsNominal == false && Type == TypePT)
         Factor = 0.95;

      if(JetPT * Factor < B.PTMin)
         return false;
      if(JetPT * Factor >= B.PTMax)
         return false;
      if(Centrality / 100 < B.CentralityMin)
         return false;
      if(Centrality / 100 >= B.CentralityMax)
         return false;

      return true;
   }
   bool Baseline()
   {
      if(SDDR < 0.0)
         return false;
      if(SDDR > 1.0)
         return false;
      if(SDZG < 0.0)
         return false;
      if(JetEta < -1.3 || JetEta > 1.3)
         return false;
      if(MatchedDR > 0.1)
         return false;

      return true;
   }
   bool DRCut()
   {
      if(Type == TypeDR)
      {
         if(IsNominal == true && SDDR < 0.095)
            return false;
         if(IsNominal == false && SDDR < 0.105)
            return false;

         return true;
      }

      if(SDDR < 0.1)
         return false;

      return true;
   }
};

int main(int argc, char *argv[])
{
   if(argc != 8)
   {
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile SD Type Tag FunctionType Right" << endl;
      return -1;
   }

   char *BaseFile = argv[1];
   char *ModifiedFile = argv[2];
   int SD = ((argv[3][0] == '0') ? 0 : 7);
   string StringType = argv[4];
   string Tag = argv[5];
   string StringFunctionType = argv[6];
   double Right = atof(argv[7]);

   int Type = TypeNormal;
   if(StringType == "PT")
      Type = TypePT;
   if(StringType == "Eta")
      Type = TypeEta;
   if(StringType == "JER")
      Type = TypeJER;
   if(StringType == "Smear")
      Type = TypeSmear;
   if(StringType == "DR")
      Type = TypeDR;
   if(StringType == "Rho")
      Type = TypeRho;
   if(StringType == "Ghost")
      Type = TypeGhost;
   if(StringType == "MB")
      Type = TypeMB;
   if(StringType == "Range")
      Type = TypeRange;
   if(StringType == "Range2")
      Type = TypeRange2;
   if(StringType == "Mass")
      Type = TypeMass;

   int FunctionType = TypeQuadratic;
   if(StringFunctionType == "Quadratic")
      FunctionType = TypeQuadratic;
   if(StringFunctionType == "Linear")
      FunctionType = TypeLinear;
   if(StringFunctionType == "Exponential")
      FunctionType = TypeExponential;

   Tag = Form("%s_%d", Tag.c_str(), SD);

   SetThesisStyle();

   PdfFileHelper PdfFile(string("Systematics_") + Tag + ".pdf");
   PdfFile.AddTextPage("Systematics");

   TFile F1(BaseFile);
   TFile F2(ModifiedFile);

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   TreeMessenger M1(T1, SD, Type, true);
   TreeMessenger M2(T2, SD, Type, false);

   TFile OutputFile((string("OutputFile_") + Tag + ".root").c_str(), "RECREATE");

   vector<Box> Cuts;
   vector<string> Labels;

   Cuts.push_back(Box(120, 140, 0.0, 0.1));   Labels.push_back("GRatio_C0_P0");
   Cuts.push_back(Box(140, 160, 0.0, 0.1));   Labels.push_back("GRatio_C0_P1");
   Cuts.push_back(Box(160, 180, 0.0, 0.1));   Labels.push_back("GRatio_C0_P2");
   Cuts.push_back(Box(180, 200, 0.0, 0.1));   Labels.push_back("GRatio_C0_P3");
   Cuts.push_back(Box(200, 300, 0.0, 0.1));   Labels.push_back("GRatio_C0_P4");
   Cuts.push_back(Box(300, 500, 0.0, 0.1));   Labels.push_back("GRatio_C0_P5");
   Cuts.push_back(Box(120, 140, 0.1, 0.3));   Labels.push_back("GRatio_C1_P0");
   Cuts.push_back(Box(140, 160, 0.1, 0.3));   Labels.push_back("GRatio_C1_P1");
   Cuts.push_back(Box(160, 180, 0.1, 0.3));   Labels.push_back("GRatio_C1_P2");
   Cuts.push_back(Box(180, 200, 0.1, 0.3));   Labels.push_back("GRatio_C1_P3");
   Cuts.push_back(Box(200, 300, 0.1, 0.3));   Labels.push_back("GRatio_C1_P4");
   Cuts.push_back(Box(300, 500, 0.1, 0.3));   Labels.push_back("GRatio_C1_P5");
   Cuts.push_back(Box(120, 140, 0.3, 0.5));   Labels.push_back("GRatio_C2_P0");
   Cuts.push_back(Box(140, 160, 0.3, 0.5));   Labels.push_back("GRatio_C2_P1");
   Cuts.push_back(Box(160, 180, 0.3, 0.5));   Labels.push_back("GRatio_C2_P2");
   Cuts.push_back(Box(180, 200, 0.3, 0.5));   Labels.push_back("GRatio_C2_P3");
   Cuts.push_back(Box(200, 300, 0.3, 0.5));   Labels.push_back("GRatio_C2_P4");
   Cuts.push_back(Box(300, 500, 0.3, 0.5));   Labels.push_back("GRatio_C2_P5");
   Cuts.push_back(Box(120, 140, 0.5, 0.8));   Labels.push_back("GRatio_C3_P0");
   Cuts.push_back(Box(140, 160, 0.5, 0.8));   Labels.push_back("GRatio_C3_P1");
   Cuts.push_back(Box(160, 180, 0.5, 0.8));   Labels.push_back("GRatio_C3_P2");
   Cuts.push_back(Box(180, 200, 0.5, 0.8));   Labels.push_back("GRatio_C3_P3");
   Cuts.push_back(Box(200, 300, 0.5, 0.8));   Labels.push_back("GRatio_C3_P4");
   Cuts.push_back(Box(300, 500, 0.5, 0.8));   Labels.push_back("GRatio_C3_P5");
   Cuts.push_back(Box(120, 140, 0.8, 1.0));   Labels.push_back("GRatio_C4_P0");
   Cuts.push_back(Box(140, 160, 0.8, 1.0));   Labels.push_back("GRatio_C4_P1");
   Cuts.push_back(Box(160, 180, 0.8, 1.0));   Labels.push_back("GRatio_C4_P2");
   Cuts.push_back(Box(180, 200, 0.8, 1.0));   Labels.push_back("GRatio_C4_P3");
   Cuts.push_back(Box(200, 300, 0.8, 1.0));   Labels.push_back("GRatio_C4_P4");
   Cuts.push_back(Box(300, 500, 0.8, 1.0));   Labels.push_back("GRatio_C4_P5");
   Cuts.push_back(Box(120, 140, 0.0, 0.8));   Labels.push_back("GRatio_CA_P0");
   Cuts.push_back(Box(140, 160, 0.0, 0.8));   Labels.push_back("GRatio_CA_P1");
   Cuts.push_back(Box(160, 180, 0.0, 0.8));   Labels.push_back("GRatio_CA_P2");
   Cuts.push_back(Box(180, 200, 0.0, 0.8));   Labels.push_back("GRatio_CA_P3");
   Cuts.push_back(Box(200, 300, 0.0, 0.8));   Labels.push_back("GRatio_CA_P4");
   Cuts.push_back(Box(300, 500, 0.0, 0.8));   Labels.push_back("GRatio_CA_P5");

   vector<vector<double>> HN(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HM(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HN2(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HM2(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HNW(Cuts.size(), vector<double>(WEIGHTBIN));
   vector<vector<double>> HMW(Cuts.size(), vector<double>(WEIGHTBIN));
   vector<double> HNInt(Cuts.size());
   vector<double> HMInt(Cuts.size());

   int EntryCount;

   EntryCount = T1->GetEntries();
   ProgressBar Bar1(cout, EntryCount);
   Bar1.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || (iE % (EntryCount / 250) == 0))
      {
         Bar1.Update(iE);
         Bar1.Print();
      }

      M1.GetEntry(iE);
      if(M1.Baseline() == false)
         continue;

      int iWB = (log(M1.Weight) - WEIGHTMIN) / (WEIGHTMAX - WEIGHTMIN) * WEIGHTBIN;
      if(iWB < 0)            iWB = 0;
      if(iWB >= WEIGHTBIN)   iWB = WEIGHTBIN;

      int iB = FindBin(M1.SDMass / M1.JetPT);

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(M1.InBox(Cuts[iC]) == false)
            continue;

         if(M1.DRCut() == true)
         {
            HNW[iC][iWB] = HNW[iC][iWB] + 1;
            if(log(M1.Weight) < 8.5)   // remove events with huge weight
            {
               HNInt[iC] = HNInt[iC] + M1.Weight;
               HN[iC][iB] = HN[iC][iB] + M1.Weight;
               HN2[iC][iB] = HN2[iC][iB] + M1.Weight * M1.Weight;
            }
         }
      }
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   EntryCount = T2->GetEntries();
   ProgressBar Bar2(cout, EntryCount);
   Bar2.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || (iE % (EntryCount / 250) == 0))
      {
         Bar2.Update(iE);
         Bar2.Print();
      }

      M2.GetEntry(iE);
      if(M2.Baseline() == false)
         continue;

      int iWB = (log(M2.Weight) - WEIGHTMIN) / (WEIGHTMAX - WEIGHTMIN) * WEIGHTBIN;
      if(iWB < 0)            iWB = 0;
      if(iWB >= WEIGHTBIN)   iWB = WEIGHTBIN;
      
      int iB = FindBin(M2.SDMass / M2.JetPT);

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(M2.InBox(Cuts[iC]) == false)
            continue;

         if(M2.DRCut() == true)
         {
            HMW[iC][iWB] = HMW[iC][iWB] + 1;
            if(log(M2.Weight) < 8.5)   // remove events with huge weight
            {
               HMInt[iC] = HMInt[iC] + M2.Weight;
               HM[iC][iB] = HM[iC][iB] + M2.Weight;
               HM2[iC][iB] = HM2[iC][iB] + M2.Weight * M2.Weight;
            }
         }
      }
   }
   Bar2.Update(EntryCount);
   Bar2.Print();
   Bar2.PrintLine();

   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      for(int iB = 0; iB < BIN; iB++)
         HN[iC][iB] = HN[iC][iB] / HNInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HN2[iC][iB] = HN2[iC][iB] / HNInt[iC] / HNInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HM[iC][iB] = HM[iC][iB] / HMInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HM2[iC][iB] = HM2[iC][iB] / HMInt[iC] / HNInt[iC];
   }

   vector<TGraphAsymmErrors *> GRatio(Cuts.size());
   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      GRatio[iC] = new TGraphAsymmErrors;
      GRatio[iC]->SetNameTitle(Labels[iC].c_str(),
         Form("PT %.0f-%.0f, Centrality %.2f-%.2f",
            Cuts[iC].PTMin, Cuts[iC].PTMax,
            Cuts[iC].CentralityMin, Cuts[iC].CentralityMax));
   }

   // vector<vector<double, double>> Error(Cuts.size());
   vector<vector<pair<double, double>>> Error(Cuts.size());
   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      PdfFile.AddTextPage(Labels[iC]);
      
      // Error[iC] = GetSystematics(PdfFile, HN[iC], HM[iC], Left, Right);
      Error[iC] = QuadraticError(PdfFile, HN[iC], HM[iC], HN2[iC], HM2[iC], FunctionType);

      // Transcribe(Error[iC], GRatio[iC]);
      TranscribeQuadratic(Error[iC], GRatio[iC]);

      AddPlot(PdfFile, HN[iC], HM[iC], HN2[iC], HM2[iC], GRatio[iC]);
      // PdfFile.AddPlot(GRatio[iC], "apl");

      TH1D HistNW("HistNW", "Nominal weight distribution;log(W);Count", WEIGHTBIN, WEIGHTMIN, WEIGHTMAX);
      HistNW.SetStats(0);
      for(int i = 1; i <= WEIGHTBIN; i++)
         HistNW.SetBinContent(i, HNW[iC][i-1]);
      PdfFile.AddPlot(HistNW, "", true);

      TH1D HistMW("HistMW", "Nominal weight distribution;log(W);Count", WEIGHTBIN, WEIGHTMIN, WEIGHTMAX);
      HistMW.SetStats(0);
      for(int i = 1; i <= WEIGHTBIN; i++)
         HistMW.SetBinContent(i, HMW[iC][i-1]);
      PdfFile.AddPlot(HistMW, "", true);
   }

   for(int iC = 0; iC < (int)Cuts.size(); iC++)
      GRatio[iC]->Write();

   OutputFile.Close();

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

pair<double, double> GetCentralFlatRMS(PdfFileHelper &PdfFile, vector<double> D, double Left, double Right)
{
   double Percentage = 0.65;

   int LeftBin = FindBin(Left);
   int RightBin = FindBin(Right);
   
   vector<double> V;
   for(int i = LeftBin; i <= RightBin; i++)
      V.push_back(fabs(D[i]));
   sort(V.begin(), V.end());

   int N = V.size() * Percentage + 1;
   if(N >= V.size())
      N = V.size() - 1;

   return pair<double, double>(V[N], -V[N]);
}

vector<double> GetSystematics(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, double Left, double Right)
{
   vector<double> D;
   for(int i = 0; i < (int)N.size(); i++)
   {
      // Ratio error
      if(N[i] > 0 && M[i] > 0)
         D.push_back(log(N[i]) - log(M[i]));
      else
         D.push_back(0);
      
      // Linear error
      // D.push_back(N[i] - M[i]);
   }

   vector<double> E(N.size());
   
   int LeftBin = FindBin(Left);
   int RightBin = FindBin(Right);

   pair<double, double> Flat = GetCentralFlatRMS(PdfFile, D, Left, Right);

   for(int i = LeftBin; i <= RightBin; i++)
      E[i] = Flat.first;

   for(int i = LeftBin - 1; i >= 0; i--)
   {
      if(fabs(D[i]) > E[i+1])
         E[i] = fabs(D[i]);
      else
         E[i] = E[i+1];
   }
   for(int i = RightBin + 1; i < (int)N.size(); i++)
   {
      if(fabs(D[i]) > E[i-1])
         E[i] = fabs(D[i]);
      else
         E[i] = E[i-1];
   }

   return E;
}

double GetDR(double eta1, double phi1, double eta2, double phi2)
{
   double deta = eta1 - eta2;
   double dphi = phi1 - phi2;
   while(dphi < -PI)
      dphi = dphi + PI;
   while(dphi > +PI)
      dphi = dphi - PI;

   return sqrt(deta * deta + dphi * dphi);
}

double GetBinCenter(int B)
{
   return 0.0 + (0.4 - 0.0) / BIN * (B + 0.5);
}

double GetSysBinCenter(int B)
{
   return 0.0 + (0.4 - 0.0) / SYSBIN * (B + 0.5);
}

int FindBin(double X)
{
   return (int)((X - 0.0) / (0.4 - 0.0) * BIN);
}

void Transcribe(vector<double> V, TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   for(int i = 0; i < SYSBIN; i++)
   {
      double X = GetSysBinCenter(i);
      int Bin = FindBin(X);

      G->SetPoint(i, X, 0);
      G->SetPointError(i, 0, 0, V[Bin], V[Bin]);
   }
}

void TranscribeQuadratic(vector<pair<double, double>> V, TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   for(int i = 0; i < SYSBIN; i++)
   {
      double X = GetSysBinCenter(i);
      int Bin = i;

      double Mean = (V[Bin].first + V[Bin].second) / 2;

      G->SetPoint(i, X, Mean);
      G->SetPointError(i, 0, 0, Mean - V[Bin].first, V[Bin].second - Mean);
   }
}

vector<pair<double, double>> QuadraticError(PdfFileHelper &PdfFile,
   vector<double> HN, vector<double> HM, vector<double> HN2, vector<double> HM2, int FunctionType)
{
   vector<double> D, DE;
   for(int i = 0; i < (int)HN.size(); i++)
   {
      // Ratio
      if(HN[i] > 0 && HM[i] > 0)
         D.push_back(log(HN[i]) - log(HM[i]));
      else
         D.push_back(0);
      
      if(HN[i] > 0 && HM[i] > 0)
         DE.push_back(sqrt(HN2[i] / HN[i] / HN[i] + HM2[i] / HM[i] / HM[i]));
      else
         DE.push_back(20);

      // Linear
      // D.push_back(N[i] - M[i]);
      // DE.push_back(sqrt(N2[i] + M2[i]));
   }

   for(int i = 0; i < (int)HN.size(); i++)
   {
      if(fabs(D[i]) > log(3))
      {
         D[i] = 0;
         DE[i] = 20;
      }
   }

   TH1D H("H", "", BIN, 0.0, 0.4);
   H.SetStats(0);

   for(int i = 0; i < (int)HN.size(); i++)
   {
      H.SetBinContent(i + 1, D[i]);
      H.SetBinError(i + 1, DE[i]);
   }

   PdfFile.AddPlot(H);

   string FunctionString = "pol2";
   if(FunctionType == TypeLinear)
      FunctionString = "pol1";
   if(FunctionType == TypeQuadratic)
      FunctionString = "pol2";
   if(FunctionType == TypeExponential)
      FunctionString = "[0]+[1]*exp(-[2]*x)";

   int ParameterCount = 3;
   if(FunctionType == TypeLinear)        ParameterCount = 2;
   if(FunctionType == TypeQuadratic)     ParameterCount = 3;
   if(FunctionType == TypeExponential)   ParameterCount = 3;

   TF1 Function("Function", FunctionString.c_str(), 0.0, 0.4);

   if(FunctionType == TypeExponential)
   {
      Function.SetParameter(0, H.GetBinContent(H.FindBin(0.20)));
      Function.SetParameter(1, 10);
      Function.SetParameter(2, 80);
   }

   TFitResultPtr FitResult = H.Fit(&Function, "S");
   TMatrixDSym Matrix = FitResult->GetCovarianceMatrix();

   H.GetFunction("Function")->SetBit(TF1::kNotDraw);

   // cout << "Covariance matrix: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << Matrix[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   double L[3][3] = {{0}};   // Cholesky decomposition:  find L such that L x L^T = M, where L is lower triangle

   if(ParameterCount >= 1)
      L[0][0] = sqrt(Matrix[0][0]);
   if(ParameterCount >= 2)
   {
      L[1][0] = Matrix[1][0] / L[0][0];
      L[1][1] = sqrt(Matrix[1][1] - L[1][0] * L[1][0]);
   }
   if(ParameterCount >= 3)
   {
      L[2][0] = Matrix[2][0] / L[0][0];
      L[2][1] = (Matrix[2][1] - L[2][0] * L[1][0]) / L[1][1];
      L[2][2] = sqrt(Matrix[2][2] - L[2][0] * L[2][0] - L[2][1] * L[2][1]);
   }

   // double LLT[3][3] = {{0}};   // Sanity check

   // for(int i = 0; i < 3; i++)
   //    for(int j = 0; j < 3; j++)
   //       LLT[i][j] = L[i][0] * L[j][0] + L[i][1] * L[j][1] + L[i][2] * L[j][2];
   
   // cout << "L: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << L[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   // cout << "L x LT: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << LLT[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   double Mean[3] = {0};
   if(ParameterCount >= 1)   Mean[0] = Function.GetParameter(0);
   if(ParameterCount >= 2)   Mean[1] = Function.GetParameter(1);
   if(ParameterCount >= 3)   Mean[2] = Function.GetParameter(2);

   vector<vector<double>> BinResults(160);
   TH2D HSpread("HSpread", ";Mass / PT;log(Ratio)", SYSBIN, 0.0, 0.4, 500, -1, 1);
   HSpread.SetStats(0);

   int Trials = 10000;
   for(int i = 0; i < Trials; i++)
   {
      double X[3] = {DrawGaussian(0, 1), DrawGaussian(0, 1), DrawGaussian(0, 1)};

      if(ParameterCount == 1)   X[2] = 0, X[1] = 0;
      if(ParameterCount == 2)   X[2] = 0;

      double Y[3] = {0};

      Y[0] = L[0][0] * X[0] + L[0][1] * X[1] + L[0][2] * X[2] + Mean[0];
      Y[1] = L[1][0] * X[0] + L[1][1] * X[1] + L[1][2] * X[2] + Mean[1];
      Y[2] = L[2][0] * X[0] + L[2][1] * X[1] + L[2][2] * X[2] + Mean[2];

      for(int iS = 0; iS < SYSBIN; iS++)
      {
         double x = GetSysBinCenter(iS);

         double v;
         if(FunctionType == TypeQuadratic)
            v = Y[0] + Y[1] * x + Y[2] * x * x;
         if(FunctionType == TypeLinear)
            v = Y[0] + Y[1] * x;
         if(FunctionType == TypeExponential)
            v = Y[0] + Y[1] * exp(-Y[2] * x);

         BinResults[iS].push_back(fabs(v));

         HSpread.Fill(x, v);
      }
   }

   TCanvas C;

   HSpread.Draw("colz");
   H.Draw("same");

   PdfFile.AddCanvas(C);

   vector<pair<double, double>> Result(160);

   for(int iS = 0; iS < SYSBIN; iS++)
   {
      sort(BinResults[iS].begin(), BinResults[iS].end());

      double P = 0.68;
      int Size = BinResults[iS].size();

      // int Min = (0.5 - P / 2) * Size;
      // int Max = (0.5 + P / 2) * Size;

      // Result[iS] = pair<double, double>(BinResults[iS][Min], BinResults[iS][Max]);

      int Location = Size * P;
      Result[iS] = pair<double, double>(-BinResults[iS][Location], BinResults[iS][Location]);
   }

   if(FunctionType == TypeExponential)   // fill in the artificial gap from exponential
   {
      for(int iS = SYSBIN - 1; iS > 0; iS--)
         if(Result[iS].second > Result[iS-1].second)
            Result[iS-1] = Result[iS];
   }

   return Result;
}

void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, vector<double> N2, vector<double> M2, TGraphAsymmErrors *G)
{
   TH1D HN("HN", "", BIN, 0.0, 0.4);
   TH1D HM("HM", "", BIN, 0.0, 0.4);
   TH1D HD("HD", "", BIN, 0.0, 0.4);

   for(int i = 0; i < BIN && i < (int)N.size() && i < (int)M.size(); i++)
   {
      HN.SetBinContent(i + 1, N[i]);
      HM.SetBinContent(i + 1, M[i]);
      HN.SetBinError(i + 1, sqrt(N2[i]));
      HM.SetBinError(i + 1, sqrt(M2[i]));
      if(N[i] > 0 && M[i] > 0)
      {
         HD.SetBinContent(i + 1, log(N[i]) - log(M[i]));
         HD.SetBinError(i + 1, sqrt(N2[i] / N[i] / N[i] + M2[i] / M[i] / M[i]));
      }
   }

   HN.SetStats(0);

   HN.SetLineColor(kBlue);
   HM.SetLineColor(kRed);
   HN.SetMarkerColor(kBlue);
   HM.SetMarkerColor(kRed);

   G->SetMarkerStyle(0);

   TCanvas C;

   HN.Draw("hist error");
   HM.Draw("hist error same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HN, "Nominal", "l");
   Legend.AddEntry(&HM, "Modified", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   TGraph GLine;
   GLine.SetPoint(0, 0, 0);
   GLine.SetPoint(1, 10000, 0);

   HD.SetStats(0);
   HD.Draw();
   GLine.Draw("l");

   PdfFile.AddCanvas(C);

   TH2D HWorld("HWorld", ";SD Mass / Jet PT;log(Ratio)", 100, 0, 0.4, 100, -0.5, 0.5);
   HWorld.SetStats(0);

   HWorld.Draw();
   G->Draw("");
   HD.Draw("same");

   PdfFile.AddCanvas(C);
}





