#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

int main()
{
   TFile F1("Graphs_MCPythia8.root");
   TFile F2("Graphs_MCHIReco.root");

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 6; iPT++)
      {
         TH2D *H1 = (TH2D *)F1.Get(Form("HSmear_%d_%d", iC, iPT));
         TH2D *H2 = (TH2D *)F2.Get(Form("HSmear_%d_%d", iC, iPT));

         double T1 = H1->GetBinContent(1, 1);
         double V1 = H1->GetBinContent(4, 1);
         double T2 = H2->GetBinContent(1, 1);
         double V2 = H2->GetBinContent(4, 1);

         cout << iC << " " << iPT << " " << T1 << " " << V1 << " " << T2 << " " << V2 << endl;
      }
   }

   F2.Close();
   F1.Close();

   return 0;
}





