#include <iostream>
using namespace std;

#include "JetUncertainty.h"

int main()
{
   JetUncertainty Uncertainty("Autumn18_V8_MC_Uncertainty_AK4PFchs.txt");

   Uncertainty.SetJetPT(100);
   Uncertainty.SetJetEta(1.3);

   cout << "PT = 100, eta = 1.3, uncertainty = " << Uncertainty.GetUncertainty().first << endl;

   return 0;
}
