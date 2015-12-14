#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TArrow.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"

#include "AngleConversion.h"
#include "CalculateME.h"   // need part 15

int main()
{
   SetThesisStyle();

   TH1D H1("H1", ";m_{2};a.u.", 15, 4, 70);
   TH1D H2("H2", ";m_{2};a.u.", 1000, 4, 70);
   TH1D HBar("HBar", ";m_{2};a.u.", 15, 4, 70);

   GeneralScalarParameters Parameter;
   Parameter.ahR = 1;

                    // 123456789
   for(int i = 0; i < 1000000000; i++)
   {
      double M1, M2;

      do
      {
         M1 = sqrt(DrawRandom(4 * 4, 100 * 100));
         M2 = sqrt(DrawRandom(4 * 4, 65 * 65));
      } while(M1 + M2 > 125 || M1 < M2);
      
      EventParameters Event;
      Event.HMass = 125;
      Event.ZMass = M1;
      Event.Z2Mass = M2;

      double Value = GetScalar2e2mu_CM_M1M2_Projections(Event, Parameter);

      H1.Fill(M2, Value);
      H2.Fill(M2, Value);
   }

   H1.SetStats(0);
   H2.SetStats(0);

   H1.Scale(1 / H1.Integral() * H1.GetNbinsX() / (70 - 4));
   H2.Scale(1 / H2.Integral() * H2.GetNbinsX() / (70 - 4));

   H1.SetLineWidth(2);
   H2.SetLineWidth(2);

   HBar.SetLineColor(kGreen - 3);
   HBar.SetFillColor(kGreen - 3);

   double Data[] = {15, 27, 29, 47.5};

   TGraph G1, G2;

   for(int i = 0; i < 4; i++)
   {
      int B1 = H1.FindBin(Data[i]);
      G1.SetPoint(i, Data[i], H1.GetBinContent(B1));
      
      int B2 = H2.FindBin(Data[i]);
      G2.SetPoint(i, Data[i], H2.GetBinContent(B2));
      
      HBar.Fill(Data[i], 100);
   }

   G1.SetMarkerStyle(20);
   G2.SetMarkerStyle(20);

   G1.SetMarkerSize(3);
   G2.SetMarkerSize(3);

   TArrow Arrow;
   Arrow.SetAngle(35);
   Arrow.SetLineWidth(2);
   Arrow.SetFillColor(kBlack);
   Arrow.SetArrowSize(0.02);

   TCanvas C;

   H1.Draw();
   C.SaveAs("Template-CoarseNoDot.png");
   C.SaveAs("Template-CoarseNoDot.C");
   C.SaveAs("Template-CoarseNoDot.eps");
   C.SaveAs("Template-CoarseNoDot.pdf");

   H1.Draw();
   HBar.Draw("bar same");
   H1.Draw("same");
   H1.Draw("axis same");
   G1.Draw("p");

   for(int i = 0; i < 4; i++)
      Arrow.DrawArrow(Data[i], 0.004, Data[i], 0.001);

   C.SaveAs("Template-Coarse.png");
   C.SaveAs("Template-Coarse.C");
   C.SaveAs("Template-Coarse.eps");
   C.SaveAs("Template-Coarse.pdf");

   H2.Draw();
   G2.Draw("p");

   for(int i = 0; i < 4; i++)
      Arrow.DrawArrow(Data[i], 0.004, Data[i], 0.001);

   C.SaveAs("Template-Fine.png");
   C.SaveAs("Template-Fine.C");
   C.SaveAs("Template-Fine.eps");
   C.SaveAs("Template-Fine.pdf");

   return 0;
}





