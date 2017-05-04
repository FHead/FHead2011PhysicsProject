#include <iostream>
using namespace std;

#include "TF1.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Tag" << endl;
      return -1;
   }
   
   string Tag = "AADataPrescale";
   Tag = argv[1];

   DataHelper DHFile("ResolutionDatabase.dh");

   TGraph GMean, GRMS;

   for(int i = 100; i < 200; i++)
   {
      GMean.SetPoint(GMean.GetN(), i + 0.5, DHFile[Tag][Form("Mean%d00",i)].GetDouble());
      GRMS.SetPoint(GRMS.GetN(), i + 0.5, DHFile[Tag][Form("RMS%d00",i)].GetDouble());
   }

   TF1 FMean("FMean", "[0]+[1]*exp(-[2]*x)+[3]*exp([4]*x)");
   TF1 FRMS("FRMS", "[0]+[1]*exp(-[2]*x)");

   FMean.SetParameter(0, -0.07);
   FMean.SetParameter(1, 0.10);
   FMean.SetParameter(2, 0.01);
   FMean.SetParameter(3, 0.10);
   FMean.SetParameter(4, 0.01);
   
   FRMS.SetParameter(0, 0.10);
   FRMS.SetParameter(1, 0.90);
   FRMS.SetParameter(2, 0.02);

   GMean.Fit(&FMean);
   GRMS.Fit(&FRMS);

   PdfFileHelper PdfFile("ResolutionFit" + Tag + ".pdf");

   PdfFile.AddTextPage(Tag);

   PdfFile.AddPlot(GMean, "ap");
   PdfFile.AddPlot(GRMS, "ap");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   DHFile[Tag]["MeanP0"] = FMean.GetParameter(0);
   DHFile[Tag]["MeanP1"] = FMean.GetParameter(1);
   DHFile[Tag]["MeanP2"] = FMean.GetParameter(2);
   DHFile[Tag]["MeanP3"] = FMean.GetParameter(3);
   DHFile[Tag]["MeanP4"] = FMean.GetParameter(4);
   
   DHFile[Tag]["RMSP0"] = FRMS.GetParameter(0);
   DHFile[Tag]["RMSP1"] = FRMS.GetParameter(1);
   DHFile[Tag]["RMSP2"] = FRMS.GetParameter(2);

   DHFile.SaveToFile("ResolutionDatabase.dh");

   return 0;
}









