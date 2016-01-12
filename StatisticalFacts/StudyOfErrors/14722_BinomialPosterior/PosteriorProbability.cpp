#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define SIZE 250000

struct Range;
int main();
Range CalculateRange(int x, int N);
Range CalculateRange2(int x, int N);
pair<double, double> SearchRange(int x, int N, double TargetIntegral);
double LogBinomial(int x, int N, double p);
double CDF(int x, int N, double p);
double CDF1(int x, int N, double p);
double CDF2(int x, int N, double p);
double CDF3(int x, int N, double p);
double DrawRandom();

struct Range
{
   double MostProbable;
   double Median;
   double Min68, Max68;
   double Min95, Max95;
};

int main()
{
   ofstream out("Everything.txt");

   cerr << "Now running a big table of (x,N) where N <= 100" << endl;

   for(int N = 1; N <= 100; N++)
   {
      for(int x = 0; x <= N; x++)
      {
         Range Result = CalculateRange2(x, N);
         out << x << " " << N
            << " " << Result.Min68 << " " << Result.Max68
            << " " << Result.Min95 << " " << Result.Max95 << endl;
      }
   }

   cerr << "Now running an expedition of x = 0" << endl;

   // 0% expedition
   for(int N = 1; N <= 1000; N++)
   {
      Range Result = CalculateRange2(0, N);
      out << 0 << " " << N
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.01" << endl;

   // 1% expedition
   for(int x = 1; x <= 20; x++)
   {
      Range Result = CalculateRange2(x, x * 100);
      out << x << " " << x * 100
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.02" << endl;

   // 2% expedition
   for(int x = 1; x <= 50; x++)
   {
      Range Result = CalculateRange2(x, x * 50);
      out << x << " " << x * 50
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.05" << endl;

   // 5% expedition
   for(int x = 1; x <= 1000; x++)
   {
      Range Result = CalculateRange2(x, x * 20);
      out << x << " " << x * 20
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.10" << endl;

   // 10% expedition
   for(int x = 1; x <= 1000; x++)
   {
      Range Result = CalculateRange2(x, x * 10);
      out << x << " " << x * 10
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.25" << endl;

   // 25% expedition
   for(int x = 1; x <= 1000; x++)
   {
      Range Result = CalculateRange2(x, x * 4);
      out << x << " " << x * 4
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   cerr << "Now running an expedition of x/N = 0.50" << endl;

   // 50% expedition
   for(int x = 1; x <= 1000; x++)
   {
      Range Result = CalculateRange2(x, x * 2);
      out << x << " " << x * 2
         << " " << Result.Min68 << " " << Result.Max68
         << " " << Result.Min95 << " " << Result.Max95 << endl;
   }

   out.close();

   return 0;
}

Range CalculateRange(int x, int N)
{
   double Samples[SIZE] = {0};

   double Max = LogBinomial(x, N, (double)x / N);

   for(int i = 0; i < SIZE; i++)
   {
      bool Good = false;
      while(Good == false)
      {
         double p = DrawRandom();
         double Value = LogBinomial(x, N, p);

         if(DrawRandom() < exp(Value - Max))
         {
            Good = true;
            Samples[i] = p;
         }
      }

      // if(i % 50000 == 0)
      //    cout << Samples[i] << endl;
   }

   sort(Samples, Samples + 250000);

   Range Result;
   Result.MostProbable = x / N;
   Result.Median = Samples[(int)(SIZE*0.500)];
   Result.Min68 = Samples[(int)(SIZE*0.160)];
   Result.Max68 = Samples[(int)(SIZE*0.840)];
   Result.Min95 = Samples[(int)(SIZE*0.025)];
   Result.Max95 = Samples[(int)(SIZE*0.975)];

   return Result;
}

Range CalculateRange2(int x, int N)
{
   if(N > 1000)
   {
      Range Result;
      Result.MostProbable = (double)x / N;
      Result.Min68 = -1;
      Result.Max68 = -1;
      Result.Min95 = -1;
      Result.Max95 = -1;

      return Result;
   }

   double MostLikely = (double)x / N;

   pair<double, double> Range68 = SearchRange(x, N, 0.6827);
   pair<double, double> Range95 = SearchRange(x, N, 0.9545);

   Range Result;
   Result.MostProbable = MostLikely;
   Result.Min68 = Range68.first;
   Result.Max68 = Range68.second;
   Result.Min95 = Range95.first;
   Result.Max95 = Range95.second;

   return Result;
}

pair<double, double> SearchRange(int x, int N, double TargetIntegral)
{
   double MostLikely = (double)x / N;

   double RawIntegral = CDF(x, N, 1);
   double LogHeight = LogBinomial(x, N, MostLikely);

   double MaxHeight = LogHeight;
   double MinHeight = LogHeight - log(100000);

   double MaxIntegral = 0;
   double MinIntegral = 1;

   double TargetEpsilon = 0.0001;

   double Left = 0, Right = 1;

   while(fabs(MaxIntegral - MinIntegral) > TargetEpsilon)
   {
      double TestHeight = (MaxHeight + MinHeight) / 2;

      Left = 0, Right = 1;

      double Min = 0, Max = MostLikely;
      if(Min == Max)
         Left = Min;
      else
      {
         while(Max - Min > 0.000000001)
         {
            if(LogBinomial(x, N, (Min + Max) / 2) > TestHeight)
               Max = (Min + Max) / 2;
            else
               Min = (Min + Max) / 2;
         }
         Left = (Min + Max) / 2;
      }

      Min = MostLikely, Max = 1;
      if(Min == Max)
         Right = Max;
      else
      {
         while(Max - Min > 0.000000001)
         {
            if(LogBinomial(x, N, (Min + Max) / 2) > TestHeight)
               Min = (Min + Max) / 2;
            else
               Max = (Min + Max) / 2;
         }
         Right = (Min + Max) / 2;
      }

      double TestIntegral = (CDF3(x, N, Right) - CDF3(x, N, Left)) / RawIntegral;

      // cout << Left << " " << Right << " " << CDF(x, N, Right) << " " << CDF(x, N, Left) << " " << CDF(x, N, 1) << endl;

      if(TestIntegral < TargetIntegral)
      {
         MaxHeight = TestHeight;
         MaxIntegral = TestIntegral;
      }
      else
      {
         MinHeight = TestHeight;
         MinIntegral = TestIntegral;
      }

      // cout << MaxHeight << " " << MinHeight << " " << MaxIntegral << " " << MinIntegral << endl;
   }

   pair<double, double> Result;
   Result.first = Left;
   Result.second = Right;
   return Result;
}

double LogBinomial(int x, int N, double p)
{
   double Answer = 0;

   for(int i = 1; i <= N; i++)
      Answer = Answer + log(i);
   for(int i = 1; i <= x; i++)
      Answer = Answer - log(i);
   for(int i = 1; i <= N - x; i++)
      Answer = Answer - log(i);

   if(x > 0)
      Answer = Answer + x * log(p);
   if(N != x)
      Answer = Answer + (N - x) * log(1 - p);

   return Answer;
}

double CDF(int x, int N, double p)
{
   return CDF3(x, N, p);

   if(p < 0.5)
      return CDF1(x, N, p);
   return CDF2(x, N, p); 
}

double CDF1(int x, int N, double p)
{
   int a = x;
   int b = N - x;

   double Term = 1;
   for(int i = 0; i < a + 1; i++)
      Term = Term * p;
   for(int i = 0; i < b; i++)
      Term = Term * (1 - p);
   Term = Term / (a + 1);

   double Sum = Term;
   for(int i = b - 1; i >= 1; i--)
   {
      Term = Term * p / (1 - p) * i / (a + 1 + (b - i));
      Sum = Sum + Term;
   }
   Term = Term * p / (1 - p) / (a + b + 1);
   Sum = Sum + Term;

   return Sum;
}

double CDF2(int x, int N, double p)
{
   int a = x;
   int b = N - x;

   double Sum = 1;
   for(int i = 0; i < a + b + 1; i++)
      Sum = Sum * p;
   Sum = Sum / (a + b);
   for(int i = 1; i <= b - 1; i++)
      Sum = Sum * (b - i) / (a + i);
   Sum = Sum / (a + b + 1);

   double Term = 1;
   for(int i = 0; i < a + b; i++)
      Term = Term * p;
   Term = Term * (1 - p);
   Term = Term / (a + b);
   for(int i = 1; i <= b - 1; i++)
      Term = Term * (b - i) / (a + i);

   Sum = Sum + Term;
   for(int i = 1; i <= b - 1; i++)
   {
      Term = Term * (1 - p) / p / i * (a + 1 + (b - i));
      Sum = Sum + Term;
   }

   return Sum;
}

double CDF3(int x, int N, double p)
{
   // placeholder for I(x,x)
   double I = 1;

   int a = x;
   int b = N - x;

   // initialize I to I(N-1,1)
   for(int i = 0; i < N; i++)
      I = I * p;
   I = I * (1 / ((double)N) - p / ((double)N + 1));

   // after each loop content, the value will be I(N-i,i)
   // I(N-i,i) = i/(N-i+1) I(N-i+1,i-1) + p^(N-i+1) (1-p)^i / (N-i+1)
   // in the end we get I(N-b,b) = I(x,N-x)
   for(int i = 2; i <= b; i++)
   {
      double NewI = I * i;

      NewI = NewI + pow(p, N - i + 1) * pow(1 - p, i);

      I = NewI / ((double)N + 1 - i);
   }

   return I;
}

double DrawRandom()
{
   // Get a random number from 0 to 1
   double x = rand() % 100;
   for(int i = 0; i < 20; i++)
      x = x / 100 + rand() % 100;
   return x / 100;
}






