g++ RunExample.cpp -o RunExample \
   `root-config --libs` `root-config --cflags` \
   -I$RootMacrosBase $RootMacrosBase/Code/library/* \
   -I../../CommonCode/include ../../CommonCode/library/*
