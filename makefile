

InitializeAll:
	git submodule init
	git submodule update
	git submodule foreach git checkout master

UpdateAll:
	# git submodule update --recursive --remote
	git submodule foreach git pull

UpdateAllRemote:
	for i in */; do git add $$i; done
	git commit -m "Update all remote"
	git push
