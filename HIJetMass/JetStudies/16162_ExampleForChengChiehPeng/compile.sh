g++ source/Messenger.cpp -c -o Messenger.o -I. `root-config --cflags`
g++ ExampleFastJetSoftDrop.cpp -o RunExample -Iinclude \
   `root-config --libs` `root-config --cflags` \
   Messenger.o \
   `fastjet-config --libs` `fastjet-config --cxxflags`
