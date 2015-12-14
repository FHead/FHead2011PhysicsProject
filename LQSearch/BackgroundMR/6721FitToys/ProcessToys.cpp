#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "TROOT.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TF1.h"

#include "PlotHelper2.h"
#include "DataHelper.h"

int main()
{
   gROOT->SetStyle("Plain");

   DataHelper DHFile("ToyResults.dh");

   vector<string> States = DHFile.GetListOfKeys();

   TFile F("ResultPlots.root", "RECREATE");

   PsFileHelper PsFile("FinalResults.ps");
   PsFile.AddTextPage("Final results of the toys");

   TH1D HParameterA("HParameterA", "Parameter A distribution", 75, 0.003, 0.006);
   TH1D HParameterB("HParameterB", "Parameter B distribution", 75, 0.045, 0.06);
   TH1D HParameterAError("HParameterAError", "Error on parameter A distribution", 75, 0.00024, 0.00028);
   TH1D HParameterBError("HParameterBError", "Error on parameter B distribution", 75, 0.0018, 0.0022);
   TH1D HParameterAPull("HParameterAPull", "Pull of parameter A distribution", 75, -8, 8);
   TH1D HParameterBPull("HParameterBPull", "Pull of parameter B distribution", 75, -8, 8);

   TH1D HExponent1("HExponent1", "First exponent in single fit", 75, 0.01, 0.015);
   TH1D HExponent1Error("HExponent1Error", "Error on first exponent in single fit", 75, 0, 0.01);
   TH1D HExponent1Pull("HExponent1Pull", "Pull of first exponent in single fit", 75, -5, 5);
   TH1D HExponent2("HExponent2", "Second exponent in single fit", 75, 0.01, 0.015);
   TH1D HExponent2Error("HExponent2Error", "Error on second exponent in single fit", 75, 0, 0.01);
   TH1D HExponent2Pull("HExponent2Pull", "Pull of second exponent in single fit", 75, -5, 5);
   TH1D HExponent3("HExponent3", "Third exponent in single fit", 75, 0.012, 0.17);
   TH1D HExponent3Error("HExponent3Error", "Error on Third exponent in single fit", 75, 0, 0.01);
   TH1D HExponent3Pull("HExponent3Pull", "Pull of Third exponent in single fit", 75, -5, 5);
   TH1D HExponent4("HExponent4", "Fourth exponent in single fit", 75, 0.015, 0.02);
   TH1D HExponent4Error("HExponent4Error", "Error on fourth exponent in single fit", 75, 0, 0.01);
   TH1D HExponent4Pull("HExponent4Pull", "Pull of fourth exponent in single fit", 75, -5, 5);
   TH1D HExponent5("HExponent5", "Fifth exponent in single fit", 75, 0.015, 0.025);
   TH1D HExponent5Error("HExponent5Error", "Error on fifth exponent in single fit", 75, 0, 0.01);
   TH1D HExponent5Pull("HExponent5Pull", "Pull of fifth exponent in single fit", 75, -5, 5);

   double InputA = 0.00452278;
   double InputB = 0.0526323;

   for(int i = 0; i < (int)States.size(); i++)
   {
      double A = DHFile[States[i]]["SimultaneousA"].GetDouble();
      double AError = DHFile[States[i]]["SimultaneousAError"].GetDouble();
      double B = DHFile[States[i]]["SimultaneousB"].GetDouble();
      double BError = DHFile[States[i]]["SimultaneousBError"].GetDouble();

      HParameterA.Fill(A);
      HParameterB.Fill(B);
      HParameterAError.Fill(AError);
      HParameterBError.Fill(BError);
      HParameterAPull.Fill((A - InputA) / AError);
      HParameterBPull.Fill((B - InputB) / BError);

      double Exp1 = DHFile[States[i]]["SingleBin1S"].GetDouble();
      double Exp1Error = DHFile[States[i]]["SingleBin1SError"].GetDouble();
      double Exp2 = DHFile[States[i]]["SingleBin2S"].GetDouble();
      double Exp2Error = DHFile[States[i]]["SingleBin2SError"].GetDouble();
      double Exp3 = DHFile[States[i]]["SingleBin3S"].GetDouble();
      double Exp3Error = DHFile[States[i]]["SingleBin3SError"].GetDouble();
      double Exp4 = DHFile[States[i]]["SingleBin4S"].GetDouble();
      double Exp4Error = DHFile[States[i]]["SingleBin4SError"].GetDouble();
      double Exp5 = DHFile[States[i]]["SingleBin5S"].GetDouble();
      double Exp5Error = DHFile[States[i]]["SingleBin5SError"].GetDouble();

      HExponent1.Fill(Exp1);
      HExponent1Error.Fill(Exp1Error);
      HExponent1Pull.Fill((Exp1 - (InputA + InputB * 0.35 * 0.35)) / Exp1Error);
      HExponent2.Fill(Exp2);
      HExponent2Error.Fill(Exp2Error);
      HExponent2Pull.Fill((Exp2 - (InputA + InputB * 0.40 * 0.40)) / Exp2Error);
      HExponent3.Fill(Exp3);
      HExponent3Error.Fill(Exp3Error);
      HExponent3Pull.Fill((Exp3 - (InputA + InputB * 0.45 * 0.45)) / Exp3Error);
      HExponent4.Fill(Exp4);
      HExponent4Error.Fill(Exp4Error);
      HExponent4Pull.Fill((Exp4 - (InputA + InputB * 0.50 * 0.50)) / Exp4Error);
      HExponent5.Fill(Exp5);
      HExponent5Error.Fill(Exp5Error);
      HExponent5Pull.Fill((Exp5 - (InputA + InputB * 0.55 * 0.55)) / Exp5Error);
   }

   PsFile.AddPlot(HParameterA, "", true);
   PsFile.AddPlot(HParameterAError, "", true);
   PsFile.AddPlot(HParameterB, "", true);
   PsFile.AddPlot(HParameterBError, "", true);
   PsFile.AddPlot(HParameterAPull, "", true);
   PsFile.AddPlot(HParameterBPull, "", true);

   HParameterA.Fit("gaus");
   HParameterAError.Fit("gaus");
   HParameterAPull.Fit("gaus");
   HParameterB.Fit("gaus");
   HParameterBError.Fit("gaus");
   HParameterBPull.Fit("gaus");

   DataHelper DHFile2("Summary.dh");
   DHFile2["A"]["Mean"] = HParameterA.GetFunction("gaus")->GetParameter(1);
   DHFile2["A"]["MeanError"] = HParameterA.GetFunction("gaus")->GetParError(1);
   DHFile2["A"]["Sigma"] = HParameterA.GetFunction("gaus")->GetParameter(2);
   DHFile2["A"]["SigmaError"] = HParameterA.GetFunction("gaus")->GetParError(2);
   DHFile2["AError"]["Mean"] = HParameterAError.GetFunction("gaus")->GetParameter(1);
   DHFile2["AError"]["MeanError"] = HParameterAError.GetFunction("gaus")->GetParError(1);
   DHFile2["AError"]["Sigma"] = HParameterAError.GetFunction("gaus")->GetParameter(2);
   DHFile2["AError"]["SigmaError"] = HParameterAError.GetFunction("gaus")->GetParError(2);
   DHFile2["APull"]["Mean"] = HParameterAPull.GetFunction("gaus")->GetParameter(1);
   DHFile2["APull"]["MeanError"] = HParameterAPull.GetFunction("gaus")->GetParError(1);
   DHFile2["APull"]["Sigma"] = HParameterAPull.GetFunction("gaus")->GetParameter(2);
   DHFile2["APull"]["SigmaError"] = HParameterAPull.GetFunction("gaus")->GetParError(2);
   DHFile2["B"]["Mean"] = HParameterB.GetFunction("gaus")->GetParameter(1);
   DHFile2["B"]["MeanError"] = HParameterB.GetFunction("gaus")->GetParError(1);
   DHFile2["B"]["Sigma"] = HParameterB.GetFunction("gaus")->GetParameter(2);
   DHFile2["B"]["SigmaError"] = HParameterB.GetFunction("gaus")->GetParError(2);
   DHFile2["BError"]["Mean"] = HParameterBError.GetFunction("gaus")->GetParameter(1);
   DHFile2["BError"]["MeanError"] = HParameterBError.GetFunction("gaus")->GetParError(1);
   DHFile2["BError"]["Sigma"] = HParameterBError.GetFunction("gaus")->GetParameter(2);
   DHFile2["BError"]["SigmaError"] = HParameterBError.GetFunction("gaus")->GetParError(2);
   DHFile2["BPull"]["Mean"] = HParameterBPull.GetFunction("gaus")->GetParameter(1);
   DHFile2["BPull"]["MeanError"] = HParameterBPull.GetFunction("gaus")->GetParError(1);
   DHFile2["BPull"]["Sigma"] = HParameterBPull.GetFunction("gaus")->GetParameter(2);
   DHFile2["BPull"]["SigmaError"] = HParameterBPull.GetFunction("gaus")->GetParError(2);
   DHFile2.SaveToFile("Summary.dh");

   // gStyle->SetOptFit(111);

   TCanvas ResultCanvas;
   ResultCanvas.Divide(3, 2);

   ResultCanvas.cd(1)->SetLogy();
   HParameterA.Draw();
   ResultCanvas.cd(2)->SetLogy();
   HParameterAError.Draw();
   ResultCanvas.cd(3)->SetLogy();
   HParameterAPull.Draw();
   
   ResultCanvas.cd(4)->SetLogy();
   HParameterB.Draw();
   ResultCanvas.cd(5)->SetLogy();
   HParameterBError.Draw();
   ResultCanvas.cd(6)->SetLogy();
   HParameterBPull.Draw();
   
   PsFile.AddCanvas(ResultCanvas);
   ResultCanvas.SaveAs("ResultOfToys.png");
   ResultCanvas.SaveAs("ResultOfToys.C");
   ResultCanvas.SaveAs("ResultOfToys.eps");

   vector<string> FitResultPage;
   FitResultPage.push_back("Input A and B: 0.00452278 and 0.0526323");
   FitResultPage.push_back("");
   FitResultPage.push_back("Result of fitting (binned) gaussian to each distribution ==> ");
   FitResultPage.push_back("");

   stringstream str;
   str << "Parameter A, mean = " << HParameterA.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HParameterA.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter A error, mean = " << HParameterAError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterAError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterAError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterAError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter A pull, mean = " << HParameterAPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterAPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterAPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterAPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B, mean = " << HParameterB.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B error, mean = " << HParameterBError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterBError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterBError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterBError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B pull, mean = " << HParameterBPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterBPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterBPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterBPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   PsFile.AddTextPage(FitResultPage, 0.1, 0.9, 0.032);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HParameterA.Write();
   HParameterAError.Write();
   HParameterAPull.Write();
   HParameterB.Write();
   HParameterBError.Write();
   HParameterBPull.Write();

   F.Close();

   return 0;
}



