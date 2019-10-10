#include <iostream>
using namespace std;

#include "TList.h"
#include "TObject.h"
#include "TKey.h"
#include "TFile.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
void TidyFit(string In, string Out);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input = CL.Get("Input");
   string Output = CL.Get("Output");

   TidyFit(Input, Output);

   return 0;
}

void TidyFit(string In, string Out)
{
   string FileName = CommandLine::Parse(In, '/')[1];
   vector<string> FileTag = CommandLine::Parse(FileName, '_');

   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);

   TKey *object = nullptr;
   while((object = (TKey *)next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');
      cout << Name << " " << Names[0] << endl;

      if(object->ReadObj()->InheritsFrom("TH1") == false)
         continue;

      if(Names.size() < 2)
         continue;

      string NewName = FileTag[0] + "_" + FileTag[2] + "_" + FileTag[3] + "_" + FileTag[4] + "_" + FileTag[1];

      FOut.cd();
      object->ReadObj()->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}





