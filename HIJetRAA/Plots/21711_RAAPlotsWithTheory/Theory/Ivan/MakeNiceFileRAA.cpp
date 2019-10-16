#include <iostream>
#include <fstream>

using namespace std;

// Assuming all three files have identical format.
int main(int argc, char *argv[])
{
   if (argc != 5)
   {
      cout << "Input Error: Need four files for radius 02, 04, and 08 + output file name." << endl;
      cout << argc << endl;
      return -1;
   }

   ifstream InFile02(argv[1]);
   ifstream InFile04(argv[2]);
   ifstream InFile08(argv[3]);
   ofstream OutFile(argv[4]);
   
   if(!InFile02.is_open()) {
      cout << "Input Error: Need R = 02 file." << endl;
      return -1;
   }
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

   while(InFile02 && InFile04 && InFile08)
   {
      double PT = 0;
      InFile02 >> PT;
      InFile04 >> PT;
      InFile08 >> PT;

      if(PT < 1)
         continue;

      double R02, RMin02, RMax02;
      InFile02 >> R02 >> RMax02 >> RMin02;
      double R04, RMin04, RMax04;
      InFile04 >> R04 >> RMax04 >> RMin04;
      double R08, RMin08, RMax08;
      InFile08 >> R08 >> RMax08 >> RMin08;
      
      OutFile << PT << " " << PT << " ";
      OutFile << R02 << " " << RMax02 << " " << RMin02 << " ";
      OutFile << "0 0 0 ";
      OutFile << R04 << " " << RMax04 << " " << RMin04 << " ";
      OutFile << "0 0 0 ";
      OutFile << R08 << " " << RMax08 << " " << RMin08 << " ";
      OutFile << "0 0 0 " << endl;
   }

   InFile02.close();
   InFile04.close();
   InFile08.close();
   OutFile.close();
   
   return 0;
}
