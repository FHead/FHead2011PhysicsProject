#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int main();
double ExtractNumber(string str, int Field);

int main()
{
   ifstream in("ResultBeforeMerging.txt");

   map<pair<int, int>, vector<string> > TheMap;

   while(in)
   {
      char ch[1024] = "";
      in.getline(ch, 1023, '\n');

      if(ch[0] == '\0')
         continue;
      if(ExtractNumber(ch, 1) < 0)
         continue;
      if(ExtractNumber(ch, 8) < 0)
         continue;

      int M0 = (int)ExtractNumber(ch, 1);
      int M12 = (int)ExtractNumber(ch, 2);

      if(TheMap.find(pair<int, int>(M0, M12)) == TheMap.end())
         TheMap.insert(pair<pair<int, int>, vector<string> >(pair<int, int>(M0, M12), vector<string>()));
      TheMap[pair<int, int>(M0, M12)].push_back(ch);
   }

   in.close();

   for(map<pair<int, int>, vector<string> >::iterator iter = TheMap.begin(); iter != TheMap.end(); iter++)
   {
      if(iter->second.size() == 0)
         continue;
      if(iter->second.size() == 1)
      {
         cout << iter->second[0] << endl;
         continue;
      }

      int BestIndex = 0;
      double BestOne = ExtractNumber(iter->second[0], 4);

      for(int i = 1; i < (int)iter->second.size(); i++)
      {
         double Limit = ExtractNumber(iter->second[i], 4);
         if(Limit < BestOne)
         {
            BestIndex = i;
            BestOne = Limit;
         }
      }

      cout << iter->second[BestIndex] << endl;
   }

   return 0;
}

double ExtractNumber(string str, int Field)
{
   stringstream X(str);

   double Result = -1;
   for(int i = 1; i <= Field; i++)
   {
      Result = -1;
      X >> Result;
   }

   return Result;
}








