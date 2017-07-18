#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TGraph.h"

#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "Messenger.h"
#include "SDJetHelper.h"
#include "BasicUtilities.h"
#include "CATree.h"

int main(int argc, char *argv[]);
double GetRhoData(double Centrality);
double GetRhoMB(double Centrality);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // {   // sanity check: is rho+data and rho_MB implemented correctly?
   //    TGraph GRhoData, GRhoMB;
   //    for(double C = 0; C < 1; C = C + 0.001)
   //    {
   //       GRhoData.SetPoint(GRhoData.GetN(), C, GetRhoData(C));
   //       GRhoMB.SetPoint(GRhoMB.GetN(), C, GetRhoMB(C));
   //    }

   //    PdfFileHelper PdfFile("SanityCheck.pdf");
   //    PdfFile.AddTextPage("Check if rho is implemented correctly");

   //    GRhoMB.SetLineColor(kRed);
   //    GRhoMB.SetMarkerColor(kRed);

   //    TCanvas C;

   //    GRhoData.Draw("");
   //    GRhoMB.Draw("pl");

   //    PdfFile.AddCanvas(C);

   //    PdfFile.AddTimeStampPage();
   //    PdfFile.Close();

   //    return 0;
   // }

   ClusterSequence::set_fastjet_banner_stream(NULL);

   string InputFileName = "HiForestAOD_999.root";
   string OutputFileName = "Output_HiForestAOD_999.root";
   string Tag = "AA6Dijet100";
   double PTHatMin = -1000000;
   double PTHatMax = 1000000;

   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];
   Tag = argv[3];
   PTHatMin = atof(argv[4]);
   PTHatMax = atof(argv[5]);

   bool IsPP = IsPPFromTag(Tag);
   bool IsData = IsDataFromTag(Tag);

   TFile InputFile(InputFileName.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzer/pfTree";

   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);
   TriggerTreeMessenger MHLT(InputFile);
   SkimTreeMessenger MSkim(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", ";;", 1, 0, 1);

   TTree OutputTree("T", "T");

   double TreeHF, TreeHFPlus, TreeHFMinus, TreeHFPlusEta4, TreeHFMinusEta4;
   OutputTree.Branch("HF", &TreeHF, "HF/D");
   OutputTree.Branch("HFPlus", &TreeHFPlus, "HFPlus/D");
   OutputTree.Branch("HFMinus", &TreeHFMinus, "HFMinus/D");
   OutputTree.Branch("HFPlusEta4", &TreeHFPlusEta4, "HFPlusEta4/D");
   OutputTree.Branch("HFMinusEta4", &TreeHFMinusEta4, "HFMinusEta4/D");

   int TreePartonFlavor, TreePartonFlavorForB;
   OutputTree.Branch("Flavor", &TreePartonFlavor, "Flavor/I");
   OutputTree.Branch("FlavorB", &TreePartonFlavorForB, "FlavorB/I");

   double TreeJetCSPT, TreeJetCSRawPT, TreeJetCSEta, TreeJetCSPhi;
   OutputTree.Branch("JetCSPT", &TreeJetCSPT, "JetCSPT/D");
   OutputTree.Branch("JetCSRawPT", &TreeJetCSRawPT, "JetCSRawPT/D");
   OutputTree.Branch("JetCSEta", &TreeJetCSEta, "JetCSEta/D");
   OutputTree.Branch("JetCSPhi", &TreeJetCSPhi, "JetCSPhi/D");
   
   double TreeJetPT, TreeJetRawPT, TreeJetEta, TreeJetPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetRawPT", &TreeJetRawPT, "JetRawPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   
   double TreeSubJet1PT, TreeSubJet1Eta, TreeSubJet1Phi;
   double TreeSubJet2PT, TreeSubJet2Eta, TreeSubJet2Phi;
   OutputTree.Branch("SubJet1PT", &TreeSubJet1PT, "SubJet1PT/D");
   OutputTree.Branch("SubJet1Eta", &TreeSubJet1Eta, "SubJet1Eta/D");
   OutputTree.Branch("SubJet1Phi", &TreeSubJet1Phi, "SubJet1Phi/D");
   OutputTree.Branch("SubJet2PT", &TreeSubJet2PT, "SubJet2PT/D");
   OutputTree.Branch("SubJet2Eta", &TreeSubJet2Eta, "SubJet2Eta/D");
   OutputTree.Branch("SubJet2Phi", &TreeSubJet2Phi, "SubJet2Phi/D");

   double TreeSubJetDR, TreeSDMass;
   OutputTree.Branch("SubJetDR", &TreeSubJetDR, "SubJetDR/D");
   OutputTree.Branch("SDMass", &TreeSDMass, "SDMass/D");

   double TreeCentrality, TreePTHat, TreeRho;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");

   double TreeMatchDR, TreeMatchPT;
   OutputTree.Branch("MatchDR", &TreeMatchDR, "MatchDR/D");
   OutputTree.Branch("MatchPT", &TreeMatchPT, "MatchPT/D");

   int TreeDepth0, TreeDepth7;
   OutputTree.Branch("Depth0", &TreeDepth0, "Depth0/I");
   OutputTree.Branch("Depth7", &TreeDepth7, "Depth7/I");

   double TreeSubJetDR0, TreeSDMass0;
   double TreeSubJetDR7, TreeSDMass7;
   OutputTree.Branch("SubJetDR0", &TreeSubJetDR0, "SubJetDR0/D");
   OutputTree.Branch("SDMass0", &TreeSDMass0, "SDMass0/D");
   OutputTree.Branch("SubJetDR7", &TreeSubJetDR7, "SubJetDR7/D");
   OutputTree.Branch("SDMass7", &TreeSDMass7, "SDMass7/D");
   
   double TreeSubJet1PT0, TreeSubJet1Eta0, TreeSubJet1Phi0;
   double TreeSubJet2PT0, TreeSubJet2Eta0, TreeSubJet2Phi0;
   OutputTree.Branch("SubJet1PT0", &TreeSubJet1PT0, "SubJet1PT0/D");
   OutputTree.Branch("SubJet1Eta0", &TreeSubJet1Eta0, "SubJet1Eta0/D");
   OutputTree.Branch("SubJet1Phi0", &TreeSubJet1Phi0, "SubJet1Phi0/D");
   OutputTree.Branch("SubJet2PT0", &TreeSubJet2PT0, "SubJet2PT0/D");
   OutputTree.Branch("SubJet2Eta0", &TreeSubJet2Eta0, "SubJet2Eta0/D");
   OutputTree.Branch("SubJet2Phi0", &TreeSubJet2Phi0, "SubJet2Phi0/D");
   
   double TreeSubJet1PT7, TreeSubJet1Eta7, TreeSubJet1Phi7;
   double TreeSubJet2PT7, TreeSubJet2Eta7, TreeSubJet2Phi7;
   OutputTree.Branch("SubJet1PT7", &TreeSubJet1PT7, "SubJet1PT7/D");
   OutputTree.Branch("SubJet1Eta7", &TreeSubJet1Eta7, "SubJet1Eta7/D");
   OutputTree.Branch("SubJet1Phi7", &TreeSubJet1Phi7, "SubJet1Phi7/D");
   OutputTree.Branch("SubJet2PT7", &TreeSubJet2PT7, "SubJet2PT7/D");
   OutputTree.Branch("SubJet2Eta7", &TreeSubJet2Eta7, "SubJet2Eta7/D");
   OutputTree.Branch("SubJet2Phi7", &TreeSubJet2Phi7, "SubJet2Phi7/D");

   bool TreePassPbPb40, TreePassPbPb60, TreePassPbPb80, TreePassPbPb100;
   OutputTree.Branch("PassPbPb40", &TreePassPbPb40, "PassPbPb40/O");
   OutputTree.Branch("PassPbPb60", &TreePassPbPb60, "PassPbPb60/O");
   OutputTree.Branch("PassPbPb80", &TreePassPbPb80, "PassPbPb80/O");
   OutputTree.Branch("PassPbPb100", &TreePassPbPb100, "PassPbPb100/O");

   double TreeCHF, TreeNHF, TreeCEF, TreeNEF, TreeMUF;
   OutputTree.Branch("CHF", &TreeCHF, "CHF/D");
   OutputTree.Branch("NHF", &TreeNHF, "NHF/D");
   OutputTree.Branch("CEF", &TreeCEF, "CEF/D");
   OutputTree.Branch("NEF", &TreeNEF, "NEF/D");
   OutputTree.Branch("MUF", &TreeMUF, "MUF/D");
   
   double TreeCHM, TreeNHM, TreeCEM, TreeNEM, TreeMUM;
   OutputTree.Branch("CHM", &TreeCHM, "CHM/D");
   OutputTree.Branch("NHM", &TreeNHM, "NHM/D");
   OutputTree.Branch("CEM", &TreeCEM, "CEM/D");
   OutputTree.Branch("NEM", &TreeNEM, "NEM/D");
   OutputTree.Branch("MUM", &TreeMUM, "MUM/D");

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   PdfFileHelper PdfFile("SanityCheck.pdf");
   PdfFile.AddTextPage("Some visualizations :D");
   int WriteJetCount = 0;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE < 200 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MHLT.GetEntry(iE);
      MSkim.GetEntry(iE);
         
      HN.Fill(0);

      TreeHF = MHiEvent.hiHF;
      TreeHFPlus = MHiEvent.hiHFplus;
      TreeHFMinus = MHiEvent.hiHFminus;
      TreeHFPlusEta4 = MHiEvent.hiHFplusEta4;
      TreeHFMinusEta4 = MHiEvent.hiHFminusEta4;
         
      TreePassPbPb40 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet40_Eta5p1_v1");
      TreePassPbPb60 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
      TreePassPbPb80 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1");
      TreePassPbPb100 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1");

      if(IsData == true && IsPP == true && MHLT.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") == false)
         continue;
      if(IsData == true && IsPP == false)
      {
         if(MHLT.CheckTrigger("HLT_HIPuAK4CaloJet40_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1") == false)
         continue;
      }
      if(IsData == true && MSkim.PassBasicFilterLoose() == false)
         continue;

      SDJetHelper HSDJet(MSDJet);

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      double RhoData = GetRhoData(TreeCentrality);
      double RhoMB = GetRhoMB(TreeCentrality);

      TreeRho = TreeRho / RhoData * RhoMB;

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      vector<PseudoJet> Particles;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         P[0] = (*MPF.E)[iPF];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      double GhostArea = 0.07 * 0.07;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      vector<PseudoJet> RawJets = Sequence.inclusive_jets();

      vector<PseudoJet> CSJets(RawJets.size());
      for(int i = 0; i < (int)RawJets.size(); i++)
      {
         double Rho = GetRho(MRho.EtaMax, MRho.Rho, RawJets[i].eta()) / RhoData * RhoMB;
         double RhoM = GetRho(MRho.EtaMax, MRho.RhoM, RawJets[i].eta()) / RhoData * RhoMB;
         contrib::ConstituentSubtractor Subtractor(Rho, RhoM, 0, -1);
         Subtractor.set_alpha(1);
         CSJets[i] = Subtractor(RawJets[i]);
      }

      vector<PseudoJet> AllCandidates;
      for(int i = 0; i < (int)CSJets.size(); i++)
      {
         vector<PseudoJet> Constituents = CSJets[i].constituents();
         AllCandidates.insert(AllCandidates.end(), Constituents.begin(), Constituents.end());
      }
      ClusterSequence NewSequence(AllCandidates, Definition);
      vector<PseudoJet> Jets = NewSequence.inclusive_jets();

      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         bool WriteJet = false;
         /*
         if(MSDJet.JetPT[iJ] > 100 && GetCentrality(MHiEvent.hiBin) > 0.8 && fabs(MSDJet.JetEta[iJ]) < 1.5)
            WriteJet = true;
         if(WriteJet == true)
            WriteJetCount = WriteJetCount + 1;
         if(WriteJetCount > 20)
         {
            WriteJet = false;
            iE = EntryCount;
            break;
         }
         */
         
         if(WriteJet == true)
            PdfFile.AddTextPage(Form("SD Jet (%.2f, %.2f, %.2f) [%d:%d]", MSDJet.JetPT[iJ], MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], MHiEvent.Run, MHiEvent.Event));

         if(WriteJet == true)
         {
            TH2D HAA("HAA", "All PF;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HAA.SetStats(0);
            for(int i = 0; i < (int)Particles.size(); i++)
               HAA.Fill(Particles[i].eta(), Particles[i].phi(), Particles[i].perp());
            PdfFile.AddPlot(HAA, "colz");
            
            TCanvas Canvas;
            HAA.Draw("colz");
            TEllipse Circle;
            Circle.SetFillStyle(0);
            for(int i = 0; i < (int)RawJets.size(); i++)
               Circle.DrawEllipse(RawJets[i].eta(), RawJets[i].phi(), 0.4, 0.4, 0.0, 360, 0.0, "");
            PdfFile.AddCanvas(Canvas);
         }
         
         if(WriteJet == true)
         {
            TH2D HCS("HCS", "All PF;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HCS.SetStats(0);
            for(int i = 0; i < (int)AllCandidates.size(); i++)
               HCS.Fill(AllCandidates[i].eta(), AllCandidates[i].phi(), AllCandidates[i].perp());
            // PdfFile.AddPlot(HCS, "colz");
            
            TCanvas Canvas;
            HCS.Draw("colz");
            TEllipse Circle;
            Circle.SetFillStyle(0);
            for(int i = 0; i < (int)Jets.size(); i++)
               Circle.DrawEllipse(Jets[i].eta(), Jets[i].phi(), 0.4, 0.4, 0.0, 360, 0.0, "");
            PdfFile.AddCanvas(Canvas);
         }

         TreeJetPT = MSDJet.JetPT[iJ];
         TreeJetRawPT = MSDJet.JetRawPT[iJ];
         TreeJetEta = MSDJet.JetEta[iJ];
         TreeJetPhi = MSDJet.JetPhi[iJ];

         TreeSubJet1PT = HSDJet.RecoSubJet1[iJ].GetPT();
         TreeSubJet1Eta = HSDJet.RecoSubJet1[iJ].GetEta();
         TreeSubJet1Phi = HSDJet.RecoSubJet1[iJ].GetPhi();
         TreeSubJet2PT = HSDJet.RecoSubJet2[iJ].GetPT();
         TreeSubJet2Eta = HSDJet.RecoSubJet2[iJ].GetEta();
         TreeSubJet2Phi = HSDJet.RecoSubJet2[iJ].GetPhi();

         TreeSubJetDR = HSDJet.RecoSubJetDR[iJ];
         TreeSDMass = MSDJet.JetM[iJ];

         TreePartonFlavor = MSDJet.RefPartonFlavor[iJ];
         TreePartonFlavorForB = MSDJet.RefPartonFlavorForB[iJ];

         int BestCSJet = 0;
         double BestCSDR = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], MJet.JetEta[i], MJet.JetPhi[i]);
            if(BestCSDR < 0 || DR < BestCSDR)
            {
               BestCSJet = i;
               BestCSDR = DR;
            }
         }

         if(BestCSDR >= 0)
         {
            TreeCHF = MJet.JetPFCHF[BestCSJet];
            TreeNHF = MJet.JetPFNHF[BestCSJet];
            TreeCEF = MJet.JetPFCEF[BestCSJet];
            TreeNEF = MJet.JetPFNEF[BestCSJet];
            TreeMUF = MJet.JetPFMUF[BestCSJet];
            TreeCHM = MJet.JetPFCHM[BestCSJet];
            TreeNHM = MJet.JetPFNHM[BestCSJet];
            TreeCEM = MJet.JetPFCEM[BestCSJet];
            TreeNEM = MJet.JetPFNEM[BestCSJet];
            TreeMUM = MJet.JetPFMUM[BestCSJet];

            TreeJetCSPT = MJet.JetPT[BestCSJet];
            TreeJetCSRawPT = MJet.JetRawPT[BestCSJet];
            TreeJetCSEta = MJet.JetEta[BestCSJet];
            TreeJetCSPhi = MJet.JetPhi[BestCSJet];
         }

         int BestJet = 0;
         double BestDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], Jets[i].eta(), Jets[i].phi());
            if(BestDR < 0 || DR < BestDR)
            {
               BestJet = i;
               BestDR = DR;
            }
         }
         
         if(WriteJet == true)
         {
            TH2D HCSJet("HCSJet", "Candidates;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HCSJet.SetStats(0);
            vector<PseudoJet> JetCandidates = Jets[BestJet].constituents();
            for(int i = 0; i < (int)JetCandidates.size(); i++)
               HCSJet.Fill(JetCandidates[i].eta(), JetCandidates[i].phi(), JetCandidates[i].perp());
            PdfFile.AddPlot(HCSJet, "colz");
         }

         if(BestDR >= 0)
         {
            TreeMatchDR = BestDR;
            TreeMatchPT = Jets[BestJet].perp();

            if(TreeJetPT < 80 && TreeMatchPT < 80)   // no need to store them!
               continue;
            if(abs(TreeJetEta) > 1.5)
               continue;

            vector<PseudoJet> Constituents = Jets[BestJet].constituents();
            vector<Node *> Nodes;
            for(int i = 0; i < (int)Constituents.size(); i++)
            {
               FourVector P;
               P[0] = Constituents[i].e();
               P[1] = Constituents[i].px();
               P[2] = Constituents[i].py();
               P[3] = Constituents[i].pz();
               Nodes.push_back(new Node(P));
            }

            BuildCATree(Nodes);

            Node *Groomed0 = FindSDNode(Nodes[0], 0.1, 0.0, 0.4);
            Node *Groomed7 = FindSDNode(Nodes[0], 0.5, 1.5, 0.4);

            TreeDepth0 = NodeDistance(Groomed0, Nodes[0]);
            TreeDepth7 = NodeDistance(Groomed7, Nodes[0]);

            if(Groomed0->N > 1)
            {
               TreeSubJetDR0 = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
               TreeSDMass0 = Groomed0->P.GetMass();
         
               TreeSubJet1PT0  = Groomed0->Child1->P.GetPT();
               TreeSubJet1Eta0 = Groomed0->Child1->P.GetEta();
               TreeSubJet1Phi0 = Groomed0->Child1->P.GetPhi();
               TreeSubJet2PT0  = Groomed0->Child2->P.GetPT();
               TreeSubJet2Eta0 = Groomed0->Child2->P.GetEta();
               TreeSubJet2Phi0 = Groomed0->Child2->P.GetPhi();
            }
            else
               TreeSubJetDR0 = -1;

            if(Groomed7->N > 1)
            {
               TreeSubJetDR7 = GetDR(Groomed7->Child1->P, Groomed7->Child2->P);
               TreeSDMass7 = Groomed7->P.GetMass();
               
               TreeSubJet1PT7 = Groomed7->Child1->P.GetPT();
               TreeSubJet1Eta7 = Groomed7->Child1->P.GetEta();
               TreeSubJet1Phi7 = Groomed7->Child1->P.GetPhi();
               TreeSubJet2PT7 = Groomed7->Child2->P.GetPT();
               TreeSubJet2Eta7 = Groomed7->Child2->P.GetEta();
               TreeSubJet2Phi7 = Groomed7->Child2->P.GetPhi();
            }
            else
               TreeSubJetDR7 = -1;

            if(WriteJet == true)
            {
               vector<string> Text(20);
               Text[0] = Form("SDJet: (%.1f, %.2f, %.2f)", MSDJet.JetPT[iJ], MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ]);
               Text[1] = "";
               Text[2] = Form("BestJet: (%.1f, %.2f, %.2f)", Jets[BestJet].perp(), Jets[BestJet].eta(), Jets[BestJet].phi());
               Text[3] = Form("GroomedPT %.2f", Groomed0->P.GetPT());
               Text[4] = Form("SDMass %.2f, SDMass/Jet %.2f", Groomed0->P.GetMass(), Groomed0->P.GetMass() / Jets[BestJet].perp());
               Text[5] = Form("DR %.2f, ZG %.2f", TreeSubJetDR0, min(TreeSubJet1PT0, TreeSubJet2PT0) / (TreeSubJet1PT0 + TreeSubJet2PT0));
               Text[6] = "";
               Text[7] = Form("SubJet1 (%.1f, %.2f, %.2f)", TreeSubJet1PT0, TreeSubJet1Eta0, TreeSubJet1Phi0);
               Text[8] = Form("SubJet2 (%.1f, %.2f, %.2f)", TreeSubJet2PT0, TreeSubJet2Eta0, TreeSubJet2Phi0);

               PdfFile.AddTextPage(Text);
            }

            delete Nodes[0];
         }
         else
            TreeMatchDR = -1;

         OutputTree.Fill();
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   HN.Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}

double GetRhoData(double Centrality)
{
   double P[8] = {240.157, -1306.41, 4848.53, -14469, 29089.2, -35111.9, 22896.1, -6188.81};
   return ((((((P[7] * Centrality + P[6]) * Centrality + P[5]) * Centrality + P[4]) * Centrality + P[3]) * Centrality + P[2]) * Centrality + P[1]) * Centrality + P[0];
}

double GetRhoMB(double Centrality)
{
   double P[8] = {229.823, -1091.79, 2645.22, -3995.89, 3066.11, -7.92988, -1466.14, 621.696};
   return ((((((P[7] * Centrality + P[6]) * Centrality + P[5]) * Centrality + P[4]) * Centrality + P[3]) * Centrality + P[2]) * Centrality + P[1]) * Centrality + P[0];
}




