#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TImage.h"

#include "SetStyle.h"
#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames = CL.GetStringVector("files", vector<string>());
   vector<string> Graphs    = CL.GetStringVector("graphs", vector<string>());
   vector<string> Labels    = CL.GetStringVector("labels", vector<string>());
   vector<string> Ranges    = CL.GetStringVector("ranges", vector<string>());
   vector<int> Colors       = CL.GetIntVector("colors", vector<int>({kBlue, kRed, kGreen + 3}));
   vector<int> Styles       = CL.GetIntVector("styles", vector<int>({kSolid, kDashed, kDotted}));
   vector<string> Texts     = CL.GetStringVector("texts", vector<string>());
   string XLabel            = CL.Get("xlabel");
   string YLabel            = CL.Get("ylabel");
   double XMin              = CL.GetDouble("xmin");
   double XMax              = CL.GetDouble("xmax");
   double YMin              = CL.GetDouble("ymin");
   double YMax              = CL.GetDouble("ymax");
   bool DoJet               = CL.GetBool("dojet", false);
   string OutputFileName    = CL.Get("output", "Meow.pdf");

   Assert(FileNames.size() == Graphs.size(), "Different number of files vs graphs");

   if(Ranges.size() < FileNames.size())
      Ranges.insert(Ranges.end(), FileNames.size() - Ranges.size(), "90");
   if(Colors.size() < FileNames.size())
      Colors.insert(Colors.end(), FileNames.size() - Colors.size(), 1);
   if(Styles.size() < FileNames.size())
      Styles.insert(Styles.end(), FileNames.size() - Styles.size(), 1);
   if(Labels.size() < FileNames.size())
      Labels.insert(Labels.end(), FileNames.size() - Labels.size(), "NoName");

   int N = FileNames.size();

   double CanvasWidth = 600;
   double CanvasHeight = 500;
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);
   Canvas.SetTopMargin(0.1);
   Canvas.SetRightMargin(0.05);
   Canvas.SetBottomMargin(0.1);
   Canvas.SetLeftMargin(0.1);

   TH2D HWorld("HWorld", "", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetTitle(XLabel.c_str());
   HWorld.GetYaxis()->SetTitle(YLabel.c_str());
   HWorld.GetXaxis()->CenterTitle();
   HWorld.GetYaxis()->CenterTitle();
   HWorld.GetXaxis()->SetTitleSize(0.05);
   HWorld.GetXaxis()->SetLabelSize(0.05);
   HWorld.GetXaxis()->SetTitleOffset(0.9);
   HWorld.GetYaxis()->SetTitleSize(0.05);
   HWorld.GetYaxis()->SetLabelSize(0.05);
   HWorld.GetYaxis()->SetTitleOffset(0.9);
   HWorld.Draw("axis");

   vector<TGraph> G90(N), GMedian(N);

   for(int i = 0; i < N; i++)
   {
      TFile File(FileNames[i].c_str());

      if(File.Get(Form("%s%s", Graphs[i].c_str(), Ranges[i].c_str())) != nullptr)
         G90[i] = *((TGraph *)File.Get(Form("%s%s", Graphs[i].c_str(), Ranges[i].c_str())));
      if(File.Get(Form("%sMedian", Graphs[i].c_str())) != nullptr)
         GMedian[i] = *((TGraph *)File.Get(Form("%sMedian", Graphs[i].c_str())));

      File.Close();

      G90[i].SetFillColorAlpha(Colors[i], 0.35);
      G90[i].SetLineColor(Colors[i]);
      G90[i].SetLineWidth(2);
      G90[i].SetLineStyle(Styles[i]);
      GMedian[i].SetLineColor(Colors[i]);
      GMedian[i].SetLineWidth(2);
      GMedian[i].SetLineStyle(Styles[i]);
   }

   TGraphErrors JetPoint, JetBorder1, JetBorder2;
   JetPoint.SetMarkerStyle(20);
   JetPoint.SetLineWidth(2);
   JetBorder1.SetLineStyle(kDashed);
   JetBorder2.SetLineStyle(kDashed);

   if(DoJet == true)
   {
      JetPoint.SetPoint(0, 0.365, 4.6);
      JetPoint.SetPointError(0, 0, 1.2);
      JetPoint.SetPoint(1, 0.460, 3.7);
      JetPoint.SetPointError(1, 0, 1.4);

      JetBorder1.SetPoint(0, 0.170, 4.6 - 1.2);
      JetBorder1.SetPoint(1, 0.170, 4.6 + 1.2);
      JetBorder1.SetPoint(2, 0.386, 4.6 + 1.2);
      JetBorder1.SetPoint(3, 0.386, 4.6 - 1.2);
      JetBorder1.SetPoint(4, 0.170, 4.6 - 1.2);

      JetBorder2.SetPoint(0, 0.340, 3.7 - 1.4);
      JetBorder2.SetPoint(1, 0.340, 3.7 + 1.4);
      JetBorder2.SetPoint(2, 0.486, 3.7 + 1.4);
      JetBorder2.SetPoint(3, 0.486, 3.7 - 1.4);
      JetBorder2.SetPoint(4, 0.340, 3.7 - 1.4);
   }

   int ItemCount = N;
   if(DoJet == true)
      ItemCount = ItemCount + 1;

   TLegend Legend(0.36, 0.85, 0.58, 0.85 - ItemCount * 0.07);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
   {
      if(G90[i].GetN() > 0)
         Legend.AddEntry(&G90[i], Form("%s", Labels[i].c_str()), "fl");
      else
         Legend.AddEntry(&GMedian[i], Form("%s", Labels[i].c_str()), "l");
   }
   if(DoJet == true)
      Legend.AddEntry(&JetPoint, "JET Collaboration", "pl");

   for(int i = 0; i < N; i++)
      G90[i].Draw("f");
   for(int i = 0; i < N; i++)
      GMedian[i].Draw("l");

   if(DoJet == true)
   {
      JetPoint.Draw("p");
      JetBorder1.Draw("l");
      JetBorder2.Draw("l");
   }

   Legend.Draw();

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextSize(0.05);
   Latex.SetTextFont(42);
   Latex.SetTextAlign(31);
   Latex.DrawLatex(0.95, 0.91, "#font[62]{ }");

   Latex.SetTextAlign(22);
   for(int i = 0; i + 3 <= Texts.size(); i = i + 3)
   {
      double X = atof(Texts[i+0].c_str());
      double Y = atof(Texts[i+1].c_str());
      string T = Texts[i+2];

      Latex.DrawLatex(X, Y, T.c_str());
   }

   double PadLX1 = 90 / CanvasWidth;
   double PadLX2 = 210 / CanvasWidth;
   double PadLY1 = 350 / CanvasHeight;
   double PadLY2 = 430 / CanvasHeight;

   // TPad PadL("PadL", "", PadLX1, PadLY1, PadLX2, PadLY2);
   // PadL.SetLeftMargin(0);
   // PadL.SetTopMargin(0);
   // PadL.SetRightMargin(0);
   // PadL.SetBottomMargin(0);
   // PadL.Draw();
   // PadL.cd();
   // TImage *Logo = (TImage *)TImage::Open("JetscapeLogo.jpg");
   // Logo->Draw("");

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}





