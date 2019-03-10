sh compile-local.sh

# ./Run ../../Samples/Jewel/16451/16451.vac.root 16451.vac.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.0.root 16451.0.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.1.root 16451.1.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.2.root 16451.2.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.3.root 16451.3.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.4.root 16451.4.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.5.root 16451.5.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.6.root 16451.6.root Jewel -100 100
# ./Run ../../Samples/Jewel/16451/16451.7.root 16451.7.root Jewel -100 100
./Run ../../Samples/Jewel/16451/16451.8.root 16451.8.root Jewel -100 100

CompileRootMacro MakePlots.cpp a.out

./a.out

