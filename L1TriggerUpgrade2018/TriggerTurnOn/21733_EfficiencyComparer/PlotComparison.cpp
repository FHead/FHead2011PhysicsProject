#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
string ExpandName(string Name);
string AutoName(string HMatch);

int main(int argc, char *argv[])
{
   int DefaultColors[6] = {-1, -1, -1, -1, -1, -1};
   DefaultColors[0] = TColor::GetColor("#E74C3C");
   DefaultColors[1] = TColor::GetColor("#3498DB");
   DefaultColors[2] = TColor::GetColor("#F1C40F");
   DefaultColors[3] = TColor::GetColor("#2ECC71");
   DefaultColors[4] = TColor::GetColor("#7F7F7F");
   DefaultColors[5] = kMagenta;

   int DefaultMarkers[6] = {20, 20, 20, 20, 20, 20};

   CommandLine CL(argc, argv);

   vector<string> Labels       = CL.GetStringVector("label");
   vector<string> FileNames    = CL.GetStringVector("file");
   vector<string> Numerators   = CL.GetStringVector("numerator");
   vector<string> Denominators = CL.GetStringVector("denominator");
   string OutputFileName       = CL.Get("output");
   string Title                = CL.Get("title", ";;Efficiency");
   double XMin                 = CL.GetDouble("xmin");
   double XMax                 = CL.GetDouble("xmax");
   double YMin                 = CL.GetDouble("ymin", 0.0);
   double YMax                 = CL.GetDouble("ymax", 1.1);
   vector<int> Colors          = CL.GetIntVector("color", vector<int>(DefaultColors, DefaultColors + 6));
   vector<int> Markers         = CL.GetIntVector("marker", vector<int>(DefaultMarkers, DefaultMarkers + 6));
   vector<double> Lines        = CL.GetDoubleVector("line", vector<double>({1.00}));
   vector<string> Texts        = CL.GetStringVector("text", vector<string>());
   bool Grid                   = CL.GetBool("grid", false);
   bool LogY                   = CL.GetBool("logy", false);
   double LegendX              = CL.GetDouble("legendx", 0.35);
   double LegendY              = CL.GetDouble("legendy", 0.20);
   int ReBin                   = CL.GetInt("rebin", 1);

   for(int i = 0; i < (int)Colors.size(); i++)
   {
      if(Colors[i] == -1)   Colors[i] = DefaultColors[0];
      if(Colors[i] == -2)   Colors[i] = DefaultColors[1];
      if(Colors[i] == -3)   Colors[i] = DefaultColors[2];
      if(Colors[i] == -4)   Colors[i] = DefaultColors[3];
      if(Colors[i] == -5)   Colors[i] = DefaultColors[4];
      if(Colors[i] == -6)   Colors[i] = DefaultColors[5];
   }

   int N = FileNames.size();

   Assert(N == Labels.size(),       "Number of files != number of labels");
   Assert(N == Numerators.size(),   "Number of files != number of numberators");
   Assert(N == Denominators.size(), "Number of files != number of denominators");
   Assert(N <= Colors.size(),       "Please specify line colors");

   if(N > Markers.size())
      Markers.insert(Markers.end(), N - Markers.size(), 20);

   bool DavignonStyle          = CL.GetBool("Davignon", false);
   if(DavignonStyle == false)
      SetThesisStyle();

   vector<TGraphAsymmErrors> Graphs(N);
   for(int i = 0; i < N; i++)
   {
      TFile File(FileNames[i].c_str());

      if(Denominators[i] == "cumulative")
      {
         TH1D *H = (TH1D *)File.Get(ExpandName(Numerators[i]).c_str());

         if(H != nullptr)
         {
            H->Rebin(ReBin);
            
            double Total = 0;
            for(int iB = 0; iB <= H->GetNbinsX() + 1; iB++)
               Total = Total + H->GetBinContent(iB);
            
            double Cumulative = H->GetBinContent(0);
            for(int iB = 1; iB <= H->GetNbinsX(); iB++)
            {
               Cumulative = Cumulative + H->GetBinContent(iB);
               Graphs[i].SetPoint(iB - 1, H->GetBinCenter(iB), Cumulative / Total);
            }
         }
      }
      else if(Denominators[i] == "simple")
      {
         TH1D *H = (TH1D *)File.Get(ExpandName(Numerators[i]).c_str());

         if(H != nullptr)
         {
            H->Rebin(ReBin);
            
            double Integral = H->Integral();
            for(int iB = 1; iB <= H->GetNbinsX(); iB++)
            {
               double BinSize = H->GetXaxis()->GetBinUpEdge(iB) - H->GetXaxis()->GetBinLowEdge(iB);
               Graphs[i].SetPoint(iB - 1, H->GetBinCenter(iB), H->GetBinContent(iB) / Integral / BinSize);
            }
         }
      }
      else
      {
         if(Denominators[i] == "auto")
            Denominators[i] = AutoName(Numerators[i]);

         TH1D *H1 = (TH1D *)File.Get(ExpandName(Numerators[i]).c_str());
         TH1D *H2 = (TH1D *)File.Get(ExpandName(Denominators[i]).c_str());

         if(H1 != nullptr && H2 != nullptr)
         {
            H1->Rebin(ReBin);
            H2->Rebin(ReBin);
            Graphs[i].Divide(H1, H2);
         }
      }

      File.Close();
   }

   TCanvas Canvas;
   if(DavignonStyle == true)
   {
      Canvas.SetCanvasSize(800, 800);
      Canvas.SetLeftMargin(0.11);
      Canvas.SetRightMargin(0.10);
   }

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw();

   TGraph GLine;
   GLine.SetLineStyle(kDashed);
   for(int i = 0; i < (int)Lines.size(); i++)
   {
      if(i % 2 == 0)
      {
         GLine.SetPoint(i * 2 + 0, XMin, Lines[i]);
         GLine.SetPoint(i * 2 + 1, XMax, Lines[i]);
      }
      else
      {
         GLine.SetPoint(i * 2 + 0, XMax, Lines[i]);
         GLine.SetPoint(i * 2 + 1, XMin, Lines[i]);
      }
   }
   GLine.Draw("l");

   for(int i = 0; i < N; i++)
   {
      Graphs[i].SetMarkerColor(Colors[i]);
      Graphs[i].SetMarkerStyle(Markers[i]);
      Graphs[i].SetMarkerSize(1.25);
      Graphs[i].SetLineColor(Colors[i]);
      Graphs[i].SetLineWidth(2);
      Graphs[i].Draw("pl");
   }

   int LegendCount = 0;
   for(int i = 0; i < N; i++)
      if(Labels[i] != "NONE")
         LegendCount = LegendCount + 1;
   TLegend Legend(LegendX, LegendY, LegendX + 0.3, LegendY + 0.06 * LegendCount);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      if(Labels[i] != "NONE")
         Legend.AddEntry(&Graphs[i], Labels[i].c_str(), "pl");
   Legend.Draw();

   if(Texts.size() > 0)
   {
      TLatex Latex;
      Latex.SetNDC();
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.035);
      Latex.SetTextAlign(11);

      for(int i = 0; i + 3 <= (int)Texts.size(); i = i + 3)
      {
         double x = atof(Texts[i+0].c_str());
         double y = atof(Texts[i+1].c_str());
         Latex.DrawLatex(x, y, Texts[i+2].c_str());
      }
   }

   if(DavignonStyle == true)
   {
      TLatex Latex;
      Latex.SetNDC();

      Latex.SetTextFont(42);
      Latex.SetTextSize(0.03);
      Latex.SetTextAlign(11);
      Latex.DrawLatex(0.11, 0.91, "#scale[1.5]{CMS} Phase-2 Simulation");

      Latex.SetTextSize(0.035);
      Latex.SetTextAlign(31);
      Latex.DrawLatex(0.90, 0.91, "14 TeV, 200 PU");
   }

   Canvas.SetGridx(Grid);
   Canvas.SetGridy(Grid);
   Canvas.SetLogy(LogY);

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}

string ExpandName(string Name)
{
   string TempString = Name;
   for(char &c : TempString)
      if(c == '_')
         c = ' ';
   stringstream str(TempString);

   string Folder = "";
   str >> Folder;

   int Pos = Folder.find("NoMatch");
   if(Pos != string::npos)
      Folder.erase(Folder.begin() + Pos, Folder.begin() + Pos + 7);

   return Folder + "/" + Name;
}

string AutoName(string HMatch)
{
   string HNoMatch = HMatch;

   for(int i = 0; i < (int)HNoMatch.size(); i++)
   {
      if(HNoMatch[i] == '_')
      {
         HNoMatch.insert(i, "NoMatch");
         break;
      }
   }

   return HNoMatch;
}
