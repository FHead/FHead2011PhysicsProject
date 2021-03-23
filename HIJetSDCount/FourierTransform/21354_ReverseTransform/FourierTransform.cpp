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

#include "FTHelper.h"

int main(int argc, char *argv[]);
void AddColorPlot(PdfFileHelper &PdfFile, double **Data, int N, string Title);

int main(int argc, char *argv[])
{
   int N = 89;

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

   TProfile2D HSR("HSR", "Signal, real;KX;KY", N, 0, N, N, 0, N);
   TProfile2D HSI("HSI", "Signal, imag;KX;KY", N, 0, N, N, 0, N);
   TProfile2D HSS("HSS", "Signal;KX;KY", N, 0, N, N, 0, N);
   TProfile2D HBR("HBR", "Background, real;KX;KY", N, 0, N, N, 0, N);
   TProfile2D HBI("HBI", "Background, imag;KX;KY", N, 0, N, N, 0, N);
   TProfile2D HBS("HBS", "Background;KX;KY", N, 0, N, N, 0, N);

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

      float I[N][N][7];
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

         JetImage S(N), B(N);

         double STotal = 0;
         double BTotal = 0;

         for(int iX = 0; iX < N; iX++)
         {
            for(int iY = 0; iY < N; iY++)
            {
               S.Data[iX][iY] = I[iX][iY][1] + I[iX][iY][2];
               B.Data[iX][iY] = I[iX][iY][4] + I[iX][iY][5];

               STotal = STotal + S.Data[iX][iY];
               BTotal = BTotal + B.Data[iX][iY];
            }
         }

         if(STotal < MinS)
            continue;
   
         TH2D HSSJet("HSSJet", "Signal;KX;KY", N, 0, N, N, 0, N);
         TH2D HBSJet("HBSJet", "Background;KX;KY", N, 0, N, N, 0, N);
   
         HSSJet.SetStats(0);
         HBSJet.SetStats(0);

         JetMode KS = Transform(S, -10, 10, -10, 10);
         JetMode KB = Transform(B, -10, 10, -10, 10);

         JetImage TS = Transform(KS);
         JetImage TB = Transform(KB);

         JetMode TKS = Transform(S, -10, 10, -10, 10);
         JetMode TKB = Transform(B, -10, 10, -10, 10);

         for(int i = -1; i <= 1; i++)
         {
            for(int j = 0; j < N; j++)
            {
               TKS.Real[(i+N)%N][j] = 0;
               TKS.Imag[(i+N)%N][j] = 0;
               TKB.Real[(i+N)%N][j] = 0;
               TKB.Imag[(i+N)%N][j] = 0;
               TKS.Real[j][(i+N)%N] = 0;
               TKS.Imag[j][(i+N)%N] = 0;
               TKB.Real[j][(i+N)%N] = 0;
               TKB.Imag[j][(i+N)%N] = 0;
            }
         }

         JetImage TTS = Transform(TKS);
         JetImage TTB = Transform(TKB);

         for(int KX = 0; KX < N; KX++)
         {
            for(int KY = 0; KY < N; KY++)
            {
               if(KX == 0 && KY == 0)
                  continue;

               HSR.Fill(KX, KY, KS.Real[KX][KY]);
               HSI.Fill(KX, KY, KS.Imag[KX][KY]);
               HSS.Fill(KX, KY, sqrt(KS.Real[KX][KY] * KS.Real[KX][KY] + KS.Imag[KX][KY] * KS.Imag[KX][KY]));
               HBR.Fill(KX, KY, KB.Real[KX][KY]);
               HBI.Fill(KX, KY, KB.Imag[KX][KY]);
               HBS.Fill(KX, KY, sqrt(KB.Real[KX][KY] * KB.Real[KX][KY] + KB.Imag[KX][KY] * KB.Imag[KX][KY]));
               
               HSSJet.Fill(KX, KY, sqrt(KS.Real[KX][KY] * KS.Real[KX][KY] + KS.Imag[KX][KY] * KS.Imag[KX][KY]) / STotal);
               HBSJet.Fill(KX, KY, sqrt(KB.Real[KX][KY] * KB.Real[KX][KY] + KB.Imag[KX][KY] * KB.Imag[KX][KY]) / BTotal);
            }
         }
   
         if(DoIndividual == true)
         {
            vector<string> Explanation(10);
            Explanation[0] = Form("Total S = %f GeV", STotal); 
            Explanation[1] = Form("Total B = %f GeV", BTotal);

            PdfFile.AddTextPage("Jet");
            AddColorPlot(PdfFile, S.Data, N, "Signal image");
            AddColorPlot(PdfFile, B.Data, N, "Background image");
            PdfFile.AddTextPage(Explanation);
            AddColorPlot(PdfFile, KS.Real, N, "Signal, real");
            AddColorPlot(PdfFile, KS.Imag, N, "Signal, imag");
            PdfFile.AddPlot(HSSJet, "colz");
            AddColorPlot(PdfFile, KB.Real, N, "Background, real");
            AddColorPlot(PdfFile, KB.Imag, N, "Background, imag");
            PdfFile.AddPlot(HBSJet, "colz");
            PdfFile.AddTextPage("Truncated");
            AddColorPlot(PdfFile, TS.Data, N, "Truncated signal image");
            AddColorPlot(PdfFile, TB.Data, N, "Truncated background image");
            PdfFile.AddTextPage("Aggressively truncated");
            AddColorPlot(PdfFile, TTS.Data, N, "Truncated signal image");
            AddColorPlot(PdfFile, TTB.Data, N, "Truncated background image");
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

void AddColorPlot(PdfFileHelper &PdfFile, double **Data, int N, string Title)
{
   TH2D H("H", Title.c_str(), N, 0, N, N, 0, N);
   H.SetStats(0);
   
   for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
         H.SetBinContent(i + 1, j + 1, Data[i][j]);
   
   PdfFile.AddPlot(H, "colz");
}








