#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " NumberOfTries" << endl;
      return -1;
   }

   string Tag = argv[1];
   double NumberOfTries = 20;
   stringstream str(argv[1]);
   str >> NumberOfTries;

   vector<string> FileNames;
   ifstream ReadMapList((string("List_") + Tag + "Tries").c_str());
   while(ReadMapList)
   {
      string temp = "MomImHere.txt";
      ReadMapList >> temp;
      if(temp == "MomImHere.txt")
         continue;
      FileNames.push_back(temp);
   }

   vector<ifstream *> InputFiles;
   for(int i = 0; i < (int)FileNames.size(); i++)
      InputFiles.push_back(new ifstream(FileNames[i].c_str()));

   ofstream OutputFileMean(("Mean_" + Tag).c_str());
   ofstream OutputFileRMS(("RMS_" + Tag).c_str());

   vector<bool> Present(FileNames.size());
   vector<double> Numbers(FileNames.size());

   long long TotalCount = 20 * 20 * 20 * 20 * 20 * 20;
   for(long long i = 0; i < 20 * 20 * 20 * 20 * 20 * 20; i++)   // ...
   {
      if((i + 1) % 1000000 == 0)
         cout << "Processing " << i + 1 << "/" << TotalCount << endl;

      for(int j = 0; j < (int)FileNames.size(); j++)
      {
         Present[j] = false;
         if(InputFiles[j] == NULL)
            continue;

         *InputFiles[j] >> Numbers[j];
         Present[j] = true;
      }

      double Count = 0, Sum = 0, Sum2 = 0;
      for(int j = 0; j < (int)FileNames.size(); j++)
      {
         if(Present[j] == false)
            continue;

         Count = Count + 1;
         Sum = Sum + Numbers[j];
         Sum2 = Sum2 + Numbers[j] * Numbers[j];
      }

      double Mean = Sum / Count;
      double RMS = sqrt((Sum2 - Count * Mean * Mean) / Count);

      OutputFileMean << " " << Mean / NumberOfTries;
      OutputFileRMS << " " << RMS / NumberOfTries;

      if(i % 20 == 19)
      {
         OutputFileMean << endl;
         OutputFileRMS << endl;
      }
   }

   OutputFileMean.close();
   OutputFileRMS.close();

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(InputFiles[i] == NULL)
         continue;
      InputFiles[i]->close();
      delete InputFiles[i];
      InputFiles[i] = NULL;
   }

   return 0;
}








