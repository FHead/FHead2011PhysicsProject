#include "Histograms.h"

Histograms::Histograms(int ptbin, double ptmin, double ptmax, int etabin, double etamin, double etamax,
   vector<double> &thresholds, string Label)
{
   Thresholds = thresholds;

   for(int iT = 0; iT < (int)thresholds.size(); iT++)
   {
      HPT.push_back(new TH1D(Form("%s_PT_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEta.push_back(new TH1D(Form("%s_Eta_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      
      HPT[iT]->Sumw2();
      HEta[iT]->Sumw2();
   }
}

Histograms::~Histograms()
{
   // We don't have ownership over histograms!

   // for(int i = 0; i < (int)HPT.size(); i++)
   //    if(HPT[i] != NULL)
   //       delete HPT[i];
   // for(int i = 0; i < (int)HEta.size(); i++)
   //    if(HEta[i] != NULL)
   //       delete HEta[i];
}

void Histograms::Fill(double check, double pt, double eta)
{
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(check < Thresholds[i])
         continue;

      if(HPT[i] != NULL)    HPT[i]->Fill(pt);
      if(HEta[i] != NULL)   HEta[i]->Fill(eta);
   }
}

void Histograms::Write(TDirectory *Directory)
{
   if(Directory != NULL)
      Directory->cd();

   for(int i = 0; i < (int)HPT.size(); i++)
   {
      if(HPT[i] == NULL)
         continue;

      if(Directory != NULL)
         HPT[i]->SetDirectory(Directory);
      HPT[i]->Write();
   }
   
   for(int i = 0; i < (int)HEta.size(); i++)
   {
      if(HEta[i] == NULL)
         continue;

      if(Directory != NULL)
         HEta[i]->SetDirectory(Directory);
      HEta[i]->Write();
   }
}

vector<double> ToVector(int N, double X1, double X2, double X3,
   double X4, double X5, double X6, double X7, double X8,
   double X9, double X10, double X11, double X12, double X13,
   double X14, double X15, double X16, double X17, double X18,
   double X19, double X20, double X21, double X22, double X23,
   double X24, double X25)
{
   vector<double> Result;

   if(N > 25)
      cerr << "[ToVector] Warning!  More than 25 entries is currently not supported!" << endl;

   if(N >= 1)   Result.push_back(X1);
   if(N >= 2)   Result.push_back(X2);
   if(N >= 3)   Result.push_back(X3);
   if(N >= 4)   Result.push_back(X4);
   if(N >= 5)   Result.push_back(X5);
   if(N >= 6)   Result.push_back(X6);
   if(N >= 7)   Result.push_back(X7);
   if(N >= 8)   Result.push_back(X8);
   if(N >= 9)   Result.push_back(X9);
   if(N >= 10)   Result.push_back(X10);
   if(N >= 11)   Result.push_back(X11);
   if(N >= 12)   Result.push_back(X12);
   if(N >= 13)   Result.push_back(X13);
   if(N >= 14)   Result.push_back(X14);
   if(N >= 15)   Result.push_back(X15);
   if(N >= 16)   Result.push_back(X16);
   if(N >= 17)   Result.push_back(X17);
   if(N >= 18)   Result.push_back(X18);
   if(N >= 19)   Result.push_back(X19);
   if(N >= 20)   Result.push_back(X10);
   if(N >= 21)   Result.push_back(X11);
   if(N >= 22)   Result.push_back(X12);
   if(N >= 23)   Result.push_back(X13);
   if(N >= 24)   Result.push_back(X14);
   if(N >= 25)   Result.push_back(X15);

   return Result;
}
