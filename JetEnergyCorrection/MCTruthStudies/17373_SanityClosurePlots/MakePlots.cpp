#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TFitResult.h"

#include "PlotHelper3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);
void MakeHistograms(map<string, TH1 *> &H1, map<string, TH2 *> &H2,
   vector<double> CEtaBins, vector<double> CPTBins);
void DeleteHistograms(map<string, TH1 *> &H1, map<string, TH2 *> &H2);
int GetBin(double Value, const vector<double> &Bins);
void TranscribeFit(TH2 *Hist, TGraphAsymmErrors *Graph);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output", "ClosurePlots.pdf");
   string InputTree = CL.Get("tree", "Tree");
   double Fraction = CL.GetDouble("fraction", 1.0);

   // Binnings
   double CEtaBinsArray[] = {-5.191, -4.191, -3.314, -2.853, -2.500,
      -1.930, -1.479, -1.044, -0.522, 0.000,
      0.522, 1.044, 1.479, 1.930, 2.500, 2.853, 3.314, 4.191, 5.191};
   vector<double> CEtaBins(CEtaBinsArray, CEtaBinsArray + 19);

   double CPTBinsArray[] = {20, 40, 70, 120, 200, 500, 1000, 6000};
   vector<double> CPTBins(CPTBinsArray, CPTBinsArray + 8);

   // Prepare inputs
   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get(InputTree.c_str());

   if(Tree == NULL)
      return -1;

   float Rho, GenPT, GenEta, GenPhi, JetPT, JetEta, JetPhi, JetPTL1, JetPTL123, JetArea;
   Tree->SetBranchAddress("Rho", &Rho);
   Tree->SetBranchAddress("GenPT", &GenPT);
   Tree->SetBranchAddress("GenEta", &GenEta);
   Tree->SetBranchAddress("GenPhi", &GenPhi);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetPTL1", &JetPTL1);
   Tree->SetBranchAddress("JetPTL123", &JetPTL123);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("JetArea", &JetArea);

   // Prepare histograms
   map<string, TH1 *> H1;
   map<string, TH2 *> H2;
   MakeHistograms(H1, H2, CEtaBins, CPTBins);

   // Prepare outputs
   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Sanity Check for MC Truth");

   // Loop over all entries and fill histograms
   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);

   int Mod = EntryCount / 300;
   if(Mod < 1)   Mod = 1;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Bar.Update(iE);
      Bar.PrintWithMod(Mod);

      if(GenPT <= 1e-10)   // dafuq
         continue;

      int CPTBin = GetBin(GenPT, CPTBins);
      int CEtaBin = GetBin(GenEta, CEtaBins);

      string Title;
      
      Title = Form("HResponseVsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(Rho, JetPT / GenPT);
      Title = Form("HResponseL1VsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(Rho, JetPTL1 / GenPT);
      Title = Form("HResponseL123VsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(Rho, JetPTL123 / GenPT);
      
      Title = Form("PResponseVsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(Rho, JetPT / GenPT);
      Title = Form("PResponseL1VsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(Rho, JetPTL1 / GenPT);
      Title = Form("PResponseL123VsRho_CEtaBin%d_CPTBin%d", CEtaBin, CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(Rho, JetPTL123 / GenPT);
      
      Title = Form("HResponseVsEta_CPTBin%d", CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenEta, JetPT / GenPT);
      Title = Form("HResponseL1VsEta_CPTBin%d", CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenEta, JetPTL1 / GenPT);
      Title = Form("HResponseL123VsEta_CPTBin%d", CPTBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenEta, JetPTL123 / GenPT);
      
      Title = Form("PResponseVsEta_CPTBin%d", CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenEta, JetPT / GenPT);
      Title = Form("PResponseL1VsEta_CPTBin%d", CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenEta, JetPTL1 / GenPT);
      Title = Form("PResponseL123VsEta_CPTBin%d", CPTBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenEta, JetPTL123 / GenPT);
         
      Title = Form("HResponseVsPT_CEtaBin%d", CEtaBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenPT, JetPT / GenPT);
      Title = Form("HResponseL1VsPT_CEtaBin%d", CEtaBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenPT, JetPTL1 / GenPT);
      Title = Form("HResponseL123VsPT_CEtaBin%d", CEtaBin);
      if(H2.find(Title) != H2.end())   H2[Title]->Fill(GenPT, JetPTL123 / GenPT);
      
      Title = Form("PResponseVsPT_CEtaBin%d", CEtaBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenPT, JetPT / GenPT);
      Title = Form("PResponseL1VsPT_CEtaBin%d", CEtaBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenPT, JetPTL1 / GenPT);
      Title = Form("PResponseL123VsPT_CEtaBin%d", CEtaBin);
      if(H1.find(Title) != H1.end())   H1[Title]->Fill(GenPT, JetPTL123 / GenPT);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   // Writing histograms to output
   PdfFile.AddTextPage("Response vs rho");

   TGraph GLine;
   GLine.SetPoint(0, -10000, 1);
   GLine.SetPoint(1, 10000, 1);
   GLine.SetPoint(2, 10000, 1.05);
   GLine.SetPoint(3, -10000, 1.05);
   GLine.SetPoint(4, -10000, 0.95);
   GLine.SetPoint(5, 10000, 0.95);
 
   for(int iEta = 0; iEta + 1 < CEtaBins.size(); iEta++)
   {
      for(int iPT = 0; iPT + 1 < CPTBins.size(); iPT++)
      {
         TGraphAsymmErrors G1, G2, G3;
         G1.SetLineColor(kMagenta);
         G1.SetMarkerColor(kMagenta);
         G1.SetMarkerStyle(26);
         G2.SetLineColor(kMagenta);
         G2.SetMarkerColor(kMagenta);
         G2.SetMarkerStyle(26);
         G3.SetLineColor(kMagenta);
         G3.SetMarkerColor(kMagenta);
         G3.SetMarkerStyle(26);

         TCanvas Canvas1;
         Canvas1.Divide(1, 3);

         string Title;

         Canvas1.cd(1);
         Title = Form("HResponseVsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         TranscribeFit(H2[Title], &G1);
         H2[Title]->Draw("colz");
         G1.Draw("p");
         Title = Form("PResponseVsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->Draw("same");
         
         Canvas1.cd(2);
         Title = Form("HResponseL1VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         TranscribeFit(H2[Title], &G2);
         H2[Title]->Draw("colz");
         G2.Draw("p");
         Title = Form("PResponseL1VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->Draw("same");

         Canvas1.cd(3);
         Title = Form("HResponseL123VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         TranscribeFit(H2[Title], &G3);
         H2[Title]->Draw("colz");
         G3.Draw("p");
         Title = Form("PResponseL123VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->Draw("same");

         PdfFile.AddCanvas(Canvas1);

         TCanvas Canvas2;
         
         TLegend Legend1(0.2, 0.8, 0.5, 0.6);
         Legend1.SetTextFont(42);
         Legend1.SetTextSize(0.035);
         Legend1.SetBorderSize(0);
         Legend1.SetFillStyle(0);
         TLegend Legend2(0.45, 0.8, 0.75, 0.6);
         Legend2.SetTextFont(42);
         Legend2.SetTextSize(0.035);
         Legend2.SetBorderSize(0);
         Legend2.SetFillStyle(0);
         
         TH2D HWorld("HWorld", ";Rho;Response", 100, 0, 70, 100, 0, 2);
         HWorld.SetStats(0);
         HWorld.Draw("axis");

         GLine.Draw("l");

         Title = Form("PResponseVsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->Draw("same");
         G1.Draw("p");
         Legend1.AddEntry(H1[Title], "Raw PT", "lp");
         Legend2.AddEntry(&G1, "Fitted Raw PT", "lp");
         HWorld.SetTitle(H1[Title]->GetTitle());

         Title = Form("PResponseL1VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->SetLineColor(kBlack);
         H1[Title]->SetMarkerColor(kBlack);
         H1[Title]->Draw("same");
         G2.SetLineColor(kBlack);
         G2.SetMarkerColor(kBlack);
         G2.Draw("p");
         Legend1.AddEntry(H1[Title], "L1", "lp");
         Legend2.AddEntry(&G2, "Fitted L1", "lp");
         
         Title = Form("PResponseL123VsRho_CEtaBin%d_CPTBin%d", iEta + 1, iPT + 1);
         H1[Title]->SetLineColor(kBlue);
         H1[Title]->SetMarkerColor(kBlue);
         H1[Title]->Draw("same");
         G3.SetLineColor(kBlue);
         G3.SetMarkerColor(kBlue);
         G3.Draw("p");
         Legend1.AddEntry(H1[Title], "L1 + L2L3", "lp");
         Legend2.AddEntry(&G3, "Fitted L1 + L2L3", "lp");

         Legend1.Draw();
         Legend2.Draw();

         PdfFile.AddCanvas(Canvas2);

         HWorld.GetYaxis()->SetRangeUser(0.8, 1.2);
         
         PdfFile.AddCanvas(Canvas2);
      }
   }

   PdfFile.AddTextPage("Response Vs eta");

   for(int iPT = 0; iPT + 1 < CPTBins.size(); iPT++)
   {
      TGraphAsymmErrors G1, G2, G3;
      G1.SetLineColor(kMagenta);
      G1.SetMarkerColor(kMagenta);
      G1.SetMarkerStyle(26);
      G2.SetLineColor(kMagenta);
      G2.SetMarkerColor(kMagenta);
      G2.SetMarkerStyle(26);
      G3.SetLineColor(kMagenta);
      G3.SetMarkerColor(kMagenta);
      G3.SetMarkerStyle(26);

      TCanvas Canvas1;
      Canvas1.Divide(1, 3);

      string Title;

      Canvas1.cd(1);
      Title = Form("HResponseVsEta_CPTBin%d", iPT + 1);
      TranscribeFit(H2[Title], &G1);
      H2[Title]->Draw("colz");
      G1.Draw("p");
      Title = Form("PResponseVsEta_CPTBin%d", iPT + 1);
      H1[Title]->Draw("same");

      Canvas1.cd(2);
      Title = Form("HResponseL1VsEta_CPTBin%d", iPT + 1);
      TranscribeFit(H2[Title], &G2);
      H2[Title]->Draw("colz");
      G2.Draw("p");
      Title = Form("PResponseL1VsEta_CPTBin%d", iPT + 1);
      H1[Title]->Draw("same");

      Canvas1.cd(3);
      Title = Form("HResponseL123VsEta_CPTBin%d", iPT + 1);
      TranscribeFit(H2[Title], &G3);
      H2[Title]->Draw("colz");
      G3.Draw("p");
      Title = Form("PResponseL123VsEta_CPTBin%d", iPT + 1);
      H1[Title]->Draw("same");

      PdfFile.AddCanvas(Canvas1);

      TCanvas Canvas2;
      
      TLegend Legend1(0.2, 0.8, 0.5, 0.6);
      Legend1.SetTextFont(42);
      Legend1.SetTextSize(0.035);
      Legend1.SetBorderSize(0);
      Legend1.SetFillStyle(0);
      TLegend Legend2(0.45, 0.8, 0.75, 0.6);
      Legend2.SetTextFont(42);
      Legend2.SetTextSize(0.035);
      Legend2.SetBorderSize(0);
      Legend2.SetFillStyle(0);
      
      TH2D HWorld("HWorld", ";Jet Eta;Response", 100, -5.2, 5.2, 100, 0, 2);
      HWorld.SetStats(0);
      HWorld.Draw("axis");

      GLine.Draw("l");

      Title = Form("PResponseVsEta_CPTBin%d", iPT + 1);
      H1[Title]->Draw("same");
      G1.Draw("p");
      Legend1.AddEntry(H1[Title], "Raw PT", "lp");
      Legend2.AddEntry(&G1, "Fitted Raw PT", "lp");
      HWorld.SetTitle(H1[Title]->GetTitle());

      Title = Form("PResponseL1VsEta_CPTBin%d", iPT + 1);
      H1[Title]->SetLineColor(kBlack);
      H1[Title]->SetMarkerColor(kBlack);
      H1[Title]->Draw("same");
      G2.SetLineColor(kBlack);
      G2.SetMarkerColor(kBlack);
      G2.Draw("p");
      Legend1.AddEntry(H1[Title], "L1", "lp");
      Legend2.AddEntry(&G2, "Fitted L1", "lp");
      
      Title = Form("PResponseL123VsEta_CPTBin%d", iPT + 1);
      H1[Title]->SetLineColor(kBlue);
      H1[Title]->SetMarkerColor(kBlue);
      H1[Title]->Draw("same");
      G3.SetLineColor(kBlue);
      G3.SetMarkerColor(kBlue);
      G3.Draw("p");
      Legend1.AddEntry(H1[Title], "L1 + L2L3", "lp");
      Legend2.AddEntry(&G3, "Fitted L1 + L2L3", "lp");

      Legend1.Draw();
      Legend2.Draw();

      PdfFile.AddCanvas(Canvas2);

      HWorld.GetYaxis()->SetRangeUser(0.8, 1.2);
      
      PdfFile.AddCanvas(Canvas2);
   }
   
   PdfFile.AddTextPage("Response vs PT");

   for(int iEta = 0; iEta + 1 < CEtaBins.size(); iEta++)
   {
      TGraphAsymmErrors G1, G2, G3;
      G1.SetLineColor(kMagenta);
      G1.SetMarkerColor(kMagenta);
      G1.SetMarkerStyle(26);
      G2.SetLineColor(kMagenta);
      G2.SetMarkerColor(kMagenta);
      G2.SetMarkerStyle(26);
      G3.SetLineColor(kMagenta);
      G3.SetMarkerColor(kMagenta);
      G3.SetMarkerStyle(26);

      TCanvas Canvas1;
      Canvas1.Divide(1, 3);

      string Title;

      Canvas1.cd(1);
      Canvas1.cd(1)->SetLogx();
      Title = Form("HResponseVsPT_CEtaBin%d", iEta + 1);
      TranscribeFit(H2[Title], &G1);
      H2[Title]->Draw("colz");
      G1.Draw("p");
      Title = Form("PResponseVsPT_CEtaBin%d", iEta + 1);
      H1[Title]->Draw("same");
      
      Canvas1.cd(2);
      Canvas1.cd(2)->SetLogx();
      Title = Form("HResponseL1VsPT_CEtaBin%d", iEta + 1);
      TranscribeFit(H2[Title], &G2);
      H2[Title]->Draw("colz");
      G2.Draw("p");
      Title = Form("PResponseL1VsPT_CEtaBin%d", iEta + 1);
      H1[Title]->Draw("same");

      Canvas1.cd(3);
      Canvas1.cd(3)->SetLogx();
      Title = Form("HResponseL123VsPT_CEtaBin%d", iEta + 1);
      TranscribeFit(H2[Title], &G3);
      H2[Title]->Draw("colz");
      G3.Draw("p");
      Title = Form("PResponseL123VsPT_CEtaBin%d", iEta + 1);
      H1[Title]->Draw("same");

      PdfFile.AddCanvas(Canvas1);

      TCanvas Canvas2;
      Canvas2.SetLogx();
      
      TLegend Legend1(0.2, 0.8, 0.5, 0.6);
      Legend1.SetTextFont(42);
      Legend1.SetTextSize(0.035);
      Legend1.SetBorderSize(0);
      Legend1.SetFillStyle(0);
      TLegend Legend2(0.45, 0.8, 0.75, 0.6);
      Legend2.SetTextFont(42);
      Legend2.SetTextSize(0.035);
      Legend2.SetBorderSize(0);
      Legend2.SetFillStyle(0);
      
      TH2D HWorld("HWorld", ";Gen PT;Response", 100, 20, 1000, 100, 0, 2);
      HWorld.SetStats(0);
      HWorld.Draw("axis");

      GLine.Draw("l");

      Title = Form("PResponseVsPT_CEtaBin%d", iEta + 1);
      H1[Title]->Draw("same");
      G1.Draw("p");
      Legend1.AddEntry(H1[Title], "Raw PT", "lp");
      Legend2.AddEntry(&G1, "Fitted Raw PT", "lp");
      HWorld.SetTitle(H1[Title]->GetTitle());

      Title = Form("PResponseL1VsPT_CEtaBin%d", iEta + 1);
      H1[Title]->SetLineColor(kBlack);
      H1[Title]->SetMarkerColor(kBlack);
      H1[Title]->Draw("same");
      G2.SetLineColor(kBlack);
      G2.SetMarkerColor(kBlack);
      G2.Draw("p");
      Legend1.AddEntry(H1[Title], "L1", "lp");
      Legend2.AddEntry(&G2, "Fitted L1", "lp");
      
      Title = Form("PResponseL123VsPT_CEtaBin%d", iEta + 1);
      H1[Title]->SetLineColor(kBlue);
      H1[Title]->SetMarkerColor(kBlue);
      H1[Title]->Draw("same");
      G3.SetLineColor(kBlue);
      G3.SetMarkerColor(kBlue);
      G3.Draw("p");
      Legend1.AddEntry(H1[Title], "L1 + L2L3", "lp");
      Legend2.AddEntry(&G3, "Fitted L1 + L2L3", "lp");

      Legend1.Draw();
      Legend2.Draw();

      PdfFile.AddCanvas(Canvas2);

      HWorld.GetYaxis()->SetRangeUser(0.8, 1.2);
      
      PdfFile.AddCanvas(Canvas2);
   }
   

   // Wrapping up stuff
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   DeleteHistograms(H1, H2);

   InputFile.Close();

   return 0;
}

void MakeHistograms(map<string, TH1 *> &H1, map<string, TH2 *> &H2,
   vector<double> CEtaBins, vector<double> CPTBins)
{
   int EtaBinCount = 82;
   double EtaBins[] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314,
      -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -2.043, -1.930, -1.830, -1.740, -1.653, -1.566,
      -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435,
      -0.348, -0.261, -0.174, -0.087, 0.000,
      5.191, 4.889, 4.716, 4.538, 4.363, 4.191, 4.013, 3.839, 3.664, 3.489, 3.314,
      3.139, 2.964, 2.853, 2.650, 2.500, 2.322, 2.172, 2.043, 1.930, 1.830, 1.740, 1.653, 1.566,
      1.479, 1.392, 1.305, 1.218, 1.131, 1.044, 0.957, 0.879, 0.783, 0.696, 0.609, 0.522, 0.435,
      0.348, 0.261, 0.174, 0.087};
   sort(EtaBins, EtaBins + 83);

   int PTBinCount = 50;
   double PTBinMin = 20;
   double PTBinMax = 1000;
   double PTBins[51];
   for(int i = 0; i <= PTBinCount; i++)
      PTBins[i] = PTBinMin * pow(PTBinMax / PTBinMin, double(i) / PTBinCount);

   int RhoBinCount = 70;
   double RhoMin = 0;
   double RhoMax = 70;
   int ResponseBinCount = 100;
   double ResponseMin = 0;
   double ResponseMax = 2;

   double TitleSize2D = 0.06;
   double TitleOffset2D = 0.8;
   double LabelSize2D = 0.06;

   for(int iE = 0; iE < (int)CEtaBins.size(); iE++)
   {
      for(int iPT = 0; iPT < (int)CPTBins.size(); iPT++)
      {
         string Name, Title;

         Name = Form("HResponseVsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho     ;Response (Raw)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H2.insert(pair<string, TH2 *>(Name.c_str(),
            new TH2D(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax,
               ResponseBinCount, ResponseMin, ResponseMax)));
         H2[Name]->SetStats(0);
         H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
         H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

         Name = Form("HResponseL1VsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho     ;Response (L1)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H2.insert(pair<string, TH2 *>(Name.c_str(),
            new TH2D(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax,
               ResponseBinCount, ResponseMin, ResponseMax)));
         H2[Name]->SetStats(0);
         H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
         H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

         Name = Form("HResponseL123VsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho     ;Response (L1+L2L3)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H2.insert(pair<string, TH2 *>(Name.c_str(),
            new TH2D(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax,
               ResponseBinCount, ResponseMin, ResponseMax)));
         H2[Name]->SetStats(0);
         H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
         H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
         H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
         H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

         Name = Form("PResponseVsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho;Response (Raw)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H1.insert(pair<string, TH1 *>(Name.c_str(),
            new TProfile(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax)));
         H1[Name]->SetStats(0);
         H1[Name]->SetLineColor(kMagenta);
         H1[Name]->SetMarkerColor(kMagenta);
         H1[Name]->SetMarkerStyle(20);

         Name = Form("PResponseL1VsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho;Response (L1)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H1.insert(pair<string, TH1 *>(Name.c_str(),
            new TProfile(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax)));
         H1[Name]->SetStats(0);
         H1[Name]->SetLineColor(kMagenta);
         H1[Name]->SetMarkerColor(kMagenta);
         H1[Name]->SetMarkerStyle(20);

         Name = Form("PResponseL123VsRho_CEtaBin%d_CPTBin%d", iE + 1, iPT + 1);
         Title = Form("JetPT/GenPT, Eta = %.3f-%.3f, PT = %.0f-%.0f;Rho;Response (L1+L2L3)",
            CEtaBins[iE], CEtaBins[iE+1], CPTBins[iPT], CPTBins[iPT+1]);
         H1.insert(pair<string, TH1 *>(Name.c_str(),
            new TProfile(Name.c_str(), Title.c_str(),
               RhoBinCount, RhoMin, RhoMax)));
         H1[Name]->SetStats(0);
         H1[Name]->SetLineColor(kMagenta);
         H1[Name]->SetMarkerColor(kMagenta);
         H1[Name]->SetMarkerStyle(20);
      }
   }
   
   for(int iPT = 0; iPT < (int)CPTBins.size(); iPT++)
   {
      string Name, Title;

      Name = Form("HResponseVsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (Raw)", CPTBins[iPT], CPTBins[iPT+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(),
            EtaBinCount, EtaBins,
            ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("HResponseL1VsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (L1)", CPTBins[iPT], CPTBins[iPT+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(),
            EtaBinCount, EtaBins,
            ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("HResponseL123VsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (L1+L2L3)", CPTBins[iPT], CPTBins[iPT+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(),
            EtaBinCount, EtaBins,
            ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("PResponseVsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (Raw)", CPTBins[iPT], CPTBins[iPT+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), EtaBinCount, EtaBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);

      Name = Form("PResponseL1VsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (L1)", CPTBins[iPT], CPTBins[iPT+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), EtaBinCount, EtaBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);

      Name = Form("PResponseL123VsEta_CPTBin%d", iPT + 1);
      Title = Form("JetPT/GenPT, PT = %.0f-%.0f;Eta;Response (L1+L2L3)", CPTBins[iPT], CPTBins[iPT+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), EtaBinCount, EtaBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);
   }

   for(int iEta = 0; iEta < (int)CEtaBins.size(); iEta++)
   {
      string Name, Title;

      Name = Form("HResponseVsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT     ;Response (Raw)",
         CEtaBins[iEta], CEtaBins[iEta+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(), PTBinCount, PTBins, ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("HResponseL1VsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT     ;Response (L1)",
         CEtaBins[iEta], CEtaBins[iEta+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(), PTBinCount, PTBins, ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("HResponseL123VsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT     ;Response (L1+L2L3)",
         CEtaBins[iEta], CEtaBins[iEta+1]);
      H2.insert(pair<string, TH2 *>(Name.c_str(),
         new TH2D(Name.c_str(), Title.c_str(), PTBinCount, PTBins, ResponseBinCount, ResponseMin, ResponseMax)));
      H2[Name]->SetStats(0);
      H2[Name]->GetXaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetYaxis()->SetTitleSize(TitleSize2D);
      H2[Name]->GetXaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetYaxis()->SetTitleOffset(TitleOffset2D);
      H2[Name]->GetXaxis()->SetLabelSize(LabelSize2D);
      H2[Name]->GetYaxis()->SetLabelSize(LabelSize2D);

      Name = Form("PResponseVsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT;Response (Raw)", CEtaBins[iEta], CEtaBins[iEta+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), PTBinCount, PTBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);

      Name = Form("PResponseL1VsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT;Response (L1)", CEtaBins[iEta], CEtaBins[iEta+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), PTBinCount, PTBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);

      Name = Form("PResponseL123VsPT_CEtaBin%d", iEta + 1);
      Title = Form("JetPT/GenPT, Eta = %.3f-%.3f;PT;Response (L1+L2L3)", CEtaBins[iEta], CEtaBins[iEta+1]);
      H1.insert(pair<string, TH1 *>(Name.c_str(),
         new TProfile(Name.c_str(), Title.c_str(), PTBinCount, PTBins)));
      H1[Name]->SetStats(0);
      H1[Name]->SetLineColor(kMagenta);
      H1[Name]->SetMarkerColor(kMagenta);
      H1[Name]->SetMarkerStyle(20);
   }
}

void DeleteHistograms(map<string, TH1 *> &H1, map<string, TH2 *> &H2)
{
   for(auto H : H1)
      if(H.second != NULL)
         delete H.second;
   
   for(auto H : H2)
      if(H.second != NULL)
         delete H.second;
}

int GetBin(double Value, const vector<double> &Bins)
{
   if(Bins.size() == 0)
      return 0;
   if(Value < Bins[0])
      return 0;
   for(int i = 0; i + 1 < (int)Bins.size(); i++)
      if(Value >= Bins[i] && Value < Bins[i+1])
         return i + 1;
   return Bins.size();
}

void TranscribeFit(TH2 *Hist, TGraphAsymmErrors *Graph)
{
   if(Hist == NULL || Graph == NULL)
      return;

   int NBinsX = Hist->GetNbinsX();
   int NBinsY = Hist->GetNbinsY();

   Graph->Set(0);

   for(int iX = 1; iX <= NBinsX; iX++)
   {
      double XMin = Hist->GetXaxis()->GetBinLowEdge(iX);
      double XMax = Hist->GetXaxis()->GetBinUpEdge(iX);

      double X = (XMin + XMax) / 2;
      double EX = (XMax - XMin) / 2;

      TH1 *Projection = (TH1 *)Hist->ProjectionY("_py", iX, iX);
      if(Projection == NULL)
         continue;
      if(Projection->Integral() == 0)
         continue;

      TFitResultPtr FitResult = Projection->Fit("gaus", "S", "", 0.2, 1.8);
      if(int(FitResult) != 0)
         continue;

      double Y = FitResult->Parameter(1);
      double EY = FitResult->ParError(1);

      int N = Graph->GetN();
      Graph->SetPoint(N, X, Y);
      Graph->SetPointError(N, EX, EX, EY, EY);

      delete Projection;
   }
}


