#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]);
int Decide(vector<double> &Theta, vector<double> &Sample);

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " D" << endl;
      return -1;
   }

   int D = atoi(argv[1]);

   vector<vector<double> > Samples;
   vector<int> Decision;

   while(cin)
   {
      char ch[1048576] = "";
      cin.getline(ch, 1048575, '\n');
      stringstream str(ch);

      int Y;
      vector<double> S(D);

      str >> Y;
      for(int i = 0; i < D; i++)
         str >> S[i];

      Samples.push_back(S);
      Decision.push_back(Y);
   }

   int LastChange = -1;
   int Current = 0;
   int TotalTest = 0;
   vector<double> Theta(D);

   while(LastChange != Current)
   {
      int Test = Decide(Theta, Samples[Current]);

      if(Test != Decision[Current])
      {
         for(int i = 0; i < D; i++)
            Theta[i] = Theta[i] + Decision[Current] * Samples[Current][i];

         LastChange = Current;
      }

      Current = (Current + 1) % Samples.size();
      TotalTest = TotalTest + 1;

      if(TotalTest >= 10000000)
      {
         cout << "Timed out after " << TotalTest << " tests" << endl;
         break;
      }
   }

   cout << "Result is out!" << endl;
   cout << "Theta = (";
   for(int i = 0; i < D; i++)
   {
      if(i != 0)
         cout << ", ";
      cout << Theta[i] / Theta[0];
   }
   cout << ")" << endl;

   return 0;
}

int Decide(vector<double> &Theta, vector<double> &Sample)
{
   double Test = 0;
   for(int i = 0; i < (int)Theta.size(); i++)
      Test = Test + Theta[i] * Sample[i];

   if(Test > 0)
      return 1;
   if(Test < 0)
      return -1;
   return 0;
}






