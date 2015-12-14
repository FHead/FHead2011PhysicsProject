#include "TBAnalysis/VLSBInformation/interface/VLSBInformation.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include <vector>
#include <map>

namespace
{
   struct dictionary
   {
      VLSBInformation vInfo;
      edm::Wrapper<VLSBInformation> wVInfo;
      std::vector<std::pair<double,double> > vpdd;
      edm::Wrapper<std::vector<std::pair<double,double> > > wvpdd;
   };

}
