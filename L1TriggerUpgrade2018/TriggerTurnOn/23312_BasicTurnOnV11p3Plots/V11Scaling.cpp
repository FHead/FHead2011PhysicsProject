#include <vector>
#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TF1.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void Transcribe(DataHelper &DHFile, string State, TGraph &G, double YMax);
void FitLinear(TGraph &G, double &P0, double &P1);

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

   vector<string> DHFileNames = CL.GetStringVector("DHFiles", vector<string>());
   vector<string> States      = CL.GetStringVector("States");
   vector<string> Labels      = CL.GetStringVector("Labels");
   string OutputBase          = CL.Get("OutputBase");

   vector<int> Markers        = CL.GetIntVector("Marker", vector<int>(DefaultMarkers, DefaultMarkers + 6));

   double MaxX                = CL.GetDouble("MaxX", 150);
   double MaxY                = CL.GetDouble("MaxY", 150);
   string Threshold           = CL.Get("Threshold", "95%");
   string Suffix              = CL.Get("Suffix", "Location");
   vector<int> Colors         = CL.GetIntVector("Color", vector<int>(DefaultColors, DefaultColors + 6));

   bool DavignonStyle = CL.GetBool("Davignon", false);

   if(DavignonStyle == false)
      SetThesisStyle();

   for(int i = 0; i < (int)Colors.size(); i++)
   {
      if(Colors[i] == -1)   Colors[i] = DefaultColors[0];
      if(Colors[i] == -2)   Colors[i] = DefaultColors[1];
      if(Colors[i] == -3)   Colors[i] = DefaultColors[2];
      if(Colors[i] == -4)   Colors[i] = DefaultColors[3];
      if(Colors[i] == -5)   Colors[i] = DefaultColors[4];
      if(Colors[i] == -6)   Colors[i] = DefaultColors[5];
   }
   
   int N = States.size();

   while(Labels.size() < N)
      Labels.push_back("Unknown");

   while(DHFileNames.size() < N)
   {
      cout << "Warning!  DHFile default to V11" << endl;
      DHFileNames.push_back("CurvesV11.dh");
   }

   while(Colors.size() < N)
      Colors.push_back(1);

   vector<TGraph> G(N);

   for(int i = 0; i < N; i++)
   {
      G[i].SetMarkerStyle(Markers[i]);
      G[i].SetMarkerSize(1.5);
      G[i].SetMarkerColor(Colors[i]);
      G[i].SetLineWidth(2);
      G[i].SetLineColor(Colors[i]);
   }

   vector<double> P0(N), P1(N);
   for(int i = 0; i < N; i++)
   {
      DataHelper DHFile(DHFileNames[i]);
      Transcribe(DHFile, States[i], G[i], MaxY);
      FitLinear(G[i], P0[i], P1[i]);
   }

   vector<TGraph> L(N);
   for(int i = 0; i < N; i++)
   {
      L[i].SetPoint(0, 0, P0[i]);
      L[i].SetPoint(1, MaxX, P0[i] + MaxX * P1[i]);
      
      L[i].SetLineWidth(2);
      L[i].SetLineColor(Colors[i]);
   }

   TCanvas Canvas;
   if(DavignonStyle == true)
   {
      Canvas.SetCanvasSize(800, 800);
      Canvas.SetLeftMargin(0.11);
      Canvas.SetRightMargin(0.10);
   }

   TH2D HWorld("HWorld", Form(";Threshold (GeV);%s %s", Threshold.c_str(), Suffix.c_str()), 100, 0, MaxX, 100, 0, MaxY);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   for(int i = 0; i < N; i++)
      G[i].Draw("p");
   for(int i = 0; i < N; i++)
      L[i].Draw("l");

   double LegendTop = DavignonStyle ? 0.875 : 0.825;
   TLegend Legend(0.175, LegendTop - 0.06 * N, 0.475, LegendTop);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&G[i], Form("%s, y = %.02f + %.02f x", Labels[i].c_str(), P0[i], P1[i]), "lp");
   Legend.Draw();

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
      Latex.DrawLatex(0.90, 0.91, "14 TeV, Double PU");
   }

   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C", OutputBase.c_str()));

   return 0;
}

void Transcribe(DataHelper &DHFile, string State, TGraph &G, double YMax)
{
   int N = DHFile[State]["N"].GetInteger();

   G.Set(0);

   for(int i = 0; i < N; i++)
   {
      double X = DHFile[State][Form("X%d",i)].GetDouble();
      double Y = DHFile[State][Form("Y%d",i)].GetDouble();

      if(Y < 0 || Y > YMax)
         continue;

      G.SetPoint(G.GetN(), X, Y);
   }

   cout << G.GetN() << endl;
}

void FitLinear(TGraph &G, double &P0, double &P1)
{
   double MinX = -1, MaxX = -1;

   for(int i = 0; i < G.GetN(); i++)
   {
      double X, Y;
      G.GetPoint(i, X, Y);

      if(MinX < 0 || X < MinX)
         MinX = X;
      if(MaxX < 0 || X > MaxX)
         MaxX = X;
   }

   // TF1 F("F", "[0]+[1]*x", MinX - 1, MaxX + 1);
   TF1 F("F", "[0]+[1]*x");

   G.Print();
   G.Fit(&F, "N");

   P0 = F.GetParameter(0);
   P1 = F.GetParameter(1);
}



