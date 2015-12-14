#include <iostream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

#include "ReadNTPTreeV4.h"

int main();
template<class T> void ComparePlots(PsFileHelper &PsFile, T &HPF, T &HCalo,
   string Option, bool LogY = false, bool LogZ = false);
void SaveToFile(TH2D &H, string Option);

int main()
{
   SetStyle();

   TChain Tree("ntp1", "ntp1");
   Tree.AddFile("Samples/default_MC_400_0_P3d.root");
   Tree.AddFile("Samples/default_MC_402_0_Gbv.root");
   Tree.AddFile("Samples/default_MC_38_0_51d.root");
   Tree.AddFile("Samples/default_MC_285_0_OcN.root");
   Tree.AddFile("Samples/default_MC_191_0_iCP.root");
   Tree.AddFile("Samples/default_MC_75_0_Y0w.root");

   NTPTreeMessenger M;
   M.SetBranchAddress(&Tree);

   TH1D HPFJetPT("HPFJetPT", "PF jet PT;PT", 100, 0, 500);
   TH1D HCaloJetPT("HCaloJetPT", "Calo jet PT;PT", 100, 0, 500);
   
   TH1D HPFJetEta("HPFJetEta", "PF jet eta (PT > 60);Eta", 100, -4, 4);
   TH1D HCaloJetEta("HCaloJetEta", "Calo jet eta (PT > 60);Eta", 100, -4, 4);

   TH1D HPFJetPhi("HPFJetPhi", "PF jet phi (PT > 60);Phi", 100, -4, 4);
   TH1D HCaloJetPhi("HCaloJetPhi", "Calo jet phi (PT > 60);Phi", 100, -4, 4);

   TH1D HClosestDR("HClosestDR", "dR(PF jet, closest calo jet)", 100, -1, 5);

   TH2D HPFJetPTVsCaloJetPT("HPFJetPTVsCaloJetPT", "PF jet PT vs. Calo jet PT;PF;Calo", 100, 0, 500, 100, 0, 500);
   TH2D HPFJetPTVsCaloJetPTSmallDR("HPFJetPTVsCaloJetPTSmallDR",
      "PF jet PT vs. Calo jet PT, dR < 0.1;PF;Calo", 100, 0, 500, 100, 0, 500);
   TH1D HPFJetPTMatchedCaloJetPTDifference("HPFJetPTMatchedCaloJetPTDifference",
      "PF Jet PT - Calo Jet PT (matched);PF - Calo", 100, -500, 500);
   TH1D HPFJetPTMatchedGoodCaloJetPTDifference("HPFJetPTMatchedGoodCaloJetPTDifference",
      "PF Jet PT - Calo Jet PT (matched, at least 60 GeV/c);PF - Calo", 100, -500, 500);

   TH1D HPFJetTCHE("HPFJetTCHE", "PFJet TCHE", 100, -10, 20);
   TH1D HCaloJetTCHE("HCaloJetTCHE", "CaloJet TCHE", 100, -10, 20);
   TH2D HPFJetTCHEVsCaloJetTCHE("HPFJetTCHEVsCaloJetTCHE", "PFJet TCHE vs. CaloJet TCHE", 100, -10, 20, 100, -10, 20);

   TH1D HPFJetOffDiagonalPT("HPFJetOffDiagonalPT", "PF Jet PT, off-diagonal;PT", 100, 0, 500);
   TH1D HCaloJetOffDiagonalPT("HCaloJetOffDiagonalPT", "Calo Jet PT, off-diagonal;PT", 100, 0, 500);
   TH2D HPFJetVsCaloJetOffDiagonalPT("HPFJetVsCaloJetOffDiagonalPT",
      "PF Jet PT vs. Calo Jet PT, off-diagonal;PT", 100, 0, 500, 100, 0, 500);
   
   TH1D HPFJetOffDiagonalEta("HPFJetOffDiagonalEta", "PF Jet Eta, off-diagonal;Eta", 100, -4, 4);
   TH1D HCaloJetOffDiagonalEta("HCaloJetOffDiagonalEta", "Calo Jet Eta, off-diagonal;Eta", 100, -4, 4);
   TH2D HPFJetVsCaloJetOffDiagonalEta("HPFJetVsCaloJetOffDiagonalEta",
      "PF Jet Eta vs. Calo Jet Eta, off-diagonal;Eta", 100, -4, 4, 100, -4, 4);

   TH1D HPFJetOffDiagonalPhi("HPFJetOffDiagonalPhi", "PF Jet Phi, off-diagonal;Phi", 100, -4, 4);
   TH1D HCaloJetOffDiagonalPhi("HCaloJetOffDiagonalPhi", "Calo Jet Phi, off-diagonal;Phi", 100, -4, 4);
   TH2D HPFJetVsCaloJetOffDiagonalPhi("HPFJetVsCaloJetOffDiagonalPhi",
      "PF Jet Phi vs. Calo Jet Phi, off-diagonal;Phi", 100, -4, 4, 100, -4, 4);

   TH2D HPFJetCaloJetOnDiagonalDEtaDPhi("HPFJetCaloJetOnDiagonalDEtaDPhi",
      "PFJet and closest CaloJet (deta, dphi), on-diagonal;deta;dphi", 100, -0.2, 0.2, 100, -0.2, 0.2);
   TH2D HPFJetCaloJetOffDiagonalDEtaDPhi("HPFJetCaloJetOffDiagonalDEtaDPhi",
      "PFJet and closest CaloJet (deta, dphi), off-diagonal;deta;dphi", 100, -0.2, 0.2, 100, -0.2, 0.2);

   int NumberOfEvents = Tree.GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 100000 == 0)
      {
         time_t currenttime;
         time(&currenttime);
         string stringtime = ctime(&currenttime);
         for(int i = 0; i < (int)stringtime.size(); i++)
         {
            if(stringtime[i] == '\n')
            {
               stringtime.erase(stringtime.begin() + i);
               i = i - 1;
            }
         }
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << " (" << stringtime << ")" << endl;
      }

      Tree.GetEntry(iEvent);

      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         FourVector PFJetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i], M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);
         HPFJetPT.Fill(PFJetP.GetPT());
         if(PFJetP.GetPT() > 60)
         {
            HPFJetEta.Fill(PFJetP.GetEta());
            HPFJetPhi.Fill(PFJetP.GetPhi());
         }
      }
      
      for(int i = 0; i < M.nAK5Jet; i++)
      {
         FourVector CaloJetP(M.energyAK5Jet[i], M.pxAK5Jet[i], M.pyAK5Jet[i], M.pzAK5Jet[i]);
         HCaloJetPT.Fill(CaloJetP.GetPT());
         if(CaloJetP.GetPT() > 60)
         {
            HCaloJetEta.Fill(CaloJetP.GetEta());
            HCaloJetPhi.Fill(CaloJetP.GetPhi());
         }
      }
      
      for(int i = 0; i < M.nAK5PFPUcorrJet; i++)
      {
         FourVector PFJetP(M.energyAK5PFPUcorrJet[i], M.pxAK5PFPUcorrJet[i], M.pyAK5PFPUcorrJet[i], M.pzAK5PFPUcorrJet[i]);
         if(PFJetP.GetPT() < 60)
            continue;
         if(PFJetP.GetEta() < -2 || PFJetP.GetEta() > 2)
            continue;

         FourVector ClosestCaloJetP(0, 0, 0, 0);
         int ClosestIndex = -1;

         for(int j = 0; j < M.nAK5Jet; j++)
         {
            FourVector CaloJetP(M.energyAK5Jet[j], M.pxAK5Jet[j], M.pyAK5Jet[j], M.pzAK5Jet[j]);
            if(CaloJetP.GetEta() < -2 || CaloJetP.GetEta() > 2)
               continue;

            if(ClosestCaloJetP.GetP() < 1e-5)
            {
               ClosestCaloJetP = CaloJetP;
               ClosestIndex = j;
            }
            if(GetDR(PFJetP, CaloJetP) < GetDR(PFJetP, ClosestCaloJetP))
            {
               ClosestCaloJetP = CaloJetP;
               ClosestIndex = j;
            }
         }

         double DR = GetDR(PFJetP, ClosestCaloJetP);

         if(ClosestIndex < 0)
         {
            HClosestDR.Fill(-0.5);
            continue;
         }
         else
         {
            HClosestDR.Fill(DR);
            HPFJetPTVsCaloJetPT.Fill(PFJetP.GetPT(), ClosestCaloJetP.GetPT());
            if(DR < 0.1)
            {
               HPFJetPTVsCaloJetPTSmallDR.Fill(PFJetP.GetPT(), ClosestCaloJetP.GetPT());
               HPFJetPTMatchedCaloJetPTDifference.Fill(PFJetP.GetPT() - ClosestCaloJetP.GetPT());
               if(ClosestCaloJetP.GetPT() > 60)
                  HPFJetPTMatchedGoodCaloJetPTDifference.Fill(PFJetP.GetPT() - ClosestCaloJetP.GetPT());
            }
         }

         double PFTag = M.trackCountingHighEffBJetTagsAK5PFPUcorrJet[i];
         double CaloTag = M.trackCountingHighEffBJetTagsAK5Jet[ClosestIndex];

         if(DR < 0.1 && ClosestCaloJetP.GetPT() > 60)
         {
            HPFJetTCHE.Fill(PFTag);
            HCaloJetTCHE.Fill(CaloTag);
            HPFJetTCHEVsCaloJetTCHE.Fill(PFTag, CaloTag);
         }

         if(DR < 0.1 && ClosestCaloJetP.GetPT() > 60 && fabs(PFTag - CaloTag) > 1)
         {
            HPFJetOffDiagonalPT.Fill(PFJetP.GetPT());
            HCaloJetOffDiagonalPT.Fill(ClosestCaloJetP.GetPT());
            HPFJetVsCaloJetOffDiagonalPT.Fill(PFJetP.GetPT(), ClosestCaloJetP.GetPT());
            
            HPFJetOffDiagonalEta.Fill(PFJetP.GetEta());
            HCaloJetOffDiagonalEta.Fill(ClosestCaloJetP.GetEta());
            HPFJetVsCaloJetOffDiagonalEta.Fill(PFJetP.GetEta(), ClosestCaloJetP.GetEta());
            
            HPFJetOffDiagonalPhi.Fill(PFJetP.GetPhi());
            HCaloJetOffDiagonalPhi.Fill(ClosestCaloJetP.GetPhi());
            HPFJetVsCaloJetOffDiagonalPhi.Fill(PFJetP.GetPhi(), ClosestCaloJetP.GetPhi());
            
            HPFJetCaloJetOffDiagonalDEtaDPhi.Fill(PFJetP.GetEta() - ClosestCaloJetP.GetEta(),
               GetDPhi(PFJetP, ClosestCaloJetP));
         }
         if(DR < 0.1 && ClosestCaloJetP.GetPT() > 60 && fabs(PFTag - CaloTag) < 1)
            HPFJetCaloJetOnDiagonalDEtaDPhi.Fill(PFJetP.GetEta() - ClosestCaloJetP.GetEta(),
               GetDPhi(PFJetP, ClosestCaloJetP));
      }
   }

   PsFileHelper PsFile("CaloVsPF.ps");
   PsFile.AddTextPage("Calo vs. PF b-tagging comparison");

   PsFile.AddTextPage("Basic jet plots");
   ComparePlots(PsFile, HPFJetPT, HCaloJetPT, "", true);
   ComparePlots(PsFile, HPFJetEta, HCaloJetEta, "", true);
   ComparePlots(PsFile, HPFJetPhi, HCaloJetPhi, "", true);

   PsFile.AddTextPage("Matching PF and Calo jets");
   PsFile.AddPlot(HClosestDR, "", true);
   PsFile.AddPlot(HPFJetPTVsCaloJetPT, "colz", false, true);
   SaveToFile(HPFJetPTVsCaloJetPT, "colz");
   PsFile.AddPlot(HPFJetPTVsCaloJetPTSmallDR, "colz", false, true);
   PsFile.AddPlot(HPFJetPTMatchedCaloJetPTDifference, "", true);
   PsFile.AddPlot(HPFJetPTMatchedGoodCaloJetPTDifference, "", true);

   PsFile.AddTextPage("B-tagging");
   ComparePlots(PsFile, HPFJetTCHE, HCaloJetTCHE, "", true);
   PsFile.AddPlot(HPFJetTCHEVsCaloJetTCHE, "colz", false, false);
   PsFile.AddPlot(HPFJetTCHEVsCaloJetTCHE, "colz", false, true);
   SaveToFile(HPFJetTCHEVsCaloJetTCHE, "colz");

   PsFile.AddTextPage("Off-diagonal jets....");
   ComparePlots(PsFile, HPFJetOffDiagonalPT, HCaloJetOffDiagonalPT, "", true);
   PsFile.AddPlot(HPFJetVsCaloJetOffDiagonalPT, "colz", false, true);
   SaveToFile(HPFJetVsCaloJetOffDiagonalPT, "colz");
   ComparePlots(PsFile, HPFJetOffDiagonalEta, HCaloJetOffDiagonalEta, "", true);
   PsFile.AddPlot(HPFJetVsCaloJetOffDiagonalEta, "colz", false, true);
   SaveToFile(HPFJetVsCaloJetOffDiagonalEta, "colz");
   ComparePlots(PsFile, HPFJetOffDiagonalPhi, HCaloJetOffDiagonalPhi, "", true);
   PsFile.AddPlot(HPFJetVsCaloJetOffDiagonalPhi, "colz", false, true);
   SaveToFile(HPFJetVsCaloJetOffDiagonalPhi, "colz");
   PsFile.AddPlot(HPFJetCaloJetOffDiagonalDEtaDPhi, "colz", false, true);
   SaveToFile(HPFJetCaloJetOffDiagonalDEtaDPhi, "colz");
   PsFile.AddPlot(HPFJetCaloJetOnDiagonalDEtaDPhi, "colz", false, true);
   SaveToFile(HPFJetCaloJetOnDiagonalDEtaDPhi, "colz");

   double DiagonalCount = 0;
   for(int i = 1; i <= HPFJetTCHEVsCaloJetTCHE.GetNbinsX(); i++)
      DiagonalCount = DiagonalCount + HPFJetTCHEVsCaloJetTCHE.GetBinContent(i, i);
   cout << "Diagonal count in TCHE vs. TCHE correlation plot = " << DiagonalCount << endl;

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

template<class T> void ComparePlots(PsFileHelper &PsFile, T &HPF, T &HCalo, string Option, bool LogY, bool LogZ)
{
   TCanvas C;

   string Option1 = Option;
   string Option2 = "same";
   if(Option != "")
      Option2 = Option + " same";

   string TempTitle = HPF.GetTitle();
   string NewTitle = TempTitle + " (blue) vs. " + HCalo.GetTitle() + " (red)";

   HPF.SetStats(0);
   HCalo.SetStats(0);

   HPF.SetTitle(NewTitle.c_str());

   HCalo.SetLineColor(kRed);

   HPF.Draw(Option1.c_str());
   HCalo.Draw(Option2.c_str());

   if(LogY == true)
      C.SetLogy();
   if(LogZ == true)
      C.SetLogz();

   PsFile.AddCanvas(C);

   TCanvas C2("C2", "C2", 1024, 1024);

   HPF.Draw(Option1.c_str());
   HCalo.Draw(Option2.c_str());

   if(LogY == true)
      C2.SetLogy();
   if(LogZ == true)
      C2.SetLogz();
   
   static int count = 0;
   count = count + 1;

   C2.SaveAs(Form("Plot_%d.png", count));
   C2.SaveAs(Form("Plot_%d.C", count));
   C2.SaveAs(Form("Plot_%d.eps", count));
   C2.SaveAs(Form("Plot_%d.pdf", count));

   HPF.SetTitle(TempTitle.c_str());
}

void SaveToFile(TH2D &H, string Option)
{
   TCanvas C("C", "C", 1024, 1024);

   H.Draw(Option.c_str());

   C.SetLogz();

   C.SaveAs(Form("%s.png", H.GetName()));
   C.SaveAs(Form("%s.C", H.GetName()));
   C.SaveAs(Form("%s.eps", H.GetName()));
   C.SaveAs(Form("%s.pdf", H.GetName()));
}





