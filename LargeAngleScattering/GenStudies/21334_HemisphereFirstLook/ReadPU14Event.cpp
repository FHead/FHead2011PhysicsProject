#include <sstream>
using namespace std;

#include "ReadPU14Event.h"

PU14Event::PU14Event()
{
   Clear();
}

void PU14Event::Clear()
{
   P.clear();
   ID.clear();
   Type.clear();
   Weight = 1;
}

PU14Reader::PU14Reader()
{
   Initialized = false;
}

PU14Reader::PU14Reader(string filename)
{
   Initialized = false;
   Initialize(filename);
}

bool PU14Reader::Initialize(string filename)
{
   FileName = filename;
   InputFile.open(FileName);
   Initialized = true;
}

bool PU14Reader::ReadNextEvent()
{
   Event.Clear();

   bool Done = false;
   while(Done == false && InputFile)
   {
      char ch[10240];
      ch[0] = '\0';
      InputFile.getline(ch, 10239, '\n');

      stringstream str(ch);

      if(str.str() == "end")
         Done = true;
      else if(ch[0] == '#')
         continue;
      else
      {
         double Px = 0, Py = 0, Pz = 0, M = -1;
         int ID = -1, Type = -1;
         str >> Px >> Py >> Pz >> M >> ID >> Type;

         FourVector P(1, Px, Py, Pz);
         P[0] = sqrt(P.GetP2() + M * M);
         
         Event.P.push_back(P);
         Event.ID.push_back(ID);
         Event.Type.push_back(Type);
      }
   }

   if(Done == false)
      return false;
   return true;
}

PU14Event PU14Reader::GetEvent()
{
   return Event;
}

vector<PU14Event> PU14Reader::GetNEvents(int N)
{
   vector<PU14Event> Result;

   while(ReadNextEvent() && (N > 0 && Result.size() < N))
      Result.push_back(Event);

   return Result;
}


