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

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void SetPad(TPad *P);
void SetAxis(TGaxis *A);
void Set1DHistogram(TH1D *H);
void Set2DHistogram(TH2D *H);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // gStyle->SetPalette(51);

   CommandLine CL(argc, argv);

   string FileName        = CL.Get("file");
   vector<string> Name    = CL.GetStringVector("name", {"A", "B", "C", "D"});
   vector<double> Min     = CL.GetDoubleVector("min", vector<double>({0, 0, 0, 0}));
   vector<double> Max     = CL.GetDoubleVector("max", vector<double>({2, 20, 2, 20}));
   bool DoTransform       = CL.GetBool("transform", false);
   string Model           = CL.Get("model", "LBT");
   vector<string> Details = CL.GetStringVector("detail", vector<string>({"", ""}));
   string Output          = CL.Get("output", "Scatter.pdf");

   int N = Name.size();

   vector<TH1D *> HDiagonal;
   vector<vector<TH2D *>> HScatter;

   int NBin = 30;

   for(int i = 0; i < N; i++)
   {
      HDiagonal.push_back(new TH1D(Form("HD%d", i), "", NBin, Min[i], Max[i]));
      Set1DHistogram(HDiagonal[i]);
   }
   for(int i = 0; i < N; i++)
   {
      HScatter.push_back(vector<TH2D *>());
      for(int j = 0; j < N; j++)
      {
         if(i >= j)
            HScatter[i].push_back(nullptr);
         else
         {
            HScatter[i].push_back(new TH2D(Form("HD%d%d", i, j), "", NBin, Min[i], Max[i], NBin, Min[j], Max[j]));
            Set2DHistogram(HScatter[i][j]);
         }
      }
   }

   PdfFileHelper PdfFile("Meow.pdf");
   PdfFile.AddTextPage("Meow");

   ifstream in(FileName);

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      double Temp[10] = {0};
      for(int i = 0; i < N; i++)
         str >> Temp[i];

      if(DoTransform == true)
      {
         double A = Temp[0];
         double B = Temp[1];

         Temp[0] = A * B;
         Temp[1] = A - A * B;
      }

      for(int i = 0; i < N; i++)
         HDiagonal[i]->Fill(Temp[i]);
      for(int i = 0; i < N; i++)
         for(int j = i + 1; j < N; j++)
            HScatter[i][j]->Fill(Temp[i], Temp[j]);
   }

   in.close();

   for(int i = 0; i < N; i++)
      PdfFile.AddPlot(HDiagonal[i]);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

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
   Latex.DrawLatex(PadX0 + PadSizeX * N, PadY0 + PadSizeY * N, "#font[62]{JETSCAPE} Preliminary");
   Latex.DrawLatex(PadX0 + PadSizeX * N, PadY0 + PadSizeY * N - LineHeight * 1, Model.c_str());

   for(int i = 0; i < (int)Details.size(); i++)
      Latex.DrawLatex(PadX0 + PadSizeX * N, PadY0 + PadSizeY * N - LineHeight * (i + 2), Details[i].c_str());
   
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

   for(int i = 0; i < N; i++)
   {
      Pads[i][i]->cd();
      HDiagonal[i]->Draw();
   }
   for(int i = 0; i < N; i++)
   {
      for(int j = i + 1; j < N; j++)
      {
         Pads[i][j]->cd();
         HScatter[i][j]->Draw("col");
      }
   }

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

   for(int i = 0; i < N; i++)
      delete HDiagonal[i];
   for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
         if(HScatter[i][j] != nullptr)
            delete HScatter[i][j];

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

void Set1DHistogram(TH1D *H)
{
   H->SetStats(0);
   H->SetLineColor(kBlack);
   H->SetLineWidth(2);
   H->GetXaxis()->SetNdivisions(305);
   H->SetTickLength(0, "y");
}

void Set2DHistogram(TH2D *H)
{
   H->SetStats(0);
   H->GetXaxis()->SetNdivisions(305);
   H->GetYaxis()->SetNdivisions(305);
   // H->SetTickLength(0, "y");
   // H->SetTickLength(0, "x");
}


