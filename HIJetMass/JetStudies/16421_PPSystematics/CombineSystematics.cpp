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
   int SD = 7;
   bool IsMC = false;

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " SD=(0|7) IsMC=(Y|N)" << endl;
      return -1;
   }

   SD = ((argv[1][0] == '0') ? 0 : 7);
   IsMC = ((argv[2][0] == 'Y') ? true : false);

   vector<string> FileNames;
   if(IsMC == true)
   {
      FileNames.push_back(Form("OutputFile_PP6_JER_%d.root", SD));
      FileNames.push_back(Form("OutputFile_PP6_JES_%d.root", SD));
      // FileNames.push_back(Form("OutputFile_PP6_JetEta_%d.root", SD));
      FileNames.push_back(Form("OutputFile_PP6_DR_%d.root", SD));
      // FileNames.push_back(Form("OutputFile_PP6_QuarkGluon_%d.root", SD));
   }
   else
   {
      FileNames.push_back(Form("OutputFile_PP6_JER_%d.root", SD));
      FileNames.push_back(Form("OutputFile_PP6_JES_%d.root", SD));
      // FileNames.push_back(Form("OutputFile_PP6_JetEta_%d.root", SD));
      FileNames.push_back(Form("OutputFile_PP6_DR_%d.root", SD));
   }

   vector<TFile *> Files;
   for(int i = 0; i < (int)FileNames.size(); i++)
      Files.push_back(new TFile(FileNames[i].c_str()));

   TFile OutputFile(Form("CombinedSystematics_%d_%c.root", SD, (IsMC ? 'Y' : 'N')), "RECREATE");

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

            double totaly = 0;

            for(int i = 0; i < (int)FileNames.size(); i++)
            {
               eyl = G[i]->GetErrorYlow(iB);
               eyh = G[i]->GetErrorYhigh(iB);

               el2 = el2 + eyl * eyl;
               eh2 = eh2 + eyh * eyh;

               G[i]->GetPoint(iB, x, y);
               totaly = totaly + y;
            }

            NewGraph.SetPoint(iB, x, totaly);
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
