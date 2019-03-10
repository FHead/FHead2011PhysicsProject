#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

int main();
void PrintJob(vector<string> &NoPU, vector<string> &PU, int Count);

int main()
{
   map<string, vector<string>> FileMap;

   int Bundle = 10;

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

   for(auto iter : FileMap)
   {
      sort(iter.second.begin(), iter.second.end());
      iter.second.erase(unique(iter.second.begin(), iter.second.end()), iter.second.end());
   }

   int BundleCount = 0;
   int Count = 0;

   vector<string> NoPUFileList;
   vector<string> PUFileList;

   for(auto iter : FileMap)
   {
      if(Bundle == 1)
      {
         NoPUFileList.clear();
         PUFileList.clear();

         NoPUFileList.push_back(iter.first);
         PUFileList = iter.second;
      }
      else
      {
         BundleCount = BundleCount + 1;
         
         NoPUFileList.push_back(iter.first);
         PUFileList.insert(PUFileList.end(), iter.second.begin(), iter.second.end());

         if(BundleCount % Bundle != 0)
            continue;
      }

      PrintJob(NoPUFileList, PUFileList, Count);

      Count = Count + 1;

      NoPUFileList.clear();
      PUFileList.clear();
   }
   if(NoPUFileList.size() > 0 && PUFileList.size() > 0)
      PrintJob(NoPUFileList, PUFileList, Count);

   fin.close();

   return 0;
}

void PrintJob(vector<string> &NoPU, vector<string> &PU, int Count)
{
   if(NoPU.size() == 0 | PU.size() == 0)
      return;

   sort(NoPU.begin(), NoPU.end());
   sort(PU.begin(), PU.end());

   NoPU.erase(unique(NoPU.begin(), NoPU.end()), NoPU.end());
   PU.erase(unique(PU.begin(), PU.end()), PU.end());

   string NoPUFile = "";
   string PUFile = "";

   if(NoPU.size() == 1)
      NoPUFile = "cp " + NoPU[0] + " NoPUFile.root";
   else
   {
      NoPUFile = "hadd -f -k NoPUFile.root";
      for(auto File : NoPU)
         NoPUFile = NoPUFile + " //" + File;
   }

   if(PU.size() == 1)
      PUFile = "cp " + PU[0] + " PUFile.root";
   else
   {
      PUFile = "hadd -f -k PUFile.root";
      for(auto File : PU)
         PUFile = PUFile + " //" + File;
   }

   cout << "cat RunFileBundle.sh \\" << endl;
   cout << "   | sed \"s#__PUFILE__#" << PUFile << "#\" \\" << endl;
   cout << "   | sed \"s#__NOPUFILE__#" << NoPUFile << "#\" \\" << endl;
   cout << "   | sed \"s#__ID__#" << Count << "#\" \\" << endl;
   cout << "   | bsub -J PUMatching" << endl;
   cout << endl;
}



