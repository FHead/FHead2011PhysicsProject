#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
double GetDPhi(double phi1, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSoftDropJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HMatchedDR("HMatchedDR", "Matched DR; DR", 100, 0, 1.5);
   TH2D HPTMatchedPT("HPTMatchedPT", "Matched PT; Jet PT; Matched PT", 100, 100, 300, 100, 0, 500);
   TH2D HJetPTEta("HJetPTEta", "Jet PT vs. Eta;Jet PT;Jet Eta", 100, 100, 300, 100, -1.3, 1.3);
   TH2D HPTGroomedRatio("HPTGroomedRatio", ";Jet PT;Groomed / Jet PT", 100, 100, 300, 100, 0, 1);
   TProfile PPTGroomedRatio("PPTGroomedRatio", ";Jet PT;Groomed / Jet PT", 100, 100, 300);
   TH2D HEtaGroomedRatio("HEtaGroomedRatio", ";Jet Eta;Groomed / Jet PT", 100, -1.3, 1.3, 100, 0, 1);
   TProfile PEtaGroomedRatio("PEtaGroomedRatio", ";Jet Eta;Groomed / Jet PT", 100, -1.3, 1.3);
   TH1D HGroomedRatio_PT100("HGroomedRatio_PT100", "Jet PT = 100-120;Groomed / Jet PT", 100, 0.5, 1);
   TH1D HGroomedRatio_PT120("HGroomedRatio_PT120", "Jet PT = 120-140;Groomed / Jet PT", 100, 0.5, 1);
   TH1D HGroomedRatio_PT140("HGroomedRatio_PT140", "Jet PT = 140-160;Groomed / Jet PT", 100, 0.5, 1);
   TH1D HGroomedRatio_PT160("HGroomedRatio_PT160", "Jet PT = 160-200;Groomed / Jet PT", 100, 0.5, 1);
   TH1D HGroomedRatio_PT200("HGroomedRatio_PT200", "Jet PT = 200-300;Groomed / Jet PT", 100, 0.5, 1);
   TProfile2D PGroomedRatio("PGroomedRatio", ";Jet PT;Jet #eta;Groomed Ratio", 100, 100, 300, 100, -1.3, 1.3);
   TH2D HPTDepth("HPTDepth", ";Jet PT;Depth", 100, 100, 300, 12, 0, 12);
   TProfile PPTDepth("PPTDepth", ";Jet PT;Depth", 100, 100, 300);
   TH2D HEtaDepth("HEtaDepth", ";Jet Eta;Depth", 100, -1.3, 1.3, 12, 0, 12);
   TProfile PEtaDepth("PEtaDepth", ";Jet Eta;Depth", 100, -1.3, 1.3);
   TH1D HDepth_PT100("HDepth_PT100", "Jet PT = 100-120;Depth", 12, 0, 12);
   TH1D HDepth_PT120("HDepth_PT120", "Jet PT = 120-140;Depth", 12, 0, 12);
   TH1D HDepth_PT140("HDepth_PT140", "Jet PT = 140-160;Depth", 12, 0, 12);
   TH1D HDepth_PT160("HDepth_PT160", "Jet PT = 160-200;Depth", 12, 0, 12);
   TH1D HDepth_PT200("HDepth_PT200", "Jet PT = 200-300;Depth", 12, 0, 12);
   TProfile2D PDepth("PDepth", ";Jet PT;Jet #eta;Depth", 100, 100, 300, 100, -1.3, 1.3);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.Tree->GetEntry(iEntry);
      MSkim.Tree->GetEntry(iEntry);
      MJet.Tree->GetEntry(iEntry);
      MSoftDropJet.Tree->GetEntry(iEntry);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;

      int Count = MJet.JetCount;
      vector<float> JetPT(MJet.JetPT, MJet.JetPT + Count);
      vector<float> JetEta(MJet.JetEta, MJet.JetEta + Count);
      vector<float> JetPhi(MJet.JetPhi, MJet.JetPhi + Count);

      for(int i = 0; i < Count; i++)
      {
         if(JetPT[i] < 80 || JetEta[i] > 2.0 || JetEta[i] < -2.0)
         {
            Count = Count - 1;
            JetPT.erase(JetPT.begin() + i);
            JetEta.erase(JetEta.begin() + i);
            JetPhi.erase(JetPhi.begin() + i);
            i = i - 1;
         }
      }

      vector<int> Index = DRMatching(Count, JetEta, JetPhi,
         MSoftDropJet.JetCount, MSoftDropJet.JetEta, MSoftDropJet.JetPhi);

      for(int i = 0; i < Count; i++)
      {
         if(JetPT[i] < 100 || JetPT[i] > 300)
            continue;
         if(JetEta[i] < -1.3 || JetEta[i] > 1.3)
            continue;

         double DEta = JetEta[i] - MSoftDropJet.JetEta[Index[i]];
         double DPhi = JetPhi[i] - MSoftDropJet.JetPhi[Index[i]];
         if(DPhi > PI)    DPhi = DPhi - 2 * PI;
         if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
         double DR = sqrt(DEta * DEta + DPhi * DPhi);
         HMatchedDR.Fill(sqrt(DEta * DEta + DPhi * DPhi));

         if(DR > 0.2)
            continue;

         HPTMatchedPT.Fill(JetPT[i], MSoftDropJet.JetPT[Index[i]]);

         if(JetPT[i] < MSoftDropJet.JetPT[Index[i]])   // Huh?
            continue;
         
         HJetPTEta.Fill(JetPT[i], JetEta[i]);
         
         HPTGroomedRatio.Fill(JetPT[i], MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         PPTGroomedRatio.Fill(JetPT[i], MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         HEtaGroomedRatio.Fill(JetEta[i], MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         PEtaGroomedRatio.Fill(JetEta[i], MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         if(JetPT[i] <= 120 && JetPT[i] > 100)
            HGroomedRatio_PT100.Fill(MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         if(JetPT[i] <= 140 && JetPT[i] > 120)
            HGroomedRatio_PT120.Fill(MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         if(JetPT[i] <= 160 && JetPT[i] > 140)
            HGroomedRatio_PT140.Fill(MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         if(JetPT[i] <= 200 && JetPT[i] > 160)
            HGroomedRatio_PT160.Fill(MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         if(JetPT[i] <= 300 && JetPT[i] > 200)
            HGroomedRatio_PT200.Fill(MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         PGroomedRatio.Fill(JetPT[i], JetEta[i], MSoftDropJet.JetPT[Index[i]] / JetPT[i]);
         
         if(MSoftDropJet.JetDroppedBranches[Index[i]] >= 0)
         {
            HPTDepth.Fill(JetPT[i], MSoftDropJet.JetDroppedBranches[Index[i]]);
            PPTDepth.Fill(JetPT[i], MSoftDropJet.JetDroppedBranches[Index[i]]);
            HEtaDepth.Fill(JetEta[i], MSoftDropJet.JetDroppedBranches[Index[i]]);
            PEtaDepth.Fill(JetEta[i], MSoftDropJet.JetDroppedBranches[Index[i]]);
            PDepth.Fill(JetPT[i], JetEta[i], MSoftDropJet.JetDroppedBranches[Index[i]]);
         }
         if(JetPT[i] <= 120 && JetPT[i] > 100)
            HDepth_PT100.Fill(MSoftDropJet.JetDroppedBranches[Index[i]]);
         if(JetPT[i] <= 140 && JetPT[i] > 120)
            HDepth_PT120.Fill(MSoftDropJet.JetDroppedBranches[Index[i]]);
         if(JetPT[i] <= 160 && JetPT[i] > 140)
            HDepth_PT140.Fill(MSoftDropJet.JetDroppedBranches[Index[i]]);
         if(JetPT[i] <= 200 && JetPT[i] > 160)
            HDepth_PT160.Fill(MSoftDropJet.JetDroppedBranches[Index[i]]);
         if(JetPT[i] <= 300 && JetPT[i] > 200)
            HDepth_PT200.Fill(MSoftDropJet.JetDroppedBranches[Index[i]]);
      }
   }

   HMatchedDR.Write();
   HPTMatchedPT.Write();
   HJetPTEta.Write();
   HPTGroomedRatio.Write();
   PPTGroomedRatio.Write();
   HEtaGroomedRatio.Write();
   PEtaGroomedRatio.Write();
   HGroomedRatio_PT100.Write();
   HGroomedRatio_PT120.Write();
   HGroomedRatio_PT140.Write();
   HGroomedRatio_PT160.Write();
   HGroomedRatio_PT200.Write();
   PGroomedRatio.Write();
   HPTDepth.Write();
   PPTDepth.Write();
   HEtaDepth.Write();
   PEtaDepth.Write();
   HDepth_PT100.Write();
   HDepth_PT120.Write();
   HDepth_PT140.Write();
   HDepth_PT160.Write();
   HDepth_PT200.Write();
   PDepth.Write();

   OutputFile.Close();

   InputFile.Close();
}






