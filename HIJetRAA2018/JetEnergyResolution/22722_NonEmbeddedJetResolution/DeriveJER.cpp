#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "DataHelper.h"
#include "SetStyle.h"

struct Jet;
int main(int argc, char *argv[]);
void AppendJets(vector<Jet> &AllJets, string FileName, string Algorithm, double MinPT, double MaxDR);
void DeriveJER(PdfFileHelper &PdfFile, DataHelper &DHFile, vector<Jet> &AllJets, double EtaMin, double EtaMax);

struct Jet
{
   double JetPT;
   double RefPT;
   double RefEta;
   bool operator <(const Jet &other) const
   {
      if(RefEta < other.RefEta)   return true;
      if(RefEta > other.RefEta)   return false;
      if(RefPT < other.RefPT)     return true;
      if(RefPT > other.RefPT)     return false;
      if(JetPT < other.JetPT)     return true;
      if(JetPT > other.JetPT)     return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames = CL.GetStringVector("Input", vector<string>({""}));
   string OutputFileName    = CL.Get("Output", "JER.pdf");
   string DHFileName        = CL.Get("DHFile", "JER.dh");
   string Algorithm         = CL.Get("Algorithm", "ak4pf");
   double MaxDR             = CL.GetDouble("MaxDR", 0.2);
   double MinPT             = CL.GetDouble("MinPT", 10);

   vector<Jet> AllJets;
   for(string FileName : FileNames)
      AppendJets(AllJets, FileName, Algorithm, MinPT, MaxDR);
   sort(AllJets.begin(), AllJets.end());

   cout << "Number of jets read: " << AllJets.size() << endl;

   int EtaBinCount = 16;
   double EtaBins[] = {-2, -1.75, -1.5, -1.25, -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2};

   DataHelper DHFile(DHFileName);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("JER Derivation");
   
   for(int i = 0; i < EtaBinCount; i++)
      DeriveJER(PdfFile, DHFile, AllJets, EtaBins[i], EtaBins[i+1]);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   DHFile.SaveToFile(DHFileName);

   return 0;
}

void AppendJets(vector<Jet> &AllJets, string FileName, string Algorithm, double MinPT, double MaxDR)
{
   if(FileName == "")
      return;

   cout << "Processing file " << FileName << endl;

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get(Form("%s/t", Algorithm.c_str()));

   if(Tree == nullptr)
      return;

   unsigned char NJet = 0;
   vector<float> *JetPT = nullptr;
   vector<float> *RefPT = nullptr;
   vector<float> *RefEta = nullptr;
   vector<float> *RefDR = nullptr;

   Tree->SetBranchAddress("nref", &NJet);
   Tree->SetBranchAddress("jtpt", &JetPT);
   Tree->SetBranchAddress("refpt", &RefPT);
   Tree->SetBranchAddress("refeta", &RefEta);
   Tree->SetBranchAddress("refdrjt", &RefDR);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         if((*RefPT)[iJ] < MinPT)
            continue;
         if((*RefDR)[iJ] > MaxDR)
            continue;

         Jet NewJet;
         NewJet.JetPT = (*JetPT)[iJ];
         NewJet.RefPT = (*RefPT)[iJ];
         NewJet.RefEta = (*RefEta)[iJ];

         AllJets.push_back(NewJet);
      }
   }

   File.Close();
}

void DeriveJER(PdfFileHelper &PdfFile, DataHelper &DHFile, vector<Jet> &AllJets, double EtaMin, double EtaMax)
{
   int Index1 = -1, Index2 = -1;
   for(int iJ = 0; iJ < (int)AllJets.size(); iJ++)
   {
      if(Index1 == -1 && AllJets[iJ].RefEta >= EtaMin)
         Index1 = iJ;
      if(Index2 == -1 && AllJets[iJ].RefEta >= EtaMax)
         Index2 = iJ;
      if(Index1 != -1 && Index2 != -1)
         break;
   }
   if(Index2 == -1)   // All jets are below EtaMax
      Index2 = AllJets.size();
   if(Index1 == -1)   // All jets are below EtaMin
      return;

   cout << "Number of jets within eta = [" << EtaMin << ", " << EtaMax << "] = " << Index2 - Index1 << endl;

   vector<pair<double, double>> Jets;
   for(int iJ = Index1; iJ < Index2; iJ++)
      Jets.push_back(pair<double, double>(AllJets[iJ].RefPT, AllJets[iJ].JetPT));
   sort(Jets.begin(), Jets.end());

   TGraphAsymmErrors G;

   int NMin = 10000;
   if(Jets.size() > 200000)
      NMin = Jets.size() / 20;

   for(int iJ = 0; iJ + NMin < Jets.size(); iJ = iJ + NMin)
   {
      int IMin = iJ;
      int IMax = iJ + NMin;
      if(IMax + NMin > Jets.size())
         IMax = Jets.size();

      double SumX0 = 0, SumX1 = 0, SumY0 = 0, SumY1 = 0, SumY2 = 0;
      for(int i = IMin; i < IMax; i++)
      {
         double R = Jets[i].second / Jets[i].first;
         SumX0 = SumX0 + 1;
         SumX1 = SumX1 + Jets[i].first;
         SumY0 = SumY0 + 1;
         SumY1 = SumY1 + R;
         SumY2 = SumY2 + R * R;
      }

      double MeanX = SumX1 / SumX0;
      double MeanY = SumY1 / SumY0;
      double RMS = sqrt((SumY2 - SumY1 * SumY1 / SumY0) / SumY0);

      int IP = G.GetN();
      G.SetPoint(IP, MeanX, RMS / MeanY);
      G.SetPointError(IP, MeanX - Jets[IMin].first, Jets[IMax-1].first - MeanX,
         RMS / MeanY / sqrt(SumY0), RMS / MeanY / sqrt(SumY0));
   }

   TF1 F("F", "sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/x/x)", 0, 2000);
   G.Fit(&F);

   PdfFile.AddPlot(G, "ap", false, false, true, true);

   string State = Form("Fit_%.03f_%.03f", EtaMin, EtaMax);
   DHFile[State]["EtaMin"] = EtaMin;
   DHFile[State]["EtaMax"] = EtaMax;
   DHFile[State]["P0"] = F.GetParameter(0);
   DHFile[State]["P1"] = F.GetParameter(1);
   DHFile[State]["P2"] = F.GetParameter(2);
   DHFile[State]["P0Error"] = F.GetParError(0);
   DHFile[State]["P1Error"] = F.GetParError(1);
   DHFile[State]["P2Error"] = F.GetParError(2);
}


