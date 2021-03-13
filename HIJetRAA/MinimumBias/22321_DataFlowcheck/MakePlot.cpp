#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile File("OutputFile.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   double Bins[] = {75, 80, 85, 90, 95, 100, 105, 110, 120, 130, 140, 160};

   TProfile P2("P2", ";Jet PT (GeV);#Delta v_{2}", 11, Bins);
   TProfile P3("P3", ";Jet PT (GeV);#Delta v_{3}", 11, Bins);
   P2.SetStats(0);
   P3.SetStats(0);

   double J1PT;
   double V32, V33, V42, V43;

   Tree->SetBranchAddress("J1PT", &J1PT);
   Tree->SetBranchAddress("V32", &V32);
   Tree->SetBranchAddress("V33", &V33);
   Tree->SetBranchAddress("V42", &V42);
   Tree->SetBranchAddress("V43", &V43);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      P2.Fill(J1PT, V32 - V42);
      P3.Fill(J1PT, V33 - V43);
   }

   PdfFileHelper PdfFile("Result.pdf");
   PdfFile.AddTextPage("#Delta v_{N} in the presence of jets");

   PdfFile.AddPlot(P2);
   PdfFile.AddPlot(P3);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}




