#include <string>
#include <iostream>
using namespace std;

#include "TFile.h"

#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cout << "Usage: " << argv[0] << " SourceFile Tag" << endl;
      return -1;
   }

   string SourceFile = argv[1];
   string Tag = argv[2];

   TFile F(SourceFile.c_str());

   PsFileHelper PsFile(Tag + ".ps");
   PsFile.AddTextPage(Tag);

   PsFile.AddHistogramFromFile(F, "HMRNew", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New005", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New010", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New015", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New020", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New025", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New030", "", true);
   PsFile.AddHistogramFromFile(F, "HR2New", "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}




