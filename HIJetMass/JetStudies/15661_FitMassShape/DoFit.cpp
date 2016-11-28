#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   // TF1 Function("Function", "[0]*exp(-(x-[1])**2/(2*[2]*[2]))+[3]*(tanh(200*(x-[1]))+1)*(exp(-[4]*x)+[5]*exp(-[6]*x))*(tanh([7]*(x-[8])+1))");
   // Function.SetParameter(0, 10);
   // Function.SetParameter(1, 0.05);
   // Function.FixParameter(2, 0.01);
   // Function.SetParameter(3, 10);
   // Function.SetParameter(4, 36);
   // Function.SetParameter(5, 1);
   // Function.SetParameter(6, 2);
   // Function.SetParameter(7, -80);
   // Function.FixParameter(8, 0.24);
   
   // TF1 Function("Function", "[0]*exp(-(x*x)/(2*[1]*[1]))*(tanh([2]*x)+1)");
   // Function.SetParameter(1, 0.05);
   // Function.SetParameter(2, 1);

   TF1 Function("Function", "[0]*(tanh([1]*(x-[2]))+1)*(tanh([3]*(x-[4]))+1)*(exp(-[5]*x)+[6]*exp(-[7]*x))*(tanh([8]*(x-[9]))+1)");
   Function.SetParameter(1, 40);
   Function.SetParameter(2, 0.03);
   Function.SetParameter(3, 20);
   Function.SetParameter(4, -0.03);
   Function.SetParameter(5, 36);
   Function.SetParameter(7, 0.6);
   Function.SetParameter(8, -40);
   Function.FixParameter(9, 0.24);
   
   TFile File("PP6Dijet.root");

   TH1D H("H", "H", 160, 0, 0.4);

   TTree *T = (TTree *)File.Get("OutputTree");

   T->Draw("NewJetSDMass2/NewJetPT>>H", "MCWeight * (JetPT > 120 && JetPT < 140 && NewJetSDMass2 > 0)", "hist");
   H.Scale(1 / H.Integral());

   H.Fit(&Function, "", "", 0, 0.40);

   PdfFileHelper PdfFile("FitResult.pdf");
   PdfFile.AddTextPage("fit");

   PdfFile.AddPlot(H);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   File.Close();

   return 0;
}



