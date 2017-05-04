#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("TPVisualization.pdf");
   PdfFile.AddTextPage("Visualize TP");

   TFile File("Meow.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double M[158];
   for(int i = 0; i < 158; i++)
      Tree->SetBranchAddress(Form("B%d", i + 1), &M[i]);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      TH2D H(Form("H%d", iE), Form("Electron PT = %.2f, (ieta %.0f iphi %.0f);#Delta eta;#Delta phi", M[3], M[6], M[7]),
         5, -2.5, 2.5, 5, -2.5, 2.5);

      int Count = 0;
      for(int ieta = -2; ieta <= 2; ieta++)
      {
         for(int iphi = -2; iphi <= 2; iphi++)
         {
            if(M[10+Count*6] > 0)
               H.Fill(ieta, iphi, M[10+Count*6]);
            // if(M[11+Count*6] > 0)
            //    H.Fill(ieta, iphi, M[11+Count*6]);

            Count = Count + 1;
         }
      }

      H.SetStats(0);
      PdfFile.AddPlot(H, "colz text");
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   return 0;
}




