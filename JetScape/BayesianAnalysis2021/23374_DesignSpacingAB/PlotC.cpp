#include <vector>
#include <iostream>
using namespace std;

#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
double IntegralPDF(double xB, double a, double b);
void SavePlot(TH1 &H, string Option = "");

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   PdfFileHelper PdfFile("Parameters.pdf");
   PdfFile.AddTextPage("C1 & C2");

   PdfFile.AddTextPage("C3");

   vector<double> XBs{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
   double XB0 = 0.05;

   for(double XB : XBs)
   {
      TH2D H("H", Form("X_{B} = %.2f;a;b", XB), 500, -10, 100, 500, -10, 100);
      H.SetStats(0);

      for(int iX = 1; iX <= H.GetNbinsX(); iX++)
      {
         double X = H.GetXaxis()->GetBinCenter(iX);
         for(int iY = 1; iY <= H.GetNbinsY(); iY++)
         {
            double Y = H.GetYaxis()->GetBinCenter(iY);
            H.SetBinContent(iX, iY, IntegralPDF(XB, X, Y) / IntegralPDF(XB0, X, Y));
         }
      }

      PdfFile.AddPlot(H, "colz");
      SavePlot(H, "colz");
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double IntegralPDF(double xB, double a, double b)
{
   double Xmin=0.01, Xmax=0.99, X=0, dX=0, ans=0; int N=100; 
   if(xB > Xmax) {ans=0;}
   else 
   {
      for(int i=0; i<N; i++)
      {
         dX = (Xmax - xB)/N;
         X= xB + (i+0.5)*dX;   
         if (X<Xmin){X=Xmin;}
         ans = ans + pow(X,a)*pow(1-X,b)*dX;
      }
   }
   //JSINFO<<"(xB,a,b)=("<<xB<<","<<a<<","<<b<<"), \t Area="<<ans;
   return ans;
}

void SavePlot(TH1 &H, string Option)
{
   static int Index = 0;
   Index = Index + 1;

   TCanvas Canvas;

   H.Draw(Option.c_str());

   Canvas.SaveAs(Form("Plots/Parameters%d.png", Index));
}


