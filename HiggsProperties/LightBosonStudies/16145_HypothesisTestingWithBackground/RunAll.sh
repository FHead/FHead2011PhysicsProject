for ID in `seq 2 10`
do
   for Cut in P F
   do
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UU_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A1UU_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UU_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A2UU_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A3UU_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A3UU_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UA_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A2UA_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UZ_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A2UZ_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UUpA3UU_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A1UUpA3UU_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UURIpA1UZRI_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A1UURIpA1UZRI_${Cut}_${ID}
      ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UURpA1UZR_18p4GeV_noPDF_GenCuts_${ID}.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root $Cut A1UURpA1UZR_${Cut}_${ID}
   done
done
