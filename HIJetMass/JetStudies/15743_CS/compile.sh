CompileRootMacro CSCheck.cpp RunCheck -I ../../CommonCode/include ../../CommonCode/library/* \
   `fastjet-config --libs` `fastjet-config --cxxflags` \
   /Users/yichen/Programs/fastjet/fastjet-3.2.1/../install321/lib/libConstituentSubtractor.a
CompileRootMacro CSCheckPartII.cpp RunCheckPartII -I ../../CommonCode/include ../../CommonCode/library/* \
   `fastjet-config --libs` `fastjet-config --cxxflags` \
   /Users/yichen/Programs/fastjet/fastjet-3.2.1/../install321/lib/libConstituentSubtractor.a
