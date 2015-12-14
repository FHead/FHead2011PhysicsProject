#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include <fstream>

class HcalTBVLSBReconstructor : public edm::EDProducer
{
public:
  explicit HcalTBVLSBReconstructor(const edm::ParameterSet&);
  ~HcalTBVLSBReconstructor();
  
private:
  virtual void beginJob(const edm::EventSetup&);
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  virtual void parseTextFiles();
  virtual void buildMap();
  double GetAdc(double adc, int iMotherboard, int iChannel);

  static const double clockPeriod_;

  int minSample_;   // region of samples used
  int maxSample_;   // region of samples used

  double mip[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];   // for muon calibration
  std::string mipFileName;   // data file

  std::vector<std::pair<double, double> > adcMap[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];   // adc map
  std::string adcMapFileName;   // mapping file name

  int iEta_ [HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];
  int iPhi_ [HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];
  int depth_[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];
  int layer_[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];

  bool goodChannel_[HcalTBVLSBData::maxMotherBoards][HcalTBVLSBData::maxChannels];

  bool doInterpolate;

  int channelToLayer[16];
  int layerToChannel[16];

  bool zeroSuppression;
  double zeroSuppressionLevel;
};

const double HcalTBVLSBReconstructor::clockPeriod_= 1.0e9/160.0e6;//in ns

HcalTBVLSBReconstructor::HcalTBVLSBReconstructor(const edm::ParameterSet& iConfig)
{
  //produces<HBHERecHitCollection>();
  produces<HBHERecHitCollection>("VLSB");

  minSample_ = iConfig.getUntrackedParameter<unsigned int>("minSample", 0);
  maxSample_ = iConfig.getUntrackedParameter<unsigned int>("maxSample", 31);
  mipFileName = iConfig.getUntrackedParameter<std::string>("mipFileName", "");
  adcMapFileName = iConfig.getUntrackedParameter<std::string>("adcMapFileName", "");
  doInterpolate = iConfig.getUntrackedParameter<bool>("interpolate", false);

  zeroSuppression = iConfig.getUntrackedParameter<bool>("zeroSuppression", false);
  zeroSuppressionLevel = iConfig.getUntrackedParameter<double>("zeroSuppressionLevel", 10);

  buildMap();
}

HcalTBVLSBReconstructor::~HcalTBVLSBReconstructor()
{
}

void HcalTBVLSBReconstructor::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::auto_ptr<HBHERecHitCollection> rec(new HBHERecHitCollection);
  rec->reserve(HcalTBVLSBData::maxMotherBoards*HcalTBVLSBData::maxChannels);

  edm::Handle<VLSBInformation> hVlsbInfo;
  iEvent.getByType(hVlsbInfo);

  edm::Handle<HcalTBVLSBData> vlsb_data;
  iEvent.getByType(vlsb_data);
  
  for (int iMotherBoard=0;iMotherBoard<HcalTBVLSBData::maxMotherBoards;iMotherBoard++) {
    for (int iChannel=0;iChannel<HcalTBVLSBData::maxChannels;iChannel++) {
      double pedestalValue = hVlsbInfo->baseline[iMotherBoard][iChannel];
      
      double time=0.0;
      double maxSampleCharge=0.0;
      double totalCharge=0.0;
      bool goodData=true;

      bool zeroSuppressed = true;
      if(zeroSuppression == false)
         zeroSuppressed = false;
      if(zeroSuppression == true && goodChannel_[iMotherBoard][iChannel] == true)
      {
         for(int iSample = minSample_; iSample <= maxSample_ - 1; iSample++)
         {
            double adc = vlsb_data->adc(iMotherBoard, iChannel, iSample) - pedestalValue;
            adc = adc + vlsb_data->adc(iMotherBoard, iChannel, iSample + 1) - pedestalValue;

            if(adc > zeroSuppressionLevel)
               zeroSuppressed = false;
         }
      }

      for (int iSample=minSample_;iSample<=maxSample_;iSample++) {
	unsigned short adc=vlsb_data->adc(iMotherBoard,iChannel,iSample);

	if (adc==HcalTBVLSBData::badCode)
        {
	  goodData=false;
	  break;
	}

	double this_charge=adc-pedestalValue;
        this_charge = GetAdc(this_charge, iMotherBoard, iChannel);
	totalCharge+=this_charge;

        // if(iMotherBoard == 0 && iChannel == 12)
        //    printf("[Reconstructor] adc = %d, pedestal = %f, charge = %f, total = %f, mip = %f\n",
        //       adc, pedestalValue, this_charge, totalCharge, mip[iMotherBoard][iChannel]);

	if (this_charge>maxSampleCharge) {
	  maxSampleCharge=this_charge;
	  time=iSample*clockPeriod_;
	}
      } //end loop over samples
      
      double energy=totalCharge/mip[iMotherBoard][iChannel];

      if((goodChannel_[iMotherBoard][iChannel] == false || goodData == false) && doInterpolate == true)
      {
         int layer = channelToLayer[iChannel];

         int channel1 = 0;
         int channel2 = 0;

         double totalcharge1 = 0;
         double totalcharge2 = 0;

         if(layer == 0)
            channel1 = channel2 = layerToChannel[1];
         else if(layer == HcalTBVLSBData::maxChannels - 1)
            channel1 = channel2 = layerToChannel[HcalTBVLSBData::maxChannels-2];
         else
         {
            channel1 = layerToChannel[layer-1];
            channel2 = layerToChannel[layer+1];
         }

         for(int iSample = minSample_; iSample < maxSample_; iSample++)
         {
	    unsigned short adc1=vlsb_data->adc(iMotherBoard,channel1,iSample);
            totalcharge1 = totalcharge1 + (adc1 - hVlsbInfo->baseline[iMotherBoard][channel1]);

	    unsigned short adc2=vlsb_data->adc(iMotherBoard,channel2,iSample);
            totalcharge2 = totalcharge2 + (adc2 - hVlsbInfo->baseline[iMotherBoard][channel2]);
         }

         energy = totalcharge1 / mip[iMotherBoard][channel1];
         energy = energy + totalcharge2 / mip[iMotherBoard][channel2];

         energy = energy / 2;
      }

      //iPhi is _not_ standard--see buildMap()
      HcalDetId did(HcalBarrel,iEta_[iMotherBoard][iChannel],iPhi_[iMotherBoard][iChannel],depth_[iMotherBoard][iChannel]);

      if (goodData && goodChannel_[iMotherBoard][iChannel] && zeroSuppressed == false) rec->push_back(HBHERecHit(did,energy,time));
      else if(doInterpolate == true) rec->push_back(HBHERecHit(did, energy, time));

    } //end loop over channels
  } //end loop over motherboards

  iEvent.put(rec,"VLSB");
  
}

void HcalTBVLSBReconstructor::beginJob(const edm::EventSetup&)
{
  parseTextFiles();
}

void HcalTBVLSBReconstructor::parseTextFiles()
{
  for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++) {
    for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++) {
      mip[iMotherBoard][iChannel] = 1;
    }
  }
  
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
  
  if(adcMapFileName.size() != 0)
    {
      std::ifstream in(adcMapFileName.c_str());
      
      while(in)
	{
	  int motherboard = -1;
	  int layer = -1;
	  double adc = -1;
	  double imaginaryAdc = -1;
	  
	  in >> motherboard >> layer >> adc >> imaginaryAdc;
	  
	  if(motherboard == -1 || layer == -1)
	    continue;
	  
	  adcMap[motherboard][layerToChannel[layer]].push_back(std::pair<double, double>(adc, imaginaryAdc));
	}
      
      in.close();
      
      // for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      //    for(int iChannel = 0; iChannel < 16; iChannel++)
      //       sort(adcMap[iMotherBoard][iChannel].begin(), adcMap[iMotherBoard][iChannel].end());
    }
}

void HcalTBVLSBReconstructor::endJob()
{
}

void HcalTBVLSBReconstructor::buildMap()
{
  for(int iMotherBoard = 0; iMotherBoard < HcalTBVLSBData::maxMotherBoards; iMotherBoard++) {
    for(int iChannel = 0; iChannel < HcalTBVLSBData::maxChannels; iChannel++) {
      depth_[iMotherBoard][iChannel]=1;

      if (iMotherBoard==0) iEta_[iMotherBoard][iChannel]=8;
      if (iMotherBoard==1) iEta_[iMotherBoard][iChannel]=7;
      if (iMotherBoard==3) iEta_[iMotherBoard][iChannel]=9;

      if (iChannel<15)  layer_[iMotherBoard][iChannel]=iChannel+1;
      if (iChannel==15) layer_[iMotherBoard][iChannel]=0;

      //VLSB was always reading out iPhi=3; use "iphi" part of HcalDetId to store layer number
      iPhi_[iMotherBoard][iChannel]=50+layer_[iMotherBoard][iChannel];

      goodChannel_[iMotherBoard][iChannel]=true;
      if (iChannel==11)                   goodChannel_[iMotherBoard][iChannel]=false;
      if (iMotherBoard==3 && iChannel==2) goodChannel_[iMotherBoard][iChannel]=false;
      if (iMotherBoard==1 && iChannel==4) goodChannel_[iMotherBoard][iChannel]=false;
    }

  }


  for(int iChannel = 0; iChannel < 15; iChannel++){
    channelToLayer[iChannel] = iChannel + 1;
    layerToChannel[iChannel+1] = iChannel;
  }
  channelToLayer[15] = 0;
  layerToChannel[0] = 15;
  
}

double HcalTBVLSBReconstructor::GetAdc(double adc, int iMotherBoard, int iChannel)
{
   if(iMotherBoard >= HcalTBVLSBData::maxMotherBoards || iChannel > HcalTBVLSBData::maxChannels)   // something is wrong!!
      return -10000;

   if(adcMap[iMotherBoard][iChannel].size() == 0)   // no map for this channel~
      return adc;

   if(adcMap[iMotherBoard][iChannel][0].first > adc)   // in the linear region
      return adc;

   int mapSize = (int)adcMap[iMotherBoard][iChannel].size();
   if(adcMap[iMotherBoard][iChannel][mapSize-1].first < adc)   // saturated
      return adcMap[iMotherBoard][iChannel][mapSize-1].second;

   // search for the right one~
   int lowerlimit = 0;
   int upperlimit = mapSize - 1;

   while(upperlimit - lowerlimit > 1)
   {
      int center = (lowerlimit + upperlimit) / 2;

      if(adcMap[iMotherBoard][iChannel][center].first > adc)
         upperlimit = center;
      else
         lowerlimit = center;
   }

   double imaginaryAdc = (adc - adcMap[iMotherBoard][iChannel][lowerlimit].first) /
      (adcMap[iMotherBoard][iChannel][upperlimit].first - adcMap[iMotherBoard][iChannel][lowerlimit].first) *
      (adcMap[iMotherBoard][iChannel][upperlimit].second - adcMap[iMotherBoard][iChannel][lowerlimit].second) +
      adcMap[iMotherBoard][iChannel][lowerlimit].second;

   return imaginaryAdc;
}

//define this as a plug-in
DEFINE_FWK_MODULE(HcalTBVLSBReconstructor);
