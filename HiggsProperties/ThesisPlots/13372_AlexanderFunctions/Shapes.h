#include <algorithm>
#include <cmath>

// ------ PU correction functions ------ PU correction functions ------ 
// ------------------------ HB ----------------------------------------
double a1_HB(double x) { // version 23.02.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.7261, -0.03124, 0.001177, -1.349e-05, -5.512e-08};
  static const double pol42[5] = {0.4151, 0.006921, -0.0003291, 4.897e-06, -2.42e-08};
  static const double pol31[4] = {0.469, -0.00151, 4.307e-06, -4.697e-09};
  static const double pol32[4] = {0.5264, -0.001902, 4.613e-06, -3.808e-09};
  static const double pol11[2] = {0.2648, -1.942e-05};
  static const double pol12[2] = {0.2413, -3.638e-07};
  double out(0);
  if (x > 0 && x < 28) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=28 && x < 60) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=60 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 435) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 435 && x < 1330) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1330) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a2_HB(double x) { // version 23.02.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.3148, -0.03012, 0.001738, -4.53e-05, 4.414e-07};
  static const double pol42[5] = {0.1315, -0.00103, 1.192e-05, -6.723e-08, 3.843e-10};
  static const double pol31[4] = {0.1108, -5.343e-05, -1.06e-06, 3.75e-09};
  static const double pol32[4] = {0.1045, -0.0001121, 1.443e-07, -7.224e-11};
  static const double pol11[2] = {0.07919, -1.252e-05};
  static const double pol12[2] = {0.06529, -3.825e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 65) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=65 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 850) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 850 && x < 1640) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1640) {
    out = pol12[0] + pol12[1]*x;
    //out = pol0[0];
  }
  return out*x;
}

double a3_HB(double x) { // version 23.02.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.158, -0.01651, 0.0009571, -2.583e-05, 2.629e-07};
  static const double pol42[5] = {0.0664, -0.001408, 2.026e-05, -9.511e-08, -1.235e-11};
  static const double pol31[4] = {0.03989, -8.034e-05, -1.448e-07, 1.205e-09};
  static const double pol21[3] = {0.03055, -1.585e-05, 7.227e-09};
  static const double pol11[2] = {0.02444, -2.433e-06};
  static const double pol12[2] = {0.0243, -2.282e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 880) {
    out = pol21[0] + pol21[1]*x + pol21[2]*x*x;
  } else if (x >= 880 && x < 1500) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1500) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

// ------------------------ 17-20 ----------------------------------------
double a1_1720(double x) { // version 28.03.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.6129, -0.00765, -0.0008141, 5.724e-05, -9.377e-07};
  static const double pol42[5] = {0.4033, 0.00678, -0.000312, 4.534e-06, -2.197e-08};
  static const double pol31[4] = {0.4603, -0.001526, 4.85e-06, -6.446e-09};
  static const double pol32[4] = {0.4849, -0.001505, 3.307e-06, -2.461e-09};
  static const double pol1[2] = {0.261, -2.086e-05};
  static const double pol0[1] = {0.2354};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 410) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 410 && x < 1320) {
    out = pol1[0] + pol1[1]*x;
  } else if (x >= 1320) {
    out = pol0[0];
  }
  return out*x;
}

double a2_1720(double x) { // version 28.03.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.313, -0.02747, 0.001404, -3.232e-05, 2.748e-07};
  static const double pol42[5] = {0.1519,-0.003287, 7.798e-05, -9.27e-07, 4.455e-09};
  static const double pol31[4] = {0.1079, -0.0002475, 2.859e-07, 7.703e-10};
  static const double pol32[4] = {0.09147, -0.0001035, 1.268e-07, -5.747e-11};
  static const double pol1[2] = {0.06536, -8.462e-06};
  static const double pol0[1] = {0.05337};
  double out(0);
  if (x > 0 && x < 27) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=27 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 1050) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 1050 && x < 1550) {
    out = pol1[0] + pol1[1]*x;
  } else if (x >= 1550) {
    out = pol0[0];
  }
  return out*x;
}

double a3_1720(double x) { // version 28.03.2014
  // this function is made from profile TS7/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.1654, -0.01691, 0.0009276,-2.403e-05, 2.368e-07};
  static const double pol42[5] = {0.07517, -0.002402, 5.164e-05, -5.637e-07, 2.601e-09};
  static const double pol31[4] = {0.03484, -0.0001004, -1.08e-07, 1.339e-09};
  static const double pol32[4] = {0.02256, -7.084e-06, 8.055e-10, 1.608e-12};
  static const double pol1[2] = {0.01989, -1.917e-06};
  static const double pol0[1] = {0.01804};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 60) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=60 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 850) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 850 && x < 970) {
    out = pol1[0] + pol1[1]*x;
  } else if (x >= 970) {
    out = pol0[0];
  }
  return out*x;
}

// ------------------------ 21-23 ----------------------------------------
double a1_2123(double x) { // version 28.03.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.4908, 0.01378, -0.002152, 9.244e-05, -1.27e-06};
  static const double pol42[5] = {0.3983, 0.00721, -0.000334, 4.999e-06, -2.52e-08};
  static const double pol31[4] = {0.4746, -0.001923, 8.029e-06, -1.411e-08};
  static const double pol32[4] = {0.4848, -0.001503, 3.339e-06, -2.518e-09};
  static const double pol11[2] = {0.264, -2.491e-05};
  static const double pol12[2] = {0.2545, -1.539e-05};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 515) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 515 && x < 1240) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1240) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a2_2123(double x) { // version 28.03.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.2886, -0.01573, 0.0003735, 3.986e-06, -1.723e-07};
  static const double pol42[5] = {0.1724, -0.003205, 6.239e-05, -5.989e-07, 2.346e-09};
  static const double pol31[4] = {0.1302, -0.0004984, 2.021e-06, -3.34e-09};
  static const double pol32[4] = {0.104, -0.0001241, 1.579e-07, -7.438e-11};
  static const double pol1[2] = {0.07527, -1.186e-05};
  static const double pol0[1] = {0.05917};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 1000) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 1000 && x < 1380) {
    out = pol1[0] + pol1[1]*x;
  } else if (x >= 1380) {
    out = pol0[0];
  }
  return out*x;
}

double a3_2123(double x) { // version 28.03.2014
  // this function is made from profile TS7/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.1692, -0.01211, 0.0004151,-4.673e-06, -9.917e-09};
  static const double pol42[5] = {0.09808, -0.00334, 7.183e-05, -7.694e-07, 3.359e-09};
  static const double pol31[4] = {0.04349, -0.0001779, 3.677e-07, 2.398e-10};
  static const double pol21[3] = {0.0271, -1.299e-05, 5.891e-09};
  static const double pol11[2] = {0.02095, -9.13e-07};
  static const double pol12[2] = {0.0234, -2.563e-06};
  double out(0);
  if (x > 0 && x < 22) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=22 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 955) {
    out = pol21[0] + pol21[1]*x + pol21[2]*x*x;
  } else if (x >= 955 && x < 1550) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1550) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

// ------------------------ 24-25 ----------------------------------------
double a1_2425(double x) { // version 28.03.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.4595, 0.01439, -0.001756, 6.716e-05, -8.552e-07};
  static const double pol42[5] = {0.3636, 0.01037, -0.0004347, 6.349e-06, -3.167e-08};
  static const double pol31[4] = {0.4698, -0.001775, 6.638e-06, -1.061e-08};
  static const double pol32[4] = {0.4854, -0.001519, 3.321e-06, -2.483e-09};
  static const double pol11[2] = {0.2568, -2.584e-05};
  static const double pol12[2] = {0.2282, -2.334e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 425) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 425 && x < 1250) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1250) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a2_2425(double x) { // version 28.03.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.2922, -0.009065,-0.0002295, 2.453e-05,-4.171e-07};
  static const double pol42[5] = {0.2008,-0.003443, 5.083e-05, -3.064e-07, 4.728e-10};
  static const double pol31[4] = {0.1533, -0.0007735, 3.571e-06, -6.432e-09};
  static const double pol32[4] = {0.1028, -8.7e-05, 8.209e-08, -3.136e-11};
  static const double pol11[2] = {0.07719, -1.123e-05};
  static const double pol12[2] = {0.0637, -1.798e-06};
  double out(0);
  if (x > 0 && x < 24) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >= 24 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >= 68 && x < 220) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >= 220 && x < 975) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 975 && x < 1450) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1450) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a3_2425(double x) { // version 28.03.2014
  // this function is made from profile TS7/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.189, -0.008964, -1.31e-06, 1.147e-05, -2.162e-07};
  static const double pol42[5] = {0.1229, -0.004001, 7.607e-05, -6.99e-07, 2.603e-09};
  static const double pol31[4] = {0.05612, -0.0003412, 1.296e-06, -1.627e-09};
  static const double pol21[3] = {0.0305, -2.055e-05, 1.099e-08};
  static const double pol11[2] = {0.02398, -3.276e-06};
  static const double pol12[2] = {0.02178, -1.19e-06};
  double out(0);
  if (x > 0 && x < 30) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=30 && x < 70) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=70 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 975) {
    out = pol21[0] + pol21[1]*x + pol21[2]*x*x;
  } else if (x >= 975 && x < 1300) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1300) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

// ------------------------ 26-27 ----------------------------------------
double a1_2627(double x) { // version 28.03.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.4404, 0.01173, -0.001344, 4.862e-05, -5.896e-07};
  static const double pol42[5] = {0.3483, 0.01019, -0.000416, 5.989e-06, -2.946e-08};
  static const double pol31[4] = {0.4545, -0.0016, 5.716e-06, -8.879e-09};
  static const double pol32[4] = {0.4794, -0.001485, 3.206e-06, -2.369e-09};
  static const double pol11[2] = {0.2531, -2.403e-05};
  static const double pol12[2] = {0.2376, -9.953e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 515) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 515 && x < 1200) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1200) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a2_2627(double x) { // version 28.03.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.3104, -0.01182, 0.0001538, 4.599e-06, -9.634e-08};
  static const double pol42[5] = {0.2105, -0.003244, 2.824e-05, 1.422e-07, -2.243e-09};
  static const double pol31[4] = {0.1587, -0.0008399, 3.787e-06, -6.468e-09};
  static const double pol32[4] = {0.1078, -0.000115, 1.33e-07, -5.914e-11};
  static const double pol11[2] = {0.07933, -1.265e-05};
  static const double pol12[2] = {0.06511, -2.133e-06};
  double out(0);
  if (x > 0 && x < 20) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=20 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 215) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=215 && x < 1000) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 1000 && x < 1350) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1350) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a3_2627(double x) { // version 28.03.2014
  // this function is made from profile TS7/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.2115, -0.01203, 0.0003039, -1.979e-06, -1.554e-08};
  static const double pol42[5] = {0.1352, -0.004278, 7.07e-05, -4.804e-07, 9.36e-10};
  static const double pol31[4] = {0.06245, -0.0004413, 1.873e-06, -2.76e-09};
  static const double pol32[4] = {0.03237, -3.191e-05, 3.321e-08, -1.301e-11};
  static const double pol11[2] = {0.02353, -2.846e-06};
  static const double pol12[2] = {0.02226, -1.488e-06};
  double out(0);
  if (x > 0 && x < 33) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=33 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 1025) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 1025 && x < 1450) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1450) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

// ------------------------ 28 ----------------------------------------
double a1_28(double x) { // version 28.03.2014
  // this function is made from profile TS5/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.4552, 0.00774, -0.0007652, 2.166e-05, -2.04e-07};
  static const double pol42[5] = {0.4447, 0.001959, -0.0001573, 2.587e-06, -1.341e-08};
  static const double pol31[4] = {0.4364, -0.0009454, 9.873e-07, 1.515e-09};
  static const double pol32[4] = {0.4726, -0.00135, 2.811e-06, -2.047e-09};
  static const double pol11[2] = {0.2569, -2.931e-05};
  static const double pol12[2] = {0.2345, -8.457e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 515) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 515 && x < 1150) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1150) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a2_28(double x) { // version 28.03.2014
  // this function is made from profile TS6/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.3477, -0.002766, -0.0003802, 1.631e-05, -1.871e-07};
  static const double pol42[5] = {0.3404, -0.006505, 8.54e-05, -4.002e-07, -4.685e-11};
  static const double pol31[4] = {0.2295, -0.001221, 4.778e-06, -7.352e-09};
  static const double pol32[4] = {0.1589, -0.0002629, 3.0e-07, -1.249e-10};
  static const double pol11[2] = {0.08305, -1.098e-05};
  static const double pol12[2] = {0.07318, -3.478e-06};
  double out(0);
  if (x > 0 && x < 23) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=23 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 970) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 970 && x < 1300) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1300) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

double a3_28(double x) { // version 28.03.2014
  // this function is made from profile TS7/TS4 vs TS4, MultiJet
  static const double pol41[5] = {0.2486, -0.006409, -0.0001518, 1.08e-05, -1.383e-07};
  static const double pol42[5] = {0.2269, -0.007492, 0.0001426, -1.283e-06, 4.437e-09};
  static const double pol31[4] = {0.09919, -0.0005777, 2.013e-06, -2.61e-09};
  static const double pol32[4] = {0.06175, -0.0001129, 1.167e-07, -4.246e-11};
  static const double pol11[2] = {0.02788, -4.659e-06};
  static const double pol12[2] = {0.02325, -1.051e-06};
  double out(0);
  if (x > 0 && x < 19) {
    out = pol41[0] + pol41[1]*x + pol41[2]*x*x + pol41[3]*x*x*x + pol41[4]*x*x*x*x;
  } else if (x >=19 && x < 68) {
    out = pol42[0] + pol42[1]*x + pol42[2]*x*x + pol42[3]*x*x*x + pol42[4]*x*x*x*x;
  } else if (x >=68 && x < 190) {
    out = pol31[0] + pol31[1]*x + pol31[2]*x*x + pol31[3]*x*x*x;
  } else if (x >=190 && x < 905) {
    out = pol32[0] + pol32[1]*x + pol32[2]*x*x + pol32[3]*x*x*x;
  } else if (x >= 905 && x < 1450) {
    out = pol11[0] + pol11[1]*x;
  } else if (x >= 1450) {
    out = pol12[0] + pol12[1]*x;
  }
  return out*x;
}

// -------------- functions a_1(TS4) = TS3/TS4 ov TS4 ----------------
double a_1_HB(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet, HB
  static const double par[2] = { 1.46711e-01, 1.46676e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

double a_1_1720(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet
  static const double par[2] = { 1.411431e-01, 1.58035e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

double a_1_2123(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet
  static const double par[2] = { 1.63057e-01, 2.45809e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

double a_1_2425(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet
  static const double par[2] = { 2.03391e-01, 3.75696e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

double a_1_2627(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet
  static const double par[2] = { 2.70479e-01, 6.80057e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

double a_1_28(double x) { // version 09.04.2014
  // this function is made from profile TS3/TS4 vs TS4, MultiJet
  static const double par[2] = { 5.83711e-02, 1.05714e+03}; 
  double out = par[0]*(1.0 - exp(-x/par[1]));
  return out*x;
}

// ------ PU correction functions ------ PU correction functions ------ 

//----------------------------------------------------------------------------------------------
void pucorrection(double *ts, double (*a1)(double), double (*a2)(double), double (*a3)(double), 
		  double (*a_1)(double)) 
{  
  // TS4 correction with functions a1(x) and a2(x)
  double ts20 = ts[2];
  double ts30 = ts[3] - a_1(ts[4]); // time slew correction with a_1(x)
  double ts21 = ts20 >= 0 ? a2(ts20) : 0; 
  double ts22 = ts20 >= 0 ? a1(ts20) : 0;
  double ts321 = ts30 - ts22 >= 0 ? a1(ts30 - ts22) : 0; 
  ts[4] -= (ts321 + ts21); // ts4corr => ts4 after pu correction
  
  // ts5 correction with functions a2(x) and a3(x)
  double ts52 = ts20 >= 0 ? a3(ts20) : 0;
  double ts51 = ts30 - ts22 >= 0 ? a2(ts30 - ts22) : 0; 
  ts[5] -= (ts51 + ts52); // ts5corr => ts5 after pu correction  
}

void PUcorr(double *ts, double IEta) 
{ 
// TS4 & TS5 corrections with functions a1(x), a2(x), a3(x) and a_1(x)
// for different IEta regions: HB and HE rings 17-20, 21-23, 24-25, 26-27, 28 
  if (std::fabs(IEta) < 17) {
    pucorrection(ts, a1_HB, a2_HB, a3_HB, a_1_HB);
  } else if (std::fabs(IEta) >= 17 && std::fabs(IEta) <= 20) {
    pucorrection(ts, a1_1720, a2_1720, a3_1720, a_1_1720);
  } else if (std::fabs(IEta) >= 21 && std::fabs(IEta) <= 23) {
    pucorrection(ts, a1_2123, a2_2123, a3_2123, a_1_2123);
  } else if (std::fabs(IEta) >= 24 && std::fabs(IEta) <= 25) {
    pucorrection(ts, a1_2425, a2_2425, a3_2425, a_1_2425);
  } else if (std::fabs(IEta) >= 26 && std::fabs(IEta) <= 27) {
    pucorrection(ts, a1_2627, a2_2627, a3_2627, a_1_2627);
  } else if (std::fabs(IEta) >= 28) {
    pucorrection(ts, a1_28, a2_28, a3_28, a_1_28);
  }
}


