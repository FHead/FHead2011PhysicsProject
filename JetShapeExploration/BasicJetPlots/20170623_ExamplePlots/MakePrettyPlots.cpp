#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   // Set plot style
   SetThesisStyle();

   // Output pdf file
   PdfFileHelper PdfFile("PrettyPlots.pdf");
   PdfFile.AddTextPage("Some first plots!");

   // Input file
   TFile File("ScaledResult/PP6Dijet.root");

   // Add a bunch of histograms from the file
   PdfFile.AddTextPage("PTHat Plots");
   PdfFile.AddHistogramFromFile(File, "HPTHat", "", true);
   PdfFile.AddHistogramFromFile(File, "HPTHatSelected", "", true);
   
   PdfFile.AddTextPage("Jet Plots");
   PdfFile.AddHistogramFromFile(File, "HJetPT", "", true);
   PdfFile.AddHistogramFromFile(File, "HJetEta", "", false);
   PdfFile.AddHistogramFromFile(File, "HJetPhi", "", false);
   PdfFile.AddHistogramFromFile(File, "HJetEtaSmallPT", "", false);
   PdfFile.AddHistogramFromFile(File, "HJetPhiSmallPT", "", false);

   // Cleanup
   File.Close();

   // Add a time stamp and close the pdf file
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



