#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main();
string Step1Simplification(vector<string> &Keywords, string Input);
string Step2Simplification(vector<string> &Keywords, string Input);
bool CheckKeyword(vector<string> &Keywords, string Input);
bool IsAllowed(char c);

int main()
{
   string String = "";
   // ifstream in("ReplacedGeneralScalarSameLine.txt");
   ifstream in("AfterCleaning2");
   in >> String;

   vector<string> Keywords;
   Keywords.push_back("aAR");     Keywords.push_back("aAI");
   Keywords.push_back("aAdR");    Keywords.push_back("aAdI");
   Keywords.push_back("aZAR");    Keywords.push_back("aZAI");
   Keywords.push_back("aZAdR");   Keywords.push_back("aZAdI");
   Keywords.push_back("aZR");     Keywords.push_back("aZI");
   Keywords.push_back("aZdR");    Keywords.push_back("aZdI");
   Keywords.push_back("ahR");     Keywords.push_back("ahI");

   string Temp = String;
   do
   {
      Temp = String;
      String = Step1Simplification(Keywords, String);
      String = Step2Simplification(Keywords, String);
   } while(Temp != String);

   cout << String << endl;

   return 0;
}

string Step1Simplification(vector<string> &Keywords, string Input)
{
   bool Changed = true;
   while(Changed == true)
   {
      Changed = false;

      vector<int> Beginnings;

      for(int i = 0; i < (int)Input.size(); i++)
      {
         if(Input[i] == '(')
         {
            Beginnings.push_back(i);
            continue;
         }

         if(Input[i] == ')')
         {
            int Start = Beginnings[Beginnings.size()-1];
            int End = i;

            if(CheckKeyword(Keywords, Input.substr(Start, End - Start + 1)) == false)
            {
               Input.erase(Input.begin() + Start, Input.begin() + End + 1);
               Input.insert(Input.begin() + Start, 'X');
               i = Start;
               Changed = true;
            }

            Beginnings.pop_back();
         }
      }
   }

   return Input;
}

string Step2Simplification(vector<string> &Keywords, string Input)
{
   bool Changed = true;

   while(Changed == true)
   {
      Changed = false;

      vector<int> VariableStart, VariableEnd;
      for(int i = 0; i < (int)Input.size() - 1; i++)
      {
         if(IsAllowed(Input[i]) == false && IsAllowed(Input[i+1]) == true)
            VariableStart.push_back(i);
         if(IsAllowed(Input[i]) == true && IsAllowed(Input[i+1]) == false)
            VariableEnd.push_back(i);
      }

      if(VariableEnd[0] == 0)
         VariableEnd.erase(VariableEnd.begin());
      if(VariableStart.size() != VariableEnd.size())
         VariableEnd.push_back(Input.size() - 1);

      /*
      cout << VariableStart.size() << " " << VariableEnd.size() << endl;
      for(int i = 0; i < (int)VariableStart.size(); i++)
         cout << " " << VariableStart[i];
      cout << endl;
      for(int i = 0; i < (int)VariableEnd.size(); i++)
         cout << " " << VariableEnd[i];
      cout << endl;
      */

      for(int i = 0; i < (int)VariableStart.size() - 1; i++)
      {
         if(CheckKeyword(Keywords, Input.substr(VariableStart[i] + 1, VariableEnd[i] - VariableStart[i])) == true)
            continue;
         if(CheckKeyword(Keywords, Input.substr(VariableStart[i+1] + 1, VariableEnd[i+1] - VariableStart[i+1])) == true)
         {
            i = i + 1;
            continue;
         }

         if(VariableStart[i+1] != VariableEnd[i] + 1)
            continue;

         if(Input[VariableStart[i+1]] == '*' || Input[VariableStart[i+1]] == '/')
         {
            Input.erase(Input.begin() + (VariableStart[i] + 1), Input.begin() + (VariableEnd[i+1] + 1));
            Input.insert(Input.begin() + (VariableStart[i] + 1), 'X');
            Changed = true;
            break;
         }
         if((Input[VariableStart[i+1]] == '+' || Input[VariableStart[i+1]] == '-')
            && Input[VariableStart[i]] != '*' && Input[VariableStart[i]] != '/'
            && Input[VariableEnd[i+1]+1] != '*' && Input[VariableEnd[i+1]+1] != '/')
         {
            Input.erase(Input.begin() + (VariableStart[i] + 1), Input.begin() + (VariableEnd[i+1] + 1));
            Input.insert(Input.begin() + (VariableStart[i] + 1), 'X');
            Changed = true;
            break;
         }
      }
   }

   return Input;
}

bool CheckKeyword(vector<string> &Keywords, string Input)
{
   for(int i = 0; i < (int)Keywords.size(); i++)
      if(Input.find(Keywords[i]) != string::npos)
         return true;

   return false;
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
   return false;
}


