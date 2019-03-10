#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   
   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   double PhiMin = CL.GetDouble("phimin");
   double PhiMax = CL.GetDouble("phimax");
   double PTMin = CL.GetDouble("ptmin", 100);
   double PTMax = CL.GetDouble("ptmax", 200);
   double EtaMin = CL.GetDouble("etamin", -2.5);
   double EtaMax = CL.GetDouble("etamax", -1.7);
   string Algorithm = CL.Get("algorithm", "ak4pf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Response plot");

   TH1D HResponse("HResponse", ";PT/PT;#", 100, 0.0, 2.0);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get(Form("%s/t", Algorithm.c_str()));

   assert(Tree != NULL);

   vector<float> *JetPT = NULL, *JetEta = NULL, *JetPhi = NULL;
   vector<float> *RefPT = NULL, *RefEta = NULL, *RefPhi = NULL;

   Tree->SetBranchAddress("jtpt", &JetPT);
   Tree->SetBranchAddress("jteta", &JetEta);
   Tree->SetBranchAddress("jtphi", &JetPhi);
   Tree->SetBranchAddress("refpt", &RefPT);
   Tree->SetBranchAddress("refeta", &RefEta);
   Tree->SetBranchAddress("refphi", &RefPhi);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      for(int i = 0; i < (int)RefPT->size(); i++)
      {
         if((*RefPT)[i] < PTMin || (*RefPT)[i] > PTMax)
            continue;
         if((*RefEta)[i] < EtaMin || (*RefEta)[i] > EtaMax)
            continue;
         if((*RefPhi)[i] < PhiMin || (*RefPhi)[i] > PhiMax)
            continue;

         HResponse.Fill((*JetPT)[i] / (*RefPT)[i]);
      }
   }

   File.Close();

   PdfFile.AddPlot(HResponse, "", false);
   PdfFile.AddPlot(HResponse, "", true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}






