default: Execute

Execute: Converter.cpp
	CompileRootMacro Converter.cpp Execute

ConvertVacuum: Execute
	for i in `seq 1 10`; do ./Execute --Input Recoil/jewel_recoils_vac_$$i.root --Output Recoil/smallfiles/jewel_recoils_vac_$$i; done

ConvertRecoil: Execute
	for i in `seq 1 10`; do ./Execute --Input Recoil/jewel_recoils_simple_$$i.root --Output Recoil/smallfiles/jewel_recoils_simple_$$i; done

ConvertNoRecoil: Execute
	for i in `seq 1 10`; do ./Execute --Input NoRecoil/jewel_simple_$$i.root --Output NoRecoil/smallfiles/jewel_simple_$$i; done



