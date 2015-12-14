#ifndef Gen_HH
#define Gen_HH

class Gen {
public:
  Gen(double mass, double width);
  ~Gen();

  double Pcms(double mH, double mZstar);
  double BreitWigner(double mstar, double m, double w);
  double Gamma_a(double mstar);
  double Gamma_b(double mstar);
  void SetX(double val){ _X = val; }
  void SetP(double val){ _P = val; }
  void SetQ(double val){ _Q = val; }
  void SetY(double val){ _Y = val; }
  void SetXY(double val){ _XY = val; }
  void SetXQ(double val){ _XQ = val; }
  void SetXP(double val){ _XP = val; }
  void SetDelta(double val){ _delta = val; }
 

protected:
  void Init(double mass, double width);
  double _mH; //Higgs mass
  double _wH; //Higgs width
  double _mZ; //nominal PDG Z mass
  double _wZ; //nominal PDG Z width
  double _mMu; //nominal PDG mu mass
  double _eta_bar;
  double _pi;
  double _ca;
  double _cv;
  double _g1;
  double _gs;
  double _gt;
  double _gss;
  double _gst;
  double _gsst;

  //For the spin 1 case
  double _X;
  double _P;
  double _XP;
  double _delta;

  //For the spin 0 case
  double _Y;
  double _Q;
  double _XY;
  double _XQ;

  //Here we put in coefficients from integrating over different angles
  double _c1;
  double _c2;
  double _cT;
  double _s1;
  double _s2; 
  double _s1c1;
  double _s2c2;
  double _sT;
  double _sTcT;
  double _c;
  double _cPHI;
  double _c2PHI;
  double _s;
  double _sc;
  double _sPHI;
  double _s2PHI;
  double _c1_2;
  double _c2_2;
  double _s1_2;
  double _s2_2;
  double _sT_2;
  double _cT_2;
  double _c_2;
  double _s_2;
  double _cPHI_2;
  double _c1_const;
  double _c2_const;
  double _phi_const;
  double _PHI_const;
  double _cosTHETA_const;

};
#endif
