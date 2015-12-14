#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TH1D.h>
#include <iostream>
#include <vector>
#include <SmearingFunction.hh>

using namespace std;

SmearingFunction::SmearingFunction(vector<TH1D*> pTSmear, 
				   vector<TH1D*> etaSmear) {
  _pTSmearing  = pTSmear;
  _etaSmearing = etaSmear;
  // set seed
  int jobpid   = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+jobpid;
  _random = new TRandom3(seed);

  pTBin[0] = 0.;
  pTBin[1] = 10.;
  pTBin[2] = 100.;
  for(int i=0; i<24; i++) etaBin[i] = 0.05+0.10*i;
  // pT smearing
  deltapT[0][0]  = 0.7077;  deltapT[0][1]  = 0.6465;  deltapT[0][2]  = 1.4579;
  deltapT[1][0]  = 0.7517;  deltapT[1][1]  = 0.6663;  deltapT[1][2]  = 1.4232;
  deltapT[2][0]  = 0.7840;  deltapT[2][1]  = 0.7250;  deltapT[2][2]  = 1.4579;
  deltapT[3][0]  = 0.8080;  deltapT[3][1]  = 0.7700;  deltapT[3][2]  = 1.4667;
  deltapT[4][0]  = 0.8579;  deltapT[4][1]  = 0.7983;  deltapT[4][2]  = 1.5024;
  deltapT[5][0]  = 0.8479;  deltapT[5][1]  = 0.8227;  deltapT[5][2]  = 1.4845;
  deltapT[6][0]  = 0.8686;  deltapT[6][1]  = 0.8277;  deltapT[6][2]  = 1.5298;
  deltapT[7][0]  = 0.9224;  deltapT[7][1]  = 0.8897;  deltapT[7][2]  = 1.5484;
  deltapT[8][0]  = 1.0219;  deltapT[8][1]  = 0.9114;  deltapT[8][2]  = 1.6248;
  deltapT[9][0]  = 1.0594;  deltapT[9][1]  = 1.0594;  deltapT[9][2]  = 1.9465;
  deltapT[10][0] = 1.1389;  deltapT[10][1] = 1.0985;  deltapT[10][2] = 1.9348;
  deltapT[11][0] = 1.2243;  deltapT[11][1] = 1.1597;  deltapT[11][2] = 1.8437;
  deltapT[12][0] = 1.3081;  deltapT[12][1] = 1.2023;  deltapT[12][2] = 1.9940;
  deltapT[13][0] = 1.3977;  deltapT[13][1] = 1.2692;  deltapT[13][2] = 2.0798;
  deltapT[14][0] = 1.3893;  deltapT[14][1] = 1.2317;  deltapT[14][2] = 2.1178;
  deltapT[15][0] = 1.3810;  deltapT[15][1] = 1.2317;  deltapT[15][2] = 2.0674;
  deltapT[16][0] = 1.3240;  deltapT[16][1] = 1.2096;  deltapT[16][2] = 2.0924;
  deltapT[17][0] = 1.3977;  deltapT[17][1] = 1.2617;  deltapT[17][2] = 2.2388;
  deltapT[18][0] = 1.3810;  deltapT[18][1] = 1.3810;  deltapT[18][2] = 2.7770;
  deltapT[19][0] = 1.4404;  deltapT[19][1] = 1.4404;  deltapT[19][2] = 3.0031;
  deltapT[20][0] = 1.5114;  deltapT[20][1] = 1.5114;  deltapT[20][2] = 3.2477;
  deltapT[21][0] = 1.6745;  deltapT[21][1] = 1.6745;  deltapT[21][2] = 4.1323;
  deltapT[22][0] = 1.7570;  deltapT[22][1] = 1.8888;  deltapT[22][2] = 5.2896;
  deltapT[23][0] = 1.9583;  deltapT[23][1] = 2.0798;  deltapT[23][2] = 6.8944;
  
  // Theta smearing
  deltaTheta[0][0]  = 2.5295;  deltaTheta[0][1]  = 0.5971;  deltaTheta[0][2]  = 0.4701;
  deltaTheta[1][0]  = 2.5019;  deltaTheta[1][1]  = 0.5240;  deltaTheta[1][2]  = 0.4251;
  deltaTheta[2][0]  = 2.4501;  deltaTheta[2][1]  = 0.4739;  deltaTheta[2][2]  = 0.3695;
  deltaTheta[3][0]  = 2.4477;  deltaTheta[3][1]  = 0.4415;  deltaTheta[3][2]  = 0.3147;
  deltaTheta[4][0]  = 2.5958;  deltaTheta[4][1]  = 0.4239;  deltaTheta[4][2]  = 0.2846;
  deltaTheta[5][0]  = 2.6985;  deltaTheta[5][1]  = 0.4495;  deltaTheta[5][2]  = 0.2930;
  deltaTheta[6][0]  = 2.9781;  deltaTheta[6][1]  = 0.5110;  deltaTheta[6][2]  = 0.3364;
  deltaTheta[7][0]  = 3.1271;  deltaTheta[7][1]  = 0.5530;  deltaTheta[7][2]  = 0.3328;
  deltaTheta[8][0]  = 3.5203;  deltaTheta[8][1]  = 0.5749;  deltaTheta[8][2]  = 0.3494;
  deltaTheta[9][0]  = 3.6233;  deltaTheta[9][1]  = 0.5976;  deltaTheta[9][2]  = 0.3422;
  deltaTheta[10][0] = 4.2451;  deltaTheta[10][1] = 0.6595;  deltaTheta[10][2] = 0.3557;
  deltaTheta[11][0] = 4.6385;  deltaTheta[11][1] = 0.7206;  deltaTheta[11][2] = 0.3484;
  deltaTheta[12][0] = 5.1703;  deltaTheta[12][1] = 0.7953;  deltaTheta[12][2] = 0.3731;
  deltaTheta[13][0] = 6.0571;  deltaTheta[13][1] = 0.8776;  deltaTheta[13][2] = 0.4243;
  deltaTheta[14][0] = 6.8874;  deltaTheta[14][1] = 0.9495;  deltaTheta[14][2] = 0.4238;
  deltaTheta[15][0] = 7.7536;  deltaTheta[15][1] = 1.0905;  deltaTheta[15][2] = 0.4724;
  deltaTheta[16][0] = 9.1746;  deltaTheta[16][1] = 1.2277;  deltaTheta[16][2] = 0.4815;
  deltaTheta[17][0] = 10.432;  deltaTheta[17][1] = 1.3149;  deltaTheta[17][2] = 0.5056;
  deltaTheta[18][0] = 12.222;  deltaTheta[18][1] = 1.5715;  deltaTheta[18][2] = 0.5361;
  deltaTheta[19][0] = 14.176;  deltaTheta[19][1] = 1.7170;  deltaTheta[19][2] = 0.6157;
  deltaTheta[20][0] = 15.960;  deltaTheta[20][1] = 1.9139;  deltaTheta[20][2] = 0.6728;
  deltaTheta[21][0] = 19.265;  deltaTheta[21][1] = 2.2424;  deltaTheta[21][2] = 0.8284;
  deltaTheta[22][0] = 22.124;  deltaTheta[22][1] = 2.6797;  deltaTheta[22][2] = 1.0099;
  deltaTheta[23][0] = 24.174;  deltaTheta[23][1] = 2.9870;  deltaTheta[23][2] = 1.2942;
  
  // Phi smearing
  deltaPhi[0][0]  = 2.0584;  deltaPhi[0][1]  = 0.3051;  deltaPhi[0][2]  = 0.0819;
  deltaPhi[1][0]  = 2.0379;  deltaPhi[1][1]  = 0.3220;  deltaPhi[1][2]  = 0.0798;
  deltaPhi[2][0]  = 1.9992;  deltaPhi[2][1]  = 0.3188;  deltaPhi[2][2]  = 0.0081;
  deltaPhi[3][0]  = 2.1097;  deltaPhi[3][1]  = 0.3155;  deltaPhi[3][2]  = 0.0817;
  deltaPhi[4][0]  = 2.0697;  deltaPhi[4][1]  = 0.3331;  deltaPhi[4][2]  = 0.0839;
  deltaPhi[5][0]  = 2.1449;  deltaPhi[5][1]  = 0.3237;  deltaPhi[5][2]  = 0.0823;
  deltaPhi[6][0]  = 2.2226;  deltaPhi[6][1]  = 0.3386;  deltaPhi[6][2]  = 0.0822;
  deltaPhi[7][0]  = 2.3032;  deltaPhi[7][1]  = 0.3445;  deltaPhi[7][2]  = 0.0821;
  deltaPhi[8][0]  = 2.4982;  deltaPhi[8][1]  = 0.3570;  deltaPhi[8][2]  = 0.0836;
  deltaPhi[9][0]  = 2.4284;  deltaPhi[9][1]  = 0.3633;  deltaPhi[9][2]  = 0.0898;
  deltaPhi[10][0] = 2.4708;  deltaPhi[10][1] = 0.3696;  deltaPhi[10][2] = 0.0897;
  deltaPhi[11][0] = 2.7296;  deltaPhi[11][1] = 0.3830;  deltaPhi[11][2] = 0.0880;
  deltaPhi[12][0] = 2.7774;  deltaPhi[12][1] = 0.3969;  deltaPhi[12][2] = 0.0929;
  deltaPhi[13][0] = 2.9312;  deltaPhi[13][1] = 0.4076;  deltaPhi[13][2] = 0.0954;
  deltaPhi[14][0] = 3.1794;  deltaPhi[14][1] = 0.4072;  deltaPhi[14][2] = 0.0998;
  deltaPhi[15][0] = 3.2648;  deltaPhi[15][1] = 0.4377;  deltaPhi[15][2] = 0.1015;
  deltaPhi[16][0] = 3.4771;  deltaPhi[16][1] = 0.4373;  deltaPhi[16][2] = 0.0969;
  deltaPhi[17][0] = 3.5058;  deltaPhi[17][1] = 0.4700;  deltaPhi[17][2] = 0.1080;
  deltaPhi[18][0] = 3.9083;  deltaPhi[18][1] = 0.4696;  deltaPhi[18][2] = 0.1118;
  deltaPhi[19][0] = 4.0872;  deltaPhi[19][1] = 0.5001;  deltaPhi[19][2] = 0.1170;
  deltaPhi[20][0] = 4.1210;  deltaPhi[20][1] = 0.5135;  deltaPhi[20][2] = 0.1224;
  deltaPhi[21][0] = 4.4292;  deltaPhi[21][1] = 0.5520;  deltaPhi[21][2] = 0.1390;
  deltaPhi[22][0] = 4.6745;  deltaPhi[22][1] = 0.5718;  deltaPhi[22][2] = 0.1529;
  deltaPhi[23][0] = 4.8000;  deltaPhi[23][1] = 0.5927;  deltaPhi[23][2] = 0.1858;
  
  for(int i=0; i<21; i++) etaEle[i]  = i*(2.4/20.);
  
  effEle[0] =  0.880;
  effEle[1] =  0.917;
  effEle[2] =  0.924;
  effEle[3] =  0.897;
  effEle[4] =  0.921;
  effEle[5] =  0.929;
  effEle[6] =  0.896;
  effEle[7] =  0.927;
  effEle[8] =  0.917;
  effEle[9] =  0.871;
  effEle[10] = 0.895;
  effEle[11] = 0.865;
  effEle[12] = 0.536;
  effEle[13] = 0.881;
  effEle[14] = 0.902;
  effEle[15] = 0.910;
  effEle[16] = 0.904;
  effEle[17] = 0.884;
  effEle[18] = 0.824;
  effEle[19] = 0.60;
  effEle[20] = 0.;
}

TLorentzVector SmearingFunction::SmearMuon(TLorentzVector genMuon) {

  double eta = genMuon.Eta();
  double phi = genMuon.Phi();
  double pT = fabs(genMuon.Pt());
  double M = genMuon.M();

  TLorentzVector recoMuon;

  // find the edges of eta bin
  int iEta = 23;
  for(int j=0; j<23; j++) {
    if(fabs(eta)>=etaBin[j] && fabs(eta)<etaBin[j+1]) {
      iEta = j;
      j = 24;
    }
  }
  // find the edges of pT bin
  int ipT = 2;
  for(int j=0; j<2; j++)
    if(pT>=pTBin[j] && pT<pTBin[j+1])
      ipT = j;
  // apply pT smearing
  double sigmalow = deltapT[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltapT[iEta+1][ipT]-deltapT[iEta][ipT]);
  double sigmahigh = deltapT[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltapT[iEta+1][ipT+1]-deltapT[iEta][ipT+1]);
  double sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);
  pT = gRandom->Gaus(pT,sigma);
  // apply eta smearing
  sigmalow = deltaTheta[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT]-deltaTheta[iEta][ipT]);
  sigmahigh = deltaTheta[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT+1]-deltaTheta[iEta][ipT+1]);
  sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);
  double theta = 2.*atan(exp(-eta));
  theta = atan(1./gRandom->Gaus(1./tan(theta),sigma*0.001));
  if(theta<0.) theta += asin(1.)*2.;
  double etanew = -log(tan(theta/2.));
  // apply phi smearing
  sigmalow = deltaPhi[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT]-deltaPhi[iEta][ipT]);
  sigmahigh = deltaPhi[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT+1]-deltaPhi[iEta][ipT+1]);
  sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);      
  phi = gRandom->Gaus(phi,sigma*0.001);
  
  recoMuon.SetPtEtaPhiM(pT,etanew,phi,M);

  return recoMuon;
}

TLorentzVector SmearingFunction::SmearEle(TLorentzVector genEle) {
  double eta = genEle.Eta();
  double theta = genEle.Theta();
  double phi = genEle.Phi();
  double pT = fabs(genEle.Pt());
  double P = fabs(genEle.P());
  double M = genEle.M();

  TLorentzVector recoEle;

  
  // find the edges of pT bin
  int ipT = 2;
  for(int j=0; j<2; j++)
    if(pT>=pTBin[j] && pT<pTBin[j+1])
      ipT = j;
  
  // resolution page PTDR VOL1 PAG 400
  double Cele_SHOWER = 0.018;
  double Cele_OTHER  = 0.010;
  // electron classes PTDR VOL1 PAG 397
  double fSHOWER = 0.60;

  
  int iEta=-99;
  TLorentzVector particle;

 
  // find the eta bin for ele momentum smearing
  iEta=20;
  for(int j=0; j<20; j++)
    if(fabs(eta) >= etaEle[j] && fabs(eta) <  etaEle[j+1]) {
      iEta = j;
      j = 20;
    }
  //efficiency
  double myrndm = gRandom->Rndm();
  if(myrndm <= effEle[iEta]) {
    // shower electron or not
    bool shower = (gRandom->Rndm() < fSHOWER ? true : false);
    // resolution
    double p = (shower == true ?
		gRandom->Gaus(P,Cele_SHOWER*P) :
		gRandom->Gaus(P,Cele_OTHER*P));
    pT = sin(theta)*p;
  } else {
    pT = 3.0;
  }

  // find the edges of eta bin
  iEta = 23;
  for(int j=0; j<23; j++) {
    if(fabs(eta)>=etaBin[j] && fabs(eta)<etaBin[j+1]) {
      iEta = j;
      j = 24;
    }
  }
  
  
  // apply eta smearing
  double sigmalow = deltaTheta[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT]-deltaTheta[iEta][ipT]);
  double sigmahigh = deltaTheta[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT+1]-deltaTheta[iEta][ipT+1]);
  double sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);
  theta = 2.*atan(exp(-eta));
  theta = atan(1./gRandom->Gaus(1./tan(theta),sigma*0.001));
  if(theta<0.) theta += asin(1.)*2.;
  double etanew = -log(tan(theta/2.));
  // apply phi smearing
  sigmalow = deltaPhi[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT]-deltaPhi[iEta][ipT]);
  sigmahigh = deltaPhi[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT+1]-deltaPhi[iEta][ipT+1]);
  sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);      
  phi = gRandom->Gaus(phi,sigma*0.001);
  
  recoEle.SetPtEtaPhiM(pT,etanew,phi,M);

  return recoEle;
}

TLorentzVector SmearingFunction::SmearExtreme(TLorentzVector genMuon) {

  double eta = genMuon.Eta();
  double phi = genMuon.Phi();
  double pT = fabs(genMuon.Pt());
  double M = genMuon.M();

  TLorentzVector recoMuon;

  // find the edges of eta bin
  int iEta = 23;
  for(int j=0; j<23; j++) {
    if(fabs(eta)>=etaBin[j] && fabs(eta)<etaBin[j+1]) {
      iEta = j;
      j = 24;
    }
  }
  // find the edges of pT bin
  int ipT = 2;
  for(int j=0; j<2; j++)
    if(pT>=pTBin[j] && pT<pTBin[j+1])
      ipT = j;
  // apply pT smearing
  double sigmalow = deltapT[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltapT[iEta+1][ipT]-deltapT[iEta][ipT]);
  double sigmahigh = deltapT[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltapT[iEta+1][ipT+1]-deltapT[iEta][ipT+1]);
  double sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);
  pT = gRandom->Gaus(pT,10.0*sigma);
  // apply eta smearing
  sigmalow = deltaTheta[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT]-deltaTheta[iEta][ipT]);
  sigmahigh = deltaTheta[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaTheta[iEta+1][ipT+1]-deltaTheta[iEta][ipT+1]);
  sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);
  double theta = 2.*atan(exp(-eta));
  theta = atan(1./gRandom->Gaus(1./tan(theta),sigma*0.001));
  if(theta<0.) theta += asin(1.)*2.;
  double etanew = -log(tan(theta/2.));
  // apply phi smearing
  sigmalow = deltaPhi[iEta][ipT] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT]-deltaPhi[iEta][ipT]);
  sigmahigh = deltaPhi[iEta][ipT+1] +
    (fabs(eta)-etaBin[iEta])/(etaBin[iEta+1]-etaBin[iEta])*
    (deltaPhi[iEta+1][ipT+1]-deltaPhi[iEta][ipT+1]);
  sigma = sigmalow + (pT-pTBin[ipT])/(pTBin[ipT+1]-pTBin[ipT])*(sigmahigh-sigmalow);      
  phi = gRandom->Gaus(phi,sigma*0.001);
  
  recoMuon.SetPtEtaPhiM(pT,etanew,phi,M);

  return recoMuon;
}
