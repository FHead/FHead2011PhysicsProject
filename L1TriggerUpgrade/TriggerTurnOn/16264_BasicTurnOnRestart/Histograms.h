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
   vector<TH1D *> HPTEta15;
   vector<TH1D *> HPTEta15Large;
   vector<TH1D *> HEta;
   vector<TH1D *> HEtaPT20;
   vector<TH1D *> HEtaPT25;
   vector<TH1D *> HEtaPT200;
   vector<TH1D *> HPTIso010;
   vector<TH1D *> HPTEta10Iso010;
   vector<TH1D *> HPTEtaLargeIso010;
   vector<TH1D *> HPTEta15Iso010;
   vector<TH1D *> HPTEta15LargeIso010;
   vector<TH1D *> HEtaIso010;
   vector<TH1D *> HEtaPT20Iso010;
   vector<TH1D *> HEtaPT25Iso010;
   vector<TH1D *> HEtaPT200Iso010;
   vector<TH1D *> HPTIso014;
   vector<TH1D *> HPTEta10Iso014;
   vector<TH1D *> HPTEtaLargeIso014;
   vector<TH1D *> HPTEta15Iso014;
   vector<TH1D *> HPTEta15LargeIso014;
   vector<TH1D *> HEtaIso014;
   vector<TH1D *> HEtaPT20Iso014;
   vector<TH1D *> HEtaPT25Iso014;
   vector<TH1D *> HEtaPT200Iso014;
   vector<TH1D *> HPTIso023;
   vector<TH1D *> HPTEta10Iso023;
   vector<TH1D *> HPTEtaLargeIso023;
   vector<TH1D *> HPTEta15Iso023;
   vector<TH1D *> HPTEta15LargeIso023;
   vector<TH1D *> HEtaIso023;
   vector<TH1D *> HEtaPT20Iso023;
   vector<TH1D *> HEtaPT25Iso023;
   vector<TH1D *> HEtaPT200Iso023;
   vector<TH1D *> HPTIso045;
   vector<TH1D *> HPTEta10Iso045;
   vector<TH1D *> HPTEtaLargeIso045;
   vector<TH1D *> HPTEta15Iso045;
   vector<TH1D *> HPTEta15LargeIso045;
   vector<TH1D *> HEtaIso045;
   vector<TH1D *> HEtaPT20Iso045;
   vector<TH1D *> HEtaPT25Iso045;
   vector<TH1D *> HEtaPT200Iso045;
   vector<TH1D *> HTkIso;
   vector<TH1D *> HTkIsoRestricted;
   vector<TH1D *> HTkIsoRestricted2;
public:
   Histograms(int ptbin, double ptmin, double ptmax,
      int etabin, double etamin, double etamax,
      int isobin, double isomin, double isomax,
      vector<double> &thresholds, string Label);
   ~Histograms();
   void Fill(double check, double pt, double eta, double iso);
   void Fill(FourVector Check, FourVector P, double iso);
   void Write(TDirectory *Directory = NULL);
};

vector<double> ToVector(int N, double X1 = -1, double X2 = -1, double X3 = -1,
   double X4 = -1, double X5 = -1, double X6 = -1, double X7 = -1, double X8 = -1,
   double X9 = -1, double X10 = -1, double X11 = -1, double X12 = -1, double X13 = -1,
   double X14 = -1, double X15 = -1, double X16 = -1, double X17 = -1, double X18 = -1,
   double X19 = -1, double X20 = -1, double X21 = -1, double X22 = -1, double X23 = -1,
   double X24 = -1, double X25 = -1);
