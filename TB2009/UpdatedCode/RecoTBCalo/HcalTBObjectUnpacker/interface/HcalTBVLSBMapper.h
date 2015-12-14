 #ifndef HCALTBVLSBMAPPER_H
#define HCALTBVLSBMAPPER_H 1
#include <map>

class HcalTBVLSBMapper {
public:
  HcalTBVLSBMapper();
  std::map<int,int>  socketToStripId_;
  std::map<int,int>  hcalFiberToStrip_;
  std::map<int,int>  preampLemoToSocket_;
  std::map<int,int>  moboToPreampLemo_;
private:
  void buildMaps();

  void buildPreampLemoToSocketMap();
  void insertPreampLemoToSocketElement(int preampBoard,int preampBoardChannel,int strip,int stripChannel);

  void buildSocketToStripIdMap();
  void insertSocketToStripIdElement(int stripId,int socketNumber);

  void buildMoboToPreampLemoMap();
  void insertMoboToPreampLemoElement(int mobo,int moboChannel,int preampBoard,int preampBoardChannel);

};

#endif
