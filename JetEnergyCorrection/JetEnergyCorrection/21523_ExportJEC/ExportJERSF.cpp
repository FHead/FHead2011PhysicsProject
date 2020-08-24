#include <iostream>
#include <vector>
using namespace std;

#include "CommandLine.h"

#include "JetCorrector.h"

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

   string Database = "JRDatabase";
   string FileName = Database + "/" + Version + "/" + Version + "_SF_" + Algorithm + ".txt";
   SingleJetCorrector JEC(FileName);
   
   string Tag = Dependent;
   if(Mode != Rho)                  Tag = Tag + Form("_Rho%.02f", FixRho);
   if(Mode != PT)                   Tag = Tag + Form("_PT%.02f", FixPT);
   if(Mode != Eta)                  Tag = Tag + Form("_Eta%.02f", FixEta);
   if(Mode != Phi && FixPhi != 0)   Tag = Tag + Form("_Phi%.02f", FixPhi);

   int JEREtaBinCount = 28;
 double JEREtaBinEdge[] = {-5.191, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.043, -1.930, -1.740, -1.305, -1.131, -0.783, -0.522, 0.000, 0.522, 0.783, 1.131, 1.305, 1.740, 1.930, 2.043, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 5.191};

   vector<double> EtaBins;
   for(int i = 0; i < JEREtaBinCount; i++)
   {
      EtaBins.push_back(JEREtaBinEdge[i] + 0.0001);
      EtaBins.push_back(JEREtaBinEdge[i+1] - 0.0001);
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

      JEC.SetJetPT(FixPT);
      JEC.SetJetEta(FixEta);
      JEC.SetJetPhi(FixPhi);
      JEC.SetRho(FixRho);
      JEC.SetJetArea(FixArea);
         
      if(Mode == Rho)   JEC.SetRho(X);
      if(Mode == PT)    JEC.SetJetPT(X);
      if(Mode == Eta)   JEC.SetJetEta(X);
      if(Mode == Phi)   JEC.SetJetPhi(X);
      if(Mode == Area)  JEC.SetJetArea(X);

      vector<double> Parameters = JEC.GetParameters();

      double Y = -1, YLow = -1, YHigh = -1;

      if(Parameters.size() == 3)
      {
         Y = Parameters[0];
         YLow = Parameters[1];
         YHigh = Parameters[2];
      }

      cout << "[" << X << ", " << Y << ", " << YLow << ", " << YHigh << "]";
      if(i != NBin)
         cout << ",";
   }
   cout << "]}," << endl;

   return 0;
}
