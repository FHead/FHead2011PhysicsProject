// -*- C++ -*-
//
// Package:    CExportChargeAnalyzer
// Class:      CExportChargeAnalyzer
// 
/**\class CExportChargeAnalyzer CExportChargeAnalyzer.cc TBRecHitAnalysis/CExportChargeAnalyzer/src/CExportChargeAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Mon Aug 24 19:23:48 CEST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include "TBAnalysis/RunInformation/interface/RunInformation.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "TNtuple.h"
#include "TFile.h"

//
// class decleration
//

class CExportChargeAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit CExportChargeAnalyzer(const edm::ParameterSet&);
      ~CExportChargeAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TNtuple *allData;
      std::string moduleName;
      bool toweronly;
      bool simplified;
      bool sidetowersimplified;
      bool exportVlsb;
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
CExportChargeAnalyzer::CExportChargeAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "AllCharges.root");

   moduleName = iConfig.getUntrackedParameter<std::string>("moduleName", "");

   toweronly = iConfig.getUntrackedParameter<bool>("toweronly", false);
   simplified = iConfig.getUntrackedParameter<bool>("simplified", true);
   sidetowersimplified = iConfig.getUntrackedParameter<bool>("sidetowersimplified", false);

   exportVlsb = iConfig.getUntrackedParameter<bool>("exportVlsb", true);

   outputFile = new TFile(outputFileName.c_str(), "RECREATE");
   allData = NULL;
}


CExportChargeAnalyzer::~CExportChargeAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
CExportChargeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double towerEnergy[3][3] = {{0}};
   double normalChannelEnergy[3][3][4] = {{{0}}};
   double vlsbChannelEnergy[3][16] = {{0}};

   edm::Handle<HBHERecHitCollection> hData;
   iEvent.getByLabel(moduleName, hData);

   for(HBHERecHitCollection::const_iterator iter = hData->begin(); iter != hData->end(); iter++)
   {
      double energy = iter->energy();

      int ieta = iter->id().ieta();

      int iphi = iter->id().iphi();
      int layergroup = 0;

      if(iphi >= 50)
      {
         layergroup = iphi - 50;
         iphi = 3;
      }
      else
      {
         layergroup = iphi / 10 - 1;
         iphi = iphi % 10;
      }

      if(iphi < 2 || iphi > 4)   // not of interest to us
         continue;
      if(ieta < 7 || ieta > 9)   // not of interest to us
         continue;
      if(iphi == 3 && (layergroup > 15 || layergroup < 0))
         continue;
      if(iphi != 3 && (layergroup >= 4 || layergroup < 0))
         continue;

      int iPhiIndex = iphi - 2;
      int iEtaIndex = ieta - 7;

      towerEnergy[iPhiIndex][iEtaIndex] = towerEnergy[iPhiIndex][iEtaIndex] + energy;
      if(iphi != 3)
         normalChannelEnergy[iPhiIndex][iEtaIndex][layergroup] = energy;
      else
         vlsbChannelEnergy[iEtaIndex][layergroup] = energy;
   }

   edm::Handle<VLSBInformation> hVlsbInfo;
   if(exportVlsb == true)
      iEvent.getByType(hVlsbInfo);

   edm::Handle<RunInformation> hRunInfo;
   iEvent.getByType(hRunInfo);

   // print output
   std::cout << "[CExportCharge] " << iEvent.id().event();

   std::cout << " " << hRunInfo->beamEnergy;

   if(toweronly == true)
   {
      for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
         for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
            std::cout << " " << towerEnergy[iPhiIndex][iEtaIndex];

      std::cout << " " << hRunInfo->hitPosition[0] << " " << hRunInfo->hitPosition[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[0];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[2];
   }
   else if(simplified == true)
   {
      for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)   // normal readout (side towers)
      {
         if(iPhiIndex == 1)
            continue;

         for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
            std::cout << " " << towerEnergy[iPhiIndex][iEtaIndex];
      }

      if(exportVlsb == true)
      {
         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
            std::cout << " " << vlsbChannelEnergy[1][iLayer];

         std::cout << " " << towerEnergy[1][0];

         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
            std::cout << " " << vlsbChannelEnergy[2][iLayer];
      }
   }
   else if(sidetowersimplified == true)
   {
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         std::cout << " " << towerEnergy[0][iEtaIndex];

      for(int ieta = 7; ieta <= 9; ieta++)
      {
         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
         {
            if(exportVlsb == true)
               std::cout << " " << vlsbChannelEnergy[ieta-7][iLayer];
            else
               std::cout << " " << 0;
         }
      }

      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         std::cout << " " << towerEnergy[2][iEtaIndex];

      std::cout << " " << hRunInfo->hitPosition[0] << " " << hRunInfo->hitPosition[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[0];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[2];
   }
   else
   {
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int layergroup = 0; layergroup < 4; layergroup++)
            std::cout << " " << normalChannelEnergy[0][iEtaIndex][layergroup];

      for(int ieta = 7; ieta <= 9; ieta++)
      {
         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
         {
            if(exportVlsb == true)
               std::cout << " " << vlsbChannelEnergy[ieta-7][iLayer];
            else
               std::cout << " " << 0;
         }
      }

      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int layergroup = 0; layergroup < 4; layergroup++)
            std::cout << " " << normalChannelEnergy[2][iEtaIndex][layergroup];

      std::cout << " " << hRunInfo->hitPosition[0] << " " << hRunInfo->hitPosition[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[0];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[1];
      std::cout << " " << hRunInfo->wireChamberHitsDistance2[2];
   }

   std::cout << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
CExportChargeAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CExportChargeAnalyzer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CExportChargeAnalyzer);
