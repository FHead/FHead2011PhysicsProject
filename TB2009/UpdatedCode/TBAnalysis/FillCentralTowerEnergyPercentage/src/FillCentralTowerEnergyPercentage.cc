// -*- C++ -*-
//
// Package:    FillCentralTowerEnergyPercentage
// Class:      FillCentralTowerEnergyPercentage
// 
/**\class FillCentralTowerEnergyPercentage FillCentralTowerEnergyPercentage.cc TBAnalysis/FillCentralTowerEnergyPercentage/src/FillCentralTowerEnergyPercentage.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Sun Aug  9 17:00:44 CEST 2009
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
#include "TH1D.h"
#include "TNtuple.h"

//
// class decleration
//

class FillCentralTowerEnergyPercentage : public edm::EDAnalyzer
{
   public:
      explicit FillCentralTowerEnergyPercentage(const edm::ParameterSet&);
      ~FillCentralTowerEnergyPercentage();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TH1D *percentage_7_789;
      TH1D *percentage_8_789;
      TH1D *percentage_9_789;
      TH1D *percentage_89_789;
      bool zeroSuppress;
      TNtuple *data;
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
FillCentralTowerEnergyPercentage::FillCentralTowerEnergyPercentage(const edm::ParameterSet& iConfig)
{
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "EnergyPercentage.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");
   zeroSuppress = iConfig.getUntrackedParameter<bool>("zeroSuppress", true);

   percentage_7_789 = new TH1D("Percentage_7_789",
      "Percentage of energy in tower ieta 7 compared to all 3 towers", 100, 0, 1);
   percentage_8_789 = new TH1D("Percentage_8_789",
      "Percentage of energy in central tower compared to all 3 towers", 100, 0, 1);
   percentage_9_789 = new TH1D("Percentage_9_789",
      "Percentage of energy in tower ieta 9 compared to all 3 towers", 100, 0, 1);
   percentage_89_789 = new TH1D("Percentage_89_789",
      "Percentage of energy in tower 8 & 9 compared to all 3 towers", 100, 0, 1);

   data = new TNtuple("Data", "Data", "Event:Percentage7:Percentage8:Percentage9:HitX:HitY:DistanceA:DistanceB:DistanceC");
}


FillCentralTowerEnergyPercentage::~FillCentralTowerEnergyPercentage()
{
   delete data;
   delete percentage_7_789;
   delete percentage_8_789;
   delete percentage_9_789;
   delete percentage_89_789;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillCentralTowerEnergyPercentage::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double rightenergy = 0;
   double centralenergy = 0;
   double leftenergy = 0;
   double allenergy = 0;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      double energy = 0;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            energy = energy + adc / hVlsbInfo->mip[iMotherBoard][iChannel];
         }
      }

      if(energy < 0 && zeroSuppress == true)
         continue;

      if(iMotherBoard == 0)
         centralenergy = centralenergy + energy;
      if(iMotherBoard == 3)
         rightenergy = rightenergy + energy;
      if(iMotherBoard == 1)
         leftenergy = leftenergy + energy;
      allenergy = allenergy + energy;
   }

   if(allenergy < 1e-10)
   {
      // std::cout << iEvent.id().event() << " " << centralenergy << " " << allenergy << std::endl;
      percentage_8_789->Fill(0);
      data->Fill(iEvent.id().event(), 0, 0, 0,
         hVlsbInfo->hitPosition[0], hVlsbInfo->hitPosition[1],
         hVlsbInfo->wireChamberHitsDistance2[0], hVlsbInfo->wireChamberHitsDistance2[1], hVlsbInfo->wireChamberHitsDistance2[2]);
   }
   else
   {
      percentage_7_789->Fill(leftenergy / allenergy);
      percentage_8_789->Fill(centralenergy / allenergy);
      percentage_9_789->Fill(rightenergy / allenergy);
      percentage_89_789->Fill((rightenergy + centralenergy) / allenergy);
      data->Fill(iEvent.id().event(), leftenergy / allenergy, centralenergy / allenergy, rightenergy / allenergy,
         hVlsbInfo->hitPosition[0], hVlsbInfo->hitPosition[1],
         hVlsbInfo->wireChamberHitsDistance2[0], hVlsbInfo->wireChamberHitsDistance2[1], hVlsbInfo->wireChamberHitsDistance2[2]);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillCentralTowerEnergyPercentage::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillCentralTowerEnergyPercentage::endJob()
{
   outputFile->cd();
   percentage_7_789->Write();
   percentage_8_789->Write();
   percentage_9_789->Write();
   percentage_89_789->Write();
   data->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillCentralTowerEnergyPercentage);
