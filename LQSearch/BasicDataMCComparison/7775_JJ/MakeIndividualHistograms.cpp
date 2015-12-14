#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

#include "TauHelperFunctions2.h"

class ReweightHelper;
int main(int argc, char *argv[]);

class ReweightHelper
{
public:
   vector<double> PUWeight;
public:
   void InitializeWeight(string RootFile);
   double GetWeight(int NPU);
};

void ReweightHelper::InitializeWeight(string RootFile)
{
   double Flat10[25] = {0.0698146584, 0.0698146584, 0.0698146584,
      0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584,
      0.0698146584, 0.0698146584, 0.0698146584, 0.0630151648, 0.0526654164,
      0.0402754482, 0.0292988928, 0.0194384503, 0.0122016783, 0.007207042,
      0.004003637, 0.0020278322, 0.0010739954, 0.0004595759, 0.0002229748,
      0.0001028162, 4.58337152809607E-05};

   double DataAverage[25] = {0};
   TFile F(RootFile.c_str());
   TH1D *H = (TH1D *)F.Get("pileup");
   for(int i = 1; i <= 25; i++)
      DataAverage[i-1] = H->GetBinContent(i);
   F.Close();

   PUWeight.resize(25);
   for(int i = 0; i < 25; i++)
      PUWeight[i] = DataAverage[i] / Flat10[i];

   double Total = 0;
   for(int i = 0; i < 25; i++)
      Total = Total + PUWeight[i];
   for(int i = 0; i < 25; i++)
      PUWeight[i] = PUWeight[i] / Total;
}

double ReweightHelper::GetWeight(int NPU)
{
   if(NPU < PUWeight.size())
      return PUWeight[NPU];
   return 0;
}

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
   double MRL = 0;
   double RL = 0;
   double MR11 = 0;
   double R11 = 0;
   double MRJJ = 0;
   double RJJ = 0;
   double MRPhoton = 0;
   double RPhoton = 0;
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
   double Muon2PT = 0;
   double MuonEta = 0;
   double Muon2Eta = 0;
   double MuonPhi = 0;
   double Muon2Phi = 0;
   double ElectronPT = 0;
   double PhotonPT = 0;

   Tree.SetBranchAddress("MR", &MR);
   Tree.SetBranchAddress("R", &R);
   Tree.SetBranchAddress("MRL", &MRL);
   Tree.SetBranchAddress("RL", &RL);
   Tree.SetBranchAddress("MR11", &MR11);
   Tree.SetBranchAddress("R11", &R11);
   Tree.SetBranchAddress("MRJJ", &MRJJ);
   Tree.SetBranchAddress("RJJ", &RJJ);
   Tree.SetBranchAddress("MRPhoton", &MRPhoton);
   Tree.SetBranchAddress("RPhoton", &RPhoton);
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
   Tree.SetBranchAddress("Muon2PT", &Muon2PT);
   Tree.SetBranchAddress("MuonEta", &MuonEta);
   Tree.SetBranchAddress("Muon2Eta", &Muon2Eta);
   Tree.SetBranchAddress("MuonPhi", &MuonPhi);
   Tree.SetBranchAddress("Muon2Phi", &Muon2Phi);
   Tree.SetBranchAddress("ElectronPT", &ElectronPT);
   Tree.SetBranchAddress("PhotonPT", &PhotonPT);

   ReweightHelper Helper;
   Helper.InitializeWeight("PU.root");

   TFile InputFile(Input.c_str());
   TH1D *HPileUpCount = (TH1D *)InputFile.Get("HPileUpCount");
   double TotalWeight = 0;
   for(int i = 0; i < HPileUpCount->GetNbinsX(); i++)
      TotalWeight = TotalWeight + HPileUpCount->GetBinContent(i + 2) * Helper.GetWeight(i);
   InputFile.Close();

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("MRTree", "Similar to input reduced tree but with weight");
   
   double EventWeight = 0;
   OutputTree.Branch("MR", &MR);
   OutputTree.Branch("R", &R);
   OutputTree.Branch("MRL", &MRL);
   OutputTree.Branch("RL", &RL);
   OutputTree.Branch("MRPhoton", &MRPhoton);
   OutputTree.Branch("RPhoton", &RPhoton);
   OutputTree.Branch("LooseBTagCount", &LooseBTagCount);
   OutputTree.Branch("MediumBTagCount", &MediumBTagCount);
   OutputTree.Branch("TightBTagCount", &TightBTagCount);
   OutputTree.Branch("PileupCount", &PileUpCount);
   OutputTree.Branch("GoodMuonCountTight", &GoodMuonTight);
   OutputTree.Branch("GoodMuonCountLoose", &GoodMuonLoose);
   OutputTree.Branch("GoodElectronCountTight", &GoodElectronTight);
   OutputTree.Branch("GoodElectronCountLoose", &GoodElectronLoose);
   OutputTree.Branch("EventWeight", &EventWeight);

   string Selection[9] = {"Had", "TightMuon", "LooseMuon", "TightElectron", "LooseElectron",
      "LooseMuEle", "TightMuEle", "Photon", "DoubleMuon"};
   string BTagger[8] = {"All", "NoTag", "OneLoose", "TwoLoose", "OneMedium", "TwoMedium", "OneTight", "TwoTight"};

   TH1D *HMR_R2000[9][8] = {NULL};
   TH1D *HMR_R2014[9][8] = {NULL};
   TH1D *HMR_R2014Restricted[9][8] = {NULL};
   TH1D *HMR_R2020[9][8] = {NULL};
   TH1D *HMR_R2020Restricted[9][8] = {NULL};
   TH1D *HMR_R2025[9][8] = {NULL};
   TH1D *HMR_R2025Restricted[9][8] = {NULL};
   TH1D *HMR_R2030[9][8] = {NULL};
   TH1D *HMR_R2035[9][8] = {NULL};
   TH1D *HMR_R2040[9][8] = {NULL};
   TH1D *HMR_R2045[9][8] = {NULL};
   TH1D *HMR_R2050[9][8] = {NULL};
   TH1D *HR_MR000[9][8] = {NULL};
   TH1D *HR2_MR000[9][8] = {NULL};
   TH1D *HR2_MR100[9][8] = {NULL};
   TH1D *HR2_MR200[9][8] = {NULL};
   TH1D *HR2_MR300[9][8] = {NULL};
   TH1D *HR2_MR400[9][8] = {NULL};
   TH1D *HR2_MR400Restricted[9][8] = {NULL};
   TH1D *HR2_MR400Restricted2[9][8] = {NULL};
   TH1D *HR2_MR500[9][8] = {NULL};
   TH1D *HMRL_R2000[9][8] = {NULL};
   TH1D *HMRL_R2014[9][8] = {NULL};
   TH1D *HMRL_R2014Restricted[9][8] = {NULL};
   TH1D *HMRL_R2020[9][8] = {NULL};
   TH1D *HMRL_R2020Restricted[9][8] = {NULL};
   TH1D *HMRL_R2025[9][8] = {NULL};
   TH1D *HMRL_R2025Restricted[9][8] = {NULL};
   TH1D *HMRL_R2030[9][8] = {NULL};
   TH1D *HMRL_R2035[9][8] = {NULL};
   TH1D *HMRL_R2040[9][8] = {NULL};
   TH1D *HMRL_R2045[9][8] = {NULL};
   TH1D *HMRL_R2050[9][8] = {NULL};
   TH1D *HR2L_MR000[9][8] = {NULL};
   TH1D *HR2L_MR100[9][8] = {NULL};
   TH1D *HR2L_MR200[9][8] = {NULL};
   TH1D *HR2L_MR300[9][8] = {NULL};
   TH1D *HR2L_MR400[9][8] = {NULL};
   TH1D *HR2L_MR400Restricted[9][8] = {NULL};
   TH1D *HR2L_MR400Restricted2[9][8] = {NULL};
   TH1D *HR2L_MR500[9][8] = {NULL};
   TH1D *HMRJJ_R2000[9][8] = {NULL};
   TH1D *HMRJJ_R2014[9][8] = {NULL};
   TH1D *HMRJJ_R2014Restricted[9][8] = {NULL};
   TH1D *HMRJJ_R2020[9][8] = {NULL};
   TH1D *HMRJJ_R2020Restricted[9][8] = {NULL};
   TH1D *HMRJJ_R2025[9][8] = {NULL};
   TH1D *HMRJJ_R2025Restricted[9][8] = {NULL};
   TH1D *HMRJJ_R2030[9][8] = {NULL};
   TH1D *HMRJJ_R2035[9][8] = {NULL};
   TH1D *HMRJJ_R2040[9][8] = {NULL};
   TH1D *HMRJJ_R2045[9][8] = {NULL};
   TH1D *HMRJJ_R2050[9][8] = {NULL};
   TH1D *HR2JJ_MR000[9][8] = {NULL};
   TH1D *HR2JJ_MR100[9][8] = {NULL};
   TH1D *HR2JJ_MR200[9][8] = {NULL};
   TH1D *HR2JJ_MR300[9][8] = {NULL};
   TH1D *HR2JJ_MR400[9][8] = {NULL};
   TH1D *HR2JJ_MR400Restricted[9][8] = {NULL};
   TH1D *HR2JJ_MR400Restricted2[9][8] = {NULL};
   TH1D *HR2JJ_MR500[9][8] = {NULL};
   TH1D *HPhotonMR_R2000[9][8] = {NULL};
   TH1D *HPhotonMR_R2014[9][8] = {NULL};
   TH1D *HPhotonMR_R2020[9][8] = {NULL};
   TH1D *HPhotonMR_R2025[9][8] = {NULL};
   TH1D *HPhotonMR_R2030[9][8] = {NULL};
   TH1D *HPhotonMR_R2035[9][8] = {NULL};
   TH1D *HPhotonMR_R2040[9][8] = {NULL};
   TH1D *HPhotonMR_R2045[9][8] = {NULL};
   TH1D *HPhotonMR_R2050[9][8] = {NULL};
   TH1D *HPhotonR2_MR000[9][8] = {NULL};
   TH1D *HPhotonR2_MR100[9][8] = {NULL};
   TH1D *HPhotonR2_MR200[9][8] = {NULL};
   TH1D *HPhotonR2_MR300[9][8] = {NULL};
   TH1D *HPhotonR2_MR400[9][8] = {NULL};
   TH1D *HPhotonR2_MR500[9][8] = {NULL};
   TH1D *HMR11_R112000[9][8] = {NULL};
   TH1D *HMR11_R112014[9][8] = {NULL};
   TH1D *HMR11_R112020[9][8] = {NULL};
   TH1D *HMR11_R112040[9][8] = {NULL};
   TH1D *HMR11_R112050[9][8] = {NULL};
   TH1D *HMR11_R112060[9][8] = {NULL};
   TH1D *HMR11_R112070[9][8] = {NULL};
   TH1D *HMR11_R112080[9][8] = {NULL};
   TH1D *HMR11_R112090[9][8] = {NULL};
   TH1D *HR112_MR11000[9][8] = {NULL};
   TH1D *HR112_MR11100[9][8] = {NULL};
   TH1D *HR112_MR11200[9][8] = {NULL};
   TH1D *HR112_MR11300[9][8] = {NULL};
   TH1D *HR112_MR11400[9][8] = {NULL};
   TH1D *HR112_MR11500[9][8] = {NULL};
   TH1D *HJetPT[9][8] = {NULL};
   TH1D *HElectronPT[9][8] = {NULL};
   TH1D *HMuonPT[9][8] = {NULL};
   TH1D *HMuon2PT[9][8] = {NULL};
   TH1D *HDiMuonPT[9][8] = {NULL};
   TH1D *HDiMuonMass[9][8] = {NULL};
   TH1D *HDiMuonMass2[9][8] = {NULL};
   TH1D *HDiMuonPT_ZPole[9][8] = {NULL};
   TH1D *HDiMuonRapidity[9][8] = {NULL};
   TH1D *HPhotonPT[9][8] = {NULL};
   TH1D *HMET[9][8] = {NULL};
   TH1D *HJetPT_MR400R2025[9][8] = {NULL};
   TH1D *HElectronPT_MR400R2025[9][8] = {NULL};
   TH1D *HMuonPT_MR400R2025[9][8] = {NULL};
   TH1D *HMuon2PT_MR400R2025[9][8] = {NULL};
   TH1D *HDiMuonPT_MR400R2025[9][8] = {NULL};
   TH1D *HDiMuonMass_MR400R2025[9][8] = {NULL};
   TH1D *HDiMuonRapidity_MR400R2025[9][8] = {NULL};
   TH1D *HPhotonPT_MR400R2025[9][8] = {NULL};
   TH1D *HMET_MR400R2025[9][8] = {NULL};
   TH1D *HJetPT_MR400R2014[9][8] = {NULL};
   TH1D *HElectronPT_MR400R2014[9][8] = {NULL};
   TH1D *HMuonPT_MR400R2014[9][8] = {NULL};
   TH1D *HMuon2PT_MR400R2014[9][8] = {NULL};
   TH1D *HDiMuonPT_MR400R2014[9][8] = {NULL};
   TH1D *HDiMuonMass_MR400R2014[9][8] = {NULL};
   TH1D *HDiMuonRapidity_MR400R2014[9][8] = {NULL};
   TH1D *HPhotonPT_MR400R2014[9][8] = {NULL};
   TH1D *HMET_MR400R2014[9][8] = {NULL};

   TH2D *HMRRMap[9][8] = {NULL};

   for(int i = 0; i < 9; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         HMR_R2000[i][j] = new TH1D(Form("HMR_R2000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.00, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2014[i][j] = new TH1D(Form("HMR_R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2014Restricted[i][j] = new TH1D(Form("HMR_R2014Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMR_R2020[i][j] = new TH1D(Form("HMR_R2020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2020Restricted[i][j] = new TH1D(Form("HMR_R2020Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMR_R2025[i][j] = new TH1D(Form("HMR_R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR_R2025Restricted[i][j] = new TH1D(Form("HMR_R2025Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
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
         
         HR_MR000[i][j] = new TH1D(Form("HR_MR000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R, MR > 0, (%s), (%s);R", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
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
         HR2_MR400Restricted[i][j] = new TH1D(Form("HR2_MR400Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.14, 1.5);
         HR2_MR400Restricted2[i][j] = new TH1D(Form("HR2_MR400Restricted2_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.20, 1.5);
         HR2_MR500[i][j] = new TH1D(Form("HR2_MR500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("R^{2}, MR > 500, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HMRL_R2000[i][j] = new TH1D(Form("HMRL_R2000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.00, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2014[i][j] = new TH1D(Form("HMRL_R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2014Restricted[i][j] = new TH1D(Form("HMRL_R2014Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRL_R2020[i][j] = new TH1D(Form("HMRL_R2020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2020Restricted[i][j] = new TH1D(Form("HMRL_R2020Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRL_R2025[i][j] = new TH1D(Form("HMRL_R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2025Restricted[i][j] = new TH1D(Form("HMRL_R2025Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRL_R2030[i][j] = new TH1D(Form("HMRL_R2030_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.30, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2035[i][j] = new TH1D(Form("HMRL_R2035_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.35, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2040[i][j] = new TH1D(Form("HMRL_R2040_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.40, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2045[i][j] = new TH1D(Form("HMRL_R2045_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.45, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRL_R2050[i][j] = new TH1D(Form("HMRL_R2050_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) M_{R}, R^{2} > 0.50, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         
         HR2L_MR000[i][j] = new TH1D(Form("HR2L_MR000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 0, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2L_MR100[i][j] = new TH1D(Form("HR2L_MR100_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 100, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2L_MR200[i][j] = new TH1D(Form("HR2L_MR200_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 200, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2L_MR300[i][j] = new TH1D(Form("HR2L_MR300_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 300, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2L_MR400[i][j] = new TH1D(Form("HR2L_MR400_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2L_MR400Restricted[i][j] = new TH1D(Form("HR2L_MR400Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.14, 1.5);
         HR2L_MR400Restricted2[i][j] = new TH1D(Form("HR2L_MR400Restricted2_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.20, 1.5);
         HR2L_MR500[i][j] = new TH1D(Form("HR2L_MR500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(Lepton) R^{2}, MR > 500, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HMRJJ_R2000[i][j] = new TH1D(Form("HMRJJ_R2000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.00, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2014[i][j] = new TH1D(Form("HMRJJ_R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2014Restricted[i][j] = new TH1D(Form("HMRJJ_R2014Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRJJ_R2020[i][j] = new TH1D(Form("HMRJJ_R2020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2020Restricted[i][j] = new TH1D(Form("HMRJJ_R2020Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRJJ_R2025[i][j] = new TH1D(Form("HMRJJ_R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2025Restricted[i][j] = new TH1D(Form("HMRJJ_R2025Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 400, 1400);
         HMRJJ_R2030[i][j] = new TH1D(Form("HMRJJ_R2030_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.30, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2035[i][j] = new TH1D(Form("HMRJJ_R2035_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.35, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2040[i][j] = new TH1D(Form("HMRJJ_R2040_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.40, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2045[i][j] = new TH1D(Form("HMRJJ_R2045_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.45, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMRJJ_R2050[i][j] = new TH1D(Form("HMRJJ_R2050_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) M_{R}, R^{2} > 0.50, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         
         HR2JJ_MR000[i][j] = new TH1D(Form("HR2JJ_MR000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 0, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2JJ_MR100[i][j] = new TH1D(Form("HR2JJ_MR100_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 100, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2JJ_MR200[i][j] = new TH1D(Form("HR2JJ_MR200_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 200, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2JJ_MR300[i][j] = new TH1D(Form("HR2JJ_MR300_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 300, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2JJ_MR400[i][j] = new TH1D(Form("HR2JJ_MR400_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HR2JJ_MR400Restricted[i][j] = new TH1D(Form("HR2JJ_MR400Restricted_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.14, 1.5);
         HR2JJ_MR400Restricted2[i][j] = new TH1D(Form("HR2JJ_MR400Restricted2_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0.20, 1.5);
         HR2JJ_MR500[i][j] = new TH1D(Form("HR2JJ_MR500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("(JJ) R^{2}, MR > 500, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HPhotonMR_R2000[i][j] = new TH1D(Form("HPhotonMR_R2000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.00, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2014[i][j] = new TH1D(Form("HPhotonMR_R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.14, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2020[i][j] = new TH1D(Form("HPhotonMR_R2020_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.20, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2025[i][j] = new TH1D(Form("HPhotonMR_R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.25, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2030[i][j] = new TH1D(Form("HPhotonMR_R2030_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.30, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2035[i][j] = new TH1D(Form("HPhotonMR_R2035_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.35, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2040[i][j] = new TH1D(Form("HPhotonMR_R2040_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.40, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2045[i][j] = new TH1D(Form("HPhotonMR_R2045_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.45, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HPhotonMR_R2050[i][j] = new TH1D(Form("HPhotonMR_R2050_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon M_{R}, R^{2} > 0.50, (%s), (%s);M_{R}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         
         HPhotonR2_MR000[i][j] = new TH1D(Form("HPhotonR2_MR000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 0, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HPhotonR2_MR100[i][j] = new TH1D(Form("HPhotonR2_MR100_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 100, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HPhotonR2_MR200[i][j] = new TH1D(Form("HPhotonR2_MR200_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 200, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HPhotonR2_MR300[i][j] = new TH1D(Form("HPhotonR2_MR300_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 300, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HPhotonR2_MR400[i][j] = new TH1D(Form("HPhotonR2_MR400_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 400, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         HPhotonR2_MR500[i][j] = new TH1D(Form("HPhotonR2_MR500_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Photon R^{2}, MR > 500, (%s), (%s);R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1.5);
         
         HMR11_R112000[i][j] = new TH1D(Form("HMR11_R112000_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.00, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMR11_R112014[i][j] = new TH1D(Form("HMR11_R112014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("M_{R}^{(11)}, R^{2 (11)} > 0.14, (%s), (%s);M_{R}^{(11)}", Selection[i].c_str(), BTagger[j].c_str()),
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
         HMuon2PT[i][j] = new TH1D(Form("HMuon2PT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Subleading muon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonPT[i][j] = new TH1D(Form("HDiMuonPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonMass[i][j] = new TH1D(Form("HDiMuonMass_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Mass, (%s), (%s);Mass", Selection[i].c_str(), BTagger[j].c_str()),
            25, 50, 150);
         HDiMuonMass2[i][j] = new TH1D(Form("HDiMuonMass2_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Mass, (%s), (%s);Mass", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonPT_ZPole[i][j] = new TH1D(Form("HDiMuonPT_ZPole_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon PT (around Z pole), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonRapidity[i][j] = new TH1D(Form("HDiMuonRapidity_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Rapidity, (%s), (%s);Rapidity", Selection[i].c_str(), BTagger[j].c_str()),
            25, -4, 4);
         HElectronPT[i][j] = new TH1D(Form("HElectronPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading electron PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HPhotonPT[i][j] = new TH1D(Form("HPhotonPT_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon PT, (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);
         HMET[i][j] = new TH1D(Form("HMET_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("MET, (%s), (%s);MET", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);
         
         HJetPT_MR400R2025[i][j] = new TH1D(Form("HJetPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading jet PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMuonPT_MR400R2025[i][j] = new TH1D(Form("HMuonPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading muon PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HMuon2PT_MR400R2025[i][j] = new TH1D(Form("HMuon2PT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Subleading muon PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonPT_MR400R2025[i][j] = new TH1D(Form("HDiMuonPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonMass_MR400R2025[i][j] = new TH1D(Form("HDiMuonMass_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Mass (MR > 400, R^{2} > 0.25), (%s), (%s);Mass", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 150);
         HDiMuonRapidity_MR400R2025[i][j] = new TH1D(Form("HDiMuonRapidity_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Rapidity (MR > 400, R^{2} > 0.25), (%s), (%s);Rapidity", Selection[i].c_str(), BTagger[j].c_str()),
            25, -4, 4);
         HElectronPT_MR400R2025[i][j] = new TH1D(Form("HElectronPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading electron PT (MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HPhotonPT_MR400R2025[i][j] = new TH1D(Form("HPhotonPT_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon PT ((Photon) MR > 400, R^{2} > 0.25), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);
         HMET_MR400R2025[i][j] = new TH1D(Form("HMET_MR400R2025_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("MET, MR > 400, R^{2} > 0.25), (%s), (%s);MET", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);

         HJetPT_MR400R2014[i][j] = new TH1D(Form("HJetPT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading jet PT (MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1500);
         HMuonPT_MR400R2014[i][j] = new TH1D(Form("HMuonPT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading muon PT (MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HMuon2PT_MR400R2014[i][j] = new TH1D(Form("HMuon2PT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Subleading muon PT (MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonPT_MR400R2014[i][j] = new TH1D(Form("HDiMuonPT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon PT (MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HDiMuonMass_MR400R2014[i][j] = new TH1D(Form("HDiMuonMass_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Mass (MR > 400, R^{2} > 0.14), (%s), (%s);Mass", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 150);
         HDiMuonRapidity_MR400R2014[i][j] = new TH1D(Form("HDiMuonRapidity_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Di-muon Rapidity (MR > 400, R^{2} > 0.14), (%s), (%s);Rapidity", Selection[i].c_str(), BTagger[j].c_str()),
            25, -4, 4);
         HElectronPT_MR400R2014[i][j] = new TH1D(Form("HElectronPT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading electron PT (MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 500);
         HPhotonPT_MR400R2014[i][j] = new TH1D(Form("HPhotonPT_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Leading good photon PT ((Photon) MR > 400, R^{2} > 0.14), (%s), (%s);PT", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);
         HMET_MR400R2014[i][j] = new TH1D(Form("HMET_MR400R2014_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("MET, MR > 400, R^{2} > 0.14), (%s), (%s);MET", Selection[i].c_str(), BTagger[j].c_str()),
            25, 0, 1000);

         HMRRMap[i][j] = new TH2D(Form("HMRRMap_%s_%s", Selection[i].c_str(), BTagger[j].c_str()),
            Form("Yield in M_{R}/R^{2} bins;M_{R};R^{2}", Selection[i].c_str(), BTagger[j].c_str()),
            15, 0, 1500, 10, 0, 1);
      }
   }

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      double OriginalWeight = 1;
      if(CrossSection > 0)
         OriginalWeight = Helper.GetWeight(PileUpCount);

      // TotalWeight = TotalWeight + Weight;

      for(int i = 0; i < 9; i++)
      {
         if(i == 0 && (GoodMuonLoose > 0 || GoodElectronLoose > 0))     continue;
         if(i == 1 && GoodMuonTight != 1)                               continue;
         if(i == 2 && GoodMuonLoose != 1)                               continue;
         if(i == 3 && GoodElectronTight != 1)                           continue;
         if(i == 4 && GoodElectronLoose != 1)                           continue;
         if(i == 5 && (GoodElectronLoose == 0 || GoodMuonLoose == 0))   continue;
         if(i == 6 && (GoodElectronTight == 0 || GoodMuonTight == 0))   continue;
         if(i == 7 && PhotonPT < 100)                                   continue;   // oops forgot photon count
         if(i == 8 && GoodMuonTight != 2)                               continue;

         for(int j = 0; j < 8; j++)
         {
            if(j == 1 && LooseBTagCount != 0)    continue;
            if(j == 2 && LooseBTagCount != 1)    continue;
            if(j == 3 && LooseBTagCount < 2)     continue;
            if(j == 4 && MediumBTagCount != 1)   continue;
            if(j == 5 && MediumBTagCount < 2)    continue;
            if(j == 6 && TightBTagCount != 1)    continue;
            if(j == 7 && TightBTagCount < 2)     continue;

            double Weight = OriginalWeight;
            
            if(R * R > 0.00)    HMR_R2000[i][j]->Fill(MR, Weight);
            if(R * R > 0.14)    HMR_R2014[i][j]->Fill(MR, Weight);
            if(R * R > 0.14)    HMR_R2014Restricted[i][j]->Fill(MR, Weight);
            if(R * R > 0.20)    HMR_R2020[i][j]->Fill(MR, Weight);
            if(R * R > 0.20)    HMR_R2020Restricted[i][j]->Fill(MR, Weight);
            if(R * R > 0.25)    HMR_R2025[i][j]->Fill(MR, Weight);
            if(R * R > 0.25)    HMR_R2025Restricted[i][j]->Fill(MR, Weight);
            if(R * R > 0.30)    HMR_R2030[i][j]->Fill(MR, Weight);
            if(R * R > 0.35)    HMR_R2035[i][j]->Fill(MR, Weight);
            if(R * R > 0.40)    HMR_R2040[i][j]->Fill(MR, Weight);
            if(R * R > 0.45)    HMR_R2045[i][j]->Fill(MR, Weight);
            if(R * R > 0.50)    HMR_R2050[i][j]->Fill(MR, Weight);

            if(MR > 0)     HR_MR000[i][j]->Fill(R, Weight);
            if(MR > 0)     HR2_MR000[i][j]->Fill(R * R, Weight);
            if(MR > 100)   HR2_MR100[i][j]->Fill(R * R, Weight);
            if(MR > 200)   HR2_MR200[i][j]->Fill(R * R, Weight);
            if(MR > 300)   HR2_MR300[i][j]->Fill(R * R, Weight);
            if(MR > 400)   HR2_MR400[i][j]->Fill(R * R, Weight);
            if(MR > 400)   HR2_MR400Restricted[i][j]->Fill(R * R, Weight);
            if(MR > 400)   HR2_MR400Restricted2[i][j]->Fill(R * R, Weight);
            if(MR > 500)   HR2_MR500[i][j]->Fill(R * R, Weight);
            
            if(RL * RL > 0.00)    HMRL_R2000[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.14)    HMRL_R2014[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.14)    HMRL_R2014Restricted[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.20)    HMRL_R2020[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.20)    HMRL_R2020Restricted[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.25)    HMRL_R2025[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.25)    HMRL_R2025Restricted[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.30)    HMRL_R2030[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.35)    HMRL_R2035[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.40)    HMRL_R2040[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.45)    HMRL_R2045[i][j]->Fill(MRL, Weight);
            if(RL * RL > 0.50)    HMRL_R2050[i][j]->Fill(MRL, Weight);

            if(MRL > 0)     HR2L_MR000[i][j]->Fill(RL * RL, Weight);
            if(MRL > 100)   HR2L_MR100[i][j]->Fill(RL * RL, Weight);
            if(MRL > 200)   HR2L_MR200[i][j]->Fill(RL * RL, Weight);
            if(MRL > 300)   HR2L_MR300[i][j]->Fill(RL * RL, Weight);
            if(MRL > 400)   HR2L_MR400[i][j]->Fill(RL * RL, Weight);
            if(MRL > 400)   HR2L_MR400Restricted[i][j]->Fill(RL * RL, Weight);
            if(MRL > 400)   HR2L_MR400Restricted2[i][j]->Fill(RL * RL, Weight);
            if(MRL > 500)   HR2L_MR500[i][j]->Fill(RL * RL, Weight);
            
            if(RJJ * RJJ > 0.00)    HMRJJ_R2000[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.14)    HMRJJ_R2014[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.14)    HMRJJ_R2014Restricted[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.20)    HMRJJ_R2020[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.20)    HMRJJ_R2020Restricted[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.25)    HMRJJ_R2025[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.25)    HMRJJ_R2025Restricted[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.30)    HMRJJ_R2030[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.35)    HMRJJ_R2035[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.40)    HMRJJ_R2040[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.45)    HMRJJ_R2045[i][j]->Fill(MRJJ, Weight);
            if(RJJ * RJJ > 0.50)    HMRJJ_R2050[i][j]->Fill(MRJJ, Weight);

            if(MRJJ > 0)     HR2JJ_MR000[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 100)   HR2JJ_MR100[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 200)   HR2JJ_MR200[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 300)   HR2JJ_MR300[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 400)   HR2JJ_MR400[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 400)   HR2JJ_MR400Restricted[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 400)   HR2JJ_MR400Restricted2[i][j]->Fill(RJJ * RJJ, Weight);
            if(MRJJ > 500)   HR2JJ_MR500[i][j]->Fill(RJJ * RJJ, Weight);
            
            if(MRPhoton > 0)     HPhotonR2_MR000[i][j]->Fill(RPhoton * RPhoton, Weight);
            if(MRPhoton > 100)   HPhotonR2_MR100[i][j]->Fill(RPhoton * RPhoton, Weight);
            if(MRPhoton > 200)   HPhotonR2_MR200[i][j]->Fill(RPhoton * RPhoton, Weight);
            if(MRPhoton > 300)   HPhotonR2_MR300[i][j]->Fill(RPhoton * RPhoton, Weight);
            if(MRPhoton > 400)   HPhotonR2_MR400[i][j]->Fill(RPhoton * RPhoton, Weight);
            if(MRPhoton > 500)   HPhotonR2_MR500[i][j]->Fill(RPhoton * RPhoton, Weight);
            
            if(RPhoton * RPhoton > 0.00)    HPhotonMR_R2000[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.14)    HPhotonMR_R2014[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.20)    HPhotonMR_R2020[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.25)    HPhotonMR_R2025[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.30)    HPhotonMR_R2030[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.35)    HPhotonMR_R2035[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.40)    HPhotonMR_R2040[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.45)    HPhotonMR_R2045[i][j]->Fill(MRPhoton, Weight);
            if(RPhoton * RPhoton > 0.50)    HPhotonMR_R2050[i][j]->Fill(MRPhoton, Weight);

            if(R11 * R11 > 0.00)    HMR11_R112000[i][j]->Fill(MR11, Weight);
            if(R11 * R11 > 0.14)    HMR11_R112014[i][j]->Fill(MR11, Weight);
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

            FourVector Muon1P, Muon2P;
            Muon1P.SetPtEtaPhi(MuonPT, MuonEta, MuonPhi);
            Muon2P.SetPtEtaPhi(Muon2PT, Muon2Eta, Muon2Phi);
            FourVector DiMuon = Muon1P + Muon2P;

            HJetPT[i][j]->Fill(JetPT, Weight);
            if(i == 1 || i == 2 || i == 5 || i == 6 || i == 8)
               HMuonPT[i][j]->Fill(MuonPT, Weight);
            if(i == 8)
            {
               HMuon2PT[i][j]->Fill(Muon2PT, Weight);
               HDiMuonPT[i][j]->Fill(DiMuon.GetPT(), Weight);
               HDiMuonMass[i][j]->Fill(DiMuon.GetMass(), Weight);
               HDiMuonMass2[i][j]->Fill(DiMuon.GetMass(), Weight);
               if(DiMuon.GetMass() > 80 && DiMuon.GetMass() < 100)
                  HDiMuonPT_ZPole[i][j]->Fill(DiMuon.GetPT(), Weight);
               HDiMuonRapidity[i][j]->Fill(DiMuon.GetRapidity(), Weight);
            }
            if(i == 3 || i == 4 || i == 5 || i == 6)
               HElectronPT[i][j]->Fill(ElectronPT, Weight);
            if(i == 7)
               HPhotonPT[i][j]->Fill(PhotonPT, Weight);
            // HMET[i][j]->Fill(asdgasdgasgds);
            
            if(MR > 400 && R * R > 0.25)
            {
               HJetPT_MR400R2025[i][j]->Fill(JetPT, Weight);
               if(i == 1 || i == 2 || i == 5 || i == 6)
                  HMuonPT_MR400R2025[i][j]->Fill(MuonPT, Weight);
               if(i == 8)
               {
                  HMuon2PT_MR400R2025[i][j]->Fill(Muon2PT, Weight);
                  HDiMuonPT_MR400R2025[i][j]->Fill(DiMuon.GetPT(), Weight);
                  HDiMuonMass_MR400R2025[i][j]->Fill(DiMuon.GetMass(), Weight);
                  HDiMuonRapidity_MR400R2025[i][j]->Fill(DiMuon.GetRapidity(), Weight);
               }
               if(i == 3 || i == 4 || i == 5 || i == 6)
                  HElectronPT_MR400R2025[i][j]->Fill(ElectronPT, Weight);
               // HMET_MR400R2025[i][j]->Fill(....);
            }
            if(MRPhoton > 400 && RPhoton * RPhoton > 0.25)
               if(i == 7)
                  HPhotonPT_MR400R2025[i][j]->Fill(PhotonPT, Weight);

            if(MR > 400 && R * R > 0.14)
            {
               HJetPT_MR400R2014[i][j]->Fill(JetPT, Weight);
               if(i == 1 || i == 2 || i == 5 || i == 6)
                  HMuonPT_MR400R2014[i][j]->Fill(MuonPT, Weight);
               if(i == 8)
               {
                  HMuon2PT_MR400R2014[i][j]->Fill(Muon2PT, Weight);
                  HDiMuonPT_MR400R2014[i][j]->Fill(DiMuon.GetPT(), Weight);
                  HDiMuonMass_MR400R2014[i][j]->Fill(DiMuon.GetMass(), Weight);
                  HDiMuonRapidity_MR400R2014[i][j]->Fill(DiMuon.GetRapidity(), Weight);
               }
               if(i == 3 || i == 4 || i == 5 || i == 6)
                  HElectronPT_MR400R2014[i][j]->Fill(ElectronPT, Weight);
               // HMET_MR400R2014[i][j]->Fill(....);
            }
            if(MRPhoton > 400 && RPhoton * RPhoton > 0.14)
               if(i == 7)
                  HPhotonPT_MR400R2014[i][j]->Fill(PhotonPT, Weight);

            HMRRMap[i][j]->Fill(MR, R * R, Weight);
         }
      }

      if(CrossSection > 0)
         EventWeight = CrossSection * 1000 * OriginalWeight / TotalWeight;
      else
         EventWeight = 1;
      OutputTree.Fill();
   }

   for(int i = 0; i < 9; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         if(CrossSection > 0)
         {
            double ScaleFactor = 1;
            /*
            if(j == 2)   ScaleFactor = 0.88;
            if(j == 3)   ScaleFactor = 0.88 * 0.88;
            if(j == 4)   ScaleFactor = 0.92;
            if(j == 5)   ScaleFactor = 0.92 * 0.92;
            if(j == 6)   ScaleFactor = 1.01;
            if(j == 7)   ScaleFactor = 1.01 * 1.01;
            */

            HMR_R2000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2014Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2020[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2020Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2025Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2030[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2035[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2040[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2045[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR_R2050[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HR_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR100[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR200[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR300[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR400[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR400Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR400Restricted2[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2_MR500[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HMRL_R2000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2014Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2020[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2020Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2025Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2030[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2035[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2040[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2045[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRL_R2050[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HR2L_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR100[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR200[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR300[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR400[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR400Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR400Restricted2[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2L_MR500[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HMRJJ_R2000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2014Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2020[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2020Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2025Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2030[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2035[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2040[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2045[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMRJJ_R2050[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HR2JJ_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR100[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR200[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR300[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR400[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR400Restricted[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR400Restricted2[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR2JJ_MR500[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HPhotonMR_R2000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2020[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2030[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2035[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2040[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2045[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonMR_R2050[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HPhotonR2_MR000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonR2_MR100[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonR2_MR200[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonR2_MR300[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonR2_MR400[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonR2_MR500[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HMR11_R112000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112020[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112040[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112050[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112060[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112070[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112080[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMR11_R112090[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HR112_MR11000[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR112_MR11100[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR112_MR11200[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR112_MR11300[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR112_MR11400[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HR112_MR11500[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HJetPT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuon2PT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonMass[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonMass2[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonPT_ZPole[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonRapidity[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HElectronPT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonPT[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMET[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            
            HJetPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuonPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuon2PT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonMass_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonRapidity_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HElectronPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonPT_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMET_MR400R2025[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HJetPT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuonPT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMuon2PT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonPT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonMass_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HDiMuonRapidity_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HElectronPT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HPhotonPT_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
            HMET_MR400R2014[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);

            HMRRMap[i][j]->Scale(CrossSection * 1000 / TotalWeight * ScaleFactor);
         }

         HMR_R2000[i][j]->Write();
         HMR_R2014[i][j]->Write();
         HMR_R2014Restricted[i][j]->Write();
         HMR_R2020[i][j]->Write();
         HMR_R2020Restricted[i][j]->Write();
         HMR_R2025[i][j]->Write();
         HMR_R2025Restricted[i][j]->Write();
         HMR_R2030[i][j]->Write();
         HMR_R2035[i][j]->Write();
         HMR_R2040[i][j]->Write();
         HMR_R2045[i][j]->Write();
         HMR_R2050[i][j]->Write();

         HR_MR000[i][j]->Write();
         HR2_MR000[i][j]->Write();
         HR2_MR100[i][j]->Write();
         HR2_MR200[i][j]->Write();
         HR2_MR300[i][j]->Write();
         HR2_MR400[i][j]->Write();
         HR2_MR400Restricted[i][j]->Write();
         HR2_MR400Restricted2[i][j]->Write();
         HR2_MR500[i][j]->Write();

         HMRL_R2000[i][j]->Write();
         HMRL_R2014[i][j]->Write();
         HMRL_R2014Restricted[i][j]->Write();
         HMRL_R2020[i][j]->Write();
         HMRL_R2020Restricted[i][j]->Write();
         HMRL_R2025[i][j]->Write();
         HMRL_R2025Restricted[i][j]->Write();
         HMRL_R2030[i][j]->Write();
         HMRL_R2035[i][j]->Write();
         HMRL_R2040[i][j]->Write();
         HMRL_R2045[i][j]->Write();
         HMRL_R2050[i][j]->Write();

         HR2L_MR000[i][j]->Write();
         HR2L_MR100[i][j]->Write();
         HR2L_MR200[i][j]->Write();
         HR2L_MR300[i][j]->Write();
         HR2L_MR400[i][j]->Write();
         HR2L_MR400Restricted[i][j]->Write();
         HR2L_MR400Restricted2[i][j]->Write();
         HR2L_MR500[i][j]->Write();

         HMRJJ_R2000[i][j]->Write();
         HMRJJ_R2014[i][j]->Write();
         HMRJJ_R2014Restricted[i][j]->Write();
         HMRJJ_R2020[i][j]->Write();
         HMRJJ_R2020Restricted[i][j]->Write();
         HMRJJ_R2025[i][j]->Write();
         HMRJJ_R2025Restricted[i][j]->Write();
         HMRJJ_R2030[i][j]->Write();
         HMRJJ_R2035[i][j]->Write();
         HMRJJ_R2040[i][j]->Write();
         HMRJJ_R2045[i][j]->Write();
         HMRJJ_R2050[i][j]->Write();

         HR2JJ_MR000[i][j]->Write();
         HR2JJ_MR100[i][j]->Write();
         HR2JJ_MR200[i][j]->Write();
         HR2JJ_MR300[i][j]->Write();
         HR2JJ_MR400[i][j]->Write();
         HR2JJ_MR400Restricted[i][j]->Write();
         HR2JJ_MR400Restricted2[i][j]->Write();
         HR2JJ_MR500[i][j]->Write();

         HPhotonMR_R2000[i][j]->Write();
         HPhotonMR_R2014[i][j]->Write();
         HPhotonMR_R2020[i][j]->Write();
         HPhotonMR_R2025[i][j]->Write();
         HPhotonMR_R2030[i][j]->Write();
         HPhotonMR_R2035[i][j]->Write();
         HPhotonMR_R2040[i][j]->Write();
         HPhotonMR_R2045[i][j]->Write();
         HPhotonMR_R2050[i][j]->Write();

         HPhotonR2_MR000[i][j]->Write();
         HPhotonR2_MR100[i][j]->Write();
         HPhotonR2_MR200[i][j]->Write();
         HPhotonR2_MR300[i][j]->Write();
         HPhotonR2_MR400[i][j]->Write();
         HPhotonR2_MR500[i][j]->Write();

         HMR11_R112000[i][j]->Write();
         HMR11_R112014[i][j]->Write();
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
         HMuon2PT[i][j]->Write();
         HDiMuonPT[i][j]->Write();
         HDiMuonMass[i][j]->Write();
         HDiMuonMass2[i][j]->Write();
         HDiMuonPT_ZPole[i][j]->Write();
         HDiMuonRapidity[i][j]->Write();
         HElectronPT[i][j]->Write();
         HPhotonPT[i][j]->Write();
         HMET[i][j]->Write();
         
         HJetPT_MR400R2025[i][j]->Write();
         HMuonPT_MR400R2025[i][j]->Write();
         HMuon2PT_MR400R2025[i][j]->Write();
         HDiMuonPT_MR400R2025[i][j]->Write();
         HDiMuonMass_MR400R2025[i][j]->Write();
         HDiMuonRapidity_MR400R2025[i][j]->Write();
         HElectronPT_MR400R2025[i][j]->Write();
         HPhotonPT_MR400R2025[i][j]->Write();
         HMET_MR400R2025[i][j]->Write();

         HJetPT_MR400R2014[i][j]->Write();
         HMuonPT_MR400R2014[i][j]->Write();
         HMuon2PT_MR400R2014[i][j]->Write();
         HDiMuonPT_MR400R2014[i][j]->Write();
         HDiMuonMass_MR400R2014[i][j]->Write();
         HDiMuonRapidity_MR400R2014[i][j]->Write();
         HElectronPT_MR400R2014[i][j]->Write();
         HPhotonPT_MR400R2014[i][j]->Write();
         HMET_MR400R2014[i][j]->Write();

         HMRRMap[i][j]->Write();
         
         delete HMR_R2000[i][j];
         delete HMR_R2014[i][j];
         delete HMR_R2014Restricted[i][j];
         delete HMR_R2020[i][j];
         delete HMR_R2020Restricted[i][j];
         delete HMR_R2025[i][j];
         delete HMR_R2025Restricted[i][j];
         delete HMR_R2030[i][j];
         delete HMR_R2035[i][j];
         delete HMR_R2040[i][j];
         delete HMR_R2045[i][j];
         delete HMR_R2050[i][j];

         delete HR_MR000[i][j];
         delete HR2_MR000[i][j];
         delete HR2_MR100[i][j];
         delete HR2_MR200[i][j];
         delete HR2_MR300[i][j];
         delete HR2_MR400[i][j];
         delete HR2_MR400Restricted[i][j];
         delete HR2_MR400Restricted2[i][j];
         delete HR2_MR500[i][j];

         delete HMRL_R2000[i][j];
         delete HMRL_R2014[i][j];
         delete HMRL_R2014Restricted[i][j];
         delete HMRL_R2020[i][j];
         delete HMRL_R2020Restricted[i][j];
         delete HMRL_R2025[i][j];
         delete HMRL_R2025Restricted[i][j];
         delete HMRL_R2030[i][j];
         delete HMRL_R2035[i][j];
         delete HMRL_R2040[i][j];
         delete HMRL_R2045[i][j];
         delete HMRL_R2050[i][j];

         delete HR2L_MR000[i][j];
         delete HR2L_MR100[i][j];
         delete HR2L_MR200[i][j];
         delete HR2L_MR300[i][j];
         delete HR2L_MR400[i][j];
         delete HR2L_MR400Restricted[i][j];
         delete HR2L_MR400Restricted2[i][j];
         delete HR2L_MR500[i][j];

         delete HMRJJ_R2000[i][j];
         delete HMRJJ_R2014[i][j];
         delete HMRJJ_R2014Restricted[i][j];
         delete HMRJJ_R2020[i][j];
         delete HMRJJ_R2020Restricted[i][j];
         delete HMRJJ_R2025[i][j];
         delete HMRJJ_R2025Restricted[i][j];
         delete HMRJJ_R2030[i][j];
         delete HMRJJ_R2035[i][j];
         delete HMRJJ_R2040[i][j];
         delete HMRJJ_R2045[i][j];
         delete HMRJJ_R2050[i][j];

         delete HR2JJ_MR000[i][j];
         delete HR2JJ_MR100[i][j];
         delete HR2JJ_MR200[i][j];
         delete HR2JJ_MR300[i][j];
         delete HR2JJ_MR400[i][j];
         delete HR2JJ_MR400Restricted[i][j];
         delete HR2JJ_MR400Restricted2[i][j];
         delete HR2JJ_MR500[i][j];

         delete HPhotonMR_R2000[i][j];
         delete HPhotonMR_R2014[i][j];
         delete HPhotonMR_R2020[i][j];
         delete HPhotonMR_R2025[i][j];
         delete HPhotonMR_R2030[i][j];
         delete HPhotonMR_R2035[i][j];
         delete HPhotonMR_R2040[i][j];
         delete HPhotonMR_R2045[i][j];
         delete HPhotonMR_R2050[i][j];

         delete HPhotonR2_MR000[i][j];
         delete HPhotonR2_MR100[i][j];
         delete HPhotonR2_MR200[i][j];
         delete HPhotonR2_MR300[i][j];
         delete HPhotonR2_MR400[i][j];
         delete HPhotonR2_MR500[i][j];

         delete HMR11_R112000[i][j];
         delete HMR11_R112014[i][j];
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
         delete HMuon2PT[i][j];
         delete HDiMuonPT[i][j];
         delete HDiMuonMass[i][j];
         delete HDiMuonMass2[i][j];
         delete HDiMuonPT_ZPole[i][j];
         delete HDiMuonRapidity[i][j];
         delete HElectronPT[i][j];
         delete HPhotonPT[i][j];
         delete HMET[i][j];

         delete HJetPT_MR400R2025[i][j];
         delete HMuonPT_MR400R2025[i][j];
         delete HMuon2PT_MR400R2025[i][j];
         delete HDiMuonPT_MR400R2025[i][j];
         delete HDiMuonMass_MR400R2025[i][j];
         delete HDiMuonRapidity_MR400R2025[i][j];
         delete HElectronPT_MR400R2025[i][j];
         delete HPhotonPT_MR400R2025[i][j];
         delete HMET_MR400R2025[i][j];
         
         delete HJetPT_MR400R2014[i][j];
         delete HMuonPT_MR400R2014[i][j];
         delete HMuon2PT_MR400R2014[i][j];
         delete HDiMuonPT_MR400R2014[i][j];
         delete HDiMuonMass_MR400R2014[i][j];
         delete HDiMuonRapidity_MR400R2014[i][j];
         delete HElectronPT_MR400R2014[i][j];
         delete HPhotonPT_MR400R2014[i][j];
         delete HMET_MR400R2014[i][j];
         
         delete HMRRMap[i][j];
      }
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}



