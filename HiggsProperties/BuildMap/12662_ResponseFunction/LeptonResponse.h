#include "Code/TauHelperFunctions2.h"

// #define EFFICIENCY_USE_SI_11174
// #define EFFICIENCY_USE_YONG_11672
// #define EFFICIENCY_USE_SI_12575
#define EFFICIENCY_USE_SI_WIDE_12575
// #define EFFICIENCY_USE_LATEST
// #define EFFICIENCY_USE_TRIVIAL

inline unsigned int FindLeptonBinBinary(const double value, const double bins[], unsigned int nbins);
inline unsigned int FindLeptonBin(const double value, const double bins[], unsigned int nbins);

// Trivial smearing and efficiencies
double GetFlatEfficiency(double Pt, double PzP, double Phi);
double GetFlatEfficiencyWithCut(double Pt, double PzP, double Phi);
double GetGaussianSmear(const FourVector &Vector, double Delta, double Mean = 0, double Sigma = 0.1);

// Maps from Si (1)1174
double GetMuonEfficiencyPtEtaPhi_Si11174(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta_Si11174(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Si11174(double Pt, double PzP, double Phi);
double SmearMuon_Si11174(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

// From Yong (1)1672
double GetElectronEfficiencyPtEtaPhi_Yong11672_HZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_HZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Yong11672_ZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_ZZ4l(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi_Yong11672_Zll(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta_Yong11672_Zll(double Pt, double PzP, double Phi);
double SmearMuon_Yong11672(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron_Yong11672(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

// From Si (1)2575
double GetMuonEfficiencyPtEta7TeV_Si12575(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta8TeV_Si12575(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta7TeV_Si12575(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta8TeV_Si12575(double Pt, double PzP, double Phi);
double SmearMuon7TeV_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearMuon8TeV_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron7TeV_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron8TeV_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearMuon7TeVWide_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearMuon8TeVWide_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron7TeVWide_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron8TeVWide_Si12575(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

// Universal entrance function
double GetMuonEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta(double Pt, double PzP, double Phi);
double SmearMuon(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

double GetMuonEfficiencyPtEtaPhi7TeV(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta7TeV(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi7TeV(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta7TeV(double Pt, double PzP, double Phi);
double SmearMuon7TeV(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron7TeV(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

double GetMuonEfficiencyPtEtaPhi8TeV(double Pt, double PzP, double Phi);
double GetMuonEfficiencyPtEta8TeV(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEtaPhi8TeV(double Pt, double PzP, double Phi);
double GetElectronEfficiencyPtEta8TeV(double Pt, double PzP, double Phi);
double SmearMuon8TeV(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);
double SmearElectron8TeV(const FourVector &Vector, double Delta, double ExtraSmear = 0, double ExtraScale = 1);

double SmearMuonCentral(const FourVector &Vector, double Delta);
double SmearMuonUp(const FourVector &Vector, double Delta);
double SmearMuonDown(const FourVector &Vector, double Delta);
double SmearMuonWide(const FourVector &Vector, double Delta);
double SmearMuonNarrow(const FourVector &Vector, double Delta);
double SmearElectronCentral(const FourVector &Vector, double Delta);
double SmearElectronUp(const FourVector &Vector, double Delta);
double SmearElectronDown(const FourVector &Vector, double Delta);
double SmearElectronWide(const FourVector &Vector, double Delta);
double SmearElectronNarrow(const FourVector &Vector, double Delta);

double SmearMuonCentral7TeV(const FourVector &Vector, double Delta);
double SmearMuonUp7TeV(const FourVector &Vector, double Delta);
double SmearMuonDown7TeV(const FourVector &Vector, double Delta);
double SmearMuonWide7TeV(const FourVector &Vector, double Delta);
double SmearMuonNarrow7TeV(const FourVector &Vector, double Delta);
double SmearElectronCentral7TeV(const FourVector &Vector, double Delta);
double SmearElectronUp7TeV(const FourVector &Vector, double Delta);
double SmearElectronDown7TeV(const FourVector &Vector, double Delta);
double SmearElectronWide7TeV(const FourVector &Vector, double Delta);
double SmearElectronNarrow7TeV(const FourVector &Vector, double Delta);

double SmearMuonCentral8TeV(const FourVector &Vector, double Delta);
double SmearMuonUp8TeV(const FourVector &Vector, double Delta);
double SmearMuonDown8TeV(const FourVector &Vector, double Delta);
double SmearMuonWide8TeV(const FourVector &Vector, double Delta);
double SmearMuonNarrow8TeV(const FourVector &Vector, double Delta);
double SmearElectronCentral8TeV(const FourVector &Vector, double Delta);
double SmearElectronUp8TeV(const FourVector &Vector, double Delta);
double SmearElectronDown8TeV(const FourVector &Vector, double Delta);
double SmearElectronWide8TeV(const FourVector &Vector, double Delta);
double SmearElectronNarrow8TeV(const FourVector &Vector, double Delta);



