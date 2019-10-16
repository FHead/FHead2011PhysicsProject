#include <iostream>
#include <fstream>

using namespace std;

// Assuming all three files have identical format.
int main(int argc, char *argv[])
{
   if (argc != 4)
   {
      cout << "Input Error: Need three files for radius 04 and 08 + output file name." << endl;
      cout << argc << endl;
      return -1;
   }

   ifstream InFile04(argv[1]);
   ifstream InFile08(argv[2]);
   ofstream OutFile(argv[3]);

   if(!InFile04.is_open()) {
      cout << "Input Error: Need R = 04 file." << endl;
      return -1;
   }
   if(!InFile08.is_open()) {
      cout << "Input Error: Need R = 08 file." << endl;
      return -1;
   }
   if(!OutFile.is_open()) {
      cout << "Output Error: Output file not open." << endl;
      return -1;
   }

   int Count = 0;

   while(InFile04 && InFile08)
   {
      double PT = 0;
      InFile04 >> PT;
      InFile08 >> PT;

      if(PT < 1)
         continue;

      double R04, RMin04, RMax04;
      InFile04 >> R04 >> RMax04 >> RMin04;
      double R08, RMin08, RMax08;
      InFile08 >> R08 >> RMax08 >> RMin08;
      
      OutFile << PT << " " << PT << " ";
      OutFile << "1 1 1 ";
      OutFile << "0 0 0 ";
      OutFile << R04 << " " << RMax04 << " " << RMin04 << " ";
      OutFile << "0 0 0 ";
      OutFile << R08 << " " << RMax08 << " " << RMin08 << " ";
      OutFile << "0 0 0 " << endl;
   }

   InFile04.close();
   InFile08.close();
   OutFile.close();
   
   return 0;
}
