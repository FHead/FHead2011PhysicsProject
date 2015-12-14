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
double Source(double r, double Sigma);
SimulationResult Simulate(double u, double w, double Step, double Mass2, double c1, double c2, double c, double Sigma, bool Print = false);

int main()
{
   double Step = 3e-10;
   double Mass2 = 401279.64;
   double c1 = 482.824975;
   double c2 = 0.12909808976;
   // double c = 786508.09;   // top
   double c = 453.028663181;   // bottom

   double Sigmas[] = {1e-3, 1e-4, 1e-5, 1e-6, 1e-7};

   for(int i = 0; i < 5; i++)
   {
      double umin = 1, umax = 10;
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
      while((umax - umin) / (umax + umin) > 1e-7)
      {
         double umiddle = (umax + umin) / 2;
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

double Source(double r, double Sigma)
{
   return -exp(-r * r / 2 / Sigma / Sigma) / sqrt(2 * PI) / Sigma;
}

SimulationResult Simulate(double u, double w, double Step, double Mass2, double c1, double c2, double c, double Sigma, bool Print)
{
   cout << "Trying with initial value = " << setprecision(20) << u << "..." << endl;

   for(long long i = 0; i < 10000000000; i++)
   {
      double r = i * Step;
      double dudr = w;
      double dwdr = Mass2 * u - 2 * w / r + Source(r, Sigma) * c;

      if(i == 0)
         dwdr = Mass2 * u + Source(r, Sigma) * c;

      double proposal_r = (i + 1) * Step;
      double proposal_u = u + dudr * Step;
      double proposal_w = w + dwdr * Step;

      double proposal_dudr = proposal_w;
      double proposal_dwdr = Mass2 * proposal_u - 2 * proposal_w / proposal_r + Source(proposal_r, Sigma) * c;
      
      double average_dudr = (dudr + proposal_dudr) / 2;
      double average_dwdr = (dwdr + proposal_dwdr) / 2;

      u = u + average_dudr * Step;
      w = w + average_dwdr * Step;

      if(i > 10000 && w > 0)
      {
         cout << "   Result is (+)" << endl;
         return BendOver;
      }
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


