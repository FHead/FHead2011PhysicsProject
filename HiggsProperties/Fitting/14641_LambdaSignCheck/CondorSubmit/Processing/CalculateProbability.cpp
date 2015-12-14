#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

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
   double SumX0 = 0;
   double SumX1 = 0;
   double SumX2 = 0;
   double SumX3 = 0;
   double SumX4 = 0;
   double SumX0Y = 0;
   double SumX1Y = 0;
   double SumX2Y = 0;

   for(int i = 0; i < (int)x.size(); i++)
   {
      SumX0 = SumX0 + 1;
      SumX1 = SumX1 + x[i];
      SumX2 = SumX2 + x[i] * x[i];
      SumX3 = SumX3 + x[i] * x[i] * x[i];
      SumX4 = SumX4 + x[i] * x[i] * x[i] * x[i];
      SumX0Y = SumX0Y + y[i];
      SumX1Y = SumX1Y + x[i] * y[i];
      SumX2Y = SumX2Y + x[i] * x[i] * y[i];
   }

   double D = SumX4 * SumX2 * SumX0 - SumX4 * SumX1 * SumX1
      + SumX3 * SumX1 * SumX2 - SumX3 * SumX3 * SumX0
      + SumX2 * SumX3 * SumX1 - SumX2 * SumX2 * SumX2;
   double Da = SumX2Y * SumX2 * SumX0 - SumX2Y * SumX1 * SumX1
      + SumX1Y * SumX1 * SumX2 - SumX1Y * SumX3 * SumX0
      + SumX0Y * SumX3 * SumX1 - SumX0Y * SumX2 * SumX2;
   double Db = SumX4 * SumX1Y * SumX0 - SumX4 * SumX0Y * SumX1
      + SumX3 * SumX0Y * SumX2 - SumX3 * SumX2Y * SumX0
      + SumX2 * SumX2Y * SumX1 - SumX2 * SumX1Y * SumX2;
   double Dc = SumX4 * SumX2 * SumX0Y - SumX4 * SumX1 * SumX1Y
      + SumX3 * SumX1 * SumX2Y - SumX3 * SumX3 * SumX0Y
      + SumX2 * SumX3 * SumX1Y - SumX2 * SumX2 * SumX2Y;

   a = Da / D;
   b = Db / D;
   c = Dc / D;

   double min = (4 * a * c - b * b) / (4 * a);
   double minlocation = -b / (2 * a);

   cout << minlocation << endl;

   Sigma = minlocation * sqrt(2 * a);

   double p = (1 - erf(Sigma / sqrt(2))) / 2;

   return p;
}



