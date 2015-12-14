// -*- C++ -*-
//
// Package:    TriggerFilter
// Class:      TriggerFilter
// 
/**\class TriggerFilter TriggerFilter.cc TBAnalysis/TriggerFilter/src/TriggerFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug  6 09:12:37 CEST 2009
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

//
// class declaration
//

class TriggerFilter : public edm::EDFilter
{
   public:
      explicit TriggerFilter(const edm::ParameterSet&);
      ~TriggerFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      bool allowBeamTrigger;
      bool allowOutOfSpillPedestalTrigger;
      bool allowOthers;
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
TriggerFilter::TriggerFilter(const edm::ParameterSet& iConfig)
{
   allowBeamTrigger = iConfig.getUntrackedParameter<bool>("allowBeamTrigger", true);
   allowOutOfSpillPedestalTrigger = iConfig.getUntrackedParameter<bool>("allowOutOfSpillPedestalTrigger", false);
   allowOthers = iConfig.getUntrackedParameter<bool>("allowOthers", false);
}


TriggerFilter::~TriggerFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBTriggerData> trigger_data;
   iEvent.getByType(trigger_data);

   if(trigger_data->wasBeamTrigger() && allowBeamTrigger == false)
      return false;
   else if(trigger_data->wasBeamTrigger() && allowBeamTrigger == true)
      return true;
   else if(trigger_data->wasOutSpillPedestalTrigger() && allowOutOfSpillPedestalTrigger == false)
      return false;
   else if(trigger_data->wasOutSpillPedestalTrigger() && allowOutOfSpillPedestalTrigger == true)
      return true;

   if(allowOthers == false)
      return false;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFilter);
