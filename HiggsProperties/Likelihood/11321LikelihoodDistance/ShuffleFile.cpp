//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   // Sanity check
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFileName OutputFileName" << endl;
      cerr << "Note - this is a simplistic implementation and WILL be slow for big arrays" << endl;
      return -1;
   }

   // Vector to hold everything
   vector<double> Numbers;

   // inputs
   ifstream in(argv[1]);
   while(in)
   {
      double Temp = -99999;
      in >> Temp;
      if(Temp < -99990)
         continue;

      Numbers.push_back(Temp);
   }
   in.close();

   // Small warning message for large array size
   if(Numbers.size() > 1000000)
      cerr << "Warning, array size is very large.  Expect slowness..." << endl;

   // Do the shuffling
   random_shuffle(Numbers.begin(), Numbers.end());
   random_shuffle(Numbers.begin(), Numbers.end());
   random_shuffle(Numbers.begin(), Numbers.end());
   random_shuffle(Numbers.begin(), Numbers.end());
   random_shuffle(Numbers.begin(), Numbers.end());

   // outputs
   ofstream out(argv[2]);
   for(int i = 0; i < Numbers.size(); i++)
      out << Numbers[i] << endl;
   out.close();

   return 0;
}
//---------------------------------------------------------------------------








