// -*- C++ -*-
//
// Package:    FillMaxAdcAnalyzer
// Class:      FillMaxAdcAnalyzer
// 
/**\class FillMaxAdcAnalyzer FillMaxAdcAnalyzer.cc TBAnalysis/FillMaxAdcAnalyzer/src/FillMaxAdcAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Mon Aug 17 13:29:59 CEST 2009
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

#include "TH1D.h"
#include "TFile.h"

//
// class decleration
//

class FillMaxAdcAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillMaxAdcAnalyzer(const edm::ParameterSet&);
      ~FillMaxAdcAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      double threshold;

      TFile *outputFile;
      TH1D *numberOfSamplePassThresholdInChannel[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];
      TH1D *maxNumberOfSampleInChannelPassThreshold;
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
FillMaxAdcAnalyzer::FillMaxAdcAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   threshold = iConfig.getUntrackedParameter<double>("threshold", 12600);

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "MaxAdc.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         TString name = Form("OverThresholdSample_%d_%d", iMotherBoard, iChannel);
         TString title = Form("Number of samples over threshold (motherboard %d, channel %d);;", iMotherBoard, iChannel);
         numberOfSamplePassThresholdInChannel[iMotherBoard][iChannel] = new TH1D(name, title, 33, -0.5, 32.5);
      }
   }

   maxNumberOfSampleInChannelPassThreshold = new TH1D("MaxNumberOverThreshold", "Maximum number of sample in channel that passes threshold in an event", 33, -0.5, 32.5);
}


FillMaxAdcAnalyzer::~FillMaxAdcAnalyzer()
{
   delete maxNumberOfSampleInChannelPassThreshold;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         delete numberOfSamplePassThresholdInChannel[iMotherBoard][iChannel];

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillMaxAdcAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   int maxcount = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         int count = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
            if(hVlsbData->adc(iMotherBoard, iChannel, iSample) > threshold)
               count = count + 1;

         numberOfSamplePassThresholdInChannel[iMotherBoard][iChannel]->Fill(count);

         if(count > maxcount)
            maxcount = count;
      }
   }

   maxNumberOfSampleInChannelPassThreshold->Fill(maxcount);
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillMaxAdcAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillMaxAdcAnalyzer::endJob()
{
   outputFile->cd();

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         numberOfSamplePassThresholdInChannel[iMotherBoard][iChannel]->Write();

   maxNumberOfSampleInChannelPassThreshold->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillMaxAdcAnalyzer);
