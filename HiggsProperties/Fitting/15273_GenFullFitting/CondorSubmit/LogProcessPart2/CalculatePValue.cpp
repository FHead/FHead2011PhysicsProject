#include <map>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

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

      for(int i = 0; i < (int)GWW[ID].size(); i++)
      {
         if(GWW[ID][i] < 0)
            Negative = Negative + exp(-(NLL[ID][i] - NLL[ID][0]));
         else if(GWW[ID][i] > 0)
            Positive = Positive + exp(-(NLL[ID][i] - NLL[ID][0]));
         else
         {
            Negative = Negative + exp(-(NLL[ID][i] - NLL[ID][0])) / 2;
            Positive = Positive + exp(-(NLL[ID][i] - NLL[ID][0])) / 2;
         }
      }

      cout << YT[ID][0] << " " << GWW[ID][0] << " " << NLL[ID][0]
         << " " << Negative / (Negative + Positive) << endl;
   }

   return 0;
}



