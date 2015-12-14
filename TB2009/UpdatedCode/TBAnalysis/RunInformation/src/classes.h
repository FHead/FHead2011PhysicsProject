#include "TBAnalysis/RunInformation/interface/RunInformation.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include <vector>
#include <map>

namespace
{
   struct dictionary
   {
      RunInformation vInfo;
      edm::Wrapper<RunInformation> wVInfo;
      std::vector<std::pair<double,double> > vpdd;
      edm::Wrapper<std::vector<std::pair<double,double> > > wvpdd;
   };

}
