#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#define MAX 100000

class Event;
int main(int argc, char *argv[]);

class Event
{
public:
   int E[3];
   double ELocation[4];
   double W;
   double *P[9];
   double *V[6];
   double AHeavyIon[14];
   double AEventScale;
   double AProcessID;
   double AProcessVertex;
public:
   Event()
   {
      for(int i = 0; i < 9; i++)
         P[i] = new double[MAX];
      for(int i = 0; i < 6; i++)
         V[i] = new double[MAX];
   }
   ~Event() 
   {
      for(int i = 0; i < 9; i++)
         delete[] P[i];
      for(int i = 0; i < 6; i++)
         delete[] V[i];
   }
   void Clean()
   {
      for(int i = 0; i < 3; i++)    
         E[i] = 0;
      for(int i = 0; i < 4; i++)    
         ELocation[i] = 0;   
      W = 0;
      for(int i = 0; i < 9; i++)
         for(int j = 0; j < MAX; j++)
            P[i][j] = 0;
      for(int i = 0; i < 6; i++)
         for(int j = 0; j < MAX; j++)
            V[i][j] = 0;
      for(int i = 0; i < 14; i++)
         AHeavyIon[i] = 0;
      AEventScale = 0;
      AProcessID = 0;
      AProcessVertex = 0;
   }
   void DoBranch(TTree &T)
   {
      T.Branch("Run",       &E[0],      "Run/I");
      T.Branch("VCount",    &E[1],      "VCount/I");
      T.Branch("PCount",    &E[2],      "PCount/I");
      T.Branch("Location",  &ELocation, "Location[4]/D");
      T.Branch("W",         &W,         "W/D");
      T.Branch("PIndex",    P[0],      "PIndex[PCount]/D");
      T.Branch("PVertex",   P[1],      "PVertex[PCount]/D");
      T.Branch("PID",       P[2],      "PID[PCount]/D");
      T.Branch("Px",        P[3],      "Px[PCount]/D");
      T.Branch("Py",        P[4],      "Py[PCount]/D");
      T.Branch("Pz",        P[5],      "Pz[PCount]/D");
      T.Branch("PE",        P[6],      "PE[PCount]/D");
      T.Branch("PM",        P[7],      "PM[PCount]/D");
      T.Branch("PStatus",   P[8],      "PStatus[PCount]/D");
      T.Branch("VIndex",    V[0],      "VIndex[VCount]/D");
      T.Branch("VStatus",   V[1],      "VStatus[VCount]/D");
      T.Branch("Vx",        V[2],      "Vx[VCount]/D");
      T.Branch("Vy",        V[3],      "Vy[VCount]/D");
      T.Branch("Vz",        V[4],      "Vz[VCount]/D");
      T.Branch("Vt",        V[5],      "Vt[VCount]/D");
      T.Branch("AHeavyIon", &AHeavyIon, "AHeavyIon[14]/D");
      T.Branch("AEventScale", &AEventScale, "AEventScale/D");
      T.Branch("AProcessID", &AProcessID, "AProcessID/D");
      T.Branch("AProcessVertex", &AProcessVertex, "AProcessVertex/D");
   }
};

int main(int argc, char *argv[])
{
   string InputFile = "example.hepmc";
   string OutputFile = "example.root";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile.hepmc OutputFile.root" << endl;
      return -1;
   }

   InputFile = argv[1];
   OutputFile = argv[2];

   TFile File(OutputFile.c_str(), "RECREATE");

   TTree Tree("Tree", "Tree");

   ifstream in(InputFile.c_str());
   
   bool BeforeFirstEvent = true;
   Event E;
   int PCount = 0;
   int VCount = 0;

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
         PCount = 0;
         VCount = 0;

         for(int i = 0; i < 3; i++)
            str >> E.E[i];
         if(E.E[1] >= MAX)   E.E[1] = MAX;
         if(E.E[2] >= MAX)   E.E[2] = MAX;

         string Dummy = "";
         str >> Dummy;
         
         if(Dummy == "@")
            for(int i = 0; i < 4; i++)
               str >> E.ELocation[i];
      }
      if(Type == "W")
      {
         double Weight = -1;
         str >> Weight;
         if(Weight > 0)
            E.W = Weight;
         else
            E.W = 1;
      }
      if(Type == "A")
      {
         string AType;
         str >> AType >> AType;

         if(AType == "GenHeavyIon")             for(int i = 0; i < 14; i++) str >> E.AHeavyIon[i];
         if(AType == "signal_process_vertex")   str >> E.AProcessVertex;
         if(AType == "signal_process_id")       str >> E.AProcessID;
         if(AType == "event_scale")             str >> E.AEventScale;
      }
      if(Type == "V")
      {
         str >> E.V[0][VCount] >> E.V[1][VCount];

         // Do something here later if needed
         string ParticleIn = "";
         str >> ParticleIn;

         string Dummy = "";
         str >> Dummy;
         if(Dummy == "@")
            str >> E.V[2][VCount] >> E.V[3][VCount] >> E.V[4][VCount] >> E.V[5][VCount];

         VCount = VCount + 1;
      }
      if(Type == "P")
      {
         for(int i = 0; i < 9; i++)
            str >> E.P[i][PCount];
         PCount = PCount + 1;
      }
   }
   
   if(BeforeFirstEvent == false)
      Tree.Fill();

   in.close();

   Tree.Write();

   File.Close();

   return 0;
}




