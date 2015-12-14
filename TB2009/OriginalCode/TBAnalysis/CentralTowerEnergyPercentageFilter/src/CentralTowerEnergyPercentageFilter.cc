// -*- C++ -*-
//
// Package:    CentralTowerEnergyPercentageFilter
// Class:      CentralTowerEnergyPercentageFilter
// 
/**\class CentralTowerEnergyPercentageFilter CentralTowerEnergyPercentageFilter.cc TBAnalysis/CentralTowerEnergyPercentageFilter/src/CentralTowerEnergyPercentageFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Sun Aug  9 18:19:11 CEST 2009
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

class CentralTowerEnergyPercentageFilter : public edm::EDFilter
{
   public:
      explicit CentralTowerEnergyPercentageFilter(const edm::ParameterSet&);
      ~CentralTowerEnergyPercentageFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double minimum;
      bool includeMotherBoard[4];
      bool zerosuppress;
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
CentralTowerEnergyPercentageFilter::CentralTowerEnergyPercentageFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimum = iConfig.getUntrackedParameter<double>("cut", 0.95);
   includeMotherBoard[0] = iConfig.getUntrackedParameter<bool>("includeMotherBoard0", true);
   includeMotherBoard[1] = iConfig.getUntrackedParameter<bool>("includeMotherBoard1", false);
   includeMotherBoard[2] = false;
   includeMotherBoard[3] = iConfig.getUntrackedParameter<bool>("includeMotherBoard3", false);
   zerosuppress = iConfig.getUntrackedParameter<bool>("zeroSuppress", true);
}


CentralTowerEnergyPercentageFilter::~CentralTowerEnergyPercentageFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CentralTowerEnergyPercentageFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double centralenergy = 0;
   double allenergy = 0;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {  
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      double energy = 0;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            energy = energy + adc / hVlsbInfo->mip[iMotherBoard][iChannel];
         }
      }

      if(energy < 0 && zerosuppress == true)
         energy = 0;

      if(includeMotherBoard[iMotherBoard] == true)
         centralenergy = centralenergy + energy;
      allenergy = allenergy + energy;
   }

   double percentage = centralenergy / allenergy;
   if(allenergy < 1e-10)
      percentage = 0;

   if(percentage < minimum)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void CentralTowerEnergyPercentageFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void CentralTowerEnergyPercentageFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralTowerEnergyPercentageFilter);
