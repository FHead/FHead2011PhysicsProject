// -*- C++ -*-
//
// Package:    FillMaxLayerDistributionAnalyzer
// Class:      FillMaxLayerDistributionAnalyzer
// 
/**\class FillMaxLayerDistributionAnalyzer FillMaxLayerDistributionAnalyzer.cc TBAnalysis/FillMaxLayerDistributionAnalyzer/src/FillMaxLayerDistributionAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Fri Jul 31 09:29:03 CEST 2009
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

//
// class decleration
//

class FillMaxLayerDistributionAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillMaxLayerDistributionAnalyzer(const edm::ParameterSet&);
      ~FillMaxLayerDistributionAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TH1D *maxLayerDistribution[4];
      TH1D *meanLayerDistribution[4];
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
FillMaxLayerDistributionAnalyzer::FillMaxLayerDistributionAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "MaxLayerDistribution.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   maxLayerDistribution[0] = new TH1D("MaxLayerHistogram_0", "Maximum channel per event (motherboard 0);Channel;", 16, -0.5, 15.5);
   maxLayerDistribution[1] = new TH1D("MaxLayerHistogram_1", "Maximum channel per event (motherboard 1);Channel;", 16, -0.5, 15.5);
   maxLayerDistribution[2] = new TH1D("MaxLayerHistogram_2", "Maximum channel per event (motherboard 2);Channel;", 16, -0.5, 15.5);
   maxLayerDistribution[3] = new TH1D("MaxLayerHistogram_3", "Maximum channel per event (motherboard 3);Channel;", 16, -0.5, 15.5);

   meanLayerDistribution[0] = new TH1D("MeanLayerHistogram_0", "Mean channel per event (motherboard 0);Channel;", 200, -0.5, 15.5);
   meanLayerDistribution[1] = new TH1D("MeanLayerHistogram_1", "Mean channel per event (motherboard 1);Channel;", 200, -0.5, 15.5);
   meanLayerDistribution[2] = new TH1D("MeanLayerHistogram_2", "Mean channel per event (motherboard 2);Channel;", 200, -0.5, 15.5);
   meanLayerDistribution[3] = new TH1D("MeanLayerHistogram_3", "Mean channel per event (motherboard 3);Channel;", 200, -0.5, 15.5);
}


FillMaxLayerDistributionAnalyzer::~FillMaxLayerDistributionAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   delete maxLayerDistribution[3];
   delete maxLayerDistribution[2];
   delete maxLayerDistribution[1];
   delete maxLayerDistribution[0];
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillMaxLayerDistributionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      int maxchannel = 0;
      double maxadc = 0;

      double meanlayer = 0;
      double totalcharge = 0;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         double totaladc = 0;
         for(int iSample = hVlsbInfo->minSample; iSample < hVlsbInfo->maxSample; iSample++)
         {
            double realAdc = hVlsbData->adc(iMotherBoard, iChannel, iSample) -
               hVlsbInfo->baseline[iMotherBoard][iChannel];
            totaladc = totaladc + hVlsbInfo->GetAdc(realAdc, iMotherBoard, iChannel);
         }
         totaladc = totaladc / hVlsbInfo->mip[iMotherBoard][iChannel];

         if(maxadc < totaladc && hVlsbInfo->goodChannel[iMotherBoard][iChannel] == true)
         {
            maxadc = totaladc;
            maxchannel = iChannel;
         }

         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == true)
         {
            meanlayer = meanlayer + totaladc * hVlsbInfo->channelToLayer[iMotherBoard][iChannel];
            totalcharge = totalcharge + totaladc;
         }
         else   // let's assume that there aren't neighboring bad channels....
         {
            int channel1 = 0;
            int channel2 = 0;

            int layer = hVlsbInfo->channelToLayer[iMotherBoard][iChannel];

            if(hVlsbInfo->channelToLayer[iMotherBoard][iChannel] == 0)
            {
               channel1 = hVlsbInfo->layerToChannel[iMotherBoard][layer+1];
               channel2 = channel1;
            }
            else if(hVlsbInfo->channelToLayer[iMotherBoard][iChannel] == HcalTBVLSBData::maxChannels - 1)
            {
               channel1 = hVlsbInfo->layerToChannel[iMotherBoard][layer-1];
               channel2 = channel1;
            }
            else
            {
               channel1 = hVlsbInfo->layerToChannel[iMotherBoard][layer-1];
               channel2 = hVlsbInfo->layerToChannel[iMotherBoard][layer+1];
            }

            double totaladc1 = 0;
            for(int iSample = hVlsbInfo->minSample; iSample < hVlsbInfo->maxSample; iSample++)
            {
               double realAdc = hVlsbData->adc(iMotherBoard, channel1, iSample) -
                  hVlsbInfo->baseline[iMotherBoard][channel1];
               totaladc1 = totaladc1 + hVlsbInfo->GetAdc(realAdc, iMotherBoard, channel1);
            }
            totaladc1 = totaladc1 / hVlsbInfo->mip[iMotherBoard][channel1];

            double totaladc2 = 0;
            for(int iSample = hVlsbInfo->minSample; iSample < hVlsbInfo->maxSample; iSample++)
            {
               double realAdc = hVlsbData->adc(iMotherBoard, channel2, iSample) -
                  hVlsbInfo->baseline[iMotherBoard][channel2];
               totaladc2 = totaladc2 + hVlsbInfo->GetAdc(realAdc, iMotherBoard, channel2);
            }
            totaladc2 = totaladc2 / hVlsbInfo->mip[iMotherBoard][channel2];

            totaladc = (totaladc1 + totaladc2) / 2;

            meanlayer = meanlayer + totaladc * hVlsbInfo->channelToLayer[iMotherBoard][iChannel];
            totalcharge = totalcharge + totaladc;
         }
      }

      meanlayer = meanlayer / totalcharge;

      meanLayerDistribution[iMotherBoard]->Fill(meanlayer);
      maxLayerDistribution[iMotherBoard]->Fill(hVlsbInfo->channelToLayer[iMotherBoard][maxchannel]);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillMaxLayerDistributionAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillMaxLayerDistributionAnalyzer::endJob()
{
   outputFile->cd();
   maxLayerDistribution[0]->Write();
   maxLayerDistribution[1]->Write();
   maxLayerDistribution[2]->Write();
   maxLayerDistribution[3]->Write();

   meanLayerDistribution[0]->Write();
   meanLayerDistribution[1]->Write();
   meanLayerDistribution[2]->Write();
   meanLayerDistribution[3]->Write();

   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 0"
      << " Mean of max layer " << maxLayerDistribution[0]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 1"
      << " Mean of max layer " << maxLayerDistribution[1]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 2"
      << " Mean of max layer " << maxLayerDistribution[2]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 3"
      << " Mean of max layer " << maxLayerDistribution[3]->GetMean() << std::endl;

   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 0"
      << " Mean of mean layer " << meanLayerDistribution[0]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 1"
      << " Mean of mean layer " << meanLayerDistribution[1]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 2"
      << " Mean of mean layer " << meanLayerDistribution[2]->GetMean() << std::endl;
   std::cout << "[FillMaxLayerDistributionAnalyzer][Summary] Motherboard 3"
      << " Mean of mean layer " << meanLayerDistribution[3]->GetMean() << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillMaxLayerDistributionAnalyzer);
