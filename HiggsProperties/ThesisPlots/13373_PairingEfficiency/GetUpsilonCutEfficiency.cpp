#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

int main();
void GetUpsilonCutEfficiency(string FileName);
double CheckEfficiency(string FileName);

int main()
{
   vector<string> FileNames;
   FileNames.push_back("Result_gg_h_4e_A1ZZ_A2AA_0d01_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A1ZZ_A2AA_0d05_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A1ZZ_A2AA_0d1_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A1ZZ_A2AA_0d5_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A1ZZ_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A2AA_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A2ZA_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_A2ZZ_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_SMVV_A2ZZ0d005_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_SMVV_A2ZZ0d05_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_SMVV_A2ZZ0d0_LooseCuts.root");
   FileNames.push_back("Result_gg_h_4e_SMVV_A2ZZ0d5_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A1ZZ_A2AA_0d01_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A1ZZ_A2AA_0d05_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A1ZZ_A2AA_0d1_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A1ZZ_A2AA_0d5_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A1ZZ_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A2AA_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A2ZA_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_A2ZZ_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_SMVV_A2ZZ0d005_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_SMVV_A2ZZ0d05_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_SMVV_A2ZZ0d0_LooseCuts.root");
   FileNames.push_back("Result_gg_h_2e2mu_SMVV_A2ZZ0d5_LooseCuts.root");

   for(int i = 0; i < (int)FileNames.size(); i++)
      GetUpsilonCutEfficiency(FileNames[i]);

   return 0;
}

void GetUpsilonCutEfficiency(string FileName)
{
   cout << "Amount of events inside upsilon region for file " << FileName << " is " << CheckEfficiency(FileName) << endl;
}

double CheckEfficiency(string FileName)
{
   TFile File(FileName.c_str());
   TTree *T = (TTree *)File.Get("CutTree");
   TH1D H("H", "", 100, 0, 10);

   T->Draw("((M2CMS>8.8&&M2CMS<10.8)||(M1CMS>8.8&&M1CMS<10.8)||(M1Opposite>8.8&&M1Opposite<10.8)||(M2Opposite>8.8&&M2Opposite<10.8))>>H", "(SameMass+OppositeMass+StandardMass)*BaselineCut>0");
   return H.GetMean();
}


