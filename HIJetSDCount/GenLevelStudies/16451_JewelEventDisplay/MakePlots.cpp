#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

#include "JewelMessenger.h"

int main();
void AttachOneEvent(PdfFileHelper &PdfFile, JewelMessenger &M);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("ResultMedium.pdf");
   PdfFile.AddTextPage("Medium");

   TFile File("example.root");

   JewelMessenger M(File);

   int EntryCount = M.EntryCount();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      M.GetEntry(iE);

      if(iE >= 100)
         break;

      AttachOneEvent(PdfFile, M);
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AttachOneEvent(PdfFileHelper &PdfFile, JewelMessenger &M)
{
   PdfFile.AddTextPage("Begin new event");

   int Bin = 200;
   TH2D HAll("HAll", "all status;eta;phi", Bin, -5, 5, Bin, -M_PI, M_PI);
   TH2D HStatus1("HStatus1", "status 1;eta;phi", Bin, -5, 5, Bin, -M_PI, M_PI);
   TH2D HStatus2("HStatus2", "status 2;eta;phi", Bin, -5, 5, Bin, -M_PI, M_PI);
   TH2D HStatus3("HStatus3", "status 3;eta;phi", Bin, -5, 5, Bin, -M_PI, M_PI);

   HAll.SetStats(0);
   HStatus1.SetStats(0);
   HStatus2.SetStats(0);
   HStatus3.SetStats(0);

   for(int i = 0; i < M.ParticleCount; i++)
   {
      double PT = sqrt(M.PX[i] * M.PX[i] + M.PY[i] * M.PY[i]);
      double Momentum = sqrt(M.PX[i] * M.PX[i] + M.PY[i] * M.PY[i] + M.PZ[i] * M.PZ[i]);

      double Eta = 0.5 * log((Momentum + M.PZ[i]) / (Momentum - M.PZ[i]));
      double Phi = acos(M.PX[i] / PT);
      if(M.PY[i] < 0)
         Phi = -Phi;

      HAll.Fill(Eta, Phi, PT);
      if(M.Status[i] == 1)
         HStatus1.Fill(Eta, Phi, PT);
      if(M.Status[i] == 2)
         HStatus2.Fill(Eta, Phi, PT);
      if(M.Status[i] == 3)
         HStatus3.Fill(Eta, Phi, PT);
   }

   PdfFile.AddPlot(HAll, "colz");
   PdfFile.AddPlot(HStatus1, "colz");
   PdfFile.AddPlot(HStatus2, "colz");
   PdfFile.AddPlot(HStatus3, "colz");
}


