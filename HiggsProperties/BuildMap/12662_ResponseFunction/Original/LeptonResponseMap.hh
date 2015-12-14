
#include "TRandom3.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "CMSAna/HZZ4L/interface/RooDoubleSidedCBShape.hh"
#include "TH2F.h"



//=== FUNCTION DECLARATIONS ======================================================================================

  
UInt_t LeptonResponseMapFindBin( double value, double bins[], UInt_t nbins) {

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


double GenerateLeptonPtFromModel(TFile *inputfile, Int_t leptonID, Double_t pt, Double_t eta) 
{  

  string LeptonType = "";
  if (abs(leptonID) == 11) LeptonType = "Electrons";
  else if (abs(leptonID) == 13) LeptonType = "Muons";
  else {
    cout << "Error: leptonID " << leptonID << " is not recognized \n";
    return 0;
  }

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  UInt_t PtBin = LeptonResponseMapFindBin(pt,ptBins, 14);
  UInt_t EtaBin = LeptonResponseMapFindBin(fabs(eta),etaBins, 16);

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

  RooRealVar     *mean  = w->var("mean");
  RooRealVar     *sigma = w->var("sigma");
  RooRealVar     *alphaL = w->var("alphaL");
  RooRealVar     *nL     = w->var("nL");
  RooRealVar     *alphaR = w->var("alphaR");
  RooRealVar     *nR     = w->var("nR");
//   cout << "Model Parameters: " 
//        << " mean=" << mean->getVal() << " ; "
//        << " sigma=" << sigma->getVal() << " ; "
//        << " alphaL=" << alphaL->getVal() << " ; "
//        << " nL=" << nL->getVal() << " ; "
//        << " alphaR=" << alphaR->getVal() << " ; "
//        << " nR=" << nR->getVal() << " ; "
//        << "\n";

//   TH2F *meanHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_mean",LeptonType.c_str()));
//   TH2F *sigmaHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_sigma",LeptonType.c_str()));
//   TH2F *alphaLHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_alphaL",LeptonType.c_str()));
//   TH2F *nLHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_nL",LeptonType.c_str()));
//   TH2F *alphaRHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_alphaR",LeptonType.c_str()));
//   TH2F *nRHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_nR",LeptonType.c_str()));
//   double tmpmean = meanHist->GetBinContent(PtBin,EtaBin);
//   double tmpsigma = sigmaHist->GetBinContent(PtBin,EtaBin);
//   double tmpalphaL = alphaLHist->GetBinContent(PtBin,EtaBin);
//   double tmpnL = nLHist->GetBinContent(PtBin,EtaBin);
//   double tmpalphaR = alphaRHist->GetBinContent(PtBin,EtaBin);
//   double tmpnR = nRHist->GetBinContent(PtBin,EtaBin);


//   cout << "Check Model Parameters: " 
//        << " mean=" << tmpmean << " ; "
//        << " sigma=" << tmpsigma << " ; "
//        << " alphaL=" << tmpalphaL << " ; "
//        << " nL=" << tmpnL << " ; "
//        << " alphaR=" << tmpalphaR << " ; "
//        << " nR=" << tmpnR << " ; "
//        << "\n";

  RooRealVar *leptonPtRes = new RooRealVar("leptonPtRes","leptonPtRes",-0.75,0.75);
  RooDataSet *data = model->generate(*leptonPtRes,1);
  const RooArgSet *ent = data->get(0);
  double val = static_cast<RooAbsReal*>(ent->find(leptonPtRes->GetName()))->getVal();

  double simulatedPt = (val + 1)*pt;
  return simulatedPt;

}


//apply an approximate gaussian model - to improve speed
double GenerateLeptonPtFromGaussianModel(TFile *inputfile, TRandom3 *random, Int_t leptonID, Double_t pt, Double_t eta) 
{  

  string LeptonType = "";
  if (abs(leptonID) == 11) LeptonType = "Electrons";
  else if (abs(leptonID) == 13) LeptonType = "Muons";
  else {
    cout << "Error: leptonID " << leptonID << " is not recognized \n";
    return 0;
  }

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  UInt_t PtBin = LeptonResponseMapFindBin(pt,ptBins, 14);
  UInt_t EtaBin = LeptonResponseMapFindBin(fabs(eta),etaBins, 16);

  RooFit::PrintLevel(-1);

  TH2F *meanHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_mean",LeptonType.c_str()));
  TH2F *sigmaHist = (TH2F*)inputfile->Get(Form("DoubleSidedCBShapeParamArray_%s_sigma",LeptonType.c_str()));
  double tmpmean = meanHist->GetBinContent(PtBin,EtaBin);
  double tmpsigma = sigmaHist->GetBinContent(PtBin,EtaBin);
    
  //adhoc correction to make resolution approximately match the resolution we get using proper CB response functions
  double val = random->Gaus(tmpmean,tmpsigma*(4.5/2.4));

  double simulatedPt = (val + 1)*pt;
  return simulatedPt;

}



double GenerateLeptonPtFromHist(TFile *inputfile, string LeptonType, Double_t pt, Double_t eta) 
{  

  Double_t ptBins[15] = {5,7,8,9,10,12,14,16,18,20,25,30,35,40,50};
  Double_t etaBins[17] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4442,1.566,1.8,2,2.1,2.2,2.3,2.4,2.5,2.6};

  UInt_t PtBin = LeptonResponseMapFindBin(pt,ptBins, 14);
  UInt_t EtaBin = LeptonResponseMapFindBin(fabs(eta),etaBins, 16);

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


