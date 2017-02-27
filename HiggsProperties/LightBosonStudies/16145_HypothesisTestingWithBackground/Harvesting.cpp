#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#define MODELCOUNT 9

struct Triplet;
int main(int argc, char *argv[]);
vector<vector<double>> ReadLikelihood(string FileName);
Triplet GetTriplet(int x, int N);
ostream &operator <<(ostream &out, Triplet &T);

struct Triplet
{
   double Center;
   double Low;
   double High;
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   PdfFileHelper PdfFile("ResultDoubleFile_A1UU_A1UUpA3UU_F.pdf");
   PdfFile.AddTextPage("A1UU (black) vs A1UU+A3UU (red)");

   string File1 = "LikelihoodFixed_A1UU_F_1_Scenario0";
   string File2 = "LikelihoodFixed_A1UUpA3UU_F_1_Scenario0";

   vector<vector<double>> L1 = ReadLikelihood(File1);
   vector<vector<double>> L2 = ReadLikelihood(File2);

   ofstream out("NiceResult.txt");

   // Single model likelihood distributions
   for(int iM = 0; iM < MODELCOUNT; iM++)
   {
      double Min = L1[0][iM];
      double Max = L1[0][iM];

      for(int i = 0; i < (int)L1.size(); i++)
      {
         if(Min > L1[i][iM])
            Min = L1[i][iM];
         if(Max < L1[i][iM])
            Max = L1[i][iM];
      }
      for(int i = 0; i < (int)L2.size(); i++)
      {
         if(Min > L2[i][iM])
            Min = L2[i][iM];
         if(Max < L2[i][iM])
            Max = L2[i][iM];
      }

      double Range = Max - Min;
      Min = Min - Range * 0.1;
      Max = Max + Range * 0.1;

      PdfFile.AddTextPage(Form("Model %d Likelihood", iM));

      TH1D HM1("HM1", ";log(L);a.u.", 100, Min, Max);
      TH1D HM2("HM2", ";log(L);a.u.", 100, Min, Max);

      for(int i = 0; i < (int)L1.size(); i++)
         HM1.Fill(L1[i][iM]);
      for(int i = 0; i < (int)L2.size(); i++)
         HM2.Fill(L2[i][iM]);

      HM1.SetStats(0);
      HM1.SetLineColor(kBlack);

      HM2.SetStats(0);
      HM2.SetLineColor(kRed);

      HM1.Scale(1 / HM1.Integral());
      HM2.Scale(1 / HM2.Integral());

      TCanvas C;

      HM1.Draw();
      HM2.Draw("same");

      PdfFile.AddCanvas(C);
   }

   // Likelihood ratio distributions
   for(int iM1 = 0; iM1 < MODELCOUNT; iM1++)
   {
      for(int iM2 = iM1 + 1; iM2 < MODELCOUNT; iM2++)
      {
         double Min = L1[0][iM1] - L1[0][iM2];
         double Max = L1[0][iM1] - L1[0][iM2];

         vector<double> L1D(L1.size());
         vector<double> L2D(L2.size());

         for(int i = 0; i < (int)L1.size(); i++)
         {
            if(Min > L1[i][iM1] - L1[i][iM2])
               Min = L1[i][iM1] - L1[i][iM2];
            if(Max < L1[i][iM1] - L1[i][iM2])
               Max = L1[i][iM1] - L1[i][iM2];
            
            L1D.push_back(L1[i][iM1] - L1[i][iM2]);
         }
         for(int i = 0; i < (int)L2.size(); i++)
         {
            if(Min > L2[i][iM1] - L2[i][iM2])
               Min = L2[i][iM1] - L2[i][iM2];
            if(Max < L2[i][iM1] - L2[i][iM2])
               Max = L2[i][iM1] - L2[i][iM2];

            L2D.push_back(L2[i][iM1] - L2[i][iM2]);
         }

         double Range = Max - Min;
         Min = Min - Range * 0.1;
         Max = Max + Range * 0.1;

         PdfFile.AddTextPage(Form("Model %d - model %d", iM1, iM2));

         TH1D HM1("HM1", ";log(L) - log(L);a.u.", 100, Min, Max);
         TH1D HM2("HM2", ";log(L) - log(L);a.u.", 100, Min, Max);

         for(int i = 0; i < (int)L1.size(); i++)
            HM1.Fill(L1[i][iM1] - L1[i][iM2]);
         for(int i = 0; i < (int)L2.size(); i++)
            HM2.Fill(L2[i][iM1] - L2[i][iM2]);

         HM1.SetStats(0);
         HM1.SetLineColor(kBlack);

         HM2.SetStats(0);
         HM2.SetLineColor(kRed);

         HM1.Scale(1 / HM1.Integral());
         HM2.Scale(1 / HM2.Integral());

         TCanvas C;

         HM1.Draw();
         HM2.Draw("same");

         PdfFile.AddCanvas(C);

         sort(L1D.begin(), L1D.end());
         sort(L2D.begin(), L2D.end());

         // Usual hypothesis testing
         double L1DMedian = L1D[L1D.size()*0.500];
         double L1DSigmaPlus = L1D[L1D.size()*0.835];
         double L1DSigmaMinus = L1D[L1D.size()*0.165];
         double L2DMedian = L2D[L2D.size()*0.500];
         double L2DSigmaPlus = L2D[L2D.size()*0.835];
         double L2DSigmaMinus = L2D[L2D.size()*0.165];

         int L1DMedianCount = 0;
         int L1DSigmaPlusCount = 0;
         int L1DSigmaMinusCount = 0;
         int L2DMedianCount = 0;
         int L2DSigmaPlusCount = 0;
         int L2DSigmaMinusCount = 0;

         for(int i = 0; i < (int)L2D.size(); i++)
         {
            if(L2D[i] < L1DMedian)       L1DMedianCount = L1DMedianCount + 1;
            if(L2D[i] < L1DSigmaPlus)    L1DSigmaPlusCount = L1DSigmaPlusCount + 1;
            if(L2D[i] < L1DSigmaMinus)   L1DSigmaMinusCount = L1DSigmaMinusCount + 1;
         }
         for(int i = 0; i < (int)L1D.size(); i++)
         {
            if(L1D[i] < L2DMedian)       L2DMedianCount = L2DMedianCount + 1;
            if(L1D[i] < L2DSigmaPlus)    L2DSigmaPlusCount = L2DSigmaPlusCount + 1;
            if(L1D[i] < L2DSigmaMinus)   L2DSigmaMinusCount = L2DSigmaMinusCount + 1;
         }

         if(L1DMedianCount * 2 > (int)L2D.size())       L1DMedianCount = (int)L2D.size() - L1DMedianCount;
         if(L1DSigmaPlusCount * 2 > (int)L2D.size())    L1DSigmaPlusCount = (int)L2D.size() - L1DSigmaPlusCount;
         if(L1DSigmaMinusCount * 2 > (int)L2D.size())   L1DSigmaMinusCount = (int)L2D.size() - L1DSigmaMinusCount;
         if(L2DMedianCount * 2 > (int)L1D.size())       L2DMedianCount = (int)L1D.size() - L2DMedianCount;
         if(L2DSigmaPlusCount * 2 > (int)L1D.size())    L2DSigmaPlusCount = (int)L1D.size() - L2DSigmaPlusCount;
         if(L2DSigmaMinusCount * 2 > (int)L1D.size())   L2DSigmaMinusCount = (int)L1D.size() - L2DSigmaMinusCount;

         Triplet L1DMedianResult = GetTriplet(L1DMedianCount, (int)L2D.size());
         Triplet L1DSigmaPlusResult = GetTriplet(L1DSigmaPlusCount, (int)L2D.size());
         Triplet L1DSigmaMinusResult = GetTriplet(L1DSigmaMinusCount, (int)L2D.size());
         Triplet L2DMedianResult = GetTriplet(L2DMedianCount, (int)L1D.size());
         Triplet L2DSigmaPlusResult = GetTriplet(L2DSigmaPlusCount, (int)L1D.size());
         Triplet L2DSigmaMinusResult = GetTriplet(L2DSigmaMinusCount, (int)L1D.size());

         // model comparison p-value
         double ModelP = 0;
         if(L1D[0] > L2D[L2D.size()-1] || L2D[0] > L1D[L1D.size()-1])   // no overlap!  p-value is zero
            ModelP = 0;
         else  // There is some overlap
         {
            ModelP = 0.5;
         }

         out << iM1 << " " << iM2
            << " " << L1DMedianResult << " " << L1DSigmaPlusResult << " " << L1DSigmaMinusResult
            << " " << L2DMedianResult << " " << L1DSigmaPlusResult << " " << L1DSigmaMinusResult
            << " " << ModelP << endl;
      }
   }

   out.close();

   return 0;
}

vector<vector<double>> ReadLikelihood(string FileName)
{
   vector<vector<double>> Result;

   ifstream in(FileName.c_str());

   double Temp[MODELCOUNT];

   while(in)
   {
      char ch[10240] = "";
      in.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      bool Good = true;
      for(int i = 0; i < MODELCOUNT; i++)
      {
         Temp[i] = 12345678;
         str >> Temp[i];
         if(Temp[i] > 12345677)
            Good = false;
      }

      if(Good == false)
         continue;

      Result.push_back(vector<double>(Temp, Temp + MODELCOUNT));
   }

   in.close();

   return Result;
}

Triplet GetTriplet(int x, int N)
{
   Triplet Result;

   Result.Center = (double)x / N;
   Result.Low = Result.Center / 2;
   Result.High = Result.Center + (1 - Result.Center) / 2;

   return Result;
}

ostream &operator <<(ostream &out, Triplet &T)
{
   out << T.Center << " " << T.Low << " " << T.High;
   return out;
}






