#include "include/Messenger.h"
#include "include/SDJetHelper.h"
   
SDJetHelper::SDJetHelper(JetTreeMessenger &MJet)
{
   Initialize(MJet);
}

SDJetHelper::~SDJetHelper()
{
}

bool SDJetHelper::Initialize(JetTreeMessenger &MJet)
{
   RecoSubJet1.resize(MJet.JetCount);
   RecoSubJet2.resize(MJet.JetCount);
   GoodRecoSubJet.resize(MJet.JetCount);
   RecoSubJetDR.resize(MJet.JetCount);

   GenSubJet1.resize(MJet.JetCount);
   GenSubJet2.resize(MJet.JetCount);
   GoodGenSubJet.resize(MJet.JetCount);
   GenSubJetDR.resize(MJet.JetCount);

   SubJetMaxDR.resize(MJet.JetCount);
   SubJetSumDR.resize(MJet.JetCount);
   Region.resize(MJet.JetCount);
   SubJetX1.resize(MJet.JetCount);
   SubJetY1.resize(MJet.JetCount);
   SubJetX2.resize(MJet.JetCount);
   SubJetY2.resize(MJet.JetCount);
   GenWeightedX.resize(MJet.JetCount);
   AverageX.resize(MJet.JetCount);
   AverageY.resize(MJet.JetCount);
   Inside.resize(MJet.JetCount);

   for(int i = 0; i < MJet.JetCount; i++)
   {
      if(MJet.JetSubJetPT == NULL || MJet.JetSubJetPT->size() < MJet.JetCount || (*MJet.JetSubJetPT)[i].size() < 2)
      {
         RecoSubJet1[i] = FourVector(0, 0, 0, 0);
         RecoSubJet2[i] = FourVector(0, 0, 0, 0);
         GoodRecoSubJet[i] = false;
         RecoSubJetDR[i] = -1;
      }
      else
      {
         RecoSubJet1[i].SetPtEtaPhiMass((*MJet.JetSubJetPT)[i][0], (*MJet.JetSubJetEta)[i][0],
            (*MJet.JetSubJetPhi)[i][0], (*MJet.JetSubJetM)[i][0]);
         RecoSubJet2[i].SetPtEtaPhiMass((*MJet.JetSubJetPT)[i][1], (*MJet.JetSubJetEta)[i][1],
            (*MJet.JetSubJetPhi)[i][1], (*MJet.JetSubJetM)[i][1]);
         GoodRecoSubJet[i] = true;
         RecoSubJetDR[i] = GetDR(RecoSubJet1[i], RecoSubJet2[i]);
      }
      
      if(MJet.RefGSubJetPT == NULL || MJet.RefGSubJetPT->size() < MJet.JetCount || (*MJet.RefGSubJetPT)[i].size() < 2)
      {
         GenSubJet1[i] = FourVector(0, 0, 0, 0);
         GenSubJet2[i] = FourVector(0, 0, 0, 0);
         GoodGenSubJet[i] = false;
         GenSubJetDR[i] = -1;
      }
      else
      {
         GenSubJet1[i].SetPtEtaPhiMass((*MJet.RefGSubJetPT)[i][0], (*MJet.RefGSubJetEta)[i][0],
            (*MJet.RefGSubJetPhi)[i][0], (*MJet.RefGSubJetM)[i][0]);
         GenSubJet2[i].SetPtEtaPhiMass((*MJet.RefGSubJetPT)[i][1], (*MJet.RefGSubJetEta)[i][1],
            (*MJet.RefGSubJetPhi)[i][1], (*MJet.RefGSubJetM)[i][1]);
         GoodGenSubJet[i] = true;
         GenSubJetDR[i] = GetDR(GenSubJet1[i], GenSubJet2[i]);
      }

      if(GoodRecoSubJet[i] == false || GoodGenSubJet[i] == false)
      {
         SubJetMaxDR[i] = -1;
         SubJetSumDR[i] = -1;
         Region[i] = 0;
         SubJetX1[i] = 0;
         SubJetY1[i] = 0;
         SubJetX2[i] = 0;
         SubJetY2[i] = 0;
         GenWeightedX[i] = 0;
         AverageX[i] = 0;
         AverageY[i] = 0;
      }
      else
      {
         double DR11 = GetDR(GenSubJet1[i], RecoSubJet1[i]);
         double DR12 = GetDR(GenSubJet1[i], RecoSubJet2[i]);
         double DR21 = GetDR(GenSubJet2[i], RecoSubJet1[i]);
         double DR22 = GetDR(GenSubJet2[i], RecoSubJet2[i]);

         if(DR11 + DR22 < DR12 + DR21)
         {
            SubJetSumDR[i] = DR11 + DR22;
            SubJetMaxDR[i] = std::max(DR11, DR22);
         }
         else
         {
            SubJetSumDR[i] = DR12 + DR21;
            SubJetMaxDR[i] = std::max(DR12, DR21);
         }

         if(RecoSubJetDR[i] < 0.1)
            Region[i] = 3;
         else
         {
            if(SubJetMaxDR[i] > RecoSubJetDR[i] / 2)
               Region[i] = 2;
            else
               Region[i] = 1;
         }

         double DeltaEta = GenSubJet1[i].GetEta() - GenSubJet2[i].GetEta();
         double MeanEta = (GenSubJet1[i].GetEta() + GenSubJet2[i].GetEta()) / 2;
         double DeltaPhi = (GenSubJet1[i].GetPhi() - GenSubJet2[i].GetPhi());
         if(DeltaPhi < -PI)   DeltaPhi = DeltaPhi + 2 * PI;
         if(DeltaPhi > +PI)   DeltaPhi = DeltaPhi - 2 * PI;
         double MeanPhi = GenSubJet2[i].GetPhi() + DeltaPhi / 2;
         if(MeanPhi < -PI)   MeanPhi = MeanPhi + 2 * PI;
         if(MeanPhi > +PI)   MeanPhi = MeanPhi - 2 * PI;

         double M11 = DeltaEta / 2;
         double M12 = DeltaPhi / 2;
         double M21 = -DeltaPhi / 2;
         double M22 = DeltaEta / 2;

         double DetM = M11 * M22 - M12 * M21;

         double IM11 = M22 / DetM;
         double IM12 = -M21 / DetM;
         double IM21 = -M12 / DetM;
         double IM22 = M11 / DetM;

         double SubJetEta1 = RecoSubJet1[i].GetEta() - MeanEta;
         double SubJetPhi1 = RecoSubJet1[i].GetPhi() - MeanPhi;
         double SubJetEta2 = RecoSubJet2[i].GetEta() - MeanEta;
         double SubJetPhi2 = RecoSubJet2[i].GetPhi() - MeanPhi;
         if(SubJetPhi1 > +PI)   SubJetPhi1 = SubJetPhi1 - 2 * PI;
         if(SubJetPhi1 < -PI)   SubJetPhi1 = SubJetPhi1 + 2 * PI;
         if(SubJetPhi2 > +PI)   SubJetPhi2 = SubJetPhi2 - 2 * PI;
         if(SubJetPhi2 < -PI)   SubJetPhi2 = SubJetPhi2 + 2 * PI;

         SubJetX1[i] = IM11 * SubJetEta1 + IM12 * SubJetPhi1;
         SubJetY1[i] = IM21 * SubJetEta1 + IM22 * SubJetPhi1;
         SubJetX2[i] = IM11 * SubJetEta2 + IM12 * SubJetPhi2;
         SubJetY2[i] = IM21 * SubJetEta2 + IM22 * SubJetPhi2;

         GenWeightedX[i] = (1 * GenSubJet1[i].GetPT() + (-1) * GenSubJet2[i].GetPT())
            / (GenSubJet1[i].GetPT() + GenSubJet2[i].GetPT());

         AverageX[i] = (SubJetX1[i] * RecoSubJet1[i].GetPT() + SubJetX2[i] * RecoSubJet2[i].GetPT()) / (RecoSubJet1[i].GetPT() + RecoSubJet2[i].GetPT());
         AverageY[i] = (SubJetY1[i] * RecoSubJet1[i].GetPT() + SubJetY2[i] * RecoSubJet2[i].GetPT()) / (RecoSubJet1[i].GetPT() + RecoSubJet2[i].GetPT());

         Inside[i] = false;
         if((SubJetX2[i] - 1) * (SubJetX2[i] - 1) + SubJetY2[i] * SubJetY2[i] < 2 * 2)
            Inside[i] = true;
         if((SubJetX2[i] + 1) * (SubJetX2[i] + 1) + SubJetY2[i] * SubJetY2[i] < 2 * 2)
            Inside[i] = true;
      }
   }

   return true;
}
