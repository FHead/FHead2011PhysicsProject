#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

#define TRIGGER_NONE 0
#define TRIGGER_PbPb100 1

int main(int argc, char *argv[]);
double GetPercentage(TTree *T, string Cut, int TriggerType, double CMin, double CMax);

int main(int argc, char *argv[])
{
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase TriggerType CMin CMax" << endl;
      return 0;
   }

   int TriggerType = TRIGGER_NONE;
   if(string(argv[3]) == "PbPb100")
      TriggerType = TRIGGER_PbPb100;

   double CMin = atof(argv[4]);
   double CMax = atof(argv[5]);

   SetThesisStyle();

   int BinZ = 7;
   double Z[7] = {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45};
   string ZStr[7] = {"SubJetDR0", "SubJetDRs[0]", "SubJetDRs[1]",
      "SubJetDRs[2]", "SubJetDRs[3]", "SubJetDRs[4]", "SubJetDRs[5]"};

   int BinDR = 7;
   double DR[7] = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4};
   string DRStr[7] = {"0.10", "0.15", "0.20", "0.25", "0.30", "0.35", "0.40"};

   TH2D H("H", ";DR Cut;Z Cut", BinDR, 0, BinDR, BinZ, 0, BinZ);
   H.SetStats(0);

   for(int i = 0; i < BinZ; i++)
      H.GetYaxis()->SetBinLabel(i + 1, Form("%.2f", Z[i]));
   for(int i = 0; i < BinDR; i++)
      H.GetXaxis()->SetBinLabel(i + 1, Form("%.2f", DR[i]));

   TFile File(argv[1]);
   TTree *T = (TTree *)File.Get("T");

   for(int i = 0; i < BinDR; i++)
      for(int j = 0; j < BinZ; j++)
         H.SetBinContent(i + 1, j + 1, GetPercentage(T, ZStr[j] + ">" + DRStr[i], TriggerType, CMin, CMax));

   TCanvas C;

   H.Draw("colz text");

   H.SetMaximum(100);
   H.SetMinimum(0.1);
   C.SetLogz();

   C.SaveAs((string(argv[2]) + ".pdf").c_str());

   return 0;
}

double GetPercentage(TTree *T, string Cut, int TriggerType, double CMin, double CMax)
{
   if(T == NULL)
      return 0;

   string Selection = "(JetCSPT > 180 && abs(JetCSEta) < 1.3)";
   if(T->GetBranch("MCWeight") != NULL)
      Selection = Selection + " * MCWeight";

   if(TriggerType == TRIGGER_PbPb100)
      Selection = Selection + " * PassPbPb100";

   if(CMin >= 0)
      Selection = Selection + Form(" * (Centrality >= %f)", CMin);
   if(CMax >= 0)
      Selection = Selection + Form(" * (Centrality <= %f)", CMax);

   TH1D HTemp("HTemp", "HTemp", 2, 0, 2);
   T->Draw((Cut + ">>HTemp").c_str(), Selection.c_str());

   return HTemp.GetMean() * 100;
}




