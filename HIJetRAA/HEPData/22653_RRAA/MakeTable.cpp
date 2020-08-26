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

#define PT0 0
#define PT1 1
#define PT2 2
#define PT3 3
#define PT4 4

#define C0 0
#define C1 1
#define C2 2
#define C3 3

int main(int argc, char *argv[]);
void GetRRAA(TGraphAsymmErrors &H, string FileName, int P, int C, bool Sys = false);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string FileName = CL.Get("Input", "RRAA_Smooth_RedStat.root");

   // First index: type => C0, C1, C2, C3
   // Second index: PT => 200-250, 250-300, 300-400, 400-500, 500-1000
   vector<vector<TGraphAsymmErrors>> G(4), GSys(4);
   for(int iC = 0; iC < 4; iC++)
   {
      G[iC].resize(5);
      GSys[iC].resize(5);

      for(int iPT = 0; iPT < 5; iPT++)
      {
         GetRRAA(G[iC][iPT], FileName, iPT, iC, false);
         GetRRAA(GSys[iC][iPT], FileName, iPT, iC, true);
      }
   }

   string Cs[] = {"0-10", "10-30", "30-50", "50-90"};
   string PTs[] = {"200-250", "250-300", "300-400", "400-500", "500-1000"};

   for(int iPT = 0; iPT < 5; iPT++)
   {
      ofstream out(Form("Table8-%d.yaml", iPT + 1));

      vector<pair<double, double>> Xs;
      Xs.push_back(pair<double, double>(0.25, 0.35));
      Xs.push_back(pair<double, double>(0.35, 0.45));
      Xs.push_back(pair<double, double>(0.55, 0.65));
      Xs.push_back(pair<double, double>(0.75, 0.85));
      Xs.push_back(pair<double, double>(0.95, 1.05));

      out << "independent_variables:" << endl;
      out << "- header: {name: R}" << endl;
      out << "  values:" << endl;
      for(int iX = 0; iX < (int)Xs.size(); iX++)
         out << "  - value: " << fixed << setprecision(1) << (Xs[iX].first + Xs[iX].second) / 2 << endl;

      out << "dependent_variables:" << endl;

      for(int iC = 0; iC < 4; iC++)
      {
         out << "- header: {name: RAA(R) / RAA(R=0.2)}" << endl;
         out << "  qualifiers:" << endl;
         out << "  - {name: ABS(ETA), value: 0.0-2.0}" << endl;
         out << "  - {name: RE, value: 'PB PB --> JET X, P P --> JET X'}" << endl;
         out << "  - {name: SQRT(S)/NUCLEON, units: GeV, value: '5020'}" << endl;
         out << "  - {name: CENTRALITY, units: pct, value: " << Cs[iC] << "}" << endl;
         out << "  - {name: PT, units: GEV, value: " << PTs[iPT] << "}" << endl;
         out << "  values:" << endl;

         for(int iX = 0; iX < (int)Xs.size(); iX++)
         {
            bool Found = false;

            for(int iR = 0; iR < G[iC][iR].GetN(); iR++)
            {
               double X, Y;
               G[iC][iPT].GetPoint(iR, X, Y);
               double EYL = G[iC][iPT].GetErrorYlow(iR);
               double EYH = G[iC][iPT].GetErrorYhigh(iR);
               double SYL = GSys[iC][iPT].GetErrorYlow(iR);
               double SYH = GSys[iC][iPT].GetErrorYhigh(iR);

               cout << iC << " " << iPT << " " << iR << " " << X << " " << Y << endl;
               
               if(Xs[iX].first < X && X < Xs[iX].second && Y > 0.001)
                  Found = true;
               else
                  continue;

               int D = FindFirstSignificantDigit(EYL);
               D = max(D, FindFirstSignificantDigit(EYH));
               D = max(D, FindFirstSignificantDigit(SYL));
               D = max(D, FindFirstSignificantDigit(SYH));
               D = D - 1;

               out << "  - value: " << fixed << setprecision(CountDigitBelowPoint(D)) << Y << endl;
               out << "    errors:" << endl;
               out << "    - {label: stat, asymerror: {minus: " << -EYL << ", plus: " << EYH << "}}" << endl;
               out << "    - {label: sys, asymerror: {minus: " << -SYL << ", plus: " << SYH << "}}" << endl;
            }

            if(Found == false)
               out << "  - value: '-'" << endl;
         }
      }

      out.close();
   }

   return 0;
}

void GetRRAA(TGraphAsymmErrors &H, string FileName, int P, int C, bool Sys)
{
   TFile File(FileName.c_str());

   string Ps[] = {"200p0to250p0", "250p0to300p0", "300p0to400p0", "400p0to500p0", "500p0to1000p0"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};

   string HistogramName = "";
   
   HistogramName = HistogramName + "Cent" + Cs[C];
   HistogramName = HistogramName + "_" + Ps[P];
   if(Sys == false)   HistogramName = HistogramName + "_1";
   else               HistogramName = HistogramName + "_2";
      
   vector<pair<double, double>> Xs;
   Xs.push_back(pair<double, double>(0.25, 0.35));
   Xs.push_back(pair<double, double>(0.35, 0.45));
   Xs.push_back(pair<double, double>(0.55, 0.65));
   Xs.push_back(pair<double, double>(0.75, 0.85));
   Xs.push_back(pair<double, double>(0.95, 1.05));

   if(Sys == false)
   {
      TGraphAsymmErrors *G = (TGraphAsymmErrors *)File.Get(HistogramName.c_str());
      
      for(int iX = 0; iX < 5; iX++)
      {
         H.SetPoint(iX, (Xs[iX].first + Xs[iX].second) / 2, 0);

         for(int i = 0; i < G->GetN(); i++)
         {
            double X, Y, EX1, EX2, EY1, EY2;
            G->GetPoint(i, X, Y);
            EX1 = G->GetErrorXlow(i);
            EX2 = G->GetErrorXhigh(i);
            EY1 = G->GetErrorYlow(i);
            EY2 = G->GetErrorYhigh(i);

            if(Xs[iX].first < X && X < Xs[iX].second)
            {
               H.SetPoint(iX, X, Y);
               H.SetPointEXlow(iX, EX1);
               H.SetPointEXhigh(iX, EX2);
               H.SetPointEYlow(iX, EY1);
               H.SetPointEYhigh(iX, EY2);
            }
         }
      }
   }
   else
   {
      TH1D *Histogram = (TH1D *)File.Get(HistogramName.c_str());

      for(int iX = 0; iX < 5; iX++)
      {
         H.SetPoint(iX, (Xs[iX].first + Xs[iX].second) / 2, 0);

         for(int i = 1; i <= Histogram->GetNbinsX(); i++)
         {
            double X = Histogram->GetBinCenter(i);
            double DX = Histogram->GetXaxis()->GetBinUpEdge(i) - X;
            double Y = Histogram->GetBinContent(i);
            double DY = Histogram->GetBinError(i);
            
            if(Xs[iX].first < X && X < Xs[iX].second)
            {
               H.SetPoint(iX, X, Y);
               H.SetPointEXlow(iX, DX * 0.8);
               H.SetPointEXhigh(iX, DX * 0.8);
               H.SetPointEYlow(iX, DY);
               H.SetPointEYhigh(iX, DY);
            }
         }
      }
   }

   File.Close();
}
