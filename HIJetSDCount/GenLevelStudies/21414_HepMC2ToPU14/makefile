default: SayHi

SayHi:
	echo Hi

Execute: Convert.cpp
	g++ Convert.cpp -o Execute

ConvertR: Execute
	for i in `seq 11 30`; do ./Execute SamplesBase/dijets_pthat150/jewel_PbPb_simple_$$i.hepmc SamplesBase/dijets_pthat150/RootSimple/jewel_$$i.root; done
	for i in `seq 11 30`; do ./Execute SamplesBase/dijets_pthat150/jewel_PbPb_vac_$$i.hepmc SamplesBase/dijets_pthat150/RootVac/jewel_$$i.root; done
	for i in `seq 11 30`; do ./Execute SamplesBase/dijets_pthat70/jewel_PbPb_simple_$$i.hepmc SamplesBase/dijets_pthat70/RootSimple/jewel_$$i.root; done
	for i in `seq 11 30`; do ./Execute SamplesBase/dijets_pthat70/jewel_PbPb_vac_$$i.hepmc SamplesBase/dijets_pthat70/RootVac/jewel_$$i.root; done

ConvertNR: Execute
	for i in `seq 1 30`; do ./Execute SamplesBaseNR/dijets_pthat150/jewel_PbPb_simple_$$i.hepmc SamplesBaseNR/dijets_pthat150/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do ./Execute SamplesBaseNR/dijets_pthat150/jewel_PbPb_vac_$$i.hepmc SamplesBaseNR/dijets_pthat150/RootVac/jewel_$$i.root; done
	for i in `seq 1 30`; do ./Execute SamplesBaseNR/dijets_pthat70/jewel_PbPb_simple_$$i.hepmc SamplesBaseNR/dijets_pthat70/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do ./Execute SamplesBaseNR/dijets_pthat70/jewel_PbPb_vac_$$i.hepmc SamplesBaseNR/dijets_pthat70/RootVac/jewel_$$i.root; done

ConvertZJet: Execute
	# for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat150/jewel_PbPb_simple_$$i.hepmc SamplesBase/zjet_pthat150/RootSimple/jewel_$$i.root; done
	# for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat150/jewel_PbPb_vac_$$i.hepmc SamplesBase/zjet_pthat150/RootVac/jewel_$$i.root; done
	# for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat70/jewel_PbPb_simple_$$i.hepmc SamplesBase/zjet_pthat70/RootSimple/jewel_$$i.root; done
	# for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat70/jewel_PbPb_vac_$$i.hepmc SamplesBase/zjet_pthat70/RootVac/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat150/jewel_PbPb_simple_$$i.hepmc SamplesBaseNR/zjet_pthat150/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat150/jewel_PbPb_vac_$$i.hepmc SamplesBaseNR/zjet_pthat150/RootVac/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat70/jewel_PbPb_simple_$$i.hepmc SamplesBaseNR/zjet_pthat70/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat70/jewel_PbPb_vac_$$i.hepmc SamplesBaseNR/zjet_pthat70/RootVac/jewel_$$i.root; done

ConvertDiJetFull: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat70_full/jewel_PbPb_simple_$$i.hepmc SamplesBase/dijets_pthat70_full/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat70_full/jewel_PbPb_vac_$$i.hepmc SamplesBase/dijets_pthat70_full/RootVac/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat70_full/jewel_PbPb_simple_$$i.hepmc SamplesBaseNR/dijets_pthat70_full/RootSimple/jewel_$$i.root; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat70_full/jewel_PbPb_vac_$$i.hepmc SamplesBaseNR/dijets_pthat70_full/RootVac/jewel_$$i.root; done
