#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]);
string Step1Simplification(string Input);
string Step2Simplification(string Input);
string Step3Simplification(string Input);
bool IsAllowed(char c);

int main(int argc, char *argv[])
{
   string Indices[14] = {"aZAdR", "aZAdI",
      "aAdR", "aAdI", "aZAR", "aZAI", "aZdR", "aZdI",
      "aAR", "aAI", "aZR", "aZI", "ahR", "ahI"};

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " NonZero1 NonZero2" << endl;
      return -1;
   }

   string NonZero1 = argv[1];
   string NonZero2 = argv[2];

   string FullExpression = "";
   ifstream in("ReplacedGeneralScalarSameLine.txt");
   in >> FullExpression;
   in.close();

   // FullExpression = "0/4096.+0/4096.+0/8192.-(el*0)/8192.-0/8192.+0/8192.";

   for(int i = 0; i < 14; i++)
   {
      if(Indices[i] == NonZero1 || Indices[i] == NonZero2)
         continue;

      int Position = FullExpression.find(Indices[i]);
      while(Position != string::npos)
      {
         FullExpression.replace(FullExpression.begin() + Position,
            FullExpression.begin() + (Position + Indices[i].size()), "0");
         Position = FullExpression.find(Indices[i]);
      }
   }

   string Temp = "";
   while(Temp != FullExpression)
   {
      Temp = FullExpression;
      FullExpression = Step1Simplification(FullExpression);
      FullExpression = Step2Simplification(FullExpression);
      FullExpression = Step3Simplification(FullExpression);
   }

   cout << FullExpression << endl;

   return 0;
}

string Step1Simplification(string Input)
{
   int N = 15;
   string LookFor[] = {"0+0", "0-0", "0*0", "(0)", "(-0", "pow0", ")-0", "(0+", "+0+", "(0-", "-0+", "+0-",
      "+0)", "-0)", "()"};
   string ReplaceAs[] = {"0", "0", "0", "0", "(0", "0", ")+0", "(", "+", "(-", "+", "-",
      ")", ")", "0"};

   string Temp = "";
   while(Temp != Input)
   {
      Temp = Input;

      for(int i = 0; i < N; i++)
      {
         int Position = Input.find(LookFor[i]);
         while(Position != string::npos)
         {
            Input.replace(Input.begin() + Position, Input.begin() + (Position + LookFor[i].size()), ReplaceAs[i]);
            Position = Input.find(LookFor[i]);
         }
      }
   }

   return Input;
}

string Step2Simplification(string Input)
{
   for(int i = 0; i < (int)Input.size() - 2; i++)
   {
      if((Input[i] == '0' && Input[i+1] == '*' && Input[i+2] == '(')
         || (Input[i] == '0' && Input[i+1] == '('))
      {
         int End = -1;

         int StartOffset = 3;
         if(Input[i+1] == '(')
            StartOffset = 2;

         int Layer = 1;
         for(int j = i + StartOffset; j < (int)Input.size(); j++)
         {
            if(Input[j] == '(')
               Layer = Layer + 1;
            if(Input[j] == ')')
            {
               Layer = Layer - 1;
               if(Layer == 0)
               {
                  End = j;
                  break;
               }
            }
         }

         if(End == -1)
         {
            cerr << "Something is wrong..." << endl;
            return "";
         }

         Input.erase(Input.begin() + (i + 1), Input.begin() + (End + 1));
      }
   }
   
   for(int i = 2; i < (int)Input.size(); i++)
   {
      if(Input[i] == '0' && Input[i-1] == '*' && Input[i-2] == ')')
      {
         int End = -1;

         int Layer = 1;
         for(int j = i - 3; j >= 0; j--)
         {
            if(Input[j] == ')')
               Layer = Layer + 1;
            if(Input[j] == '(')
            {
               Layer = Layer - 1;
               if(Layer == 0)
               {
                  End = j;
                  break;
               }
            }
         }

         if(End == -1)
         {
            cerr << "Something is wrong..." << endl;
            return "";
         }

         Input.erase(Input.begin() + End, Input.begin() + i);
      }
   }

   return Input;
}

string Step3Simplification(string Input)
{
   bool Changed = true;

   while(Changed == true)
   {
      Changed = false;

      if(Input == "0")
         break;

      vector<int> VariableStart, VariableEnd;
      
      if(IsAllowed(Input[0]) == true)
         VariableStart.push_back(-1);

      for(int i = 0; i < (int)Input.size() - 1; i++)
      {
         if(IsAllowed(Input[i]) == false && IsAllowed(Input[i+1]) == true)
            VariableStart.push_back(i);
         if(IsAllowed(Input[i]) == true && IsAllowed(Input[i+1]) == false)
            VariableEnd.push_back(i);
      }

      // if(VariableEnd[0] == 0)
      //    VariableEnd.erase(VariableEnd.begin());
      if(VariableStart.size() != VariableEnd.size())
         VariableEnd.push_back(Input.size() - 1);
      
      for(int i = 0; Changed == false && i < (int)VariableStart.size() - 1; i++)
      {
         if(VariableEnd[i] - VariableStart[i] != 1 || Input[VariableStart[i]+1] != '0')
            continue;
         if(VariableStart[i+1] - VariableEnd[i] != 1)
            continue;

         if(Input[VariableStart[i+1]] == '*' || Input[VariableStart[i+1]] == '/')
         {
            Input.erase(Input.begin() + VariableStart[i+1], Input.begin() + (VariableEnd[i+1] + 1));
            Changed = true;
            break;
         }
      }

      for(int i = 1; Changed == false && i < (int)VariableStart.size(); i++)
      {
         if((VariableEnd[i] - VariableStart[i] != 1) || (Input[VariableStart[i]+1] != '0'))
            continue;
         if(VariableStart[i] - VariableEnd[i-1] != 1)
            continue;

         if(Input[VariableStart[i]] == '*')
         {
            Input.erase(Input.begin() + (VariableStart[i-1] + 1), Input.begin() + (VariableStart[i] + 1));
            Changed = true;
            break;
         }
      }
   }

   return Input;
}

bool IsAllowed(char c)
{
   if(c <= 'Z' && c >= 'A')
      return true;
   if(c <= 'z' && c >= 'a')
      return true;
   if(c == '_')
      return true;
   if(c <= '9' && c >= '0')
      return true;
   if(c == '.')
      return true;
   return false;
}





