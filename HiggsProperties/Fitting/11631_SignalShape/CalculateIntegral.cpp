#include <iostream>
#include <vector>
using namespace std;

#include "RooRealVar.h"
#include "RooBreitWigner.h"
#include "RooDoubleSidedCBShape.hh"
#include "RooFFTConvPdf.h"
using namespace std;

#include "TGraph.h"

#include "PlotHelper2.h"

struct Polynomial;
int main();
double GetIntegral(double Mass, Polynomial M0, Polynomial Sigma, Polynomial AlphaL, Polynomial AlphaR,
   Polynomial NL, Polynomial NR, const vector<double> &Masses, const vector<double> &Width,
   const vector<double> &BrGG, const vector<double> &BrZZ, PsFileHelper &PsFile);
double GetSignalShape(double m, double mh, double m0, double sigma, double alphal, double alphar,
   double nl, double nr, const vector<double> &Masses, const vector<double> &Width,
   const vector<double> &BrGG, const vector<double> &BrZZ, PsFileHelper &PsFile);
double GetModifiedBW(double m, double mh, const vector<double> &Masses, const vector<double> &Width,
   const vector<double> &BrGG, const vector<double> &BrZZ);
double GetDoubleSidedCB(double m, double m0, double sigma, double alphal, double alphar, double nl, double nr);
vector<double> ReadFile(string FileName, int Column);
double GetValue(double x, const vector<double> &X, const vector<double> &Y);

struct Polynomial
{
   double P0, P1, P2, P3, P4;
};

int main()
{
   Polynomial M0, Sigma, AlphaL, AlphaR, NL, NR;

   ifstream in("FitParameters.txt");

   in >> M0.P0 >> M0.P1 >> M0.P2 >> M0.P3 >> M0.P4;
   in >> Sigma.P0 >> Sigma.P1 >> Sigma.P2 >> Sigma.P3 >> Sigma.P4;
   in >> AlphaL.P0 >> AlphaL.P1 >> AlphaL.P2 >> AlphaL.P3 >> AlphaL.P4;
   in >> AlphaR.P0 >> AlphaR.P1 >> AlphaR.P2 >> AlphaR.P3 >> AlphaR.P4;
   in >> NL.P0 >> NL.P1 >> NL.P2 >> NL.P3 >> NL.P4;
   in >> NR.P0 >> NR.P1 >> NR.P2 >> NR.P3 >> NR.P4;

   in.close();

   vector<double> Mass = ReadFile("HiggsWidths.txt", 1);
   vector<double> Width = ReadFile("HiggsWidths.txt", 2);
   vector<double> BrGG = ReadFile("HiggsWidths.txt", 3);
   vector<double> BrZZ = ReadFile("HiggsWidths.txt", 4);

   PsFileHelper PsFile("IntegralCheck.ps");
   PsFile.AddTextPage("Check integrals");

   for(double M = 100; M <= 200; M = M + 0.1)
   {
      double Integral = GetIntegral(M, M0, Sigma, AlphaL, AlphaR, NL, NR, Mass, Width, BrGG, BrZZ, PsFile);
      cout << "I " << M << " " << Integral << endl;
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double GetIntegral(double Mass, Polynomial M0, Polynomial Sigma, Polynomial AlphaL, Polynomial AlphaR,
   Polynomial NL, Polynomial NR, const vector<double> &Masses, const vector<double> &Widths,
   const vector<double> &BrGG, const vector<double> &BrZZ, PsFileHelper &PsFile)
{
   double Mass1 = 1 * Mass;
   double Mass2 = Mass1 * Mass;
   double Mass3 = Mass2 * Mass;
   double Mass4 = Mass3 * Mass;

   double m0 = M0.P0 + M0.P1 * Mass1 + M0.P2 * Mass2 + M0.P3 * Mass3 + M0.P4 * Mass4;
   double sigma = Sigma.P0 + Sigma.P1 * Mass1 + Sigma.P2 * Mass2 + Sigma.P3 * Mass3 + Sigma.P4 * Mass4;
   double alphal = AlphaL.P0 + AlphaL.P1 * Mass1 + AlphaL.P2 * Mass2 + AlphaL.P3 * Mass3 + AlphaL.P4 * Mass4;
   double alphar = AlphaR.P0 + AlphaR.P1 * Mass1 + AlphaR.P2 * Mass2 + AlphaR.P3 * Mass3 + AlphaR.P4 * Mass4;
   double nl = NL.P0 + NL.P1 * Mass1 + NL.P2 * Mass2 + NL.P3 * Mass3 + NL.P4 * Mass4;
   double nr = NR.P0 + NR.P1 * Mass1 + NR.P2 * Mass2 + NR.P3 * Mass3 + NR.P4 * Mass4;

   cout << "P " << Mass << " " << m0 << " " << sigma << " "
      << alphal << " " << alphar << " " << nl << " " << nr << endl;

   bool DoGraph = false;
   if(Mass - (int)(Mass + 0.0001) < 1e-5)
      DoGraph = true;

   TGraph G;
   G.SetNameTitle(Form("G%.1f", Mass), Form("Mass = %f", Mass));

   int index = 0;
   double Integral = 0;
   for(double M = 100; M <= 200; M = M + 0.1)
   {
      double Value = GetSignalShape(M, Mass, m0, sigma, alphal, alphar, nl, nr, Masses, Widths, BrGG, BrZZ, PsFile);
      Integral = Integral + Value * 1;

      if(DoGraph == true)
         G.SetPoint(index, M, Value);
      index = index + 1;
   }

   if(DoGraph == true)
   {
      PsFile.AddPlot(G, "apl", false);
      PsFile.AddPlot(G, "apl", true);
   }

   return Integral;
}

double GetSignalShape(double m, double mh, double m0, double sigma, double alphal, double alphar,
   double nl, double nr, const vector<double> &Masses, const vector<double> &Width,
   const vector<double> &BrGG, const vector<double> &BrZZ, PsFileHelper &PsFile)
{
   double StepSize = mh / 1000;

   // TGraph G;
   // G.SetNameTitle("SignalShape",
   //    Form("%f, %f, %f, %f, %f, %f, %f, %f", m, mh, m0, sigma, alphal, alphar, nl, nr));
   // int GraphIndex = 0;

   double Total = 0;
   for(double M = mh * 0; M < mh * 2; M = M + StepSize)
   {
      double Contribution = 0;
      Contribution = Contribution + GetModifiedBW(M, mh, Masses, Width, BrGG, BrZZ)
         * GetDoubleSidedCB(m - M, m0, sigma, alphal, alphar, nl, nr);
      Contribution = Contribution + GetModifiedBW(M + StepSize / 2, mh, Masses, Width, BrGG, BrZZ)
         * GetDoubleSidedCB(m - M - StepSize / 2, m0, sigma, alphal, alphar, nl, nr) * 4;
      Contribution = Contribution + GetModifiedBW(M + StepSize, mh, Masses, Width, BrGG, BrZZ)
         * GetDoubleSidedCB(m - M - StepSize, m0, sigma, alphal, alphar, nl, nr);
      
      Total = Total + Contribution;

      // G.SetPoint(GraphIndex, M, Contribution);
      // GraphIndex = GraphIndex + 1;
   }
   Total = Total * StepSize;

   // PsFile.AddPlot(G, "apl", false);
   // PsFile.AddPlot(G, "apl", true);

   return Total;
}

double GetModifiedBW(double m, double mh, const vector<double> &Masses, const vector<double> &Width,
   const vector<double> &BrGG, const vector<double> &BrZZ)
{
   double sigma = GetValue(m, Masses, Width);
   double brzz = GetValue(m, Masses, BrZZ);
   double brgg = GetValue(m, Masses, BrGG);

   return brzz * brgg * sigma * sigma * m / ((m * m - mh * mh) * (m * m - mh * mh) + mh * mh * sigma * sigma);
}

double GetDoubleSidedCB(double m, double m0, double sigma, double alphal, double alphar, double nl, double nr)
{
   if(alphal < 0)   alphal = -alphal;
   if(alphar < 0)   alphar = -alphar;

   double delta = (m - m0) / sigma;

   if(delta < -alphal)
   {
      double a = pow(nl / alphal, nl) * exp(-0.5 * alphal * alphal);
      double b = nl / alphal - alphal;
      return a / pow(b - delta, nl);
   }
   else if(delta > alphar)
   {
      double a = pow(nr / alphar, nr) * exp(-0.5 * alphar * alphar);
      double b = nr / alphar - alphar;
      return a / pow(b + delta, nr);
   }
   else
      return exp(-0.5 * delta * delta);

   return 0;
}

double GetHiggsWidth(double Mass, const vector<pair<double, double> > &Widths)
{
   // Assume the width array is sorted by Mass

   if(Mass < Widths[0].first)
      return Widths[0].second;
   if(Mass >= Widths[Widths.size()-1].first)
      return Widths[Widths.size()-1].second;

   for(int i = 0; i < Widths.size() - 1; i++)
   {
      if(Mass < Widths[i].first || Mass >= Widths[i+1].first)
         continue;

      double x1 = Widths[i].first;
      double x2 = Widths[i+1].first;
      double y1 = Widths[i].second;
      double y2 = Widths[i+1].second;

      return y1 * exp((Mass - x1) / (x2 - x1) * (log(y2) - log(y1)));
   }

   return 0;
}

vector<double> ReadFile(string FileName, int Col)
{
   vector<double> Result;

   ifstream in(FileName.c_str());

   while(in)
   {
      double Temp = -999;

      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      stringstream str(ch);

      for(int i = 1; i <= Col; i++)
      {
         double temp = -999;
         str >> temp;

         if(i == Col)
            Temp = temp;
      }

      if(Temp <= 0)
         continue;

      Result.push_back(Temp);
   }

   in.close();

   return Result;
}

double GetValue(double x, const vector<double> &X, const vector<double> &Y)
{
   if(X.size() == 0 || Y.size() == 0)
   {
      cerr << "[GetValue] Error!  Sizes of arrays are zero!" << endl;
      cerr << "[GetValue] Exiting returning 0..." << endl;
      return 0;
   }
   if(X.size() != Y.size())
   {
      cerr << "[GetValue] Error!  Sizes of arrays are different!" << endl;
      cerr << "[GetValue] Exiting returning 0..." << endl;
      return 0;
   }

   if(x < X[0])
      return Y[0];
   if(x >= X[X.size()-1])
      return Y[Y.size()-1];

   for(int i = 0; i < (int)X.size() - 1; i++)
   {
      if(x < X[i] || x >= X[i+1])
         continue;

      double x1 = X[i];
      double x2 = X[i+1];
      double y1 = Y[i];
      double y2 = Y[i+1];

      return y1 * exp((x - x1) / (x2 - x1) * (log(y2) - log(y1)));
   }
   return 0;
}
//---------------------------------------------------------------------------






