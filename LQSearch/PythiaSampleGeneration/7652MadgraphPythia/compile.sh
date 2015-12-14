#!/bin/sh

input=$1
output=$2

if [ -z $1 ]; then
   echo "Please specify the source file you want to compile"
   exit
fi

if [ -z $2 ]; then
   output=a.out
fi

root_cflags=`sh $ROOTSYS/bin/root-config --cflags`
root_libs=`sh $ROOTSYS/bin/root-config --libs`
roofit_libs="-lRooFitCore -lRooFit -lMinuit -lFoam -lRooStats -lMathMore"
# fastjet_cflags=`fastjet-config --cxxflags`
# fastjet_libs=`fastjet-config --libs`
extrainclude="-I/$HOME/RootMacros"
pythia_include="-I$PYTHIA8/include"
pythia_libs="-L$PYTHIA8/lib/archive -lpythia8 -llhapdfdummy"
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
# cxx="-m64"
delphes_libs="/home/yichen/Programs/Madgraph/MadGraph5_v1_4_3/Delphes/lib/libUtilities.so"
delphes_include="-I/home/yichen/Programs/Madgraph/MadGraph5_v1_4_3/Delphes -I/home/yichen/Programs/Madgraph/MadGraph5_v1_4_3/Delphes/Examples/interface -I/home/yichen/Programs/Madgraph/MadGraph5_v1_4_3/Delphes/interface -I/home/yichen/Programs/Madgraph/MadGraph5_v1_4_3/Delphes/Utilities/ExRootAnalysis/interface"

# libs="$root_libs $roofit_libs $fastjet_libs $pythia_libs -lMathMore"
libs="$root_libs $roofit_libs $fastjet_libs $pythia_libs $delphes_libs"
flags="$cxx $cxxflags $fastjet_cflags $root_cflags"
include="$extrainclude $pythia_include $delphes_include"

# quick fix....
libs=`echo $libs | sed "s/-lz//g"`

echo g++ $input $libs $flags $include -o $output
g++ $input $libs $flags $include -o $output



