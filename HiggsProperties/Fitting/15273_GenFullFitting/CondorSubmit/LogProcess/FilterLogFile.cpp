#include <iostream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
   string Filter = "NNNNNNYNNNNN";
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " FloatFilter" << endl;
      cerr << "Example: " << argv[0] << " NNNNNNYNNNNN" << endl;
      return -1;
   }

   Filter = argv[1];

   map<int, int> Basis;
   multimap<int, vector<double> > Data;
   map<int, vector<double> > DataFirst;
   map<int, string> Float;

   while(cin)
   {
      int ID = -1;
      int basis = -1;
      vector<double> data(13);

      char ch[1048576] = "";
      cin.getline(ch, 1048575, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);
      str >> ID >> basis;
      for(int i = 0; i < 13; i++)
         str >> data[i];

      if(ID < 0 || basis < 0 || basis > 3)
         continue;

      if(Basis.find(ID) == Basis.end())
         Basis.insert(pair<int, int>(ID, basis));

      Data.insert(pair<int, vector<double> >(ID, data));

      if(Float.find(ID) == Float.end())
         Float.insert(pair<int, string>(ID, "NNNNNNNNNNNN"));

      if(DataFirst.find(ID) == DataFirst.end())
         DataFirst.insert(pair<int, vector<double> >(ID, data));
      else
      {
         for(int i = 0; i < 12; i++)
            if(DataFirst[ID][i] != data[i])
               Float[ID][i] = 'Y';
      }
   }

   for(multimap<int, vector<double> >::iterator iter = Data.begin();
      iter != Data.end(); iter++)
   {
      int ID = iter->first;
      vector<double> data = iter->second;

      if(Float[ID] != Filter)
         continue;

      cout << ID << " " << Basis[ID] << " " << Float[ID];
      for(int i = 0; i < (int)data.size(); i++)
         cout << " " << data[i];
      cout << endl;
   }

   return 0;
}






