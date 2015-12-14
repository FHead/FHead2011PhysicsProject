#include <iostream>
#include <sstream>
using namespace std;

#include "Code/DrawRandom.h"

int main()
{
   double Tally = 1;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      string Action = "";
      str >> Action;

      if(Action == "")
         continue;
      if(Action == "START")
         break;
      if(Action == "END")
         continue;

      if(Action == "SCALE")
      {
         double Value = 1;
         str >> Value;
         Tally = Tally * Value;
      }
      
      if(Action == "EVENT")
      {
         double Check = DrawRandom(0, 1);
         if(Check > Tally)
            continue;

         for(int i = 0; i < 9; i++)
         {
            double Value = -1;
            str >> Value;
            cout << " " << Value;
         }
         cout << endl;
      }
   }

   return 0;
}








