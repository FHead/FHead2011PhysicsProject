// -*- C++ -*-
//
// Package:    ExportChargeAnalyzer
// Class:      ExportChargeAnalyzer
// 
/**\class ExportChargeAnalyzer ExportChargeAnalyzer.cc TBRecHitAnalysis/ExportChargeAnalyzer/src/ExportChargeAnalyzer.cc

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

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "TNtuple.h"
#include "TFile.h"

//
// class decleration
//

class ExportChargeAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit ExportChargeAnalyzer(const edm::ParameterSet&);
      ~ExportChargeAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TNtuple *allData;
      std::string normalModule;
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
ExportChargeAnalyzer::ExportChargeAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "AllCharges.root");

   normalModule = iConfig.getUntrackedParameter<std::string>("normalModule", "");

   toweronly = iConfig.getUntrackedParameter<bool>("toweronly", false);
   simplified = iConfig.getUntrackedParameter<bool>("simplified", true);
   sidetowersimplified = iConfig.getUntrackedParameter<bool>("sidetowersimplified", false);

   outputFile = new TFile(outputFileName.c_str(), "RECREATE");
   allData = NULL;

   exportVlsb = iConfig.getUntrackedParameter<bool>("exportVlsb", true);
}


ExportChargeAnalyzer::~ExportChargeAnalyzer()
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
ExportChargeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double normalTowerEnergy[3][3] = {{0}};
   double normalChannelEnergy[3][3][4] = {{{0}}};

   if(normalModule.size() != 0)
   {
      edm::Handle<HBHERecHitCollection> hNormalData;
      iEvent.getByLabel(normalModule, hNormalData);

      // std::cout << hNormalData->size() << std::endl;

      if(hNormalData->size() != 32 && hNormalData->size() != 64)   // 64: not our run, 32: our run
         return;

      for(HBHERecHitCollection::const_iterator iter = hNormalData->begin(); iter != hNormalData->end(); iter++)
      {
         double energy = iter->energy();

         int ieta = iter->id().ieta();

         int iphi = iter->id().iphi();
         int layergroup = iphi / 10 - 1;
         iphi = iphi % 10;

         if(iphi != 2 && iphi != 4)   // not of interest to us
            continue;
         if(ieta < 7 || ieta > 9)   // not of interest to us
            continue;
         if(layergroup >= 4 || layergroup < 0)   // what.....
            continue;

         int iPhiIndex = iphi - 2;
         int iEtaIndex = ieta - 7;

         normalTowerEnergy[iPhiIndex][iEtaIndex] = normalTowerEnergy[iPhiIndex][iEtaIndex] + energy;
         normalChannelEnergy[iPhiIndex][iEtaIndex][layergroup] = energy;
      }
   }

   // All-layer readout
   double vlsbcharges[4][16] = {{0}};
   double vlsbtowercharge[4] = {0};

   double beamenergy = 0;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   edm::Handle<VLSBInformation> hVlsbInfo;

   if(exportVlsb == true)
   {
      iEvent.getByType(hVlsbData);
      iEvent.getByType(hVlsbInfo);

      beamenergy = hVlsbInfo->beamEnergy;
 
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
            continue;

         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         {
            // if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            //    continue;

            for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
            {
               double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
               adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
               adc = adc / hVlsbInfo->mip[iMotherBoard][iChannel];

               vlsbcharges[iMotherBoard][iChannel] = vlsbcharges[iMotherBoard][iChannel] + adc;
               vlsbtowercharge[iMotherBoard] = vlsbtowercharge[iMotherBoard] + adc;
            }
         }
      }
   }

   // print output
   std::cout << "[ExportCharge] " << iEvent.id().event();

   std::cout << " " << beamenergy;

   if(toweronly == true)
   {
      for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
      {
         for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         {
            if(iPhiIndex != 1)
               std::cout << " " << normalTowerEnergy[iPhiIndex][iEtaIndex];
            else
            {
               if(exportVlsb == true)
               {
                  int iMotherBoard = 0;
                  if(iEtaIndex == 0)
                     iMotherBoard = 1;
                  else if(iEtaIndex == 1)
                     iMotherBoard = 0;
                  else
                     iMotherBoard = 3;

                  std::cout << " " << vlsbtowercharge[iMotherBoard];
               }
               else
                  std::cout << " 0";
            }
         }
      }

      if(exportVlsb == true)
      {
         std::cout << " " << hVlsbInfo->hitPosition[0] << " " << hVlsbInfo->hitPosition[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[0];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[2];
      }
      else
         std::cout << " 0 0 0 0 0";
   }
   else if(simplified == true)
   {
      for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)   // normal readout (side towers)
      {
         if(iPhiIndex == 1)
            continue;

         for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
            std::cout << " " << normalTowerEnergy[iPhiIndex][iEtaIndex];
      }

      if(exportVlsb == true)
      {
         for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)   // all-layer readout (iphi = 3)
         {
            if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
               continue;

            if(hVlsbInfo->motherBoardEta[iMotherBoard] == 7)
               std::cout << " " << vlsbtowercharge[iMotherBoard];
            else
               for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
                  std::cout << " " << vlsbcharges[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]];
         }
      }
   }
   else if(sidetowersimplified == true)
   {
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         std::cout << " " << normalChannelEnergy[0][iEtaIndex][0] + normalChannelEnergy[0][iEtaIndex][1] + normalChannelEnergy[0][iEtaIndex][0] + normalChannelEnergy[0][iEtaIndex][3];

      for(int ieta = 7; ieta <= 9; ieta++)
      {
         int iMotherBoard = 0;
         if(ieta == 7)
            iMotherBoard = 1;
         else if(ieta == 8)
            iMotherBoard = 0;
         else
            iMotherBoard = 3;

         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
         {
            if(exportVlsb == true)
               std::cout << " " << vlsbcharges[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]];
            else
               std::cout << " " << 0;
         }
      }

      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         std::cout << " " << normalChannelEnergy[2][iEtaIndex][0] + normalChannelEnergy[2][iEtaIndex][1] + normalChannelEnergy[2][iEtaIndex][2] + normalChannelEnergy[2][iEtaIndex][3];

      if(exportVlsb == true)
      {
         std::cout << " " << hVlsbInfo->hitPosition[0] << " " << hVlsbInfo->hitPosition[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[0];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[2];
      }
      else
         std::cout << " 0 0 0 0 0";
   }
   else
   {
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int layergroup = 0; layergroup < 4; layergroup++)
            std::cout << " " << normalChannelEnergy[0][iEtaIndex][layergroup];

      for(int ieta = 7; ieta <= 9; ieta++)
      {
         int iMotherBoard = 0;
         if(ieta == 7)
            iMotherBoard = 1;
         else if(ieta == 8)
            iMotherBoard = 0;
         else
            iMotherBoard = 3;

         for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
         {
            if(exportVlsb == true)
               std::cout << " " << vlsbcharges[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]];
            else
               std::cout << " " << 0;
         }
      }

      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int layergroup = 0; layergroup < 4; layergroup++)
            std::cout << " " << normalChannelEnergy[2][iEtaIndex][layergroup];

      if(exportVlsb == true)
      {
         std::cout << " " << hVlsbInfo->hitPosition[0] << " " << hVlsbInfo->hitPosition[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[0];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[1];
         std::cout << " " << hVlsbInfo->wireChamberHitsDistance2[2];
      }
      else
         std::cout << " 0 0 0 0 0";
   }

   std::cout << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
ExportChargeAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ExportChargeAnalyzer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(ExportChargeAnalyzer);
