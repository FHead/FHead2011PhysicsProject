
EventFile = SortedEventList
TestEventFile = SmallSortedEventList

SortFile:
	grep Entry < eventlist.txt | awk '{print $$11,$$15,$$13}' | tr ' ' ':' | uniq > $(EventFile)
	head -n 10 $(EventFile) > $(TestEventFile)

TestPickNoPU:
	edmPickEvents.py --runInteractive /QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-NoPU_94X_mc2017_realistic_v10-v2/AODSIM $(TestEventFile)
	mv pickevents.root TestNoPUEvents.root

PickNoPU:
	edmPickEvents.py --maxEventsInteractive 250 --runInteractive /QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-NoPU_94X_mc2017_realistic_v10-v2/AODSIM $(EventFile)
	mv pickevents.root NoPUEvents.root

PickPU:
	edmPickEvents.py --maxEventsInteractive 250 --runInteractive /QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-FlatPU0to70_94X_mc2017_realistic_v10-v1/AODSIM $(EventFile)
	mv pickevents.root WithPUEvents.root
