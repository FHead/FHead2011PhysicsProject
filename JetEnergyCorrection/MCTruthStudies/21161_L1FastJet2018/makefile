all: RunListRunLumi RunMatchFiles RunPrepareStep2Submission Columnize

RunListRunLumi: ListRunLumi.cpp
	g++ ListRunLumi.cpp -o RunListRunLumi \
		`root-config --cflags --libs`

RunMatchFiles: MatchFiles.cpp
	g++ MatchFiles.cpp -o RunMatchFiles

RunPrepareStep2Submission: PrepareStep2Submission.cpp
	g++ PrepareStep2Submission.cpp -o RunPrepareStep2Submission

Columnize: Columnize.cpp
	g++ Columnize.cpp -o Columnize

PrepareStep2:
	./RunPrepareStep2Submission 2 > SubmitStep2.sh
	sed "s/Step2/Step2b/g" < SubmitStep2.sh > SubmitStep2b.sh

ExtractStep2bArguments:
	grep Arguments Step2b.condor | cut --delim=' ' --field=3- > Step2b.arguments

ManualStep2b:
	mkdir -p /tmp/chenyi/Temp
	rm Temp
	ln -s /tmp/chenti/Temp .
	cp Step2bPUMatching.sh Temp/
	cp Step2b.arguments Temp/
	cd Temp/
	while read arguments; do bash Step2bPUMatching.sh $arguments; done < Step2b.arguments

