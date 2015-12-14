#include "TBAnalysis/ShowerCluster/interface/ShowerCluster.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include <vector>
#include <map>

namespace
{
   struct dictionary
   {
      ShowerCluster vInfo;
      edm::Wrapper<ShowerCluster> wVInfo;
      std::vector<ShowerCluster> vpdd;
      edm::Wrapper<std::vector<ShowerCluster> > wvpdd;
   };

}

