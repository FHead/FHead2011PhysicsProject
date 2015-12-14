#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "PlotHelper.h"

void ProducePDF(string InputName = "FinalOutput.root");

void ProducePDF(string InputName)
{
   PsFileHelper PsFile("FinalResult.ps");
   PsFile.AddTextPage("Toys on extracting 4-jet bin");

   TFile F(InputName.c_str());

   vector<string> ExplanationText;
   ExplanationText.push_back("Compare the following:");
   ExplanationText.push_back("   - extract alpha (beta fixed at zero) from 1-3 jet bins and extrapolate");
   ExplanationText.push_back("   - extract with unconstrained fit");
   ExplanationText.push_back("Assume statistics similar to 2010 dataset");
   PsFile.AddTextPage(ExplanationText);

   PsFile.AddHistogramFromFile(F, "HFourthBinPrediction");
   
   PsFile.AddHistogramFromFile(F, "HFourthBinExtraction");
   
   PsFile.AddHistogramFromFile(F, "HDifference");

   vector<string> DifferencePullExplanation;
   DifferencePullExplanation.push_back("Error on extraction is from the fit");
   DifferencePullExplanation.push_back("Error on prediction is calculated as follows:");
   DifferencePullExplanation.push_back("   Error^2 = (sigma_yield / alpha^3)^2");
   DifferencePullExplanation.push_back("      + (3 * sigma_alpha * yield / alpha^4)^2");
   DifferencePullExplanation.push_back("   where yield is the (>=1) yield from the fit");
   DifferencePullExplanation.push_back("Total error used as denominator is summed in quadrature the above two");
   PsFile.AddTextPage(DifferencePullExplanation);

   TH1D *DifferencePull = (TH1D *)F.Get("HDifferencePull");
   DifferencePull->Fit("gaus");
   PsFile.AddPlot(DifferencePull);

   TH1D *DifferencePull2 = (TH1D *)F.Get("HDifferencePull2");
   DifferencePull2->Fit("gaus");
   PsFile.AddPlot(DifferencePull2);

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}



