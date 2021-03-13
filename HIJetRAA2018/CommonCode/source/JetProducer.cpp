#include "include/JetProducer.h"

#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"

#include "Math/ProbFuncMathCore.h"

#include "include/RhoCalculator.h"

JetProducer::JetProducer()
{
   SetCMSPreset();
}

JetProducer::~JetProducer()
{
}

void JetProducer::SetCMSPreset()
{
   PassThrough = false;
   MinProbability = 0.05;
   MaxProbability = 0.95;
   MinJetPT = 0;
   CSR = -1;
   CSAlpha = 2;
   JetR = 0.4;
   MinPTDiff = -1000;
}
   
std::vector<FourVector> JetProducer::ClusterJets(const std::vector<FourVector> &PF,
   const std::vector<FourVector> &PFID1)
{
   std::vector<fastjet::PseudoJet> FJPF;
   for(const FourVector &P : PF)
      FJPF.emplace_back(P[1], P[2], P[3], P[0]);
   fastjet::JetDefinition Definition(fastjet::antikt_algorithm, JetR);
   fastjet::GhostedAreaSpec GhostArea(6.5, 1, 0.005);
   fastjet::AreaDefinition AreaDefinition(fastjet::active_area_explicit_ghosts,
      GhostArea);
   fastjet::ClusterSequenceArea Sequence(FJPF, Definition, AreaDefinition);
   std::vector<fastjet::PseudoJet> TempJets = Sequence.inclusive_jets(MinJetPT);

   std::vector<FourVector> Jets;

   if(PassThrough == true)
   {
      for(fastjet::PseudoJet J : TempJets)
         Jets.emplace_back(J.e(), J.px(), J.py(), J.pz());
      return Jets;
   }

   CRho.CalculateRho(PF);
   std::vector<double> PPhi = CPhi.DoRhoModulationFit(PFID1);

   for(fastjet::PseudoJet J : TempJets)
   {
      std::vector<fastjet::PseudoJet> Particle, Ghost;
      fastjet::SelectorIsPureGhost().sift(J.constituents(), Ghost, Particle);
      if(Particle.size() == 0)
         continue;

      double FitProbability = ROOT::Math::chisquared_cdf_c(PPhi[5], PPhi[6]);

      fastjet::PseudoJet AllGhost;
      for(fastjet::PseudoJet &G : Ghost)
      {
         double Modulation = 1;
         if(FitProbability > MinProbability && FitProbability < MaxProbability)
            Modulation = CPhi.GetModulation(G.phi());

         double PT = CRho.GetRho(G.eta()) * G.area() * Modulation;
         G.reset_momentum_PtYPhiM(PT, G.rap(), G.phi(), 0);

         AllGhost = AllGhost + G;
      }
      double PTDiff = J.perp() - AllGhost.perp();
      if(PTDiff < MinPTDiff)
         continue;

      fastjet::contrib::ConstituentSubtractor Subtractor;
      Subtractor.set_distance_type(fastjet::contrib::ConstituentSubtractor::deltaR);
      Subtractor.set_max_distance(CSR);
      Subtractor.set_alpha(CSAlpha);
      Subtractor.set_do_mass_subtraction(true);
      Subtractor.set_remove_all_zero_pt_particles(true);

      fastjet::PseudoJet Subtracted
         = fastjet::join(Subtractor.do_subtraction(Particle, Ghost));
      if(Subtracted.perp() > 0)
      {
         FourVector J;
         J.SetPtEtaPhiMass(Subtracted.perp(), Subtracted.eta(), Subtracted.phi(), Subtracted.m());
         Jets.emplace_back(J);
      }
   }

   return Jets;
}
