#include <fstream>
#include <string>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TColor.h"

#include "GenparticleTree.h"
#include "TauHelperFunctions.h"
#include "PlotHelper.h"

int main(int argc, char *argv[]);
void BJetProfile(string InputMass);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   TStyle gStyle;
   
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);
   gStyle.SetOptStat("roumen");

   string InputMass = "350";
   if(argc > 1)
      InputMass = argv[1];
   BJetProfile(InputMass);

   return 0;
}

void BJetProfile(string InputMass)
{
   ifstream in(("Samples/LQ" + InputMass + "Sample").c_str());

   PsFileHelper PsFile(("PropertiesBJet_" + InputMass + "GeV.ps").c_str());
   PsFile.AddTextPage("Properties of b-jets (from LQ sample)");

   map<int, int> FinalPDGIDAndCount;

   TH1D HFinalParticleCountFromB("HFinalParticleCountFromB", "Final particle count from b jets", 350, -0.5, 349.5);

   TH1D HPhotonPTFraction("HPhotonPTFraction", "Photon PT fraction", 100, 0, 1);
   TH1D HPionPTFraction("HPionPTFraction", "Pion PT fraction", 100, 0, 1);
   TH1D HKaonPTFraction("HKaonPTFraction", "Kaon PT fraction", 100, 0, 1);
   TH1D HNucleonPTFraction("HNucleonPTFraction", "Nucleon PT fraction", 100, 0, 1);
   TH1D HLeptonPTFraction("HLeptonPTFraction", "Lepton (including neutrino) PT fraction", 100, 0, 1);
   TH1D HOtherPTFraction("HOtherPTFraction",
      "PT carried by other things (not photon, pion, kaon, neucleon, lepton)", 100, 0, 1);
   TH2D HPhotonPTFractionVsPT("HPhotonPTFractionVsPT", "Photon PT fraction;PT;Fraction", 100, 0, 500, 100, 0, 1);
   TH2D HPionPTFractionVsPT("HPionPTFractionVsPT", "Pion PT fraction;PT;Fraction", 100, 0, 500, 100, 0, 1);
   TH2D HKaonPTFractionVsPT("HKaonPTFractionVsPT", "Kaon PT fraction;PT;Fraction", 100, 0, 500, 100, 0, 1);
   TH2D HNucleonPTFractionVsPT("HNucleonPTFractionVsPT", "Nucleon PT fraction;PT;Fraction", 100, 0, 500, 100, 0, 1);
   TH2D HLeptonPTFractionVsPT("HLeptonPTFractionVsPT", "Lepton (including neutrino) PT fraction;PT;Fraction",
      100, 0, 500, 100, 0, 1);
   TH2D HOtherPTFractionVsPT("HOtherPTFractionVsPT",
      "PT carried by other things (not photon, pion, kaon, neucleon, lepton);PT;Fraction", 100, 0, 500, 100, 0, 1);

   // TH1D HBFlightDistance("HBFlightDistance", "Flight distance of b quark (cm?)", 100, 0, 100);
   // TH1D HBProperFlightDistance("HBProperFlightDistance", "Proper flight distance of b quark (cm?)", 100, 0, 100);

   TH1D H10PercentDR("H10PercentDR", "Minimal dR that enclosed 10\% of energy", 100, 0, 0.2);
   TH1D H20PercentDR("H20PercentDR", "Minimal dR that enclosed 20\% of energy", 100, 0, 0.2);
   TH1D H30PercentDR("H30PercentDR", "Minimal dR that enclosed 30\% of energy", 100, 0, 0.2);
   TH1D H40PercentDR("H40PercentDR", "Minimal dR that enclosed 40\% of energy", 100, 0, 0.2);
   TH1D H50PercentDR("H50PercentDR", "Minimal dR that enclosed 50\% of energy", 100, 0, 0.2);
   TH1D H60PercentDR("H60PercentDR", "Minimal dR that enclosed 60\% of energy", 100, 0, 0.2);
   TH1D H70PercentDR("H70PercentDR", "Minimal dR that enclosed 70\% of energy", 100, 0, 0.2);
   TH1D H80PercentDR("H80PercentDR", "Minimal dR that enclosed 80\% of energy", 100, 0, 0.2);
   TH1D H90PercentDR("H90PercentDR", "Minimal dR that enclosed 90\% of energy", 100, 0, 0.2);
   TH1D H100PercentDR("H100PercentDR", "Minimal dR that enclosed 100\% of energy", 100, 0, 1);

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);
   int EventCount = Helper.IntValue;

   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << EventCount << endl;

      GenParticleTree Tree;
      Tree.LoadFromStream(in, false);

      vector<int> BTemp = FindAllIndices(Tree, 5, -1);
      vector<int> BbarTemp = FindAllIndices(Tree, -5, -1);

      vector<int> BIndices;
      BIndices.insert(BIndices.end(), BTemp.begin(), BTemp.end());
      BIndices.insert(BIndices.end(), BbarTemp.begin(), BbarTemp.end());

      for(int i = 0; i < (int)BIndices.size(); i++)
      {
         bool HasLQAsMother = false;

         for(int j = 0; j < (int)Tree[BIndices[i]].Mothers.size(); j++)
            if(abs(Tree[Tree[BIndices[i]].Mothers[j]].PDGID) == 42)
               HasLQAsMother = true;

         if(HasLQAsMother == false)
         {
            BIndices.erase(BIndices.begin() + i);
            i = i - 1;
         }
      }

      for(int i = 0; i < (int)BIndices.size(); i++)
      {
         vector<int> AllChildren = TraceChildren(Tree, BIndices[i]);
         vector<int> AllStableChildren = KeepStableParticle(Tree, AllChildren);

         HFinalParticleCountFromB.Fill(AllStableChildren.size());

         if(AllStableChildren.size() == 0)   // something is wrong with the b
            continue;

         // Check final particle PDGID
         for(int j = 0; j < (int)AllStableChildren.size(); j++)
         {
            int PDGID = Tree[AllStableChildren[j]].PDGID;
            if(FinalPDGIDAndCount.find(PDGID) == FinalPDGIDAndCount.end())
               FinalPDGIDAndCount.insert(pair<int, int>(PDGID, 1));
            else
               FinalPDGIDAndCount[PDGID] = FinalPDGIDAndCount[PDGID] + 1;
         }

         // PT Fractions from photons and pions
         const double *BP = Tree[BIndices[i]].P;
         double PhotonTotalP[4] = {0, 0, 0, 0};
         double PionTotalP[4] = {0, 0, 0, 0};
         double KaonTotalP[4] = {0, 0, 0, 0};
         double NucleonTotalP[4] = {0, 0, 0, 0};
         double LeptonTotalP[4] = {0, 0, 0, 0};
         double OtherTotalP[4] = {0, 0, 0, 0};

         for(int j = 0; j < (int)AllStableChildren.size(); j++)
         {
            int PDGID = Tree[AllStableChildren[j]].PDGID;

            if(PDGID == 22)
            {
               PhotonTotalP[0] = PhotonTotalP[0] + Tree[AllStableChildren[j]].P[0];
               PhotonTotalP[1] = PhotonTotalP[1] + Tree[AllStableChildren[j]].P[1];
               PhotonTotalP[2] = PhotonTotalP[2] + Tree[AllStableChildren[j]].P[2];
               PhotonTotalP[3] = PhotonTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
            else if(PDGID == 211 || PDGID == -211)
            {
               PionTotalP[0] = PionTotalP[0] + Tree[AllStableChildren[j]].P[0];
               PionTotalP[1] = PionTotalP[1] + Tree[AllStableChildren[j]].P[1];
               PionTotalP[2] = PionTotalP[2] + Tree[AllStableChildren[j]].P[2];
               PionTotalP[3] = PionTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
            else if(PDGID == 321 || PDGID == -321 || PDGID == 130 || PDGID == 310)
            {
               KaonTotalP[0] = KaonTotalP[0] + Tree[AllStableChildren[j]].P[0];
               KaonTotalP[1] = KaonTotalP[1] + Tree[AllStableChildren[j]].P[1];
               KaonTotalP[2] = KaonTotalP[2] + Tree[AllStableChildren[j]].P[2];
               KaonTotalP[3] = KaonTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
            else if(PDGID == 2112 || PDGID == 2212 || PDGID == -2112 || PDGID == -2212)
            {
               NucleonTotalP[0] = NucleonTotalP[0] + Tree[AllStableChildren[j]].P[0];
               NucleonTotalP[1] = NucleonTotalP[1] + Tree[AllStableChildren[j]].P[1];
               NucleonTotalP[2] = NucleonTotalP[2] + Tree[AllStableChildren[j]].P[2];
               NucleonTotalP[3] = NucleonTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
            else if(PDGID >= -16 && PDGID <= 16)
            {
               LeptonTotalP[0] = LeptonTotalP[0] + Tree[AllStableChildren[j]].P[0];
               LeptonTotalP[1] = LeptonTotalP[1] + Tree[AllStableChildren[j]].P[1];
               LeptonTotalP[2] = LeptonTotalP[2] + Tree[AllStableChildren[j]].P[2];
               LeptonTotalP[3] = LeptonTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
            else
            {
               OtherTotalP[0] = OtherTotalP[0] + Tree[AllStableChildren[j]].P[0];
               OtherTotalP[1] = OtherTotalP[1] + Tree[AllStableChildren[j]].P[1];
               OtherTotalP[2] = OtherTotalP[2] + Tree[AllStableChildren[j]].P[2];
               OtherTotalP[3] = OtherTotalP[3] + Tree[AllStableChildren[j]].P[3];
            }
         }

         HPhotonPTFraction.Fill(GetPT(PhotonTotalP) / GetPT(BP));
         HPionPTFraction.Fill(GetPT(PionTotalP) / GetPT(BP));
         HKaonPTFraction.Fill(GetPT(KaonTotalP) / GetPT(BP));
         HNucleonPTFraction.Fill(GetPT(NucleonTotalP) / GetPT(BP));
         HLeptonPTFraction.Fill(GetPT(LeptonTotalP) / GetPT(BP));
         HOtherPTFraction.Fill(GetPT(OtherTotalP) / GetPT(BP));

         HPhotonPTFractionVsPT.Fill(GetPT(BP), GetPT(PhotonTotalP) / GetPT(BP));
         HPionPTFractionVsPT.Fill(GetPT(BP), GetPT(PionTotalP) / GetPT(BP));
         HKaonPTFractionVsPT.Fill(GetPT(BP), GetPT(KaonTotalP) / GetPT(BP));
         HNucleonPTFractionVsPT.Fill(GetPT(BP), GetPT(NucleonTotalP) / GetPT(BP));
         HLeptonPTFractionVsPT.Fill(GetPT(BP), GetPT(LeptonTotalP) / GetPT(BP));
         HOtherPTFractionVsPT.Fill(GetPT(BP), GetPT(OtherTotalP) / GetPT(BP));

         // flight distance
         // double FlightDistance = 0;
         // const double *ProductionV = Tree[BIndices[i]].V;
         // const double *DecayV = Tree[Tree[BIndices[i]].Daughters[0]].V;
         // double Duration[4] = {DecayV[0] - ProductionV[0], DecayV[1] - ProductionV[1],
         //    DecayV[2] - ProductionV[2], DecayV[3] - ProductionV[3]};
         //
         // HBFlightDistance.Fill(GetP(Duration));
         // HBProperFlightDistance.Fill(GetMass(Duration));

         // Transverse profile
         vector<GenParticle> ChildrenSortedByDR;
         for(int j = 0; j < (int)AllStableChildren.size(); j++)
            ChildrenSortedByDR.push_back(Tree[AllStableChildren[j]]);
         sort(ChildrenSortedByDR.begin(), ChildrenSortedByDR.end(), GenParticle::SortByDR(GetEta(BP), GetPhi(BP)));

         double PSoFar[4] = {0, 0, 0, 0};
         bool Passed10Percent = false;
         bool Passed20Percent = false;
         bool Passed30Percent = false;
         bool Passed40Percent = false;
         bool Passed50Percent = false;
         bool Passed60Percent = false;
         bool Passed70Percent = false;
         bool Passed80Percent = false;
         bool Passed90Percent = false;
         bool Passed100Percent = false;

         for(int j = 0; j < (int)ChildrenSortedByDR.size(); j++)
         {
            if(ChildrenSortedByDR[j].PDGID == 12 || ChildrenSortedByDR[j].PDGID == -12)
               continue;
            if(ChildrenSortedByDR[j].PDGID == 14 || ChildrenSortedByDR[j].PDGID == -14)
               continue;
            if(ChildrenSortedByDR[j].PDGID == 16 || ChildrenSortedByDR[j].PDGID == -16)
               continue;

            PSoFar[0] = PSoFar[0] + ChildrenSortedByDR[j].P[0];
            PSoFar[1] = PSoFar[1] + ChildrenSortedByDR[j].P[1];
            PSoFar[2] = PSoFar[2] + ChildrenSortedByDR[j].P[2];
            PSoFar[3] = PSoFar[3] + ChildrenSortedByDR[j].P[3];

            double Percentage = GetPT(PSoFar) / GetPT(BP);

            if(Passed10Percent == false && Percentage >= 0.1)
            {
               Passed10Percent = true;
               H10PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed20Percent == false && Percentage >= 0.2)
            {
               Passed20Percent = true;
               H20PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed30Percent == false && Percentage >= 0.3)
            {
               Passed30Percent = true;
               H30PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed40Percent == false && Percentage >= 0.4)
            {
               Passed40Percent = true;
               H40PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed50Percent == false && Percentage >= 0.5)
            {
               Passed50Percent = true;
               H50PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed60Percent == false && Percentage >= 0.6)
            {
               Passed60Percent = true;
               H60PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed70Percent == false && Percentage >= 0.7)
            {
               Passed70Percent = true;
               H70PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed80Percent == false && Percentage >= 0.8)
            {
               Passed80Percent = true;
               H80PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed90Percent == false && Percentage >= 0.9)
            {
               Passed90Percent = true;
               H90PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
            if(Passed100Percent == false && Percentage >= 1)
            {
               Passed100Percent = true;
               H100PercentDR.Fill(GetDR(ChildrenSortedByDR[j].P, BP));
            }
         }
      }
   }

   PsFile.AddPlot(HFinalParticleCountFromB, "", true);

   PsFile.AddTextPage("PT Fractions");
   PsFile.AddPlot(HPhotonPTFraction, "", true);
   PsFile.AddPlot(HPionPTFraction, "", true);
   PsFile.AddPlot(HKaonPTFraction, "", true);
   PsFile.AddPlot(HNucleonPTFraction, "", true);
   PsFile.AddPlot(HLeptonPTFraction, "", true);
   PsFile.AddPlot(HOtherPTFraction, "", true);

   PsFile.AddPlot(HPhotonPTFractionVsPT, "colz", false);
   PsFile.AddPlot(HPionPTFractionVsPT, "colz", false);
   PsFile.AddPlot(HKaonPTFractionVsPT, "colz", false);
   PsFile.AddPlot(HNucleonPTFractionVsPT, "colz", false);
   PsFile.AddPlot(HLeptonPTFractionVsPT, "colz", false);
   PsFile.AddPlot(HOtherPTFractionVsPT, "colz", false);

   vector<string> FlightDistanceExplanation;
   FlightDistanceExplanation.push_back("Since it's bare b in the gen-level distribution,");
   FlightDistanceExplanation.push_back("      it is not clear how to define the \"flight distance\"");
   FlightDistanceExplanation.push_back("Skipped for now until I have a better look at the");
   FlightDistanceExplanation.push_back("      MC information.");
   
   PsFile.AddTextPage("Flight distance");
   PsFile.AddTextPage(FlightDistanceExplanation);
   // PsFile.AddPlot(HBFlightDistance, "", true);
   // PsFile.AddPlot(HBProperFlightDistance, "", true);

   PsFile.AddTextPage("Transverse profile");
   PsFile.AddPlot(H10PercentDR, "", true);
   PsFile.AddPlot(H20PercentDR, "", true);
   PsFile.AddPlot(H30PercentDR, "", true);
   PsFile.AddPlot(H40PercentDR, "", true);
   PsFile.AddPlot(H50PercentDR, "", true);
   PsFile.AddPlot(H60PercentDR, "", true);
   PsFile.AddPlot(H70PercentDR, "", true);
   PsFile.AddPlot(H80PercentDR, "", true);
   PsFile.AddPlot(H90PercentDR, "", true);
   PsFile.AddPlot(H100PercentDR, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   in.close();

   // print final particles and counts
   cout << "Final particles inside b-jets: (PDGID, Count)" << endl;
   for(map<int, int>::iterator iter = FinalPDGIDAndCount.begin(); iter != FinalPDGIDAndCount.end(); iter++)
      cout << iter->first << " " << iter->second << endl;
}




