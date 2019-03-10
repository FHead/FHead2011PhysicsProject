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
   vector<TH1D *> HPTEta15;
   vector<TH1D *> HPTEtaLarge;
   vector<TH1D *> HEta;
   vector<TH1D *> HEtaPT20;
   vector<TH1D *> HEtaPT25;
   vector<TH1D *> HEtaPT200;
   vector<TH1D *> HTkIso;
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

