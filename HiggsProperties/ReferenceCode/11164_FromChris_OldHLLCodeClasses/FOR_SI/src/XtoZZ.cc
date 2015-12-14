using namespace std;
#include <TLorentzVector.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <XtoZZ.hh>

using namespace std;

XtoZZ::XtoZZ(double mass, double width){
  Init(mass, width);
}

void XtoZZ::Init(double mass, double width) {
  _mH  = mass;
  _wH  = width;
  _mZ  = 91.1876;      // PDG value
  _wZ  = 2.4952;       // PDG value
  _mMu = 0.105658367 ; // PDG value

  // set seed
  int jobpid = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+jobpid;
  gRandom = new TRandom3(seed);

  _mHPDF = (TH1D*) new TH1D("_mHPDF", "_mHPDF", 5000, _mH-5.0*_wH, _mH+5.0*_wH);
  _mZPDF = (TH1D*) new TH1D("_mZPDF", "_mZPDF", 5000, _mZ-5.0*_wZ, _mZ+5.0*_wZ);


  //Initialize Z and H mass PDF's
  for(int i = 0; i < 5000; i++){
    _mHPDF->Fill(_mHPDF->GetBinCenter(i+1),BreitWigner(_mHPDF->GetBinCenter(i+1),_mH, _wH));
    _mZPDF->Fill(_mZPDF->GetBinCenter(i+1),BreitWigner(_mZPDF->GetBinCenter(i+1),_mZ, _wZ));
  }
  _mHPDF->Scale(1.0/_mHPDF->Integral());
  _mZPDF->Scale(1.0/_mZPDF->Integral());
}

void XtoZZ::SetSmearingFunction(SmearingFunction* smear ){
  _cmsSmear = smear;
}

void XtoZZ::GenBoost(){
  _BoostDist->GetRandom2(_etaH, _pTH);
  _phiH = gRandom->Rndm()*4.*asin(1.);
}

void XtoZZ::SetBoost(double eta, double pt){
  _etaH = eta; 
  _pTH = pt;
  _phiH = gRandom->Rndm()*4.*asin(1.);
}

void XtoZZ::SetBoostDist(string filename) {

  TFile* hboostfile = TFile::Open(filename.c_str());
  _BoostDist = (TH2D*) hboostfile->Get("higgsGEN_pTvseta_histo");
  //hboostfile->Close();
 
}

double XtoZZ::BreitWigner(double mstar, double m, double w){

  double ret = 1.0/((mstar*mstar-m*m)*(mstar*mstar-m*m) + mstar*mstar*w*w);

  return ret;
}

void XtoZZ::LoadEvent(double M, double cosTHETA, double PHI, 
		      double c1, double c2, double phi){
  _c1GEN = c1;
  _c2GEN = c2;
  _phiGEN = phi;
  _PHIGEN = PHI;
  _cosTHETAGEN = cosTHETA;
  _massZ2GEN = M;
  
  //
  //Now we get the Higgs and Z1 masses
  //
  bool cont = true;
  while(cont){
    _massHGEN = _mHPDF->GetRandom();
    _massZ1GEN = _mZPDF->GetRandom();
    if(_massZ1GEN+_massZ2GEN <= _massHGEN){
      cont = false;
    }
  }
}
 
void XtoZZ::CalcGenMomenta() {

  double s1GEN = sqrt(1.-pow(_c1GEN,2.));
  double s2GEN = sqrt(1.-pow(_c2GEN,2.));

  // momentum of the Z in the Higgs rest frame
  // we fix the z axis // to the back-to-back Z momenta
  double gamma1 = (_massHGEN*_massHGEN-_massZ2GEN*_massZ2GEN+_massZ1GEN*_massZ1GEN)
    /(2.0*_massHGEN*_massZ1GEN);
  double gamma2 = (_massHGEN*_massHGEN+_massZ2GEN*_massZ2GEN-_massZ1GEN*_massZ1GEN)
    /(2.0*_massHGEN*_massZ2GEN);

  double beta1 = sqrt(1.0-1.0/(gamma1*gamma1));
  double beta2 = sqrt(1.0-1.0/(gamma2*gamma2));

  TLorentzVector pZ1(0., 0.,  -beta1*gamma1*_massZ1GEN, gamma1*_massZ1GEN);
  TLorentzVector pZ2(0., 0.,  beta2*gamma2*_massZ2GEN, gamma2*_massZ2GEN);
  
  // momentum of the leptons in the Z rest frame
  double eMu1 = _massZ1GEN/2.;
  double eMu2 = _massZ2GEN/2.;
  double pMu1 = sqrt(eMu1*eMu1 - _mMu*_mMu);
  double pMu2 = sqrt(eMu2*eMu2 - _mMu*_mMu);

  _p1pGEN.SetPxPyPzE(pMu1*s1GEN*sin(_phiGEN), pMu1*s1GEN*cos(_phiGEN), pMu1*_c1GEN, eMu1);
  _p1mGEN.SetPxPyPzE(-1.0*pMu1*s1GEN*sin(_phiGEN), -1.0*pMu1*s1GEN*cos(_phiGEN), -1.0*pMu1*_c1GEN, eMu1);
  _p2pGEN.SetPxPyPzE(0.0, -pMu2*s2GEN, -pMu2*_c2GEN, eMu2);
  _p2mGEN.SetPxPyPzE(0.0, pMu2*s2GEN, pMu2*_c2GEN, eMu2);

  

  // boost the leptons in the Higgs RF
  TVector3 Z1boost = pZ1.BoostVector();
  TVector3 Z2boost = pZ2.BoostVector();

  _p1pGEN.Boost(-Z1boost);
  _p1mGEN.Boost(-Z1boost);

  _p2pGEN.Boost(-Z2boost);
  _p2mGEN.Boost(-Z2boost);

  //Now we are in the Higgs rest frame - we need to now align this frame in the right direction
  //see below

  //Higgs direction
  double thetaH= atan(exp(-_etaH))*2.;

  TLorentzVector Higgs;
  Higgs.SetPtEtaPhiM(_pTH, _etaH, _phiH, _massHGEN);
  //Vector perp to Higgs direction
 
  
  //Higgs Boost vector
  TVector3 Hboost = Higgs.BoostVector();
  TVector3 direction = -1.0*Higgs.Vect().Unit();
  TVector3 direction_perp;

  direction_perp.SetXYZ(1.0,0.0,0.0);
  
  
  //let's align the leptons correctly in the Higgs rest frame

  direction_perp.RotateUz(direction);

  _p1pGEN.RotateUz(direction);
  _p1mGEN.RotateUz(direction);
  
  _p2pGEN.RotateUz(direction);
  _p2mGEN.RotateUz(direction);
  
  direction = -1.0*direction;

  double THETA = acos(_cosTHETAGEN);
	
  _p1pGEN.Rotate(THETA,direction_perp);
  _p1mGEN.Rotate(THETA,direction_perp);
	
  _p2pGEN.Rotate(THETA,direction_perp);
  _p2mGEN.Rotate(THETA,direction_perp);

  TVector3 vZ2 = (_p2pGEN+_p2mGEN).Vect().Unit();

  // _p1pGEN.Rotate(-_PHIGEN,direction);
//   _p1mGEN.Rotate(-_PHIGEN,direction);
	
//   _p2pGEN.Rotate(-_PHIGEN,direction);
//   _p2mGEN.Rotate(-_PHIGEN,direction);

  _p1pGEN.Rotate(-_PHIGEN,vZ2);
  _p1mGEN.Rotate(-_PHIGEN,vZ2);
	
  _p2pGEN.Rotate(-_PHIGEN,vZ2);
  _p2mGEN.Rotate(-_PHIGEN,vZ2);
 
  // boost the leptons in the lab frame
  _p1pGEN.Boost(Hboost);
  _p1mGEN.Boost(Hboost);
  
  _p2pGEN.Boost(Hboost);
  _p2mGEN.Boost(Hboost);

  _HGEN = _p1pGEN+_p1mGEN+_p2pGEN+_p2mGEN;
  _Z1GEN = _p1pGEN+_p1mGEN;
  _Z2GEN = _p2pGEN+_p2mGEN;
}

void XtoZZ::SmearMomenta(int type) {
  //type == 1 means electrons
  //type == 2 means extreme
  //everything else, muons
  if(type == 1){
    // smear the lepton momenta
    _p1p = _cmsSmear->SmearEle(_p1pGEN);
    _p1m = _cmsSmear->SmearEle(_p1mGEN);
    _p2p = _cmsSmear->SmearEle(_p2pGEN);
    _p2m = _cmsSmear->SmearEle(_p2mGEN);
  } else {
    if(type == 2){
      // smear the lepton momenta
      _p1p = _cmsSmear->SmearExtreme(_p1pGEN);
      _p1m = _cmsSmear->SmearExtreme(_p1mGEN);
      _p2p = _cmsSmear->SmearExtreme(_p2pGEN);
      _p2m = _cmsSmear->SmearExtreme(_p2mGEN);
    } else {
      // smear the lepton momenta
      _p1p = _cmsSmear->SmearMuon(_p1pGEN);
      _p1m = _cmsSmear->SmearMuon(_p1mGEN);
      _p2p = _cmsSmear->SmearMuon(_p2pGEN);
      _p2m = _cmsSmear->SmearMuon(_p2mGEN);
    }
  }
  //_p1p = _p1pGEN;
  //_p1m = _p1mGEN;
  //_p2p = _p2pGEN;
  //_p2m = _p2mGEN;

}

bool XtoZZ::PassCuts(double eta_cut, double pt_cut) {

  bool ret = true;

  if(fabs(_p1p.Eta()) > eta_cut ||
     fabs(_p1m.Eta()) > eta_cut ||
     fabs(_p2p.Eta()) > eta_cut ||
     fabs(_p2m.Eta()) > eta_cut) ret = false;

  if(fabs(_p1p.Pt()) < pt_cut ||
     fabs(_p1m.Pt()) < pt_cut ||
     fabs(_p2p.Pt()) < pt_cut ||
     fabs(_p2m.Pt()) < pt_cut) ret = false;

  return ret;
}

void XtoZZ::SwitchZ(){
  TLorentzVector v_tmp;
  v_tmp = _p1p;
  _p1p = _p2p;
  _p2p = v_tmp;
  v_tmp = _p1m;
  _p1m = _p2m;
  _p2m = v_tmp;
  v_tmp = _p1pGEN;
  _p1pGEN = _p2pGEN;
  _p2pGEN = v_tmp;
  v_tmp = _p1mGEN;
  _p1mGEN = _p2mGEN;
  _p2mGEN = v_tmp;

  TLorentzVector p1p = _p1pGEN;
  TLorentzVector p1m = _p1mGEN;
  TLorentzVector p2p = _p2pGEN;
  TLorentzVector p2m = _p2mGEN;

  _HGEN = p1p+p1m+p2p+p2m;
  _Z1GEN = p1p+p1m;
  _Z2GEN = p2p+p2m;

  TLorentzVector Hmom = p1p+p1m+p2p+p2m;
  TVector3 Hboost = Hmom.BoostVector();
  TVector3 direction = Hmom.Vect().Unit();

  p1p.Boost(-Hboost);
  p1m.Boost(-Hboost);
  p2p.Boost(-Hboost);
  p2m.Boost(-Hboost);

  TLorentzVector Z1mom = p1p + p1m;
  TLorentzVector Z2mom = p2p + p2m;

  //First we get everything from the Higgs rest frame
  
  _cosTHETAGEN = Z2mom.Vect().Unit().Dot(direction);
  
  TVector3 p1p_cross_p1m = p1p.Vect().Cross(p1m.Vect());
  TVector3 p2p_cross_p2m = p2p.Vect().Cross(p2m.Vect());
  double dot_phi = p1p.Vect().Dot(p2p_cross_p2m);
  
  _phiGEN = p1p_cross_p1m.Angle(p2p_cross_p2m);
  if(dot_phi < 0.0 && _phiGEN > 0.0){
    _phiGEN = TMath::Pi()*2.0-_phiGEN;
  }

  TVector3 H_cross_Z2 = direction.Cross(Z2mom.Vect());

  //p2p_cross_p2m.Rotate(TMath::Pi()/2.0, Z2mom.Vect());

  _PHIGEN = H_cross_Z2.Angle(p2p_cross_p2m);

  double dot_PHI = direction.Dot(p2p_cross_p2m);
  if(dot_PHI > 0.0 && _PHIGEN > 0.0){
    _PHIGEN = TMath::Pi()*2.0-_PHIGEN;
  }

  //Now we move to Z rest frame for c1/c2

  TVector3 Z1boost = Z1mom.BoostVector();
  TVector3 Z2boost = Z2mom.BoostVector();

  p1p.Boost(-Z1boost);
  p1m.Boost(-Z1boost);

  p2p.Boost(-Z2boost);
  p2m.Boost(-Z2boost);

  _c1GEN = p1m.Vect().Unit().Dot(-Z1boost.Unit());
  _c2GEN = p2m.Vect().Unit().Dot(-Z2boost.Unit());
}
  
  

void XtoZZ::CalcRecoKinematics(bool ID) {
  // go from the lab frame to the Higgs RF
  // and compute all the kinematics

  //
  //first, if ID == false it means we don't know which
  //Z is which, so we will assign Z2 as the one with 
  //cos(theta_i) larger
  //so we do this first
  //

  if(ID == false){
    TLorentzVector p1p_tmp = _p1p;
    TLorentzVector p1m_tmp = _p1m;
    TLorentzVector p2p_tmp = _p2p;
    TLorentzVector p2m_tmp = _p2m;

    TLorentzVector H_tmp = p1p_tmp+p1m_tmp+p2p_tmp+p2m_tmp;
    TVector3 Hboost_tmp = H_tmp.BoostVector();
    
    p1p_tmp.Boost(-Hboost_tmp);
    p1m_tmp.Boost(-Hboost_tmp);
    p2p_tmp.Boost(-Hboost_tmp);
    p2m_tmp.Boost(-Hboost_tmp);

    TLorentzVector Z1_tmp = p1p_tmp + p1m_tmp;
    TLorentzVector Z2_tmp = p2p_tmp + p2m_tmp;

    TVector3 Z1boost_tmp = Z1_tmp.BoostVector();
    TVector3 Z2boost_tmp = Z2_tmp.BoostVector();

    p1p_tmp.Boost(-Z1boost_tmp);
    p1m_tmp.Boost(-Z1boost_tmp);

    p2p_tmp.Boost(-Z2boost_tmp);
    p2m_tmp.Boost(-Z2boost_tmp);

    double c1_tmp = p1m_tmp.Vect().Unit().Dot(-Z1boost_tmp.Unit());
    double c2_tmp = p2m_tmp.Vect().Unit().Dot(-Z2boost_tmp.Unit());
    
    // switch if necessary
    double ran = gRandom->Rndm();
    if(ran > 0.5){
      //if(c1_tmp > c2_tmp){
      SwitchZ();
    }
  }

  TLorentzVector p1p = _p1p;
  TLorentzVector p1m = _p1m;
  TLorentzVector p2p = _p2p;
  TLorentzVector p2m = _p2m;

  _H = p1p+p1m+p2p+p2m;
  _Z1 = p1p+p1m;
  _Z2 = p2p+p2m;

  TLorentzVector Hmom = p1p+p1m+p2p+p2m;
  TVector3 Hboost = Hmom.BoostVector();
  TVector3 direction = Hmom.Vect().Unit();

  

  p1p.Boost(-Hboost);
  p1m.Boost(-Hboost);
  p2p.Boost(-Hboost);
  p2m.Boost(-Hboost);

  TLorentzVector Z1mom = p1p + p1m;
  TLorentzVector Z2mom = p2p + p2m;

  //First we get everything from the Higgs rest frame
  
  _cosTHETA = Z2mom.Vect().Unit().Dot(direction);
  
  TVector3 p1p_cross_p1m = p1p.Vect().Cross(p1m.Vect());
  TVector3 p2p_cross_p2m = p2p.Vect().Cross(p2m.Vect());
  double dot_phi = p1p.Vect().Dot(p2p_cross_p2m);
  
  _phi = p1p_cross_p1m.Angle(p2p_cross_p2m);
  if(dot_phi < 0.0 && _phi > 0.0){
    _phi = TMath::Pi()*2.0-_phi;
  }

  TVector3 H_cross_Z2 = direction.Cross(Z2mom.Vect());

  //p2p_cross_p2m.Rotate(TMath::Pi()/2.0, Z2mom.Vect());

  _PHI = H_cross_Z2.Angle(p2p_cross_p2m);

  double dot_PHI = direction.Dot(p2p_cross_p2m);
  if(dot_PHI > 0.0 && _PHI > 0.0){
    _PHI = TMath::Pi()*2.0-_PHI;
  }

  //Now we move to Z rest frame for c1/c2

  TVector3 Z1boost = Z1mom.BoostVector();
  TVector3 Z2boost = Z2mom.BoostVector();

  p1p.Boost(-Z1boost);
  p1m.Boost(-Z1boost);

  p2p.Boost(-Z2boost);
  p2m.Boost(-Z2boost);

  _c1 = p1m.Vect().Unit().Dot(-Z1boost.Unit());
  _c2 = p2m.Vect().Unit().Dot(-Z2boost.Unit());
}

