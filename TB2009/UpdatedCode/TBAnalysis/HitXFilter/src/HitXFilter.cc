// -*- C++ -*-
//
// Package:    HitXFilter
// Class:      HitXFilter
// 
/**\class HitXFilter HitXFilter.cc TBAnalysis/HitXFilter/src/HitXFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Fri Aug 28 11:28:18 CEST 2009
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

class HitXFilter : public edm::EDFilter
{
   public:
      explicit HitXFilter(const edm::ParameterSet&);
      ~HitXFilter();

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
HitXFilter::HitXFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   maximum = iConfig.getUntrackedParameter<double>("maximum", 10000);
}


HitXFilter::~HitXFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HitXFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   if(hVlsbInfo->hitPosition[0] > maximum)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
HitXFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HitXFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(HitXFilter);
