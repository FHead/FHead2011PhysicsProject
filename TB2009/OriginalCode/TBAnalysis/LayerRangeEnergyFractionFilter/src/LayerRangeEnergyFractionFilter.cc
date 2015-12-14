// -*- C++ -*-
//
// Package:    LayerRangeEnergyFractionFilter
// Class:      LayerRangeEnergyFractionFilter
// 
/**\class LayerRangeEnergyFractionFilter LayerRangeEnergyFractionFilter.cc TBAnalysis/LayerRangeEnergyFractionFilter/src/LayerRangeEnergyFractionFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug  6 22:50:38 CEST 2009
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

class LayerRangeEnergyFractionFilter : public edm::EDFilter {
   public:
      explicit LayerRangeEnergyFractionFilter(const edm::ParameterSet&);
      ~LayerRangeEnergyFractionFilter();

   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      // ----------member data ---------------------------
      int minlayer;
      int maxlayer;
      double minimum;   // that passes

      int survivedEvents;
      int totalEvents;
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
LayerRangeEnergyFractionFilter::LayerRangeEnergyFractionFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minlayer = iConfig.getUntrackedParameter<int>("minLayer", 8);
   maxlayer = iConfig.getUntrackedParameter<int>("maxLayer", 15);
   minimum = iConfig.getUntrackedParameter<double>("minimum", 0.1);

   std::cout << "[LayerRangeEnergyFractionFilter][LayerRangeEnergyFractionFilter] ";
   std::cout << minlayer << " " << maxlayer << " " << minimum << std::endl;

   totalEvents = 0;
   survivedEvents = 0;
}


LayerRangeEnergyFractionFilter::~LayerRangeEnergyFractionFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
LayerRangeEnergyFractionFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
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

   totalEvents = totalEvents + 1;

   if(partialenergy / totalenergy < minimum)
      return false;

   survivedEvents = survivedEvents + 1;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
LayerRangeEnergyFractionFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LayerRangeEnergyFractionFilter::endJob()
{
   std::cout << "[LayerRangeEnergyFractionFilter][endJob] Survival: " << survivedEvents
      << "/" << totalEvents << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(LayerRangeEnergyFractionFilter);
