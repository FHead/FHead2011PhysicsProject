// -*- C++ -*-
//
// Package:    MaxAdcCutFilter
// Class:      MaxAdcCutFilter
// 
/**\class MaxAdcCutFilter MaxAdcCutFilter.cc TBAnalysis/MaxAdcCutFilter/src/MaxAdcCutFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Wed Jul 29 10:37:21 CEST 2009
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

#include "TBDataFormats/HcalTBObjects/interface/HcalTBTriggerData.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"

#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

#include <vector>

//
// class declaration
//

class MaxAdcCutFilter : public edm::EDFilter
{
   public:
      explicit MaxAdcCutFilter(const edm::ParameterSet&);
      ~MaxAdcCutFilter();

   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      // ----------member data ---------------------------
      std::vector<double> cut[HcalTBVLSBData::maxMotherBoards];
      int eventCount;
      int survivedEventCount;
      bool relativeToBaseline;
      bool useRealAdc;
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
MaxAdcCutFilter::MaxAdcCutFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   double overallcut = iConfig.getUntrackedParameter<double>("cut", 12600);
   cut[0] = iConfig.getUntrackedParameter<std::vector<double> >("motherBoard0_cut", std::vector<double>());
   cut[1] = iConfig.getUntrackedParameter<std::vector<double> >("motherBoard1_cut", std::vector<double>());
   cut[2] = iConfig.getUntrackedParameter<std::vector<double> >("motherBoard2_cut", std::vector<double>());
   cut[3] = iConfig.getUntrackedParameter<std::vector<double> >("motherBoard3_cut", std::vector<double>());

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if((int)cut[iMotherBoard].size() <= iChannel)
            cut[iMotherBoard].push_back(overallcut);
         else if(cut[iMotherBoard][iChannel] > overallcut)
            cut[iMotherBoard][iChannel] = overallcut;
      }
   }

   relativeToBaseline = iConfig.getUntrackedParameter<bool>("baselineSubtracted", false);
   useRealAdc = iConfig.getUntrackedParameter<bool>("useRealAdc", true);

   eventCount = 0;
   survivedEventCount = 0;
}


MaxAdcCutFilter::~MaxAdcCutFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MaxAdcCutFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   eventCount = eventCount + 1;

   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            // if the motherboard is not setup, the values will be 65535
            if(adc > 65500)
               continue;

            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];

            if(useRealAdc == false)
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);

            if(relativeToBaseline == false)
               adc = adc + hVlsbInfo->baseline[iMotherBoard][iChannel];

            if(adc > cut[iMotherBoard][iChannel])
               return false;
         }
      }
   }

   survivedEventCount = survivedEventCount + 1;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MaxAdcCutFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MaxAdcCutFilter::endJob()
{
   std::cout << "[MaxAdcCutFilter][endJob] Survived events: " << survivedEventCount << "/"
      << eventCount << " (" << (double)(survivedEventCount) / eventCount * 100 << "%)" << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(MaxAdcCutFilter);
