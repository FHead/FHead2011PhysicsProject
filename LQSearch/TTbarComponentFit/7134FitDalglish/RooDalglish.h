//---------------------------------------------------------------------------
#ifndef ROO_Dalglish
#define ROO_Dalglish
//---------------------------------------------------------------------------
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
//---------------------------------------------------------------------------
#include "RooFit.h"

#include "Riostream.h"
#include <TMath.h>
#include <math.h>

#include "RooDalglish.h"
#include "RooRealVar.h"
//---------------------------------------------------------------------------
class RooRealVar;
class RooAbsReal;

#include "TMath.h"
//---------------------------------------------------------------------------
class RooDalglish : public RooAbsPdf
{
public:
   RooDalglish() {} ;
   RooDalglish(const char *name, const char *title,
				RooAbsReal &_x, RooAbsReal &_y, RooAbsReal &_xhat, RooAbsReal &_yhat, RooAbsReal &_b,
				RooAbsReal &_x0, RooAbsReal &_y0, RooAbsReal &_c, RooAbsReal &_s, RooAbsReal &_sigmaX, 
				RooAbsReal &_sigmaY, RooAbsReal &_xoff, RooAbsReal &_yoff);
   RooDalglish(const RooDalglish& other,
      const char* name = 0);
   virtual TObject* clone(const char* newname) const { return new RooDalglish(*this,newname); }
   inline virtual ~RooDalglish() { }

   
	Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,const char* rangeName) const;
	Double_t analyticalIntegral(Int_t code, const char* rangeName) const;

protected:
	RooRealProxy X;        // dependent variable
	RooRealProxy Y;        // other dependent variable
	RooRealProxy Xhat;     // offset parameter for tail part 
	RooRealProxy Yhat;     // offset parameter for tail part
	RooRealProxy B;        // slope of tail part
	RooRealProxy X0;       // X 'scale';
	RooRealProxy Y0;       // Y 'scale';
	RooRealProxy C;        // xy iso contour value
	RooRealProxy S;        // strength of 'turn-off'
	RooRealProxy SigmaX;   // sigma of X gaussian 'turn-off'
	RooRealProxy SigmaY;   // sigma of Y gaussian 'turn-off'
	RooRealProxy XOFF;     // X dial for gaussian 'turn-off'
	RooRealProxy YOFF;     // Y dial for gaussian 'turn-off'
	

   Double_t evaluate() const;
};
//---------------------------------------------------------------------------
RooDalglish::RooDalglish(const char *name,
			 const char *title,
			 RooAbsReal &_x, RooAbsReal &_y, RooAbsReal &_xhat, RooAbsReal &_yhat, RooAbsReal &_b,
			 RooAbsReal &_x0, RooAbsReal &_y0, RooAbsReal &_c, RooAbsReal &_s, 
			 RooAbsReal &_sigmaX, RooAbsReal &_sigmaY, RooAbsReal &_xoff, RooAbsReal &_yoff) :
RooAbsPdf(name, title), 
  X("X", "DependentX", this, _x),
  Y("Y", "DependentY", this, _y),
  Xhat("Xhat", "offset X", this, _xhat),
  Yhat("Yhat", "offset Y", this, _yhat),
  B("B", "tail slope", this, _b),
  X0("X0", "X scale", this, _x0),
  Y0("Y0", "Y scale", this, _y0),
  C("C", "tail slope", this, _c),
  S("S", "turn off slope", this, _s),
  SigmaX("SigmaX", "X sigma", this, _sigmaX),
  SigmaY("SigmaY", "Y sigma", this, _sigmaY),
  XOFF("XOFF", "X dial", this, _xoff),
  YOFF("YOFF", "Y dial", this, _yoff)
{
}
//---------------------------------------------------------------------------
RooDalglish::RooDalglish(const RooDalglish& other, const char* name) :
  RooAbsPdf(other, name), X("X", this, other.X), Y("Y", this, other.Y), Xhat("Xhat", this, other.Xhat),
  Yhat("Yhat", this, other.Yhat), B("B", this, other.B), X0("X0", this, other.X0), Y0("Y0", this, other.Y0),
  C("C", this, other.C), S("S", this, other.S), SigmaX("SigmaX", this, other.SigmaX), 
  SigmaY("SigmaY", this, other.SigmaY), XOFF("XOFF", this, other.XOFF), YOFF("YOFF", this, other.YOFF)
{
}
//---------------------------------------------------------------------------
Double_t RooDalglish::evaluate() const
{
  double value = 0;
  
  double xx = X-X0-Xhat;
  double yy = Y-Y0-Yhat;
  
  double xxhat = X0;
  double yyhat = Y0;
  
  double CP = C+B/(2*S);
  
  
  double POL = B*(X-Xhat)*(Y-Yhat);
  
  /*
    if(POL < 2){
    POL = 2;
    }
  */
  
  value = (POL-1.)*exp(-POL+2.);
  
  
  return max(value, 1e-40);

  if(xx*yy < CP){
    value *= exp(-S*(xx*yy-CP)*(xx*yy-CP));
  }
  
  
  
  if(xx*yy < CP-B/(2*S)){
    value = POL-1.;
    //value *= exp(-B*(xx*yyhat+yy*xxhat+CP+xxhat*yyhat)+2.+B*B/(4*S));
    value *= exp(-B*(xx*yyhat+yy*xxhat+CP+xxhat*yyhat)+2.+B*B/(4*S));
  }
  
  /*
    double yoff = YOFF;
    if(Y < yoff){
    
    value *= exp(-SigmaY*(Y-yoff)*(Y-yoff));
    
    }
    
    double xoff = XOFF;
    if(X < xoff){
    value *= exp(-SigmaX*(X-xoff)*(X-xoff));
    
    }
  */
  return max(value,1e-40);
}

Int_t RooDalglish::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const 
{
   return 0;

  if(matchArgs(allVars,analVars,X)) return 1;
  if(matchArgs(allVars,analVars,Y)) return 2;
  
  return 0;
}

Double_t RooDalglish::analyticalIntegral(Int_t code, const char* rangeName) const
{
  
  switch(code) {
  case 1:
    {
      double ret = 0;
      double MIN = X.min(rangeName);
      double MAX = X.max(rangeName);
      double xL[2];
      double xxL[2];
      xL[0] = MIN;
      xL[1] = MAX;
      xxL[0] = MIN-X0-Xhat;
      xxL[1] = MAX-X0-Xhat;
      
      double yy = Y-Y0-Yhat;
      
      double CP = C+B/(2*S);
      
      //First, we check whether Y is large enough for X to cross into transition/tail
      if(yy > 0.0){
	//now, we need to check which transistions this thing crosses.
	double TRAN = CP/yy+X0+Xhat; //tail to transition
	if(MIN > TRAN){ //tail only
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    INT[i] = -1.*(xL[i]-Xhat)*exp(-B*(xL[i]-Xhat)*(Y-Yhat)+2.);
	  }
	  ret = INT[1]-INT[0];
	  return ret;
	}
	//for(int i = 0; i < 100; i++) cout << "HERE" << endl;
	if(MAX < TRAN){ //core only
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    double xx = xxL[i];
	    double x = xL[i];
	    
	    INT[i] = (exp(2.+B*B/(4.*S))/(B*Y0*Y0))*(-B*Y0*(x-Xhat)*(Y-Yhat)-yy)*exp(-B*(CP+xx*Y0+X0*(Y-Yhat)));
	  }
	  ret = INT[1]-INT[0];
	  return ret;
	} else {
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    double xx = xxL[i];
	    double x = xL[i];
	    if(i == 1){
	      xx = TRAN-X0-Xhat;
	      x = TRAN;
	    }
	    INT[i] = (exp(2.+B*B/(4.*S))/(B*Y0*Y0))*(-B*Y0*(x-Xhat)*(Y-Yhat)-yy)*exp(-B*(CP+xx*Y0+X0*(Y-Yhat)));
	  }
	  for(int i = 0; i < 2; i++){
	    double x = xL[i];
	    if(i == 0) x = TRAN;
	    INT[i] += -1.*(x-Xhat)*exp(-B*(x-Xhat)*(Y-Yhat)+2.);
	  }
	  ret = INT[1]-INT[0];
	  return ret;
					
	}
      } else {
	double INT[2];
	for(int i = 0; i < 2; i++){
	  double xx = xxL[i];
	  double x = xL[i];
	  INT[i] = (exp(2.+B*B/(4.*S))/(B*Y0*Y0))*(-B*Y0*(x-Xhat)*(Y-Yhat)-yy)*exp(-B*(CP+xx*Y0+X0*(Y-Yhat)));
	}
	ret = INT[1]-INT[0];
	return ret;
      }
			
			
			
      // should never get here
      return 0.0;
			
    }
  case 2:
    {
      double ret = 0;
      double MIN = Y.min(rangeName);
      double MAX = Y.max(rangeName);
      double yL[2];
      double yyL[2];
      yL[0] = MIN;
      yL[1] = MAX;
      yyL[0] = MIN-Y0-Yhat;
      yyL[1] = MAX-Y0-Yhat;
			
      double xx = X-X0-Xhat;
			
      double CP = C+B/(2*S);
			
      //First, we check whether X is large enough for Y to cross into transition/tail
      if(xx > 0.0){
	//now, we need to check which transistions this thing crosses.
	double TRAN = CP/xx+Y0+Yhat; //tail to transition
	if(MIN > TRAN){ //tail only
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    INT[i] = -1.*(yL[i]-Yhat)*exp(-B*(yL[i]-Yhat)*(X-Xhat)+2.);
	  }
	  ret = INT[1]-INT[0];
	  return ret;
	}
	//for(int i = 0; i < 100; i++) cout << "HERE" << endl;
	if(MAX < TRAN){ //core only
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    double yy = yyL[i];
	    double y = yL[i];
						
	    INT[i] = (exp(2.+B*B/(4.*S))/(B*X0*X0))*(-B*X0*(y-Yhat)*(X-Xhat)-xx)*exp(-B*(CP+yy*X0+Y0*(X-Xhat)));
	  }
	  ret = INT[1]-INT[0];
	  return ret;
	} else {
	  double INT[2];
	  for(int i = 0; i < 2; i++){
	    double yy = yyL[i];
	    double y = yL[i];
	    if(i == 1){
	      yy = TRAN-Y0-Yhat;
	      y = TRAN;
	    }
						
	    INT[i] = (exp(2.+B*B/(4.*S))/(B*X0*X0))*(-B*X0*(y-Yhat)*(X-Xhat)-xx)*exp(-B*(CP+yy*X0+Y0*(X-Xhat)));
	  }
	  for(int i = 0; i < 2; i++){
	    double y = yL[i];
	    if(i == 0) y = TRAN;
	    INT[i] += -1.*(y-Yhat)*exp(-B*(y-Yhat)*(X-Xhat)+2.);
	  }
	  ret = INT[1]-INT[0];
	  return ret;
					
	}
      } else {
	double INT[2];
	for(int i = 0; i < 2; i++){
	  double yy = yyL[i];
	  double y = yL[i];
					
	  INT[i] = (exp(2.+B*B/(4.*S))/(B*X0*X0))*(-B*X0*(y-Yhat)*(X-Xhat)-xx)*exp(-B*(CP+yy*X0+Y0*(X-Xhat)));
	}
	ret = INT[1]-INT[0];
	return ret;
      }
			
			
			
      // should never get here
      return 0.0;
			
    }
  }
	
	
  assert(0);
  return 0;
}
//---------------------------------------------------------------------------
#endif
