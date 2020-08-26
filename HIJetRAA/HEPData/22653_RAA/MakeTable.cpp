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

int main(int argc, char *argv[]);
void GetRAA(TH1D &H, string FileName, int R, int C, bool Sys = false);
void Rebin(TH1D &H1, TH1D &H2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string FileName = CL.Get("Input", "RAA_Smooth.root");

   // First index: type => C0, C1, C2, C3
   // Second index: radius => 0.2, 0.3, 0.4, 0.6, 0.8, 1.0
   double Bins[] = {200, 250, 300, 400, 500, 1000};
   vector<vector<TH1D *>> H(4), HSys(4);
   for(int iC = 0; iC < 4; iC++)
   {
      H[iC].resize(6);
      HSys[iC].resize(6);

      for(int iR = 0; iR < 6; iR++)
      {
         H[iC][iR]    = new TH1D(Form("H%d%d", iC, iR),    "", 5, Bins);
         HSys[iC][iR] = new TH1D(Form("HSys%d%d", iC, iR), "", 5, Bins);

         GetRAA(*H[iC][iR], FileName, iR, iC, false);
         GetRAA(*HSys[iC][iR], FileName, iR, iC, true);
      }
   }

   double TAA[] = {0.100719, 0.051233, 0.025341, 0.018646};
   double Lumi = 0.023;

   string Cs[] = {"0-10", "10-30", "30-50", "50-80"};
   string Rs[] = {"0.2", "0.3", "0.4", "0.6", "0.8", "1.0"};

   for(int iR = 0; iR < 6; iR++)
   {
      ofstream out(Form("Table7-%d.yaml", iR + 1));

      vector<pair<double, double>> Xs;
      for(int iC = 0; iC < 4; iC++)
      {
         for(int iP = 1; iP <= H[iC][iR]->GetNbinsX(); iP++)
         {
            double XL = H[iC][iR]->GetXaxis()->GetBinLowEdge(iP);
            double XH = H[iC][iR]->GetXaxis()->GetBinUpEdge(iP);
            double X = (XL + XH) / 2;

            bool Found = false;
            for(int iX = 0; iX < (int)Xs.size(); iX++)
               if(Xs[iX].first < X && Xs[iX].second > X)
                  Found = true;
            if(Found == false)
               Xs.push_back(pair<double, double>(XL, XH));
         }
      }
      sort(Xs.begin(), Xs.end());

      out << "independent_variables:" << endl;
      out << "- header: {name: PT, units: GEV}" << endl;
      out << "  values:" << endl;
      for(int iX = 0; iX < (int)Xs.size(); iX++)
         out << "  - {low: " << Xs[iX].first << ", high: " << Xs[iX].second << "}" << endl;

      out << "dependent_variables:" << endl;

      for(int iC = 0; iC < 4; iC++)
      {
         out << "- header: {name: RAA}" << endl;
         out << "  qualifiers:" << endl;
         out << "  - {name: ABS(ETA), value: 0.0-2.0}" << endl;
         out << "  - {name: RE, value: PB PB --> JET X, P P --> JET X}" << endl;
         out << "  - {name: SQRT(S)/NUCLEON, units: GeV, value: '5020'}" << endl;
         out << "  - {name: CENTRALITY, units: pct, value: " << Cs[iC] << "}" << endl;
         out << "  - {name: R, value: " << Rs[iR] << "}" << endl;
         out << "  values:" << endl;

         for(int iX = 0; iX < (int)Xs.size(); iX++)
         {
            bool Found = false;

            for(int iP = 1; iP <= H[iC][iR]->GetNbinsX(); iP++)
            {
               double X = H[iC][iR]->GetBinCenter(iP);
               double Y = H[iC][iR]->GetBinContent(iP);
               double EY = H[iC][iR]->GetBinError(iP);
               double SY = HSys[iC][iR]->GetBinError(iP);

               if(Xs[iX].first < X && X < Xs[iX].second && Y > 0.001)
                  Found = true;
               else
                  continue;

               double SysLumi = Lumi * Y;
               double SysTAA = TAA[iC] * Y;

               int D = FindFirstSignificantDigit(EY);
               D = max(D, FindFirstSignificantDigit(SY));
               D = max(D, FindFirstSignificantDigit(SysLumi));
               D = max(D, FindFirstSignificantDigit(SysTAA));
               D = D - 1;

               out << "  - value: " << fixed << setprecision(CountDigitBelowPoint(D)) << Y << endl;
               out << "    errors:" << endl;
               out << "    - {label: stat, asymerror: {minus: " << -EY << ", plus: " << EY << "}}" << endl;
               out << "    - {label: sys, asymerror: {minus: " << -SY << ", plus: " << SY << "}}" << endl;
               out << "    - {label: TAA, asymerror: {minus: " << -SysTAA << ", plus: " << SysTAA << "}}" << endl;
               out << "    - {label: lumi, asymerror: {minus: " << -SysLumi << ", plus: " << SysLumi << "}}" << endl;
            }

            if(Found == false)
               out << "  - value: '-'" << endl;
         }
      }

      out.close();
   }

   return 0;
}

void GetRAA(TH1D &H, string FileName, int R, int C, bool Sys)
{
   TFile File(FileName.c_str());

   string Rs[] = {"2", "3", "4", "6", "8", "10"};
   string Cs[] = {"0to10", "10to30", "30to50", "50to90"};

   string HistogramName = "";

   HistogramName = HistogramName + "akCs" + Rs[R] + "PU3PFFlowJetAnalyzer";
   HistogramName = HistogramName + "_Cent" + Cs[C];
   if(Sys == false)   HistogramName = HistogramName + "_1";
   else               HistogramName = HistogramName + "_2";

   TH1D *Histogram = (TH1D *)File.Get(HistogramName.c_str());
   Rebin(*Histogram, H);

   File.Close();
}

void Rebin(TH1D &H1, TH1D &H2)
{
   H2.Reset();

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V = H1.GetBinContent(i);
      double E = H1.GetBinError(i);

      int B = H2.FindBin(H1.GetBinCenter(i));

      V = V + H2.GetBinContent(B);
      E = sqrt(E * E + H2.GetBinError(B) * H2.GetBinError(B));

      H2.SetBinContent(B, V);
      H2.SetBinError(B, E);
   }
}

