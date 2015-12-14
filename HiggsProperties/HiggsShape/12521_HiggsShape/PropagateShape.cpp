#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
double Source(double r);

int main()
{
   double u = 153.49350384;   // 83-85
   double w = 0;
   double Step = 1e-10;
   double Mass2 = 401279.64;
   double c1 = 482.824975;
   double c2 = 0.12909808976;
   double c = 786508.09;   // top

   for(long long i = 0; i < 10000000000; i++)
   {
      double r = i * Step;
      double dudr = w;
      double dwdr = Mass2 * u - 2 * w / r + Source(r) * c;

      if(i == 0)
         dwdr = Mass2 * u + Source(r) * c;

      double proposal_r = (i + 1) * Step;
      double proposal_u = u + dudr * Step;
      double proposal_w = w + dwdr * Step;

      double proposal_dudr = proposal_w;
      double proposal_dwdr = Mass2 * proposal_u - 2 * proposal_w / proposal_r + Source(proposal_r) * c;
      
      double average_dudr = (dudr + proposal_dudr) / 2;
      double average_dwdr = (dwdr + proposal_dwdr) / 2;

      u = u + average_dudr * Step;
      w = w + average_dwdr * Step;

      if(i % 100000 == 0)
         cout << (i + 1) * Step << " " << u << " " << w
            << " " << dudr << " " << dwdr << endl;
   }

   return 0;
}

double Source(double r)
{
   double Sigma = 1e-3;

   return -exp(-r * r / 2 / Sigma / Sigma) / sqrt(2 * PI) / Sigma;
}



