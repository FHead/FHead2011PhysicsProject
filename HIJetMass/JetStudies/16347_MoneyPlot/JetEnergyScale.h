#ifndef JetEnergyScale_16347
#define JetEnergyScale_16347

#include <iostream>
#include <cmath>
using namespace std;

#include "TF1.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "PlotHelper3Forward.h"

class JetEnergyScale
{
public:
   TProfile *P[30];   // 30 bins in eta, each covering range 0.087
   TH2D *H[30];
   double A[30][7];   // fit to pol4 for each profile
public:
   JetEnergyScale();
   ~JetEnergyScale();
   void Fill(double JetPT, double RawJetPT, double Eta, double Weight = 1);
   int FindBin(double Eta);
   double DistanceToBoundary(double Eta);
   void DoFit();
   double Apply(double RawJetPT, double Eta);
};

#endif
