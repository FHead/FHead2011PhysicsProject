#include <iostream>
#include <cmath>
using namespace std;

#include "Code/DrawRandom.h"
#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   int N = CL.GetInt("N", 1000000);
   double Sigma = CL.GetDouble("Sigma", 0.15);
   double PhiSigma = CL.GetDouble("PhiSigma", 0.03);

   for(int i = 0; i < N; i++)
   {
      double JetPT = DrawRandom(15 - Sigma * 5, 100);
      double JetPT1 = JetPT * DrawGaussian(1, Sigma);
      double JetPT2 = JetPT * DrawGaussian(1, Sigma);
      double JetPhi1 = DrawGaussian(PhiSigma);
      double JetPhi2 = DrawGaussian(PhiSigma) + M_PI;

      FourVector J1, J2;
      J1.SetPtEtaPhi(JetPT1, DrawGaussian(0.02), JetPhi1);
      J2.SetPtEtaPhi(JetPT2, DrawGaussian(0.02), JetPhi2);

      FourVector Q = J1 + J2;
      FourVector P = (J1 - J2) * 0.5;

      double Phi = GetDPhi(Q, P);

      cout << JetPT << " " << JetPT1 << " " << JetPT2 << " " << JetPhi1 << " " << JetPhi2 << " " << Phi << " " << Q.GetPT() << " " << P.GetPT() << endl;
   }

   return 0;
}



