#include <iostream>
using namespace std;

#include "TASImage.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"

int main()
{
   TASImage image("EventDisplay-191271_385661498_352_3DTower.png");
   int Height = image.GetHeight();
   int Width = image.GetWidth();

   cout << Width << " " << Height << endl;

   TCanvas C("C", "C", Width + 4, Height + 28);   // not sure why these are needed....tweaked to be correct
   C.SetMargin(0, 0, 0, 0);

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextColor(kWhite);
   Latex.SetTextSize(0.03);

   gStyle->SetPalette(53);
   image.Draw();

   Latex.DrawLatex(0.60, 0.25, "CMS Experiment      17:14:50 Apr. 15, 2012");
   Latex.DrawLatex(0.60, 0.20, "Run 191271, Event 385661498, Lumi 352");
   Latex.DrawLatex(0.60, 0.15, "m_{4l} = 128.971 GeV/c^{2}");
   Latex.DrawLatex(0.60, 0.10, "m_{1} = 82.280 GeV/c^{2}, m_{2} = 36.265 GeV/c^{2}");

   Latex.DrawLatex(0.20, 0.10, "#mu^{+}, p_{T} = 25.9, #eta = 0.95, #phi = -1.16");
   Latex.DrawLatex(0.05, 0.65, "#mu^{-}, p_{T} = 21.3, #eta = 0.93, #phi = 0.05");
   Latex.DrawLatex(0.25, 0.90, "#mu^{+}, p_{T} = 15.5, #eta = -0.08, #phi = 2.07");
   Latex.DrawLatex(0.70, 0.50, "#mu^{-}, p_{T} = 18.4., #eta = -1.63, #phi = 0.88");

   C.SaveAs("HiggsDiscovery-Results-EventDisplay.png");
   // C.SaveAs("HiggsDiscovery-Results-EventDisplay.C");
   // C.SaveAs("HiggsDiscovery-Results-EventDisplay.eps");
   // C.SaveAs("HiggsDiscovery-Results-EventDisplay.pdf");

   return 0;
}


