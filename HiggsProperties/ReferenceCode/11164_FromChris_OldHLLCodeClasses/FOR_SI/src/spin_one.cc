using namespace std;
#include <TLorentzVector.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <iostream>
#include <Gen.cc>
#include <spin_one.hh>

using namespace std;

spin_one::spin_one(double mass, double width) : Gen(mass, width){
  _X = 1.;
  _P = 0.;
  _XP = 0.0;
  _delta = 0.0;

};

double spin_one::Prob_M(double m){
  double pcms = Pcms(_mH, m);
 
  cout << _X << " " << _P << endl;

  if(pcms < 0.0) return 0.0;

  //Here, these are the mass variables _squared_ (without the square explicitly)
  double md = _mZ*_mZ-m*m;
  double M1 = _mH*_mH-3.0*_mZ*_mZ-m*m;
  double M2 = _mH*_mH-_mZ*_mZ-3.0*m*m;
  double M3 = _mH*_mH - 2.0*(_mZ*_mZ+m*m);
  //double M4 = _mH*_mH - (_mZ*_mZ+m*m);

  cout << M1 << " " << M2 << " " << M3 << " " << md << endl;

  double g_b = Gamma_b(m);

  //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

   //First X^2 part
  double XX = _g1*2.0*md*md*_phi_const*_s1_2*_s2_2*_sT_2*_PHI_const
    -_g1*_mH*_mH*_mZ*_mZ*_c2PHI*_c*_s1_2*_s2_2*_sT_2
    +_g1*_mH*_mH*_mZ*_mZ*_s2PHI*_s*_s1_2*_s2_2*_sT_2
    -_g1*_mH*_mH*m*m*_c2PHI*_s1_2*_s2_2*_phi_const*_sT_2;
  XX += _g1*_mH*_mH*2.0*m*m*_s1_2*_c2_const*_phi_const*_PHI_const*_cosTHETA_const
    + _g1*_mH*_mH*2.0*m*m*_cT_2*_s1_2*_c2_const*_phi_const*_PHI_const
    + _g1*_mH*_mH*2.0*_mZ*_mZ*_s2_2*_c1_const*_phi_const*_PHI_const*_cosTHETA_const
    + _g1*_mH*_mH*2.0*_mZ*_mZ*_cT_2*_s2_2*_c1_const*_phi_const*_PHI_const
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*_s1_2*_s2_2*_phi_const*_cosTHETA_const*_PHI_const
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*_cT_2*_s1_2*_s2_2*_phi_const*_PHI_const;
  XX += 4.0*_g1*_mH*md*_sTcT*_mZ*_sPHI*_c*_s2_2*_s1c1
    + 4.0*_g1*_mH*md*_sTcT*_mZ*_cPHI*_s*_s1c1*_s2_2
    - 4.0*_g1*_mH*md*_sTcT*m*_sPHI*_s2c2*_s1_2*_phi_const;
  XX += -2.0*_mH*_mH*_mZ*m*_g1*_c*_s1c1*_s2c2*_PHI_const*_cosTHETA_const
    + 2.0*_mH*_mH*_mZ*m*_gss*_c*_s1*_s2
    - 2.0*_mH*_mH*_mZ*m*_g1*_cT_2*_s1c1*_s2c2*_c*_PHI_const
    + 2.0*_mH*_mH*_mZ*m*_gss*_cT_2*_s1*_s2*_c*_PHI_const
    - 2.0*_mH*_mH*_mZ*m*_sT_2*_g1*_c2PHI*_c*_s1c1*_s2c2
    + 2.0*_mH*_mH*_mZ*m*_sT_2*_g1*_s2PHI*_s*_s1c1*_s2c2
    - 2.0*_mH*_mH*_mZ*m*_sT_2*_gss*_c2PHI*_c*_s1*_s2
    + 2.0*_mH*_mH*_mZ*m*_sT_2*_gss*_s2PHI*_s*_s1*_s2;

  XX *= 4.0*_mZ*_mZ*m*m*g_b*g_b*_X*_X;

  //Now the P^2 part
  double PP = _g1*_mH*_mH*_sT_2*M2*M2*_mZ*_mZ*_c2PHI*_c*_s1_2*_s2_2
    - _g1*_mH*_mH*_sT_2*M2*M2*_mZ*_mZ*_s2PHI*_s*_s1_2*_s2_2
    + _g1*_mH*_mH*_sT_2*M1*M1*m*m*_c2PHI*_s1_2*_s2_2*_phi_const;
  PP += 8.0*_mZ*_mZ*m*m*md*md*_sT_2*_g1*_c1_2*_c2_const*_phi_const*_PHI_const
    + 8.0*_mZ*_mZ*m*m*md*md*_sT_2*_g1*_c2_2*_c1_const*_phi_const*_PHI_const
    + 8.0*_mZ*_mZ*m*m*md*md*_sT_2*_g1*_s1_2*_s2_2*_s_2*_PHI_const
    + 16.0*_mZ*_mZ*m*m*md*md*_sT_2*_gss*_c1*_c2*_phi_const*_PHI_const;
  PP += _g1*_mH*_mH*2.0*M1*M1*m*m*_s1_2*_c2_const*_phi_const*_cosTHETA_const*_PHI_const
    + _g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*_s2_2*_c1_const*_phi_const*_cosTHETA_const*_PHI_const
    - _g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*_s1_2*_s2_2*_phi_const*_cosTHETA_const*_PHI_const
    + _cT_2*_g1*_mH*_mH*2.0*M1*M1*m*m*_s1_2*_c2_const*_phi_const*_PHI_const
    + _cT_2*_g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*_s2_2*_c1_const*_phi_const*_PHI_const
    - _cT_2*_g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*_s1_2*_s2_2*_phi_const*_PHI_const;
  PP += -8.0*_mH*md*_mZ*m*_sTcT*M2*_mZ*_g1*_sPHI*_c_2*_s2c2*_s1_2
    - 8.0*_mH*md*_mZ*m*_sTcT*M2*_mZ*_g1*_cPHI*_sc*_s2c2*_s1_2
    - 8.0*_mH*md*_mZ*m*_sTcT*M2*_mZ*_g1*_sPHI*_c1_2*_s2c2*_phi_const
    - 8.0*_mH*md*_mZ*m*_sTcT*M2*_mZ*_gss*_sPHI*_s2*_c1*_phi_const;
  PP += 8.0*_mH*md*_mZ*m*_sTcT*M1*m*_g1*_sPHI*_c*_s1c1*_s2_2
    + 8.0*_mH*md*_mZ*m*_sTcT*M1*m*_g1*_sPHI*_c*_s1c1*_c2_2
    + 8.0*_mH*md*_mZ*m*_sTcT*M1*m*_g1*_cPHI*_s*_s1c1*_c2_2
    + 8.0*_mH*md*_mZ*m*_sTcT*M1*m*_gss*_sPHI*_c*_s1*_c2
    + 8.0*_mH*md*_mZ*m*_sTcT*M1*m*_gss*_cPHI*_s*_s1*_c2;
  PP += 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*_s1c1*_s2c2*_c*_cosTHETA_const*_PHI_const
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_gss*_c*_s1*_s2*_cosTHETA_const*_PHI_const
    + 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*_cT_2*_s1c1*_s2c2*_c*_PHI_const
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_gss*_cT_2*_s1*_s2*_c*_PHI_const
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_sT_2*_g1*_c2PHI*_c*_s1c1*_s2c2
    + 2.0*_mH*_mH*M1*M2*_mZ*m*_sT_2*_g1*_s2PHI*_s*_s1c1*_s2c2
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_sT_2*_gss*_c2PHI*_c*_s1*_s2
    + 2.0*_mH*_mH*M1*M2*_mZ*m*_sT_2*_gss*_s2PHI*_s*_s1*_s2;

  PP *= _P*_P;

  //Now the XP cosdelta interference term
  double XPcos = _g1*_mH*_mH*_sT_2*M1*m*m*_s2PHI*_s1_2*_s2_2*_phi_const
    - _g1*_mH*_mH*_sT_2*M2*_mZ*_mZ*_s2PHI*_c*_s1_2*_s2_2
    - _g1*_mH*_mH*_sT_2*M2*_mZ*_mZ*_c2PHI*_s*_s1_2*_s2_2;
  XPcos += 2.0*_g1*_mH*md*_sTcT*m*2.0*_mZ*_mZ*_sPHI*_sc*_s1_2*_s2c2
    + 2.0*_g1*_mH*md*_sTcT*m*2.0*_mZ*_mZ*_cPHI*_s_2*_s1_2*_s2c2
    - 2.0*_g1*_mH*md*_sTcT*m*M1*_cPHI*_s1_2*_s2c2*_phi_const;
  XPcos += -2.0*_g1*_mH*md*_sTcT*_mZ*2.0*m*m*_sPHI*_s*_s2_2*_s1c1
    - 2.0*_g1*_mH*md*_sTcT*_mZ*M2*_cPHI*_c*_s2_2*_s1c1
    + 2.0*_g1*_mH*md*_sTcT*_mZ*M2*_sPHI*_s*_s2_2*_s1c1;
  XPcos += -2.0*_mZ*m*_mH*_mH*M3*_g1*_s1c1*_s2c2*_s*_cosTHETA_const*_PHI_const
    + 2.0*_mZ*m*_mH*_mH*M3*_gss*_s*_s1*_s2*_cosTHETA_const*_PHI_const
    - 2.0*_mZ*m*_mH*_mH*M3*_g1*_cT_2*_s1c1*_s2c2*_s*_PHI_const
    + 2.0*_mZ*m*_mH*_mH*M3*_gss*_cT_2*_s1*_s2*_s*_PHI_const;
  XPcos += -2.0*_mZ*m*md*_sT_2*_g1*_mH*_mH*_sPHI*_c*_s1c1*_s2c2
    - 2.0*_mZ*m*md*_sT_2*_g1*_mH*_mH*_cPHI*_s*_s1c1*_s2c2
    - 2.0*_mZ*m*md*_sT_2*_g1*2.0*md*_s*_s1c1*_s2c2*_PHI_const
    - 2.0*_mZ*m*md*_sT_2*_gss*_mH*_mH*_sPHI*_c*_s1*_s2
    - 2.0*_mZ*m*md*_sT_2*_gss*_mH*_mH*_cPHI*_s*_s1*_s2
    - 2.0*_mZ*m*md*_sT_2*_gss*2.0*md*_s*_s1*_s2*_PHI_const;
  XPcos += -4.0*_mH*_mZ*m*md*_sTcT*m*_g1*_cPHI*_c*_c2_const*_s1c1
    - 4.0*_mH*_mZ*m*md*_sTcT*m*_g1*_sPHI*_s*_c2_const*_s1c1
    - 4.0*_mH*_mZ*m*md*_sTcT*m*_gss*_cPHI*_c*_s1*_c2
    - 4.0*_mH*_mZ*m*md*_sTcT*m*_gss*_sPHI*_s*_s1*_c2
    - 4.0*_mH*_mZ*m*md*_sTcT*_mZ*_g1*_cPHI*_s2c2*_c1_const*_phi_const
    - 4.0*_mH*_mZ*m*md*_sTcT*_mZ*_gss*_cPHI*_s2*_c1*_phi_const;

  XPcos *= 4.0*_mZ*m*_XP*cos(_delta)*g_b;

  //Now the XP sindelta interference term
  double XPsin = _gs*_mH*md*_sTcT*m*2.0*_mZ*_mZ*_sPHI*_c_2*_s1_2*_s2
    + _gs*_mH*md*_sTcT*m*2.0*_mZ*_mZ*_cPHI*_sc*_s1_2*_s2
    - _gs*_mH*md*_sTcT*m*M1*_sPHI*_s1_2*_s2*_phi_const;
  XPsin += -1.0*_gs*_mH*md*_sTcT*_mZ*2.0*m*m*_sPHI*_s2_2*_s1*_c
    + _gs*_mH*md*_sTcT*_mZ*M2*_sPHI*_c*_s2_2*_s1
    + _gs*_mH*md*_sTcT*_mZ*M2*_cPHI*_s*_s2_2*_s1;
  XPsin += _gs*_mH*_mH*M1*m*m*_s1_2*_c2*_phi_const*_cosTHETA_const*_PHI_const
    + _gs*_mH*_mH*M2*_mZ*_mZ*_s2_2*_c1*_phi_const*_cosTHETA_const*_PHI_const
    + _gs*_mH*_mH*M1*m*m*_cT_2*_s1_2*_c2*_phi_const*_PHI_const
    + _gs*_mH*_mH*M2*_mZ*_mZ*_cT_2*_s2_2*_c1*_phi_const*_PHI_const;
  XPsin += _mZ*m*_gs*_mH*_mH*md*_s1c1*_c*_s2*_cosTHETA_const*_PHI_const
    - _mZ*m*_gs*_mH*_mH*md*_s2c2*_c*_s1*_cosTHETA_const*_PHI_const
    + _mZ*m*_gs*_mH*_mH*md*_cT_2*_s2*_s1c1*_c*_PHI_const
    - _mZ*m*_gs*_mH*_mH*md*_cT_2*_s1*_s2c2*_c*_PHI_const;
  XPsin += -1.0*_mZ*m*_gs*_sT_2*_mH*_mH*M3*_c2PHI*_c*_s2*_s1c1
    + _mZ*m*_gs*_sT_2*_mH*_mH*M3*_s2PHI*_s*_s1c1*_s2
    - _mZ*m*_gs*_sT_2*2.0*md*md*_c*_s1c1*_s2*_PHI_const
    - _mZ*m*_gs*_sT_2*_mH*_mH*M3*_c2PHI*_c*_s2c2*_s1
    + _mZ*m*_gs*_sT_2*_mH*_mH*M3*_s2PHI*_s*_s2c2*_s1
    - _mZ*m*_gs*_sT_2*2.0*md*md*_c*_s2c2*_s1*_PHI_const;
  XPsin += 2.0*_gs*_mH*md*_mZ*m*_sTcT*m*_sPHI*_c*_s1*_c2_const
    + 2.0*_gs*_mH*md*_mZ*m*_sTcT*m*_cPHI*_s*_s1*_c2_const
    - 2.0*_gs*_mH*md*_mZ*m*_sTcT*_mZ*_sPHI*_s2*_c1_const*_phi_const
    + 2.0*_gs*_mH*md*_mZ*m*_sTcT*m*_sPHI*_c*_s1c1*_c2
    + 2.0*_gs*_mH*md*_mZ*m*_sTcT*m*_cPHI*_s*_s1c1*_c2
    - 2.0*_gs*_mH*md*_mZ*m*_sTcT*_mZ*_sPHI*_c1*_s2c2*_phi_const;

  XPsin *= -1.0*_mZ*m*_XP*sin(_delta)*g_b;

  double ME = XX + PP + XPcos + XPsin;

  return ME*PS;
}

double spin_one::Prob_ANGLES(double m, double cosTHETA, double PHI){
  //Here, these are the mass variables _squared_ (without the square explicitly)
  double md = _mZ*_mZ-m*m;
  double M1 = _mH*_mH-3.0*_mZ*_mZ-m*m;
  double M2 = _mH*_mH-_mZ*_mZ-3.0*m*m;
  double M3 = _mH*_mH - 2.0*(_mZ*_mZ+m*m);
  //double M4 = _mH*_mH - (_mZ*_mZ+m*m);

  double g_b = Gamma_b(m);
 
  double cPHI = cos(PHI);
  double c2PHI = cos(2.0*PHI);
  double sPHI = sin(PHI);
  double s2PHI = sin(2.0*PHI);
  double cT = cosTHETA;
  double sT = sqrt(1.0-cT*cT);

  //First X^2 part
  double XX = _g1*sT*sT*2.0*md*md*_phi_const*_s1_2*_s2_2
    -_g1*sT*sT*_mH*_mH*_mZ*_mZ*c2PHI*_c*_s1_2*_s2_2
    +_g1*sT*sT*_mH*_mH*_mZ*_mZ*s2PHI*_s*_s1_2*_s2_2
    -_g1*sT*sT*_mH*_mH*m*m*c2PHI*_s1_2*_s2_2*_phi_const;
  XX += _g1*_mH*_mH*2.0*m*m*_s1_2*_c2_const*_phi_const
    + _g1*_mH*_mH*2.0*m*m*cT*cT*_s1_2*_c2_const*_phi_const
    + _g1*_mH*_mH*2.0*_mZ*_mZ*_s2_2*_c1_const*_phi_const
    + _g1*_mH*_mH*2.0*_mZ*_mZ*cT*cT*_s2_2*_c1_const*_phi_const
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*_s1_2*_s2_2*_phi_const
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*cT*cT*_s1_2*_s2_2*_phi_const;
  XX += 4.0*_g1*_mH*md*cT*sT*_mZ*sPHI*_c*_s2_2*_s1c1
    + 4.0*_g1*_mH*md*cT*sT*_mZ*cPHI*_s*_s1c1*_s2_2
    - 4.0*_g1*_mH*md*cT*sT*m*sPHI*_s2c2*_s1_2*_phi_const;
  XX += -2.0*_mH*_mH*_mZ*m*_g1*_c*_s1c1*_s2c2
    + 2.0*_mH*_mH*_mZ*m*_gss*_c*_s1*_s2
    - 2.0*_mH*_mH*_mZ*m*_g1*cT*cT*_s1c1*_s2c2*_c
    + 2.0*_mH*_mH*_mZ*m*_gss*cT*cT*_s1*_s2*_c
    - 2.0*_mH*_mH*_mZ*m*sT*sT*_g1*c2PHI*_c*_s1c1*_s2c2
    + 2.0*_mH*_mH*_mZ*m*sT*sT*_g1*s2PHI*_s*_s1c1*_s2c2
    - 2.0*_mH*_mH*_mZ*m*sT*sT*_gss*c2PHI*_c*_s1*_s2
    + 2.0*_mH*_mH*_mZ*m*sT*sT*_gss*s2PHI*_s*_s1*_s2;

  XX *= 4.0*_mZ*_mZ*m*m*g_b*g_b*_X*_X;

  //Now the P^2 part
  double PP = _g1*_mH*_mH*sT*sT*M2*M2*_mZ*_mZ*c2PHI*_c*_s1_2*_s2_2
    - _g1*_mH*_mH*sT*sT*M2*M2*_mZ*_mZ*s2PHI*_s*_s1_2*_s2_2
    + _g1*_mH*_mH*sT*sT*M1*M1*m*m*c2PHI*_s1_2*_s2_2*_phi_const;
  PP += 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*_c1_2*_c2_const*_phi_const
    + 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*_c2_2*_c1_const*_phi_const
    + 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*_s1_2*_s2_2*_s_2
    + 16.0*_mZ*_mZ*m*m*md*md*sT*sT*_gss*_c1*_c2*_phi_const;
  PP += _g1*_mH*_mH*2.0*M1*M1*m*m*_s1_2*_c2_const*_phi_const
    + _g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*_s2_2*_c1_const*_phi_const
    - _g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*_s1_2*_s2_2*_phi_const
    + cT*cT*_g1*_mH*_mH*2.0*M1*M1*m*m*_s1_2*_c2_const*_phi_const
    + cT*cT*_g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*_s2_2*_c1_const*_phi_const
    - cT*cT*_g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*_s1_2*_s2_2*_phi_const;
  PP += -8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*sPHI*_c_2*_s2c2*_s1_2
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*cPHI*_sc*_s2c2*_s1_2
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*sPHI*_c1_2*_s2c2*_phi_const
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_gss*sPHI*_s2*_c1*_phi_const;
  PP += 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_g1*sPHI*_c*_s1c1*_s2_2
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_g1*sPHI*_c*_s1c1*_c2_2
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_g1*cPHI*_s*_s1c1*_c2_2
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_gss*sPHI*_c*_s1*_c2
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_gss*cPHI*_s*_s1*_c2;
  PP += 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*_s1c1*_s2c2*_c
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_gss*_c*_s1*_s2
    + 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*cT*cT*_s1c1*_s2c2*_c
    - 2.0*_mH*_mH*M1*M2*_mZ*m*_gss*cT*cT*_s1*_s2*_c
    - 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_g1*c2PHI*_c*_s1c1*_s2c2
    + 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_g1*s2PHI*_s*_s1c1*_s2c2
    - 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_gss*c2PHI*_c*_s1*_s2
    + 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_gss*s2PHI*_s*_s1*_s2;

  PP *= _P*_P;

  //Now the XP cosdelta interference term
  double XPcos = _g1*_mH*_mH*sT*sT*M1*m*m*s2PHI*_s1_2*_s2_2*_phi_const
    - _g1*_mH*_mH*sT*sT*M2*_mZ*_mZ*s2PHI*_c*_s1_2*_s2_2
    - _g1*_mH*_mH*sT*sT*M2*_mZ*_mZ*c2PHI*_s*_s1_2*_s2_2;
  XPcos += 2.0*_g1*_mH*md*cT*sT*m*2.0*_mZ*_mZ*sPHI*_sc*_s1_2*_s2c2
    + 2.0*_g1*_mH*md*cT*sT*m*2.0*_mZ*_mZ*cPHI*_s_2*_s1_2*_s2c2
    - 2.0*_g1*_mH*md*cT*sT*m*M1*cPHI*_s1_2*_s2c2*_phi_const;
  XPcos += -2.0*_g1*_mH*md*cT*sT*_mZ*2.0*m*m*sPHI*_s*_s2_2*_s1c1
    - 2.0*_g1*_mH*md*cT*sT*_mZ*M2*cPHI*_c*_s2_2*_s1c1
    + 2.0*_g1*_mH*md*cT*sT*_mZ*M2*sPHI*_s*_s2_2*_s1c1;
  XPcos += -2.0*_mZ*m*_mH*_mH*M3*_g1*_s1c1*_s2c2*_s
    + 2.0*_mZ*m*_mH*_mH*M3*_gss*_s*_s1*_s2
    - 2.0*_mZ*m*_mH*_mH*M3*_g1*cT*cT*_s1c1*_s2c2*_s
    + 2.0*_mZ*m*_mH*_mH*M3*_gss*cT*cT*_s1*_s2*_s;
  XPcos += -2.0*_mZ*m*md*sT*sT*_g1*_mH*_mH*sPHI*_c*_s1c1*_s2c2
    - 2.0*_mZ*m*md*sT*sT*_g1*_mH*_mH*cPHI*_s*_s1c1*_s2c2
    - 2.0*_mZ*m*md*sT*sT*_g1*2.0*md*_s*_s1c1*_s2c2
    - 2.0*_mZ*m*md*sT*sT*_gss*_mH*_mH*sPHI*_c*_s1*_s2
    - 2.0*_mZ*m*md*sT*sT*_gss*_mH*_mH*cPHI*_s*_s1*_s2
    - 2.0*_mZ*m*md*sT*sT*_gss*2.0*md*_s*_s1*_s2;
  XPcos += -4.0*_mH*_mZ*m*md*cT*sT*m*_g1*cPHI*_c*_c2_const*_s1c1
    - 4.0*_mH*_mZ*m*md*cT*sT*m*_g1*sPHI*_s*_c2_const*_s1c1
    - 4.0*_mH*_mZ*m*md*cT*sT*m*_gss*cPHI*_c*_s1*_c2
    - 4.0*_mH*_mZ*m*md*cT*sT*m*_gss*sPHI*_s*_s1*_c2
    - 4.0*_mH*_mZ*m*md*cT*sT*_mZ*_g1*cPHI*_s2c2*_c1_const*_phi_const
    - 4.0*_mH*_mZ*m*md*cT*sT*_mZ*_gss*cPHI*_s2*_c1*_phi_const;

  XPcos *= 4.0*_mZ*m*_XP*cos(_delta)*g_b;

  //Now the XP sindelta interference term
  double XPsin = _gs*_mH*md*cT*sT*m*2.0*_mZ*_mZ*sPHI*_c_2*_s1_2*_s2
    + _gs*_mH*md*cT*sT*m*2.0*_mZ*_mZ*cPHI*_sc*_s1_2*_s2
    - _gs*_mH*md*cT*sT*m*M1*sPHI*_s1_2*_s2*_phi_const;
  XPsin += -1.0*_gs*_mH*md*cT*sT*_mZ*2.0*m*m*sPHI*_s2_2*_s1*_c
    + _gs*_mH*md*cT*sT*_mZ*M2*sPHI*_c*_s2_2*_s1
    + _gs*_mH*md*cT*sT*_mZ*M2*cPHI*_s*_s2_2*_s1;
  XPsin += _gs*_mH*_mH*M1*m*m*_s1_2*_c2*_phi_const
    + _gs*_mH*_mH*M2*_mZ*_mZ*_s2_2*_c1*_phi_const
    + _gs*_mH*_mH*M1*m*m*cT*cT*_s1_2*_c2*_phi_const
    + _gs*_mH*_mH*M2*_mZ*_mZ*cT*cT*_s2_2*_c1*_phi_const;
  XPsin += _mZ*m*_gs*_mH*_mH*md*_s1c1*_c*_s2
    - _mZ*m*_gs*_mH*_mH*md*_s2c2*_c*_s1
    + _mZ*m*_gs*_mH*_mH*md*cT*cT*_s2*_s1c1*_c
    - _mZ*m*_gs*_mH*_mH*md*cT*cT*_s1*_s2c2*_c;
  XPsin += -1.0*_mZ*m*_gs*sT*sT*_mH*_mH*M3*c2PHI*_c*_s2*_s1c1
    + _mZ*m*_gs*sT*sT*_mH*_mH*M3*s2PHI*_s*_s1c1*_s2
    - _mZ*m*_gs*sT*sT*2.0*md*md*_c*_s1c1*_s2
    - _mZ*m*_gs*sT*sT*_mH*_mH*M3*c2PHI*_c*_s2c2*_s1
    + _mZ*m*_gs*sT*sT*_mH*_mH*M3*s2PHI*_s*_s2c2*_s1
    - _mZ*m*_gs*sT*sT*2.0*md*md*_c*_s2c2*_s1;
  XPsin += 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*sPHI*_c*_s1*_c2_const
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*cPHI*_s*_s1*_c2_const
    - 2.0*_gs*_mH*md*_mZ*m*cT*sT*_mZ*sPHI*_s2*_c1_const*_phi_const
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*sPHI*_c*_s1c1*_c2
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*cPHI*_s*_s1c1*_c2
    - 2.0*_gs*_mH*md*_mZ*m*cT*sT*_mZ*sPHI*_c1*_s2c2*_phi_const;

  XPsin *= -1.0*_mZ*m*_XP*sin(_delta)*g_b;

  double ME = XX + PP + XPcos + XPsin;
  
  return ME;
}
  

double spin_one::Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi){
  double pcms = Pcms(_mH, m);
 
  if(pcms < 0.0) return 0.0;

   //Phase space part of PDF
  double PS = BreitWigner(m, _mZ, _wZ)*m*pcms;

  //Here, these are the mass variables _squared_ (without the square explicitly)
  double md = _mZ*_mZ-m*m;
  double M1 = _mH*_mH-3.0*_mZ*_mZ-m*m;
  double M2 = _mH*_mH-_mZ*_mZ-3.0*m*m;
  double M3 = _mH*_mH - 2.0*(_mZ*_mZ+m*m);
  //double M4 = _mH*_mH - (_mZ*_mZ+m*m);

 

  double g_b = Gamma_b(m);
  double cPHI = cos(PHI);
  double c2PHI = cos(2*PHI);
  double c = cos(phi);
  double c2phi = cos(2.0*phi);
  double sPHI = sin(PHI);
  double s2PHI = sin(2.0*PHI);
  double s = sin(phi);
  double s2phi = sin(2.0*phi);
  double cT = cosTHETA;
  
  double s1 = sqrt(1.0-c1*c1);
  double s2 = sqrt(1.0-c2*c2);
  double sT = sqrt(1.0-cT*cT);


  //First X^2 part
  double XX = _g1*sT*sT*s1*s1*s2*s2*2.0*md*md
    -_g1*sT*sT*s1*s1*s2*s2*_mH*_mH*_mZ*_mZ*c2PHI*c2phi
    +_g1*sT*sT*s1*s1*s2*s2*_mH*_mH*_mZ*_mZ*s2PHI*s2phi
    -_g1*sT*sT*s1*s1*s2*s2*_mH*_mH*m*m*c2PHI;
  XX += _g1*_mH*_mH*2.0*m*m*s1*s1
    + _g1*_mH*_mH*2.0*m*m*s1*s1*cT*cT
    + _g1*_mH*_mH*2.0*_mZ*_mZ*s2*s2
    + _g1*_mH*_mH*2.0*_mZ*_mZ*s2*s2*cT*cT
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*s1*s1*s2*s2
    - _g1*_mH*_mH*(_mZ*_mZ+m*m)*s1*s1*s2*s2*cT*cT;
  XX += 4.0*_g1*_mH*md*cT*sT*_mZ*c1*s1*s2*s2*sPHI*c
    + 4.0*_g1*_mH*md*cT*sT*_mZ*c1*s1*s2*s2*cPHI*s
    - 4.0*_g1*_mH*md*cT*sT*m*c2*s2*s1*s1*sPHI;
  XX += -2.0*_mH*_mH*_mZ*m*_g1*s1*c1*c2*s2*c
    + 2.0*_mH*_mH*_mZ*m*s1*s2*_gss*c
    - 2.0*_mH*_mH*_mZ*m*_g1*s1*c1*s2*c2*c*cT*cT
    + 2.0*_mH*_mH*_mZ*m*s1*s2*_gss*c*cT*cT
    - 2.0*_mH*_mH*_mZ*m*sT*sT*_g1*s1*c1*s2*c2*c2PHI*c
    + 2.0*_mH*_mH*_mZ*m*sT*sT*_g1*s1*c1*s2*c2*s2PHI*s
    - 2.0*_mH*_mH*_mZ*m*s1*s2*sT*sT*_gss*c2PHI*c
    + 2.0*_mH*_mH*_mZ*m*s1*s2*sT*sT*_gss*s2PHI*s;

  XX *= 4.0*_mZ*_mZ*m*m*g_b*g_b*_X*_X;

  //Now the P^2 part
  double PP = _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M2*M2*_mZ*_mZ*c2PHI*c2phi
    - _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M2*M2*_mZ*_mZ*s2PHI*s2phi
    + _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M1*M1*m*m*c2PHI;
  PP += 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*c1*c1
    + 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*c2*c2
    + 8.0*_mZ*_mZ*m*m*md*md*sT*sT*_g1*s1*s1*s2*s2*s*s
    + 16.0*_mZ*_mZ*m*m*md*md*sT*sT*_gss*c1*c2;
  PP += _g1*_mH*_mH*2.0*M1*M1*m*m*s1*s1
    + _g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*s2*s2
    - _g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*s1*s1*s2*s2
    + cT*cT*_g1*_mH*_mH*2.0*M1*M1*m*m*s1*s1
    + cT*cT*_g1*_mH*_mH*2.0*M2*M2*_mZ*_mZ*s2*s2
    - cT*cT*_g1*_mH*_mH*(M2*M2*_mZ*_mZ+M1*M1*m*m)*s1*s1*s2*s2;
  PP += -8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*s2*c2*s1*s1*sPHI*c*c
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*s2*c2*s1*s1*cPHI*s*c
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*_g1*c1*c1*s2*c2*sPHI
    - 8.0*_mH*md*_mZ*m*cT*sT*M2*_mZ*s2*_gss*c1*sPHI;
  PP += 8.0*_mH*md*_mZ*m*cT*sT*M1*m*_g1*s1*c1*s2*s2*sPHI*c
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*c2*_g1*s1*c1*c2*sPHI*c
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*c2*_g1*s1*c1*c2*cPHI*s
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*s1*c2*_gss*sPHI*c
    + 8.0*_mH*md*_mZ*m*cT*sT*M1*m*s1*c2*_gss*cPHI*s;
  PP += 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*s1*c1*s2*c2*c
    - 2.0*_mH*_mH*M1*M2*_mZ*m*s1*s2*_gss*c
    + 2.0*_mH*_mH*M1*M2*_mZ*m*_g1*s1*c1*s2*c2*c*cT*cT
    - 2.0*_mH*_mH*M1*M2*_mZ*m*s1*s2*_gss*c*cT*cT
    - 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_g1*s1*c1*s2*c2*c2PHI*c
    + 2.0*_mH*_mH*M1*M2*_mZ*m*sT*sT*_g1*s1*c1*s2*c2*s2PHI*s
    - 2.0*_mH*_mH*M1*M2*_mZ*m*s1*s2*sT*sT*_gss*c2PHI*c
    + 2.0*_mH*_mH*M1*M2*_mZ*m*s1*s2*sT*sT*_gss*s2PHI*s;

  PP *= _P*_P;

  //Now the XP cosdelta interference term
  double XPcos = _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M1*m*m*s2PHI
    - _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M2*_mZ*_mZ*s2PHI*c2phi
    - _g1*_mH*_mH*sT*sT*s1*s1*s2*s2*M2*_mZ*_mZ*c2PHI*s2phi;
  XPcos += 2.0*_g1*_mH*md*cT*sT*m*s1*s1*s2*c2*2.0*_mZ*_mZ*sPHI*c*s
    + 2.0*_g1*_mH*md*cT*sT*m*s1*s1*s2*c2*2.0*_mZ*_mZ*cPHI*s*s
    - 2.0*_g1*_mH*md*cT*sT*m*s1*s1*s2*c2*M1*cPHI;
  XPcos += -2.0*_g1*_mH*md*cT*sT*_mZ*s2*s2*s1*c1*2.0*m*m*sPHI*s
    - 2.0*_g1*_mH*md*cT*sT*_mZ*s2*s2*s1*c1*M2*cPHI*c
    + 2.0*_g1*_mH*md*cT*sT*_mZ*s2*s2*s1*c1*M2*sPHI*s;
  XPcos += -2.0*_mZ*m*_mH*_mH*M3*_g1*s1*c1*s2*c2*s
    + 2.0*_mZ*m*s1*s2*_mH*_mH*M3*_gss*s
    - 2.0*_mZ*m*_mH*_mH*M3*_g1*s1*c1*s2*c2*s*cT*cT
    + 2.0*_mZ*m*s1*s2*_mH*_mH*M3*_gss*s*cT*cT;
  XPcos += -2.0*_mZ*m*md*sT*sT*_g1*s1*c1*s2*c2*_mH*_mH*sPHI*c
    - 2.0*_mZ*m*md*sT*sT*_g1*s1*c1*s2*c2*_mH*_mH*cPHI*s
    - 2.0*_mZ*m*md*sT*sT*_g1*s1*c1*s2*c2*2.0*md*s
    - 2.0*_mZ*m*s1*s2*md*sT*sT*_gss*_mH*_mH*sPHI*c
    - 2.0*_mZ*m*s1*s2*md*sT*sT*_gss*_mH*_mH*cPHI*s
    - 2.0*_mZ*m*s1*s2*md*sT*sT*_gss*2.0*md*s;
  XPcos += -4.0*_mH*_mZ*m*md*cT*sT*m*_g1*s1*c1*cPHI*c
    - 4.0*_mH*_mZ*m*md*cT*sT*m*_g1*s1*c1*sPHI*s
    - 4.0*_mH*_mZ*m*md*cT*sT*m*s1*_gss*c2*cPHI*c
    - 4.0*_mH*_mZ*m*md*cT*sT*m*s1*_gss*c2*sPHI*s
    - 4.0*_mH*_mZ*m*md*cT*sT*_mZ*_g1*s2*c2*cPHI
    - 4.0*_mH*_mZ*m*md*cT*sT*_mZ*s2*_gss*c1*cPHI;

  XPcos *= 4.0*_mZ*m*_XP*cos(_delta)*g_b;

  //Now the XP sindelta interference term
  double XPsin = _gs*_mH*md*cT*sT*m*s1*s1*s2*2.0*_mZ*_mZ*c*sPHI*c
    + _gs*_mH*md*cT*sT*m*s1*s1*s2*2.0*_mZ*_mZ*c*cPHI*s
    - _gs*_mH*md*cT*sT*m*s1*s1*s2*M1*sPHI;
  XPsin += -1.0*_gs*_mH*md*cT*sT*_mZ*s2*s2*s1*2.0*m*m*c*sPHI
    + _gs*_mH*md*cT*sT*_mZ*s2*s2*s1*M2*sPHI*c
    + _gs*_mH*md*cT*sT*_mZ*s2*s2*s1*M2*cPHI*s;
  XPsin += _gs*_mH*_mH*M1*m*m*s1*s1*c2
    + _gs*_mH*_mH*M2*_mZ*_mZ*s2*s2*c1
    + _gs*_mH*_mH*M1*m*m*s1*s1*c2*cT*cT
    + _gs*_mH*_mH*M2*_mZ*_mZ*s2*s2*c1*cT*cT;
  XPsin += _mZ*m*s2*_gs*_mH*_mH*md*s1*c1*c
    - _mZ*m*s1*_gs*_mH*_mH*md*s2*c2*c
    + _mZ*m*s2*_gs*_mH*_mH*md*s1*c1*c*cT*cT
    - _mZ*m*s1*_gs*_mH*_mH*md*s2*c2*c*cT*cT;
  XPsin += -1.0*_mZ*m*s2*_gs*sT*sT*s1*c1*_mH*_mH*M3*c2PHI*c
    + _mZ*m*s2*_gs*sT*sT*s1*c1*_mH*_mH*M3*s2PHI*s
    - _mZ*m*s2*_gs*sT*sT*s1*c1*2.0*md*md*c
    - _mZ*m*s1*_gs*sT*sT*s2*c2*_mH*_mH*M3*c2PHI*c
    + _mZ*m*s1*_gs*sT*sT*s2*c2*_mH*_mH*M3*s2PHI*s
    - _mZ*m*s1*_gs*sT*sT*s2*c2*2.0*md*md*c;
  XPsin += 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*s1*sPHI*c
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*s1*cPHI*s
    - 2.0*_gs*_mH*md*_mZ*m*cT*sT*_mZ*s2*sPHI
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*sPHI*c*s1*c1*c2
    + 2.0*_gs*_mH*md*_mZ*m*cT*sT*m*cPHI*s*s1*c1*c2
    - 2.0*_gs*_mH*md*_mZ*m*cT*sT*_mZ*sPHI*c1*s2*c2;

  XPsin *= -1.0*_mZ*m*_XP*sin(_delta)*g_b;

  double ME = XX + PP + XPcos + XPsin;

  return (ME*PS);
}
