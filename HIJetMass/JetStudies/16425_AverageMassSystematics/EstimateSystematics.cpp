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

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"
#include "DataHelper.h"
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
#define TypeQuarkGluon 12

struct Box;
class TreeMessenger;
int main(int argc, char *argv[]);
double GetDR(double eta1, double phi1, double eta2, double phi2);

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
   double SDPT1, SDPT2;
   double SDDR;
   double ExcessPT;
   double TotalPTInJet;
   double Rho;
   double MatchedDR;
   double Weight;
   int FlavorB;
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

      if(Type == TypeQuarkGluon)
      {
         Tree->SetBranchAddress("MCWeight",     &MCWeight);
         Tree->SetBranchAddress("Centrality",   &Centrality);
         Tree->SetBranchAddress("MatchPT",      &JetPT);
         Tree->SetBranchAddress("JetEta",       &JetEta);
         Tree->SetBranchAddress("JetPhi",       &JetPhi);
         Tree->SetBranchAddress("MatchDR",      &MatchedDR);
         Tree->SetBranchAddress("FlavorB",      &FlavorB);

         if(SD == 0)
         {
            Tree->SetBranchAddress("SDMass0",    &SDMass);
            Tree->SetBranchAddress("SubJet1PT0", &SDPT1);
            Tree->SetBranchAddress("SubJet2PT0", &SDPT2);
            Tree->SetBranchAddress("SubJetDR0",  &SDDR);
         }
         else
         {
            Tree->SetBranchAddress("SDMass7",    &SDMass);
            Tree->SetBranchAddress("SubJet1PT7", &SDPT1);
            Tree->SetBranchAddress("SubJet2PT7", &SDPT2);
            Tree->SetBranchAddress("SubJetDR7",  &SDDR);
         }
      }
      else
      {
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
   }
   void GetEntry(int IEntry)
   {
      if(Tree == NULL)
         return;

      Tree->GetEntry(IEntry);

      if(Type != TypeQuarkGluon)
         MatchedDR = GetDR(JetEta, JetPhi, OriginalJetEta, OriginalJetPhi);
      if(Type == TypeQuarkGluon)
         Centrality = Centrality * 100;

      double X = Centrality / 100;
      double RMST = 19.15 - 23.28 * X + 4.567e-7 * X * X - 467.4 * X * X * X + 2110 * X * X * X * X
         - 2993 * X * X * X * X * X + 227.9 * X * X * X * X * X * X + 2019 * X * X * X * X * X * X * X
         + 876.3 * X * X * X * X * X * X * X * X - 3027 * X * X * X * X * X * X * X * X * X
         + 1239 * X * X * X * X * X * X * X * X * X * X;
      
      double RMS = exp(1.14611 - 27.2452 * X) + exp(3.27512 - 3.59286 * X);   // 1
      if(Type == TypeRho && IsNominal == false)   // 9
         RMS = exp(1.14863 - 23.8947 * X) + exp(3.26913 - 3.48024 * X);
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
         RMS = RMS * 0.9;

      ExcessPT = TotalPTInJet - 0.4 * 0.4 * PI * Rho;
      if(Type != TypeQuarkGluon)
         Weight = MCWeight * exp(-ExcessPT * ExcessPT / (2 * RMST * RMST)) / exp(-ExcessPT * ExcessPT / (2 * RMS * RMS));
      else
         Weight = MCWeight;

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

      if(Type == TypeQuarkGluon)
         SDZG = max(SDPT1, SDPT2) / (SDPT1 + SDPT2);
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

      if(Type == TypeQuarkGluon)
      {
         if(IsNominal == true && IsLight() == false)
            return false;
         if(IsNominal == false && IsGluon() == false)
            return false;
      }
      
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
   bool IsLight()
   {
      if(FlavorB != 1 && FlavorB != -1 && FlavorB != 2 && FlavorB != -2)
         return false;
      return true;
   }
   bool IsGluon()
   {
      if(FlavorB != 21)
         return false;
      return true;
   }
};

int main(int argc, char *argv[])
{
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile SD Type Tag" << endl;
      return -1;
   }

   DataHelper DHFile("Systematics.dh");

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
   if(StringType == "MB")
      Type = TypeMB;
   if(StringType == "Range")
      Type = TypeRange;
   if(StringType == "Range2")
      Type = TypeRange2;
   if(StringType == "Mass")
      Type = TypeMass;
   if(StringType == "QuarkGluon")
      Type = TypeQuarkGluon;

   Tag = Form("%s_%d", Tag.c_str(), SD);

   SetThesisStyle();

   string Name = "OutputTree";
   if(Type == TypeQuarkGluon)
      Name = "T";

   TFile F1(BaseFile);
   TFile F2(ModifiedFile);

   TTree *T1 = (TTree *)F1.Get(Name.c_str());
   TTree *T2 = (TTree *)F2.Get(Name.c_str());

   TreeMessenger M1(T1, SD, Type, true);
   TreeMessenger M2(T2, SD, Type, false);

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

   vector<double> NM0(Cuts.size());
   vector<double> NM1(Cuts.size());
   vector<double> NM2(Cuts.size());
   vector<double> NM3(Cuts.size());
   vector<double> NM4(Cuts.size());
   vector<double> NM5(Cuts.size());
   
   vector<double> MM0(Cuts.size());
   vector<double> MM1(Cuts.size());
   vector<double> MM2(Cuts.size());
   vector<double> MM3(Cuts.size());
   vector<double> MM4(Cuts.size());
   vector<double> MM5(Cuts.size());

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

         double SDMassRatio = M1.SDMass / M1.JetPT;

         if(M1.DRCut() == true && log(M1.Weight) < 8.5)
         {
            NM0[iC] = NM0[iC] + 1 * M1.Weight;
            NM1[iC] = NM1[iC] + SDMassRatio * M1.Weight;
            NM2[iC] = NM2[iC] + SDMassRatio * SDMassRatio * M1.Weight;
            NM3[iC] = NM3[iC] + SDMassRatio * SDMassRatio * SDMassRatio * M1.Weight;
            NM4[iC] = NM4[iC] + SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * M1.Weight;
            NM5[iC] = NM5[iC] + SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * M1.Weight;
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

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(M2.InBox(Cuts[iC]) == false)
            continue;

         double SDMassRatio = M2.SDMass / M2.JetPT;

         if(M2.DRCut() == true && log(M2.Weight) < 8.5)
         {
            MM0[iC] = MM0[iC] + 1 * M2.Weight;
            MM1[iC] = MM1[iC] + SDMassRatio * M2.Weight;
            MM2[iC] = MM2[iC] + SDMassRatio * SDMassRatio * M2.Weight;
            MM3[iC] = MM3[iC] + SDMassRatio * SDMassRatio * SDMassRatio * M2.Weight;
            MM4[iC] = MM4[iC] + SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * M2.Weight;
            MM5[iC] = MM5[iC] + SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * SDMassRatio * M2.Weight;
         }
      }
   }
   Bar2.Update(EntryCount);
   Bar2.Print();
   Bar2.PrintLine();

   vector<double> NMean(Cuts.size());
   vector<double> MMean(Cuts.size());
   vector<double> NVariance(Cuts.size());
   vector<double> MVariance(Cuts.size());
   vector<double> NMoment3(Cuts.size());
   vector<double> MMoment3(Cuts.size());
   vector<double> NMoment4(Cuts.size());
   vector<double> MMoment4(Cuts.size());
   vector<double> NMoment5(Cuts.size());
   vector<double> MMoment5(Cuts.size());

   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      NMean[iC] = NM1[iC] / NM0[iC];
      MMean[iC] = MM1[iC] / MM0[iC];

      NVariance[iC] = (NM2[iC] - NM0[iC] * NMean[iC] * NMean[iC]) / NM0[iC];
      MVariance[iC] = (MM2[iC] - MM0[iC] * MMean[iC] * MMean[iC]) / MM0[iC];

      NMoment3[iC] = (NM3[iC] - 3 * NM2[iC] * NMean[iC] + 2 * NM0[iC] * NMean[iC] * NMean[iC] * NMean[iC]) / NM0[iC];
      MMoment3[iC] = (MM3[iC] - 3 * MM2[iC] * MMean[iC] + 2 * MM0[iC] * MMean[iC] * MMean[iC] * MMean[iC]) / MM0[iC];
      
      NMoment4[iC] = (NM4[iC] - 4 * NM3[iC] * NMean[iC] + 6 * NM2[iC] * NMean[iC] * NMean[iC] - 3 * NM0[iC] * NMean[iC] * NMean[iC] * NMean[iC] * NMean[iC]) / NM0[iC];
      MMoment4[iC] = (MM4[iC] - 4 * MM3[iC] * MMean[iC] + 6 * MM2[iC] * MMean[iC] * MMean[iC] - 3 * MM0[iC] * MMean[iC] * MMean[iC] * MMean[iC] * MMean[iC]) / MM0[iC];
      
      NMoment5[iC] = (NM5[iC] - 5 * NM4[iC] * NMean[iC] + 10 * NM3[iC] * NMean[iC] * NMean[iC] - 10 * NM2[iC] * NMean[iC] * NMean[iC] * NMean[iC] + 4 * NM0[iC] * NMean[iC] * NMean[iC] * NMean[iC] * NMean[iC] * NMean[iC]) / NM0[iC];
      MMoment5[iC] = (MM5[iC] - 5 * MM4[iC] * MMean[iC] + 10 * MM3[iC] * MMean[iC] * MMean[iC] - 10 * MM2[iC] * MMean[iC] * MMean[iC] * MMean[iC] + 4 * MM0[iC] * MMean[iC] * MMean[iC] * MMean[iC] * MMean[iC] * MMean[iC]) / MM0[iC];

      DHFile[Labels[iC]][Tag+"_Nominal"] = NMean[iC];
      DHFile[Labels[iC]][Tag+"_Modified"] = MMean[iC];
      
      DHFile[Labels[iC]][Tag+"_NominalVariance"] = NVariance[iC];
      DHFile[Labels[iC]][Tag+"_ModifiedVariance"] = MVariance[iC];
      
      DHFile[Labels[iC]][Tag+"_NominalMoment3"] = NMoment3[iC];
      DHFile[Labels[iC]][Tag+"_ModifiedMoment3"] = MMoment3[iC];
      
      DHFile[Labels[iC]][Tag+"_NominalMoment4"] = NMoment4[iC];
      DHFile[Labels[iC]][Tag+"_ModifiedMoment4"] = MMoment4[iC];
      
      DHFile[Labels[iC]][Tag+"_NominalMoment5"] = NMoment5[iC];
      DHFile[Labels[iC]][Tag+"_ModifiedMoment5"] = MMoment5[iC];
   }

   F2.Close();
   F1.Close();

   DHFile.SaveToFile("Systematics.dh");

   return 0;
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












