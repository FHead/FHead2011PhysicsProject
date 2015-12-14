/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooDoubleSidedCBShape.hh,v 1.1 2012/07/06 17:38:42 sixie Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_DOUBLESIDEDCRYSTALBALL_SHAPE
#define ROO_DOUBLESIDEDCRYSTALBALL_SHAPE

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooDoubleSidedCBShape : public RooAbsPdf {
public:
  RooDoubleSidedCBShape() {}
  RooDoubleSidedCBShape(const char *name, const char *title, RooAbsReal& _m,
                            RooAbsReal& _m0, RooAbsReal& _sigma,
                            RooAbsReal& _alphaL, RooAbsReal& _nL,
                            RooAbsReal& _alphaR, RooAbsReal& _nR);

  RooDoubleSidedCBShape(const RooDoubleSidedCBShape& other, const char* name = 0);
  virtual TObject* clone(const char* newname) const { return new RooDoubleSidedCBShape(*this,newname); }

  inline virtual ~RooDoubleSidedCBShape() { }

protected:


  RooRealProxy m;
  RooRealProxy m0;
  RooRealProxy sigma;
  RooRealProxy alphaL;
  RooRealProxy nL;
  RooRealProxy alphaR;
  RooRealProxy nR;

  Double_t evaluate() const;

private:
  ClassDef(RooDoubleSidedCBShape,1) // Crystal Ball lineshape PDF
};

#endif
