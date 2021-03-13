N = 100

default: TestRun TestRunHarvest

TestRunHarvest: ExecuteHarvest
	./ExecuteHarvest --DHFile JERTestRun2017.dh --Output JER2017.pdf
	./ExecuteHarvest --DHFile JERTestRun2018.dh --Output JER2018.pdf
	cp JER*pdf ~/public/html/

TestRun: Execute
	./Execute --Input `ls JRA2017/*root | head -n250 | tr '\n' ','` \
		--MinPT 25 --Algorithm ak4pf --MaxDR 0.2 --Output JERTestRun2017.pdf --DHFile JERTestRun2017.dh
	./Execute --Input `ls JRA2018/*root | head -n250 | tr '\n' ','` \
		--MinPT 25 --Algorithm ak4pf --MaxDR 0.2 --Output JERTestRun2018.pdf --DHFile JERTestRun2018.dh
	cp JERTestRun*.pdf ~/public/html

RunHarvestAll: ExecuteHarvest
	./ExecuteHarvest --DHFile JERRun2017_015.dh --Output JER2017_015.pdf
	./ExecuteHarvest --DHFile JERRun2017_020.dh --Output JER2017_020.pdf
	./ExecuteHarvest --DHFile JERRun2017_030.dh --Output JER2017_030.pdf
	./ExecuteHarvest --DHFile JERRun2017_040.dh --Output JER2017_040.pdf
	./ExecuteHarvest --DHFile JERRun2017_050.dh --Output JER2017_050.pdf
	./ExecuteHarvest --DHFile JERRun2017_060.dh --Output JER2017_060.pdf
	./ExecuteHarvest --DHFile JERRun2017_080.dh --Output JER2017_080.pdf
	./ExecuteHarvest --DHFile JERRun2017_100.dh --Output JER2017_100.pdf
	./ExecuteHarvest --DHFile JERRun2017_120.dh --Output JER2017_120.pdf
	./ExecuteHarvest --DHFile JERRun2018_015.dh --Output JER2018_015.pdf
	./ExecuteHarvest --DHFile JERRun2018_020.dh --Output JER2018_020.pdf
	./ExecuteHarvest --DHFile JERRun2018_030.dh --Output JER2018_030.pdf
	./ExecuteHarvest --DHFile JERRun2018_040.dh --Output JER2018_040.pdf
	./ExecuteHarvest --DHFile JERRun2018_050.dh --Output JER2018_050.pdf
	./ExecuteHarvest --DHFile JERRun2018_060.dh --Output JER2018_060.pdf
	./ExecuteHarvest --DHFile JERRun2018_080.dh --Output JER2018_080.pdf
	./ExecuteHarvest --DHFile JERRun2018_100.dh --Output JER2018_100.pdf
	./ExecuteHarvest --DHFile JERRun2018_120.dh --Output JER2018_120.pdf
	cp JER*.pdf ~/public/html/

RunAll: Execute
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak1pf --MaxDR 0.07 --Output JERRun2017_R015.pdf --DHFile JERRun2017_R015.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak2pf --MaxDR 0.10 --Output JERRun2017_R020.pdf --DHFile JERRun2017_R020.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak3pf --MaxDR 0.15 --Output JERRun2017_R030.pdf --DHFile JERRun2017_R030.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak4pf --MaxDR 0.20 --Output JERRun2017_R040.pdf --DHFile JERRun2017_R040.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak5pf --MaxDR 0.25 --Output JERRun2017_R050.pdf --DHFile JERRun2017_R050.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak6pf --MaxDR 0.30 --Output JERRun2017_R060.pdf --DHFile JERRun2017_R060.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak7pf --MaxDR 0.40 --Output JERRun2017_R080.pdf --DHFile JERRun2017_R080.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak8pf --MaxDR 0.50 --Output JERRun2017_R100.pdf --DHFile JERRun2017_R100.dh
	./Execute --Input `ls JRA2017/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak9pf --MaxDR 0.60 --Output JERRun2017_R120.pdf --DHFile JERRun2017_R120.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak1pf --MaxDR 0.07 --Output JERRun2018_R015.pdf --DHFile JERRun2018_R015.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak2pf --MaxDR 0.10 --Output JERRun2018_R020.pdf --DHFile JERRun2018_R020.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak3pf --MaxDR 0.15 --Output JERRun2018_R030.pdf --DHFile JERRun2018_R030.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak4pf --MaxDR 0.20 --Output JERRun2018_R040.pdf --DHFile JERRun2018_R040.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak5pf --MaxDR 0.25 --Output JERRun2018_R050.pdf --DHFile JERRun2018_R050.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak6pf --MaxDR 0.30 --Output JERRun2018_R060.pdf --DHFile JERRun2018_R060.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak7pf --MaxDR 0.40 --Output JERRun2018_R080.pdf --DHFile JERRun2018_R080.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak8pf --MaxDR 0.50 --Output JERRun2018_R100.pdf --DHFile JERRun2018_R100.dh
	./Execute --Input `ls JRA2018/*root | head -n$(N) | tr '\n' ','` \
		--MinPT 25 --Algorithm ak9pf --MaxDR 0.60 --Output JERRun2018_R120.pdf --DHFile JERRun2018_R120.dh
	cp JERRun*.pdf ~/public/html

ExecuteHarvest: HarvestJER.cpp
	CompileRootMacro HarvestJER.cpp ExecuteHarvest

Execute: DeriveJER.cpp
	rm -f Execute
	CompileRootMacro DeriveJER.cpp Execute
