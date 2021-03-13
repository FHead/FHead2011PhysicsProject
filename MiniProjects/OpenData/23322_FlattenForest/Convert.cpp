#include <fstream>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");

   TFile File(InputFileName.c_str());

   TTree *AnalyzerTree = (TTree *)File.Get("Analyzer/EventObjects");
   TTree *TriggerTree = (TTree *)File.Get("Trigger/HltTree");

   Assert(AnalyzerTree != nullptr, "Can't find analysis tree");
   Assert(TriggerTree != nullptr, "Can't find trigger tree");

   int RunNumber, EventNumber;
   AnalyzerTree->SetBranchAddress("RunNumber", &RunNumber);
   AnalyzerTree->SetBranchAddress("EventNumber", &EventNumber);

   int NPhoton;
   float PhotonPT[MAX], PhotonEta[MAX], PhotonPhi[MAX];
   float PhotonEcalR03[MAX], PhotonHcalR03[MAX], PhotonTrackR03[MAX], PhotonNTrackR03[MAX];
   float PhotonE15[MAX], PhotonE25[MAX], PhotonE33[MAX], PhotonE55[MAX];
   float PhotonSigmaEtaEta[MAX], PhotonSigmaIEtaIEta[MAX], PhotonHOverE[MAX];
   AnalyzerTree->SetBranchAddress("NPhoton", &NPhoton);
   AnalyzerTree->SetBranchAddress("PhotonPt", &PhotonPT);
   AnalyzerTree->SetBranchAddress("PhotonEta", &PhotonEta);
   AnalyzerTree->SetBranchAddress("PhotonPhi", &PhotonPhi);
   AnalyzerTree->SetBranchAddress("PhotonEcalR03", &PhotonEcalR03);
   AnalyzerTree->SetBranchAddress("PhotonHcalR03", &PhotonHcalR03);
   AnalyzerTree->SetBranchAddress("PhotonTrackR03", &PhotonTrackR03);
   AnalyzerTree->SetBranchAddress("PhotonNTrackR03", &PhotonNTrackR03);
   AnalyzerTree->SetBranchAddress("PhotonE15", &PhotonE15);
   AnalyzerTree->SetBranchAddress("PhotonE25", &PhotonE25);
   AnalyzerTree->SetBranchAddress("PhotonE33", &PhotonE33);
   AnalyzerTree->SetBranchAddress("PhotonE55", &PhotonE55);
   AnalyzerTree->SetBranchAddress("PhotonSigmaEtaEta", &PhotonSigmaEtaEta);
   AnalyzerTree->SetBranchAddress("PhotonSigmaIEtaIEta", &PhotonSigmaIEtaIEta);
   AnalyzerTree->SetBranchAddress("PhotonHOverE", &PhotonHOverE);

   int NTrack;
   float TrackPT[MAX], TrackEta[MAX], TrackPhi[MAX];
   int TrackCharge[MAX];
   int TrackHitsValid[MAX], TrackHitsPixel[MAX];
   float TrackDistPV0[MAX], TrackDistPVz[MAX], TrackChi2NDOF[MAX];
   AnalyzerTree->SetBranchAddress("NTrack", &NTrack);
   AnalyzerTree->SetBranchAddress("TrackPt", &TrackPT);
   AnalyzerTree->SetBranchAddress("TrackEta", &TrackEta);
   AnalyzerTree->SetBranchAddress("TrackPhi", &TrackPhi);
   AnalyzerTree->SetBranchAddress("TrackCharge", &TrackCharge);
   AnalyzerTree->SetBranchAddress("TrackHitsValid", &TrackHitsValid);
   AnalyzerTree->SetBranchAddress("TrackHitsPixel", &TrackHitsPixel);
   AnalyzerTree->SetBranchAddress("TrackDistPV0", &TrackDistPV0);
   AnalyzerTree->SetBranchAddress("TrackDistPVz", &TrackDistPVz);
   AnalyzerTree->SetBranchAddress("TrackChi2NDOF", &TrackChi2NDOF);
   
   int NMu;
   float MuPT[MAX], MuEta[MAX], MuPhi[MAX];
   int MuCharge[MAX];
   float MuIso03[MAX];
   int MuHitsValid[MAX], MuHitsPixel[MAX];
   float MuDistPV0[MAX], MuDistPVz[MAX], MuChi2NDOF[MAX];
   AnalyzerTree->SetBranchAddress("NMu", &NMu);
   AnalyzerTree->SetBranchAddress("MuPt", &MuPT);
   AnalyzerTree->SetBranchAddress("MuEta", &MuEta);
   AnalyzerTree->SetBranchAddress("MuPhi", &MuPhi);
   AnalyzerTree->SetBranchAddress("MuC", &MuCharge);
   AnalyzerTree->SetBranchAddress("MuIso03", &MuIso03);
   AnalyzerTree->SetBranchAddress("MuHitsValid", &MuHitsValid);
   AnalyzerTree->SetBranchAddress("MuHitsPixel", &MuHitsPixel);
   AnalyzerTree->SetBranchAddress("MuDistPV0", &MuDistPV0);
   AnalyzerTree->SetBranchAddress("MuDistPVz", &MuDistPVz);
   AnalyzerTree->SetBranchAddress("MuTrackChi2NDOF", &MuChi2NDOF);

   int TriggerPhoton15, TriggerPhoton20, TriggerPhoton30, TriggerPhoton40;
   TriggerTree->SetBranchAddress("HLT_HISinglePhoton15_v1", &TriggerPhoton15);
   TriggerTree->SetBranchAddress("HLT_HISinglePhoton20_v2", &TriggerPhoton20);
   TriggerTree->SetBranchAddress("HLT_HISinglePhoton30_v2", &TriggerPhoton30);
   TriggerTree->SetBranchAddress("HLT_HISinglePhoton40_v2", &TriggerPhoton40);

   ofstream out(OutputFileName);

   int EntryCount = AnalyzerTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      AnalyzerTree->GetEntry(iE);
      TriggerTree->GetEntry(iE);

      out << "START EVENT" << endl;

      out << "Trigger " << TriggerPhoton15
         << " " << TriggerPhoton20
         << " " << TriggerPhoton30
         << " " << TriggerPhoton40 << endl;
      out << "Centrality -1" << endl;
      out << "Run " << RunNumber << endl;
      out << "Event " << EventNumber << endl;
      out << "NPhoton " << NPhoton << " NTrack " << NTrack << " NMu " << NMu << endl;
      out << "CPhoton " << 14 << " CTrack " << 9 << " CMu " << 10 << endl;

      for(int i = 0; i < NPhoton; i++)
      {
         out << "P " << PhotonPT[i] << " " << PhotonEta[i] << " " << PhotonPhi[i]
            << " " << PhotonEcalR03[i] << " " << PhotonHcalR03[i]
            << " " << PhotonTrackR03[i] << " " << PhotonNTrackR03[i]
            << " " << PhotonE15[i] << " " << PhotonE25[i] << " " << PhotonE33[i] << " " << PhotonE55[i]
            << " " << PhotonSigmaEtaEta[i] << " " << PhotonSigmaIEtaIEta[i] << " " << PhotonHOverE[i] << endl;
      }

      for(int i = 0; i < NTrack; i++)
      {
         out << "T " << TrackPT[i] << " " << TrackEta[i] << " " << TrackPhi[i]
            << " " << TrackCharge[i] << " " << TrackHitsValid[i] << " " << TrackHitsPixel[i]
            << " " << TrackDistPV0[i] << " " << TrackDistPVz[i] << " " << TrackChi2NDOF[i] << endl;
      }
      
      for(int i = 0; i < NMu; i++)
      {
         out << "M " << MuPT[i] << " " << MuEta[i] << " " << MuPhi[i]
            << " " << MuCharge[i] << " " << MuIso03[i] << " " << MuHitsValid[i] << " " << MuHitsPixel[i]
            << " " << MuDistPV0[i] << " " << MuDistPVz[i] << " " << MuChi2NDOF[i] << endl;
      }
      
      out << "END EVENT" << endl;
      out << endl;
   }

   out.close();

   File.Close();

   return 0;
}




