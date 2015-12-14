// -*- C++ -*-
//
// Package:    RHTotalEnergyCut
// Class:      RHTotalEnergyCut
// 
/**\class RHTotalEnergyCut RHTotalEnergyCut.cc TBRecHitAnalysis/RHTotalEnergyCut/src/RHTotalEnergyCut.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Wed Aug 12 12:12:54 CEST 2009
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

class RHTotalEnergyCut : public edm::EDFilter
{
   public:
      explicit RHTotalEnergyCut(const edm::ParameterSet&);
      ~RHTotalEnergyCut();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double minimum;
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
RHTotalEnergyCut::RHTotalEnergyCut(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimum = iConfig.getUntrackedParameter<double>("minimum", 85);
   vlsbModule = iConfig.getUntrackedParameter<std::string>("vlsbModule", "");
   normalModule = iConfig.getUntrackedParameter<std::string>("normalModule", "");
}


RHTotalEnergyCut::~RHTotalEnergyCut()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RHTotalEnergyCut::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

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

         totalenergy = totalenergy + energy;
      }
   }

   if(totalenergy < minimum)
      return false;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RHTotalEnergyCut::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RHTotalEnergyCut::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(RHTotalEnergyCut);
