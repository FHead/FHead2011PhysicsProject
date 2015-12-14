#include <iostream>
using namespace std;

#include "TStyle.h"
#include "TH2D.h"

#include "DataHelper.h"
#include "SetStyle.h"

#include "Utilities.hcpp"

int main(int argc, char *argv[])
{
   SetThesisStyle();
   gStyle->SetPaintTextFormat(".2g");
   gStyle->SetTextAngle(30);

   string DHFileName = "Normalization.dh";
   string State = "VeryLooseCut";
   string Prefix = "s1_";
   string ZeroOut = "true";
   if(argc > 1)
      DHFileName = argv[1];
   if(argc > 2)
      State = argv[2];
   if(argc > 3)
      Prefix = argv[3];
   if(argc > 4)
      ZeroOut = argv[4];
   
   DataHelper DHFile(DHFileName);

   string Tag = DHFileName.substr(0, DHFileName.size() - 3);
   cout << Tag << endl;

   TH2D HMatrix("HMatrix", "", 16, 0, 16, 16, 0, 16);
   TH2D HMatrixReal("HMatrixReal", "", 7, 0, 7, 7, 0, 7);
   TH2D HMatrixSM("HMatrixSM", "", 16, 0, 16, 16, 0, 16);
   TH2D HMatrixSMReal("HMatrixSMReal", "", 7, 0, 7, 7, 0, 7);

   PrepareHistogram(HMatrix);
   PrepareHistogramReal(HMatrixReal);
   PrepareHistogram(HMatrixSM);
   PrepareHistogramReal(HMatrixSMReal);
   
   HMatrix.SetMarkerColor(kWhite);
   HMatrix.SetMarkerSize(HMatrix.GetMarkerSize() * 0.75);
   HMatrix.SetMaximum(10);
   HMatrix.GetXaxis()->SetLabelSize(0.07);
   HMatrix.GetYaxis()->SetLabelSize(0.07);
   
   HMatrixReal.SetMarkerColor(kWhite);
   HMatrixReal.SetMarkerSize(HMatrixReal.GetMarkerSize() * 1.25);
   HMatrixReal.SetMaximum(10);
   HMatrixReal.GetXaxis()->SetLabelSize(0.07);
   HMatrixReal.GetYaxis()->SetLabelSize(0.07);
   
   HMatrixSM.SetMarkerColor(kWhite);
   HMatrixSM.SetMarkerSize(HMatrixSM.GetMarkerSize() * 0.75);
   HMatrixSM.SetMaximum(1);
   HMatrixSM.GetXaxis()->SetLabelSize(0.07);
   HMatrixSM.GetYaxis()->SetLabelSize(0.07);
   
   HMatrixSMReal.SetMarkerColor(kWhite);
   HMatrixSMReal.SetMarkerSize(HMatrixSMReal.GetMarkerSize() * 1.25);
   HMatrixSMReal.SetMaximum(1);
   HMatrixSMReal.GetXaxis()->SetLabelSize(0.07);
   HMatrixSMReal.GetYaxis()->SetLabelSize(0.07);

   double MZ = 91.1876;
   bool Group[] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
   double SMValue[] = {2, 0, 0.005, 0, 0, 0, 0.014, 0, 0, 0, -0.008, 0, 0, 0, 0, 0};
   double Factors[] = {1, 1, 1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1 / MZ / MZ, 1 / MZ / MZ};

   for(int iX = 0; iX < 16; iX++)
   {
      for(int iY = 0; iY < 16; iY++)
      {
         if(iX < iY)
            continue;

         if(ZeroOut == "true")
         {
            if(iX + iY == 3)
               continue;

            if(Group[iX] != Group[iY])
               continue;
         }

         int index = GetIndex(iX, iY);
         int sign = 1;

         if(index == 0)
            continue;
         if(index < 0)
         {
            index = -index;
            sign = -1;
         }

         double V1 = DHFile[State][Form("%s%03d", Prefix.c_str(), 1)].GetDouble() * Factors[0] * Factors[0];
         double VV = DHFile[State][Form("%s%03d", Prefix.c_str(), index)].GetDouble() * Factors[iX] * Factors[iY];

         double Factor = 1;
         if(iX == 0)
            Factor = Factor * 2;
         if(iY == 0)
            Factor = Factor * 2;

         HMatrix.SetBinContent(iX + 1, iY + 1, VV / V1 / 4 * Factor);

         if(iX % 2 == 0 && iY % 2 == 0)
            HMatrixReal.SetBinContent(iX / 2 + 1, iY / 2 + 1, VV / V1 / 4 * Factor);

         if(fabs(SMValue[iX]) > 0 && fabs(SMValue[iY]) > 0)
            HMatrixSM.SetBinContent(iX + 1, iY + 1, VV / V1 / 4 * SMValue[iX] * SMValue[iY]);

         if(fabs(SMValue[iX]) > 0 && fabs(SMValue[iY]) > 0 && iX % 2 == 0 && iY % 2 == 0)
            HMatrixSMReal.SetBinContent(iX / 2 + 1, iY / 2 + 1, VV / V1 / 4 * SMValue[iX] * SMValue[iY]);
      }
   }

   TCanvas C("C", "C", 1024 * 1.05, 1024);

   C.SetGridx();
   C.SetGridy();

   HMatrix.Draw("colz text00");

   C.SaveAs(("Matrix" + Tag + "All.png").c_str());
   C.SaveAs(("Matrix" + Tag + "All.C").c_str());
   C.SaveAs(("Matrix" + Tag + "All.eps").c_str());
   C.SaveAs(("Matrix" + Tag + "All.pdf").c_str());

   HMatrixReal.Draw("colz text00");

   C.SaveAs(("Matrix" + Tag + "Real.png").c_str());
   C.SaveAs(("Matrix" + Tag + "Real.C").c_str());
   C.SaveAs(("Matrix" + Tag + "Real.eps").c_str());
   C.SaveAs(("Matrix" + Tag + "Real.pdf").c_str());

   HMatrixSM.Draw("colz text00");

   C.SaveAs(("Matrix" + Tag + "SM.png").c_str());
   C.SaveAs(("Matrix" + Tag + "SM.C").c_str());
   C.SaveAs(("Matrix" + Tag + "SM.eps").c_str());
   C.SaveAs(("Matrix" + Tag + "SM.pdf").c_str());

   HMatrixSMReal.Draw("colz text00");

   C.SaveAs(("Matrix" + Tag + "SMReal.png").c_str());
   C.SaveAs(("Matrix" + Tag + "SMReal.C").c_str());
   C.SaveAs(("Matrix" + Tag + "SMReal.eps").c_str());
   C.SaveAs(("Matrix" + Tag + "SMReal.pdf").c_str());

   return 0;
}





