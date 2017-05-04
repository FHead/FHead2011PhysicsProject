#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " IsData=(Y|N)" << endl;
      return -1;
   }

   bool IsData = (argv[1][0] == 'Y') ? true : false;

   string FileName = (IsData ? "AADataPrescale.root" : "AA6DijetCymbal.root");
   string OutputFileName = (IsData ? "Resolution.pdf" : "ResolutionMC.pdf");
   string State = (IsData ? "AADataPrescale" : "AA6DijetCymbal");

   SetThesisStyle();

   PdfFileHelper PdfFile(OutputFileName);

   DataHelper DHFile("ResolutionDatabase.dh");

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("T");

   double Min = 100;
   double Max = 200;
   double Spacing = 1;

   TGraph GMean, GRMS;

   for(double X = Min; X < Max; X = X + Spacing)
   {
      cout << "Now running PT = " << X << "-" << X + Spacing << endl;

      TH1D H(Form("H%d", (int)(X * 100)), Form("PT = %.2f-%.2f;PU / CS - 1;a.u.", X, X + Spacing), 100, -1, 1);
      H.SetStats(0);
      H.Sumw2();

      if(IsData == true)
         Tree->Draw(Form("JetPUPT/JetPT-1>>H%d", (int)(X * 100)),
             Form("JetPT > %f && JetPT <= %f && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality < 0.1", X, X + Spacing));
      else
         Tree->Draw(Form("JetPUPT/JetPT-1>>H%d", (int)(X * 100)),
             Form("MCWeight * (JetPT > %f && JetPT <= %f && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality < 0.1)", X, X + Spacing));

      H.Fit("gaus");

      PdfFile.AddPlot(H);

      GMean.SetPoint(GMean.GetN(), X + Spacing / 2, H.GetMean());
      GRMS.SetPoint(GRMS.GetN(), X + Spacing / 2, H.GetRMS());

      string PTString = Form("%d", (int)(X * 100));

      DHFile[State]["Mean"+PTString] = H.GetMean();
      DHFile[State]["RMS"+PTString] = H.GetRMS();
   }

   File.Close();

   DHFile.SaveToFile("ResolutionDatabase.dh");

   PdfFile.AddPlot(GMean, "ap");
   PdfFile.AddPlot(GRMS, "ap");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



