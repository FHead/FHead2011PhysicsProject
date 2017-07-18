#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"

#define MAX 10000

class Messenger;
class Histograms;
int main();
int GetType(int ID);

class Messenger
{
public:
   TFile *File;
   TTree *Tree;
   bool IsPP;
public:
   double PTHat;
   double Centrality;
   int N;
   double PT[MAX];
   double Eta[MAX];
   double Phi[MAX];
   int ID[MAX];
   double MCWeight;
public:
   Messenger(string FileName, bool ispp) : File(NULL), Tree(NULL), IsPP(ispp)
   {
      File = TFile::Open(FileName.c_str());
      if(File == NULL)
         return;

      Tree = (TTree *)File->Get("Tree");
      if(Tree == NULL)
         return;

      Tree->SetBranchAddress("PTHat", &PTHat);
      Tree->SetBranchAddress("Centrality", &Centrality);
      Tree->SetBranchAddress("GenCount", &N);
      Tree->SetBranchAddress("GenPT", &PT);
      Tree->SetBranchAddress("GenEta", &Eta);
      Tree->SetBranchAddress("GenPhi", &Phi);
      Tree->SetBranchAddress("GenID", &ID);

      if(Tree->GetBranch("MCWeight"))
         Tree->SetBranchAddress("MCWeight", &MCWeight);
      else
         MCWeight = 1;
   }
   ~Messenger()
   {
      if(File != NULL)
      {
         File->Close();
         delete File;
      }
   }
   void GetEntry(int iE)
   {
      PTHat = -1;
      N = 0;

      if(Tree == NULL)
         return;

      Tree->GetEntry(iE);
   }
   int EntryCount()
   {
      if(Tree == NULL)
         return 0;

      return Tree->GetEntries();
   }
   bool PassSelection()
   {
      if(PTHat < 100)
         return false;
      return true;
   }
};

class Histograms
{
public:
   string Tag;
   bool IsPP;
   TH1D *HPTHat;
   TH1D *HGenPT;
   TH1D *HGenEta;
   TH1D *HGenPhi;
   TH1D *HGenEta_PT5;
   TH2D *HGenEtaPhi_PT5;
   TH1D *HType_PT5;
public:
   Histograms(string tag)
      : Tag(tag)
   {
      HPTHat = new TH1D(Form("HPTHat_%s", Tag.c_str()), ";PTHat;", 100, 0, 600);
      HGenPT = new TH1D(Form("HGenPT_%s", Tag.c_str()), ";PT;", 100, 0, 20);
      HGenEta = new TH1D(Form("HGenEta_%s", Tag.c_str()), ";Eta;", 100, -2, 2);
      HGenPhi = new TH1D(Form("HGenPhi_%s", Tag.c_str()), ";Phi;", 100, -M_PI, M_PI);
      HGenEta_PT5 = new TH1D(Form("HGenEta_PT5_%s", Tag.c_str()), ";Eta;", 100, -2, 2);
      HGenEtaPhi_PT5 = new TH2D(Form("HGenEtaPhi_PT5_%s", Tag.c_str()), ";Eta;Phi", 100, -2, 2, 100, -M_PI, M_PI);
      HType_PT5 = new TH1D(Form("HType_PT5_%s", Tag.c_str()), ";Type;", 14, 0, 14);

      BasicStyling(HPTHat);
      BasicStyling(HGenPT);
      BasicStyling(HGenEta);
      BasicStyling(HGenPhi);
      BasicStyling(HGenEta_PT5);
      BasicStyling(HGenEtaPhi_PT5);
      BasicStyling(HType_PT5);
   }
   ~Histograms()
   {
   }
   void Fill(Messenger &M)
   {
      for(int iGen = 0; iGen < M.N; iGen++)
      {
         if(M.Eta[iGen] < -2 || M.Eta[iGen] > 2)
            continue;

         HGenPT->Fill(M.PT[iGen], M.MCWeight);
         HGenEta->Fill(M.Eta[iGen], M.MCWeight);
         HGenPhi->Fill(M.Phi[iGen], M.MCWeight);

         if(M.PT[iGen] > 5)
         {
            HGenEta_PT5->Fill(M.Eta[iGen], M.MCWeight);
            HGenEtaPhi_PT5->Fill(M.Eta[iGen], M.Phi[iGen], M.MCWeight);
            HType_PT5->Fill(GetType(M.ID[iGen]), M.MCWeight);
         }
      }
   }
   void FillAll(Messenger &M)
   {
      double TotalWeight = 0;

      int EntryCount = M.EntryCount();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         M.GetEntry(iE);

         HPTHat->Fill(M.PTHat, M.MCWeight);

         if(M.PassSelection() == false)
            continue;

         TotalWeight = TotalWeight + M.MCWeight;
         Fill(M);
      }
   }
   void Write()
   {
      HPTHat->Write();
      HGenPT->Write();
      HGenEta->Write();
      HGenPhi->Write();
      HGenEta_PT5->Write();
      HGenEtaPhi_PT5->Write();
      HType_PT5->Write();
   }
   void BasicStyling(TH1D *H)
   {
      if(H == NULL)
         return;

      H->Sumw2();
      
      H->SetLineWidth(2);
      H->SetMarkerStyle(20);
      H->SetStats(0);
   }
   void BasicStyling(TH2D *H)
   {
      if(H == NULL)
         return;

      H->Sumw2();

      H->SetLineWidth(2);
      H->SetMarkerStyle(20);
      H->SetStats(0);
   }
   void Scale(double c)
   {
      HPTHat->Scale(c);
      HGenPT->Scale(c);
      HGenEta->Scale(c);
      HGenPhi->Scale(c);
      HGenEta_PT5->Scale(c);
      HGenEtaPhi_PT5->Scale(c);
      HType_PT5->Scale(c);

      DivideByBinSize(HPTHat);
      DivideByBinSize(HGenPT);
      DivideByBinSize(HGenEta);
      DivideByBinSize(HGenPhi);
      DivideByBinSize(HGenEta_PT5);
      DivideByBinSize(HGenEtaPhi_PT5);
      DivideByBinSize(HType_PT5);
   }
   void DivideByBinSize(TH1D *H)
   {
      if(H == NULL)
         return;

      for(int i = 1; i <= H->GetNbinsX(); i++)
      {
         double L = H->GetXaxis()->GetBinLowEdge(i);
         double R = H->GetXaxis()->GetBinUpEdge(i);
         H->SetBinContent(i, H->GetBinContent(i) / (R - L));
         H->SetBinError(i, H->GetBinError(i) / (R - L));
      }
   }
   void DivideByBinSize(TH2D *H)
   {
      if(H == NULL)
         return;

      for(int i = 1; i <= H->GetNbinsX(); i++)
      {
         double L = H->GetXaxis()->GetBinLowEdge(i);
         double R = H->GetXaxis()->GetBinUpEdge(i);

         for(int j = 1; j <= H->GetNbinsY(); j++)
         {
            double B = H->GetYaxis()->GetBinLowEdge(j);
            double T = H->GetYaxis()->GetBinUpEdge(j);

            H->SetBinContent(i, j, H->GetBinContent(i, j) / (R - L) / (T - B));
            H->SetBinError(i, j, H->GetBinError(i, j) / (R - L) / (T - B));
         }
      }
   }
};

int main()
{
   Messenger MAA("ScaledResult/AA6DijetCymbal.root", false);
   Messenger MPP("ScaledResult/PP6Dijet.root", true);
   Messenger MPPHIReco("ScaledResult/PP6DijetHIReco.root", true);

   TFile OutputFile("Histograms.root", "RECREATE");

   Histograms HAA("AA");
   Histograms HPP("PP");
   Histograms HPPHIReco("PPHIReco");

   HAA.FillAll(MAA);
   HPP.FillAll(MPP);
   HPPHIReco.FillAll(MPPHIReco);

   HAA.Write();
   HPP.Write();
   HPPHIReco.Write();

   OutputFile.Close();

   return 0;
}

int GetType(int ID)
{
   if(ID == 1)    return 0;
   if(ID == -1)   return 1;
   if(ID == 2)    return 2;
   if(ID == -2)   return 3;
   if(ID == 3)    return 4;
   if(ID == -3)   return 5;
   if(ID == 4)    return 6;
   if(ID == -4)   return 7;
   if(ID == 5)    return 8;
   if(ID == -5)   return 9;

   if(ID == 21)   return 10;
   if(ID == 22)   return 11;

   if(ID >= 11 && ID <= 16)     return 12;
   if(ID >= -16 && ID <= -11)   return 12;

   return 13;
}




