#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TAxis.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"

#include "Utilities.hcpp"

int main(int argc, char *argv[])
{
   gStyle->SetPaintTextFormat(".2e");

   string InputFileName = "ResultTree.root";
   string OutputFileName = "MatrixPlots.root";

   if(argc > 1)   InputFileName = argv[1];
   if(argc > 2)   OutputFileName = argv[2];

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HEntryCount("HEntryCount", "Entry count!", 1, 0, 1);
   TH2D HMatrixVeryLoose2e2mu("HMatrixVeryLoose2e2mu", "Matrix, VeryLoose!", 14, 0, 14, 14, 0, 14);
   TH2D HAbsMatrixVeryLoose2e2mu("HAbsMatrixVeryLoose2e2mu", "abs. Matrix, VeryLoose!", 14, 0, 14, 14, 0, 14);
   TH2D HMatrixLoose2e2mu("HMatrixLoose2e2mu", "Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HAbsMatrixLoose2e2mu("HAbsMatrixLoose2e2mu", "abs. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HMatrixTight2e2mu("HMatrixTight2e2mu", "Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HMatrixTight2e2muReal("HMatrixTight2e2muReal", "Matrix, tight!  real only!", 7, 0, 7, 7, 0, 7);
   TH2D HAbsMatrixTight2e2mu("HAbsMatrixTight2e2mu", "abs. Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HAbsMatrixTight2e2muReal("HAbsMatrixTight2e2muReal", "abs. Matrix, tight!  real only!", 7, 0, 7, 7, 0, 7);
   TH2D HMatrixLoose4e("HMatrixLoose4e", "Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HAbsMatrixLoose4e("HAbsMatrixLoose4e", "abs. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HMatrixTight4e("HMatrixTight4e", "Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HAbsMatrixTight4e("HAbsMatrixTight4e", "abs. Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HNormMatrixVeryLoose2e2mu("HNormMatrixVeryLoose2e2mu", "norm. Matrix, VeryLoose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormAbsMatrixVeryLoose2e2mu("HNormAbsMatrixVeryLoose2e2mu", "norm. abs. Matrix, VeryLoose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormMatrixLoose2e2mu("HNormMatrixLoose2e2mu", "norm. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormAbsMatrixLoose2e2mu("HNormAbsMatrixLoose2e2mu", "norm. abs. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormMatrixTight2e2mu("HNormMatrixTight2e2mu", "norm. Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HNormAbsMatrixTight2e2mu("HNormAbsMatrixTight2e2mu", "norm. abs. Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HNormMatrixLoose4e("HNormMatrixLoose4e", "norm. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormAbsMatrixLoose4e("HNormAbsMatrixLoose4e", "norm. abs. Matrix, loose!", 14, 0, 14, 14, 0, 14);
   TH2D HNormMatrixTight4e("HNormMatrixTight4e", "norm. Matrix, tight!", 14, 0, 14, 14, 0, 14);
   TH2D HNormAbsMatrixTight4e("HNormAbsMatrixTight4e", "norm. abs. Matrix, tight!", 14, 0, 14, 14, 0, 14);

   PrepareHistogram(HMatrixVeryLoose2e2mu);
   PrepareHistogram(HAbsMatrixVeryLoose2e2mu);
   PrepareHistogram(HMatrixLoose2e2mu);
   PrepareHistogram(HAbsMatrixLoose2e2mu);
   PrepareHistogram(HMatrixTight2e2mu);
   PrepareHistogramReal(HMatrixTight2e2muReal);
   PrepareHistogram(HAbsMatrixTight2e2mu);
   PrepareHistogramReal(HAbsMatrixTight2e2muReal);
   PrepareHistogram(HMatrixLoose4e);
   PrepareHistogram(HAbsMatrixLoose4e);
   PrepareHistogram(HMatrixTight4e);
   PrepareHistogram(HAbsMatrixTight4e);
   PrepareHistogram(HNormMatrixVeryLoose2e2mu);
   PrepareHistogram(HNormAbsMatrixVeryLoose2e2mu);
   PrepareHistogram(HNormMatrixLoose2e2mu);
   PrepareHistogram(HNormAbsMatrixLoose2e2mu);
   PrepareHistogram(HNormMatrixTight2e2mu);
   PrepareHistogram(HNormAbsMatrixTight2e2mu);
   PrepareHistogram(HNormMatrixLoose4e);
   PrepareHistogram(HNormAbsMatrixLoose4e);
   PrepareHistogram(HNormMatrixTight4e);
   PrepareHistogram(HNormAbsMatrixTight4e);

   TFile File(InputFileName.c_str());  

   TTree *Tree = (TTree *)File.Get("Tree");

   double Weight[92][4] = {{0}};
   EventParameters Event2e2mu, Event4e;

   Tree->SetBranchAddress("MH", &Event2e2mu.HMass);
   Tree->SetBranchAddress("M1", &Event2e2mu.ZMass);
   Tree->SetBranchAddress("M2", &Event2e2mu.Z2Mass);
   Tree->SetBranchAddress("Phi0", &Event2e2mu.Phi0);
   Tree->SetBranchAddress("Theta0", &Event2e2mu.Theta0);
   Tree->SetBranchAddress("Phi", &Event2e2mu.Phi);
   Tree->SetBranchAddress("Theta1", &Event2e2mu.Theta1);
   Tree->SetBranchAddress("Theta2", &Event2e2mu.Theta2);
   Tree->SetBranchAddress("HPT", &Event2e2mu.PTH);
   Tree->SetBranchAddress("HPhi", &Event2e2mu.PhiH);
   Tree->SetBranchAddress("HY", &Event2e2mu.YH);
   Tree->SetBranchAddress("PhiOffset", &Event2e2mu.PhiOffset);
   Tree->SetBranchAddress("RecalculatedMH", &Event4e.HMass);
   Tree->SetBranchAddress("RecalculatedM1", &Event4e.ZMass);
   Tree->SetBranchAddress("RecalculatedM2", &Event4e.Z2Mass);
   Tree->SetBranchAddress("RecalculatedPhi0", &Event4e.Phi0);
   Tree->SetBranchAddress("RecalculatedTheta0", &Event4e.Theta0);
   Tree->SetBranchAddress("RecalculatedPhi", &Event4e.Phi);
   Tree->SetBranchAddress("RecalculatedTheta1", &Event4e.Theta1);
   Tree->SetBranchAddress("RecalculatedTheta2", &Event4e.Theta2);
   Tree->SetBranchAddress("RecalculatedHPT", &Event4e.PTH);
   Tree->SetBranchAddress("RecalculatedHPhi", &Event4e.PhiH);
   Tree->SetBranchAddress("RecalculatedHY", &Event4e.YH);
   Tree->SetBranchAddress("RecalculatedPhiOffset", &Event4e.PhiOffset);
   Tree->SetBranchAddress("Weight", Weight);

   int EntryCount = Tree->GetEntries();

   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % (EntryCount / 300) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      HEntryCount.Fill(0);

      LeptonVectors Lepton2e2mu = ConvertAnglesToVectorsRoberto(Event2e2mu);
      LeptonVectors Lepton4e = ConvertAnglesToVectorsRoberto(Event4e);

      double PassVeryLoose2e2mu = VeryLooseCut2e2mu(Lepton2e2mu);
      double PassLoose2e2mu = LooseCut2e2mu(Lepton2e2mu);
      double PassTight2e2mu = TightCut2e2mu(Lepton2e2mu);
      double PassLoose4e = LooseCut4e(Lepton4e);
      double PassTight4e = TightCut4e(Lepton4e);

      for(int iX = 1; iX <= HMatrixLoose2e2mu.GetNbinsX(); iX++)
      {
         for(int iY = 1; iY <= HMatrixLoose2e2mu.GetNbinsX(); iY++)
         {
            int Index = GetIndex(iX - 1, iY - 1);
            int Sign = 1;

            if(Index < 0)
            {
               Index = -Index;
               Sign = -1;
            }

            double MassWeight2e2mu = Event2e2mu.ZMass * Event2e2mu.Z2Mass;
            double MassWeight4e = Event2e2mu.ZMass * Event2e2mu.Z2Mass;

            if(Index != 0)
            {
               if(PassVeryLoose2e2mu == true)
               {
                  HMatrixVeryLoose2e2mu.Fill(iX - 1, iY - 1, Sign * Weight[Index][0] * MassWeight2e2mu);
                  HAbsMatrixVeryLoose2e2mu.Fill(iX - 1, iY - 1, fabs(Sign * Weight[Index][0] * MassWeight2e2mu));
               }
               if(PassLoose2e2mu == true)
               {
                  HMatrixLoose2e2mu.Fill(iX - 1, iY - 1, Sign * Weight[Index][0] * MassWeight2e2mu);
                  HAbsMatrixLoose2e2mu.Fill(iX - 1, iY - 1, fabs(Sign * Weight[Index][0] * MassWeight2e2mu));
               }
               if(PassTight2e2mu == true)
               {
                  HMatrixTight2e2mu.Fill(iX - 1, iY - 1, Sign * Weight[Index][0] * MassWeight2e2mu);
                  HAbsMatrixTight2e2mu.Fill(iX - 1, iY - 1, fabs(Sign * Weight[Index][0] * MassWeight2e2mu));
                  if(iX % 2 == 1 && iY % 2 == 1)
                  {
                     HMatrixTight2e2muReal.Fill((iX - 1) / 2, (iY - 1) / 2,
                        (Sign * Weight[Index][0] * MassWeight2e2mu));
                     HAbsMatrixTight2e2muReal.Fill((iX - 1) / 2, (iY - 1) / 2,
                        fabs(Sign * Weight[Index][0] * MassWeight2e2mu));
                  }
               }
               if(PassLoose4e == true)
               {
                  HMatrixLoose4e.Fill(iX - 1, iY - 1, Sign * Weight[Index][1] * MassWeight4e);
                  HAbsMatrixLoose4e.Fill(iX - 1, iY - 1, fabs(Sign * Weight[Index][1] * MassWeight4e));
               }
               if(PassTight4e == true)
               {
                  HMatrixTight4e.Fill(iX - 1, iY - 1, Sign * Weight[Index][1] * MassWeight4e);
                  HAbsMatrixTight4e.Fill(iX - 1, iY - 1, fabs(Sign * Weight[Index][1] * MassWeight4e));
               }
            }
         }
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   /*
   HMatrixVeryLoose2e2mu.Scale(1.0 / EntryCount);
   HAbsMatrixVeryLoose2e2mu.Scale(1.0 / EntryCount);
   HMatrixLoose2e2mu.Scale(1.0 / EntryCount);
   HAbsMatrixLoose2e2mu.Scale(1.0 / EntryCount);
   HMatrixTight2e2mu.Scale(1.0 / EntryCount);
   HAbsMatrixTight2e2mu.Scale(1.0 / EntryCount);
   HMatrixLoose4e.Scale(1.0 / EntryCount);
   HAbsMatrixLoose4e.Scale(1.0 / EntryCount);
   HMatrixTight4e.Scale(1.0 / EntryCount);
   HAbsMatrixTight4e.Scale(1.0 / EntryCount);

   FillNormalizedHistogram(HMatrixVeryLoose2e2mu, HNormMatrixVeryLoose2e2mu);
   FillNormalizedHistogram(HAbsMatrixVeryLoose2e2mu, HNormAbsMatrixVeryLoose2e2mu);
   FillNormalizedHistogram(HMatrixLoose2e2mu, HNormMatrixLoose2e2mu);
   FillNormalizedHistogram(HAbsMatrixLoose2e2mu, HNormAbsMatrixLoose2e2mu);
   FillNormalizedHistogram(HMatrixTight2e2mu, HNormMatrixTight2e2mu);
   FillNormalizedHistogram(HAbsMatrixTight2e2mu, HNormAbsMatrixTight2e2mu);
   FillNormalizedHistogram(HMatrixLoose4e, HNormMatrixLoose4e);
   FillNormalizedHistogram(HAbsMatrixLoose4e, HNormAbsMatrixLoose4e);
   FillNormalizedHistogram(HMatrixTight4e, HNormMatrixTight4e);
   FillNormalizedHistogram(HAbsMatrixTight4e, HNormAbsMatrixTight4e);

   PsFileHelper PsFile("MatrixResult.ps");
   PsFile.AddTextPage("Matrix!");

   PsFile.AddTextPage("VeryLoose, 2e2mu");
   PsFile.AddPlot(HMatrixVeryLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HMatrixVeryLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HMatrixVeryLoose2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormMatrixVeryLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormMatrixVeryLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormMatrixVeryLoose2e2mu, "colz text00", false, false);
   
   PsFile.AddTextPage("|VeryLoose|, 2e2mu");
   PsFile.AddPlot(HAbsMatrixVeryLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HAbsMatrixVeryLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HAbsMatrixVeryLoose2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormAbsMatrixVeryLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormAbsMatrixVeryLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormAbsMatrixVeryLoose2e2mu, "colz text00", false, false);

   PsFile.AddTextPage("Loose, 2e2mu");
   PsFile.AddPlot(HMatrixLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HMatrixLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HMatrixLoose2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormMatrixLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormMatrixLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormMatrixLoose2e2mu, "colz text00", false, false);
   
   PsFile.AddTextPage("|Loose|, 2e2mu");
   PsFile.AddPlot(HAbsMatrixLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HAbsMatrixLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HAbsMatrixLoose2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormAbsMatrixLoose2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormAbsMatrixLoose2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormAbsMatrixLoose2e2mu, "colz text00", false, false);
   
   PsFile.AddTextPage("Tight, 2e2mu");
   PsFile.AddPlot(HMatrixTight2e2mu, "colz", false, false);
   PsFile.AddPlot(HMatrixTight2e2mu, "colz", false, true);
   PsFile.AddPlot(HMatrixTight2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormMatrixTight2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormMatrixTight2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormMatrixTight2e2mu, "colz text00", false, false);
   
   PsFile.AddTextPage("|Tight|, 2e2mu");
   PsFile.AddPlot(HAbsMatrixTight2e2mu, "colz", false, false);
   PsFile.AddPlot(HAbsMatrixTight2e2mu, "colz", false, true);
   PsFile.AddPlot(HAbsMatrixTight2e2mu, "colz text00", false, false);
   PsFile.AddPlot(HNormAbsMatrixTight2e2mu, "colz", false, false);
   PsFile.AddPlot(HNormAbsMatrixTight2e2mu, "colz", false, true);
   PsFile.AddPlot(HNormAbsMatrixTight2e2mu, "colz text00", false, false);

   PsFile.AddTextPage("Loose, 4e");
   PsFile.AddPlot(HMatrixLoose4e, "colz", false, false);
   PsFile.AddPlot(HMatrixLoose4e, "colz", false, true);
   PsFile.AddPlot(HMatrixLoose4e, "colz text00", false, false);
   PsFile.AddPlot(HNormMatrixLoose4e, "colz", false, false);
   PsFile.AddPlot(HNormMatrixLoose4e, "colz", false, true);
   PsFile.AddPlot(HNormMatrixLoose4e, "colz text00", false, false);
   
   PsFile.AddTextPage("|Loose|, 4e");
   PsFile.AddPlot(HAbsMatrixLoose4e, "colz", false, false);
   PsFile.AddPlot(HAbsMatrixLoose4e, "colz", false, true);
   PsFile.AddPlot(HAbsMatrixLoose4e, "colz text00", false, false);
   PsFile.AddPlot(HNormAbsMatrixLoose4e, "colz", false, false);
   PsFile.AddPlot(HNormAbsMatrixLoose4e, "colz", false, true);
   PsFile.AddPlot(HNormAbsMatrixLoose4e, "colz text00", false, false);
   
   PsFile.AddTextPage("Tight, 4e");
   PsFile.AddPlot(HMatrixTight4e, "colz", false, false);
   PsFile.AddPlot(HMatrixTight4e, "colz", false, true);
   PsFile.AddPlot(HMatrixTight4e, "colz text00", false, false);
   PsFile.AddPlot(HNormMatrixTight4e, "colz", false, false);
   PsFile.AddPlot(HNormMatrixTight4e, "colz", false, true);
   PsFile.AddPlot(HNormMatrixTight4e, "colz text00", false, false);
   
   PsFile.AddTextPage("|Tight|, 4e");
   PsFile.AddPlot(HAbsMatrixTight4e, "colz", false, false);
   PsFile.AddPlot(HAbsMatrixTight4e, "colz", false, true);
   PsFile.AddPlot(HAbsMatrixTight4e, "colz text00", false, false);
   PsFile.AddPlot(HNormAbsMatrixTight4e, "colz", false, false);
   PsFile.AddPlot(HNormAbsMatrixTight4e, "colz", false, true);
   PsFile.AddPlot(HNormAbsMatrixTight4e, "colz text00", false, false);

   PsFile.AddTimeStampPage();
   PsFile.Close();
   */

   OutputFile.cd();

   HEntryCount.Write();
   HMatrixVeryLoose2e2mu.Write();
   HAbsMatrixVeryLoose2e2mu.Write();
   HMatrixLoose2e2mu.Write();
   HAbsMatrixLoose2e2mu.Write();
   HMatrixTight2e2mu.Write();
   HMatrixTight2e2muReal.Write();
   HAbsMatrixTight2e2mu.Write();
   HAbsMatrixTight2e2muReal.Write();
   HMatrixLoose4e.Write();
   HAbsMatrixLoose4e.Write();
   HMatrixTight4e.Write();
   HAbsMatrixTight4e.Write();

   OutputFile.Close();

   return 0;
}

