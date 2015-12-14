CompileRootMacro MakePlots.cpp a.out -I ../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o

# ./a.out VeryLooseCut s1_
# ./a.out LooseCutEM t1_
# ./a.out LooseCutEE v1_
# ./a.out TightCutEM T1_
# ./a.out TightCutEE V1_
# ./a.out OptLooseCutEM tt1_
# ./a.out OptLooseCutEE vv1_
# ./a.out OptTightCutEM TT1_
# ./a.out OptTightCutEE VV1_

./a.out Normal.dh TightCutEM T1_ true
./a.out Absolute.dh TightCutEM T1_ false

for i in MatrixNormalReal*
do
   cp $i ${i/MatrixNormalReal/GeneratorLevelPrecision-Photons-ComponentSize}
done

for i in MatrixAbsoluteReal*
do
   cp $i ${i/MatrixAbsoluteReal/GeneratorLevelPrecision-Photons-AbsoluteComponentSize}
done

for i in MatrixNormalSMReal*
do
   cp $i ${i/MatrixNormalSMReal/GeneratorLevelPrecision-Photons-ComponentSizeSMLike}
done

mkdir -p PairingAMatrixEM
mv Matrix* PairingAMatrixEM

./a.out Normal.dh OppositeCutEM TTT1_ true
./a.out Absolute.dh OppositeCutEM TTT1_ false

mkdir -p PairingBMatrixEM
mv Matrix* PairingBMatrixEM

./a.out Normal.dh SameCutEM TTTT1_ true
./a.out Absolute.dh SameCutEM TTTT1_ false

mkdir -p PairingCMatrixEM
mv Matrix* PairingCMatrixEM



./a.out Normal.dh TightCutEE V1_ true
./a.out Absolute.dh TightCutEE V1_ false

mkdir -p PairingAMatrixEE
mv Matrix* PairingAMatrixEE

./a.out Normal.dh OppositeCutEE VVV1_ true
./a.out Absolute.dh OppositeCutEE VVV1_ false

mkdir -p PairingBMatrixEE
mv Matrix* PairingBMatrixEE

./a.out Normal.dh SameCutEE VVVV1_ true
./a.out Absolute.dh SameCutEE VVVV1_ false

mkdir -p PairingCMatrixEE
mv Matrix* PairingCMatrixEE

