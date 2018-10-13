Merge:
	for i in TTbar DiJet60 DiJet100; do hadd -f openHLT_$$i.root `ls -l Result/*$$i*root | awk '{if($$5 > 20000) print $$9}'`; done

ListBad:
	ls -l Result/*root | awk '{if($$5 < 20000) print $$9}' | cat -n

ListGood:
	ls -l Result/*root | awk '{if($$5 > 20000) print $$9}' | cat -n

SubmitJobs:
	bash Submit.sh

ResubmitJobs:
	bash SubmitAgain.sh
