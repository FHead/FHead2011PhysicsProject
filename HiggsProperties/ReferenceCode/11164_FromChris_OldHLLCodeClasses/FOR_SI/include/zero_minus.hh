#ifndef zero_minus_HH
#define zero_minus_HH

class zero_minus : public Gen{
public:
  zero_minus(double mass, double width);
  ~zero_minus();

  double Prob_M(double m);

  double Prob_ANGLES(double m, double cosTHETA, double PHI);

  double Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi);

private:
  
};
#endif
