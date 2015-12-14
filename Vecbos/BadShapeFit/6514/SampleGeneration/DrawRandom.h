#include <cmath>
#include <cstdlib>
using namespace std;

double DrawRandom();
double DrawRandom(double max);
double DrawRandom(double min, double max);
double DrawSine(double min, double max);
double DrawLorentzian(double center, double gamma);
double DrawGaussian(double center, double sigma);
double DrawGaussian(double sigma);
double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar);
double DrawExponential(double exponent, double left, double right);
double DrawPoisson(double mean);

double DrawRandom()
{
   return double(rand() % 100000) / 100000;
}

double DrawRandom(double max)
{
   return max * DrawRandom();
}

double DrawRandom(double min, double max)
{
   return min + (max - min) * DrawRandom();
}

double DrawSine(double min, double max)
{
   bool OK = false;
   double answer = 0;

   while(OK == false)
   {
      answer = DrawRandom(min, max);
      double check = DrawRandom();

      if(check < sin(answer))
         OK = true;
   }

   return answer;
}

double DrawLorentzian(double center, double gamma)
{
   if(gamma <= 0)
      return center;

   bool OK = false;
   double displacement = 0;

   double DistributionMax = 4 / gamma / gamma;

   // functional form:
   //    const / (dx^2 + (gamma^2 / 4))
   //    const is (gamma / 2 / PI), for reference

   while(OK == false)
   {
      displacement = DrawRandom(-gamma * 20, gamma * 20);
      double check = DrawRandom(DistributionMax);

      if(check < 1 / (displacement * displacement + gamma * gamma / 4))
         OK = true;
   }

   return center + displacement;
}

double DrawGaussian(double center, double sigma)
{
   return center + DrawGaussian(sigma);
}

double DrawGaussian(double sigma)
{
   if(sigma <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   // form: exp(-x^2/(2 sigma^2))
   while(OK == false)
   {
      value = DrawRandom(-sigma * 5, sigma * 5);
      double check = DrawRandom();

      if(check < exp(-value * value / 2 / sigma / sigma))
         OK = true;
   }

   return value;
}

double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar)
{
   if(sigmal <= 0 || sigmar <= 0 || alphal <= 0 || alphar <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   while(OK == false)
   {
      value = DrawRandom(-sigmal * 40, sigmar * 40);
      double check = DrawRandom();

      double functionvalue = 0;
      if(value > 0)
         functionvalue = exp(-value * value / (2 * sigmar * sigmar + alphar * alphar * value * value));
      else
         functionvalue = exp(-value * value / (2 * sigmal * sigmal + alphal * alphal * value * value));

      if(check < functionvalue)
         OK = true;
   }

   return value + center;
}

double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar, double left, double right)
{
   if(sigmal <= 0 || sigmar <= 0 || alphal <= 0 || alphar <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   while(OK == false)
   {
      value = DrawRandom(left - center, right - center);
      double check = DrawRandom();

      double functionvalue = 0;
      if(value > 0)
         functionvalue = exp(-value * value / (2 * sigmar * sigmar + alphar * alphar * value * value));
      else
         functionvalue = exp(-value * value / (2 * sigmal * sigmal + alphal * alphal * value * value));

      if(check < functionvalue)
         OK = true;
   }

   return value + center;
}

double DrawExponential(double exponent, double left, double right)
{
   if(exponent > 0)
   {
      double result = DrawExponential(-exponent, left, right);
      result = left + right - result;
      return result;
   }

   if(right < left)
      swap(left, right);

   double value = 0;
   bool OK = false;

   while(OK == false)
   {
      value = DrawRandom(right - left);
      double check = DrawRandom();

      if(check < exp(-value * exponent))
         OK = true;
   }

   return value + left;
}

double DrawPoisson(double mean)
{
   if(mean <= 0)
      return 0;

   int value = 0;
   bool OK = false;

   while(OK == false)
   {
      value = (int)DrawRandom(mean * 1.5 + 10);
      double check = DrawRandom();

      double functionvalue = 1;
      for(int i = 0; i < value; i++)
         functionvalue = functionvalue * mean / (value - i);
      functionvalue = functionvalue * exp(-mean);

      if(check < functionvalue)
         OK = true;
   }

   return value;
}


