#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"

int main();
void ScaleHistogram(TH2D &H);

int main()
{
   SetThesisStyle();

   TFile File("openHLT.root");

   TTree *Tree = (TTree *)File.Get("hltbitanalysis/HltTree");

   TH2D H40("H40", ";CSV with PF Tracking;CSV with Common Tracking", 2, 0, 2, 2, 0, 2);
   TH2D H60("H60", ";CSV with PF Tracking;CSV with Common Tracking", 2, 0, 2, 2, 0, 2);
   TH2D H80("H80", ";CSV with PF Tracking;CSV with Common Tracking", 2, 0, 2, 2, 0, 2);

   H40.GetXaxis()->SetBinLabel(1, "Fail");
   H40.GetXaxis()->SetBinLabel(2, "Pass");
   H40.GetYaxis()->SetBinLabel(1, "Fail");
   H40.GetYaxis()->SetBinLabel(2, "Pass");
   H60.GetXaxis()->SetBinLabel(1, "Fail");
   H60.GetXaxis()->SetBinLabel(2, "Pass");
   H60.GetYaxis()->SetBinLabel(1, "Fail");
   H60.GetYaxis()->SetBinLabel(2, "Pass");
   H80.GetXaxis()->SetBinLabel(1, "Fail");
   H80.GetXaxis()->SetBinLabel(2, "Pass");
   H80.GetYaxis()->SetBinLabel(1, "Fail");
   H80.GetYaxis()->SetBinLabel(2, "Pass");

   Tree->SetAlias("J40", "HLT_PAAK4PFJet40_Eta2p1_v1");
   Tree->SetAlias("J60", "HLT_PAAK4PFJet60_Eta2p1_v1");
   Tree->SetAlias("J80", "HLT_PAAK4PFJet80_Eta2p1_v1");
   Tree->SetAlias("O40", "HLT_PAAK4PFBJetCSV40_Eta2p1_v1");
   Tree->SetAlias("O60", "HLT_PAAK4PFBJetCSV60_Eta2p1_v1");
   Tree->SetAlias("O80", "HLT_PAAK4PFBJetCSV80_Eta2p1_v1");
   Tree->SetAlias("N40", "HLT_PAAK4PFBJetCSV40_CommonTracking_Eta2p1_v1");
   Tree->SetAlias("N60", "HLT_PAAK4PFBJetCSV60_CommonTracking_Eta2p1_v1");
   Tree->SetAlias("N80", "HLT_PAAK4PFBJetCSV80_CommonTracking_Eta2p1_v1");
   
   H40.SetBinContent(1, 1, Tree->GetEntries("!O40 && !N40 && J40"));
   H40.SetBinContent(1, 2, Tree->GetEntries("!O40 &&  N40 && J40"));
   H40.SetBinContent(2, 1, Tree->GetEntries(" O40 && !N40 && J40"));
   H40.SetBinContent(2, 2, Tree->GetEntries(" O40 &&  N40 && J40"));
   H60.SetBinContent(1, 1, Tree->GetEntries("!O60 && !N60 && J60"));
   H60.SetBinContent(1, 2, Tree->GetEntries("!O60 &&  N60 && J60"));
   H60.SetBinContent(2, 1, Tree->GetEntries(" O60 && !N60 && J60"));
   H60.SetBinContent(2, 2, Tree->GetEntries(" O60 &&  N60 && J60"));
   H80.SetBinContent(1, 1, Tree->GetEntries("!O80 && !N80 && J80"));
   H80.SetBinContent(1, 2, Tree->GetEntries("!O80 &&  N80 && J80"));
   H80.SetBinContent(2, 1, Tree->GetEntries(" O80 && !N80 && J80"));
   H80.SetBinContent(2, 2, Tree->GetEntries(" O80 &&  N80 && J80"));

   H40.SetMarkerSize(2.5);
   H60.SetMarkerSize(2.5);
   H80.SetMarkerSize(2.5);

   TCanvas C;

   H40.SetStats(0);
   H40.Draw("colz text00");
   
   C.SaveAs("CountPT40.png");
   C.SaveAs("CountPT40.C");
   C.SaveAs("CountPT40.eps");
   C.SaveAs("CountPT40.pdf");

   H60.SetStats(0);
   H60.Draw("colz text00");
   
   C.SaveAs("CountPT60.png");
   C.SaveAs("CountPT60.C");
   C.SaveAs("CountPT60.eps");
   C.SaveAs("CountPT60.pdf");

   H80.SetStats(0);
   H80.Draw("colz text00");
   
   C.SaveAs("CountPT80.png");
   C.SaveAs("CountPT80.C");
   C.SaveAs("CountPT80.eps");
   C.SaveAs("CountPT80.pdf");

   ScaleHistogram(H40);
   ScaleHistogram(H60);
   ScaleHistogram(H80);

   H40.SetStats(0);
   H40.Draw("colz text00");
   
   C.SaveAs("CorrelationPT40.png");
   C.SaveAs("CorrelationPT40.C");
   C.SaveAs("CorrelationPT40.eps");
   C.SaveAs("CorrelationPT40.pdf");

   H60.SetStats(0);
   H60.Draw("colz text00");
   
   C.SaveAs("CorrelationPT60.png");
   C.SaveAs("CorrelationPT60.C");
   C.SaveAs("CorrelationPT60.eps");
   C.SaveAs("CorrelationPT60.pdf");

   H80.SetStats(0);
   H80.Draw("colz text00");
   
   C.SaveAs("CorrelationPT80.png");
   C.SaveAs("CorrelationPT80.C");
   C.SaveAs("CorrelationPT80.eps");
   C.SaveAs("CorrelationPT80.pdf");

   File.Close();

   return 0;
}

void ScaleHistogram(TH2D &H)
{
   double T11 = H.GetBinContent(1, 1);
   double T22 = H.GetBinContent(2, 2);

   H.SetBinContent(1, 1, H.GetBinContent(1, 1) / sqrt(T11 * T11));
   H.SetBinContent(1, 2, H.GetBinContent(1, 2) / sqrt(T11 * T22));
   H.SetBinContent(2, 1, H.GetBinContent(2, 1) / sqrt(T22 * T11));
   H.SetBinContent(2, 2, H.GetBinContent(2, 2) / sqrt(T22 * T22));
}




