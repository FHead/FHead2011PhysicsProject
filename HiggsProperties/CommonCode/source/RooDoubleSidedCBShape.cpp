#include "RooFit.h"

#include "Riostream.h"
#include <math.h>

#include "RooDoubleSidedCBShape.hh"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
#include "TMath.h"

// ClassImp(RooDoubleSidedCBShape);

 
//_____________________________________________________________________________
RooDoubleSidedCBShape::RooDoubleSidedCBShape(const char *name, const char *title,
                                                     RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _sigma,
                                                     RooAbsReal& _alphaL, RooAbsReal& _nL,
                                                     RooAbsReal& _alphaR, RooAbsReal& _nR) :
  RooAbsPdf(name, title),
  m("m", "Dependent", this, _m),
  m0("m0", "M0", this, _m0),
  sigma("sigma", "Sigma", this, _sigma),
  alphaL("alphaL", "AlphaL", this, _alphaL),
  nL("nL", "OrderL", this, _nL),
  alphaR("alphaR", "AlphaR", this, _alphaR),
  nR("nR", "OrderR", this, _nR)
{
}


//_____________________________________________________________________________
RooDoubleSidedCBShape::RooDoubleSidedCBShape(const RooDoubleSidedCBShape& other, const char* name) :
  RooAbsPdf(other, name), m("m", this, other.m), m0("m0", this, other.m0),
  sigma("sigma", this, other.sigma), alphaL("alphaL", this, other.alphaL),
  nL("nL", this, other.nL),alphaR("alphaR", this, other.alphaR),
  nR("nR", this, other.nR)
{
}

//_____________________________________________________________________________
Double_t RooDoubleSidedCBShape::evaluate() const {
  
  Double_t t = (m-m0)/sigma;

  if (t >= -alphaL && t < alphaR) {
    return exp(-0.5*t*t);
  } else if (t < -alphaL) {
    Double_t a =  TMath::Power(nL/fabs(alphaL),nL)*exp(-0.5*alphaL*alphaL);
    Double_t b= nL/fabs(alphaL) - fabs(alphaL); 

    return a/TMath::Power(b - t, nL);
  } else {
    Double_t a =  TMath::Power(nR/fabs(alphaR),nR)*exp(-0.5*alphaR*alphaR);
    Double_t b= nR/fabs(alphaR) - fabs(alphaR); 

    return a/TMath::Power(b + t, nR);
  }

}

