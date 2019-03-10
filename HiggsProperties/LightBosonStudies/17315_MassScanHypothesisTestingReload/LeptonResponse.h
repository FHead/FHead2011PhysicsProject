#include "Code/TauHelperFunctions3.h"

// #define EFFICIENCY_USE_SI_11174
// #define EFFICIENCY_USE_YONG_11672
#define EFFICIENCY_USE_LATEST
// #define EFFICIENCY_USE_TRIVIAL

inline unsigned int FindLeptonBinBinary(const double value, const double bins[], unsigned int nbins);
inline unsigned int FindLeptonBin(const double value, const double bins[], unsigned int nbins);

// Trivial smearing and efficiencies
double GetFlatEfficiency(double Pt, double PzP, double Phi);
double GetFlatEfficiencyWithCut(double Pt, double PzP, double Phi);
double GetGaussianSmear(FourVector &Vector, double Delta, double Mean = 0, double Sigma = 0.1);

// Maps from Si (1)1174
double GetMuonEfficiencyPtEtaPhi_Si11174(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta_Si11174(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Si11174(double Pt, double PzP, double Phi);
double SmearMuon_Si11174(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

// From Yong (1)1672
double GetElectronEfficiencyPtEtaPhi_Yong11672_HZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_HZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Yong11672_ZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_ZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Yong11672_Zll(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_Zll(double Pt, double PzP, double Phi);
double SmearMuon_Yong11672(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron_Yong11672(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

// Universal entrance function
double GetMuonEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta(double Pt, double PzP, double Phi);
double SmearMuon(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron(FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

double SmearMuonCentral(FourVector &Vector, double Delta);
double SmearMuonUp(FourVector &Vector, double Delta);
double SmearMuonDown(FourVector &Vector, double Delta);
double SmearMuonWide(FourVector &Vector, double Delta);
double SmearMuonNarrow(FourVector &Vector, double Delta);
double SmearElectronCentral(FourVector &Vector, double Delta);
double SmearElectronUp(FourVector &Vector, double Delta);
double SmearElectronDown(FourVector &Vector, double Delta);
double SmearElectronWide(FourVector &Vector, double Delta);
double SmearElectronNarrow(FourVector &Vector, double Delta);



