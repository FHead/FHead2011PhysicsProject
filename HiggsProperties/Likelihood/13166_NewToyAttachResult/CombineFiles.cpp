#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char *argv[]);
map<int, vector<double> > ReadFile(string FileName);

int main(int argc, char *argv[])
{
   if(argc <= 5)
   {
      cerr << "Usage: " << argv[0] << " Input1 Input2 Output Weight1 Weight2" << endl;
      return -1;
   }

   string FileName1 = argv[1];
   string FileName2 = argv[2];
   string FileName = argv[3];
   double Weight1 = atof(argv[4]);
   double Weight2 = atof(argv[5]);

   map<int, vector<double> > Result1 = ReadFile(FileName1);
   map<int, vector<double> > Result2 = ReadFile(FileName2);

   vector<int> Indices;
   for(map<int, vector<double> >::iterator iter = Result1.begin(); iter != Result1.end(); iter++)
      Indices.push_back(iter->first);
   for(map<int, vector<double> >::iterator iter = Result2.begin(); iter != Result2.end(); iter++)
      Indices.push_back(iter->first);

   sort(Indices.begin(), Indices.end());
   Indices.erase(unique(Indices.begin(), Indices.end()), Indices.end());

   ofstream out(FileName.c_str());

   for(int i = 0; i < (int)Indices.size(); i++)
   {
      int Index = Indices[i];
      if(Result1.find(Index) == Result1.end())
         continue;
      if(Result2.find(Index) == Result2.end())
         continue;

      out << Index;

      vector<double> Values1 = Result1[Index];
      vector<double> Values2 = Result2[Index];

      int Size = min(Values1.size(), Values2.size());

      for(int j = 0; j < Size; j++)
      {
         double Answer = 0;
         if(Values1[j] == 0 || Values1[j] == 1)
            Answer = 0;
         if(Values2[j] == 0 || Values2[j] == 1)
            Answer = 0;

         Answer = (Values1[j] * Weight1 + Values2[j] * Weight2) / (Weight1 + Weight2);

         out << " " << Answer;
      }

      out << endl;
   }

   out.close();

   return 0;
}

map<int, vector<double> > ReadFile(string FileName)
{
   map<int, vector<double> > Result;

   ifstream in(FileName.c_str());

   while(in)
   {
      char line[10240] = {0};
      in.getline(line, 10239, '\n');

      stringstream str(line);

      int Index = -1;
      vector<double> Values;

      str >> Index;
      if(Index < 0)
         continue;
      if(Result.find(Index) != Result.end())
         continue;

      while(str)
      {
         double Value = -9999;
         str >> Value;
         if(Value > -9998.9999)
            Values.push_back(Value);
      }

      Result.insert(pair<int, vector<double> >(Index, Values));
   }

   in.close();

   return Result;
}




