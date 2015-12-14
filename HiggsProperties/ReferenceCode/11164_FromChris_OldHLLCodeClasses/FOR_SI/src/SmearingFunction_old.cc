#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TH1D.h>
#include <iostream>
#include <vector>
#include <SmearingFunction.hh>

using namespace std;

SmearingFunction::SmearingFunction(vector<TH1D*> pTSmear, 
				   vector<TH1D*> etaSmear) {
  _pTSmearing  = pTSmear;
  _etaSmearing = etaSmear;
  // set seed
  int jobpid   = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+jobpid;
  _random = new TRandom3(seed);

  etaBinMuon[0] = 0.;   effRecoMuon[0] = 0.998;
  etaBinMuon[1] = 0.16; effRecoMuon[1] = 0.998;
  etaBinMuon[2] = 0.25; effRecoMuon[2] = 0.890;
  etaBinMuon[3] = 0.36; effRecoMuon[3] = 0.998;
  etaBinMuon[4] = 0.76; effRecoMuon[4] = 0.998;
  etaBinMuon[5] = 0.80; effRecoMuon[5] = 0.960;
  etaBinMuon[6] = 0.86; effRecoMuon[6] = 0.998;
  etaBinMuon[7] = 1.15; effRecoMuon[7] = 0.998;
  etaBinMuon[8] = 1.21; effRecoMuon[8] = 0.921;
  etaBinMuon[9] = 1.30; effRecoMuon[9] = 0.996;
  etaBinMuon[10] = 1.56; effRecoMuon[10] = 0.996;
  etaBinMuon[11] = 1.66; effRecoMuon[11] = 0.964;
  etaBinMuon[12] = 1.84; effRecoMuon[12] = 0.995;
  etaBinMuon[13] = 2.10; effRecoMuon[13] = 0.995;
  etaBinMuon[14] = 2.16; effRecoMuon[14] = 0.960;
  etaBinMuon[15] = 2.21; effRecoMuon[15] = 0.970;
  etaBinMuon[16] = 2.40; effRecoMuon[16] = 0.970;

  pTMuonBin[0] = 0.;    scaleMuonPt[0] = 1.;
  pTMuonBin[1] = 10.;   scaleMuonPt[1] = 1.;
  pTMuonBin[2] = 50.;   scaleMuonPt[2] = 0.998/0.993;
  pTMuonBin[3] = 100.,  scaleMuonPt[3] = 1.;
  pTMuonBin[4] = 500.;  scaleMuonPt[4] = 0.989/0.993;
  pTMuonBin[5] = 1000.; scaleMuonPt[5] = 0.982/0.993;
  pRes = 0.03;            // PTDR VOL I PAG 336
  ProbFlipCh = 0.002;     // PTDR VOL I PAG 337
}

TLorentzVector SmearingFunction::SmearMuon(TLorentzVector genMuon) {

  double pTGEN  = min(genMuon.Pt(),249.);
  double etaGEN = min(genMuon.Eta(),2.39);
  if(genMuon.Eta() < 0.) etaGEN = max(genMuon.Eta(),-2.39);

  double phiGEN = genMuon.Phi();
  double   mGEN = genMuon.M();



  int ihisto = 0.;
  for(int i=0; i<50; i++) {
    if(pTGEN>= i/50.*250. && pTGEN < (i+1)/50.*250.) {
      for(int j=0; j<24; j++) {
	if(etaGEN>= -2.4 + i/24.*4.8 && etaGEN < -2.4 + (i+1)/24.*4.8) {
	  ihisto = j+i*24;
	}
      }
    }
  }

  double pT;
  if(_pTSmearing[ihisto]->Integral() != 0.){  
    pT = genMuon.Pt()+_pTSmearing[ihisto]->GetRandom();
  } else {
    pT = genMuon.Pt();
  }
  
  double eta;
  
  if(_etaSmearing[ihisto]->Integral() != 0.){ 
    eta = genMuon.Eta() + _etaSmearing[ihisto]->GetRandom();
  } else {
    eta = genMuon.Eta();
  }
  
  
  TLorentzVector recomuon;
  recomuon.SetPtEtaPhiM(pT, eta, phiGEN, mGEN);
  

  // smear the gen-level muon according to lookup tables
  // and return the measured muon
  return recomuon;
}
