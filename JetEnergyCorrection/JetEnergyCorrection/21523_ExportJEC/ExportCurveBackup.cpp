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
   vector<string> Level = CL.GetStringVector("Level");

   string Dependent = CL.Get("Dependent");
   double Min = CL.GetDouble("Min");
   double Max = CL.GetDouble("Max");
   int NBin = CL.GetInt("NBin", 1000);
   bool JER = CL.GetBool("JER", false);
   bool ReducedEta = CL.GetBool("ReducedEta", false);

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

   vector<JetCorrector> JEC(Level.size());
   for(int i = 0; i < (int)Level.size(); i++)
   {
      string Database = "JECDatabase";
      if(JER == true)
         Database = "JRDatabase";
      string FileName = Database + "/" + Version + "/" + Version + "_" + Level[i] + "_" + Algorithm + ".txt";
      JEC[i].Initialize(FileName);
   }
   
   string Tag = Dependent;
   if(Mode != Rho)                  Tag = Tag + Form("_Rho%.02f", FixRho);
   if(Mode != PT)                   Tag = Tag + Form("_PT%.02f", FixPT);
   if(Mode != Eta)                  Tag = Tag + Form("_Eta%.02f", FixEta);
   if(Mode != Phi && FixPhi != 0)   Tag = Tag + Form("_Phi%.02f", FixPhi);

   int EtaBinCount = 82;
   double EtaBinEdge[] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -2.043, -1.93, -1.83, -1.74, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.74, 1.83, 1.93, 2.043, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191};
   if(ReducedEta == true)
      EtaBinEdge[0] = -5.000, EtaBinEdge[EtaBinCount] = 5.000;

   int JEREtaBinCount = 26;
   double JEREtaBinEdge[] = {-4.7, -3.2, -3.0, -2.8, -2.5, -2.3, -2.1, -1.9, -1.7, -1.3, -1.1, -0.8, -0.5, 0.0, 0.5, 0.8, 1.1, 1.3, 1.7, 1.9, 2.1, 2.3, 2.5, 2.8, 3.0, 3.2, 4.7};

   vector<double> EtaBins;
   if(JER == false)
   {
      for(int i = 0; i < EtaBinCount; i++)
      {
         EtaBins.push_back(EtaBinEdge[i] + 0.0001);
         EtaBins.push_back(EtaBinEdge[i+1] - 0.0001);
      }
   }
   else
   {
      for(int i = 0; i < JEREtaBinCount; i++)
      {
         EtaBins.push_back(JEREtaBinEdge[i] + 0.0001);
         EtaBins.push_back(JEREtaBinEdge[i+1] - 0.0001);
      }
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

      double TotalCorrection = 1;

      for(int j = 0; j < (int)Level.size(); j++)
      {
         JEC[j].SetJetPT(FixPT);
         JEC[j].SetJetEta(FixEta);
         JEC[j].SetJetPhi(FixPhi);
         JEC[j].SetRho(FixRho);
         JEC[j].SetJetArea(FixArea);

         if(Mode == Rho)   JEC[j].SetRho(X);
         if(Mode == PT)    JEC[j].SetJetPT(X);
         if(Mode == Eta)   JEC[j].SetJetEta(X);
         if(Mode == Phi)   JEC[j].SetJetPhi(X);
         if(Mode == Area)  JEC[j].SetJetArea(X);

         if(j > 0)
            JEC[j].SetJetPT(JEC[j-1].GetCorrectedPT());

         TotalCorrection = TotalCorrection * JEC[j].GetCorrection();
      }

      double Y = TotalCorrection;
      if(Y != Y)
         Y = -1.0;

      cout << "[" << X << ", " << Y << "]";
      if(i != NBin)
         cout << ",";
   }
   cout << "]}," << endl;

   return 0;
}
