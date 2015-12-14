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

   TH1D HB1("HB1", "Parameter B1 distribution", 75, 0.03, 0.05);
   TH1D HB1Error("HB1Error", "Error on parameter B1", 75, 0.0016, 0.0053);
   TH1D HB1Pull("HB1Pull", "Pull on parameter B1", 75, -8, 8);
   TH1D HMR1Offset("HMR1Offset", "Parameter MR1Offset distribution", 75, -350, -80);
   TH1D HMR1OffsetError("HMR1OffsetError", "Error on parameter MR1Offset", 75, 20, 65);
   TH1D HMR1OffsetPull("HMR1OffsetPull", "Pull on parameter MR1Offset", 75, -8, 8);
   TH1D HR21Offset("HR21Offset", "Parameter R21Offset distribution", 75, -0.3, -0.05);
   TH1D HR21OffsetError("HR21OffsetError", "Error on parameter R21Offset", 75, 0.00, 0.04);
   TH1D HR21OffsetPull("HR21OffsetPull", "Pull on parameter R21Offset", 75, -8, 8);
   TH1D HB2("HB2", "Parameter B2 distribution", 75, 0.005, 0.02);
   TH1D HB2Error("HB2Error", "Error on parameter B2", 75, 0.00, 0.002);
   TH1D HB2Pull("HB2Pull", "Pull on parameter B2", 75, -8, 8);
   TH1D HMR2Offset("HMR2Offset", "Parameter MR2Offset distribution", 75, -520, 0);
   TH1D HMR2OffsetError("HMR2OffsetError", "Error on parameter MR2Offset", 75, 30, 150);
   TH1D HMR2OffsetPull("HMR2OffsetPull", "Pull on parameter MR2Offset", 75, -8, 8);
   TH1D HR22Offset("HR22Offset", "Parameter R22Offset distribution", 75, -0.4, -0.05);
   TH1D HR22OffsetError("HR22OffsetError", "Error on parameter R22Offset", 75, 0.00, 0.10);
   TH1D HR22OffsetPull("HR22OffsetPull", "Pull on parameter R22Offset", 75, -8, 8);

   double InputB1 = 0.0401283;
   double InputMR1Offset = -173.396;
   double InputR21Offset = -0.144164;
   double InputB2 = 0.0401283 / 3;
   double InputMR2Offset = -200;
   double InputR22Offset = -0.22;

   for(int i = 0; i < (int)States.size(); i++)
   {
      double B1 = DHFile[States[i]]["B1"].GetDouble();
      double B1Error = DHFile[States[i]]["B1Error"].GetDouble();
      double MR1Offset = DHFile[States[i]]["MR1Offset"].GetDouble();
      double MR1OffsetError = DHFile[States[i]]["MR1OffsetError"].GetDouble();
      double R21Offset = DHFile[States[i]]["R21Offset"].GetDouble();
      double R21OffsetError = DHFile[States[i]]["R21OffsetError"].GetDouble();
      double B2 = DHFile[States[i]]["B2"].GetDouble();
      double B2Error = DHFile[States[i]]["B2Error"].GetDouble();
      double MR2Offset = DHFile[States[i]]["MR2Offset"].GetDouble();
      double MR2OffsetError = DHFile[States[i]]["MR2OffsetError"].GetDouble();
      double R22Offset = DHFile[States[i]]["R22Offset"].GetDouble();
      double R22OffsetError = DHFile[States[i]]["R22OffsetError"].GetDouble();

      double Fraction = DHFile[States[i]]["Fraction"].GetDouble();

      if(Fraction < 0.5)
      {
         swap(B1, B2);
         swap(B1Error, B2Error);
         swap(MR1Offset, MR2Offset);
         swap(MR1OffsetError, MR2OffsetError);
         swap(R21Offset, R22Offset);
         swap(R21OffsetError, R22OffsetError);
         Fraction = 1 - Fraction;
      }

      HB1.Fill(B1);
      HB1Error.Fill(B1Error);
      HB1Pull.Fill((B1 - InputB1) / B1Error);
      HMR1Offset.Fill(MR1Offset);
      HMR1OffsetError.Fill(MR1OffsetError);
      HMR1OffsetPull.Fill((MR1Offset - InputMR1Offset) / MR1OffsetError);
      HR21Offset.Fill(R21Offset);
      HR21OffsetError.Fill(R21OffsetError);
      HR21OffsetPull.Fill((R21Offset - InputR21Offset) / R21OffsetError);
      HB2.Fill(B2);
      HB2Error.Fill(B2Error);
      HB2Pull.Fill((B2 - InputB2) / B2Error);
      HMR2Offset.Fill(MR2Offset);
      HMR2OffsetError.Fill(MR2OffsetError);
      HMR2OffsetPull.Fill((MR2Offset - InputMR2Offset) / MR2OffsetError);
      HR22Offset.Fill(R22Offset);
      HR22OffsetError.Fill(R22OffsetError);
      HR22OffsetPull.Fill((R22Offset - InputR22Offset) / R22OffsetError);
   }

   PsFile.AddPlot(HB1, "", true);
   PsFile.AddPlot(HB1Error, "", true);
   PsFile.AddPlot(HB1Pull, "", true);
   PsFile.AddPlot(HMR1Offset, "", true);
   PsFile.AddPlot(HMR1OffsetError, "", true);
   PsFile.AddPlot(HMR1OffsetPull, "", true);
   PsFile.AddPlot(HR21Offset, "", true);
   PsFile.AddPlot(HR21OffsetError, "", true);
   PsFile.AddPlot(HR21OffsetPull, "", true);
   PsFile.AddPlot(HB2, "", true);
   PsFile.AddPlot(HB2Error, "", true);
   PsFile.AddPlot(HB2Pull, "", true);
   PsFile.AddPlot(HMR2Offset, "", true);
   PsFile.AddPlot(HMR2OffsetError, "", true);
   PsFile.AddPlot(HMR2OffsetPull, "", true);
   PsFile.AddPlot(HR22Offset, "", true);
   PsFile.AddPlot(HR22OffsetError, "", true);
   PsFile.AddPlot(HR22OffsetPull, "", true);

   HB1.Fit("gaus");
   HB1Error.Fit("gaus");
   HB1Pull.Fit("gaus");
   HMR1Offset.Fit("gaus");
   HMR1OffsetError.Fit("gaus");
   HMR1OffsetPull.Fit("gaus");
   HR21Offset.Fit("gaus");
   HR21OffsetError.Fit("gaus");
   HR21OffsetPull.Fit("gaus");
   HB2.Fit("gaus");
   HB2Error.Fit("gaus");
   HB2Pull.Fit("gaus");
   HMR2Offset.Fit("gaus");
   HMR2OffsetError.Fit("gaus");
   HMR2OffsetPull.Fit("gaus");
   HR22Offset.Fit("gaus");
   HR22OffsetError.Fit("gaus");
   HR22OffsetPull.Fit("gaus");

   TCanvas ResultCanvas1;
   ResultCanvas1.Divide(3, 3);

   ResultCanvas1.cd(1)->SetLogy();
   HB1.Draw();
   ResultCanvas1.cd(2)->SetLogy();
   HB1Error.Draw();
   ResultCanvas1.cd(3)->SetLogy();
   HB1Pull.Draw();

   ResultCanvas1.cd(4)->SetLogy();
   HMR1Offset.Draw();
   ResultCanvas1.cd(5)->SetLogy();
   HMR1OffsetError.Draw();
   ResultCanvas1.cd(6)->SetLogy();
   HMR1OffsetPull.Draw();

   ResultCanvas1.cd(7)->SetLogy();
   HR21Offset.Draw();
   ResultCanvas1.cd(8)->SetLogy();
   HR21OffsetError.Draw();
   ResultCanvas1.cd(9)->SetLogy();
   HR21OffsetPull.Draw();

   PsFile.AddCanvas(ResultCanvas1);
   ResultCanvas1.SaveAs("ResultOfToys1.png");
   ResultCanvas1.SaveAs("ResultOfToys1.C");
   ResultCanvas1.SaveAs("ResultOfToys1.eps");
 
   TCanvas ResultCanvas2;
   ResultCanvas2.Divide(3, 3);

   ResultCanvas2.cd(1)->SetLogy();
   HB2.Draw();
   ResultCanvas2.cd(2)->SetLogy();
   HB2Error.Draw();
   ResultCanvas2.cd(3)->SetLogy();
   HB2Pull.Draw();

   ResultCanvas2.cd(4)->SetLogy();
   HMR2Offset.Draw();
   ResultCanvas2.cd(5)->SetLogy();
   HMR2OffsetError.Draw();
   ResultCanvas2.cd(6)->SetLogy();
   HMR2OffsetPull.Draw();

   ResultCanvas2.cd(7)->SetLogy();
   HR22Offset.Draw();
   ResultCanvas2.cd(8)->SetLogy();
   HR22OffsetError.Draw();
   ResultCanvas2.cd(9)->SetLogy();
   HR22OffsetPull.Draw();

   PsFile.AddCanvas(ResultCanvas2);
   ResultCanvas2.SaveAs("ResultOfToys2.png");
   ResultCanvas2.SaveAs("ResultOfToys2.C");
   ResultCanvas2.SaveAs("ResultOfToys2.eps");
 
   vector<string> PullPage;

   vector<string> FitResultPage;
   FitResultPage.push_back("Input B1, MR10, R210: 0.0401283, -173.396, -0.144164");
   FitResultPage.push_back("");

   stringstream str;
   str << "Parameter B1, mean = " << HB1.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB1.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HB1.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB1.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B1 error, mean = " << HB1Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB1Error.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HB1Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB1Error.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B1 pull, mean = " << HB1Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB1Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HB1Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB1Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   str.str("");
   str << "Parameter MR1Offset, mean = " << HMR1Offset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR1Offset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HMR1Offset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR1Offset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MR1Offset error, mean = " << HMR1OffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR1OffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMR1OffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR1OffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MR1Offset pull, mean = " << HMR1OffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR1OffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMR1OffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR1OffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   str.str("");
   str << "Parameter R21Offset, mean = " << HR21Offset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR21Offset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HR21Offset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR21Offset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R21Offset error, mean = " << HR21OffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR21OffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR21OffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR21OffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R21Offset pull, mean = " << HR21OffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR21OffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR21OffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR21OffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   PsFile.AddTextPage(FitResultPage, 0.1, 0.9, 0.025);
   
   FitResultPage.clear();
   FitResultPage.push_back("Input B2, MR20, R220: 0.0401283 / 3, -200, -0.22");
   FitResultPage.push_back("");

   str.str("");
   str << "Parameter B2, mean = " << HB2.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB2.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HB2.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB2.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B2 error, mean = " << HB2Error.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB2Error.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HB2Error.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB2Error.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B2 pull, mean = " << HB2Pull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB2Pull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HB2Pull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB2Pull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   str.str("");
   str << "Parameter MR2Offset, mean = " << HMR2Offset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR2Offset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HMR2Offset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR2Offset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MR2Offset error, mean = " << HMR2OffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR2OffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMR2OffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR2OffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MR2Offset pull, mean = " << HMR2OffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMR2OffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMR2OffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMR2OffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   str.str("");
   str << "Parameter R22Offset, mean = " << HR22Offset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR22Offset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HR22Offset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR22Offset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R22Offset error, mean = " << HR22OffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR22OffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR22OffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR22OffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R22Offset pull, mean = " << HR22OffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR22OffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR22OffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR22OffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());
   PullPage.push_back(str.str());

   PsFile.AddTextPage(FitResultPage, 0.1, 0.9, 0.025);

   PsFile.AddTextPage(PullPage);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   HB1.Write();
   HB1Error.Write();
   HB1Pull.Write();
   HMR1Offset.Write();
   HMR1OffsetError.Write();
   HMR1OffsetPull.Write();
   HR21Offset.Write();
   HR21OffsetError.Write();
   HR21OffsetPull.Write();
   HB2.Write();
   HB2Error.Write();
   HB2Pull.Write();
   HMR2Offset.Write();
   HMR2OffsetError.Write();
   HMR2OffsetPull.Write();
   HR22Offset.Write();
   HR22OffsetError.Write();
   HR22OffsetPull.Write();

   F.Close();

   return 0;
}



