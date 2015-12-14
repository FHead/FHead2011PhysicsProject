//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
//---------------------------------------------------------------------------
#include "PlotHelper2.h"
//---------------------------------------------------------------------------
int main()
{
   // Inputs - could change to program arguments if needed
   string Toy1File = "LL_Scalar.toyll";
   string Toy2File = "LL_Pseudoscalar.toyll";
   int ToyCount = 5;

   ifstream in1(Toy1File.c_str());
   ifstream in2(Toy2File.c_str());

   // Histograms
   double Modifier = 1;
   if(ToyCount >= 50)
      Modifier = 2;
   if(ToyCount < 5)
      Modifier = 0.15;
   TH1D HScalar("HScalar", "LL distribution for scalar map toys;LL", 100, -40 * Modifier, 80 * Modifier);
   TH1D HPseudoScalar("HPseudoScalar", "LL distribution for pseudo-scalar map toys;LL", 100, -40 * Modifier, 80 * Modifier);

   HPseudoScalar.SetLineColor(kRed);
   
   // Loop!  ...and fill histograms
   while(in1)
   {
      double Total = 0;
      for(int i = 0; i < ToyCount; i++)
      {
         double Temp = -99999;
         in1 >> Temp;
         Total = Total + Temp;
      }

      if(Total < -90000)   // maybe the end of file
         continue;

      HScalar.Fill(Total);
   }
   while(in2)
   {
      double Total = 0;
      for(int i = 0; i < ToyCount; i++)
      {
         double Temp = -99999;
         in2 >> Temp;
         Total = Total + Temp;
      }

      if(Total < -90000)   // maybe the end of file
         continue;

      HPseudoScalar.Fill(-Total);
   }

   // close files
   in2.close();
   in1.close();

   // write to output
   PsFileHelper PsFile(Form("ToyResult_%d.ps", ToyCount));
   PsFile.AddTextPage("Result of toys");

   vector<string> Explanations;
   Explanations.push_back("Starting from the scalar and pseudoscalar maps");
   Explanations.push_back("Generate 300000 pseudo-datasets each (roughly), where each pseudo-dataset");
   Explanations.push_back(Form("      contains %d events", ToyCount));
   Explanations.push_back("For each dataset, evaluate likelihood on two maps and look at the ratio");
   Explanations.push_back("The x axis will be log(pseudoscalar) - log(scalar) summed over all 30 events");
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   PsFile.AddPlot(HScalar, "", false);
   PsFile.AddPlot(HScalar, "", true);
   PsFile.AddPlot(HPseudoScalar, "", false);
   PsFile.AddPlot(HPseudoScalar, "", true);

   TLegend Legend(0.55, 0.8, 0.85, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HScalar, "Toys from scalar map", "l");
   Legend.AddEntry(&HPseudoScalar, "Toys from pseudo-scalar map", "l");

   HScalar.SetStats(0);
   HPseudoScalar.SetStats(0);

   HPseudoScalar.SetTitle(Form("LL distribution for different maps with dataset size %d", ToyCount));

   TCanvas C;
   HPseudoScalar.Draw();
   HScalar.Draw("same");
   Legend.Draw();
   PsFile.AddCanvas(C);

   C.SaveAs(Form("Separation_%d_Linear.png", ToyCount));
   C.SaveAs(Form("Separation_%d_Linear.C", ToyCount));
   C.SaveAs(Form("Separation_%d_Linear.eps", ToyCount));
   C.SaveAs(Form("Separation_%d_Linear.pdf", ToyCount));

   C.SetLogy();
   PsFile.AddCanvas(C);

   C.SaveAs(Form("Separation_%d_Log.png", ToyCount));
   C.SaveAs(Form("Separation_%d_Log.C", ToyCount));
   C.SaveAs(Form("Separation_%d_Log.eps", ToyCount));
   C.SaveAs(Form("Separation_%d_Log.pdf", ToyCount));

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}
//---------------------------------------------------------------------------

