#include <vector>
using namespace std;

#include "Code/DrawRandom2.h"

#include "StockM4l.h"
   
StockM4l::StockM4l(int Seed, int Size)
{
   Initialize(Seed, Size);
}

double StockM4l::operator [](int index)
{
   if(M4l.size() == 0)
      return 0;
   return M4l[index%M4l.size()];
}

void StockM4l::Initialize(int Seed, int Size)
{
   if(Seed < 0)
      return;

   RandomMT Generator(Seed);

   M4l.resize(Size);
   for(int i = 0; i < Size; i++)
      M4l[i] = Generator.DrawGaussian(125, 2);
}



