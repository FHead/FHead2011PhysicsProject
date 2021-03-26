#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"
#include "CustomAssert.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
void DoEtaScan(PdfFileHelper &PdfFile, DataHelper &DHFile, TTree *Tree);
void DoCentralityScan(PdfFileHelper &PdfFile, DataHelper &DHFile, TTree *Tree);
void FitWidth(PdfFileHelper &PdfFile, DataHelper &DHFile, string State, TTree *Tree, string Plot,
   double EtaMin, double EtaMax, double CMin, double CMax,
   int NBin = 200, double Min = -80, double Max = 200);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string InputFileName = CL.Get("input");
   string VerboseOutputFileName = CL.Get("output", "RandomConePlotDump.pdf");
   string DHFileName = CL.Get("dhfile", "Fits.dh");

   PdfFileHelper PlotDumpFile(VerboseOutputFileName);
   PlotDumpFile.AddTextPage("Random cone plots: dump");

   DataHelper DHFile(DHFileName);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("RandomConeTree");
   Assert(Tree != nullptr, "Input tree not found!");

   DoEtaScan(PlotDumpFile, DHFile, Tree);
   DHFile.SaveToFile(DHFileName);
   
   // DoCentralityScan(PlotDumpFile, DHFile, Tree);
   // DHFile.SaveToFile(DHFileName);

   File.Close();

   PlotDumpFile.AddTimeStampPage();
   PlotDumpFile.Close();

   return 0;
}

void DoEtaScan(PdfFileHelper &PdfFile, DataHelper &DHFile, TTree *Tree)
{
   vector<double> Radius = {0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   vector<double> CBins = {0.0, 0.1, 0.3, 0.5, 0.8};
   vector<double> EtaBins = {0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90,
      1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90,
      2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00};

   for(int iC = 0; iC + 1 < (int)CBins.size(); iC++)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         cout << "Eta scan iC = " << iC << ", iR = " << iR << endl;
         
         string RString = Form("%03d", int(Radius[iR] * 100));

         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            string State = Form("RhoEta_R%d_C%d_Eta%d", iR, iC, iEta);
            FitWidth(PdfFile, DHFile, State, Tree,
               Form("R%sSum-Rho%sSum", RString.c_str(), RString.c_str()),
               EtaBins[iEta], EtaBins[iEta+1], CBins[iC], CBins[iC+1]);
            
            State = Form("RhoPhiEta_R%d_C%d_Eta%d", iR, iC, iEta);
            FitWidth(PdfFile, DHFile, State, Tree,
               Form("R%sSum-RhoPhi%sSum", RString.c_str(), RString.c_str()),
               EtaBins[iEta], EtaBins[iEta+1], CBins[iC], CBins[iC+1]);
         }
      }
   }
}

void DoCentralityScan(PdfFileHelper &PdfFile, DataHelper &DHFile, TTree *Tree)
{
   vector<double> Radius = {0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   vector<double> CBins(101);
   vector<double> EtaBins = {0.00, 0.70, 1.30, 1.70, 2.00, 2.25, 2.50, 2.75, 3.00};

   for(int iC = 0; iC < (int)CBins.size(); iC++)
      CBins[iC] = iC * 0.1;

   for(int iC = 0; iC + 1 < (int)CBins.size(); iC++)
   {
      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         cout << "Centrality scan iC = " << iC << ", iR = " << iR << endl;
      
         string RString = Form("%03d", int(Radius[iR] * 100));

         for(int iEta = 0; iEta + 1 < (int)EtaBins.size(); iEta++)
         {
            string State = Form("RhoCentrality_R%d_C%d_Eta%d", iR, iC, iEta);
            FitWidth(PdfFile, DHFile, State, Tree,
               Form("R%sSum-Rho%sSum", RString.c_str(), RString.c_str()),
               EtaBins[iEta], EtaBins[iEta+1], CBins[iC], CBins[iC+1]);
            
            State = Form("RhoPhiCentrality_R%d_C%d_Eta%d", iR, iC, iEta);
            FitWidth(PdfFile, DHFile, State, Tree,
               Form("R%sSum-RhoPhi%sSum", RString.c_str(), RString.c_str()),
               EtaBins[iEta], EtaBins[iEta+1], CBins[iC], CBins[iC+1]);
         }
      }
   }
}

void FitWidth(PdfFileHelper &PdfFile, DataHelper &DHFile, string State,
   TTree *Tree, string Plot, double EtaMin, double EtaMax, double CMin, double CMax,
   int NBin, double Min, double Max)
{
   if(Tree == nullptr)
      return;

   string CutA = Form("Centrality > %.2f && Centrality <= %.2f", CMin, CMax);
   string CutB = Form("abs(Eta) > %.3f && abs(Eta) < %.3f", EtaMin, EtaMax);
   string Cut = CutA + " && " + CutB;

   int NEntry = Tree->GetEntries();

   PdfFile.AddTextPage({"Fit for", Plot, CutA, CutB, Form("%d, [%.1f, %.1f]", NBin, Min, Max)});

   TH1D H("H", Plot.c_str(), NBin, Min, Max);
   Tree->Draw(Form("%s>>H", Plot.c_str()), Cut.c_str(), "", NEntry);

   PdfFile.AddPlot(H, "", false);

   TF1 F("F", "gaus", Min, 0);
   H.Fit(&F, "Q", "", Min, 0);
   
   double RangeMin = F.GetParameter(1) - 5 * F.GetParameter(2);
   double RangeMax = F.GetParameter(1) + 10 * F.GetParameter(2);
   double BinWidth = (RangeMax - RangeMin) / NBin;
   
   TH1D H2("H2", Plot.c_str(), NBin, RangeMin, RangeMax);
   Tree->Draw(Form("%s>>H2", Plot.c_str()), Cut.c_str(), "", NEntry);
   
   double FitMin = F.GetParameter(1) - 5 * F.GetParameter(2);
   double FitMax = F.GetParameter(2);
   H2.Fit(&F, "Q", "", FitMin, FitMax);
   FitMax = F.GetParameter(2);
   H2.Fit(&F, "Q", "", FitMin, FitMax);
   FitMax = F.GetParameter(2);
   H2.Fit(&F, "Q", "", FitMin, FitMax);
   
   PdfFile.AddPlot(H2, "", true);

   DHFile[State]["Plot"] = Plot;
   DHFile[State]["Cut"] = Cut;
   DHFile[State]["FitMin"] = FitMin;
   DHFile[State]["FitMax"] = FitMax;
   DHFile[State]["RangeMin"] = RangeMin;
   DHFile[State]["RangeMax"] = RangeMax;
   DHFile[State]["EtaMin"] = EtaMin;
   DHFile[State]["EtaMax"] = EtaMax;
   DHFile[State]["CentralityMin"] = CMin;
   DHFile[State]["CentralityMax"] = CMax;
   DHFile[State]["NBin"] = NBin;
   DHFile[State]["P0"] = F.GetParameter(0);
   DHFile[State]["P1"] = F.GetParameter(1);
   DHFile[State]["P2"] = F.GetParameter(2);
   DHFile[State]["P0Error"] = F.GetParError(0);
   DHFile[State]["P1Error"] = F.GetParError(1);
   DHFile[State]["P2Error"] = F.GetParError(2);
   DHFile[State]["Chi2"] = F.GetChisquare();
   DHFile[State]["Ndof"] = (FitMax - FitMin) / BinWidth - 3;

   return;
}




