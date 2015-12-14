using namespace std;
#include <TLorentzVector.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <Gen.cc>
#include <zero_minus.hh>

using namespace std;

zero_minus::zero_minus(double mass, double width) : Gen(mass, width){};

double zero_minus::Prob_M(double m){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

   double g_b = Gamma_b(m);
 

  //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  

  //here we calculate the ME squared, integrated over all other angles
  double ME = _PHI_const*_cosTHETA_const*m*m*m*m*_mZ*_mZ*_mZ*_mZ*g_b*g_b;

  ME *= _c1_2*_c2_2*_phi_const + 2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const-
    _c_2*_s1_2*_s2_2+_c1_const*_c2_const*_phi_const;

  return ME*PS;
}

double zero_minus::Prob_ANGLES(double m, double cosTHETA, double PHI){

  //here we calculate the ME squared, integrated over all other angles
  double ME = _c1_2*_c2_2*_phi_const + 
    2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const-
    _c_2*_s1_2*_s2_2+_c1_const*_c2_const*_phi_const;
  
  return ME;
}
  

double zero_minus::Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi){
 
  double c = cos(phi);
  double s1 = sqrt(1.0-c1*c1);
  double s2 = sqrt(1.0-c2*c2);

  double ME = c1*c1*c2*c2+2.0*_eta_bar*_eta_bar*c1*c2-c*c*s1*s1*s2*s2+1.0;

  return ME;
}
