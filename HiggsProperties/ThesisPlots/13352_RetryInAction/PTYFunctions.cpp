#include <cmath>
#include <iostream>
using namespace std;

#include "PTYFunctions.h"

double ToyYDensity(double y)
{
   // This was eta...
   // return exp(-(y - 2.6) * (y - 2.6) / (2 * 1.5 * 1.5)) + exp(-(y + 2.6) * (y + 2.6) / (2 * 1.5 * 1.5));

   if(y > 3.75 || y < -3.75)
      return 0;

   return (1.19005e+03 + -2.08029e+02 * y * y + 1.15469e+01 * y * y * y * y + -1.96945e-01 * y * y * y * y * y * y) / 1400;
}

double ToyPTDensity(double pt)
{
   double Value = 0;

   if(pt < 10)
      Value = (-3.38 + pt * 117.642 - pt * pt * 7.454) * 10 / 4276.4 * 4700.68 / 5200;
   else if(pt > 0)
      Value = (6833 * exp(-0.0385 * pt) + 57.226 * exp(-0.0112 * pt)) / 5200;

   if(Value < 0)
      Value = 0;

   return Value;
}

double ToyPTYDensity(double pt, double y, double s)
{
   return ToyYDensity(y) * ToyPTDensity(pt);
}

double MadgraphLogXDensity_Roberto12261(double z)
{
   if(z < -8.56898)
      return 0;
   if(z > -0.0941777)
      return 0;

   return 1.0655962110268478*cos(2.15548994605695e-9*(4.20911628102816 + z)) + 
      0.2377319445382884*pow(4.20911628102816 + z,2)*
      cos(0.8248839993118261*(4.20911628102816 + z)) - 
      2.9473197002822475*cos(0.8864492379673475*(4.20911628102816 + z)) + 
      2.0149947221926205*cos(1.175868221499112*(4.20911628102816 + z));

   /*
   x = x + 4.20912;
   return 0.9918607318361604*(1.0655962110268478*cos(2.15548994605695e-9*x) + 
      0.2377319445382884*x*x*cos(0.8248839993118261*x) - 
      2.9473197002822475*cos(0.8864492379673475*x) + 2.0149947221926205*cos(1.175868221499112*x));
   */
}

double MadgraphTotalDensity_Roberto12261(double pt, double y, double s)
{
   double SMACHINE = 8000 * 8000;

   if(pt > 1e-3)
      return 0;

   double Product = s / SMACHINE;
   double Ratio = exp(2 * y);

   double x1 = sqrt(Product * Ratio);
   double x2 = sqrt(Product / Ratio);

   double Density = MadgraphLogXDensity_Roberto12261(log(x1)) * MadgraphLogXDensity_Roberto12261(log(x2)) / s;

   return Density;
}

double GetPTYDensity(double pt, double y, double s)
{
#ifdef PTY_USE_TOY
   return ToyPTYDensity(pt, y);
#elif defined PTY_USE_MADGRAPH_ROBERTO12261
   return MadgraphTotalDensity_Roberto12261(pt, y, s);
#else
   return ToyPTYDensity(pt, y);
#endif
}






