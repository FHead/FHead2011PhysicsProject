mkdir -p CombinedResults/

##################################################
#Combine Trees
##################################################
./CombineLikelihoodJobs BatchResult/FA2FA3_Signal8TeV_8TeV_channel0 150 CombinedResults/FA2FA3_Signal8TeV_8TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Signal7TeV_7TeV_channel0 77 CombinedResults/FA2FA3_Signal7TeV_7TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background8TeV_8TeV_channel0 10 CombinedResults/FA2FA3_Background8TeV_8TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background7TeV_7TeV_channel0 119 CombinedResults/FA2FA3_Background7TeV_7TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets8TeV_8TeV_channel0 132 CombinedResults/FA2FA3_ZJets8TeV_8TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets7TeV_7TeV_channel0 70 CombinedResults/FA2FA3_ZJets7TeV_7TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ8TeV_8TeV_channel0 45 CombinedResults/FA2FA3_ggZZ8TeV_8TeV_channel0_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ7TeV_7TeV_channel0 45 CombinedResults/FA2FA3_ggZZ7TeV_7TeV_channel0_combined.root

./CombineLikelihoodJobs BatchResult/FA2FA3_Signal8TeV_8TeV_channel1 150 CombinedResults/FA2FA3_Signal8TeV_8TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Signal7TeV_7TeV_channel1 77 CombinedResults/FA2FA3_Signal7TeV_7TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background8TeV_8TeV_channel1 10 CombinedResults/FA2FA3_Background8TeV_8TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background7TeV_7TeV_channel1 119 CombinedResults/FA2FA3_Background7TeV_7TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets8TeV_8TeV_channel1 132 CombinedResults/FA2FA3_ZJets8TeV_8TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets7TeV_7TeV_channel1 70 CombinedResults/FA2FA3_ZJets7TeV_7TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ8TeV_8TeV_channel1 45 CombinedResults/FA2FA3_ggZZ8TeV_8TeV_channel1_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ7TeV_7TeV_channel1 45 CombinedResults/FA2FA3_ggZZ7TeV_7TeV_channel1_combined.root

./CombineLikelihoodJobs BatchResult/FA2FA3_Signal8TeV_8TeV_channel2 150 CombinedResults/FA2FA3_Signal8TeV_8TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Signal7TeV_7TeV_channel2 77 CombinedResults/FA2FA3_Signal7TeV_7TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background8TeV_8TeV_channel2 10 CombinedResults/FA2FA3_Background8TeV_8TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background7TeV_7TeV_channel2 119 CombinedResults/FA2FA3_Background7TeV_7TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets8TeV_8TeV_channel2 132 CombinedResults/FA2FA3_ZJets8TeV_8TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets7TeV_7TeV_channel2 70 CombinedResults/FA2FA3_ZJets7TeV_7TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ8TeV_8TeV_channel2 45 CombinedResults/FA2FA3_ggZZ8TeV_8TeV_channel2_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ7TeV_7TeV_channel2 45 CombinedResults/FA2FA3_ggZZ7TeV_7TeV_channel2_combined.root

./CombineLikelihoodJobs BatchResult/FA2FA3_Signal8TeV_8TeV_channel3 150 CombinedResults/FA2FA3_Signal8TeV_8TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Signal7TeV_7TeV_channel3 77 CombinedResults/FA2FA3_Signal7TeV_7TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background8TeV_8TeV_channel3 10 CombinedResults/FA2FA3_Background8TeV_8TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_Background7TeV_7TeV_channel3 119 CombinedResults/FA2FA3_Background7TeV_7TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets8TeV_8TeV_channel3 132 CombinedResults/FA2FA3_ZJets8TeV_8TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ZJets7TeV_7TeV_channel3 70 CombinedResults/FA2FA3_ZJets7TeV_7TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ8TeV_8TeV_channel3 45 CombinedResults/FA2FA3_ggZZ8TeV_8TeV_channel3_combined.root
./CombineLikelihoodJobs BatchResult/FA2FA3_ggZZ7TeV_7TeV_channel3 45 CombinedResults/FA2FA3_ggZZ7TeV_7TeV_channel3_combined.root



##################################################
#Final Combine
##################################################
./CombineLikelihood CombinedResults/FA2FA3 CombinedResults/FA2FA3_combined.root







