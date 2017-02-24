#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"
#include "ProgressBar.h"

#define BIN 20
#define SYSBIN 160

#define TypeNormal 0
#define TypePT 1
#define TypeEta 2
#define TypeJER 3
#define TypeSmear 4
#define TypeDR 5
#define TypeRho 6
#define TypeGhost 7

struct Box;
class TreeMessenger;
int main(int argc, char *argv[]);
pair<double, double> GetCentralFlatRMS(PdfFileHelper &PdfFile, vector<double> D, double Left, double Right);
vector<double> GetSystematics(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, double Left, double Right);
double GetDR(double eta1, double phi1, double eta2, double phi2);
double GetBinCenter(int B);
double GetSysBinCenter(int B);
int FindBin(double X);
void Transcribe(vector<double> V, TGraphAsymmErrors *G);
void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M);

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
      double RMST = 19.15 - 23.28 * X + 4.567e-7 * X * X - 467.4 * X * X * X + 2110 * X * X * X * X
         - 2993 * X * X * X * X * X + 227.9 * X * X * X * X * X * X + 2019 * X * X * X * X * X * X * X
         + 876.3 * X * X * X * X * X * X * X * X - 3027 * X * X * X * X * X * X * X * X * X
         + 1239 * X * X * X * X * X * X * X * X * X * X;
      double RMS = exp(1.25391 - 27.2957 * X) + exp(3.31530 - 3.53222 * X);
      if(Type == TypeRho && IsNominal == false)
         RMS = exp(1.31499 - 21.0415 * X) + exp(3.28132 - 3.5001 * X);
      else if(Type == TypeGhost && IsNominal == false)
         RMS = exp(1.15381 - 23.3627 * X) + exp(3.28807 - 3.61712 * X);
      else
         RMS = exp(1.39331 - 24.9821 * X) + exp(3.33588 - 3.5139 * X);

      if(Type == TypeSmear && IsNominal == false)
         RMS = RMS * 0.9;

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
         JetPT = JetPT * DrawGaussian(1, 0.1);
   }
   bool InBox(Box B)
   {
      double Factor = 1;
      if(IsNominal == false && Type == TypePT)
         Factor = 0.9;

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
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile SD Type Tag Left Right" << endl;
      return -1;
   }

   char *BaseFile = argv[1];
   char *ModifiedFile = argv[2];
   int SD = ((argv[3][0] == '0') ? 0 : 7);
   string StringType = argv[4];
   string Tag = argv[5];
   double Left = atof(argv[6]);
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

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(M1.InBox(Cuts[iC]) == false)
            continue;

         int iB = FindBin(M1.SDMass / M1.JetPT);

         HNInt[iC] = HNInt[iC] + M1.Weight;
         if(M1.DRCut() == true)
            HN[iC][iB] = HN[iC][iB] + M1.Weight;
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

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(M2.InBox(Cuts[iC]) == false)
            continue;

         int iB = FindBin(M2.SDMass / M2.JetPT);

         HMInt[iC] = HMInt[iC] + M2.Weight;
         if(M2.DRCut() == true)
            HM[iC][iB] = HM[iC][iB] + M2.Weight;
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
         HM[iC][iB] = HM[iC][iB] / HMInt[iC];
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

   vector<vector<double>> Error(Cuts.size());
   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      Error[iC] = GetSystematics(PdfFile, HN[iC], HM[iC], Left, Right);

      Transcribe(Error[iC], GRatio[iC]);

      PdfFile.AddTextPage(Labels[iC]);
      AddPlot(PdfFile, HN[iC], HM[iC]);
      PdfFile.AddPlot(GRatio[iC], "apl");
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

void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M)
{
   TH1D HN("HN", "", BIN, 0.0, 0.4);
   TH1D HM("HM", "", BIN, 0.0, 0.4);
   TH1D HD("HD", "", BIN, 0.0, 0.4);

   for(int i = 0; i < BIN && i < (int)N.size() && i < (int)M.size(); i++)
   {
      HN.SetBinContent(i + 1, N[i]);
      HM.SetBinContent(i + 1, M[i]);
      if(N[i] > 0 && M[i] > 0)
         HD.SetBinContent(i + 1, log(N[i]) - log(M[i]));
   }

   HN.SetStats(0);

   HN.SetLineColor(kBlue);
   HM.SetLineColor(kRed);

   TCanvas C;

   HN.Draw();
   HM.Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HN, "Nominal", "l");
   Legend.AddEntry(&HM, "Modified", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   HD.SetStats(0);
   HD.Draw();

   PdfFile.AddCanvas(C);
}





