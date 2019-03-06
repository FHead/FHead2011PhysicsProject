#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "JetCorrector.h"

int main(int argc, char *argv[]);
void PlotPTDependence(PdfFileHelper &PdfFile, double Eta, double Rho,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode = false);
void PlotEtaDependence(PdfFileHelper &PdfFile, double PT, double Rho,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode = false);
void PlotRhoDependence(PdfFileHelper &PdfFile, double PT, double Eta,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames = CL.GetStringVector("jec", {"A", "B", "C", "D"});
   vector<string> Labels    = CL.GetStringVector("label", {"A", "B", "C", "D"});
   string OutputFileName    = CL.Get("output", "JEC.pdf");
   string Title             = CL.Get("title", "JEC Plots");
   bool OffsetMode          = CL.GetBool("offset", false);

   int N = FileNames.size();

   vector<JetCorrector *> JEC;
   for(int i = 0; i < N; i++)
      JEC.push_back(new JetCorrector(FileNames[i]));

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage(Title);

   double DefaultRho;

   PdfFile.AddTextPage("PT Dependence");
   DefaultRho = 10;
   PlotPTDependence(PdfFile,  0.0, DefaultRho, JEC, Labels, Form("eta =  0.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  0.5, DefaultRho, JEC, Labels, Form("eta =  0.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  1.0, DefaultRho, JEC, Labels, Form("eta =  1.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  1.5, DefaultRho, JEC, Labels, Form("eta =  1.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.0, DefaultRho, JEC, Labels, Form("eta =  2.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.5, DefaultRho, JEC, Labels, Form("eta =  2.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.9, DefaultRho, JEC, Labels, Form("eta =  2.9, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile, -2.9, DefaultRho, JEC, Labels, Form("eta = -2.9, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  3.0, DefaultRho, JEC, Labels, Form("eta =  3.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  3.5, DefaultRho, JEC, Labels, Form("eta =  3.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  4.0, DefaultRho, JEC, Labels, Form("eta =  4.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  4.5, DefaultRho, JEC, Labels, Form("eta =  4.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   DefaultRho = 30;
   PlotPTDependence(PdfFile,  0.0, DefaultRho, JEC, Labels, Form("eta =  0.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  0.5, DefaultRho, JEC, Labels, Form("eta =  0.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  1.0, DefaultRho, JEC, Labels, Form("eta =  1.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  1.5, DefaultRho, JEC, Labels, Form("eta =  1.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.0, DefaultRho, JEC, Labels, Form("eta =  2.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.5, DefaultRho, JEC, Labels, Form("eta =  2.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  2.9, DefaultRho, JEC, Labels, Form("eta =  2.9, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile, -2.9, DefaultRho, JEC, Labels, Form("eta = -2.9, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  3.0, DefaultRho, JEC, Labels, Form("eta =  3.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  3.5, DefaultRho, JEC, Labels, Form("eta =  3.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  4.0, DefaultRho, JEC, Labels, Form("eta =  4.0, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   PlotPTDependence(PdfFile,  4.5, DefaultRho, JEC, Labels, Form("eta =  4.5, rho = %.1f;p_{T}^{reco}", DefaultRho), 1000, 6, 500, OffsetMode);
   
   PdfFile.AddTextPage("Eta Dependence");
   DefaultRho = 10;
   PlotEtaDependence(PdfFile,  10, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 10,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  30, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 30,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  50, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 50,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  70, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 70,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 100, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 100, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 150, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 150, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 200, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 200, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 250, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 250, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 500, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 500, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   DefaultRho = 30;
   PlotEtaDependence(PdfFile,  10, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 10,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  30, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 30,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  50, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 50,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  70, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 70,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 100, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 100, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 150, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 150, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 200, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 200, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 250, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 250, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 500, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 500, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   DefaultRho = 50;
   PlotEtaDependence(PdfFile,  10, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 10,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  30, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 30,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  50, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 50,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile,  70, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 70,  rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 100, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 100, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 150, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 150, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 200, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 200, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 250, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 250, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);
   PlotEtaDependence(PdfFile, 500, DefaultRho, JEC, Labels, Form("p_{T}^{reco} = 500, rho = %.1f;#eta", DefaultRho), 1000, -5, 5, OffsetMode);

   PdfFile.AddTextPage("Rho Dependence");
   PlotRhoDependence(PdfFile,  10,  0.0, JEC, Labels, "p_{T}^{reco} = 10,  eta =  0.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30,  0.0, JEC, Labels, "p_{T}^{reco} = 30,  eta =  0.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100,  0.0, JEC, Labels, "p_{T}^{reco} = 100, eta =  0.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250,  0.0, JEC, Labels, "p_{T}^{reco} = 250, eta =  0.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500,  0.0, JEC, Labels, "p_{T}^{reco} = 500, eta =  0.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10,  2.0, JEC, Labels, "p_{T}^{reco} = 10,  eta =  2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30,  2.0, JEC, Labels, "p_{T}^{reco} = 30,  eta =  2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100,  2.0, JEC, Labels, "p_{T}^{reco} = 100, eta =  2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250,  2.0, JEC, Labels, "p_{T}^{reco} = 250, eta =  2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500,  2.0, JEC, Labels, "p_{T}^{reco} = 500, eta =  2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10,  2.9, JEC, Labels, "p_{T}^{reco} = 10,  eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  20,  2.9, JEC, Labels, "p_{T}^{reco} = 20,  eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30,  2.9, JEC, Labels, "p_{T}^{reco} = 30,  eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100,  2.9, JEC, Labels, "p_{T}^{reco} = 100, eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 200,  2.9, JEC, Labels, "p_{T}^{reco} = 200, eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250,  2.9, JEC, Labels, "p_{T}^{reco} = 250, eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500,  2.9, JEC, Labels, "p_{T}^{reco} = 500, eta =  2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10,  3.0, JEC, Labels, "p_{T}^{reco} = 10,  eta =  3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30,  3.0, JEC, Labels, "p_{T}^{reco} = 30,  eta =  3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100,  3.0, JEC, Labels, "p_{T}^{reco} = 100, eta =  3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250,  3.0, JEC, Labels, "p_{T}^{reco} = 250, eta =  3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500,  3.0, JEC, Labels, "p_{T}^{reco} = 500, eta =  3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10,  4.5, JEC, Labels, "p_{T}^{reco} = 10,  eta =  4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30,  4.5, JEC, Labels, "p_{T}^{reco} = 30,  eta =  4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100,  4.5, JEC, Labels, "p_{T}^{reco} = 100, eta =  4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250,  4.5, JEC, Labels, "p_{T}^{reco} = 250, eta =  4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500,  4.5, JEC, Labels, "p_{T}^{reco} = 500, eta =  4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10, -2.0, JEC, Labels, "p_{T}^{reco} = 10,  eta = -2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30, -2.0, JEC, Labels, "p_{T}^{reco} = 30,  eta = -2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100, -2.0, JEC, Labels, "p_{T}^{reco} = 100, eta = -2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250, -2.0, JEC, Labels, "p_{T}^{reco} = 250, eta = -2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500, -2.0, JEC, Labels, "p_{T}^{reco} = 500, eta = -2.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10, -2.9, JEC, Labels, "p_{T}^{reco} = 10,  eta = -2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30, -2.9, JEC, Labels, "p_{T}^{reco} = 30,  eta = -2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100, -2.9, JEC, Labels, "p_{T}^{reco} = 100, eta = -2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250, -2.9, JEC, Labels, "p_{T}^{reco} = 250, eta = -2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500, -2.9, JEC, Labels, "p_{T}^{reco} = 500, eta = -2.9;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10, -3.0, JEC, Labels, "p_{T}^{reco} = 10,  eta = -3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30, -3.0, JEC, Labels, "p_{T}^{reco} = 30,  eta = -3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100, -3.0, JEC, Labels, "p_{T}^{reco} = 100, eta = -3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250, -3.0, JEC, Labels, "p_{T}^{reco} = 250, eta = -3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500, -3.0, JEC, Labels, "p_{T}^{reco} = 500, eta = -3.0;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  10, -4.5, JEC, Labels, "p_{T}^{reco} = 10,  eta = -4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile,  30, -4.5, JEC, Labels, "p_{T}^{reco} = 30,  eta = -4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 100, -4.5, JEC, Labels, "p_{T}^{reco} = 100, eta = -4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 250, -4.5, JEC, Labels, "p_{T}^{reco} = 250, eta = -4.5;#rho",  1000, 0, 80, OffsetMode);
   PlotRhoDependence(PdfFile, 500, -4.5, JEC, Labels, "p_{T}^{reco} = 500, eta = -4.5;#rho",  1000, 0, 80, OffsetMode);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   for(auto P : JEC)
      if(P != NULL)
         delete P;

   return 0;
}

void PlotPTDependence(PdfFileHelper &PdfFile, double Eta, double Rho,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode)
{
   int Colors[] = {kBlack, kGreen + 3, kRed, kMagenta, kYellow + 1, kCyan};

   double Bins[10000];
   for(int i = 0; i <= Bin; i++)
      Bins[i] = exp((log(Max) - log(Min)) / Bin * i + log(Min));

   int N = JEC.size();

   vector<TH1D *> HResponse;
   for(int j = 0; j < N; j++)
   {
      HResponse.push_back(new TH1D(Form("HResponse%d", j), Title.c_str(), Bin, Bins));
      HResponse[j]->SetLineColor(Colors[j]);
      HResponse[j]->SetLineWidth(2);
   }

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponse[0]->GetBinCenter(i);

      for(int j = 0; j < N; j++)
      {
         JEC[j]->SetJetPT(X);
         JEC[j]->SetJetEta(Eta);
         JEC[j]->SetJetPhi(0);
         JEC[j]->SetRho(Rho);
         JEC[j]->SetJetArea(0.4 * 0.4 * M_PI);

         if(OffsetMode == false)
            HResponse[j]->SetBinContent(i, JEC[j]->GetCorrection());
         else
            HResponse[j]->SetBinContent(i, X - JEC[j]->GetCorrection() * X);
      }
   }

   double YMin = 0.85, YMax = 1.10;
   if(OffsetMode == true)
      YMin = -30, YMax = 30;
   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);

   if(OffsetMode == false)
      HWorld.GetYaxis()->SetTitle("Correction");
   else
      HWorld.GetYaxis()->SetTitle("Offset (GeV)");

   TCanvas Canvas;
   Canvas.SetLogx();

   HWorld.Draw("axis");

   for(TH1D *H : HResponse)
      H->Draw("same");

   TLegend Legend(0.2, 0.4, 0.6, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int j = 0; j < N; j++)
      Legend.AddEntry(HResponse[j], Labels[j].c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   for(TH1D *H : HResponse)
      delete H;
}

void PlotEtaDependence(PdfFileHelper &PdfFile, double PT, double Rho,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode)
{
   int Colors[] = {kBlack, kGreen + 3, kRed, kMagenta, kYellow + 1, kCyan};

   double Bins[10000];
   for(int i = 0; i <= Bin; i++)
      Bins[i] = (Max - Min) / Bin * i + Min;

   int N = JEC.size();

   vector<TH1D *> HResponse;
   for(int j = 0; j < N; j++)
   {
      HResponse.push_back(new TH1D(Form("HResponse%d", j), Title.c_str(), Bin, Bins));
      HResponse[j]->SetLineColor(Colors[j]);
      HResponse[j]->SetLineWidth(2);
   }

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponse[0]->GetBinCenter(i);

      for(int j = 0; j < N; j++)
      {
         JEC[j]->SetJetPT(PT);
         JEC[j]->SetJetEta(X);
         JEC[j]->SetJetPhi(0);
         JEC[j]->SetRho(Rho);
         JEC[j]->SetJetArea(0.4 * 0.4 * M_PI);

         if(OffsetMode == false)
            HResponse[j]->SetBinContent(i, JEC[j]->GetCorrection());
         else
            HResponse[j]->SetBinContent(i, PT - JEC[j]->GetCorrection() * PT);
      }
   }

   double YMin = 0.85, YMax = 1.10;
   if(OffsetMode == true)
      YMin = -30, YMax = 30;
   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);

   if(OffsetMode == false)
      HWorld.GetYaxis()->SetTitle("Correction");
   else
      HWorld.GetYaxis()->SetTitle("Offset (GeV)");

   TCanvas Canvas;

   HWorld.Draw("axis");

   for(TH1D *H : HResponse)
      H->Draw("same");

   TLegend Legend(0.2, 0.4, 0.6, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int j = 0; j < N; j++)
      Legend.AddEntry(HResponse[j], Labels[j].c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   for(TH1D *H : HResponse)
      delete H;
}

void PlotRhoDependence(PdfFileHelper &PdfFile, double PT, double Eta,
   vector<JetCorrector *> JEC, vector<string> Labels,
   string Title, int Bin, double Min, double Max, bool OffsetMode)
{
   int Colors[] = {kBlack, kGreen + 3, kRed, kMagenta, kYellow + 1, kCyan};

   double Bins[10000];
   for(int i = 0; i <= Bin; i++)
      Bins[i] = (Max - Min) / Bin * i + Min;

   int N = JEC.size();

   vector<TH1D *> HResponse;
   for(int j = 0; j < N; j++)
   {
      HResponse.push_back(new TH1D(Form("HResponse%d", j), Title.c_str(), Bin, Bins));
      HResponse[j]->SetLineColor(Colors[j]);
      HResponse[j]->SetLineWidth(2);
   }

   for(int i = 1; i <= 1000; i++)
   {
      double X = HResponse[0]->GetBinCenter(i);

      for(int j = 0; j < N; j++)
      {
         JEC[j]->SetJetPT(PT);
         JEC[j]->SetJetEta(Eta);
         JEC[j]->SetJetPhi(0);
         JEC[j]->SetRho(X);
         JEC[j]->SetJetArea(0.4 * 0.4 * M_PI);

         if(OffsetMode == false)
            HResponse[j]->SetBinContent(i, JEC[j]->GetCorrection());
         else
            HResponse[j]->SetBinContent(i, PT - JEC[j]->GetCorrection() * PT);
      }
   }

   double YMin = 0.85, YMax = 1.10;
   if(OffsetMode == true)
      YMin = -30, YMax = 30;
   TH2D HWorld("HWorld", Title.c_str(), Bin, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);

   if(OffsetMode == false)
      HWorld.GetYaxis()->SetTitle("Correction");
   else
      HWorld.GetYaxis()->SetTitle("Offset (GeV)");

   TCanvas Canvas;

   HWorld.Draw("axis");

   for(TH1D *H : HResponse)
      H->Draw("same");

   TLegend Legend(0.2, 0.4, 0.6, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int j = 0; j < N; j++)
      Legend.AddEntry(HResponse[j], Labels[j].c_str(), "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   for(TH1D *H : HResponse)
      delete H;
}





