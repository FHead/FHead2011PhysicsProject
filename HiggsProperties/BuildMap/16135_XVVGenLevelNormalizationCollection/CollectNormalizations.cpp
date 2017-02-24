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
   map<string, double> Total2;
   map<string, double> FileCount;

   string SignalSuffixes[72];
   SignalSuffixes[0]  = "A1ZZR";
   SignalSuffixes[1]  = "A1ZZI";
   SignalSuffixes[2]  = "A2ZZR";
   SignalSuffixes[3]  = "A2ZZI";
   SignalSuffixes[4]  = "A3ZZR";
   SignalSuffixes[5]  = "A3ZZI";
   SignalSuffixes[6]  = "A4ZZR";
   SignalSuffixes[7]  = "A4ZZI";
   SignalSuffixes[8]  = "A1ZVR";
   SignalSuffixes[9]  = "A1ZVI";
   SignalSuffixes[10] = "A2ZVR";
   SignalSuffixes[11] = "A2ZVI";
   SignalSuffixes[12] = "A3ZVR";
   SignalSuffixes[13] = "A3ZVI";
   SignalSuffixes[14] = "A4ZVR";
   SignalSuffixes[15] = "A4ZVI";
   SignalSuffixes[16] = "A1ZAR";
   SignalSuffixes[17] = "A1ZAI";
   SignalSuffixes[18] = "A2ZAR";
   SignalSuffixes[19] = "A2ZAI";
   SignalSuffixes[20] = "A3ZAR";
   SignalSuffixes[21] = "A3ZAI";
   SignalSuffixes[22] = "A4ZAR";
   SignalSuffixes[23] = "A4ZAI";
   SignalSuffixes[24] = "A1VZR";
   SignalSuffixes[25] = "A1VZI";
   SignalSuffixes[26] = "A2VZR";
   SignalSuffixes[27] = "A2VZI";
   SignalSuffixes[28] = "A3VZR";
   SignalSuffixes[29] = "A3VZI";
   SignalSuffixes[30] = "A4VZR";
   SignalSuffixes[31] = "A4VZI";
   SignalSuffixes[32] = "A1VVR";
   SignalSuffixes[33] = "A1VVI";
   SignalSuffixes[34] = "A2VVR";
   SignalSuffixes[35] = "A2VVI";
   SignalSuffixes[36] = "A3VVR";
   SignalSuffixes[37] = "A3VVI";
   SignalSuffixes[38] = "A4VVR";
   SignalSuffixes[39] = "A4VVI";
   SignalSuffixes[40] = "A1VAR";
   SignalSuffixes[41] = "A1VAI";
   SignalSuffixes[42] = "A2VAR";
   SignalSuffixes[43] = "A2VAI";
   SignalSuffixes[44] = "A3VAR";
   SignalSuffixes[45] = "A3VAI";
   SignalSuffixes[46] = "A4VAR";
   SignalSuffixes[47] = "A4VAI";
   SignalSuffixes[48] = "A1AZR";
   SignalSuffixes[49] = "A1AZI";
   SignalSuffixes[50] = "A2AZR";
   SignalSuffixes[51] = "A2AZI";
   SignalSuffixes[52] = "A3AZR";
   SignalSuffixes[53] = "A3AZI";
   SignalSuffixes[54] = "A4AZR";
   SignalSuffixes[55] = "A4AZI";
   SignalSuffixes[56] = "A1AVR";
   SignalSuffixes[57] = "A1AVI";
   SignalSuffixes[58] = "A2AVR";
   SignalSuffixes[59] = "A2AVI";
   SignalSuffixes[60] = "A3AVR";
   SignalSuffixes[61] = "A3AVI";
   SignalSuffixes[62] = "A4AVR";
   SignalSuffixes[63] = "A4AVI";
   SignalSuffixes[64] = "A1AAR";
   SignalSuffixes[65] = "A1AAI";
   SignalSuffixes[66] = "A2AAR";
   SignalSuffixes[67] = "A2AAI";
   SignalSuffixes[68] = "A3AAR";
   SignalSuffixes[69] = "A3AAI";
   SignalSuffixes[70] = "A4AAR";
   SignalSuffixes[71] = "A4AAI";

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
         line >> Values[0] >> Values[1];

         // Values[0] = Values[0] * (135 * 135 - 115 * 115);
         // Values[1] = Values[1] * (135 * 135 - 115 * 115);

         if(Total.find(ID + "_UUbar") == Total.end())
            Total.insert(pair<string, double>(ID + "_UUbar", 0));
         if(Total.find(ID + "_DDbar") == Total.end())
            Total.insert(pair<string, double>(ID + "_DDbar", 0));
         if(Count.find(ID + "_UUbar") == Count.end())
            Count.insert(pair<string, double>(ID + "_UUbar", 0));
         if(Count.find(ID + "_DDbar") == Count.end())
            Count.insert(pair<string, double>(ID + "_DDbar", 0));

         Total2[ID+"_UUbar"] = Total2[ID+"_UUbar"] + Event * Values[0] * Values[0];
         Total[ID+"_UUbar"] = Total[ID+"_UUbar"] + Event * Values[0];
         Count[ID+"_UUbar"] = Count[ID+"_UUbar"] + Event;
         FileCount[ID+"_UUbar"] = FileCount[ID+"_UUbar"] + 1;
         Total2[ID+"_DDbar"] = Total2[ID+"_DDbar"] + Event * Values[1] * Values[1];
         Total[ID+"_DDbar"] = Total[ID+"_DDbar"] + Event * Values[1];
         Count[ID+"_DDbar"] = Count[ID+"_DDbar"] + Event;
         FileCount[ID+"_DDbar"] = FileCount[ID+"_DDbar"] + 1;
      }
      if(IDX == "TT1")
      {
         for(int i = 0; i < 72; i++)
         {
            for(int j = 0; j < 72; j++)
            {
               string Suffix = "_" + SignalSuffixes[i] + "_" + SignalSuffixes[j];

               line >> Values[0];

               // Values[0] = Values[0] * (sqrt(2 * PI) * 2) * pow((120 * 120 - 0.1 * 0.1) / (120 * 120 - 4 * 4), 2);

               if(Total.find(ID+Suffix) == Total.end())
                  Total.insert(pair<string, double>(ID + Suffix, 0));
               if(Count.find(ID+Suffix) == Count.end())
                  Count.insert(pair<string, double>(ID + Suffix, 0));

               Total2[ID+Suffix] = Total2[ID+Suffix] + Event * Values[0] * Values[0];
               Total[ID+Suffix] = Total[ID+Suffix] + Event * Values[0];
               Count[ID+Suffix] = Count[ID+Suffix] + Event;
               FileCount[ID+Suffix] = FileCount[ID+Suffix] + 1;
            }
         }
      }
   }

   DataHelper DHFile("Normalization.dh");

   for(map<string, double>::iterator iter = Count.begin(); iter != Count.end(); iter++)
   {
      string ID = iter->first;
      double Average = Total[ID] / Count[ID];
      double RMS = sqrt((Total2[ID] - Count[ID] * Average * Average) / (Count[ID] - 1));

      DHFile[State][ID] = Average;
      DHFile[State]["Count_"+ID] = Count[ID];
      DHFile[State]["Error_"+ID] = RMS / sqrt(FileCount[ID]);
   }

   DHFile.SaveToFile("Normalization.dh");

   return 0;
}









