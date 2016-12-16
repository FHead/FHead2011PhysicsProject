#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]);
double BinomialRange(int x, int N);
double LogBinomial(int x, int N, double r);
double IntBinomial(int x, int N, double r);
double JntBinomial(int x, int N, double r);
double LogFactorial(int N);

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " x N" << endl;
      return -1;
   }

   int x = atoi(argv[1]);
   int N = atoi(argv[2]);

   cout << BinomialRange(x, N) << endl;

   return 0;
}

double BinomialRange(int x, int N)
{
   double Max = JntBinomial(x, N, 1);

   double L = 0, R = 1;
   while(R - L > 1e-10)
   {
      double C = (L + R) / 2;
      double I = JntBinomial(x, N, C);

      if(I < 0.9 * Max)
         L = C;
      else
         R = C;
   }

   return (L + R) / 2;
}

double LogBinomial(int x, int N, double r)
{
   double Result = 1;

   for(int i = 1; i <= N; i++)
      Result = Result - log(i);
   for(int i = 1; i <= x; i++)
      Result = Result + log(i);
   for(int i = x + 1; i <= N; i++)
      Result = Result + log(N-i+1);

   Result = Result + x * log(r);
   Result = Result + (N - x) * log(1 - r);

   return Result;
}

double IntBinomial(int x, int N, double r)
{
   // This calculates \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;
   if(x == 0)
      return (1 - pow(1 - r, N + 1)) / (N + 1);
   
   return (IntBinomial(x - 1, N ,r) * x - pow(r, x) * pow(1 - r, N - x + 1)) / (N - x + 1);
}

double JntBinomial(int x, int N, double r)
{
   // This calculates C(N,x) * \int r^x (1-r)^(N-x) dr using a recursion relationship

   if(r == 0)
      return 0;

   if(x == 0)
      return (1 - pow(1 - r, N + 1)) / (N + 1);

   double LogExtraTerm = x * log(r) + (N - x + 1) * log(1 - r);
   LogExtraTerm = LogExtraTerm + LogFactorial(N);
   LogExtraTerm = LogExtraTerm - LogFactorial(x);
   LogExtraTerm = LogExtraTerm - LogFactorial(N - x + 1);

   if(r == 1)   // there is no extra term when r = 1
      return JntBinomial(x - 1, N, r);

   return JntBinomial(x - 1, N, r) - exp(LogExtraTerm);
}

double LogFactorial(int N)
{
   static double *Result = NULL;
   
   if(Result == NULL)
   {
      Result = new double[10000000];
      for(int i = 0; i < 10000000; i++)
         Result[i] = 0;
   }

   if(N == 0)   // log(0) = 0
      return 0;
   if(N == 1)   // log(1) = 0
      return 0;

   if(Result[N] == 0)
   {
      int n = N;
      while(Result[n] == 0 && n > 1)
         n = n - 1;
      for(int i = n + 1; i <= N; i++)
         Result[i] = Result[i-1] + log(i);
   }

   return Result[N];
}


