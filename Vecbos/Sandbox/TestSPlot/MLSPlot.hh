#ifndef ML_SPLOT
#define ML_SPLOT

class RooAbsReal;
class RooDataSet;
class RooFitResult;
class RooRealVar;
class RooSimultaneous;

#include <TH1.h>
#include <RooFitResult.h>
#include <RooRealVar.h>
#include <RooHist.h>
#include <RooPlot.h>

class MLSPlot : public TH1D {
public:
  MLSPlot();
  MLSPlot(const MLSPlot &other);
  MLSPlot(const char* name, const char *title, Int_t nbins, Double_t xmin, Double_t xmax);

  static RooDataSet* 
  addSWeightToData(const RooSimultaneous* pdf, const RooArgList &yieldsTmp, 
		   RooDataSet &data, const RooArgSet &projDeps=RooArgSet()) ;
  

 void fillSPlot(const RooDataSet &data, TString varname, TString weightname);

  void fillSPlot(const RooAbsReal &x, RooAbsReal &nstar, RooDataSet data, const RooFitResult &fitRes, const RooArgList &pdfList, const RooArgList &yields, Bool_t doErrors, const RooArgSet &projDeps=RooArgSet() );
  void fillSPlot(const RooAbsReal &x, RooAbsReal &nstar, RooDataSet data, const RooFitResult &fitRes, const RooArgList &pdfList, const RooArgList &yields, RooAbsPdf &totalPdf, Bool_t doErrors, const RooArgSet &projDeps=RooArgSet() );

  void fillSPlot(const RooAbsReal &x, RooAbsReal &nstar, RooDataSet data, const RooFitResult &fitRes, RooAbsPdf &totalPdf, RooArgList &yields, Bool_t doErrors, const RooArgSet &projDeps=RooArgSet() );

  Double_t getComponentValue(RooAbsPdf &pdf, RooArgList &yieldsTmp, Int_t igood, RooArgSet &normSet);

protected:

  ClassDef(MLSPlot,1)   // Make sPlot
};

#endif












