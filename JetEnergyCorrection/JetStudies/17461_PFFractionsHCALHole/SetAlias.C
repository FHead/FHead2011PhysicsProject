{
   Events->SetAlias("AK4PF", "recoPFJets_ak4PFJets__RECO.obj");
   Events->SetAlias("AK4PFMomentum", "AK4PF.m_state.p4Polar_.fCoordinates");
   Events->SetAlias("AK4PFPT", "AK4PFMomentum.fPt");
   Events->SetAlias("AK4PFEta", "AK4PFMomentum.fEta");
   Events->SetAlias("AK4PFPhi", "AK4PFMomentum.fPhi");
   Events->SetAlias("AK4PFFractions", "AK4PF.m_specific");
   Events->SetAlias("AK4PFCHF", "(AK4PFFractions.mChargedHadronEnergy/AK4PFPT/cosh(AK4PFEta))");
   Events->SetAlias("AK4PFCEF", "(AK4PFFractions.mChargedEmEnergy/AK4PFPT/cosh(AK4PFEta))");
   Events->SetAlias("AK4PFNHF", "(AK4PFFractions.mNeutralHadronEnergy/AK4PFPT/cosh(AK4PFEta))");
   Events->SetAlias("AK4PFNEF", "(AK4PFFractions.mNeutralEmEnergy/AK4PFPT/cosh(AK4PFEta))");
}
