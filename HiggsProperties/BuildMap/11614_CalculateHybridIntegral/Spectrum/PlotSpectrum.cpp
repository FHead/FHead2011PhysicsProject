#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

int main();
double CalculateValue(const vector<double> &X, const vector<double> &Y, double x);

int main()
{
   // Read cross section
   vector<double> CrossSectionMass, CrossSection;
   ifstream CrossSectionFile("HiggsCrossSection");
   while(CrossSectionFile)
   {
      double temp1 = -1, temp2 = -1, junk;
      CrossSectionFile >> temp1 >> temp2 >> junk >> junk >> junk >> junk;

      if(temp1 < 0 || temp2 < 0)
         continue;

      CrossSectionMass.push_back(temp1);
      CrossSection.push_back(temp2);
   }
   CrossSectionFile.close();

   // Read branching ratio
   vector<double> BranchingRatioMass, BranchingRatio;
   ifstream BranchingRatioFile("HiggsZZBranchingRatio");
   while(BranchingRatioFile)
   {
      double temp1 = -1, temp2 = -1;
      BranchingRatioFile >> temp1 >> temp2;

      if(temp1 < 0 || temp2 < 0)
         continue;

      BranchingRatioMass.push_back(temp1);
      BranchingRatio.push_back(temp2);
   }
   BranchingRatioFile.close();

   // Initialize plot helper
   PsFileHelper PsFile("Spectrum.ps");
   PsFile.AddTextPage("Spectrum hacks");

   // Make some plots convincing everyone that things are working
   TH1D HCrossSection("HCrossSection", "Higgs cross section as a function of mass", 160, 90, 250);
   TH1D HBranchingRatio("HBranchingRatio", "Higgs ZZ branching ratio as a function of mass", 160, 90, 250);
   TH1D HZZCrossSection("HZZCrossSection", "Higgs ZZ cross section as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionM("HZZCrossSectionM", "Higgs ZZ cross section (xM) as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionMM("HZZCrossSectionMM", "Higgs ZZ cross section (xM^{2}) as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionMMM("HZZCrossSectionMMM", "Higgs ZZ cross section (xM^{3}) as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionMMMM("HZZCrossSectionMMMM", "Higgs ZZ cross section (xM^{4}) as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionMMMMM("HZZCrossSectionMMMMM", "Higgs ZZ cross section (xM^{5}) as a function of mass", 160, 90, 250);
   TH1D HZZCrossSectionMMMMMM("HZZCrossSectionMMMMMM", "Higgs ZZ cross section (xM^{6}) as a function of mass", 160, 90, 250);
   
   for(int i = 1; i <= HCrossSection.GetNbinsX(); i++)
   {
      double Mass = HCrossSection.GetBinCenter(i);
      HCrossSection.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass));
      HBranchingRatio.Fill(Mass, CalculateValue(BranchingRatioMass, BranchingRatio, Mass));
      HZZCrossSection.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass));
      HZZCrossSectionM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass);
      HZZCrossSectionMM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass * Mass);
      HZZCrossSectionMMM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass * Mass * Mass);
      HZZCrossSectionMMMM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass * Mass * Mass * Mass);
      HZZCrossSectionMMMMM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass * Mass * Mass * Mass * Mass);
      HZZCrossSectionMMMMMM.Fill(Mass, CalculateValue(CrossSectionMass, CrossSection, Mass)
         * CalculateValue(BranchingRatioMass, BranchingRatio, Mass) * Mass * Mass * Mass * Mass * Mass * Mass);
   }

   PsFile.AddPlot(HCrossSection, "", true);
   PsFile.AddPlot(HBranchingRatio, "", true);
   PsFile.AddPlot(HZZCrossSection, "", true);
   PsFile.AddPlot(HZZCrossSectionM, "", true);
   PsFile.AddPlot(HZZCrossSectionMM, "", true);
   PsFile.AddPlot(HZZCrossSectionMMM, "", true);
   PsFile.AddPlot(HZZCrossSectionMMMM, "", true);
   PsFile.AddPlot(HZZCrossSectionMMMMM, "", true);
   PsFile.AddPlot(HZZCrossSectionMMMMMM, "", true);

   /*
   HZZCrossSectionMMM.Smooth(5);
   PsFile.AddPlot(HZZCrossSectionMMM, "", true);
   HZZCrossSectionMMM.Smooth(5);
   PsFile.AddPlot(HZZCrossSectionMMM, "", true);
   HZZCrossSectionMMM.Smooth(5);
   PsFile.AddPlot(HZZCrossSectionMMM, "", true);
   */

   // Clean-up
   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double CalculateValue(const vector<double> &X, const vector<double> &Y, double x)
{
   if(X.size() != Y.size())
   {
      cerr << "Meow..." << endl;
      return -1;
   }

   if(x < X[0])
      return Y[0];
   if(x >= X[X.size()-1])
      return Y[X.size()-1];

   int Index = 0;
   for(int i = 1; i < (int)X.size(); i++)
   {
      if(x < X[i])
      {
         Index = i - 1;
         break;
      }
   }

   return Y[Index] * exp((x - X[Index]) / (X[Index+1] - X[Index]) * (log(Y[Index+1]) - log(Y[Index])));
}

