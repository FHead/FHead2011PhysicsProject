// -*- C++ -*-
//
// Package:    FillEventDisplayAnalyzer
// Class:      FillEventDisplayAnalyzer
// 
/**\class FillEventDisplayAnalyzer FillEventDisplayAnalyzer.cc TBAnalysis/FillEventDisplayAnalyzer/src/FillEventDisplayAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Fri Jul 31 14:57:28 CEST 2009
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
#include "TH2D.h"

//
// class decleration
//

class FillEventDisplayAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillEventDisplayAnalyzer(const edm::ParameterSet&);
      ~FillEventDisplayAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      int maxEvent;
      int eventCount;
      TFile *outputFile;
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
FillEventDisplayAnalyzer::FillEventDisplayAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   maxEvent = iConfig.getUntrackedParameter<int>("maxEvent", 100);

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "EventDisplay.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   eventCount = 0;
}


FillEventDisplayAnalyzer::~FillEventDisplayAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillEventDisplayAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   if(eventCount >= maxEvent)
      return;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   TH2D *timeIntegratedDisplay = new TH2D(Form("TimeIntegratedEventDisplay_%d", eventCount),
      Form("Time integrated event display (event %d);iEta;Layer;Energy", iEvent.id().event()),
      3, 6.5, 9.5, hVlsbInfo->maxChannels, -0.5, hVlsbInfo->maxChannels - 0.5);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      TH2D *histogram = new TH2D(Form("EventDisplay_%d_%d", iMotherBoard, eventCount),
         Form("Event Display (motherboard %d, event %d);Layer;Sample;Energy", iMotherBoard, iEvent.id().event()),
         hVlsbInfo->maxChannels, -0.5, hVlsbInfo->maxChannels - 0.5,
         hVlsbInfo->maxSample - hVlsbInfo->minSample, hVlsbInfo->minSample - 0.5, hVlsbInfo->maxSample - 0.5);

      for(int iChannel = 0; iChannel < hVlsbInfo->maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         double totalenergy = 0;

         for(int iSample = hVlsbInfo->minSample; iSample < hVlsbInfo->maxSample; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            double energy = adc / hVlsbInfo->mip[iMotherBoard][iChannel];

            totalenergy = totalenergy + energy;

            histogram->Fill(hVlsbInfo->channelToLayer[iMotherBoard][iChannel], iSample, energy);
         }

         timeIntegratedDisplay->Fill(hVlsbInfo->motherBoardEta[iMotherBoard], hVlsbInfo->channelToLayer[iMotherBoard][iChannel], totalenergy);
      }

      outputFile->cd();
      histogram->Write();

      delete histogram;
   }

   outputFile->cd();
   timeIntegratedDisplay->Write();

   delete timeIntegratedDisplay;

   eventCount = eventCount + 1;
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillEventDisplayAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillEventDisplayAnalyzer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillEventDisplayAnalyzer);
