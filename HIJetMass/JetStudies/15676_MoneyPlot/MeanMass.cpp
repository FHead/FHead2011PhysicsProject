#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"

int main()
{
   TFile File("Graphs.root");

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 6; iPT++)
      {
         TGraphAsymmErrors *GData = (TGraphAsymmErrors *)File.Get(Form("Data_%d_%d", iC, iPT));
         TGraphAsymmErrors *GSmear = (TGraphAsymmErrors *)File.Get(Form("Smear_%d_%d", iC, iPT));

         double DataTotalXY = 0;
         double DataTotalY = 0;
         double SmearTotalXY = 0;
         double SmearTotalY = 0;

         for(int i = 0; i < (int)GData->GetN(); i++)
         {
            double x, y;
            GData->GetPoint(i, x, y);
            if(y > 0 && x == x)
            {
               DataTotalXY = DataTotalXY + x * y;
               DataTotalY = DataTotalY + y;
            }
         }
         for(int i = 0; i < (int)GSmear->GetN(); i++)
         {
            double x, y;
            GSmear->GetPoint(i, x, y);
            if(y > 0 && x == x)
            {
               SmearTotalXY = SmearTotalXY + x * y;
               SmearTotalY = SmearTotalY + y;
            }
         }

         double DataMeanX = DataTotalXY / DataTotalY;
         double SmearMeanX = SmearTotalXY / SmearTotalY;

         cout << iC << " " << iPT << " " << DataMeanX << " " << SmearMeanX << endl;
      }
   }

   File.Close();

   return 0;
}




