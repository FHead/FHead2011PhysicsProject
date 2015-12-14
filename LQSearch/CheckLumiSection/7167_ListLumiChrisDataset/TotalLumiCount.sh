cat $1 | sed "s/[0-9]*(\([0-9]*\))/\1/g" | cut --field=1-1 --delim=' ' | sed "s/://g" | grep "[0-9]" | grep -v RooFit | Sum
