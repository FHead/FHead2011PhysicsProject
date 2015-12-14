input=GenerateEvents.cpp
output=RunToy

root_cflags=`root-config --cflags`
root_libs=`root-config --libs`
fastjet_cflags=`fastjet-config --cxxflags`
fastjet_libs=`fastjet-config --libs`
pythia_include='-I/home/yichen/Programs/PYTHIA8/pythia8142/include'
pythia_lib='-L/home/yichen/Programs/PYTHIA8/pythia8142/lib/archive -lpythia8 -llhapdfdummy'
cxxflags="-g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2"
extrainclude="-I/home/$USER/RootMacros"

echo "g++ $input $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxxflags $extrainclude $pythia_include $pythia_lib -o $output"
g++ $input $root_libs $root_cflags $fastjet_libs $fastjet_cflags $cxxflags $extrainclude $pythia_include $pythia_lib -o $output



