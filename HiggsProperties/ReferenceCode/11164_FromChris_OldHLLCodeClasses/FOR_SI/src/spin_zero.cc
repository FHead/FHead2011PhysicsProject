
using namespace std;
#include <TLorentzVector.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <Gen.cc>
#include <spin_zero.hh>

using namespace std;

spin_zero::spin_zero(double mass, double width) : Gen(mass, width){
  _X = 1.;
  _P = 0.;
  _Q = 0.;
  _Y = 0.;
  _XP = 0.0;
  _XQ = 0.0;
  _XY = 0.0;

};

double spin_zero::Prob_M(double m){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

  //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  //Here, these are the mass variables _squared_ (without the square explicitly
  
  double g_b = Gamma_b(m);
  double g_a = Gamma_a(m);
 

  //First X^2 part
  double XX = 2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const
    + 2.0*_eta_bar*_eta_bar*g_a*_c*_s1*_s2
    + _s1_2*_s2_2*g_a*g_a*_phi_const
    + _c_2*_s1_2*_s2_2
    - 0.5*_s1_2*_s2_2*_phi_const
    + 0.5*_c1_2*_c2_2*_phi_const
    + 0.5*_c1_2*_c2_const*_phi_const
    + 0.5*_c2_2*_c1_const*_phi_const
    + 0.5*_c1_const*_c2_const*_phi_const
    + 2.0*g_a*_c*_s1c1*_s2c2;

  XX *= _mZ*_mZ*m*m*_X*_X*_PHI_const*_cosTHETA_const;

  //Now Q^2/P^2 part
  double PP = _c1_2*_c2_2*_phi_const 
    + 2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const
    - _c_2*_s1_2*_s2_2
    + 1.0*_c1_const*_c2_const*_phi_const;

  double QQ = PP*_mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_Q*_Q*_PHI_const*_cosTHETA_const;
  PP *= _mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_P*_P*_PHI_const*_cosTHETA_const;

  //Now Y^2 part
  double YY = _Y*_Y*_mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*g_b*g_b*_s1_2*_s2_2*_phi_const*_PHI_const*_cosTHETA_const;

  //Now XQ part
  double XQ = _c1*_c2_const*_phi_const
    + _c2*_c1_const*_phi_const
    + _c1_2*_c2*_phi_const
    + _c1*_c2_2*_phi_const
    + g_a*_c*_s1c1*_s2
    + g_a*_c*_s1*_s2c2;

  XQ *= -2.0*_eta_bar*_mZ*_mZ*_mZ*m*m*m*g_b*_XQ*_PHI_const*_cosTHETA_const;

  //Now XP part
  double XP = _sc*_s1_2*_s2_2
    + g_a*_s*_s1c1*_s2c2
    + g_a*_eta_bar*_eta_bar*_s1*_s2*_s;

  XP *= 2.0*_mZ*_mZ*_mZ*m*m*m*g_b*_XP*_PHI_const*_cosTHETA_const;

  //Now XY part

  double XY = _c*_s1c1*_s2c2
    + g_a*_s1_2*_s2_2*_phi_const
    + _eta_bar*_eta_bar*_c*_s1*_s2;

  XY *= -2.0*_mZ*_mZ*_mZ*m*m*m*g_b*g_b*_XY*_PHI_const*_cosTHETA_const;

  double ME = XX + PP + QQ + YY + XP + XQ + XY;

  return (ME*PS);


}

double spin_zero::Prob_ANGLES(double m, double cosTHETA, double PHI){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

  //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  //Here, these are the mass variables _squared_ (without the square explicitly
  
  double g_b = Gamma_b(m);
  double g_a = Gamma_a(m);
 

  //First X^2 part
  double XX = 2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const
    + 2.0*_eta_bar*_eta_bar*g_a*_c*_s1*_s2
    + _s1_2*_s2_2*g_a*g_a*_phi_const
    + _c_2*_s1_2*_s2_2
    - 0.5*_s1_2*_s2_2*_phi_const
    + 0.5*_c1_2*_c2_2*_phi_const
    + 0.5*_c1_2*_c2_const*_phi_const
    + 0.5*_c2_2*_c1_const*_phi_const
    + 0.5*_c1_const*_c2_const*_phi_const
    + 2.0*g_a*_c*_s1c1*_s2c2;

  XX *= _mZ*_mZ*m*m*_X*_X;

  //Now Q^2/P^2 part
  double PP = _c1_2*_c2_2*_phi_const 
    + 2.0*_eta_bar*_eta_bar*_c1*_c2*_phi_const
    - _c_2*_s1_2*_s2_2
    + 1.0*_c1_const*_c2_const*_phi_const;

  double QQ = PP*_mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_Q*_Q;
  PP *= _mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_P*_P;

  //Now Y^2 part
  double YY = _Y*_Y*_mZ*_mZ*_mZ*_mZ*g_b*g_b*g_b*g_b*_s1_2*_s2_2*_phi_const;

  //Now XQ part
  double XQ = _c1*_c2_const*_phi_const
    + _c2*_c1_const*_phi_const
    + _c1_2*_c2*_phi_const
    + _c1*_c2_2*_phi_const
    + g_a*_c*_s1c1*_s2
    + g_a*_c*_s1*_s2c2;

  XQ *= -2.0*_eta_bar*_mZ*_mZ*_mZ*m*m*m*g_b*_XQ;

  //Now XP part
  double XP = _sc*_s1_2*_s2_2
    + g_a*_s*_s1c1*_s2c2
    + g_a*_eta_bar*_eta_bar*_s1*_s2*_s;

  XP *= 2.0*_mZ*_mZ*_mZ*m*m*m*g_b*_XP;

  //Now XY part

  double XY = _c*_s1c1*_s2c2
    + g_a*_s1_2*_s2_2*_phi_const
    + _eta_bar*_eta_bar*_c*_s1*_s2;

  XY *= -2.0*_mZ*_mZ*_mZ*m*m*m*g_b*g_b*_XY;

  double ME = XX + PP + QQ + YY + XP + XQ + XY;

  return (ME*PS);


}
  

double spin_zero::Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

   //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  //Here, these are the mass variables _squared_ (without the square explicitly

  double g_b = Gamma_b(m);
  double g_a = Gamma_a(m);
  
  double s1 = sqrt(1.0-c1*c1);
  double s2 = sqrt(1.0-c2*c2);
  double c = cos(phi);
  double s = sin(phi);
 

  //First X^2 part
  double XX = 2.0*_eta_bar*_eta_bar*c1*c2
    + 2.0*_eta_bar*_eta_bar*g_a*c*s1*s2
    + s1*s1*s2*s2*g_a*g_a
    + c*c*s1*s1*s2*s2
    - 0.5*s1*s1*s2*s2
    + 0.5*c1*c1*c2*c2
    + 0.5*c1*c1
    + 0.5*c2*c2
    + 0.5
    + 2.0*g_a*c*c1*c2*s1*s2;

  XX *= _mZ*_mZ*m*m*_X*_X;

  //Now Q^2/P^2 part
  double PP = c1*c1*c2*c2 
    + 2.0*_eta_bar*_eta_bar*c1*c2
    - c*c*s1*s1*s2*s2
    + 1.0;

  double QQ = PP*_mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_Q*_Q;
  PP *= _mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*_P*_P;

  //Now Y^2 part
  double YY = _Y*_Y*_mZ*_mZ*_mZ*_mZ*m*m*m*m*g_b*g_b*g_b*g_b*s1*s1*s2*s2;

  //Now XQ part
  double XQ = c1
    + c2
    + c1*c1*c2
    + c1*c2*c2
    + g_a*c*s1*c1*s2
    + g_a*c*s1*s2*c2;

  XQ *= -2.0*_eta_bar*_mZ*_mZ*_mZ*m*m*m*g_b*_XQ;

  //Now XP part
  double XP = s*c*s1*s1*s2*s2
    + g_a*s*s1*c1*s2*c2
    + g_a*_eta_bar*_eta_bar*s1*s2*s;

  XP *= 2.0*_mZ*_mZ*_mZ*m*m*m*g_b*_XP;

  //Now XY part

  double XY = c*s1*c1*s2*c2
    + g_a*s1*s1*s2*s2
    + _eta_bar*_eta_bar*c*s1*s2;

  XY *= -2.0*_mZ*_mZ*_mZ*m*m*m*g_b*g_b*_XY;

  double ME = XX + PP + QQ + YY + XP + XQ + XY;

  return (ME*PS);
}
