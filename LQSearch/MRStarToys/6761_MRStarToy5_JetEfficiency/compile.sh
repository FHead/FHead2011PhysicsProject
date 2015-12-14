input1=MRToys.cpp
output1=RunToy
input2=PlotCurves.cpp
output2=CurvePlotting

root_cflags=`root-config --cflags`
root_libs=`root-config --libs`
fastjet_cflags=`fastjet-config --cxxflags`
fastjet_libs=`fastjet-config --libs`
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
# cxx="-m64"
pythia_include="-I$PYTHIA8/include"
pythia_lib="-L$PYTHIA8/lib/archive -lpythia8 -llhapdfdummy"
extrainclude="-I/home/$USER/RootMacros"

# echo "g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $pythia_include $pythia_lib -o $output1"
# g++ $input1 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $pythia_include $pythia_lib -o $output1
echo "g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $pythia_include $pythia_lib -o $output2"
g++ $input2 $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxx $cxxflags $extrainclude $pythia_include $pythia_lib -o $output2



