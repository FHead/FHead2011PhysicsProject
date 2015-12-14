// -*- C++ -*-
//
// Package:    FillAdcDistributionAnalyzer
// Class:      FillAdcDistributionAnalyzer
// 
/**\class FillAdcDistributionAnalyzer FillAdcDistributionAnalyzer.cc TBAnalysis/FillAdcDistributionAnalyzer/src/FillAdcDistributionAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Sun Aug  2 12:47:29 CEST 2009
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

#include "TH1D.h"
#include "TFile.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

//
// class decleration
//

class FillAdcDistributionAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillAdcDistributionAnalyzer(const edm::ParameterSet&);
      ~FillAdcDistributionAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TH1D *AdcDistribution;
      bool doBaselineSubtraction;
      bool doInvert;
      bool doHighDef;
      bool doDivideMIP;

      TH1D *allAdcDistribution;
      TH1D *channelAdcDistribution[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];
      TH1D *channelMaxAdcDistribution[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];

      int channelToLayer[HcalTBVLSBData::maxChannels];
      int layerToChannel[HcalTBVLSBData::maxChannels];
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
FillAdcDistributionAnalyzer::FillAdcDistributionAnalyzer(const edm::ParameterSet& iConfig)
{
   for(int i = 0; i < 15; i++)
   {
      channelToLayer[i] = i + 1;
      layerToChannel[i+1] = i;
   }
   channelToLayer[15] = 0;
   layerToChannel[0] = 15;

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "AdcDistribution.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   doBaselineSubtraction = iConfig.getUntrackedParameter<bool>("baselineSubtraction", false);
   doInvert = iConfig.getUntrackedParameter<bool>("invert", false);
   doHighDef = iConfig.getUntrackedParameter<bool>("highdef", false);
   doDivideMIP = iConfig.getUntrackedParameter<bool>("divideMIP", false);

   int binnumber = 1;
   if(doHighDef == false)
      binnumber = 200;
   else
   {
      std::cout << "[FillAdcDistributionAnalyzer][FillAdcDistributionAnalyzer] Doing high definition!" << std::endl;
      binnumber = 30000;
   }

   allAdcDistribution = new TH1D("AdcDistribution", "ADC;ADC;", binnumber, -10000, 20000);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         TString name = Form("Adc_%d_%d", iMotherBoard, channelToLayer[iChannel]);
         TString title = Form("ADC (Motherboard %d, channel %d);ADC;", iMotherBoard, channelToLayer[iChannel]);
         channelAdcDistribution[iMotherBoard][iChannel] = new TH1D(name, title, binnumber, -10000, 20000);

         name = Form("MaxAdc_%d_%d", iMotherBoard, channelToLayer[iChannel]);
         title = Form("Max ADC (Motherboard %d, channel %d);ADC;", iMotherBoard, channelToLayer[iChannel]);
         channelMaxAdcDistribution[iMotherBoard][iChannel] = new TH1D(name, title, binnumber, -10000, 20000);
      }
   }
}


FillAdcDistributionAnalyzer::~FillAdcDistributionAnalyzer()
{
   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         delete channelAdcDistribution[iMotherBoard][iChannel];

   delete allAdcDistribution;

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillAdcDistributionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         double maxadc = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);

            if(doBaselineSubtraction == true)
            {
               adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            }
            else
            {
               adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
               adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
               adc = adc + hVlsbInfo->baseline[iMotherBoard][iChannel];
            }

            if(doDivideMIP == true)
               adc = adc / hVlsbInfo->mip[iMotherBoard][iChannel];

            if(doInvert == true)
               adc = -adc;

            if(adc > maxadc)
               maxadc = adc;

            allAdcDistribution->Fill(adc);
            channelAdcDistribution[iMotherBoard][iChannel]->Fill(adc);
         }

         channelMaxAdcDistribution[iMotherBoard][iChannel]->Fill(maxadc);
      }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillAdcDistributionAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillAdcDistributionAnalyzer::endJob()
{
   outputFile->cd();

   allAdcDistribution->Write();

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         channelAdcDistribution[iMotherBoard][iChannel]->Write();
         channelMaxAdcDistribution[iMotherBoard][iChannel]->Write();
      }
   }
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillAdcDistributionAnalyzer);
