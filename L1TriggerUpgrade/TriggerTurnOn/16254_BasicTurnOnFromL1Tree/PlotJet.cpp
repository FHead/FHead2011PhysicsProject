#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double Divide(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Title, double Max, string Type, string Tag);
double Find95(TF1 &F, double Min, double Max);

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " InputFile140 InputFile200 Tag" << endl;
      return -1;
   }

   string Tag = argv[1];

   SetThesisStyle();

   PdfFileHelper PdfFile(string("Curves") + argv[3] + ".pdf");

   PdfFile.AddTextPage("Jet turn on curves");

   TFile FileTT140(argv[1]);
   TFile FileTT200(argv[2]);

   TFile FileOutput(Form("TurnOnCurves%s.root", argv[3]), "RECREATE");

   int N[] = {25, 50, 75, 100, 150, 200, 250, 300};

   for(int i = 0; i < 8; i++)
   {
      double TT140 = Divide(PdfFile, FileTT140,
         Form("l1upgrade_Jets/hjet%d", N[i]), "l1upgrade_Jets/hjetgen",
         Form("%d (140)", N[i]), 600, "Jet",
         Form("Jet%d_140", N[i]));
      double TT200 = Divide(PdfFile, FileTT200,
         Form("l1upgrade_Jets/hjet%d", N[i]),  "l1upgrade_Jets/hjetgen",
         Form("%d (200)", N[i]), 600, "Jet",
         Form("Jet%d_200", N[i]));

      cout << "95 point 0 " << N[i] << " " << TT140 << " " << TT200 << endl;
   }

   PdfFile.AddTextPage("Track EG turn on curves");

   int NEG[] = {12, 15, 20, 25, 30};

   for(int i = 0; i < 5; i++)
   {
      double EG140 = Divide(PdfFile, FileTT140,
         Form("l1upgrade_EGamma/hTkIsoeg%d", NEG[i]),  "l1upgrade_EGamma/hTkIsoeggen",
         Form("%d (140, iso eg)", NEG[i]), 50, "EG",
         Form("IsoEG%d_140", NEG[i]));
      double EG200 = Divide(PdfFile, FileTT200,
         Form("l1upgrade_EGamma/hTkIsoeg%d", NEG[i]),  "l1upgrade_EGamma/hTkIsoeggen",
         Form("%d (200, iso eg)", NEG[i]), 50, "EG",
         Form("IsoEG%d_200", NEG[i]));

      cout << "95 point 1 " << NEG[i] << " " << EG140 << " " << EG200 << endl;

      double EM140 = Divide(PdfFile, FileTT140,
         Form("l1upgrade_EGamma/htkeg%d", NEG[i]),  "l1upgrade_EGamma/htkeggen",
         Form("%d (140, eg)", NEG[i]), 50, "EG",
         Form("EG%d_140", NEG[i]));
      double EM200 = Divide(PdfFile, FileTT200,
         Form("l1upgrade_EGamma/htkeg%d", NEG[i]),  "l1upgrade_EGamma/htkeggen",
         Form("%d (200, eg)", NEG[i]), 50, "EG",
         Form("EG%d_200", NEG[i]));

      cout << "95 point 2 " << NEG[i] << " " << EM140 << " " << EM200 << endl;
   }

   FileOutput.Close();

   FileTT200.Close();
   FileTT140.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double Divide(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Title, double Max, string Type, string Tag)
{
   TH1D *H1 = (TH1D *)F.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return 0;

   TGraphAsymmErrors G;
   G.Divide(H1, H2);

   G.SetNameTitle(Form("%s_TurnOn", Tag.c_str()), "");
   G.Write();

   TH2D HWorld("HWorld", Form("%s;Gen particle PT;Efficiency", Title.c_str()), 100, 0, Max, 100, 0, 1.4);
   HWorld.SetStats(0);

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 100000, 1);

   TGraph GLineDashed;
   GLineDashed.SetPoint(0, 0, 0.95);
   GLineDashed.SetPoint(1, 100000, 0.95);
   GLineDashed.SetLineStyle(kDashed);

   string Function = "gaus";
   if(Type == "Jet")
      Function = "ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], 0) - exp(-[0]*(x-[1])+[0]*[0]*[2]*[2]/2)*ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], [0]*[0]*[2]*[2])";
   else
      // Function = "ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], 0) - exp(-[0]*(x-[1])+[0]*[0]*[2]*[2]/2)*ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], [0]*[0]*[2]*[2])";
      Function = "[2]/2+[2]/2*tanh([0]*(x-[1]))";

   TF1 Fit(Form("%s_Fit", Tag.c_str()), Function.c_str(), 0, Max);
   if(Type == "Jet")
   {
      Fit.SetParName(0, "#lambda");
      Fit.SetParName(1, "#mu");
      Fit.SetParName(2, "#sigma");
      Fit.SetParameter(0, 0.1);
      Fit.SetParameter(1, atof(Title.substr(0, 3).c_str()));
      Fit.SetParameter(2, 10);
   }
   else
   {
      // Fit.SetParName(0, "#lambda");
      // Fit.SetParName(1, "#mu");
      // Fit.SetParName(2, "#sigma");
      // Fit.SetParameter(0, 0.2);
      // Fit.SetParameter(1, atof(Title.substr(0, 3).c_str()) * 0.8);
      // Fit.SetParameter(2, 0.8);
      Fit.SetParName(0, "Steepness");
      Fit.SetParName(1, "Mid-point");
      Fit.SetParName(2, "Plateau");
      Fit.SetParameter(0, 0.05);
      Fit.SetParameter(1, atof(Title.substr(0, 3).c_str()));
      Fit.SetParameter(2, 0.99);
   }
   for(int i = 0; i < 10; i++)
      G.Fit(&Fit);

   TCanvas C;

   HWorld.Draw("axis");
   G.Draw("p");
   GLine.Draw("l");
   GLineDashed.Draw("l");
   Fit.Draw("l same");

   // C.SetLogx();

   PdfFile.AddCanvas(C);

   Fit.SetNpx(2000);
   TH1F *FitHistogram = (TH1F *)Fit.GetHistogram()->Clone(Form("%s_FitHistogram", Tag.c_str()));
   FitHistogram->Write();

   return Find95(Fit, 1, Max);
}

double Find95(TF1 &F, double Min, double Max)
{
   double Target = 0.95;

   if(F.Eval(Min) > Target || F.Eval(Max) < Target)
      return -1000;

   double L = Min;
   double R = Max;

   while(R - L > 1e-4)
   {
      double C = (L + R) / 2;
      double V = F.Eval(C);

      if(V < Target)
         L = C;
      else
         R = C;
   }

   return (R + L) / 2;
}



