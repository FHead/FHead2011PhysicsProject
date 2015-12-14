#ifndef zero_plus_HH
#define zero_plus_HH

class zero_plus : public Gen{
public:
  zero_plus(double mass, double width);
  ~zero_plus();

  double Prob_M(double m);

  double Prob_ANGLES(double m, double cosTHETA, double PHI);

  double Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi);

private:
  
};
#endif
