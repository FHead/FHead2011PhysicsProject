#include <iostream>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "TLatex.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string InputTreeName = CL.Get("tree", "DiscretizedJetTree");
   string OutputFileName = CL.Get("output", "JetImages.pdf");
   double Fraction = CL.GetDouble("fraction", 0.01);
   double MinJetPT = CL.GetDouble("minjetpt", 300);
   int MaxCount = CL.GetInt("max", -1);

   double TextTop = 0.9;
   double TextLeft = 0.1;
   double TextHeight = 0.1;

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get(InputTreeName.c_str());
   assert(Tree != NULL);

   int HydjetEntry, PythiaEntry, AllJetCount, JetCount, JetIndex;
   float JetPT, JetEta, JetPhi;
   float Images[89][89][7];

   Tree->SetBranchAddress("HydjetEntry", &HydjetEntry);
   Tree->SetBranchAddress("PythiaEntry", &PythiaEntry);
   Tree->SetBranchAddress("AllJetCount", &AllJetCount);
   Tree->SetBranchAddress("JetCount", &JetCount);
   Tree->SetBranchAddress("JetIndex", &JetIndex);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("Images", &Images);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet Images");

   int Count = 0;
   TH2D HAverageCETSignal("HAverageCETSignal", "Signal charged ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
   TH2D HAverageNETSignal("HAverageNETSignal", "Signal neutral ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
   TH2D HAverageCETBackground("HAverageCETBackground", "Background charged ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
   TH2D HAverageNETBackground("HAverageNETBackground", "Background neutral ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);

   HAverageCETSignal.SetStats(0);
   HAverageNETSignal.SetStats(0);
   HAverageCETBackground.SetStats(0);
   HAverageNETBackground.SetStats(0);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.08);
   Latex.SetTextAlign(12);

   int EntryCount = Tree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(JetPT < MinJetPT)
         continue;

      TH2D HCPTSignal("HCPTSignal", "Signal charged PT;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HCETSignal("HCETSignal", "Signal charged ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HNETSignal("HNETSignal", "Signal neutral ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HCPTBackground("HCPTBackground", "Background charged PT;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HCETBackground("HCETBackground", "Background charged ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HNETBackground("HNETBackground", "Background neutral ET;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);
      TH2D HRhoA("HRhoA", "#rho #times A;Eta Bin;Phi Bin", 89, 0, 89, 89, 0, 89);

      HCPTSignal.SetStats(0);
      HCETSignal.SetStats(0);
      HNETSignal.SetStats(0);
      HCPTBackground.SetStats(0);
      HCETBackground.SetStats(0);
      HNETBackground.SetStats(0);
      HRhoA.SetStats(0);

      Count = Count + 1;
      for(int i = 0; i < 89; i++)
      {
         for(int j = 0; j < 89; j++)
         {
            HCPTSignal.SetBinContent(i + 1, j + 1, Images[i][j][0]);
            HCETSignal.SetBinContent(i + 1, j + 1, Images[i][j][1]);
            HNETSignal.SetBinContent(i + 1, j + 1, Images[i][j][2]);
            HCPTBackground.SetBinContent(i + 1, j + 1, Images[i][j][3]);
            HCETBackground.SetBinContent(i + 1, j + 1, Images[i][j][4]);
            HNETBackground.SetBinContent(i + 1, j + 1, Images[i][j][5]);
            HRhoA.SetBinContent(i + 1, j + 1, Images[i][j][6]);
            
            HAverageCETSignal.Fill(i + 0.5, j + 0.5, Images[i][j][1]);
            HAverageNETSignal.Fill(i + 0.5, j + 0.5, Images[i][j][2]);
            HAverageCETBackground.Fill(i + 0.5, j + 0.5, Images[i][j][4]);
            HAverageNETBackground.Fill(i + 0.5, j + 0.5, Images[i][j][5]);
         }
      }

      if(MaxCount > 0 && Count > MaxCount)
         continue;

      double Minimum = 0, Maximum = 0;
      Maximum = max(Maximum, HCPTSignal.GetMaximum());
      Maximum = max(Maximum, HCETSignal.GetMaximum());
      Maximum = max(Maximum, HNETSignal.GetMaximum());
      Maximum = max(Maximum, HCPTBackground.GetMaximum());
      Maximum = max(Maximum, HCETBackground.GetMaximum());
      Maximum = max(Maximum, HNETBackground.GetMaximum());
      HCPTSignal.SetMaximum(Maximum);
      HCETSignal.SetMaximum(Maximum);
      HNETSignal.SetMaximum(Maximum);
      HCPTBackground.SetMaximum(Maximum);
      HCETBackground.SetMaximum(Maximum);
      HNETBackground.SetMaximum(Maximum);
      HCPTSignal.SetMinimum(Minimum);
      HCETSignal.SetMinimum(Minimum);
      HNETSignal.SetMinimum(Minimum);
      HCPTBackground.SetMinimum(Minimum);
      HCETBackground.SetMinimum(Minimum);
      HNETBackground.SetMinimum(Minimum);

      TCanvas Canvas;
      Canvas.Divide(3, 3);

      Canvas.cd(1);
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 0, "Event Information");
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 1, "");
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 2, Form("Hydjet entry = %d", HydjetEntry));
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 3, Form("Pythia entry = %d", PythiaEntry));
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 4, Form("Jet count = (%d, %d)", AllJetCount, JetCount));
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 5, Form("Jet entry = %d", JetIndex));
      
      Canvas.cd(2);
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 0, Form("Jet PT = %.2f", JetPT));
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 1, Form("Jet Eta = %.2f", JetEta));
      Latex.DrawLatex(TextLeft, TextTop - TextHeight * 2, Form("Jet Phi = %.2f", JetPhi));

      Canvas.cd(3);
      HRhoA.Draw("colz");

      Canvas.cd(4);
      Canvas.cd(4)->SetGridx();
      Canvas.cd(4)->SetGridy();
      HCPTSignal.Draw("colz");
      Canvas.cd(5);
      Canvas.cd(5)->SetGridx();
      Canvas.cd(5)->SetGridy();
      HCETSignal.Draw("colz");
      Canvas.cd(6);
      Canvas.cd(6)->SetGridx();
      Canvas.cd(6)->SetGridy();
      HNETSignal.Draw("colz");
      
      Canvas.cd(7);
      Canvas.cd(7)->SetGridx();
      Canvas.cd(7)->SetGridy();
      HCPTBackground.Draw("colz");
      Canvas.cd(8);
      Canvas.cd(8)->SetGridx();
      Canvas.cd(8)->SetGridy();
      HCETBackground.Draw("colz");
      Canvas.cd(9);
      Canvas.cd(9)->SetGridx();
      Canvas.cd(9)->SetGridy();
      HNETBackground.Draw("colz");

      PdfFile.AddCanvas(Canvas);
   }

   HAverageCETSignal.Scale(double(1) / Count);
   HAverageNETSignal.Scale(double(1) / Count);
   HAverageCETBackground.Scale(double(1) / Count);
   HAverageNETBackground.Scale(double(1) / Count);

   TCanvas Canvas;

   Canvas.Divide(2, 2);

   Canvas.cd(1);
   Canvas.cd(1)->SetGridx();
   Canvas.cd(1)->SetGridy();
   HAverageCETSignal.Draw("colz");
   Canvas.cd(2);
   Canvas.cd(2)->SetGridx();
   Canvas.cd(2)->SetGridy();
   HAverageNETSignal.Draw("colz");
   Canvas.cd(3);
   Canvas.cd(3)->SetGridx();
   Canvas.cd(3)->SetGridy();
   HAverageCETBackground.Draw("colz");
   Canvas.cd(4);
   Canvas.cd(4)->SetGridx();
   Canvas.cd(4)->SetGridy();
   HAverageNETBackground.Draw("colz");

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   InputFile.Close();

   return 0;
}





