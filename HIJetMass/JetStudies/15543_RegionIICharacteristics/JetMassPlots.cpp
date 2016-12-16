#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "SDJetHelper.h"

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "I'd rather not run on data for this study" << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   double CBinMin[5+1] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   string PTBin[7] = {"PTBin0", "PTBin1", "PTBin2", "PTBin3", "PTBin4", "PTBin5", "PTBin6"};
   double PTBinMin[7+1] = {80, 100, 120, 140, 160, 200, 300, 500};

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH2D *HSubJet1Location[5][7] = {NULL};
   TH2D *HSubJet2Location[5][7] = {NULL};
   TH2D *HSubJet1XVsGenWeightedXIn[5][7] = {NULL};
   TH2D *HSubJet1PTVsGenSumPTIn[5][7] = {NULL};
   TH2D *HSubJet1PTVsGenSubJet1PTIn[5][7] = {NULL};
   TH2D *HSubJet2PTVsGenSubJet2PTIn[5][7] = {NULL};
   TH2D *HSubJet1DPTVsSubJet2DPTIn[5][7] = {NULL};
   TH2D *HSumPTVsGenSubJet1PTIn[5][7] = {NULL};
   TH2D *HSubJetAverageXVsSubJetAverageYIn[5][7] = {NULL};
   TH2D *HSubJet1XVsGenWeightedXOut[5][7] = {NULL};
   TH2D *HSubJet1PTVsGenSumPTOut[5][7] = {NULL};
   TH2D *HSubJet1PTVsGenSubJet1PTOut[5][7] = {NULL};
   TH2D *HSubJet2PTVsGenSubJet2PTOut[5][7] = {NULL};
   TH2D *HSubJet1DPTVsSubJet2DPTOut[5][7] = {NULL};
   TH2D *HSumPTVsGenSubJet1PTOut[5][7] = {NULL};
   TH2D *HSubJetAverageXVsSubJetAverageYOut[5][7] = {NULL};
   
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 7; j++)
      {
         char Title[1024] = "";
         sprintf(Title, "C %.0f%%-%.0f%%, PT %.0f-%.0f", CBinMin[i] * 100, CBinMin[i+1] * 100,
            PTBinMin[j], PTBinMin[j+1]);

         HSubJet1Location[i][j] = new TH2D(Form("HSubJet1Location%d%d", i, j),
            Form("%s;x;y", Title), 100, -5, 5, 100, -5, 5);
         HSubJet2Location[i][j] = new TH2D(Form("HSubJet2Location%d%d", i, j),
            Form("%s;x;y", Title), 100, -5, 5, 100, -5, 5);
         HSubJet1XVsGenWeightedXIn[i][j] = new TH2D(Form("HSubJet1XVsGenWeightedXIn%d%d", i, j),
            Form("%s;subjet1 x;average gen x", Title), 100, -2, 2, 100, 0, 1);
         HSubJet1PTVsGenSumPTIn[i][j] = new TH2D(Form("HSubJet1PTVsGenSumPTIn%d%d", i, j),
            Form("%s;subjet1 PT;gen PT1 + PT2", Title), 500, 0, 500, 500, 0, 500);
         HSubJet1PTVsGenSubJet1PTIn[i][j] = new TH2D(Form("HSubJet1PTVsGenSubJet1PTIn%d%d", i, j),
            Form("%s;subjet1 PT;gen PT1", Title), 500, 0, 500, 500, 0, 500);
         HSubJet2PTVsGenSubJet2PTIn[i][j] = new TH2D(Form("HSubJet2PTVsGenSubJet2PTIn%d%d", i, j),
            Form("%s;subjet2 PT;gen PT2", Title), 500, 0, 500, 500, 0, 500);
         HSubJet1DPTVsSubJet2DPTIn[i][j] = new TH2D(Form("HSubJet1DPTVsSubJet2DPTIn%d%d", i, j),
            Form("%s;subjet1 PT reco - gen;subjet2 PT reco - gen", Title), 200, -100, 100, 200, -100, 100);
         HSumPTVsGenSubJet1PTIn[i][j] = new TH2D(Form("HSumPTVsGenSubJet1PTIn%d%d", i, j),
            Form("%s;Sum PT;gen PT1", Title), 500, 0, 500, 500, 0, 500);
         HSubJetAverageXVsSubJetAverageYIn[i][j] = new TH2D(Form("HSubJetAverageXVsSubJetAverageYIn%d%d", i, j),
            Form("%s;Average x;Average y", Title), 100, -2.5, 2.5, 100, -2.5, 2.5);
         HSubJet1XVsGenWeightedXOut[i][j] = new TH2D(Form("HSubJet1XVsGenWeightedXOut%d%d", i, j),
            Form("%s;subjet1 x;average gen x", Title), 100, -2, 2, 100, 0, 1);
         HSubJet1PTVsGenSumPTOut[i][j] = new TH2D(Form("HSubJet1PTVsGenSumPTOut%d%d", i, j),
            Form("%s;subjet1 PT;gen PT1 + PT2", Title), 500, 0, 500, 500, 0, 500);
         HSubJet1PTVsGenSubJet1PTOut[i][j] = new TH2D(Form("HSubJet1PTVsGenSubJet1PTOut%d%d", i, j),
            Form("%s;subjet1 PT;gen PT1", Title), 500, 0, 500, 500, 0, 500);
         HSubJet2PTVsGenSubJet2PTOut[i][j] = new TH2D(Form("HSubJet2PTVsGenSubJet2PTOut%d%d", i, j),
            Form("%s;subjet2 PT;gen PT2", Title), 500, 0, 500, 500, 0, 500);
         HSubJet1DPTVsSubJet2DPTOut[i][j] = new TH2D(Form("HSubJet1DPTVsSubJet2DPTOut%d%d", i, j),
            Form("%s;subjet1 PT reco - gen;subjet2 PT reco - gen", Title), 200, -100, 100, 200, -100, 100);
         HSumPTVsGenSubJet1PTOut[i][j] = new TH2D(Form("HSumPTVsGenSubJet1PTOut%d%d", i, j),
            Form("%s;Sum PT;gen PT1", Title), 500, 0, 500, 500, 0, 500);
         HSubJetAverageXVsSubJetAverageYOut[i][j] = new TH2D(Form("HSubJetAverageXVsSubJetAverageYOut%d%d", i, j),
            Form("%s;Average x;Average y", Title), 100, -2.5, 2.5, 100, -2.5, 2.5);
      }
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);
      
      double Centrality = GetCentrality(MHiEvent.hiBin);

      SDJetHelper HSDJet(MSDJet);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.JetPT[i] < 80 || MSDJet.JetPT[i] > 500)
            continue;
         if(MSDJet.JetEta[i] < -1.3 || MSDJet.JetEta[i] > 1.3)
            continue;

         if(HSDJet.GoodRecoSubJet[i] == false)
            continue;
         if(HSDJet.GoodGenSubJet[i] == false)
            continue;

         if(HSDJet.Region[i] != 2)   // we want region II for this study
            continue;

         int CIndex = 0;
         for(int j = 0; j < 5; j++)
            if(Centrality >= CBinMin[j] && Centrality < CBinMin[j+1])
               CIndex = j;
         int PIndex = 0;
         for(int j = 0; j < 7; j++)
            if(MSDJet.JetPT[i] >= PTBinMin[j] && MSDJet.JetPT[i] < PTBinMin[j+1])
               PIndex = j;

         double GenWeightedX = (1 * HSDJet.GenSubJet1[i].GetPT() + (-1) * HSDJet.GenSubJet2[i].GetPT())
            / (HSDJet.GenSubJet1[i].GetPT() + HSDJet.GenSubJet2[i].GetPT());

         bool Inside = false;
         if((HSDJet.SubJetX2[i] - 1) * (HSDJet.SubJetX2[i] - 1) + HSDJet.SubJetY2[i] * HSDJet.SubJetY2[i] < 2 * 2)
            Inside = true;
         if((HSDJet.SubJetX2[i] + 1) * (HSDJet.SubJetX2[i] + 1) + HSDJet.SubJetY2[i] * HSDJet.SubJetY2[i] < 2 * 2)
            Inside = true;

         double AverageX = (HSDJet.SubJetX1[i] * HSDJet.RecoSubJet1[i].GetPT() + HSDJet.SubJetX2[i] * HSDJet.RecoSubJet2[i].GetPT()) / (HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT());
         double AverageY = (HSDJet.SubJetY1[i] * HSDJet.RecoSubJet1[i].GetPT() + HSDJet.SubJetY2[i] * HSDJet.RecoSubJet2[i].GetPT()) / (HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT());

         HSubJet1Location[CIndex][PIndex]->Fill(HSDJet.SubJetX1[i], HSDJet.SubJetY1[i]);
         HSubJet2Location[CIndex][PIndex]->Fill(HSDJet.SubJetX2[i], HSDJet.SubJetY2[i]);
         if(Inside == true)
         {
            HSubJet1XVsGenWeightedXIn[CIndex][PIndex]->Fill(HSDJet.SubJetX1[i], GenWeightedX);
            HSubJet1PTVsGenSumPTIn[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT() + HSDJet.GenSubJet2[i].GetPT());
            HSubJet1PTVsGenSubJet1PTIn[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT());
            HSubJet2PTVsGenSubJet2PTIn[CIndex][PIndex]->Fill(HSDJet.RecoSubJet2[i].GetPT(),
               HSDJet.GenSubJet2[i].GetPT());
            HSubJet1DPTVsSubJet2DPTIn[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT() - HSDJet.GenSubJet1[i].GetPT(),
               HSDJet.RecoSubJet2[i].GetPT() - HSDJet.GenSubJet2[i].GetPT());
            HSumPTVsGenSubJet1PTIn[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT());
            HSubJetAverageXVsSubJetAverageYIn[CIndex][PIndex]->Fill(AverageX, AverageY);
         }
         else
         {
            HSubJet1XVsGenWeightedXOut[CIndex][PIndex]->Fill(HSDJet.SubJetX1[i], GenWeightedX);
            HSubJet1PTVsGenSumPTOut[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT() + HSDJet.GenSubJet2[i].GetPT());
            HSubJet1PTVsGenSubJet1PTOut[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT());
            HSubJet2PTVsGenSubJet2PTOut[CIndex][PIndex]->Fill(HSDJet.RecoSubJet2[i].GetPT(),
               HSDJet.GenSubJet2[i].GetPT());
            HSubJet1DPTVsSubJet2DPTOut[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT() - HSDJet.GenSubJet1[i].GetPT(),
               HSDJet.RecoSubJet2[i].GetPT() - HSDJet.GenSubJet2[i].GetPT());
            HSumPTVsGenSubJet1PTOut[CIndex][PIndex]->Fill(HSDJet.RecoSubJet1[i].GetPT() + HSDJet.RecoSubJet2[i].GetPT(),
               HSDJet.GenSubJet1[i].GetPT());
            HSubJetAverageXVsSubJetAverageYOut[CIndex][PIndex]->Fill(AverageX, AverageY);
         }
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 7; j++)
      {
         if(HSubJet1Location[i][j] != NULL)   HSubJet1Location[i][j]->Write();
         if(HSubJet2Location[i][j] != NULL)   HSubJet2Location[i][j]->Write();
         if(HSubJet1XVsGenWeightedXIn[i][j] != NULL)   HSubJet1XVsGenWeightedXIn[i][j]->Write();
         if(HSubJet1PTVsGenSumPTIn[i][j] != NULL)   HSubJet1PTVsGenSumPTIn[i][j]->Write();
         if(HSubJet1PTVsGenSubJet1PTIn[i][j] != NULL)   HSubJet1PTVsGenSubJet1PTIn[i][j]->Write();
         if(HSubJet2PTVsGenSubJet2PTIn[i][j] != NULL)   HSubJet2PTVsGenSubJet2PTIn[i][j]->Write();
         if(HSubJet1DPTVsSubJet2DPTIn[i][j] != NULL)   HSubJet1DPTVsSubJet2DPTIn[i][j]->Write();
         if(HSumPTVsGenSubJet1PTIn[i][j] != NULL)   HSumPTVsGenSubJet1PTIn[i][j]->Write();
         if(HSubJetAverageXVsSubJetAverageYIn[i][j] != NULL)   HSubJetAverageXVsSubJetAverageYIn[i][j]->Write();
         if(HSubJet1XVsGenWeightedXOut[i][j] != NULL)   HSubJet1XVsGenWeightedXOut[i][j]->Write();
         if(HSubJet1PTVsGenSumPTOut[i][j] != NULL)   HSubJet1PTVsGenSumPTOut[i][j]->Write();
         if(HSubJet1PTVsGenSubJet1PTOut[i][j] != NULL)   HSubJet1PTVsGenSubJet1PTOut[i][j]->Write();
         if(HSubJet2PTVsGenSubJet2PTOut[i][j] != NULL)   HSubJet2PTVsGenSubJet2PTOut[i][j]->Write();
         if(HSubJet1DPTVsSubJet2DPTOut[i][j] != NULL)   HSubJet1DPTVsSubJet2DPTOut[i][j]->Write();
         if(HSumPTVsGenSubJet1PTOut[i][j] != NULL)   HSumPTVsGenSubJet1PTOut[i][j]->Write();
         if(HSubJetAverageXVsSubJetAverageYOut[i][j] != NULL)   HSubJetAverageXVsSubJetAverageYOut[i][j]->Write();

         if(HSubJet1Location[i][j] != NULL)   delete HSubJet1Location[i][j];
         if(HSubJet2Location[i][j] != NULL)   delete HSubJet2Location[i][j];
         if(HSubJet1XVsGenWeightedXIn[i][j] != NULL)   delete HSubJet1XVsGenWeightedXIn[i][j];
         if(HSubJet1PTVsGenSumPTIn[i][j] != NULL)   delete HSubJet1PTVsGenSumPTIn[i][j];
         if(HSubJet1PTVsGenSubJet1PTIn[i][j] != NULL)   delete HSubJet1PTVsGenSubJet1PTIn[i][j];
         if(HSubJet2PTVsGenSubJet2PTIn[i][j] != NULL)   delete HSubJet2PTVsGenSubJet2PTIn[i][j];
         if(HSubJet1DPTVsSubJet2DPTIn[i][j] != NULL)   delete HSubJet1DPTVsSubJet2DPTIn[i][j];
         if(HSumPTVsGenSubJet1PTIn[i][j] != NULL)   delete HSumPTVsGenSubJet1PTIn[i][j];
         if(HSubJetAverageXVsSubJetAverageYIn[i][j] != NULL)   delete HSubJetAverageXVsSubJetAverageYIn[i][j];
         if(HSubJet1XVsGenWeightedXOut[i][j] != NULL)   delete HSubJet1XVsGenWeightedXOut[i][j];
         if(HSubJet1PTVsGenSumPTOut[i][j] != NULL)   delete HSubJet1PTVsGenSumPTOut[i][j];
         if(HSubJet1PTVsGenSubJet1PTOut[i][j] != NULL)   delete HSubJet1PTVsGenSubJet1PTOut[i][j];
         if(HSubJet2PTVsGenSubJet2PTOut[i][j] != NULL)   delete HSubJet2PTVsGenSubJet2PTOut[i][j];
         if(HSubJet1DPTVsSubJet2DPTOut[i][j] != NULL)   delete HSubJet1DPTVsSubJet2DPTOut[i][j];
         if(HSumPTVsGenSubJet1PTOut[i][j] != NULL)   delete HSumPTVsGenSubJet1PTOut[i][j];
         if(HSubJetAverageXVsSubJetAverageYOut[i][j] != NULL)   delete HSubJetAverageXVsSubJetAverageYOut[i][j];
      }
   }

   OutputFile.Close();

   InputFile.Close();
}

double CalculateDR(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
   if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
   return sqrt(DEta * DEta + DPhi * DPhi);
}





