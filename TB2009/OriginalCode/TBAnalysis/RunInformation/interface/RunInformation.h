#include <iostream>
#include <vector>
#include <map>

class RunInformation
{
public:   // I'm lazy.....
   double beamEnergy;
   double hitPosition[4];
   double wireChamberHitsDistance2[3];   // distance from the extrapolated line to wire chamber hit position for chamber A, B, C
public:
   RunInformation();
   ~RunInformation();
};

