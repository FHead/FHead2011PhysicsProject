cat $1 | cut --delim=' ' --f=1-1 > Column1_$1.txt
cat $1 | cut --delim=' ' --f=2-2 > Column2_$1.txt
FileDivide Column1_$1.txt Column2_$1.txt Ratio_$1.txt
rm Column1_$1.txt
rm Column2_$1.txt


