#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " FileName Size" << endl;
      return -1;
   }

   TFile F(argv[1], "RECREATE");
   double Size = atof(argv[2]);

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
            G->SetPointError(i, 0, 0, log(1 + Size), log(1 + Size));
         }

         G->Write();
      }
   }

   F.Close();
}



