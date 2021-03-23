#ifndef JETPRODUCER_23125_ASJIFIJAS
#define JETPRODUCER_23125_ASJIFIJAS

#include <vector>

#include "Code/TauHelperFunctions3.h"

#include "include/RhoCalculator.h"

class JetProducer;

class JetProducer
{
private:
   bool PassThrough;
   double MinProbability;
   double MaxProbability;
   double MinJetPT;
   double CSR;
   double CSAlpha;
   double JetR;
   double MinPTDiff;
   RhoCalculator CRho;
   RhoModulationCalculator CPhi;
public:
   JetProducer();
   ~JetProducer();
   void SetCMSPreset();
   void SetPassThrough(bool Value)      { PassThrough = Value; }
   void SetMinProbability(double Value) { MinProbability = Value; }
   void SetMaxProbability(double Value) { MaxProbability = Value; }
   void SetMinJetPT(double Value)       { MinJetPT = Value; }
   void SetCSR(double Value)            { CSR = Value; }
   void SetCSAlpha(double Value)        { CSAlpha = Value; }
   void SetJetR(double Value)           { JetR = Value; }
   void SetMinPTDiff(double Value)      { MinPTDiff = Value; }
   std::vector<FourVector> ClusterJets(const std::vector<FourVector> &PF,
      const std::vector<FourVector> &PFID1);
   RhoCalculator &GetRhoCalculator()    { return CRho; }
   RhoModulationCalculator &GetRhoModulationCalculator() { return CPhi; }
};

#endif
