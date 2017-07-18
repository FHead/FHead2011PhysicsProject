#include "JetEnergyScale.h"

JetEnergyScale::JetEnergyScale()
{
   for(int i = 0; i < 30; i++)
      P[i] = new TProfile(Form("JES_P%d", i), Form("JES for bin %d", i), 150, 80, 500);
   
   for(int i = 0; i < 30; i++)
      H[i] = new TH2D(Form("JES_H%d", i), Form("JES for bin %d", i), 150, 80, 500, 100, 0.5, 1.5);

   for(int i = 0; i < 30; i++)
      for(int j = 0; j < 7; j++)
         A[i][j] = 0;
}

JetEnergyScale::~JetEnergyScale()
{
   // for(int i = 0; i < 30; i++)
   //    if(P[i] != NULL)
   //       delete P[i];
   // 
   // for(int i = 0; i < 30; i++)
   //    if(H[i] != NULL)
   //       delete H[i];
}

void JetEnergyScale::Fill(double JetPT, double RawJetPT, double Eta, double Weight)
{
   int Bin = FindBin(Eta);
   double Distance = DistanceToBoundary(Eta);

   if(Bin < 0 || Bin >= 30)   // out of bound!
      return;
   if(Distance < 0.0001)   // too close to boundary, don't use
      return;

   H[Bin]->Fill(RawJetPT, JetPT / RawJetPT, Weight);
   P[Bin]->Fill(RawJetPT, JetPT / RawJetPT, Weight);
}

int JetEnergyScale::FindBin(double Eta)
{
   double BinSize = 0.087;
   return floor(Eta / BinSize) + 15;
}

double JetEnergyScale::DistanceToBoundary(double Eta)
{
   double BinSize = 0.087;
   
   double Left = floor(Eta / BinSize) * BinSize;
   double Right = Left + BinSize;

   return min(Eta - Left, Right - Eta);
}
   
void JetEnergyScale::DoFit()
{
   PdfFileHelper PdfFile("JESCheck.pdf");
   PdfFile.AddTextPage("JES scales and fits");

   for(int i = 0; i < 30; i++)
   {
      TF1 Fit("Fit", "pol4+expo(5)");
      for(int j = 0; j < 10; j++)
         P[i]->Fit(&Fit);

      for(int j = 0; j < 7; j++)
         A[i][j] = Fit.GetParameter(j);

      P[i]->SetMinimum(0.5);
      P[i]->SetMaximum(1.5);

      PdfFile.AddPlot(H[i], "colz");

      TCanvas Canvas;

      P[i]->Draw();

      double ExampleEta = (i - 15 + 0.5) * 0.087;

      TGraph G;
      G.SetPoint(0, 100, Apply(100, ExampleEta) / 100);
      G.SetPoint(1, 150, Apply(150, ExampleEta) / 150);
      G.SetPoint(2, 200, Apply(200, ExampleEta) / 200);
      G.SetPoint(3, 250, Apply(250, ExampleEta) / 250);
      G.SetPoint(4, 300, Apply(300, ExampleEta) / 300);
      G.SetMarkerStyle(20);
      G.SetMarkerSize(2);
      G.SetMarkerColor(kMagenta);
      G.Draw("p");

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}
   
double JetEnergyScale::Apply(double RawJetPT, double Eta)
{
   int Bin = FindBin(Eta);
   if(Bin < 0 || Bin >= 30)
      return 0;

   if(RawJetPT < 100)
      return 0;

   double Answer = (((A[Bin][4] * RawJetPT + A[Bin][3]) * RawJetPT + A[Bin][2]) * RawJetPT + A[Bin][1]) * RawJetPT + A[Bin][0];
   Answer = Answer + exp(A[Bin][5] + A[Bin][6] * RawJetPT);

   return Answer * RawJetPT;
}



