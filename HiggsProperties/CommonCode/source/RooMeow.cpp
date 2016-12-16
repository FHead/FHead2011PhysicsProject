//----------------------------------------------------------------------------
#include "RooFit.h"

#include "Riostream.h"
#include <math.h>

#include "RooMeow.hh"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
#include "TMath.h"

// ClassImp(RooMeow);
//----------------------------------------------------------------------------
RooMeow::RooMeow(const char *name, const char *title, RooAbsReal &a1, RooAbsReal &a3, RooAbsReal &a3phase,
      RooAbsReal &v11, RooAbsReal &v33, RooAbsReal &v44, RooAbsReal &v13, RooAbsReal &v14/*, RooAbsReal &v34*/,
      RooAbsReal &i11, RooAbsReal &i33, RooAbsReal &i44, RooAbsReal &i13, RooAbsReal &i14/*, RooAbsReal &i34*/) :
   RooAbsPdf(name, title),
   A1("A1", "Dependent", this, a1), A3("A3", "Dependent", this, a3), A3Phase("A3Phase", "Dependent", this, a3phase),
   V11("V11", "V11", this, v11), V33("V33", "V33", this, v33), V44("V44", "V44", this, v44),
   V13("V13", "V13", this, v13), V14("V14", "V14", this, v14)/*, V34("V34", "V34", this, v34)*/,
   I11("I11", "I11", this, i11), I33("I33", "I33", this, i33), I44("I44", "I44", this, i44),
   I13("I13", "I13", this, i13), I14("I14", "I14", this, i14)/*, I34("I34", "I34", this, i34)*/
{
}
//----------------------------------------------------------------------------
RooMeow::RooMeow(const RooMeow &other, const char *name) :
   RooAbsPdf(other, name),
   A1("A1", this, other.A1), A3("A3", this, other.A3), A3Phase("A3Phase", this, other.A3Phase),
   V11("V11", this, other.V11), V33("V33", this, other.V33), V44("V44", this, other.V44),
   V13("V13", this, other.V13), V14("V14", this, other.V14)/*, V34("V34", this, other.V34)*/,
   I11("I11", this, other.I11), I33("I33", this, other.I33), I44("I44", this, other.I44),
   I13("I13", this, other.I13), I14("I14", this, other.I14)/*, I34("I34", this, other.I34)*/
{
}
//----------------------------------------------------------------------------
Double_t RooMeow::evaluate() const
{
   double A3R = A3 * cos(A3Phase);
   double A3I = A3 * sin(A3Phase);

   double Top = A1 * A1 * V11 + A3R * A3R * V33 + A3I * A3I * V44
      + A1 * A3 * V13 + A1 * A3I * V14/* + A3R * A3I * V34*/;
   double Bottom = A1 * A1 * I11 + A3R * A3R * I33 + A3I * A3I * I44
      + A1 * A3 * I13 + A1 * A3I * I14/* + A3R * A3I * I34*/;

   if(Top < 1e-6 || Bottom < 1e-6)
      return 1e-6;

   std::cout << "Evaluate: " << Top << " " << Bottom << std::endl;

   return Top / Bottom;
}
//----------------------------------------------------------------------------
Int_t RooMeow::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
   return 1;
}
//----------------------------------------------------------------------------
Double_t RooMeow::analyticalIntegral(Int_t code, const char* rangeName) const
{
   return 1;
}
//----------------------------------------------------------------------------





