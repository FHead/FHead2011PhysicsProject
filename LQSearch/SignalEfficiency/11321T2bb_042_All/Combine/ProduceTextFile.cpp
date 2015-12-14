#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

int main()
{
   TFile F1("PDF.root");
   TFile F2("EverythingElseRelativeError.root");

   TH2D *HCentral = (TH2D *)F1.Get("HCentral");
   TH2D *HPDF = (TH2D *)F1.Get("HRelative");
   TH2D *HDuoCentral = (TH2D *)F1.Get("HDuoCentral");
   TH2D *HDuoPDF = (TH2D *)F1.Get("HDuoRelative");
   TH2D *HOthers = (TH2D *)F2.Get("HRelativeEfficiency");

   for(int i = 1; i <= HCentral->GetNbinsX(); i++)
   {
      for(int j = 1; j <= HCentral->GetNbinsY(); j++)
      {
         if(HCentral->GetBinContent(i, j) <= 0)
            continue;

         cout << "[WithNNPDF]" << HCentral->GetXaxis()->GetBinLowEdge(i) << " " << HCentral->GetYaxis()->GetBinLowEdge(j)
            << " " << HCentral->GetBinContent(i, j)
            << " " << HCentral->GetBinContent(i, j) * sqrt(HPDF->GetBinContent(i, j) * HPDF->GetBinContent(i, j)
               + HOthers->GetBinContent(i, j) * HOthers->GetBinContent(i, j)) << endl;
         cout << "[WithoutNNPDF]" << HDuoCentral->GetXaxis()->GetBinLowEdge(i) << " " << HDuoCentral->GetYaxis()->GetBinLowEdge(j)
            << " " << HDuoCentral->GetBinContent(i, j)
            << " " << HDuoCentral->GetBinContent(i, j) * sqrt(HDuoPDF->GetBinContent(i, j) * HDuoPDF->GetBinContent(i, j)
               + HOthers->GetBinContent(i, j) * HOthers->GetBinContent(i, j)) << endl;
      }
   }

   F2.Close();
   F1.Close();

   return 0;
}





