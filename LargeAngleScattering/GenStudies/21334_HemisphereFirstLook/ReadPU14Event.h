#include <iostream>
#include <fstream>
#include <vector>

#include "Code/TauHelperFunctions3.h"

struct PU14Event
{
   std::vector<FourVector> P;
   std::vector<int> ID;
   std::vector<int> Type;
   double Weight;
public:
   PU14Event();
   void Clear();
};

class PU14Reader
{
public:
   bool Initialized;
   std::string FileName;
   std::ifstream InputFile;
   PU14Event Event;
public:
   PU14Reader();
   PU14Reader(std::string filename);
   bool Initialize(std::string filename);
   bool ReadNextEvent();
   PU14Event GetEvent();
   std::vector<PU14Event> GetNEvents(int N = -1);
};







