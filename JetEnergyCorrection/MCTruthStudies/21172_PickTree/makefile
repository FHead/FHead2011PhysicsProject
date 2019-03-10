Dataset    = /QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/RunIIFall18GS-102X_upgrade2018_realistic_v11-v1/GEN-SIM
Cut        = RefPT > 200 && RefPT < 250 && RefEta > 2.8 && RefEta < 2.9 && PTHat < 500
Cut        = RefPT > 200 && RefPT < 250 && RefEta < 0.1 && RefEta > -0.1 && PTHat < 500
EventCount = 1000
Cut        = RefPT > 100 && RefEta < 0.1 && RefEta > -0.1 && PTHat < 500

default: Execute

ListEvents: ListEvents.cpp
	CompileRootMacro ListEvents.cpp ListEvents

Execute: ListEvents
	if [ ! -f /tmp/chenyi/All.root ]; then cp SynchTree/All.root /tmp/chenyi; fi
	./ListEvents --File /tmp/chenyi/All.root --Cut "$(Cut)" --EventCount $(EventCount) > Events.txt
	cut --delim=':' --field=2 < Events.txt | sort | uniq > Lumis.txt
	edmPickEvents.py $(Dataset) Events.txt

DASHack:
	dasgoclient -query 'file dataset=$(Dataset)' > Files.txt
	for File in `cat Files.txt`; do echo "$$File `dasgoclient -query \"lumi file=$$File\"`"; done > Hack.txt

GetFileList:
	rm -rf GoodFileListMeow.txt
	for i in `cat Lumis.txt`; do echo $$i; cat Hack.txt | tr '[]' ',' | grep ",$$i," | cut --delim=' ' --field=1; cat Hack.txt | tr '[]' ',' | grep ",$$i," | cut --delim=' ' --field=1 >> GoodFileListMeow.txt; done
	cat GoodFileListMeow.txt | sort | uniq > GoodFileList.txt
	rm GoodFileListMeow.txt

PickEvents:
	edmCopyPickMerge outputFile=/tmp/chenyi/pickevents.root \
		eventsToProcess=`cat Events.txt | cut --delim=':' --field=1,3 | tr '\n' ',' | sed "s/,$$//"` \
		inputFiles=`cat GoodFileList.txt | tr '\n' ',' | sed "s/,$$//"`
