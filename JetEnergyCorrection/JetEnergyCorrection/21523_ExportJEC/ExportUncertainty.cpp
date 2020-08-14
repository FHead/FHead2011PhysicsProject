#include <iostream>
#include <vector>
using namespace std;

#include "CommandLine.h"

#include "JetUncertainty.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Version = CL.Get("Version");
   string Algorithm = CL.Get("Algorithm");

   string Dependent = CL.Get("Dependent");
   double Min = CL.GetDouble("Min");
   double Max = CL.GetDouble("Max");
   int NBin = CL.GetInt("NBin", 1000);

   double FixRho = CL.GetDouble("FixRho", 20);
   double FixPT = CL.GetDouble("FixPT", 100);
   double FixEta = CL.GetDouble("FixEta", 0.0);
   double FixPhi = CL.GetDouble("FixPhi", 0.0);
   double FixArea = CL.GetDouble("FixArea", 0.4 * 0.4 * M_PI);

   enum ModeType {Rho, PT, Eta, Phi, Area} Mode;

   if(Dependent == "Rho")   Mode = Rho;
   if(Dependent == "PT")    Mode = PT;
   if(Dependent == "Eta")   Mode = Eta;
   if(Dependent == "Phi")   Mode = Phi;

   string FileName = "JECDatabase/" + Version + "/" + Version + "_Uncertainty_" + Algorithm + ".txt";
   JetUncertainty JEU(FileName);

   string Tag = Dependent;
   if(Mode != PT)    Tag = Tag + Form("_PT%.02f", FixPT);
   if(Mode != Eta)   Tag = Tag + Form("_Eta%.02f", FixEta);

   int EtaBinCount = 40;
   double EtaBinEdge[] = {-5.4, -5.0, -4.4, -4.0, -3.5, -3.0, -2.8, -2.6, -2.4, -2.2, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.5, 4.0, 4.4, 5.0, 5.4};
   vector<double> EtaBins;
   for(int i = 0; i < EtaBinCount; i++)
   {
      EtaBins.push_back(EtaBinEdge[i] + 0.0001);
      EtaBins.push_back(EtaBinEdge[i+1] - 0.0001);
   }
   if(Mode == Eta)
      NBin = EtaBins.size() - 1;

   cout << "            \"" << Tag << "\": {Data: [";
   for(int i = 0; i <= NBin; i++)
   {
      double X;
      if(Mode == PT)
         X = exp(log(Min) + (log(Max) - log(Min)) / NBin * i);
      else if(Mode == Eta)
         X = EtaBins[i];
      else
         X = Min + (Max - Min) / NBin * i;

      JEU.SetJetPT(FixPT);
      JEU.SetJetEta(FixEta);
      JEU.SetJetPhi(FixPhi);
      JEU.SetRho(FixRho);
      JEU.SetJetArea(FixArea);

      if(Mode == Rho)   JEU.SetRho(X);
      if(Mode == PT)    JEU.SetJetPT(X);
      if(Mode == Eta)   JEU.SetJetEta(X);
      if(Mode == Phi)   JEU.SetJetPhi(X);
      if(Mode == Area)  JEU.SetJetArea(X);

      double Y = JEU.GetUncertainty().second;

      cout << "[" << X << ", " << Y << "]";
      if(i != NBin)
         cout << ",";
   }
   cout << "]}," << endl;

   return 0;
}
