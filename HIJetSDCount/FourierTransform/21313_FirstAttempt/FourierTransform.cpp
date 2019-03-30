#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TCanvas.h"

#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#define SIZE 89

int main(int argc, char *argv[]);
pair<double, double> GetCoefficient(double Image[SIZE][SIZE], int KX, int KY);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool DoIndividual             = CL.GetBool("DoIndividual", false);
   double Percentage             = CL.GetDouble("Percentage", 1.00);
   double MinS                   = CL.GetDouble("MinS", 25);
   double CellSize               = CL.GetDouble("CellSize", 0.087);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Fourier transform first try");

   TProfile2D HSR("HSR", "Signal, real;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   TProfile2D HSI("HSI", "Signal, imag;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   TProfile2D HSS("HSS", "Signal;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   TProfile2D HBR("HBR", "Background, real;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   TProfile2D HBI("HBI", "Background, imag;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   TProfile2D HBS("HBS", "Background;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);

   HSR.SetStats(0);
   HSI.SetStats(0);
   HSS.SetStats(0);
   HBR.SetStats(0);
   HBI.SetStats(0);
   HBS.SetStats(0);

   for(string FileName : InputFileNames)
   {
      TFile InputFile(FileName.c_str());
                                           
      TTree *Tree = (TTree *)InputFile.Get("DiscretizedJetTree");
      if(Tree == nullptr)
         continue;

      float I[SIZE][SIZE][7];
      Tree->SetBranchAddress("Images", &I);

      int EntryCount = Tree->GetEntries() * Percentage;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);
      
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 300 || iE % (EntryCount / 200) == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         double S[SIZE][SIZE] = {{0}};
         double B[SIZE][SIZE] = {{0}};

         double STotal = 0;
         double BTotal = 0;

         TH2D HSJet("HSJet", "Signal image;X;Y", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HBJet("HBJet", "Background image;X;Y", SIZE, 0, SIZE, SIZE, 0, SIZE);

         HSJet.SetStats(0);
         HBJet.SetStats(0);
         
         for(int iX = 0; iX < SIZE; iX++)
         {
            for(int iY = 0; iY < SIZE; iY++)
            {
               S[iX][iY] = I[iX][iY][1] + I[iX][iY][2];
               B[iX][iY] = I[iX][iY][4] + I[iX][iY][5];

               HSJet.Fill(iX, iY, S[iX][iY]);
               HBJet.Fill(iX, iY, B[iX][iY]);

               STotal = STotal + S[iX][iY];
               BTotal = BTotal + B[iX][iY];
            }
         }

         if(STotal < MinS)
            continue;
   
         TH2D HSRJet("HSRJet", "Signal, real;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HSIJet("HSIJet", "Signal, imag;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HSSJet("HSSJet", "Signal;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HBRJet("HBRJet", "Background, real;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HBIJet("HBIJet", "Background, imag;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
         TH2D HBSJet("HBSJet", "Background;KX;KY", SIZE, 0, SIZE, SIZE, 0, SIZE);
   
         HSRJet.SetStats(0);
         HSIJet.SetStats(0);
         HSSJet.SetStats(0);
         HBRJet.SetStats(0);
         HBIJet.SetStats(0);
         HBSJet.SetStats(0);

         for(int KX = 0; KX < SIZE; KX++)
         {
            for(int KY = 0; KY < SIZE; KY++)
            {
               if(KX == 0 && KY == 0)
                  continue;

               pair<double, double> CS = GetCoefficient(S, KX, KY);
               pair<double, double> CB = GetCoefficient(B, KX, KY);

               HSR.Fill(KX, KY, CS.first);
               HSI.Fill(KX, KY, CS.second);
               HSS.Fill(KX, KY, sqrt(CS.first * CS.first + CS.second * CS.second));
               HBR.Fill(KX, KY, CB.first);
               HBI.Fill(KX, KY, CB.second);
               HBS.Fill(KX, KY, sqrt(CB.first * CB.first + CB.second * CB.second));
               
               HSRJet.Fill(KX, KY, CS.first / STotal);
               HSIJet.Fill(KX, KY, CS.second / STotal);
               HSSJet.Fill(KX, KY, sqrt(CS.first * CS.first + CS.second * CS.second) / STotal);
               HBRJet.Fill(KX, KY, CB.first / BTotal);
               HBIJet.Fill(KX, KY, CB.second / BTotal);
               HBSJet.Fill(KX, KY, sqrt(CB.first * CB.first + CB.second * CB.second) / BTotal);
            }
         }
   
         if(DoIndividual == true)
         {
            vector<string> Explanation(10);
            Explanation[0] = Form("Total S = %f GeV", STotal); 
            Explanation[1] = Form("Total B = %f GeV", BTotal);

            PdfFile.AddTextPage("Jet");
            PdfFile.AddPlot(HSJet, "colz");
            PdfFile.AddPlot(HBJet, "colz");
            PdfFile.AddTextPage(Explanation);
            PdfFile.AddPlot(HSRJet, "colz");
            PdfFile.AddPlot(HSIJet, "colz");
            PdfFile.AddPlot(HSSJet, "colz");
            PdfFile.AddPlot(HBRJet, "colz");
            PdfFile.AddPlot(HBIJet, "colz");
            PdfFile.AddPlot(HBSJet, "colz");
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   PdfFile.AddTextPage("Average");
   PdfFile.AddPlot(HSR, "colz");
   PdfFile.AddPlot(HSI, "colz");
   PdfFile.AddPlot(HSS, "colz");
   PdfFile.AddPlot(HBR, "colz");
   PdfFile.AddPlot(HBI, "colz");
   PdfFile.AddPlot(HBS, "colz");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

pair<double, double> GetCoefficient(double Image[SIZE][SIZE], int KX, int KY)
{
   double FR = 0, FI = 0;

   static bool Initialized = false;
   static double Cos[SIZE] = {0};
   static double Sin[SIZE] = {0};

   if(Initialized == false)
   {
      for(int i = 0; i < SIZE; i++)
      {
         Cos[i] = cos(2 * M_PI / SIZE * i);
         Sin[i] = sin(2 * M_PI / SIZE * i);
      }
      Initialized = true;
   }

   for(int iX = 0; iX < SIZE; iX++)
   {
      for(int iY = 0; iY < SIZE; iY++)
      {
         int K = (KX * iX + KY * iY) % SIZE;

         FR = FR + Image[iX][iY] * Cos[K];
         FI = FI - Image[iX][iY] * Sin[K];
      }
   }

   return pair<double, double>(FR, FI);
}




