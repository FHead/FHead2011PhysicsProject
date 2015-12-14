// -*- C++ -*-
//
// Package:    ShowerClusterProducer
// Class:      ShowerClusterProducer
// 
/**\class ShowerClusterProducer ShowerClusterProducer.cc TBAnalysis/ShowerClusterProducer/src/ShowerClusterProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Tue Aug 18 15:46:56 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBAnalysis/ShowerCluster/interface/ShowerCluster.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include "TBAnalysis/RunInformation/interface/RunInformation.h"

#include <cmath>
#include <vector>
#include <algorithm>

//
// class decleration
//

class ShowerClusterProducer : public edm::EDProducer
{
   public:
      explicit ShowerClusterProducer(const edm::ParameterSet&);
      ~ShowerClusterProducer();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      double threshold;   // the threshold for a sample to be considered as seed
};

struct TimeSample
{
public:
   double energy;
   int layer;
   int sample;
public:
   TimeSample()
   {
      energy = 0;
      layer = 0;
      sample = 0;
   }
   TimeSample(double energy_, int layer_, int sample_)
   {
      energy = energy_;
      layer = layer_;
      sample = sample_;
   }
   bool operator <(const TimeSample &other) const
   {
      if(energy < other.energy)
         return true;
      if(energy > other.energy)
         return false;

      if(layer < other.layer)
         return true;
      if(layer > other.layer)
         return false;

      if(sample < other.sample)
         return true;
      if(sample > other.sample)
         return false;

      return false;
   }
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
ShowerClusterProducer::ShowerClusterProducer(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<std::vector<ShowerCluster> >();

   //now do what ever other initialization is needed
   threshold = iConfig.getUntrackedParameter<double>("threshold", 1);
}


ShowerClusterProducer::~ShowerClusterProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ShowerClusterProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::auto_ptr<std::vector<ShowerCluster> > pResult(new std::vector<ShowerCluster>);

   edm::Handle<HcalTBVLSBData> hVlsbData;
   iEvent.getByType(hVlsbData);

   edm::Handle<VLSBInformation> hVlsbInfo;
   iEvent.getByType(hVlsbInfo);

   edm::Handle<RunInformation> hRunInfo;
   iEvent.getByType(hRunInfo);

   // do it for central mother board only for now
   double energy[HcalTBVLSBData::maxChannels][HcalTBVLSBData::maxSamples] = {0};
   int iMotherBoard = 0;

   // copy the energy out
   for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++)
   {
      if(hVlsbInfo->goodChannel[iMotherBoard][iChannel] == false)   // skip
         continue;

      for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
      {
         double adc = hVlsbData->adc(iMotherBoard, iChannel, iSample);
         adc = adc - hVlsbInfo->baseline[iMotherBoard][iChannel];
         adc = hVlsbInfo->GetAdc(adc, iMotherBoard, iChannel);
         energy[hVlsbInfo->channelToLayer[iMotherBoard][iChannel]][iSample] = energy[hVlsbInfo->channelToLayer[iMotherBoard][iChannel]][iSample] + adc / hVlsbInfo->mip[iMotherBoard][iChannel];
      }
   }

   // create a list of seeds, and sort
   std::vector<TimeSample> seeds;
   for(int iLayer = 0; iLayer < HcalTBVLSBData::maxChannels; iLayer++)
      for(int iSample = 0; iSample < HcalTBVLSBData::maxSamples; iSample++)
         if(energy[iLayer][iSample] > threshold)
            seeds.push_back(TimeSample(energy[iLayer][iSample], iLayer, iSample));
   sort(seeds.begin(), seeds.end());
   reverse(seeds.begin(), seeds.end());

   // from the largest seed down, create cluster(s)
   int seedindex = 0;
   while(seedindex < (int)seeds.size())
   {
      if(energy[seeds[seedindex].layer][seeds[seedindex].sample] < threshold)   // seed used
      {
         seedindex = seedindex + 1;
         continue;
      }

      ShowerCluster newcluster;

      int seedlayer = seeds[seedindex].layer;
      int seedsample = seeds[seedindex].sample;

      // search in time direction
      int maxindex = seedsample;
      while(maxindex != HcalTBVLSBData::maxSamples - 1 && energy[seedlayer][maxindex] > energy[seedlayer][maxindex+1])
         maxindex = maxindex + 1;

      int minindex = seedsample;
      while(minindex != 0 && energy[seedlayer][minindex] > energy[seedlayer][minindex-1])
         minindex = minindex - 1;

      // now go in direction of different layers
      std::map<int, int> boundary_start;
      std::map<int, int> boundary_end;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
      {
         int maxlayer = seedlayer;
         while(maxlayer != HcalTBVLSBData::maxChannels - 1)
         {
            if(hVlsbInfo->goodChannel[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][maxlayer+1]] == true)
            {
               if(energy[maxlayer][iSample] > energy[maxlayer+1][iSample])
                  maxlayer = maxlayer + 1;
               else
                  break;
            }
            else
            {
               if(energy[maxlayer][iSample] > energy[maxlayer+2][iSample])
                  maxlayer = maxlayer + 2;
               else
                  break;
            }
         }

         int minlayer = seedlayer;
         while(minlayer != 0)
         {
            if(hVlsbInfo->goodChannel[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][minlayer-1]] == true)
            {
               if(energy[minlayer][iSample] > energy[minlayer-1][iSample])
                  minlayer = minlayer - 1;
               else
                  break;
            }
            else
            {
               if(energy[minlayer][iSample] > energy[minlayer-2][iSample])
                  minlayer = minlayer - 2;
               else
                  break;
            }
         }

         boundary_start.insert(std::pair<int, int>(iSample, minlayer));
         boundary_end.insert(std::pair<int, int>(iSample, maxlayer));
      }

      newcluster.boundary_start = boundary_start;
      newcluster.boundary_end = boundary_end;

      // calculate total energy
      double totalenergy = 0;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
            if(hVlsbInfo->goodChannel[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]] == true)
               totalenergy = totalenergy + energy[iLayer][iSample];
      newcluster.energy = totalenergy;

      // calculate average time
      double time = 0;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
            if(hVlsbInfo->goodChannel[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]] == true)
               time = time + energy[iLayer][iSample] * iSample;
      newcluster.time = time / totalenergy;

      // calculate average layer
      double layer = 0;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
            if(hVlsbInfo->goodChannel[iMotherBoard][hVlsbInfo->layerToChannel[iMotherBoard][iLayer]] == true)
               layer = layer + energy[iLayer][iSample] * iLayer;
      newcluster.depth = layer / totalenergy;

      // calculate layer rms
      std::map<int, double> layer_sum;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
      {
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
         {
            if(layer_sum.find(iLayer) == layer_sum.end())
               layer_sum.insert(std::pair<int, double>(iLayer, 0));
            layer_sum[iLayer] = layer_sum[iLayer] + energy[iLayer][iSample];
         }
      }
      double layer_variance = 0;
      for(std::map<int, double>::iterator layeriter = layer_sum.begin(); layeriter != layer_sum.end(); layeriter++)
         layer_variance = layer_variance + (layeriter->first - newcluster.depth) * (layeriter->first - newcluster.depth) * layeriter->second;
      newcluster.depth_rms = sqrt(layer_variance / totalenergy);

      // calculate time rms
      double time_variance = 0;
      for(int iSample = minindex; iSample <= maxindex; iSample++)
      {
         double sum = 0;
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
           sum = sum + energy[iLayer][iSample];
         time_variance = time_variance + (iSample - newcluster.time) * (iSample - newcluster.time) * sum;
      }
      newcluster.time_rms = sqrt(time_variance / totalenergy);

      // take the energy away from the table
      for(int iSample = minindex; iSample <= maxindex; iSample++)
         for(int iLayer = boundary_start[iSample]; iLayer <= boundary_end[iSample]; iLayer++)
            energy[iLayer][iSample] = 0;

      seedindex = seedindex + 1;

      pResult->push_back(newcluster);
   }

   std::map<double, int> depthToIndex;
   for(int iCluster = 0; iCluster < (int)pResult->size(); iCluster++)
      depthToIndex.insert(std::pair<double, int>(pResult->at(iCluster).depth, iCluster));

   double remainingEnergy = hRunInfo->beamEnergy;
   for(std::map<double, int>::iterator iter = depthToIndex.begin(); iter != depthToIndex.end(); iter++)
   {
      pResult->at(iter->second).remaining_energy = remainingEnergy;
      remainingEnergy = remainingEnergy - pResult->at(iter->second).energy;
   }   

   // uncomment to debug
   // std::cout << "[ShowerClusterProducer][Produce] Number of clusters = " << pResult->size() << std::endl;
   // std::cout << "[ShowerClusterProducer][Produce] Energies are ";
   // for(int iCluster = 0; iCluster < (int)pResult->size(); iCluster++)
   //    std::cout << pResult->at(iCluster).energy << " ";
   // std::cout << std::endl;

   iEvent.put(pResult);
}

// ------------ method called once each job just before starting event loop  ------------
void 
ShowerClusterProducer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ShowerClusterProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(ShowerClusterProducer);
