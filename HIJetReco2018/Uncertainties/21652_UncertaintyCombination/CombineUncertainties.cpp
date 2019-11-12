#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

#include "JetUncertainty.h"

#define ScanEta 0
#define ScanPT 1

int main(int argc, char *argv[]);
void AddPlots(PdfFileHelper &PdfFile, vector<JetUncertainty> &JEU, vector<string> &Tags,
   string Title, double Min, double Max, double PT, double Eta, int Scan);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<double> PTBins = {9.0, 11.0, 13.5, 16.5, 19.5, 22.5, 26.0, 30.0, 34.5, 40.0, 46.0, 52.5, 60.0, 69.0, 79.0, 90.5, 105.5, 123.5, 143.0, 163.5, 185.0, 208.0, 232.5, 258.5, 286.0, 331.0, 396.0, 468.5, 549.5, 639.0, 738.0, 847.5, 968.5, 1102.0, 1249.5, 1412.0, 1590.5, 1787.0, 2003.0, 2241.0, 2503.0, 2790.5, 3107.0, 3455.0, 3837.0, 4257.0, 4719.0, 5226.5, 5784.0, 6538.0};
   vector<double> EtaBins = {-5, -4, -3.664, -3.489, -3.314, -3.139, -2.98, -2.83, -2.66325, -2.493, -2.329, -2.17725, -2.047, -1.93325, -1.8325, -1.74075, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.95925, -0.8745, -0.78525, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.78525, 0.8745, 0.95925, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.74075, 1.8325, 1.93325, 2.047, 2.17725, 2.329, 2.493, 2.66325, 2.83, 2.98, 3.139, 3.314, 3.489, 3.664, 4, 5};

   vector<string> FileNames = CL.GetStringVector("FileNames");
   vector<string> Tags      = CL.GetStringVector("Tags");

   string OutputBase        = CL.Get("Output");

   cout << FileNames.size() << endl;

   int N = FileNames.size();
   
   vector<JetUncertainty> JEU(N);
   for(int i = 0; i < N; i++)
      JEU[i].Initialize(FileNames[i]);

   ofstream out(OutputBase + ".txt");

   out << "{1 JetEta 1 JetPt \"\" Correction Uncertainty}" << endl;

   for(unsigned int i = 0; i + 1 < EtaBins.size(); i++)
   {
      double Eta = (EtaBins[i] + EtaBins[i+1]) / 2;

      out << EtaBins[i] << " " << EtaBins[i+1] << " " << PTBins.size() * 3;

      for(unsigned int j = 0; j < PTBins.size(); j++)
      {
         double U1 = 0, U2 = 0;

         for(unsigned int k = 0; k < N; k++)
         {
            JEU[k].SetJetPT(PTBins[j]);
            JEU[k].SetJetEta(Eta);
            JEU[k].SetJetPhi(0);

            U1 = U1 + JEU[k].GetUncertainty().first * JEU[k].GetUncertainty().first;
            U2 = U2 + JEU[k].GetUncertainty().second * JEU[k].GetUncertainty().second;
         }

         if(U1 > 1)   U1 = 1;
         if(U2 > 1)   U2 = 1;

         out << " " << PTBins[j] << " " << sqrt(U1) << " " << sqrt(U2);
      }

      out << endl;
   }

   out.close();

   FileNames.push_back(OutputBase + ".txt");
   Tags.push_back("Total");
   N = N + 1;

   JEU.push_back(JetUncertainty(OutputBase + ".txt"));

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Uncertainty Plots");

   AddPlots(PdfFile, JEU, Tags, "p_{T} = 30 GeV;#eta;", -5, 5, 30, 0, ScanEta);
   AddPlots(PdfFile, JEU, Tags, "p_{T} = 100 GeV;#eta;", -5, 5, 100, 0, ScanEta);
   AddPlots(PdfFile, JEU, Tags, "p_{T} = 300 GeV;#eta;", -5, 5, 300, 0, ScanEta);
   AddPlots(PdfFile, JEU, Tags, "#eta = 0.0;p_{T};", 10, 500, 30, 0.0, ScanPT);
   AddPlots(PdfFile, JEU, Tags, "#eta = 1.5;p_{T};", 10, 500, 30, 1.5, ScanPT);
   AddPlots(PdfFile, JEU, Tags, "#eta = 2.5;p_{T};", 10, 500, 30, 2.5, ScanPT);
   AddPlots(PdfFile, JEU, Tags, "#eta = 3.0;p_{T};", 10, 500, 30, 3.0, ScanPT);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlots(PdfFileHelper &PdfFile, vector<JetUncertainty> &JEU, vector<string> &Tags,
   string Title, double Min, double Max, double PT, double Eta, int Scan)
{
   int N = JEU.size();
   vector<TGraph> G(N);

   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < 1000; j++)
      {
         double x = 0;
         if(Scan == ScanEta)
         {
            x = (Max - Min) / 1000 * (j + 0.5) + Min;
            Eta = x;
         }
         if(Scan == ScanPT)
         {
            x = exp((log(Max) - log(Min)) / 1000 * (j + 0.5) + log(Min));
            PT = x;
         }

         JEU[i].SetJetPT(PT);
         JEU[i].SetJetEta(Eta);
         JEU[i].SetJetPhi(0);

         double U = JEU[i].GetUncertainty().first;

         G[i].SetPoint(j, x, U);
      }
   }

   int Color[] = {kBlack, kRed, kBlue, kGreen, kCyan, kMagenta, kYellow + 3};

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, Min, Max, 100, 0.001, 10);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   TLegend Legend(0.2, 0.5, 0.5, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   TLegend Legend2(0.5, 0.5, 0.8, 0.8);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);

   for(int i = 0; i < N; i++)
   {
      G[i].SetLineColor(Color[i%7]);
      G[i].SetLineWidth(2);
      if(i >= 7)
         G[i].SetLineStyle(kDashed);
      G[i].Draw("l");

      if(i < 7)
         Legend.AddEntry(&G[i], Tags[i].c_str(), "l");
      else
         Legend2.AddEntry(&G[i], Tags[i].c_str(), "l");
   }

   Legend.Draw();
   Legend2.Draw();

   if(Scan == ScanPT)
      Canvas.SetLogx();
   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);
}






