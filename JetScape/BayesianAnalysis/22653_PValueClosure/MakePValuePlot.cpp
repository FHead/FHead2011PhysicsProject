#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "DataHelper.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile", "Results.dh");
   string OutputFileName = CL.Get("Output", "PValue.pdf");
   string Label = CL.Get("Label", "LBT");

   TH1D HPValue("HPValue", ";p-value;Number of holdout tests", 50, 0, 1);
   HPValue.SetStats(0);
   HPValue.Sumw2();

   HPValue.GetXaxis()->CenterTitle();
   HPValue.GetYaxis()->CenterTitle();

   DataHelper DHFile(DHFileName);

   vector<string> States = DHFile.GetListOfKeys();

   for(string State : States)
   {
      double Size = DHFile[State]["PosteriorSize"].GetInteger();
      double Index = DHFile[State]["Index"].GetInteger();

      HPValue.Fill(Index / Size);
   }

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);
   Latex.SetNDC();

   TCanvas Canvas;
   
   HPValue.Draw("hist");

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, Label.c_str());

   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.85, 0.92, "#font[62]{JETSCAPE}");

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}




