#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPad.h"
#include "TImage.h"

#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisSmallStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output", "Chi2.pdf");
   string Model = CL.Get("Model", "MODEL");
   int NDF = CL.GetInt("NDF", -1);
   double Max = CL.GetDouble("Max", -1);

   vector<double> Data;

   ifstream in(InputFileName);
   while(in)
   {
      double Temp = -1;
      in >> Temp;
      if(Temp > 0)
         Data.push_back(Temp);
   }
   in.close();

   double MaxData = 0;
   for(int i = 0; i < (int)Data.size(); i++)
      if(MaxData < Data[i])
         MaxData = Data[i];

   TH1D H("H", ";#chi^{2};a.u.", 75, 0, ((Max < 0) ? (MaxData * 1.05) : Max));
   H.SetStats(0);

   for(int i = 0; i < (int)Data.size(); i++)
      H.Fill(Data[i]);

   int BinCount = H.GetNbinsX();
   double BinSize = (H.GetXaxis()->GetBinUpEdge(BinCount) - H.GetXaxis()->GetBinLowEdge(1)) / BinCount;
   H.Scale(1 / H.Integral() / BinSize);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);
   Latex.SetNDC();

   TCanvas Canvas;

   H.Draw("hist");

   if(Model != "" && Model != "MODEL")
   {
      Latex.SetTextAlign(12);
      Latex.DrawLatex(0.10, 0.92, Model.c_str());
   }
   
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.85, 0.92, "#font[62]{}");

   if(NDF > 0)
   {
      Latex.SetTextAlign(32);
      Latex.DrawLatex(0.80, 0.80, Form("N_{Data} = %d", NDF));
   }

   TPad PadL("PadL", "", 0.15, 0.71, 0.36, 0.85);
   PadL.SetLeftMargin(0);
   PadL.SetTopMargin(0);
   PadL.SetRightMargin(0);
   PadL.SetBottomMargin(0);
   PadL.Draw();
   PadL.cd();
   TImage *Logo = (TImage *)TImage::Open("JetscapeLogo.jpg");
   Logo->Draw("");

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}



