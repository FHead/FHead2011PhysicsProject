#ifndef ROOMEOW_11525_JASKDLJHNFASKDBHNFJASKHFASDf
#define ROOMEOW_11525_JASKDLJHNFASKDBHNFJASKHFASDf

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooMeow : public RooAbsPdf
{
public:
   RooMeow() {}
   RooMeow(const char *name, const char *title, RooAbsReal &a1, RooAbsReal &a3, RooAbsReal &a3phase,
      RooAbsReal &v11, RooAbsReal &v33, RooAbsReal &v44, RooAbsReal &v13, RooAbsReal &v14/*, RooAbsReal &v34*/,
      RooAbsReal &i11, RooAbsReal &i33, RooAbsReal &i44, RooAbsReal &i13, RooAbsReal &i14/*, RooAbsReal &i34*/);

   RooMeow(const RooMeow &other, const char *name = 0);
   virtual TObject* clone(const char *newname) const { return new RooMeow(*this, newname); }

   inline virtual ~RooMeow() {}

   Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
   Double_t analyticalIntegral(Int_t code, const char* rangeName) const;

protected:
   RooRealProxy A1;
   RooRealProxy A3;
   RooRealProxy A3Phase;
   RooRealProxy V11, V33, V44, V13, V14, V34;
   RooRealProxy I11, I33, I44, I13, I14, I34;

   Double_t evaluate() const;

private:
   // ClassDef(RooMeow,1) // Crystal Ball lineshape PDF
};

#endif
