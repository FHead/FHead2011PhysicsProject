// -*- C++ -*-
//
// Package:    FillAverageChargeLayerAnalyzer
// Class:      FillAverageChargeLayerAnalyzer
// 
/**\class FillAverageChargeLayerAnalyzer FillAverageChargeLayerAnalyzer.cc TBAnalysis/FillAverageChargeLayerAnalyzer/src/FillAverageChargeLayerAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Jul 30 10:39:40 CEST 2009
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

#include "TGraph.h"
#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"

//
// class decleration
//

class FillAverageChargeLayerAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillAverageChargeLayerAnalyzer(const edm::ParameterSet&);
      ~FillAverageChargeLayerAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TH2D *averageChargeLayerHistogram;              // average charge vs. layer & motherboard
      TH1D *totalChargeHistogram;                     // distribution of total charge
      TH1D *centralTowerChargeLayer;                  // average charge vs. layer in motherboard 0
      TH1D *eta89TowerChargeLayer;                    // average charge vs. layer in motherboard 0 & 3
      TH1D *totalChargeSingleLayerHistogram[4][16];   // distribution of charge of channels
      TGraph *chargeVsEventNum[4][16];                // total charge/energy evolution in channels
      TFile *outputFile;
      bool doTextOutput;
      int channelToLayer[16];
      int eventCount;
      bool doMissingChannelInterpolate;
      int layerToChannel[16];
      bool doChargeEvent;
      bool useMIP;
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
FillAverageChargeLayerAnalyzer::FillAverageChargeLayerAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   averageChargeLayerHistogram = new TH2D("AverageChargeLayer", "Average total charge;Mother Board;Layer;Average total energy", 4, -0.5, 3.5, 16, -0.5, 15.5);
   totalChargeHistogram = new TH1D("TotalCharge", "Total charge;Energy;", 240000, -1000, 50000);
   eta89TowerChargeLayer = new TH1D("Eta89TowerChargeLayer", "Average total charge in two towers;Layer;Energy", 16, -0.5, 15.5);
   centralTowerChargeLayer = new TH1D("CentralTowerChargeLayer", "Average total charge;Layer;Energy", 16, -0.5, 15.5);

   useMIP = iConfig.getUntrackedParameter<bool>("useMIP", true);

   doTextOutput = iConfig.getUntrackedParameter<bool>("textOutput", false);
   doMissingChannelInterpolate = iConfig.getUntrackedParameter<bool>("interpolate", false);
   doChargeEvent = iConfig.getUntrackedParameter<bool>("chargeVsEvent", false);

   for(int i = 0; i < 15; i++)
   {
      channelToLayer[i] = i + 1;
      layerToChannel[i+1] = i;
   }
   channelToLayer[15] = 0;
   layerToChannel[0] = 15;

   eventCount = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         TString name = Form("ChargeDistribution_%d_%d", iMotherBoard, channelToLayer[iChannel]);
         TString title = Form("Charge (Motherboard %d, layer %d);Charge;",
            iMotherBoard, channelToLayer[iChannel]);
         totalChargeSingleLayerHistogram[iMotherBoard][iChannel] = new TH1D(name, title, 8000, -3000, 5000);

         name = Form("ChargePerEvent_%d_%d", iMotherBoard, channelToLayer[iChannel]);
         title = Form("Charge (Motherboard %d, layer %d);Event number;Charge",
            iMotherBoard, channelToLayer[iChannel]);
         chargeVsEventNum[iMotherBoard][iChannel] = new TGraph;
         chargeVsEventNum[iMotherBoard][iChannel]->SetNameTitle(name, title);
      }
   }
}


FillAverageChargeLayerAnalyzer::~FillAverageChargeLayerAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         delete totalChargeSingleLayerHistogram[iMotherBoard][iChannel];

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         delete chargeVsEventNum[iMotherBoard][iChannel];

   delete centralTowerChargeLayer;
   delete eta89TowerChargeLayer;
   delete totalChargeHistogram;
   delete averageChargeLayerHistogram;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillAverageChargeLayerAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   double eventtotalcharge = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         double channeltotalenergy = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double energy = 0;

            if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == true)
            {
               double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
               adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
               if(useMIP == true)
                  energy = adc / hVlsbInfo->mip[iMotherBoard][iChannel];
               else
                  energy = adc;
            }
            else if(doMissingChannelInterpolate == true)
            {
               int centerlayer = hVlsbInfo->channelToLayer[iMotherBoard][iChannel];

               int channel1 = 0;
               int channel2 = 0;

               if(centerlayer == 0)
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][1];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][1];
               }
               else if(centerlayer == HcalTBVLSBData::maxChannels - 1)
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][HcalTBVLSBData::maxChannels-2];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][HcalTBVLSBData::maxChannels-2];
               }
               else
               {
                  channel1 = hVlsbInfo->layerToChannel[iMotherBoard][centerlayer-1];
                  channel2 = hVlsbInfo->layerToChannel[iMotherBoard][centerlayer+1];
               }

               double adc1 = hVlsbData->adc(iMotherBoard, channel1, iSample);
               adc1 = adc1 - hVlsbInfo->baseline[iMotherBoard][channel1];
               adc1 = hVlsbInfo->GetAdc(adc1, iMotherBoard, channel1);
               if(useMIP == true)
                  energy = adc1 / hVlsbInfo->mip[iMotherBoard][channel1];
               else
                  energy = adc1;

               double adc2 = hVlsbData->adc(iMotherBoard, channel2, iSample);
               adc2 = adc2 - hVlsbInfo->baseline[iMotherBoard][channel2];
               adc2 = hVlsbInfo->GetAdc(adc2, iMotherBoard, channel2);
               if(useMIP == true)
                  energy = energy + adc2 / hVlsbInfo->mip[iMotherBoard][channel2];
               else
                  energy = energy + adc2;

               energy = energy / 2;
            }

            averageChargeLayerHistogram->Fill(iMotherBoard, channelToLayer[iChannel], energy);

            if(iMotherBoard == 0)
               centralTowerChargeLayer->Fill(channelToLayer[iChannel], energy);
            if(iMotherBoard == 0 || iMotherBoard == 3)
               eta89TowerChargeLayer->Fill(channelToLayer[iChannel], energy);

            eventtotalcharge = eventtotalcharge + energy;
            channeltotalenergy = channeltotalenergy + energy;
         }

         totalChargeSingleLayerHistogram[iMotherBoard][iChannel]->Fill(channeltotalenergy);
         chargeVsEventNum[iMotherBoard][iChannel]->SetPoint(eventCount, iEvent.id().event(), channeltotalenergy);
      }
   }

   totalChargeHistogram->Fill(eventtotalcharge);

   eventCount = eventCount + 1;
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillAverageChargeLayerAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillAverageChargeLayerAnalyzer::endJob()
{
   outputFile->cd();
   averageChargeLayerHistogram->Scale(1.0 / eventCount);
   averageChargeLayerHistogram->Write();
   totalChargeHistogram->Write();
   eta89TowerChargeLayer->Scale(1.0 / eventCount);
   eta89TowerChargeLayer->Write();
   centralTowerChargeLayer->Scale(1.0 / eventCount);
   centralTowerChargeLayer->Write();

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         totalChargeSingleLayerHistogram[iMotherBoard][iChannel]->Write();

   if(doChargeEvent == true)
   {
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
            chargeVsEventNum[iMotherBoard][iChannel]->Write();
   }

   if(doTextOutput == true)
   {
      std::cout << "Motherboard, channel, average total charge" << std::endl;
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         {
            std::cout << iMotherBoard << " "
               << iChannel << " "
               << averageChargeLayerHistogram->GetBinContent(iMotherBoard + 1, channelToLayer[iChannel] + 1)
               << std::endl;
         }
      }
   }
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillAverageChargeLayerAnalyzer);
