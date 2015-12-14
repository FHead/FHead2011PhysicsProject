#include <iostream>

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "AngleConversion.h"
#include "CalculateME.h"

class ProjectionHelper
{
private:
   TTree *SignalTree;
   TTree *BackgroundTree;
   EventParameters Angles;
   EventParameters ReshuffledAngles;
   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, L3PT, L3Eta, L3Phi, L4PT, L4Eta, L4Phi;
   double Weight[16][4];
   bool PassBaseline2e2mu, PassBaseline4e;

public:
   enum Dimension {DimensionMH, DimensionM1, DimensionM2,
      DimensionPhi0, DimensionTheta0, DimensionPhi, DimensionTheta1, DimensionTheta2,
      DimensionCosTheta0, DimensionCosTheta1, DimensionCosTheta2,
      DimensionL1PT, DimensionL1Eta, DimensionL1Phi,
      DimensionL2PT, DimensionL2Eta, DimensionL2Phi,
      DimensionL3PT, DimensionL3Eta, DimensionL3Phi,
      DimensionL4PT, DimensionL4Eta, DimensionL4Phi};

private:
   void SetBranchAddress(TTree *Tree);
   double GetDimensionValue(Dimension dimension, EventParameters Event);
   vector<double> GetTotalWeight(const GeneralScalarParameters &P);
   bool PassBaselineCut(EventParameters Event);

public:
   ProjectionHelper(TTree *signaltree = NULL, TTree *backgroundtree = NULL);
   ~ProjectionHelper();
   void SetTree(bool IsSignal, TTree *tree);
   void FillProjection(TH1D *H, Dimension dimension, double Normalization,
      const GeneralScalarParameters &Parameters,
      double EEWeight, double MMWeight, double EMWeight, double MEWeight,
      double EEFraction, double MMFraction, double EMFraction, double MEFraction);
   void FillProjection(TH1D &H, Dimension dimension, double Normalization,
      const GeneralScalarParameters &Parameters,
      double EEWeight, double MMWeight, double EMWeight, double MEWeight,
      double EEFraction, double MMFraction, double EMFraction, double MEFraction);
   void FillProjection(TH2D *H, Dimension dimension1, Dimension dimension2,
      double Normalization, const GeneralScalarParameters &Parameters,
      double EEWeight, double MMWeight, double EMWeight, double MEWeight);
   void FillProjection(TH2D &H, Dimension dimension1, Dimension dimension2,
      double Normalization, const GeneralScalarParameters &Parameters,
      double EEWeight, double MMWeight, double EMWeight, double MEWeight);
};





