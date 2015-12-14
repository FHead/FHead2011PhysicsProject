#include "Code/TauHelperFunctions2.h"

inline unsigned int FindLeptonBin( const double value, const double bins[], unsigned int nbins);
double GetMuonEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double SmearMuon(FourVector &Vector, double Delta);



