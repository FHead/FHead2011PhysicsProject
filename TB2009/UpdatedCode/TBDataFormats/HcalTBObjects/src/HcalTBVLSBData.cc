#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"

HcalTBVLSBData::HcalTBVLSBData() {}

void HcalTBVLSBData::setAdc(int iMotherBoard,int iChannel,int iSample,unsigned short adc) {
  data_[iMotherBoard][iChannel][iSample]=adc;
}
unsigned short HcalTBVLSBData::adc(int iMotherBoard,int iChannel,int iSample) const {
  if (iMotherBoard<0 || iMotherBoard>=maxMotherBoards) return badCode;
  if (iChannel<0 || iChannel>=maxChannels) return badCode;
  if (iSample<0 || iSample>=maxSamples) return badCode;
  return data_[iMotherBoard][iChannel][iSample];
}
