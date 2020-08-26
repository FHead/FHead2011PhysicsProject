#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"

#include "SignificantDigit.h"

#define R02 0
#define R03 1
#define R04 2
#define R06 3
#define R08 4
#define R10 5

#define C0 0
#define C1 1
#define C2 2
#define C3 3
#define PP 4

int main(int argc, char *argv[]);
void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int Cent, bool Sys);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string FileName = CL.Get("Input", "Spectra_Smooth.root");

   // First index: type => C0, C1, C2, C3, PP
   // Second index: radius => 0.2, 0.3, 0.4, 0.6, 0.8, 1.0
   vector<vector<TGraphAsymmErrors>> G(5), GSys(5);

   for(int iC = 0; iC < 5; iC++)
   {
      G[iC].resize(6);
      GSys[iC].resize(6);
      for(int iR = 0; iR < 6; iR++)
      {
         GetGraph(FileName, G[iC][iR], iR, iC, false);
         GetGraph(FileName, GSys[iC][iR], iR, iC, true);
      }
   }

   double LumiTAA[] = {0.100719, 0.051233, 0.025341, 0.018646, 0.023};

   string Cs[] = {"0-10", "10-30", "30-50", "50-80", "Inclusive"};
   string Rs[] = {"0.2", "0.3", "0.4", "0.6", "0.8", "1.0"};

   for(int iR = 0; iR < 6; iR++)
   {
      ofstream out(Form("Table5-%d.yaml", iR + 1));

      vector<pair<double, double>> Xs;
      for(int iC = 0; iC < 5; iC++)
      {
         for(int iP = 0; iP < G[iC][iR].GetN(); iP++)
         {
            double X, Y, EXL, EXH, EYL, EYH, SYL, SYH;
            G[iC][iR].GetPoint(iP, X, Y);
            EXL = G[iC][iR].GetErrorXlow(iP);
            EXH = G[iC][iR].GetErrorXhigh(iP);

            bool Found = false;
            for(int iX = 0; iX < (int)Xs.size(); iX++)
               if(Xs[iX].first < X && Xs[iX].second > X)
                  Found = true;
            if(Found == false)
               Xs.push_back(pair<double, double>(X - EXL, X + EXH));
         }
      }
      sort(Xs.begin(), Xs.end());

      out << "independent_variables:" << endl;
      out << "- header: {name: PT, units: GEV}" << endl;
      out << "  values:" << endl;
      for(int iX = 0; iX < (int)Xs.size(); iX++)
         out << "  - {low: " << Xs[iX].first << ", high: " << Xs[iX].second << "}" << endl;

      out << "dependent_variables:" << endl;
      
      for(int iC = 0; iC < 5; iC++)
      {
         out << "- header: {name: d^2 sigma / d PT d ETA}" << endl;
         out << "  qualifiers:" << endl;
         out << "  - {name: ABS(ETA), value: 0.0-2.0}" << endl;
         if(iC == PP)
            out << "  - {name: RE, value: P P --> JET X}" << endl;
         else
            out << "  - {name: RE, value: PB PB --> JET X}" << endl;
         out << "  - {name: SQRT(S)/NUCLEON, units: GeV, value: '5020'}" << endl;
         out << "  - {name: CENTRALITY, units: pct, value: " << Cs[iC] << "}" << endl;
         out << "  - {name: R, value: " << Rs[iR] << "}" << endl;
         out << "  values:" << endl;

         for(int iX = 0; iX < (int)Xs.size(); iX++)
         {
            bool Found = false;

            for(int iP = 0; iP < G[iC][iR].GetN(); iP++)
            {
               double X, Y, EXL, EXH, EYL, EYH, SYL, SYH;
               G[iC][iR].GetPoint(iP, X, Y);
               EXL = G[iC][iR].GetErrorXlow(iP);
               EXH = G[iC][iR].GetErrorXhigh(iP);
               EYL = G[iC][iR].GetErrorYlow(iP);
               EYH = G[iC][iR].GetErrorYhigh(iP);
               SYL = GSys[iC][iR].GetErrorYlow(iP);
               SYH = GSys[iC][iR].GetErrorYhigh(iP);

               if(Xs[iX].first < X && X < Xs[iX].second)
                  Found = true;
               else
                  continue;

               double Global = LumiTAA[iC] * Y;

               SYL = sqrt(SYL * SYL - Global * Global);
               SYH = sqrt(SYH * SYH - Global * Global);

               int D = FindFirstSignificantDigit(EYL);
               D = max(D, FindFirstSignificantDigit(EYH));
               D = max(D, FindFirstSignificantDigit(SYL));
               D = max(D, FindFirstSignificantDigit(SYH));
               D = max(D, FindFirstSignificantDigit(Global));
               D = D - 1;

               out << "  - value: " << fixed << setprecision(CountDigitBelowPoint(D)) << Y << endl;
               out << "    errors:" << endl;
               out << "    - {label: stat, asymerror: {minus: " << -EYL << ", plus: " << EYH << "}}" << endl;
               out << "    - {label: sys, asymerror: {minus: " << -SYL << ", plus: " << SYH << "}}" << endl;
               out << "    - {label: global, asymerror: {minus: " << -Global << ", plus: " << Global << "}}" << endl;
            }

            if(Found == false)
               out << "  - value: '-'" << endl;
         }
      }


      out.close();
   }

   return 0;
}

void GetGraph(string FileName, TGraphAsymmErrors &G, int R, int Cent, bool Sys)
{
   TFile File(FileName.c_str());

   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"Cent0to10", "Cent10to30", "Cent30to50", "Cent50to90"};

   string HistName = "";
   if(Cent != PP)
      HistName = "akCs" + Rs[R] + "PU3PFFlowJetAnalyzer_" + Cs[Cent];
   else
      HistName = "ak" + Rs[R] + "PFJetAnalyzer_" + Cs[0];

   if(Sys == false)
      HistName = HistName + "_1";
   else
      HistName = HistName + "_2";

   TH1D *H = (TH1D *)File.Get(HistName.c_str());
   if(H == nullptr)
      cout << HistName << endl;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double X = H->GetXaxis()->GetBinCenter(i);
      double Y = H->GetBinContent(i);
      double EX = (H->GetXaxis()->GetBinUpEdge(i) - H->GetXaxis()->GetBinLowEdge(i)) / 2;
      double EY = H->GetBinError(i);

      G.SetPoint(i - 1, X, Y);
      G.SetPointError(i - 1, EX, EX, EY, EY);
   }

   File.Close();
}



