//root -l EWKAna/HZZ4l/Selection/HZZ4lSelection.C+\(\"\"\)

//================================================================================================
//
// HZZ4l selection macro
//
//  * plots distributions associated with selected events
//  * prints list of selected events from data
//  * outputs ROOT files of events passing selection for each sample, 
//    which can be processed by plotSelect.C
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

// define structures to read in ntuple
#include "HiggsAna/DataTree/interface/HiggsAnaDefs.hh"
#include "HiggsAna/DataTree/interface/TEventInfo.hh"
#include "HiggsAna/DataTree/interface/TElectron.hh"
#include "HiggsAna/DataTree/interface/TMuon.hh"
#include "HiggsAna/DataTree/interface/TJet.hh"
#include "HiggsAna/DataTree/interface/TGenParticle.hh"
#include "HiggsAna/DataTree/interface/TPFCandidate.hh"

#include "EGamma/EGammaAnalysisTools/interface/EGammaMvaEleEstimator.h"
#include "HiggsAna/Utils/CommonDefs.hh"
#include "HiggsAna/Utils/LeptonIDCuts.hh"
#include "HiggsAna/HZZ4l/Utils/LeptonSelection.hh"
#include "HiggsAna/HZZ4l/Utils/HZZDefs.hh"
#include "HiggsAna/HZZ4l/Utils/FSRRecovery.hh"

// output data structs
#include "HiggsAna/HZZ4l/interface/HZZEfficiencyMap.hh"

// #include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#endif


//=== FUNCTION DECLARATIONS ======================================================================================

//------------------------------------------------------------------------------
// getTreeFromFile
//------------------------------------------------------------------------------
TTree* getTreeFromFile(const char* infname, const char* tname)
{
  bool verbose = false;

  if (verbose) {
    cout << "--- Open file " << infname << endl;
  }
  
  TFile* inf = TFile::Open(infname,"read");
  assert(inf);

  TTree* t = (TTree*)inf->Get(tname);
  
  if (!t) {
    TDirectory *dir = (TDirectory*)inf->FindObjectAny("HwwNtuplerMod");
    if (!dir) {
      cout << "Cannot get Directory HwwNtuplerMod from file " << infname << endl;
      assert(dir);
    }
    t = (TTree*)dir->Get(tname);
  }

  if (!t) {
    cout << "Cannot get Tree with name " << tname << " from file " << infname << endl;
  }
  assert(t);


  if (verbose) {
    cout << "---\tRecovered tree " << t->GetName()
	 << " with "<< t->GetEntries() << " entries" << endl;
  }
  
  return t;
}




//=== MAIN MACRO =================================================================================================

void MakeEfficiencyMapNtuple(const string Label = "ZZ", Int_t Option = 0) 
{  
  gBenchmark->Start("HZZTemplate");
  string label = Label;
  if (Label != "") label = "_" + Label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //==============================================================================================================
  Bool_t printDebug = kFALSE;
  //Double_t lumi = 1092;              // luminosity (pb^-1)
  Bool_t doFSR = kTRUE;

  UInt_t DataEra = 0;

  if (Option == 0) {
    DataEra = kDataEra_2011_MC;
  } else if (Option == 1) {
    DataEra = kDataEra_2012_MC;
  }

  vector<vector<string> > inputFiles;

  inputFiles.push_back(vector<string>());
  if (Option == 0) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0003.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0004.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0005.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0006.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0007.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0008.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0009.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz2e2m-powheg-v9_noskim_0010.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0003.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0004.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0005.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0006.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0007.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4e-powheg-v9_noskim_0008.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0003.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0004.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0005.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0006.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0007.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-zz4m-powheg-v9_noskim_0008.root");


  }


  if (Option == 120) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0003.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0004.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h120zz4l-gf-v9_noskim_0005.root");

  }
  if (Option == 121) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h121zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h121zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h121zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 122) {

  }
  if (Option == 123) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h123zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h123zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h123zz4l-gf-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h123zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 124) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h124zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h124zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h124zz4l-gf-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h124zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 125) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0003.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0004.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-gf-v9_noskim_0005.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h125zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 126) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h126zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h126zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h126zz4l-gf-v9_noskim_0002.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h126zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 127) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h127zz4l-gf-v9_noskim_0000.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h127zz4l-gf-v9_noskim_0001.root");
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h127zz4l-vbf-v9_noskim_0000.root");

  }
  if (Option == 130) {
    inputFiles.back().push_back("root://eoscms//eos/cms/store/group/phys_higgs/cmshzz4l/sixie/hist/AllNtuple/cern/filefi/028/AllNtuple_HZZ4lNtuple_s12-h130zz4l-vbf-v9_noskim_0000.root");

  }



  vector<string> processNames;
  processNames.push_back("HZZ120");
//   processNames.push_back("Data");
//   processNames.push_back("ZZ");
//   processNames.push_back("WZ");
//   processNames.push_back("ttbar");
//   processNames.push_back("WW"); 

  assert(processNames.size() == inputFiles.size());


  //--------------------------------------------------------------------------------------------------------------
  // Set up MVA Evaluator Classes
  //==============================================================================================================  

  EGammaMvaEleEstimator *eleIDMVA = new EGammaMvaEleEstimator();
  vector<string> weightFiles;

  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat1.weights.xml")).c_str());
  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat2.weights.xml")).c_str());
  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat3.weights.xml")).c_str());
  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat4.weights.xml")).c_str());
  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat5.weights.xml")).c_str());
  weightFiles.push_back((string(getenv("CMSSW_BASE"))+string("/src/HiggsAna/HZZ4l/data/ElectronIDMVAWeights/Electrons_BDTG_NonTrigV0_Cat6.weights.xml")).c_str());
  
  eleIDMVA->initialize( "BDT", EGammaMvaEleEstimator::kNonTrig,
                        kTRUE, weightFiles);
  


  //--------------------------------------------------------------------------------------------------------------
  // Yields
  //==============================================================================================================  
  const UInt_t NSelectionStages = 12;
  Int_t NEventsPassSelectionStages[NSelectionStages];
  Int_t NEventsPassSelectionStages_Z1e[NSelectionStages];
  Int_t NEventsPassSelectionStages_Z1m[NSelectionStages];
  Int_t NEventsPassSelectionStages_4e[NSelectionStages];
  Int_t NEventsPassSelectionStages_4m[NSelectionStages];
  Int_t NEventsPassSelectionStages_2e2m[NSelectionStages];
  for (UInt_t n=0; n < NSelectionStages; ++n) {
    NEventsPassSelectionStages[n] = 0;
    NEventsPassSelectionStages_Z1e[n] = 0;
    NEventsPassSelectionStages_Z1m[n] = 0;
    NEventsPassSelectionStages_4e[n] = 0;
    NEventsPassSelectionStages_4m[n] = 0;
    NEventsPassSelectionStages_2e2m[n] = 0;
  }


  
  //--------------------------------------------------------------------------------------------------------------
  // Pileup Reweighting
  //==============================================================================================================  
  TFile *fPUFile = TFile::Open("/afs/cern.ch/work/s/sixie/public/HZZ4l/auxiliar/2012/puWeights_Summer12_5000ipb_71mb.root");
  TH1D *fhDPU = (TH1D*)(fPUFile->Get("puWeights"));
  assert(fhDPU);
  fhDPU->SetDirectory(0);
  delete fPUFile;


  //--------------------------------------------------------------------------------------------------------------
  // output ntuple structure
  //==============================================================================================================  
  HZZEfficiencyMap efficiencyMap;

  TFile *fOutputFile = new TFile(("HZZEfficiencyMap"+label+".root").c_str(), "RECREATE");
  TTree *fOutputTree = new TTree("EfficiencyMap","EfficiencyMap");
  fOutputTree->Branch("efficiencyMap",&efficiencyMap);


  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code 
  //==============================================================================================================  
  ofstream eventList("ReferenceSelection_sixie.eventList.txt");
  //
  // Access samples and fill histograms
  TTree *eventTree=0;  
   
  // Data structures to store info from TTrees
  higgsana::TEventInfo *info    = new higgsana::TEventInfo();
  TClonesArray *electronArr = new TClonesArray("higgsana::TElectron");
  TClonesArray *muonArr = new TClonesArray("higgsana::TMuon");
  TClonesArray *jetArr = new TClonesArray("higgsana::TJet");
  TClonesArray *genparticleArr = new TClonesArray("higgsana::TGenParticle");
  TClonesArray *pfcandidateArr = new TClonesArray("higgsana::TPFCandidate");
  
  for (UInt_t qq = 0; qq<inputFiles.size() ; ++qq) { 
    for (UInt_t f = 0; f < inputFiles[qq].size() ; ++f) {

      printDebug = kFALSE;

      //********************************************************
      // Get Tree
      //********************************************************
      cout << "Reading File " << inputFiles[qq][f] << endl;
      eventTree = getTreeFromFile(inputFiles[qq][f].c_str(),"Events"); 
      TBranch *infoBr;
      TBranch *electronBr;
      TBranch *muonBr;
      TBranch *jetBr;
      TBranch *genparticleBr;
      TBranch *pfcandidateBr;


      //*****************************************************************************************
      //Loop over muon Data Tree
      //*****************************************************************************************
      // Set branch address to structures that will store the info  
      eventTree->SetBranchAddress("Info",       &info);      infoBr       = eventTree->GetBranch("Info");
      eventTree->SetBranchAddress("Electron", &electronArr); electronBr = eventTree->GetBranch("Electron");
      eventTree->SetBranchAddress("Muon", &muonArr);         muonBr = eventTree->GetBranch("Muon");
      eventTree->SetBranchAddress("PFJet", &jetArr);         jetBr = eventTree->GetBranch("PFJet");
      eventTree->SetBranchAddress("GenParticle", &genparticleArr);         genparticleBr = eventTree->GetBranch("GenParticle");
      eventTree->SetBranchAddress("PFCandidate", &pfcandidateArr);         pfcandidateBr = eventTree->GetBranch("PFCandidate");
  
      for(UInt_t ientry=0; ientry<eventTree->GetEntries(); ientry++) {       	
        infoBr->GetEntry(ientry);
        if (ientry % 10000 == 0) cout << "Event " << ientry << endl;
	
        //Use Only Testing events
        //if (info->evtNum % 2 == 0 ) continue;
        //Use Only Training events
        //if (info->evtNum % 2 != 0 ) continue;
       

        //********************************************************
        //double mynpu = TMath::Min((double)info->nPUEvents,34.999);
        //Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
        //double npuWeight = fhDPU->GetBinContent(npuxbin);
        //********************************************************


        //***********************************************************
        // Definition of Pileup Energy density
        //***********************************************************
        Double_t rhoMuonIso = 0;
        Double_t rhoEleIso = 0;
        UInt_t MuonEAEra = 0;
        UInt_t EleEAEra = 0;

        if (DataEra == kDataEra_2011_MC) {
     
          if (!(isnan(info->RhoKt6PFJetsForIso25) || 
                isinf(info->RhoKt6PFJetsForIso25))) {
            rhoMuonIso = info->RhoKt6PFJetsForIso25;
            rhoEleIso = info->RhoKt6PFJetsForIso25;
          }
          MuonEAEra = kDataEra_2011_Data;
          EleEAEra = kDataEra_2011_Data;

        } else if (DataEra == kDataEra_2012_MC) {

          if (!(isnan(info->RhoKt6PFJetsCentralNeutral) || 
                isinf(info->RhoKt6PFJetsCentralNeutral))) {
            rhoMuonIso = info->RhoKt6PFJetsCentralNeutral;
          }

          if (!(isnan(info->RhoKt6PFJets) || 
                isinf(info->RhoKt6PFJets))) {
            rhoEleIso = info->RhoKt6PFJets;
          }

          MuonEAEra = kDataEra_2012_Data;
          EleEAEra = kDataEra_2012_Data;

        }

        if(printDebug) cout << "Muon Isolation Rho: " << rhoMuonIso << endl;
        if(printDebug) cout << "Muon EA Era: " << MuonEAEra << endl;
        if(printDebug) cout << "Ele Isolation Rho: " << rhoEleIso << endl;
        if(printDebug) cout << "Ele EA Era: " << EleEAEra << endl;

   

        //********************************************************
        // Printdebug
        //********************************************************
        if ((0 == 1)
          ) printDebug = kTRUE;
        



        //********************************************************
        // Load the branches
        //********************************************************
        electronArr->Clear(); 
        muonArr->Clear(); 
        jetArr->Clear();  //if (info->evtNum % 2 != 0 ) continue;
       
        genparticleArr->Clear(); 
        pfcandidateArr->Clear(); 
        electronBr->GetEntry(ientry);
        muonBr->GetEntry(ientry);
        jetBr->GetEntry(ientry);
        genparticleBr->GetEntry(ientry);
        pfcandidateBr->GetEntry(ientry);

//         Double_t eventweight = info->eventweight * lumi * npuWeight;
        //Double_t eventweight = npuWeight;
        

        //********************************************************
        // Efficiency Map
        //********************************************************
        vector<Double_t> pdgid;
        vector<Double_t> status;
        vector<Double_t> genpt;
        vector<Double_t> geneta;
        vector<Double_t> genphi;
        vector<Double_t> recopt;
        vector<Double_t> recoeta;
        vector<Double_t> recophi;
        vector<Int_t>    recoCharge;
        vector<Bool_t>   pass;

        //********************************************************
        // GenInfo
        //********************************************************
        vector<Double_t> genpt_ele;
        vector<Double_t> geneta_ele;
        vector<Double_t> genphi_ele;
        vector<Double_t> genpt_mu;
        vector<Double_t> geneta_mu;
        vector<Double_t> genphi_mu;

        Double_t minGenLeptonDR = 9999;
        for(Int_t k=0; k<genparticleArr->GetEntries(); k++) {
          const higgsana::TGenParticle *gen = (higgsana::TGenParticle*)((*genparticleArr)[k]);


//           if (gen->status == 1 && (abs(gen->pdgid) == 11 || abs(gen->pdgid) == 13 ) ) {

          //Take pre-FSR leptons, direct daughter of the Z decay
          if ( (abs(gen->pdgid) == 11 || abs(gen->pdgid) == 13) && gen->motherPdgID == 23 ) {
            if (abs(gen->pdgid) == 11) {
              if (!(fabs(gen->eta) < 2.5 )) continue;
            }
            if (abs(gen->pdgid) == 13) {
              if (!(fabs(gen->eta) < 2.4 )) continue;
            }
            pdgid.push_back(gen->pdgid); 
            status.push_back(gen->status);
            genpt.push_back(gen->pt); 
            geneta.push_back(gen->eta); 
            genphi.push_back(gen->phi); 
            recopt.push_back(-9999); 
            recoeta.push_back(-9999); 
            recophi.push_back(-9999); 
            recoCharge.push_back(-9999);
            pass.push_back(kFALSE); 

            if (abs(gen->pdgid) == 11) {
              genpt_ele.push_back(gen->pt);
              geneta_ele.push_back(gen->eta);
              genphi_ele.push_back(gen->phi);
            }
            if (abs(gen->pdgid) == 13) {
              genpt_mu.push_back(gen->pt);
              geneta_mu.push_back(gen->eta);
              genphi_mu.push_back(gen->phi);
            }
          }

          //find pair of gen leptons that are closest in DR
          if (!(gen->status == 1 && (abs(gen->pdgid) == 11 || abs(gen->pdgid) == 13))) continue;
          for(Int_t l=k+1; l<genparticleArr->GetEntries(); l++) {
            const higgsana::TGenParticle *p2 = (higgsana::TGenParticle*)((*genparticleArr)[l]);
            if (!(p2->status == 1 && (abs(p2->pdgid) == 11 || abs(p2->pdgid) == 13))) continue;
            if (minGenLeptonDR > deltaR(gen->eta,gen->phi,p2->eta,p2->phi)) {
              minGenLeptonDR = deltaR(gen->eta,gen->phi,p2->eta,p2->phi);
            }
          }
        }

        //******************************************************************
        //print out gen leptons
        //******************************************************************
        //for(UInt_t l=0; l<pdgid.size(); ++l) {
          //cout << "GenLepton " << l << " : " << pdgid[l] << " " << status[l] << " : " << genpt[l] << " " << geneta[l] << " " << genphi[l] << endl;
        //}



        //********************************************************
        // Met
        //********************************************************
        TVector3 pfMet;        
        if(info->pfMEx!=0 || info->pfMEy!=0) {       
          pfMet.SetXYZ(info->pfMEx, info->pfMEy, 0);
        }



        //********************************************************
        // Selection Steps
        //********************************************************
        Bool_t PassSelectionStages[NSelectionStages];
        Bool_t PassSelectionStages_Z1e[NSelectionStages];
        Bool_t PassSelectionStages_Z1m[NSelectionStages];
        Bool_t PassSelectionStages_4e[NSelectionStages];
        Bool_t PassSelectionStages_4m[NSelectionStages];
        Bool_t PassSelectionStages_2e2m[NSelectionStages];
        for (UInt_t n=0; n < NSelectionStages; ++n) {
          PassSelectionStages[n] = kFALSE;
          PassSelectionStages_Z1e[n] = kFALSE;
          PassSelectionStages_Z1m[n] = kFALSE;
          PassSelectionStages_4e[n] = kFALSE;
          PassSelectionStages_4m[n] = kFALSE;
          PassSelectionStages_2e2m[n] = kFALSE;
        }


        //********************************************************
        // Selection Stage 0 : Skim 0
        //********************************************************
        int nlep_above_10=0;
        int nlep_above_20=0;
        for(uint i=0; i<uint(muonArr->GetEntries()); i++) 
        {
          const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[i]);        
          if( !( (mu->typeBits & kGlobal) == kGlobal || 
                 (mu->typeBits & kTracker) == kTracker) 
            ) continue;
          if( fabs(mu->eta) > 2.4 ) continue; 
          if( mu->pt > 10 )  nlep_above_10++;
          if( mu->pt > 20 )  nlep_above_20++;
        }
        for(uint i=0; i<uint(electronArr->GetEntries()); i++) 
        {
          const higgsana::TElectron *ele = (higgsana::TElectron*)((*electronArr)[i]);        
          if( fabs(ele->eta) > 2.5 )                        continue; 
          if( ele->pt > 10 )  nlep_above_10++;
          if( ele->pt > 20 )  nlep_above_20++;
        }
        if( nlep_above_10 > 1 && nlep_above_20 > 0) {          
          PassSelectionStages[0] = kTRUE;
          PassSelectionStages_Z1e[0] = kTRUE;
          PassSelectionStages_Z1m[0] = kTRUE;
          PassSelectionStages_4e[0] = kTRUE;
          PassSelectionStages_4m[0] = kTRUE;
          PassSelectionStages_2e2m[0] = kTRUE;
        } else {
          PassSelectionStages[0] = kFALSE;                   
        }

        //********************************************************
        // Selection Stage 1: Skim 0.1 - 1 SF pair with  mLL > 40 
        //********************************************************
        bool ossf_pair=false;

        //Look for mumu pair
        for(uint i=0; i<uint(muonArr->GetEntries()); i++) {
          const higgsana::TMuon *mu1 = (higgsana::TMuon*)((*muonArr)[i]);  

          if (printDebug) cout << "mu1 " << mu1->pt << " " << mu1->eta << " " << mu1->phi << endl;

          if( !( (mu1->typeBits & kGlobal) == kGlobal || 
                 (mu1->typeBits & kTracker) == kTracker) 
            ) continue;
          if( fabs(mu1->eta) > 2.4 ) continue; 
          if( fabs(mu1->pt) < 3 ) continue; 
          
          for(uint j=i+1; j<uint(muonArr->GetEntries()); j++) {
            const higgsana::TMuon *mu2 = (higgsana::TMuon*)((*muonArr)[j]);        
            if( !( (mu2->typeBits & kGlobal) == kGlobal || 
                   (mu2->typeBits & kTracker) == kTracker) 
              ) continue;
            if( fabs(mu2->eta) > 2.4 ) continue; 
            if( fabs(mu2->pt) < 3 ) continue; 

            TLorentzVector v1,v2;
            v1.SetPtEtaPhiM( mu1->pt, mu1->eta, mu1->phi, MUONMASS);
            v2.SetPtEtaPhiM( mu2->pt, mu2->eta, mu2->phi, MUONMASS);
            if( (v1+v2).M() >= 40) ossf_pair = true;

          }
        }

        //Look for ee pair
        for(uint i=0; i<uint(electronArr->GetEntries()); i++) {
          const higgsana::TElectron *el1 = (higgsana::TElectron*)((*electronArr)[i]);        
          if (printDebug) cout << "el1 " << el1->pt << " " << el1->eta << " " << el1->phi << endl;

          if( fabs(el1->eta) > 2.5 )                continue; 
          if( el1->pt < 5 )                         continue; 

          for(uint j=i+1; j<uint(electronArr->GetEntries()); j++) {
            const higgsana::TElectron *el2 = (higgsana::TElectron*)((*electronArr)[j]);        
            if( fabs(el2->eta) > 2.5 )              continue; 
            if( el2->pt < 5 )                     continue; 
            TLorentzVector v1,v2;
            v1.SetPtEtaPhiM( el1->pt, el1->eta, el1->phi, ELECTRONMASS);
            v2.SetPtEtaPhiM( el2->pt, el2->eta, el2->phi, ELECTRONMASS);
            if( (v1+v2).M() >= 40 ) ossf_pair = true;
          }
        }

        if( ossf_pair ) {
          PassSelectionStages[1] = kTRUE;
          PassSelectionStages_Z1e[1] = kTRUE;
          PassSelectionStages_Z1m[1] = kTRUE;
          PassSelectionStages_4e[1] = kTRUE;
          PassSelectionStages_4m[1] = kTRUE;
          PassSelectionStages_2e2m[1] = kTRUE;
        } else {
          PassSelectionStages[1] = kFALSE;
        }
        

        //***********************************************************
        // Selection Stage 2: Trigger Selection  
        //***********************************************************

        if (DataEra == kDataEra_2011_MC) {
          if (
            (info->triggerBits & kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) == kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL
            ||
            (info->triggerBits & kHLT_Mu17_Mu8) == kHLT_Mu17_Mu8
            ) {
            PassSelectionStages[2] = kTRUE;
            PassSelectionStages_Z1e[2] = kTRUE;
            PassSelectionStages_Z1m[2] = kTRUE;
            PassSelectionStages_4e[2] = kTRUE;
            PassSelectionStages_4m[2] = kTRUE;
            PassSelectionStages_2e2m[2] = kTRUE;
          } else {
            PassSelectionStages[2] = kFALSE;
          }

          if (printDebug) {
            cout << "DEBUG Trigger: "
                 << Bool_t((info->triggerBits & kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) == kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) << " "
                 << Bool_t((info->triggerBits & kHLT_Mu17_Mu8) == kHLT_Mu17_Mu8) << " "
                 << endl;
            cout << PassSelectionStages[2] << endl;
          }   


        } else if (DataEra == kDataEra_2012_MC) {
          if (
            (info->triggerBits & kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) == kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL
            ||
            (info->triggerBits & kHLT_Mu17_Mu8) == kHLT_Mu17_Mu8
            ||
            (info->triggerBits & kHLT_Mu17_TkMu8) == kHLT_Mu17_TkMu8
            ||
            (info->triggerBits & kHLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) == kHLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL
            ||
            (info->triggerBits & kHLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) == kHLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL
            ) {
            PassSelectionStages[2] = kTRUE;
            PassSelectionStages_Z1e[2] = kTRUE;
            PassSelectionStages_Z1m[2] = kTRUE;
            PassSelectionStages_4e[2] = kTRUE;
            PassSelectionStages_4m[2] = kTRUE;
            PassSelectionStages_2e2m[2] = kTRUE;
          } else {
            PassSelectionStages[2] = kFALSE;
          }

          if (printDebug) {
            cout << "DEBUG Trigger: "
                 << Bool_t((info->triggerBits & kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) == kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL) << " "
                 << Bool_t((info->triggerBits & kHLT_Mu17_Mu8) == kHLT_Mu17_Mu8) << " "
                 << Bool_t((info->triggerBits & kHLT_Mu17_TkMu8) == kHLT_Mu17_TkMu8) << " "
                 << Bool_t((info->triggerBits & kHLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) == kHLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) << " "
                  << Bool_t((info->triggerBits & kHLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) == kHLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) << " "
                << endl;
            cout << PassSelectionStages[2] << endl;
          }


        }


        if (printDebug) cout << "PassSelectionStages[2] = " << PassSelectionStages[2] << endl;


        //***********************************************************
        // Selection Stage 2: Lepton Selection 
        //***********************************************************
        vector<Int_t> leptonType;
        vector<UInt_t> leptonIndex;

        //  Build collection of leptons to be vetoed for isolation
        //  empty, reference selection applies no additional vetos 
        //  vector<const higgsana::TMuon*> muonsToVeto;
        //  vector<const higgsana::TElectron*> electronsToVeto;

        //  Build collection of PFPhotons (identified as FSR) to be
        //  vetoed for isolation
        vector<const higgsana::TPFCandidate*> photonsToVeto;

        //    
        if( printDebug ) cout << "\tnMuons: " << muonArr->GetEntries() << endl;
        //----------------------------------------------------
        for(uint i=0; i<uint(muonArr->GetEntries()); i++) 
        {
          const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[i]);      

          if( printDebug ) { 
            cout << "muon:: " << mu->pt << " " << mu->eta << " " << mu->phi << " : " ;
          }

          if (!PassMuonHZZ4lPreselection(mu)) {
            if( printDebug )cout << endl;
            continue;
          }
          if( printDebug )cout << " pass preselection : ";
          
          if (!PassMuonHZZ4lICHEP2012ID(mu,i,pfcandidateArr)) {
            if( printDebug )cout << endl;
            continue;
          } 
          if( printDebug )cout << " pass ID : ";

          //--------------------------------------------------------------------------------------
          //Do Isolation here only if we're not doing FSR, otherwise isolation comes afterwards
          //--------------------------------------------------------------------------------------
          if (!doFSR) {
            if (!PassMuonHZZ4lICHEP2012Iso(mu, i, pfcandidateArr,rhoMuonIso,MuonEAEra,photonsToVeto, printDebug)) {
              if( printDebug )cout << endl;
              continue;
            }
            if( printDebug )cout << " pass Iso : ";
          }
          if( printDebug )cout << endl;
          
          leptonType.push_back(13);
          leptonIndex.push_back(i);
      
        }
    
        //
        if( printDebug ) { cout << "\tnElectron: " << electronArr->GetEntries() << endl; }
        // --------------------------------------------------------------------------------
        for(uint i=0; i<uint(electronArr->GetEntries()); i++) 
        {
          const higgsana::TElectron *ele = (higgsana::TElectron*)((*electronArr)[i]);

          if( printDebug ) { 
            cout << "ele:: " << ele->pt << " " << ele->eta << " " << ele->phi << " : " ;
          }

          //Clean ID'ed and Preselected muons from electrons if they fall within dR < 0.05
          Bool_t overlapsWithMuon = kFALSE;
          for(UInt_t j=0; j<leptonIndex.size(); j++) {
            if (leptonType[j] != 13) continue;
            const higgsana::TMuon *tmpmu = (higgsana::TMuon*)((*muonArr)[leptonIndex[j]]);      
            
            if (deltaR(tmpmu->eta,tmpmu->phi, ele->eta,ele->phi) < 0.05) {
              overlapsWithMuon = kTRUE;
              break;
            }
          }
          if (overlapsWithMuon) {
            if( printDebug ) cout << " : Overlaps with Muon : ";
            if( printDebug ) cout << endl;              
            continue;
          }

          if (!PassEleHZZ4lPreselection(ele)) {
            if( printDebug )cout << endl;
            continue;
          }
          if( printDebug )cout << " pass preselection : ";
          
          if (!PassEleHZZ4lICHEP2012ID(ele, eleIDMVA, printDebug)) {
            if( printDebug )cout << endl;
            continue;
          } 
          if( printDebug )cout << " pass ID : ";


          //--------------------------------------------------------------------------------------
          //Do Isolation here only if we're not doing FSR, otherwise isolation comes afterwards
          //--------------------------------------------------------------------------------------
          if (!doFSR) {
            if (!PassEleHZZ4lICHEP2012Iso(ele,pfcandidateArr,rhoEleIso,EleEAEra,photonsToVeto, printDebug)) {
              if( printDebug )cout << endl;
              continue;
            }
            if( printDebug )cout << " pass Iso : ";
          }
          if( printDebug )cout << endl;

          leptonType.push_back(11);
          leptonIndex.push_back(i);
        }


        //********************************************************
        // Sort Lepton Vector by pT
        //********************************************************
        Int_t tempLeptonType;
        Int_t tempLeptonIndex;
        for (uint l=0; l<leptonType.size(); l++) {
          for (uint k=0; k < leptonType.size() - 1; k++) {
            Double_t tmpPt_kPlusOne = 0;
            Double_t tmpPt_k = 0;
            if (leptonType[k] == 11) {
              const higgsana::TElectron *tmpele = (higgsana::TElectron*)((*electronArr)[leptonIndex[k]]);      
              tmpPt_k = tmpele->pt;
            } else {
              const higgsana::TMuon *tmpmu = (higgsana::TMuon*)((*muonArr)[leptonIndex[k]]);      
              tmpPt_k = tmpmu->pt;
            }
            if (leptonType[k+1] == 11) {
              const higgsana::TElectron *tmpele = (higgsana::TElectron*)((*electronArr)[leptonIndex[k+1]]);      
              tmpPt_kPlusOne = tmpele->pt;
            } else {
              const higgsana::TMuon *tmpmu = (higgsana::TMuon*)((*muonArr)[leptonIndex[k+1]]);
              tmpPt_kPlusOne = tmpmu->pt;
            }

            if (tmpPt_kPlusOne > tmpPt_k) {
              tempLeptonType = leptonType[k];
              tempLeptonIndex = leptonIndex[k];
              
              leptonType[k] = leptonType[k+1];
              leptonIndex[k] = leptonIndex[k+1];
          
              leptonType[k+1] = tempLeptonType;
              leptonIndex[k+1] = tempLeptonIndex;
            }
          }
        }
        
        //********************************************************
        // Make collection of lepton four vectors
        //********************************************************
        vector<TLorentzVector> leptonFourVector;
        for (uint l=0; l<leptonType.size(); l++) {          
          TLorentzVector v;
          if (leptonType[l] == 11) {
            const higgsana::TElectron *tmpele = (higgsana::TElectron*)((*electronArr)[leptonIndex[l]]);  
            v.SetPtEtaPhiM( tmpele->pt, tmpele->eta, tmpele->phi, ELECTRONMASS);
          } else {
            const higgsana::TMuon *tmpmu = (higgsana::TMuon*)((*muonArr)[leptonIndex[l]]);      
            v.SetPtEtaPhiM( tmpmu->pt, tmpmu->eta, tmpmu->phi, MUONMASS);
          }
          leptonFourVector.push_back(v);
        }

        //********************************************************
        // Dump Stuff
        //********************************************************
        if(printDebug) cout << "CHECK Before FSR Stuff\n";
        int nmu=0, nele=0;
        for( uint i=0; i<leptonType.size(); i++ ) {

          Double_t pt, eta, phi;
          if (leptonType[i] == 11) {
            const higgsana::TElectron *tmpele = (higgsana::TElectron*)((*electronArr)[leptonIndex[i]]);      
            pt = tmpele->pt;
            eta = tmpele->eta;
            phi = tmpele->phi;
          } else {
            const higgsana::TMuon *tmpmu = (higgsana::TMuon*)((*muonArr)[leptonIndex[i]]);      
            pt = tmpmu->pt;
            eta = tmpmu->eta;
            phi = tmpmu->phi;
          }

          if(printDebug) { 
            cout << "lepvec :: evt: " << info->evtNum
                 << "\tindex: " << i 
                 << "\ttype: " << leptonType[i] 
                 << "\tpt: " << pt
                 << "\teta: " << eta
                 << "\tphi: " << phi;
            cout << endl;
          }
          if( leptonType[i] == 11 ) nele++;
          else nmu++;
        }
        if( printDebug ) { 
          cout << "postsel nlep: " << leptonType.size()
               << "\tnmuon: " << nmu
               << "\tnelectron: " << nele
               << endl;
        }

        if( printDebug && PassSelectionStages[0] && PassSelectionStages[1] && PassSelectionStages[2] && leptonType.size() >= 4 ) { 
          cout << "BEFORE Z Pass 4L: " << info->evtNum << endl;
        }


        //********************************************************
        // Reco Lepton Information
        //********************************************************
        vector<Double_t> selectedLeptonPt;
        vector<Double_t> selectedLeptonEta;
        vector<Double_t> selectedLeptonPhi;
        vector<Int_t>    selectedLeptonCharge;


        //********************************************************
        // Step 4: Z candidate preselection
        //********************************************************
        std::vector<std::pair<int,int> > ZCandidateLeptonTypePairs;
        std::vector<std::pair<uint,uint> > ZCandidateLeptonIndexPairs;
        std::vector<std::pair<TLorentzVector,TLorentzVector> > ZCandidateLeptonFourVectorPairs;

        for(uint i = 0; i < leptonType.size(); ++i) {
          for(uint j = i+1; j < leptonType.size(); ++j) {
            
            //*********************************
            //Select only same flavor pairs
            //*********************************
            if( leptonType[i] != leptonType[j] )      continue;

            Int_t leptonCharge_i = 0;
            Int_t leptonCharge_j = 0;
            TLorentzVector leptonFourVector_i;
            TLorentzVector leptonFourVector_j;
            if( leptonType[i] == 11) {
              const higgsana::TElectron *ele1 = (higgsana::TElectron*)((*electronArr)[leptonIndex[i]]);      
              leptonCharge_i = ele1->q;
              leptonFourVector_i.SetPtEtaPhiM( ele1->pt, ele1->eta, ele1->phi, ELECTRONMASS);

              const higgsana::TElectron *ele2 = (higgsana::TElectron*)((*electronArr)[leptonIndex[j]]);      
              leptonCharge_j = ele2->q;
              leptonFourVector_j.SetPtEtaPhiM( ele2->pt, ele2->eta, ele2->phi, ELECTRONMASS);
            } else {
              const higgsana::TMuon *mu1 = (higgsana::TMuon*)((*muonArr)[leptonIndex[i]]);      
              leptonCharge_i = mu1->q;
              leptonFourVector_i.SetPtEtaPhiM( mu1->pt, mu1->eta, mu1->phi, MUONMASS);

              const higgsana::TMuon *mu2 = (higgsana::TMuon*)((*muonArr)[leptonIndex[j]]);      
              leptonCharge_j = mu2->q;
              leptonFourVector_j.SetPtEtaPhiM( mu2->pt, mu2->eta, mu2->phi, MUONMASS);
            }

            if (printDebug) cout << "dilepton pair: " << i << " " << j << endl;

            //*********************************
            //Select only opposite charge pairs
            //*********************************
            if( leptonCharge_i == leptonCharge_j ) continue;

            TLorentzVector ZFourVector = (leptonFourVector_i + leptonFourVector_j);

            vector<TLorentzVector> lepvec_i = leptonFourVector;
            vector<TLorentzVector> lepvec_j = leptonFourVector;
            vector<Int_t> leptonType_i = leptonType;
            vector<Int_t> leptonType_j = leptonType;


            //initialize FSR Recovery status
            vector<Bool_t> FSRRecoveryAttempted_i;
            vector<Bool_t> FSRRecoveryAttempted_j;
            for(uint q = 0; q < lepvec_i.size(); ++q) {
              FSRRecoveryAttempted_i.push_back(kFALSE);
              FSRRecoveryAttempted_j.push_back(kFALSE);
            }

            Bool_t passIsolation_i = kFALSE;
            Bool_t passIsolation_j = kFALSE;
            if (printDebug) cout << "Leptons i : " << leptonFourVector_i.Pt() << " " << leptonFourVector_i.Eta() << " " << leptonFourVector_i.Phi() << endl;
            if (printDebug) cout << "Leptons j : " << leptonFourVector_j.Pt() << " " << leptonFourVector_j.Eta() << " " << leptonFourVector_j.Phi() << endl;
            if (printDebug) cout << "Z: " << ZFourVector.Pt() << " " << ZFourVector.Eta() << " " << ZFourVector.Phi() << endl;
            if (printDebug) cout << "3: " << i << " " << j << endl;
            if( doFSR ) { 
              if (printDebug) cout << endl;
              if (printDebug) cout << "----------------> FSR ("<<i<<","<<j<<") <----------------------" << endl;
              photonsToVeto.clear();
              float old_pt_i = leptonFourVector_i.Pt();
              float old_pt_j = leptonFourVector_j.Pt();
              float old_M  =  ZFourVector.M(); 	  

              if (printDebug) cout << "i: " << i << endl;
              if( leptonType[i] == 13 ) {
                const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[leptonIndex[i]]);      
                higgsana::TMuon * newmu = const_cast<higgsana::TMuon *>(mu);
                if (printDebug) cout << "try FSR Recovery TypeI: muon : " << i << " (originalindex " << leptonIndex[i] << " : "
                     << mu->pt << " " << mu->eta << " " << mu->phi << endl;
                if( FSRRecovery_TypeI( newmu, leptonIndex[i], i, FSRRecoveryAttempted_i, leptonType_i, lepvec_i, 
                                       pfcandidateArr, &ZFourVector, photonsToVeto, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEI :: oldpt: " << old_pt_i 
                                      << "\tnewpt: " << lepvec_i[i].Pt() 
                                      << "\tindex: " << i 
                                      << endl;
                  //lepvec[i].fsrRecoveryAttempted=true;
                }
                if (printDebug) cout << "try FSR Recovery TypeII: muon : " << mu->pt << " " << mu->eta << " " << mu->phi << endl;
                if( recover_typeII_Photon( newmu, i, FSRRecoveryAttempted_i, lepvec_i, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEII :: oldpt: " << old_pt_i 
                                      << "\tnewpt: " << lepvec_i[i].Pt() 
                                      << "\tindex: " << i 
                                      << endl;
                  //lepvec[i].fsrRecoveryAttempted=true;
                }
              } else { 
                const higgsana::TElectron *el = (higgsana::TElectron*)((*electronArr)[leptonIndex[i]]);      
                higgsana::TElectron* newel = const_cast<higgsana::TElectron*>(el);
                if (printDebug) cout << "try FSR Recovery TypeII: electron : " << el->pt << " " << el->eta << " " << el->phi << endl;
                if( FSRRecovery_TypeI( newel, leptonIndex[i], i, FSRRecoveryAttempted_i, leptonType_i, lepvec_i, 
                                       pfcandidateArr, &ZFourVector, photonsToVeto, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEI :: oldpt: " << old_pt_i 
                                      << "\tnewpt: " << lepvec_i[i].Pt() 
                                      << "\tindex: " << i 
                                      << endl;
                  //lepvec[i].fsrRecoveryAttempted=true;
                }
              }


              if (printDebug) cout << "j: " << j << endl;
              if( leptonType[j] == 13 ) {
                const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[leptonIndex[j]]);      
                higgsana::TMuon *newmu = const_cast<higgsana::TMuon*>(mu);
                if (printDebug) cout << "try FSR Recovery TypeI: muon : " << mu->pt << " " << mu->eta << " " << mu->phi << endl;
                if(	FSRRecovery_TypeI(newmu, leptonIndex[j], j, FSRRecoveryAttempted_j, leptonType_j, lepvec_j, 
                                          pfcandidateArr, &ZFourVector, photonsToVeto, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEI :: oldpt: " << old_pt_j 
                                      << "\tnewpt: " << lepvec_j[j].Pt() 
                                      << "\tindex: " << j 
                                      << endl;
                  //lepvec[j].fsrRecoveryAttempted=true;
                }
                if (printDebug) cout << "try FSR Recovery TypeII: muon : " << mu->pt << " " << mu->eta << " " << mu->phi << endl;
                if(	recover_typeII_Photon(newmu, j, FSRRecoveryAttempted_j, lepvec_j, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEII :: oldpt: " << old_pt_j 
                                      << "\tnewpt: " << lepvec_j[j].Pt() 
                                      << "\tindex: " << j 
                                      << endl;
                  //lepvec[j].fsrRecoveryAttempted=true;
                }
              } else { 
                const higgsana::TElectron *el = (higgsana::TElectron*)((*electronArr)[leptonIndex[j]]);      
                higgsana::TElectron* newel = const_cast<higgsana::TElectron*>(el);
                if (printDebug) cout << "try FSR Recovery TypeII: electron : " << el->pt << " " << el->eta << " " << el->phi << endl;
                if(	FSRRecovery_TypeI(newel, leptonIndex[j], j, FSRRecoveryAttempted_j, leptonType_j, lepvec_j, 
                                          pfcandidateArr, &ZFourVector, photonsToVeto, printDebug ) ) { 
                  if(printDebug) cout << "FSR TYPEI :: oldpt: " << old_pt_j 
                                      << "\tnewpt: " << lepvec_j[j].Pt() 
                                      << "\tindex: " << j 
                                      << endl;
                  // lepvec[j].fsrRecoveryAttempted=true;
                }
              }

              //
              // now fix isolation
              //

              if( leptonType[i] == 11 ) {
                const higgsana::TElectron *el = (higgsana::TElectron*)((*electronArr)[leptonIndex[i]]);      
                passIsolation_i = PassEleHZZ4lICHEP2012Iso(el,pfcandidateArr,rhoEleIso,EleEAEra,photonsToVeto, printDebug);	  

              } else { 
                const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[leptonIndex[i]]);      
                passIsolation_i = PassMuonHZZ4lICHEP2012Iso(mu,leptonIndex[i],pfcandidateArr,rhoMuonIso,MuonEAEra,photonsToVeto, printDebug);
              }

              if( leptonType[j] == 11 ) {
                const higgsana::TElectron *el = (higgsana::TElectron*)((*electronArr)[leptonIndex[j]]);      
                passIsolation_j = PassEleHZZ4lICHEP2012Iso(el,pfcandidateArr,rhoEleIso,EleEAEra,photonsToVeto, printDebug);	  
              } else { 
                const higgsana::TMuon *mu = (higgsana::TMuon*)((*muonArr)[leptonIndex[j]]);      
                passIsolation_j = PassMuonHZZ4lICHEP2012Iso(mu,leptonIndex[j],pfcandidateArr,rhoMuonIso,MuonEAEra,photonsToVeto, printDebug);
              }

              float new_M    =   (lepvec_i[i]+lepvec_j[j]).M();
              float new_pt_i = lepvec_i[i].Pt(); 
              float new_pt_j = lepvec_j[j].Pt(); 
              if( printDebug ) { 
                if (printDebug) cout << "\toldM: " << old_M << "\tnewM:" << new_M << endl;
                if (printDebug) cout << "\told_pt_i: " << old_pt_i << "\tnew_pt_i:" << new_pt_i << endl;
                if (printDebug) cout << "\told_pt_j: " << old_pt_j << "\tnew_pt_j:" << new_pt_j << endl;
                if (printDebug) cout << "isolated_i: " << passIsolation_i << " - isolated_j: " << passIsolation_j << endl;
              }
	  
            } // doFSR

            //Both leptons pass isolation
            if( !(passIsolation_i && passIsolation_j)) continue;    

            ZCandidateLeptonTypePairs.push_back(std::pair<int,int>(leptonType[i],leptonType[j]));
            ZCandidateLeptonIndexPairs.push_back(std::pair<int,int> (i,j));
            ZCandidateLeptonFourVectorPairs.push_back(std::pair<TLorentzVector,TLorentzVector>(lepvec_i[i],lepvec_j[j]));
            if( printDebug ) cout << "Z candidate ("<< i << "," << j << ")"
                                  << "\tmass: " << (lepvec_i[i]+lepvec_j[j]).M() << endl;


            //Save Lepton information
            selectedLeptonPt.push_back(lepvec_i[i].Pt());
            selectedLeptonEta.push_back(lepvec_i[i].Eta());
            selectedLeptonPhi.push_back(lepvec_i[i].Phi());
            selectedLeptonCharge.push_back(leptonCharge_i);
            selectedLeptonPt.push_back(lepvec_j[j].Pt());
            selectedLeptonEta.push_back(lepvec_j[j].Eta());
            selectedLeptonPhi.push_back(lepvec_j[j].Phi());
            selectedLeptonCharge.push_back(leptonCharge_j);

           }
        }


        if( ZCandidateLeptonFourVectorPairs.size() > 0 ) { 
          if (printDebug && PassSelectionStages[0] && PassSelectionStages[1] && PassSelectionStages[2]) cout << "Pass ZCandidate: " << info->evtNum << endl;

          PassSelectionStages[3] = kTRUE;
          PassSelectionStages_Z1e[3] = kTRUE;
          PassSelectionStages_Z1m[3] = kTRUE;
          PassSelectionStages_4e[3] = kTRUE;
          PassSelectionStages_4m[3] = kTRUE;
          PassSelectionStages_2e2m[3] = kTRUE;
          if( printDebug ) cout << "event has >0  Z candidates" << endl;
        } else {
          PassSelectionStages[3] = kFALSE;
        }


        //*******************************************
        // Print Selected lepton information
        //*******************************************
//         for( uint l=0; l<selectedLeptonPt.size(); l++ ) {
//           cout << "Selected Lepton " << l << " : " << selectedLeptonCharge[l] << " : " 
//                << selectedLeptonPt[l] << " " 
//                << selectedLeptonEta[l] << " " 
//                << selectedLeptonPhi[l] << " " 
//                << endl;
//         }
        

        //*******************************************
        // Match to gen level particles
        //*******************************************
        for( uint l=0; l<genpt.size(); ++l ) {
          Double_t minDR = 9999;
          Double_t matchedPt = 0;
          Double_t matchedEta = 0;
          Double_t matchedPhi = 0;
          Int_t matchedCharge = 0;
          Bool_t match = kFALSE;


          for( uint k=0; k<selectedLeptonPt.size(); ++k ) {
            Double_t tmpDR = deltaR(geneta[l],genphi[l],selectedLeptonEta[k],selectedLeptonPhi[k]);
            if (tmpDR > 0.5) continue;
            if (tmpDR < minDR) {
              minDR = tmpDR;
              matchedPt = selectedLeptonPt[k];
              matchedEta = selectedLeptonEta[k];
              matchedPhi = selectedLeptonPhi[k];
              matchedCharge = selectedLeptonCharge[k];
              match = kTRUE;
            }
          }


          if (match) {
            recopt[l] = matchedPt;
            recoeta[l] = matchedEta;
            recophi[l] = matchedPhi;
          }

          //Fill Information
          efficiencyMap.type = pdgid[l];
          efficiencyMap.genpt = genpt[l];
          efficiencyMap.geneta = geneta[l];
          efficiencyMap.genphi = genphi[l];
          efficiencyMap.recopt = recopt[l];
          efficiencyMap.recoeta = recoeta[l];
          efficiencyMap.recophi = recophi[l];
          efficiencyMap.recocharge = matchedCharge;
          efficiencyMap.pass = match;
          efficiencyMap.nvtx = info->nPV0;
          efficiencyMap.weight = 1.0;
          //*********************************************************
          //Fill 
          //*********************************************************
          fOutputTree->Fill();

        }


        //*********************************************************
        //save
        //*********************************************************
        //fOutputFile->Close();
        


      } //end loop over data     
    }
  }

  delete info;
  delete electronArr;
  delete muonArr;
  delete jetArr;


//   TFile *fOutputFile = new TFile(("HZZEfficiencyMap"+label+".root").c_str(), "RECREATE");
//   fOutputFile->WriteTObject(fOutputTree, fOutputTree->GetName(), "WriteDelete");
  fOutputFile->cd();
  fOutputFile->Write();
  fOutputFile->Close();
  delete fOutputFile;

   
  gBenchmark->Show("WWTemplate");       
} 



