root_cflags=`sh $ROOTSYS/bin/root-config --cflags`
root_libs=`sh $ROOTSYS/bin/root-config --libs`
roofit_libs="-lRooFitCore -lRooFit -lMinuit -lFoam -lMathMore"
fastjet_cflags=`fastjet-config --cxxflags`
fastjet_libs=`fastjet-config --libs`
extrainclude="-I/home/$USER/RootMacros"
pythia_include="-I$PYTHIA8/include"
pythia_libs="-L$PYTHIA8/lib/archive -lpythia8 -llhapdfdummy"
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
# cxx="-m64"

libs="$root_libs $roofit_libs $fastjet_libs $pythia_libs"
flags="$cxx $cxxflags $fastjet_cflags $root_cflags"
include="$extrainclude $pythia_include"

g++ Utilities.cc $flags $include -c -o Utilities.o
g++ JetCorrectorParameters.cc $flags $include -c -o JetCorrectorParameters.o
g++ SimpleJetCorrectionUncertainty.cc $flags $include -c -o SimpleJetCorrectionUncertainty.o
g++ JetCorrectionUncertainty.cc $flags $include -c -o JetCorrectionUncertainty.o

extra="Utilities.o JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o JetCorrectionUncertainty.o"

g++ GetJES.cpp $libs $flags $include $extra -o a.out
g++ GetJES_030.cpp $libs $flags $include $extra -o a.out.030
g++ GetJES_035.cpp $libs $flags $include $extra -o a.out.035
g++ GetJES_038.cpp $libs $flags $include $extra -o a.out.038
g++ GetJES_042.cpp $libs $flags $include $extra -o a.out.042
g++ GetJES_045.cpp $libs $flags $include $extra -o a.out.045
g++ GetJES_048.cpp $libs $flags $include $extra -o a.out.048





