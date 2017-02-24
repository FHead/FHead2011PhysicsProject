#include <map>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

#define NO_PRIOR 0
#define NORMAL_PRIOR 1
#define LOOSE_PRIOR 2

int main();
void Integrate(int Count, double *YT, double *GWW, double *NLL, int Prior);
void PickoutModels(int Count, double *YT, double *GWW, double *NLL);
double EvaluatePrior(double YT);
double EvaluatePriorLoose(double YT);

int main()
{
   int LastID = -1;
   int Count = 0;
   double YT[20000];
   double GWW[20000];
   double NLL[20000];

   char ch[1024] = "";
   
   while(cin)
   {
      ch[0] = '\0';
      cin.getline(ch, 1023, '\n');

      stringstream str(ch);

      string Identifier = "";
      str >> Identifier;
      if(Identifier != "HypTest")
         continue;

      double ID = -1, yt = 0, gww = 0, nll = -1;
      str >> ID >> yt >> gww >> nll;

      if(ID < 0 || nll < -1)   // must be some sort of error
         continue;

      if(LastID >= 0 && ID != LastID)
      {
         // output and reset variables
         
         cout << setprecision(20) << LastID;
         Integrate(Count, YT, GWW, NLL, NO_PRIOR);
         Integrate(Count, YT, GWW, NLL, NORMAL_PRIOR);
         Integrate(Count, YT, GWW, NLL, LOOSE_PRIOR);
         PickoutModels(Count, YT, GWW, NLL);
         cout << endl;

         Count = 0;
      }

      LastID = ID;
      YT[Count] = yt;
      GWW[Count] = gww;
      NLL[Count] = nll;
      Count = Count + 1;
   }

   if(LastID >= 0)
   {
      cout << setprecision(20) << LastID;
      Integrate(Count, YT, GWW, NLL, NO_PRIOR);
      Integrate(Count, YT, GWW, NLL, NORMAL_PRIOR);
      Integrate(Count, YT, GWW, NLL, LOOSE_PRIOR);
      PickoutModels(Count, YT, GWW, NLL);
      cout << endl;
   }

   return 0;
}

void Integrate(int Count, double *YT, double *GWW, double *NLL, int Prior)
{
   double BestNLL = -1;
   for(int i = 0; i < Count; i++)
   {
      if(BestNLL < 0)
         BestNLL = NLL[i];
      else
      {
         if(BestNLL > NLL[i])
            BestNLL = NLL[i];
      }
   }

   double Result[5];
   for(int i = 0; i < 5; i++)
      Result[i] = 0;

   for(int i = 0; i < Count; i++)
   {
      double Factor = 1;
      if(Prior == NORMAL_PRIOR)
         Factor = EvaluatePrior(YT[i]);
      if(Prior == LOOSE_PRIOR)
         Factor = EvaluatePriorLoose(YT[i]);

      if(GWW[i] < -1.5)
         Result[0] = Result[0] + exp(-(NLL[i] - BestNLL)) * Factor;
      else if(GWW[i] < -0.5)
         Result[1] = Result[1] + exp(-(NLL[i] - BestNLL)) * Factor;
      else if(GWW[i] < 0.5)
         Result[2] = Result[2] + exp(-(NLL[i] - BestNLL)) * Factor;
      else if(GWW[i] < 1.5)
         Result[3] = Result[3] + exp(-(NLL[i] - BestNLL)) * Factor;
      else
         Result[4] = Result[4] + exp(-(NLL[i] - BestNLL)) * Factor;
   }

   cout << setprecision(20);
   for(int i = 0; i < 5; i++)
      cout << " " << Result[i];
}

double EvaluatePrior(double YT)
{
   if(fabs(YT) < 2)
      return 1;
   
   return exp(-(YT - 2) * (YT - 2) / (2 * 0.5 * 0.5));
}

double EvaluatePriorLoose(double YT)
{
   if(fabs(YT) < 2.5)
      return 1;
   
   return exp(-(YT - 2.5) * (YT - 2.5) / (2 * 1 * 1));
}

void PickoutModels(int Count, double *YT, double *GWW, double *NLL)
{
   double NLL_SM = 0;
   double NLL_H5 = 0;

   for(int i = 0; i < Count; i++)
   {
      if(fabs(GWW[i] - 2) < 1e-6 && fabs(YT[i] - 1) < 1e-6)
         NLL_SM = NLL[i];
      if(fabs(GWW[i] + 1) < 1e-6 && fabs(YT[i] - 0) < 1e-6)
         NLL_H5 = NLL[i];
   }

   cout << setprecision(20) << " " << NLL_SM << " " << NLL_H5;
}


