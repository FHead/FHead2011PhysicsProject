#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

class Efficiency;
int main();
map<pair<int, int>, Efficiency> ReadResult(string FileName);

class Efficiency
{
public:
   int M0;
   int M12;
   double CentralEfficiency;
   double UpPercent;
   double DownPercent;
public:
   Efficiency() : M0(0), M12(0), CentralEfficiency(0), UpPercent(0), DownPercent(0) {}
};

int main()
{
   TFile F("Output.root", "RECREATE");

   map<pair<int, int>, Efficiency> CTEQResult = ReadResult("CTEQResult");
   map<pair<int, int>, Efficiency> MRSTResult = ReadResult("MRSTResult");
   map<pair<int, int>, Efficiency> NNPDFResult = ReadResult("NNPDFResult");

   TH2D HDuoCentral("HDuoCentral", "Duo central efficiency", 50, 0, 1250, 50, 0, 1250);
   TH2D HDuoRelative("HDuoRelative", "Duo relative efficiency", 50, 0, 1250, 50, 0, 1250);
   TH2D HCentral("HCentral", "Central efficiency", 50, 0, 1250, 50, 0, 1250);
   TH2D HRelative("HRelative", "Relative efficiency", 50, 0, 1250, 50, 0, 1250);

   for(map<pair<int, int>, Efficiency>::iterator iter = CTEQResult.begin(); iter != CTEQResult.end(); iter++)
   {
      pair<int, int> index = iter->first;

      if(MRSTResult.find(index) == MRSTResult.end())
         continue;
      if(NNPDFResult.find(index) == NNPDFResult.end())
         continue;

      double CTEQLow = CTEQResult[index].CentralEfficiency * (1 - CTEQResult[index].DownPercent);
      double CTEQHigh = CTEQResult[index].CentralEfficiency * (1 + CTEQResult[index].UpPercent);
      double MRSTLow = MRSTResult[index].CentralEfficiency * (1 - MRSTResult[index].DownPercent);
      double MRSTHigh = MRSTResult[index].CentralEfficiency * (1 + MRSTResult[index].UpPercent);
      double NNPDFLow = NNPDFResult[index].CentralEfficiency * (1 - NNPDFResult[index].DownPercent);
      double NNPDFHigh = NNPDFResult[index].CentralEfficiency * (1 + NNPDFResult[index].UpPercent);

      if(CTEQLow > CTEQHigh)     swap(CTEQLow, CTEQHigh);
      if(MRSTLow > MRSTHigh)     swap(MRSTLow, MRSTHigh);
      if(NNPDFLow > NNPDFHigh)   swap(NNPDFLow, NNPDFHigh);

      double DuoLow = min(CTEQLow, MRSTLow);
      double DuoHigh = max(CTEQHigh, MRSTHigh);
      double Low = min(min(CTEQLow, MRSTLow), NNPDFLow);
      double High = max(max(CTEQHigh, MRSTHigh), NNPDFHigh);

      cout << "[Verbose] M0 = " << index.first << ", M12 = " << index.second << endl;
      cout << "[Verbose] CTEQ: " << CTEQLow << " ~ " << CTEQHigh << endl;
      cout << "[Verbose] MRST: " << MRSTLow << " ~ " << MRSTHigh << endl;
      cout << "[Verbose] NNPDF: " << NNPDFLow << " ~ " << NNPDFHigh << endl;
      cout << "[Verbose] Total: " << Low << " ~ " << High << endl;

      HDuoCentral.Fill(index.first, index.second, (DuoHigh + DuoLow) / 2);
      HDuoRelative.Fill(index.first, index.second, (DuoHigh - DuoLow) / (DuoHigh + DuoLow));
      HCentral.Fill(index.first, index.second, (High + Low) / 2);
      HRelative.Fill(index.first, index.second, (High - Low) / (High + Low));
   }

   HDuoCentral.Write();
   HDuoRelative.Write();
   HCentral.Write();
   HRelative.Write();

   F.Close();

   return 0;
}

map<pair<int, int>, Efficiency> ReadResult(string FileName)
{
   map<pair<int, int>, Efficiency> Result;

   ifstream in(FileName.c_str());

   while(in)
   {
      Efficiency newone;

      in >> newone.M0 >> newone.M12 >> newone.CentralEfficiency >> newone.UpPercent >> newone.DownPercent;

      if(newone.M0 > 0 && newone.M12 > 0)
      {
         pair<int, int> index(newone.M0, newone.M12);

         Result.insert(pair<pair<int, int>, Efficiency>(index, newone));
      }
   }

   in.close();

   return Result;
}




