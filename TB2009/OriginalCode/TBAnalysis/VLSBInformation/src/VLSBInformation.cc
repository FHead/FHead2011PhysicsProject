#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"

VLSBInformation::VLSBInformation()
{
   maxMotherBoards = 4;
   maxChannels = 16;

   Initialize();
}

VLSBInformation::VLSBInformation(int _maxMotherBoards, int _maxChannels)
   : maxMotherBoards(_maxMotherBoards), maxChannels(_maxChannels)
{
   Initialize();
}

VLSBInformation::~VLSBInformation()
{
}

void VLSBInformation::Initialize()
{
   for(int iMotherBoards = 0; iMotherBoards < 4; iMotherBoards++)
   {
      for(int iChannels = 0; iChannels < 16; iChannels++)
      {
         baseline[iMotherBoards][iChannels] = 0;
         mip[iMotherBoards][iChannels] = 0;
         goodChannel[iMotherBoards][iChannels] = true;
         adcMap[iMotherBoards][iChannels].clear();
      }
   }

   minSample = 0;
   maxSample = 31;
   baselineSamples = 3;

   // for now, just list the bad channels here
   goodChannel[0][11] = false;
   goodChannel[1][11] = false;
   goodChannel[3][11] = false;
   goodChannel[1][4] = false;
   goodChannel[3][2] = false;

   useMotherBoard[0] = true;
   useMotherBoard[1] = false;
   useMotherBoard[2] = false;
   useMotherBoard[3] = false;

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
   {
      for(int iChannel = 0; iChannel < 15; iChannel++)
      {
         channelToLayer[iMotherBoard][iChannel] = iChannel + 1;
         layerToChannel[iMotherBoard][iChannel+1] = iChannel;
      }
      channelToLayer[iMotherBoard][15] = 0;
      layerToChannel[iMotherBoard][0] = 15;
   }

   motherBoardEta[0] = 8;
   motherBoardEta[1] = 7;
   motherBoardEta[2] = 1000;
   motherBoardEta[3] = 9;

   hitPosition[0] = 0;
   hitPosition[1] = 0;

   time = 0;
}

double VLSBInformation::GetAdc(double realAdc, int iMotherBoard, int iChannel) const
{
   if(iMotherBoard >= maxMotherBoards || iChannel > maxChannels)   // something is wrong!!
      return -10000;

   if(adcMap[iMotherBoard][iChannel].size() == 0)   // no map for this channel~
      return realAdc;

   if(adcMap[iMotherBoard][iChannel][0].first > realAdc)   // in the linear region
      return realAdc;

   int mapSize = (int)adcMap[iMotherBoard][iChannel].size();
   if(adcMap[iMotherBoard][iChannel][mapSize-1].first < realAdc)   // saturated
      return adcMap[iMotherBoard][iChannel][mapSize-1].second;

   // search for the right one~
   int lowerlimit = 0;
   int upperlimit = mapSize - 1;

   while(upperlimit - lowerlimit > 1)
   {
      int center = (lowerlimit + upperlimit) / 2;

      if(adcMap[iMotherBoard][iChannel][center].first > realAdc)
         upperlimit = center;
      else
         lowerlimit = center;
   }

   double imaginaryAdc = (realAdc - adcMap[iMotherBoard][iChannel][lowerlimit].first) /
      (adcMap[iMotherBoard][iChannel][upperlimit].first - adcMap[iMotherBoard][iChannel][lowerlimit].first) *
      (adcMap[iMotherBoard][iChannel][upperlimit].second - adcMap[iMotherBoard][iChannel][lowerlimit].second) +
      adcMap[iMotherBoard][iChannel][lowerlimit].second;

   return imaginaryAdc;
}


