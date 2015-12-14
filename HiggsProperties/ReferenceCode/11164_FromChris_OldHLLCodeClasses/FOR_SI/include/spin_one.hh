#ifndef spin_one_HH
#define spin_one_HH

class spin_one : public Gen{
public:
  spin_one(double mass, double width);
  ~spin_one();

  double Prob_M(double m);

  double Prob_ANGLES(double m, double cosTHETA, double PHI);

  double Prob_angles(double m, double cosTHETA, double PHI, double c1, double c2, double phi);

private:
  
};
#endif
