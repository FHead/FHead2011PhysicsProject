#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164062862089986280348253421170679

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage " << argv[0] << " InputFile CrossSection OutputFile [PileupFile]" << endl;
      cerr << "   Enter negative cross section for data" << endl;
      cerr << "   The pile-up file contains a histogram with desired weights" << endl;
      cerr << "   in the absence of pile-up file there will be no pile-up re-weighting." << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[3];

   string PileupFile = "";
   if(argc >= 5)
      PileupFile = argv[4];

   stringstream sigmastr(argv[2]);
   double CrossSection = -1;
   sigmastr >> CrossSection;

   cout << "Running with parameters " << argv[1] << " " << argv[2] << " " << argv[3] << " " << endl;

   TChain Tree("ReducedTree", "ReducedTree");
   Tree.AddFile(Input.c_str());

   double MR = 0;
   double R = 0;
   double MR11 = 0;
   double R11 = 0;
   int LooseBTagCount = 0;
   int MediumBTagCount = 0;
   int TightBTagCount = 0;
   int PileUpCount = 0;
   int GoodMuonTight = 0;
   int GoodMuonLoose = 0;
   int GoodElectronTight = 0;
   int GoodElectronLoose = 0;
   double JetPT = 0;
   double MuonPT = 0;
   double ElectronPT = 0;
   int PhotonCount = 0;
   double PhotonEcalIsolation[10] = {0};
   double PhotonHcalIsolation[10] = {0};
   double PhotonTrackIsolation[10] = {0};
   double PhotonPT[10] = {0};
   double PhotonEta[10] = {0};
   double PhotonSigmaIEtaIEta[10] = {0};
   double PhotonHOverE[10] = {0};
   double PhotonR9[10] = {0};
   bool PhotonSeed[10] = {false};
   double Rho = 0;

   Tree.SetBranchAddress("MR", &MR);
   Tree.SetBranchAddress("R", &R);
   Tree.SetBranchAddress("MR11", &MR11);
   Tree.SetBranchAddress("R11", &R11);
   Tree.SetBranchAddress("LooseBTagCount", &LooseBTagCount);
   Tree.SetBranchAddress("MediumBTagCount", &MediumBTagCount);
   Tree.SetBranchAddress("TightBTagCount", &TightBTagCount);
   Tree.SetBranchAddress("PileupCount", &PileUpCount);
   Tree.SetBranchAddress("GoodMuonCountTight", &GoodMuonTight);
   Tree.SetBranchAddress("GoodMuonCountLoose", &GoodMuonLoose);
   Tree.SetBranchAddress("GoodElectronCountTight", &GoodElectronTight);
   Tree.SetBranchAddress("GoodElectronCountLoose", &GoodElectronLoose);
   Tree.SetBranchAddress("Jet1PT", &JetPT);
   Tree.SetBranchAddress("MuonPT", &MuonPT);
   Tree.SetBranchAddress("ElectronPT", &ElectronPT);
   Tree.SetBranchAddress("PhotonCount", &PhotonCount);
   Tree.SetBranchAddress("AllPhotonEcalIsolation", PhotonEcalIsolation);
   Tree.SetBranchAddress("AllPhotonHcalIsolation", PhotonHcalIsolation);
   Tree.SetBranchAddress("AllPhotonTrackIsolation", PhotonTrackIsolation);
   Tree.SetBranchAddress("AllPhotonPT", PhotonPT);
   Tree.SetBranchAddress("AllPhotonHOverE", PhotonHOverE);
   Tree.SetBranchAddress("AllPhotonEta", PhotonEta);
   Tree.SetBranchAddress("AllPhotonSigmaIEtaIEta", PhotonSigmaIEtaIEta);
   Tree.SetBranchAddress("AllPhotonR9", PhotonR9);
   Tree.SetBranchAddress("AllPhotonSeed", PhotonSeed);
   Tree.SetBranchAddress("Rho", &Rho);

   TFile InputFile(Input.c_str());
   double TotalWeight = ((TH1D *)InputFile.Get("HPileUpCount"))->Integral();
   InputFile.Close();

   TFile OutputFile(Output.c_str(), "RECREATE");

   string Selection[8] = {"Had", "TightMuon", "LooseMuon", "TightElectron", "LooseElectron",
      "LooseMuEle", "TightMuEle", "Photon"};
   string BTagger[8] = {"All", "NoTag", "OneLoose", "TwoLoose", "OneMedium", "TwoMedium", "OneTight", "TwoTight"};

   TH1D *HMR_R2000[8][8] = {NULL};
   TH1D *HMR_R2020[8][8] = {NULL};
   TH1D *HMR_R2025[8][8] = {NULL};
   TH1D *HMR_R2030[8][8] = {NULL};
   TH1D *HMR_R2035[8][8] = {NULL};
   TH1D *HMR_R2040[8][8] = {NULL};
   TH1D *HMR_R2045[8][8] = {NULL};
   TH1D *HMR_R2050[8][8] = {NULL};
   TH1D *HR2_MR000[8][8] = {NULL};
   TH1D *HR2_MR100[8][8] = {NULL};
   TH1D *HR2_MR200[8][8] = {NULL};
   TH1D *HR2_MR300[8][8] = {NULL};
   TH1D *HR2_MR400[8][8] = {NULL};
   TH1D *HR2_MR500[8][8] = {NULL};
   TH1D *HMR11_R112000[8][8] = {NULL};
   TH1D *HMR11_R112020[8][8] = {NULL};
   TH1D *HMR11_R112040[8][8] = {NULL};
   TH1D *HMR11_R112050[8][8] = {NULL};
   TH1D *HMR11_R112060[8][8] = {NULL};
   TH1D *HMR11_R112070[8][8] = {NULL};
   TH1D *HMR11_R112080[8][8] = {NULL};
   TH1D *HMR11_R112090[8][8] = {NULL};
   TH1D *HR112_MR11000[8][8] = {NULL};
   TH1D *HR112_MR11100[8][8] = {NULL};
   TH1D *HR112_MR11200[8][8] = {NULL};
   TH1D *HR112_MR11300[8][8] = {NULL};
   TH1D *HR112_MR11400[8][8] = {NULL};
   TH1D *HR112_MR11500[8][8] = {NULL};
   TH1D *HJetPT[8][8] = {NULL};
   TH1D *HElectronPT[8][8] = {NULL};
   TH1D *HMuonPT[8][8] = {NULL};
   TH1D *HJetPT_MR400R2025[8][8] = {NULL};
   TH1D *HElectronPT_MR400R2025[8][8] = {NULL};
   TH1D *HMuonPT_MR400R2025[8][8] = {NULL};
   TH1D *HPhotonPT[8][8] = {NULL};   // leading good photon
   TH1D *HPhotonIsolation[8][8] = {NULL};
   TH1D *HPhotonHOverE[8][8] = {NULL};
   TH1D *HPhotonSigmaIEtaIEta[8][8] = {NULL};
   TH1D *HPhotonR9[8][8] = {NULL};
   TH1D *HAllPhotonPT[8][8] = {NULL};   // all photon candidates
   TH1D *HAllPhotonIsolation[8][8] = {NULL};   // N-1 plots
   TH1D *HAllPhotonHOverE[8][8] = {NULL};
   TH1D *HAllPhotonSigmaIEtaIEta[8][8] = {NULL};
   TH1D *HAllPhotonR9[8][8] = {NULL};

   TH2D *HMRRMap[8][8] = {NULL};

   for(int i = 0; i < 8; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         HMR_R2000[i][j] = new TH1D(Form("HMR_R2000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.00, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2020[i][j] = new TH1D(Form("HMR_R2020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2025[i][j] = new TH1D(Form("HMR_R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2030[i][j] = new TH1D(Form("HMR_R2030_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.30, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2035[i][j] = new TH1D(Form("HMR_R2035_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.35, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2040[i][j] = new TH1D(Form("HMR_R2040_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.40, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2045[i][j] = new TH1D(Form("HMR_R2045_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.45, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2050[i][j] = new TH1D(Form("HMR_R2050_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.50, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         
         HR2_MR000[i][j] = new TH1D(Form("HR2_MR000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 0, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2_MR100[i][j] = new TH1D(Form("HR2_MR100_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 100, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2_MR200[i][j] = new TH1D(Form("HR2_MR200_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 200, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2_MR300[i][j] = new TH1D(Form("HR2_MR300_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 300, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2_MR400[i][j] = new TH1D(Form("HR2_MR400_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2_MR500[i][j] = new TH1D(Form("HR2_MR500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 500, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HMR11_R112000[i][j] = new TH1D(Form("HMR11_R112000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.00, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112020[i][j] = new TH1D(Form("HMR11_R112020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.20, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112040[i][j] = new TH1D(Form("HMR11_R112040_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.40, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112050[i][j] = new TH1D(Form("HMR11_R112050_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.50, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112060[i][j] = new TH1D(Form("HMR11_R112060_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.60, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112070[i][j] = new TH1D(Form("HMR11_R112070_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.70, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112080[i][j] = new TH1D(Form("HMR11_R112080_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.80, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112090[i][j] = new TH1D(Form("HMR11_R112090_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.90, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         
         HR112_MR11000[i][j] = new TH1D(Form("HR112_MR11000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 0, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR112_MR11100[i][j] = new TH1D(Form("HR112_MR11100_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 100, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR112_MR11200[i][j] = new TH1D(Form("HR112_MR11200_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 200, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR112_MR11300[i][j] = new TH1D(Form("HR112_MR11300_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 300, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR112_MR11400[i][j] = new TH1D(Form("HR112_MR11400_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 400, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR112_MR11500[i][j] = new TH1D(Form("HR112_MR11500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2 (11)}, MR11 > 500, (%s), (%s);R^{2 (11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HJetPT[i][j] = new TH1D(Form("HJetPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading jet PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMuonPT[i][j] = new TH1D(Form("HMuonPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading muon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HElectronPT[i][j] = new TH1D(Form("HElectronPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading electron PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         
         HJetPT_MR400R2025[i][j] = new TH1D(Form("HJetPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading jet PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMuonPT_MR400R2025[i][j] = new TH1D(Form("HMuonPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading muon PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HElectronPT_MR400R2025[i][j] = new TH1D(Form("HElectronPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading electron PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);

         HPhotonPT[i][j] = new TH1D(Form("HPhotonPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 450);
         HPhotonIsolation[i][j] = new TH1D(Form("HPhotonIsolation_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon Isolation, (%s), (%s);Isolation", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 20);
         HPhotonHOverE[i][j] = new TH1D(Form("HPhotonHOverE_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon H/E, (%s), (%s);H/E", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 0.5);
         HPhotonSigmaIEtaIEta[i][j] = new TH1D(Form("HPhotonSigmaIEtaIEta_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon SigmaIEtaIEta, (%s), (%s)", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 0.05);
         HPhotonR9[i][j] = new TH1D(Form("HPhotonR9_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon R9, (%s), (%s);R9", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);

         HAllPhotonPT[i][j] = new TH1D(Form("HAllPhotonPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("All good photon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 450);
         HAllPhotonIsolation[i][j] = new TH1D(Form("HAllPhotonIsolation_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("All good (N-1) photon Isolation, (%s), (%s);Isolation", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 20);
         HAllPhotonHOverE[i][j] = new TH1D(Form("HAllPhotonHOverE_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("All good (N-1) photon H/E, (%s), (%s);H/E", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 0.5);
         HAllPhotonSigmaIEtaIEta[i][j] = new TH1D(Form("HAllPhotonSigmaIEtaIEta_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("All good (N-1) photon SigmaIEtaIEta, (%s), (%s)", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 0.05);
         HAllPhotonR9[i][j] = new TH1D(Form("HAllPhotonR9_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("All good (N-1) photon R9, (%s), (%s);R9", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);

         HMRRMap[i][j] = new TH2D(Form("HMRRMap_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Yield in M_{R}/R^{2} bins;M_{R};R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            15, 0, 1500, 10, 0, 1);
      }
   }

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      double Weight = 1;
      // TotalWeight = TotalWeight + Weight;

      int GoodPhotonCount = 0;
      int FirstPhotonIndex = -1;
      double PhotonIsolation[10] = {0};
      for(int i = 0; i < PhotonCount; i++)
      {
         PhotonIsolation[i] = PhotonHcalIsolation[i] + PhotonEcalIsolation[i] + PhotonTrackIsolation[i];

         if(PhotonSeed[i] == true)                           continue;
         if(PhotonPT[i] < 30)                                continue;
         if(fabs(PhotonEta[i]) > 1.569)                      continue;
         if(PhotonSigmaIEtaIEta[i] > 0.011)                  continue;
         if(PhotonR9[i] > 1 || PhotonR9[i] < 0.8)            continue;
         if(PhotonHOverE[i] > 0.05)                          continue;
         if(PhotonIsolation[i] - Rho * PI * 0.4 * 0.4 > 6)   continue;

         GoodPhotonCount = GoodPhotonCount + 1;
         if(FirstPhotonIndex == -1)
            FirstPhotonIndex = i;
      }

      for(int i = 0; i < 8; i++)
      {
         if(i == 0 && (GoodMuonLoose > 0 || GoodElectronLoose > 0))     continue;
         if(i == 1 && GoodMuonTight != 1)                               continue;
         if(i == 2 && GoodMuonLoose != 1)                               continue;
         if(i == 3 && GoodElectronTight != 1)                           continue;
         if(i == 4 && GoodElectronLoose != 1)                           continue;
         if(i == 5 && (GoodElectronLoose == 0 || GoodMuonLoose == 0))   continue;
         if(i == 6 && (GoodElectronTight == 0 || GoodMuonTight == 0))   continue;
         if(i == 7 && GoodPhotonCount == 0)                             continue;

         for(int j = 0; j < 8; j++)
         {
            if(j == 1 && LooseBTagCount != 0)    continue;
            if(j == 2 && LooseBTagCount != 1)    continue;
            if(j == 3 && LooseBTagCount < 2)     continue;
            if(j == 4 && MediumBTagCount != 1)   continue;
            if(j == 5 && MediumBTagCount < 2)    continue;
            if(j == 6 && TightBTagCount != 1)    continue;
            if(j == 7 && TightBTagCount < 2)     continue;

            if(R * R > 0.00)    HMR_R2000[i][j]->Fill(MR, Weight);
            if(R * R > 0.20)    HMR_R2020[i][j]->Fill(MR, Weight);
            if(R * R > 0.25)    HMR_R2025[i][j]->Fill(MR, Weight);
            if(R * R > 0.30)    HMR_R2030[i][j]->Fill(MR, Weight);
            if(R * R > 0.35)    HMR_R2035[i][j]->Fill(MR, Weight);
            if(R * R > 0.40)    HMR_R2040[i][j]->Fill(MR, Weight);
            if(R * R > 0.45)    HMR_R2045[i][j]->Fill(MR, Weight);
            if(R * R > 0.50)    HMR_R2050[i][j]->Fill(MR, Weight);

            if(MR > 0)     HR2_MR000[i][j]->Fill(R * R, Weight);
            if(MR > 100)   HR2_MR100[i][j]->Fill(R * R, Weight);
            if(MR > 200)   HR2_MR200[i][j]->Fill(R * R, Weight);
            if(MR > 300)   HR2_MR300[i][j]->Fill(R * R, Weight);
            if(MR > 400)   HR2_MR400[i][j]->Fill(R * R, Weight);
            if(MR > 500)   HR2_MR500[i][j]->Fill(R * R, Weight);
            
            if(R11 * R11 > 0.00)    HMR11_R112000[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.20)    HMR11_R112020[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.40)    HMR11_R112040[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.50)    HMR11_R112050[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.60)    HMR11_R112060[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.70)    HMR11_R112070[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.80)    HMR11_R112080[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.90)    HMR11_R112090[i][j]->Fill(MR11, Weight);

            if(MR11 > 0)     HR112_MR11000[i][j]->Fill(R11 * R11, Weight);
            if(MR11 > 100)   HR112_MR11100[i][j]->Fill(R11 * R11, Weight);
            if(MR11 > 200)   HR112_MR11200[i][j]->Fill(R11 * R11, Weight);
            if(MR11 > 300)   HR112_MR11300[i][j]->Fill(R11 * R11, Weight);
            if(MR11 > 400)   HR112_MR11400[i][j]->Fill(R11 * R11, Weight);
            if(MR11 > 500)   HR112_MR11500[i][j]->Fill(R11 * R11, Weight);

            HJetPT[i][j]->Fill(JetPT, Weight);
            if(i == 1 || i == 2 || i == 5 || i == 6)
               HMuonPT[i][j]->Fill(MuonPT, Weight);
            if(i == 3 || i == 4 || i == 5 || i == 6)
               HElectronPT[i][j]->Fill(ElectronPT, Weight);
            
            if(MR > 400 && R * R > 0.25)
            {
               HJetPT_MR400R2025[i][j]->Fill(JetPT, Weight);
               if(i == 1 || i == 2 || i == 5 || i == 6)
                  HMuonPT_MR400R2025[i][j]->Fill(MuonPT, Weight);
               if(i == 3 || i == 4 || i == 5 || i == 6)
                  HElectronPT_MR400R2025[i][j]->Fill(ElectronPT, Weight);
            }

            if(FirstPhotonIndex >= 0)
            {
               HPhotonPT[i][j]->Fill(PhotonPT[FirstPhotonIndex], Weight);
               HPhotonHOverE[i][j]->Fill(PhotonHOverE[FirstPhotonIndex], Weight);
               HPhotonSigmaIEtaIEta[i][j]->Fill(PhotonSigmaIEtaIEta[FirstPhotonIndex], Weight);
               HPhotonIsolation[i][j]->Fill(PhotonIsolation[FirstPhotonIndex] - Rho * 0.4 * 0.4 * PI, Weight);
               HPhotonR9[i][j]->Fill(PhotonR9[FirstPhotonIndex], Weight);
            }

            for(int k = 0; k < PhotonCount; k++)
            {
               if(PhotonSeed[k] == true)                           continue;
               if(PhotonPT[k] < 30)                                continue;
               if(fabs(PhotonEta[k]) > 1.569)                      continue;

               if(PhotonSigmaIEtaIEta[k] < 0.011 && PhotonR9[k] < 1 && PhotonR9[k] > 0.8 && PhotonHOverE[k] < 0.05)
                  HAllPhotonIsolation[i][j]->Fill(PhotonIsolation[k] - Rho * PI * 0.4 * 0.4, Weight);
               if(PhotonSigmaIEtaIEta[k] < 0.011 && PhotonR9[k] < 1 && PhotonR9[k] > 0.8 && PhotonIsolation[k] - Rho * PI * 0.4 * 0.4 < 6)
                  HAllPhotonHOverE[i][j]->Fill(PhotonHOverE[k], Weight);
               if(PhotonSigmaIEtaIEta[k] < 0.011 && PhotonHOverE[k] < 0.05 && PhotonIsolation[k] - Rho * PI * 0.4 * 0.4 < 6)
                  HAllPhotonR9[i][j]->Fill(PhotonR9[k], Weight);
               if(PhotonR9[k] < 1 && PhotonR9[k] > 0.8 && PhotonIsolation[k] - Rho * PI * 0.4 * 0.4 < 6 && PhotonHOverE[k] <0.05)
                  HAllPhotonSigmaIEtaIEta[i][j]->Fill(PhotonSigmaIEtaIEta[k], Weight);
               if(PhotonSigmaIEtaIEta[k] < 0.011 && PhotonR9[k] < 1 && PhotonR9[k] > 0.8 && PhotonIsolation[k] - Rho * PI * 0.4 * 0.4 < 6 && PhotonHOverE[k] <0.05)
                  HAllPhotonPT[i][j]->Fill(PhotonPT[k], Weight);
            }

            HMRRMap[i][j]->Fill(MR, R * R, Weight);
         }
      }
   }

   for(int i = 0; i < 8; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         if(CrossSection > 0)
         {
            HMR_R2000[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2020[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2030[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2035[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2040[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2045[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR_R2050[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HR2_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR2_MR100[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR2_MR200[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR2_MR300[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR2_MR400[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR2_MR500[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HMR11_R112000[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112020[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112040[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112050[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112060[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112070[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112080[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMR11_R112090[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HR112_MR11000[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR112_MR11100[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR112_MR11200[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR112_MR11300[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR112_MR11400[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HR112_MR11500[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HJetPT[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMuonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HElectronPT[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            
            HJetPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HMuonPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HElectronPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HPhotonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HPhotonIsolation[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HPhotonHOverE[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HPhotonR9[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HPhotonSigmaIEtaIEta[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HAllPhotonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HAllPhotonIsolation[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HAllPhotonHOverE[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HAllPhotonR9[i][j]->Scale(CrossSection * 1000 / TotalWeight);
            HAllPhotonSigmaIEtaIEta[i][j]->Scale(CrossSection * 1000 / TotalWeight);

            HMRRMap[i][j]->Scale(CrossSection * 1000 / TotalWeight);
         }

         HMR_R2000[i][j]->Write();
         HMR_R2020[i][j]->Write();
         HMR_R2025[i][j]->Write();
         HMR_R2030[i][j]->Write();
         HMR_R2035[i][j]->Write();
         HMR_R2040[i][j]->Write();
         HMR_R2045[i][j]->Write();
         HMR_R2050[i][j]->Write();

         HR2_MR000[i][j]->Write();
         HR2_MR100[i][j]->Write();
         HR2_MR200[i][j]->Write();
         HR2_MR300[i][j]->Write();
         HR2_MR400[i][j]->Write();
         HR2_MR500[i][j]->Write();

         HMR11_R112000[i][j]->Write();
         HMR11_R112020[i][j]->Write();
         HMR11_R112040[i][j]->Write();
         HMR11_R112050[i][j]->Write();
         HMR11_R112060[i][j]->Write();
         HMR11_R112070[i][j]->Write();
         HMR11_R112080[i][j]->Write();
         HMR11_R112090[i][j]->Write();

         HR112_MR11000[i][j]->Write();
         HR112_MR11100[i][j]->Write();
         HR112_MR11200[i][j]->Write();
         HR112_MR11300[i][j]->Write();
         HR112_MR11400[i][j]->Write();
         HR112_MR11500[i][j]->Write();

         HJetPT[i][j]->Write();
         HMuonPT[i][j]->Write();
         HElectronPT[i][j]->Write();
         
         HJetPT_MR400R2025[i][j]->Write();
         HMuonPT_MR400R2025[i][j]->Write();
         HElectronPT_MR400R2025[i][j]->Write();

         HPhotonPT[i][j]->Write();
         HPhotonIsolation[i][j]->Write();
         HPhotonHOverE[i][j]->Write();
         HPhotonSigmaIEtaIEta[i][j]->Write();
         HPhotonR9[i][j]->Write();

         HAllPhotonPT[i][j]->Write();
         HAllPhotonIsolation[i][j]->Write();
         HAllPhotonHOverE[i][j]->Write();
         HAllPhotonSigmaIEtaIEta[i][j]->Write();
         HAllPhotonR9[i][j]->Write();

         HMRRMap[i][j]->Write();
         
         delete HMR_R2000[i][j];
         delete HMR_R2020[i][j];
         delete HMR_R2025[i][j];
         delete HMR_R2030[i][j];
         delete HMR_R2035[i][j];
         delete HMR_R2040[i][j];
         delete HMR_R2045[i][j];
         delete HMR_R2050[i][j];

         delete HR2_MR000[i][j];
         delete HR2_MR100[i][j];
         delete HR2_MR200[i][j];
         delete HR2_MR300[i][j];
         delete HR2_MR400[i][j];
         delete HR2_MR500[i][j];

         delete HMR11_R112000[i][j];
         delete HMR11_R112020[i][j];
         delete HMR11_R112040[i][j];
         delete HMR11_R112050[i][j];
         delete HMR11_R112060[i][j];
         delete HMR11_R112070[i][j];
         delete HMR11_R112080[i][j];
         delete HMR11_R112090[i][j];

         delete HR112_MR11000[i][j];
         delete HR112_MR11100[i][j];
         delete HR112_MR11200[i][j];
         delete HR112_MR11300[i][j];
         delete HR112_MR11400[i][j];
         delete HR112_MR11500[i][j];

         delete HJetPT[i][j];
         delete HMuonPT[i][j];
         delete HElectronPT[i][j];

         delete HJetPT_MR400R2025[i][j];
         delete HMuonPT_MR400R2025[i][j];
         delete HElectronPT_MR400R2025[i][j];

         delete HPhotonPT[i][j];
         delete HPhotonIsolation[i][j];
         delete HPhotonHOverE[i][j];
         delete HPhotonSigmaIEtaIEta[i][j];
         delete HPhotonR9[i][j];

         delete HAllPhotonPT[i][j];
         delete HAllPhotonIsolation[i][j];
         delete HAllPhotonHOverE[i][j];
         delete HAllPhotonSigmaIEtaIEta[i][j];
         delete HAllPhotonR9[i][j];

         delete HMRRMap[i][j];
      }
   }

   OutputFile.Close();

   return 0;
}



