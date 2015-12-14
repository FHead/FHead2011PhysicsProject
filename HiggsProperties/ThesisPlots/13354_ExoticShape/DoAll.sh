for i in gg_h_*_A2[ZA][ZA]*root
do
   echo
   ./RunMassPlot $i ${i/.root/} Y
   # ./RunDistributionPlot $i ${i/.root/}
done

mkdir -p NoCutMassPlots
mv gg_h_*M1M2*NoCut* NoCutMassPlots/

mkdir -p WithCutMassPlots
mv gg_h_*M1M2* WithCutMassPlots/

mkdir -p DistributionPlots
mv gg_h_*LooseCuts-* DistributionPlots/

for i in png C eps pdf
do
   cp NoCutMassPlots/gg_h_2e2mu_A2AA_LooseCuts-M1M2CMSNoCut.$i EffectiveVertex-VertexParameterization-ExoticSignalShapesA2AA.$i
   cp NoCutMassPlots/gg_h_2e2mu_A2ZA_LooseCuts-M1M2CMSNoCut.$i EffectiveVertex-VertexParameterization-ExoticSignalShapesA2ZA.$i
   cp NoCutMassPlots/gg_h_2e2mu_A2ZZ_LooseCuts-M1M2CMSNoCut.$i EffectiveVertex-VertexParameterization-ExoticSignalShapesA2ZZ.$i
   cp NoCutMassPlots/gg_h_2e2mu_SMVV_A2ZZ0d0_LooseCuts-M1M2CMSNoCut.$i EffectiveVertex-VertexParameterization-ExoticSignalShapesA1ZZ.$i
   cp NoCutMassPlots/gg_h_2e2mu_A2ZZ_LooseCuts-M1M2CMSNoCut.$i GeneratorLevelPrecision-Improvement-MassA2AA2e2muZZ.$i
   cp NoCutMassPlots/gg_h_4e_A2ZZ_LooseCuts-M1M2CMSNoCut.$i    GeneratorLevelPrecision-Improvement-MassA2AA4eZZ.$i
   cp NoCutMassPlots/gg_h_2e2mu_A2AA_LooseCuts-M1M2CMSNoCut.$i GeneratorLevelPrecision-Improvement-MassA2AA2e2muAA.$i
   cp NoCutMassPlots/gg_h_4e_A2AA_LooseCuts-M1M2CMSNoCut.$i    GeneratorLevelPrecision-Improvement-MassA2AA4eAA.$i
done


