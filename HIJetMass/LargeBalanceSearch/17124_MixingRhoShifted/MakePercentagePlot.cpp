#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "DataHelper.h"

#define TRIGGER_NONE 0
#define TRIGGER_PbPb100 1

int main(int argc, char *argv[]);
pair<double, double> GetPercentage(TTree *T, string Cut, int TriggerType, double CMin, double CMax);

int main(int argc, char *argv[])
{
   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase TriggerType CMin CMax State" << endl;
      return 0;
   }

   int TriggerType = TRIGGER_NONE;
   if(string(argv[3]) == "PbPb100")
      TriggerType = TRIGGER_PbPb100;

   double CMin = atof(argv[4]);
   double CMax = atof(argv[5]);

   string State = argv[6];

   SetThesisStyle();

   int BinZ = 7;
   double Z[7] = {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45};
   string ZStr[7] = {"BestJetDR", "SubJetDRs[0]", "SubJetDRs[1]",
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
   TTree *T = (TTree *)File.Get("OutputTree");

   T->SetAlias("CWeight1", "(9.213e4-3.165e5*Centrality+1.246e6*Centrality*Centrality-2.297e6*Centrality*Centrality*Centrality+1.605e6*Centrality*Centrality*Centrality*Centrality)");
   T->SetAlias("CWeight2", "(1.173e5*exp(-(Centrality-0.7545)*(Centrality-0.7545)/(2*0.05989*0.05989)))");
   T->SetAlias("CWeight", "((Centrality<0.74)*CWeight1+(Centrality>0.74)*CWeight2)");

   T->SetAlias("DEta", "(BestJetEta-JetEta)");
   T->SetAlias("DPhiRaw", "(BestJetPhi-JetPhi)");
   T->SetAlias("DPhi", "(DPhiRaw+(DPhiRaw<-3.14159)*2*3.14159-(DPhiRaw>3.14159)*2*3.14159)");
   T->SetAlias("DR2", "(DEta*DEta+DPhi*DPhi)");

   DataHelper DHFile("PercentageResult.dh");

   for(int i = 0; i < BinDR; i++)
   {
      for(int j = 0; j < BinZ; j++)
      {
         pair<double, double> Result = GetPercentage(T, ZStr[j] + ">" + DRStr[i], TriggerType, CMin, CMax);
         H.SetBinContent(i + 1, j + 1, Result.first);
         H.SetBinError(i + 1, j + 1, Result.second);

         DHFile[State][Form("Z %.02f DR %.02f Percentage", Z[j], DR[i])] = Result.first / 100;
         DHFile[State][Form("Z %.02f DR %.02f Error", Z[j], DR[i])] = Result.second / 100;
      }
   }

   DHFile.SaveToFile("PercentageResult.dh");

   TCanvas C;

   H.Draw("colz text e");

   H.SetMaximum(100);
   H.SetMinimum(0.1);
   C.SetLogz();

   C.SaveAs((string(argv[2]) + ".pdf").c_str());

   return 0;
}

pair<double, double> GetPercentage(TTree *T, string Cut, int TriggerType, double CMin, double CMax)
{
   if(T == NULL)
      return pair<double, double>(0, 0);

   string Selection = "(BestJetPT > 180 && abs(BestJetEta) < 1.3)";
   if(T->GetBranch("MCWeight") != NULL)
      Selection = Selection + " * MCWeight";

   if(TriggerType == TRIGGER_PbPb100)
      Selection = Selection + " * PassPbPb100";

   if(CMin >= 0)
      Selection = Selection + Form(" * (Centrality >= %f) * CWeight", CMin);
   if(CMax >= 0)
      Selection = Selection + Form(" * (Centrality <= %f) * CWeight", CMax);

   Selection = Selection + " * (DR2 < 0.1 * 0.1)";

   TH1D HTemp("HTemp", "HTemp", 2, 0, 2);
   T->Draw((Cut + ">>HTemp").c_str(), Selection.c_str());

   return pair<double, double>(HTemp.GetMean() * 100, HTemp.GetMeanError() * 100);
}




