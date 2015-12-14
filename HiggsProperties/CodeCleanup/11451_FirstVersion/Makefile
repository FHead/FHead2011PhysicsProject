INCLUDE   = -I./include
OBJECTS   = library/CalculateME.o library/DrawRandom2.o library/AngleConversion.o library/TauHelperFunctions2.o
CC        = g++
ROOTLIBS  = `root-config --glibs`
ROOTFLAGS = `root-config --cflags`

all: bin/ProduceBackgroundMap bin/ProduceSignalMap bin/AttachLikelihood

bin/%: source/%.cpp $(OBJECTS)
	$(CC) $< $(INCLUDE) $(OBJECTS) $(ROOTLIBS) $(ROOTFLAGS) -o $@

library/%.o: source/%.cc
	$(CC) $< $(INCLUDE) -c -o $@

clean:
	rm -f library/* bin/*
