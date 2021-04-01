#ifndef HISTOGRAMS_H_21232
#define HISTOGRAMS_H_21232

#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"

#define MODE_NOMATCH 0
#define MODE_NORMAL 1

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
   vector<TH1D *> HResponsePT50;
   vector<TH1D *> HResponsePT100;
   vector<TH1D *> HResponsePT150;
   vector<TH1D *> HResponsePT200;
   vector<TH1D *> HEta;
   vector<TH1D *> HEtaPT2to5;
   vector<TH1D *> HEtaPT3to5;
   vector<TH1D *> HEtaPT3to6;
   vector<TH1D *> HEtaPT3to10;
   vector<TH1D *> HEtaPT3to15;
   vector<TH1D *> HEtaPT15;
   vector<TH1D *> HEtaPT20;
   vector<TH1D *> HEtaPT10to25;
   vector<TH1D *> HEtaPT25;
   vector<TH1D *> HEtaPT30;
   vector<TH1D *> HEtaPT20to40;
   vector<TH1D *> HEtaPT40;
   vector<TH1D *> HEtaPT40to100;
   vector<TH1D *> HEtaPT100;
   vector<TH1D *> HEtaPT200;
   vector<TH1D *> HEtaDXY20;
   vector<TH1D *> HEtaDXY50;
   vector<TH1D *> HEtaDXY80;
   vector<TH1D *> HTkIso;
   vector<TH1D *> HTkIsoPT10;
   vector<TH1D *> HTkIsoPT20;
   vector<TH1D *> HTkIsoPT30;
   vector<TH1D *> HTkIsoPT40;
   vector<TH1D *> HTkIsoEta15;
   vector<TH1D *> HTkIsoEtaLarge;
   vector<TH1D *> HTkIsoPT10Eta15;
   vector<TH1D *> HTkIsoPT10EtaLarge;
   vector<TH1D *> HDR;
   vector<TH1D *> HDRPT10;
   vector<TH1D *> HDRPT20;
   vector<TH1D *> HDRPT50;
   vector<TH1D *> HDREta15;
   vector<TH1D *> HDRPT10Eta15;
   vector<TH1D *> HDRPT20Eta15;
   vector<TH1D *> HDREtaLarge;
   vector<TH1D *> HDRPT10EtaLarge;
   vector<TH1D *> HDRPT20EtaLarge;
   vector<TH1D *> HDXY;
   vector<TH1D *> HDXYPT15;
   vector<TH1D *> HDXYPT20;
   vector<TH1D *> HDXYPT30;
public:
   Histograms(int ptbin, double ptmin, double ptmax,
      int etabin, double etamin, double etamax,
      int isobin, double isomin, double isomax,
      int dxybin, double dxymin, double dxymax,
      vector<double> &thresholds, string Label);
   ~Histograms();
   void Fill(double check, double pt, double eta, double iso, double dr, bool Mode, int Region, double dxy);
   void Fill(FourVector Check, FourVector P, double iso, int Region, double dxy);
   void Write(TDirectory *Directory = NULL);
   void Write(vector<TH1D *> &Histograms, TDirectory *Directory);
   TH1D *New(string Label, string Name, string Cut, string Title, int Bin, double Min, double Max);
};

#endif
