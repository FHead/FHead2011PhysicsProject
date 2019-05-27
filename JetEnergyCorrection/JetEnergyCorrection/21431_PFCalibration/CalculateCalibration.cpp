#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

#include "TF1.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
void energyEmHad(double t, double& e, double&h, double eta, double phi, map<string, TF1> &F);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName = CL.Get("input", "PFCalibration2019_mc_UL2017.txt");

   map<int, string> Labels;
   Labels[3001] = "aBarrel";
   Labels[3002] = "aEndcap";
   Labels[3003] = "bBarrel";
   Labels[3004] = "bEndcap";
   Labels[3005] = "cBarrel";
   Labels[3006] = "cEndcap";
   Labels[3007] = "aEtaBarrel";
   Labels[3008] = "aEtaEndcap";
   Labels[3009] = "bEtaBarrel";
   Labels[3010] = "bEtaEndcap";
   Labels[3011] = "aEtaBarrelH";
   Labels[3012] = "aEtaEndcapH";
   Labels[3013] = "bEtaBarrelH";
   Labels[3014] = "bEtaEndcapH";
   Labels[3015] = "aEtaBarrelEH";
   Labels[3016] = "aEtaEndcapEH";
   Labels[3017] = "bEtaBarrelEH";
   Labels[3018] = "bEtaEndcapEH";
   Labels[3019] = "cEtaBarrelH";
   Labels[3020] = "cEtaBarrelEH";
   Labels[3021] = "cEtaEndcapH";
   Labels[3022] = "cEtaEndcapEH";
   Labels[3023] = "dEtaEndcapH";
   Labels[3024] = "dEtaEndcapEH";

   ifstream in(FileName);

   map<string, TF1> F;

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';

      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      int ID = 0;
      double Min = 0, Max = 1000;
      string Formula = "";

      str >> ID >> Min >> Max >> Formula;

      if(Labels.find(ID) == Labels.end())
         continue;

      F[Labels[ID]] = TF1(Labels[ID].c_str(), Formula.c_str());
   }

   double t = 60;
   double ee = 10, hh = 30;
   double e = ee, h = hh;
   double eta = 0.5;
   double phi = 3;

   energyEmHad(t, e, h, eta, phi, F);
   cout << t << " " << eta << " " << ee << " " << hh << " => " << e << " " << h << endl;

   in.close();

   return 0;
}

void energyEmHad(double t, double& e, double&h, double eta, double phi, map<string, TF1> &F)
{
   double threshE = 3.5;
   double threshH = 2.5;

   // Use calorimetric energy as true energy for neutral particles
   double tt = t;
   double ee = e;
   double hh = h;
   double a = 1.;
   double b = 1.;
   double etaCorrE = 1.;
   double etaCorrH = 1.;
   auto absEta = std::abs(eta);
   t = min(999.9,max(tt,e+h));
   if ( t < 1. ) return;

   // Barrel calibration
   if ( absEta < 1.48 ) { 
      // The energy correction
      a = e>0. ? F["aBarrel"](t) : 1.;
      b = e>0. ? F["bBarrel"](t) : F["cBarrel"](t);
      double thresh = e > 0. ? threshE : threshH;

      // Protection against negative calibration
      if ( a < -0.25 || b < -0.25 ) { 
         a = 1.;
         b = 1.;
         thresh = 0.;
      }

      // The new estimate of the true energy
      t = min(999.9,max(tt, thresh+a*e+b*h));

      // The angular correction 
      if ( e > 0. && thresh > 0. ) {
         etaCorrE = 1.0 + F["aEtaBarrelEH"](t) + 1.3*F["bEtaBarrelEH"](t)*F["cEtaBarrelEH"](absEta);
         etaCorrH = 1.0;
      } else {
         etaCorrE = 1.0 + F["aEtaBarrelH"](t) + 1.3*F["bEtaBarrelH"](t)*F["cEtaBarrelH"](absEta);
         etaCorrH = 1.0 + F["aEtaBarrelH"](t) + F["bEtaBarrelH"](t)*F["cEtaBarrelH"](absEta);


      }
      if ( e > 0. && thresh > 0. ) 
         e = h > 0. ? threshE-threshH + etaCorrE * a * e : threshE + etaCorrE * a * e;
      if ( h > 0. && thresh > 0. ) {
         h = threshH + etaCorrH * b * h;
      }

      // Endcap calibration   
   } else {
      // The energy correction
      a = e>0. ? F["aEndcap"](t) : 1.;
      b = e>0. ? F["bEndcap"](t) : F["cEndcap"](t);
      double thresh = e > 0. ? threshE : threshH;

      // Protection against negative calibration
      if ( a < -0.25 || b < -0.25 ) { 
         a = 1.;
         b = 1.;
         thresh = 0.;
      }

      // The new estimate of the true energy
      t = min(999.9,max(tt, thresh+a*e+b*h));

      // The angular correction 
      double dEta = std::abs( absEta - 1.5 );
      double etaPow = dEta * dEta * dEta * dEta;


      if ( e > 0. && thresh > 0. ) {
         if(absEta<2.5) {
            etaCorrE = 1. + F["aEtaEndcapEH"](t) + F["bEtaEndcapEH"](t)*F["cEtaEndcapEH"](absEta);
         }
         else {

            etaCorrE = 1. + F["aEtaEndcapEH"](t) + 1.3*F["bEtaEndcapEH"](t)*F["dEtaEndcapEH"](absEta);
         }

         etaCorrH = 1. + F["aEtaEndcapEH"](t) + F["bEtaEndcapEH"](t)*(0.04 + etaPow);
      } else {
         etaCorrE = 1.;
         if(absEta<2.5) {
            etaCorrH = 1. + F["aEtaEndcapH"](t) + F["bEtaEndcapH"](t)*F["cEtaEndcapH"](absEta);
         }
         else {
            etaCorrH = 1. + F["aEtaEndcapH"](t) + F["bEtaEndcapH"](t)*F["dEtaEndcapH"](absEta);
         }
      }

      //t = min(999.9,max(tt, thresh + etaCorrE*a*e + etaCorrH*b*h));

      if ( e > 0. && thresh > 0. ) 
         e = h > 0. ? threshE-threshH + etaCorrE * a * e : threshE + etaCorrE * a * e;
      if ( h > 0. && thresh > 0. ) {
         h = threshH + etaCorrH * b * h;
      }
   }

   // Protection
   if ( e < 0. || h < 0. ) {

      // Some protection against crazy calibration
      if ( e < 0. ) e = ee;
      if ( h < 0. ) h = hh;
   }

   // And that's it !


}
