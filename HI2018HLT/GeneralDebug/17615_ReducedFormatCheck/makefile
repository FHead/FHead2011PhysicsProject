Execute:
	cat CopiedFromAustin | tr ',' '\n' | sed "s/[ ]*//g" | grep -v "^$$" | sort > SortedFromAustin
	cat CopiedFromGoogleDoc | grep -v '#' | awk '{if($$1 < 11000) print}' | sed "s/[ ]*//g" | grep -v "^$$" | sort > SortedFromGoogleDoc
	echo "Left: From Austin, Right: From Google Doc" 
	diff -w SortedFromAustin SortedFromGoogleDoc | colordiff
