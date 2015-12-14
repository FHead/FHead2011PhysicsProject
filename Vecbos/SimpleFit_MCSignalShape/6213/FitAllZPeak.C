#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"

#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooLorentzian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooCruijff.h"
#include "RooPlot.h"

#include "PlotHelper.h"

using namespace RooFit;

struct FitResult;
void FitAllZPeak(string RootFile = "Samples/ZJetsAll.root");
void FitZPeak(string RootFile = "Samples/ZJetsAll.root", string JetFlavor = "Calo");
FitResult FitZPeak(string RootFile, int JetCount, string JetFlavor, PsFileHelper &PsFile);

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
};

void FitAllZPeak(string RootFile)
{
   FitZPeak(RootFile, "Calo");
   FitZPeak(RootFile, "UncorrectedCalo");
   FitZPeak(RootFile, "PF");
   FitZPeak(RootFile, "Track");
}

void FitZPeak(string RootFile, string JetFlavor)
{
   vector<FitResult> Results;

   PsFileHelper PsFile(JetFlavor + "JetShapes.ps");
   PsFile.AddTextPage("Signal shape with different inclusive " + JetFlavor + " jet bins");

   for(int i = 0; i <= 4; i++)
      Results.push_back(FitZPeak(RootFile, i, JetFlavor, PsFile));

   PsFile.AddTimeStampPage();
   PsFile.Close();

   cout << "\\begin{table}[htdp]" << endl;
   cout << " \\caption{Results of a ML fit to a sample of signal Monte Carlo events with "
      << JetFlavor << " jets."
      << "\\label{tab:peakingZshape" << JetFlavor << "}}" << endl;
   cout << " \\centering" << endl;
   cout << " \\begin{tabular}{|c|c|c|c|c|}" << endl;
   cout << "   \\hline" << endl;
   cout << "   \\verb|Parameter| & $Z+\\geq 0~jets$ & $Z+\\geq 1~jets$"
      << "& $Z+\\geq 2~jets$ & $Z+\\geq 3~jets$ & $Z+\\geq 4~jets$ \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   $m$        ";
   for(int i = 0; i <= 4; i++)
      cout << "& $ " << Results[i].Mass[0] << " \\pm " << Results[i].Mass[1] << " $";
   cout << " \\\\" << endl;
   cout << "   $\\sigma_L$  ";
   for(int i = 0; i <= 4; i++)
      cout << "& $ " << Results[i].SigmaL[0] << " \\pm " << Results[i].SigmaL[1] << "$ ";
   cout << "\\\\" << endl;
   cout << "   $\\sigma_R$  ";
   for(int i = 0; i <= 4; i++)
      cout << "& $ " << Results[i].SigmaR[0] << " \\pm " << Results[i].SigmaR[1] << "$ ";
   cout << "\\\\" << endl;
   cout << "   $\\alpha_L$  ";
   for(int i = 0; i <= 4; i++)
      cout << "& $ " << Results[i].AlphaL[0] << " \\pm " << Results[i].AlphaL[1] << "$ ";
   cout << "\\\\" << endl;
   cout << "   $\\alpha_R$  ";
   for(int i = 0; i <= 4; i++)
      cout << "& $ " << Results[i].AlphaR[0] << " \\pm " << Results[i].AlphaR[1] << "$ ";
   cout << "\\\\" << endl;
   cout << "   \\hline" << endl;
   cout << " \\end{tabular}" << endl;
   cout << "\\end{table}" << endl;
}

FitResult FitZPeak(string RootFile, int JetCount, string JetFlavor, PsFileHelper &PsFile)
{
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NJets(Form("N%sJet", JetFlavor.c_str()), "Count of jets", 0, 100000);
   RooArgSet TreeVarSet(ZMass, NJets);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("outTree");
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = Form("N%sJet >= %d", JetFlavor.c_str(), JetCount);
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.000, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 0.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.508, 0.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 0.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 0.01, 1000000);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);

   MainZPeak.fitTo(*ReducedDataSet);

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title("Mass of lepton pair"));

   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));

   MainZPeak.paramOn(FinalResult, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));

   MainZPeak.plotOn(FinalResult, LineColor(kRed));

   TCanvas Canvas("c1", "c1", 0, 0, 1024, 768);
   FinalResult->Draw();
   // Canvas.SaveAs(Form("FitResult_%sJet%d.png", JetFlavor.c_str(), JetCount));
   // Canvas.SaveAs(Form("FitResult_%sJet%d.C", JetFlavor.c_str(), JetCount));
   // Canvas.SaveAs(Form("FitResult_%sJet%d.eps", JetFlavor.c_str(), JetCount));

   PsFile.AddCanvas(Canvas);

   FitResult Result;

   Result.Mass[0] = PeakPosition.getVal();
   Result.Mass[1] = PeakPosition.getError();
   Result.AlphaL[0] = AlphaL.getVal();
   Result.AlphaL[1] = AlphaL.getError();
   Result.AlphaR[0] = AlphaR.getVal();
   Result.AlphaR[1] = AlphaR.getError();
   Result.SigmaL[0] = SigmaL.getVal();
   Result.SigmaL[1] = SigmaL.getError();
   Result.SigmaR[0] = SigmaR.getVal();
   Result.SigmaR[1] = SigmaR.getError();

   return Result;
}

