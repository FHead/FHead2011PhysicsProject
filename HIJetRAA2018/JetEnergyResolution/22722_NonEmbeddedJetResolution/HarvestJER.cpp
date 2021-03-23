#include <iostream>
using namespace std;

#include "TGraphErrors.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName  = CL.Get("DHFile", "JERTestRun2017.dh");
   string PdfFileName = CL.Get("Output", "JERSummary.dh");

   DataHelper DHFile(DHFileName);

   int EtaBinCount = 16;
   double EtaBins[] = {-2, -1.75, -1.5, -1.25, -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2};

   TGraphErrors G0, G1, G2;

   for(int i = 0; i < EtaBinCount; i++)
   {
      string State = Form("Fit_%.03f_%.03f", EtaBins[i], EtaBins[i+1]);

      double P0 = DHFile[State]["P0"].GetDouble();
      double E0 = DHFile[State]["P0Error"].GetDouble();
      double P1 = DHFile[State]["P1"].GetDouble();
      double E1 = DHFile[State]["P1Error"].GetDouble();
      double P2 = DHFile[State]["P2"].GetDouble();
      double E2 = DHFile[State]["P2Error"].GetDouble();

      E0 = sqrt(2) * fabs(P0) * E0;
      P0 = P0 * P0;
      E1 = sqrt(2) * fabs(P1) * E1;
      P1 = P1 * P1;
      E2 = sqrt(2) * fabs(P2) * E2;
      P2 = P2 * P2;

      G0.SetPoint(i, (EtaBins[i] + EtaBins[i+1]) / 2, P0);
      G0.SetPointError(i, (EtaBins[i+1] - EtaBins[i]) / 2, E0);
      G1.SetPoint(i, (EtaBins[i] + EtaBins[i+1]) / 2, P1);
      G1.SetPointError(i, (EtaBins[i+1] - EtaBins[i]) / 2, E1);
      G2.SetPoint(i, (EtaBins[i] + EtaBins[i+1]) / 2, P2);
      G2.SetPointError(i, (EtaBins[i+1] - EtaBins[i]) / 2, E2);
   }

   PdfFileHelper PdfFile(PdfFileName);
   PdfFile.AddTextPage("JER Summary");

   PdfFile.AddPlot(G0, "ap");
   PdfFile.AddPlot(G1, "ap");
   PdfFile.AddPlot(G2, "ap");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




