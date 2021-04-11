#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "CustomAssert.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void HumanPlots(PdfFileHelper &PdfFile,
   map<string, TH1D *> &H, vector<string> Names, vector<string> Labels, vector<int> Colors,
   vector<double> Bins1, vector<double> Bins2,
   string BinningObservable = "", string Title = "", string XTitle = "", string YTitle = "");
void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2);
TH1D *BuildSystematics(TH1D *HResult, TH1D *HVariation);
vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2, TH1D *H2 = nullptr);
void SetPad(TPad *P);
void SetAxis(TGaxis &A);
void SetWorld(TH2D *H);
TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2);
double CalculateIntegral(TGraphAsymmErrors &G, double MinX = -999);
double AddUp(TH1D *H, double XMin, double XMax, vector<double> Bins);
vector<TGraphAsymmErrors> TranscribeMC(string FileName, string HistogramName,
   double MinOverwrite, double MaxOverwrite, double XMin, double XMax,
   bool DoSelfNormalize = false, double Scale = 1);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName           = CL.Get("Input");
   string SystematicFileName      = CL.Get("Systematic");
   string OutputFileName          = CL.Get("Output");
   string FinalOutputFileName     = CL.Get("FinalOutput", "Meow.pdf");
   double GenPrimaryMinOverwrite  = CL.GetDouble("GenPrimaryMin", -999);
   double GenPrimaryMaxOverwrite  = CL.GetDouble("GenPrimaryMax", 999);
   double RecoPrimaryMinOverwrite = CL.GetDouble("RecoPrimaryMin", -999);
   double RecoPrimaryMaxOverwrite = CL.GetDouble("RecoPrimaryMax", 999);
   string PrimaryName             = CL.Get("PrimaryName", "HUnfoldedBayes14");
   bool DoSelfNormalize           = CL.GetBool("DoSelfNormalize", false);
   bool DoEventNormalize          = CL.GetBool("DoEventNormalize", false);
   double ExtraScale              = CL.GetDouble("ExtraScale", 1.00);

   vector<string> MCFileNames     = CL.GetStringVector("MCFile", vector<string>{InputFileName});
   vector<string> MCHistNames     = CL.GetStringVector("MCHistogram", vector<string>{"HMCTruth"});
   vector<string> MCLabels        = CL.GetStringVector("MCLabel", vector<string>{"PYTHIA6"});
   vector<int> MCColors           = CL.GetIntVector("MCColors", vector<int>{0, 1, 3, 5, 4, 7});

   vector<string> Texts           = CL.GetStringVector("Texts", vector<string>());

   double MarkerModifier          = CL.GetDouble("MarkerModifier", 1.0);

   double WorldXMin               = CL.GetDouble("WorldXMin", 10);
   double WorldXMax               = CL.GetDouble("WorldXMax", 50);
   double WorldYMin               = CL.GetDouble("WorldYMin", 1000);
   double WorldYMax               = CL.GetDouble("WorldYMax", 5e5);
   double WorldRMin               = CL.GetDouble("WorldRMin", 0.51);
   double WorldRMax               = CL.GetDouble("WorldRMax", 1.49);
   bool LogY                      = CL.GetBool("LogY", true);

   string XLabel                  = CL.Get("XLabel", "Jet P (GeV)");
   string YLabel                  = CL.Get("YLabel", "dN / d(Jet P)");
   string BinningLabel            = CL.Get("Binning", "Jet P");

   int XAxisSpacing               = CL.GetInt("XAxis", 505);
   int YAxisSpacing               = CL.GetInt("YAxis", 505);
   int RAxisSpacing               = CL.GetInt("RAxis", 505);

   double LegendX                 = CL.GetDouble("LegendX", 0.5);
   double LegendY                 = CL.GetDouble("LegendY", 0.5);
   double LegendSize              = CL.GetDouble("LegendSize", 0.075);

   Assert(DoSelfNormalize == false || DoEventNormalize == false, "Multiple normalization option chosen!");

   int MCCount = MCFileNames.size();
   Assert(MCCount == MCFileNames.size(), "MC file count not match");
   Assert(MCCount == MCHistNames.size(), "MC histogram count not match");
   Assert(MCCount == MCLabels.size(), "MC label count not match");
   Assert(MCCount <= MCColors.size(), "Not enough colors for MC");

   Assert(Texts.size() % 4 == 0, "Wrong additional text format!  It should be a collection of quadruplets: pad_index,x,y,text");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Unfolding plots");

   TFile InputFile(InputFileName.c_str());
   TFile SystematicFile(SystematicFileName.c_str());

   if(DoEventNormalize == true)
      Assert(InputFile.Get("DataEventCount") != nullptr, "No event count found in input file but option enabled");

   vector<double> GenBins1
      = DetectBins((TH1D *)InputFile.Get("HGenPrimaryBinMin"), (TH1D *)InputFile.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)InputFile.Get("HGenBinningBinMin"), (TH1D *)InputFile.Get("HGenBinningBinMax"));
   GenBins1[0] = GenPrimaryMinOverwrite;
   GenBins1[GenBins1.size()-1] = GenPrimaryMaxOverwrite;

   vector<string> H1Names{"HInput", "HMCMeasured", "HMCTruth"};

   if(find(H1Names.begin(), H1Names.end(), PrimaryName) == H1Names.end())
      H1Names.push_back(PrimaryName);

   map<string, TH1D *> H1;
   for(string Name : H1Names)
      H1[Name] = (TH1D *)InputFile.Get(Name.c_str());

   if(DoSelfNormalize == true)
      SelfNormalize(H1[PrimaryName], GenBins1, GenBins2);
   else
   {
      if(DoEventNormalize == true)
      {
         double EventCount = atof(InputFile.Get("DataEventCount")->GetTitle());
         H1[PrimaryName]->Scale(1 / EventCount);
      }
      if(ExtraScale > 0)
         H1[PrimaryName]->Scale(ExtraScale);
   }

   H1["HSystematicsRatioPlus"] = (TH1D *)SystematicFile.Get("HTotalPlus");
   H1["HSystematicsRatioMinus"] = (TH1D *)SystematicFile.Get("HTotalMinus");
   H1["HSystematicsPlus"] = BuildSystematics(H1[PrimaryName], H1["HSystematicsRatioPlus"]);
   H1["HSystematicsMinus"] = BuildSystematics(H1[PrimaryName], H1["HSystematicsRatioMinus"]);

   int IgnoreGroup = CL.GetInt("IgnoreGroup", 2);
   int Column      = CL.GetInt("Column", 4);
   int Row         = CL.GetInt("Row", 2);

   int BinningCount = GenBins2.size() - 1;
   if(BinningCount == 1)
   {
      IgnoreGroup = 0;
      Column = 1;
      Row = 1;
   }

   int PadWidth     = 250;
   int PadHeight    = 250;
   int PadRHeight   = 100;
   int MarginLeft   = 50 + (Column - 1) * 15;
   int MarginRight  = 25 + (Column - 1) * 10;
   int MarginTop    = 25 + (Column - 1) * 10;
   int MarginBottom = 50 + (Column - 1) * 15;

   double CanvasWidth = MarginLeft + PadWidth * Column + MarginRight;
   double CanvasHeight = MarginBottom + PadHeight * Row + PadRHeight * Row + MarginTop;

   double PadDX = PadWidth / CanvasWidth;
   double PadDY = PadHeight / CanvasHeight;
   double PadX0 = MarginLeft / CanvasWidth;
   double PadY0 = MarginBottom / CanvasHeight;
   double PadDR = PadRHeight / CanvasHeight;

   vector<TGraphAsymmErrors> GResult = Transcribe(H1[PrimaryName], GenBins1, GenBins2, nullptr);
   vector<TGraphAsymmErrors> GSystematics = Transcribe(H1["HSystematicsPlus"], GenBins1, GenBins2, H1["HSystematicsMinus"]);
   
   double PrimaryScale = AddUp(H1[PrimaryName], WorldXMin, WorldXMax, GenBins1);
   vector<vector<TGraphAsymmErrors>> GMC(MCCount);
   for(int i = 0; i < MCCount; i++)
      GMC[i] = TranscribeMC(MCFileNames[i], MCHistNames[i],
         GenPrimaryMinOverwrite, GenPrimaryMaxOverwrite,
         WorldXMin, WorldXMax, DoSelfNormalize, PrimaryScale);
   
   for(TGraphAsymmErrors G : GResult)
      cout << "Total integral = " << CalculateIntegral(G, WorldXMin) << endl;

   vector<TGraphAsymmErrors> GRResult, GRSystematics;
   vector<vector<TGraphAsymmErrors>> GRMC(MCCount);
   for(int i = 0; i < (int)GResult.size(); i++)
   {
      GRResult.push_back(CalculateRatio(GResult[i], GResult[i]));
      GRSystematics.push_back(CalculateRatio(GSystematics[i], GResult[i]));
      for(int j = 0; j < MCCount; j++)
         GRMC[j].push_back(CalculateRatio(GMC[j][i], GResult[i]));
   }

   for(TGraphAsymmErrors G : GResult)
      PdfFile.AddPlot(G, "ap");
   for(TGraphAsymmErrors G : GSystematics)
      PdfFile.AddPlot(G, "ap");
   for(vector<TGraphAsymmErrors> &V : GMC)
      for(TGraphAsymmErrors G : V)
         PdfFile.AddPlot(G, "ap");

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   // Setup pads
   vector<TPad *> Pads;
   vector<TPad *> RPads;
   for(int i = IgnoreGroup; i < BinningCount; i++)
   {
      int R = (i - IgnoreGroup) / Column;
      int C = (i - IgnoreGroup) % Column;

      double XMin = PadX0 + PadDX * C;
      double XMax = PadX0 + PadDX * (C + 1);
      double YMin = PadY0 + (PadDY + PadDR) * R;
      double YMax = PadY0 + (PadDY + PadDR) * (R + 1);

      Pads.emplace_back(new TPad(Form("P%d", i), "", XMin, YMin + PadDR, XMax, YMax));
      RPads.emplace_back(new TPad(Form("RP%d", i), "", XMin, YMin, XMax, YMin + PadDR));

      if(LogY == true)
         Pads[i-IgnoreGroup]->SetLogy();
   }

   for(TPad *P : Pads)
      SetPad(P);
   for(TPad *P : RPads)
      SetPad(P);
   
   // Setup axes
   vector<TGaxis *> XAxis, YAxis, RAxis;
   for(int i = 0; i < Column; i++)
   {
      XAxis.emplace_back(new TGaxis(PadX0 + PadDX * i, PadY0, PadX0 + PadDX * (i + 1), PadY0, WorldXMin, WorldXMax, XAxisSpacing, ""));
      SetAxis(*XAxis[i]);
      XAxis[i]->SetLabelSize(0.030 - max(Row, Column) * 0.001);
   }
   for(int i = 0; i < Row; i++)
   {
      double YMin = PadY0 + (PadDY + PadDR) * i;
      double YMax = YMin + PadDY + PadDR;
      string Option = (LogY ? "G" : "");
      YAxis.emplace_back(new TGaxis(PadX0, YMin + PadDR, PadX0, YMax, WorldYMin, WorldYMax, YAxisSpacing, Option.c_str()));
      RAxis.emplace_back(new TGaxis(PadX0, YMin, PadX0, YMin + PadDR, WorldRMin, WorldRMax, RAxisSpacing, ""));
      SetAxis(*YAxis[i]);
      SetAxis(*RAxis[i]);
      YAxis[i]->SetLabelSize(0.030 - max(Row, Column) * 0.001);
      RAxis[i]->SetLabelSize(0.030 - max(Row, Column) * 0.001);
   }

   // Setup axis labels
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035 - max(Column, Row) * 0.002);
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(22);
   Latex.SetNDC();
   for(int i = 0; i < Column; i++)
      Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.5, XLabel.c_str());
   Latex.SetTextAngle(90);
   Latex.SetTextAlign(22);
   for(int i = 0; i < Row; i++)
      Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadDR * (i + 1.0) + PadDY * (i + 0.5), YLabel.c_str());
   for(int i = 0; i < Row; i++)
      Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadDR * (i + 0.5) + PadDY * i, "Ratio to Data");

   // Setup general information
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(PadX0, PadY0 + PadDR * Row + PadDY * Row + 0.01, "ALEPH Archived Data 1994, e^{+}e^{-} #sqrt{s} = 91.2 GeV");

   // Setup worlds
   vector<TH2D *> HWorld;
   vector<TH2D *> HWorldR;
   for(int i = IgnoreGroup; i < BinningCount; i++)
   {
      int Index = i - IgnoreGroup;

      Pads[Index]->cd();
      HWorld.emplace_back(new TH2D(Form("HWorld%d", i), "", 100, WorldXMin, WorldXMax, 100, WorldYMin, WorldYMax));
      SetWorld(HWorld[Index]);
      HWorld[Index]->GetXaxis()->SetNdivisions(XAxisSpacing);
      HWorld[Index]->GetYaxis()->SetNdivisions(YAxisSpacing);
      
      RPads[Index]->cd();
      HWorldR.emplace_back(new TH2D(Form("HWorldR%d", i), "", 100, WorldXMin, WorldXMax, 100, WorldRMin, WorldRMax));
      SetWorld(HWorldR[Index]);
      HWorldR[Index]->GetXaxis()->SetNdivisions(XAxisSpacing);
      HWorldR[Index]->GetYaxis()->SetNdivisions(RAxisSpacing);
   }

   // Adding panel labeling
   if(Column > 1 || Row > 1)
   {
      for(int i = IgnoreGroup; i < BinningCount; i++)
      {
         int Index = i - IgnoreGroup;
         Pads[Index]->cd();

         string BinLabel = "";
         if(GenBins2[i] > -999)
            BinLabel = BinLabel + Form("%.1f < ", GenBins2[i]);
         BinLabel = BinLabel + BinningLabel;
         if(GenBins2[i+1] < 999)
            BinLabel = BinLabel + Form(" < %.1f", GenBins2[i+1]);

         Latex.SetTextFont(42);
         Latex.SetTextSize(0.075);
         Latex.SetTextAlign(33);
         Latex.DrawLatex(0.9, 0.9, BinLabel.c_str());
      }
   }

   // Make the legend
   TLegend Legend(LegendX, LegendY, LegendX + 0.3, LegendY + 0.065 * (1 + MCCount));
   Legend.SetTextFont(42);
   Legend.SetTextSize(LegendSize);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GSystematics[BinningCount-1], "Data", "plf");
   for(int j = 0; j < MCCount; j++)
      Legend.AddEntry(&GMC[j][BinningCount-1], MCLabels[j].c_str(), "l");

   // Plot the actual curves & legend
   for(int i = IgnoreGroup; i < BinningCount; i++)
   {
      int Index = i - IgnoreGroup;

      Pads[Index]->cd();

      for(int j = 0; j < MCCount; j++)
      {
         GMC[j][i].SetLineWidth(2);
         GMC[j][i].SetLineColor(Colors[MCColors[j]]);
         GMC[j][i].SetMarkerStyle(1);
         GMC[j][i].SetMarkerColor(Colors[MCColors[j]]);
      }
      
      GSystematics[i].SetLineWidth(2);
      GSystematics[i].SetLineColor(Colors[6]);
      GSystematics[i].SetFillColor(Colors[2]);
      GSystematics[i].SetMarkerStyle(20);
      GSystematics[i].SetMarkerSize(MarkerModifier);
      GSystematics[i].SetMarkerColor(Colors[6]);
      
      GResult[i].SetLineWidth(2);
      GResult[i].SetLineColor(Colors[6]);
      GResult[i].SetMarkerStyle(20);
      GResult[i].SetMarkerSize(MarkerModifier);
      GResult[i].SetMarkerColor(Colors[6]);

      GSystematics[i].Draw("2");
      for(int j = 0; j < MCCount; j++)
         GMC[j][i].Draw("lz");
      GResult[i].Draw("pz");

      HWorld[Index]->Draw("axis same");

      for(int j = 0; j < (int)Texts.size(); j = j + 4)
      {
         int PadIndex = atoi(Texts[j+0].c_str());
         double X     = atof(Texts[j+1].c_str());
         double Y     = atof(Texts[j+2].c_str());
         string Text  = Texts[j+3];

         if(PadIndex != Index)
            continue;

         Latex.SetNDC();
         Latex.SetTextFont(42);
         Latex.SetTextSize(0.035);
         Latex.SetTextAlign(12);
         Latex.DrawLatex(X, Y, Text.c_str());
      }

      if(i == BinningCount - 1)
         Legend.Draw();

      RPads[Index]->cd();

      for(int j = 0; j < MCCount; j++)
      {
         GRMC[j][i].SetLineWidth(2);
         GRMC[j][i].SetLineColor(Colors[MCColors[j]]);
         GRMC[j][i].SetMarkerStyle(1);
         GRMC[j][i].SetMarkerColor(Colors[MCColors[j]]);
      }

      GRSystematics[i].SetLineWidth(2);
      GRSystematics[i].SetLineColor(Colors[6]);
      GRSystematics[i].SetFillColor(Colors[2]);
      GRSystematics[i].SetMarkerStyle(20);
      GRSystematics[i].SetMarkerSize(MarkerModifier);
      GRSystematics[i].SetMarkerColor(Colors[6]);
      
      GRResult[i].SetLineWidth(2);
      GRResult[i].SetLineColor(Colors[6]);
      GRResult[i].SetMarkerStyle(20);
      GRResult[i].SetMarkerSize(MarkerModifier);
      GRResult[i].SetMarkerColor(Colors[6]);

      GRSystematics[i].Draw("2");
      for(int j = 0; j < MCCount; j++)
         GRMC[j][i].Draw("lz");
      GRResult[i].Draw("pz");
      
      HWorldR[Index]->Draw("axis same");
   }

   Canvas.cd();

   for(int j = 0; j < (int)Texts.size(); j = j + 4)
   {
      int PadIndex = atoi(Texts[j+0].c_str());
      double X     = atof(Texts[j+1].c_str());
      double Y     = atof(Texts[j+2].c_str());
      string Text  = Texts[j+3];

      if(PadIndex != -1)
         continue;

      Latex.SetNDC();
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.035);
      Latex.SetTextAlign(12);
      Latex.DrawLatex(X, Y, Text.c_str());
   }

   Canvas.SaveAs(FinalOutputFileName.c_str());

   for(TH2D *H : HWorld)    delete H;
   for(TH2D *H : HWorldR)   delete H;
   for(TGaxis *A : XAxis)   delete A;
   for(TGaxis *A : YAxis)   delete A;
   for(TGaxis *A : RAxis)   delete A;
   for(TPad *P : Pads)      delete P;
   for(TPad *P : RPads)     delete P;

   SystematicFile.Close();
   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return vector<double>{};

   vector<pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   sort(Bins.begin(), Bins.end());
   auto iterator = unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   vector<double> Result;
   for(auto iterator : Bins)
   {
      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }
   
   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2)
{
   if(H == nullptr)
      return;
   
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      int BinCount = Bins1.size() - 1;
      if(BinCount <= 0)
         BinCount = 1;

      double Total = 0;
      for(int i = 0; i < BinCount; i++)
         Total = Total + H->GetBinContent(i + 1 + iB * BinCount);
      
      for(int i = 0; i < BinCount; i++)
      {
         H->SetBinContent(i + 1 + iB * BinCount, H->GetBinContent(i + 1 + iB * BinCount) / Total);
         H->SetBinError(i + 1 + iB * BinCount, H->GetBinError(i + 1 + iB * BinCount) / Total);
      }
   }
}

TH1D *BuildSystematics(TH1D *HResult, TH1D *HVariation)
{
   if(HResult == nullptr)
      return nullptr;

   TH1D *HSystematics = (TH1D *)HResult->Clone();

   if(HVariation == nullptr)
      return HSystematics;

   HSystematics->Reset();
   for(int i = 1; i <= HResult->GetNbinsX(); i++)
   {
      double V = HResult->GetBinContent(i);
      double R = HVariation->GetBinContent(i);
      HSystematics->SetBinContent(i, V * (R + 1));
   }

   return HSystematics;
}

vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2, TH1D *H2)
{
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;
   
   vector<TGraphAsymmErrors> Result(BinningCount);
   if(H == nullptr)
      return Result;

   int PrimaryBinCount = Bins1.size() - 1;
   double PrimaryBins[1000] = {0};
   for(int i = 0; i <= PrimaryBinCount; i++)
      PrimaryBins[i] = Bins1[i];
   double Delta = PrimaryBins[PrimaryBinCount-1] - PrimaryBins[1];

   if(PrimaryBins[0] < -998)
      PrimaryBins[0] = PrimaryBins[1] - Delta * 0.05;
   if(PrimaryBins[PrimaryBinCount] > 998)
      PrimaryBins[PrimaryBinCount] = PrimaryBins[PrimaryBinCount-1] + Delta * 0.05;
   if(PrimaryBins[0] < 0 && PrimaryBins[1] > 0)
      PrimaryBins[0] = 0;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      for(int i = 0; i < PrimaryBinCount; i++)
      {
         double X = (PrimaryBins[i] + PrimaryBins[i+1]) / 2;
         double DX = (PrimaryBins[i+1] - PrimaryBins[i]) / 2;
         double Y = 0, DY = 0;

         if(H2 == nullptr)
         {
            Y = H->GetBinContent(i + iB * PrimaryBinCount + 1);
            DY = H->GetBinError(i + iB * PrimaryBinCount + 1);
         }
         else
         {
            double YUp = H->GetBinContent(i + iB * PrimaryBinCount + 1);
            double YDown = H2->GetBinContent(i + iB * PrimaryBinCount + 1);

            Y = (YUp + YDown) / 2;
            DY = fabs(YUp - YDown) / 2;
         }

         double Width = PrimaryBins[i+1] - PrimaryBins[i];

         Result[iB].SetPoint(i, X, Y / Width);
         Result[iB].SetPointError(i, DX, DX, DY / Width, DY / Width);
      }
   }

   return Result;
}

void SetPad(TPad *P)
{
   if(P == nullptr)
      return;
   P->SetLeftMargin(0);
   P->SetTopMargin(0);
   P->SetRightMargin(0);
   P->SetBottomMargin(0);
   P->SetTickx();
   P->SetTicky();
   P->Draw();
}

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.030);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   // A.SetNoExponent();
   A.Draw();
}

void SetWorld(TH2D *H)
{
   if(H == nullptr)
      return;
   H->SetStats(0);
   H->Draw("axis");
}

TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2)
{
   TGraphAsymmErrors G;

   int N = G2.GetN();
   for(int i = 0; i < N; i++)
   {
      double X1, X2, Y1, Y2, E1YH, E1YL, E1XH, E1XL;

      G1.GetPoint(i, X1, Y1);
      E1YH = G1.GetErrorYhigh(i);
      E1YL = G1.GetErrorYlow(i);
      E1XH = G1.GetErrorXhigh(i);
      E1XL = G1.GetErrorXlow(i);
      G2.GetPoint(i, X2, Y2);

      if(Y2 == 0)
         continue;

      G.SetPoint(i, X1, Y1 / Y2);
      G.SetPointError(i, E1XL, E1XH, E1YL / Y2, E1YH / Y2);
   }

   return G;
}

double CalculateIntegral(TGraphAsymmErrors &G, double MinX)
{
   double Total = 0;

   int N = G.GetN();
   for(int i = 0; i < N; i++)
   {
      double EX1, EX2, X, Y;

      G.GetPoint(i, X, Y);
      EX1 = G.GetErrorXlow(i);
      EX2 = G.GetErrorXhigh(i);

      if(X < MinX)
         continue;

      Total = Total + Y * (EX1 + EX2);
   }

   return Total;
}

double AddUp(TH1D *H, double XMin, double XMax, vector<double> Bins)
{
   double Total = 0;

   for(int i = 1; i < (int)Bins.size(); i++)
   {
      double Min = Bins[i-1];
      double Max = Bins[i];

      double V = H->GetBinContent(i);

      if(Min > XMin && Max <= XMax)
         Total = Total + V;
      if(Min <= XMin && Max > XMin)
         Total = Total + V * (Max - XMin) / (Max - Min);
      if(Min <= XMax && Max > XMax)
         Total = Total + V * (XMax - Min) / (Max - Min);
   }

   return Total;
}

vector<TGraphAsymmErrors> TranscribeMC(string FileName, string HistogramName,
   double MinOverwrite, double MaxOverwrite, double XMin, double XMax,  bool DoSelfNormalize, double Scale)
{
   vector<TGraphAsymmErrors> G;

   TFile File(FileName.c_str());

   TH1D *H = (TH1D *)File.Get(HistogramName.c_str());
   if(H == nullptr)
   {
      File.Close();
      return G;
   }

   vector<double> GenBins1
      = DetectBins((TH1D *)File.Get("HGenPrimaryBinMin"), (TH1D *)File.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)File.Get("HGenBinningBinMin"), (TH1D *)File.Get("HGenBinningBinMax"));
   GenBins1[0] = MinOverwrite;
   GenBins1[GenBins1.size()-1] = MaxOverwrite;

   double Total = AddUp(H, XMin, XMax, GenBins1);
   H->Scale(Scale / Total);

   if(DoSelfNormalize == true)
      SelfNormalize(H, GenBins1, GenBins2);

   G = Transcribe(H, GenBins1, GenBins2);

   File.Close();

   return G;
}

