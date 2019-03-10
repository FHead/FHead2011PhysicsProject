ConvertAllR: Convert150Vac Convert150Simple Convert70Vac Convert70Simple

ConvertAllNR: Convert150VacNR Convert150SimpleNR Convert70VacNR Convert70SimpleNR

Execute: Converter.cpp
	CompileRootMacro Converter.cpp Execute

Convert150Vac: Execute
	for i in `seq 11 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat150/RootVac/jewel_$$i.root SamplesBase/dijets_pthat150/PU14Vac/jewel_$$i.pu14; done

Convert150Simple: Execute
	for i in `seq 11 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat150/RootSimple/jewel_$$i.root SamplesBase/dijets_pthat150/PU14Simple/jewel_$$i.pu14; done

Convert70Vac: Execute
	for i in `seq 11 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat70/RootVac/jewel_$$i.root SamplesBase/dijets_pthat70/PU14Vac/jewel_$$i.pu14; done

Convert70Simple: Execute
	for i in `seq 11 30`; do echo $$i; ./Execute SamplesBase/dijets_pthat70/RootSimple/jewel_$$i.root SamplesBase/dijets_pthat70/PU14Simple/jewel_$$i.pu14; done

Convert150VacNR: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat150/RootVac/jewel_$$i.root SamplesBaseNR/dijets_pthat150/PU14Vac/jewel_$$i.pu14; done

Convert150SimpleNR: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat150/RootSimple/jewel_$$i.root SamplesBaseNR/dijets_pthat150/PU14Simple/jewel_$$i.pu14; done

Convert70VacNR: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat70/RootVac/jewel_$$i.root SamplesBaseNR/dijets_pthat70/PU14Vac/jewel_$$i.pu14; done

Convert70SimpleNR: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/dijets_pthat70/RootSimple/jewel_$$i.root SamplesBaseNR/dijets_pthat70/PU14Simple/jewel_$$i.pu14; done
	
ConvertZJet: Execute
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat150/RootVac/jewel_$$i.root SamplesBase/zjet_pthat150/PU14Vac/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat150/RootSimple/jewel_$$i.root SamplesBase/zjet_pthat150/PU14Simple/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat70/RootVac/jewel_$$i.root SamplesBase/zjet_pthat70/PU14Vac/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBase/zjet_pthat70/RootSimple/jewel_$$i.root SamplesBase/zjet_pthat70/PU14Simple/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat150/RootVac/jewel_$$i.root SamplesBaseNR/zjet_pthat150/PU14Vac/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat150/RootSimple/jewel_$$i.root SamplesBaseNR/zjet_pthat150/PU14Simple/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat70/RootVac/jewel_$$i.root SamplesBaseNR/zjet_pthat70/PU14Vac/jewel_$$i.pu14; done
	for i in `seq 1 30`; do echo $$i; ./Execute SamplesBaseNR/zjet_pthat70/RootSimple/jewel_$$i.root SamplesBaseNR/zjet_pthat70/PU14Simple/jewel_$$i.pu14; done
