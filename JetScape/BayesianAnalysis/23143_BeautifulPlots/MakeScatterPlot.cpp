#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "TExec.h"

int main(int argc, char *argv[]);
void SetPad(TPad *P);
void SetAxis(TGaxis *A);
void Set1DHistogram(TH1D *H, int Color);
void Set2DHistogram(TH2D *H, int Color);
void Block2DHistogram(TH2D *H, int N, int Offset);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // gStyle->SetPalette(51);

   CommandLine CL(argc, argv);

   vector<string> FileNames = CL.GetStringVector("file");
   vector<string> Labels    = CL.GetStringVector("label");
   vector<string> Name      = CL.GetStringVector("name", {"A", "B", "C", "D"});
   vector<string> Details   = CL.GetStringVector("detail", vector<string>({"", ""}));
   bool DoDots              = CL.GetBool("dot", false);
   double LegendX           = CL.GetDouble("legendx", 0.7);
   string Output            = CL.Get("output", "Scatter.pdf");

   int Colors[] = {kRed, kBlue, kGreen + 3};
   TExec Exe1("Exe1", "double S1[2] = {0.000, 1.000}; double R1[2] = {1.000, 1.000}; double G1[2] = {1.000, 0.100}; double B1[2] = {1.000, 0.100}; TColor::CreateGradientColorTable(2, S1, R1, G1, B1, 99, 0.6);"); 
   TExec Exe2("Exe2", "double S1[2] = {0.000, 1.000}; double R1[2] = {1.000, 0.100}; double G1[2] = {1.000, 0.100}; double B1[2] = {1.000, 1.000}; TColor::CreateGradientColorTable(2, S1, R1, G1, B1, 99, 0.8);"); 
   TExec Exe3("Exe3", "double S1[2] = {0.000, 1.000}; double R1[2] = {1.000, 0.100}; double G1[2] = {1.000, 1.000}; double B1[2] = {1.000, 0.100}; TColor::CreateGradientColorTable(2, S1, R1, G1, B1, 99, 0.4);"); 

   int NFiles = FileNames.size();
   int N = Name.size();

   vector<TFile *> Files;
   for(int i = 0; i < NFiles; i++)
      Files.push_back(new TFile(FileNames[i].c_str()));

   vector<double> Min, Max;
   for(int i = 0; i < N; i++)
   {
      TH1D *H = (TH1D *)Files[0]->Get(Form("HPosterior%d", i));

      Min.push_back(H->GetXaxis()->GetBinLowEdge(1));
      Max.push_back(H->GetXaxis()->GetBinUpEdge(H->GetNbinsX()));
   }

   double PaddingLeft = 175;
   double PaddingBottom = 175;
   double PaddingRight = 50;
   double PaddingTop = 50;
   double PanelSizeX = 500;
   double PanelSizeY = 500;

   double CanvasX = PaddingLeft + PaddingRight + PanelSizeX * N;
   double CanvasY = PaddingTop + PaddingBottom + PanelSizeY * N;
   
   double PadX0 = PaddingLeft / CanvasX;
   double PadY0 = PaddingBottom / CanvasY;
   double PadSizeX = PanelSizeX / CanvasX;
   double PadSizeY = PanelSizeY / CanvasY;

   TCanvas Canvas("Canvas", "", CanvasX, CanvasY);

   TLatex Latex;
   Latex.SetTextFont(62);
   Latex.SetTextSize(0.03);
   Latex.SetTextAlign(22);
   Latex.SetNDC();

   for(int i = 0; i < N; i++)
   {
      Latex.DrawLatex(PadX0 + PadSizeX * (i + 0.5), PadY0 * 0.3, Name[i].c_str());
      Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadSizeY * (N - i - 0.5), Name[i].c_str());
   }

   double LineHeight = 0.05;

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);
   Latex.SetTextAlign(33);
   Latex.DrawLatex(PadX0 + PadSizeX * N, PadY0 + PadSizeY * N, "#font[62]{JETSCAPE}");

   for(int i = 0; i < (int)Details.size(); i++)
      Latex.DrawLatex(PadX0 + PadSizeX * N, PadY0 + PadSizeY * N - LineHeight * (i + 1), Details[i].c_str());
   
   vector<TGaxis *> XAxis, YAxis;

   for(int i = 0; i < N; i++)
   {
      double Protector = (i == N - 1) ? 1 : 0.999;

      XAxis.push_back(new TGaxis(PadX0 + PadSizeX * i, PadY0, PadX0 + PadSizeX * (i + 1), PadY0, Min[i], Max[i] * Protector, 305, ""));
      SetAxis(XAxis[i]);
      XAxis[i]->Draw();
      
      Protector = (i == 1) ? 1 : 0.999;
      
      YAxis.push_back(new TGaxis(PadX0, PadY0 + PadSizeY * (N - i - 1), PadX0, PadY0 + PadSizeY * (N - i), Min[i], Max[i] * Protector, 305, ""));
      SetAxis(YAxis[i]);
      if(i != 0)
         YAxis[i]->Draw();
   }

   vector<vector<TPad *>> Pads;
   for(int i = 0; i < N; i++)
   {
      Pads.push_back(vector<TPad *>());
      for(int j = 0; j < N; j++)
      {
         if(j < i)
         {
            Pads[i].push_back(nullptr);
            continue;
         }
         Pads[i].push_back(new TPad(Form("P%d", i), "",
            PadX0 + PadSizeX * i,       PadY0 + PadSizeY * (N - j - 1),
            PadX0 + PadSizeX * (i + 1), PadY0 + PadSizeY * (N - j), 0));
         SetPad(Pads[i][j]);
      }
   }

   TLegend Legend(LegendX + 0.000, PadY0 + PadSizeY * N - LineHeight * (Details.size() + 2),
                  LegendX + 0.300, PadY0 + PadSizeY * N - LineHeight * (Details.size() + 2 + NFiles));
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.04);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);

   for(int i = 0; i < N; i++)
   {
      Pads[i][i]->cd();
      double Max = 0;
      for(int j = 0; j < NFiles; j++)
      {
         TH1D *H = (TH1D *)Files[j]->Get(Form("HPosterior%d", i));
         Set1DHistogram(H, Colors[j]);
         Max = max(Max, H->GetMaximum());
         if(i == 0)
            Legend.AddEntry(H, Labels[j].c_str(), "l");
      }
      for(int j = 0; j < NFiles; j++)
      {
         TH1D *H = (TH1D *)Files[j]->Get(Form("HPosterior%d", i));
         H->SetMaximum(Max * 1.2);
         H->Draw(j == 0 ? "hist" : "hist same");
      }
   }
   for(int i = 0; i < N; i++)
   {
      for(int j = i + 1; j < N; j++)
      {
         Pads[i][j]->cd();
         bool First = true;
         for(int k = NFiles - 1; k >= 0; k--)
         {
            TH2D *H = (TH2D *)Files[k]->Get(Form("HPosterior%d%d", i, j));
            Set2DHistogram(H, Colors[k]);
            Block2DHistogram(H, NFiles, k);

            if(DoDots == false)
            {
               if(First)
               {
                  H->Draw("axis");
                  First = false;
               }

               if(k == 0)        Exe1.Draw();
               else if(k == 1)   Exe2.Draw();
               else              Exe3.Draw();

               // if(k == 0)
               {
                  H->Draw("col same");
                  H->Draw("axis same");
               }
               // else
               // {
               //    H->SetContour(3);
               //    H->Draw("cont3 same");
               // }
            }
            else
               H->Draw(k == 0 ? "" : "same");
         }
      }
   }

   Canvas.cd();
   if(NFiles > 1)
      Legend.Draw();

   Canvas.SaveAs(Output.c_str());

   for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
         if(Pads[i][j] != nullptr)
            delete Pads[i][j];
   
   for(int i = 0; i < N; i++)
   {
      delete XAxis[i];
      delete YAxis[i];
   }

   for(int i = 0; i < NFiles; i++)
   {
      Files[i]->Close();
      delete Files[i];
   }

   return 0;
}

void SetPad(TPad *P)
{
   P->SetLeftMargin(0);
   P->SetTopMargin(0);
   P->SetRightMargin(0);
   P->SetBottomMargin(0);
   // P->SetTickx();
   // P->SetTicky();
   P->Draw();
}

void SetAxis(TGaxis *A)
{
   A->SetLabelFont(42);
   A->SetLabelSize(0.030);
   A->SetMaxDigits(6);
}

void Set1DHistogram(TH1D *H, int Color)
{
   H->SetStats(0);
   H->SetLineColor(Color);
   // H->SetFillColor(Color);
   H->SetLineWidth(2);
   H->GetXaxis()->SetNdivisions(305);
   H->SetTickLength(0, "y");
   H->Scale(1 / H->Integral());
}

void Set2DHistogram(TH2D *H, int Color)
{
   H->SetStats(0);
   H->GetXaxis()->SetNdivisions(305);
   H->GetYaxis()->SetNdivisions(305);
   H->SetMarkerColor(Color);
   H->SetMarkerStyle(1);

   // H->Rebin2D(2, 2);

   // H->SetTickLength(0, "y");
   // H->SetTickLength(0, "x");
}

void Block2DHistogram(TH2D *H, int N, int Offset)
{
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      for(int j = 1; j <= H->GetNbinsY(); j++)
      {
         if((i + j) % N != Offset)
            H->SetBinContent(i, j, 0);
      }
   }
}

