// -*- C++ -*-
//
// Package:    FirstClusterTimeFilter
// Class:      FirstClusterTimeFilter
// 
/**\class FirstClusterTimeFilter FirstClusterTimeFilter.cc TBAnalysis/FirstClusterTimeFilter/src/FirstClusterTimeFilter.cc

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

#include "TBAnalysis/ShowerCluster/interface/ShowerCluster.h"

//
// class declaration
//

class FirstClusterTimeFilter : public edm::EDFilter
{
   public:
      explicit FirstClusterTimeFilter(const edm::ParameterSet&);
      ~FirstClusterTimeFilter();

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
FirstClusterTimeFilter::FirstClusterTimeFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   minimumTime = iConfig.getUntrackedParameter<double>("minimum", 9);
}


FirstClusterTimeFilter::~FirstClusterTimeFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FirstClusterTimeFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<std::vector<ShowerCluster> > hClusters;
   iEvent.getByType(hClusters);

   if(hClusters->size() == 0)
      return false;

   double maxenergy = hClusters->at(0).energy;
   int maxenergyindex = 0;

   for(int i = 1; i < (int)hClusters->size(); i++)
   {
      if(hClusters->at(i).energy > maxenergy)
      {
         maxenergy = hClusters->at(i).energy;
         maxenergyindex = i;
      }
   }

   if(hClusters->at(maxenergyindex).time < minimumTime)
      return false;

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FirstClusterTimeFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FirstClusterTimeFilter::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(FirstClusterTimeFilter);
