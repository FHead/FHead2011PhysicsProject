CompileRootMacro MakeFigure2.cpp a.out -I ../../CommonCode/include ../../CommonCode/library/AngleConversion.o

./a.out gg_h_2e2mu_A2AA_LooseCuts.root Figure2TempAAEM
./a.out gg_h_2e2mu_A2ZA_LooseCuts.root Figure2TempZAEM
./a.out gg_h_2e2mu_A2ZZ_LooseCuts.root Figure2TempZZEM
./a.out gg_h_4e_A2AA_LooseCuts.root Figure2TempAAEE
./a.out gg_h_4e_A2ZA_LooseCuts.root Figure2TempZAEE
./a.out gg_h_4e_A2ZZ_LooseCuts.root Figure2TempZZEE

for i in png C eps pdf
do
   mv Figure2TempAAEM-M1M2CMSNoCut.$i Figure2AAEM.$i
   mv Figure2TempZAEM-M1M2CMSNoCut.$i Figure2ZAEM.$i
   mv Figure2TempZZEM-M1M2CMSNoCut.$i Figure2ZZEM.$i
   mv Figure2TempAAEE-M1M2CMSNoCut.$i Figure2AAEE.$i
   mv Figure2TempZAEE-M1M2CMSNoCut.$i Figure2ZAEE.$i
   mv Figure2TempZZEE-M1M2CMSNoCut.$i Figure2ZZEE.$i
done

rm Figure2Temp*

