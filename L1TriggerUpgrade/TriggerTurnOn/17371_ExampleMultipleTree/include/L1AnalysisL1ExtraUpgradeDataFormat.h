#ifndef __L1Analysis_L1AnalysisL1ExtraUpgradeDataFormat_H__
#define __L1Analysis_L1AnalysisL1ExtraUpgradeDataFormat_H__

//-------------------------------------------------------------------------------
// Created 20/04/2010 - E. Conte, A.C. Le Bihan
// 
// 
// Original code : UserCode/L1TriggerDPG/L1ExtraTreeProducer - Jim Brooke
//-------------------------------------------------------------------------------


#include <vector>

namespace L1Analysis
{
  struct L1AnalysisL1ExtraUpgradeDataFormat
  {
    L1AnalysisL1ExtraUpgradeDataFormat(){Reset();};
    ~L1AnalysisL1ExtraUpgradeDataFormat(){};
    
    void Reset()
    {
      nEG = 0;
      egEt.clear();
      egEta.clear();
      egPhi.clear();
      egBx.clear();
      
      nIsoEG = 0;
      isoEGEt.clear();
      isoEGEta.clear();
      isoEGPhi.clear();
      isoEGBx.clear();

      //TkEM, TkEG
      nTkEG = 0;
      tkEGEt.clear();
      tkEGEta.clear();
      tkEGPhi.clear();
      tkEGBx.clear();
      tkEGTrkIso.clear();
      tkEGzVtx.clear();

      // 2nd TkEG collection (TrkPt=7)
      nTkEG2 = 0;
      tkEG2Et.clear();
      tkEG2Eta.clear();
      tkEG2Phi.clear();
      tkEG2Bx.clear();
      tkEG2TrkIso.clear();
      tkEG2zVtx.clear();

      nTkIsoEG = 0;
      tkIsoEGEt.clear();
      tkIsoEGEta.clear();
      tkIsoEGPhi.clear();
      tkIsoEGBx.clear();
      tkIsoEGTrkIso.clear();
      tkIsoEGzVtx.clear();

      nTkEM = 0;
      tkEMEt.clear();
      tkEMEta.clear();
      tkEMPhi.clear();
      tkEMBx.clear();
      tkEMTrkIso.clear();

      nTau = 0;
      tauEt.clear();
      tauEta.clear();
      tauPhi.clear(); 
      tauBx.clear();

      nIsoTau = 0;
      isoTauEt.clear();
      isoTauEta.clear();
      isoTauPhi.clear(); 
      isoTauBx.clear();

      // TkTaus
      nTkTau = 0;
      tkTauEt.clear();
      tkTauEta.clear();
      tkTauPhi.clear();
      tkTauBx.clear();
      tkTauTrkIso.clear();
      tkTauzVtx.clear();

      nJets = 0;
      jetEt.clear();
      jetEta.clear();
      jetPhi.clear();
      jetBx.clear();

      // TkJets
      nTkJets = 0;
      tkJetEt.clear();
      tkJetEta.clear();
      tkJetPhi.clear();
      tkJetBx.clear();
      tkJetzVtx.clear();

      nFwdJets = 0;
      fwdJetEt.clear();
      fwdJetEta.clear();
      fwdJetPhi.clear();
      fwdJetBx.clear();

      nMuons = 0;
      muonEt.clear();
      muonEta.clear();
      muonPhi.clear();
      muonChg.clear();
      muonIso.clear();
      muonFwd.clear();
      muonMip.clear();
      muonRPC.clear();
      muonBx.clear();
      muonQuality.clear();

      // tkTkMuons
      nTkMuons = 0;
      tkMuonEt.clear();
      tkMuonEta.clear();
      tkMuonPhi.clear();
      tkMuonChg.clear();
      tkMuonTrkIso.clear();
      tkMuonFwd.clear();
      tkMuonMip.clear();
      tkMuonRPC.clear();
      tkMuonBx.clear();
      tkMuonQuality.clear();
      tkMuonzVtx.clear();

      nMet = 0;
      et.clear();
      met.clear();
      metPhi.clear();
      metBx.clear();

      // TkMet
      nTkMet = 0;
      tkEt.clear();
      tkMet.clear();
      tkMetPhi.clear();
      tkMetBx.clear();


      nMht = 0;
      ht.clear();
      mht.clear();
      mhtPhi.clear();
      mhtBx.clear();

      //TkMht
      nTkMht = 0;
      tkHt.clear();
      tkMht.clear();
      tkMhtPhi.clear();
      tkMhtBx.clear();


    }
   
    unsigned int nEG;
    std::vector<double> egEt;
    std::vector<double> egEta;
    std::vector<double> egPhi;
    std::vector<int>    egBx;
 
    unsigned int nIsoEG;
    std::vector<double> isoEGEt;
    std::vector<double> isoEGEta;
    std::vector<double> isoEGPhi;
    std::vector<int>    isoEGBx;
 
    unsigned int nTkEG;
    std::vector<double> tkEGEt;
    std::vector<double> tkEGEta;
    std::vector<double> tkEGPhi;
    std::vector<int>    tkEGBx;
    std::vector<double> tkEGTrkIso;
    std::vector<double> tkEGzVtx;

    unsigned int nTkEG2;
    std::vector<double> tkEG2Et;
    std::vector<double> tkEG2Eta;
    std::vector<double> tkEG2Phi;
    std::vector<int>    tkEG2Bx;
    std::vector<double> tkEG2TrkIso;
    std::vector<double> tkEG2zVtx;


    unsigned int nTkIsoEG;
    std::vector<double> tkIsoEGEt;
    std::vector<double> tkIsoEGEta;
    std::vector<double> tkIsoEGPhi;
    std::vector<int>    tkIsoEGBx;
    std::vector<double> tkIsoEGTrkIso;
    std::vector<double> tkIsoEGzVtx;

    unsigned int nTkEM;
    std::vector<double> tkEMEt;
    std::vector<double> tkEMEta;
    std::vector<double> tkEMPhi;
    std::vector<int>    tkEMBx;
    std::vector<double> tkEMTrkIso;


    unsigned int nTau;
    std::vector<double> tauEt;
    std::vector<double> tauEta;
    std::vector<double> tauPhi;
    std::vector<int>    tauBx;

    unsigned int nIsoTau;
    std::vector<double> isoTauEt;
    std::vector<double> isoTauEta;
    std::vector<double> isoTauPhi;
    std::vector<int>    isoTauBx;

    unsigned int nTkTau;
    std::vector<double> tkTauEt;
    std::vector<double> tkTauEta;
    std::vector<double> tkTauPhi;
    std::vector<int>    tkTauBx;
    std::vector<double> tkTauTrkIso;
    std::vector<double> tkTauzVtx;


    unsigned int nJets;
    std::vector<double> jetEt;
    std::vector<double> jetEta;
    std::vector<double> jetPhi;
    std::vector<int>    jetBx;
 
    unsigned int nTkJets;
    std::vector<double> tkJetEt;
    std::vector<double> tkJetEta;
    std::vector<double> tkJetPhi;
    std::vector<int>    tkJetBx;
    std::vector<double> tkJetzVtx;

    unsigned int nFwdJets;
    std::vector<double> fwdJetEt;
    std::vector<double> fwdJetEta;
    std::vector<double> fwdJetPhi;
    std::vector<int>    fwdJetBx;

    unsigned int nMuons;
    std::vector<double>   muonEt;
    std::vector<double>   muonEta;
    std::vector<double>   muonPhi;
    std::vector<int>      muonChg;
    std::vector<unsigned int> muonIso;
    std::vector<unsigned int> muonFwd;
    std::vector<unsigned int> muonMip;
    std::vector<unsigned int> muonRPC;
    std::vector<int>      muonBx;
    std::vector<int>      muonQuality;
 
    unsigned int nTkMuons;
    std::vector<double>   tkMuonEt;
    std::vector<double>   tkMuonEta;
    std::vector<double>   tkMuonPhi;
    std::vector<int>      tkMuonChg;
    std::vector<unsigned int> tkMuonIso;
    std::vector<double> tkMuonTrkIso;
    std::vector<unsigned int> tkMuonFwd;
    std::vector<unsigned int> tkMuonMip;
    std::vector<unsigned int> tkMuonRPC;
    std::vector<int>      tkMuonBx;
    std::vector<unsigned int>      tkMuonQuality;
    std::vector<double>   tkMuonzVtx;

    unsigned int nMet;
    std::vector<double> et;
    std::vector<double> met;
    std::vector<double> metPhi;
    std::vector<double> metBx;

    unsigned int nTkMet;
    std::vector<double> tkEt;
    std::vector<double> tkMet;
    std::vector<double> tkMetPhi;
    std::vector<double> tkMetBx;

    unsigned int nMht;
    std::vector<double> ht;
    std::vector<double> mht;
    std::vector<double> mhtPhi;
    std::vector<double> mhtBx;

    unsigned int nTkMht;
    std::vector<double> tkHt;
    std::vector<double> tkMht;
    std::vector<double> tkMhtPhi;
    std::vector<double> tkMhtBx;



  }; 
}
#endif


