#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " InputFile" << endl;
      return -1;
   }

   TFile File(argv[1]);

   TH2D *HH1 = (TH2D *)File.Get("HSDMassRatioVsRecoSubJetDR_I");
   TH2D *HH2 = (TH2D *)File.Get("HSDMassRatioVsRecoSubJetDR_II");

   if(HH1 == NULL || HH2 == NULL)
      return -1;

   TH1D *H1 = HH1->ProjectionX();
   TH1D *H2 = HH2->ProjectionX();

   cout << "Region I = " << H1->Integral() << endl;
   cout << "Region II = " << H2->Integral() << endl;
   cout << "Region II / All = " << H2->Integral() / (H1->Integral() + H2->Integral()) << endl;
   
   cout << "Region I (DR > 0.2) = " << H1->Integral(26, 100) << endl;
   cout << "Region II (DR > 0.2) = " << H2->Integral(26, 100) << endl;
   cout << "Region II / All (DR > 0.2) = "
      << H2->Integral(26, 100) / (H1->Integral(26, 100) + H2->Integral(26, 100)) << endl;

   File.Close();

   return 0;
}





