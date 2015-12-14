// -*- C++ -*-
//
// Package:    FirstNSampleRMSFilter
// Class:      FirstNSampleRMSFilter
// 
/**\class FirstNSampleRMSFilter FirstNSampleRMSFilter.cc TBAnalysis/FirstNSampleRMSFilter/src/FirstNSampleRMSFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Sep  3 21:18:19 CEST 2009
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

#include <cmath>

//
// class declaration
//

class FirstNSampleRMSFilter : public edm::EDFilter
{
   public:
      explicit FirstNSampleRMSFilter(const edm::ParameterSet&);
      ~FirstNSampleRMSFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      int N;   // number of samples to use in the beginning
      double maximum;   // RMS cannot exceed this value
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
FirstNSampleRMSFilter::FirstNSampleRMSFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   N = iConfig.getUntrackedParameter<int>("N", 4);
   maximum = iConfig.getUntrackedParameter<double>("maximum", 18);
}


FirstNSampleRMSFilter::~FirstNSampleRMSFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FirstNSampleRMSFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   double X = 0;
   double XX = 0;
   int count = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         for(int iSample = 0; iSample < N; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample) - hVlsbInfo->baseline[iMotherBoard][iSample];
            X = X + adc;
            XX = XX + adc * adc;
            count = count + 1;
         }
      }
   }

   double RMS = std::sqrt((XX - X * X) / count);

   if(RMS > maximum)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FirstNSampleRMSFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FirstNSampleRMSFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(FirstNSampleRMSFilter);
