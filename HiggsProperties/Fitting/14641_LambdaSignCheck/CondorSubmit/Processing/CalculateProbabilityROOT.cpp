#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TGraph.h"
#include "TF1.h"

int main(int argc, char *argv[]);
double NegativeProbability(const vector<double> &x, const vector<double> &y, double &Sigma, double &a, double &b, double &c);

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      cerr << "Usage: " << argv[0] << " FileName" << endl;
      return -1;
   }

   ifstream in(argv[1]);

   map<int, vector<double> > X;
   map<int, vector<double> > Y;

   while(in)
   {
      double temp[14] = {0};
      for(int i = 0; i < 14; i++)
         temp[i] = -1;

      for(int i = 0; i < 14; i++)
         in >> temp[i];

      if(temp[0] < 0)
         continue;

      if(X.find(temp[0]) == X.end())
      {
         X.insert(pair<int, vector<double> >(temp[0], vector<double>()));
         Y.insert(pair<int, vector<double> >(temp[0], vector<double>()));
      }

      X[temp[0]].push_back(temp[7]);
      Y[temp[0]].push_back(temp[13]);
   }

   in.close();

   for(map<int, vector<double> >::iterator iter = X.begin(); iter != X.end(); iter++)
   {
      int ID = iter->first;

      double Sigma = 0;
      double a = 0, b = 0, c = 0;
      double P = NegativeProbability(X[ID], Y[ID], Sigma, a, b, c);

      cout << ID << " " << P << " " << Sigma << endl;
   }

   return 0;
}

double NegativeProbability(const vector<double> &x, const vector<double> &y, double &Sigma,
   double &a, double &b, double &c)
{
   TGraph G;
   for(int i = 0; i < (int)x.size(); i++)
      G.SetPoint(i, x[i], y[i]);

   TF1 F("F", "pol2");
   G.Fit(&F);

   a = F.GetParameter(2);
   b = F.GetParameter(1);
   c = F.GetParameter(0);

   cerr << a << " " << b << " " << c << " " << -b / sqrt(2 * a) << endl;

   double min = (4 * a * c - b * b) / (4 * a);
   double minlocation = -b / (2 * a);

   cout << minlocation << endl;

   Sigma = minlocation * sqrt(2 * a);

   double p = (1 - erf(Sigma / sqrt(2))) / 2;

   return p;
}



