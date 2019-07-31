#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Event;
int main(int argc, char *argv[]);

class Event
{
public:
   double E[12];
   int ERand;
   double EWeight;
   string N[2];
   string U[2];
   double C[2];
   double H[13];
   double F[9];
   double V[9];
   int PCount;
   double P[12][10000];
   double EventCount;
public:
   Event() {}
   ~Event() {}
   void Clean()
   {
      for(int i = 0; i < 12; i++)   E[i] = 0;
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
   void WriteEvent(ofstream &out)
   {
      out << "# event " << EventCount << endl;
      out << "weight " << EWeight << endl;
      for(int i = 0; i < PCount; i++)
      {
         if(P[7][i] < 1.1 && P[7][i] > 0.9)   // 1
            out << P[2][i] << " " << P[3][i] << " " << P[4][i] << " " << P[6][i] << " " << P[1][i] << " 0" << endl;
         if(P[7][i] < 4.1 && P[7][i] > 3.9)   // 4
            out << P[2][i] << " " << P[3][i] << " " << P[4][i] << " " << P[6][i] << " " << P[1][i] << " 0" << endl;
         if(P[7][i] < 3.1 && P[7][i] > 2.9)   // 3
            out << P[2][i] << " " << P[3][i] << " " << P[4][i] << " " << P[6][i] << " " << P[1][i] << " -1" << endl;
      }
      out << "end" << endl;
      EventCount = EventCount + 1;
   }
};

int main(int argc, char *argv[])
{
   string InputFile = "example.hepmc";
   string OutputFile = "example.pu14";

   if(argc != 3 && argc != 2)
   {
      cerr << "Usage: " << argv[0] << " [InputFile.hepmc] OutputFile.pu14" << endl;
      return -1;
   }

   bool ReadFromSTD = false;

   if(argc == 3)
   {
      ReadFromSTD = false;
      InputFile = argv[1];
      OutputFile = argv[2];
   }
   else
   {
      ReadFromSTD = true;
      OutputFile = argv[1];
   }

   int Split = 2000;
   int Index = 0;
   int CurrentCount = 0;

   ifstream filein(InputFile.c_str());

   istream &in = (ReadFromSTD ? cin : filein);
   char filename[1000];
   sprintf(filename, "%s_%d.pu14", OutputFile.c_str(), Index);
   ofstream out(filename);

   bool BeforeFirstEvent = true;
   Event E;

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
         {
            E.WriteEvent(out);
            CurrentCount = CurrentCount + 1;

            if(CurrentCount >= Split)
            {
               CurrentCount = 0;
               Index = Index + 1;
               out.close();
               sprintf(filename, "%s_%d.pu14", OutputFile.c_str(), Index);
               out.open(filename);
            }
         }

         BeforeFirstEvent = false;
         E.Clean();

         for(int i = 0; i < 10; i++)
            str >> E.E[i];

         str >> E.E[10];
         if(E.E[10] != 0)
            for(int i = 0; i < E.E[10]; i++)
               str >> E.ERand;
         str >> E.E[11];
         if(E.E[11] != 0)
         {
            E.EWeight = 1;
            double Weight = 1;
            for(int i = 0; i < E.E[11]; i++)
            {
               str >> Weight;
               E.EWeight = E.EWeight * Weight;
            }
         }
         else
            E.EWeight = 1;
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

   if(BeforeFirstEvent == false)
      E.WriteEvent(out);

   filein.close();
   out.close();

   return 0;
}




