#include <iostream>
#include <vector>
using namespace std;

#include "JetCorrectorParameters.h"
#include "FactorizedJetCorrector.h"

int main()
{
   JetCorrectorParameters ResJetPar("92X_upgrade2017_realistic_v11_L2L3Residual_AK4PF.txt");
   JetCorrectorParameters L3JetPar("92X_upgrade2017_realistic_v11_L3Absolute_AK4PF.txt");
   JetCorrectorParameters L2JetPar("92X_upgrade2017_realistic_v11_L2Relative_AK4PF.txt");
   JetCorrectorParameters L1JetPar("92X_upgrade2017_realistic_v11_L1FastJet_AK4PF.txt");

   vector<JetCorrectorParameters> vPar;
   vPar.push_back(L1JetPar);
   vPar.push_back(L2JetPar);
   vPar.push_back(L3JetPar);
   vPar.push_back(ResJetPar);

   FactorizedJetCorrector JetCorrector(vPar);

   JetCorrector.setJetEta(1.3);
   JetCorrector.setJetPt(25);
   cout << "Correction = " << JetCorrector.getCorrection() << endl;

   return 0;
}


