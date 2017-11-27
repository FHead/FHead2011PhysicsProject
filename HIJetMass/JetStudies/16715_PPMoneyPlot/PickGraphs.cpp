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
   TFile F2(Form("Graphs_SD%d_PP6.root", SD));
   TFile F3(Form("Graphs_SD%d_PP8.root", SD));
   TFile F4(Form("Graphs_SD%d_PPHerwig.root", SD));

   TFile FOutput(Form("Graphs_SD%d_Picked.root", SD), "RECREATE");

   string Prefix[20] =
   {
      "MassData", "MassSmear", "MassDataSys", "MassSmearSys",
      "ZGData", "ZGSmear", "DRData", "DRSmear", "PTPTData", "PTPTSmear",
      "MassData0", "MassSmear0", "MassDataSys0", "MassSmearSys0",
      "ZGData0", "ZGSmear0", "DRData0", "DRSmear0", "PTPTData0", "PTPTSmear0"
   };
   
   string SourcePrefix[4] = {"Data", "PP6", "PP8", "PPHerwig"};

   for(int i = 0; i < 5; i++)   // centrality bin
   {
      for(int j = 0; j < 6; j++)   // PT bin
      {
         for(int k = 0; k < 20; k++)   // graph type
         {
            for(int iS = 0; iS < 4; iS++)   // sources
            {
               TGraphAsymmErrors *G = NULL;

               if(iS == 0)
                  G = (TGraphAsymmErrors *)F1.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
               if(iS == 1)
                  G = (TGraphAsymmErrors *)F2.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
               if(iS == 2)
                  G = (TGraphAsymmErrors *)F3.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));
               if(iS == 3)
                  G = (TGraphAsymmErrors *)F4.Get(Form("%s_%d_%d", Prefix[k].c_str(), i, j));

               if(G == NULL)
                  continue;

               G->Clone(Form("%s_%s_%d_%d", SourcePrefix[iS].c_str(), Prefix[k].c_str(), i, j))->Write();
            }
         }
      }
   }

   FOutput.Close();

   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}









