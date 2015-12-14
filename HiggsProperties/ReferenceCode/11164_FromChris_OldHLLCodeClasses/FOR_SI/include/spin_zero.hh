#ifndef spin_zero_HH
#define spin_zero_HH

class spin_zero : public Gen{
public:
  spin_zero(double mass, double width);
  ~spin_zero();

  double Prob_M(double m);

  double Prob_ANGLES(double m, double cosTHETA, double PHI);

  double Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi);

private:
  
};
#endif
