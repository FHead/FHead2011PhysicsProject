
CopyYAML:
	cp ../22653_RAA/*yaml .
	cp ../22653_RRAA/*yaml .
	cp ../22653_SpectraRatio/*yaml .
	cp ../22653_Spectrum/*yaml .

CheckSubmission:
	wget https://raw.githubusercontent.com/HEPData/hepdata-submission/master/scripts/check.py
	python3 check.py

Packup:
	rm Submission.tar.gz
	tar zcvf Submission.tar.gz *yaml
	cp Submission.tar.gz ~/public/html/
