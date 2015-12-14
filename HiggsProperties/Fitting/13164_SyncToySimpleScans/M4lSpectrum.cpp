#include <cmath>
using namespace std;

double GetZX8TeV2e2muSpectrum(double s)
{
   double P0 = -0.427373;
   double P1 = 0.00662414;
   double P2 = -2.30331e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX8TeV2mu2eSpectrum(double s)
{
   double P0 = -0.897482;
   double P1 = 0.0131309;
   double P2 = -4.49537e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX8TeV4eSpectrum(double s)
{
   double P0 = -1.13314;
   double P1 = 0.0169006;
   double P2 = -5.99977e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX8TeV4muSpectrum(double s)
{
   double P0 = -0.386375;
   double P1 = 0.00610286;
   double P2 = -2.14907e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetggZZ8TeV2e2muSpectrum(double s)
{
   double P0 = -0.408567;
   double P1 = 0.00666796;
   double P2 = -2.45833e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetggZZ8TeV2mu2eSpectrum(double s)
{
   double P0 = -0.11745;
   double P1 = 0.00169595;
   double P2 = -3.48382e-6;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetggZZ8TeV4eSpectrum(double s)
{
   double P0 = -0.221981;
   double P1 = 0.00329074;
   double P2 = -9.53908e-6;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetggZZ8TeV4muSpectrum(double s)
{
   double P0 = -0.255638;
   double P1 = 0.00429343;
   double P2 = -1.5394e-5;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX7TeV2e2muSpectrum(double s)
{
   double P0 = -0.578073;
   double P1 = 0.00897481;
   double P2 = -3.15378e-05;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX7TeV2mu2eSpectrum(double s)
{
   double P0 = -1.16077;
   double P1 = 0.0170693;
   double P2 = -5.89468e-05;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX7TeV4eSpectrum(double s)
{
   double P0 = -1.03745;
   double P1 = 0.0150399;
   double P2 = -5.06205e-05;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetZX7TeV4muSpectrum(double s)
{
   double P0 = -0.503048;
   double P1 = 0.00796494;
   double P2 = -2.8267e-05;
   double Normalization = 15 * P0 + 1837.5 * P1 + 225375 * P2;

   return (P0 + P1 * sqrt(s) + P2 * s) / sqrt(s) / Normalization / 2;
}

double GetggZZ7TeV2e2muSpectrum(double s)
{
   return 0;
}

double GetggZZ7TeV2mu2eSpectrum(double s)
{
   return 0;
}

double GetggZZ7TeV4eSpectrum(double s)
{
   return 0;
}

double GetggZZ7TeV4muSpectrum(double s)
{
   return 0;
}

