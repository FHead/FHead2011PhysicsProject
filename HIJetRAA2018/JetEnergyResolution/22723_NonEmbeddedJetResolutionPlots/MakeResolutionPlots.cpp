#include <iostream>
#include <vector>
using namespace std;

#include "TLegend.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TLatex.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   double XMin = CL.GetDouble("XMin", 20);
   double XMax = CL.GetDouble("XMax", 1000);
   double YMin = CL.GetDouble("YMin", 0);
   double YMax = CL.GetDouble("YMax", 1);
   vector<string> DHFileNames = CL.GetStringVector("DHFile", vector<string>());
   vector<string> States = CL.GetStringVector("State", vector<string>());
   vector<string> Labels = CL.GetStringVector("Label", vector<string>());
   vector<string> ExtraText = CL.GetStringVector("Extra", vector<string>());
   string OutputFileName = CL.Get("Output", "Resolution.pdf");

   int Colors[] = {kBlack, kRed, kBlue, kCyan, kMagenta, kGreen + 1, kBlack, kRed, kBlue, kCyan, kMagenta};
   int Styles[] = {kSolid, kSolid, kSolid, kSolid, kSolid, kSolid, kDashed, kDashed, kDashed, kDashed, kDashed};
 
   Assert(DHFileNames.size() > 0, "No input DHFile specified.");
   Assert(States.size() > 0, "No input states specified.");

   if(DHFileNames.size() == 1 && States.size() > 1)
      DHFileNames.resize(States.size(), DHFileNames[0]);
   if(States.size() == 1 && DHFileNames.size() > 1)
      States.resize(DHFileNames.size(), States[0]);
   
   Assert(States.size() == DHFileNames.size(), "Number of files and number of states do not match.");

   if(Labels.size() < DHFileNames.size())
      Labels.resize(DHFileNames.size(), "X");

   int N = DHFileNames.size();

   vector<TF1 *> Functions;
   for(int i = 0; i < N; i++)
   {
      DataHelper DHFile(DHFileNames[i]);

      double P0 = DHFile[States[i]]["P0"].GetDouble();
      double P1 = DHFile[States[i]]["P1"].GetDouble();
      double P2 = DHFile[States[i]]["P2"].GetDouble();

      cout << P0 << " " << P1 << " " << P2 << endl;

      Functions.push_back(new TF1(Form("F%d", i), "sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/x/x)", XMin, XMax));
      Functions[i]->SetParameters(P0, P1, P2);
   }

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";p_{T};#sigma/#mu", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   TLegend Legend(0.55, 0.85, 0.85, 0.85 - 0.05 * N);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);

   for(int i = 0; i < N; i++)
   {
      if(Functions[i] == nullptr)
         continue;

      Functions[i]->SetLineColor(Colors[i]);
      Functions[i]->SetLineStyle(Styles[i]);
      Functions[i]->Draw("same");

      Legend.AddEntry(Functions[i], Labels[i].c_str(), "l");
   }

   Legend.Draw();

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(12);
   for(int i = 0; i < (int)ExtraText.size(); i++)
      Latex.DrawLatex(0.15, 0.15 + (ExtraText.size() - i) * 0.05, ExtraText[i].c_str());

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{Internal}");

   Canvas.SetLogx();
   Canvas.SaveAs(OutputFileName.c_str());

   for(TF1 *F : Functions)
      if(F != nullptr)
         delete F;

   return 0;
}


