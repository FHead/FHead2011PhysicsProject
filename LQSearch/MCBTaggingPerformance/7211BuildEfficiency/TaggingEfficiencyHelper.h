#ifndef TaggingEfficiencyHelper_H_7211_ASDKLADHKGKDJSG
#define TaggingEfficiencyHelper_H_7211_ASDKLADHKGKDJSG

#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TPaletteAxis.h"

class TaggingEfficiencyHelper;
double EventTaggedChance(vector<double> Efficiencies, int MinimumTagCount = 1);
double EventTaggedChance(vector<double> Efficiencies, int MinimumTagCount = 1, int IndexToSkip = -1);

class TaggingEfficiencyHelper
{
public:
   TH1D *HAllPT;
   TH1D *HSelectedPT;
   TH1D *HAllEta;
   TH1D *HSelectedEta;
   TH2D *HDistributionPTVsEta;
   vector<double> ScaleFactorEta;
   vector<double> ScaleFactorPT;
public:
   TaggingEfficiencyHelper();
   TaggingEfficiencyHelper(TFile &F, string AllPTName, string SelectedPTName,
      string AllEtaName, string SelectedEtaName, string DistributionName);
   ~TaggingEfficiencyHelper();
   void Initialize(TFile &F, string AllPTName, string SelectedPTName,
      string AllEtaName, string SelectedEtaName, string DistributionName);
   void UpdateScaleFactor();
   void RebinPT(int bin);
   void RebinEta(int bin);
   double GetEfficiency(double PT, double Eta);
};

TaggingEfficiencyHelper::TaggingEfficiencyHelper()
{
   HAllPT = NULL;
   HSelectedPT = NULL;
   HAllEta = NULL;
   HSelectedEta = NULL;
   HDistributionPTVsEta = NULL;

   ScaleFactorEta.clear();
   ScaleFactorPT.clear();
}

TaggingEfficiencyHelper::TaggingEfficiencyHelper(TFile &F, string AllPTName, string SelectedPTName,
   string AllEtaName, string SelectedEtaName, string DistributionName)
{
   HAllPT = NULL;
   HSelectedPT = NULL;
   HAllEta = NULL;
   HSelectedEta = NULL;
   HDistributionPTVsEta = NULL;

   ScaleFactorEta.clear();
   ScaleFactorPT.clear();

   Initialize(F, AllPTName, SelectedPTName, AllEtaName, SelectedEtaName, DistributionName);
}

TaggingEfficiencyHelper::~TaggingEfficiencyHelper()
{
}

void TaggingEfficiencyHelper::Initialize(TFile &F, string AllPTName, string SelectedPTName,
   string AllEtaName, string SelectedEtaName, string DistributionName)
{
   HAllPT = (TH1D *)F.Get(AllPTName.c_str());
   HSelectedPT = (TH1D *)F.Get(SelectedPTName.c_str());
   HAllEta = (TH1D *)F.Get(AllEtaName.c_str());
   HSelectedEta = (TH1D *)F.Get(SelectedEtaName.c_str());
   HDistributionPTVsEta = (TH2D *)F.Get(DistributionName.c_str());

   ScaleFactorEta.clear();
   ScaleFactorPT.clear();

   if(HAllPT == NULL || HSelectedPT == NULL || HAllEta == NULL || HSelectedEta == NULL
      || HDistributionPTVsEta == NULL)
   {
      cout << "Initialization of tagging efficiency helper failed!!!" << endl;
      return;
   }

   UpdateScaleFactor();
}

void TaggingEfficiencyHelper::UpdateScaleFactor()
{
   if(HAllPT == NULL || HSelectedPT == NULL || HAllEta == NULL || HSelectedEta == NULL
      || HDistributionPTVsEta == NULL)
      return;
   
   ScaleFactorEta.resize(HAllEta->GetNbinsX());
   ScaleFactorPT.resize(HAllPT->GetNbinsX());

   for(int i = 0; i < (int)ScaleFactorEta.size(); i++)
   {
      double Numerator = 0;
      double Denominator = 0;

      for(int j = 0; j < HAllPT->GetNbinsX(); j++)
      {
         if(HDistributionPTVsEta->GetBinContent(j + 1, i + 1) > 0)
         {
            Numerator = Numerator + HDistributionPTVsEta->GetBinContent(j + 1, i + 1);
            Denominator = Denominator
               + HDistributionPTVsEta->GetBinContent(j + 1, i + 1)
               * HSelectedPT->GetBinContent(j + 1) / HAllPT->GetBinContent(j + 1);
         }
      }

      ScaleFactorEta[i] = Numerator / Denominator;
   }
   
   for(int i = 0; i < (int)ScaleFactorPT.size(); i++)
   {
      double Numerator = 0;
      double Denominator = 0;

      for(int j = 0; j < HAllEta->GetNbinsX(); j++)
      {
         if(HDistributionPTVsEta->GetBinContent(i + 1, j + 1) > 0)
         {
            Numerator = Numerator + HDistributionPTVsEta->GetBinContent(i + 1, j + 1);
            Denominator = Denominator
               + HDistributionPTVsEta->GetBinContent(i + 1, j + 1)
               * HSelectedEta->GetBinContent(j + 1) / HAllEta->GetBinContent(j + 1);
         }
      }

      ScaleFactorPT[i] = Numerator / Denominator;
   }
}

void TaggingEfficiencyHelper::RebinPT(int bin)
{
   if(HAllPT == NULL || HSelectedPT == NULL || HDistributionPTVsEta == NULL)
      return;

   HAllPT->Rebin(bin);
   HSelectedPT->Rebin(bin);
   HDistributionPTVsEta->Rebin2D(bin, 1);
}

void TaggingEfficiencyHelper::RebinEta(int bin)
{
   if(HAllEta == NULL || HSelectedEta == NULL || HDistributionPTVsEta == NULL)
      return;

   HAllEta->Rebin(bin);
   HSelectedEta->Rebin(bin);
   HDistributionPTVsEta->Rebin2D(1, bin);
}
   
double TaggingEfficiencyHelper::GetEfficiency(double PT, double Eta)
{
   int PTBin = HAllPT->FindBin(PT);
   if(PTBin > HAllPT->GetNbinsX())
      PTBin = HAllPT->GetNbinsX();
   if(PTBin <= 0)
      PTBin = 1;

   int EtaBin = HAllEta->FindBin(Eta);
   if(EtaBin > HAllEta->GetNbinsX())
      EtaBin = HAllEta->GetNbinsX();
   if(EtaBin <= 0)
      EtaBin = 1;

   double Numerator = HSelectedPT->GetBinContent(PTBin) * HSelectedEta->GetBinContent(EtaBin);
   double Denominator = HAllPT->GetBinContent(PTBin) * HAllEta->GetBinContent(EtaBin);
   double ScaleFactor1 = ScaleFactorEta[EtaBin-1];
   double ScaleFactor2 = ScaleFactorPT[PTBin-1];
   double ScaleFactor = (ScaleFactor1 + ScaleFactor2) / 2;

   if(Denominator == 0)   // too small PT, not supported!!
      return 0;

   return Numerator / Denominator * ScaleFactor;
}

double EventTaggedChance(vector<double> Efficiencies, int MinimumTagCount, int IndexToSkip)
{
   if(MinimumTagCount == 0)
      return 1;

   for(int i = 0; i < (int)Efficiencies.size(); i++)
      if(Efficiencies[i] == 1)
         Efficiencies[i] = 0.999999;
      
   if(MinimumTagCount == 1)
   {
      Efficiencies.push_back(0);

      double Product = 1;
      for(int i = 0; i < (int)Efficiencies.size() && i != IndexToSkip; i++)
         Product = Product * (1 - Efficiencies[i]);
      return 1 - Product;
   }

   if(MinimumTagCount == 2)
   {
      Efficiencies.push_back(0);
      Efficiencies.push_back(0);
      
      double Product = 1;
      for(int i = 0; i < (int)Efficiencies.size() && i != IndexToSkip; i++)
         Product = Product * (1 - Efficiencies[i]);

      double BadChance = Product;
      for(int i = 0; i < (int)Efficiencies.size() && i != IndexToSkip; i++)
         BadChance = BadChance + Product / (1 - Efficiencies[i]) * Efficiencies[i];

      return 1 - BadChance;
   }

   cout << "Warning!  Event tagged chance calculation of more than 2 tagged jets are not implemented yet!" << endl;

   return 0;
}

#endif

