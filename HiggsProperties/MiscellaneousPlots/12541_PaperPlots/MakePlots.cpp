#include <iostream>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

class TreeMessenger;
int main(int argc, char *argv[]);

class TreeMessenger
{
public:
   float A1ZZ, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA;
   float F, S, B, N1, N2;
   TTree *T;
public:
   void SetBranchAddress(TTree *Tree)
   {
      if(Tree == NULL)   return;

      Tree->SetBranchAddress("A1ZZ", &A1ZZ);
      Tree->SetBranchAddress("A2ZZ", &A2ZZ);   Tree->SetBranchAddress("A3ZZ", &A3ZZ);
      Tree->SetBranchAddress("A2ZA", &A2ZA);   Tree->SetBranchAddress("A3ZA", &A3ZA);
      Tree->SetBranchAddress("A2AA", &A2AA);   Tree->SetBranchAddress("A3AA", &A3AA);
      Tree->SetBranchAddress("F", &F);   
      Tree->SetBranchAddress("S", &S);         Tree->SetBranchAddress("B", &B);
      Tree->SetBranchAddress("N1", &N1);       Tree->SetBranchAddress("N2", &N2);

      T = Tree;
   }
   map<string, TH1D *> CreateHistograms(string NamePrefix, bool IsExotic)
   {
      map<string, TH1D *> Histograms;

      string NNString = "NN", FString = "N", SString = "1", CString = "2";

      for(int iN = 0; iN < 2; iN++)
      {
         if(iN == 0)   NNString = "NN";
         else          NNString = "YY";

         for(int iF = 0; iF < 2; iF++)
         {
            if(iF == 0)   FString = "N";
            else          FString = "Y";

            for(int iS = 1; iS <= 7; iS++)
            {
               SString = Form("%d", iS);

               for(int iC = 1; iC <= 8; iC++)
               {
                  CString = Form("%d", iC);

                  string ID = NNString + "_" + FString + "_" + SString + "_" + CString;
                  string HistogramName = "H_" + NamePrefix + "_" + ID;

                  double LimitMin = 0, LimitMax = 1;
                  if(iC == 1)   LimitMin = 0, LimitMax = 1;
                  if(iC == 2)   LimitMin = -1, LimitMax = 1;
                  if(iC == 3)   LimitMin = -1, LimitMax = 1;
                  if(iC == 4)   LimitMin = -0.05, LimitMax = 0.05;
                  if(iC == 5)   LimitMin = -0.05, LimitMax = 0.05;
                  if(iC == 6)   LimitMin = -0.05, LimitMax = 0.05;
                  if(iC == 7)   LimitMin = -0.05, LimitMax = 0.05;
                  if(iC == 8)   LimitMin = 0, LimitMax = 1;
                  TH1D *H = new TH1D(HistogramName.c_str(), "", 120, LimitMin, LimitMax);

                  Histograms.insert(pair<string, TH1D *>("N_" + ID, H));

                  HistogramName = "H_" + NamePrefix + "O_" + ID;

                  LimitMin = 0, LimitMax = 1;
                  if(iC == 1)   continue;
                  if(iC == 2)   LimitMin = -5 + (IsExotic ? 3.5 : 0), LimitMax = 5 + (IsExotic ? 3.5 : 0);
                  if(iC == 3)   LimitMin = -8 + (IsExotic ? 5 : 0), LimitMax = 8 + (IsExotic ? 5 : 0);
                  if(iC == 4)   LimitMin = -0.2, LimitMax = 0.2;
                  if(iC == 5)   LimitMin = -0.2, LimitMax = 0.2;
                  if(iC == 6)   LimitMin = -0.2, LimitMax = 0.2;
                  if(iC == 7)   LimitMin = -0.2, LimitMax = 0.2;
                  if(iC == 8)   continue;
                  H = new TH1D(HistogramName.c_str(), "", 120, LimitMin, LimitMax);

                  Histograms.insert(pair<string, TH1D *>("O_" + ID, H));
               }
            }
         }
      }

      return Histograms;
   }
   map<string, TH1D *> FillBasicHistograms(string NamePrefix, bool IsExotic)
   {
      if(T == NULL)   return map<string, TH1D *>();

      map<string, TH1D *> Histograms = CreateHistograms(NamePrefix, IsExotic);

      int EntryCount = T->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         T->GetEntry(iE);

         string NString = "NN", FString, SString;

         if(N1 < -100 && N2 < -100)   NString = "NN";
         if(N1 > -100 && N2 > -100)   NString = "YY";

         if(F < 0)    FString = "N";
         if(F >= 0)   FString = "Y";

         if(S == 25)      SString = "1";
         if(S == 50)      SString = "2";
         if(S == 100)     SString = "3";
         if(S == 200)     SString = "4";
         if(S == 400)     SString = "5";
         if(S == 800)     SString = "6";
         if(S == 1600)    SString = "7";

         string ID = NString + "_" + FString + "_" + SString + "_";

         if(Histograms.find("N_" + ID + "1") != Histograms.end())
            Histograms["N_"+ID+"1"]->Fill(A1ZZ);
         if(Histograms.find("N_" + ID + "2") != Histograms.end())
            Histograms["N_"+ID+"2"]->Fill(A2ZZ);
         if(Histograms.find("N_" + ID + "3") != Histograms.end())
            Histograms["N_"+ID+"3"]->Fill(A3ZZ);
         if(Histograms.find("N_" + ID + "4") != Histograms.end())
            Histograms["N_"+ID+"4"]->Fill(A2ZA);
         if(Histograms.find("N_" + ID + "5") != Histograms.end())
            Histograms["N_"+ID+"5"]->Fill(A3ZA);
         if(Histograms.find("N_" + ID + "6") != Histograms.end())
            Histograms["N_"+ID+"6"]->Fill(A2AA);
         if(Histograms.find("N_" + ID + "7") != Histograms.end())
            Histograms["N_"+ID+"7"]->Fill(A3AA);
         if(Histograms.find("N_" + ID + "8") != Histograms.end())
            Histograms["N_"+ID+"8"]->Fill(F);
         
         if(Histograms.find("O_" + ID + "2") != Histograms.end())
            Histograms["O_"+ID+"2"]->Fill(A2ZZ / A1ZZ);
         if(Histograms.find("O_" + ID + "3") != Histograms.end())
            Histograms["O_"+ID+"3"]->Fill(A3ZZ / A1ZZ);
         if(Histograms.find("O_" + ID + "4") != Histograms.end())
            Histograms["O_"+ID+"4"]->Fill(A2ZA / A1ZZ);
         if(Histograms.find("O_" + ID + "5") != Histograms.end())
            Histograms["O_"+ID+"5"]->Fill(A3ZA / A1ZZ);
         if(Histograms.find("O_" + ID + "6") != Histograms.end())
            Histograms["O_"+ID+"6"]->Fill(A2AA / A1ZZ);
         if(Histograms.find("O_" + ID + "7") != Histograms.end())
            Histograms["O_"+ID+"7"]->Fill(A3AA / A1ZZ);
      }

      return Histograms;
   }
   map<string, TH2D *> CreateHistograms2D(string NamePrefix, bool IsExotic)
   {
      map<string, TH2D *> Histograms;

      string NNString = "NN", FString = "N", SString = "1", CString = "2";

      for(int iN = 0; iN < 2; iN++)
      {
         if(iN == 0)   NNString = "NN";
         else          NNString = "YY";

         for(int iF = 0; iF < 2; iF++)
         {
            if(iF == 0)   FString = "N";
            else          FString = "Y";

            for(int iS = 1; iS <= 7; iS++)
            {
               SString = Form("%d", iS);

               for(int iC1 = 2; iC1 <= 8; iC1++)
               {
                  for(int iC2 = iC1 + 1; iC2 <= 8; iC2++)
                  {
                     CString = Form("%d%d", iC1, iC2);
   
                     string ID = NNString + "_" + FString + "_" + SString + "_" + CString;
                     string HistogramName = "H_" + NamePrefix + "O_" + ID;
   
                     double LimitXMin = 0, LimitXMax = 1, LimitYMin = 0, LimitYMax = 1;
                     if(iC1 == 2)   LimitXMin = -5 + (IsExotic ? 3.5 : 0), LimitXMax = 5 + (IsExotic ? 3.5 : 0);
                     if(iC1 == 3)   LimitXMin = -8 + (IsExotic ? 5 : 0), LimitXMax = 8 + (IsExotic ? 5 : 0);
                     if(iC1 == 4)   LimitXMin = -0.2, LimitXMax = 0.2;
                     if(iC1 == 5)   LimitXMin = -0.2, LimitXMax = 0.2;
                     if(iC1 == 6)   LimitXMin = -0.2, LimitXMax = 0.2;
                     if(iC1 == 7)   LimitXMin = -0.2, LimitXMax = 0.2;
                     if(iC1 == 8)   LimitXMin = 0, LimitXMax = 1;
                     if(iC2 == 2)   LimitYMin = -5 + (IsExotic ? 3.5 : 0), LimitYMax = 5 + (IsExotic ? 3.5 : 0);
                     if(iC2 == 3)   LimitYMin = -8 + (IsExotic ? 5 : 0), LimitYMax = 8 + (IsExotic ? 5 : 0);
                     if(iC2 == 4)   LimitYMin = -0.2, LimitYMax = 0.2;
                     if(iC2 == 5)   LimitYMin = -0.2, LimitYMax = 0.2;
                     if(iC2 == 6)   LimitYMin = -0.2, LimitYMax = 0.2;
                     if(iC2 == 7)   LimitYMin = -0.2, LimitYMax = 0.2;
                     if(iC2 == 8)   LimitYMin = 0, LimitYMax = 1;
                     TH2D *H = new TH2D(HistogramName.c_str(), "",
                        120, LimitXMin, LimitXMax, 120, LimitYMin, LimitYMax);
   
                     Histograms.insert(pair<string, TH2D *>("O_" + ID, H));
                  }
               }
            }
         }
      }

      return Histograms;
   }
   map<string, TH2D *> FillBasicHistograms2D(string NamePrefix, bool IsExotic)
   {
      if(T == NULL)   return map<string, TH2D *>();

      map<string, TH2D *> Histograms = CreateHistograms2D(NamePrefix, IsExotic);

      int EntryCount = T->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         T->GetEntry(iE);

         string NString = "NN", FString, SString;

         if(N1 < -100 && N2 < -100)   NString = "NN";
         if(N1 > -100 && N2 > -100)   NString = "YY";

         if(F < 0)    FString = "N";
         if(F >= 0)   FString = "Y";

         if(S == 25)      SString = "1";
         if(S == 50)      SString = "2";
         if(S == 100)     SString = "3";
         if(S == 200)     SString = "4";
         if(S == 400)     SString = "5";
         if(S == 800)     SString = "6";
         if(S == 1600)    SString = "7";

         string ID = NString + "_" + FString + "_" + SString + "_";

         double OValues[] = {A2ZZ / A1ZZ, A3ZZ / A1ZZ, A2ZA / A1ZZ, A3ZA / A1ZZ, A2AA / A1ZZ, A3AA / A1ZZ, F};

         for(int iC1 = 2; iC1 <= 8; iC1++)
         {
            for(int iC2 = iC1 + 1; iC2 <= 8; iC2++)
            {
               string HistogramID = "O_" + ID + Form("%d%d", iC1, iC2);
               if(Histograms.find(HistogramID) != Histograms.end())
                  Histograms[HistogramID]->Fill(OValues[iC1-2], OValues[iC2-2]);
            }
         }
      }

      return Histograms;
   }
};

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Model=(11|16|31|36)" << endl;
      return -1;
   }

   bool IsExotic = false;
   if(string(argv[3]) == "16" || string(argv[3]) == "36")
      IsExotic = true;

   TreeMessenger M;

   TFile FInput(argv[1]);

   M.SetBranchAddress((TTree *)FInput.Get("Tree"));
   TTree *T = (TTree *)FInput.Get("Tree");
   cout << T->GetEntries() << endl;
   
   TFile FOutput(argv[2], "recreate");
   
   map<string, TH1D *> GenHistograms = M.FillBasicHistograms("", IsExotic);
   map<string, TH2D *> GenHistograms2D = M.FillBasicHistograms2D("", IsExotic);

   for(map<string, TH1D *>::iterator iter = GenHistograms.begin(); iter != GenHistograms.end(); iter++)
   {
      if(iter->second == NULL)              continue;
      if(iter->second->GetEntries() == 0)   continue;

      iter->second->Write();
   }
   for(map<string, TH2D *>::iterator iter = GenHistograms2D.begin(); iter != GenHistograms2D.end(); iter++)
   {
      if(iter->second == NULL)              continue;
      if(iter->second->GetEntries() == 0)   continue;

      iter->second->Write();
   }
   
   FOutput.Close();
   
   FInput.Close();
   
   return 0;
}






