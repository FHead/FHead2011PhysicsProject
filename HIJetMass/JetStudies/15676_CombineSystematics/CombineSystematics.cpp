#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   bool IsMC = false;

   vector<string> FileNames;
   if(IsMC == true)
   {
      FileNames.push_back("OutputFile_Ghost.root");
      FileNames.push_back("OutputFile_JER.root");
      FileNames.push_back("OutputFile_JetEta.root");
      FileNames.push_back("OutputFile_MB.root");
      FileNames.push_back("OutputFile_PTScale.root");
      FileNames.push_back("OutputFile_Rho.root");
      FileNames.push_back("OutputFile_NewSmear.root");
      FileNames.push_back("OutputFile_DR.root");
   }
   else
   {
      FileNames.push_back("OutputFile_Ghost.root");
      FileNames.push_back("OutputFile_JER.root");
      FileNames.push_back("OutputFile_PTScale.root");
      FileNames.push_back("OutputFile_DR.root");
   }

   vector<TFile *> Files;
   for(int i = 0; i < (int)FileNames.size(); i++)
      Files.push_back(new TFile(FileNames[i].c_str()));

   TFile OutputFile("CombinedSystematics.root", "RECREATE");

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iP = 0; iP < 6; iP++)
      {
         string GraphName = Form("GRatio_C%d_P%d", iC, iP);

         vector<TGraphAsymmErrors *> G;
         for(int i = 0; i < (int)FileNames.size(); i++)
            G.push_back((TGraphAsymmErrors *)Files[i]->Get(GraphName.c_str()));

         TGraphAsymmErrors NewGraph;
         NewGraph.SetNameTitle(GraphName.c_str(), "Combined systematics");

         for(int iB = 0; iB < 160; iB++)
         {
            double x, y, exl, exh, eyl, eyh;
            G[0]->GetPoint(iB, x, y);

            double el2 = 0, eh2 = 0;

            for(int i = 0; i < (int)FileNames.size(); i++)
            {
               eyl = G[i]->GetErrorYlow(iB);
               eyh = G[i]->GetErrorYhigh(iB);

               el2 = el2 + eyl * eyl;
               eh2 = eh2 + eyh * eyh;
            }

            NewGraph.SetPoint(iB, x, y);
            NewGraph.SetPointError(iB, 0, 0, sqrt(el2), sqrt(eh2));
         }

         NewGraph.Write();
      }
   }

   OutputFile.Close();

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      if(Files[i] != NULL)
      {
         Files[i]->Close();
         delete Files[i];
      }
   }

   return 0;
}
