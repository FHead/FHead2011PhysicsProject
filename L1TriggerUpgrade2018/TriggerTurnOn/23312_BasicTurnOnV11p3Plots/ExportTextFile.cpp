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
   DataHelper DHFile("CurvesV11p3.dh");
   
   ofstream OutputFile("ScalingsV11p3.txt");

   typedef pair<string, string> P;
   typedef pair<string, vector<string>> PV;
   vector<P> GName =
   {
      P("PFPhase1HT", "PFPhase1HT"),
      P("PFPhase1HT090", "090PFPhase1HT"),
      P("PuppiMET", "PuppiMET"),
      P("PuppiMET090", "090PuppiMET")
   };
   vector<P> TwoPartName =
   {
      P("EGPhoton", "EG"),
      P("EGElectron", "EGTrackID"),
      P("TkElectron", "TkElectronTrackID"),
      P("TkIsoElectron", "TkIsoElectron"),
      P("TkIsoPhoton", "TkIsoPhotonTrackID"),
      P("TkIsoPhotonPV", "TkIsoPhotonPVTrackID"),
      P("NNTauTight", "NNTauTight"),
      P("NNTauLoose", "NNTauLoose"),
      P("NNTauTight090", "090NNTauTight"),
      P("NNTauLoose090", "090NNTauLoose"),
      // P("CaloTau", "CaloTau")
   };
   vector<P> ThreePartName =
   {
      P("PFPhase1Jet", "PFPhase1Jet")
   };
   vector<P> ThreePartNameBOE =
   {
      // P("TkMuonQual", "TkMuonQual"),
      // P("StandaloneMuonQual", "StandaloneMuonQualIso")
   };
   vector<P> FourPartNameBOEO =
   {
   };
   vector<PV> ThreePartNameCustom =
   {
      PV("TkMuon", {"TkMuonB", "TkMuonO", "TkMuonE"}),
      PV("StandaloneMuon", {"StandaloneMuonIsoB", "StandaloneMuonIsoO", "StandaloneMuonIsoE"})
   };

   for(P Name : GName)
   {
      TGraph G;

      FillGraph(DHFile, Name.second, G);

      TF1 F("F", "[0]+[1]*x");
      G.Fit(&F);

      if(F.GetParameter(0) > 0)
         OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline-" << F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
      else
         OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et); "
            << "lambda:=Et>(offline+" << -F.GetParameter(0) << ")/" << F.GetParameter(1) << endl;
   }

   for(P Name : TwoPartName)
   {
      TGraph G1, G2;
      
      FillGraph(DHFile, Name.second + "Barrel", G1);
      FillGraph(DHFile, Name.second + "Endcap", G2);

      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);

      double EtaSplit = 1.5;

      OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et,Eta); ";
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
   
   for(P Name : ThreePartName)
   {
      TGraph G1, G2, G3;
      
      FillGraph(DHFile, Name.second + "Barrel", G1);
      FillGraph(DHFile, Name.second + "Endcap", G2);
      FillGraph(DHFile, Name.second + "Forward", G3);
      if(G3.GetN() == 0)
         FillGraph(DHFile, Name.second + "Extended", G3);

      G1.Print();
      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);
      TF1 F3("F3", "[0]+[1]*x");
      G3.Fit(&F3);

      double EtaSplit1 = 1.5;
      double EtaSplit2 = 2.4;

      OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et,Eta); ";
      OutputFile << "lambda:=";
      if(F1.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit1 << " else (";
      if(F2.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit2 << " else ";
      if(F3.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      OutputFile << ")" << endl;
   }
 
   for(P Name : ThreePartNameBOE)
   {
      TGraph G1, G2, G3;
      
      FillGraph(DHFile, Name.second + "B", G1);
      FillGraph(DHFile, Name.second + "O", G2);
      FillGraph(DHFile, Name.second + "E", G3);

      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);
      TF1 F3("F3", "[0]+[1]*x");
      G3.Fit(&F3);

      double EtaSplit1 = 0.9;
      double EtaSplit2 = 1.2;

      OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et,Eta); ";
      OutputFile << "lambda:=";
      if(F1.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit1 << " else (";
      if(F2.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit2 << " else ";
      if(F3.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      OutputFile << ")" << endl;
   }

   for(P Name : FourPartNameBOEO)
   {
      TGraph G1, G2, G3, G4;
      
      FillGraph(DHFile, Name.second + "B", G1);
      FillGraph(DHFile, Name.second + "O", G2);
      FillGraph(DHFile, Name.second + "E", G3);
      FillGraph(DHFile, "TkMuonStubExtended", G4);

      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);
      TF1 F3("F3", "[0]+[1]*x");
      G3.Fit(&F3);
      TF1 F4("F4", "[0]+[1]*x");
      G4.Fit(&F4);

      double EtaSplit1 = 0.9;
      double EtaSplit2 = 1.2;
      double EtaSplit3 = 2.4;

      OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et,Eta); ";
      OutputFile << "lambda:=";
      if(F1.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit1 << " else (";
      if(F2.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit2 << " else (";
      if(F3.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit3 << " else ";
      if(F4.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F4.GetParameter(0) << ")/" << F4.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F4.GetParameter(0) << ")/" << F4.GetParameter(1);
      OutputFile << "))" << endl;
   }

   for(PV Name : ThreePartNameCustom)
   {
      if(Name.second.size() != 3)
         continue;

      TGraph G1, G2, G3;
      
      FillGraph(DHFile, Name.second[0], G1);
      FillGraph(DHFile, Name.second[1], G2);
      FillGraph(DHFile, Name.second[2], G3);

      TF1 F1("F1", "[0]+[1]*x");
      G1.Fit(&F1);
      TF1 F2("F2", "[0]+[1]*x");
      G2.Fit(&F2);
      TF1 F3("F3", "[0]+[1]*x");
      G3.Fit(&F3);

      double EtaSplit1 = 0.9;
      double EtaSplit2 = 1.2;

      OutputFile << "function :: " << Name.first << "OfflineEtCut :: args:=(offline,Et,Eta); ";
      OutputFile << "lambda:=";
      if(F1.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F1.GetParameter(0) << ")/" << F1.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit1 << " else (";
      if(F2.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F2.GetParameter(0) << ")/" << F2.GetParameter(1);
      OutputFile << " if abs(Eta)<" << EtaSplit2 << " else ";
      if(F3.GetParameter(0) > 0)
         OutputFile << "Et>(offline-" << F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      else
         OutputFile << "Et>(offline+" << -F3.GetParameter(0) << ")/" << F3.GetParameter(1);
      OutputFile << ")" << endl;
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


