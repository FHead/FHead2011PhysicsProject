#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

int main()
{
   map<string, vector<string>> FileMap;

   ifstream fin("MatchedFiles");

   while(fin)
   {
      char ch[1048576] = "";
      fin.getline(ch, 1048575, '\n');
      stringstream str(ch);

      int Lumi = -1;
      string FileNoPU = "";
      string FilePU = "";

      str >> Lumi >> FileNoPU >> FilePU;

      if(Lumi < 0 || FileNoPU == "" || FilePU == "")
         continue;

      if(FileMap.find(FileNoPU) == FileMap.end())
         FileMap.insert(pair<string, vector<string>>(FileNoPU, vector<string>()));

      FileMap[FileNoPU].push_back(FilePU);
   }

   int Count = 0;
   for(auto iter : FileMap)
   {
      string NoPUFile = iter.first;
      if(iter.second.size() == 0)
         continue;

      sort(iter.second.begin(), iter.second.end());
      iter.second.erase(unique(iter.second.begin(), iter.second.end()), iter.second.end());

      string PUFile = "";

      if(iter.second.size() == 1)
         PUFile = "cp " + iter.second[0] + " PUFile.root";
      else
      {
         PUFile = "hadd PUFile.root";
         for(auto File : iter.second)
            PUFile = PUFile + " //" + File;
      }

      cout << "cat RunFile.sh \\" << endl;
      cout << "   | sed \"s#__PUFILE__#" << PUFile << "#\" \\" << endl;
      cout << "   | sed \"s#__NOPUFILE__#" << NoPUFile << "#\" \\" << endl;
      cout << "   | sed \"s#__ID__#" << Count << "#\" \\" << endl;
      cout << "   | bsub -J PUMatching" << endl;
      cout << endl;

      Count = Count + 1;
   }

   fin.close();

   return 0;
}

