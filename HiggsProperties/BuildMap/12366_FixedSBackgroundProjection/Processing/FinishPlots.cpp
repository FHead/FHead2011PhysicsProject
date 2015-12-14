#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"

int main();
void ExportPlots(TFile &F, string Name1, string Name2, string NameBase, string XAxis, bool LogY);
void LegoPlot(TFile &F, string Name, string NameBase, string XAxis, string YAxis);

int main()
{
   TFile FileB("OutputFileAllBackground.root");
   
   ExportPlots(FileB, "HToyM1", "HMCM1", "BackgroundM1Projection", "M_{1}", false);
   ExportPlots(FileB, "HToyM2", "HMCM2", "BackgroundM2Projection", "M_{2}", false);
   ExportPlots(FileB, "HToyPhi0", "HMCPhi0", "BackgroundPhi0Projection", "#Phi_{1}", false);
   ExportPlots(FileB, "HToyTheta0", "HMCTheta0", "BackgroundTheta0Projection", "cos #Theta", false);
   ExportPlots(FileB, "HToyPhi", "HMCPhi", "BackgroundPhiProjection", "#Phi", false);
   ExportPlots(FileB, "HToyTheta1", "HMCTheta1", "BackgroundTheta1Projection", "cos #theta_{1}", false);
   ExportPlots(FileB, "HToyTheta2", "HMCTheta2", "BackgroundTheta2Projection", "cos #theta_{2}", false);

   LegoPlot(FileB, "HToyM1M2", "BackgroundM1M2Projection", "M_{1}", "M_{2}");
   LegoPlot(FileB, "HToyM1Phi0", "BackgroundM1Phi0Projection", "M_{1}", "#Phi_{1}");
   LegoPlot(FileB, "HToyM1Theta0", "BackgroundM1Theta0Projection", "M_{1}", "cos #Theta");
   LegoPlot(FileB, "HToyM1Phi", "BackgroundM1PhiProjection", "M_{1}", "#Phi");
   LegoPlot(FileB, "HToyM1Theta1", "BackgroundM1Theta1Projection", "M_{1}", "cos #theta_{1}");
   LegoPlot(FileB, "HToyM1Theta2", "BackgroundM1Theta2Projection", "M_{1}", "cos #theta_{2}");
   LegoPlot(FileB, "HToyM2Phi0", "BackgroundM2Phi0Projection", "M_{2}", "#Phi_{1}");
   LegoPlot(FileB, "HToyM2Theta0", "BackgroundM2Theta0Projection", "M_{2}", "cos #Theta");
   LegoPlot(FileB, "HToyM2Phi", "BackgroundM2PhiProjection", "M_{2}", "#Phi");
   LegoPlot(FileB, "HToyM2Theta1", "BackgroundM2Theta1Projection", "M_{2}", "cos #theta_{1}");
   LegoPlot(FileB, "HToyM2Theta2", "BackgroundM2Theta2Projection", "M_{2}", "cos #theta_{2}");
   LegoPlot(FileB, "HToyPhi0Theta0", "BackgroundPhi0Theta0Projection", "#Phi_{1}", "cos #Theta");
   LegoPlot(FileB, "HToyPhi0Phi", "BackgroundPhi0PhiProjection", "#Phi_{1}", "#Phi");
   LegoPlot(FileB, "HToyPhi0Theta1", "BackgroundPhi0Theta1Projection", "#Phi_{1}", "cos #theta_{1}");
   LegoPlot(FileB, "HToyPhi0Theta2", "BackgroundPhi0Theta2Projection", "#Phi_{1}", "cos #theta_{2}");
   LegoPlot(FileB, "HToyTheta0Phi", "BackgroundTheta0PhiProjection", "cos #Theta", "#Phi");
   LegoPlot(FileB, "HToyTheta0Theta1", "BackgroundTheta0Theta1Projection", "cos #Theta", "cos #theta_{1}");
   LegoPlot(FileB, "HToyTheta0Theta2", "BackgroundTheta0Theta2Projection", "cos #Theta", "cos #theta_{2}");
   LegoPlot(FileB, "HToyPhiTheta1", "BackgroundPhiTheta1Projection", "#Phi", "cos #theta_{1}");
   LegoPlot(FileB, "HToyPhiTheta2", "BackgroundPhiTheta2Projection", "#Phi", "cos #theta_{2}");
   LegoPlot(FileB, "HToyTheta1Theta2", "BackgroundTheta1Theta2Projection", "cos #theta_{1}", "cos #theta_{2}");

   FileB.Close();

   TFile FileS("OutputFileAllSignal.root");

   ExportPlots(FileS, "HToyM1", "HMCM1", "SignalM1Projection", "M_{1}", false);
   ExportPlots(FileS, "HToyM2", "HMCM2", "SignalM2Projection", "M_{2}", false);
   ExportPlots(FileS, "HToyPhi0", "HMCPhi0", "SignalPhi0Projection", "#Phi_{1}", false);
   ExportPlots(FileS, "HToyTheta0", "HMCTheta0", "SignalTheta0Projection", "cos #Theta", false);
   ExportPlots(FileS, "HToyPhi", "HMCPhi", "SignalPhiProjection", "#Phi", false);
   ExportPlots(FileS, "HToyTheta1", "HMCTheta1", "SignalTheta1Projection", "cos #theta_{1}", false);
   ExportPlots(FileS, "HToyTheta2", "HMCTheta2", "SignalTheta2Projection", "cos #theta_{2}", false);

   LegoPlot(FileS, "HToyM1M2", "SignalM1M2Projection", "M_{1}", "M_{2}");
   LegoPlot(FileS, "HToyM1Phi0", "SignalM1Phi0Projection", "M_{1}", "#Phi_{1}");
   LegoPlot(FileS, "HToyM1Theta0", "SignalM1Theta0Projection", "M_{1}", "cos #Theta");
   LegoPlot(FileS, "HToyM1Phi", "SignalM1PhiProjection", "M_{1}", "#Phi");
   LegoPlot(FileS, "HToyM1Theta1", "SignalM1Theta1Projection", "M_{1}", "cos #theta_{1}");
   LegoPlot(FileS, "HToyM1Theta2", "SignalM1Theta2Projection", "M_{1}", "cos #theta_{2}");
   LegoPlot(FileS, "HToyM2Phi0", "SignalM2Phi0Projection", "M_{2}", "#Phi_{1}");
   LegoPlot(FileS, "HToyM2Theta0", "SignalM2Theta0Projection", "M_{2}", "cos #Theta");
   LegoPlot(FileS, "HToyM2Phi", "SignalM2PhiProjection", "M_{2}", "#Phi");
   LegoPlot(FileS, "HToyM2Theta1", "SignalM2Theta1Projection", "M_{2}", "cos #theta_{1}");
   LegoPlot(FileS, "HToyM2Theta2", "SignalM2Theta2Projection", "M_{2}", "cos #theta_{2}");
   LegoPlot(FileS, "HToyPhi0Theta0", "SignalPhi0Theta0Projection", "#Phi_{1}", "cos #Theta");
   LegoPlot(FileS, "HToyPhi0Phi", "SignalPhi0PhiProjection", "#Phi_{1}", "#Phi");
   LegoPlot(FileS, "HToyPhi0Theta1", "SignalPhi0Theta1Projection", "#Phi_{1}", "cos #theta_{1}");
   LegoPlot(FileS, "HToyPhi0Theta2", "SignalPhi0Theta2Projection", "#Phi_{1}", "cos #theta_{2}");
   LegoPlot(FileS, "HToyTheta0Phi", "SignalTheta0PhiProjection", "cos #Theta", "#Phi");
   LegoPlot(FileS, "HToyTheta0Theta1", "SignalTheta0Theta1Projection", "cos #Theta", "cos #theta_{1}");
   LegoPlot(FileS, "HToyTheta0Theta2", "SignalTheta0Theta2Projection", "cos #Theta", "cos #theta_{2}");
   LegoPlot(FileS, "HToyPhiTheta1", "SignalPhiTheta1Projection", "#Phi", "cos #theta_{1}");
   LegoPlot(FileS, "HToyPhiTheta2", "SignalPhiTheta2Projection", "#Phi", "cos #theta_{2}");
   LegoPlot(FileS, "HToyTheta1Theta2", "SignalTheta1Theta2Projection", "cos #theta_{1}", "cos #theta_{2}");
   
   FileS.Close();

   return 0;
}

void ExportPlots(TFile &F, string Name1, string Name2, string NameBase, string XAxis, bool LogY)
{
   TH1D *H1 = (TH1D *)F.Get(Name1.c_str());
   TH1D *H2 = (TH1D *)F.Get(Name2.c_str());

   TCanvas Canvas;
   Canvas.SetLeftMargin(0.15);

   H1->Scale(1 / H1->Integral());
   H2->Scale(1 / H2->Integral());

   H1->GetXaxis()->SetTitle(XAxis.c_str());
   H2->GetXaxis()->SetTitle(XAxis.c_str());

   H1->GetYaxis()->SetTitle(Form("#frac{1}{#sigma} #frac{d #sigma}{d %s}", XAxis.c_str()));
   H2->GetYaxis()->SetTitle(Form("#frac{1}{#sigma} #frac{d #sigma}{d %s}", XAxis.c_str()));

   H1->GetYaxis()->SetTitleOffset(1.45);
   H2->GetYaxis()->SetTitleOffset(1.45);

   H1->GetXaxis()->CenterTitle(true);
   H2->GetXaxis()->CenterTitle(true);

   H1->GetYaxis()->CenterTitle(true);
   H2->GetYaxis()->CenterTitle(true);

   H1->SetStats(0);
   H2->SetStats(0);

   if(LogY == false)
   {
      H1->SetMinimum(0);
      H2->SetMinimum(0);
   }
   else
   {
      H1->SetMinimum(1e-4);
      H2->SetMinimum(1e-4);
   }

   H1->SetLineWidth(2);
   H2->SetLineWidth(2);

   H1->SetLineColor(kRed);
   H2->SetLineColor(kBlue);

   H1->SetMarkerColor(kRed);
   H2->SetMarkerColor(kBlue);

   H1->SetMarkerSize(6);
   H2->SetMarkerSize(6);

   H1->Draw("error");
   H2->Draw("same");

   if(LogY == true)
      Canvas.SetLogy(true);

   Canvas.SaveAs(Form("%s.png", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.C", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", NameBase.c_str()));
}

void LegoPlot(TFile &F, string Name, string NameBase, string XAxis, string YAxis)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());

   TCanvas Canvas;

   H->SetStats(0);
   H->GetXaxis()->SetTitle(XAxis.c_str());
   H->GetYaxis()->SetTitle(YAxis.c_str());

   H->GetXaxis()->CenterTitle(true);
   H->GetYaxis()->CenterTitle(true);
   
   H->GetXaxis()->SetTitleOffset(2.0);
   H->GetYaxis()->SetTitleOffset(2.0);

   H->Rebin2D(2, 2);

   H->Scale(1/H->Integral());
   
   H->Draw("lego20z");

   Canvas.SaveAs(Form("%s.png", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.C", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", NameBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", NameBase.c_str()));
}





