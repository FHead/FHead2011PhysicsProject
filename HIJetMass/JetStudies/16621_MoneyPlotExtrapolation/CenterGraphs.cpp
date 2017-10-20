#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TList.h"
#include "TKey.h"
#include "TObject.h"
#include "TClass.h"

int main(int argc, char *argv[]);
void ClearNaN(TGraphAsymmErrors *G);

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SD" << endl;
      return -1;
   }

   string SD = argv[1];

   string InputFileName = "Graphs_SD" + SD + "_DataPicked.root";
   string OutputFileName = "Graphs_SD" + SD + "_DataCentered.root";

   TFile FileIn(InputFileName.c_str());
   TFile FileOut(OutputFileName.c_str(), "RECREATE");

   TList *List = (TList *)FileIn.GetListOfKeys();
   TIter Iter(List);
   TKey *Key = NULL, *OldKey = NULL;

   do
   {
      Key = (TKey *)Iter();
      if(Key == NULL)
         break;

      TObject *Object = Key->ReadObj();

      if(Object->IsA()->InheritsFrom("TGraphAsymmErrors") == true)   // asymmetric graph!  center them!
      {
         TGraphAsymmErrors *G = (TGraphAsymmErrors *)Object;

         int N = G->GetN();
         for(int i = 0; i < N; i++)
         {
            double x, y;
            G->GetPoint(i, x, y);

            double xl, xr;
            xl = G->GetErrorXlow(i);
            xr = G->GetErrorXhigh(i);

            x = (2 * x + xr - xl) / 2;

            G->SetPoint(i, x, y);
            G->SetPointEXlow(i, (xl + xr) / 2);
            G->SetPointEXhigh(i, (xl + xr) / 2);
         }

         ClearNaN(G);

         G->Clone(G->GetName())->Write();
      }
      else   // otherwise just copy them to the new file
         Object->Clone(Object->GetName())->Write();

   } while(Key != NULL);

   FileOut.Close();
   FileIn.Close();

   return 0;
}

void ClearNaN(TGraphAsymmErrors *G)
{
   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      double xl, xr, yl, yr;

      G->GetPoint(i, x, y);
      xl = G->GetErrorXlow(i);
      xr = G->GetErrorXhigh(i);
      yl = G->GetErrorYlow(i);
      yr = G->GetErrorYhigh(i);

      if(x != x || y != y || xl != xl || xr != xr || yl != yl || yr != yr)
      {
         G->SetPoint(i, x, -1);
         G->SetPointError(i, 0, 0, 1000, 1000);
      }
   }
}





