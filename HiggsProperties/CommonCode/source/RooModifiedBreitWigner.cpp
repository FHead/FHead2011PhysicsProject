//---------------------------------------------------------------------------
#include "RooFit.h"

#include "Riostream.h"
#include <math.h>

#include "RooModifiedBreitWigner.hh"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
#include "TMath.h"

// ClassImp(RooModifiedBreitWigner);
//---------------------------------------------------------------------------
RooModifiedBreitWigner::RooModifiedBreitWigner(const char *name, const char *title,
      RooAbsReal& _m, RooAbsReal& _m0) :
   RooAbsPdf(name, title),
   m("m", "Dependent", this, _m),
   m0("m0", "M0", this, _m0)
{
}
//---------------------------------------------------------------------------
RooModifiedBreitWigner::RooModifiedBreitWigner(const RooModifiedBreitWigner& other, const char* name) :
   RooAbsPdf(other, name), m("m", this, other.m), m0("m0", this, other.m0)
{
   Mass = other.Mass;
   Width = other.Width;
   BrGG = other.BrGG;
   BrZZ = other.BrZZ;
}
//---------------------------------------------------------------------------
double RooModifiedBreitWigner::evaluate() const
{  
   double sigma_all = GetWidth(m);
   double sigma_gg = sigma_all * GetBrGG(m);
   double sigma_zz = sigma_all * GetBrZZ(m);
   double Lgg = Lgg_7(m);

   return sigma_gg * sigma_zz * m / ((m * m - m0 * m0) * (m * m - m0 * m0) + m * m * sigma_all * sigma_all) * Lgg;
}
//---------------------------------------------------------------------------
void RooModifiedBreitWigner::SetSpectra(std::vector<double> mass, std::vector<double> width,
   std::vector<double> brgg, std::vector<double> brzz)
{
   if(mass.size() != width.size() || mass.size() != brgg.size() || mass.size() != brzz.size())
   {
      std::cerr << "[RooModifiedBreitWigner][SetSpectra] Error!  Sizes of arrays don't match!" << std::endl;
      std::cerr << "[RooModifiedBreitWigner][SetSpectra] Exiting without setting anything..." << std::endl;
      return;
   }

   Mass = mass;
   Width = width;
   BrGG = brgg;
   BrZZ = brzz;

   std::cout << "[RooModifiedBreitWigner][SetSpectra] Info: array sizes = "
      << Mass.size() << " " << Width.size() << " " << BrGG.size() << " " << BrZZ.size() << std::endl;
}
//---------------------------------------------------------------------------
double RooModifiedBreitWigner::GetValue(double x, const std::vector<double> &X, const std::vector<double> &Y) const
{
   if(X.size() == 0 || Y.size() == 0)
   {
      std::cerr << "[RooModifiedBreitWigner][GetValue] Error!  Sizes of arrays are zero!" << std::endl;
      std::cerr << "[RooModifiedBreitWigner][GetValue] Exiting returning 0..." << std::endl;
      return 0;
   }
   if(X.size() != Y.size())
   {
      std::cerr << "[RooModifiedBreitWigner][GetValue] Error!  Sizes of arrays are different!" << std::endl;
      std::cerr << "[RooModifiedBreitWigner][GetValue] Exiting returning 0..." << std::endl;
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
double RooModifiedBreitWigner::GetWidth(double mass) const
{
   return GetValue(mass, Mass, Width);
}
//---------------------------------------------------------------------------
double RooModifiedBreitWigner::GetBrZZ(double mass) const
{
   return GetValue(mass, Mass, BrZZ);
}
//---------------------------------------------------------------------------
double RooModifiedBreitWigner::GetBrGG(double mass) const
{
   return GetValue(mass, Mass, BrGG);
}
//---------------------------------------------------------------------------
double RooModifiedBreitWigner::Lgg_7(double mHstar) const
{
   double u = log(1000 * (mHstar / 7000));
   double Z = (((((((((-6.4e-09 * u - 7e-09)*u - 7.15e-08)*u -5.5e-09)*u - 7.5e-08)*u - 1.6e-05)*u - 1e-05)* u - 5e-05)* u - 5.5e-04)*u -.33)*u*u-2*u;

   double zz = exp(Z);

   double lum = 1.2765346093e+10 * zz;

   return lum;
}
//---------------------------------------------------------------------------

