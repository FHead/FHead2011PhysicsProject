#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/DrawRandom.h"
#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 10000

int main(int argc, char *argv[]);
double DrawMomentum(double Mean);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input  = CL.Get("input");
   string Output = CL.Get("output");
   double JetR   = CL.GetDouble("r", 0.4);
   double MinJetPT = CL.GetDouble("minjetpt", 50);
   double MultiplicativeMean = CL.GetDouble("multiplicativemean", 0.9);
   double MultiplicativeSigma = CL.GetDouble("multiplicativesigma", 0.05);
   double SubtractiveMean = CL.GetDouble("subtractivemean", 5);
   double SubtractiveSigma = CL.GetDouble("subtractivesigma", 2);
   double GrassMean = CL.GetDouble("grassmean", 1.2);
   bool UniformGrass = CL.GetBool("uniformgrass", true);
   double Fraction = CL.GetDouble("fraction", 1.00);

   TFile File(Input.c_str());
   TTree *Tree = (TTree *)File.Get("tgen");

   int nParticle;
   float e[MAX];
   float px[MAX];
   float py[MAX];
   float pz[MAX];
   int status[MAX];
   int pid[MAX];
   Tree->SetBranchAddress("nParticle", &nParticle);
   Tree->SetBranchAddress("e", &e);
   Tree->SetBranchAddress("px", &px);
   Tree->SetBranchAddress("py", &py);
   Tree->SetBranchAddress("pz", &pz);
   Tree->SetBranchAddress("status", &status);
   Tree->SetBranchAddress("pid", &pid);

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("MorphedTree", "MorphedTree");

   OutputTree.Branch("MinJetPT", &MinJetPT, "MinJetPT/D");
   OutputTree.Branch("MultiplicativeMean", &MultiplicativeMean, "MultiplicativeMean/D");
   OutputTree.Branch("MultiplicativeSigma", &MultiplicativeSigma, "MultiplicativeSigma/D");
   OutputTree.Branch("SubtractiveMean", &SubtractiveMean, "SubtractiveMean/D");
   OutputTree.Branch("SubtractiveSigma", &SubtractiveSigma, "SubtractiveSigma/D");
   OutputTree.Branch("GrassMean", &GrassMean, "GrassMean/D");
   
   int N;
   double E[MAX];
   double PX[MAX];
   double PY[MAX];
   double PZ[MAX];
   double PT[MAX];
   double Eta[MAX];
   double Phi[MAX];
   int PID[MAX];
   int Status[MAX];

   OutputTree.Branch("N", &N, "N/I");
   OutputTree.Branch("E", &E, "E[N]/D");
   OutputTree.Branch("PX", &PX, "PX[N]/D");
   OutputTree.Branch("PY", &PY, "PY[N]/D");
   OutputTree.Branch("PZ", &PZ, "PZ[N]/D");
   OutputTree.Branch("PT", &PT, "PT[N]/D");
   OutputTree.Branch("Eta", &Eta, "Eta[N]/D");
   OutputTree.Branch("Phi", &Phi, "Phi[N]/D");
   OutputTree.Branch("PID", &PID, "PID[N]/I");
   OutputTree.Branch("Status", &Status, "Status[N]/I");

   int EntryCount = Tree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      vector<FourVector> P;
      for(int i = 0; i < nParticle; i++)
         P.emplace_back(FourVector(e[i], px[i], py[i], pz[i]));

      vector<PseudoJet> FastJetParticles;
      for(int i = 0; i < nParticle; i++)
      {
         if(status[i] != 1)                  continue;
         if(pid[i] == 12 || pid[i] == -12)   continue;
         if(pid[i] == 14 || pid[i] == -14)   continue;
         if(pid[i] == 16 || pid[i] == -16)   continue;

         FastJetParticles.push_back(PseudoJet(px[i], py[i], pz[i], e[i]));
      }
      JetDefinition Definition(antikt_algorithm, JetR);
      ClusterSequence Sequence(FastJetParticles, Definition);
      vector<PseudoJet> FastJets = Sequence.inclusive_jets();

      int NJet = FastJets.size();

      vector<FourVector> Jets;
      for(int iJ = 0; iJ < NJet; iJ++)
         Jets.emplace_back(FastJets[iJ].e(), FastJets[iJ].px(), FastJets[iJ].py(), FastJets[iJ].pz());

      vector<FourVector> EnergyLostInJet(NJet);
      for(int iP = 0; iP < nParticle; iP++)
      {
         if(status[iP] != 1)
            continue;

         int BestIndex = -1;
         double BestDR = -1;
         for(int iJ = 0; iJ < NJet; iJ++)
         {
            double DR = GetDR(Jets[iJ], P[iP]);
            if(BestDR < 0 || DR < BestDR)
            {
               BestIndex = iJ;
               BestDR = DR;
            }
         }

         if(BestDR > JetR)
            continue;
         if(BestDR < 0)
            continue;
         if(Jets[BestIndex].GetPT() < MinJetPT)
            continue;

         FourVector OriginalP = P[iP];
         double NewPT = P[iP].GetPT();
         if(MultiplicativeSigma > 0)
            NewPT = NewPT * min(1.0, DrawGaussian(MultiplicativeMean, MultiplicativeSigma));
         if(SubtractiveSigma > 0)
            NewPT = NewPT - max(0.0, DrawGaussian(SubtractiveMean, SubtractiveSigma));
         if(NewPT <= 0)
            NewPT = 1e-10;
         P[iP].SetPtEtaPhi(NewPT, P[iP].GetEta(), P[iP].GetPhi());

         EnergyLostInJet[BestIndex] = EnergyLostInJet[BestIndex] + (OriginalP - P[iP]);
      }

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         vector<FourVector> Grass;

         // cout << iJ << " " << EnergyLostInJet[iJ].GetPT() << " " << Jets[iJ].GetPT() << endl;
         // cout << " " << EnergyLostInJet[iJ].GetEta() << " " << EnergyLostInJet[iJ].GetPhi() << endl;
         // cout << " " << Jets[iJ].GetEta() << " " << Jets[iJ].GetPhi() << endl;

         double DR = GetDR(EnergyLostInJet[iJ], Jets[iJ]);
         if(DR > M_PI / 2)   // huh?
            continue;

         FourVector CurrentJet = Jets[iJ] - EnergyLostInJet[iJ];

         while(CurrentJet.GetPT() < Jets[iJ].GetPT())
         {
            double GrassPT = DrawMomentum(GrassMean);
            double Eta, Phi;
            if(UniformGrass == true)
            {
               double DR = sqrt(DrawRandom(0, 1)) * JetR;
               double Angle = DrawRandom(0, 2 * M_PI);
               double Eta = DR * cos(Angle) + Jets[iJ].GetEta();
               double Phi = DR * sin(Angle) + Jets[iJ].GetPhi();
            }
            else
            {
               do
               {
                  Eta = DrawGaussian(JetR * 0.5);
                  Phi = DrawGaussian(JetR * 0.5);
               } while(Eta * Eta + Phi * Phi > JetR * JetR);
               Eta = Eta + Jets[iJ].GetEta();
               Phi = Phi + Jets[iJ].GetPhi();
            }

            FourVector NewGrass;
            NewGrass.SetPtEtaPhiMass(GrassPT, Eta, Phi, 0.135);

            double TotalPT = (CurrentJet + NewGrass).GetPT();

            if(TotalPT < Jets[iJ].GetPT())
            {
               CurrentJet = CurrentJet + NewGrass;
               Grass.push_back(NewGrass);
            }
            else
            {
               NewGrass = NewGrass * (TotalPT - Jets[iJ].GetPT()) / (TotalPT - CurrentJet.GetPT());
               CurrentJet = CurrentJet + NewGrass;
               Grass.push_back(NewGrass);
               break;
            }
         }

         if(iE == 0 && Jets[iJ].GetPT() > 50)
            cout << CurrentJet << " " << Jets[iJ] << " " << Jets[iJ] - EnergyLostInJet[iJ] << endl;

         P.insert(P.end(), Grass.begin(), Grass.end());
      }
      
      N = P.size();
      for(int i = 0; i < N; i++)
      {
         E[i] = P[i][0];
         PX[i] = P[i][1];
         PY[i] = P[i][2];
         PZ[i] = P[i][3];
         PT[i] = P[i].GetPT();
         Eta[i] = P[i].GetEta();
         Phi[i] = P[i].GetPhi();
         Status[i] = (i < nParticle) ? status[i] : 1;
         PID[i] = (i < nParticle) ? pid[i] : (299 * (2 * (DrawRandom(-1, 1) > 0) - 1));
      }

      OutputTree.Fill();
   }

   OutputFile.Close();

   File.Close();

   return 0;
}

double DrawMomentum(double Mean)
{
   double a = 2 / Mean;
   double X;

   double Max = Mean * 20;

   bool Good = false;
   while(Good == false)
   {
      X = DrawExponential(-a, 0);
      if(X < Max && DrawRandom(0, 1) < X / Max)
         Good = true;
   }

   return X;
}

