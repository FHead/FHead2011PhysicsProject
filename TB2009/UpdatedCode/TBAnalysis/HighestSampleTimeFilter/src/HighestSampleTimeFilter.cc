// -*- C++ -*-
//
// Package:    HighestSampleTimeFilter
// Class:      HighestSampleTimeFilter
// 
/**\class HighestSampleTimeFilter HighestSampleTimeFilter.cc TBAnalysis/HighestSampleTimeFilter/src/HighestSampleTimeFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Sep  3 11:47:47 CEST 2009
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

class HighestSampleTimeFilter : public edm::EDFilter
{
   public:
      explicit HighestSampleTimeFilter(const edm::ParameterSet&);
      ~HighestSampleTimeFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double minimumTime;   // in units of samples
      bool individual;
      double threshold;
      bool doInvert;
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
HighestSampleTimeFilter::HighestSampleTimeFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimumTime = iConfig.getUntrackedParameter<double>("minimum", 9);
   individual = iConfig.getUntrackedParameter<bool>("individual", true);
   threshold = iConfig.getUntrackedParameter<double>("threshold", 50);
   doInvert = iConfig.getUntrackedParameter<bool>("invert", false);
}


HighestSampleTimeFilter::~HighestSampleTimeFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HighestSampleTimeFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   double highestvalue = 0;
   int sample = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         double high = -100000;
         double low = 100000;
         int highindex = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            if(doInvert == true)
               adc = -adc;

            if(adc > highestvalue)
            {
               highestvalue = adc;
               sample = iSample;
            }

            if(adc > high)
            {
               high = adc;
               highindex = iSample;
            }

            if(adc < low)
               low = adc;
         }

         if(individual == true && high - low > threshold && highindex < minimumTime)
            return false;
      }
   }

   if(sample < minimumTime)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
HighestSampleTimeFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HighestSampleTimeFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(HighestSampleTimeFilter);
