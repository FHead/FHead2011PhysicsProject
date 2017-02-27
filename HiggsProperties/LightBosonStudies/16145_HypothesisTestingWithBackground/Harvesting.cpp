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
pair<double, double> BinomialRange(int x, int N);
double JntBinomial(int x, int N, double r);
double LogFactorial(int N);

struct Triplet
{
   double Center;
   double Low;
   double High;
};

int main(int argc, char *argv[])
{
   string Model1 = "A1UU";
   string Model2 = "A2UU";
   string Scenario = "1";
   string Cut = "F";
   string File1 = "LikelihoodFixed_A1UU_F_1_Scenario1";
   string File2 = "LikelihoodFixed_A2UU_F_1_Scenario1";

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " Model1 Model2 Cut Scenario File1 File2" << endl;
      return -1;
   }

   Model1 = argv[1];
   Model2 = argv[2];
   Cut = argv[3];
   Scenario = argv[4];
   File1 = argv[5];
   File2 = argv[6];
   
   SetThesisStyle();

   PdfFileHelper PdfFile("PDF/ResultDoubleFile_" + Model1 + "_" + Model2 + "_" + Cut + "_Scenario" + Scenario + ".pdf");
   PdfFile.AddTextPage(Model1 + " (black) vs " + Model2 + " (red)");

   vector<vector<double>> L1 = ReadLikelihood(File1);
   vector<vector<double>> L2 = ReadLikelihood(File2);

   ofstream out("ModelComparison/NiceResult_" + Model1 + "_" + Model2 + "_" + Cut + "_Scenario" + Scenario + ".txt");

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
            
            L1D[i] = L1[i][iM1] - L1[i][iM2];
         }
         for(int i = 0; i < (int)L2.size(); i++)
         {
            if(Min > L2[i][iM1] - L2[i][iM2])
               Min = L2[i][iM1] - L2[i][iM2];
            if(Max < L2[i][iM1] - L2[i][iM2])
               Max = L2[i][iM1] - L2[i][iM2];

            L2D[i] = L2[i][iM1] - L2[i][iM2];
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
            int BestI1 = -1;
            int BestI2 = -1;
            double BestD = -1;

            bool Swapped = false;
            if(L1D.size() < L2D.size())
            {
               swap(L1D, L2D);
               Swapped = true;
            }

            for(int I1 = 0; I1 < (int)L1D.size(); I1++)
            {
               int I2Min = (int)((1 - (double)(I1 + 2) / L1D.size()) * L2D.size());
               int I2Max = (int)((1 - (double)(I1 - 2) / L1D.size()) * L2D.size());

               if(I2Min < 0)                  I2Min = 0;
               if(I2Max >= (int)L2D.size())   I2Max = (int)L2D.size() - 1;

               int BestI2R = I2Min;
               double BestRD = fabs((double)I1 / (int)L1D.size() - (1 - (double)BestI2R / (int)L2D.size()));
               
               for(int I2 = I2Min; I2 < I2Max; I2++)
               {
                  double D = fabs((double)I1 / (int)L1D.size() - (1 - (double)I2 / (int)L2D.size()));

                  if(D < BestRD)
                  {
                     BestI2R = I2;
                     BestRD = D;
                  }
               }

               double D = fabs(L1D[I1] - L2D[BestI2R]);
               
               if(BestD < 0 || D < BestD)
               {
                  BestI1 = I1;
                  BestI2 = BestI2R;
                  BestD = D;
               }
            }

            double P1 = (double)BestI1 / L1D.size();
            double P2 = 1 - (double)BestI2 / L2D.size();

            ModelP = (P1 + P2) / 2;

            if(ModelP > 0.5)
               ModelP = 1 - ModelP;

            if(Swapped == true)
               swap(L1D, L2D);
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

   pair<double, double> Range = BinomialRange(x, N);

   Result.Center = (double)x / N;
   Result.Low = Range.first;
   Result.High = Range.second;

   return Result;
}

ostream &operator <<(ostream &out, Triplet &T)
{
   out << T.Center << " " << T.Low << " " << T.High;
   return out;
}

pair<double, double> BinomialRange(int x, int N)
{
   if(N > 10000)
   {
      pair<double, double> FakeRange;
      double r = (double)x / N;
      FakeRange.first = max(0.0, r - r * (1 / sqrt(max(x, 1)) + 1 / sqrt(N)));
      FakeRange.second = min(1.0, r + r * (1 / sqrt(max(x, 1)) + 1 / sqrt(N)));
      return FakeRange;
   }

   double Max = JntBinomial(x, N, 1);

   double BestR = (double)x / N;
   double LogBestHeight = x * log(BestR) + (N - x) * log(1 - BestR);
   if(x == 0)
      LogBestHeight = (N - x) * log(1 - BestR);
   if(x == N)
      LogBestHeight = x * log(BestR);

   pair<double, double> Range(0, 1);

   double LogHeightL = LogBestHeight - 20, LogHeightR = LogBestHeight;
   while(LogHeightR - LogHeightL > 1e-6)
   {
      double LogHeightC = (LogHeightL + LogHeightR) / 2;

      double L = 0, R = BestR;
      while(R - L > 1e-8)
      {
         double C = (L + R) / 2;
         double LH = x * log(C) + (N - x) * log(1 - C);
         if(LH < LogHeightC)
            L = C;
         else
            R = C;
      }
      Range.first = (L + R) / 2;

      L = BestR, R = 1;
      while(R - L > 1e-8)
      {
         double C = (L + R) / 2;
         double LH = x * log(C) + (N - x) * log(1 - C);
         if(LH >= LogHeightC)
            L = C;
         else
            R = C;
      }
      Range.second = (L + R) / 2;

      double Check = JntBinomial(x, N, Range.second) - JntBinomial(x, N, Range.first);
      if(Check < 0.90 * Max)   // Range too small, lower height
         LogHeightR = LogHeightC;
      else
         LogHeightL = LogHeightC;
   }

   return Range;
}

double JntBinomial(int x, int N, double r)
{
   // This calculates C(N,x) * \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;

   if(x == 0)
      return (1 - pow(1 - r, N + 1)) / (N + 1);

   double LogExtraTerm = x * log(r) + (N - x + 1) * log(1 - r);
   LogExtraTerm = LogExtraTerm + LogFactorial(N);
   LogExtraTerm = LogExtraTerm - LogFactorial(x);
   LogExtraTerm = LogExtraTerm - LogFactorial(N - x + 1);

   if(r == 1)   // there is no extra term when r = 1
      return JntBinomial(x - 1, N, r);

   return JntBinomial(x - 1, N, r) - exp(LogExtraTerm);
}

double LogFactorial(int N)
{
   static double Result[100000] = {0};

   if(N == 0)   // log(0) = 0
      return 0;
   if(N == 1)   // log(1) = 0
      return 0;

   if(Result[N] == 0)
   {
      double Answer = LogFactorial(N - 1) + log(N);
      Result[N] = Answer;
      return Answer;
   }

   return Result[N];
}



