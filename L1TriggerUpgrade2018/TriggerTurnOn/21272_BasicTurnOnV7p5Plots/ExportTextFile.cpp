#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TF1.h"

#include "DataHelper.h"

int main(int argc, char *argv[]);
void FillGraph(DataHelper &DHFile, string Tag, TGraph &G);
void FillReverseGraph(DataHelper &DHFile, string Tag, TGraph &G);

int main(int argc, char *argv[])
{
   DataHelper DHFile("Curves.dh");
   
   ofstream OutputFile("Scalings.txt");

   vector<pair<string, string>> GName =
   {
      pair<string, string>("StandaloneMuonIsoTanh", "StandaloneMuon"),
      pair<string, string>("StandaloneDisplacedMuonIso", "StandaloneDisplacedMuon"),
      pair<string, string>("TkMuon", "TkMuon"),
      pair<string, string>("TkMuonStubIso", "TkMuonStub"),
      pair<string, string>("PuppiJetFitFix2", "PuppiJet"),
      pair<string, string>("PuppiHT30", "PuppiHT30"),
      pair<string, string>("PuppiMET", "PuppiMET"),
      pair<string, string>("PFTau", "PFTau"),
      pair<string, string>("PFIsoTau", "PFIsoTau"),
      pair<string, string>("TrackerJetFit", "TrackerJet"),
      pair<string, string>("TrackerJetChargedFit", "TrackerJetCharged"),
      pair<string, string>("TrackerHT5", "TrackerHT"),
      pair<string, string>("TrackerHTCharged5", "TrackerHTCharged"),
      pair<string, string>("TrackerMET", "TrackerMET"),
      pair<string, string>("TkTau", "TkTau"),
      pair<string, string>("CaloTkTau", "CaloTkTau"),
      pair<string, string>("TkEGTau", "TkEGTau"),
      pair<string, string>("TrackerMHT5METFit", "TrackerMHT")
   };
   vector<pair<string, string>> TwoPartName =
   {
      pair<string, string>("EG", "StandalonePhoton"),
      pair<string, string>("EGTrackID", "StandaloneElectron"),
      pair<string, string>("TkElectronTrackID", "TkElectron"),
      pair<string, string>("TkIsoElectron", "TkIsoElectron"),
      pair<string, string>("TkIsoPhotonTrackID", "TkIsoPhoton"),
      pair<string, string>("TkIsoPhotonPVTrackID", "TkIsoPhotonPV"),
      pair<string, string>("TkIsoElectronPV", "TkIsoElectronPV"),
      pair<string, string>("CaloJet", "CaloJet"),
      pair<string, string>("QCDCaloJet", "QCDCaloJet")
   };
   vector<pair<string, string>> QuadraticName =
   {
      pair<string, string>("TrackerMHT5METFit", "TrackerMHTQuadratic")
   };


   for(pair<string, string> Name : GName)
   {
      TGraph G;

      FillGraph(DHFile, Name.first, G);

      TF1 F("F", "[0]+[1]*x");
      G.Fit(&F);

      if(F.GetParameter(0) > 0)
         OutputFile << "function :: " << Name.second << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline-" << F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
      else
         OutputFile << "function :: " << Name.second << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline+" << -F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
   }

   for(pair<string, string> Name : QuadraticName)
   {
      TGraph G;
      
      FillReverseGraph(DHFile, Name.first, G);

      TF1 F("F1", "[0]+[1]*x+[2]*x*x");
      G.Fit(&F);

      OutputFile << "function :: " << Name.second << "OfflineEtCut :: args:=(offline,Et); "
         << "lambda:=Et>";
      if(F.GetParameter(0) > 0)   OutputFile << F.GetParameter(0);
      else                        OutputFile << "-" << -F.GetParameter(0);
      if(F.GetParameter(1) > 0)   OutputFile << "+" << F.GetParameter(1) << "*offline";
      else                        OutputFile << "-" << -F.GetParameter(1) << "*offline";
      if(F.GetParameter(2) > 0)   OutputFile << "+" << F.GetParameter(2) << "*offline*offline";
      else                        OutputFile << "-" << -F.GetParameter(2) << "*offline*offline";
      OutputFile << endl;
   }

   for(pair<string, string> Name : TwoPartName)
   {
      TGraph G1, G2;
      
      FillGraph(DHFile, Name.first + "Barrel", G1);
      FillGraph(DHFile, Name.first + "Endcap", G2);

      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);

      double EtaSplit = 1.392;

      OutputFile << "function :: " << Name.second << "OfflineEtCut :: args:=(offline,Et,Eta); ";
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

   return 0;
}

void FillGraph(DataHelper &DHFile, string Tag, TGraph &G)
{
   int N = DHFile[Tag]["N"].GetInteger();

   if(N <= 0)
      return;

   G.Set(N);

   for(int i = 0; i < N; i++)
   {
      double X = DHFile[Tag][Form("X%d",i)].GetDouble();
      double Y = DHFile[Tag][Form("Y%d",i)].GetDouble();

      G.SetPoint(i, X, Y);
   }
}

void FillReverseGraph(DataHelper &DHFile, string Tag, TGraph &G)
{
   int N = DHFile[Tag]["N"].GetInteger();

   if(N <= 0)
      return;

   G.Set(N);

   for(int i = 0; i < N; i++)
   {
      double Y = DHFile[Tag][Form("X%d",i)].GetDouble();
      double X = DHFile[Tag][Form("Y%d",i)].GetDouble();

      G.SetPoint(i, X, Y);
   }
}


