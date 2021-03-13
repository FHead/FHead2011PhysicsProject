
default: Harvest.sh

Execute:
	bash Execute.sh

Deploy: Deploy2018 Deploy2017

Deploy2018:
	bash Harvest.sh 2018
	for i in `seq 1 9`; do cp MeowMC2018_L2Relative_AK$${i}PF.txt JECDatabase/Autumn18_HI_RAAV2_MC/Autumn18_HI_RAAV2_MC_L2Relative_AK$${i}PF.txt; done

Merge2017:
	bash Merge2017.sh

Deploy2017:
	bash Harvest.sh 2017
	for i in `seq 1 9`; do cp MeowMC2017_L2Relative_AK$${i}PF.txt JECDatabase/Spring18_ppRef5TeV_RAAV2_MC/Spring18_ppRef5TeV_RAAV2_MC_L2Relative_AK$${i}PF.txt; done
