#include <iostream>
using namespace std;

#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions2.h"

#include "Messenger.h"
#include "BasicUtilities.h"

int main()
{
   TFile File("HiForestAOD_999.root");

   HiEventTreeMessenger MHiEvent(File);
   JetTreeMessenger MJet(File);
   PFTreeMessenger MPF(File);
   RhoTreeMessenger MRho(File);

   if(MHiEvent.Tree == NULL)
      return -1;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);

      vector<PseudoJet> Particles;
      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
         P[0] = (*MPF.E)[i];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      double GhostArea = 0.0005;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      vector<PseudoJet> NewJets(Jets.size());
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         double rho = GetRho(MRho.EtaMax, MRho.Rho, Jets[i].eta());
         double rhom = GetRho(MRho.EtaMax, MRho.RhoM, Jets[i].eta());
         contrib::ConstituentSubtractor Subtractor(rho, rhom);
         Subtractor.set_alpha(1);  // optional
         // subtractor.set_max_deltaR(2);  // optional
         NewJets[i] = Subtractor(Jets[i]);
      }

      for(int i = 0; i < (int)NewJets.size(); i++)
      {
         double rho = GetRho(MRho.EtaMax, MRho.Rho, Jets[i].eta());
         double rhom = GetRho(MRho.EtaMax, MRho.RhoM, Jets[i].eta());
         cout << rho << " " << rhom << endl;
         cout << Jets[i].perp() << " " << Jets[i].eta() << " " << Jets[i].phi() << endl;
         cout << NewJets[i].perp() << " " << NewJets[i].eta() << " " << NewJets[i].phi() << endl;
         cout << endl;
      }

      break;
   }

   File.Close();

   return 0;
}





