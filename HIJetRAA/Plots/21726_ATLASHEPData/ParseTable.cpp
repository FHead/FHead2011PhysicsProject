#include <iostream>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input = CL.Get("Input");
   string Output = CL.Get("Output");

   string Centrality = "NotSpecified";

   ifstream in(Input);

   TFile OutputFile(Output.c_str(), "RECREATE");

   TGraphAsymmErrors GStat, GSys, GLumi, GTAA;

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      if(ch[0] == '#')
      {
         for(int i = 0; ch[i] != '\n'; i++)
            if(ch[i] == ',')
               ch[i] = ' ';
         vector<string> Items = CommandLine::Parse(ch, ' ');

         if(Items[1] == "CENTRALITY" && Items.size() >= 4)
            Centrality = Items[4];

         continue;
      }
      if(ch[0] >= '0' && ch[0] <= '9')
      {
         vector<string> Items = CommandLine::Parse(ch, ',');
         vector<double> Numbers;
         for(string Item : Items)
            Numbers.push_back(atof(Item.c_str()));

         if(Items.size() != 12)
            continue;

         double X = Numbers[0];
         double EXL = Numbers[0] - Numbers[1];
         double EXH = Numbers[2] - Numbers[0];
         double Y = Numbers[3];

         int N = GSys.GetN();

         GSys.SetPoint(N, X, Y);
         GStat.SetPoint(N, X, Y);
         GLumi.SetPoint(N, X, Y);
         GTAA.SetPoint(N, X, Y);

         GSys.SetPointError(N, EXL, EXH, -Numbers[5], Numbers[4]);
         GStat.SetPointError(N, EXL, EXH, -Numbers[7], Numbers[6]);
         GTAA.SetPointError(N, EXL, EXH, -Numbers[9], Numbers[8]);
         GLumi.SetPointError(N, EXL, EXH, -Numbers[11], Numbers[10]);
      }
   }

   GSys.SetName(Form("ATLAS_Cent%s_Sys", Centrality.c_str()));
   GStat.SetName(Form("ATLAS_Cent%s_Stat", Centrality.c_str()));
   GLumi.SetName(Form("ATLAS_Cent%s_Lumi", Centrality.c_str()));
   GTAA.SetName(Form("ATLAS_Cent%s_TAA", Centrality.c_str()));

   GSys.Write();
   GStat.Write();
   GLumi.Write();
   GTAA.Write();

   OutputFile.Close();

   in.close();

   return 0;
}
