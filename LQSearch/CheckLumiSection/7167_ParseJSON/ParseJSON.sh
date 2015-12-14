cat $1 | sed "s#, \"#\n#g" | sed "s/\([1-9][0-9]*\), \([1-9][0-9]*\)/\1-\2/g" | sed "s/[{}\"\[]//g" | sed "s#\]##g" | sort

TEMP1=`cat $1 | sed "s#, \"#\n#g" | sed "s/\([1-9][0-9]*\), \([1-9][0-9]*\)/\1-\2/g" | sed "s/[{}\"\[]//g" | sed "s#\]##g" | sort | sed "s/[0-9]*://g" | sed "s/,/\n/g" | sed "s/-/ /g" | sed "s/^ //g" | cut --delim=' ' --field=1-1 | Sum`
TEMP2=`cat $1 | sed "s#, \"#\n#g" | sed "s/\([1-9][0-9]*\), \([1-9][0-9]*\)/\1-\2/g" | sed "s/[{}\"\[]//g" | sed "s#\]##g" | sort | sed "s/[0-9]*://g" | sed "s/,/\n/g" | sed "s/-/ /g" | sed "s/^ //g" | cut --delim=' ' --field=2-2 | Sum`
TEMP3=`cat $1 | sed "s#, \"#\n#g" | sed "s/\([1-9][0-9]*\), \([1-9][0-9]*\)/\1-\2/g" | sed "s/[{}\"\[]//g" | sed "s#\]##g" | sort | sed "s/[0-9]*://g" | sed "s/,/\n/g" | sed "s/-/ /g" | sed "s/^ //g" | cut --delim=' ' --field=2-2 | wc -l`

echo
echo "Total Number of lumi sections = `echo $TEMP2 | SubtractConst $TEMP1 | AddConst $TEMP3`"


