#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"

#include "ProgressBar.h"
#include "PlotHelper2.h"

struct FitResultSummary;
int main();
string ToString(int Number, int Digit);
string GetType(const FitResultSummary &M);

struct FitResultSummary
{
public:
   float A2ZZA1ZZ, A2ZZA1ZZError;
   float A2ZZPhase, A2ZZPhaseError;
   float A3ZZA1ZZ, A3ZZA1ZZError;
   float A3ZZPhase, A3ZZPhaseError;
   float A2ZAA1ZZ, A2ZAA1ZZError;
   float A2ZAPhase, A2ZAPhaseError;
   float A3ZAA1ZZ, A3ZAA1ZZError;
   float A3ZAPhase, A3ZAPhaseError;
   float A2AAA1ZZ, A2AAA1ZZError;
   float A2AAPhase, A2AAPhaseError;
   float A3AAA1ZZ, A3AAA1ZZError;
   float A3AAPhase, A3AAPhaseError;
   float Fem, FemError;
   float Fme, FmeError;
   float Fee, FeeError;
   float Fmm, FmmError;
   float N1, N1Error;
   float N2, N2Error;
   float EDM;
   float Sem, Bem;
   float Sme, Bme;
   float See, Bee;
   float Smm, Bmm;
   float FitStatus;
};

int main()
{
   TChain Tree("ResultTree", "ResultTree");
   Tree.AddFile("Output_16.root");

   FitResultSummary M;
   Tree.SetBranchAddress("A2ZZA1ZZ", &M.A2ZZA1ZZ);
   Tree.SetBranchAddress("A2ZZA1ZZError", &M.A2ZZA1ZZError);
   Tree.SetBranchAddress("A3ZZA1ZZ", &M.A3ZZA1ZZ);
   Tree.SetBranchAddress("A3ZZA1ZZError", &M.A3ZZA1ZZError);
   Tree.SetBranchAddress("A2ZAA1ZZ", &M.A2ZAA1ZZ);
   Tree.SetBranchAddress("A2ZAA1ZZError", &M.A2ZAA1ZZError);
   Tree.SetBranchAddress("A3ZAA1ZZ", &M.A3ZAA1ZZ);
   Tree.SetBranchAddress("A3ZAA1ZZError", &M.A3ZAA1ZZError);
   Tree.SetBranchAddress("A2AAA1ZZ", &M.A2AAA1ZZ);
   Tree.SetBranchAddress("A2AAA1ZZError", &M.A2AAA1ZZError);
   Tree.SetBranchAddress("A3AAA1ZZ", &M.A3AAA1ZZ);
   Tree.SetBranchAddress("A3AAA1ZZError", &M.A3AAA1ZZError);
   Tree.SetBranchAddress("Fem", &M.Fem);
   Tree.SetBranchAddress("FemError", &M.FemError);
   Tree.SetBranchAddress("N1", &M.N1);
   Tree.SetBranchAddress("N1Error", &M.N1Error);
   Tree.SetBranchAddress("N2", &M.N2);
   Tree.SetBranchAddress("N2Error", &M.N2Error);
   Tree.SetBranchAddress("Sem", &M.Sem);
   Tree.SetBranchAddress("Bem", &M.Bem);
   Tree.SetBranchAddress("Status", &M.FitStatus);

   TFile File("Histograms.root", "RECREATE");

   map<string, TH1D *> H1D;

   string TNames[] = {"A2ZZ", "A3ZZ", "A2ZA", "A3ZA", "A2AA", "A3AA"};
   double Boundary[] = {5, 8, 0.1, 0.1, 0.1, 0.1};
   double Center[] = {3, 5, 0, 0, 0, 0};
   
   int SignalSizes[] = {25, 50, 100, 200, 400, 800, 1600};

   string BName = "N";
   for(int iA = 1; iA < 64; iA++)
   {
      string AName = ToString(iA, 6);
      for(int iN = 0; iN < 4; iN++)
      {
         if(iN > 0)
            continue;
         string NName = ToString(iN, 2);
         for(int iS = 0; iS < 7; iS++)
         {
            string SName = "1";
            SName[0] = char(SName[0] + iS);
            for(int iT = 0; iT < 6; iT++)
            {
               string TName = TNames[iT];
               string HistogramName = "H_" + AName + "_" + NName + "_" + BName + "_" + SName + "_" + TName;
               
               TH1D *H = new TH1D(HistogramName.c_str(), HistogramName.c_str(), 50,
                  Center[iT] - Boundary[iT], Center[iT] + Boundary[iT]);
               H1D.insert(pair<string, TH1D *>(HistogramName, H));
            }
         }
      }
   }

   int EntryCount = Tree.GetEntries();
   ProgressBar Bar(cerr, EntryCount);
   Bar.SetStyle(3);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      if(iE % (EntryCount / 300) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      if(M.FitStatus < 3)
         continue;

      string Identifier = GetType(M);

      double Centers[6] = {0};
      Centers[0] = M.A2ZZA1ZZ;
      Centers[1] = M.A3ZZA1ZZ;
      Centers[2] = M.A2ZAA1ZZ;
      Centers[3] = M.A3ZAA1ZZ;
      Centers[4] = M.A2AAA1ZZ;
      Centers[5] = M.A3AAA1ZZ;

      for(int iT = 0; iT < 6; iT++)
      {
         if(H1D.find(Identifier + TNames[iT]) == H1D.end())
            continue;

         TH1D *H = H1D[Identifier+TNames[iT]];

         H->Fill(Centers[iT]);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   PsFileHelper PsFile("PlotDump.ps");
   PsFile.AddTextPage("A dump of plots...");

   for(map<string, TH1D *>::iterator iter = H1D.begin(); iter != H1D.end(); iter++)
   {
      if(iter->second == NULL)
         continue;
      if(iter->second->GetEntries() == 0)
         continue;
      iter->second->SetStats(0);
      iter->second->Scale(1 / iter->second->Integral());
      iter->second->Write();
      // PsFile.AddPlot(iter->second);

      TCanvas C;
      iter->second->Draw();
      // C.SaveAs(Form("Plots/%s.gif", iter->first.c_str()));
      C.SaveAs(Form("Plots/%s.pdf", iter->first.c_str()));
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}

string ToString(int Number, int Digit)
{
   string Result = "";

   for(int i = 0; i < Digit; i++)
   {
      if(Number % 2 == 0)
         Result = Result + "N";
      else
         Result = Result + "Y";
      Number = Number / 2;
   }

   reverse(Result.begin(), Result.end());

   return Result;
}

string GetType(const FitResultSummary &M)
{
   string Result = "H_";

   if(M.A2ZZA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";
   if(M.A3ZZA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";
   if(M.A2ZAA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";
   if(M.A3ZAA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";
   if(M.A2AAA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";
   if(M.A3AAA1ZZError < 1e-20)   Result = Result + "N";
   else                          Result = Result + "Y";

   Result = Result + "_";

   if(M.N1Error < 1e-20)   Result = Result + "N";
   else                    Result = Result + "Y";
   if(M.N2Error < 1e-20)   Result = Result + "N";
   else                    Result = Result + "Y";

   Result = Result + "_";

   if(M.FemError < 1e-20)   Result = Result + "N";
   else                     Result = Result + "Y";

   Result = Result + "_";

   int Count = (int)(M.Sem);
   if(Count == 25)     Result = Result + "1";
   if(Count == 50)     Result = Result + "2";
   if(Count == 100)    Result = Result + "3";
   if(Count == 200)    Result = Result + "4";
   if(Count == 400)    Result = Result + "5";
   if(Count == 800)    Result = Result + "6";
   if(Count == 1600)   Result = Result + "7";

   Result = Result + "_";

   return Result;
}


