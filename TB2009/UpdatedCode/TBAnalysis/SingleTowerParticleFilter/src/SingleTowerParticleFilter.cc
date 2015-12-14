// -*- C++ -*-
//
// Package:    SingleTowerParticleFilter
// Class:      SingleTowerParticleFilter
// 
/**\class SingleTowerParticleFilter SingleTowerParticleFilter.cc TBAnalysis/SingleTowerParticleFilter/src/SingleTowerParticleFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Jul 30 10:35:24 CEST 2009
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
#include "TBDataFormats/HcalTBObjects/interface/HcalTBBeamCounters.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBEventPosition.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBTiming.h"

//
// class declaration
//

class SingleTowerParticleFilter : public edm::EDFilter
{
   public:
      explicit SingleTowerParticleFilter(const edm::ParameterSet&);
      ~SingleTowerParticleFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      int particleNumber;
      bool useD;
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
SingleTowerParticleFilter::SingleTowerParticleFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   particleNumber = iConfig.getUntrackedParameter<int>("particleNumber", 1);
   std::cout << "[SingleTowerParticleFilter][SingleTowerParticleFilter] particle number = " << particleNumber << std::endl;
   useD = iConfig.getUntrackedParameter<bool>("useD", false);
}


SingleTowerParticleFilter::~SingleTowerParticleFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
SingleTowerParticleFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // for now, require that there is one hit in chamber A, B, C
   edm::Handle<HcalTBTriggerData> trigger;
   edm::Handle<HcalTBBeamCounters> qadc;
   edm::Handle<HcalTBEventPosition> epos;
   edm::Handle<HcalTBTiming> time;

   iEvent.getByType(trigger);
   iEvent.getByType(qadc);
   iEvent.getByType(epos);
   iEvent.getByType(time);

   std::vector<double> Ax;
   std::vector<double> Ay;
   std::vector<double> Bx;
   std::vector<double> By;
   std::vector<double> Cx;
   std::vector<double> Cy;
   std::vector<double> Dx;
   std::vector<double> Dy;

   epos->getChamberHits('A', Ax, Ay);
   epos->getChamberHits('B', Bx, By);
   epos->getChamberHits('C', Cx, Cy);
   epos->getChamberHits('D', Dx, Dy);

   if(useD == false)
   {
      if((int)Ax.size() == particleNumber && (int)Ay.size() == particleNumber &&
         (int)Bx.size() == particleNumber && (int)By.size() == particleNumber &&
         (int)Cx.size() == particleNumber && (int)Cy.size() == particleNumber)
         return true;
      else
         return false;
   }
   else
   {
      if((int)Ax.size() == particleNumber && (int)Ay.size() == particleNumber &&
         (int)Bx.size() == particleNumber && (int)By.size() == particleNumber &&
         (int)Cx.size() == particleNumber && (int)Cy.size() == particleNumber &&
         (int)Dx.size() == particleNumber && (int)Dy.size() == particleNumber)
         return true;
      else
         return false;
   }

   return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
SingleTowerParticleFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTowerParticleFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(SingleTowerParticleFilter);
