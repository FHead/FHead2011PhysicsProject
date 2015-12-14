#ifndef TBDATAFORMATS_HCALTBOBJECTS_HCALVLSBRECHIT
#define TBDATAFORMATS_HCALTBOBJECTS_HCALVLSBRECHIT

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include <ostream>

class HcalTBVLSBRecHit {
 public:
  typedef HcalDetId key_type;

  HcalTBVLSBRecHit();
  explicit HcalTBVLSBRecHit(const DetId& id, unsigned short layer, float energy, float time);
  virtual ~HcalTBVLSBRecHit();
  unsigned short layer() const { return layer_; }
  float energy() const { return energy_; }
  float time() const { return time_; }
  const DetId& detid() const { return id_; }
  HcalDetId id() const { return HcalDetId(detid()); }
 private:
  DetId id_;
  unsigned short layer_;
  float energy_;
  float time_;
};

std::ostream& operator<<(std::ostream& s, const HcalTBVLSBRecHit& hit);

#endif
