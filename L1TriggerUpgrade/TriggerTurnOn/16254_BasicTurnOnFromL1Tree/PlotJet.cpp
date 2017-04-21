#include <iostream>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void Divide(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Title);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Curves.pdf");
   
   PdfFile.AddTextPage("Jet turn on curves");

   TFile FileTT140("Result/TT140.root");
   TFile FileTT200("Result/TT200.root");

   int N[] = {25, 50, 75, 100, 150, 200, 250, 300};

   for(int i = 0; i < 8; i++)
   {
      Divide(PdfFile, FileTT140,
         Form("l1upgrade_Jets/hjet%d", N[i]),  "l1upgrade_Jets/hjetgen", Form("%d (TT140)", N[i]));
      Divide(PdfFile, FileTT200,
         Form("l1upgrade_Jets/hjet%d", N[i]),  "l1upgrade_Jets/hjetgen", Form("%d (TT200)", N[i]));
   }
   
   FileTT200.Close();
   FileTT140.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Divide(PdfFileHelper &PdfFile, TFile &F, string N1, string N2, string Title)
{
   TH1D *H1 = (TH1D *)F.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F.Get(N2.c_str());

   TGraphAsymmErrors G;
   G.Divide(H1, H2);

   TH2D HWorld("HWorld", Form("%s;Jet PT (?);Efficiency", Title.c_str()), 100, 0, 600, 100, 0, 1.4);
   HWorld.SetStats(0);

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 100000, 1);
   
   TGraph GLineDashed;
   GLineDashed.SetPoint(0, 0, 0.95);
   GLineDashed.SetPoint(1, 100000, 0.95);
   GLineDashed.SetLineStyle(kDashed);

   /*
   TF1 Fit("Fit", "[0]+[1]*tanh([2]*(x-[3]))", 0, 400);
   Fit.SetParameter(0, 0.5);
   Fit.SetParameter(1, 0.5);
   Fit.SetParameter(2, 10);
   Fit.SetParameter(3, 100);
   G.Fit(&Fit);
   */
   
   TF1 Fit("Fit", "0.5+0.5*tanh([0]*(x-[1]))", 0, 600);
   Fit.SetParName(0, "Steepness");
   Fit.SetParName(1, "Mid-point");
   Fit.SetParameter(0, 0.05);
   Fit.SetParameter(1, atof(Title.substr(0, 3).c_str()));
   for(int i = 0; i < 10; i++)
      G.Fit(&Fit);

   TCanvas C;

   HWorld.Draw("axis");
   G.Draw("p");
   GLine.Draw("l");
   GLineDashed.Draw("l");

   // C.SetLogx();

   PdfFile.AddCanvas(C);
}




