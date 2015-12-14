#include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBRecHit.h"

HcalTBVLSBRecHit::HcalTBVLSBRecHit() : energy_(0), time_(0) {
}

HcalTBVLSBRecHit::HcalTBVLSBRecHit(const DetId& id, unsigned short layer, float energy, float time) : id_(id),layer_(layer),energy_(energy), time_(time) {
}

HcalTBVLSBRecHit::~HcalTBVLSBRecHit() {
}

std::ostream& operator<<(std::ostream& s, const HcalTBVLSBRecHit& hit) {
  return s << hit.detid().rawId() << ", "<< hit.layer() << ", " << hit.energy() << " GeV, " << hit.time() << " ns";
}

