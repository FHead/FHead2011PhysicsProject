#include "Code/TauHelperFunctions2.h"

inline unsigned int FindLeptonBin( const double value, const double bins[], unsigned int nbins);
double GetMuonEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double SmearMuon(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearMuonCentral(FourVector &Vector, double Delta);
double SmearMuonUp(FourVector &Vector, double Delta);
double SmearMuonDown(FourVector &Vector, double Delta);
double SmearMuonWide(FourVector &Vector, double Delta);
double SmearMuonNarrow(FourVector &Vector, double Delta);



