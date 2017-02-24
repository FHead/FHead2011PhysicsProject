#include <map>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

int main();
double EvaluatePrior(double YT);

int main()
{
   map<int, vector<double> > YT;
   map<int, vector<double> > GWW;
   map<int, vector<double> > NLL;

   while(cin)
   {
      int ID = -1;
      double yt = -1, gww = -1, nll = -1;
      cin >> ID >> yt >> gww >> nll;

      if(ID < 0)
         continue;

      if(YT.find(ID) == YT.end())
      {
         YT.insert(pair<int, vector<double> >(ID, vector<double>()));
         GWW.insert(pair<int, vector<double> >(ID, vector<double>()));
         NLL.insert(pair<int, vector<double> >(ID, vector<double>()));
      }

      YT[ID].push_back(yt);
      GWW[ID].push_back(gww);
      NLL[ID].push_back(nll);
   }

   for(map<int, vector<double> >::iterator iter = YT.begin(); iter != YT.end(); iter++)
   {
      int ID = iter->first;

      double Positive = 0;
      double Negative = 0;

      double PositiveWithPrior = 0;
      double NegativeWithPrior = 0;

      double BestNLL = -1;
      for(int i = 0; i < (int)GWW[ID].size(); i++)
      {
         if(BestNLL < 0)
            BestNLL = NLL[ID][i];
         else
            BestNLL = ((BestNLL > NLL[ID][i]) ? NLL[ID][i] : BestNLL);
      }

      for(int i = 0; i < (int)GWW[ID].size(); i++)
      {
         if(GWW[ID][i] < 0)
            Negative = Negative + exp(-(NLL[ID][i] - BestNLL));
         else if(GWW[ID][i] > 0)
            Positive = Positive + exp(-(NLL[ID][i] - BestNLL));
         else
         {
            Negative = Negative + exp(-(NLL[ID][i] - BestNLL)) / 2;
            Positive = Positive + exp(-(NLL[ID][i] - BestNLL)) / 2;
         }
         
         double Prior = EvaluatePrior(YT[ID][i]);
         if(GWW[ID][i] < 0)
            NegativeWithPrior = NegativeWithPrior + exp(-(NLL[ID][i] - BestNLL)) * Prior;
         else if(GWW[ID][i] > 0)
            PositiveWithPrior = PositiveWithPrior + exp(-(NLL[ID][i] - BestNLL)) * Prior;
         else
         {
            NegativeWithPrior = NegativeWithPrior + exp(-(NLL[ID][i] - BestNLL)) * Prior / 2;
            PositiveWithPrior = PositiveWithPrior + exp(-(NLL[ID][i] - BestNLL)) * Prior / 2;
         }
      }

      cout << ID << " " << Negative / (Negative + Positive)
         << " " << NegativeWithPrior / (NegativeWithPrior + PositiveWithPrior)<< endl;
   }

   return 0;
}

double EvaluatePrior(double YT)
{
   if(fabs(YT) < 2)
      return 1;
   
   return exp(-(YT - 2) * (YT - 2) / (2 * 0.5 * 0.5));
}

