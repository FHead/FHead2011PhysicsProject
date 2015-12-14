// -*- C++ -*-
//
// Package:    RHEnergyPercentageCut
// Class:      RHEnergyPercentageCut
// 
/**\class RHEnergyPercentageCut RHEnergyPercentageCut.cc TBRecHitAnalysis/RHEnergyPercentageCut/src/RHEnergyPercentageCut.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Wed Aug 12 12:30:15 CEST 2009
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

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

//
// class declaration
//

class RHEnergyPercentageCut : public edm::EDFilter
{
   public:
      explicit RHEnergyPercentageCut(const edm::ParameterSet&);
      ~RHEnergyPercentageCut();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double minimum;
      bool includeTower[3][3];
      std::string vlsbModule;
      std::string normalModule;
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
RHEnergyPercentageCut::RHEnergyPercentageCut(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimum = iConfig.getUntrackedParameter<double>("minimum", 0.9);

   vlsbModule = iConfig.getUntrackedParameter<std::string>("vlsbModule", "");
   normalModule = iConfig.getUntrackedParameter<std::string>("normalModule", "");

   includeTower[0][0] = iConfig.getUntrackedParameter<bool>("includeEta7Phi2", false);
   includeTower[0][1] = iConfig.getUntrackedParameter<bool>("includeEta8Phi2", false);
   includeTower[0][2] = iConfig.getUntrackedParameter<bool>("includeEta9Phi2", false);
   includeTower[1][0] = iConfig.getUntrackedParameter<bool>("includeEta7Phi3", false);
   includeTower[1][1] = iConfig.getUntrackedParameter<bool>("includeEta8Phi3", true);
   includeTower[1][2] = iConfig.getUntrackedParameter<bool>("includeEta9Phi3", true);
   includeTower[2][0] = iConfig.getUntrackedParameter<bool>("includeEta7Phi4", false);
   includeTower[2][1] = iConfig.getUntrackedParameter<bool>("includeEta8Phi4", false);
   includeTower[2][2] = iConfig.getUntrackedParameter<bool>("includeEta9Phi4", false);
}


RHEnergyPercentageCut::~RHEnergyPercentageCut()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RHEnergyPercentageCut::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double partialenergy = 0;
   double totalenergy = 0;

   if(normalModule.size() != 0)
   {
      edm::Handle<HBHERecHitCollection> hNormalData;
      iEvent.getByLabel(normalModule, hNormalData);

      for(HBHERecHitCollection::const_iterator iter = hNormalData->begin(); iter != hNormalData->end(); iter++)
      {
         double energy = iter->energy();

         int ieta = iter->id().ieta();

         int iphi = iter->id().iphi();
         int layergroup = iphi / 10 - 1;
         iphi = iphi % 10;

         if(iphi != 2 && iphi != 4)   // not of interest to us
            continue;
         if(ieta < 7 || ieta > 9)   // not of interest to us
            continue;
         if(layergroup >= 4 || layergroup < 0)   // what.....
            continue;

         int iPhiIndex = iphi - 2;
         int iEtaIndex = ieta - 7;

         if(energy < 2)
            continue;

         if(includeTower[iPhiIndex][iEtaIndex] == true)
            partialenergy = partialenergy + energy;

         totalenergy = totalenergy + energy;
      }
   }

   if(vlsbModule.size() != 0)
   {
      edm::Handle<HBHERecHitCollection> hVlsbData;
      iEvent.getByLabel(vlsbModule, "VLSB", hVlsbData);

      for(HBHERecHitCollection::const_iterator iter = hVlsbData->begin(); iter != hVlsbData->end(); iter++)
      {
         double energy = iter->energy();

         int ieta = iter->id().ieta();

         int iphi = iter->id().iphi();
         int layergroup = iphi - 50;
         iphi = 3;

         if(layergroup > 16 || layergroup < 0)   // what......
            continue;
         if(ieta < 7 || ieta > 9)   // something is wrong
            continue;

         int iPhiIndex = iphi - 2;
         int iEtaIndex = ieta - 7;

         if(energy < 2)
            continue;

         if(includeTower[iPhiIndex][iEtaIndex] == true)
            partialenergy = partialenergy + energy;

         totalenergy = totalenergy + energy;
      }
   }

   if(partialenergy / totalenergy < minimum)
      return false;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RHEnergyPercentageCut::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RHEnergyPercentageCut::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(RHEnergyPercentageCut);
