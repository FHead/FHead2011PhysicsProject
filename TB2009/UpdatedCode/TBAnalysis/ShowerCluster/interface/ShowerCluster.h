#ifndef SHOWERCLUSTER_H
#define SHOWERCLUSTER_H

#include <map>

class ShowerCluster
{
public:   // I'm lazy.....
   double energy;  // total energy of the cluster
   double time;    // time of the cluster
   double depth;   // average depth weighted by energy
   std::map<int, int> boundary_start;   // min layer of samples
   std::map<int, int> boundary_end;     // max layer of samples
   double depth_rms;
   double time_rms;
   double remaining_energy;   // remaining energy before this shower starts
public:
   ShowerCluster();
   ~ShowerCluster();
};

#endif
