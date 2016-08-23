#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "DataHelper.h"

int main()
{
   DataHelper DHFile("Efficiencies.dh");

   while(cin)
   {
      char ch[1048576] = "";
      cin.getline(ch, 1048575, '\n');

      stringstream str(ch);

      string Model = "";
      string State = "";
      vector<double> Efficiencies;

      str >> Model >> State;
      while(str)
      {
         double Temp = -10000;
         str >> Temp;
         if(Temp >= 0 && Temp <= 1)
            Efficiencies.push_back(Temp);
      }

      if(Model == "" || State == "")
         continue;

      for(int i = 0; i < (int)Efficiencies.size(); i++)
      {
         string CutString = "CutA";
         CutString[3] = char('A' + i);
         DHFile[Model+"_"+State][CutString] = Efficiencies[i];
      }
   }

   DHFile.SaveToFile("Efficiencies.dh");

   return 0;
}




