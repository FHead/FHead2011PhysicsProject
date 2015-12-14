//root -l HiggsAna/HZZ4l/HLL/CreateEfficiencyMap.C+'("HZZEfficiencyMap_HZZ125.root","HZZ125",0)'


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
#include "HiggsAna/HZZ4l/interface/HZZEfficiencyMap.hh"

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

void CreateEfficiencyMap(const string filename, const string Label = "ZZ", Int_t Option = 0) 
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
   const UInt_t NPtBins = 15;
   const UInt_t NEtaBins = 16;
   const UInt_t NPhiBins = 12;
   double ptBins[NPtBins+1] = { 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 50};
   double etaBins[NEtaBins+1] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4442, 1.566, 1.8, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
   double phiBins[NPhiBins+1] = { -3.2, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5,  2, 2.5, 3.2 };

//   double ***NDenominator_PtEtaPhi;
//   double ***NNumerator_PtEtaPhi;
//   double ***Efficiency_PtEtaPhi;
//   double **NDenominator_PtEta;
//   double **NNumerator_PtEta;
//   double **Efficiency_PtEta;

   vector<vector<vector<double> > > NDenominator_PtEtaPhi;
   vector<vector<vector<double> > > NNumerator_PtEtaPhi;
   vector<vector<vector<double> > > Efficiency_PtEtaPhi;
   vector<vector<double> > NDenominator_PtEta;
   vector<vector<double> > NNumerator_PtEta;
   vector<vector<double> > Efficiency_PtEta;
   
   initialize3DArray(NDenominator_PtEtaPhi, NPtBins, NEtaBins, NPhiBins);
   initialize3DArray(NNumerator_PtEtaPhi, NPtBins, NEtaBins, NPhiBins);
   initialize3DArray(Efficiency_PtEtaPhi, NPtBins, NEtaBins, NPhiBins);
   initialize2DArray(NDenominator_PtEta, NPtBins, NEtaBins);
   initialize2DArray(NNumerator_PtEta, NPtBins, NEtaBins);
   initialize2DArray(Efficiency_PtEta, NPtBins, NEtaBins);
  
   
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
    if (ientry % 100000 == 0) cout << "Event " << ientry << endl;
    
    //********************************************************
    //double mynpu = TMath::Min((double)info->nPUEvents,34.999);
    //Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
    //double npuWeight = fhDPU->GetBinContent(npuxbin);
    //********************************************************
    double weight = 1.0;

    Int_t tmpPtBin = FindBin( efficiencyMap->genpt , ptBins, NPtBins);
    Int_t tmpEtaBin = FindBin( fabs(efficiencyMap->geneta) , etaBins, NEtaBins);
    Int_t tmpPhiBin = FindBin( efficiencyMap->genphi , phiBins, NPhiBins);

//     cout << fabs(efficiencyMap->geneta) << " " << tmpEtaBin << endl;

    NDenominator_PtEtaPhi[tmpPtBin][tmpEtaBin][tmpPhiBin] += weight;
    NDenominator_PtEta[tmpPtBin][tmpEtaBin] += weight;
    if (efficiencyMap->pass == kTRUE && efficiencyMap->recopt > -9999) {
      NNumerator_PtEtaPhi[tmpPtBin][tmpEtaBin][tmpPhiBin] += weight;
      NNumerator_PtEta[tmpPtBin][tmpEtaBin] += weight;      
    }
  } //end loop over data     

  computeEfficiencyPtEtaPhi(NNumerator_PtEtaPhi, NDenominator_PtEtaPhi, Efficiency_PtEtaPhi);
  computeEfficiencyPtEta(NNumerator_PtEta, NDenominator_PtEta, Efficiency_PtEta);

  for (uint i=0; i < NPtBins+2; ++i) {
    for (uint j=0; j < NEtaBins+2; ++j) {
      for (uint k=0; k < NPhiBins+2; ++k) {
        cout << i << " " << j << " " << k << " : " << Efficiency_PtEtaPhi[i][j][k] << endl;
      }
    }
  }


  //********************************************************
  // Produce output lookup table
  //******************************************************** 
  ofstream outf("LeptonEfficiencyMap.h");

  outf << "UInt_t FindBin( double value, double bins[], UInt_t nbins) {" << endl;
  outf << "  UInt_t nbinboundaries = nbins+1;" << endl;
  outf << "  UInt_t bin = 0;" << endl;
  outf << "  for (uint i=0; i < nbinboundaries; ++i) {" << endl;
  outf << "    if (i < nbinboundaries-1) {" << endl;
  outf << "      if (value >= bins[i] && value < bins[i+1]) {" << endl;
  outf << "        bin = i+1;" << endl;
  outf << "        break;" << endl;
  outf << "      }" << endl;
  outf << "    } else if (i == nbinboundaries-1) {" << endl;
  outf << "      if (value >= bins[i]) {" << endl;
  outf << "        bin = nbinboundaries;" << endl;
  outf << "        break;" << endl;
  outf << "      }" << endl;
  outf << "    }    " << endl;
  outf << "  }" << endl;
  outf << "  return bin;" << endl;
  outf << "}" << endl;

  outf << endl;
  outf << endl;

  outf << "Double_t GetLeptonEfficiencyPtEtaPhi(Double_t Pt, Double_t Eta, Double_t Phi) {" << endl;

  outf << endl;
  outf << "  Double_t ptBins[" << NPtBins+1 << "] = {";
  for (uint i=0; i < NPtBins+1; ++i) {
    outf << ptBins[i];
    if (i < NPtBins) {
      outf << ",";
    }
  }
  outf << "};\n";

  outf << "  Double_t etaBins[" << NEtaBins+1 << "] = {";
  for (uint i=0; i < NEtaBins+1; ++i) {
    outf << etaBins[i];
    if (i < NEtaBins) {
      outf << ",";
    }
  }
  outf << "};\n";

  outf << "  Double_t phiBins[" << NPhiBins+1 << "] = {";
  for (uint i=0; i < NPhiBins+1; ++i) {
    outf << phiBins[i];
    if (i < NPhiBins) {
      outf << ",";
    }
  }
  outf << "};\n";

  outf << endl;
  outf << endl;

  outf << "  Double_t Efficiency[" << NPtBins+2 << "][" << NEtaBins+2 << "][" << NPhiBins+2 << "]  = {";
  outf << endl;

  for (uint i=0; i < NPtBins+2; ++i) {
    outf << "    {" << endl;
    for (uint j=0; j < NEtaBins+2; ++j) {
      outf << "      {";
      for (uint k=0; k < NPhiBins+2; ++k) {
        outf << Efficiency_PtEtaPhi[i][j][k];
        if (k< NPhiBins+1) {
          outf << ",";
        }        
      }
      if (j< NEtaBins+1) {
        outf << "},";
      } else {
        outf << "}";
      }
      outf << endl;
    }
    if (i< NPtBins+1) {
      outf << "    },";
    } else {
      outf << "}";
    }
    outf << endl;
  }

  outf << "};" << endl;

  outf << endl;
  outf << endl;

  outf << "  Int_t tmpPtBin = FindBin( Pt , ptBins, " << NPtBins << ");" << endl;
  outf << "  Int_t tmpEtaBin = FindBin( Eta , etaBins, " << NEtaBins << ");" << endl;
  outf << "  Int_t tmpPhiBin = FindBin( Phi , phiBins, " << NPhiBins << ");" << endl;
  outf << "  return Efficiency[tmpPtBin][tmpEtaBin][tmpPhiBin];" << endl;
  outf << "}" << endl;


  outf << endl;
  outf << endl;
  outf << endl;
  outf << endl;


  outf << "Double_t GetLeptonEfficiencyPtEta(Double_t Pt, Double_t Eta) {" << endl;

  outf << endl;
  outf << "  Double_t ptBins[" << NPtBins+1 << "] = {";
  for (uint i=0; i < NPtBins+1; ++i) {
    outf << ptBins[i];
    if (i < NPtBins) {
      outf << ",";
    }
  }
  outf << "};\n";

  outf << "  Double_t etaBins[" << NEtaBins+1 << "] = {";
  for (uint i=0; i < NEtaBins+1; ++i) {
    outf << etaBins[i];
    if (i < NEtaBins) {
      outf << ",";
    }
  }
  outf << "};\n";


  outf << endl;
  outf << endl;

  outf << "  Double_t Efficiency[" << NPtBins+2 << "][" << NEtaBins+2 << "] = {";
  outf << endl;

  for (uint i=0; i < NPtBins+2; ++i) {
    outf << "    {";
    for (uint j=0; j < NEtaBins+2; ++j) {
      outf << Efficiency_PtEta[i][j];
      if (j< NEtaBins+1) {
        outf << ",";
      }
    }
    if (i< NPtBins+1) {
      outf << "    },";
    } else {
      outf << "}";
    }
    outf << endl;
  }
  
  outf << "  };" << endl;

  outf << endl;
  outf << endl;

  outf << "  Int_t tmpPtBin = FindBin( Pt , ptBins, " << NPtBins << ");" << endl;
  outf << "  Int_t tmpEtaBin = FindBin( Eta , etaBins, " << NEtaBins << ");" << endl;
  outf << "  return Efficiency[tmpPtBin][tmpEtaBin];" << endl;
  outf << "}" << endl;


  outf.close();




  gBenchmark->Show("WWTemplate");       
} 


