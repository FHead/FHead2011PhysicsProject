#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " Identifier" << endl;
      return -1;
   }

   string ModuleName = argv[1];

   bool Streaming = false;

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      string str = ch;

      if(Streaming == true)
      {
         if(str.find("----") != string::npos)
            Streaming = false;
      }
      
      if(Streaming == false)
      {
         if(str.find(ModuleName) == string::npos)
            continue;

         Streaming = true;
      }

      cout << str << endl;
   }

   return 0;
}




