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

   TH1D HParameterA1("HParameterA1", "Parameter A1 distribution", 75, 0.002, 0.007);
   TH1D HParameterB1("HParameterB1", "Parameter B1 distribution", 75, 0.035, 0.07);
   TH1D HParameterA1Error("HParameterA1Error", "Error on parameter A1 distribution", 75, 0.0001, 0.001);
   TH1D HParameterB1Error("HParameterB1Error", "Error on parameter B1 distribution", 75, 0.001, 0.009);
   TH1D HParameterA1Pull("HParameterA1Pull", "Pull of parameter A1 distribution", 75, -8, 8);
   TH1D HParameterB1Pull("HParameterB1Pull", "Pull of parameter B1 distribution", 75, -8, 8);
   TH1D HParameterA2("HParameterA2", "Parameter A2 distribution", 75, -0.002, 0.006);
   TH1D HParameterB2("HParameterB2", "Parameter B2 distribution", 75, -0.01, 0.045);
   TH1D HParameterA2Error("HParameterA2Error", "Error on parameter A2 distribution", 75, 0.00024, 0.002);
   TH1D HParameterB2Error("HParameterB2Error", "Error on parameter B2 distribution", 75, 0.0018, 0.015);
   TH1D HParameterA2Pull("HParameterA2Pull", "Pull of parameter A2 distribution", 75, -8, 8);
   TH1D HParameterB2Pull("HParameterB2Pull", "Pull of parameter B2 distribution", 75, -8, 8);

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

   double InputA1 = 0.00452278;
   double InputB1 = 0.0526323;
   double InputA2 = 0.00452278 / 2.5;
   double InputB2 = 0.0526323 / 3;

   for(int i = 0; i < (int)States.size(); i++)
   {
      double A1 = DHFile[States[i]]["SimultaneousA1"].GetDouble();
      double A1Error = DHFile[States[i]]["SimultaneousA1Error"].GetDouble();
      double B1 = DHFile[States[i]]["SimultaneousB1"].GetDouble();
      double B1Error = DHFile[States[i]]["SimultaneousB1Error"].GetDouble();
      double A2 = DHFile[States[i]]["SimultaneousA2"].GetDouble();
      double A2Error = DHFile[States[i]]["SimultaneousA2Error"].GetDouble();
      double B2 = DHFile[States[i]]["SimultaneousB2"].GetDouble();
      double B2Error = DHFile[States[i]]["SimultaneousB2Error"].GetDouble();

      HParameterA1.Fill(A1);
      HParameterB1.Fill(B1);
      HParameterA1Error.Fill(A1Error);
      HParameterB1Error.Fill(B1Error);
      HParameterA1Pull.Fill((A1 - InputA1) / A1Error);
      HParameterB1Pull.Fill((B1 - InputB1) / B1Error);
      HParameterA2.Fill(A2);
      HParameterB2.Fill(B2);
      HParameterA2Error.Fill(A2Error);
      HParameterB2Error.Fill(B2Error);
      HParameterA2Pull.Fill((A2 - InputA2) / A2Error);
      HParameterB2Pull.Fill((B2 - InputB2) / B2Error);

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
      HExponent1Pull.Fill((Exp1 - (InputA1 + InputB1 * 0.35 * 0.35)) / Exp1Error);
      HExponent2.Fill(Exp2);
      HExponent2Error.Fill(Exp2Error);
      HExponent2Pull.Fill((Exp2 - (InputA1 + InputB1 * 0.40 * 0.40)) / Exp2Error);
      HExponent3.Fill(Exp3);
      HExponent3Error.Fill(Exp3Error);
      HExponent3Pull.Fill((Exp3 - (InputA1 + InputB1 * 0.45 * 0.45)) / Exp3Error);
      HExponent4.Fill(Exp4);
      HExponent4Error.Fill(Exp4Error);
      HExponent4Pull.Fill((Exp4 - (InputA1 + InputB1 * 0.50 * 0.50)) / Exp4Error);
      HExponent5.Fill(Exp5);
      HExponent5Error.Fill(Exp5Error);
      HExponent5Pull.Fill((Exp5 - (InputA1 + InputB1 * 0.55 * 0.55)) / Exp5Error);
   }

   PsFile.AddPlot(HParameterA1, "", true);
   PsFile.AddPlot(HParameterA1Error, "", true);
   PsFile.AddPlot(HParameterB1, "", true);
   PsFile.AddPlot(HParameterB1Error, "", true);
   PsFile.AddPlot(HParameterA1Pull, "", true);
   PsFile.AddPlot(HParameterB1Pull, "", true);
   PsFile.AddPlot(HParameterA2, "", true);
   PsFile.AddPlot(HParameterA2Error, "", true);
   PsFile.AddPlot(HParameterB2, "", true);
   PsFile.AddPlot(HParameterB2Error, "", true);
   PsFile.AddPlot(HParameterA2Pull, "", true);
   PsFile.AddPlot(HParameterB2Pull, "", true);

   HParameterA1.Fit("gaus");
   HParameterA1Error.Fit("gaus");
   HParameterA1Pull.Fit("gaus");
   HParameterB1.Fit("gaus");
   HParameterB1Error.Fit("gaus");
   HParameterB1Pull.Fit("gaus");
   HParameterA2.Fit("gaus");
   HParameterA2Error.Fit("gaus");
   HParameterA2Pull.Fit("gaus");
   HParameterB2.Fit("gaus");
   HParameterB2Error.Fit("gaus");
   HParameterB2Pull.Fit("gaus");

   DataHelper DHFile2("Summary.dh");
   DHFile2["A1"]["Mean"] = HParameterA1.GetFunction("gaus")->GetParameter(1);
   DHFile2["A1"]["MeanError"] = HParameterA1.GetFunction("gaus")->GetParError(1);
   DHFile2["A1"]["Sigma"] = HParameterA1.GetFunction("gaus")->GetParameter(2);
   DHFile2["A1"]["SigmaError"] = HParameterA1.GetFunction("gaus")->GetParError(2);
   DHFile2["A1Error"]["Mean"] = HParameterA1Error.GetFunction("gaus")->GetParameter(1);
   DHFile2["A1Error"]["MeanError"] = HParameterA1Error.GetFunction("gaus")->GetParError(1);
   DHFile2["A1Error"]["Sigma"] = HParameterA1Error.GetFunction("gaus")->GetParameter(2);
   DHFile2["A1Error"]["SigmaError"] = HParameterA1Error.GetFunction("gaus")->GetParError(2);
   DHFile2["A1Pull"]["Mean"] = HParameterA1Pull.GetFunction("gaus")->GetParameter(1);
   DHFile2["A1Pull"]["MeanError"] = HParameterA1Pull.GetFunction("gaus")->GetParError(1);
   DHFile2["A1Pull"]["Sigma"] = HParameterA1Pull.GetFunction("gaus")->GetParameter(2);
   DHFile2["A1Pull"]["SigmaError"] = HParameterA1Pull.GetFunction("gaus")->GetParError(2);
   DHFile2["B1"]["Mean"] = HParameterB1.GetFunction("gaus")->GetParameter(1);
   DHFile2["B1"]["MeanError"] = HParameterB1.GetFunction("gaus")->GetParError(1);
   DHFile2["B1"]["Sigma"] = HParameterB1.GetFunction("gaus")->GetParameter(2);
   DHFile2["B1"]["SigmaError"] = HParameterB1.GetFunction("gaus")->GetParError(2);
   DHFile2["B1Error"]["Mean"] = HParameterB1Error.GetFunction("gaus")->GetParameter(1);
   DHFile2["B1Error"]["MeanError"] = HParameterB1Error.GetFunction("gaus")->GetParError(1);
   DHFile2["B1Error"]["Sigma"] = HParameterB1Error.GetFunction("gaus")->GetParameter(2);
   DHFile2["B1Error"]["SigmaError"] = HParameterB1Error.GetFunction("gaus")->GetParError(2);
   DHFile2["B1Pull"]["Mean"] = HParameterB1Pull.GetFunction("gaus")->GetParameter(1);
   DHFile2["B1Pull"]["MeanError"] = HParameterB1Pull.GetFunction("gaus")->GetParError(1);
   DHFile2["B1Pull"]["Sigma"] = HParameterB1Pull.GetFunction("gaus")->GetParameter(2);
   DHFile2["B1Pull"]["SigmaError"] = HParameterB1Pull.GetFunction("gaus")->GetParError(2);
   DHFile2.SaveToFile("Summary.dh");

   // gStyle->SetOptFit(111);

   TCanvas ResultCanvas1;
   ResultCanvas1.Divide(3, 2);

   ResultCanvas1.cd(1)->SetLogy();
   HParameterA1.Draw();
   ResultCanvas1.cd(2)->SetLogy();
   HParameterA1Error.Draw();
   ResultCanvas1.cd(3)->SetLogy();
   HParameterA1Pull.Draw();
   
   ResultCanvas1.cd(4)->SetLogy();
   HParameterB1.Draw();
   ResultCanvas1.cd(5)->SetLogy();
   HParameterB1Error.Draw();
   ResultCanvas1.cd(6)->SetLogy();
   HParameterB1Pull.Draw();
   
   PsFile.AddCanvas(ResultCanvas1);
   ResultCanvas1.SaveAs("ResultOfToys1.png");
   ResultCanvas1.SaveAs("ResultOfToys1.C");
   ResultCanvas1.SaveAs("ResultOfToys1.eps");
   
   TCanvas ResultCanvas2;
   ResultCanvas2.Divide(3, 2);

   ResultCanvas2.cd(1)->SetLogy();
   HParameterA2.Draw();
   ResultCanvas2.cd(2)->SetLogy();
   HParameterA2Error.Draw();
   ResultCanvas2.cd(3)->SetLogy();
   HParameterA2Pull.Draw();
   
   ResultCanvas2.cd(4)->SetLogy();
   HParameterB2.Draw();
   ResultCanvas2.cd(5)->SetLogy();
   HParameterB2Error.Draw();
   ResultCanvas2.cd(6)->SetLogy();
   HParameterB2Pull.Draw();
   
   PsFile.AddCanvas(ResultCanvas2);
   ResultCanvas2.SaveAs("ResultOfToys2.png");
   ResultCanvas2.SaveAs("ResultOfToys2.C");
   ResultCanvas2.SaveAs("ResultOfToys2.eps");

   vector<string> FitResultPage1;
   FitResultPage1.push_back("Input A and B: 0.00452278 and 0.0526323");
   FitResultPage1.push_back("");
   FitResultPage1.push_back("Result of fitting (binned) gaussian to each distribution ==> ");
   FitResultPage1.push_back("");

   stringstream str;
   str << "Parameter A1, mean = " << HParameterA1.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA1.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "      sigma = " << HParameterA1.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA1.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "Parameter A1 error, mean = " << HParameterA1Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA1Error.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterA1Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA1Error.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "Parameter A1 pull, mean = " << HParameterA1Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA1Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterA1Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA1Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "Parameter B1, mean = " << HParameterB1.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB1.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB1.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB1.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "Parameter B1 error, mean = " << HParameterB1Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB1Error.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB1Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB1Error.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   str.str("");
   str << "Parameter B1 pull, mean = " << HParameterB1Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB1Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage1.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB1Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB1Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage1.push_back(str.str());

   PsFile.AddTextPage(FitResultPage1, 0.1, 0.9, 0.032);
   
   vector<string> FitResultPage2;
   FitResultPage2.push_back("Input A and B: 0.00452278 / 2.5 and 0.0526323 / 3");
   FitResultPage2.push_back("");
   FitResultPage2.push_back("Result of fitting (binned) gaussian to each distribution ==> ");
   FitResultPage2.push_back("");

   str.str("");
   str << "Parameter A2, mean = " << HParameterA2.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA2.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "      sigma = " << HParameterA2.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA2.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "Parameter A2 error, mean = " << HParameterA2Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA2Error.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterA2Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA2Error.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "Parameter A2 pull, mean = " << HParameterA2Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterA2Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterA2Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterA2Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "Parameter B2, mean = " << HParameterB1.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB2.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB2.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB2.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "Parameter B2 error, mean = " << HParameterB1Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB2Error.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB2Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB2Error.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   str.str("");
   str << "Parameter B2 pull, mean = " << HParameterB1Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HParameterB2Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage2.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HParameterB2Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HParameterB2Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage2.push_back(str.str());

   PsFile.AddTextPage(FitResultPage2, 0.1, 0.9, 0.032);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HParameterA1.Write();
   HParameterA1Error.Write();
   HParameterA1Pull.Write();
   HParameterB1.Write();
   HParameterB1Error.Write();
   HParameterB1Pull.Write();
   HParameterA2.Write();
   HParameterA2Error.Write();
   HParameterA2Pull.Write();
   HParameterB2.Write();
   HParameterB2Error.Write();
   HParameterB2Pull.Write();

   F.Close();

   return 0;
}



