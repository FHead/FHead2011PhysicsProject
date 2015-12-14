#ifndef HCALTBVLSBDATA_H
#define HCALTBVLSBDATA_H 1

#include <string>
#include <iostream>
#include <vector>

class HcalTBVLSBData {
 public:
  HcalTBVLSBData();
  static const int maxMotherBoards=4;
  static const int maxChannels=16;
  static const int maxSamples=32;
  static const unsigned short badCode=0xFFFF;
  void setAdc(int iMotherBoard,int iChannel,int iSample,unsigned short adc);
  unsigned short adc(int iMotherBoard,int iChannel,int iSample) const;
 private:
  unsigned short data_[maxMotherBoards][maxChannels][maxSamples];
};
#endif
