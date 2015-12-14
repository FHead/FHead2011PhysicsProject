// -*- C++ -*-
//
// Package:    DumpAdcToNtuple
// Class:      DumpAdcToNtuple
// 
/**\class DumpAdcToNtuple DumpAdcToNtuple.cc TBAnalysis/DumpAdcToNtuple/src/DumpAdcToNtuple.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Tue Jul 28 21:41:41 CEST 2009
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

#include "TBDataFormats/HcalTBObjects/interface/HcalTBTriggerData.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"

#include "TFile.h"
#include "TNtuple.h"

//
// class decleration
//

class DumpAdcToNtuple : public edm::EDAnalyzer
{
   public:
      explicit DumpAdcToNtuple(const edm::ParameterSet&);
      ~DumpAdcToNtuple();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TNtuple *dataTree;
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
DumpAdcToNtuple::DumpAdcToNtuple(const edm::ParameterSet& iConfig)
{
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("Output", "output.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   dataTree = new TNtuple("ADCValues", "Raw ADC Values", "Event:Motherboard:Channel:Sample:Adc:BeamTrigger");
}


DumpAdcToNtuple::~DumpAdcToNtuple()
{
   delete dataTree;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DumpAdcToNtuple::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // get event number
   static int eventNumber = -1;
   eventNumber = eventNumber + 1;

   // check is it is beam trigger
   edm::Handle<HcalTBTriggerData> hHcalTBTriggerData;
   iEvent.getByType(hHcalTBTriggerData);

   bool beamTrigger = false;
   if(hHcalTBTriggerData->wasBeamTrigger() == true)
      beamTrigger = true;

   // now fill all data in
   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);

            if(beamTrigger == true)
               dataTree->Fill(eventNumber, iMotherBoard, iChannel, iSample, adc, 1);
            else
               dataTree->Fill(eventNumber, iMotherBoard, iChannel, iSample, adc, 0);
         }
      }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
DumpAdcToNtuple::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DumpAdcToNtuple::endJob()
{
   outputFile->cd();
   dataTree->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(DumpAdcToNtuple);
