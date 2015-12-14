using namespace std;
#include <TLorentzVector.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <ZZ_bkg.hh>

using namespace std;

ZZ_bkg::ZZ_bkg(){
  Init();
}

void ZZ_bkg::Init() {
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

  _mZPDF = (TH1D*) new TH1D("_mZPDF", "_mZPDF", 5000, _mZ-5.0*_wZ, _mZ+5.0*_wZ);
  //Initialize Z mass PDF's
  for(int i = 0; i < 5000; i++){
    
    _mZPDF->Fill(_mZPDF->GetBinCenter(i+1),BreitWigner(_mZPDF->GetBinCenter(i+1),_mZ, _wZ));
  }
  _mZPDF->Scale(1.0/_mZPDF->Integral());
}

void ZZ_bkg::SetBoostDist(string filename) {
  TBranch *b_N_M, *b_min_M, *b_max_M;
  TBranch *b_N_pt, *b_min_pt, *b_max_pt;
  TBranch *b_N_eta, *b_min_eta, *b_max_eta;
  
  TFile* hboostfile = TFile::Open(filename.c_str());
  TTree* param = (TTree*) hboostfile->Get("data");
  param->SetBranchAddress("N_M_pteta", &N_M, &b_N_M);
  param->SetBranchAddress("min_M_pteta", &min_M, &b_min_M);
  param->SetBranchAddress("max_M_pteta", &max_M, &b_max_M);
  param->SetBranchAddress("N_pt", &N_pt, &b_N_pt);
  param->SetBranchAddress("min_pt", &min_pt, &b_min_pt);
  param->SetBranchAddress("max_pt", &max_pt, &b_max_pt);
  param->SetBranchAddress("N_eta", &N_eta, &b_N_eta);
  param->SetBranchAddress("min_eta", &min_eta, &b_min_eta);
  param->SetBranchAddress("max_eta", &max_eta, &b_max_eta);
  param->GetEntry(0);
  param->Delete();
  hboostfile->Close();

  for(int i_M = 0; i_M < N_M; i_M++){
    char *name = new char[100];
    sprintf(name, "h_pteta_%d", i_M);
    _BoostDist.push_back(new TH2D(name,name,N_pt,min_pt,max_pt,N_eta,min_eta,max_eta));
  }

  TFile* boostfile = TFile::Open(filename.c_str());
  TH2D* temp;
  for(int i_M = 0; i_M < N_M; i_M++){
    char *name = new char[100];
    sprintf(name, "h_pteta_%d", i_M);
    temp = (TH2D*) boostfile->Get(name);
    _BoostDist[i_M]->Add(temp);
    temp->Delete();
  }
  boostfile->Close();
 
}

void ZZ_bkg::GenBoost(double mH){
  int i_M = int((mH-min_M)*double(N_M)/(max_M-min_M));
  if(i_M < 0) i_M = 0;
  if(i_M >= N_M) i_M = N_M-1;
  _BoostDist[i_M]->GetRandom2(_pTH, _etaH);
  _phiH = gRandom->Rndm()*4.*asin(1.);
}

void ZZ_bkg::SetSmearingFunction(SmearingFunction* smear ){
  _cmsSmear = smear;
}

void ZZ_bkg::LoadEvent(double M, double cosTHETA, double PHI, 
		       double c1, double c2, double phi){
  _massHGEN = M;
  _c1GEN = c1;
  _c2GEN = c2;
  _phiGEN = phi;
  _PHIGEN = PHI;
  _cosTHETAGEN = cosTHETA;
  
  
  //
  //Now we get the Higgs and Z1 masses
  //
  bool cont = true;
  while(cont){
    _massZ2GEN = _mZPDF->GetRandom();
    _massZ1GEN = _mZPDF->GetRandom();
    if(_massZ1GEN+_massZ2GEN <= _massHGEN){
      cont = false;
    }
  }
}

void ZZ_bkg::LoadEvent(TLorentzVector p1p, TLorentzVector p1m, 
		       TLorentzVector p2p, TLorentzVector p2m){
  _p1pGEN = p1p;
  _p1mGEN = p1m;
  _p2pGEN = p2p;
  _p2mGEN = p2m;
}
 
void ZZ_bkg::CalcGenKinematics() {

  _HGEN = _p1pGEN+_p1mGEN+_p2pGEN+_p2mGEN;
  _Z1GEN = _p1pGEN+_p1mGEN;
  _Z2GEN = _p2pGEN+_p2mGEN;

  TLorentzVector p1p = _p1pGEN;
  TLorentzVector p1m = _p1mGEN;
  TLorentzVector p2p = _p2pGEN;
  TLorentzVector p2m = _p2mGEN;

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

void ZZ_bkg::SmearMomenta(int type) {
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

bool ZZ_bkg::PassCuts(double eta_cut, double pt_cut) {

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

double ZZ_bkg::BreitWigner(double mstar, double m, double w){

  double ret = 1.0/((mstar*mstar-m*m)*(mstar*mstar-m*m) + mstar*mstar*w*w);

  return ret;
}

void ZZ_bkg::CalcGenMomenta() {

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

void ZZ_bkg::SwitchZ(){
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
  
  

void ZZ_bkg::CalcRecoKinematics(bool ID) {
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


double ZZ_bkg::Prob(double mH, double cosTHETA, double PHI, double c1, double c2, double phi){

  double _eta = 0.0056;
  double S = mH*mH/(_mZ*_mZ);
  //double S = mH/_mZ;
  double s1 = sqrt(1.0-c1*c1);
  double s2 = sqrt(1.0-c2*c2);
  double sinTHETA = sqrt(1.0-cosTHETA*cosTHETA);

  double C0 = -4.
    +4.*pow(c1,2.)*pow(c2,2.)
    -S
    -pow(c1,2.)*pow(c2,2.)*S
    +8.*c1*c2*S*_eta
    +32.*s1*s2*_eta*cos(phi)+ 
    (-4.+S)*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    -4.*s1*s2*(2.*c1*c2+8.*_eta+(-2.+S)*s1*s2*cos(phi))*cos(phi-PHI)*cos(PHI)
    +4.*S*pow(s1,2.)*pow(s2,2.)*pow(cos(phi-PHI),2.)*pow(cos(PHI),2.);
  
  C0 *= pow(-2.+S,2.);

  double C1 = 2.*pow(c1,2.)*c2*s2*cos(PHI)+
    2.*pow(c2,2.)*c1*s1*cos(phi-PHI)+
    c2*(s1*(-4.*(-6.+S)*_eta+(-2.+S)*s1*s2*cos(phi))*cos(phi-PHI)+
	s2*(-4.+S-2.*S*pow(s1,2.)*pow(cos(phi-PHI),2.))*cos(PHI))+ 
    c1*(s2*(-4.*(-6.+S)*_eta+(-2.+S)*s1*s2*cos(phi))*cos(PHI)+
	s1*(-4.+S-2.*S*pow(s2,2.)*pow(cos(PHI),2.))*cos(phi-PHI));
  
  C1 *= -4.*cosTHETA*(-2.+S)*sqrt(S)*sinTHETA;
  
  double C2 = -16.
    +16.*pow(c1,2.)*pow(c2,2.)
    -12.*S
    +4.*pow(c1,2.)*pow(c2,2.)*S
    +4.*pow(c1,2.)*pow(S,2.)
    +4.*pow(c2,2.)*pow(S,2.)
    -8.*pow(c1,2.)*pow(c2,2.)*pow(S,2.)
    +pow(S,3.)
    -pow(c1,2.)*pow(S,3.)
    -pow(c2,2.)*pow(S,3.)
    +pow(c1,2.)*pow(c2,2.)*pow(S,3.)
    -32.*c1*c2*S*_eta
    -32.*c1*c2*s1*s2*cos(phi)
    +32.*c1*c2*S*s1*s2*cos(phi)
    -8.*c1*c2*pow(S,2.)*s1*s2*cos(phi)
    +128.*S*s1*s2*_eta*cos(phi)
    -32.*pow(S,2.)*s1*s2*_eta*cos(phi)
    +16.*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.) 
    -36.*S*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    +16*pow(S,2.)*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.) 
    -2.*pow(S,3.)*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    +4.*S*(-4.+S+pow(c2,2.)*S)*pow(s1,2.)*pow(cos(phi- PHI),2.)
    +8.*s1*s2*
    (4.*(c1*c2*pow(-1.+S,2.)+4.*_eta)+
     (-4.+10.*S-6.*pow(S,2.)+pow(S,3.))*s1*s2*cos(phi))*
    cos(phi-PHI)*cos(PHI)-4.*S*pow(s2,2.)*
    (4.-(1.+pow(c1,2.))*S+2.*pow(-2.+S,2.)*pow(s1,2.)*pow(cos(phi-PHI),2.))*
    pow(cos(PHI),2.);
  
  C2 *= pow(cosTHETA,2.);

  double C3 = -4.*pow(c1,2.)*c2*s2*cos(PHI)
    -4.*pow(c2,2.)*c1*c2*cos(phi-PHI)
    +c2*((-4.+S)*s1*(4.*_eta-s1*s2*cos(phi))*cos(phi-PHI)+s2*(4.-S+2.*(-2.+S)*pow(s1,2.)*pow(cos(phi-PHI),2.))*cos(PHI)) 
    +c1*((-4.+S)*s2*(4.*_eta-s1*s2*cos(phi))*cos(PHI)+s1*(4.-S+2*(-2.+S)*pow(s2,2.)*pow(cos(PHI),2.))*cos(phi-PHI));

  C3 *= -4.*pow(cosTHETA,3.)*pow(S,1.5)*sinTHETA;

  double C4 = 16.*pow(c1,2.)*pow(c2,2.)
    -4.*pow(c1,2.)*S
    -4.*pow(c2,2.)*S
    +pow(c1,2.)*pow(S,2.)
    +pow(c2,2.)*pow(S,2.)
    +32.*c1*c2*S*_eta
    -8.*c1*c2*pow(S,2.)*_eta
    -32.*c1*c2*s1*s2*cos(phi)
    +8.*c1*c2*S*s1*s2*cos(phi)
    +16.*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    -8.*S*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    +pow(S,2.)*pow(s1,2.)*pow(s2,2.)*pow(cos(phi),2.)
    -4.*(-4.+S+pow(c2,2.)*S)*pow(s1,2.)*pow(cos(phi-PHI),2.)
    -4.*s1*s2*(2.*c1*c2*(-4.+3.*S)-8.*(-4.+S)*_eta+(8.-6.*S+pow(S,2.))*s1*s2*cos(phi))*cos(phi-PHI)*cos(PHI)
    +4.*pow(s2,2.)*(4-(1.+pow(c1,2.))*S+pow(-2.+S,2.)*pow(s1,2.)*pow(cos(phi-PHI),2.))*pow(cos(PHI),2);

  C4 *= pow(cosTHETA,4)*S;

  double val = -1.0*(C0+C1+C2+C3)/pow(pow(-2.+S,2.)-pow(cosTHETA,2.)*(-4.+S)*S,2.);

 

  return val;
}
