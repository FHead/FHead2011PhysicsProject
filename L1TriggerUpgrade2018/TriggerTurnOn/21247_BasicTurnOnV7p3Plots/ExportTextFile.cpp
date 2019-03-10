#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TF1.h"

int main(int argc, char *argv[])
{
   TFile File("Curves.root");
   ofstream OutputFile("Scalings.txt");

   vector<string> GName = {"StandaloneMuonIso", "StandaloneDisplacedMuonIso", "TkMuon", "TkMuonStubIso",
      "PuppiJet", "PuppiJetForMET", "PuppiHT30", "PuppiMET", "PFTau", "PFIsoTau"};
   vector<string> TwoPartName = {"EG", "EGTrackID", "TkElectronTrackID", "TkIsoElectron",
      "TkIsoPhotonTrackID", "TkIsoPhotonPVTrackID", "TkIsoElectronPV", "CaloJet"};

   for(string Name : GName)
   {
      TGraph *G = (TGraph *)File.Get(Name.c_str());
      if(G == nullptr)
         continue;

      TF1 F("F", "[0]+[1]*x");
      G->Fit(&F);

      if(F.GetParameter(0) > 0)
         OutputFile << "function :: " << Name << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline-" << F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
      else
         OutputFile << "function :: " << Name << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline+" << -F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
   }

   for(string Name : TwoPartName)
   {
      TGraph *G1 = (TGraph *)File.Get((Name + "Barrel").c_str());
      TGraph *G2 = (TGraph *)File.Get((Name + "Endcap").c_str());
      if(G1 == nullptr)
         continue;
      if(G2 == nullptr)
         continue;

      TF1 F1("F1", "[0]+[1]*x");
      G1->Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2->Fit(&F2);

      double EtaSplit = 1.392;

      OutputFile << "function :: " << Name << "OfflineEtCut :: args:=(offline,Et,Eta); ";
      OutputFile << "lambda:=";
      if(F1.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit << " else ";
      if(F2.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F2.GetParameter(0) << ")/" << F2.GetParameter(1) << endl;
      else
         OutputFile << "Et>(offline+" << -F2.GetParameter(0) << ")/" << F2.GetParameter(1) << endl;
   }

   OutputFile.close();
   File.Close();

   return 0;
}


// function :: pfTauOfflineEtCut    :: args:=(offline,Et); lambda:=Et>(offline-2.173)/1.067



