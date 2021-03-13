#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string PosteriorFileName = CL.Get("Posterior");
   string HoldoutFileName   = CL.Get("Holdout");
   int N                    = CL.GetInt("N");

   char StrN[100];
   sprintf(StrN, "%d", N);

   TH1D HPosterior("HPosterior", ";Posterior function value;#", 100, 225, 236);
   HPosterior.SetStats(0);
   double Holdout = -1;

   ifstream in(PosteriorFileName);
   while(in)
   {
      double Temp = -1;
      in >> Temp;
      if(Temp < 0)
         continue;
      HPosterior.Fill(Temp);
   }
   in.close();

   ifstream in2(HoldoutFileName);
   in2 >> Holdout;
   in2.close();

   TGraph G;
   G.SetLineStyle(kDashed);
   G.SetPoint(0, Holdout, 0);
   G.SetPoint(1, Holdout, 100000);

   TCanvas Canvas;
   Canvas.SetLogy();

   HPosterior.Draw();
   G.Draw("l");

   Canvas.SaveAs(Form("Example%d.pdf", N));

   return 0;
}



