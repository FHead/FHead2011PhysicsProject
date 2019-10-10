#include <iostream>
using namespace std;

#include "TList.h"
#include "TObject.h"
#include "TKey.h"
#include "TFile.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
void TidyMu(string In, string Out, string Prefix);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input = CL.Get("Input");
   string Output = CL.Get("Output");
   bool IsMu = CL.GetBool("IsMu", false);
   bool IsSigma = CL.GetBool("IsSigma", false);
   bool IsSigmaMu = CL.GetBool("IsSigmaMu", false);

   if(IsMu)
      TidyMu(Input, Output, "Mu");
   else if(IsSigma)
      TidyMu(Input, Output, "Sigma");
   else if(IsSigmaMu)
      TidyMu(Input, Output, "SigmaMu");

   return 0;
}

void TidyMu(string In, string Out, string Prefix)
{
   TFile FIn(In.c_str());

   TFile FOut(Out.c_str(), "RECREATE");

   TList *List = FIn.GetListOfKeys();
   TIter next(List);

   map<string, int> Counts;
   
   TKey *object = nullptr;
   while((object = (TKey *)next()))
   {
      string Name = object->GetName();
      vector<string> Names = CommandLine::Parse(Name, '_');
      cout << Name << " " << Names[0] << endl;

      if(Names.size() < 6)
         continue;

      string NewName = Names[5];

      if(Counts.find(NewName) == Counts.end())
         Counts.insert(pair<string, int>(NewName, 1));
      else
         continue;
         // Counts[NewName] = Counts[NewName] + 1;

      // NewName = NewName + "_" + Counts[NewName];
      if(Prefix != "")
         NewName = Prefix + "_" + NewName;

      if(object->ReadObj()->InheritsFrom("TH1") == false)
         continue;

      FOut.cd();
      object->ReadObj()->Clone(NewName.c_str())->Write();
   }

   FOut.Close();

   FIn.Close();
}





