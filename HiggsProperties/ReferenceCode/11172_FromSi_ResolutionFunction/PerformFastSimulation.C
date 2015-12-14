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
void PerformFastSimulation(string inputfilename, string outputfilename,
                           const string Label = "ZZ", Int_t Option = 0) {

  string label = Label;
  if (Label != "") label = "_" + Label;

  //*****************************************************************************************
  // Load LeptonResponseFile
  //*****************************************************************************************
  TFile *LeptonResponseFile = 0;
  if (Option == 0) {
    LeptonResponseFile = new TFile("HiggsAna/HZZ4l/HLL/LeptonResolutionData/PtResolution_ZZ.root","READ");
  } else if (Option == 1) {
    LeptonResponseFile = new TFile("HiggsAna/HZZ4l/HLL/LeptonResolutionData/PtResolution_Hist_ZZ.root","READ");
  }
  assert(LeptonResponseFile);
  Bool_t validateFile = kTRUE;
  if (Option == 0) {
    validateFile = ValidateLeptonResolutionMap(LeptonResponseFile, "Electrons", Option) && ValidateLeptonResolutionMap(LeptonResponseFile, "Muons", Option);
  }
  if (Option == 1) {
    validateFile = ValidateLeptonResolutionMap(LeptonResponseFile, "Electrons", Option) && ValidateLeptonResolutionMap(LeptonResponseFile, "Muons", Option);
  }
  assert(validateFile);



  //*****************************************************************************************
  // Load Input
  //*****************************************************************************************
  HZZEventTree hzzEventTree;
  hzzEventTree.LoadTree(inputfilename.c_str());
  hzzEventTree.InitTree();
  cout << "Events in the ntuple: " << hzzEventTree.tree_->GetEntries() << endl;

  //*************************************************************************************************
  //Output tree
  //*************************************************************************************************
  cout << "Output File : " << outputfilename << endl;
  TFile *outputFile = new TFile(outputfilename.c_str(), "RECREATE");
  outputFile->cd();
  TTree *outputTree = hzzEventTree.tree_->CloneTree(0);

  //turn off roofit info messagers
  RooMsgService::instance().setStreamStatus(1,0);
 
  //*****************************************************************************************
  // Event Loop
  //*****************************************************************************************
  for(UInt_t ientry=0; ientry < hzzEventTree.tree_->GetEntries(); ientry++) {       	
    hzzEventTree.tree_->GetEntry(ientry);
    if (ientry % 10000 == 0) cout << "Event " << ientry << endl;

    Double_t eventWeight = 1;


    vector<TLorentzVector> leptonFourVector;
    vector<int> leptonType;


    //***************************************************************************************
    //Simulate Lepton Response
    //***************************************************************************************
    Double_t Lep1Efficiency = 1.0;
    Double_t Lep1SimulatedPt = -1;
    TLorentzVector v1;
    if (hzzEventTree.fGenLep1Pt > 0) {
      if (abs(hzzEventTree.fGenLep1Type) == 11) {
        Lep1Efficiency = GetElectronEfficiencyPtEtaPhi(hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta), hzzEventTree.fGenLep1Phi);
        if (Option==0) {
          Lep1SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta));
        } else if (Option == 1) {
          Lep1SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v1.SetPtEtaPhiM( Lep1SimulatedPt, hzzEventTree.fGenLep1Eta, hzzEventTree.fGenLep1Phi, ELECTRONMASS);
      } else {
        Lep1Efficiency = GetMuonEfficiencyPtEtaPhi(hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta), hzzEventTree.fGenLep1Phi);
        if (Option==0) {
          Lep1SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Muons", hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta));
        } else if (Option == 1) {
          Lep1SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Muons", hzzEventTree.fGenLep1Pt, fabs(hzzEventTree.fGenLep1Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v1.SetPtEtaPhiM( Lep1SimulatedPt, hzzEventTree.fGenLep1Eta, hzzEventTree.fGenLep1Phi, MUONMASS);
      }
      leptonFourVector.push_back(v1);
      leptonType.push_back(hzzEventTree.fGenLep1Type);
    }


    Double_t Lep2Efficiency = 1.0;
    Double_t Lep2SimulatedPt = -1;
    TLorentzVector v2;
    if (hzzEventTree.fGenLep2Pt > 0) {
      if (abs(hzzEventTree.fGenLep2Type) == 11) {
        Lep2Efficiency = GetElectronEfficiencyPtEtaPhi(hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta), hzzEventTree.fGenLep2Phi);
        if (Option==0) {
          Lep2SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta));
        } else if (Option == 1) {
          Lep2SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v2.SetPtEtaPhiM( Lep2SimulatedPt, hzzEventTree.fGenLep2Eta, hzzEventTree.fGenLep2Phi, ELECTRONMASS);
      } else {
        Lep2Efficiency = GetMuonEfficiencyPtEtaPhi(hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta), hzzEventTree.fGenLep2Phi);
        if (Option==0) {
          Lep2SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Muons", hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta));
        } else if (Option == 1) {
          Lep2SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Muons", hzzEventTree.fGenLep2Pt, fabs(hzzEventTree.fGenLep2Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v2.SetPtEtaPhiM( Lep2SimulatedPt, hzzEventTree.fGenLep2Eta, hzzEventTree.fGenLep2Phi, MUONMASS);
      }
      leptonFourVector.push_back(v2);
      leptonType.push_back(hzzEventTree.fGenLep2Type);
    }

    Double_t Lep3Efficiency = 1.0;
    Double_t Lep3SimulatedPt = -1;
    TLorentzVector v3;
    if (hzzEventTree.fGenLep3Pt > 0) {
      if (abs(hzzEventTree.fGenLep3Type) == 11) {
        Lep3Efficiency = GetElectronEfficiencyPtEtaPhi(hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta), hzzEventTree.fGenLep3Phi);
        if (Option==0) {
          Lep3SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta));
        } else if (Option == 1) {
          Lep3SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v3.SetPtEtaPhiM( Lep3SimulatedPt, hzzEventTree.fGenLep3Eta, hzzEventTree.fGenLep3Phi, ELECTRONMASS);
      } else {
        Lep3Efficiency = GetMuonEfficiencyPtEtaPhi(hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta), hzzEventTree.fGenLep3Phi);
        if (Option==0) {
          Lep3SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Muons", hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta));
        } else if (Option == 1) {
          Lep3SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Muons", hzzEventTree.fGenLep3Pt, fabs(hzzEventTree.fGenLep3Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v3.SetPtEtaPhiM( Lep3SimulatedPt, hzzEventTree.fGenLep3Eta, hzzEventTree.fGenLep3Phi, MUONMASS);
      }
      leptonFourVector.push_back(v3);
      leptonType.push_back(hzzEventTree.fGenLep3Type);
    }

    Double_t Lep4Efficiency = 1.0;
    Double_t Lep4SimulatedPt = -1;
    TLorentzVector v4;
    if (hzzEventTree.fGenLep4Pt > 0) {
      if (abs(hzzEventTree.fGenLep4Type) == 11) {
        Lep4Efficiency = GetElectronEfficiencyPtEtaPhi(hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta), hzzEventTree.fGenLep4Phi);
        if (Option==0) {
          Lep4SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta));
        } else if (Option == 1) {
          Lep4SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Electrons", hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v4.SetPtEtaPhiM( Lep4SimulatedPt, hzzEventTree.fGenLep4Eta, hzzEventTree.fGenLep4Phi, ELECTRONMASS);
      } else {
        Lep4Efficiency = GetMuonEfficiencyPtEtaPhi(hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta), hzzEventTree.fGenLep4Phi);
        if (Option==0) {
          Lep4SimulatedPt = GenerateLeptonPtFromModel(LeptonResponseFile, "Muons", hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta));
        } else if (Option == 1) {
          Lep4SimulatedPt = GenerateLeptonPtFromHist(LeptonResponseFile, "Muons", hzzEventTree.fGenLep4Pt, fabs(hzzEventTree.fGenLep4Eta));
        } else {
          cout << "option not recognized\n"; return;
        }
        v4.SetPtEtaPhiM( Lep4SimulatedPt, hzzEventTree.fGenLep4Eta, hzzEventTree.fGenLep4Phi, MUONMASS);
      }
      leptonFourVector.push_back(v4);
      leptonType.push_back(hzzEventTree.fGenLep4Type);
    }

    
//Debug

//     cout <<leptonType.size() << " : " <<  leptonFourVector.size() << endl;

//     for( uint i=0; i<leptonFourVector.size(); i++ ) {
//       cout << "lepton " << i << " : " << leptonFourVector[i].Pt() << " " << leptonFourVector[i].Eta() << " " << leptonFourVector[i].Phi() << " " << endl;
//     }
//     cout << endl;
    

    //***************************************************************************************
    //Emulate Event Selection
    //***************************************************************************************
    Bool_t passEventSelection = kTRUE;


    //select Z1
    Int_t Z1Lepton1Index = -1;
    Int_t Z1Lepton2Index = -1;
    TLorentzVector selectedZ1FourVector;
    float selectedZ1Mass = 9999.;

    for( uint i=0; i<leptonFourVector.size(); i++ ) {
      for( uint j=i+1; j<leptonFourVector.size(); j++ ) {

        //choose same flavor, opp charge pairs
        if (abs(leptonType[i]) != abs(leptonType[j])) continue;
        if ( leptonType[i]*leptonType[j] > 0 ) continue;

        TLorentzVector tmpZ1vec = (leptonFourVector[i] + leptonFourVector[j]);
        if( fabs(tmpZ1vec.M()-ZMASS) < fabs(selectedZ1Mass-ZMASS) ) {
          selectedZ1Mass=tmpZ1vec.M();
          selectedZ1FourVector = tmpZ1vec;
          if (leptonFourVector[i].Pt() > leptonFourVector[j].Pt()) {
            Z1Lepton1Index = i;
            Z1Lepton2Index = j;
          } else {
            Z1Lepton1Index = j;
            Z1Lepton2Index = i;
          }
        }
      }
    }

    //Z1 mass cut
    passEventSelection = passEventSelection && (selectedZ1FourVector.M() > 40 && selectedZ1FourVector.M() < 120);

    //select Z2
    Int_t Z2Lepton1Index = -1;
    Int_t Z2Lepton2Index = -1;
    TLorentzVector selectedZ2FourVector;
    float selectedZ2Pt = -1.;
    for( uint i=0; i<leptonFourVector.size(); i++ ) {
      for( uint j=i+1; j<leptonFourVector.size(); j++ ) {
        
        //choose same flavor, opp charge pairs
        if (abs(leptonType[i]) != abs(leptonType[j])) continue;
        if ( leptonType[i]*leptonType[j] > 0 ) continue;

        //cannot be one of the z1 leptons
        if (int(i) == Z1Lepton1Index) continue;
        if (int(i) == Z1Lepton2Index) continue;
        if (int(j) == Z1Lepton1Index) continue;
        if (int(j) == Z1Lepton2Index) continue;

        TLorentzVector tmpZ2vec = (leptonFourVector[i] + leptonFourVector[j]);
        if( tmpZ2vec.Pt() > selectedZ2Pt ) {

          selectedZ2Pt = tmpZ2vec.Pt();
          selectedZ2FourVector = tmpZ2vec;

          if (leptonFourVector[i].Pt() > leptonFourVector[j].Pt()) {
            Z2Lepton1Index = i;
            Z2Lepton2Index = j;
          } else {
            Z2Lepton1Index = j;
            Z2Lepton2Index = i;
          }
        }
      }
    }


    //Z2 mass cut
    passEventSelection = passEventSelection && (selectedZ2FourVector.M() > 4 && selectedZ2FourVector.M() < 120);
  
    //lepton pt cuts
    Bool_t passLeptonPt2010Cut = kFALSE;
    Int_t NLepAbove20 = 0;
    Int_t NLepAbove10 = 0;
    for( uint i=0; i<leptonFourVector.size(); i++ ) {
      if (leptonFourVector[i].Pt() > 20) NLepAbove20++;
      if (leptonFourVector[i].Pt() > 10) NLepAbove10++;
    }
    if (NLepAbove20 >= 1 && NLepAbove10 >= 2) passLeptonPt2010Cut = kTRUE;
    passEventSelection = passEventSelection && passLeptonPt2010Cut;

    //resonance killing 4/4
    Bool_t passResonanceKillingCut = kTRUE;
    for( uint i=0; i<leptonFourVector.size(); i++ ) {
      for( uint j=i+1; j<leptonFourVector.size(); j++ ) {
        
        //don't do this for same sign pairs
        if (leptonType[i]*leptonType[j] > 0) continue;

        if ( (leptonFourVector[i] + leptonFourVector[j]).M() < 4.0) passResonanceKillingCut = kFALSE;
      }
    }
    passEventSelection = passEventSelection && passResonanceKillingCut;

    //m_4l cut, mz2 cut    
    passEventSelection = passEventSelection && ( (selectedZ1FourVector+selectedZ2FourVector).M() > 100 );
    passEventSelection = passEventSelection && ( selectedZ2FourVector.M() > 12 );


    //***************************************************************************************
    //Fill output
    //***************************************************************************************
    if (Z1Lepton1Index >= 0) {

      hzzEventTree.fLep1Pt = leptonFourVector[Z1Lepton1Index].Pt();
      hzzEventTree.fLep1Type = leptonType[Z1Lepton1Index];
      hzzEventTree.fLep1Eta = leptonFourVector[Z1Lepton1Index].Eta();
      hzzEventTree.fLep1Phi = leptonFourVector[Z1Lepton1Index].Phi();

//       cout << leptonFourVector[Z1Lepton1Index].Pt() << " " << leptonFourVector[Z1Lepton1Index].Eta() << " " << leptonFourVector[Z1Lepton1Index].Phi() << endl;
//       cout << leptonFourVector[Z1Lepton2Index].Pt() << " " << leptonFourVector[Z1Lepton2Index].Eta() << " " << leptonFourVector[Z1Lepton2Index].Phi() << endl;
//       cout << selectedZ1FourVector.M() << endl;
//       cout << endl;

      hzzEventTree.fLep2Pt = leptonFourVector[Z1Lepton2Index].Pt();
      hzzEventTree.fLep2Type = leptonType[Z1Lepton2Index];
      hzzEventTree.fLep2Eta = leptonFourVector[Z1Lepton2Index].Eta();
      hzzEventTree.fLep2Phi = leptonFourVector[Z1Lepton2Index].Phi();
      hzzEventTree.fZ1Mass = selectedZ1FourVector.M();
      hzzEventTree.fZ1Pt = selectedZ1FourVector.Pt();          
      hzzEventTree.fZ1Eta = selectedZ1FourVector.Eta();
      hzzEventTree.fZ1Rapidity = selectedZ1FourVector.Rapidity();
    } else {
      hzzEventTree.fLep1Type = 0;
      hzzEventTree.fLep1Pt = 0;
      hzzEventTree.fLep1Eta = 0;
      hzzEventTree.fLep1Phi = 0;
      hzzEventTree.fLep2Type = 0;
      hzzEventTree.fLep2Pt = 0;
      hzzEventTree.fLep2Eta = 0;
      hzzEventTree.fLep2Phi = 0;
      hzzEventTree.fZ1Mass = 0;
      hzzEventTree.fZ1Pt = 0;          
      hzzEventTree.fZ1Eta = 0;
      hzzEventTree.fZ1Rapidity = 0;
    }

    if (Z2Lepton1Index >= 0) {      
      hzzEventTree.fLep3Pt = leptonFourVector[Z2Lepton1Index].Pt();
      hzzEventTree.fLep3Type = leptonType[Z2Lepton1Index];
      hzzEventTree.fLep3Eta = leptonFourVector[Z2Lepton1Index].Eta();
      hzzEventTree.fLep3Phi = leptonFourVector[Z2Lepton1Index].Phi();
      hzzEventTree.fLep4Pt = leptonFourVector[Z2Lepton2Index].Pt();
      hzzEventTree.fLep4Type = leptonType[Z2Lepton2Index];
      hzzEventTree.fLep4Eta = leptonFourVector[Z2Lepton2Index].Eta();
      hzzEventTree.fLep4Phi = leptonFourVector[Z2Lepton2Index].Phi();
      hzzEventTree.fZ2Mass = selectedZ2FourVector.M();
      hzzEventTree.fZ2Pt = selectedZ2FourVector.Pt();          
      hzzEventTree.fZ2Eta = selectedZ2FourVector.Eta();
      hzzEventTree.fZ2Rapidity = selectedZ2FourVector.Rapidity();
    } else {
      hzzEventTree.fLep3Type = 0;
      hzzEventTree.fLep3Pt = 0;
      hzzEventTree.fLep3Eta = 0;
      hzzEventTree.fLep3Phi = 0;
      hzzEventTree.fLep4Type = 0;
      hzzEventTree.fLep4Pt = 0;
      hzzEventTree.fLep4Eta = 0;
      hzzEventTree.fLep4Phi = 0;
      hzzEventTree.fZ2Mass = 0;
      hzzEventTree.fZ2Pt = 0;          
      hzzEventTree.fZ2Eta = 0;
      hzzEventTree.fZ2Rapidity = 0;
    }

    if (Z1Lepton1Index >= 0 && Z2Lepton1Index >= 0) {      
      hzzEventTree.fFourLeptonPt = (selectedZ1FourVector+selectedZ2FourVector).Pt();
      hzzEventTree.fFourLeptonMass = (selectedZ1FourVector+selectedZ2FourVector).M();
      hzzEventTree.fFourLeptonRapidity = (selectedZ1FourVector+selectedZ2FourVector).Rapidity();
    }


    hzzEventTree.fWeight = hzzEventTree.fWeight*Lep1Efficiency;
    hzzEventTree.fPassFullSelection = passEventSelection;

    outputTree->Fill();


  } 

  outputFile->Write();
  outputFile->Close();
  delete outputFile;


}
