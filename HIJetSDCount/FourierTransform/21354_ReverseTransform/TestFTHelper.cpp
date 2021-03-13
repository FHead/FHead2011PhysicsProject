#include <iostream>
#include <cstdlib>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "PlotHelper4.h"
#include "SetStyle.h"

#include "FTHelper.h"

int main(int argc, char *argv[]);
void AddColorPlot(PdfFileHelper &PdfFile, double **Data, int N, string Title);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   PdfFileHelper PdfFile("TestRun.pdf");
   PdfFile.AddTextPage("Fourier transform validation");

   int N = 10;

   JetImage Source(N);
   for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
         Source.Data[i][j] = rand() % 100 + 1;

   JetMode Mode = Transform(Source, -1000, 1000, -1000, 1000);

   JetImage Result = Transform(Mode);
   
   AddColorPlot(PdfFile, Source.Data, N, "Source image");
   AddColorPlot(PdfFile, Result.Data, N, "Transformed back");
   AddColorPlot(PdfFile, Mode.Real, N, "Real");
   AddColorPlot(PdfFile, Mode.Imag, N, "Imag");

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
   
   PdfFile.AddPlot(H, "colz text00");
}




