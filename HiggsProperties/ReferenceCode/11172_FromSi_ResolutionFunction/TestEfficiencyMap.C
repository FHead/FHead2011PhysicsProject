//root -l HiggsAna/HZZ4l/HLL/CreateEfficiencyMap.C+'("HZZEfficiencyMap_HZZ125.root","HZZ125"0)'


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
#include "HiggsAna/HZZ4l/HLL/LeptonResolutionData/ElectronEfficiencyMap.h"
#include "HiggsAna/HZZ4l/HLL/LeptonResolutionData/MuonEfficiencyMap.h"
#include "LeptonResponseMap.hh"

#endif



//=== MAIN MACRO =================================================================================================

void TestEfficiencyMap() 
{  

  cout << GetElectronEfficiencyPtEtaPhi(25.5, 0.3, 0.2) << endl;
  cout << GetMuonEfficiencyPtEta(25.5, 0.3) << endl;

  TFile *LeptonResponseFile = new TFile("HiggsAna/HZZ4l/HLL/LeptonResolutionData/PtResolution_ZZ.root","READ");
  assert(LeptonResponseFile);

  cout << "Test Electron: " << GenerateLeptonPtFromModel(LeptonResponseFile, "Electrons", 25.5, 0.3) << endl;
  cout << "Test Muon: " << GenerateLeptonPtFromHist(LeptonResponseFile, "Muons", 25.5, 0.3) << endl;

} 


