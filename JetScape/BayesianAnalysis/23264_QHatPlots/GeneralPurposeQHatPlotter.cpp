#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TImage.h"
#include "TGaxis.h"

#include "SetStyle.h"
#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames      = CL.GetStringVector("files", vector<string>());
   vector<string> Graphs         = CL.GetStringVector("graphs", vector<string>());
   vector<string> Labels         = CL.GetStringVector("labels", vector<string>());
   vector<string> Ranges         = CL.GetStringVector("ranges", vector<string>());
   vector<int> Colors            = CL.GetIntVector("colors", vector<int>({kBlue, kRed, kGreen + 3}));
   vector<int> Styles            = CL.GetIntVector("styles", vector<int>({kSolid, kDashed, kDotted}));

   vector<string> Texts          = CL.GetStringVector("texts", vector<string>());
   string XLabel                 = CL.Get("xlabel");
   string YLabel                 = CL.Get("ylabel");
   double XMin                   = CL.GetDouble("xmin");
   double XMax                   = CL.GetDouble("xmax");
   double YMin                   = CL.GetDouble("ymin");
   double YMax                   = CL.GetDouble("ymax");
   double LegendX                = CL.GetDouble("legendx", 0.36);
   double LegendY                = CL.GetDouble("legendy", 0.85);
   bool DoJet                    = CL.GetBool("dojet", false);
   
   bool DoInset                  = CL.GetBool("inset", false);
   double InsetLeft              = CL.GetDouble("insetleft", 0.65);
   double InsetRight             = CL.GetDouble("insetright", 0.90);
   double InsetTop               = CL.GetDouble("insettop", 0.85);
   double InsetBottom            = CL.GetDouble("insetbottom", 0.60);
   double InsetXMin              = CL.GetDouble("insetxmin", XMin);
   double InsetXMax              = CL.GetDouble("insetxmax", XMax);
   double InsetYMin              = CL.GetDouble("insetymin", YMin);
   double InsetYMax              = CL.GetDouble("insetymax", YMax);
   vector<string> InsetFileNames = CL.GetStringVector("insetfiles", vector<string>());
   vector<string> InsetGraphs    = CL.GetStringVector("insetgraphs", vector<string>());
   vector<string> InsetLabels    = CL.GetStringVector("insetlabels", vector<string>());
   vector<string> InsetRanges    = CL.GetStringVector("insetranges", vector<string>());
   // vector<int> InsetColors       = CL.GetIntVector("insetcolors", vector<int>({kGreen + 1, kRed - 4, kAzure + 7}));
   vector<int> InsetColors       = CL.GetIntVector("insetcolors", vector<int>({kAzure + 8, kAzure + 1, kAzure}));
   vector<int> InsetStyles       = CL.GetIntVector("insetstyles", vector<int>({kSolid, kSolid, kSolid}));
   string InsetText              = CL.Get("insettext", "");
   
   string OutputFileName         = CL.Get("output", "Meow.pdf");

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

   double OverallScale = 5;
   double CanvasWidth = 600 * OverallScale;
   double CanvasHeight = 500 * OverallScale;
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);
   TPad MainPad("MainPad", "", 0, 0, 1, 1);
   MainPad.SetTopMargin(0.1);
   MainPad.SetRightMargin(0.05);
   MainPad.SetBottomMargin(0.1);
   MainPad.SetLeftMargin(0.1);
   MainPad.Draw();
   MainPad.cd();

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
      {
         G90[i] = *((TGraph *)File.Get(Form("%s%s", Graphs[i].c_str(), Ranges[i].c_str())));

         double X, Y;
         G90[i].GetPoint(0, X, Y);
         G90[i].SetPoint(G90[i].GetN(), X, Y);
      }
      if(File.Get(Form("%sMedian", Graphs[i].c_str())) != nullptr)
         GMedian[i] = *((TGraph *)File.Get(Form("%sMedian", Graphs[i].c_str())));

      File.Close();

      // G90[i].SetFillColorAlpha(Colors[i], 0.35);
      G90[i].SetLineColor(Colors[i]);
      G90[i].SetLineWidth(2);
      G90[i].SetLineStyle(Styles[i]);
      GMedian[i].SetLineColor(Colors[i]);
      GMedian[i].SetLineWidth(2);
      GMedian[i].SetLineStyle(Styles[i]);
   }

   TGraphErrors JetPoint, JetBorder1, JetBorder2;
   JetPoint.SetMarkerStyle(20);
   JetPoint.SetMarkerSize(OverallScale);
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

   TLegend Legend(LegendX, LegendY, LegendX + 0.22, LegendY - ItemCount * 0.07);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.04);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
   {
      if(G90[i].GetN() > 0)
         Legend.AddEntry(&G90[i], Form("%s", Labels[i].c_str()), "l");
      else
         Legend.AddEntry(&GMedian[i], Form("%s", Labels[i].c_str()), "l");
   }
   if(DoJet == true)
      Legend.AddEntry(&JetPoint, "JET Collaboration", "pl");

   for(int i = 0; i < N; i++)
      G90[i].Draw("l");
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

   double PadLX1 = 510 / CanvasWidth * OverallScale;
   double PadLX2 = 570 / CanvasWidth * OverallScale;
   double PadLY1 = 455 / CanvasHeight * OverallScale;
   double PadLY2 = 495 / CanvasHeight * OverallScale;

   TPad PInset("PInset", "", InsetLeft, InsetBottom, InsetRight, InsetTop);
   PInset.SetTopMargin(0);
   PInset.SetRightMargin(0);
   PInset.SetBottomMargin(0);
   PInset.SetLeftMargin(0);

   Canvas.cd();
   TGaxis InsetX(InsetLeft, InsetBottom, InsetRight, InsetBottom, InsetXMin, InsetXMax, 505, "S");
   TGaxis InsetY(InsetLeft, InsetBottom, InsetLeft, InsetTop, InsetYMin, InsetYMax, 505, "S");
   InsetX.SetTickLength(0);
   InsetX.SetLabelFont(42);
   InsetX.SetLabelSize(0.03);
   InsetX.SetTitleFont(42);
   InsetX.SetTitleSize(0.03);
   InsetX.CenterTitle();
   InsetX.SetTitle(XLabel.c_str());
   InsetY.SetTickLength(0);
   InsetY.SetLabelFont(42);
   InsetY.SetLabelSize(0.03);
   InsetY.SetTitleFont(42);
   InsetY.SetTitleSize(0.03);
   InsetY.CenterTitle();
   InsetY.SetTitle(YLabel.c_str());

   TH2D HWorldInset("HWorldInset", "", 100, InsetXMin, InsetXMax, 100, InsetYMin, InsetYMax);
   HWorldInset.SetStats(0);
   HWorldInset.GetXaxis()->SetTickLength(0.02 / (InsetTop - InsetBottom));
   HWorldInset.GetYaxis()->SetTickLength(0.02 / (InsetRight - InsetLeft));
   HWorldInset.GetXaxis()->SetNdivisions(505);
   HWorldInset.GetYaxis()->SetNdivisions(505);
   
   int InsetN = InsetFileNames.size();
   vector<TGraph> InsetG90(InsetN), InsetGMedian(InsetN);

   for(int i = 0; i < InsetN; i++)
   {
      TFile File(InsetFileNames[i].c_str());

      if(File.Get(Form("%s%s", InsetGraphs[i].c_str(), InsetRanges[i].c_str())) != nullptr)
         InsetG90[i] = *((TGraph *)File.Get(Form("%s%s", InsetGraphs[i].c_str(), InsetRanges[i].c_str())));
      if(File.Get(Form("%sMedian", InsetGraphs[i].c_str())) != nullptr)
         InsetGMedian[i] = *((TGraph *)File.Get(Form("%sMedian", InsetGraphs[i].c_str())));

      File.Close();

      InsetG90[i].SetFillColorAlpha(InsetColors[i], 1.0);
      InsetG90[i].SetLineColor(InsetColors[i]);
      InsetG90[i].SetLineWidth(2);
      InsetG90[i].SetLineStyle(InsetStyles[i]);
      InsetGMedian[i].SetLineColor(InsetColors[i]);
      InsetGMedian[i].SetLineWidth(2);
      InsetGMedian[i].SetLineStyle(InsetStyles[i]);
   }

   if(DoInset == true)
   {
      InsetX.Draw();
      InsetY.Draw();

      PInset.Draw();
      PInset.cd();

      HWorldInset.Draw("axis");
      
      for(int i = 0; i < InsetN; i++)
         InsetG90[i].Draw("f");
      // for(int i = 0; i < InsetN; i++)
      //    InsetGMedian[i].Draw("l");
      
      string Label = "Prior";
      for(int i = InsetN - 1; i >= 0; i--)
         Label = Label + Form(" #bf{#color[%d]{%s}}", InsetColors[i], InsetLabels[i].c_str());
      
      Latex.SetTextAlign(22);
      Latex.SetTextSize(0.03 / (InsetTop - InsetBottom));
      Latex.DrawLatex(0.500, 0.700, Label.c_str());
      Latex.DrawLatex(0.500, 0.825, InsetText.c_str());

      HWorldInset.Draw("axis same");
   }

   Canvas.cd();
   TPad PadL("PadL", "", PadLX1, PadLY1, PadLX2, PadLY2);
   PadL.SetLeftMargin(0);
   PadL.SetTopMargin(0);
   PadL.SetRightMargin(0);
   PadL.SetBottomMargin(0);
   PadL.Draw();
   PadL.cd();
   TImage *Logo = (TImage *)TImage::Open("JetscapeLogo.jpeg");
   // Logo->SetJpegDpi("JetscapeLogo.jpeg", 300);
   Logo->Draw("");

   Canvas.SaveAs((OutputFileName + ".eps").c_str());
   Canvas.SaveAs((OutputFileName + ".png").c_str());

   return 0;
}





