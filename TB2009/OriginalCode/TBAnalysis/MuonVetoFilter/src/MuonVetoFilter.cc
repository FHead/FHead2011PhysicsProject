// -*- C++ -*-
//
// Package:    MuonVetoFilter
// Class:      MuonVetoFilter
// 
/**\class MuonVetoFilter MuonVetoFilter.cc TBAnalysis/MuonVetoFilter/src/MuonVetoFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug 20 17:40:18 CEST 2009
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

#include "TBDataFormats/HcalTBObjects/interface/HcalTBBeamCounters.h"

//
// class declaration
//

class MuonVetoFilter : public edm::EDFilter
{
   public:
      explicit MuonVetoFilter(const edm::ParameterSet&);
      ~MuonVetoFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double maximum;
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
MuonVetoFilter::MuonVetoFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   maximum = iConfig.getUntrackedParameter<double>("maximum", 150);
}


MuonVetoFilter::~MuonVetoFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MuonVetoFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBBeamCounters> qadc;
   iEvent.getByType(qadc);

   if(qadc->VMBadc() > maximum)
      return false;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MuonVetoFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonVetoFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonVetoFilter);
