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

int main(int argc, char *argv[]);
void GetHistogram(string FileName, TH1D &H, int R, bool Sys);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string FileName = CL.Get("Input", "SpectraRatio_Smooth_RedStat.root");

   string Rs[] = {"0.2", "0.3", "0.4", "0.6", "0.8"};
   int PTBinCount = 7;
   double PTs[] = {200, 250, 300, 350, 400, 500, 620, 1000};

   // index = radius from 0.2 to 0.8
   vector<TH1D *> H(5), HSys(5);
   for(int iR = 0; iR < 5; iR++)
   {
      H[iR] = new TH1D(Form("H%d", iR), "", 7, PTs);
      HSys[iR] = new TH1D(Form("HSys%d", iR), "", 7, PTs);

      GetHistogram(FileName, *H[iR], iR, false);
      GetHistogram(FileName, *HSys[iR], iR, true);
   }

   ofstream out("Table6.yaml");
   
   out << "independent_variables:" << endl;
   out << "- header: {name: PT, units: GEV}" << endl;
   out << "  values:" << endl;
   for(int iX = 0; iX < PTBinCount; iX++)
      out << "  - {low: " << PTs[iX] << ", high: " << PTs[iX+1] << "}" << endl;
      
   out << "dependent_variables:" << endl;   

   for(int iR = 0; iR < 5; iR++)
   {
      out << "- header: {name: (d sigma^R / d PT) / (d sigma^(R=1.0) / d PT)}" << endl;
      out << "  qualifiers:" << endl;
      out << "  - {name: ABS(ETA), value: 0.0-2.0}" << endl;
      out << "  - {name: RE, value: P P --> JET X}" << endl;
      out << "  - {name: SQRT(S), units: GeV, value: '5020'}" << endl;
      out << "  - {name: R, value: " << Rs[iR] << "}" << endl;
      out << "  values:" << endl;

      for(int iPT = 1; iPT <= PTBinCount; iPT++)
      {
         double Y = H[iR]->GetBinContent(iPT);
         double EY = H[iR]->GetBinError(iPT);
         double SY = HSys[iR]->GetBinError(iPT);

         int D = FindFirstSignificantDigit(EY);
         D = max(D, FindFirstSignificantDigit(SY));
         D = D - 1;

         out << "  - value: " << fixed << setprecision(CountDigitBelowPoint(D)) << Y << endl;
         out << "    errors:" << endl;
         out << "    - {label: stat, asymerror: {minus: " << -EY << ", plus: " << EY << "}}" << endl;
         out << "    - {label: sys, asymerror: {minus: " << -SY << ", plus: " << SY << "}}" << endl;
      }
   }

   out.close();

   return 0;
}

void GetHistogram(string FileName, TH1D &H, int R, bool Sys)
{
   TFile File("SpectraRatio_Smooth_RedStat.root");

   int Rs[] = {2, 3, 4, 6, 8};
   TH1D *Histogram = (TH1D *)File.Get(Form("ak%dPFJetAnalyzer_%d", Rs[R], Sys ? 2 : 1));

   for(int i = 1; i <= Histogram->GetNbinsX(); i++)
   {
      H.SetBinContent(i, Histogram->GetBinContent(i));
      H.SetBinError(i, Histogram->GetBinError(i));
   }

   File.Close();
}

