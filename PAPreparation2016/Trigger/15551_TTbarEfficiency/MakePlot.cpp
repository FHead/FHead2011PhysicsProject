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

   File.Close();
}



