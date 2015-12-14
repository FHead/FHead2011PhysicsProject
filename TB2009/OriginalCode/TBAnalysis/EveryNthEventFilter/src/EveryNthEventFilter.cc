// -*- C++ -*-
//
// Package:    EveryNthEventFilter
// Class:      EveryNthEventFilter
// 
/**\class EveryNthEventFilter EveryNthEventFilter.cc TBAnalysis/EveryNthEventFilter/src/EveryNthEventFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Fri Aug 21 11:07:07 CEST 2009
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

//
// class declaration
//

class EveryNthEventFilter : public edm::EDFilter
{
   public:
      explicit EveryNthEventFilter(const edm::ParameterSet&);
      ~EveryNthEventFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      int N;
      int offset;
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
EveryNthEventFilter::EveryNthEventFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   N = iConfig.getUntrackedParameter<int>("N", 4);
   offset = iConfig.getUntrackedParameter<int>("offset", 0);

   offset = offset % N;
}


EveryNthEventFilter::~EveryNthEventFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
EveryNthEventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   if(iEvent.id().event() % N != offset)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
EveryNthEventFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EveryNthEventFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(EveryNthEventFilter);
