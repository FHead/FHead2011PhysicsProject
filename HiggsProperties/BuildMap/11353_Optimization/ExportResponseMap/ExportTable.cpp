#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2F.h"

int main();
void ExportHistogram(TFile &F, string Name);

int main()
{
   double ptBins[15] = {5, 7, 8, 9, 10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 50};
   double etaBins[17] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4442, 1.566, 1.8, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6};

   TFile File("PtResolutionModel_ZZ.root");

   cout << "static const double mean[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_mean");
   cout << endl;

   cout << "static const double sigma[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_sigma");
   cout << endl;
   
   cout << "static const double alphaL[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_alphaL");
   cout << endl;
   
   cout << "static const double alphaR[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_alphaR");
   cout << endl;
   
   cout << "static const double nL[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_nL");
   cout << endl;
   
   cout << "static const double nR[][] = ";
   ExportHistogram(File, "DoubleSidedCBShapeParamArray_Muons_nR");
   cout << endl;
   

   File.Close();

   return 0;
}

void ExportHistogram(TFile &F, string Name)
{
   TH2F *H = (TH2F *)F.Get(Name.c_str());

   cout << "{" << endl;
   for(int i = 1; i <= H->GetNbinsY(); i++)
   {
      cout << "{";
      for(int j = 1; j <= H->GetNbinsX(); j++)
      {
         if(j != 1)
            cout << ", ";
         cout << H->GetBinContent(j, i);
      }
      cout << "}";

      if(i != H->GetNbinsY())
      {
         cout << ",";
         cout << endl;
      }
   }
   cout << "};" << endl;
}








