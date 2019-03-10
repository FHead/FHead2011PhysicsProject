g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o \
   -I$HOME/FHeadHelperCode/RootMacros/
g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++1y
g++ source/CATree.cpp -I. -c -o library/CATree.o -I$HOME/FHeadHelperCode/RootMacros/ -std=c++1y
g++ source/SDJetHelper.cpp -I. -c -o library/SDJetHelper.o \
   `root-config --cflags` -std=c++1y -I$HOME/FHeadHelperCode/RootMacros/
g++ source/EventMatching.cpp -I. -c -o library/EventMatching.o `root-config --cflags` -std=c++1y

# CompileRootMacro source/ScaleHistograms.cpp bin/ScaleHistograms
# CompileRootMacro source/AttachTags.cpp bin/AttachTags

CompileRootMacro source/SimpleJetCorrector.cc library/SimpleJetCorrector.o -c -Iinclude
CompileRootMacro source/FactorizedJetCorrector.cc library/FactorizedJetCorrector.o -c -Iinclude
CompileRootMacro source/JetCorrectorParameters.cc library/JetCorrectorParameters.o -c -Iinclude
CompileRootMacro source/Utilities.cc library/Utilities.o -c -Iinclude
CompileRootMacro source/SimpleJetCorrectionUncertainty.cc library/SimpleJetCorrectionUncertainty.o -c -Iinclude
CompileRootMacro source/JetCorrectionUncertainty.cc library/JetCorrectionUncertainty.o -c -Iinclude

