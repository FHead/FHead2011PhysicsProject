#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846264338327950288479716939937510

enum SimulationResult
{
   BendOver,
   Good,
   Negative
};

int main();
long double Source(long double r, long double Sigma);
SimulationResult Simulate(long double u, long double w, long double Step, long double Mass2, long double c1, long double c2, long double c, long double Sigma, bool Print = false);

int main()
{
   cout << sizeof(float) << endl;
   cout << sizeof(double) << endl;
   cout << sizeof(long double) << endl;

   long double Step = 1e-12;
   long double Mass2 = 401279.64;
   long double c1 = 482.824975;
   long double c2 = 0.12909808976;
   // long double c1 = 0;
   // long double c2 = 0;
   long double c = sqrt(786508.09);   // top
   // long double c = sqrt(453.028663181);   // bottom
   // long double c = 6.537;   // charm
   // long double c = 15 * sqrt(453.028663181);   // 15x bottom

   long double Sigmas[] = {1e-3, 1e-4, 1e-5, 1e-6, 1e-7};

   for(int i = 0; i < 4; i++)
   {
      long double umin = 1, umax = 10;
      while(Simulate(umin, 0, Step, Mass2, c1, c2, c, Sigmas[i]) == BendOver)
      {
         umax = umin;
         umin = umin / 10;
      }
      while(Simulate(umax, 0, Step, Mass2, c1, c2, c, Sigmas[i]) == Negative)
      {
         umin = umax;
         umax = umax * 10;
      }
      while((umax - umin) / (umax + umin) > 1e-15)
      {
         long double umiddle = (umax + umin) / 2;
         SimulationResult Result = Simulate(umiddle, 0, Step, Mass2, c1, c2, c, Sigmas[i]);
         if(Result == BendOver)
            umax = umiddle;
         if(Result == Negative)
            umin = umiddle;
         if(Result == Good)
            break;
      }

      Simulate((umax + umin) / 2, 0, Step, Mass2, c1, c2, c, Sigmas[i], true);

      cout << "Best initial value for " << Sigmas[i] << " is " << (umax + umin) / 2 << endl;
   }

   return 0;
}

long double Source(long double r, long double Sigma)
{
   return -exp(-r * r / 2 / Sigma / Sigma) / sqrt(2 * PI) / Sigma / Sigma / Sigma;
}

SimulationResult Simulate(long double u, long double w, long double Step, long double Mass2, long double c1, long double c2, long double c, long double Sigma, bool Print)
{
   cout << "Trying with initial value = " << setprecision(20) << u << "..." << endl;

   for(long long i = 0; i < 10000000000; i++)
   {
      long double r = i * Step;
      long double dudr = w;
      long double dwdr = Mass2 * u - 2 * w / r + Source(r, Sigma) * c + c1 * u * u + c2 * u * u * u;

      if(i == 0)
         dwdr = Mass2 * u + Source(r, Sigma) * c;

      long double proposal_r = (i + 1) * Step;
      long double proposal_u = u + dudr * Step;
      long double proposal_w = w + dwdr * Step;

      long double proposal_dudr = proposal_w;
      long double proposal_dwdr = Mass2 * proposal_u - 2 * proposal_w / proposal_r + Source(proposal_r, Sigma) * c
         + c1 * proposal_u * proposal_u + c2 * proposal_u * proposal_u * proposal_u;
      
      long double average_dudr = (dudr + proposal_dudr) / 2;
      long double average_dwdr = (dwdr + proposal_dwdr) / 2;

      u = u + average_dudr * Step;
      w = w + average_dwdr * Step;

      if(u != u || w != w)
      {
         cout << "   Result is (+)" << endl;
         return BendOver;
      }
      if(i > 100 && w > 0)
      {
         cout << "   Result is (+)" << endl;
         return BendOver;
      }
      // if(i > 10000 && average_dwdr > 0)
      // {
      //    cout << "   Result is (+)" << endl;
      //    return BendOver;
      // }
      if(u < 0)
      {
         cout << "   Result is (-)" << endl;
         return Negative;
      }
      
      if(Print == true && (i % 100000) == 0)
         cout << "LOG " << Sigma << " " << (i + 1) * Step << " " << u << " " << w
            << " " << dudr << " " << dwdr << endl;
   }

   cout << "   Result is ( )" << endl;

   return Good;
}


