#include <iostream>
#include <vector>
#include <map>

class VLSBInformation
{
public:   // I'm lazy.....
   int minSample;
   int maxSample;
   double baseline[4][16];   // will upgrade later to handle more general case
   double mip[4][16];   // muon calibration
   int maxMotherBoards;
   int maxChannels;
   int baselineSamples;
   int channelToLayer[4][16];
   int layerToChannel[4][16];
   bool goodChannel[4][16];
   bool useMotherBoard[4];
   int motherBoardEta[4];
   std::vector<std::pair<double, double> > adcMap[4][16];
   double beamEnergy;
   double hitPosition[2];
   double wireChamberHitsDistance2[3];   // distance from the extrapolated line to wire chamber hit position for chamber A, B, C
   double time;   // time of maximum of pulse in units of samples
   double channelTime[4][16];
public:
   VLSBInformation();
   VLSBInformation(int _maxMotherBoards, int _maxChannels);
   ~VLSBInformation();
   void Initialize();
   double GetAdc(double realAdc, int iMotherBoard, int iChannel) const;
};

