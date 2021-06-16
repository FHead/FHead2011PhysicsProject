

InitializeAll:
	git submodule init
	git submodule checkout
	git submodule foreach git checkout master

UpdateAll:
	git submodule update --recursive --remote
