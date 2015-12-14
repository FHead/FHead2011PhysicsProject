// -*- C++ -*-
//
// Package:    AlignPulseAnalyzer
// Class:      AlignPulseAnalyzer
// 
/**\class AlignPulseAnalyzer AlignPulseAnalyzer.cc TBAnalysis/AlignPulseAnalyzer/src/AlignPulseAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Aug 13 22:23:32 CEST 2009
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
#include "TGraph.h"
#include "TH1D.h"

//
// class decleration
//

class AlignPulseAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit AlignPulseAnalyzer(const edm::ParameterSet&);
      ~AlignPulseAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob();

      // ----------member data ---------------------------
      int rejectionSample;   // if pulse starts before this sample, reject
      double rejectionHeight;   // what counts as the "start of pulse"?

      TFile *outputFile;
      TGraph *pulsePerEventOverlay;
      TH1D *averagePulseShape;
      TH1D *reversedAveragePulseShape;
      TH1D *eventsPerBin;
      TH1D *timeDistribution;

      double maxmaxsample;
      double minmaxsample;

      int eventsPassRejectionTest;
      double averageEnergy;
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
AlignPulseAnalyzer::AlignPulseAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   rejectionSample = iConfig.getUntrackedParameter<int>("rejectionSample", 3);
   rejectionHeight = iConfig.getUntrackedParameter<double>("rejectionHeight", 0.1);

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "TimingStudies.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   pulsePerEventOverlay = new TGraph;
   pulsePerEventOverlay->SetNameTitle("PulsePerEvent", "Pulse per event");

   averagePulseShape = new TH1D("AveragePulseShape", "AveragePulseShape", 140, -10, 25);
   reversedAveragePulseShape = new TH1D("ReversedAveragePulseShape", "ReversedAveragePulseShape", 140, -10, 25);
   eventsPerBin = new TH1D("EventsPerBin", "EventsPerBin", 140, -10, 25);
   timeDistribution = new TH1D("TimeDistribution", "Time of pulse;Time (sample);", 200, 0, 20);

   eventsPassRejectionTest = 0;
   averageEnergy = 0;

   maxmaxsample = iConfig.getUntrackedParameter<double>("maxsample", 100000000);
   minmaxsample = iConfig.getUntrackedParameter<double>("minsample", -100000000);
}


AlignPulseAnalyzer::~AlignPulseAnalyzer()
{
   delete timeDistribution;
   delete eventsPerBin;
   delete averagePulseShape;
   delete reversedAveragePulseShape;
   delete pulsePerEventOverlay;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
AlignPulseAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   double totalPerSample[HcalTBVLSBData::maxSamples];
   double grandtotal = 0;

   for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
      totalPerSample[iSample] = 0;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(hVlsbInfo->useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)
            continue;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
            adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
            double energy = adc / hVlsbInfo->mip[iMotherBoard][iChannel];

            // if(energy < 0)
            //   energy = 0;

            totalPerSample[iSample] = totalPerSample[iSample] + energy;
            grandtotal = grandtotal + energy;
         }
      }
   }

   for(int iSample = 0; iSample < rejectionSample; iSample++)
      if(totalPerSample[iSample] > rejectionHeight)
         return;

   if(grandtotal <= 0)   // bad baseline!
      return;

   double maxSample = 0;
   for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
      if(totalPerSample[iSample] > maxSample)
         maxSample = totalPerSample[iSample];

   if(maxSample < minmaxsample || maxSample > maxmaxsample)   // outside of window
      return;

   eventsPassRejectionTest = eventsPassRejectionTest + 1;
   averageEnergy = averageEnergy + grandtotal;

   // Algorithm: average sample weighted by energy
   // double referencePoint = 0;
   // for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
   //    referencePoint = referencePoint + totalPerSample[iSample] * iSample;
   // referencePoint = referencePoint / grandtotal;

   // Algorithm: average sample weighted by energy, but only around peak
   double referencePoint = 0;
   double totalweight = 0;
   double maxenergy = 0;
   for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
      if(maxenergy < totalPerSample[iSample])
         maxenergy = totalPerSample[iSample];
   if(maxenergy < 0)
      return;
   for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
   {
      if(totalPerSample[iSample] > maxenergy * 0.5)
      {
         referencePoint = referencePoint + totalPerSample[iSample] * iSample;
         totalweight = totalweight + totalPerSample[iSample];
      }
   }
   referencePoint = referencePoint / totalweight;

   static int pointcount = 0;

   if(iEvent.id().event() < 100)
   {
      for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
      {
         pulsePerEventOverlay->SetPoint(pointcount, iSample - referencePoint, totalPerSample[iSample]);
         pointcount = pointcount + 1;
      }
   }

   for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
   {
      averagePulseShape->Fill(iSample - referencePoint, totalPerSample[iSample]);
      reversedAveragePulseShape->Fill(referencePoint - iSample, totalPerSample[iSample]);
      eventsPerBin->Fill(iSample - referencePoint, grandtotal);
   }

   timeDistribution->Fill(referencePoint);
}


// ------------ method called once each job just before starting event loop  ------------
void 
AlignPulseAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 

AlignPulseAnalyzer::endJob()
{
   averageEnergy = averageEnergy / eventsPassRejectionTest;

   std::cout << "[AlignPulseAnalyzer][endJob] Average energy is " << averageEnergy << std::endl;

   outputFile->cd();

   pulsePerEventOverlay->Write();

   averagePulseShape->Divide(eventsPerBin);
   averagePulseShape->Scale(averageEnergy / averagePulseShape->Integral("width"));

   reversedAveragePulseShape->Divide(eventsPerBin);

   // int bincount = 0;
   // double averagelevel = 0;
   // for(int iBin = 0; averagePulseShape->GetBinContent(iBin) < rejectionHeight; iBin++)
   // {
   //    bincount = bincount + 1;
   //    averagelevel = averagelevel + averagePulseShape->GetBinContent(iBin);
   // }
   // averagelevel = averagelevel / bincount;

   // for(int iBin = 0; iBin < averagePulseShape->GetNbinsX(); iBin++)
   // {
   //    averagePulseShape->AddBinContent(iBin, -averagelevel);
   //    reversedAveragePulseShape->AddBinContent(iBin, -averagelevel);
   // }

   averagePulseShape->Write();
   reversedAveragePulseShape->Write();

   eventsPerBin->Write();

   timeDistribution->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(AlignPulseAnalyzer);
