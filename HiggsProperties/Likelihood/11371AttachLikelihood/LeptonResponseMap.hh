//root -l HiggsAna/HZZ4l/HLL/CreateLeptonResponseMap.C+'("HZZEfficiencyMap_HZZ125.root","HZZ125",0)'


//================================================================================================
//
// Create Efficiency Map
//
//________________________________________________________________________________________________

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TFile.h>                  // file handle class
#include <TTree.h>                  // class to access ntuples
#include <TBranch.h>                // class to access branches in TTree
#include <TClonesArray.h>           // ROOT array class
#include <TCanvas.h>                // class for drawing
#include <TH1F.h>                   // 1D histograms
#include <TBenchmark.h>             // class to track macro running statistics
#include <TLorentzVector.h>         // 4-vector class
#include <TVector3.h>               // 3D vector class
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <string>                   // C++ string class
#include <sstream>                  // class for parsing strings

// data structs
#include "HZZEfficiencyMap.hh"

// RooFit headers
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooExtendPdf.h"
#include "RooCBShape.h"
#include "RooBifurGauss.h"
#include "RooPlot.h"
#include "RooBifurGauss.h"
#include "RooDoubleSidedCBShape.hh"

#endif


//=== FUNCTION DECLARATIONS ======================================================================================

  
inline UInt_t LeptonResponseMapFindBin( const double value, const double bins[], UInt_t nbins) {

  UInt_t nbinboundaries = nbins + 1;
  UInt_t bin = 0;
  for (uint i=0; i < nbinboundaries; ++i) {
    if (i < nbinboundaries-1) {
      if (value >= bins[i] && value < bins[i+1]) {
        bin = i+1;
        break;
      }
    } else if (i == nbinboundaries-1) {
      if (value >= bins[i]) {
        bin = nbinboundaries - 1;
        break;
      }
    }    
  }
  return bin;
}
  




//=== MAIN MACRO =================================================================================================
Bool_t ValidateLeptonResolutionMap(TFile *inputfile, string LeptonType, Int_t Option = 0)
{  
  Bool_t pass = kTRUE;

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  for (uint i = 0; i < 16; ++i) {
    for (uint j = 0; j < 18; ++j) {
      if (Option == 0) {
        RooWorkspace *w = (RooWorkspace*)inputfile->Get(Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j));
        if (!w) { 
          cout << "cannot load workspace: " << Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j) << endl;
          assert(w);
        }
        RooDoubleSidedCBShape *model = (RooDoubleSidedCBShape*)(w->pdf("LeptonPtResModel"));
        if (!model) {
          cout << "cannot find model: " << Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j) << endl;        
          pass = kFALSE;
        }
      }
      if (Option == 1) {
        TH1F *LeptonPtResolutionHist = (TH1F*)inputfile->Get(Form("LeptonPtResolution_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j));
        if (!LeptonPtResolutionHist) {
          cout << "cannot find histogram: " << Form("LeptonPtResolution_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j) << endl;
          pass = kFALSE;
        }
      }
    }
  }
  return pass;  
}


double GenerateLeptonPtFromModel(TFile *inputfile, string LeptonType, Double_t pt, Double_t eta) 
{  

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  UInt_t PtBin = LeptonResponseMapFindBin(pt,ptBins, 14);
  UInt_t EtaBin = LeptonResponseMapFindBin(eta,etaBins, 16);

  RooFit::PrintLevel(-1);

  RooWorkspace *w = (RooWorkspace*)inputfile->Get(Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),PtBin, EtaBin));
  if (!w) { 
    cout << "cannot load workspace: " << Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),PtBin, EtaBin) << endl;
    assert(w);
  }
  RooDoubleSidedCBShape *model = (RooDoubleSidedCBShape*)(w->pdf("LeptonPtResModel"));
  if (!model) {
    cout << "cannot find model: " << Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),PtBin, EtaBin) << endl;
  }

  RooRealVar *leptonPtRes = new RooRealVar("leptonPtRes","leptonPtRes",-0.75,0.75);
  RooDataSet *data = model->generate(*leptonPtRes,1);
  const RooArgSet *ent = data->get(0);
  double val = static_cast<RooAbsReal*>(ent->find(leptonPtRes->GetName()))->getVal();

  double simulatedPt = (val + 1)*pt;
  return simulatedPt;

}


double GenerateLeptonPtFromHist(TFile *inputfile, string LeptonType, Double_t pt, Double_t eta) 
{  

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  UInt_t PtBin = LeptonResponseMapFindBin(pt,ptBins, 14);
  UInt_t EtaBin = LeptonResponseMapFindBin(eta,etaBins, 16);

  TH1F *LeptonPtResolutionHist = (TH1F*)inputfile->Get(Form("LeptonPtResolution_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),PtBin, EtaBin));
  if (!LeptonPtResolutionHist) {
    cout << "cannot find histogram: " << Form("LeptonPtResolution_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),PtBin, EtaBin) << endl;
  }
  if (LeptonPtResolutionHist->Integral() == 0) {
    cout << "Integral=0: " << LeptonPtResolutionHist->GetEntries() << " : " << LeptonType << " " << pt << " " << eta << endl;
  }
  

  double leptonPtFromHist = LeptonPtResolutionHist->GetRandom();
  double simulatedPt = (leptonPtFromHist + 1)*pt;
  return simulatedPt;

} 


