#include <iostream>
using namespace std;

#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TKey.h"
#include "TClass.h"

#include "PlotHelper2.h"

int main()
{
   PsFileHelper PsFile("PlotDump.ps");
   PsFile.AddTextPage("Dump of all the plots in file");

   TFile File("AddedMap_T003.root");

   TList *List = (TList *)File.GetListOfKeys();
   TIter NextKey(List);
   
   TKey *Key = (TKey *)NextKey();
   while(Key != NULL)
   {
      string Name = Key->GetName();
      string Type = File.Get(Key->GetName())->IsA()->GetName();

      TH1 *Histogram = (TH1 *)File.Get(Key->GetName());

      if(Type == "TH1D")
      {
         if(Name.find("Sig") != string::npos)
            Histogram->SetMinimum(0);
         PsFile.AddPlot(Histogram, "", false);
         
         if(Name.find("Sig") != string::npos)
            Histogram->SetMinimum(Histogram->GetMaximum() / 10000);
         if(Histogram->GetMaximum() > 0)
            PsFile.AddPlot(Histogram, "", true);
      }
      if(Type == "TH2D")
      {
         if(Name.find("Sig") != string::npos)
            Histogram->SetMinimum(0);
         PsFile.AddPlot(Histogram, "colz", false, false);
         
         if(Name.find("Sig") != string::npos)
            Histogram->SetMinimum(Histogram->GetMaximum() / 10000);
         if(Histogram->GetMaximum() > 0)
            PsFile.AddPlot(Histogram, "colz", false, true);
      }

      Key = (TKey *)NextKey();
   }

   File.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




