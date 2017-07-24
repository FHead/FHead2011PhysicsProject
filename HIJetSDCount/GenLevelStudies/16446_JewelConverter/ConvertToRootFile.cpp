#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

class Event;
int main();

class Event
{
public:
   double E[13];
   string N[2];
   string U[2];
   double C[2];
   double H[13];
   double F[9];
   double V[9];
   int PCount;
   double P[12][10000];
public:
   Event() {}
   ~Event() {}
   void Clean()
   {
      for(int i = 0; i < 13; i++)   E[i] = 0;
      for(int i = 0; i < 2; i++)    N[i] = "";
      for(int i = 0; i < 2; i++)    U[i] = "";
      for(int i = 0; i < 2; i++)    C[i] = 0;
      for(int i = 0; i < 13; i++)   H[i] = 0;
      for(int i = 0; i < 9; i++)    F[i] = 0;
      for(int i = 0; i < 9; i++)    V[i] = 0;
      PCount = 0;
      for(int i = 0; i < 12; i++)
         for(int j = 0; j < 10000; j++)
            P[i][j] = 0;
   }
   void DoBranch(TTree &T)
   {
      T.Branch("E", &E, "E[13]/D");
      T.Branch("C", &C, "C[2]/D");
      T.Branch("H", &H, "H[13]/D");
      T.Branch("F", &F, "F[9]/D");
      T.Branch("V", &V, "V[9]/D");
      T.Branch("NP", &PCount, "NP/I");
      T.Branch("PIndex", &P[0], "PIndex[NP]/I");
      T.Branch("PID", &P[1], "PID[NP]/D");
      T.Branch("PX", &P[2], "PX[NP]/D");
      T.Branch("PY", &P[3], "PY[NP]/D");
      T.Branch("PZ", &P[4], "PZ[NP]/D");
      T.Branch("PE", &P[5], "PE[NP]/D");
      T.Branch("PM", &P[6], "PM[NP]/D");
      T.Branch("PStatus", &P[7], "PStatus[NP]/D");
      T.Branch("PUnknown1", &P[8], "PUnknown1[NP]/D");
      T.Branch("PUnknown2", &P[9], "PUnknown2[NP]/D");
      T.Branch("PUnknown3", &P[10], "PUnknown3[NP]/D");
      T.Branch("PUnknown4", &P[11], "PUnknown4[NP]/D");
   }
};

int main()
{
   string InputFile = "example-vac.hepmc";
   string OutputFile = "example-vac.root";

   TFile File(OutputFile.c_str(), "RECREATE");

   TTree Tree("Tree", "Tree");

   ifstream in(InputFile.c_str());
   
   bool BeforeFirstEvent = true;
   Event E;

   E.DoBranch(Tree);

   while(in)
   {
      char ch[1024];
      ch[0] = '\0';
      in.getline(ch, 1023, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream str(ch);
      string Type;
      str >> Type;

      if(BeforeFirstEvent == true && Type != "E")
         continue;

      if(Type == "E")
      {
         if(BeforeFirstEvent == false)
            Tree.Fill();
         BeforeFirstEvent = false;
         E.Clean();

         for(int i = 0; i < 13; i++)
            str >> E.E[i];
      }
      if(Type == "N")   for(int i = 0; i < 2; i++)    str >> E.N[i];
      if(Type == "U")   for(int i = 0; i < 2; i++)    str >> E.U[i];
      if(Type == "C")   for(int i = 0; i < 2; i++)    str >> E.C[i];
      if(Type == "H")   for(int i = 0; i < 13; i++)   str >> E.H[i];
      if(Type == "F")   for(int i = 0; i < 9; i++)    str >> E.F[i];
      if(Type == "V")   for(int i = 0; i < 9; i++)    str >> E.V[i];
      if(Type == "P")
      {
         for(int i = 0; i < 12; i++)
            str >> E.P[i][E.PCount];
         E.PCount = E.PCount + 1;
      }
   }

   in.close();

   Tree.Write();

   File.Close();

   return 0;
}




