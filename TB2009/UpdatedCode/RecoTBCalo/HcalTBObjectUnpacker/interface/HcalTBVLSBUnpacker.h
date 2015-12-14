#ifndef HCALTBVLSBUNPACKER_H
#define HCALTBVLSBUNPACKER_H 1
#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
//#include "RecoTBCalo/HcalTBObjectUnpacker/interface/HcalTBVLSBMapper.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"
#include <map>

namespace hcaltb {
class HcalTBVLSBUnpacker {
public:
  HcalTBVLSBUnpacker();
  ~HcalTBVLSBUnpacker();
  static const int nWordsExpected=HcalTBVLSBData::maxMotherBoards*HcalTBVLSBData::maxChannels*HcalTBVLSBData::maxSamples/2;
  //void unpack(const FEDRawData& raw,HcalTBVLSBData& vlsbdata) const;
  void unpack(const FEDRawData& raw,HcalTBVLSBData& vlsbdata);
private:
  std::vector<int> badWordCounts_;
};

}

#endif
