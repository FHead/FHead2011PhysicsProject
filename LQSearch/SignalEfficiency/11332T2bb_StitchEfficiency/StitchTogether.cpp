#include <iostream>
#include <fstream>
using namespace std;

int main()
{
   ifstream in025("Efficiency025");

   while(in025)
   {
      int m0 = -1, m12 = -1;
      double eff = -1, seff = -1;

      in025 >> m0 >> m12 >> eff >> seff;

      if(m0 < 0 || m12 < 0 || eff < 0 || seff < 0)
         continue;

      if(m0 * m0 - m12 * m12 < 350 * 350)
         cout << m0 << " " << m12 << " " << eff << " " << seff << endl;
   }

   in025.close();
   
   ifstream in042("Efficiency042");
   
   while(in042)
   {
      int m0 = -1, m12 = -1;
      double eff = -1, seff = -1;

      in042 >> m0 >> m12 >> eff >> seff;

      if(m0 < 0 || m12 < 0 || eff < 0 || seff < 0)
         continue;

      if(m0 * m0 - m12 * m12 >= 350 * 350)
         cout << m0 << " " << m12 << " " << eff << " " << seff << endl;
   }

   in042.close();

   return 0;
}






