// -*- C++ -*-
//
// Package:    FillExtrapolatedHitPointAnalyzer
// Class:      FillExtrapolatedHitPointAnalyzer
// 
/**\class FillExtrapolatedHitPointAnalyzer FillExtrapolatedHitPointAnalyzer.cc TBAnalysis/FillExtrapolatedHitPointAnalyzer/src/FillExtrapolatedHitPointAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug 27 17:22:38 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

#include "TFile.h"
#include "TNtuple.h"

//
// class decleration
//

class FillExtrapolatedHitPointAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillExtrapolatedHitPointAnalyzer(const edm::ParameterSet&);
      ~FillExtrapolatedHitPointAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TNtuple *datatree;
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
FillExtrapolatedHitPointAnalyzer::FillExtrapolatedHitPointAnalyzer(const edm::ParameterSet& iConfig)
{
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "HitPosition.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   datatree = new TNtuple("data", "data", "Event:HitX:HitY:DistanceA:DistanceB:DistanceC");
}


FillExtrapolatedHitPointAnalyzer::~FillExtrapolatedHitPointAnalyzer()
{
   delete datatree;

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillExtrapolatedHitPointAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   datatree->Fill(iEvent.id().event(), hVlsbInfo->hitPosition[0], hVlsbInfo->hitPosition[1],
      hVlsbInfo->wireChamberHitsDistance2[0], hVlsbInfo->wireChamberHitsDistance2[1], hVlsbInfo->wireChamberHitsDistance2[2]);
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillExtrapolatedHitPointAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillExtrapolatedHitPointAnalyzer::endJob()
{
   outputFile->cd();
   datatree->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillExtrapolatedHitPointAnalyzer);
