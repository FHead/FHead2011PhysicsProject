for Cut in F P
do
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UU_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A1UU_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UUpA3UU_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A1UUpA3UU_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UURIpA1UZRI_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A1UURIpA1UZRI_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A1UURpA1UZR_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A1UURpA1UZR_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UA_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A2UA_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UU_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A2UU_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A2UZ_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A2UZ_${Cut}_1
   ./RunLikelihood Trees16141/ggtoPhto2e2mu_A3UU_18p4GeV_noPDF_GenCuts_1.root Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_1.root $Cut A3UU_${Cut}_1
done
