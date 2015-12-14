// -*- C++ -*-
//
// Package:    RHMergeCollectionProducer
// Class:      RHMergeCollectionProducer
// 
/**\class RHMergeCollectionProducer RHMergeCollectionProducer.cc TBRecHitAnalysis/RHMergeCollectionProducer/src/RHMergeCollectionProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Tue Aug 25 20:58:24 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


using std::string;
using std::cout;
using std::endl;

//
// class decleration
//

class RHMergeCollectionProducer : public edm::EDProducer
{
   public:
      explicit RHMergeCollectionProducer(const edm::ParameterSet&);
      ~RHMergeCollectionProducer();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      string normalModule;
      string vlsbModule;
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
RHMergeCollectionProducer::RHMergeCollectionProducer(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
*/
   //now do what ever other initialization is needed
  
}


RHMergeCollectionProducer::~RHMergeCollectionProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RHMergeCollectionProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(pOut);
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
RHMergeCollectionProducer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RHMergeCollectionProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RHMergeCollectionProducer);
