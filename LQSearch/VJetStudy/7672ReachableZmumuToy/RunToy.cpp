#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "SetStyle.h"

int main();
double GetAcceptance(double y, double PT);

int main()
{
   SetStyle();

   TFile F("Histogram.root", "RECREATE");

   TH2D HAcceptance("HAcceptance", "Acceptance;y;PT", 100, 0, 1.6, 100, 20, 1000);

   for(int i = 1; i <= 100; i++)
      for(int j = 1; j <= 100; j++)
         HAcceptance.SetBinContent(i, j,
            GetAcceptance(HAcceptance.GetXaxis()->GetBinCenter(i), HAcceptance.GetYaxis()->GetBinCenter(j)));

   HAcceptance.SetStats(0);

   PsFileHelper PsFile("ZAcceptance.ps");
   PsFile.AddTextPage("Probe-able part of Z");

   PsFile.AddPlot(HAcceptance, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HAcceptance.Write();
   F.Close();

   return 0;
}

double GetAcceptance(double y, double PT)
{
   double e2y = exp(-2 * y);
   double m = 91;

   double TotalTrial = 100000;
   double PassedTrial = 0;
   for(int i = 0; i < TotalTrial; i++)
   {
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(0, PI * 2);

      FourVector Muon1, Muon2;
      Muon1.SetSizeThetaPhi(m / 2, Theta, Phi);
      Muon2.SetSizeThetaPhi(m / 2, PI - Theta, PI + Phi);

      FourVector ZDirection;
      ZDirection[1] = PT;
      ZDirection[2] = 0;   // without loss of generality
      ZDirection[3] = sqrt((1 - e2y) * (1 - e2y) / 4 / e2y * (PT * PT + m * m));
      ZDirection[0] = sqrt(ZDirection.GetP2() + m * m);

      // if(i == 0)
      //    cout << y << " " << ZDirection.GetY() << endl;

      double Beta = ZDirection.GetP() / ZDirection[0];

      FourVector LabMuon1 = Muon1.Boost(ZDirection, Beta);
      FourVector LabMuon2 = Muon2.Boost(ZDirection, Beta);

      if(LabMuon1.GetPT() > 20 && LabMuon2.GetPT() > 20
         && LabMuon1.GetAbsEta() < 2.5 && LabMuon2.GetAbsEta() < 2.5)
         PassedTrial = PassedTrial + 1;
   }

   return PassedTrial / TotalTrial;
}



