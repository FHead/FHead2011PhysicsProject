// root -l HiggsAna/HZZ4l/HLL/PerformFastSimulation.C+'("HZZEventNtuple_Test_0000.root","HZZEventNtuple_FastSim_Test_0000.root","ZZ",0)'

//================================================================================================
//
//
//
//
//________________________________________________________________________________________________

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TFile.h>                  // file handle class
#include <TTree.h>                  // class to access ntuples
#include <TBranch.h>                // class to access branches in TTree
#include <TClonesArray.h>           // ROOT array class
#include <iostream>                 // standard I/O
#include "RooMsgService.h"

#include "HiggsAna/HZZ4l/interface/HZZEventTree.h"
#include "HiggsAna/HZZ4l/HLL/LeptonResolutionData/ElectronEfficiencyMap.h"
#include "HiggsAna/HZZ4l/HLL/LeptonResolutionData/MuonEfficiencyMap.h"
#include "LeptonResponseMap.hh"
#include "HiggsAna/Utils/CommonDefs.hh"

#endif


//*************************************************************************************************
//Main Function
//*************************************************************************************************
void PtResolutionModel(string inputfilename, string outputfilename,
                           const string Label = "ZZ", Int_t Option = 0) {


  Bool_t pass = kTRUE;

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  RooFit::PrintLevel(-1);

  for (uint i = 0; i < 16; ++i) {
    for (uint j = 0; j < 18; ++j) {
      if (Option == 0) {
        RooDoubleSidedCBShape *model = (RooDoubleSidedCBShape*)inputfile->Get(Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j));
        if (!model) {
          cout << "cannot find model: " << Form("LeptonPtResolutionModel_%s_PtBin%d_EtaBin%d",LeptonType.c_str(),i, j) << endl;        
          pass = kFALSE;
          continue;
        }

        RooRealVar leptonPtRes("leptonPtRes","leptonPtRes",-0.75,0.75);
        RooDataHist *data = new RooDataHist();


        RooRealVar     *mean  = new RooRealVar("mean","mean",0.06,-10,10);
        RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.0165,0.00001,0.0175);
        RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,50);
        RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,30);
        RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,50);
        RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,30);
        

        cout << "Model: " << model->

      }

    }
  }



}
