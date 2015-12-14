// -*- C++ -*-
//
// Package:    TotalEnergyCutFilter
// Class:      TotalEnergyCutFilter
// 
/**\class TotalEnergyCutFilter TotalEnergyCutFilter.cc TBAnalysis/TotalEnergyCutFilter/src/TotalEnergyCutFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Fri Jul 31 15:14:57 CEST 2009
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

class TotalEnergyCutFilter : public edm::EDFilter
{
   public:
      explicit TotalEnergyCutFilter(const edm::ParameterSet&);
      ~TotalEnergyCutFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double cut;
      bool doMissingChannelInterpolate;
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
TotalEnergyCutFilter::TotalEnergyCutFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   cut = iConfig.getUntrackedParameter<double>("cut", 30);
   doMissingChannelInterpolate = iConfig.getUntrackedParameter<bool>("interpolate", false);
   useMotherBoard[0] = iConfig.getUntrackedParameter<bool>("useMotherBoard0", true);
   useMotherBoard[1] = iConfig.getUntrackedParameter<bool>("useMotherBoard1", true);
   useMotherBoard[2] = iConfig.getUntrackedParameter<bool>("useMotherBoard2", true);
   useMotherBoard[3] = iConfig.getUntrackedParameter<bool>("useMotherBoard3", true);
}


TotalEnergyCutFilter::~TotalEnergyCutFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TotalEnergyCutFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   double eventtotalenergy = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double energy = 0;

            if(doMissingChannelInterpolate == false || hVlsbInfo->goodChannel[iMotherBoard][iChannel] == true)
            {
               double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
               adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
               energy = adc / hVlsbInfo->mip[iMotherBoard][iChannel];
            }
            else
            {
               int centerlayer = hVlsbInfo->channelToLayer[iMotherBoard][iChannel];

               int channel1 = 0;
               int channel2 = 0;

               if(centerlayer == 0)
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][1];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][1];
               }
               else if(centerlayer == HcalTBVLSBData::maxChannels - 1)
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][HcalTBVLSBData::maxChannels-2];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][HcalTBVLSBData::maxChannels-2];
               }
               else
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][centerlayer-1];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][centerlayer+1];
               }

               double adc1 = hVlsbData->adc(iMotherBoard, channel1, iSample);
               adc1 = adc1 - hVlsbInfo->baseline[iMotherBoard][channel1];
               adc1 = hVlsbInfo->GetAdc(adc1, iMotherBoard, channel1);
               energy = adc1 / hVlsbInfo->mip[iMotherBoard][channel1];

               double adc2 = hVlsbData->adc(iMotherBoard, channel2, iSample);
               adc2 = adc2 - hVlsbInfo->baseline[iMotherBoard][channel2];
               adc2 = hVlsbInfo->GetAdc(adc2, iMotherBoard, channel2);
               energy = energy + adc2 / hVlsbInfo->mip[iMotherBoard][channel2];

               energy = energy / 2;
            }

            if(useMotherBoard[iMotherBoard] == true)
               eventtotalenergy = eventtotalenergy + energy;
         }
      }
   }

   if(eventtotalenergy > cut)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TotalEnergyCutFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TotalEnergyCutFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(TotalEnergyCutFilter);
