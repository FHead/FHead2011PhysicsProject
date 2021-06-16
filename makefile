

InitializeAll:
	git submodule init
	git submodule update
	git submodule foreach git checkout master

UpdateAll:
	git submodule update --recursive --remote
