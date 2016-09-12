#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TF1.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void ExportHistogram1D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2D(TFile &File, string HistogramName, string OutputName);
void ExportProfile2D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2DWithProfile(TFile &File, string HistogramName, string ProfileName, string OutputName);
void ExportHistogram2DWithProfileFit(TFile &File, string HistogramName, string ProfileName, string OutputName);
void NormalizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   char *InputFile = argv[1];
   string OutputBase = argv[2];

   TFile File(InputFile);

   string Type1[3] = {"Gen", "Gen", "Reco"};
   string Type2[3] = {"Reco", "SD", "SD"};

   for(int iType = 0; iType < 3; iType++)
   {
      string Name = "", Name2 = "", NameOutput = "";
      
      Name = "P" + Type2[iType] + "MassOver" + Type1[iType] + "MassPT";
      if((TProfile *)File.Get(Name.c_str()))
         ((TProfile *)File.Get(Name.c_str()))->SetErrorOption("S");
      Name = "P" + Type2[iType] + "MassMinus" + Type1[iType] + "MassPT";
      if((TProfile *)File.Get(Name.c_str()))
         ((TProfile *)File.Get(Name.c_str()))->SetErrorOption("S");

      Name = "H" + Type1[iType] + "Mass" + Type2[iType] + "Mass";
      NameOutput = OutputBase + "_H" + Type1[iType] + "Mass" + Type2[iType] + "Mass";
      ExportHistogram2D(File, Name, NameOutput);
      
      Name = "P" + Type2[iType] + "MassOver" + Type1[iType] + "MassPTCentrality";
      NameOutput = OutputBase + "_" + Type2[iType] + "MassOver" + Type2[iType] + "MassCentrality";
      ExportProfile2D(File, Name, NameOutput);

      Name = "H" + Type2[iType] + "MassOver" + Type1[iType] + "MassPT";
      Name2 = "P" + Type2[iType] + "MassOver" + Type1[iType] + "MassPT";
      NameOutput = OutputBase + "_" + Type2[iType] + "MassOver" + Type2[iType] + "GenMassPT";
      ExportHistogram2DWithProfile(File, Name, Name2, NameOutput);

      Name = "P" + Type2[iType] + "MassMinus" + Type1[iType] + "MassPTCentrality";
      NameOutput = OutputBase + "_" + Type2[iType] + "MassMinus" + Type2[iType] + "MassCentrality";
      ExportProfile2D(File, Name, NameOutput);
      
      Name = "H" + Type2[iType] + "MassMinus" + Type1[iType] + "MassPT";
      Name2 = "P" + Type2[iType] + "MassMinus" + Type1[iType] + "MassPT";
      NameOutput = OutputBase + "_" + Type2[iType] + "MassMinus" + Type2[iType] + "GenMassPT";
      ExportHistogram2DWithProfile(File, Name, Name2, NameOutput);
   }

   File.Close();

   return 0;
}

void ExportHistogram1D(TFile &File, string HistogramName, string OutputName)
{
   TH1D *H = (TH1D *)File.Get(HistogramName.c_str());

   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw();

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2D(TFile &File, string HistogramName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());

   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw("colz");

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportProfile2D(TFile &File, string HistogramName, string OutputName)
{
   TProfile2D *H = (TProfile2D *)File.Get(HistogramName.c_str());

   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw("colz");

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2DWithProfile(TFile &File, string HistogramName, string ProfileName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());
   TProfile *P = (TProfile *)File.Get(ProfileName.c_str());

   if(H == NULL || P == NULL)
      return;

   TCanvas C;

   P->Rebin(2);
   P->SetMarkerStyle(8);
   P->SetMarkerColor(kRed);
   P->SetLineWidth(2);
   P->SetLineColor(kRed);

   H->SetStats(0);
   H->Draw("colz");
   P->Draw("same");

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2DWithProfileFit(TFile &File, string HistogramName, string ProfileName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());
   TProfile *P = (TProfile *)File.Get(ProfileName.c_str());

   if(H == NULL || P == NULL)
      return;

   TCanvas C;

   P->Rebin(2);
   P->SetMarkerStyle(8);
   P->SetMarkerColor(kRed);
   P->SetLineWidth(2);
   P->SetLineColor(kRed);

   TF1 F("F", "[0]*log(x)+[1]");
   P->Fit(&F);

   H->SetStats(0);
   H->Draw("colz");
   P->Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(P, "Fit: a ln(p_{T}^{jet}) + b", "l");
   Legend.AddEntry("", Form("a = %4.2f #pm %4.2f", F.GetParameter(0), F.GetParError(0)), "");
   Legend.AddEntry("", Form("b = %4.2f #pm %4.2f", F.GetParameter(1), F.GetParError(1)), "");
   Legend.Draw();

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void NormalizeHistogram(TH1D &H)
{
   int N = H.GetNbinsX();
   double L = H.GetXaxis()->GetBinLowEdge(1);
   double R = H.GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;

   H.Scale(1 / H.Integral() / BinSize);
}






