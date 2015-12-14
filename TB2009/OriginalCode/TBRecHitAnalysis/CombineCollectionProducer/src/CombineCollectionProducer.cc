// -*- C++ -*-
//
// Package:    CombineCollectionProducer
// Class:      CombineCollectionProducer
// 
/**\class CombineCollectionProducer CombineCollectionProducer.cc TBRecHitAnalysis/CombineCollectionProducer/src/CombineCollectionProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Tue Sep  1 16:18:38 CEST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <map>
#include <string>
#include <fstream>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

//
// class decleration
//

class CombineCollectionProducer : public edm::EDProducer
{
   public:
      explicit CombineCollectionProducer(const edm::ParameterSet&);
      ~CombineCollectionProducer();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      std::map<int, double> interCalibration;
      std::string interCalibrationFileName;

      std::string normalModuleName;
      std::string vlsbModuleName;

      bool doParameterization;
      double ParameterizationCorrection(double energy, double eOverH);
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
CombineCollectionProducer::CombineCollectionProducer(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<HBHERecHitCollection>();

   //now do what ever other initialization is needed
   interCalibrationFileName = iConfig.getUntrackedParameter<std::string>("interCalibration", "");

   normalModuleName = iConfig.getUntrackedParameter<std::string>("normalModule", "");
   vlsbModuleName = iConfig.getUntrackedParameter<std::string>("vlsbModule", "");

   doParameterization = iConfig.getUntrackedParameter<bool>("parameterizationCorrection", false);
}


CombineCollectionProducer::~CombineCollectionProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CombineCollectionProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::auto_ptr<HBHERecHitCollection> pHits(new HBHERecHitCollection);

   if(normalModuleName != "")
   {
      edm::Handle<HBHERecHitCollection> hNormalData;
      iEvent.getByLabel(normalModuleName, hNormalData);

      for(HBHERecHitCollection::const_iterator iter = hNormalData->begin(); iter != hNormalData->end(); iter++)
      {
         double newenergy = iter->energy();
         if(interCalibration.find(iter->id().ieta() * 1000 + iter->id().iphi()) != interCalibration.end())
            newenergy = iter->energy() * interCalibration[iter->id().ieta()*1000+iter->id().iphi()];

         if(doParameterization == true)
            newenergy = ParameterizationCorrection(newenergy, 1.4);

         HBHERecHit hit(iter->id(), newenergy, iter->time());

         pHits->push_back(hit);
      }
   }

   if(vlsbModuleName != "")
   {
      edm::Handle<HBHERecHitCollection> hVlsbData;
      iEvent.getByLabel(vlsbModuleName, "VLSB", hVlsbData);

      for(HBHERecHitCollection::const_iterator iter = hVlsbData->begin(); iter != hVlsbData->end(); iter++)
      {
         double newenergy = iter->energy();
         if(interCalibration.find(iter->id().ieta() * 1000 + iter->id().iphi()) != interCalibration.end())
            newenergy = iter->energy() * interCalibration[iter->id().ieta()*1000+iter->id().iphi()];

         if(doParameterization == true)
            newenergy = ParameterizationCorrection(newenergy, 1.4);

         HBHERecHit hit(iter->id(), newenergy, iter->time());

         pHits->push_back(hit);
      }
   }

   edm::Handle<HBHERecHitCollection> hVlsbData;

   iEvent.put(pHits);
}

// ------------ method called once each job just before starting event loop  ------------
void 
CombineCollectionProducer::beginJob(const edm::EventSetup&)
{
   if(interCalibrationFileName != "")
   {
      std::ifstream in(interCalibrationFileName.c_str());

      while(in)
      {
         int iphi = -1;
         int ieta = -1;
         double constant = 0;

         in >> iphi >> ieta >> constant;

         if(iphi < 0)   // which should not happen....
            continue;

         interCalibration.insert(std::pair<int, double>(ieta * 1000 + iphi, constant));
      }

      in.close();
   }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CombineCollectionProducer::endJob()
{
}

double CombineCollectionProducer::ParameterizationCorrection(double energy, double eOverH)
{
   if(energy <= 1)
      return energy;

   double pie = 1;

   if(energy >= 8)
      pie = (1 + (eOverH - 1) * 0.1 * std::log(energy)) / eOverH;
   else
      pie = 0.179 * std::log(energy) + 0.413;

   return energy / pie;
}

//define this as a plug-in
DEFINE_FWK_MODULE(CombineCollectionProducer);
