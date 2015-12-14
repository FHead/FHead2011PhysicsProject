input1=MakeMRTree.cpp
output1=ProduceTree
input2=FitMRDistribution.cpp
output2=PerformFit

root_cflags=`root-config --cflags`
root_libs=`root-config --libs`
roofit_libs="-lRooFitCore -lRooFit -lMinuit -lFoam"
fastjet_cflags=`fastjet-config --cxxflags`
fastjet_libs=`fastjet-config --libs`
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
# cxx="-m64"
extrainclude="-I/home/$USER/RootMacros"
pythia_include="-I$PYTHIA8/include"
pythia_lib="-L$PYTHIA8/lib/archive -lpythia8 -llhapdfdummy"

# echo "g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs $pythia_include $pythia_lib -o $output1"
# g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs $pythia_include $pythia_lib -o $output1
echo "g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs $pythia_include $pythia_lib -o $output2"
g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs $pythia_include $pythia_lib -o $output2




