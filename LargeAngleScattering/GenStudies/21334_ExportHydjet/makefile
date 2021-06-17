MAX = 40000

default: TestRun

TestRun: Execute
	# ./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root --Output /tmp/chenyi/HydjetCentral.pu14 --MaxEvent $(MAX)--PTHatMin -1000000 --PTHatMax 1000000 --HiBinMin 0 --HiBinMax 20
	./Execute --Input /eos/cms/store/group/phys_heavyions/chenyi///Samples/store/user/rbi/merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root --Output /tmp/chenyi/HydjetCentral.pu14 --MaxEvent $(MAX)--PTHatMin -1000000 --PTHatMax 1000000 --HiBinMin 0 --HiBinMax 20

ExportPhotonJet: Execute
	./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Pythia8_Photon15_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root --Output /tmp/chenyi/PhotonJet15.pu14 --MaxEvent $(MAX)--PTHatMin 15 --PTMatMax 30
	./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Pythia8_Photon30_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root --Output /tmp/chenyi/PhotonJet30.pu14 --MaxEvent $(MAX)--PTHatMin 30 --PTMatMax 50
	./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Pythia8_Photon50_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root --Output /tmp/chenyi/PhotonJet50.pu14 --MaxEvent $(MAX)--PTHatMin 50 --PTMatMax 80
	./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Pythia8_Photon80_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root --Output /tmp/chenyi/PhotonJet80.pu14 --MaxEvent $(MAX)--PTHatMin 80 --PTMatMax 120
	./Execute --Input root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/Pythia8_Photon120_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root --Output /tmp/chenyi/PhotonJet120.pu14 --MaxEvent $(MAX)--PTHatMin 120 --PTMatMax 10000

Execute: ExportHydjet.cpp
	CompileRootMacro ExportHydjet.cpp Execute
