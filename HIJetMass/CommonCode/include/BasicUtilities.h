#include <vector>
#include <iostream>

#define PI 3.14159265358979323846264338327950288479716939937510

double GetRho(std::vector<double> *EtaMax, std::vector<double> *Rho, double Eta);
double GetCentrality(int Bin);
bool IsDataFromTag(std::string Tag);
bool IsPPFromTag(std::string Tag);
template<class T, class U>
   std::vector<int> DRMatching(int BaseN, T BaseEta, T BasePhi,
      int TargetN, U TargetEta, U TargetPhi);

