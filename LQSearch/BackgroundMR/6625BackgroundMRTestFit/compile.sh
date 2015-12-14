input1=FitMRDistribution.cpp
input2=FitTwoExpMRDistribution.cpp
output1=PerformFit
output2=TwoExpPerformFit

root_cflags=`root-config --cflags`
root_libs=`root-config --libs`
roofit_libs="-lRooFitCore -lRooFit -lMinuit -lFoam"
fastjet_cflags=`fastjet-config --cxxflags`
fastjet_libs=`fastjet-config --libs`
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
cxx="-m64"
extrainclude="-I/home/$USER/RootMacros"

echo "g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs -o $output1"
g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs -o $output1

echo "g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs -o $output2"
g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $roofit_libs -o $output2



