#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
using namespace std;

#include "DataHelper.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   string State = "ee";
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " StateString" << endl;
      cerr << "   I reads in stuff from stdin.  Pipe all results to me!" << endl;
      return -1;
   }

   State = argv[1];

   map<string, double> Total;
   map<string, double> Count;

   string SignalSuffixes[32];
   SignalSuffixes[0]  = "A1ZZR";
   SignalSuffixes[1]  = "A1ZZI";
   SignalSuffixes[2]  = "A2ZZR";
   SignalSuffixes[3]  = "A2ZZI";
   SignalSuffixes[4]  = "A3ZZR";
   SignalSuffixes[5]  = "A3ZZI";
   SignalSuffixes[6]  = "A4ZZR";
   SignalSuffixes[7]  = "A4ZZI";
   SignalSuffixes[8]  = "A1ZAR";
   SignalSuffixes[9]  = "A1ZAI";
   SignalSuffixes[10] = "A2ZAR";
   SignalSuffixes[11] = "A2ZAI";
   SignalSuffixes[12] = "A3ZAR";
   SignalSuffixes[13] = "A3ZAI";
   SignalSuffixes[14] = "A4ZAR";
   SignalSuffixes[15] = "A4ZAI";
   SignalSuffixes[16] = "A1AZR";
   SignalSuffixes[17] = "A1AZI";
   SignalSuffixes[18] = "A2AZR";
   SignalSuffixes[19] = "A2AZI";
   SignalSuffixes[20] = "A3AZR";
   SignalSuffixes[21] = "A3AZI";
   SignalSuffixes[22] = "A4AZR";
   SignalSuffixes[23] = "A4AZI";
   SignalSuffixes[24] = "A1AAR";
   SignalSuffixes[25] = "A1AAI";
   SignalSuffixes[26] = "A2AAR";
   SignalSuffixes[27] = "A2AAI";
   SignalSuffixes[28] = "A3AAR";
   SignalSuffixes[29] = "A3AAI";
   SignalSuffixes[30] = "A4AAR";
   SignalSuffixes[31] = "A4AAI";

   while(cin)
   {
      char ch[204800] = "";
      cin.getline(ch, 204799, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream line(ch);

      string ID = "";
      double Event = 0;
      vector<double> Values(15);

      line >> ID >> Event;

      if(Event == 0)
         continue;

      string IDX = ID;
      for(int i = 0; i < IDX.size(); i++)
         if((IDX[i] >= 'a' && IDX[i] <= 'z') || (IDX[i] >= 'A' && IDX[i] <= 'Z'))
            IDX[i] = 'T';

      if(IDX == "TT2")
      {
         line >> Values[0];

         Values[0] = Values[0] * (135 * 135 - 115 * 115);

         if(Total.find(ID) == Total.end())
            Total.insert(pair<string, double>(ID, 0));
         if(Count.find(ID) == Count.end())
            Count.insert(pair<string, double>(ID, 0));

         Total[ID] = Total[ID] + Event * Values[0];
         Count[ID] = Count[ID] + Event;
      }
      if(IDX == "TT1")
      {
         for(int i = 0; i < 32; i++)
         {
            for(int j = 0; j < 32; j++)
            {
               string Suffix = "_" + SignalSuffixes[i] + "_" + SignalSuffixes[j];

               line >> Values[0];

               Values[0] = Values[0] * (sqrt(2 * PI) * 2) * pow((120 * 120 - 3 * 3) / (120 * 120 - 4 * 4), 2);

               if(Total.find(ID+Suffix) == Total.end())
                  Total.insert(pair<string, double>(ID + Suffix, 0));
               if(Count.find(ID+Suffix) == Count.end())
                  Count.insert(pair<string, double>(ID + Suffix, 0));

               Total[ID+Suffix] = Total[ID+Suffix] + Event * Values[0];
               Count[ID+Suffix] = Count[ID+Suffix] + Event;
            }
         }
      }
   }

   DataHelper DHFile("Normalization.dh");

   for(map<string, double>::iterator iter = Count.begin(); iter != Count.end(); iter++)
   {
      string ID = iter->first;
      double Average = Total[ID] / Count[ID];

      DHFile[State][ID] = Average;
      DHFile[State]["Count_"+ID] = Count[ID];
   }

   DHFile.SaveToFile("Normalization.dh");

   return 0;
}









