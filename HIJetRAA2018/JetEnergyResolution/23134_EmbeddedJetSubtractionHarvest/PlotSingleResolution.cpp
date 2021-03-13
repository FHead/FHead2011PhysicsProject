#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
TGraphAsymmErrors TranscribePTScan(DataHelper &DHFile, string Prefix, int CBin, int EtaBin);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input  = CL.Get("input", "R040_NoPhi.dh");
   string Output = CL.Get("output", "R040_NoPhi.pdf");

   SetThesisStyle();

   DataHelper DHFile(Input);

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Meow");

   TGraphAsymmErrors GPT[4][6];

   for(int iC = 0; iC < 4; iC++)
   {
      for(int iEta = 0; iEta < 6; iEta++)
      {
         GPT[iC][iEta] = TranscribePTScan(DHFile, "PTScan", iC, iEta);
         PdfFile.AddPlot(GPT[iC][iEta], "ap", false, false, false, true);
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

TGraphAsymmErrors TranscribePTScan(DataHelper &DHFile, string Prefix, int CBin, int EtaBin)
{
   TGraphAsymmErrors G;

   G.SetTitle(Form("CBin %d, EtaBin %d", CBin, EtaBin));
   
   vector<string> States = DHFile.GetListOfKeys();
   for(string State : States)
   {
      if(State.find(Prefix + "_") != 0)   // we want the right prefix
         continue;
      if(State.find(Form("Centrality%d", CBin)) == string::npos)   // wrong centrality bin
         continue;
      if(State.find(Form("Eta%d", EtaBin)) == string::npos)   // wrong eta bin
         continue;

      int N = G.GetN();
      double PTMin = DHFile[State]["PTMin"].GetDouble();
      double PTMax = DHFile[State]["PTMax"].GetDouble();

      double Mean = DHFile[State]["Mean"].GetDouble();
      double RMS = DHFile[State]["RMS"].GetDouble();

      G.SetPoint(N, (PTMax + PTMin) / 2, Mean);
      G.SetPointError(N, 0, 0, RMS, RMS);
   }

   G.Sort();

   return G;
}

