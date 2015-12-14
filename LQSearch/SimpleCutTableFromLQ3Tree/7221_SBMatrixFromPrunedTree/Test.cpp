#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

int main()
{
   TFile F("Matrices.root");

   TH1D *H1 = (TH1D *)F.Get("HMRStar_RStar020Cut_QCD50");
   TH1D *H2 = (TH1D *)F.Get("HMRStar_RStar020Cut_QCD100");
   TH1D *H3 = (TH1D *)F.Get("HMRStar_RStar020Cut_QCD250");
   TH1D *H4 = (TH1D *)F.Get("HMRStar_RStar020Cut_QCD500");
   TH1D *H5 = (TH1D *)F.Get("HMRStar_RStar020Cut_QCD1000");

   H1->Add(H2);
   H1->Add(H3);
   H1->Add(H4);
   H1->Add(H5);
   
   TH1D *H6 = (TH1D *)F.Get("HMRStar_RStar050Cut_QCD50");
   TH1D *H7 = (TH1D *)F.Get("HMRStar_RStar050Cut_QCD100");
   TH1D *H8 = (TH1D *)F.Get("HMRStar_RStar050Cut_QCD250");
   TH1D *H9 = (TH1D *)F.Get("HMRStar_RStar050Cut_QCD500");
   TH1D *H10 = (TH1D *)F.Get("HMRStar_RStar050Cut_QCD1000");

   H6->Add(H7);
   H6->Add(H8);
   H6->Add(H9);
   H6->Add(H10);

   TCanvas C;
   H1->Draw();
   H6->Draw("same");
   C.SetLogy();
   C.SaveAs("Test.png");

   F.Close();

   return 0;
}



