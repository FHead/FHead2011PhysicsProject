#include <iostream>
using namespace std;

#include "DataHelper.h"

int main()
{
   DataHelper DHFile("Yields.dh");

   string States[] =
      {"uubar_2e2mu", "uubar_4e", "ddbar_2e2mu", "ddbar_4e",
      "SMVV_2e2mu", "SMVV_4e", "5plet_2e2mu", "5plet_4e"}; 

   for(int i = 0; i < 13; i++)
   {
      string CutString = "CutA";
      CutString[3] = char('A' + i);

      for(int j = 0; j < 8; j++)
      {
         cout << DHFile[States[j]][CutString].GetDouble();
         if(j != 7)
            cout << " & ";
         else
            cout << " \\\\\\hline";
      }
      cout << endl;
   }

   return 0;
}



