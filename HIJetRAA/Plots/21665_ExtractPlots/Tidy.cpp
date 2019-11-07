#include <iostream>
using namespace std;

#include "TList.h"
#include "TObject.h"
#include "TKey.h"
#include "TFile.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
void TidyRAA(string In, string Out);
void TidyRRAA(string In, string Out);
void TidySysSpectra(string In, string Out);
void TidySpectra(string In, string Out);
void TidySysRAA(string In, string Out);
void TidySysRRAA(string In, string Out);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input      = CL.Get("Input");
   string Output     = CL.Get("Output");
   bool IsRAA        = CL.GetBool("IsRAA", false);
   bool IsRRAA       = CL.GetBool("IsRRAA", false);
   bool IsSysSpectra = CL.GetBool("IsSysSpectra", false);
   bool IsSpectra    = CL.GetBool("IsSpectra", false);
   bool IsSysRAA     = CL.GetBool("IsSysRAA", false);
   bool IsSysRRAA    = CL.GetBool("IsSysRRAA", false);

   if(IsRAA)
      TidyRAA(Input, Output);
   else if(IsRRAA)
      TidyRRAA(Input, Output);
   else if(IsSysSpectra)
      TidySysSpectra(Input, Output);
   else if(IsSpectra)
      TidySpectra(Input, Output);
   else if(IsSysRAA)
      TidySysRAA(Input, Output);
   else if(IsSysRRAA)
      TidySysRRAA(Input, Output);

   return 0;
}

void TidyRAA(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);

   string PreviousName = "";
   string PreviousNameSys = "";
   int Count = 1;
   
   TKey *object = nullptr;
   while((object = (TKey *)next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');
      cout << Name << " " << Names[0] << endl;

      if(Names.size() < 5)
         continue;

      string NewName = "";

      if(Names[0] != "Syst")
      {
         NewName = Names[3] + "_" + Names[5];
         if(NewName == PreviousName)
            continue;
         else
            PreviousName = NewName;
         NewName = NewName + "_1";
      }
      else
      {
         NewName = Names[4] + "_" + Names[6];
         if(NewName == PreviousNameSys)
            continue;
         else
            PreviousNameSys = NewName;
         NewName = NewName + "_2";
      }

      if(object->ReadObj()->InheritsFrom("TH1") == false)
         continue;

      FOut.cd();
      object->ReadObj()->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}

void TidyRRAA(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);
   
   TObject *object = nullptr;
   while((object = next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names.size() < 4)
         continue;

      string NewName;
      if(Names[0] == "Syst")
         NewName = Names[2] + "_" + Names[3] + "_2";
      else
         NewName = Names[3] + "_" + Names[4] + "_1";

      FOut.cd();
      FIn.Get(Name.c_str())->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}

void TidySysSpectra(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);
   
   TObject *object = nullptr;
   while((object = next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names.size() < 12)
         continue;

      string NewName = Names[2] + "_" + Names[4] + "_" + Names[12];

      FOut.cd();
      FIn.Get(Name.c_str())->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}

void TidySpectra(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);
   
   string PreviousName = "";
   string PreviousNameSys = "";
   
   TObject *object = nullptr;
   while((object = next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names.size() < 12)
         continue;

      string NewName = Names[2] + "_" + Names[4] + "_1";
      if(Names[0] == "Syst")
         NewName = Names[3] + "_" + Names[5] + "_2";

      if(Names[0] != "Syst")
      {
         if(PreviousName == NewName)
            continue;
         else
            PreviousName = NewName;
      }
      if(Names[0] == "Syst")
      {
         if(PreviousNameSys == NewName)
            continue;
         else
            PreviousNameSys = NewName;
      }

      FOut.cd();
      FIn.Get(Name.c_str())->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}

void TidySysRAA(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);
   
   TObject *object = nullptr;
   while((object = next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names.size() < 13)
         continue;

      string NewName = Names[3] + "_" + Names[5] + "_" + Names[13];

      FOut.cd();
      FIn.Get(Name.c_str())->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}

void TidySysRRAA(string In, string Out)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);
   
   TObject *object = nullptr;
   while((object = next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');

      if(Names.size() < 7)
         continue;

      string NewName = Names[1] + "_" + Names[2] + "_" + Names[4];

      FOut.cd();
      FIn.Get(Name.c_str())->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}





