// -*- C++ -*-
//
// Package:    LayerZeroVetoFilter
// Class:      LayerZeroVetoFilter
// 
/**\class LayerZeroVetoFilter LayerZeroVetoFilter.cc TBAnalysis/LayerZeroVetoFilter/src/LayerZeroVetoFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug  6 22:37:03 CEST 2009
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

class LayerZeroVetoFilter : public edm::EDFilter
{
   public:
      explicit LayerZeroVetoFilter(const edm::ParameterSet&);
      ~LayerZeroVetoFilter();

   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      // ----------member data ---------------------------
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
LayerZeroVetoFilter::LayerZeroVetoFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

}


LayerZeroVetoFilter::~LayerZeroVetoFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
LayerZeroVetoFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   int iMotherBoard = 0;   // using only the central tower

   double energy0 = 0;
   for(int iSample = 0; iSample < hVlsbInfo->maxSample; iSample++)
   {
      double adc = hVlsbData->adc(iMotherBoard, 0, iSample);
      adc = adc - hVlsbInfo->baseline[iMotherBoard][0];
      adc = hVlsbInfo->GetAdc(adc, iMotherBoard, 0);
      energy0 = energy0 + adc / hVlsbInfo->mip[iMotherBoard][0];
   }

   for(int iChannel = 1; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
   {
      double energy = 0;

      for(int iSample = 0; iSample < hVlsbInfo->maxSample; iSample++)
      {
         double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
         adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
         adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
         energy = energy + adc / hVlsbInfo->mip[iMotherBoard][iChannel];
      }

      if(energy > energy0)
         return true;
   }

   return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
LayerZeroVetoFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LayerZeroVetoFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(LayerZeroVetoFilter);
