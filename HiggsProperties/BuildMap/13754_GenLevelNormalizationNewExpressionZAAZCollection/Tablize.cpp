#include <iostream>
using namespace std;

#include "TStyle.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "DataHelper.h"
#include "SetStyle.h"

#include "Utilities.hcpp"

int main(int argc, char *argv[])
{
   SetStyle();
   gStyle->SetPaintTextFormat(".2e");

   DataHelper DHFile("Normalization.dh");
   string State = "VeryLooseCut";
   string Prefix = "s1_";
   if(argc > 1)
      State = argv[1];
   if(argc > 2)
      Prefix = argv[2];

   TH2D HMatrix("HMatrix", "", 14, 0, 14, 14, 0, 14);
   TH2D HMatrixReal("HMatrixReal", "", 7, 0, 7, 7, 0, 7);
   TH2D HMatrixSM("HMatrixSM", "", 14, 0, 14, 14, 0, 14);
   PrepareHistogram(HMatrix);
   PrepareHistogramReal(HMatrixReal);
   PrepareHistogram(HMatrixSM);
   HMatrix.SetMarkerColor(kWhite);
   HMatrix.SetMaximum(0.25);
   HMatrixReal.SetMarkerColor(kWhite);
   HMatrixReal.SetMarkerSize(HMatrixReal.GetMarkerSize() * 2);
   HMatrixReal.SetMaximum(0.25);
   HMatrixSM.SetMarkerColor(kWhite);
   HMatrixSM.SetMaximum(1);

   bool Group[] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
   double SMValue[] = {2, 0, 0.005, 0, 0, 0, 0.007, 0, 0, 0, -0.008, 0, 0, 0};

   for(int iX = 0; iX < 14; iX++)
   {
      for(int iY = 0; iY < 14; iY++)
      {
         if(iX + iY == 3)
            continue;

         if(Group[iX] != Group[iY])
            continue;

         int index = GetIndex(iX, iY);
         int sign = 1;

         if(index == 0)
            continue;
         if(index < 0)
         {
            index = -index;
            sign = -1;
         }

         double V1 = DHFile[State][Form("%s%02d", Prefix.c_str(), 1)].GetDouble();
         double VV = DHFile[State][Form("%s%02d", Prefix.c_str(), index)].GetDouble();

         HMatrix.SetBinContent(iX + 1, iY + 1, VV / V1 / 4);

         if(iX % 2 == 0 && iY % 2 == 0)
            HMatrixReal.SetBinContent(iX / 2 + 1, iY / 2 + 1, VV / V1 / 4);

         if(fabs(SMValue[iX]) > 0 && fabs(SMValue[iY]) > 0)
            HMatrixSM.SetBinContent(iX + 1, iY + 1, VV / V1 / 4 * SMValue[iX] * SMValue[iY]);
      }
   }

   // HMatrixSM.Scale(1 / HMatrixSM.Integral());

   PsFileHelper PsFile("Matrix.ps");
   PsFile.AddTextPage(State);

   PsFile.AddPlot(HMatrix, "colz text15");
   PsFile.AddPlot(HMatrixReal, "colz text15");

   PsFile.AddPlot(HMatrixSM, "colz text15");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}





