
using namespace std;

#include <Gen.hh>

using namespace std;

Gen::Gen(double mass, double width){
  Init(mass, width);
}

void Gen::Init(double mass, double width) {
  _mH  = mass;
  _wH  = width;
  _mZ  = 91.1876;      // PDG value
  _wZ  = 2.4952;       // PDG value
  _mMu = 0.105658367 ; // PDG value
  _eta_bar = 0.1497;
  _pi = asin(1.0)*2.0;
  _ca = -0.5014;
  _cv = -0.0379;
  _g1 = (_cv*_cv+_ca*_ca)*(_cv*_cv+_ca*_ca);
  _gs = -4.0*_cv*_ca*(_cv*_cv+_ca*_ca);
  _gt = -1.0*(_cv*_cv+_ca*_ca)*(_cv*_cv+_ca*_ca)*_eta_bar;
  _gss = 4.0*_cv*_cv*_ca*_ca;
  _gst = 4.0*_cv*_ca*(_cv*_cv+_ca*_ca)*_eta_bar;
  _gsst = -4.0*_cv*_cv*_ca*_ca*_eta_bar;

  //
  // For the spin 1 case, X, P and delta are defined in the particular
  // model's files, not here!!!
  //

  //Here we put in coefficients from integrating over different angles
  _c1 = 0.0;
  _c2 = 0.0;
  _cT = 0.0;
  _s1 = _pi/2.0;
  _s2 = _pi/2.0; 
  _s1c1 = 0.0;
  _s2c2 = 0.0;
  _sT = _pi/2.0;
  _sTcT = 0.0;
  _c = 0.0;
  _cPHI = 0.0;
  _c2PHI = 0.0;
  _s = 0.0;
  _sc = 0.0;
  _sPHI = 0.0;
  _s2PHI = 0.0;
  _c1_2 = 2.0/3.0;
  _c2_2 = 2.0/3.0;
  _s1_2 = 4.0/3.0;
  _s2_2 = 4.0/3.0;
  _sT_2 = 4.0/3.0;
  _cT_2 = 2.0/3.0;
  _c_2 = _pi;
  _s_2 = _pi;
  _cPHI_2 = _pi;
  _c1_const = 2.0;
  _c2_const = 2.0;
  _phi_const = 2.0*_pi;
  _PHI_const = 2.0*_pi;
  _cosTHETA_const = 2.0;
 
}

double Gen::Pcms(double mH, double m2){
  if(mH - _mZ - m2 < 0.0) return -1.0;

  double ret = (1.0/(2.0*mH))*sqrt(mH*mH-(_mZ-m2)*(_mZ-m2))*
    sqrt(mH*mH-(_mZ+m2)*(_mZ+m2));

  return ret;
}

double Gen::BreitWigner(double mstar, double m, double w){

  double ret = 1.0/((mstar*mstar-m*m)*(mstar*mstar-m*m) + mstar*mstar*w*w);

  return ret;
}

double Gen::Gamma_a(double mstar){
  double gamma_1 = (_mH*_mH-mstar*mstar+_mZ*_mZ)/(2.0*_mH*_mZ);
  double gamma_2 = (_mH*_mH+mstar*mstar-_mZ*_mZ)/(2.0*_mH*mstar);

  double beta_1 = sqrt(1.0-1.0/(gamma_1*gamma_1));
  double beta_2 = sqrt(1.0-1.0/(gamma_2*gamma_2));

  double ret = gamma_1*gamma_2*(1.0+beta_1*beta_2);
  
  return ret;
}

double Gen::Gamma_b(double mstar){
  double gamma_a = Gamma_a(mstar);

  return (sqrt(gamma_a*gamma_a-1.0));
}
  
