using namespace std;
#include <TLorentzVector.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <Gen.cc>
#include <zero_plus.hh>

using namespace std;

zero_plus::zero_plus(double mass, double width) : Gen(mass, width){};

double zero_plus::Prob_M(double m){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

  double g_a = Gamma_a(m);
 

  //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  

  //here we calculate the ME squared, integrated over all other angles
  double ME = _PHI_const*_cosTHETA_const*_mZ*m*m*_mZ*_mZ;

  ME *= 2.0*(_c1*_c1*_phi_const + _c*_s1*_s1*g_a)*_eta_bar*_eta_bar+
    _s1_2*_s2_2*_phi_const*g_a*g_a + 2.0*_c*_c1*_c2*_s1*_s2*g_a+
    0.5*((2.0*_c_2-_phi_const)*_s1_2*_s2_2+(_c1_2*_c2_2+2.0*_c1_2*_c2_const+
					    _c1_const*_c2_const)*_phi_const);

 

  return ME*PS;
}

double zero_plus::Prob_ANGLES(double m, double cosTHETA, double PHI){
  double g_a = Gamma_a(m);

  //here we calculate the ME squared, integrated over all other angles
  double ME = 2.0*(_c1*_c1*_phi_const + _c*_s1*_s1*g_a)*_eta_bar*_eta_bar+
    _s1_2*_s2_2*_phi_const*g_a*g_a + 2.0*_c*_c1*_c2*_s1*_s2*g_a+
    0.5*((2.0*_c_2-_phi_const)*_s1_2*_s2_2+(_c1_2*_c2_2+2.0*_c1_2*_c2_const+
					    _c1_const*_c2_const)*_phi_const);
  
  return ME;
}
  

double zero_plus::Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi){
  double g_a = Gamma_a(m);
  double c = cos(phi);
  double s1 = sqrt(1.0-c1*c1);
  double s2 = sqrt(1.0-c2*c2);

  double ME = 2.0*(c1*c2 +c*s1*s2*g_a)*_eta_bar*_eta_bar+s1*s1*s2*s2*g_a*g_a+2.0*c*c1*c2*s1*s2*g_a+
    0.5*((2.0*c*c-1.0)*s1*s1*s2*s2+(c1*c1+1.0)*(c2*c2+1.0));

  return ME;
}
