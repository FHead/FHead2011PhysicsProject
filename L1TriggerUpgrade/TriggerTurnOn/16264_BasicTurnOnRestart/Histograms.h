#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"

class Histograms
{
public:
   vector<double> Thresholds;
   vector<TH1D *> HPT;
   vector<TH1D *> HPTEta10;
   vector<TH1D *> HPTEtaLarge;
   vector<TH1D *> HEta;
   vector<TH1D *> HEtaPT20;
   vector<TH1D *> HEtaPT25;
public:
   Histograms(int ptbin, double ptmin, double ptmax, int etabin, double etamin, double etamax,
      vector<double> &thresholds, string Label);
   ~Histograms();
   void Fill(double check, double pt, double eta);
   void Fill(FourVector Check, FourVector P);
   void Write(TDirectory *Directory = NULL);
};

vector<double> ToVector(int N, double X1 = -1, double X2 = -1, double X3 = -1,
   double X4 = -1, double X5 = -1, double X6 = -1, double X7 = -1, double X8 = -1,
   double X9 = -1, double X10 = -1, double X11 = -1, double X12 = -1, double X13 = -1,
   double X14 = -1, double X15 = -1, double X16 = -1, double X17 = -1, double X18 = -1,
   double X19 = -1, double X20 = -1, double X21 = -1, double X22 = -1, double X23 = -1,
   double X24 = -1, double X25 = -1);
