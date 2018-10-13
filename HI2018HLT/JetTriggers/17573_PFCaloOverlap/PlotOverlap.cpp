#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("HLTFile");
   string TreeName = CL.Get("HLTTree");
   vector<string> CaloTriggers = CL.GetStringVector("CaloTrigger");
   vector<string> CaloLabels = CL.GetStringVector("CaloLabel");
   vector<string> PFTriggers = CL.GetStringVector("PFTrigger");
   vector<string> PFLabels = CL.GetStringVector("PFLabel");
   string Output = CL.Get("Output");

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Correlation");

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   int NCalo = CaloTriggers.size();
   int NPF = PFTriggers.size();

   TH1D HCalo("HCalo", "", NCalo, 0, NCalo);
   TH1D HPF("HPF", "", NPF, 0, NPF);
   TH2D HCaloPF("HCaloPF", "", NCalo, 0, NCalo, NPF, 0, NPF);
   TH2D HCaloPFIncrease("HCaloPFIncrease", "", NCalo, 0, NCalo, NPF, 0, NPF);

   HCalo.SetStats(0);
   HPF.SetStats(0);
   HCaloPF.SetStats(0);
   HCaloPFIncrease.SetStats(0);

   for(int i = 1; i <= NCalo; i++)
      HCalo.GetXaxis()->SetBinLabel(i, CaloLabels[i-1].c_str());
   for(int i = 1; i <= NPF; i++)
      HPF.GetXaxis()->SetBinLabel(i, PFLabels[i-1].c_str());
   for(int i = 1; i <= NCalo; i++)
      HCaloPF.GetXaxis()->SetBinLabel(i, CaloLabels[i-1].c_str());
   for(int i = 1; i <= NPF; i++)
      HCaloPF.GetYaxis()->SetBinLabel(i, PFLabels[i-1].c_str());
   for(int i = 1; i <= NCalo; i++)
      HCaloPFIncrease.GetXaxis()->SetBinLabel(i, CaloLabels[i-1].c_str());
   for(int i = 1; i <= NPF; i++)
      HCaloPFIncrease.GetYaxis()->SetBinLabel(i, PFLabels[i-1].c_str());

   for(int i = 1; i <= NCalo; i++)
      HCalo.SetBinContent(i, Tree->GetEntries(CaloTriggers[i-1].c_str()));
   for(int i = 1; i <= NPF; i++)
      HPF.SetBinContent(i, Tree->GetEntries(PFTriggers[i-1].c_str()));
   for(int i = 1; i <= NCalo; i++)
   {
      for(int j = 1; j <= NPF; j++)
      {
         HCaloPF.SetBinContent(i, j, Tree->GetEntries((CaloTriggers[i-1] + " || " + PFTriggers[j-1]).c_str()));
         HCaloPFIncrease.SetBinContent(i, j, HCaloPF.GetBinContent(i, j) / HCalo.GetBinContent(i) - 1);
      }
   }

   PdfFile.AddPlot(HCalo, "hist text00", true);
   PdfFile.AddPlot(HPF, "hist text00", true);
   PdfFile.AddPlot(HCaloPF, "colz text00", false, true);

   gStyle->SetPaintTextFormat(".2g");

   PdfFile.AddPlot(HCaloPFIncrease, "colz text00", false, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();
}





