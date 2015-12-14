for i in ddbar_*
do
   echo
   ./DoCut $i Result_$i N
   ./RunPlot Result_$i ColorPlot_${i/.root/} Relative
   ./RunPlot Result_$i AbsoluteColorPlot_${i/.root/} Absolute
   ./RunPlot Result_$i NoLeptonCutColorPlot_${i/.root/} None
done

for i in png C eps pdf
do
   cp AbsoluteColorPlot_gg_h_2e2mu_A2ZZ_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2ZZ-2e2mu.$i
   cp AbsoluteColorPlot_gg_h_2e2mu_A2ZA_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2ZA-2e2mu.$i
   cp AbsoluteColorPlot_gg_h_2e2mu_A2AA_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2AA-2e2mu.$i
   cp AbsoluteColorPlot_gg_h_4e_A2ZZ_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2ZZ-4e.$i
   cp AbsoluteColorPlot_gg_h_4e_A2ZA_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2ZA-4e.$i
   cp AbsoluteColorPlot_gg_h_4e_A2AA_LooseCuts.$i GeneratorLevelPrecision-Improvement-AbsoluteColorPlot-A2AA-4e.$i
   cp ColorPlot_gg_h_2e2mu_A2ZZ_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2ZZ-2e2mu.$i
   cp ColorPlot_gg_h_2e2mu_A2ZA_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2ZA-2e2mu.$i
   cp ColorPlot_gg_h_2e2mu_A2AA_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2AA-2e2mu.$i
   cp ColorPlot_gg_h_4e_A2ZZ_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2ZZ-4e.$i
   cp ColorPlot_gg_h_4e_A2ZA_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2ZA-4e.$i
   cp ColorPlot_gg_h_4e_A2AA_LooseCuts.$i GeneratorLevelPrecision-Improvement-ColorPlot-A2AA-4e.$i
done





