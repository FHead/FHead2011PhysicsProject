INCLUDE   = -I./include
OBJECTS   = library/CalculateME.o library/DrawRandom2.o library/AngleConversion.o library/TauHelperFunctions2.o
CC        = g++
ROOTLIBS  = `root-config --glibs`
ROOTFLAGS = `root-config --cflags`

all: bin/ProduceBackgroundMap bin/ProduceSignalMap bin/AttachLikelihood bin/VisualizeMap bin/ExampleFit

bookkeeping:
	cd bin; ln -s ../HiggsFiles; cd ..

bin/VisualizeMap: source/VisualizeMap.cpp library/TauHelperFunctions2.o
	$(CC) $< $(INCLUDE) library/TauHelperFunctions2.o $(ROOTLIBS) $(ROOTFLAGS) -o $@

bin/ProduceBackgroundMap: source/ProduceBackgroundMap.cpp $(OBJECTS)
	$(CC) $< $(INCLUDE) $(OBJECTS) $(ROOTLIBS) $(ROOTFLAGS) -o $@

bin/ProduceSignalMap: source/ProduceSignalMap.cpp $(OBJECTS)
	$(CC) $< $(INCLUDE) $(OBJECTS) $(ROOTLIBS) $(ROOTFLAGS) -o $@

bin/AttachLikelihood: source/AttachLikelihood.cpp $(OBJECTS)
	$(CC) $< $(INCLUDE) $(OBJECTS) $(ROOTLIBS) $(ROOTFLAGS) -o $@

bin/ExampleFit: source/ExampleFit.cpp $(OBJECTS)
	$(CC) $< $(INCLUDE) $(OBJECTS) $(ROOTLIBS) $(ROOTFLAGS) -o $@

library/%.o: source/%.cc
	$(CC) $< $(INCLUDE) -c -o $@

clean:
	rm -f library/* bin/*
