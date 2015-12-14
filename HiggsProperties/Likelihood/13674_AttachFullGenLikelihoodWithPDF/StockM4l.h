#include <vector>

class StockM4l
{
private:
   std::vector<double> M4l;
public:
   StockM4l(int Seed = 31426, int Size = 100000);
   double operator [](int index);
private:
   void Initialize(int Seed, int Size);
};






