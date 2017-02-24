#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

int main()
{
   int N = 5;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      string Label = "";
      str >> Label;

      if(Label == "")
         continue;

      double SumX = 0, SumY = 0, SumXX = 0, SumYY = 0;

      for(int i = 0; i < N; i++)
      {
         double X = 0, Y = 0;
         str >> X >> Y;

         SumX = SumX + X;
         SumXX = SumXX + X * X;
         SumY = SumY + Y;
         SumYY = SumYY + Y * Y;
      }

      cout << Label
         << " " << SumX / N << " " << sqrt((SumXX - SumX * SumX / N) / (N - 1))
         << " " << SumY / N << " " << sqrt((SumYY - SumY * SumY / N) / (N - 1)) << endl;
   }

   return 0;
}




