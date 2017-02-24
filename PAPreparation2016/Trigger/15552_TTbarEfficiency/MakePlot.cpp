#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   TFile File("Output.root");

   SetThesisStyle();

   TH2D *H = (TH2D *)File.Get("HYield");
   H->SetStats(0);

   TCanvas C;
   H->Draw("colz text00");

   C.SaveAs("Yield.png");
   C.SaveAs("Yield.C");
   C.SaveAs("Yield.eps");
   C.SaveAs("Yield.pdf");

   cout << "Calo 40 " << H->GetBinContent(8, 2) / H->GetBinContent(2, 2) << endl;
   cout << "Calo 60 " << H->GetBinContent(9, 3) / H->GetBinContent(3, 3) << endl;
   cout << "Calo 80 " << H->GetBinContent(10, 4) / H->GetBinContent(4, 4) << endl;
   cout << "PF 40 " << H->GetBinContent(11, 5) / H->GetBinContent(5, 5) << endl;
   cout << "PF 60 " << H->GetBinContent(12, 6) / H->GetBinContent(6, 6) << endl;
   cout << "PF 80 " << H->GetBinContent(13, 7) / H->GetBinContent(7, 7) << endl;

   File.Close();
}



