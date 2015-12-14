#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

#include "TNtuple.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"

int main();
map<double, vector<double> > ReadIntegral(string FileName);
double GetIntegral(const map<double, vector<double> > &Integrals, double Mass, int Component);

int main()
{
   map<double, vector<double> > Integrals = ReadIntegral("AllIntegrals_Central");
   map<double, vector<double> > IntegralsUp = ReadIntegral("AllIntegrals_Up");
   map<double, vector<double> > IntegralsDown = ReadIntegral("AllIntegrals_Down");
   map<double, vector<double> > IntegralsWide = ReadIntegral("AllIntegrals_Wide");
   map<double, vector<double> > IntegralsNarrow = ReadIntegral("AllIntegrals_Narrow");

   TFile InputFile("HZZ4l_Prophecy4f_125_100K_tree_11521.root");
   TTree *InputTree = (TTree *)InputFile.Get("zz4lTree/probe_tree");

   float l1pt, l1eta, l1phi;
   float l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi;
   float l4pt, l4eta, l4phi;

   InputTree->SetBranchAddress("l1pt", &l1pt);
   InputTree->SetBranchAddress("l1eta", &l1eta);
   InputTree->SetBranchAddress("l1phi", &l1phi);
   InputTree->SetBranchAddress("l2pt", &l2pt);
   InputTree->SetBranchAddress("l2eta", &l2eta);
   InputTree->SetBranchAddress("l2phi", &l2phi);
   InputTree->SetBranchAddress("l3pt", &l3pt);
   InputTree->SetBranchAddress("l3eta", &l3eta);
   InputTree->SetBranchAddress("l3phi", &l3phi);
   InputTree->SetBranchAddress("l4pt", &l4pt);
   InputTree->SetBranchAddress("l4eta", &l4eta);
   InputTree->SetBranchAddress("l4phi", &l4phi);

   double L11, L22, L33, L44, L55, L12, L13, L14, L15, L23, L24, L25, L34, L35, L45, LB;
   double I11, I22, I33, I44, I55, I12, I13, I14, I15, I23, I24, I25, I34, I35, I45, IB;
   double L11Up, L22Up, L33Up, L44Up, L55Up, L12Up, L13Up, L14Up, L15Up, L23Up, L24Up, L25Up, L34Up, L35Up, L45Up, LBUp;
   double I11Up, I22Up, I33Up, I44Up, I55Up, I12Up, I13Up, I14Up, I15Up, I23Up, I24Up, I25Up, I34Up, I35Up, I45Up, IBUp;
   double L11Down, L22Down, L33Down, L44Down, L55Down, L12Down, L13Down, L14Down, L15Down, L23Down, L24Down, L25Down, L34Down, L35Down, L45Down, LBDown;
   double I11Down, I22Down, I33Down, I44Down, I55Down, I12Down, I13Down, I14Down, I15Down, I23Down, I24Down, I25Down, I34Down, I35Down, I45Down, IBDown;
   double L11Wide, L22Wide, L33Wide, L44Wide, L55Wide, L12Wide, L13Wide, L14Wide, L15Wide, L23Wide, L24Wide, L25Wide, L34Wide, L35Wide, L45Wide, LBWide;
   double I11Wide, I22Wide, I33Wide, I44Wide, I55Wide, I12Wide, I13Wide, I14Wide, I15Wide, I23Wide, I24Wide, I25Wide, I34Wide, I35Wide, I45Wide, IBWide;
   double L11Narrow, L22Narrow, L33Narrow, L44Narrow, L55Narrow, L12Narrow, L13Narrow, L14Narrow, L15Narrow, L23Narrow, L24Narrow, L25Narrow, L34Narrow, L35Narrow, L45Narrow, LBNarrow;
   double I11Narrow, I22Narrow, I33Narrow, I44Narrow, I55Narrow, I12Narrow, I13Narrow, I14Narrow, I15Narrow, I23Narrow, I24Narrow, I25Narrow, I34Narrow, I35Narrow, I45Narrow, IBNarrow;
   float Mass = 125;

   InputTree->SetBranchAddress("Hybrid_A1RA1R", &L11);
   InputTree->SetBranchAddress("Hybrid_A2RA2R", &L22);
   InputTree->SetBranchAddress("Hybrid_A3RA3R", &L33);
   InputTree->SetBranchAddress("Hybrid_A3RI3I", &L44);
   InputTree->SetBranchAddress("Hybrid_A2RI2I", &L55);
   InputTree->SetBranchAddress("Hybrid_A1RA2R", &L12);
   InputTree->SetBranchAddress("Hybrid_A1RA3R", &L13);
   InputTree->SetBranchAddress("Hybrid_A1RA3I", &L14);
   InputTree->SetBranchAddress("Hybrid_A1RA2I", &L15);
   InputTree->SetBranchAddress("Hybrid_A2RA3R", &L23);
   InputTree->SetBranchAddress("Hybrid_A2IA3R", &L24);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2RA2I", &L25);
   InputTree->SetBranchAddress("Hybrid_A3RA3I", &L34);
   InputTree->SetBranchAddress("Hybrid_A2RA3I", &L35);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2IA3I", &L45);
   InputTree->SetBranchAddress("Hybrid_Background", &LB);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonUp", &L11Up);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonUp", &L22Up);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonUp", &L33Up);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonUp", &L44Up);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonUp", &L55Up);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonUp", &L12Up);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonUp", &L13Up);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonUp", &L14Up);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonUp", &L15Up);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonUp", &L23Up);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonUp", &L24Up);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonUp", &L25Up);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonUp", &L34Up);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonUp", &L35Up);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonUp", &L45Up);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonUp", &LBUp);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonDown", &L11Down);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonDown", &L22Down);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonDown", &L33Down);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonDown", &L44Down);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonDown", &L55Down);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonDown", &L12Down);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonDown", &L13Down);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonDown", &L14Down);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonDown", &L15Down);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonDown", &L23Down);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonDown", &L24Down);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonDown", &L25Down);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonDown", &L34Down);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonDown", &L35Down);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonDown", &L45Down);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonDown", &LBDown);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonWide", &L11Wide);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonWide", &L22Wide);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonWide", &L33Wide);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonWide", &L44Wide);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonWide", &L55Wide);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonWide", &L12Wide);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonWide", &L13Wide);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonWide", &L14Wide);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonWide", &L15Wide);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonWide", &L23Wide);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonWide", &L24Wide);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonWide", &L25Wide);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonWide", &L34Wide);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonWide", &L35Wide);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonWide", &L45Wide);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonWide", &LBWide);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonNarrow", &L11Narrow);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonNarrow", &L22Narrow);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonNarrow", &L33Narrow);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonNarrow", &L44Narrow);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonNarrow", &L55Narrow);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonNarrow", &L12Narrow);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonNarrow", &L13Narrow);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonNarrow", &L14Narrow);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonNarrow", &L15Narrow);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonNarrow", &L23Narrow);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonNarrow", &L24Narrow);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonNarrow", &L25Narrow);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonNarrow", &L34Narrow);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonNarrow", &L35Narrow);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonNarrow", &L45Narrow);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonNarrow", &LBNarrow);
   // InputTree->SetBranchAddress("mass", &Mass);

   string BranchList = "";
   BranchList = BranchList + "L11C:L22C:L33C:L44C:L55C:L12C:L13C:L14C:L15C:L23C:L24C:L25C:L34C:L35C:L45C:LBC";
   BranchList = BranchList + ":L11U:L22U:L33U:L44U:L55U:L12U:L13U:L14U:L15U:L23U:L24U:L25U:L34U:L35U:L45U:LBU";
   BranchList = BranchList + ":L11D:L22D:L33D:L44D:L55D:L12D:L13D:L14D:L15D:L23D:L24D:L25D:L34D:L35D:L45D:LBD";
   BranchList = BranchList + ":L11W:L22W:L33W:L44W:L55W:L12W:L13W:L14W:L15W:L23W:L24W:L25W:L34W:L35W:L45W:LBW";
   BranchList = BranchList + ":L11N:L22N:L33N:L44N:L55N:L12N:L13N:L14N:L15N:L23N:L24N:L25N:L34N:L35N:L45N:LBN";
   BranchList = BranchList + ":I11C:I22C:I33C:I44C:I55C:I12C:I13C:I14C:I15C:I23C:I24C:I25C:I34C:I35C:I45C:IBC";
   BranchList = BranchList + ":I11U:I22U:I33U:I44U:I55U:I12U:I13U:I14U:I15U:I23U:I24U:I25U:I34U:I35U:I45U:IBU";
   BranchList = BranchList + ":I11D:I22D:I33D:I44D:I55D:I12D:I13D:I14D:I15D:I23D:I24D:I25D:I34D:I35D:I45D:IBD";
   BranchList = BranchList + ":I11W:I22W:I33W:I44W:I55W:I12W:I13W:I14W:I15W:I23W:I24W:I25W:I34W:I35W:I45W:IBW";
   BranchList = BranchList + ":I11N:I22N:I33N:I44N:I55N:I12N:I13N:I14N:I15N:I23N:I24N:I25N:I34N:I35N:I45N:IBN";
   BranchList = BranchList + ":Mass";
   
   double L11C, L22C, L33C, L44C, L55C, L12C, L13C, L14C, L15C, L23C, L24C, L25C, L34C, L35C, L45C, LBC;
   double L11U, L22U, L33U, L44U, L55U, L12U, L13U, L14U, L15U, L23U, L24U, L25U, L34U, L35U, L45U, LBU;
   double L11D, L22D, L33D, L44D, L55D, L12D, L13D, L14D, L15D, L23D, L24D, L25D, L34D, L35D, L45D, LBD;
   double L11W, L22W, L33W, L44W, L55W, L12W, L13W, L14W, L15W, L23W, L24W, L25W, L34W, L35W, L45W, LBW;
   double L11N, L22N, L33N, L44N, L55N, L12N, L13N, L14N, L15N, L23N, L24N, L25N, L34N, L35N, L45N, LBN;
   double I11C, I22C, I33C, I44C, I55C, I12C, I13C, I14C, I15C, I23C, I24C, I25C, I34C, I35C, I45C, IBC;
   double I11U, I22U, I33U, I44U, I55U, I12U, I13U, I14U, I15U, I23U, I24U, I25U, I34U, I35U, I45U, IBU;
   double I11D, I22D, I33D, I44D, I55D, I12D, I13D, I14D, I15D, I23D, I24D, I25D, I34D, I35D, I45D, IBD;
   double I11W, I22W, I33W, I44W, I55W, I12W, I13W, I14W, I15W, I23W, I24W, I25W, I34W, I35W, I45W, IBW;
   double I11N, I22N, I33N, I44N, I55N, I12N, I13N, I14N, I15N, I23N, I24N, I25N, I34N, I35N, I45N, IBN;

   TFile OutputFile("FitTree.root", "RECREATE");
   TNtuple OutputTree("OutputTree", "OutputTree", BranchList.c_str());

   float Branches[200] = {0};

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      FourVector L1, L2, L3, L4;
      L1.SetPtEtaPhi(l1pt, l1eta, l1phi);
      L2.SetPtEtaPhi(l2pt, l2eta, l2phi);
      L3.SetPtEtaPhi(l3pt, l3eta, l3phi);
      L4.SetPtEtaPhi(l4pt, l4eta, l4phi);
      Mass = (L1 + L2 + L3 + L4).GetMass();

      if(Mass >= 160 || Mass <= 100)
         continue;

      I11 = GetIntegral(Integrals, Mass, 1);    L11C = L11 / I11;   I11C = I11;
      I22 = GetIntegral(Integrals, Mass, 2);    L22C = L22 / I22;   I22C = I22;
      I33 = GetIntegral(Integrals, Mass, 4);    L33C = L33 / I33;   I33C = I33;
      I44 = GetIntegral(Integrals, Mass, 5);    L44C = L44 / I44;   I44C = I44;
      I55 = GetIntegral(Integrals, Mass, 3);    L55C = L55 / I55;   I55C = I55;
      I12 = GetIntegral(Integrals, Mass, 6);    L12C = L12 / I12;   I12C = I12;
      I13 = GetIntegral(Integrals, Mass, 8);    L13C = L13 / I13;   I13C = I13;
      I14 = GetIntegral(Integrals, Mass, 9);    L14C = L14 / I14;   I14C = I14;
      I15 = GetIntegral(Integrals, Mass, 7);    L15C = L15 / I15;   I15C = I15;
      I23 = GetIntegral(Integrals, Mass, 11);   L23C = L23 / I23;   I23C = I23;
      I24 = GetIntegral(Integrals, Mass, 13);   L24C = L24 / I24;   I24C = I24;
      I25 = GetIntegral(Integrals, Mass, 10);   L25C = L25 / I25;   I25C = I25;
      I34 = GetIntegral(Integrals, Mass, 15);   L34C = L34 / I34;   I34C = I34;
      I35 = GetIntegral(Integrals, Mass, 12);   L35C = L35 / I35;   I35C = I35;
      I45 = GetIntegral(Integrals, Mass, 14);   L45C = L45 / I45;   I45C = I45;
      IB = GetIntegral(Integrals, Mass, 0);     LBC = LB / IB;      IBC = IB;
      
      I11Up = GetIntegral(IntegralsUp, Mass, 1);    L11U = L11Up / I11Up;   I11U = I11Up;
      I22Up = GetIntegral(IntegralsUp, Mass, 2);    L22U = L22Up / I22Up;   I22U = I22Up;
      I33Up = GetIntegral(IntegralsUp, Mass, 4);    L33U = L33Up / I33Up;   I33U = I33Up;
      I44Up = GetIntegral(IntegralsUp, Mass, 5);    L44U = L44Up / I44Up;   I44U = I44Up;
      I55Up = GetIntegral(IntegralsUp, Mass, 3);    L55U = L55Up / I55Up;   I55U = I55Up;
      I12Up = GetIntegral(IntegralsUp, Mass, 6);    L12U = L12Up / I12Up;   I12U = I12Up;
      I13Up = GetIntegral(IntegralsUp, Mass, 8);    L13U = L13Up / I13Up;   I13U = I13Up;
      I14Up = GetIntegral(IntegralsUp, Mass, 9);    L14U = L14Up / I14Up;   I14U = I14Up;
      I15Up = GetIntegral(IntegralsUp, Mass, 7);    L15U = L15Up / I15Up;   I15U = I15Up;
      I23Up = GetIntegral(IntegralsUp, Mass, 11);   L23U = L23Up / I23Up;   I23U = I23Up;
      I24Up = GetIntegral(IntegralsUp, Mass, 13);   L24U = L24Up / I24Up;   I24U = I24Up;
      I25Up = GetIntegral(IntegralsUp, Mass, 15);   L25U = L25Up / I25Up;   I25U = I25Up;
      I34Up = GetIntegral(IntegralsUp, Mass, 10);   L34U = L34Up / I34Up;   I34U = I34Up;
      I35Up = GetIntegral(IntegralsUp, Mass, 12);   L35U = L35Up / I35Up;   I35U = I35Up;
      I45Up = GetIntegral(IntegralsUp, Mass, 14);   L45U = L45Up / I45Up;   I45U = I45Up;
      IBUp = GetIntegral(IntegralsUp, Mass, 0);     LBU = LBUp / IBUp;      IBU = IBUp;
      
      I11Down = GetIntegral(IntegralsDown, Mass, 1);    L11D = L11Down / I11Down;   I11D = I11Down;
      I22Down = GetIntegral(IntegralsDown, Mass, 2);    L22D = L22Down / I22Down;   I22D = I22Down;
      I33Down = GetIntegral(IntegralsDown, Mass, 4);    L33D = L33Down / I33Down;   I33D = I33Down;
      I44Down = GetIntegral(IntegralsDown, Mass, 5);    L44D = L44Down / I44Down;   I44D = I44Down;
      I55Down = GetIntegral(IntegralsDown, Mass, 3);    L55D = L55Down / I55Down;   I55D = I55Down;
      I12Down = GetIntegral(IntegralsDown, Mass, 6);    L12D = L12Down / I12Down;   I12D = I12Down;
      I13Down = GetIntegral(IntegralsDown, Mass, 8);    L13D = L13Down / I13Down;   I13D = I13Down;
      I14Down = GetIntegral(IntegralsDown, Mass, 9);    L14D = L14Down / I14Down;   I14D = I14Down;
      I15Down = GetIntegral(IntegralsDown, Mass, 7);    L15D = L15Down / I15Down;   I15D = I15Down;
      I23Down = GetIntegral(IntegralsDown, Mass, 11);   L23D = L23Down / I23Down;   I23D = I23Down;
      I24Down = GetIntegral(IntegralsDown, Mass, 13);   L24D = L24Down / I24Down;   I24D = I24Down;
      I25Down = GetIntegral(IntegralsDown, Mass, 15);   L25D = L25Down / I25Down;   I25D = I25Down;
      I34Down = GetIntegral(IntegralsDown, Mass, 10);   L34D = L34Down / I34Down;   I34D = I34Down;
      I35Down = GetIntegral(IntegralsDown, Mass, 12);   L35D = L35Down / I35Down;   I35D = I35Down;
      I45Down = GetIntegral(IntegralsDown, Mass, 14);   L45D = L45Down / I45Down;   I45D = I45Down;
      IBDown = GetIntegral(IntegralsDown, Mass, 0);     LBD = LBDown / IBDown;      IBD = IBDown;

      I11Wide = GetIntegral(IntegralsWide, Mass, 1);    L11W = L11Wide / I11Wide;   I11W = I11Wide;
      I22Wide = GetIntegral(IntegralsWide, Mass, 2);    L22W = L22Wide / I22Wide;   I22W = I22Wide;
      I33Wide = GetIntegral(IntegralsWide, Mass, 4);    L33W = L33Wide / I33Wide;   I33W = I33Wide;
      I44Wide = GetIntegral(IntegralsWide, Mass, 5);    L44W = L44Wide / I44Wide;   I44W = I44Wide;
      I55Wide = GetIntegral(IntegralsWide, Mass, 3);    L55W = L55Wide / I55Wide;   I55W = I55Wide;
      I12Wide = GetIntegral(IntegralsWide, Mass, 6);    L12W = L12Wide / I12Wide;   I12W = I12Wide;
      I13Wide = GetIntegral(IntegralsWide, Mass, 8);    L13W = L13Wide / I13Wide;   I13W = I13Wide;
      I14Wide = GetIntegral(IntegralsWide, Mass, 9);    L14W = L14Wide / I14Wide;   I14W = I14Wide;
      I15Wide = GetIntegral(IntegralsWide, Mass, 7);    L15W = L15Wide / I15Wide;   I15W = I15Wide;
      I23Wide = GetIntegral(IntegralsWide, Mass, 11);   L23W = L23Wide / I23Wide;   I23W = I23Wide;
      I24Wide = GetIntegral(IntegralsWide, Mass, 13);   L24W = L24Wide / I24Wide;   I24W = I24Wide;
      I25Wide = GetIntegral(IntegralsWide, Mass, 15);   L25W = L25Wide / I25Wide;   I25W = I25Wide;
      I34Wide = GetIntegral(IntegralsWide, Mass, 10);   L34W = L34Wide / I34Wide;   I34W = I34Wide;
      I35Wide = GetIntegral(IntegralsWide, Mass, 12);   L35W = L35Wide / I35Wide;   I35W = I35Wide;
      I45Wide = GetIntegral(IntegralsWide, Mass, 14);   L45W = L45Wide / I45Wide;   I45W = I45Wide;
      IBWide = GetIntegral(IntegralsWide, Mass, 0);     LBW = LBWide / IBWide;      IBW = IBWide;

      I11Narrow = GetIntegral(IntegralsNarrow, Mass, 1);    L11N = L11Narrow / I11Narrow;   I11N = I11Narrow;
      I22Narrow = GetIntegral(IntegralsNarrow, Mass, 2);    L22N = L22Narrow / I22Narrow;   I22N = I22Narrow;
      I33Narrow = GetIntegral(IntegralsNarrow, Mass, 4);    L33N = L33Narrow / I33Narrow;   I33N = I33Narrow;
      I44Narrow = GetIntegral(IntegralsNarrow, Mass, 5);    L44N = L44Narrow / I44Narrow;   I44N = I44Narrow;
      I55Narrow = GetIntegral(IntegralsNarrow, Mass, 3);    L55N = L55Narrow / I55Narrow;   I55N = I55Narrow;
      I12Narrow = GetIntegral(IntegralsNarrow, Mass, 6);    L12N = L12Narrow / I12Narrow;   I12N = I12Narrow;
      I13Narrow = GetIntegral(IntegralsNarrow, Mass, 8);    L13N = L13Narrow / I13Narrow;   I13N = I13Narrow;
      I14Narrow = GetIntegral(IntegralsNarrow, Mass, 9);    L14N = L14Narrow / I14Narrow;   I14N = I14Narrow;
      I15Narrow = GetIntegral(IntegralsNarrow, Mass, 7);    L15N = L15Narrow / I15Narrow;   I15N = I15Narrow;
      I23Narrow = GetIntegral(IntegralsNarrow, Mass, 11);   L23N = L23Narrow / I23Narrow;   I23N = I23Narrow;
      I24Narrow = GetIntegral(IntegralsNarrow, Mass, 13);   L24N = L24Narrow / I24Narrow;   I24N = I24Narrow;
      I25Narrow = GetIntegral(IntegralsNarrow, Mass, 15);   L25N = L25Narrow / I25Narrow;   I25N = I25Narrow;
      I34Narrow = GetIntegral(IntegralsNarrow, Mass, 10);   L34N = L34Narrow / I34Narrow;   I34N = I34Narrow;
      I35Narrow = GetIntegral(IntegralsNarrow, Mass, 12);   L35N = L35Narrow / I35Narrow;   I35N = I35Narrow;
      I45Narrow = GetIntegral(IntegralsNarrow, Mass, 14);   L45N = L45Narrow / I45Narrow;   I45N = I45Narrow;
      IBNarrow = GetIntegral(IntegralsNarrow, Mass, 0);     LBN = LBNarrow / IBNarrow;      IBN = IBNarrow;

      Branches[0] = L11C;   Branches[1] = L22C;   Branches[2] = L33C;   Branches[3] = L44C;   Branches[4] = L55C;
      Branches[5] = L12C;   Branches[6] = L13C;   Branches[7] = L14C;   Branches[8] = L15C;   Branches[9] = L23C;
      Branches[10] = L24C;  Branches[11] = L25C;  Branches[12] = L34C;  Branches[13] = L35C;  Branches[14] = L45C;
      Branches[15] = LBC;

      Branches[16] = L11U;  Branches[17] = L22U;  Branches[18] = L33U;  Branches[19] = L44U;  Branches[20] = L55U;
      Branches[21] = L12U;  Branches[22] = L13U;  Branches[23] = L14U;  Branches[24] = L15U;  Branches[25] = L23U;
      Branches[26] = L24U;  Branches[27] = L25U;  Branches[28] = L34U;  Branches[29] = L35U;  Branches[30] = L45U;
      Branches[31] = LBU;

      Branches[32] = L11D;  Branches[33] = L22D;  Branches[34] = L33D;  Branches[35] = L44D;  Branches[36] = L55D;
      Branches[37] = L12D;  Branches[38] = L13D;  Branches[39] = L14D;  Branches[40] = L15D;  Branches[41] = L23D;
      Branches[42] = L24D;  Branches[43] = L25D;  Branches[44] = L34D;  Branches[45] = L35D;  Branches[46] = L45D;
      Branches[47] = LBD;

      Branches[48] = L11W;  Branches[49] = L22W;  Branches[50] = L33W;  Branches[51] = L44W;  Branches[52] = L55W;
      Branches[53] = L12W;  Branches[54] = L13W;  Branches[55] = L14W;  Branches[56] = L15W;  Branches[57] = L23W;
      Branches[58] = L24W;  Branches[59] = L25W;  Branches[60] = L34W;  Branches[61] = L35W;  Branches[62] = L45W;
      Branches[63] = LBW;

      Branches[64] = L11N;  Branches[65] = L22N;  Branches[66] = L33N;  Branches[67] = L44N;  Branches[68] = L55N;
      Branches[69] = L12N;  Branches[70] = L13N;  Branches[71] = L14N;  Branches[72] = L15N;  Branches[73] = L23N;
      Branches[74] = L24N;  Branches[75] = L25N;  Branches[76] = L34N;  Branches[77] = L35N;  Branches[78] = L45N;
      Branches[79] = LBN;

      Branches[80] = I11C;  Branches[81] = I22C;  Branches[82] = I33C;  Branches[83] = I44C;  Branches[84] = I55C;
      Branches[85] = I12C;  Branches[86] = I13C;  Branches[87] = I14C;  Branches[88] = I15C;  Branches[89] = I23C;
      Branches[90] = I24C;  Branches[91] = I25C;  Branches[92] = I34C;  Branches[93] = I35C;  Branches[94] = I45C;
      Branches[95] = IBC;

      Branches[96] = I11U;  Branches[97] = I22U;  Branches[98] = I33U;  Branches[99] = I44U;  Branches[100] = I55U;
      Branches[101] = I12U; Branches[102] = I13U; Branches[103] = I14U; Branches[104] = I15U; Branches[105] = I23U;
      Branches[106] = I24U; Branches[107] = I25U; Branches[108] = I34U; Branches[109] = I35U; Branches[110] = I45U;
      Branches[111] = IBU;

      Branches[112] = I11D; Branches[113] = I22D; Branches[114] = I33D; Branches[115] = I44D; Branches[116] = I55D;
      Branches[117] = I12D; Branches[118] = I13D; Branches[119] = I14D; Branches[120] = I15D; Branches[121] = I23D;
      Branches[122] = I24D; Branches[123] = I25D; Branches[124] = I34D; Branches[125] = I35D; Branches[126] = I45D;
      Branches[127] = IBD;

      Branches[128] = I11W; Branches[129] = I22W; Branches[130] = I33W; Branches[131] = I44W; Branches[132] = I55W;
      Branches[133] = I12W; Branches[134] = I13W; Branches[135] = I14W; Branches[136] = I15W; Branches[137] = I23W;
      Branches[138] = I24W; Branches[139] = I25W; Branches[140] = I34W; Branches[141] = I35W; Branches[142] = I45W;
      Branches[143] = IBW;

      Branches[144] = I11N; Branches[145] = I22N; Branches[146] = I33N; Branches[147] = I44N; Branches[148] = I55N;
      Branches[149] = I12N; Branches[150] = I13N; Branches[151] = I14N; Branches[152] = I15N; Branches[153] = I23N;
      Branches[154] = I24N; Branches[155] = I25N; Branches[156] = I34N; Branches[157] = I35N; Branches[158] = I45N;
      Branches[159] = IBN;

      Branches[160] = Mass;

      OutputTree.Fill(Branches);
   }

   OutputFile.cd();
   OutputTree.Write();

   InputFile.Close();

   return 0;
}

map<double, vector<double> > ReadIntegral(string FileName)
{
   map<double, vector<double> > Integrals;

   ifstream in(FileName.c_str());

   while(in)
   {
      char line[10240] = "";
      in.getline(line, 10239, '\n');
      if(line[0] == '\0')
         continue;

      stringstream str(line);

      double Mass = -1;
      int Count = -1;
      str >> Mass >> Count;

      if(Mass < 0 || Count < 0)
         continue;

      vector<double> Temp;
      while(str)
      {
         double value = -999;
         str >> value;
         if(value < -998)
            continue;

         Temp.push_back(value);
      }

      Integrals.insert(pair<double, vector<double> >(Mass, Temp));
   }

   in.close();

   return Integrals;
}

double GetIntegral(const map<double, vector<double> > &Integrals, double Mass, int Component)
{
   if(Mass < Integrals.begin()->first)
      return 10000000000;

   double PreviousMass = -1;
   double PreviousValue = -1;
   for(map<double, vector<double> >::const_iterator iter = Integrals.begin(); iter != Integrals.end(); iter++)
   {
      if(iter->second.size() <= Component)
         return 10000000000;

      if(Mass >= iter->first)
      {
         PreviousMass = iter->first;
         PreviousValue = iter->second[Component];
         continue;
      }

      double CurrentMass = iter->first;
      double CurrentValue = iter->second[Component];

      return (Mass - PreviousMass) / (CurrentMass - PreviousMass) * (CurrentValue - PreviousValue) + PreviousValue;
   }

   return 10000000000;
}







