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
   vector<TH1D *> HResponse;
   vector<TH1D *> HResponseEta15;
   vector<TH1D *> HResponseEtaLarge;
   vector<TH1D *> HResponsePT10;
   vector<TH1D *> HResponsePT10Eta15;
   vector<TH1D *> HResponsePT10EtaLarge;
   vector<TH1D *> HEta;
   vector<TH1D *> HEtaPT20;
   vector<TH1D *> HEtaPT25;
   vector<TH1D *> HEtaPT200;
   vector<TH1D *> HTkIso;
   vector<TH1D *> HTkIsoPT10;
   vector<TH1D *> HTkIsoPT20;
   vector<TH1D *> HTkIsoPT30;
   vector<TH1D *> HTkIsoPT40;
public:
   Histograms(int ptbin, double ptmin, double ptmax,
      int etabin, double etamin, double etamax,
      int isobin, double isomin, double isomax,
      vector<double> &thresholds, string Label);
   ~Histograms();
   void Fill(double check, double pt, double eta, double iso);
   void Fill(FourVector Check, FourVector P, double iso);
   void Write(TDirectory *Directory = NULL);
   void Write(vector<TH1D *> &Histograms, TDirectory *Directory);
};

