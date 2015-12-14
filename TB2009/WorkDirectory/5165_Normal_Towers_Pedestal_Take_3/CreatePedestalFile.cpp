#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;

vector<string> ParseLine(char *line)
{
   stringstream str(line);

   vector<string> result;

   while(str)
   {
      string temp;
      str >> temp;
      result.push_back(temp);
   }

   return result;
}

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cout << "Usage: exe old_pedestal shift new_pedestal" << endl;
      return -1;
   }

   map<int, double> pedestalshift;

   ifstream shift(argv[2]);

   while(shift)
   {
      int ieta = 0;
      int iphi = 0;
      double amount = 0;

      shift >> ieta >> iphi >> amount;

      pedestalshift.insert(pair<int, double>(ieta * 1000 + iphi, amount));
   }

   shift.close();

   ifstream oldpedestal(argv[1]);
   ofstream newpedestal(argv[3]);

   while(oldpedestal)
   {
      char ch[10240] = "";
      oldpedestal.getline(ch, 10239, '\n');

      if(ch[0] == '#')
      {
         newpedestal << ch << endl;
         continue;
      }

      vector<string> parsed = ParseLine(ch);

      if(parsed.size() < 9)
      {
         newpedestal << ch << endl;
         continue;
      }

      int ieta = atoi(parsed[0].c_str());
      int iphi = atoi(parsed[1].c_str());
      int index = ieta * 1000 + iphi;

      if(pedestalshift.find(index) == pedestalshift.end())
      {
         newpedestal << ch << endl;
         continue;
      }

      newpedestal << setw(17) << parsed[0] << setw(16) << parsed[1];
      newpedestal << setw(16) << parsed[2] << setw(16) << parsed[3];

      newpedestal << setprecision(5) << setw(9) << atof(parsed[4].c_str()) + pedestalshift[index] / 4;
      newpedestal << setprecision(5) << setw(9) << atof(parsed[5].c_str()) + pedestalshift[index] / 4;
      newpedestal << setprecision(5) << setw(9) << atof(parsed[6].c_str()) + pedestalshift[index] / 4;
      newpedestal << setprecision(5) << setw(9) << atof(parsed[7].c_str()) + pedestalshift[index] / 4;

      newpedestal << setw(11) << parsed[8] << endl;
   }

   newpedestal.close();
   oldpedestal.close();

   return 0;
}

