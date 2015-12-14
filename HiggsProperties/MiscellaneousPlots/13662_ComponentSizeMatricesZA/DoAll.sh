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

for i in A B C D E F G H I J K
do
   mkdir -p Pairing/2e2mu-${i}
   mkdir -p Pairing/4e-${i}
   mkdir -p PairingPDF/2e2mu-${i}
   mkdir -p PairingPDF/4e-${i}

   ./a.out Normal.dh Cut${i} T${i}1_ true
   ./a.out Absolute.dh Cut${i} T${i}1_ false
   
   cp Matrix*pdf PairingPDF/2e2mu-${i}
   mv Matrix* Pairing/2e2mu-${i}

   ./a.out Normal.dh Cut${i} V${i}1_ true
   ./a.out Absolute.dh Cut${i} V${i}1_ false
   
   cp Matrix*pdf PairingPDF/4e-${i}
   mv Matrix* Pairing/4e-${i}
done


