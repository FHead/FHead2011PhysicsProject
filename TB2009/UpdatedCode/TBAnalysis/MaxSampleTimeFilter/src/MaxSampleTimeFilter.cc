// -*- C++ -*-
//
// Package:    MaxSampleTimeFilter
// Class:      MaxSampleTimeFilter
// 
/**\class MaxSampleTimeFilter MaxSampleTimeFilter.cc TBAnalysis/MaxSampleTimeFilter/src/MaxSampleTimeFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Sep  3 14:14:17 CEST 2009
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

class MaxSampleTimeFilter : public edm::EDFilter {
   public:
      explicit MaxSampleTimeFilter(const edm::ParameterSet&);
      ~MaxSampleTimeFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
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
MaxSampleTimeFilter::MaxSampleTimeFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

}


MaxSampleTimeFilter::~MaxSampleTimeFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MaxSampleTimeFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MaxSampleTimeFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MaxSampleTimeFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MaxSampleTimeFilter);
