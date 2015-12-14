#ifndef HIGGSANA_HZZ4L_HZZEFFICIENCYMAP
#define HIGGSANA_HZZ4L_HZZEFFICIENCYMAP

#include <TObject.h>

// #define VARLIST_GENINFO "type/I:genpt/F:geneta/F:genphi/F:recopt/F:recoeta/F:recophi/F:recocharge/F:nvtx/I:pass/O:weight/F"

class HZZEfficiencyMap : public TObject 
{ 
  public:
    HZZEfficiencyMap(){}
    ~HZZEfficiencyMap(){}
    
    int type;
    float genpt,geneta,genphi;
    float recopt,recoeta,recophi;
    int recocharge;
    int nvtx;
    bool pass;
    float weight;

    // ClassDef(HZZEfficiencyMap,1)      
};

#endif

