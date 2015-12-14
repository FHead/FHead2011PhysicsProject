//---------------------------------------------------------------------------
#ifndef ROO_MODIFIEDBREITWIGNER
#define ROO_MODIFIEDBREITWIGNER
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
//---------------------------------------------------------------------------
class RooRealVar;
//---------------------------------------------------------------------------
class RooModifiedBreitWigner : public RooAbsPdf
{
public:
   RooModifiedBreitWigner() {}
   RooModifiedBreitWigner(const char *name, const char *title, RooAbsReal& _m, RooAbsReal& _m0);

   RooModifiedBreitWigner(const RooModifiedBreitWigner& other, const char* name = 0);
   virtual TObject* clone(const char* newname) const { return new RooModifiedBreitWigner(*this, newname); }

   inline virtual ~RooModifiedBreitWigner() {}

   void SetSpectra(std::vector<double> mass, std::vector<double> width,
      std::vector<double> brgg, std::vector<double> brzz);
   double GetValue(double x, const std::vector<double> &X, const std::vector<double> &Y) const;
   double GetWidth(double mass) const;
   double GetBrZZ(double mass) const;
   double GetBrGG(double mass) const;
   double Lgg_7(double mHstar) const;

protected:
   RooRealProxy m;
   RooRealProxy m0;

   std::vector<double> Mass;
   std::vector<double> Width;
   std::vector<double> BrGG;
   std::vector<double> BrZZ;

   Double_t evaluate() const;

private:
   // ClassDef(RooModifiedBreitWigner,1) // Modified BW lineshape PDF
};
//---------------------------------------------------------------------------
#endif
