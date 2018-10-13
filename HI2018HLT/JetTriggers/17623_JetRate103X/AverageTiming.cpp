#include <map>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
   map<string, int> Count;
   map<string, double> Total;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');
      stringstream str(ch);

      string Module;
      double Average;
      double WhenRun;

      str >> Module >> Average >> WhenRun;

      Count[Module] += 1;
      Total[Module] += Average;
   }

   for(pair<string, int> P : Count)
   {
      string M = P.first;
      cout << setw(20) << Total[M] / Count[M] << " " << M << endl;
   }
   
   return 0;
}




