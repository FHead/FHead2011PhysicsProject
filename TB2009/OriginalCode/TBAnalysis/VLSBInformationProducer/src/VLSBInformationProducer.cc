// -*- C++ -*-
//
// Package:    VLSBInformationProducer
// Class:      VLSBInformationProducer
// 
/**\class VLSBInformationProducer VLSBInformationProducer.cc TBAnalysis/VLSBInformationProducer/src/VLSBInformationProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Jul 30 10:50:56 CEST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>
#include <algorithm>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"

#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBEventPosition.h"

//
// class decleration
//

class VLSBInformationProducer : public edm::EDProducer
{
   public:
      explicit VLSBInformationProducer(const edm::ParameterSet&);
      ~VLSBInformationProducer();

   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      // ----------member data ---------------------------
      int minSample;   // region of samples used
      int maxSample;   // region of samples used
      int baselineSamples;   // number of samples used to construct baseline
      bool usePedestalMean;   // whether to use first two samples to calculate baseline or not
      std::string pedestalFile;   // file name containing the pedestals
      double pedestals[4][16];   // pedestal mean
      std::string secondaryShiftFile;   // mean energy after stage-2 baseline subtraction for pedestal events
      double secondaryShift[4][16];

      double mip[4][16];   // for muon calibration
      double roughmip[4][16];   // for stage-2 baseline subtraction
      std::string mipFileName;   // data file
      std::string roughmipFileName;

      std::vector<std::pair<double, double> > adcMap[4][16];   // adc map
      std::string adcMapFileName;   // mapping file name

      bool useMotherBoard[4];   // whether to use cerntain motherboard or not
      int motherBoardEta[4];   // eta value for each motherboard
      double beamEnergy;

      std::string interCalibrationFileName;
      double interCalibration[4][16];   // inter-calibration constants

      double wireChamberPositions[3];   // A, B, C
      double chamberBShift[2];
      double chamberCShift[2];

      int channelToLayer[16];
      int layerToChannel[16];

      bool lowestSampleSubtraction;
      int numberOfSamplesForSubtraction;
      int numberOfSamplesToSkip;
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
VLSBInformationProducer::VLSBInformationProducer(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<VLSBInformation>();

   //now do what ever other initialization is needed
   minSample = iConfig.getUntrackedParameter<unsigned int>("minSample", 2);
   maxSample = iConfig.getUntrackedParameter<unsigned int>("maxSample", 31);
   baselineSamples = iConfig.getUntrackedParameter<unsigned int>("baselineSamples", 3);

   usePedestalMean = iConfig.getUntrackedParameter<bool>("usePedestalMean", false);
   pedestalFile = iConfig.getUntrackedParameter<std::string>("pedestalMean", "");
   secondaryShiftFile = iConfig.getUntrackedParameter<std::string>("secondaryShift", "");

   mipFileName = iConfig.getUntrackedParameter<std::string>("mip", "");
   roughmipFileName = iConfig.getUntrackedParameter<std::string>("roughmip", mipFileName);
   adcMapFileName = iConfig.getUntrackedParameter<std::string>("adcMap", "");

   useMotherBoard[0] = iConfig.getUntrackedParameter<bool>("useMotherBoard0", true);
   useMotherBoard[1] = iConfig.getUntrackedParameter<bool>("useMotherBoard1", false);
   useMotherBoard[2] = iConfig.getUntrackedParameter<bool>("useMotherBoard2", false);
   useMotherBoard[3] = iConfig.getUntrackedParameter<bool>("useMotherBoard3", false);

   for(int iChannel = 0; iChannel < 15; iChannel++)
   {
      channelToLayer[iChannel] = iChannel + 1;
      layerToChannel[iChannel+1] = iChannel;
   }
   channelToLayer[15] = 0;
   layerToChannel[0] = 15;

   motherBoardEta[0] = iConfig.getUntrackedParameter<int>("motherBoard0Eta", 8);
   motherBoardEta[1] = iConfig.getUntrackedParameter<int>("motherBoard1Eta", 7);
   motherBoardEta[2] = iConfig.getUntrackedParameter<int>("motherBoard2Eta", 100);
   motherBoardEta[3] = iConfig.getUntrackedParameter<int>("motherBoard3Eta", 9);

   beamEnergy = iConfig.getUntrackedParameter<double>("beamEnergy", 0);

   interCalibrationFileName = iConfig.getUntrackedParameter<std::string>("interCalibration", "");

   wireChamberPositions[0] = iConfig.getUntrackedParameter<double>("chamberAPosition", -514);
   wireChamberPositions[1] = iConfig.getUntrackedParameter<double>("chamberBPosition", -404);
   wireChamberPositions[2] = iConfig.getUntrackedParameter<double>("chamberCPosition", -200);
   chamberBShift[0] = iConfig.getUntrackedParameter<double>("chamberBXShift", -1.67);
   chamberBShift[1] = iConfig.getUntrackedParameter<double>("chamberBYShift", 1.50);
   chamberCShift[0] = iConfig.getUntrackedParameter<double>("chamberCXShift", -1.544);
   chamberCShift[1] = iConfig.getUntrackedParameter<double>("chamberCYShift", 0.148);

   lowestSampleSubtraction = iConfig.getUntrackedParameter<bool>("lowestSampleSubtraction", false);
   numberOfSamplesForSubtraction = iConfig.getUntrackedParameter<int>("numberOfSamplesForSubtraction", 32);   // whole central strip
   numberOfSamplesToSkip = iConfig.getUntrackedParameter<int>("numberOfSamplesToSkip", 32);

   if(lowestSampleSubtraction == true)
   {
      std::cout << "[VLSBInformationProducer][constructor] Use lowest sample subtraction with " << numberOfSamplesForSubtraction << " samples, ";
      std::cout << "skipping lowest " << numberOfSamplesToSkip << " samples" << std::endl;
   }
}


VLSBInformationProducer::~VLSBInformationProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
VLSBInformationProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   std::auto_ptr<VLSBInformation> pInfo(new VLSBInformation(HcalTBVLSBData::maxMotherBoards, HcalTBVLSBData::maxChannels));

   if(usePedestalMean == false || pedestalFile == "")
   {
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         {
            double totalAdc = 0;

            for(int iSample = minSample; iSample < minSample + baselineSamples; iSample++)
               totalAdc = totalAdc + hVlsbData->adc(iMotherBoard, iChannel, iSample);

            pInfo->baseline[iMotherBoard][iChannel] = totalAdc / baselineSamples;
         }
      }
   }
   else
   {
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
            pInfo->baseline[iMotherBoard][iChannel] = pedestals[iMotherBoard][iChannel];
   }

   if(lowestSampleSubtraction == true)
   {
      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         std::vector<double> samples;

         if(useMotherBoard[iMotherBoard] == false)
            continue;

         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         {
            if(pInfo->goodChannel[iMotherBoard][iChannel] == false)
               continue;

            for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
               samples.push_back((hVlsbData->adc(iMotherBoard, iChannel, iSample) - pInfo->baseline[iMotherBoard][iChannel]) / roughmip[iMotherBoard][iChannel]);
         }

         std::sort(samples.begin(), samples.end());

         int count = 0;
         double totalenergy = 0;

         for(int i = numberOfSamplesToSkip; i < numberOfSamplesForSubtraction + numberOfSamplesToSkip; i++)
         {
            if(i >= (int)samples.size())
               break;

            count = count + 1;
            totalenergy = totalenergy + samples[i];
         }

         double averageenergy = totalenergy / count;
         if(count == 0)
            averageenergy = 0;

         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
            pInfo->baseline[iMotherBoard][iChannel] = pInfo->baseline[iMotherBoard][iChannel] + averageenergy * roughmip[iMotherBoard][iChannel];
      }

      for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      {
         if(useMotherBoard[iMotherBoard] == false)
            continue;

         for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
            pInfo->baseline[iMotherBoard][iChannel] = pInfo->baseline[iMotherBoard][iChannel] + secondaryShift[iMotherBoard][iChannel] * roughmip[iMotherBoard][iChannel] / 32;
      }
   }

   pInfo->minSample = minSample;
   pInfo->maxSample = maxSample;
   pInfo->baselineSamples = baselineSamples;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         pInfo->mip[iMotherBoard][iChannel] = mip[iMotherBoard][iChannel] / interCalibration[iMotherBoard][iChannel];

   pInfo->useMotherBoard[0] = useMotherBoard[0];
   pInfo->useMotherBoard[1] = useMotherBoard[1];
   pInfo->useMotherBoard[2] = useMotherBoard[2];
   pInfo->useMotherBoard[3] = useMotherBoard[3];

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
         pInfo->adcMap[iMotherBoard][iChannel] = adcMap[iMotherBoard][iChannel];

   pInfo->motherBoardEta[0] = motherBoardEta[0];
   pInfo->motherBoardEta[1] = motherBoardEta[1];
   pInfo->motherBoardEta[2] = motherBoardEta[2];
   pInfo->motherBoardEta[3] = motherBoardEta[3];

   pInfo->beamEnergy = beamEnergy;

   edm::Handle<HcalTBEventPosition> epos;
   iEvent.getByType(epos);

   std::vector<double> Ax;
   std::vector<double> Ay;
   std::vector<double> Bx;
   std::vector<double> By;
   std::vector<double> Cx;
   std::vector<double> Cy;

   epos->getChamberHits('A', Ax, Ay);
   epos->getChamberHits('B', Bx, By);
   epos->getChamberHits('C', Cx, Cy);

   if(Ax.size() == 1 && Ay.size() == 1 && Bx.size() == 1 && By.size() == 1 && Cx.size() == 1 && Cy.size() == 1)
   {
      double X[3] = {Ax[0], Bx[0], Cx[0]};
      double Y[3] = {Ay[0], By[0], Cy[0]};

      X[1] = X[1] + chamberBShift[0];
      X[2] = X[2] + chamberCShift[0];
      Y[1] = Y[1] + chamberBShift[1];
      Y[2] = Y[2] + chamberCShift[1];

      double SumZ = 0;
      double SumZZ = 0;
      double SumX = 0;
      double SumY = 0;
      double SumXZ = 0;
      double SumYZ = 0;

      for(int i = 0; i < 3; i++)
      {
         SumZ = SumZ + wireChamberPositions[i];
         SumZZ = SumZZ + wireChamberPositions[i] * wireChamberPositions[i];
         SumX = SumX + X[i];
         SumY = SumY + Y[i];
         SumXZ = SumXZ + X[i] * wireChamberPositions[i];
         SumYZ = SumYZ + Y[i] * wireChamberPositions[i];
      }

      double cx = (SumX * SumZZ - SumZ * SumXZ) / (3 * SumZZ - SumZ * SumZ);
      double cy = (SumY * SumZZ - SumZ * SumYZ) / (3 * SumZZ - SumZ * SumZ);

      pInfo->hitPosition[0] = cx;
      pInfo->hitPosition[1] = cy;

      double mx = (SumX - cx * 3) / SumZ;
      double my = (SumY - cy * 3) / SumZ;

      for(int i = 0; i < 3; i++)
      {
         double dx = X[i] - mx * wireChamberPositions[i] - cx;
         double dy = Y[i] - my * wireChamberPositions[i] - cy;
         pInfo->wireChamberHitsDistance2[i] = dx * dx + dy * dy;
      }
   }
   else
   {
      pInfo->hitPosition[0] = 0;
      pInfo->hitPosition[1] = 0;

      pInfo->wireChamberHitsDistance2[0] = -1;
      pInfo->wireChamberHitsDistance2[1] = -1;
      pInfo->wireChamberHitsDistance2[2] = -1;
   }

   double pulseShape[HcalTBVLSBData::maxSamples] = {0};
   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - pInfo->baseline[iMotherBoard][iChannel];
            adc = adc / pInfo->mip[iMotherBoard][iChannel];
            pulseShape[iSample] = pulseShape[iSample] + adc;
         }
      }
   }

   int maxSample = 0;
   for(int iSample = 1; iSample < HcalTBVLSBData::maxSamples; iSample++)
      if(pulseShape[maxSample] < pulseShape[iSample])
         maxSample = iSample;

   double totalenergy = 0;
   for(int iSample = maxSample - 2; iSample <= maxSample + 2; iSample++)
   {
      pInfo->time = pInfo->time + pulseShape[iSample] * iSample;
      totalenergy = totalenergy + pulseShape[iSample];
   }
   pInfo->time = pInfo->time / totalenergy;

   for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++)
   {
      if(useMotherBoard[iMotherBoard] == false)
         continue;

      for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
      {
         if(pInfo->goodChannel[iMotherBoard][iChannel] == false)
         {
            pInfo->channelTime[iMotherBoard][iChannel] = 100000;
            continue;
         }

         double energy = 0;
         double weightedtime = 0;

         for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         {
            double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
            adc = adc - pInfo->baseline[iMotherBoard][iChannel];
            adc = adc / pInfo->mip[iMotherBoard][iChannel];
            energy = energy + adc;
            weightedtime = weightedtime + adc * iSample;
         }

         pInfo->channelTime[iMotherBoard][iChannel] = weightedtime / energy;
      }
   }

   iEvent.put(pInfo);
}

// ------------ method called once each job just before starting event loop  ------------
void 
VLSBInformationProducer::beginJob(const edm::EventSetup&)
{
   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      for(int iChannel = 0; iChannel < 16; iChannel++)
         mip[iMotherBoard][iChannel] = 1;

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      for(int iChannel = 0; iChannel < 16; iChannel++)
         roughmip[iMotherBoard][iChannel] = 1;

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      for(int iChannel = 0; iChannel < 16; iChannel++)
         interCalibration[iMotherBoard][iChannel] = 1;

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      for(int iChannel = 0; iChannel < 16; iChannel++)
         secondaryShift[iMotherBoard][iChannel] = 0;

   if(mipFileName.size() != 0)
   {
      std::ifstream in(mipFileName.c_str());

      while(in)
      {
         int motherboard = -1;
         int channel = -1;
         double muonCharge = 1;

         in >> motherboard >> channel >> muonCharge;

         if(motherboard != -1 && channel != -1)
            mip[motherboard][channel] = muonCharge;
         else
            break;
      }

      in.close();
   }

   if(roughmipFileName.size() != 0)
   {
      std::cout << "[VLSBInformationProducer][beginJob] Begin to read rough mip file" << std::endl;

      std::ifstream in(roughmipFileName.c_str());

      while(in)
      {
         int motherboard = -1;
         int channel = -1;
         double muonCharge = 1;

         in >> motherboard >> channel >> muonCharge;
         // std::cout << motherboard << " " << channel << " " << muonCharge << std::endl;

         if(motherboard != -1 && channel != -1)
            roughmip[motherboard][channel] = muonCharge;
         else
            break;
      }
   }

   if(adcMapFileName.size() != 0)
   {
      std::ifstream in(adcMapFileName.c_str());

      while(in)
      {
         int motherboard = -1;
         int layer = -1;
         double realAdc = -1;
         double imaginaryAdc = -1;

         in >> motherboard >> layer >> realAdc >> imaginaryAdc;

         if(motherboard == -1 || layer == -1)
            continue;

         adcMap[motherboard][layerToChannel[layer]].push_back(std::pair<double, double>(realAdc, imaginaryAdc));
      }

      in.close();

      // for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      //    for(int iChannel = 0; iChannel < 16; iChannel++)
      //       sort(adcMap[iMotherBoard][iChannel].begin(), adcMap[iMotherBoard][iChannel].end());
   }

   if(usePedestalMean == true && pedestalFile.size() != 0)
   {
      std::cout << "[VLSBInformationProducer][beginJob] use pedestal mean file "
         << "instead of first few samples" << std::endl;

      std::ifstream in(pedestalFile.c_str());

      while(in)
      {
         int motherboard = -1;
         int layer = -1;
         double pedestal = 0;

         in >> motherboard >> layer >> pedestal;

         if(motherboard == -1 || layer == -1)
            continue;

         pedestals[motherboard][layerToChannel[layer]] = pedestal;
      }

      in.close();
   }

   if(secondaryShiftFile.size() != 0)
   {
      std::cout << "[VLSBInformationProducer][beginJob] reading secondary shift file" << std::endl;

      std::ifstream in(secondaryShiftFile.c_str());

      while(in)
      {
         int motherboard = -1;
         int channel = -1;
         double shift = 0;

         in >> motherboard >> channel >> shift;
         // std::cout << motherboard << " " << channel << " " << shift << std::endl;

         if(motherboard == -1 || channel == -1)
            continue;

         secondaryShift[motherboard][channel] = shift;
      }

      in.close();
   }

   if(interCalibrationFileName.size() != 0)
   {
      std::ifstream in(interCalibrationFileName.c_str());

      while(in)
      {
         int ieta = 0;
         int iphi = 0;
         double constant = 0;

         in >> iphi >> ieta >> constant;

         if(iphi < 50)
            continue;

         if(ieta == 7)
            interCalibration[1][layerToChannel[iphi-50]] = constant;
         if(ieta == 8)
            interCalibration[0][layerToChannel[iphi-50]] = constant;
         if(ieta == 9)
            interCalibration[3][layerToChannel[iphi-50]] = constant;
      }

      in.close();
   }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VLSBInformationProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(VLSBInformationProducer);
