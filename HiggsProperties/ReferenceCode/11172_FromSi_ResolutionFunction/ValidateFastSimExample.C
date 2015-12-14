// root -l HiggsAna/HZZ4l/HLL/ValidateFastSimExample.C+'("HZZEventNtuple_ZZ_0000.root","HZZEventNtuple_FastSim_ZZ_0000.root","ZZ")'

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
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"

#include "HiggsAna/HZZ4l/interface/HZZEventTree.h"
#include "HiggsAna/Utils/CommonDefs.hh"

#include "TLorentzVector.h"

#endif


//*************************************************************************************************
//Main Function
//*************************************************************************************************
void ValidateFastSimExample(string fullsimFilename, string fastsimFilename,
                           const string Label = "ZZ") {

  string label = Label;
  if (Label != "") label = "_" + Label;

  //*****************************************************************************************
  // Load Input
  //*****************************************************************************************
  HZZEventTree fullsimHZZEventTree;
  fullsimHZZEventTree.LoadTree(fullsimFilename.c_str());
  fullsimHZZEventTree.InitTree();
  HZZEventTree fastsimHZZEventTree;
  fastsimHZZEventTree.LoadTree(fastsimFilename.c_str());
  fastsimHZZEventTree.InitTree();
  cout << "Events in the ntuple: " << fastsimHZZEventTree.tree_->GetEntries() << endl;

  //*************************************************************************************************
  //Histograms
  //*************************************************************************************************
  TH1::AddDirectory(kFALSE);
  TH1F *histZ1Mass_ee_fullsim = new TH1F( "histZ1Mass_ee_fullsim", ";Z1 Mass [GeV/c^{2}]; Number of Events", 100, 0,200);
  TH1F *histZ1Mass_ee_fastsim = new TH1F( "histZ1Mass_ee_fastsim", ";Z1 Mass [GeV/c^{2}]; Number of Events", 100, 0,200);
  TH1F *histZ1Mass_mm_fullsim = new TH1F( "histZ1Mass_mm_fullsim", ";Z1 Mass [GeV/c^{2}]; Number of Events", 100, 0,200);
  TH1F *histZ1Mass_mm_fastsim = new TH1F( "histZ1Mass_mm_fastsim", ";Z1 Mass [GeV/c^{2}]; Number of Events", 100, 0,200);

 
  //*****************************************************************************************
  // Loop over fullsim events
  //*****************************************************************************************
  for(UInt_t ientry=0; ientry < fullsimHZZEventTree.tree_->GetEntries(); ientry++) {       	
    fullsimHZZEventTree.tree_->GetEntry(ientry);
    if (ientry % 10000 == 0) cout << "Event " << ientry << endl;

    //how to get lepton four momenta
    TLorentzVector lepton1FourVector;
    lepton1FourVector.SetPtEtaPhiM( fullsimHZZEventTree.fLep1Pt, fullsimHZZEventTree.fLep1Eta, fullsimHZZEventTree.fLep1Phi, ELECTRONMASS);

    //fill events passing selection
    if (fullsimHZZEventTree.fPassFullSelection) {
      if (abs(fullsimHZZEventTree.fLep1Type) == 11) {
        histZ1Mass_ee_fullsim->Fill(fullsimHZZEventTree.fZ1Mass, fullsimHZZEventTree.fWeight);
      } else {
        histZ1Mass_mm_fullsim->Fill(fullsimHZZEventTree.fZ1Mass, fullsimHZZEventTree.fWeight);
      }
    }
  }

  //*****************************************************************************************
  // Loop over fastsim events
  //*****************************************************************************************
  for(UInt_t ientry=0; ientry < fastsimHZZEventTree.tree_->GetEntries(); ientry++) {       	
    fastsimHZZEventTree.tree_->GetEntry(ientry);
    if (ientry % 10000 == 0) cout << "Event " << ientry << endl;

    //how to get lepton four momenta
    TLorentzVector lepton1FourVector;
    lepton1FourVector.SetPtEtaPhiM( fastsimHZZEventTree.fLep1Pt, fastsimHZZEventTree.fLep1Eta, fastsimHZZEventTree.fLep1Phi, ELECTRONMASS);

    //fill events passing selection
    if (fastsimHZZEventTree.fPassFullSelection) {
      if (abs(fastsimHZZEventTree.fLep1Type) == 11) {
        histZ1Mass_ee_fastsim->Fill(fastsimHZZEventTree.fZ1Mass, fastsimHZZEventTree.fWeight);
      } else {
        histZ1Mass_mm_fastsim->Fill(fastsimHZZEventTree.fZ1Mass, fastsimHZZEventTree.fWeight);
      }
    }

  }


  //*****************************************************************************************
  // Plot
  //*****************************************************************************************
  TCanvas *cv = 0;
  TLegend *legend = 0;

  cv = new TCanvas("cv","cv", 800,600);
  legend = new TLegend(0.54,0.14,0.94,0.44);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(histZ1Mass_ee_fullsim,"FullSim", "LP");
  legend->AddEntry(histZ1Mass_ee_fastsim,"FastSim", "LP");


  histZ1Mass_ee_fullsim->SetLineColor(kRed);
  histZ1Mass_ee_fullsim->Draw("hist");
  histZ1Mass_ee_fastsim->SetLineColor(kBlue);
  histZ1Mass_ee_fastsim->Draw("same");
  legend->Draw();
  cv->SaveAs(("FastSimValidation_Z1Mass_ee" + label + ".gif").c_str());


  cv = new TCanvas("cv","cv", 800,600);
  legend = new TLegend(0.54,0.14,0.94,0.44);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(histZ1Mass_mm_fullsim,"FullSim", "LP");
  legend->AddEntry(histZ1Mass_mm_fastsim,"FastSim", "LP");


  histZ1Mass_mm_fullsim->SetLineColor(kRed);
  histZ1Mass_mm_fullsim->Draw("hist");
  histZ1Mass_mm_fastsim->SetLineColor(kBlue);
  histZ1Mass_mm_fastsim->Draw("same");
  legend->Draw();
  cv->SaveAs(("FastSimValidation_Z1Mass_mm" + label + ".gif").c_str());



}
