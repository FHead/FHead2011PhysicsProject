#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " FileName SizeFirstBin SizeRest" << endl;
      return -1;
   }

   TFile F(argv[1], "RECREATE");
   double Size = atof(argv[2]);
   double SizeRest = atof(argv[3]);

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 6; iPT++)
      {
         TGraphAsymmErrors *G = new TGraphAsymmErrors;

         G->SetNameTitle(Form("GRatio_C%d_P%d", iC, iPT), "");

         for(int i = 0; i < 160; i++)
         {
            double BinCenter = (i + 0.5) / 160 * (0.4 - 0.0);

            G->SetPoint(i, BinCenter, 0);
            if(iC == 0 && iPT == 1)
               G->SetPointError(i, 0, 0, log(1 + Size), log(1 + Size));
            else
               G->SetPointError(i, 0, 0, log(1 + SizeRest), log(1 + SizeRest));
         }

         G->Write();
      }
   }

   F.Close();
}



