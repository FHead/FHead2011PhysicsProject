// -*- C++ -*-
//
// Package:    PulseTimeFilter
// Class:      PulseTimeFilter
// 
/**\class PulseTimeFilter PulseTimeFilter.cc TBAnalysis/PulseTimeFilter/src/PulseTimeFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Sep  3 11:47:47 CEST 2009
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

#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

//
// class declaration
//

class PulseTimeFilter : public edm::EDFilter
{
   public:
      explicit PulseTimeFilter(const edm::ParameterSet&);
      ~PulseTimeFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double minimumTime;   // in units of samples
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
PulseTimeFilter::PulseTimeFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimumTime = iConfig.getUntrackedParameter<double>("minimum", 9);
}


PulseTimeFilter::~PulseTimeFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
PulseTimeFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   if(hVlsbInfo->time < minimumTime)
      return false;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
PulseTimeFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PulseTimeFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(PulseTimeFilter);
