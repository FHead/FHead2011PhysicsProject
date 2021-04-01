#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "SetStyle.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void AddRatio(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, string Title = "", string X = "", string Y = "");

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   bool DoPV = CL.GetBool("DoPV", true);
   double PT1Cut = CL.GetDouble("PT1", 16);
   double PT2Cut = CL.GetDouble("PT2", 8);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Double photon plots");

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("ObjectTree");

   double Reference1P[4], Reference2P[4];
   Tree->SetBranchAddress("Reference1P", &Reference1P);
   Tree->SetBranchAddress("Reference2P", &Reference2P);

   double Object1P[4], Object2P[4];
   if(DoPV == true)
   {
      Tree->SetBranchAddress("ObjectPV1P", &Object1P);
      Tree->SetBranchAddress("ObjectPV2P", &Object2P);
   }
   else
   {
      Tree->SetBranchAddress("ObjectNonPV1P", &Object1P);
      Tree->SetBranchAddress("ObjectNonPV2P", &Object2P);
   }

   int Bin = 40;
   double Max = 60;
   TH1D HReferencePT1("HReferencePT1", ";PT1;", Bin, 0, Max);
   TH1D HReferencePT2("HReferencePT2", ";PT2;", Bin, 0, Max);
   TH1D HLeadingMatchPT1("HLeadingMatchPT1", ";PT1;", Bin, 0, Max);
   TH1D HLeadingMatchPT2("HLeadingMatchPT2", ";PT2;", Bin, 0, Max);
   TH1D HLeadingPassPT1("HLeadingPassPT1", ";PT1;", Bin, 0, Max);
   TH1D HLeadingPassPT2("HLeadingPassPT2", ";PT2;", Bin, 0, Max);
   TH1D HSubleadingMatchPT1("HSubLeadingMatchPT1", ";PT1;", Bin, 0, Max);
   TH1D HSubleadingMatchPT2("HSubLeadingMatchPT2", ";PT2;", Bin, 0, Max);
   TH1D HSubleadingPassPT1("HSubLeadingPassPT1", ";PT1;", Bin, 0, Max);
   TH1D HSubleadingPassPT2("HSubLeadingPassPT2", ";PT2;", Bin, 0, Max);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      FourVector Reference1(Reference1P[0], Reference1P[1], Reference1P[2], Reference1P[3]);
      FourVector Reference2(Reference2P[0], Reference2P[1], Reference2P[2], Reference2P[3]);
      FourVector Object1(Object1P[0], Object1P[1], Object1P[2], Object1P[3]);
      FourVector Object2(Object2P[0], Object2P[1], Object2P[2], Object2P[3]);

      if(Reference1[0] < 0 || Reference2[0] < 0)
         continue;
      if(Reference1.GetAbsEta() > 1.479)
         continue;
      if(Reference2.GetAbsEta() > 1.479)
         continue;

      HReferencePT1.Fill(Reference1.GetPT());
      HReferencePT2.Fill(Reference2.GetPT());

      if(Object1[0] < 0)
         continue;

      HLeadingMatchPT1.Fill(Reference1.GetPT());
      HLeadingMatchPT2.Fill(Reference2.GetPT());

      if(Object1.GetPT() < PT1Cut)
         continue;

      HLeadingPassPT1.Fill(Reference1.GetPT());
      HLeadingPassPT2.Fill(Reference2.GetPT());

      if(Object2[0] < 0)
         continue;

      HSubleadingMatchPT1.Fill(Reference1.GetPT());
      HSubleadingMatchPT2.Fill(Reference2.GetPT());

      if(Object2.GetPT() < PT2Cut)
         continue;

      HSubleadingPassPT1.Fill(Reference1.GetPT());
      HSubleadingPassPT2.Fill(Reference2.GetPT());
   }

   File.Close();

   // PdfFile.AddTextPage("Leading");
   // PdfFile.AddPlot(HReferencePT1);
   // PdfFile.AddPlot(HLeadingMatchPT1);
   // PdfFile.AddPlot(HLeadingPassPT1);
   // PdfFile.AddPlot(HSubleadingMatchPT1);
   // PdfFile.AddPlot(HSubleadingPassPT1);
   
   // AddRatio(PdfFile, HLeadingMatchPT1, HReferencePT1, "Leading match", "Leading PT", "");
   // AddRatio(PdfFile, HLeadingPassPT1, HLeadingMatchPT1, "Leading turn on", "Leading PT", "");
   // AddRatio(PdfFile, HSubleadingMatchPT1, HLeadingPassPT1, "Subleading match", "Leading PT", "");
   // AddRatio(PdfFile, HSubleadingPassPT1, HSubleadingMatchPT1, "Subleading turn on", "Leading PT", "");
   
   PdfFile.AddTextPage("Subleading");
   // PdfFile.AddPlot(HReferencePT2);
   // PdfFile.AddPlot(HLeadingMatchPT2);
   // PdfFile.AddPlot(HLeadingPassPT2);
   // PdfFile.AddPlot(HSubleadingMatchPT2);
   // PdfFile.AddPlot(HSubleadingPassPT2);

   PdfFile.AddTextPage(
   {
      "Different steps:",
      "",
      "\"Leading match\":",
      "      Gen only => Gen only + leading leg match",
      "\"Leading turn on\":",
      "      Leading leg match => leading leg pass threshold",
      "\"Subleading match\":",
      "      Leading leg pass threshold",
      "      => leading leg pass threshold + subleading leg match",
      "\"Subleading turn on\":",
      "      Leading leg pass threshold + subleading leg match",
      "       => Both legs pass threshold"
   });

   AddRatio(PdfFile, HLeadingMatchPT2, HReferencePT2, "Leading match", "Subleading PT", "");
   AddRatio(PdfFile, HLeadingPassPT2, HLeadingMatchPT2, "Leading turn on", "Subleading PT", "");
   AddRatio(PdfFile, HSubleadingMatchPT2, HLeadingPassPT2, "Subleading match", "Subleading PT", "");
   AddRatio(PdfFile, HSubleadingPassPT2, HSubleadingMatchPT2, "Subleading turn on", "Subleading PT", "");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddRatio(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, string Title, string X, string Y)
{
   TGraphAsymmErrors G;
   G.Divide(&H1, &H2);

   G.SetTitle(Title.c_str());
   G.GetXaxis()->SetTitle(X.c_str());
   G.GetYaxis()->SetTitle(Y.c_str());

   G.SetLineWidth(2);

   PdfFile.AddPlot(G, "ap");
}


