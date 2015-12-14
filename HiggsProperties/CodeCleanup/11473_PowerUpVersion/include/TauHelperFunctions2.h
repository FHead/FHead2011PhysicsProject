//----------------------------------------------------------------------------
#ifndef TauHelperFunctions_6624_AJSDKGIRIKANSVCGKISNCGIKNHKZSG
#define TauHelperFunctions_6624_AJSDKGIRIKANSVCGKISNCGIKNHKZSG
//----------------------------------------------------------------------------
// FourVector class - with a lot of extra setters and getter
// Author: Yi Chen (original version on 6624)
//----------------------------------------------------------------------------
#include <vector>
#include <cmath>
#include <ostream>
//----------------------------------------------------------------------------
#include "DrawRandom2.h"
// #include "GenparticleTree.h"
//----------------------------------------------------------------------------
// Categories:
//    -1. not final tau (goes into tau gamma)
//    1. mu nu nu
//    2. e nu nu
//    3. nu pi-
//    4. nu pi0 pi-
//    5. nu pi0 pi0 pi-
//    6. nu pi+ pi- pi-
//    7. nu pi+ pi- pi- pi0
//    8. Otherwise
//----------------------------------------------------------------------------
#define PI 3.14159265358979323846264338327950288479716939937510
//----------------------------------------------------------------------------
class FourVector;
std::ostream &operator <<(std::ostream &out, FourVector P);
FourVector operator *(double Scale, FourVector P);
double GetAngle(const FourVector P1, const FourVector P2);
double GetDR(const FourVector P1, const FourVector P2);
double GetDPhi(const FourVector P1, const FourVector P2);
double EPS(const FourVector A, const FourVector B, const FourVector C, const FourVector D);
double GetMT(const FourVector P1, const FourVector P2);
double GetMinRadius(const FourVector P1, const FourVector P2, const FourVector P3);   // in eta-phi space
double GetMinRadius(const double X1, const double Y1, const double X2, const double Y2, const double X3, const double Y3);
double GetMR(const FourVector P1, const FourVector P2);
double GetMRStar(const FourVector P1, const FourVector P2);
double Get2011MR(const FourVector P1, const FourVector P2);
double GetISRRemovedMR(const FourVector P1, const FourVector P2, const FourVector POther, double ME3Assumption = 0);
double GetISRRemoved2011MR(const FourVector P1, const FourVector P2, const FourVector POther, double ME3Assumption = 0);
double GetISR2011MR(const FourVector P1, const FourVector P2, const FourVector ME, int Assumption = 0);
double GetMRT(const FourVector P1, const FourVector P2, const FourVector ME);
double GetR(const FourVector P1, const FourVector P2, const FourVector ME);
double GetRStar(const FourVector P1, const FourVector P2, const FourVector ME);
double Get2011R(const FourVector P1, const FourVector P2, const FourVector ME);
double GetISRRemovedR(const FourVector P1, const FourVector P2, const FourVector POther, double ME3Assumption = 0);
double GetISRRemoved2011R(const FourVector P1, const FourVector P2, const FourVector POther, double ME3Assumption = 0);
double GetISR2011R(const FourVector P1, const FourVector P2, const FourVector ME, int Assumption = 0, char AdditionalVariant = 'g');
double GetGammaRStar(const FourVector P1, const FourVector P2);
double BetaToGamma(double Beta);
double GammaToBeta(double Gamma);
std::vector<FourVector> SplitIntoGroups(std::vector<FourVector> &Input, bool ZeroMass = true);
double GetDifference8(FourVector &P1, FourVector &P2, FourVector &ME, double BetaX);
double GetDifference9(FourVector &P1, FourVector &P2, FourVector &ME, double BetaZ);
double FindMR11MinimumPz(FourVector J1, FourVector J2, FourVector ME, FourVector ISR);
double EstimateMass11(FourVector J1, FourVector J2, FourVector ME, FourVector ISR, bool Reversal = false);
double EstimateTransverseMass11(FourVector J1, FourVector J2, FourVector ME, FourVector ISR, char Variant = 'g', bool Reversal = false);
// int FindCategory(GenParticleTree &Tree, int index);
//----------------------------------------------------------------------------
class FourVector
{
public:
   double P[4];
public:
   FourVector();
   FourVector(double p[4]);
   FourVector(double e, double px, double py, double pz);
   ~FourVector();
   void SetPtEtaPhi(double pt, double eta, double phi);   // massless
   void SetPtEtaPhiMass(double pt, double eta, double phi, double mass = 0);
   void SetPtYPhi(double pt, double y, double phi);   // massless
   void SetPtYPhiMass(double pt, double y, double phi, double mass = 0);
   void SetSizeEtaPhi(double size, double eta, double phi);
   void SetSizeEtaPhiMass(double size, double eta, double phi, double mass = 0);
   void SetSizeEtaPhiEnergy(double size, double eta, double phi, double energy);
   void SetSizeThetaPhi(double size, double theta, double phi);
   void SetSizeThetaPhiMass(double size, double theta, double phi, double mass = 0);
   double &operator [](int index);
   double operator [](int index) const;
   FourVector &operator =(const FourVector &Other);
   FourVector operator +(const FourVector &Other) const;
   FourVector operator -() const;
   FourVector operator -(const FourVector &Other) const;
   double operator *(const FourVector &other) const;
   FourVector operator *(double Scale) const;
   FourVector operator /(double Scale) const;
public:
   double GetMass() const;
   double GetMass2() const;
   double GetP() const;
   double GetP2() const;
   double GetPT() const;
   double GetPT2() const;
   double GetEta() const;
   double GetAbsEta() const;
   double GetRapidity() const;
   double GetY() const;
   double GetPhi() const;
   double GetTheta() const;
   double GetGamma() const;
   double GetBeta() const;
   FourVector RotateX(double Angle) const;
   FourVector RotateY(double Angle) const;
   FourVector RotateZ(double Angle) const;
   FourVector Rotate(const FourVector Axis, double Angle) const;
   FourVector BoostX(double Beta) const;
   FourVector BoostY(double Beta) const;
   FourVector BoostZ(double Beta) const;
   FourVector Boost(const FourVector Axis, double Beta) const;
   FourVector GammaBoostX(double Gamma) const;
   FourVector GammaBoostY(double Gamma) const;
   FourVector GammaBoostZ(double Gamma) const;
   FourVector GammaBoost(const FourVector Axis, double Gamma) const;
   FourVector SmearAngle(double Angle) const;
   FourVector SmearMomentum(double Scale) const;
   FourVector SpatialCross(const FourVector Other) const;
   FourVector SpatialNormalize() const;
   double SpatialDot(const FourVector &Other) const;
   double MetricDot(const FourVector &Other) const;
};
//----------------------------------------------------------------------------
#endif
