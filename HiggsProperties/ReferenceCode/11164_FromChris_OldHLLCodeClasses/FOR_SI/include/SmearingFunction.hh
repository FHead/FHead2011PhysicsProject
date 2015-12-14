#ifndef SmearFun_HH
#define SmearFun_HH

class SmearingFunction {
public:
  SmearingFunction(vector<TH1D*>, vector<TH1D*>);
  ~SmearingFunction();
  TLorentzVector SmearMuon(TLorentzVector genMuon);
  TLorentzVector SmearEle(TLorentzVector genEle);
  TLorentzVector SmearExtreme(TLorentzVector genMuon);

  private:
  TRandom3* _random;
  vector<TH1D*> _pTSmearing;
  vector<TH1D*> _etaSmearing;
  
  //New parameterization from Maurizio
  double pTBin[3];
  double etaBin[24];
  double deltapT[24][3];
  double deltaTheta[24][3];
  double deltaPhi[24][3];

  //Ele stuff
  double etaEle[21];
  double effEle[21];

};
#endif
