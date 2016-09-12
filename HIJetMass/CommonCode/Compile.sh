g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o
g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++11
g++ source/CATree.cpp -I. -c -o library/CATree.o -I/afs/cern.ch/user/c/chenyi/RootMacros/


