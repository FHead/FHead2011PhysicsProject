// -*- C++ -*-
//
// Package:    BaselineSubtractionStudyAnalyzer
// Class:      BaselineSubtractionStudyAnalyzer
// 
/**\class BaselineSubtractionStudyAnalyzer BaselineSubtractionStudyAnalyzer.cc TBAnalysis/BaselineSubtractionStudyAnalyzer/src/BaselineSubtractionStudyAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Sep  3 19:39:33 CEST 2009
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

#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"

#include "TFile.h"
#include "TNtuple.h"

#include <cmath>

//
// class decleration
//

class BaselineSubtractionStudyAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit BaselineSubtractionStudyAnalyzer(const edm::ParameterSet&);
      ~BaselineSubtractionStudyAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TNtuple *FirstNSamples[8];
      TFile *outputFile;
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
BaselineSubtractionStudyAnalyzer::BaselineSubtractionStudyAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   FirstNSamples[0] = new TNtuple("First2", "RMS of the first two samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[1] = new TNtuple("First3", "RMS of the first three samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[2] = new TNtuple("First4", "RMS of the first four samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[3] = new TNtuple("First5", "RMS of the first five samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[4] = new TNtuple("First6", "RMS of the first six samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[5] = new TNtuple("First7", "RMS of the first seven samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[6] = new TNtuple("First8", "RMS of the first eight samples assuming using these for subtraction", "RMS:Time");
   FirstNSamples[7] = new TNtuple("First9", "RMS of the first nine samples assuming using these for subtraction", "RMS:Time");

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "output.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");
}


BaselineSubtractionStudyAnalyzer::~BaselineSubtractionStudyAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   delete FirstNSamples[0];
   delete FirstNSamples[1];
   delete FirstNSamples[2];
   delete FirstNSamples[3];
   delete FirstNSamples[4];
   delete FirstNSamples[5];
   delete FirstNSamples[6];
   delete FirstNSamples[7];

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
BaselineSubtractionStudyAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   for(int N = 2; N < 10; N++)
   {
      int index = N - 2;

      std::vector<double> samples;

      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
            continue;

         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         {
            if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
               continue;

            double average = 0;
            for(int iSample = 0; iSample < N; iSample++)
               average = average + hVlsbData->adc(iMotherBoard, iChannel, iSample);
            average = average / N;

            for(int iSample = 0; iSample < N; iSample++)
               samples.push_back(hVlsbData->adc(iMotherBoard, iChannel, iSample) - average);
         }
      }

      double SX = 0;
      double SXX = 0;

      for(int i = 0; i < (int)samples.size(); i++)
      {
         SX = SX + samples[i];
         SXX = SXX + samples[i] * samples[i];
      }

      double RMS = std::sqrt((SXX - SX * SX) / samples.size());

      FirstNSamples[index]->Fill(RMS, hVlsbInfo->time);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
BaselineSubtractionStudyAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BaselineSubtractionStudyAnalyzer::endJob()
{
   outputFile->cd();

   FirstNSamples[0]->Write();
   FirstNSamples[1]->Write();
   FirstNSamples[2]->Write();
   FirstNSamples[3]->Write();
   FirstNSamples[4]->Write();
   FirstNSamples[5]->Write();
   FirstNSamples[6]->Write();
   FirstNSamples[7]->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(BaselineSubtractionStudyAnalyzer);
