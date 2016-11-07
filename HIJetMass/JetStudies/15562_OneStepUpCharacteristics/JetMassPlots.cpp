#include <iostream>
#include <iomanip>
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
#include "CATree.h"

int main(int argc, char *argv[]);

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
   string PFTreeName = "pfcandAnalyzerCS/pfTree";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   GenParticleTreeMessenger MGen(InputFile);
   PFTreeMessenger MPF(InputFile);

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

   TH2D HGenMatchingQuality1("HGenMatchingQuality1", ";x;y", 100, -2, 2, 100, -2, 2);
   TH2D HGenMatchingQuality2("HGenMatchingQuality2", ";x;y", 100, -2, 2, 100, -2, 2);
   TH2D HRecoMatchingQuality1("HRecoMatchingQuality1", ";x;y", 100, -2, 2, 100, -2, 2);
   TH2D HRecoMatchingQuality2("HRecoMatchingQuality2", ";x;y", 100, -2, 2, 100, -2, 2);
   
   TH2D HGenMatchingDistance("HGenMatchingDistance", ";dist 1;dist 2", 100, 0, 1, 100, 0, 1);
   TH2D HRecoMatchingDistance("HRecoMatchingDistance", ";dist 1;dist 2", 100, 0, 1, 100, 0, 1);

   TH2D HGenMatchedPT("HGenMatchedPT", ";PT1 Ratio;PT2 Ratio", 100, 0, 2, 100, 0, 2);
   TH2D HRecoMatchedPT("HRecoMatchedPT", ";PT1 Ratio;PT2 Ratio", 100, 0, 2, 100, 0, 2);

   TH2D HSubJet1PTRatioVsSubJet2PTRatio("HSubJet1PTRatioVsSubJet2PTRatio",
      ";reco/gen 1;reco/gen 2", 100, 0, 2, 100, 0, 2);
   TH2D HRecoSubJet1PTVsTotalGenPT("HRecoSubJet1PTVsTotalGenPT",
      ";reco 1;gen 1 + gen 2", 100, 0, 200, 100, 0, 200);
   TH2D HTotalRecoPTVsTotalGenPT("HTotalRecoPTVsTotalGenPT",
      ";reco 1 + reco 2;gen 1 + gen 2", 100, 0, 200, 100, 0, 200);
   TH2D HRecoSubJet1XVsGenAverageX("HRecoSubJet1XVsGenAverageX",
      ";reco 1 x;gen average x", 100, -2, 2, 100, -2, 2);

   TH2D HReco1OneUpXY("HReco1OneUpXY", ";x;y", 100, -2, 2, 100, -2, 2);
   TH2D HReco2OneUpXY("HReco2OneUpXY", ";x;y", 200, -4, 4, 200, -4, 4);

   TH2D HReco2OneUpDistanceVsCentrality("HReco2OneUpDistanceVsCentrality",
      ";centrality;reco 2 one up distance", 100, 0, 1, 100, 0, 10);
   TH2D HReco2OneUpDistanceVsJetPT("HReco2OneUpDistanceVsJetPT",
      ";JetPT;reco 2 one up distance", 100, 80, 500, 100, 0, 10);
   TH2D HReco2OneUpDistanceVsJetEta("HReco2OneUpDistanceVsJetEta",
      ";JetEta;reco 2 one up distance", 100, -1.5, 1.5, 100, 0, 10);
   
   TProfile PGoodReco2OneUpVsCentrality("PGoodReco2OneUpVsCentrality",
      ";centrality;P(reco 2 one up distance < 1.0)", 100, 0, 1);
   TProfile PGoodReco2OneUpVsJetPT("PGoodReco2OneUpVsJetPT",
      ";JetPT;P(reco 2 one up distance < 1.0)", 100, 80, 500);
   TProfile PGoodReco2OneUpVsJetEta("PGoodReco2OneUpVsJetEta",
      ";JetEta;P(reco 2 one up distance < 1.0)", 100, -1.5, 1.5);

   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 7; j++)
      {
         char Title[1024] = "";
         sprintf(Title, "C %.0f%%-%.0f%%, PT %.0f-%.0f", CBinMin[i] * 100, CBinMin[i+1] * 100,
            PTBinMin[j], PTBinMin[j+1]);
      }
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MGen.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      
      SDJetHelper HSDJet(MSDJet);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);
      
      double Centrality = GetCentrality(MHiEvent.hiBin);

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
         if(HSDJet.Inside[i] == true)   // we want outside jets
            continue;

         int CIndex = GetIndex(Centrality, CBinMin, CBinMin + 6);
         int PIndex = GetIndex(MSDJet.JetPT[i], PTBinMin, PTBinMin + 8);
         if(CIndex >= 5)  CIndex = 4;
         if(PIndex >= 7)  PIndex = 6;

         vector<Node *> GenNodes;
         vector<Node *> RecoNodes;

         for(int j = 0; j < (int)(*MGen.PT).size(); j++)
         {
            int ID = (*MGen.ID)[j];
            if(ID < 0)
               ID = -ID;
            if(ID == 12 || ID == 14 || ID == 16)
               continue;
            
            double DR = GetDR(MSDJet.JetEta[i], MSDJet.JetPhi[i], (*MGen.Eta)[j], (*MGen.Phi)[j]);
            if(DR < 0.4)
            {
               FourVector P;
               P.SetPtEtaPhi((*MGen.PT)[j], (*MGen.Eta)[j], (*MGen.Phi)[j]);
               GenNodes.push_back(new Node(P));
            }
         }
         for(int j = 0; j < (int)(*MPF.PT).size(); j++)
         {
            double DR = GetDR(MSDJet.JetEta[i], MSDJet.JetPhi[i], (*MPF.Eta)[j], (*MPF.Phi)[j]);
            if(DR < 0.4)
            {
               FourVector P;
               P.SetPtEtaPhi((*MPF.PT)[j], (*MPF.Eta)[j], (*MPF.Phi)[j]);
               P[0] = (*MPF.E)[j];
               RecoNodes.push_back(new Node(P));
            }
         }

         BuildCATree(GenNodes);
         BuildCATree(RecoNodes);

         Node *GroomedGen = FindSDNode(GenNodes[0]);
         Node *GroomedReco = FindSDNode(RecoNodes[0]);

         if(GroomedGen == NULL || GroomedReco == NULL
            || GroomedGen->N == 1 || GroomedReco->N == 1)
         {
            delete GenNodes[0];
            delete RecoNodes[0];
            continue;
         }

         XY GenMean;    GenMean.SetAsAverage(HSDJet.GenSubJet1[i], HSDJet.GenSubJet2[i]);
         XY RecoMean;   RecoMean.SetAsAverage(HSDJet.RecoSubJet1[i], HSDJet.RecoSubJet2[i]);

         Matrix22 GenMatrix(HSDJet.GenSubJet1[i], HSDJet.GenSubJet2[i]);
         Matrix22 RecoMatrix(HSDJet.RecoSubJet1[i], HSDJet.RecoSubJet2[i]);

         XY GenSDJet1(GenMatrix, GenMean, GroomedGen->Child1->P);
         XY GenSDJet2(GenMatrix, GenMean, GroomedGen->Child2->P);
         XY RecoSDJet1(RecoMatrix, RecoMean, GroomedReco->Child1->P);
         XY RecoSDJet2(RecoMatrix, RecoMean, GroomedReco->Child2->P);

         HGenMatchingQuality1.Fill(GenSDJet1.X, GenSDJet1.Y);
         HGenMatchingQuality2.Fill(GenSDJet2.X, GenSDJet2.Y);
         HRecoMatchingQuality1.Fill(RecoSDJet1.X, RecoSDJet1.Y);
         HRecoMatchingQuality2.Fill(RecoSDJet2.X, RecoSDJet2.Y);

         double GenMatchingDistance1 = (GenSDJet1 - XY(1, 0)).Norm();
         double GenMatchingDistance2 = (GenSDJet2 - XY(-1, 0)).Norm();
         double RecoMatchingDistance1 = (RecoSDJet1 - XY(1, 0)).Norm();
         double RecoMatchingDistance2 = (RecoSDJet2 - XY(-1, 0)).Norm();

         HGenMatchingDistance.Fill(GenMatchingDistance1, GenMatchingDistance2);
         HRecoMatchingDistance.Fill(RecoMatchingDistance1, RecoMatchingDistance2);

         if(GenMatchingDistance1 > 0.05 || GenMatchingDistance2 > 0.05
            || RecoMatchingDistance1 > 0.1 || RecoMatchingDistance2 > 0.1)
         {
            delete GenNodes[0];
            delete RecoNodes[0];
            continue;
         }

         double GenPTRatio1 = GroomedGen->Child1->P.GetPT() / HSDJet.GenSubJet1[i].GetPT();
         double GenPTRatio2 = GroomedGen->Child2->P.GetPT() / HSDJet.GenSubJet2[i].GetPT();
         double RecoPTRatio1 = GroomedReco->Child1->P.GetPT() / HSDJet.RecoSubJet1[i].GetPT();
         double RecoPTRatio2 = GroomedReco->Child2->P.GetPT() / HSDJet.RecoSubJet2[i].GetPT();

         HGenMatchedPT.Fill(GenPTRatio1, GenPTRatio2);
         HRecoMatchedPT.Fill(RecoPTRatio1, RecoPTRatio2);

         if(GenPTRatio1 < 0.95 || GenPTRatio1 > 1.05 || GenPTRatio2 < 0.95 || GenPTRatio2 > 1.05
            || RecoPTRatio1 < 0.95 || RecoPTRatio1 > 1.05 || RecoPTRatio2 < 0.95 || RecoPTRatio2 > 1.05)
         {
            delete GenNodes[0];
            delete RecoNodes[0];
            continue;
         }

         FourVector G1 = GroomedGen->Child1->P;
         FourVector G2 = GroomedGen->Child2->P;
         FourVector R1 = GroomedReco->Child1->P;
         FourVector R2 = GroomedReco->Child2->P;

         HSubJet1PTRatioVsSubJet2PTRatio.Fill(R1.GetPT() / G1.GetPT(), R2.GetPT() / G2.GetPT());
         HRecoSubJet1PTVsTotalGenPT.Fill(R1.GetPT(), G1.GetPT() + G2.GetPT());
         HTotalRecoPTVsTotalGenPT.Fill(R1.GetPT() + R2.GetPT(), G1.GetPT() + G2.GetPT());
         HRecoSubJet1XVsGenAverageX.Fill(HSDJet.SubJetX1[i], HSDJet.GenWeightedX[i]);

         if(GroomedGen->Parent == NULL)
         {
            delete GenNodes[0];
            delete RecoNodes[0];

            continue;
         }

         Node *OneUpGen = GroomedGen->Parent;

         XY OneUpGenMean;    OneUpGenMean.SetAsAverage(OneUpGen->Child1->P, OneUpGen->Child2->P);
         Matrix22 OneUpGenMatrix(OneUpGen->Child1->P, OneUpGen->Child2->P);

         XY Reco1OneUpXY(OneUpGenMatrix, OneUpGenMean, GroomedReco->Child1->P);
         XY Reco2OneUpXY(OneUpGenMatrix, OneUpGenMean, GroomedReco->Child2->P);

         double Reco2OneUpDistance = (Reco2OneUpXY - XY(-1, 0)).Norm();

         HReco1OneUpXY.Fill(Reco1OneUpXY.X, Reco1OneUpXY.Y);
         HReco2OneUpXY.Fill(Reco2OneUpXY.X, Reco2OneUpXY.Y);
         HReco2OneUpDistanceVsCentrality.Fill(Centrality,   Reco2OneUpDistance);
         HReco2OneUpDistanceVsJetPT.Fill(MSDJet.JetPT[i],   Reco2OneUpDistance);
         HReco2OneUpDistanceVsJetEta.Fill(MSDJet.JetEta[i], Reco2OneUpDistance);
         PGoodReco2OneUpVsCentrality.Fill(Centrality,       ((Reco2OneUpDistance < 1.0) ? 1 : 0));
         PGoodReco2OneUpVsJetPT.Fill(MSDJet.JetPT[i],       ((Reco2OneUpDistance < 1.0) ? 1 : 0));
         PGoodReco2OneUpVsJetEta.Fill(MSDJet.JetEta[i],     ((Reco2OneUpDistance < 1.0) ? 1 : 0));

         delete GenNodes[0];
         delete RecoNodes[0];
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   HGenMatchingQuality1.Write();
   HGenMatchingQuality2.Write();
   HRecoMatchingQuality1.Write();
   HRecoMatchingQuality2.Write();

   HGenMatchingDistance.Write();
   HRecoMatchingDistance.Write();

   HGenMatchedPT.Write();
   HRecoMatchedPT.Write();

   HSubJet1PTRatioVsSubJet2PTRatio.Write();
   HRecoSubJet1PTVsTotalGenPT.Write();
   HTotalRecoPTVsTotalGenPT.Write();
   HRecoSubJet1XVsGenAverageX.Write();

   HReco1OneUpXY.Write();
   HReco2OneUpXY.Write();
   HReco2OneUpDistanceVsCentrality.Write();
   HReco2OneUpDistanceVsJetPT.Write();
   HReco2OneUpDistanceVsJetEta.Write();
   PGoodReco2OneUpVsCentrality.Write();
   PGoodReco2OneUpVsJetPT.Write();
   PGoodReco2OneUpVsJetEta.Write();

   // for(int i = 0; i < 5; i++)
   // {
   //    for(int j = 0; j < 7; j++)
   //    {
   //       if(HGenMatchingQuality[i][j] != NULL)   HGenMatchingQuality[i][j]->Write();
   //
   //       if(HGenMatchingQuality[i][j] != NULL)   delete HGenMatchingQuality[i][j];
   //    }
   // }

   OutputFile.Close();

   InputFile.Close();
}

