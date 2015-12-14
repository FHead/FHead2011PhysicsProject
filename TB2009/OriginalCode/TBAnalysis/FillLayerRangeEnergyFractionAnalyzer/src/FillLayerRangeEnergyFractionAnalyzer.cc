// -*- C++ -*-
//
// Package:    FillLayerRangeEnergyFractionAnalyzer
// Class:      FillLayerRangeEnergyFractionAnalyzer
// 
/**\class FillLayerRangeEnergyFractionAnalyzer FillLayerRangeEnergyFractionAnalyzer.cc TBAnalysis/FillLayerRangeEnergyFractionAnalyzer/src/FillLayerRangeEnergyFractionAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug  6 22:58:54 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

#include "TFile.h"
#include "TH1D.h"
#include "TString.h"

//
// class decleration
//

class FillLayerRangeEnergyFractionAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillLayerRangeEnergyFractionAnalyzer(const edm::ParameterSet&);
      ~FillLayerRangeEnergyFractionAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      int minlayer;
      int maxlayer;

      TFile *outputFile;
      TH1D *fractionHistogram;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
FillLayerRangeEnergyFractionAnalyzer::FillLayerRangeEnergyFractionAnalyzer(const edm::ParameterSet& iConfig)
{
   minlayer = iConfig.getUntrackedParameter<int>("minLayer", 8);
   maxlayer = iConfig.getUntrackedParameter<int>("maxLayer", 15);

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "fraction.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   TString title = Form("Fraction of Energy between layers %d and %d", minlayer, maxlayer);
   fractionHistogram = new TH1D("FractionEnergy", title, 100, 0, 1);
}


FillLayerRangeEnergyFractionAnalyzer::~FillLayerRangeEnergyFractionAnalyzer()
{
   delete fractionHistogram;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillLayerRangeEnergyFractionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   int iMotherBoard = 0;   // using only the central tower

   double totalenergy = 0;
   double partialenergy = 0;

   for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
   {
      if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
         continue;

      double energy = 0;

      for(int iSample = 0; iSample < hVlsbInfo->maxSample; iSample++)
      {
         double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
         adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
         adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
         energy = energy + adc / hVlsbInfo->mip[iMotherBoard][iChannel];
      }

      totalenergy = totalenergy + energy;
      if(hVlsbInfo->channelToLayer[iMotherBoard][iChannel] <= maxlayer &&
         hVlsbInfo->channelToLayer[iMotherBoard][iChannel] >= minlayer)
         partialenergy = partialenergy + energy;
   }

   fractionHistogram->Fill(partialenergy / totalenergy);
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillLayerRangeEnergyFractionAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillLayerRangeEnergyFractionAnalyzer::endJob()
{
   outputFile->cd();
   fractionHistogram->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillLayerRangeEnergyFractionAnalyzer);
