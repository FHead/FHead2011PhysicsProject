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
#include <TH2F.h>                   // 1D histograms
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
#include "HiggsAna/HZZ4l/interface/HZZEfficiencyMap.hh"

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
#include "HiggsAna/HZZ4l/HLL/RooDoubleSidedCBShape.hh"

#endif


//=== FUNCTION DECLARATIONS ======================================================================================

void initialize3DArray(double ***array, UInt_t NPtBins, UInt_t NEtaBins, UInt_t NPhiBins) {

  array = new double**[NPtBins+2];
  for (uint i=0; i < NPtBins+2; ++i) {
    array[i] = new double*[NEtaBins+2];
    for (uint j=0; j < NEtaBins+2; ++j) {
      array[i][j] = new double[NPhiBins+2];
      for (uint k=0; k < NPhiBins+2; ++k) {
        array[i][j][k] = 0;
      }      
    }
  }
}

void initialize3DArray(vector<vector<vector<double> > > &array, UInt_t NPtBins, UInt_t NEtaBins, UInt_t NPhiBins) {

  array.resize(NPtBins+2);
  for (uint i=0; i < NPtBins+2; ++i) {
    array[i].resize(NEtaBins+2);
    for (uint j=0; j < NEtaBins+2; ++j) {
      array[i][j].resize(NPhiBins+2);
      for (uint k=0; k < NPhiBins+2; ++k) {
        array[i][j][k] = 0;
      }
    }
  }
}

void initialize2DArray(vector<vector<double> > &array, UInt_t NPtBins, UInt_t NEtaBins) {

  array.resize(NPtBins+2);
  for (uint i=0; i < NPtBins+2; ++i) {
    array[i].resize(NEtaBins+2);
    for (uint j=0; j < NEtaBins+2; ++j) {
      array[i][j]= 0;
    }
  }
}
  
void initializeHistograms(vector<vector<TH1F*> > &hists, string name, UInt_t NPtBins, UInt_t NEtaBins, UInt_t nbins, Double_t xmin, Double_t xmax) {

  hists.resize(NPtBins+2);
  for (uint i=0; i < NPtBins+2; ++i) {
    hists[i].resize(NEtaBins+2);
    for (uint j=0; j < NEtaBins+2; ++j) {      
      hists[i][j]= new TH1F(Form("%s_PtBin%d_EtaBin%d",name.c_str(),i,j), "; (Reco Pt - Gen Pt)/Gen Pt; Number of Events", nbins, xmin, xmax);
    }
  }
}
  
UInt_t FindBin( double value, double bins[], UInt_t nbins) {

  UInt_t nbinboundaries = nbins+1;
  UInt_t bin = 0;
  for (uint i=0; i < nbinboundaries; ++i) {
    if (i < nbinboundaries-1) {
      if (value >= bins[i] && value < bins[i+1]) {
        bin = i+1;
        break;
      }
    } else if (i == nbinboundaries-1) {
      if (value >= bins[i]) {
        bin = nbinboundaries;
        break;
      }
    }    
  }
  return bin;
}
  
void computeEfficiencyPtEtaPhi(vector<vector<vector<double> > > &numerator, 
                       vector<vector<vector<double> > > &denominator,
                       vector<vector<vector<double> > > &eff
  ) {

  for (uint i=0; i < numerator.size(); ++i) {
    for (uint j=0; j < numerator[i].size(); ++j) {
      for (uint k=0; k < numerator[i][j].size(); ++k) {
        if (denominator[i][j][k] > 0) {         
          eff[i][j][k] = numerator[i][j][k] / denominator[i][j][k];        
        } else {
          eff[i][j][k] = 0;
        }
      }
    }
  }
}

void computeEfficiencyPtEta(vector<vector<double> > &numerator, 
                       vector<vector<double> > &denominator,
                       vector<vector<double> > &eff
  ) {

  for (uint i=0; i < numerator.size(); ++i) {
    for (uint j=0; j < numerator[i].size(); ++j) {
      if ( denominator[i][j] > 0) {
        eff[i][j] = numerator[i][j] / denominator[i][j];
      } else {
        eff[i][j] = 0;
      }
    }
  }
}


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

void FillLeptonResponseHists(const string filename, const string Label = "ZZ", Int_t Option = 0) 
{  
  gBenchmark->Start("HZZTemplate");
  string label = Label;
  if (Label != "") label = "_" + Label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //==============================================================================================================


//   //--------------------------------------------------------------------------------------------------------------
//   // Pileup Reweighting
//   //==============================================================================================================  
//   TFile *fPUFile = TFile::Open("/data/smurf/sixie/Pileup/weights/PileupReweighting.Fall11_To_Full2011.root");
//   TH1D *fhDPU = (TH1D*)(fPUFile->Get("puWeights"));
//   assert(fhDPU);
//   fhDPU->SetDirectory(0);
//   delete fPUFile;


  //********************************************************
  // Create Arrays to store the map
  //********************************************************
   const UInt_t NPtBins = 14;
   const UInt_t NEtaBins = 16;
   double ptBins[NPtBins+1] = { 5, 7, 8, 9, 10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 50};
   double etaBins[NEtaBins+1] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4442, 1.566, 1.8, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6};

   vector<vector<TH1F*> > PtResolution_PtEta_Electrons;
   vector<vector<TH1F*> > PtResolution_PtEta_Muons;

   initializeHistograms(PtResolution_PtEta_Electrons, "LeptonPtResolution_Electrons", NPtBins, NEtaBins, 100, -0.75, 0.75 );
   initializeHistograms(PtResolution_PtEta_Muons, "LeptonPtResolution_Muons", NPtBins, NEtaBins, 100, -0.25, 0.25);

   
  //--------------------------------------------------------------------------------------------------------------
  // Read efficiency map ntuple
  //==============================================================================================================  
  // Access samples and fill histograms
  TTree *eventTree=0;  
   
  // Data structures to store info from TTrees
  HZZEfficiencyMap *efficiencyMap = new HZZEfficiencyMap();

  //********************************************************
  // Get Tree
  //********************************************************
  cout << "Reading File " << filename << endl;
  eventTree = getTreeFromFile(filename.c_str(),"EfficiencyMap"); 

  TBranch *efficiencyMapBr;

  //*****************************************************************************************
  //Loop over tree
  //*****************************************************************************************
  // Set branch address to structures that will store the info  
  eventTree->SetBranchAddress("efficiencyMap",       &efficiencyMap);      
  efficiencyMapBr = eventTree->GetBranch("efficiencyMap");
  
  for(UInt_t ientry=0; ientry<eventTree->GetEntries(); ientry++) {       	
    efficiencyMapBr->GetEntry(ientry);
    if (ientry % 1000000 == 0) cout << "Event " << ientry << endl;
    
    //********************************************************
    //double mynpu = TMath::Min((double)info->nPUEvents,34.999);
    //Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
    //double npuWeight = fhDPU->GetBinContent(npuxbin);
    //********************************************************
    double weight = 1.0;

    Int_t tmpPtBin = FindBin( efficiencyMap->genpt , ptBins, NPtBins);
    Int_t tmpEtaBin = FindBin( fabs(efficiencyMap->geneta) , etaBins, NEtaBins);

    if (efficiencyMap->pass == kTRUE && efficiencyMap->recopt > -9999 
//         && efficiencyMap->type*efficiencyMap->recocharge > 0
      ) {

      if (abs(efficiencyMap->type) == 11) {
        PtResolution_PtEta_Electrons[tmpPtBin][tmpEtaBin]->Fill( (efficiencyMap->recopt - efficiencyMap->genpt)/efficiencyMap->genpt , weight);
      } 
      if (abs(efficiencyMap->type) == 13) {
        PtResolution_PtEta_Muons[tmpPtBin][tmpEtaBin]->Fill( (efficiencyMap->recopt - efficiencyMap->genpt)/efficiencyMap->genpt , weight);
      } 
    }
  } //end loop over data



  //********************************************************
  // Output file
  //******************************************************** 
  TFile *fileOutput = new TFile(("PtResolutionHist" + label + ".root").c_str(), "UPDATE");
  for (uint i=0; i < NPtBins+2; ++i) {
    for (uint j=0; j < NEtaBins+2; ++j) {
      fileOutput->WriteTObject(PtResolution_PtEta_Electrons[i][j], PtResolution_PtEta_Electrons[i][j]->GetName(), "WriteDelete");
      fileOutput->WriteTObject(PtResolution_PtEta_Muons[i][j], PtResolution_PtEta_Muons[i][j]->GetName(), "WriteDelete");
    }
  }
  fileOutput->Close();
  delete fileOutput;

  fileOutput = new TFile(("PtResolution" + label + ".root").c_str(), "UPDATE");
  for (uint i=0; i < NPtBins+2; ++i) {
    for (uint j=0; j < NEtaBins+2; ++j) {
      fileOutput->WriteTObject(PtResolution_PtEta_Electrons[i][j], PtResolution_PtEta_Electrons[i][j]->GetName(), "WriteDelete");
      fileOutput->WriteTObject(PtResolution_PtEta_Muons[i][j], PtResolution_PtEta_Muons[i][j]->GetName(), "WriteDelete");
    }
  }
  fileOutput->Close();
  delete fileOutput;

  return;

}


void FitLeptonResponseModels(const string Label = "ZZ", Int_t Option = 0) {

  string label = Label;
  if (Label != "") label = "_" + Label;
  TFile *fileInput = new TFile(("PtResolution" + label + ".root").c_str(), "UPDATE");

  //********************************************************
  // Bins
  //********************************************************
  const UInt_t NPtBins = 14;
  const UInt_t NEtaBins = 16;
  const UInt_t NPhiBins = 12;
  
  
  //********************************************************
  // Output
  //********************************************************
  TFile *fileOutput = new TFile(("PtResolutionModel" + label + ".root").c_str(), "UPDATE");
  
  TH2F* DoubleSidedCBShapeParamArray_mean = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_mean");
  TH2F* DoubleSidedCBShapeParamArray_sigma = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_sigma");
  TH2F* DoubleSidedCBShapeParamArray_alphaL = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_alphaL");
  TH2F* DoubleSidedCBShapeParamArray_nL = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_nL");
  TH2F* DoubleSidedCBShapeParamArray_alphaR = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_alphaR");
  TH2F* DoubleSidedCBShapeParamArray_nR = (TH2F*)fileOutput->Get("DoubleSidedCBShapeParamArray_nR");

  if (!DoubleSidedCBShapeParamArray_mean) DoubleSidedCBShapeParamArray_mean = new TH2F( "DoubleSidedCBShapeParamArray_mean", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);
  if (!DoubleSidedCBShapeParamArray_sigma) DoubleSidedCBShapeParamArray_sigma = new TH2F( "DoubleSidedCBShapeParamArray_sigma", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);
  if (!DoubleSidedCBShapeParamArray_alphaL) DoubleSidedCBShapeParamArray_alphaL = new TH2F( "DoubleSidedCBShapeParamArray_alphaL", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);
  if (!DoubleSidedCBShapeParamArray_nL) DoubleSidedCBShapeParamArray_nL = new TH2F( "DoubleSidedCBShapeParamArray_nL", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);
  if (!DoubleSidedCBShapeParamArray_alphaR) DoubleSidedCBShapeParamArray_alphaR = new TH2F( "DoubleSidedCBShapeParamArray_alphaR", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);
  if (!DoubleSidedCBShapeParamArray_nR) DoubleSidedCBShapeParamArray_nR = new TH2F( "DoubleSidedCBShapeParamArray_nR", "", NPtBins, 0, NPtBins, NEtaBins, 0, NEtaBins);

  for (uint i=0; i < NPtBins+2; ++i) {
    for (uint j=0; j < NEtaBins+2; ++j) {
      DoubleSidedCBShapeParamArray_mean->SetBinContent(i,j,1.0);
      DoubleSidedCBShapeParamArray_sigma->SetBinContent(i,j,1.0);
      DoubleSidedCBShapeParamArray_alphaL->SetBinContent(i,j,1.0);
      DoubleSidedCBShapeParamArray_nL->SetBinContent(i,j,1.0);
      DoubleSidedCBShapeParamArray_alphaR->SetBinContent(i,j,1.0);
      DoubleSidedCBShapeParamArray_nR->SetBinContent(i,j,1.0);
    }
  }



  //********************************************************
  // Fit for resolution function for electrons
  //******************************************************** 
  for (uint i=0; i < NPtBins+2; ++i) {
    for (uint j=0; j < NEtaBins+2; ++j) {

      if (!(
            (0==1)
            || (i==15 && j==4)
            )
        ) continue;

      TH1F* hist = (TH1F*)fileInput->Get(Form("LeptonPtResolution_Electrons_PtBin%d_EtaBin%d",i,j));
      assert(hist);

      RooRealVar leptonPtRes("leptonPtRes","leptonPtRes",-0.75,0.75);
      leptonPtRes.setRange("range",-0.75,0.75);
      leptonPtRes.setBins(100);
      RooDataHist *data=0;
      data = new RooDataHist("data","data",RooArgSet(leptonPtRes),hist);


      //********* OLD DEFAULTS *************************************************************
//       RooRealVar     *mean  = new RooRealVar("mean","mean",-0.006,-10,10);
//       RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.02,0.00001,0.021);
//       RooRealVar     *alpha = new RooRealVar("alpha","alpha",5,0,20);
//       RooRealVar     *n     = new RooRealVar("n","n",3,0,10);
      
//       RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,20);
//       RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,10);
//       RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,20);
//       RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,10);

//       RooRealVar     *sigmaL = new RooRealVar("sigmaL","sigmaL",0.02,0.00001,0.1);
//       RooRealVar     *sigmaR = new RooRealVar("sigmaR","sigmaR",0.02,0.00001,0.1);
      //************************************************************************************


//       RooRealVar     *mean  = new RooRealVar("mean","mean",-0.006,-10,10);
//       RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.02,0.00001,0.1);
//       RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,50);
//       RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,30);
//       RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,50);
//       RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,30);


      RooRealVar     *mean  = new RooRealVar("mean","mean",0.06,-10,10);
      RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.0165,0.00001,0.0175);
      RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,50);
      RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,30);
      RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,50);
      RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,30);


      RooDoubleSidedCBShape *model = new RooDoubleSidedCBShape("LeptonPtResModel","LeptonPtResModel",
                                                               leptonPtRes,*mean,*sigma,*alphaL,*nL,*alphaR,*nR);

      RooFitResult *fitResult=0;
      fitResult = model->fitTo(*data,
                               RooFit::Binned(true),
                               RooFit::Strategy(1),
                               RooFit::Save());

      cout << "Fitted parameters\n";
      cout << mean->getVal() << endl;
      cout << sigma->getVal() << endl;
      cout << alphaL->getVal() << endl;
      cout << nL->getVal() << endl;
      cout << alphaR->getVal() << endl;
      cout << nR->getVal() << endl;
     

      RooPlot *frame = leptonPtRes.frame(RooFit::Bins(100));
      data->plotOn(frame,RooFit::MarkerStyle(kFullCircle),RooFit::MarkerSize(0.8),RooFit::DrawOption("ZP"));    
      model->plotOn(frame);


      //Save Workspace
      RooWorkspace *w = new RooWorkspace(Form("LeptonPtResolutionModel_Electrons_PtBin%d_EtaBin%d",i,j),Form("LeptonPtResolutionModel_Electrons_PtBin%d_EtaBin%d",i,j));
      w->import(*model);
      w->import(*data);
      w->Print();

      TCanvas *cv = new TCanvas("cv","cv",800,600);
      
      frame->Draw();
      cv->SaveAs(Form("LeptonPtResolution_Electrons%s_PtBin%d_EtaBin%d.gif",label.c_str(),i,j)); 

      fileOutput->WriteTObject(model, Form("LeptonPtResolutionModel_Electrons_PtBin%d_EtaBin%d",i,j), "WriteDelete");
      fileOutput->WriteTObject(cv, Form("LeptonPtResolutionFit_Electrons_PtBin%d_EtaBin%d",i,j), "WriteDelete");
      fileOutput->WriteTObject(w, w->GetName(), "WriteDelete");

      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_mean, "DoubleSidedCBShapeParamArray_mean", "WriteDelete");
      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_sigma, "DoubleSidedCBShapeParamArray_sigma", "WriteDelete");
      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_alphaL, "DoubleSidedCBShapeParamArray_alphaL", "WriteDelete");
      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_nL, "DoubleSidedCBShapeParamArray_nL", "WriteDelete");
      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_alphaR, "DoubleSidedCBShapeParamArray_alphaR", "WriteDelete");
      fileOutput->WriteTObject(DoubleSidedCBShapeParamArray_nR, "DoubleSidedCBShapeParamArray_nR", "WriteDelete");


    }
  }





//   //********************************************************
//   // Fit for resolution function for muons
//   //******************************************************** 
//   for (uint i=0; i < NPtBins+2; ++i) {
//     for (uint j=0; j < NEtaBins+2; ++j) {

//       if (!(
//             (0==1)
// //             || (i==12 && j==8)
// //                            || (i==15 && j==14)
// //                        || (i==15 && j==7)
//             )
//         ) continue;

//       TH1F* hist = (TH1F*)fileInput->Get(Form("LeptonPtResolution_Electrons_PtBin%d_EtaBin%d",i,j));
//       assert(hist);

//       RooRealVar leptonPtRes("leptonPtRes","leptonPtRes",-0.25,0.25);
//       leptonPtRes.setRange("range",-0.25,0.25);
//       leptonPtRes.setBins(100);
//       RooDataHist *data=0;
//       data = new RooDataHist("data","data",RooArgSet(leptonPtRes),hist);

//       //********* OLD DEFAULTS *************************************************************
// //       RooRealVar     *mean  = new RooRealVar("mean","mean",-0.006,-10,10);
// //       RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.02,0.00001,0.021);
// //       RooRealVar     *alpha = new RooRealVar("alpha","alpha",5,0,20);
// //       RooRealVar     *n     = new RooRealVar("n","n",3,0,10);
      
// //       RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,20);
// //       RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,10);
// //       RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,20);
// //       RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,10);

// //       RooRealVar     *sigmaL = new RooRealVar("sigmaL","sigmaL",0.02,0.00001,0.1);
// //       RooRealVar     *sigmaR = new RooRealVar("sigmaR","sigmaR",0.02,0.00001,0.1);
//       //************************************************************************************

 
// //       RooRealVar     *mean  = new RooRealVar("mean","mean",-0.006,-10,10);
// //       RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.02,0.00001,0.1);
// //       RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,50);
// //       RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,30);
// //       RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,50);
// //       RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,30);

//       RooRealVar     *mean  = new RooRealVar("mean","mean",-0.006,-10,10);
//       RooRealVar     *sigma = new RooRealVar("sigma","sigma",0.03, 0.001, 0.1);
//       RooRealVar     *alphaL = new RooRealVar("alphaL","alphaL",5,0,50);
//       RooRealVar     *nL     = new RooRealVar("nL","nL",3,0,30);
//       RooRealVar     *alphaR = new RooRealVar("alphaR","alphaR",5,0,50);
//       RooRealVar     *nR     = new RooRealVar("nR","nR",3,0,30);
// //       sigma->setConstant(true);

//       RooDoubleSidedCBShape *model = new RooDoubleSidedCBShape("LeptonPtResModel","LeptonPtResModel",
//                                                                leptonPtRes,*mean,*sigma,*alphaL,*nL,*alphaR,*nR);

//       RooFitResult *fitResult=0;
//       fitResult = model->fitTo(*data,
//                                RooFit::Binned(true),
//                                RooFit::Strategy(1),
//                                RooFit::Save());

//       RooPlot *frame = leptonPtRes.frame(RooFit::Bins(100));
//       data->plotOn(frame,RooFit::MarkerStyle(kFullCircle),RooFit::MarkerSize(0.8),RooFit::DrawOption("ZP"));    
//       model->plotOn(frame);

//       TCanvas *cv = new TCanvas("cv","cv",800,600);
      
//       frame->Draw();
//       cv->SaveAs(Form("LeptonPtResolution_Muons_PtBin%d_EtaBin%d.gif",i,j)); 

//       fileOutput->WriteTObject(model, Form("LeptonPtResolutionModel_Muons_PtBin%d_EtaBin%d",i,j), "WriteDelete");
//       fileOutput->WriteTObject(cv, Form("LeptonPtResolutionFit_Muons_PtBin%d_EtaBin%d",i,j), "WriteDelete");
      
//     }
//   }



//   fileOutput->Close();




  gBenchmark->Show("WWTemplate");       
}


void CreateLeptonResponseMap(const string filename, const string Label = "ZZ", Int_t Option = 0) {

  if (Option == 0) {
    FillLeptonResponseHists(filename, Label, Option);
  } 

  if (Option == 0 || Option == 1) {
    FitLeptonResponseModels(Label, Option);
  }

}
