default: SayHI

SayHI:
	echo Hi

ProcessL1:
	cut --delim=',' --field=1-2 < inputPrescaleList.txt | tr ',' ' ' | sed "s/-1/0/g" \
		| sed "s/^HLT_L1/L1_/" | sed "s/BptxAND/_BptxAND/" | sed "s/_v[0-9]//" \
		| sed "s/10100/_10_100/" | sed "s/30100/_30_100/" | sed "s/50100/_50_100/" \
		| sed "s/20100/_20_100/" | sed "s/70100/_70_100/" | sed "s/80100/_80_100/" \
		| sed "s/60100/_60_100/" | sed "s/40100/_40_100/" \
		| sed "s/FWD/_FWD/" | sed "s/_Cent/Cent/" | sed "s/Cent/_Cent/" \
		| sed "s/_Single/Single/g" | sed "s/Single/_Single/g" \
		| sed "s/Mid/_Mid/g" | sed "s/\([0-9]\)Min/\1_Min/g" > L1Prescale.txt

Execute: CalculateOverlap.cpp
	g++ CalculateOverlap.cpp `root-config --cflags --libs` -o Execute -I/afs/cern.ch/user/c/chenyi/RootMacros/

TestRun: Execute
	./Execute --L1 L1Prescale.txt --HLT HLTList.txt --OpenHLT openHLT_MinBias.root --MBRate 40000 | tee Log
	cp Output.pdf ~/public/html/


