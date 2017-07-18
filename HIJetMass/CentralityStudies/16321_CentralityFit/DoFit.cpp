#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"

#include "DataHelper.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string InputFileName = "ScaledResult/AA6Dijet.root";
   string Tag = "AA6Dijet";

   if(argc != 3)
   {
      cerr << argv[0] << " Input Tag" << endl;
      return -1;
   }

   InputFileName = argv[1];
   Tag = argv[2];

   DataHelper DHFile("RhoDatabase.dh");

   PdfFileHelper PdfFile(Tag + ".pdf");

   TFile File(InputFileName.c_str());

   for(int i = 0; i < 100; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("HRho%d", i));
      if(H == NULL)
         continue;

      H->Rebin(5);

      TF1 F("F", "gaus");

      F.SetParLimits(1, 0, 400);
      F.SetParLimits(2, 0, 50);

      H->Fit(&F);

      H->SetStats(0);

      PdfFile.AddPlot(H);

      DHFile[Tag][Form("C%02d_A",i)] = F.GetParameter(0);
      DHFile[Tag][Form("C%02d_B",i)] = F.GetParameter(1);
      DHFile[Tag][Form("C%02d_C",i)] = F.GetParameter(2);
      DHFile[Tag][Form("C%02d_ErrorA",i)] = F.GetParError(0);
      DHFile[Tag][Form("C%02d_ErrorB",i)] = F.GetParError(1);
      DHFile[Tag][Form("C%02d_ErrorC",i)] = F.GetParError(2);
   }
   
   for(int i = 0; i < 100; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("HRhoM%d", i));
      if(H == NULL)
         continue;

      H->Rebin(5);

      TF1 F("F", "gaus");

      F.SetParLimits(1, 0, 400);
      F.SetParLimits(2, 0, 50);

      H->Fit(&F);

      H->SetStats(0);

      PdfFile.AddPlot(H);

      DHFile[Tag][Form("RhoM_C%02d_A",i)] = F.GetParameter(0);
      DHFile[Tag][Form("RhoM_C%02d_B",i)] = F.GetParameter(1);
      DHFile[Tag][Form("RhoM_C%02d_C",i)] = F.GetParameter(2);
      DHFile[Tag][Form("RhoM_C%02d_ErrorA",i)] = F.GetParError(0);
      DHFile[Tag][Form("RhoM_C%02d_ErrorB",i)] = F.GetParError(1);
      DHFile[Tag][Form("RhoM_C%02d_ErrorC",i)] = F.GetParError(2);
   }

   PdfFile.Close();

   DHFile.SaveToFile("RhoDatabase.dh");

   return 0;
}



