mkdir -p bin library

g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o \
   -I$RootMacrosBase/
g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++11
g++ source/CATree.cpp -I. -c -o library/CATree.o -I$RootMacrosBase/ -std=c++11
g++ source/SDJetHelper.cpp -I. -c -o library/SDJetHelper.o \
   `root-config --cflags` -std=c++11 -I$RootMacrosBase/
g++ source/EventMatching.cpp -I. -c -o library/EventMatching.o `root-config --cflags` -std=c++11

g++ source/ScaleHistograms.cpp -o bin/ScaleHistograms `root-config --libs` `root-config --cflags`
g++ source/AttachTags.cpp -o bin/AttachTags `root-config --libs` `root-config --cflags`

