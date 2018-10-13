Merge:
	hadd -f openHLT.root `ls -l Result/*root | awk '{if($$5 > 20000) print $$9}'`

ListBad:
	ls -l Result/*root | awk '{if($$5 < 20000) print $$9}' | cat -n

SubmitJobs:
	bash Submit.sh

ResubmitJobs:
	bash SubmitAgain.sh
