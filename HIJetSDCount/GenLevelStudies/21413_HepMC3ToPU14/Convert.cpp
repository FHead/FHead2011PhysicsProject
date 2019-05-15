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
   int EventCount;
public:
   Event()
   {
      EventCount = 0;
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
   void WriteEvent(ofstream &out)
   {
      out << "# event " << EventCount << endl;
      out << "weight " << W << endl;
      for(int i = 0; i < E[2]; i++)
      {
         if(P[8][i] < 1.1 && P[8][i] > 0.9)   // 1
            out << P[3][i] << " " << P[4][i] << " " << P[5][i] << " " << P[7][i] << " " << P[2][i] << " " << 0 << endl;
         if(P[8][i] < 4.1 && P[8][i] > 3.9)   // 4
            out << P[3][i] << " " << P[4][i] << " " << P[5][i] << " " << P[7][i] << " " << P[2][i] << " " << 0 << endl;
         if(P[8][i] < 3.1 && P[8][i] > 2.9)   // 3
            out << P[3][i] << " " << P[4][i] << " " << P[5][i] << " " << P[7][i] << " " << P[2][i] << " " << -1 << endl;
      }
      out << "end" << endl;
      EventCount = EventCount + 1;
   }
};

int main(int argc, char *argv[])
{
   string InputFile = "example.hepmc";
   string OutputFile = "example.root";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile.hepmc OutputFile.pu14" << endl;
      return -1;
   }

   InputFile = argv[1];
   OutputFile = argv[2];

   ifstream in(InputFile.c_str());
   ofstream out(OutputFile.c_str());
   
   bool BeforeFirstEvent = true;
   Event E;
   int PCount = 0;
   int VCount = 0;

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
            E.WriteEvent(out);
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
      E.WriteEvent(out);

   out.close();
   in.close();

   return 0;
}




