#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " SD" << endl;
      return -1;
   }

   int SD = (argv[1][0] == '0') ? 0 : 7;

   TFile F1(Form("Graphs_SD%d_Data.root", SD));
   TFile F2(Form("Graphs_SD%d_DataPrescale_100.root", SD));
   TFile F3(Form("Graphs_SD%d_DataPrescale_80.root", SD));
   TFile F4(Form("Graphs_SD%d_DataPrescale_60.root", SD));

   TFile FOutput(Form("Graphs_SD%d_DataPicked.root", SD), "RECREATE");

   int Source[5][6] =
   {
      {4, 4, 4, 4, 4},   // 120-140
      {4, 3, 1, 1, 1},   // 140-160
      {3, 1, 1, 1, 1},   // 160-180
      {1, 1, 1, 1, 1},   // 180-200
      {1, 1, 1, 1, 1},   // 200-300
   };

   string Prefix[16] =
   {
      "MassData", "MassSmear", "MassDataSys", "MassSmearSys",
      "ZGData", "ZGSmear", "DRData", "DRSmear",
      "MassData0", "MassSmear0", "MassDataSys0", "MassSmearSys0",
      "ZGData0", "ZGSmear0", "DRData0", "DRSmear0"
   };

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         for(int k = 0; k < 16; k++)
         {
            TGraphAsymmErrors *G = NULL;

            if(Source[i][j] == 1)
               G = (TGraphAsymmErrors *)F1.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
            if(Source[i][j] == 2)
               G = (TGraphAsymmErrors *)F2.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
            if(Source[i][j] == 3)
               G = (TGraphAsymmErrors *)F3.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
            if(Source[i][j] == 4)
               G = (TGraphAsymmErrors *)F4.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));

            if(G == NULL)
               continue;

            G->Write();
         }
      }
   }

   FOutput.Close();

   F2.Close();
   F1.Close();

   return 0;
}









