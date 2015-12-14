// -*- C++ -*-
//
// Package:    AllSingleLayerChargeCut
// Class:      AllSingleLayerChargeCut
// 
/**\class AllSingleLayerChargeCut AllSingleLayerChargeCut.cc TBAnalysis/AllSingleLayerChargeCut/src/AllSingleLayerChargeCut.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Mon Aug 17 17:59:28 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

//
// class declaration
//

class AllSingleLayerChargeCut : public edm::EDFilter
{
   public:
      explicit AllSingleLayerChargeCut(const edm::ParameterSet&);
      ~AllSingleLayerChargeCut();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double maximum;
      bool useMotherBoard[4];
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
AllSingleLayerChargeCut::AllSingleLayerChargeCut(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   maximum = iConfig.getUntrackedParameter<double>("maximum", 300);
   useMotherBoard[0] = iConfig.getUntrackedParameter<bool>("useMotherBoard0", true);
   useMotherBoard[1] = iConfig.getUntrackedParameter<bool>("useMotherBoard1", true);
   useMotherBoard[2] = iConfig.getUntrackedParameter<bool>("useMotherBoard2", false);
   useMotherBoard[3] = iConfig.getUntrackedParameter<bool>("useMotherBoard3", true);
}


AllSingleLayerChargeCut::~AllSingleLayerChargeCut()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
AllSingleLayerChargeCut::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false || useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         double chargesum = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            chargesum = chargesum + adc;
         }

         if(chargesum > maximum)
            return false;
      }
   }

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
AllSingleLayerChargeCut::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AllSingleLayerChargeCut::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(AllSingleLayerChargeCut);
