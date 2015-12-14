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

   TH1D HB("HB", "Parameter B distribution", 75, 0.03, 0.05);
   TH1D HBError("HBError", "Error on parameter B", 75, 0.0016, 0.0023);
   TH1D HBPull("HBPull", "Pull on parameter B", 75, -8, 8);
   TH1D HMROffset("HMROffset", "Parameter MROffset distribution", 75, -260, -80);
   TH1D HMROffsetError("HMROffsetError", "Error on parameter MROffset", 75, 0, 50);
   TH1D HMROffsetPull("HMROffsetPull", "Pull on parameter MROffset", 75, -8, 8);
   TH1D HR2Offset("HR2Offset", "Parameter R2Offset distribution", 75, -0.3, -0.05);
   TH1D HR2OffsetError("HR2OffsetError", "Error on parameter R2Offset", 75, 0.00, 0.02);
   TH1D HR2OffsetPull("HR2OffsetPull", "Pull on parameter R2Offset", 75, -8, 8);

   double InputB = 0.0401283;
   double InputMROffset = -173.396;
   double InputR2Offset = -0.144164;

   for(int i = 0; i < (int)States.size(); i++)
   {
      double B = DHFile[States[i]]["B"].GetDouble();
      double BError = DHFile[States[i]]["BError"].GetDouble();
      double MROffset = DHFile[States[i]]["MROffset"].GetDouble();
      double MROffsetError = DHFile[States[i]]["MROffsetError"].GetDouble();
      double R2Offset = DHFile[States[i]]["R2Offset"].GetDouble();
      double R2OffsetError = DHFile[States[i]]["R2OffsetError"].GetDouble();

      HB.Fill(B);
      HBError.Fill(BError);
      HBPull.Fill((B - InputB) / BError);
      HMROffset.Fill(MROffset);
      HMROffsetError.Fill(MROffsetError);
      HMROffsetPull.Fill((MROffset - InputMROffset) / MROffsetError);
      HR2Offset.Fill(R2Offset);
      HR2OffsetError.Fill(R2OffsetError);
      HR2OffsetPull.Fill((R2Offset - InputR2Offset) / R2OffsetError);
   }

   PsFile.AddPlot(HB, "", true);
   PsFile.AddPlot(HBError, "", true);
   PsFile.AddPlot(HBPull, "", true);
   PsFile.AddPlot(HMROffset, "", true);
   PsFile.AddPlot(HMROffsetError, "", true);
   PsFile.AddPlot(HMROffsetPull, "", true);
   PsFile.AddPlot(HR2Offset, "", true);
   PsFile.AddPlot(HR2OffsetError, "", true);
   PsFile.AddPlot(HR2OffsetPull, "", true);

   HB.Fit("gaus");
   HBError.Fit("gaus");
   HBPull.Fit("gaus");
   HMROffset.Fit("gaus");
   HMROffsetError.Fit("gaus");
   HMROffsetPull.Fit("gaus");
   HR2Offset.Fit("gaus");
   HR2OffsetError.Fit("gaus");
   HR2OffsetPull.Fit("gaus");

   TCanvas ResultCanvas;
   ResultCanvas.Divide(3, 3);

   ResultCanvas.cd(1)->SetLogy();
   HB.Draw();
   ResultCanvas.cd(2)->SetLogy();
   HBError.Draw();
   ResultCanvas.cd(3)->SetLogy();
   HBPull.Draw();

   ResultCanvas.cd(4)->SetLogy();
   HMROffset.Draw();
   ResultCanvas.cd(5)->SetLogy();
   HMROffsetError.Draw();
   ResultCanvas.cd(6)->SetLogy();
   HMROffsetPull.Draw();

   ResultCanvas.cd(7)->SetLogy();
   HR2Offset.Draw();
   ResultCanvas.cd(8)->SetLogy();
   HR2OffsetError.Draw();
   ResultCanvas.cd(9)->SetLogy();
   HR2OffsetPull.Draw();
   
   PsFile.AddCanvas(ResultCanvas);
   ResultCanvas.SaveAs("ResultOfToys.png");
   ResultCanvas.SaveAs("ResultOfToys.C");
   ResultCanvas.SaveAs("ResultOfToys.eps");

   TCanvas PullCanvas("PullCanvas", "PullCanvas", 512 * 3, 512);
   PullCanvas.Divide(3, 1);
   PullCanvas.cd(1)->SetLogy();
   HBPull.SetStats(0);
   HBPull.Draw();
   PullCanvas.cd(3)->SetLogy();
   HMROffsetPull.SetStats(0);
   HMROffsetPull.Draw();
   PullCanvas.cd(2)->SetLogy();
   HR2OffsetPull.SetStats(0);
   HR2OffsetPull.Draw();
   PullCanvas.SaveAs("Pulls.png");
   PullCanvas.SaveAs("Pulls.C");
   PullCanvas.SaveAs("Pulls.eps");
   
   vector<string> FitResultPage;
   FitResultPage.push_back("Input B, MR0, R20: 0.0401283, -173.396, -0.144164");
   FitResultPage.push_back("");

   stringstream str;
   str << "Parameter B, mean = " << HB.GetFunction("gaus")->GetParameter(1) << " +- "
      << HB.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HB.GetFunction("gaus")->GetParameter(2) << " +- "
      << HB.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B error, mean = " << HBError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HBError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HBError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HBError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter B pull, mean = " << HBPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HBPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HBPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HBPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MROffset, mean = " << HMROffset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMROffset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HMROffset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMROffset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MROffset error, mean = " << HMROffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMROffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMROffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMROffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter MROffset pull, mean = " << HMROffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HMROffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HMROffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HMROffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R2Offset, mean = " << HR2Offset.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR2Offset.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "      sigma = " << HR2Offset.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR2Offset.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R2Offset error, mean = " << HR2OffsetError.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR2OffsetError.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR2OffsetError.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR2OffsetError.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   str.str("");
   str << "Parameter R2Offset pull, mean = " << HR2OffsetPull.GetFunction("gaus")->GetParameter(1) << " +- "
      << HR2OffsetPull.GetFunction("gaus")->GetParError(1);
   FitResultPage.push_back(str.str());
   
   str.str("");
   str << "      sigma = " << HR2OffsetPull.GetFunction("gaus")->GetParameter(2) << " +- "
      << HR2OffsetPull.GetFunction("gaus")->GetParError(2);
   FitResultPage.push_back(str.str());

   PsFile.AddTextPage(FitResultPage, 0.1, 0.9, 0.025);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   HB.Write();
   HBError.Write();
   HBPull.Write();
   HMROffset.Write();
   HMROffsetError.Write();
   HMROffsetPull.Write();
   HR2Offset.Write();
   HR2OffsetError.Write();
   HR2OffsetPull.Write();

   F.Close();

   return 0;
}



