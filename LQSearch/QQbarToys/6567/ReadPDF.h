#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

#include "DrawRandom.h"

vector<pair<double, double> > ReadPDF(string InputFile);
double DrawX(vector<pair<double, double> > &PDF);

vector<pair<double, double> > ReadPDF(string InputFile)
{
   vector<pair<double, double> > PDF;

   ifstream in(InputFile.c_str());

   while(in)
   {
      double x = -1000;
      double Q2 = -1000;
      double xf = -1000;

      in >> x >> Q2 >> xf;

      if(x > 0 && Q2 > 0 && xf > 0)
         PDF.push_back(pair<double, double>(x, xf));
   }

   in.close();

   sort(PDF.begin(), PDF.end());

   cout << "Read " << PDF.size() << " entries from " << InputFile << endl;

   return PDF;
}

double DrawX(vector<pair<double, double> > &PDF)
{
   double x = 0.15;

   bool OK = false;

   while(OK == false)
   {
      x = DrawRandom(0, 1);

      double Limit = 0;
      if(x < PDF[0].first)
         Limit = PDF[0].second;
      else if(x >= PDF[PDF.size()-1].first)
         Limit = PDF[PDF.size()-1].second;
      else
      {
         int FirstLargerIndex = 1;
         for(int i = 1; i < (int)PDF.size(); i++)
         {
            if(x < PDF[i].first)
            {
               FirstLargerIndex = i;
               break;
            }
         }

         double xleft = PDF[FirstLargerIndex-1].first;
         double xright = PDF[FirstLargerIndex].first;

         double yleft = PDF[FirstLargerIndex-1].second;
         double yright = PDF[FirstLargerIndex].second;

         Limit = (yright - yleft) / (xright - xleft) * (x - xleft) + yleft;
      }

      double y = DrawRandom(0, PDF[0].second);

      if(y <= Limit)
         OK = true;
   }

   return x;
}





