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
#include "Code/DrawRandom.h"

#include "FTHelper.h"

int main(int argc, char *argv[]);
void AddColorPlot(PdfFileHelper &PdfFile, double **Data, int N, string Title);
void AddColorPlotSizePhase(PdfFileHelper &PdfFile, double **Real, double **Imag, int N, string Title);
void AddShape(PdfFileHelper &PdfFile, double EtaSlope, double Phi0, double C0, double C1, double C2,
   int N, double CellSize, int Truncation);
void AddJet(PdfFileHelper &PdfFile, double X, double Y, int Count, double Sigma, double K,
   int N, double CellSize, int Truncation);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string OutputFileName         = CL.Get("Output");
   int N                         = CL.GetInt("N", 89);
   int Truncation                = CL.GetInt("Truncation", 10);
   double CellSize               = CL.GetDouble("Size", 0.017);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Fourier catalog");

   AddShape(PdfFile,  0.0,  0.0,  1.0,  0.0,  0.0, N, CellSize, Truncation);
   AddShape(PdfFile,  0.1,  0.0,  1.0,  0.0,  0.0, N, CellSize, Truncation);
   AddShape(PdfFile,  0.2,  0.0,  0.0,  0.0,  0.0, N, CellSize, Truncation);
   AddShape(PdfFile, -0.2,  0.0,  0.0,  0.0,  0.0, N, CellSize, Truncation);
   AddShape(PdfFile,  0.0,  0.0,  0.0,  0.2,  0.2, N, CellSize, Truncation);
   AddShape(PdfFile,  0.0,  0.0,  0.0,  0.2,  0.0, N, CellSize, Truncation);
   AddShape(PdfFile,  0.0,  0.0,  0.0,  0.0,  0.2, N, CellSize, Truncation);
   AddShape(PdfFile,  0.0,  0.5,  0.0,  0.0,  0.2, N, CellSize, Truncation);

   AddJet(PdfFile, 0.0, 0.0, 20, 0.15, 4.5, N, CellSize, Truncation);
   AddJet(PdfFile, 0.1, 0.1, 20, 0.15, 4.5, N, CellSize, Truncation);
   AddJet(PdfFile, 0.0, 0.0, 10, 0.15, 4.5, N, CellSize, Truncation);
   AddJet(PdfFile, 0.0, 0.0, 30, 0.15, 4.5, N, CellSize, Truncation);
   AddJet(PdfFile, 0.0, 0.0, 20, 0.25, 4.5, N, CellSize, Truncation);

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

void AddColorPlotSizePhase(PdfFileHelper &PdfFile, double **Real, double **Imag, int N, string Title)
{
   TH2D H1("H1", Title.c_str(), N, 0, N, N, 0, N);
   TH2D H2("H2", Title.c_str(), N, 0, N, N, 0, N);
   H1.SetStats(0);
   H2.SetStats(0);
   
   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < N; j++)
      {
         H1.SetBinContent(i + 1, j + 1, GetSize(Real[i][j], Imag[i][j]));
         H2.SetBinContent(i + 1, j + 1, GetPhase(Real[i][j], Imag[i][j]));
      }
   }
   
   H1.SetTitle(Form("%s (size)", H1.GetTitle()));
   H2.SetTitle(Form("%s (phase)", H2.GetTitle()));

   PdfFile.AddPlot(H1, "colz");
   PdfFile.AddPlot(H2, "colz");
}

void AddShape(PdfFileHelper &PdfFile, double EtaSlope, double Phi0, double C0, double C1, double C2,
   int N, double CellSize, int Truncation)
{
   JetImage Image(N);

   for(int i = 0; i < N; i++)
   {
      double Eta = (i - N * 0.5) * CellSize;

      for(int j = 0; j < N; j++)
      {
         double Phi = (j - N * 0.5) * CellSize;

         Image.Data[i][j] = C0 + C1 * cos(Phi - Phi0) + C2 * cos(2 * (Phi - Phi0)) + EtaSlope * Eta;
      }
   }

   JetMode Mode = Transform(Image, -1000, 1000, -1000, 1000);
   JetMode Truncated = Transform(Image, -Truncation, Truncation, -Truncation, Truncation);
   JetImage TruncatedImage = Transform(Truncated);

   for(int i = -1; i <= 1; i++)
   {
      for(int j = -1; j <= 1; j++)
      {
         Truncated.Real[(i+N)%N][(j+N)%N] = 0;
         Truncated.Imag[(i+N)%N][(j+N)%N] = 0;
      }
   }
   
   JetImage DoublyTruncatedImage = Transform(Truncated);

   for(int i = -1; i <= 1; i++)
   {
      for(int j = 0; j < N; j++)
      {
         Truncated.Real[(i+N)%N][(j+N)%N] = 0;
         Truncated.Imag[(i+N)%N][(j+N)%N] = 0;
         Truncated.Real[(j+N)%N][(i+N)%N] = 0;
         Truncated.Imag[(j+N)%N][(i+N)%N] = 0;
      }
   }
   
   JetImage AggressivelyTruncatedImage = Transform(Truncated);
 
   vector<string> Explanation(20);
   Explanation[0] = "Input background shape with:";
   Explanation[1] = Form("   EtaSlope = %.2f", EtaSlope);
   Explanation[2] = Form("   (C0, C1, C2) = (%.2f, %.2f, %.2f)", C0, C1, C2);
   Explanation[3] = Form("   Phi0 = %.2f", Phi0);
   Explanation[4] = Form("   Cell size = %.4f", CellSize);
   Explanation[5] = Form("   N = %d", N);
   Explanation[6] = Form("   Map size = %.2f", N * CellSize);
   Explanation[7] = Form("   Truncate at #pm%d", Truncation);
   Explanation[8] = "";
   Explanation[9] = "Background in each cell =";
   Explanation[10] = " slope * eta + C0 + C1 cos(phi - phi0) + C2 cos(2(phi - phi0))";
   Explanation[11] = "";
   PdfFile.AddTextPage(Explanation);

   AddColorPlot(PdfFile, Image.Data, N, "Input distribution");
   AddColorPlot(PdfFile, Mode.Real, N, "Real modes");
   AddColorPlot(PdfFile, Mode.Imag, N, "Imaginary modes");
   AddColorPlotSizePhase(PdfFile, Mode.Real, Mode.Imag, N, "Fourier modes");
   AddColorPlot(PdfFile, TruncatedImage.Data, N, "Truncated image");
   AddColorPlot(PdfFile, DoublyTruncatedImage.Data, N, "Doubly-truncated image");
   AddColorPlot(PdfFile, AggressivelyTruncatedImage.Data, N, "Aggressively-truncated image");
}

void AddJet(PdfFileHelper &PdfFile, double X, double Y, int Count, double Sigma, double K,
   int N, double CellSize, int Truncation)
{
   JetImage Image(N);

   for(int i = 0; i < Count; i++)
   {
      double Eta = DrawGaussian(X, Sigma);
      double Phi = DrawGaussian(Y, Sigma);
      double PT = exp(log(1 - DrawRandom(0, 1)) / (1 - K));

      int EtaBin = (int)(Eta / CellSize + N * 0.5);
      int PhiBin = (int)(Phi / CellSize + N * 0.5);

      if(EtaBin < 0 || EtaBin >= N)
         continue;
      if(PhiBin < 0 || PhiBin >= N)
         continue;

      Image.Data[EtaBin][PhiBin] += PT;
   }

   JetMode Mode = Transform(Image, -1000, 1000, -1000, 1000);
   JetMode Truncated = Transform(Image, -Truncation, Truncation, -Truncation, Truncation);
   JetImage TruncatedImage = Transform(Truncated);

   for(int i = -1; i <= 1; i++)
   {
      for(int j = -1; j <= 1; j++)
      {
         Truncated.Real[(i+N)%N][(j+N)%N] = 0;
         Truncated.Imag[(i+N)%N][(j+N)%N] = 0;
      }
   }
   
   JetImage DoublyTruncatedImage = Transform(Truncated);

   for(int i = -1; i <= 1; i++)
   {
      for(int j = 0; j < N; j++)
      {
         Truncated.Real[(i+N)%N][(j+N)%N] = 0;
         Truncated.Imag[(i+N)%N][(j+N)%N] = 0;
         Truncated.Real[(j+N)%N][(i+N)%N] = 0;
         Truncated.Imag[(j+N)%N][(i+N)%N] = 0;
      }
   }
   
   JetImage AggressivelyTruncatedImage = Transform(Truncated);
 
   vector<string> Explanation(20);
   Explanation[0] = "Input jet with:";
   Explanation[1] = Form("   (eta, phi) = (%.2f, %.2f)", X, Y);
   Explanation[2] = Form("   spread = %.2f", Sigma);
   Explanation[3] = Form("   power law = x^-%.2f", K);
   Explanation[4] = Form("   Cell size = %.4f", CellSize);
   Explanation[5] = Form("   N = %d", N);
   Explanation[6] = Form("   Map size = %.2f", N * CellSize);
   Explanation[7] = Form("   Truncate at #pm%d", Truncation);
   Explanation[8] = "";
   Explanation[9] = "";
   Explanation[10] = "";
   Explanation[11] = "";
   PdfFile.AddTextPage(Explanation);

   AddColorPlot(PdfFile, Image.Data, N, "Pseudo-jet");
   AddColorPlot(PdfFile, Mode.Real, N, "Real modes");
   AddColorPlot(PdfFile, Mode.Imag, N, "Imaginary modes");
   AddColorPlotSizePhase(PdfFile, Mode.Real, Mode.Imag, N, "Fourier modes");
   AddColorPlot(PdfFile, TruncatedImage.Data, N, "Truncated image");
   AddColorPlot(PdfFile, DoublyTruncatedImage.Data, N, "Doubly-truncated image");
   AddColorPlot(PdfFile, AggressivelyTruncatedImage.Data, N, "Aggressively-truncated image");
}







