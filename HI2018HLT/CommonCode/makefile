RootMacro=$$HOME/FHeadHelperCode/RootMacros

default: Libraries

Libraries: library/BasicUtilities.o library/Messenger.o library/CATree.o library/SDJetHelper.o library/EventMatching.o

Executables: bin/ScaleHistograms bin/AttachTags

library/BasicUtilities.o: source/BasicUtilities.cpp
	g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o \
   	-I$(RootMacro) -std=c++17

library/Messenger.o: source/Messenger.cpp
	g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++17

library/CATree.o: source/CATree.cpp
	g++ source/CATree.cpp -I. -c -o library/CATree.o -I$(RootMacro) -std=c++17

library/SDJetHelper.o: source/SDJetHelper.cpp
	g++ source/SDJetHelper.cpp -I. -c -o library/SDJetHelper.o \
   	`root-config --cflags` -std=c++17 -I$(RootMacro)

library/EventMatching.o: source/EventMatching.cpp
	g++ source/EventMatching.cpp -I. -c -o library/EventMatching.o `root-config --cflags` -std=c++17

bin/ScaleHistograms: source/ScaleHistograms.cpp
	CompileRootMacro source/ScaleHistograms.cpp bin/ScaleHistograms

bin/AttachTags: source/AttachTags.cpp
	CompileRootMacro source/AttachTags.cpp bin/AttachTags

